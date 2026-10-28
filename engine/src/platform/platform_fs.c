/* platform_fs — the repo's bounded filesystem PAL. Read side:
 * platform_list_dir (Stage 4 scene editor Phase 3 Task 1), POSIX
 * opendir/readdir + lstat (no symlink following), Win32 FindFirstFileA.
 * Write side (Stage 5 Phase A Task 3): PlatformAtomicWriter +
 * platform_mkdir + platform_file_size — contract and crash-safety ordering
 * documented in platform_fs.h; POSIX branch tested, Win32 branch
 * compile-only (kept minimal and correct by inspection). */

#if !defined(_WIN32)
/* glibc: the engine pins _POSIX_C_SOURCE=199309L, which hides lstat()
 * (filewatch.c R419 precedent). Defining _DEFAULT_SOURCE before any libc
 * header restores it; harmless where no pin exists (test inline copies). */
#define _DEFAULT_SOURCE
#endif

#include <platform/platform_fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Shared helper for the write-side PAL (Stage 5 Phase A Task 3): derives the
 * parent directory of a '/'-separated path (the platform_fs.h convention —
 * Windows APIs accept '/'). "name" → ".", "/name" → "/". commit() fsyncs
 * this directory so the rename itself is durable. */
static bool platform_fs_parent_dir(const char *path, char *out, usize cap) {
    const char *slash = strrchr(path, '/');
    usize n;
    if (!slash) {
        if (cap < 2) return false;
        out[0] = '.';
        out[1] = '\0';
        return true;
    }
    n = (usize)(slash - path);
    if (n == 0) n = 1; /* "/name" → "/" */
    if (n + 1 > cap) return false;
    memcpy(out, path, n);
    out[n] = '\0';
    return true;
}

#if defined(_WIN32)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

bool platform_list_dir(const char *path, PlatformDirEntry *entries, u32 capacity, u32 *out_count) {
    if (!path || !out_count) return false;
    if (capacity > 0 && !entries) return false;
    *out_count = 0;
    usize path_len = strlen(path);
    if (path_len == 0 || path_len + 1 >= PLATFORM_FS_PATH_CAPACITY) return false;

    /* FindFirstFileA accepts '/' separators. */
    char pattern[PLATFORM_FS_PATH_CAPACITY];
    int n = snprintf(pattern, sizeof(pattern), "%s/*", path);
    if (n < 0 || (usize)n >= sizeof(pattern)) return false;

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h == INVALID_HANDLE_VALUE) {
        /* An existing but empty directory yields ERROR_FILE_NOT_FOUND. */
        if (GetLastError() == ERROR_FILE_NOT_FOUND) return true;
        return false;
    }
    u32 count = 0;
    for (;;) {
        const char *name = fd.cFileName;
        if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0) {
            usize name_len = strlen(name);
            if (name_len > 0 && name_len < PLATFORM_FS_NAME_CAPACITY) {
                if (count < capacity) {
                    memcpy(entries[count].name, name, name_len + 1);
                    /* No-follow parity with the POSIX lstat branch:
                     * reparse points (directory symlinks, junctions) carry
                     * FILE_ATTRIBUTE_DIRECTORY but must report
                     * is_dir == false. */
                    entries[count].is_dir =
                        (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 &&
                        (fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) == 0;
                }
                count++;
            }
        }
        if (!FindNextFileA(h, &fd)) break;
    }
    DWORD err = GetLastError();
    FindClose(h);
    if (err != ERROR_NO_MORE_FILES) {
        *out_count = 0;
        return false;
    }
    *out_count = count;
    return true;
}

/* ---------------------------------------------------------------- */
/* Stage 5 Phase A Task 3: write-side PAL — Win32 branch.            */
/* Exercised by test_platform_fs_write on the Windows lanes.         */
/* CreateFile/WriteFile/FlushFileBuffers (the _fsync equivalent)/    */
/* MoveFileEx(REPLACE_EXISTING | WRITE_THROUGH). See platform_fs.h   */
/* for the contract.                                                 */
/* ---------------------------------------------------------------- */

