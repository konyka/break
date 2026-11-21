#include <task/task.h>
#include <core/log.h>
#include <core/trace_schema.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>

#ifdef ENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#else
    #include <time.h>
    #include <unistd.h>
#endif

/* ============================================================
 * Platform Abstraction
 * ============================================================ */

#ifdef ENGINE_PLATFORM_WINDOWS
static inline void platform_sleep_ns(u32 ns) {
    /* Windows Sleep is in ms; minimum 0 yields timeslice */
    DWORD ms = ns / 1000000;
    if (ms == 0 && ns > 0) { SwitchToThread(); }
    else { Sleep(ms); }
}
static inline u32 platform_cpu_count(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (u32)si.dwNumberOfProcessors;
}
static u64 task_clock_ns(void) {
    static LARGE_INTEGER freq;
    LARGE_INTEGER now;
    if (freq.QuadPart == 0) QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&now);
    return (u64)((double)now.QuadPart * 1e9 / (double)freq.QuadPart);
}

#else /* POSIX */

static inline void platform_sleep_ns(u32 ns) {
    struct timespec ts = { 0, (long)ns };
    nanosleep(&ts, NULL);
}
static inline u32 platform_cpu_count(void) {
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    return n > 0 ? (u32)n : 1;
}
static u64 task_clock_ns(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (u64)now.tv_sec * 1000000000u + (u64)now.tv_nsec;
}

#endif

/* ============================================================
 * Thread-local worker ID
 * ============================================================ */

static _Thread_local i32 tls_worker_id = -1;

/* ============================================================
 * Chase-Lev Work-Stealing Deque
 * ============================================================ */

static bool deque_init(WorkStealDeque *dq, u32 capacity) {
    dq->capacity = capacity;
    dq->buffer = (_Atomic(Task *) *)calloc(capacity, sizeof(_Atomic(Task *)));
    /* R166-A: calloc failure leaves buffer NULL — subsequent push/steal/pop
     * operations dereference NULL, causing crash. */
    if (!dq->buffer) {
        dq->capacity = 0;
        atomic_store_explicit(&dq->top, 0, memory_order_relaxed);
        atomic_store_explicit(&dq->bottom, 0, memory_order_relaxed);
        return false;
    }
    atomic_store_explicit(&dq->top, 0, memory_order_relaxed);
    atomic_store_explicit(&dq->bottom, 0, memory_order_relaxed);
    return true;
}

static void deque_destroy(WorkStealDeque *dq) {
    free((void *)dq->buffer);
    dq->buffer = NULL;
}

/* Owner thread push (bottom) */
static bool deque_push(WorkStealDeque *dq, Task *task) {
    i64 b = atomic_load_explicit(&dq->bottom, memory_order_relaxed);
    i64 t = atomic_load_explicit(&dq->top, memory_order_acquire);

    if (b - t >= (i64)dq->capacity) {
        return false; /* full */
    }

    atomic_store_explicit(&dq->buffer[b & (i64)(dq->capacity - 1)], task,
                          memory_order_relaxed);
    /* R701: an explicit release store (was: release fence + relaxed
     * store) — semantically identical, but analyzer-visible: fence-
     * plus-relaxed combinations are a classic blind spot of race
     * detectors modeling. */
    atomic_store_explicit(&dq->bottom, b + 1, memory_order_release);
    return true;
}

/* Owner thread pop (bottom, LIFO) */
static Task *deque_pop(WorkStealDeque *dq) {
    i64 b = atomic_load_explicit(&dq->bottom, memory_order_relaxed) - 1;
    atomic_store_explicit(&dq->bottom, b, memory_order_relaxed);
    atomic_thread_fence(memory_order_seq_cst);
    i64 t = atomic_load_explicit(&dq->top, memory_order_relaxed);

    if (t <= b) {
        Task *task = atomic_load_explicit(
            &dq->buffer[b & (i64)(dq->capacity - 1)], memory_order_relaxed);
        if (t == b) {
            /* Last element — race with steal */
            if (!atomic_compare_exchange_strong_explicit(
                    &dq->top, &t, t + 1,
                    memory_order_seq_cst, memory_order_relaxed)) {
                task = NULL; /* stolen */
            }
            atomic_store_explicit(&dq->bottom, b + 1, memory_order_relaxed);
        }
        return task;
    }

    /* Empty */
    atomic_store_explicit(&dq->bottom, b + 1, memory_order_relaxed);
    return NULL;
}

/* Thief thread steal (top, FIFO) */
static Task *deque_steal(WorkStealDeque *dq) {
    i64 t = atomic_load_explicit(&dq->top, memory_order_acquire);
    atomic_thread_fence(memory_order_seq_cst);
    i64 b = atomic_load_explicit(&dq->bottom, memory_order_acquire);

    if (t >= b) return NULL; /* empty */

    Task *task = atomic_load_explicit(
        &dq->buffer[t & (i64)(dq->capacity - 1)], memory_order_relaxed);

    if (!atomic_compare_exchange_strong_explicit(
            &dq->top, &t, t + 1,
            memory_order_seq_cst, memory_order_relaxed)) {
        return NULL; /* CAS failed, contention */
    }
    return task;
}

/* ============================================================
 * Task Allocation
 * ============================================================ */

/* Forward declaration — defined below in worker section */
static _Atomic(TaskSystem *) g_task_system = NULL;

