#include <runtime/runtime_io.h>

#include <runtime/runtime_thread.h>

#include <core/platform_thread.h>
#include <runtime/runtime_test_hooks.h>

#include <asset/vfs.h>

#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(PLATFORM_THREAD_POSIX)
#include <errno.h>
#include <time.h>
#endif

/* Formal IO/VFS facade: a module-level singleton whose IO worker threads are
 * formal BreakRuntimeThread objects reading through a BORROWED VFS. The
 * compatibility async loader (engine/src/asset/async_loader.c) is not used
 * and not modified; this is the formal completion bridge beside it.
 *
 * Concurrency layout:
 *  - g_io_lock (lazy-initialized, process-stable) guards publication of the
 *    singleton facade pointer. Lock order is always
 *    g_io_lock -> facade->mutex -> (test registry spinlock); never reversed.
 *  - All facade/request mutable state lives under facade->mutex. Two conds:
 *    work_cond wakes workers (submit / shutdown), completion_cond wakes
 *    completion waiters (publish / shutdown).
 *  - Request memory ownership is a refcount: 2 at submit (caller + facade).
 *    The facade reference is dropped by whoever removes the request from
 *    facade tracking (worker after processing, or the shutdown drain); the
 *    caller drops its reference with break_runtime_io_request_release(). The
 *    request is freed when the count reaches 0.
 *  - Request API calls anchor to the facade through request->facade. The
 *    facade object is freed only at a later re-init, and only when the
 *    previous lifecycle has no live requests (active == 0) — so a live
 *    request can never point at a freed facade.
 */

typedef enum IoFacadeState {
    IO_FACADE_RUNNING = 0,
    IO_FACADE_STOPPING,
    IO_FACADE_STOPPED
} IoFacadeState;

typedef enum IoRequestState {
    IO_REQ_QUEUED = 0,
    IO_REQ_READING,
    IO_REQ_DONE /* a completion has been published (any state) */
} IoRequestState;

typedef struct BreakRuntimeIoFacade {
    PlatformMutex mutex;
    PlatformCond work_cond;
    PlatformCond completion_cond;
    VFS *vfs; /* borrowed; mount table outlives the workers */
    BreakRuntimeIoRequest **ring; /* tail of this single allocation */
    u32 ring_capacity;
    u32 ring_head;
    u32 ring_count;
    BreakRuntimeThread **workers; /* separate bounded allocation */
    u32 worker_count;
    IoFacadeState state;
    bool shutdown_begun;
    bool workers_should_exit;
    u64 next_request_id;
    u32 active;
    /* stats (all under mutex) */
    u64 submitted;
    u64 completed;
    u64 failed;
    u64 cancelled;
    u64 timed_out;
    u64 overload_rejects;
    u64 closed_rejects;
    u64 stale_drops;
    u64 bytes_published;
    u32 high_water;
} BreakRuntimeIoFacade;

struct BreakRuntimeIoRequest {
    BreakRuntimeIoFacade *facade; /* borrowed; outlives the request */
    _Atomic u32 refs;
    u64 id;
    u64 generation;  /* under facade mutex; bumped by cancel */
    IoRequestState state; /* under facade mutex */
    u32 completion_state; /* BreakRuntimeIoCompletionState once DONE */
    BreakRuntimeOwnedMessage *completion; /* under facade mutex */
    u64 deadline_ns;
    char path[BREAK_RUNTIME_IO_MAX_PATH];
};

/* Completion wire layout: header followed by byte_size payload bytes. Both
 * sides copy through memcpy, so no packing/aliasing concerns. */
typedef struct RuntimeIoCompletionWire {
    u64 request_id;
    u64 generation;
    u32 state; /* BreakRuntimeIoCompletionState */
    u32 error; /* BreakRuntimeError */
    u64 byte_size;
} RuntimeIoCompletionWire;

static PlatformMutex g_io_lock;
static atomic_flag g_io_lock_init_flag = ATOMIC_FLAG_INIT;
static bool g_io_lock_ready = false;
static BreakRuntimeIoFacade *g_io = NULL; /* under g_io_lock */

static void io_global_lock(void)
{
    while (atomic_flag_test_and_set_explicit(&g_io_lock_init_flag,
                                             memory_order_acquire)) {
        platform_thread_yield();
    }
    if (!g_io_lock_ready) {
        platform_mutex_init(&g_io_lock);
        g_io_lock_ready = true;
    }
    atomic_flag_clear_explicit(&g_io_lock_init_flag, memory_order_release);
    platform_mutex_lock(&g_io_lock);
}

static void io_global_unlock(void)
{
    platform_mutex_unlock(&g_io_lock);
}

