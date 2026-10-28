#include <runtime/runtime_reload.h>

#include <runtime/runtime_profiler.h>
#include <runtime/runtime_thread.h>

#include <core/platform_thread.h>
#include <runtime/runtime_test_hooks.h>

#include <asset/vfs.h>

#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(PLATFORM_THREAD_POSIX)
#include <time.h>
#endif

/* Formal hot-reload coordinator (header contract in runtime_reload.h).
 *
 * Concurrency layout:
 *  - One mutex + one work cond per facade. The facade mutex is taken before
 *    the profiler bridge mutex whenever both are held (the bridge is a leaf:
 *    it never calls back into the coordinator), so the order
 *    reload.mutex -> profiler.mutex is consistent and cannot deadlock.
 *  - Slot memory ownership: slots are a fixed array owned by the facade. A
 *    slot's staging bytes are owned by the worker until publish (ownership
 *    moves to the slot while VALIDATING), then by the owner thread while
 *    COMMITTING, and are freed on every terminal path.
 *  - Publication epochs: every transition that invalidates a worker claim or
 *    a queued commit command bumps the slot epoch; a late worker/commit
 *    result whose captured epoch no longer matches is dropped and counted
 *    (stats.stale_drops) — exactly one terminal state per request, always.
 *  - Handle generation: the u64 handle carries (generation << 32) |
 *    (slot_index + 1); the generation bumps when a terminal state is consumed
 *    by poll(), so a consumed handle can never name a re-armed slot (STALE).
 */

typedef enum ReloadFacadeState {
    RELOAD_FACADE_RUNNING = 0,
    RELOAD_FACADE_STOPPING,
    RELOAD_FACADE_STOPPED
} ReloadFacadeState;

typedef enum ReloadSlotState {
    RELOAD_SLOT_FREE = 0,
    RELOAD_SLOT_QUEUED,
    RELOAD_SLOT_LOADING,
    RELOAD_SLOT_VALIDATING,
    RELOAD_SLOT_COMMITTING, /* the owner thread is inside the commit hook */
    RELOAD_SLOT_TERMINAL
} ReloadSlotState;

typedef struct ReloadSlot {
    u64 generation;     /* handle generation; bumped at terminal consume */
    u64 epoch;          /* publication epoch; bumped at arm/cancel/finalize */
    ReloadSlotState state;
    u32 terminal_state; /* BreakRuntimeReloadState when TERMINAL */
    bool counted_active; /* counts toward stats.active until terminal */
    u64 deadline_ns;    /* 0 = no deadline */
    u8 *staged;         /* owned staging bytes (VALIDATING only) */
    usize staged_size;
    char path[BREAK_RUNTIME_RELOAD_MAX_PATH];
} ReloadSlot;

typedef struct ReloadCommitCommand {
    u32 slot_index;
    u64 epoch; /* publish-time epoch; staleness filter at claim */
} ReloadCommitCommand;

struct BreakRuntimeReload {
    PlatformMutex mutex;
    PlatformCond work_cond;
    VFS *vfs; /* borrowed; outlives the facade */
    BreakRuntimeReloadHooks hooks;
    BreakRuntimeProfiler *profiler; /* borrowed, may be NULL */
    PlatformThreadId owner;         /* pump_events/commit_owner thread */
    ReloadSlot *slots;              /* separate bounded allocation */
    u32 slot_capacity;
    u32 *pending; /* ring of slot indices; capacity == slot_capacity */
    u32 pending_head;
    u32 pending_count;
    ReloadCommitCommand *commits; /* bounded owner-commit queue */
    u32 commit_capacity;
    u32 commit_head;
    u32 commit_count;
    char (*events)[BREAK_RUNTIME_RELOAD_MAX_PATH]; /* bounded hint queue */
    u32 event_capacity;
    u32 event_head;
    u32 event_count;
    BreakRuntimeThread **workers; /* separate bounded allocation */
    u32 worker_count;
    u32 request_timeout_ms;
    ReloadFacadeState facade_state;
    bool workers_should_exit;
    u32 commits_in_flight; /* owner thread inside a commit hook right now */
    u64 next_epoch;
    /* stats (all under mutex) */
    u64 requested;
    u64 merged;
    u64 events_notified;
    u64 events_coalesced;
    u64 event_overloads;
    u64 events_deferred;
    u64 committed;
    u64 failed_keep_old;
    u64 cancelled;
    u64 timed_out;
    u64 oom;
    u64 request_overloads;
    u64 commit_overloads;
    u64 closed_rejects;
    u64 stale_rejects;
    u64 stale_drops;
    u32 active;
    u32 high_water;
};

/* ------------------------------------------------------------------ */
/* test-only hooks: deterministic worker gates                          */
/* ------------------------------------------------------------------ */

#if defined(BREAK_RUNTIME_TESTING)

_Atomic u32 g_break_runtime_test_reload_gate_claim = 0u;
_Atomic u32 g_break_runtime_test_reload_gate_load = 0u;
_Atomic u64 g_break_runtime_test_reload_popped = 0u;

void break_runtime_test_reload_set_gates(u32 gate_claim, u32 gate_load)
{
    /* Plain stores: the claim gate is a yield-spin outside the facade mutex
     * (see the worker loop), so no cond broadcast is needed on release. */
    atomic_store_explicit(&g_break_runtime_test_reload_gate_claim, gate_claim,
                          memory_order_release);
    atomic_store_explicit(&g_break_runtime_test_reload_gate_load, gate_load,
                          memory_order_release);
}

#endif /* BREAK_RUNTIME_TESTING */

/* ------------------------------------------------------------------ */
/* helpers                                                             */
/* ------------------------------------------------------------------ */

