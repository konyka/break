#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

/* Runtime Core metrics registry (design: docs/design/runtime_metrics.md).
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * A process-local, thread-safe, non-blocking registry of named counters and
 * gauges, plus a stable text encoding a remote collector can parse. It is the
 * numeric-aggregate complement to runtime_profiler's event stream: the
 * profiler answers "what happened when", this answers "what are the counts
 * now". Neither touches engine/src/core/profiler.c, and this registry starts
 * no threads.
 *
 * Hot-path contract:
 *  - break_runtime_metrics_add()/set() are callable from ANY thread and NEVER
 *    block a hot path: no allocation, no callback, a short mutex guards a
 *    bounded slot table. A counter add saturates at UINT64_MAX (counted,
 *    never wraps). A name not yet present takes a free slot; the table full
 *    -> BREAK_RUNTIME_OVERLOAD, counted, nothing stored. Slots are never
 *    removed, so a name's index is stable for its lifetime.
 *  - A counter op on a gauge (or vice versa), or a kind that disagrees with an
 *    existing slot, -> BREAK_RUNTIME_INVALID with no state change.
 *  - After close -> BREAK_RUNTIME_CLOSED.
 *  - snapshot()/encode() are OWNER-THREAD-ONLY (the creating thread; REJECTED
 *    otherwise) and remain readable after close for a final export.
 *
 * Error taxonomy:
 *   INVALID  — NULL argument, empty/over-long name, name with whitespace,
 *              kind mismatch, config cap above its hard bound, byte/count
 *              overflow at create.
 *   REJECTED — snapshot/encode from a non-owner thread.
 *   CLOSED   — add/set after close.
 *   OVERLOAD — add/set on a full table; snapshot/encode into too small a
 *              buffer (non-blocking, counted / required size reported).
 *   OOM      — allocation failure at create.
 */

typedef struct BreakRuntimeMetrics BreakRuntimeMetrics; /* opaque, caller-owned */

#define BREAK_RUNTIME_METRICS_NAME_CAPACITY 48u
#define BREAK_RUNTIME_METRICS_DEFAULT_CAPACITY 64u
#define BREAK_RUNTIME_METRICS_MAX_CAPACITY 1024u

typedef enum BreakRuntimeMetricKind {
    BREAK_RUNTIME_METRIC_COUNTER = 0, /* monotonic, add-only */
    BREAK_RUNTIME_METRIC_GAUGE = 1    /* arbitrary instantaneous value */
} BreakRuntimeMetricKind;

typedef struct BreakRuntimeMetricsConfig {
    u32 capacity; /* 0 = default; bounded slot table */
} BreakRuntimeMetricsConfig;

typedef struct BreakRuntimeMetricSample {
    char name[BREAK_RUNTIME_METRICS_NAME_CAPACITY];
    BreakRuntimeMetricKind kind;
    u64 value;
} BreakRuntimeMetricSample;

typedef struct BreakRuntimeMetricsStats {
    u64 updates;        /* add/set operations accepted */
    u64 overflow_drops; /* add/set rejected OVERLOAD (table full) */
    u64 saturations;    /* counter adds clamped at UINT64_MAX */
    u64 closed_rejects; /* add/set rejected CLOSED */
    u32 tracked;        /* slots in use right now */
} BreakRuntimeMetricsStats;

/* On success *out is newly owned; on failure it is set to NULL. Count AND byte
 * checks run before allocation. The calling thread becomes the owner thread.
 * `config` may be NULL (defaults). */
BreakRuntimeError break_runtime_metrics_create(
    const BreakRuntimeMetricsConfig *config,
    BreakRuntimeMetrics **out);

/* Stops admission (add/set -> CLOSED). Idempotent; NULL is a no-op. */
void break_runtime_metrics_close(BreakRuntimeMetrics *metrics);

/* Releases the registry. NULL is a no-op. No worker threads exist; safe in
 * any state once producers have quiesced. */
void break_runtime_metrics_destroy(BreakRuntimeMetrics *metrics);

/* Hot-path counter accumulate / gauge is INVALID here. `kind` must be
 * COUNTER and must match any existing slot for `name`. Saturates at
 * UINT64_MAX (counted). Non-blocking; see header contract. */
BreakRuntimeError break_runtime_metrics_add(
    BreakRuntimeMetrics *metrics,
    const char *name,
    BreakRuntimeMetricKind kind,
    u64 delta);

/* Hot-path gauge set / counter is INVALID here. `kind` must be GAUGE and must
 * match any existing slot for `name`. Non-blocking; see header contract. */
BreakRuntimeError break_runtime_metrics_set(
    BreakRuntimeMetrics *metrics,
    const char *name,
    BreakRuntimeMetricKind kind,
    u64 value);

/* OWNER THREAD ONLY (REJECTED otherwise). Copies every slot into `out` (up to
 * `capacity`) in creation order. *out_count receives the number of slots.
 * Too small -> OVERLOAD with *out_count = required count and `out` untouched
 * past what fits is not written. Legal after close. */
BreakRuntimeError break_runtime_metrics_snapshot(
    BreakRuntimeMetrics *metrics,
    BreakRuntimeMetricSample *out,
    u32 capacity,
    u32 *out_count);

/* OWNER THREAD ONLY (REJECTED otherwise). Encodes the snapshot as stable
 * text, one line per metric:
 *   BRKM1 <name> <counter|gauge> <value>\n
 * into `buf` (NUL-terminated), in creation order. *out_len receives the byte
 * length (excluding NUL). `buf` too small (or NULL with `capacity` 0) ->
 * OVERLOAD with *out_len = required length and an empty `buf` when capacity
 * > 0. NULL metrics/out_len, or NULL `buf` with non-zero capacity -> INVALID.
 * Legal after close. */
BreakRuntimeError break_runtime_metrics_encode(
    BreakRuntimeMetrics *metrics,
    char *buf,
    usize capacity,
    usize *out_len);

/* Observability snapshot. INVALID on NULL arguments. Legal in any state. */
BreakRuntimeError break_runtime_metrics_stats(
    BreakRuntimeMetrics *metrics,
    BreakRuntimeMetricsStats *out_stats);
