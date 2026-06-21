#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
    #define NOMINMAX
    #endif
    #include <windows.h>
#else
    #include <dirent.h>
    #include <sys/stat.h>
#endif

typedef unsigned int       u32;
typedef unsigned long long u64;
typedef unsigned char      u8;

#define MAX_ENTRIES   4096
#define MAX_PATH_LEN  260
#define PAK_MAGIC     0x54415045

static u32 fnv1a(const char *str) {
    u32 hash = 2166136261u;
    while (*str) {
        hash ^= (u8)*str++;
        hash *= 16777619u;
    }
    return hash;
}

typedef struct {
    u32 name_hash;
    u32 name_offset;
    u32 data_offset;
    u32 size;
} PakEntry;

static char    g_names[MAX_ENTRIES * MAX_PATH_LEN];
static u32     g_name_size;
static PakEntry g_entries[MAX_ENTRIES];
static u32     g_entry_count;
static char    g_paths[MAX_ENTRIES][MAX_PATH_LEN];

/* Query file size (64-bit safe). Returns 0 on failure. */
static int get_file_size(const char *path, u64 *out_size) {
#ifdef _WIN32
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &attr))
        return 0;
    *out_size = ((u64)attr.nFileSizeHigh << 32) | (u64)attr.nFileSizeLow;
    return 1;
#else
    struct stat st;
    if (stat(path, &st) != 0)
        return 0;
    *out_size = (u64)st.st_size;
    return 1;
#endif
}

/* Check whether a path is a directory. */
static int is_directory(const char *path) {
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES &&
           (attr & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
#endif
}

/* Check whether a path is a regular file. */
static int is_regular_file(const char *path) {
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES &&
           !(attr & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
#endif
}

static void add_file(const char *rel_path, const char *abs_path) {
    if (g_entry_count >= MAX_ENTRIES) return;

    u64 sz;
    if (!get_file_size(abs_path, &sz)) return;

    if (sz > 0xFFFFFFFFull) {
        fprintf(stderr, "WARN: '%s' exceeds 4 GB limit, skipping\n", abs_path);
        return;
    }

    u32 idx = g_entry_count++;
    strncpy(g_paths[idx], abs_path, MAX_PATH_LEN - 1);
    g_paths[idx][MAX_PATH_LEN - 1] = '\0';

    u32 name_off = g_name_size;
    u32 name_len = (u32)strlen(rel_path) + 1;
    memcpy(g_names + g_name_size, rel_path, name_len);
    g_name_size += name_len;

    g_entries[idx].name_hash = fnv1a(rel_path);
    g_entries[idx].name_offset = name_off;
    g_entries[idx].size = (u32)sz;
    g_entries[idx].data_offset = 0;
}

static void scan_dir(const char *base_dir, const char *rel_prefix) {
#ifdef _WIN32
    char pattern[1024];
    if (rel_prefix[0])
        snprintf(pattern, sizeof(pattern), "%s/%s/*", base_dir, rel_prefix);
    else
        snprintf(pattern, sizeof(pattern), "%s/*", base_dir);

    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(pattern, &fd);
    if (hFind == INVALID_HANDLE_VALUE) return;

    do {
        if (fd.cFileName[0] == '.') continue;

        char rel[1024];
        if (rel_prefix[0])
            snprintf(rel, sizeof(rel), "%s/%s", rel_prefix, fd.cFileName);
        else
            snprintf(rel, sizeof(rel), "%s", fd.cFileName);

        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", base_dir, rel);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            scan_dir(base_dir, rel);
        } else {
            add_file(rel, full);
        }
    } while (FindNextFileA(hFind, &fd));

    FindClose(hFind);
#else
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", base_dir, rel_prefix);

    DIR *d = opendir(path);
    if (!d) return;

    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (ent->d_name[0] == '.') continue;

        char rel[1024];
        if (rel_prefix[0])
            snprintf(rel, sizeof(rel), "%s/%s", rel_prefix, ent->d_name);
        else
            snprintf(rel, sizeof(rel), "%s", ent->d_name);

        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", base_dir, rel);

        struct stat st;
        if (stat(full, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                scan_dir(base_dir, rel);
            } else if (S_ISREG(st.st_mode)) {
                add_file(rel, full);
            }
        }
    }
    closedir(d);
#endif
}

