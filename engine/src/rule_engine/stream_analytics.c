#include "re_internal.h"
#include <string.h>
#include <stdint.h>
#include <math.h>

/* Stream analytics (sub-project C Task C2): the local analog of upstream
 * StreamAnalytics (rust-rule-engine v1.21.4 f80a541
 * src/streaming/aggregator.rs:285). The cache semantics mirror
 * aggregate_cached (:305) and the multi-window statistics mirror
 * moving_average (:329), detect_anomalies (:357) and calculate_trend (:399);
 * the public header documents every divergence. Local events are read
 * directly out of the window struct, the same access stream_correlation.c
 * uses. */

/* Exact event-name equality (the local "field" mapping): unlike the
 * aggregate filter, an empty name is not a wildcard - the analytics APIs
 * reject an empty event_name before this helper runs. */
static int analytics_event_matches(re_string_t event_name,
                                   const re_stream_event_impl_t *event) {
    return event_name.size == event->name_size &&
        memcmp(event_name.data, event->name, event_name.size) == 0;
}

static int analytics_event_numeric(const re_stream_event_impl_t *event) {
    return event->value.type == RE_VALUE_INT64 || event->value.type == RE_VALUE_DOUBLE;
}

/* Only callable for events analytics_event_numeric accepted. */
static double analytics_event_number(const re_stream_event_impl_t *event) {
    return event->value.type == RE_VALUE_INT64
        ? (double)event->value.as.int64_value : event->value.as.double_value;
}

static void analytics_entry_destroy(re_stream_analytics_t *analytics,
                                    re_stream_analytics_entry_t *entry) {
    re_free(&analytics->allocator, entry->key);
    re_free(&analytics->allocator, entry->event_type);
    re_free(&analytics->allocator, entry->first_data);
    re_free(&analytics->allocator, entry->last_data);
}

/* Entry identity: caller key string + kind + filter identity (event_type,
 * and percentile where relevant). Upstream keys on the string alone
 * (aggregator.rs:309); the wider identity is a documented hardening. The
 * percentile compares bitwise so -0.0/NaN stay distinct, mirroring the
 * bitwise double compare stream_correlation.c's stream_value_equal uses. */
static int analytics_entry_identity(const re_stream_analytics_entry_t *entry,
                                    re_string_t key,
                                    re_string_t event_type,
                                    re_stream_aggregate_kind_t kind,
                                    double percentile) {
    if (entry->kind != kind || entry->key_size != key.size ||
        entry->event_type_size != event_type.size) return 0;
    if (key.size != 0u && memcmp(entry->key, key.data, key.size) != 0) return 0;
    if (event_type.size != 0u &&
        memcmp(entry->event_type, event_type.data, event_type.size) != 0) return 0;
    return memcmp(&entry->percentile, &percentile, sizeof(percentile)) == 0;
}

/* Hit iff current_time - ts < ttl (aggregator.rs:311). A timestamp ahead of
 * the caller clock never hits: upstream's wrapping u64 subtraction would
 * compare huge against the ttl as well. */
static int analytics_entry_hit(const re_stream_analytics_entry_t *entry,
                               uint64_t cache_ttl_ms,
                               uint64_t current_time_ms) {
    return entry->timestamp_ms <= current_time_ms &&
        current_time_ms - entry->timestamp_ms < cache_ttl_ms;
}

/* Evict ALL entries past the TTL (upstream's retain, aggregator.rs:323). */
static void analytics_evict_expired(re_stream_analytics_t *analytics,
                                    uint64_t current_time_ms) {
    size_t index = 0u;
    while (index < analytics->count) {
        if (analytics_entry_hit(&analytics->entries[index],
                                analytics->cache_ttl_ms, current_time_ms)) {
            ++index;
        } else {
            analytics_entry_destroy(analytics, &analytics->entries[index]);
            analytics->entries[index] = analytics->entries[analytics->count - 1u];
            --analytics->count;
        }
    }
}

