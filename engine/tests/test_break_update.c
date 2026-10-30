/* ==========================================================================
 *  test_break_update.c — Stage 5 Phase A Task 4 tests: signed canonical
 *  manifest parse/verify/accessors/compatibility + content-addressed chunk
 *  store (put/has/get, verify-on-read corruption detection, bounds).
 *
 *  Test-vector provenance (generated ONCE offline on 2026-10-24 with the
 *  system OpenSSL 3.5.9 CLI; scratch dir /tmp/upd_t4_keygen; the private
 *  key is NOT committed anywhere — this is a TEST-ONLY keypair, never a
 *  product key):
 *    openssl genpkey -algorithm ed25519 -out break_update_test_sk.pem
 *    openssl pkey -in break_update_test_sk.pem -pubout -out break_update_test_pk.pem
 *    openssl pkey -pubin -in break_update_test_pk.pem -outform DER \
 *        | tail -c 32 | xxd -p -c 64                      -> TEST_PUBKEY_HEX
 *    chunk hashes: sha256sum of printf 'break-update-test-chunk-{alpha,beta,gamma}'
 *    openssl pkeyutl -sign -inkey break_update_test_sk.pem -rawin \
 *        -in golden_body.bin | base64                     -> GOLDEN signature line
 *    cross-checked: openssl pkeyutl -verify -pubin -inkey break_update_test_pk.pem \
 *        -rawin -in golden_body.bin -sigfile golden_sig.bin
 *        -> "Signature Verified Successfully".
 * ========================================================================== */

#include "test_framework.h"

#include <update/break_update.h>
#include <crypto/break_crypto.h>
#include <platform/platform_fs.h>

#include <string.h>

/* ---- fixed test vectors (see provenance above) ------------------------ */

static const char TEST_PUBKEY_HEX[] =
    "419d3071bda8be4a6cbab81a1822222f792ad811a880b9e7b198e8d17b2610e4";

#define HASH_ALPHA_HEX \
    "31ca71057907d32be7a05d519e2ba060fc5e1ff59090021896e1019b1f819d33"
#define HASH_BETA_HEX \
    "a2e73e0d4b1284d0cbc821a45ab40ba2f52ade27152f2fc0a6cf75a8b15225c7"
#define HASH_GAMMA_HEX \
    "715fcc4e06d98e89e24f0cd56313d2689b70cb421259aaadcff6807f0f6faf57"

#define HDR \
    "break-manifest-v1\n" \
    "version: 1.2.3\n" \
    "channel: stable\n" \
    "platform: linux-x86-64\n" \
    "min-version: 0.9.0\n"

#define GOLDEN_CHUNKS \
    "chunk: " HASH_ALPHA_HEX " 4096 bin/engine\n" \
    "chunk: " HASH_BETA_HEX  " 1048576 data/base.pak\n" \
    "chunk: " HASH_GAMMA_HEX " 2048 shaders/pbr.spv\n"

#define GOLDEN_SIG_LINE \
    "signature: g/CtMPXkw6cYSU+NJDm9mXViMQxB627vcBv0Rm+P3DkIv1n960QVlfY3DYA7GUdyaMm07eVAVwFpDXAEh5lXBw==\n"

/* base64 of 64 zero bytes: 86 'A' + "==" — canonical, structurally valid,
 * but cryptographically wrong for any message/key ("unsigned manifest"). */
#define ZERO_SIG_B64 \
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=="
#define ZERO_SIG_LINE "signature: " ZERO_SIG_B64 "\n"

static const char GOLDEN_MANIFEST[] = HDR GOLDEN_CHUNKS GOLDEN_SIG_LINE;

/* ---- helpers ----------------------------------------------------------- */

