#include <script/break_lua.h>

#include <script/break_lua_test_hooks.h>

#include <core/platform_thread.h>

#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>

#include <stdlib.h>

/* One runtime = one lua_State = one owner thread. No synchronization
 * primitives: the owner-thread rule in break_lua.h is the whole threading
 * model. The runtime owns the VM it creates and nothing else yet (module
 * registry lands in Task 2, frame hooks in Task 3, host bindings in Task 4);
 * the config caps are recorded here so those tasks enforce them without
 * re-validation. */

struct BreakLuaRuntime {
    lua_State *L;
    PlatformThreadId owner;
    u32 max_modules;
    u32 max_values;
    usize max_module_bytes;
    u64 instruction_budget;
};

#if defined(BREAK_LUA_TESTING)

#include <stdio.h>

_Atomic u64 g_break_lua_test_alloc_budget = BREAK_LUA_TEST_ALLOC_DISABLED;

/* Test-build live-runtime registry: destroy() looks the pointer up BY VALUE
 * and never dereferences it first — a double destroy would otherwise read
 * freed memory before the check could fire. Exactly-once semantics: a
 * registered pointer is freed and removed; any unregistered pointer (double
 * destroy or foreign) aborts with a diagnostic, because destroy() has no
 * return channel. Registration is mandatory at create; exhausting the
 * bounded table is a test bug and also aborts. The spinlock keeps the
 * registry TSan-clean. */
#define BREAK_LUA_REGISTRY_CAPACITY 256u

static atomic_flag g_registry_lock = ATOMIC_FLAG_INIT;
static const void *g_registry[BREAK_LUA_REGISTRY_CAPACITY];
static u32 g_registry_count;

static void registry_lock(void)
{
    while (atomic_flag_test_and_set_explicit(&g_registry_lock,
                                             memory_order_acquire)) {
        platform_thread_yield();
    }
}

static void registry_unlock(void)
{
    atomic_flag_clear_explicit(&g_registry_lock, memory_order_release);
}

static void registry_add(const void *runtime)
{
    bool added = false;
    registry_lock();
    if (g_registry_count < BREAK_LUA_REGISTRY_CAPACITY) {
        g_registry[g_registry_count] = runtime;
        g_registry_count++;
        added = true;
    }
    registry_unlock();
    if (!added) {
        fprintf(stderr,
                "break_lua_runtime_create: test registry exhausted (%u live "
                "runtimes)\n",
                BREAK_LUA_REGISTRY_CAPACITY);
        abort();
    }
}

static bool registry_remove(const void *runtime)
{
    u32 i;
    bool found = false;
    registry_lock();
    for (i = 0; i < g_registry_count; i++) {
        if (g_registry[i] == runtime) {
            g_registry[i] = g_registry[g_registry_count - 1u];
            g_registry_count--;
            found = true;
            break;
        }
    }
    registry_unlock();
    return found;
}

#endif /* BREAK_LUA_TESTING */

/* Lua allocator. Production is plain realloc/free; the test variant routes
 * every growing request through the injection budget so lua_newstate /
 * luaL_openlibs allocation failures are exercisable. `ud` is the owning
 * runtime (unused while the runtime keeps no per-VM accounting; the
 * signature requires it). */
static void *break_lua_alloc(void *ud, void *ptr, size_t osize, size_t nsize)
{
    (void)ud;
    (void)osize;
    if (nsize == 0u) {
        free(ptr);
        return NULL;
    }
#if defined(BREAK_LUA_TESTING)
    if (break_lua_test_alloc_should_fail()) {
        return NULL;
    }
#endif
    return realloc(ptr, nsize);
}

/* luaL_openlibs is not internally protected: an allocation failure inside it
 * would longjmp with no recovery point and hit Lua's default panic (abort).
 * Running it through lua_pcall makes any error (LUA_ERRMEM included) a clean
 * NULL return from create, in test injection and in production alike. */
static int break_lua_openlibs_wrapper(lua_State *L)
{
    luaL_openlibs(L);
    return 0;
}

