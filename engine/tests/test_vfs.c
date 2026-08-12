/* test_vfs.c — VFS virtual file system unit tests
 *
 * Tests cover:
 *   - vfs_create / vfs_destroy lifecycle
 *   - Directory mount + file read
 *   - vfs_read / vfs_getc / vfs_eof / vfs_size / vfs_read_all
 *   - PAK binary format: write a synthetic PAK, mount and read files
 *   - Mount priority (later mount overrides earlier)
 *   - Null / edge-case argument handling
 *   - Mount limit (VFS_MAX_MOUNTS)
 */

#include "test_framework.h"
#include <asset/vfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* ------------------------------------------------------------------ */
/* helpers                                                             */
/* ------------------------------------------------------------------ */

/* R444: per-pid /tmp paths — parallel ctest trees raced on the fixed names.
 * Function-backed so the macros below keep working at every use site;
 * static buffers, single-threaded tests only. */
static const char *vfs_tmp_dir(void)
{
    static char b[128];
    return test_tmp(b, sizeof b, "test_vfs_dir");
}
static const char *vfs_tmp_file(void)
{
    static char b[160];
    snprintf(b, sizeof b, "%s/hello.txt", vfs_tmp_dir());
    return b;
}
static const char *vfs_tmp_pak(void)
{
    static char b[128];
    return test_tmp(b, sizeof b, "test_vfs.pak");
}

#define TMP_DIR  vfs_tmp_dir()
#define TMP_FILE vfs_tmp_file()
#define TMP_PAK  vfs_tmp_pak()

static void make_tmp_file(const char *path, const char *content)
{
    FILE *fp = fopen(path, "wb");
    if (fp) {
        fwrite(content, 1, strlen(content), fp);
        fclose(fp);
    }
}

static void ensure_dir(const char *path)
{
    mkdir(path, 0755);
}

static bool make_deep_dir(char *dir, usize cap, char *base, usize base_cap,
                          usize target_len) {
    test_tmp(base, base_cap, "r476_vfs_root");
    if (mkdir(base, 0755) != 0) return false;
    int n = snprintf(dir, cap, "%s", base);
    if (n < 0 || (usize)n >= cap || (usize)n > target_len) return false;
    while ((usize)n < target_len) {
        usize remaining = target_len - (usize)n;
        if (remaining < 2) return false;
        usize part_len = remaining - 1;
        if (part_len > 80) part_len = 80;
        dir[n++] = '/';
        memset(dir + n, 'a', part_len);
        n += (int)part_len;
        dir[n] = '\0';
        if (mkdir(dir, 0755) != 0) return false;
    }
    return true;
}

static void remove_deep_dir(char *dir, const char *base) {
    for (;;) {
        rmdir(dir);
        if (strcmp(dir, base) == 0) break;
        char *slash = strrchr(dir, '/');
        if (!slash) break;
        *slash = '\0';
    }
}

static bool make_truncation_prefix(char *rel, usize rel_len,
                                   const char *root, char *absolute, usize absolute_cap) {
    usize pos = 0;
    while (rel_len - pos > 1) {
        usize part_len = rel_len - pos - 2;
        if (part_len > 80) part_len = 80;
        if (part_len == 0) return false;
        memset(rel + pos, 'b', part_len);
        pos += part_len;
        rel[pos++] = '/';
        int n = snprintf(absolute, absolute_cap, "%s/%.*s", root, (int)(pos - 1), rel);
        if (n < 0 || (usize)n >= absolute_cap || mkdir(absolute, 0755) != 0) return false;
    }
    rel[pos++] = 'x';
    rel[pos] = '\0';
    int n = snprintf(absolute, absolute_cap, "%s/%s", root, rel);
    return n >= 0 && (usize)n < absolute_cap;
}

/* Replicate fnv1a from vfs.c for PAK hash test */
static u32 test_fnv1a(const char *str)
{
    u32 hash = 2166136261u;
    while (*str) {
        hash ^= (u8)*str++;
        hash *= 16777619u;
    }
    return hash;
}

/* ------------------------------------------------------------------ */
/* tests                                                               */
/* ------------------------------------------------------------------ */

