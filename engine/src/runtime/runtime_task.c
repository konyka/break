#include <runtime/runtime_task.h>

#include <core/platform_thread.h>
#include <runtime/runtime_test_hooks.h>

#include <stdatomic.h>
#include <stdlib.h>

/* Formal task facade: a bounded queue of owned task calls over the legacy
 * TaskSystem. The legacy queue-full inline fallback lives in task.c and is
 * untouched; this facade never executes a submitted task itself — submit()
 * only accepts (queue owns the call) or rejects (caller keeps the payload),
 * and drain() forwards to task_submit_ex() from the owner thread.
 *
 * Each accepted task owns one heap TaskCall (allocated at submit) carrying
 * the owned payload message; the node never retains borrowed pointers. At
 * drain the TaskCall pointer is handed to the legacy system and freed by the
 * trampoline after the callback returns; the payload ownership moves to the
 * callback, which must release it. */

typedef struct BreakRuntimeTaskCall {
    BreakRuntimeTaskFn fn;
    BreakRuntimeOwnedMessage *payload;
    u32 priority;
} BreakRuntimeTaskCall;

struct BreakRuntimeTaskQueue {
    PlatformMutex mutex;
    BreakRuntimeTaskCall **ring; /* tail of this single allocation */
    u32 capacity;
    u32 head;
    u32 count;
    bool closed;
    u64 submitted;
    u64 forwarded;
    u64 overload_rejects;
    u64 closed_rejects;
    u64 high_water;
};

static usize runtime_task_align_up(usize value, usize alignment)
{
    /* _Alignof results are always powers of two. */
    return (value + (alignment - 1u)) & ~(alignment - 1u);
}

static void break_runtime_task_trampoline(void *ctx)
{
    BreakRuntimeTaskCall *call = (BreakRuntimeTaskCall *)ctx;
    call->fn(call->payload);
    free(call);
}

BreakRuntimeError break_runtime_task_queue_create(
    const BreakRuntimeTaskConfig *config,
    BreakRuntimeTaskQueue **out_queue)
{
    BreakRuntimeTaskQueue *queue;
    usize header_bytes;
    usize bytes;
    u32 capacity = BREAK_RUNTIME_TASK_QUEUE_DEFAULT_CAPACITY;

    if (!out_queue) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_queue = NULL;
    if (config && config->capacity != 0u) {
        if (config->capacity > BREAK_RUNTIME_TASK_QUEUE_MAX_CAPACITY) {
            return BREAK_RUNTIME_INVALID;
        }
        capacity = config->capacity;
    }

    header_bytes = runtime_task_align_up(sizeof(*queue),
                                         (usize)_Alignof(BreakRuntimeTaskCall *));
    if ((usize)capacity >
        (SIZE_MAX - header_bytes) / sizeof(BreakRuntimeTaskCall *)) {
        return BREAK_RUNTIME_INVALID;
    }
    bytes = header_bytes + (usize)capacity * sizeof(BreakRuntimeTaskCall *);

    queue = break_runtime_test_calloc(bytes);
    if (!queue) {
        return BREAK_RUNTIME_OOM;
    }
    platform_mutex_init(&queue->mutex);
    queue->ring = (BreakRuntimeTaskCall **)((char *)queue + header_bytes);
    queue->capacity = capacity;
    queue->head = 0u;
    queue->count = 0u;
    queue->closed = false;
    *out_queue = queue;
    return BREAK_RUNTIME_OK;
}

void break_runtime_task_queue_destroy(BreakRuntimeTaskQueue *queue)
{
    u32 i;
    if (!queue) {
        return;
    }
    /* Contract: no concurrent users at destroy. Tasks already forwarded to
     * the legacy system are legacy-owned and untouched. */
    for (i = 0; i < queue->count; i++) {
        BreakRuntimeTaskCall *call =
            queue->ring[(queue->head + i) % queue->capacity];
        break_runtime_message_release(call->payload);
        free(call);
    }
    platform_mutex_destroy(&queue->mutex);
    free(queue);
}

