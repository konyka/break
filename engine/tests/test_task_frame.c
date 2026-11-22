/* Cross-frame continuations: work deferred to a later frame runs when the
 * owner reaches that frame, in submission order, on the owner thread or on
 * the task system, and honours cancellation tokens. */
#include "test_framework.h"
#include <task/task_frame.h>
#include <stdatomic.h>
#include <string.h>

typedef struct {
    u32 order[32];
    u32 count;
} Trace;

typedef struct {
    Trace *trace;
    u32 id;
} Step;

static void record(void *ctx) {
    Step *s = (Step *)ctx;
    if (s->trace->count < 32u) s->trace->order[s->trace->count] = s->id;
    s->trace->count++;
}

static _Atomic u32 g_ran;
static void count_ran(void *ctx) {
    (void)ctx;
    atomic_fetch_add(&g_ran, 1u);
}

TEST(continuations_run_at_their_frame_in_submission_order) {
    TaskFrameQueue q;
    ASSERT_TRUE(task_frame_queue_init(&q, 16u));
    Trace trace;
    memset(&trace, 0, sizeof(trace));
    Step steps[5] = {{&trace, 1}, {&trace, 2}, {&trace, 3}, {&trace, 4}, {&trace, 5}};
    ASSERT_EQ(task_frame_defer(&q, 12u, record, &steps[0], NULL), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_defer(&q, 11u, record, &steps[1], NULL), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_defer(&q, 12u, record, &steps[2], NULL), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_defer(&q, 11u, record, &steps[3], NULL), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_defer(&q, 20u, record, &steps[4], NULL), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_pending(&q), 5u);
    ASSERT_EQ(task_frame_run(&q, 10u, NULL), 0u);
    ASSERT_EQ(trace.count, 0u);
    ASSERT_EQ(task_frame_run(&q, 11u, NULL), 2u);
    ASSERT_EQ(trace.count, 2u);
    ASSERT_EQ(trace.order[0], 2u);
    ASSERT_EQ(trace.order[1], 4u);
    /* a skipped frame still runs everything that became due, oldest frame
     * first, then submission order: 14 was submitted after 12 but is
     * younger, so it runs last */
    Step late = {&trace, 6};
    ASSERT_EQ(task_frame_defer(&q, 14u, record, &late, NULL), TASK_FRAME_OK);
    Step early = {&trace, 7};
    ASSERT_EQ(task_frame_defer(&q, 13u, record, &early, NULL), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_run(&q, 15u, NULL), 4u);
    ASSERT_EQ(trace.order[2], 1u);
    ASSERT_EQ(trace.order[3], 3u);
    ASSERT_EQ(trace.order[4], 7u);
    ASSERT_EQ(trace.order[5], 6u);
    ASSERT_EQ(task_frame_pending(&q), 1u);
    ASSERT_EQ(task_frame_run(&q, 20u, NULL), 1u);
    ASSERT_EQ(trace.order[6], 5u);
    ASSERT_EQ(task_frame_pending(&q), 0u);
    task_frame_queue_destroy(&q);
}

/* A continuation may defer more work; work deferred for the frame being run
 * waits for the next run call, so one frame never loops on itself. */
static TaskFrameQueue *g_queue;
static Trace g_trace;
static Step g_later = {&g_trace, 9};
static void defer_again(void *ctx) {
    record(ctx);
    (void)task_frame_defer(g_queue, 3u, record, &g_later, NULL);
}

TEST(continuation_deferred_from_a_continuation_waits_for_the_next_run) {
    TaskFrameQueue q;
    ASSERT_TRUE(task_frame_queue_init(&q, 4u));
    g_queue = &q;
    memset(&g_trace, 0, sizeof(g_trace));
    Step first = {&g_trace, 1};
    ASSERT_EQ(task_frame_defer(&q, 3u, defer_again, &first, NULL), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_run(&q, 3u, NULL), 1u);
    ASSERT_EQ(g_trace.count, 1u);
    ASSERT_EQ(task_frame_pending(&q), 1u);
    ASSERT_EQ(task_frame_run(&q, 3u, NULL), 1u);
    ASSERT_EQ(g_trace.order[1], 9u);
    task_frame_queue_destroy(&q);
}

/* A full queue refuses new work without dropping queued work; a cancelled
 * token skips the continuation (it is still removed and counted). */
