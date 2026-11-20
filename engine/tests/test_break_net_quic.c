/* test_break_net_quic — loopback evidence for break_net_quic
 * (docs/design/quic_transport.md). Real UDP sockets on 127.0.0.1 with port-0
 * binds; both endpoints step alternately from the test thread; every wait is
 * condition-polled with a deadline (no fixed sleeps). */

#include "network/break_net_quic.h"
#include "network/break_online_voice.h"
#include "network/break_online_voice_quic.h"
#include "network/break_online_lobby.h"
#include "network/break_online_session_quic.h"
#include "network/break_voice_mixer.h"
#include "test_quic_udp_proxy.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal test harness (repo idiom) ---------------------------------- */

static int g_failures;
#define ASSERT_TRUE(x) do { if (!(x)) { \
    printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #x); g_failures++; \
    return false; } } while (0)
#define ASSERT_FALSE(x) ASSERT_TRUE(!(x))
#define ASSERT_EQ_U(a, b) do { u64 _a = (u64)(a), _b = (u64)(b); \
    if (_a != _b) { printf("FAIL %s:%d: %s=%llu != %s=%llu\n", __FILE__, \
    __LINE__, #a, (unsigned long long)_a, #b, (unsigned long long)_b); \
    g_failures++; return false; } } while (0)

#define STR2(x) #x
#define STR(x) STR2(x)
#define FIXTURE(name) STR(BREAK_TEST_SSL_FIXTURE_DIR) "/" name

static const char *kCert = FIXTURE("break_test_cert.pem");
static const char *kKey = FIXTURE("break_test_key.pem");
static const char *kAlpn = "break/1";

typedef struct {
    BreakNetQuicServer *server;
    BreakNetQuicClient *client;
    BreakNetQuicEvent first_event; /* first server event captured while pumping */
    bool has_first_event;
} Pair;

/* Alternating bounded steps until cond(user) or the deadline (5 s wall). */
static bool pump_until(Pair *p, bool (*cond)(Pair *), u64 budget_ms) {
    u64 waited = 0;
    while (waited < budget_ms) {
        if (p->server != NULL) {
            break_net_quic_server_step(p->server, 1u);
        }
        if (p->client != NULL) {
            break_net_quic_client_step(p->client, 1u);
        }
        if (cond(p)) {
            return true;
        }
        waited += 2u;
    }
    return false;
}

static bool cond_handshake(Pair *p) {
    return break_net_quic_client_handshake_done(p->client);
}
/* The server's CONNECT event lands a round trip after the client's handshake
 * completes (the client's Finished must still be processed server-side), so
 * pump until the event is captured, not just until the client is ready. */
static bool cond_connect_event(Pair *p) {
    if (!break_net_quic_client_handshake_done(p->client)) {
        return false;
    }
    if (!p->has_first_event) {
        BreakNetQuicEvent ev;
        while (break_net_quic_server_poll_event(p->server, &ev)) {
            if (!p->has_first_event) {
                p->first_event = ev;
                p->has_first_event = true;
            }
        }
    }
    return p->has_first_event;
}
static bool get_connect_event(Pair *p, BreakNetQuicEvent *out) {
    if (!pump_until(p, cond_connect_event, 5000u)) {
        return false;
    }
    *out = p->first_event;
    p->has_first_event = false;
    return true;
}
static bool cond_failed(Pair *p) {
    return break_net_quic_client_failed(p->client);
}

static u32 g_client_handshake_ms;
static Pair make_pair(const char *alpn, const char *server_name, u32 max_conns) {
    Pair p;
    p.server = NULL;
    p.client = NULL;
    p.has_first_event = false;
    BreakNetQuicServerConfig sc;
    memset(&sc, 0, sizeof(sc));
    sc.cert_file = kCert;
    sc.key_file = kKey;
    sc.alpn = kAlpn;
    sc.port = 0;
    sc.max_connections = max_conns;
    p.server = break_net_quic_server_create(&sc);
    if (p.server == NULL) {
        return p;
    }
    BreakNetQuicClientConfig cc;
    memset(&cc, 0, sizeof(cc));
    cc.host = "127.0.0.1";
    cc.port = break_net_quic_server_port(p.server);
    cc.server_name = server_name;
    cc.trust_store_file = kCert; /* self-signed fixture is its own CA */
    cc.cert_file = kCert;        /* snow clients always carry a certificate */
    cc.key_file = kKey;
    cc.alpn = alpn;
    cc.handshake_timeout_ms = g_client_handshake_ms;
    p.client = break_net_quic_client_create(&cc);
    if (p.client == NULL) {
        break_net_quic_server_destroy(&p.server);
    }
    return p;
}

static void free_pair(Pair *p) {
    break_net_quic_client_destroy(&p->client);
    break_net_quic_server_destroy(&p->server);
}

static bool server_next_event(BreakNetQuicServer *s, BreakNetQuicEvent *ev) {
    return break_net_quic_server_poll_event(s, ev);
}

/* ---- tests --------------------------------------------------------------- */

static bool test_config_validation(void) {
    BreakNetQuicServerConfig sc;
    memset(&sc, 0, sizeof(sc));
    ASSERT_TRUE(break_net_quic_server_create(NULL) == NULL);
    ASSERT_TRUE(break_net_quic_server_create(&sc) == NULL); /* nothing set */
    sc.cert_file = kCert;
    sc.key_file = kKey;
    ASSERT_TRUE(break_net_quic_server_create(&sc) == NULL); /* missing alpn */
    sc.alpn = kAlpn;
    sc.cert_file = "/nonexistent/cert.pem";
    ASSERT_TRUE(break_net_quic_server_create(&sc) == NULL); /* unreadable cert */
    sc.cert_file = kCert;
    sc.max_connections = BREAK_NET_QUIC_MAX_CONNECTIONS + 1u;
    ASSERT_TRUE(break_net_quic_server_create(&sc) == NULL); /* over hard cap */

    BreakNetQuicClientConfig cc;
    memset(&cc, 0, sizeof(cc));
    ASSERT_TRUE(break_net_quic_client_create(NULL) == NULL);
    ASSERT_TRUE(break_net_quic_client_create(&cc) == NULL);
    cc.host = "localhost"; /* not an IPv4 literal in v1 */
    cc.port = 1u;
    cc.server_name = "localhost";
    cc.trust_store_file = kCert;
    cc.cert_file = kCert;
    cc.key_file = kKey;
    cc.alpn = kAlpn;
    ASSERT_TRUE(break_net_quic_client_create(&cc) == NULL);
    cc.host = "127.0.0.1";
    cc.trust_store_file = "/nonexistent/ca.pem";
    ASSERT_TRUE(break_net_quic_client_create(&cc) == NULL);
    cc.trust_store_file = kCert;
    cc.cert_file = NULL; /* client certificate is mandatory (snow contract) */
    ASSERT_TRUE(break_net_quic_client_create(&cc) == NULL);
    return true;
}

