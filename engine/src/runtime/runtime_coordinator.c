#include <runtime/runtime_coordinator.h>

#include <stdlib.h>
#include <string.h>

/* Single-owner lifecycle coordinator. No synchronization primitives: the
 * owner-thread rule in runtime_coordinator.h is the whole threading model.
 * The coordinator owns only itself and its copied subsystem table; subsystem
 * resources stay subsystem-owned (timeout retains them, FAILED keeps them
 * diagnosable).
 */

typedef enum RuntimeStopPhase {
    PHASE_NONE = 0,
    PHASE_STOP_ADMISSION,
    PHASE_STOP_PRODUCERS,
    PHASE_CLOSE_QUEUES,
    PHASE_DRAIN,
    PHASE_JOIN,
    PHASE_DESTROY,
    PHASE_DONE
} RuntimeStopPhase;

struct BreakRuntimeCoordinator {
    BreakRuntimeSubsystem *subsystems; /* tail of this single allocation */
    BreakRuntimeState state;
    BreakRuntimeError last_error;
    u32 subsystem_count;
    u32 capacity;
    u32 resume_phase; /* RuntimeStopPhase of the timed-out callback */
    u32 resume_index; /* subsystem index of the timed-out callback */
};

static usize runtime_align_up(usize value, usize alignment)
{
    /* _Alignof results are always powers of two. */
    return (value + (alignment - 1u)) & ~(alignment - 1u);
}

const char *break_runtime_error_name(BreakRuntimeError error)
{
    switch (error) {
    case BREAK_RUNTIME_OK: return "OK";
    case BREAK_RUNTIME_INVALID: return "INVALID";
    case BREAK_RUNTIME_CLOSED: return "CLOSED";
    case BREAK_RUNTIME_OVERLOAD: return "OVERLOAD";
    case BREAK_RUNTIME_OOM: return "OOM";
    case BREAK_RUNTIME_TIMEOUT: return "TIMEOUT";
    case BREAK_RUNTIME_STALE: return "STALE";
    case BREAK_RUNTIME_REJECTED: return "REJECTED";
    case BREAK_RUNTIME_FAILED: return "FAILED";
    default: return "UNKNOWN";
    }
}

const char *break_runtime_state_name(BreakRuntimeState state)
{
    switch (state) {
    case BREAK_RUNTIME_CREATED: return "CREATED";
    case BREAK_RUNTIME_STARTING: return "STARTING";
    case BREAK_RUNTIME_RUNNING: return "RUNNING";
    case BREAK_RUNTIME_QUIESCING: return "QUIESCING";
    case BREAK_RUNTIME_DRAINING: return "DRAINING";
    case BREAK_RUNTIME_STOPPING: return "STOPPING";
    case BREAK_RUNTIME_STOPPED: return "STOPPED";
    case BREAK_RUNTIME_STATE_FAILED: return "FAILED";
    default: return "UNKNOWN";
    }
}

BreakRuntimeError break_runtime_coordinator_create(
    const BreakRuntimeCoordinatorConfig *config,
    BreakRuntimeCoordinator **out_coordinator)
{
    BreakRuntimeCoordinator *coordinator;
    usize header_bytes;
    usize bytes;
    u32 max_subsystems = BREAK_RUNTIME_MAX_SUBSYSTEMS;

    if (!out_coordinator) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_coordinator = NULL;
    if (config && config->max_subsystems != 0u) {
        if (config->max_subsystems > BREAK_RUNTIME_MAX_SUBSYSTEMS) {
            return BREAK_RUNTIME_INVALID;
        }
        max_subsystems = config->max_subsystems;
    }

    /* Bounded capacity: count check against the hard bound happened above;
     * byte check happens before any allocation, so a bad budget fails closed
     * instead of overflowing the size computation. */
    header_bytes = runtime_align_up(sizeof(*coordinator),
                                    (usize)_Alignof(BreakRuntimeSubsystem));
    if ((usize)max_subsystems >
        (SIZE_MAX - header_bytes) / sizeof(BreakRuntimeSubsystem)) {
        return BREAK_RUNTIME_INVALID;
    }
    bytes = header_bytes + (usize)max_subsystems * sizeof(BreakRuntimeSubsystem);

    coordinator = calloc(1, bytes);
    if (!coordinator) {
        return BREAK_RUNTIME_OOM;
    }
    coordinator->subsystems =
        (BreakRuntimeSubsystem *)((char *)coordinator + header_bytes);
    coordinator->state = BREAK_RUNTIME_CREATED;
    coordinator->last_error = BREAK_RUNTIME_OK;
    coordinator->subsystem_count = 0u;
    coordinator->capacity = max_subsystems;
    coordinator->resume_phase = PHASE_NONE;
    coordinator->resume_index = 0u;
    *out_coordinator = coordinator;
    return BREAK_RUNTIME_OK;
}