TEST(capacity_and_cancellation) {
    TaskFrameQueue q;
    ASSERT_TRUE(task_frame_queue_init(&q, 2u));
    Trace trace;
    memset(&trace, 0, sizeof(trace));
    Step a = {&trace, 1}, b = {&trace, 2}, c = {&trace, 3};
    TaskCancelToken token;
    task_cancel_token_init(&token);
    ASSERT_EQ(task_frame_defer(&q, 1u, record, &a, &token), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_defer(&q, 1u, record, &b, NULL), TASK_FRAME_OK);
    ASSERT_EQ(task_frame_defer(&q, 1u, record, &c, NULL), TASK_FRAME_FULL);
    ASSERT_EQ(task_frame_pending(&q), 2u);
    task_cancel(&token);
    ASSERT_EQ(task_frame_run(&q, 1u, NULL), 2u);
    ASSERT_EQ(trace.count, 1u);
    ASSERT_EQ(trace.order[0], 2u);
    ASSERT_EQ(task_frame_cancelled(&q), 1u);
    ASSERT_EQ(task_frame_defer(NULL, 1u, record, &a, NULL), TASK_FRAME_INVALID);
    ASSERT_EQ(task_frame_defer(&q, 1u, NULL, &a, NULL), TASK_FRAME_INVALID);
    task_frame_queue_destroy(&q);
    ASSERT_FALSE(task_frame_queue_init(&q, 0u));
    ASSERT_EQ(task_frame_defer(&q, 1u, record, &a, NULL), TASK_FRAME_INVALID);
    ASSERT_EQ(task_frame_run(&q, 1u, NULL), 0u);
    task_frame_queue_destroy(&q);
}

/* With a task system the due continuations run on workers and task_frame_run
 * returns only when all of them have finished. */
TEST(due_continuations_run_on_the_task_system) {
    TaskSystem *ts = task_system_create(2);
    ASSERT_NOT_NULL(ts);
    TaskFrameQueue q;
    bool ok = task_frame_queue_init(&q, 64u);
    atomic_store(&g_ran, 0u);
    u32 deferred = 0u;
    for (u32 i = 0; ok && i < 40u; i++)
        if (task_frame_defer(&q, 5u + (i % 2u), count_ran, NULL, NULL) == TASK_FRAME_OK) deferred++;
    u32 ran5 = ok ? task_frame_run(&q, 5u, ts) : 0u;
    u32 seen5 = atomic_load(&g_ran);
    u32 ran6 = ok ? task_frame_run(&q, 6u, ts) : 0u;
    u32 seen6 = atomic_load(&g_ran);
    if (ok) task_frame_queue_destroy(&q);
    task_system_destroy(ts);
    ASSERT_TRUE(ok);
    ASSERT_EQ(deferred, 40u);
    ASSERT_EQ(ran5, 20u);
    ASSERT_EQ(seen5, 20u);
    ASSERT_EQ(ran6, 20u);
    ASSERT_EQ(seen6, 40u);
}

/* Continuations that run on workers may defer more work at the same time.
 * defer once did an unlocked count++, so two workers could take the last
 * free slot together and write one entry past the end of the buffer. */
static TaskFrameQueue *g_shared;
static _Atomic u32 g_redeferred;
static _Atomic u32 g_refused;
static void defer_from_worker(void *ctx) {
    (void)ctx;
    TaskFrameError e = task_frame_defer(g_shared, 6u, count_ran, NULL, NULL);
    if (e == TASK_FRAME_OK) atomic_fetch_add(&g_redeferred, 1u);
    else if (e == TASK_FRAME_FULL) atomic_fetch_add(&g_refused, 1u);
}

TEST(continuations_on_workers_may_defer_concurrently) {
    TaskSystem *ts = task_system_create(4);
    ASSERT_NOT_NULL(ts);
    for (u32 round = 0; round < 200u; round++) {
        TaskFrameQueue q;
        ASSERT_TRUE(task_frame_queue_init(&q, 40u));
        g_shared = &q;
        atomic_store(&g_redeferred, 0u);
        atomic_store(&g_refused, 0u);
        atomic_store(&g_ran, 0u);
        for (u32 i = 0; i < 40u; i++)
            ASSERT_EQ(task_frame_defer(&q, 5u, defer_from_worker, NULL, NULL), TASK_FRAME_OK);
        ASSERT_EQ(task_frame_run(&q, 5u, ts), 40u);
        ASSERT_EQ(atomic_load(&g_redeferred) + atomic_load(&g_refused), 40u);
        ASSERT_EQ(atomic_load(&g_redeferred), 40u);
        ASSERT_EQ(task_frame_pending(&q), 40u);
        ASSERT_EQ(task_frame_run(&q, 6u, ts), 40u);
        ASSERT_EQ(atomic_load(&g_ran), 40u);
        ASSERT_EQ(task_frame_pending(&q), 0u);
        task_frame_queue_destroy(&q);
    }
    task_system_destroy(ts);
}

TEST_MAIN_BEGIN()
    RUN_TEST(continuations_run_at_their_frame_in_submission_order);
    RUN_TEST(continuation_deferred_from_a_continuation_waits_for_the_next_run);
    RUN_TEST(capacity_and_cancellation);
    RUN_TEST(due_continuations_run_on_the_task_system);
    RUN_TEST(continuations_on_workers_may_defer_concurrently);
TEST_MAIN_END()
