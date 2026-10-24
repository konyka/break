/* TLS transport-mode tests for the Snowflake-backed Break network adapter.
 *
 * Every loopback test runs a THREAD-mode reactor with a port-0 acceptor and a
 * raw POSIX socket client whose TLS side is an in-test snow_ssl_t (client
 * role); the搬运 loop is socket read -> snow_ssl_do_handshake/snow_ssl_read ->
 * socket write.  Synchronization is condition-polling with deadlines only.
 *
 * Fixture PEMs live in the pinned Snowflake tree (no copies):
 * BREAK_TEST_SSL_FIXTURE_DIR is injected by CMake and points at
 * ${SNOWFLAKE_SOURCE_DIR}/tests/common/fixtures/ssl (CN=localhost self-signed,
 * test-only). */
#include "test_framework.h"
#include <network/break_net_adapter.h>
#include <network/break_net_envelope.h>
#include <network/break_net_events.h>
#include <network/break_net_message.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>
#include <snow/network_buffer.h>
#include <snow/openssl.h>
#include <arpa/inet.h>
#include <poll.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

extern int clock_gettime(int, struct timespec *);
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
extern int usleep(unsigned int);
extern ssize_t recv(int, void *, size_t, int);
extern ssize_t send(int, const void *, size_t, int);

#ifndef BREAK_TEST_SSL_FIXTURE_DIR
#error "BREAK_TEST_SSL_FIXTURE_DIR must be defined by the build system"
#endif
#define BREAK_TLS_STR2(x) #x
#define BREAK_TLS_STR(x) BREAK_TLS_STR2(x)
static const char *const k_fixture_dir = BREAK_TLS_STR(BREAK_TEST_SSL_FIXTURE_DIR);

#define TLS_TEST_DEADLINE_US UINT64_C(5000000)
#define TLS_TEST_RAWLOG_CAPACITY 65536u

static uint64_t tls_test_monotonic_us(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint64_t)now.tv_sec * UINT64_C(1000000) +
           (uint64_t)now.tv_nsec / UINT64_C(1000);
}

static void tls_test_fixture_path(char *out, size_t cap, const char *name)
{
    snprintf(out, cap, "%s/%s", k_fixture_dir, name);
}

static BreakNetReactorConfig tls_test_config(void)
{
    BreakNetReactorConfig config = {0};
    config.drive_mode = BREAK_NET_DRIVE_THREAD;
    config.logical_index = 0;
    config.max_connections = 16u;
    config.empty_connection_timeout_ms = 1000;
    config.watchdog_interval_ms = 1000u;
    config.step_timeout_ms = 10u;
    return config;
}

static snow_acceptor_t *tls_test_acceptor(void)
{
    snow_endpoint_t *endpoint = NULL;
    snow_acceptor_t *acceptor = NULL;
    if (snow_endpoint_create(&endpoint) != SNOW_OK ||
        snow_endpoint_set_host(endpoint, "127.0.0.1") != SNOW_OK ||
        snow_endpoint_set_port(endpoint, 0) != SNOW_OK ||
        snow_acceptor_create(endpoint, &acceptor) != SNOW_OK) {
        snow_endpoint_destroy(endpoint);
        return NULL;
    }
    snow_endpoint_destroy(endpoint);
    if (snow_acceptor_bind(acceptor, 1) != SNOW_OK) {
        snow_acceptor_destroy(acceptor);
        return NULL;
    }
    return acceptor;
}

static int tls_test_connect(snow_acceptor_t *acceptor)
{
    const snow_endpoint_t *endpoint = snow_acceptor_endpoint(acceptor);
    struct sockaddr_in address = {0};
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons((uint16_t)snow_endpoint_port(endpoint));
    if (connect(fd, (const struct sockaddr *)&address, sizeof(address)) != 0) {
        close(fd);
        return -1;
    }
    return fd;
}

/* ------------------------------------------------------------------ */
/* In-test TLS client (raw socket + client-role snow_ssl_t)            */
/* ------------------------------------------------------------------ */

