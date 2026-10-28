# Stage 5 Phase A (Security Foundations + Signed Package Format) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver Stage 5 Phase A: the threat-model/security-contract document required by the roadmap acceptance gates, version/build identity, a `break_crypto` library backed by system OpenSSL EVP (SHA-256 / HMAC-SHA256 / Ed25519 verify / CSPRNG — no home-grown crypto), write-side PAL primitives (atomic file commit), and `break_update` with the signed-manifest format and content-addressed chunk store (Stage 5 subproject 1). Download/resume/A-B/rollback (subproject 2), crash capture/upload (3), transport authentication (4), and replay/rate-limit/anti-tamper (5) are follow-up Phase B/C/D plans, NOT this plan.

**Architecture:** `break_crypto` is a thin C11 wrapper over the system OpenSSL 3 libcrypto EVP API (maintained primitive source; vendored/self-rolled crypto is rejected by the roadmap acceptance line "Cryptographic tests use maintained platform/library primitives; no home-grown authentication"). `break_update` builds the update trust root offline-verifyable: a canonical text manifest signed with Ed25519 (client verifies only; signing is offline tooling), plus a local content-addressed chunk store whose filenames are SHA-256 hex digests, written through a new atomic-commit PAL writer (tmp + fsync + rename) and re-hashed on every read (verify-on-read). Both libraries are formal optional static targets with contract tests pinning that `engine`/`engine_demo`/`dxx_break`/`editor` do not link them.

**Tech Stack:** C11; system OpenSSL 3.5.9 libcrypto (headers confirmed present; `pkg-config --modversion openssl` = 3.5.9); `engine/src/platform/platform_fs.c` (Phase 3 PAL file); ctest lanes normal/ASan+UBSan/TSan.

## Global Constraints

- C11. Exactly ONE new external dependency: OpenSSL libcrypto (system, maintained). No home-grown hash/MAC/signature code. `snow_auth`'s keyed-FNV-1a remains non-cryptographic and is NOT reused (documented in the threat-model doc).
- New formal optional targets `break_crypto` + `break_update`: `ENGINE_BUILD_TESTS`-independent, and NOT linked by `engine`/`engine_demo`/`dxx_break`/`editor` — contract ctests pin both directions (mirror `test_break_editor_target_contract.cmake` shape).
- `BREAK_ENABLE_CRYPTO` option (default ON): `find_package(OpenSSL REQUIRED)`; ON + not found → `FATAL_ERROR` (fail-closed, mirrors the `BREAK_ENABLE_SNOWFLAKE` idiom at `engine/CMakeLists.txt:291-309`); OFF → both targets and their tests absent.
- Bounded everything: manifest ≤ 1 MiB, ≤ 65536 chunk entries, chunk logical name ≤ 128 bytes, channel/platform/version fields ≤ 64 bytes; store chunk size ≤ 128 MiB (matches `VFS_MAX_FILE_BYTES`); all parse arithmetic overflow-checked; fail-closed on any structural anomaly.
- Error discipline: verify APIs return plain `false` on ANY validation failure (no partial-success, no error-string oracle for attacker-controlled input); parse APIs return NULL with an internal-only reason enum (no detailed parse-error oracle beyond "structure invalid" — documented decision).
- Windows branches of new PAL functions compile-only (no Windows lane here — same precedent as `platform_list_dir`); POSIX branch fully tested.
- Fuzz lane is not built in this repo state → record `Not Run` (house convention per `runtime_security.md` §8.2).
- Three-tree lanes (normal / `-DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON` / `-DENGINE_USE_TSAN=ON`), contract ctests, nm export gates, `ENGINE_BUILD_TESTS=OFF` tree builds, all per established SDD protocol.
- Honest docs: Phase A delivers offline verification primitives + on-disk formats ONLY. No transport security, no download, no crash upload, no server. OpenSSL OOM paths are not interceptable by repo test hooks — document, do not claim injection coverage there.

