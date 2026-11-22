/* The main loop adapter reads its facts from a real Platform (the mobile
 * layer, which needs no display) and the observer turns platform changes
 * into bus notices. */
#include "test_framework.h"
#include <platform/platform.h>
#include <runtime/runtime_bus.h>
#include <runtime/runtime_mainloop.h>
#include <runtime/runtime_mainloop_platform.h>
#include <runtime/runtime_queue.h>
#include <string.h>

static u32 drain_types(BreakRuntimeQueue *q, u32 *types, u32 cap, BreakRuntimeMainLoopNotice *last) {
    u32 n = 0u;
    for (;;) {
        BreakRuntimeOwnedMessage *m = NULL;
        BreakRuntimeMainLoopNotice notice;
        if (break_runtime_queue_poll(q, &m) != BREAK_RUNTIME_OK || !m) return n;
        if (break_runtime_mainloop_notice_view(m, &notice) == BREAK_RUNTIME_OK) {
            if (n < cap) types[n] = notice.type;
            if (last) *last = notice;
            n++;
        }
        break_runtime_message_release(m);
    }
}

TEST(platform_changes_become_notices) {
    int window;
    const PlatformConfig config = {
        .width = 640, .height = 480, .title = "mainloop",
        .native_window = &window, .native_content_scale = 2.0f,
    };
    const BreakRuntimeQueueConfig qcfg = {32u, 0u};
    const u16 kind = BREAK_RUNTIME_MAINLOOP_NOTICE_KIND;
    BreakRuntimeBus *bus = NULL;
    BreakRuntimeQueue *queue = NULL;
    BreakRuntimeMainLoop *ml = NULL;
    BreakRuntimeMainLoopFacts facts;
    BreakRuntimeMainLoopNotice last;
    u32 types[8];
    u32 sub = 0u;
    Platform *platform = platform_create(&config);
    ASSERT_NOT_NULL(platform);
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_queue_create(&qcfg, &queue), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_create(bus, &ml), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "main", queue, &kind, 1u, &sub), BREAK_RUNTIME_OK);

    ASSERT_FALSE(break_runtime_mainloop_platform_facts(NULL, 1u, false, &facts));
    ASSERT_FALSE(break_runtime_mainloop_platform_facts(platform, 1u, false, NULL));
    ASSERT_TRUE(break_runtime_mainloop_platform_facts(platform, 1u, false, &facts));
    ASSERT_EQ(facts.drawable_width, 640u);
    ASSERT_EQ(facts.drawable_height, 480u);
    ASSERT_FLOAT_EQ(facts.content_scale, 2.0f, 0.001f);
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &facts), BREAK_RUNTIME_OK);
    ASSERT_EQ(drain_types(queue, types, 8u, NULL), 3u);

    ASSERT_TRUE(platform_mobile_resize(platform, 400, 300, 800, 600, 2.0f));
    ASSERT_TRUE(break_runtime_mainloop_platform_facts(platform, 2u, false, &facts));
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &facts), BREAK_RUNTIME_OK);
    ASSERT_EQ(drain_types(queue, types, 8u, &last), 2u);
    ASSERT_EQ(types[0], (u32)BREAK_RUNTIME_MAINLOOP_RESIZED);
    ASSERT_EQ(types[1], (u32)BREAK_RUNTIME_MAINLOOP_WSI_CHANGED);
    ASSERT_EQ(last.a, (u32)PLATFORM_WSI_RESIZED);

    platform_mobile_notify_suspend(platform);
    ASSERT_TRUE(break_runtime_mainloop_platform_facts(platform, 3u, true, &facts));
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &facts), BREAK_RUNTIME_OK);
    ASSERT_EQ(drain_types(queue, types, 8u, &last), 2u);
    ASSERT_EQ(types[0], (u32)BREAK_RUNTIME_MAINLOOP_CLOSE_REQUESTED);
    ASSERT_EQ(types[1], (u32)BREAK_RUNTIME_MAINLOOP_WSI_CHANGED);
    ASSERT_EQ(last.a, (u32)PLATFORM_WSI_SUSPENDED);
    ASSERT_EQ(last.b, (u32)PLATFORM_WSI_RESIZED);
    ASSERT_EQ(last.frame, 3u);

    (void)break_runtime_bus_unsubscribe(bus, sub);
    break_runtime_mainloop_destroy(ml);
    break_runtime_queue_destroy(queue);
    break_runtime_bus_destroy(bus);
    platform_destroy(platform);
}

TEST_MAIN_BEGIN()
    RUN_TEST(platform_changes_become_notices);
TEST_MAIN_END()
