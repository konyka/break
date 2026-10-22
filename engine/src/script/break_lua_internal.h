#pragma once

/* Internal to the break_lua library: shared by break_lua_runtime.c and
 * break_lua_module.c. NOT public ABI — never installed for consumers, never
 * included by public headers. The public surface stays break_lua.h alone. */

#include <script/break_lua.h>

#include <core/platform_thread.h>

#include <lua/lua.h>

/* One registry slot per module. The environment table (holding the chunk's
 * globals and the `state` field) is the only Lua-side reference a slot
 * needs: the persistent state table stays reachable through the live
 * environment, so no second registry ref exists to leak. */
typedef struct BreakLuaModule {
    char *name;    /* owned copy (bounded by BREAK_LUA_MAX_MODULE_NAME_BYTES) */
    u32 version;   /* 1 at first load; +1 per committed reload */
    u64 hash;      /* FNV-1a-64 of the live source bytes */
    int env_ref;   /* LUA_REGISTRYINDEX reference to the module environment */
    bool occupied;
} BreakLuaModule;

struct BreakLuaRuntime {
    lua_State *L;
    PlatformThreadId owner;
    u32 max_modules;
    u32 max_values;
    usize max_module_bytes;
    u64 instruction_budget;
    BreakLuaModule *modules; /* owned array of max_modules slots */
    u32 module_count;
    int op_ref;              /* registry ref to the protected module-op
                              * dispatch function (set at create bootstrap) */
};

/* break_lua_module.c internals consumed by break_lua_runtime.c. */

/* Registers the protected module-op dispatch closure in the Lua registry.
 * Called from the create bootstrap wrapper, i.e. already under lua_pcall:
 * the cfunction allocation here can longjmp safely. */
void break_lua_module_bootstrap(lua_State *L, BreakLuaRuntime *runtime);

/* Frees every owned module name and the registry array. Pure C: makes no
 * Lua API calls, so it is safe to run immediately before lua_close (which
 * then tears down every remaining registry reference at once). */
void break_lua_module_registry_destroy(BreakLuaRuntime *runtime);