/* Write a single file's data to the output stream.
 * On Windows, uses memory-mapped I/O for zero-copy. */
static int write_file_data(const char *path, u32 size, FILE *out) {
    if (size == 0) return 1; /* nothing to write for empty files */

#ifdef _WIN32
    HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "ERROR: cannot open '%s' (err %lu)\n", path,
                GetLastError());
        return 0;
    }

    HANDLE hMap = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (!hMap) {
        fprintf(stderr, "ERROR: cannot create file mapping for '%s' (err %lu)\n",
                path, GetLastError());
        CloseHandle(hFile);
        return 0;
    }

    const void *data = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
    if (!data) {
        fprintf(stderr, "ERROR: cannot map view for '%s' (err %lu)\n",
                path, GetLastError());
        CloseHandle(hMap);
        CloseHandle(hFile);
        return 0;
    }

    fwrite(data, 1, size, out);

    UnmapViewOfFile(data);
    CloseHandle(hMap);
    CloseHandle(hFile);
    return 1;
#else
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "ERROR: cannot read '%s'\n", path);
        return 0;
    }
    u8 buf[65536];
    u32 remaining = size;
    while (remaining > 0) {
        u32 chunk = remaining > sizeof(buf) ? (u32)sizeof(buf) : remaining;
        size_t nread = fread(buf, 1, chunk, fp);
        if (nread < chunk) {
            fprintf(stderr, "ERROR: short read on '%s'\n", path);
            fclose(fp);
            return 0;
        }
        fwrite(buf, 1, chunk, out);
        remaining -= chunk;
    }
    fclose(fp);
    return 1;
#endif
}

/* Extract the filename component from a path, handling both '/' and '\'. */
static const char *basename_of(const char *path) {
    const char *slash  = strrchr(path, '/');
    const char *bslash = strrchr(path, '\\');
    const char *name   = slash;
    if (bslash && (!name || bslash > name))
        name = bslash;
    return name ? name + 1 : path;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <output.pak> <input_dir_or_file> [...]\n", argv[0]);
        return 1;
    }

    const char *output = argv[1];

    for (int i = 2; i < argc; i++) {
        if (is_directory(argv[i])) {
            scan_dir(argv[i], "");
        } else if (is_regular_file(argv[i])) {
            const char *name = basename_of(argv[i]);
            add_file(name, argv[i]);
        } else {
            fprintf(stderr, "WARN: skipping '%s' (not found)\n", argv[i]);
        }
    }

    if (g_entry_count == 0) {
        fprintf(stderr, "ERROR: no files to pack\n");
        return 1;
    }

    u32 header_size = 16;
    u32 entry_table_size = g_entry_count * (u32)sizeof(PakEntry);
    u32 data_start = header_size + entry_table_size + g_name_size;

    u32 offset = data_start;
    for (u32 i = 0; i < g_entry_count; i++) {
        g_entries[i].data_offset = offset;
        offset += g_entries[i].size;
    }

    FILE *out = fopen(output, "wb");
    if (!out) {
        fprintf(stderr, "ERROR: cannot create '%s'\n", output);
        return 1;
    }

    u32 magic = PAK_MAGIC;
    u32 version = 1;
    fwrite(&magic, 4, 1, out);
    fwrite(&version, 4, 1, out);
    fwrite(&g_entry_count, 4, 1, out);
    fwrite(&g_name_size, 4, 1, out);
    fwrite(g_entries, sizeof(PakEntry), g_entry_count, out);
    fwrite(g_names, 1, g_name_size, out);

    for (u32 i = 0; i < g_entry_count; i++) {
        if (!write_file_data(g_paths[i], g_entries[i].size, out)) {
            fclose(out);
            return 1;
        }
    }

    fclose(out);
    printf("Packed %u files into '%s' (%u bytes)\n", g_entry_count, output, offset);
    return 0;
}