TEST(vfs_create_destroy)
{
    VFS *vfs = vfs_create();
    ASSERT_TRUE(vfs != NULL);
    vfs_destroy(vfs);  /* should not crash */
}

TEST(vfs_destroy_null)
{
    vfs_destroy(NULL);  /* must be safe */
}

TEST(vfs_mount_dir_basic)
{
    ensure_dir(TMP_DIR);
    make_tmp_file(TMP_FILE, "hello vfs");

    VFS *vfs = vfs_create();
    bool ok = vfs_mount_dir(vfs, TMP_DIR);
    ASSERT_TRUE(ok);
    vfs_destroy(vfs);
}

TEST(vfs_mount_dir_null_vfs)
{
    /* NOTE: vfs_mount_dir does not check dir_path==NULL (engine bug),
     * so we only test vfs==NULL here. */
    ASSERT_TRUE(!vfs_mount_dir(NULL, "/tmp"));
}

/* R475: the mount root is persisted in VFS_MAX_PATH bytes; accepting a
 * longer value would redirect every later relative lookup to its prefix. */
TEST(vfs_mount_dir_rejects_path_truncation)
{
    char path[VFS_MAX_PATH + 1u];
    memset(path, 'x', sizeof(path) - 1u);
    path[sizeof(path) - 1u] = '\0';

    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    ASSERT_FALSE(vfs_mount_dir(vfs, path));
    ASSERT_EQ(vfs->mount_count, 0u);
    vfs_destroy(vfs);
}

TEST(vfs_open_read_dir)
{
    ensure_dir(TMP_DIR);
    make_tmp_file(TMP_FILE, "hello vfs");

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, TMP_DIR);

    VFSFile *f = vfs_open(vfs, "hello.txt");
    ASSERT_TRUE(f != NULL);
    ASSERT_EQ(vfs_size(f), (usize)9);

    char buf[32] = {0};
    usize n = vfs_read(f, buf, sizeof(buf));
    ASSERT_EQ(n, (usize)9);
    ASSERT_TRUE(memcmp(buf, "hello vfs", 9) == 0);

    vfs_close(f);
    vfs_destroy(vfs);
}

/* R476: vfs_open combines a persisted mount root and caller path in full[512].
 * A join that truncates must not open an existing file named by that prefix. */
TEST(vfs_open_rejects_join_path_truncation)
{
    char base[128], root[512];
    ASSERT_TRUE(make_deep_dir(root, sizeof(root), base, sizeof(base), 230));
    usize prefix_len = 510u - strlen(root);
    char rel[512], prefix_file[1024], requested[512];
    ASSERT_TRUE(make_truncation_prefix(rel, prefix_len, root, prefix_file, sizeof(prefix_file)));
    make_tmp_file(prefix_file, "wrong file");
    memcpy(requested, rel, prefix_len);
    memcpy(requested + prefix_len, "_real", sizeof("_real"));

    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    ASSERT_TRUE(vfs_mount_dir(vfs, root));
    ASSERT_TRUE(vfs_open(vfs, requested) == NULL);
    vfs_destroy(vfs);

    remove(prefix_file);
    remove_deep_dir(root, base);
}

TEST(vfs_open_nonexistent)
{
    ensure_dir(TMP_DIR);
    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, TMP_DIR);

    VFSFile *f = vfs_open(vfs, "no_such_file.txt");
    ASSERT_TRUE(f == NULL);

    vfs_destroy(vfs);
}

TEST(vfs_open_null_vfs)
{
    VFSFile *f = vfs_open(NULL, "foo.txt");
    ASSERT_TRUE(f == NULL);
}

TEST(vfs_getc_eof)
{
    ensure_dir(TMP_DIR);
    make_tmp_file(TMP_FILE, "AB");

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, TMP_DIR);

    VFSFile *f = vfs_open(vfs, "hello.txt");
    ASSERT_TRUE(f != NULL);
    ASSERT_TRUE(!vfs_eof(f));

    i32 c1 = vfs_getc(f);
    ASSERT_EQ(c1, (i32)'A');
    i32 c2 = vfs_getc(f);
    ASSERT_EQ(c2, (i32)'B');
    ASSERT_TRUE(vfs_eof(f));
    ASSERT_EQ(vfs_getc(f), -1);  /* past end */

    vfs_close(f);
    vfs_destroy(vfs);
}

