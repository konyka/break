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

/* Threshold alert rules over a snapshot. A rule fires when the sample named
 * `name` exists and its value is STRICTLY above (ABOVE) or below (BELOW)
 * `threshold`; an absent name never fires. */
typedef enum BreakRuntimeMetricAlertOp {
    BREAK_RUNTIME_METRIC_ALERT_ABOVE = 0,
    BREAK_RUNTIME_METRIC_ALERT_BELOW = 1
} BreakRuntimeMetricAlertOp;

typedef struct BreakRuntimeMetricAlertRule {
    const char *name; /* sample name to test; must be non-NULL */
    BreakRuntimeMetricAlertOp op;
    u64 threshold;
} BreakRuntimeMetricAlertRule;

/* Pure, stateless, any thread: evaluates `rules` against `samples` (e.g. the
 * output of break_runtime_metrics_snapshot) and writes the indices of firing
 * rules into `fired` in rule order. *out_count receives the number of firing
 * rules. Too small `fired` -> OVERLOAD with *out_count = required count and
 * `fired` untouched. INVALID (with *out_count = 0) on NULL out_count, NULL
 * samples/rules/fired with a non-zero count, a rule with a NULL name or an
 * unknown op, or sample/rule count above BREAK_RUNTIME_METRICS_MAX_CAPACITY;
 * every rule is validated before any is evaluated. */
BreakRuntimeError break_runtime_metrics_evaluate_alerts(
    const BreakRuntimeMetricSample *samples,
    u32 sample_count,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 *fired,
    u32 fired_capacity,
    u32 *out_count);

/* Bounded history of snapshots: a caller-owned ring of `depth` frames, each a
 * copy of up to `width` samples stamped with a caller-supplied tick. It is
 * single-threaded (no lock) and allocates only at create. record() snapshots a
 * registry, so it must run on that registry's owner thread. */
typedef struct BreakRuntimeMetricsHistory BreakRuntimeMetricsHistory; /* opaque */

#define BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH 256u

typedef struct BreakRuntimeMetricsHistoryConfig {
    u32 depth; /* frames retained; 1..BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH */
    u32 width; /* samples per frame; 0 = BREAK_RUNTIME_METRICS_DEFAULT_CAPACITY */
} BreakRuntimeMetricsHistoryConfig;

typedef struct BreakRuntimeMetricsHistoryStats {
    u64 recorded;    /* frames accepted */
    u64 evicted;     /* oldest frames overwritten by a newer one */
    u64 width_drops; /* records rejected OVERLOAD: snapshot wider than `width` */
    u32 frames;      /* frames retained right now */
} BreakRuntimeMetricsHistoryStats;

/* On success *out is newly owned; on failure it is set to NULL. INVALID on
 * NULL arguments, depth 0 or above the max, width above
 * BREAK_RUNTIME_METRICS_MAX_CAPACITY. OOM on allocation failure. */
BreakRuntimeError break_runtime_metrics_history_create(
    const BreakRuntimeMetricsHistoryConfig *config,
    BreakRuntimeMetricsHistory **out);

/* NULL is a no-op. */
void break_runtime_metrics_history_destroy(BreakRuntimeMetricsHistory *history);

/* Snapshots `metrics` into a new frame stamped `tick`, evicting the oldest
 * frame when full. `tick` must be strictly greater than the last recorded
 * tick (INVALID otherwise). A snapshot wider than `width` -> OVERLOAD
 * (counted) with the ring unchanged. The registry's REJECTED (non-owner
 * thread) passes through with the ring unchanged. */
BreakRuntimeError break_runtime_metrics_history_record(
    BreakRuntimeMetricsHistory *history,
    BreakRuntimeMetrics *metrics,
    u64 tick);

/* Copies the frame `age` steps back (0 = newest) into `out` and its tick into
 * *out_tick (which may be NULL). *out_count receives the sample count. No such
 * frame -> STALE with *out_count = 0. `out` too small -> OVERLOAD with
 * *out_count = required count and `out` untouched. INVALID on NULL history or
 * out_count, or NULL `out` with non-zero capacity. */
