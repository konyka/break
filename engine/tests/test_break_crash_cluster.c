#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include "test_framework.h"

#include <crash/break_crash_cluster.h>
#include <platform/platform_fs.h>

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

static char g_dir[300];

static void dir_init(void) {
    test_tmp(g_dir, sizeof(g_dir), "crash_cluster");
    TEST_MKDIR(g_dir);
}

static void path_in(char *out, size_t cap, const char *name) {
    snprintf(out, cap, "%s/%s", g_dir, name);
}

/* a 64-char lowercase hex string made of one repeated digit, for readable fixtures */
static const char *hx(char d) {
    static char bufs[8][65];
    static int next;
    char *b = bufs[next++ & 7];
    memset(b, d, 64u);
    b[64] = '\0';
    return b;
}

static BreakCrashFrame frame(const char *module, const char *symbol, u64 mod_off, bool resolved) {
    BreakCrashFrame f;
    memset(&f, 0, sizeof(f));
    snprintf(f.module, sizeof(f.module), "%s", module);
    snprintf(f.symbol, sizeof(f.symbol), "%s", symbol);
    f.module_offset = mod_off;
    f.resolved = resolved;
    return f;
}

/* ------------------------------------------------------------------ signature */

TEST(a_signature_is_stable_and_ignores_addresses_and_processes) {
    char a[65], b[65];
    BreakCrashFrame f1[3], f2[3];
    f1[0] = frame("game", "leaf", 0x100, true);  f1[0].pc = 0x400100; f1[0].symbol_offset = 7;
    f1[1] = frame("game", "mid", 0x200, true);   f1[1].pc = 0x400200;
    f1[2] = frame("game", "outer", 0x300, true); f1[2].pc = 0x400300;
    f2[0] = frame("game", "leaf", 0x9100, true); f2[0].pc = 0x7f0000009100ull; f2[0].symbol_offset = 99;
    f2[1] = frame("game", "mid", 0x9200, true);
    f2[2] = frame("game", "outer", 0x9300, true);
    ASSERT_TRUE(break_crash_signature(11, f1, 3u, a));
    ASSERT_TRUE(break_crash_signature(11, f2, 3u, b));
    ASSERT_STR_EQ(a, b);                       /* different addresses / offsets inside the functions */
    ASSERT_EQ(strlen(a), 64u);
    for (int i = 0; i < 64; i++) ASSERT_TRUE((a[i] >= '0' && a[i] <= '9') || (a[i] >= 'a' && a[i] <= 'f'));
}

TEST(a_signature_depends_on_signal_and_the_top_three_frames_only) {
    char base[65], other[65];
    BreakCrashFrame f[5];
    f[0] = frame("game", "leaf", 1, true);
    f[1] = frame("game", "mid", 2, true);
    f[2] = frame("game", "outer", 3, true);
    f[3] = frame("game", "main", 4, true);
    f[4] = frame("libc.so.6", "", 5, false);
    ASSERT_TRUE(break_crash_signature(11, f, 5u, base));
    /* frames beyond the third do not matter */
    {
        BreakCrashFrame g[5];
        memcpy(g, f, sizeof(g));
        g[3] = frame("game", "different", 9, true);
        g[4] = frame("x", "y", 9, true);
        ASSERT_TRUE(break_crash_signature(11, g, 5u, other));
        ASSERT_STR_EQ(base, other);
    }
    /* signal matters */
    ASSERT_TRUE(break_crash_signature(6, f, 5u, other));
    ASSERT_TRUE(strcmp(base, other) != 0);
    /* each of the first three frames matters */
    for (int k = 0; k < 3; k++) {
        BreakCrashFrame g[5];
        memcpy(g, f, sizeof(g));
        g[k] = frame("game", "changed", 77, true);
        ASSERT_TRUE(break_crash_signature(11, g, 5u, other));
        ASSERT_TRUE(strcmp(base, other) != 0);
    }
    /* module matters */
    {
        BreakCrashFrame g[5];
        memcpy(g, f, sizeof(g));
        snprintf(g[0].module, sizeof(g[0].module), "plugin");
        ASSERT_TRUE(break_crash_signature(11, g, 5u, other));
        ASSERT_TRUE(strcmp(base, other) != 0);
    }
    /* order matters */
    {
        BreakCrashFrame g[5];
        memcpy(g, f, sizeof(g));
        g[0] = f[1];
        g[1] = f[0];
        ASSERT_TRUE(break_crash_signature(11, g, 5u, other));
        ASSERT_TRUE(strcmp(base, other) != 0);
    }
}

