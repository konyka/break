/* ==========================================================================
 *  test_network.c — Unit tests for the network module (UDP / TCP sockets).
 * ========================================================================== */

#include "test_framework.h"
#include <network/network.h>
#include <string.h>

/* UDP send completion does not guarantee the peer's non-blocking receive
 * queue has been populated yet. Wait for readiness before consuming a packet. */
static i32 recvfrom_wait_readable(NetSocket *socket, void *buf, u32 size,
                                  NetAddress *out_addr)
{
    NetPollFd pfd = { .socket = socket, .events = NET_POLL_READ, .revents = 0 };
    if (net_poll(&pfd, 1, 1000) <= 0 || (pfd.revents & NET_POLL_READ) == 0)
        return NET_ERROR;
    return net_recvfrom(socket, buf, size, out_addr);
}

/* ----------------------------------------------------------------------- */

/* A socket bound to INADDR_ANY reports local host "0.0.0.0"; Winsock rejects
 * sendto() to the wildcard with WSAEADDRNOTAVAIL (Linux maps it to loopback,
 * which is why this only fails on Windows). Normalize the destination to
 * loopback for tests that send to a socket's own local address. */
static void net_test_normalize_loopback(NetAddress *addr)
{
    if (strcmp(addr->host, "0.0.0.0") == 0) {
        strncpy(addr->host, "127.0.0.1", sizeof(addr->host) - 1u);
        addr->host[sizeof(addr->host) - 1u] = '\0';
    } else if (strcmp(addr->host, "::") == 0) {
        strncpy(addr->host, "::1", sizeof(addr->host) - 1u);
        addr->host[sizeof(addr->host) - 1u] = '\0';
    }
}

/* ----------------------------------------------------------------------- */

TEST(init_shutdown)
{
    ASSERT_TRUE(net_init());
    net_shutdown();
}

TEST(udp_create_close)
{
    ASSERT_TRUE(net_init());
    NetSocket *s = net_udp_create(0);
    ASSERT_NOT_NULL(s);
    net_close(s);
    net_shutdown();
}

TEST(address_resolve)
{
    ASSERT_TRUE(net_init());
    NetAddress addr;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", 8080, &addr));
    ASSERT_EQ(addr.port, (u16)8080);
    net_shutdown();
}

TEST(address_resolve_localhost)
{
    ASSERT_TRUE(net_init());
    NetAddress addr;
    ASSERT_TRUE(net_address_resolve("localhost", 12345, &addr));
    ASSERT_EQ(addr.port, (u16)12345);
    net_shutdown();
}

TEST(address_equal)
{
    NetAddress a = {0}, b = {0}, c = {0};
    strncpy(a.host, "127.0.0.1", sizeof(a.host) - 1u);
    strncpy(b.host, "127.0.0.1", sizeof(b.host) - 1u);
    strncpy(c.host, "10.0.0.1", sizeof(c.host) - 1u);
    a.port = 8080u;
    b.port = 8080u;
    c.port = 8080u;
    ASSERT_TRUE(net_address_equal(&a, &b));
    ASSERT_FALSE(net_address_equal(&a, &c));
    b.port = 8081u;
    ASSERT_FALSE(net_address_equal(&a, &b));
}

TEST(udp_loopback)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = net_udp_create(0);
    ASSERT_NOT_NULL(recv_s);
    NetSocket *send_s = net_udp_create(0);
    ASSERT_NOT_NULL(send_s);

    net_set_nonblocking(recv_s, true);

    /* Send a message */
    NetAddress dst;
    ASSERT_TRUE(net_socket_get_local_address(recv_s, &dst));
    net_test_normalize_loopback(&dst);
    const char *msg = "Hello, loopback!";
    i32 sent = net_sendto(send_s, msg, (u32)strlen(msg) + 1, &dst);
    ASSERT_TRUE(sent > 0);

    /* Receive */
    char buf[64] = {0};
    NetAddress src;
    i32 received = recvfrom_wait_readable(recv_s, buf, sizeof(buf), &src);
    ASSERT_TRUE(received > 0);
    ASSERT_STR_EQ(buf, "Hello, loopback!");

    net_close(send_s);
    net_close(recv_s);
    net_shutdown();
}