BreakRuntimeError break_runtime_metrics_history_frame(
    const BreakRuntimeMetricsHistory *history,
    u32 age,
    BreakRuntimeMetricSample *out,
    u32 capacity,
    u32 *out_count,
    u64 *out_tick);

/* INVALID on NULL arguments. */
BreakRuntimeError break_runtime_metrics_history_stats(
    const BreakRuntimeMetricsHistory *history,
    BreakRuntimeMetricsHistoryStats *out_stats);

/* Sustained alerts over a history: a rule fires only when it fires (as in
 * break_runtime_metrics_evaluate_alerts) on EACH of the newest `sustain`
 * frames; with fewer retained frames nothing fires. This debounces a single
 * spike. Output, OVERLOAD and rule validation follow
 * break_runtime_metrics_evaluate_alerts. INVALID (with *out_count = 0) also on
 * NULL history, or `sustain` of 0 or above
 * BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH. Same thread as the history. */
BreakRuntimeError break_runtime_metrics_history_evaluate_alerts(
    const BreakRuntimeMetricsHistory *history,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 sustain,
    u32 *fired,
    u32 fired_capacity,
    u32 *out_count);

/* Per-rule transition between the sustained window ending at the newest frame
 * and the one ending a frame earlier. A window with too few retained frames
 * counts as not firing, so the first proven window reports RAISED. */
typedef enum BreakRuntimeMetricAlertEdge {
    BREAK_RUNTIME_METRIC_ALERT_STEADY = 0,  /* unchanged (firing or not) */
    BREAK_RUNTIME_METRIC_ALERT_RAISED = 1,  /* began firing at the newest frame */
    BREAK_RUNTIME_METRIC_ALERT_CLEARED = 2  /* stopped firing at the newest frame */
} BreakRuntimeMetricAlertEdge;

/* Writes one edge per rule into `edges[0..rule_count)` (rule order). INVALID
 * on NULL history, `sustain` of 0 or not below the history depth (the
 * previous window must stay provable once the ring is full), NULL rules/edges
 * with a non-zero count, a rule with a NULL name or unknown op, or a rule
 * count above BREAK_RUNTIME_METRICS_MAX_CAPACITY. `edge_capacity` below
 * `rule_count` -> OVERLOAD. `edges` is untouched on any error. Same thread as
 * the history; stateless, so a caller wanting each transition exactly once
 * calls this once per recorded frame. */
BreakRuntimeError break_runtime_metrics_history_alert_edges(
    const BreakRuntimeMetricsHistory *history,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 sustain,
    BreakRuntimeMetricAlertEdge *edges,
    u32 edge_capacity);

/* Growth of the COUNTER `name` between the frame `span` steps back and the
 * newest frame: *out_delta = newest - older, *out_ticks (may be NULL) = the
 * tick distance, so a caller derives a rate without floating point here.
 * STALE when fewer than `span` + 1 frames are retained or `name` is absent
 * from either frame. INVALID on NULL history/name/out_delta, `span` of 0, or
 * when `name` is a GAUGE (a gauge can fall, so its delta is not growth).
 * Outputs are untouched on any error. Same thread as the history. */
BreakRuntimeError break_runtime_metrics_history_delta(
    const BreakRuntimeMetricsHistory *history,
    const char *name,
    u32 span,
    u64 *out_delta,
    u64 *out_ticks);

/* Windowed aggregate of `name` over the newest `window` frames (age 0 ..
 * window-1): min, max and mean of the per-frame values. Works for COUNTER or
 * GAUGE (the caller knows the kind); the mean is integer (sum / counted),
 * truncated, and `sum` saturates at UINT64_MAX so a counter window cannot
 * overflow silently. Only frames in which `name` is present are counted;
 * `out_counted` reports how many of the `window` frames contributed. Any out
 * pointer may be NULL. STALE when the history is empty, `window` exceeds the
 * retained frames, or `name` is absent from every frame in the window (no
 * outputs written). INVALID on NULL history/name or `window` of 0. Same
 * thread as the history. */