static bool test_handshake_echo(void) {
    Pair p = make_pair(kAlpn, "localhost", 0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(break_net_quic_server_port(p.server) != 0u);
    /* server saw exactly one CONNECT */
    BreakNetQuicEvent ev;
    ASSERT_TRUE(get_connect_event(&p, &ev));
    ASSERT_EQ_U(ev.type, BREAK_NET_QUIC_EVENT_CONNECT);
    /* The listener's Retry policy (per-boot secret) answered the tokenless
     * Initial before accepting: the counter proves the path is live. */
    ASSERT_TRUE(break_net_quic_server_retry_requests(p.server) >= 1u);
    u32 conn_id = ev.conn_id;
    BreakNetQuicConn *conn = break_net_quic_server_conn(p.server, conn_id);
    ASSERT_TRUE(conn != NULL);
    ASSERT_FALSE(server_next_event(p.server, &ev)); /* no duplicates */

    const char *ping = "ping";
    ASSERT_TRUE(break_net_quic_client_send(p.client, (const u8 *)ping, 4u));

    /* pump until the server inbox holds the message */
    bool got = false;
    for (u32 i = 0u; i < 2500u && !got; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        BreakNetQuicEvent mev;
        while (break_net_quic_server_poll_event(p.server, &mev)) {
            if (mev.type == BREAK_NET_QUIC_EVENT_MESSAGE &&
                mev.conn_id == conn_id) {
                got = true;
            }
        }
    }
    ASSERT_TRUE(got);
    u8 buf[64];
    u32 len = 0;
    ASSERT_TRUE(break_net_quic_conn_read(p.server, conn, buf, sizeof(buf), &len));
    ASSERT_EQ_U(len, 4u);
    ASSERT_TRUE(memcmp(buf, "ping", 4u) == 0);
    ASSERT_FALSE(break_net_quic_conn_read(p.server, conn, buf, sizeof(buf), &len));

    const char *pong = "pong";
    ASSERT_TRUE(break_net_quic_conn_send(p.server, conn, (const u8 *)pong, 4u));
    bool replied = false;
    for (u32 i = 0u; i < 2500u && !replied; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        if (break_net_quic_client_read(p.client, buf, sizeof(buf), &len)) {
            replied = true;
        }
    }
    ASSERT_TRUE(replied);
    ASSERT_EQ_U(len, 4u);
    ASSERT_TRUE(memcmp(buf, "pong", 4u) == 0);
    free_pair(&p);
    return true;
}

static bool test_sequential_messages(void) {
    Pair p = make_pair(kAlpn, "localhost", 0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    BreakNetQuicEvent ev;
    ASSERT_TRUE(get_connect_event(&p, &ev));
    BreakNetQuicConn *conn = break_net_quic_server_conn(p.server, ev.conn_id);
    ASSERT_TRUE(conn != NULL);

    /* five messages, strictly in order; single-inbox backpressure means the
     * test reads between sends */
    for (u32 m = 0u; m < 5u; m++) {
        char payload[16];
        int plen = snprintf(payload, sizeof(payload), "msg%u", m);
        ASSERT_TRUE(break_net_quic_client_send(p.client, (const u8 *)payload,
                                               (u32)plen));
        bool got = false;
        for (u32 i = 0u; i < 2500u && !got; i++) {
            u8 buf[64];
            u32 len = 0;
            break_net_quic_server_step(p.server, 1u);
            break_net_quic_client_step(p.client, 1u);
            BreakNetQuicEvent dev;
            while (break_net_quic_server_poll_event(p.server, &dev)) {
            }
            if (break_net_quic_conn_read(p.server, conn, buf, sizeof(buf),
                                         &len)) {
                ASSERT_EQ_U(len, (u32)plen);
                ASSERT_TRUE(memcmp(buf, payload, (size_t)plen) == 0);
                got = true;
            }
        }
        ASSERT_TRUE(got);
    }
    free_pair(&p);
    return true;
}

static bool test_message_size_cap(void) {
    Pair p = make_pair(kAlpn, "localhost", 0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    BreakNetQuicEvent ev;
    ASSERT_TRUE(get_connect_event(&p, &ev));
    BreakNetQuicConn *conn = break_net_quic_server_conn(p.server, ev.conn_id);
    ASSERT_TRUE(conn != NULL);

    static u8 big[BREAK_NET_QUIC_MAX_MESSAGE];
    memset(big, 0xA5, sizeof(big));
    /* exactly at the cap: accepted and echoed whole */
    ASSERT_TRUE(break_net_quic_client_send(p.client, big,
                                           BREAK_NET_QUIC_MAX_MESSAGE));
    /* over the cap: refused at the API boundary */
    static u8 over[BREAK_NET_QUIC_MAX_MESSAGE + 1u];
    ASSERT_FALSE(break_net_quic_client_send(p.client, over, sizeof(over)));

    bool got = false;
    static u8 buf[BREAK_NET_QUIC_MAX_MESSAGE];
    for (u32 i = 0u; i < 5000u && !got; i++) {
        u32 len = 0;
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        BreakNetQuicEvent dev;
        while (break_net_quic_server_poll_event(p.server, &dev)) {
        }
        if (break_net_quic_conn_read(p.server, conn, buf, sizeof(buf), &len)) {
            ASSERT_EQ_U(len, BREAK_NET_QUIC_MAX_MESSAGE);
            ASSERT_TRUE(memcmp(buf, big, sizeof(big)) == 0);
            got = true;
        }
    }
    ASSERT_TRUE(got);
    free_pair(&p);
    return true;
}

static bool test_wrong_alpn_fails_closed(void) {
    /* the server refuses the ALPN at TLS selection and answers nothing the
     * client can use; the module's own handshake deadline fails the client
     * closed (500 ms keeps the wall time short) */
    g_client_handshake_ms = 500u;
    Pair p = make_pair("other/1", "localhost", 0u);
    g_client_handshake_ms = 0u;
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_failed, 5000u));
    ASSERT_FALSE(break_net_quic_client_handshake_done(p.client));
    BreakNetQuicEvent ev;
    ASSERT_FALSE(break_net_quic_server_poll_event(p.server, &ev));
    free_pair(&p);
    return true;
}

static bool test_wrong_server_name_fails_closed(void) {
    g_client_handshake_ms = 500u;
    Pair p = make_pair(kAlpn, "wrong.local", 0u);
    g_client_handshake_ms = 0u;
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_failed, 5000u));
    ASSERT_FALSE(break_net_quic_client_handshake_done(p.client));
    free_pair(&p);
    return true;
}

static bool test_slot_table_full(void) {
    Pair p1 = make_pair(kAlpn, "localhost", 1u); /* one slot */
    ASSERT_TRUE(p1.server != NULL && p1.client != NULL);
    ASSERT_TRUE(pump_until(&p1, cond_handshake, 5000u));

    /* drain the first client's CONNECT so the second client's arrival is
     * observable on a clean event queue */
    BreakNetQuicEvent dev0;
    while (break_net_quic_server_poll_event(p1.server, &dev0)) {
    }

    /* second client against the full table: its Initials are dropped and
     * counted, its handshake never completes */
    BreakNetQuicClientConfig cc;
    memset(&cc, 0, sizeof(cc));
    cc.host = "127.0.0.1";
    cc.port = break_net_quic_server_port(p1.server);
    cc.server_name = "localhost";
    cc.trust_store_file = kCert;
    cc.cert_file = kCert;
    cc.key_file = kKey;
    cc.alpn = kAlpn;
    Pair p2;
    p2.server = NULL;
    p2.client = break_net_quic_client_create(&cc);
    ASSERT_TRUE(p2.client != NULL);
    Pair drive;
    drive.server = p1.server;
    drive.client = p2.client;
    ASSERT_FALSE(pump_until(&drive, cond_handshake, 1500u));
    ASSERT_TRUE(break_net_quic_server_dropped_datagrams(p1.server) >= 1u);
    break_net_quic_client_destroy(&p2.client);
    free_pair(&p1);
    return true;
}

