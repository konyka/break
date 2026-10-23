/* ==========================================================================
 *  test_break_crypto.c — Known-answer + misuse tests for the break_crypto
 *  OpenSSL EVP wrapper (Stage 5 Phase A Task 2).
 *
 *  Vector provenance (all cross-checked outside the test binary):
 *   - SHA-256: NIST examples ("" / "abc") + 56-byte ("abcdbcde...nopq") and
 *     64-byte (64 x 'a') block-boundary vectors; expected digests verified
 *     against python3 hashlib (OpenSSL-backed) on 2026-10-24.
 *   - HMAC-SHA256: RFC 4231 §4 test cases 1-7 (full 32-byte outputs;
 *     case 5 is the untruncated value) — verified against python3 hmac.
 *   - Ed25519: RFC 8032 §7.1 TEST 1/2/3 — TEST 2/3 verified against
 *     `openssl pkeyutl -verify -rawin`; TEST 1 (empty message, which
 *     pkeyutl cannot feed) verified against a direct EVP_DigestVerify
 *     call compiled against the system libcrypto.
 * ========================================================================== */

#include "test_framework.h"
#include <crypto/break_crypto.h>
#include <string.h>

/* ---- helpers ---------------------------------------------------------- */

static int hexval(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

/* Decodes exactly out_len bytes (2*out_len hex chars); returns false on
 * malformed input. Test-local helper, not a crypto primitive. */
static bool hex2bin(const char *hex, u8 *out, usize out_len)
{
    usize i;
    for (i = 0; i < out_len; i++) {
        int hi = hexval(hex[2 * i]);
        int lo = hexval(hex[2 * i + 1]);
        if (hi < 0 || lo < 0) return false;
        out[i] = (u8)((hi << 4) | lo);
    }
    return true;
}

static void expect_digest(const char *msg, usize len, const char *expected_hex)
{
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    u8 expected[BREAK_CRYPTO_SHA256_SIZE];
    ASSERT_TRUE(break_crypto_sha256(msg, len, out));
    ASSERT_TRUE(hex2bin(expected_hex, expected, sizeof(expected)));
    ASSERT_TRUE(memcmp(out, expected, sizeof(expected)) == 0);
}

/* ---- SHA-256 one-shot known-answer vectors ---------------------------- */

TEST(sha256_nist_empty)
{
    expect_digest("", 0,
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

TEST(sha256_nist_abc)
{
    expect_digest("abc", 3,
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
}

TEST(sha256_56byte_boundary)
{
    /* 56 bytes: the largest message still fitting one padded block. */
    static const char m[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    ASSERT_EQ(strlen(m), 56);
    expect_digest(m, 56,
        "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
}

TEST(sha256_64byte_boundary)
{
    /* 64 bytes: exactly one full compression block. */
    char m[64];
    memset(m, 'a', sizeof(m));
    expect_digest(m, sizeof(m),
        "ffe054fe7ae0cb6dc65c3af9b61d5209f439851db43d0ba5997337df154668eb");
}

TEST(sha256_null_empty_semantics)
{
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    /* NULL data with len 0 hashes the empty message (same digest as ""). */
    ASSERT_TRUE(break_crypto_sha256(NULL, 0, out));
    expect_digest("", 0,
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    /* NULL data with nonzero len, and NULL out, are rejected. */
    ASSERT_FALSE(break_crypto_sha256(NULL, 1, out));
    ASSERT_FALSE(break_crypto_sha256("abc", 3, NULL));
    ASSERT_FALSE(break_crypto_sha256(NULL, 0, NULL));
}

/* ---- SHA-256 streaming ------------------------------------------------ */

TEST(sha256_streaming_split_every_offset)
{
    /* For the 64-byte boundary message, every two-part split must equal the
     * one-shot digest (full offset scan, 0..64 inclusive). */
    char m[64];
    u8 oneshot[BREAK_CRYPTO_SHA256_SIZE];
    usize split;
    memset(m, 'a', sizeof(m));
    ASSERT_TRUE(break_crypto_sha256(m, sizeof(m), oneshot));
    for (split = 0; split <= sizeof(m); split++) {
        u8 out[BREAK_CRYPTO_SHA256_SIZE];
        BreakCryptoSha256Ctx *ctx = break_crypto_sha256_ctx_create();
        ASSERT_NOT_NULL(ctx);
        ASSERT_TRUE(break_crypto_sha256_update(ctx, m, split));
        ASSERT_TRUE(break_crypto_sha256_update(ctx, m + split, sizeof(m) - split));
        ASSERT_TRUE(break_crypto_sha256_final(ctx, out));
        ASSERT_TRUE(memcmp(out, oneshot, sizeof(out)) == 0);
        break_crypto_sha256_ctx_destroy(ctx);
    }
}

TEST(sha256_streaming_byte_at_a_time)
{
    static const char m[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    u8 oneshot[BREAK_CRYPTO_SHA256_SIZE];
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    usize i;
    BreakCryptoSha256Ctx *ctx;
    ASSERT_TRUE(break_crypto_sha256(m, 56, oneshot));
    ctx = break_crypto_sha256_ctx_create();
    ASSERT_NOT_NULL(ctx);
    for (i = 0; i < 56; i++) {
        ASSERT_TRUE(break_crypto_sha256_update(ctx, m + i, 1));
    }
    ASSERT_TRUE(break_crypto_sha256_final(ctx, out));
    ASSERT_TRUE(memcmp(out, oneshot, sizeof(out)) == 0);
    break_crypto_sha256_ctx_destroy(ctx);
}

TEST(sha256_streaming_zero_len_updates_are_noops)
{
    u8 oneshot[BREAK_CRYPTO_SHA256_SIZE];
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    BreakCryptoSha256Ctx *ctx;
    ASSERT_TRUE(break_crypto_sha256("abc", 3, oneshot));
    ctx = break_crypto_sha256_ctx_create();
    ASSERT_NOT_NULL(ctx);
    ASSERT_TRUE(break_crypto_sha256_update(ctx, NULL, 0)); /* NULL+0: no-op */
    ASSERT_TRUE(break_crypto_sha256_update(ctx, "abc", 3));
    ASSERT_TRUE(break_crypto_sha256_update(ctx, "zzz", 0));
    ASSERT_TRUE(break_crypto_sha256_final(ctx, out));
    ASSERT_TRUE(memcmp(out, oneshot, sizeof(out)) == 0);
    break_crypto_sha256_ctx_destroy(ctx);
}

TEST(sha256_streaming_state_machine_misuse)
{
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    BreakCryptoSha256Ctx *ctx = break_crypto_sha256_ctx_create();
    ASSERT_NOT_NULL(ctx);
    ASSERT_TRUE(break_crypto_sha256_update(ctx, "abc", 3));
    ASSERT_TRUE(break_crypto_sha256_final(ctx, out));
    /* Documented state machine: after final the ctx is destroy-only. */
    ASSERT_FALSE(break_crypto_sha256_update(ctx, "d", 1)); /* final then update */
    ASSERT_FALSE(break_crypto_sha256_final(ctx, out));     /* double final */
    break_crypto_sha256_ctx_destroy(ctx);
}

TEST(sha256_streaming_null_argument_matrix)
{
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    BreakCryptoSha256Ctx *ctx = break_crypto_sha256_ctx_create();
    ASSERT_NOT_NULL(ctx);
    ASSERT_FALSE(break_crypto_sha256_update(NULL, "a", 1));  /* NULL ctx */
    ASSERT_FALSE(break_crypto_sha256_final(NULL, out));      /* NULL ctx */
    ASSERT_FALSE(break_crypto_sha256_update(ctx, NULL, 1));  /* NULL data, len>0 */
    ASSERT_FALSE(break_crypto_sha256_final(ctx, NULL));      /* NULL out */
    break_crypto_sha256_ctx_destroy(ctx);
    break_crypto_sha256_ctx_destroy(NULL);                   /* destroy(NULL) safe */
}

/* ---- HMAC-SHA256: RFC 4231 test cases 1-7 ----------------------------- */

static void expect_hmac(const u8 *key, usize key_len, const u8 *data, usize data_len,
                        const char *expected_hex)
{
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    u8 expected[BREAK_CRYPTO_SHA256_SIZE];
    ASSERT_TRUE(break_crypto_hmac_sha256(key, key_len, data, data_len, out));
    ASSERT_TRUE(hex2bin(expected_hex, expected, sizeof(expected)));
    ASSERT_TRUE(memcmp(out, expected, sizeof(expected)) == 0);
}

TEST(hmac_sha256_rfc4231)
{
    u8 key[131];
    u8 data[152];
    usize i;

    /* Case 1 */
    memset(key, 0x0b, 20);
    expect_hmac(key, 20, (const u8 *)"Hi There", 8,
        "b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7");

    /* Case 2 */
    expect_hmac((const u8 *)"Jefe", 4,
        (const u8 *)"what do ya want for nothing?", 28,
        "5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843");

    /* Case 3 */
    memset(key, 0xaa, 20);
    memset(data, 0xdd, 50);
    expect_hmac(key, 20, data, 50,
        "773ea91e36800e46854db8ebd09181a72959098b3ef8c122d9635514ced565fe");

    /* Case 4 */
    for (i = 0; i < 25; i++) key[i] = (u8)(i + 1);
    memset(data, 0xcd, 50);
    expect_hmac(key, 25, data, 50,
        "82558a389a443c0ea4cc819899f2083a85f0faa3e578f8077a2e3ff46729665b");

    /* Case 5 (full 32-byte output; the RFC prints the 16-byte truncation) */
    memset(key, 0x0c, 20);
    expect_hmac(key, 20, (const u8 *)"Test With Truncation", 20,
        "a3b6167473100ee06e0c796c2955552bfa6f7c0a6a8aef8b93f860aab0cd20c5");

    /* Case 6 (key larger than the 64-byte block size) */
    memset(key, 0xaa, 131);
    expect_hmac(key, 131,
        (const u8 *)"Test Using Larger Than Block-Size Key - Hash Key First", 54,
        "60e431591ee0b67f0d8a26aacbf5b77f8e0bc6213728c5140546040f0ee37f54");

    /* Case 7 (large key and large data) */
    expect_hmac(key, 131,
        (const u8 *)"This is a test using a larger than block-size key and a "
        "larger than block-size data. The key needs to be hashed before being "
        "used by the HMAC algorithm.", 152,
        "9b09ffa71b942fcb27635fbcd5b0e944bfdc63644f0713938a7f51535c3a35e2");
}

TEST(hmac_sha256_empty_key_and_data)
{
    /* HMAC with an empty key is well-defined (key pads to a zero block);
     * expected value verified against python3 hmac. */
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    u8 expected[BREAK_CRYPTO_SHA256_SIZE];
    ASSERT_TRUE(break_crypto_hmac_sha256(NULL, 0, "abc", 3, out));
    ASSERT_TRUE(hex2bin("fd7adb152c05ef80dccf50a1fa4c05d5a3ec6da95575fc312ae7c5d091836351",
                        expected, sizeof(expected)));
    ASSERT_TRUE(memcmp(out, expected, sizeof(expected)) == 0);
    /* Empty data with a non-empty key succeeds (value not pinned; the RFC
     * 4231 matrix above pins the algorithm). */
    ASSERT_TRUE(break_crypto_hmac_sha256("k", 1, NULL, 0, out));
}

TEST(hmac_sha256_null_argument_matrix)
{
    u8 out[BREAK_CRYPTO_SHA256_SIZE];
    ASSERT_FALSE(break_crypto_hmac_sha256(NULL, 1, "abc", 3, out)); /* NULL key, len>0 */
    ASSERT_FALSE(break_crypto_hmac_sha256("k", 1, NULL, 1, out));   /* NULL data, len>0 */
    ASSERT_FALSE(break_crypto_hmac_sha256("k", 1, "abc", 3, NULL)); /* NULL out */
    ASSERT_FALSE(break_crypto_hmac_sha256(NULL, 0, "abc", 3, NULL));
}

/* ---- Ed25519: RFC 8032 §7.1 TEST 1/2/3 -------------------------------- */

static const char kT1Pub[] = "d75a980182b10ab7d54bfed3c964073a0ee172f3daa62325af021a68f707511a";
static const char kT1Sig[] =
    "e5564300c360ac729086e2cc806e828a84877f1eb8e5d974d873e06522490155"
    "5fb8821590a33bacc61e39701cf9b46bd25bf5f0595bbe24655141438e7a100b";
static const char kT2Pub[] = "3d4017c3e843895a92b70aa74d1b7ebc9c982ccf2ec4968cc0cd55f12af4660c";
static const char kT2Sig[] =
    "92a009a9f0d4cab8720e820b5f642540a2b27b5416503f8fb3762223ebdb69da"
    "085ac1e43e15996e458f3613d0f11d8c387b2eaeb4302aeeb00d291612bb0c00";
static const char kT3Pub[] = "fc51cd8e6218a1a38da47ed00230f0580816ed13ba3303ac5deb911548908025";
static const char kT3Sig[] =
    "6291d657deec24024827e69c3abe01a30ce548a284743a445e3680d7db5ac3ac"
    "18ff9b538d16f290ae67f760984dc6594a7c15e9716ed28dc027beceea1ec40a";

TEST(ed25519_rfc8032_valid_signatures)
{
    u8 pub[BREAK_CRYPTO_ED25519_KEY_SIZE];
    u8 sig[BREAK_CRYPTO_ED25519_SIG_SIZE];

    /* TEST 1: empty message. */
    ASSERT_TRUE(hex2bin(kT1Pub, pub, sizeof(pub)));
    ASSERT_TRUE(hex2bin(kT1Sig, sig, sizeof(sig)));
    ASSERT_TRUE(break_crypto_ed25519_verify(sig, "", 0, pub));

    /* TEST 2: 1-byte message 0x72. */
    ASSERT_TRUE(hex2bin(kT2Pub, pub, sizeof(pub)));
    ASSERT_TRUE(hex2bin(kT2Sig, sig, sizeof(sig)));
    ASSERT_TRUE(break_crypto_ed25519_verify(sig, "\x72", 1, pub));

    /* TEST 3: 2-byte message 0xaf82. */
    ASSERT_TRUE(hex2bin(kT3Pub, pub, sizeof(pub)));
    ASSERT_TRUE(hex2bin(kT3Sig, sig, sizeof(sig)));
    ASSERT_TRUE(break_crypto_ed25519_verify(sig, "\xaf\x82", 2, pub));
}

TEST(ed25519_bit_flip_rejection)
{
    u8 pub[BREAK_CRYPTO_ED25519_KEY_SIZE];
    u8 sig[BREAK_CRYPTO_ED25519_SIG_SIZE];
    u8 msg[1] = {0x72};

    ASSERT_TRUE(hex2bin(kT2Pub, pub, sizeof(pub)));
    ASSERT_TRUE(hex2bin(kT2Sig, sig, sizeof(sig)));
    ASSERT_TRUE(break_crypto_ed25519_verify(sig, msg, 1, pub));

    /* Flip one bit in the signature. */
    sig[0] ^= 0x01;
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, msg, 1, pub));
    sig[0] ^= 0x01;
    sig[63] ^= 0x80;
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, msg, 1, pub));
    sig[63] ^= 0x80;

    /* Flip one bit in the message. */
    msg[0] ^= 0x01;
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, msg, 1, pub));
    msg[0] ^= 0x01;

    /* Flip one bit in the public key. */
    pub[0] ^= 0x01;
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, msg, 1, pub));
    pub[0] ^= 0x01;
    pub[31] ^= 0x80;
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, msg, 1, pub));
    pub[31] ^= 0x80;

    /* Sanity: restored inputs verify again. */
    ASSERT_TRUE(break_crypto_ed25519_verify(sig, msg, 1, pub));
}

