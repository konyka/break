/**
 * @file my_slider.h
 * @brief Horizontal slider widget.
 *
 * value in [min, max] (float), optional step snapping (0 = continuous).
 * Drag the knob (grab-based) or click the track to jump. Emits
 * "changed" when the value changes; "value"/"min"/"max" are bindable.
 */
#ifndef MY_SLIDER_H
#define MY_SLIDER_H

#include "myui/my_widget.h"

/** @brief Horizontal slider (IS-A widget). */
typedef struct my_slider_t {
  my_widget_t base;
  float value;
  float min;
  float max;
  float step;     /**< 0 = continuous */
  bool dragging;
} my_slider_t;

my_widget_t* my_slider_create(const my_allocator_t* allocator);
my_ret_t my_slider_set_value(my_widget_t* slider, float value);
float my_slider_get_value(my_widget_t* slider);
my_ret_t my_slider_set_range(my_widget_t* slider, float min, float max);
my_ret_t my_slider_set_step(my_widget_t* slider, float step);

#endif /* MY_SLIDER_H */
