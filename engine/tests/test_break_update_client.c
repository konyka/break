/* ==========================================================================
 *  test_break_update_client.c — Stage 5 Phase B Task 1 tests: update client
 *  state machine + A/B slot layout; Task 2 tests: chunked downloader with
 *  byte-level resume via an in-process fake fetcher; Task 3 tests: the
 *  stage/activate/unstage pipeline end-to-end headless.
 *
 *  Task 1 pins: fresh-open layout + byte-exact initial state; reopen
 *  round-trips; corrupt-state battery → open NULL (truncated / unknown key /
 *  bad value / cross-field nonsense / charset / >64 KiB — no heuristic
 *  repair); confirm_boot without pending → false (+STATE); confirm_boot
 *  success persists-first; rollback three refusal paths (no previous →
 *  STATE, below min-rollback → POLICY, staged exists → STATE) + success
 *  flip/swap; every op leaves zero PlatformAtomicWriter tmp residue;
 *  write-ahead failure injection (state path replaced by a directory →
 *  persist false + IO, in-memory state untouched, tmp unlinked, op retryable
 *  after repair); NULL-arg matrix.
 *
 *  Task 2 pins (fake fetcher = fixture buffer map + scriptable deterministic
 *  failure: fail-on-call-K global / fail-after-N-bytes on one object; every
 *  call range-validated against the claimed size WITHOUT computing
 *  offset+len): full 3-chunk download with a CAS pre-seeded chunk never
 *  re-fetched (call-count pin) and sequential manifest-order call sequence;
 *  mid-chunk transport failure → resume continues at the persisted byte
 *  offset (offset > 0 asserted) with byte-equal final content; completed
 *  chunk never re-fetched across client reopen; hash mismatch → false +
 *  VERIFY, .part gone, CAS lacks the chunk, restart from 0 on retry; corrupt
 *  resume entry battery (offset > size / .part missing / size mismatch /
 *  unknown hash) → false + STATE with zero transport, clean restart from 0;
 *  stale completed entry (chunk already in CAS) self-heals silently;
 *  zero-byte chunk fetched zero times; 0-chunk manifest → true no-op;
 *  near-U64_MAX claimed size → every call clamped from the manifest size
 *  (saw_bad_range stays false); confirm_boot preserves a resume-chunk line
 *  byte-exactly (review M1 pin).
 *
 *  Task 3 pins (signed fixture manifests — test-only Ed25519 keypair, see the
 *  Task 3 section header for provenance): full cycle fresh stage → activate →
 *  confirm with slot file bytes == chunk bytes (byte-exact, nested names via
 *  per-component mkdir) and byte-exact state at every step; SIGNATURE BEFORE
 *  TRANSPORT gate — invalid signature → VERIFY + zero fetch calls + zero disk
 *  change; channel/platform mismatch and below-min-version → POLICY + zero
 *  fetch; fresh-client min-version semantics (current=none ⇒ source 0.0.0:
 *  a 0.0.0-floor payload stages, a higher floor refuses) both ways; stage
 *  while staged → STATE (unstage is the only clear path); fetch failure ⇒
 *  slot trees untouched + resume progress kept; materialize failure ⇒ partial
 *  slot removed + state unchanged; activate without stage → STATE; activate
 *  with missing/corrupt update-version marker → IO (fail closed, no flip);
 *  rollback pre-confirm flips back + clears pending; rollback post-confirm
 *  allowed above / refused below the min-rollback floor; rollback while
 *  staged → STATE, then unstage → rollback allowed again; unstage without
 *  staged → false; A→B→A re-stage over the retained slot is byte-exact with
 *  zero stale files; crash-simulation (destroy+reopen between stage and
 *  activate) keeps the staged slot intact and current unchanged.
 * ========================================================================== */

#include "test_framework.h"

#include <update/break_update_client.h>
#include <update/break_update.h>
#include <crypto/break_crypto.h>
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

/* Best-effort recursive removal of a file or directory tree (test teardown;
 * Task 3 fills the slots with real trees). ISO-C remove() handles files and
 * emptied directories on POSIX. */
static void remove_tree(const char *path) {
    PlatformDirEntry entries[32];
    u32 count = 0;
    if (!platform_list_dir(path, entries, 32, &count)) {
        remove(path);
        return;
    }
    u32 i;
    for (i = 0; i < count && i < 32; i++) {
        char child[1200];
        join_path(child, sizeof(child), path, entries[i].name);
        if (entries[i].is_dir) {
            remove_tree(child);
        } else {
            remove(child);
        }
    }
    TEST_RMDIR(path);
}

/* Best-effort teardown of the fixed Task 1 layout (state may be a file or,
 * after the failure-injection test, already gone; remove() handles both on
 * POSIX and TEST_RMDIR covers the directory case). Task 2: chunks/ may hold
 * downloaded chunks + a .part spool — remove files before the rmdir.
 * Task 3: slots/A + slots/B may hold materialized trees (files/ subtrees +
 * update-version markers) — removed recursively. */