static Task *task_alloc(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio) {
    /* Lock-free bump allocation: atomic_fetch_add gives each caller a unique
     * pool_idx without mutex contention. Each caller writes to a distinct
     * task_pool[pool_idx] slot, so no data race occurs.
     * R420: saturate the counter at capacity instead of a plain fetch_add —
     * a monotonic u32 wraps past 2^32 submissions, and a wrapped count would
     * hand out a live pool slot to be memset. The count only matters versus
     * capacity, so stopping at capacity loses nothing. */
    Task *t = NULL;
    bool heap = false;
    u32 pool_idx = atomic_load_explicit(&ts->task_pool_count, memory_order_relaxed);
    for (;;) {
        if (pool_idx >= ts->task_pool_capacity) break;
        if (atomic_compare_exchange_weak_explicit(&ts->task_pool_count, &pool_idx,
                                                  pool_idx + 1,
                                                  memory_order_acq_rel,
                                                  memory_order_relaxed)) break;
    }
    if (pool_idx < ts->task_pool_capacity) {
        t = &ts->_task_block[pool_idx];
        ts->task_pool[pool_idx] = t;
    }

    if (!t) {
        /* Fallback: pool exhausted, allocate on heap */
        t = (Task *)calloc(1, sizeof(Task));
        /* R156: calloc failure leaves t NULL — memset below would crash. */
        if (!t) return NULL;
        /* R414: task_pool_count is monotonic, so the old "best-effort
         * registration" branch was dead code and pool_idx always ended up
         * 0xFFFFFFFF here. Drop it: heap tasks are never registered in
         * task_pool. Their handle encodes idx 0xFFFFFFFF, which
         * task_wait_handle / task_submit_dep explicitly reject, and they get
         * ref_count 1 (exec ref only) so task_release() frees them. */
        pool_idx = 0xFFFFFFFF;
        heap = true;
    }

    memset(t, 0, sizeof(Task));
    t->fn = fn;
    t->ctx = ctx;
    t->priority = prio;
    atomic_store_explicit(&t->dep_count, 0, memory_order_relaxed);
    /* R414: pool tasks keep exec ref + pool ref (2); heap-fallback tasks have
     * no pool ref (1) so the exec-ref drop in execute_task frees them. */
    atomic_store_explicit(&t->ref_count, heap ? 1u : 2u, memory_order_relaxed);
    t->waiters = NULL;

    /* Assign handle: encode pool index for O(1) lookup in wait_handle */
    u32 gen = (u32)(atomic_fetch_add_explicit(&ts->next_handle, 1, memory_order_relaxed) + 1);
    t->handle = ((u64)gen << 32) | (u64)pool_idx;

    return t;
}

static void task_release(Task *t) {
    u32 old = atomic_fetch_sub_explicit(&t->ref_count, 1, memory_order_acq_rel);
    if (old == 1) {
        /* Only free heap-allocated tasks. Block tasks are freed with the block.
         * Detect by checking if t falls outside the block range. We store the
         * block pointer in a static accessible via g_task_system. */
        TaskSystem *ts = atomic_load_explicit(&g_task_system, memory_order_acquire);
        /* R414: compare as integers — relational comparison between a heap
         * pointer and the unrelated _task_block array is UB in C11. */
        bool is_block = false;
        if (ts) {
            uintptr_t addr = (uintptr_t)t;
            uintptr_t lo   = (uintptr_t)ts->_task_block;
            uintptr_t hi   = lo + (uintptr_t)ts->task_pool_capacity * sizeof(Task);
            is_block = addr >= lo && addr < hi;
        }
        if (!is_block) free(t);
    }
}

/* ============================================================
 * Internal: Submit-queue draining
 *
 * Concurrency invariants (Chase-Lev correctness):
 *  - A worker's deque may only be PUSHED by its owning thread. Therefore the
 *    global submit queue is never redistributed into other workers' deques.
 *    Instead each worker PULLS its share into its OWN deque (owner push), and
 *    non-worker threads (e.g. the main thread in task_wait) execute inline.
 *  - The global submit queue (`submit_queue` + `submit_count`) is mutated ONLY
 *    under `submit_mutex`. In particular the count reset uses an
 *    exchange *inside* the lock so a concurrent submit can never overwrite an
 *    unprocessed slot.
 * ============================================================ */

static void execute_task(TaskSystem *ts, Worker *self, Task *task);

/* Enqueue to the mutex-protected global submit queue (used by non-worker
 * submitters and as a fallback when a local deque is full). */
static void enqueue_global(TaskSystem *ts, Task *t) {
    platform_mutex_lock(&ts->submit_mutex);
    u32 idx = atomic_load_explicit(&ts->submit_count, memory_order_relaxed);
    if (idx < SUBMIT_QUEUE_CAPACITY) {
        ts->submit_queue[idx] = t;
        atomic_store_explicit(&ts->submit_count, idx + 1, memory_order_release);
        platform_mutex_unlock(&ts->submit_mutex);
    } else {
        /* Queue full (rare) — run inline so the task is never lost. */
        platform_mutex_unlock(&ts->submit_mutex);
        execute_task(ts, NULL, t);
    }
}

/* Schedule a now-ready task. Worker context pushes to its own deque (owner
 * push); otherwise route through the global queue. */
static void schedule_ready(TaskSystem *ts, Worker *self, Task *t) {
    if (self && deque_push(&self->queues[t->priority], t)) return;
    enqueue_global(ts, t);
}

/* Atomically detach the whole global submit queue under the lock. Returns the
 * number of (compacted, non-NULL) tasks written to `out` (capacity
 * SUBMIT_QUEUE_CAPACITY). */
static u32 detach_submit_queue(TaskSystem *ts, Task **out) {
    if (atomic_load_explicit(&ts->submit_count, memory_order_acquire) == 0) return 0;
    platform_mutex_lock(&ts->submit_mutex);
    u32 count = atomic_exchange_explicit(&ts->submit_count, 0, memory_order_relaxed);
    u32 n = 0;
    for (u32 i = 0; i < count; i++) {
        Task *t = ts->submit_queue[i];
        ts->submit_queue[i] = NULL;
        if (t) out[n++] = t;
    }
    platform_mutex_unlock(&ts->submit_mutex);
    return n;
}

/* Worker context: move queued submissions into the caller's OWN deque. */
static void worker_pull_submitted(TaskSystem *ts, Worker *self) {
    Task *batch[SUBMIT_QUEUE_CAPACITY];
    u32 n = detach_submit_queue(ts, batch);
    for (u32 i = 0; i < n; i++) {
        Task *t = batch[i];
        if (!deque_push(&self->queues[t->priority], t)) {
            execute_task(ts, self, t); /* local deque full — run inline */
        }
    }
}

/* Non-worker context (e.g. main thread): execute queued submissions inline.
 * Safe because execute_task tolerates a NULL worker. Returns true if any ran. */
static bool drain_submitted_inline(TaskSystem *ts) {
    Task *batch[SUBMIT_QUEUE_CAPACITY];
    u32 n = detach_submit_queue(ts, batch);
    for (u32 i = 0; i < n; i++) {
        execute_task(ts, NULL, batch[i]);
    }
    return n > 0;
}

