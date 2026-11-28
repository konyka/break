/* Per-device AUTH v2 keyring: add/remove, constant-time resolve and
 * all-or-nothing diff reload from a keyring file. */
#include "test_framework.h"

#include <stdio.h>
#include <string.h>

#include <network/break_keyring.h>

typedef struct TestKey {
    u8 id[8];
    u8 psk[32];
} TestKey;

static TestKey test_key(u8 seed)
{
    TestKey k;
    u32 i;
    for (i = 0u; i < 8u; i++) k.id[i] = (u8)(seed * 17u + i);
    for (i = 0u; i < 32u; i++) k.psk[i] = (u8)(seed * 29u + i * 3u + 1u);
    return k;
}

/* "<16 hex id> <64 hex psk>" without a line end into out (82 bytes). */
static void test_key_line(const TestKey *k, char out[82])
{
    u32 i;
    for (i = 0u; i < 8u; i++) snprintf(out + 2u * i, 3u, "%02x", k->id[i]);
    out[16] = ' ';
    for (i = 0u; i < 32u; i++) snprintf(out + 17u + 2u * i, 3u, "%02X", k->psk[i]);
}

static bool resolves_to(BreakKeyring *ring, const TestKey *k)
{
    u8 out[32];
    if (!break_keyring_resolve(ring, k->id, out)) return false;
    return memcmp(out, k->psk, 32u) == 0;
}

static const char *test_file_path(char *buf, size_t cap, const char *name)
{
    snprintf(buf, cap, "break_keyring_%s_%d.txt", name, (int)TEST_GETPID());
    return buf;
}

static bool write_file(const char *path, const char *text, size_t len)
{
    FILE *f = fopen(path, "wb");
    size_t n;
    if (f == NULL) return false;
    n = fwrite(text, 1u, len, f);
    return fclose(f) == 0 && n == len;
}

/* Writes text to a fresh file, loads it and removes the file. */
static BreakKeyringLoadResult load_via_file(BreakKeyring *ring, const char *name,
                                            const char *text, size_t len,
                                            BreakKeyringRevokedFn revoked, void *user,
                                            bool *written)
{
    char path[128];
    BreakKeyringLoadResult result;
    test_file_path(path, sizeof(path), name);
    *written = write_file(path, text, len);
    result = break_keyring_load_file(ring, path, revoked, user);
    remove(path);
    return result;
}

typedef struct RevokedLog {
    u32 count;
    u8 ids[8][8];
    bool resolved_inside[8];
    BreakKeyring *ring;
} RevokedLog;

static void record_revoked(void *user, const u8 key_id[8])
{
    RevokedLog *log = (RevokedLog *)user;
    if (log->count < 8u) {
        u8 psk[32];
        memcpy(log->ids[log->count], key_id, 8u);
        log->resolved_inside[log->count] =
            log->ring != NULL && break_keyring_resolve(log->ring, key_id, psk);
    }
    log->count++;
}

TEST(keyring_add_remove_and_capacity)
{
    TestKey a = test_key(1u);
    TestKey b = test_key(2u);
    BreakKeyring *small;
    BreakKeyring *big;
    ASSERT_TRUE(break_keyring_create(0u) == NULL);
    ASSERT_TRUE(break_keyring_create(BREAK_KEYRING_MAX_KEYS + 1u) == NULL);
    big = break_keyring_create(BREAK_KEYRING_MAX_KEYS);
    ASSERT_NOT_NULL(big);
    break_keyring_destroy(big);
    small = break_keyring_create(1u);
    ASSERT_NOT_NULL(small);
    ASSERT_EQ(break_keyring_count(small), 0u);
    ASSERT_TRUE(break_keyring_add(small, a.id, a.psk));
    ASSERT_EQ(break_keyring_count(small), 1u);
    /* the same id again is refused, even with another psk */
    ASSERT_FALSE(break_keyring_add(small, a.id, b.psk));
    /* the ring is full */
    ASSERT_FALSE(break_keyring_add(small, b.id, b.psk));
    ASSERT_EQ(break_keyring_count(small), 1u);
    ASSERT_FALSE(break_keyring_remove(small, b.id));
    ASSERT_TRUE(break_keyring_remove(small, a.id));
    ASSERT_EQ(break_keyring_count(small), 0u);
    ASSERT_FALSE(break_keyring_remove(small, a.id));
    /* the freed slot takes a new key */
    ASSERT_TRUE(break_keyring_add(small, b.id, b.psk));
    ASSERT_TRUE(resolves_to(small, &b));
    ASSERT_FALSE(break_keyring_add(NULL, a.id, a.psk));
    ASSERT_FALSE(break_keyring_add(small, NULL, a.psk));
    ASSERT_FALSE(break_keyring_add(small, a.id, NULL));
    ASSERT_FALSE(break_keyring_remove(NULL, b.id));
    ASSERT_FALSE(break_keyring_remove(small, NULL));
    ASSERT_EQ(break_keyring_count(NULL), 0u);
    break_keyring_destroy(small);
    break_keyring_destroy(NULL);
}

