#pragma once
/* ==========================================================================
 *  break_net_quic — QUIC transport channel for break_net, built entirely on
 *  Snowflake's pinned ngtcp2 adapter (snow/quic_ngtcp2.h): no QUIC, TLS, or
 *  congestion-control code lives here. Contract: docs/design/quic_transport.md.
 *
 *  Wire model (v1): one client-initiated bidirectional stream per connection
 *  carrying length-prefixed frames [u32be payload_len][payload], payload_len
 *  <= BREAK_NET_QUIC_MAX_MESSAGE. The stream is ordered and reliable, so
 *  frames need no sequence numbers.
 *
 *  Security (fail-closed, mirrors break_http's posture):
 *   - Client: trust_store_file + server_name are required; verification is
 *     not optional (the snow adapter hard-fails a missing trust store and
 *     verifies the certificate chain and host name).
 *   - Server: cert_file/key_file are required PEMs, loaded once at create.
 *   - ALPN is required on both sides (QUIC has no ALPN-less handshake).
 *
 *  Boundedness: fixed event queue (128) per endpoint, fixed slot table
 *  (max_connections) on the server, one 64 KiB reassembly buffer plus one
 *  64 KiB pending-tx buffer per live connection (allocated on accept/connect,
 *  freed on reclaim). A full event queue drops events and counts them; a
 *  full slot table drops new Initials and counts them; a connection whose
 *  single-message inbox is unread stops consuming stream credit (QUIC flow
 *  control backpressures the peer), and send refuses while a previous
 *  message is still draining (tx pending buffer busy).
 *
 *  Threading: single owner thread per endpoint; every API call and every
 *  adapter touch happens on the thread that calls step(). No locks.
 *
 *  POSIX only (sockets, poll); IPv4 only; mirrors the pinned adapter's
 *  accept contract. Windows/IPv6 are documented non-goals for v1.
 * ========================================================================== */

#include <core/types.h>
#include <network/break_net_envelope.h>
#include <network/break_net_message_registry.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_NET_QUIC_MAX_MESSAGE 65532u /* payload bytes; +4 frame header */
#define BREAK_NET_QUIC_MAX_PEM 65536u     /* cert/key/trust-store read bound */
#define BREAK_NET_QUIC_MAX_CONNECTIONS 64u
#define BREAK_NET_QUIC_EVENT_CAPACITY 128u

typedef struct BreakNetQuicClient BreakNetQuicClient;
typedef struct BreakNetQuicServer BreakNetQuicServer;
/* Server-side connection slot handle. Valid from its CONNECT event until the
 * matching DISCONNECT event is consumed; never dereference past that. */
typedef struct BreakNetQuicConn BreakNetQuicConn;

typedef enum BreakNetQuicEventType {
    BREAK_NET_QUIC_EVENT_NONE = 0,
    BREAK_NET_QUIC_EVENT_CONNECT,    /* server only: handshake completed */
    BREAK_NET_QUIC_EVENT_MESSAGE,    /* a full frame waits in the inbox */
    BREAK_NET_QUIC_EVENT_DISCONNECT, /* connection is terminal */
    BREAK_NET_QUIC_EVENT_AUTHENTICATED /* server only: AUTH v2 verified */
} BreakNetQuicEventType;

typedef enum BreakNetQuicDisconnectReason {
    BREAK_NET_QUIC_DISCONNECT_NONE = 0,
    BREAK_NET_QUIC_DISCONNECT_PEER = 1,       /* peer closed */
    BREAK_NET_QUIC_DISCONNECT_LOCAL = 2,      /* conn_close / client_close */
    BREAK_NET_QUIC_DISCONNECT_IDLE = 3,       /* idle timeout */
    BREAK_NET_QUIC_DISCONNECT_HANDSHAKE = 4,  /* handshake deadline / failure */
    BREAK_NET_QUIC_DISCONNECT_PROTOCOL = 5,   /* frame protocol violation */
    BREAK_NET_QUIC_DISCONNECT_AUTH = 6        /* auth timeout or bad AUTH */
} BreakNetQuicDisconnectReason;

