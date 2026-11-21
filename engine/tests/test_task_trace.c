/* Task graph tracing: an opt-in bounded log of executed tasks (start, end,
 * thread) and dependency edges, exported as a Chrome trace document with one
 * slice per task and a flow arrow per edge. */
#include "test_framework.h"
#include <core/trace_schema.h>
#include <task/task.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

static TaskSystem *g_ts;
static _Atomic u32 g_ran;
static char g_buf[1 << 18];

static void count_ran(void *ctx) {
    (void)ctx;
    atomic_fetch_add(&g_ran, 1u);
}

static usize count_substr(const char *haystack, const char *needle) {
    usize count = 0u;
    usize len = strlen(needle);
    for (const char *p = strstr(haystack, needle); p; p = strstr(p + len, needle)) count++;
    return count;
}

static bool export_ok(usize *len) {
    *len = 0u;
    return task_trace_export(g_ts, g_buf, sizeof g_buf, len);
}

static bool find_record(TaskHandle h, TaskTraceRecord *out) {
    u32 n = task_trace_record_count(g_ts);
    for (u32 i = 0; i < n; i++) {
        if (task_trace_get(g_ts, i, out) && out->handle == h) return true;
    }
    return false;
}

TEST(tracing_is_off_until_enabled) {
    atomic_store(&g_ran, 0u);
    for (u32 i = 0; i < 8u; i++) task_submit(g_ts, count_ran, NULL);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_ran), 8u);
    ASSERT_FALSE(task_trace_enabled(g_ts));
    ASSERT_EQ(task_trace_record_count(g_ts), 0u);
    usize len = 7u;
    ASSERT_FALSE(export_ok(&len));
    ASSERT_EQ(len, 0u);
    ASSERT_FALSE(task_trace_enable(g_ts, 0u));
    ASSERT_FALSE(task_trace_enable(NULL, 16u));
    ASSERT_FALSE(task_trace_enabled(NULL));
    ASSERT_EQ(task_trace_record_count(NULL), 0u);
}

TEST(each_executed_task_becomes_one_slice) {
    ASSERT_TRUE(task_trace_enable(g_ts, 64u));
    ASSERT_TRUE(task_trace_enabled(g_ts));
    atomic_store(&g_ran, 0u);
    for (u32 i = 0; i < 10u; i++) task_submit(g_ts, count_ran, NULL);
    task_wait(g_ts);
    ASSERT_EQ(task_trace_record_count(g_ts), 10u);
    ASSERT_EQ(task_trace_dropped(g_ts), 0u);
    for (u32 i = 0; i < 10u; i++) {
        TaskTraceRecord r;
        ASSERT_TRUE(task_trace_get(g_ts, i, &r));
        ASSERT_TRUE(r.handle != TASK_HANDLE_INVALID);
        ASSERT_TRUE(r.end_ns >= r.start_ns);
        ASSERT_TRUE(r.worker >= -1 && r.worker < (i32)task_worker_count(g_ts));
        ASSERT_FALSE(r.cancelled);
    }
    TaskTraceRecord none;
    ASSERT_FALSE(task_trace_get(g_ts, 10u, &none));
    ASSERT_FALSE(task_trace_get(g_ts, 0u, NULL));

    usize len = 0u;
    ASSERT_TRUE(export_ok(&len));
    ASSERT_EQ(len, strlen(g_buf));
    ASSERT_EQ(strncmp(g_buf, "{\"traceEvents\":[", 16), 0);
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"X\""), 10u);
    ASSERT_EQ(count_substr(g_buf, "\"cat\":\"" BREAK_TRACE_CAT_TASK "\""), 10u);
    ASSERT_EQ(count_substr(g_buf, BREAK_TRACE_OTHER_DATA), 1u);
    ASSERT_EQ(strcmp(g_buf + len - 2u, "}}"), 0);
    /* one named track per worker plus the inline track */
    ASSERT_EQ(count_substr(g_buf, "\"name\":\"thread_name\""), task_worker_count(g_ts) + 1u);
    ASSERT_NOT_NULL(strstr(g_buf, "\"name\":\"inline\""));
    ASSERT_NOT_NULL(strstr(g_buf, "\"name\":\"worker 0\""));
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"s\""), 0u);
    task_trace_disable(g_ts);
    ASSERT_FALSE(task_trace_enabled(g_ts));
}

