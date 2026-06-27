#include <task/task.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>

#ifdef ENGINE_PLATFORM_WINDOWS
    #include <windows.h>
    #include <process.h>
#else
    #include <pthread.h>
    #include <time.h>
    #include <unistd.h>
#endif

/* ============================================================
 * Platform Abstraction
 * ============================================================ */

#ifdef ENGINE_PLATFORM_WINDOWS

static inline void platform_mutex_init(void *storage) {
    CRITICAL_SECTION *cs = (CRITICAL_SECTION *)storage;
    InitializeCriticalSection(cs);
}
static inline void platform_mutex_destroy(void *storage) {
    CRITICAL_SECTION *cs = (CRITICAL_SECTION *)storage;
    DeleteCriticalSection(cs);
}
static inline void platform_mutex_lock(void *storage) {
    EnterCriticalSection((CRITICAL_SECTION *)storage);
}
static inline void platform_mutex_unlock(void *storage) {
    LeaveCriticalSection((CRITICAL_SECTION *)storage);
}
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
typedef unsigned (__stdcall *win_thread_fn)(void *);
static inline bool platform_thread_create(void *handle_out, unsigned (__stdcall *fn)(void *), void *arg) {
    HANDLE h = (HANDLE)_beginthreadex(NULL, 0, fn, arg, 0, NULL);
    *(HANDLE *)handle_out = h;
    return h != NULL;
}
static inline void platform_thread_join(void *handle_storage) {
    HANDLE h = *(HANDLE *)handle_storage;
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
}

#else /* POSIX */

static inline void platform_mutex_init(void *storage) {
    pthread_mutex_init((pthread_mutex_t *)storage, NULL);
}
static inline void platform_mutex_destroy(void *storage) {
    pthread_mutex_destroy((pthread_mutex_t *)storage);
}
static inline void platform_mutex_lock(void *storage) {
    pthread_mutex_lock((pthread_mutex_t *)storage);
}
static inline void platform_mutex_unlock(void *storage) {
    pthread_mutex_unlock((pthread_mutex_t *)storage);
}
static inline void platform_sleep_ns(u32 ns) {
    struct timespec ts = { 0, (long)ns };
    nanosleep(&ts, NULL);
}
static inline u32 platform_cpu_count(void) {
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    return n > 0 ? (u32)n : 1;
}
static inline bool platform_thread_create_posix(void *storage, void *(*fn)(void *), void *arg) {
    return pthread_create((pthread_t *)storage, NULL, fn, arg) == 0;
}
static inline void platform_thread_join_posix(void *storage) {
    pthread_join(*(pthread_t *)storage, NULL);
}

#endif

/* ============================================================
 * Thread-local worker ID
 * ============================================================ */

static _Thread_local i32 tls_worker_id = -1;

/* ============================================================
 * Chase-Lev Work-Stealing Deque
 * ============================================================ */

static void deque_init(WorkStealDeque *dq, u32 capacity) {
    dq->capacity = capacity;
    dq->buffer = (Task **)calloc(capacity, sizeof(Task *));
    atomic_store_explicit(&dq->top, 0, memory_order_relaxed);
    atomic_store_explicit(&dq->bottom, 0, memory_order_relaxed);
}

static void deque_destroy(WorkStealDeque *dq) {
    free(dq->buffer);
    dq->buffer = NULL;
}

/* Owner thread push (bottom) */
static bool deque_push(WorkStealDeque *dq, Task *task) {
    i64 b = atomic_load_explicit(&dq->bottom, memory_order_relaxed);
    i64 t = atomic_load_explicit(&dq->top, memory_order_acquire);

    if (b - t >= (i64)dq->capacity) {
        return false; /* full */
    }

    dq->buffer[b & (i64)(dq->capacity - 1)] = task;
    atomic_thread_fence(memory_order_release);
    atomic_store_explicit(&dq->bottom, b + 1, memory_order_relaxed);
    return true;
}

