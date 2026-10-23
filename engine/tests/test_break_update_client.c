/* ==========================================================================
 *  test_break_update_client.c — Stage 5 Phase B Task 1 tests: update client
 *  state machine + A/B slot layout (no download — fetch/stage/activate/
 *  unstage are Tasks 2/3 and do not exist yet).
 *
 *  Pins: fresh-open layout + byte-exact initial state; reopen round-trips;
 *  corrupt-state battery → open NULL (truncated / unknown key / bad value /
 *  cross-field nonsense / charset / >64 KiB — no heuristic repair);
 *  confirm_boot without pending → false (+STATE); confirm_boot success
 *  persists-first; rollback three refusal paths (no previous → STATE, below
 *  min-rollback → POLICY, staged exists → STATE) + success flip/swap; every
 *  op leaves zero PlatformAtomicWriter tmp residue; write-ahead failure
 *  injection (state path replaced by a directory → persist false + IO,
 *  in-memory state untouched, tmp unlinked, op retryable after repair);
 *  NULL-arg matrix.
 * ========================================================================== */

#include "test_framework.h"

#include <update/break_update_client.h>
#include <platform/platform_fs.h>

#include <string.h>
#include <sys/stat.h> /* mkdir declaration for TEST_MKDIR (test_platform_fs_write precedent) */

/* Byte-exact initial state, pinned against the implementation's own copy. */
static const char INITIAL_STATE[] =
    "break-update-state-v1\n"
    "current: none\n"
    "staged: none\n"
    "pending: no\n"
    "confirmed: no\n"
    "current-version: none\n"
    "previous-version: none\n"
    "min-rollback-version: 0.0.0\n"
    "resume-chunk: none\n";

/* Line macros keep the corrupt battery compact: a variant swaps ONE line. */
#define L_MAGIC  "break-update-state-v1\n"
#define L_CUR_N  "current: none\n"
#define L_STG_N  "staged: none\n"
#define L_PEND_N "pending: no\n"
#define L_CONF_N "confirmed: no\n"
#define L_CVER_N "current-version: none\n"
#define L_PVER_N "previous-version: none\n"
#define L_MINRB  "min-rollback-version: 0.0.0\n"
#define L_RES_N  "resume-chunk: none\n"

#define HASH64 \
    "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"

/* ---- helpers ------------------------------------------------------------ */

static void join_path(char *out, usize cap, const char *dir, const char *leaf) {
    int r = snprintf(out, cap, "%s/%s", dir, leaf);
    if (r < 0 || (usize)r >= cap) {
        printf("  FATAL: path overflow in test helper\n");
        exit(2);
    }
}

static bool write_file(const char *path, const void *data, usize len) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return false;
    bool ok = fwrite(data, 1, len, fp) == len;
    if (fclose(fp) != 0) ok = false;
    return ok;
}

/* Exact-size byte comparison against a NUL-terminated expectation. */
static bool file_bytes_equal(const char *path, const char *expect) {
    u64 size = 0;
    if (!platform_file_size(path, &size)) return false;
    usize elen = strlen(expect);
    if (size != (u64)elen) return false;
    u8 *buf = malloc(size ? (usize)size : 1);
    if (!buf) return false;
    usize got = 0;
    FILE *fp = fopen(path, "rb");
    if (fp) {
        if (size) got = fread(buf, 1, (usize)size, fp);
        fclose(fp);
    }
    bool ok = fp && got == (usize)size && memcmp(buf, expect, elen) == 0;
    free(buf);
    return ok;
}

/* No PlatformAtomicWriter residue ("<path>.tmpXXXXXX") anywhere in root. */
static bool dir_has_tmp(const char *dir) {
    PlatformDirEntry entries[16];
    u32 count = 0;
    if (!platform_list_dir(dir, entries, 16, &count)) return false;
    u32 i;
    for (i = 0; i < count && i < 16; i++) {
        if (strstr(entries[i].name, ".tmp")) return true;
    }
    return false;
}

/* Best-effort teardown of the fixed Task 1 layout (state may be a file or,
 * after the failure-injection test, already gone; remove() handles both on
 * POSIX and TEST_RMDIR covers the directory case). */