TEST(vfs_read_all_helper)
{
    ensure_dir(TMP_DIR);
    make_tmp_file(TMP_FILE, "all data");

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, TMP_DIR);

    usize sz = 0;
    u8 *data = vfs_read_all(vfs, "hello.txt", &sz);
    ASSERT_TRUE(data != NULL);
    ASSERT_EQ(sz, (usize)8);
    ASSERT_TRUE(memcmp(data, "all data", 8) == 0);
    free(data);

    vfs_destroy(vfs);
}

TEST(vfs_read_all_nonexistent)
{
    ensure_dir(TMP_DIR);
    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, TMP_DIR);

    usize sz = 99;
    u8 *data = vfs_read_all(vfs, "missing.txt", &sz);
    ASSERT_TRUE(data == NULL);

    vfs_destroy(vfs);
}

TEST(vfs_read_null_file)
{
    char buf[8];
    ASSERT_EQ(vfs_read(NULL, buf, sizeof(buf)), (usize)0);
    ASSERT_EQ(vfs_size(NULL), (usize)0);
    ASSERT_TRUE(vfs_eof(NULL));  /* null => treated as EOF */
}

TEST(vfs_mount_priority)
{
    /* Two directories: second mount overrides first for same filename */
    char dir_a[128], dir_b[128]; /* R444: per-pid paths */
    char file_a[160], file_b[160];
    test_tmp(dir_a, sizeof dir_a, "test_vfs_a");
    test_tmp(dir_b, sizeof dir_b, "test_vfs_b");
    snprintf(file_a, sizeof file_a, "%s/data.txt", dir_a);
    snprintf(file_b, sizeof file_b, "%s/data.txt", dir_b);
    const char *DIR_A = dir_a;
    const char *DIR_B = dir_b;
    ensure_dir(DIR_A);
    ensure_dir(DIR_B);

    make_tmp_file(file_a, "from_A");
    make_tmp_file(file_b, "from_B");

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, DIR_A);
    vfs_mount_dir(vfs, DIR_B);

    VFSFile *f = vfs_open(vfs, "data.txt");
    ASSERT_TRUE(f != NULL);

    char buf[16] = {0};
    vfs_read(f, buf, sizeof(buf));
    /* Later mount (DIR_B) should win */
    ASSERT_TRUE(memcmp(buf, "from_B", 6) == 0);

    vfs_close(f);
    vfs_destroy(vfs);
}

/* R397: DIR mount had no max file size — ftell → calloc entire file. */
TEST(vfs_dir_rejects_oversized_file)
{
    ensure_dir(TMP_DIR);
    char big_path[160]; /* R444: per-pid path */
    snprintf(big_path, sizeof big_path, "%s/huge.bin", TMP_DIR);
    FILE *f = fopen(big_path, "wb");
    ASSERT_NOT_NULL(f);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    ASSERT_TRUE(ftruncate(fileno(f), (off_t)VFS_MAX_FILE_BYTES + 1) == 0);
#else
    if (fseek(f, (long)VFS_MAX_FILE_BYTES, SEEK_SET) == 0) fputc('x', f);
#endif
    fclose(f);

    VFS *vfs = vfs_create();
    ASSERT_TRUE(vfs_mount_dir(vfs, TMP_DIR));
    ASSERT_TRUE(vfs_open(vfs, "huge.bin") == NULL);

    usize sz = 99;
    u8 *data = vfs_read_all(vfs, "huge.bin", &sz);
    ASSERT_TRUE(data == NULL);
    ASSERT_EQ(sz, (usize)0);

    vfs_destroy(vfs);
    remove(big_path);
}