static void cleanup_root(const char *root) {
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    remove(p);
    TEST_RMDIR(p);
    join_path(p, sizeof(p), root, "chunks");
    {
        PlatformDirEntry entries[80];
        u32 count = 0, i;
        if (platform_list_dir(p, entries, 80, &count)) {
            char q[1200];
            for (i = 0; i < count && i < 80; i++) {
                if (entries[i].is_dir) continue;
                join_path(q, sizeof(q), p, entries[i].name);
                remove(q);
            }
        }
    }
    TEST_RMDIR(p);
    join_path(p, sizeof(p), root, "slots/A");
    remove_tree(p);
    join_path(p, sizeof(p), root, "slots/B");
    remove_tree(p);
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

    /* Over-long root: the open-time bound reserves room for the tightest
     * suffix — "/slots/A/files/" (15) + a 128-byte manifest name + the
     * writer's ".tmpXXXXXX" (10) + NUL = 154 bytes (covers "/state" etc.)
     * below PLATFORM_FS_PATH_CAPACITY → reject beyond that. */
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

/* ==================== Task 2: chunked downloader + resume ==================
 * In-process fake fetcher: a fixture buffer map keyed by object name (==
 * chunk sha256 hex) plus scriptable, deterministic failure:
 *   - fail-on-call-K: the K-th (1-based) call of a phase returns false;
 *   - fail-after-N-bytes: calls on a chosen object starting at offset >= N
 *     return false (a contiguous download dies right after byte N).
 * Every call is range-validated against the object's CLAIMED size without
 * ever computing offset+len (an overflow or a beyond-size request sets
 * saw_bad_range and is refused) — this is the client-side clamp contract.
 * Served (offset,len) pairs are logged for the whole test (lifetime) so the
 * pins can assert byte-level contiguity across failure/resume phases. */

#define ZERO_SIG_B64 \
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=="

#define FAKE_MAX_OBJS   8
#define FAKE_MAX_RANGES 32
#define FAKE_MAX_ORDER  64

typedef struct {
    u64 off, len;
} FakeRange;

typedef struct {
    char name[65];     /* object name == chunk sha256 hex */
    const u8 *bytes;   /* fixture content; NULL → deterministic pattern bytes */
    u64 size;          /* fixture length == manifest-declared size */
    u64 claimed;       /* remote-claimed size (== size; ~U64_MAX in the overflow test) */
    u32 calls;         /* calls in the current phase */
    u64 n_ranges;      /* served ranges, lifetime (never reset mid-test) */
    u64 phase_marker;  /* n_ranges at the last fake_reset_phase */
    FakeRange ranges[FAKE_MAX_RANGES];
} FakeObj;

typedef struct {
    FakeObj objs[FAKE_MAX_OBJS];
    usize count;
    u64 total_calls;      /* current phase */
    u64 fail_on_call;     /* 1-based global call that fails; 0 = never */
    char fail_obj[65];    /* object under the byte rule; "" = none */
    u64 fail_after_bytes; /* fail_obj calls with offset >= this fail */
    bool saw_bad_range;   /* a call overflowed offset+len or exceeded claimed */
    bool saw_zero_len;    /* a zero-length request was made */
    bool saw_unknown;     /* fetch of an unregistered object */
    u8 order[FAKE_MAX_ORDER]; /* object index per call, current phase */
    u64 n_order;
} FakeFetch;

static void test_fatal(const char *msg) {
    printf("  FATAL: %s\n", msg);
    exit(2);
}

static void fake_add(FakeFetch *f, const char *hex, const u8 *bytes, u64 size,
                     u64 claimed) {
    if (f->count >= FAKE_MAX_OBJS) test_fatal("fake object table overflow");
    if (strlen(hex) != 64) test_fatal("fake object name is not 64-hex");
    FakeObj *o = &f->objs[f->count++];
    memset(o, 0, sizeof(*o));
    memcpy(o->name, hex, 65);
    o->bytes = bytes;
    o->size = size;
    o->claimed = claimed;
}

/* Keeps registrations and the lifetime range log; zeroes the counters and
 * the failure knobs (a "phase" = one fetch_all attempt). */
static void fake_reset_phase(FakeFetch *f) {
    usize i;
    f->total_calls = 0;
    f->fail_on_call = 0;
    f->fail_obj[0] = '\0';
    f->fail_after_bytes = 0;
    f->saw_bad_range = false;
    f->saw_zero_len = false;
    f->saw_unknown = false;
    f->n_order = 0;
    for (i = 0; i < f->count; i++) {
        f->objs[i].calls = 0;
        f->objs[i].phase_marker = f->objs[i].n_ranges;
    }
}

static bool fake_fetch(void *user, const char *object_name, u64 offset, u64 len,
                       u8 *out) {
    FakeFetch *f = (FakeFetch *)user;
    FakeObj *o = NULL;
    usize i;
    f->total_calls++;
    for (i = 0; i < f->count; i++) {
        if (strcmp(f->objs[i].name, object_name) == 0) {
            o = &f->objs[i];
            break;
        }
    }
    if (!o) {
        f->saw_unknown = true;
        return false;
    }
    /* Clamp contract: offset+len must not overflow u64 and must stay inside
     * the claimed size — checked WITHOUT computing offset+len. */
    if (offset > o->claimed || len > o->claimed - offset) f->saw_bad_range = true;
    if (len == 0) f->saw_zero_len = true;
    o->calls++;
    if (f->n_order >= FAKE_MAX_ORDER) test_fatal("order log overflow");
    f->order[f->n_order++] = (u8)(o - f->objs);
    if (f->fail_on_call && f->total_calls == f->fail_on_call) return false;
    if (f->fail_obj[0] && strcmp(f->fail_obj, object_name) == 0 &&
        offset >= f->fail_after_bytes)
        return false;
    if (f->saw_bad_range) return false; /* refuse to serve out-of-range */
    if (o->n_ranges >= FAKE_MAX_RANGES) test_fatal("range log overflow");
    o->ranges[o->n_ranges].off = offset;
    o->ranges[o->n_ranges].len = len;
    o->n_ranges++;
    if (o->bytes) {
        if (offset > o->size || len > o->size - offset)
            test_fatal("fixture-backed range outside the real buffer");
        memcpy(out, o->bytes + (usize)offset, (usize)len);
    } else {
        u64 k;
        for (k = 0; k < len; k++) out[k] = (u8)((offset + k) * 33u + 11u);
    }
    return true;
}

/* ---- Task 2 fixtures + helpers -------------------------------------------- */

static u8 g_fx_small[100];
static u8 g_fx_a[100000];
static u8 g_fx_a2[100000];
static u8 g_fx_big[200000];
static u8 g_fx_b[300];
static u8 g_fx_c[70000];
static u8 g_fx_x[1000];
static u8 g_fx_right[300];
static u8 g_fx_wrong[300];
static u8 g_fx_n[42];

static void fill_bytes(u8 *b, usize n, u8 seed) {
    usize i;
    for (i = 0; i < n; i++) b[i] = (u8)(seed + 7u * (u8)i + (u8)(i >> 8));
}

static void bin2hex(const u8 *in, usize n, char *out) {
    static const char hexd[] = "0123456789abcdef";
    usize i;
    for (i = 0; i < n; i++) {
        out[2 * i] = hexd[in[i] >> 4];
        out[2 * i + 1] = hexd[in[i] & 15];
    }
    out[2 * n] = '\0';
}

static void hash_hex_of(const void *data, usize len, char out[65]) {
    u8 h[32];
    if (!break_crypto_sha256(data, len, h)) test_fatal("fixture sha256 failed");
    bin2hex(h, 32, out);
}

typedef struct {
    const char *mname; /* slot-relative name (unused by fetch_all) */
    const char *hex;
    u64 size;
} ManChunk;

/* Canonical manifest text with the structurally-valid zero signature
 * (fetch_all never verifies it — Task 3's stage does). Names pre-sorted. */
static BreakUpdateManifest *build_manifest(const ManChunk *chunks, usize n) {
    char buf[4096];
    usize off = 0;
    usize i;
    int r = snprintf(buf, sizeof(buf),
                     "break-manifest-v1\n"
                     "version: 2.0.0\n"
                     "channel: stable\n"
                     "platform: linux-x86-64\n"
                     "min-version: 0.0.0\n");
    if (r < 0) test_fatal("manifest header");
    off = (usize)r;
    for (i = 0; i < n; i++) {
        r = snprintf(buf + off, sizeof(buf) - off, "chunk: %s %llu %s\n",
                     chunks[i].hex, (unsigned long long)chunks[i].size,
                     chunks[i].mname);
        if (r < 0 || (usize)r >= sizeof(buf) - off) test_fatal("manifest overflow");
        off += (usize)r;
    }
    r = snprintf(buf + off, sizeof(buf) - off, "signature: %s\n", ZERO_SIG_B64);
    if (r < 0 || (usize)r >= sizeof(buf) - off) test_fatal("manifest overflow");
    off += (usize)r;
    BreakUpdateManifest *m = break_update_manifest_parse(buf, off);
    if (!m) test_fatal("test manifest failed to parse");
    return m;
}

static bool cas_put(const char *root, const void *data, usize len) {
    BreakUpdateStore *s = break_update_store_open(root);
    if (!s) return false;
    bool ok = break_update_store_put_chunk(s, data, len);
    break_update_store_destroy(s);
    return ok;
}

static bool cas_has(const char *root, const char *hex) {
    BreakUpdateStore *s = break_update_store_open(root);
    if (!s) return false;
    bool ok = break_update_store_has_chunk(s, hex);
    break_update_store_destroy(s);
    return ok;
}

static bool cas_bytes_equal(const char *root, const char *hex, const u8 *expect,
                            u64 len) {
    BreakUpdateStore *s = break_update_store_open(root);
    if (!s) return false;
    u8 *buf = NULL;
    u64 n = 0;
    bool ok = break_update_store_get_chunk(s, hex, &buf, &n);
    break_update_store_destroy(s);
    if (!ok) return false;
    ok = n == len && (len == 0 || memcmp(buf, expect, (usize)len) == 0);
    free(buf);
    return ok;
}

/* "<root>/chunks/<hex>.part" */
static void part_path_of(const char *root, const char *hex, char *out, usize cap) {
    char dir[1200];
    char leaf[80];
    int r;
    join_path(dir, sizeof(dir), root, "chunks");
    r = snprintf(leaf, sizeof(leaf), "%s.part", hex);
    if (r < 0 || (usize)r >= sizeof(leaf)) test_fatal("part leaf overflow");
    join_path(out, cap, dir, leaf);
}

/* state file (tiny here) contains the NUL-terminated needle. */
static bool state_contains(const char *root, const char *needle) {
    char p[1200];
    char buf[2048];
    u64 size = 0;
    usize got = 0;
    FILE *fp;
    join_path(p, sizeof(p), root, "state");
    if (!platform_file_size(p, &size)) return false;
    if (size == 0 || size >= sizeof(buf)) return false;
    fp = fopen(p, "rb");
    if (!fp) return false;
    got = fread(buf, 1, (usize)size, fp);
    fclose(fp);
    if (got != (usize)size) return false;
    buf[size] = '\0';
    return strstr(buf, needle) != NULL;
}

/* chunks/ listing: regular-file count + whether any ".part" name exists. */
static bool chunks_dir_scan(const char *root, u32 *out_files, bool *out_has_part) {
    char p[1200];
    PlatformDirEntry entries[80];
    u32 count = 0, i, files = 0;
    bool part = false;
    join_path(p, sizeof(p), root, "chunks");
    if (!platform_list_dir(p, entries, 80, &count)) return false;
    for (i = 0; i < count && i < 80; i++) {
        if (entries[i].is_dir) continue;
        files++;
        if (strstr(entries[i].name, ".part")) part = true;
    }
    *out_files = files;
    *out_has_part = part;
    return true;
}

/* Served ranges must tile [0,size) contiguously in call order (byte-level
 * resume: no gap, no overlap, full coverage). */
static bool ranges_tile(const FakeObj *o, u64 size) {
    u64 expect = 0;
    u64 i;
    for (i = 0; i < o->n_ranges; i++) {
        if (o->ranges[i].off != expect) return false;
        expect += o->ranges[i].len;
    }
    return expect == size;
}

TEST(fetch_all_full_download_cas_dedup) {
    fill_bytes(g_fx_a, sizeof(g_fx_a), 11);
    fill_bytes(g_fx_b, sizeof(g_fx_b), 23);
    fill_bytes(g_fx_c, sizeof(g_fx_c), 37);
    char ha[65], hb[65], hc[65];
    hash_hex_of(g_fx_a, sizeof(g_fx_a), ha);
    hash_hex_of(g_fx_b, sizeof(g_fx_b), hb);
    hash_hex_of(g_fx_c, sizeof(g_fx_c), hc);
    ManChunk chunks[] = {
        {"a.bin", ha, sizeof(g_fx_a)},
        {"b.bin", hb, sizeof(g_fx_b)},
        {"c.bin", hc, sizeof(g_fx_c)},
    };
    BreakUpdateManifest *m = build_manifest(chunks, 3);

    char root[512];
    test_tmp(root, sizeof(root), "upc_dl_full");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    /* Pre-seed b.bin's chunk: same-object re-download suppression (never
     * re-fetched — the call-count pin). */
    ASSERT_TRUE(cas_put(root, g_fx_b, sizeof(g_fx_b)));

    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, ha, g_fx_a, sizeof(g_fx_a), sizeof(g_fx_a));
    fake_add(&f, hb, g_fx_b, sizeof(g_fx_b), sizeof(g_fx_b));
    fake_add(&f, hc, g_fx_c, sizeof(g_fx_c), sizeof(g_fx_c));

    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_TRUE(f.objs[0].calls > 0u);
    ASSERT_EQ(f.objs[1].calls, 0u); /* THE dedup pin: CAS hit → zero fetches */
    ASSERT_TRUE(f.objs[2].calls > 0u);
    ASSERT_EQ(f.total_calls, (u64)f.objs[0].calls + (u64)f.objs[2].calls);
    ASSERT_FALSE(f.saw_bad_range);
    ASSERT_FALSE(f.saw_zero_len);
    ASSERT_FALSE(f.saw_unknown);
    /* Sequential in manifest order: every a call precedes every c call, and
     * the pre-seeded b (index 1) never appears. */
    {
        u64 k;
        bool saw_c = false;
        ASSERT_EQ(f.n_order, f.total_calls);
        for (k = 0; k < f.n_order; k++) {
            if (f.order[k] == 2) saw_c = true;
            if (saw_c) {
                ASSERT_TRUE(f.order[k] == 2);
            } else {
                ASSERT_TRUE(f.order[k] == 0);
            }
        }
    }
    ASSERT_TRUE(ranges_tile(&f.objs[0], sizeof(g_fx_a)));
    ASSERT_TRUE(ranges_tile(&f.objs[2], sizeof(g_fx_c)));
    /* Every chunk landed in the CAS under its manifest hash, byte-exact. */
    ASSERT_TRUE(cas_bytes_equal(root, ha, g_fx_a, sizeof(g_fx_a)));
    ASSERT_TRUE(cas_bytes_equal(root, hb, g_fx_b, sizeof(g_fx_b)));
    ASSERT_TRUE(cas_bytes_equal(root, hc, g_fx_c, sizeof(g_fx_c)));
    /* One .part at a time, none survives; chunks/ holds exactly the 3. */
    u32 files = 0;
    bool part = true;
    ASSERT_TRUE(chunks_dir_scan(root, &files, &part));
    ASSERT_EQ(files, 3u);
    ASSERT_FALSE(part);
    /* Slot fields untouched; the resume entry round-tripped back to none. */
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));
    ASSERT_FALSE(dir_has_tmp(root));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(fetch_all_midchunk_resume) {
    fill_bytes(g_fx_big, sizeof(g_fx_big), 51);
    char hb[65];
    hash_hex_of(g_fx_big, sizeof(g_fx_big), hb);
    ManChunk chunks[] = {{"big.bin", hb, sizeof(g_fx_big)}};
    BreakUpdateManifest *m = build_manifest(chunks, 1);

    char root[512];
    test_tmp(root, sizeof(root), "upc_dl_resume");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, hb, g_fx_big, sizeof(g_fx_big), sizeof(g_fx_big));
    /* fail-after-N-bytes: the first block lands, the next call (starting at
     * offset >= 1) dies — the chunk is mid-flight. */
    memcpy(f.fail_obj, hb, 65);
    f.fail_after_bytes = 1;

    ASSERT_FALSE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_FETCH);
    ASSERT_EQ(f.objs[0].n_ranges, (u64)1); /* exactly one block spooled */
    ASSERT_EQ(f.objs[0].ranges[0].off, (u64)0);
    u64 delivered = f.objs[0].ranges[0].len;
    ASSERT_TRUE(delivered > 0 && delivered < (u64)sizeof(g_fx_big));

    /* Progress persisted in the state file; the .part matches the offset. */
    char expect_line[128];
    int r = snprintf(expect_line, sizeof(expect_line), "resume-chunk: %s|%llu\n", hb,
                     (unsigned long long)delivered);
    ASSERT_TRUE(r > 0 && (usize)r < sizeof(expect_line));
    ASSERT_TRUE(state_contains(root, expect_line));
    char part_path[1200];
    part_path_of(root, hb, part_path, sizeof(part_path));
    u64 part_size = 0;
    ASSERT_TRUE(platform_file_size(part_path, &part_size));
    ASSERT_EQ(part_size, delivered);

    /* Resume with the failure rule off: continues at the persisted offset. */
    fake_reset_phase(&f);
    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    /* Fake-side pins: the resume's first served range starts at offset > 0
     * (exactly the persisted offset), and the served ranges tile the chunk. */
    ASSERT_TRUE(f.objs[0].n_ranges > f.objs[0].phase_marker);
    ASSERT_EQ(f.objs[0].ranges[f.objs[0].phase_marker].off, delivered);
    ASSERT_TRUE(ranges_tile(&f.objs[0], sizeof(g_fx_big)));
    ASSERT_TRUE(cas_bytes_equal(root, hb, g_fx_big, sizeof(g_fx_big))); /* final bytes equal */
    ASSERT_FALSE(platform_file_size(part_path, &part_size));            /* .part gone */
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE)); /* entry cleared */
    ASSERT_FALSE(dir_has_tmp(root));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(fetch_all_completed_chunk_not_refetched_across_reopen) {
    fill_bytes(g_fx_small, sizeof(g_fx_small), 61);
    fill_bytes(g_fx_big, sizeof(g_fx_big), 71);
    char ha[65], hb[65];
    hash_hex_of(g_fx_small, sizeof(g_fx_small), ha);
    hash_hex_of(g_fx_big, sizeof(g_fx_big), hb);
    ManChunk chunks[] = {
        {"a.bin", ha, sizeof(g_fx_small)},
        {"b.bin", hb, sizeof(g_fx_big)},
    };
    BreakUpdateManifest *m = build_manifest(chunks, 2);

    char root[512];
    test_tmp(root, sizeof(root), "upc_dl_reopen");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, ha, g_fx_small, sizeof(g_fx_small), sizeof(g_fx_small));
    fake_add(&f, hb, g_fx_big, sizeof(g_fx_big), sizeof(g_fx_big));
    /* fail-on-call-3: call 1 = a's only block (completes), call 2 = b's first
     * block, call 3 dies → a in CAS, b mid-flight with persisted progress. */
    f.fail_on_call = 3;

    ASSERT_FALSE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_FETCH);
    ASSERT_EQ(f.objs[0].n_ranges, (u64)1);
    ASSERT_EQ(f.objs[1].n_ranges, (u64)1);
    u64 b_done = f.objs[1].ranges[0].len;
    ASSERT_TRUE(b_done > 0 && b_done < (u64)sizeof(g_fx_big));
    ASSERT_TRUE(cas_bytes_equal(root, ha, g_fx_small, sizeof(g_fx_small)));
    char expect_line[128];
    int r = snprintf(expect_line, sizeof(expect_line), "resume-chunk: %s|%llu\n", hb,
                     (unsigned long long)b_done);
    ASSERT_TRUE(r > 0 && (usize)r < sizeof(expect_line));
    ASSERT_TRUE(state_contains(root, expect_line));

    /* Crash simulation: destroy + reopen on the same root. */
    break_update_client_destroy(c);
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    fake_reset_phase(&f);
    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    /* Persisted progress pin: the completed chunk is never re-fetched across
     * the reopen; b resumes at the persisted byte offset and tiles fully. */
    ASSERT_EQ(f.objs[0].calls, 0u);
    ASSERT_TRUE(f.objs[1].n_ranges > f.objs[1].phase_marker);
    ASSERT_EQ(f.objs[1].ranges[f.objs[1].phase_marker].off, b_done);
    ASSERT_TRUE(ranges_tile(&f.objs[1], sizeof(g_fx_big)));
    ASSERT_TRUE(cas_bytes_equal(root, ha, g_fx_small, sizeof(g_fx_small)));
    ASSERT_TRUE(cas_bytes_equal(root, hb, g_fx_big, sizeof(g_fx_big)));
    u32 files = 0;
    bool part = true;
    ASSERT_TRUE(chunks_dir_scan(root, &files, &part));
    ASSERT_EQ(files, 2u);
    ASSERT_FALSE(part);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(fetch_all_hash_mismatch_verify) {
    fill_bytes(g_fx_right, sizeof(g_fx_right), 81);
    fill_bytes(g_fx_wrong, sizeof(g_fx_wrong), 97); /* same length, wrong bytes */
    char ha[65];
    hash_hex_of(g_fx_right, sizeof(g_fx_right), ha);
    ManChunk chunks[] = {{"bad.bin", ha, sizeof(g_fx_right)}};
    BreakUpdateManifest *m = build_manifest(chunks, 1);

    char root[512];
    test_tmp(root, sizeof(root), "upc_dl_verify");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, ha, g_fx_wrong, sizeof(g_fx_wrong), sizeof(g_fx_wrong));

    ASSERT_FALSE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_VERIFY);
    ASSERT_EQ(f.objs[0].n_ranges, (u64)1); /* fully spooled, then rejected */
    /* .part discarded, nothing entered the CAS, the entry was cleared. */
    char part_path[1200];
    u64 sz = 0;
    part_path_of(root, ha, part_path, sizeof(part_path));
    ASSERT_FALSE(platform_file_size(part_path, &sz));
    ASSERT_FALSE(cas_has(root, ha));
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));

    /* A corrected remote restarts the chunk from 0 (progress discarded). */
    f.objs[0].bytes = g_fx_right;
    fake_reset_phase(&f);
    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(f.objs[0].n_ranges, (u64)2); /* one range per phase */
    ASSERT_EQ(f.objs[0].ranges[f.objs[0].phase_marker].off, (u64)0);
    ASSERT_TRUE(cas_bytes_equal(root, ha, g_fx_right, sizeof(g_fx_right)));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

