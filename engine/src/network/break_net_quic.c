/* break_net_quic — QUIC transport channel over Snowflake's pinned ngtcp2
 * adapter. Contract: docs/design/quic_transport.md. Every QUIC/TLS/loss
 * recovery decision lives in the adapter; this file owns sockets, the slot
 * table, frame reassembly, and the event queue. Single owner thread. */

#include "network/break_net_quic.h"

#include "crypto/break_crypto.h"

#include <snow/quic_ngtcp2.h>

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BNQ_FRAME_CAP (BREAK_NET_QUIC_MAX_MESSAGE + 4u)
#define BNQ_RECV_BUDGET_PER_STEP 64u
#define BNQ_DEFAULT_MAX_CONNECTIONS 8u
#define BNQ_DEFAULT_HANDSHAKE_MS 5000u
#define BNQ_DEFAULT_IDLE_MS 30000u

/* ------------------------------------------------------------------ events */

typedef struct {
    BreakNetQuicEvent entries[BREAK_NET_QUIC_EVENT_CAPACITY];
    u32 head, count;
    u64 overflow;
} BnqEventQueue;

static void bnq_event_post(BnqEventQueue *q, u8 type, u8 reason, u32 conn_id) {
    if (q->count == BREAK_NET_QUIC_EVENT_CAPACITY) {
        q->overflow++;
        return;
    }
    u32 tail = (q->head + q->count) % BREAK_NET_QUIC_EVENT_CAPACITY;
    q->entries[tail].type = type;
    q->entries[tail].reason = reason;
    q->entries[tail]._pad = 0u;
    q->entries[tail].conn_id = conn_id;
    q->count++;
}

static bool bnq_event_take(BnqEventQueue *q, BreakNetQuicEvent *out) {
    if (q->count == 0u) {
        return false;
    }
    *out = q->entries[q->head];
    q->head = (q->head + 1u) % BREAK_NET_QUIC_EVENT_CAPACITY;
    q->count--;
    return true;
}

/* -------------------------------------------------------------- connection */

struct BreakNetQuicConn {
    SnowQuicNgtcp2 *adapter;
    int fd; /* borrowed from the endpoint */
    SnowTransportDatagramAddress local;
    SnowTransportDatagramAddress remote;
    int64_t stream_id; /* -1 until the client-opened stream is known */
    u32 conn_id;
    bool connected_socket; /* client: fd is connect()ed, use send() */
    u64 rx_stream_offset; /* next expected stream offset */

    u8 *rx; /* FRAME_CAP bytes: reassembly + single-message inbox */
    u32 rx_len;
    u32 rx_msg_len; /* payload bytes of the ready message (rx[0..len)) */
    bool rx_msg_ready;

    u8 *tx; /* FRAME_CAP bytes: one frame draining */
    u32 tx_len, tx_off;

    bool handshake_done;
    bool connect_posted; /* CONNECT event issued for this slot */
    bool close_reported; /* adapter terminal, DISCONNECT not yet consumed */
    u8 close_reason;

    /* The pinned adapter refuses sends on streams it has never seen
     * (SnowQuicNgtcp2SendStreamEx returns SNOW_ERR_PROTO), so a server cannot
     * speak first: the module client emits a frame-level READY marker
     * (length word 0xFFFFFFFF, no payload, never reaches the app) the moment
     * its stream opens, and the server learns the stream from that first
     * inbound data. stream_ready gates every send. */
    bool stream_ready;
    bool ready_sent;

    /* session layer: envelope sequences per direction + auth state */
    u32 tx_seq; /* next outbound envelope sequence (from 1, saturating) */
    BreakNetEnvelopeContext rx_ctx; /* inbound strict-sequence check */
    u8 auth_state; /* 0 = none/open, 1 = challenged, 2 = authenticated */
    u8 server_nonce[16];
    u64 auth_deadline_ns;
    bool rx_msg_event_posted; /* MESSAGE event issued for the ready inbox */

    struct BreakNetQuicServer *server; /* back-pointer (server side) */
};

static u64 bnq_now_ns(void *unused) {
    struct timespec ts;
    (void)unused;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * UINT64_C(1000000000) + (u64)ts.tv_nsec;
}

/* The snow adapter takes ALPN in wire format (length-prefixed, matching
 * SSL_set_alpn_protos); the module's public config carries a plain C string
 * (1..32 chars). Returns the wire size (1 + len), 0 on invalid input. */
static u32 bnq_alpn_wire(const char *alpn, u8 *out, u32 cap) {
    size_t len;
    if (alpn == NULL || alpn[0] == '\0') {
        return 0u;
    }
    len = strlen(alpn);
    if (len > 32u || 1u + len > cap) {
        return 0u;
    }
    out[0] = (u8)len;
    memcpy(out + 1u, alpn, len);
    return (u32)(1u + len);
}

static SnowStatus bnq_output(const uint8_t *data, size_t len, void *userdata) {
    /* One datagram per call, len <= SNOW_QUIC_NGTCP2_MAX_PACKET. A full UDP
     * buffer is retried once after a 1 ms writable wait, then dropped and
     * counted nowhere visible to QUIC (the adapter retransmits by its own
     * loss recovery — that is the point of running it). */
    BreakNetQuicConn *conn = (BreakNetQuicConn *)userdata;
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(conn->remote.port);
    memcpy(&sa.sin_addr, conn->remote.address, 4u);
    /* A connect()ed UDP socket rejects sendto-with-address (EISCONN on
     * macOS): clients send() on the connected socket, servers sendto() the
     * observed remote. */
    ssize_t n;
    if (conn->connected_socket) {
        n = send(conn->fd, data, len, 0);
    } else {
        n = sendto(conn->fd, data, len, 0, (const struct sockaddr *)&sa,
                   sizeof(sa));
    }
    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        struct pollfd pfd;
        pfd.fd = conn->fd;
        pfd.events = POLLOUT;
        pfd.revents = 0;
        if (poll(&pfd, 1u, 1) > 0) {
            n = conn->connected_socket
                    ? send(conn->fd, data, len, 0)
                    : sendto(conn->fd, data, len, 0,
                             (const struct sockaddr *)&sa, sizeof(sa));
        }
    }
    return (n == (ssize_t)len) ? SNOW_OK : SNOW_ERR_IO;
}