void break_runtime_task_queue_close(BreakRuntimeTaskQueue *queue)
{
    if (!queue) {
        return;
    }
    platform_mutex_lock(&queue->mutex);
    queue->closed = true;
    platform_mutex_unlock(&queue->mutex);
}

BreakRuntimeError break_runtime_task_submit(
    BreakRuntimeTaskQueue *queue,
    BreakRuntimeTaskFn fn,
    BreakRuntimeOwnedMessage *payload,
    TaskPriority priority)
{
    BreakRuntimeTaskCall *call;
    BreakRuntimeError err = BREAK_RUNTIME_OK;

    if (!queue || !fn) {
        return BREAK_RUNTIME_INVALID;
    }
    if (priority >= TASK_PRIORITY_COUNT) {
        return BREAK_RUNTIME_INVALID;
    }

    call = break_runtime_test_calloc(sizeof(*call));
    if (!call) {
        return BREAK_RUNTIME_OOM;
    }
    call->fn = fn;
    call->payload = payload;
    call->priority = (u32)priority;

    platform_mutex_lock(&queue->mutex);
    if (queue->closed) {
        queue->closed_rejects++;
        err = BREAK_RUNTIME_CLOSED;
    } else if (queue->count >= queue->capacity) {
        queue->overload_rejects++;
        err = BREAK_RUNTIME_OVERLOAD;
    } else {
        queue->ring[(queue->head + queue->count) % queue->capacity] = call;
        queue->count++;
        queue->submitted++;
        if (queue->count > queue->high_water) {
            queue->high_water = queue->count;
        }
    }
    platform_mutex_unlock(&queue->mutex);

    if (err != BREAK_RUNTIME_OK) {
        /* Rejection: the caller keeps the payload; the call node is ours. */
        call->payload = NULL;
        free(call);
    }
    return err;
}

BreakRuntimeError break_runtime_task_queue_drain(
    BreakRuntimeTaskQueue *queue,
    TaskSystem *ts,
    u32 max_tasks,
    u32 *out_forwarded)
{
    u32 forwarded = 0u;

    if (!queue || !ts || !out_forwarded) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_forwarded = 0u;

    while (forwarded < max_tasks) {
        BreakRuntimeTaskCall *call;

        platform_mutex_lock(&queue->mutex);
        if (queue->count == 0u) {
            platform_mutex_unlock(&queue->mutex);
            break;
        }
        /* Best-effort credit gate on the legacy external submit queue: stop
         * draining rather than relying on the legacy queue-full fallback.
         * Concurrent legacy submitters can still race this; the formal
         * never-inline contract is enforced at submit(), not here. */
        if (atomic_load_explicit(&ts->submit_count, memory_order_acquire) >=
            (u32)SUBMIT_QUEUE_CAPACITY) {
            platform_mutex_unlock(&queue->mutex);
            break;
        }
        call = queue->ring[queue->head];
        queue->ring[queue->head] = NULL;
        queue->head = (queue->head + 1u) % queue->capacity;
        queue->count--;
        platform_mutex_unlock(&queue->mutex);

        /* Outside the queue mutex: the legacy system takes over the call
         * node; the trampoline frees it after the callback returns. */
        task_submit_ex(ts, break_runtime_task_trampoline, call,
                       (TaskPriority)call->priority);
        forwarded++;
    }

    if (forwarded > 0u) {
        platform_mutex_lock(&queue->mutex);
        queue->forwarded += forwarded;
        platform_mutex_unlock(&queue->mutex);
    }
    *out_forwarded = forwarded;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_task_queue_stats(
    BreakRuntimeTaskQueue *queue,
    BreakRuntimeTaskStats *out_stats)
{
    if (!queue || !out_stats) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&queue->mutex);
    out_stats->submitted = queue->submitted;
    out_stats->forwarded = queue->forwarded;
    out_stats->overload_rejects = queue->overload_rejects;
    out_stats->closed_rejects = queue->closed_rejects;
    out_stats->high_water = queue->high_water;
    platform_mutex_unlock(&queue->mutex);
    return BREAK_RUNTIME_OK;
}
