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

/* ---------------------------------------------------------------- */
/* Stage 5 Phase A Task 3: write-side PAL. POSIX branch fully        */
/* tested; Win32 branch compile-only (_WIN32) — correct by           */
/* inspection only, no Windows lane exercises it in this repo state  */
/* (the platform_list_dir precedent).                                */
/*                                                                   */
/* Crash-safety ordering of a commit (the durability contract):      */
/*   1. fsync the tmp file (payload bytes durable)                   */
/*   2. close the tmp file                                           */
/*   3. rename the tmp over the target (atomic same-filesystem       */
/*      replacement — the tmp lives in the target's directory)       */
/*   4. fsync the containing directory (the rename itself durable)   */
/* Any failed step → commit returns false. A failure before step 3   */
/* leaves the target untouched. The tmp is unlinked on every failure */
/* whose containing directory still permits it — a write-denied      */
/* (e.g. 0444) directory denies the cleanup unlink too (POSIX        */
/* reality): there the fail-closed guarantees are false returned,    */
/* target untouched, handle consumed, and the write path already     */
/* fails at open (mkstemp EACCES) so no tmp ever exists.             */
/*                                                                   */
/* Handle discipline: commit and abort CONSUME the writer (it is     */
/* freed) on every outcome — a consumed handle must not be used      */
/* again; callers set it to NULL. abort(NULL) is a safe no-op and    */
/* commit(NULL) returns false, so the consume-then-NULL idiom is     */
/* idempotent in the free(NULL) sense. A failed write latches the    */
/* writer into a sticky failure state: later writes return false     */
/* and commit degenerates to abort (false, no rename).               */
/*                                                                   */
/* POSIX: the committed file carries mkstemp's 0600 mode; callers    */
/* needing other modes chmod after commit. platform_file_size        */
/* follows symlinks (stat(2)) — a symlink to a regular file reports  */
/* the target's size. platform_mkdir uses mode 0755. Paths bounded   */
/* by PLATFORM_FS_PATH_CAPACITY (the ".tmpXXXXXX" suffix must fit).  */
/* ---------------------------------------------------------------- */

/* platform_fs.h additions — POSIX tested; Win32 branch compile-only (_WIN32):
 * CreateFile/WriteFile/_fsync-equivalent (FlushFileBuffers)/MoveFileEx(REPLACE_EXISTING). */

/* Opens "<path>.tmpXXXXXX" in the SAME directory as path (rename atomicity requires
 * same filesystem). Only ONE writer per instance; not thread-safe. */
typedef struct PlatformAtomicWriter PlatformAtomicWriter;
PlatformAtomicWriter *platform_atomic_writer_open(const char *path);     /* NULL on error */
bool platform_atomic_writer_write(PlatformAtomicWriter *w, const void *data, usize len); /* false → abort state */
bool platform_atomic_writer_commit(PlatformAtomicWriter *w);  /* fsync file, close, rename over path,
                                                                 fsync directory, free writer */
void platform_atomic_writer_abort(PlatformAtomicWriter *w);   /* close + unlink tmp + free; idempotent */

bool platform_mkdir(const char *path);                        /* single level; true if exists-as-dir */
bool platform_file_size(const char *path, u64 *out_size);     /* false if missing/not-regular */
