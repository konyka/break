#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

/* BreakRuntimeCoordinator — the single lifecycle coordinator.
 *
 * OWNER THREAD (binding constraint): every function in this header must be
 * called from the one owner thread (Game/Main). The coordinator deliberately
 * contains no mutex; arbitrary multi-owner mutation is a contract violation,
 * not a supported mode. Subsystem callbacks also run on the owner thread.
 *
 * Global lifecycle (design: docs/design/runtime_overview.md §7):
 *
 *   CREATED -> STARTING -> RUNNING -> QUIESCING -> DRAINING -> STOPPING -> STOPPED
 *   any non-terminal state -> FAILED   (sticky, diagnostic)
 *
 * Delivered transition surface:
 *   create   -> CREATED
 *   start    CREATED -> STARTING -> RUNNING (synchronous; STARTING is only
 *            observable from inside callbacks/state queries during start)
 *   stop     RUNNING -> QUIESCING -> DRAINING -> STOPPING -> STOPPED
 *   stop     retried from QUIESCING/DRAINING/STOPPING resumes a timed-out
 *            stop at the exact callback that returned TIMEOUT
 *   fail     CREATED/STARTING/RUNNING/QUIESCING/DRAINING/STOPPING -> FAILED
 *
 * Error taxonomy used by this header:
 *   BREAK_RUNTIME_INVALID  — malformed call (NULL argument) or a lifecycle
 *                            transition that does not exist in the graph
 *                            (e.g. stop from CREATED).
 *   BREAK_RUNTIME_REJECTED — a meaningful request rejected by policy in the
 *                            current state (start when already RUNNING,
 *                            registration after start, fail from STOPPED,
 *                            admission before the runtime is RUNNING).
 *   BREAK_RUNTIME_CLOSED   — admission after shutdown has begun or finished
 *                            (QUIESCING/DRAINING/STOPPING/STOPPED).
 *   BREAK_RUNTIME_FAILED   — admission or stop attempted on a FAILED
 *                            coordinator (sticky).
 *   BREAK_RUNTIME_TIMEOUT  — a subsystem callback kept live ownership past
 *                            its bounded budget; nothing is freed and the
 *                            same coordinator may retry stop.
 *   BREAK_RUNTIME_OVERLOAD — the bounded subsystem table is full.
 *   BREAK_RUNTIME_OOM      — allocation failure at create.
 */

typedef struct BreakRuntimeCoordinator BreakRuntimeCoordinator; /* opaque, owned by the caller */

/* Hard upper bound for the subsystem table. The table is a fixed capacity
 * budget: registration beyond it fails with BREAK_RUNTIME_OVERLOAD, never
 * grows implicitly. */
#define BREAK_RUNTIME_MAX_SUBSYSTEMS 16u

typedef struct BreakRuntimeCoordinatorConfig {
    /* 0 selects the default (BREAK_RUNTIME_MAX_SUBSYSTEMS); values above
     * BREAK_RUNTIME_MAX_SUBSYSTEMS are rejected with BREAK_RUNTIME_INVALID.
     * The allocation applies count and byte checks before allocating. */
    u32 max_subsystems;
} BreakRuntimeCoordinatorConfig;

/* Shutdown callback set for one subsystem. The descriptor is COPIED at
 * registration; `name` and `user_data` are borrowed and must outlive the
 * registration. Any callback may be NULL (no-op for that phase).
 *
 * Callback contract:
 *  - Return BREAK_RUNTIME_OK to let the phase advance.
 *  - Return BREAK_RUNTIME_TIMEOUT to keep live ownership: the coordinator
 *    returns TIMEOUT to the owner, stays in the current stop state, frees
 *    nothing, and a later stop() resumes at the exact callback that timed
 *    out (completed callbacks are never re-run).
 *  - Any other non-OK return publishes sticky FAILED and propagates to the
 *    owner verbatim; the remaining callbacks of the stop sequence do not run.
 *  - Callbacks run on the owner thread. The only coordinator call legal from
 *    inside a callback is break_runtime_coordinator_state(); callbacks must
 *    not drive start/stop/fail/register recursively.
 *
 * Phase order for one full stop (registration order within each phase):
 *   QUIESCING: stop_admission, stop_producers   (stop new admission, then producers)
 *   DRAINING:  close_queues, drain              (bounded completions/close watermarks)
 *   STOPPING:  join, destroy                    (join workers, then destroy)
 */
