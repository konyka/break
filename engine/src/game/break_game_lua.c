#include <game/break_game_lua.h>

#include <game/break_game_internal.h>

#include <stdlib.h>
#include <string.h>

typedef struct BreakGameLuaActor {
    BreakLuaHostHandle handle;
    bool live;
} BreakGameLuaActor;

struct BreakGameLuaAdapter {
    BreakGame *game;
    BreakLuaRuntime *runtime;
    BreakGameLuaActor *actors;
    BreakGameLuaFault last_fault;
};

static void break_game_lua_record_fault(BreakGameLuaAdapter *adapter,
                                        const char *module, Entity entity,
                                        BreakLuaError error)
{
    BreakGameLuaFault *fault = &adapter->last_fault;
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

static void break_game_lua_actor_tick(void *user, const char *module,
                                      Entity entity, f32 dt)
{
    BreakGameLuaAdapter *adapter = (BreakGameLuaAdapter *)user;
    BreakGameLuaActor *actor;
    BreakLuaValue args[2];
    BreakLuaError err;
    u32 slot = break_game_actor_slot(adapter->game, entity);
    if (slot == UINT32_MAX) {
        break_game_lua_record_fault(adapter, module, entity, BREAK_LUA_STALE);
        return;
    }
    actor = &adapter->actors[slot];
    if (!actor->live) {
        u64 token = ((u64)entity.generation << 32) | (u64)entity.index;
        err = break_lua_host_handle_acquire(adapter->runtime, token,
                                            &actor->handle);
        if (err != BREAK_LUA_OK) {
            break_game_lua_record_fault(adapter, module, entity, err);
            return;
        }
        actor->live = true;
    }
    memset(args, 0, sizeof(args));
    args[0].type = BREAK_LUA_VALUE_HOST_HANDLE;
    args[0].as.handle = actor->handle;
    args[1].type = BREAK_LUA_VALUE_NUMBER;
    args[1].as.n = (f64)dt;
    err = break_lua_runtime_call(adapter->runtime, module, "on_actor_tick",
                                 args, 2u, NULL, 0u);
    if (err != BREAK_LUA_OK) {
        break_game_lua_record_fault(adapter, module, entity, err);
    }
}

static void break_game_lua_actor_despawn(void *user, Entity entity)
{
    BreakGameLuaAdapter *adapter = (BreakGameLuaAdapter *)user;
    u32 slot = break_game_actor_slot(adapter->game, entity);
    BreakGameLuaActor *actor;
    BreakLuaError err;
    if (slot == UINT32_MAX) {
        return;
    }
    actor = &adapter->actors[slot];
    if (!actor->live) {
        return;
    }
    err = break_lua_host_handle_release(adapter->runtime, actor->handle);
    actor->live = false;
    memset(&actor->handle, 0, sizeof(actor->handle));
    if (err != BREAK_LUA_OK) {
        break_game_lua_record_fault(adapter, "actor_despawn", entity, err);
    }
}

BreakGameLuaAdapter *break_game_lua_create(BreakGame *game,
                                            BreakLuaRuntime *runtime)
{
    BreakGameLuaAdapter *adapter;
    BreakGameScriptBridge bridge;
    if (!game || !runtime || !break_game_is_owner(game) ||
        break_lua_runtime_check_owner(runtime) != BREAK_LUA_OK) {
        return NULL;
    }
    adapter = (BreakGameLuaAdapter *)calloc(1u, sizeof(*adapter));
    if (!adapter) {
        return NULL;
    }
    adapter->actors = (BreakGameLuaActor *)calloc(game->max_actors,
                                                  sizeof(*adapter->actors));
    if (!adapter->actors) {
        free(adapter);
        return NULL;
    }
    adapter->game = game;
    adapter->runtime = runtime;
    memset(&bridge, 0, sizeof(bridge));
    bridge.user = adapter;
    bridge.actor_tick = break_game_lua_actor_tick;
    bridge.actor_despawn = break_game_lua_actor_despawn;
    if (break_game_set_script_bridge(game, &bridge) != BREAK_GAME_OK) {
        free(adapter->actors);
        free(adapter);
        return NULL;
    }
    return adapter;
}

void break_game_lua_destroy(BreakGameLuaAdapter *adapter)
{
    u32 slot;
    if (!adapter || !break_game_is_owner(adapter->game) ||
        break_lua_runtime_check_owner(adapter->runtime) != BREAK_LUA_OK) {
        return;
    }
    if (adapter->game->script_bridge_used &&
        adapter->game->script_bridge.user == adapter) {
        (void)break_game_set_script_bridge(adapter->game, NULL);
    }
    for (slot = 0u; slot < adapter->game->max_actors; slot++) {
        BreakGameLuaActor *actor = &adapter->actors[slot];
        if (actor->live) {
            (void)break_lua_host_handle_release(adapter->runtime, actor->handle);
            actor->live = false;
        }
    }
    free(adapter->actors);
    free(adapter);
}

BreakGameLuaFault break_game_lua_last_fault(
    const BreakGameLuaAdapter *adapter)
{
    BreakGameLuaFault fault;
    memset(&fault, 0, sizeof(fault));
    if (adapter && break_game_is_owner(adapter->game)) {
        fault = adapter->last_fault;
    }
    return fault;
}