/* Owner thread pop (bottom, LIFO) */
static Task *deque_pop(WorkStealDeque *dq) {
    i64 b = atomic_load_explicit(&dq->bottom, memory_order_relaxed) - 1;
    atomic_store_explicit(&dq->bottom, b, memory_order_relaxed);
    atomic_thread_fence(memory_order_seq_cst);
    i64 t = atomic_load_explicit(&dq->top, memory_order_relaxed);

    if (t <= b) {
        Task *task = dq->buffer[b & (i64)(dq->capacity - 1)];
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

    Task *task = dq->buffer[t & (i64)(dq->capacity - 1)];

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
static TaskSystem *g_task_system;

static Task *task_alloc(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio) {
    /* Lock-free bump allocation: atomic_fetch_add gives each caller a unique
     * pool_idx without mutex contention. Each caller writes to a distinct
     * task_pool[pool_idx] slot, so no data race occurs. */
    Task *t = NULL;
    u32 pool_idx = atomic_fetch_add_explicit(&ts->task_pool_count, 1, memory_order_acq_rel);
    if (pool_idx < ts->task_pool_capacity) {
        t = &ts->_task_block[pool_idx];
        ts->task_pool[pool_idx] = t;
    }

    if (!t) {
        /* Fallback: pool exhausted, allocate on heap */
        t = (Task *)calloc(1, sizeof(Task));
        /* Best-effort registration: mutex only needed for this rare path */
        platform_mutex_lock(ts->pool_mutex_storage);
        u32 cur = atomic_load(&ts->task_pool_count);
        if (cur <= ts->task_pool_capacity) {
            pool_idx = cur - 1;
            if (pool_idx < ts->task_pool_capacity) {
                ts->task_pool[pool_idx] = t;
            }
        }
        platform_mutex_unlock(ts->pool_mutex_storage);
    }

    memset(t, 0, sizeof(Task));
    t->fn = fn;
    t->ctx = ctx;
    t->priority = prio;
    atomic_store_explicit(&t->dep_count, 0, memory_order_relaxed);
    atomic_store_explicit(&t->ref_count, 2, memory_order_relaxed); /* exec ref + pool ref */
    t->parent = NULL;

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
        TaskSystem *ts = g_task_system;
        bool is_block = ts && t >= ts->_task_block &&
                        t < ts->_task_block + ts->task_pool_capacity;
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
 *    under `submit_mutex_storage`. In particular the count reset uses an
 *    exchange *inside* the lock so a concurrent submit can never overwrite an
 *    unprocessed slot.
 * ============================================================ */

static void execute_task(TaskSystem *ts, Worker *self, Task *task);

/* Enqueue to the mutex-protected global submit queue (used by non-worker
 * submitters and as a fallback when a local deque is full). */
static void enqueue_global(TaskSystem *ts, Task *t) {
    platform_mutex_lock(ts->submit_mutex_storage);
    u32 idx = atomic_load_explicit(&ts->submit_count, memory_order_relaxed);
    if (idx < SUBMIT_QUEUE_CAPACITY) {
        ts->submit_queue[idx] = t;
        atomic_store_explicit(&ts->submit_count, idx + 1, memory_order_release);
        platform_mutex_unlock(ts->submit_mutex_storage);
    } else {
        /* Queue full (rare) — run inline so the task is never lost. */
        platform_mutex_unlock(ts->submit_mutex_storage);
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
    platform_mutex_lock(ts->submit_mutex_storage);
    u32 count = atomic_exchange_explicit(&ts->submit_count, 0, memory_order_relaxed);
    u32 n = 0;
    for (u32 i = 0; i < count; i++) {
        Task *t = ts->submit_queue[i];
        ts->submit_queue[i] = NULL;
        if (t) out[n++] = t;
    }
    platform_mutex_unlock(ts->submit_mutex_storage);
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

static void execute_task(TaskSystem *ts, Worker *self, Task *task) {
    task->fn(task->ctx);

    /* Mark completed BEFORE dependency resolution so wait_handle can see it. */
    atomic_store_explicit(&task->completed, true, memory_order_release);
    atomic_fetch_add_explicit(&ts->total_tasks_completed, 1, memory_order_relaxed);

    /* Resolve parent dependency. Each dependency holds one reference to the
     * parent (taken in task_submit_dep); release it here. */
    Task *parent = task->parent;
    if (parent) {
        u32 old = atomic_fetch_sub_explicit(&parent->dep_count, 1, memory_order_acq_rel);
        if (old == 1) {
            /* All dependencies resolved — schedule parent (owner-safe). */
            schedule_ready(ts, self, parent);
        }
        task_release(parent);
    }

    task_release(task);
}

/* ============================================================
 * Global pointer for worker thread TaskSystem access
 * (forward-declared above task_alloc)
 * ============================================================ */

/* Fixup: workers need access to TaskSystem. We use the global. */

#ifdef ENGINE_PLATFORM_WINDOWS
static unsigned __stdcall worker_entry(void *arg) {
    Worker *self = (Worker *)arg;
    TaskSystem *ts = g_task_system;
    tls_worker_id = (i32)self->id;
    atomic_store_explicit(&self->active, true, memory_order_release);

    while (atomic_load_explicit(&ts->running, memory_order_acquire)) {
        Task *task = NULL;

        for (int prio = 0; prio < TASK_PRIORITY_COUNT && !task; prio++) {
            task = deque_pop(&self->queues[prio]);
        }

        if (!task) {
            worker_pull_submitted(ts, self);
            for (int prio = 0; prio < TASK_PRIORITY_COUNT && !task; prio++) {
                task = deque_pop(&self->queues[prio]);
            }
        }

        if (!task) {
            u32 start = (self->id + self->steal_attempts + 1) % ts->worker_count;
            for (u32 i = 0; i < ts->worker_count - 1 && !task; i++) {
                u32 victim = (start + i) % ts->worker_count;
                if (victim == self->id) continue;
                for (int prio = 0; prio < TASK_PRIORITY_COUNT && !task; prio++) {
                    task = deque_steal(&ts->workers[victim].queues[prio]);
                }
            }
        }

        if (task) {
            self->steal_attempts = 0;
            self->backoff_ns = 100;
            execute_task(ts, self, task);
        } else {
            self->steal_attempts++;
            if (self->steal_attempts > ts->worker_count * 2) {
                platform_sleep_ns(self->backoff_ns);
                if (self->backoff_ns < 1000000) {
                    self->backoff_ns *= 2;
                } else {
                    self->backoff_ns = 1000000;
                }
            }
        }
    }

    atomic_store_explicit(&self->active, false, memory_order_release);
    return 0;
}
#else
static void *worker_entry(void *arg) {
    Worker *self = (Worker *)arg;
    TaskSystem *ts = g_task_system;
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
        }

        /* 4. Execute or backoff */
        if (task) {
            self->steal_attempts = 0;
            self->backoff_ns = 100;
            execute_task(ts, self, task);
        } else {
            self->steal_attempts++;
            if (self->steal_attempts > ts->worker_count * 2) {
                platform_sleep_ns(self->backoff_ns);
                if (self->backoff_ns < 1000000) {
                    self->backoff_ns *= 2;
                } else {
                    self->backoff_ns = 1000000; /* max 1ms */
                }
            }
        }
    }

    atomic_store_explicit(&self->active, false, memory_order_release);
    return NULL;
}
#endif

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
    u8 *mem = (u8 *)calloc(1, ts_bytes + pool_bytes + block_bytes + worker_bytes);
    if (!mem) return NULL;

    TaskSystem *ts = (TaskSystem *)mem;
    ts->worker_count = (u32)worker_count;
    ts->task_pool_capacity = cap;
    ts->task_pool    = (Task **)(mem + ts_bytes);
    ts->_task_block  = (Task *)(mem + ts_bytes + pool_bytes);
    ts->workers      = (Worker *)(mem + ts_bytes + pool_bytes + block_bytes);

    atomic_store_explicit(&ts->running, true, memory_order_relaxed);
    atomic_store_explicit(&ts->total_tasks_completed, 0, memory_order_relaxed);
    atomic_store_explicit(&ts->total_tasks_submitted, 0, memory_order_relaxed);
    atomic_store_explicit(&ts->next_handle, 0, memory_order_relaxed);
    atomic_store_explicit(&ts->submit_count, 0, memory_order_relaxed);

    /* Init submit mutex */
    platform_mutex_init(ts->submit_mutex_storage);

    /* Init task pool */
    atomic_store_explicit(&ts->task_pool_count, 0, memory_order_relaxed);
    platform_mutex_init(ts->pool_mutex_storage);

    /* Init workers */
    for (i32 i = 0; i < worker_count; i++) {
        Worker *w = &ts->workers[i];
        w->id = (u32)i;
        w->steal_attempts = 0;
        w->backoff_ns = 100;
        atomic_store_explicit(&w->active, false, memory_order_relaxed);
        for (int p = 0; p < TASK_PRIORITY_COUNT; p++) {
            deque_init(&w->queues[p], DEQUE_CAPACITY);
        }
    }

    g_task_system = ts;

    /* Start worker threads */
    for (i32 i = 0; i < worker_count; i++) {
        Worker *w = &ts->workers[i];
        bool thread_ok;
#ifdef ENGINE_PLATFORM_WINDOWS
        thread_ok = platform_thread_create(&w->thread_handle, worker_entry, w);
#else
        thread_ok = platform_thread_create_posix(w->thread_storage, worker_entry, w);
#endif
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
                LOG_FATAL("Task system: failed to create any worker threads");
            }
            break;
        }
    }

    LOG_INFO("Task system: %d workers (Chase-Lev work-stealing)", ts->worker_count);
    return ts;
}

