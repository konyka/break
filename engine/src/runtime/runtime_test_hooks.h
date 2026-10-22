#pragma once

/* Internal test hooks for the Runtime Core formal facade. Compiled into the
 * test-only `runtime_core_test` variant (BREAK_RUNTIME_TESTING=1), mirroring
 * the break_ecs_replication_test / BREAK_WORLD_DELTA_TESTING pattern; the
 * production `runtime_core` target never sees these symbols.
 *
 * Allocation failure injection: the budget is the number of further
 * allocations that may succeed; every allocation attempt beyond the budget
 * fails. BREAK_RUNTIME_TEST_ALLOC_DISABLED turns the hook off (default). */

#include <core/types.h>

#if defined(BREAK_RUNTIME_TESTING)

#include <stdatomic.h>
#include <stdlib.h>

#define BREAK_RUNTIME_TEST_ALLOC_DISABLED UINT64_MAX

extern _Atomic u64 g_break_runtime_test_alloc_budget;

/* Forward-failure injection for the task facade drain: the budget is the
 * number of further legacy-forward attempts that report TASK_HANDLE_INVALID
 * (as if the legacy task pool were exhausted and its heap fallback OOM'd)
 * without consuming the task call. 0 disables the hook (default). */
extern _Atomic u64 g_break_runtime_test_forward_fail_budget;

/* IO facade worker gates (defined in runtime_io.c, test variant only).
 * gate_pop != 0: workers block BEFORE claiming from the pending ring (the
 * request stays QUEUED). gate_read != 0: workers block AFTER claiming
 * (QUEUED->READING) and BEFORE the VFS read. 0 disables each gate. */
extern _Atomic u32 g_break_runtime_test_io_gate_pop;
extern _Atomic u32 g_break_runtime_test_io_gate_read;
/* Number of requests workers have claimed (QUEUED->READING). */
extern _Atomic u64 g_break_runtime_test_io_popped;

/* Sets both gates and wakes gated workers when a gate is released. Defined
 * in runtime_io.c (test variant); a no-op safe call before init. */
void break_runtime_test_io_set_gates(u32 gate_pop, u32 gate_read);

static inline void break_runtime_test_set_forward_fail_budget(u64 budget)
{
    atomic_store_explicit(&g_break_runtime_test_forward_fail_budget, budget,
                          memory_order_relaxed);
}

static inline bool break_runtime_test_forward_should_fail(void)
{
    u64 budget =
        atomic_load_explicit(&g_break_runtime_test_forward_fail_budget,
                             memory_order_relaxed);
    while (budget != 0u) {
        if (atomic_compare_exchange_weak_explicit(
                &g_break_runtime_test_forward_fail_budget, &budget,
                budget - 1u, memory_order_relaxed, memory_order_relaxed)) {
            return true;
        }
    }
    return false;
}

static inline void break_runtime_test_set_alloc_budget(u64 budget)
{
    atomic_store_explicit(&g_break_runtime_test_alloc_budget, budget,
                          memory_order_relaxed);
}

/* Returns NULL when the (test-only) budget is exhausted. */
static inline void *break_runtime_test_calloc(usize bytes)
{
    u64 budget =
        atomic_load_explicit(&g_break_runtime_test_alloc_budget,
                             memory_order_relaxed);
    while (budget != BREAK_RUNTIME_TEST_ALLOC_DISABLED) {
        if (budget == 0u) {
            return NULL;
        }
        if (atomic_compare_exchange_weak_explicit(
                &g_break_runtime_test_alloc_budget, &budget, budget - 1u,
                memory_order_relaxed, memory_order_relaxed)) {
            break;
        }
    }
    return calloc(1, bytes);
}

#else

#include <stdlib.h>

static inline void *break_runtime_test_calloc(usize bytes)
{
    return calloc(1, bytes);
}

#endif
