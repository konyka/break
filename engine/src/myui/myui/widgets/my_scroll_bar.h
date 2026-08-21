/**
 * @file my_scroll_bar.h
 * @brief Vertical scroll bar widget.
 *
 * value = scroll fraction [0,1]; page_size = visible fraction [0,1]
 * (drives thumb length, min 16px so it stays grabbable). Drag the thumb
 * (grab semantics), click the track to page. Emits "changed" (read the
 * value back via my_scroll_bar_get_value). Scroll containers link with
 * my_list_view_set_scroll_bar() / my_text_area_set_scroll_bar().
 */
#ifndef MY_SCROLL_BAR_H
#define MY_SCROLL_BAR_H

#include "myui/my_widget.h"

#define MY_SCROLL_BAR_MIN_THUMB 16

/** @brief Vertical scroll bar (IS-A widget). */
typedef struct my_scroll_bar_t {
  my_widget_t base;
  float value;      /**< [0,1] scroll fraction */
  float page_size;  /**< [0,1] visible fraction */
  bool dragging;
  int32_t drag_off; /**< grab offset inside the thumb (px) */
} my_scroll_bar_t;

my_widget_t* my_scroll_bar_create(const my_allocator_t* allocator);
my_ret_t my_scroll_bar_set_value(my_widget_t* bar, float value);
float my_scroll_bar_get_value(my_widget_t* bar);
my_ret_t my_scroll_bar_set_page_size(my_widget_t* bar, float page_size);
float my_scroll_bar_get_page_size(my_widget_t* bar);

#endif /* MY_SCROLL_BAR_H */
