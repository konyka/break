/* Sub-project C Task C5: stream rule evaluation - the engine's stream
 * registry and the window-fact injection run (upstream rust-rule-engine
 * v1.21.4 f80a541 src/streaming/engine.rs). The GRL stream-pattern CE
 * evaluation itself lives in ir_eval.c next to the other CE kinds and uses
 * re_engine_stream_lookup from this file. See rule_engine.h for the public
 * contract and the documented upstream mappings. */
#include "re_internal.h"
#include <string.h>
#include <stdint.h>

re_stream_window_t *re_engine_stream_lookup(const re_engine_t *engine,
                                            const char *name, size_t name_size) {
    size_t index;
    if (engine == NULL || name == NULL || name_size == 0u) return NULL;
    for (index = 0u; index < engine->stream_registry_count; ++index) {
        const re_stream_registry_entry_t *entry = &engine->stream_registry[index];
        if (entry->name_size == name_size && memcmp(entry->name, name, name_size) == 0)
            return entry->window;
    }
    return NULL;
}

re_status_t re_engine_stream_register(re_engine_t *engine, re_string_t name,
                                      re_stream_window_t *window) {
    size_t index;
    char *copy;
    if (engine == NULL || window == NULL || name.data == NULL || name.size == 0u)
        return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    for (index = 0u; index < engine->stream_registry_count; ++index) {
        re_stream_registry_entry_t *entry = &engine->stream_registry[index];
        if (entry->name_size == name.size && memcmp(entry->name, name.data, name.size) == 0) {
            /* Documented replace: re-registering a name swaps the borrowed
             * window and keeps the owned name copy. */
            entry->window = window;
            return RE_STATUS_OK;
        }
    }
    if (engine->stream_registry_count == RE_STREAM_REGISTRY_CAP) return RE_STATUS_LIMIT;
    copy = re_alloc(&engine->allocator, name.size + 1u);
    if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(copy, name.data, name.size);
    copy[name.size] = '\0';
    engine->stream_registry[engine->stream_registry_count].name = copy;
    engine->stream_registry[engine->stream_registry_count].name_size = name.size;
    engine->stream_registry[engine->stream_registry_count].window = window;
    ++engine->stream_registry_count;
    return RE_STATUS_OK;
}