BreakRuntimeError break_runtime_metrics_history_aggregate(
    const BreakRuntimeMetricsHistory *history,
    const char *name,
    u32 window,
    u64 *out_min,
    u64 *out_max,
    u64 *out_mean,
    u32 *out_counted);

/* Statistic an aggregate alert compares against its rule threshold. */
typedef enum BreakRuntimeMetricAggregateStat {
    BREAK_RUNTIME_METRIC_AGGREGATE_MIN = 0,
    BREAK_RUNTIME_METRIC_AGGREGATE_MAX = 1,
    BREAK_RUNTIME_METRIC_AGGREGATE_MEAN = 2
} BreakRuntimeMetricAggregateStat;

/* Windowed aggregate alerts: a rule fires when
 * break_runtime_metrics_history_aggregate over the newest `window` frames
 * succeeds and the chosen `stat` is STRICTLY above (ABOVE) or below (BELOW)
 * the rule threshold. A window longer than the retained frames, or a name
 * absent from every frame of the window, never fires. Output, OVERLOAD and
 * rule validation follow break_runtime_metrics_evaluate_alerts. INVALID (with
 * *out_count = 0) also on NULL history, `window` of 0 or above
 * BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH, or an unknown `stat`. Same thread
 * as the history. */
BreakRuntimeError break_runtime_metrics_history_evaluate_aggregate_alerts(
    const BreakRuntimeMetricsHistory *history,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 window,
    BreakRuntimeMetricAggregateStat stat,
    u32 *fired,
    u32 fired_capacity,
    u32 *out_count);

/* Per-rule transition of the aggregate alert between the window ending at the
 * newest frame and the one ending a frame earlier, as
 * break_runtime_metrics_history_alert_edges does for sustained alerts. An
 * unproven window counts as not firing, so the first proven firing window
 * reports RAISED. INVALID on NULL history, `window` of 0 or not below the
 * history depth (the previous window must stay provable once the ring is
 * full), an unknown `stat`, NULL rules/edges with a non-zero count, a rule
 * with a NULL name or unknown op, or a rule count above
 * BREAK_RUNTIME_METRICS_MAX_CAPACITY. `edge_capacity` below `rule_count` ->
 * OVERLOAD. `edges` is untouched on any error. Same thread as the history;
 * call once per recorded frame to see each transition exactly once. */
BreakRuntimeError break_runtime_metrics_history_aggregate_alert_edges(
    const BreakRuntimeMetricsHistory *history,
    const BreakRuntimeMetricAlertRule *rules,
    u32 rule_count,
    u32 window,
    BreakRuntimeMetricAggregateStat stat,
    BreakRuntimeMetricAlertEdge *edges,
    u32 edge_capacity);

/* Compression for encoded documents (design: docs/design/runtime_metrics.md
 * section 35). A self-contained LZ77 byte codec, so runtime_core takes no new
 * library dependency. BRKM1 text repeats its "BRKM1 " prefix, its kind and
 * long shared name prefixes on every line, which is exactly what LZ77 removes.
 *
 * Stream: "BRKZ1", a little-endian u32 original length, then tokens until the
 * output reaches that length. A control byte c < 0x80 is a literal run: the
 * next c + 1 bytes are copied. A control byte c >= 0x80 is a match: copy
 * (c & 0x7F) + 4 bytes starting a little-endian u16 distance (1..65535) back
 * in the output already produced; the copy may overlap itself, which is how a
 * run of one byte is expressed. The codec is not tied to the BRKM1 grammar and
 * works on any bytes. Pure; any thread. */
#define BREAK_RUNTIME_METRICS_COMPRESS_MAX_INPUT (16u * 1024u * 1024u)
/* Worst-case stream size for `n` input bytes: header plus one control byte
 * per 128 literals. compress never needs more than this. */
