#include <runtime/runtime_queue.h>

#include <core/platform_thread.h>
#include <runtime/runtime_test_hooks.h>

#include <stdlib.h>
#include <string.h>

/* Bounded MPSC FIFO queue of owned messages. A single allocation holds the
 * queue object and its slot ring (tail). All mutable state lives under the
 * mutex; the condition variable exists only for wait() (producers never
 * wait: full is reported as non-blocking OVERLOAD). */

typedef struct RuntimeQueueSlot {
    BreakRuntimeOwnedMessage *message;
    u8 control;
} RuntimeQueueSlot;

struct BreakRuntimeQueue {
    PlatformMutex mutex;
    PlatformCond not_empty;
    RuntimeQueueSlot *slots; /* tail of this single allocation */
    u32 capacity;
    u32 reserved_control;
    u32 head;
    u32 count;
    u32 data_count; /* occupied slots holding non-control messages */
    u64 generation;
    bool closed;
    u64 enqueued;
    u64 dequeued;
    u64 overload_rejects;
    u64 stale_rejects;
    u64 closed_rejects;
    u64 high_water;
};

static usize runtime_queue_align_up(usize value, usize alignment)
{
    /* _Alignof results are always powers of two. */
    return (value + (alignment - 1u)) & ~(alignment - 1u);
}

BreakRuntimeError break_runtime_queue_create(
    const BreakRuntimeQueueConfig *config,
    BreakRuntimeQueue **out_queue)
{
    BreakRuntimeQueue *queue;
    usize header_bytes;
    usize bytes;
    u32 capacity = BREAK_RUNTIME_QUEUE_DEFAULT_CAPACITY;
    u32 reserved_control = 0u;

    if (!out_queue) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_queue = NULL;
    if (config) {
        if (config->capacity != 0u) {
            if (config->capacity > BREAK_RUNTIME_QUEUE_MAX_CAPACITY) {
                return BREAK_RUNTIME_INVALID;
            }
            capacity = config->capacity;
        }
        reserved_control = config->reserved_control;
    }
    if (reserved_control > capacity) {
        return BREAK_RUNTIME_INVALID;
    }

    /* Bounded capacity: count checked against the hard bound above; byte
     * check runs before allocation so a bad budget fails closed. */
    header_bytes = runtime_queue_align_up(sizeof(*queue),
                                          (usize)_Alignof(RuntimeQueueSlot));
    if ((usize)capacity > (SIZE_MAX - header_bytes) / sizeof(RuntimeQueueSlot)) {
        return BREAK_RUNTIME_INVALID;
    }
    bytes = header_bytes + (usize)capacity * sizeof(RuntimeQueueSlot);

    queue = break_runtime_test_calloc(bytes);
    if (!queue) {
        return BREAK_RUNTIME_OOM;
    }
    platform_mutex_init(&queue->mutex);
    platform_cond_init(&queue->not_empty);
    queue->slots = (RuntimeQueueSlot *)((char *)queue + header_bytes);
    queue->capacity = capacity;
    queue->reserved_control = reserved_control;
    queue->head = 0u;
    queue->count = 0u;
    queue->data_count = 0u;
    queue->generation = 1u;
    queue->closed = false;
    *out_queue = queue;
    return BREAK_RUNTIME_OK;
}

void break_runtime_queue_destroy(BreakRuntimeQueue *queue)
{
    u32 i;
    if (!queue) {
        return;
    }
    /* Contract: no concurrent producers/consumers at destroy (coordinator
     * phase order stop_producers -> close -> drain -> destroy). */
    for (i = 0; i < queue->count; i++) {
        RuntimeQueueSlot *slot =
            &queue->slots[(queue->head + i) % queue->capacity];
        break_runtime_message_release(slot->message);
    }
    platform_cond_destroy(&queue->not_empty);
    platform_mutex_destroy(&queue->mutex);
    free(queue);
}

void break_runtime_queue_close(BreakRuntimeQueue *queue)
{
    if (!queue) {
        return;
    }
    platform_mutex_lock(&queue->mutex);
    if (!queue->closed) {
        queue->closed = true;
        queue->generation++;
    }
    platform_cond_broadcast(&queue->not_empty);
    platform_mutex_unlock(&queue->mutex);
}

u64 break_runtime_queue_generation(BreakRuntimeQueue *queue)
{
    u64 generation;
    if (!queue) {
        return 0u;
    }
    platform_mutex_lock(&queue->mutex);
    generation = queue->generation;
    platform_mutex_unlock(&queue->mutex);
    return generation;
}