typedef struct TlsTestClient {
    int fd;
    snow_ssl_ctx_t *ctx;
    snow_ssl_t *ssl;
    unsigned char rawlog[TLS_TEST_RAWLOG_CAPACITY];
    size_t rawlog_len;
} TlsTestClient;

static bool tls_test_client_open(TlsTestClient *client, snow_acceptor_t *acceptor,
                                 bool with_client_cert)
{
    char cert[512];
    char key[512];
    snow_ssl_ctx_opts_t opts;
    memset(client, 0, sizeof(*client));
    memset(&opts, 0, sizeof(opts));
    client->fd = tls_test_connect(acceptor);
    if (client->fd < 0) return false;
    if (with_client_cert) {
        tls_test_fixture_path(cert, sizeof(cert), "snow_test_cert.pem");
        tls_test_fixture_path(key, sizeof(key), "snow_test_key.pem");
        opts.cert_file = cert;
        opts.key_file = key;
    }
    client->ctx = snow_ssl_ctx_new(&opts, NULL);
    if (client->ctx == NULL) { close(client->fd); return false; }
    client->ssl = snow_ssl_new(client->ctx);
    if (client->ssl == NULL ||
        snow_ssl_init(client->ssl, false) != SNOW_OK) {
        snow_ssl_free(client->ssl);
        snow_ssl_ctx_free(client->ctx);
        close(client->fd);
        return false;
    }
    return true;
}

static void tls_test_client_close(TlsTestClient *client)
{
    snow_ssl_free(client->ssl);
    snow_ssl_ctx_free(client->ctx);
    if (client->fd >= 0) close(client->fd);
    client->ssl = NULL;
    client->ctx = NULL;
    client->fd = -1;
}

/* Deadline-bounded readability wait: 1 readable, 0 timeout, -1 error. */
static int tls_test_wait_readable(int fd, uint64_t deadline_us)
{
    uint64_t now = tls_test_monotonic_us();
    struct pollfd pfd;
    int ms;
    int result;
    if (now >= deadline_us) return 0;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    ms = (int)((deadline_us - now) / UINT64_C(1000));
    if (ms <= 0) ms = 1;
    result = poll(&pfd, 1, ms);
    if (result < 0) return -1;
    if (result == 0) return 0;
    return (pfd.revents & (POLLIN | POLLERR | POLLHUP)) != 0 ? 1 : 0;
}

/* Drain the ciphertext accumulated in `out` to the socket. */
static bool tls_test_flush_out(int fd, snow_network_buffer_t *out)
{
    size_t size = snow_network_buffer_length(out);
    size_t offset = 0u;
    size_t copied = 0u;
    unsigned char *flat;
    if (size == 0u) return true;
    flat = (unsigned char *)malloc(size);
    if (flat == NULL) return false;
    if (snow_network_buffer_copy_to(out, flat, size, &copied) != SNOW_OK ||
        copied != size) {
        free(flat);
        return false;
    }
    snow_network_buffer_clear(out);
    while (offset < size) {
        ssize_t written = send(fd, flat + offset, size - offset, 0);
        if (written <= 0) {
            free(flat);
            return false;
        }
        offset += (size_t)written;
    }
    free(flat);
    return true;
}

/* Drive the client handshake to completion; every step is deadline-bounded. */
static bool tls_test_client_handshake(TlsTestClient *client, uint64_t deadline_us)
{
    snow_network_buffer_t *out = NULL;
    unsigned char buf[4096];
    bool ok = false;
    if (snow_network_buffer_create(&out) != SNOW_OK) return false;
    if (snow_ssl_do_handshake(client->ssl, out, NULL, 0u) != 0) goto done;
    if (!tls_test_flush_out(client->fd, out)) goto done;
    while (!snow_ssl_is_handshaked(client->ssl)) {
        ssize_t got;
        if (tls_test_wait_readable(client->fd, deadline_us) != 1) goto done;
        got = recv(client->fd, buf, sizeof(buf), 0);
        if (got <= 0) goto done;
        if (snow_ssl_do_handshake(client->ssl, out, buf, (size_t)got) != 0) goto done;
        if (!tls_test_flush_out(client->fd, out)) goto done;
    }
    ok = true;
done:
    snow_network_buffer_destroy(out);
    return ok;
}

