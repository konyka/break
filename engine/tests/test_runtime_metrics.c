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

static BreakRuntimeMetricsHistory *make_history(u32 depth, u32 width) {
    BreakRuntimeMetricsHistoryConfig cfg = {depth, width};
    BreakRuntimeMetricsHistory *h = NULL;
    return break_runtime_metrics_history_create(&cfg, &h) == BREAK_RUNTIME_OK ? h : NULL;
}

TEST(history_create_validates_config) {
    BreakRuntimeMetricsHistoryConfig zero = {0u, 4u};
    BreakRuntimeMetricsHistoryConfig wide = {4u, BREAK_RUNTIME_METRICS_MAX_CAPACITY + 1u};
    BreakRuntimeMetricsHistoryConfig deep = {BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH + 1u, 4u};
    BreakRuntimeMetricsHistory *h = (BreakRuntimeMetricsHistory *)1;
    ASSERT_EQ(break_runtime_metrics_history_create(&zero, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_create(NULL, &h), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(h == NULL);
    ASSERT_EQ(break_runtime_metrics_history_create(&zero, &h), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_create(&wide, &h), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_create(&deep, &h), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(h == NULL);
    break_runtime_metrics_history_destroy(NULL);
}

TEST(history_records_frames_newest_first_and_evicts_oldest) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(2u, 4u);
    BreakRuntimeMetricSample out[4];
    BreakRuntimeMetricsHistoryStats stats;
    u32 n = 0u;
    u64 tick = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    ASSERT_EQ(break_runtime_metrics_history_frame(h, 0u, out, 4u, &n, &tick),
              BREAK_RUNTIME_STALE);
    for (u64 v = 1u; v <= 3u; ++v) {
        ASSERT_EQ(break_runtime_metrics_set(m, "q.depth", BREAK_RUNTIME_METRIC_GAUGE, v * 10u),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_metrics_history_record(h, m, v * 100u), BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(break_runtime_metrics_history_frame(h, 0u, out, 4u, &n, &tick), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(tick, 300u);
    ASSERT_EQ(sample_value(out, n, "q.depth"), 30u);
    ASSERT_EQ(break_runtime_metrics_history_frame(h, 1u, out, 4u, &n, &tick), BREAK_RUNTIME_OK);
    ASSERT_EQ(tick, 200u);
    ASSERT_EQ(sample_value(out, n, "q.depth"), 20u);
    ASSERT_EQ(break_runtime_metrics_history_frame(h, 2u, out, 4u, &n, &tick),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(n, 0u);
    ASSERT_EQ(break_runtime_metrics_history_stats(h, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.recorded, 3u);
    ASSERT_EQ(stats.evicted, 1u);
    ASSERT_EQ(stats.frames, 2u);
    ASSERT_EQ(stats.width_drops, 0u);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(history_rejects_non_increasing_ticks_and_wide_snapshots) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 1u);
    BreakRuntimeMetricsHistoryStats stats;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    ASSERT_EQ(break_runtime_metrics_history_record(h, NULL, 1u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_record(NULL, m, 1u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_set(m, "a", BREAK_RUNTIME_METRIC_GAUGE, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 5u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 5u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 4u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_set(m, "b", BREAK_RUNTIME_METRIC_GAUGE, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 6u), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_runtime_metrics_history_stats(h, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.recorded, 1u);
    ASSERT_EQ(stats.frames, 1u);
    ASSERT_EQ(stats.width_drops, 1u);
    ASSERT_EQ(break_runtime_metrics_history_stats(h, NULL), BREAK_RUNTIME_INVALID);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(history_frame_reports_required_count_when_too_small) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(2u, 4u);
    BreakRuntimeMetricSample out[1];
    u32 n = 0u;
    u64 tick = 9u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    ASSERT_EQ(break_runtime_metrics_set(m, "a", BREAK_RUNTIME_METRIC_GAUGE, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_add(m, "b", BREAK_RUNTIME_METRIC_COUNTER, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_frame(h, 0u, out, 1u, &n, &tick),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(break_runtime_metrics_history_frame(h, 0u, NULL, 1u, &n, &tick),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_frame(h, 0u, out, 1u, NULL, &tick),
              BREAK_RUNTIME_INVALID);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

static void record_depth(BreakRuntimeMetrics *m, BreakRuntimeMetricsHistory *h, u64 v, u64 tick) {
    (void)break_runtime_metrics_set(m, "q.depth", BREAK_RUNTIME_METRIC_GAUGE, v);
    (void)break_runtime_metrics_history_record(h, m, tick);
}

TEST(sustained_alerts_require_every_recent_frame_to_fire) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(8u, 4u);
    const BreakRuntimeMetricAlertRule rules[] = {
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u},
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_BELOW, 100u},
    };
    u32 fired[2];
    u32 n = 9u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    record_depth(m, h, 9u, 1u);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, rules, 2u, 2u, fired, 2u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 0u); /* fewer frames than the sustain window: nothing fires */
    record_depth(m, h, 3u, 2u);
    record_depth(m, h, 9u, 3u);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, rules, 2u, 2u, fired, 2u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 1u); /* rule 0 dipped at tick 2 */
    ASSERT_EQ(fired[0], 1u);
    record_depth(m, h, 9u, 4u);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, rules, 2u, 2u, fired, 2u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(fired[0], 0u);
    ASSERT_EQ(fired[1], 1u);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, rules, 2u, 3u, fired, 2u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(fired[0], 1u);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, rules, 2u, 1u, fired, 1u, &n),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(n, 2u);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(sustained_alerts_validate_arguments) {
    BreakRuntimeMetricsHistory *h = make_history(2u, 4u);
    const BreakRuntimeMetricAlertRule good[] = {
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u}};
    const BreakRuntimeMetricAlertRule bad[] = {{NULL, BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u}};
    u32 fired[1];
    u32 n = 4u;
    ASSERT_NOT_NULL(h);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(NULL, good, 1u, 1u, fired, 1u, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, good, 1u, 0u, fired, 1u, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, bad, 1u, 1u, fired, 1u, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, good, 1u, 1u, fired, 1u, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(n, 0u);
    break_runtime_metrics_history_destroy(h);
}

TEST(sustain_longer_than_the_ring_never_fires) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(2u, 4u);
    const BreakRuntimeMetricAlertRule rules[] = {
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u}};
    u32 fired[1];
    u32 n = 9u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    record_depth(m, h, 9u, 1u);
    record_depth(m, h, 9u, 2u);
    record_depth(m, h, 9u, 3u);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, rules, 1u, 2u, fired, 1u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_alerts(h, rules, 1u, 3u, fired, 1u, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 0u); /* only 2 frames retained: a 3-frame window is unproven */
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(alert_edges_report_raise_and_clear_between_consecutive_windows) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(8u, 4u);
    const BreakRuntimeMetricAlertRule rules[] = {
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u},
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_BELOW, 100u},
    };
    BreakRuntimeMetricAlertEdge edges[2];
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    record_depth(m, h, 9u, 1u);
    record_depth(m, h, 9u, 2u);
    /* Window at age 0 is [2,1]; the previous window [1,0] is unproven. */
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, rules, 2u, 2u, edges, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(edges[0], BREAK_RUNTIME_METRIC_ALERT_RAISED);
    ASSERT_EQ(edges[1], BREAK_RUNTIME_METRIC_ALERT_RAISED);
    record_depth(m, h, 9u, 3u);
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, rules, 2u, 2u, edges, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(edges[0], BREAK_RUNTIME_METRIC_ALERT_STEADY);
    ASSERT_EQ(edges[1], BREAK_RUNTIME_METRIC_ALERT_STEADY);
    record_depth(m, h, 3u, 4u);
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, rules, 2u, 2u, edges, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(edges[0], BREAK_RUNTIME_METRIC_ALERT_CLEARED);
    ASSERT_EQ(edges[1], BREAK_RUNTIME_METRIC_ALERT_STEADY);
    record_depth(m, h, 3u, 5u);
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, rules, 2u, 2u, edges, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(edges[0], BREAK_RUNTIME_METRIC_ALERT_STEADY);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(alert_edges_validate_arguments) {
    BreakRuntimeMetricsHistory *h = make_history(2u, 4u);
    const BreakRuntimeMetricAlertRule good[] = {
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u},
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_BELOW, 5u}};
    const BreakRuntimeMetricAlertRule bad[] = {{"q.depth", (BreakRuntimeMetricAlertOp)9, 5u}};
    BreakRuntimeMetricAlertEdge edges[2] = {BREAK_RUNTIME_METRIC_ALERT_RAISED,
                                            BREAK_RUNTIME_METRIC_ALERT_RAISED};
    ASSERT_NOT_NULL(h);
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(NULL, good, 2u, 1u, edges, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, good, 2u, 0u, edges, 2u),
              BREAK_RUNTIME_INVALID);
    /* depth 2: a sustain of 2 leaves no frame to prove the previous window. */
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, good, 2u, 2u, edges, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, bad, 1u, 1u, edges, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, good, 2u, 1u, NULL, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, good, 2u, 1u, edges, 1u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(edges[0], BREAK_RUNTIME_METRIC_ALERT_RAISED); /* untouched on error */
    ASSERT_EQ(break_runtime_metrics_history_alert_edges(h, good, 2u, 1u, edges, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(edges[0], BREAK_RUNTIME_METRIC_ALERT_STEADY); /* empty ring: nothing fires */
    break_runtime_metrics_history_destroy(h);
}

TEST(history_delta_measures_counter_growth_over_a_window) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    u64 delta = 99u;
    u64 ticks = 99u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 5u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 10u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "net.sent", 1u, &delta, &ticks),
              BREAK_RUNTIME_STALE); /* one frame: no window yet */
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 7u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 15u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 3u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 30u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "net.sent", 1u, &delta, &ticks),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(delta, 3u);
    ASSERT_EQ(ticks, 15u);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "net.sent", 2u, &delta, &ticks),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(delta, 10u);
    ASSERT_EQ(ticks, 20u);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "net.sent", 3u, &delta, &ticks),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "missing", 1u, &delta, &ticks),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 31u), BREAK_RUNTIME_OK);
    /* Full ring of depth 4: a span of 4 would wrap onto the newest frame. */
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "net.sent", 3u, &delta, &ticks),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(delta, 11u);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "net.sent", 4u, &delta, &ticks),
              BREAK_RUNTIME_STALE);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(history_delta_rejects_gauges_and_bad_arguments) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    u64 delta = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    record_depth(m, h, 9u, 1u);
    record_depth(m, h, 3u, 2u);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "q.depth", 1u, &delta, NULL),
              BREAK_RUNTIME_INVALID); /* a gauge can fall: a delta is meaningless */
    ASSERT_EQ(break_runtime_metrics_history_delta(NULL, "q.depth", 1u, &delta, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, NULL, 1u, &delta, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "q.depth", 0u, &delta, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_delta(h, "q.depth", 1u, NULL, NULL),
              BREAK_RUNTIME_INVALID);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

static BreakRuntimeError decode_text(const char *text, BreakRuntimeMetricSample *out, u32 cap,
                                     u32 *n) {
    return break_runtime_metrics_decode(text, strlen(text), out, cap, n);
}

TEST(decode_round_trips_the_encoding) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricSample snap[8];
    BreakRuntimeMetricSample back[8];
    char buf[256];
    usize len = 0u;
    u32 count = 0u;
    u32 n = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, UINT64_MAX),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "q.depth", BREAK_RUNTIME_METRIC_GAUGE, 0u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_snapshot(m, snap, 8u, &count), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_encode(m, buf, sizeof buf, &len), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_decode(buf, len, back, 8u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, count);
    for (u32 i = 0u; i < n; ++i) {
        ASSERT_STR_EQ(back[i].name, snap[i].name);
        ASSERT_EQ(back[i].kind, snap[i].kind);
        ASSERT_EQ(back[i].value, snap[i].value);
    }
    ASSERT_EQ(break_runtime_metrics_decode("", 0u, back, 8u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 0u);
    ASSERT_EQ(break_runtime_metrics_decode(NULL, 0u, NULL, 0u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 0u);
    break_runtime_metrics_destroy(m);
}

TEST(decode_rejects_malformed_input_as_a_whole) {
    static const char *const bad[] = {
        "BRKM1 a counter 1",                       /* missing final newline */
        "BRKM2 a counter 1\n",                     /* wrong version tag */
        "BRKM1 a timer 1\n",                       /* unknown kind */
        "BRKM1 a counter\n",                       /* missing value */
        "BRKM1 a counter 1 2\n",                   /* trailing field */
        "BRKM1  a counter 1\n",                    /* empty name (double space) */
        "BRKM1 a counter -1\n",                    /* sign */
        "BRKM1 a counter +1\n",                    /* sign */
        "BRKM1 a counter 01\n",                    /* non-canonical leading zero */
        "BRKM1 a counter 1x\n",                    /* junk digit */
        "BRKM1 a counter 18446744073709551616\n",  /* UINT64_MAX + 1 */
        "BRKM1 a counter 1\r\n",                   /* CR is not part of the format */
        "BRKM1 a counter 1\nBRKM1 a gauge 2\n",    /* duplicate name */
        "BRKM1 a counter 1\n\n",                   /* blank line */
        "BRKM1 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa counter 1\n", /* 48-char name */
    };
    BreakRuntimeMetricSample out[4];
    u32 n = 0u;
    for (usize i = 0u; i < sizeof bad / sizeof bad[0]; ++i) {
        n = 7u;
        out[0].value = 42u;
        ASSERT_EQ(decode_text(bad[i], out, 4u, &n), BREAK_RUNTIME_INVALID);
        ASSERT_EQ(n, 0u);
        ASSERT_EQ(out[0].value, 42u); /* nothing written */
    }
    ASSERT_EQ(break_runtime_metrics_decode("BRKM1 a\0 counter 1\n", 20u, out, 4u, &n),
              BREAK_RUNTIME_INVALID); /* embedded NUL */
}

TEST(decode_accepts_boundary_values_and_reports_required_count) {
    BreakRuntimeMetricSample out[2];
    u32 n = 0u;
    ASSERT_EQ(decode_text("BRKM1 a counter 18446744073709551615\nBRKM1 b gauge 0\n", out, 2u,
                          &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(out[0].value, UINT64_MAX);
    ASSERT_EQ(out[0].kind, BREAK_RUNTIME_METRIC_COUNTER);
    ASSERT_EQ(out[1].value, 0u);
    ASSERT_EQ(out[1].kind, BREAK_RUNTIME_METRIC_GAUGE);
    ASSERT_EQ(decode_text("BRKM1 a counter 1\nBRKM1 b gauge 2\nBRKM1 c gauge 3\n", out, 2u,
                          &n),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(n, 3u);
    ASSERT_EQ(decode_text("BRKM1 a counter 1\nBRKM1 b gauge 2\nBRKM1 c gauge\n", out, 2u, &n),
              BREAK_RUNTIME_INVALID); /* malformed wins over too small */
    ASSERT_EQ(break_runtime_metrics_decode("x", 1u, out, 2u, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_decode(NULL, 1u, out, 2u, &n), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_decode("", 0u, NULL, 2u, &n), BREAK_RUNTIME_INVALID);
}

static BreakRuntimeError merge_texts(const char *const *docs, u32 n, char *out, usize cap,
                                     usize *out_len) {
    const void *ptrs[4];
    usize lens[4];
    for (u32 i = 0u; i < n; ++i) {
        ptrs[i] = docs[i];
        lens[i] = strlen(docs[i]);
    }
    return break_runtime_metrics_merge(ptrs, lens, n, out, cap, out_len);
}

TEST(merge_keeps_the_newest_value_per_name_in_first_seen_order) {
    static const char *const docs[] = {
        "BRKM1 net.sent counter 10\nBRKM1 q.depth gauge 4\n",
        "BRKM1 q.depth gauge 9\nBRKM1 pool.free gauge 2\n",
        "BRKM1 net.sent counter 25\n",
    };
    char out[256];
    usize len = 0u;
    ASSERT_EQ(merge_texts(docs, 3u, out, sizeof out, &len), BREAK_RUNTIME_OK);
    /* Names keep the order they were first seen; each takes the newest
     * document's value (a counter is monotonic, so the newer snapshot already
     * includes the older one). */
    ASSERT_STR_EQ(out,
                  "BRKM1 net.sent counter 25\n"
                  "BRKM1 q.depth gauge 9\n"
                  "BRKM1 pool.free gauge 2\n");
    ASSERT_EQ(len, strlen(out));
}

TEST(merge_output_is_strictly_decodable_and_round_trips_encode) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricSample back[8];
    char a[256];
    char b[256];
    char out[512];
    const void *ptrs[2];
    usize lens[2];
    usize len = 0u;
    u32 n = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(break_runtime_metrics_add(m, "x", BREAK_RUNTIME_METRIC_COUNTER, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_encode(m, a, sizeof a, &lens[0]), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_add(m, "x", BREAK_RUNTIME_METRIC_COUNTER, 4u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "y", BREAK_RUNTIME_METRIC_GAUGE, UINT64_MAX),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_encode(m, b, sizeof b, &lens[1]), BREAK_RUNTIME_OK);
    ptrs[0] = a;
    ptrs[1] = b;
    ASSERT_EQ(break_runtime_metrics_merge(ptrs, lens, 2u, out, sizeof out, &len),
              BREAK_RUNTIME_OK);
    /* Merging a document with a later snapshot of the same registry yields
     * exactly the later snapshot's encoding. */
    ASSERT_EQ(len, lens[1]);
    ASSERT_TRUE(memcmp(out, b, len) == 0);
    ASSERT_EQ(break_runtime_metrics_decode(out, len, back, 8u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(back[0].value, 5u);
    ASSERT_EQ(back[1].value, UINT64_MAX);
    break_runtime_metrics_destroy(m);
}

TEST(merge_rejects_a_kind_change_and_any_malformed_input_as_a_whole) {
    static const char *const kind_flip[] = {
        "BRKM1 a counter 1\n",
        "BRKM1 a gauge 1\n",
    };
    static const char *const one_bad[] = {
        "BRKM1 a counter 1\n",
        "BRKM1 b counter 01\n",
    };
    char out[64];
    usize len = 7u;
    memcpy(out, "sentinel", 9u);
    ASSERT_EQ(merge_texts(kind_flip, 2u, out, sizeof out, &len), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(len, 0u);
    ASSERT_STR_EQ(out, "sentinel");
    len = 7u;
    ASSERT_EQ(merge_texts(one_bad, 2u, out, sizeof out, &len), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(len, 0u);
    ASSERT_STR_EQ(out, "sentinel");
}

TEST(merge_reports_the_required_size_and_handles_empty_documents) {
    static const char *const docs[] = {
        "BRKM1 alpha counter 1\n",
        "",
        "BRKM1 beta gauge 22\n",
    };
    static const char *const empties[] = {"", ""};
    char out[64];
    usize len = 0u;
    const usize want = strlen("BRKM1 alpha counter 1\nBRKM1 beta gauge 22\n");
    /* Needs `want` bytes plus a NUL. One byte short: OVERLOAD with the size. */
    memcpy(out, "sentinel", 9u);
    ASSERT_EQ(merge_texts(docs, 3u, out, want, &len), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(len, want);
    ASSERT_EQ(out[0], '\0');
    ASSERT_EQ(merge_texts(docs, 3u, out, want + 1u, &len), BREAK_RUNTIME_OK);
    ASSERT_EQ(len, want);
    ASSERT_STR_EQ(out, "BRKM1 alpha counter 1\nBRKM1 beta gauge 22\n");
    /* All-empty input merges to the empty document. */
    ASSERT_EQ(merge_texts(empties, 2u, out, sizeof out, &len), BREAK_RUNTIME_OK);
    ASSERT_EQ(len, 0u);
    ASSERT_STR_EQ(out, "");
}

TEST(merge_validates_arguments) {
    const void *ptrs[1] = {"BRKM1 a counter 1\n"};
    usize lens[1] = {18u};
    const void *null_doc[1] = {NULL};
    usize nonzero[1] = {3u};
    char out[32];
    usize len = 0u;
    ASSERT_EQ(break_runtime_metrics_merge(ptrs, lens, 1u, out, sizeof out, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_merge(NULL, lens, 1u, out, sizeof out, &len),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_merge(ptrs, NULL, 1u, out, sizeof out, &len),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_merge(ptrs, lens, 1u, NULL, 8u, &len), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_merge(null_doc, nonzero, 1u, out, sizeof out, &len),
              BREAK_RUNTIME_INVALID);
    {
        /* Exactly the document cap is accepted; one more is refused. */
        const void *many[BREAK_RUNTIME_METRICS_MERGE_MAX_DOCUMENTS + 1u];
        usize many_lens[BREAK_RUNTIME_METRICS_MERGE_MAX_DOCUMENTS + 1u];
        for (u32 i = 0u; i <= BREAK_RUNTIME_METRICS_MERGE_MAX_DOCUMENTS; ++i) {
            many[i] = "BRKM1 a counter 1\n";
            many_lens[i] = 18u;
        }
        ASSERT_EQ(break_runtime_metrics_merge(many, many_lens,
                                              BREAK_RUNTIME_METRICS_MERGE_MAX_DOCUMENTS, out,
                                              sizeof out, &len),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(len, 18u);
        ASSERT_EQ(break_runtime_metrics_merge(many, many_lens,
                                              BREAK_RUNTIME_METRICS_MERGE_MAX_DOCUMENTS + 1u, out,
                                              sizeof out, &len),
                  BREAK_RUNTIME_INVALID);
    }
    /* Zero documents is the empty merge. */
    ASSERT_EQ(break_runtime_metrics_merge(NULL, NULL, 0u, out, sizeof out, &len),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(len, 0u);
}

TEST(merge_rejects_more_distinct_names_than_one_document_may_hold) {
    /* Each document is valid on its own, but together they hold more distinct
     * names than BREAK_RUNTIME_METRICS_MAX_CAPACITY, which the strict decoder
     * would refuse. The merge must refuse rather than emit such a document. */
    enum { k_docs = 2, k_per = 600 };
    static char docs[k_docs][k_per * 24];
    const void *ptrs[k_docs];
    usize lens[k_docs];
    static char out[k_docs * k_per * 24 + 1];
    usize len = 0u;
    for (u32 d = 0u; d < k_docs; ++d) {
        usize at = 0u;
        for (u32 i = 0u; i < k_per; ++i) {
            int w = snprintf(docs[d] + at, sizeof docs[d] - at, "BRKM1 d%u.n%u gauge 1\n", d, i);
            ASSERT_TRUE(w > 0);
            at += (usize)w;
        }
        ptrs[d] = docs[d];
        lens[d] = at;
    }
    ASSERT_EQ(break_runtime_metrics_merge(ptrs, lens, k_docs, out, sizeof out, &len),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(len, 0u);
}

TEST(alert_edge_encoding_lists_only_transitions_in_rule_order) {
    const BreakRuntimeMetricAlertRule rules[] = {
        {"q.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u},
        {"pool.free", BREAK_RUNTIME_METRIC_ALERT_BELOW, 2u},
        {"net.sent", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 18446744073709551615u},
    };
    const BreakRuntimeMetricAlertEdge edges[] = {BREAK_RUNTIME_METRIC_ALERT_RAISED,
                                                 BREAK_RUNTIME_METRIC_ALERT_STEADY,
                                                 BREAK_RUNTIME_METRIC_ALERT_CLEARED};
    const BreakRuntimeMetricAlertEdge steady[] = {BREAK_RUNTIME_METRIC_ALERT_STEADY,
                                                  BREAK_RUNTIME_METRIC_ALERT_STEADY,
                                                  BREAK_RUNTIME_METRIC_ALERT_STEADY};
    char buf[160];
    usize len = 0u;
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(rules, edges, 3u, buf, sizeof buf, &len),
              BREAK_RUNTIME_OK);
    ASSERT_STR_EQ(buf, "BRKA1 raised q.depth above 5\n"
                       "BRKA1 cleared net.sent above 18446744073709551615\n");
    ASSERT_EQ(len, strlen(buf));
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(rules, steady, 3u, buf, sizeof buf, &len),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(len, 0u);
    ASSERT_STR_EQ(buf, "");
}

TEST(alert_edge_encoding_reports_required_length_and_validates) {
    const BreakRuntimeMetricAlertRule rules[] = {
        {"pool.free", BREAK_RUNTIME_METRIC_ALERT_BELOW, 2u}};
    const BreakRuntimeMetricAlertRule bad_name[] = {
        {"has space", BREAK_RUNTIME_METRIC_ALERT_BELOW, 2u}};
    const BreakRuntimeMetricAlertRule bad_op[] = {
        {"pool.free", (BreakRuntimeMetricAlertOp)5, 2u}};
    const BreakRuntimeMetricAlertEdge raised[] = {BREAK_RUNTIME_METRIC_ALERT_RAISED};
    const BreakRuntimeMetricAlertEdge bogus[] = {(BreakRuntimeMetricAlertEdge)9};
    const char want[] = "BRKA1 raised pool.free below 2\n";
    char buf[64];
    usize len = 0u;
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(rules, raised, 1u, buf, sizeof want - 1u,
                                                       &len),
              BREAK_RUNTIME_OVERLOAD); /* no room for the NUL */
    ASSERT_EQ(len, sizeof want - 1u);
    ASSERT_STR_EQ(buf, "");
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(rules, raised, 1u, NULL, 0u, &len),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(len, sizeof want - 1u);
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(rules, raised, 1u, buf, sizeof want, &len),
              BREAK_RUNTIME_OK);
    ASSERT_STR_EQ(buf, want);
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(bad_name, raised, 1u, buf, sizeof buf,
                                                       &len),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(bad_op, raised, 1u, buf, sizeof buf, &len),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(rules, bogus, 1u, buf, sizeof buf, &len),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(rules, raised, 1u, buf, sizeof buf, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(NULL, raised, 1u, buf, sizeof buf, &len),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_encode_alert_edges(rules, raised, 1u, NULL, 4u, &len),
              BREAK_RUNTIME_INVALID);
}


static BreakRuntimeMetricsRetryQueue *make_retry(u32 capacity, usize max_payload) {
    BreakRuntimeMetricsRetryConfig cfg;
    BreakRuntimeMetricsRetryQueue *q = NULL;
    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = capacity;
    cfg.max_payload_bytes = max_payload;
    return break_runtime_metrics_retry_create(&cfg, &q) == BREAK_RUNTIME_OK ? q : NULL;
}

static bool retry_head_is(BreakRuntimeMetricsRetryQueue *q, const char *expect) {
    const void *bytes = NULL;
    usize len = 0u;
    u32 attempts = 0u;
    if (break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts) != BREAK_RUNTIME_OK)
        return false;
    return len == strlen(expect) && memcmp(bytes, expect, len) == 0;
}

TEST(retry_queue_is_fifo_and_release_advances) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryStats stats;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "one", 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "two", 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "three", 5u), BREAK_RUNTIME_OK);
    ASSERT_TRUE(retry_head_is(q, "one"));
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_TRUE(retry_head_is(q, "two"));
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_TRUE(retry_head_is(q, "three"));
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    /* Empty: peek, attempt and release are all STALE. */
    {
        const void *bytes = NULL;
        usize len = 7u;
        u32 attempts = 7u;
        ASSERT_EQ(break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts),
                  BREAK_RUNTIME_STALE);
        ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_STALE);
        ASSERT_EQ(break_runtime_metrics_retry_record_attempt(q, &attempts),
                  BREAK_RUNTIME_STALE);
    }
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_EQ(stats.enqueued, 3u);
    ASSERT_EQ(stats.released, 3u);
    ASSERT_EQ(stats.dropped_oldest, 0u);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_queue_full_drops_the_oldest_entry) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 64u);
    BreakRuntimeMetricsRetryStats stats;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "b", 1u), BREAK_RUNTIME_OK);
    /* Full: the newest wins and the oldest is evicted, still OK. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "c", 1u), BREAK_RUNTIME_OK);
    ASSERT_TRUE(retry_head_is(q, "b"));
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 2u);
    ASSERT_EQ(stats.enqueued, 3u);
    ASSERT_EQ(stats.dropped_oldest, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_TRUE(retry_head_is(q, "c"));
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_queue_counts_attempts_per_entry) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 64u);
    BreakRuntimeMetricsRetryStats stats;
    const void *bytes = NULL;
    usize len = 0u;
    u32 attempts = 99u;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "x", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "y", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 0u);
    ASSERT_EQ(break_runtime_metrics_retry_record_attempt(q, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_record_attempt(q, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 2u);
    ASSERT_EQ(break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 2u);
    /* Attempts belong to the entry: the next entry starts clean. */
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 0u);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.attempts, 2u);
    /* Slot reuse must clear attempts: wrap the ring so a new payload lands in
     * the slot whose previous entry had recorded attempts. */
    ASSERT_EQ(break_runtime_metrics_retry_record_attempt(q, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "z", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_TRUE(retry_head_is(q, "z"));
    ASSERT_EQ(break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 0u);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_queue_validates_configuration_and_payloads) {
    BreakRuntimeMetricsRetryQueue *q = NULL;
    BreakRuntimeMetricsRetryConfig cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = 0u;
    cfg.max_payload_bytes = 16u;
    ASSERT_EQ(break_runtime_metrics_retry_create(&cfg, &q), BREAK_RUNTIME_INVALID);
    cfg.capacity = BREAK_RUNTIME_METRICS_RETRY_MAX_ENTRIES + 1u;
    ASSERT_EQ(break_runtime_metrics_retry_create(&cfg, &q), BREAK_RUNTIME_INVALID);
    cfg.capacity = 2u;
    cfg.max_payload_bytes = 0u;
    ASSERT_EQ(break_runtime_metrics_retry_create(&cfg, &q), BREAK_RUNTIME_INVALID);
    cfg.max_payload_bytes = BREAK_RUNTIME_METRICS_RETRY_MAX_PAYLOAD_BYTES + 1u;
    ASSERT_EQ(break_runtime_metrics_retry_create(&cfg, &q), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_create(NULL, &q), BREAK_RUNTIME_INVALID);
    cfg.max_payload_bytes = 4u;
    ASSERT_EQ(break_runtime_metrics_retry_create(&cfg, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(q == NULL);
    q = make_retry(2u, 4u);
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, NULL, 2u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "ab", 0u), BREAK_RUNTIME_INVALID);
    /* One byte past the configured payload cap. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "abcde", 5u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "abcd", 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(NULL, "a", 1u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_stats(NULL, NULL), BREAK_RUNTIME_INVALID);
    break_runtime_metrics_retry_destroy(q);
    break_runtime_metrics_retry_destroy(NULL);
}

TEST(retry_queue_round_trips_a_real_metrics_encoding) {
    BreakRuntimeMetrics *m = make_metrics(0u);
    BreakRuntimeMetricsRetryQueue *q = make_retry(4u, 4096u);
    BreakRuntimeMetricSample decoded[8];
    char buf[1024];
    usize len = 0u;
    const void *bytes = NULL;
    usize held = 0u;
    u32 attempts = 0u;
    u32 count = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_add(m, "pushes.failed", BREAK_RUNTIME_METRIC_COUNTER, 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_encode(m, buf, sizeof(buf), &len), BREAK_RUNTIME_OK);
    ASSERT_TRUE(len > 0u);
    /* A failed delivery parks the exact encoded bytes for a later attempt. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, buf, len), BREAK_RUNTIME_OK);
    memset(buf, 0, sizeof(buf));
    ASSERT_EQ(break_runtime_metrics_retry_peek(q, &bytes, &held, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(held, len);
    ASSERT_EQ(break_runtime_metrics_decode((const char *)bytes, held, decoded, 8u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(sample_value(decoded, count, "pushes.failed"), 4u);
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    break_runtime_metrics_retry_destroy(q);
    break_runtime_metrics_destroy(m);
}


typedef struct {
    u32 calls;
    u32 fail_first;   /* fail this many calls, then succeed */
    bool always_fail;
    char seen[8][16];
} FakeSender;

static BreakRuntimeError fake_send(void *user, const void *bytes, usize len) {
    FakeSender *f = (FakeSender *)user;
    if (f->calls < 8u && len < sizeof(f->seen[0])) {
        memcpy(f->seen[f->calls], bytes, len);
        f->seen[f->calls][len] = '\0';
    }
    f->calls++;
    if (f->always_fail || f->calls <= f->fail_first) return BREAK_RUNTIME_FAILED;
    return BREAK_RUNTIME_OK;
}

TEST(retry_drain_delivers_in_order_within_the_send_budget) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    memset(&f, 0, sizeof(f));
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "b", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "c", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 2u, 0u, &r), BREAK_RUNTIME_OK);
    ASSERT_EQ(r.delivered, 2u);
    ASSERT_EQ(r.failed, 0u);
    ASSERT_EQ(f.calls, 2u);
    ASSERT_TRUE(strcmp(f.seen[0], "a") == 0);
    ASSERT_TRUE(strcmp(f.seen[1], "b") == 0);
    ASSERT_TRUE(retry_head_is(q, "c"));
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 8u, 0u, &r), BREAK_RUNTIME_OK);
    ASSERT_EQ(r.delivered, 1u);
    /* Empty queue: OK, nothing sent. */
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 8u, 0u, &r), BREAK_RUNTIME_OK);
    ASSERT_EQ(r.delivered + r.failed + r.abandoned, 0u);
    ASSERT_EQ(f.calls, 3u);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_drain_stops_on_failure_and_keeps_the_entry) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    const void *bytes = NULL;
    usize len = 0u;
    u32 attempts = 0u;
    memset(&f, 0, sizeof(f));
    f.fail_first = 1u;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "b", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 8u, 0u, &r), BREAK_RUNTIME_OK);
    /* One failed send backs off: nothing delivered, head kept with 1 attempt. */
    ASSERT_EQ(r.failed, 1u);
    ASSERT_EQ(r.delivered, 0u);
    ASSERT_EQ(f.calls, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 1u);
    ASSERT_TRUE(retry_head_is(q, "a"));
    /* Next step: the sender recovers and both entries go out in order. */
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 8u, 0u, &r), BREAK_RUNTIME_OK);
    ASSERT_EQ(r.delivered, 2u);
    ASSERT_TRUE(strcmp(f.seen[1], "a") == 0);
    ASSERT_TRUE(strcmp(f.seen[2], "b") == 0);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_drain_abandons_a_poison_payload_at_max_attempts) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    memset(&f, 0, sizeof(f));
    f.always_fail = true;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "p", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "q", 1u), BREAK_RUNTIME_OK);
    /* First failure on "p" is below the limit: stop and keep it. */
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 8u, 2u, &r), BREAK_RUNTIME_OK);
    ASSERT_EQ(r.failed, 1u);
    ASSERT_EQ(r.abandoned, 0u);
    ASSERT_TRUE(retry_head_is(q, "p"));
    /* Second failure reaches the limit: "p" is dropped and draining moves on
     * to "q", whose own first failure stops the drain. */
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 8u, 2u, &r), BREAK_RUNTIME_OK);
    ASSERT_EQ(r.abandoned, 1u);
    ASSERT_EQ(r.failed, 2u);
    ASSERT_TRUE(retry_head_is(q, "q"));
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_drain_validates_arguments) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 8u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    memset(&f, 0, sizeof(f));
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_drain(NULL, fake_send, &f, 1u, 0u, &r),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, NULL, &f, 1u, 0u, &r), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 0u, 0u, &r),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 1u, 0u, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(f.calls, 0u);
    break_runtime_metrics_retry_destroy(q);
}


