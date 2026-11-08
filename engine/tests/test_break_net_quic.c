/* test_break_net_quic — loopback evidence for break_net_quic
 * (docs/design/quic_transport.md). Real UDP sockets on 127.0.0.1 with port-0
 * binds; both endpoints step alternately from the test thread; every wait is
 * condition-polled with a deadline (no fixed sleeps). */

#include "network/break_net_quic.h"

#include <stdio.h>
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
