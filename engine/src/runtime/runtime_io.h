#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>
#include <runtime/runtime_message.h>

/* Runtime Core formal IO/VFS facade (design:
 * docs/design/runtime_asset_streaming.md §4.2/§4.3/§6,
 * docs/design/runtime_thread_model.md §5.3/§6-§7).
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * This is the formal completion bridge beside the legacy async loader: the
 * compatibility loader (`engine/src/asset/async_loader.c`, including its
 * completion-queue wait behaviour) is byte-for-byte UNCHANGED. The facade
 * reads through a borrowed VFS on its own formal worker threads
 * (runtime_thread.h) and delivers exactly one OWNED completion per request
 * as a BreakRuntimeOwnedMessage. There are NO callbacks anywhere in this
 * API, so no GameThread callback can ever fire on an IO worker.
 *
 * Lifecycle: the facade is a module-level singleton (the brief's request
 * APIs carry no context pointer).
 *  - init() validates the config (count AND byte checks before allocation),
 *    spawns `worker_count` formal threads. init() while RUNNING or STOPPING
 *    -> REJECTED. A new init after a successful shutdown is legal only when
 *    no request of the previous lifecycle is still live (else REJECTED) —
 *    this keeps the previous facade (which late polls/releases still touch)
 *    un-freed until its last request is released.
 *  - shutdown(timeout_ms): closes admission (submit -> CLOSED), interrupts
 *    every blocked completion wait (-> CLOSED), finalizes still-queued
 *    requests as CANCELLED completions, then stops workers with the bounded
 *    runtime_thread stop contract. On any worker timeout it returns
 *    BREAK_RUNTIME_TIMEOUT and RETAINS live ownership (state STOPPING;
 *    nothing freed; a later shutdown resumes). Full stop -> STOPPED.
 *  - Request objects stay valid across shutdown: a completion published
 *    before, during, or after shutdown remains pollable until consumed;
 *    break_runtime_io_request_release() always works.
 *
 * Request contract:
 *  - submit() copies the path into bounded storage, stamps the opaque
 *    request with a u64 id and the current facade generation, and NEVER
 *    waits for capacity: live-request count at capacity -> OVERLOAD.
 *  - `deadline_ns` is an absolute timespec_get(TIME_UTC) nanosecond deadline;
 *    0 disables it. A request whose deadline has expired before its read
 *    starts finalizes as TIMED_OUT without touching the VFS.
 *  - cancel() transitions QUEUED/READING -> CANCELLED (bumping the request
 *    generation) and publishes the CANCELLED completion itself. A worker
 *    that later finishes a read for such a request detects the stale
 *    generation, releases its own bytes, and does NOT publish (counted as
 *    stale_drops): exactly one completion per request, always.
 *  - poll_completion() is non-blocking; wait_completion() blocks up to
 *    `timeout_ms` (deadline-interruptible -> TIMEOUT, completion NOT
 *    consumed, retry allowed) and is shutdown-interruptible (-> CLOSED as
 *    soon as shutdown begins, even if a completion might arrive later).
 *    A successful poll/wait transfers the completion message ownership to
 *    the caller (release with break_runtime_message_release()); a consumed
 *    completion is never delivered twice.
 *  - request_release() releases the caller's reference; an unconsumed
 *    completion is released with the request. NULL is a no-op. Double
 *    release (or a foreign pointer) is a contract violation: test builds
 *    (BREAK_RUNTIME_TESTING) abort with a diagnostic, mirroring the owned
 *    message registry.
 *
 * Error taxonomy:
 *   INVALID  — NULL argument, empty/over-long path, nonzero flags (no flags
 *              are defined yet; fail-closed for forward compatibility), or
 *              malformed config.
 *   REJECTED — submit before init; init while RUNNING/STOPPING; init while
 *              a previous lifecycle still has live requests; cancel of an
 *              already-completed request.
 *   CLOSED   — submit after shutdown began; wait_completion interrupted by
 *              shutdown.
 *   OVERLOAD — live-request capacity reached at submit; a read result above
 *              BREAK_RUNTIME_IO_MAX_FILE_BYTES (FAILED completion).
 *   TIMEOUT  — wait_completion budget expired; shutdown budget expired.
 *   OOM      — allocation failure.
 *   FAILED   — worker spawn failure at init; VFS read failure (FAILED
 *              completion).
 */

typedef struct VFS VFS; /* borrowed mount source; vfs.h stays out of this header */

typedef struct BreakRuntimeIoRequest BreakRuntimeIoRequest; /* opaque, caller-owned */

#define BREAK_RUNTIME_IO_DEFAULT_WORKERS 2u
#define BREAK_RUNTIME_IO_MAX_WORKERS 8u
#define BREAK_RUNTIME_IO_DEFAULT_REQUEST_CAPACITY 256u
#define BREAK_RUNTIME_IO_MAX_REQUEST_CAPACITY 1024u
/* Bounded path copy; identical to VFS_MAX_PATH. */
#define BREAK_RUNTIME_IO_MAX_PATH 260u

