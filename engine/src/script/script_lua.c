#include <script/script_lua.h>
#include <ecs/ecs.h>
#include <physics/physics.h>
#include <platform/input.h>
#include <core/log.h>

#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/* Registry key under which the owning LuaScript* is stashed so the C bindings
 * can reach the host systems. */
#define BREAK_LS_REGKEY "BreakLuaScript"

static LuaScript *ls_from_state(lua_State *L) {
    lua_getfield(L, LUA_REGISTRYINDEX, BREAK_LS_REGKEY);
    LuaScript *ls = (LuaScript *)lua_touserdata(L, -1);
    lua_pop(L, 1);
    return ls;
}

/* Validate a 1-based body id argument against the physics world. Returns NULL
 * (without raising) when out of range or no physics world is bound. */
static RigidBody *checked_body(lua_State *L, PhysicsWorld *pw, int arg) {
    if (!pw) return NULL;
    lua_Integer id = luaL_checkinteger(L, arg);
    if (id <= 0 || (u32)id >= pw->count) return NULL;
    return &pw->bodies[(u32)id];
}

/* -------------------------------------------------------------------------
 *  engine.* bindings
 * ------------------------------------------------------------------------- */

static int l_log(lua_State *L) {
    const char *msg = luaL_checkstring(L, 1);
    LOG_INFO("[lua] %s", msg);
    return 0;
}

static int l_entity_count(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    World *w = ls ? (World *)ls->world : NULL;
    lua_pushinteger(L, w ? (lua_Integer)w->entity_count : 0);
    return 1;
}

static int l_body_count(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    PhysicsWorld *pw = ls ? (PhysicsWorld *)ls->physics : NULL;
    lua_pushinteger(L, pw ? (lua_Integer)pw->count : 0);
    return 1;
}

static int l_get_pos(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    RigidBody *b = checked_body(L, ls ? (PhysicsWorld *)ls->physics : NULL, 1);
    if (!b) return 0;
    lua_pushnumber(L, b->position.e[0]);
    lua_pushnumber(L, b->position.e[1]);
    lua_pushnumber(L, b->position.e[2]);
    return 3;
}

static int l_set_pos(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    RigidBody *b = checked_body(L, ls ? (PhysicsWorld *)ls->physics : NULL, 1);
    if (!b) return 0;
    b->position.e[0] = (f32)luaL_checknumber(L, 2);
    b->position.e[1] = (f32)luaL_checknumber(L, 3);
    b->position.e[2] = (f32)luaL_checknumber(L, 4);
    return 0;
}

static int l_get_vel(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    RigidBody *b = checked_body(L, ls ? (PhysicsWorld *)ls->physics : NULL, 1);
    if (!b) return 0;
    lua_pushnumber(L, b->velocity.e[0]);
    lua_pushnumber(L, b->velocity.e[1]);
    lua_pushnumber(L, b->velocity.e[2]);
    return 3;
}

static int l_set_vel(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    RigidBody *b = checked_body(L, ls ? (PhysicsWorld *)ls->physics : NULL, 1);
    if (!b) return 0;
    b->velocity.e[0] = (f32)luaL_checknumber(L, 2);
    b->velocity.e[1] = (f32)luaL_checknumber(L, 3);
    b->velocity.e[2] = (f32)luaL_checknumber(L, 4);
    return 0;
}

static int l_apply_impulse(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    PhysicsWorld *pw = ls ? (PhysicsWorld *)ls->physics : NULL;
    if (!pw) return 0;
    lua_Integer id = luaL_checkinteger(L, 1);
    if (id <= 0 || (u32)id >= pw->count) return 0;
    Vec3 imp = vec3((f32)luaL_checknumber(L, 2),
                    (f32)luaL_checknumber(L, 3),
                    (f32)luaL_checknumber(L, 4));
    physics_body_apply_impulse(pw, (u32)id, imp);
    return 0;
}