TEST(an_unresolved_frame_is_identified_by_module_and_offset_and_frames_do_not_collide) {
    char a[65], b[65], c[65];
    BreakCrashFrame f[1], g[1], h[2];
    f[0] = frame("game", "", 0x1234, false);
    g[0] = frame("game", "", 0x1235, false);
    ASSERT_TRUE(break_crash_signature(11, f, 1u, a));
    ASSERT_TRUE(break_crash_signature(11, g, 1u, b));
    ASSERT_TRUE(strcmp(a, b) != 0);
    /* a resolved frame whose name looks like an unresolved encoding is still a different frame */
    h[0] = frame("game", "x", 0, true);
    h[1] = frame("game", "", 0, false);
    ASSERT_TRUE(break_crash_signature(11, h, 2u, c));
    ASSERT_TRUE(strcmp(c, a) != 0);
    /* a frame with no module at all */
    {
        BreakCrashFrame z[1];
        z[0] = frame("", "", 0, false);
        ASSERT_TRUE(break_crash_signature(11, z, 1u, c));
        ASSERT_TRUE(strcmp(c, a) != 0);
    }
    /* frame boundaries cannot be forged: ("a","bc") vs ("ab","c") */
    {
        BreakCrashFrame p[1], q[1];
        p[0] = frame("a", "bc", 0, true);
        q[0] = frame("ab", "c", 0, true);
        ASSERT_TRUE(break_crash_signature(11, p, 1u, a));
        ASSERT_TRUE(break_crash_signature(11, q, 1u, b));
        ASSERT_TRUE(strcmp(a, b) != 0);
    }
}

TEST(signature_rejects_bad_arguments) {
    char out[65];
    BreakCrashFrame f[1];
    f[0] = frame("game", "leaf", 1, true);
    ASSERT_FALSE(break_crash_signature(0, f, 1u, out));
    ASSERT_FALSE(break_crash_signature(-1, f, 1u, out));
    ASSERT_FALSE(break_crash_signature(65, f, 1u, out));
    ASSERT_FALSE(break_crash_signature(11, f, 1u, NULL));
    ASSERT_FALSE(break_crash_signature(11, NULL, 1u, out));
    ASSERT_TRUE(break_crash_signature(11, NULL, 0u, out));    /* a crash with no frames still has a signature */
    ASSERT_TRUE(break_crash_signature(64, f, 1u, out));
}

/* --------------------------------------------------------------------- counting */

static BreakCrashClusterStore *fresh(void) {
    BreakCrashClusterStore *s = break_crash_cluster_open("/nonexistent-dir-for-cluster-tests/stats");
    /* a missing file in a missing directory is still "no file": an empty store */
    return s;
}

TEST(a_missing_file_is_an_empty_store) {
    BreakCrashClusterStore *s = fresh();
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_cluster_signature_count(s), 0u);
    ASSERT_EQ(break_crash_cluster_build_count(s), 0u);
    break_crash_cluster_destroy(s);
}

TEST(reports_are_counted_per_signature_and_duplicates_are_not_counted_twice) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    u64 cnt = 0;
    bool reg = true;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "build-1"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), hx('a'), "build-1", "leaf", &o));
    ASSERT_TRUE(o.new_signature);
    ASSERT_FALSE(o.duplicate);
    ASSERT_EQ(o.count, 1u);
    ASSERT_TRUE(break_crash_cluster_add(s, hx('2'), hx('a'), "build-1", "leaf", &o));
    ASSERT_FALSE(o.new_signature);
    ASSERT_EQ(o.count, 2u);
    /* the same record again */
    ASSERT_TRUE(break_crash_cluster_add(s, hx('2'), hx('a'), "build-1", "leaf", &o));
    ASSERT_TRUE(o.duplicate);
    ASSERT_EQ(o.count, 2u);
    ASSERT_TRUE(break_crash_cluster_add(s, hx('3'), hx('b'), "build-1", NULL, &o));
    ASSERT_TRUE(o.new_signature);
    ASSERT_EQ(break_crash_cluster_signature_count(s), 2u);
    ASSERT_TRUE(break_crash_cluster_find(s, hx('a'), &cnt, &reg));
    ASSERT_EQ(cnt, 2u);
    ASSERT_FALSE(reg);
    ASSERT_FALSE(break_crash_cluster_find(s, hx('c'), &cnt, &reg));
    break_crash_cluster_destroy(s);
}

TEST(an_unregistered_build_changes_nothing) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "build-1"));
    ASSERT_FALSE(break_crash_cluster_add(s, hx('1'), hx('a'), "build-9", "leaf", &o));
    ASSERT_TRUE(o.unknown_build);
    ASSERT_EQ(break_crash_cluster_signature_count(s), 0u);
    /* and the rejected record hash was NOT remembered: once the build exists the same record counts */
    ASSERT_TRUE(break_crash_cluster_register_build(s, "build-9"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), hx('a'), "build-9", "leaf", &o));
    ASSERT_FALSE(o.duplicate);
    ASSERT_EQ(o.count, 1u);
    break_crash_cluster_destroy(s);
}