static u64 reload_now_ns(void)
{
#if defined(PLATFORM_THREAD_POSIX)
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) != TIME_UTC) {
        return 0u;
    }
    return (u64)ts.tv_sec * 1000000000ULL + (u64)ts.tv_nsec;
#else
    /* Millisecond resolution is sufficient for reload-scale deadlines. */
    return (u64)GetTickCount64() * 1000000ULL;
#endif
}

/* Lifecycle instant into the borrowed profiler bridge (may be NULL). The
 * bridge never blocks and drops on a full ring, so this is safe on worker
 * hot paths. Called with the facade mutex held (bridge mutex is a leaf). */
static void reload_note(BreakRuntimeReload *reload, const char *name)
{
    if (reload->profiler) {
        (void)break_runtime_profiler_record(reload->profiler, name);
    }
}

static const char *reload_state_note(u32 terminal_state)
{
    switch ((BreakRuntimeReloadState)terminal_state) {
    case BREAK_RUNTIME_RELOAD_COMMITTED:
        return "break.runtime.reload.committed";
    case BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD:
        return "break.runtime.reload.failed_keep_old";
    case BREAK_RUNTIME_RELOAD_CANCELLED:
        return "break.runtime.reload.cancelled";
    case BREAK_RUNTIME_RELOAD_TIMEOUT:
        return "break.runtime.reload.timeout";
    case BREAK_RUNTIME_RELOAD_OOM:
        return "break.runtime.reload.oom";
    default:
        return "break.runtime.reload.state";
    }
}

/* Handle codec: (generation << 32) | (slot_index + 1). 0 is never valid. */
static BreakRuntimeReloadRequest reload_make_handle(u32 slot_index,
                                                    u64 generation)
{
    return (generation << 32) | (u64)(slot_index + 1u);
}

/* Decodes and validates the handle against the slot table.
 * Returns the slot on success (facade mutex held), NULL + *out_error set
 * otherwise (facade mutex NOT held on the error path). */
static ReloadSlot *reload_resolve_handle(BreakRuntimeReload *reload,
                                         BreakRuntimeReloadRequest request,
                                         BreakRuntimeError *out_error)
{
    u32 slot_index;
    u64 generation;
    ReloadSlot *slot;

    if (request == 0u) {
        *out_error = BREAK_RUNTIME_STALE;
        return NULL;
    }
    slot_index = (u32)(request & 0xFFFFFFFFu);
    generation = request >> 32;
    if (slot_index == 0u) {
        *out_error = BREAK_RUNTIME_STALE;
        return NULL;
    }
    slot_index--;

    platform_mutex_lock(&reload->mutex);
    if (slot_index >= reload->slot_capacity) {
        reload->stale_rejects++;
        platform_mutex_unlock(&reload->mutex);
        *out_error = BREAK_RUNTIME_STALE;
        return NULL;
    }
    slot = &reload->slots[slot_index];
    if (slot->generation != generation || slot->state == RELOAD_SLOT_FREE) {
        reload->stale_rejects++;
        platform_mutex_unlock(&reload->mutex);
        *out_error = BREAK_RUNTIME_STALE;
        return NULL;
    }
    return slot;
}

/* Publishes a terminal state iff the slot is still the worker's claim
 * (LOADING at the captured epoch); otherwise the result is stale and dropped
 * (counted). Terminal publication is exactly-once. Every terminal
 * publication frees the request's ADMISSION slot (stats.active); the table
 * slot itself is released only when poll() consumes the terminal state. */
static void reload_finalize_terminal(BreakRuntimeReload *reload,
                                     u32 slot_index,
                                     u64 epoch,
                                     BreakRuntimeReloadState terminal_state)
{
    ReloadSlot *slot;

    platform_mutex_lock(&reload->mutex);
    slot = &reload->slots[slot_index];
    if (slot->state == RELOAD_SLOT_LOADING && slot->epoch == epoch) {
        slot->state = RELOAD_SLOT_TERMINAL;
        slot->terminal_state = (u32)terminal_state;
        slot->epoch = ++reload->next_epoch;
        if (slot->counted_active) {
            slot->counted_active = false;
            reload->active--;
        }
        switch (terminal_state) {
        case BREAK_RUNTIME_RELOAD_TIMEOUT:
            reload->timed_out++;
            break;
        case BREAK_RUNTIME_RELOAD_OOM:
            reload->oom++;
            break;
        case BREAK_RUNTIME_RELOAD_CANCELLED:
            reload->cancelled++;
            break;
        default:
            reload->failed_keep_old++;
            break;
        }
        reload_note(reload, reload_state_note((u32)terminal_state));
    } else {
        /* Cancelled/shutdown-drained while the worker was in flight. */
        reload->stale_drops++;
    }
    platform_mutex_unlock(&reload->mutex);
}

/* Publishes validated staging into the bounded owner-commit queue. Takes over
 * `staged` in every case (stored in the slot on success, freed otherwise). */
