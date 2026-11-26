#include <runtime/runtime_metrics.h>

#include <core/platform_thread.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Process-local metrics registry (design: docs/design/runtime_metrics.md).
 * One mutex guards the slot table; add()/set() never allocate and never wait,
 * so a hot path recording a counter cannot block. The mutex is a leaf: the
 * registry calls into no runtime subsystem while holding it. Slots are never
 * removed, so a name's index is stable once created. */

typedef struct RuntimeMetricSlot {
    char name[BREAK_RUNTIME_METRICS_NAME_CAPACITY];
    BreakRuntimeMetricKind kind;
    u64 value;
} RuntimeMetricSlot;

struct BreakRuntimeMetrics {
    PlatformMutex mutex;
    RuntimeMetricSlot *slots; /* bounded table, creation order */
    u32 capacity;
    u32 count;
    PlatformThreadId owner; /* snapshot/encode caller (create caller) */
    bool closed;
    /* stats (all under mutex) */
    u64 updates;
    u64 overflow_drops;
    u64 saturations;
    u64 closed_rejects;
};

static bool metrics_name_valid(const char *name, usize *out_len) {
    usize i;
    if (!name || name[0] == '\0') return false;
    for (i = 0u; name[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)name[i];
        if (i + 1u >= BREAK_RUNTIME_METRICS_NAME_CAPACITY) return false;
        /* No whitespace or low control bytes: the text encoding is
         * space-delimited and one metric per line, so the name must not
         * contain a space, a newline, or any byte at or below 0x20. */
        if (c <= ' ') return false;
    }
    if (out_len) *out_len = i;
    return true;
}

BreakRuntimeError break_runtime_metrics_create(
    const BreakRuntimeMetricsConfig *config,
    BreakRuntimeMetrics **out) {
    BreakRuntimeMetrics *metrics;
    u32 capacity;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    capacity = config && config->capacity != 0u ? config->capacity
                                                 : BREAK_RUNTIME_METRICS_DEFAULT_CAPACITY;
    if (capacity > BREAK_RUNTIME_METRICS_MAX_CAPACITY) return BREAK_RUNTIME_INVALID;
    metrics = (BreakRuntimeMetrics *)calloc(1u, sizeof(*metrics));
    if (!metrics) return BREAK_RUNTIME_OOM;
    metrics->slots = (RuntimeMetricSlot *)calloc(capacity, sizeof(*metrics->slots));
    if (!metrics->slots) {
        free(metrics);
        return BREAK_RUNTIME_OOM;
    }
    platform_mutex_init(&metrics->mutex);
    metrics->capacity = capacity;
    metrics->count = 0u;
    metrics->owner = platform_thread_current_id();
    metrics->closed = false;
    *out = metrics;
    return BREAK_RUNTIME_OK;
}

void break_runtime_metrics_close(BreakRuntimeMetrics *metrics) {
    if (!metrics) return;
    platform_mutex_lock(&metrics->mutex);
    metrics->closed = true;
    platform_mutex_unlock(&metrics->mutex);
}

void break_runtime_metrics_destroy(BreakRuntimeMetrics *metrics) {
    if (!metrics) return;
    platform_mutex_destroy(&metrics->mutex);
    free(metrics->slots);
    free(metrics);
}

/* Locates the slot for `name`, creating it when absent. Returns NULL and sets
 * *out_err when the kind disagrees, the name is invalid, or the table is full.
 * Caller holds the mutex. */
static RuntimeMetricSlot *metrics_slot_for(BreakRuntimeMetrics *metrics, const char *name,
                                           BreakRuntimeMetricKind kind,
                                           BreakRuntimeError *out_err) {
    usize len = 0u;
    u32 i;
    if (!metrics_name_valid(name, &len)) {
        *out_err = BREAK_RUNTIME_INVALID;
        return NULL;
    }
    for (i = 0u; i < metrics->count; ++i) {
        if (strcmp(metrics->slots[i].name, name) == 0) {
            if (metrics->slots[i].kind != kind) {
                *out_err = BREAK_RUNTIME_INVALID;
                return NULL;
            }
            return &metrics->slots[i];
        }
    }
    if (metrics->count == metrics->capacity) {
        metrics->overflow_drops++;
        *out_err = BREAK_RUNTIME_OVERLOAD;
        return NULL;
    }
    {
        RuntimeMetricSlot *slot = &metrics->slots[metrics->count++];
        memcpy(slot->name, name, len + 1u);
        slot->kind = kind;
        slot->value = 0u;
        return slot;
    }
}