TEST(vfs_pak_format)
{
    /* Build a minimal PAK file in memory and write to disk:
     *   PakHeader { magic, version, entry_count=1, name_table_size }
     *   PakEntry[1]
     *   name_table: "greet.txt\0"
     *   data: "PAK DATA!"
     */
    const char *fname   = "greet.txt";
    const char *content = "PAK DATA!";
    u32 fname_len       = (u32)strlen(fname) + 1;   /* include NUL */
    u32 content_len     = (u32)strlen(content);

    PakHeader hdr;
    hdr.magic          = VFS_PAK_MAGIC;
    hdr.version        = VFS_PAK_VERSION;
    hdr.entry_count    = 1;
    hdr.name_table_size = fname_len;

    u32 name_table_off = (u32)(sizeof(PakHeader) + sizeof(PakEntry));
    u32 data_off       = name_table_off + fname_len;

    PakEntry entry;
    entry.name_hash   = test_fnv1a(fname);
    entry.name_offset = 0;
    entry.data_offset = data_off;
    entry.size        = content_len;

    FILE *fp = fopen(TMP_PAK, "wb");
    ASSERT_TRUE(fp != NULL);
    fwrite(&hdr,   sizeof(hdr),   1, fp);
    fwrite(&entry, sizeof(entry), 1, fp);
    fwrite(fname,  1, fname_len,     fp);
    fwrite(content, 1, content_len,  fp);
    fclose(fp);

    /* Mount and read */
    VFS *vfs = vfs_create();
    bool ok = vfs_mount_pak(vfs, TMP_PAK);
    ASSERT_TRUE(ok);

    VFSFile *f = vfs_open(vfs, "greet.txt");
    ASSERT_TRUE(f != NULL);
    ASSERT_EQ(vfs_size(f), (usize)content_len);

    char buf[32] = {0};
    vfs_read(f, buf, sizeof(buf));
    ASSERT_TRUE(memcmp(buf, content, content_len) == 0);

    vfs_close(f);
    vfs_destroy(vfs);
}

/* The allocation sentinel must prevent an overread, not turn a truncated name
 * table entry into a valid path.  Malformed entries remain lookup misses. */
TEST(vfs_pak_unterminated_name_is_miss)
{
    const char *fname = "greet.txt";
    const char *content = "PAK DATA!";
    u32 fname_len = (u32)strlen(fname);  /* deliberately excludes NUL */
    u32 content_len = (u32)strlen(content);
    u32 data_off = (u32)(sizeof(PakHeader) + sizeof(PakEntry)) + fname_len;

    PakHeader hdr = { .magic = VFS_PAK_MAGIC, .version = VFS_PAK_VERSION,
                      .entry_count = 1, .name_table_size = fname_len };
    PakEntry entry = { .name_hash = test_fnv1a(fname), .name_offset = 0,
                       .data_offset = data_off, .size = content_len };

    FILE *fp = fopen(TMP_PAK, "wb");
    ASSERT_NOT_NULL(fp);
    ASSERT_EQ(fwrite(&hdr, sizeof(hdr), 1, fp), (usize)1);
    ASSERT_EQ(fwrite(&entry, sizeof(entry), 1, fp), (usize)1);
    ASSERT_EQ(fwrite(fname, 1, fname_len, fp), (usize)fname_len);
    ASSERT_EQ(fwrite(content, 1, content_len, fp), (usize)content_len);
    ASSERT_EQ(fclose(fp), 0);

    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    ASSERT_TRUE(vfs_mount_pak(vfs, TMP_PAK));
    ASSERT_TRUE(vfs_open(vfs, fname) == NULL);
    vfs_destroy(vfs);
}

/* R388: writes a one-entry PAK whose header/entry fields can be overridden, so
 * the bounds checks in vfs_mount_pak can be driven directly. Layout matches
 * vfs_pak_format above. */
static void write_pak_with(u32 entry_count, u32 name_table_size,
                           u32 entry_data_offset, u32 entry_size)
{
    const char *fname   = "greet.txt";
    const char *content = "PAK DATA!";
    u32 fname_len       = (u32)strlen(fname) + 1;
    u32 content_len     = (u32)strlen(content);

    PakHeader hdr = { .magic = VFS_PAK_MAGIC, .version = VFS_PAK_VERSION,
                      .entry_count = entry_count, .name_table_size = name_table_size };
    PakEntry entry = { .name_hash = test_fnv1a(fname), .name_offset = 0,
                       .data_offset = entry_data_offset, .size = entry_size };

    FILE *fp = fopen(TMP_PAK, "wb");
    if (!fp) return;
    fwrite(&hdr,    sizeof(hdr),   1, fp);
    fwrite(&entry,  sizeof(entry), 1, fp);
    fwrite(fname,   1, fname_len,    fp);
    fwrite(content, 1, content_len,  fp);
    fclose(fp);
}

