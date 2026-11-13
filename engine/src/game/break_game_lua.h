#pragma once

#include <game/break_game.h>
#include <script/break_lua.h>

typedef struct BreakGameLuaAdapter BreakGameLuaAdapter;

typedef struct BreakGameLuaFault {
    bool valid;
    u64 total;
    Entity entity;
    char module[BREAK_GAME_NAME_CAP];
    BreakLuaError error;
} BreakGameLuaFault;

BreakGameLuaAdapter *break_game_lua_create(BreakGame *game,
                                            BreakLuaRuntime *runtime);
void break_game_lua_destroy(BreakGameLuaAdapter *adapter);
BreakGameLuaFault break_game_lua_last_fault(
    const BreakGameLuaAdapter *adapter);

/* Per-actor script counters for the live actor `entity`. `ticks` counts
 * successful on_actor_tick calls, `failures` failed ones (including handle
 * acquisition), and `skipped` ticks not run because the actor's module was
 * disabled. A module is disabled for the adapter's lifetime after one of its
 * calls trips the runtime instruction budget; other modules keep running.
 * Counters reset when the actor slot is despawned. NULL adapter or out ->
 * BREAK_LUA_INVALID; non-owner thread -> BREAK_LUA_REJECTED; an entity that
 * is not a live actor -> BREAK_LUA_STALE. `out` is zeroed on every non-OK
 * return. */
typedef struct BreakGameLuaActorStats {
    u64 ticks;
    u64 failures;
    u64 skipped;
    BreakLuaError last_error;
    bool disabled;
} BreakGameLuaActorStats;

BreakLuaError break_game_lua_actor_stats(const BreakGameLuaAdapter *adapter,
                                         Entity entity,
                                         BreakGameLuaActorStats *out);