#define BREAK_RUNTIME_METRICS_COMPRESS_BOUND(n) (9u + (n) + ((n) + 127u) / 128u)

/* Compresses `len` bytes. OVERLOAD when `capacity` is below the stream size:
 * *out_len gets the exact size and nothing is written. INVALID on NULL
 * out_len, NULL in with non-zero len, NULL out with non-zero capacity, or len
 * above BREAK_RUNTIME_METRICS_COMPRESS_MAX_INPUT. OOM if the match index
 * cannot be allocated. */
BreakRuntimeError break_runtime_metrics_compress(const void *in, usize len, void *out,
                                                 usize capacity, usize *out_len);

/* Decompresses a stream, which is untrusted input. The original length is
 * read from the header first: a stream claiming more than `capacity` bytes is
 * OVERLOAD with *out_len set to that length and nothing written. Any
 * malformation (bad magic, short header, claimed length above
 * BREAK_RUNTIME_METRICS_COMPRESS_MAX_INPUT, a truncated token, a distance of 0
 * or past the output so far, a token that runs past the claimed length, or
 * trailing bytes) is INVALID with *out_len = 0. On INVALID, bytes already
 * written to `out` are not meaningful. Also INVALID on NULL out_len, NULL in,
 * or NULL out with non-zero capacity. */
BreakRuntimeError break_runtime_metrics_decompress(const void *in, usize len, void *out,
                                                   usize capacity, usize *out_len);

#define BREAK_RUNTIME_METRICS_MERGE_MAX_DOCUMENTS 64u

/* Batch merge: folds `count` encoded documents (each in the
 * break_runtime_metrics_encode() format, `lens[i]` bytes, oldest first) into
 * one document, so a backlog of snapshots goes out as a single payload. Each
 * name appears once, in the order it was first seen, with the value from the
 * NEWEST document that has it: a counter is monotonic and a gauge is a level,
 * so the latest snapshot supersedes earlier ones for both kinds. The output is
 * itself a valid input for break_runtime_metrics_decode().
 *
 * The whole batch is validated before anything is written. INVALID (with
 * *out_len = 0 and `out` untouched) when any document is malformed in the
 * break_runtime_metrics_decode() sense, a name changes kind between
 * documents, the merged set has more than BREAK_RUNTIME_METRICS_MAX_CAPACITY
 * names, `count` exceeds BREAK_RUNTIME_METRICS_MERGE_MAX_DOCUMENTS, or on NULL
 * out_len, NULL docs/lens with a non-zero count, a NULL document with a
 * non-zero length, or NULL `out` with a non-zero capacity. A result that does
 * not fit `capacity` bytes plus a NUL -> OVERLOAD with *out_len = required
 * length and out[0] = '\0' when capacity > 0. On OK, `out` is NUL-terminated
 * and *out_len excludes the NUL. Pure; any thread. */
BreakRuntimeError break_runtime_metrics_merge(
    const void *const *docs,
    const usize *lens,
    u32 count,
    char *out,
    usize capacity,
    usize *out_len);

/* Strict decoder for the break_runtime_metrics_encode() text, for a remote
 * collector reading untrusted bytes. `text` is `len` bytes (no NUL needed).
 * Every line must be exactly `BRKM1 <name> <counter|gauge> <value>\n`: name
 * per the registry rules (1..47 bytes, no byte <= 0x20), value canonical
 * unsigned decimal (no sign, no leading zero unless "0") within UINT64_MAX,
 * single spaces, LF line ends, no blank line, no duplicate name, at most
 * BREAK_RUNTIME_METRICS_MAX_CAPACITY lines. Any violation -> INVALID for the
 * whole input with *out_count = 0 and `out` untouched; a valid input with
 * more lines than `capacity` -> OVERLOAD with *out_count = required count and
 * `out` untouched. INVALID also on NULL out_count, NULL text with non-zero
 * len, or NULL out with non-zero capacity. Pure; any thread. */
