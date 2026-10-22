#include <runtime/runtime_profiler.h>

#include <core/platform_thread.h>
#include <platform/time.h>
#include <runtime/runtime_test_hooks.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Formal profiler bridge over the existing profiler.c singleton. profiler.c
 * is byte-for-byte unchanged: the bridge calls only its public API
 * (profiler_current_tid() at record time; the consumer hands the exported
 * meta array to profiler_export_chrome_trace()).
 *
 * Concurrency layout: one mutex guards both rings. record() never allocates
 * and never waits — the hot path is a bounded ring write under a short mutex.
 * The profiler mutex is a leaf in the lock order (the bridge never calls into
 * any runtime subsystem while holding it), so reload workers recording
 * lifecycle instants cannot deadlock against the collector.
 */

typedef struct RuntimeProfilerEvent {
    u64 ts_us;
    u32 tid;
    char name[BREAK_RUNTIME_PROFILER_NAME_CAPACITY];
} RuntimeProfilerEvent;

struct BreakRuntimeProfiler {
    PlatformMutex mutex;
    RuntimeProfilerEvent *events; /* bounded transport ring */
    u32 event_capacity;
    u32 event_head;
    u32 event_count;
    RuntimeProfilerEvent *window; /* bounded presentation window (append) */
    char (*window_values)[BREAK_RUNTIME_PROFILER_VALUE_CAPACITY];
    u32 window_capacity;
    u32 window_count;
    PlatformThreadId owner; /* collector thread (create caller) */
    bool closed;
    /* stats (all under mutex) */
    u64 recorded;
    u64 overload_drops;
    u64 collected;
    u64 window_drops;
    u64 closed_rejects;
    u64 high_water;
};

BreakRuntimeError break_runtime_profiler_create(
    const BreakRuntimeProfilerConfig *config,
    BreakRuntimeProfiler **out_profiler)
{
    BreakRuntimeProfiler *profiler;
    u32 event_capacity;
    u32 window_capacity;

    if (!out_profiler) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_profiler = NULL;

    event_capacity = config && config->event_capacity != 0u
                         ? config->event_capacity
                         : BREAK_RUNTIME_PROFILER_DEFAULT_EVENT_CAPACITY;
    window_capacity = config && config->window_capacity != 0u
                          ? config->window_capacity
                          : BREAK_RUNTIME_PROFILER_DEFAULT_WINDOW_CAPACITY;
    if (event_capacity > BREAK_RUNTIME_PROFILER_MAX_EVENT_CAPACITY ||
        window_capacity > BREAK_RUNTIME_PROFILER_MAX_WINDOW_CAPACITY) {
        return BREAK_RUNTIME_INVALID;
    }
    /* Count AND byte checks before allocation. The count caps make these
     * unreachable in practice; they are part of the contract. The divisors
     * are bound to locals so the comparisons are not provably-false to the
     * compiler (the count range is capped above), matching the checked-size
     * style of the other runtime facades. */
    {
        const usize event_size = sizeof(RuntimeProfilerEvent);
        const usize value_size = sizeof(*profiler->window_values);
        if ((usize)event_capacity > SIZE_MAX / event_size ||
            (usize)window_capacity > SIZE_MAX / event_size ||
            (usize)window_capacity > SIZE_MAX / value_size) {
            return BREAK_RUNTIME_INVALID;
        }
    }

    profiler = break_runtime_test_calloc(sizeof(*profiler));
    if (!profiler) {
        return BREAK_RUNTIME_OOM;
    }
    platform_mutex_init(&profiler->mutex);
    profiler->event_capacity = event_capacity;
    profiler->window_capacity = window_capacity;
    profiler->owner = platform_thread_current_id();

    profiler->events = break_runtime_test_calloc(
        (usize)event_capacity * sizeof(RuntimeProfilerEvent));
    if (!profiler->events) {
        break_runtime_profiler_destroy(profiler);
        return BREAK_RUNTIME_OOM;
    }
    profiler->window = break_runtime_test_calloc(
        (usize)window_capacity * sizeof(RuntimeProfilerEvent));
    if (!profiler->window) {
        break_runtime_profiler_destroy(profiler);
        return BREAK_RUNTIME_OOM;
    }
    profiler->window_values = break_runtime_test_calloc(
        (usize)window_capacity * sizeof(*profiler->window_values));
    if (!profiler->window_values) {
        break_runtime_profiler_destroy(profiler);
        return BREAK_RUNTIME_OOM;
    }
    *out_profiler = profiler;
    return BREAK_RUNTIME_OK;
}

void break_runtime_profiler_close(BreakRuntimeProfiler *profiler)
{
    if (!profiler) {
        return;
    }
    platform_mutex_lock(&profiler->mutex);
    profiler->closed = true;
    platform_mutex_unlock(&profiler->mutex);
}