TEST(ed25519_wrong_length_rejection)
{
    /* The API's sig/key sizes are compile-time fixed arrays; the attacker-
     * controlled length is msg_len. A signature made over one message
     * length must not verify at another (message-length mismatch). */
    u8 pub[BREAK_CRYPTO_ED25519_KEY_SIZE];
    u8 sig[BREAK_CRYPTO_ED25519_SIG_SIZE];

    /* TEST 2 signs a 1-byte message: rejecting len 0 and len 2. */
    ASSERT_TRUE(hex2bin(kT2Pub, pub, sizeof(pub)));
    ASSERT_TRUE(hex2bin(kT2Sig, sig, sizeof(sig)));
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, "\x72", 0, pub));
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, "\x72\x00", 2, pub));

    /* TEST 1 signs the empty message: rejecting any nonzero length. */
    ASSERT_TRUE(hex2bin(kT1Pub, pub, sizeof(pub)));
    ASSERT_TRUE(hex2bin(kT1Sig, sig, sizeof(sig)));
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, "\x00", 1, pub));
}

TEST(ed25519_null_argument_matrix)
{
    u8 pub[BREAK_CRYPTO_ED25519_KEY_SIZE];
    u8 sig[BREAK_CRYPTO_ED25519_SIG_SIZE];
    ASSERT_TRUE(hex2bin(kT1Pub, pub, sizeof(pub)));
    ASSERT_TRUE(hex2bin(kT1Sig, sig, sizeof(sig)));
    /* NULL message with len 0 is the empty message: TEST 1 verifies. */
    ASSERT_TRUE(break_crypto_ed25519_verify(sig, NULL, 0, pub));
    ASSERT_FALSE(break_crypto_ed25519_verify(NULL, "", 0, pub));  /* NULL sig */
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, "", 0, NULL));  /* NULL pubkey */
    ASSERT_FALSE(break_crypto_ed25519_verify(sig, NULL, 1, pub)); /* NULL msg, len>0 */
}