static void reload_publish_commit(BreakRuntimeReload *reload,
                                  u32 slot_index,
                                  u64 epoch,
                                  u8 *staged,
                                  usize staged_size)
{
    ReloadSlot *slot;

    platform_mutex_lock(&reload->mutex);
    slot = &reload->slots[slot_index];
    if (slot->state == RELOAD_SLOT_LOADING && slot->epoch == epoch) {
        if (reload->commit_count < reload->commit_capacity) {
            ReloadCommitCommand *command;
            slot->staged = staged;
            slot->staged_size = staged_size;
            staged = NULL; /* ownership moved to the slot */
            slot->state = RELOAD_SLOT_VALIDATING;
            slot->epoch = ++reload->next_epoch;
            command = &reload->commits[(reload->commit_head +
                                        reload->commit_count) %
                                       reload->commit_capacity];
            command->slot_index = slot_index;
            command->epoch = slot->epoch;
            reload->commit_count++;
            reload_note(reload, "break.runtime.reload.validating");
        } else {
            /* Bounded owner-commit queue full: never block the worker, never
             * overwrite a live command. The old version stays live. */
            reload->commit_overloads++;
            slot->state = RELOAD_SLOT_TERMINAL;
            slot->terminal_state = (u32)BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD;
            slot->epoch = ++reload->next_epoch;
            if (slot->counted_active) {
                slot->counted_active = false;
                reload->active--;
            }
            reload->failed_keep_old++;
            reload_note(reload, reload_state_note(
                                    (u32)BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD));
        }
    } else {
        reload->stale_drops++;
    }
    platform_mutex_unlock(&reload->mutex);
    free(staged);
}

/* ------------------------------------------------------------------ */
/* worker                                                              */
/* ------------------------------------------------------------------ */

static void reload_worker_main(void *arg)
{
    BreakRuntimeReload *reload = (BreakRuntimeReload *)arg;

    for (;;) {
        u32 slot_index = 0u;
        u64 epoch = 0u;
        u64 deadline_ns = 0u;
        bool claimed = false;
        char path[BREAK_RUNTIME_RELOAD_MAX_PATH];

        platform_mutex_lock(&reload->mutex);
#if defined(BREAK_RUNTIME_TESTING)
        /* Test gate: yield-spin BEFORE claiming (outside the mutex) so
         * cancel/stats/shutdown proceed while the worker is parked. The exit
         * flag bypasses the gate so shutdown stays bounded with the gate
         * armed. */
        if (atomic_load_explicit(&g_break_runtime_test_reload_gate_claim,
                                 memory_order_acquire) != 0u &&
            !reload->workers_should_exit) {
            platform_mutex_unlock(&reload->mutex);
            platform_thread_yield();
            continue;
        }
#endif
        while (reload->pending_count == 0u && !reload->workers_should_exit) {
            platform_cond_wait(&reload->work_cond, &reload->mutex);
        }
        if (reload->pending_count == 0u) {
            /* workers_should_exit with a drained ring: exit. */
            platform_mutex_unlock(&reload->mutex);
            break;
        }
        slot_index = reload->pending[reload->pending_head];
        reload->pending_head =
            (reload->pending_head + 1u) % reload->slot_capacity;
        reload->pending_count--;
        {
            ReloadSlot *slot = &reload->slots[slot_index];
            if (slot->state == RELOAD_SLOT_QUEUED) {
                slot->state = RELOAD_SLOT_LOADING;
                slot->epoch = ++reload->next_epoch;
                epoch = slot->epoch;
                deadline_ns = slot->deadline_ns;
                memcpy(path, slot->path, sizeof(path));
                claimed = true;
#if defined(BREAK_RUNTIME_TESTING)
                atomic_fetch_add_explicit(
                    &g_break_runtime_test_reload_popped, 1u,
                    memory_order_release);
#endif
            }
        }
        platform_mutex_unlock(&reload->mutex);

        if (!claimed) {
            /* Cancelled/shutdown-drained while queued: the terminal state was
             * already published by cancel()/shutdown(); reclaim only. */
            continue;
        }

#if defined(BREAK_RUNTIME_TESTING)
        /* Test gate: yield-spin AFTER the claim (LOADING), BEFORE the read.
         * Deliberately ignores the exit flag (unlike the claim gate) so a
         * parked worker keeps the facade live for the bounded-shutdown
         * TIMEOUT contract. */
        while (atomic_load_explicit(&g_break_runtime_test_reload_gate_load,
                                    memory_order_acquire) != 0u) {
            platform_thread_yield();
        }
#endif

        if (deadline_ns != 0u && reload_now_ns() > deadline_ns) {
            /* Processing deadline expired before the load: no VFS access. */
            reload_finalize_terminal(reload, slot_index, epoch,
                                     BREAK_RUNTIME_RELOAD_TIMEOUT);
            continue;
        }

        {
            usize size = 0u;
            u8 *data = vfs_read_all(reload->vfs, path, &size);
            if (!data || size == 0u) {
                /* Missing/unreadable/empty: old version stays live. */
                free(data);
                reload_finalize_terminal(reload, slot_index, epoch,
                                         BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD);
                continue;
            }
            if (size > (usize)BREAK_RUNTIME_RELOAD_MAX_STAGING_BYTES) {
                free(data);
                reload_finalize_terminal(reload, slot_index, epoch,
                                         BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD);
                continue;
            }
            /* Owned staging copy through the hook allocator (the byte budget
             * above bounds it; the VFS buffer is released immediately). */
            {
                u8 *staged = break_runtime_test_calloc(size);
                if (!staged) {
                    free(data);
                    reload_finalize_terminal(reload, slot_index, epoch,
                                             BREAK_RUNTIME_RELOAD_OOM);
                    continue;
                }
                memcpy(staged, data, size);
                free(data);
                if (reload->hooks.validate &&
                    reload->hooks.validate(path, staged, size,
                                           reload->hooks.user) !=
                        BREAK_RUNTIME_OK) {
                    /* Validation failure preserves the old data. */
                    free(staged);
                    reload_finalize_terminal(
                        reload, slot_index, epoch,
                        BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD);
                    continue;
                }
                reload_publish_commit(reload, slot_index, epoch, staged, size);
            }
        }
    }
}

/* ------------------------------------------------------------------ */
/* lifecycle                                                           */
/* ------------------------------------------------------------------ */

/* Frees every allocation of a fully-quiesced (STOPPED or never-started)
 * facade. Worker objects must already be joined/destroyed. */