TEST(malformed_arguments_are_rejected_without_effect) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    char upper[65], shortsig[40];
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    memcpy(upper, hx('a'), 65u);
    upper[3] = 'A';
    snprintf(shortsig, sizeof(shortsig), "%s", hx('a'));
    ASSERT_FALSE(break_crash_cluster_add(s, upper, hx('a'), "b1", "x", &o));
    ASSERT_FALSE(break_crash_cluster_add(s, hx('1'), upper, "b1", "x", &o));
    ASSERT_FALSE(break_crash_cluster_add(s, shortsig, hx('a'), "b1", "x", &o));
    ASSERT_FALSE(break_crash_cluster_add(s, hx('1'), hx('a'), "B1", "x", &o));
    ASSERT_FALSE(break_crash_cluster_add(s, hx('1'), hx('a'), "", "x", &o));
    ASSERT_FALSE(break_crash_cluster_add(s, hx('1'), hx('a'), NULL, "x", &o));
    ASSERT_FALSE(break_crash_cluster_add(s, NULL, hx('a'), "b1", "x", &o));
    ASSERT_FALSE(break_crash_cluster_add(NULL, hx('1'), hx('a'), "b1", "x", &o));
    ASSERT_EQ(break_crash_cluster_signature_count(s), 0u);
    ASSERT_FALSE(break_crash_cluster_register_build(s, "b1"));       /* duplicate */
    ASSERT_FALSE(break_crash_cluster_register_build(s, "has space"));
    ASSERT_FALSE(break_crash_cluster_register_build(s, "UPPER"));
    ASSERT_FALSE(break_crash_cluster_register_build(s, ""));
    ASSERT_FALSE(break_crash_cluster_register_build(s, "../x"));
    {
        char longid[80];
        memset(longid, 'a', 65u);
        longid[65] = '\0';
        ASSERT_FALSE(break_crash_cluster_register_build(s, longid));
    }
    ASSERT_EQ(break_crash_cluster_build_count(s), 1u);
    break_crash_cluster_destroy(s);
}

/* ------------------------------------------------------------------ regressions */

TEST(a_crash_in_a_later_build_after_the_fix_is_a_regression) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    bool reg = false;
    u64 cnt = 0;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b2"));
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b3"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), hx('a'), "b1", "leaf", &o));
    ASSERT_TRUE(break_crash_cluster_mark_fixed(s, hx('a'), "b2"));
    /* old clients keep crashing after the fix shipped: not a regression */
    ASSERT_TRUE(break_crash_cluster_add(s, hx('2'), hx('a'), "b1", "leaf", &o));
    ASSERT_FALSE(o.regression_started);
    /* the build that carries the fix itself: not a regression either (the fix is "in" b2) */
    ASSERT_TRUE(break_crash_cluster_add(s, hx('3'), hx('a'), "b2", "leaf", &o));
    ASSERT_FALSE(o.regression_started);
    ASSERT_TRUE(break_crash_cluster_find(s, hx('a'), &cnt, &reg));
    ASSERT_FALSE(reg);
    ASSERT_EQ(cnt, 3u);
    /* a build released after the fix crashes the same way */
    ASSERT_TRUE(break_crash_cluster_add(s, hx('4'), hx('a'), "b3", "leaf", &o));
    ASSERT_TRUE(o.regression_started);
    ASSERT_TRUE(break_crash_cluster_find(s, hx('a'), &cnt, &reg));
    ASSERT_TRUE(reg);
    ASSERT_EQ(cnt, 4u);
    /* the flip is reported once */
    ASSERT_TRUE(break_crash_cluster_add(s, hx('5'), hx('a'), "b3", "leaf", &o));
    ASSERT_FALSE(o.regression_started);
    ASSERT_TRUE(break_crash_cluster_find(s, hx('a'), NULL, &reg));
    ASSERT_TRUE(reg);
    break_crash_cluster_destroy(s);
}

TEST(a_signature_never_marked_fixed_is_never_a_regression) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    bool reg = true;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b2"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), hx('a'), "b1", "leaf", &o));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('2'), hx('a'), "b2", "leaf", &o));
    ASSERT_FALSE(o.regression_started);
    ASSERT_TRUE(break_crash_cluster_find(s, hx('a'), NULL, &reg));
    ASSERT_FALSE(reg);
    break_crash_cluster_destroy(s);
}

TEST(marking_fixed_again_clears_the_regression_and_moves_the_fix_forward) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    bool reg = false;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b2"));
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b3"));
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b4"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), hx('a'), "b1", "leaf", &o));
    ASSERT_TRUE(break_crash_cluster_mark_fixed(s, hx('a'), "b2"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('2'), hx('a'), "b3", "leaf", &o));
    ASSERT_TRUE(o.regression_started);
    ASSERT_TRUE(break_crash_cluster_mark_fixed(s, hx('a'), "b3"));
    ASSERT_TRUE(break_crash_cluster_find(s, hx('a'), NULL, &reg));
    ASSERT_FALSE(reg);
    ASSERT_TRUE(break_crash_cluster_add(s, hx('3'), hx('a'), "b3", "leaf", &o));
    ASSERT_FALSE(o.regression_started);          /* b3 now carries the fix */
    ASSERT_TRUE(break_crash_cluster_add(s, hx('4'), hx('a'), "b4", "leaf", &o));
    ASSERT_TRUE(o.regression_started);           /* but b4 is later */
    break_crash_cluster_destroy(s);
}

TEST(marking_fixed_after_a_later_build_already_reported_it_is_a_regression_at_once) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    bool reg = false;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b2"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), hx('a'), "b1", "leaf", &o));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('2'), hx('a'), "b2", "leaf", &o));
    ASSERT_TRUE(break_crash_cluster_mark_fixed(s, hx('a'), "b1"));
    ASSERT_TRUE(break_crash_cluster_find(s, hx('a'), NULL, &reg));
    ASSERT_TRUE(reg);
    ASSERT_TRUE(break_crash_cluster_mark_fixed(s, hx('a'), "b2"));      /* the fix is declared at the later build */
    ASSERT_TRUE(break_crash_cluster_find(s, hx('a'), NULL, &reg));
    ASSERT_FALSE(reg);
    break_crash_cluster_destroy(s);
}

