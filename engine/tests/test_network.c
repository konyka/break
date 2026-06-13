/* ==========================================================================
 *  test_network.c — Unit tests for the network module (UDP / TCP sockets).
 * ========================================================================== */

#include "test_framework.h"
#include <network/network.h>
#include <string.h>

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
    /* Create two UDP sockets: sender and receiver */
    NetSocket *recv_s = net_udp_create(0);
    ASSERT_NOT_NULL(recv_s);
    NetSocket *send_s = net_udp_create(0);
    ASSERT_NOT_NULL(send_s);

    /* Get receiver's bound port (we need to figure it out).
     * Since we bound to port 0, the OS assigned a port.
     * For this test, we'll use a fixed port instead. */
    net_close(recv_s);
    net_close(send_s);

    /* Use a fixed high port for loopback test */
    recv_s = net_udp_create(19876);
    ASSERT_NOT_NULL(recv_s);
    net_set_nonblocking(recv_s, true);

    send_s = net_udp_create(0);
    ASSERT_NOT_NULL(send_s);

    /* Send a message */
    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", 19876, &dst));
    const char *msg = "Hello, loopback!";
    i32 sent = net_sendto(send_s, msg, (u32)strlen(msg) + 1, &dst);
    ASSERT_TRUE(sent > 0);

    /* Receive */
    char buf[64] = {0};
    NetAddress src;
    i32 received = net_recvfrom(recv_s, buf, sizeof(buf), &src);
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
    NetSocket *recv_s = net_udp_create(19877);
    ASSERT_NOT_NULL(recv_s);
    NetSocket *send_s = net_udp_create(0);
    ASSERT_NOT_NULL(send_s);

    NetAddress dst;
    net_address_resolve("127.0.0.1", 19877, &dst);
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
    RUN_TEST(sendto_empty_buffer);
TEST_MAIN_END()