---

## File and Target Map

- Create: `docs/design/security_threat_model.md` — Stage 5 threat model + client trust limits + server authority + update trust chain + crash-data privacy/redaction contract + anti-tamper cost model (extends `runtime_security.md` §3/§10).
- Create: `engine/src/core/break_version.h/.c` — `BREAK_VERSION_MAJOR/MINOR/PATCH` macros + `BREAK_BUILD_ID` (CMake-injected `git rev-parse --short=12 HEAD`, `"unknown"` fallback) + `break_version_string()`; compiled into the `engine` target (product metadata, like `log.c`).
- Create: `engine/src/crypto/break_crypto.h/.c` — SHA-256 one-shot+streaming, HMAC-SHA256, Ed25519 verify, CSPRNG bytes; target `break_crypto` (PUBLIC `OpenSSL::Crypto`).
- Modify: `engine/src/platform/platform_fs.h/.c` — atomic-commit writer + `platform_mkdir` + `platform_file_size` (POSIX tested; Win32 compile-only).
- Create: `engine/src/update/break_update.h/.c` — canonical manifest parse/verify/accessors + compatibility policy + CAS chunk store.
- Create tests: `engine/tests/test_break_version.c`, `test_break_crypto.c`, `test_platform_fs_write.c`, `test_break_update.c`; contract `engine/tests/test_break_crypto_target_contract.cmake` + `test_break_update_target_contract.cmake`.
- Modify: `engine/CMakeLists.txt` — option, find_package, targets, tests, contract ctests.
- Modify at closeout: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 5 → Phase A delivered; subprojects 2-5 pending), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`.

---

### Task 1: Threat model document + version/build identity

**Files:**
- Create: `docs/design/security_threat_model.md`
- Create: `engine/src/core/break_version.h`, `engine/src/core/break_version.c`
- Create: `engine/tests/test_break_version.c`
- Modify: `engine/CMakeLists.txt` (version TU into `engine` sources; `BREAK_BUILD_ID` define via `git rev-parse --short=12 HEAD` with `"unknown"` fallback; new test)

**Interfaces (verbatim):**
```c
/* engine/src/core/break_version.h */
#define BREAK_VERSION_MAJOR 0  /* product triple starts 0.1.0; bump rules documented */
#define BREAK_VERSION_MINOR 1
#define BREAK_VERSION_PATCH 0
/* Returns "MAJOR.MINOR.PATCH[+buildid]" — static storage, never NULL. */
const char *break_version_string(void);
```

- [ ] Threat model doc contents (all mandatory, extend `runtime_security.md` §3.3/§10): client trust limits (client NEVER authoritative; anti-tamper raises attack cost only); server authority enumeration (economy/inventory/damage/matchmaking examples as design targets); update trust chain (offline Ed25519 signing key → signed canonical manifest → content-addressed chunks; client verifies only; no unsigned path in release — roadmap acceptance line); transport auth + key/session lifecycle scope statement (Phase B/C); crash-data privacy (paths/peer/user-data redaction contract before any upload exists); replay/rate-limit model statement; Snowflake pin/vendoring risk recorded (path-referenced, not in `locked_dependencies.json`); explicit "NOT delivered" list (subprojects 2-5, TLS wiring into break_net adapter, snow TLS usage).
- [ ] RED: `test_break_version` — string non-NULL, matches `^0\.1\.0(\+.+)?$` shape (parse-check in test), build-id suffix non-empty when injected. Fails before the TU exists.
- [ ] GREEN: implement; test passes.
- [ ] Lanes: build-sdd-p5a, -asan, -tsan — new test green on all three; `engine` still builds `ENGINE_BUILD_TESTS=OFF` (existing notests tree rebuild).
- [ ] Commit.

### Task 2: break_crypto (OpenSSL EVP wrapper)

**Files:**
- Create: `engine/src/crypto/break_crypto.h`, `engine/src/crypto/break_crypto.c`
- Create: `engine/tests/test_break_crypto.c`
- Create: `engine/tests/test_break_crypto_target_contract.cmake`
- Modify: `engine/CMakeLists.txt` (`BREAK_ENABLE_CRYPTO` option + `find_package(OpenSSL REQUIRED)` + `break_crypto` static lib PUBLIC `OpenSSL::Crypto` + test + contract ctest)

**Interfaces (verbatim):**
```c
/* engine/src/crypto/break_crypto.h — all functions return false on ANY failure;
 * verify failure is indistinguishable from other failure by design. */
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
```

- [ ] RED: known-answer tests fail to link before the lib exists (record linker errors as RED evidence).
- [ ] GREEN tests (all must pass): SHA-256 NIST vectors (`""`, `"abc"`, 56-byte and 64-byte boundary vectors); streaming split at every byte offset equals one-shot; HMAC-SHA256 RFC 4231 test cases 1-7; Ed25519 RFC 8032 TEST 1/2/3 verify true + bit-flipped sig/msg/key verify false + wrong-length rejection; `break_crypto_random` 32 bytes nonzero-run heuristic + two draws differ; NULL/empty argument matrix; `final` then `update` misuse → false (documented state machine).
- [ ] nm gate: production `libbreak_crypto.a` exports exactly the 8 public symbols above; zero OpenSSL symbols re-exported (archive link test: a tiny executable links ONLY `libbreak_crypto.a` + `-lcrypto` and runs one verify).
- [ ] Contract ctest: `engine`/`engine_demo`/`dxx_break`/`editor` zero `break_crypto_*` symbols; source-list pin.
- [ ] Lanes ×3 trees green; ASan ×3 / TSan ×5 repeats of `test_break_crypto` zero reports.
- [ ] Commit.

### Task 3: Write-side PAL (atomic commit writer)

**Files:**
- Modify: `engine/src/platform/platform_fs.h`, `engine/src/platform/platform_fs.c`
- Create: `engine/tests/test_platform_fs_write.c`
- Modify: `engine/CMakeLists.txt` (test)

**Interfaces (verbatim):**
```c
/* platform_fs.h additions — POSIX tested; Win32 branch compile-only (_WIN32):
 * CreateFile/WriteFile/_fsync-equivalent (FlushFileBuffers)/MoveFileEx(REPLACE_EXISTING). */