struct PlatformAtomicWriter {
    HANDLE h; /* INVALID_HANDLE_VALUE once closed */
    char tmp_path[PLATFORM_FS_PATH_CAPACITY];
    char target_path[PLATFORM_FS_PATH_CAPACITY];
    char dir_path[PLATFORM_FS_PATH_CAPACITY];
    bool failed; /* sticky: a write/flush step failed */
};

PlatformAtomicWriter *platform_atomic_writer_open(const char *path) {
    if (!path) return NULL;
    usize path_len = strlen(path);
    /* "<path>.tmpXXXXXX" (10 bytes) + NUL must fit. */
    if (path_len == 0 || path_len + 10 + 1 > PLATFORM_FS_PATH_CAPACITY) return NULL;

    /* No mkstemp here: synthesize "<path>.tmpXXXXXX" candidates and let
     * CREATE_NEW arbitrate uniqueness (retry on collision). */
    DWORD seed = GetTickCount() ^ (GetCurrentProcessId() << 16);
    HANDLE h = INVALID_HANDLE_VALUE;
    char tmp[PLATFORM_FS_PATH_CAPACITY];
    for (int attempt = 0; attempt < 100; attempt++) {
        seed = seed * 1103515245u + 12345u; /* LCG; uniqueness from CREATE_NEW */
        int n = snprintf(tmp, sizeof(tmp), "%s.tmp%06lX", path,
                         (unsigned long)((seed >> 8) & 0xFFFFFFu));
        if (n < 0 || (usize)n >= sizeof(tmp)) return NULL;
        h = CreateFileA(tmp, GENERIC_WRITE, 0, NULL, CREATE_NEW,
                        FILE_ATTRIBUTE_NORMAL, NULL);
        if (h != INVALID_HANDLE_VALUE) break;
        if (GetLastError() != ERROR_FILE_EXISTS) return NULL;
    }
    if (h == INVALID_HANDLE_VALUE) return NULL;

    PlatformAtomicWriter *w = malloc(sizeof(*w));
    if (!w) {
        CloseHandle(h);
        DeleteFileA(tmp);
        return NULL;
    }
    w->h = h;
    memcpy(w->tmp_path, tmp, strlen(tmp) + 1);
    memcpy(w->target_path, path, path_len + 1);
    if (!platform_fs_parent_dir(path, w->dir_path, sizeof(w->dir_path))) {
        CloseHandle(h);
        DeleteFileA(tmp);
        free(w);
        return NULL;
    }
    w->failed = false;
    return w;
}

bool platform_atomic_writer_write(PlatformAtomicWriter *w, const void *data, usize len) {
    if (!w) return false;
    if (w->failed) return false; /* sticky failure state */
    if (!data) {
        if (len == 0) return true; /* NULL+0: empty write no-op */
        w->failed = true;
        return false;
    }
    const u8 *p = data;
    while (len > 0) {
        DWORD chunk = (len > (usize)0x40000000u) ? 0x40000000u : (DWORD)len;
        DWORD written = 0;
        if (!WriteFile(w->h, p, chunk, &written, NULL) || written == 0) {
            w->failed = true;
            return false;
        }
        p += written;
        len -= (usize)written;
    }
    return true;
}

