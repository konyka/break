#include <runtime/runtime_task.h>

#include <core/platform_thread.h>
#include <runtime/runtime_metrics.h>
#include <runtime/runtime_test_hooks.h>

#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(BREAK_RUNTIME_TESTING)
_Atomic u64 g_break_runtime_test_forward_fail_budget = 0u;
#endif

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

typedef struct BreakRuntimeTaskQueue BreakRuntimeTaskQueue;

/* Completion counters live outside the queue: a worker bumps them after it
 * published the notice, and the owner may destroy the queue as soon as it
 * has seen that notice. The queue holds one reference and every forwarded
 * call that publishes holds one; the last release frees the block. */
typedef struct BreakRuntimeTaskCompletionCounters {
    _Atomic u32 refs;
    _Atomic u64 published;
    _Atomic u64 dropped;
} BreakRuntimeTaskCompletionCounters;

static void runtime_task_counters_release(BreakRuntimeTaskCompletionCounters *c)
{
    if (c && atomic_fetch_sub_explicit(&c->refs, 1u, memory_order_acq_rel) == 1u) {
        free(c);
    }
}

typedef struct BreakRuntimeTaskCall {
    BreakRuntimeTaskFn fn;
    BreakRuntimeOwnedMessage *payload;
    u32 priority;
    /* Set at drain: where the completion notice goes (bus NULL = none). */
    BreakRuntimeBus *bus;
    u16 kind;
    BreakRuntimeTaskCompletionCounters *counters; /* referenced when bus != NULL */
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
    u64 forward_rejects;
    u64 high_water;
    BreakRuntimeBus *completion_bus;
    u16 completion_kind;
    BreakRuntimeTaskCompletionCounters *counters; /* bumped by workers */
};

static usize runtime_task_align_up(usize value, usize alignment)
{
    /* _Alignof results are always powers of two. */
    return (value + (alignment - 1u)) & ~(alignment - 1u);
}