static u64 io_now_ns(void)
{
#if defined(PLATFORM_THREAD_POSIX)
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) != TIME_UTC) {
        return 0u;
    }
    return (u64)ts.tv_sec * 1000000000ULL + (u64)ts.tv_nsec;
#else
    /* GetTickCount64 has millisecond resolution; deadlines are IO-scale, so
     * this is sufficient for the Win32 lane. */
    return (u64)GetTickCount64() * 1000000ULL;
#endif
}

/* ------------------------------------------------------------------ */
/* test-only hooks: deterministic worker gates + request registry       */
/* ------------------------------------------------------------------ */

#if defined(BREAK_RUNTIME_TESTING)

_Atomic u32 g_break_runtime_test_io_gate_pop = 0u;
_Atomic u32 g_break_runtime_test_io_gate_read = 0u;
_Atomic u64 g_break_runtime_test_io_popped = 0u;

void break_runtime_test_io_set_gates(u32 gate_pop, u32 gate_read)
{
    atomic_store_explicit(&g_break_runtime_test_io_gate_pop, gate_pop,
                          memory_order_release);
    atomic_store_explicit(&g_break_runtime_test_io_gate_read, gate_read,
                          memory_order_release);
    /* Releasing the pop gate must wake parked workers. */
    io_global_lock();
    if (g_io) {
        platform_mutex_lock(&g_io->mutex);
        platform_cond_broadcast(&g_io->work_cond);
        platform_mutex_unlock(&g_io->mutex);
    }
    io_global_unlock();
}

/* Test-build live-request registry: same by-value exactly-once pattern as
 * the owned-message registry (runtime_message.c). release() looks the
 * pointer up without dereferencing it; an unregistered pointer (double
 * release or foreign) aborts, because release() has no return channel. */
#define RUNTIME_IO_REGISTRY_CAPACITY 2048u

static atomic_flag g_io_registry_lock = ATOMIC_FLAG_INIT;
static const void *g_io_registry[RUNTIME_IO_REGISTRY_CAPACITY];
static u32 g_io_registry_count;

static void io_registry_lock(void)
{
    while (atomic_flag_test_and_set_explicit(&g_io_registry_lock,
                                             memory_order_acquire)) {
        platform_thread_yield();
    }
}

static void io_registry_unlock(void)
{
    atomic_flag_clear_explicit(&g_io_registry_lock, memory_order_release);
}

static void io_registry_add(const void *request)
{
    bool added = false;
    io_registry_lock();
    if (g_io_registry_count < RUNTIME_IO_REGISTRY_CAPACITY) {
        g_io_registry[g_io_registry_count] = request;
        g_io_registry_count++;
        added = true;
    }
    io_registry_unlock();
    if (!added) {
        fprintf(stderr,
                "break_runtime_io_submit: test registry exhausted (%u live "
                "requests)\n",
                RUNTIME_IO_REGISTRY_CAPACITY);
        abort();
    }
}

static bool io_registry_remove(const void *request)
{
    u32 i;
    bool found = false;
    io_registry_lock();
    for (i = 0; i < g_io_registry_count; i++) {
        if (g_io_registry[i] == request) {
            g_io_registry[i] = g_io_registry[g_io_registry_count - 1u];
            g_io_registry_count--;
            found = true;
            break;
        }
    }
    io_registry_unlock();
    return found;
}

#endif /* BREAK_RUNTIME_TESTING */

/* ------------------------------------------------------------------ */
/* request helpers                                                     */
/* ------------------------------------------------------------------ */

static void io_request_free(BreakRuntimeIoRequest *request)
{
    break_runtime_message_release(request->completion);
    free(request);
}

/* Drops the facade's reference (worker after processing, or the shutdown
 * drain). Never touches the test registry: only the caller's release is
 * registered. */
static void io_request_drop_facade_ref(BreakRuntimeIoRequest *request)
{
    if (atomic_fetch_sub_explicit(&request->refs, 1u, memory_order_acq_rel) ==
        1u) {
        io_request_free(request);
    }
}

/* Builds an owned completion message: wire header + payload copy.
 * `data` may be NULL (byte_size must then be 0). */