/* Copies the covered prefix of a fully populated cached result into
 * out_result, the same struct_size gating re_stream_window_aggregate_v1
 * applies on its way out. */
static void analytics_result_out(const re_stream_aggregate_result_t *cached,
                                 re_stream_aggregate_result_t *out_result) {
    uint32_t covered = out_result->struct_size < (uint32_t)sizeof(*out_result)
        ? out_result->struct_size : (uint32_t)sizeof(*out_result);
    memcpy(out_result, cached, covered);
    out_result->struct_size = covered;
}

/* Deep-copies a STRING result value into fresh storage so the cache never
 * borrows from the window (upstream clones the AggregationResult). */
static re_status_t analytics_clone_value_data(re_stream_analytics_t *analytics,
                                              re_value_t *value, char **out_data) {
    *out_data = NULL;
    if (value->type != RE_VALUE_STRING) return RE_STATUS_OK;
    *out_data = re_alloc(&analytics->allocator, value->as.string.size + 1u);
    if (*out_data == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(*out_data, value->as.string.data, value->as.string.size);
    (*out_data)[value->as.string.size] = '\0';
    value->as.string.data = *out_data;
    return RE_STATUS_OK;
}

re_status_t re_stream_analytics_create(re_engine_t *engine,
                                       uint64_t cache_ttl_ms,
                                       re_stream_analytics_t **out_analytics) {
    re_stream_analytics_t *analytics;
    if (engine == NULL || out_analytics == NULL) return RE_STATUS_INVALID_ARGUMENT;
    analytics = re_alloc(&engine->allocator, sizeof(*analytics));
    if (analytics == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(analytics, 0, sizeof(*analytics));
    analytics->allocator = engine->allocator;
    analytics->cache_ttl_ms = cache_ttl_ms;
    *out_analytics = analytics;
    return RE_STATUS_OK;
}

void re_stream_analytics_destroy(re_stream_analytics_t *analytics) {
    size_t index;
    if (analytics == NULL) return;
    for (index = 0u; index < analytics->count; ++index)
        analytics_entry_destroy(analytics, &analytics->entries[index]);
    re_free(&analytics->allocator, analytics->entries);
    re_free(&analytics->allocator, analytics);
}

re_status_t re_stream_analytics_aggregate_cached(
    re_stream_analytics_t *analytics, re_string_t key,
    const re_stream_window_t *window, const re_stream_filter_options_t *filter,
    re_stream_aggregate_kind_t kind, uint64_t current_time_ms,
    re_stream_aggregate_result_t *out_result) {
    re_string_t event_type;
    double percentile = 0.0;
    size_t index;
    re_stream_analytics_entry_t *entry;
    re_stream_aggregate_result_t fresh;
    if (analytics == NULL || window == NULL || filter == NULL ||
        out_result == NULL || key.data == NULL)
        return RE_STATUS_INVALID_ARGUMENT;
    /* The same validation re_stream_window_aggregate_v1 applies, done up
     * front so a cache hit cannot sneak an uncovered struct_size past the
     * gate (a hit never re-runs the fold). */
    if (filter->struct_size < (uint32_t)offsetof(re_stream_filter_options_t, percentile) ||
        out_result->struct_size < (uint32_t)offsetof(re_stream_aggregate_result_t, minimum) ||
        kind < RE_STREAM_AGGREGATE_COUNT || kind > RE_STREAM_AGGREGATE_PERCENTILE)
        return RE_STATUS_INVALID_ARGUMENT;
    if (kind == RE_STREAM_AGGREGATE_PERCENTILE &&
        (filter->struct_size < (uint32_t)offsetof(re_stream_filter_options_t, percentile) +
            (uint32_t)sizeof(filter->percentile) ||
         !(filter->percentile >= 0.0 && filter->percentile <= 100.0)))
        return RE_STATUS_INVALID_ARGUMENT;
    /* A non-empty event_type with NULL data matches nothing in the fold
     * (stream_name_matches rejects NULL data at nonzero size); collapse it
     * to the empty identity so it deliberately aliases the match-everything
     * cache entry instead of forming its own. */
    event_type = filter->event_type.data != NULL ? filter->event_type
        : (re_string_t){NULL, 0u};
    if (kind == RE_STREAM_AGGREGATE_PERCENTILE) percentile = filter->percentile;
    for (index = 0u; index < analytics->count; ++index) {
        entry = &analytics->entries[index];
        if (analytics_entry_identity(entry, key, event_type, kind, percentile) &&
            analytics_entry_hit(entry, analytics->cache_ttl_ms, current_time_ms)) {
            /* A hit returns the clone untouched: no timestamp refresh, no
             * eviction (aggregator.rs:313). */
            analytics_result_out(&entry->result, out_result);
            return RE_STATUS_OK;
        }
    }
    /* Miss: recompute via the C1 aggregate fold. Only successful
     * aggregations are cached; an error propagates with the cache untouched
     * (upstream caches AggregationResult::None instead - documented). */
    memset(&fresh, 0, sizeof(fresh));
    fresh.struct_size = (uint32_t)sizeof(fresh);
    {
        re_status_t status = re_stream_window_aggregate_v1(window, filter, kind, &fresh);
        if (status != RE_STATUS_OK) return status;
    }
    /* Evict-all-on-miss (aggregator.rs:323), run before the insert so the
     * fresh entry (and the first/last borrow handed out below) survives;
     * upstream's retain runs after the insert and only differs in the TTL-0
     * corner, where the local survivor can never be a hit anyway. A stale
     * entry with this identity is past the TTL by definition of the miss, so
     * eviction already removed it - a plain append replaces it. */
    analytics_evict_expired(analytics, current_time_ms);
    if (analytics->count == analytics->capacity) {
        size_t capacity = analytics->capacity == 0u ? 4u : analytics->capacity * 2u;
        re_stream_analytics_entry_t *entries = re_realloc(&analytics->allocator,
            analytics->entries, capacity * sizeof(*entries));
        if (entries == NULL) return RE_STATUS_OUT_OF_MEMORY;
        analytics->entries = entries;
        analytics->capacity = capacity;
    }
    entry = &analytics->entries[analytics->count];
    memset(entry, 0, sizeof(*entry));
    if (re_copy_string(&analytics->allocator, key, &entry->key) != RE_STATUS_OK)
        return RE_STATUS_OUT_OF_MEMORY;
    entry->key_size = key.size;
    if (event_type.size != 0u) {
        if (re_copy_string(&analytics->allocator, event_type, &entry->event_type) !=
            RE_STATUS_OK) {
            analytics_entry_destroy(analytics, entry);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        entry->event_type_size = event_type.size;
    }
    if (analytics_clone_value_data(analytics, &fresh.first, &entry->first_data) !=
        RE_STATUS_OK ||
        analytics_clone_value_data(analytics, &fresh.last, &entry->last_data) !=
        RE_STATUS_OK) {
        analytics_entry_destroy(analytics, entry);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    entry->timestamp_ms = current_time_ms;
    entry->kind = kind;
    entry->percentile = percentile;
    entry->result = fresh;
    ++analytics->count;
    analytics_result_out(&entry->result, out_result);
    return RE_STATUS_OK;
}

re_status_t re_stream_analytics_moving_average(
    const re_stream_analytics_t *analytics,
    const re_stream_window_t *const *windows, size_t window_count,
    re_string_t event_name, size_t last_n, double *out_value) {
    size_t start, w, e;
    uint64_t count = 0u;
    double sum = 0.0;
    if (analytics == NULL || out_value == NULL ||
        event_name.data == NULL || event_name.size == 0u ||
        (windows == NULL && window_count != 0u))
        return RE_STATUS_INVALID_ARGUMENT;
    /* window_count == 0 or last_n == 0 leave an empty selection, upstream's
     * None (aggregator.rs:333/:343). */
    if (window_count == 0u || last_n == 0u) return RE_STATUS_NOT_FOUND;
    start = window_count > last_n ? window_count - last_n : 0u;
    for (w = start; w < window_count; ++w) {
        const re_stream_window_t *window = windows[w];
        if (window == NULL) return RE_STATUS_INVALID_ARGUMENT;
        for (e = 0u; e < window->count; ++e) {
            const re_stream_event_impl_t *event = &window->events[e];
            if (!analytics_event_matches(event_name, event) ||
                !analytics_event_numeric(event)) continue;
            sum += analytics_event_number(event);
            ++count;
        }
    }
    /* Global sum/count over every matching event, NOT an average of
     * per-window averages (aggregator.rs:339-345). */
    if (count == 0u) return RE_STATUS_NOT_FOUND;
    *out_value = sum / (double)count;
    return RE_STATUS_OK;
}

re_status_t re_stream_analytics_detect_anomalies(
    const re_stream_analytics_t *analytics,
    const re_stream_window_t *const *windows, size_t window_count,
    re_string_t event_name, double threshold,
    uint64_t *out_timestamps, size_t capacity, size_t *out_count) {
    size_t w, e, flagged = 0u;
    uint64_t historical = 0u;
    double sum = 0.0, mean, squared = 0.0, stddev;
    if (analytics == NULL || out_count == NULL ||
        event_name.data == NULL || event_name.size == 0u ||
        (windows == NULL && window_count != 0u) ||
        (out_timestamps == NULL && capacity != 0u))
        return RE_STATUS_INVALID_ARGUMENT;
    /* Upstream returns an empty vector for both minimum violations; the
     * local API signals them (documented divergence). */
    if (window_count < 3u) return RE_STATUS_INVALID_ARGUMENT;
    /* Historical = every window except the last (aggregator.rs:363). */
    for (w = 0u; w + 1u < window_count; ++w) {
        const re_stream_window_t *window = windows[w];
        if (window == NULL) return RE_STATUS_INVALID_ARGUMENT;
        for (e = 0u; e < window->count; ++e) {
            const re_stream_event_impl_t *event = &window->events[e];
            if (!analytics_event_matches(event_name, event) ||
                !analytics_event_numeric(event)) continue;
            sum += analytics_event_number(event);
            ++historical;
        }
    }
    if (historical < 10u) return RE_STATUS_NOT_FOUND;
    /* Population statistics: variance divides by N (aggregator.rs:375-376). */
    mean = sum / (double)historical;
    for (w = 0u; w + 1u < window_count; ++w) {
        const re_stream_window_t *window = windows[w];
        for (e = 0u; e < window->count; ++e) {
            const re_stream_event_impl_t *event = &window->events[e];
            double delta;
            if (!analytics_event_matches(event_name, event) ||
                !analytics_event_numeric(event)) continue;
            delta = analytics_event_number(event) - mean;
            squared += delta * delta;
        }
    }
    stddev = sqrt(squared / (double)historical);
    if (stddev == 0.0) {
        /* Documented guard: upstream divides by zero - a value equal to the
         * mean gets a NaN z-score and passes, any unequal value gets +/-inf
         * and is flagged; local flags nothing. */
        *out_count = 0u;
        return RE_STATUS_OK;
    }
    /* Flag LAST-window events with |z| > threshold (aggregator.rs:383-391).
     * Upstream returns event IDs; local events have no IDs, so the timestamp
     * is the reported identity (duplicate timestamps repeat). A NaN
     * threshold flags nothing, matching upstream's comparison. */
    {
        const re_stream_window_t *window = windows[window_count - 1u];
        if (window == NULL) return RE_STATUS_INVALID_ARGUMENT;
        for (e = 0u; e < window->count; ++e) {
            const re_stream_event_impl_t *event = &window->events[e];
            double z;
            if (!analytics_event_matches(event_name, event) ||
                !analytics_event_numeric(event)) continue;
            z = (analytics_event_number(event) - mean) / stddev;
            if (fabs(z) > threshold) {
                if (flagged < capacity) out_timestamps[flagged] = event->timestamp;
                ++flagged;
            }
        }
    }
    /* The codebase's buffer-capacity idiom (re_rule_template_instantiate):
     * the caller learns the required capacity through *out_count. */
    *out_count = flagged;
    return flagged > capacity ? RE_STATUS_LIMIT : RE_STATUS_OK;
}

re_status_t re_stream_analytics_calculate_trend(
    const re_stream_analytics_t *analytics,
    const re_stream_window_t *const *windows, size_t window_count,
    re_string_t event_name, re_stream_trend_t *out_trend) {
    double *averages;
    size_t used = 0u, w, e, half, i;
    double first_sum = 0.0, second_sum = 0.0, first_avg, second_avg, change_percent;
    if (analytics == NULL || out_trend == NULL ||
        event_name.data == NULL || event_name.size == 0u ||
        (windows == NULL && window_count != 0u))
        return RE_STATUS_INVALID_ARGUMENT;
    /* Upstream returns Stable for window_count < 2 (aggregator.rs:402); the
     * local API signals it (documented divergence). */
    if (window_count < 2u) return RE_STATUS_INVALID_ARGUMENT;
    averages = re_alloc(&analytics->allocator, window_count * sizeof(*averages));
    if (averages == NULL) return RE_STATUS_OUT_OF_MEMORY;
    /* Per-window averages over the numeric events named event_name; windows
     * with no such events contribute nothing (upstream's filter_map,
     * aggregator.rs:405). */
    for (w = 0u; w < window_count; ++w) {
        const re_stream_window_t *window = windows[w];
        uint64_t count = 0u;
        double sum = 0.0;
        if (window == NULL) {
            re_free(&analytics->allocator, averages);
            return RE_STATUS_INVALID_ARGUMENT;
        }
        for (e = 0u; e < window->count; ++e) {
            const re_stream_event_impl_t *event = &window->events[e];
            if (!analytics_event_matches(event_name, event) ||
                !analytics_event_numeric(event)) continue;
            sum += analytics_event_number(event);
            ++count;
        }
        if (count != 0u) averages[used++] = sum / (double)count;
    }
    if (used < 2u) {
        re_free(&analytics->allocator, averages);
        *out_trend = RE_STREAM_TREND_STABLE;
        return RE_STATUS_OK;
    }
    /* Half-split: the second half takes the odd extra (aggregator.rs:411). */
    half = used / 2u;
    for (i = 0u; i < half; ++i) first_sum += averages[i];
    for (i = half; i < used; ++i) second_sum += averages[i];
    re_free(&analytics->allocator, averages);
    first_avg = first_sum / (double)half;
    second_avg = second_sum / (double)(used - half);
    if (first_avg == 0.0) {
        /* Documented division guard: upstream's f64 division yields
         * +/-inf (Increasing/Decreasing by the sign of second_avg) or NaN
         * (Stable) here; local reports STABLE. */
        *out_trend = RE_STREAM_TREND_STABLE;
        return RE_STATUS_OK;
    }
    /* > +5 Increasing, < -5 Decreasing, else Stable - the +/-5 boundary
     * itself is Stable (aggregator.rs:416-422). */
    change_percent = (second_avg - first_avg) / first_avg * 100.0;
    *out_trend = change_percent > 5.0 ? RE_STREAM_TREND_INCREASING
        : change_percent < -5.0 ? RE_STREAM_TREND_DECREASING
        : RE_STREAM_TREND_STABLE;
    return RE_STATUS_OK;
}
