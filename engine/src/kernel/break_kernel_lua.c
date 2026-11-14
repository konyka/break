#include <kernel/break_kernel_lua.h>

#include <kernel/break_kernel_internal.h>

#include <stdlib.h>
#include <string.h>

typedef struct BreakKernelLuaActor {
    BreakLuaHostHandle handle;
    bool live;
    u64 ticks;
    u64 failures;
    u64 skipped;
    BreakLuaError last_error;
} BreakKernelLuaActor;

struct BreakKernelLuaAdapter {
    BreakKernel *kernel;
    BreakLuaRuntime *runtime;
    BreakKernelLuaActor *actors;
    BreakKernelLuaFault last_fault;
    char disabled[BREAK_KERNEL_HARD_MAX_CLASSES][BREAK_KERNEL_NAME_CAP];
    u32 disabled_count;
};

static bool break_kernel_lua_module_disabled(const BreakKernelLuaAdapter *adapter,
                                           const char *module)
{
    u32 i;
    for (i = 0u; i < adapter->disabled_count; i++) {
        if (strncmp(adapter->disabled[i], module, BREAK_KERNEL_NAME_CAP) == 0) {
            return true;
        }
    }
    return false;
}

static void break_kernel_lua_disable_module(BreakKernelLuaAdapter *adapter,
                                          const char *module)
{
    usize len = 0u;
    char *slot;
    if (break_kernel_lua_module_disabled(adapter, module) ||
        adapter->disabled_count >= BREAK_KERNEL_HARD_MAX_CLASSES) {
        return;
    }
    slot = adapter->disabled[adapter->disabled_count++];
    while (len + 1u < BREAK_KERNEL_NAME_CAP && module[len] != '\0') {
        len++;
    }
    memcpy(slot, module, len);
    slot[len] = '\0';
}

static void break_kernel_lua_record_fault(BreakKernelLuaAdapter *adapter,
                                        const char *module, Entity entity,
                                        BreakLuaError error)
{
    BreakKernelLuaFault *fault = &adapter->last_fault;
    usize len = 0u;
    fault->valid = true;
    fault->total++;
    fault->entity = entity;
    fault->error = error;
    while (len + 1u < sizeof(fault->module) && module[len] != '\0') {
        len++;
    }
    memcpy(fault->module, module, len);
    fault->module[len] = '\0';
}

static void break_kernel_lua_actor_tick(void *user, const char *module,
                                      Entity entity, f32 dt)
{
    BreakKernelLuaAdapter *adapter = (BreakKernelLuaAdapter *)user;
    BreakKernelLuaActor *actor;
    BreakLuaValue args[2];
    BreakLuaError err;
    u64 trips;
    u32 slot = break_kernel_actor_slot(adapter->kernel, entity);
    if (slot == UINT32_MAX) {
        break_kernel_lua_record_fault(adapter, module, entity, BREAK_LUA_STALE);
        return;
    }
    actor = &adapter->actors[slot];
    if (break_kernel_lua_module_disabled(adapter, module)) {
        actor->skipped++;
        return;
    }
    if (!actor->live) {
        u64 token = ((u64)entity.generation << 32) | (u64)entity.index;
        err = break_lua_host_handle_acquire(adapter->runtime, token,
                                            &actor->handle);
        if (err != BREAK_LUA_OK) {
            actor->failures++;
            actor->last_error = err;
            break_kernel_lua_record_fault(adapter, module, entity, err);
            return;
        }
        actor->live = true;
    }
    memset(args, 0, sizeof(args));
    args[0].type = BREAK_LUA_VALUE_HOST_HANDLE;
    args[0].as.handle = actor->handle;
    args[1].type = BREAK_LUA_VALUE_NUMBER;
    args[1].as.n = (f64)dt;
    trips = break_lua_runtime_budget_trip_count(adapter->runtime);
    err = break_lua_runtime_call(adapter->runtime, module, "on_actor_tick",
                                 args, 2u, NULL, 0u);
    if (err != BREAK_LUA_OK) {
        actor->failures++;
        actor->last_error = err;
        if (break_lua_runtime_budget_trip_count(adapter->runtime) != trips) {
            break_kernel_lua_disable_module(adapter, module);
        }
        break_kernel_lua_record_fault(adapter, module, entity, err);
        return;
    }
    actor->ticks++;
}