void break_runtime_coordinator_destroy(BreakRuntimeCoordinator *coordinator)
{
    /* Only the coordinator object is released; subsystem resources are
     * subsystem-owned and are not touched here. */
    free(coordinator);
}

BreakRuntimeState break_runtime_coordinator_state(
    const BreakRuntimeCoordinator *coordinator)
{
    if (!coordinator) {
        return BREAK_RUNTIME_STATE_FAILED;
    }
    return coordinator->state;
}

BreakRuntimeError break_runtime_coordinator_last_error(
    const BreakRuntimeCoordinator *coordinator)
{
    if (!coordinator) {
        return BREAK_RUNTIME_INVALID;
    }
    return coordinator->last_error;
}

BreakRuntimeError break_runtime_coordinator_register_subsystem(
    BreakRuntimeCoordinator *coordinator,
    const BreakRuntimeSubsystem *subsystem)
{
    if (!coordinator || !subsystem) {
        return BREAK_RUNTIME_INVALID;
    }
    if (coordinator->state != BREAK_RUNTIME_CREATED) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (coordinator->subsystem_count >= coordinator->capacity) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    coordinator->subsystems[coordinator->subsystem_count] = *subsystem;
    coordinator->subsystem_count++;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_coordinator_start(
    BreakRuntimeCoordinator *coordinator)
{
    if (!coordinator) {
        return BREAK_RUNTIME_INVALID;
    }
    if (coordinator->state != BREAK_RUNTIME_CREATED) {
        return BREAK_RUNTIME_REJECTED;
    }
    /* Synchronous: STARTING is published for observers inside the transition
     * and settles to RUNNING before returning. */
    coordinator->state = BREAK_RUNTIME_STARTING;
    coordinator->state = BREAK_RUNTIME_RUNNING;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_coordinator_admit(
    BreakRuntimeCoordinator *coordinator)
{
    if (!coordinator) {
        return BREAK_RUNTIME_INVALID;
    }
    switch (coordinator->state) {
    case BREAK_RUNTIME_RUNNING:
        return BREAK_RUNTIME_OK;
    case BREAK_RUNTIME_CREATED:
    case BREAK_RUNTIME_STARTING:
        return BREAK_RUNTIME_REJECTED;
    case BREAK_RUNTIME_STATE_FAILED:
        return BREAK_RUNTIME_FAILED;
    default:
        /* QUIESCING/DRAINING/STOPPING/STOPPED: shutdown owns the runtime. */
        return BREAK_RUNTIME_CLOSED;
    }
}

static BreakRuntimeError runtime_run_phase(
    BreakRuntimeCoordinator *coordinator,
    u32 phase,
    u32 first_index)
{
    u32 i;
    for (i = first_index; i < coordinator->subsystem_count; i++) {
        BreakRuntimeSubsystem *sub = &coordinator->subsystems[i];
        BreakRuntimeError (*callback)(void *) = NULL;
        BreakRuntimeError err;
        switch (phase) {
        case PHASE_STOP_ADMISSION: callback = sub->stop_admission; break;
        case PHASE_STOP_PRODUCERS: callback = sub->stop_producers; break;
        case PHASE_CLOSE_QUEUES: callback = sub->close_queues; break;
        case PHASE_DRAIN: callback = sub->drain; break;
        case PHASE_JOIN: callback = sub->join; break;
        case PHASE_DESTROY: callback = sub->destroy; break;
        default: return BREAK_RUNTIME_INVALID;
        }
        if (!callback) {
            continue;
        }
        err = callback(sub->user_data);
        if (err == BREAK_RUNTIME_OK) {
            continue;
        }
        coordinator->last_error = err;
        if (err == BREAK_RUNTIME_TIMEOUT) {
            /* Retain live ownership: no state change, nothing freed; a later
             * stop() resumes at exactly this callback. */
            coordinator->resume_phase = phase;
            coordinator->resume_index = i;
            return BREAK_RUNTIME_TIMEOUT;
        }
        /* Unrecoverable subsystem error: sticky FAILED, verbatim result. */
        coordinator->state = BREAK_RUNTIME_STATE_FAILED;
        coordinator->resume_phase = PHASE_NONE;
        coordinator->resume_index = 0u;
        return err;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_coordinator_stop(
    BreakRuntimeCoordinator *coordinator)
{
    u32 phase;
    u32 index;

    if (!coordinator) {
        return BREAK_RUNTIME_INVALID;
    }
    switch (coordinator->state) {
    case BREAK_RUNTIME_STOPPED:
        return BREAK_RUNTIME_OK; /* idempotent */
    case BREAK_RUNTIME_STATE_FAILED:
        return BREAK_RUNTIME_FAILED; /* sticky: no callbacks re-run */
    case BREAK_RUNTIME_CREATED:
    case BREAK_RUNTIME_STARTING:
        return BREAK_RUNTIME_INVALID; /* no such transition */
    case BREAK_RUNTIME_RUNNING:
        phase = PHASE_STOP_ADMISSION;
        index = 0u;
        break;
    default:
        /* QUIESCING/DRAINING/STOPPING: legal retry of a timed-out stop,
         * resuming at the callback that returned TIMEOUT. */
        phase = coordinator->resume_phase;
        index = coordinator->resume_index;
        break;
    }

    for (; phase != PHASE_DONE; phase++) {
        BreakRuntimeError err;
        if (phase == PHASE_STOP_ADMISSION || phase == PHASE_STOP_PRODUCERS) {
            coordinator->state = BREAK_RUNTIME_QUIESCING;
        } else if (phase == PHASE_CLOSE_QUEUES || phase == PHASE_DRAIN) {
            coordinator->state = BREAK_RUNTIME_DRAINING;
        } else {
            coordinator->state = BREAK_RUNTIME_STOPPING;
        }
        err = runtime_run_phase(coordinator, phase, index);
        if (err != BREAK_RUNTIME_OK) {
            return err;
        }
        index = 0u;
    }

    coordinator->state = BREAK_RUNTIME_STOPPED;
    coordinator->last_error = BREAK_RUNTIME_OK;
    coordinator->resume_phase = PHASE_NONE;
    coordinator->resume_index = 0u;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_coordinator_fail(
    BreakRuntimeCoordinator *coordinator,
    BreakRuntimeError reason)
{
    if (!coordinator) {
        return BREAK_RUNTIME_INVALID;
    }
    if (reason == BREAK_RUNTIME_OK) {
        return BREAK_RUNTIME_INVALID;
    }
    if (coordinator->state == BREAK_RUNTIME_STATE_FAILED) {
        return BREAK_RUNTIME_OK; /* sticky: keep the first diagnostic reason */
    }
    if (coordinator->state == BREAK_RUNTIME_STOPPED) {
        return BREAK_RUNTIME_REJECTED;
    }
    coordinator->state = BREAK_RUNTIME_STATE_FAILED;
    coordinator->last_error = reason;
    coordinator->resume_phase = PHASE_NONE;
    coordinator->resume_index = 0u;
    return BREAK_RUNTIME_OK;
}