TEST(mark_fixed_needs_a_known_signature_and_a_registered_build) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), hx('a'), "b1", "leaf", &o));
    ASSERT_FALSE(break_crash_cluster_mark_fixed(s, hx('b'), "b1"));      /* unknown signature */
    ASSERT_FALSE(break_crash_cluster_mark_fixed(s, hx('a'), "nope"));    /* unregistered build */
    ASSERT_FALSE(break_crash_cluster_mark_fixed(s, "short", "b1"));
    ASSERT_FALSE(break_crash_cluster_mark_fixed(NULL, hx('a'), "b1"));
    ASSERT_TRUE(break_crash_cluster_mark_fixed(s, hx('a'), "b1"));
    break_crash_cluster_destroy(s);
}

/* ------------------------------------------------------------------ persistence */

static BreakCrashClusterStore *populated(void) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    if (s == NULL) return NULL;
    (void)break_crash_cluster_register_build(s, "b1");
    (void)break_crash_cluster_register_build(s, "b2");
    (void)break_crash_cluster_add(s, hx('1'), hx('b'), "b1", "leaf", &o);
    (void)break_crash_cluster_add(s, hx('2'), hx('a'), "b1", NULL, &o);
    (void)break_crash_cluster_add(s, hx('3'), hx('a'), "b2", NULL, &o);
    (void)break_crash_cluster_mark_fixed(s, hx('a'), "b1");
    return s;
}

TEST(a_store_survives_save_and_open_byte_for_byte) {
    char path[400], t1[8192], t2[8192];
    BreakCrashClusterStore *s = populated(), *r;
    usize n1, n2;
    bool reg = false;
    u64 cnt = 0;
    ASSERT_NOT_NULL(s);
    path_in(path, sizeof(path), "stats.txt");
    ASSERT_TRUE(break_crash_cluster_save(s, path));
    r = break_crash_cluster_open(path);
    ASSERT_NOT_NULL(r);
    n1 = break_crash_cluster_serialize(s, t1, sizeof(t1));
    n2 = break_crash_cluster_serialize(r, t2, sizeof(t2));
    ASSERT_TRUE(n1 > 0u);
    ASSERT_EQ(n1, n2);
    ASSERT_TRUE(memcmp(t1, t2, n1) == 0);
    ASSERT_TRUE(break_crash_cluster_find(r, hx('a'), &cnt, &reg));
    ASSERT_EQ(cnt, 2u);
    ASSERT_TRUE(reg);                              /* the regression flag survived */
    ASSERT_TRUE(break_crash_cluster_build_known(r, "b2"));
    /* the remembered record hashes survived: a repeated upload is still a duplicate */
    {
        BreakCrashClusterOutcome o;
        ASSERT_TRUE(break_crash_cluster_add(r, hx('3'), hx('a'), "b2", NULL, &o));
        ASSERT_TRUE(o.duplicate);
    }
    break_crash_cluster_destroy(r);
    break_crash_cluster_destroy(s);
}

TEST(a_failed_save_leaves_the_previous_file_untouched) {
    char path[400], before[8192], after[8192];
    BreakCrashClusterStore *s = populated();
    FILE *f;
    size_t nb, na;
    ASSERT_NOT_NULL(s);
    path_in(path, sizeof(path), "stats_keep.txt");
    ASSERT_TRUE(break_crash_cluster_save(s, path));
    f = fopen(path, "rb");
    ASSERT_NOT_NULL(f);
    nb = fread(before, 1u, sizeof(before), f);
    fclose(f);
    /* the directory vanishes: the writer cannot even open its temp file */
    ASSERT_FALSE(break_crash_cluster_save(s, "/nonexistent-dir-for-cluster-tests/x/stats"));
    f = fopen(path, "rb");
    ASSERT_NOT_NULL(f);
    na = fread(after, 1u, sizeof(after), f);
    fclose(f);
    ASSERT_EQ(nb, na);
    ASSERT_TRUE(memcmp(before, after, nb) == 0);
    ASSERT_FALSE(break_crash_cluster_save(NULL, path));
    ASSERT_FALSE(break_crash_cluster_save(s, ""));
    break_crash_cluster_destroy(s);
}