static BreakRuntimeMetricsRetryQueue *make_retry_coalescing(u32 capacity, usize max_payload) {
    BreakRuntimeMetricsRetryConfig cfg;
    BreakRuntimeMetricsRetryQueue *q = NULL;
    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = capacity;
    cfg.max_payload_bytes = max_payload;
    cfg.coalesce_repeats = true;
    return break_runtime_metrics_retry_create(&cfg, &q) == BREAK_RUNTIME_OK ? q : NULL;
}

TEST(retry_coalesces_repeats_of_the_newest_payload) {
    BreakRuntimeMetricsRetryQueue *q = make_retry_coalescing(4u, 64u);
    BreakRuntimeMetricsRetryStats stats;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "same", 4u), BREAK_RUNTIME_OK);
    /* Identical repeats fold into the newest entry instead of filling the ring. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "same", 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "same", 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_EQ(stats.enqueued, 1u);
    ASSERT_EQ(stats.coalesced, 2u);
    ASSERT_EQ(stats.dropped_oldest, 0u);
    /* A different payload is stored; a same-length different-byte one too. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "diff", 4u), BREAK_RUNTIME_OK);
    /* A prefix of the newest is NOT a duplicate (length must match). */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "dif", 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 3u);
    ASSERT_EQ(stats.enqueued, 3u);
    ASSERT_TRUE(retry_head_is(q, "same"));
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_coalescing_compares_only_the_newest_entry) {
    BreakRuntimeMetricsRetryQueue *q = make_retry_coalescing(4u, 64u);
    BreakRuntimeMetricsRetryStats stats;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "b", 1u), BREAK_RUNTIME_OK);
    /* "a" is in the ring but not newest, so it is stored again. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 3u);
    ASSERT_EQ(stats.coalesced, 0u);
    /* Coalescing must not resurrect a released entry as a comparison target. */
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_EQ(stats.coalesced, 0u);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_without_coalescing_keeps_every_repeat) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(4u, 64u); /* default: off */
    BreakRuntimeMetricsRetryStats stats;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "same", 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "same", 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 2u);
    ASSERT_EQ(stats.coalesced, 0u);
    break_runtime_metrics_retry_destroy(q);
}


