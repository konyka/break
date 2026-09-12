/* ==========================================================================
 *  test_net_loop.c — Unit tests for the platform-optimal event loop.
 *
 *  Semantics verified here are backend-independent (kqueue / epoll / IOCP):
 *  readiness notification, batched event retrieval, cross-thread wakeup.
 * ========================================================================== */

#include "test_framework.h"
#include <network/network.h>
#include <network/net_loop.h>
#include <platform/time.h>
#include <string.h>
#include <time.h>

#if !defined(ENGINE_PLATFORM_WINDOWS)
#include <pthread.h>
#endif

#define NET_LOOP_STRESS_DATAGRAMS 512u

static void make_loopback_pair(NetSocket **recv_s, NetSocket **send_s,
                               NetAddress *dst)
{
    *recv_s = net_udp_create(0);
    *send_s = net_udp_create(0);
    ASSERT_NOT_NULL(*recv_s);
    ASSERT_NOT_NULL(*send_s);
    net_set_nonblocking(*recv_s, true);
    net_set_nonblocking(*send_s, true);
    ASSERT_TRUE(net_socket_get_local_address(*recv_s, dst));
    if (strcmp(dst->host, "0.0.0.0") == 0) {
        strncpy(dst->host, "127.0.0.1", sizeof(dst->host) - 1u);
        dst->host[sizeof(dst->host) - 1u] = '\0';
    }
}

TEST(loop_create_destroy)
{
    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    net_loop_destroy(loop);
    /* NULL safety */
    net_loop_destroy(NULL);
    net_loop_wakeup(NULL);
    ASSERT_FALSE(net_loop_add(NULL, NULL, NET_LOOP_READ, NULL));
    ASSERT_EQ(net_loop_wait(NULL, NULL, 0, 0), NET_ERROR);
}

TEST(loop_wait_timeout)
{
    ASSERT_TRUE(net_init());
    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    NetLoopEvent ev[4];
    /* No sockets registered: wait must time out, not error. */
    ASSERT_EQ(net_loop_wait(loop, ev, 4, 10), 0);
    net_loop_destroy(loop);
    net_shutdown();
}

TEST(loop_read_event_on_loopback)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = NULL, *send_s = NULL;
    NetAddress dst = {0};
    make_loopback_pair(&recv_s, &send_s, &dst);

    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    ASSERT_TRUE(net_loop_add(loop, recv_s, NET_LOOP_READ, (void *)recv_s));

    const char payload[] = "hello-loop";
    ASSERT_EQ(net_sendto(send_s, payload, (u32)sizeof(payload), &dst),
              (i32)sizeof(payload));

    NetLoopEvent ev[4] = {0};
    i32 n = net_loop_wait(loop, ev, 4, 1000);
    ASSERT_TRUE(n > 0);
    ASSERT_TRUE((ev[0].events & NET_LOOP_READ) != 0u);
    ASSERT_TRUE(ev[0].socket == recv_s);
    ASSERT_TRUE(ev[0].tag == (void *)recv_s);

    /* The readiness report must correspond to a real datagram. */
    char buf[64];
    NetAddress from;
    ASSERT_EQ(net_recvfrom(recv_s, buf, sizeof(buf), &from), (i32)sizeof(payload));
    ASSERT_STR_EQ(buf, payload);

    net_loop_destroy(loop);
    net_close(recv_s);
    net_close(send_s);
    net_shutdown();
}

TEST(loop_no_event_without_send)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = NULL, *send_s = NULL;
    NetAddress dst = {0};
    make_loopback_pair(&recv_s, &send_s, &dst);

    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    ASSERT_TRUE(net_loop_add(loop, recv_s, NET_LOOP_READ, NULL));

    NetLoopEvent ev[4];
    ASSERT_EQ(net_loop_wait(loop, ev, 4, 50), 0);

    net_loop_destroy(loop);
    net_close(recv_s);
    net_close(send_s);
    net_shutdown();
}

