/* Stage 4 scene editor Phase 3 Task 1: platform_list_dir + BreakEditorAssets
 * surface tests.
 *
 * Covers (brief checklist): one-level listing of files/dirs; capacity
 * truncation detectable via out_count > capacity; probe mode (capacity 0);
 * error paths (missing path, file-as-path, over-long path, bad args);
 * over-long stat-join skip + 255-byte name boundary; symlink no-follow via
 * lstat (POSIX); model create validation (missing/file/empty/over-long
 * root, trailing-slash normalization); dirs-first byte-wise deterministic
 * sort pinned; enter/up with root clamping and the depth-8 cap; rejection
 * of absolute/'/'-containing/empty/"."/unknown/non-dir/symlink/over-long
 * enter names; ".." escape impossible; extension filter on/off (dirs always
 * pass, case-sensitive, bounded token drops); abs_path bounded; empty dir;
 * OOM create sweep; 4096-entry per-directory cap. */

/* glibc under -std=c11 (__STRICT_ANSI__) hides symlink() without a feature
 * test macro (same situation as filewatch.c's _POSIX_C_SOURCE pin). */
#if !defined(_WIN32)
#define _DEFAULT_SOURCE
#endif

#include "test_framework.h"

#include <platform/platform_fs.h>
#include <editor/editor_assets.h>
#include <editor/editor_test_hooks.h>

#include <string.h>

#if !defined(_WIN32)
#include <sys/stat.h>
#endif

/* ------------------------------------------------------------------ */
/* Fixture helpers                                                     */
/* ------------------------------------------------------------------ */

static bool mk_dir(const char *path) {
    return TEST_MKDIR(path) == 0;
}

static bool mk_file(const char *path) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return false;
    return fclose(fp) == 0;
}

static void join2(char *out, usize cap, const char *a, const char *b) {
    snprintf(out, cap, "%s/%s", a, b);
}

/* Finds `name` in `entries[0..count)`; returns its index or -1. */
static long find_entry(const PlatformDirEntry *entries, u32 count, const char *name) {
    for (u32 i = 0; i < count; i++) {
        if (strcmp(entries[i].name, name) == 0) return (long)i;
    }
    return -1;
}

/* ------------------------------------------------------------------ */
/* platform_list_dir                                                   */
/* ------------------------------------------------------------------ */

