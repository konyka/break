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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void platform_atomic_diagnostic_init(PlatformAtomicWriterDiagnostic *diagnostic,
                                            const char *path) {
    if (!diagnostic) return;
    memset(diagnostic, 0, sizeof(*diagnostic));
    if (path) {
        usize length = strlen(path);
        if (length < PLATFORM_FS_PATH_CAPACITY) {
            memcpy(diagnostic->target_path, path, length + 1u);
        }
    }
}

static void platform_atomic_diagnostic_temporary(PlatformAtomicWriterDiagnostic *diagnostic,
                                                 const char *path) {
    if (!diagnostic || !path) return;
    usize length = strlen(path);
    if (length < PLATFORM_FS_PATH_CAPACITY)
        memcpy(diagnostic->temporary_path, path, length + 1u);
}

static void platform_atomic_diagnostic_record(PlatformAtomicWriterDiagnostic *diagnostic,
                                              const char *step, i64 raw_result,
                                              u64 os_error, int crt_error,
                                              u64 got, u64 expected) {
    if (!diagnostic || diagnostic->step) return;
    diagnostic->step = step;
    diagnostic->raw_result = raw_result;
    diagnostic->os_error = os_error;
    diagnostic->crt_error = crt_error;
    diagnostic->got = got;
    diagnostic->expected = expected;
}

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
    PlatformAtomicWriterDiagnostic *diagnostic;
    bool error_saved;
    DWORD os_error;
    int crt_error;
};

static void platform_atomic_win32_error(PlatformAtomicWriter *w, const char *step,
                                        i64 raw_result, DWORD os_error, int crt_error,
                                        u64 got, u64 expected) {
    if (!w->error_saved) {
        w->error_saved = true;
        w->os_error = os_error;
        w->crt_error = crt_error;
    }
    platform_atomic_diagnostic_record(w->diagnostic, step, raw_result,
                                      (u64)os_error, crt_error, got, expected);
}

