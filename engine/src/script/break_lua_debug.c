#include <script/break_lua_debug.h>

#include <script/break_lua_internal.h>

#include <stdlib.h>
#include <string.h>

typedef struct BreakLuaBreakpoint {
    char module[BREAK_LUA_DEBUG_MODULE_CAPACITY];
    u32 id;
    u32 line;
    bool used;
} BreakLuaBreakpoint;

struct BreakLuaDebug {
    BreakLuaRuntime *runtime;
    BreakLuaDebugPauseFn on_pause;
    void *user;
    bool enabled;
    bool paused;
    BreakLuaBreakpoint breakpoints[BREAK_LUA_DEBUG_MAX_BREAKPOINTS];
    u32 next_breakpoint_id;
    BreakLuaDebugStep step;
    u32 step_depth;
    BreakLuaDebugPause pause;
    lua_Debug frames[BREAK_LUA_DEBUG_MAX_FRAMES];
    BreakLuaDebugFrame frame_info[BREAK_LUA_DEBUG_MAX_FRAMES];
    u32 frame_count;
    BreakLuaError stack_error;
};

static BreakLuaError break_lua_debug_owner(BreakLuaDebug *debug)
{
    if (!debug) {
        return BREAK_LUA_INVALID;
    }
    return break_lua_runtime_check_owner(debug->runtime);
}

static bool break_lua_debug_copy(char *out, usize capacity, const char *source)
{
    usize len;
    if (!source) {
        source = "";
    }
    len = break_lua_name_len(source, capacity);
    if (len >= capacity) {
        return false;
    }
    memcpy(out, source, len);
    out[len] = '\0';
    return true;
}

static u32 break_lua_debug_depth(lua_State *L)
{
    lua_Debug ar;
    u32 depth = 0u;
    while (lua_getstack(L, (int)depth, &ar) != 0) {
        depth++;
    }
    return depth;
}

static bool break_lua_debug_source_module(lua_Debug *ar, char *out,
                                          usize capacity)
{
    if (!ar->source || ar->source[0] != '@') {
        out[0] = '\0';
        return true;
    }
    return break_lua_debug_copy(out, capacity, ar->source + 1);
}

static void break_lua_debug_capture_stack(BreakLuaDebug *debug)
{
    lua_State *L = debug->runtime->L;
    u32 level = 0u;
    debug->frame_count = 0u;
    debug->stack_error = BREAK_LUA_OK;
    for (;;) {
        lua_Debug ar;
        BreakLuaDebugFrame *out;
        if (lua_getstack(L, (int)level, &ar) == 0) {
            break;
        }
        level++;
        if (lua_getinfo(L, "nSl", &ar) == 0) {
            debug->stack_error = BREAK_LUA_FAILED;
            break;
        }
        if (strcmp(ar.what, "C") == 0) {
            continue;
        }
        if (debug->frame_count >= BREAK_LUA_DEBUG_MAX_FRAMES) {
            debug->stack_error = BREAK_LUA_OVERLOAD;
            break;
        }
        out = &debug->frame_info[debug->frame_count];
        memset(out, 0, sizeof(*out));
        if (!break_lua_debug_source_module(&ar, out->module,
                                           sizeof(out->module)) ||
            !break_lua_debug_copy(out->function, sizeof(out->function),
                                  ar.name)) {
            debug->stack_error = BREAK_LUA_OVERLOAD;
            break;
        }
        out->line = ar.currentline > 0 ? (u32)ar.currentline : 0u;
        out->defined_line = ar.linedefined > 0 ? (u32)ar.linedefined : 0u;
        debug->frames[debug->frame_count] = ar;
        debug->frame_count++;
    }
}

static bool break_lua_debug_breakpoint_matches(const BreakLuaDebug *debug,
                                                const char *module, u32 line)
{
    u32 i;
    for (i = 0u; i < BREAK_LUA_DEBUG_MAX_BREAKPOINTS; i++) {
        const BreakLuaBreakpoint *breakpoint = &debug->breakpoints[i];
        if (breakpoint->used && breakpoint->line == line &&
            strcmp(breakpoint->module, module) == 0) {
            return true;
        }
    }
    return false;
}

static bool break_lua_debug_step_matches(const BreakLuaDebug *debug, u32 depth)
{
    switch (debug->step) {
    case BREAK_LUA_DEBUG_STEP_INTO:
        return true;
    case BREAK_LUA_DEBUG_STEP_OVER:
        return depth <= debug->step_depth;
    case BREAK_LUA_DEBUG_STEP_OUT:
        return depth < debug->step_depth;
    default:
        return false;
    }
}

