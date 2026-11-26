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
    RUN_TEST(history_delta_rejects_gauges_and_bad_arguments);
    RUN_TEST(decode_round_trips_the_encoding);
    RUN_TEST(decode_rejects_malformed_input_as_a_whole);
    RUN_TEST(decode_accepts_boundary_values_and_reports_required_count);
TEST_MAIN_END()