TEST(keyring_resolve_returns_the_psk_and_leaves_misses_alone)
{
    TestKey a = test_key(1u);
    TestKey b = test_key(2u);
    TestKey c = test_key(3u);
    u8 out[32];
    u8 untouched[32];
    BreakKeyring *ring = break_keyring_create(4u);
    ASSERT_NOT_NULL(ring);
    ASSERT_TRUE(break_keyring_add(ring, a.id, a.psk));
    ASSERT_TRUE(break_keyring_add(ring, b.id, b.psk));
    ASSERT_TRUE(break_keyring_resolve(ring, b.id, out));
    ASSERT_TRUE(memcmp(out, b.psk, 32u) == 0);
    ASSERT_TRUE(break_keyring_resolve(ring, a.id, out));
    ASSERT_TRUE(memcmp(out, a.psk, 32u) == 0);
    memset(untouched, 0xAA, sizeof(untouched));
    memset(out, 0xAA, sizeof(out));
    ASSERT_FALSE(break_keyring_resolve(ring, c.id, out));
    ASSERT_TRUE(memcmp(out, untouched, 32u) == 0);
    /* an id differing from a stored one in its last byte only is a miss */
    c = a;
    c.id[7] ^= 0x01u;
    ASSERT_FALSE(break_keyring_resolve(ring, c.id, out));
    ASSERT_TRUE(memcmp(out, untouched, 32u) == 0);
    /* free and wiped slots hold an all-zero id and psk; an all-zero id (the
     * built-in client's default) must not match them */
    memset(c.id, 0, sizeof(c.id));
    ASSERT_FALSE(break_keyring_resolve(ring, c.id, out));
    ASSERT_TRUE(memcmp(out, untouched, 32u) == 0);
    ASSERT_TRUE(break_keyring_remove(ring, b.id));
    ASSERT_FALSE(break_keyring_resolve(ring, c.id, out));
    ASSERT_TRUE(memcmp(out, untouched, 32u) == 0);
    ASSERT_FALSE(break_keyring_resolve(NULL, a.id, out));
    ASSERT_FALSE(break_keyring_resolve(ring, NULL, out));
    ASSERT_FALSE(break_keyring_resolve(ring, a.id, NULL));
    ASSERT_TRUE(memcmp(out, untouched, 32u) == 0);
    break_keyring_destroy(ring);
}

TEST(keyring_load_accepts_comments_blank_lines_and_crlf)
{
    TestKey a = test_key(1u);
    TestKey b = test_key(2u);
    char la[82];
    char lb[82];
    char text[512];
    int len;
    bool written;
    BreakKeyringLoadResult result;
    BreakKeyring *ring = break_keyring_create(4u);
    ASSERT_NOT_NULL(ring);
    test_key_line(&a, la);
    test_key_line(&b, lb);
    len = snprintf(text, sizeof(text), "# devices\r\n%.81s\r\n\r\n\n%.81s", la, lb);
    ASSERT_TRUE(len > 0 && (size_t)len < sizeof(text));
    result = load_via_file(ring, "crlf", text, (size_t)len, NULL, NULL, &written);
    ASSERT_TRUE(written);
    ASSERT_EQ(result, BREAK_KEYRING_LOAD_OK);
    ASSERT_EQ(break_keyring_count(ring), 2u);
    ASSERT_TRUE(resolves_to(ring, &a));
    ASSERT_TRUE(resolves_to(ring, &b));
    break_keyring_destroy(ring);
}

