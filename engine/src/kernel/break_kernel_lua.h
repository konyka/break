#pragma once

#include <kernel/break_kernel.h>
#include <script/break_lua.h>

typedef struct BreakKernelLuaAdapter BreakKernelLuaAdapter;

typedef struct BreakKernelLuaFault {
    bool valid;
    u64 total;
    Entity entity;
    char module[BREAK_KERNEL_NAME_CAP];
    BreakLuaError error;
} BreakKernelLuaFault;

BreakKernelLuaAdapter *break_kernel_lua_create(BreakKernel *kernel,
                                            BreakLuaRuntime *runtime);
void break_kernel_lua_destroy(BreakKernelLuaAdapter *adapter);
BreakKernelLuaFault break_kernel_lua_last_fault(
    const BreakKernelLuaAdapter *adapter);

/* Per-actor script counters for the live actor `entity`. `ticks` counts
 * successful on_actor_tick calls, `failures` failed ones (including handle
 * acquisition), and `skipped` ticks not run because the actor's module was
 * disabled. A module is disabled for the adapter's lifetime after one of its
 * calls trips the runtime instruction budget; other modules keep running.
 * Counters reset when the actor slot is despawned. NULL adapter or out ->
 * BREAK_LUA_INVALID; non-owner thread -> BREAK_LUA_REJECTED; an entity that
 * is not a live actor -> BREAK_LUA_STALE. `out` is zeroed on every non-OK
 * return. */
typedef struct BreakKernelLuaActorStats {
    u64 ticks;
    u64 failures;
    u64 skipped;
    BreakLuaError last_error;
    bool disabled;
} BreakKernelLuaActorStats;

BreakLuaError break_kernel_lua_actor_stats(const BreakKernelLuaAdapter *adapter,
                                         Entity entity,
                                         BreakKernelLuaActorStats *out);
