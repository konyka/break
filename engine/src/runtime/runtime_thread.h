#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

/* Runtime Core formal thread facade (design:
 * docs/design/runtime_thread_model.md §5-§7,
 * docs/design/runtime_overview.md §6-§7).
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * This wraps the header-only engine/src/core/platform_thread.h primitives
 * WITHOUT exposing OS thread handles (or any OS type) in the public API:
 * BreakRuntimeThread is opaque and the entry function is a plain
 * void (*)(void *), adapted internally to the native calling convention.
 *
 * OWNER THREAD (binding constraint): create/start/stop/state/destroy must be
 * called from the one owner thread; the object deliberately carries no
 * cross-owner arbitration. break_runtime_thread_stop_requested() is the one
 * exception: it is designed to be polled by the worker thread itself.
 *
 * Stop contract (completion condition + bounded wait + join ownership):
 *  - stop() publishes the stop request (the completion condition the worker
 *    observes via break_runtime_thread_stop_requested()), then waits up to
 *    `timeout_ms` for the worker to exit.
 *  - On worker exit the OWNER joins exactly once (join ownership) and the
 *    thread reaches BREAK_RUNTIME_THREAD_STOPPED. stop() never force-kills
 *    and never detaches.
 *  - If the worker has not exited within the budget, stop() returns
 *    BREAK_RUNTIME_TIMEOUT and retains live ownership: nothing is freed, the
 *    thread stays BREAK_RUNTIME_THREAD_STOP_REQUESTED, and a later stop() on
 *    the same object resumes the wait (a completed join is never re-run).
 *  - destroy() releases the object itself and is only legal from CREATED
 *    (never started or start-failed) or STOPPED; destroying a live
 *    (RUNNING/STOP_REQUESTED) thread is a contract violation, mirroring the
 *    queue destroy-with-concurrent-users rule.
 *
 * Error taxonomy:
 *   INVALID  — NULL argument, create without an entry function, stop() from
 *              CREATED (no such transition).
 *   REJECTED — start() from a non-CREATED state.
 *   TIMEOUT  — stop() budget expired with the worker still live; ownership
 *              retained, retry allowed.
 *   OOM      — allocation failure at create.
 *   FAILED   — the platform refused to spawn the thread (nothing is live;
 *              the object stays CREATED).
 */

typedef struct BreakRuntimeThread BreakRuntimeThread; /* opaque, owned by caller */

/* Diagnostic name capacity; the create-time name copy is bounded and always
 * NUL-terminated. */
#define BREAK_RUNTIME_THREAD_NAME_CAPACITY 32u

typedef enum BreakRuntimeThreadState {
    BREAK_RUNTIME_THREAD_CREATED = 0,
    BREAK_RUNTIME_THREAD_RUNNING,
    BREAK_RUNTIME_THREAD_STOP_REQUESTED,
    BREAK_RUNTIME_THREAD_STOPPED
} BreakRuntimeThreadState;

/* Formal thread entry: runs on the spawned thread. `arg` is the borrowed
 * context handed over at create; ownership of `arg` never transfers. */
typedef void (*BreakRuntimeThreadFn)(void *arg);

typedef struct BreakRuntimeThreadConfig {
    const char *name;          /* borrowed; copied into bounded storage; NULL ok */
    BreakRuntimeThreadFn fn;   /* required */
    void *arg;                 /* borrowed context handed to fn */
} BreakRuntimeThreadConfig;

/* On success *out_thread is newly owned; on failure it is set to NULL. */
BreakRuntimeError break_runtime_thread_create(
    const BreakRuntimeThreadConfig *config,
    BreakRuntimeThread **out_thread);

/* Releases the object. NULL is a no-op. Legal only from CREATED or STOPPED
 * (see header contract); a live thread must be stop()ed first. */
void break_runtime_thread_destroy(BreakRuntimeThread *thread);

/* CREATED -> RUNNING: spawns the worker. From any other state -> REJECTED.
 * On platform spawn failure -> FAILED and the object stays CREATED. */
BreakRuntimeError break_runtime_thread_start(
    BreakRuntimeThread *thread);

/* RUNNING/STOP_REQUESTED: publish the stop request, bounded-wait for worker
 * exit, join on success -> STOPPED, OK. Budget expired -> TIMEOUT (live
 * ownership retained; retry resumes). From STOPPED -> OK (idempotent).
 * From CREATED -> INVALID. */
BreakRuntimeError break_runtime_thread_stop(
    BreakRuntimeThread *thread, u32 timeout_ms);

/* The completion condition: true once stop() has published the stop request.
 * Intended to be polled by the worker thread; safe to call from any thread. */
bool break_runtime_thread_stop_requested(BreakRuntimeThread *thread);

/* Current state; BREAK_RUNTIME_THREAD_CREATED for NULL. */
BreakRuntimeThreadState break_runtime_thread_state(
    BreakRuntimeThread *thread);