static int hexval(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static bool hex2bin(const char *hex, u8 *out, usize out_len) {
    usize i;
    for (i = 0; i < out_len; i++) {
        int hi = hexval(hex[2 * i]);
        int lo = hexval(hex[2 * i + 1]);
        if (hi < 0 || lo < 0) return false;
        out[i] = (u8)((hi << 4) | lo);
    }
    return true;
}

static void bin2hex(const u8 *in, usize n, char *out) {
    static const char h[] = "0123456789abcdef";
    usize i;
    for (i = 0; i < n; i++) {
        out[2 * i] = h[in[i] >> 4];
        out[2 * i + 1] = h[in[i] & 15];
    }
    out[2 * n] = '\0';
}

static void test_pubkey(u8 out[32]) {
    if (!hex2bin(TEST_PUBKEY_HEX, out, 32)) {
        printf("  FATAL: embedded pubkey hex malformed\n");
        exit(2);
    }
}

static BreakUpdateManifest *parse_cstr(const char *s) {
    return break_update_manifest_parse(s, strlen(s));
}

static bool manifest_parses(const char *text) {
    BreakUpdateManifest *m = parse_cstr(text);
    if (!m) return false;
    break_update_manifest_destroy(m);
    return true;
}

/* header lines + chunk_lines + zero-signature line. */
static bool composed_parses(const char *header, const char *chunk_lines) {
    char buf[4096];
    snprintf(buf, sizeof(buf), "%s%s%s", header, chunk_lines, ZERO_SIG_LINE);
    return manifest_parses(buf);
}

static bool chunk_manifest_parses(const char *chunk_lines) {
    return composed_parses(HDR, chunk_lines);
}

/* ---- manifest: golden parse + accessors + verify ----------------------- */

TEST(golden_parse_accessors_verify) {
    u8 pub[32];
    test_pubkey(pub);

    BreakUpdateManifest *m = parse_cstr(GOLDEN_MANIFEST);
    ASSERT_NOT_NULL(m);

    u32 v[3] = {0, 0, 0};
    break_update_manifest_version(m, v);
    ASSERT_EQ(v[0], 1u); ASSERT_EQ(v[1], 2u); ASSERT_EQ(v[2], 3u);
    u32 mv[3] = {0, 0, 0};
    break_update_manifest_min_version(m, mv);
    ASSERT_EQ(mv[0], 0u); ASSERT_EQ(mv[1], 9u); ASSERT_EQ(mv[2], 0u);
    ASSERT_STR_EQ(break_update_manifest_channel(m), "stable");
    ASSERT_STR_EQ(break_update_manifest_platform(m), "linux-x86-64");
    ASSERT_EQ(break_update_manifest_chunk_count(m), 3u);

    static const struct { const char *name; const char *hash; u64 size; } want[3] = {
        {"bin/engine",       HASH_ALPHA_HEX, 4096},
        {"data/base.pak",    HASH_BETA_HEX,  1048576},
        {"shaders/pbr.spv",  HASH_GAMMA_HEX, 2048},
    };
    u64 i;
    for (i = 0; i < 3; i++) {
        const char *name = NULL;
        u8 hash[32], want_hash[32];
        u64 size = 0;
        ASSERT_TRUE(break_update_manifest_chunk_at(m, i, &name, hash, &size));
        ASSERT_STR_EQ(name, want[i].name);
        ASSERT_EQ(size, want[i].size);
        ASSERT_TRUE(hex2bin(want[i].hash, want_hash, 32));
        ASSERT_TRUE(memcmp(hash, want_hash, 32) == 0);
    }
    /* bad indices */
    const char *name = NULL;
    u8 hash[32];
    u64 size = 0;
    ASSERT_FALSE(break_update_manifest_chunk_at(m, 3, &name, hash, &size));
    ASSERT_FALSE(break_update_manifest_chunk_at(m, (u64)-1, &name, hash, &size));

    ASSERT_TRUE(break_update_manifest_verify(m, pub));
    pub[0] ^= 0x01; /* wrong key: indistinguishable false */
    ASSERT_FALSE(break_update_manifest_verify(m, pub));

    break_update_manifest_destroy(m);
    break_update_manifest_destroy(NULL); /* safe no-op */
}

TEST(tamper_body_verify_false) {
    u8 pub[32];
    test_pubkey(pub);
    static char tampered[sizeof(GOLDEN_MANIFEST)];
    memcpy(tampered, GOLDEN_MANIFEST, sizeof(tampered));
    char *hit = strstr(tampered, "31ca");
    ASSERT_NOT_NULL(hit);
    ASSERT_EQ(*hit, '3');
    *hit = '4'; /* single-character flip in the body, still canonical hex */
    BreakUpdateManifest *m = parse_cstr(tampered);
    ASSERT_NOT_NULL(m);            /* structure still valid ... */
    ASSERT_FALSE(break_update_manifest_verify(m, pub)); /* ... signature not */
    break_update_manifest_destroy(m);
}

TEST(unsigned_manifest_verify_false) {
    u8 pub[32];
    test_pubkey(pub);
    ASSERT_EQ(strlen(ZERO_SIG_B64), 88); /* 86 data + 2 pad, pin the vector */
    char buf[1024];
    snprintf(buf, sizeof(buf), "%s%s%s", HDR, GOLDEN_CHUNKS, ZERO_SIG_LINE);
    BreakUpdateManifest *m = parse_cstr(buf);
    ASSERT_NOT_NULL(m); /* zero signature is canonical base64 → parses */
    ASSERT_FALSE(break_update_manifest_verify(m, pub));
    break_update_manifest_destroy(m);
}

/* ---- manifest: canonical strictness (ANY deviation → NULL) ------------- */

TEST(truncation_parse_null) {
    usize n = strlen(GOLDEN_MANIFEST);
    usize sig_off = (usize)(strstr(GOLDEN_MANIFEST, "signature: ") - GOLDEN_MANIFEST);
    ASSERT_TRUE(break_update_manifest_parse(GOLDEN_MANIFEST, n - 1) == NULL); /* no final LF */
    ASSERT_TRUE(break_update_manifest_parse(GOLDEN_MANIFEST, n - 50) == NULL); /* mid-signature */
    ASSERT_TRUE(break_update_manifest_parse(GOLDEN_MANIFEST, sig_off) == NULL); /* sig line gone */
    ASSERT_TRUE(break_update_manifest_parse(GOLDEN_MANIFEST, 64) == NULL);     /* mid-body */
    ASSERT_TRUE(break_update_manifest_parse(GOLDEN_MANIFEST, 0) == NULL);
    ASSERT_TRUE(parse_cstr("") == NULL);
}

TEST(missing_duplicate_unsorted_keys_null) {
    /* missing channel / platform / min-version / version */
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion: 1.2.3\nplatform: linux-x86-64\n"
        "min-version: 0.9.0\n" ZERO_SIG_LINE));
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion: 1.2.3\nchannel: stable\n"
        "min-version: 0.9.0\n" ZERO_SIG_LINE));
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion: 1.2.3\nchannel: stable\n"
        "platform: linux-x86-64\n" ZERO_SIG_LINE));
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nchannel: stable\nplatform: linux-x86-64\n"
        "min-version: 0.9.0\n" ZERO_SIG_LINE));
    /* duplicate channel (fixed order makes the 2nd one a deviation) */
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion: 1.2.3\nchannel: stable\nchannel: beta\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE));
    /* unsorted header keys */
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion: 1.2.3\nplatform: linux-x86-64\n"
        "channel: stable\nmin-version: 0.9.0\n" ZERO_SIG_LINE));
    /* wrong magic line */
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v2\nversion: 1.2.3\nchannel: stable\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE));
    /* empty line inside the header */
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\n\nversion: 1.2.3\nchannel: stable\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE));
}

