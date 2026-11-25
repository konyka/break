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
    void (*on_destroy)(void *user_data);
} BreakRuntimeWorldSessionLifecycle;

/* Copies lifecycle and its hooks. user_data and the adapter's Bus, World
 * Session and publications remain borrowed. Registration requires an open,
 * unbound adapter and a CREATED coordinator. A second registration of the same
 * adapter is REJECTED, even through another coordinator, and changes neither
 * owner. Allocation or coordinator registration failure rolls back the bind.
 *
 * Success transfers adapter close/destroy to the coordinator. The caller must
 * quiesce external producers through stop_producers/join and must not directly
 * close or destroy the registered adapter. Direct destroy returns false before
 * close/unsubscribe while bound. STOPPED releases only the adapter, then calls
 * on_destroy once after successful release. TIMEOUT, FAILED and abandon do not
 * call on_destroy; a NULL hook preserves the original behavior. */
BreakRuntimeError break_runtime_world_session_register_subsystem(
    BreakRuntimeWorldSession *adapter,
    BreakRuntimeCoordinator *coordinator,
    const BreakRuntimeWorldSessionLifecycle *lifecycle);

/* CREATED or FAILED: unregister this exact binding, release its allocation and
 * return adapter ownership to the caller. Other states, a wrong coordinator,
 * or an unbound adapter return false without changing either owner. After a
 * successful abandon the caller may manually close/drain/destroy the adapter.
 *
 * Before destroying a coordinator that did not reach STOPPED, first quiesce
 * every external producer and adapter API call, then abandon each World
 * adapter and release it manually. RUNNING and stopping coordinators must use
 * the normal stop path instead. */
bool break_runtime_world_session_abandon(
    BreakRuntimeWorldSession *adapter,
    BreakRuntimeCoordinator *coordinator);

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