static BreakRuntimeMetricsRetryQueue *g_reentry_queue;
static BreakRuntimeError g_reentry_result;

static BreakRuntimeError reentrant_send(void *user, const void *bytes, usize len) {
    (void)user;
    (void)bytes;
    (void)len;
    /* A send callback must not mutate the queue it is draining: the payload it
     * was handed lives in the ring and an enqueue can overwrite that slot. */
    g_reentry_result = break_runtime_metrics_retry_enqueue(g_reentry_queue, "zz", 2u);
    return BREAK_RUNTIME_OK;
}

TEST(retry_rejects_enqueue_reentered_from_a_send_callback) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 8u);
    BreakRuntimeMetricsRetryDrainResult r;
    BreakRuntimeMetricsRetryStats stats;
    ASSERT_NOT_NULL(q);
    g_reentry_queue = q;
    g_reentry_result = BREAK_RUNTIME_OK;
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "aa", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, reentrant_send, NULL, 4u, 0u, &r),
              BREAK_RUNTIME_OK);
    /* The reentrant enqueue is refused, so the borrowed payload cannot be
     * overwritten mid-send; the delivery itself still succeeds. */
    ASSERT_EQ(g_reentry_result, BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(r.delivered, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_EQ(stats.enqueued, 1u);
    /* After the drain returns, enqueue works again. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "bb", 2u), BREAK_RUNTIME_OK);
    g_reentry_queue = NULL;
    break_runtime_metrics_retry_destroy(q);
}


static BreakRuntimeMetricsRetryBackoff backoff_of(u64 base_us, u64 max_us) {
    BreakRuntimeMetricsRetryBackoff b;
    memset(&b, 0, sizeof(b));
    b.base_us = base_us;
    b.max_us = max_us;
    return b;
}

TEST(retry_timed_drain_waits_for_the_exponential_backoff_deadline) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryBackoff b = backoff_of(100u, 10000u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    u64 due = 0u;
    memset(&f, 0, sizeof(f));
    f.always_fail = true;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    /* A fresh entry is due immediately. */
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 0u);
    /* First failure at t=1000 schedules the retry base_us later. */
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, 1000u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(r.failed, 1u);
    ASSERT_EQ(f.calls, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 1100u);
    /* Before the deadline the timed drain sends nothing at all. */
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, 1099u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(r.failed + r.delivered + r.abandoned, 0u);
    ASSERT_EQ(r.deferred, 1u);
    ASSERT_EQ(f.calls, 1u);
    /* At the deadline it retries; the second failure doubles the delay. */
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, 1100u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(r.failed, 1u);
    ASSERT_EQ(f.calls, 2u);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 1300u);
    /* Third failure doubles again: 400 us. */
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, 1300u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 1700u);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_timed_drain_caps_the_delay_and_resets_it_on_success) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryBackoff b = backoff_of(100u, 250u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    u64 due = 0u;
    u64 now = 0u;
    memset(&f, 0, sizeof(f));
    f.always_fail = true;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "b", 1u), BREAK_RUNTIME_OK);
    /* Delays 100, 200, then capped at 250 for every later failure. */
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, now, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, now + 100u);
    now = due;
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, now, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, now + 200u);
    now = due;
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, now, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, now + 250u);
    now = due;
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, now, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, now + 250u);
    /* The sender recovers: "a" goes out, and "b" is attempted in the same
     * drain because the backoff belongs to the failed entry, not the queue. */
    f.always_fail = false;
    now = due;
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, now, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(r.delivered, 2u);
    ASSERT_EQ(r.deferred, 0u);
    /* Empty queue: nothing is due. */
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_STALE);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_timed_drain_does_not_overflow_a_huge_attempt_count) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 8u);
    BreakRuntimeMetricsRetryBackoff b = backoff_of(1000u, UINT64_MAX);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    u64 due = 0u;
    u64 now = 5u;
    memset(&f, 0, sizeof(f));
    f.always_fail = true;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    /* 80 failures would shift base_us past 64 bits; the delay must saturate
     * rather than wrap to a small value, and the deadline must not wrap past
     * UINT64_MAX either. */
    for (u32 i = 0u; i < 80u; ++i) {
        ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 1u, 0u, &b, now, &r),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
        ASSERT_TRUE(due >= now);
        now = due;
    }
    ASSERT_EQ(due, UINT64_MAX);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_timed_drain_saturates_the_shift_for_a_large_attempt_count) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 8u);
    BreakRuntimeMetricsRetryBackoff b = backoff_of(1000u, UINT64_MAX);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    u64 due = 0u;
    u32 attempts = 0u;
    const void *bytes = NULL;
    usize len = 0u;
    memset(&f, 0, sizeof(f));
    f.always_fail = true;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    /* The untimed drain records attempts without setting a deadline, so the
     * entry reaches 55 attempts while still being due now. */
    for (u32 i = 0u; i < 55u; ++i) {
        ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 1u, 0u, &r),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 55u);
    /* The 56th failure needs 1000 << 55, which does not fit in 64 bits. It
     * must saturate to UINT64_MAX, not wrap to a smaller finite delay. */
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 1u, 0u, &b, 0u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, UINT64_MAX);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_reused_slot_starts_with_no_deadline) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(1u, 8u);
    BreakRuntimeMetricsRetryBackoff b = backoff_of(1000u, 1000u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    u64 due = 0u;
    memset(&f, 0, sizeof(f));
    f.always_fail = true;
    ASSERT_NOT_NULL(q);
    /* With capacity 1 every entry lives in the same slot. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 1u, 0u, &b, 0u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 1000u);
    /* Release it, then enqueue a new payload into the reused slot: the new
     * entry must be due at once, not inherit the old deadline. */
    ASSERT_EQ(break_runtime_metrics_retry_release(q), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "b", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 0u);
    /* Same for a full queue that evicts the oldest entry to make room. */
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 1u, 0u, &b, 0u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 1000u);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "c", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 0u);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_timed_drain_validates_arguments) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 8u);
    BreakRuntimeMetricsRetryBackoff b = backoff_of(100u, 1000u);
    BreakRuntimeMetricsRetryBackoff zero_base = backoff_of(0u, 1000u);
    BreakRuntimeMetricsRetryBackoff inverted = backoff_of(500u, 100u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    u64 due = 0u;
    memset(&f, 0, sizeof(f));
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(NULL, fake_send, &f, 1u, 0u, &b, 0u, &r),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, NULL, &f, 1u, 0u, &b, 0u, &r),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 0u, 0u, &b, 0u, &r),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 1u, 0u, NULL, 0u, &r),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 1u, 0u, &b, 0u, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 1u, 0u, &zero_base, 0u,
                                                      &r),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 1u, 0u, &inverted, 0u,
                                                      &r),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(NULL, &due), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_next_due(q, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(f.calls, 0u);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_untimed_drain_ignores_any_backoff_deadline) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 8u);
    BreakRuntimeMetricsRetryBackoff b = backoff_of(1000000u, 1000000u);
    BreakRuntimeMetricsRetryDrainResult r;
    FakeSender f;
    memset(&f, 0, sizeof(f));
    f.fail_first = 1u;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "a", 1u), BREAK_RUNTIME_OK);
    /* A timed failure sets a one-second deadline... */
    ASSERT_EQ(break_runtime_metrics_retry_drain_timed(q, fake_send, &f, 8u, 0u, &b, 0u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(r.failed, 1u);
    /* ...but the original untimed drain keeps its contract and sends now. */
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, fake_send, &f, 8u, 0u, &r), BREAK_RUNTIME_OK);
    ASSERT_EQ(r.delivered, 1u);
    ASSERT_EQ(f.calls, 2u);
    break_runtime_metrics_retry_destroy(q);
}