static void reload_facade_free(BreakRuntimeReload *reload)
{
    if (!reload) {
        return;
    }
    free(reload->workers);
    free(reload->events);
    free(reload->commits);
    free(reload->pending);
    free(reload->slots);
    platform_cond_destroy(&reload->work_cond);
    platform_mutex_destroy(&reload->mutex);
    free(reload);
}

/* Stops every spawned worker with the bounded formal stop contract.
 * Returns OK when all are STOPPED, TIMEOUT if any is still live (ownership
 * retained). */
static BreakRuntimeError reload_stop_workers(BreakRuntimeReload *reload,
                                             u32 timeout_ms)
{
    u32 i;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    for (i = 0u; i < reload->worker_count; i++) {
        if (!reload->workers[i]) {
            continue;
        }
        if (break_runtime_thread_state(reload->workers[i]) ==
            BREAK_RUNTIME_THREAD_STOPPED) {
            continue;
        }
        if (break_runtime_thread_stop(reload->workers[i], timeout_ms) ==
            BREAK_RUNTIME_TIMEOUT) {
            result = BREAK_RUNTIME_TIMEOUT;
        }
    }
    return result;
}

static void reload_destroy_workers(BreakRuntimeReload *reload)
{
    u32 i;
    if (!reload->workers) {
        return;
    }
    for (i = 0u; i < reload->worker_count; i++) {
        break_runtime_thread_destroy(reload->workers[i]);
    }
}