/* One corrupt-resume sub-case: craft a state carrying <resume_line>, drop a
 * .part of <part_len> zero bytes named <part_hex> when part_len > 0, then
 * fetch_all must report STATE with ZERO transport, discard the .part, clear
 * the entry — and a retry must succeed from offset 0. The manifest holds the
 * single chunk x.bin (content/hex). */
static void corrupt_resume_case(const char *name, const char *resume_line,
                                const char *part_hex, usize part_len,
                                const u8 *content, u64 content_len,
                                const char *hex) {
    static const u8 zeros[2048];
    char state[1024];
    int r = snprintf(state, sizeof(state),
                     L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N
                         L_MINRB "%s",
                     resume_line);
    if (r < 0 || (usize)r >= sizeof(state)) test_fatal("corrupt case state overflow");
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), name, state);
    ASSERT_NOT_NULL(c);
    if (!c) return;
    if (part_len) {
        char pp[1200];
        if (part_len > sizeof(zeros)) test_fatal("part fixture overflow");
        part_path_of(root, part_hex, pp, sizeof(pp));
        ASSERT_TRUE(write_file(pp, zeros, part_len));
    }
    ManChunk mc[] = {{"x.bin", hex, content_len}};
    BreakUpdateManifest *m = build_manifest(mc, 1);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, hex, content, content_len, content_len);

    ASSERT_FALSE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_EQ(f.total_calls, (u64)0); /* triage precedes any transport */
    char pp[1200];
    u64 sz = 0;
    part_path_of(root, part_hex, pp, sizeof(pp));
    ASSERT_FALSE(platform_file_size(pp, &sz)); /* .part discarded */
    ASSERT_TRUE(state_contains(root, "resume-chunk: none\n"));

    /* Restarted clean: the retry fetches from offset 0 and succeeds. */
    fake_reset_phase(&f);
    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_EQ(f.objs[0].ranges[0].off, (u64)0);
    ASSERT_TRUE(ranges_tile(&f.objs[0], content_len));
    ASSERT_TRUE(cas_bytes_equal(root, hex, content, content_len));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(fetch_all_corrupt_resume_state) {
    fill_bytes(g_fx_x, sizeof(g_fx_x), 113);
    char hx[65], hy[65];
    char line[160];
    int r;
    hash_hex_of(g_fx_x, sizeof(g_fx_x), hx);
    hash_hex_of("not-in-manifest", 15, hy);

    /* (a) offset beyond the manifest chunk size (+ a .part to discard). */
    r = snprintf(line, sizeof(line), "resume-chunk: %s|1001\n", hx);
    ASSERT_TRUE(r > 0 && (usize)r < sizeof(line));
    corrupt_resume_case("upc_dl_cora", line, hx, 1001, g_fx_x, sizeof(g_fx_x), hx);

    /* (b) offset > 0 with no .part on disk. */
    r = snprintf(line, sizeof(line), "resume-chunk: %s|500\n", hx);
    ASSERT_TRUE(r > 0 && (usize)r < sizeof(line));
    corrupt_resume_case("upc_dl_corb", line, hx, 0, g_fx_x, sizeof(g_fx_x), hx);

    /* (c) .part size disagrees with the recorded offset. */
    r = snprintf(line, sizeof(line), "resume-chunk: %s|500\n", hx);
    ASSERT_TRUE(r > 0 && (usize)r < sizeof(line));
    corrupt_resume_case("upc_dl_corc", line, hx, 400, g_fx_x, sizeof(g_fx_x), hx);

    /* (d) resume hash unknown to this manifest. */
    r = snprintf(line, sizeof(line), "resume-chunk: %s|10\n", hy);
    ASSERT_TRUE(r > 0 && (usize)r < sizeof(line));
    corrupt_resume_case("upc_dl_cord", line, hy, 10, g_fx_x, sizeof(g_fx_x), hx);
}