static usize retry_save_to(BreakRuntimeMetricsRetryQueue *q, u8 *buf, usize cap) {
    usize len = 0u;
    return break_runtime_metrics_retry_save(q, buf, cap, &len) == BREAK_RUNTIME_OK ? len : 0u;
}

TEST(retry_save_then_load_restores_payloads_attempts_and_order) {
    BreakRuntimeMetricsRetryQueue *src = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryQueue *dst = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryStats stats;
    u8 blob[1024];
    usize len;
    u32 attempts = 0u;
    u32 loaded = 0u;
    const void *bytes = NULL;
    usize blen = 0u;
    ASSERT_NOT_NULL(src);
    ASSERT_NOT_NULL(dst);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "one", 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "two", 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "three", 5u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_record_attempt(src, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_record_attempt(src, &attempts), BREAK_RUNTIME_OK);
    len = retry_save_to(src, blob, sizeof blob);
    ASSERT_TRUE(len > 0u);
    ASSERT_EQ(break_runtime_metrics_retry_load(dst, blob, len, &loaded), BREAK_RUNTIME_OK);
    ASSERT_EQ(loaded, 3u);
    /* FIFO order and the head's attempt count survive the round trip. */
    ASSERT_EQ(break_runtime_metrics_retry_peek(dst, &bytes, &blen, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(blen, 3u);
    ASSERT_TRUE(memcmp(bytes, "one", 3u) == 0);
    ASSERT_EQ(attempts, 2u);
    ASSERT_EQ(break_runtime_metrics_retry_release(dst), BREAK_RUNTIME_OK);
    ASSERT_TRUE(retry_head_is(dst, "two"));
    ASSERT_EQ(break_runtime_metrics_retry_peek(dst, &bytes, &blen, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 0u);
    ASSERT_EQ(break_runtime_metrics_retry_release(dst), BREAK_RUNTIME_OK);
    ASSERT_TRUE(retry_head_is(dst, "three"));
    ASSERT_EQ(break_runtime_metrics_retry_stats(dst, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 1u);
    /* The saved image is canonical: saving the reloaded queue reproduces it. */
    {
        BreakRuntimeMetricsRetryQueue *again = make_retry(4u, 64u);
        u8 blob2[1024];
        usize len2;
        ASSERT_NOT_NULL(again);
        ASSERT_EQ(break_runtime_metrics_retry_load(again, blob, len, &loaded), BREAK_RUNTIME_OK);
        len2 = retry_save_to(again, blob2, sizeof blob2);
        ASSERT_EQ(len2, len);
        ASSERT_TRUE(memcmp(blob, blob2, len) == 0);
        break_runtime_metrics_retry_destroy(again);
    }
    /* An empty queue saves to a valid image that loads as zero entries. */
    {
        BreakRuntimeMetricsRetryQueue *empty = make_retry(2u, 8u);
        BreakRuntimeMetricsRetryQueue *into = make_retry(2u, 8u);
        u8 eb[64];
        usize elen;
        ASSERT_NOT_NULL(empty);
        ASSERT_NOT_NULL(into);
        elen = retry_save_to(empty, eb, sizeof eb);
        ASSERT_TRUE(elen > 0u);
        ASSERT_EQ(break_runtime_metrics_retry_load(into, eb, elen, &loaded), BREAK_RUNTIME_OK);
        ASSERT_EQ(loaded, 0u);
        break_runtime_metrics_retry_destroy(into);
        break_runtime_metrics_retry_destroy(empty);
    }
    break_runtime_metrics_retry_destroy(dst);
    break_runtime_metrics_retry_destroy(src);
}

TEST(retry_save_reports_the_required_size) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 16u);
    u8 blob[256];
    usize need = 0u;
    usize len = 0u;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "payload", 7u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_save(q, NULL, 0u, &need), BREAK_RUNTIME_OVERLOAD);
    ASSERT_TRUE(need > 7u);
    ASSERT_EQ(break_runtime_metrics_retry_save(q, blob, need - 1u, &len), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(len, need);
    ASSERT_EQ(break_runtime_metrics_retry_save(q, blob, need, &len), BREAK_RUNTIME_OK);
    ASSERT_EQ(len, need);
    break_runtime_metrics_retry_destroy(q);
}

TEST(retry_load_into_a_smaller_queue_keeps_the_newest_entries) {
    BreakRuntimeMetricsRetryQueue *src = make_retry(4u, 16u);
    BreakRuntimeMetricsRetryQueue *dst = make_retry(2u, 16u);
    BreakRuntimeMetricsRetryStats stats;
    u8 blob[512];
    usize len;
    u32 loaded = 0u;
    ASSERT_NOT_NULL(src);
    ASSERT_NOT_NULL(dst);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "b", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "c", 1u), BREAK_RUNTIME_OK);
    len = retry_save_to(src, blob, sizeof blob);
    ASSERT_TRUE(len > 0u);
    /* Same rule as enqueue on a full ring: the oldest entries are dropped. */
    ASSERT_EQ(break_runtime_metrics_retry_load(dst, blob, len, &loaded), BREAK_RUNTIME_OK);
    ASSERT_EQ(loaded, 3u);
    ASSERT_EQ(break_runtime_metrics_retry_stats(dst, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 2u);
    ASSERT_EQ(stats.dropped_oldest, 1u);
    ASSERT_TRUE(retry_head_is(dst, "b"));
    break_runtime_metrics_retry_destroy(dst);
    break_runtime_metrics_retry_destroy(src);
}

TEST(retry_load_rejects_corruption_as_a_whole) {
    BreakRuntimeMetricsRetryQueue *src = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryQueue *dst = make_retry(4u, 64u);
    BreakRuntimeMetricsRetryStats stats;
    u8 blob[512];
    u8 bad[512];
    usize len;
    u32 loaded = 0u;
    ASSERT_NOT_NULL(src);
    ASSERT_NOT_NULL(dst);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "alpha", 5u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "beta", 4u), BREAK_RUNTIME_OK);
    len = retry_save_to(src, blob, sizeof blob);
    ASSERT_TRUE(len > 0u);
    /* The destination already holds an entry; a rejected load leaves it. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(dst, "kept", 4u), BREAK_RUNTIME_OK);
    /* Every single-byte flip and every truncation is rejected. */
    for (usize i = 0u; i < len; ++i) {
        memcpy(bad, blob, len);
        bad[i] ^= 0x01u;
        loaded = 99u;
        ASSERT_EQ(break_runtime_metrics_retry_load(dst, bad, len, &loaded),
                  BREAK_RUNTIME_INVALID);
        ASSERT_EQ(loaded, 0u);
    }
    for (usize cut = 0u; cut < len; ++cut) {
        ASSERT_EQ(break_runtime_metrics_retry_load(dst, blob, cut, &loaded),
                  BREAK_RUNTIME_INVALID);
    }
    /* Trailing bytes after a valid image are not ignored. */
    memcpy(bad, blob, len);
    bad[len] = 0u;
    ASSERT_EQ(break_runtime_metrics_retry_load(dst, bad, len + 1u, &loaded),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_stats(dst, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_EQ(stats.enqueued, 1u);
    ASSERT_TRUE(retry_head_is(dst, "kept"));
    break_runtime_metrics_retry_destroy(dst);
    break_runtime_metrics_retry_destroy(src);
}

TEST(retry_load_rejects_an_entry_larger_than_the_queue_slot) {
    BreakRuntimeMetricsRetryQueue *src = make_retry(2u, 64u);
    BreakRuntimeMetricsRetryQueue *dst = make_retry(2u, 4u);
    BreakRuntimeMetricsRetryStats stats;
    u8 blob[256];
    usize len;
    u32 loaded = 0u;
    ASSERT_NOT_NULL(src);
    ASSERT_NOT_NULL(dst);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "ok", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "too-long", 8u), BREAK_RUNTIME_OK);
    len = retry_save_to(src, blob, sizeof blob);
    ASSERT_TRUE(len > 0u);
    /* The image is well formed, but one entry cannot fit a 4-byte slot. The
     * load is refused as a whole rather than half applied. */
    ASSERT_EQ(break_runtime_metrics_retry_load(dst, blob, len, &loaded), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(loaded, 0u);
    ASSERT_EQ(break_runtime_metrics_retry_stats(dst, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 0u);
    break_runtime_metrics_retry_destroy(dst);
    break_runtime_metrics_retry_destroy(src);
}

/* Independent CRC-32 (ISO-HDLC) so a test can re-seal an image it edited and
 * reach the checks behind the checksum. */
static u32 test_crc32(const u8 *p, usize n) {
    u32 crc = 0xFFFFFFFFu;
    for (usize i = 0u; i < n; ++i) {
        crc ^= p[i];
        for (int b = 0; b < 8; ++b) crc = (crc & 1u) ? (crc >> 1) ^ 0xEDB88320u : crc >> 1;
    }
    return ~crc;
}

static void test_seal(u8 *img, usize len) {
    u32 crc = test_crc32(img, len - 4u);
    img[len - 4u] = (u8)crc;
    img[len - 3u] = (u8)(crc >> 8);
    img[len - 2u] = (u8)(crc >> 16);
    img[len - 1u] = (u8)(crc >> 24);
}

TEST(retry_load_checks_magic_and_framing_behind_a_valid_checksum) {
    BreakRuntimeMetricsRetryQueue *src = make_retry(2u, 16u);
    BreakRuntimeMetricsRetryQueue *dst = make_retry(2u, 16u);
    u8 blob[256];
    u8 bad[256];
    usize len;
    u32 loaded = 0u;
    ASSERT_NOT_NULL(src);
    ASSERT_NOT_NULL(dst);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "abc", 3u), BREAK_RUNTIME_OK);
    len = retry_save_to(src, blob, sizeof blob);
    ASSERT_TRUE(len > 0u);
    /* The CRC is computed the same way as the library's: a re-sealed copy of
     * the original image still loads, so the re-seal is faithful. */
    memcpy(bad, blob, len);
    test_seal(bad, len);
    ASSERT_EQ(break_runtime_metrics_retry_load(dst, bad, len, &loaded), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_release(dst), BREAK_RUNTIME_OK);
    /* Wrong magic with a matching CRC. */
    memcpy(bad, blob, len);
    bad[4] = '2';
    test_seal(bad, len);
    ASSERT_EQ(break_runtime_metrics_retry_load(dst, bad, len, &loaded), BREAK_RUNTIME_INVALID);
    /* A count of 0 leaves the entry's bytes trailing before the CRC. */
    memcpy(bad, blob, len);
    bad[5] = bad[6] = bad[7] = bad[8] = 0u;
    test_seal(bad, len);
    ASSERT_EQ(break_runtime_metrics_retry_load(dst, bad, len, &loaded), BREAK_RUNTIME_INVALID);
    /* A zero-length entry is never produced by save. Build a well-framed image
     * holding one: magic, count 1, attempts 0, length 0, no payload, CRC. Its
     * framing is exact, so only the zero-length rule can reject it. */
    {
        u8 zero[5 + 4 + 8 + 4];
        memcpy(zero, "BRKR1", 5u);
        memset(zero + 5, 0, sizeof zero - 5u);
        zero[5] = 1u;
        test_seal(zero, sizeof zero);
        ASSERT_EQ(break_runtime_metrics_retry_load(dst, zero, sizeof zero, &loaded),
                  BREAK_RUNTIME_INVALID);
    }
    ASSERT_EQ(loaded, 0u);
    /* A count larger than the entries present: the walker must stop at the
     * end of the buffer instead of reading another entry header past it. The
     * image is exactly sized in its own heap block so ASan sees an over-read. */
    {
        u8 *over = (u8 *)malloc(len);
        ASSERT_NOT_NULL(over);
        memcpy(over, blob, len);
        over[5] = 2u;
        test_seal(over, len);
        ASSERT_EQ(break_runtime_metrics_retry_load(dst, over, len, &loaded),
                  BREAK_RUNTIME_INVALID);
        free(over);
    }
    /* An entry length that runs past the CRC. */
    {
        u8 *over = (u8 *)malloc(len);
        ASSERT_NOT_NULL(over);
        memcpy(over, blob, len);
        over[13] = 4u; /* "abc" holds 3 bytes; 4 overlaps the trailer */
        test_seal(over, len);
        ASSERT_EQ(break_runtime_metrics_retry_load(dst, over, len, &loaded),
                  BREAK_RUNTIME_INVALID);
        free(over);
    }
    /* Shorter than magic + count + CRC, yet sealed. */
    {
        u8 tiny[5 + 4];
        memcpy(tiny, "BRKR1", 5u);
        test_seal(tiny, sizeof tiny);
        ASSERT_EQ(break_runtime_metrics_retry_load(dst, tiny, sizeof tiny, &loaded),
                  BREAK_RUNTIME_INVALID);
    }
    break_runtime_metrics_retry_destroy(dst);
    break_runtime_metrics_retry_destroy(src);
}