TEST(keyring_load_rejects_each_malformed_shape_and_leaves_the_ring)
{
    TestKey orig = test_key(9u);
    TestKey a = test_key(1u);
    TestKey b = test_key(2u);
    TestKey c = test_key(3u);
    char lo[82];
    char la[82];
    char lb[82];
    char lc[82];
    char bad[82];
    char text[1024];
    char path[128];
    RevokedLog log;
    bool written;
    BreakKeyringLoadResult result;
    u32 shape;
    BreakKeyring *ring = break_keyring_create(2u);
    ASSERT_NOT_NULL(ring);
    ASSERT_TRUE(break_keyring_add(ring, orig.id, orig.psk));
    test_key_line(&orig, lo);
    test_key_line(&a, la);
    test_key_line(&b, lb);
    test_key_line(&c, lc);
    for (shape = 0u; shape < 8u; shape++) {
        BreakKeyringLoadResult expect = BREAK_KEYRING_LOAD_MALFORMED;
        int len = 0;
        memset(&log, 0, sizeof(log));
        log.ring = ring;
        /* each file starts with a valid line for a new key, so a parser that
         * applied lines as it read them would change the ring */
        memcpy(bad, lb, sizeof(bad));
        switch (shape) {
        case 0u: /* 80 chars: a 15-char id */
            len = snprintf(text, sizeof(text), "%.81s\n%.15s %.64s\n", la, lb, lb + 17);
            break;
        case 1u: /* tab instead of the space */
            bad[16] = '\t';
            len = snprintf(text, sizeof(text), "%.81s\n%.81s\n", la, bad);
            break;
        case 2u: /* non-hex id */
            bad[3] = 'g';
            len = snprintf(text, sizeof(text), "%.81s\n%.81s\n", la, bad);
            break;
        case 3u: /* non-hex psk */
            bad[80] = 'z';
            len = snprintf(text, sizeof(text), "%.81s\n%.81s\n", la, bad);
            break;
        case 4u: /* duplicate id with another psk */
            memcpy(bad, la, 17u);
            len = snprintf(text, sizeof(text), "%.81s\n%.81s\n", la, bad);
            break;
        case 5u: /* three keys into a capacity-2 ring */
            expect = BREAK_KEYRING_LOAD_TOO_LARGE;
            len = snprintf(text, sizeof(text), "%.81s\n%.81s\n%.81s\n", la, lb, lc);
            break;
        case 6u: /* only comments */
            expect = BREAK_KEYRING_LOAD_EMPTY;
            len = snprintf(text, sizeof(text), "# one\n\n# %.81s\n", lo);
            break;
        default: /* missing file */
            expect = BREAK_KEYRING_LOAD_UNREADABLE;
            break;
        }
        if (shape == 7u) {
            written = true;
            result = break_keyring_load_file(ring, test_file_path(path, sizeof(path),
                                                                  "missing"),
                                             record_revoked, &log);
        } else {
            written = len > 0 && (size_t)len < sizeof(text);
            if (written) {
                result = load_via_file(ring, "malformed", text, (size_t)len,
                                       record_revoked, &log, &written);
            } else {
                result = BREAK_KEYRING_LOAD_OK;
            }
        }
        if (!written || result != expect) {
            printf("(shape %u) ", (unsigned)shape);
        }
        ASSERT_TRUE(written);
        ASSERT_EQ(result, expect);
        ASSERT_EQ(break_keyring_count(ring), 1u);
        ASSERT_TRUE(resolves_to(ring, &orig));
        ASSERT_EQ(log.count, 0u);
    }
    /* the in-memory entry point also refuses NULL text and an oversized length */
    memset(&log, 0, sizeof(log));
    ASSERT_EQ(break_keyring_load_text(ring, NULL, 0u, record_revoked, &log),
              BREAK_KEYRING_LOAD_UNREADABLE);
    ASSERT_EQ(break_keyring_load_text(NULL, la, 81u, record_revoked, &log),
              BREAK_KEYRING_LOAD_UNREADABLE);
    ASSERT_EQ(break_keyring_load_file(ring, NULL, record_revoked, &log),
              BREAK_KEYRING_LOAD_UNREADABLE);
    ASSERT_EQ(break_keyring_count(ring), 1u);
    ASSERT_EQ(log.count, 0u);
    break_keyring_destroy(ring);
}