/* ============================================================
 * Worker Thread Main Loop
 * ============================================================ */

/* ============================================================
 * Task graph trace
 * ============================================================ */

typedef struct {
    TaskHandle from;
    TaskHandle to;
} TaskTraceEdge;

struct TaskTraceLog {
    _Atomic bool active;
    u64 origin_ns;
    u32 capacity;
    _Atomic u64 next;
    _Atomic u64 dropped;
    TaskTraceRecord *records;
    u32 edge_capacity;
    _Atomic u64 edge_next;
    TaskTraceEdge *edges;
};

static void task_trace_free(struct TaskTraceLog *log) {
    if (!log) return;
    free(log->records);
    free(log->edges);
    free(log);
}

static struct TaskTraceLog *trace_active(TaskSystem *ts) {
    struct TaskTraceLog *log = atomic_load_explicit(&ts->trace, memory_order_acquire);
    if (log && !atomic_load_explicit(&log->active, memory_order_relaxed)) return NULL;
    return log;
}

static void trace_add_edge(struct TaskTraceLog *log, TaskHandle from, TaskHandle to) {
    u64 i = atomic_fetch_add_explicit(&log->edge_next, 1u, memory_order_relaxed);
    if (i < log->edge_capacity) {
        log->edges[i].from = from;
        log->edges[i].to = to;
    }
}

static void execute_task(TaskSystem *ts, Worker *self, Task *task) {
    (void)self;
    struct TaskTraceLog *trace = trace_active(ts);
    u64 trace_start = trace ? task_clock_ns() : 0u;
    bool skipped = false;
    if (tls_worker_id >= 0 && (u32)tls_worker_id < ts->worker_count)
        atomic_fetch_add_explicit(&ts->workers[tls_worker_id].executed, 1, memory_order_relaxed);
    else
        atomic_fetch_add_explicit(&ts->inline_executed, 1, memory_order_relaxed);
    if (task->cancel && atomic_load_explicit(&task->cancel->cancelled, memory_order_acquire)) {
        atomic_fetch_add_explicit(&ts->total_tasks_cancelled, 1, memory_order_relaxed);
        skipped = true;
    } else {
        task->fn(task->ctx);
    }
    /* Recorded before the completion count below, so a task_wait that sees
     * the task finished also sees its record. */
    if (trace) {
        u64 end = task_clock_ns();
        u64 slot = atomic_fetch_add_explicit(&trace->next, 1u, memory_order_relaxed);
        if (slot < trace->capacity) {
            TaskTraceRecord *r = &trace->records[slot];
            r->handle = task->handle;
            r->start_ns = trace_start > trace->origin_ns ? trace_start - trace->origin_ns : 0u;
            r->end_ns = end > trace->origin_ns ? end - trace->origin_ns : 0u;
            if (r->end_ns < r->start_ns) r->end_ns = r->start_ns;
            r->worker = (tls_worker_id >= 0 && (u32)tls_worker_id < ts->worker_count)
                            ? tls_worker_id : -1;
            r->cancelled = skipped;
        } else {
            atomic_fetch_add_explicit(&trace->dropped, 1u, memory_order_relaxed);
        }
    }

    /* Mark completed BEFORE dependency resolution so wait_handle can see it. */
    atomic_store_explicit(&task->completed, true, memory_order_release);
    /* R267 (CORRECTNESS): task_wait() (see below) decides "all done" solely by
     * acquire-loading total_tasks_completed and comparing it to submitted — it
     * does NOT load each task's `completed` flag, so the per-task release store
     * above never synchronizes with a global task_wait(). If this increment were
     * memory_order_relaxed, the acquire load in task_wait() would not form a
     * happens-before with the non-atomic writes performed inside task->fn()
     * (e.g. ecs_parallel_for component updates, sys_sync_transform_from_physics),
     * so a thread returning from task_wait() could read STALE task results on a
     * weak-memory target (ARM / Apple Silicon; the engine supports macOS). x86
     * TSO happens to hide this. Use acq_rel: each worker's increment acquires the
     * prior workers' increments (chaining their fn() writes into a happens-before
     * chain) and releases its own, so once task_wait()'s acquire load observes
     * completed >= submitted, every finished task's writes are visible. */
    atomic_fetch_add_explicit(&ts->total_tasks_completed, 1, memory_order_acq_rel);

    /* R173: Detach waiter list under pool lock (fan-out + race-safe). */
    platform_mutex_lock(&ts->pool_mutex);
    TaskWaitLink *waiters = task->waiters;
    task->waiters = NULL;
    platform_mutex_unlock(&ts->pool_mutex);

    while (waiters) {
        TaskWaitLink *link = waiters;
        waiters = link->next;
        Task *child = link->child;
        free(link);
        if (child) {
            u32 old = atomic_fetch_sub_explicit(&child->dep_count, 1, memory_order_acq_rel);
            if (old == 1) {
                schedule_ready(ts, self, child);
            }
            task_release(child);
        }
    }

    task_release(task);
}

/* ============================================================
 * Global pointer for worker thread TaskSystem access
 * (forward-declared above task_alloc)
 * ============================================================ */

/* Fixup: workers need access to TaskSystem. We use the global. */