BreakRuntimeError break_runtime_metrics_add(
    BreakRuntimeMetrics *metrics,
    const char *name,
    BreakRuntimeMetricKind kind,
    u64 delta) {
    BreakRuntimeError err = BREAK_RUNTIME_OK;
    RuntimeMetricSlot *slot;
    if (!metrics || kind != BREAK_RUNTIME_METRIC_COUNTER) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&metrics->mutex);
    if (metrics->closed) {
        metrics->closed_rejects++;
        platform_mutex_unlock(&metrics->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    slot = metrics_slot_for(metrics, name, kind, &err);
    if (!slot) {
        platform_mutex_unlock(&metrics->mutex);
        return err;
    }
    if (slot->value > UINT64_MAX - delta) {
        slot->value = UINT64_MAX;
        metrics->saturations++;
    } else {
        slot->value += delta;
    }
    metrics->updates++;
    platform_mutex_unlock(&metrics->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_set(
    BreakRuntimeMetrics *metrics,
    const char *name,
    BreakRuntimeMetricKind kind,
    u64 value) {
    BreakRuntimeError err = BREAK_RUNTIME_OK;
    RuntimeMetricSlot *slot;
    if (!metrics || kind != BREAK_RUNTIME_METRIC_GAUGE) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&metrics->mutex);
    if (metrics->closed) {
        metrics->closed_rejects++;
        platform_mutex_unlock(&metrics->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    slot = metrics_slot_for(metrics, name, kind, &err);
    if (!slot) {
        platform_mutex_unlock(&metrics->mutex);
        return err;
    }
    slot->value = value;
    metrics->updates++;
    platform_mutex_unlock(&metrics->mutex);
    return BREAK_RUNTIME_OK;
}

static bool metrics_is_owner(const BreakRuntimeMetrics *metrics) {
    /* owner is written once in create() before the registry is published, so
     * this read needs no lock. */
    return platform_thread_id_equal(platform_thread_current_id(), metrics->owner);
}

BreakRuntimeError break_runtime_metrics_snapshot(
    BreakRuntimeMetrics *metrics,
    BreakRuntimeMetricSample *out,
    u32 capacity,
    u32 *out_count) {
    u32 i;
    if (!metrics || !out_count) return BREAK_RUNTIME_INVALID;
    if (!metrics_is_owner(metrics)) return BREAK_RUNTIME_REJECTED;
    if (capacity != 0u && !out) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&metrics->mutex);
    *out_count = metrics->count;
    if (metrics->count > capacity) {
        platform_mutex_unlock(&metrics->mutex);
        return BREAK_RUNTIME_OVERLOAD;
    }
    for (i = 0u; i < metrics->count; ++i) {
        memcpy(out[i].name, metrics->slots[i].name, sizeof(out[i].name));
        out[i].kind = metrics->slots[i].kind;
        out[i].value = metrics->slots[i].value;
    }
    platform_mutex_unlock(&metrics->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_encode(
    BreakRuntimeMetrics *metrics,
    char *buf,
    usize capacity,
    usize *out_len) {
    usize needed = 0u;
    usize written = 0u;
    u32 i;
    bool overflow = false;
    if (!metrics || !out_len) return BREAK_RUNTIME_INVALID;
    if (!buf && capacity != 0u) return BREAK_RUNTIME_INVALID;
    if (!metrics_is_owner(metrics)) return BREAK_RUNTIME_REJECTED;
    platform_mutex_lock(&metrics->mutex);
    for (i = 0u; i < metrics->count; ++i) {
        const RuntimeMetricSlot *slot = &metrics->slots[i];
        char line[BREAK_RUNTIME_METRICS_NAME_CAPACITY + 48u];
        int n = snprintf(line, sizeof(line), "BRKM1 %s %s %llu\n", slot->name,
                         slot->kind == BREAK_RUNTIME_METRIC_COUNTER ? "counter" : "gauge",
                         (unsigned long long)slot->value);
        if (n < 0) {
            platform_mutex_unlock(&metrics->mutex);
            return BREAK_RUNTIME_FAILED;
        }
        needed += (usize)n;
        if (!overflow && written + (usize)n + 1u <= capacity) {
            memcpy(buf + written, line, (usize)n);
            written += (usize)n;
        } else {
            overflow = true;
        }
    }
    *out_len = needed;
    if (overflow || needed + 1u > capacity) {
        if (buf && capacity != 0u) buf[0] = '\0';
        platform_mutex_unlock(&metrics->mutex);
        return BREAK_RUNTIME_OVERLOAD;
    }
    buf[written] = '\0';
    platform_mutex_unlock(&metrics->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_stats(
    BreakRuntimeMetrics *metrics,
    BreakRuntimeMetricsStats *out_stats) {
    if (!metrics || !out_stats) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&metrics->mutex);
    out_stats->updates = metrics->updates;
    out_stats->overflow_drops = metrics->overflow_drops;
    out_stats->saturations = metrics->saturations;
    out_stats->closed_rejects = metrics->closed_rejects;
    out_stats->tracked = metrics->count;
    platform_mutex_unlock(&metrics->mutex);
    return BREAK_RUNTIME_OK;
}

static bool metrics_alert_fires(const BreakRuntimeMetricSample *samples, u32 sample_count,
                                const BreakRuntimeMetricAlertRule *rule) {
    for (u32 i = 0u; i < sample_count; ++i) {
        if (strcmp(samples[i].name, rule->name) != 0) continue;
        return rule->op == BREAK_RUNTIME_METRIC_ALERT_ABOVE ? samples[i].value > rule->threshold
                                                            : samples[i].value < rule->threshold;
    }
    return false;
}

BreakRuntimeError break_runtime_metrics_evaluate_alerts(
    const BreakRuntimeMetricSample *samples,
    u32 sample_count,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 *fired,
    u32 fired_capacity,
    u32 *out_count) {
    u32 required = 0u;
    u32 written = 0u;
    if (!out_count) return BREAK_RUNTIME_INVALID;
    *out_count = 0u;
    if ((!samples && sample_count != 0u) || (!rules && rule_count != 0u) ||
        (!fired && fired_capacity != 0u) ||
        sample_count > BREAK_RUNTIME_METRICS_MAX_CAPACITY ||
        rule_count > BREAK_RUNTIME_METRICS_MAX_CAPACITY)
        return BREAK_RUNTIME_INVALID;
    for (u32 r = 0u; r < rule_count; ++r) {
        if (!rules[r].name || (rules[r].op != BREAK_RUNTIME_METRIC_ALERT_ABOVE &&
                               rules[r].op != BREAK_RUNTIME_METRIC_ALERT_BELOW))
            return BREAK_RUNTIME_INVALID;
    }
    for (u32 r = 0u; r < rule_count; ++r)
        if (metrics_alert_fires(samples, sample_count, &rules[r])) required++;
    if (required > fired_capacity) {
        *out_count = required;
        return BREAK_RUNTIME_OVERLOAD;
    }
    for (u32 r = 0u; r < rule_count; ++r)
        if (metrics_alert_fires(samples, sample_count, &rules[r])) fired[written++] = r;
    *out_count = written;
    return BREAK_RUNTIME_OK;
}

struct BreakRuntimeMetricsHistory {
    BreakRuntimeMetricSample *samples; /* depth * width, frame-major */
    BreakRuntimeMetricSample *scratch; /* width; snapshot target before commit */
    u32 *counts;                       /* samples per frame */
    u64 *ticks;
    u32 depth;
    u32 width;
    u32 head;   /* next frame slot to write */
    u32 frames; /* retained frames */
    u64 recorded;
    u64 evicted;
    u64 width_drops;
};

BreakRuntimeError break_runtime_metrics_history_create(
    const BreakRuntimeMetricsHistoryConfig *config,
    BreakRuntimeMetricsHistory **out) {
    BreakRuntimeMetricsHistory *history;
    u32 width;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!config || config->depth == 0u ||
        config->depth > BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH ||
        config->width > BREAK_RUNTIME_METRICS_MAX_CAPACITY)
        return BREAK_RUNTIME_INVALID;
    width = config->width != 0u ? config->width : BREAK_RUNTIME_METRICS_DEFAULT_CAPACITY;
    history = (BreakRuntimeMetricsHistory *)calloc(1u, sizeof(*history));
    if (!history) return BREAK_RUNTIME_OOM;
    history->samples = (BreakRuntimeMetricSample *)calloc(
        (usize)config->depth * (usize)width, sizeof(*history->samples));
    history->scratch = (BreakRuntimeMetricSample *)calloc(width, sizeof(*history->scratch));
    history->counts = (u32 *)calloc(config->depth, sizeof(*history->counts));
    history->ticks = (u64 *)calloc(config->depth, sizeof(*history->ticks));
    if (!history->samples || !history->scratch || !history->counts || !history->ticks) {
        break_runtime_metrics_history_destroy(history);
        return BREAK_RUNTIME_OOM;
    }
    history->depth = config->depth;
    history->width = width;
    *out = history;
    return BREAK_RUNTIME_OK;
}

void break_runtime_metrics_history_destroy(BreakRuntimeMetricsHistory *history) {
    if (!history) return;
    free(history->samples);
    free(history->scratch);
    free(history->counts);
    free(history->ticks);
    free(history);
}

BreakRuntimeError break_runtime_metrics_history_record(
    BreakRuntimeMetricsHistory *history,
    BreakRuntimeMetrics *metrics,
    u64 tick) {
    BreakRuntimeError err;
    u32 count = 0u;
    u32 slot;
    if (!history || !metrics) return BREAK_RUNTIME_INVALID;
    if (history->frames > 0u) {
        u32 newest = (history->head + history->depth - 1u) % history->depth;
        if (tick <= history->ticks[newest]) return BREAK_RUNTIME_INVALID;
    }
    err = break_runtime_metrics_snapshot(metrics, history->scratch, history->width, &count);
    if (err == BREAK_RUNTIME_OVERLOAD) {
        history->width_drops++;
        return BREAK_RUNTIME_OVERLOAD;
    }
    if (err != BREAK_RUNTIME_OK) return err;
    slot = history->head;
    memcpy(&history->samples[(usize)slot * history->width], history->scratch,
           (usize)count * sizeof(*history->scratch));
    history->counts[slot] = count;
    history->ticks[slot] = tick;
    history->head = (slot + 1u) % history->depth;
    if (history->frames == history->depth)
        history->evicted++;
    else
        history->frames++;
    history->recorded++;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_history_frame(
    const BreakRuntimeMetricsHistory *history,
    u32 age,
    BreakRuntimeMetricSample *out,
    u32 capacity,
    u32 *out_count,
    u64 *out_tick) {
    u32 slot;
    u32 count;
    if (!history || !out_count || (!out && capacity != 0u)) return BREAK_RUNTIME_INVALID;
    *out_count = 0u;
    if (age >= history->frames) return BREAK_RUNTIME_STALE;
    slot = (history->head + history->depth - 1u - age) % history->depth;
    count = history->counts[slot];
    if (count > capacity) {
        *out_count = count;
        return BREAK_RUNTIME_OVERLOAD;
    }
    if (count > 0u)
        memcpy(out, &history->samples[(usize)slot * history->width],
               (usize)count * sizeof(*out));
    *out_count = count;
    if (out_tick) *out_tick = history->ticks[slot];
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_history_stats(
    const BreakRuntimeMetricsHistory *history,
    BreakRuntimeMetricsHistoryStats *out_stats) {
    if (!history || !out_stats) return BREAK_RUNTIME_INVALID;
    out_stats->recorded = history->recorded;
    out_stats->evicted = history->evicted;
    out_stats->width_drops = history->width_drops;
    out_stats->frames = history->frames;
    return BREAK_RUNTIME_OK;
}

/* True when `rule` fires on each of the `sustain` frames starting `offset`
 * steps back from the newest. Too few retained frames -> false (unproven). */
static bool metrics_history_window_fires(const BreakRuntimeMetricsHistory *history,
                                         const BreakRuntimeMetricAlertRule *rule,
                                         u32 sustain, u32 offset) {
    if (history->frames < sustain || history->frames - sustain < offset) return false;
    for (u32 age = offset; age < offset + sustain; ++age) {
        u32 slot = (history->head + history->depth - 1u - age) % history->depth;
        if (!metrics_alert_fires(&history->samples[(usize)slot * history->width],
                                 history->counts[slot], rule))
            return false;
    }
    return true;
}

BreakRuntimeError break_runtime_metrics_history_evaluate_alerts(
    const BreakRuntimeMetricsHistory *history,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 sustain,
    u32 *fired,
    u32 fired_capacity,
    u32 *out_count) {
    u32 required = 0u;
    u32 written = 0u;
    if (!out_count) return BREAK_RUNTIME_INVALID;
    *out_count = 0u;
    if (!history || sustain == 0u || sustain > BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH ||
        (!rules && rule_count != 0u) || (!fired && fired_capacity != 0u) ||
        rule_count > BREAK_RUNTIME_METRICS_MAX_CAPACITY)
        return BREAK_RUNTIME_INVALID;
    for (u32 r = 0u; r < rule_count; ++r) {
        if (!rules[r].name || (rules[r].op != BREAK_RUNTIME_METRIC_ALERT_ABOVE &&
                               rules[r].op != BREAK_RUNTIME_METRIC_ALERT_BELOW))
            return BREAK_RUNTIME_INVALID;
    }
    for (u32 r = 0u; r < rule_count; ++r)
        if (metrics_history_window_fires(history, &rules[r], sustain, 0u)) required++;
    if (required > fired_capacity) {
        *out_count = required;
        return BREAK_RUNTIME_OVERLOAD;
    }
    for (u32 r = 0u; r < rule_count; ++r)
        if (metrics_history_window_fires(history, &rules[r], sustain, 0u)) fired[written++] = r;
    *out_count = written;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_history_alert_edges(
    const BreakRuntimeMetricsHistory *history,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 sustain,
    BreakRuntimeMetricAlertEdge *edges,
    u32 edge_capacity) {
    if (!history || sustain == 0u || sustain >= history->depth ||
        (!rules && rule_count != 0u) || (!edges && rule_count != 0u) ||
        rule_count > BREAK_RUNTIME_METRICS_MAX_CAPACITY)
        return BREAK_RUNTIME_INVALID;
    for (u32 r = 0u; r < rule_count; ++r) {
        if (!rules[r].name || (rules[r].op != BREAK_RUNTIME_METRIC_ALERT_ABOVE &&
                               rules[r].op != BREAK_RUNTIME_METRIC_ALERT_BELOW))
            return BREAK_RUNTIME_INVALID;
    }
    if (edge_capacity < rule_count) return BREAK_RUNTIME_OVERLOAD;
    for (u32 r = 0u; r < rule_count; ++r) {
        bool now = metrics_history_window_fires(history, &rules[r], sustain, 0u);
        bool before = metrics_history_window_fires(history, &rules[r], sustain, 1u);
        edges[r] = now == before ? BREAK_RUNTIME_METRIC_ALERT_STEADY
                   : now         ? BREAK_RUNTIME_METRIC_ALERT_RAISED
                                 : BREAK_RUNTIME_METRIC_ALERT_CLEARED;
    }
    return BREAK_RUNTIME_OK;
}

static const BreakRuntimeMetricSample *metrics_history_find(
    const BreakRuntimeMetricsHistory *history, u32 age, const char *name) {
    u32 slot = (history->head + history->depth - 1u - age) % history->depth;
    const BreakRuntimeMetricSample *frame = &history->samples[(usize)slot * history->width];
    for (u32 i = 0u; i < history->counts[slot]; ++i)
        if (strcmp(frame[i].name, name) == 0) return &frame[i];
    return NULL;
}

/* Aggregate over `window` frames starting `offset` steps back from the
 * newest. Returns false (outputs untouched) when the window is not fully
 * retained or `name` is absent from all of its frames. */
static bool metrics_history_aggregate_at(const BreakRuntimeMetricsHistory *history,
                                         const char *name, u32 window, u32 offset,
                                         u64 *out_min, u64 *out_max, u64 *out_mean,
                                         u32 *out_counted) {
    u64 lo = 0u;
    u64 hi = 0u;
    u64 sum = 0u;
    u32 counted = 0u;
    if (history->frames == 0u || window > history->frames ||
        history->frames - window < offset)
        return false;
    for (u32 age = offset; age < offset + window; ++age) {
        const BreakRuntimeMetricSample *s = metrics_history_find(history, age, name);
        if (!s) continue;
        if (counted == 0u) {
            lo = s->value;
            hi = s->value;
        } else {
            if (s->value < lo) lo = s->value;
            if (s->value > hi) hi = s->value;
        }
        /* Saturating sum so a counter window cannot overflow silently. */
        if (sum > UINT64_MAX - s->value) {
            sum = UINT64_MAX;
        } else {
            sum += s->value;
        }
        ++counted;
    }
    if (counted == 0u) return false;
    if (out_min) *out_min = lo;
    if (out_max) *out_max = hi;
    if (out_mean) *out_mean = sum / counted;
    if (out_counted) *out_counted = counted;
    return true;
}

BreakRuntimeError break_runtime_metrics_history_aggregate(
    const BreakRuntimeMetricsHistory *history, const char *name, u32 window,
    u64 *out_min, u64 *out_max, u64 *out_mean, u32 *out_counted) {
    if (!history || !name || window == 0u) return BREAK_RUNTIME_INVALID;
    return metrics_history_aggregate_at(history, name, window, 0u, out_min, out_max, out_mean,
                                        out_counted)
               ? BREAK_RUNTIME_OK
               : BREAK_RUNTIME_STALE;
}

static bool metrics_aggregate_stat_valid(BreakRuntimeMetricAggregateStat stat) {
    return stat == BREAK_RUNTIME_METRIC_AGGREGATE_MIN ||
           stat == BREAK_RUNTIME_METRIC_AGGREGATE_MAX ||
           stat == BREAK_RUNTIME_METRIC_AGGREGATE_MEAN;
}

static bool metrics_aggregate_alert_fires(const BreakRuntimeMetricsHistory *history,
                                          const BreakRuntimeMetricAlertRule *rule, u32 window,
                                          u32 offset, BreakRuntimeMetricAggregateStat stat) {
    u64 lo = 0u;
    u64 hi = 0u;
    u64 mean = 0u;
    u64 value;
    if (!metrics_history_aggregate_at(history, rule->name, window, offset, &lo, &hi, &mean, NULL))
        return false;
    value = stat == BREAK_RUNTIME_METRIC_AGGREGATE_MIN   ? lo
            : stat == BREAK_RUNTIME_METRIC_AGGREGATE_MAX ? hi
                                                         : mean;
    return rule->op == BREAK_RUNTIME_METRIC_ALERT_ABOVE ? value > rule->threshold
                                                        : value < rule->threshold;
}

static bool metrics_alert_rules_valid(const BreakRuntimeMetricAlertRule *rules, u32 rule_count) {
    for (u32 r = 0u; r < rule_count; ++r) {
        if (!rules[r].name || (rules[r].op != BREAK_RUNTIME_METRIC_ALERT_ABOVE &&
                               rules[r].op != BREAK_RUNTIME_METRIC_ALERT_BELOW))
            return false;
    }
    return true;
}

BreakRuntimeError break_runtime_metrics_history_evaluate_aggregate_alerts(
    const BreakRuntimeMetricsHistory *history,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 window,
    BreakRuntimeMetricAggregateStat stat,
    u32 *fired,
    u32 fired_capacity,
    u32 *out_count) {
    u32 required = 0u;
    u32 written = 0u;
    if (!out_count) return BREAK_RUNTIME_INVALID;
    *out_count = 0u;
    if (!history || window == 0u || window > BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH ||
        !metrics_aggregate_stat_valid(stat) ||
        (!rules && rule_count != 0u) || (!fired && fired_capacity != 0u) ||
        rule_count > BREAK_RUNTIME_METRICS_MAX_CAPACITY)
        return BREAK_RUNTIME_INVALID;
    if (!metrics_alert_rules_valid(rules, rule_count)) return BREAK_RUNTIME_INVALID;
    for (u32 r = 0u; r < rule_count; ++r)
        if (metrics_aggregate_alert_fires(history, &rules[r], window, 0u, stat)) required++;
    if (required > fired_capacity) {
        *out_count = required;
        return BREAK_RUNTIME_OVERLOAD;
    }
    for (u32 r = 0u; r < rule_count; ++r)
        if (metrics_aggregate_alert_fires(history, &rules[r], window, 0u, stat))
            fired[written++] = r;
    *out_count = written;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_history_aggregate_alert_edges(
    const BreakRuntimeMetricsHistory *history,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 window,
    BreakRuntimeMetricAggregateStat stat,
    BreakRuntimeMetricAlertEdge *edges,
    u32 edge_capacity) {
    if (!history || window == 0u || window >= history->depth ||
        !metrics_aggregate_stat_valid(stat) || (!rules && rule_count != 0u) ||
        (!edges && rule_count != 0u) || rule_count > BREAK_RUNTIME_METRICS_MAX_CAPACITY)
        return BREAK_RUNTIME_INVALID;
    if (!metrics_alert_rules_valid(rules, rule_count)) return BREAK_RUNTIME_INVALID;
    if (edge_capacity < rule_count) return BREAK_RUNTIME_OVERLOAD;
    for (u32 r = 0u; r < rule_count; ++r) {
        bool now = metrics_aggregate_alert_fires(history, &rules[r], window, 0u, stat);
        bool before = metrics_aggregate_alert_fires(history, &rules[r], window, 1u, stat);
        edges[r] = now == before ? BREAK_RUNTIME_METRIC_ALERT_STEADY
                   : now         ? BREAK_RUNTIME_METRIC_ALERT_RAISED
                                 : BREAK_RUNTIME_METRIC_ALERT_CLEARED;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_history_delta(
    const BreakRuntimeMetricsHistory *history,
    const char *name,
    u32 span,
    u64 *out_delta,
    u64 *out_ticks) {
    const BreakRuntimeMetricSample *newest;
    const BreakRuntimeMetricSample *older;
    u32 newest_slot;
    u32 older_slot;
    if (!history || !name || span == 0u || !out_delta) return BREAK_RUNTIME_INVALID;
    if (history->frames == 0u) return BREAK_RUNTIME_STALE;
    newest = metrics_history_find(history, 0u, name);
    if (newest && newest->kind != BREAK_RUNTIME_METRIC_COUNTER) return BREAK_RUNTIME_INVALID;
    if (span >= history->frames || !newest) return BREAK_RUNTIME_STALE;
    older = metrics_history_find(history, span, name);
    /* Slots are never removed and a counter only grows (saturating), so a
     * kind change or a decrease means the frames are not comparable. */
    if (!older || older->kind != BREAK_RUNTIME_METRIC_COUNTER || older->value > newest->value)
        return BREAK_RUNTIME_STALE;
    newest_slot = (history->head + history->depth - 1u) % history->depth;
    older_slot = (history->head + history->depth - 1u - span) % history->depth;
    *out_delta = newest->value - older->value;
    if (out_ticks) *out_ticks = history->ticks[newest_slot] - history->ticks[older_slot];
    return BREAK_RUNTIME_OK;
}

typedef struct RuntimeMetricsLine {
    const char *name;
    usize name_len;
    BreakRuntimeMetricKind kind;
    u64 value;
} RuntimeMetricsLine;

/* Parses one line starting at text[*pos]; advances *pos past its LF. */
static bool metrics_decode_line(const char *text, usize len, usize *pos,
                                RuntimeMetricsLine *line) {
    static const char kTag[] = "BRKM1 ";
    usize p = *pos;
    usize start;
    usize digits;
    u64 value = 0u;
    if (len - p < sizeof(kTag) - 1u || memcmp(text + p, kTag, sizeof(kTag) - 1u) != 0)
        return false;
    p += sizeof(kTag) - 1u;
    start = p;
    while (p < len && (unsigned char)text[p] > ' ') p++;
    line->name = text + start;
    line->name_len = p - start;
    if (line->name_len == 0u || line->name_len >= BREAK_RUNTIME_METRICS_NAME_CAPACITY ||
        p >= len || text[p] != ' ')
        return false;
    p++;
    if (len - p >= 8u && memcmp(text + p, "counter ", 8u) == 0) {
        line->kind = BREAK_RUNTIME_METRIC_COUNTER;
        p += 8u;
    } else if (len - p >= 6u && memcmp(text + p, "gauge ", 6u) == 0) {
        line->kind = BREAK_RUNTIME_METRIC_GAUGE;
        p += 6u;
    } else {
        return false;
    }
    start = p;
    while (p < len && text[p] >= '0' && text[p] <= '9') {
        u64 d = (u64)(text[p] - '0');
        if (value > (UINT64_MAX - d) / 10u) return false;
        value = value * 10u + d;
        p++;
    }
    digits = p - start;
    if (digits == 0u || (digits > 1u && text[start] == '0')) return false;
    if (p >= len || text[p] != '\n') return false;
    line->value = value;
    *pos = p + 1u;
    return true;
}

BreakRuntimeError break_runtime_metrics_decode(
    const char *text,
    usize len,
    BreakRuntimeMetricSample *out,
    u32 capacity,
    u32 *out_count) {
    usize pos = 0u;
    u32 count = 0u;
    if (!out_count) return BREAK_RUNTIME_INVALID;
    *out_count = 0u;
    if ((!text && len != 0u) || (!out && capacity != 0u)) return BREAK_RUNTIME_INVALID;
    while (pos < len) {
        RuntimeMetricsLine line;
        usize prev = 0u;
        if (count == BREAK_RUNTIME_METRICS_MAX_CAPACITY) return BREAK_RUNTIME_INVALID;
        if (!metrics_decode_line(text, len, &pos, &line)) return BREAK_RUNTIME_INVALID;
        /* Earlier lines already parsed cleanly; re-walk them for duplicates. */
        for (u32 j = 0u; j < count; ++j) {
            RuntimeMetricsLine other;
            (void)metrics_decode_line(text, len, &prev, &other);
            if (other.name_len == line.name_len &&
                memcmp(other.name, line.name, line.name_len) == 0)
                return BREAK_RUNTIME_INVALID;
        }
        count++;
    }
    if (count > capacity) {
        *out_count = count;
        return BREAK_RUNTIME_OVERLOAD;
    }
    pos = 0u;
    for (u32 i = 0u; i < count; ++i) {
        RuntimeMetricsLine line;
        (void)metrics_decode_line(text, len, &pos, &line);
        memcpy(out[i].name, line.name, line.name_len);
        out[i].name[line.name_len] = '\0';
        out[i].kind = line.kind;
        out[i].value = line.value;
    }
    *out_count = count;
    return BREAK_RUNTIME_OK;
}

/* LZ77 codec (design section 35). Greedy matching through a hash of the next
 * four bytes, one candidate per bucket. Two passes keep compress free of an
 * output-size guess: the first only measures, the second writes, and both
 * walk the identical token sequence. */
#define LZ_MIN_MATCH 4u
#define LZ_MAX_MATCH (0x7Fu + LZ_MIN_MATCH) /* 131 */
#define LZ_MAX_LITERAL 128u
#define LZ_WINDOW 65535u
#define LZ_HASH_BITS 15u
#define LZ_HEADER 9u
static const u8 k_lz_magic[5] = {'B', 'R', 'K', 'Z', '1'};

static u32 lz_hash(const u8 *p) {
    u32 v = (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
    return (v * 2654435761u) >> (32u - LZ_HASH_BITS);
}

/* Emits pending literals [lit_start, lit_start + lit_len) in runs of at most
 * LZ_MAX_LITERAL. With out == NULL only the size is accumulated. */
static void lz_flush_literals(const u8 *in, usize lit_start, usize lit_len, u8 *out, usize *at) {
    while (lit_len != 0u) {
        usize run = lit_len < LZ_MAX_LITERAL ? lit_len : LZ_MAX_LITERAL;
        if (out) {
            out[*at] = (u8)(run - 1u);
            memcpy(out + *at + 1u, in + lit_start, run);
        }
        *at += 1u + run;
        lit_start += run;
        lit_len -= run;
    }
}

static usize lz_encode(const u8 *in, usize len, u32 *table, u8 *out) {
    usize at = LZ_HEADER;
    usize pos = 0u;
    usize lit_start = 0u;
    for (u32 i = 0u; i < (1u << LZ_HASH_BITS); ++i) table[i] = UINT32_MAX;
    if (out) {
        memcpy(out, k_lz_magic, sizeof k_lz_magic);
        out[5] = (u8)len;
        out[6] = (u8)(len >> 8);
        out[7] = (u8)(len >> 16);
        out[8] = (u8)(len >> 24);
    }
    while (pos + LZ_MIN_MATCH <= len) {
        u32 h = lz_hash(in + pos);
        u32 cand = table[h];
        usize match = 0u;
        table[h] = (u32)pos;
        if (cand != UINT32_MAX && pos - cand <= LZ_WINDOW &&
            memcmp(in + cand, in + pos, LZ_MIN_MATCH) == 0) {
            usize limit = len - pos < LZ_MAX_MATCH ? len - pos : LZ_MAX_MATCH;
            match = LZ_MIN_MATCH;
            while (match < limit && in[cand + match] == in[pos + match]) ++match;
        }
        if (match < LZ_MIN_MATCH) {
            ++pos;
            continue;
        }
        lz_flush_literals(in, lit_start, pos - lit_start, out, &at);
        if (out) {
            usize dist = pos - cand;
            out[at] = (u8)(0x80u | (match - LZ_MIN_MATCH));
            out[at + 1u] = (u8)dist;
            out[at + 2u] = (u8)(dist >> 8);
        }
        at += 3u;
        pos += match;
        lit_start = pos;
    }
    lz_flush_literals(in, lit_start, len - lit_start, out, &at);
    return at;
}

BreakRuntimeError break_runtime_metrics_compress(const void *in, usize len, void *out,
                                                 usize capacity, usize *out_len) {
    u32 *table;
    usize need;
    if (!out_len) return BREAK_RUNTIME_INVALID;
    *out_len = 0u;
    if ((!in && len != 0u) || (!out && capacity != 0u)) return BREAK_RUNTIME_INVALID;
    if (len > BREAK_RUNTIME_METRICS_COMPRESS_MAX_INPUT) return BREAK_RUNTIME_INVALID;
    table = (u32 *)malloc(sizeof(u32) << LZ_HASH_BITS);
    if (!table) return BREAK_RUNTIME_OOM;
    need = lz_encode((const u8 *)in, len, table, NULL);
    *out_len = need;
    if (capacity < need) {
        free(table);
        return BREAK_RUNTIME_OVERLOAD;
    }
    (void)lz_encode((const u8 *)in, len, table, (u8 *)out);
    free(table);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_decompress(const void *in, usize len, void *out,
                                                   usize capacity, usize *out_len) {
    const u8 *p = (const u8 *)in;
    u8 *o = (u8 *)out;
    usize want;
    usize at = LZ_HEADER;
    usize produced = 0u;
    if (!out_len) return BREAK_RUNTIME_INVALID;
    *out_len = 0u;
    if (!in || (!out && capacity != 0u)) return BREAK_RUNTIME_INVALID;
    if (len < LZ_HEADER || memcmp(p, k_lz_magic, sizeof k_lz_magic) != 0)
        return BREAK_RUNTIME_INVALID;
    want = (usize)p[5] | ((usize)p[6] << 8) | ((usize)p[7] << 16) | ((usize)p[8] << 24);
    if (want > BREAK_RUNTIME_METRICS_COMPRESS_MAX_INPUT) return BREAK_RUNTIME_INVALID;
    if (want > capacity) {
        *out_len = want;
        return BREAK_RUNTIME_OVERLOAD;
    }
    while (produced < want) {
        u8 c;
        if (at >= len) return BREAK_RUNTIME_INVALID; /* stream ends early */
        c = p[at++];
        if (c < 0x80u) {
            usize run = (usize)c + 1u;
            if (len - at < run || want - produced < run) return BREAK_RUNTIME_INVALID;
            memcpy(o + produced, p + at, run);
            at += run;
            produced += run;
        } else {
            usize run = (usize)(c & 0x7Fu) + LZ_MIN_MATCH;
            usize dist;
            if (len - at < 2u) return BREAK_RUNTIME_INVALID;
            dist = (usize)p[at] | ((usize)p[at + 1u] << 8);
            at += 2u;
            if (dist == 0u || dist > produced || want - produced < run)
                return BREAK_RUNTIME_INVALID;
            /* Byte by byte: the source may overlap the bytes being written. */
            for (usize k = 0u; k < run; ++k) o[produced + k] = o[produced - dist + k];
            produced += run;
        }
    }
    if (at != len) return BREAK_RUNTIME_INVALID; /* trailing bytes */
    *out_len = produced;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_merge(const void *const *docs, const usize *lens,
                                              u32 count, char *out, usize capacity,
                                              usize *out_len) {
    BreakRuntimeMetricSample *merged = NULL;
    BreakRuntimeMetricSample *scratch = NULL;
    u32 merged_count = 0u;
    usize needed = 0u;
    usize written = 0u;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (!out_len) return BREAK_RUNTIME_INVALID;
    *out_len = 0u;
    if ((!docs || !lens) && count != 0u) return BREAK_RUNTIME_INVALID;
    if (!out && capacity != 0u) return BREAK_RUNTIME_INVALID;
    if (count > BREAK_RUNTIME_METRICS_MERGE_MAX_DOCUMENTS) return BREAK_RUNTIME_INVALID;
    for (u32 d = 0u; d < count; ++d) {
        if (!docs[d] && lens[d] != 0u) return BREAK_RUNTIME_INVALID;
    }
    merged = (BreakRuntimeMetricSample *)calloc(BREAK_RUNTIME_METRICS_MAX_CAPACITY,
                                                sizeof(*merged));
    scratch = (BreakRuntimeMetricSample *)calloc(BREAK_RUNTIME_METRICS_MAX_CAPACITY,
                                                 sizeof(*scratch));
    if (!merged || !scratch) {
        result = BREAK_RUNTIME_OOM;
        goto done;
    }
    /* Validate and fold every document before writing a single output byte. */
    for (u32 d = 0u; d < count; ++d) {
        u32 n = 0u;
        if (break_runtime_metrics_decode((const char *)docs[d], lens[d], scratch,
                                         BREAK_RUNTIME_METRICS_MAX_CAPACITY,
                                         &n) != BREAK_RUNTIME_OK) {
            result = BREAK_RUNTIME_INVALID;
            goto done;
        }
        for (u32 i = 0u; i < n; ++i) {
            u32 j = 0u;
            while (j < merged_count && strcmp(merged[j].name, scratch[i].name) != 0) ++j;
            if (j < merged_count) {
                if (merged[j].kind != scratch[i].kind) {
                    result = BREAK_RUNTIME_INVALID;
                    goto done;
                }
                merged[j].value = scratch[i].value; /* newer document wins */
                continue;
            }
            if (merged_count == BREAK_RUNTIME_METRICS_MAX_CAPACITY) {
                result = BREAK_RUNTIME_INVALID;
                goto done;
            }
            merged[merged_count++] = scratch[i];
        }
    }
    for (u32 j = 0u; j < merged_count; ++j) {
        char line[BREAK_RUNTIME_METRICS_NAME_CAPACITY + 48u];
        int n = snprintf(line, sizeof(line), "BRKM1 %s %s %llu\n", merged[j].name,
                         merged[j].kind == BREAK_RUNTIME_METRIC_COUNTER ? "counter" : "gauge",
                         (unsigned long long)merged[j].value);
        if (n < 0) {
            result = BREAK_RUNTIME_FAILED;
            goto done;
        }
        if (needed + (usize)n + 1u <= capacity) {
            memcpy(out + written, line, (usize)n);
            written += (usize)n;
        }
        needed += (usize)n;
    }
    *out_len = needed;
    if (needed + 1u > capacity) {
        if (out && capacity != 0u) out[0] = '\0';
        result = BREAK_RUNTIME_OVERLOAD;
        goto done;
    }
    out[written] = '\0';
done:
    free(scratch);
    free(merged);
    return result;
}

BreakRuntimeError break_runtime_metrics_encode_alert_edges(
    const BreakRuntimeMetricAlertRule *rules,
    const BreakRuntimeMetricAlertEdge *edges,
    u32 count,
    char *buf,
    usize capacity,
    usize *out_len) {
    usize needed = 0u;
    usize written = 0u;
    if (!out_len) return BREAK_RUNTIME_INVALID;
    *out_len = 0u;
    if (((!rules || !edges) && count != 0u) || (!buf && capacity != 0u) ||
        count > BREAK_RUNTIME_METRICS_MAX_CAPACITY)
        return BREAK_RUNTIME_INVALID;
    for (u32 i = 0u; i < count; ++i) {
        if (!metrics_name_valid(rules[i].name, NULL) ||
            (rules[i].op != BREAK_RUNTIME_METRIC_ALERT_ABOVE &&
             rules[i].op != BREAK_RUNTIME_METRIC_ALERT_BELOW) ||
            (edges[i] != BREAK_RUNTIME_METRIC_ALERT_STEADY &&
             edges[i] != BREAK_RUNTIME_METRIC_ALERT_RAISED &&
             edges[i] != BREAK_RUNTIME_METRIC_ALERT_CLEARED))
            return BREAK_RUNTIME_INVALID;
    }
    for (u32 i = 0u; i < count; ++i) {
        char line[BREAK_RUNTIME_METRICS_NAME_CAPACITY + 64u];
        int n;
        if (edges[i] == BREAK_RUNTIME_METRIC_ALERT_STEADY) continue;
        n = snprintf(line, sizeof(line), "BRKA1 %s %s %s %llu\n",
                     edges[i] == BREAK_RUNTIME_METRIC_ALERT_RAISED ? "raised" : "cleared",
                     rules[i].name,
                     rules[i].op == BREAK_RUNTIME_METRIC_ALERT_ABOVE ? "above" : "below",
                     (unsigned long long)rules[i].threshold);
        if (n < 0 || (usize)n >= sizeof(line)) return BREAK_RUNTIME_FAILED;
        if (needed + (usize)n + 1u <= capacity) {
            memcpy(buf + written, line, (usize)n);
            written += (usize)n;
        }
        needed += (usize)n;
    }
    *out_len = needed;
    if (needed + 1u > capacity) {
        if (buf && capacity != 0u) buf[0] = '\0';
        return BREAK_RUNTIME_OVERLOAD;
    }
    buf[written] = '\0';
    return BREAK_RUNTIME_OK;
}

/* Bounded retry queue (design: docs/design/runtime_metrics.md section 22).
 * Owner-thread only, so no mutex: a ring of fixed-size payload slots carved
 * from one allocation. Enqueue copies bytes; a full ring evicts the oldest so
 * the freshest telemetry survives. */
typedef struct RetryEntry {
    usize len;
    u32 attempts;
    u64 due_us; /* timed drain: earliest retry time; 0 = due now */
} RetryEntry;

struct BreakRuntimeMetricsRetryQueue {
    PlatformThreadId owner;
    u32 capacity;
    usize max_payload_bytes;
    bool coalesce_repeats;
    bool draining; /* inside retry_drain: the send callback holds a borrowed slot */
    u32 head;  /* oldest entry */
    u32 count;
    RetryEntry *entries;
    u8 *payloads; /* capacity * max_payload_bytes */
    BreakRuntimeMetricsRetryStats stats;
};

static bool retry_is_owner(const BreakRuntimeMetricsRetryQueue *queue) {
    return platform_thread_id_equal(platform_thread_current_id(), queue->owner);
}

static u8 *retry_slot_bytes(BreakRuntimeMetricsRetryQueue *queue, u32 slot) {
    return queue->payloads + (usize)slot * queue->max_payload_bytes;
}

BreakRuntimeError break_runtime_metrics_retry_create(
    const BreakRuntimeMetricsRetryConfig *config,
    BreakRuntimeMetricsRetryQueue **out) {
    BreakRuntimeMetricsRetryQueue *queue;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!config) return BREAK_RUNTIME_INVALID;
    if (config->capacity == 0u ||
        config->capacity > BREAK_RUNTIME_METRICS_RETRY_MAX_ENTRIES) {
        return BREAK_RUNTIME_INVALID;
    }
    if (config->max_payload_bytes == 0u ||
        config->max_payload_bytes > BREAK_RUNTIME_METRICS_RETRY_MAX_PAYLOAD_BYTES) {
        return BREAK_RUNTIME_INVALID;
    }
    queue = (BreakRuntimeMetricsRetryQueue *)calloc(1u, sizeof(*queue));
    if (!queue) return BREAK_RUNTIME_OOM;
    queue->entries = (RetryEntry *)calloc(config->capacity, sizeof(*queue->entries));
    queue->payloads = (u8 *)calloc((usize)config->capacity, config->max_payload_bytes);
    if (!queue->entries || !queue->payloads) {
        free(queue->payloads);
        free(queue->entries);
        free(queue);
        return BREAK_RUNTIME_OOM;
    }
    queue->owner = platform_thread_current_id();
    queue->capacity = config->capacity;
    queue->max_payload_bytes = config->max_payload_bytes;
    queue->coalesce_repeats = config->coalesce_repeats;
    *out = queue;
    return BREAK_RUNTIME_OK;
}

void break_runtime_metrics_retry_destroy(BreakRuntimeMetricsRetryQueue *queue) {
    if (!queue) return;
    free(queue->payloads);
    free(queue->entries);
    free(queue);
}

BreakRuntimeError break_runtime_metrics_retry_enqueue(
    BreakRuntimeMetricsRetryQueue *queue, const void *bytes, usize len) {
    u32 slot;
    if (!queue || !bytes || len == 0u) return BREAK_RUNTIME_INVALID;
    if (len > queue->max_payload_bytes) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    if (queue->draining) return BREAK_RUNTIME_REJECTED;
    if (queue->coalesce_repeats && queue->count != 0u) {
        u32 newest = (queue->head + queue->count - 1u) % queue->capacity;
        if (queue->entries[newest].len == len &&
            memcmp(retry_slot_bytes(queue, newest), bytes, len) == 0) {
            queue->stats.coalesced++;
            return BREAK_RUNTIME_OK;
        }
    }
    if (queue->count == queue->capacity) {
        /* Drop the oldest so the newest payload is admitted. */
        queue->head = (queue->head + 1u) % queue->capacity;
        queue->count--;
        queue->stats.dropped_oldest++;
    }
    slot = (queue->head + queue->count) % queue->capacity;
    memcpy(retry_slot_bytes(queue, slot), bytes, len);
    queue->entries[slot].len = len;
    queue->entries[slot].attempts = 0u;
    queue->entries[slot].due_us = 0u;
    queue->count++;
    queue->stats.enqueued++;
    queue->stats.queued = queue->count;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_retry_peek(
    BreakRuntimeMetricsRetryQueue *queue, const void **out_bytes, usize *out_len,
    u32 *out_attempts) {
    if (!queue || !out_bytes || !out_len) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    if (queue->count == 0u) return BREAK_RUNTIME_STALE;
    *out_bytes = retry_slot_bytes(queue, queue->head);
    *out_len = queue->entries[queue->head].len;
    if (out_attempts) *out_attempts = queue->entries[queue->head].attempts;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_retry_record_attempt(
    BreakRuntimeMetricsRetryQueue *queue, u32 *out_attempts) {
    RetryEntry *entry;
    if (!queue) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    if (queue->count == 0u) return BREAK_RUNTIME_STALE;
    entry = &queue->entries[queue->head];
    if (entry->attempts != UINT32_MAX) entry->attempts++;
    queue->stats.attempts++;
    if (out_attempts) *out_attempts = entry->attempts;
    return BREAK_RUNTIME_OK;
}

static void retry_pop(BreakRuntimeMetricsRetryQueue *queue) {
    queue->head = (queue->head + 1u) % queue->capacity;
    queue->count--;
    queue->stats.released++;
    queue->stats.queued = queue->count;
}

BreakRuntimeError break_runtime_metrics_retry_release(
    BreakRuntimeMetricsRetryQueue *queue) {
    if (!queue) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    if (queue->draining) return BREAK_RUNTIME_REJECTED;
    if (queue->count == 0u) return BREAK_RUNTIME_STALE;
    retry_pop(queue);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_retry_stats(
    const BreakRuntimeMetricsRetryQueue *queue,
    BreakRuntimeMetricsRetryStats *out_stats) {
    if (!queue || !out_stats) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    *out_stats = queue->stats;
    out_stats->queued = queue->count;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_retry_drain(
    BreakRuntimeMetricsRetryQueue *queue, BreakRuntimeMetricsRetrySendFn send, void *user,
    u32 max_sends, u32 max_attempts, BreakRuntimeMetricsRetryDrainResult *out_result) {
    u32 sends = 0u;
    if (!queue || !send || !out_result || max_sends == 0u) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    if (queue->draining) return BREAK_RUNTIME_REJECTED;
    memset(out_result, 0, sizeof(*out_result));
    while (queue->count != 0u && sends < max_sends) {
        RetryEntry *entry = &queue->entries[queue->head];
        BreakRuntimeError sent;
        /* The callback gets a pointer into the ring, so queue mutation is
         * refused until it returns (enqueue/release/nested drain -> REJECTED). */
        queue->draining = true;
        sent = send(user, retry_slot_bytes(queue, queue->head), entry->len);
        queue->draining = false;
        sends++;
        if (sent == BREAK_RUNTIME_OK) {
            retry_pop(queue);
            out_result->delivered++;
            continue;
        }
        if (entry->attempts != UINT32_MAX) entry->attempts++;
        queue->stats.attempts++;
        out_result->failed++;
        if (max_attempts != 0u && entry->attempts >= max_attempts) {
            retry_pop(queue);
            out_result->abandoned++;
            continue;
        }
        break;
    }
    return BREAK_RUNTIME_OK;
}

/* Delay before the retry that follows the `attempts`-th failure (attempts >= 1):
 * min(base * 2^(attempts-1), max), with the shift saturating instead of
 * wrapping. */
static u64 retry_backoff_delay(const BreakRuntimeMetricsRetryBackoff *backoff, u32 attempts) {
    u32 shift = attempts - 1u;
    u64 delay;
    if (shift >= 64u || backoff->base_us > (UINT64_MAX >> shift)) {
        delay = UINT64_MAX;
    } else {
        delay = backoff->base_us << shift;
    }
    return delay < backoff->max_us ? delay : backoff->max_us;
}

BreakRuntimeError break_runtime_metrics_retry_drain_timed(
    BreakRuntimeMetricsRetryQueue *queue, BreakRuntimeMetricsRetrySendFn send, void *user,
    u32 max_sends, u32 max_attempts, const BreakRuntimeMetricsRetryBackoff *backoff,
    u64 now_us, BreakRuntimeMetricsRetryDrainResult *out_result) {
    u32 sends = 0u;
    if (!queue || !send || !out_result || !backoff || max_sends == 0u) {
        return BREAK_RUNTIME_INVALID;
    }
    if (backoff->base_us == 0u || backoff->max_us < backoff->base_us) {
        return BREAK_RUNTIME_INVALID;
    }
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    if (queue->draining) return BREAK_RUNTIME_REJECTED;
    memset(out_result, 0, sizeof(*out_result));
    while (queue->count != 0u && sends < max_sends) {
        RetryEntry *entry = &queue->entries[queue->head];
        BreakRuntimeError sent;
        u64 delay;
        if (now_us < entry->due_us) {
            out_result->deferred = 1u;
            break;
        }
        queue->draining = true;
        sent = send(user, retry_slot_bytes(queue, queue->head), entry->len);
        queue->draining = false;
        sends++;
        if (sent == BREAK_RUNTIME_OK) {
            retry_pop(queue);
            out_result->delivered++;
            continue;
        }
        if (entry->attempts != UINT32_MAX) entry->attempts++;
        queue->stats.attempts++;
        out_result->failed++;
        if (max_attempts != 0u && entry->attempts >= max_attempts) {
            retry_pop(queue);
            out_result->abandoned++;
            continue;
        }
        delay = retry_backoff_delay(backoff, entry->attempts);
        entry->due_us = now_us > UINT64_MAX - delay ? UINT64_MAX : now_us + delay;
        break;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_retry_next_due(
    BreakRuntimeMetricsRetryQueue *queue, u64 *out_due_us) {
    if (!queue || !out_due_us) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    if (queue->count == 0u) return BREAK_RUNTIME_STALE;
    *out_due_us = queue->entries[queue->head].due_us;
    return BREAK_RUNTIME_OK;
}

/* Per-channel retry router (design section 34): one queue per destination so
 * a stalled channel cannot hold another channel's FIFO head. */
typedef struct RetryRouterChannel {
    BreakRuntimeMetricsRetryQueue *queue;
    BreakRuntimeMetricsRetrySendFn send;
    void *user;
    u32 max_sends;
    u32 max_attempts;
    BreakRuntimeMetricsRetryBackoff backoff;
} RetryRouterChannel;

struct BreakRuntimeMetricsRetryRouter {
    u32 count;
    RetryRouterChannel channels[BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS];
};

void break_runtime_metrics_retry_router_destroy(BreakRuntimeMetricsRetryRouter *router) {
    if (!router) return;
    for (u32 i = 0u; i < router->count; ++i)
        break_runtime_metrics_retry_destroy(router->channels[i].queue);
    free(router);
}

BreakRuntimeError break_runtime_metrics_retry_router_create(
    const BreakRuntimeMetricsRetryRouterConfig *config,
    BreakRuntimeMetricsRetryRouter **out) {
    BreakRuntimeMetricsRetryRouter *router;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!config || !config->channels || config->channel_count == 0u ||
        config->channel_count > BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS)
        return BREAK_RUNTIME_INVALID;
    /* Validate every channel before allocating, so a bad later channel never
     * leaves earlier queues half built. Queue sizing is checked by
     * retry_create below, which also runs before anything is kept. */
    for (u32 i = 0u; i < config->channel_count; ++i) {
        const BreakRuntimeMetricsRetryChannelConfig *c = &config->channels[i];
        if (!c->send || c->max_sends == 0u) return BREAK_RUNTIME_INVALID;
        if (c->backoff.base_us == 0u || c->backoff.max_us < c->backoff.base_us)
            return BREAK_RUNTIME_INVALID;
    }
    router = (BreakRuntimeMetricsRetryRouter *)calloc(1u, sizeof(*router));
    if (!router) return BREAK_RUNTIME_OOM;
    for (u32 i = 0u; i < config->channel_count; ++i) {
        const BreakRuntimeMetricsRetryChannelConfig *c = &config->channels[i];
        RetryRouterChannel *ch = &router->channels[i];
        BreakRuntimeError err = break_runtime_metrics_retry_create(&c->queue, &ch->queue);
        if (err != BREAK_RUNTIME_OK) {
            break_runtime_metrics_retry_router_destroy(router);
            return err;
        }
        router->count = i + 1u;
        ch->send = c->send;
        ch->user = c->user;
        ch->max_sends = c->max_sends;
        ch->max_attempts = c->max_attempts;
        ch->backoff = c->backoff;
    }
    *out = router;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_retry_router_enqueue(
    BreakRuntimeMetricsRetryRouter *router, u32 channel, const void *bytes, usize len) {
    if (!router || channel >= router->count) return BREAK_RUNTIME_INVALID;
    return break_runtime_metrics_retry_enqueue(router->channels[channel].queue, bytes, len);
}

BreakRuntimeError break_runtime_metrics_retry_router_drain(
    BreakRuntimeMetricsRetryRouter *router, u64 now_us,
    BreakRuntimeMetricsRetryRouterResult *out_result) {
    BreakRuntimeError first = BREAK_RUNTIME_OK;
    if (!router || !out_result) return BREAK_RUNTIME_INVALID;
    memset(out_result, 0, sizeof(*out_result));
    for (u32 i = 0u; i < router->count; ++i) {
        RetryRouterChannel *ch = &router->channels[i];
        BreakRuntimeMetricsRetryDrainResult r;
        BreakRuntimeError err =
            break_runtime_metrics_retry_drain_timed(ch->queue, ch->send, ch->user, ch->max_sends,
                                                    ch->max_attempts, &ch->backoff, now_us, &r);
        if (err != BREAK_RUNTIME_OK) {
            if (first == BREAK_RUNTIME_OK) first = err;
            continue; /* report later; never stop the remaining channels */
        }
        out_result->delivered += r.delivered;
        out_result->abandoned += r.abandoned;
        out_result->failed += r.failed;
        out_result->deferred_channels += r.deferred;
    }
    return first;
}

BreakRuntimeError break_runtime_metrics_retry_router_next_due(
    BreakRuntimeMetricsRetryRouter *router, u64 *out_due_us) {
    bool any = false;
    u64 earliest = UINT64_MAX;
    if (!router || !out_due_us) return BREAK_RUNTIME_INVALID;
    for (u32 i = 0u; i < router->count; ++i) {
        u64 due = 0u;
        BreakRuntimeError err = break_runtime_metrics_retry_next_due(router->channels[i].queue, &due);
        if (err == BREAK_RUNTIME_STALE) continue;
        if (err != BREAK_RUNTIME_OK) return err;
        if (!any || due < earliest) earliest = due;
        any = true;
    }
    if (!any) return BREAK_RUNTIME_STALE;
    *out_due_us = earliest;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_retry_router_stats(
    BreakRuntimeMetricsRetryRouter *router, u32 channel, BreakRuntimeMetricsRetryStats *out_stats) {
    if (!router || !out_stats || channel >= router->count) return BREAK_RUNTIME_INVALID;
    return break_runtime_metrics_retry_stats(router->channels[channel].queue, out_stats);
}

/* Save image: "BRKR1", u32 count, then per entry u32 attempts, u32 len and the
 * payload, then a CRC-32 (ISO-HDLC, reflected 0xEDB88320) of all prior bytes.
 * Integers are little-endian. */
static const char k_retry_magic[5] = {'B', 'R', 'K', 'R', '1'};
#define RETRY_IMAGE_HEADER 9u /* magic + count */
#define RETRY_IMAGE_ENTRY_HEADER 8u
#define RETRY_IMAGE_TRAILER 4u

static u32 retry_crc32(const u8 *p, usize n) {
    u32 crc = 0xFFFFFFFFu;
    for (usize i = 0u; i < n; ++i) {
        crc ^= p[i];
        for (int b = 0; b < 8; ++b) crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
    }
    return ~crc;
}

static void retry_put_u32(u8 *p, u32 v) {
    p[0] = (u8)v;
    p[1] = (u8)(v >> 8);
    p[2] = (u8)(v >> 16);
    p[3] = (u8)(v >> 24);
}

static u32 retry_get_u32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

BreakRuntimeError break_runtime_metrics_retry_save(BreakRuntimeMetricsRetryQueue *queue,
                                                   void *out, usize capacity, usize *out_len) {
    usize need = RETRY_IMAGE_HEADER + RETRY_IMAGE_TRAILER;
    u8 *p;
    usize at;
    if (!queue || !out_len) return BREAK_RUNTIME_INVALID;
    if (!out && capacity != 0u) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    for (u32 i = 0u; i < queue->count; ++i) {
        u32 slot = (queue->head + i) % queue->capacity;
        need += RETRY_IMAGE_ENTRY_HEADER + queue->entries[slot].len;
    }
    *out_len = need;
    if (capacity < need) return BREAK_RUNTIME_OVERLOAD;
    p = (u8 *)out;
    memcpy(p, k_retry_magic, sizeof k_retry_magic);
    retry_put_u32(p + sizeof k_retry_magic, queue->count);
    at = RETRY_IMAGE_HEADER;
    for (u32 i = 0u; i < queue->count; ++i) {
        u32 slot = (queue->head + i) % queue->capacity;
        const RetryEntry *entry = &queue->entries[slot];
        retry_put_u32(p + at, entry->attempts);
        retry_put_u32(p + at + 4u, (u32)entry->len);
        at += RETRY_IMAGE_ENTRY_HEADER;
        memcpy(p + at, retry_slot_bytes(queue, slot), entry->len);
        at += entry->len;
    }
    retry_put_u32(p + at, retry_crc32(p, at));
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_metrics_retry_load(BreakRuntimeMetricsRetryQueue *queue,
                                                   const void *bytes, usize len,
                                                   u32 *out_loaded) {
    const u8 *p = (const u8 *)bytes;
    u32 count;
    usize at;
    if (!out_loaded) return BREAK_RUNTIME_INVALID;
    *out_loaded = 0u;
    if (!queue || !bytes || len == 0u) return BREAK_RUNTIME_INVALID;
    if (!retry_is_owner(queue)) return BREAK_RUNTIME_REJECTED;
    if (queue->draining) return BREAK_RUNTIME_REJECTED;
    /* Pass 1: validate the whole image without touching the queue. */
    if (len < RETRY_IMAGE_HEADER + RETRY_IMAGE_TRAILER) return BREAK_RUNTIME_INVALID;
    if (memcmp(p, k_retry_magic, sizeof k_retry_magic) != 0) return BREAK_RUNTIME_INVALID;
    if (retry_get_u32(p + len - RETRY_IMAGE_TRAILER) != retry_crc32(p, len - RETRY_IMAGE_TRAILER))
        return BREAK_RUNTIME_INVALID;
    count = retry_get_u32(p + sizeof k_retry_magic);
    at = RETRY_IMAGE_HEADER;
    for (u32 i = 0u; i < count; ++i) {
        u32 entry_len;
        if (len - RETRY_IMAGE_TRAILER - at < RETRY_IMAGE_ENTRY_HEADER) return BREAK_RUNTIME_INVALID;
        entry_len = retry_get_u32(p + at + 4u);
        at += RETRY_IMAGE_ENTRY_HEADER;
        if (entry_len == 0u || entry_len > queue->max_payload_bytes) return BREAK_RUNTIME_INVALID;
        if (len - RETRY_IMAGE_TRAILER - at < entry_len) return BREAK_RUNTIME_INVALID;
        at += entry_len;
    }
    if (at != len - RETRY_IMAGE_TRAILER) return BREAK_RUNTIME_INVALID; /* trailing bytes */
    /* Pass 2: append. Enqueue applies the full-ring eviction rule; it cannot
     * fail here because every length was checked against the slot size. */
    at = RETRY_IMAGE_HEADER;
    for (u32 i = 0u; i < count; ++i) {
        u32 attempts = retry_get_u32(p + at);
        u32 entry_len = retry_get_u32(p + at + 4u);
        u32 newest;
        bool coalesce = queue->coalesce_repeats;
        at += RETRY_IMAGE_ENTRY_HEADER;
        queue->coalesce_repeats = false; /* restore entries exactly as saved */
        (void)break_runtime_metrics_retry_enqueue(queue, p + at, entry_len);
        queue->coalesce_repeats = coalesce;
        newest = (queue->head + queue->count - 1u) % queue->capacity;
        queue->entries[newest].attempts = attempts;
        at += entry_len;
    }
    *out_loaded = count;
    return BREAK_RUNTIME_OK;
}
