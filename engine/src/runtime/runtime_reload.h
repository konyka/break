#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

/* Runtime Core formal hot-reload coordinator (design:
 * docs/design/runtime_hot_reload.md §4-§6,
 * docs/design/runtime_thread_model.md §5-§6,
 * docs/design/runtime_overview.md §6-§7).
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * This is the formal staging/validate/commit state machine for asset hot
 * reload. It does NOT modify the existing compatibility watcher/reload code
 * (`engine/src/platform/filewatch.c`, `engine/src/asset/hotreload.c`): those
 * integrate ONLY through the two seams below.
 *  - FileWatch seam: a consumer's filewatch callback calls
 *    break_runtime_reload_notify_file_event() with the changed path (copied
 *    into bounded storage; no borrowed pointer crosses the callback). The
 *    callback performs no load, no validation, and no owner-state mutation.
 *  - hotreload seam: the consumer's commit hook (BreakRuntimeReloadHooks
 *    .commit) runs ONLY on the owner thread inside
 *    break_runtime_reload_commit_owner() and performs the actual swap
 *    (failed-keep-old is preserved: a non-OK commit leaves the old version
 *    untouched). Workers never touch the swap.
 *
 * NO Lua VM exists in this task: Lua module reload is a Stage 3 dependency
 * (docs/design/runtime_hot_reload.md §3.3/§9). The validate/commit hooks are
 * the only staging surface; a Lua staging VM is out of scope here.
 *
 * Pipeline (per request): QUEUED -> LOADING (worker reads the path through
 * the borrowed VFS into an owned staging copy) -> VALIDATING (worker runs the
 * pure validate hook, then parks the staging bytes on a bounded commit queue)
 * -> owner-thread commit_owner() runs the commit hook -> COMMITTED.
 * Failures: load/validate/commit failure or staging oversize ->
 * FAILED_KEEP_OLD (the old version stays live; staging is discarded);
 * cancel() -> CANCELLED; processing deadline expired before the load ->
 * TIMEOUT; staging allocation failure -> OOM.
 *
 * Request handle: an opaque u64 with a slot generation in the high bits
 * (mirroring the IO facade's id+generation discipline). 0 is never a valid
 * handle; on any failure `out_request` is set to 0. A handle goes STALE once
 * its terminal state has been consumed by poll() (the slot generation is
 * bumped at consumption) or when the handle never referred to a live slot.
 *
 * Exactly-once completion: poll() is NON-consuming for the non-terminal
 * states (LOADING/VALIDATING) and CONSUMING for every terminal state
 * (COMMITTED/FAILED_KEEP_OLD/CANCELLED/TIMEOUT/OOM): the terminal state is
 * delivered exactly once, the slot is released, and a later poll/cancel with
 * the same handle returns BREAK_RUNTIME_STALE.
 *
 * Coalescing: file events for a path already present in the bounded event
 * queue merge into one pending hint (stats.events_coalesced). request() for a
 * path with a live non-terminal request merges into the existing handle
 * (stats.merged). pump_events() defers an event whose path has a live
 * non-terminal request (head-of-line, retried by the next pump) so a burst
 * during an in-flight reload produces a follow-up reload of the latest
 * content instead of writing new bytes into old staging.
 *
 * Backpressure: producers NEVER wait for capacity. Event queue full (new
 * path) -> OVERLOAD. Live-request count at capacity OR the pending ring
 * physically full -> OVERLOAD (dual gate, mirroring the IO facade: a request
 * cancelled while QUEUED frees its live slot immediately but its ring slot
 * only at claim/drain). Commit queue full at publish -> the request finalizes
 * FAILED_KEEP_OLD and stats.commit_overloads counts it; the default commit
 * capacity equals the request capacity so this requires a deliberately
 * smaller configured commit queue.
 *
 * Threads: request/poll/cancel/notify_file_event/stats/shutdown are safe from
 * any thread (mutex-protected, non-blocking). pump_events and commit_owner
 * are OWNER-THREAD-ONLY (the creating thread); a call from any other thread
 * returns REJECTED. validate hooks run on coordinator worker threads and must
 * be pure staging checks (no owner state, no World/Lua/RHI mutation); the
 * commit hook runs on the owner thread only.
 *
 * Shutdown: shutdown(timeout_ms) closes admission (request/notify -> CLOSED),
 * finalizes every still-QUEUED/LOADING/VALIDATING request as CANCELLED
 * (in-flight worker results are dropped on the stale epoch, counted in
 * stats.stale_drops), clears pending events/commit commands, then stops the
 * workers with the bounded runtime_thread stop contract. On a worker timeout
 * it returns BREAK_RUNTIME_TIMEOUT and RETAINS live ownership (state
 * STOPPING; nothing freed; a later shutdown resumes). The same TIMEOUT rule
 * applies while an owner-thread commit is in flight (commit_owner drops the
 * facade mutex around the commit hook): shutdown retains live ownership
 * instead of reaching STOPPED, so a destroy() from another thread can never
 * free the facade under the owner thread's feet — retry shutdown after
 * commit_owner has returned. Terminal states stay pollable across shutdown.
 * destroy() requires a fully stopped facade;
 * destroying a live facade is a contract violation (test builds abort),
 * mirroring the thread/queue destroy rules.
 *
 * Error taxonomy:
 *   INVALID  — NULL argument, empty/over-long path, malformed config (cap
 *              above its hard bound, missing VFS or commit hook), byte/count
 *              overflow in the checked create arithmetic.
 *   REJECTED — pump_events/commit_owner from a non-owner thread; cancel of a
 *              request whose commit is already in flight on the owner thread
 *              or whose terminal state is a real result (non-CANCELLED).
 *   CLOSED   — request/notify after shutdown began.
 *   OVERLOAD — bounded queue/capacity full (see Backpressure); never blocks.
 *   STALE    — poll/cancel with a handle whose generation no longer names a
 *              live slot (consumed, or never valid).
 *   TIMEOUT  — shutdown budget expired with a worker still live, or an
 *              owner-thread commit still in flight at shutdown (ownership
 *              retained, retry allowed).
 *   OOM      — allocation failure at create. (A staging allocation failure
 *              during a request is delivered as the request's OOM state.)
 *
 * A cancel() failure cannot strand a request: cancel needs no allocation, so
 * QUEUED/LOADING/VALIDATING -> CANCELLED always succeeds (idempotent OK on an
 * already-CANCELLED, still-unconsumed request).
 */