static BreakRuntimeOwnedMessage *io_build_completion(
    const BreakRuntimeIoRequest *request,
    u64 generation,
    BreakRuntimeIoCompletionState state,
    BreakRuntimeError error,
    const void *data,
    usize byte_size)
{
    RuntimeIoCompletionWire wire;
    BreakRuntimeMessageView view;
    BreakRuntimeOwnedMessage *message = NULL;
    u8 *scratch = NULL;
    usize total;

    if (byte_size > 0u && !data) {
        return NULL;
    }
    if (byte_size > 0u) {
        if (byte_size > SIZE_MAX - sizeof(wire)) {
            return NULL;
        }
        total = sizeof(wire) + byte_size;
        scratch = malloc(total);
        if (!scratch) {
            return NULL;
        }
        memcpy(scratch + sizeof(wire), data, byte_size);
    } else {
        total = sizeof(wire);
    }

    memset(&wire, 0, sizeof(wire));
    wire.request_id = request->id;
    wire.generation = generation;
    wire.state = (u32)state;
    wire.error = (u32)error;
    wire.byte_size = (u64)byte_size;

    memset(&view, 0, sizeof(view));
    view.kind = BREAK_RUNTIME_IO_COMPLETION_KIND;
    view.version = BREAK_RUNTIME_IO_COMPLETION_VERSION;
    view.flags = 0u;
    view.sequence = request->id;
    if (scratch) {
        memcpy(scratch, &wire, sizeof(wire));
        view.data = scratch;
        view.size = total;
    } else {
        view.data = &wire;
        view.size = sizeof(wire);
    }
    if (break_runtime_message_copy(&view, &message) != BREAK_RUNTIME_OK) {
        message = NULL;
    }
    free(scratch);
    return message;
}

/* Worker-side finalize: publishes (state, error, data[0..byte_size)) iff the
 * request is still in READING at the captured generation and has no
 * completion yet; otherwise the result is STALE — the worker releases its
 * own bytes and never publishes (counted). Takes over `data` in all cases
 * (frees it after the payload copy). */
static void io_worker_finalize(
    BreakRuntimeIoFacade *facade,
    BreakRuntimeIoRequest *request,
    u64 generation_at_start,
    BreakRuntimeIoCompletionState state,
    BreakRuntimeError error,
    void *data,
    usize byte_size)
{
    BreakRuntimeOwnedMessage *message;
    bool published;

    message = io_build_completion(request, generation_at_start, state, error,
                                  data, byte_size);
    if (!message && state == BREAK_RUNTIME_IO_COMPLETED) {
        /* The payload copy failed (OOM): degrade to a FAILED completion. */
        state = BREAK_RUNTIME_IO_FAILED;
        error = BREAK_RUNTIME_OOM;
        byte_size = 0u;
        message = io_build_completion(request, generation_at_start, state,
                                      error, NULL, 0u);
    }

    platform_mutex_lock(&facade->mutex);
    if (request->state == IO_REQ_READING &&
        request->generation == generation_at_start &&
        !request->completion) {
        request->state = IO_REQ_DONE;
        request->completion_state = (u32)state;
        if (message) {
            request->completion = message;
            switch (state) {
            case BREAK_RUNTIME_IO_COMPLETED:
                facade->completed++;
                facade->bytes_published += (u64)byte_size;
                break;
            case BREAK_RUNTIME_IO_TIMED_OUT:
                facade->timed_out++;
                break;
            case BREAK_RUNTIME_IO_FAILED:
                facade->failed++;
                break;
            default:
                facade->cancelled++;
                break;
            }
            published = true;
        } else {
            /* Deep OOM: even the failure completion could not be built. The
             * request still reaches a terminal state (waiters wake on
             * shutdown or their deadlines); counted as failed + dropped. */
            facade->failed++;
            facade->stale_drops++;
            published = false;
        }
        platform_cond_broadcast(&facade->completion_cond);
    } else {
        /* Stale generation (cancelled while reading): release the result,
         * never publish. */
        facade->stale_drops++;
        published = false;
    }
    platform_mutex_unlock(&facade->mutex);

    if (!published) {
        break_runtime_message_release(message);
    }
    free(data);
}

/* ------------------------------------------------------------------ */
/* worker                                                              */
/* ------------------------------------------------------------------ */

