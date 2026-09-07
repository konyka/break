/**
 * @file my_timer.h
 * @brief PAL timers: a small manager driven by the main loop.
 *
 * The manager never reads a clock itself; the injectable now-function
 * keeps tests deterministic (dummy port injects a fake clock). Deadline
 * arithmetic saturates at UINT64_MAX so a valid monotonic clock near its
 * upper bound cannot make a timer fire early after integer wraparound.
 *
 * Callback contract: return MY_RET_OK to reschedule (periodic), any
 * other value to remove the timer. Removing a timer from inside its own
 * callback is safe. An interval of zero is rejected to prevent a busy loop.
 * Destroying the manager from a callback is safe: destruction is deferred
 * until the outermost fire unwinds, and no further timers run in that fire.
 * While a callback runs, its entry is held in an inline current slot; timers
 * added by callbacks enter pending and are committed at the outermost fire
 * boundary, avoiding per-fire deferred allocation.
 */
#ifndef MY_TIMER_H
#define MY_TIMER_H

#include "myc/my_error.h"
#include "myc/my_emitter.h"
#include "myc/my_mem.h"

/** @brief Monotonic clock source, milliseconds. */
typedef uint64_t (*my_timer_now_fn_t)(void* ctx);

/**
 * @brief Timer callback. Return MY_RET_OK to repeat, anything else to
 * be removed after this fire.
 */
typedef my_ret_t (*my_timer_callback_t)(void* ctx);

/** @brief Opaque timer manager. */
typedef struct my_timer_manager_t my_timer_manager_t;

/** @brief Create a manager (NULL allocator = default). */
my_timer_manager_t* my_timer_manager_create(const my_allocator_t* allocator,
                                            my_timer_now_fn_t now_fn,
                                            void* now_ctx);

void my_timer_manager_destroy(my_timer_manager_t* mgr);

/**
 * @brief Add a timer firing every interval_ms (first fire after
 * interval_ms). interval_ms must be non-zero. @return timer id (> 0), 0 on
 * failure.
 */
uint32_t my_timer_add(my_timer_manager_t* mgr, my_timer_callback_t callback,
                      void* ctx, uint32_t interval_ms);

/**
 * @brief Add a timer guarded by an invalidatable callback context lease.
 *
 * The timer retains the lease until removal. Invalidating the lease skips a
 * callback that has not started; a callback already admitted may finish.
 */
uint32_t my_timer_add_lease(my_timer_manager_t* mgr,
                            my_timer_callback_t callback,
                            my_emitter_context_lease_t* lease,
                            uint32_t interval_ms);

/** @brief Remove a timer. MY_RET_NOT_FOUND when the id is unknown. */
my_ret_t my_timer_remove(my_timer_manager_t* mgr, uint32_t id);

/**
 * @brief Milliseconds until the next timer is due, or UINT32_MAX when no
 * timers are pending or the wait exceeds UINT32_MAX. Used by main loops to
 * compute wait timeouts. Inactive or invalidated lease roots are discarded
 * before the result is computed, so an invalidated timer cannot cause a
 * transient zero-timeout busy loop. The manager keeps a deadline min-heap,
 * so this is O(1) after inactive roots are discarded.
 */
uint32_t my_timer_manager_due_in_ms(my_timer_manager_t* mgr);

/**
 * @brief Fire all timers that are due now. Periodic timers whose callback
 * returns MY_RET_OK are rescheduled. @return number of timers fired.
 */
uint32_t my_timer_manager_fire(my_timer_manager_t* mgr);

#endif /* MY_TIMER_H */