/* R388: name_table_size == UINT32_MAX made `name_table_size + 1` wrap to 0 in
 * u32, so calloc handed back a minimal block and the following fread wrote the
 * rest of the file into it — a heap buffer overflow with attacker-controlled
 * bytes. Found by fuzz_vfs_pak. */
TEST(vfs_pak_name_table_size_overflow_rejected)
{
    write_pak_with(1, UINT32_MAX, (u32)(sizeof(PakHeader) + sizeof(PakEntry)) + 10u, 9);

    VFS *vfs = vfs_create();
    ASSERT_TRUE(!vfs_mount_pak(vfs, TMP_PAK));
    vfs_destroy(vfs);
}

/* R388: the entry table must fit in the bytes following the header. Pre-fix this
 * was also rejected, but only after a multi-gigabyte calloc that entry_count
 * alone sized; this pins the cheap rejection so the bound cannot be dropped. */
TEST(vfs_pak_entry_count_bounded_by_file_size)
{
    write_pak_with(VFS_MAX_PAK_ENTRIES + 1u, 10,
                   (u32)(sizeof(PakHeader) + sizeof(PakEntry)) + 10u, 9);

    VFS *vfs = vfs_create();
    ASSERT_TRUE(!vfs_mount_pak(vfs, TMP_PAK));
    vfs_destroy(vfs);
}

/* R412: PAKs are generated by tools/packer.c, which caps files at 4096 entries.
 * Mounting larger external archives used to size metadata allocations directly
 * from the header before any gameplay path opened a file. */
TEST(vfs_pak_entry_count_above_tool_cap_rejected)
{
    u32 name_len = (u32)strlen("greet.txt") + 1u;
    write_pak_with(VFS_MAX_PAK_ENTRIES + 1u, name_len,
                   (u32)(sizeof(PakHeader) + sizeof(PakEntry)) + name_len, 9u);

    VFS *vfs = vfs_create();
    ASSERT_TRUE(!vfs_mount_pak(vfs, TMP_PAK));
    vfs_destroy(vfs);
}

/* R388: an entry claiming data past EOF must not be openable. As above the
 * pre-fix result was also NULL, but only after vfs_open sized a ~4 GiB calloc
 * from entry->size; this pins the miss so the range check cannot be dropped. */
TEST(vfs_pak_entry_data_past_eof_is_miss)
{
    u32 name_len = (u32)strlen("greet.txt") + 1u;
    write_pak_with(1, name_len, (u32)(sizeof(PakHeader) + sizeof(PakEntry)) + name_len,
                   0xFFFFFF00u);

    VFS *vfs = vfs_create();
    /* The header itself is consistent, so the mount succeeds; the lying entry is
     * simply not reachable. */
    ASSERT_TRUE(vfs_mount_pak(vfs, TMP_PAK));
    ASSERT_TRUE(vfs_open(vfs, "greet.txt") == NULL);
    vfs_destroy(vfs);
}

TEST(vfs_pak_bad_magic)
{
    PakHeader hdr = { .magic = 0xDEADBEEF, .version = 1, .entry_count = 0, .name_table_size = 0 };
    FILE *fp = fopen(TMP_PAK, "wb");
    fwrite(&hdr, sizeof(hdr), 1, fp);
    fclose(fp);

    VFS *vfs = vfs_create();
    bool ok = vfs_mount_pak(vfs, TMP_PAK);
    ASSERT_TRUE(!ok);  /* should reject bad magic */
    vfs_destroy(vfs);
}

/* A PAK version selects its on-disk layout. Do not parse a future or stale
 * version as the current PakEntry format merely because its magic matches. */
TEST(vfs_pak_version_mismatch_rejected)
{
    PakHeader hdr = { .magic = VFS_PAK_MAGIC, .version = VFS_PAK_VERSION + 1u,
                      .entry_count = 0, .name_table_size = 0 };
    FILE *fp = fopen(TMP_PAK, "wb");
    ASSERT_NOT_NULL(fp);
    ASSERT_TRUE(fwrite(&hdr, sizeof(hdr), 1, fp) == 1);
    ASSERT_TRUE(fclose(fp) == 0);

    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    ASSERT_FALSE(vfs_mount_pak(vfs, TMP_PAK));
    ASSERT_EQ(vfs->mount_count, 0u);
    vfs_destroy(vfs);
}

