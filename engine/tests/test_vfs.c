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

/* ------------------------------------------------------------------ */
/* helpers                                                             */
/* ------------------------------------------------------------------ */

static const char *TMP_DIR  = "/tmp/test_vfs_dir";
static const char *TMP_FILE = "/tmp/test_vfs_dir/hello.txt";
static const char *TMP_PAK  = "/tmp/test_vfs.pak";

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
    const char *DIR_A = "/tmp/test_vfs_a";
    const char *DIR_B = "/tmp/test_vfs_b";
    ensure_dir(DIR_A);
    ensure_dir(DIR_B);

    make_tmp_file("/tmp/test_vfs_a/data.txt", "from_A");
    make_tmp_file("/tmp/test_vfs_b/data.txt", "from_B");

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

TEST(vfs_pak_nonexistent)
{
    VFS *vfs = vfs_create();
    bool ok = vfs_mount_pak(vfs, "/tmp/no_such_pak_file_xyz.pak");
    ASSERT_TRUE(!ok);
    vfs_destroy(vfs);
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
    RUN_TEST(vfs_open_read_dir);
    RUN_TEST(vfs_open_nonexistent);
    RUN_TEST(vfs_open_null_vfs);
    RUN_TEST(vfs_getc_eof);
    RUN_TEST(vfs_read_all_helper);
    RUN_TEST(vfs_read_all_nonexistent);
    RUN_TEST(vfs_read_null_file);
    RUN_TEST(vfs_mount_priority);
    RUN_TEST(vfs_pak_format);
    RUN_TEST(vfs_pak_bad_magic);
    RUN_TEST(vfs_pak_nonexistent);
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
