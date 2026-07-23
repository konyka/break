#include <asset/vfs.h>
#include <core/log.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "async_loader_private.h" /* R255: AsyncMutex for concurrent PAK reads */

static u32 fnv1a(const char *str) {
    u32 hash = 2166136261u;
    while (*str) {
        hash ^= (u8)*str++;
        hash *= 16777619u;
    }
    return hash;
}

/* Next power of 2 >= n */
static u32 next_pow2(u32 n) {
    n--; n |= n >> 1; n |= n >> 2; n |= n >> 4; n |= n >> 8; n |= n >> 16; n++;
    return n < 4 ? 4 : n;
}

VFS *vfs_create(void) {
    VFS *vfs = calloc(1, sizeof(VFS));
    if (!vfs) return NULL;
    /* R255: serialize concurrent PAK fseek+fread (see struct comment). */
    AsyncMutex *lock = (AsyncMutex *)malloc(sizeof(AsyncMutex));
    if (lock) { async_mutex_init(lock); vfs->pak_lock = lock; }
    return vfs;
}

void vfs_destroy(VFS *vfs) {
    if (!vfs) return;
    for (u32 i = 0; i < vfs->mount_count; i++) {
        if (vfs->mounts[i].type == VFS_MOUNT_PAK) {
            if (vfs->mounts[i].pak_fp) fclose(vfs->mounts[i].pak_fp);
            free(vfs->mounts[i].pak_entries);
            free(vfs->mounts[i].pak_names);
            free(vfs->mounts[i].pak_hash_table);
        }
    }
    if (vfs->pak_lock) {
        async_mutex_destroy((AsyncMutex *)vfs->pak_lock);
        free(vfs->pak_lock);
    }
    free(vfs);
}

bool vfs_mount_dir(VFS *vfs, const char *dir_path) {
    /* R105-1: NULL check prevents strncpy UB and LOG_INFO %s NULL crash */
    if (!vfs || !dir_path || vfs->mount_count >= VFS_MAX_MOUNTS) return false;
    u32 idx = vfs->mount_count++;
    vfs->mounts[idx].type = VFS_MOUNT_DIR;
    strncpy(vfs->mounts[idx].path, dir_path, VFS_MAX_PATH - 1);
    vfs->mounts[idx].path[VFS_MAX_PATH - 1] = '\0';
    LOG_INFO("VFS: mounted directory '%s'", dir_path);
    return true;
}