static void cleanup_root(const char *root) {
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    remove(p);
    TEST_RMDIR(p);
    join_path(p, sizeof(p), root, "chunks");
    TEST_RMDIR(p);
    join_path(p, sizeof(p), root, "slots/A");
    TEST_RMDIR(p);
    join_path(p, sizeof(p), root, "slots/B");
    TEST_RMDIR(p);
    join_path(p, sizeof(p), root, "slots");
    TEST_RMDIR(p);
    TEST_RMDIR(root);
}

/* Writes <text> as <root>/state, opens the client, tears everything down.
 * Returns true when open succeeded. */
static int g_bad_counter = 0;

static bool state_bytes_open(const void *text, usize len) {
    char root[512];
    char name[64];
    snprintf(name, sizeof(name), "upc_bad_%d", g_bad_counter++);
    test_tmp(root, sizeof(root), name);
    TEST_MKDIR(root);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    if (!write_file(p, text, len)) {
        printf("  FATAL: battery fixture write failed\n");
        exit(2);
    }
    BreakUpdateClient *c = break_update_client_open(root);
    bool opened = c != NULL;
    break_update_client_destroy(c);
    cleanup_root(root);
    return opened;
}

static bool state_lines_open(const char *magic, const char *current, const char *staged,
                             const char *pending, const char *confirmed, const char *cver,
                             const char *pver, const char *minrb, const char *resume) {
    char buf[1024];
    int r = snprintf(buf, sizeof(buf), "%s%s%s%s%s%s%s%s%s", magic, current, staged,
                     pending, confirmed, cver, pver, minrb, resume);
    if (r < 0 || (usize)r >= sizeof(buf)) {
        printf("  FATAL: battery line overflow\n");
        exit(2);
    }
    return state_bytes_open(buf, (usize)r);
}

/* Writes a crafted state, opens, and keeps the client + root for the test. */
static BreakUpdateClient *open_with_state(char *root, usize root_cap, const char *name,
                                          const char *state_text) {
    test_tmp(root, root_cap, name);
    TEST_MKDIR(root);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    if (!write_file(p, state_text, strlen(state_text))) {
        printf("  FATAL: fixture write failed\n");
        exit(2);
    }
    return break_update_client_open(root);
}

/* ---- fresh open ---------------------------------------------------------- */

TEST(fresh_open_layout_and_initial_state) {
    char root[512];
    test_tmp(root, sizeof(root), "upc_fresh");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);

    /* Layout: root = {chunks/ (dir), slots/ (dir), state (file)}. */
    PlatformDirEntry entries[8];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 8, &count));
    ASSERT_EQ(count, 3u);
    bool saw_chunks = false, saw_slots = false, saw_state = false;
    u32 i;
    for (i = 0; i < count && i < 8; i++) {
        if (strcmp(entries[i].name, "chunks") == 0) {
            saw_chunks = true;
            ASSERT_TRUE(entries[i].is_dir);
        } else if (strcmp(entries[i].name, "slots") == 0) {
            saw_slots = true;
            ASSERT_TRUE(entries[i].is_dir);
        } else if (strcmp(entries[i].name, "state") == 0) {
            saw_state = true;
            ASSERT_FALSE(entries[i].is_dir);
        }
    }
    ASSERT_TRUE(saw_chunks && saw_slots && saw_state);

    char p[1200];
    join_path(p, sizeof(p), root, "chunks");
    ASSERT_TRUE(platform_list_dir(p, NULL, 0, &count));
    ASSERT_EQ(count, 0u);
    join_path(p, sizeof(p), root, "slots");
    ASSERT_TRUE(platform_list_dir(p, entries, 8, &count));
    ASSERT_EQ(count, 2u);
    bool saw_a = false, saw_b = false;
    for (i = 0; i < count && i < 8; i++) {
        if (strcmp(entries[i].name, "A") == 0) {
            saw_a = true;
            ASSERT_TRUE(entries[i].is_dir);
        } else if (strcmp(entries[i].name, "B") == 0) {
            saw_b = true;
            ASSERT_TRUE(entries[i].is_dir);
        }
    }
    ASSERT_TRUE(saw_a && saw_b);
    join_path(p, sizeof(p), root, "slots/A");
    ASSERT_TRUE(platform_list_dir(p, NULL, 0, &count));
    ASSERT_EQ(count, 0u);
    join_path(p, sizeof(p), root, "slots/B");
    ASSERT_TRUE(platform_list_dir(p, NULL, 0, &count));
    ASSERT_EQ(count, 0u);

    /* Queries on a fresh install. */
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    ASSERT_FALSE(break_update_client_pending(c));
    ASSERT_FALSE(break_update_client_confirmed(c));
    u32 v[3] = {9, 9, 9};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 0u);
    ASSERT_EQ(v[1], 0u);
    ASSERT_EQ(v[2], 0u);
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);

    /* Byte-exact initial state file + no writer tmp residue. */
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));
    ASSERT_FALSE(dir_has_tmp(root));

    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(reopen_roundtrip) {
    char root[512];
    test_tmp(root, sizeof(root), "upc_reopen");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    break_update_client_destroy(c);

    /* Reopen: parses the persisted initial state, rewrites nothing. */
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    ASSERT_FALSE(break_update_client_pending(c));
    ASSERT_FALSE(break_update_client_confirmed(c));
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);

    /* Third open: stable. */
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(crafted_state_reopen) {
    static const char crafted[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        "pending: yes\n"
        L_CONF_N
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        "resume-chunk: " HASH64 "|4096\n";
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_crafted", crafted);
    ASSERT_NOT_NULL(c);
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    ASSERT_TRUE(break_update_client_pending(c));
    ASSERT_FALSE(break_update_client_confirmed(c));
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 1u);
    ASSERT_EQ(v[1], 2u);
    ASSERT_EQ(v[2], 3u);
    break_update_client_destroy(c);

    /* Open never rewrites a valid state file; the reopen sees the same. */
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, crafted));
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    ASSERT_TRUE(break_update_client_pending(c));
    break_update_client_destroy(c);
    cleanup_root(root);
}