static bool test_graceful_close_events(void) {
    Pair p = make_pair(kAlpn, "localhost", 0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    BreakNetQuicEvent ev;
    ASSERT_TRUE(get_connect_event(&p, &ev));
    u32 conn_id = ev.conn_id;

    break_net_quic_client_close(p.client);
    /* drive until both sides observe the close */
    bool server_saw = false, client_saw = false;
    for (u32 i = 0u; i < 5000u && !(server_saw && client_saw); i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        BreakNetQuicEvent dev;
        while (break_net_quic_server_poll_event(p.server, &dev)) {
            if (dev.type == BREAK_NET_QUIC_EVENT_DISCONNECT &&
                dev.conn_id == conn_id) {
                server_saw = true;
                ASSERT_EQ_U(dev.reason, BREAK_NET_QUIC_DISCONNECT_PEER);
            }
        }
        while (break_net_quic_client_poll_event(p.client, &dev)) {
            if (dev.type == BREAK_NET_QUIC_EVENT_DISCONNECT) {
                client_saw = true;
                ASSERT_EQ_U(dev.reason, BREAK_NET_QUIC_DISCONNECT_LOCAL);
            }
        }
    }
    ASSERT_TRUE(server_saw);
    ASSERT_TRUE(client_saw);
    /* the slot is reclaimed: the handle no longer resolves */
    ASSERT_TRUE(break_net_quic_server_conn(p.server, conn_id) == NULL);
    free_pair(&p);
    return true;
}

/* ---- session layer: envelopes + CHALLENGE/AUTH-v2 ------------------------- */

static const u8 k_test_psk[32] = {
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
};
static const u8 k_test_key_id[8] = {0, 0, 0, 0, 0, 0, 0, 0};

static bool test_key_fn(void *user, const u8 key_id[8], u8 out_psk[32]) {
    const u8 *psk = (const u8 *)user;
    if (memcmp(key_id, k_test_key_id, 8u) != 0) {
        return false;
    }
    memcpy(out_psk, psk, 32u);
    return true;
}

/* make_pair with server-side auth required */
static Pair make_auth_pair(u32 auth_timeout_ms) {
    Pair p = make_pair(kAlpn, "localhost", 0u);
    if (p.server != NULL) {
        if (!break_net_quic_server_set_auth(p.server, test_key_fn,
                                            (void *)k_test_psk,
                                            auth_timeout_ms)) {
            free_pair(&p);
        }
    }
    return p;
}

static bool cond_server_event_auth(Pair *p); /* fwd */

/* pump until the server posts an event of `type`; captured in the pair */
static u8 g_want_event;
static bool cond_server_event_auth(Pair *p) {
    BreakNetQuicEvent ev;
    if (p->has_first_event) {
        return true;
    }
    while (break_net_quic_server_poll_event(p->server, &ev)) {
        if (ev.type == g_want_event) {
            p->first_event = ev;
            p->has_first_event = true;
        }
    }
    return p->has_first_event;
}

static bool test_auth_roundtrip(void) {
    Pair p = make_auth_pair(0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));
    /* the CHALLENGE must land in the client inbox */
    bool challenged = false;
    for (u32 i = 0u; i < 2500u && !challenged; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        challenged = break_net_quic_client_authenticate(p.client,
                                                        k_test_key_id,
                                                        k_test_psk);
    }
    ASSERT_TRUE(challenged);
    /* server verifies and posts AUTHENTICATED */
    g_want_event = BREAK_NET_QUIC_EVENT_AUTHENTICATED;
    ASSERT_TRUE(pump_until(&p, cond_server_event_auth, 5000u));
    BreakNetQuicEvent ev = p.first_event;
    p.has_first_event = false;
    BreakNetQuicConn *conn = break_net_quic_server_conn(p.server, ev.conn_id);
    ASSERT_TRUE(conn != NULL);

    /* post-auth envelope echo with sequences: server reads seq 2 (AUTH was
     * seq 1 on the client direction) */
    const char *hello = "hello";
    ASSERT_TRUE(break_net_quic_client_send_message(
        p.client, 4u, 1u, 0u, (const u8 *)hello, 5u));
    bool got = false;
    u16 mid = 0u, ver = 0u;
    u32 seq = 0u, len = 0u;
    u8 buf[64];
    for (u32 i = 0u; i < 2500u && !got; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        BreakNetQuicEvent dev;
        while (break_net_quic_server_poll_event(p.server, &dev)) {
        }
        if (break_net_quic_conn_recv_message(p.server, conn, &mid, &ver, &seq,
                                             buf, sizeof(buf), &len)) {
            got = true;
        }
    }
    ASSERT_TRUE(got);
    ASSERT_EQ_U(mid, 4u);
    ASSERT_EQ_U(ver, 1u);
    ASSERT_EQ_U(seq, 2u); /* AUTH consumed sequence 1 on this direction */
    ASSERT_EQ_U(len, 5u);
    ASSERT_TRUE(memcmp(buf, "hello", 5u) == 0);
    free_pair(&p);
    return true;
}

static bool test_auth_wrong_psk_fails_closed(void) {
    Pair p = make_auth_pair(0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));
    u8 wrong_psk[32];
    memset(wrong_psk, 0x24, sizeof(wrong_psk));
    bool answered = false;
    for (u32 i = 0u; i < 2500u && !answered; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        answered = break_net_quic_client_authenticate(p.client, k_test_key_id,
                                                      wrong_psk);
    }
    ASSERT_TRUE(answered);
    /* the server must close the connection; both sides observe DISCONNECT
     * with AUTH reason on the server side */
    g_want_event = BREAK_NET_QUIC_EVENT_DISCONNECT;
    ASSERT_TRUE(pump_until(&p, cond_server_event_auth, 5000u));
    ASSERT_EQ_U(p.first_event.reason, BREAK_NET_QUIC_DISCONNECT_AUTH);
    free_pair(&p);
    return true;
}

static bool test_auth_preauth_noise_fails_closed(void) {
    Pair p = make_auth_pair(0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));
    /* skip the CHALLENGE and send an application message instead */
    const char *noise = "noise";
    ASSERT_TRUE(break_net_quic_client_send_message(p.client, 4u, 1u, 0u,
                                                   (const u8 *)noise, 5u));
    g_want_event = BREAK_NET_QUIC_EVENT_DISCONNECT;
    ASSERT_TRUE(pump_until(&p, cond_server_event_auth, 5000u));
    ASSERT_EQ_U(p.first_event.reason, BREAK_NET_QUIC_DISCONNECT_AUTH);
    free_pair(&p);
    return true;
}

static bool test_auth_timeout(void) {
    Pair p = make_auth_pair(300u); /* 300 ms auth budget */
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));
    /* never authenticate: the server must close with AUTH reason */
    g_want_event = BREAK_NET_QUIC_EVENT_DISCONNECT;
    ASSERT_TRUE(pump_until(&p, cond_server_event_auth, 5000u));
    ASSERT_EQ_U(p.first_event.reason, BREAK_NET_QUIC_DISCONNECT_AUTH);
    free_pair(&p);
    return true;
}