/* ---- CSPRNG ----------------------------------------------------------- */

TEST(random_32bytes_not_all_zero)
{
    u8 buf[32];
    u8 zero[32];
    memset(buf, 0, sizeof(buf));
    memset(zero, 0, sizeof(zero));
    ASSERT_TRUE(break_crypto_random(buf, sizeof(buf)));
    /* Nonzero-run heuristic: 32 CSPRNG bytes are all-zero with probability
     * 2^-256, so equality with the zero block is a failure signal, not a
     * flake risk. */
    ASSERT_TRUE(memcmp(buf, zero, sizeof(buf)) != 0);
}

TEST(random_two_draws_differ)
{
    u8 a[32];
    u8 b[32];
    ASSERT_TRUE(break_crypto_random(a, sizeof(a)));
    ASSERT_TRUE(break_crypto_random(b, sizeof(b)));
    ASSERT_TRUE(memcmp(a, b, sizeof(a)) != 0);
}

TEST(random_argument_matrix)
{
    u8 buf[8];
    ASSERT_TRUE(break_crypto_random(buf, 0));  /* zero-length draw succeeds */
    ASSERT_TRUE(break_crypto_random(NULL, 0)); /* NULL with len 0 succeeds */
    ASSERT_FALSE(break_crypto_random(NULL, 1)); /* NULL with len>0 rejected */
}

