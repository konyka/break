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

/** @brief Push button (IS-A widget). */
typedef struct my_button_t {
  my_widget_t base;
  char* text;                 /**< owned copy */
  bool pressed;               /**< pointer is down inside */
  uint64_t down_ms;           /**< press time (min display, M16) */
  uint32_t release_timer;     /**< pending delayed release (0 = none) */
  /* hover comes from the base widget (dispatcher-maintained, M14a);
   * fallback state colors are literals in button_state_color (M24b) */
} my_button_t;

/** @brief Create a button (NULL allocator = default, NULL text allowed). */
my_widget_t* my_button_create(const my_allocator_t* allocator, const char* text);

/** @brief Replace the button text (owned copy). */
my_ret_t my_button_set_text(my_widget_t* button, const char* text);

#endif /* MY_BUTTON_H */