typedef struct BreakNetQuicEvent {
    u8 type;    /* BreakNetQuicEventType */
    u8 reason;  /* BreakNetQuicDisconnectReason for DISCONNECT, else 0 */
    u16 _pad;
    u32 conn_id;
} BreakNetQuicEvent;

typedef struct BreakNetQuicServerConfig {
    const char *cert_file; /* PEM, required */
    const char *key_file;  /* PEM, required */
    const char *alpn;      /* required, e.g. "break/1" */
    u16 port;              /* 0 = ephemeral; query via _port() */
    u32 max_connections;   /* 0 = default 8; hard cap 64 */
    u32 handshake_timeout_ms; /* 0 = default 5000 */
    u32 max_idle_timeout_ms;  /* 0 = default 30000 */
} BreakNetQuicServerConfig;

typedef struct BreakNetQuicClientConfig {
    const char *host;             /* IPv4 literal, required */
    u16 port;                     /* required */
    const char *server_name;      /* SNI + certificate verify name, required */
    const char *trust_store_file; /* PEM CA bundle, required */
    const char *alpn;             /* required */
    /* Client certificate + key, required: the pinned snow adapter builds
     * every client with one (its TLS contract). The server's adapter surface
     * does not verify client certificates; peer identity stays app-level
     * (CHALLENGE/AUTH-v2 slice, see docs/design/quic_transport.md). */
    const char *cert_file;        /* PEM, required */
    const char *key_file;         /* PEM, required */
    u32 handshake_timeout_ms;     /* 0 = default 5000; enforced module-side
                                   * (the snow client config has no such
                                   * field) */
} BreakNetQuicClientConfig;

/* ---- server ------------------------------------------------------------- */

BreakNetQuicServer *break_net_quic_server_create(const BreakNetQuicServerConfig *cfg);
/* Bound port (resolved when port was 0). 0 on NULL. */
u16 break_net_quic_server_port(const BreakNetQuicServer *server);
/* Drives the endpoint: receives datagrams, feeds accepts/connections,
 * services timers, posts events. Waits at most timeout_ms (bounded by the
 * nearest connection deadline). Returns true when any work happened. */
bool break_net_quic_server_step(BreakNetQuicServer *server, u32 timeout_ms);
/* Dequeues the oldest event. Returns false when empty. */
bool break_net_quic_server_poll_event(BreakNetQuicServer *server,
                                      BreakNetQuicEvent *out);
/* Resolves a conn_id from a CONNECT/MESSAGE event to its slot handle.
 * NULL for stale/unknown ids. */
BreakNetQuicConn *break_net_quic_server_conn(BreakNetQuicServer *server,
                                             u32 conn_id);
/* Copies the inbox message out (cap-bounded) and reopens flow-control
 * credit. Returns false when the inbox is empty or cap is too small. */
bool break_net_quic_conn_read(BreakNetQuicServer *server, BreakNetQuicConn *conn,
                              u8 *out, u32 cap, u32 *out_len);
/* Queues one framed message on the connection's stream. Returns false while
 * a previous message is still draining or len exceeds the cap. */
bool break_net_quic_conn_send(BreakNetQuicServer *server, BreakNetQuicConn *conn,
                              const u8 *data, u32 len);
void break_net_quic_conn_close(BreakNetQuicServer *server, BreakNetQuicConn *conn);
/* Observability: unrouted/dropped datagrams and dropped events. */
u64 break_net_quic_server_dropped_datagrams(const BreakNetQuicServer *server);
u64 break_net_quic_server_events_overflow(const BreakNetQuicServer *server);
void break_net_quic_server_destroy(BreakNetQuicServer **server);

/* ---- client ------------------------------------------------------------- */

BreakNetQuicClient *break_net_quic_client_create(const BreakNetQuicClientConfig *cfg);
bool break_net_quic_client_step(BreakNetQuicClient *client, u32 timeout_ms);
bool break_net_quic_client_handshake_done(const BreakNetQuicClient *client);
/* Terminal without ever connecting (verification, ALPN, or transport
 * failure). */