TEST(dependencies_become_flow_arrows) {
    ASSERT_TRUE(task_trace_enable(g_ts, 64u));
    atomic_store(&g_ran, 0u);
    TaskHandle a = task_submit_ex(g_ts, count_ran, NULL, TASK_PRIORITY_NORMAL);
    TaskHandle b = task_submit_dep(g_ts, count_ran, NULL, &a, 1u);
    TaskHandle ab[2] = {a, b};
    TaskHandle c = task_submit_dep(g_ts, count_ran, NULL, ab, 2u);
    ASSERT_TRUE(a != TASK_HANDLE_INVALID && b != TASK_HANDLE_INVALID && c != TASK_HANDLE_INVALID);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_ran), 3u);
    ASSERT_EQ(task_trace_edge_count(g_ts), 3u);

    TaskTraceRecord ra, rb, rc;
    ASSERT_TRUE(find_record(a, &ra));
    ASSERT_TRUE(find_record(b, &rb));
    ASSERT_TRUE(find_record(c, &rc));
    ASSERT_TRUE(rb.start_ns >= ra.end_ns);
    ASSERT_TRUE(rc.start_ns >= rb.end_ns);

    usize len = 0u;
    ASSERT_TRUE(export_ok(&len));
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"X\""), 3u);
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"s\""), 3u);
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"f\""), 3u);
    ASSERT_EQ(count_substr(g_buf, "\"cat\":\"" BREAK_TRACE_CAT_TASK_FLOW "\""), 6u);
    /* every arrow id appears exactly twice: once at its start, once at its end */
    for (u32 id = 1u; id <= 3u; id++) {
        char key[32];
        snprintf(key, sizeof key, "\"id\":%u,", id);
        ASSERT_EQ(count_substr(g_buf, key), 2u);
    }
    task_trace_disable(g_ts);
}

/* A dependency on a task that already finished is still an edge of the graph. */
TEST(dependency_on_a_finished_task_is_still_an_arrow) {
    ASSERT_TRUE(task_trace_enable(g_ts, 16u));
    TaskHandle a = task_submit_ex(g_ts, count_ran, NULL, TASK_PRIORITY_HIGH);
    task_wait_handle(g_ts, a);
    TaskHandle b = task_submit_dep(g_ts, count_ran, NULL, &a, 1u);
    ASSERT_TRUE(b != TASK_HANDLE_INVALID);
    task_wait(g_ts);
    ASSERT_EQ(task_trace_edge_count(g_ts), 1u);
    usize len = 0u;
    ASSERT_TRUE(export_ok(&len));
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"s\""), 1u);
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"f\""), 1u);
    task_trace_disable(g_ts);
}

TEST(full_log_drops_and_keeps_arrows_paired) {
    ASSERT_TRUE(task_trace_enable(g_ts, 4u));
    TaskHandle prev = task_submit_ex(g_ts, count_ran, NULL, TASK_PRIORITY_NORMAL);
    for (u32 i = 0; i < 9u; i++) prev = task_submit_dep(g_ts, count_ran, NULL, &prev, 1u);
    task_wait(g_ts);
    ASSERT_EQ(task_trace_record_count(g_ts), 4u);
    ASSERT_EQ(task_trace_dropped(g_ts), 6u);
    usize len = 0u;
    ASSERT_TRUE(export_ok(&len));
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"X\""), 4u);
    /* the chain's first four tasks were kept: three arrows join them, and
     * arrows to dropped tasks are left out instead of dangling */
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"s\""), 3u);
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"f\""), 3u);
    /* re-enabling starts a fresh log */
    ASSERT_TRUE(task_trace_enable(g_ts, 8u));
    ASSERT_EQ(task_trace_record_count(g_ts), 0u);
    ASSERT_EQ(task_trace_dropped(g_ts), 0u);
    ASSERT_EQ(task_trace_edge_count(g_ts), 0u);
    task_trace_disable(g_ts);
}

