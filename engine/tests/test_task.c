/* ==========================================================================
 *  test_task.c — Unit tests for the task system (work-stealing thread pool).
 *
 *  NOTE: TaskSystem uses a global pointer (g_task_system), so we create
 *  ONE system at the start and reuse it for all tests.
 * ========================================================================== */

#include "test_framework.h"
#include <task/task.h>
#include <stdatomic.h>

static TaskSystem *g_ts;

/* ---- Shared test helpers ---- */

static _Atomic i32 g_counter;

static void increment_fn(void *ctx)
{
    (void)ctx;
    atomic_fetch_add(&g_counter, 1);
}

static void add_value_fn(void *ctx)
{
    i32 val = *(i32 *)ctx;
    atomic_fetch_add(&g_counter, val);
}

/* ----------------------------------------------------------------------- */

TEST(single_task)
{
    atomic_store(&g_counter, 0);
    task_submit(g_ts, increment_fn, NULL);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_counter), 1);
}

TEST(many_tasks)
{
    atomic_store(&g_counter, 0);
    const i32 N = 100;
    for (i32 i = 0; i < N; i++) {
        task_submit(g_ts, increment_fn, NULL);
    }
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_counter), N);
}

TEST(tasks_with_context)
{
    atomic_store(&g_counter, 0);
    i32 values[10];
    for (i32 i = 0; i < 10; i++) values[i] = i + 1;
    void *ctxs[10];
    for (i32 i = 0; i < 10; i++) ctxs[i] = &values[i];
    task_submit_n(g_ts, add_value_fn, ctxs, 10);
    task_wait(g_ts);
    /* sum of 1..10 = 55 */
    ASSERT_EQ(atomic_load(&g_counter), 55);
}

TEST(handle_based_submit)
{
    atomic_store(&g_counter, 0);
    TaskHandle h = task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_HIGH);
    ASSERT_NEQ(h, TASK_HANDLE_INVALID);
    task_wait_handle(g_ts, h);
    ASSERT_EQ(atomic_load(&g_counter), 1);
}

TEST(priority_levels)
{
    atomic_store(&g_counter, 0);
    task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_LOW);
    task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_NORMAL);
    task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_HIGH);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_counter), 3);
}

TEST(worker_count_query)
{
    ASSERT_EQ(task_worker_count(g_ts), 2u);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    g_ts = task_system_create(2);
    if (!g_ts) {
        printf("FATAL: task_system_create failed\n");
        return 1;
    }

    RUN_TEST(single_task);
    RUN_TEST(many_tasks);
    RUN_TEST(tasks_with_context);
    RUN_TEST(handle_based_submit);
    RUN_TEST(priority_levels);
    RUN_TEST(worker_count_query);

    task_system_destroy(g_ts);

    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
