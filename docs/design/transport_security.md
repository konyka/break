# Transport Security — break_net TLS mode, CHALLENGE/AUTH-v2, replay/rate-limit model

Status: **delivered client+library-side** (Stage 5 Phase D, 2026-10-24, branch `sdd/stage5-transport-security`, range `a7c0588b..c80efeb2` + closeout; plan `docs/superpowers/plans/2026-10-24-stage5-transport-security.md`). This document is the contract record for Stage 5 subproject 4 (transport authentication, key/session lifecycle seam) and the delivered half of subproject 5 (replay protection, admission rate limits). It is honest about what exists: a **library seam with loopback evidence**, not a deployed service. There is no server product, no production PKI material in this repo, and no "secure deployment" claim — see §8 and §9.

## 1. Trust chain

The delivered trust chain has three links, each enforced at a different layer, in order:

```text
TLS channel (optional, server-side acceptor mode; OpenSSL 3.5.9 via Snowflake snow_ssl_*)
        │  confidentiality + peer/server authentication; handshake failure closes (fail-closed)
        ▼
CHALLENGE (message_id=3, v1, 16B fresh server_nonce per connection)
        │  server proves liveness of the nonce; client binds its reply to this connection
        ▼
AUTH v2 (message_id=1, version 2, 56B: key_id[8] || client_nonce[16] || tag[32])
        │  tag = HMAC-SHA256(psk, "BRKAUTH2" || server_nonce || client_nonce);
        │  wrong tag / unknown key_id / wrong version / AUTH-v1-after-set_auth → CLOSING (fail-closed)
        ▼
Session binding (BreakSessionManager: NEW → AUTHENTICATING → AUTHENTICATED)
        authenticated session carries monotonic inbound sequence checks and optional max_age expiry
```

Independence of the links, verified by test:

- TLS alone does not authenticate the application peer at the protocol level — the CHALLENGE/AUTH-v2 handshake runs identically over plaintext and TLS transports. Test 2 of `test_break_net_tls.c` runs the AUTH handshake through TLS.
- CHALLENGE/AUTH-v2 does not require TLS: it provides origin authentication (HMAC) but **not confidentiality**. Without TLS the wire carries the CHALLENGE/AUTH bytes in cleartext. The plaintext AUTH-v1 path is byte-identical to the pre-Phase-D behavior when no auth is configured (existing suites prove it).
- `BREAK_ENABLE_CRYPTO=OFF` builds: the AUTH-v2/CHALLENGE surface is absent (registry accepts AUTH v1 only, CHALLENGE id 3 unregistered), so there is no unauthenticated AUTH-v2 plaintext bypass. nm verified: `break_session_set_auth`, `break_session_set_max_age`, both internal seams, and all `break_crypto_*` undefined/absent. TLS still works in this configuration (it depends only on Snowflake's own OpenSSL detection, not on `break_crypto`).

## 2. TLS mode

Interface (`engine/src/network/break_net_adapter.h:36-50`):

```c
typedef struct BreakNetTlsConfig {
    const char *cert_file;   /* PEM; server cert — required */
    const char *key_file;    /* PEM; matching key — required */
    const char *ca_file;     /* PEM; optional (NULL) — client verification CA */
    int verify_peer;         /* 0 = do not request client certs; 1 = require+verify */
} BreakNetTlsConfig;
bool break_net_reactor_set_tls(BreakNetReactor *reactor, const BreakNetTlsConfig *cfg);
bool break_net_reactor_is_tls(const BreakNetReactor *reactor);
```

Semantics (all fail-closed):

- CREATED state only, exactly once; the strings are copied. TLS is a **server-side acceptor mode**: with TLS set, every accepted connection must complete a TLS handshake before any envelope parses. Handshake failure closes the connection; no `MESSAGE_RECEIVED` events are produced from pre-handshake bytes.
- `verify_peer != 0 && ca_file == NULL` is rejected outright (deviation D1, adjudicated): OpenSSL's `FAIL_IF_NO_PEER_CERT` without a CA silently degrades to verify-none, so "require+verify" without a CA is a false configuration, not a degraded one.
- Garbage-before-handshake and a plaintext envelope aimed at a TLS server both end in a closed connection with zero message events.
- mTLS works: `verify_peer=1` with a CA accepts a client presenting a fixture cert and rejects a certless client (fail-closed).
- The parser splits at `break_net_parser`: `tls_ctx == NULL` → the original plaintext frame parser (pure extraction, byte-identical); non-NULL → the TLS path (`break_net_parser_tls`), which consumes the whole ciphertext burst, runs the handshake, reinjects handshake/alert ciphertext via `snow_connection_send` outside the queue mutex (deadlock argument in task-2-report), and drains any post-handshake residual application ciphertext in the same burst so a client that pipelines `Finished+appdata` cannot deadlock the server.
- Threading contract: every `snow_ssl_t` touch (handshake/read/write/free) happens on the single reactor driver thread — THREAD mode alternates drain/step on the host thread, STEP mode serializes via the step-driver atomic guard. `tls_ctx` is configured only in CREATED state and immutable after start, so parser reads are lock-free. TSan ×5 zero reports.
- Outbound: messages enqueued before handshake completion wait in the 256-entry outbound queue (per-connection FIFO preserved; no head-of-line blocking across connections — a handshaking peer does not freeze other peers' sends, fix round 1 I1). Once handshaked, the drain path encrypts via `snow_ssl_write` into a per-identity scratch buffer and sends a copy.

Evidence: `test_break_net_tls.c` 10/10 — config validation matrix (NULL/missing cert/missing key/mismatched key/verify_peer-without-CA/second call/non-CREATED), handshake+AUTH/PING round-trip with a wire-level assertion that the envelope magic never appears on the raw socket (LE and BE scan of the full rawlog), garbage-negative, plaintext-negative, mTLS accept and reject, blocked-handshake peer isolation, full-ring/middle-removal order pins. Green on normal/ASan+UBSan/TSan trees, ×3/×5 repeated zero-report runs.

## 3. CHALLENGE / AUTH-v2

Wire definitions (`engine/src/network/break_session.h:23-34`, registry `break_net_message_registry.c`):

| Message | ID | Versions | Payload limit | Phase | Duplicate policy |
|---:|---:|---:|---:|---|---|
| AUTH | 1 | 1..2 (CRYPTO=ON); 1..1 (OFF) | 64 KiB | ANY | REJECT |
| PING | 2 | 1..1 | 64 KiB | ANY | IDEMPOTENT |
| CHALLENGE | 3 | 1..1 (CRYPTO=ON only) | 16 B | ANY | REJECT |

Flow:

1. On accept (with auth configured), the adapter generates a fresh 16-byte `server_nonce` via `break_crypto_random`, stores it on the connection identity, and queues CHALLENGE(id=3, v1, 16B). In TLS mode the CHALLENGE is sent only after the handshake completes.
2. The client answers AUTH v2, exactly 56 bytes: `key_id[8] || client_nonce[16] || tag[32]`.
3. The session manager resolves the PSK through the app-supplied callback `BreakNetAuthKeyFn(user, key_id, out_psk[32])`, then checks `tag == HMAC-SHA256(psk, "BRKAUTH2" || server_nonce || client_nonce)` with a fixed 32-byte constant-time loop.
4. Failure taxonomy, all fail-closed into CLOSING: unknown key_id, tampered tag, wrong version, wrong length, missing server nonce, AUTH v1 after `break_session_set_auth`, and AUTH v2 while crypto is compiled in but no auth is configured.
5. Success migrates the session to AUTHENTICATED.

Crypto discipline: only `break_crypto_hmac_sha256` and `break_crypto_random` are called — zero home-grown crypto, no FNV/checksum-as-auth anywhere in the diff (grep gate). The keyed-FNV-1a `snow_auth` in the Snowflake tree is explicitly not reused (threat model §2).

Configuration contract (`break_session_set_auth(fn, user)`): process-wide because the pinned two-argument interface has no manager parameter. Changes are accepted only while every session is NEW **and** no authentication operation is active — an operation pins its fn/user snapshot through its first state transition and final dispatch under a global operation lease (review fix round 1), so a mid-handshake `set_auth`/`clear` returns false instead of racing the snapshot. The callback resolves key_id, so provisioning and rollover stay app-side.

Built-in CHALLENGE client helper: generates a random 16B client_nonce and sends AUTH v2 with the **all-zero key_id** — an adjudicated convention (task 3): the pinned interface has no client key selector, so the helper requests key_id zero; servers resolving arbitrary configured key_ids still work when clients hand-form AUTH v2. Unknown key_id always fails closed.

### Nonce freshness and replay argument

- `server_nonce` is 16 bytes (128 bits) from the system CSPRNG, generated per accepted connection. A replayed AUTH v2 from connection A carries the tag bound to A's `server_nonce`; connection B has an independent nonce, so the tag does not verify on B. Cross-connection byte-exact replay is test-pinned to fail.
- Within one connection the tag also covers the client_nonce, so two authentication attempts on the same connection with different client nonces produce different tags; the REJECT duplicate policy plus strict inbound sequence monotonicity (`decode_with_context` requires strictly increasing sequence) stop same-connection redelivery.
- AUTH is a one-shot transition (NEW → AUTHENTICATING → AUTHENTICATED; repeated authentication returns false), so a captured AUTH cannot be replayed after success either.
- What is NOT covered: there is no replay window for post-authentication application messages beyond the strict inbound sequence check, and no replay protection across reconnects for non-AUTH messages — the inbound sequence resets when a connection identity is recycled. This is a documented boundary: the anti-replay guarantee is scoped to the authentication handshake and per-connection ordering.
- Application-message replay window (library piece, 2026-10-30): `engine/src/network/break_replay_window.{h,c}` keeps the highest accepted 64-bit sequence number and a 64-bit bitmap of the 64 before it (RFC 4303 §3.4.3 style). Each number is accepted once; late arrivals within the window are accepted; older ones are rejected as `TOO_OLD`; sequence 0 is reserved. `check` does not consume, `check_and_mark` does — the intended order is check → authenticate (MAC/AEAD) → check_and_mark, so a forged packet cannot burn a number. One window per (sender, key); reset on rekey. Tests: `test_break_replay_window` (5 cases: duplicates, late arrivals, window slide incl. a jump to `UINT64_MAX` without shift overflow, check-without-mark, NULL); two mutations (shift without the ≥64 clear, an off-by-one window edge) each turn a case red. **Not wired**: break_net's message path does not use it yet (its envelope sequence is 32-bit and strictly ordered per connection), so the boundary above still describes the shipped transport.
- Message/byte rate limit (library piece, 2026-10-30): `engine/src/network/break_msg_rate.{h,c}` gives each admitted connection two token buckets on an injected millisecond clock, one in messages and one in bytes. A message is admitted only if both hold enough (1 message, `bytes` bytes); a refused message costs nothing and increments a denied counter. Tokens are kept in thousandths so rates that are not multiples of 1000/s lose no remainder; a clock that goes backwards refills nothing; refill saturates at the burst without overflow, even with `UINT32_MAX` rates and a `UINT64_MAX` clock. A message larger than the byte burst is never admissible, so callers must cap message size below it. Tests: `test_break_msg_rate` (4 cases: burst then refill, independent byte limit, fractional refill and backwards clock, bad configuration and overflow); two mutations (message check against 1 instead of 1000 thousandths, refill without saturation) each turn cases red. **Wired (opt-in)**: `break_session_manager_set_message_rate(manager, &cfg)` enables it per session manager (four non-zero limits plus a monotonic millisecond clock callback; only while no session is bound; `NULL` disables). Each bound or reclaimed session gets fresh full buckets. Every received message is admitted against its connection's buckets before the registry lookup and dispatch; an over-limit message is dropped, recorded as `BREAK_SESSION_APPLY_RATE_LIMITED` (`stats.rate_limited`, mirrored in the editor's `BreakEditorRemoteSessionStats`), and the session stays open. Default is off, so existing behaviour is unchanged. Tests in `test_break_session`: per-connection drop and refill, byte bucket, frozen configuration, fresh buckets for a rebound connection key; removing the admit gate turns both red.

## 4. Key lifecycle seam

Delivered: the **seam** only. `BreakNetAuthKeyFn` maps an 8-byte key_id to a 32-byte PSK; provisioning, storage, rotation, and revocation are application-side, inside the callback. The engine never stores key material: the PSK lives in a stack buffer for the duration of verification. Session expiry (`break_session_set_max_age`, 0 = no expiry, monotonic clock — `CLOCK_MONOTONIC` on POSIX, `GetTickCount64` on Windows) ages AUTHENTICATED sessions into CLOSING at the next GameThread poll; the expiry scan is bounded by capacity and is not deferrable by the close budget (review fix round 1).

NOT delivered: key generation tooling, per-device provisioning, rotation/rollout orchestration, revocation lists, key escrow. Until those exist app-side, the authentication seam is not a deployable credential system.

## 5. Rate-limit model and capacity

Interface (`break_net_adapter.h:52-62`): `BreakNetRateLimitConfig{global_accept_per_sec, global_burst, per_ip_per_minute}` + `break_net_reactor_set_rate_limits` (CREATED only, once) + `break_net_reactor_admission_denied` (observable counter).

Model:

- Enforcement point is the Snowflake admission hook (`snow_net_thread_add_acceptor_with_handlers_ex`) — a denied connection is refused **before** any connection object, identity, or session slot is allocated.
- Global token bucket (snow ratelimiter): `global_accept_per_sec` refill + `global_burst` capacity; both must be non-zero together or the configuration fails.
- Per-IP sliding window (snow freqlimiter): `per_ip_per_minute` accepts per source IP text. The per-IP table is fixed at **1024 entries**; a full table denies **new** IPs (fail-closed, documented) while known IPs keep being measured. No dynamic growth, no eviction.
- All limiter state lives on the network driver thread (limiters are not thread-safe). The denied counter is `_Atomic uint64_t` with relaxed atomic access because the public observer may read it off-thread (review fix round 1 — C11 compliance).
- All fields zero ⇒ no admission state allocated, `admit=NULL` registered, legacy behavior preserved, counter stays 0.
- Known limitation (documented, conservative direction): a consumed token is not refunded if Snowflake fails to create the connection after admit — the rollback hook is unused, so the limiter errs toward denying more.

Evidence: `test_break_net_adapter.c` 38/38 — global burst denial with a short real-clock refill window (denial itself is asserted via counter + connection count, not sleep), per-IP window denial, full-table semantics at the capacity boundary, config lifecycle (CREATED-only/once/all-zero no-op). Green on three trees.

## 6. Boundedness ledger

| Resource | Bound | Enforcement |
|---|---|---|
| Event queue / outbound queue | 256 entries each | OVERLOAD, no inline |
| Connection identity table | 256 | create-time cap vs `max_connections` |
| Per-IP admission table | 1024 entries | full → deny new IPs |
| AUTH v2 payload | 56 B exact | registry + session length check |
| CHALLENGE payload | 16 B exact | registry limit |
| Denied counter | `_Atomic uint64_t` | observable via `break_net_reactor_admission_denied` |
| Outbound sequence | uint32 per connection, monotonic from 1, saturates at UINT32_MAX (no wrap to 0) | drain-path assignment, retry preserves assigned sequence |
| Session capacity | `max_sessions` lifetime bindings; closed slots never recycled | bind refusal |
| Test synchronization | port-0 + condition polling with deadlines; zero fixed sleeps | all loopback tests |

## 7. Production PKI requirements (honest guidance)

What this library gives you is TLS transport with `verify_peer` support — **not** a PKI. For any real deployment:

- Use certificates from a real CA chain (public CA or an operated private CA); `ca_file` must carry that CA for `verify_peer=1`.
- The self-signed fixture certs under `tests/common/fixtures/ssl` exist **for tests only** (injected via the `BREAK_TEST_SSL_FIXTURE_DIR` compile macro). They are a one-cert PKI stand-in; shipping them or anything derived from them as production trust anchors defeats peer authentication.
- Key files are read by the Snowflake/OpenSSL layer from PEM paths — filesystem permissions and custody of `key_file` are the application's responsibility; the engine does not manage, rotate, or protect key material on disk.
- `verify_peer=0` (no client certs) means the TLS channel authenticates only the server-to-client direction at the transport level; application-level peer identity then rests entirely on CHALLENGE/AUTH-v2 PSKs.
- No "secure deployment" claim is made: there is no server product, no deployment guide beyond this section, and the loopback evidence does not cover WAN conditions, cert rotation, CRL/OCSP, or cipher policy hardening (Snowflake/OpenSSL defaults are used as-is).

## 8. Documented limitations

- **No TLS shutdown API / ZERO_RETURN divergence**: the Snowflake wrapper swallows `SSL_ERROR_ZERO_RETURN` (`snow_openssl.c:589-598`) and exposes no close_notify API, so close_notify and TCP FIN are indistinguishable. The adapter treats the TCP-layer close event as authoritative (`on_closed` semantics unchanged); the TLS close signal is not separately reported.
- **No session resumption**: `SSL_SESS_CACHE_OFF`; per-connection TLS state is not resumable, and session-level state (session id, sequence) is bound to the connection lifetime and never survives reconnect.
- **Zero key_id helper convention**: the built-in client helper always requests key_id zero (§3); apps needing non-zero client key_ids must hand-form AUTH v2.
- **Tokens not refunded**: admission tokens consumed by an admit that later fails connection creation are not returned (conservative direction, §5).
- **Full 1024 per-IP table**: denies new IPs; no eviction or LRU (§5).
- **Process-wide auth domain**: `break_session_set_auth` is process-global (no per-manager isolation) — apps needing parallel independent key domains must discriminate inside the callback user data.
- **PSK memset may be optimized out**: the stack PSK buffer is not explicitly zeroed with a barrier after verification (deferred minor from task 3 review).
- **clock_gettime failure not fail-closed**: a failing monotonic clock reads as time 0 for max_age purposes (deferred minor).

## 9. NOT delivered

- Server product / server authority (economy/inventory/damage/matchmaking remain design-target enumerations in threat model §3 — no server code exists).
- Per-device key provisioning tooling, rotation/revocation orchestration (§4).
- Client anti-tamper code: the anti-tamper position remains a **cost-model document** (threat model §2 — signals are at most a server-side risk input, never a trust basis); no implementation exists or is claimed.
- DTLS / QUIC; UDP is untouched by this phase.
- Session resumption, TLS shutdown/close_notify plumbing (§8).
- Remote debug channel, Lua remote session (still gated on a fuller security/transport contract).
- Replay protection beyond the handshake + per-connection sequence scope (§3).
- WAN/production validation of any kind (§7).

## 10. Evidence index

- Implementation: `engine/src/network/break_net_adapter.{h,c}` (TLS mode, admission rate limits, parser split, outbound monotonic sequence), `engine/src/network/break_session.{h,c}` (CHALLENGE/AUTH-v2, operation lease, max_age), `engine/src/network/break_net_message_registry.{h,c}` (CHALLENGE id 3, AUTH v1..2 under CRYPTO).
- Tests: `engine/tests/test_break_net_tls.c` (10), `test_break_net_adapter.c` (38), `test_break_session.c` (34) — all green on normal/ASan+UBSan/TSan trees, repeated ×3/×5 with zero sanitizer reports; full non-graphics suite 203 = 202 + 1 Windows-only skip on all three trees.
- Task evidence: `.superpowers/sdd/2026-10-24-stage5-transport-security/task-{1..5}-report.md` (RED-before-GREEN logs, review fix rounds, pin gate failure-path evidence).
- Pin/supply chain: Snowflake pinned at `d5d4a9287d81468506a3f1962dead16f72a3b5c1` with a configure-time fail-closed FATAL gate (`engine/CMakeLists.txt:295-383`, mirrored in `engine/external/locked_dependencies.json` and `docs/design/snowflake_c11_adapter.md`); OpenSSL-stub snow builds are rejected at configure time when `BREAK_ENABLE_CRYPTO=ON`.
- Sibling contracts: `docs/design/security_threat_model.md` §5/§7 (this phase is their delivered enforcement point), `docs/design/session_protocol.md` (session state machine and wire facts), `docs/design/snowflake_c11_adapter.md` (adapter lifecycle/queue contracts).