TEST(fetch_all_stale_resume_self_heals) {
    /* Crash window: the chunk reached the CAS but the resume entry was never
     * cleared → the entry is stale, NOT corrupt: cleared silently, no error,
     * zero transport. */
    fill_bytes(g_fx_x, sizeof(g_fx_x), 113);
    char hx[65];
    hash_hex_of(g_fx_x, sizeof(g_fx_x), hx);
    char state[1024];
    int r = snprintf(state, sizeof(state),
                     L_MAGIC L_CUR_N L_STG_N L_PEND_N L_CONF_N L_CVER_N L_PVER_N
                         L_MINRB "resume-chunk: %s|%llu\n",
                     hx, (unsigned long long)sizeof(g_fx_x));
    if (r < 0 || (usize)r >= sizeof(state)) test_fatal("stale case state overflow");
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_dl_stale", state);
    ASSERT_NOT_NULL(c);
    ASSERT_TRUE(cas_put(root, g_fx_x, sizeof(g_fx_x))); /* already in the CAS */
    ManChunk mc[] = {{"x.bin", hx, sizeof(g_fx_x)}};
    BreakUpdateManifest *m = build_manifest(mc, 1);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, hx, g_fx_x, sizeof(g_fx_x), sizeof(g_fx_x));

    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_EQ(f.total_calls, (u64)0);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));
    ASSERT_TRUE(cas_bytes_equal(root, hx, g_fx_x, sizeof(g_fx_x)));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(fetch_all_zero_byte_chunk) {
    char hz[65], hn[65];
    fill_bytes(g_fx_n, sizeof(g_fx_n), 131);
    hash_hex_of("", 0, hz); /* sha256 of the empty input */
    hash_hex_of(g_fx_n, sizeof(g_fx_n), hn);
    ManChunk chunks[] = {
        {"n.bin", hn, sizeof(g_fx_n)},
        {"z.bin", hz, 0},
    };
    BreakUpdateManifest *m = build_manifest(chunks, 2);

    char root[512];
    test_tmp(root, sizeof(root), "upc_dl_zero");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, hn, g_fx_n, sizeof(g_fx_n), sizeof(g_fx_n));
    fake_add(&f, hz, (const u8 *)"", 0, 0);

    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_EQ(f.objs[0].calls, 1u);
    ASSERT_EQ(f.objs[1].calls, 0u); /* zero-byte chunk: never fetched */
    ASSERT_FALSE(f.saw_zero_len);   /* and no zero-length request was made */
    ASSERT_FALSE(f.saw_bad_range);
    ASSERT_TRUE(cas_bytes_equal(root, hz, (const u8 *)"", 0)); /* len-0 hit */
    ASSERT_TRUE(cas_bytes_equal(root, hn, g_fx_n, sizeof(g_fx_n)));
    u32 files = 0;
    bool part = true;
    ASSERT_TRUE(chunks_dir_scan(root, &files, &part));
    ASSERT_EQ(files, 2u);
    ASSERT_FALSE(part);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(fetch_all_empty_manifest) {
    BreakUpdateManifest *m = build_manifest(NULL, 0);
    char root[512];
    test_tmp(root, sizeof(root), "upc_dl_empty");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    /* user = NULL: with zero chunks the fetch callback is never invoked. */
    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, NULL));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_EQ(f.total_calls, (u64)0);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));
    u32 files = 0;
    bool part = true;
    ASSERT_TRUE(chunks_dir_scan(root, &files, &part));
    ASSERT_EQ(files, 0u);
    ASSERT_FALSE(part);

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(fetch_all_offset_len_overflow_clamped) {
    /* The remote "claims" a near-U64_MAX object (the manifest size is the
     * bound): the client must clamp every range from the manifest size and
     * never compute an overflowing offset+len (the fake validates each call
     * WITHOUT computing the sum), and must never allocate size-proportionally
     * (this process survives; the spool is block-bounded). */
    char hh[65];
    hash_hex_of("overflow-fixture", 16, hh); /* digest never reached */
    ManChunk chunks[] = {{"huge.bin", hh, ~(u64)0}};
    BreakUpdateManifest *m = build_manifest(chunks, 1);

    char root[512];
    test_tmp(root, sizeof(root), "upc_dl_overflow");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, hh, NULL, ~(u64)0, ~(u64)0); /* pattern bytes, claimed ~U64_MAX */
    f.fail_on_call = 3;                        /* stop deterministically */

    ASSERT_FALSE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_FETCH);
    ASSERT_EQ(f.total_calls, (u64)3);
    ASSERT_FALSE(f.saw_bad_range); /* THE pin: no overflow, no beyond-size call */
    ASSERT_FALSE(f.saw_zero_len);
    ASSERT_EQ(f.objs[0].n_ranges, (u64)2); /* two blocks spooled before the failure */
    ASSERT_EQ(f.objs[0].ranges[0].off, (u64)0);
    ASSERT_EQ(f.objs[0].ranges[1].off, f.objs[0].ranges[0].len);
    {
        u64 delivered = f.objs[0].ranges[0].len + f.objs[0].ranges[1].len;
        char expect_line[160];
        char part_path[1200];
        u64 part_size = 0;
        int r = snprintf(expect_line, sizeof(expect_line), "resume-chunk: %s|%llu\n",
                         hh, (unsigned long long)delivered);
        ASSERT_TRUE(r > 0 && (usize)r < sizeof(expect_line));
        ASSERT_TRUE(state_contains(root, expect_line)); /* progress = delivered */
        part_path_of(root, hh, part_path, sizeof(part_path));
        ASSERT_TRUE(platform_file_size(part_path, &part_size));
        ASSERT_EQ(part_size, delivered);
    }

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(fetch_all_null_args) {
    fill_bytes(g_fx_n, sizeof(g_fx_n), 139);
    char hn[65];
    hash_hex_of(g_fx_n, sizeof(g_fx_n), hn);
    ManChunk chunks[] = {{"n.bin", hn, sizeof(g_fx_n)}};
    BreakUpdateManifest *m = build_manifest(chunks, 1);

    char root[512];
    test_tmp(root, sizeof(root), "upc_dl_null");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, hn, g_fx_n, sizeof(g_fx_n), sizeof(g_fx_n));

    ASSERT_FALSE(break_update_client_fetch_all(NULL, m, fake_fetch, &f));
    ASSERT_FALSE(break_update_client_fetch_all(c, NULL, fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_INVALID);
    ASSERT_FALSE(break_update_client_fetch_all(c, m, NULL, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_INVALID);
    ASSERT_EQ(f.total_calls, (u64)0); /* nothing was attempted */
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(confirm_boot_preserves_resume_line) {
    /* Review M1 (Task 1): a pending state carrying resume-chunk keeps that
     * line BYTE-EXACTLY across confirm_boot — in-flight download progress
     * must survive the boot lifecycle (fetch_all consumes it verbatim). */
    static const char pending_resume[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        "pending: yes\n"
        L_CONF_N
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        "resume-chunk: " HASH64 "|4096\n";
    static const char confirmed_resume[] =
        L_MAGIC
        "current: B\n"
        L_STG_N
        L_PEND_N
        "confirmed: yes\n"
        "current-version: 1.2.3\n"
        "previous-version: 1.1.0\n"
        "min-rollback-version: 1.0.0\n"
        "resume-chunk: " HASH64 "|4096\n";
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_conf_resume",
                                           pending_resume);
    ASSERT_NOT_NULL(c);
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, confirmed_resume)); /* resume line preserved */
    ASSERT_FALSE(dir_has_tmp(root));
    break_update_client_destroy(c);

    c = break_update_client_open(root); /* and it survives a reopen */
    ASSERT_NOT_NULL(c);
    ASSERT_TRUE(break_update_client_confirmed(c));
    ASSERT_TRUE(file_bytes_equal(p, confirmed_resume));
    break_update_client_destroy(c);
    cleanup_root(root);
}

/* ==================== Task 3: stage → activate → unstage ===================
 * Signed fixture manifests (REAL Ed25519 signatures — stage's verify gate
 * demands them; Phase A's keypair cannot sign new bodies because its private
 * key was never committed). Test-vector provenance (generated ONCE offline on
 * 2026-10-24 with the system OpenSSL 3.5.9 CLI; scratch dir
 * /tmp/upd_t3_keygen; the private key is NOT committed anywhere — TEST-ONLY
 * keypair, never a product key):
 *   openssl genpkey -algorithm ed25519 -out sk.pem
 *   openssl pkey -in sk.pem -pubout -out pk.pem
 *   openssl pkey -pubin -in pk.pem -outform DER | tail -c 32 | xxd -p -c 64
 *       -> STAGE_PUBKEY_HEX
 *   chunk hashes: sha256 over the fill_bytes(seed, size) fixture bytes (the
 *       same generator the fixtures below use — pinned by
 *       stage_fixture_vectors_match so fixture drift fails loudly)
 *   openssl pkeyutl -sign -inkey sk.pem -rawin -in <body> | base64
 *       -> SIG_* lines (body = all bytes before the signature line);
 *       every signature cross-checked with pkeyutl -verify.
 * Manifests (channel stable / platform linux-x86-64 throughout):
 *   M_A    version 2.0.0 min-version 0.0.0   bin/engine(100000,s11)
 *          data/base.pak(300,s23) shaders/pbr.spv(70000,s37)
 *   M_B    version 3.0.0 min-version 1.0.0   bin/engine(100000,s51)
 *          data/extra.pak(1000,s61)
 *   M_C    version 4.0.0 min-version 2.0.0   bin/engine(300,s71)
 *          readme.txt(42,s81)       (file set disjoint from M_A: staleness pin)
 *   M_MINV version 2.1.0 min-version 2.0.0   core.bin(100,s91)  (policy probe)
 * ========================================================================== */

static const char STAGE_PUBKEY_HEX[] =
    "8ee7de4ce6e6abed6c656cb57b92868957979edf28fb0fc41d73845f15587f31";

#define HASH_A_ENGINE \
    "b0287b430b1f8d1b4c2347812dc7da5374f3b390562249366600281df8f78bd6"
#define HASH_A_BASEPAK \
    "1ba3e75a0797219ef7fbe3a1b6c43996c0c50a30b93a813c1ff5483a0ad1d4d6"
#define HASH_A_PBRSPV \
    "29b676461c156fab5db89a3a89cc3d8676e7eb013899b37f65a0b4751fcd844a"
#define HASH_B_ENGINE \
    "432c0bf203827797fb8b586807798268cf92d873a1b3ef83c253994ce7898355"
#define HASH_B_EXTRAPAK \
    "90fb7379afb6eb020b272ffc9c03c22a7477e1bfe0356e7ef7d2e72b3cd0db21"
#define HASH_C_ENGINE \
    "01559ffa2e81750c21ff41fd393bebbcd5475be4c5b618a057776e42c5441b91"
#define HASH_C_README \
    "6ea595b29bc254143fa27ab0c040165de66053edf1d942c6a9c264a2fcaac318"
#define HASH_MINV_CORE \
    "9a910e8d6b031043251615469920de9011270d57253e55d05e5023b0ec0d5fb8"

#define SIG_A \
    "RsjbaYyEX7rYwqrTl4n+yWtGuoHbFaYyAttJasEpmzRHbnWunt1WnDeY2YNYfZOMbNrdA26rU18JihNap1FNCg=="
#define SIG_B \
    "VYq6WBAjMsCzKxCvzqGlPTsuhfTsZtzqJdC96yB76pTsJep3XwXw1u01vO6jLpLhTcfsN1EOC3QzpN64hegvBw=="