static void break_runtime_task_trampoline(void *ctx)
{
    BreakRuntimeTaskCall *call = (BreakRuntimeTaskCall *)ctx;
    BreakRuntimeMessageView payload_view;
    u64 sequence = 0u;
    u64 correlation_id = 0u;
    if (call->bus && call->payload &&
        break_runtime_message_view(call->payload, &payload_view) == BREAK_RUNTIME_OK) {
        sequence = payload_view.sequence;
        correlation_id = payload_view.correlation_id;
    }
    call->fn(call->payload); /* releases the payload */
    if (call->bus) {
        BreakRuntimeMessageView notice;
        u32 delivered = 0u;
        memset(&notice, 0, sizeof(notice));
        notice.kind = call->kind;
        notice.version = 1u;
        notice.sequence = sequence;
        notice.correlation_id = correlation_id;
        notice.data = &sequence;
        notice.size = sizeof(sequence);
        (void)break_runtime_bus_publish(call->bus, &notice, &delivered);
        if (delivered > 0u) {
            atomic_fetch_add(&call->counters->published, 1u);
        } else {
            atomic_fetch_add(&call->counters->dropped, 1u);
        }
        runtime_task_counters_release(call->counters);
    }
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
    queue->counters = break_runtime_test_calloc(sizeof(*queue->counters));
    if (!queue->counters) {
        free(queue);
        return BREAK_RUNTIME_OOM;
    }
    atomic_init(&queue->counters->refs, 1u);
    atomic_init(&queue->counters->published, 0u);
    atomic_init(&queue->counters->dropped, 0u);
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
    runtime_task_counters_release(queue->counters);
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
        TaskHandle handle;

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
        /* Peek, not pop: the node stays linked until the legacy system has
         * accepted it. drain() is owner-thread-only, so the head cannot move
         * while the lock is dropped; concurrent submits only append. */
        call = queue->ring[queue->head];
        call->bus = queue->completion_bus;
        call->kind = queue->completion_kind;
        call->counters = call->bus ? queue->counters : NULL;
        if (call->counters) {
            atomic_fetch_add_explicit(&call->counters->refs, 1u, memory_order_relaxed);
        }
        platform_mutex_unlock(&queue->mutex);

        /* Outside the queue mutex: on acceptance the legacy system takes over
         * the call node and the trampoline frees it after the callback
         * returns. `call` is never dereferenced after this point. */
#if defined(BREAK_RUNTIME_TESTING)
        if (break_runtime_test_forward_should_fail()) {
            handle = TASK_HANDLE_INVALID;
        } else
#endif
        {
            handle = task_submit_ex(ts, break_runtime_task_trampoline, call,
                                    (TaskPriority)call->priority);
        }

        if (handle == TASK_HANDLE_INVALID) {
            /* Legacy rejected the task WITHOUT consuming ctx (task pool
             * exhausted + heap-fallback OOM): retain-and-stop. The node and
             * its owned payload stay queued for a later drain; nothing is
             * leaked, dropped, or misreported. */
            platform_mutex_lock(&queue->mutex);
            queue->forward_rejects++;
            platform_mutex_unlock(&queue->mutex);
            if (call->counters) {
                /* the next drain takes a fresh reference */
                runtime_task_counters_release(call->counters);
                call->counters = NULL;
                call->bus = NULL;
            }
            break;
        }

        /* Accepted: detach the head (still `call`; only this owner thread
         * dequeues). The trampoline may already have run and freed the node —
         * detaching touches only the ring slot, never the node. */
        platform_mutex_lock(&queue->mutex);
        queue->ring[queue->head] = NULL;
        queue->head = (queue->head + 1u) % queue->capacity;
        queue->count--;
        queue->forwarded++;
        platform_mutex_unlock(&queue->mutex);
        forwarded++;
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
    out_stats->forward_rejects = queue->forward_rejects;
    out_stats->high_water = queue->high_water;
    platform_mutex_unlock(&queue->mutex);
    out_stats->completions_published = atomic_load(&queue->counters->published);
    out_stats->completions_dropped = atomic_load(&queue->counters->dropped);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_task_queue_publish_completions(
    BreakRuntimeTaskQueue *queue,
    BreakRuntimeBus *bus,
    u16 kind)
{
    if (!queue) {
        return BREAK_RUNTIME_INVALID;
    }
    if (bus && !break_runtime_bus_kind_accepts(bus, kind, 1u, sizeof(u64))) {
        return BREAK_RUNTIME_REJECTED;
    }
    platform_mutex_lock(&queue->mutex);
    queue->completion_bus = bus;
    queue->completion_kind = kind;
    platform_mutex_unlock(&queue->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_task_queue_export_metrics(
    BreakRuntimeTaskQueue *queue,
    struct BreakRuntimeMetrics *metrics,
    const char *prefix)
{
    BreakRuntimeTaskStats stats;
    struct {
        const char *suffix;
        u64 value;
    } gauges[8];
    char name[128];
    u32 i;
    if (!queue || !metrics || !prefix || prefix[0] == '\0') {
        return BREAK_RUNTIME_INVALID;
    }
    if (break_runtime_task_queue_stats(queue, &stats) != BREAK_RUNTIME_OK) {
        return BREAK_RUNTIME_INVALID;
    }
    gauges[0].suffix = "submitted";             gauges[0].value = stats.submitted;
    gauges[1].suffix = "forwarded";             gauges[1].value = stats.forwarded;
    gauges[2].suffix = "overload_rejects";      gauges[2].value = stats.overload_rejects;
    gauges[3].suffix = "closed_rejects";        gauges[3].value = stats.closed_rejects;
    gauges[4].suffix = "forward_rejects";       gauges[4].value = stats.forward_rejects;
    gauges[5].suffix = "high_water";            gauges[5].value = stats.high_water;
    gauges[6].suffix = "completions_published"; gauges[6].value = stats.completions_published;
    gauges[7].suffix = "completions_dropped";   gauges[7].value = stats.completions_dropped;
    for (i = 0; i < 8u; i++) {
        BreakRuntimeError result;
        int n = snprintf(name, sizeof(name), "%s.%s", prefix, gauges[i].suffix);
        if (n < 0) {
            return BREAK_RUNTIME_FAILED;
        }
        /* The registry rejects an over-long name with INVALID; let that be the
         * reported error rather than silently truncating here. */
        result = break_runtime_metrics_set(metrics, name, BREAK_RUNTIME_METRIC_GAUGE,
                                           gauges[i].value);
        if (result != BREAK_RUNTIME_OK) {
            return result;
        }
    }
    return BREAK_RUNTIME_OK;
}
