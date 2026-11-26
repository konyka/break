/* Runtime Core metrics registry: named counters/gauges with a non-blocking
 * record path and an owner-thread snapshot/text-encode export. */
#include "test_framework.h"
#include <core/platform_thread.h>
#include <runtime/runtime_metrics.h>
#include <stdint.h>
#include <string.h>

static BreakRuntimeMetrics *make_metrics(u32 capacity) {
    BreakRuntimeMetricsConfig cfg = {capacity};
    BreakRuntimeMetrics *m = NULL;
    return break_runtime_metrics_create(&cfg, &m) == BREAK_RUNTIME_OK ? m : NULL;
}

static u64 sample_value(const BreakRuntimeMetricSample *s, u32 n, const char *name) {
    for (u32 i = 0u; i < n; i++)
        if (strcmp(s[i].name, name) == 0) return s[i].value;
    return UINT64_MAX;
}

TEST(create_validates_config_and_defaults) {
    BreakRuntimeMetrics *m = NULL;
    BreakRuntimeMetricsConfig over = {BREAK_RUNTIME_METRICS_MAX_CAPACITY + 1u};
    BreakRuntimeMetricsStats stats;
    ASSERT_EQ(break_runtime_metrics_create(NULL, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_create(&over, &m), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(m == NULL);
    ASSERT_EQ(break_runtime_metrics_create(NULL, &m), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_stats(m, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.tracked, 0u);
    break_runtime_metrics_destroy(m);
}

TEST(counter_adds_accumulate_and_saturate) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricSample out[8];
    BreakRuntimeMetricsStats stats;
    u32 n = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 3u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 4u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER,
                                        UINT64_MAX),
              BREAK_RUNTIME_OK); /* saturates */
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 8u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(sample_value(out, n, "net.sent"), UINT64_MAX);
    ASSERT_EQ(break_runtime_metrics_stats(m, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.tracked, 1u);
    ASSERT_EQ(stats.updates, 3u);
    ASSERT_EQ(stats.saturations, 1u);
    break_runtime_metrics_destroy(m);
}

TEST(gauge_set_overwrites_and_kind_mismatch_is_invalid) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricSample out[8];
    u32 n = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_set(m, "queue.depth", BREAK_RUNTIME_METRIC_GAUGE, 10u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "queue.depth", BREAK_RUNTIME_METRIC_GAUGE, 2u),
              BREAK_RUNTIME_OK);
    /* add on a gauge, set on a counter, and kind disagreeing with a slot */
    ASSERT_EQ(break_runtime_metrics_add(m, "queue.depth", BREAK_RUNTIME_METRIC_GAUGE, 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_add(m, "queue.depth", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_set(m, "queue.depth", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 8u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(sample_value(out, n, "queue.depth"), 2u);
    break_runtime_metrics_destroy(m);
}

TEST(names_are_validated) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    char longname[BREAK_RUNTIME_METRICS_NAME_CAPACITY + 4u];
    ASSERT_NOT_NULL(m);
    memset(longname, 'x', sizeof longname);
    longname[sizeof longname - 1u] = '\0';
    ASSERT_EQ(break_runtime_metrics_add(m, NULL, BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_add(m, "", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_add(m, longname, BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_add(m, "has space", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_add(m, "has\nnewline", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_INVALID);
    break_runtime_metrics_destroy(m);
}

TEST(table_full_overloads_without_disturbing_existing_slots) {
    BreakRuntimeMetrics *m = make_metrics(2u);
    BreakRuntimeMetricSample out[4];
    BreakRuntimeMetricsStats stats;
    u32 n = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "a", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_add(m, "b", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_add(m, "c", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_OVERLOAD);
    /* an existing name still updates after the table is full */
    ASSERT_EQ(break_runtime_metrics_add(m, "a", BREAK_RUNTIME_METRIC_COUNTER, 5u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 4u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(sample_value(out, n, "a"), 6u);
    ASSERT_EQ(break_runtime_metrics_stats(m, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.overflow_drops, 1u);
    ASSERT_EQ(stats.tracked, 2u);
    break_runtime_metrics_destroy(m);
}

TEST(snapshot_reports_required_count_when_too_small) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricSample out[1];
    u32 n = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "a", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "b", BREAK_RUNTIME_METRIC_GAUGE, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 1u, &n), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(n, 2u);
    break_runtime_metrics_destroy(m);
}

TEST(encode_emits_stable_lines_in_creation_order) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    char buf[128];
    usize len = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 7u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "queue.depth", BREAK_RUNTIME_METRIC_GAUGE, 3u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_encode(m, buf, sizeof buf, &len), BREAK_RUNTIME_OK);
    ASSERT_STR_EQ(buf,
                  "BRKM1 net.sent counter 7\n"
                  "BRKM1 queue.depth gauge 3\n");
    ASSERT_EQ(len, strlen(buf));
    break_runtime_metrics_destroy(m);
}

TEST(encode_reports_required_length_when_too_small) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    char small[8];
    usize full = 0u;
    usize len = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 7u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_encode(m, NULL, 0u, &full), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(full, strlen("BRKM1 net.sent counter 7\n"));
    ASSERT_EQ(break_runtime_metrics_encode(m, small, sizeof small, &len), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(len, full);
    ASSERT_EQ(small[0], '\0');
    break_runtime_metrics_destroy(m);
}

TEST(close_rejects_updates_but_keeps_snapshot_readable) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricSample out[8];
    BreakRuntimeMetricsStats stats;
    u32 n = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "a", BREAK_RUNTIME_METRIC_COUNTER, 9u),
              BREAK_RUNTIME_OK);
    break_runtime_metrics_close(m);
    break_runtime_metrics_close(m); /* idempotent */
    ASSERT_EQ(break_runtime_metrics_add(m, "a", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(break_runtime_metrics_set(m, "b", BREAK_RUNTIME_METRIC_GAUGE, 1u),
              BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 8u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(sample_value(out, n, "a"), 9u);
    ASSERT_EQ(break_runtime_metrics_stats(m, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.closed_rejects, 2u);
    break_runtime_metrics_destroy(m);
}

typedef struct OwnerProbe {
    BreakRuntimeMetrics *metrics;
    BreakRuntimeError snapshot_rc;
    BreakRuntimeError encode_rc;
} OwnerProbe;

static PLATFORM_THREAD_RET owner_probe(PLATFORM_THREAD_ARG arg) {
    OwnerProbe *p = (OwnerProbe *)arg;
    BreakRuntimeMetricSample out[4];
    char buf[64];
    u32 n = 0u;
    usize len = 0u;
    p->snapshot_rc = break_runtime_metrics_snapshot(p->metrics, out, 4u, &n);
    p->encode_rc = break_runtime_metrics_encode(p->metrics, buf, sizeof buf, &len);
    return PLATFORM_THREAD_RETURN;
}

TEST(snapshot_and_encode_reject_non_owner_thread) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    OwnerProbe probe;
    PlatformThread thread;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "a", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_OK);
    probe.metrics = m;
    probe.snapshot_rc = BREAK_RUNTIME_OK;
    probe.encode_rc = BREAK_RUNTIME_OK;
    ASSERT_TRUE(platform_thread_create(&thread, owner_probe, &probe));
    platform_thread_join(thread);
    ASSERT_EQ(probe.snapshot_rc, BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(probe.encode_rc, BREAK_RUNTIME_REJECTED);
    break_runtime_metrics_destroy(m);
}

static const BreakRuntimeMetricSample kAlertSamples[] = {
    {"queue.depth", BREAK_RUNTIME_METRIC_GAUGE, 10u},
    {"net.sent", BREAK_RUNTIME_METRIC_COUNTER, 3u},
    {"pool.free", BREAK_RUNTIME_METRIC_GAUGE, 2u},
};

TEST(alerts_fire_on_strict_threshold_crossing_in_rule_order) {
    const BreakRuntimeMetricAlertRule rules[] = {
        {"queue.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 9u},  /* 10 > 9 fires */
        {"queue.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 10u}, /* equal: silent */
        {"pool.free", BREAK_RUNTIME_METRIC_ALERT_BELOW, 2u},    /* equal: silent */
        {"pool.free", BREAK_RUNTIME_METRIC_ALERT_BELOW, 3u},    /* 2 < 3 fires */
        {"missing", BREAK_RUNTIME_METRIC_ALERT_BELOW, 100u},    /* absent: silent */
        {"net.sent", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 0u},     /* 3 > 0 fires */
    };
    u32 fired[8];
    u32 n = 99u;
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, rules, 6u, fired, 8u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 3u);
    ASSERT_EQ(fired[0], 0u);
    ASSERT_EQ(fired[1], 3u);
    ASSERT_EQ(fired[2], 5u);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, rules, 0u, fired, 8u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 0u);
}

TEST(alerts_report_required_count_when_output_too_small) {
    const BreakRuntimeMetricAlertRule rules[] = {
        {"queue.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 1u},
        {"net.sent", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 1u},
    };
    u32 fired[1] = {77u};
    u32 n = 0u;
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, rules, 2u, fired, 1u, &n),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(fired[0], 77u);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, rules, 2u, NULL, 0u, &n),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(n, 2u);
}

TEST(alerts_validate_arguments) {
    const BreakRuntimeMetricAlertRule good[] = {
        {"queue.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 1u}};
    const BreakRuntimeMetricAlertRule bad_op[] = {
        {"queue.depth", (BreakRuntimeMetricAlertOp)7, 1u}};
    const BreakRuntimeMetricAlertRule null_name[] = {
        {NULL, BREAK_RUNTIME_METRIC_ALERT_ABOVE, 1u}};
    u32 fired[2];
    u32 n = 5u;
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, good, 1u, fired, 2u, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(NULL, 3u, good, 1u, fired, 2u, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, NULL, 1u, fired, 2u, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, good, 1u, NULL, 2u, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, bad_op, 1u, fired, 2u, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, null_name, 1u, fired, 2u,
                                                    &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(kAlertSamples, 3u, good,
                                                    BREAK_RUNTIME_METRICS_MAX_CAPACITY + 1u,
                                                    fired, 2u, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(n, 0u);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(NULL, 0u, good, 1u, fired, 2u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 0u);
}

TEST(alerts_evaluate_a_live_snapshot) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricSample out[8];
    const BreakRuntimeMetricAlertRule rules[] = {
        {"bus.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 4u}};
    u32 count = 0u;
    u32 fired[1];
    u32 n = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_set(m, "bus.depth", BREAK_RUNTIME_METRIC_GAUGE, 4u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 8u, &count), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(out, count, rules, 1u, fired, 1u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 0u);
    ASSERT_EQ(break_runtime_metrics_set(m, "bus.depth", BREAK_RUNTIME_METRIC_GAUGE, 5u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, out, 8u, &count), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_evaluate_alerts(out, count, rules, 1u, fired, 1u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(fired[0], 0u);
    break_runtime_metrics_destroy(m);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_config_and_defaults);
    RUN_TEST(counter_adds_accumulate_and_saturate);
    RUN_TEST(gauge_set_overwrites_and_kind_mismatch_is_invalid);
    RUN_TEST(names_are_validated);
    RUN_TEST(table_full_overloads_without_disturbing_existing_slots);
    RUN_TEST(snapshot_reports_required_count_when_too_small);
    RUN_TEST(encode_emits_stable_lines_in_creation_order);
    RUN_TEST(encode_reports_required_length_when_too_small);
    RUN_TEST(close_rejects_updates_but_keeps_snapshot_readable);
    RUN_TEST(snapshot_and_encode_reject_non_owner_thread);
    RUN_TEST(alerts_fire_on_strict_threshold_crossing_in_rule_order);
    RUN_TEST(alerts_report_required_count_when_output_too_small);
    RUN_TEST(alerts_validate_arguments);
    RUN_TEST(alerts_evaluate_a_live_snapshot);
TEST_MAIN_END()
