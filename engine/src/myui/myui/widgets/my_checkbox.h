/**
 * @file my_checkbox.h
 * @brief Checkbox widget: two states + a display-only mixed state.
 *
 * Clicking toggles checked/unchecked (mixed is only settable via API or
 * binding, and clears on toggle). Emits "changed" on toggle; the "value"
 * property is bindable (bool).
 */
#ifndef MY_CHECKBOX_H
#define MY_CHECKBOX_H

#include "myui/my_widget.h"

/** @brief Checkbox (IS-A widget). */
typedef struct my_checkbox_t {
  my_widget_t base;
  const my_allocator_t* allocator;
  char* text;      /**< owned label text, may be NULL */
  bool checked;
  bool mixed;      /**< indeterminate display; cleared by any toggle */
  bool pressed;
} my_checkbox_t;

my_widget_t* my_checkbox_create(const my_allocator_t* allocator,
                                const char* text);
/** @brief Replace the label text (owned copy; NULL clears). */
my_ret_t my_checkbox_set_text(my_widget_t* checkbox, const char* text);
my_ret_t my_checkbox_set_checked(my_widget_t* checkbox, bool checked);
bool my_checkbox_get_checked(my_widget_t* checkbox);
my_ret_t my_checkbox_set_mixed(my_widget_t* checkbox, bool mixed);

#endif /* MY_CHECKBOX_H */