static void io_worker_main(void *arg)
{
    BreakRuntimeIoFacade *facade = (BreakRuntimeIoFacade *)arg;

    for (;;) {
        BreakRuntimeIoRequest *request;
        u64 generation_at_start = 0u;
        bool claimed = false;

        platform_mutex_lock(&facade->mutex);
#if defined(BREAK_RUNTIME_TESTING)
        /* Test gate: park BEFORE claiming from the ring. */
        while (atomic_load_explicit(&g_break_runtime_test_io_gate_pop,
                                    memory_order_acquire) != 0u) {
            platform_cond_wait(&facade->work_cond, &facade->mutex);
        }
#endif
        while (facade->ring_count == 0u && !facade->workers_should_exit) {
            platform_cond_wait(&facade->work_cond, &facade->mutex);
        }
        if (facade->ring_count == 0u) {
            /* workers_should_exit with a drained ring: exit. */
            platform_mutex_unlock(&facade->mutex);
            break;
        }
        request = facade->ring[facade->ring_head];
        facade->ring[facade->ring_head] = NULL;
        facade->ring_head = (facade->ring_head + 1u) % facade->ring_capacity;
        facade->ring_count--;
        if (request->state == IO_REQ_QUEUED && !request->completion) {
            request->state = IO_REQ_READING;
            generation_at_start = request->generation;
            claimed = true;
#if defined(BREAK_RUNTIME_TESTING)
            atomic_fetch_add_explicit(&g_break_runtime_test_io_popped, 1u,
                                      memory_order_release);
#endif
        }
        platform_mutex_unlock(&facade->mutex);

        if (!claimed) {
            /* Cancelled (or shutdown-drained) while queued: the completion
             * was already published by cancel()/shutdown; only drop the
             * facade reference. */
            io_request_drop_facade_ref(request);
            continue;
        }

#if defined(BREAK_RUNTIME_TESTING)
        /* Test gate: park AFTER the claim (state READING), BEFORE the read.
         * Deliberately a yield-spin outside the facade mutex so cancel() and
         * shutdown() proceed while the worker is parked. */
        while (atomic_load_explicit(&g_break_runtime_test_io_gate_read,
                                    memory_order_acquire) != 0u) {
            platform_thread_yield();
        }
#endif

        if (request->deadline_ns != 0u &&
            io_now_ns() > request->deadline_ns) {
            /* Deadline expired before the read started: no VFS access. */
            io_worker_finalize(facade, request, generation_at_start,
                               BREAK_RUNTIME_IO_TIMED_OUT,
                               BREAK_RUNTIME_TIMEOUT, NULL, 0u);
        } else {
            usize size = 0u;
            u8 *data = vfs_read_all(facade->vfs, request->path, &size);
            if (!data || size == 0u) {
                free(data);
                io_worker_finalize(facade, request, generation_at_start,
                                   BREAK_RUNTIME_IO_FAILED,
                                   BREAK_RUNTIME_FAILED, NULL, 0u);
            } else if (size > (usize)BREAK_RUNTIME_IO_MAX_FILE_BYTES) {
                io_worker_finalize(facade, request, generation_at_start,
                                   BREAK_RUNTIME_IO_FAILED,
                                   BREAK_RUNTIME_OVERLOAD, data, 0u);
            } else {
                io_worker_finalize(facade, request, generation_at_start,
                                   BREAK_RUNTIME_IO_COMPLETED,
                                   BREAK_RUNTIME_OK, data, size);
            }
        }
        io_request_drop_facade_ref(request);
    }
}

/* ------------------------------------------------------------------ */
/* lifecycle                                                           */
/* ------------------------------------------------------------------ */

static void io_facade_destroy(BreakRuntimeIoFacade *facade)
{
    u32 i;
    if (!facade) {
        return;
    }
    /* Contract: workers joined (STOPPED) or never spawned; ring drained;
     * no live requests (active == 0). */
    if (facade->workers) {
        for (i = 0; i < facade->worker_count; i++) {
            break_runtime_thread_destroy(facade->workers[i]);
        }
        free(facade->workers);
    }
    platform_cond_destroy(&facade->completion_cond);
    platform_cond_destroy(&facade->work_cond);
    platform_mutex_destroy(&facade->mutex);
    free(facade);
}

/* Stops every worker with the bounded formal stop contract. Returns OK when
 * all are STOPPED, TIMEOUT if any is still live (ownership retained). */
static BreakRuntimeError io_facade_stop_workers(
    BreakRuntimeIoFacade *facade, u32 timeout_ms)
{
    u32 i;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    for (i = 0; i < facade->worker_count; i++) {
        BreakRuntimeThreadState state =
            break_runtime_thread_state(facade->workers[i]);
        if (state == BREAK_RUNTIME_THREAD_STOPPED) {
            continue;
        }
        if (break_runtime_thread_stop(facade->workers[i], timeout_ms) ==
            BREAK_RUNTIME_TIMEOUT) {
            result = BREAK_RUNTIME_TIMEOUT;
        }
    }
    return result;
}

