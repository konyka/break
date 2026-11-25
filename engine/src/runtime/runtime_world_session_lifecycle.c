#include <runtime/runtime_world_session_lifecycle.h>

#include <runtime/runtime_world_session.h>

#include <stdlib.h>
#include <string.h>

#define RUNTIME_WORLD_SESSION_DEFAULT_DRAIN_BUDGET 32u

typedef struct {
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionLifecycle lifecycle;
} RuntimeWorldSessionLifecycleBinding;

#ifdef BREAK_RUNTIME_TESTING
static BreakRuntimeWorldSessionLifecycleTrace runtime_world_lifecycle_trace;
static void *runtime_world_lifecycle_trace_user_data;
static u32 runtime_world_lifecycle_destroy_failures;

void break_runtime_world_session_lifecycle_set_trace_for_test(
    BreakRuntimeWorldSessionLifecycleTrace trace, void *user_data)
{
    runtime_world_lifecycle_trace = trace;
    runtime_world_lifecycle_trace_user_data = user_data;
}

void break_runtime_world_session_lifecycle_set_destroy_failures_for_test(u32 failures)
{
    runtime_world_lifecycle_destroy_failures = failures;
}
#endif

static void runtime_world_lifecycle_record_phase(const char *phase)
{
#ifdef BREAK_RUNTIME_TESTING
    if (runtime_world_lifecycle_trace) {
        runtime_world_lifecycle_trace(runtime_world_lifecycle_trace_user_data, phase);
    }
#else
    (void)phase;
#endif
}

static BreakRuntimeError runtime_world_lifecycle_close(
    RuntimeWorldSessionLifecycleBinding *binding, const char *phase)
{
    runtime_world_lifecycle_record_phase(phase);
    break_runtime_world_session_close(binding->adapter);
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError runtime_world_lifecycle_stop_admission(void *user_data)
{
    return runtime_world_lifecycle_close(user_data, "stop_admission");
}

static BreakRuntimeError runtime_world_lifecycle_stop_producers(void *user_data)
{
    RuntimeWorldSessionLifecycleBinding *binding = user_data;
    runtime_world_lifecycle_record_phase("stop_producers");
    if (binding->lifecycle.stop_producers) {
        return binding->lifecycle.stop_producers(binding->lifecycle.user_data);
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError runtime_world_lifecycle_close_queues(void *user_data)
{
    return runtime_world_lifecycle_close(user_data, "close_queues");
}

static BreakRuntimeError runtime_world_lifecycle_drain(void *user_data)
{
    RuntimeWorldSessionLifecycleBinding *binding = user_data;
    BreakRuntimeError result;
    runtime_world_lifecycle_record_phase("drain");
    result = break_runtime_world_session_drain(
        binding->adapter, binding->lifecycle.drain_budget, NULL);
    if (break_runtime_world_session_pending(binding->adapter) != 0u ||
        result == BREAK_RUNTIME_OVERLOAD) {
        return BREAK_RUNTIME_TIMEOUT;
    }
    if (result == BREAK_RUNTIME_OK || result == BREAK_RUNTIME_STALE ||
        result == BREAK_RUNTIME_INVALID || result == BREAK_RUNTIME_REJECTED ||
        result == BREAK_RUNTIME_CLOSED) {
        return BREAK_RUNTIME_OK;
    }
    return result;
}

static BreakRuntimeError runtime_world_lifecycle_join(void *user_data)
{
    RuntimeWorldSessionLifecycleBinding *binding = user_data;
    runtime_world_lifecycle_record_phase("join");
    if (binding->lifecycle.join) {
        return binding->lifecycle.join(binding->lifecycle.user_data);
    }
    return BREAK_RUNTIME_OK;
}

static bool runtime_world_lifecycle_destroy_adapter(BreakRuntimeWorldSession *adapter)
{
#ifdef BREAK_RUNTIME_TESTING
    if (runtime_world_lifecycle_destroy_failures != 0u) {
        runtime_world_lifecycle_destroy_failures--;
        return false;
    }
#endif
    return break_runtime_world_session_destroy(adapter);
}

static BreakRuntimeError runtime_world_lifecycle_destroy(void *user_data)
{
    RuntimeWorldSessionLifecycleBinding *binding = user_data;
    runtime_world_lifecycle_record_phase("destroy");
    if (break_runtime_world_session_pending(binding->adapter) != 0u) {
        return BREAK_RUNTIME_TIMEOUT;
    }
    if (!runtime_world_lifecycle_destroy_adapter(binding->adapter)) {
        return BREAK_RUNTIME_TIMEOUT;
    }
    free(binding);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_world_session_register_subsystem(
    BreakRuntimeWorldSession *adapter,
    BreakRuntimeCoordinator *coordinator,
    const BreakRuntimeWorldSessionLifecycle *lifecycle)
{
    RuntimeWorldSessionLifecycleBinding *binding;
    BreakRuntimeSubsystem subsystem;
    BreakRuntimeError result;
    if (!adapter || !coordinator) return BREAK_RUNTIME_INVALID;
    if (break_runtime_world_session_is_closed(adapter) ||
        break_runtime_coordinator_state(coordinator) != BREAK_RUNTIME_CREATED) {
        return BREAK_RUNTIME_REJECTED;
    }
    binding = calloc(1u, sizeof(*binding));
    if (!binding) return BREAK_RUNTIME_OOM;
    binding->adapter = adapter;
    if (lifecycle) binding->lifecycle = *lifecycle;
    if (binding->lifecycle.drain_budget == 0u) {
        binding->lifecycle.drain_budget = RUNTIME_WORLD_SESSION_DEFAULT_DRAIN_BUDGET;
    }
    memset(&subsystem, 0, sizeof(subsystem));
    subsystem.name = "runtime_world_session";
    subsystem.user_data = binding;
    subsystem.stop_admission = runtime_world_lifecycle_stop_admission;
    subsystem.stop_producers = runtime_world_lifecycle_stop_producers;
    subsystem.close_queues = runtime_world_lifecycle_close_queues;
    subsystem.drain = runtime_world_lifecycle_drain;
    subsystem.join = runtime_world_lifecycle_join;
    subsystem.destroy = runtime_world_lifecycle_destroy;
    result = break_runtime_coordinator_register_subsystem(coordinator, &subsystem);
    if (result != BREAK_RUNTIME_OK) free(binding);
    return result;
}
