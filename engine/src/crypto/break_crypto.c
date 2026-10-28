/* ==========================================================================
 *  break_crypto.c — thin C11 wrapper over the system OpenSSL 3 libcrypto
 *  EVP API (Stage 5 Phase A Task 2). Zero home-grown cryptography: every
 *  primitive is an OpenSSL call:
 *    SHA-256        one-shot  EVP_Digest(); streaming  EVP_MD_CTX +
 *                            EVP_DigestInit_ex/Update/Final_ex
 *    HMAC-SHA256    EVP_MAC_fetch("HMAC") + EVP_MAC_init/update/final
 *    Ed25519 verify EVP_PKEY_new_raw_public_key + EVP_DigestVerify (no
 *                            pre-hash, per the Ed25519 pure scheme)
 *    CSPRNG         RAND_bytes(), chunked below its int parameter width
 *
 *  Error discipline (contract, see break_crypto.h): false on ANY failure;
 *  verify failure is indistinguishable from other failure. Every length is
 *  range-checked against the underlying OpenSSL parameter type before the
 *  call; all EVP length parameters are size_t, so no usize input can
 *  truncate there — the only int-width parameter is RAND_bytes' num, which
 *  is served by a chunked loop instead of a cast. OpenSSL-internal OOM
 *  paths cannot be intercepted by this repository's test hooks (documented
 *  in docs/design/security_threat_model.md §4/§8; no injection coverage is
 *  claimed there).
 * ========================================================================== */

#include <crypto/break_crypto.h>

#include <limits.h>
#include <stdlib.h>
#include <openssl/core.h>
#include <openssl/core_names.h>
#include <openssl/evp.h>
#include <openssl/opensslv.h>
#include <openssl/rand.h>

#if !defined(OPENSSL_VERSION_MAJOR) || OPENSSL_VERSION_MAJOR < 3
#error "break_crypto requires OpenSSL 3 libcrypto (EVP_MAC / raw Ed25519 keys)"
#endif

/* Valid stand-in pointer for NULL+0 inputs so OpenSSL never receives a NULL
 * data pointer even for zero-length operations. */
static const u8 k_break_crypto_empty[1] = {0};

static const void *break_crypto_data_or_empty(const void *data)
{
    return data ? data : (const void *)k_break_crypto_empty;
}

/* ---- SHA-256 one-shot -------------------------------------------------- */

bool break_crypto_sha256(const void *data, usize len, u8 out[32])
{
    unsigned int out_len = 0;
    if (!out) return false;
    if (!data && len > 0) return false;
    if (EVP_Digest(break_crypto_data_or_empty(data), len,
                   out, &out_len, EVP_sha256(), NULL) != 1) {
        return false;
    }
    return out_len == BREAK_CRYPTO_SHA256_SIZE;
}

/* ---- SHA-256 streaming ------------------------------------------------- */

struct BreakCryptoSha256Ctx {
    EVP_MD_CTX *mdctx;
    bool finalized; /* after final the ctx is destroy-only (documented state machine) */
};

BreakCryptoSha256Ctx *break_crypto_sha256_ctx_create(void)
{
    BreakCryptoSha256Ctx *ctx = (BreakCryptoSha256Ctx *)malloc(sizeof(*ctx));
    if (!ctx) return NULL;
    ctx->mdctx = EVP_MD_CTX_new();
    if (!ctx->mdctx) {
        free(ctx);
        return NULL;
    }
    ctx->finalized = false;
    if (EVP_DigestInit_ex(ctx->mdctx, EVP_sha256(), NULL) != 1) {
        EVP_MD_CTX_free(ctx->mdctx);
        free(ctx);
        return NULL;
    }
    return ctx;
}

bool break_crypto_sha256_update(BreakCryptoSha256Ctx *ctx, const void *data, usize len)
{
    if (!ctx || ctx->finalized) return false;
    if (!data && len > 0) return false;
    return EVP_DigestUpdate(ctx->mdctx, break_crypto_data_or_empty(data), len) == 1;
}

