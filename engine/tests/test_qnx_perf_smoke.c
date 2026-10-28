/* ==========================================================================
 *  test_qnx_perf_smoke.c — Efficiency smoke for the QNX headless profile.
 *
 *  Runs on any POSIX host (headless CI lanes) and on a QNX target unchanged:
 *  it exercises exactly the subsystems a QNX deployment uses — the poll()
 *  net_loop backend, the work-stealing task system, and the myui offscreen
 *  draw pipeline (vgcanvas + frame metrics) — and asserts loose throughput
 *  floors chosen to hold under sanitizers on slow CI runners, so a real
 *  target regression fails loudly instead of silently degrading.
 * ========================================================================== */

#include "test_framework.h"
#include <network/net_loop.h>
#include <network/network.h>
#include <platform/time.h>
#include <task/task.h>
#include <myr/my_ui_metrics.h>
#include <myr/my_vgcanvas.h>
#include <string.h>

#define QNX_SMOKE_DATAGRAMS 512u
#define QNX_SMOKE_DATAGRAMS_MIN_PER_SEC 256.0
#define QNX_SMOKE_TASKS 20000u
#define QNX_SMOKE_TASKS_MIN_PER_SEC 5000.0
#define QNX_SMOKE_FRAMES 2000u
#define QNX_SMOKE_OPS_PER_FRAME 20u
#define QNX_SMOKE_OPS_MIN_PER_SEC 20000.0