TEST(poll_timeout)
{
    ASSERT_TRUE(net_init());
    NetSocket *s = net_udp_create(0);
    ASSERT_NOT_NULL(s);
    net_set_nonblocking(s, true);

    NetPollFd pfd = { .socket = s, .events = NET_POLL_READ, .revents = 0 };
    i32 ret = net_poll(&pfd, 1, 10);  /* 10ms timeout */
    ASSERT_EQ(ret, 0);  /* timeout, no data */
    ASSERT_EQ(pfd.revents, 0u);

    net_close(s);
    net_shutdown();
}

TEST(poll_readable)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = net_udp_create(0);
    ASSERT_NOT_NULL(recv_s);
    NetSocket *send_s = net_udp_create(0);
    ASSERT_NOT_NULL(send_s);

    NetAddress dst;
    ASSERT_TRUE(net_socket_get_local_address(recv_s, &dst));
    net_test_normalize_loopback(&dst);
    const char *msg = "poll test";
    net_sendto(send_s, msg, (u32)strlen(msg) + 1, &dst);

    NetPollFd pfd = { .socket = recv_s, .events = NET_POLL_READ, .revents = 0 };
    i32 ret = net_poll(&pfd, 1, 1000);  /* 1s timeout */
    ASSERT_TRUE(ret > 0);
    ASSERT_TRUE((pfd.revents & NET_POLL_READ) != 0);

    net_close(send_s);
    net_close(recv_s);
    net_shutdown();
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(address_resolve_null)
{
    ASSERT_TRUE(net_init());
    NetAddress addr;
    /* NULL address string should fail gracefully */
    ASSERT_TRUE(!net_address_resolve(NULL, 8080, &addr));
    net_shutdown();
}

TEST(address_resolve_invalid)
{
    ASSERT_TRUE(net_init());
    NetAddress addr;
    /* Invalid hostname - result is implementation-defined (may resolve via DNS) */
    (void)net_address_resolve("invalid.hostname.that.does.not.exist.xyz", 8080, &addr);
    /* Just verify no crash */
    ASSERT_TRUE(true);
    net_shutdown();
}

TEST(udp_create_zero_port)
{
    ASSERT_TRUE(net_init());
    /* Zero port means OS assigns a port */
    NetSocket *s = net_udp_create(0);
    ASSERT_NOT_NULL(s);
    net_close(s);
    net_shutdown();
}

TEST(udp_ephemeral_port_is_queryable)
{
    ASSERT_TRUE(net_init());
    NetSocket *socket = net_udp_create(0);
    ASSERT_NOT_NULL(socket);

    NetAddress address;
    ASSERT_TRUE(net_socket_get_local_address(socket, &address));
    ASSERT_STR_EQ(address.host, "0.0.0.0");
    ASSERT_TRUE(address.port != 0u);
    ASSERT_FALSE(net_socket_get_local_address(NULL, &address));
    ASSERT_FALSE(net_socket_get_local_address(socket, NULL));

    net_close(socket);
    net_shutdown();
}

TEST(sendto_empty_buffer)
{
    ASSERT_TRUE(net_init());
    NetSocket *s = net_udp_create(0);
    ASSERT_NOT_NULL(s);

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", 19999, &dst));

    /* Send empty buffer - should not crash */
    i32 sent = net_sendto(s, "", 0, &dst);
    (void)sent;  /* Result is implementation-defined */

    net_close(s);
    net_shutdown();
}