static int l_spawn(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    PhysicsWorld *pw = ls ? (PhysicsWorld *)ls->physics : NULL;
    if (!pw) { lua_pushinteger(L, 0); return 1; }
    Vec3 pos = vec3((f32)luaL_checknumber(L, 1),
                    (f32)luaL_checknumber(L, 2),
                    (f32)luaL_checknumber(L, 3));
    f32 mass = (f32)luaL_optnumber(L, 4, 1.0);
    u32 id = physics_body_create(pw, pos, vec3(0.5f, 0.5f, 0.5f), mass, false, 0);
    lua_pushinteger(L, (lua_Integer)id);
    return 1;
}

static int l_body_set_ccd(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    PhysicsWorld *pw = ls ? (PhysicsWorld *)ls->physics : NULL;
    if (!pw) return 0;
    lua_Integer id = luaL_checkinteger(L, 1);
    bool on = lua_toboolean(L, 2);
    if (id > 0 && (u32)id < pw->count) physics_body_set_ccd(pw, (u32)id, on);
    return 0;
}

static int l_key_down(lua_State *L) {
    LuaScript *ls = ls_from_state(L);
    InputState *in = ls ? (InputState *)ls->input : NULL;
    lua_Integer key = luaL_checkinteger(L, 1);
    bool down = false;
    if (in && key >= 0 && key < 512) down = input_key_down(in, (int)key);
    lua_pushboolean(L, down);
    return 1;
}

static const luaL_Reg k_engine_api[] = {
    { "log",          l_log },
    { "entity_count", l_entity_count },
    { "body_count",   l_body_count },
    { "get_pos",      l_get_pos },
    { "set_pos",      l_set_pos },
    { "get_vel",      l_get_vel },
    { "set_vel",      l_set_vel },
    { "apply_impulse",l_apply_impulse },
    { "spawn",        l_spawn },
    { "body_set_ccd", l_body_set_ccd },
    { "key_down",     l_key_down },
    { NULL, NULL },
};

/* -------------------------------------------------------------------------
 *  Lifecycle
 * ------------------------------------------------------------------------- */

bool lua_script_init(LuaScript *ls) {
    if (!ls) return false;
    memset(ls, 0, sizeof(*ls));
    ls->L = luaL_newstate();
    if (!ls->L) return false;
    luaL_openlibs(ls->L);

    /* Stash the owning struct so bindings can reach the host systems. */
    lua_pushlightuserdata(ls->L, ls);
    lua_setfield(ls->L, LUA_REGISTRYINDEX, BREAK_LS_REGKEY);

    /* engine.* table. */
    luaL_newlib(ls->L, k_engine_api);
    lua_setglobal(ls->L, "engine");
    return true;
}

void lua_script_shutdown(LuaScript *ls) {
    if (!ls) return;
    if (ls->L) lua_close(ls->L);
    memset(ls, 0, sizeof(*ls));
}

void lua_script_bind_host(LuaScript *ls, void *world, void *physics, void *input) {
    if (!ls) return;
    ls->world = world;
    ls->physics = physics;
    ls->input = input;
}

static void refresh_hooks(LuaScript *ls) {
    lua_State *L = ls->L;
    lua_getglobal(L, "on_start");  ls->has_start  = lua_isfunction(L, -1); lua_pop(L, 1);
    lua_getglobal(L, "on_update"); ls->has_update = lua_isfunction(L, -1); lua_pop(L, 1);
    lua_getglobal(L, "on_spawn");  ls->has_spawn  = lua_isfunction(L, -1); lua_pop(L, 1);
}

/* Run the chunk currently on top of the stack (a loaded function). Pops it.
 * Logs and returns false on runtime error. */
static bool run_loaded_chunk(LuaScript *ls, const char *what) {
    if (lua_pcall(ls->L, 0, 0, 0) != LUA_OK) {
        LOG_ERROR("Lua run error (%s): %s", what, lua_tostring(ls->L, -1));
        lua_pop(ls->L, 1);
        return false;
    }
    refresh_hooks(ls);
    ls->loaded = true;
    return true;
}