TEST(a_write_that_fails_part_way_leaves_the_previous_file_intact_and_reports_failure) {
    char path[400], before[8192], after[8192];
    BreakCrashClusterStore *s = populated();
    FILE *f;
    size_t nb, na;
    pid_t pid;
    int status = 0;
    ASSERT_NOT_NULL(s);
    path_in(path, sizeof(path), "stats_limit.txt");
    ASSERT_TRUE(break_crash_cluster_save(s, path));
    f = fopen(path, "rb");
    ASSERT_NOT_NULL(f);
    nb = fread(before, 1u, sizeof(before), f);
    fclose(f);
    ASSERT_TRUE(nb > 100u);
    /* a child with a 64-byte file size limit: the write fails with EFBIG part way through */
    pid = fork();
    ASSERT_TRUE(pid >= 0);
    if (pid == 0) {
        struct rlimit rl;
        rl.rlim_cur = 64u;
        rl.rlim_max = 64u;
        signal(SIGXFSZ, SIG_IGN);
        if (setrlimit(RLIMIT_FSIZE, &rl) != 0) _exit(2);
        _exit(break_crash_cluster_save(s, path) ? 1 : 0);
    }
    ASSERT_EQ(waitpid(pid, &status, 0), pid);
    ASSERT_TRUE(WIFEXITED(status));
    ASSERT_EQ(WEXITSTATUS(status), 0);               /* save reported failure */
    f = fopen(path, "rb");
    ASSERT_NOT_NULL(f);
    na = fread(after, 1u, sizeof(after), f);
    fclose(f);
    ASSERT_EQ(nb, na);
    ASSERT_TRUE(memcmp(before, after, nb) == 0);
    {
        BreakCrashClusterStore *r = break_crash_cluster_open(path);
        ASSERT_NOT_NULL(r);                           /* and it still parses */
        break_crash_cluster_destroy(r);
    }
    break_crash_cluster_destroy(s);
}

/* returns true when the mutated text is refused by the parser */
static bool refused(const char *text, usize len) {
    BreakCrashClusterStore *s = break_crash_cluster_parse(text, len);
    bool bad = s == NULL;
    break_crash_cluster_destroy(s);
    return bad;
}

TEST(the_parser_accepts_only_the_canonical_text) {
    char t[8192], m[8192];
    BreakCrashClusterStore *s = populated(), *ok;
    usize n;
    ASSERT_NOT_NULL(s);
    n = break_crash_cluster_serialize(s, t, sizeof(t));
    ASSERT_TRUE(n > 0u);
    ok = break_crash_cluster_parse(t, n);
    ASSERT_NOT_NULL(ok);
    break_crash_cluster_destroy(ok);
    /* every strict prefix is refused */
    for (usize k = 0u; k < n; k++) ASSERT_TRUE(refused(t, k));
    /* trailing bytes are refused */
    memcpy(m, t, n);
    m[n] = '\n';
    ASSERT_TRUE(refused(m, n + 1u));
    m[n] = 'x';
    ASSERT_TRUE(refused(m, n + 1u));
    /* changing any single byte to another printable byte is refused or reproduces the same text */
    {
        usize accepted_different = 0u;
        for (usize k = 0u; k < n; k++) {
            char saved = t[k];
            BreakCrashClusterStore *p;
            t[k] = saved == 'z' ? 'y' : 'z';
            p = break_crash_cluster_parse(t, n);
            if (p != NULL) {
                char again[8192];
                usize an = break_crash_cluster_serialize(p, again, sizeof(again));
                if (an != n || memcmp(again, t, n) != 0) accepted_different++;
                break_crash_cluster_destroy(p);
            }
            t[k] = saved;
        }
        ASSERT_EQ(accepted_different, 0u);
    }
    break_crash_cluster_destroy(s);
}

TEST(the_parser_rejects_structural_lies) {
    const char head[] = "break-crash-stats v1\n";
    char t[4096];
    int n;
    /* wrong header */
    ASSERT_TRUE(refused("break-crash-stats v2\nbuilds: 0\nseen: 0\nsignatures: 0\n", 52u));
    ASSERT_TRUE(refused("", 0u));
    ASSERT_TRUE(refused(NULL, 5u));
    /* the minimal valid file parses */
    n = snprintf(t, sizeof(t), "%sbuilds: 0\nseen: 0\nsignatures: 0\n", head);
    ASSERT_FALSE(refused(t, (usize)n));
    /* count lies */
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nseen: 0\nsignatures: 0\n", head);
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 99999\nseen: 0\nsignatures: 0\n", head);
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 0\nseen: 5000\nsignatures: 0\n", head);
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 0\nseen: 0\nsignatures: 5000\n", head);
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 00\nseen: 0\nsignatures: 0\n", head);
    ASSERT_TRUE(refused(t, (usize)n));       /* non-canonical number */
    n = snprintf(t, sizeof(t), "%sbuilds: -1\nseen: 0\nsignatures: 0\n", head);
    ASSERT_TRUE(refused(t, (usize)n));
    /* duplicate build ids */
    n = snprintf(t, sizeof(t), "%sbuilds: 2\nbuild: b1\nbuild: b1\nseen: 0\nsignatures: 0\n", head);
    ASSERT_TRUE(refused(t, (usize)n));
    /* a signature pointing at a build that does not exist */
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 1\nsig: %s 1 5 5 - 0 -\n", head, hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 1\nsig: %s 1 0 0 7 0 -\n", head, hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    /* signatures out of order / duplicated */
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 2\nsig: %s 1 0 0 - 0 -\nsig: %s 1 0 0 - 0 -\n",
                 head, hx('b'), hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 2\nsig: %s 1 0 0 - 0 -\nsig: %s 1 0 0 - 0 -\n",
                 head, hx('a'), hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    /* a regressed flag that is not 0/1; extra tokens; a missing token */
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 1\nsig: %s 1 0 0 - 2 -\n", head, hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 1\nsig: %s 1 0 0 - 0 - extra\n", head, hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 1\nsig: %s 1 0 0 - 0\n", head, hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    /* last build before first build, or outside the list */
    n = snprintf(t, sizeof(t), "%sbuilds: 2\nbuild: b1\nbuild: b2\nseen: 0\nsignatures: 1\nsig: %s 1 1 0 - 0 -\n", head, hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 1\nsig: %s 1 0 3 - 0 -\n", head, hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    /* a count that overflows 64 bits */
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 1\nsig: %s 99999999999999999999 0 0 - 0 -\n",
                 head, hx('a'));
    ASSERT_TRUE(refused(t, (usize)n));
    /* a well-formed one for contrast */
    n = snprintf(t, sizeof(t), "%sbuilds: 1\nbuild: b1\nseen: 0\nsignatures: 1\nsig: %s 7 0 0 0 1 leaf\n", head, hx('a'));
    ASSERT_FALSE(refused(t, (usize)n));
    /* CRLF and embedded NUL */
    n = snprintf(t, sizeof(t), "break-crash-stats v1\r\nbuilds: 0\r\nseen: 0\r\nsignatures: 0\r\n");
    ASSERT_TRUE(refused(t, (usize)n));
    n = snprintf(t, sizeof(t), "%sbuilds: 0\nseen: 0\nsignatures: 0\n", head);
    t[n - 3] = '\0';
    ASSERT_TRUE(refused(t, (usize)n));
}