static PLATFORM_THREAD_RET worker_entry(PLATFORM_THREAD_ARG arg) {
    Worker *self = (Worker *)arg;
    TaskSystem *ts = atomic_load_explicit(&g_task_system, memory_order_acquire);
    tls_worker_id = (i32)self->id;
    atomic_store_explicit(&self->active, true, memory_order_release);

    while (atomic_load_explicit(&ts->running, memory_order_acquire)) {
        Task *task = NULL;

        /* 1. Pop from local queues (high prio first) */
        for (int prio = 0; prio < TASK_PRIORITY_COUNT && !task; prio++) {
            task = deque_pop(&self->queues[prio]);
        }

        /* 2. Pull global submissions into our own deque */
        if (!task) {
            worker_pull_submitted(ts, self);
            for (int prio = 0; prio < TASK_PRIORITY_COUNT && !task; prio++) {
                task = deque_pop(&self->queues[prio]);
            }
        }

        /* 3. Steal from other workers */
        if (!task) {
            u32 start = (self->id + self->steal_attempts + 1) % ts->worker_count;
            for (u32 i = 0; i < ts->worker_count - 1 && !task; i++) {
                u32 victim = (start + i) % ts->worker_count;
                if (victim == self->id) continue;
                for (int prio = 0; prio < TASK_PRIORITY_COUNT && !task; prio++) {
                    task = deque_steal(&ts->workers[victim].queues[prio]);
                }
            }
            if (task) atomic_fetch_add_explicit(&self->stolen, 1, memory_order_relaxed);
        }

        /* 4. Execute or backoff */
        if (task) {
            self->steal_attempts = 0;
            self->backoff_ns = 100;
            execute_task(ts, self, task);
        } else {
            self->steal_attempts++;
            if (self->steal_attempts > ts->worker_count * 2) {
                atomic_fetch_add_explicit(&self->idle_sleeps, 1, memory_order_relaxed);
                platform_sleep_ns(self->backoff_ns);
                /* R414: cap backoff at 50us (was 1ms) — see Windows path. */
                if (self->backoff_ns < 50000) {
                    self->backoff_ns *= 2;
                } else {
                    self->backoff_ns = 50000; /* max 50us */
                }
            }
        }
    }

    atomic_store_explicit(&self->active, false, memory_order_release);
    return PLATFORM_THREAD_RETURN;
}


/* ============================================================
 * Public API: Create / Destroy
 * ============================================================ */

TaskSystem *task_system_create(i32 worker_count) {
    if (worker_count <= 0) {
        u32 cores = platform_cpu_count();
        worker_count = (i32)(cores > 1 ? cores - 1 : 1);
    }

    /* Single allocation: TaskSystem + task_pool[4096] + _task_block[4096] + workers[N].
     * Layout: [TaskSystem][Task* pool * cap][Task block * cap][Worker * N] */
    u32 cap = 4096;
    usize ts_bytes     = sizeof(TaskSystem);
    usize pool_bytes   = (usize)cap * sizeof(Task *);
    usize block_bytes  = (usize)cap * sizeof(Task);
    usize worker_bytes = (usize)worker_count * sizeof(Worker);
    usize worker_off   = ts_bytes + pool_bytes + block_bytes;
    /* R414: Worker is ENGINE_ALIGN(64) but calloc only guarantees max_align —
     * over-allocate and round the workers pointer up to a 64-byte boundary. */
    u8 *mem = (u8 *)calloc(1, worker_off + 64 + worker_bytes);
    if (!mem) return NULL;

    TaskSystem *ts = (TaskSystem *)mem;
    ts->worker_count = (u32)worker_count;
    ts->task_pool_capacity = cap;
    ts->task_pool    = (Task **)(mem + ts_bytes);
    ts->_task_block  = (Task *)(mem + ts_bytes + pool_bytes);
    ts->workers      = (Worker *)(((uintptr_t)mem + worker_off + 63u) & ~(uintptr_t)63u);

    atomic_store_explicit(&ts->running, true, memory_order_relaxed);
    atomic_store_explicit(&ts->total_tasks_completed, 0, memory_order_relaxed);
    atomic_store_explicit(&ts->total_tasks_cancelled, 0, memory_order_relaxed);
    atomic_store_explicit(&ts->inline_executed, 0, memory_order_relaxed);
    atomic_store_explicit(&ts->total_tasks_submitted, 0, memory_order_relaxed);
    atomic_store_explicit(&ts->next_handle, 0, memory_order_relaxed);
    atomic_store_explicit(&ts->submit_count, 0, memory_order_relaxed);

    /* Init submit mutex */
    platform_mutex_init(&ts->submit_mutex);

    /* Init task pool */
    atomic_store_explicit(&ts->task_pool_count, 0, memory_order_relaxed);
    platform_mutex_init(&ts->pool_mutex);

    /* Init workers */
    for (i32 i = 0; i < worker_count; i++) {
        Worker *w = &ts->workers[i];
        w->id = (u32)i;
        w->steal_attempts = 0;
        w->backoff_ns = 100;
        atomic_init(&w->executed, 0u);
        atomic_init(&w->stolen, 0u);
        atomic_init(&w->idle_sleeps, 0u);
        atomic_store_explicit(&w->active, false, memory_order_relaxed);
        for (int p = 0; p < TASK_PRIORITY_COUNT; p++) {
            if (!deque_init(&w->queues[p], DEQUE_CAPACITY)) {
                /* R166-A: calloc failure — destroy already-initialized deques and abort */
                LOG_FATAL("Task system: deque_init OOM at worker %d priority %d", i, p);
                for (i32 j = 0; j <= i; j++) {
                    Worker *wj = &ts->workers[j];
                    for (int q = 0; q < TASK_PRIORITY_COUNT; q++) {
                        if (j == i && q == p) break;
                        deque_destroy(&wj->queues[q]);
                    }
                }
                platform_mutex_destroy(&ts->submit_mutex);
                platform_mutex_destroy(&ts->pool_mutex);
                free(ts);
                return NULL;
            }
        }
    }

    /* Task lifetime accounting uses a process-wide ownership pointer. Claim it
     * before starting workers so concurrent creators cannot install a second
     * live system and make task_release() inspect the wrong pool. */
    TaskSystem *expected_system = NULL;
    if (!atomic_compare_exchange_strong_explicit(&g_task_system, &expected_system, ts,
                                                 memory_order_release,
                                                 memory_order_acquire)) {
        LOG_ERROR("Task system: only one live instance is supported");
        for (i32 i = 0; i < worker_count; i++) {
            for (int p = 0; p < TASK_PRIORITY_COUNT; p++) {
                deque_destroy(&ts->workers[i].queues[p]);
            }
        }
        platform_mutex_destroy(&ts->submit_mutex);
        platform_mutex_destroy(&ts->pool_mutex);
        free(ts);
        return NULL;
    }

    /* Start worker threads */
    for (i32 i = 0; i < worker_count; i++) {
        Worker *w = &ts->workers[i];
        bool thread_ok;
        thread_ok = platform_thread_create(&w->thread, worker_entry, w);
        if (!thread_ok) {
            LOG_ERROR("Task system: failed to create worker thread %d", i);
            /* R141: Destroy deques for workers that were initialized but won't get threads */
            for (i32 j = i; j < worker_count; j++) {
                Worker *wj = &ts->workers[j];
                for (int p = 0; p < TASK_PRIORITY_COUNT; p++) {
                    deque_destroy(&wj->queues[p]);
                }
            }
            ts->worker_count = (u32)i;
            if (ts->worker_count == 0) {
                /* R167-G: No workers at all — fail create instead of returning
                 * a degraded handle that silently runs everything on the main thread. */
                LOG_FATAL("Task system: failed to create any worker threads");
                platform_mutex_destroy(&ts->submit_mutex);
                platform_mutex_destroy(&ts->pool_mutex);
                free(ts);
                atomic_store_explicit(&g_task_system, NULL, memory_order_release);
                return NULL;
            }
            break;
        }
    }

    LOG_INFO("Task system: %d workers (Chase-Lev work-stealing)", ts->worker_count);
    return ts;
}

