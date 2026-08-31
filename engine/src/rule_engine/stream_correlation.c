#include "re_internal.h"
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

static int stream_name_matches(const re_string_t expected, const char *actual, size_t actual_size) {
    return expected.size == 0u || (expected.data != NULL && expected.size == actual_size &&
        memcmp(expected.data, actual, actual_size) == 0);
}

static int stream_key_matches(const re_string_t expected, const re_stream_event_impl_t *event) {
    if (expected.size == 0u) return 1;
    return event->value.type == RE_VALUE_STRING && expected.data != NULL &&
        expected.size == event->value.as.string.size &&
        memcmp(expected.data, event->value.as.string.data, expected.size) == 0;
}

static int stream_filter_matches(const re_stream_event_impl_t *event,
                                 const re_stream_filter_options_t *filter) {
    return stream_name_matches(filter->event_type, event->name, event->name_size) &&
           stream_key_matches(filter->key, event);
}

/* Typed value equality for COUNT_DISTINCT: same type tag and equal payload
 * (double compared bitwise, string by content, NONE/NULL/UNKNOWN equal their
 * own tag). The nearer local precedent is the shared re_value_equal_typed
 * (declared in re_internal.h, defined in engine.c): it is NOT reused because
 * its double arm is `==`, which would conflate -0.0 with 0.0 and make every
 * NaN unequal even to an identical NaN; the bitwise compare keeps NaN and
 * -0.0 distinct, the same choice the analytics cache's percentile identity
 * makes (stream_analytics.c). It otherwise mirrors the
 * backward_machine_bind.c value_equal idiom; upstream counts distinct
 * debug-strings instead (rust-rule-engine v1.21.4 f80a541
 * src/streaming/aggregator.rs CountDistinct arm), which would equate 1 and
 * 1.0 - a documented divergence. */
static int stream_value_equal(const re_value_t *left, const re_value_t *right) {
    if (left->type != right->type) return 0;
    switch (left->type) {
    case RE_VALUE_BOOL: return left->as.boolean == right->as.boolean;
    case RE_VALUE_INT64: return left->as.int64_value == right->as.int64_value;
    case RE_VALUE_DOUBLE:
        return memcmp(&left->as.double_value, &right->as.double_value,
                      sizeof(left->as.double_value)) == 0;
    case RE_VALUE_STRING:
        return left->as.string.size == right->as.string.size &&
            (left->as.string.size == 0u ||
             memcmp(left->as.string.data, right->as.string.data, left->as.string.size) == 0);
    case RE_VALUE_NONE: case RE_VALUE_NULL: case RE_VALUE_UNKNOWN: return 1;
    }
    return 0;
}

static int stream_double_compare(const void *left, const void *right) {
    double a = *(const double *)left;
    double b = *(const double *)right;
    return (a > b) - (a < b);
}

/* Only callable for events the numeric fold already accepted (INT64/DOUBLE). */
static double stream_event_number(const re_stream_event_impl_t *event) {
    return event->value.type == RE_VALUE_INT64
        ? (double)event->value.as.int64_value : event->value.as.double_value;
}