u64 break_runtime_queue_advance_generation(BreakRuntimeQueue *queue)
{
    u64 generation;
    if (!queue) {
        return 0u;
    }
    platform_mutex_lock(&queue->mutex);
    queue->generation++;
    generation = queue->generation;
    platform_mutex_unlock(&queue->mutex);
    return generation;
}

BreakRuntimeError break_runtime_queue_enqueue(
    BreakRuntimeQueue *queue,
    BreakRuntimeOwnedMessage *message,
    u64 expected_generation)
{
    BreakRuntimeMessageView view;
    RuntimeQueueSlot *slot;
    bool control;
    bool admitted;

    if (!queue || !message) {
        return BREAK_RUNTIME_INVALID;
    }
    if (break_runtime_message_view(message, &view) != BREAK_RUNTIME_OK) {
        return BREAK_RUNTIME_INVALID;
    }
    control = (view.flags & BREAK_RUNTIME_MESSAGE_FLAG_CONTROL) != 0u;

    platform_mutex_lock(&queue->mutex);
    if (queue->closed) {
        queue->closed_rejects++;
        platform_mutex_unlock(&queue->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    if (expected_generation != queue->generation) {
        queue->stale_rejects++;
        platform_mutex_unlock(&queue->mutex);
        return BREAK_RUNTIME_STALE;
    }
    if (control) {
        admitted = queue->count < queue->capacity;
    } else {
        /* Data messages never touch the reserved control slots. */
        admitted = queue->data_count < queue->capacity - queue->reserved_control;
    }
    if (!admitted) {
        queue->overload_rejects++;
        platform_mutex_unlock(&queue->mutex);
        return BREAK_RUNTIME_OVERLOAD;
    }
    slot = &queue->slots[(queue->head + queue->count) % queue->capacity];
    slot->message = message;
    slot->control = control ? 1u : 0u;
    queue->count++;
    if (!control) {
        queue->data_count++;
    }
    queue->enqueued++;
    if (queue->count > queue->high_water) {
        queue->high_water = queue->count;
    }
    if (queue->count == 1u) {
        platform_cond_signal(&queue->not_empty);
    }
    platform_mutex_unlock(&queue->mutex);
    return BREAK_RUNTIME_OK;
}

/* Shared dequeue tail; the caller holds the mutex and has count > 0. */
static BreakRuntimeOwnedMessage *runtime_queue_pop_locked(
    BreakRuntimeQueue *queue)
{
    RuntimeQueueSlot *slot = &queue->slots[queue->head];
    BreakRuntimeOwnedMessage *message = slot->message;
    slot->message = NULL;
    queue->head = (queue->head + 1u) % queue->capacity;
    queue->count--;
    if (!slot->control) {
        queue->data_count--;
    }
    queue->dequeued++;
    return message;
}

BreakRuntimeError break_runtime_queue_poll(
    BreakRuntimeQueue *queue,
    BreakRuntimeOwnedMessage **out_message)
{
    if (!queue || !out_message) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_message = NULL;
    platform_mutex_lock(&queue->mutex);
    if (queue->count == 0u) {
        BreakRuntimeError err =
            queue->closed ? BREAK_RUNTIME_CLOSED : BREAK_RUNTIME_OK;
        platform_mutex_unlock(&queue->mutex);
        return err;
    }
    *out_message = runtime_queue_pop_locked(queue);
    platform_mutex_unlock(&queue->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_queue_wait(
    BreakRuntimeQueue *queue,
    BreakRuntimeOwnedMessage **out_message)
{
    if (!queue || !out_message) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_message = NULL;
    platform_mutex_lock(&queue->mutex);
    while (queue->count == 0u && !queue->closed) {
        platform_cond_wait(&queue->not_empty, &queue->mutex);
    }
    if (queue->count == 0u) {
        /* Closed and drained: the shutdown wakeup path. */
        platform_mutex_unlock(&queue->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    *out_message = runtime_queue_pop_locked(queue);
    platform_mutex_unlock(&queue->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_queue_stats(
    BreakRuntimeQueue *queue,
    BreakRuntimeQueueStats *out_stats)
{
    if (!queue || !out_stats) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&queue->mutex);
    out_stats->enqueued = queue->enqueued;
    out_stats->dequeued = queue->dequeued;
    out_stats->overload_rejects = queue->overload_rejects;
    out_stats->stale_rejects = queue->stale_rejects;
    out_stats->closed_rejects = queue->closed_rejects;
    out_stats->high_water = queue->high_water;
    platform_mutex_unlock(&queue->mutex);
    return BREAK_RUNTIME_OK;
}