TEST(opening_an_unreadable_or_garbage_file_fails_instead_of_resetting_the_statistics) {
    char path[400];
    FILE *f;
    path_in(path, sizeof(path), "garbage.txt");
    f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    fputs("not a statistics file\n", f);
    fclose(f);
    ASSERT_TRUE(break_crash_cluster_open(path) == NULL);
    path_in(path, sizeof(path), "empty.txt");
    f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    fclose(f);
    ASSERT_TRUE(break_crash_cluster_open(path) == NULL);       /* a truncated file is not "no file" */
    ASSERT_TRUE(break_crash_cluster_open(g_dir) == NULL);      /* a directory */
    ASSERT_TRUE(break_crash_cluster_open("") == NULL);
    ASSERT_TRUE(break_crash_cluster_open(NULL) == NULL);
}

/* --------------------------------------------------------------------- bounds */

TEST(the_signature_table_is_bounded_and_evicts_the_rarest) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    char sig[65], rec[65];
    u64 cnt = 0;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    for (u32 i = 0u; i < BREAK_CRASH_CLUSTER_MAX_SIGNATURES; i++) {
        snprintf(sig, sizeof(sig), "%064x", i + 1u);
        snprintf(rec, sizeof(rec), "%064x", 0x100000u + i);
        ASSERT_TRUE(break_crash_cluster_add(s, rec, sig, "b1", "f", &o));
        if (i != 0u) {      /* signature 1 stays the rarest: every other one is reported twice */
            snprintf(rec, sizeof(rec), "%064x", 0x200000u + i);
            ASSERT_TRUE(break_crash_cluster_add(s, rec, sig, "b1", "f", &o));
        }
    }
    ASSERT_EQ(break_crash_cluster_signature_count(s), BREAK_CRASH_CLUSTER_MAX_SIGNATURES);
    snprintf(sig, sizeof(sig), "%064x", 0xabcdefu);
    snprintf(rec, sizeof(rec), "%064x", 0x300000u);
    ASSERT_TRUE(break_crash_cluster_add(s, rec, sig, "b1", "f", &o));
    ASSERT_TRUE(o.new_signature);
    ASSERT_EQ(break_crash_cluster_signature_count(s), BREAK_CRASH_CLUSTER_MAX_SIGNATURES);
    snprintf(sig, sizeof(sig), "%064x", 1u);
    ASSERT_FALSE(break_crash_cluster_find(s, sig, &cnt, NULL));        /* the rarest was evicted */
    snprintf(sig, sizeof(sig), "%064x", 2u);
    ASSERT_TRUE(break_crash_cluster_find(s, sig, &cnt, NULL));
    ASSERT_EQ(cnt, 2u);
    {
        static char big[BREAK_CRASH_CLUSTER_FILE_MAX];
        usize n = break_crash_cluster_serialize(s, big, sizeof(big));
        BreakCrashClusterStore *r;
        ASSERT_TRUE(n > 0u && n < sizeof(big));
        r = break_crash_cluster_parse(big, n);          /* a full store still round trips */
        ASSERT_NOT_NULL(r);
        break_crash_cluster_destroy(r);
    }
    break_crash_cluster_destroy(s);
}

TEST(the_remembered_record_hashes_are_bounded_oldest_first) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    char rec[65];
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    for (u32 i = 0u; i < BREAK_CRASH_CLUSTER_MAX_SEEN + 1u; i++) {
        snprintf(rec, sizeof(rec), "%064x", i + 1u);
        ASSERT_TRUE(break_crash_cluster_add(s, rec, hx('a'), "b1", "f", &o));
        ASSERT_FALSE(o.duplicate);
    }
    snprintf(rec, sizeof(rec), "%064x", BREAK_CRASH_CLUSTER_MAX_SEEN + 1u);
    ASSERT_TRUE(break_crash_cluster_add(s, rec, hx('a'), "b1", "f", &o));
    ASSERT_TRUE(o.duplicate);                        /* the newest is still remembered */
    snprintf(rec, sizeof(rec), "%064x", 1u);
    ASSERT_TRUE(break_crash_cluster_add(s, rec, hx('a'), "b1", "f", &o));
    ASSERT_FALSE(o.duplicate);                       /* the oldest was forgotten, so it counts again */
    break_crash_cluster_destroy(s);
}