static void break_kernel_lua_actor_despawn(void *user, Entity entity)
{
    BreakKernelLuaAdapter *adapter = (BreakKernelLuaAdapter *)user;
    u32 slot = break_kernel_actor_slot(adapter->kernel, entity);
    BreakKernelLuaActor *actor;
    BreakLuaError err;
    if (slot == UINT32_MAX) {
        return;
    }
    actor = &adapter->actors[slot];
    actor->ticks = 0u;
    actor->failures = 0u;
    actor->skipped = 0u;
    actor->last_error = BREAK_LUA_OK;
    if (!actor->live) {
        return;
    }
    err = break_lua_host_handle_release(adapter->runtime, actor->handle);
    actor->live = false;
    memset(&actor->handle, 0, sizeof(actor->handle));
    if (err != BREAK_LUA_OK) {
        break_kernel_lua_record_fault(adapter, "actor_despawn", entity, err);
    }
}

BreakKernelLuaAdapter *break_kernel_lua_create(BreakKernel *kernel,
                                            BreakLuaRuntime *runtime)
{
    BreakKernelLuaAdapter *adapter;
    BreakKernelScriptBridge bridge;
    if (!kernel || !runtime || !break_kernel_is_owner(kernel) ||
        break_lua_runtime_check_owner(runtime) != BREAK_LUA_OK) {
        return NULL;
    }
    adapter = (BreakKernelLuaAdapter *)calloc(1u, sizeof(*adapter));
    if (!adapter) {
        return NULL;
    }
    adapter->actors = (BreakKernelLuaActor *)calloc(kernel->max_actors,
                                                  sizeof(*adapter->actors));
    if (!adapter->actors) {
        free(adapter);
        return NULL;
    }
    adapter->kernel = kernel;
    adapter->runtime = runtime;
    memset(&bridge, 0, sizeof(bridge));
    bridge.user = adapter;
    bridge.actor_tick = break_kernel_lua_actor_tick;
    bridge.actor_despawn = break_kernel_lua_actor_despawn;
    if (break_kernel_set_script_bridge(kernel, &bridge) != BREAK_KERNEL_OK) {
        free(adapter->actors);
        free(adapter);
        return NULL;
    }
    return adapter;
}

void break_kernel_lua_destroy(BreakKernelLuaAdapter *adapter)
{
    u32 slot;
    if (!adapter || !break_kernel_is_owner(adapter->kernel) ||
        break_lua_runtime_check_owner(adapter->runtime) != BREAK_LUA_OK) {
        return;
    }
    if (adapter->kernel->script_bridge_used &&
        adapter->kernel->script_bridge.user == adapter) {
        (void)break_kernel_set_script_bridge(adapter->kernel, NULL);
    }
    for (slot = 0u; slot < adapter->kernel->max_actors; slot++) {
        BreakKernelLuaActor *actor = &adapter->actors[slot];
        if (actor->live) {
            (void)break_lua_host_handle_release(adapter->runtime, actor->handle);
            actor->live = false;
        }
    }
    free(adapter->actors);
    free(adapter);
}

BreakKernelLuaFault break_kernel_lua_last_fault(
    const BreakKernelLuaAdapter *adapter)
{
    BreakKernelLuaFault fault;
    memset(&fault, 0, sizeof(fault));
    if (adapter && break_kernel_is_owner(adapter->kernel)) {
        fault = adapter->last_fault;
    }
    return fault;
}

BreakLuaError break_kernel_lua_actor_stats(const BreakKernelLuaAdapter *adapter,
                                         Entity entity,
                                         BreakKernelLuaActorStats *out)
{
    const BreakKernelLuaActor *actor;
    u32 slot;
    if (!out) {
        return BREAK_LUA_INVALID;
    }
    memset(out, 0, sizeof(*out));
    if (!adapter) {
        return BREAK_LUA_INVALID;
    }
    if (!break_kernel_is_owner(adapter->kernel)) {
        return BREAK_LUA_REJECTED;
    }
    slot = break_kernel_actor_slot(adapter->kernel, entity);
    if (slot == UINT32_MAX) {
        return BREAK_LUA_STALE;
    }
    actor = &adapter->actors[slot];
    out->ticks = actor->ticks;
    out->failures = actor->failures;
    out->skipped = actor->skipped;
    out->last_error = actor->last_error;
    out->disabled = break_kernel_lua_module_disabled(
        adapter,
        adapter->kernel->classes[adapter->kernel->actors[slot].class_id].lua_module);
    return BREAK_LUA_OK;
}
