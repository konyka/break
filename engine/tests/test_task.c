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

static void set_counter_fn(void *ctx)
{
    i32 val = *(i32 *)ctx;
    atomic_store(&g_counter, val);
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

TEST(submit_dep_waits_for_parent)
{
    i32 final_value = 100;
    atomic_store(&g_counter, 0);
    TaskHandle parent = task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_NORMAL);
    TaskHandle deps[] = { parent };
    TaskHandle child = task_submit_dep(g_ts, set_counter_fn, &final_value, deps, 1);
    ASSERT_NEQ(child, TASK_HANDLE_INVALID);
    task_wait_handle(g_ts, child);
    ASSERT_EQ(atomic_load(&g_counter), 100);
}

TEST(submit_dep_runs_when_dep_already_done)
{
    i32 final_value = 200;
    atomic_store(&g_counter, 0);
    TaskHandle parent = task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_NORMAL);
    task_wait_handle(g_ts, parent);
    ASSERT_EQ(atomic_load(&g_counter), 1);
    TaskHandle deps[] = { parent };
    TaskHandle child = task_submit_dep(g_ts, set_counter_fn, &final_value, deps, 1);
    ASSERT_NEQ(child, TASK_HANDLE_INVALID);
    task_wait_handle(g_ts, child);
    ASSERT_EQ(atomic_load(&g_counter), 200);
}

TEST(submit_dep_waits_for_two_parents)
{
    i32 final_value = 300;
    atomic_store(&g_counter, 0);
    TaskHandle a = task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_NORMAL);
    TaskHandle b = task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_NORMAL);
    TaskHandle deps[] = { a, b };
    TaskHandle child = task_submit_dep(g_ts, set_counter_fn, &final_value, deps, 2);
    ASSERT_NEQ(child, TASK_HANDLE_INVALID);
    task_wait_handle(g_ts, child);
    ASSERT_EQ(atomic_load(&g_counter), 300);
}

TEST(submit_dep_null_deps_rejected)
{
    /* R420: deps == NULL with dep_count > 0 dereferenced NULL — the
     * submission must fail with TASK_HANDLE_INVALID, not segfault. */
    atomic_store(&g_counter, 0);
    TaskHandle h = task_submit_dep(g_ts, increment_fn, NULL, NULL, 1);
    ASSERT_EQ(h, TASK_HANDLE_INVALID);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_counter), 0);  /* rejected task must not run */
}

TEST(submit_n_null_ctxs_ignored)
{
    /* R420: ctxs == NULL with count > 0 dereferenced NULL — must be a no-op. */
    atomic_store(&g_counter, 0);
    task_submit_n(g_ts, increment_fn, NULL, 3);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_counter), 0);
}

TEST(submit_null_fn_rejected)
{
    /* R424: a NULL fn would crash a worker in execute_task — every submit
     * path must reject it. */
    atomic_store(&g_counter, 0);
    void *ctxs[1] = { NULL };

    task_submit(g_ts, NULL, NULL);                          /* void path */
    task_submit_n(g_ts, NULL, ctxs, 1);                     /* batch path */

    TaskHandle h = task_submit_ex(g_ts, NULL, NULL, TASK_PRIORITY_NORMAL);
    ASSERT_EQ(h, TASK_HANDLE_INVALID);                      /* handle path */

    TaskHandle hd = task_submit_dep(g_ts, NULL, NULL, NULL, 0);
    ASSERT_EQ(hd, TASK_HANDLE_INVALID);                     /* dep path */

    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_counter), 0);  /* nothing may have run */
}

/* ----------------------------------------------------------------------- */
/* R414 regression tests.
 * NOTE: these must run LAST — pushing the shared g_ts past the 4096-entry
 * static task pool (heap fallback) is irreversible for its lifetime. */

TEST(out_of_range_priority_is_clamped)
{
    atomic_store(&g_counter, 0);
    /* R414: garbage priority must be clamped, not index queues[] OOB. */
    TaskHandle h = task_submit_ex(g_ts, increment_fn, NULL, (TaskPriority)99);
    ASSERT_NEQ(h, TASK_HANDLE_INVALID);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_counter), 1);
}

TEST(beyond_pool_capacity_all_execute)
{
    atomic_store(&g_counter, 0);
    /* Push total submissions past the 4096-entry static pool so the tail
     * takes the R414 heap-fallback path. All must still execute exactly
     * once (ref_count 1 freed via task_release — no crash, no hang). */
    const i32 N = 4096 + 512;
    TaskHandle last = TASK_HANDLE_INVALID;
    for (i32 i = 0; i < N; i++) {
        last = task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_NORMAL);
        ASSERT_NEQ(last, TASK_HANDLE_INVALID);
    }
    /* `last` is a heap-fallback handle (idx 0xFFFFFFFF): task_wait_handle
     * explicitly rejects it and must return immediately, not hang. */
    task_wait_handle(g_ts, last);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_counter), N);
}

TEST(submit_dep_on_heap_handle_fails)
{
    /* Pool is exhausted by now, so this parent is a heap-fallback task. */
    TaskHandle parent = task_submit_ex(g_ts, increment_fn, NULL, TASK_PRIORITY_NORMAL);
    ASSERT_NEQ(parent, TASK_HANDLE_INVALID);
    TaskHandle deps[] = { parent };
    /* R414: depending on an unresolvable heap handle must fail loudly, not
     * silently drop the dependency. */
    TaskHandle child = task_submit_dep(g_ts, increment_fn, NULL, deps, 1);
    ASSERT_EQ(child, TASK_HANDLE_INVALID);
    task_wait(g_ts);
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
    RUN_TEST(submit_dep_waits_for_parent);
    RUN_TEST(submit_dep_runs_when_dep_already_done);
    RUN_TEST(submit_dep_waits_for_two_parents);
    RUN_TEST(submit_dep_null_deps_rejected);
    RUN_TEST(submit_n_null_ctxs_ignored);
    RUN_TEST(submit_null_fn_rejected);
    /* R414: these exhaust the shared task pool — keep them last. */
    RUN_TEST(out_of_range_priority_is_clamped);
    RUN_TEST(beyond_pool_capacity_all_execute);
    RUN_TEST(submit_dep_on_heap_handle_fails);

    task_system_destroy(g_ts);

    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
