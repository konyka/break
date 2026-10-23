/* platform_list_dir — contract documented in platform_fs.h (Stage 4 scene
 * editor Phase 3 Task 1; the plan's ONE additive PAL function).
 * POSIX: opendir/readdir + lstat (no symlink following). Win32:
 * FindFirstFileA — compiled but not exercisable on this lane; kept minimal
 * and correct by inspection. */

#if !defined(_WIN32)
/* glibc: the engine pins _POSIX_C_SOURCE=199309L, which hides lstat()
 * (filewatch.c R419 precedent). Defining _DEFAULT_SOURCE before any libc
 * header restores it; harmless where no pin exists (test inline copies). */
#define _DEFAULT_SOURCE
#endif

#include <platform/platform_fs.h>

#include <stdio.h>
#include <string.h>

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
                    entries[count].is_dir =
                        (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
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

#else /* POSIX */

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

bool platform_list_dir(const char *path, PlatformDirEntry *entries, u32 capacity, u32 *out_count) {
    if (!path || !out_count) return false;
    if (capacity > 0 && !entries) return false;
    *out_count = 0;
    usize path_len = strlen(path);
    if (path_len == 0 || path_len + 1 >= PLATFORM_FS_PATH_CAPACITY) return false;

    DIR *dir = opendir(path);
    if (!dir) return false;

    u32 count = 0;
    errno = 0;
    for (;;) {
        struct dirent *de = readdir(dir);
        if (!de) break; /* EOF or error — distinguished by errno below */
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
    int saved_errno = errno;
    closedir(dir);
    if (saved_errno != 0) { /* readdir error, not EOF */
        *out_count = 0;
        return false;
    }
    *out_count = count;
    return true;
}

#endif
