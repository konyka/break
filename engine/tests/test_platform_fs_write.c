/* Stage 5 Phase A Task 3: write-side PAL tests — PlatformAtomicWriter
 * commit/abort/failure-latching, platform_mkdir, platform_file_size.
 *
 * Covers (brief checklist): commit → content readable at target + tmp gone;
 * overwrite of an existing target swaps content; abort → no tmp residue +
 * pre-existing target untouched (and a never-created target stays absent);
 * write failure latches (later write false, commit false, no residue —
 * RLIMIT_FSIZE injection, POSIX); abort idempotent in the free(NULL) sense
 * (the handle is consumed → caller NULLs it → abort(NULL) is a no-op);
 * write-denied directory (0444, non-root — the platform_list_dir precedent)
 * fail-closed: open NULL with no tmp residue, and a mid-write permission
 * flip → commit false with target untouched; platform_mkdir single-level /
 * exists-as-dir true / missing parent false / colliding file false;
 * platform_file_size 0-byte / 1 MiB / missing / directory; NULL + over-long
 * argument matrix. */

/* glibc under -std=c11 (__STRICT_ANSI__) hides chmod/getrlimit/sigprocmask
 * without a feature test macro (the test_editor_assets.c precedent). */
#if !defined(_WIN32)
#define _DEFAULT_SOURCE
#endif

#include "test_framework.h"

#include <platform/platform_fs.h>

#include <string.h>

#if !defined(_WIN32)
#include <sys/stat.h>
#include <sys/resource.h>
#include <signal.h>
#endif

/* ------------------------------------------------------------------ */
/* Fixture helpers                                                     */
/* ------------------------------------------------------------------ */

static bool mk_dir(const char *path) {
    return TEST_MKDIR(path) == 0;
}

static void join2(char *out, usize cap, const char *a, const char *b) {
    snprintf(out, cap, "%s/%s", a, b);
}

/* Creates/truncates a file with the given bytes (fixture pre-state). */
static bool put_file(const char *path, const void *data, usize len) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return false;
    if (len && fwrite(data, 1, len, fp) != len) {
        fclose(fp);
        return false;
    }
    return fclose(fp) == 0;
}

/* Reads the whole file for content comparison (NUL-terminated; cap includes
 * the NUL). -1 = cannot open, -2 = longer than cap - 1. */
static long read_file(const char *path, u8 *buf, usize cap) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return -1;
    usize n = fread(buf, 1, cap - 1, fp);
    int extra = fgetc(fp); /* EOF expected exactly at cap - 1 */
    fclose(fp);
    if (extra != EOF) return -2;
    buf[n] = '\0';
    return (long)n;
}

/* Directory entry count via the sibling PAL function (99 = listing error). */
static u32 dir_count(const char *path) {
    PlatformDirEntry entries[16];
    u32 count = 0;
    if (!platform_list_dir(path, entries, 16, &count)) return 99u;
    return count;
}

/* ------------------------------------------------------------------ */
/* PlatformAtomicWriter                                                */
/* ------------------------------------------------------------------ */