/* ---- runner ------------------------------------------------------------ */

TEST_MAIN_BEGIN()
    RUN_TEST(sha256_nist_empty);
    RUN_TEST(sha256_nist_abc);
    RUN_TEST(sha256_56byte_boundary);
    RUN_TEST(sha256_64byte_boundary);
    RUN_TEST(sha256_null_empty_semantics);
    RUN_TEST(sha256_streaming_split_every_offset);
    RUN_TEST(sha256_streaming_byte_at_a_time);
    RUN_TEST(sha256_streaming_zero_len_updates_are_noops);
    RUN_TEST(sha256_streaming_state_machine_misuse);
    RUN_TEST(sha256_streaming_null_argument_matrix);
    RUN_TEST(hmac_sha256_rfc4231);
    RUN_TEST(hmac_sha256_empty_key_and_data);
    RUN_TEST(hmac_sha256_null_argument_matrix);
    RUN_TEST(ed25519_rfc8032_valid_signatures);
    RUN_TEST(ed25519_bit_flip_rejection);
    RUN_TEST(ed25519_wrong_length_rejection);
    RUN_TEST(ed25519_null_argument_matrix);
    RUN_TEST(random_32bytes_not_all_zero);
    RUN_TEST(random_two_draws_differ);
    RUN_TEST(random_argument_matrix);
TEST_MAIN_END()