re_status_t re_engine_stream_unregister(re_engine_t *engine, re_string_t name) {
    size_t index;
    if (engine == NULL || name.data == NULL || name.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    for (index = 0u; index < engine->stream_registry_count; ++index) {
        re_stream_registry_entry_t *entry = &engine->stream_registry[index];
        if (entry->name_size == name.size && memcmp(entry->name, name.data, name.size) == 0) {
            re_free(&engine->allocator, entry->name);
            /* The window is borrowed: it is NOT destroyed here. */
            for (++index; index < engine->stream_registry_count; ++index)
                engine->stream_registry[index - 1u] = engine->stream_registry[index];
            --engine->stream_registry_count;
            return RE_STATUS_OK;
        }
    }
    /* Documented no-op for an unregistered name. */
    return RE_STATUS_OK;
}

static uint64_t saturating_mul_u64(uint64_t left, uint64_t right) {
    if (left != 0u && right > UINT64_MAX / left) return UINT64_MAX;
    return left * right;
}

static uint64_t saturating_add_u64(uint64_t left, uint64_t right) {
    return left > UINT64_MAX - right ? UINT64_MAX : left + right;
}

/* Injection bounds (rule_engine.h documents the mapping): tumbling reports
 * the current bucket's span - window->bucket_start is the bucket INDEX
 * (ts / retention_ms, tumbling_session.c:136) - sliding the [oldest retained
 * event, watermark] span and session the [session start, session_end) span;
 * an empty sliding/session window reports 0/0. */
static void stream_window_bounds(const re_stream_window_t *window,
                                 uint64_t *out_start, uint64_t *out_end) {
    uint64_t start = 0u;
    uint64_t end = 0u;
    if (window->options.kind == RE_STREAM_WINDOW_TUMBLING) {
        start = saturating_mul_u64(window->bucket_start, window->options.retention_ms);
        end = saturating_add_u64(start, window->options.retention_ms);
    } else if (window->count != 0u) {
        start = window->events[0].timestamp;
        end = window->options.kind == RE_STREAM_WINDOW_SESSION
            ? window->session_end : window->watermark;
    }
    *out_start = start;
    *out_end = end;
}

static re_status_t inject_u64(re_facts_t *facts, const char *name, size_t name_size,
                              uint64_t value) {
    re_value_t fact;
    fact.type = RE_VALUE_INT64;
    fact.as.int64_value = value > (uint64_t)INT64_MAX ? INT64_MAX : (int64_t)value;
    return re_facts_set(facts, (re_string_t){name, name_size}, &fact);
}

static re_status_t inject_double(re_facts_t *facts, const char *name, size_t name_size,
                                 double value) {
    re_value_t fact;
    fact.type = RE_VALUE_DOUBLE;
    fact.as.double_value = value;
    return re_facts_set(facts, (re_string_t){name, name_size}, &fact);
}

/* One numeric fold per distinct event name (upstream's per-field fold,
 * engine.rs:364-376; the local "field" is the event name). name borrows the
 * first event carrying it - the window outlives the injection. */
typedef struct re_stream_fold_t {
    const char *name;
    size_t name_size;
    double sum;
    double minimum;
    double maximum;
    size_t count;
} re_stream_fold_t;

static int stream_value_is_numeric(const re_value_t *value, double *out) {
    if (value->type == RE_VALUE_INT64) { *out = (double)value->as.int64_value; return 1; }
    if (value->type == RE_VALUE_DOUBLE) { *out = value->as.double_value; return 1; }
    return 0;
}

/* Injects "<name>Sum" / "<name>Average" / "<name>Min" / "<name>Max" for one
 * fold: the name verbatim plus the capitalized suffix (upstream
 * engine.rs:364-376). */
static re_status_t inject_fold(re_facts_t *facts, const re_stream_fold_t *fold) {
    static const struct { const char *suffix; size_t size; } suffixes[4] = {
        {"Sum", 3u}, {"Average", 7u}, {"Min", 3u}, {"Max", 3u}
    };
    char *key;
    size_t index;
    re_status_t status = RE_STATUS_OK;
    if (fold->name_size > SIZE_MAX - 8u) return RE_STATUS_LIMIT;
    key = re_alloc(&facts->allocator, fold->name_size + 8u);
    if (key == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(key, fold->name, fold->name_size);
    for (index = 0u; index < 4u && status == RE_STATUS_OK; ++index) {
        double value = index == 0u ? fold->sum :
            index == 1u ? fold->sum / (double)fold->count :
            index == 2u ? fold->minimum : fold->maximum;
        memcpy(key + fold->name_size, suffixes[index].suffix, suffixes[index].size);
        status = inject_double(facts, key, fold->name_size + suffixes[index].size, value);
    }
    re_free(&facts->allocator, key);
    return status;
}

/* Builds the per-name numeric folds over the retained events (non-numeric
 * values are excluded from their name's fold, mirroring C1's numeric-only
 * aggregate fold; a name seen only with non-numeric values never gets a
 * fold) and injects them. */
static re_status_t inject_aggregates(re_facts_t *facts, const re_stream_window_t *window) {
    re_stream_fold_t *folds = NULL;
    size_t fold_count = 0u;
    size_t fold_capacity = 0u;
    size_t index;
    re_status_t status = RE_STATUS_OK;
    for (index = 0u; index < window->count && status == RE_STATUS_OK; ++index) {
        const re_stream_event_impl_t *event = &window->events[index];
        double number;
        size_t fold_index;
        if (!stream_value_is_numeric(&event->value, &number)) continue;
        for (fold_index = 0u; fold_index < fold_count; ++fold_index)
            if (folds[fold_index].name_size == event->name_size &&
                memcmp(folds[fold_index].name, event->name, event->name_size) == 0) break;
        if (fold_index == fold_count) {
            if (fold_count == fold_capacity) {
                size_t next = fold_capacity == 0u ? 8u : fold_capacity * 2u;
                re_stream_fold_t *grown;
                if (next < fold_capacity || next > SIZE_MAX / sizeof(*grown)) {
                    status = RE_STATUS_LIMIT;
                    break;
                }
                grown = re_realloc(&facts->allocator, folds, next * sizeof(*grown));
                if (grown == NULL) { status = RE_STATUS_OUT_OF_MEMORY; break; }
                folds = grown;
                fold_capacity = next;
            }
            folds[fold_count].name = event->name;
            folds[fold_count].name_size = event->name_size;
            folds[fold_count].sum = number;
            folds[fold_count].minimum = number;
            folds[fold_count].maximum = number;
            folds[fold_count].count = 1u;
            ++fold_count;
        } else {
            folds[fold_index].sum += number;
            if (number < folds[fold_index].minimum) folds[fold_index].minimum = number;
            if (number > folds[fold_index].maximum) folds[fold_index].maximum = number;
            ++folds[fold_index].count;
        }
    }
    for (index = 0u; index < fold_count && status == RE_STATUS_OK; ++index)
        status = inject_fold(facts, &folds[index]);
    re_free(&facts->allocator, folds);
    return status;
}

re_status_t re_engine_stream_run(re_engine_t *engine, re_facts_t *facts,
                                 re_stream_window_t *window) {
    static const char count_name[] = "WindowEventCount";
    static const char start_name[] = "WindowStartTime";
    static const char end_name[] = "WindowEndTime";
    static const char duration_name[] = "WindowDurationMs";
    uint64_t start;
    uint64_t end;
    re_status_t status;
    if (engine == NULL || facts == NULL || window == NULL) return RE_STATUS_INVALID_ARGUMENT;
    /* Keep the injection atomic with the run: a busy engine or fact set
     * rejects BEFORE any fact is written (re_engine_run would report the
     * same BUSY after the writes landed). */
    if (engine->running || facts->running) return RE_STATUS_BUSY;
    stream_window_bounds(window, &start, &end);
    /* Every injection is a host-visible re_facts_set write (the A8 built-in
     * idiom), so each one bumps facts->mutation_serial - B2's proof-graph
     * cache can never serve a stale backward result across two stream runs.
     * All four Window* facts are injected even when 0 (upstream always
     * injects them, engine.rs:347-353). */
    status = inject_double(facts, count_name, sizeof(count_name) - 1u, (double)window->count);
    if (status == RE_STATUS_OK)
        status = inject_u64(facts, start_name, sizeof(start_name) - 1u, start);
    if (status == RE_STATUS_OK)
        status = inject_u64(facts, end_name, sizeof(end_name) - 1u, end);
    if (status == RE_STATUS_OK)
        status = inject_u64(facts, duration_name, sizeof(duration_name) - 1u, end - start);
    if (status == RE_STATUS_OK) status = inject_aggregates(facts, window);
    if (status != RE_STATUS_OK) return status;
    return re_engine_run(engine, facts, NULL, NULL);
}
