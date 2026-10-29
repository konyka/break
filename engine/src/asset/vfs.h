#pragma once
#include <core/types.h>
#include <stdio.h>

#define VFS_MAX_MOUNTS  16
#define VFS_MAX_PATH    260
#define VFS_PAK_MAGIC   0x54415045 /* 'EPAT' little-endian = 'TAPE' */
#define VFS_PAK_VERSION 1
#define VFS_MAX_PAK_ENTRIES 4096u
/* R397: DIR mounts read the whole file into memory; cap before calloc like
 * SCRIPT/HOTRELOAD paths so sparse multi-GB files cannot OOM the process. */
#define VFS_MAX_FILE_BYTES (128u << 20)  /* 128 MiB — fits 4K RGBA8 mip chains */

typedef struct VFS VFS;
typedef struct VFSFile VFSFile;

typedef enum {
    VFS_MOUNT_DIR,
    VFS_MOUNT_PAK,
} VFSMountType;

typedef struct {
    u32  name_hash;
    u32  name_offset;
    u32  data_offset;
    u32  size;
} PakEntry;

typedef struct {
    u32  magic;
    u32  version;
    u32  entry_count;
    u32  name_table_size;
} PakHeader;

struct VFSFile {
    u8   *data;
    usize size;
    usize pos;
};

struct VFS {
    struct {
        VFSMountType type;
        char         path[VFS_MAX_PATH];
        FILE        *pak_fp;
        PakHeader    pak_header;
        PakEntry    *pak_entries;
        char        *pak_names;
        /* Hash table for O(1) entry lookup (open-addressing, linear probing) */
        u32         *pak_hash_table;  /* maps hash → entry index, UINT32_MAX = empty */
        u32          pak_hash_size;   /* power-of-2 table size */
    } mounts[VFS_MAX_MOUNTS];
    u32 mount_count;
    /* R255: PAK mounts share one FILE* whose seek cursor is process-global; the
     * async loader runs multiple IO workers that call vfs_open concurrently, so a
     * lock serializes each PAK fseek+fread. Opaque to avoid leaking threading
     * headers into vfs.h consumers (allocated/typed as AsyncMutex in vfs.c). */
    void *pak_lock;
};

VFS    *vfs_create(void);
void    vfs_destroy(VFS *vfs);
bool    vfs_mount_dir(VFS *vfs, const char *dir_path);
bool    vfs_mount_pak(VFS *vfs, const char *pak_path);

VFSFile *vfs_open(VFS *vfs, const char *path);
usize    vfs_read(VFSFile *f, void *buf, usize size);
i32      vfs_getc(VFSFile *f);
bool     vfs_eof(VFSFile *f);
void     vfs_close(VFSFile *f);
usize    vfs_size(VFSFile *f);
u8      *vfs_read_all(VFS *vfs, const char *path, usize *out_size);

/* Visits every entry of every PAK mount that vfs_open can serve (entries
 * rejected at mount time are skipped), mounts in mount order, entries in
 * archive order. `path` is borrowed for the call only. Return false from
 * `fn` to stop. Returns the number of entries visited; 0 for NULL vfs/fn.
 * Same thread rules as vfs_mount_*: do not mount concurrently. */
typedef bool (*VFSPakEntryFn)(void *user, const char *path, u32 size);
usize vfs_enumerate_pak(VFS *vfs, VFSPakEntryFn fn, void *user);

/* One file to pack: `name` is the VFS path (non-empty, < VFS_MAX_PATH,
 * unique within the call); `data` may be NULL only when size == 0. */
typedef struct {
    const char *name;
    const void *data;
    u32         size;
} VFSPakSource;
/* Writes a version-VFS_PAK_VERSION archive readable by vfs_mount_pak,
 * entries in the given order. The archive is written to "<path>.tmp" and
 * renamed over `path` only after every byte is flushed, so a failure never
 * leaves a partial archive at `path`. false for NULL path, NULL sources with
 * count > 0, count > VFS_MAX_PAK_ENTRIES, invalid/duplicate names, a total
 * size that does not fit 32-bit offsets, or any I/O error. The replace is
 * rename(); on Windows that fails when `path` already exists (remove it
 * first there). */
bool vfs_pak_write(const char *path, const VFSPakSource *sources, u32 count);