static SnowStatus bnq_handshake_done(void *userdata) {
    BreakNetQuicConn *conn = (BreakNetQuicConn *)userdata;
    conn->handshake_done = true;
    return SNOW_OK;
}

static SnowStatus bnq_recv_stream(int64_t stream_id, u32 flags, u64 offset,
                                  const uint8_t *data, size_t len,
                                  void *userdata) {
    (void)flags;
    BreakNetQuicConn *conn = (BreakNetQuicConn *)userdata;
    conn->stream_ready = true; /* inbound data materialized the stream */
    if (conn->stream_id < 0) {
        conn->stream_id = stream_id; /* client-opened stream, learned here */
    }
    if (stream_id != conn->stream_id || offset != conn->rx_stream_offset) {
        return SNOW_ERR_PROTO; /* one stream, strictly in order */
    }
    if (len > BNQ_FRAME_CAP || conn->rx_len + (u32)len > BNQ_FRAME_CAP) {
        return SNOW_ERR_PROTO; /* peer overran the flow-control window */
    }
    memcpy(conn->rx + conn->rx_len, data, len);
    conn->rx_len += (u32)len;
    conn->rx_stream_offset += len;
    return SNOW_OK;
}

/* Extract complete frames; stop when the inbox is occupied (flow-control
 * credit is only returned on app read, so a conforming peer cannot overrun). */
/* Fills the single-message inbox; event posting is the caller's decision
 * (the server's auth gate consumes AUTH envelopes without app events). */
static void bnq_extract(BreakNetQuicConn *conn) {
    for (;;) {
        if (conn->rx_msg_ready || conn->rx_len < 4u) {
            return;
        }
        u32 len = ((u32)conn->rx[0] << 24) | ((u32)conn->rx[1] << 16) |
                  ((u32)conn->rx[2] << 8) | (u32)conn->rx[3];
        if (len == UINT32_MAX) {
            /* READY marker: consume and keep extracting (a real frame may
             * follow in the same burst). Credit is consumed on read — but
             * markers are 4 header bytes with no payload, consumed here. */
            u32 rest = conn->rx_len - 4u;
            memmove(conn->rx, conn->rx + 4u, rest);
            conn->rx_len = rest;
            SnowQuicNgtcp2ConsumeStream(conn->adapter, conn->stream_id, 4u,
                                        bnq_now_ns(NULL));
            continue;
        }
        if (len > BREAK_NET_QUIC_MAX_MESSAGE) {
            conn->close_reason = BREAK_NET_QUIC_DISCONNECT_PROTOCOL;
            SnowQuicNgtcp2Close(conn->adapter);
            return;
        }
        if (conn->rx_len < 4u + len) {
            return;
        }
        conn->rx_msg_len = len;
        conn->rx_msg_ready = true;
        return;
    }
}

static bool bnq_conn_read(BreakNetQuicConn *conn, u8 *out, u32 cap,
                          u32 *out_len) {
    if (!conn->rx_msg_ready || cap < conn->rx_msg_len) {
        return false;
    }
    memcpy(out, conn->rx + 4u, conn->rx_msg_len);
    if (out_len != NULL) {
        *out_len = conn->rx_msg_len;
    }
    /* Consume the frame's credit and shift any residual reassembly down. */
    u32 frame = 4u + conn->rx_msg_len;
    u32 rest = conn->rx_len - frame;
    memmove(conn->rx, conn->rx + frame, rest);
    conn->rx_len = rest;
    conn->rx_msg_ready = false;
    conn->rx_msg_len = 0u;
    conn->rx_msg_event_posted = false;
    SnowQuicNgtcp2ConsumeStream(conn->adapter, conn->stream_id, frame,
                                bnq_now_ns(NULL));
    return true;
}

static bool bnq_conn_send(BreakNetQuicConn *conn, const u8 *data, u32 len) {
    if (conn->tx_off < conn->tx_len || len > BREAK_NET_QUIC_MAX_MESSAGE ||
        (len > 0u && data == NULL)) {
        return false; /* busy draining or over cap */
    }
    conn->tx[0] = (u8)(len >> 24);
    conn->tx[1] = (u8)(len >> 16);
    conn->tx[2] = (u8)(len >> 8);
    conn->tx[3] = (u8)len;
    if (len > 0u) {
        memcpy(conn->tx + 4u, data, len);
    }
    conn->tx_off = 0u;
    conn->tx_len = 4u + len;
    return true;
}

static void bnq_conn_drain_tx(BreakNetQuicConn *conn) {
    while (conn->tx_off < conn->tx_len && conn->stream_id >= 0 &&
           conn->handshake_done && conn->stream_ready) {
        size_t accepted = 0u;
        SnowStatus st = SnowQuicNgtcp2SendStreamEx(
            conn->adapter, conn->stream_id, conn->tx + conn->tx_off,
            conn->tx_len - conn->tx_off, 0, bnq_now_ns(NULL), &accepted);
        if (st != SNOW_OK || accepted == 0u) {
            return; /* flow-controlled; retry next step */
        }
        conn->tx_off += (u32)accepted;
    }
}

/* Encodes one envelope (sequence auto-assigned from 1, saturating) and
 * queues it as a frame. False on oversize payload or busy tx buffer. */
static bool bnq_conn_send_message(BreakNetQuicConn *conn, u16 message_id,
                                  u16 version, u16 flags, const u8 *payload,
                                  u32 len) {
    if (len > BREAK_NET_QUIC_MAX_ENVELOPE_PAYLOAD ||
        (len > 0u && payload == NULL)) {
        return false;
    }
    /* Encode straight into the tx pending buffer after the 4-byte frame
     * length: one buffer, zero extra copies. */
    if (conn->tx_off < conn->tx_len) {
        return false; /* previous frame still draining */
    }
    u32 seq = conn->tx_seq;
    if (conn->tx_seq < UINT32_MAX) {
        conn->tx_seq++;
    }
    BreakNetEnvelope env;
    env.protocol_version = version;
    env.message_id = message_id;
    env.flags = flags;
    env.sequence = seq;
    env.payload = payload;
    env.payload_size = len;
    size_t encoded = 0u;
    if (break_net_envelope_encode(&env, conn->tx + 4u,
                                  BREAK_NET_QUIC_MAX_MESSAGE, &encoded) !=
            BREAK_NET_ENVELOPE_OK ||
        encoded > BREAK_NET_QUIC_MAX_MESSAGE) {
        return false;
    }
    u32 total = (u32)encoded;
    conn->tx[0] = (u8)(total >> 24);
    conn->tx[1] = (u8)(total >> 16);
    conn->tx[2] = (u8)(total >> 8);
    conn->tx[3] = (u8)total;
    conn->tx_off = 0u;
    conn->tx_len = 4u + total;
    return true;
}