bool vfs_mount_pak(VFS *vfs, const char *pak_path) {
    /* R105-1: NULL check prevents fopen UB and LOG_ERROR %s NULL crash */
    if (!vfs || !pak_path || vfs->mount_count >= VFS_MAX_MOUNTS) return false;

    FILE *fp = fopen(pak_path, "rb");
    if (!fp) {
        LOG_ERROR("VFS: failed to open pak '%s'", pak_path);
        return false;
    }

    PakHeader hdr;
    if (fread(&hdr, sizeof(hdr), 1, fp) != 1 || hdr.magic != VFS_PAK_MAGIC) {
        LOG_ERROR("VFS: invalid pak format '%s'", pak_path);
        fclose(fp);
        return false;
    }

    PakEntry *entries = calloc(hdr.entry_count, sizeof(PakEntry));
    if (!entries) { fclose(fp); return false; }

    if (fread(entries, sizeof(PakEntry), hdr.entry_count, fp) != hdr.entry_count) {
        free(entries); fclose(fp); return false;
    }

    /* R160-A: Allocate name_table_size + 1 to guarantee a null terminator at the
     * end of the buffer.  Without this, a PAK whose name table lacks a trailing
     * '\0' would cause strcmp in vfs_open to read one byte past the allocation. */
    char *names = calloc(hdr.name_table_size + 1, 1);
    if (!names) { free(entries); fclose(fp); return false; }
    if (fseek(fp, sizeof(PakHeader) + hdr.entry_count * sizeof(PakEntry), SEEK_SET) != 0) {
        free(names); free(entries); fclose(fp); return false;
    }
    if (fread(names, 1, hdr.name_table_size, fp) != hdr.name_table_size) {
        /* R143: Check fread return — truncated PAK name table */
        free(names); free(entries); fclose(fp); return false;
    }

    /* R157: Validate entry_count before multiplication to prevent u32 overflow
     * in next_pow2(entry_count * 2) — a malicious PAK with entry_count > 2^30
     * would overflow, producing a tiny hash table and infinite loop in probing. */
    if (hdr.entry_count > (1u << 30)) {
        free(names); free(entries); fclose(fp); return false;
    }

    /* Build hash table for O(1) lookup: open-addressing with linear probing.
     * R121: Moved BEFORE mount registration so failure doesn't require rollback. */
    u32 table_size = next_pow2(hdr.entry_count * 2);
    u32 *table = (u32 *)malloc(table_size * sizeof(u32));
    if (!table) { free(names); free(entries); fclose(fp); return false; }
    memset(table, 0xFF, table_size * sizeof(u32)); /* UINT32_MAX = empty */
    u32 mask = table_size - 1;
    for (u32 e = 0; e < hdr.entry_count; e++) {
        /* R160-A: Validate name_offset before inserting into hash table.
         * A malicious PAK could set name_offset >= name_table_size, causing an
         * out-of-bounds read in vfs_open when computing the name pointer. */
        if (entries[e].name_offset >= hdr.name_table_size) continue;
        u32 slot = entries[e].name_hash & mask;
        while (table[slot] != UINT32_MAX) {
            slot = (slot + 1) & mask;
        }
        table[slot] = e;
    }

    u32 idx = vfs->mount_count++;
    vfs->mounts[idx].type = VFS_MOUNT_PAK;
    strncpy(vfs->mounts[idx].path, pak_path, VFS_MAX_PATH - 1);
    vfs->mounts[idx].path[VFS_MAX_PATH - 1] = '\0';
    vfs->mounts[idx].pak_fp = fp;
    vfs->mounts[idx].pak_header = hdr;
    vfs->mounts[idx].pak_entries = entries;
    vfs->mounts[idx].pak_names = names;
    vfs->mounts[idx].pak_hash_table = table;
    vfs->mounts[idx].pak_hash_size = table_size;

    LOG_INFO("VFS: mounted pak '%s' (%u files)", pak_path, hdr.entry_count);
    return true;
}

/* R353: DIR mounts join mount_path/path and fopen — reject absolute paths and
 * ".." segments so a glTF uri / asset path cannot escape the mount root. */
