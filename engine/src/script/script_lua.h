#pragma once
#include <core/types.h>

/* ==========================================================================
 *  script_lua — real Lua 5.4 scripting (vendored in external/lua).
 *
 *  A LuaScript owns one lua_State with the standard libraries plus an `engine`
 *  table that binds the host's ECS World, PhysicsWorld and InputState. Scripts
 *  are plain `.lua` files; the host calls global hooks (`on_start`, `on_update`,
 *  `on_spawn`) and the file is hot-reloaded when its mtime changes.
 *
 *  Host bindings are optional: every `engine.*` function degrades gracefully
 *  (returns 0 / no-op) when the corresponding host pointer is NULL, so a script
 *  can be exercised in isolation (see tests/test_script_lua.c).
 * ========================================================================== */

typedef struct lua_State lua_State;

typedef struct {
    lua_State *L;
    char       path[256];
    u32        last_mtime;
    bool       loaded;
    bool       has_start;
    bool       has_update;
    bool       has_spawn;

    /* Host systems exposed to `engine.*` (any may be NULL). */
    void *world;     /* World*        */
    void *physics;   /* PhysicsWorld* */
    void *input;     /* InputState*   */
} LuaScript;

/* Create the lua_State and register the `engine` table. Returns false on OOM. */
bool lua_script_init(LuaScript *ls);
void lua_script_shutdown(LuaScript *ls);

/* Point the `engine.*` bindings at host systems (any may be NULL). */
void lua_script_bind_host(LuaScript *ls, void *world, void *physics, void *input);

/* Load + execute a chunk. `lua_script_load` reads from a file (and records its
 * mtime for hot reload); `lua_script_load_string` runs an in-memory chunk. Both
 * report syntax/runtime errors via the log and return false. */
bool lua_script_load(LuaScript *ls, const char *path);
bool lua_script_load_string(LuaScript *ls, const char *code, const char *chunk_name);

/* Re-run the file if its mtime changed since the last load. No-op if unchanged
 * or if no file was loaded. */
void lua_script_reload_if_changed(LuaScript *ls);

/* Invoke global hooks if present. on_update passes dt (seconds). */
void lua_script_call_start(LuaScript *ls);
void lua_script_call_update(LuaScript *ls, f32 dt);
void lua_script_call_spawn(LuaScript *ls);

/* Generic no-argument call of a global function by name. Returns false if the
 * global is missing/not a function or the call raised an error. */
bool lua_script_call_void(LuaScript *ls, const char *fn_name);

/* Read/write a numeric global (for host<->script parameter exchange). */
void lua_script_set_number(LuaScript *ls, const char *name, f64 value);
f64  lua_script_get_number(LuaScript *ls, const char *name, f64 fallback);
