#include "test_framework.h"
#include <runtime/runtime_message.h>
#include <runtime/runtime_queue.h>
#include <runtime/runtime_bus.h>
#include <runtime/runtime_metrics.h>
#include <runtime/runtime_task.h>
#include <runtime/runtime_test_hooks.h>
#include <core/platform_thread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32)
#include <sys/types.h>
#include <sys/wait.h>
#endif

/* Focused contract tests for the Runtime Core formal facade: owned messages,
 * bounded MPSC queue, and the formal task submit API. Links the test-only
 * runtime_core_test variant (BREAK_RUNTIME_TESTING=1) for allocation failure
 * injection and double-release rejection; the production runtime_core target
 * is exercised unchanged by test_runtime_core. */

/* ------------------------------------------------------------------ */
/* helpers                                                             */
/* ------------------------------------------------------------------ */

static BreakRuntimeOwnedMessage *make_pair_msg(u16 kind, u64 sequence,
                                               u32 flags, u32 a, u32 b)
{
    u32 payload[2];
    BreakRuntimeMessageView view;
    BreakRuntimeOwnedMessage *msg = NULL;
    payload[0] = a;
    payload[1] = b;
    memset(&view, 0, sizeof(view));
    view.kind = kind;
    view.version = 1u;
    view.flags = flags;
    view.sequence = sequence;
    view.data = payload;
    view.size = sizeof(payload);
    if (break_runtime_message_copy(&view, &msg) != BREAK_RUNTIME_OK) {
        return NULL;
    }
    return msg;
}

static BreakRuntimeOwnedMessage *make_value_msg(u64 sequence, u32 value)
{
    BreakRuntimeMessageView view;
    BreakRuntimeOwnedMessage *msg = NULL;
    memset(&view, 0, sizeof(view));
    view.kind = 7u;
    view.version = 1u;
    view.sequence = sequence;
    view.data = &value;
    view.size = sizeof(value);
    if (break_runtime_message_copy(&view, &msg) != BREAK_RUNTIME_OK) {
        return NULL;
    }
    return msg;
}

static u32 msg_first_u32(const BreakRuntimeOwnedMessage *msg)
{
    BreakRuntimeMessageView view;
    u32 value = 0u;
    if (break_runtime_message_view(msg, &view) == BREAK_RUNTIME_OK &&
        view.size >= sizeof(u32)) {
        memcpy(&value, view.data, sizeof(value));
    }
    return value;
}

static void test_sleep_ms(long ms)
{
#if defined(_WIN32)
    Sleep((unsigned long)ms);
#else
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
#endif
}

/* ------------------------------------------------------------------ */
/* owned messages                                                      */
/* ------------------------------------------------------------------ */

TEST(message_copy_produces_independent_owned_bytes)
{
    u8 source[64];
    BreakRuntimeMessageView view;
    BreakRuntimeMessageView owned_view;
    BreakRuntimeOwnedMessage *msg = NULL;
    int i;

    for (i = 0; i < 64; i++) {
        source[i] = (u8)(i * 3 + 1);
    }
    memset(&view, 0, sizeof(view));
    view.kind = 42u;
    view.version = 3u;
    view.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
    view.sequence = 9001u;
    view.data = source;
    view.size = sizeof(source);

    ASSERT_EQ(break_runtime_message_copy(&view, &msg), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);

    /* Mutating/freeing the producer buffer must not disturb the owned copy. */
    memset(source, 0xFF, sizeof(source));

    ASSERT_EQ(break_runtime_message_view(msg, &owned_view), BREAK_RUNTIME_OK);
    ASSERT_EQ(owned_view.kind, 42u);
    ASSERT_EQ(owned_view.version, 3u);
    ASSERT_EQ(owned_view.flags, BREAK_RUNTIME_MESSAGE_FLAG_CONTROL);
    ASSERT_EQ(owned_view.sequence, 9001u);
    ASSERT_EQ(owned_view.size, sizeof(source));
    for (i = 0; i < 64; i++) {
        ASSERT_EQ(((const u8 *)owned_view.data)[i], (u8)(i * 3 + 1));
    }

    break_runtime_message_release(msg);
    break_runtime_message_release(NULL); /* NULL release is a no-op */
}