/* ---- RFC 9221 datagram channel -------------------------------------------- */

typedef struct {
    u8 last_type;
    u64 last_sequence;
    u32 last_len;
    u8 last_payload[1200];
    u32 count;
    u64 dropped;
} DatagramCapture;

static bool capture_datagram(BreakNetQuicConn *conn, u8 type, u64 sequence,
                             const u8 *payload, u32 payload_len, void *user) {
    DatagramCapture *cap = (DatagramCapture *)user;
    if (getenv("BNQ_DEBUG") != NULL) {
        fprintf(stderr, "DBG capture_datagram called, user=%p count=%u\n",
                user, cap->count);
    }
    (void)conn;
    cap->last_type = type;
    cap->last_sequence = sequence;
    cap->last_len = payload_len;
    if (payload_len > 0u && payload_len <= sizeof(cap->last_payload)) {
        memcpy(cap->last_payload, payload, payload_len);
    }
    cap->count++;
    return true;
}

static bool test_datagram_echo(void) {
    Pair p = make_auth_pair(0u); /* datagrams require authentication */
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));

    /* 注册数据报回调 */
    DatagramCapture server_cap = {0}, client_cap = {0};
    if (getenv("BNQ_DEBUG") != NULL) {
        fprintf(stderr, "DBG test: server_cap=%p\n", (void *)&server_cap);
    }
    break_net_quic_server_set_datagram_handler(p.server, capture_datagram,
                                               &server_cap);
    break_net_quic_client_set_datagram_handler(p.client, capture_datagram,
                                               &client_cap);

    /* 完成认证（CHALLENGE/AUTH-v2 在可靠流上） */
    bool authed = false;
    for (u32 i = 0u; i < 2500u && !authed; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        if (break_net_quic_client_handshake_done(p.client)) {
            authed = break_net_quic_client_authenticate(p.client, k_test_key_id,
                                                        k_test_psk);
        }
    }
    ASSERT_TRUE(authed);

    /* 等待服务器认证完成 */
    g_want_event = BREAK_NET_QUIC_EVENT_AUTHENTICATED;
    ASSERT_TRUE(pump_until(&p, cond_server_event_auth, 5000u));
    BreakNetQuicConn *conn = break_net_quic_server_conn(p.server,
                                                        p.first_event.conn_id);
    ASSERT_TRUE(conn != NULL);
    p.has_first_event = false;

    /* 客户端发数据报给服务器 */
    const char *voice_frame = "voice-frame-0";
    ASSERT_TRUE(break_net_quic_client_datagram_send(p.client, 1u,
                                                    (const u8 *)voice_frame,
                                                    13u));

    /* 驱动直到服务器收到数据报 */
    for (u32 i = 0u; i < 2500u && server_cap.count == 0u; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
    }
    if (getenv("BNQ_DEBUG") != NULL) {
        fprintf(stderr, "DBG after loop: server_cap.count=%u\n", server_cap.count);
    }
    ASSERT_TRUE(server_cap.count >= 1u);
    ASSERT_EQ_U(server_cap.last_type, 1u);
    ASSERT_EQ_U(server_cap.last_sequence, 1u); /* 第一个数据报 */
    ASSERT_EQ_U(server_cap.last_len, 13u);
    ASSERT_TRUE(memcmp(server_cap.last_payload, voice_frame, 13u) == 0);

    /* 服务器回发数据报给客户端 */
    const char *reply = "voice-ack-0";
    ASSERT_TRUE(break_net_quic_datagram_send(p.server, conn, 2u,
                                             (const u8 *)reply, 11u));
    for (u32 i = 0u; i < 2500u && client_cap.count == 0u; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
    }
    ASSERT_TRUE(client_cap.count >= 1u);
    ASSERT_EQ_U(client_cap.last_type, 2u);
    ASSERT_EQ_U(client_cap.last_sequence, 1u);
    ASSERT_EQ_U(client_cap.last_len, 11u);
    ASSERT_TRUE(memcmp(client_cap.last_payload, reply, 11u) == 0);

    free_pair(&p);
    return true;
}

static bool test_datagram_size_boundary(void) {
    Pair p = make_auth_pair(0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));

    DatagramCapture cap = {0};
    break_net_quic_client_set_datagram_handler(p.client, capture_datagram,
                                               &cap);

    bool authed = false;
    for (u32 i = 0u; i < 2500u && !authed; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        if (break_net_quic_client_handshake_done(p.client)) {
            authed = break_net_quic_client_authenticate(p.client, k_test_key_id,
                                                        k_test_psk);
        }
    }
    ASSERT_TRUE(authed);

    /* 1200 字节：接受 */
    u8 payload[1200];
    memset(payload, 0xA5, sizeof(payload));
    ASSERT_TRUE(break_net_quic_client_datagram_send(p.client, 1u, payload,
                                                    sizeof(payload)));

    /* 1201 字节：拒绝（超过 MTU 边界） */
    u8 oversize[1201];
    memset(oversize, 0x5A, sizeof(oversize));
    ASSERT_FALSE(break_net_quic_client_datagram_send(p.client, 1u, oversize,
                                                     sizeof(oversize)));

    free_pair(&p);
    return true;
}

static bool test_datagram_unauthenticated_dropped(void) {
    Pair p = make_auth_pair(0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));

    DatagramCapture cap = {0};
    break_net_quic_server_set_datagram_handler(p.server, capture_datagram,
                                               &cap);

    /* 未认证就发数据报：服务器应该丢弃（计数）。发送可能暂时被拥塞控制
     * 拒绝（AGAIN），重试直到发出或超时。 */
    const char *noise = "unauth-noise";
    bool sent = false;
    for (u32 i = 0u; i < 2500u && !sent; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        sent = break_net_quic_client_datagram_send(p.client, 1u,
                                                   (const u8 *)noise, 12u);
    }
    ASSERT_TRUE(sent);

    for (u32 i = 0u; i < 2500u; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
    }
    /* 服务器不应该收到任何数据报（未认证被丢弃） */
    ASSERT_EQ_U(cap.count, 0u);

    free_pair(&p);
    return true;
}

/* ---- replay-window integration through a real UDP proxy ------------------- */

static bool proxy_pair_step(Pair *p, TestQuicUdpProxySet *proxies) {
    if (!test_quic_udp_proxy_set_step(proxies, 0u)) {
        return false;
    }
    break_net_quic_server_step(p->server, 1u);
    break_net_quic_client_step(p->client, 1u);
    return test_quic_udp_proxy_set_step(proxies, 0u);
}

static bool proxy_datagram_send(Pair *p, TestQuicUdpProxySet *proxies,
                                u64 sequence, u8 payload) {
    for (u32 round = 0u; round < 2500u; ++round) {
        /* A congested send consumes its local number before returning false.
         * Reset on every attempt so this deterministic test never skips. */
        if (!break_net_quic_client_set_next_datagram_sequence_for_test(
                p->client, sequence)) {
            return false;
        }
        if (break_net_quic_client_datagram_send(p->client, 7u, &payload, 1u)) {
            return true;
        }
        if (!proxy_pair_step(p, proxies)) {
            return false;
        }
    }
    return false;
}

