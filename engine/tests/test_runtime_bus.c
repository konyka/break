/* Runtime Core message bus: a registry of message kinds (each with a
 * version limit and a payload budget) that fans published messages out to
 * the bounded queues of the subscribers of that kind, and reports the
 * resulting topology and its counters. */
#include "test_framework.h"
#include <core/platform_thread.h>
#include <runtime/runtime_bus.h>
#include <runtime/runtime_queue.h>
#include <runtime/runtime_test_hooks.h>
#include <stdatomic.h>
#include <string.h>

static BreakRuntimeMessageView view_of(u16 kind, u16 version, const void *data, usize size) {
    BreakRuntimeMessageView v;
    memset(&v, 0, sizeof v);
    v.kind = kind;
    v.version = version;
    v.data = data;
    v.size = size;
    return v;
}

static BreakRuntimeQueue *make_queue(u32 capacity) {
    BreakRuntimeQueueConfig cfg = {capacity, 0u};
    BreakRuntimeQueue *q = NULL;
    return break_runtime_queue_create(&cfg, &q) == BREAK_RUNTIME_OK ? q : NULL;
}

static u32 drain(BreakRuntimeQueue *q, u16 *kinds, u32 cap) {
    u32 n = 0u;
    for (;;) {
        BreakRuntimeOwnedMessage *m = NULL;
        if (break_runtime_queue_poll(q, &m) != BREAK_RUNTIME_OK || !m) break;
        BreakRuntimeMessageView v;
        if (break_runtime_message_view(m, &v) == BREAK_RUNTIME_OK && n < cap) kinds[n] = v.kind;
        n++;
        break_runtime_message_release(m);
    }
    return n;
}

static BreakRuntimeBus *make_bus(void) {
    BreakRuntimeBus *bus = NULL;
    if (break_runtime_bus_create(&bus) != BREAK_RUNTIME_OK) return NULL;
    BreakRuntimeBusKind input = {1u, 2u, 64u, "input.key", false, 0u};
    BreakRuntimeBusKind snapshot = {2u, 1u, 1024u, "world.snapshot", false, 0u};
    if (break_runtime_bus_register_kind(bus, &input) != BREAK_RUNTIME_OK ||
        break_runtime_bus_register_kind(bus, &snapshot) != BREAK_RUNTIME_OK) {
        break_runtime_bus_destroy(bus);
        return NULL;
    }
    return bus;
}

TEST(kind_registration_is_validated) {
    BreakRuntimeBus *bus = NULL;
    ASSERT_EQ(break_runtime_bus_create(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(bus);
    BreakRuntimeBusKind ok = {5u, 1u, 16u, "net.ping", false, 0u};
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &ok), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &ok), BREAK_RUNTIME_INVALID); /* duplicate */
    BreakRuntimeBusKind zero_version = {6u, 0u, 16u, "a", false, 0u};
    BreakRuntimeBusKind big_budget = {7u, 1u, BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD + 1u, "b", false, 0u};
    BreakRuntimeBusKind no_name = {8u, 1u, 16u, NULL, false, 0u};
    BreakRuntimeBusKind bad_name = {9u, 1u, 16u, "has space", false, 0u};
    BreakRuntimeBusKind quote_name = {10u, 1u, 16u, "q\"x", false, 0u};
    BreakRuntimeBusKind long_name = {11u, 1u, 16u, "abcdefghijklmnopqrstuvwxyz0123456789", false, 0u};
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &zero_version), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &big_budget), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &no_name), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &bad_name), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &quote_name), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &long_name), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_register_kind(NULL, &ok), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, NULL), BREAK_RUNTIME_INVALID);
    /* the registry is bounded */
    BreakRuntimeError last = BREAK_RUNTIME_OK;
    u32 added = 0u;
    for (u32 k = 100u; k < 100u + BREAK_RUNTIME_BUS_MAX_KINDS + 1u && last == BREAK_RUNTIME_OK; k++) {
        BreakRuntimeBusKind more = {(u16)k, 1u, 8u, "more", false, 0u};
        last = break_runtime_bus_register_kind(bus, &more);
        if (last == BREAK_RUNTIME_OK) added++;
    }
    ASSERT_EQ(last, BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(added, BREAK_RUNTIME_BUS_MAX_KINDS - 1u);
    break_runtime_bus_destroy(bus);
    break_runtime_bus_destroy(NULL);
}