TEST(message_copy_validates_null_and_size)
{
    BreakRuntimeMessageView view;
    BreakRuntimeOwnedMessage *msg = NULL;
    u32 payload = 7u;

    memset(&view, 0, sizeof(view));
    view.kind = 1u;
    view.version = 1u;
    view.data = &payload;
    view.size = sizeof(payload);

    /* NULL arguments are malformed. */
    ASSERT_EQ(break_runtime_message_copy(NULL, &msg), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(msg, NULL);
    ASSERT_EQ(break_runtime_message_copy(&view, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_message_view(NULL, &view), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_message_view(msg, NULL), BREAK_RUNTIME_INVALID);

    /* Claimed payload bytes without data are malformed. */
    view.data = NULL;
    view.size = 5u;
    msg = NULL;
    ASSERT_EQ(break_runtime_message_copy(&view, &msg), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(msg, NULL);

    /* Over-budget payloads map to OVERLOAD (never truncated/fragmented). */
    view.data = &payload;
    view.size = (usize)BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD + 1u;
    ASSERT_EQ(break_runtime_message_copy(&view, &msg), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(msg, NULL);

    /* Zero payload is legal. */
    view.data = NULL;
    view.size = 0u;
    view.sequence = 123u;
    ASSERT_EQ(break_runtime_message_copy(&view, &msg), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(break_runtime_message_view(msg, &view), BREAK_RUNTIME_OK);
    ASSERT_EQ(view.size, 0u);
    ASSERT_EQ(view.sequence, 123u);
    break_runtime_message_release(msg);
}

TEST(message_double_release_aborts_in_test_builds)
{
#if !defined(_WIN32)
    pid_t pid = fork();
    if (pid == 0) {
        BreakRuntimeOwnedMessage *msg = make_pair_msg(1u, 1u, 0u, 1u, 2u);
        if (!msg) {
            _exit(2); /* copy itself failed: not the path under test */
        }
        break_runtime_message_release(msg);
        break_runtime_message_release(msg); /* contract violation: must abort */
        _exit(0); /* reached only if double release was NOT rejected */
    }
    ASSERT_TRUE(pid > 0);
    {
        int status = 0;
        ASSERT_EQ(waitpid(pid, &status, 0), pid);
        /* abort() terminates by signal; a clean exit means the double
         * release slipped through. */
        ASSERT_TRUE(WIFSIGNALED(status));
    }
    /* Normal single release in the parent stays functional afterwards. */
    {
        BreakRuntimeOwnedMessage *msg = make_pair_msg(1u, 2u, 0u, 3u, 4u);
        ASSERT_NOT_NULL(msg);
        break_runtime_message_release(msg);
    }
#endif
}

TEST(message_allocation_failure_injection)
{
    u32 payload = 1u;
    BreakRuntimeMessageView view;
    BreakRuntimeOwnedMessage *msg = NULL;

    memset(&view, 0, sizeof(view));
    view.kind = 1u;
    view.version = 1u;
    view.data = &payload;
    view.size = sizeof(payload);

    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_message_copy(&view, &msg), BREAK_RUNTIME_OOM);
    ASSERT_EQ(msg, NULL);

    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    ASSERT_EQ(break_runtime_message_copy(&view, &msg), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    break_runtime_message_release(msg);
}

/* ------------------------------------------------------------------ */
/* bounded MPSC queue                                                  */
/* ------------------------------------------------------------------ */

TEST(queue_fifo_order_and_stats)
{
    BreakRuntimeQueue *q = NULL;
    BreakRuntimeQueueStats stats;
    BreakRuntimeOwnedMessage *msg = NULL;
    u64 gen;
    int i;

    ASSERT_EQ(break_runtime_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(q);
    gen = break_runtime_queue_generation(q);
    ASSERT_NEQ(gen, 0u);

    for (i = 1; i <= 4; i++) {
        msg = make_value_msg((u64)i, (u32)i);
        ASSERT_NOT_NULL(msg);
        ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OK);
    }

    for (i = 1; i <= 4; i++) {
        msg = NULL;
        ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
        ASSERT_NOT_NULL(msg);
        ASSERT_EQ(msg_first_u32(msg), (u32)i);
        break_runtime_message_release(msg);
    }

    /* Empty but open: non-blocking poll reports OK with no message. */
    msg = NULL;
    ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
    ASSERT_EQ(msg, NULL);

    ASSERT_EQ(break_runtime_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.enqueued, 4u);
    ASSERT_EQ(stats.dequeued, 4u);
    ASSERT_EQ(stats.high_water, 4u);
    ASSERT_EQ(stats.overload_rejects, 0u);

    /* Malformed calls. */
    ASSERT_EQ(break_runtime_queue_poll(NULL, &msg), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_poll(q, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_wait(q, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_enqueue(NULL, NULL, gen),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_enqueue(q, NULL, gen),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_stats(NULL, &stats), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_stats(q, NULL), BREAK_RUNTIME_INVALID);

    break_runtime_queue_destroy(q);
    break_runtime_queue_destroy(NULL);
}

TEST(queue_reserved_control_capacity)
{
    BreakRuntimeQueueConfig cfg;
    BreakRuntimeQueue *q = NULL;
    BreakRuntimeQueueStats stats;
    BreakRuntimeOwnedMessage *msg;
    u64 gen;
    int i;

    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = 4u;
    cfg.reserved_control = 1u;
    ASSERT_EQ(break_runtime_queue_create(&cfg, &q), BREAK_RUNTIME_OK);
    gen = break_runtime_queue_generation(q);

    /* Data region holds capacity - reserved == 3 messages. */
    for (i = 1; i <= 3; i++) {
        msg = make_value_msg((u64)i, (u32)i);
        ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OK);
    }
    msg = make_value_msg(4u, 4u);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OVERLOAD);
    break_runtime_message_release(msg); /* caller keeps ownership on failure */

    /* Control messages still enqueue into the reserved slot. */
    msg = make_value_msg(5u, 5u);
    {
        BreakRuntimeMessageView view;
        BreakRuntimeOwnedMessage *control = NULL;
        u32 payload = 5u;
        memset(&view, 0, sizeof(view));
        view.kind = 7u;
        view.version = 1u;
        view.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
        view.sequence = 5u;
        view.data = &payload;
        view.size = sizeof(payload);
        ASSERT_EQ(break_runtime_message_copy(&view, &control), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_queue_enqueue(q, control, gen),
                  BREAK_RUNTIME_OK);
    }

    /* Now even control is full. */
    msg = make_value_msg(6u, 6u);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OVERLOAD);
    break_runtime_message_release(msg);

    /* FIFO across classes: enqueue order is preserved. The rejected 4th data
     * message never entered, so the drained sequence is 1,2,3,5. */
    {
        static const u32 expected_values[] = {1u, 2u, 3u, 5u};
        for (i = 0; i < 4; i++) {
            msg = NULL;
            ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
            ASSERT_NOT_NULL(msg);
            ASSERT_EQ(msg_first_u32(msg), expected_values[i]);
            break_runtime_message_release(msg);
        }
    }

    ASSERT_EQ(break_runtime_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.enqueued, 4u);
    ASSERT_EQ(stats.overload_rejects, 2u);
    ASSERT_EQ(stats.high_water, 4u);

    break_runtime_queue_destroy(q);

    /* Malformed configs are rejected at create. */
    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = 2u;
    cfg.reserved_control = 3u;
    q = NULL;
    ASSERT_EQ(break_runtime_queue_create(&cfg, &q), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(q, NULL);
    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = BREAK_RUNTIME_QUEUE_MAX_CAPACITY + 1u;
    ASSERT_EQ(break_runtime_queue_create(&cfg, &q), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_create(NULL, NULL), BREAK_RUNTIME_INVALID);

    break_runtime_queue_destroy(q);
}

TEST(queue_stale_generation_rejected)
{
    BreakRuntimeQueue *q = NULL;
    BreakRuntimeQueueStats stats;
    BreakRuntimeOwnedMessage *msg;
    u64 gen0;
    u64 gen1;

    ASSERT_EQ(break_runtime_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    gen0 = break_runtime_queue_generation(q);
    gen1 = break_runtime_queue_advance_generation(q);
    ASSERT_EQ(gen1, gen0 + 1u);
    ASSERT_EQ(break_runtime_queue_generation(q), gen1);

    /* A producer holding the old epoch is classified STALE and keeps its
     * owned payload. */
    msg = make_value_msg(1u, 11u);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen0), BREAK_RUNTIME_STALE);
    break_runtime_message_release(msg);

    /* The current epoch enqueues and polls normally. */
    msg = make_value_msg(2u, 22u);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen1), BREAK_RUNTIME_OK);
    msg = NULL;
    ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(msg_first_u32(msg), 22u);
    break_runtime_message_release(msg);

    /* close() also advances the generation. */
    break_runtime_queue_close(q);
    ASSERT_EQ(break_runtime_queue_generation(q), gen1 + 1u);

    ASSERT_EQ(break_runtime_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.stale_rejects, 1u);
    ASSERT_EQ(stats.enqueued, 1u);

    break_runtime_queue_destroy(q);
}

TEST(queue_control_fill_then_data_overload_keeps_ring_intact)
{
    /* Regression (review Critical 1): control messages may legitimately
     * occupy EVERY physical slot. A data enqueue into a control-filled ring
     * must report OVERLOAD; admitting it would overwrite the live head slot
     * (message loss, FIFO corruption, double release at destroy). */
    BreakRuntimeQueueConfig cfg;
    BreakRuntimeQueue *q = NULL;
    BreakRuntimeQueueStats stats;
    BreakRuntimeOwnedMessage *msg;
    u64 gen;
    int i;

    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = 4u;
    cfg.reserved_control = 1u;
    ASSERT_EQ(break_runtime_queue_create(&cfg, &q), BREAK_RUNTIME_OK);
    gen = break_runtime_queue_generation(q);

    /* Controls spill beyond the reserved slot and fill the whole ring. */
    for (i = 1; i <= 4; i++) {
        msg = make_value_msg((u64)i, (u32)i);
        ASSERT_NOT_NULL(msg);
        {
            BreakRuntimeMessageView view;
            BreakRuntimeOwnedMessage *control = NULL;
            u32 payload = (u32)i;
            memset(&view, 0, sizeof(view));
            view.kind = 7u;
            view.version = 1u;
            view.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
            view.sequence = (u64)i;
            view.data = &payload;
            view.size = sizeof(payload);
            ASSERT_EQ(break_runtime_message_copy(&view, &control),
                      BREAK_RUNTIME_OK);
            break_runtime_message_release(msg);
            ASSERT_EQ(break_runtime_queue_enqueue(q, control, gen),
                      BREAK_RUNTIME_OK);
        }
    }

    /* The ring is physically full: a data enqueue MUST be rejected. (On the
     * buggy admission this returned OK and corrupted the ring; the early
     * assertion return keeps the RED run at assertion level.) */
    msg = make_value_msg(99u, 99u);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OVERLOAD);
    break_runtime_message_release(msg);

    /* Ring intact: all four controls drain in FIFO order. */
    for (i = 1; i <= 4; i++) {
        msg = NULL;
        ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
        ASSERT_NOT_NULL(msg);
        ASSERT_EQ(msg_first_u32(msg), (u32)i);
        break_runtime_message_release(msg);
    }
    msg = NULL;
    ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
    ASSERT_EQ(msg, NULL);

    ASSERT_EQ(break_runtime_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.enqueued, 4u);
    ASSERT_EQ(stats.dequeued, 4u);
    ASSERT_EQ(stats.overload_rejects, 1u);

    /* Destroy on an uncorrupted ring: every slot released exactly once. */
    break_runtime_queue_destroy(q);
}

TEST(queue_mixed_control_data_wraparound_fifo)
{
    /* Regression (review Important 2): mixed control/data interleavings keep
     * FIFO within the physical ring, including after wraparound; once the
     * ring is physically full, BOTH classes report OVERLOAD. */
    BreakRuntimeQueueConfig cfg;
    BreakRuntimeQueue *q = NULL;
    BreakRuntimeOwnedMessage *msg;
    u64 gen;
    int i;
    static const u32 phase_a[] = {1u, 2u, 3u, 4u, 5u, 6u};
    static const u32 phase_b[] = {4u, 5u, 6u, 7u, 8u, 9u};

    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = 6u;
    cfg.reserved_control = 2u;
    ASSERT_EQ(break_runtime_queue_create(&cfg, &q), BREAK_RUNTIME_OK);
    gen = break_runtime_queue_generation(q);

    /* Phase A: interleave d1,c1,d2,c2,d3,c3 — ring physically full. */
    for (i = 0; i < 6; i++) {
        u32 value = phase_a[i];
        int is_control = (i % 2) == 1;
        BreakRuntimeMessageView view;
        BreakRuntimeOwnedMessage *m = NULL;
        memset(&view, 0, sizeof(view));
        view.kind = 7u;
        view.version = 1u;
        view.flags = is_control ? BREAK_RUNTIME_MESSAGE_FLAG_CONTROL : 0u;
        view.sequence = (u64)value;
        view.data = &value;
        view.size = sizeof(value);
        ASSERT_EQ(break_runtime_message_copy(&view, &m), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_queue_enqueue(q, m, gen), BREAK_RUNTIME_OK);
    }

    /* Full ring: data AND control both reject. */
    msg = make_value_msg(70u, 70u);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OVERLOAD);
    break_runtime_message_release(msg);
    {
        BreakRuntimeMessageView view;
        BreakRuntimeOwnedMessage *control = NULL;
        u32 payload = 71u;
        memset(&view, 0, sizeof(view));
        view.kind = 7u;
        view.version = 1u;
        view.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
        view.sequence = 71u;
        view.data = &payload;
        view.size = sizeof(payload);
        ASSERT_EQ(break_runtime_message_copy(&view, &control),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_queue_enqueue(q, control, gen),
                  BREAK_RUNTIME_OVERLOAD);
        break_runtime_message_release(control);
    }

    /* Drain three (head moves to mid-ring), then interleave c,d,c into the
     * freed slots — the ring wraps. */
    for (i = 0; i < 3; i++) {
        msg = NULL;
        ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
        ASSERT_NOT_NULL(msg);
        ASSERT_EQ(msg_first_u32(msg), phase_a[i]);
        break_runtime_message_release(msg);
    }
    for (i = 7; i <= 9; i++) {
        u32 value = (u32)i;
        int is_control = (i != 8);
        BreakRuntimeMessageView view;
        BreakRuntimeOwnedMessage *m = NULL;
        memset(&view, 0, sizeof(view));
        view.kind = 7u;
        view.version = 1u;
        view.flags = is_control ? BREAK_RUNTIME_MESSAGE_FLAG_CONTROL : 0u;
        view.sequence = (u64)value;
        view.data = &value;
        view.size = sizeof(value);
        ASSERT_EQ(break_runtime_message_copy(&view, &m), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_queue_enqueue(q, m, gen), BREAK_RUNTIME_OK);
    }

    /* Wrapped ring is physically full again: data_count (2) < capacity -
     * reserved (4) would wrongly admit without the physical-slot guard. */
    msg = make_value_msg(72u, 72u);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OVERLOAD);
    break_runtime_message_release(msg);

    /* FIFO order survives the wrap: 4,5,6,7,8,9. */
    for (i = 0; i < 6; i++) {
        msg = NULL;
        ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
        ASSERT_NOT_NULL(msg);
        ASSERT_EQ(msg_first_u32(msg), phase_b[i]);
        break_runtime_message_release(msg);
    }
    msg = NULL;
    ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
    ASSERT_EQ(msg, NULL);

    break_runtime_queue_destroy(q);
}

