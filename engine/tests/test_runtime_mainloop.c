/* PAL/MainLoop on the runtime bus: the main loop reports what it observed
 * from the platform each frame, and the observer publishes one notice per
 * change (resize, close request, WSI state, content scale), never waiting. */
#include "test_framework.h"
#include <runtime/runtime_bus.h>
#include <runtime/runtime_mainloop.h>
#include <runtime/runtime_queue.h>
#include <math.h>
#include <string.h>

typedef struct {
    BreakRuntimeBus *bus;
    BreakRuntimeQueue *queue;
    u32 sub;
} MlFixture;

static bool ml_open(MlFixture *f, u32 capacity) {
    const BreakRuntimeQueueConfig cfg = {capacity, 0u};
    const u16 kind = BREAK_RUNTIME_MAINLOOP_NOTICE_KIND;
    memset(f, 0, sizeof(*f));
    return break_runtime_bus_create(&f->bus) == BREAK_RUNTIME_OK &&
           break_runtime_queue_create(&cfg, &f->queue) == BREAK_RUNTIME_OK &&
           break_runtime_mainloop_register_kind(f->bus) == BREAK_RUNTIME_OK &&
           break_runtime_bus_subscribe(f->bus, "mainloop", f->queue, &kind, 1u, &f->sub) ==
               BREAK_RUNTIME_OK;
}

static void ml_close(MlFixture *f) {
    if (f->sub) (void)break_runtime_bus_unsubscribe(f->bus, f->sub);
    break_runtime_queue_destroy(f->queue);
    break_runtime_bus_destroy(f->bus);
}

static bool ml_next(MlFixture *f, BreakRuntimeMainLoopNotice *out) {
    BreakRuntimeOwnedMessage *m = NULL;
    bool ok;
    if (break_runtime_queue_poll(f->queue, &m) != BREAK_RUNTIME_OK || !m) return false;
    ok = break_runtime_mainloop_notice_view(m, out) == BREAK_RUNTIME_OK;
    break_runtime_message_release(m);
    return ok;
}

static BreakRuntimeMainLoopFacts facts(u64 frame, u32 w, u32 h) {
    BreakRuntimeMainLoopFacts x;
    memset(&x, 0, sizeof(x));
    x.frame = frame;
    x.drawable_width = w;
    x.drawable_height = h;
    x.content_scale = 1.0f;
    x.wsi_state = 1u;
    return x;
}

TEST(first_observation_reports_the_initial_state_once) {
    MlFixture f;
    BreakRuntimeMainLoop *ml = NULL;
    BreakRuntimeMainLoopNotice n;
    BreakRuntimeMainLoopFacts x = facts(1u, 640u, 480u);
    ASSERT_TRUE(ml_open(&f, 16u));
    ASSERT_EQ(break_runtime_mainloop_create(NULL, &ml), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_mainloop_create(f.bus, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_mainloop_create(f.bus, &ml), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_RESIZED);
    ASSERT_EQ(n.frame, 1u);
    ASSERT_EQ(n.a, 640u);
    ASSERT_EQ(n.b, 480u);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_WSI_CHANGED);
    ASSERT_EQ(n.a, 1u);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_SCALE_CHANGED);
    ASSERT_EQ(n.a, 1000u);
    ASSERT_FALSE(ml_next(&f, &n));
    /* an unchanged frame publishes nothing */
    x.frame = 2u;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ml_next(&f, &n));
    break_runtime_mainloop_destroy(ml);
    ml_close(&f);
}

TEST(each_change_is_one_notice_in_a_fixed_order) {
    MlFixture f;
    BreakRuntimeMainLoop *ml = NULL;
    BreakRuntimeMainLoopNotice n;
    BreakRuntimeMainLoopFacts x = facts(1u, 640u, 480u);
    BreakRuntimeMainLoopStats st;
    ASSERT_TRUE(ml_open(&f, 16u));
    ASSERT_EQ(break_runtime_mainloop_create(f.bus, &ml), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    while (ml_next(&f, &n)) {}

    x.frame = 7u;
    x.drawable_width = 800u;
    x.close_requested = true;
    x.wsi_state = 4u;
    x.content_scale = 1.5f;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_CLOSE_REQUESTED);
    ASSERT_EQ(n.frame, 7u);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_RESIZED);
    ASSERT_EQ(n.a, 800u);
    ASSERT_EQ(n.b, 480u);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_WSI_CHANGED);
    ASSERT_EQ(n.a, 4u);
    ASSERT_EQ(n.b, 1u); /* previous state */
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_SCALE_CHANGED);
    ASSERT_EQ(n.a, 1500u);
    ASSERT_FALSE(ml_next(&f, &n));

    /* a close request that stays pending is not repeated; a new one after
     * it was cancelled is */
    x.frame = 8u;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ml_next(&f, &n));
    x.frame = 9u;
    x.close_requested = false;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ml_next(&f, &n));
    x.frame = 10u;
    x.close_requested = true;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_CLOSE_REQUESTED);
    ASSERT_EQ(n.frame, 10u);

    /* a height-only change is a resize */
    x.frame = 10u;
    x.drawable_height = 600u;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_RESIZED);
    ASSERT_EQ(n.a, 800u);
    ASSERT_EQ(n.b, 600u);

    /* a zero-sized drawable (minimised) is a resize too */
    x.frame = 11u;
    x.close_requested = false;
    x.drawable_width = 0u;
    x.drawable_height = 0u;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ml_next(&f, &n));
    ASSERT_EQ(n.type, (u32)BREAK_RUNTIME_MAINLOOP_RESIZED);
    ASSERT_EQ(n.a, 0u);
    ASSERT_EQ(n.b, 0u);

    ASSERT_EQ(break_runtime_mainloop_stats(ml, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.observed, 7u);
    ASSERT_EQ(st.published, 10u);
    ASSERT_EQ(st.dropped, 0u);
    break_runtime_mainloop_destroy(ml);
    ml_close(&f);
}