TEST(platform_list_basic_and_probe) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_list_basic");
    ASSERT_TRUE(mk_dir(root));
    char p[600];
    join2(p, sizeof(p), root, "sub1"); ASSERT_TRUE(mk_dir(p));
    join2(p, sizeof(p), root, "sub2"); ASSERT_TRUE(mk_dir(p));
    join2(p, sizeof(p), root, "f1.txt"); ASSERT_TRUE(mk_file(p));
    join2(p, sizeof(p), root, "f2.md"); ASSERT_TRUE(mk_file(p));
    join2(p, sizeof(p), root, "f3"); ASSERT_TRUE(mk_file(p));

    PlatformDirEntry entries[8];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 8, &count));
    ASSERT_EQ(count, 5u);

    long i_sub1 = find_entry(entries, count, "sub1");
    long i_sub2 = find_entry(entries, count, "sub2");
    long i_f1 = find_entry(entries, count, "f1.txt");
    long i_f2 = find_entry(entries, count, "f2.md");
    long i_f3 = find_entry(entries, count, "f3");
    ASSERT_TRUE(i_sub1 >= 0 && i_sub2 >= 0 && i_f1 >= 0 && i_f2 >= 0 && i_f3 >= 0);
    ASSERT_TRUE(entries[i_sub1].is_dir);
    ASSERT_TRUE(entries[i_sub2].is_dir);
    ASSERT_FALSE(entries[i_f1].is_dir);
    ASSERT_FALSE(entries[i_f2].is_dir);
    ASSERT_FALSE(entries[i_f3].is_dir);
    /* Dot entries are never reported. */
    ASSERT_TRUE(find_entry(entries, count, ".") < 0);
    ASSERT_TRUE(find_entry(entries, count, "..") < 0);

    /* Probe mode: NULL entries with capacity 0 counts without writing. */
    u32 probe = 0;
    ASSERT_TRUE(platform_list_dir(root, NULL, 0, &probe));
    ASSERT_EQ(probe, 5u);

    join2(p, sizeof(p), root, "sub1"); ASSERT_TRUE(TEST_RMDIR(p) == 0);
    join2(p, sizeof(p), root, "sub2"); ASSERT_TRUE(TEST_RMDIR(p) == 0);
    join2(p, sizeof(p), root, "f1.txt"); remove(p);
    join2(p, sizeof(p), root, "f2.md"); remove(p);
    join2(p, sizeof(p), root, "f3"); remove(p);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(platform_list_truncation_detectable) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_trunc");
    ASSERT_TRUE(mk_dir(root));
    char p[600];
    for (int i = 0; i < 5; i++) {
        char name[32];
        snprintf(name, sizeof(name), "f%d", i);
        join2(p, sizeof(p), root, name);
        ASSERT_TRUE(mk_file(p));
    }

    PlatformDirEntry entries[2];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 2, &count));
    /* out_count is the TOTAL found: truncation is detectable. */
    ASSERT_EQ(count, 5u);

    /* Zero capacity with a non-NULL buffer writes nothing but counts. */
    count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 0, &count));
    ASSERT_EQ(count, 5u);

    for (int i = 0; i < 5; i++) {
        char name[32];
        snprintf(name, sizeof(name), "f%d", i);
        join2(p, sizeof(p), root, name);
        remove(p);
    }
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(platform_list_empty_dir) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_empty");
    ASSERT_TRUE(mk_dir(root));

    PlatformDirEntry entries[4];
    u32 count = 99;
    ASSERT_TRUE(platform_list_dir(root, entries, 4, &count));
    ASSERT_EQ(count, 0u);

    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(platform_list_error_paths) {
    PlatformDirEntry entries[4];
    u32 count = 0;

    ASSERT_FALSE(platform_list_dir(NULL, entries, 4, &count));
    char root[512];
    test_tmp(root, sizeof(root), "assets_err");
    ASSERT_TRUE(mk_dir(root));
    ASSERT_FALSE(platform_list_dir(root, entries, 4, NULL));
    ASSERT_FALSE(platform_list_dir(root, NULL, 4, &count));

    /* Missing directory. */
    char missing[600];
    join2(missing, sizeof(missing), root, "no_such_dir");
    ASSERT_FALSE(platform_list_dir(missing, entries, 4, &count));

    /* A regular file is not listable (POSIX ENOTDIR / Win32 error). */
    char file[600];
    join2(file, sizeof(file), root, "a_file");
    ASSERT_TRUE(mk_file(file));
    ASSERT_FALSE(platform_list_dir(file, entries, 4, &count));

    /* Over-long path (>= 1024 bytes incl NUL) is a bounded false. */
    char huge[1200];
    memset(huge, 'a', sizeof(huge) - 1);
    huge[sizeof(huge) - 1] = '\0';
    ASSERT_FALSE(platform_list_dir(huge, entries, 4, &count));

    remove(file);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(platform_list_name_bounds) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_maxname");
    ASSERT_TRUE(mk_dir(root));

    /* 255-byte name fits exactly (name[256] incl NUL). Filesystems cap
     * component names at 255 bytes (NAME_MAX), so a 256+-byte name cannot
     * be created on this lane and the skip guard for it is covered by the
     * stat-join overflow test below + code inspection. */
    char long_name[256];
    memset(long_name, 'n', 255);
    long_name[255] = '\0';
    char p[900];
    join2(p, sizeof(p), root, long_name);
    ASSERT_TRUE(mk_file(p));
    char s[600];
    join2(s, sizeof(s), root, "s.txt");
    ASSERT_TRUE(mk_file(s));

    PlatformDirEntry entries[4];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 4, &count));
    ASSERT_EQ(count, 2u);
    long i_long = find_entry(entries, count, long_name);
    ASSERT_TRUE(i_long >= 0);
    ASSERT_EQ(strlen(entries[i_long].name), 255u);

    remove(p);
    remove(s);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