TEST(retry_load_restores_repeats_even_into_a_coalescing_queue) {
    BreakRuntimeMetricsRetryQueue *src = make_retry(4u, 16u);
    BreakRuntimeMetricsRetryQueue *dst = make_retry_coalescing(4u, 16u);
    BreakRuntimeMetricsRetryStats stats;
    u8 blob[256];
    usize len;
    u32 loaded = 0u;
    u32 attempts = 0u;
    const void *bytes = NULL;
    usize blen = 0u;
    ASSERT_NOT_NULL(src);
    ASSERT_NOT_NULL(dst);
    /* Two identical payloads with different attempt counts. Folding them on
     * load would lose one entry and one attempt history. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "same", 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_record_attempt(src, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "same", 4u), BREAK_RUNTIME_OK);
    len = retry_save_to(src, blob, sizeof blob);
    ASSERT_EQ(break_runtime_metrics_retry_load(dst, blob, len, &loaded), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_stats(dst, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 2u);
    ASSERT_EQ(stats.coalesced, 0u);
    ASSERT_EQ(break_runtime_metrics_retry_peek(dst, &bytes, &blen, &attempts), BREAK_RUNTIME_OK);
    ASSERT_EQ(attempts, 1u);
    /* Coalescing still applies to ordinary enqueues afterwards. */
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(dst, "same", 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_stats(dst, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.coalesced, 1u);
    break_runtime_metrics_retry_destroy(dst);
    break_runtime_metrics_retry_destroy(src);
}

static u8 g_load_image[256];
static usize g_load_image_len;
static BreakRuntimeError g_load_result;

static BreakRuntimeError load_from_send(void *user, const void *bytes, usize len) {
    u32 loaded = 0u;
    (void)bytes;
    (void)len;
    g_load_result = break_runtime_metrics_retry_load((BreakRuntimeMetricsRetryQueue *)user,
                                                     g_load_image, g_load_image_len, &loaded);
    return BREAK_RUNTIME_OK;
}

TEST(retry_load_is_refused_from_inside_a_drain_callback) {
    BreakRuntimeMetricsRetryQueue *src = make_retry(2u, 16u);
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 16u);
    BreakRuntimeMetricsRetryDrainResult r;
    BreakRuntimeMetricsRetryStats stats;
    ASSERT_NOT_NULL(src);
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(src, "x", 1u), BREAK_RUNTIME_OK);
    g_load_image_len = retry_save_to(src, g_load_image, sizeof g_load_image);
    ASSERT_TRUE(g_load_image_len > 0u);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, "head", 4u), BREAK_RUNTIME_OK);
    g_load_result = BREAK_RUNTIME_OK;
    /* A load would append into the ring while send holds a borrowed slot. */
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, load_from_send, q, 1u, 0u, &r),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(g_load_result, BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.queued, 0u);
    break_runtime_metrics_retry_destroy(q);
    break_runtime_metrics_retry_destroy(src);
}

/* Compression (design section 35). Stream: "BRKZ1", u32 LE original length,
 * then tokens. A control byte c < 0x80 is a literal run of c + 1 bytes that
 * follow; c >= 0x80 is a match of (c & 0x7F) + 4 bytes copied from a u16 LE
 * distance (1..65535) back in the output. */
static usize compress_into(const void *in, usize len, u8 *out, usize cap) {
    usize n = 0u;
    return break_runtime_metrics_compress(in, len, out, cap, &n) == BREAK_RUNTIME_OK ? n : 0u;
}

TEST(compress_round_trips_an_encoded_registry_and_shrinks_it) {
    BreakRuntimeMetrics *m = make_metrics(64u);
    static char text[8192];
    static u8 packed[8192];
    static char back[8192];
    usize text_len = 0u;
    usize packed_len;
    usize back_len = 0u;
    char name[32];
    ASSERT_NOT_NULL(m);
    for (u32 i = 0u; i < 48u; ++i) {
        snprintf(name, sizeof name, "subsystem.queue%u.depth", i);
        ASSERT_EQ(break_runtime_metrics_set(m, name, BREAK_RUNTIME_METRIC_GAUGE, i * 7u),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(break_runtime_metrics_encode(m, text, sizeof text, &text_len), BREAK_RUNTIME_OK);
    packed_len = compress_into(text, text_len, packed, sizeof packed);
    ASSERT_TRUE(packed_len > 0u);
    /* BRKM1 lines repeat their prefix, kind and much of each name, so the
     * stream must come out well under half the size. */
    ASSERT_TRUE(packed_len * 2u < text_len);
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, back, sizeof back, &back_len),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(back_len, text_len);
    ASSERT_TRUE(memcmp(back, text, text_len) == 0);
    break_runtime_metrics_destroy(m);
}

TEST(compress_handles_incompressible_and_highly_repetitive_input) {
    static u8 noise[5000];
    static u8 packed[6000];
    static u8 back[70000];
    static u8 run[66000];
    usize back_len = 0u;
    usize packed_len;
    u32 s = 0x12345678u;
    for (usize i = 0u; i < sizeof noise; ++i) {
        s = s * 1103515245u + 12345u;
        noise[i] = (u8)(s >> 23);
    }
    packed_len = compress_into(noise, sizeof noise, packed, sizeof packed);
    ASSERT_TRUE(packed_len > 0u);
    /* Worst case is bounded: one control byte per 128 literals plus the
     * header, so random data never balloons. */
    ASSERT_TRUE(packed_len <= BREAK_RUNTIME_METRICS_COMPRESS_BOUND(sizeof noise));
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, back, sizeof back, &back_len),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(back_len, sizeof noise);
    ASSERT_TRUE(memcmp(back, noise, sizeof noise) == 0);
    /* A long run of one byte, longer than the 64 KiB match window. Matches
     * overlap their own output, which is how a run is copied. */
    memset(run, 'z', sizeof run);
    run[sizeof run - 1u] = '!';
    packed_len = compress_into(run, sizeof run, packed, sizeof packed);
    ASSERT_TRUE(packed_len > 0u);
    /* One match token covers at most 131 bytes in 3 bytes, so the best this
     * format can do is about 66000 / 131 * 3 = 1512 bytes plus a few literals.
     * The bound proves matches are found and chained, not merely emitted. */
    ASSERT_TRUE(packed_len < 1600u);
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, back, sizeof back, &back_len),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(back_len, sizeof run);
    ASSERT_TRUE(memcmp(back, run, sizeof run) == 0);
    /* Empty input is a header-only stream. */
    packed_len = compress_into("", 0u, packed, sizeof packed);
    ASSERT_EQ(packed_len, 9u);
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, back, sizeof back, &back_len),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(back_len, 0u);
}

TEST(compress_and_decompress_report_the_required_size) {
    static const char text[] = "BRKM1 a counter 1\nBRKM1 a.b counter 1\nBRKM1 a.b.c counter 1\n";
    u8 packed[256];
    char back[256];
    usize need = 0u;
    usize got = 0u;
    usize packed_len;
    /* Compress: OVERLOAD with the exact size, and nothing written past it. */
    ASSERT_EQ(break_runtime_metrics_compress(text, sizeof text - 1u, NULL, 0u, &need),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_TRUE(need > 9u);
    memset(packed, 0xA5, sizeof packed);
    ASSERT_EQ(break_runtime_metrics_compress(text, sizeof text - 1u, packed, need - 1u, &got),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(got, need);
    for (usize i = need - 1u; i < sizeof packed; ++i) ASSERT_EQ(packed[i], 0xA5u);
    ASSERT_EQ(break_runtime_metrics_compress(text, sizeof text - 1u, packed, need, &got),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(got, need);
    packed_len = got;
    /* Decompress: the size comes from the header, before any byte is copied. */
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, NULL, 0u, &need),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(need, sizeof text - 1u);
    memset(back, 0x5A, sizeof back);
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, back, need - 1u, &got),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(got, need);
    ASSERT_EQ((u8)back[0], 0x5Au);
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, back, need, &got),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(memcmp(back, text, need) == 0);
}