static void break_lua_debug_observer(lua_State *L, lua_Debug *ar, void *user)
{
    BreakLuaDebug *debug = (BreakLuaDebug *)user;
    BreakLuaDebugStep action = BREAK_LUA_DEBUG_STEP_NONE;
    u32 depth;
    bool breakpoint;
    bool step;
    if (!debug->enabled || debug->paused || ar->event != LUA_HOOKLINE ||
        ar->currentline <= 0) {
        return;
    }
    if (lua_getinfo(L, "Sl", ar) == 0 ||
        !break_lua_debug_source_module(ar, debug->pause.module,
                                       sizeof(debug->pause.module))) {
        return;
    }
    depth = break_lua_debug_depth(L);
    breakpoint = break_lua_debug_breakpoint_matches(
        debug, debug->pause.module, (u32)ar->currentline);
    step = break_lua_debug_step_matches(debug, depth);
    if (!breakpoint && !step) {
        return;
    }
    debug->pause.reason = breakpoint ? BREAK_LUA_DEBUG_PAUSE_BREAKPOINT
                                     : BREAK_LUA_DEBUG_PAUSE_STEP;
    debug->pause.line = (u32)ar->currentline;
    debug->step = BREAK_LUA_DEBUG_STEP_NONE;
    break_lua_debug_capture_stack(debug);
    debug->paused = true;
    if (debug->on_pause) {
        action = debug->on_pause(debug, &debug->pause, debug->user);
    }
    debug->paused = false;
    if (debug->enabled && action >= BREAK_LUA_DEBUG_STEP_INTO &&
        action <= BREAK_LUA_DEBUG_STEP_OUT) {
        debug->step = action;
        debug->step_depth = depth;
    }
}

BreakLuaDebug *break_lua_debug_create(BreakLuaRuntime *runtime,
                                      BreakLuaDebugPauseFn on_pause,
                                      void *user)
{
    BreakLuaDebug *debug;
    if (break_lua_runtime_check_owner(runtime) != BREAK_LUA_OK ||
        runtime->execution_observer) {
        return NULL;
    }
    debug = (BreakLuaDebug *)calloc(1u, sizeof(*debug));
    if (!debug) {
        return NULL;
    }
    debug->runtime = runtime;
    debug->on_pause = on_pause;
    debug->user = user;
    debug->next_breakpoint_id = 1u;
    break_lua_execution_observer_set(runtime, break_lua_debug_observer, debug);
    return debug;
}

void break_lua_debug_destroy(BreakLuaDebug *debug)
{
    if (!debug || debug->paused || break_lua_debug_owner(debug) != BREAK_LUA_OK) {
        return;
    }
    break_lua_execution_observer_set(debug->runtime, NULL, NULL);
    free(debug);
}

BreakLuaError break_lua_debug_set_enabled(BreakLuaDebug *debug, bool enabled)
{
    BreakLuaError owner = break_lua_debug_owner(debug);
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    debug->enabled = enabled;
    break_lua_execution_observer_enable(debug->runtime, enabled);
    if (!enabled) {
        debug->step = BREAK_LUA_DEBUG_STEP_NONE;
    }
    return BREAK_LUA_OK;
}

BreakLuaError break_lua_debug_breakpoint_set(BreakLuaDebug *debug,
                                              const char *module, u32 line,
                                              u32 *out_id)
{
    BreakLuaError owner = break_lua_debug_owner(debug);
    usize module_len;
    u32 i;
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!module || !out_id || line == 0u) {
        return BREAK_LUA_INVALID;
    }
    module_len = break_lua_name_len(module, BREAK_LUA_DEBUG_MODULE_CAPACITY);
    if (module_len == 0u || module_len >= BREAK_LUA_DEBUG_MODULE_CAPACITY) {
        return BREAK_LUA_INVALID;
    }
    if (debug->next_breakpoint_id == 0u) {
        return BREAK_LUA_OVERLOAD;
    }
    for (i = 0u; i < BREAK_LUA_DEBUG_MAX_BREAKPOINTS; i++) {
        BreakLuaBreakpoint *breakpoint = &debug->breakpoints[i];
        if (!breakpoint->used) {
            breakpoint->used = true;
            breakpoint->id = debug->next_breakpoint_id;
            breakpoint->line = line;
            memcpy(breakpoint->module, module, module_len + 1u);
            *out_id = breakpoint->id;
            if (debug->next_breakpoint_id == UINT32_MAX) {
                debug->next_breakpoint_id = 0u;
            } else {
                debug->next_breakpoint_id++;
            }
            return BREAK_LUA_OK;
        }
    }
    return BREAK_LUA_OVERLOAD;
}

BreakLuaError break_lua_debug_breakpoint_clear(BreakLuaDebug *debug, u32 id)
{
    BreakLuaError owner = break_lua_debug_owner(debug);
    u32 i;
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    for (i = 0u; i < BREAK_LUA_DEBUG_MAX_BREAKPOINTS; i++) {
        BreakLuaBreakpoint *breakpoint = &debug->breakpoints[i];
        if (breakpoint->used && breakpoint->id == id) {
            memset(breakpoint, 0, sizeof(*breakpoint));
            return BREAK_LUA_OK;
        }
    }
    return BREAK_LUA_STALE;
}

