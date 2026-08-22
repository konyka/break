/**
 * @file my_timer.h
 * @brief PAL timers: a small manager driven by the main loop.
 *
 * The manager never reads a clock itself; the injectable now-function
 * keeps tests deterministic (dummy port injects a fake clock).
 *
 * Callback contract: return MY_RET_OK to reschedule (periodic), any
 * other value to remove the timer. Removing a timer from inside its own
 * callback is safe.
 */
#ifndef MY_TIMER_H
#define MY_TIMER_H

#include "myc/my_error.h"
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
 * interval_ms). @return timer id (> 0), 0 on failure.
 */
uint32_t my_timer_add(my_timer_manager_t* mgr, my_timer_callback_t callback,
                      void* ctx, uint32_t interval_ms);

/** @brief Remove a timer. MY_RET_NOT_FOUND when the id is unknown. */
my_ret_t my_timer_remove(my_timer_manager_t* mgr, uint32_t id);

/**
 * @brief Milliseconds until the next timer is due, or UINT32_MAX when no
 * timers are pending. Used by main loops to compute wait timeouts.
 */
uint32_t my_timer_manager_due_in_ms(my_timer_manager_t* mgr);

/**
 * @brief Fire all timers that are due now. Periodic timers whose callback
 * returns MY_RET_OK are rescheduled. @return number of timers fired.
 */
uint32_t my_timer_manager_fire(my_timer_manager_t* mgr);

#endif /* MY_TIMER_H */