typedef struct BreakRuntimeReload BreakRuntimeReload; /* opaque, caller-owned */
typedef struct VFS VFS; /* borrowed mount source; vfs.h stays out of this header */
typedef struct BreakRuntimeProfiler BreakRuntimeProfiler; /* borrowed, optional */

/* Opaque request handle: u64 with a slot generation (see header contract). */
typedef u64 BreakRuntimeReloadRequest;

typedef enum BreakRuntimeReloadState {
    BREAK_RUNTIME_RELOAD_LOADING = 0,
    BREAK_RUNTIME_RELOAD_VALIDATING,
    BREAK_RUNTIME_RELOAD_COMMITTED,
    BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD,
    BREAK_RUNTIME_RELOAD_CANCELLED,
    BREAK_RUNTIME_RELOAD_TIMEOUT,
    BREAK_RUNTIME_RELOAD_OOM
} BreakRuntimeReloadState;

#define BREAK_RUNTIME_RELOAD_MAX_PATH 260u
#define BREAK_RUNTIME_RELOAD_DEFAULT_WORKERS 2u
#define BREAK_RUNTIME_RELOAD_MAX_WORKERS 4u
#define BREAK_RUNTIME_RELOAD_DEFAULT_REQUEST_CAPACITY 64u
#define BREAK_RUNTIME_RELOAD_MAX_REQUEST_CAPACITY 1024u
#define BREAK_RUNTIME_RELOAD_DEFAULT_EVENT_CAPACITY 256u
#define BREAK_RUNTIME_RELOAD_MAX_EVENT_CAPACITY 1024u
#define BREAK_RUNTIME_RELOAD_MAX_COMMIT_CAPACITY 1024u

