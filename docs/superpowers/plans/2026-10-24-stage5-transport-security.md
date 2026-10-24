# Stage 5 Phase D (Transport Security: Pin + TLS + Session Auth + Rate Limit) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver Stage 5 subproject 4 (transport authentication + key/session lifecycle) and the transport-borne parts of subproject 5 (replay protection, rate limits): pin the Snowflake dependency by commit hash with a fail-closed configure-time check, wire snow's memory-BIO TLS into the `break_net` adapter as an explicit per-reactor mode, add a real session authentication handshake (challenge-response HMAC over fresh nonces, key lookup seam) with monotonic outbound sequence, and wire bounded admission rate limits. Server-side authority remains a documented design target (no server product ships); client anti-tamper remains the documented cost model (no client anti-tamper code this phase).

**Architecture:** Snowflake stays a path-referenced external repo but becomes commit-pinned in `locked_dependencies.json` with a configure-time `git rev-parse` equality gate (fail-closed). TLS uses snowflake's existing OpenSSL memory-BIO wrapper (`snow_ssl_*`, handshake-from-start): the adapter gains a `BreakNetTlsConfig` setter (CREATED-state only), allocates one `snow_ssl_t` per connection in the existing `on_new_connection` hook (callbacks and outbound drain provably share one thread — the `snow_ssl_t` single-thread contract is satisfied), splits inbound ciphertext/plaintext inside the existing parser, and encrypts outbound frames after envelope encode. Session auth adds registry message CHALLENGE (id=3): server sends a fresh 16-byte nonce on accept; the client answers AUTH v2 (`key_id[8] ‖ client_nonce[16] ‖ HMAC-SHA256 tag[32]` over both nonces); a caller-supplied key callback resolves `key_id`→PSK (the key-lifecycle seam). Outbound envelopes get real monotonic per-connection sequences (fixing the hardcoded-0 gap); inbound keeps strict-increment (TCP ordered; cross-connection replay is defeated by fresh server nonces + TLS channel binding — analysis documented). Rate limits attach at snow's official `admit(ip,port)` hook: a global token bucket plus a bounded per-IP frequency table.

**Tech Stack:** C11; snowflake @ pinned commit (memory-BIO TLS over OpenSSL); `break_crypto` HMAC-SHA256 + CSPRNG (Phase A); existing `break_net`/`break_session`; real TCP loopback tests (THREAD mode, port-0 acceptor); test-only self-signed cert fixtures referenced from the snowflake tree via compile definition (no file copies).

## Global Constraints