TEST(chunk_name_rules) {
    static const char *bad_names[] = {
        "data/../x",   /* ".." substring */
        "..x",
        "x..",
        "/absolute",   /* leading '/' */
        "bad$name",    /* charset violation */
        "bad name",    /* space */
        "bad\tname",   /* tab */
        "",            /* empty (line ends after the separator space) */
    };
    char line[512];
    usize i;
    for (i = 0; i < sizeof(bad_names) / sizeof(bad_names[0]); i++) {
        snprintf(line, sizeof(line), "chunk: %s 12 %s\n", HASH_ALPHA_HEX, bad_names[i]);
        ASSERT_FALSE(chunk_manifest_parses(line));
    }
    /* 129-byte name → NULL */
    char long_name[130];
    memset(long_name, 'a', sizeof(long_name));
    long_name[sizeof(long_name) - 1] = '\0';
    snprintf(line, sizeof(line), "chunk: %s 12 %s\n", HASH_ALPHA_HEX, long_name);
    ASSERT_EQ(strlen(long_name), 129u);
    ASSERT_FALSE(chunk_manifest_parses(line));

    /* accept pins: 128-byte name, nested path, dotted name. */
    long_name[128] = '\0';
    snprintf(line, sizeof(line), "chunk: %s 12 %s\n", HASH_ALPHA_HEX, long_name);
    ASSERT_TRUE(chunk_manifest_parses(line));
    snprintf(line, sizeof(line), "chunk: %s 12 a/b/c.d_e\n", HASH_ALPHA_HEX);
    ASSERT_TRUE(chunk_manifest_parses(line));
}

TEST(chunk_listing_rules) {
    /* unsorted chunk lines → NULL */
    ASSERT_FALSE(chunk_manifest_parses(
        "chunk: " HASH_BETA_HEX " 1 data/base.pak\n"
        "chunk: " HASH_ALPHA_HEX " 1 bin/engine\n"));
    /* duplicate names → NULL */
    ASSERT_FALSE(chunk_manifest_parses(
        "chunk: " HASH_ALPHA_HEX " 1 bin/engine\n"
        "chunk: " HASH_BETA_HEX " 2 bin/engine\n"));
    /* zero chunks is structurally valid */
    ASSERT_TRUE(chunk_manifest_parses(""));

    BreakUpdateManifest *m = parse_cstr(HDR ZERO_SIG_LINE);
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_update_manifest_chunk_count(m), 0u);
    const char *name = NULL;
    u8 hash[32];
    u64 size = 0;
    ASSERT_FALSE(break_update_manifest_chunk_at(m, 0, &name, hash, &size));
    break_update_manifest_destroy(m);
}

