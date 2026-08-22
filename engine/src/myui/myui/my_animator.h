/**
 * @file my_animator.h
 * @brief Property animations for widgets, driven by a main-loop timer.
 *
 * One manager per app (created by my_window_manager). Animations tick at
 * ~60fps via a 16ms loop timer that exists only while animations are
 * active. A widget's animations are cancelled automatically when its
 * subtree leaves the tree or its window is destroyed.
 *
 * repeat_count semantics: number of EXTRA plays after the first
 * (0 = play once, -1 = forever). yoyo reverses every other cycle.
 */
#ifndef MY_ANIMATOR_H
#define MY_ANIMATOR_H

#include "mypal/my_pal.h"
#include "myui/my_widget.h"

/** @brief Easing function: t in [0,1] -> eased [0,1]. */
typedef float (*my_easing_fn_t)(float t);

float my_easing_linear(float t);
float my_easing_ease_in(float t);
float my_easing_ease_out(float t);
float my_easing_ease_in_out(float t);

/** @brief Called each tick after the value was applied. */
typedef void (*my_anim_update_cb_t)(my_widget_t* widget, void* ctx);
/** @brief Called once when the animation completes (not on stop). */
typedef void (*my_anim_done_cb_t)(my_widget_t* widget, void* ctx);

/** @brief Animation manager (opaque). */
typedef struct my_animator_manager_t my_animator_manager_t;

/** @brief Create a manager bound to a main loop (both borrowed). */
my_animator_manager_t* my_animator_manager_create(const my_allocator_t* allocator,
                                                  my_pal_t* pal,
                                                  my_pal_main_loop_t* loop);

/** @brief Destroy the manager (cancels all animations and the timer). */
void my_animator_manager_destroy(my_animator_manager_t* mgr);

/**
 * @brief Animate a numeric widget property.
 * @param prop "x", "y", "w", "h" (uses to_x) or "xy" (uses both).
 * @return animation id (> 0), 0 on failure.
 */
uint32_t my_animator_animate(my_animator_manager_t* mgr, my_widget_t* widget,
                             const char* prop, float to_x, float to_y,
                             uint32_t duration_ms, uint32_t delay_ms,
                             my_easing_fn_t easing, int repeat_count, bool yoyo,
                             my_anim_update_cb_t on_update,
                             my_anim_done_cb_t on_done, void* ctx);

/** @brief Convenience: move a widget over time (manager found via root). */
uint32_t my_animator_move_to(my_widget_t* widget, int32_t x, int32_t y,
                             uint32_t duration_ms, my_easing_fn_t easing);

/** @brief Cancel one animation (no on_done). */
void my_animator_stop(my_animator_manager_t* mgr, uint32_t anim_id);

/** @brief Cancel all animations of a widget and its descendants. */
void my_animator_stop_widget(my_animator_manager_t* mgr, my_widget_t* widget);

/** @brief Number of active animations. */
size_t my_animator_manager_active_count(my_animator_manager_t* mgr);

#endif /* MY_ANIMATOR_H */
