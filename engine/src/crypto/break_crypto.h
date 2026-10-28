#pragma once
#include <core/types.h>

/* ==========================================================================
 *  break_crypto — thin C11 wrapper over the system OpenSSL 3 libcrypto EVP
 *  API (Stage 5 Phase A Task 2; primitive layer of the update trust chain in
 *  docs/design/security_threat_model.md §4).
 *
 *  Zero home-grown cryptography: every primitive below is an OpenSSL EVP
 *  call (SHA-256 via EVP_Digest*, HMAC-SHA256 via EVP_MAC, Ed25519 verify
 *  via EVP_DigestVerify, CSPRNG via RAND_bytes). No primitive is
 *  implemented locally.
 *
 *  Error discipline: all functions return false on ANY failure; verify
 *  failure is indistinguishable from other failure by design (no
 *  partial-success, no error-string oracle for attacker-controlled input).
 *
 *  NULL/length discipline: a NULL data pointer is accepted only when the
 *  matching length is 0 (treated as empty input); NULL with a nonzero
 *  length, or a NULL out pointer, is always false. Lengths are usize and
 *  are range-checked against the underlying OpenSSL parameter types before
 *  every call (no silent truncation).
 *
 *  Streaming state machine: a created ctx accepts update() calls;
 *  final() produces the digest exactly once — after final() the ctx is
 *  destroy-only (update() and final() both return false on a finalized
 *  ctx). destroy(NULL) is a safe no-op.
 *
 *  OpenSSL-internal OOM paths cannot be intercepted by this repository's
 *  test hooks (no injection coverage there — documented in
 *  docs/design/security_threat_model.md §4/§8).
 * ========================================================================== */

#define BREAK_CRYPTO_SHA256_SIZE 32
#define BREAK_CRYPTO_ED25519_SIG_SIZE 64
#define BREAK_CRYPTO_ED25519_KEY_SIZE 32

bool break_crypto_sha256(const void *data, usize len, u8 out[32]);       /* NULL/oversize → false */

typedef struct BreakCryptoSha256Ctx BreakCryptoSha256Ctx;                 /* opaque; streaming */
BreakCryptoSha256Ctx *break_crypto_sha256_ctx_create(void);               /* NULL on OOM */
bool break_crypto_sha256_update(BreakCryptoSha256Ctx *ctx, const void *data, usize len);
bool break_crypto_sha256_final(BreakCryptoSha256Ctx *ctx, u8 out[32]);    /* ctx stays reusable-destroy only */
void break_crypto_sha256_ctx_destroy(BreakCryptoSha256Ctx *ctx);

bool break_crypto_hmac_sha256(const void *key, usize key_len,
                              const void *data, usize data_len, u8 out[32]);
bool break_crypto_ed25519_verify(const u8 sig[64], const void *msg, usize msg_len,
                                 const u8 pubkey[32]);                    /* false = invalid/failure */
bool break_crypto_random(u8 *out, usize len);                             /* CSPRNG; false on failure */