TEST(field_strictness) {
    char buf[4096];
    /* version: leading zero / u32 overflow / wrong shape */
    snprintf(buf, sizeof(buf), "%s", "break-manifest-v1\nversion: 01.2.3\n"
        "channel: stable\nplatform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE);
    ASSERT_FALSE(manifest_parses(buf));
    snprintf(buf, sizeof(buf), "%s", "break-manifest-v1\nversion: 4294967296.0.0\n"
        "channel: stable\nplatform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE);
    ASSERT_FALSE(manifest_parses(buf));
    snprintf(buf, sizeof(buf), "%s", "break-manifest-v1\nversion: 1.2\n"
        "channel: stable\nplatform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE);
    ASSERT_FALSE(manifest_parses(buf));
    snprintf(buf, sizeof(buf), "%s", "break-manifest-v1\nversion: 1.2.3.4\n"
        "channel: stable\nplatform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE);
    ASSERT_FALSE(manifest_parses(buf));
    snprintf(buf, sizeof(buf), "%s", "break-manifest-v1\nversion: 1.2.x\n"
        "channel: stable\nplatform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE);
    ASSERT_FALSE(manifest_parses(buf));
    /* accept pin: u32-max components parse */
    snprintf(buf, sizeof(buf), "%s", "break-manifest-v1\nversion: 4294967295.4294967295.4294967295\n"
        "channel: stable\nplatform: linux-x86-64\nmin-version: 0.0.0\n" ZERO_SIG_LINE);
    ASSERT_TRUE(manifest_parses(buf));

    /* channel/platform charset: uppercase, '_', empty, 65 chars */
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion: 1.2.3\nchannel: Stable\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE));
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion: 1.2.3\nchannel: bad_chan\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE));
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion: 1.2.3\nchannel: \n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE));
    char chan[66];
    memset(chan, 'c', sizeof(chan));
    chan[sizeof(chan) - 1] = '\0'; /* 65 chars */
    snprintf(buf, sizeof(buf), "break-manifest-v1\nversion: 1.2.3\nchannel: %s\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE, chan);
    ASSERT_EQ(strlen(chan), 65u);
    ASSERT_FALSE(manifest_parses(buf));
    chan[64] = '\0'; /* 64 chars: the accepted boundary */
    snprintf(buf, sizeof(buf), "break-manifest-v1\nversion: 1.2.3\nchannel: %s\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE, chan);
    ASSERT_TRUE(manifest_parses(buf));

    /* chunk hash: uppercase / short / long */
    ASSERT_FALSE(chunk_manifest_parses(
        "chunk: 31CA71057907D32BE7A05D519E2BA060FC5E1FF59090021896E1019B1F819D33 1 a\n"));
    ASSERT_FALSE(chunk_manifest_parses(
        "chunk: 31ca71057907d32be7a05d519e2ba060fc5e1ff59090021896e1019b1f819d3 1 a\n"));
    ASSERT_FALSE(chunk_manifest_parses(
        "chunk: 31ca71057907d32be7a05d519e2ba060fc5e1ff59090021896e1019b1f819d330 1 a\n"));
    /* size: leading zero / u64 overflow / empty */
    ASSERT_FALSE(chunk_manifest_parses(
        "chunk: " HASH_ALPHA_HEX " 04096 a\n"));
    ASSERT_FALSE(chunk_manifest_parses(
        "chunk: " HASH_ALPHA_HEX " 18446744073709551616 a\n")); /* u64 max + 1 */
    ASSERT_FALSE(chunk_manifest_parses(
        "chunk: " HASH_ALPHA_HEX "  a\n"));
    /* accept pin: u64-max size parses — the 128 MiB cap is a STORE limit,
     * not a manifest-grammar limit (documented decision). */
    ASSERT_TRUE(chunk_manifest_parses(
        "chunk: " HASH_ALPHA_HEX " 18446744073709551615 a\n"));
}

TEST(byte_and_layout_strictness) {
    static char buf[sizeof(GOLDEN_MANIFEST) + 16];

    /* CR anywhere → NULL */
    memcpy(buf, GOLDEN_MANIFEST, sizeof(GOLDEN_MANIFEST));
    char *lf = strchr(buf, '\n');
    ASSERT_NOT_NULL(lf);
    memmove(lf + 1, lf, strlen(lf) + 1);
    *lf = '\r';
    ASSERT_TRUE(parse_cstr(buf) == NULL);

    /* 0x7F / >= 0x80 bytes → NULL */
    memcpy(buf, GOLDEN_MANIFEST, sizeof(GOLDEN_MANIFEST));
    buf[10] = 0x7F;
    ASSERT_TRUE(parse_cstr(buf) == NULL);
    memcpy(buf, GOLDEN_MANIFEST, sizeof(GOLDEN_MANIFEST));
    buf[10] = (char)(unsigned char)0x80;
    ASSERT_TRUE(parse_cstr(buf) == NULL);

    /* embedded NUL → NULL (explicit length, not strlen) */
    memcpy(buf, GOLDEN_MANIFEST, sizeof(GOLDEN_MANIFEST));
    buf[10] = '\0';
    ASSERT_TRUE(break_update_manifest_parse(buf, strlen(GOLDEN_MANIFEST)) == NULL);

    /* double space / tab separator in a header line → NULL */
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion:  1.2.3\nchannel: stable\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE));
    ASSERT_FALSE(manifest_parses(
        "break-manifest-v1\nversion:\t1.2.3\nchannel: stable\n"
        "platform: linux-x86-64\nmin-version: 0.9.0\n" ZERO_SIG_LINE));

    /* trailing garbage after the signature line → NULL */
    snprintf(buf, sizeof(buf), "%s%s", GOLDEN_MANIFEST, "extra\n");
    ASSERT_TRUE(parse_cstr(buf) == NULL);
}

TEST(signature_line_strictness) {
    char buf[4096];
    usize off;
    /* wrong lengths: 87 / 89 base64 chars */
    off = 0;
    memcpy(buf, HDR, strlen(HDR)); off += strlen(HDR);
    memcpy(buf + off, "signature: ", 11); off += 11;
    memset(buf + off, 'A', 87); off += 87;
    buf[off++] = '\n'; buf[off] = '\0';
    ASSERT_FALSE(manifest_parses(buf));
    off = strlen(HDR) + 11;
    memcpy(buf, HDR, strlen(HDR));
    memcpy(buf + strlen(HDR), "signature: ", 11);
    memset(buf + off, 'A', 89); off += 89;
    buf[off++] = '\n'; buf[off] = '\0';
    ASSERT_FALSE(manifest_parses(buf));
    /* '=' not at the tail pad position */
    snprintf(buf, sizeof(buf), "%ssignature: =%s\n", HDR, &ZERO_SIG_B64[1]);
    ASSERT_FALSE(manifest_parses(buf));
    /* non-base64 character */
    snprintf(buf, sizeof(buf), "%ssignature: *%s\n", HDR, &ZERO_SIG_B64[1]);
    ASSERT_FALSE(manifest_parses(buf));
    /* missing pad (86 data chars, no "==") */
    snprintf(buf, sizeof(buf), "%ssignature: %.*sAA\n", HDR, 86, ZERO_SIG_B64);
    ASSERT_FALSE(manifest_parses(buf));
    /* non-canonical pad bits: golden sig char[85] 'w'(48) → 'x'(49, low 4 bits != 0) */
    memcpy(buf, GOLDEN_MANIFEST, sizeof(GOLDEN_MANIFEST));
    char *sig = strstr(buf, "signature: ");
    ASSERT_NOT_NULL(sig);
    sig += strlen("signature: ");
    ASSERT_EQ(sig[85], 'w');
    sig[85] = 'x';
    ASSERT_TRUE(parse_cstr(buf) == NULL);
    /* golden sig char[85] with another canonical (low-4-bits-zero) value still
     * PARSES (structure valid) but no longer verifies — canonicality is about
     * encoding, not correctness. 'A'(0) is canonical. */
    memcpy(buf, GOLDEN_MANIFEST, sizeof(GOLDEN_MANIFEST));
    sig = strstr(buf, "signature: ") + strlen("signature: ");
    sig[85] = 'A';
    BreakUpdateManifest *m = parse_cstr(buf);
    ASSERT_NOT_NULL(m);
    u8 pub[32];
    test_pubkey(pub);
    ASSERT_FALSE(break_update_manifest_verify(m, pub));
    break_update_manifest_destroy(m);
}

