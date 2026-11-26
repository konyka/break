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

static bool metrics_history_rule_sustained(const BreakRuntimeMetricsHistory *history,
                                           const BreakRuntimeMetricAlertRule *rule,
                                           u32 sustain) {
    if (history->frames < sustain) return false;
    for (u32 age = 0u; age < sustain; ++age) {
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
        if (metrics_history_rule_sustained(history, &rules[r], sustain)) required++;
    if (required > fired_capacity) {
        *out_count = required;
        return BREAK_RUNTIME_OVERLOAD;
    }
    for (u32 r = 0u; r < rule_count; ++r)
        if (metrics_history_rule_sustained(history, &rules[r], sustain)) fired[written++] = r;
    *out_count = written;
    return BREAK_RUNTIME_OK;
}