#define SIG_C \
    "YcKzm/tLCVOyu55meeAH6ubq1J3kfKLHa9BqFXOcyqcYeJVd6psCRJYcrIWptguIlrbYtGLhugxf6u4FS4V9BA=="
#define SIG_MINV \
    "ardYg8E4atHGzqt5ApSFs2oGhkWRAA4c96kFLSGMDGRFKZpdDcaosshzN8+lM/06Tr/lUH+QFkNfJ6IozVNgCg=="

static const u8 *stage_pubkey(void) {
    static u8 pub[32];
    static bool done = false;
    if (!done) {
        usize i;
        for (i = 0; i < 32; i++) {
            int hi = -1, lo = -1;
            char ch = STAGE_PUBKEY_HEX[2 * i], cl = STAGE_PUBKEY_HEX[2 * i + 1];
            if (ch >= '0' && ch <= '9') hi = ch - '0';
            else if (ch >= 'a' && ch <= 'f') hi = ch - 'a' + 10;
            if (cl >= '0' && cl <= '9') lo = cl - '0';
            else if (cl >= 'a' && cl <= 'f') lo = cl - 'a' + 10;
            if (hi < 0 || lo < 0) test_fatal("stage pubkey hex malformed");
            pub[i] = (u8)((hi << 4) | lo);
        }
        done = true;
    }
    return pub;
}

/* Canonical signed manifest text: header (parameterized version/min-version,
 * fixed stable/linux-x86-64) + chunk lines + the given base64 signature. */
static BreakUpdateManifest *signed_manifest(const char *version, const char *min_version,
                                            const ManChunk *chunks, usize n,
                                            const char *sig_b64) {
    char buf[4096];
    usize off;
    usize i;
    int r = snprintf(buf, sizeof(buf),
                     "break-manifest-v1\n"
                     "version: %s\n"
                     "channel: stable\n"
                     "platform: linux-x86-64\n"
                     "min-version: %s\n",
                     version, min_version);
    if (r < 0 || (usize)r >= sizeof(buf)) test_fatal("signed manifest header");
    off = (usize)r;
    for (i = 0; i < n; i++) {
        r = snprintf(buf + off, sizeof(buf) - off, "chunk: %s %llu %s\n",
                     chunks[i].hex, (unsigned long long)chunks[i].size,
                     chunks[i].mname);
        if (r < 0 || (usize)r >= sizeof(buf) - off) test_fatal("signed manifest overflow");
        off += (usize)r;
    }
    r = snprintf(buf + off, sizeof(buf) - off, "signature: %s\n", sig_b64);
    if (r < 0 || (usize)r >= sizeof(buf) - off) test_fatal("signed manifest overflow");
    off += (usize)r;
    BreakUpdateManifest *m = break_update_manifest_parse(buf, off);
    if (!m) test_fatal("signed test manifest failed to parse");
    return m;
}

static BreakUpdateManifest *manifest_a(void) {
    ManChunk chunks[] = {
        {"bin/engine", HASH_A_ENGINE, 100000},
        {"data/base.pak", HASH_A_BASEPAK, 300},
        {"shaders/pbr.spv", HASH_A_PBRSPV, 70000},
    };
    return signed_manifest("2.0.0", "0.0.0", chunks, 3, SIG_A);
}

static BreakUpdateManifest *manifest_b(void) {
    ManChunk chunks[] = {
        {"bin/engine", HASH_B_ENGINE, 100000},
        {"data/extra.pak", HASH_B_EXTRAPAK, 1000},
    };
    return signed_manifest("3.0.0", "1.0.0", chunks, 2, SIG_B);
}

static BreakUpdateManifest *manifest_c(void) {
    ManChunk chunks[] = {
        {"bin/engine", HASH_C_ENGINE, 300},
        {"readme.txt", HASH_C_README, 42},
    };
    return signed_manifest("4.0.0", "2.0.0", chunks, 2, SIG_C);
}

static BreakUpdateManifest *manifest_minv(void) {
    ManChunk chunks[] = {
        {"core.bin", HASH_MINV_CORE, 100},
    };
    return signed_manifest("2.1.0", "2.0.0", chunks, 1, SIG_MINV);
}

static void fill_fx_a(void) {
    fill_bytes(g_fx_a, 100000, 11);
    fill_bytes(g_fx_b, 300, 23);
    fill_bytes(g_fx_c, 70000, 37);
}

static void fill_fx_b(void) {
    fill_bytes(g_fx_a2, 100000, 51);
    fill_bytes(g_fx_x, 1000, 61);
}

static void fill_fx_c(void) {
    fill_bytes(g_fx_right, 300, 71);
    fill_bytes(g_fx_n, 42, 81);
}

static void fake_add_a(FakeFetch *f) {
    fake_add(f, HASH_A_ENGINE, g_fx_a, 100000, 100000);
    fake_add(f, HASH_A_BASEPAK, g_fx_b, 300, 300);
    fake_add(f, HASH_A_PBRSPV, g_fx_c, 70000, 70000);
}

static void fake_add_b(FakeFetch *f) {
    fake_add(f, HASH_B_ENGINE, g_fx_a2, 100000, 100000);
    fake_add(f, HASH_B_EXTRAPAK, g_fx_x, 1000, 1000);
}

static void fake_add_c(FakeFetch *f) {
    fake_add(f, HASH_C_ENGINE, g_fx_right, 300, 300);
    fake_add(f, HASH_C_README, g_fx_n, 42, 42);
}

/* The common stage call shape: configured channel/platform match the signed
 * fixture manifests. */
static bool stage_call(BreakUpdateClient *c, BreakUpdateManifest *m, FakeFetch *f) {
    return break_update_client_stage(c, m, stage_pubkey(), "stable", "linux-x86-64",
                                     fake_fetch, f);
}

/* ---- slot-tree inspection helpers ------------------------------------------ */

/* "<root>/slots/<slot><suffix>" */
static void slot_path_of(const char *root, char slot, const char *suffix,
                         char *out, usize cap) {
    char dir[1200];
    char leaf[1200];
    join_path(dir, sizeof(dir), root, "slots");
    snprintf(leaf, sizeof(leaf), "%c%s", slot, suffix);
    join_path(out, cap, dir, leaf);
}

/* Byte-exact compare of a file against a binary expectation. */
static bool file_bytes_equal_buf(const char *path, const u8 *expect, usize len) {
    u64 size = 0;
    if (!platform_file_size(path, &size)) return false;
    if (size != (u64)len) return false;
    u8 *buf = malloc(len ? len : 1);
    if (!buf) return false;
    usize got = 0;
    FILE *fp = fopen(path, "rb");
    if (fp) {
        if (len) got = fread(buf, 1, len, fp);
        fclose(fp);
    }
    bool ok = fp && got == len && (len == 0 || memcmp(buf, expect, len) == 0);
    free(buf);
    return ok;
}

/* Exact directory membership: count == n and every expected name present
 * (is_dirs may be NULL to skip the file/dir classification check). */
