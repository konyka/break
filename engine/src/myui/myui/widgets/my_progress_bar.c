/**
 * @file my_progress_bar.c
 * @brief Progress bar widget.
 */
#include "myui/widgets/my_progress_bar.h"

static void progress_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_progress_bar_t* b = (my_progress_bar_t*)widget;
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                          0xE0E0E0FFu);
  uint32_t fg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_FG_COLOR,
                                          0x4CAF50FFu);
  float frac = b->value / 100.0f;
  float r = (float)widget->rect.h / 2.0f;

  if (frac < 0.0f) {
    frac = 0.0f;
  }
  if (frac > 1.0f) {
    frac = 1.0f;
  }
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                 (float)widget->rect.h},
                                r);
  if (frac > 0.0f) {
    my_vgcanvas_save(vg);
    my_vgcanvas_clip_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w * frac,
                                            (float)widget->rect.h});
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
    my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                   (float)widget->rect.h},
                                  r);
    my_vgcanvas_restore(vg);
  }
}

static const my_widget_vtable_t s_progress_vtable = {progress_on_paint, NULL,
                                                     NULL, NULL};

my_widget_t* my_progress_bar_create(const my_allocator_t* allocator) {
  my_progress_bar_t* b =
      (my_progress_bar_t*)my_mem_calloc(allocator, 1, sizeof(my_progress_bar_t));
  if (b == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)b, allocator, &s_progress_vtable,
                     "progress_bar") != MY_RET_OK) {
    my_mem_free(allocator, b);
    return NULL;
  }
  ((my_widget_t*)b)->enable = false; /* display only */
  ((my_widget_t*)b)->widget_type = "progress_bar";
  return (my_widget_t*)b;
}

my_ret_t my_progress_bar_set_value(my_widget_t* bar, float value) {
  my_progress_bar_t* b = (my_progress_bar_t*)bar;
  if (bar == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (value < 0.0f) {
    value = 0.0f;
  }
  if (value > 100.0f) {
    value = 100.0f;
  }
  if (b->value != value) {
    b->value = value;
    my_widget_invalidate(bar, NULL);
  }
  return MY_RET_OK;
}

float my_progress_bar_get_value(my_widget_t* bar) {
  return bar != NULL ? ((my_progress_bar_t*)bar)->value : 0.0f;
}