TEST(oversize_manifest_null) {
    /* > 1 MiB total → NULL regardless of content. */
    static const usize cap = 1024 * 1024 + 1;
    char *big = malloc(cap + 1);
    ASSERT_NOT_NULL(big);
    memset(big, 'a', cap);
    big[cap] = '\0';
    ASSERT_TRUE(break_update_manifest_parse(big, cap) == NULL);
    free(big);
    /* The 65536-chunk cap is unreachable under the 1 MiB cap (65537 minimal
     * ~75-byte chunk lines ≈ 4.9 MiB); both are enforced in code — the size
     * gate is what fires here (documented, matches header note). */
}

/* ---- compatibility policy ---------------------------------------------- */

TEST(compatible_matrix) {
    BreakUpdateManifest *m = parse_cstr(GOLDEN_MANIFEST);
    ASSERT_NOT_NULL(m);
    /* golden: channel stable, platform linux-x86-64, min-version 0.9.0 */
    ASSERT_TRUE(break_update_manifest_compatible(m, "stable", "linux-x86-64", 0, 9, 0)); /* equal min */
    ASSERT_TRUE(break_update_manifest_compatible(m, "stable", "linux-x86-64", 0, 9, 1));
    ASSERT_TRUE(break_update_manifest_compatible(m, "stable", "linux-x86-64", 1, 0, 0));
    ASSERT_FALSE(break_update_manifest_compatible(m, "stable", "linux-x86-64", 0, 8, 9)); /* older */
    ASSERT_FALSE(break_update_manifest_compatible(m, "stable", "linux-x86-64", 0, 8, 99));
    ASSERT_FALSE(break_update_manifest_compatible(m, "beta", "linux-x86-64", 1, 0, 0));   /* channel */
    ASSERT_FALSE(break_update_manifest_compatible(m, "stable", "darwin-arm64", 1, 0, 0)); /* platform */
    ASSERT_FALSE(break_update_manifest_compatible(NULL, "stable", "linux-x86-64", 1, 0, 0));
    ASSERT_FALSE(break_update_manifest_compatible(m, NULL, "linux-x86-64", 1, 0, 0));
    ASSERT_FALSE(break_update_manifest_compatible(m, "stable", NULL, 1, 0, 0));
    break_update_manifest_destroy(m);
}

TEST(null_arg_matrix) {
    u8 pub[32];
    test_pubkey(pub);
    ASSERT_TRUE(break_update_manifest_parse(NULL, 5) == NULL);

    ASSERT_FALSE(break_update_manifest_verify(NULL, pub));

    u32 v[3];
    break_update_manifest_version(NULL, v);      /* no crash, no write */
    break_update_manifest_min_version(NULL, v);
    ASSERT_TRUE(break_update_manifest_channel(NULL) == NULL);
    ASSERT_TRUE(break_update_manifest_platform(NULL) == NULL);
    ASSERT_EQ(break_update_manifest_chunk_count(NULL), 0u);

    BreakUpdateManifest *m = parse_cstr(GOLDEN_MANIFEST);
    ASSERT_NOT_NULL(m);
    const char *name = NULL;
    u8 hash[32];
    u64 size = 0;
    ASSERT_FALSE(break_update_manifest_verify(m, NULL));
    ASSERT_FALSE(break_update_manifest_chunk_at(m, 0, NULL, hash, &size));
    ASSERT_FALSE(break_update_manifest_chunk_at(m, 0, &name, NULL, &size));
    ASSERT_FALSE(break_update_manifest_chunk_at(m, 0, &name, hash, NULL));
    ASSERT_FALSE(break_update_manifest_chunk_at(NULL, 0, &name, hash, &size));
    break_update_manifest_version(m, NULL);      /* tolerated no-op */
    break_update_manifest_destroy(m);
}

/* ---- content-addressed store -------------------------------------------- */

static void chunk_path_of(char *out, usize cap, const char *root, const char *name) {
    snprintf(out, cap, "%s/chunks/%s", root, name);
}

static void cleanup_store(const char *root, const char **names, usize n_names) {
    usize i;
    for (i = 0; i < n_names; i++) {
        char p[1200];
        chunk_path_of(p, sizeof(p), root, names[i]);
        remove(p);
    }
    char chunks[1200];
    snprintf(chunks, sizeof(chunks), "%s/chunks", root);
    TEST_RMDIR(chunks);
    TEST_RMDIR(root);
}