BreakRuntimeError break_runtime_metrics_decode(
    const char *text,
    usize len,
    BreakRuntimeMetricSample *out,
    u32 capacity,
    u32 *out_count);

/* Stable text for alert delivery: one line per NON-STEADY edge, in rule
 * order,
 *   BRKA1 <raised|cleared> <name> <above|below> <threshold>\n
 * into `buf` (NUL-terminated); STEADY edges produce nothing, so an all-steady
 * input encodes to "". *out_len receives the byte length (excluding NUL).
 * `buf` too small (or NULL with capacity 0) -> OVERLOAD with *out_len =
 * required length and an empty `buf` when capacity > 0. INVALID on NULL
 * out_len, NULL rules/edges with a non-zero count, NULL buf with non-zero
 * capacity, a rule name the registry would reject, an unknown op or edge, or
 * a count above BREAK_RUNTIME_METRICS_MAX_CAPACITY; validation runs before
 * anything is written. Pure; any thread. */
BreakRuntimeError break_runtime_metrics_encode_alert_edges(
    const BreakRuntimeMetricAlertRule *rules,
    const BreakRuntimeMetricAlertEdge *edges,
    u32 count,
    char *buf,
    usize capacity,
    usize *out_len);

/* Bounded retry queue for failed metric/alert deliveries (design:
 * docs/design/runtime_metrics.md section 22).
 *
 * The push helpers report FAILED without retrying, so a caller that wants
 * at-least-once delivery had to keep its own backlog. This is that backlog:
 * a caller-owned, fixed-capacity FIFO of already-encoded payload bytes. It
 * starts no threads, never retries by itself and performs no I/O; the owner
 * drives it from its diagnostics step.
 *
 * Ownership and threading match the registry: every call is owner-thread only
 * (the creating thread; REJECTED otherwise). All storage is allocated at
 * create, so enqueue never allocates.
 *
 * A full queue drops the OLDEST entry to admit the newest (freshest telemetry
 * wins) and counts the drop. Each entry carries the number of delivery
 * attempts made for it, so a caller can give up on a poison payload. */
typedef struct BreakRuntimeMetricsRetryQueue BreakRuntimeMetricsRetryQueue; /* opaque */

#define BREAK_RUNTIME_METRICS_RETRY_MAX_ENTRIES 256u
#define BREAK_RUNTIME_METRICS_RETRY_MAX_PAYLOAD_BYTES (64u * 1024u)

typedef struct BreakRuntimeMetricsRetryConfig {
    u32 capacity;           /* entries retained; 1..BREAK_RUNTIME_METRICS_RETRY_MAX_ENTRIES */
    usize max_payload_bytes; /* per entry; 1..BREAK_RUNTIME_METRICS_RETRY_MAX_PAYLOAD_BYTES */
    /* When true, an enqueue whose bytes equal the NEWEST entry's is coalesced:
     * nothing is stored and `coalesced` counts it. Repeated pushes of an
     * unchanged registry are the common failure shape, and without this they
     * would evict distinct telemetry once the ring is full. Only the newest
     * entry is compared, so the check stays O(payload) and never scans the
     * ring; non-adjacent duplicates are still kept. */
    bool coalesce_repeats;
} BreakRuntimeMetricsRetryConfig;

typedef struct BreakRuntimeMetricsRetryStats {
    u32 queued;        /* entries currently held */
    u64 enqueued;      /* accepted enqueues */
    u64 dropped_oldest;/* entries evicted to admit a newer one */
    u64 released;      /* entries removed by release() */
    u64 attempts;      /* total attempt bumps recorded */
    u64 coalesced;     /* enqueues folded into the newest entry */
} BreakRuntimeMetricsRetryStats;

/* INVALID on NULL out, NULL config, a zero or over-bound capacity or
 * max_payload_bytes; OOM on allocation failure. */
BreakRuntimeError break_runtime_metrics_retry_create(
    const BreakRuntimeMetricsRetryConfig *config,
    BreakRuntimeMetricsRetryQueue **out);