TEST(queue_allocation_failure_injection)
{
    BreakRuntimeQueue *q = NULL;

    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_queue_create(NULL, &q), BREAK_RUNTIME_OOM);
    ASSERT_EQ(q, NULL);

    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    ASSERT_EQ(break_runtime_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(q);
    break_runtime_queue_destroy(q);
}

/* ------------------------------------------------------------------ */
/* shutdown wakeup                                                     */
/* ------------------------------------------------------------------ */

typedef struct WaiterCtx {
    BreakRuntimeQueue *queue;
    _Atomic int *ready;
    BreakRuntimeError result;
    BreakRuntimeOwnedMessage *msg;
} WaiterCtx;

static PLATFORM_THREAD_RET waiter_main(PLATFORM_THREAD_ARG arg)
{
    WaiterCtx *w = (WaiterCtx *)arg;
    atomic_fetch_add_explicit(w->ready, 1, memory_order_release);
    w->result = break_runtime_queue_wait(w->queue, &w->msg);
    return PLATFORM_THREAD_RETURN;
}

TEST(queue_close_wakes_waiters_and_stops_admission)
{
    BreakRuntimeQueue *q = NULL;
    PlatformThread threads[2];
    WaiterCtx waiters[2];
    _Atomic int ready;
    BreakRuntimeOwnedMessage *msg;
    u64 gen;
    int i;

    ASSERT_EQ(break_runtime_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    gen = break_runtime_queue_generation(q);
    atomic_store(&ready, 0);
    memset(waiters, 0, sizeof(waiters));
    for (i = 0; i < 2; i++) {
        waiters[i].queue = q;
        waiters[i].ready = &ready;
        waiters[i].result = BREAK_RUNTIME_OK;
        waiters[i].msg = NULL;
        ASSERT_TRUE(platform_thread_create(&threads[i], waiter_main,
                                           &waiters[i]));
    }
    while (atomic_load_explicit(&ready, memory_order_acquire) != 2) {
        platform_thread_yield();
    }
    /* Give both waiters the chance to actually block inside wait(). */
    test_sleep_ms(20);

    /* Shutdown wakeup: close releases every waiter. */
    break_runtime_queue_close(q);
    for (i = 0; i < 2; i++) {
        platform_thread_join(threads[i]);
        ASSERT_EQ(waiters[i].result, BREAK_RUNTIME_CLOSED);
        ASSERT_EQ(waiters[i].msg, NULL);
    }

    /* Admission stays shut after close. */
    msg = make_value_msg(1u, 1u);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg,
                                          break_runtime_queue_generation(q)),
              BREAK_RUNTIME_CLOSED);
    break_runtime_message_release(msg);

    /* Poll on a closed, drained queue reports CLOSED. */
    msg = NULL;
    ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(msg, NULL);

    /* close() is idempotent. */
    break_runtime_queue_close(q);
    break_runtime_queue_destroy(q);

    /* A closed queue still drains queued messages before reporting CLOSED. */
    ASSERT_EQ(break_runtime_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    gen = break_runtime_queue_generation(q);
    msg = make_value_msg(9u, 9u);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OK);
    break_runtime_queue_close(q);
    msg = NULL;
    ASSERT_EQ(break_runtime_queue_wait(q, &msg), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(msg_first_u32(msg), 9u);
    break_runtime_message_release(msg);
    msg = NULL;
    ASSERT_EQ(break_runtime_queue_wait(q, &msg), BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(msg, NULL);
    break_runtime_queue_destroy(q);
}

/* ------------------------------------------------------------------ */
/* MPSC concurrency                                                    */
/* ------------------------------------------------------------------ */

#define MPSC_PRODUCERS 4
#define MPSC_PER_PRODUCER 32

typedef struct ProducerCtx {
    BreakRuntimeQueue *queue;
    u64 generation;
    u32 id;
    int failures;
} ProducerCtx;

static PLATFORM_THREAD_RET producer_main(PLATFORM_THREAD_ARG arg)
{
    ProducerCtx *p = (ProducerCtx *)arg;
    u32 j;
    for (j = 0; j < (u32)MPSC_PER_PRODUCER; j++) {
        BreakRuntimeOwnedMessage *msg =
            make_pair_msg((u16)p->id, (u64)j, 0u, p->id, j);
        if (!msg) {
            p->failures++;
            break;
        }
        if (break_runtime_queue_enqueue(p->queue, msg, p->generation) !=
            BREAK_RUNTIME_OK) {
            break_runtime_message_release(msg);
            p->failures++;
        }
    }
    return PLATFORM_THREAD_RETURN;
}

TEST(queue_mpsc_producers_single_consumer)
{
    BreakRuntimeQueueConfig cfg;
    BreakRuntimeQueue *q = NULL;
    BreakRuntimeQueueStats stats;
    PlatformThread threads[MPSC_PRODUCERS];
    ProducerCtx producers[MPSC_PRODUCERS];
    u32 next[MPSC_PRODUCERS];
    u32 seen[MPSC_PRODUCERS];
    int total = 0;
    int i;

    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = (u32)(MPSC_PRODUCERS * MPSC_PER_PRODUCER);
    ASSERT_EQ(break_runtime_queue_create(&cfg, &q), BREAK_RUNTIME_OK);

    for (i = 0; i < MPSC_PRODUCERS; i++) {
        producers[i].queue = q;
        producers[i].generation = break_runtime_queue_generation(q);
        producers[i].id = (u32)i;
        producers[i].failures = 0;
        next[i] = 0u;
        seen[i] = 0u;
        ASSERT_TRUE(platform_thread_create(&threads[i], producer_main,
                                           &producers[i]));
    }
    for (i = 0; i < MPSC_PRODUCERS; i++) {
        platform_thread_join(threads[i]);
        ASSERT_EQ(producers[i].failures, 0);
    }

    /* Single consumer: every message arrives exactly once, and each
     * producer's messages keep their per-producer FIFO order. */
    for (;;) {
        BreakRuntimeOwnedMessage *msg = NULL;
        BreakRuntimeMessageView view;
        u32 pair[2] = {0u, 0u};
        ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
        if (!msg) {
            break;
        }
        ASSERT_EQ(break_runtime_message_view(msg, &view), BREAK_RUNTIME_OK);
        ASSERT_EQ(view.size, sizeof(pair));
        memcpy(pair, view.data, sizeof(pair));
        ASSERT_TRUE(pair[0] < (u32)MPSC_PRODUCERS);
        ASSERT_EQ(pair[1], next[pair[0]]);
        next[pair[0]]++;
        seen[pair[0]]++;
        total++;
        break_runtime_message_release(msg);
    }
    ASSERT_EQ(total, MPSC_PRODUCERS * MPSC_PER_PRODUCER);
    for (i = 0; i < MPSC_PRODUCERS; i++) {
        ASSERT_EQ(seen[i], (u32)MPSC_PER_PRODUCER);
    }

    ASSERT_EQ(break_runtime_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.enqueued, (u64)(MPSC_PRODUCERS * MPSC_PER_PRODUCER));
    ASSERT_EQ(stats.overload_rejects, 0u);

    break_runtime_queue_destroy(q);
}

/* ------------------------------------------------------------------ */
/* formal task facade                                                  */
/* ------------------------------------------------------------------ */

static _Atomic u32 g_inline_probe_ran;
static _Atomic u64 g_task_sum;
static _Atomic u32 g_task_ran;

static void inline_probe_task(BreakRuntimeOwnedMessage *payload)
{
    atomic_fetch_add(&g_inline_probe_ran, 1u);
    break_runtime_message_release(payload);
}

static void accumulate_task(BreakRuntimeOwnedMessage *payload)
{
    BreakRuntimeMessageView view;
    if (payload &&
        break_runtime_message_view(payload, &view) == BREAK_RUNTIME_OK &&
        view.size == sizeof(u32)) {
        u32 value = 0u;
        memcpy(&value, view.data, sizeof(value));
        atomic_fetch_add(&g_task_sum, (u64)value);
    }
    atomic_fetch_add(&g_task_ran, 1u);
    break_runtime_message_release(payload);
}

TEST(task_submit_overload_never_inlines)
{
    BreakRuntimeTaskConfig cfg;
    BreakRuntimeTaskQueue *q = NULL;
    BreakRuntimeTaskStats stats;

    atomic_store(&g_inline_probe_ran, 0u);
    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = 2u;
    ASSERT_EQ(break_runtime_task_queue_create(&cfg, &q), BREAK_RUNTIME_OK);

    /* Malformed submissions. */
    ASSERT_EQ(break_runtime_task_submit(NULL, inline_probe_task, NULL,
                                        TASK_PRIORITY_NORMAL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_task_submit(q, NULL, NULL, TASK_PRIORITY_NORMAL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_task_submit(q, inline_probe_task, NULL,
                                        TASK_PRIORITY_COUNT),
              BREAK_RUNTIME_INVALID);

    /* Bounded capacity: two accepted, the third rejected with OVERLOAD. */
    ASSERT_EQ(break_runtime_task_submit(q, inline_probe_task,
                                        make_value_msg(1u, 1u),
                                        TASK_PRIORITY_NORMAL),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_task_submit(q, inline_probe_task,
                                        make_value_msg(2u, 2u),
                                        TASK_PRIORITY_HIGH),
              BREAK_RUNTIME_OK);
    {
        BreakRuntimeOwnedMessage *payload = make_value_msg(3u, 3u);
        ASSERT_EQ(break_runtime_task_submit(q, inline_probe_task, payload,
                                            TASK_PRIORITY_LOW),
                  BREAK_RUNTIME_OVERLOAD);
        break_runtime_message_release(payload); /* caller keeps ownership */
    }

    /* The formal facade NEVER executes a task inline: not on accept, not on
     * overload. */
    ASSERT_EQ(atomic_load(&g_inline_probe_ran), 0u);

    /* close() stops admission. */
    break_runtime_task_queue_close(q);
    {
        BreakRuntimeOwnedMessage *payload = make_value_msg(4u, 4u);
        ASSERT_EQ(break_runtime_task_submit(q, inline_probe_task, payload,
                                            TASK_PRIORITY_NORMAL),
                  BREAK_RUNTIME_CLOSED);
        break_runtime_message_release(payload);
    }
    break_runtime_task_queue_close(q); /* idempotent */
    ASSERT_EQ(atomic_load(&g_inline_probe_ran), 0u);

    ASSERT_EQ(break_runtime_task_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.overload_rejects, 1u);
    ASSERT_EQ(stats.closed_rejects, 1u);
    ASSERT_EQ(stats.high_water, 2u);

    /* destroy releases the still-queued payloads (ASan-leak observable). */
    break_runtime_task_queue_destroy(q);
    break_runtime_task_queue_destroy(NULL);

    /* Malformed create. */
    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = BREAK_RUNTIME_TASK_QUEUE_MAX_CAPACITY + 1u;
    q = NULL;
    ASSERT_EQ(break_runtime_task_queue_create(&cfg, &q), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_task_queue_create(NULL, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_task_queue_stats(NULL, &stats),
              BREAK_RUNTIME_INVALID);
}

TEST(task_drain_executes_on_legacy_system)
{
    BreakRuntimeTaskQueue *q = NULL;
    BreakRuntimeTaskStats stats;
    TaskSystem *ts;
    u32 forwarded = 0u;
    int i;

    atomic_store(&g_task_sum, 0u);
    atomic_store(&g_task_ran, 0u);

    ts = task_system_create(2);
    ASSERT_NOT_NULL(ts);

    ASSERT_EQ(break_runtime_task_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    for (i = 1; i <= 4; i++) {
        BreakRuntimeOwnedMessage *payload = make_value_msg((u64)i, (u32)i);
        ASSERT_NOT_NULL(payload);
        ASSERT_EQ(break_runtime_task_submit(q, accumulate_task, payload,
                                            TASK_PRIORITY_NORMAL),
                  BREAK_RUNTIME_OK);
    }
    /* A NULL payload is legal; the callback receives NULL. */
    ASSERT_EQ(break_runtime_task_submit(q, accumulate_task, NULL,
                                        TASK_PRIORITY_LOW),
              BREAK_RUNTIME_OK);

    /* Nothing runs before the owner-thread drain. */
    ASSERT_EQ(atomic_load(&g_task_ran), 0u);

    ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 16u, &forwarded),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(forwarded, 5u);
    ASSERT_EQ(break_runtime_task_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.forwarded, 5u);

    task_wait(ts);
    ASSERT_EQ(atomic_load(&g_task_ran), 5u);
    ASSERT_EQ(atomic_load(&g_task_sum), 10u);

    /* Draining an empty queue forwards nothing; malformed drains rejected. */
    ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 16u, &forwarded),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(forwarded, 0u);
    ASSERT_EQ(break_runtime_task_queue_drain(NULL, ts, 16u, &forwarded),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_task_queue_drain(q, NULL, 16u, &forwarded),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 16u, NULL),
              BREAK_RUNTIME_INVALID);

    break_runtime_task_queue_destroy(q);
    task_system_destroy(ts);
}

TEST(task_drain_forward_failure_retains_queue)
{
    /* Regression (review Important 1): legacy task_submit_ex can return
     * TASK_HANDLE_INVALID WITHOUT consuming the task call. Drain must not
     * leak the node/payload or count it as forwarded: the tasks stay queued
     * (retain-and-stop) and a later drain runs them. The injection hook
     * simulates the legacy rejection deterministically. */
    BreakRuntimeTaskQueue *q = NULL;
    BreakRuntimeTaskStats stats;
    TaskSystem *ts;
    u32 forwarded = 0u;
    int i;

    atomic_store(&g_task_sum, 0u);
    atomic_store(&g_task_ran, 0u);

    ts = task_system_create(2);
    ASSERT_NOT_NULL(ts);
    ASSERT_EQ(break_runtime_task_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    for (i = 1; i <= 2; i++) {
        BreakRuntimeOwnedMessage *payload = make_value_msg((u64)i, (u32)i);
        ASSERT_NOT_NULL(payload);
        ASSERT_EQ(break_runtime_task_submit(q, accumulate_task, payload,
                                            TASK_PRIORITY_NORMAL),
                  BREAK_RUNTIME_OK);
    }

    /* Legacy forward rejected: nothing is forwarded, nothing runs, the queue
     * retains both tasks. */
    break_runtime_test_set_forward_fail_budget(1u);
    ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 16u, &forwarded),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(forwarded, 0u);
    ASSERT_EQ(atomic_load(&g_task_ran), 0u);
    ASSERT_EQ(break_runtime_task_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.forwarded, 0u);
    ASSERT_EQ(stats.forward_rejects, 1u);

    /* After the transient failure the same tasks drain and execute, still in
     * FIFO submit order. */
    break_runtime_test_set_forward_fail_budget(0u);
    ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 16u, &forwarded),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(forwarded, 2u);
    task_wait(ts);
    ASSERT_EQ(atomic_load(&g_task_ran), 2u);
    ASSERT_EQ(atomic_load(&g_task_sum), 3u);
    ASSERT_EQ(break_runtime_task_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.forwarded, 2u);
    ASSERT_EQ(stats.forward_rejects, 1u);

    break_runtime_task_queue_destroy(q);
    task_system_destroy(ts);
}

TEST(task_allocation_failure_injection)
{
    BreakRuntimeTaskQueue *q = NULL;
    BreakRuntimeOwnedMessage *payload;

    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_task_queue_create(NULL, &q), BREAK_RUNTIME_OOM);
    ASSERT_EQ(q, NULL);
    /* the queue allocates, its completion counter block does not */
    break_runtime_test_set_alloc_budget(1u);
    ASSERT_EQ(break_runtime_task_queue_create(NULL, &q), BREAK_RUNTIME_OOM);
    ASSERT_EQ(q, NULL);

    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    ASSERT_EQ(break_runtime_task_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(q);

    /* Submit OOM: the caller keeps the payload. The payload is copied before
     * the budget is armed so only the submit allocation is injected. */
    payload = make_value_msg(1u, 1u);
    ASSERT_NOT_NULL(payload);
    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_task_submit(q, inline_probe_task, payload,
                                        TASK_PRIORITY_NORMAL),
              BREAK_RUNTIME_OOM);
    break_runtime_message_release(payload);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);

    break_runtime_task_queue_destroy(q);
}