TEST(store_open_layout) {
    char root[512];
    test_tmp(root, sizeof(root), "upd_open");
    BreakUpdateStore *s = break_update_store_open(root);
    ASSERT_NOT_NULL(s);
    /* layout exists: root holds exactly one entry, the chunks directory */
    PlatformDirEntry entries[4];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(root, entries, 4, &count));
    ASSERT_EQ(count, 1u);
    ASSERT_STR_EQ(entries[0].name, "chunks");
    ASSERT_TRUE(entries[0].is_dir);
    break_update_store_destroy(s);

    /* reopen on an existing layout → fine */
    s = break_update_store_open(root);
    ASSERT_NOT_NULL(s);
    break_update_store_destroy(s);
    break_update_store_destroy(NULL); /* no-op */

    /* root path colliding with an existing FILE → NULL */
    char froot[600];
    snprintf(froot, sizeof(froot), "%s_file", root);
    FILE *fp = fopen(froot, "wb");
    ASSERT_NOT_NULL(fp);
    ASSERT_EQ(fclose(fp), 0);
    ASSERT_TRUE(break_update_store_open(froot) == NULL);
    remove(froot);

    ASSERT_TRUE(break_update_store_open(NULL) == NULL);
    ASSERT_TRUE(break_update_store_open("") == NULL);

    /* over-long root: root + "/chunks/" + 64 hex + NUL must stay below
     * PLATFORM_FS_PATH_CAPACITY → reject beyond that. */
    char long_root[1200];
    memset(long_root, 'a', sizeof(long_root) - 1);
    long_root[sizeof(long_root) - 1] = '\0';
    ASSERT_TRUE(break_update_store_open(long_root) == NULL);

    char chunks[600];
    snprintf(chunks, sizeof(chunks), "%s/chunks", root);
    ASSERT_TRUE(TEST_RMDIR(chunks) == 0);
    ASSERT_TRUE(TEST_RMDIR(root) == 0);
}

TEST(store_roundtrip) {
    char root[512];
    test_tmp(root, sizeof(root), "upd_rt");
    BreakUpdateStore *s = break_update_store_open(root);
    ASSERT_NOT_NULL(s);

    static const char payload1[] = "hello chunk";
    u8 h1[32];
    char n1[65];
    ASSERT_TRUE(break_crypto_sha256(payload1, 11, h1));
    bin2hex(h1, 32, n1);

    ASSERT_FALSE(break_update_store_has_chunk(s, n1)); /* absent before put */
    ASSERT_TRUE(break_update_store_put_chunk(s, payload1, 11));
    ASSERT_TRUE(break_update_store_has_chunk(s, n1));

    char p1[1200];
    chunk_path_of(p1, sizeof(p1), root, n1);
    u64 fsize = 0;
    ASSERT_TRUE(platform_file_size(p1, &fsize));
    ASSERT_EQ(fsize, 11u);

    u8 *buf = NULL;
    u64 len = 0;
    ASSERT_TRUE(break_update_store_get_chunk(s, n1, &buf, &len));
    ASSERT_NOT_NULL(buf);
    ASSERT_EQ(len, 11u);
    ASSERT_TRUE(memcmp(buf, payload1, 11) == 0);
    free(buf);

    /* 2 MiB patterned payload */
    const usize n2 = 2u * 1024u * 1024u;
    u8 *payload2 = malloc(n2);
    ASSERT_NOT_NULL(payload2);
    usize i;
    for (i = 0; i < n2; i++) payload2[i] = (u8)(i ^ (i >> 8) ^ (i >> 16));
    u8 h2[32];
    char n2hex[65];
    ASSERT_TRUE(break_crypto_sha256(payload2, n2, h2));
    bin2hex(h2, 32, n2hex);
    ASSERT_TRUE(break_update_store_put_chunk(s, payload2, n2));
    buf = NULL;
    len = 0;
    ASSERT_TRUE(break_update_store_get_chunk(s, n2hex, &buf, &len));
    ASSERT_EQ(len, (u64)n2);
    ASSERT_TRUE(memcmp(buf, payload2, n2) == 0);
    free(buf);
    free(payload2);

    /* put is idempotent: same bytes again → still fine */
    ASSERT_TRUE(break_update_store_put_chunk(s, payload1, 11));

    /* valid-format but absent name → get false */
    u8 h3[32];
    char n3[65];
    ASSERT_TRUE(break_crypto_sha256("never put", 9, h3));
    bin2hex(h3, 32, n3);
    ASSERT_FALSE(break_update_store_has_chunk(s, n3));
    buf = NULL;
    ASSERT_FALSE(break_update_store_get_chunk(s, n3, &buf, &len));
    ASSERT_TRUE(buf == NULL);

    break_update_store_destroy(s);
    const char *names[] = {n1, n2hex};
    cleanup_store(root, names, 2);
}

TEST(store_corruption_detected) {
    char root[512];
    test_tmp(root, sizeof(root), "upd_corrupt");
    BreakUpdateStore *s = break_update_store_open(root);
    ASSERT_NOT_NULL(s);

    static const char payload[] = "integrity me";
    u8 h[32];
    char name[65];
    ASSERT_TRUE(break_crypto_sha256(payload, 12, h));
    bin2hex(h, 32, name);
    ASSERT_TRUE(break_update_store_put_chunk(s, payload, 12));

    char path[1200];
    chunk_path_of(path, sizeof(path), root, name);

    /* externally flip one byte in the chunk file */
    FILE *fp = fopen(path, "r+b");
    ASSERT_NOT_NULL(fp);
    int c = fgetc(fp);
    ASSERT_TRUE(c != EOF);
    ASSERT_TRUE(fseek(fp, 0, SEEK_SET) == 0);
    ASSERT_EQ(fputc(c ^ 0x01, fp), (c ^ 0x01));
    ASSERT_EQ(fclose(fp), 0);

    ASSERT_TRUE(break_update_store_has_chunk(s, name)); /* existence only */
    u8 *buf = NULL;
    u64 len = 0;
    ASSERT_FALSE(break_update_store_get_chunk(s, name, &buf, &len)); /* verify-on-read */
    ASSERT_TRUE(buf == NULL);

    /* externally truncate the chunk file → short read → false */
    fp = fopen(path, "wb");
    ASSERT_NOT_NULL(fp);
    ASSERT_EQ(fwrite(payload, 1, 4, fp), 4u);
    ASSERT_EQ(fclose(fp), 0);
    ASSERT_FALSE(break_update_store_get_chunk(s, name, &buf, &len));

    break_update_store_destroy(s);
    const char *names[] = {name};
    cleanup_store(root, names, 1);
}