BreakRuntimeError break_runtime_reload_create(
    const BreakRuntimeReloadConfig *config,
    BreakRuntimeReload **out_reload)
{
    BreakRuntimeReload *reload;
    u32 worker_count;
    u32 request_capacity;
    u32 event_capacity;
    u32 commit_capacity;
    u32 i;

    if (!out_reload) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_reload = NULL;
    if (!config || !config->vfs || !config->hooks.commit) {
        return BREAK_RUNTIME_INVALID;
    }
    worker_count = config->worker_count != 0u
                       ? config->worker_count
                       : BREAK_RUNTIME_RELOAD_DEFAULT_WORKERS;
    if (worker_count > BREAK_RUNTIME_RELOAD_MAX_WORKERS) {
        return BREAK_RUNTIME_INVALID;
    }
    request_capacity = config->request_capacity != 0u
                           ? config->request_capacity
                           : BREAK_RUNTIME_RELOAD_DEFAULT_REQUEST_CAPACITY;
    if (request_capacity > BREAK_RUNTIME_RELOAD_MAX_REQUEST_CAPACITY) {
        return BREAK_RUNTIME_INVALID;
    }
    event_capacity = config->event_capacity != 0u
                         ? config->event_capacity
                         : BREAK_RUNTIME_RELOAD_DEFAULT_EVENT_CAPACITY;
    if (event_capacity > BREAK_RUNTIME_RELOAD_MAX_EVENT_CAPACITY) {
        return BREAK_RUNTIME_INVALID;
    }
    commit_capacity = config->commit_capacity != 0u ? config->commit_capacity
                                                    : request_capacity;
    if (commit_capacity > BREAK_RUNTIME_RELOAD_MAX_COMMIT_CAPACITY) {
        return BREAK_RUNTIME_INVALID;
    }

    /* Count AND byte checks before every allocation. The count caps make
     * these unreachable in practice; they are part of the contract. The
     * divisors are bound to locals so the comparisons are not provably-false
     * to the compiler (the count ranges are capped above), matching the
     * checked-size style of the other runtime facades. */
    {
        const usize slot_size = sizeof(ReloadSlot);
        const usize pending_size = sizeof(u32);
        const usize command_size = sizeof(ReloadCommitCommand);
        const usize event_size = sizeof(*reload->events);
        const usize worker_size = sizeof(BreakRuntimeThread *);
        if ((usize)request_capacity > SIZE_MAX / slot_size ||
            (usize)request_capacity > SIZE_MAX / pending_size ||
            (usize)commit_capacity > SIZE_MAX / command_size ||
            (usize)event_capacity > SIZE_MAX / event_size ||
            (usize)worker_count > SIZE_MAX / worker_size) {
            return BREAK_RUNTIME_INVALID;
        }
    }

    reload = break_runtime_test_calloc(sizeof(*reload));
    if (!reload) {
        return BREAK_RUNTIME_OOM;
    }
    platform_mutex_init(&reload->mutex);
    platform_cond_init(&reload->work_cond);
    reload->vfs = config->vfs;
    reload->hooks = config->hooks;
    reload->profiler = config->profiler;
    reload->owner = platform_thread_current_id();
    reload->slot_capacity = request_capacity;
    reload->commit_capacity = commit_capacity;
    reload->event_capacity = event_capacity;
    reload->worker_count = worker_count;
    reload->request_timeout_ms = config->request_timeout_ms;

    reload->slots = break_runtime_test_calloc((usize)request_capacity *
                                              sizeof(ReloadSlot));
    if (!reload->slots) {
        reload_facade_free(reload);
        return BREAK_RUNTIME_OOM;
    }
    reload->pending =
        break_runtime_test_calloc((usize)request_capacity * sizeof(u32));
    if (!reload->pending) {
        reload_facade_free(reload);
        return BREAK_RUNTIME_OOM;
    }
    reload->commits = break_runtime_test_calloc((usize)commit_capacity *
                                                sizeof(ReloadCommitCommand));
    if (!reload->commits) {
        reload_facade_free(reload);
        return BREAK_RUNTIME_OOM;
    }
    reload->events =
        break_runtime_test_calloc((usize)event_capacity *
                                  sizeof(*reload->events));
    if (!reload->events) {
        reload_facade_free(reload);
        return BREAK_RUNTIME_OOM;
    }
    reload->workers = break_runtime_test_calloc((usize)worker_count *
                                                sizeof(BreakRuntimeThread *));
    if (!reload->workers) {
        reload_facade_free(reload);
        return BREAK_RUNTIME_OOM;
    }

    /* Spawn the formal worker threads. On any failure, stop (bounded) and
     * join the ones that started, then fail. */
    for (i = 0u; i < worker_count; i++) {
        BreakRuntimeThreadConfig thread_cfg;
        char name[BREAK_RUNTIME_THREAD_NAME_CAPACITY];
        snprintf(name, sizeof(name), "rt-reload-%u", i);
        memset(&thread_cfg, 0, sizeof(thread_cfg));
        thread_cfg.name = name;
        thread_cfg.fn = reload_worker_main;
        thread_cfg.arg = reload;
        if (break_runtime_thread_create(&thread_cfg, &reload->workers[i]) !=
                BREAK_RUNTIME_OK ||
            break_runtime_thread_start(reload->workers[i]) !=
                BREAK_RUNTIME_OK) {
            platform_mutex_lock(&reload->mutex);
            reload->workers_should_exit = true;
            platform_cond_broadcast(&reload->work_cond);
            platform_mutex_unlock(&reload->mutex);
            (void)reload_stop_workers(reload, 1000u);
            reload_destroy_workers(reload);
            reload_facade_free(reload);
            return BREAK_RUNTIME_FAILED;
        }
    }

    reload->facade_state = RELOAD_FACADE_RUNNING;
    *out_reload = reload;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_reload_shutdown(
    BreakRuntimeReload *reload,
    u32 timeout_ms)
{
    BreakRuntimeError stop_result;
    u32 i;

    if (!reload) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&reload->mutex);
    if (reload->facade_state == RELOAD_FACADE_STOPPED) {
        platform_mutex_unlock(&reload->mutex);
        return BREAK_RUNTIME_OK; /* idempotent */
    }
    /* 1. Close admission (request/notify/pump -> CLOSED). */
    reload->facade_state = RELOAD_FACADE_STOPPING;

    /* 2. Drain: every still-QUEUED/LOADING/VALIDATING request finalizes
     * CANCELLED (slot-owned staging is freed; in-flight worker results drop
     * on the stale epoch). COMMITTING requests are mid-commit on the owner
     * thread and finalize there. Terminal states stay pollable. */
    for (i = 0u; i < reload->slot_capacity; i++) {
        ReloadSlot *slot = &reload->slots[i];
        if (slot->state == RELOAD_SLOT_QUEUED ||
            slot->state == RELOAD_SLOT_LOADING ||
            slot->state == RELOAD_SLOT_VALIDATING) {
            free(slot->staged);
            slot->staged = NULL;
            slot->staged_size = 0u;
            slot->state = RELOAD_SLOT_TERMINAL;
            slot->terminal_state = (u32)BREAK_RUNTIME_RELOAD_CANCELLED;
            slot->epoch = ++reload->next_epoch;
            if (slot->counted_active) {
                slot->counted_active = false;
                reload->active--;
            }
            reload->cancelled++;
        }
    }
    reload->pending_head = 0u;
    reload->pending_count = 0u;
    reload->commit_head = 0u;
    reload->commit_count = 0u;
    reload->event_head = 0u;
    reload->event_count = 0u;
    reload_note(reload, "break.runtime.reload.shutdown");

    /* 3. Ask workers to exit and wake them. */
    reload->workers_should_exit = true;
    platform_cond_broadcast(&reload->work_cond);
    platform_mutex_unlock(&reload->mutex);

    /* 4. Bounded stop/join per worker. TIMEOUT retains live ownership: the
     * facade stays STOPPING, nothing is freed, and a later shutdown resumes
     * (already-stopped workers are skipped). */
    stop_result = reload_stop_workers(reload, timeout_ms);
    if (stop_result == BREAK_RUNTIME_TIMEOUT) {
        return BREAK_RUNTIME_TIMEOUT;
    }

    platform_mutex_lock(&reload->mutex);
    if (reload->commits_in_flight != 0u) {
        /* An owner-thread commit is in flight (commit_owner dropped the
         * mutex around the hook): completing STOPPED now would let a
         * cross-thread destroy() free the slots and mutex under the owner's
         * feet. Retain live ownership — the coordinator's
         * timeout-retains-ownership rule; retry after commit_owner returns. */
        platform_mutex_unlock(&reload->mutex);
        return BREAK_RUNTIME_TIMEOUT;
    }
    reload->facade_state = RELOAD_FACADE_STOPPED;
    platform_mutex_unlock(&reload->mutex);
    return BREAK_RUNTIME_OK;
}

void break_runtime_reload_destroy(BreakRuntimeReload *reload)
{
    if (!reload) {
        return;
    }
    if (reload->facade_state != RELOAD_FACADE_STOPPED) {
        /* Destroying a live facade is a contract violation (mirroring the
         * thread/queue destroy rules): test builds fail-stop; production
         * retains the facade rather than freeing memory the workers use. */
#if defined(BREAK_RUNTIME_TESTING)
        fprintf(stderr,
                "break_runtime_reload_destroy: facade not shut down "
                "(state %d)\n",
                (int)reload->facade_state);
        abort();
#else
        return;
#endif
    }
    reload_destroy_workers(reload);
    reload_facade_free(reload);
}

/* ------------------------------------------------------------------ */
/* request API                                                         */
/* ------------------------------------------------------------------ */

/* Shared arming path for request() and pump_events(). Requires the facade
 * mutex. Returns OK and arms a free slot, or OVERLOAD when a gate rejects.
 * The merge/defer scans are O(capacity) by design (bounded table). */