TEST(decompress_accepts_hand_built_streams_at_the_limits) {
    /* "ab" as literals, then a 6-byte match at distance 2 (overlapping). */
    static const u8 overlap[] = {'B', 'R', 'K', 'Z', '1', 8, 0, 0, 0,
                                 0x01, 'a', 'b', 0x82, 2, 0};
    /* A single 128-byte literal run, the longest one control byte allows. */
    static u8 longlit[9 + 1 + 128];
    /* A 131-byte match, the longest one control byte allows. */
    static const u8 longmatch[] = {'B', 'R', 'K', 'Z', '1', 132, 0, 0, 0,
                                   0x00, 'q', 0xFF, 1, 0};
    char out[256];
    usize n = 0u;
    ASSERT_EQ(break_runtime_metrics_decompress(overlap, sizeof overlap, out, sizeof out, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 8u);
    ASSERT_TRUE(memcmp(out, "abababab", 8u) == 0);
    memcpy(longlit, "BRKZ1", 5u);
    longlit[5] = 128u;
    longlit[6] = longlit[7] = longlit[8] = 0u;
    longlit[9] = 0x7Fu;
    for (u32 i = 0u; i < 128u; ++i) longlit[10u + i] = (u8)('A' + i % 26u);
    ASSERT_EQ(break_runtime_metrics_decompress(longlit, sizeof longlit, out, sizeof out, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 128u);
    ASSERT_EQ(out[127], (char)('A' + 127u % 26u));
    ASSERT_EQ(break_runtime_metrics_decompress(longmatch, sizeof longmatch, out, sizeof out, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 132u);
    for (u32 i = 0u; i < 132u; ++i) ASSERT_EQ(out[i], 'q');
}

TEST(decompress_rejects_malformed_streams) {
    static const u8 good[] = {'B', 'R', 'K', 'Z', '1', 8, 0, 0, 0, 0x01, 'a', 'b', 0x82, 2, 0};
    struct {
        const char *why;
        u8 bytes[24];
        usize len;
    } bad[] = {
        {"bad magic", {'B', 'R', 'K', 'Z', '2', 0, 0, 0, 0}, 9u},
        {"short header", {'B', 'R', 'K', 'Z', '1', 0, 0, 0}, 8u},
        {"distance 0", {'B', 'R', 'K', 'Z', '1', 5, 0, 0, 0, 0x00, 'a', 0x80, 0, 0}, 14u},
        {"distance past output", {'B', 'R', 'K', 'Z', '1', 5, 0, 0, 0, 0x00, 'a', 0x80, 2, 0}, 14u},
        {"match before any output", {'B', 'R', 'K', 'Z', '1', 4, 0, 0, 0, 0x80, 1, 0}, 12u},
        {"truncated literal", {'B', 'R', 'K', 'Z', '1', 3, 0, 0, 0, 0x02, 'a', 'b'}, 12u},
        {"truncated distance", {'B', 'R', 'K', 'Z', '1', 5, 0, 0, 0, 0x00, 'a', 0x80, 1}, 13u},
        {"output longer than header", {'B', 'R', 'K', 'Z', '1', 1, 0, 0, 0, 0x01, 'a', 'b'}, 12u},
        {"output shorter than header", {'B', 'R', 'K', 'Z', '1', 3, 0, 0, 0, 0x01, 'a', 'b'}, 12u},
        {"match overruns header", {'B', 'R', 'K', 'Z', '1', 3, 0, 0, 0, 0x00, 'a', 0x80, 1, 0}, 14u},
        {"length over the cap", {'B', 'R', 'K', 'Z', '1', 0, 0, 0, 0x7F}, 9u},
    };
    char out[64];
    usize n = 0u;
    ASSERT_EQ(break_runtime_metrics_decompress(good, sizeof good, out, sizeof out, &n),
              BREAK_RUNTIME_OK);
    for (usize i = 0u; i < sizeof bad / sizeof bad[0]; ++i) {
        n = 77u;
        memset(out, 0x33, sizeof out);
        if (break_runtime_metrics_decompress(bad[i].bytes, bad[i].len, out, sizeof out, &n) !=
            BREAK_RUNTIME_INVALID) {
            fprintf(stderr, "    accepted: %s\n", bad[i].why);
            ASSERT_TRUE(false);
        }
        ASSERT_EQ(n, 0u);
    }
    /* Every truncation of a valid stream is refused. Each cut is copied into
     * its own exact-size heap block, so reading one byte past the cut (a
     * literal that runs off the end, a half-read distance, a control byte the
     * stream does not have) is an out-of-bounds read under ASan. */
    for (usize cut = 0u; cut < sizeof good; ++cut) {
        u8 *exact = (u8 *)malloc(cut ? cut : 1u);
        ASSERT_NOT_NULL(exact);
        memcpy(exact, good, cut);
        ASSERT_EQ(break_runtime_metrics_decompress(exact, cut, out, sizeof out, &n),
                  BREAK_RUNTIME_INVALID);
        free(exact);
    }
    /* A valid stream followed by one more byte. */
    {
        u8 *longer = (u8 *)malloc(sizeof good + 1u);
        ASSERT_NOT_NULL(longer);
        memcpy(longer, good, sizeof good);
        longer[sizeof good] = 0x00u;
        ASSERT_EQ(break_runtime_metrics_decompress(longer, sizeof good + 1u, out, sizeof out, &n),
                  BREAK_RUNTIME_INVALID);
        free(longer);
    }
    /* A literal run that claims more bytes than the stream holds, with a
     * header length large enough that only the input bound can stop it. */
    {
        static const u8 shape[] = {'B', 'R', 'K', 'Z', '1', 64, 0, 0, 0, 0x3F, 'a', 'b'};
        u8 *exact = (u8 *)malloc(sizeof shape);
        ASSERT_NOT_NULL(exact);
        memcpy(exact, shape, sizeof shape);
        ASSERT_EQ(break_runtime_metrics_decompress(exact, sizeof shape, out, sizeof out, &n),
                  BREAK_RUNTIME_INVALID);
        free(exact);
    }
}

TEST(compress_never_reaches_further_back_than_the_window) {
    /* A distinctive 200-byte block, then 70000 bytes that never repeat it,
     * then the block again. The second copy is more than 65535 bytes after
     * the first, so it cannot be a match: a u16 distance would wrap and point
     * at the wrong bytes. */
    enum { k_block = 200, k_gap = 70000, k_total = k_block * 2 + k_gap };
    static u8 in[k_total];
    static u8 packed[BREAK_RUNTIME_METRICS_COMPRESS_BOUND(k_total)];
    static u8 back[k_total];
    usize packed_len;
    usize n = 0u;
    u32 s = 0xC0FFEEu;
    for (usize i = 0u; i < k_block; ++i) in[i] = (u8)('a' + i % 26u);
    for (usize i = k_block; i < k_block + k_gap; ++i) {
        s = s * 1664525u + 1013904223u;
        in[i] = (u8)(0x80u | (s >> 25)); /* high bytes never occur in the block */
    }
    memcpy(in + k_block + k_gap, in, k_block);
    packed_len = compress_into(in, sizeof in, packed, sizeof packed);
    ASSERT_TRUE(packed_len > 0u);
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, back, sizeof back, &n),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(n, sizeof in);
    ASSERT_TRUE(memcmp(back, in, sizeof in) == 0);
}

TEST(compress_writes_the_full_32_bit_length) {
    /* 16 MiB + 1 is above the input cap, so the largest legal input is used:
     * its length has a non-zero top byte (0x01000000), which a header that
     * dropped the high byte would store as 0. */
    const usize len = BREAK_RUNTIME_METRICS_COMPRESS_MAX_INPUT;
    u8 *in = (u8 *)malloc(len);
    u8 *packed = (u8 *)malloc(BREAK_RUNTIME_METRICS_COMPRESS_BOUND(len));
    u8 *back = (u8 *)malloc(len);
    usize packed_len = 0u;
    usize n = 0u;
    ASSERT_NOT_NULL(in);
    ASSERT_NOT_NULL(packed);
    ASSERT_NOT_NULL(back);
    memset(in, 'x', len);
    ASSERT_EQ(break_runtime_metrics_compress(in, len, packed, BREAK_RUNTIME_METRICS_COMPRESS_BOUND(len),
                                             &packed_len),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(packed[8], 0x01u);
    ASSERT_EQ(break_runtime_metrics_decompress(packed, packed_len, back, len, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, len);
    ASSERT_TRUE(memcmp(back, in, len) == 0);
    free(back);
    free(packed);
    free(in);
}

TEST(compression_validates_arguments) {
    u8 buf[32];
    usize n = 0u;
    ASSERT_EQ(break_runtime_metrics_compress("a", 1u, buf, sizeof buf, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_compress(NULL, 1u, buf, sizeof buf, &n), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_compress("a", 1u, NULL, 8u, &n), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_compress("a", BREAK_RUNTIME_METRICS_COMPRESS_MAX_INPUT + 1u,
                                             buf, sizeof buf, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_decompress(buf, 9u, buf, sizeof buf, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_decompress(NULL, 9u, buf, sizeof buf, &n),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_decompress(buf, 9u, NULL, 8u, &n), BREAK_RUNTIME_INVALID);
}

/* Per-channel retry router. Each FakeSender is one collector endpoint. */
static BreakRuntimeMetricsRetryRouter *make_router(FakeSender *metrics, FakeSender *alerts,
                                                   u32 metrics_max_attempts) {
    BreakRuntimeMetricsRetryChannelConfig ch[2];
    BreakRuntimeMetricsRetryRouterConfig cfg;
    BreakRuntimeMetricsRetryRouter *r = NULL;
    memset(ch, 0, sizeof(ch));
    memset(&cfg, 0, sizeof(cfg));
    ch[0].queue.capacity = 4u;
    ch[0].queue.max_payload_bytes = 32u;
    ch[0].send = fake_send;
    ch[0].user = metrics;
    ch[0].max_sends = 8u;
    ch[0].max_attempts = metrics_max_attempts;
    ch[0].backoff.base_us = 100u;
    ch[0].backoff.max_us = 1000u;
    ch[1] = ch[0];
    ch[1].user = alerts;
    ch[1].max_attempts = 0u;
    ch[1].backoff.base_us = 10u;
    ch[1].backoff.max_us = 10u;
    cfg.channels = ch;
    cfg.channel_count = 2u;
    return break_runtime_metrics_retry_router_create(&cfg, &r) == BREAK_RUNTIME_OK ? r : NULL;
}

TEST(router_routes_each_payload_to_its_own_channel_queue) {
    FakeSender m, a;
    BreakRuntimeMetricsRetryRouter *r;
    BreakRuntimeMetricsRetryRouterResult res;
    BreakRuntimeMetricsRetryStats st;
    memset(&m, 0, sizeof(m));
    memset(&a, 0, sizeof(a));
    r = make_router(&m, &a, 0u);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, "m1", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 1u, "a1", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, "m2", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 0u, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 2u);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 1u, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 0u, &res), BREAK_RUNTIME_OK);
    /* Each channel's payloads reach only that channel's sender, in order. */
    ASSERT_EQ(m.calls, 2u);
    ASSERT_STR_EQ(m.seen[0], "m1");
    ASSERT_STR_EQ(m.seen[1], "m2");
    ASSERT_EQ(a.calls, 1u);
    ASSERT_STR_EQ(a.seen[0], "a1");
    ASSERT_EQ(res.delivered, 3u);
    ASSERT_EQ(res.failed, 0u);
    ASSERT_EQ(res.deferred_channels, 0u);
    break_runtime_metrics_retry_router_destroy(r);
}

TEST(router_a_failing_channel_does_not_block_the_others) {
    FakeSender m, a;
    BreakRuntimeMetricsRetryRouter *r;
    BreakRuntimeMetricsRetryRouterResult res;
    BreakRuntimeMetricsRetryStats st;
    memset(&m, 0, sizeof(m));
    memset(&a, 0, sizeof(a));
    m.always_fail = true; /* the metrics collector is down */
    r = make_router(&m, &a, 0u);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, "m1", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, "m2", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 1u, "a1", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 1u, "a2", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 0u, &res), BREAK_RUNTIME_OK);
    /* The dead channel stops after one failed try; the healthy one still
     * delivers its whole backlog in the same call. */
    ASSERT_EQ(m.calls, 1u);
    ASSERT_EQ(a.calls, 2u);
    ASSERT_EQ(res.delivered, 2u);
    ASSERT_EQ(res.failed, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 0u, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 2u);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 1u, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 0u);
    /* New alerts keep flowing while metrics stays down. */
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 1u, "a3", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 50u, &res), BREAK_RUNTIME_OK);
    ASSERT_EQ(a.calls, 3u);
    ASSERT_STR_EQ(a.seen[2], "a3");
    /* metrics is still inside its 100 us backoff, so it was not retried. */
    ASSERT_EQ(m.calls, 1u);
    ASSERT_EQ(res.deferred_channels, 1u);
    break_runtime_metrics_retry_router_destroy(r);
}

TEST(router_applies_each_channels_own_backoff_and_attempt_limit) {
    FakeSender m, a;
    BreakRuntimeMetricsRetryRouter *r;
    BreakRuntimeMetricsRetryRouterResult res;
    BreakRuntimeMetricsRetryStats st;
    memset(&m, 0, sizeof(m));
    memset(&a, 0, sizeof(a));
    m.always_fail = true;
    a.always_fail = true;
    r = make_router(&m, &a, 2u); /* metrics gives up after 2 attempts */
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, "m1", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 1u, "a1", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 0u, &res), BREAK_RUNTIME_OK);
    ASSERT_EQ(m.calls, 1u);
    ASSERT_EQ(a.calls, 1u);
    /* At t=10 only alerts (10 us backoff) is due; metrics (100 us) is not. */
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 10u, &res), BREAK_RUNTIME_OK);
    ASSERT_EQ(m.calls, 1u);
    ASSERT_EQ(a.calls, 2u);
    ASSERT_EQ(res.deferred_channels, 1u);
    /* At t=100 metrics retries and hits its own limit; alerts never gives up. */
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 100u, &res), BREAK_RUNTIME_OK);
    ASSERT_EQ(m.calls, 2u);
    ASSERT_EQ(res.abandoned, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 0u, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 0u);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 1u, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 1u);
    break_runtime_metrics_retry_router_destroy(r);
}

TEST(router_reports_the_earliest_due_channel) {
    FakeSender m, a;
    BreakRuntimeMetricsRetryRouter *r;
    BreakRuntimeMetricsRetryRouterResult res;
    u64 due = 0u;
    memset(&m, 0, sizeof(m));
    memset(&a, 0, sizeof(a));
    m.always_fail = true;
    a.always_fail = true;
    r = make_router(&m, &a, 0u);
    ASSERT_NOT_NULL(r);
    /* Nothing queued anywhere: nothing is due. */
    ASSERT_EQ(break_runtime_metrics_retry_router_next_due(r, &due), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, "m1", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 1u, "a1", 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_next_due(r, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 0u);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 1000u, &res), BREAK_RUNTIME_OK);
    /* metrics is due at 1100, alerts at 1010: the router reports the minimum,
     * so an owner can sleep exactly until the next channel needs work. */
    ASSERT_EQ(break_runtime_metrics_retry_router_next_due(r, &due), BREAK_RUNTIME_OK);
    ASSERT_EQ(due, 1010u);
    break_runtime_metrics_retry_router_destroy(r);
}

/* A send that re-enters the router's drain. The inner drain reaches this
 * channel's queue while its outer drain still holds a borrowed slot, so that
 * queue reports REJECTED; the other channel is idle and drains normally. */
static BreakRuntimeMetricsRetryRouter *g_router_reentry;
static BreakRuntimeError g_router_inner;
static u32 g_router_inner_calls;

static BreakRuntimeError router_reentrant_send(void *user, const void *bytes, usize len) {
    BreakRuntimeMetricsRetryRouterResult inner;
    (void)user;
    (void)bytes;
    (void)len;
    if (g_router_inner_calls++ == 0u)
        g_router_inner = break_runtime_metrics_retry_router_drain(g_router_reentry, 0u, &inner);
    return BREAK_RUNTIME_OK;
}