void break_runtime_metrics_retry_destroy(BreakRuntimeMetricsRetryQueue *queue);

/* Copies `len` bytes as the newest entry with attempts = 0. A full queue drops
 * the oldest entry first (counted) and still returns OK. INVALID on NULL
 * queue, NULL bytes with non-zero len, zero len, or len above the configured
 * max_payload_bytes. REJECTED off the owner thread. */
BreakRuntimeError break_runtime_metrics_retry_enqueue(
    BreakRuntimeMetricsRetryQueue *queue,
    const void *bytes,
    usize len);

/* Borrows the oldest entry without removing it: *out_bytes points into the
 * queue and stays valid until the next enqueue/release/destroy. *out_attempts
 * receives the attempts recorded so far. STALE when the queue is empty (no
 * output written). INVALID on NULL queue/out_bytes/out_len; REJECTED off the
 * owner thread. */
BreakRuntimeError break_runtime_metrics_retry_peek(
    BreakRuntimeMetricsRetryQueue *queue,
    const void **out_bytes,
    usize *out_len,
    u32 *out_attempts);

/* Records one more delivery attempt for the oldest entry (saturating at
 * UINT32_MAX) and reports the new total. STALE when empty. */
BreakRuntimeError break_runtime_metrics_retry_record_attempt(
    BreakRuntimeMetricsRetryQueue *queue,
    u32 *out_attempts);

/* Removes the oldest entry (after a successful delivery, or to abandon a
 * poison payload). STALE when empty. */
BreakRuntimeError break_runtime_metrics_retry_release(
    BreakRuntimeMetricsRetryQueue *queue);

/* Owner-thread snapshot of the counters. INVALID on NULL argument. */
BreakRuntimeError break_runtime_metrics_retry_stats(
    const BreakRuntimeMetricsRetryQueue *queue,
    BreakRuntimeMetricsRetryStats *out_stats);

/* Delivery callback for break_runtime_metrics_retry_drain(): sends one payload
 * and returns OK on success; any other result counts as a failed attempt. */
typedef BreakRuntimeError (*BreakRuntimeMetricsRetrySendFn)(void *user, const void *bytes,
                                                            usize len);

typedef struct BreakRuntimeMetricsRetryDrainResult {
    u32 delivered;  /* entries sent and released */
    u32 abandoned;  /* entries released after reaching max_attempts */
    u32 failed;     /* failed sends this call (entry kept, attempt recorded) */
    u32 deferred;   /* timed drain only: 1 when it stopped at a head not yet due */
} BreakRuntimeMetricsRetryDrainResult;

/* Exponential backoff for break_runtime_metrics_retry_drain_timed(). After an
 * entry's n-th failed attempt (n >= 1) its next try is not before
 * now_us + min(base_us * 2^(n-1), max_us). The shift and the deadline both
 * saturate, so a long outage can only push the deadline to UINT64_MAX, never
 * wrap it into the past. Both values are microseconds on the caller's clock. */
typedef struct BreakRuntimeMetricsRetryBackoff {
    u64 base_us; /* delay after the first failure; must be > 0 */
    u64 max_us;  /* cap on every delay; must be >= base_us */
} BreakRuntimeMetricsRetryBackoff;

/* Runs the peek -> send -> release/record loop from the oldest entry, sending
 * at most `max_sends` payloads. A successful send releases the entry and goes
 * on to the next one. A failed send records an attempt; if the entry has then
 * reached `max_attempts` (0 = never give up) it is released and counted as
 * abandoned and draining continues, otherwise draining stops so the caller
 * backs off until its next step. Owner thread only; performs no I/O itself.
 * INVALID on NULL queue/send/out_result or max_sends == 0; REJECTED off the
 * owner thread. An empty queue is OK with all counts zero.
 *
 * Reentrancy: `send` receives a pointer into the queue's own storage, so while
 * it runs the queue refuses enqueue, release and a nested drain with REJECTED.
 * Without this, an enqueue that wrapped the ring could overwrite the very bytes
 * being transmitted. Enqueue work discovered inside `send` must be deferred
 * until drain returns. */