BreakLuaError break_lua_debug_step(BreakLuaDebug *debug,
                                   BreakLuaDebugStep mode)
{
    BreakLuaError owner = break_lua_debug_owner(debug);
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!debug->enabled) {
        return BREAK_LUA_REJECTED;
    }
    if (mode < BREAK_LUA_DEBUG_STEP_INTO || mode > BREAK_LUA_DEBUG_STEP_OUT) {
        return BREAK_LUA_INVALID;
    }
    debug->step = mode;
    debug->step_depth = break_lua_debug_depth(debug->runtime->L);
    return BREAK_LUA_OK;
}

BreakLuaError break_lua_debug_stack(BreakLuaDebug *debug,
                                    BreakLuaDebugFrame *out, usize capacity,
                                    usize *out_count)
{
    BreakLuaError owner = break_lua_debug_owner(debug);
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!debug->paused) {
        return BREAK_LUA_REJECTED;
    }
    if (!out_count || (capacity != 0u && !out)) {
        return BREAK_LUA_INVALID;
    }
    *out_count = debug->frame_count;
    if (debug->stack_error != BREAK_LUA_OK) {
        return debug->stack_error;
    }
    if (capacity < debug->frame_count) {
        return BREAK_LUA_OVERLOAD;
    }
    if (debug->frame_count != 0u) {
        memcpy(out, debug->frame_info,
               debug->frame_count * sizeof(*debug->frame_info));
    }
    return BREAK_LUA_OK;
}

static void break_lua_debug_local_value(lua_State *L, int index,
                                        BreakLuaDebugValue *out)
{
    size_t len;
    const char *string;
    memset(out, 0, sizeof(*out));
    switch (lua_type(L, index)) {
    case LUA_TNIL:
        out->type = BREAK_LUA_DEBUG_VALUE_NIL;
        break;
    case LUA_TBOOLEAN:
        out->type = BREAK_LUA_DEBUG_VALUE_BOOL;
        out->as.b = lua_toboolean(L, index) != 0;
        break;
    case LUA_TNUMBER:
        out->type = BREAK_LUA_DEBUG_VALUE_NUMBER;
        out->as.n = (f64)lua_tonumber(L, index);
        break;
    case LUA_TSTRING:
        out->type = BREAK_LUA_DEBUG_VALUE_STRING;
        string = lua_tolstring(L, index, &len);
        memcpy(out->as.s.data, string, len);
        out->as.s.data[len] = '\0';
        out->as.s.len = (u32)len;
        break;
    default:
        out->type = BREAK_LUA_DEBUG_VALUE_OTHER;
        string = lua_typename(L, lua_type(L, index));
        len = strlen(string);
        memcpy(out->type_name, string, len + 1u);
        break;
    }
}

BreakLuaError break_lua_debug_locals(BreakLuaDebug *debug, u32 frame,
                                     BreakLuaDebugLocal *out, usize capacity,
                                     usize *out_count)
{
    BreakLuaError owner = break_lua_debug_owner(debug);
    lua_State *L;
    usize count = 0u;
    int index;
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!debug->paused) {
        return BREAK_LUA_REJECTED;
    }
    if (frame >= debug->frame_count || !out_count ||
        (capacity != 0u && !out)) {
        return BREAK_LUA_INVALID;
    }
    if (debug->stack_error != BREAK_LUA_OK) {
        return debug->stack_error;
    }
    L = debug->runtime->L;
    if (!lua_checkstack(L, 4)) {
        return BREAK_LUA_OVERLOAD;
    }
    for (index = 1;; index++) {
        const char *name = lua_getlocal(L, &debug->frames[frame], index);
        size_t len;
        if (!name) {
            break;
        }
        len = break_lua_name_len(name, BREAK_LUA_DEBUG_LOCAL_NAME_CAPACITY);
        if (len >= BREAK_LUA_DEBUG_LOCAL_NAME_CAPACITY) {
            lua_pop(L, 1);
            return BREAK_LUA_OVERLOAD;
        }
        if (lua_type(L, -1) == LUA_TSTRING) {
            (void)lua_tolstring(L, -1, &len);
            if (len >= BREAK_LUA_DEBUG_STRING_CAPACITY) {
                lua_pop(L, 1);
                return BREAK_LUA_OVERLOAD;
            }
        }
        lua_pop(L, 1);
        count++;
    }
    *out_count = count;
    if (capacity < count) {
        return BREAK_LUA_OVERLOAD;
    }
    for (index = 1; (usize)index <= count; index++) {
        const char *name = lua_getlocal(L, &debug->frames[frame], index);
        size_t len = strlen(name);
        BreakLuaDebugLocal *local = &out[index - 1];
        memset(local, 0, sizeof(*local));
        memcpy(local->name, name, len + 1u);
        break_lua_debug_local_value(L, -1, &local->value);
        lua_pop(L, 1);
    }
    return BREAK_LUA_OK;
}
