#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>
#include <runtime/runtime_message.h>

/* Runtime Core bounded MPSC message queue (design:
 * docs/design/runtime_message_model.md §5.2/§6, docs/design/runtime_thread_model.md
 * §6, docs/design/runtime_overview.md §6).
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * Contract:
 *  - Bounded ring of owned messages, FIFO. Multiple producer threads may
 *    enqueue concurrently; a single consumer drains (MPSC). All internal
 *    state is mutex-protected; producers never wait for capacity.
 *  - Ownership transfers at enqueue: on BREAK_RUNTIME_OK the queue owns the
 *    message; on ANY error the caller keeps ownership and must release it.
 *    poll/wait transfer ownership to the consumer, who must release.
 *  - Full queue -> non-blocking BREAK_RUNTIME_OVERLOAD, never inline, never
 *    blocking. Reserved control capacity: `reserved_control` slots are only
 *    usable by messages flagged BREAK_RUNTIME_MESSAGE_FLAG_CONTROL, so
 *    control (shutdown/close-watermark/failure) still enqueues when the data
 *    region is full.
 *  - Generation: producers pass the generation they observed via
 *    break_runtime_queue_generation(); a mismatch means the producer's epoch
 *    is stale -> BREAK_RUNTIME_STALE. break_runtime_queue_advance_generation()
 *    models a new snapshot/connection epoch; close() also bumps it.
 *  - Shutdown wakeup: close() stops admission and wakes every waiter;
 *    wait() drains remaining messages (OK) and reports BREAK_RUNTIME_CLOSED
 *    once the closed queue is empty. close() is idempotent.
 *  - destroy() releases every still-queued owned message. The caller must
 *    quiesce producers/consumers first (coordinator phase order:
 *    stop_producers -> close -> drain -> destroy); destroy with concurrent
 *    users is a contract violation.
 *
 * Error taxonomy:
 *   INVALID  — NULL argument or malformed config (capacity above the hard
 *              bound, reserved_control > capacity, byte-overflow budget).
 *   OVERLOAD — no slot for the message's class (data region full, or the
 *              whole queue full for control).
 *   STALE    — expected_generation != current generation.
 *   CLOSED   — enqueue after close; poll/wait on a closed, drained queue.
 *   OOM      — allocation failure at create.
 */

typedef struct BreakRuntimeQueue BreakRuntimeQueue; /* opaque, owned by caller */

#define BREAK_RUNTIME_QUEUE_DEFAULT_CAPACITY 256u
#define BREAK_RUNTIME_QUEUE_MAX_CAPACITY 4096u

typedef struct BreakRuntimeQueueConfig {
    /* 0 selects BREAK_RUNTIME_QUEUE_DEFAULT_CAPACITY; values above
     * BREAK_RUNTIME_QUEUE_MAX_CAPACITY are rejected with INVALID. */
    u32 capacity;
    /* Slots reserved for BREAK_RUNTIME_MESSAGE_FLAG_CONTROL messages.
     * Must be <= the effective capacity. 0 = no reserved control capacity. */
    u32 reserved_control;
} BreakRuntimeQueueConfig;

typedef struct BreakRuntimeQueueStats {
    u64 enqueued;         /* successful enqueues */
    u64 dequeued;         /* successful polls/waits */
    u64 overload_rejects; /* enqueue attempts rejected OVERLOAD */
    u64 stale_rejects;    /* enqueue attempts rejected STALE */
    u64 closed_rejects;   /* enqueue attempts rejected CLOSED */
    u64 high_water;       /* maximum occupied slots observed */
} BreakRuntimeQueueStats;

/* `config` may be NULL (defaults). On success *out_queue is newly owned; on
 * failure it is set to NULL. Count and byte checks run before allocation. */
BreakRuntimeError break_runtime_queue_create(
    const BreakRuntimeQueueConfig *config,
    BreakRuntimeQueue **out_queue);

/* Releases the queue and every owned message still inside. NULL is a no-op.
 * No concurrent users may exist (see header contract). */
void break_runtime_queue_destroy(BreakRuntimeQueue *queue);

/* Stops admission, advances the generation, and wakes all waiters.
 * Idempotent; NULL is a no-op. Queued messages remain drainable. */
void break_runtime_queue_close(BreakRuntimeQueue *queue);

/* Current generation; 0 for NULL. */
u64 break_runtime_queue_generation(BreakRuntimeQueue *queue);

/* Advances the generation (new epoch). Returns the new generation, 0 on
 * NULL. */
u64 break_runtime_queue_advance_generation(BreakRuntimeQueue *queue);

/* Enqueues an owned message if `expected_generation` is current and the
 * message's class has a slot. On OK ownership transfers to the queue; on any
 * error the caller keeps ownership. Never blocks, never executes payloads. */
BreakRuntimeError break_runtime_queue_enqueue(
    BreakRuntimeQueue *queue,
    BreakRuntimeOwnedMessage *message,
    u64 expected_generation);

/* Non-blocking dequeue, FIFO. OK with *out_message set, or OK with
 * *out_message == NULL when the queue is empty but open; CLOSED when closed
 * and drained. On OK with a message, ownership transfers to the caller. */
BreakRuntimeError break_runtime_queue_poll(
    BreakRuntimeQueue *queue,
    BreakRuntimeOwnedMessage **out_message);

/* Blocking dequeue, FIFO: waits while the queue is empty and open. Returns
 * OK with a message, or CLOSED once the queue is closed and drained. Every
 * close() wakes all waiters (shutdown wakeup). INVALID on NULL arguments. */
BreakRuntimeError break_runtime_queue_wait(
    BreakRuntimeQueue *queue,
    BreakRuntimeOwnedMessage **out_message);

/* Snapshot of the observability counters (design: "high-water/drop/overload/
 * retry 统计"). INVALID on NULL arguments. */
BreakRuntimeError break_runtime_queue_stats(
    BreakRuntimeQueue *queue,
    BreakRuntimeQueueStats *out_stats);