bool break_crypto_sha256_final(BreakCryptoSha256Ctx *ctx, u8 out[32])
{
    unsigned int out_len = 0;
    if (!ctx || !out || ctx->finalized) return false;
    if (EVP_DigestFinal_ex(ctx->mdctx, out, &out_len) != 1) {
        return false;
    }
    if (out_len != BREAK_CRYPTO_SHA256_SIZE) return false;
    ctx->finalized = true;
    return true;
}

void break_crypto_sha256_ctx_destroy(BreakCryptoSha256Ctx *ctx)
{
    if (!ctx) return;
    EVP_MD_CTX_free(ctx->mdctx);
    free(ctx);
}

/* ---- HMAC-SHA256 (EVP_MAC path) ---------------------------------------- */

bool break_crypto_hmac_sha256(const void *key, usize key_len,
                              const void *data, usize data_len, u8 out[32])
{
    EVP_MAC *mac = NULL;
    EVP_MAC_CTX *mctx = NULL;
    OSSL_PARAM params[2];
    size_t out_len = 0;
    bool ok = false;

    if (!out) return false;
    if (!key && key_len > 0) return false;
    if (!data && data_len > 0) return false;

    mac = EVP_MAC_fetch(NULL, "HMAC", NULL);
    if (!mac) goto done;
    mctx = EVP_MAC_CTX_new(mac);
    if (!mctx) goto done;

    params[0] = OSSL_PARAM_construct_utf8_string(
        OSSL_MAC_PARAM_DIGEST, (char *)"SHA256", 0);
    params[1] = OSSL_PARAM_construct_end();

    if (EVP_MAC_init(mctx, break_crypto_data_or_empty(key),
                     key_len, params) != 1) {
        goto done;
    }
    if (EVP_MAC_update(mctx, break_crypto_data_or_empty(data),
                       data_len) != 1) {
        goto done;
    }
    if (EVP_MAC_final(mctx, out, &out_len, BREAK_CRYPTO_SHA256_SIZE) != 1) {
        goto done;
    }
    ok = (out_len == BREAK_CRYPTO_SHA256_SIZE);

done:
    EVP_MAC_CTX_free(mctx);
    EVP_MAC_free(mac);
    return ok;
}

/* ---- Ed25519 verify (pure scheme, no pre-hash) -------------------------- */

bool break_crypto_ed25519_verify(const u8 sig[64], const void *msg, usize msg_len,
                                 const u8 pubkey[32])
{
    EVP_PKEY *pkey = NULL;
    EVP_MD_CTX *vctx = NULL;
    bool ok = false;

    if (!sig || !pubkey) return false;
    if (!msg && msg_len > 0) return false;

    pkey = EVP_PKEY_new_raw_public_key(EVP_PKEY_ED25519, NULL,
                                       pubkey, BREAK_CRYPTO_ED25519_KEY_SIZE);
    if (!pkey) goto done;
    vctx = EVP_MD_CTX_new();
    if (!vctx) goto done;
    if (EVP_DigestVerifyInit(vctx, NULL, NULL, NULL, pkey) != 1) goto done;
    /* Ed25519 is a one-shot, digest-less operation: EVP_DigestVerify over
     * the whole message; result 1 = valid, anything else = invalid/failure
     * (indistinguishable by contract). */
    ok = (EVP_DigestVerify(vctx, sig, BREAK_CRYPTO_ED25519_SIG_SIZE,
                           break_crypto_data_or_empty(msg),
                           msg_len) == 1);

done:
    EVP_MD_CTX_free(vctx);
    EVP_PKEY_free(pkey);
    return ok;
}

/* ---- CSPRNG ------------------------------------------------------------- */

bool break_crypto_random(u8 *out, usize len)
{
    if (!out && len > 0) return false;
    /* RAND_bytes takes an int num; chunk below INT_MAX instead of casting. */
    while (len > 0) {
        usize chunk = len > (usize)INT_MAX ? (usize)INT_MAX : len;
        if (RAND_bytes(out, (int)chunk) != 1) return false;
        out += chunk;
        len -= chunk;
    }
    return true;
}
