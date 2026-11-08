# QUIC Transport — break_net_quic over Snowflake ngtcp2 adapter

Status: **delivered as a library seam with loopback evidence** (v1, 2026-11-08; Snowflake pin `5fab267e`).
This document is the contract record for the first QUIC slice. It is honest
about what exists: a client/server channel module driven by the caller's
thread, exercised over real UDP loopback — not a reactor-integrated transport,
and not a deployed service. See §8 (limitations) and §9 (NOT delivered).

## 1. Decision: consume Snowflake's QUIC, never reimplement it

All QUIC protocol work — handshake, TLS 1.3 key schedule, streams, flow
control, congestion control, loss recovery, connection IDs — lives in
Snowflake's ngtcp2 adapter (`snow_quic_ngtcp2_adapter`,
`include/snow/quic_ngtcp2.h`, pinned tree `0fceed6d`), which is ngtcp2 v1.25.0
(vendored byte-exact, `third_party/NGTCP2_PROVENANCE.txt`) over OpenSSL's QUIC
TLS seam (`SSL_set_quic_tls_cbs`, requires OpenSSL ≥ 3.5). Break adds **no**
QUIC, TLS, or congestion-control code of its own; `break_net_quic` is a thin
ownership/framing layer that:

1. owns the POSIX UDP sockets (the only network code Break writes — datagram
   plumbing, not protocol);
2. owns the connection slot table and source-address demux on the server
   (mirrors the documented first-cut semantics of Snowflake's
   `snow_quic_udp_server_t` listener, see §6);
3. frames application messages onto one QUIC bidirectional stream per
   connection (§3);
4. enforces Break's boundedness and fail-closed rules (§4, §5).

Why not OpenSSL 4.x's own QUIC stack (`SSL_new_listener` etc.): the pinned
Snowflake tree already ships a vetted, tested adapter with Break-relevant
hardening (Retry policy, stateless reset, handshake deadlines, per-address
accept limits, conn stats). Writing a second QUIC integration against raw
OpenSSL would duplicate that work and diverge from the pinned dependency
contract. The engine's OpenSSL 4.x capability probe (loopback QUICv1 echo,
2026-11-08) confirmed the TLS seam both stacks share; Snowflake's adapter is
the one consumed.

## 2. Architecture

```text
app (game client/server)
   │  break_net_quic.h — create / step / send / poll_message / close
   ▼
break_net_quic (engine/src/network/break_net_quic.c)
   │  owns: UDP socket (POSIX), slot table, frame reassembly, deadlines
   ▼
snow_quic_ngtcp2_adapter (pinned snow 0fceed6d)
   │  snow_quic_ngtcp2_init (client) / snow_quic_ngtcp2_accept (server)
   │  input_path / service / open_bidi_stream / send_stream / callbacks
   ▼
ngtcp2 v1.25.0 + ngtcp2_crypto_ossl (vendored in snow third_party/)
   ▼
OpenSSL ≥ 3.5 QUIC TLS seam (SSL_set_quic_tls_cbs; local evidence on 4.0.3)
```

Threading: single owner thread per endpoint. Every adapter touch
(init/accept/input/service/send/destroy) happens inside `*_step` or the
module's own API called from that thread — same discipline as the break_net
reactor contract (transport_security.md §2). No locks; the API documents the
owner-thread rule.

Drive model: caller-pumped `step(endpoint, timeout_ms)`. Each step polls the
UDP socket up to the nearest of (caller timeout, next ngtcp2 service
deadline), feeds received datagrams, services connections, and flushes
outbound datagrams through the adapter's output callback. Tests use real UDP
loopback with port-0 binds and condition polling; zero fixed sleeps.

## 3. Wire model

One client-initiated bidirectional stream per connection carries all
application traffic for v1. Messages are length-prefixed frames:

```text
[u32be payload_len][payload bytes]   payload_len <= 64 KiB - 4
```

- The stream is ordered and reliable (QUIC), so frames need no sequence
  numbers; reassembly is a per-connection bounded buffer.
- A frame header claiming more than the cap is a protocol error: the
  connection is closed (fail-closed), counted, and no partial message is
  delivered.
- Message semantics (request/response, broadcast, reliability classes) are
  application-side. Mapping break_net envelopes (`break_net_envelope`) onto
  frames is the documented next slice, not v1 (§9).

Why not QUIC datagrams (RFC 9221): the pinned ngtcp2 adapter v1 surface is
stream-oriented; datagram support lands with the replay-window wiring
(transport_security.md §3, 2026-10-30 decision reserves `break_replay_window`
for exactly that datagram path).

## 4. Security model