BreakRuntimeError break_runtime_metrics_retry_drain(
    BreakRuntimeMetricsRetryQueue *queue,
    BreakRuntimeMetricsRetrySendFn send,
    void *user,
    u32 max_sends,
    u32 max_attempts,
    BreakRuntimeMetricsRetryDrainResult *out_result);

/* break_runtime_metrics_retry_drain() with automatic backoff timing. Before
 * each send it checks the head entry's deadline: when now_us is earlier, the
 * drain stops without sending and reports deferred = 1. A failed send that
 * keeps its entry sets that entry's deadline from `backoff` (see
 * BreakRuntimeMetricsRetryBackoff); a fresh entry is due at once. Delivery,
 * abandonment and reentrancy are exactly as in retry_drain. The deadline is
 * per entry, so once a failed head is delivered the next entry is tried in the
 * same call. The untimed retry_drain ignores deadlines entirely. now_us is the
 * caller's monotonic clock; the library never reads a clock itself. INVALID
 * also on a NULL backoff, base_us of 0, or max_us below base_us. */
BreakRuntimeError break_runtime_metrics_retry_drain_timed(
    BreakRuntimeMetricsRetryQueue *queue,
    BreakRuntimeMetricsRetrySendFn send,
    void *user,
    u32 max_sends,
    u32 max_attempts,
    const BreakRuntimeMetricsRetryBackoff *backoff,
    u64 now_us,
    BreakRuntimeMetricsRetryDrainResult *out_result);

/* Serializes the queue's pending entries, oldest first, so a backlog can be
 * written to disk and survives a restart. The image is self-describing and
 * checksummed: "BRKR1" (5), then a little-endian u32 entry count, then each
 * entry as little-endian u32 attempts, little-endian u32 payload length, and
 * the payload bytes, then a little-endian CRC-32 (ISO-HDLC) over everything
 * before it. Deadlines are not saved: a restored entry is due immediately.
 * Counters other than the per-entry attempt count are process-local and are
 * not saved.
 *
 * OVERLOAD when `capacity` is below the image size: *out_len gets the required
 * size and `out` is untouched. OK writes exactly that many bytes and sets
 * *out_len. INVALID on NULL queue/out_len, or NULL out with non-zero capacity.
 * REJECTED off the owner thread. */
BreakRuntimeError break_runtime_metrics_retry_save(
    BreakRuntimeMetricsRetryQueue *queue,
    void *out,
    usize capacity,
    usize *out_len);

/* Appends the entries of a save image to the queue, oldest first, after
 * whatever it already holds. The image is validated completely before the
 * queue changes: a bad magic, a truncated image, a count or length that
 * overruns the buffer, trailing bytes, a payload larger than the queue's
 * max_payload_bytes, or a CRC mismatch is INVALID with *out_loaded = 0 and the
 * queue untouched. When the queue fills up, the oldest entries are dropped and
 * counted in dropped_oldest, exactly as enqueue does. Loaded entries keep their
 * attempt counts; their deadline is 0, so they are due at once.
 * *out_loaded receives the number of entries in the image.
 * INVALID on NULL queue/bytes/out_loaded, or zero len. REJECTED off the owner
 * thread or while a drain callback is running. */
BreakRuntimeError break_runtime_metrics_retry_load(
    BreakRuntimeMetricsRetryQueue *queue,
    const void *bytes,
    usize len,
    u32 *out_loaded);

/* Per-channel retry router (design: docs/design/runtime_metrics.md section 34).
 *
 * One retry queue serves one destination. Putting metrics snapshots and alert
 * transitions in the same queue would let a dead /metrics collector hold the
 * FIFO head and starve /alerts. The router keeps one queue per channel, each
 * with its own send callback, attempt limit and backoff, and drains all of
 * them in one call: a failure or a pending backoff on one channel never stops
 * another. Ownership, threading and reentrancy are those of the queues it
 * owns (owner-thread only; no enqueue from inside a send callback). */