/* ---- corrupt / oversize state → open NULL (fail closed, no repair) ------- */

TEST(corrupt_state_battery) {
    /* Harness sanity: the initial state itself opens. */
    ASSERT_TRUE(state_bytes_open(INITIAL_STATE, strlen(INITIAL_STATE)));

    /* Truncation / framing. */
    ASSERT_FALSE(state_bytes_open(INITIAL_STATE, 40)); /* mid-file cut */
    ASSERT_FALSE(state_bytes_open(INITIAL_STATE, strlen(INITIAL_STATE) - 1)); /* no final LF */
    ASSERT_FALSE(state_bytes_open("", 0));

    /* Wrong magic. */
    ASSERT_FALSE(state_lines_open("break-update-state-v2\n", L_CUR_N, L_STG_N, L_PEND_N,
                                  L_CONF_N, L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open("break-manifest-v1\n", L_CUR_N, L_STG_N, L_PEND_N,
                                  L_CONF_N, L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));

    /* Unknown key (line 2) and trailing extra line. */
    ASSERT_FALSE(state_lines_open(L_MAGIC, "cuurent: none\n", L_STG_N, L_PEND_N,
                                  L_CONF_N, L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_bytes_open(
        L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB L_RES_N
        "extra: 1\n", strlen(L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N
                            L_MINRB L_RES_N "extra: 1\n")));
    /* Missing last line (8 of 9). */
    ASSERT_FALSE(state_bytes_open(
        L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB,
        strlen(L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB)));
    /* Duplicate key (second "current" where "staged" belongs). */
    ASSERT_FALSE(state_bytes_open(
        L_MAGIC L_CUR_N L_CUR_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB L_RES_N,
        strlen(L_MAGIC L_CUR_N L_CUR_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB
               L_RES_N)));

    /* Bad values. */
    ASSERT_FALSE(state_lines_open(L_MAGIC, "current: C\n", L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, "current: a\n", L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, "current: A \n", L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N)); /* trailing sp */
    ASSERT_FALSE(state_lines_open(L_MAGIC, "current : none\n", L_STG_N, L_PEND_N,
                                  L_CONF_N, L_CVER_N, L_PVER_N, L_MINRB, L_RES_N)); /* bad sep */
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, "staged: non\n", L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, "pending: YES\n", L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, "confirmed: yesplease\n",
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  "current-version: 01.2.3\n", L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  "current-version: 1.2\n", L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, "min-rollback-version: none\n", L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, "min-rollback-version: 1.2.3.4\n", L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, "min-rollback-version: 4294967296.0.0\n",
                                  L_RES_N)); /* u32 overflow */

    /* resume-chunk grammar. */
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB, "resume-chunk: abc\n"));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB,
                                  "resume-chunk: " HASH64 "\n")); /* no |offset */
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB,
                                  "resume-chunk: " HASH64 "|01\n")); /* leading zero */
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB,
                                  "resume-chunk: " HASH64 "|18446744073709551616\n")); /* u64 overflow */
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB,
                                  "resume-chunk: "
                                  "0123456789ABCDEF0123456789abcdef0123456789abcdef0123456789abcdef"
                                  "|0\n")); /* uppercase hex */

    /* Cross-field invariants (states no legal transition produces). */
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  "current-version: 1.0.0\n", L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, "current: A\n", L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, L_CONF_N,
                                  L_CVER_N, "previous-version: 1.0.0\n", L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, "current: A\n", L_STG_N, "pending: yes\n",
                                  "confirmed: yes\n", "current-version: 1.0.0\n",
                                  L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, "pending: yes\n", L_CONF_N,
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));
    ASSERT_FALSE(state_lines_open(L_MAGIC, L_CUR_N, L_STG_N, L_PEND_N, "confirmed: yes\n",
                                  L_CVER_N, L_PVER_N, L_MINRB, L_RES_N));

    /* Charset: CR, TAB, >=0x80, NUL. */
    ASSERT_FALSE(state_bytes_open(
        L_MAGIC "current: none\r\n" L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB L_RES_N,
        strlen(L_MAGIC "current: none\r\n" L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB
               L_RES_N)));
    ASSERT_FALSE(state_bytes_open(
        L_MAGIC L_CUR_N L_STG_N "pending:\tyes\n" L_CONF_N L_CVER_N L_PVER_N L_MINRB L_RES_N,
        strlen(L_MAGIC L_CUR_N L_STG_N "pending:\tyes\n" L_CONF_N L_CVER_N L_PVER_N L_MINRB
               L_RES_N)));
    ASSERT_FALSE(state_bytes_open(
        L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB
        "resume-chunk: non\xC3\xA9\n",
        strlen(L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB
               "resume-chunk: non\xC3\xA9\n")));
    {
        static const char with_nul[] =
            L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB L_RES_N;
        char buf[sizeof(with_nul)];
        memcpy(buf, with_nul, sizeof(with_nul));
        buf[10] = '\0'; /* NUL inside the magic line region */
        ASSERT_FALSE(state_bytes_open(buf, sizeof(with_nul) - 1));
    }
}

