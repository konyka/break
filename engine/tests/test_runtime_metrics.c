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
TEST_MAIN_END()