static bool test_datagram_replay_window_integration(void) {
    Pair p;
    memset(&p, 0, sizeof(p));
    BreakNetQuicServerConfig server_config;
    memset(&server_config, 0, sizeof(server_config));
    server_config.cert_file = kCert;
    server_config.key_file = kKey;
    server_config.alpn = kAlpn;
    server_config.port = 0u;
    server_config.max_connections = 1u;
    p.server = break_net_quic_server_create(&server_config);
    ASSERT_TRUE(p.server != NULL);
    ASSERT_TRUE(break_net_quic_server_set_auth(p.server, test_key_fn,
                                               (void *)k_test_psk, 0u));

    DatagramCapture capture;
    memset(&capture, 0, sizeof(capture));
    break_net_quic_server_set_datagram_handler(p.server, capture_datagram,
                                               &capture);

    TestQuicUdpProxySet *proxies = NULL;
    ASSERT_TRUE(test_quic_udp_proxy_set_create(
        break_net_quic_server_port(p.server), 1u, &proxies));
    BreakNetQuicClientConfig client_config;
    memset(&client_config, 0, sizeof(client_config));
    client_config.host = "127.0.0.1";
    client_config.port = test_quic_udp_proxy_port(proxies, 0u);
    client_config.server_name = "localhost";
    client_config.trust_store_file = kCert;
    client_config.cert_file = kCert;
    client_config.key_file = kKey;
    client_config.alpn = kAlpn;
    p.client = break_net_quic_client_create(&client_config);
    ASSERT_TRUE(p.client != NULL);

    bool auth_sent = false;
    BreakNetQuicConn *conn = NULL;
    for (u32 round = 0u; round < 6000u && conn == NULL; ++round) {
        ASSERT_TRUE(proxy_pair_step(&p, proxies));
        if (!auth_sent && break_net_quic_client_handshake_done(p.client)) {
            auth_sent = break_net_quic_client_authenticate(p.client,
                                                           k_test_key_id,
                                                           k_test_psk);
        }
        BreakNetQuicEvent event;
        while (break_net_quic_server_poll_event(p.server, &event)) {
            if (event.type == BREAK_NET_QUIC_EVENT_AUTHENTICATED) {
                conn = break_net_quic_server_conn(p.server, event.conn_id);
            }
        }
    }
    ASSERT_TRUE(auth_sent);
    ASSERT_TRUE(conn != NULL);
    ASSERT_EQ_U(break_net_quic_conn_dropped_datagrams(conn), 0u);

    /* Send application sequence 1 twice in distinct, freshly protected QUIC
     * packets. A byte-identical UDP copy would be discarded by ngtcp2 itself
     * and would not exercise this module's replay window. */
    const u32 unique_datagrams = 66u;
    for (u32 sequence = 1u; sequence <= unique_datagrams; ++sequence) {
        u8 payload = (u8)sequence;
        ASSERT_TRUE(proxy_datagram_send(&p, proxies, sequence, payload));
        for (u32 round = 0u;
             round < 2500u && capture.count < sequence; ++round) {
            ASSERT_TRUE(proxy_pair_step(&p, proxies));
        }
        ASSERT_EQ_U(capture.count, sequence);
        ASSERT_EQ_U(capture.last_sequence, sequence);
        ASSERT_EQ_U(capture.last_type, 7u);
        ASSERT_EQ_U(capture.last_len, 1u);
        ASSERT_EQ_U(capture.last_payload[0], sequence);

        if (sequence == 1u) {
            ASSERT_TRUE(proxy_datagram_send(&p, proxies, 1u, payload));
            for (u32 round = 0u;
                 round < 2500u &&
                 break_net_quic_conn_dropped_datagrams(conn) < 1u; ++round) {
                ASSERT_TRUE(proxy_pair_step(&p, proxies));
            }
            ASSERT_EQ_U(break_net_quic_conn_dropped_datagrams(conn), 1u);
            ASSERT_EQ_U(capture.count, 1u); /* duplicate was not delivered */
        }
    }

    /* After sequence 66, sequence 1 is 65 positions behind the highest and
     * therefore outside the 64-bit window. It still travels in a new QUIC
     * packet through the proxy, but must not reach the application callback. */
    ASSERT_TRUE(proxy_datagram_send(&p, proxies, 1u, 1u));
    TestQuicUdpProxyStats stats;
    memset(&stats, 0, sizeof(stats));
    for (u32 round = 0u; round < 2500u; ++round) {
        ASSERT_TRUE(proxy_pair_step(&p, proxies));
        test_quic_udp_proxy_set_stats(proxies, 0u, &stats);
        if (break_net_quic_conn_dropped_datagrams(conn) == 2u &&
            stats.queued == 0u) {
            break;
        }
    }
    ASSERT_EQ_U(capture.count, unique_datagrams);
    ASSERT_EQ_U(capture.last_sequence, unique_datagrams);
    ASSERT_EQ_U(break_net_quic_conn_dropped_datagrams(conn), 2u);
    ASSERT_EQ_U(stats.dropped, 0u);
    ASSERT_EQ_U(stats.queued, 0u);
    ASSERT_TRUE(stats.forwarded >= unique_datagrams + 2u);

    free_pair(&p);
    test_quic_udp_proxy_set_destroy(&proxies);
    return true;
}

/* ---- voice over QUIC datagram --------------------------------------------- */

static bool test_voice_over_quic_datagram(void) {
    Pair p = make_auth_pair(0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));

    /* 创建语音接收器（服务器和客户端各一个） */
    BreakVoiceReceiver *server_rx = NULL;
    BreakVoiceReceiver *client_rx = NULL;
    BreakVoiceStreamConfig voice_cfg;
    memset(&voice_cfg, 0, sizeof(voice_cfg));
    voice_cfg.sample_rate = 16000u;
    voice_cfg.channels = 1u;
    voice_cfg.sample_count = 160u;
    voice_cfg.jitter_delay_ms = 20u;
    voice_cfg.jitter_capacity = 8u;
    voice_cfg.queue_capacity = 16u;
    ASSERT_TRUE(break_voice_receiver_create(NULL, &voice_cfg, &server_rx) ==
                BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_voice_receiver_create(NULL, &voice_cfg, &client_rx) ==
                BREAK_RUNTIME_OK);

    /* 注册语音接收器到 QUIC 数据报通道 */
    break_voice_quic_attach_receiver_server(p.server, server_rx);
    break_voice_quic_attach_receiver(p.client, client_rx);

    /* 完成认证 */
    bool authed = false;
    for (u32 i = 0u; i < 2500u && !authed; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        if (break_net_quic_client_handshake_done(p.client)) {
            authed = break_net_quic_client_authenticate(p.client, k_test_key_id,
                                                        k_test_psk);
        }
    }
    ASSERT_TRUE(authed);

    g_want_event = BREAK_NET_QUIC_EVENT_AUTHENTICATED;
    ASSERT_TRUE(pump_until(&p, cond_server_event_auth, 5000u));
    BreakNetQuicConn *conn = break_net_quic_server_conn(p.server,
                                                        p.first_event.conn_id);
    ASSERT_TRUE(conn != NULL);
    p.has_first_event = false;

    /* 构造一帧语音并发送（BRV1 编码） */
    BreakVoiceFrame frame;
    memset(&frame, 0, sizeof(frame));
    frame.sequence = 1u;
    frame.sample_rate = 16000u;
    frame.channels = 1u;
    frame.sample_count = 160u;
    for (u32 i = 0u; i < 160u; i++) {
        frame.samples[i] = (i16)(i * 100); /* 简单的斜坡信号 */
    }
    ASSERT_TRUE(break_voice_quic_send(p.client, &frame, false));

    /* 驱动直到服务器收到语音帧。注意：inbox 接收与 jitter buffer 入队是
     * 两个阶段——数据报进 inbox 后需要 pump 才会被解码入队。 */
    BreakVoiceReceiverStats stats;
    u64 now_ms = 1000u;
    for (u32 i = 0u; i < 2500u; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        break_voice_receiver_pump(server_rx, 16u, now_ms);
        now_ms += 1u;
        if (break_voice_receiver_stats(server_rx, &stats) == BREAK_RUNTIME_OK &&
            stats.accepted >= 1u) {
            break;
        }
    }
    ASSERT_TRUE(stats.accepted >= 1u);

    /* 服务器回发一帧语音给客户端 */
    frame.sequence = 2u;
    ASSERT_TRUE(break_voice_quic_send_server(p.server, conn, &frame, false));
    for (u32 i = 0u; i < 2500u; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        break_voice_receiver_pump(client_rx, 16u, now_ms);
        now_ms += 1u;
        if (break_voice_receiver_stats(client_rx, &stats) == BREAK_RUNTIME_OK &&
            stats.accepted >= 1u) {
            break;
        }
    }
    ASSERT_TRUE(stats.accepted >= 1u);

    break_voice_receiver_destroy(server_rx);
    break_voice_receiver_destroy(client_rx);
    free_pair(&p);
    return true;
}