TEST(message_copy_keeps_correlation_id)
{
    u32 payload = 7u;
    BreakRuntimeMessageView view;
    BreakRuntimeMessageView owned_view;
    BreakRuntimeOwnedMessage *msg = NULL;

    memset(&view, 0, sizeof(view));
    view.kind = 5u;
    view.version = 1u;
    view.sequence = 11u;
    view.correlation_id = 0x1234567890ABCDEFull;
    view.data = &payload;
    view.size = sizeof(payload);
    ASSERT_EQ(break_runtime_message_copy(&view, &msg), BREAK_RUNTIME_OK);
    view.correlation_id = 0u;
    ASSERT_EQ(break_runtime_message_view(msg, &owned_view), BREAK_RUNTIME_OK);
    ASSERT_EQ(owned_view.correlation_id, 0x1234567890ABCDEFull);
    ASSERT_EQ(owned_view.sequence, 11u);
    break_runtime_message_release(msg);

    /* zeroed views stay uncorrelated */
    ASSERT_EQ(break_runtime_message_copy(&view, &msg), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_message_view(msg, &owned_view), BREAK_RUNTIME_OK);
    ASSERT_EQ(owned_view.correlation_id, 0u);
    break_runtime_message_release(msg);
}

#define CORRELATION_THREADS 4
#define CORRELATION_PER_THREAD 1000