/* Per-request read budget. The VFS layer keeps its own 128 MiB fail-closed
 * cap; the formal facade's blob budget is deliberately smaller (design:
 * docs/design/runtime_asset_streaming.md §4.2 — blob budgets are separate
 * from the 16 MiB message assembly cap; this is the IO blob budget). */
#ifndef BREAK_RUNTIME_IO_MAX_FILE_BYTES
#define BREAK_RUNTIME_IO_MAX_FILE_BYTES (16u * 1024u * 1024u)
#endif

/* Message kind of every IO completion (BreakRuntimeMessageView.kind). */
#define BREAK_RUNTIME_IO_COMPLETION_KIND 0x4F49u /* 'I' | 'O'<<8 */
#define BREAK_RUNTIME_IO_COMPLETION_VERSION 1u

typedef struct BreakRuntimeIoConfig {
    VFS *vfs;             /* borrowed; must outlive the facade lifecycle */
    u32 worker_count;     /* 0 = BREAK_RUNTIME_IO_DEFAULT_WORKERS */
    u32 request_capacity; /* 0 = BREAK_RUNTIME_IO_DEFAULT_REQUEST_CAPACITY */
} BreakRuntimeIoConfig;

typedef enum BreakRuntimeIoCompletionState {
    BREAK_RUNTIME_IO_COMPLETED = 0, /* bytes valid */
    BREAK_RUNTIME_IO_FAILED,        /* VFS read / OOM / oversize (see error) */
    BREAK_RUNTIME_IO_CANCELLED,     /* cancel() or shutdown queue drain */
    BREAK_RUNTIME_IO_TIMED_OUT      /* deadline expired before the read */
} BreakRuntimeIoCompletionState;

/* Parsed view of a completion message. `bytes` is BORROWED: it points into
 * the completion message payload and is valid until the message is
 * released. Everything else is copied out. */
typedef struct BreakRuntimeIoCompletion {
    u64 request_id;
    u64 generation;     /* request generation at publish time */
    u32 state;          /* BreakRuntimeIoCompletionState */
    u32 error;          /* BreakRuntimeError; OK for COMPLETED/CANCELLED */
    const void *bytes;  /* borrowed; NULL when byte_size == 0 */
    u64 byte_size;
} BreakRuntimeIoCompletion;

typedef struct BreakRuntimeIoStats {
    u64 submitted;        /* successful submits */
    u64 completed;        /* COMPLETED completions published */
    u64 failed;           /* FAILED completions published */
    u64 cancelled;        /* CANCELLED completions published */
    u64 timed_out;        /* TIMED_OUT completions published */
    u64 overload_rejects; /* submits rejected OVERLOAD */
    u64 closed_rejects;   /* submits rejected CLOSED */
    u64 stale_drops;      /* worker results dropped for stale generation */
    u64 bytes_published;  /* payload bytes handed to consumers via publish */
    u32 active;           /* live requests right now */
    u32 high_water;       /* maximum live requests observed */
} BreakRuntimeIoStats;

BreakRuntimeError break_runtime_io_init(const BreakRuntimeIoConfig *config);
BreakRuntimeError break_runtime_io_shutdown(u32 timeout_ms);

/* On success *out_request is a newly owned opaque handle (caller must
 * release); on any failure it is set to NULL. Never waits for capacity. */
BreakRuntimeError break_runtime_io_submit(
    BreakRuntimeIoRequest **out_request,
    const char *path,
    u32 flags,
    u64 deadline_ns);

/* QUEUED/READING -> CANCELLED; publishes the CANCELLED completion.
 * Idempotent on an already-cancelled request (OK). REJECTED when a
 * non-cancellation completion already exists. OOM leaves the request
 * uncancelled (retry allowed). */
BreakRuntimeError break_runtime_io_cancel(BreakRuntimeIoRequest *request);

/* Non-blocking completion take. OK with *out_completion set (ownership
 * transfers; exactly once) or OK with *out_completion == NULL when no
 * completion has been published yet. INVALID on NULL arguments. */
BreakRuntimeError break_runtime_io_poll_completion(
    BreakRuntimeIoRequest *request,
    BreakRuntimeOwnedMessage **out_completion);

/* Blocking completion take: waits while no completion is published.
 * OK transfers ownership exactly once; TIMEOUT leaves the completion
 * unconsumed (retry allowed); CLOSED when shutdown begins first. */
BreakRuntimeError break_runtime_io_wait_completion(
    BreakRuntimeIoRequest *request,
    u32 timeout_ms,
    BreakRuntimeOwnedMessage **out_completion);

/* Releases the caller's request reference. NULL is a no-op. Double release
 * (or a foreign pointer) is a contract violation: test builds abort. */
void break_runtime_io_request_release(BreakRuntimeIoRequest *request);

/* Parses and validates a completion message (kind/version/size). The view
 * borrows the byte pointer from the message. INVALID on malformed input. */
BreakRuntimeError break_runtime_io_completion_view(
    const BreakRuntimeOwnedMessage *completion_message,
    BreakRuntimeIoCompletion *out_completion);

/* Facade observability snapshot. INVALID on NULL argument or before any
 * init; remains queryable after shutdown. */
BreakRuntimeError break_runtime_io_stats(BreakRuntimeIoStats *out_stats);
