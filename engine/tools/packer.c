#include <core/types.h>
#include <platform/file.h>
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
#endif

#define MAX_ENTRIES   4096  /* Keep in sync with VFS_MAX_PAK_ENTRIES. */
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
static int     g_path_error; /* R428: set on any path truncation; main aborts. */

static void add_file(const char *rel_path, const char *abs_path) {
    if (g_entry_count >= MAX_ENTRIES) return;

    u64 sz;
    if (!platform_file_size(abs_path, &sz)) return;

    if (sz > 0xFFFFFFFFull) {
        fprintf(stderr, "WARN: '%s' exceeds 4 GB limit, skipping\n", abs_path);
        return;
    }

    u32 name_len = (u32)strlen(rel_path) + 1;
    /* R105-2: Bounds-check g_names to prevent buffer overflow when
     * relative paths exceed MAX_PATH_LEN or total name data exceeds buffer. */
    if (g_name_size + name_len > MAX_ENTRIES * MAX_PATH_LEN) {
        fprintf(stderr, "WARN: name buffer full, skipping '%s'\n", rel_path);
        return;
    }

    /* R428: g_paths is MAX_PATH_LEN (260) — a longer abs path was silently
     * truncated by strncpy, so the packed entry later read the wrong file.
     * Fail loudly instead. */
    size_t abs_len = strlen(abs_path);
    if (abs_len >= MAX_PATH_LEN) {
        fprintf(stderr, "ERROR: absolute path exceeds %d bytes: '%s'\n",
                MAX_PATH_LEN, abs_path);
        g_path_error = 1;
        return;
    }

    u32 idx = g_entry_count++;
    memcpy(g_paths[idx], abs_path, abs_len + 1);

    u32 name_off = g_name_size;
    memcpy(g_names + g_name_size, rel_path, name_len);
    g_name_size += name_len;

    g_entries[idx].name_hash = fnv1a(rel_path);
    g_entries[idx].name_offset = name_off;
    g_entries[idx].size = (u32)sz;
    g_entries[idx].data_offset = 0;
}

static void packer_visitor(const char *rel_path, const char *abs_path,
                           bool is_directory, void *user) {
    (void)user;
    if (!is_directory)
        add_file(rel_path, abs_path);
}

static void scan_dir(const char *base_dir, const char *rel_prefix) {
    (void)rel_prefix;
    platform_dir_foreach(base_dir, "", packer_visitor, NULL);
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

    /* R164: Check fwrite return value to detect disk-full errors. */
    if (fwrite(data, 1, size, out) != size) {
        fprintf(stderr, "ERROR: failed to write data for '%s' (disk full?)\n", path);
        UnmapViewOfFile(data);
        CloseHandle(hMap);
        CloseHandle(hFile);
        return 0;
    }

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
        /* R164: Check fwrite return value to detect disk-full errors. */
        if (fwrite(buf, 1, chunk, out) != chunk) {
            fprintf(stderr, "ERROR: failed to write data for '%s' (disk full?)\n", path);
            fclose(fp);
            return 0;
        }
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
        if (platform_file_is_directory(argv[i])) {
            scan_dir(argv[i], "");
        } else if (platform_file_is_regular(argv[i])) {
            const char *name = basename_of(argv[i]);
            add_file(name, argv[i]);
        } else {
            fprintf(stderr, "WARN: skipping '%s' (not found)\n", argv[i]);
        }
    }

    /* R428: any path truncation during scanning means the pak would be
     * incomplete or corrupt — abort instead of writing it. */
    if (g_path_error) {
        fprintf(stderr, "ERROR: aborting due to path truncation errors above\n");
        return 1;
    }

    if (g_entry_count == 0) {
        fprintf(stderr, "ERROR: no files to pack\n");
        return 1;
    }

    u32 header_size = 16;
    u32 entry_table_size = g_entry_count * (u32)sizeof(PakEntry);
    u32 data_start = header_size + entry_table_size + g_name_size;

    /* R164: Use u64 accumulator to detect u32 overflow in total data offset.
     * PAK format uses u32 data_offset fields; if total packed data exceeds 4 GB,
     * the u32 offset would silently wrap, producing a corrupt PAK file. */
    u64 total_offset = (u64)data_start;
    for (u32 i = 0; i < g_entry_count; i++) {
        if (total_offset > 0xFFFFFFFFull) {
            fprintf(stderr, "ERROR: total data size exceeds 4 GB limit "
                    "(PAK format uses u32 offsets)\n");
            return 1;
        }
        g_entries[i].data_offset = (u32)total_offset;
        total_offset += g_entries[i].size;
    }

    FILE *out = fopen(output, "wb");
    if (!out) {
        fprintf(stderr, "ERROR: cannot create '%s'\n", output);
        return 1;
    }

    /* R164: Check fwrite return values to detect disk-full / I/O errors. */
    u32 magic = PAK_MAGIC;
    u32 version = 1;
    int write_ok = 1;
    write_ok &= (fwrite(&magic, 4, 1, out) == 1);
    write_ok &= (fwrite(&version, 4, 1, out) == 1);
    write_ok &= (fwrite(&g_entry_count, 4, 1, out) == 1);
    write_ok &= (fwrite(&g_name_size, 4, 1, out) == 1);
    write_ok &= (fwrite(g_entries, sizeof(PakEntry), g_entry_count, out) == g_entry_count);
    write_ok &= (fwrite(g_names, 1, g_name_size, out) == g_name_size);
    if (!write_ok) {
        fprintf(stderr, "ERROR: failed to write PAK header (disk full?)\n");
        fclose(out);
        return 1;
    }

    for (u32 i = 0; i < g_entry_count; i++) {
        if (!write_file_data(g_paths[i], g_entries[i].size, out)) {
            fclose(out);
            return 1;
        }
    }

    fclose(out);
    printf("Packed %u files into '%s' (%llu bytes)\n",
           g_entry_count, output, (unsigned long long)total_offset);
    return 0;
}