void task_system_destroy(TaskSystem *ts) {
    /* Signal shutdown */
    atomic_store_explicit(&ts->running, false, memory_order_release);

    /* Join all workers */
    for (u32 i = 0; i < ts->worker_count; i++) {
        Worker *w = &ts->workers[i];
#ifdef ENGINE_PLATFORM_WINDOWS
        platform_thread_join(&w->thread_handle);
#else
        platform_thread_join_posix(w->thread_storage);
#endif
    }

    /* Cleanup deques */
    for (u32 i = 0; i < ts->worker_count; i++) {
        for (int p = 0; p < TASK_PRIORITY_COUNT; p++) {
            deque_destroy(&ts->workers[i].queues[p]);
        }
    }

    /* Release the pool's reference on every registered task. After the worker
     * join above no other thread touches these, so any task whose execution
     * reference already dropped is freed here; the rest are freed now. */
    u32 pool_count = atomic_load(&ts->task_pool_count);
    for (u32 i = 0; i < pool_count; i++) {
        Task *t = ts->task_pool[i];
        if (t) task_release(t);
    }

    platform_mutex_destroy(ts->submit_mutex_storage);
    platform_mutex_destroy(ts->pool_mutex_storage);

    /* Single free: task_pool, _task_block, and workers are within the same block */
    free(ts);

    g_task_system = NULL;
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
    Task *t = task_alloc(ts, fn, ctx, TASK_PRIORITY_NORMAL);
    submit_to_system(ts, t);
}

