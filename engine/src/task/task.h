#pragma once
#include <core/types.h>
#include <core/platform_thread.h>
#include <stdatomic.h>

/* ---- Task Function Type ---- */
typedef void (*TaskFn)(void *ctx);

/* ---- Task Priority Levels ---- */
typedef enum {
    TASK_PRIORITY_HIGH   = 0,
    TASK_PRIORITY_NORMAL = 1,
    TASK_PRIORITY_LOW    = 2,
    TASK_PRIORITY_COUNT  = 3
} TaskPriority;

/* ---- Task Handle (opaque ID for dependency tracking) ---- */
typedef u64 TaskHandle;
#define TASK_HANDLE_INVALID ((TaskHandle)0)

/* ---- Cancellation ----
 * A caller-owned token shared by any number of tasks. Initialize it with
 * task_cancel_token_init (or zero it) before use, and do not re-initialize
 * it while tasks that use it are outstanding. task_cancel sets it; it stays
 * set. A task submitted with a token is skipped (fn is not called) if the
 * token is set when the task is about to run, on a worker or on a thread
 * that drains tasks inline; it still completes: its dependents are
 * released, task_wait and task_wait_handle return, and
 * task_cancelled_count counts it. A task that is already running is not
 * interrupted; fn can poll task_cancel_requested and return early, so the
 * caller must still wait before freeing ctx. Dependents with a different
 * or no token still run after a skipped parent; give a whole subtree one
 * token to drop it together. The token must outlive every task using it. */
typedef struct {
    _Atomic bool cancelled;
} TaskCancelToken;

/* ---- Task Node ---- */
typedef struct TaskWaitLink TaskWaitLink;
struct TaskWaitLink {
    struct Task *child;
    TaskWaitLink *next;
};

typedef struct Task {
    TaskFn       fn;
    void        *ctx;
    _Atomic u32  dep_count;     /* outstanding dependency count */
    _Atomic u32  ref_count;     /* reference count for lifetime */
    TaskWaitLink *waiters;      /* R173: tasks waiting on this one (fan-out) */
    TaskPriority priority;
    TaskHandle   handle;
    _Atomic bool completed;     /* set true after fn() returns or is skipped */
    const TaskCancelToken *cancel; /* NULL = not cancellable */
} Task;

/* ---- Chase-Lev Work-Stealing Deque ---- */
#define DEQUE_CAPACITY 1024  /* must be power of 2 */

typedef struct {
    _Atomic i64   top;
    _Atomic i64   bottom;
    /* R385: slots must be atomic, not just top/bottom. The owner's push and a
     * thief's steal legitimately touch the same slot concurrently — the CAS on
     * `top` decides who keeps the value, but the access itself is still a data
     * race unless the slot is atomic. Relaxed is sufficient: the surrounding
     * fences and the CAS provide all the ordering (Lê et al. 2013). */
    _Atomic(Task *) *buffer;    /* circular buffer of task pointers */
    u32           capacity;
} WorkStealDeque;

/* ---- Worker Thread ---- */
/* R414: pad/align to a cache line — adjacent Workers in the workers[] array
 * otherwise share lines and false-share on their hot deque atomics. The
 * matching allocation alignment is handled in task_system_create(). */
typedef struct {
    WorkStealDeque queues[TASK_PRIORITY_COUNT]; /* one deque per priority */
    u32            id;
    _Atomic bool   active;
    u32            steal_attempts;
    u32            backoff_ns;
    /* Diagnostics (relaxed counters, read with task_worker_stats). */
    _Atomic u64    executed; /* tasks run on this worker's thread */
    _Atomic u64    stolen;   /* of those, taken from another worker's deque */
    _Atomic u64    idle_sleeps;
    PlatformThread thread;
} ENGINE_ALIGN(64) Worker;

/* ---- Task System ---- */
#define SUBMIT_QUEUE_CAPACITY 256

typedef struct {
    Worker       *workers;
    u32           worker_count;
    _Atomic bool  running;
    _Atomic u64   total_tasks_completed;
    _Atomic u64   total_tasks_submitted;
    _Atomic u64   next_handle;
    _Atomic u64   total_tasks_cancelled;
    _Atomic u64   inline_executed; /* tasks run on a non-worker thread */

    /* Global submit queue (for external thread submissions) */
    /* R420: use the platform mutex type directly; task.c passes &ts->submit_mutex
     * to platform_mutex_* everywhere. */
    PlatformMutex submit_mutex;
    Task         *submit_queue[SUBMIT_QUEUE_CAPACITY];
    _Atomic u32   submit_count;

    /* Task handle registry (simple pool) */
    Task        **task_pool;
    u32           task_pool_capacity;
    _Atomic u32   task_pool_count;
    /* Pre-allocated contiguous Task block (bump allocator) */
    Task         *_task_block;
    /* R420: embedded platform mutex, shared by both Windows and POSIX paths. */
    PlatformMutex pool_mutex;
    /* Optional task graph trace (NULL = never enabled); see task_trace_*. */
    _Atomic(struct TaskTraceLog *) trace;
} TaskSystem;

/* ---- Legacy compatible type alias ---- */
/* Backward compatibility: TaskQueue and TaskSystem used to be visible */
typedef struct { void *_opaque; } TaskQueue;

/* ---- Public API ---- */

/**
 * Create task system.
 * @param worker_count Number of worker threads. 0 = auto-detect (cores - 1).
 *
 * R429: single-instance only — create at most ONE TaskSystem per process.
 * task_release() uses the global g_task_system for heap-vs-block decisions,
 * so a second live system would release tasks against the wrong pool.
 */
