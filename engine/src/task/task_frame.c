#include <task/task_frame.h>
#include <stdlib.h>
#include <string.h>

bool task_frame_queue_init(TaskFrameQueue *q, u32 capacity) {
    if (!q) return false;
    memset(q, 0, sizeof(*q));
    if (capacity == 0u) return false;
    q->entries = (TaskFrameEntry *)calloc(capacity, sizeof(*q->entries));
    if (!q->entries) return false;
    q->capacity = capacity;
    return true;
}

void task_frame_queue_destroy(TaskFrameQueue *q) {
    if (!q) return;
    free(q->entries);
    memset(q, 0, sizeof(*q));
}

TaskFrameError task_frame_defer(TaskFrameQueue *q, u64 frame, TaskFn fn, void *ctx,
                                const TaskCancelToken *cancel) {
    if (!q || !q->entries || !fn) return TASK_FRAME_INVALID;
    if (q->count == q->capacity) return TASK_FRAME_FULL;
    TaskFrameEntry *e = &q->entries[q->count++];
    e->frame = frame;
    e->sequence = q->next_sequence++;
    e->fn = fn;
    e->ctx = ctx;
    e->cancel = cancel;
    return TASK_FRAME_OK;
}

static bool entry_before(const TaskFrameEntry *a, const TaskFrameEntry *b) {
    return a->frame < b->frame || (a->frame == b->frame && a->sequence < b->sequence);
}

/* Moves the entries due at `frame` to the front, sorted oldest frame first,
 * then by sequence; returns how many there are. The rest keep their order. */
static u32 partition_due(TaskFrameQueue *q, u64 frame) {
    u32 due = 0u;
    for (u32 i = 0; i < q->count; i++) {
        if (q->entries[i].frame <= frame) {
            TaskFrameEntry e = q->entries[i];
            memmove(&q->entries[due + 1u], &q->entries[due], (size_t)(i - due) * sizeof(e));
            q->entries[due++] = e;
        }
    }
    for (u32 i = 1; i < due; i++) {
        TaskFrameEntry e = q->entries[i];
        u32 j = i;
        while (j > 0u && entry_before(&e, &q->entries[j - 1u])) {
            q->entries[j] = q->entries[j - 1u];
            j--;
        }
        q->entries[j] = e;
    }
    return due;
}

u32 task_frame_run(TaskFrameQueue *q, u64 frame, TaskSystem *ts) {
    if (!q || !q->entries || q->running) return 0u;
    u32 due = partition_due(q, frame);
    if (due == 0u) return 0u;
    /* Detach the due entries first: continuations may defer into q while
     * they run, and those land in q, not in this batch, so they wait for the
     * next run even when they are due now. */
    TaskFrameEntry *batch = (TaskFrameEntry *)malloc((size_t)due * sizeof(*batch));
    if (!batch) return 0u;
    memcpy(batch, q->entries, (size_t)due * sizeof(*batch));
    memmove(q->entries, q->entries + due, (size_t)(q->count - due) * sizeof(*batch));
    q->count -= due;
    q->running = true;
    for (u32 i = 0; i < due; i++) {
        if (task_cancel_requested(batch[i].cancel)) {
            q->cancelled++;
            continue;
        }
        /* a task that cannot be submitted runs inline rather than being lost */
        if (!ts || task_submit_cancellable(ts, batch[i].fn, batch[i].ctx, TASK_PRIORITY_NORMAL,
                                           batch[i].cancel, NULL, 0u) == TASK_HANDLE_INVALID)
            batch[i].fn(batch[i].ctx);
    }
    if (ts) task_wait(ts);
    q->running = false;
    free(batch);
    return due;
}

u32 task_frame_pending(const TaskFrameQueue *q) {
    return q ? q->count : 0u;
}

u64 task_frame_cancelled(const TaskFrameQueue *q) {
    return q ? q->cancelled : 0u;
}