TEST(oversize_state_null) {
    const usize big = 64u * 1024u + 1u;
    u8 *buf = malloc(big);
    ASSERT_NOT_NULL(buf);
    memset(buf, 'a', big);
    ASSERT_FALSE(state_bytes_open(buf, big)); /* >64 KiB rejected pre-parse */
    free(buf);
}

/* ---- confirm_boot --------------------------------------------------------- */

TEST(confirm_boot_no_pending) {
    /* Fresh install: pending=no → false + STATE, state file untouched. */
    char root[512];
    test_tmp(root, sizeof(root), "upc_conf_nopend");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(break_update_client_confirm_boot(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_FALSE(break_update_client_confirmed(c));
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);
    cleanup_root(root);

    /* Already confirmed (pending=no, confirmed=yes) → still false + STATE. */
    static const char confirmed_state[] =
        L_MAGIC
        "current: A\n"
        L_STG_N
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.0.0\n"
        L_PVER_N
        L_MINRB
        L_RES_N;
    c = open_with_state(root, sizeof(root), "upc_conf_again", confirmed_state);
    ASSERT_NOT_NULL(c);
    join_path(p, sizeof(p), root, "state");
    ASSERT_FALSE(break_update_client_confirm_boot(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_TRUE(file_bytes_equal(p, confirmed_state));
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(confirm_boot_success) {
    static const char pending_state[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        "pending: yes\n"
        L_CONF_N
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    static const char confirmed_state[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_conf_ok", pending_state);
    ASSERT_NOT_NULL(c);
    ASSERT_TRUE(break_update_client_pending(c));

    ASSERT_TRUE(break_update_client_confirm_boot(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_FALSE(break_update_client_pending(c));
    ASSERT_TRUE(break_update_client_confirmed(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 1u);
    ASSERT_EQ(v[1], 2u);
    ASSERT_EQ(v[2], 3u);

    /* Persisted BEFORE the visible effect — the on-disk state already shows
     * the confirmation, byte-exact. */
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, confirmed_state));
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);

    /* Persistence round-trip across reopen. */
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(break_update_client_pending(c));
    ASSERT_TRUE(break_update_client_confirmed(c));
    break_update_client_destroy(c);
    cleanup_root(root);
}

/* ---- rollback -------------------------------------------------------------- */

TEST(rollback_no_previous) {
    /* Fresh install: no previous slot → false + STATE. */
    char root[512];
    test_tmp(root, sizeof(root), "upc_rb_fresh");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);
    cleanup_root(root);

    /* Live slot, previous-version=none (first update confirmed) → false. */
    static const char no_prev[] =
        L_MAGIC
        "current: A\n"
        L_STG_N
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.2.3\n"
        L_PVER_N
        L_MINRB
        L_RES_N;
    c = open_with_state(root, sizeof(root), "upc_rb_noprev", no_prev);
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, no_prev)); /* refused op persists nothing */
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(rollback_below_min_policy) {
    static const char state[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.2.3\n"
        "previous-version: 0.9.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_rb_floor", state);
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_POLICY);
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 1u);
    ASSERT_EQ(v[2], 3u);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, state));
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(rollback_with_staged_state) {
    static const char state[] =
        L_MAGIC
        "current: B\n"
        "staged: A\n"
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_rb_staged", state);
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, state));
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(rollback_success) {
    /* Pre-confirm boot of B (previous A 1.1.0): rollback flips back. */
    static const char before[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        "pending: yes\n"
        L_CONF_N
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    static const char after[] =
        L_MAGIC
        "current: A\n"
        L_STG_N
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.1.0\n"
        "previous-version: 1.2.3\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_rb_ok", before);
    ASSERT_NOT_NULL(c);
    ASSERT_TRUE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_EQ(break_update_client_current_slot(c), 'A');      /* slot flipped */
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 1u);
    ASSERT_EQ(v[1], 1u);
    ASSERT_EQ(v[2], 0u);                                      /* version swapped */
    ASSERT_FALSE(break_update_client_pending(c));             /* pending cleared */
    ASSERT_TRUE(break_update_client_confirmed(c));            /* known-good slot */
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, after));
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);

    /* Persistence across reopen; the previous/current roles are exchanged. */
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    ASSERT_TRUE(break_update_client_confirmed(c));
    break_update_client_destroy(c);
    cleanup_root(root);

    /* Boundary: previous == min-rollback floor is allowed (>= policy). */
    static const char at_floor[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.2.3\n"
        "previous-version: 1.0.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    c = open_with_state(root, sizeof(root), "upc_rb_eqfloor", at_floor);
    ASSERT_NOT_NULL(c);
    ASSERT_TRUE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    break_update_client_destroy(c);
    cleanup_root(root);
}

