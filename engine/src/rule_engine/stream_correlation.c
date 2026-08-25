#include "re_internal.h"
#include <string.h>
#include <stdint.h>
#include <limits.h>

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

re_status_t re_stream_window_aggregate_v1(const re_stream_window_t *window,
                                          const re_stream_filter_options_t *filter,
                                          re_stream_aggregate_kind_t kind,
                                          re_stream_aggregate_result_t *out_result) {
    size_t index;
    uint64_t count = 0u;
    double sum = 0.0;
    if (window == NULL || filter == NULL || out_result == NULL ||
        filter->struct_size < sizeof(*filter) ||
        out_result->struct_size < sizeof(*out_result) ||
        (kind != RE_STREAM_AGGREGATE_COUNT && kind != RE_STREAM_AGGREGATE_SUM &&
         kind != RE_STREAM_AGGREGATE_AVERAGE)) return RE_STATUS_INVALID_ARGUMENT;
    for (index = 0u; index < window->count; ++index) {
        const re_stream_event_impl_t *event = &window->events[index];
        if (!stream_filter_matches(event, filter)) continue;
        if (count == UINT64_MAX) return RE_STATUS_LIMIT;
        ++count;
        if (kind != RE_STREAM_AGGREGATE_COUNT) {
            if (event->value.type == RE_VALUE_INT64) sum += (double)event->value.as.int64_value;
            else if (event->value.type == RE_VALUE_DOUBLE) sum += event->value.as.double_value;
            else return RE_STATUS_INVALID_ARGUMENT;
        }
    }
    memset(out_result, 0, sizeof(*out_result));
    out_result->struct_size = sizeof(*out_result);
    out_result->count = count;
    out_result->sum = sum;
    out_result->average = count == 0u ? 0.0 : sum / (double)count;
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