TEST(vfs_pak_nonexistent)
{
    VFS *vfs = vfs_create();
    bool ok = vfs_mount_pak(vfs, "/tmp/no_such_pak_file_xyz.pak");
    ASSERT_TRUE(!ok);
    vfs_destroy(vfs);
}

/* The mounted PAK path is retained in VFS_MAX_PATH bytes just like a
 * directory mount. Reject a longer source path instead of silently storing a
 * different truncated identity. */
TEST(vfs_mount_pak_rejects_path_truncation)
{
    char base[128], dir[512], path[1024];
    test_tmp(base, sizeof(base), "r549_vfs_root");
    ASSERT_EQ(mkdir(base, 0755), 0);
    int dn = snprintf(dir, sizeof(dir), "%s", base);
    ASSERT_TRUE(dn >= 0 && (usize)dn < sizeof(dir));
    while ((usize)dn < 250u) {
        usize part = 70u;
        if ((usize)dn + 1u + part > 250u) part = 250u - (usize)dn - 1u;
        dir[dn++] = '/';
        memset(dir + dn, 'q', part);
        dn += (int)part;
        dir[dn] = '\0';
        ASSERT_EQ(mkdir(dir, 0755), 0);
    }
    int n = snprintf(path, sizeof(path), "%s/archive.pak", dir);
    ASSERT_TRUE(n >= 0 && (usize)n < sizeof(path));
    PakHeader hdr = { .magic = VFS_PAK_MAGIC, .version = VFS_PAK_VERSION,
                      .entry_count = 0u, .name_table_size = 0u };
    FILE *fp = fopen(path, "wb");
    ASSERT_NOT_NULL(fp);
    ASSERT_EQ(fwrite(&hdr, sizeof(hdr), 1u, fp), (usize)1);
    ASSERT_EQ(fclose(fp), 0);

    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    ASSERT_FALSE(vfs_mount_pak(vfs, path));
    ASSERT_EQ(vfs->mount_count, 0u);
    vfs_destroy(vfs);
    remove(path);
    remove_deep_dir(dir, base);
}

TEST(vfs_mount_limit)
{
    VFS *vfs = vfs_create();
    ensure_dir(TMP_DIR);
    for (u32 i = 0; i < VFS_MAX_MOUNTS; i++) {
        ASSERT_TRUE(vfs_mount_dir(vfs, TMP_DIR));
    }
    /* Next mount should fail */
    ASSERT_TRUE(!vfs_mount_dir(vfs, TMP_DIR));
    vfs_destroy(vfs);
}

TEST(vfs_pak_header_constants)
{
    /* Verify PAK magic value is 'EPAT' LE = 'TAPE' */
    u32 magic = VFS_PAK_MAGIC;
    u8 *b = (u8 *)&magic;
    ASSERT_EQ(b[0], (u8)'E');
    ASSERT_EQ(b[1], (u8)'P');
    ASSERT_EQ(b[2], (u8)'A');
    ASSERT_EQ(b[3], (u8)'T');
    ASSERT_EQ(VFS_PAK_VERSION, 1u);
}

TEST(vfs_read_partial)
{
    ensure_dir(TMP_DIR);
    make_tmp_file(TMP_FILE, "0123456789");

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, TMP_DIR);

    VFSFile *f = vfs_open(vfs, "hello.txt");
    ASSERT_TRUE(f != NULL);
    ASSERT_EQ(vfs_size(f), (usize)10);

    char buf[4] = {0};
    usize n = vfs_read(f, buf, 4);
    ASSERT_EQ(n, (usize)4);
    ASSERT_TRUE(memcmp(buf, "0123", 4) == 0);
    ASSERT_TRUE(!vfs_eof(f));

    n = vfs_read(f, buf, 4);
    ASSERT_EQ(n, (usize)4);
    ASSERT_TRUE(memcmp(buf, "4567", 4) == 0);

    /* Only 2 bytes left */
    n = vfs_read(f, buf, 4);
    ASSERT_EQ(n, (usize)2);
    ASSERT_TRUE(vfs_eof(f));

    vfs_close(f);
    vfs_destroy(vfs);
}