TEST(loop_remove_stops_events)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = NULL, *send_s = NULL;
    NetAddress dst = {0};
    make_loopback_pair(&recv_s, &send_s, &dst);

    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    ASSERT_TRUE(net_loop_add(loop, recv_s, NET_LOOP_READ, NULL));
    ASSERT_TRUE(net_loop_remove(loop, recv_s));

    const char payload[] = "x";
    ASSERT_TRUE(net_sendto(send_s, payload, (u32)sizeof(payload), &dst) > 0);

    NetLoopEvent ev[4];
    ASSERT_EQ(net_loop_wait(loop, ev, 4, 50), 0);

    net_loop_destroy(loop);
    net_close(recv_s);
    net_close(send_s);
    net_shutdown();
}

TEST(loop_modify_drops_read)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = NULL, *send_s = NULL;
    NetAddress dst = {0};
    make_loopback_pair(&recv_s, &send_s, &dst);

    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    ASSERT_TRUE(net_loop_add(loop, recv_s, NET_LOOP_READ, NULL));
    /* Narrow the interest set to write-only; read must stop firing. */
    ASSERT_TRUE(net_loop_modify(loop, recv_s, NET_LOOP_WRITE));

    const char payload[] = "x";
    ASSERT_TRUE(net_sendto(send_s, payload, (u32)sizeof(payload), &dst) > 0);

    NetLoopEvent ev[4];
    i32 n = net_loop_wait(loop, ev, 4, 50);
    for (i32 i = 0; i < n; i++) {
        ASSERT_TRUE((ev[i].events & NET_LOOP_READ) == 0u);
    }

    net_loop_destroy(loop);
    net_close(recv_s);
    net_close(send_s);
    net_shutdown();
}

TEST(loop_rejects_invalid_interest_masks)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = NULL, *send_s = NULL;
    NetAddress dst = {0};
    make_loopback_pair(&recv_s, &send_s, &dst);

    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    ASSERT_FALSE(net_loop_add(loop, recv_s, 0u, NULL));
    ASSERT_FALSE(net_loop_add(loop, recv_s, NET_LOOP_ERROR, NULL));
    ASSERT_FALSE(net_loop_add(loop, recv_s, NET_LOOP_READ | 8u, NULL));
    ASSERT_TRUE(net_loop_add(loop, recv_s, NET_LOOP_READ, NULL));
    ASSERT_FALSE(net_loop_modify(loop, recv_s, NET_LOOP_ERROR));
    ASSERT_FALSE(net_loop_modify(loop, recv_s, NET_LOOP_WRITE | 8u));

    const char payload[] = "mask";
    ASSERT_TRUE(net_sendto(send_s, payload, (u32)sizeof(payload), &dst) > 0);
    NetLoopEvent ev[4] = {0};
    i32 n = net_loop_wait(loop, ev, 4, 1000);
    ASSERT_TRUE(n > 0);
    ASSERT_TRUE((ev[0].events & NET_LOOP_READ) != 0u);

    net_loop_destroy(loop);
    net_close(recv_s);
    net_close(send_s);
    net_shutdown();
}

