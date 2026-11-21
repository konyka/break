/* Work-stealing priority policy: an idle worker steals the highest-priority
 * task available on any other worker before a lower-priority one, and a
 * worker with local low-priority work still picks up high-priority work
 * submitted from outside first. Each test builds the deque contents
 * deterministically by holding workers inside blocker tasks. */
#include "test_framework.h"
#include <task/task.h>
#include <stdatomic.h>
#include <string.h>

typedef struct {
    _Atomic u32 next;
    _Atomic u32 order[64]; /* priority + 1; 0 until written */
} RunOrder;

static RunOrder g_order;

static void record_low(void *ctx) {
    (void)ctx;
    u32 i = atomic_fetch_add(&g_order.next, 1u);
    if (i < 64u) atomic_store(&g_order.order[i], (u32)TASK_PRIORITY_LOW + 1u);
}

static void record_high(void *ctx) {
    (void)ctx;
    u32 i = atomic_fetch_add(&g_order.next, 1u);
    if (i < 64u) atomic_store(&g_order.order[i], (u32)TASK_PRIORITY_HIGH + 1u);
}

static void spin_until(_Atomic u32 *flag, u32 value) {
    for (u64 spin = 0; spin < 2000000000ull && atomic_load(flag) < value; spin++)
        platform_thread_yield();
}

/* The priority of the first task that ran, once its slot is written. */
static u32 first_priority(void) {
    spin_until(&g_order.order[0], 1u);
    return atomic_load(&g_order.order[0]) - 1u;
}

/* ---- steal order across victims ---- */

static TaskSystem *g_ts;
static _Atomic u32 g_arrived;
static _Atomic u32 g_pushed;
static _Atomic u32 g_release;
static _Atomic i32 g_ids[3];

static void steal_blocker(void *ctx) {
    (void)ctx;
    i32 me = task_worker_id(g_ts);
    u32 slot = atomic_fetch_add(&g_arrived, 1u);
    if (slot < 3u) atomic_store(&g_ids[slot], me);
    spin_until(&g_arrived, 3u);
    /* The thief is the worker that arrived first; the worker the old
     * victim-major scan visits first holds the low-priority work, the
     * other one holds the high-priority task. */
    i32 thief = atomic_load(&g_ids[0]);
    i32 workers = (i32)task_worker_count(g_ts);
    i32 low_holder = (thief + 1) % workers;
    i32 high_holder = (thief + 2) % workers;
    if (me == low_holder) {
        for (u32 i = 0; i < 8u; i++) (void)task_submit_ex(g_ts, record_low, NULL, TASK_PRIORITY_LOW);
        atomic_fetch_add(&g_pushed, 1u);
        spin_until(&g_release, 1u);
    } else if (me == high_holder) {
        (void)task_submit_ex(g_ts, record_high, NULL, TASK_PRIORITY_HIGH);
        atomic_fetch_add(&g_pushed, 1u);
        spin_until(&g_release, 1u);
    } else {
        spin_until(&g_pushed, 2u);
    }
}

TEST(thief_takes_the_highest_priority_task_from_any_victim) {
    g_ts = task_system_create(3);
    ASSERT_NOT_NULL(g_ts);
    memset(&g_order, 0, sizeof g_order);
    atomic_store(&g_arrived, 0u);
    atomic_store(&g_pushed, 0u);
    atomic_store(&g_release, 0u);
    for (u32 i = 0; i < 3u; i++) (void)task_submit_ex(g_ts, steal_blocker, NULL, TASK_PRIORITY_NORMAL);
    /* only the thief is free: wait until it has run the first stolen task */
    u32 first = first_priority();
    atomic_store(&g_release, 1u);
    spin_until(&g_order.next, 9u);
    task_wait(g_ts);
    u32 ran = atomic_load(&g_order.next);
    task_system_destroy(g_ts);
    g_ts = NULL;
    ASSERT_EQ(ran, 9u);
    ASSERT_EQ(first, (u32)TASK_PRIORITY_HIGH);
}

/* ---- external high-priority work versus local low-priority work ---- */

static _Atomic u32 g_local_ready;
static _Atomic u32 g_external_sent;

static void local_blocker(void *ctx) {
    (void)ctx;
    for (u32 i = 0; i < 8u; i++) (void)task_submit_ex(g_ts, record_low, NULL, TASK_PRIORITY_LOW);
    atomic_store(&g_local_ready, 1u);
    spin_until(&g_external_sent, 1u);
}

TEST(external_high_priority_runs_before_local_low_priority) {
    g_ts = task_system_create(1);
    ASSERT_NOT_NULL(g_ts);
    memset(&g_order, 0, sizeof g_order);
    atomic_store(&g_local_ready, 0u);
    atomic_store(&g_external_sent, 0u);
    (void)task_submit_ex(g_ts, local_blocker, NULL, TASK_PRIORITY_NORMAL);
    spin_until(&g_local_ready, 1u);
    (void)task_submit_ex(g_ts, record_high, NULL, TASK_PRIORITY_HIGH);
    atomic_store(&g_external_sent, 1u);
    /* do not task_wait yet: it would run the external task on this thread */
    spin_until(&g_order.next, 9u);
    task_wait(g_ts);
    u32 ran = atomic_load(&g_order.next);
    u32 first = first_priority();
    task_system_destroy(g_ts);
    g_ts = NULL;
    ASSERT_EQ(ran, 9u);
    ASSERT_EQ(first, (u32)TASK_PRIORITY_HIGH);
}

TEST_MAIN_BEGIN()
    RUN_TEST(thief_takes_the_highest_priority_task_from_any_victim);
    RUN_TEST(external_high_priority_runs_before_local_low_priority);
TEST_MAIN_END()
