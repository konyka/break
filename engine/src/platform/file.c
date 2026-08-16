#include "platform/file.h"
#include <stdio.h>
#include <string.h>

#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    #include <direct.h>
#else
    #include <sys/stat.h>
    #include <dirent.h>
    #include <errno.h>
    #include <unistd.h>
#endif

static bool join_path(char *out, size_t cap,
                      const char *a, const char *b, const char *c) {
    int n;
    const char *prefix = (a && a[0]) ? a : NULL;
    if (b && b[0]) {
        if (c && c[0])
            n = prefix ? snprintf(out, cap, "%s/%s/%s", prefix, b, c)
                       : snprintf(out, cap, "%s/%s", b, c);
        else
            n = prefix ? snprintf(out, cap, "%s/%s", prefix, b)
                       : snprintf(out, cap, "%s", b);
    } else {
        if (c && c[0])
            n = prefix ? snprintf(out, cap, "%s/%s", prefix, c)
                       : snprintf(out, cap, "%s", c);
        else
            n = prefix ? snprintf(out, cap, "%s", prefix)
                       : snprintf(out, cap, ".");
    }
    return n >= 0 && (size_t)n < cap;
}

bool platform_mkdir(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    int rc = _mkdir(path);
    if (rc == 0) return true;
    return platform_file_is_directory(path);
#else
    if (mkdir(path, 0755) == 0) return true;
    if (errno == EEXIST)
        return platform_file_is_directory(path);
    return false;
#endif
}

bool platform_file_exists(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES;
#else
    struct stat st;
    return stat(path, &st) == 0;
#endif
}

bool platform_file_is_directory(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
#endif
}

bool platform_file_is_regular(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES &&
           !(attr & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
#endif
}

bool platform_file_size(const char *path, u64 *out_size) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &attr))
        return false;
    *out_size = ((u64)attr.nFileSizeHigh << 32) | (u64)attr.nFileSizeLow;
    return true;
#else
    struct stat st;
    if (stat(path, &st) != 0) return false;
    *out_size = (u64)st.st_size;
    return true;
#endif
}

u64 platform_file_mtime(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &attr))
        return 0;
    u64 ft = ((u64)attr.ftLastWriteTime.dwHighDateTime << 32) |
             (u64)attr.ftLastWriteTime.dwLowDateTime;
    /* FILETIME is 100-ns intervals since 1601-01-01. Convert to Unix seconds. */
    if (ft < 116444736000000000ULL) return 0;
    return (ft - 116444736000000000ULL) / 10000000ULL;
#else
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return (u64)st.st_mtime;
#endif
}

bool platform_file_remove(const char *path) {
    return remove(path) == 0;
}

bool platform_dir_foreach(const char *base_dir,
                          const char *rel_prefix,
                          PlatformDirVisitor visitor,
                          void *user) {
    char dir_path[1024];
    if (!join_path(dir_path, sizeof(dir_path), base_dir, rel_prefix, NULL))
        return false;

#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    char pattern[1024];
    if (!join_path(pattern, sizeof(pattern), dir_path, "", "*"))
        return false;

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h == INVALID_HANDLE_VALUE) return false;

    bool ok = true;
    do {
        if (fd.cFileName[0] == '.') continue;

        char rel[1024], abs[1024];
        if (!join_path(rel, sizeof(rel), rel_prefix, "", fd.cFileName) ||
            !join_path(abs, sizeof(abs), base_dir, rel, NULL)) {
            ok = false;
            break;
        }

        bool is_dir = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        visitor(rel, abs, is_dir, user);
        if (is_dir) {
            if (!platform_dir_foreach(base_dir, rel, visitor, user)) {
                ok = false;
                break;
            }
        }
    } while (FindNextFileA(h, &fd));

    FindClose(h);
    return ok;
#else
    DIR *d = opendir(dir_path);
    if (!d) return false;

    bool ok = true;
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (ent->d_name[0] == '.') continue;

        char rel[1024], abs[1024];
        if (!join_path(rel, sizeof(rel), rel_prefix, "", ent->d_name) ||
            !join_path(abs, sizeof(abs), base_dir, rel, NULL)) {
            ok = false;
            break;
        }

        bool is_dir = platform_file_is_directory(abs);
        visitor(rel, abs, is_dir, user);
        if (is_dir) {
            if (!platform_dir_foreach(base_dir, rel, visitor, user)) {
                ok = false;
                break;
            }
        }
    }
    closedir(d);
    return ok;
#endif
}