TEST(full_queue_drops_and_counts_without_waiting) {
    MlFixture f;
    BreakRuntimeMainLoop *ml = NULL;
    BreakRuntimeMainLoopNotice n;
    BreakRuntimeMainLoopFacts x = facts(1u, 10u, 10u);
    BreakRuntimeMainLoopStats st;
    ASSERT_TRUE(ml_open(&f, 2u));
    ASSERT_EQ(break_runtime_mainloop_create(f.bus, &ml), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK); /* 3 notices */
    for (u32 i = 2u; i < 6u; i++) {
        x.frame = i;
        x.drawable_width = 10u + i;
        ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(break_runtime_mainloop_stats(ml, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.published + st.dropped, 7u);
    ASSERT_EQ(st.published, 2u);
    ASSERT_EQ(st.dropped, 5u);
    /* the state still follows the facts: the next change is relative to
     * the last observation, not to the last delivered notice */
    while (ml_next(&f, &n)) {}
    x.frame = 6u;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ml_next(&f, &n));
    break_runtime_mainloop_destroy(ml);
    ml_close(&f);
}

TEST(invalid_facts_and_conflicting_kind_are_rejected) {
    MlFixture f;
    BreakRuntimeMainLoop *ml = NULL;
    BreakRuntimeMainLoopFacts x = facts(1u, 10u, 10u);
    BreakRuntimeBus *other = NULL;
    const BreakRuntimeBusKind clash = {BREAK_RUNTIME_MAINLOOP_NOTICE_KIND, 3u, 4u, "x", false, 0u};
    ASSERT_TRUE(ml_open(&f, 4u));
    ASSERT_EQ(break_runtime_mainloop_register_kind(f.bus), BREAK_RUNTIME_OK); /* idempotent */
    ASSERT_EQ(break_runtime_mainloop_create(f.bus, &ml), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_observe(NULL, &x), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_mainloop_observe(ml, NULL), BREAK_RUNTIME_INVALID);
    x.content_scale = -1.0f;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_INVALID);
    x.content_scale = NAN;
    ASSERT_EQ(break_runtime_mainloop_observe(ml, &x), BREAK_RUNTIME_INVALID);
    break_runtime_mainloop_destroy(ml);
    break_runtime_mainloop_destroy(NULL);

    ASSERT_EQ(break_runtime_bus_create(&other), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_register_kind(other, &clash), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_register_kind(other), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_runtime_mainloop_create(other, &ml), BREAK_RUNTIME_REJECTED);
    break_runtime_bus_destroy(other);
    ml_close(&f);
}

TEST(notice_view_is_strict) {
    BreakRuntimeMessageView v;
    BreakRuntimeOwnedMessage *m = NULL;
    BreakRuntimeMainLoopNotice n;
    u8 bytes[BREAK_RUNTIME_MAINLOOP_NOTICE_SIZE];
    memset(bytes, 0, sizeof bytes);
    bytes[0] = (u8)BREAK_RUNTIME_MAINLOOP_RESIZED;
    memset(&v, 0, sizeof v);
    v.kind = BREAK_RUNTIME_MAINLOOP_NOTICE_KIND;
    v.version = BREAK_RUNTIME_MAINLOOP_NOTICE_VERSION;
    v.data = bytes;
    v.size = sizeof bytes;
    ASSERT_EQ(break_runtime_message_copy(&v, &m), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_notice_view(m, &n), BREAK_RUNTIME_OK);
    break_runtime_message_release(m);
    bytes[0] = 99u; /* unknown type */
    ASSERT_EQ(break_runtime_message_copy(&v, &m), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_notice_view(m, &n), BREAK_RUNTIME_INVALID);
    break_runtime_message_release(m);
    bytes[0] = (u8)BREAK_RUNTIME_MAINLOOP_RESIZED;
    v.size = sizeof bytes - 1u;
    ASSERT_EQ(break_runtime_message_copy(&v, &m), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_notice_view(m, &n), BREAK_RUNTIME_INVALID);
    break_runtime_message_release(m);
    v.size = sizeof bytes;
    v.kind = 0x1234u;
    ASSERT_EQ(break_runtime_message_copy(&v, &m), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_mainloop_notice_view(m, &n), BREAK_RUNTIME_INVALID);
    break_runtime_message_release(m);
    ASSERT_EQ(break_runtime_mainloop_notice_view(NULL, &n), BREAK_RUNTIME_INVALID);
}

TEST_MAIN_BEGIN()
    RUN_TEST(first_observation_reports_the_initial_state_once);
    RUN_TEST(each_change_is_one_notice_in_a_fixed_order);
    RUN_TEST(full_queue_drops_and_counts_without_waiting);
    RUN_TEST(invalid_facts_and_conflicting_kind_are_rejected);
    RUN_TEST(notice_view_is_strict);
TEST_MAIN_END()