Client side (fail-closed, mirrors break_http's posture):

- `trust_store_file` is **required**; the snow adapter sets
  `SSL_VERIFY_PEER` and refuses a missing/empty trust store
  (`snow_quic_ngtcp2.c` init gate). There is no insecure mode.
- `server_name` is required and used for SNI + certificate hostname
  verification. A name mismatch fails the handshake.
- `alpn` is required (QUIC has no ALPN-less handshake). The module's config
  carries a plain C string; the module converts it to wire format
  (length-prefixed, what `SSL_set_alpn_protos` and the adapter expect).
  Since Snowflake `5fab267e` the adapter's ALPN selector answers no-match
  with `SSL_TLSEXT_ERR_ALERT_FATAL` (RFC 9001 section 7 — QUIC mandates
  ALPN; the earlier NOACK let a mismatched handshake complete), so a
  client offering a disjoint ALPN fails closed. The client additionally
  enforces a module-side handshake deadline (`handshake_timeout_ms`,
  default 5 s; the snow client config has no such field) so a silently
  dropped or refused handshake can never hang the caller.
- `cert_file`/`key_file` are **required on the client too**: the pinned
  adapter's client init gates on a certificate and key (its TLS contract).
  The server side does not verify client certificates (no trust-store
  field in the pinned adapter's server config), so peer identity stays
  app-level (see the server side below).

Server side:

- `cert_file`/`key_file` are required PEMs, loaded once at create (bounded
  read, ≤ 64 KiB each); a missing/mismatched pair fails create.
- Client authentication at the TLS layer is **not** provided by the pinned
  adapter's server config (no trust-store field); application-level peer
  authentication therefore remains the CHALLENGE/AUTH-v2 seam
  (transport_security.md §3). Wiring it onto QUIC frames is a next slice (§9).
- v1 does not configure the adapter's Retry policy (`retry_secret`): a
  tokenless Initial costs the server handshake state. This is a documented
  DoS surface for Internet-facing use (§8); the adapter supports the policy
  and enabling it is a config-only follow-up.

## 5. Boundedness ledger

| Resource | Bound | Enforcement |
|---|---|---|
| Server connection slots | `max_connections` (1..64), fixed table | full → new Initials dropped + counted |
| Frame payload | ≤ 65532 B | header over cap → connection closed |
| Reassembly buffer | 64 KiB per connection | fixed allocation per slot |
| PEM inputs | ≤ 64 KiB per file, read once at create | create fails otherwise |
| Inbound message queue | 256 messages per connection | full → drop + count (OVERLOAD) |
| Step wait | min(caller timeout, ngtcp2 deadline) | poll(2) with computed deadline |
| Handshake | `handshake_timeout_ms` (default 5 s) | adapter deadline → terminal |
| Idle | `max_idle_timeout_ms` (default 30 s) | adapter transport parameter |
| Test synchronization | port-0 + condition polling, no fixed sleeps | all tests |

## 6. Relationship to Snowflake's udp_engine listener

Snowflake ships a fuller server path — `snow_quic_udp_server_t` over
`snow_udp_engine` — with CID-based routing, Retry budgets, stateless reset,
and slot reclamation. It requires the caller to inject a complete poller/IO
vtable (poller_create/add/wait, recv/send hooks; udp_engine ABI v15). v1 does
not consume it because break_net_quic's step model needs exactly one socket
per endpoint and no second event system next to the engine's own loops; the
v1 demux mirrors the listener's documented first-cut semantics (source-address
key, IPv4) including its known limitation (a client reboot reusing a port
collides with its old slot until idle/close reclaims it). Migrating the server
side onto `snow_quic_udp_server_t` is the planned hardening slice and is a
module-internal change — the public API (§7) is unaffected.

## 7. Public interface (v1)

```c
typedef struct BreakNetQuicClient BreakNetQuicClient;
typedef struct BreakNetQuicServer BreakNetQuicServer;
typedef struct BreakNetQuicConn BreakNetQuicConn; /* server-side slot handle */

typedef struct BreakNetQuicClientConfig {
    const char *host;             /* IPv4 literal, required */
    u16 port;                     /* required */
    const char *server_name;      /* SNI + cert verify name, required */
    const char *trust_store_file; /* PEM CA bundle, required */
    const char *alpn;             /* required (plain string; the module
                                   * converts to wire format) */
    const char *cert_file;        /* PEM, required (adapter TLS contract) */
    const char *key_file;         /* PEM, required */
    u32 handshake_timeout_ms;     /* 0 = default 5000, module-enforced */
} BreakNetQuicClientConfig;

typedef struct BreakNetQuicServerConfig {
    const char *cert_file;        /* PEM, required */
    const char *key_file;         /* PEM, required */
    const char *alpn;             /* required */
    u16 port;                     /* 0 = ephemeral; query via _port() */
    u32 max_connections;          /* 1..64 */
    u32 handshake_timeout_ms;     /* 0 = 5000 */
    u32 max_idle_timeout_ms;      /* 0 = 30000 */
} BreakNetQuicServerConfig;
```

Client: `create` / `step` / `handshake_done` / `failed` / `send` /
`poll_message` / `close` / `destroy`.
Server: `create` / `port` / `step` / `next_event` (CONNECT / MESSAGE /
DISCONNECT queue) / `conn_send` / `conn_close` / counters / `destroy`.
Events are dequeued by the owner thread; MESSAGE payloads are copied into the
caller buffer with the 64 KiB cap. Full contract in
`engine/src/network/break_net_quic.h`; the C++20 RAII wrapper
(`engine/src/network/break_net_quic.hpp`, namespace `breakxx::quic`) ships in
the same commit and is exercised by `test_break_net_quic_cpp20` through the
same loopback echo (dual-language policy, Build_Guide §1.1).

## 8. Documented limitations

- **POSIX only** (sockets, poll). Windows is not implemented (mirrors
  break_http's v1 posture).
- **IPv4 only**, matching the pinned adapter's accept contract.
- **No mTLS at the QUIC/TLS layer** (§4): use CHALLENGE/AUTH-v2 on top.
- **No Retry/address validation in v1** (§4): Internet-facing deployments must
  enable the adapter's retry policy first.
- **Source-address demux** (§6): client reboot with a reused port collides
  until the old slot is reclaimed; CID routing comes with the listener slice.
- **No 0-RTT / session resumption** wired (adapter supports it via
  `snow_quic_ngtcp2_server_tls_t`; v1 uses per-connection contexts).
- **No connection migration** surfaced to the app.
- Loopback evidence only: no WAN/loss/jitter validation.

## 9. NOT delivered

- break_net envelope/session mapping onto QUIC frames (next slice: envelopes
  ride §3 frames; CHALLENGE/AUTH-v2 runs as the first framed exchange).
- `snow_quic_udp_server_t` listener migration (§6), Retry policy wiring,
  stateless reset secrets.
- QUIC datagrams + `break_replay_window` wiring (§3).
- Reactor integration (THREAD mode) with the TCP break_net reactor.
- 0-RTT resumption, migration, multi-stream APIs, per-stream prioritization.
- Windows support, IPv6.

## 10. Build gate

`BREAK_ENABLE_QUIC` (default **OFF**, opt-in) requires
`BREAK_ENABLE_SNOWFLAKE=ON` + `BREAK_ENABLE_CRYPTO=ON` and an OpenSSL ≥ 3.5
with the QUIC TLS seam. When ON, the snow block sets
`SNOW_USE_VENDORED_NGTCP2` / `SNOW_ENABLE_QUIC_NGTCP2` /
`SNOW_ENABLE_TRANSPORT_MANAGER` before `add_subdirectory` and fail-closes
unless `snow_quic_ngtcp2_adapter` exists afterwards. macOS note: the system
LibreSSL is not linkable and brew openssl is not in the default prefix — pass
`-DOPENSSL_ROOT_DIR=<openssl>=3.5 prefix` (local evidence:
self-built OpenSSL 4.0.3). CI lanes on OpenSSL 3.0 keep the default OFF; the
gate, not the environment, decides.

```bash
cmake -S engine -B build-quic -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=<pinned snow checkout> -DBREAK_ENABLE_QUIC=ON \
  -DOPENSSL_ROOT_DIR=<openssl-3.5+ prefix>
ctest --test-dir build-quic -R break_net_quic --output-on-failure
```

## 11. Evidence index

- Implementation: `engine/src/network/break_net_quic.{h,c}`.
- Tests: `engine/tests/test_break_net_quic.c` 8/8 — config validation
  matrix, handshake + framed echo round trip, sequential-message ordering,
  cap boundary (65532 accepted / 65533 refused at the API), wrong-ALPN and
  wrong-server-name fail-closed, slot-table-full rejection with drop
  counter, graceful close events on both sides. Plus
  `test_break_net_quic_cpp20` (same echo through the C++20 wrapper).
  All over real UDP loopback, port-0 binds, deadline-bounded condition
  polling; 5/5 repeated runs green; the full non-graphics suite reads
  281/281 with the suite included.
- Fixtures: `engine/tests/fixtures/ssl/` (CN=localhost, 2020–2049), same
  trust model as break_http's tests (transport_security.md §7).
- Snowflake pin: moved to `5fab267e` in the same change (the pin tracks
  snowflake main per policy; this move also carried the Google-style API
  rename migration and the ALPN fail-closed fix upstream).
- Environment evidence: macOS arm64 + OpenSSL 4.0.3 (self-built,
  `-DOPENSSL_ROOT_DIR`), QUICv1 / TLS_AES_256_GCM_SHA384 loopback verified
  via raw OpenSSL 4.x API (2026-11-08 smoke) and via the snow adapter
  (this module's tests). Snow's own QUIC suite: 13/13 with the ALPN fix.