/* size bytes: '#' comment lines of 64 bytes, optionally ending in one key
 * line; the caller frees. */
static char *padded_text(size_t size, const TestKey *key)
{
    char *text = (char *)malloc(size);
    size_t body = size;
    size_t i;
    if (text == NULL) return NULL;
    if (key != NULL) {
        char line[82];
        test_key_line(key, line);
        body = size - 81u;
        memcpy(text + body, line, 81u);
    }
    for (i = 0u; i < body; i++) text[i] = (i % 64u == 63u) ? '\n' : '#';
    if (body > 0u) text[body - 1u] = '\n';
    return text;
}

TEST(keyring_load_rejects_an_oversized_file)
{
    TestKey a = test_key(1u);
    TestKey orig = test_key(9u);
    BreakKeyringLoadResult over;
    BreakKeyringLoadResult over_text;
    BreakKeyringLoadResult exact;
    bool written_over;
    bool written_exact;
    char *big = padded_text(BREAK_KEYRING_MAX_FILE_BYTES + 1u, NULL);
    char *fits = padded_text(BREAK_KEYRING_MAX_FILE_BYTES, &a);
    BreakKeyring *ring = break_keyring_create(4u);
    if (ring != NULL) (void)break_keyring_add(ring, orig.id, orig.psk);
    over = BREAK_KEYRING_LOAD_OK;
    over_text = BREAK_KEYRING_LOAD_OK;
    exact = BREAK_KEYRING_LOAD_UNREADABLE;
    written_over = false;
    written_exact = false;
    if (ring != NULL && big != NULL && fits != NULL) {
        over = load_via_file(ring, "oversize", big, BREAK_KEYRING_MAX_FILE_BYTES + 1u,
                             NULL, NULL, &written_over);
        over_text = break_keyring_load_text(ring, big, BREAK_KEYRING_MAX_FILE_BYTES + 1u,
                                            NULL, NULL);
    }
    free(big);
    ASSERT_NOT_NULL(ring);
    ASSERT_NOT_NULL(fits);
    ASSERT_TRUE(written_over);
    ASSERT_EQ(over, BREAK_KEYRING_LOAD_TOO_LARGE);
    ASSERT_EQ(over_text, BREAK_KEYRING_LOAD_TOO_LARGE);
    ASSERT_EQ(break_keyring_count(ring), 1u);
    ASSERT_TRUE(resolves_to(ring, &orig));
    /* exactly BREAK_KEYRING_MAX_FILE_BYTES is accepted */
    exact = load_via_file(ring, "maxsize", fits, BREAK_KEYRING_MAX_FILE_BYTES, NULL, NULL,
                          &written_exact);
    free(fits);
    ASSERT_TRUE(written_exact);
    ASSERT_EQ(exact, BREAK_KEYRING_LOAD_OK);
    ASSERT_EQ(break_keyring_count(ring), 1u);
    ASSERT_TRUE(resolves_to(ring, &a));
    ASSERT_FALSE(resolves_to(ring, &orig));
    break_keyring_destroy(ring);
}