static bool dir_entries_exact(const char *path, const char *const *names,
                              const bool *is_dirs, usize n) {
    PlatformDirEntry entries[32];
    u32 count = 0;
    if (!platform_list_dir(path, entries, 32, &count)) return false;
    if (count != n) return false;
    usize i;
    u32 j;
    for (i = 0; i < n; i++) {
        bool found = false;
        for (j = 0; j < count && j < 32; j++) {
            if (strcmp(entries[j].name, names[i]) == 0) {
                if (is_dirs && entries[j].is_dir != is_dirs[i]) return false;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

static bool slot_file_bytes_equal(const char *root, char slot, const char *name,
                                  const u8 *expect, usize len) {
    char p[1200];
    char f[1200];
    slot_path_of(root, slot, "/files", p, sizeof(p));
    join_path(f, sizeof(f), p, name);
    return file_bytes_equal_buf(f, expect, len);
}

static bool slot_path_absent(const char *root, char slot, const char *suffix) {
    char p[1200];
    u64 sz = 0;
    slot_path_of(root, slot, suffix, p, sizeof(p));
    return !platform_file_size(p, &sz);
}

/* slots/<slot> == {files/ (dir), update-version (file)}. */
static bool slot_top_exact(const char *root, char slot) {
    static const char *const names[] = {"files", "update-version"};
    static const bool dirs[] = {true, false};
    char p[1200];
    slot_path_of(root, slot, "", p, sizeof(p));
    return dir_entries_exact(p, names, dirs, 2);
}

static bool marker_is(const char *root, char slot, const char *version_line) {
    char p[1200];
    slot_path_of(root, slot, "/update-version", p, sizeof(p));
    return file_bytes_equal(p, version_line);
}

/* Slot tree == M_A exactly (byte-exact per chunk, marker 2.0.0, no extras). */
static bool slot_matches_manifest_a(const char *root, char slot) {
    static const char *const dirs3[] = {"bin", "data", "shaders"};
    static const bool isdir3[] = {true, true, true};
    char p[1200];
    if (!slot_top_exact(root, slot)) return false;
    slot_path_of(root, slot, "/files", p, sizeof(p));
    if (!dir_entries_exact(p, dirs3, isdir3, 3)) return false;
    if (!slot_file_bytes_equal(root, slot, "bin/engine", g_fx_a, 100000)) return false;
    if (!slot_file_bytes_equal(root, slot, "data/base.pak", g_fx_b, 300)) return false;
    if (!slot_file_bytes_equal(root, slot, "shaders/pbr.spv", g_fx_c, 70000)) return false;
    return marker_is(root, slot, "2.0.0\n");
}

static bool slot_matches_manifest_b(const char *root, char slot) {
    static const char *const top[] = {"bin", "data"};
    static const bool topd[] = {true, true};
    char p[1200];
    if (!slot_top_exact(root, slot)) return false;
    slot_path_of(root, slot, "/files", p, sizeof(p));
    if (!dir_entries_exact(p, top, topd, 2)) return false;
    if (!slot_file_bytes_equal(root, slot, "bin/engine", g_fx_a2, 100000)) return false;
    if (!slot_file_bytes_equal(root, slot, "data/extra.pak", g_fx_x, 1000)) return false;
    return marker_is(root, slot, "3.0.0\n");
}

static bool slot_matches_manifest_c(const char *root, char slot) {
    static const char *const top[] = {"bin", "readme.txt"};
    static const bool topd[] = {true, false};
    char p[1200];
    if (!slot_top_exact(root, slot)) return false;
    slot_path_of(root, slot, "/files", p, sizeof(p));
    if (!dir_entries_exact(p, top, topd, 2)) return false;
    if (!slot_file_bytes_equal(root, slot, "bin/engine", g_fx_right, 300)) return false;
    if (!slot_file_bytes_equal(root, slot, "readme.txt", g_fx_n, 42)) return false;
    return marker_is(root, slot, "4.0.0\n");
}

/* Zero disk activity below root: chunks/ empty, both slots empty, state file
 * byte-equal to expect_state. */
static bool disk_pristine(const char *root, const char *expect_state) {
    char p[1200];
    u32 files = 99;
    bool part = true;
    if (!chunks_dir_scan(root, &files, &part) || files != 0 || part) return false;
    slot_path_of(root, 'A', "", p, sizeof(p));
    if (!dir_entries_exact(p, NULL, NULL, 0)) return false;
    slot_path_of(root, 'B', "", p, sizeof(p));
    if (!dir_entries_exact(p, NULL, NULL, 0)) return false;
    join_path(p, sizeof(p), root, "state");
    return file_bytes_equal(p, expect_state);
}

/* ---- shared expected states (byte-exact) ------------------------------------ */

static const char STATE_STAGED_A_FRESH[] =
    L_MAGIC L_CUR_N "staged: A\n" L_PEND_N L_CONF_N L_CVER_N L_PVER_N L_MINRB L_RES_N;
static const char STATE_CURRENT_A_PENDING[] =
    L_MAGIC "current: A\n" L_STG_N "pending: yes\n" L_CONF_N
    "current-version: 2.0.0\n" L_PVER_N L_MINRB L_RES_N;
static const char STATE_CURRENT_A_CONFIRMED[] =
    L_MAGIC "current: A\n" L_STG_N L_PEND_N "confirmed: yes\n"
    "current-version: 2.0.0\n" L_PVER_N L_MINRB L_RES_N;

TEST(stage_fixture_vectors_match) {
    /* Fixture-drift guard: the embedded hashes must be the sha256 of the
     * fill_bytes fixtures, or every signed-manifest test fails obscurely. */
    char h[65];
    fill_fx_a();
    fill_fx_b();
    fill_fx_c();
    fill_bytes(g_fx_small, sizeof(g_fx_small), 91);
    hash_hex_of(g_fx_a, 100000, h);
    ASSERT_STR_EQ(h, HASH_A_ENGINE);
    hash_hex_of(g_fx_b, 300, h);
    ASSERT_STR_EQ(h, HASH_A_BASEPAK);
    hash_hex_of(g_fx_c, 70000, h);
    ASSERT_STR_EQ(h, HASH_A_PBRSPV);
    hash_hex_of(g_fx_a2, 100000, h);
    ASSERT_STR_EQ(h, HASH_B_ENGINE);
    hash_hex_of(g_fx_x, 1000, h);
    ASSERT_STR_EQ(h, HASH_B_EXTRAPAK);
    hash_hex_of(g_fx_right, 300, h);
    ASSERT_STR_EQ(h, HASH_C_ENGINE);
    hash_hex_of(g_fx_n, 42, h);
    ASSERT_STR_EQ(h, HASH_C_README);
    hash_hex_of(g_fx_small, 100, h);
    ASSERT_STR_EQ(h, HASH_MINV_CORE);
    /* And the four embedded signatures really verify against the test key. */
    BreakUpdateManifest *m = manifest_a();
    ASSERT_TRUE(break_update_manifest_verify(m, stage_pubkey()));
    break_update_manifest_destroy(m);
    m = manifest_b();
    ASSERT_TRUE(break_update_manifest_verify(m, stage_pubkey()));
    break_update_manifest_destroy(m);
    m = manifest_c();
    ASSERT_TRUE(break_update_manifest_verify(m, stage_pubkey()));
    break_update_manifest_destroy(m);
    m = manifest_minv();
    ASSERT_TRUE(break_update_manifest_verify(m, stage_pubkey()));
    break_update_manifest_destroy(m);
}

TEST(stage_activate_confirm_full_cycle) {
    fill_fx_a();
    BreakUpdateManifest *m = manifest_a();
    char root[512];
    test_tmp(root, sizeof(root), "upc_st_cycle");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);

    /* stage: fetch_all runs (3 chunks missing), then slot A materializes. */
    ASSERT_TRUE(stage_call(c, m, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_TRUE(f.objs[0].calls > 0u && f.objs[1].calls > 0u && f.objs[2].calls > 0u);
    ASSERT_FALSE(f.saw_bad_range);
    ASSERT_TRUE(cas_has(root, HASH_A_ENGINE));
    ASSERT_TRUE(cas_has(root, HASH_A_BASEPAK));
    ASSERT_TRUE(cas_has(root, HASH_A_PBRSPV));
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A'));
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, STATE_STAGED_A_FRESH)); /* mark persisted */
    ASSERT_EQ(break_update_client_current_slot(c), '-');    /* current unchanged */
    slot_path_of(root, 'A', "/files", p, sizeof(p));
    ASSERT_FALSE(dir_has_tmp(p)); /* no writer residue in the slot tree */
    slot_path_of(root, 'A', "", p, sizeof(p));
    ASSERT_FALSE(dir_has_tmp(p));

    /* activate: pure state flip (slots are data); byte-exact persisted first. */
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    ASSERT_TRUE(break_update_client_pending(c));
    ASSERT_FALSE(break_update_client_confirmed(c));
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 2u);
    ASSERT_EQ(v[1], 0u);
    ASSERT_EQ(v[2], 0u);
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, STATE_CURRENT_A_PENDING));
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A')); /* activate touches nothing */

    /* confirm_boot completes the cycle. */
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, STATE_CURRENT_A_CONFIRMED));

    /* Persistence across reopen. */
    break_update_client_destroy(c);
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    ASSERT_TRUE(break_update_client_confirmed(c));
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A'));
    break_update_client_destroy(c);

    break_update_manifest_destroy(m);
    cleanup_root(root);
}

