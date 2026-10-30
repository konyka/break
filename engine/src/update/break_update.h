#pragma once
/* ==========================================================================
 *  break_update — Stage 5 Phase A Task 4: the signed canonical manifest and
 *  the content-addressed chunk store. This library is the concrete landing
 *  of the update trust chain in docs/design/security_threat_model.md §4:
 *  offline Ed25519 signing key → signed canonical manifest →
 *  content-addressed chunks. The client VERIFIES only — no signing entry
 *  point exists anywhere in this library (signing is offline tooling).
 *
 *  Error discipline (plan Global Constraints): parse returns NULL on ANY
 *  structural/canonical deviation (no partial parse, no error-string
 *  oracle); verify returns plain false on ANY failure, indistinguishable
 *  from a bad signature. All attacker-controlled arithmetic (version
 *  triple, chunk size decimal, counts, offsets) is overflow-checked before
 *  any allocation sized by it.
 *
 *  Canonical enforcement details (all deviations → parse NULL):
 *   - every byte is LF or printable ASCII 0x20-0x7E (no CR, TAB, NUL,
 *     bytes >= 0x7F); the text ends with exactly one final LF;
 *   - the four header keys appear in the fixed order version, channel,
 *     platform, min-version, each exactly once, separator ": " (one space);
 *   - version components and chunk sizes are decimal without leading zeros
 *     ("0" itself is allowed) and are range-checked (u32 / u64);
 *   - the chunk hash is exactly 64 lowercase hex chars; chunk lines are
 *     sorted by name byte-wise and strictly increasing (unique names);
 *   - the signature line is the LAST line; its base64 is exactly 88 chars
 *     (86 data + "==" pad) with canonical zero pad bits, decoding to the
 *     64-byte Ed25519 signature over ALL bytes before that line;
 *   - a manifest with zero chunk lines is structurally valid.
 *  The 1 MiB total cap makes the 65536-chunk cap unreachable in practice
 *  (65537 minimal chunk lines already exceed 1 MiB); both are enforced.
 *
 *  Store discipline: put recomputes the SHA-256 of the data — the digest
 *  hex IS the file name (a caller-supplied name cannot disagree by
 *  construction); the write goes through PlatformAtomicWriter (fsync file
 *  → rename → fsync dir, see platform_fs.h); get re-hashes the bytes read
 *  and compares against the requested name before handing them out
 *  (verify-on-read — corruption returns false). get reads exactly the
 *  stat-reported length and re-hashes, which also closes the size/read
 *  race window. Chunk names accepted by has/get are exactly 64 lowercase
 *  hex chars — anything else is false (no path component can escape the
 *  chunks directory). A zero-length chunk is valid: get returns true with
 *  *out_len == 0 and *out_buf a freeable malloc pointer.
 *
 *  OpenSSL-internal OOM paths cannot be intercepted by this repository's
 *  test hooks (no injection coverage there — documented in
 *  docs/design/security_threat_model.md §4/§8).
 *
 *  Ed25519 small-order public-key note: OpenSSL's verifier follows ZIP-215
 *  cofactorless semantics, so its acceptance of a small-order (e.g.
 *  all-zero) public key is MESSAGE-DEPENDENT — empirically about 1/4 of
 *  message samples verify with an all-zero key + all-zero signature (Task 4
 *  review; pinned by the unsigned-path pins, which therefore must use a
 *  real key — test_break_update_target_contract.cmake:174-180). This is
 *  architecturally unreachable here by contract: the verification pubkey
 *  MUST be a compile-time built-in trusted constant and is NEVER
 *  attacker-controlled input (there is no key field in the manifest). If a
 *  future phase ever takes the pubkey from external input, this acceptance
 *  behavior MUST be re-evaluated before doing so.
 * ========================================================================== */

#include <core/types.h>

/* engine/src/update/break_update.h — manifest is canonical text (UTF-8 ASCII subset, LF):
 *   break-manifest-v1
 *   version: MAJOR.MINOR.PATCH
 *   channel: <1..64 chars [a-z0-9-]>
 *   platform: <1..64 chars [a-z0-9-]>
 *   min-version: MAJOR.MINOR.PATCH
 *   chunk: <sha256-64hex> <size-dec> <name ≤128B [A-Za-z0-9._/-], no "..", no leading '/'>
 *   ...                     (chunk lines sorted by name byte-wise; names unique)
 *   signature: <base64 86+2pad chars, Ed25519 over ALL bytes before this line>
 * Limits: total ≤ 1 MiB; ≤ 65536 chunks; field values ≤ 64B. ANY deviation → parse NULL. */