TEST(publish_fans_out_to_subscribers_of_the_kind) {
    BreakRuntimeBus *bus = make_bus();
    ASSERT_NOT_NULL(bus);
    BreakRuntimeQueue *logic = make_queue(16u);
    BreakRuntimeQueue *ui = make_queue(16u);
    ASSERT_NOT_NULL(logic);
    ASSERT_NOT_NULL(ui);
    const u16 both[2] = {1u, 2u};
    const u16 only_input[1] = {1u};
    u32 logic_id = 0u, ui_id = 0u;
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "logic", logic, both, 2u, &logic_id), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "ui", ui, only_input, 1u, &ui_id), BREAK_RUNTIME_OK);
    ASSERT_TRUE(logic_id != 0u && ui_id != 0u && logic_id != ui_id);

    u32 key = 42u;
    BreakRuntimeMessageView v = view_of(1u, 2u, &key, sizeof key);
    u32 delivered = 99u;
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 2u);
    char snap[100];
    memset(snap, 7, sizeof snap);
    v = view_of(2u, 1u, snap, sizeof snap);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 1u);

    u16 kinds[8];
    ASSERT_EQ(drain(logic, kinds, 8u), 2u);
    ASSERT_EQ(kinds[0], 1u);
    ASSERT_EQ(kinds[1], 2u);
    ASSERT_EQ(drain(ui, kinds, 8u), 1u);
    ASSERT_EQ(kinds[0], 1u);

    /* each subscriber receives its own copy of the payload */
    v = view_of(1u, 1u, &key, sizeof key);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, NULL), BREAK_RUNTIME_OK);
    BreakRuntimeOwnedMessage *a = NULL, *b = NULL;
    ASSERT_EQ(break_runtime_queue_poll(logic, &a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_queue_poll(ui, &b), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(a);
    ASSERT_NOT_NULL(b);
    ASSERT_TRUE(a != b);
    BreakRuntimeMessageView va, vb;
    ASSERT_EQ(break_runtime_message_view(a, &va), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_message_view(b, &vb), BREAK_RUNTIME_OK);
    ASSERT_TRUE(va.data != vb.data && va.data != (const void *)&key);
    ASSERT_EQ(memcmp(va.data, &key, sizeof key), 0);
    break_runtime_message_release(a);
    break_runtime_message_release(b);

    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(logic);
    break_runtime_queue_destroy(ui);
}

TEST(unknown_kinds_versions_and_oversize_payloads_are_rejected) {
    BreakRuntimeBus *bus = make_bus();
    ASSERT_NOT_NULL(bus);
    BreakRuntimeQueue *q = make_queue(8u);
    ASSERT_NOT_NULL(q);
    const u16 kinds[2] = {1u, 2u};
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "logic", q, kinds, 2u, NULL), BREAK_RUNTIME_OK);
    u8 big[65];
    memset(big, 1, sizeof big);
    u32 delivered = 99u;
    BreakRuntimeMessageView v = view_of(3u, 1u, big, 1u);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(delivered, 0u);
    v = view_of(1u, 3u, big, 1u); /* newer than the registered version */
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_REJECTED);
    v = view_of(1u, 0u, big, 1u);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_REJECTED);
    v = view_of(1u, 1u, big, sizeof big); /* 65 > 64-byte budget */
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OVERLOAD);
    v = view_of(1u, 1u, NULL, 4u);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_publish(bus, NULL, &delivered), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_publish(NULL, &v, &delivered), BREAK_RUNTIME_INVALID);
    u16 none[1];
    ASSERT_EQ(drain(q, none, 1u), 0u);

    BreakRuntimeBusStats bs;
    ASSERT_EQ(break_runtime_bus_stats(bus, &bs), BREAK_RUNTIME_OK);
    ASSERT_EQ(bs.unknown_kind_rejects, 1u);
    BreakRuntimeBusKindStats ks;
    ASSERT_EQ(break_runtime_bus_kind_stats(bus, 1u, &ks), BREAK_RUNTIME_OK);
    ASSERT_EQ(ks.published, 0u);
    ASSERT_EQ(ks.version_rejects, 2u);
    ASSERT_EQ(ks.size_rejects, 1u);
    ASSERT_EQ(break_runtime_bus_kind_stats(bus, 3u, &ks), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_runtime_bus_kind_stats(bus, 1u, NULL), BREAK_RUNTIME_INVALID);
    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(q);
}