#if !defined(_WIN32)
TEST(platform_list_stat_join_overflow_skips_entry) {
    /* POSIX lane: builds a real directory whose path is just below the
     * 1024-byte bound, containing one file whose joined stat path crosses
     * it — the entry must be skipped (and not counted), listing stays OK. */
    char dir[1100];
    test_tmp(dir, sizeof(dir), "assets_deep");
    ASSERT_TRUE(mk_dir(dir));
    usize base_len = strlen(dir);
    int level = 0;
    while (strlen(dir) < 984) {
        char seg[64];
        snprintf(seg, sizeof(seg), "/%047d", level); /* '/' + 47 chars */
        if (strlen(dir) + strlen(seg) >= PLATFORM_FS_PATH_CAPACITY - 1) break;
        strcat(dir, seg);
        ASSERT_TRUE(mk_dir(dir));
        level++;
    }
    ASSERT_TRUE(strlen(dir) >= 984);
    ASSERT_TRUE(strlen(dir) < PLATFORM_FS_PATH_CAPACITY - 1);

    char fname[48];
    memset(fname, 'f', 40);
    fname[40] = '\0';
    char fpath[1200];
    join2(fpath, sizeof(fpath), dir, fname);
    ASSERT_TRUE(strlen(fpath) + 1 > PLATFORM_FS_PATH_CAPACITY);
    ASSERT_TRUE(mk_file(fpath));

    PlatformDirEntry entries[4];
    u32 count = 77;
    ASSERT_TRUE(platform_list_dir(dir, entries, 4, &count));
    ASSERT_EQ(count, 0u); /* the one real file cannot be stat-joined: skipped */

    remove(fpath);
    while (strlen(dir) > base_len) {
        ASSERT_TRUE(TEST_RMDIR(dir) == 0);
        char *slash = strrchr(dir, '/');
        ASSERT_NOT_NULL(slash);
        *slash = '\0';
    }
    ASSERT_TRUE(TEST_RMDIR(dir) == 0);
}

TEST(platform_list_lstat_failure_skips_entry_not_listing) {
    /* Non-root only: permission bits don't bind euid 0. */
    if (geteuid() == 0) return;
    char root[512];
    test_tmp(root, sizeof(root), "assets_lstatfail");
    ASSERT_TRUE(mk_dir(root));
    char p[600];
    join2(p, sizeof(p), root, "a.txt"); ASSERT_TRUE(mk_file(p));
    join2(p, sizeof(p), root, "sub"); ASSERT_TRUE(mk_dir(p));
    join2(p, sizeof(p), root, "b.txt"); ASSERT_TRUE(mk_file(p));

    /* Control: a readable+searchable directory lists all three. */
    PlatformDirEntry entries[8];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 8, &count));
    ASSERT_EQ(count, 3u);

    /* Read-without-search on the LISTED directory: readdir still yields
     * names (read bit), but every lstat fails EACCES (no search bit) —
     * a deterministic mid-listing lstat failure. Contract: unclassifiable
     * entries are skipped and not counted; the listing itself still
     * succeeds (a stale lstat errno must not turn EOF into an error). */
    ASSERT_EQ(chmod(root, 0444), 0);
    count = 77;
    bool ok = platform_list_dir(root, entries, 8, &count);
    chmod(root, 0755); /* restore before any ASSERT can bail out */
    ASSERT_TRUE(ok);
    ASSERT_EQ(count, 0u);

    join2(p, sizeof(p), root, "a.txt"); remove(p);
    join2(p, sizeof(p), root, "b.txt"); remove(p);
    join2(p, sizeof(p), root, "sub"); TEST_RMDIR(p);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(platform_list_symlink_not_followed) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_symlink");
    ASSERT_TRUE(mk_dir(root));
    char p[700];
    join2(p, sizeof(p), root, "realdir"); ASSERT_TRUE(mk_dir(p));
    char inner[750];
    join2(inner, sizeof(inner), p, "inner.txt"); ASSERT_TRUE(mk_file(inner));
    join2(p, sizeof(p), root, "target.txt"); ASSERT_TRUE(mk_file(p));

    char realdir[700];
    join2(realdir, sizeof(realdir), root, "realdir");
    char linkdir[700];
    join2(linkdir, sizeof(linkdir), root, "linkdir");
    ASSERT_EQ(symlink(realdir, linkdir), 0);
    char target[700];
    join2(target, sizeof(target), root, "target.txt");
    char linkfile[700];
    join2(linkfile, sizeof(linkfile), root, "linkfile");
    ASSERT_EQ(symlink(target, linkfile), 0);
    char broken[700];
    join2(broken, sizeof(broken), root, "broken");
    char nowhere[700];
    join2(nowhere, sizeof(nowhere), root, "no_such_target");
    ASSERT_EQ(symlink(nowhere, broken), 0);

    PlatformDirEntry entries[8];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 8, &count));
    ASSERT_EQ(count, 5u); /* realdir target.txt linkdir linkfile broken */

    long i_realdir = find_entry(entries, count, "realdir");
    long i_target = find_entry(entries, count, "target.txt");
    long i_linkdir = find_entry(entries, count, "linkdir");
    long i_linkfile = find_entry(entries, count, "linkfile");
    long i_broken = find_entry(entries, count, "broken");
    ASSERT_TRUE(i_realdir >= 0 && i_target >= 0 && i_linkdir >= 0 &&
                i_linkfile >= 0 && i_broken >= 0);
    ASSERT_TRUE(entries[i_realdir].is_dir);
    ASSERT_FALSE(entries[i_target].is_dir);
    /* lstat classification: symlinks never report is_dir, even to a dir. */
    ASSERT_FALSE(entries[i_linkdir].is_dir);
    ASSERT_FALSE(entries[i_linkfile].is_dir);
    ASSERT_FALSE(entries[i_broken].is_dir);

    remove(linkdir);
    remove(linkfile);
    remove(broken);
    remove(target);
    join2(inner, sizeof(inner), realdir, "inner.txt"); remove(inner);
    ASSERT_TRUE(TEST_RMDIR(realdir) == 0);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}