TEST(stage_verify_failure_zero_fetch_zero_disk) {
    /* THE cross-cutting gate: signature BEFORE transport — a VERIFY failure
     * must perform zero fetch calls, zero disk writes, zero state changes. */
    fill_fx_a();
    ManChunk chunks[] = {
        {"bin/engine", HASH_A_ENGINE, 100000},
        {"data/base.pak", HASH_A_BASEPAK, 300},
        {"shaders/pbr.spv", HASH_A_PBRSPV, 70000},
    };
    /* Structurally valid (canonical zero signature) but cryptographically
     * wrong: parses, never verifies. */
    BreakUpdateManifest *m = signed_manifest("2.0.0", "0.0.0", chunks, 3, ZERO_SIG_B64);

    char root[512];
    test_tmp(root, sizeof(root), "upc_st_verify");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);

    ASSERT_FALSE(stage_call(c, m, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_VERIFY);
    ASSERT_EQ(f.total_calls, (u64)0); /* zero transport — the pinned gate */
    ASSERT_TRUE(disk_pristine(root, INITIAL_STATE));
    ASSERT_FALSE(dir_has_tmp(root));

    /* Real signature + wrong key: indistinguishable refusal, still zero. */
    break_update_manifest_destroy(m);
    m = manifest_a();
    u8 wrong[32];
    memcpy(wrong, stage_pubkey(), 32);
    wrong[0] ^= 0x01;
    ASSERT_FALSE(break_update_client_stage(c, m, wrong, "stable", "linux-x86-64",
                                           fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_VERIFY);
    ASSERT_EQ(f.total_calls, (u64)0);
    ASSERT_TRUE(disk_pristine(root, INITIAL_STATE));

    /* Control: the same manifest with the right key stages fine. */
    ASSERT_TRUE(stage_call(c, m, &f));
    ASSERT_TRUE(f.total_calls > 0u);
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A'));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(stage_policy_channel_platform_mismatch) {
    fill_fx_a();
    BreakUpdateManifest *m = manifest_a(); /* valid signature */
    char root[512];
    test_tmp(root, sizeof(root), "upc_st_policy");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);

    ASSERT_FALSE(break_update_client_stage(c, m, stage_pubkey(), "beta",
                                           "linux-x86-64", fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_POLICY);
    ASSERT_EQ(f.total_calls, (u64)0); /* policy precedes transport too */
    ASSERT_TRUE(disk_pristine(root, INITIAL_STATE));

    ASSERT_FALSE(break_update_client_stage(c, m, stage_pubkey(), "stable",
                                           "windows-x86-64", fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_POLICY);
    ASSERT_EQ(f.total_calls, (u64)0);
    ASSERT_TRUE(disk_pristine(root, INITIAL_STATE));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(stage_policy_min_version) {
    fill_fx_a();
    fill_bytes(g_fx_small, sizeof(g_fx_small), 91);
    BreakUpdateManifest *m = manifest_minv(); /* min-version 2.0.0, signed */

    /* (a) current version 1.0.0 < manifest min-version 2.0.0 → POLICY. */
    static const char current_v1[] =
        L_MAGIC "current: A\n" L_STG_N L_PEND_N "confirmed: yes\n"
        "current-version: 1.0.0\n" L_PVER_N L_MINRB L_RES_N;
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_st_minv",
                                           current_v1);
    ASSERT_NOT_NULL(c);
    /* The live slot holds a marker-less fixture file (content irrelevant). */
    char p[1200];
    slot_path_of(root, 'A', "/files", p, sizeof(p));
    ASSERT_EQ(TEST_MKDIR(p), 0);
    char fpath[1200];
    join_path(fpath, sizeof(fpath), p, "old.bin");
    ASSERT_TRUE(write_file(fpath, "old-bytes", 9));
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add(&f, HASH_MINV_CORE, g_fx_small, 100, 100);
    ASSERT_FALSE(stage_call(c, m, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_POLICY);
    ASSERT_EQ(f.total_calls, (u64)0);
    ASSERT_TRUE(file_bytes_equal_buf(fpath, (const u8 *)"old-bytes", 9)); /* intact */
    slot_path_of(root, 'B', "", p, sizeof(p));
    ASSERT_TRUE(dir_entries_exact(p, NULL, NULL, 0));
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, current_v1));
    break_update_client_destroy(c);
    cleanup_root(root);

    /* (b) fresh client (current=none → source 0.0.0): the same floor refuses
     * — documented semantics: only a 0.0.0-floor payload provisions fresh. */
    test_tmp(root, sizeof(root), "upc_st_minv_fresh");
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(stage_call(c, m, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_POLICY);
    ASSERT_EQ(f.total_calls, (u64)0);
    ASSERT_TRUE(disk_pristine(root, INITIAL_STATE));

    /* (c) a 0.0.0-floor manifest stages fine on the same fresh client. */
    BreakUpdateManifest *ma = manifest_a();
    fake_reset_phase(&f);
    fake_add_a(&f);
    ASSERT_TRUE(stage_call(c, ma, &f));
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A'));
    break_update_manifest_destroy(ma);
    break_update_client_destroy(c);
    cleanup_root(root);

    break_update_manifest_destroy(m);
}

TEST(stage_while_staged_refused) {
    fill_fx_a();
    fill_fx_b();
    fill_fx_c();
    BreakUpdateManifest *ma = manifest_a();
    BreakUpdateManifest *mb = manifest_b();
    BreakUpdateManifest *mc = manifest_c();
    char root[512];
    test_tmp(root, sizeof(root), "upc_st_twice");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);
    fake_add_b(&f);
    fake_add_c(&f);

    /* Live current A v2.0.0 (so the M_B/M_C policy floors 1.0.0/2.0.0 pass
     * and the staged interlock is what actually refuses). */
    ASSERT_TRUE(stage_call(c, ma, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    fake_reset_phase(&f);
    ASSERT_TRUE(stage_call(c, mb, &f));
    ASSERT_TRUE(slot_matches_manifest_b(root, 'B'));
    static const char staged_b[] =
        L_MAGIC "current: A\n" "staged: B\n" L_PEND_N "confirmed: yes\n"
        "current-version: 2.0.0\n" L_PVER_N L_MINRB L_RES_N;

    fake_reset_phase(&f);
    /* The plan designates unstage as the ONLY non-activating clear: a second
     * stage while staged refuses with STATE, zero transport, zero changes. */
    ASSERT_FALSE(stage_call(c, mc, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_EQ(f.total_calls, (u64)0);
    ASSERT_TRUE(slot_matches_manifest_b(root, 'B')); /* staged tree untouched */
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, staged_b));

    /* unstage + stage IS the re-stage path. */
    ASSERT_TRUE(break_update_client_unstage(c));
    ASSERT_TRUE(stage_call(c, mc, &f));
    ASSERT_TRUE(slot_matches_manifest_c(root, 'B'));

    break_update_manifest_destroy(ma);
    break_update_manifest_destroy(mb);
    break_update_manifest_destroy(mc);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(stage_fetch_failure_keeps_resume_and_slots) {
    fill_fx_b();
    BreakUpdateManifest *mb = manifest_b();
    /* current=A v1.0.0 confirmed with a fixture file in the LIVE slot. */
    static const char current_v1[] =
        L_MAGIC "current: A\n" L_STG_N L_PEND_N "confirmed: yes\n"
        "current-version: 1.0.0\n" L_PVER_N L_MINRB L_RES_N;
    char root[512];
    BreakUpdateClient *c = open_with_state(root, sizeof(root), "upc_st_fetchfail",
                                           current_v1);
    ASSERT_NOT_NULL(c);
    char p[1200];
    slot_path_of(root, 'A', "/files", p, sizeof(p));
    ASSERT_EQ(TEST_MKDIR(p), 0);
    char fpath[1200];
    join_path(fpath, sizeof(fpath), p, "old.bin");
    ASSERT_TRUE(write_file(fpath, "old-bytes", 9));
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_b(&f);
    /* Die after the first block of bin/engine. */
    memcpy(f.fail_obj, HASH_B_ENGINE, 65);
    f.fail_after_bytes = 1;

    ASSERT_FALSE(stage_call(c, mb, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_FETCH);
    /* A transport failure touches NO slot: the live slot's bytes and the
     * (empty) inactive slot are exactly as before; resume progress persists. */
    ASSERT_TRUE(file_bytes_equal_buf(fpath, (const u8 *)"old-bytes", 9));
    slot_path_of(root, 'B', "", p, sizeof(p));
    ASSERT_TRUE(dir_entries_exact(p, NULL, NULL, 0));
    ASSERT_TRUE(state_contains(root, "resume-chunk: " HASH_B_ENGINE "|"));
    join_path(p, sizeof(p), root, "state");
    ASSERT_FALSE(file_bytes_equal(p, current_v1)); /* resume line differs */
    break_update_client_destroy(c);

    /* Retry with a healthy transport: resumes at the byte boundary, then
     * materializes into B; the live slot A still keeps its bytes. */
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    fake_reset_phase(&f);
    ASSERT_TRUE(stage_call(c, mb, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_TRUE(slot_matches_manifest_b(root, 'B'));
    ASSERT_TRUE(file_bytes_equal_buf(fpath, (const u8 *)"old-bytes", 9));

    break_update_manifest_destroy(mb);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(stage_materialize_failure_cleans_slot) {
    fill_fx_a();
    BreakUpdateManifest *m = manifest_a();
    char root[512];
    test_tmp(root, sizeof(root), "upc_st_matfail");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    /* Pre-seed the whole CAS: fetch_all becomes a zero-transport no-op, so a
     * materialize failure leaves the state file BYTE-UNCHANGED (no resume
     * progress either) — "state unchanged except resume progress", exactly. */
    ASSERT_TRUE(cas_put(root, g_fx_a, 100000));
    ASSERT_TRUE(cas_put(root, g_fx_b, 300));
    ASSERT_TRUE(cas_put(root, g_fx_c, 70000));
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);

    /* Injection: slots/A is a regular FILE — the clean cannot fix that (it
     * never removes the slot dir itself), mkdir of files/ fails (ENOTDIR). */
    char p[1200];
    slot_path_of(root, 'A', "", p, sizeof(p));
    ASSERT_EQ(TEST_RMDIR(p), 0);
    ASSERT_TRUE(write_file(p, "jam", 3));
    ASSERT_FALSE(stage_call(c, m, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_IO);
    ASSERT_EQ(f.total_calls, (u64)0); /* CAS hit ⇒ zero transport by design */
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE)); /* nothing persisted */

    /* Repair → retry succeeds (no wedge). */
    slot_path_of(root, 'A', "", p, sizeof(p));
    ASSERT_EQ(remove(p), 0);
    ASSERT_EQ(TEST_MKDIR(p), 0);
    ASSERT_TRUE(stage_call(c, m, &f));
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A'));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(activate_without_stage_state) {
    fill_fx_a();
    BreakUpdateManifest *m = manifest_a();
    char root[512];
    test_tmp(root, sizeof(root), "upc_act_none");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    ASSERT_FALSE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));

    /* Chunks in the CAS do NOT imply staged: fetch_all then activate still
     * refuses (only the full stage marks staged). */
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);
    ASSERT_TRUE(break_update_client_fetch_all(c, m, fake_fetch, &f));
    ASSERT_FALSE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(activate_marker_missing_or_corrupt) {
    fill_fx_a();
    BreakUpdateManifest *m = manifest_a();
    char root[512];
    test_tmp(root, sizeof(root), "upc_act_marker");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);
    ASSERT_TRUE(stage_call(c, m, &f));

    /* Marker removed (partial-tree window): activate fails closed — IO, no
     * flip, state byte-unchanged. */
    char p[1200];
    char st[1200];
    slot_path_of(root, 'A', "/update-version", p, sizeof(p));
    ASSERT_EQ(remove(p), 0);
    ASSERT_FALSE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_IO);
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    join_path(st, sizeof(st), root, "state");
    ASSERT_TRUE(file_bytes_equal(st, STATE_STAGED_A_FRESH));

    /* Corrupt marker (not a canonical version line): same refusal. */
    ASSERT_TRUE(write_file(p, "not-a-version\n", 14));
    ASSERT_FALSE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_IO);
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    ASSERT_TRUE(file_bytes_equal(st, STATE_STAGED_A_FRESH));

    /* Restored marker → activate succeeds (no wedge). */
    ASSERT_TRUE(write_file(p, "2.0.0\n", 6));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    ASSERT_TRUE(break_update_client_pending(c));
    ASSERT_TRUE(file_bytes_equal(st, STATE_CURRENT_A_PENDING));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(rollback_after_activate_preconfirm) {
    fill_fx_a();
    fill_fx_b();
    BreakUpdateManifest *ma = manifest_a();
    BreakUpdateManifest *mb = manifest_b();
    char root[512];
    test_tmp(root, sizeof(root), "upc_rb_preconf");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);
    fake_add_b(&f);

    /* First activation ever: no previous — rollback refused even pending. */
    ASSERT_TRUE(stage_call(c, ma, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_FALSE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_TRUE(break_update_client_confirm_boot(c)); /* A = v2.0.0 live */

    /* Second update: stage B → activate → pending (previous = A 2.0.0). */
    fake_reset_phase(&f);
    ASSERT_TRUE(stage_call(c, mb, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 3u);
    ASSERT_TRUE(break_update_client_pending(c));

    /* Pre-confirm rollback: flips back, pending cleared, known-good mark. */
    ASSERT_TRUE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 2u);
    ASSERT_FALSE(break_update_client_pending(c));
    ASSERT_TRUE(break_update_client_confirmed(c));
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A')); /* rollback touches no tree */
    ASSERT_TRUE(slot_matches_manifest_b(root, 'B'));
    static const char rolled_back[] =
        L_MAGIC "current: A\n" L_STG_N L_PEND_N "confirmed: yes\n"
        "current-version: 2.0.0\n" "previous-version: 3.0.0\n" L_MINRB L_RES_N;
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, rolled_back));

    break_update_manifest_destroy(ma);
    break_update_manifest_destroy(mb);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(rollback_after_confirm_and_floor) {
    fill_fx_a();
    fill_fx_b();
    BreakUpdateManifest *ma = manifest_a();
    BreakUpdateManifest *mb = manifest_b();
    char root[512];
    test_tmp(root, sizeof(root), "upc_rb_postconf");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);
    fake_add_b(&f);
    ASSERT_TRUE(stage_call(c, ma, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    fake_reset_phase(&f);
    ASSERT_TRUE(stage_call(c, mb, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_TRUE(break_update_client_confirm_boot(c)); /* B v3 confirmed, prev A v2 */

    /* Post-confirm rollback is allowed while the previous slot is retained
     * (floor 0.0.0 ≤ 2.0.0). */
    ASSERT_TRUE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    /* …and back (both slots ≥ floor: ping-pong at the state level). */
    ASSERT_TRUE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 3u);
    break_update_client_destroy(c);
    cleanup_root(root);

    /* Below the min-rollback floor → POLICY (the floor is product policy —
     * no client API mutates it this phase, so craft it). A fixture file in
     * the current slot stays untouched by the refusal. */
    static const char floored[] =
        L_MAGIC "current: B\n" L_STG_N L_PEND_N "confirmed: yes\n"
        "current-version: 3.0.0\n" "previous-version: 2.0.0\n"
        "min-rollback-version: 3.0.0\n" L_RES_N;
    c = open_with_state(root, sizeof(root), "upc_rb_floor3", floored);
    ASSERT_NOT_NULL(c);
    char fp_[1200];
    slot_path_of(root, 'B', "/files", fp_, sizeof(fp_));
    ASSERT_EQ(TEST_MKDIR(fp_), 0);
    {
        char ffile[1200];
        join_path(ffile, sizeof(ffile), fp_, "keep.bin");
        ASSERT_TRUE(write_file(ffile, "keep", 4));
    }
    ASSERT_FALSE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_POLICY);
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, floored));
    {
        char ffile[1200];
        join_path(ffile, sizeof(ffile), fp_, "keep.bin");
        ASSERT_TRUE(file_bytes_equal(ffile, "keep")); /* refusal touches nothing */
    }
    break_update_client_destroy(c);
    cleanup_root(root);

    break_update_manifest_destroy(ma);
    break_update_manifest_destroy(mb);
}

TEST(rollback_while_staged_then_unstage_allows) {
    fill_fx_a();
    fill_fx_b();
    fill_fx_c();
    BreakUpdateManifest *ma = manifest_a();
    BreakUpdateManifest *mb = manifest_b();
    BreakUpdateManifest *mc = manifest_c();
    char root[512];
    test_tmp(root, sizeof(root), "upc_rb_staged");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);
    fake_add_b(&f);
    fake_add_c(&f);
    /* Reach current=B v3.0.0 confirmed, previous=A v2.0.0. */
    ASSERT_TRUE(stage_call(c, ma, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    fake_reset_phase(&f);
    ASSERT_TRUE(stage_call(c, mb, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_TRUE(break_update_client_confirm_boot(c));

    /* Stage M_C into A: the clean consumes the retained previous tree — the
     * exact reason rollback interlocks on staged. */
    fake_reset_phase(&f);
    ASSERT_TRUE(stage_call(c, mc, &f));
    ASSERT_TRUE(slot_matches_manifest_c(root, 'A'));
    ASSERT_TRUE(slot_path_absent(root, 'A', "/files/data/base.pak")); /* stale gone */
    ASSERT_FALSE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);

    /* unstage: mark cleared (persisted first), staged tree removed. */
    ASSERT_TRUE(break_update_client_unstage(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_OK);
    char p[1200];
    slot_path_of(root, 'A', "", p, sizeof(p));
    ASSERT_TRUE(dir_entries_exact(p, NULL, NULL, 0)); /* slot A empty */
    static const char unstaged[] =
        L_MAGIC "current: B\n" L_STG_N L_PEND_N "confirmed: yes\n"
        "current-version: 3.0.0\n" "previous-version: 2.0.0\n" L_MINRB L_RES_N;
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, unstaged));

    /* Rollback allowed again (version policy; previous-version 2.0.0 ≥ floor)
     * — a pure pointer flip: slot A's tree was consumed by the stage+unstage
     * cycle (documented 2-slot A/B caveat); slot B keeps M_B byte-exactly. */
    ASSERT_TRUE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 2u);
    ASSERT_TRUE(slot_matches_manifest_b(root, 'B'));
    slot_path_of(root, 'A', "", p, sizeof(p));
    ASSERT_TRUE(dir_entries_exact(p, NULL, NULL, 0));
    static const char after_rb[] =
        L_MAGIC "current: A\n" L_STG_N L_PEND_N "confirmed: yes\n"
        "current-version: 2.0.0\n" "previous-version: 3.0.0\n" L_MINRB L_RES_N;
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, after_rb));

    break_update_manifest_destroy(ma);
    break_update_manifest_destroy(mb);
    break_update_manifest_destroy(mc);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(unstage_without_staged) {
    fill_fx_a();
    BreakUpdateManifest *ma = manifest_a();
    char root[512];
    test_tmp(root, sizeof(root), "upc_unst_none");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);

    /* Fresh: nothing staged → false + STATE, state byte-unchanged. */
    ASSERT_FALSE(break_update_client_unstage(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, INITIAL_STATE));

    /* After ACTIVATE there is no staged slot anymore: unstage cannot touch
     * the live slot (pending=yes) → false + STATE, nothing changes. */
    ASSERT_TRUE(stage_call(c, ma, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_FALSE(break_update_client_unstage(c));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_TRUE(break_update_client_pending(c));
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A'));
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    ASSERT_FALSE(break_update_client_unstage(c)); /* confirmed: still none staged */
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_STATE);
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A'));

    break_update_manifest_destroy(ma);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(restage_cycle_a_b_a) {
    fill_fx_a();
    fill_fx_b();
    fill_fx_c();
    BreakUpdateManifest *ma = manifest_a();
    BreakUpdateManifest *mb = manifest_b();
    BreakUpdateManifest *mc = manifest_c();
    char root[512];
    test_tmp(root, sizeof(root), "upc_cycle_aba");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);
    fake_add_b(&f);
    fake_add_c(&f);

    /* A: v2.0.0 live (first activation picks slot A — the fixed fresh choice). */
    ASSERT_TRUE(stage_call(c, ma, &f));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    /* B: v3.0.0 live; previous = A 2.0.0. */
    fake_reset_phase(&f);
    ASSERT_TRUE(stage_call(c, mb, &f));
    ASSERT_EQ(f.total_calls, (u64)3); /* engine 2 blocks + extra.pak 1 (no dedup yet) */
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    ASSERT_TRUE(slot_matches_manifest_b(root, 'B'));
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A')); /* retained previous intact */

    /* A again: v4.0.0 staged over the RETAINED slot — the clean must make the
     * slot exactly M_C (M_A-only names base.pak/pbr.spv must vanish). */
    fake_reset_phase(&f);
    ASSERT_TRUE(stage_call(c, mc, &f));
    ASSERT_TRUE(slot_matches_manifest_c(root, 'A'));
    ASSERT_TRUE(slot_path_absent(root, 'A', "/files/data/base.pak"));
    ASSERT_TRUE(slot_path_absent(root, 'A', "/files/shaders/pbr.spv"));
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    u32 v[3] = {0, 0, 0};
    break_update_client_current_version(c, v);
    ASSERT_EQ(v[0], 4u);
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    static const char cycle_state[] =
        L_MAGIC "current: A\n" L_STG_N L_PEND_N "confirmed: yes\n"
        "current-version: 4.0.0\n" "previous-version: 3.0.0\n" L_MINRB L_RES_N;
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, cycle_state));

    /* Rollback to B: B was never re-staged since its activation → its content
     * IS guaranteed — byte-exact M_B after the flip. */
    ASSERT_TRUE(break_update_client_rollback(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'B');
    ASSERT_TRUE(slot_matches_manifest_b(root, 'B'));
    ASSERT_TRUE(slot_matches_manifest_c(root, 'A'));

    break_update_manifest_destroy(ma);
    break_update_manifest_destroy(mb);
    break_update_manifest_destroy(mc);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(crash_between_stage_and_activate_reopen) {
    fill_fx_a();
    BreakUpdateManifest *m = manifest_a();
    char root[512];
    test_tmp(root, sizeof(root), "upc_crash_stage");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);
    ASSERT_TRUE(stage_call(c, m, &f));

    /* Crash simulation: the process dies between stage and activate. */
    break_update_client_destroy(c);
    c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    /* State consistent: staged intact (slot + state), current unchanged. */
    ASSERT_EQ(break_update_client_current_slot(c), '-');
    ASSERT_FALSE(break_update_client_pending(c));
    ASSERT_TRUE(slot_matches_manifest_a(root, 'A'));
    ASSERT_TRUE(cas_bytes_equal(root, HASH_A_ENGINE, g_fx_a, 100000));
    char p[1200];
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, STATE_STAGED_A_FRESH));

    /* The staged update survives the crash and activates normally. */
    ASSERT_TRUE(break_update_client_activate(c));
    ASSERT_EQ(break_update_client_current_slot(c), 'A');
    ASSERT_TRUE(break_update_client_confirm_boot(c));
    join_path(p, sizeof(p), root, "state");
    ASSERT_TRUE(file_bytes_equal(p, STATE_CURRENT_A_CONFIRMED));

    break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    cleanup_root(root);
}