/* A full subscriber queue drops its copy without blocking the publisher or
 * starving the other subscribers; the publisher sees OVERLOAD and the
 * delivered count, and the drop is counted on that subscriber. */
TEST(full_subscriber_queue_is_backpressure_not_blocking) {
    BreakRuntimeBus *bus = make_bus();
    ASSERT_NOT_NULL(bus);
    BreakRuntimeQueue *slow = make_queue(2u);
    BreakRuntimeQueue *fast = make_queue(16u);
    ASSERT_NOT_NULL(slow);
    ASSERT_NOT_NULL(fast);
    const u16 input[1] = {1u};
    u32 slow_id = 0u, fast_id = 0u;
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "slow", slow, input, 1u, &slow_id), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "fast", fast, input, 1u, &fast_id), BREAK_RUNTIME_OK);
    u32 key = 1u;
    BreakRuntimeMessageView v = view_of(1u, 1u, &key, sizeof key);
    u32 delivered = 0u;
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OK);
    for (u32 i = 0; i < 3u; i++) {
        ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OVERLOAD);
        ASSERT_EQ(delivered, 1u);
    }
    BreakRuntimeBusSubscriberStats ss;
    ASSERT_EQ(break_runtime_bus_subscriber_stats(bus, slow_id, &ss), BREAK_RUNTIME_OK);
    ASSERT_EQ(ss.delivered, 2u);
    ASSERT_EQ(ss.dropped, 3u);
    ASSERT_EQ(break_runtime_bus_subscriber_stats(bus, fast_id, &ss), BREAK_RUNTIME_OK);
    ASSERT_EQ(ss.delivered, 5u);
    ASSERT_EQ(ss.dropped, 0u);
    BreakRuntimeBusKindStats ks;
    ASSERT_EQ(break_runtime_bus_kind_stats(bus, 1u, &ks), BREAK_RUNTIME_OK);
    ASSERT_EQ(ks.published, 5u);
    ASSERT_EQ(ks.delivered, 7u);
    ASSERT_EQ(ks.dropped, 3u);
    u16 kinds[16];
    ASSERT_EQ(drain(slow, kinds, 16u), 2u);
    ASSERT_EQ(drain(fast, kinds, 16u), 5u);
    /* once drained, delivery resumes */
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 2u);
    /* a closed subscriber queue also counts as a drop */
    break_runtime_queue_close(slow);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(delivered, 1u);
    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(slow);
    break_runtime_queue_destroy(fast);
}