typedef struct BreakUpdateManifest BreakUpdateManifest;   /* opaque, owns parsed memory */
BreakUpdateManifest *break_update_manifest_parse(const void *text, usize len);   /* structure+canonical only */
bool break_update_manifest_verify(const BreakUpdateManifest *m, const u8 pubkey[32]); /* signature check */
void break_update_manifest_destroy(BreakUpdateManifest *m);
void break_update_manifest_version(const BreakUpdateManifest *m, u32 out[3]);
void break_update_manifest_min_version(const BreakUpdateManifest *m, u32 out[3]);
const char *break_update_manifest_channel(const BreakUpdateManifest *m);   /* borrowed */
const char *break_update_manifest_platform(const BreakUpdateManifest *m);  /* borrowed */
u64 break_update_manifest_chunk_count(const BreakUpdateManifest *m);
/* false on bad index; out_name borrowed (≤128B), out_hash 32B copied, *out_size set */
bool break_update_manifest_chunk_at(const BreakUpdateManifest *m, u64 index,
                                    const char **out_name, u8 out_hash[32], u64 *out_size);
/* Policy: platform string equal AND channel equal AND current version >= min-version. */
bool break_update_manifest_compatible(const BreakUpdateManifest *m, const char *channel,
                                      const char *platform, u32 cur_major, u32 cur_minor, u32 cur_patch);

/* Gray rollout (client half). The server publishes a release to a share of
 * devices; the client decides deterministically whether it is in that
 * share, without any server round-trip:
 *   bucket = first 4 bytes (big-endian) of
 *            SHA-256("break-rollout-v1\n" device_id "\n" MAJOR.MINOR.PATCH)
 *            mod 10000
 * so a device keeps its bucket for one release and is reshuffled for the
 * next (no device is always first). device_id: 1..128 bytes, opaque (the
 * app supplies a stable per-install id; it is hashed, never sent).
 * admits(bucket, percent_bp): bucket < percent_bp, where percent_bp is the
 * share in basis points (0 = nobody, 10000 = everyone; larger is clamped).
 * The share itself must come from authenticated data (e.g. a signed field
 * a later manifest version adds); nothing here trusts it. */
#define BREAK_UPDATE_ROLLOUT_BUCKETS 10000u
#define BREAK_UPDATE_ROLLOUT_DEVICE_ID_MAX 128u
bool break_update_rollout_bucket(const char *device_id, const u32 version[3],
                                 u32 *out_bucket);
bool break_update_rollout_admits(u32 bucket, u32 percent_bp);
/* Allow-list (QA / beta devices that take a release ahead of the share).
 * list: LF-separated device ids (len bytes, NOT NUL-terminated; optional
 * trailing LF; blank lines ignored; ≤ BREAK_UPDATE_ROLLOUT_LIST_MAX bytes).
 * *out_listed = whether device_id equals one whole line, byte-exactly.
 * false (out untouched) for an invalid device_id, NULL list with len > 0,
 * NULL out, len over the cap, a CR anywhere, or a line longer than
 * BREAK_UPDATE_ROLLOUT_DEVICE_ID_MAX — a malformed list is never
 * half-applied. Like the share, the list must come from authenticated data. */
#define BREAK_UPDATE_ROLLOUT_LIST_MAX (64u * 1024u)
bool break_update_rollout_listed(const char *device_id, const char *list, usize len,
                                 bool *out_listed);

/* Content-addressed store: <root>/chunks/<sha256hex>; manifest files via caller's own pathing.
 * put: name must be the sha256-hex of data (recomputed); atomic writer; size ≤ 128 MiB.
 * get: verify-on-read (re-hash before handing bytes out); caller-owned *out_buf (malloc). */
typedef struct BreakUpdateStore BreakUpdateStore;
BreakUpdateStore *break_update_store_open(const char *root_path);   /* mkdirs layout; NULL on error */
void break_update_store_destroy(BreakUpdateStore *s);
bool break_update_store_put_chunk(BreakUpdateStore *s, const void *data, usize len); /* name = computed hash */
bool break_update_store_has_chunk(BreakUpdateStore *s, const char *sha256_hex_name);
bool break_update_store_get_chunk(BreakUpdateStore *s, const char *sha256_hex_name,
                                  u8 **out_buf, u64 *out_len);   /* false on miss/corruption */