static bool vfs_rel_path_safe(const char *path) {
    if (!path || !*path) return false;
    if (path[0] == '/') return false;
    const char *p = path;
    for (;;) {
        if (p[0] == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0'))
            return false;
        const char *slash = strchr(p, '/');
        if (!slash) break;
        p = slash + 1;
    }
    return true;
}

VFSFile *vfs_open(VFS *vfs, const char *path) {
    if (!vfs || !path) return NULL;
    if (!vfs_rel_path_safe(path)) return NULL;

    u32 hash = fnv1a(path);

    for (u32 i = vfs->mount_count; i > 0; i--) {
        u32 mi = i - 1;

        if (vfs->mounts[mi].type == VFS_MOUNT_PAK) {
            /* O(1) hash table lookup with linear probing */
            u32 *table = vfs->mounts[mi].pak_hash_table;
            u32 table_size = vfs->mounts[mi].pak_hash_size;
            if (table && table_size > 0) {
                u32 mask = table_size - 1;
                u32 slot = hash & mask;
                while (table[slot] != UINT32_MAX) {
                    u32 e = table[slot];
                    if (vfs->mounts[mi].pak_entries[e].name_hash == hash) {
                        const char *name = vfs->mounts[mi].pak_names + vfs->mounts[mi].pak_entries[e].name_offset;
                        if (strcmp(name, path) == 0) {
                            PakEntry *pe = &vfs->mounts[mi].pak_entries[e];
                            /* Single alloc: VFSFile + data */
                            u8 *vfs_block = (u8 *)calloc(1, sizeof(VFSFile) + pe->size);
                            if (!vfs_block) return NULL;
                            VFSFile *f = (VFSFile *)vfs_block;
                            f->data = vfs_block + sizeof(VFSFile);
                            f->size = pe->size;
                            /* R255: the shared pak_fp cursor is mutated by
                             * fseek+fread; async IO workers call this concurrently,
                             * so hold the lock across both to keep each read atomic.
                             * Without it two workers interleave seeks and one reads
                             * another entry's bytes — still passing the size check. */
                            AsyncMutex *lk = (AsyncMutex *)vfs->pak_lock;
                            if (lk) async_mutex_lock(lk);
                            bool pak_ok =
                                fseek(vfs->mounts[mi].pak_fp, pe->data_offset, SEEK_SET) == 0 &&
                                fread(f->data, 1, pe->size, vfs->mounts[mi].pak_fp) == pe->size;
                            if (lk) async_mutex_unlock(lk);
                            if (!pak_ok) {
                                /* R143: bad seek or truncated PAK entry data */
                                free(vfs_block); return NULL;
                            }
                            f->pos = 0;
                            return f;
                        }
                    }
                    slot = (slot + 1) & mask;
                }
            }
        } else {
            char full[512];
            snprintf(full, sizeof(full), "%s/%s", vfs->mounts[mi].path, path);
            FILE *fp = fopen(full, "rb");
            if (fp) {
                if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return NULL; }
                long fsz = ftell(fp);
                if (fsz < 0) { fclose(fp); return NULL; }
                usize sz = (usize)fsz;
                if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return NULL; }
                /* Single alloc: VFSFile + data */
                u8 *vfs_block = (u8 *)calloc(1, sizeof(VFSFile) + sz);
                if (!vfs_block) { fclose(fp); return NULL; }
                VFSFile *f = (VFSFile *)vfs_block;
                f->data = vfs_block + sizeof(VFSFile);
                f->size = sz;
                if (fread(f->data, 1, sz, fp) != sz) {
                    /* R143: Check fread return — truncated file data */
                    free(vfs_block); fclose(fp); return NULL;
                }
                fclose(fp);
                f->pos = 0;
                return f;
            }
        }
    }
    return NULL;
}

usize vfs_read(VFSFile *f, void *buf, usize size) {
    if (!f || !f->data) return 0;
    usize avail = f->size - f->pos;
    usize to_read = size < avail ? size : avail;
    memcpy(buf, f->data + f->pos, to_read);
    f->pos += to_read;
    return to_read;
}

i32 vfs_getc(VFSFile *f) {
    if (!f || f->pos >= f->size) return -1;
    return f->data[f->pos++];
}

bool vfs_eof(VFSFile *f) {
    return !f || f->pos >= f->size;
}

void vfs_close(VFSFile *f) {
    if (!f) return;
    free(f); /* single free: VFSFile + data (allocated as one block) */
}

usize vfs_size(VFSFile *f) {
    return f ? f->size : 0;
}

u8 *vfs_read_all(VFS *vfs, const char *path, usize *out_size) {
    VFSFile *f = vfs_open(vfs, path);
    if (!f) {
        if (out_size) *out_size = 0;
        return NULL;
    }
    /* Copy data out: in single-alloc layout, data is freed with vfs_close */
    u8 *data = (u8 *)malloc(f->size);
    if (data) {
        memcpy(data, f->data, f->size);
        if (out_size) *out_size = f->size;
    } else {
        /* R353: malloc fail must not leave a stale non-zero *out_size. */
        if (out_size) *out_size = 0;
    }
    vfs_close(f);
    return data;
}