TEST(commit_content_readable_tmp_gone) {
    char root[512];
    test_tmp(root, sizeof(root), "fsw_commit");
    ASSERT_TRUE(mk_dir(root));
    char target[600];
    join2(target, sizeof(target), root, "out.bin");

    PlatformAtomicWriter *w = platform_atomic_writer_open(target);
    ASSERT_NOT_NULL(w);
    ASSERT_TRUE(platform_atomic_writer_write(w, "hello", 5));
    ASSERT_TRUE(platform_atomic_writer_write(w, "", 0)); /* empty write no-op */
    ASSERT_TRUE(platform_atomic_writer_write(w, " world", 6));
    ASSERT_TRUE(platform_atomic_writer_commit(w));
    w = NULL;

    u8 buf[64];
    ASSERT_EQ(read_file(target, buf, sizeof(buf)), 11);
    ASSERT_STR_EQ((const char *)buf, "hello world");
    ASSERT_EQ(dir_count(root), 1u); /* tmp gone, only out.bin */

    u64 size = 0;
    ASSERT_TRUE(platform_file_size(target, &size));
    ASSERT_EQ(size, (u64)11);

    remove(target);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(commit_overwrites_existing_target) {
    char root[512];
    test_tmp(root, sizeof(root), "fsw_overwrite");
    ASSERT_TRUE(mk_dir(root));
    char target[600];
    join2(target, sizeof(target), root, "data.bin");
    ASSERT_TRUE(put_file(target, "old-content", 11));

    PlatformAtomicWriter *w = platform_atomic_writer_open(target);
    ASSERT_NOT_NULL(w);
    ASSERT_TRUE(platform_atomic_writer_write(w, "new", 3));
    ASSERT_TRUE(platform_atomic_writer_commit(w));
    w = NULL;

    u8 buf[64];
    ASSERT_EQ(read_file(target, buf, sizeof(buf)), 3);
    ASSERT_STR_EQ((const char *)buf, "new");
    ASSERT_EQ(dir_count(root), 1u);

    remove(target);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(abort_no_residue_target_untouched) {
    char root[512];
    test_tmp(root, sizeof(root), "fsw_abort");
    ASSERT_TRUE(mk_dir(root));
    char target[600];
    join2(target, sizeof(target), root, "keep.bin");
    ASSERT_TRUE(put_file(target, "original", 8));

    /* Variant 1: pre-existing target — content untouched by the abort. */
    PlatformAtomicWriter *w = platform_atomic_writer_open(target);
    ASSERT_NOT_NULL(w);
    ASSERT_TRUE(platform_atomic_writer_write(w, "garbage", 7));
    platform_atomic_writer_abort(w);
    w = NULL;
    u8 buf[64];
    ASSERT_EQ(read_file(target, buf, sizeof(buf)), 8);
    ASSERT_STR_EQ((const char *)buf, "original");
    ASSERT_EQ(dir_count(root), 1u); /* tmp gone */

    /* Variant 2: a target that never existed stays absent. */
    char other[600];
    join2(other, sizeof(other), root, "never.bin");
    w = platform_atomic_writer_open(other);
    ASSERT_NOT_NULL(w);
    ASSERT_TRUE(platform_atomic_writer_write(w, "x", 1));
    platform_atomic_writer_abort(w);
    w = NULL;
    ASSERT_EQ(read_file(other, buf, sizeof(buf)), -1); /* absent */
    ASSERT_EQ(dir_count(root), 1u);

    remove(target);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(abort_idempotent_null_noop) {
    /* Idempotence contract (platform_fs.h): commit/abort CONSUME the handle
     * (it is freed); the caller NULLs it and abort(NULL) is a safe no-op —
     * the free(NULL) idiom. Double abort on a dangling non-NULL handle would
     * be a use-after-free by C rules and is a contract violation, exactly
     * like double free. */
    char root[512];
    test_tmp(root, sizeof(root), "fsw_abortidem");
    ASSERT_TRUE(mk_dir(root));
    char target[600];
    join2(target, sizeof(target), root, "t.bin");

    platform_atomic_writer_abort(NULL); /* no-op, no crash */

    PlatformAtomicWriter *w = platform_atomic_writer_open(target);
    ASSERT_NOT_NULL(w);
    platform_atomic_writer_abort(w); /* abort without any write */
    w = NULL;
    platform_atomic_writer_abort(w); /* second abort on the NULLed handle */
    ASSERT_EQ(dir_count(root), 0u);

    w = platform_atomic_writer_open(target);
    ASSERT_NOT_NULL(w);
    ASSERT_TRUE(platform_atomic_writer_write(w, "data", 4));
    platform_atomic_writer_abort(w);
    w = NULL;
    platform_atomic_writer_abort(w); /* double abort via the NULL idiom */
    platform_atomic_writer_abort(NULL);
    ASSERT_EQ(dir_count(root), 0u);

    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

#if !defined(_WIN32)
/* Catching (not blocking) SIGXFSZ: a blocked SIGXFSZ would stay PENDING and
 * kill the process when the mask is restored. A caught signal is consumed by
 * the handler, and the limit-crossing write(2) still fails EFBIG. */
static volatile sig_atomic_t g_sigxfsz_seen;
static void on_sigxfsz(int sig) {
    (void)sig;
    g_sigxfsz_seen = 1;
}

TEST(write_failure_latches_then_commit_fails_clean) {
    /* Deterministic write-failure injection: RLIMIT_FSIZE soft = 64 with
     * SIGXFSZ caught → the crossing write(2) fails EFBIG. Contract: the
     * failed write returns false and LATCHES (later writes false), and
     * commit on a latched writer fails closed (false, no rename, no tmp
     * residue, target never created). RLIMIT_FSIZE binds euid 0 too, so no
     * geteuid skip here. Nothing may ASSERT between setrlimit and the
     * restore — a bail-out would leak the 64-byte limit into later tests. */
    char root[512];
    test_tmp(root, sizeof(root), "fsw_wfail");
    ASSERT_TRUE(mk_dir(root));
    char target[600];
    join2(target, sizeof(target), root, "big.bin");

    struct sigaction sa, prev_sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = on_sigxfsz;
    sigemptyset(&sa.sa_mask);
    ASSERT_EQ(sigaction(SIGXFSZ, &sa, &prev_sa), 0);
    struct rlimit prev_rl;
    ASSERT_EQ(getrlimit(RLIMIT_FSIZE, &prev_rl), 0);

    g_sigxfsz_seen = 0;
    struct rlimit rl = prev_rl;
    rl.rlim_cur = 64;
    int limited = (setrlimit(RLIMIT_FSIZE, &rl) == 0);
    PlatformAtomicWriter *w = limited ? platform_atomic_writer_open(target) : NULL;
    u8 buf[128];
    memset(buf, 0xAB, sizeof(buf));
    int w1 = 1, w2 = 1, committed = 1;
    if (w) {
        w1 = platform_atomic_writer_write(w, buf, sizeof(buf)); /* crosses 64 */
        w2 = platform_atomic_writer_write(w, buf, 1);           /* latched */
        committed = platform_atomic_writer_commit(w);           /* fail closed */
    }
    setrlimit(RLIMIT_FSIZE, &prev_rl);
    sigaction(SIGXFSZ, &prev_sa, NULL);

    ASSERT_TRUE(limited);
    ASSERT_NOT_NULL(w);
    ASSERT_TRUE(g_sigxfsz_seen); /* the limit really fired */
    ASSERT_FALSE(w1);
    ASSERT_FALSE(w2);
    ASSERT_FALSE(committed);
    u8 out[8];
    ASSERT_EQ(read_file(target, out, sizeof(out)), -1); /* target absent */
    ASSERT_EQ(dir_count(root), 0u);                     /* tmp cleaned */

    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(readonly_dir_0444_fail_closed) {
    /* Non-root only: permission bits don't bind euid 0 (the
     * platform_list_dir 0444 precedent). */
    if (geteuid() == 0) return;
    char root[512];
    test_tmp(root, sizeof(root), "fsw_0444");
    ASSERT_TRUE(mk_dir(root));
    char target[600];
    join2(target, sizeof(target), root, "ro.bin");

    /* Variant A: the writer's tmp lives in the target's directory, so a
     * write-denied directory fails the write path at open (mkstemp EACCES)
     * — fail closed, and no tmp can ever have existed. */
    ASSERT_EQ(chmod(root, 0444), 0);
    PlatformAtomicWriter *w = platform_atomic_writer_open(target);
    chmod(root, 0755); /* restore before any ASSERT can bail out */
    ASSERT_TRUE(w == NULL);
    ASSERT_EQ(dir_count(root), 0u); /* no tmp residue */

    /* Variant B: writer opened while writable, then the directory flips to
     * 0444 → commit fails closed at rename(2) (EACCES): false, target never
     * created, handle consumed. POSIX reality (documented in
     * platform_fs.h): the cleanup unlink is denied by the same 0444, so the
     * stale tmp outlives the failed commit until permissions allow removal.
     * The no-residue guarantee is carried by variant A and by every
     * abort/failure path whose directory stays writable (pinned by the
     * other tests in this file). */
    w = platform_atomic_writer_open(target);
    ASSERT_NOT_NULL(w);
    ASSERT_TRUE(platform_atomic_writer_write(w, "data", 4));
    ASSERT_EQ(chmod(root, 0444), 0);
    int committed = platform_atomic_writer_commit(w);
    chmod(root, 0755); /* restore before any ASSERT can bail out */
    ASSERT_FALSE(committed);
    u8 out[8];
    ASSERT_EQ(read_file(target, out, sizeof(out)), -1); /* target absent */

    /* Exactly the one stale "ro.bin.tmpXXXXXX" from the failed commit
     * remains; remove it now that permissions allow. */
    PlatformDirEntry entries[8];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 8, &count));
    ASSERT_EQ(count, 1u);
    ASSERT_NOT_NULL(strstr(entries[0].name, ".tmp"));
    char p[700];
    join2(p, sizeof(p), root, entries[0].name);
    remove(p);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}
#endif /* !_WIN32 */

/* ------------------------------------------------------------------ */
/* platform_mkdir / platform_file_size                                 */
/* ------------------------------------------------------------------ */

TEST(mkdir_single_level_and_existing) {
    char root[512];
    test_tmp(root, sizeof(root), "fsw_mkdir");
    ASSERT_TRUE(mk_dir(root));
    char a[600];
    join2(a, sizeof(a), root, "a");

    ASSERT_TRUE(platform_mkdir(a)); /* creates a single level */
    ASSERT_TRUE(platform_mkdir(a)); /* already exists as dir → true */

    char ab[640];
    join2(ab, sizeof(ab), a, "b");
    ASSERT_TRUE(platform_mkdir(ab)); /* parent exists: still single level */

    char missing_parent[700];
    join2(missing_parent, sizeof(missing_parent), root, "nope/child");
    ASSERT_FALSE(platform_mkdir(missing_parent)); /* no implicit parents */

    char f[600];
    join2(f, sizeof(f), root, "file");
    ASSERT_TRUE(put_file(f, "x", 1));
    ASSERT_FALSE(platform_mkdir(f)); /* exists as FILE → false */

    PlatformDirEntry entries[8]; /* sanity: mkdir really made the dir */
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(a, entries, 8, &count));
    ASSERT_EQ(count, 1u);

    remove(f);
    ASSERT_TRUE(TEST_RMDIR(ab) == 0);
    ASSERT_TRUE(TEST_RMDIR(a) == 0);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(file_size_zero_and_1mib) {
    char root[512];
    test_tmp(root, sizeof(root), "fsw_fsize");
    ASSERT_TRUE(mk_dir(root));

    char zero[600];
    join2(zero, sizeof(zero), root, "zero.bin");
    ASSERT_TRUE(put_file(zero, "", 0));
    u64 size = 77;
    ASSERT_TRUE(platform_file_size(zero, &size));
    ASSERT_EQ(size, (u64)0);

    /* 1 MiB written THROUGH the atomic writer (dogfoods large writes). */
    char big[600];
    join2(big, sizeof(big), root, "big.bin");
    PlatformAtomicWriter *w = platform_atomic_writer_open(big);
    ASSERT_NOT_NULL(w);
    static const u8 block[4096] = {0x5A};
    for (int i = 0; i < 256; i++) {
        ASSERT_TRUE(platform_atomic_writer_write(w, block, sizeof(block)));
    }
    ASSERT_TRUE(platform_atomic_writer_commit(w));
    w = NULL;
    size = 0;
    ASSERT_TRUE(platform_file_size(big, &size));
    ASSERT_EQ(size, (u64)(1024 * 1024));

    char missing[600];
    join2(missing, sizeof(missing), root, "missing.bin");
    ASSERT_FALSE(platform_file_size(missing, &size)); /* missing → false */
    ASSERT_FALSE(platform_file_size(root, &size));    /* directory → false */

    remove(zero);
    remove(big);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(null_and_error_matrix) {
    u64 size = 0;
    ASSERT_TRUE(platform_atomic_writer_open(NULL) == NULL);
    ASSERT_TRUE(platform_atomic_writer_open("") == NULL);
    ASSERT_FALSE(platform_atomic_writer_write(NULL, "x", 1));
    ASSERT_FALSE(platform_atomic_writer_commit(NULL));
    platform_atomic_writer_abort(NULL); /* no-op */
    ASSERT_FALSE(platform_mkdir(NULL));
    ASSERT_FALSE(platform_mkdir(""));
    ASSERT_FALSE(platform_file_size(NULL, &size));
    ASSERT_FALSE(platform_file_size("x", NULL));
    ASSERT_FALSE(platform_file_size("", &size));

    /* Over-long paths (no room for the ".tmpXXXXXX" suffix / NUL). */
    char long_path[1200];
    memset(long_path, 'a', sizeof(long_path) - 1);
    long_path[sizeof(long_path) - 1] = '\0';
    ASSERT_TRUE(platform_atomic_writer_open(long_path) == NULL);
    ASSERT_FALSE(platform_mkdir(long_path));
    ASSERT_FALSE(platform_file_size(long_path, &size));

    char root[512];
    test_tmp(root, sizeof(root), "fsw_null");
    ASSERT_TRUE(mk_dir(root));

    /* open into a missing directory → NULL (mkstemp ENOENT), no residue. */
    char ghost[600];
    join2(ghost, sizeof(ghost), root, "no_such_dir/file.bin");
    ASSERT_TRUE(platform_atomic_writer_open(ghost) == NULL);
    ASSERT_EQ(dir_count(root), 0u);

    /* write(w, NULL, 0) is an empty no-op; write(w, NULL, >0) fails and
     * latches — a subsequent VALID write stays false; commit fails closed. */
    char target[600];
    join2(target, sizeof(target), root, "t.bin");
    PlatformAtomicWriter *w = platform_atomic_writer_open(target);
    ASSERT_NOT_NULL(w);
    ASSERT_TRUE(platform_atomic_writer_write(w, NULL, 0));
    ASSERT_FALSE(platform_atomic_writer_write(w, NULL, 1));
    ASSERT_FALSE(platform_atomic_writer_write(w, "y", 1)); /* latched */
    ASSERT_FALSE(platform_atomic_writer_commit(w));        /* fail closed */
    w = NULL;
    ASSERT_EQ(dir_count(root), 0u); /* no residue */

    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

#if !defined(_WIN32)
/* Stage 5 Task 3 review M2 pin (controller pre-authorized in the Task 4
 * dispatch): platform_file_size FOLLOWS symlinks (stat(2)) — a symlink to
 * a regular file reports the target's size; a dangling symlink and a
 * directory are false. The CAS consumer (Task 4 break_update store) is
 * protected by verify-on-read regardless. */
TEST(file_size_follows_symlinks) {
    char root[512];
    test_tmp(root, sizeof(root), "fsw_symlink");
    ASSERT_TRUE(mk_dir(root));
    char target[600];
    join2(target, sizeof(target), root, "real.bin");
    ASSERT_TRUE(put_file(target, "123456789", 9));

    char link[600];
    join2(link, sizeof(link), root, "link.bin");
    ASSERT_EQ(symlink("real.bin", link), 0);
    u64 size = 0;
    ASSERT_TRUE(platform_file_size(link, &size)); /* follows → target size */
    ASSERT_EQ(size, (u64)9);

    char dangling[600];
    join2(dangling, sizeof(dangling), root, "dangling.bin");
    ASSERT_EQ(symlink("no_such_file", dangling), 0);
    ASSERT_FALSE(platform_file_size(dangling, &size)); /* dangling → false */
    ASSERT_FALSE(platform_file_size(root, &size));     /* directory → false */

    remove(link);
    remove(dangling);
    remove(target);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}
#endif

TEST_MAIN_BEGIN()
    RUN_TEST(commit_content_readable_tmp_gone);
    RUN_TEST(commit_overwrites_existing_target);
    RUN_TEST(abort_no_residue_target_untouched);
    RUN_TEST(abort_idempotent_null_noop);
#if !defined(_WIN32)
    RUN_TEST(write_failure_latches_then_commit_fails_clean);
    RUN_TEST(readonly_dir_0444_fail_closed);
    RUN_TEST(file_size_follows_symlinks);
#endif
    RUN_TEST(mkdir_single_level_and_existing);
    RUN_TEST(file_size_zero_and_1mib);
    RUN_TEST(null_and_error_matrix);
TEST_MAIN_END()