bool platform_atomic_writer_commit(PlatformAtomicWriter *w) {
    if (!w) return false;
    /* Ordering (durability contract, platform_fs.h):
     *   FlushFileBuffers file → CloseHandle → MoveFileEx over target with
     *   MOVEFILE_WRITE_THROUGH. Windows has no directory fsync:
     *   FlushFileBuffers on a directory handle needs GENERIC_WRITE and
     *   fails with ERROR_ACCESS_DENIED for it, so the rename itself is made
     *   durable by WRITE_THROUGH (the call returns after the move is on
     *   disk). Any pre-rename failure deletes the tmp (target untouched);
     *   the handle is consumed on every outcome. */
    bool ok = !w->failed;
    if (ok && !FlushFileBuffers(w->h)) ok = false;
    if (!CloseHandle(w->h)) ok = false;
    w->h = INVALID_HANDLE_VALUE;
    if (ok && !MoveFileExA(w->tmp_path, w->target_path,
                           MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) ok = false;
    if (!ok) DeleteFileA(w->tmp_path); /* no residue; harmless if moved */
    free(w);
    return ok;
}

void platform_atomic_writer_abort(PlatformAtomicWriter *w) {
    if (!w) return; /* NULL no-op: idempotent in the free(NULL) sense */
    if (w->h != INVALID_HANDLE_VALUE) CloseHandle(w->h);
    DeleteFileA(w->tmp_path); /* harmless if already gone */
    free(w);
}

bool platform_mkdir(const char *path) {
    if (!path) return false;
    usize path_len = strlen(path);
    if (path_len == 0 || path_len + 1 > PLATFORM_FS_PATH_CAPACITY) return false;
    if (CreateDirectoryA(path, NULL)) return true;
    if (GetLastError() != ERROR_ALREADY_EXISTS) return false; /* single level */
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

bool platform_file_size(const char *path, u64 *out_size) {
    if (!path || !out_size) return false;
    usize path_len = strlen(path);
    if (path_len == 0 || path_len + 1 > PLATFORM_FS_PATH_CAPACITY) return false;
    WIN32_FILE_ATTRIBUTE_DATA d;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &d)) return false;
    if ((d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) return false;
    *out_size = ((u64)d.nFileSizeHigh << 32) | (u64)d.nFileSizeLow;
    return true;
}

#else /* POSIX */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

bool platform_list_dir(const char *path, PlatformDirEntry *entries, u32 capacity, u32 *out_count) {
    if (!path || !out_count) return false;
    if (capacity > 0 && !entries) return false;
    *out_count = 0;
    usize path_len = strlen(path);
    if (path_len == 0 || path_len + 1 >= PLATFORM_FS_PATH_CAPACITY) return false;

    DIR *dir = opendir(path);
    if (!dir) return false;

    u32 count = 0;
    int readdir_errno = 0;
    for (;;) {
        /* Per-iteration reset: a failed lstat above (skipped entry) leaves
         * errno set, and EOF readdir returns NULL without clearing it —
         * without the reset the EOF check below would misread the stale
         * lstat errno as a readdir error and fail the whole listing. */
        errno = 0;
        struct dirent *de = readdir(dir);
        if (!de) {
            readdir_errno = errno; /* 0 = EOF, otherwise a readdir error */
            break;
        }
        const char *name = de->d_name;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;
        usize name_len = strlen(name);
        if (name_len == 0 || name_len >= PLATFORM_FS_NAME_CAPACITY) continue;
        /* lstat needs the joined path; an over-long join cannot be
         * classified, so the entry is skipped entirely (not counted). */
        if (path_len + 1 + name_len + 1 > PLATFORM_FS_PATH_CAPACITY) continue;
        char full[PLATFORM_FS_PATH_CAPACITY];
        memcpy(full, path, path_len);
        full[path_len] = '/';
        memcpy(full + path_len + 1, name, name_len + 1);
        struct stat st;
        if (lstat(full, &st) != 0) continue; /* raced away / unreadable */
        if (count < capacity) {
            memcpy(entries[count].name, name, name_len + 1);
            entries[count].is_dir = S_ISDIR(st.st_mode) != 0;
        }
        count++;
    }
    closedir(dir);
    if (readdir_errno != 0) { /* genuine readdir error, not EOF */
        *out_count = 0;
        return false;
    }
    *out_count = count;
    return true;
}

/* ---------------------------------------------------------------- */
/* Stage 5 Phase A Task 3: write-side PAL — POSIX branch (tested).   */
/* Contract and crash-safety ordering: platform_fs.h.                */
/* ---------------------------------------------------------------- */

struct PlatformAtomicWriter {
    int fd; /* -1 once closed */
    char tmp_path[PLATFORM_FS_PATH_CAPACITY];   /* "<path>.tmpXXXXXX" */
    char target_path[PLATFORM_FS_PATH_CAPACITY];
    char dir_path[PLATFORM_FS_PATH_CAPACITY];   /* commit step 4 fsync */
    bool failed; /* sticky: a write/fsync step failed */
};

PlatformAtomicWriter *platform_atomic_writer_open(const char *path) {
    if (!path) return NULL;
    usize path_len = strlen(path);
    /* mkstemp needs "<path>.tmpXXXXXX" (10 bytes) + NUL to fit. */
    if (path_len == 0 || path_len + 10 + 1 > PLATFORM_FS_PATH_CAPACITY) return NULL;

    char tmp[PLATFORM_FS_PATH_CAPACITY];
    memcpy(tmp, path, path_len);
    memcpy(tmp + path_len, ".tmpXXXXXX", 11); /* includes the NUL */
    int fd = mkstemp(tmp); /* 0600, in the SAME directory as path */
    if (fd < 0) return NULL;

    PlatformAtomicWriter *w = malloc(sizeof(*w));
    if (!w) {
        close(fd);
        unlink(tmp);
        return NULL;
    }
    w->fd = fd;
    memcpy(w->tmp_path, tmp, path_len + 11);
    memcpy(w->target_path, path, path_len + 1);
    if (!platform_fs_parent_dir(path, w->dir_path, sizeof(w->dir_path))) {
        close(fd);
        unlink(tmp);
        free(w);
        return NULL;
    }
    w->failed = false;
    return w;
}

bool platform_atomic_writer_write(PlatformAtomicWriter *w, const void *data, usize len) {
    if (!w) return false;
    if (w->failed) return false; /* sticky failure state */
    if (!data) {
        if (len == 0) return true; /* NULL+0: empty write no-op */
        w->failed = true;
        return false;
    }
    const u8 *p = data;
    while (len > 0) {
        ssize_t n = write(w->fd, p, len);
        if (n < 0) {
            if (errno == EINTR) continue;
            w->failed = true;
            return false;
        }
        p += (usize)n;
        len -= (usize)n;
    }
    return true;
}

bool platform_atomic_writer_commit(PlatformAtomicWriter *w) {
    if (!w) return false;
    /* Ordering (durability contract, platform_fs.h):
     *   fsync file → close → rename over target → fsync directory.
     * Any pre-rename failure unlinks the tmp (target untouched); a failed
     * writer never renames. The handle is consumed on every outcome. */
    bool ok = !w->failed;
    if (ok && fsync(w->fd) != 0) ok = false;
    if (close(w->fd) != 0) ok = false; /* closed exactly once, either way */
    w->fd = -1;
    if (ok && rename(w->tmp_path, w->target_path) != 0) ok = false;
    if (ok) {
        int dfd = open(w->dir_path, O_RDONLY);
        if (dfd < 0) {
            ok = false;
        } else {
            if (fsync(dfd) != 0) ok = false;
            close(dfd);
        }
    }
    if (!ok) unlink(w->tmp_path); /* no residue; ENOENT post-rename is fine */
    free(w);
    return ok;
}

void platform_atomic_writer_abort(PlatformAtomicWriter *w) {
    if (!w) return; /* NULL no-op: idempotent in the free(NULL) sense */
    if (w->fd >= 0) close(w->fd);
    unlink(w->tmp_path); /* harmless if already gone */
    free(w);
}

bool platform_mkdir(const char *path) {
    if (!path) return false;
    usize path_len = strlen(path);
    if (path_len == 0 || path_len + 1 > PLATFORM_FS_PATH_CAPACITY) return false;
    if (mkdir(path, 0755) == 0) return true;
    if (errno != EEXIST) return false; /* e.g. ENOENT: single level only */
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode) != 0;
}

bool platform_file_size(const char *path, u64 *out_size) {
    if (!path || !out_size) return false;
    usize path_len = strlen(path);
    if (path_len == 0 || path_len + 1 > PLATFORM_FS_PATH_CAPACITY) return false;
    struct stat st;
    if (stat(path, &st) != 0) return false; /* missing/unreadable */
    if (!S_ISREG(st.st_mode)) return false; /* e.g. a directory */
    *out_size = (u64)st.st_size;
    return true;
}

#endif