#endif /* !_WIN32 */

/* ------------------------------------------------------------------ */
/* BreakEditorAssets model                                             */
/* ------------------------------------------------------------------ */

/* Standard sorted fixture: dirs {zdir, Adir}, files {b.txt, A.txt, a.bscn}. */
static void build_sort_fixture(const char *root) {
    char p[700];
    join2(p, sizeof(p), root, "zdir"); ASSERT_TRUE(mk_dir(p));
    join2(p, sizeof(p), root, "Adir"); ASSERT_TRUE(mk_dir(p));
    join2(p, sizeof(p), root, "b.txt"); ASSERT_TRUE(mk_file(p));
    join2(p, sizeof(p), root, "A.txt"); ASSERT_TRUE(mk_file(p));
    join2(p, sizeof(p), root, "a.bscn"); ASSERT_TRUE(mk_file(p));
}

static void destroy_sort_fixture(const char *root) {
    char p[700];
    join2(p, sizeof(p), root, "zdir"); TEST_RMDIR(p);
    join2(p, sizeof(p), root, "Adir"); TEST_RMDIR(p);
    join2(p, sizeof(p), root, "b.txt"); remove(p);
    join2(p, sizeof(p), root, "A.txt"); remove(p);
    join2(p, sizeof(p), root, "a.bscn"); remove(p);
    TEST_RMDIR(root);
}

static void assert_entry(const BreakEditorAssets *a, usize i,
                         const char *name, bool is_dir) {
    const char *got_name = NULL;
    bool got_dir = false;
    ASSERT_TRUE(break_editor_assets_entry_at(a, i, &got_name, &got_dir));
    ASSERT_STR_EQ(got_name, name);
    ASSERT_TRUE(got_dir == is_dir);
}

static void assert_sort_fixture_order(const BreakEditorAssets *a) {
    /* dirs-first, byte-wise strcmp: 'A'(0x41) < 'a'(0x61) < 'b' < 'z'. */
    ASSERT_EQ(break_editor_assets_count(a), 5u);
    assert_entry(a, 0, "Adir", true);
    assert_entry(a, 1, "zdir", true);
    assert_entry(a, 2, "A.txt", false);
    assert_entry(a, 3, "a.bscn", false);
    assert_entry(a, 4, "b.txt", false);
}

TEST(model_create_sorts_dirs_first_deterministic) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_model_sort");
    ASSERT_TRUE(mk_dir(root));
    build_sort_fixture(root);

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");
    assert_sort_fixture_order(a);
    break_editor_assets_destroy(a);

    /* Determinism pin: a fresh model over the same tree yields the exact
     * same order. */
    BreakEditorAssets *b = break_editor_assets_create(root);
    ASSERT_NOT_NULL(b);
    assert_sort_fixture_order(b);
    break_editor_assets_destroy(b);

    destroy_sort_fixture(root);
}