TEST(loop_batched_events_two_sockets)
{
    ASSERT_TRUE(net_init());
    NetSocket *r1 = net_udp_create(0), *r2 = net_udp_create(0);
    NetSocket *s = net_udp_create(0);
    ASSERT_NOT_NULL(r1);
    ASSERT_NOT_NULL(r2);
    ASSERT_NOT_NULL(s);

    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    ASSERT_TRUE(net_loop_add(loop, r1, NET_LOOP_READ, (void *)1));
    ASSERT_TRUE(net_loop_add(loop, r2, NET_LOOP_READ, (void *)2));

    NetAddress dst1 = {0}, dst2 = {0};
    ASSERT_TRUE(net_socket_get_local_address(r1, &dst1));
    ASSERT_TRUE(net_socket_get_local_address(r2, &dst2));
    strcpy(dst1.host, "127.0.0.1");
    strcpy(dst2.host, "127.0.0.1");

    const char p[] = "b";
    ASSERT_TRUE(net_sendto(s, p, (u32)sizeof(p), &dst1) > 0);
    ASSERT_TRUE(net_sendto(s, p, (u32)sizeof(p), &dst2) > 0);

    /* Give the kernel a beat to queue both datagrams, so a single wait can
     * surface both readiness events together (that batching is the point of
     * this test). */
    time_sleep_us(50000);

    NetLoopEvent ev[8];
    u32 got = 0;
    bool batched = false;
    for (u32 attempt = 0; attempt < 10u && got < 2u; attempt++) {
        i32 n = net_loop_wait(loop, ev, 8, 1000);
        ASSERT_TRUE(n >= 0);
        if (n > 1) batched = true;
        got += (u32)(n > 0 ? n : 0);
    }
    ASSERT_EQ(got, 2u);
    ASSERT_TRUE(batched);

    net_loop_destroy(loop);
    net_close(r1);
    net_close(r2);
    net_close(s);
    net_shutdown();
}

#if !defined(ENGINE_PLATFORM_WINDOWS)
typedef struct {
    NetLoop *loop;
} WakeupCtx;

static void *wakeup_thread(void *arg)
{
    WakeupCtx *ctx = (WakeupCtx *)arg;
    struct timespec ts = { 0, 100 * 1000 * 1000 }; /* 100ms */
    nanosleep(&ts, NULL);
    net_loop_wakeup(ctx->loop);
    return NULL;
}

TEST(loop_wakeup_from_thread)
{
    ASSERT_TRUE(net_init());
    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);

    WakeupCtx ctx = { loop };
    pthread_t th;
    ASSERT_EQ(pthread_create(&th, NULL, wakeup_thread, &ctx), 0);

    /* Block up to 5s; wakeup must cut it short. */
    u64 start = time_microseconds();
    NetLoopEvent ev[4];
    i32 n = net_loop_wait(loop, ev, 4, 5000);
    u64 elapsed_us = time_microseconds() - start;
    ASSERT_EQ(n, 0);          /* wakeup yields no socket events */
    ASSERT_TRUE(elapsed_us < 4000000ull); /* well under the 5s timeout */

    pthread_join(th, NULL);
    net_loop_destroy(loop);
    net_shutdown();
}
#endif

TEST(loop_repeated_short_waits)
{
    ASSERT_TRUE(net_init());
    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    NetLoopEvent ev[4];
    for (u32 i = 0; i < 64u; i++) {
        ASSERT_EQ(net_loop_wait(loop, ev, 4, 1), 0);
    }
    net_loop_destroy(loop);
    net_shutdown();
}

TEST(loop_rejects_unrepresentable_event_count)
{
    ASSERT_TRUE(net_init());
    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    NetLoopEvent ev[1];
    ASSERT_EQ(net_loop_wait(loop, ev, UINT32_MAX, 0), NET_ERROR);
    net_loop_destroy(loop);
    net_shutdown();
}