static BreakRuntimeError reload_arm_locked(BreakRuntimeReload *reload,
                                           const char *path,
                                           u32 *out_slot_index)
{
    u32 i;

    if (reload->active >= reload->slot_capacity) {
        /* Never wait for capacity: bounded non-blocking OVERLOAD. */
        reload->request_overloads++;
        return BREAK_RUNTIME_OVERLOAD;
    }
    if (reload->pending_count >= reload->slot_capacity) {
        /* The pending ring is physically full. This is NOT implied by the
         * active gate: a request cancelled while QUEUED frees its live slot
         * immediately but its ring slot only at claim/drain. Without this
         * gate the push index would overwrite a live entry (mirrors the IO
         * facade dual gate). */
        reload->request_overloads++;
        return BREAK_RUNTIME_OVERLOAD;
    }
    for (i = 0u; i < reload->slot_capacity; i++) {
        if (reload->slots[i].state == RELOAD_SLOT_FREE) {
            ReloadSlot *slot = &reload->slots[i];
            usize path_len = strlen(path);
            slot->state = RELOAD_SLOT_QUEUED;
            slot->epoch = ++reload->next_epoch;
            slot->counted_active = true;
            slot->staged = NULL;
            slot->staged_size = 0u;
            if (reload->request_timeout_ms != 0u) {
                slot->deadline_ns =
                    reload_now_ns() +
                    (u64)reload->request_timeout_ms * 1000000ULL;
            } else {
                slot->deadline_ns = 0u;
            }
            memcpy(slot->path, path, path_len + 1u);
            reload->pending[(reload->pending_head + reload->pending_count) %
                            reload->slot_capacity] = i;
            reload->pending_count++;
            reload->active++;
            reload->requested++;
            if (reload->active > reload->high_water) {
                reload->high_water = reload->active;
            }
            platform_cond_signal(&reload->work_cond);
            reload_note(reload, "break.runtime.reload.request");
            *out_slot_index = i;
            return BREAK_RUNTIME_OK;
        }
    }
    /* active < slot_capacity guarantees a FREE slot (active counts exactly
     * the non-FREE slots); unreachable defensive bound. */
    reload->request_overloads++;
    return BREAK_RUNTIME_OVERLOAD;
}

/* True when a live NON-TERMINAL request already covers `path` (merge target
 * for request(), deferral trigger for pump_events()). Requires the mutex. */
static bool reload_find_live_locked(BreakRuntimeReload *reload,
                                    const char *path,
                                    u32 *out_slot_index)
{
    u32 i;
    for (i = 0u; i < reload->slot_capacity; i++) {
        ReloadSlot *slot = &reload->slots[i];
        if ((slot->state == RELOAD_SLOT_QUEUED ||
             slot->state == RELOAD_SLOT_LOADING ||
             slot->state == RELOAD_SLOT_VALIDATING ||
             slot->state == RELOAD_SLOT_COMMITTING) &&
            strcmp(slot->path, path) == 0) {
            if (out_slot_index) {
                *out_slot_index = i;
            }
            return true;
        }
    }
    return false;
}