PlatformAtomicWriter *platform_atomic_writer_open_diagnostic(
    const char *path, PlatformAtomicWriterDiagnostic *diagnostic) {
    platform_atomic_diagnostic_init(diagnostic, path);
    if (!path) {
        platform_atomic_diagnostic_record(diagnostic, "validate", -1, 0, 0, 0, 0);
        return NULL;
    }
    usize path_len = strlen(path);
    /* "<path>.tmpXXXXXX" (10 bytes) + NUL must fit. */
    if (path_len == 0 || path_len + 10 + 1 > PLATFORM_FS_PATH_CAPACITY) {
        platform_atomic_diagnostic_record(diagnostic, "validate", -1, 0, 0, 0, 0);
        return NULL;
    }

    /* No mkstemp here: synthesize "<path>.tmpXXXXXX" candidates and let
     * CREATE_NEW arbitrate uniqueness (retry on collision). */
    DWORD seed = GetTickCount() ^ (GetCurrentProcessId() << 16);
    HANDLE h = INVALID_HANDLE_VALUE;
    DWORD last_error = ERROR_SUCCESS;
    int last_crt_error = 0;
    char tmp[PLATFORM_FS_PATH_CAPACITY];
    for (int attempt = 0; attempt < 100; attempt++) {
        seed = seed * 1103515245u + 12345u; /* LCG; uniqueness from CREATE_NEW */
        int n = snprintf(tmp, sizeof(tmp), "%s.tmp%06lX", path,
                         (unsigned long)((seed >> 8) & 0xFFFFFFu));
        if (n < 0 || (usize)n >= sizeof(tmp)) {
            int saved_errno = errno;
            platform_atomic_diagnostic_record(diagnostic, "snprintf", (i64)n,
                                              0, saved_errno, 0, 0);
            errno = saved_errno;
            return NULL;
        }
        platform_atomic_diagnostic_temporary(diagnostic, tmp);
        h = CreateFileA(tmp, GENERIC_WRITE, 0, NULL, CREATE_NEW,
                        FILE_ATTRIBUTE_NORMAL, NULL);
        last_error = GetLastError();
        last_crt_error = errno;
        if (h != INVALID_HANDLE_VALUE) break;
        if (last_error != ERROR_FILE_EXISTS) {
            platform_atomic_diagnostic_record(diagnostic, "CreateFileA", -1,
                                              (u64)last_error, last_crt_error, 0, 0);
            SetLastError(last_error);
            errno = last_crt_error;
            return NULL;
        }
    }
    if (h == INVALID_HANDLE_VALUE) {
        platform_atomic_diagnostic_record(diagnostic, "CreateFileA", -1,
                                          (u64)last_error, last_crt_error, 0, 0);
        SetLastError(last_error);
        errno = last_crt_error;
        return NULL;
    }

    PlatformAtomicWriter *w = malloc(sizeof(*w));
    if (!w) {
        int saved_errno = errno;
        DWORD saved_error = GetLastError();
        platform_atomic_diagnostic_record(diagnostic, "malloc", 0, 0,
                                          saved_errno, 0, 0);
        BOOL close_result = CloseHandle(h);
        DWORD close_error = GetLastError();
        int close_errno = errno;
        if (!close_result)
            platform_atomic_diagnostic_record(diagnostic, "CloseHandle",
                                              (i64)close_result, (u64)close_error,
                                              close_errno, 0, 0);
        BOOL delete_result = DeleteFileA(tmp);
        DWORD delete_error = GetLastError();
        int delete_errno = errno;
        if (!delete_result)
            platform_atomic_diagnostic_record(diagnostic, "DeleteFileA",
                                              (i64)delete_result, (u64)delete_error,
                                              delete_errno, 0, 0);
        SetLastError(saved_error);
        errno = saved_errno;
        return NULL;
    }
    w->h = h;
    w->diagnostic = diagnostic;
    w->error_saved = false;
    w->os_error = ERROR_SUCCESS;
    w->crt_error = 0;
    memcpy(w->tmp_path, tmp, strlen(tmp) + 1);
    memcpy(w->target_path, path, path_len + 1);
    if (!platform_fs_parent_dir(path, w->dir_path, sizeof(w->dir_path))) {
        DWORD saved_error = GetLastError();
        int saved_errno = errno;
        platform_atomic_diagnostic_record(diagnostic, "parent_dir", 0, 0, 0, 0, 0);
        BOOL close_result = CloseHandle(h);
        DWORD close_error = GetLastError();
        int close_errno = errno;
        if (!close_result)
            platform_atomic_diagnostic_record(diagnostic, "CloseHandle",
                                              (i64)close_result, (u64)close_error,
                                              close_errno, 0, 0);
        BOOL delete_result = DeleteFileA(tmp);
        DWORD delete_error = GetLastError();
        int delete_errno = errno;
        if (!delete_result)
            platform_atomic_diagnostic_record(diagnostic, "DeleteFileA",
                                              (i64)delete_result, (u64)delete_error,
                                              delete_errno, 0, 0);
        free(w);
        SetLastError(saved_error);
        errno = saved_errno;
        return NULL;
    }
    w->failed = false;
    return w;
}

PlatformAtomicWriter *platform_atomic_writer_open(const char *path) {
    return platform_atomic_writer_open_diagnostic(path, NULL);
}

bool platform_atomic_writer_write(PlatformAtomicWriter *w, const void *data, usize len) {
    if (!w) return false;
    if (w->failed) return false; /* sticky failure state */
    if (!data) {
        if (len == 0) return true; /* NULL+0: empty write no-op */
        platform_atomic_win32_error(w, "argument", 0, 0, 0, 0, (u64)len);
        w->failed = true;
        return false;
    }
    const u8 *p = data;
    while (len > 0) {
        DWORD chunk = (len > (usize)0x40000000u) ? 0x40000000u : (DWORD)len;
        DWORD written = 0;
        BOOL result = WriteFile(w->h, p, chunk, &written, NULL);
        DWORD write_error = GetLastError();
        int write_errno = errno;
        if (!result || written == 0) {
            platform_atomic_win32_error(w, "WriteFile", (i64)result, write_error,
                                        write_errno, (u64)written, (u64)chunk);
            w->failed = true;
            SetLastError(write_error);
            errno = write_errno;
            return false;
        }
        p += written;
        len -= (usize)written;
    }
    return true;
}