static void smoke_loopback_pair(NetSocket **recv_s, NetSocket **send_s,
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

/* Measured rates are printed so target runs can be pasted into
 * docs/qnx_compat.md as evidence without rerunning under a profiler. */
TEST(qnx_smoke_net_loop_poll_throughput)
{
    ASSERT_TRUE(net_init());
    NetSocket *recv_s = NULL, *send_s = NULL;
    NetAddress dst = {0};
    smoke_loopback_pair(&recv_s, &send_s, &dst);

    NetLoop *loop = net_loop_create();
    ASSERT_NOT_NULL(loop);
    ASSERT_TRUE(net_loop_add(loop, recv_s, NET_LOOP_READ, NULL));

    const char p[] = "smoke";
    u32 sent = 0, received = 0;
    u64 start = time_microseconds();
    u64 deadline = start + 5000000ull;
    NetLoopEvent ev[32];
    while (sent < QNX_SMOKE_DATAGRAMS && time_microseconds() < deadline) {
        u32 batch = 0;
        while (batch < 16u && sent < QNX_SMOKE_DATAGRAMS) {
            i32 rc = net_sendto(send_s, p, (u32)sizeof(p), &dst);
            if (rc == NET_WOULD_BLOCK) break;
            ASSERT_EQ(rc, (i32)sizeof(p));
            sent++;
            batch++;
        }
        i32 n = net_loop_wait(loop, ev, 32, 500);
        if (n == NET_ERROR) break;
        if (n > 0) {
            char buf[64];
            while (net_recvfrom(recv_s, buf, sizeof(buf), NULL) > 0) received++;
        }
    }
    while (received < sent && time_microseconds() < deadline) {
        i32 n = net_loop_wait(loop, ev, 32, 500);
        if (n == NET_ERROR) break;
        if (n > 0) {
            char buf[64];
            while (net_recvfrom(recv_s, buf, sizeof(buf), NULL) > 0) received++;
        }
    }
    u64 elapsed_us = time_microseconds() - start;

    ASSERT_EQ(sent, QNX_SMOKE_DATAGRAMS);
    ASSERT_EQ(received, QNX_SMOKE_DATAGRAMS);
    f64 seconds = (f64)elapsed_us / 1e6;
    f64 rate = seconds > 0.0 ? (f64)received / seconds : 0.0;
    printf("qnx_perf_smoke: poll net_loop %.0f datagrams/sec (%u in %.3fs)\n",
           rate, received, seconds);
    ASSERT_TRUE(rate >= QNX_SMOKE_DATAGRAMS_MIN_PER_SEC);

    net_loop_destroy(loop);
    net_close(recv_s);
    net_close(send_s);
    net_shutdown();
}

static void smoke_task_fn(void *ctx)
{
    (void)ctx;
}

TEST(qnx_smoke_task_throughput)
{
    TaskSystem *ts = task_system_create(2);
    ASSERT_NOT_NULL(ts);

    u64 start = time_microseconds();
    for (u32 i = 0; i < QNX_SMOKE_TASKS; i++) {
        task_submit(ts, smoke_task_fn, NULL);
    }
    task_wait(ts);
    u64 elapsed_us = time_microseconds() - start;
    ASSERT_TRUE(atomic_load(&ts->total_tasks_completed) >=
                (u64)QNX_SMOKE_TASKS);

    f64 seconds = (f64)elapsed_us / 1e6;
    f64 rate = seconds > 0.0 ? (f64)QNX_SMOKE_TASKS / seconds : 0.0;
    printf("qnx_perf_smoke: task system %.0f tasks/sec (%u in %.3fs)\n",
           rate, QNX_SMOKE_TASKS, seconds);
    ASSERT_TRUE(rate >= QNX_SMOKE_TASKS_MIN_PER_SEC);

    task_system_destroy(ts);
}

typedef struct smoke_canvas_t {
    my_vgcanvas_t base;
    u64 ops;
} smoke_canvas_t;

static my_ret_t smoke_begin(my_vgcanvas_t *vg, const my_rect_t *dirty)
{
    (void)dirty;
    ((smoke_canvas_t *)vg)->ops++;
    return MY_RET_OK;
}

static my_ret_t smoke_end(my_vgcanvas_t *vg)
{
    ((smoke_canvas_t *)vg)->ops++;
    return MY_RET_OK;
}

static my_ret_t smoke_fill_rect(my_vgcanvas_t *vg, const my_rectf_t *rect)
{
    (void)rect;
    ((smoke_canvas_t *)vg)->ops++;
    return MY_RET_OK;
}

static my_ret_t smoke_stroke_rect(my_vgcanvas_t *vg, const my_rectf_t *rect)
{
    return smoke_fill_rect(vg, rect);
}

static my_ret_t smoke_text(my_vgcanvas_t *vg, const char *text, float x,
                           float y)
{
    (void)text; (void)x; (void)y;
    ((smoke_canvas_t *)vg)->ops++;
    return MY_RET_OK;
}

static const my_vgcanvas_vtable_t smoke_vtable = {
    .begin_frame = smoke_begin,
    .end_frame = smoke_end,
    .fill_rect = smoke_fill_rect,
    .stroke_rect = smoke_stroke_rect,
    .draw_text = smoke_text};

TEST(qnx_smoke_myui_offscreen_frames)
{
    smoke_canvas_t canvas = {0};
    canvas.base.vtable = &smoke_vtable;
    my_rectf_t rect = {0.0f, 0.0f, 64.0f, 16.0f};
    memset(&g_myui_metrics, 0, sizeof(g_myui_metrics));
    my_ui_metrics_set_enabled(true);

    u64 start = time_microseconds();
    for (u32 f = 0; f < QNX_SMOKE_FRAMES; f++) {
        ASSERT_EQ(my_vgcanvas_begin_frame(&canvas.base, NULL), MY_RET_OK);
        for (u32 i = 0; i < 8u; i++) {
            ASSERT_EQ(my_vgcanvas_fill_rect(&canvas.base, &rect), MY_RET_OK);
            ASSERT_EQ(my_vgcanvas_stroke_rect(&canvas.base, &rect), MY_RET_OK);
        }
        for (u32 i = 0; i < 4u; i++) {
            ASSERT_EQ(my_vgcanvas_draw_text(&canvas.base, "qnx", 0.0f, 0.0f),
                      MY_RET_OK);
        }
        ASSERT_EQ(my_vgcanvas_end_frame(&canvas.base), MY_RET_OK);
    }
    u64 elapsed_us = time_microseconds() - start;
    my_ui_frame_metrics_sample_t sample;
    ASSERT_TRUE(my_ui_metrics_get_last(&sample));
    ASSERT_TRUE(sample.draw_calls > 0);

    f64 seconds = (f64)elapsed_us / 1e6;
    f64 total_ops = (f64)QNX_SMOKE_FRAMES * (f64)QNX_SMOKE_OPS_PER_FRAME;
    f64 rate = seconds > 0.0 ? total_ops / seconds : 0.0;
    printf("qnx_perf_smoke: myui offscreen pipeline %.0f vg ops/sec "
           "(%u frames in %.3fs)\n", rate, QNX_SMOKE_FRAMES, seconds);
    ASSERT_TRUE(rate >= QNX_SMOKE_OPS_MIN_PER_SEC);
    my_ui_metrics_set_enabled(false);
}

int main(void)
{
    RUN_TEST(qnx_smoke_net_loop_poll_throughput);
    RUN_TEST(qnx_smoke_task_throughput);
    RUN_TEST(qnx_smoke_myui_offscreen_frames);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
