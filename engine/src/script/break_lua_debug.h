#pragma once

#include <script/break_lua.h>

#define BREAK_LUA_DEBUG_MAX_BREAKPOINTS 32u
#define BREAK_LUA_DEBUG_MAX_FRAMES 32u
#define BREAK_LUA_DEBUG_MODULE_CAPACITY 128u
#define BREAK_LUA_DEBUG_FUNCTION_CAPACITY 64u
#define BREAK_LUA_DEBUG_LOCAL_NAME_CAPACITY 64u
#define BREAK_LUA_DEBUG_STRING_CAPACITY 128u

typedef struct BreakLuaDebug BreakLuaDebug;

typedef enum BreakLuaDebugPauseReason {
    BREAK_LUA_DEBUG_PAUSE_BREAKPOINT = 1,
    BREAK_LUA_DEBUG_PAUSE_STEP = 2
} BreakLuaDebugPauseReason;

typedef enum BreakLuaDebugStep {
    BREAK_LUA_DEBUG_STEP_NONE = 0,
    BREAK_LUA_DEBUG_STEP_INTO,
    BREAK_LUA_DEBUG_STEP_OVER,
    BREAK_LUA_DEBUG_STEP_OUT
} BreakLuaDebugStep;

typedef struct BreakLuaDebugPause {
    BreakLuaDebugPauseReason reason;
    char module[BREAK_LUA_DEBUG_MODULE_CAPACITY];
    u32 line;
} BreakLuaDebugPause;

typedef struct BreakLuaDebugFrame {
    char module[BREAK_LUA_DEBUG_MODULE_CAPACITY];
    char function[BREAK_LUA_DEBUG_FUNCTION_CAPACITY];
    u32 line;
    u32 defined_line;
} BreakLuaDebugFrame;

typedef enum BreakLuaDebugValueType {
    BREAK_LUA_DEBUG_VALUE_NIL = 0,
    BREAK_LUA_DEBUG_VALUE_BOOL,
    BREAK_LUA_DEBUG_VALUE_NUMBER,
    BREAK_LUA_DEBUG_VALUE_STRING,
    BREAK_LUA_DEBUG_VALUE_OTHER
} BreakLuaDebugValueType;

typedef struct BreakLuaDebugValue {
    BreakLuaDebugValueType type;
    char type_name[16];
    union {
        bool b;
        f64 n;
        struct {
            char data[BREAK_LUA_DEBUG_STRING_CAPACITY];
            u32 len;
        } s;
    } as;
} BreakLuaDebugValue;

typedef struct BreakLuaDebugLocal {
    char name[BREAK_LUA_DEBUG_LOCAL_NAME_CAPACITY];
    BreakLuaDebugValue value;
} BreakLuaDebugLocal;

typedef BreakLuaDebugStep (*BreakLuaDebugPauseFn)(
    BreakLuaDebug *debug, const BreakLuaDebugPause *pause, void *user);

BreakLuaDebug *break_lua_debug_create(BreakLuaRuntime *runtime,
                                      BreakLuaDebugPauseFn on_pause,
                                      void *user);
void break_lua_debug_destroy(BreakLuaDebug *debug);
BreakLuaError break_lua_debug_set_enabled(BreakLuaDebug *debug, bool enabled);
BreakLuaError break_lua_debug_breakpoint_set(BreakLuaDebug *debug,
                                              const char *module, u32 line,
                                              u32 *out_id);
BreakLuaError break_lua_debug_breakpoint_clear(BreakLuaDebug *debug, u32 id);
BreakLuaError break_lua_debug_step(BreakLuaDebug *debug,
                                   BreakLuaDebugStep mode);
BreakLuaError break_lua_debug_stack(BreakLuaDebug *debug,
                                    BreakLuaDebugFrame *out, usize capacity,
                                    usize *out_count);
BreakLuaError break_lua_debug_locals(BreakLuaDebug *debug, u32 frame,
                                     BreakLuaDebugLocal *out, usize capacity,
                                     usize *out_count);
