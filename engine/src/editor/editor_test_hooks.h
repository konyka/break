#pragma once
/* Internal test hooks for break_editor. Compiled into the test-only
 * `break_editor_test` variant (BREAK_EDITOR_TESTING=1), mirroring the
 * break_lua_test / break_lua_test_hooks.h pattern; the production
 * `break_editor` target never sees these symbols (nm-verifiable).
 *
 * Allocation failure injection: the budget is the number of further
 * editor-owned allocations that may succeed; every attempt beyond the
 * budget fails. One shared budget covers every editor-owned allocation:
 * the doc struct, the name-slot block, the cmd-stack struct, the
 * cmd-stack entry array, and every command object. (The internal World's
 * own allocations belong to break_ecs_replication and are NOT hooked.)
 * BREAK_EDITOR_TEST_ALLOC_DISABLED turns the hook off (default). */

#include <core/types.h>

#if defined(BREAK_EDITOR_TESTING)

#include <stdatomic.h>
#include <stdlib.h>

#define BREAK_EDITOR_TEST_ALLOC_DISABLED UINT64_MAX

extern _Atomic u64 g_break_editor_test_alloc_budget;

static inline void break_editor_test_set_alloc_budget(u64 budget) {
    atomic_store_explicit(&g_break_editor_test_alloc_budget, budget,
                          memory_order_relaxed);
}

/* Returns true when the (test-only) budget is exhausted and the allocation
 * must fail. */
static inline bool break_editor_test_alloc_should_fail(void) {
    u64 budget = atomic_load_explicit(&g_break_editor_test_alloc_budget,
                                      memory_order_relaxed);
    while (budget != BREAK_EDITOR_TEST_ALLOC_DISABLED) {
        if (budget == 0u) {
            return true;
        }
        if (atomic_compare_exchange_weak_explicit(
                &g_break_editor_test_alloc_budget, &budget, budget - 1u,
                memory_order_relaxed, memory_order_relaxed)) {
            return false;
        }
    }
    return false;
}

/* Returns NULL when the (test-only) budget is exhausted. */
static inline void *break_editor_test_calloc(usize bytes) {
    if (break_editor_test_alloc_should_fail()) {
        return NULL;
    }
    return calloc(1, bytes);
}

#else

#include <stdlib.h>

static inline void *break_editor_test_calloc(usize bytes) {
    return calloc(1, bytes);
}

#endif