TEST(sendto_const_address)
{
    /* R418: net_sendto must not write a resolver cache into the caller's
     * address (it previously cast away const). A genuinely const NetAddress
     * in read-only storage must work. */
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = net_udp_create(0);
    ASSERT_NOT_NULL(recv_s);
    net_set_nonblocking(recv_s, true);
    NetSocket *send_s = net_udp_create(0);
    ASSERT_NOT_NULL(send_s);

    NetAddress recv_addr;
    ASSERT_TRUE(net_socket_get_local_address(recv_s, &recv_addr));
    const NetAddress dst = { .host = "127.0.0.1", .port = recv_addr.port };
    const char *msg = "const addr";
    i32 sent = net_sendto(send_s, msg, (u32)strlen(msg) + 1, &dst);
    ASSERT_TRUE(sent > 0);

    char buf[64] = {0};
    i32 received = recvfrom_wait_readable(recv_s, buf, sizeof(buf), NULL);
    ASSERT_TRUE(received > 0);
    ASSERT_STR_EQ(buf, "const addr");

    net_close(send_s);
    net_close(recv_s);
    net_shutdown();
}

TEST(sendto_repeated_sends_with_cache)
{
    /* R423: net_sendto caches the resolved sockaddr on the socket, keyed by
     * (host,port). The cache must be externally invisible: repeated sends to
     * the same destination (cache hit) and a send to a different destination
     * (key differs → re-resolve) must all arrive intact. */
    ASSERT_TRUE(net_init());
    NetSocket *recv_a = net_udp_create(0);
    ASSERT_NOT_NULL(recv_a);
    net_set_nonblocking(recv_a, true);
    NetSocket *recv_b = net_udp_create(0);
    ASSERT_NOT_NULL(recv_b);
    net_set_nonblocking(recv_b, true);
    NetSocket *send_s = net_udp_create(0);
    ASSERT_NOT_NULL(send_s);

    NetAddress dst_a, dst_b;
    ASSERT_TRUE(net_socket_get_local_address(recv_a, &dst_a));
    ASSERT_TRUE(net_socket_get_local_address(recv_b, &dst_b));
    net_test_normalize_loopback(&dst_a);
    net_test_normalize_loopback(&dst_b);

    const char *m1 = "first";
    const char *m2 = "second";
    const char *m3 = "third-b";
    ASSERT_TRUE(net_sendto(send_s, m1, (u32)strlen(m1) + 1, &dst_a) > 0);
    /* Second send to the same (host,port) — the cache-hit path. */
    ASSERT_TRUE(net_sendto(send_s, m2, (u32)strlen(m2) + 1, &dst_a) > 0);
    /* Different port — cache key differs, must re-resolve, not reuse. */
    ASSERT_TRUE(net_sendto(send_s, m3, (u32)strlen(m3) + 1, &dst_b) > 0);

    char buf[64] = {0};
    ASSERT_TRUE(recvfrom_wait_readable(recv_a, buf, sizeof(buf), NULL) > 0);
    ASSERT_STR_EQ(buf, "first");
    memset(buf, 0, sizeof(buf));
    ASSERT_TRUE(recvfrom_wait_readable(recv_a, buf, sizeof(buf), NULL) > 0);
    ASSERT_STR_EQ(buf, "second");
    memset(buf, 0, sizeof(buf));
    ASSERT_TRUE(recvfrom_wait_readable(recv_b, buf, sizeof(buf), NULL) > 0);
    ASSERT_STR_EQ(buf, "third-b");

    net_close(send_s);
    net_close(recv_b);
    net_close(recv_a);
    net_shutdown();
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(init_shutdown);
    RUN_TEST(udp_create_close);
    RUN_TEST(address_resolve);
    RUN_TEST(address_resolve_localhost);
    RUN_TEST(address_equal);
    RUN_TEST(udp_loopback);
    RUN_TEST(poll_timeout);
    RUN_TEST(poll_readable);
    /* Edge cases */
    RUN_TEST(address_resolve_null);
    RUN_TEST(address_resolve_invalid);
    RUN_TEST(udp_create_zero_port);
    RUN_TEST(udp_ephemeral_port_is_queryable);
    RUN_TEST(sendto_empty_buffer);
    RUN_TEST(sendto_const_address);
    RUN_TEST(sendto_repeated_sends_with_cache);
TEST_MAIN_END()