void task_system_destroy(TaskSystem *ts) {
    /* R174: Force-resolve any blocked dependents so task_wait cannot hang on
     * incomplete graphs, then drain runnable work before stopping workers. */
    u32 pool_count = atomic_load(&ts->task_pool_count);
    if (pool_count > ts->task_pool_capacity) pool_count = ts->task_pool_capacity;
    platform_mutex_lock(&ts->pool_mutex);
    for (u32 i = 0; i < pool_count; i++) {
        Task *t = ts->task_pool[i];
        if (!t) continue;
        while (t->waiters) {
            TaskWaitLink *link = t->waiters;
            t->waiters = link->next;
            Task *child = link->child;
            free(link);
            if (!child) continue;
            u32 left = atomic_exchange_explicit(&child->dep_count, 0u, memory_order_acq_rel);
            if (left > 0u) {
                platform_mutex_unlock(&ts->pool_mutex);
                schedule_ready(ts, NULL, child);
                platform_mutex_lock(&ts->pool_mutex);
            }
            task_release(child);
        }
    }
    platform_mutex_unlock(&ts->pool_mutex);

    task_wait(ts);

    /* Signal shutdown */
    atomic_store_explicit(&ts->running, false, memory_order_release);

    /* Join all workers */
    for (u32 i = 0; i < ts->worker_count; i++) {
        Worker *w = &ts->workers[i];
        platform_thread_join(w->thread);
    }

    /* Cleanup deques */
    for (u32 i = 0; i < ts->worker_count; i++) {
        for (int p = 0; p < TASK_PRIORITY_COUNT; p++) {
            deque_destroy(&ts->workers[i].queues[p]);
        }
    }

    /* R156: Clamp to capacity — task_pool_count can exceed task_pool_capacity
     * when the pool is exhausted and tasks fall back to heap allocation. */
    pool_count = atomic_load(&ts->task_pool_count);
    if (pool_count > ts->task_pool_capacity) pool_count = ts->task_pool_capacity;
    for (u32 i = 0; i < pool_count; i++) {
        Task *t = ts->task_pool[i];
        if (!t) continue;
        while (t->waiters) {
            TaskWaitLink *link = t->waiters;
            t->waiters = link->next;
            free(link);
        }
        task_release(t);
    }

    platform_mutex_destroy(&ts->submit_mutex);
    platform_mutex_destroy(&ts->pool_mutex);
    task_trace_free(atomic_load_explicit(&ts->trace, memory_order_acquire));

    /* Single free: task_pool, _task_block, and workers are within the same block */
    free(ts);

    atomic_store_explicit(&g_task_system, NULL, memory_order_release);
}

/* ============================================================
 * Public API: Submit
 * ============================================================ */

static void submit_to_system(TaskSystem *ts, Task *t) {
    atomic_fetch_add_explicit(&ts->total_tasks_submitted, 1, memory_order_relaxed);

    /* If called from a worker thread, push directly to the local deque
     * (owner push — the only thread that pushes this deque's bottom). */
    if (tls_worker_id >= 0 && (u32)tls_worker_id < ts->worker_count) {
        Worker *w = &ts->workers[tls_worker_id];
        if (deque_push(&w->queues[t->priority], t)) {
            return;
        }
    }

    /* Otherwise (or if the local deque is full), use the global submit queue. */
    enqueue_global(ts, t);
}

void task_submit(TaskSystem *ts, TaskFn fn, void *ctx) {
    /* R424: a NULL fn would crash a worker in execute_task — reject it. */
    if (!fn) return;
    Task *t = task_alloc(ts, fn, ctx, TASK_PRIORITY_NORMAL);
    if (!t) return;  /* R156: calloc failure */
    submit_to_system(ts, t);
}

void task_submit_n(TaskSystem *ts, TaskFn fn, void **ctxs, i32 count) {
    /* R420: ctxs==NULL with count>0 dereferenced NULL — validate like the
     * other submit paths. */
    if (count > 0 && !ctxs) return;
    /* R424: a NULL fn would crash a worker in execute_task — reject it. */
    if (!fn) return;
    for (i32 i = 0; i < count; i++) {
        Task *t = task_alloc(ts, fn, ctxs[i], TASK_PRIORITY_NORMAL);
        if (!t) continue;  /* R156: calloc failure */
        submit_to_system(ts, t);
    }
}

TaskHandle task_submit_ex(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio) {
    /* R414: prio indexes Worker.queues[TASK_PRIORITY_COUNT] — clamp garbage
     * values (e.g. from a bad cast) before they cause an OOB deque access. */
    if ((u32)prio >= TASK_PRIORITY_COUNT) prio = TASK_PRIORITY_NORMAL;
    /* R424: a NULL fn would crash a worker in execute_task — reject it. */
    if (!fn) return TASK_HANDLE_INVALID;
    Task *t = task_alloc(ts, fn, ctx, prio);
    if (!t) return TASK_HANDLE_INVALID;  /* R156: calloc failure */
    TaskHandle h = t->handle;
    submit_to_system(ts, t);
    return h;
}

static TaskHandle task_submit_with(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio,
                                   const TaskCancelToken *token, TaskHandle *deps,
                                   u32 dep_count);

TaskHandle task_submit_dep(TaskSystem *ts, TaskFn fn, void *ctx,
                           TaskHandle *deps, u32 dep_count) {
    return task_submit_with(ts, fn, ctx, TASK_PRIORITY_NORMAL, NULL, deps, dep_count);
}

