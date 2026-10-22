#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>
#include <runtime/runtime_message.h>
#include <task/task.h>

/* Runtime Core formal task facade (design:
 * docs/design/runtime_thread_model.md §5 "Task" / §6.1-§6.2,
 * docs/design/runtime_overview.md §6).
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * This is a SEPARATE formal API over the legacy TaskSystem — the legacy
 * `task_submit`/queue-full INLINE fallback is a compatibility fact and stays
 * byte-for-byte unchanged. The formal facade owns its own bounded pending
 * queue and applies a reject/credit policy instead:
 *
 *  - submit() NEVER executes the task inline and never waits for capacity.
 *    Formal queue full -> BREAK_RUNTIME_OVERLOAD (counted).
 *  - Ownership transfers at submit: the queue node owns the payload message
 *    copy (an owned BreakRuntimeOwnedMessage, or NULL). Queue nodes never
 *    retain producer stack, World, Lua, Snowflake, or UI pointers — the only
 *    cross-thread cargo is the owned message.
 *  - Payload ownership at execution: the worker callback receives the owned
 *    payload and MUST release it (release(NULL) is a no-op). The trampoline
 *    context is owned by the queue node until drain hands it to the legacy
 *    system, which frees it after the callback returns.
 *  - drain() runs on the owner thread and forwards queued tasks FIFO into a
 *    borrowed legacy TaskSystem via task_submit_ex(), preserving priority.
 *    drain() never blocks; it stops early (leaving the rest queued) when the
 *    legacy external submit queue has no visible credit. That gate is
 *    best-effort: concurrent legacy submitters can still race it, in which
 *    case the legacy system's own documented fallback applies. The formal
 *    contract enforced here is at submit(): never-inline, OVERLOAD when the
 *    formal queue is full.
 *  - close() stops admission (idempotent); already-queued tasks stay
 *    drainable. destroy() releases queued payloads and trampoline contexts.
 *
 * Error taxonomy:
 *   INVALID  — NULL argument, priority >= TASK_PRIORITY_COUNT, malformed
 *              config.
 *   CLOSED   — submit after close.
 *   OVERLOAD — formal queue full (reject/credit policy, observable via
 *              stats).
 *   OOM      — allocation failure at create or submit.
 */

typedef struct BreakRuntimeTaskQueue BreakRuntimeTaskQueue; /* opaque, owned */

#define BREAK_RUNTIME_TASK_QUEUE_DEFAULT_CAPACITY 256u
#define BREAK_RUNTIME_TASK_QUEUE_MAX_CAPACITY 4096u

typedef struct BreakRuntimeTaskConfig {
    /* 0 selects BREAK_RUNTIME_TASK_QUEUE_DEFAULT_CAPACITY; values above
     * BREAK_RUNTIME_TASK_QUEUE_MAX_CAPACITY are rejected with INVALID. */
    u32 capacity;
} BreakRuntimeTaskConfig;

/* Worker callback. `payload` is owned by the callback and must be released
 * with break_runtime_message_release() (NULL payload is legal). */
typedef void (*BreakRuntimeTaskFn)(BreakRuntimeOwnedMessage *payload);

typedef struct BreakRuntimeTaskStats {
    u64 submitted;        /* successful submits */
    u64 forwarded;        /* tasks handed to the legacy system by drain */
    u64 overload_rejects; /* submits rejected OVERLOAD */
    u64 closed_rejects;   /* submits rejected CLOSED */
    u64 forward_rejects;  /* drain forwards rejected by the legacy system
                           * (TASK_HANDLE_INVALID); the task stays queued */
    u64 high_water;       /* maximum queued tasks observed */
} BreakRuntimeTaskStats;

/* `config` may be NULL (defaults). On success *out_queue is newly owned; on
 * failure it is set to NULL. Count and byte checks run before allocation. */
BreakRuntimeError break_runtime_task_queue_create(
    const BreakRuntimeTaskConfig *config,
    BreakRuntimeTaskQueue **out_queue);

/* Releases the queue, every queued payload message, and every trampoline
 * context. NULL is a no-op. No concurrent users may exist; tasks already
 * forwarded to the legacy system are legacy-owned and untouched. */
void break_runtime_task_queue_destroy(BreakRuntimeTaskQueue *queue);

/* Stops admission. Idempotent; NULL is a no-op. Queued tasks remain
 * drainable. */
void break_runtime_task_queue_close(BreakRuntimeTaskQueue *queue);

/* Enqueues (fn, payload, priority) without ever executing fn. On OK the
 * queue owns `payload`; on any error the caller keeps it. Non-blocking. */
BreakRuntimeError break_runtime_task_submit(
    BreakRuntimeTaskQueue *queue,
    BreakRuntimeTaskFn fn,
    BreakRuntimeOwnedMessage *payload,
    TaskPriority priority);

/* Owner-thread drain: forwards up to `max_tasks` queued tasks FIFO into the
 * borrowed legacy `ts` via task_submit_ex(). Stops early when the legacy
 * external submit queue shows no credit (best-effort gate) or when the queue
 * empties. *out_forwarded receives the number forwarded this call. Legal
 * after close() to drain the remainder.
 *
 * Legacy rejection policy (retain-and-stop): task_submit_ex() may return
 * TASK_HANDLE_INVALID without consuming the task (legacy task pool exhausted
 * and its heap-fallback allocation failed). Drain then stops immediately,
 * counts the attempt in stats.forward_rejects, and the task stays queued
 * with its owned payload intact — nothing is leaked or dropped, and a later
 * drain retries it in FIFO order. */
BreakRuntimeError break_runtime_task_queue_drain(
    BreakRuntimeTaskQueue *queue,
    TaskSystem *ts,
    u32 max_tasks,
    u32 *out_forwarded);

/* Snapshot of the observability counters. INVALID on NULL arguments. */
BreakRuntimeError break_runtime_task_queue_stats(
    BreakRuntimeTaskQueue *queue,
    BreakRuntimeTaskStats *out_stats);