re_status_t re_stream_window_aggregate_v1(const re_stream_window_t *window,
                                          const re_stream_filter_options_t *filter,
                                          re_stream_aggregate_kind_t kind,
                                          re_stream_aggregate_result_t *out_result) {
    size_t index;
    uint64_t count = 0u;
    uint64_t distinct = 0u;
    double sum = 0.0;
    double minimum = 0.0;
    double maximum = 0.0;
    double stddev = 0.0;
    double percentile = 0.0;
    const re_stream_event_impl_t *first = NULL;
    const re_stream_event_impl_t *last = NULL;
    uint32_t covered;
    int folds_number;
    if (window == NULL || filter == NULL || out_result == NULL ||
        filter->struct_size < (uint32_t)offsetof(re_stream_filter_options_t, percentile) ||
        out_result->struct_size < (uint32_t)offsetof(re_stream_aggregate_result_t, minimum) ||
        kind < RE_STREAM_AGGREGATE_COUNT || kind > RE_STREAM_AGGREGATE_PERCENTILE)
        return RE_STATUS_INVALID_ARGUMENT;
    /* The percentile parameter is tail-appended (Task C1): a pre-C1 caller
     * cannot have supplied it, so only PERCENTILE requires the covered field.
     * NaN fails the range test. */
    if (kind == RE_STREAM_AGGREGATE_PERCENTILE &&
        (filter->struct_size < (uint32_t)offsetof(re_stream_filter_options_t, percentile) +
            (uint32_t)sizeof(filter->percentile) ||
         !(filter->percentile >= 0.0 && filter->percentile <= 100.0)))
        return RE_STATUS_INVALID_ARGUMENT;
    folds_number = kind == RE_STREAM_AGGREGATE_SUM || kind == RE_STREAM_AGGREGATE_AVERAGE ||
        kind == RE_STREAM_AGGREGATE_MIN || kind == RE_STREAM_AGGREGATE_MAX ||
        kind == RE_STREAM_AGGREGATE_STDDEV || kind == RE_STREAM_AGGREGATE_PERCENTILE;
    for (index = 0u; index < window->count; ++index) {
        const re_stream_event_impl_t *event = &window->events[index];
        if (!stream_filter_matches(event, filter)) continue;
        if (count == UINT64_MAX) return RE_STATUS_LIMIT;
        ++count;
        if (folds_number) {
            double number;
            if (event->value.type == RE_VALUE_INT64) number = (double)event->value.as.int64_value;
            else if (event->value.type == RE_VALUE_DOUBLE) number = event->value.as.double_value;
            else return RE_STATUS_INVALID_ARGUMENT;
            sum += number;
            if (count == 1u || number < minimum) minimum = number;
            if (count == 1u || number > maximum) maximum = number;
        }
        /* The events array is timestamp-sorted for sliding windows but plain
         * insertion order for bounded ones, so fold by timestamp: strict less
         * keeps the earliest insertion on ties, greater-or-equal keeps the
         * latest. */
        if (first == NULL || event->timestamp < first->timestamp) first = event;
        if (last == NULL || event->timestamp >= last->timestamp) last = event;
    }
    if (count == 0u && kind >= RE_STREAM_AGGREGATE_MIN) return RE_STATUS_NOT_FOUND;
    if (kind == RE_STREAM_AGGREGATE_STDDEV) {
        /* Population stddev: variance = sum((v - mean)^2) / N with the N
         * divisor, requiring >= 2 values (upstream None otherwise)
         * (f80a541 src/streaming/aggregator.rs:233). */
        double mean;
        double squared = 0.0;
        if (count < 2u) return RE_STATUS_NOT_FOUND;
        mean = sum / (double)count;
        for (index = 0u; index < window->count; ++index) {
            const re_stream_event_impl_t *event = &window->events[index];
            double delta;
            if (!stream_filter_matches(event, filter)) continue;
            delta = stream_event_number(event) - mean;
            squared += delta * delta;
        }
        stddev = sqrt(squared / (double)count);
    } else if (kind == RE_STREAM_AGGREGATE_PERCENTILE) {
        /* Sorted ascending, nearest-rank index round(p/100 * (n - 1))
         * (f80a541 src/streaming/aggregator.rs:253). */
        double *values;
        size_t used = 0u;
        size_t rank;
        if (count > (uint64_t)(SIZE_MAX / sizeof(double))) return RE_STATUS_LIMIT;
        values = re_alloc(&window->allocator, (size_t)count * sizeof(*values));
        if (values == NULL) return RE_STATUS_OUT_OF_MEMORY;
        for (index = 0u; index < window->count; ++index) {
            const re_stream_event_impl_t *event = &window->events[index];
            if (!stream_filter_matches(event, filter)) continue;
            values[used++] = stream_event_number(event);
        }
        qsort(values, used, sizeof(*values), stream_double_compare);
        rank = (size_t)round(filter->percentile / 100.0 * (double)(used - 1u));
        percentile = values[rank];
        re_free(&window->allocator, values);
    } else if (kind == RE_STREAM_AGGREGATE_COUNT_DISTINCT) {
        /* O(n^2) distinct scan over the bounded retained set: a value joins
         * the distinct set when no earlier matching event equals it. */
        size_t earlier_index;
        for (index = 0u; index < window->count; ++index) {
            const re_stream_event_impl_t *event = &window->events[index];
            int seen = 0;
            if (!stream_filter_matches(event, filter)) continue;
            for (earlier_index = 0u; earlier_index < index; ++earlier_index) {
                const re_stream_event_impl_t *earlier = &window->events[earlier_index];
                if (!stream_filter_matches(earlier, filter)) continue;
                if (stream_value_equal(&earlier->value, &event->value)) { seen = 1; break; }
            }
            if (!seen) {
                if (distinct == UINT64_MAX) return RE_STATUS_LIMIT;
                ++distinct;
            }
        }
    }
    covered = out_result->struct_size < (uint32_t)sizeof(*out_result)
        ? out_result->struct_size : (uint32_t)sizeof(*out_result);
    memset(out_result, 0, covered);
    out_result->struct_size = covered;
    /* For COUNT_DISTINCT the distinct-value count lands in count (documented
     * on the struct); every other kind reports the matching-event count. */
    out_result->count = kind == RE_STREAM_AGGREGATE_COUNT_DISTINCT ? distinct : count;
    out_result->sum = sum;
    out_result->average = count == 0u ? 0.0 : sum / (double)count;
    if ((uint32_t)offsetof(re_stream_aggregate_result_t, maximum) +
        (uint32_t)sizeof(out_result->maximum) <= covered) {
        out_result->minimum = minimum;
        out_result->maximum = maximum;
    }
    if ((uint32_t)offsetof(re_stream_aggregate_result_t, last) +
        (uint32_t)sizeof(out_result->last) <= covered) {
        /* Borrowed window-owned values; see the struct comment in the header. */
        if (first != NULL) out_result->first = first->value;
        if (last != NULL) out_result->last = last->value;
    }
    if ((uint32_t)offsetof(re_stream_aggregate_result_t, percentile) +
        (uint32_t)sizeof(out_result->percentile) <= covered) {
        out_result->stddev = stddev;
        out_result->percentile = percentile;
    }
    return RE_STATUS_OK;
}