/* Opens "<path>.tmpXXXXXX" in the SAME directory as path (rename atomicity requires
 * same filesystem). Only ONE writer per instance; not thread-safe. */
typedef struct PlatformAtomicWriter PlatformAtomicWriter;
PlatformAtomicWriter *platform_atomic_writer_open(const char *path);     /* NULL on error */
bool platform_atomic_writer_write(PlatformAtomicWriter *w, const void *data, usize len); /* false → abort state */
bool platform_atomic_writer_commit(PlatformAtomicWriter *w);  /* fsync file, close, rename over path,
                                                                 fsync directory, free writer */
void platform_atomic_writer_abort(PlatformAtomicWriter *w);   /* close + unlink tmp + free; idempotent */

bool platform_mkdir(const char *path);                        /* single level; true if exists-as-dir */
bool platform_file_size(const char *path, u64 *out_size);     /* false if missing/not-regular */
```

- [ ] RED: tests fail before implementation (commit/abort/visibility cases).
- [ ] GREEN tests: commit → content readable at target + tmp gone; overwrite existing target atomically (content swapped); abort → no tmp file, target untouched (pre-existing content intact); write-after-failure returns false; abort idempotent (double abort safe); commit on read-only directory (0444) → false + no tmp residue; `platform_mkdir` existing dir true / nested missing parent false; `platform_file_size` on 0-byte and 1 MiB files; NULL argument matrix.
- [ ] Lanes ×3 trees green; ASan/TSan repeats zero reports.
- [ ] Doc: header comment documents crash-safety ordering (fsync file → rename → fsync dir) and the Win32 compile-only status.
- [ ] Commit.

### Task 4: break_update (signed manifest + content-addressed store)

**Files:**
- Create: `engine/src/update/break_update.h`, `engine/src/update/break_update.c`
- Create: `engine/tests/test_break_update.c`
- Create: `engine/tests/test_break_update_target_contract.cmake`
- Modify: `engine/CMakeLists.txt` (`break_update` static lib PUBLIC `break_crypto` + test + contract ctest; gated on `BREAK_ENABLE_CRYPTO`)

**Interfaces (verbatim):**
```c
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
```

- [ ] RED: golden/tamper tests fail before implementation.
- [ ] GREEN tests: golden manifest (test-generated Ed25519 keypair via OpenSSL at test time or a fixed test-only keypair committed as hex constants — pick fixed test vectors, sign offline ONCE with a scratch OpenSSL script and embed; document provenance); parse→verify true; tamper: single-bit flip in body → verify false; truncation → parse NULL; missing/duplicate/unsorted keys → NULL; name `..`/absolute/too-long → NULL; >1 MiB → NULL; compatible() matrix (channel mismatch, platform mismatch, older current, equal min boundary); store: put→has→get round-trip bytes equal; get re-hash corruption detection (flip one byte in the chunk file externally → get false); put wrong-size/zero-byte chunk; 128 MiB+1 rejection without allocation blowup (use sparse/ oversized claim — test via size parameter on write path only, document); unknown-name charset rejection.
- [ ] nm gate: `libbreak_update.a` exports exactly the 15 public symbols; contract ctest pins no-link into engine/demos/editor + source list.
- [ ] Lanes ×3 trees green; ASan ×3 / TSan ×5 repeats zero reports; `timeout -s KILL 60` direct binary runs exit 0.
- [ ] Commit.

### Task 5: Validation and documentation closeout

**Files:**
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 5 status: Phase A delivered — threat model doc + version identity + break_crypto + atomic-write PAL + break_update signed-manifest/CAS; subprojects 2-5 pending), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`
- Modify: `engine/CMakeLists.txt` only if a real fix is needed.