typedef struct BreakRuntimeSubsystem {
    const char *name;     /* borrowed diagnostic label */
    void *user_data;      /* borrowed context handed back to every callback */
    BreakRuntimeError (*stop_admission)(void *user_data);
    BreakRuntimeError (*stop_producers)(void *user_data);
    BreakRuntimeError (*close_queues)(void *user_data);
    BreakRuntimeError (*drain)(void *user_data);
    BreakRuntimeError (*join)(void *user_data);
    BreakRuntimeError (*destroy)(void *user_data);
} BreakRuntimeSubsystem;

/* `config` may be NULL (defaults). On success *out_coordinator is a newly
 * owned handle; on failure it is left NULL/unchanged. */
BreakRuntimeError break_runtime_coordinator_create(
    const BreakRuntimeCoordinatorConfig *config,
    BreakRuntimeCoordinator **out_coordinator);

/* Releases the coordinator object itself, in ANY state. This never stops or
 * destroys subsystems: subsystem resources are owned by the subsystems, so
 * the owner must stop() to STOPPED first if it wants the shutdown sequence
 * to run. Destroying a live (non-STOPPED) coordinator only abandons
 * coordination. NULL is a no-op. */
void break_runtime_coordinator_destroy(BreakRuntimeCoordinator *coordinator);

BreakRuntimeState break_runtime_coordinator_state(
    const BreakRuntimeCoordinator *coordinator);

/* Last non-OK result (start/stop/fail/callback), BREAK_RUNTIME_OK when none.
 * FAILED keeps its first diagnostic reason queryable here. */
BreakRuntimeError break_runtime_coordinator_last_error(
    const BreakRuntimeCoordinator *coordinator);

/* Copies `subsystem` into the bounded table. Only legal in CREATED;
 * otherwise REJECTED. Table full -> OVERLOAD. */
BreakRuntimeError break_runtime_coordinator_register_subsystem(
    BreakRuntimeCoordinator *coordinator,
    const BreakRuntimeSubsystem *subsystem);

/* CREATED -> STARTING -> RUNNING. From any other state -> REJECTED
 * (FAILED included: sticky). */
BreakRuntimeError break_runtime_coordinator_start(
    BreakRuntimeCoordinator *coordinator);

/* Admission gate for new work. RUNNING -> OK; CREATED/STARTING -> REJECTED;
 * QUIESCING/DRAINING/STOPPING/STOPPED -> CLOSED; FAILED -> FAILED. */
BreakRuntimeError break_runtime_coordinator_admit(
    BreakRuntimeCoordinator *coordinator);

/* RUNNING -> drives the full phase sequence -> STOPPED, returns OK.
 * From QUIESCING/DRAINING/STOPPING resumes a timed-out stop (legal retry).
 * From STOPPED -> OK (idempotent no-op).
 * From CREATED/STARTING -> INVALID (no such transition).
 * From FAILED -> FAILED (sticky; no callbacks run). */
BreakRuntimeError break_runtime_coordinator_stop(
    BreakRuntimeCoordinator *coordinator);

/* Publishes sticky FAILED with a diagnostic reason (`reason` must be
 * non-OK, else INVALID). Legal from CREATED/STARTING/RUNNING/QUIESCING/
 * DRAINING/STOPPING. From STOPPED -> REJECTED. From FAILED -> OK,
 * idempotent, first reason retained. */
BreakRuntimeError break_runtime_coordinator_fail(
    BreakRuntimeCoordinator *coordinator,
    BreakRuntimeError reason);
