#pragma once
#include <core/types.h>
#include <stdio.h>

#define VFS_MAX_MOUNTS  16
#define VFS_MAX_PATH    260
#define VFS_PAK_MAGIC   0x54415045 /* 'EPAT' little-endian = 'TAPE' */
#define VFS_PAK_VERSION 1

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