/* ---- lobby over QUIC authenticated session -------------------------------- */

static bool test_lobby_quic_auth_source(void) {
    Pair p = make_auth_pair(0u);
    ASSERT_TRUE(p.server != NULL && p.client != NULL);
    ASSERT_TRUE(pump_until(&p, cond_handshake, 5000u));

    /* 完成认证 */
    bool authed = false;
    for (u32 i = 0u; i < 2500u && !authed; i++) {
        break_net_quic_server_step(p.server, 1u);
        break_net_quic_client_step(p.client, 1u);
        if (break_net_quic_client_handshake_done(p.client)) {
            authed = break_net_quic_client_authenticate(p.client, k_test_key_id,
                                                        k_test_psk);
        }
    }
    ASSERT_TRUE(authed);

    g_want_event = BREAK_NET_QUIC_EVENT_AUTHENTICATED;
    ASSERT_TRUE(pump_until(&p, cond_server_event_auth, 5000u));
    u32 conn_id = p.first_event.conn_id;
    p.has_first_event = false;

    /* 创建 lobby，用 QUIC 认证源 */
    BreakLobbyConfig lobby_cfg;
    memset(&lobby_cfg, 0, sizeof(lobby_cfg));
    lobby_cfg.max_rooms = 8u;
    lobby_cfg.max_members_per_room = 4u;
    BreakLobby *lobby = NULL;
    ASSERT_TRUE(break_lobby_create(&lobby_cfg, &lobby) == BREAK_RUNTIME_OK);

    BreakOnlineAuthSource auth = break_online_session_quic_auth(p.server);

    /* 认证后的 conn_id 可以创建房间 */
    BreakLobbyAuth la;
    la.session = conn_id;
    la.source = auth;
    BreakOnlineHandle room;
    BreakOnlineMemberHandle member;
    BreakLobbyRoomDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.name = "quic-test-room";
    desc.region = 1u;
    desc.mode = 1u;
    desc.max_members = 4u;
    desc.listed = true;
    ASSERT_TRUE(break_lobby_room_create(lobby, &la, &desc, &room, &member) ==
                BREAK_RUNTIME_OK);
    /* handle.index 从 0 开始（第一个房间）；验证 handle 有效即可 */
    ASSERT_TRUE(break_online_handle_valid(room));

    /* 未认证的 conn_id（比如 999）被拒绝 */
    la.session = 999u;
    BreakOnlineHandle bad_room;
    ASSERT_FALSE(break_lobby_room_create(lobby, &la, &desc, &bad_room,
                                         &member) == BREAK_RUNTIME_OK);

    break_lobby_destroy(lobby);
    free_pair(&p);
    return true;
}

/* ---- three-client voice conference over QUIC ------------------------------ */

#define CONFERENCE_CLIENTS 3u

typedef struct {
    BreakNetQuicClient *client;
    BreakVoiceReceiver *receiver;
    bool auth_sent;
} ConferenceClient;

typedef struct {
    BreakVoiceMixer *mixer;
    BreakNetQuicConn *connections[CONFERENCE_CLIENTS];
    u32 connection_count;
    u64 now_ms;
} ConferenceServer;

/* The server has one global datagram callback. Route each authenticated voice
 * datagram directly into the mixer, keyed by its stable connection id. */
static bool conference_receive_voice(BreakNetQuicConn *conn, u8 type,
                                     u64 sequence, const u8 *payload,
                                     u32 payload_len, void *user) {
    ConferenceServer *conference = (ConferenceServer *)user;
    (void)sequence;
    if (type != BREAK_VOICE_QUIC_MSG_TYPE) {
        return true;
    }
    return break_voice_mixer_push(conference->mixer,
                                  break_net_quic_conn_id(conn), payload,
                                  payload_len, conference->now_ms) ==
           BREAK_RUNTIME_OK;
}

static bool conference_step(BreakNetQuicServer *server,
                            ConferenceClient clients[CONFERENCE_CLIENTS],
                            TestQuicUdpProxySet *proxies) {
    if (proxies != NULL && !test_quic_udp_proxy_set_step(proxies, 0u)) {
        return false;
    }
    break_net_quic_server_step(server, 1u);
    for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
        break_net_quic_client_step(clients[i].client, 1u);
    }
    return proxies == NULL || test_quic_udp_proxy_set_step(proxies, 0u);
}

static bool conference_client_send_voice(BreakNetQuicServer *server,
                                         ConferenceClient clients[CONFERENCE_CLIENTS],
                                         TestQuicUdpProxySet *proxies, u32 index,
                                         const BreakVoiceFrame *frame) {
    for (u32 round = 0u; round < 2500u; ++round) {
        if (break_voice_quic_send(clients[index].client, frame, false)) {
            return true;
        }
        if (!conference_step(server, clients, proxies)) {
            return false;
        }
    }
    return false;
}

static bool conference_server_send_voice(BreakNetQuicServer *server,
                                         ConferenceClient clients[CONFERENCE_CLIENTS],
                                         TestQuicUdpProxySet *proxies,
                                         BreakNetQuicConn *conn,
                                         const BreakVoiceFrame *frame) {
    for (u32 round = 0u; round < 2500u; ++round) {
        if (break_voice_quic_send_server(server, conn, frame, false)) {
            return true;
        }
        if (!conference_step(server, clients, proxies)) {
            return false;
        }
    }
    return false;
}

static bool conference_direction_drained(TestQuicUdpProxySet *proxies,
                                         u32 direction, u32 sent_per_client) {
    if (proxies == NULL) {
        return true;
    }
    for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
        TestQuicUdpProxyStats stats;
        test_quic_udp_proxy_set_stats(proxies, i, &stats);
        if (stats.received[direction] < sent_per_client || stats.queued != 0u) {
            return false;
        }
    }
    return true;
}