TEST(stage_null_args) {
    fill_fx_a();
    BreakUpdateManifest *m = manifest_a();
    char root[512];
    test_tmp(root, sizeof(root), "upc_st_null");
    BreakUpdateClient *c = break_update_client_open(root);
    ASSERT_NOT_NULL(c);
    FakeFetch f;
    memset(&f, 0, sizeof(f));
    fake_add_a(&f);

    ASSERT_FALSE(break_update_client_stage(NULL, m, stage_pubkey(), "stable",
                                           "linux-x86-64", fake_fetch, &f));
    ASSERT_FALSE(break_update_client_stage(c, NULL, stage_pubkey(), "stable",
                                           "linux-x86-64", fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_INVALID);
    ASSERT_FALSE(break_update_client_stage(c, m, NULL, "stable", "linux-x86-64",
                                           fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_INVALID);
    ASSERT_FALSE(break_update_client_stage(c, m, stage_pubkey(), NULL,
                                           "linux-x86-64", fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_INVALID);
    ASSERT_FALSE(break_update_client_stage(c, m, stage_pubkey(), "stable", NULL,
                                           fake_fetch, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_INVALID);
    ASSERT_FALSE(break_update_client_stage(c, m, stage_pubkey(), "stable",
                                           "linux-x86-64", NULL, &f));
    ASSERT_EQ(break_update_client_last_error(c), BREAK_UPDATE_CLIENT_INVALID);
    ASSERT_EQ(f.total_calls, (u64)0); /* nothing attempted */
    ASSERT_TRUE(disk_pristine(root, INITIAL_STATE));
    ASSERT_FALSE(break_update_client_activate(NULL));
    ASSERT_FALSE(break_update_client_unstage(NULL));

    break_update_manifest_destroy(m);
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
    RUN_TEST(fetch_all_full_download_cas_dedup);
    RUN_TEST(fetch_all_midchunk_resume);
    RUN_TEST(fetch_all_completed_chunk_not_refetched_across_reopen);
    RUN_TEST(fetch_all_hash_mismatch_verify);
    RUN_TEST(fetch_all_corrupt_resume_state);
    RUN_TEST(fetch_all_stale_resume_self_heals);
    RUN_TEST(fetch_all_zero_byte_chunk);
    RUN_TEST(fetch_all_empty_manifest);
    RUN_TEST(fetch_all_offset_len_overflow_clamped);
    RUN_TEST(fetch_all_null_args);
    RUN_TEST(confirm_boot_preserves_resume_line);
    RUN_TEST(stage_fixture_vectors_match);
    RUN_TEST(stage_activate_confirm_full_cycle);
    RUN_TEST(stage_verify_failure_zero_fetch_zero_disk);
    RUN_TEST(stage_policy_channel_platform_mismatch);
    RUN_TEST(stage_policy_min_version);
    RUN_TEST(stage_while_staged_refused);
    RUN_TEST(stage_fetch_failure_keeps_resume_and_slots);
    RUN_TEST(stage_materialize_failure_cleans_slot);
    RUN_TEST(activate_without_stage_state);
    RUN_TEST(activate_marker_missing_or_corrupt);
    RUN_TEST(rollback_after_activate_preconfirm);
    RUN_TEST(rollback_after_confirm_and_floor);
    RUN_TEST(rollback_while_staged_then_unstage_allows);
    RUN_TEST(unstage_without_staged);
    RUN_TEST(restage_cycle_a_b_a);
    RUN_TEST(crash_between_stage_and_activate_reopen);
    RUN_TEST(stage_null_args);
TEST_MAIN_END()