typedef struct {
    u64 ids[CORRELATION_PER_THREAD];
} CorrelationCtx;

static PLATFORM_THREAD_RET correlation_main(PLATFORM_THREAD_ARG arg)
{
    CorrelationCtx *c = (CorrelationCtx *)arg;
    u32 j;
    for (j = 0; j < (u32)CORRELATION_PER_THREAD; j++) {
        c->ids[j] = break_runtime_correlation_next();
    }
    return PLATFORM_THREAD_RETURN;
}

static int compare_u64(const void *a, const void *b)
{
    u64 x = *(const u64 *)a;
    u64 y = *(const u64 *)b;
    return x < y ? -1 : (x > y ? 1 : 0);
}

TEST(correlation_next_is_unique_across_threads)
{
    static CorrelationCtx ctx[CORRELATION_THREADS];
    static u64 all[CORRELATION_THREADS * CORRELATION_PER_THREAD];
    PlatformThread threads[CORRELATION_THREADS];
    u64 first;
    u64 second;
    int i;
    u32 j;
    usize n = 0u;

    first = break_runtime_correlation_next();
    second = break_runtime_correlation_next();
    ASSERT_TRUE(first != 0u);
    ASSERT_TRUE(second > first);
    for (i = 0; i < CORRELATION_THREADS; i++) {
        ASSERT_TRUE(platform_thread_create(&threads[i], correlation_main,
                                           &ctx[i]));
    }
    for (i = 0; i < CORRELATION_THREADS; i++) {
        platform_thread_join(threads[i]);
    }
    for (i = 0; i < CORRELATION_THREADS; i++) {
        for (j = 0; j < (u32)CORRELATION_PER_THREAD; j++) {
            ASSERT_TRUE(ctx[i].ids[j] > second);
            if (j > 0u) {
                ASSERT_TRUE(ctx[i].ids[j] > ctx[i].ids[j - 1u]);
            }
            all[n++] = ctx[i].ids[j];
        }
    }
    qsort(all, n, sizeof(all[0]), compare_u64);
    for (j = 1u; j < (u32)n; j++) {
        ASSERT_TRUE(all[j] != all[j - 1u]);
    }
}