TEST(router_reports_a_channel_error_without_skipping_later_channels) {
    FakeSender later;
    BreakRuntimeMetricsRetryChannelConfig ch[2];
    BreakRuntimeMetricsRetryRouterConfig cfg;
    BreakRuntimeMetricsRetryRouter *r = NULL;
    BreakRuntimeMetricsRetryRouterResult res;
    memset(&later, 0, sizeof(later));
    memset(ch, 0, sizeof(ch));
    ch[0].queue.capacity = 2u;
    ch[0].queue.max_payload_bytes = 8u;
    ch[0].send = router_reentrant_send;
    ch[0].max_sends = 1u;
    ch[0].backoff.base_us = 1u;
    ch[0].backoff.max_us = 1u;
    ch[1] = ch[0];
    ch[1].send = fake_send;
    ch[1].user = &later;
    memset(&cfg, 0, sizeof(cfg));
    cfg.channels = ch;
    cfg.channel_count = 2u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_OK);
    g_router_reentry = r;
    g_router_inner = BREAK_RUNTIME_OK;
    g_router_inner_calls = 0u;
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, "a", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 1u, "b", 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 0u, &res), BREAK_RUNTIME_OK);
    /* Inside the callback: channel 0 is mid-send and refuses, yet channel 1
     * is still drained by that same inner call, and the refusal is reported
     * once every channel has had its turn. */
    ASSERT_EQ(g_router_inner, BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(later.calls, 1u);
    ASSERT_STR_EQ(later.seen[0], "b");
    g_router_reentry = NULL;
    break_runtime_metrics_retry_router_destroy(r);
}

TEST(router_accepts_exactly_the_maximum_channel_count) {
    FakeSender f;
    BreakRuntimeMetricsRetryChannelConfig ch[BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS + 1u];
    BreakRuntimeMetricsRetryRouterConfig cfg;
    BreakRuntimeMetricsRetryRouter *r = NULL;
    BreakRuntimeMetricsRetryStats st;
    memset(&f, 0, sizeof(f));
    memset(ch, 0, sizeof(ch));
    for (u32 i = 0u; i <= BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS; ++i) {
        ch[i].queue.capacity = 1u;
        ch[i].queue.max_payload_bytes = 4u;
        ch[i].send = fake_send;
        ch[i].user = &f;
        ch[i].max_sends = 1u;
        ch[i].backoff.base_us = 1u;
        ch[i].backoff.max_us = 1u;
    }
    memset(&cfg, 0, sizeof(cfg));
    cfg.channels = ch;
    cfg.channel_count = BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_OK);
    /* The last configured channel is usable; one past it is refused by both
     * enqueue and stats, so neither can index outside the channel table. */
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(
                  r, BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS - 1u, "x", 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS,
                                                         "x", 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS,
                                                       &st),
              BREAK_RUNTIME_INVALID);
    break_runtime_metrics_retry_router_destroy(r);
    r = NULL;
    cfg.channel_count = BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS + 1u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(r == NULL);
}

TEST(router_validates_its_configuration) {
    FakeSender f;
    BreakRuntimeMetricsRetryChannelConfig ch[2];
    BreakRuntimeMetricsRetryRouterConfig cfg;
    BreakRuntimeMetricsRetryRouter *r = (BreakRuntimeMetricsRetryRouter *)&f;
    memset(&f, 0, sizeof(f));
    memset(ch, 0, sizeof(ch));
    ch[0].queue.capacity = 2u;
    ch[0].queue.max_payload_bytes = 8u;
    ch[0].send = fake_send;
    ch[0].user = &f;
    ch[0].max_sends = 1u;
    ch[0].backoff.base_us = 1u;
    ch[0].backoff.max_us = 1u;
    ch[1] = ch[0];
    memset(&cfg, 0, sizeof(cfg));
    cfg.channels = ch;
    cfg.channel_count = 2u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(NULL, &r), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(r == NULL);
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, NULL), BREAK_RUNTIME_INVALID);
    cfg.channel_count = 0u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    cfg.channel_count = BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS + 1u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    cfg.channel_count = 2u;
    cfg.channels = NULL;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    cfg.channels = ch;
    ch[1].send = NULL;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    ch[1].send = fake_send;
    ch[1].max_sends = 0u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    ch[1].max_sends = 1u;
    ch[1].backoff.base_us = 0u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    ch[1].backoff.base_us = 5u; /* max_us (1) below base_us */
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    ch[1].backoff.base_us = 1u;
    ch[1].queue.capacity = 0u; /* a bad queue config in the second channel */
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(r == NULL);
    ch[1].queue.capacity = 2u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(r);
    break_runtime_metrics_retry_router_destroy(r);
    break_runtime_metrics_retry_router_destroy(NULL);
}

TEST(router_validates_call_arguments) {
    FakeSender m, a;
    BreakRuntimeMetricsRetryRouter *r;
    BreakRuntimeMetricsRetryRouterResult res;
    BreakRuntimeMetricsRetryStats st;
    u64 due = 0u;
    memset(&m, 0, sizeof(m));
    memset(&a, 0, sizeof(a));
    r = make_router(&m, &a, 0u);
    ASSERT_NOT_NULL(r);
    /* A channel index outside the configured set is refused, not clamped. */
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 2u, "x", 1u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 2u, &st), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(NULL, 0u, "x", 1u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, NULL, 1u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(NULL, 0u, &res), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 0u, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(NULL, 0u, &st), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 0u, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_next_due(NULL, &due), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_router_next_due(r, NULL), BREAK_RUNTIME_INVALID);
    /* A payload larger than the channel's slot is the queue's INVALID. */
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(
                  r, 0u, "0123456789012345678901234567890123", 34u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(m.calls + a.calls, 0u);
    break_runtime_metrics_retry_router_destroy(r);
}

TEST(retry_persist_validates_arguments_and_ownership_rules) {
    BreakRuntimeMetricsRetryQueue *q = make_retry(2u, 8u);
    u8 blob[64];
    usize len = 0u;
    u32 loaded = 0u;
    ASSERT_NOT_NULL(q);
    ASSERT_EQ(break_runtime_metrics_retry_save(NULL, blob, sizeof blob, &len),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_save(q, blob, sizeof blob, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_save(q, NULL, 8u, &len), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_load(NULL, blob, 4u, &loaded), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_load(q, NULL, 4u, &loaded), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_retry_load(q, blob, 4u, NULL), BREAK_RUNTIME_INVALID);
    /* Not an image at all. */
    memset(blob, 0, sizeof blob);
    ASSERT_EQ(break_runtime_metrics_retry_load(q, blob, sizeof blob, &loaded),
              BREAK_RUNTIME_INVALID);
    break_runtime_metrics_retry_destroy(q);
}

TEST(history_aggregate_reports_window_min_max_mean) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    u64 lo = 0u, hi = 0u, mean = 0u;
    u32 counted = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    /* A gauge that moves 4 -> 10 -> 7 over three frames. */
    ASSERT_EQ(break_runtime_metrics_set(m, "q.depth", BREAK_RUNTIME_METRIC_GAUGE, 4u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 10u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "q.depth", BREAK_RUNTIME_METRIC_GAUGE, 10u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 20u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "q.depth", BREAK_RUNTIME_METRIC_GAUGE, 7u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 30u), BREAK_RUNTIME_OK);
    /* Window of 3: min 4, max 10, mean (4+10+7)/3 = 7 (truncated). */
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "q.depth", 3u, &lo, &hi, &mean, &counted),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(lo, 4u);
    ASSERT_EQ(hi, 10u);
    ASSERT_EQ(mean, 7u);
    ASSERT_EQ(counted, 3u);
    /* Window of 2 (newest two: 10, 7): min 7, max 10, mean 8 (truncated). */
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "q.depth", 2u, &lo, &hi, &mean, &counted),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(lo, 7u);
    ASSERT_EQ(hi, 10u);
    ASSERT_EQ(mean, 8u);
    ASSERT_EQ(counted, 2u);
    /* NULL outs are allowed. */
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "q.depth", 1u, NULL, NULL, NULL, NULL),
              BREAK_RUNTIME_OK);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(history_aggregate_counts_only_present_frames) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    u64 lo = 9u, hi = 9u, mean = 9u;
    u32 counted = 9u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    /* Frame 0: only "other". Frame 1 & 2: "late" appears at 5 then 15. */
    ASSERT_EQ(break_runtime_metrics_set(m, "other", BREAK_RUNTIME_METRIC_GAUGE, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 10u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "late", BREAK_RUNTIME_METRIC_GAUGE, 5u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 20u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "late", BREAK_RUNTIME_METRIC_GAUGE, 15u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 30u), BREAK_RUNTIME_OK);
    /* Window of 3 but "late" is only in the newest two frames. */
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "late", 3u, &lo, &hi, &mean, &counted),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(lo, 5u);
    ASSERT_EQ(hi, 15u);
    ASSERT_EQ(mean, 10u);
    ASSERT_EQ(counted, 2u);
    /* Absent from every frame in the window -> STALE, outputs untouched. */
    lo = hi = mean = 123u; counted = 123u;
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "ghost", 3u, &lo, &hi, &mean, &counted),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(lo, 123u);
    ASSERT_EQ(counted, 123u);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(history_aggregate_sum_saturates_without_overflow) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    u64 lo = 0u, hi = 0u, mean = 0u;
    u32 counted = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    /* Frame 0 = UINT64_MAX, frame 1 = 2. A plain running sum would wrap to 1
     * (mean 0); saturation clamps the sum to UINT64_MAX (mean UINT64_MAX/2).
     * The two outcomes differ, so this pins the saturation branch. */
    ASSERT_EQ(break_runtime_metrics_set(m, "big", BREAK_RUNTIME_METRIC_GAUGE, UINT64_MAX),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 10u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_set(m, "big", BREAK_RUNTIME_METRIC_GAUGE, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 20u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "big", 2u, &lo, &hi, &mean, &counted),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(lo, 2u);
    ASSERT_EQ(hi, UINT64_MAX);
    ASSERT_EQ(mean, UINT64_MAX / 2u);
    ASSERT_EQ(counted, 2u);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

static void record_gauge_frames(BreakRuntimeMetrics *m, BreakRuntimeMetricsHistory *h,
                                const char *name, const u64 *values, u32 n) {
    for (u32 i = 0u; i < n; ++i) {
        ASSERT_EQ(break_runtime_metrics_set(m, name, BREAK_RUNTIME_METRIC_GAUGE, values[i]),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_metrics_history_record(h, m, 10u * (i + 1u)), BREAK_RUNTIME_OK);
    }
}

TEST(aggregate_alerts_pick_the_requested_stat) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    static const u64 values[] = {2u, 20u, 2u}; /* min 2, max 20, mean 8 */
    BreakRuntimeMetricAlertRule rules[3] = {
        {"lat", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u},
        {"lat", BREAK_RUNTIME_METRIC_ALERT_BELOW, 5u},
        {"lat", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 10u}, /* only MAX crosses 10 */
    };
    u32 fired[3] = {9u, 9u, 9u};
    u32 count = 9u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    record_gauge_frames(m, h, "lat", values, 3u);
    /* MIN 2: only BELOW 5 fires. */
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 3u, 3u, BREAK_RUNTIME_METRIC_AGGREGATE_MIN, fired, 3u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(fired[0], 1u);
    /* MAX 20: ABOVE 5 and ABOVE 10 fire. */
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 3u, 3u, BREAK_RUNTIME_METRIC_AGGREGATE_MAX, fired, 3u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(fired[0], 0u);
    ASSERT_EQ(fired[1], 2u);
    /* MEAN 8: only ABOVE 5 fires (8 is not above 10). */
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 3u, 3u, BREAK_RUNTIME_METRIC_AGGREGATE_MEAN, fired, 3u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(fired[0], 0u);
    /* Window 1 (newest = 2): MEAN 2 -> only BELOW fires. */
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 3u, 1u, BREAK_RUNTIME_METRIC_AGGREGATE_MEAN, fired, 3u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(fired[0], 1u);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(aggregate_alerts_threshold_is_strict_and_unproven_never_fires) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    static const u64 values[] = {5u, 5u};
    BreakRuntimeMetricAlertRule rules[3] = {
        {"lat", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u},
        {"lat", BREAK_RUNTIME_METRIC_ALERT_BELOW, 5u},
        {"ghost", BREAK_RUNTIME_METRIC_ALERT_BELOW, 100u},
    };
    u32 fired[3] = {0u, 0u, 0u};
    u32 count = 9u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    record_gauge_frames(m, h, "lat", values, 2u);
    /* Value equal to threshold fires neither; absent name never fires. */
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 3u, 2u, BREAK_RUNTIME_METRIC_AGGREGATE_MEAN, fired, 3u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 0u);
    /* Window longer than retained frames: nothing fires, not an error. */
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 3u, 3u, BREAK_RUNTIME_METRIC_AGGREGATE_MIN, fired, 3u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 0u);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(aggregate_alerts_overload_and_validation) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    static const u64 values[] = {50u};
    BreakRuntimeMetricAlertRule rules[2] = {
        {"lat", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 1u},
        {"lat", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 2u},
    };
    BreakRuntimeMetricAlertRule bad_name = {NULL, BREAK_RUNTIME_METRIC_ALERT_ABOVE, 1u};
    BreakRuntimeMetricAlertRule bad_op = {"lat", (BreakRuntimeMetricAlertOp)7, 1u};
    u32 fired[2] = {77u, 77u};
    u32 count = 9u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    record_gauge_frames(m, h, "lat", values, 1u);
    /* Two firing rules but room for one -> OVERLOAD with the required count. */
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 2u, 1u, BREAK_RUNTIME_METRIC_AGGREGATE_MAX, fired, 1u, &count),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(fired[0], 77u);
    count = 9u;
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  NULL, rules, 2u, 1u, BREAK_RUNTIME_METRIC_AGGREGATE_MAX, fired, 2u, &count),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 2u, 0u, BREAK_RUNTIME_METRIC_AGGREGATE_MAX, fired, 2u, &count),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 2u, BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH + 1u,
                  BREAK_RUNTIME_METRIC_AGGREGATE_MAX, fired, 2u, &count),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 2u, 1u, (BreakRuntimeMetricAggregateStat)9, fired, 2u, &count),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, &bad_name, 1u, 1u, BREAK_RUNTIME_METRIC_AGGREGATE_MAX, fired, 2u, &count),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, &bad_op, 1u, 1u, BREAK_RUNTIME_METRIC_AGGREGATE_MAX, fired, 2u, &count),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_evaluate_aggregate_alerts(
                  h, rules, 2u, 1u, BREAK_RUNTIME_METRIC_AGGREGATE_MAX, fired, 2u, NULL),
              BREAK_RUNTIME_INVALID);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