/* Per-request staging byte budget (worker-side staging copy). Deliberately
 * matched to the IO facade blob budget; reads above it finalize
 * FAILED_KEEP_OLD. Overridable at compile time. */
#ifndef BREAK_RUNTIME_RELOAD_MAX_STAGING_BYTES
#define BREAK_RUNTIME_RELOAD_MAX_STAGING_BYTES (16u * 1024u * 1024u)
#endif

/* Staging hooks. `user` is borrowed and must outlive the facade.
 *  - validate: runs on a coordinator WORKER thread; must be a pure staging
 *    check over the borrowed bytes (no owner state, no World/Lua/RHI
 *    mutation). NULL selects accept-all. Any non-OK return finalizes the
 *    request FAILED_KEEP_OLD.
 *  - commit: REQUIRED. Runs ONLY on the owner thread inside
 *    commit_owner(); `staging_bytes`/`staging_size` are borrowed for the
 *    duration of the call. OK -> COMMITTED; any non-OK return ->
 *    FAILED_KEEP_OLD (the old version must stay live; the hook simply did
 *    not swap). The hook must not retain the byte pointer. */
typedef struct BreakRuntimeReloadHooks {
    BreakRuntimeError (*validate)(const char *path, const void *staging_bytes,
                                  usize staging_size, void *user);
    BreakRuntimeError (*commit)(const char *path, const void *staging_bytes,
                                usize staging_size, void *user);
    void *user;
} BreakRuntimeReloadHooks;

typedef struct BreakRuntimeReloadConfig {
    VFS *vfs;                       /* borrowed, required; outlives the facade */
    BreakRuntimeReloadHooks hooks;  /* commit required; validate may be NULL */
    BreakRuntimeProfiler *profiler; /* borrowed, may be NULL; lifecycle instants */
    u32 worker_count;               /* 0 = BREAK_RUNTIME_RELOAD_DEFAULT_WORKERS */
    u32 request_capacity;           /* 0 = default; live request slots */
    u32 event_capacity;             /* 0 = default; bounded file-event hints */
    u32 commit_capacity;            /* 0 = request_capacity; bounded commit queue */
    u32 request_timeout_ms;         /* 0 = disabled; per-request processing budget */
} BreakRuntimeReloadConfig;

typedef struct BreakRuntimeReloadStats {
    u64 requested;         /* successful request admissions (request + pump) */
    u64 merged;            /* request() merged into a live same-path request */
    u64 events_notified;   /* file events enqueued */
    u64 events_coalesced;  /* file events merged into a pending same-path hint */
    u64 event_overloads;   /* notify rejected OVERLOAD (event queue full) */
    u64 events_deferred;   /* pump head-of-line deferrals (live same-path request) */
    u64 committed;         /* COMMITTED terminal states published */
    u64 failed_keep_old;   /* FAILED_KEEP_OLD terminal states published */
    u64 cancelled;         /* CANCELLED terminal states published */
    u64 timed_out;         /* TIMEOUT terminal states published */
    u64 oom;               /* OOM terminal states published */
    u64 request_overloads; /* admissions rejected OVERLOAD */
    u64 commit_overloads;  /* commit publishes rejected OVERLOAD (FAILED_KEEP_OLD) */
    u64 closed_rejects;    /* request/notify rejected CLOSED */
    u64 stale_rejects;     /* poll/cancel rejected STALE */
    u64 stale_drops;       /* worker/commit results dropped on a stale epoch */
    u32 active;            /* live requests right now (armed, non-terminal);
                            * every terminal publication frees the admission
                            * slot; the table slot frees at poll-consume */
    u32 high_water;        /* maximum live requests observed */
} BreakRuntimeReloadStats;

/* `config` must be valid (VFS + commit hook required). On success
 * *out_reload is newly owned and RUNNING (workers spawned); on failure it is
 * set to NULL. Count AND byte checks run before every allocation. The calling
 * thread becomes the owner thread for pump_events/commit_owner. */