TEST(model_create_root_validation) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_rootval");
    ASSERT_TRUE(mk_dir(root));

    /* Missing root -> create fails. */
    char missing[600];
    join2(missing, sizeof(missing), root, "missing");
    ASSERT_TRUE(break_editor_assets_create(missing) == NULL);

    /* A regular file as root -> create fails. */
    char file[600];
    join2(file, sizeof(file), root, "file.txt");
    ASSERT_TRUE(mk_file(file));
    ASSERT_TRUE(break_editor_assets_create(file) == NULL);

    /* Empty / NULL / over-long root -> create fails. */
    ASSERT_TRUE(break_editor_assets_create("") == NULL);
    ASSERT_TRUE(break_editor_assets_create(NULL) == NULL);
    char huge[1200];
    memset(huge, 'a', sizeof(huge) - 1);
    huge[sizeof(huge) - 1] = '\0';
    ASSERT_TRUE(break_editor_assets_create(huge) == NULL);

    /* Trailing slashes normalize away. */
    char slashed[600];
    snprintf(slashed, sizeof(slashed), "%s/", root);
    BreakEditorAssets *a = break_editor_assets_create(slashed);
    ASSERT_NOT_NULL(a);
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");
    break_editor_assets_destroy(a);

    remove(file);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_enter_up_root_clamp) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_nav");
    ASSERT_TRUE(mk_dir(root));
    char sub[600];
    join2(sub, sizeof(sub), root, "sub");
    ASSERT_TRUE(mk_dir(sub));
    char deeper[650];
    join2(deeper, sizeof(deeper), sub, "deeper");
    ASSERT_TRUE(mk_dir(deeper));
    char f[700];
    join2(f, sizeof(f), sub, "in_sub.txt");
    ASSERT_TRUE(mk_file(f));

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);
    ASSERT_EQ(break_editor_assets_count(a), 1u); /* only sub */

    ASSERT_TRUE(break_editor_assets_enter(a, "sub"));
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "sub");
    ASSERT_EQ(break_editor_assets_count(a), 2u); /* deeper + in_sub.txt */

    ASSERT_TRUE(break_editor_assets_enter(a, "deeper"));
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "sub/deeper");
    ASSERT_EQ(break_editor_assets_count(a), 0u);

    ASSERT_TRUE(break_editor_assets_up(a));
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "sub");
    ASSERT_EQ(break_editor_assets_count(a), 2u);

    /* ".." through enter is the parent move. */
    ASSERT_TRUE(break_editor_assets_enter(a, ".."));
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");

    /* Root clamping: up / enter("..") at the root stay at the root and
     * report success (clamped, not escaped). */
    ASSERT_TRUE(break_editor_assets_up(a));
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");
    ASSERT_TRUE(break_editor_assets_enter(a, ".."));
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");
    ASSERT_EQ(break_editor_assets_count(a), 1u);

    break_editor_assets_destroy(a);
    remove(f);
    ASSERT_TRUE(TEST_RMDIR(deeper) == 0);
    ASSERT_TRUE(TEST_RMDIR(sub) == 0);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_enter_rejects_unsafe) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_reject");
    ASSERT_TRUE(mk_dir(root));
    char sub[600];
    join2(sub, sizeof(sub), root, "sub");
    ASSERT_TRUE(mk_dir(sub));
    char f[600];
    join2(f, sizeof(f), root, "file.txt");
    ASSERT_TRUE(mk_file(f));
#if !defined(_WIN32)
    char linkdir[600];
    join2(linkdir, sizeof(linkdir), root, "linkdir");
    ASSERT_EQ(symlink(sub, linkdir), 0);
#endif

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);

    char long_name[300];
    memset(long_name, 'n', 280);
    long_name[280] = '\0';

    ASSERT_FALSE(break_editor_assets_enter(a, "/tmp"));       /* absolute */
    ASSERT_FALSE(break_editor_assets_enter(a, "a/b"));       /* contains '/' */
    ASSERT_FALSE(break_editor_assets_enter(a, "sub/../x"));  /* contains '/' */
    ASSERT_FALSE(break_editor_assets_enter(a, "."));         /* dot */
    ASSERT_FALSE(break_editor_assets_enter(a, ""));          /* empty */
    ASSERT_FALSE(break_editor_assets_enter(a, NULL));        /* NULL */
    ASSERT_FALSE(break_editor_assets_enter(a, "missing"));   /* unknown name */
    ASSERT_FALSE(break_editor_assets_enter(a, "file.txt"));  /* not a dir */
    ASSERT_FALSE(break_editor_assets_enter(a, long_name));   /* >= 256 bytes */