- C11; no new external dependencies (OpenSSL arrives transitively via snowflake's `snow::net`, which already links it when found; `break_crypto` when `BREAK_ENABLE_CRYPTO=ON`). No home-grown crypto/auth anywhere: session proof = `break_crypto_hmac_sha256` ONLY.
- **No snowflake source modifications** (external repo; findings like the `snow_ssl_read` ZERO_RETURN header/impl divergence and the missing TLS shutdown API are documented limitations, not patched).
- `break_net` stays gated on `BREAK_ENABLE_SNOWFLAKE` (existing); session-auth code additionally requires `BREAK_ENABLE_CRYPTO` (`#if` composition documented; both OFF ⇒ plaintext AUTH v1 behavior unchanged). TLS mode is opt-in per reactor; plaintext mode unchanged and fully tested.
- Wire format authority is the 18-byte little-endian envelope (`break_net_envelope.h:13-17`); the unused big-endian 12-byte validator in `break_net_protocol.c` is NOT extended (documented as non-authoritative).
- Bounded everything: per-IP rate table ≤ 1024 entries (eviction documented); nonces 16 bytes from `break_crypto_random`; AUTH v2 payload exactly 56 bytes; CHALLENGE payload exactly 16 bytes; auth failure → immediate close (existing `break_session.c:270-272` path); session lifetime config optional (0 = no expiry default).
- Fail closed: TLS handshake failure → parser ERR → connection closes; pin mismatch → configure FATAL_ERROR with remediation text; `BREAK_ENABLE_SNOWFLAKE=ON` + TLS configured but snow built without OpenSSL → configure-time assertion (no runtime NOSYS surprise).
- All new behavior headless-tested over real TCP loopback (THREAD mode; port-0 acceptor; condition-polling drivers — existing test shapes) plus in-process negative matrix.
- Three-tree lanes (normal / ASan+UBSan / TSan), any new/changed contract ctests, nm discipline for touched targets, `ENGINE_BUILD_TESTS=OFF` tree builds; fuzz lane `Not Run` (house convention).
- Honest docs: TLS without PKI guidance is not "secure deployment" — docs state verify_peer/CA requirements for production; self-signed fixtures are test-only; server authority and anti-tamper remain design-target statements.

---

## File and Target Map

- Modify: `engine/external/locked_dependencies.json` — add snowflake pin entry (name/version=commit/purpose=runtime-optional/source=path/sha256=`n/a-commit-pinned`/verify mechanism documented).
- Modify: `engine/CMakeLists.txt` — pin verification + OpenSSL-presence assertion inside the existing `BREAK_ENABLE_SNOWFLAKE` block; `break_net` gains `break_crypto` link when both gates ON; new test `test_break_net_tls` + registrations.
- Modify: `engine/src/network/break_net_adapter.h/.c` — TLS config + per-connection TLS + parser split + outbound encryption + monotonic outbound sequence + rate-limit config/admit wiring + admission counter.
- Modify: `engine/src/network/break_session.h/.c` — CHALLENGE/AUTH-v2 handshake + key callback seam + optional session max-age.
- Modify: `engine/src/network/break_net_message_registry.c` — register CHALLENGE (id=3, v1..1, 16-byte payload, PHASE_NEW-only policy per registry capabilities) + AUTH accepts v1..2.
- Create: `engine/tests/test_break_net_tls.c` — TLS loopback suite; modify `engine/tests/test_break_session.c` / `test_break_net_adapter.c` only where outbound-sequence==0 pins must be updated to monotonic expectations.
- Docs: new `docs/design/transport_security.md`; closeout touches `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 5 subprojects 4 + transport-borne parts of 5), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`, `docs/design/security_threat_model.md` (§5/§7 status sync), `docs/design/session_protocol.md` (CHALLENGE/AUTH-v2 + outbound sequence + rate limits).

---

### Task 1: Snowflake commit pin + configure-time gates (no behavior change)

**Files:**
- Modify: `engine/external/locked_dependencies.json` (add snowflake entry)
- Modify: `engine/CMakeLists.txt` (pin check + OpenSSL assertion inside the `BREAK_ENABLE_SNOWFLAKE` block, `:291-309`)
- Modify: `docs/design/snowflake_c11_adapter.md` (pin policy + verified hash)

**Interfaces:** no code interface change. Pin mechanism (verbatim semantics):
```cmake
# inside if(BREAK_ENABLE_SNOWFLAKE), after SNOWFLAKE_SOURCE_DIR resolution:
# execute_process(COMMAND git -C <dir> rev-parse HEAD) must equal the pinned hash below,
# else FATAL_ERROR naming the pinned hash, the found hash, and the update procedure.
set(BREAK_SNOWFLAKE_PIN "7d40d19c85115042555b6707ffebbfb4fadb8e38")  # snowflake main HEAD 2026-10-24
```

- [ ] Add the locked_dependencies.json entry (name `snowflake`, version = pinned commit, purpose `runtime-optional (BREAK_ENABLE_SNOWFLAKE)`, sha256 `n/a-commit-pinned-via-configure-check`, platforms linux/windows/macos).
- [ ] CMake: pin equality gate (fail-closed FATAL_ERROR with pinned/found/update-procedure text; non-git or missing dir already FATALs earlier) + assertion that snow's OpenSSL is enabled when `BREAK_ENABLE_CRYPTO=ON` (fail-closed configure message; the stub-returning-NOSYS build is only acceptable when CRYPTO=OFF — documented).
- [ ] RED: no test change; verification = configure experiments: (a) correct pin → configures; (b) tampered pin in a /tmp copy → FATAL_ERROR with the required text; (c) `BREAK_ENABLE_SNOWFLAKE=OFF` tree unaffected.
- [ ] GREEN: default tree + `build-session`-style snowflake-enabled tree both configure/build green; full non-graphics suite unchanged (this task must not alter any test count).
- [ ] Docs update; commit.

### Task 2: TLS transport mode in the break_net adapter

**Files:**
- Modify: `engine/src/network/break_net_adapter.h`, `engine/src/network/break_net_adapter.c`
- Create: `engine/tests/test_break_net_tls.c`
- Modify: `engine/CMakeLists.txt` (test registration; fixture dir compile definition pointing into `${SNOWFLAKE_SOURCE_DIR}/tests/common/fixtures/ssl`)

**Interfaces (verbatim):**
```c
/* break_net_adapter.h additions */
typedef struct BreakNetTlsConfig {
    const char *cert_file;   /* PEM; server cert — required */
    const char *key_file;    /* PEM; matching key — required */
    const char *ca_file;     /* PEM; optional (NULL) — client verification CA */
    int verify_peer;         /* 0 = do not request client certs; 1 = require+verify */
} BreakNetTlsConfig;
/* CREATED state only; copies the strings. TLS is a server-side acceptor mode:
 * with TLS set, EVERY accepted connection must complete a TLS handshake before any
 * envelope parses; handshake failure closes the connection (fail-closed).
 * false on: non-CREATED state, NULL, missing cert/key, snow built without OpenSSL. */
bool break_net_reactor_set_tls(BreakNetReactor *r, const BreakNetTlsConfig *cfg);
bool break_net_reactor_is_tls(const BreakNetReactor *r);
```

Implementation requirements (from recon, pinned): per-connection `snow_ssl_t` created in the existing `on_new_connection` hook (`break_net_adapter.c:135`), freed in `on_closed` (`:219-231` — free must respect the pending-drain deferred release at `:337-367`); inbound split inside `break_net_parser` (`:73-133`): pre-handshake bytes feed `snow_ssl_do_handshake` (ciphertext consumed via `move_header`; produced handshake ciphertext re-injected via `snow_connection_send`); post-handshake, `snow_ssl_read` into the plaintext envelope path unchanged; outbound: `break_net_drain_outbound` (`:383-433`) encrypts after `break_net_envelope_encode` via `snow_ssl_write`. Threading: callbacks and drain provably share one thread (`:489-526` THREAD / `:735-737` STEP) satisfying the `snow_ssl_t` single-thread contract — assert by construction comment. TLS close_notify vs TCP FIN indistinguishability (snow wrapper swallows ZERO_RETURN): documented limitation; existing close events stay authoritative.

- [ ] RED: `test_break_net_tls` fails to build/link before implementation.
- [ ] GREEN tests (real loopback, THREAD mode, port-0 acceptor, condition-polling; fixtures referenced via compile definition, cert CN=localhost self-signed, verify_peer=0 unless stated): full handshake → AUTH/PING exchange where the client side (raw POSIX socket + in-test client `snow_ssl_t`) decrypts and sees the exact envelope bytes; outbound PING arrives ciphertext-on-wire (raw socket read sees NO plaintext magic `42524b31`) and decrypts to the known frame; garbage-before-TLS (client writes 64 junk bytes) → connection closed without any event; plaintext-envelope client against TLS server → closed; mismatched cert/key config → `set_tls` false; `BREAK_ENABLE_CRYPTO=OFF` build with TLS configured → documented behavior (TLS transport works without crypto gate; only session auth needs crypto — pin by a configure/build check); TLS+`verify_peer=1` with fixture CA → handshakes (client presents fixture cert), and without client cert → closed.
- [ ] Regression: existing `test_break_net_adapter` / `test_break_session` plaintext suites unchanged and green.
- [ ] Lanes: build-sdd-p5d, -asan, -tsan green ×3 (snowflake-enabled configs: `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/snowflake`); ASan ×3 / TSan ×5 repeats zero reports; `timeout -s KILL 60` direct runs exit 0 (no handshake hangs).
- [ ] Commit.

### Task 3: Session authentication handshake + monotonic outbound sequence

**Files:**
- Modify: `engine/src/network/break_session.h`, `engine/src/network/break_session.c`
- Modify: `engine/src/network/break_net_message_registry.c` (CHALLENGE id=3; AUTH v1..2)
- Modify: `engine/src/network/break_net_adapter.c` (outbound sequence from per-connection counter; challenge send on accept when auth configured)
- Modify: `engine/tests/test_break_session.c`, `engine/tests/test_break_net_adapter.c` (update outbound-sequence==0 pins to monotonic)
- Modify: `engine/CMakeLists.txt` (`break_net` links `break_crypto` when `BREAK_ENABLE_CRYPTO=ON`)

**Interfaces (verbatim):**
```c
/* break_session.h additions (compiled when BREAK_ENABLE_CRYPTO; absent otherwise) */
/* CHALLENGE payload (message_id=3, v1): server_nonce[16]. AUTH v2 payload (message_id=1,
 * version 2, 56 bytes): key_id[8] ‖ client_nonce[16] ‖ tag[32], where
 * tag = HMAC-SHA256(psk, "BRKAUTH2" ‖ server_nonce ‖ client_nonce) and psk comes from: */
typedef bool (*BreakNetAuthKeyFn)(void *user, const u8 key_id[8], u8 out_psk[32]);  /* false = unknown key */
/* NEW-state only. When set, the session layer expects CHALLENGE→AUTH v2 (server side)
 * and answers challenges (client side helper). Key rotation = callback resolves by
 * key_id (the key-lifecycle seam; provisioning/rollover stay app-side, documented). */
bool break_session_set_auth(BreakNetAuthKeyFn fn, void *user);
/* Optional session expiry (0 = no expiry, default); authenticated sessions older than
 * max_age_seconds transition CLOSING at the next poll (GameThread). */
void break_session_set_max_age(BreakSession *s, u32 max_age_seconds);
```

Semantics pinned: server_nonce from `break_crypto_random` per connection (fresh ⇒ captured AUTH tags are worthless on new connections — the cross-connection replay argument); AUTH v1 plaintext acceptance is a config decision (`break_session_set_auth` unset ⇒ v1 test behavior unchanged; set ⇒ v1 AUTH rejected — fail-closed when auth configured); auth failure → immediate close (existing `:270-272`); outbound envelope sequence = per-connection monotonic counter starting at 1 (inbound strict-increment unchanged).

- [ ] RED: session/auth tests fail before implementation.
- [ ] GREEN tests: happy-path CHALLENGE→AUTH v2 over plaintext loopback (auth configured) → AUTHENTICATED; tampered tag → closed, never AUTHENTICATED; unknown key_id → closed; AUTH v1 when auth configured → rejected/closed; AUTH v2 replayed on a second connection (same bytes) → rejected (fresh server nonce) — the replay pin; outbound sequences 1,2,3… observed by the peer (updated pins); `max_age` expiry transitions at poll; CRYPTO=OFF tree compiles without the auth symbols (nm check) and keeps v1 behavior.
- [ ] Lanes ×3 green; ASan ×3 / TSan ×5 zero reports; timeout-wrapped direct runs.
- [ ] Commit.

### Task 4: Admission rate limits

**Files:**
- Modify: `engine/src/network/break_net_adapter.h`, `engine/src/network/break_net_adapter.c`
- Modify: `engine/tests/test_break_net_adapter.c`

**Interfaces (verbatim):**
```c
/* break_net_adapter.h additions */
typedef struct BreakNetRateLimitConfig {
    u32 global_accept_per_sec;   /* token bucket rate; 0 = unlimited */
    u32 global_burst;            /* bucket capacity; 0 = unlimited */
    u32 per_ip_per_minute;       /* sliding-window accepts per source IP; 0 = unlimited */
} BreakNetRateLimitConfig;
/* CREATED state only. Uses snow ratelimiter/freqlimiter under the admit(ip,port) hook
 * (snow_net_thread_add_acceptor_with_handlers_ex). Per-IP table ≤ 1024 entries;
 * full table → deny NEW IPs (fail-closed, documented), known IPs still measured.
 * All limiter state lives on the network driver thread (limiters are not thread-safe). */
bool break_net_reactor_set_rate_limits(BreakNetReactor *r, const BreakNetRateLimitConfig *cfg);
u64 break_net_reactor_admission_denied(const BreakNetReactor *r);   /* observable counter */
```

- [ ] RED: tests fail before implementation.
- [ ] GREEN tests: burst allowance then denials (global bucket: accept burst=N, next immediate accepts denied, counter increments; deterministic via injected-clock limiter `_at` variants where the API allows, else real-clock short windows); per-IP window denies the (limit+1)-th connection from loopback within the window; counter observable; limits disabled (zeros) → legacy behavior; config on non-CREATED → false.
- [ ] Lanes ×3 green; ASan ×3 / TSan ×5 zero reports.
- [ ] Commit.

### Task 5: Validation and documentation closeout

**Files:**
- Create: `docs/design/transport_security.md`
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 5: subproject 4 delivered client+library-side; subproject 5 partially — replay/rate-limit delivered, server authority + anti-tamper remain design targets), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`, `docs/design/security_threat_model.md` (§5 transport auth scope → delivered items; §7 replay/rate-limit model → delivered enforcement points), `docs/design/session_protocol.md` (CHALLENGE/AUTH-v2, outbound monotonic sequence, rate limits, TLS mode)

- [ ] Clean normal tree (snowflake-enabled): full default build + all `break_net` lanes green; `ENGINE_BUILD_TESTS=OFF` tree; nm discipline on `libbreak_net.a`; full non-graphics suite green with failure classification per house convention (note: snowflake-gated tests absent in default OFF builds — document both configurations).
- [ ] ASan/UBSan + TSan trees green, zero reports; timeout-wrapped direct runs.
- [ ] Pin gate re-verified (tamper experiment in /tmp copy → FATAL_ERROR).
- [ ] transport_security.md: trust chain (TLS channel → CHALLENGE/AUTH-v2 → session binding), nonce freshness replay analysis, key lifecycle seam (provisioning/rotation app-side, key_id resolution), rate-limit model + capacity/eviction, production PKI requirements (verify_peer/CA; self-signed fixtures test-only), documented limitations (no TLS shutdown API, ZERO_RETURN divergence, no session resumption, per-connection state not resumable), NOT-delivered (server product, per-device key provisioning tooling, anti-tamper code, DTLS/QUIC).
- [ ] threat model §5/§7 status sync; roadmap Stage 5 subprojects 4/5 wording honest (client anti-tamper = cost-model document only).
- [ ] `git diff --check` clean on branch range.

## Cross-cutting Review Gates

- RED before production code; GREEN normal/ASan/TSan after.
- No home-grown crypto/auth: grep gate — session proof only via `break_crypto_hmac_sha256`; no FNV/checksum-as-auth anywhere in the diff.
- Fail closed: TLS handshake failure closes; auth failure closes; pin mismatch FATALs at configure; full per-IP table denies new IPs.
- Plaintext regression: with no TLS/auth configured, wire behavior is byte-identical to before (existing suites prove it; reviewer diff-checks the parser split didn't alter the plaintext path).
- Threading contract: all `snow_ssl_t` use on the driver thread only (construction argument + code read).
- Bounded: per-IP table ≤1024; AUTH v2 56B; CHALLENGE 16B; counters observable; no unbounded retry in tests (condition polls have deadlines).
- Zero flake tolerance: all loopback tests use port-0 + condition-polling with deadlines; no fixed sleeps as synchronization.
- Docs honest: no "secure deployment" claim without PKI guidance; limitations section complete; server authority/anti-tamper remain design targets.
- A task completes only after focused code review, doc update, and `git diff --check` on its range.
