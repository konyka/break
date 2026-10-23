#pragma once
/* Stage 4 scene editor Phase 3 Task 1: bounded one-level directory listing
 * — the plan's ONE additive PAL function (Global Constraints), filling the
 * repo's missing directory-enumeration primitive. POSIX: opendir/readdir
 * with lstat (no symlink following). Win32: FindFirstFileA under _WIN32.
 *
 * Byte caps below INCLUDE the NUL terminator (the
 * BREAK_EDITOR_NAME_CAPACITY convention): a path of PLATFORM_FS_PATH_CAPACITY
 * bytes or more is rejected, an entry name of PLATFORM_FS_NAME_CAPACITY
 * bytes or more cannot be represented and is skipped (see below).
 *
 * Names are handled byte-wise with '/' as the separator on every platform
 * (Windows APIs accept '/'); no encoding re-normalization is performed. */

#include <core/types.h>

#define PLATFORM_FS_PATH_CAPACITY 1024u
#define PLATFORM_FS_NAME_CAPACITY 256u

typedef struct PlatformDirEntry { char name[256]; bool is_dir; } PlatformDirEntry;

/* Lists one directory level, bounded. Returns false on OS error/overflow of path.
 * entries written until capacity; out_count = TOTAL entries found (may exceed capacity
 * => truncation is detectable). Not recursive. Does not follow symlinks (POSIX: lstat).
 *
 * Precise contract:
 * - "." and ".." are never reported.
 * - Entry order is the OS enumeration order — NOT sorted (sorting is the
 *   caller's job; break_editor_assets sorts dirs-first byte-wise).
 * - is_dir is the lstat classification on POSIX: a symlink (even to a
 *   directory) reports is_dir == false — symlinks are never followed.
 *   Entries whose lstat fails mid-listing (e.g. deleted concurrently) are
 *   skipped and not counted.
 * - An entry whose name does not fit PLATFORM_FS_NAME_CAPACITY, or whose
 *   joined stat path would reach PLATFORM_FS_PATH_CAPACITY, is skipped
 *   entirely: it is neither written nor counted in *out_count.
 * - entries may be NULL when capacity == 0 (a pure counting probe);
 *   entries == NULL with capacity > 0 is a contract violation → false.
 * - On a false return *out_count is 0 and the entries content is
 *   unspecified. */
bool platform_list_dir(const char *path, PlatformDirEntry *entries, u32 capacity, u32 *out_count);
