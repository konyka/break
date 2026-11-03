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