/* Completions on the bus: a finished task publishes (kind, version 1,
 * payload = its 8-byte sequence) with the payload's correlation id, so the
 * owner learns of finished work from its own queue. */
static BreakRuntimeOwnedMessage *make_correlated_msg(u64 sequence, u64 cid)
{
    BreakRuntimeMessageView view;
    BreakRuntimeOwnedMessage *msg = NULL;
    u32 value = (u32)sequence;
    memset(&view, 0, sizeof(view));
    view.kind = 7u;
    view.version = 1u;
    view.sequence = sequence;
    view.correlation_id = cid;
    view.data = &value;
    view.size = sizeof(value);
    if (break_runtime_message_copy(&view, &msg) != BREAK_RUNTIME_OK) return NULL;
    return msg;
}

TEST(task_completions_are_published_on_the_bus)
{
    BreakRuntimeBus *bus = NULL;
    BreakRuntimeQueue *done = NULL;
    BreakRuntimeTaskQueue *q = NULL;
    BreakRuntimeQueueConfig qc = {32u, 0u};
    BreakRuntimeTaskStats stats;
    const u16 kind = 0x0901u;
    BreakRuntimeBusKind completion = {0x0901u, 1u, 8u, "task.done", false, 0u};
    u32 forwarded = 0u, sub = 0u;
    u64 seen_cid[8] = {0}, seen_seq[8] = {0};
    u32 seen = 0u;
    TaskSystem *ts;

    atomic_store(&g_task_sum, 0u);
    atomic_store(&g_task_ran, 0u);
    ts = task_system_create(2);
    ASSERT_NOT_NULL(ts);
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_queue_create(&qc, &done), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "owner", done, &kind, 1u, &sub), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_task_queue_create(NULL, &q), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_task_queue_publish_completions(NULL, bus, kind), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_task_queue_publish_completions(q, bus, 0x0999u), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_runtime_task_queue_publish_completions(q, bus, kind), BREAK_RUNTIME_OK);

    for (u32 i = 1; i <= 4; i++) {
        BreakRuntimeOwnedMessage *payload = make_correlated_msg(i, 100u + i);
        ASSERT_NOT_NULL(payload);
        ASSERT_EQ(break_runtime_task_submit(q, accumulate_task, payload, TASK_PRIORITY_NORMAL),
                  BREAK_RUNTIME_OK);
    }
    /* a task without a payload completes with correlation id 0, sequence 0 */
    ASSERT_EQ(break_runtime_task_submit(q, accumulate_task, NULL, TASK_PRIORITY_LOW),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 16u, &forwarded), BREAK_RUNTIME_OK);
    ASSERT_EQ(forwarded, 5u);
    task_wait(ts);
    ASSERT_EQ(atomic_load(&g_task_ran), 5u);

    for (;;) {
        BreakRuntimeOwnedMessage *m = NULL;
        BreakRuntimeMessageView v;
        ASSERT_EQ(break_runtime_queue_poll(done, &m), BREAK_RUNTIME_OK);
        if (m == NULL) break;
        ASSERT_EQ(break_runtime_message_view(m, &v), BREAK_RUNTIME_OK);
        ASSERT_EQ(v.kind, kind);
        ASSERT_EQ(v.size, 8u);
        ASSERT_TRUE(seen < 8u);
        seen_cid[seen] = v.correlation_id;
        memcpy(&seen_seq[seen], v.data, 8u);
        seen++;
        break_runtime_message_release(m);
    }
    ASSERT_EQ(seen, 5u);
    {
        u64 cid_sum = 0u, seq_sum = 0u;
        u32 zero = 0u;
        for (u32 i = 0; i < seen; i++) {
            cid_sum += seen_cid[i];
            seq_sum += seen_seq[i];
            if (seen_cid[i] == 0u) zero++;
            if (seen_cid[i] != 0u) ASSERT_EQ(seen_cid[i], 100u + seen_seq[i]);
        }
        ASSERT_EQ(zero, 1u);
        ASSERT_EQ(cid_sum, 101u + 102u + 103u + 104u);
        ASSERT_EQ(seq_sum, 1u + 2u + 3u + 4u);
    }
    ASSERT_EQ(break_runtime_task_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.completions_published, 5u);
    ASSERT_EQ(stats.completions_dropped, 0u);

    /* detached: tasks still run, nothing is published */
    ASSERT_EQ(break_runtime_task_queue_publish_completions(q, NULL, kind), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_task_submit(q, accumulate_task, make_correlated_msg(9u, 9u),
                                        TASK_PRIORITY_NORMAL), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 16u, &forwarded), BREAK_RUNTIME_OK);
    task_wait(ts);
    {
        BreakRuntimeOwnedMessage *m = NULL;
        ASSERT_EQ(break_runtime_queue_poll(done, &m), BREAK_RUNTIME_OK);
        ASSERT_TRUE(m == NULL);
    }
    ASSERT_EQ(atomic_load(&g_task_ran), 6u);

    break_runtime_task_queue_destroy(q);
    task_system_destroy(ts);
    ASSERT_EQ(break_runtime_bus_unsubscribe(bus, sub), BREAK_RUNTIME_OK);
    break_runtime_queue_destroy(done);
    break_runtime_bus_destroy(bus);
}