void task_submit_n(TaskSystem *ts, TaskFn fn, void **ctxs, i32 count) {
    for (i32 i = 0; i < count; i++) {
        Task *t = task_alloc(ts, fn, ctxs[i], TASK_PRIORITY_NORMAL);
        submit_to_system(ts, t);
    }
}

TaskHandle task_submit_ex(TaskSystem *ts, TaskFn fn, void *ctx, TaskPriority prio) {
    Task *t = task_alloc(ts, fn, ctx, prio);
    TaskHandle h = t->handle;
    submit_to_system(ts, t);
    return h;
}

TaskHandle task_submit_dep(TaskSystem *ts, TaskFn fn, void *ctx,
                           TaskHandle *deps, u32 dep_count) {
    Task *t = task_alloc(ts, fn, ctx, TASK_PRIORITY_NORMAL);
    TaskHandle h = t->handle;

    /* Set dependency count — task won't execute until all deps decrement it */
    atomic_store_explicit(&t->dep_count, dep_count, memory_order_relaxed);

    /* Link this task as parent of each dependency (O(1) lookup via pool index) */
    platform_mutex_lock(ts->pool_mutex_storage);
    u32 pool_count = atomic_load(&ts->task_pool_count);
    for (u32 d = 0; d < dep_count; d++) {
        u32 idx = (u32)(deps[d] & 0xFFFFFFFFu);
        if (idx >= pool_count) continue;
        Task *dep = ts->task_pool[idx];
        if (dep && dep->handle == deps[d]) {
            dep->parent = t;
            atomic_fetch_add_explicit(&t->ref_count, 1, memory_order_relaxed);
        }
    }
    platform_mutex_unlock(ts->pool_mutex_storage);

    /* If no actual dependencies found, submit immediately */
    if (atomic_load_explicit(&t->dep_count, memory_order_acquire) == 0) {
        submit_to_system(ts, t);
    }
    /* Otherwise, task will be submitted when last dep completes (in execute_task) */

    return h;
}

/* ============================================================
 * Public API: Wait
 * ============================================================ */

void task_wait(TaskSystem *ts) {
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

        platform_sleep_ns(100000); /* 100us */
    }
}

void task_wait_handle(TaskSystem *ts, TaskHandle handle) {
    /* O(1) lookup via pool index encoded in the lower 32 bits of the handle. */
    u32 idx = (u32)(handle & 0xFFFFFFFFu);
    u32 gen = (u32)(handle >> 32);

    u32 pool_count = atomic_load_explicit(&ts->task_pool_count, memory_order_acquire);
    if (idx >= pool_count) return;  /* handle not found — already done */

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
        platform_sleep_ns(100000);  /* 100us */
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
