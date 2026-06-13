#pragma once
#include <core/types.h>
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

/* ---- Task Node ---- */
typedef struct Task {
    TaskFn       fn;
    void        *ctx;
    _Atomic u32  dep_count;     /* outstanding dependency count */
    _Atomic u32  ref_count;     /* reference count for lifetime */
    struct Task *parent;        /* parent task (dependency chain) */
    TaskPriority priority;
    TaskHandle   handle;
    _Atomic bool completed;     /* set true after fn() returns */
} Task;

/* ---- Chase-Lev Work-Stealing Deque ---- */
#define DEQUE_CAPACITY 1024  /* must be power of 2 */

typedef struct {
    _Atomic i64   top;
    _Atomic i64   bottom;
    Task        **buffer;       /* circular buffer of task pointers */
    u32           capacity;
} WorkStealDeque;

/* ---- Worker Thread ---- */
typedef struct {
    WorkStealDeque queues[TASK_PRIORITY_COUNT]; /* one deque per priority */
    u32            id;
    _Atomic bool   active;
    u32            steal_attempts;
    u32            backoff_ns;
#ifdef ENGINE_PLATFORM_WINDOWS
    void          *thread_handle;  /* HANDLE */
#else
    u64            thread_storage[8]; /* enough for pthread_t */
#endif
} Worker;

/* ---- Task System ---- */
#define SUBMIT_QUEUE_CAPACITY 256

typedef struct {
    Worker       *workers;
    u32           worker_count;
    _Atomic bool  running;
    _Atomic u64   total_tasks_completed;
    _Atomic u64   total_tasks_submitted;
    _Atomic u64   next_handle;

    /* Global submit queue (for external thread submissions) */
#ifdef ENGINE_PLATFORM_WINDOWS
    void         *submit_cs;    /* CRITICAL_SECTION pointer */
#else
    u64           submit_mutex_storage[8]; /* enough for pthread_mutex_t */
#endif
    Task         *submit_queue[SUBMIT_QUEUE_CAPACITY];
    _Atomic u32   submit_count;

    /* Task handle registry (simple pool) */
    Task        **task_pool;
    u32           task_pool_capacity;
    _Atomic u32   task_pool_count;
    /* Pre-allocated contiguous Task block (bump allocator) */
    Task         *_task_block;
#ifdef ENGINE_PLATFORM_WINDOWS
    void         *pool_cs;
#else
    u64           pool_mutex_storage[8];
#endif
} TaskSystem;

/* ---- Legacy compatible type alias ---- */
/* Backward compatibility: TaskQueue and TaskSystem used to be visible */
typedef struct { void *_opaque; } TaskQueue;

/* ---- Public API ---- */

/**
 * Create task system.
 * @param worker_count Number of worker threads. 0 = auto-detect (cores - 1).
 */
TaskSystem *task_system_create(i32 worker_count);

/** Destroy task system (waits for all pending tasks to complete). */
void task_system_destroy(TaskSystem *ts);

/** Submit a task (backward-compatible, NORMAL priority). */
void task_submit(TaskSystem *ts, TaskFn fn, void *ctx);

/** Submit N tasks with same function (backward-compatible, NORMAL priority). */
void task_submit_n(TaskSystem *ts, TaskFn fn, void **ctxs, i32 count);

/** Wait until all submitted tasks are complete. */
void task_wait(TaskSystem *ts);

/** Get current worker ID (returns -1 if called from non-worker thread). */
i32 task_worker_id(TaskSystem *ts);

/* ---- Extended API ---- */

/** Submit with explicit priority. Returns handle for dependency tracking. */
TaskHandle task_submit_ex(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio);

/** Submit with dependencies. Task won't execute until all deps complete. */
TaskHandle task_submit_dep(TaskSystem *ts, TaskFn fn, void *ctx,
                           TaskHandle *deps, u32 dep_count);

/** Wait for a specific task to complete. */
void task_wait_handle(TaskSystem *ts, TaskHandle handle);

/** Get worker thread count. */
u32 task_worker_count(TaskSystem *ts);
