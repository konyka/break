#pragma once

#include <runtime/runtime_coordinator.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakRuntimeWorldSession BreakRuntimeWorldSession;

typedef struct {
    u32 drain_budget; /* 0 = 32 */
    BreakRuntimeError (*stop_producers)(void *user_data);
    BreakRuntimeError (*join)(void *user_data);
    void *user_data;
} BreakRuntimeWorldSessionLifecycle;

/* Copies lifecycle and its hooks. user_data and the adapter's Bus, World
 * Session and publications remain borrowed. Successful registration transfers
 * adapter close/destroy to the coordinator; STOPPED releases only the adapter. */
BreakRuntimeError break_runtime_world_session_register_subsystem(
    BreakRuntimeWorldSession *adapter,
    BreakRuntimeCoordinator *coordinator,
    const BreakRuntimeWorldSessionLifecycle *lifecycle);

#ifdef BREAK_RUNTIME_TESTING
typedef void (*BreakRuntimeWorldSessionLifecycleTrace)(void *user_data,
                                                       const char *phase);
void break_runtime_world_session_lifecycle_set_trace_for_test(
    BreakRuntimeWorldSessionLifecycleTrace trace, void *user_data);
void break_runtime_world_session_lifecycle_set_destroy_failures_for_test(u32 failures);
#endif

#ifdef __cplusplus
}
#endif