bool break_net_quic_client_failed(const BreakNetQuicClient *client);
bool break_net_quic_client_send(BreakNetQuicClient *client, const u8 *data, u32 len);
bool break_net_quic_client_read(BreakNetQuicClient *client, u8 *out, u32 cap,
                                u32 *out_len);
bool break_net_quic_client_poll_event(BreakNetQuicClient *client,
                                      BreakNetQuicEvent *out);
void break_net_quic_client_close(BreakNetQuicClient *client);
void break_net_quic_client_destroy(BreakNetQuicClient **client);

/* ---- session layer: envelopes + CHALLENGE/AUTH-v2 over frames ----------- */

/* Envelope payloads ride frames: the 18-byte envelope header leaves this
 * much of the 64 KiB frame budget. Larger payloads are refused at send. */
#define BREAK_NET_QUIC_MAX_ENVELOPE_PAYLOAD \
    (BREAK_NET_QUIC_MAX_MESSAGE - BREAK_NET_ENVELOPE_HEADER_SIZE)

/* Same wire contract as the TCP transport (transport_security.md section 3):
 * CHALLENGE = id 3, v1, server_nonce[16]; AUTH v2 = id 1, v2, 56 bytes
 * key_id[8] || client_nonce[16] || HMAC-SHA256(psk, "BRKAUTH2" ||
 * server_nonce || client_nonce). Message ids come from
 * break_net_message_registry.h. */
typedef bool (*BreakNetQuicAuthKeyFn)(void *user, const u8 key_id[8],
                                      u8 out_psk[32]);

/* Server: require CHALLENGE/AUTH-v2 on every new connection, resolved through
 * fn (app-side key custody, per-server — unlike the TCP seam this is not
 * process-global). Call right after create, before the first step. A
 * connection that has not authenticated within auth_timeout_ms (0 = default
 * 10000) is closed with DISCONNECT_AUTH; while unauthenticated, anything
 * that is not a well-formed AUTH v2 closes the connection fail-closed.
 * Returns false on bad arguments or when called after traffic. */
bool break_net_quic_server_set_auth(BreakNetQuicServer *server,
                                    BreakNetQuicAuthKeyFn fn, void *user,
                                    u32 auth_timeout_ms);

/* Client: answer the pending CHALLENGE with AUTH v2. Consumes the challenge
 * from the inbox; false when no challenge is pending, the challenge is
 * malformed, or the CSPRNG/HMAC fails. Success means the AUTH was queued —
 * the server never confirms in v1; a failed AUTH closes the connection
 * (observable via DISCONNECT/AUTH). */
bool break_net_quic_client_authenticate(BreakNetQuicClient *client,
                                        const u8 key_id[8], const u8 psk[32]);

/* Envelope-level messaging. Outbound sequence is assigned per direction from
 * 1 (monotonic, saturating); inbound is checked strictly increasing, exactly
 * like the TCP adapter's decode_with_context. version is the envelope
 * protocol_version (1 for application messages; 2 is AUTH v2's). */
bool break_net_quic_conn_send_message(BreakNetQuicServer *server,
                                      BreakNetQuicConn *conn, u16 message_id,
                                      u16 version, u16 flags,
                                      const u8 *payload, u32 len);
bool break_net_quic_client_send_message(BreakNetQuicClient *client,
                                        u16 message_id, u16 version,
                                        u16 flags, const u8 *payload, u32 len);
/* Inbox read with envelope decode. Payload copies into out (cap-bounded).
 * False when the inbox is empty or cap is too small. */
bool break_net_quic_conn_recv_message(BreakNetQuicServer *server,
                                      BreakNetQuicConn *conn,
                                      u16 *out_message_id, u16 *out_version,
                                      u32 *out_sequence, u8 *out, u32 cap,
                                      u32 *out_len);
bool break_net_quic_client_recv_message(BreakNetQuicClient *client,
                                        u16 *out_message_id, u16 *out_version,
                                        u32 *out_sequence, u8 *out, u32 cap,
                                        u32 *out_len);

#ifdef __cplusplus
} /* extern "C" */
#endif