static bool run_voice_conference(bool impaired, bool random, u32 seed,
                                 u32 uplink_drop, u32 downlink_drop) {
    BreakNetQuicServerConfig server_config;
    memset(&server_config, 0, sizeof(server_config));
    server_config.cert_file = kCert;
    server_config.key_file = kKey;
    server_config.alpn = kAlpn;
    server_config.port = 0u;
    server_config.max_connections = CONFERENCE_CLIENTS;
    BreakNetQuicServer *server = break_net_quic_server_create(&server_config);
    ASSERT_TRUE(server != NULL);
    ASSERT_TRUE(break_net_quic_server_set_auth(server, test_key_fn,
                                               (void *)k_test_psk, 0u));
    TestQuicUdpProxySet *proxies = NULL;
    if (impaired) {
        ASSERT_TRUE(test_quic_udp_proxy_set_create(
            break_net_quic_server_port(server), CONFERENCE_CLIENTS, &proxies));
    }

    BreakVoiceMixerConfig mixer_config;
    memset(&mixer_config, 0, sizeof(mixer_config));
    mixer_config.stream.sample_rate = 16000u;
    mixer_config.stream.channels = 1u;
    mixer_config.stream.sample_count = 160u;
    mixer_config.stream.jitter_delay_ms = 20u;
    mixer_config.stream.jitter_capacity = 8u;
    mixer_config.stream.queue_capacity = 16u;
    mixer_config.max_sources = CONFERENCE_CLIENTS;
    mixer_config.idle_timeout_ms = 1000u;

    ConferenceServer conference;
    memset(&conference, 0, sizeof(conference));
    conference.now_ms = 1000u;
    ASSERT_TRUE(break_voice_mixer_create(&mixer_config, &conference.mixer) ==
                BREAK_RUNTIME_OK);
    break_net_quic_server_set_datagram_handler(server, conference_receive_voice,
                                               &conference);

    ConferenceClient clients[CONFERENCE_CLIENTS];
    memset(clients, 0, sizeof(clients));
    for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
        BreakNetQuicClientConfig client_config;
        memset(&client_config, 0, sizeof(client_config));
        client_config.host = "127.0.0.1";
        client_config.port = impaired ? test_quic_udp_proxy_port(proxies, i)
                                      : break_net_quic_server_port(server);
        client_config.server_name = "localhost";
        client_config.trust_store_file = kCert;
        client_config.cert_file = kCert;
        client_config.key_file = kKey;
        client_config.alpn = kAlpn;
        clients[i].client = break_net_quic_client_create(&client_config);
        ASSERT_TRUE(clients[i].client != NULL);
        ASSERT_TRUE(break_voice_receiver_create(NULL, &mixer_config.stream,
                                                &clients[i].receiver) ==
                    BREAK_RUNTIME_OK);
        break_voice_quic_attach_receiver(clients[i].client, clients[i].receiver);
    }

    /* Authenticate all clients and retain the three server-side connections.
     * Authenticate can return false until CHALLENGE arrives, so keep polling. */
    for (u32 round = 0u; round < 6000u; ++round) {
        ASSERT_TRUE(conference_step(server, clients, proxies));
        bool all_auth_sent = true;
        for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
            if (!clients[i].auth_sent &&
                break_net_quic_client_handshake_done(clients[i].client)) {
                clients[i].auth_sent = break_net_quic_client_authenticate(
                    clients[i].client, k_test_key_id, k_test_psk);
            }
            all_auth_sent = all_auth_sent && clients[i].auth_sent;
        }
        conference.now_ms += 1u;
        BreakNetQuicEvent event;
        while (break_net_quic_server_poll_event(server, &event)) {
            if (event.type == BREAK_NET_QUIC_EVENT_AUTHENTICATED &&
                conference.connection_count < CONFERENCE_CLIENTS) {
                BreakNetQuicConn *conn =
                    break_net_quic_server_conn(server, event.conn_id);
                ASSERT_TRUE(conn != NULL);
                ASSERT_EQ_U(break_net_quic_conn_id(conn), event.conn_id);
                conference.connections[conference.connection_count++] = conn;
            }
        }
        if (all_auth_sent &&
            conference.connection_count == CONFERENCE_CLIENTS) {
            break;
        }
    }
    ASSERT_EQ_U(conference.connection_count, CONFERENCE_CLIENTS);
    ASSERT_EQ_U(break_net_quic_conn_id(NULL), 0u);

    /* Impair only post-auth traffic. Deterministic mode drops every fourth
     * packet and uses 15/30 ms delays; random mode applies the scenario's
     * per-direction loss rates with 0..20 ms seeded jitter. */
    const u32 frame_count = !impaired ? 1u : (random ? 6u : 4u);
    if (random) {
        test_quic_udp_proxy_set_impairment(proxies, true, 0u, 0u, false);
        test_quic_udp_proxy_set_random(proxies, true, seed, uplink_drop,
                                       downlink_drop, 20u);
    } else if (impaired) {
        test_quic_udp_proxy_set_impairment(proxies, true, 4u, 15u, true);
    }

    /* Each participant contributes constant PCM: 1000, 2000, or 3000. Weak-net
     * runs send multiple frames so packet impairments affect real BRV1 data. */
    for (u32 sequence = 1u; sequence <= frame_count; ++sequence) {
        for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
            BreakVoiceFrame frame;
            memset(&frame, 0, sizeof(frame));
            frame.sequence = sequence;
            frame.sample_rate = 16000u;
            frame.channels = 1u;
            frame.sample_count = 160u;
            for (u32 sample = 0u; sample < 160u; ++sample) {
                frame.samples[sample] = (i16)((i + 1u) * 1000u);
            }
            ASSERT_TRUE(conference_client_send_voice(server, clients, proxies,
                                                     i, &frame));
        }
        ASSERT_TRUE(conference_step(server, clients, proxies));
        conference.now_ms += 1u;
    }

    BreakVoiceMixerStats mixer_stats;
    memset(&mixer_stats, 0, sizeof(mixer_stats));
    for (u32 round = 0u; round < 5000u; ++round) {
        ASSERT_TRUE(conference_step(server, clients, proxies));
        conference.now_ms += 1u;
        ASSERT_TRUE(break_voice_mixer_stats(conference.mixer, &mixer_stats) ==
                    BREAK_RUNTIME_OK);
        if (mixer_stats.accepted >= CONFERENCE_CLIENTS &&
            conference_direction_drained(proxies, 0u, frame_count)) {
            break;
        }
    }
    ASSERT_EQ_U(mixer_stats.sources, CONFERENCE_CLIENTS);
    ASSERT_TRUE(mixer_stats.accepted >= CONFERENCE_CLIENTS);
    if (!impaired) {
        ASSERT_EQ_U(mixer_stats.accepted, CONFERENCE_CLIENTS);
    }
    ASSERT_EQ_U(mixer_stats.invalid, 0u);
    ASSERT_TRUE(conference_direction_drained(proxies, 0u, frame_count));

    conference.now_ms += mixer_config.stream.jitter_delay_ms + 1u;
    BreakVoicePlayback mixed;
    bool mixed_ready = false;
    ASSERT_TRUE(break_voice_mixer_pop(conference.mixer, conference.now_ms,
                                      &mixed, &mixed_ready) == BREAK_RUNTIME_OK);
    ASSERT_TRUE(mixed_ready);
    ASSERT_FALSE(mixed.concealed);
    ASSERT_EQ_U(mixed.sample_count, 160u);
    for (u32 sample = 0u; sample < mixed.sample_count; ++sample) {
        ASSERT_EQ_U(mixed.samples[sample], 6000);
    }

    BreakVoiceFrame output;
    memset(&output, 0, sizeof(output));
    output.sample_rate = 16000u;
    output.channels = 1u;
    output.sample_count = mixed.sample_count;
    memcpy(output.samples, mixed.samples, sizeof(output.samples));
    for (u32 frame = 0u; frame < frame_count; ++frame) {
        output.sequence = mixed.sequence + frame;
        for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
            ASSERT_TRUE(conference_server_send_voice(
                server, clients, proxies, conference.connections[i], &output));
        }
        ASSERT_TRUE(conference_step(server, clients, proxies));
        conference.now_ms += 1u;
    }

    bool all_received = false;
    for (u32 round = 0u; round < 5000u; ++round) {
        ASSERT_TRUE(conference_step(server, clients, proxies));
        all_received = true;
        for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
            break_voice_receiver_pump(clients[i].receiver, 16u,
                                      conference.now_ms);
            BreakVoiceReceiverStats stats;
            ASSERT_TRUE(break_voice_receiver_stats(clients[i].receiver, &stats) ==
                        BREAK_RUNTIME_OK);
            all_received = all_received && stats.accepted >= 1u;
        }
        conference.now_ms += 1u;
        if (all_received &&
            conference_direction_drained(proxies, 1u, frame_count)) {
            break;
        }
    }
    ASSERT_TRUE(all_received);
    ASSERT_TRUE(conference_direction_drained(proxies, 1u, frame_count));

    conference.now_ms += mixer_config.stream.jitter_delay_ms + 1u;
    for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
        BreakVoicePlayback playback;
        bool ready = false;
        ASSERT_TRUE(break_voice_receiver_pop(clients[i].receiver,
                                             conference.now_ms, &playback,
                                             &ready) == BREAK_RUNTIME_OK);
        ASSERT_TRUE(ready);
        ASSERT_EQ_U(playback.sample_count, 160u);
        for (u32 sample = 0u; sample < playback.sample_count; ++sample) {
            ASSERT_EQ_U(playback.samples[sample], 6000);
        }
    }

    if (impaired) {
        u64 direction_drops[TEST_QUIC_UDP_PROXY_STATS_DIRS] = {0u, 0u};
        u64 direction_jitter[TEST_QUIC_UDP_PROXY_STATS_DIRS] = {0u, 0u};
        for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
            TestQuicUdpProxyStats stats;
            test_quic_udp_proxy_set_stats(proxies, i, &stats);
            ASSERT_TRUE(stats.received[0] >= frame_count);
            ASSERT_TRUE(stats.received[1] >= frame_count);
            if (random) {
                for (u32 direction = 0u;
                     direction < TEST_QUIC_UDP_PROXY_STATS_DIRS; ++direction) {
                    direction_drops[direction] += stats.dropped_by_direction[direction];
                    direction_jitter[direction] +=
                        stats.jittered_by_direction[direction];
                }
            } else {
                ASSERT_TRUE(stats.dropped >= 2u);   /* uplink + downlink loss */
                ASSERT_TRUE(stats.delayed >= 6u);   /* surviving frames */
                ASSERT_TRUE(stats.reordered >= 2u); /* both directions */
            }
        }
        if (random) {
            if (uplink_drop >= 25u) {
                ASSERT_TRUE(direction_drops[0] > 0u);
            }
            if (downlink_drop >= 25u) {
                ASSERT_TRUE(direction_drops[1] > 0u);
            }
            ASSERT_TRUE(direction_jitter[0] > 0u);
            ASSERT_TRUE(direction_jitter[1] > 0u);
        }
    }

    break_voice_mixer_destroy(conference.mixer);
    for (u32 i = 0u; i < CONFERENCE_CLIENTS; ++i) {
        break_voice_receiver_destroy(clients[i].receiver);
        break_net_quic_client_destroy(&clients[i].client);
    }
    break_net_quic_server_destroy(&server);
    test_quic_udp_proxy_set_destroy(&proxies);
    return true;
}

