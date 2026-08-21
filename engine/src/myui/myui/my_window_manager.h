/**
 * @file my_window_manager.h
 * @brief Window stack manager + application entry point.
 *
 * The manager registers itself as the PAL event handler and routes
 * events to the window owning the source PAL window. Windows form a
 * stack (later = on top); closing the last window quits the main loop
 * (observable via quit_requested).
 */
#ifndef MY_WINDOW_MANAGER_H
#define MY_WINDOW_MANAGER_H

#include "myui/my_animator.h"
#include "myui/my_window.h"

struct my_window_manager_t;

/**
 * @brief Open hook: called once per my_window_manager_open AFTER the
 * window is on the stack, shown and invalidated (BreakUI installs it to
 * inject the shared RHI vgcanvas + font and to center modal dialogs
 * over the window below when the port cannot move windows).
 */
typedef void (*my_window_on_open_t)(struct my_window_manager_t* wm,
                                    my_window_t* win, void* ctx);

/** @brief Window stack manager. */
typedef struct my_window_manager_t {
  const my_allocator_t* allocator;
  my_pal_t* pal;            /**< borrowed */
  my_pal_main_loop_t* loop; /**< borrowed */
  my_darray_t* windows;     /**< stack of owned refs (my_window_t*) */
  my_animator_manager_t* anim_mgr; /**< owned: drives widget animations */
  uint32_t paint_timer_id;  /**< periodic dirty-window repaint tick */
  bool auto_paint;          /**< false: Break drives painting (no tick) */
  my_window_on_open_t on_open; /**< BreakUI injection hook */
  void* on_open_ctx;
  my_window_t* surface_pointer_grab; /**< weak shared-surface capture */
  my_window_t* surface_focus_window; /**< weak shared-surface key/IME target */
  uint64_t windows_epoch;      /**< increments when the stack changes */
  bool quit_requested;      /**< set when the last window was closed */
} my_window_manager_t;

/** @brief Create a manager; registers the PAL event handler. */
my_window_manager_t* my_window_manager_create(const my_allocator_t* allocator,
                                              my_pal_t* pal,
                                              my_pal_main_loop_t* loop);

/**
 * @brief Push a window (takes one manager ref), show it, invalidate fully.
 *
 * The caller retains and must release its creator ref independently. This is
 * based on my_window_t, not my_window_widget(), because the latter is a
 * borrowed content accessor in CSD mode.
 */
my_ret_t my_window_manager_open(my_window_manager_t* wm, my_window_t* win);

/**
 * @brief Close (remove + unref) a window. Closing the last one calls
 * main_loop quit and sets quit_requested.
 */
my_ret_t my_window_manager_close(my_window_manager_t* wm, my_window_t* win);

/** @brief Top window of the stack (borrowed), NULL when empty. */
my_window_t* my_window_manager_top(my_window_manager_t* wm);
void my_window_manager_set_on_open(my_window_manager_t* wm,
                                   my_window_on_open_t cb, void* ctx);

/**
 * @brief Toggle the manager's ~33ms repaint tick (default on). BreakUI
 * drives painting from its own frame loop (break_ui_render iterates the
 * window stack), so it disables the tick to avoid double paints.
 */
void my_window_manager_set_auto_paint(my_window_manager_t* wm, bool on);

/**
 * @brief Route one PAL event through the manager's modal-window rules.
 *
 * Break's Platform pump owns the OS event loop, so the BreakUI bridge calls
 * this directly instead of relying on the PAL event handler callback.
 */
my_ret_t my_window_manager_on_pal_event(my_window_manager_t* wm,
                                        my_pal_window_t* pal_window,
                                        const my_event_t* event);

/** @brief Route an event originating from one shared physical surface. */
my_ret_t my_window_manager_dispatch_surface_event(
    my_window_manager_t* wm, const my_event_t* event);

/** @brief Resize the shared surface root and recenter logical dialogs. */
my_ret_t my_window_manager_resize_surface(my_window_manager_t* wm,
                                          int32_t width, int32_t height);

/** @brief Refresh the content scale of every logical window in the stack.
 * Returns true if any canvas was reconfigured and invalidated. */
bool my_window_manager_refresh_scales(my_window_manager_t* wm);

/** @brief Close all windows above the bottom one. */
my_ret_t my_window_manager_back_to_home(my_window_manager_t* wm);

/** @brief Number of open windows. */
size_t my_window_manager_count(my_window_manager_t* wm);

/** @brief Snapshot the stack with one strong ref per returned window. */
my_ret_t my_window_manager_snapshot_windows(my_window_manager_t* wm,
                                            my_window_t***out_windows,
                                            size_t* out_count);

/** @brief Release a snapshot returned by my_window_manager_snapshot_windows. */
void my_window_manager_release_snapshot(my_window_manager_t* wm,
                                        my_window_t** windows, size_t count);

/** @brief Current window-stack mutation epoch. */
uint64_t my_window_manager_windows_epoch(const my_window_manager_t* wm);

/** @brief Close all windows and unregister the PAL handler. */
void my_window_manager_destroy(my_window_manager_t* wm);

/** @brief Factory for the app's first window (my_app_run). */
typedef my_window_t* (*my_app_window_factory_t)(my_pal_t* pal, void* ctx);

/**
 * @brief Convenience entry: create main loop + window manager, build the
 * first window via factory, open it, run the loop, clean up.
 */
my_ret_t my_app_run(my_pal_t* pal, my_app_window_factory_t factory, void* ctx);

#endif /* MY_WINDOW_MANAGER_H */