typedef struct BreakRuntimeMetricsRetryRouter BreakRuntimeMetricsRetryRouter; /* opaque */

#define BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS 8u

typedef struct BreakRuntimeMetricsRetryChannelConfig {
    BreakRuntimeMetricsRetryConfig queue; /* validated as by retry_create */
    BreakRuntimeMetricsRetrySendFn send;  /* required */
    void *user;                           /* passed to send */
    u32 max_sends;                        /* per drain; >= 1 */
    u32 max_attempts;                     /* 0 = never give up */
    BreakRuntimeMetricsRetryBackoff backoff; /* validated as by drain_timed */
} BreakRuntimeMetricsRetryChannelConfig;

typedef struct BreakRuntimeMetricsRetryRouterConfig {
    const BreakRuntimeMetricsRetryChannelConfig *channels;
    u32 channel_count; /* 1..BREAK_RUNTIME_METRICS_RETRY_MAX_CHANNELS */
} BreakRuntimeMetricsRetryRouterConfig;

typedef struct BreakRuntimeMetricsRetryRouterResult {
    u32 delivered;         /* summed over channels */
    u32 abandoned;
    u32 failed;
    u32 deferred_channels; /* channels whose head was not yet due */
} BreakRuntimeMetricsRetryRouterResult;

/* Validates every channel (send set, max_sends >= 1, the backoff and queue
 * rules of drain_timed and retry_create) before allocating anything. INVALID
 * with *out = NULL on any bad channel, a NULL config/out/channels, or a
 * channel_count of 0 or above the maximum; OOM on allocation failure. The
 * configuration is copied; the caller's array need not outlive the call. */
BreakRuntimeError break_runtime_metrics_retry_router_create(
    const BreakRuntimeMetricsRetryRouterConfig *config,
    BreakRuntimeMetricsRetryRouter **out);
void break_runtime_metrics_retry_router_destroy(BreakRuntimeMetricsRetryRouter *router);

/* Enqueues into channel `channel` with the queue's rules. INVALID on NULL
 * router or a channel index not below channel_count; otherwise returns what
 * retry_enqueue returns for that channel's queue. */
BreakRuntimeError break_runtime_metrics_retry_router_enqueue(
    BreakRuntimeMetricsRetryRouter *router,
    u32 channel,
    const void *bytes,
    usize len);

/* Runs drain_timed on every channel at `now_us`, in channel order, and sums
 * the per-channel counts into *out_result. A channel's error is reported only
 * after every channel has been drained, so one channel cannot stop another;
 * the first such error is returned. INVALID on NULL router/out_result. */
BreakRuntimeError break_runtime_metrics_retry_router_drain(
    BreakRuntimeMetricsRetryRouter *router,
    u64 now_us,
    BreakRuntimeMetricsRetryRouterResult *out_result);

/* The earliest head deadline across all non-empty channels (0 = some channel
 * is due now). STALE when every channel is empty. INVALID on NULL args. */
BreakRuntimeError break_runtime_metrics_retry_router_next_due(
    BreakRuntimeMetricsRetryRouter *router,
    u64 *out_due_us);

/* Counters of channel `channel`'s queue. INVALID on NULL args or a bad index. */
BreakRuntimeError break_runtime_metrics_retry_router_stats(
    BreakRuntimeMetricsRetryRouter *router,
    u32 channel,
    BreakRuntimeMetricsRetryStats *out_stats);

/* The head entry's backoff deadline in *out_due_us (0 = due now), so an owner
 * can sleep until then instead of polling. STALE when the queue is empty (no
 * output written). INVALID on NULL arguments; REJECTED off the owner thread. */
BreakRuntimeError break_runtime_metrics_retry_next_due(
    BreakRuntimeMetricsRetryQueue *queue,
    u64 *out_due_us);