TEST(the_build_list_is_bounded) {
    BreakCrashClusterStore *s = fresh();
    char id[32];
    ASSERT_NOT_NULL(s);
    for (u32 i = 0u; i < BREAK_CRASH_CLUSTER_MAX_BUILDS; i++) {
        snprintf(id, sizeof(id), "b%u", i);
        ASSERT_TRUE(break_crash_cluster_register_build(s, id));
    }
    ASSERT_FALSE(break_crash_cluster_register_build(s, "one-too-many"));
    ASSERT_EQ(break_crash_cluster_build_count(s), BREAK_CRASH_CLUSTER_MAX_BUILDS);
    break_crash_cluster_destroy(s);
}

TEST(a_hostile_symbol_name_is_neutralised_before_it_reaches_the_file) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    char t[8192], *nl;
    usize n;
    BreakCrashClusterStore *r;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), hx('a'), "b1", "evil\nsig: injected line\x01 tail with spaces", &o));
    n = break_crash_cluster_serialize(s, t, sizeof(t));
    ASSERT_TRUE(n > 0u);
    t[n] = '\0';
    nl = strstr(t, "injected");
    ASSERT_NOT_NULL(nl);
    ASSERT_TRUE(strstr(t, "\nsig: injected") == NULL);          /* no forged line */
    r = break_crash_cluster_parse(t, n);
    ASSERT_NOT_NULL(r);                                         /* and the file still parses */
    break_crash_cluster_destroy(r);
    /* a name made only of "-" is the file's "none" marker and is stored as none */
    ASSERT_TRUE(break_crash_cluster_add(s, hx('2'), hx('b'), "b1", "-", &o));
    n = break_crash_cluster_serialize(s, t, sizeof(t));
    r = break_crash_cluster_parse(t, n);
    ASSERT_NOT_NULL(r);
    break_crash_cluster_destroy(r);
    /* a very long name is cut */
    {
        char longname[400];
        memset(longname, 'q', sizeof(longname) - 1u);
        longname[sizeof(longname) - 1u] = '\0';
        ASSERT_TRUE(break_crash_cluster_add(s, hx('3'), hx('c'), "b1", longname, &o));
        n = break_crash_cluster_serialize(s, t, sizeof(t));
        r = break_crash_cluster_parse(t, n);
        ASSERT_NOT_NULL(r);
        break_crash_cluster_destroy(r);
    }
    break_crash_cluster_destroy(s);
}

/* --------------------------------------------------------------------- report */

TEST(the_report_orders_by_count_then_signature_and_flags_regressions) {
    BreakCrashClusterStore *s = populated();
    char rep[4096];
    usize n;
    const char *p_a, *p_b;
    ASSERT_NOT_NULL(s);
    n = break_crash_cluster_report(s, rep, sizeof(rep));
    ASSERT_TRUE(n > 0u);
    ASSERT_EQ(strlen(rep), n);
    ASSERT_TRUE(strncmp(rep, "crash clusters: 2 signatures, 2 builds\n", 38u) == 0);
    p_a = strstr(rep, "aaaaaaaaaaaaaaaa");
    p_b = strstr(rep, "bbbbbbbbbbbbbbbb");
    ASSERT_NOT_NULL(p_a);
    ASSERT_NOT_NULL(p_b);
    ASSERT_TRUE(p_a < p_b);                         /* count 2 before count 1 */
    ASSERT_NOT_NULL(strstr(rep, "REGRESSED"));
    ASSERT_NOT_NULL(strstr(rep, "top=leaf"));
    ASSERT_NOT_NULL(strstr(rep, "fixed=b1"));
    ASSERT_EQ(break_crash_cluster_report(s, rep, 10u), 0u);      /* too small */
    ASSERT_EQ(break_crash_cluster_report(NULL, rep, sizeof(rep)), 0u);
    break_crash_cluster_destroy(s);
}