TEST(subscriptions_are_validated_and_removable) {
    BreakRuntimeBus *bus = make_bus();
    ASSERT_NOT_NULL(bus);
    BreakRuntimeQueue *q = make_queue(8u);
    ASSERT_NOT_NULL(q);
    const u16 input[1] = {1u};
    const u16 unknown[1] = {9u};
    const u16 dup[2] = {1u, 1u};
    u32 id = 0u;
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "x", q, unknown, 1u, &id), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "x", q, dup, 2u, &id), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "x", NULL, input, 1u, &id), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "x", q, NULL, 1u, &id), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "x", q, input, 0u, &id), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "bad name", q, input, 1u, &id), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "x", q, input, 1u, &id), BREAK_RUNTIME_OK);
    u32 key = 1u;
    BreakRuntimeMessageView v = view_of(1u, 1u, &key, sizeof key);
    u32 delivered = 0u;
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 1u);
    ASSERT_EQ(break_runtime_bus_unsubscribe(bus, id), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_unsubscribe(bus, id), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_bus_unsubscribe(bus, 0u), BREAK_RUNTIME_STALE);
    BreakRuntimeBusSubscriberStats ss;
    ASSERT_EQ(break_runtime_bus_subscriber_stats(bus, id, &ss), BREAK_RUNTIME_STALE);
    /* no subscriber left: publishing is fine and delivers nothing */
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 0u);
    u16 kinds[4];
    ASSERT_EQ(drain(q, kinds, 4u), 1u);
    /* ids are not reused */
    u32 again = 0u;
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "x", q, input, 1u, &again), BREAK_RUNTIME_OK);
    ASSERT_TRUE(again != id);
    /* the subscriber table is bounded */
    BreakRuntimeError last = BREAK_RUNTIME_OK;
    u32 added = 1u;
    while (last == BREAK_RUNTIME_OK && added <= BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS) {
        last = break_runtime_bus_subscribe(bus, "more", q, input, 1u, NULL);
        if (last == BREAK_RUNTIME_OK) added++;
    }
    ASSERT_EQ(last, BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(added, BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS);
    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(q);
}

static usize count_substr(const char *haystack, const char *needle) {
    usize count = 0u;
    usize len = strlen(needle);
    for (const char *p = strstr(haystack, needle); p; p = strstr(p + len, needle)) count++;
    return count;
}