/* Encrypt `size` plaintext bytes and write the ciphertext to the socket. */
static bool tls_test_client_send(TlsTestClient *client, const void *data, size_t size)
{
    snow_network_buffer_t *out = NULL;
    bool ok = false;
    if (snow_network_buffer_create(&out) != SNOW_OK) return false;
    if (snow_ssl_write(client->ssl, (const char *)data, size, out) == 0 &&
        tls_test_flush_out(client->fd, out)) {
        ok = true;
    }
    snow_network_buffer_destroy(out);
    return ok;
}

/* Read one raw burst (deadline-bounded), log it, decrypt into `plain`.
 * Returns 1 = bytes pumped, 0 = timeout, -1 = peer gone / TLS error. */
static int tls_test_client_pump(TlsTestClient *client, snow_network_buffer_t *plain,
                                uint64_t deadline_us)
{
    unsigned char buf[4096];
    ssize_t got;
    int ready = tls_test_wait_readable(client->fd, deadline_us);
    if (ready <= 0) return ready;
    got = recv(client->fd, buf, sizeof(buf), 0);
    if (got <= 0) return -1;
    if (client->rawlog_len + (size_t)got <= sizeof(client->rawlog)) {
        memcpy(client->rawlog + client->rawlog_len, buf, (size_t)got);
        client->rawlog_len += (size_t)got;
    }
    if (snow_ssl_read(client->ssl, buf, (size_t)got, plain) != 0) return -1;
    return 1;
}

/* True when the 0x42524b31 envelope magic (either byte order) appears. */
static bool tls_test_contains_magic(const unsigned char *data, size_t size)
{
    static const unsigned char le[] = {0x31u, 0x4bu, 0x52u, 0x42u};
    static const unsigned char be[] = {0x42u, 0x52u, 0x4bu, 0x31u};
    size_t i;
    for (i = 0u; i + 4u <= size; ++i) {
        if (memcmp(data + i, le, 4u) == 0 || memcmp(data + i, be, 4u) == 0)
            return true;
    }
    return false;
}

/* ------------------------------------------------------------------ */
/* Reactor event polling helpers (condition-polling, deadline-bounded) */
/* ------------------------------------------------------------------ */

typedef struct TlsTestEventWatch {
    bool saw_opened;
    bool saw_message;
    bool saw_close;
    uint64_t opened_key;
    BreakNetEvent message_event;
} TlsTestEventWatch;

/* Poll until the close event arrives or the deadline passes; records what was
 * seen.  The last MESSAGE_RECEIVED event is kept in message_event (owned by
 * the watch; caller releases). */
static void tls_test_watch_until_close(BreakNetReactor *reactor, uint64_t deadline_us,
                                       TlsTestEventWatch *watch)
{
    memset(watch, 0, sizeof(*watch));
    while (tls_test_monotonic_us() < deadline_us && !watch->saw_close) {
        BreakNetEvent event = {0};
        if (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED) {
                watch->saw_opened = true;
                watch->opened_key = event.connection_key;
            } else if (event.type == BREAK_NET_EVENT_MESSAGE_RECEIVED) {
                watch->saw_message = true;
                break_net_event_release(&watch->message_event);
                watch->message_event = event;
                memset(&event, 0, sizeof(event));
            } else if (event.type == BREAK_NET_EVENT_CONNECTION_CLOSED ||
                       event.type == BREAK_NET_EVENT_TRANSPORT_ERROR) {
                watch->saw_close = true;
            }
            break_net_event_release(&event);
        } else {
            usleep(1000u);
        }
    }
}

static bool tls_test_wait_opened(BreakNetReactor *reactor, uint64_t deadline_us,
                                 uint64_t *connection_key)
{
    while (tls_test_monotonic_us() < deadline_us) {
        BreakNetEvent event = {0};
        if (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            bool opened = event.type == BREAK_NET_EVENT_CONNECTION_OPENED;
            if (opened) *connection_key = event.connection_key;
            break_net_event_release(&event);
            if (opened) return true;
        } else {
            usleep(1000u);
        }
    }
    return false;
}

