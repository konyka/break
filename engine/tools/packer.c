#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

typedef unsigned int u32;
typedef unsigned char u8;

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

static void add_file(const char *rel_path, const char *abs_path) {
    if (g_entry_count >= MAX_ENTRIES) return;

    FILE *fp = fopen(abs_path, "rb");
    if (!fp) return;
    fseek(fp, 0, SEEK_END);
    u32 sz = (u32)ftell(fp);
    fclose(fp);

    u32 idx = g_entry_count++;
    strncpy(g_paths[idx], abs_path, MAX_PATH_LEN - 1);

    u32 name_off = g_name_size;
    u32 name_len = (u32)strlen(rel_path) + 1;
    memcpy(g_names + g_name_size, rel_path, name_len);
    g_name_size += name_len;

    g_entries[idx].name_hash = fnv1a(rel_path);
    g_entries[idx].name_offset = name_off;
    g_entries[idx].size = sz;
    g_entries[idx].data_offset = 0;
}

static void scan_dir(const char *base_dir, const char *rel_prefix) {
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
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <output.pak> <input_dir_or_file> [...]\n", argv[0]);
        return 1;
    }

    const char *output = argv[1];

    for (int i = 2; i < argc; i++) {
        struct stat st;
        if (stat(argv[i], &st) != 0) {
            fprintf(stderr, "WARN: skipping '%s' (not found)\n", argv[i]);
            continue;
        }
        if (S_ISDIR(st.st_mode)) {
            scan_dir(argv[i], "");
        } else if (S_ISREG(st.st_mode)) {
            const char *name = strrchr(argv[i], '/');
            name = name ? name + 1 : argv[i];
            add_file(name, argv[i]);
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
        FILE *fp = fopen(g_paths[i], "rb");
        if (!fp) {
            fprintf(stderr, "ERROR: cannot read '%s'\n", g_paths[i]);
            fclose(out);
            return 1;
        }
        u8 buf[65536];
        u32 remaining = g_entries[i].size;
        while (remaining > 0) {
            u32 chunk = remaining > sizeof(buf) ? sizeof(buf) : remaining;
            fread(buf, 1, chunk, fp);
            fwrite(buf, 1, chunk, out);
            remaining -= chunk;
        }
        fclose(fp);
    }

    fclose(out);
    printf("Packed %u files into '%s' (%u bytes)\n", g_entry_count, output, offset);
    return 0;
}
