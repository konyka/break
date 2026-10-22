#pragma once

/* Internal test hooks for the Stage 3 break_lua runtime facade. Compiled
 * into the test-only `break_lua_test` variant (BREAK_LUA_TESTING=1),
 * mirroring the runtime_core_test / BREAK_RUNTIME_TESTING pattern; the
 * production `break_lua` target never sees these symbols (nm-verifiable).
 *
 * Allocation failure injection: the budget is the number of further
 * allocations that may succeed; every allocation attempt beyond the budget
 * fails. One shared budget feeds both the runtime struct calloc and every
 * growing request the Lua allocator makes behind lua_newstate/luaL_openlibs,
 * so a budget sweep covers every create-path allocation.
 * BREAK_LUA_TEST_ALLOC_DISABLED turns the hook off (default). */

#include <core/types.h>

#include <script/break_lua.h>

#if defined(BREAK_LUA_TESTING)

#include <stdatomic.h>
#include <stdlib.h>

#define BREAK_LUA_TEST_ALLOC_DISABLED UINT64_MAX

extern _Atomic u64 g_break_lua_test_alloc_budget;

typedef struct BreakLuaRuntime BreakLuaRuntime;

static inline void break_lua_test_set_alloc_budget(u64 budget)
{
    atomic_store_explicit(&g_break_lua_test_alloc_budget, budget,
                          memory_order_relaxed);
}

/* Returns true when the (test-only) budget is exhausted and the allocation
 * must fail. */
static inline bool break_lua_test_alloc_should_fail(void)
{
    u64 budget = atomic_load_explicit(&g_break_lua_test_alloc_budget,
                                      memory_order_relaxed);
    while (budget != BREAK_LUA_TEST_ALLOC_DISABLED) {
        if (budget == 0u) {
            return true;
        }
        if (atomic_compare_exchange_weak_explicit(
                &g_break_lua_test_alloc_budget, &budget, budget - 1u,
                memory_order_relaxed, memory_order_relaxed)) {
            return false;
        }
    }
    return false;
}

/* Returns NULL when the (test-only) budget is exhausted. */
static inline void *break_lua_test_calloc(usize bytes)
{
    if (break_lua_test_alloc_should_fail()) {
        return NULL;
    }
    return calloc(1, bytes);
}

/* Test-only accessor for the VM owned by `runtime`, returned type-erased so
 * the public API never exposes lua_State*. Defined in break_lua_runtime.c
 * (test variant only); a test that links the vendored lua target may cast the
 * result back to lua_State* locally. NULL runtime -> NULL. */
void *break_lua_test_lua_state(BreakLuaRuntime *runtime);

/* Task 2 module probes (test variant only, defined in break_lua_module.c).
 * They are plain owner-thread probes using the Lua C API directly (no
 * metamethods are triggered: all lookups are raw); call them only with the
 * allocation-injection budget disabled. */

typedef struct BreakLuaTestModuleStat {
    bool loaded;    /* a module with this name is registered */
    u32 version;    /* live version; 0 when not loaded */
    u64 hash;       /* FNV-1a-64 of the live source bytes; 0 when not loaded */
} BreakLuaTestModuleStat;

BreakLuaTestModuleStat break_lua_test_module_stat(BreakLuaRuntime *runtime,
                                                  const char *module_name);

/* Number of registered (live) modules; 0 for NULL runtime. */
u32 break_lua_test_module_count(BreakLuaRuntime *runtime);

/* Reads a numeric global from the module's live environment (raw field of
 * the environment table, i.e. defined by the chunk itself). Returns false
 * when the module is unknown, the key is absent, or the value is not a
 * number. */
bool break_lua_test_module_env_number(BreakLuaRuntime *runtime,
                                      const char *module_name,
                                      const char *key, double *out_value);

/* Reads a numeric field of the module's persistent state table (the `state`
 * global of the live environment). Same false contract as above. */
bool break_lua_test_module_state_number(BreakLuaRuntime *runtime,
                                        const char *module_name,
                                        const char *key, double *out_value);

/* Task 3 frame-lifecycle probes (test variant only, defined in
 * break_lua_value.c). Plain owner-thread probes using no Lua API except
 * where noted; call them only with the allocation-injection budget
 * disabled. */

/* Bounded copy of the runtime's most recent frame-hook fault record plus
 * the lifetime fault counter. All fixed storage; never allocates. */
typedef struct BreakLuaTestFrameError {
    bool valid;            /* at least one fault has been recorded */
    u64 frame_seq;         /* begin_frame sequence number of the last fault */
    u64 total;             /* lifetime count of frame hook faults */
    bool budget;           /* last fault was an instruction-budget trip */
    bool dispatch_failure; /* last fault was dispatch-level, not a module hook */
    char module[BREAK_LUA_MAX_MODULE_NAME_BYTES];
    char hook[16];
    char message[128];
} BreakLuaTestFrameError;

BreakLuaTestFrameError break_lua_test_last_frame_error(BreakLuaRuntime *runtime);

/* True when the named live module's frame hooks are currently marked
 * disabled (instruction-budget runaway policy). False for unknown names. */
bool break_lua_test_module_hooks_disabled(BreakLuaRuntime *runtime,
                                          const char *module_name);

/* Installs the test-only `_test_reload_now()` binding into the named live
 * module's environment: when Lua code calls it, the runtime reloads
 * `target_module` with the given source. This simulates a script-triggered
 * reload path (the production `break.*` surface has no reload binding) so
 * the Task 3 frame snapshot semantics (pinned environments survive a
 * mid-dispatch reload) are exercisable without one. Error surface mirrors
 * load_module's admission checks (INVALID shapes, OVERLOAD bytes, STALE
 * unknown module, REJECTED non-owner). */
BreakLuaError break_lua_test_install_reloader(BreakLuaRuntime *runtime,
                                              const char *module_name,
                                              const char *target_module,
                                              const void *source,
                                              usize source_size);

#else

#include <stdlib.h>

static inline void *break_lua_test_calloc(usize bytes)
{
    return calloc(1, bytes);
}

#endif