bool lua_script_load_string(LuaScript *ls, const char *code, const char *chunk_name) {
    if (!ls || !ls->L || !code) return false;
    if (luaL_loadbuffer(ls->L, code, strlen(code),
                        chunk_name ? chunk_name : "=chunk") != LUA_OK) {
        LOG_ERROR("Lua compile error: %s", lua_tostring(ls->L, -1));
        lua_pop(ls->L, 1);
        return false;
    }
    return run_loaded_chunk(ls, chunk_name ? chunk_name : "chunk");
}

static u32 file_mtime(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return (u32)st.st_mtime;
}

bool lua_script_load(LuaScript *ls, const char *path) {
    if (!ls || !ls->L || !path) return false;
    if (luaL_loadfile(ls->L, path) != LUA_OK) {
        LOG_ERROR("Lua load error: %s", lua_tostring(ls->L, -1));
        lua_pop(ls->L, 1);
        return false;
    }
    snprintf(ls->path, sizeof(ls->path), "%s", path);
    ls->last_mtime = file_mtime(path);
    bool ok = run_loaded_chunk(ls, path);
    if (ok) LOG_INFO("Lua script loaded: %s (start=%d update=%d spawn=%d)",
                     path, ls->has_start, ls->has_update, ls->has_spawn);
    return ok;
}

void lua_script_reload_if_changed(LuaScript *ls) {
    if (!ls || !ls->L || ls->path[0] == '\0') return;
    u32 mt = file_mtime(ls->path);
    if (mt != 0 && mt != ls->last_mtime) {
        ls->last_mtime = mt;
        if (luaL_loadfile(ls->L, ls->path) != LUA_OK) {
            LOG_ERROR("Lua reload error: %s", lua_tostring(ls->L, -1));
            lua_pop(ls->L, 1);
            return;
        }
        if (run_loaded_chunk(ls, ls->path))
            LOG_INFO("Lua script reloaded: %s", ls->path);
    }
}

/* -------------------------------------------------------------------------
 *  Hook invocation
 * ------------------------------------------------------------------------- */

bool lua_script_call_void(LuaScript *ls, const char *fn_name) {
    if (!ls || !ls->L || !fn_name) return false;
    lua_getglobal(ls->L, fn_name);
    if (!lua_isfunction(ls->L, -1)) { lua_pop(ls->L, 1); return false; }
    if (lua_pcall(ls->L, 0, 0, 0) != LUA_OK) {
        LOG_ERROR("Lua call error (%s): %s", fn_name, lua_tostring(ls->L, -1));
        lua_pop(ls->L, 1);
        return false;
    }
    return true;
}

void lua_script_call_start(LuaScript *ls) {
    if (ls && ls->has_start) lua_script_call_void(ls, "on_start");
}

void lua_script_call_spawn(LuaScript *ls) {
    if (ls && ls->has_spawn) lua_script_call_void(ls, "on_spawn");
}

void lua_script_call_update(LuaScript *ls, f32 dt) {
    if (!ls || !ls->L || !ls->has_update) return;
    lua_getglobal(ls->L, "on_update");
    if (!lua_isfunction(ls->L, -1)) { lua_pop(ls->L, 1); return; }
    lua_pushnumber(ls->L, (lua_Number)dt);
    if (lua_pcall(ls->L, 1, 0, 0) != LUA_OK) {
        LOG_ERROR("Lua on_update error: %s", lua_tostring(ls->L, -1));
        lua_pop(ls->L, 1);
    }
}

/* -------------------------------------------------------------------------
 *  Global number exchange
 * ------------------------------------------------------------------------- */

void lua_script_set_number(LuaScript *ls, const char *name, f64 value) {
    if (!ls || !ls->L || !name) return;
    lua_pushnumber(ls->L, (lua_Number)value);
    lua_setglobal(ls->L, name);
}

f64 lua_script_get_number(LuaScript *ls, const char *name, f64 fallback) {
    if (!ls || !ls->L || !name) return fallback;
    lua_getglobal(ls->L, name);
    f64 v = fallback;
    if (lua_isnumber(ls->L, -1)) v = (f64)lua_tonumber(ls->L, -1);
    lua_pop(ls->L, 1);
    return v;
}