TEST(loop_stress_throughput)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = NULL, *send_s = NULL;
    NetAddress dst = {0};
    make_loopback_pair(&recv_s, &send_s, &dst);

    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    ASSERT_TRUE(net_loop_add(loop, recv_s, NET_LOOP_READ, NULL));

    /* Produce bounded batches so the kernel's UDP receive queue cannot drop
     * datagrams before the readiness consumer gets scheduled. */
    const char p[] = "datagram";
    u32 sent = 0;
    u32 received = 0;
    u64 deadline = time_microseconds() + 5000000ull;
    NetLoopEvent ev[32];
    while (sent < NET_LOOP_STRESS_DATAGRAMS &&
           time_microseconds() < deadline) {
        u32 batch = 0;
        while (batch < 16u && sent < NET_LOOP_STRESS_DATAGRAMS) {
            i32 rc = net_sendto(send_s, p, (u32)sizeof(p), &dst);
            if (rc == NET_WOULD_BLOCK) break;
            ASSERT_EQ(rc, (i32)sizeof(p));
            sent++;
            batch++;
        }
        i32 n = net_loop_wait(loop, ev, 32, 500);
        if (n == NET_ERROR) break;
        if (n > 0) {
            /* Ready: drain everything currently queued (non-blocking). */
            char buf[64];
            while (net_recvfrom(recv_s, buf, sizeof(buf), NULL) > 0) {
                received++;
            }
        }
    }
    while (received < sent && time_microseconds() < deadline) {
        i32 n = net_loop_wait(loop, ev, 32, 500);
        if (n == NET_ERROR) break;
        if (n > 0) {
            char buf[64];
            while (net_recvfrom(recv_s, buf, sizeof(buf), NULL) > 0) {
                received++;
            }
        }
    }
    ASSERT_EQ(sent, NET_LOOP_STRESS_DATAGRAMS);
    ASSERT_EQ(received, NET_LOOP_STRESS_DATAGRAMS);

    net_loop_destroy(loop);
    net_close(recv_s);
    net_close(send_s);
    net_shutdown();
}

#if defined(ENGINE_PLATFORM_WINDOWS)
TEST(loop_iocp_registration_growth_keeps_inflight_slots_stable)
{
    NetSocket *receivers[32] = {0};
    NetSocket *sender = NULL;
    NetAddress destination = {0};
    NetLoop *loop = NULL;
    NetLoopEvent events[4];
    i32 n;
    u32 i;

    ASSERT_TRUE(net_init());
    sender = net_udp_create(0);
    ASSERT_NOT_NULL(sender);
    loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    for (i = 0u; i < 32u; ++i) {
        receivers[i] = net_udp_create(0);
        ASSERT_NOT_NULL(receivers[i]);
        net_set_nonblocking(receivers[i], true);
        ASSERT_TRUE(net_loop_add(loop, receivers[i], NET_LOOP_READ,
                                 receivers[i]));
        if (i == 0u) {
            ASSERT_TRUE(net_socket_get_local_address(receivers[i],
                                                     &destination));
        }
    }
    if (strcmp(destination.host, "0.0.0.0") == 0) {
        strncpy(destination.host, "127.0.0.1", sizeof(destination.host) - 1u);
        destination.host[sizeof(destination.host) - 1u] = '\0';
    }
    ASSERT_TRUE(net_sendto(sender, "iocp", 5u, &destination) > 0);
    n = net_loop_wait(loop, events, 4u, 1000);
    ASSERT_TRUE(n > 0);
    ASSERT_TRUE(events[0].socket == receivers[0]);

    net_loop_destroy(loop);
    for (i = 0u; i < 32u; ++i) net_close(receivers[i]);
    net_close(sender);
    net_shutdown();
}
#endif

TEST_MAIN_BEGIN()
    RUN_TEST(loop_create_destroy);
    RUN_TEST(loop_wait_timeout);
    RUN_TEST(loop_read_event_on_loopback);
    RUN_TEST(loop_no_event_without_send);
    RUN_TEST(loop_remove_stops_events);
    RUN_TEST(loop_modify_drops_read);
    RUN_TEST(loop_rejects_invalid_interest_masks);
    RUN_TEST(loop_batched_events_two_sockets);
#if !defined(ENGINE_PLATFORM_WINDOWS)
    RUN_TEST(loop_wakeup_from_thread);
#endif
    RUN_TEST(loop_repeated_short_waits);
    RUN_TEST(loop_rejects_unrepresentable_event_count);
    RUN_TEST(loop_stress_throughput);
#if defined(ENGINE_PLATFORM_WINDOWS)
    RUN_TEST(loop_iocp_registration_growth_keeps_inflight_slots_stable);
#endif
TEST_MAIN_END()