/* The owner may destroy the task queue as soon as it has polled a task's
 * completion notice, while the worker that published it is still returning
 * from the trampoline. The trampoline once bumped counters inside the queue
 * after publishing, a use-after-free that AddressSanitizer reports here. */
TEST(task_queue_can_be_destroyed_once_the_notice_arrives)
{
    BreakRuntimeBus *bus = NULL;
    BreakRuntimeQueue *done = NULL;
    BreakRuntimeQueueConfig qc = {4u, 0u};
    const u16 kind = 0x0903u;
    BreakRuntimeBusKind completion = {0x0903u, 1u, 8u, "task.done3", false, 0u};
    u32 sub = 0u;
    TaskSystem *ts = task_system_create(2);
    ASSERT_NOT_NULL(ts);
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_queue_create(&qc, &done), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "owner", done, &kind, 1u, &sub), BREAK_RUNTIME_OK);
    for (u32 round = 0; round < 200u; round++) {
        BreakRuntimeTaskQueue *q = NULL;
        BreakRuntimeOwnedMessage *m = NULL;
        u32 forwarded = 0u;
        ASSERT_EQ(break_runtime_task_queue_create(NULL, &q), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_task_queue_publish_completions(q, bus, kind), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_task_submit(q, accumulate_task, make_correlated_msg(1u, 1u),
                                            TASK_PRIORITY_NORMAL), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 1u, &forwarded), BREAK_RUNTIME_OK);
        ASSERT_EQ(forwarded, 1u);
        while (m == NULL) {
            ASSERT_EQ(break_runtime_queue_poll(done, &m), BREAK_RUNTIME_OK);
            if (m == NULL) platform_thread_yield();
        }
        break_runtime_message_release(m);
        break_runtime_task_queue_destroy(q);
    }
    task_wait(ts);
    task_system_destroy(ts);
    ASSERT_EQ(break_runtime_bus_unsubscribe(bus, sub), BREAK_RUNTIME_OK);
    break_runtime_queue_destroy(done);
    break_runtime_bus_destroy(bus);
}

/* A full owner queue drops the completion; the task still ran and the
 * worker never waited. */