BreakRuntimeError break_runtime_reload_request(
    BreakRuntimeReload *reload,
    const char *path,
    BreakRuntimeReloadRequest *out_request)
{
    usize path_len;
    u32 slot_index = 0u;
    BreakRuntimeError armed;

    if (!reload || !out_request) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_request = 0u;
    if (!path || path[0] == '\0') {
        return BREAK_RUNTIME_INVALID;
    }
    path_len = strlen(path);
    if (path_len >= (usize)BREAK_RUNTIME_RELOAD_MAX_PATH) {
        return BREAK_RUNTIME_INVALID; /* rejected, never truncated */
    }

    platform_mutex_lock(&reload->mutex);
    if (reload->facade_state != RELOAD_FACADE_RUNNING) {
        reload->closed_rejects++;
        platform_mutex_unlock(&reload->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    /* Coalescing at request granularity: a live same-path request absorbs the
     * new one and returns the existing handle. */
    if (reload_find_live_locked(reload, path, &slot_index)) {
        ReloadSlot *slot = &reload->slots[slot_index];
        reload->merged++;
        *out_request = reload_make_handle(slot_index, slot->generation);
        platform_mutex_unlock(&reload->mutex);
        return BREAK_RUNTIME_OK;
    }
    armed = reload_arm_locked(reload, path, &slot_index);
    if (armed != BREAK_RUNTIME_OK) {
        platform_mutex_unlock(&reload->mutex);
        return armed;
    }
    *out_request =
        reload_make_handle(slot_index, reload->slots[slot_index].generation);
    platform_mutex_unlock(&reload->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_reload_poll(
    BreakRuntimeReload *reload,
    BreakRuntimeReloadRequest request,
    BreakRuntimeReloadState *out_state)
{
    ReloadSlot *slot;
    BreakRuntimeError error = BREAK_RUNTIME_OK;

    if (!reload || !out_state) {
        return BREAK_RUNTIME_INVALID;
    }
    slot = reload_resolve_handle(reload, request, &error);
    if (!slot) {
        return error;
    }
    /* Facade mutex held (resolver contract). */
    switch (slot->state) {
    case RELOAD_SLOT_QUEUED:
    case RELOAD_SLOT_LOADING:
        *out_state = BREAK_RUNTIME_RELOAD_LOADING; /* non-consuming */
        break;
    case RELOAD_SLOT_VALIDATING:
    case RELOAD_SLOT_COMMITTING:
        *out_state = BREAK_RUNTIME_RELOAD_VALIDATING; /* non-consuming */
        break;
    default:
        /* Terminal: deliver exactly once, release the table slot, and bump
         * the generation so this handle goes stale. The admission slot was
         * already freed at terminal publication (counted_active). */
        *out_state = (BreakRuntimeReloadState)slot->terminal_state;
        slot->state = RELOAD_SLOT_FREE;
        slot->generation++;
        free(slot->staged);
        slot->staged = NULL;
        slot->staged_size = 0u;
        if (slot->counted_active) {
            slot->counted_active = false;
            reload->active--;
        }
        break;
    }
    platform_mutex_unlock(&reload->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_reload_cancel(
    BreakRuntimeReload *reload,
    BreakRuntimeReloadRequest request)
{
    ReloadSlot *slot;
    BreakRuntimeError error = BREAK_RUNTIME_OK;
    BreakRuntimeError result = BREAK_RUNTIME_OK;

    if (!reload) {
        return BREAK_RUNTIME_INVALID;
    }
    slot = reload_resolve_handle(reload, request, &error);
    if (!slot) {
        return error;
    }
    /* Facade mutex held (resolver contract). No allocation anywhere on this
     * path: cancel can never fail halfway (no build-then-bump needed). */
    switch (slot->state) {
    case RELOAD_SLOT_QUEUED:
    case RELOAD_SLOT_LOADING:
    case RELOAD_SLOT_VALIDATING:
        /* The epoch bump makes a late worker result / queued commit command
         * stale; the worker reclaims its pending-ring entry, the owner pump
         * skips the dead command (counted as stale drops). Slot-owned staging
         * (VALIDATING) is freed here. The admission slot is freed at once
         * (the physical ring/table slots are reclaimed at claim/consume). */
        free(slot->staged);
        slot->staged = NULL;
        slot->staged_size = 0u;
        slot->state = RELOAD_SLOT_TERMINAL;
        slot->terminal_state = (u32)BREAK_RUNTIME_RELOAD_CANCELLED;
        slot->epoch = ++reload->next_epoch;
        if (slot->counted_active) {
            slot->counted_active = false;
            reload->active--;
        }
        reload->cancelled++;
        reload_note(reload,
                    reload_state_note((u32)BREAK_RUNTIME_RELOAD_CANCELLED));
        result = BREAK_RUNTIME_OK;
        break;
    case RELOAD_SLOT_COMMITTING:
        /* The owner thread is inside the commit hook: the swap may already
         * have happened; the request finalizes COMMITTED/FAILED_KEEP_OLD. */
        result = BREAK_RUNTIME_REJECTED;
        break;
    default:
        /* Terminal: idempotent for a pending CANCELLED, REJECTED for a real
         * result (mirrors the IO facade cancel contract). */
        result = slot->terminal_state == (u32)BREAK_RUNTIME_RELOAD_CANCELLED
                     ? BREAK_RUNTIME_OK
                     : BREAK_RUNTIME_REJECTED;
        break;
    }
    platform_mutex_unlock(&reload->mutex);
    return result;
}

/* ------------------------------------------------------------------ */
/* file events + owner pumps                                           */
/* ------------------------------------------------------------------ */

BreakRuntimeError break_runtime_reload_notify_file_event(
    BreakRuntimeReload *reload,
    const char *path)
{
    usize path_len;
    u32 i;

    if (!reload || !path || path[0] == '\0') {
        return BREAK_RUNTIME_INVALID;
    }
    path_len = strlen(path);
    if (path_len >= (usize)BREAK_RUNTIME_RELOAD_MAX_PATH) {
        return BREAK_RUNTIME_INVALID;
    }

    platform_mutex_lock(&reload->mutex);
    if (reload->facade_state != RELOAD_FACADE_RUNNING) {
        reload->closed_rejects++;
        platform_mutex_unlock(&reload->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    /* Coalescing: a pending hint for the same path absorbs the burst. Dedupe
     * runs before the fullness gate so a same-path hint still merges into a
     * full queue (the hint stream is lossy for NEW paths only). */
    for (i = 0u; i < reload->event_count; i++) {
        u32 index = (reload->event_head + i) % reload->event_capacity;
        if (strcmp(reload->events[index], path) == 0) {
            reload->events_coalesced++;
            platform_mutex_unlock(&reload->mutex);
            return BREAK_RUNTIME_OK;
        }
    }
    if (reload->event_count >= reload->event_capacity) {
        reload->event_overloads++;
        platform_mutex_unlock(&reload->mutex);
        return BREAK_RUNTIME_OVERLOAD;
    }
    memcpy(reload->events[(reload->event_head + reload->event_count) %
                          reload->event_capacity],
           path, path_len + 1u);
    reload->event_count++;
    reload->events_notified++;
    platform_mutex_unlock(&reload->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_reload_pump_events(
    BreakRuntimeReload *reload,
    u32 max_events,
    u32 *out_count)
{
    u32 started = 0u;

    if (!reload || !out_count) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_count = 0u;
    if (!platform_thread_id_equal(reload->owner,
                                  platform_thread_current_id())) {
        return BREAK_RUNTIME_REJECTED;
    }

    platform_mutex_lock(&reload->mutex);
    if (reload->facade_state != RELOAD_FACADE_RUNNING) {
        reload->closed_rejects++;
        platform_mutex_unlock(&reload->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    while (started < max_events && reload->event_count > 0u) {
        const char *path = reload->events[reload->event_head];
        u32 slot_index = 0u;
        /* Head-of-line deferral: a hint whose path has a live non-terminal
         * request stays queued (the burst becomes a follow-up reload once the
         * in-flight one terminates), and the pump stops there. */
        if (reload_find_live_locked(reload, path, NULL)) {
            reload->events_deferred++;
            break;
        }
        if (reload_arm_locked(reload, path, &slot_index) != BREAK_RUNTIME_OK) {
            break; /* admission full: the hint stays queued for a later pump */
        }
        /* The arm copied the path into the slot; only now drop the hint. */
        reload->event_head =
            (reload->event_head + 1u) % reload->event_capacity;
        reload->event_count--;
        started++;
    }
    platform_mutex_unlock(&reload->mutex);
    *out_count = started;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_reload_commit_owner(
    BreakRuntimeReload *reload,
    u32 max_commits,
    u32 *out_count)
{
    u32 done = 0u;

    if (!reload || !out_count) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_count = 0u;
    if (!platform_thread_id_equal(reload->owner,
                                  platform_thread_current_id())) {
        return BREAK_RUNTIME_REJECTED;
    }

    while (done < max_commits) {
        ReloadCommitCommand command;
        ReloadSlot *slot;
        u8 *staged;
        usize staged_size;
        u64 claimed_epoch;
        BreakRuntimeError commit_error;
        char path[BREAK_RUNTIME_RELOAD_MAX_PATH];

        platform_mutex_lock(&reload->mutex);
        if (reload->commit_count == 0u) {
            platform_mutex_unlock(&reload->mutex);
            break;
        }
        command = reload->commits[reload->commit_head];
        reload->commit_head =
            (reload->commit_head + 1u) % reload->commit_capacity;
        reload->commit_count--;
        slot = &reload->slots[command.slot_index];
        if (!(slot->state == RELOAD_SLOT_VALIDATING &&
              slot->epoch == command.epoch)) {
            /* Cancelled/shutdown-drained between publish and claim: skip the
             * dead command (the terminal state was already published). */
            reload->stale_drops++;
            platform_mutex_unlock(&reload->mutex);
            continue;
        }
        /* Claim: the owner takes over the staging bytes; the slot becomes
         * COMMITTING (cancel now rejects — the swap may be in flight). The
         * in-flight counter makes a cross-thread shutdown retain live
         * ownership (TIMEOUT) instead of freeing the facade under this
         * thread's feet while the mutex is dropped around the hook. */
        staged = slot->staged;
        staged_size = slot->staged_size;
        slot->staged = NULL;
        slot->staged_size = 0u;
        slot->state = RELOAD_SLOT_COMMITTING;
        slot->epoch = ++reload->next_epoch;
        claimed_epoch = slot->epoch;
        reload->commits_in_flight++;
        memcpy(path, slot->path, sizeof(path));
        platform_mutex_unlock(&reload->mutex);

        /* The hotreload seam: the consumer's swap runs ONLY here, on the
         * owner thread. A non-OK return preserves the old version. */
        commit_error = reload->hooks.commit(path, staged, staged_size,
                                            reload->hooks.user);

        platform_mutex_lock(&reload->mutex);
        reload->commits_in_flight--;
        if (slot->state == RELOAD_SLOT_COMMITTING &&
            slot->epoch == claimed_epoch) {
            slot->state = RELOAD_SLOT_TERMINAL;
            slot->terminal_state =
                commit_error == BREAK_RUNTIME_OK
                    ? (u32)BREAK_RUNTIME_RELOAD_COMMITTED
                    : (u32)BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD;
            slot->epoch = ++reload->next_epoch;
            if (slot->counted_active) {
                slot->counted_active = false;
                reload->active--;
            }
            if (commit_error == BREAK_RUNTIME_OK) {
                reload->committed++;
            } else {
                reload->failed_keep_old++;
            }
            reload_note(reload, reload_state_note(slot->terminal_state));
        } else {
            reload->stale_drops++; /* defensive: nothing mutates COMMITTING */
        }
        platform_mutex_unlock(&reload->mutex);
        free(staged);
        done++;
    }
    *out_count = done;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_reload_stats(
    BreakRuntimeReload *reload,
    BreakRuntimeReloadStats *out_stats)
{
    if (!reload || !out_stats) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&reload->mutex);
    out_stats->requested = reload->requested;
    out_stats->merged = reload->merged;
    out_stats->events_notified = reload->events_notified;
    out_stats->events_coalesced = reload->events_coalesced;
    out_stats->event_overloads = reload->event_overloads;
    out_stats->events_deferred = reload->events_deferred;
    out_stats->committed = reload->committed;
    out_stats->failed_keep_old = reload->failed_keep_old;
    out_stats->cancelled = reload->cancelled;
    out_stats->timed_out = reload->timed_out;
    out_stats->oom = reload->oom;
    out_stats->request_overloads = reload->request_overloads;
    out_stats->commit_overloads = reload->commit_overloads;
    out_stats->closed_rejects = reload->closed_rejects;
    out_stats->stale_rejects = reload->stale_rejects;
    out_stats->stale_drops = reload->stale_drops;
    out_stats->active = reload->active;
    out_stats->high_water = reload->high_water;
    platform_mutex_unlock(&reload->mutex);
    return BREAK_RUNTIME_OK;
}

const char *break_runtime_reload_state_name(BreakRuntimeReloadState state)
{
    switch (state) {
    case BREAK_RUNTIME_RELOAD_LOADING:
        return "LOADING";
    case BREAK_RUNTIME_RELOAD_VALIDATING:
        return "VALIDATING";
    case BREAK_RUNTIME_RELOAD_COMMITTED:
        return "COMMITTED";
    case BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD:
        return "FAILED_KEEP_OLD";
    case BREAK_RUNTIME_RELOAD_CANCELLED:
        return "CANCELLED";
    case BREAK_RUNTIME_RELOAD_TIMEOUT:
        return "TIMEOUT";
    case BREAK_RUNTIME_RELOAD_OOM:
        return "OOM";
    default:
        return "UNKNOWN";
    }
}