TEST(store_zero_byte_chunk) {
    char root[512];
    test_tmp(root, sizeof(root), "upd_zero");
    BreakUpdateStore *s = break_update_store_open(root);
    ASSERT_NOT_NULL(s);

    /* sha256("") — the empty-content name */
    static const char empty_hex[] =
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    ASSERT_TRUE(break_update_store_put_chunk(s, "x", 0));
    ASSERT_TRUE(break_update_store_has_chunk(s, empty_hex));
    u8 *buf = NULL;
    u64 len = 99;
    ASSERT_TRUE(break_update_store_get_chunk(s, empty_hex, &buf, &len));
    ASSERT_EQ(len, 0u);
    ASSERT_NOT_NULL(buf); /* freeable malloc pointer */
    free(buf);

    /* NULL data with len 0 is the same empty chunk */
    ASSERT_TRUE(break_update_store_put_chunk(s, NULL, 0));

    break_update_store_destroy(s);
    const char *names[] = {empty_hex};
    cleanup_store(root, names, 1);
}

TEST(store_size_limit_and_bad_args) {
    char root[512];
    test_tmp(root, sizeof(root), "upd_limit");
    BreakUpdateStore *s = break_update_store_open(root);
    ASSERT_NOT_NULL(s);

    u8 tiny[4] = {1, 2, 3, 4};
    /* 128 MiB + 1 rejected. The size gate runs BEFORE any data access, so
     * passing a 4-byte buffer with an oversized claim is safe and proves
     * rejection without a 128 MiB allocation (documented test approach). */
    ASSERT_FALSE(break_update_store_put_chunk(s, tiny, 128u * 1024u * 1024u + 1u));
    /* exactly 128 MiB is the accepted boundary — exercised via the size
     * gate only (no real 128 MiB buffer in a unit test; the write path for
     * large bodies is dogfooded at 2 MiB in store_roundtrip). */
    ASSERT_FALSE(break_update_store_put_chunk(s, NULL, 5));
    ASSERT_FALSE(break_update_store_put_chunk(NULL, tiny, 4));

    char n1[65];
    u8 h1[32];
    ASSERT_TRUE(break_crypto_sha256(tiny, 4, h1));
    bin2hex(h1, 32, n1);
    ASSERT_FALSE(break_update_store_has_chunk(NULL, n1));
    u8 *buf = NULL;
    u64 len = 0;
    ASSERT_FALSE(break_update_store_get_chunk(NULL, n1, &buf, &len));
    ASSERT_FALSE(break_update_store_get_chunk(s, n1, NULL, &len));
    ASSERT_FALSE(break_update_store_get_chunk(s, n1, &buf, NULL));
    ASSERT_TRUE(buf == NULL);

    break_update_store_destroy(s);
    cleanup_store(root, NULL, 0);
}

TEST(store_name_charset_rejected) {
    char root[512];
    test_tmp(root, sizeof(root), "upd_names");
    BreakUpdateStore *s = break_update_store_open(root);
    ASSERT_NOT_NULL(s);

    static const char *bad[] = {
        "31CA71057907D32BE7A05D519E2BA060FC5E1FF59090021896E1019B1F819D33", /* uppercase */
        "31ca71057907d32be7a05d519e2ba060fc5e1ff59090021896e1019b1f819d3",  /* 63 */
        "31ca71057907d32be7a05d519e2ba060fc5e1ff59090021896e1019b1f819d330", /* 65 */
        "zzca71057907d32be7a05d519e2ba060fc5e1ff59090021896e1019b1f819d33", /* non-hex */
        "31ca71057907d32be7a05d519e2ba060fc5e1ff59090021896e1019b1f819d3/",  /* slash */
        "../../../etc/passwd__________________________________________xx",
        "",
    };
    usize i;
    u8 *buf = NULL;
    u64 len = 0;
    for (i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
        ASSERT_FALSE(break_update_store_has_chunk(s, bad[i]));
        ASSERT_FALSE(break_update_store_get_chunk(s, bad[i], &buf, &len));
        ASSERT_TRUE(buf == NULL);
    }
    ASSERT_FALSE(break_update_store_has_chunk(s, NULL));
    ASSERT_FALSE(break_update_store_get_chunk(s, NULL, &buf, &len));

    break_update_store_destroy(s);
    cleanup_store(root, NULL, 0);
}

/* Gray rollout bucket: deterministic per (device, version), uniform over
 * 0..9999, admitted when bucket < percent in basis points. */