TaskHandle task_submit_cancellable(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio,
                                   const TaskCancelToken *token, TaskHandle *deps,
                                   u32 dep_count) {
    if ((u32)prio >= TASK_PRIORITY_COUNT) prio = TASK_PRIORITY_NORMAL;
    return task_submit_with(ts, fn, ctx, prio, token, deps, dep_count);
}

static TaskHandle task_submit_with(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio,
                                   const TaskCancelToken *token, TaskHandle *deps,
                                   u32 dep_count) {
    /* R420: deps==NULL with dep_count>0 dereferenced NULL below — fail the
     * submission instead of segfaulting. */
    if (dep_count > 0 && !deps) return TASK_HANDLE_INVALID;
    /* R424: a NULL fn would crash a worker in execute_task — reject it. */
    if (!fn) return TASK_HANDLE_INVALID;
    Task *t = task_alloc(ts, fn, ctx, prio);
    if (!t) return TASK_HANDLE_INVALID;  /* R156: calloc failure */
    t->cancel = token;
    TaskHandle h = t->handle;

    /* R173: Count toward task_wait even while blocked on deps. */
    atomic_fetch_add_explicit(&ts->total_tasks_submitted, 1, memory_order_relaxed);

    /* R170/R173: Link into each dep's waiter list (fan-out). Skip completed. */
    u32 actual_deps = 0u;
    bool oom = false;

    platform_mutex_lock(&ts->pool_mutex);
    for (u32 d = 0; d < dep_count; d++) {
        u32 idx = (u32)(deps[d] & 0xFFFFFFFFu);
        /* R414: a heap-fallback task handle (idx 0xFFFFFFFF) cannot be
         * resolved through task_pool — fail the submission instead of
         * silently dropping the dependency. Reuses the oom unwind path. */
        if (idx == 0xFFFFFFFFu) { oom = true; break; }
        if (idx >= ts->task_pool_capacity) continue;
        Task *dep = ts->task_pool[idx];
        if (!dep || dep->handle != deps[d]) continue;
        if (atomic_load_explicit(&dep->completed, memory_order_acquire)) continue;

        TaskWaitLink *link = (TaskWaitLink *)malloc(sizeof(TaskWaitLink));
        if (!link) { oom = true; break; }
        link->child = t;
        link->next = dep->waiters;
        dep->waiters = link;
        actual_deps++;
        atomic_fetch_add_explicit(&t->ref_count, 1, memory_order_relaxed);
    }

    /* R177: malloc failure must not under-count deps (child would run early). */
    if (oom) {
        for (u32 d = 0; d < dep_count; d++) {
            u32 idx = (u32)(deps[d] & 0xFFFFFFFFu);
            if (idx >= ts->task_pool_capacity) continue;
            Task *dep = ts->task_pool[idx];
            if (!dep || dep->handle != deps[d]) continue;
            TaskWaitLink **pp = &dep->waiters;
            while (*pp) {
                if ((*pp)->child == t) {
                    TaskWaitLink *dead = *pp;
                    *pp = dead->next;
                    free(dead);
                    task_release(t);
                    break;
                }
                pp = &(*pp)->next;
            }
        }
        atomic_store_explicit(&t->dep_count, 0u, memory_order_release);
        atomic_store_explicit(&t->completed, true, memory_order_release);
        platform_mutex_unlock(&ts->pool_mutex);
        atomic_fetch_sub_explicit(&ts->total_tasks_submitted, 1, memory_order_relaxed);
        /* Drop exec ref — frees heap-fallback tasks; pool ref retained for
         * pool tasks. */
        task_release(t);
        return TASK_HANDLE_INVALID;
    }

    struct TaskTraceLog *trace = dep_count > 0u ? trace_active(ts) : NULL;
    if (trace) {
        for (u32 d = 0; d < dep_count; d++) {
            u32 idx = (u32)(deps[d] & 0xFFFFFFFFu);
            if (idx >= ts->task_pool_capacity) continue;
            Task *dep = ts->task_pool[idx];
            if (!dep || dep->handle != deps[d]) continue;
            trace_add_edge(trace, deps[d], h);
        }
    }
    atomic_store_explicit(&t->dep_count, actual_deps, memory_order_release);
    platform_mutex_unlock(&ts->pool_mutex);

    /* Ready now — enqueue without double-counting submitted. */
    if (actual_deps == 0u) {
        if (tls_worker_id >= 0 && (u32)tls_worker_id < ts->worker_count) {
            Worker *w = &ts->workers[tls_worker_id];
            if (deque_push(&w->queues[t->priority], t)) return h;
        }
        enqueue_global(ts, t);
    }

    return h;
}

/* ============================================================
 * Public API: Wait
 * ============================================================ */

void task_wait(TaskSystem *ts) {
    /* Contract (task.h): not callable from a worker task — the wait set
     * includes the caller's own running task, which can never complete while
     * it waits, so the loop below could never exit (self-deadlock). */
    if (tls_worker_id >= 0 && (u32)tls_worker_id < ts->worker_count) {
        LOG_WARN("task_wait called from a worker task (self-deadlock) — returning");
        return;
    }
    /* Spin until all submitted tasks are completed */
    while (true) {
        u64 submitted = atomic_load_explicit(&ts->total_tasks_submitted, memory_order_acquire);
        u64 completed = atomic_load_explicit(&ts->total_tasks_completed, memory_order_acquire);
        u32 pending = atomic_load_explicit(&ts->submit_count, memory_order_acquire);

        if (completed >= submitted && pending == 0) {
            break;
        }

        /* Help process tasks while waiting. */
        if (tls_worker_id >= 0 && (u32)tls_worker_id < ts->worker_count) {
            Worker *w = &ts->workers[tls_worker_id];
            Task *task = NULL;
            for (int prio = 0; prio < TASK_PRIORITY_COUNT && !task; prio++) {
                task = deque_pop(&w->queues[prio]);
            }
            if (!task) {
                worker_pull_submitted(ts, w);
                for (int prio = 0; prio < TASK_PRIORITY_COUNT && !task; prio++) {
                    task = deque_pop(&w->queues[prio]);
                }
            }
            if (task) {
                execute_task(ts, w, task);
                continue;
            }
        } else if (drain_submitted_inline(ts)) {
            /* Non-worker (main) thread: run queued tasks inline. */
            continue;
        }

        /* R414: steal from worker deques before sleeping — deque_steal is
         * CAS-based and safe for any thief thread, and it cuts wait latency
         * when work is stuck in a sleeping worker's deque. */
        Task *stolen = NULL;
        for (u32 v = 0; v < ts->worker_count && !stolen; v++) {
            for (int prio = 0; prio < TASK_PRIORITY_COUNT && !stolen; prio++) {
                stolen = deque_steal(&ts->workers[v].queues[prio]);
            }
        }
        if (stolen) {
            execute_task(ts, NULL, stolen);
            continue;
        }

        platform_sleep_ns(50000); /* R429: 50us, matching R414 worker backoff */
    }
}