TEST(topology_export_lists_kinds_subscribers_and_counters) {
    BreakRuntimeBus *bus = make_bus();
    ASSERT_NOT_NULL(bus);
    BreakRuntimeQueue *logic = make_queue(1u);
    BreakRuntimeQueue *ui = make_queue(8u);
    ASSERT_NOT_NULL(logic);
    ASSERT_NOT_NULL(ui);
    const u16 both[2] = {1u, 2u};
    const u16 input[1] = {1u};
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "logic", logic, both, 2u, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "ui", ui, input, 1u, NULL), BREAK_RUNTIME_OK);
    u32 key = 1u;
    BreakRuntimeMessageView v = view_of(1u, 1u, &key, sizeof key);
    (void)break_runtime_bus_publish(bus, &v, NULL);
    (void)break_runtime_bus_publish(bus, &v, NULL); /* logic is full: one drop */
    v = view_of(77u, 1u, &key, sizeof key);
    (void)break_runtime_bus_publish(bus, &v, NULL);

    char buf[4096];
    usize len = 0u;
    ASSERT_EQ(break_runtime_bus_export_topology(bus, buf, sizeof buf, &len), BREAK_RUNTIME_OK);
    ASSERT_EQ(len, strlen(buf));
    ASSERT_EQ(buf[0], '{');
    ASSERT_EQ(buf[len - 1u], '}');
    ASSERT_NOT_NULL(strstr(buf, "\"unknown_kind_rejects\":1"));
    ASSERT_NOT_NULL(strstr(buf, "{\"kind\":1,\"name\":\"input.key\",\"max_version\":2,\"max_payload\":64,"
                                "\"control\":false,\"max_per_tick\":0,"
                                "\"published\":2,\"delivered\":3,\"dropped\":1,"));
    ASSERT_NOT_NULL(strstr(buf, "{\"kind\":2,\"name\":\"world.snapshot\""));
    ASSERT_NOT_NULL(strstr(buf, "\"name\":\"logic\",\"kinds\":[1,2],\"delivered\":1,\"dropped\":1,"
                                "\"queue\":{\"enqueued\":1,\"dequeued\":0,\"high_water\":1,"
                                "\"overload_rejects\":1}"));
    ASSERT_NOT_NULL(strstr(buf, "\"name\":\"ui\",\"kinds\":[1],\"delivered\":2,\"dropped\":0,"));
    ASSERT_EQ(count_substr(buf, "\"id\":"), 2u);

    char small[16];
    usize need = 0u;
    ASSERT_EQ(break_runtime_bus_export_topology(bus, small, sizeof small, &need), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(need, len);
    ASSERT_EQ(small[0], '\0');
    ASSERT_EQ(break_runtime_bus_export_topology(bus, NULL, 0u, &need), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(need, len);
    ASSERT_EQ(break_runtime_bus_export_topology(NULL, buf, sizeof buf, &need), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_bus_export_topology(bus, buf, sizeof buf, NULL), BREAK_RUNTIME_INVALID);

    u16 kinds[4];
    (void)drain(logic, kinds, 4u);
    (void)drain(ui, kinds, 4u);
    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(logic);
    break_runtime_queue_destroy(ui);
}

TEST(allocation_failure_is_reported_and_counted) {
    BreakRuntimeBus *bus = NULL;
    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OOM);
    ASSERT_EQ(bus, NULL);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    bus = make_bus();
    ASSERT_NOT_NULL(bus);
    BreakRuntimeQueue *q = make_queue(8u);
    ASSERT_NOT_NULL(q);
    const u16 input[1] = {1u};
    u32 id = 0u;
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "x", q, input, 1u, &id), BREAK_RUNTIME_OK);
    u32 key = 1u;
    BreakRuntimeMessageView v = view_of(1u, 1u, &key, sizeof key);
    u32 delivered = 9u;
    break_runtime_test_set_alloc_budget(0u);
    BreakRuntimeError err = break_runtime_bus_publish(bus, &v, &delivered);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    ASSERT_EQ(err, BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(delivered, 0u);
    BreakRuntimeBusSubscriberStats ss;
    ASSERT_EQ(break_runtime_bus_subscriber_stats(bus, id, &ss), BREAK_RUNTIME_OK);
    ASSERT_EQ(ss.dropped, 1u);
    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(q);
}

/* Publishers on several threads and a subscribe/unsubscribe churn: every
 * copy is either delivered or counted as dropped, and after unsubscribe
 * returns the bus never touches that queue again. */
typedef struct {
    BreakRuntimeBus *bus;
    _Atomic u32 *go;
    u32 published;
} PublisherCtx;

static PLATFORM_THREAD_RET publisher_main(PLATFORM_THREAD_ARG arg) {
    PublisherCtx *c = (PublisherCtx *)arg;
    while (!atomic_load(c->go)) platform_thread_yield();
    u32 key = 5u;
    BreakRuntimeMessageView v = view_of(1u, 1u, &key, sizeof key);
    for (u32 i = 0; i < 2000u; i++) {
        BreakRuntimeError e = break_runtime_bus_publish(c->bus, &v, NULL);
        if (e == BREAK_RUNTIME_OK || e == BREAK_RUNTIME_OVERLOAD) c->published++;
    }
    return PLATFORM_THREAD_RETURN;
}

