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

#else

#include <stdlib.h>

static inline void *break_lua_test_calloc(usize bytes)
{
    return calloc(1, bytes);
}

#endif