static BreakRuntimeMetricAlertEdge aggregate_edge_after(BreakRuntimeMetrics *m,
                                                        BreakRuntimeMetricsHistory *h,
                                                        const BreakRuntimeMetricAlertRule *rule,
                                                        BreakRuntimeMetricAggregateStat stat,
                                                        u64 value, u64 tick) {
    BreakRuntimeMetricAlertEdge edge = (BreakRuntimeMetricAlertEdge)99;
    if (break_runtime_metrics_set(m, "lat", BREAK_RUNTIME_METRIC_GAUGE, value) !=
            BREAK_RUNTIME_OK ||
        break_runtime_metrics_history_record(h, m, tick) != BREAK_RUNTIME_OK ||
        break_runtime_metrics_history_aggregate_alert_edges(h, rule, 1u, 2u, stat, &edge, 1u) !=
            BREAK_RUNTIME_OK)
        return (BreakRuntimeMetricAlertEdge)98;
    return edge;
}

TEST(aggregate_alert_edges_report_each_transition_once) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    const BreakRuntimeMetricAlertRule rule = {"lat", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 10u};
    const BreakRuntimeMetricAggregateStat mean = BREAK_RUNTIME_METRIC_AGGREGATE_MEAN;
    BreakRuntimeMetricAlertEdge edge = (BreakRuntimeMetricAlertEdge)99;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    /* Window 2 of the mean, rule ABOVE 10. One frame: unproven -> STEADY. */
    ASSERT_EQ(aggregate_edge_after(m, h, &rule, mean, 4u, 10u), BREAK_RUNTIME_METRIC_ALERT_STEADY);
    /* (4,30) mean 17 fires; the previous window is unproven -> RAISED. */
    ASSERT_EQ(aggregate_edge_after(m, h, &rule, mean, 30u, 20u), BREAK_RUNTIME_METRIC_ALERT_RAISED);
    /* The stat matters: the min of (4,30) is 4, which does not fire. */
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(
                  h, &rule, 1u, 2u, BREAK_RUNTIME_METRIC_AGGREGATE_MIN, &edge, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(edge, BREAK_RUNTIME_METRIC_ALERT_STEADY);
    /* (30,30) and (30,0) mean 15 keep firing -> STEADY. */
    ASSERT_EQ(aggregate_edge_after(m, h, &rule, mean, 30u, 30u), BREAK_RUNTIME_METRIC_ALERT_STEADY);
    ASSERT_EQ(aggregate_edge_after(m, h, &rule, mean, 0u, 40u), BREAK_RUNTIME_METRIC_ALERT_STEADY);
    /* (0,0) after a firing (30,0): CLEARED, then STEADY while quiet. The ring
     * is full here, so the previous window is read from retained frames. */
    ASSERT_EQ(aggregate_edge_after(m, h, &rule, mean, 0u, 50u), BREAK_RUNTIME_METRIC_ALERT_CLEARED);
    ASSERT_EQ(aggregate_edge_after(m, h, &rule, mean, 0u, 60u), BREAK_RUNTIME_METRIC_ALERT_STEADY);
    break_runtime_metrics_history_destroy(h);
    /* A firing first frame: the previous window (one retained frame for a
     * window of 2) is unproven, so it must not count as firing and the
     * newest full window reports RAISED rather than STEADY. */
    h = make_history(4u, 4u);
    ASSERT_NOT_NULL(h);
    ASSERT_EQ(aggregate_edge_after(m, h, &rule, mean, 30u, 10u), BREAK_RUNTIME_METRIC_ALERT_STEADY);
    ASSERT_EQ(aggregate_edge_after(m, h, &rule, mean, 30u, 20u), BREAK_RUNTIME_METRIC_ALERT_RAISED);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(aggregate_alert_edges_validation_leaves_edges_untouched) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    static const u64 values[] = {50u, 50u};
    BreakRuntimeMetricAlertRule rules[2] = {
        {"lat", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 1u},
        {"ghost", BREAK_RUNTIME_METRIC_ALERT_BELOW, 100u},
    };
    BreakRuntimeMetricAlertRule bad_name = {NULL, BREAK_RUNTIME_METRIC_ALERT_ABOVE, 1u};
    BreakRuntimeMetricAlertRule bad_op = {"lat", (BreakRuntimeMetricAlertOp)7, 1u};
    BreakRuntimeMetricAlertEdge edges[2] = {(BreakRuntimeMetricAlertEdge)77,
                                            (BreakRuntimeMetricAlertEdge)77};
    const BreakRuntimeMetricAggregateStat max = BREAK_RUNTIME_METRIC_AGGREGATE_MAX;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    record_gauge_frames(m, h, "lat", values, 2u);
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(h, rules, 2u, 1u, max, edges, 1u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(NULL, rules, 2u, 1u, max, edges,
                                                                   2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(h, rules, 2u, 0u, max, edges, 2u),
              BREAK_RUNTIME_INVALID);
    /* window must stay below the depth (4) so the previous window is provable. */
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(h, rules, 2u, 4u, max, edges, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(
                  h, rules, 2u, 1u, (BreakRuntimeMetricAggregateStat)9, edges, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(h, &bad_name, 1u, 1u, max,
                                                                   edges, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(h, &bad_op, 1u, 1u, max, edges,
                                                                   2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(h, rules, 2u, 1u, max, NULL, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(edges[0], (BreakRuntimeMetricAlertEdge)77);
    ASSERT_EQ(edges[1], (BreakRuntimeMetricAlertEdge)77);
    /* Valid: window 3 exceeds the 2 retained frames -> unproven, STEADY; the
     * absent name is STEADY too. */
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(h, rules, 2u, 3u, max, edges, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(edges[0], BREAK_RUNTIME_METRIC_ALERT_STEADY);
    ASSERT_EQ(edges[1], BREAK_RUNTIME_METRIC_ALERT_STEADY);
    /* Zero rules is valid and writes nothing. */
    ASSERT_EQ(break_runtime_metrics_history_aggregate_alert_edges(h, NULL, 0u, 1u, max, NULL, 0u),
              BREAK_RUNTIME_OK);
    break_runtime_metrics_history_destroy(h);
    break_runtime_metrics_destroy(m);
}

TEST(history_aggregate_validates_arguments) {
    BreakRuntimeMetrics *m = make_metrics(8u);
    BreakRuntimeMetricsHistory *h = make_history(4u, 4u);
    u64 lo = 0u;
    ASSERT_NOT_NULL(m);
    ASSERT_NOT_NULL(h);
    /* Empty history -> STALE. */
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "x", 1u, &lo, NULL, NULL, NULL),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_metrics_set(m, "x", BREAK_RUNTIME_METRIC_GAUGE, 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_history_record(h, m, 10u), BREAK_RUNTIME_OK);
    /* window beyond retained frames -> STALE. */
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "x", 2u, &lo, NULL, NULL, NULL),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_metrics_history_aggregate(NULL, "x", 1u, &lo, NULL, NULL, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, NULL, 1u, &lo, NULL, NULL, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_history_aggregate(h, "x", 0u, &lo, NULL, NULL, NULL),
              BREAK_RUNTIME_INVALID);
    break_runtime_metrics_history_destroy(h);
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
    RUN_TEST(history_create_validates_config);
    RUN_TEST(history_records_frames_newest_first_and_evicts_oldest);
    RUN_TEST(history_rejects_non_increasing_ticks_and_wide_snapshots);
    RUN_TEST(history_frame_reports_required_count_when_too_small);
    RUN_TEST(sustained_alerts_require_every_recent_frame_to_fire);
    RUN_TEST(sustained_alerts_validate_arguments);
    RUN_TEST(sustain_longer_than_the_ring_never_fires);
    RUN_TEST(alert_edges_report_raise_and_clear_between_consecutive_windows);
    RUN_TEST(alert_edges_validate_arguments);
    RUN_TEST(history_delta_measures_counter_growth_over_a_window);
    RUN_TEST(history_aggregate_reports_window_min_max_mean);
    RUN_TEST(history_aggregate_counts_only_present_frames);
    RUN_TEST(history_aggregate_sum_saturates_without_overflow);
    RUN_TEST(history_aggregate_validates_arguments);
    RUN_TEST(aggregate_alerts_pick_the_requested_stat);
    RUN_TEST(aggregate_alerts_threshold_is_strict_and_unproven_never_fires);
    RUN_TEST(aggregate_alerts_overload_and_validation);
    RUN_TEST(aggregate_alert_edges_report_each_transition_once);
    RUN_TEST(aggregate_alert_edges_validation_leaves_edges_untouched);
    RUN_TEST(history_delta_rejects_gauges_and_bad_arguments);
    RUN_TEST(decode_round_trips_the_encoding);
    RUN_TEST(decode_rejects_malformed_input_as_a_whole);
    RUN_TEST(decode_accepts_boundary_values_and_reports_required_count);
    RUN_TEST(alert_edge_encoding_lists_only_transitions_in_rule_order);
    RUN_TEST(alert_edge_encoding_reports_required_length_and_validates);
    RUN_TEST(retry_queue_is_fifo_and_release_advances);
    RUN_TEST(retry_queue_full_drops_the_oldest_entry);
    RUN_TEST(retry_queue_counts_attempts_per_entry);
    RUN_TEST(retry_queue_validates_configuration_and_payloads);
    RUN_TEST(retry_queue_round_trips_a_real_metrics_encoding);
    RUN_TEST(retry_drain_delivers_in_order_within_the_send_budget);
    RUN_TEST(retry_drain_stops_on_failure_and_keeps_the_entry);
    RUN_TEST(retry_drain_abandons_a_poison_payload_at_max_attempts);
    RUN_TEST(retry_drain_validates_arguments);
    RUN_TEST(retry_coalesces_repeats_of_the_newest_payload);
    RUN_TEST(retry_coalescing_compares_only_the_newest_entry);
    RUN_TEST(retry_without_coalescing_keeps_every_repeat);
    RUN_TEST(retry_rejects_enqueue_reentered_from_a_send_callback);
    RUN_TEST(retry_timed_drain_waits_for_the_exponential_backoff_deadline);
    RUN_TEST(retry_timed_drain_caps_the_delay_and_resets_it_on_success);
    RUN_TEST(retry_timed_drain_does_not_overflow_a_huge_attempt_count);
    RUN_TEST(retry_timed_drain_saturates_the_shift_for_a_large_attempt_count);
    RUN_TEST(retry_reused_slot_starts_with_no_deadline);
    RUN_TEST(retry_timed_drain_validates_arguments);
    RUN_TEST(retry_untimed_drain_ignores_any_backoff_deadline);
    RUN_TEST(merge_keeps_the_newest_value_per_name_in_first_seen_order);
    RUN_TEST(merge_output_is_strictly_decodable_and_round_trips_encode);
    RUN_TEST(merge_rejects_a_kind_change_and_any_malformed_input_as_a_whole);
    RUN_TEST(merge_reports_the_required_size_and_handles_empty_documents);
    RUN_TEST(merge_validates_arguments);
    RUN_TEST(merge_rejects_more_distinct_names_than_one_document_may_hold);
    RUN_TEST(retry_save_then_load_restores_payloads_attempts_and_order);
    RUN_TEST(retry_save_reports_the_required_size);
    RUN_TEST(retry_load_into_a_smaller_queue_keeps_the_newest_entries);
    RUN_TEST(retry_load_rejects_corruption_as_a_whole);
    RUN_TEST(retry_load_rejects_an_entry_larger_than_the_queue_slot);
    RUN_TEST(retry_load_checks_magic_and_framing_behind_a_valid_checksum);
    RUN_TEST(retry_load_restores_repeats_even_into_a_coalescing_queue);
    RUN_TEST(retry_load_is_refused_from_inside_a_drain_callback);
    RUN_TEST(retry_persist_validates_arguments_and_ownership_rules);
    RUN_TEST(compress_round_trips_an_encoded_registry_and_shrinks_it);
    RUN_TEST(compress_handles_incompressible_and_highly_repetitive_input);
    RUN_TEST(compress_and_decompress_report_the_required_size);
    RUN_TEST(decompress_accepts_hand_built_streams_at_the_limits);
    RUN_TEST(decompress_rejects_malformed_streams);
    RUN_TEST(compress_never_reaches_further_back_than_the_window);
    RUN_TEST(compress_writes_the_full_32_bit_length);
    RUN_TEST(compression_validates_arguments);
    RUN_TEST(router_routes_each_payload_to_its_own_channel_queue);
    RUN_TEST(router_a_failing_channel_does_not_block_the_others);
    RUN_TEST(router_applies_each_channels_own_backoff_and_attempt_limit);
    RUN_TEST(router_reports_the_earliest_due_channel);
    RUN_TEST(router_reports_a_channel_error_without_skipping_later_channels);
    RUN_TEST(router_accepts_exactly_the_maximum_channel_count);
    RUN_TEST(router_validates_its_configuration);
    RUN_TEST(router_validates_call_arguments);
TEST_MAIN_END()