BreakRuntimeError break_runtime_io_init(const BreakRuntimeIoConfig *config)
{
    BreakRuntimeIoFacade *facade;
    usize header_bytes;
    usize bytes;
    u32 worker_count;
    u32 request_capacity;
    u32 i;

    if (!config || !config->vfs) {
        return BREAK_RUNTIME_INVALID;
    }
    worker_count = config->worker_count != 0u ? config->worker_count
                                              : BREAK_RUNTIME_IO_DEFAULT_WORKERS;
    if (worker_count > BREAK_RUNTIME_IO_MAX_WORKERS) {
        return BREAK_RUNTIME_INVALID;
    }
    request_capacity = config->request_capacity != 0u
                           ? config->request_capacity
                           : BREAK_RUNTIME_IO_DEFAULT_REQUEST_CAPACITY;
    if (request_capacity > BREAK_RUNTIME_IO_MAX_REQUEST_CAPACITY) {
        return BREAK_RUNTIME_INVALID;
    }

    /* Count AND byte checks before allocation. The count caps above make
     * these unreachable in practice; they are part of the contract. */
    header_bytes = (sizeof(*facade) + _Alignof(BreakRuntimeIoRequest *) - 1u) &
                   ~((usize)_Alignof(BreakRuntimeIoRequest *) - 1u);
    if ((usize)request_capacity >
        (SIZE_MAX - header_bytes) / sizeof(BreakRuntimeIoRequest *)) {
        return BREAK_RUNTIME_INVALID;
    }
    bytes = header_bytes +
            (usize)request_capacity * sizeof(BreakRuntimeIoRequest *);

    facade = break_runtime_test_calloc(bytes);
    if (!facade) {
        return BREAK_RUNTIME_OOM;
    }
    platform_mutex_init(&facade->mutex);
    platform_cond_init(&facade->work_cond);
    platform_cond_init(&facade->completion_cond);
    facade->vfs = config->vfs;
    facade->ring = (BreakRuntimeIoRequest **)((char *)facade + header_bytes);
    facade->ring_capacity = request_capacity;
    facade->state = IO_FACADE_RUNNING;
    facade->workers = break_runtime_test_calloc(
        (usize)worker_count * sizeof(BreakRuntimeThread *));
    if (!facade->workers) {
        io_facade_destroy(facade);
        return BREAK_RUNTIME_OOM;
    }
    facade->worker_count = worker_count;

    /* Spawn the formal worker threads before publishing the facade. On any
     * failure, stop (bounded) and join the ones that started, then fail. */
    for (i = 0; i < worker_count; i++) {
        BreakRuntimeThreadConfig thread_cfg;
        char name[BREAK_RUNTIME_THREAD_NAME_CAPACITY];
        snprintf(name, sizeof(name), "rt-io-%u", i);
        memset(&thread_cfg, 0, sizeof(thread_cfg));
        thread_cfg.name = name;
        thread_cfg.fn = io_worker_main;
        thread_cfg.arg = facade;
        if (break_runtime_thread_create(&thread_cfg, &facade->workers[i]) !=
                BREAK_RUNTIME_OK ||
            break_runtime_thread_start(facade->workers[i]) !=
                BREAK_RUNTIME_OK) {
            platform_mutex_lock(&facade->mutex);
            facade->workers_should_exit = true;
            platform_cond_broadcast(&facade->work_cond);
            platform_mutex_unlock(&facade->mutex);
            (void)io_facade_stop_workers(facade, 1000u);
            io_facade_destroy(facade);
            return BREAK_RUNTIME_FAILED;
        }
    }

    io_global_lock();
    if (g_io) {
        bool reject;
        platform_mutex_lock(&g_io->mutex);
        /* REJECTED while a lifecycle is live (RUNNING/STOPPING) or while a
         * previous lifecycle still has live requests (its facade must stay
         * allocated for late polls/releases). */
        reject = g_io->state != IO_FACADE_STOPPED || g_io->active != 0u;
        platform_mutex_unlock(&g_io->mutex);
        if (reject) {
            io_global_unlock();
            /* Roll back: no consumer could have submitted yet. */
            platform_mutex_lock(&facade->mutex);
            facade->workers_should_exit = true;
            platform_cond_broadcast(&facade->work_cond);
            platform_mutex_unlock(&facade->mutex);
            (void)io_facade_stop_workers(facade, 1000u);
            io_facade_destroy(facade);
            return BREAK_RUNTIME_REJECTED;
        }
        /* The previous lifecycle is fully released: retire its facade (late
         * polls/releases are impossible because no request is live). */
        io_facade_destroy(g_io);
    }
    g_io = facade;
    io_global_unlock();
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_io_shutdown(u32 timeout_ms)
{
    BreakRuntimeIoFacade *facade;
    BreakRuntimeError stop_result;

    /* Keep the global lock until the facade mutex is held: a concurrent
     * re-init retires a STOPPED facade only after taking the facade mutex,
     * so it can never free the facade out from under this call (lock order:
     * g_io_lock -> facade mutex). */
    io_global_lock();
    facade = g_io;
    if (!facade) {
        io_global_unlock();
        return BREAK_RUNTIME_INVALID; /* never inited */
    }
    platform_mutex_lock(&facade->mutex);
    io_global_unlock();
    if (facade->state == IO_FACADE_STOPPED) {
        platform_mutex_unlock(&facade->mutex);
        return BREAK_RUNTIME_OK; /* idempotent */
    }
    /* 1. Close admission; interrupt every blocked completion wait. */
    facade->state = IO_FACADE_STOPPING;
    facade->shutdown_begun = true;
    platform_cond_broadcast(&facade->completion_cond);

    /* 2. Drain the pending ring: finalize every still-queued request as
     * CANCELLED (exactly-once publish; a request already finalized by
     * cancel() keeps its completion). In-flight reads are finalized by
     * their workers. Dropping the facade reference may free the request. */
    while (facade->ring_count > 0u) {
        BreakRuntimeIoRequest *request = facade->ring[facade->ring_head];
        facade->ring[facade->ring_head] = NULL;
        facade->ring_head = (facade->ring_head + 1u) % facade->ring_capacity;
        facade->ring_count--;
        if (request->state == IO_REQ_QUEUED && !request->completion) {
            BreakRuntimeOwnedMessage *message;
            request->generation++;
            message = io_build_completion(request, request->generation,
                                          BREAK_RUNTIME_IO_CANCELLED,
                                          BREAK_RUNTIME_OK, NULL, 0u);
            if (message) {
                request->state = IO_REQ_DONE;
                request->completion_state = (u32)BREAK_RUNTIME_IO_CANCELLED;
                request->completion = message;
                facade->cancelled++;
                platform_cond_broadcast(&facade->completion_cond);
            } else {
                /* Deep OOM building the cancellation completion: the request
                 * is still terminal-cancelled, waiters were already woken. */
                request->state = IO_REQ_DONE;
                request->completion_state = (u32)BREAK_RUNTIME_IO_CANCELLED;
                facade->cancelled++;
                facade->stale_drops++;
            }
        }
        io_request_drop_facade_ref(request);
    }

    /* 3. Ask workers to exit and wake them. */
    facade->workers_should_exit = true;
    platform_cond_broadcast(&facade->work_cond);
    platform_mutex_unlock(&facade->mutex);

    /* 4. Bounded stop/join per worker. TIMEOUT retains live ownership: the
     * facade stays STOPPING, nothing is freed, and a later shutdown resumes
     * (already-stopped workers are skipped). */
    stop_result = io_facade_stop_workers(facade, timeout_ms);
    if (stop_result == BREAK_RUNTIME_TIMEOUT) {
        return BREAK_RUNTIME_TIMEOUT;
    }

    platform_mutex_lock(&facade->mutex);
    facade->state = IO_FACADE_STOPPED;
    platform_mutex_unlock(&facade->mutex);
    return BREAK_RUNTIME_OK;
}

/* ------------------------------------------------------------------ */
/* request API                                                         */
/* ------------------------------------------------------------------ */

BreakRuntimeError break_runtime_io_submit(
    BreakRuntimeIoRequest **out_request,
    const char *path,
    u32 flags,
    u64 deadline_ns)
{
    BreakRuntimeIoFacade *facade;
    BreakRuntimeIoRequest *request;
    usize path_len;

    if (!out_request) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_request = NULL;
    if (!path || path[0] == '\0') {
        return BREAK_RUNTIME_INVALID;
    }
    if (flags != 0u) {
        /* No flags are defined yet: fail closed for forward compatibility. */
        return BREAK_RUNTIME_INVALID;
    }
    path_len = strlen(path);
    if (path_len >= (usize)BREAK_RUNTIME_IO_MAX_PATH) {
        return BREAK_RUNTIME_INVALID;
    }

    /* Hold the global lock across admission so a concurrent re-init cannot
     * retire the facade mid-submit (lock order: g_io_lock -> facade mutex). */
    io_global_lock();
    facade = g_io;
    if (!facade) {
        io_global_unlock();
        return BREAK_RUNTIME_REJECTED; /* admission before init */
    }
    platform_mutex_lock(&facade->mutex);
    if (facade->state != IO_FACADE_RUNNING) {
        facade->closed_rejects++;
        platform_mutex_unlock(&facade->mutex);
        io_global_unlock();
        return BREAK_RUNTIME_CLOSED;
    }
    if (facade->active >= facade->ring_capacity) {
        /* Never wait for capacity: bounded non-blocking OVERLOAD. */
        facade->overload_rejects++;
        platform_mutex_unlock(&facade->mutex);
        io_global_unlock();
        return BREAK_RUNTIME_OVERLOAD;
    }

    request = break_runtime_test_calloc(sizeof(*request));
    if (!request) {
        platform_mutex_unlock(&facade->mutex);
        io_global_unlock();
        return BREAK_RUNTIME_OOM;
    }
    atomic_store_explicit(&request->refs, 2u, memory_order_relaxed);
    request->facade = facade;
    request->id = ++facade->next_request_id;
    request->generation = 1u;
    request->state = IO_REQ_QUEUED;
    request->deadline_ns = deadline_ns;
    memcpy(request->path, path, path_len + 1u);

    /* ring_count <= active < ring_capacity: the push always has room. */
    facade->ring[(facade->ring_head + facade->ring_count) %
                 facade->ring_capacity] = request;
    facade->ring_count++;
    facade->active++;
    facade->submitted++;
    if (facade->active > facade->high_water) {
        facade->high_water = facade->active;
    }
    platform_cond_signal(&facade->work_cond);
    platform_mutex_unlock(&facade->mutex);
    io_global_unlock();

#if defined(BREAK_RUNTIME_TESTING)
    io_registry_add(request);
#endif
    *out_request = request;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_io_cancel(BreakRuntimeIoRequest *request)
{
    BreakRuntimeIoFacade *facade;
    BreakRuntimeOwnedMessage *message;

    if (!request) {
        return BREAK_RUNTIME_INVALID;
    }
    facade = request->facade;

    platform_mutex_lock(&facade->mutex);
    if (request->state == IO_REQ_DONE) {
        /* Already finalized. Idempotent for a cancellation completion;
         * REJECTED when a real result exists. */
        u32 completion_state = request->completion_state;
        platform_mutex_unlock(&facade->mutex);
        return completion_state == (u32)BREAK_RUNTIME_IO_CANCELLED
                   ? BREAK_RUNTIME_OK
                   : BREAK_RUNTIME_REJECTED;
    }
    /* QUEUED or READING: cancel bumps the generation so a worker finalizing
     * an in-flight read detects the stale generation and drops its bytes. */
    request->generation++;
    message = io_build_completion(request, request->generation,
                                  BREAK_RUNTIME_IO_CANCELLED,
                                  BREAK_RUNTIME_OK, NULL, 0u);
    if (!message) {
        platform_mutex_unlock(&facade->mutex);
        return BREAK_RUNTIME_OOM; /* not cancelled; retry allowed */
    }
    request->state = IO_REQ_DONE;
    request->completion_state = (u32)BREAK_RUNTIME_IO_CANCELLED;
    request->completion = message;
    facade->cancelled++;
    platform_cond_broadcast(&facade->completion_cond);
    platform_mutex_unlock(&facade->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_io_poll_completion(
    BreakRuntimeIoRequest *request,
    BreakRuntimeOwnedMessage **out_completion)
{
    BreakRuntimeIoFacade *facade;

    if (!request || !out_completion) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_completion = NULL;
    facade = request->facade;
    platform_mutex_lock(&facade->mutex);
    if (request->completion) {
        *out_completion = request->completion;
        request->completion = NULL;
    }
    platform_mutex_unlock(&facade->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_io_wait_completion(
    BreakRuntimeIoRequest *request,
    u32 timeout_ms,
    BreakRuntimeOwnedMessage **out_completion)
{
    BreakRuntimeIoFacade *facade;

    if (!request || !out_completion) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_completion = NULL;
    facade = request->facade;
    platform_mutex_lock(&facade->mutex);
    for (;;) {
        if (request->completion) {
            *out_completion = request->completion;
            request->completion = NULL;
            platform_mutex_unlock(&facade->mutex);
            return BREAK_RUNTIME_OK;
        }
        if (facade->shutdown_begun) {
            /* Shutdown interruption: wake with CLOSED even if a completion
             * might arrive later; the caller may still poll afterwards. */
            platform_mutex_unlock(&facade->mutex);
            return BREAK_RUNTIME_CLOSED;
        }
        /* Deadline-interruptible wait. */
#if defined(PLATFORM_THREAD_POSIX)
        {
            struct timespec deadline;
            int result = 0;
            if (timespec_get(&deadline, TIME_UTC) != TIME_UTC) {
                platform_mutex_unlock(&facade->mutex);
                return BREAK_RUNTIME_TIMEOUT;
            }
            deadline.tv_sec += (time_t)(timeout_ms / 1000u);
            deadline.tv_nsec += (long)(timeout_ms % 1000u) * 1000000L;
            if (deadline.tv_nsec >= 1000000000L) {
                deadline.tv_sec++;
                deadline.tv_nsec -= 1000000000L;
            }
            result = pthread_cond_timedwait(&facade->completion_cond,
                                            &facade->mutex, &deadline);
            if (result == ETIMEDOUT) {
                platform_mutex_unlock(&facade->mutex);
                return BREAK_RUNTIME_TIMEOUT; /* completion not consumed */
            }
            /* Other wakeups (publish/shutdown/spurious) re-check the loop. */
        }
#else
        {
            ULONGLONG deadline = GetTickCount64() + (ULONGLONG)timeout_ms;
            ULONGLONG now = GetTickCount64();
            DWORD remaining = now >= deadline ? 0u : (DWORD)(deadline - now);
            if (!SleepConditionVariableCS(&facade->completion_cond,
                                          &facade->mutex, remaining)) {
                platform_mutex_unlock(&facade->mutex);
                return BREAK_RUNTIME_TIMEOUT;
            }
        }
#endif
    }
}

void break_runtime_io_request_release(BreakRuntimeIoRequest *request)
{
    BreakRuntimeIoFacade *facade;
    if (!request) {
        return;
    }
#if defined(BREAK_RUNTIME_TESTING)
    /* By value, before any dereference (mirrors the message registry). */
    if (!io_registry_remove(request)) {
        fprintf(stderr,
                "break_runtime_io_request_release: double release or foreign "
                "request %p\n",
                (void *)request);
        abort();
    }
#endif
    facade = request->facade;
    platform_mutex_lock(&facade->mutex);
    facade->active--;
    platform_mutex_unlock(&facade->mutex);
    if (atomic_fetch_sub_explicit(&request->refs, 1u, memory_order_acq_rel) ==
        1u) {
        io_request_free(request);
    }
}

/* ------------------------------------------------------------------ */
/* completion parsing + stats                                          */
/* ------------------------------------------------------------------ */

BreakRuntimeError break_runtime_io_completion_view(
    const BreakRuntimeOwnedMessage *completion_message,
    BreakRuntimeIoCompletion *out_completion)
{
    BreakRuntimeMessageView view;
    RuntimeIoCompletionWire wire;

    if (!completion_message || !out_completion) {
        return BREAK_RUNTIME_INVALID;
    }
    if (break_runtime_message_view(completion_message, &view) !=
        BREAK_RUNTIME_OK) {
        return BREAK_RUNTIME_INVALID;
    }
    if (view.kind != BREAK_RUNTIME_IO_COMPLETION_KIND ||
        view.version != BREAK_RUNTIME_IO_COMPLETION_VERSION) {
        return BREAK_RUNTIME_INVALID;
    }
    if (view.size < sizeof(wire)) {
        return BREAK_RUNTIME_INVALID;
    }
    memcpy(&wire, view.data, sizeof(wire));
    if (wire.byte_size != (u64)(view.size - sizeof(wire))) {
        return BREAK_RUNTIME_INVALID;
    }
    if (wire.state > (u32)BREAK_RUNTIME_IO_TIMED_OUT) {
        return BREAK_RUNTIME_INVALID;
    }
    out_completion->request_id = wire.request_id;
    out_completion->generation = wire.generation;
    out_completion->state = wire.state;
    out_completion->error = wire.error;
    out_completion->byte_size = wire.byte_size;
    out_completion->bytes = wire.byte_size > 0u
                                ? (const u8 *)view.data + sizeof(wire)
                                : NULL;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_io_stats(BreakRuntimeIoStats *out_stats)
{
    BreakRuntimeIoFacade *facade;

    if (!out_stats) {
        return BREAK_RUNTIME_INVALID;
    }
    /* Same publish-read discipline as shutdown(): hold the global lock until
     * the facade mutex is held, so a concurrent re-init cannot retire the
     * facade in between. */
    io_global_lock();
    facade = g_io;
    if (!facade) {
        io_global_unlock();
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&facade->mutex);
    io_global_unlock();
    out_stats->submitted = facade->submitted;
    out_stats->completed = facade->completed;
    out_stats->failed = facade->failed;
    out_stats->cancelled = facade->cancelled;
    out_stats->timed_out = facade->timed_out;
    out_stats->overload_rejects = facade->overload_rejects;
    out_stats->closed_rejects = facade->closed_rejects;
    out_stats->stale_drops = facade->stale_drops;
    out_stats->bytes_published = facade->bytes_published;
    out_stats->active = facade->active;
    out_stats->high_water = facade->high_water;
    platform_mutex_unlock(&facade->mutex);
    return BREAK_RUNTIME_OK;
}
