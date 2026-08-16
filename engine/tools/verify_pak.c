/* verify_pak.c — Verify packer output is VFS-compatible
 *
 * Mounts a .pak file via VFS, reads each entry, and compares
 * against the original file on disk. */
#include <asset/vfs.h>
#include <core/log.h>
#include <platform/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERIFY_CHUNK_BYTES (64u * 1024u)

static int verify_file(VFS *vfs, const char *pak_name,
                       const char *disk_path) {
    VFSFile *f = vfs_open(vfs, pak_name);
    if (!f) {
        fprintf(stderr, "FAIL: cannot open '%s' from pak\n", pak_name);
        return 0;
    }

    usize pak_size = vfs_size(f);

    /* Read from disk for comparison */
    FILE *fp = fopen(disk_path, "rb");
    if (!fp) {
        fprintf(stderr, "FAIL: cannot open '%s' on disk\n", disk_path);
        vfs_close(f);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long disk_size = ftell(fp);
    if (disk_size < 0) {
        fprintf(stderr, "FAIL: ftell error for '%s'\n", disk_path);
        fclose(fp);
        vfs_close(f);
        return 0;
    }
    fseek(fp, 0, SEEK_SET);

    if ((usize)disk_size != pak_size) {
        fprintf(stderr, "FAIL: size mismatch for '%s' (pak=%zu, disk=%ld)\n",
                pak_name, pak_size, disk_size);
        fclose(fp);
        vfs_close(f);
        return 0;
    }

    u8 *disk_buf = malloc(VERIFY_CHUNK_BYTES);
    u8 *pak_buf = malloc(VERIFY_CHUNK_BYTES);
    if (!disk_buf || !pak_buf) {
        fprintf(stderr, "FAIL: chunk buffer malloc failed for '%s'\n", pak_name);
        free(disk_buf);
        free(pak_buf);
        fclose(fp);
        vfs_close(f);
        return 0;
    }

    int match = 1;
    usize remaining = pak_size;
    while (remaining > 0) {
        usize chunk = remaining < VERIFY_CHUNK_BYTES ? remaining : VERIFY_CHUNK_BYTES;
        if (fread(disk_buf, 1, chunk, fp) != chunk) {
            fprintf(stderr, "FAIL: short read on disk for '%s'\n", disk_path);
            match = 0;
            break;
        }
        usize nread = vfs_read(f, pak_buf, chunk);
        if (nread != chunk) {
            fprintf(stderr, "FAIL: short read for '%s' (%zu/%zu)\n",
                    pak_name, nread, chunk);
            match = 0;
            break;
        }
        if (memcmp(disk_buf, pak_buf, chunk) != 0) {
            fprintf(stderr, "FAIL: content mismatch for '%s'\n", pak_name);
            match = 0;
            break;
        }
        remaining -= chunk;
    }

    if (match) printf("OK: '%s' (%zu bytes) matches\n", pak_name, pak_size);

    free(disk_buf);
    free(pak_buf);
    fclose(fp);
    vfs_close(f);
    return match;
}

/* R428: mirror packer.c's recursive scan_dir. The old code only scanned
 * top-level files of src_dir, but the packer recurses and stores names like
 * "sub/file" — nested entries were never verified yet the tool printed
 * success. Returns 1 when every file under base_dir/rel_prefix matches. */
typedef struct {
    VFS *vfs;
    const char *base_dir;
    int all_ok;
} VerifyCtx;

static void verify_visitor(const char *rel_path, const char *abs_path,
                           bool is_directory, void *user) {
    VerifyCtx *ctx = (VerifyCtx *)user;
    if (is_directory) return;
    if (!verify_file(ctx->vfs, rel_path, abs_path))
        ctx->all_ok = 0;
}

static int verify_dir(VFS *vfs, const char *base_dir, const char *rel_prefix) {
    (void)rel_prefix;
    VerifyCtx ctx = { vfs, base_dir, 1 };
    if (!platform_dir_foreach(base_dir, "", verify_visitor, &ctx))
        return 0;
    return ctx.all_ok;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file.pak> <source_dir>\n", argv[0]);
        return 1;
    }

    const char *pak_path  = argv[1];
    const char *src_dir   = argv[2];

    VFS *vfs = vfs_create();
    if (!vfs_mount_pak(vfs, pak_path)) {
        fprintf(stderr, "FAIL: cannot mount pak '%s'\n", pak_path);
        vfs_destroy(vfs);
        return 1;
    }

    int all_ok = verify_dir(vfs, src_dir, "");

    vfs_destroy(vfs);

    if (all_ok) {
        printf("\nAll files verified successfully!\n");
        return 0;
    } else {
        printf("\nVerification FAILED!\n");
        return 1;
    }
}
