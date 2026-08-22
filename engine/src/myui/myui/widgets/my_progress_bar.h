/**
 * @file my_progress_bar.h
 * @brief Progress bar widget (display only, binding-friendly).
 */
#ifndef MY_PROGRESS_BAR_H
#define MY_PROGRESS_BAR_H

#include "myui/my_widget.h"

/** @brief Progress bar (IS-A widget), value in [0, 100]. */
typedef struct my_progress_bar_t {
  my_widget_t base;
  float value;
} my_progress_bar_t;

my_widget_t* my_progress_bar_create(const my_allocator_t* allocator);
my_ret_t my_progress_bar_set_value(my_widget_t* bar, float value);
float my_progress_bar_get_value(my_widget_t* bar);

#endif /* MY_PROGRESS_BAR_H */