static bool tls_test_wait_identity_count(BreakNetReactor *reactor, size_t expected,
                                         uint64_t deadline_us)
{
    while (tls_test_monotonic_us() < deadline_us) {
        if (break_net_reactor_connection_identity_count_for_test(reactor) == expected)
            return true;
        usleep(1000u);
    }
    return false;
}

/* ------------------------------------------------------------------ */
/* Tests                                                               */
/* ------------------------------------------------------------------ */

TEST(break_net_tls_config_validation)
{
    char cert[512];
    char key[512];
    char mismatch[512];
    BreakNetReactorConfig config = tls_test_config();
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = tls_test_acceptor();
    BreakNetTlsConfig cfg = {0};
    tls_test_fixture_path(cert, sizeof(cert), "snow_test_cert.pem");
    tls_test_fixture_path(key, sizeof(key), "snow_test_key.pem");
    tls_test_fixture_path(mismatch, sizeof(mismatch), "snow_test_mismatch_key.pem");

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_FALSE(break_net_reactor_is_tls(NULL));
    ASSERT_FALSE(break_net_reactor_is_tls(reactor));
    ASSERT_FALSE(break_net_reactor_set_tls(NULL, &cfg));
    ASSERT_FALSE(break_net_reactor_set_tls(reactor, NULL));

    /* Missing cert / key. */
    cfg.key_file = key;
    ASSERT_FALSE(break_net_reactor_set_tls(reactor, &cfg));
    cfg.cert_file = cert;
    cfg.key_file = NULL;
    ASSERT_FALSE(break_net_reactor_set_tls(reactor, &cfg));

    /* Mismatched cert/key -> snow ctx factory fails closed -> false. */
    cfg.key_file = mismatch;
    ASSERT_FALSE(break_net_reactor_set_tls(reactor, &cfg));

    /* verify_peer=1 without a CA would silently degrade to verify-none. */
    cfg.key_file = key;
    cfg.verify_peer = 1;
    cfg.ca_file = NULL;
    ASSERT_FALSE(break_net_reactor_set_tls(reactor, &cfg));

    /* Valid configuration sticks. */
    cfg.verify_peer = 0;
    ASSERT_TRUE(break_net_reactor_set_tls(reactor, &cfg));
    ASSERT_TRUE(break_net_reactor_is_tls(reactor));

    /* Second configuration rejected (single CREATED-state application). */
    ASSERT_FALSE(break_net_reactor_set_tls(reactor, &cfg));

    /* Non-CREATED state rejected. */
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_FALSE(break_net_reactor_set_tls(reactor, &cfg));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_tls_handshake_auth_ping_roundtrip)
{
    char cert[512];
    char key[512];
    BreakNetReactorConfig config = tls_test_config();
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = tls_test_acceptor();
    BreakNetTlsConfig cfg = {0};
    TlsTestClient client;
    uint64_t deadline;
    uint64_t connection_key = 0u;
    unsigned char payload[] = {0xdeu, 0xadu, 0xbeu, 0xefu};
    unsigned char auth_wire[BREAK_NET_ENVELOPE_MAX_SIZE];
    size_t auth_size = 0u;
    BreakNetEnvelope auth = {0};
    BreakNetEvent event = {0};
    snow_network_buffer_t *plain = NULL;
    unsigned char ping_wire[64];
    size_t copied = 0u;
    BreakNetEnvelope ping = {0};
    int pump = 0;

    tls_test_fixture_path(cert, sizeof(cert), "snow_test_cert.pem");
    tls_test_fixture_path(key, sizeof(key), "snow_test_key.pem");
    cfg.cert_file = cert;
    cfg.key_file = key;
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_tls(reactor, &cfg));
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(tls_test_client_open(&client, acceptor, false));

    deadline = tls_test_monotonic_us() + TLS_TEST_DEADLINE_US;
    ASSERT_TRUE(tls_test_client_handshake(&client, deadline));
    ASSERT_TRUE(tls_test_wait_opened(reactor, deadline, &connection_key));

    /* Client -> server: AUTH envelope as TLS ciphertext. */
    auth.protocol_version = BREAK_NET_PROTOCOL_VERSION;
    auth.message_id = BREAK_NET_MESSAGE_ID_AUTH;
    auth.sequence = 7u;
    auth.payload = payload;
    auth.payload_size = sizeof(payload);
    ASSERT_EQ(break_net_envelope_encode(&auth, auth_wire, sizeof(auth_wire),
                                        &auth_size), BREAK_NET_ENVELOPE_OK);
    ASSERT_TRUE(tls_test_client_send(&client, auth_wire, auth_size));

    /* Server emits the decrypted envelope with exact fields. */
    {
        bool got_message = false;
        while (tls_test_monotonic_us() < deadline && !got_message) {
            if (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
                got_message = event.type == BREAK_NET_EVENT_MESSAGE_RECEIVED;
                if (!got_message) break_net_event_release(&event);
            } else {
                usleep(1000u);
            }
        }
        ASSERT_TRUE(got_message);
    }
    ASSERT_EQ(event.connection_key, connection_key);
    ASSERT_EQ(event.message.message_id, BREAK_NET_MESSAGE_ID_AUTH);
    ASSERT_EQ(event.message.protocol_version, BREAK_NET_PROTOCOL_VERSION);
    ASSERT_EQ(event.message.sequence, 7u);
    ASSERT_EQ(event.message.size, sizeof(payload));
    ASSERT_TRUE(memcmp(event.message.data, payload, sizeof(payload)) == 0);
    break_net_event_release(&event);

    /* Server -> client: PING envelope; on the wire it must be ciphertext. */
    ASSERT_EQ(break_net_reactor_send(reactor, connection_key,
                                     BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, payload,
                                     sizeof(payload)), BREAK_NET_SEND_OK);
    ASSERT_EQ(snow_network_buffer_create(&plain), SNOW_OK);
    while (snow_network_buffer_length(plain) < 18u + sizeof(payload)) {
        pump = tls_test_client_pump(&client, plain, deadline);
        ASSERT_EQ(pump, 1);
    }
    ASSERT_TRUE(client.rawlog_len > 0u);
    ASSERT_FALSE(tls_test_contains_magic(client.rawlog, client.rawlog_len));
    ASSERT_EQ(snow_network_buffer_copy_to(plain, ping_wire,
                                          18u + sizeof(payload), &copied), SNOW_OK);
    ASSERT_EQ(copied, 18u + sizeof(payload));
    ASSERT_EQ(break_net_envelope_decode(ping_wire, copied, &ping),
              BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(ping.message_id, BREAK_NET_MESSAGE_ID_PING);
    ASSERT_EQ(ping.protocol_version, BREAK_NET_PROTOCOL_VERSION);
    ASSERT_EQ(ping.sequence, 0u); /* monotonic outbound sequence is Task 3 */
    ASSERT_EQ(ping.payload_size, sizeof(payload));
    ASSERT_TRUE(memcmp(ping.payload, payload, sizeof(payload)) == 0);
    snow_network_buffer_destroy(plain);

    tls_test_client_close(&client);
    deadline = tls_test_monotonic_us() + TLS_TEST_DEADLINE_US;
    {
        TlsTestEventWatch watch;
        tls_test_watch_until_close(reactor, deadline, &watch);
        ASSERT_TRUE(watch.saw_close);
        break_net_event_release(&watch.message_event);
    }
    ASSERT_TRUE(tls_test_wait_identity_count(reactor, 0u, deadline));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_tls_garbage_before_handshake_closes_without_messages)
{
    char cert[512];
    char key[512];
    BreakNetReactorConfig config = tls_test_config();
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = tls_test_acceptor();
    BreakNetTlsConfig cfg = {0};
    unsigned char garbage[64];
    TlsTestEventWatch watch;
    int fd;
    uint64_t deadline;

    tls_test_fixture_path(cert, sizeof(cert), "snow_test_cert.pem");
    tls_test_fixture_path(key, sizeof(key), "snow_test_key.pem");
    cfg.cert_file = cert;
    cfg.key_file = key;
    memset(garbage, 0xa5u, sizeof(garbage));
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_tls(reactor, &cfg));
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    fd = tls_test_connect(acceptor);
    ASSERT_TRUE(fd >= 0);
    ASSERT_EQ(send(fd, garbage, sizeof(garbage), 0), (ssize_t)sizeof(garbage));

    deadline = tls_test_monotonic_us() + TLS_TEST_DEADLINE_US;
    tls_test_watch_until_close(reactor, deadline, &watch);
    ASSERT_TRUE(watch.saw_opened);
    ASSERT_TRUE(watch.saw_close);
    ASSERT_FALSE(watch.saw_message);
    break_net_event_release(&watch.message_event);
    ASSERT_TRUE(tls_test_wait_identity_count(reactor, 0u, deadline));
    close(fd);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_tls_plaintext_envelope_client_is_closed)
{
    char cert[512];
    char key[512];
    BreakNetReactorConfig config = tls_test_config();
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = tls_test_acceptor();
    BreakNetTlsConfig cfg = {0};
    unsigned char payload[] = {1u, 2u, 3u, 4u};
    unsigned char wire[BREAK_NET_ENVELOPE_MAX_SIZE];
    size_t wire_size = 0u;
    BreakNetEnvelope auth = {0};
    TlsTestEventWatch watch;
    int fd;
    uint64_t deadline;

    tls_test_fixture_path(cert, sizeof(cert), "snow_test_cert.pem");
    tls_test_fixture_path(key, sizeof(key), "snow_test_key.pem");
    cfg.cert_file = cert;
    cfg.key_file = key;
    auth.protocol_version = BREAK_NET_PROTOCOL_VERSION;
    auth.message_id = BREAK_NET_MESSAGE_ID_AUTH;
    auth.sequence = 1u;
    auth.payload = payload;
    auth.payload_size = sizeof(payload);
    ASSERT_EQ(break_net_envelope_encode(&auth, wire, sizeof(wire), &wire_size),
              BREAK_NET_ENVELOPE_OK);
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_tls(reactor, &cfg));
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    fd = tls_test_connect(acceptor);
    ASSERT_TRUE(fd >= 0);
    ASSERT_EQ(send(fd, wire, wire_size, 0), (ssize_t)wire_size);

    deadline = tls_test_monotonic_us() + TLS_TEST_DEADLINE_US;
    tls_test_watch_until_close(reactor, deadline, &watch);
    ASSERT_TRUE(watch.saw_opened);
    ASSERT_TRUE(watch.saw_close);
    ASSERT_FALSE(watch.saw_message);
    break_net_event_release(&watch.message_event);
    ASSERT_TRUE(tls_test_wait_identity_count(reactor, 0u, deadline));
    close(fd);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_tls_verify_peer_accepts_fixture_client_cert)
{
    char cert[512];
    char key[512];
    BreakNetReactorConfig config = tls_test_config();
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = tls_test_acceptor();
    BreakNetTlsConfig cfg = {0};
    TlsTestClient client;
    uint64_t deadline;
    uint64_t connection_key = 0u;
    unsigned char payload[] = {9u, 8u, 7u, 6u};
    unsigned char auth_wire[BREAK_NET_ENVELOPE_MAX_SIZE];
    size_t auth_size = 0u;
    BreakNetEnvelope auth = {0};
    BreakNetEvent event = {0};

    tls_test_fixture_path(cert, sizeof(cert), "snow_test_cert.pem");
    tls_test_fixture_path(key, sizeof(key), "snow_test_key.pem");
    cfg.cert_file = cert;
    cfg.key_file = key;
    cfg.ca_file = cert; /* one-cert PKI: the self-signed fixture is its own CA */
    cfg.verify_peer = 1;
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_tls(reactor, &cfg));
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(tls_test_client_open(&client, acceptor, true));

    deadline = tls_test_monotonic_us() + TLS_TEST_DEADLINE_US;
    ASSERT_TRUE(tls_test_client_handshake(&client, deadline));
    ASSERT_TRUE(tls_test_wait_opened(reactor, deadline, &connection_key));

    auth.protocol_version = BREAK_NET_PROTOCOL_VERSION;
    auth.message_id = BREAK_NET_MESSAGE_ID_AUTH;
    auth.sequence = 3u;
    auth.payload = payload;
    auth.payload_size = sizeof(payload);
    ASSERT_EQ(break_net_envelope_encode(&auth, auth_wire, sizeof(auth_wire),
                                        &auth_size), BREAK_NET_ENVELOPE_OK);
    ASSERT_TRUE(tls_test_client_send(&client, auth_wire, auth_size));
    {
        bool got_message = false;
        while (tls_test_monotonic_us() < deadline && !got_message) {
            if (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
                got_message = event.type == BREAK_NET_EVENT_MESSAGE_RECEIVED;
                if (!got_message) break_net_event_release(&event);
            } else {
                usleep(1000u);
            }
        }
        ASSERT_TRUE(got_message);
    }
    ASSERT_EQ(event.message.message_id, BREAK_NET_MESSAGE_ID_AUTH);
    ASSERT_EQ(event.message.size, sizeof(payload));
    break_net_event_release(&event);

    tls_test_client_close(&client);
    deadline = tls_test_monotonic_us() + TLS_TEST_DEADLINE_US;
    ASSERT_TRUE(tls_test_wait_identity_count(reactor, 0u, deadline));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_tls_verify_peer_rejects_certless_client)
{
    char cert[512];
    char key[512];
    BreakNetReactorConfig config = tls_test_config();
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = tls_test_acceptor();
    BreakNetTlsConfig cfg = {0};
    TlsTestClient client;
    TlsTestEventWatch watch;
    uint64_t deadline;
    bool handshake_ok;
    bool peer_dead = false;

    tls_test_fixture_path(cert, sizeof(cert), "snow_test_cert.pem");
    tls_test_fixture_path(key, sizeof(key), "snow_test_key.pem");
    cfg.cert_file = cert;
    cfg.key_file = key;
    cfg.ca_file = cert;
    cfg.verify_peer = 1;
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_tls(reactor, &cfg));
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(tls_test_client_open(&client, acceptor, false));

    deadline = tls_test_monotonic_us() + TLS_TEST_DEADLINE_US;
    handshake_ok = tls_test_client_handshake(&client, deadline);
    /* TLS 1.3: the client may locally "finish" before the server's
     * certificate-required alert arrives; either way the connection dies. */
    tls_test_watch_until_close(reactor, deadline, &watch);
    ASSERT_TRUE(watch.saw_opened);
    ASSERT_TRUE(watch.saw_close);
    ASSERT_FALSE(watch.saw_message);
    break_net_event_release(&watch.message_event);
    ASSERT_TRUE(tls_test_wait_identity_count(reactor, 0u, deadline));
    while (tls_test_monotonic_us() < deadline && !peer_dead) {
        int ready = tls_test_wait_readable(client.fd, deadline);
        if (ready == 0) break;
        if (ready < 0) {
            peer_dead = true;
            break;
        }
        {
            unsigned char buf[512];
            ssize_t got = recv(client.fd, buf, sizeof(buf), 0);
            if (got <= 0) {
                peer_dead = true;
            } else if (!handshake_ok ||
                       snow_ssl_read(client.ssl, buf, (size_t)got,
                                     snow_ssl_recv_buffer(client.ssl)) != 0) {
                peer_dead = true;
            }
        }
    }
    ASSERT_TRUE(peer_dead);
    tls_test_client_close(&client);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST_MAIN_BEGIN()
    RUN_TEST(break_net_tls_config_validation);
    RUN_TEST(break_net_tls_handshake_auth_ping_roundtrip);
    RUN_TEST(break_net_tls_garbage_before_handshake_closes_without_messages);
    RUN_TEST(break_net_tls_plaintext_envelope_client_is_closed);
    RUN_TEST(break_net_tls_verify_peer_accepts_fixture_client_cert);
    RUN_TEST(break_net_tls_verify_peer_rejects_certless_client);
TEST_MAIN_END()