TEST(keyring_reload_applies_the_difference)
{
    TestKey a = test_key(1u);
    TestKey b = test_key(2u);
    TestKey c = test_key(3u);
    TestKey d = test_key(4u);
    TestKey b2 = b;
    char la[82];
    char lb2[82];
    char ld[82];
    char text[512];
    RevokedLog log;
    bool written;
    int len;
    BreakKeyringLoadResult result;
    BreakKeyring *ring = break_keyring_create(4u);
    ASSERT_NOT_NULL(ring);
    b2.psk[31] ^= 0x80u;
    ASSERT_TRUE(break_keyring_add(ring, a.id, a.psk));
    ASSERT_TRUE(break_keyring_add(ring, b.id, b.psk));
    ASSERT_TRUE(break_keyring_add(ring, c.id, c.psk));
    test_key_line(&a, la);
    test_key_line(&b2, lb2);
    test_key_line(&d, ld);
    len = snprintf(text, sizeof(text), "%.81s\n%.81s\n%.81s\n", la, lb2, ld);
    ASSERT_TRUE(len > 0 && (size_t)len < sizeof(text));
    memset(&log, 0, sizeof(log));
    result = load_via_file(ring, "reload", text, (size_t)len, record_revoked, &log,
                           &written);
    ASSERT_TRUE(written);
    ASSERT_EQ(result, BREAK_KEYRING_LOAD_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_TRUE(memcmp(log.ids[0], b.id, 8u) == 0);
    ASSERT_TRUE(memcmp(log.ids[1], c.id, 8u) == 0);
    ASSERT_TRUE(resolves_to(ring, &a));
    ASSERT_TRUE(resolves_to(ring, &b2));
    ASSERT_TRUE(resolves_to(ring, &d));
    ASSERT_FALSE(resolves_to(ring, &c));
    ASSERT_EQ(break_keyring_count(ring), 3u);
    /* reloading the same content changes nothing and revokes nothing */
    memset(&log, 0, sizeof(log));
    ASSERT_EQ(break_keyring_load_text(ring, text, (usize)len, record_revoked, &log),
              BREAK_KEYRING_LOAD_OK);
    ASSERT_EQ(log.count, 0u);
    ASSERT_EQ(break_keyring_count(ring), 3u);
    /* a NULL callback is allowed */
    len = snprintf(text, sizeof(text), "%.81s\n", la);
    ASSERT_EQ(break_keyring_load_text(ring, text, (usize)len, NULL, NULL),
              BREAK_KEYRING_LOAD_OK);
    ASSERT_EQ(break_keyring_count(ring), 1u);
    ASSERT_TRUE(resolves_to(ring, &a));
    break_keyring_destroy(ring);
}

TEST(keyring_revoked_sees_the_id_before_the_wipe)
{
    TestKey a = test_key(1u);
    TestKey b = test_key(2u);
    char la[82];
    RevokedLog log;
    BreakKeyring *ring = break_keyring_create(2u);
    ASSERT_NOT_NULL(ring);
    ASSERT_TRUE(break_keyring_add(ring, a.id, a.psk));
    ASSERT_TRUE(break_keyring_add(ring, b.id, b.psk));
    test_key_line(&a, la);
    memset(&log, 0, sizeof(log));
    log.ring = ring;
    ASSERT_EQ(break_keyring_load_text(ring, la, 81u, record_revoked, &log),
              BREAK_KEYRING_LOAD_OK);
    ASSERT_EQ(log.count, 1u);
    /* the removed key no longer resolves inside the callback ... */
    ASSERT_FALSE(log.resolved_inside[0]);
    /* ... but the id it was given is still the removed id */
    ASSERT_TRUE(memcmp(log.ids[0], b.id, 8u) == 0);
    break_keyring_destroy(ring);
}

TEST(keyring_load_text_matches_load_file)
{
    TestKey a = test_key(1u);
    TestKey b = test_key(2u);
    TestKey c = test_key(3u);
    char la[82];
    char lb[82];
    char text[512];
    bool written;
    int len;
    BreakKeyringLoadResult from_file;
    BreakKeyringLoadResult from_text;
    BreakKeyring *ring_file = break_keyring_create(4u);
    BreakKeyring *ring_text = break_keyring_create(4u);
    ASSERT_NOT_NULL(ring_file);
    ASSERT_NOT_NULL(ring_text);
    test_key_line(&a, la);
    test_key_line(&b, lb);
    len = snprintf(text, sizeof(text), "# k\n%.81s\r\n%.81s", la, lb);
    ASSERT_TRUE(len > 0 && (size_t)len < sizeof(text));
    from_file = load_via_file(ring_file, "same", text, (size_t)len, NULL, NULL, &written);
    /* a trailing byte past len must be ignored */
    text[len] = 'x';
    from_text = break_keyring_load_text(ring_text, text, (usize)len, NULL, NULL);
    ASSERT_TRUE(written);
    ASSERT_EQ(from_file, BREAK_KEYRING_LOAD_OK);
    ASSERT_EQ(from_text, from_file);
    ASSERT_EQ(break_keyring_count(ring_text), break_keyring_count(ring_file));
    ASSERT_EQ(break_keyring_count(ring_text), 2u);
    ASSERT_TRUE(resolves_to(ring_file, &a) && resolves_to(ring_text, &a));
    ASSERT_TRUE(resolves_to(ring_file, &b) && resolves_to(ring_text, &b));
    ASSERT_FALSE(resolves_to(ring_file, &c) || resolves_to(ring_text, &c));
    break_keyring_destroy(ring_file);
    break_keyring_destroy(ring_text);
}

TEST(keyring_key_at_walks_insertion_order)
{
    TestKey a = test_key(1u);
    TestKey b = test_key(2u);
    TestKey c = test_key(3u);
    u8 id[8];
    u8 psk[32];
    BreakKeyring *ring = break_keyring_create(4u);
    ASSERT_NOT_NULL(ring);
    ASSERT_TRUE(break_keyring_add(ring, a.id, a.psk));
    ASSERT_TRUE(break_keyring_add(ring, b.id, b.psk));
    ASSERT_TRUE(break_keyring_add(ring, c.id, c.psk));
    ASSERT_TRUE(break_keyring_remove(ring, b.id));
    ASSERT_TRUE(break_keyring_key_at(ring, 0u, id, psk));
    ASSERT_TRUE(memcmp(id, a.id, 8u) == 0 && memcmp(psk, a.psk, 32u) == 0);
    ASSERT_TRUE(break_keyring_key_at(ring, 1u, id, psk));
    ASSERT_TRUE(memcmp(id, c.id, 8u) == 0 && memcmp(psk, c.psk, 32u) == 0);
    ASSERT_FALSE(break_keyring_key_at(ring, 2u, id, psk));
    ASSERT_FALSE(break_keyring_key_at(NULL, 0u, id, psk));
    ASSERT_FALSE(break_keyring_key_at(ring, 0u, NULL, psk));
    ASSERT_FALSE(break_keyring_key_at(ring, 0u, id, NULL));
    /* a key added after the removal goes last */
    ASSERT_TRUE(break_keyring_add(ring, b.id, b.psk));
    ASSERT_TRUE(break_keyring_key_at(ring, 2u, id, psk));
    ASSERT_TRUE(memcmp(id, b.id, 8u) == 0);
    break_keyring_destroy(ring);
}

TEST_MAIN_BEGIN()
    RUN_TEST(keyring_add_remove_and_capacity);
    RUN_TEST(keyring_resolve_returns_the_psk_and_leaves_misses_alone);
    RUN_TEST(keyring_load_accepts_comments_blank_lines_and_crlf);
    RUN_TEST(keyring_load_rejects_each_malformed_shape_and_leaves_the_ring);
    RUN_TEST(keyring_load_rejects_an_oversized_file);
    RUN_TEST(keyring_reload_applies_the_difference);
    RUN_TEST(keyring_revoked_sees_the_id_before_the_wipe);
    RUN_TEST(keyring_load_text_matches_load_file);
    RUN_TEST(keyring_key_at_walks_insertion_order);
TEST_MAIN_END()