/* ------------------------------------------------------------------ */
/*  Edge Cases                                                          */
/* ------------------------------------------------------------------ */

TEST(vfs_close_null)
{
    vfs_close(NULL);  /* Must not crash */
}

TEST(vfs_getc_null)
{
    i32 c = vfs_getc(NULL);
    ASSERT_EQ(c, -1);  /* NULL file returns EOF */
}

TEST(vfs_read_all_null_vfs)
{
    usize sz = 99;
    u8 *data = vfs_read_all(NULL, "test.txt", &sz);
    ASSERT_TRUE(data == NULL);
}

TEST(vfs_open_empty_path)
{
    ensure_dir(TMP_DIR);
    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, TMP_DIR);

    /* R353: empty path is rejected (not a safe relative path). */
    VFSFile *f = vfs_open(vfs, "");
    ASSERT_TRUE(f == NULL);

    vfs_destroy(vfs);
}

TEST(vfs_rejects_path_traversal)
{
    /* R353: DIR mount must not fopen outside mount via ".." or absolute paths. */
    ensure_dir(TMP_DIR);
    make_tmp_file(TMP_FILE, "hello vfs");

    VFS *vfs = vfs_create();
    ASSERT_TRUE(vfs_mount_dir(vfs, TMP_DIR));

    ASSERT_TRUE(vfs_open(vfs, NULL) == NULL);
    ASSERT_TRUE(vfs_open(vfs, "/etc/passwd") == NULL);
    ASSERT_TRUE(vfs_open(vfs, "../test_vfs_dir/hello.txt") == NULL);
    ASSERT_TRUE(vfs_open(vfs, "foo/../../etc/passwd") == NULL);

    VFSFile *ok = vfs_open(vfs, "hello.txt");
    ASSERT_TRUE(ok != NULL);
    vfs_close(ok);

    vfs_destroy(vfs);
}

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */

TEST_MAIN_BEGIN()
    ensure_dir(TMP_DIR);

    RUN_TEST(vfs_create_destroy);
    RUN_TEST(vfs_destroy_null);
    RUN_TEST(vfs_mount_dir_basic);
    RUN_TEST(vfs_mount_dir_null_vfs);
    RUN_TEST(vfs_mount_dir_rejects_path_truncation);
    RUN_TEST(vfs_open_read_dir);
    RUN_TEST(vfs_open_rejects_join_path_truncation);
    RUN_TEST(vfs_open_nonexistent);
    RUN_TEST(vfs_open_null_vfs);
    RUN_TEST(vfs_getc_eof);
    RUN_TEST(vfs_read_all_helper);
    RUN_TEST(vfs_read_all_nonexistent);
    RUN_TEST(vfs_read_null_file);
    RUN_TEST(vfs_mount_priority);
    RUN_TEST(vfs_dir_rejects_oversized_file);
    RUN_TEST(vfs_pak_format);
    RUN_TEST(vfs_pak_unterminated_name_is_miss);
    RUN_TEST(vfs_pak_name_table_size_overflow_rejected);
    RUN_TEST(vfs_pak_entry_count_bounded_by_file_size);
    RUN_TEST(vfs_pak_entry_data_past_eof_is_miss);
    RUN_TEST(vfs_pak_entry_count_above_tool_cap_rejected);
    RUN_TEST(vfs_pak_bad_magic);
    RUN_TEST(vfs_pak_version_mismatch_rejected);
    RUN_TEST(vfs_pak_nonexistent);
    RUN_TEST(vfs_mount_pak_rejects_path_truncation);
    RUN_TEST(vfs_mount_limit);
    RUN_TEST(vfs_pak_header_constants);
    RUN_TEST(vfs_read_partial);
    /* Edge cases */
    RUN_TEST(vfs_close_null);
    RUN_TEST(vfs_getc_null);
    RUN_TEST(vfs_read_all_null_vfs);
    RUN_TEST(vfs_open_empty_path);
    RUN_TEST(vfs_rejects_path_traversal);
TEST_MAIN_END()