#if !defined(_WIN32)
    /* Symlinked dirs are never enterable (lstat: is_dir == false). */
    ASSERT_FALSE(break_editor_assets_enter(a, "linkdir"));
#endif

    /* Nothing moved, nothing listed differently. */
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");
#if !defined(_WIN32)
    ASSERT_EQ(break_editor_assets_count(a), 3u); /* sub + file.txt + linkdir */
#else
    ASSERT_EQ(break_editor_assets_count(a), 2u);
#endif

    break_editor_assets_destroy(a);
#if !defined(_WIN32)
    remove(linkdir);
#endif
    remove(f);
    ASSERT_TRUE(TEST_RMDIR(sub) == 0);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_depth_cap_8) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_depth");
    ASSERT_TRUE(mk_dir(root));
    char cur[700];
    snprintf(cur, sizeof(cur), "%s", root);
    for (int i = 1; i <= 9; i++) {
        char seg[16];
        snprintf(seg, sizeof(seg), "d%d", i);
        strcat(cur, "/");
        strcat(cur, seg);
        ASSERT_TRUE(mk_dir(cur));
    }

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);
    char expected_rel[128] = "";
    for (int i = 1; i <= 8; i++) {
        char seg[16];
        snprintf(seg, sizeof(seg), "d%d", i);
        ASSERT_TRUE(break_editor_assets_enter(a, seg));
        if (i > 1) strcat(expected_rel, "/");
        strcat(expected_rel, seg);
        ASSERT_STR_EQ(break_editor_assets_current_rel(a), expected_rel);
    }
    /* Depth 8 reached: the 9th level exists on disk but is rejected. */
    ASSERT_FALSE(break_editor_assets_enter(a, "d9"));
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "d1/d2/d3/d4/d5/d6/d7/d8");

    for (int i = 0; i < 8; i++) {
        ASSERT_TRUE(break_editor_assets_up(a));
    }
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");

    break_editor_assets_destroy(a);
    for (int i = 9; i >= 1; i--) {
        ASSERT_TRUE(TEST_RMDIR(cur) == 0);
        char *slash = strrchr(cur, '/');
        ASSERT_NOT_NULL(slash);
        *slash = '\0';
    }
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_filter_csv_on_off) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_filter");
    ASSERT_TRUE(mk_dir(root));
    char p[600];
    join2(p, sizeof(p), root, "sub"); ASSERT_TRUE(mk_dir(p));
    const char *files[] = {"a.bscn", "b.json", "c.lua", "d.txt", "note", ".hidden"};
    for (usize i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
        join2(p, sizeof(p), root, files[i]);
        ASSERT_TRUE(mk_file(p));
    }

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);
    ASSERT_EQ(break_editor_assets_count(a), 7u); /* sub + 6 files */

    break_editor_assets_set_filter(a, "bscn,json,lua");
    ASSERT_EQ(break_editor_assets_count(a), 4u);
    assert_entry(a, 0, "sub", true); /* dirs always pass */
    assert_entry(a, 1, "a.bscn", false);
    assert_entry(a, 2, "b.json", false);
    assert_entry(a, 3, "c.lua", false);

    /* Case-sensitive, byte-wise. */
    break_editor_assets_set_filter(a, "BSCN");
    ASSERT_EQ(break_editor_assets_count(a), 1u);
    assert_entry(a, 0, "sub", true);

    /* No extension ('note', '.hidden') never passes an active filter. */
    break_editor_assets_set_filter(a, "txt");
    ASSERT_EQ(break_editor_assets_count(a), 2u);
    assert_entry(a, 0, "sub", true);
    assert_entry(a, 1, "d.txt", false);

    /* Off via NULL and via "". */
    break_editor_assets_set_filter(a, NULL);
    ASSERT_EQ(break_editor_assets_count(a), 7u);
    break_editor_assets_set_filter(a, "");
    ASSERT_EQ(break_editor_assets_count(a), 7u);

    /* Empty segments and duplicates are harmless. */
    break_editor_assets_set_filter(a, "bscn,,bscn,");
    ASSERT_EQ(break_editor_assets_count(a), 2u);

    /* Over-long tokens are dropped (bounded), the rest still work. */
    {
        char csv[128];
        char tok[48];
        memset(tok, 'x', 40);
        tok[40] = '\0';
        snprintf(csv, sizeof(csv), "bscn,%s,lua", tok);
        break_editor_assets_set_filter(a, csv);
        ASSERT_EQ(break_editor_assets_count(a), 3u); /* sub + a.bscn + c.lua */
    }

    /* Beyond 16 tokens the tail is dropped: "bscn" at position 17 lost. */
    {
        char csv[256] = "";
        for (int i = 0; i < 16; i++) {
            char tok[8];
            snprintf(tok, sizeof(tok), "e%d,", i);
            strcat(csv, tok);
        }
        strcat(csv, "bscn");
        break_editor_assets_set_filter(a, csv);
        ASSERT_EQ(break_editor_assets_count(a), 1u); /* only sub */
    }

    break_editor_assets_destroy(a);
    for (usize i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
        join2(p, sizeof(p), root, files[i]);
        remove(p);
    }
    join2(p, sizeof(p), root, "sub"); TEST_RMDIR(p);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_abs_path_bounded) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_abspath");
    ASSERT_TRUE(mk_dir(root));
    char sub[600];
    join2(sub, sizeof(sub), root, "sub");
    ASSERT_TRUE(mk_dir(sub));
    char f[650];
    join2(f, sizeof(f), sub, "f.txt");
    ASSERT_TRUE(mk_file(f));
    char rf[600];
    join2(rf, sizeof(rf), root, "top.txt");
    ASSERT_TRUE(mk_file(rf));

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);
    /* root order: sub(dir), top.txt. */
    char out[1200];
    ASSERT_TRUE(break_editor_assets_abs_path(a, 1, out, sizeof(out)));
    char expect[1200];
    snprintf(expect, sizeof(expect), "%s/top.txt", root);
    ASSERT_STR_EQ(out, expect);

    ASSERT_TRUE(break_editor_assets_enter(a, "sub"));
    ASSERT_TRUE(break_editor_assets_abs_path(a, 0, out, sizeof(out)));
    snprintf(expect, sizeof(expect), "%s/sub/f.txt", root);
    ASSERT_STR_EQ(out, expect);

    /* Bounded: too-small cap fails without writing past it. */
    out[0] = 'X';
    usize need = strlen(expect) + 1;
    ASSERT_FALSE(break_editor_assets_abs_path(a, 0, out, need - 1));
    ASSERT_TRUE(break_editor_assets_abs_path(a, 0, out, need));
    ASSERT_STR_EQ(out, expect);

    /* Out-of-range index and bad args fail. */
    ASSERT_FALSE(break_editor_assets_abs_path(a, 1, out, sizeof(out)));
    ASSERT_FALSE(break_editor_assets_abs_path(a, 0, NULL, sizeof(out)));
    ASSERT_FALSE(break_editor_assets_abs_path(NULL, 0, out, sizeof(out)));

    break_editor_assets_destroy(a);
    remove(f);
    remove(rf);
    ASSERT_TRUE(TEST_RMDIR(sub) == 0);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_empty_dir) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_modelempty");
    ASSERT_TRUE(mk_dir(root));

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);
    ASSERT_EQ(break_editor_assets_count(a), 0u);
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");
    const char *name = NULL;
    bool is_dir = false;
    ASSERT_FALSE(break_editor_assets_entry_at(a, 0, &name, &is_dir));
    char out[64];
    ASSERT_FALSE(break_editor_assets_abs_path(a, 0, out, sizeof(out)));
    break_editor_assets_destroy(a);

    /* destroy(NULL) is a no-op. */
    break_editor_assets_destroy(NULL);

    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_entries_capped_4096) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_cap4096");
    ASSERT_TRUE(mk_dir(root));
    char p[700];
    for (int i = 0; i < 4100; i++) {
        char name[32];
        snprintf(name, sizeof(name), "f%04d", i);
        join2(p, sizeof(p), root, name);
        ASSERT_TRUE(mk_file(p));
    }

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);
    /* The cache is bounded: exactly 4096 of the 4100 files. Which 4096 the
     * OS enumeration yields is NOT pinned (readdir order is unspecified) —
     * the platform-level out_count > capacity pin covers truncation
     * detectability. */
    ASSERT_EQ(break_editor_assets_count(a), 4096u);
    const char *name = NULL;
    bool is_dir = true;
    ASSERT_TRUE(break_editor_assets_entry_at(a, 0, &name, &is_dir));
    ASSERT_FALSE(is_dir);
    ASSERT_TRUE(break_editor_assets_entry_at(a, 4095, &name, &is_dir));
    ASSERT_FALSE(break_editor_assets_entry_at(a, 4096, &name, &is_dir));

    break_editor_assets_destroy(a);
    for (int i = 0; i < 4100; i++) {
        char name[32];
        snprintf(name, sizeof(name), "f%04d", i);
        join2(p, sizeof(p), root, name);
        remove(p);
    }
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_escape_impossible) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_escape");
    ASSERT_TRUE(mk_dir(root));
    char sub[600];
    join2(sub, sizeof(sub), root, "sub");
    ASSERT_TRUE(mk_dir(sub));

    BreakEditorAssets *a = break_editor_assets_create(root);
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_editor_assets_enter(a, "sub"));
    for (int i = 0; i < 5; i++) {
        ASSERT_TRUE(break_editor_assets_enter(a, ".."));
    }
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");
    for (int i = 0; i < 5; i++) {
        ASSERT_TRUE(break_editor_assets_up(a));
    }
    ASSERT_STR_EQ(break_editor_assets_current_rel(a), "");

    /* Every abs_path stays byte-prefixed by the root. */
    ASSERT_EQ(break_editor_assets_count(a), 1u);
    char out[1200];
    ASSERT_TRUE(break_editor_assets_abs_path(a, 0, out, sizeof(out)));
    ASSERT_TRUE(strncmp(out, root, strlen(root)) == 0);

    break_editor_assets_destroy(a);
    ASSERT_TRUE(TEST_RMDIR(sub) == 0);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(model_oom_create_sweep) {
    char root[512];
    test_tmp(root, sizeof(root), "assets_oom");
    ASSERT_TRUE(mk_dir(root));

    /* create performs exactly 3 editor-owned allocations: the struct, the
     * 4096-entry cache, the visible-index array. Budgets 0..2 must fail
     * with NULL (no leak — ASan detect_leaks watches this), 3 succeeds. */
    for (u64 budget = 0; budget < 3; budget++) {
        break_editor_test_set_alloc_budget(budget);
        BreakEditorAssets *a = break_editor_assets_create(root);
        break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
        ASSERT_TRUE(a == NULL);
    }

    break_editor_test_set_alloc_budget(3);
    BreakEditorAssets *a = break_editor_assets_create(root);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_NOT_NULL(a);
    break_editor_assets_destroy(a);

    BreakEditorAssets *b = break_editor_assets_create(root);
    ASSERT_NOT_NULL(b);
    break_editor_assets_destroy(b);

    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(platform_list_basic_and_probe);
    RUN_TEST(platform_list_truncation_detectable);
    RUN_TEST(platform_list_empty_dir);
    RUN_TEST(platform_list_error_paths);
    RUN_TEST(platform_list_name_bounds);
#if !defined(_WIN32)
    RUN_TEST(platform_list_stat_join_overflow_skips_entry);
    RUN_TEST(platform_list_lstat_failure_skips_entry_not_listing);
    RUN_TEST(platform_list_symlink_not_followed);
#endif
    RUN_TEST(model_create_sorts_dirs_first_deterministic);
    RUN_TEST(model_create_root_validation);
    RUN_TEST(model_enter_up_root_clamp);
    RUN_TEST(model_enter_rejects_unsafe);
    RUN_TEST(model_depth_cap_8);
    RUN_TEST(model_filter_csv_on_off);
    RUN_TEST(model_abs_path_bounded);
    RUN_TEST(model_empty_dir);
    RUN_TEST(model_entries_capped_4096);
    RUN_TEST(model_escape_impossible);
    RUN_TEST(model_oom_create_sweep);
TEST_MAIN_END()