TEST(cancelled_tasks_are_marked) {
    ASSERT_TRUE(task_trace_enable(g_ts, 8u));
    TaskCancelToken token;
    task_cancel_token_init(&token);
    task_cancel(&token);
    atomic_store(&g_ran, 0u);
    TaskHandle h = task_submit_cancellable(g_ts, count_ran, NULL, TASK_PRIORITY_NORMAL, &token,
                                           NULL, 0u);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_ran), 0u);
    TaskTraceRecord r;
    ASSERT_TRUE(find_record(h, &r));
    ASSERT_TRUE(r.cancelled);
    usize len = 0u;
    ASSERT_TRUE(export_ok(&len));
    ASSERT_EQ(count_substr(g_buf, "\"cancelled\":true"), 1u);
    task_trace_disable(g_ts);
}

TEST(short_buffer_reports_the_needed_length) {
    ASSERT_TRUE(task_trace_enable(g_ts, 8u));
    TaskHandle a = task_submit_ex(g_ts, count_ran, NULL, TASK_PRIORITY_NORMAL);
    (void)task_submit_dep(g_ts, count_ran, NULL, &a, 1u);
    task_wait(g_ts);
    usize full = 0u;
    ASSERT_TRUE(export_ok(&full));
    ASSERT_TRUE(full > 0u);
    char small[32];
    memset(small, 'x', sizeof small);
    usize need = 0u;
    ASSERT_FALSE(task_trace_export(g_ts, small, sizeof small, &need));
    ASSERT_EQ(need, full);
    ASSERT_EQ(small[0], '\0');
    char *exact = (char *)malloc(full + 1u);
    ASSERT_NOT_NULL(exact);
    usize got = 0u;
    bool ok = task_trace_export(g_ts, exact, full + 1u, &got);
    bool same = ok && strcmp(exact, g_buf) == 0;
    free(exact);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(same);
    ASSERT_EQ(got, full);
    ASSERT_FALSE(task_trace_export(g_ts, NULL, 0u, NULL));
    task_trace_disable(g_ts);
}

/* Many tasks on every worker at once: the log stays consistent. */
TEST(concurrent_recording_is_consistent) {
    ASSERT_TRUE(task_trace_enable(g_ts, 256u));
    atomic_store(&g_ran, 0u);
    TaskHandle roots[16];
    for (u32 i = 0; i < 16u; i++) roots[i] = task_submit_ex(g_ts, count_ran, NULL, TASK_PRIORITY_NORMAL);
    for (u32 i = 0; i < 300u; i++) (void)task_submit_dep(g_ts, count_ran, NULL, &roots[i % 16u], 1u);
    task_wait(g_ts);
    ASSERT_EQ(atomic_load(&g_ran), 316u);
    ASSERT_EQ(task_trace_record_count(g_ts) + task_trace_dropped(g_ts), 316u);
    ASSERT_EQ(task_trace_record_count(g_ts), 256u);
    usize len = 0u;
    ASSERT_TRUE(export_ok(&len));
    ASSERT_EQ(count_substr(g_buf, "\"ph\":\"s\""), count_substr(g_buf, "\"ph\":\"f\""));
    task_trace_disable(g_ts);
}

TEST_MAIN_BEGIN()
    g_ts = task_system_create(3);
    if (!g_ts) return 1;
    RUN_TEST(tracing_is_off_until_enabled);
    RUN_TEST(each_executed_task_becomes_one_slice);
    RUN_TEST(dependencies_become_flow_arrows);
    RUN_TEST(dependency_on_a_finished_task_is_still_an_arrow);
    RUN_TEST(full_log_drops_and_keeps_arrows_paired);
    RUN_TEST(cancelled_tasks_are_marked);
    RUN_TEST(short_buffer_reports_the_needed_length);
    RUN_TEST(concurrent_recording_is_consistent);
    task_system_destroy(g_ts);
TEST_MAIN_END()