/* ---- write-ahead failure injection ---------------------------------------- */

TEST(persist_failure_write_ahead) {
    /* A pending state, then the state path is replaced by a DIRECTORY:
     * commit's rename(tmp → state) fails (POSIX ENOTDIR; Win32 MoveFileEx
     * refuses dirs) → the op reports IO, memory is untouched, the tmp is
     * unlinked, and after repair the op succeeds (no wedge). */
    static const char pending_state[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        "pending: yes\n"
        L_CONF_N
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_fail_conf", pending_state);
    ASSERT_NOT_NULL(c);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_EQ(remove(p), 0);
    ASSERT_EQ(TEST_MKDIR(p), 0);
    ASSERT_FALSE(break_update_client_confirm_boot(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_IO);
    ASSERT_TRUE(break_update_client_pending(c));    /* memory untouched */
    ASSERT_FALSE(break_update_client_confirmed(c));
    ASSERT_FALSE(dir_has_tmp(root));                /* tmp unlinked by the PAL */
    ASSERT_EQ(TEST_RMDIR(p), 0);
    ASSERT_TRUE(break_update_client_confirm_boot(c)); /* retry after repair */
    ASSERT_TRUE(break_update_client_confirmed(c));
    break_update_client_destroy(c);
    cleanup_root(root);

    /* Same injection against rollback. */
    static const char confirmed_b[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    c = open_with_state(root, sizeof(root), "upc_fail_rb", confirmed_b);
    ASSERT_NOT_NULL(c);
    join_path(p, sizeof(p), root, "state");
    ASSERT_EQ(remove(p), 0);
    ASSERT_EQ(TEST_MKDIR(p), 0);
    ASSERT_FALSE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_IO);
    ASSERT_EQ(break_update_client_current_slot(c), 'B'); /* flip never happened */
    ASSERT_FALSE(dir_has_tmp(root));
    ASSERT_EQ(TEST_RMDIR(p), 0);
    ASSERT_TRUE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    break_update_client_destroy(c);
    cleanup_root(root);
}

/* ---- open path rejections ---------------------------------------------------- */

TEST(open_path_rejections) {
    ASSERT_TRUE(break_update_client_open(NULL) == NULL);
    ASSERT_TRUE(break_update_client_open("") == NULL);

    char root[512];
    test_tmp(root, sizeof(root), "upc_openrej");

    /* root collides with an existing FILE → NULL. */
    ASSERT_TRUE(write_file(root, "x", 1));
    ASSERT_TRUE(break_update_client_open(root) == NULL);
    remove(root);

    /* Over-long root: "<root>/state" + the writer's ".tmpXXXXXX" + NUL must
     * stay below PLATFORM_FS_PATH_CAPACITY → reject beyond that. */
    char long_root[1200];
    memset(long_root, 'a', sizeof(long_root) - 1);
    long_root[sizeof(long_root) - 1] = '\0';
    ASSERT_TRUE(break_update_client_open(long_root) == NULL);

    /* state path occupied by a DIRECTORY → persist of the initial state
     * fails closed (rename refuses) → NULL, no tmp residue. */
    TEST_MKDIR(root);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_EQ(TEST_MKDIR(p), 0);
    ASSERT_TRUE(break_update_client_open(root) == NULL);
    ASSERT_FALSE(dir_has_tmp(root));
    ASSERT_EQ(TEST_RMDIR(p), 0);
    cleanup_root(root);
}

/* ---- tmp residue across an op sequence -------------------------------------- */

TEST(no_tmp_residue) {
    static const char pending_state[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        "pending: yes\n"
        L_CONF_N
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        L_RES_N;
    char root[512];
    test_tmp(root, sizeof(root), "upc_notmp");
    BreakUpdateClient *c = break_update_client_open(root); /* fresh persist */
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);

    c = open_with_state(root, sizeof(root), "upc_notmp2", pending_state);
    ASSERT_NOT_NULL(c);
    ASSERT_TRUE(break_update_client_confirm_boot(c));   /* op 1 */
    ASSERT_FALSE(dir_has_tmp(root));
    ASSERT_TRUE(break_update_client_rollback(c));       /* op 2 */
    ASSERT_FALSE(dir_has_tmp(root));
    ASSERT_FALSE(break_update_client_confirm_boot(c));  /* refused op: no write */
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);
    ASSERT_FALSE(dir_has_tmp(root));
    cleanup_root(root);
}

/* ---- NULL-arg matrix --------------------------------------------------------- */

TEST(null_arg_matrix) {
    ASSERT_EQ(break_update_client_current_slot(NULL), '-');
    ASSERT_FALSE(break_update_client_pending(NULL));
    ASSERT_FALSE(break_update_client_confirmed(NULL));
    u32 v[3] = {7, 7, 7};
    break_update_client_current_version(NULL, v);
    ASSERT_EQ(v[0], 0u);
    ASSERT_EQ(v[1], 0u);
    ASSERT_EQ(v[2], 0u);
    break_update_client_current_version(NULL, NULL); /* no crash */
    ASSERT_EQ(break_update_client_last_error(NULL), BREAK_UPDATE_CLIENT_INVALID);
    ASSERT_FALSE(break_update_client_confirm_boot(NULL));
    ASSERT_FALSE(break_update_client_rollback(NULL));
    break_update_client_destroy(NULL); /* no crash */

    char root[512];
    test_tmp(root, sizeof(root), "upc_nullmatrix");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    break_update_client_current_version(c, NULL); /* no crash, no effect */
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST_MAIN_BEGIN()
    RUN_TEST(fresh_open_layout_and_initial_state);
    RUN_TEST(reopen_roundtrip);
    RUN_TEST(crafted_state_reopen);
    RUN_TEST(corrupt_state_battery);
    RUN_TEST(oversize_state_null);
    RUN_TEST(confirm_boot_no_pending);
    RUN_TEST(confirm_boot_success);
    RUN_TEST(rollback_no_previous);
    RUN_TEST(rollback_below_min_policy);
    RUN_TEST(rollback_with_staged_state);
    RUN_TEST(rollback_success);
    RUN_TEST(persist_failure_write_ahead);
    RUN_TEST(open_path_rejections);
    RUN_TEST(no_tmp_residue);
    RUN_TEST(null_arg_matrix);
TEST_MAIN_END()