PlatformAtomicCommitResult platform_atomic_writer_commit_status(PlatformAtomicWriter *w) {
    if (!w) return PLATFORM_ATOMIC_NOT_COMMITTED_TARGET_UNCHANGED;
    bool ok = !w->failed;
    if (ok) {
        BOOL result = FlushFileBuffers(w->h);
        DWORD flush_error = GetLastError();
        int flush_errno = errno;
        if (!result) {
            platform_atomic_win32_error(w, "FlushFileBuffers", (i64)result,
                                        flush_error, flush_errno, 0, 0);
            ok = false;
        }
    }
    BOOL close_result = CloseHandle(w->h);
    DWORD close_error = GetLastError();
    int close_errno = errno;
    if (!close_result) {
        platform_atomic_win32_error(w, "CloseHandle", (i64)close_result,
                                    close_error, close_errno, 0, 0);
        ok = false;
    }
    w->h = INVALID_HANDLE_VALUE;
    if (ok) {
        BOOL result = MoveFileExA(w->tmp_path, w->target_path,
                                  MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
        DWORD move_error = GetLastError();
        int move_errno = errno;
        if (!result) {
            platform_atomic_win32_error(w, "MoveFileExA", (i64)result,
                                        move_error, move_errno, 0, 0);
            ok = false;
        }
    }
    if (!ok) {
        BOOL result = DeleteFileA(w->tmp_path);
        DWORD delete_error = GetLastError();
        int delete_errno = errno;
        if (!result)
            platform_atomic_win32_error(w, "DeleteFileA", (i64)result,
                                        delete_error, delete_errno, 0, 0);
    }
    bool restore_error = w->error_saved;
    DWORD saved_error = w->os_error;
    int saved_errno = w->crt_error;
    free(w);
    if (restore_error) {
        SetLastError(saved_error);
        errno = saved_errno;
    }
    return ok ? PLATFORM_ATOMIC_SUCCESS_DURABLE
              : PLATFORM_ATOMIC_NOT_COMMITTED_TARGET_UNCHANGED;
}

bool platform_atomic_writer_commit(PlatformAtomicWriter *w) {
    return platform_atomic_writer_commit_status(w) == PLATFORM_ATOMIC_SUCCESS_DURABLE;
}

void platform_atomic_writer_abort(PlatformAtomicWriter *w) {
    if (!w) return; /* NULL no-op: idempotent in the free(NULL) sense */
    if (w->h != INVALID_HANDLE_VALUE) {
        BOOL result = CloseHandle(w->h);
        DWORD close_error = GetLastError();
        int close_errno = errno;
        if (!result)
            platform_atomic_win32_error(w, "CloseHandle", (i64)result,
                                        close_error, close_errno, 0, 0);
    }
    BOOL delete_result = DeleteFileA(w->tmp_path); /* harmless if already gone */
    DWORD delete_error = GetLastError();
    int delete_errno = errno;
    if (!delete_result)
        platform_atomic_win32_error(w, "DeleteFileA", (i64)delete_result,
                                    delete_error, delete_errno, 0, 0);
    bool restore_error = w->error_saved;
    DWORD saved_error = w->os_error;
    int saved_errno = w->crt_error;
    free(w);
    if (restore_error) {
        SetLastError(saved_error);
        errno = saved_errno;
    }
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
    PlatformAtomicWriterDiagnostic *diagnostic;
    bool error_saved;
    int crt_error;
};

static void platform_atomic_posix_error(PlatformAtomicWriter *w, const char *step,
                                        i64 raw_result, int crt_error,
                                        u64 got, u64 expected) {
    if (!w->error_saved) {
        w->error_saved = true;
        w->crt_error = crt_error;
    }
    platform_atomic_diagnostic_record(w->diagnostic, step, raw_result,
                                      0, crt_error, got, expected);
}

PlatformAtomicWriter *platform_atomic_writer_open_diagnostic(
    const char *path, PlatformAtomicWriterDiagnostic *diagnostic) {
    platform_atomic_diagnostic_init(diagnostic, path);
    if (!path) {
        platform_atomic_diagnostic_record(diagnostic, "validate", -1, 0, 0, 0, 0);
        return NULL;
    }
    usize path_len = strlen(path);
    /* mkstemp needs "<path>.tmpXXXXXX" (10 bytes) + NUL to fit. */
    if (path_len == 0 || path_len + 10 + 1 > PLATFORM_FS_PATH_CAPACITY) {
        platform_atomic_diagnostic_record(diagnostic, "validate", -1, 0, 0, 0, 0);
        return NULL;
    }

    char tmp[PLATFORM_FS_PATH_CAPACITY];
    memcpy(tmp, path, path_len);
    memcpy(tmp + path_len, ".tmpXXXXXX", 11); /* includes the NUL */
    int fd = mkstemp(tmp); /* 0600, in the SAME directory as path */
    int mkstemp_errno = errno;
    platform_atomic_diagnostic_temporary(diagnostic, tmp);
    if (fd < 0) {
        platform_atomic_diagnostic_record(diagnostic, "mkstemp", (i64)fd,
                                          0, mkstemp_errno, 0, 0);
        errno = mkstemp_errno;
        return NULL;
    }

    PlatformAtomicWriter *w = malloc(sizeof(*w));
    if (!w) {
        int saved_errno = errno;
        platform_atomic_diagnostic_record(diagnostic, "malloc", 0, 0,
                                          saved_errno, 0, 0);
        int close_result = close(fd);
        int close_errno = errno;
        if (close_result != 0)
            platform_atomic_diagnostic_record(diagnostic, "close", (i64)close_result,
                                              0, close_errno, 0, 0);
        int unlink_result = unlink(tmp);
        int unlink_errno = errno;
        if (unlink_result != 0)
            platform_atomic_diagnostic_record(diagnostic, "unlink", (i64)unlink_result,
                                              0, unlink_errno, 0, 0);
        errno = saved_errno;
        return NULL;
    }
    w->fd = fd;
    w->diagnostic = diagnostic;
    w->error_saved = false;
    w->crt_error = 0;
    memcpy(w->tmp_path, tmp, path_len + 11);
    memcpy(w->target_path, path, path_len + 1);
    if (!platform_fs_parent_dir(path, w->dir_path, sizeof(w->dir_path))) {
        int saved_errno = errno;
        platform_atomic_diagnostic_record(diagnostic, "parent_dir", 0, 0, 0, 0, 0);
        int close_result = close(fd);
        int close_errno = errno;
        if (close_result != 0)
            platform_atomic_diagnostic_record(diagnostic, "close", (i64)close_result,
                                              0, close_errno, 0, 0);
        int unlink_result = unlink(tmp);
        int unlink_errno = errno;
        if (unlink_result != 0)
            platform_atomic_diagnostic_record(diagnostic, "unlink", (i64)unlink_result,
                                              0, unlink_errno, 0, 0);
        free(w);
        errno = saved_errno;
        return NULL;
    }
    w->failed = false;
    return w;
}

PlatformAtomicWriter *platform_atomic_writer_open(const char *path) {
    return platform_atomic_writer_open_diagnostic(path, NULL);
}

bool platform_atomic_writer_write(PlatformAtomicWriter *w, const void *data, usize len) {
    if (!w) return false;
    if (w->failed) return false; /* sticky failure state */
    if (!data) {
        if (len == 0) return true; /* NULL+0: empty write no-op */
        platform_atomic_posix_error(w, "argument", 0, 0, 0, (u64)len);
        w->failed = true;
        return false;
    }
    const u8 *p = data;
    while (len > 0) {
        ssize_t n = write(w->fd, p, len);
        int write_errno = errno;
        if (n < 0) {
            if (write_errno == EINTR) continue;
            platform_atomic_posix_error(w, "write", (i64)n, write_errno, 0, (u64)len);
            w->failed = true;
            errno = write_errno;
            return false;
        }
        p += (usize)n;
        len -= (usize)n;
    }
    return true;
}

PlatformAtomicCommitResult platform_atomic_writer_commit_status(PlatformAtomicWriter *w) {
    if (!w) return PLATFORM_ATOMIC_NOT_COMMITTED_TARGET_UNCHANGED;
    bool ok = !w->failed;
    bool renamed = false;
    if (ok) {
        int result = fsync(w->fd);
        int fsync_errno = errno;
        if (result != 0) {
            platform_atomic_posix_error(w, "fsync", (i64)result, fsync_errno, 0, 0);
            ok = false;
        }
    }
    int close_result = close(w->fd);
    int close_errno = errno;
    if (close_result != 0) {
        platform_atomic_posix_error(w, "close", (i64)close_result, close_errno, 0, 0);
        ok = false;
    }
    w->fd = -1;
    if (ok) {
        int result = rename(w->tmp_path, w->target_path);
        int rename_errno = errno;
        if (result == 0) {
            renamed = true;
        } else {
            platform_atomic_posix_error(w, "rename", (i64)result, rename_errno, 0, 0);
            ok = false;
        }
    }
    if (ok) {
        int dfd = open(w->dir_path, O_RDONLY);
        int open_errno = errno;
        if (dfd < 0) {
            platform_atomic_posix_error(w, "open(dir)", (i64)dfd, open_errno, 0, 0);
            ok = false;
        } else {
            int fsync_result = fsync(dfd);
            int fsync_errno = errno;
            if (fsync_result != 0) {
                platform_atomic_posix_error(w, "fsync(dir)", (i64)fsync_result,
                                            fsync_errno, 0, 0);
                ok = false;
            }
            int dir_close_result = close(dfd);
            int dir_close_errno = errno;
            if (dir_close_result != 0 && !ok)
                platform_atomic_posix_error(w, "close(dir)", (i64)dir_close_result,
                                            dir_close_errno, 0, 0);
        }
    }
    if (!ok) {
        int result = unlink(w->tmp_path);
        int unlink_errno = errno;
        if (result != 0)
            platform_atomic_posix_error(w, "unlink", (i64)result, unlink_errno, 0, 0);
    }
    bool restore_error = w->error_saved;
    int saved_errno = w->crt_error;
    free(w);
    if (restore_error) errno = saved_errno;
    if (renamed) {
        return ok ? PLATFORM_ATOMIC_SUCCESS_DURABLE
                  : PLATFORM_ATOMIC_RENAMED_DURABILITY_UNKNOWN;
    }
    return PLATFORM_ATOMIC_NOT_COMMITTED_TARGET_UNCHANGED;
}

bool platform_atomic_writer_commit(PlatformAtomicWriter *w) {
    return platform_atomic_writer_commit_status(w) == PLATFORM_ATOMIC_SUCCESS_DURABLE;
}

void platform_atomic_writer_abort(PlatformAtomicWriter *w) {
    if (!w) return; /* NULL no-op: idempotent in the free(NULL) sense */
    if (w->fd >= 0) {
        int result = close(w->fd);
        int close_errno = errno;
        if (result != 0)
            platform_atomic_posix_error(w, "close", (i64)result, close_errno, 0, 0);
    }
    int unlink_result = unlink(w->tmp_path); /* harmless if already gone */
    int unlink_errno = errno;
    if (unlink_result != 0)
        platform_atomic_posix_error(w, "unlink", (i64)unlink_result, unlink_errno, 0, 0);
    bool restore_error = w->error_saved;
    int saved_errno = w->crt_error;
    free(w);
    if (restore_error) errno = saved_errno;
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