TEST(concurrent_publishers_and_unsubscribe) {
    BreakRuntimeBus *bus = make_bus();
    ASSERT_NOT_NULL(bus);
    /* bounded below the test build's 4096 live-message registry */
    BreakRuntimeQueue *keep = make_queue(1024u);
    BreakRuntimeQueue *churn = make_queue(1024u);
    ASSERT_NOT_NULL(keep);
    ASSERT_NOT_NULL(churn);
    const u16 input[1] = {1u};
    u32 keep_id = 0u;
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "keep", keep, input, 1u, &keep_id), BREAK_RUNTIME_OK);
    _Atomic u32 go;
    atomic_init(&go, 0u);
    PublisherCtx ctx[3];
    PlatformThread threads[3];
    for (u32 i = 0; i < 3u; i++) {
        ctx[i].bus = bus;
        ctx[i].go = &go;
        ctx[i].published = 0u;
        ASSERT_TRUE(platform_thread_create(&threads[i], publisher_main, &ctx[i]));
    }
    atomic_store(&go, 1u);
    u64 churn_delivered = 0u;
    u64 keep_drained = 0u;
    for (u32 round = 0; round < 50u; round++) {
        u32 id = 0u;
        if (break_runtime_bus_subscribe(bus, "churn", churn, input, 1u, &id) != BREAK_RUNTIME_OK) continue;
        platform_thread_yield();
        ASSERT_EQ(break_runtime_bus_unsubscribe(bus, id), BREAK_RUNTIME_OK);
        BreakRuntimeQueueStats before, after;
        ASSERT_EQ(break_runtime_queue_stats(churn, &before), BREAK_RUNTIME_OK);
        platform_thread_yield();
        ASSERT_EQ(break_runtime_queue_stats(churn, &after), BREAK_RUNTIME_OK);
        ASSERT_EQ(after.enqueued + after.overload_rejects, before.enqueued + before.overload_rejects);
        u16 kinds[1];
        churn_delivered += drain(churn, kinds, 0u);
        keep_drained += drain(keep, kinds, 0u);
    }
    for (u32 i = 0; i < 3u; i++) platform_thread_join(threads[i]);
    u32 published = ctx[0].published + ctx[1].published + ctx[2].published;
    ASSERT_EQ(published, 6000u);
    BreakRuntimeBusSubscriberStats ks;
    ASSERT_EQ(break_runtime_bus_subscriber_stats(bus, keep_id, &ks), BREAK_RUNTIME_OK);
    ASSERT_EQ(ks.delivered + ks.dropped, 6000u);
    u16 kinds[1];
    keep_drained += drain(keep, kinds, 0u);
    ASSERT_EQ(keep_drained, ks.delivered);
    BreakRuntimeBusKindStats kst;
    ASSERT_EQ(break_runtime_bus_kind_stats(bus, 1u, &kst), BREAK_RUNTIME_OK);
    ASSERT_EQ(kst.published, 6000u);
    ASSERT_EQ(kst.delivered, ks.delivered + churn_delivered);
    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(keep);
    break_runtime_queue_destroy(churn);
}

/* A control kind's copies carry BREAK_RUNTIME_MESSAGE_FLAG_CONTROL, so they
 * use the subscriber queue's reserved control slots and still arrive when
 * ordinary data has filled the queue. */