void task_wait_handle(TaskSystem *ts, TaskHandle handle) {
    /* O(1) lookup via pool index encoded in the lower 32 bits of the handle. */
    u32 idx = (u32)(handle & 0xFFFFFFFFu);
    u32 gen = (u32)(handle >> 32);

    /* R156: Check against task_pool_capacity, not task_pool_count —
     * pool_count can exceed capacity when pool is exhausted. */
    /* R414: heap-fallback tasks are never registered in task_pool, so their
     * handles (idx 0xFFFFFFFF) cannot be resolved to a Task. Do NOT silently
     * return here: a caller that waits before releasing the task's ctx would
     * race the still-running task (UAF). Wait conservatively for ALL submitted
     * tasks instead — task_wait() returns only after this task (and everything
     * submitted so far) has completed, so the wait is real. */
    if (idx == 0xFFFFFFFFu) { task_wait(ts); return; }
    if (idx >= ts->task_pool_capacity) return;  /* handle not found — already done */

    Task *t = ts->task_pool[idx];
    if (!t || (u32)(t->handle >> 32) != gen) return;  /* recycled slot */

    /* Spin until this specific task completes. The task is kept alive by the
     * reference the pool holds (released only in task_system_destroy), so this
     * dereference is safe even after the task's execution ref is dropped. */
    while (!atomic_load_explicit(&t->completed, memory_order_acquire)) {
        /* Help process tasks while waiting (same as task_wait). */
        if (tls_worker_id >= 0 && (u32)tls_worker_id < ts->worker_count) {
            Worker *w = &ts->workers[tls_worker_id];
            Task *help = NULL;
            for (int prio = 0; prio < TASK_PRIORITY_COUNT && !help; prio++) {
                help = deque_pop(&w->queues[prio]);
            }
            if (!help) {
                worker_pull_submitted(ts, w);
                for (int prio = 0; prio < TASK_PRIORITY_COUNT && !help; prio++) {
                    help = deque_pop(&w->queues[prio]);
                }
            }
            if (help) {
                execute_task(ts, w, help);
                continue;
            }
        } else if (drain_submitted_inline(ts)) {
            continue;
        }
        platform_sleep_ns(50000);  /* R429: 50us, matching R414 worker backoff */
    }
}

/* ============================================================
 * Public API: Query
 * ============================================================ */

i32 task_worker_id(TaskSystem *ts) {
    (void)ts;
    return tls_worker_id;
}

u32 task_worker_count(TaskSystem *ts) {
    return ts->worker_count;
}

void task_cancel_token_init(TaskCancelToken *token) {
    if (token) atomic_init(&token->cancelled, false);
}

void task_cancel(TaskCancelToken *token) {
    if (token) atomic_store_explicit(&token->cancelled, true, memory_order_release);
}

bool task_cancel_requested(const TaskCancelToken *token) {
    return token && atomic_load_explicit(&token->cancelled, memory_order_acquire);
}

bool task_worker_stats(TaskSystem *ts, u32 worker_id, TaskWorkerStats *out) {
    if (!ts || !out || worker_id >= ts->worker_count) return false;
    const Worker *w = &ts->workers[worker_id];
    out->executed = atomic_load_explicit(&w->executed, memory_order_relaxed);
    out->stolen = atomic_load_explicit(&w->stolen, memory_order_relaxed);
    out->idle_sleeps = atomic_load_explicit(&w->idle_sleeps, memory_order_relaxed);
    return true;
}

u64 task_inline_executed(TaskSystem *ts) {
    return ts ? atomic_load_explicit(&ts->inline_executed, memory_order_relaxed) : 0u;
}

u64 task_cancelled_count(TaskSystem *ts) {
    return ts ? atomic_load_explicit(&ts->total_tasks_cancelled, memory_order_relaxed) : 0u;
}

bool task_trace_enable(TaskSystem *ts, u32 capacity) {
    if (!ts || capacity == 0u || capacity > 0x3FFFFFFFu) return false;
    struct TaskTraceLog *log = (struct TaskTraceLog *)calloc(1, sizeof(*log));
    if (!log) return false;
    log->capacity = capacity;
    log->edge_capacity = capacity * 4u;
    log->records = (TaskTraceRecord *)calloc(capacity, sizeof(TaskTraceRecord));
    log->edges = (TaskTraceEdge *)calloc(log->edge_capacity, sizeof(TaskTraceEdge));
    if (!log->records || !log->edges) {
        task_trace_free(log);
        return false;
    }
    atomic_init(&log->next, 0u);
    atomic_init(&log->dropped, 0u);
    atomic_init(&log->edge_next, 0u);
    log->origin_ns = task_clock_ns();
    atomic_init(&log->active, true);
    task_trace_free(atomic_exchange_explicit(&ts->trace, log, memory_order_acq_rel));
    return true;
}

void task_trace_disable(TaskSystem *ts) {
    struct TaskTraceLog *log = ts ? atomic_load_explicit(&ts->trace, memory_order_acquire) : NULL;
    if (log) atomic_store_explicit(&log->active, false, memory_order_relaxed);
}

bool task_trace_enabled(TaskSystem *ts) {
    return ts && trace_active(ts) != NULL;
}

static struct TaskTraceLog *trace_log(TaskSystem *ts) {
    return ts ? atomic_load_explicit(&ts->trace, memory_order_acquire) : NULL;
}