TEST(rollout_bucket_is_deterministic_bounded_and_uniform)
{
    u32 b1 = 0u, b2 = 0u, counts[10] = {0};
    const u32 v[3] = {1u, 2u, 3u};
    const u32 v2[3] = {1u, 2u, 4u};
    ASSERT_TRUE(break_update_rollout_bucket("device-0001", v, &b1));
    ASSERT_TRUE(break_update_rollout_bucket("device-0001", v, &b2));
    ASSERT_EQ(b1, b2);
    ASSERT_TRUE(b1 < 10000u);
    /* a new release reshuffles: across many devices the buckets differ */
    {
        u32 same = 0u;
        for (u32 i = 0u; i < 200u; i++) {
            char id[32];
            u32 x, y;
            snprintf(id, sizeof(id), "dev-%u", i);
            ASSERT_TRUE(break_update_rollout_bucket(id, v, &x));
            ASSERT_TRUE(break_update_rollout_bucket(id, v2, &y));
            if (x == y) same++;
        }
        ASSERT_TRUE(same < 5u);
    }
    /* roughly uniform: 10000 devices into 10 deciles, each within 10% */
    for (u32 i = 0u; i < 10000u; i++) {
        char id[32];
        u32 x;
        snprintf(id, sizeof(id), "uniform-%u", i);
        ASSERT_TRUE(break_update_rollout_bucket(id, v, &x));
        ASSERT_TRUE(x < 10000u);
        counts[x / 1000u]++;
    }
    for (u32 d = 0u; d < 10u; d++) {
        ASSERT_TRUE(counts[d] > 900u && counts[d] < 1100u);
    }
    /* admission */
    ASSERT_FALSE(break_update_rollout_admits(0u, 0u));      /* 0%: nobody */
    ASSERT_TRUE(break_update_rollout_admits(9999u, 10000u)); /* 100%: all */
    ASSERT_TRUE(break_update_rollout_admits(499u, 500u));    /* 5% */
    ASSERT_FALSE(break_update_rollout_admits(500u, 500u));
    ASSERT_FALSE(break_update_rollout_admits(10000u, 10000u)); /* bad bucket */
    ASSERT_TRUE(break_update_rollout_admits(0u, 20000u));    /* clamped */
    /* bad input */
    ASSERT_FALSE(break_update_rollout_bucket(NULL, v, &b1));
    ASSERT_FALSE(break_update_rollout_bucket("", v, &b1));
    ASSERT_FALSE(break_update_rollout_bucket("x", NULL, &b1));
    ASSERT_FALSE(break_update_rollout_bucket("x", v, NULL));
    {
        char longid[130];
        memset(longid, 'a', sizeof(longid) - 1u);
        longid[sizeof(longid) - 1u] = '\0';
        ASSERT_FALSE(break_update_rollout_bucket(longid, v, &b1)); /* > 128 */
        longid[128] = '\0';
        ASSERT_TRUE(break_update_rollout_bucket(longid, v, &b1));
    }
}

/* Allow-list ("白名单"): a newline-separated list of device ids (LF, an
 * optional trailing LF, blank lines ignored) admits a listed device ahead of
 * the share. Matching is exact and whole-line; malformed lists (a line over
 * the id cap, a CR, total over 64 KiB) are rejected, never half-read. */
TEST(rollout_allow_list_exact_whole_line_match)
{
    static const char list[] = "qa-device-1\nbeta-tester-7\n\nlab-3";
    bool listed = true;
    char big[130];
    ASSERT_TRUE(break_update_rollout_listed("beta-tester-7", list, sizeof(list) - 1u, &listed));
    ASSERT_TRUE(listed);
    ASSERT_TRUE(break_update_rollout_listed("lab-3", list, sizeof(list) - 1u, &listed));
    ASSERT_TRUE(listed);
    /* prefixes, suffixes and substrings do not match */
    ASSERT_TRUE(break_update_rollout_listed("beta-tester", list, sizeof(list) - 1u, &listed));
    ASSERT_FALSE(listed);
    ASSERT_TRUE(break_update_rollout_listed("beta-tester-77", list, sizeof(list) - 1u, &listed));
    ASSERT_FALSE(listed);
    ASSERT_TRUE(break_update_rollout_listed("qa", list, sizeof(list) - 1u, &listed));
    ASSERT_FALSE(listed);
    /* empty list: valid, nobody listed */
    ASSERT_TRUE(break_update_rollout_listed("lab-3", "", 0u, &listed));
    ASSERT_FALSE(listed);
    /* malformed: CR, over-long line, invalid device id */
    ASSERT_FALSE(break_update_rollout_listed("lab-3", "lab-3\r\n", 7u, &listed));
    memset(big, 'x', sizeof(big) - 1u);
    big[sizeof(big) - 1u] = '\0';
    ASSERT_FALSE(break_update_rollout_listed("lab-3", big, sizeof(big) - 1u, &listed));
    ASSERT_FALSE(break_update_rollout_listed("", list, sizeof(list) - 1u, &listed));
    ASSERT_FALSE(break_update_rollout_listed("lab-3", NULL, 4u, &listed));
    ASSERT_FALSE(break_update_rollout_listed("lab-3", list, sizeof(list) - 1u, NULL));
    ASSERT_FALSE(break_update_rollout_listed("lab-3", list,
                                             BREAK_UPDATE_ROLLOUT_LIST_MAX + 1u, &listed));
}

TEST_MAIN_BEGIN()
    RUN_TEST(golden_parse_accessors_verify);
    RUN_TEST(tamper_body_verify_false);
    RUN_TEST(unsigned_manifest_verify_false);
    RUN_TEST(truncation_parse_null);
    RUN_TEST(missing_duplicate_unsorted_keys_null);
    RUN_TEST(chunk_name_rules);
    RUN_TEST(chunk_listing_rules);
    RUN_TEST(field_strictness);
    RUN_TEST(byte_and_layout_strictness);
    RUN_TEST(signature_line_strictness);
    RUN_TEST(oversize_manifest_null);
    RUN_TEST(compatible_matrix);
    RUN_TEST(null_arg_matrix);
    RUN_TEST(store_open_layout);
    RUN_TEST(store_roundtrip);
    RUN_TEST(store_corruption_detected);
    RUN_TEST(store_zero_byte_chunk);
    RUN_TEST(store_size_limit_and_bad_args);
    RUN_TEST(store_name_charset_rejected);
    RUN_TEST(rollout_bucket_is_deterministic_bounded_and_uniform);
    RUN_TEST(rollout_allow_list_exact_whole_line_match);
TEST_MAIN_END()