TEST(control_kinds_use_reserved_queue_capacity) {
    BreakRuntimeBus *bus = make_bus();
    ASSERT_NOT_NULL(bus);
    BreakRuntimeBusKind shutdown = {3u, 1u, 8u, "core.shutdown", true, 0u};
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &shutdown), BREAK_RUNTIME_OK);
    BreakRuntimeQueueConfig cfg = {4u, 1u};
    BreakRuntimeQueue *q = NULL;
    ASSERT_EQ(break_runtime_queue_create(&cfg, &q), BREAK_RUNTIME_OK);
    const u16 kinds[2] = {1u, 3u};
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "logic", q, kinds, 2u, NULL), BREAK_RUNTIME_OK);
    u32 key = 1u;
    BreakRuntimeMessageView v = view_of(1u, 1u, &key, sizeof key);
    for (u32 i = 0; i < 3u; i++) ASSERT_EQ(break_runtime_bus_publish(bus, &v, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, NULL), BREAK_RUNTIME_OVERLOAD); /* data region full */
    v = view_of(3u, 1u, NULL, 0u);
    u32 delivered = 0u;
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 1u);
    u16 got[8];
    ASSERT_EQ(drain(q, got, 8u), 4u);
    ASSERT_EQ(got[3], 3u);
    /* ordinary kinds never carry the flag, even if the publisher sets it */
    v = view_of(1u, 1u, &key, sizeof key);
    v.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
    for (u32 i = 0; i < 3u; i++) ASSERT_EQ(break_runtime_bus_publish(bus, &v, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_publish(bus, &v, NULL), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(drain(q, got, 8u), 3u);
    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(q);
}

/* A kind with max_per_tick accepts that many publishes between two
 * break_runtime_bus_tick calls; the rest are OVERLOAD, delivered to nobody
 * and counted, and other kinds are unaffected. */
TEST(per_tick_quota_limits_a_kind) {
    BreakRuntimeBus *bus = make_bus();
    ASSERT_NOT_NULL(bus);
    BreakRuntimeBusKind chatter = {4u, 1u, 8u, "debug.chatter", false, 3u};
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &chatter), BREAK_RUNTIME_OK);
    BreakRuntimeQueue *q = make_queue(64u);
    ASSERT_NOT_NULL(q);
    const u16 kinds[2] = {1u, 4u};
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "logic", q, kinds, 2u, NULL), BREAK_RUNTIME_OK);
    BreakRuntimeMessageView c = view_of(4u, 1u, NULL, 0u);
    u32 key = 1u;
    BreakRuntimeMessageView in = view_of(1u, 1u, &key, sizeof key);
    u32 delivered = 9u;
    for (u32 i = 0; i < 3u; i++) ASSERT_EQ(break_runtime_bus_publish(bus, &c, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_publish(bus, &c, &delivered), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(delivered, 0u);
    ASSERT_EQ(break_runtime_bus_publish(bus, &c, NULL), BREAK_RUNTIME_OVERLOAD);
    for (u32 i = 0; i < 10u; i++) ASSERT_EQ(break_runtime_bus_publish(bus, &in, NULL), BREAK_RUNTIME_OK);
    BreakRuntimeBusKindStats ks;
    ASSERT_EQ(break_runtime_bus_kind_stats(bus, 4u, &ks), BREAK_RUNTIME_OK);
    ASSERT_EQ(ks.published, 3u);
    ASSERT_EQ(ks.quota_rejects, 2u);
    ASSERT_EQ(ks.dropped, 0u);
    ASSERT_EQ(break_runtime_bus_tick(bus), BREAK_RUNTIME_OK);
    for (u32 i = 0; i < 3u; i++) ASSERT_EQ(break_runtime_bus_publish(bus, &c, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_publish(bus, &c, NULL), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_runtime_bus_tick(NULL), BREAK_RUNTIME_INVALID);
    u16 got[32];
    ASSERT_EQ(drain(q, got, 32u), 16u);
    char buf[4096];
    usize len = 0u;
    ASSERT_EQ(break_runtime_bus_export_topology(bus, buf, sizeof buf, &len), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(strstr(buf, "\"name\":\"debug.chatter\",\"max_version\":1,\"max_payload\":8,"
                                "\"control\":false,\"max_per_tick\":3,\"published\":6,"));
    ASSERT_NOT_NULL(strstr(buf, "\"quota_rejects\":3}"));
    break_runtime_bus_destroy(bus);
    break_runtime_queue_destroy(q);
}

TEST_MAIN_BEGIN()
    RUN_TEST(kind_registration_is_validated);
    RUN_TEST(publish_fans_out_to_subscribers_of_the_kind);
    RUN_TEST(unknown_kinds_versions_and_oversize_payloads_are_rejected);
    RUN_TEST(full_subscriber_queue_is_backpressure_not_blocking);
    RUN_TEST(subscriptions_are_validated_and_removable);
    RUN_TEST(topology_export_lists_kinds_subscribers_and_counters);
    RUN_TEST(allocation_failure_is_reported_and_counted);
    RUN_TEST(concurrent_publishers_and_unsubscribe);
    RUN_TEST(control_kinds_use_reserved_queue_capacity);
    RUN_TEST(per_tick_quota_limits_a_kind);
TEST_MAIN_END()
