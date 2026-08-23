/**
 * @file my_button.h
 * @brief Minimal push button widget.
 *
 * States: normal / hover / pressed / disabled (four color fields).
 * Emits "click" (via my_widget_on) when released inside after a press.
 * Text rendering is a placeholder until the font system (M3b+).
 */
#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include "myui/my_widget.h"

typedef struct my_pal_main_loop_t my_pal_main_loop_t;

/** @brief Push button (IS-A widget). */
typedef struct my_button_t {
  my_widget_t base;
  char* text;                 /**< owned copy */
  bool pressed;               /**< pointer is down inside */
  uint64_t down_ms;           /**< press time (min display, M16) */
  uint32_t release_timer;     /**< pending delayed release (0 = none) */
  uint32_t cooldown_ms;       /**< configured cooldown after a click */
  uint32_t cooldown_active_ms; /**< duration of the current cooldown */
  uint64_t cooldown_until_ms; /**< monotonic deadline, 0 = inactive */
  uint32_t cooldown_timer;    /**< animation timer (0 = none) */
  my_pal_main_loop_t* cooldown_loop; /**< weak loop while timer is active */
  /* hover comes from the base widget (dispatcher-maintained, M14a);
   * fallback state colors are literals in button_state_color (M24b) */
} my_button_t;

/** @brief Create a button (NULL allocator = default, NULL text allowed). */
my_widget_t* my_button_create(const my_allocator_t* allocator, const char* text);

/** @brief Replace the button text (owned copy). */
my_ret_t my_button_set_text(my_widget_t* button, const char* text);

/** @brief Set the cooldown applied after the next successful click. */
my_ret_t my_button_set_cooldown(my_widget_t* button, uint32_t duration_ms);

/** @brief Return whether the monotonic cooldown deadline is still active. */
bool my_button_is_cooling_down(const my_widget_t* button);

/** @brief Return the saturated cooldown time remaining in milliseconds. */
uint32_t my_button_cooldown_remaining_ms(const my_widget_t* button);

/** @brief Return cooldown progress in [0, 1] (1 at start, 0 when done). */
float my_button_cooldown_progress(const my_widget_t* button);

#endif /* MY_BUTTON_H */