TaskSystem *task_system_create(i32 worker_count);

/** Destroy task system (waits for all pending tasks to complete). */
void task_system_destroy(TaskSystem *ts);

/** Submit a task (backward-compatible, NORMAL priority). */
void task_submit(TaskSystem *ts, TaskFn fn, void *ctx);

/** Submit N tasks with same function (backward-compatible, NORMAL priority). */
void task_submit_n(TaskSystem *ts, TaskFn fn, void **ctxs, i32 count);

/** Wait until all submitted tasks are complete.
 * Must NOT be called from a worker task: the wait set includes the caller's
 * own running task, which can never complete while it waits (self-deadlock);
 * the call logs a warning and returns immediately instead. */
void task_wait(TaskSystem *ts);

/** Get current worker ID (returns -1 if called from non-worker thread). */
i32 task_worker_id(TaskSystem *ts);

/* ---- Extended API ---- */

/** Submit with explicit priority. Returns handle for dependency tracking. */
TaskHandle task_submit_ex(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio);

/** Submit with dependencies. Task won't execute until all deps complete. */
TaskHandle task_submit_dep(TaskSystem *ts, TaskFn fn, void *ctx,
                           TaskHandle *deps, u32 dep_count);

/** Wait for a specific task to complete.
 * Heap-fallback handles (returned once the 4096-entry task pool is exhausted)
 * cannot be resolved to their Task; waiting on one waits for ALL currently
 * submitted tasks instead — conservative, but the wait is always real.
 * Must NOT be called from a worker task (same self-deadlock contract as
 * task_wait). */
void task_wait_handle(TaskSystem *ts, TaskHandle handle);

/** Get worker thread count. */
u32 task_worker_count(TaskSystem *ts);

/* ---- Cancellation API ---- */

void task_cancel_token_init(TaskCancelToken *token);
/** Request cancellation (release); idempotent, NULL is ignored. */
void task_cancel(TaskCancelToken *token);
/** True once task_cancel was called (acquire); false for NULL. */
bool task_cancel_requested(const TaskCancelToken *token);

/** Like task_submit_dep with a priority and an optional token (NULL makes
 * it an ordinary task). Fails like task_submit_dep: NULL fn, deps == NULL
 * with dep_count > 0, a heap-fallback dependency, or allocation failure. */
TaskHandle task_submit_cancellable(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio,
                                   const TaskCancelToken *token, TaskHandle *deps,
                                   u32 dep_count);

/** Tasks skipped because their token was set before they ran. */
u64 task_cancelled_count(TaskSystem *ts);

/* ---- Diagnostics ----
 * Per-worker counters for measuring work distribution and stealing. A task
 * counts toward the worker whose thread runs it (or toward
 * task_inline_executed when a non-worker thread, such as one inside
 * task_wait, runs it), cancelled tasks included. `stolen` counts tasks a
 * worker took from another worker's deque in its own loop. Counters are
 * monotonic and relaxed: a snapshot taken while tasks run is approximate,
 * one taken after task_wait is exact. */
typedef struct TaskWorkerStats {
    u64 executed;
    u64 stolen;
    u64 idle_sleeps;
} TaskWorkerStats;

/** False for a NULL system or output, or worker_id >= task_worker_count. */
bool task_worker_stats(TaskSystem *ts, u32 worker_id, TaskWorkerStats *out);
u64 task_inline_executed(TaskSystem *ts);

/* ---- Task graph trace ----
 * An opt-in, bounded log of executed tasks and dependency edges for
 * visualizing a task graph. task_trace_enable starts a fresh log holding up
 * to `capacity` tasks (and 4 * capacity edges); tasks that run once it is
 * full are counted by task_trace_dropped and not recorded. When tracing is
 * off the only cost is one atomic load per task and per dependency.
 * Enable, disable, read and export only while the system is quiescent (no
 * task submitted since the last task_wait is still pending): the log is not
 * synchronized against concurrent recording and enable frees the previous
 * log. task_trace_disable stops recording and keeps the log readable until
 * the next enable or task_system_destroy. Times are nanoseconds since the
 * log was enabled. */
typedef struct TaskTraceRecord {
    TaskHandle handle;
    u64 start_ns;
    u64 end_ns;
    i32 worker; /* -1 when a non-worker thread ran the task inline */
    bool cancelled;
} TaskTraceRecord;

/** False for a NULL system, zero capacity, or allocation failure. */
bool task_trace_enable(TaskSystem *ts, u32 capacity);
void task_trace_disable(TaskSystem *ts);
bool task_trace_enabled(TaskSystem *ts);
/** Recorded tasks, in the order they finished. */
u32 task_trace_record_count(TaskSystem *ts);
u64 task_trace_dropped(TaskSystem *ts);
/** Recorded dependency edges, including edges to an already finished task. */
u32 task_trace_edge_count(TaskSystem *ts);
/** False for a NULL output or index >= task_trace_record_count. */
bool task_trace_get(TaskSystem *ts, u32 index, TaskTraceRecord *out);
/** Writes the log as a NUL-terminated Chrome trace document: one "X" slice
 * per task on a track per worker (plus an "inline" track), and an "s"/"f"
 * flow pair per edge whose two tasks were both recorded. *out_len (if not
 * NULL) receives the document length without the NUL. Returns false, with
 * buf[0] = '\0' when capacity > 0 and *out_len set to the needed length,
 * when the buffer is too small; returns false with *out_len = 0 when no log
 * exists. */
bool task_trace_export(TaskSystem *ts, char *buf, usize capacity, usize *out_len);