/* Reads the inbox as an envelope with the strict inbound sequence check. */
static bool bnq_conn_recv_message(BreakNetQuicConn *conn, u16 *out_id,
                                  u16 *out_version, u32 *out_seq, u8 *out,
                                  u32 cap, u32 *out_len) {
    if (!conn->rx_msg_ready) {
        return false;
    }
    BreakNetEnvelope env;
    if (break_net_envelope_decode_with_context(&conn->rx_ctx, conn->rx + 4u,
                                               conn->rx_msg_len, &env) !=
        BREAK_NET_ENVELOPE_OK) {
        conn->close_reason = BREAK_NET_QUIC_DISCONNECT_PROTOCOL;
        SnowQuicNgtcp2Close(conn->adapter);
        return false;
    }
    if (env.payload_size > cap) {
        return false;
    }
    if (env.payload_size > 0u) {
        memcpy(out, env.payload, env.payload_size);
    }
    if (out_id != NULL) {
        *out_id = env.message_id;
    }
    if (out_version != NULL) {
        *out_version = env.protocol_version;
    }
    if (out_seq != NULL) {
        *out_seq = env.sequence;
    }
    if (out_len != NULL) {
        *out_len = (u32)env.payload_size;
    }
    /* consume the frame exactly like a raw read */
    u32 frame = 4u + conn->rx_msg_len;
    u32 rest = conn->rx_len - frame;
    memmove(conn->rx, conn->rx + frame, rest);
    conn->rx_len = rest;
    conn->rx_msg_ready = false;
    conn->rx_msg_len = 0u;
    conn->rx_msg_event_posted = false;
    SnowQuicNgtcp2ConsumeStream(conn->adapter, conn->stream_id, frame,
                                bnq_now_ns(NULL));
    return true;
}

static void bnq_conn_free(BreakNetQuicConn *conn) {
    if (conn == NULL) {
        return;
    }
    if (conn->adapter != NULL) {
        SnowQuicNgtcp2Destroy(&conn->adapter);
    }
    free(conn->rx);
    free(conn->tx);
    free(conn);
}

/* ------------------------------------------------------------------ server */

struct BreakNetQuicServer {
    int fd;
    u16 port;
    u32 max_connections;
    u64 handshake_timeout_ns;
    u64 max_idle_timeout_ns;
    u8 alpn_wire[34]; /* length-prefixed wire format */
    u32 alpn_wire_len;

    u8 *cert_pem;
    size_t cert_pem_len;
    u8 *key_pem;
    size_t key_pem_len;

    BreakNetQuicConn **slots; /* max_connections entries, calloc'd */
    u32 next_conn_id;
    u64 dropped;
    BnqEventQueue events;

    BreakNetQuicAuthKeyFn auth_fn; /* NULL = open connections (v1 default) */
    void *auth_user;
    u64 auth_timeout_ns;
    u32 accepted_count; /* set_auth is only legal before the first accept */
};

/* ------------------------------------------------------------------ client */

struct BreakNetQuicClient {
    int fd;
    BreakNetQuicConn *conn; /* single connection */
    BnqEventQueue events;
    bool failed;
    u64 created_ns; /* handshake deadline origin */
    u64 handshake_timeout_ns; /* module-enforced (the snow client config has
                               * no such field); default 5 s like the server */
};

/* ------------------------------------------------------------------- peers */

static int bnq_socket_nonblock(void) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return -1;
    }
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) != 0) {
        close(fd);
        return -1;
    }
    return fd;
}

static SnowTransportDatagramAddress bnq_addr_from(const struct sockaddr_in *sa) {
    SnowTransportDatagramAddress a;
    memset(&a, 0, sizeof(a));
    a.family = kSnowTransportDatagramAddressIpv4;
    a.port = ntohs(sa->sin_port);
    memcpy(a.address, &sa->sin_addr, 4u);
    return a;
}

static bool bnq_addr_equal(const SnowTransportDatagramAddress *a,
                           const SnowTransportDatagramAddress *b) {
    return a->family == b->family && a->port == b->port &&
           memcmp(a->address, b->address, 4u) == 0;
}

/* Reads a PEM file once, bounded. Returns NULL on any failure. */
static u8 *bnq_read_pem(const char *path, size_t *out_len) {
    if (path == NULL) {
        return NULL;
    }
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        return NULL;
    }
    u8 *buf = (u8 *)malloc(BREAK_NET_QUIC_MAX_PEM + 1u);
    if (buf == NULL) {
        fclose(f);
        return NULL;
    }
    size_t n = fread(buf, 1u, BREAK_NET_QUIC_MAX_PEM, f);
    int read_err = ferror(f);
    int extra = fgetc(f); /* EOF expected exactly at the bound */
    fclose(f);
    if (read_err != 0 || n == 0u || extra != EOF) {
        free(buf);
        return NULL;
    }
    *out_len = n;
    return buf;
}

static void bnq_fill_client_adapter_config(SnowQuicNgtcp2Config *cfg,
                                           BreakNetQuicConn *conn,
                                           const char *server_name,
                                           const u8 *trust, size_t trust_len,
                                           const u8 *alpn, u32 alpn_len) {
    memset(cfg, 0, sizeof(*cfg));
    cfg->output = bnq_output;
    cfg->output_userdata = conn;
    cfg->clock = bnq_now_ns;
    cfg->clock_userdata = NULL;
    cfg->server_name = server_name;
    cfg->trust_store_pem = trust;
    cfg->trust_store_pem_size = trust_len;
    cfg->alpn = alpn;
    cfg->alpn_size = alpn_len;
    cfg->local_address = conn->local;
    cfg->remote_address = conn->remote;
    cfg->handshake_completed = bnq_handshake_done;
    cfg->recv_stream_data = bnq_recv_stream;
    cfg->event_userdata = conn;
}