const char *break_lua_error_name(BreakLuaError error)
{
    switch (error) {
    case BREAK_LUA_OK: return "OK";
    case BREAK_LUA_INVALID: return "INVALID";
    case BREAK_LUA_CLOSED: return "CLOSED";
    case BREAK_LUA_OVERLOAD: return "OVERLOAD";
    case BREAK_LUA_OOM: return "OOM";
    case BREAK_LUA_TIMEOUT: return "TIMEOUT";
    case BREAK_LUA_STALE: return "STALE";
    case BREAK_LUA_REJECTED: return "REJECTED";
    case BREAK_LUA_FAILED: return "FAILED";
    default: return "UNKNOWN";
    }
}

BreakLuaRuntime *break_lua_runtime_create(const BreakLuaRuntimeConfig *config)
{
    BreakLuaRuntime *runtime;
    u32 max_modules = BREAK_LUA_DEFAULT_MAX_MODULES;
    u32 max_values = BREAK_LUA_MAX_VALUES;
    usize max_module_bytes = (usize)BREAK_LUA_MAX_MODULE_BYTES;
    u64 instruction_budget = 0u;

    /* Fail-closed validation: caps above the hard ceilings are rejected,
     * never clamped (documented in break_lua.h). No arithmetic on the
     * untrusted values happens before this gate. */
    if (config) {
        if (config->max_modules > BREAK_LUA_MAX_MODULES ||
            config->max_values > BREAK_LUA_MAX_VALUES ||
            config->max_module_bytes > (usize)BREAK_LUA_MAX_MODULE_BYTES) {
            return NULL;
        }
        if (config->max_modules != 0u) {
            max_modules = config->max_modules;
        }
        if (config->max_values != 0u) {
            max_values = config->max_values;
        }
        if (config->max_module_bytes != 0u) {
            max_module_bytes = config->max_module_bytes;
        }
        instruction_budget = config->instruction_budget;
    }

    runtime = break_lua_test_calloc(sizeof(*runtime));
    if (!runtime) {
        return NULL;
    }

    runtime->L = lua_newstate(break_lua_alloc, runtime);
    if (!runtime->L) {
        free(runtime);
        return NULL;
    }
    /* Standard libraries opened on the owned state, under protection so an
     * allocation failure here fails closed instead of panicking. Per-module
     * sandboxed environments are Task 4 scope; no module can be loaded yet
     * (Task 2), so nothing script-controlled reaches this state. */
    lua_pushcfunction(runtime->L, break_lua_openlibs_wrapper);
    if (lua_pcall(runtime->L, 0, 0, 0) != LUA_OK) {
        lua_close(runtime->L);
        free(runtime);
        return NULL;
    }

    runtime->owner = platform_thread_current_id();
    runtime->max_modules = max_modules;
    runtime->max_values = max_values;
    runtime->max_module_bytes = max_module_bytes;
    runtime->instruction_budget = instruction_budget;
#if defined(BREAK_LUA_TESTING)
    registry_add(runtime);
#endif
    return runtime;
}

void break_lua_runtime_destroy(BreakLuaRuntime *runtime)
{
    if (!runtime) {
        return;
    }
#if defined(BREAK_LUA_TESTING)
    if (!registry_remove(runtime)) {
        fprintf(stderr,
                "break_lua_runtime_destroy: double destroy or foreign "
                "runtime %p\n",
                (void *)runtime);
        abort();
    }
#endif
    lua_close(runtime->L);
    free(runtime);
}

BreakLuaError break_lua_runtime_effective_config(
    const BreakLuaRuntime *runtime, BreakLuaRuntimeConfig *out_config)
{
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!out_config) {
        return BREAK_LUA_INVALID;
    }
    out_config->max_modules = runtime->max_modules;
    out_config->max_values = runtime->max_values;
    out_config->max_module_bytes = runtime->max_module_bytes;
    out_config->instruction_budget = runtime->instruction_budget;
    return BREAK_LUA_OK;
}

BreakLuaError break_lua_runtime_check_owner(const BreakLuaRuntime *runtime)
{
    if (!runtime) {
        return BREAK_LUA_INVALID;
    }
    if (!platform_thread_id_equal(platform_thread_current_id(),
                                  runtime->owner)) {
        return BREAK_LUA_REJECTED;
    }
    return BREAK_LUA_OK;
}

#if defined(BREAK_LUA_TESTING)
void *break_lua_test_lua_state(BreakLuaRuntime *runtime)
{
    if (!runtime) {
        return NULL;
    }
    return (void *)runtime->L;
}
#endif