static bool test_voice_conference(void) {
    return run_voice_conference(false, false, 0u, 0u, 0u);
}

static bool test_voice_conference_weak_network(void) {
    return run_voice_conference(true, false, 0u, 0u, 0u);
}

static bool test_voice_conference_seeded_weak_network(void) {
    return run_voice_conference(true, true, 0xB5EED123u, 25u, 25u);
}

static bool test_voice_conference_seeded_uplink_loss(void) {
    return run_voice_conference(true, true, 0xA11CE002u, 40u, 5u);
}

static bool test_voice_conference_seeded_downlink_loss(void) {
    return run_voice_conference(true, true, 0xD00D1003u, 5u, 40u);
}

/* ---- runner --------------------------------------------------------------- */

typedef bool (*TestFn)(void);
typedef struct {
    const char *name;
    TestFn fn;
} TestCase;

int main(void) {
    static const TestCase tests[] = {
        {"config_validation", test_config_validation},
        {"handshake_echo", test_handshake_echo},
        {"sequential_messages", test_sequential_messages},
        {"message_size_cap", test_message_size_cap},
        {"wrong_alpn_fails_closed", test_wrong_alpn_fails_closed},
        {"wrong_server_name_fails_closed", test_wrong_server_name_fails_closed},
        {"slot_table_full", test_slot_table_full},
        {"graceful_close_events", test_graceful_close_events},
        {"auth_roundtrip", test_auth_roundtrip},
        {"auth_wrong_psk_fails_closed", test_auth_wrong_psk_fails_closed},
        {"auth_preauth_noise_fails_closed", test_auth_preauth_noise_fails_closed},
        {"auth_timeout", test_auth_timeout},
        {"datagram_echo", test_datagram_echo},
        {"datagram_size_boundary", test_datagram_size_boundary},
        {"datagram_unauthenticated_dropped", test_datagram_unauthenticated_dropped},
        {"datagram_replay_window_integration", test_datagram_replay_window_integration},
        {"voice_over_quic_datagram", test_voice_over_quic_datagram},
        {"lobby_quic_auth_source", test_lobby_quic_auth_source},
        {"voice_conference", test_voice_conference},
        {"voice_conference_weak_network", test_voice_conference_weak_network},
        {"voice_conference_seeded_weak_network", test_voice_conference_seeded_weak_network},
        {"voice_conference_seeded_uplink_loss", test_voice_conference_seeded_uplink_loss},
        {"voice_conference_seeded_downlink_loss", test_voice_conference_seeded_downlink_loss},
    };
    size_t passed = 0;
    size_t total = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0u; i < total; i++) {
        int before = g_failures;
        bool ok = tests[i].fn();
        if (ok && g_failures == before) {
            printf("PASS %s\n", tests[i].name);
            passed++;
        } else {
            printf("FAIL %s\n", tests[i].name);
        }
    }
    printf("%zu/%zu passed\n", passed, total);
    return passed == total ? 0 : 1;
}