BreakRuntimeError break_runtime_reload_create(
    const BreakRuntimeReloadConfig *config,
    BreakRuntimeReload **out_reload);

/* Bounded shutdown (see header contract). TIMEOUT retains live ownership;
 * retry resumes. OK is idempotent. INVALID on NULL. */
BreakRuntimeError break_runtime_reload_shutdown(
    BreakRuntimeReload *reload,
    u32 timeout_ms);

/* Releases the facade. NULL is a no-op. Legal only after a completed
 * shutdown (workers STOPPED); destroying a live facade is a contract
 * violation (test builds abort). */
void break_runtime_reload_destroy(BreakRuntimeReload *reload);

/* Starts a reload of `path`, or merges into a live same-path request
 * (returning the existing handle). Non-blocking; never waits for capacity.
 * On success *out_request is the opaque handle; on failure it is 0. */
BreakRuntimeError break_runtime_reload_request(
    BreakRuntimeReload *reload,
    const char *path,
    BreakRuntimeReloadRequest *out_request);

/* Non-blocking state query. Non-terminal states are reported without
 * consuming; the first poll observing a terminal state delivers it exactly
 * once and releases the slot (the handle goes STALE afterwards). STALE for a
 * dead/foreign handle; INVALID on NULL arguments. Legal across shutdown. */
BreakRuntimeError break_runtime_reload_poll(
    BreakRuntimeReload *reload,
    BreakRuntimeReloadRequest request,
    BreakRuntimeReloadState *out_state);

/* QUEUED/LOADING/VALIDATING -> CANCELLED (published at once, pollable via
 * the same handle); a late worker result is dropped on the stale epoch.
 * Idempotent OK on an already-CANCELLED unconsumed request. REJECTED when the
 * commit is already in flight on the owner thread or a non-CANCELLED
 * terminal state exists. STALE for a dead/foreign handle. Never allocates. */
BreakRuntimeError break_runtime_reload_cancel(
    BreakRuntimeReload *reload,
    BreakRuntimeReloadRequest request);

/* FileWatch seam (see header): records a bounded, owned change hint for
 * `path`. Safe from any producer thread; never blocks; same-path hints
 * coalesce; full queue -> OVERLOAD (the hint stream is lossy by design, like
 * the underlying watcher overflow contract). */
BreakRuntimeError break_runtime_reload_notify_file_event(
    BreakRuntimeReload *reload,
    const char *path);

/* OWNER THREAD ONLY (REJECTED otherwise). Converts up to `max_events` queued
 * file-event hints into requests (same admission gates as request(); a hint
 * whose path has a live non-terminal request defers the whole pump at the
 * head of the queue — retry next tick). *out_count receives the number of
 * requests started. CLOSED after shutdown began. */
BreakRuntimeError break_runtime_reload_pump_events(
    BreakRuntimeReload *reload,
    u32 max_events,
    u32 *out_count);

/* OWNER THREAD ONLY (REJECTED otherwise). Runs up to `max_commits` pending
 * commit hooks (owner-thread swap; see BreakRuntimeReloadHooks.commit) and
 * publishes COMMITTED / FAILED_KEEP_OLD. *out_count receives the number of
 * commits executed. Stale commands (cancelled/shutdown-drained requests) are
 * skipped and counted in stats.stale_drops. Legal across shutdown to drain
 * validated staging. */
BreakRuntimeError break_runtime_reload_commit_owner(
    BreakRuntimeReload *reload,
    u32 max_commits,
    u32 *out_count);

/* Observability snapshot. INVALID on NULL arguments. Legal in any state. */
BreakRuntimeError break_runtime_reload_stats(
    BreakRuntimeReload *reload,
    BreakRuntimeReloadStats *out_stats);

/* Diagnostic names ("LOADING", ...); never NULL, unknown values map to
 * "UNKNOWN". Pure string conversion, no allocation. */
const char *break_runtime_reload_state_name(BreakRuntimeReloadState state);
