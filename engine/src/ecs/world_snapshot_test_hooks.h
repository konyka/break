#pragma once
/* Internal test hooks for World snapshots. Compiled into the test-only
 * `break_ecs_replication_test` variant (BREAK_WORLD_DELTA_TESTING=1),
 * mirroring editor_test_hooks.h; the production `break_ecs_replication`
 * target never sees these symbols.
 *
 * Allocation failure injection: the budget is the number of further
 * snapshot-owned allocations that may succeed; every attempt beyond it
 * fails. One shared budget covers the snapshot struct, its entity array,
 * its byte block, the filter's keep-mask and each entity's component
 * array, so a test can walk the cleanup path after any single failure.
 * BREAK_WORLD_SNAPSHOT_TEST_ALLOC_DISABLED turns the hook off (default). */

#include <core/types.h>

#if defined(BREAK_WORLD_DELTA_TESTING)

#include <stdatomic.h>
#include <stdlib.h>

#define BREAK_WORLD_SNAPSHOT_TEST_ALLOC_DISABLED UINT64_MAX

extern _Atomic u64 g_break_world_snapshot_test_alloc_budget;

static inline void break_world_snapshot_test_set_alloc_budget(u64 budget) {
    atomic_store_explicit(&g_break_world_snapshot_test_alloc_budget, budget,
                          memory_order_relaxed);
}

static inline bool break_world_snapshot_test_alloc_should_fail(void) {
    u64 budget = atomic_load_explicit(&g_break_world_snapshot_test_alloc_budget,
                                      memory_order_relaxed);
    while (budget != BREAK_WORLD_SNAPSHOT_TEST_ALLOC_DISABLED) {
        if (budget == 0u) return true;
        if (atomic_compare_exchange_weak_explicit(
                &g_break_world_snapshot_test_alloc_budget, &budget, budget - 1u,
                memory_order_relaxed, memory_order_relaxed)) {
            return false;
        }
    }
    return false;
}

static inline void *break_world_snapshot_test_calloc(usize count, usize bytes) {
    if (break_world_snapshot_test_alloc_should_fail()) return NULL;
    return calloc(count, bytes);
}

static inline void *break_world_snapshot_test_malloc(usize bytes) {
    if (break_world_snapshot_test_alloc_should_fail()) return NULL;
    return malloc(bytes);
}

#else

#include <stdlib.h>

/* Production passthrough: macros, so the production archive carries no
 * break_world_snapshot_test_* symbol at all. */
#define break_world_snapshot_test_calloc(count, bytes) calloc((count), (bytes))
#define break_world_snapshot_test_malloc(bytes) malloc(bytes)

#endif
