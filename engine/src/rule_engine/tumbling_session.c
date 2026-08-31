#include "re_internal.h"
#include <string.h>
#include <stdint.h>

static size_t bounded_event_bytes(const re_stream_event_impl_t *event) {
    return event->name_size + (event->value.type == RE_VALUE_STRING
        ? event->value.as.string.size : sizeof(re_value_t));
}

static void bounded_drop(re_stream_window_t *window, size_t index) {
    size_t next;
    re_free(&window->allocator, window->events[index].name);
    re_free(&window->allocator, window->events[index].value_data);
    for (next = index + 1u; next < window->count; ++next)
        window->events[next - 1u] = window->events[next];
    --window->count;
}

static size_t bounded_total_bytes(const re_stream_window_t *window) {
    size_t index, total = 0u;
    for (index = 0u; index < window->count; ++index)
        total += bounded_event_bytes(&window->events[index]);
    return total;
}

static re_status_t bounded_copy(re_stream_window_t *window, re_string_t name,
                                const re_value_t *value, re_stream_event_impl_t *event) {
    memset(event, 0, sizeof(*event));
    event->timestamp = window->watermark;
    event->name_size = name.size;
    event->name = re_alloc(&window->allocator, name.size + 1u);
    if (event->name == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(event->name, name.data, name.size);
    event->name[name.size] = '\0';
    event->value = *value;
    if (value->type == RE_VALUE_STRING) {
        event->value_data = re_alloc(&window->allocator, value->as.string.size + 1u);
        if (event->value_data == NULL) {
            re_free(&window->allocator, event->name);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        memcpy(event->value_data, value->as.string.data, value->as.string.size);
        event->value_data[value->as.string.size] = '\0';
        event->value.as.string.data = event->value_data;
    }
    return RE_STATUS_OK;
}

static void bounded_limits(re_stream_window_t *window) {
    while (window->count > window->options.max_events ||
           (window->count != 0u && bounded_total_bytes(window) > window->options.max_bytes))
        bounded_drop(window, 0u);
}

static uint64_t bounded_saturating_add(uint64_t base, uint64_t add) {
    return base > UINT64_MAX - add ? UINT64_MAX : base + add;
}

/* Sub-project C Task C4, watermark-driven closure (a documented local
 * composition - upstream watermarks only gate recording and never drive
 * window closure, f80a541 src/streaming/watermark.rs:340; only join-node
 * eviction consumes them, src/rete/stream_join_node.rs:204). Evaluated
 * lazily at record time against the window's CURRENT watermark - no timers,
 * per the single-threaded contract. A record that ADVANCES the watermark may
 * therefore close older buckets/sessions as a side effect, and subsequent
 * records to them get the late-policy treatment below. A tumbling bucket is
 * CLOSED when watermark >= bucket_end + allowed_lateness_ms; the session a
 * record targets is CLOSED when watermark >= (timestamp_ms + retention_ms)
 * + allowed_lateness_ms. The gate runs BEFORE the late gate: for DROP and
 * ERROR it can never change the outcome (bucket_end > timestamp_ms and the
 * +retention term make closure strictly stronger than gap > lateness, so a
 * closed target is a late target with the same status); the observable delta
 * is ACCEPT - a closed target is recorded only when it is still retained
 * (tumbling: its bucket is the window's current bucket; session: the record
 * lands in the open session, timestamp_ms <= session_end), otherwise it is
 * RE_STATUS_NOT_FOUND instead of the late gate's silent RE_STATUS_OK. Closed
 * buckets remain readable for aggregation until the usual bucket switch or
 * bound eviction. Sliding windows never reach this function (extensions.c
 * keeps them on the record-gate-only path - no discrete buckets). */
static int bounded_closed_target(const re_stream_window_t *window, uint64_t timestamp_ms,
                                 int *out_retained) {
    uint64_t close_at;
    if (window->options.kind == RE_STREAM_WINDOW_TUMBLING) {
        uint64_t bucket = timestamp_ms / window->options.retention_ms;
        uint64_t bucket_end = bounded_saturating_add(
            timestamp_ms - timestamp_ms % window->options.retention_ms,
            window->options.retention_ms);
        close_at = bounded_saturating_add(bucket_end, window->options.allowed_lateness_ms);
        *out_retained = window->count != 0u && bucket == window->bucket_start;
    } else {
        uint64_t own_end = bounded_saturating_add(timestamp_ms, window->options.retention_ms);
        close_at = bounded_saturating_add(own_end, window->options.allowed_lateness_ms);
        *out_retained = window->count != 0u && timestamp_ms <= window->session_end;
    }
    return window->watermark >= close_at;
}

re_status_t re_stream_window_create_bounded(re_engine_t *engine,
                                            const re_stream_window_options_t *options,
                                            re_stream_window_t **out_window) {
    re_stream_window_t *window;
    if (engine == NULL || options == NULL || out_window == NULL) return RE_STATUS_INVALID_ARGUMENT;
    window = re_alloc(&engine->allocator, sizeof(*window));
    if (window == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(window, 0, sizeof(*window));
    window->allocator = engine->allocator;
    window->options = *options;
    *out_window = window;
    return RE_STATUS_OK;
}

re_status_t re_stream_window_record_bounded(re_stream_window_t *window,
                                            uint64_t timestamp_ms,
                                            re_string_t event_name,
                                            const re_value_t *value) {
    re_stream_event_impl_t event;
    int accept_closed_retained = 0;
    uint64_t gap = window != NULL && timestamp_ms < window->watermark
        ? window->watermark - timestamp_ms : 0u;
    if (window == NULL || value == NULL || event_name.data == NULL || event_name.size == 0u)
        return RE_STATUS_INVALID_ARGUMENT;
    if (window->options.watermark_drives_closure) {
        int retained = 0;
        if (bounded_closed_target(window, timestamp_ms, &retained)) {
            if (window->options.late_event_policy == RE_LATE_EVENT_DROP) return RE_STATUS_NOT_FOUND;
            if (window->options.late_event_policy == RE_LATE_EVENT_ERROR) return RE_STATUS_ERROR;
            if (!retained) return RE_STATUS_NOT_FOUND;
            accept_closed_retained = 1; /* ACCEPT: record the retained closed target. */
        }
    }
    if (!accept_closed_retained && gap > window->options.allowed_lateness_ms)
        return window->options.late_event_policy == RE_LATE_EVENT_DROP ? RE_STATUS_NOT_FOUND
            : window->options.late_event_policy == RE_LATE_EVENT_ERROR ? RE_STATUS_ERROR : RE_STATUS_OK;
    if (timestamp_ms > window->watermark) window->watermark = timestamp_ms;
    if (window->options.kind == RE_STREAM_WINDOW_TUMBLING) {
        uint64_t bucket = timestamp_ms / window->options.retention_ms;
        if (window->count != 0u && bucket != window->bucket_start) {
            while (window->count != 0u) bounded_drop(window, 0u);
        }
        window->bucket_start = bucket;
    } else if (window->count != 0u && timestamp_ms > window->session_end) {
        while (window->count != 0u) bounded_drop(window, 0u);
    }
    if (bounded_copy(window, event_name, value, &event) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY;
    event.timestamp = timestamp_ms;
    if (window->count == window->capacity) {
        size_t capacity = window->capacity == 0u ? 8u : window->capacity * 2u;
        re_stream_event_impl_t *events = re_realloc(&window->allocator, window->events,
                                                    capacity * sizeof(*events));
        if (events == NULL) {
            re_free(&window->allocator, event.name);
            re_free(&window->allocator, event.value_data);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        window->events = events;
        window->capacity = capacity;
    }
    window->events[window->count++] = event;
    if (window->options.kind == RE_STREAM_WINDOW_SESSION &&
        window->options.retention_ms > UINT64_MAX - timestamp_ms) {
        bounded_drop(window, window->count - 1u);
        return RE_STATUS_LIMIT;
    }
    if (window->options.kind == RE_STREAM_WINDOW_SESSION) {
        uint64_t next_end = timestamp_ms + window->options.retention_ms;
        if (next_end < timestamp_ms) {
            bounded_drop(window, window->count - 1u);
            return RE_STATUS_LIMIT;
        }
        if (next_end > window->session_end) window->session_end = next_end;
    }
    bounded_limits(window);
    return RE_STATUS_OK;
}
