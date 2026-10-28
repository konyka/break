#pragma once

#include <core/types.h>
#include <core/profiler.h>
#include <runtime/runtime_types.h>

/* Runtime Core formal profiler bridge (design:
 * docs/design/runtime_thread_model.md §5 "Profiler" / §6,
 * docs/design/runtime_hot_reload.md §4.1 "Message/Profiler",
 * docs/design/runtime_overview.md §6).
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * This is a bounded event handoff OVER the existing `engine/src/core/profiler.c`
 * singleton. profiler.c is byte-for-byte UNCHANGED and its behavior for
 * existing consumers (frame ring, per-thread tid tracks, Chrome trace export)
 * is untouched: the bridge uses only its public API
 * (profiler_current_tid() at record time; the consumer passes the bridge's
 * meta array to profiler_export_chrome_trace()). Span recording stays on the
 * existing profiler_push()/profiler_pop() on the recording thread — the
 * bridge deliberately does not replay spans on the collector thread, because
 * that would distort region timing (queueing delay would become duration).
 *
 * Event ownership and hot-path contract:
 *  - break_runtime_profiler_record() is callable from ANY thread and NEVER
 *    blocks a hot path: it performs no allocation, never waits for capacity
 *    and never runs a callback; it copies the name into a bounded preallocated
 *    ring slot under a short mutex and captures the thread's profiler tid
 *    (profiler_current_tid(), lazily registering the thread through
 *    profiler.c's own thread-safe path) and a microsecond timestamp at the
 *    call site. Full ring -> BREAK_RUNTIME_OVERLOAD, counted, nothing queued.
 *  - The event is OWNED by the bridge between record() and collect(); no
 *    event pointer ever escapes the bridge.
 *  - break_runtime_profiler_collect() is COLLECTOR/OWNER-THREAD-ONLY (the
 *    creating thread; REJECTED otherwise): it moves up to `max_events` events
 *    into the bounded presentation window. Window full -> the event is
 *    dropped and counted (stats.window_drops); the window never overwrites a
 *    live entry.
 *  - break_runtime_profiler_window_advance() (owner thread) retires the
 *    oldest presented entries FIFO after the consumer has exported them,
 *    freeing window capacity: the bridge is a CONTINUOUS handoff, not a
 *    one-shot buffer. Without advance the window eventually saturates and
 *    every later collect drops (all counted, never silent).
 *  - break_runtime_profiler_export_meta() fills a caller-provided
 *    ProfilerMetaInstant array (key = event name, value = "tid=N ts=US")
 *    borrowing the window storage; the consumer hands the array straight to
 *    profiler_export_chrome_trace(). The borrowed pointers stay valid until
 *    the next collect()/window_advance()/export_meta()/destroy() on this
 *    bridge.
 *
 * close() stops admission (record -> CLOSED, idempotent); collect() drains
 * the remainder and reports CLOSED once a closed bridge is empty. destroy()
 * releases the bridge in any state (no worker threads exist).
 *
 * Error taxonomy:
 *   INVALID  — NULL argument, empty/over-long name, malformed config (cap
 *              above its hard bound), byte/count overflow at create.
 *   REJECTED — collect/export from a non-owner thread.
 *   CLOSED   — record after close; collect on a closed, drained bridge.
 *   OVERLOAD — record on a full event ring (non-blocking, counted).
 *   OOM      — allocation failure at create.
 */

typedef struct BreakRuntimeProfiler BreakRuntimeProfiler; /* opaque, caller-owned */

#define BREAK_RUNTIME_PROFILER_NAME_CAPACITY 48u
#define BREAK_RUNTIME_PROFILER_VALUE_CAPACITY 56u
#define BREAK_RUNTIME_PROFILER_DEFAULT_EVENT_CAPACITY 256u
#define BREAK_RUNTIME_PROFILER_MAX_EVENT_CAPACITY 4096u
#define BREAK_RUNTIME_PROFILER_DEFAULT_WINDOW_CAPACITY 128u
#define BREAK_RUNTIME_PROFILER_MAX_WINDOW_CAPACITY 1024u

typedef struct BreakRuntimeProfilerConfig {
    u32 event_capacity;  /* 0 = default; bounded transport ring */
    u32 window_capacity; /* 0 = default; bounded presentation window */
} BreakRuntimeProfilerConfig;

typedef struct BreakRuntimeProfilerStats {
    u64 recorded;       /* events accepted into the transport ring */
    u64 overload_drops; /* records rejected OVERLOAD (ring full) */
    u64 collected;      /* events moved into the presentation window */
    u64 window_drops;   /* collected events dropped on a full window */
    u64 closed_rejects; /* records rejected CLOSED */
    u64 high_water;     /* maximum transport-ring occupancy observed */
    u32 window_count;   /* presentation-window entries right now */
} BreakRuntimeProfilerStats;

/* On success *out_profiler is newly owned; on failure it is set to NULL.
 * Count AND byte checks run before allocation. The calling thread becomes
 * the collector/owner thread. `config` may be NULL (defaults). */
BreakRuntimeError break_runtime_profiler_create(
    const BreakRuntimeProfilerConfig *config,
    BreakRuntimeProfiler **out_profiler);

/* Stops admission (record -> CLOSED). Idempotent; NULL is a no-op. */
void break_runtime_profiler_close(BreakRuntimeProfiler *profiler);

/* Releases the bridge and every owned event/window entry. NULL is a no-op.
 * No worker threads exist; safe in any state once producers have quiesced. */
void break_runtime_profiler_destroy(BreakRuntimeProfiler *profiler);

/* Hot-path event record (see header contract): copies `name`, captures the
 * calling thread's profiler tid and the current microsecond timestamp, and
 * enqueues an owned event. Non-blocking, never allocates, never runs a
 * callback. Full ring -> OVERLOAD; after close -> CLOSED. */
BreakRuntimeError break_runtime_profiler_record(
    BreakRuntimeProfiler *profiler,
    const char *name);

/* COLLECTOR/OWNER THREAD ONLY (REJECTED otherwise). Moves up to
 * `max_events` queued events into the bounded presentation window (window
 * full -> drop + count). *out_count receives the number drained this call.
 * Returns CLOSED once the bridge is closed AND fully drained. */
BreakRuntimeError break_runtime_profiler_collect(
    BreakRuntimeProfiler *profiler,
    u32 max_events,
    u32 *out_count);

/* COLLECTOR/OWNER THREAD ONLY (REJECTED otherwise). Fills `out_meta` (up to
 * `capacity`) with key/value pairs borrowing the presentation window; hand
 * the array to profiler_export_chrome_trace(). *out_count receives the
 * number filled. Borrowed pointers are valid until the next
 * collect/window_advance/export_meta/destroy on this bridge. */
BreakRuntimeError break_runtime_profiler_export_meta(
    BreakRuntimeProfiler *profiler,
    ProfilerMetaInstant *out_meta,
    u32 capacity,
    u32 *out_count);

/* COLLECTOR/OWNER THREAD ONLY (REJECTED otherwise). Retires the oldest
 * min(`count`, window_count) presented entries FIFO, freeing window capacity
 * for later collect() calls. Advancing zero entries is a no-op (OK). Call it
 * after the consumer has exported/consumed the presented entries. */
BreakRuntimeError break_runtime_profiler_window_advance(
    BreakRuntimeProfiler *profiler,
    u32 count);

/* Observability snapshot. INVALID on NULL arguments. Legal in any state. */
BreakRuntimeError break_runtime_profiler_stats(
    BreakRuntimeProfiler *profiler,
    BreakRuntimeProfilerStats *out_stats);