void break_runtime_profiler_destroy(BreakRuntimeProfiler *profiler)
{
    if (!profiler) {
        return;
    }
    free(profiler->window_values);
    free(profiler->window);
    free(profiler->events);
    platform_mutex_destroy(&profiler->mutex);
    free(profiler);
}

BreakRuntimeError break_runtime_profiler_record(
    BreakRuntimeProfiler *profiler,
    const char *name)
{
    usize name_len;
    RuntimeProfilerEvent *slot;

    if (!profiler || !name || name[0] == '\0') {
        return BREAK_RUNTIME_INVALID;
    }
    name_len = strlen(name);
    if (name_len >= (usize)BREAK_RUNTIME_PROFILER_NAME_CAPACITY) {
        return BREAK_RUNTIME_INVALID; /* rejected, never truncated */
    }

    platform_mutex_lock(&profiler->mutex);
    if (profiler->closed) {
        profiler->closed_rejects++;
        platform_mutex_unlock(&profiler->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    if (profiler->event_count >= profiler->event_capacity) {
        /* Hot path: never wait for capacity, never inline, never overwrite a
         * live entry. Bounded drop, counted. */
        profiler->overload_drops++;
        platform_mutex_unlock(&profiler->mutex);
        return BREAK_RUNTIME_OVERLOAD;
    }
    slot = &profiler->events[(profiler->event_head + profiler->event_count) %
                             profiler->event_capacity];
    /* Capture identity and time at the CALL SITE: the recording thread's own
     * profiler tid (lazily registered through profiler.c's thread-safe path)
     * and the current microsecond clock. */
    slot->tid = profiler_current_tid();
    slot->ts_us = time_microseconds();
    memcpy(slot->name, name, name_len + 1u);
    profiler->event_count++;
    profiler->recorded++;
    if ((u64)profiler->event_count > profiler->high_water) {
        profiler->high_water = profiler->event_count;
    }
    platform_mutex_unlock(&profiler->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_profiler_collect(
    BreakRuntimeProfiler *profiler,
    u32 max_events,
    u32 *out_count)
{
    u32 drained = 0u;
    bool closed;

    if (!profiler || !out_count) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_count = 0u;
    if (!platform_thread_id_equal(profiler->owner,
                                  platform_thread_current_id())) {
        return BREAK_RUNTIME_REJECTED;
    }

    platform_mutex_lock(&profiler->mutex);
    while (profiler->event_count > 0u && drained < max_events) {
        RuntimeProfilerEvent *event = &profiler->events[profiler->event_head];
        if (profiler->window_count < profiler->window_capacity) {
            u32 slot = profiler->window_count;
            /* Ownership handoff: the window takes the event copy; the value
             * string is materialized into bounded window storage. */
            profiler->window[slot] = *event;
            snprintf(profiler->window_values[slot],
                     BREAK_RUNTIME_PROFILER_VALUE_CAPACITY, "tid=%u ts=%llu",
                     event->tid, (unsigned long long)event->ts_us);
            profiler->window_count++;
        } else {
            /* The window never overwrites a live entry. */
            profiler->window_drops++;
        }
        profiler->event_head =
            (profiler->event_head + 1u) % profiler->event_capacity;
        profiler->event_count--;
        profiler->collected++;
        drained++;
    }
    closed = profiler->closed;
    platform_mutex_unlock(&profiler->mutex);

    *out_count = drained;
    if (drained == 0u && closed) {
        return BREAK_RUNTIME_CLOSED;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_profiler_export_meta(
    BreakRuntimeProfiler *profiler,
    ProfilerMetaInstant *out_meta,
    u32 capacity,
    u32 *out_count)
{
    u32 i;
    u32 filled;

    if (!profiler || !out_meta || !out_count) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_count = 0u;
    if (!platform_thread_id_equal(profiler->owner,
                                  platform_thread_current_id())) {
        return BREAK_RUNTIME_REJECTED;
    }

    platform_mutex_lock(&profiler->mutex);
    filled = profiler->window_count < capacity ? profiler->window_count
                                               : capacity;
    for (i = 0u; i < filled; i++) {
        /* Borrowed window storage; valid until the next collect/export/
         * destroy on this bridge. */
        out_meta[i].key = profiler->window[i].name;
        out_meta[i].value = profiler->window_values[i];
    }
    platform_mutex_unlock(&profiler->mutex);
    *out_count = filled;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_profiler_stats(
    BreakRuntimeProfiler *profiler,
    BreakRuntimeProfilerStats *out_stats)
{
    if (!profiler || !out_stats) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&profiler->mutex);
    out_stats->recorded = profiler->recorded;
    out_stats->overload_drops = profiler->overload_drops;
    out_stats->collected = profiler->collected;
    out_stats->window_drops = profiler->window_drops;
    out_stats->closed_rejects = profiler->closed_rejects;
    out_stats->high_water = profiler->high_water;
    out_stats->window_count = profiler->window_count;
    platform_mutex_unlock(&profiler->mutex);
    return BREAK_RUNTIME_OK;
}