TEST(a_signature_prefix_resolves_only_when_it_is_long_enough_and_unambiguous) {
    BreakCrashClusterStore *s = fresh();
    BreakCrashClusterOutcome o;
    char full[65], sig_a[65], sig_b[65];
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_crash_cluster_register_build(s, "b1"));
    memcpy(sig_a, hx('a'), 65u);
    memcpy(sig_b, hx('a'), 65u);
    sig_b[12] = 'b';                         /* shares the first 12 characters with sig_a */
    ASSERT_TRUE(break_crash_cluster_add(s, hx('1'), sig_a, "b1", "x", &o));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('2'), sig_b, "b1", "x", &o));
    ASSERT_TRUE(break_crash_cluster_add(s, hx('3'), hx('c'), "b1", "x", &o));
    /* unique prefixes */
    ASSERT_TRUE(break_crash_cluster_resolve_prefix(s, "cccccccc", full));
    ASSERT_STR_EQ(full, hx('c'));
    ASSERT_TRUE(break_crash_cluster_resolve_prefix(s, "aaaaaaaaaaaaa", full));    /* 13 chars: sig_b differs at 12 */
    ASSERT_STR_EQ(full, sig_a);
    ASSERT_TRUE(break_crash_cluster_resolve_prefix(s, sig_b, full));              /* the full signature */
    ASSERT_STR_EQ(full, sig_b);
    /* ambiguous: both start with 12 a's */
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, "aaaaaaaaaaaa", full));
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, "aaaaaaaa", full));
    /* too short, not hex, uppercase, unknown, too long, NULL */
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, "ccccccc", full));
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, "", full));
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, "cccccccg", full));
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, "CCCCCCCC", full));
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, "dddddddd", full));
    {
        char longp[80];
        memset(longp, 'c', 65u);
        longp[65] = '\0';
        ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, longp, full));
    }
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, NULL, full));
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(s, "cccccccc", NULL));
    ASSERT_FALSE(break_crash_cluster_resolve_prefix(NULL, "cccccccc", full));
    break_crash_cluster_destroy(s);
}

/* ----------------------------------------------------------------------- lock */

TEST(the_lock_excludes_a_second_process_until_it_is_released) {
    char path[400];
    BreakCrashClusterLock *l;
    int pipefd[2];
    pid_t pid;
    char got = 0;
    path_in(path, sizeof(path), "locked.txt");
    l = break_crash_cluster_lock(path);
    ASSERT_NOT_NULL(l);
    ASSERT_EQ(pipe(pipefd), 0);
    pid = fork();
    ASSERT_TRUE(pid >= 0);
    if (pid == 0) {
        BreakCrashClusterLock *l2 = break_crash_cluster_lock(path);   /* blocks until the parent unlocks */
        char c = l2 != NULL ? 'k' : 'f';
        (void)!write(pipefd[1], &c, 1u);
        break_crash_cluster_unlock(l2);
        _exit(0);
    }
    usleep(150000);
    ASSERT_EQ(waitpid(pid, NULL, WNOHANG), 0);          /* the child is still blocked */
    break_crash_cluster_unlock(l);
    ASSERT_EQ(read(pipefd[0], &got, 1u), 1);
    ASSERT_EQ(got, 'k');
    ASSERT_EQ(waitpid(pid, NULL, 0), pid);
    close(pipefd[0]);
    close(pipefd[1]);
    break_crash_cluster_unlock(NULL);
    ASSERT_TRUE(break_crash_cluster_lock("") == NULL);
    ASSERT_TRUE(break_crash_cluster_lock(NULL) == NULL);
}

static void cleanup(void) {
    char cmd[400];
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'", g_dir);
    (void)system(cmd);
}

TEST_MAIN_BEGIN()
    dir_init();
    RUN_TEST(a_signature_is_stable_and_ignores_addresses_and_processes);
    RUN_TEST(a_signature_depends_on_signal_and_the_top_three_frames_only);
    RUN_TEST(an_unresolved_frame_is_identified_by_module_and_offset_and_frames_do_not_collide);
    RUN_TEST(signature_rejects_bad_arguments);
    RUN_TEST(a_missing_file_is_an_empty_store);
    RUN_TEST(reports_are_counted_per_signature_and_duplicates_are_not_counted_twice);
    RUN_TEST(an_unregistered_build_changes_nothing);
    RUN_TEST(malformed_arguments_are_rejected_without_effect);
    RUN_TEST(a_crash_in_a_later_build_after_the_fix_is_a_regression);
    RUN_TEST(a_signature_never_marked_fixed_is_never_a_regression);
    RUN_TEST(marking_fixed_again_clears_the_regression_and_moves_the_fix_forward);
    RUN_TEST(marking_fixed_after_a_later_build_already_reported_it_is_a_regression_at_once);
    RUN_TEST(mark_fixed_needs_a_known_signature_and_a_registered_build);
    RUN_TEST(a_store_survives_save_and_open_byte_for_byte);
    RUN_TEST(a_failed_save_leaves_the_previous_file_untouched);
    RUN_TEST(a_write_that_fails_part_way_leaves_the_previous_file_intact_and_reports_failure);
    RUN_TEST(the_parser_accepts_only_the_canonical_text);
    RUN_TEST(the_parser_rejects_structural_lies);
    RUN_TEST(opening_an_unreadable_or_garbage_file_fails_instead_of_resetting_the_statistics);
    RUN_TEST(the_signature_table_is_bounded_and_evicts_the_rarest);
    RUN_TEST(the_remembered_record_hashes_are_bounded_oldest_first);
    RUN_TEST(the_build_list_is_bounded);
    RUN_TEST(a_hostile_symbol_name_is_neutralised_before_it_reaches_the_file);
    RUN_TEST(the_report_orders_by_count_then_signature_and_flags_regressions);
    RUN_TEST(a_signature_prefix_resolves_only_when_it_is_long_enough_and_unambiguous);
    RUN_TEST(the_lock_excludes_a_second_process_until_it_is_released);
    cleanup();
TEST_MAIN_END()