TEST(task_completions_never_block_a_worker)
{
    BreakRuntimeBus *bus = NULL;
    BreakRuntimeQueue *done = NULL;
    BreakRuntimeTaskQueue *q = NULL;
    BreakRuntimeQueueConfig qc = {2u, 0u};
    BreakRuntimeTaskStats stats;
    const u16 kind = 0x0902u;
    BreakRuntimeBusKind completion = {0x0902u, 1u, 8u, "task.done2", false, 0u};
    u32 forwarded = 0u, sub = 0u;
    TaskSystem *ts;

    atomic_store(&g_task_ran, 0u);
    ts = task_system_create(2);
    ASSERT_NOT_NULL(ts);
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_queue_create(&qc, &done), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "owner", done, &kind, 1u, &sub), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_task_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_task_queue_publish_completions(q, bus, kind), BREAK_RUNTIME_OK);
    for (u32 i = 1; i <= 10; i++)
        ASSERT_EQ(break_runtime_task_submit(q, accumulate_task, make_correlated_msg(i, i),
                                            TASK_PRIORITY_NORMAL), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_task_queue_drain(q, ts, 16u, &forwarded), BREAK_RUNTIME_OK);
    task_wait(ts);
    ASSERT_EQ(atomic_load(&g_task_ran), 10u);
    ASSERT_EQ(break_runtime_task_queue_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.completions_published, 2u);
    ASSERT_EQ(stats.completions_dropped, 8u);
    break_runtime_task_queue_destroy(q);
    task_system_destroy(ts);
    ASSERT_EQ(break_runtime_bus_unsubscribe(bus, sub), BREAK_RUNTIME_OK);
    break_runtime_queue_destroy(done);
    break_runtime_bus_destroy(bus);
}

static u64 facade_metric_of(BreakRuntimeMetrics *m, const char *name)
{
    BreakRuntimeMetricSample out[32];
    u32 n = 0u, i;
    if (break_runtime_metrics_snapshot(m, out, 32u, &n) != BREAK_RUNTIME_OK) return UINT64_MAX;
    for (i = 0u; i < n; i++)
        if (strcmp(out[i].name, name) == 0) return out[i].value;
    return UINT64_MAX;
}

TEST(queue_export_metrics_mirrors_counters_as_idempotent_gauges)
{
    BreakRuntimeQueue *q = NULL;
    BreakRuntimeMetrics *m = NULL;
    BreakRuntimeMetricSample out[32];
    BreakRuntimeOwnedMessage *msg = NULL;
    u64 gen;
    u32 n = 0u;
    int i;

    ASSERT_EQ(break_runtime_queue_create(NULL, &q), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_create(NULL, &m), BREAK_RUNTIME_OK);
    gen = break_runtime_queue_generation(q);
    for (i = 1; i <= 3; i++) {
        msg = make_value_msg((u64)i, (u32)i);
        ASSERT_NOT_NULL(msg);
        ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen), BREAK_RUNTIME_OK);
    }
    msg = NULL;
    ASSERT_EQ(break_runtime_queue_poll(q, &msg), BREAK_RUNTIME_OK);
    break_runtime_message_release(msg);
    /* a stale enqueue so stale_rejects is nonzero; caller keeps the message */
    msg = make_value_msg(99u, 99u);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(break_runtime_queue_enqueue(q, msg, gen + 1u), BREAK_RUNTIME_STALE);
    break_runtime_message_release(msg);

    ASSERT_EQ(break_runtime_queue_export_metrics(NULL, m, "q.input"), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_export_metrics(q, NULL, "q.input"), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_export_metrics(q, m, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_export_metrics(q, m, ""), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_queue_export_metrics(q, m, "q.input"), BREAK_RUNTIME_OK);
    ASSERT_EQ(facade_metric_of(m, "q.input.enqueued"), 3u);
    ASSERT_EQ(facade_metric_of(m, "q.input.dequeued"), 1u);
    ASSERT_EQ(facade_metric_of(m, "q.input.stale_rejects"), 1u);
    ASSERT_EQ(facade_metric_of(m, "q.input.overload_rejects"), 0u);
    ASSERT_EQ(facade_metric_of(m, "q.input.closed_rejects"), 0u);
    ASSERT_EQ(facade_metric_of(m, "q.input.high_water"), 3u);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 32u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 6u);

    /* idempotent re-export: gauges, no slot growth and no value growth */
    ASSERT_EQ(break_runtime_queue_export_metrics(q, m, "q.input"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 32u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 6u);
    ASSERT_EQ(facade_metric_of(m, "q.input.enqueued"), 3u);
    ASSERT_EQ(facade_metric_of(m, "q.input.high_water"), 3u);

    /* a distinct prefix tracks a second queue's gauges alongside */
    ASSERT_EQ(break_runtime_queue_export_metrics(q, m, "q.output"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 32u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 12u);

    /* an over-long prefix overflows the metric name; the set INVALID surfaces */
    {
        char longp[48];
        memset(longp, 'p', sizeof longp);
        longp[sizeof longp - 1u] = '\0';
        ASSERT_EQ(break_runtime_queue_export_metrics(q, m, longp), BREAK_RUNTIME_INVALID);
    }

    break_runtime_metrics_destroy(m);
    break_runtime_queue_destroy(q);
}

TEST_MAIN_BEGIN()
    RUN_TEST(message_copy_produces_independent_owned_bytes);
    RUN_TEST(message_copy_validates_null_and_size);
    RUN_TEST(message_double_release_aborts_in_test_builds);
    RUN_TEST(message_allocation_failure_injection);
    RUN_TEST(queue_fifo_order_and_stats);
    RUN_TEST(queue_reserved_control_capacity);
    RUN_TEST(queue_stale_generation_rejected);
    RUN_TEST(queue_control_fill_then_data_overload_keeps_ring_intact);
    RUN_TEST(queue_mixed_control_data_wraparound_fifo);
    RUN_TEST(queue_allocation_failure_injection);
    RUN_TEST(queue_close_wakes_waiters_and_stops_admission);
    RUN_TEST(queue_mpsc_producers_single_consumer);
    RUN_TEST(task_submit_overload_never_inlines);
    RUN_TEST(task_drain_executes_on_legacy_system);
    RUN_TEST(task_drain_forward_failure_retains_queue);
    RUN_TEST(task_allocation_failure_injection);
    RUN_TEST(task_completions_are_published_on_the_bus);
    RUN_TEST(task_queue_can_be_destroyed_once_the_notice_arrives);
    RUN_TEST(task_completions_never_block_a_worker);
    RUN_TEST(message_copy_keeps_correlation_id);
    RUN_TEST(correlation_next_is_unique_across_threads);
    RUN_TEST(queue_export_metrics_mirrors_counters_as_idempotent_gauges);
TEST_MAIN_END()
