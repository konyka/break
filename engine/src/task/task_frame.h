#pragma once
#include <task/task.h>

/* Cross-frame continuations: work scheduled to run when the owner reaches a
 * later frame. The queue belongs to one owner thread, which calls
 * task_frame_run. task_frame_defer is safe from any thread, which covers
 * continuations that defer more work while they run on several workers.
 *
 * task_frame_run(q, frame, ts) runs every continuation whose frame is <= the
 * given frame, oldest frame first and in submission order within a frame.
 * Work deferred while a run is in progress waits for the next run call, even
 * when it is due, so a continuation that re-defers for the current frame
 * cannot loop forever. With ts == NULL continuations run inline on the
 * calling thread; otherwise each runs as a task on ts and the call returns
 * once all of them have finished (the same rules as task_wait apply: do not
 * call it from a worker). A continuation whose cancellation token is set
 * when the run starts is skipped and counted in task_frame_cancelled. The
 * context pointer must stay valid until the continuation has run or been
 * skipped. A continuation that calls task_frame_run on its own queue gets 0
 * (runs do not nest); one that cannot be submitted to ts runs inline. If the
 * batch buffer cannot be allocated, the run removes nothing and returns 0. */

typedef enum TaskFrameError {
    TASK_FRAME_OK = 0,
    TASK_FRAME_INVALID,
    TASK_FRAME_FULL
} TaskFrameError;

typedef struct TaskFrameEntry {
    u64 frame;
    u64 sequence;
    TaskFn fn;
    void *ctx;
    const TaskCancelToken *cancel;
} TaskFrameEntry;

typedef struct TaskFrameQueue {
    TaskFrameEntry *entries;
    u32 count;
    u32 capacity;
    u64 next_sequence;
    u64 cancelled;
    bool running;
    PlatformMutex mutex; /* initialized when entries != NULL */
} TaskFrameQueue;

/* capacity must be > 0; returns false on a zero capacity or allocation
 * failure, leaving the queue empty and safe to destroy. Initializing a live
 * queue discards it without freeing; destroy it first. */
bool task_frame_queue_init(TaskFrameQueue *q, u32 capacity);
void task_frame_queue_destroy(TaskFrameQueue *q);

TaskFrameError task_frame_defer(TaskFrameQueue *q, u64 frame, TaskFn fn, void *ctx,
                                const TaskCancelToken *cancel);

/* Returns the number of continuations removed (run or skipped). */
u32 task_frame_run(TaskFrameQueue *q, u64 frame, TaskSystem *ts);

u32 task_frame_pending(const TaskFrameQueue *q);
u64 task_frame_cancelled(const TaskFrameQueue *q);