re_status_t re_stream_window_correlate_v1(const re_stream_window_t *window,
                                          const re_stream_correlation_options_t *options,
                                          uint64_t *out_matches) {
    size_t first_index, second_index;
    uint64_t matches = 0u;
    if (window == NULL || options == NULL || out_matches == NULL ||
        options->struct_size < sizeof(*options) || options->timeout_ms == UINT64_MAX)
        return RE_STATUS_INVALID_ARGUMENT;
    for (first_index = 0u; first_index < window->count; ++first_index) {
        const re_stream_event_impl_t *first = &window->events[first_index];
        if (!stream_name_matches(options->first_event_type, first->name, first->name_size) ||
            !stream_key_matches(options->key, first)) continue;
        for (second_index = first_index + 1u; second_index < window->count; ++second_index) {
            const re_stream_event_impl_t *second = &window->events[second_index];
            uint64_t gap;
            if (!stream_name_matches(options->second_event_type, second->name, second->name_size) ||
                !stream_key_matches(options->key, second) || second->timestamp < first->timestamp)
                continue;
            gap = second->timestamp - first->timestamp;
            if (gap > options->timeout_ms) break;
            if (matches == UINT64_MAX) return RE_STATUS_LIMIT;
            ++matches;
            break;
        }
    }
    *out_matches = matches;
    return RE_STATUS_OK;
}