u32 task_trace_record_count(TaskSystem *ts) {
    struct TaskTraceLog *log = trace_log(ts);
    if (!log) return 0u;
    u64 n = atomic_load_explicit(&log->next, memory_order_relaxed);
    return n < log->capacity ? (u32)n : log->capacity;
}

u64 task_trace_dropped(TaskSystem *ts) {
    struct TaskTraceLog *log = trace_log(ts);
    return log ? atomic_load_explicit(&log->dropped, memory_order_relaxed) : 0u;
}

u32 task_trace_edge_count(TaskSystem *ts) {
    struct TaskTraceLog *log = trace_log(ts);
    if (!log) return 0u;
    u64 n = atomic_load_explicit(&log->edge_next, memory_order_relaxed);
    return n < log->edge_capacity ? (u32)n : log->edge_capacity;
}

bool task_trace_get(TaskSystem *ts, u32 index, TaskTraceRecord *out) {
    if (!out || index >= task_trace_record_count(ts)) return false;
    *out = trace_log(ts)->records[index];
    return true;
}

typedef struct {
    char *buf;
    usize capacity;
    usize len;
} TaskTraceWriter;

static void trace_printf(TaskTraceWriter *w, const char *fmt, ...) {
    char tmp[256];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(tmp, sizeof tmp, fmt, ap);
    va_end(ap);
    if (n <= 0) return;
    usize len = (usize)n < sizeof tmp ? (usize)n : sizeof tmp - 1u;
    if (w->len + len < w->capacity) memcpy(w->buf + w->len, tmp, len);
    w->len += len;
}

typedef struct {
    TaskHandle handle;
    u32 index;
} TaskTraceIndex;

static int trace_index_cmp(const void *a, const void *b) {
    TaskHandle ha = ((const TaskTraceIndex *)a)->handle;
    TaskHandle hb = ((const TaskTraceIndex *)b)->handle;
    return ha < hb ? -1 : (ha > hb ? 1 : 0);
}

static const TaskTraceRecord *trace_find(const struct TaskTraceLog *log,
                                         const TaskTraceIndex *index, u32 count,
                                         TaskHandle handle) {
    TaskTraceIndex key = {handle, 0u};
    const TaskTraceIndex *hit = (const TaskTraceIndex *)bsearch(
        &key, index, count, sizeof(TaskTraceIndex), trace_index_cmp);
    return hit ? &log->records[hit->index] : NULL;
}

/* Track 0 is the inline track; worker w is track w + 1. */
static u32 trace_tid(i32 worker) {
    return worker < 0 ? 0u : (u32)worker + 1u;
}

bool task_trace_export(TaskSystem *ts, char *buf, usize capacity, usize *out_len) {
    if (out_len) *out_len = 0u;
    struct TaskTraceLog *log = trace_log(ts);
    if (!log) {
        if (buf && capacity > 0u) buf[0] = '\0';
        return false;
    }
    u32 count = task_trace_record_count(ts);
    u32 edges = task_trace_edge_count(ts);
    TaskTraceIndex *index = NULL;
    if (count > 0u) {
        index = (TaskTraceIndex *)malloc((usize)count * sizeof(TaskTraceIndex));
        if (!index) {
            if (buf && capacity > 0u) buf[0] = '\0';
            return false;
        }
        for (u32 i = 0; i < count; i++) {
            index[i].handle = log->records[i].handle;
            index[i].index = i;
        }
        qsort(index, count, sizeof(TaskTraceIndex), trace_index_cmp);
    }

    TaskTraceWriter w = {buf, buf ? capacity : 0u, 0u};
    trace_printf(&w, "{\"traceEvents\":[\n");
    trace_printf(&w, "{\"name\":\"thread_name\",\"ph\":\"M\",\"pid\":1,\"tid\":0,"
                     "\"args\":{\"name\":\"inline\"}}");
    for (u32 i = 0; i < ts->worker_count; i++) {
        trace_printf(&w, ",\n{\"name\":\"thread_name\",\"ph\":\"M\",\"pid\":1,\"tid\":%u,"
                         "\"args\":{\"name\":\"worker %u\"}}", i + 1u, i);
    }
    for (u32 i = 0; i < count; i++) {
        const TaskTraceRecord *r = &log->records[i];
        trace_printf(&w, ",\n{\"name\":\"task\",\"cat\":\"" BREAK_TRACE_CAT_TASK "\",\"ph\":\"X\","
                         "\"ts\":%.3f,\"dur\":%.3f,\"pid\":1,\"tid\":%u,"
                         "\"args\":{\"handle\":%llu,\"cancelled\":%s}}",
                     (double)r->start_ns / 1000.0, (double)(r->end_ns - r->start_ns) / 1000.0,
                     trace_tid(r->worker), (unsigned long long)r->handle,
                     r->cancelled ? "true" : "false");
    }
    u32 flow_id = 0u;
    for (u32 e = 0; e < edges; e++) {
        const TaskTraceRecord *from = trace_find(log, index, count, log->edges[e].from);
        const TaskTraceRecord *to = trace_find(log, index, count, log->edges[e].to);
        if (!from || !to) continue;
        flow_id++;
        trace_printf(&w, ",\n{\"name\":\"dependency\",\"cat\":\"" BREAK_TRACE_CAT_TASK_FLOW "\","
                         "\"ph\":\"s\",\"id\":%u,\"ts\":%.3f,\"pid\":1,\"tid\":%u}",
                     flow_id, (double)from->start_ns / 1000.0, trace_tid(from->worker));
        trace_printf(&w, ",\n{\"name\":\"dependency\",\"cat\":\"" BREAK_TRACE_CAT_TASK_FLOW "\","
                         "\"ph\":\"f\",\"bp\":\"e\",\"id\":%u,\"ts\":%.3f,\"pid\":1,\"tid\":%u}",
                     flow_id, (double)to->start_ns / 1000.0, trace_tid(to->worker));
    }
    trace_printf(&w, "\n]," BREAK_TRACE_OTHER_DATA "}");
    free(index);

    if (out_len) *out_len = w.len;
    if (w.len >= w.capacity) {
        if (buf && capacity > 0u) buf[0] = '\0';
        return false;
    }
    buf[w.len] = '\0';
    return true;
}
