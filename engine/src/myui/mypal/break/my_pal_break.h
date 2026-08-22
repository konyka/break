/**
 * @file my_pal_break.h
 * @brief Break Platform adapter for myui's PAL interface.
 *
 * This port does not own the OS window or RHI device; it wraps an existing
 * break Platform and pumps input/timers manually from the BreakUI bridge.
 */
#ifndef MY_PAL_BREAK_H
#define MY_PAL_BREAK_H

#include "mypal/my_pal.h"
#include "platform/platform.h"
#include "rhi/rhi.h"

my_pal_t *my_pal_break_create(const my_allocator_t *allocator, Platform *platform,
                              RHIDevice *device);

/** @brief Fire due timers on a Break PAL main loop. */
uint32_t my_pal_break_fire_timers(my_pal_main_loop_t *loop);

/** @brief Dispatch copied posted events and fire due timers. */
uint32_t my_pal_break_pump(my_pal_main_loop_t *loop);

#endif /* MY_PAL_BREAK_H */