/* ------------------------------------------------------------------ server */

BreakNetQuicServer *break_net_quic_server_create(
    const BreakNetQuicServerConfig *cfg) {
    if (cfg == NULL || cfg->cert_file == NULL || cfg->key_file == NULL ||
        cfg->max_connections > BREAK_NET_QUIC_MAX_CONNECTIONS) {
        return NULL;
    }
    BreakNetQuicServer *s = (BreakNetQuicServer *)calloc(1u, sizeof(*s));
    if (s == NULL) {
        return NULL;
    }
    s->fd = -1;
    s->max_connections = cfg->max_connections != 0u
                             ? cfg->max_connections
                             : BNQ_DEFAULT_MAX_CONNECTIONS;
    s->handshake_timeout_ns =
        (u64)(cfg->handshake_timeout_ms != 0u ? cfg->handshake_timeout_ms
                                              : BNQ_DEFAULT_HANDSHAKE_MS) *
        UINT64_C(1000000);
    s->max_idle_timeout_ns =
        (u64)(cfg->max_idle_timeout_ms != 0u ? cfg->max_idle_timeout_ms
                                             : BNQ_DEFAULT_IDLE_MS) *
        UINT64_C(1000000);
    s->alpn_wire_len = bnq_alpn_wire(cfg->alpn, s->alpn_wire,
                                     sizeof(s->alpn_wire));
    if (s->alpn_wire_len == 0u) {
        break_net_quic_server_destroy(&s);
        return NULL;
    }
    s->next_conn_id = 1u;

    s->slots = (BreakNetQuicConn **)calloc(s->max_connections,
                                           sizeof(BreakNetQuicConn *));
    s->cert_pem = bnq_read_pem(cfg->cert_file, &s->cert_pem_len);
    s->key_pem = bnq_read_pem(cfg->key_file, &s->key_pem_len);
    if (s->slots == NULL || s->cert_pem == NULL || s->key_pem == NULL) {
        break_net_quic_server_destroy(&s);
        return NULL;
    }

    s->fd = bnq_socket_nonblock();
    if (s->fd < 0) {
        break_net_quic_server_destroy(&s);
        return NULL;
    }
    int one = 1;
    setsockopt(s->fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sa.sin_port = htons(cfg->port);
    if (bind(s->fd, (const struct sockaddr *)&sa, sizeof(sa)) != 0) {
        break_net_quic_server_destroy(&s);
        return NULL;
    }
    socklen_t sl = sizeof(sa);
    if (getsockname(s->fd, (struct sockaddr *)&sa, &sl) != 0) {
        break_net_quic_server_destroy(&s);
        return NULL;
    }
    s->port = ntohs(sa.sin_port);
    return s;
}

u16 break_net_quic_server_port(const BreakNetQuicServer *server) {
    return server != NULL ? server->port : 0u;
}

static void bnq_server_reclaim(BreakNetQuicServer *s, u32 index) {
    BreakNetQuicConn *conn = s->slots[index];
    if (conn == NULL) {
        return;
    }
    u8 reason = conn->close_reason;
    if (reason == BREAK_NET_QUIC_DISCONNECT_NONE) {
        if (!conn->handshake_done) {
            reason = BREAK_NET_QUIC_DISCONNECT_HANDSHAKE;
        } else if (SnowQuicNgtcp2IsLocallyClosed(conn->adapter)) {
            reason = BREAK_NET_QUIC_DISCONNECT_LOCAL;
        } else {
            reason = BREAK_NET_QUIC_DISCONNECT_PEER;
        }
    }
    bnq_event_post(&s->events, BREAK_NET_QUIC_EVENT_DISCONNECT, reason,
                   conn->conn_id);
    bnq_conn_free(conn);
    s->slots[index] = NULL;
}

static void bnq_server_accept(BreakNetQuicServer *s,
                              const SnowTransportDatagramAddress *local,
                              const SnowTransportDatagramAddress *remote,
                              const uint8_t *packet, size_t len, u64 now_ns) {
    u32 index;
    for (index = 0u; index < s->max_connections; index++) {
        if (s->slots[index] == NULL) {
            break;
        }
    }
    if (index == s->max_connections) {
        s->dropped++; /* slot table full: new Initials are refused */
        return;
    }
    BreakNetQuicConn *conn =
        (BreakNetQuicConn *)calloc(1u, sizeof(BreakNetQuicConn));
    if (conn == NULL) {
        s->dropped++;
        return;
    }
    conn->fd = s->fd;
    conn->local = *local;
    conn->remote = *remote;
    /* The module contract pins exactly one stream: the client's first
     * bidirectional stream, which QUIC numbers 0 (client-initiated bidi
     * stream ids are 0, 4, 8, ...). The client opens it as its handshake
     * completes; the server may send on it from the same moment. */
    conn->stream_id = 0;
    conn->conn_id = s->next_conn_id++;
    conn->tx_seq = 1u; /* outbound envelope sequence starts at 1 (TCP parity) */
    conn->server = s;
    conn->rx = (u8 *)malloc(BNQ_FRAME_CAP);
    conn->tx = (u8 *)malloc(BNQ_FRAME_CAP);
    if (conn->rx == NULL || conn->tx == NULL) {
        bnq_conn_free(conn);
        s->dropped++;
        return;
    }
    SnowQuicNgtcp2ServerConfig sc;
    memset(&sc, 0, sizeof(sc));
    sc.output = bnq_output;
    sc.output_userdata = conn;
    sc.clock = bnq_now_ns;
    sc.clock_userdata = NULL;
    sc.certificate_pem = s->cert_pem;
    sc.certificate_pem_size = s->cert_pem_len;
    sc.private_key_pem = s->key_pem;
    sc.private_key_pem_size = s->key_pem_len;
    sc.alpn = s->alpn_wire;
    sc.alpn_size = s->alpn_wire_len;
    sc.local_address = *local;
    sc.remote_address = *remote;
    sc.max_idle_timeout_ns = s->max_idle_timeout_ns;
    sc.handshake_timeout_ns = s->handshake_timeout_ns;
    sc.handshake_completed = bnq_handshake_done;
    sc.recv_stream_data = bnq_recv_stream;
    sc.event_userdata = conn;
    /* accept emits the first flight through bnq_output before returning, so
     * the slot's fd/remote must already be wired (they are, above). */
    if (SnowQuicNgtcp2Accept(&conn->adapter, sc, packet, len, now_ns) !=
        SNOW_OK) {
        bnq_conn_free(conn);
        s->dropped++;
        return;
    }
    s->slots[index] = conn;
    s->accepted_count++;
}

/* Auth gate for unauthenticated connections: the inbox must hold exactly a
 * well-formed AUTH v2 (id 1, version 2, 56 bytes). Anything else closes the
 * connection fail-closed. On success the session flips to authenticated and
 * the app gets an AUTHENTICATED event. */
static void bnq_server_auth_consume(BreakNetQuicServer *s,
                                    BreakNetQuicConn *conn) {
    u16 mid = 0u, ver = 0u;
    u32 seq = 0u, len = 0u;
    u8 payload[64];
    bool ok = bnq_conn_recv_message(conn, &mid, &ver, &seq, payload,
                                    sizeof(payload), &len);
    bool authed = false;
    if (ok && mid == BREAK_NET_MESSAGE_ID_AUTH && ver == 2u && len == 56u) {
        const u8 *key_id = payload;
        const u8 *client_nonce = payload + 8u;
        const u8 *tag = payload + 24u;
        u8 psk[32];
        if (s->auth_fn(s->auth_user, key_id, psk)) {
            u8 context[8u + 16u + 16u];
            u8 expected[32];
            memcpy(context, "BRKAUTH2", 8u);
            memcpy(context + 8u, conn->server_nonce, 16u);
            memcpy(context + 24u, client_nonce, 16u);
            if (break_crypto_hmac_sha256(psk, sizeof(psk), context,
                                         sizeof(context), expected)) {
                u32 diff = 0u;
                for (u32 i = 0u; i < 32u; i++) {
                    diff |= (u32)(expected[i] ^ tag[i]);
                }
                authed = (diff == 0u);
            }
        }
        memset(psk, 0, sizeof(psk));
    }
    if (authed) {
        conn->auth_state = 2u;
        conn->auth_deadline_ns = 0u;
        bnq_event_post(&s->events, BREAK_NET_QUIC_EVENT_AUTHENTICATED, 0u,
                       conn->conn_id);
    } else {
        /* bad/missing AUTH, wrong tag, unknown key, protocol noise: close */
        conn->close_reason = BREAK_NET_QUIC_DISCONNECT_AUTH;
        SnowQuicNgtcp2Close(conn->adapter);
    }
}

bool break_net_quic_server_set_auth(BreakNetQuicServer *s,
                                    BreakNetQuicAuthKeyFn fn, void *user,
                                    u32 auth_timeout_ms) {
    if (s == NULL || fn == NULL || s->accepted_count != 0u) {
        return false;
    }
    s->auth_fn = fn;
    s->auth_user = user;
    s->auth_timeout_ns =
        (u64)(auth_timeout_ms != 0u ? auth_timeout_ms : 10000u) *
        UINT64_C(1000000);
    return true;
}

bool break_net_quic_client_authenticate(BreakNetQuicClient *c,
                                        const u8 key_id[8],
                                        const u8 psk[32]) {
    if (c == NULL || c->conn == NULL || key_id == NULL || psk == NULL) {
        return false;
    }
    BreakNetQuicConn *conn = c->conn;
    /* The CHALLENGE must be the pending inbox message. */
    u16 mid = 0u, ver = 0u;
    u32 seq = 0u, len = 0u;
    u8 nonce[16];
    if (!bnq_conn_recv_message(conn, &mid, &ver, &seq, nonce, sizeof(nonce),
                               &len) ||
        mid != BREAK_NET_MESSAGE_ID_CHALLENGE || ver != 1u || len != 16u) {
        return false;
    }
    u8 payload[56];
    u8 client_nonce[16];
    if (!break_crypto_random(client_nonce, sizeof(client_nonce))) {
        return false;
    }
    u8 context[8u + 16u + 16u];
    memcpy(context, "BRKAUTH2", 8u);
    memcpy(context + 8u, nonce, 16u);
    memcpy(context + 24u, client_nonce, 16u);
    u8 tag[32];
    if (!break_crypto_hmac_sha256(psk, 32u, context, sizeof(context), tag)) {
        return false;
    }
    memcpy(payload, key_id, 8u);
    memcpy(payload + 8u, client_nonce, 16u);
    memcpy(payload + 24u, tag, 32u);
    memset(client_nonce, 0, sizeof(client_nonce));
    return bnq_conn_send_message(conn, BREAK_NET_MESSAGE_ID_AUTH, 2u, 0u,
                                 payload, sizeof(payload));
}

bool break_net_quic_conn_send_message(BreakNetQuicServer *s,
                                      BreakNetQuicConn *conn, u16 message_id,
                                      u16 version, u16 flags,
                                      const u8 *payload, u32 len) {
    if (s == NULL || conn == NULL || conn->server != s ||
        !conn->handshake_done || conn->close_reported) {
        return false;
    }
    return bnq_conn_send_message(conn, message_id, version, flags, payload,
                                 len);
}

bool break_net_quic_client_send_message(BreakNetQuicClient *c,
                                        u16 message_id, u16 version,
                                        u16 flags, const u8 *payload,
                                        u32 len) {
    if (c == NULL || c->conn == NULL || !c->conn->handshake_done ||
        c->conn->close_reported) {
        return false;
    }
    return bnq_conn_send_message(c->conn, message_id, version, flags, payload,
                                 len);
}

bool break_net_quic_conn_recv_message(BreakNetQuicServer *s,
                                      BreakNetQuicConn *conn,
                                      u16 *out_message_id, u16 *out_version,
                                      u32 *out_sequence, u8 *out, u32 cap,
                                      u32 *out_len) {
    if (s == NULL || conn == NULL || conn->server != s || out == NULL) {
        return false;
    }
    return bnq_conn_recv_message(conn, out_message_id, out_version,
                                 out_sequence, out, cap, out_len);
}

bool break_net_quic_client_recv_message(BreakNetQuicClient *c,
                                        u16 *out_message_id, u16 *out_version,
                                        u32 *out_sequence, u8 *out, u32 cap,
                                        u32 *out_len) {
    if (c == NULL || c->conn == NULL || out == NULL) {
        return false;
    }
    return bnq_conn_recv_message(c->conn, out_message_id, out_version,
                                 out_sequence, out, cap, out_len);
}

bool break_net_quic_server_step(BreakNetQuicServer *s, u32 timeout_ms) {
    if (s == NULL) {
        return false;
    }
    bool progress = false;
    u64 now = bnq_now_ns(NULL);

    /* Service first: collect the nearest deadline across connections. */
    u64 wait_ns = (u64)timeout_ms * UINT64_C(1000000);
    for (u32 i = 0u; i < s->max_connections; i++) {
        BreakNetQuicConn *conn = s->slots[i];
        if (conn == NULL || conn->adapter == NULL) {
            continue;
        }
        u64 deadline = 0u;
        SnowQuicNgtcp2Service(conn->adapter, now, &deadline);
        if (deadline != 0u && deadline > now && deadline - now < wait_ns) {
            wait_ns = deadline - now;
        }
    }

    struct pollfd pfd;
    pfd.fd = s->fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    int pr = poll(&pfd, 1u, (int)(wait_ns / UINT64_C(1000000)));
    if (pr > 0 && (pfd.revents & POLLIN) != 0) {
        for (u32 budget = 0u; budget < BNQ_RECV_BUDGET_PER_STEP; budget++) {
            u8 packet[SNOW_QUIC_NGTCP2_MAX_PACKET];
            struct sockaddr_in src;
            socklen_t srclen = sizeof(src);
            ssize_t n = recvfrom(s->fd, packet, sizeof(packet), 0,
                                 (struct sockaddr *)&src, &srclen);
            if (n <= 0) {
                break; /* EAGAIN: drained */
            }
            progress = true;
            now = bnq_now_ns(NULL);
            SnowTransportDatagramAddress remote = bnq_addr_from(&src);
            struct sockaddr_in me;
            socklen_t melen = sizeof(me);
            if (getsockname(s->fd, (struct sockaddr *)&me, &melen) != 0) {
                s->dropped++;
                continue;
            }
            SnowTransportDatagramAddress local = bnq_addr_from(&me);
            BreakNetQuicConn *conn = NULL;
            for (u32 i = 0u; i < s->max_connections; i++) {
                if (s->slots[i] != NULL &&
                    bnq_addr_equal(&s->slots[i]->remote, &remote)) {
                    conn = s->slots[i];
                    break;
                }
            }
            if (conn != NULL) {
                if (SnowQuicNgtcp2InputPath(conn->adapter, packet, (size_t)n,
                                            local, remote, now) != SNOW_OK) {
                    s->dropped++;
                }
            } else {
                bnq_server_accept(s, &local, &remote, packet, (size_t)n, now);
            }
        }
    }

    /* Service again: handshakes, streams, timers; then lifecycle. */
    now = bnq_now_ns(NULL);
    for (u32 i = 0u; i < s->max_connections; i++) {
        BreakNetQuicConn *conn = s->slots[i];
        if (conn == NULL) {
            continue;
        }
        u64 deadline = 0u;
        SnowQuicNgtcp2Service(conn->adapter, now, &deadline);
        if (conn->handshake_done && !conn->connect_posted) {
            conn->connect_posted = true;
            bnq_event_post(&s->events, BREAK_NET_QUIC_EVENT_CONNECT, 0u,
                           conn->conn_id);
        }
        /* Auth configured: the CHALLENGE (first server message, envelope
         * sequence 1) goes out as soon as the client's READY marker has
         * materialized the stream; the auth deadline starts at the send. */
        if (conn->handshake_done && !conn->close_reported &&
            conn->stream_ready && s->auth_fn != NULL && conn->auth_state == 0u) {
            if (!break_crypto_random(conn->server_nonce, 16u) ||
                !bnq_conn_send_message(conn, BREAK_NET_MESSAGE_ID_CHALLENGE,
                                       1u, 0u, conn->server_nonce, 16u)) {
                conn->close_reason = BREAK_NET_QUIC_DISCONNECT_AUTH;
                SnowQuicNgtcp2Close(conn->adapter);
            } else {
                conn->auth_state = 1u;
                conn->auth_deadline_ns = now + s->auth_timeout_ns;
            }
        }
        if (conn->handshake_done && !conn->close_reported) {
            if (!conn->rx_msg_ready) {
                bnq_extract(conn);
            }
            if (conn->rx_msg_ready && !conn->rx_msg_event_posted) {
                if (s->auth_fn != NULL && conn->auth_state != 2u) {
                    bnq_server_auth_consume(s, conn);
                } else {
                    conn->rx_msg_event_posted = true;
                    bnq_event_post(&s->events, BREAK_NET_QUIC_EVENT_MESSAGE,
                                   0u, conn->conn_id);
                }
            }
            bnq_conn_drain_tx(conn);
            /* auth deadline: still challenged when the timer fires -> close */
            if (conn->auth_state == 1u && now > conn->auth_deadline_ns) {
                conn->close_reason = BREAK_NET_QUIC_DISCONNECT_AUTH;
                SnowQuicNgtcp2Close(conn->adapter);
            }
        }
        if (SnowQuicNgtcp2IsClosingOrDraining(conn->adapter)) {
            conn->close_reported = true;
        }
    }
    /* Reclaim terminal slots (posts DISCONNECT). */
    for (u32 i = 0u; i < s->max_connections; i++) {
        if (s->slots[i] != NULL && s->slots[i]->close_reported) {
            bnq_server_reclaim(s, i);
        }
    }
    return progress;
}

bool break_net_quic_server_poll_event(BreakNetQuicServer *s,
                                      BreakNetQuicEvent *out) {
    if (s == NULL || out == NULL) {
        return false;
    }
    return bnq_event_take(&s->events, out);
}

BreakNetQuicConn *break_net_quic_server_conn(BreakNetQuicServer *s,
                                             u32 conn_id) {
    if (s == NULL) {
        return NULL;
    }
    for (u32 i = 0u; i < s->max_connections; i++) {
        if (s->slots[i] != NULL && s->slots[i]->conn_id == conn_id) {
            return s->slots[i];
        }
    }
    return NULL;
}

bool break_net_quic_conn_read(BreakNetQuicServer *s, BreakNetQuicConn *conn,
                              u8 *out, u32 cap, u32 *out_len) {
    if (s == NULL || conn == NULL || conn->server != s || out == NULL) {
        return false;
    }
    bool ok = bnq_conn_read(conn, out, cap, out_len);
    if (ok && !conn->rx_msg_ready) {
        bnq_extract(conn);
    }
    return ok;
}

bool break_net_quic_conn_send(BreakNetQuicServer *s, BreakNetQuicConn *conn,
                              const u8 *data, u32 len) {
    if (s == NULL || conn == NULL || conn->server != s ||
        !conn->handshake_done || conn->stream_id < 0 || !conn->stream_ready) {
        return false;
    }
    return bnq_conn_send(conn, data, len);
}

void break_net_quic_conn_close(BreakNetQuicServer *s, BreakNetQuicConn *conn) {
    if (s == NULL || conn == NULL || conn->server != s ||
        conn->adapter == NULL) {
        return;
    }
    conn->close_reason = BREAK_NET_QUIC_DISCONNECT_LOCAL;
    SnowQuicNgtcp2Close(conn->adapter);
}

u64 break_net_quic_server_dropped_datagrams(const BreakNetQuicServer *s) {
    return s != NULL ? s->dropped : 0u;
}

u64 break_net_quic_server_events_overflow(const BreakNetQuicServer *s) {
    return s != NULL ? s->events.overflow : 0u;
}

void break_net_quic_server_destroy(BreakNetQuicServer **server) {
    if (server == NULL || *server == NULL) {
        return;
    }
    BreakNetQuicServer *s = *server;
    if (s->slots != NULL) {
        for (u32 i = 0u; i < s->max_connections; i++) {
            bnq_conn_free(s->slots[i]);
        }
        free(s->slots);
    }
    if (s->fd >= 0) {
        close(s->fd);
    }
    free(s->cert_pem);
    free(s->key_pem);
    free(s);
    *server = NULL;
}

/* ------------------------------------------------------------------ client */

BreakNetQuicClient *break_net_quic_client_create(
    const BreakNetQuicClientConfig *cfg) {
    if (cfg == NULL || cfg->host == NULL || cfg->port == 0u ||
        cfg->server_name == NULL || cfg->server_name[0] == '\0' ||
        cfg->trust_store_file == NULL || cfg->cert_file == NULL ||
        cfg->key_file == NULL) {
        return NULL;
    }
    u8 alpn_wire[34];
    u32 alpn_wire_len = bnq_alpn_wire(cfg->alpn, alpn_wire, sizeof(alpn_wire));
    if (alpn_wire_len == 0u) {
        return NULL;
    }
    struct in_addr addr;
    if (inet_pton(AF_INET, cfg->host, &addr) != 1) {
        return NULL; /* IPv4 literal only (v1 contract) */
    }
    size_t trust_len = 0u, cert_len = 0u, key_len = 0u;
    u8 *trust = bnq_read_pem(cfg->trust_store_file, &trust_len);
    u8 *cert = bnq_read_pem(cfg->cert_file, &cert_len);
    u8 *key = bnq_read_pem(cfg->key_file, &key_len);
    if (trust == NULL || cert == NULL || key == NULL) {
        free(trust);
        free(cert);
        free(key);
        return NULL;
    }
    BreakNetQuicClient *c = (BreakNetQuicClient *)calloc(1u, sizeof(*c));
    BreakNetQuicConn *conn =
        (BreakNetQuicConn *)calloc(1u, sizeof(BreakNetQuicConn));
    if (c == NULL || conn == NULL) {
        free(trust);
        free(cert);
        free(key);
        free(c);
        free(conn);
        return NULL;
    }
    c->fd = -1;
    c->conn = conn;
    conn->fd = -1;
    conn->stream_id = -1;
    conn->conn_id = 1u;
    conn->tx_seq = 1u;
    conn->rx = (u8 *)malloc(BNQ_FRAME_CAP);
    conn->tx = (u8 *)malloc(BNQ_FRAME_CAP);
    if (conn->rx == NULL || conn->tx == NULL) {
        free(trust);
        free(cert);
        free(key);
        break_net_quic_client_destroy(&c);
        return NULL;
    }

    c->fd = bnq_socket_nonblock();
    if (c->fd < 0) {
        free(trust);
        free(cert);
        free(key);
        break_net_quic_client_destroy(&c);
        return NULL;
    }
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(cfg->port);
    sa.sin_addr = addr;
    if (connect(c->fd, (const struct sockaddr *)&sa, sizeof(sa)) != 0) {
        free(trust);
        free(cert);
        free(key);
        break_net_quic_client_destroy(&c);
        return NULL;
    }
    conn->connected_socket = true;
    struct sockaddr_in me;
    socklen_t melen = sizeof(me);
    if (getsockname(c->fd, (struct sockaddr *)&me, &melen) != 0) {
        free(trust);
        free(cert);
        free(key);
        break_net_quic_client_destroy(&c);
        return NULL;
    }
    conn->fd = c->fd;
    conn->local = bnq_addr_from(&me);
    conn->remote = bnq_addr_from(&sa);
    c->created_ns = bnq_now_ns(NULL);
    c->handshake_timeout_ns =
        (u64)(cfg->handshake_timeout_ms != 0u ? cfg->handshake_timeout_ms
                                              : BNQ_DEFAULT_HANDSHAKE_MS) *
        UINT64_C(1000000);

    /* The init emits the first flight through bnq_output before returning,
     * so the conn's fd/addresses must already be wired (they are, above). */
    SnowQuicNgtcp2Config qc;
    bnq_fill_client_adapter_config(&qc, conn, cfg->server_name, trust,
                                   trust_len, alpn_wire, alpn_wire_len);
    qc.certificate_pem = cert;
    qc.certificate_pem_size = cert_len;
    qc.private_key_pem = key;
    qc.private_key_pem_size = key_len;
    SnowStatus st = SnowQuicNgtcp2Init(&conn->adapter, qc);
    free(trust); /* the adapter copies what it needs into its SSL_CTX */
    free(cert);
    free(key);
    if (st != SNOW_OK) {
        break_net_quic_client_destroy(&c);
        return NULL;
    }
    return c;
}

bool break_net_quic_client_step(BreakNetQuicClient *c, u32 timeout_ms) {
    if (c == NULL || c->conn == NULL || c->conn->adapter == NULL) {
        return false;
    }
    BreakNetQuicConn *conn = c->conn;
    bool progress = false;
    u64 now = bnq_now_ns(NULL);
    u64 wait_ns = (u64)timeout_ms * UINT64_C(1000000);
    u64 deadline = 0u;
    SnowQuicNgtcp2Service(conn->adapter, now, &deadline);
    if (deadline != 0u && deadline > now && deadline - now < wait_ns) {
        wait_ns = deadline - now;
    }

    struct pollfd pfd;
    pfd.fd = c->fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    int pr = poll(&pfd, 1u, (int)(wait_ns / UINT64_C(1000000)));
    if (pr > 0 && (pfd.revents & POLLIN) != 0) {
        for (u32 budget = 0u; budget < BNQ_RECV_BUDGET_PER_STEP; budget++) {
            u8 packet[SNOW_QUIC_NGTCP2_MAX_PACKET];
            ssize_t n = recv(c->fd, packet, sizeof(packet), 0);
            if (n <= 0) {
                break;
            }
            progress = true;
            now = bnq_now_ns(NULL);
            SnowQuicNgtcp2InputPath(conn->adapter, packet, (size_t)n,
                                    conn->local, conn->remote, now);
        }
    }

    now = bnq_now_ns(NULL);
    SnowQuicNgtcp2Service(conn->adapter, now, &deadline);
    if (!conn->handshake_done && !conn->close_reported &&
        now - c->created_ns > c->handshake_timeout_ns) {
        /* handshake deadline: close fail-closed (wrong ALPN, unreachable
         * peer, silent drop all land here) */
        c->failed = true;
        conn->close_reason = BREAK_NET_QUIC_DISCONNECT_HANDSHAKE;
        SnowQuicNgtcp2Close(conn->adapter);
    }
    if (conn->handshake_done && conn->stream_id < 0) {
        int64_t stream_id = -1;
        if (SnowQuicNgtcp2OpenBidiStream(conn->adapter, &stream_id, now) ==
            SNOW_OK) {
            conn->stream_id = stream_id;
            conn->stream_ready = true; /* locally opened = materialized */
        }
    }
    /* The READY marker materializes the stream on the server side (the
     * adapter refuses sends on never-seen streams), letting the server's
     * CHALLENGE out. Frame-level, invisible to both read APIs. */
    if (conn->handshake_done && conn->stream_ready && !conn->ready_sent &&
        conn->tx_off >= conn->tx_len) {
        conn->tx[0] = 0xFFu;
        conn->tx[1] = 0xFFu;
        conn->tx[2] = 0xFFu;
        conn->tx[3] = 0xFFu;
        conn->tx_off = 0u;
        conn->tx_len = 4u;
        conn->ready_sent = true;
    }
    if (conn->handshake_done) {
        if (!conn->rx_msg_ready) {
            bnq_extract(conn);
        }
        if (conn->rx_msg_ready && !conn->rx_msg_event_posted) {
            conn->rx_msg_event_posted = true;
            bnq_event_post(&c->events, BREAK_NET_QUIC_EVENT_MESSAGE, 0u,
                           conn->conn_id);
        }
        bnq_conn_drain_tx(conn);
    }
    if (SnowQuicNgtcp2IsClosingOrDraining(conn->adapter) &&
        !conn->close_reported) {
        conn->close_reported = true;
        u8 reason;
        if (!conn->handshake_done) {
            c->failed = true;
            reason = BREAK_NET_QUIC_DISCONNECT_HANDSHAKE;
        } else if (SnowQuicNgtcp2IsLocallyClosed(conn->adapter)) {
            reason = BREAK_NET_QUIC_DISCONNECT_LOCAL;
        } else {
            reason = BREAK_NET_QUIC_DISCONNECT_PEER;
        }
        bnq_event_post(&c->events, BREAK_NET_QUIC_EVENT_DISCONNECT, reason,
                       conn->conn_id);
    }
    return progress;
}

bool break_net_quic_client_handshake_done(const BreakNetQuicClient *c) {
    return c != NULL && c->conn != NULL && c->conn->handshake_done &&
           !c->conn->close_reported;
}

bool break_net_quic_client_failed(const BreakNetQuicClient *c) {
    return c != NULL && c->failed;
}

bool break_net_quic_client_send(BreakNetQuicClient *c, const u8 *data,
                                u32 len) {
    if (c == NULL || c->conn == NULL || !c->conn->handshake_done ||
        c->conn->stream_id < 0) {
        return false;
    }
    return bnq_conn_send(c->conn, data, len);
}

bool break_net_quic_client_read(BreakNetQuicClient *c, u8 *out, u32 cap,
                                u32 *out_len) {
    if (c == NULL || c->conn == NULL || out == NULL) {
        return false;
    }
    bool ok = bnq_conn_read(c->conn, out, cap, out_len);
    if (ok && !c->conn->rx_msg_ready) {
        bnq_extract(c->conn);
    }
    return ok;
}

bool break_net_quic_client_poll_event(BreakNetQuicClient *c,
                                      BreakNetQuicEvent *out) {
    if (c == NULL || out == NULL) {
        return false;
    }
    return bnq_event_take(&c->events, out);
}

void break_net_quic_client_close(BreakNetQuicClient *c) {
    if (c == NULL || c->conn == NULL || c->conn->adapter == NULL) {
        return;
    }
    c->conn->close_reason = BREAK_NET_QUIC_DISCONNECT_LOCAL;
    SnowQuicNgtcp2Close(c->conn->adapter);
}

void break_net_quic_client_destroy(BreakNetQuicClient **client) {
    if (client == NULL || *client == NULL) {
        return;
    }
    BreakNetQuicClient *c = *client;
    bnq_conn_free(c->conn);
    if (c->fd >= 0) {
        close(c->fd);
    }
    free(c);
    *client = NULL;
}
