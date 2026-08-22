/**
 * @file my_pal_dummy.h
 * @brief Dummy PAL port: headless, deterministic, used by all unit tests.
 *
 * Windows wrap my_lcd_mem (BGRA8888); the main loop is a manual queue
 * (my_pal_main_loop_pump_n) with an injectable clock so timer tests are
 * deterministic. run() processes until starved or quit.
 */
#ifndef MY_PAL_DUMMY_H
#define MY_PAL_DUMMY_H

#include "mypal/my_pal.h"

/** @brief Create the dummy platform. */
my_pal_t* my_pal_dummy_create(const my_allocator_t* allocator);

/** @brief Test hook: set the dummy platform's monotonic clock. */
void my_pal_dummy_set_now_ms(my_pal_t* pal, uint64_t now_ms);

/** @brief Test hook (M12c): inject a display scale factor (default 1).
 * Takes effect for windows created/resized afterwards. */
void my_pal_dummy_set_scale_factor(my_pal_t* pal, float scale);

/** @brief Test hook (M13a): last IME spot reported to this window. */
void my_pal_dummy_get_ime_spot(my_pal_window_t* win, int32_t* x,
                               int32_t* y);

/** @brief Test hook: whether text input is enabled for this window. */
bool my_pal_dummy_get_ime_enabled(my_pal_window_t* win);

/** @brief Test hook: last UTF-8 editor context reported to this window. */
void my_pal_dummy_get_ime_surrounding(my_pal_window_t* win, char* utf8,
                                      size_t size, int32_t* cursor,
                                      int32_t* anchor);

/** @brief Test hook (M13c): deliver an event through the pal's
 * registered handler (exercises the window manager's routing). */
void my_pal_dummy_inject_event(my_pal_t* pal, my_pal_window_t* win,
                               const my_event_t* event);

/**
 * @brief Test hook (dummy loops only): dispatch up to n queued events,
 * FIFO. @return number of events dispatched (0 when queue is empty or
 * loop is not a dummy loop).
 */
uint32_t my_pal_main_loop_pump_n(my_pal_main_loop_t* loop, uint32_t n);

/** @brief Test hook (M16): pretend the compositor gives no SSD, so
 * windows are created with client-side decoration. Default false. */
void my_pal_dummy_set_needs_csd(my_pal_t* pal, bool needs);

/** @brief Test hook (M16): how often begin_move was requested. */
uint32_t my_pal_dummy_begin_move_count(my_pal_window_t* win);

/** @brief Test hook (M21a): the window's current cursor shape. */
my_cursor_t my_pal_dummy_get_cursor(my_pal_window_t* win);

#endif /* MY_PAL_DUMMY_H */