- [ ] Clean normal tree: full default build + new lanes green; `ENGINE_BUILD_TESTS=OFF` tree builds all production targets; nm: zero test-hook symbols in production archives (incl. new libs).
- [ ] ASan/UBSan + TSan trees: all lanes green, zero reports.
- [ ] Full non-graphics/non-fuzz suite; classify failures (graphics / platform-skip / pre-cleared flake `test_break_replication_fragment` + pre-existing `test_vulkan` golden drift / branch-caused=fix).
- [ ] Contract ctests green (all four target-contract suites).
- [ ] `git diff --check` clean on branch range.
- [ ] Threat-model doc cross-check: every "NOT delivered" claim matches code reality; no doc claims transport security, download, crash upload, or server behavior.

## Cross-cutting Review Gates

- RED before production code; GREEN normal/ASan/TSan after (three-tree evidence per task).
- No home-grown crypto/authentication anywhere in the diff; every crypto call goes through OpenSSL EVP (`grep` gate in review: no `sha256_transform`-style local implementations introduced).
- Verify APIs fail closed and indistinguishable; no partial commit; parse bounds enforced before any allocation sized by attacker-controlled numbers (overflow-checked).
- Atomic writer ordering: fsync file → rename → fsync directory; abort never leaves residue.
- New libraries stay out of `engine`/`engine_demo`/`dxx_break`/`editor` link closures (contract tests).
- No GPU behavior claims; no server-side claims; client-side verification only.
- Docs honest: Phase A = offline primitives + on-disk formats; Stage 5 subprojects 2-5 explicitly pending; fuzz `Not Run`.
- A task completes only after focused code review, doc update, and `git diff --check` on its range.
