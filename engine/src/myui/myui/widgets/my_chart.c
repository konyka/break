/**
 * @file my_chart.c
 * @brief ECharts-inspired native line/bar chart widget.
 */
#include "myui/widgets/my_chart.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "mypal/my_event.h"
#include "myr/my_color.h"
#include "myr/my_vgcanvas.h"
#include "myui/my_window.h"

#define CHART_PAD_LEFT 42.0f
#define CHART_PAD_RIGHT 12.0f
#define CHART_PAD_TOP 30.0f
#define CHART_PAD_BOTTOM 26.0f
#define CHART_GRID_LINES 5u
#define CHART_DEFAULT_MIN 0.0f
#define CHART_DEFAULT_MAX 100.0f
#define CHART_HOVER_NONE SIZE_MAX

static const uint32_t s_colors[MY_CHART_MAX_SERIES] = {
    0xE85D75FFu, 0x3A86FFFF, 0xF4A261FFu, 0x2A9D8FFF};

static my_chart_t* chart_cast(my_widget_t* widget) {
  return my_chart_is_instance(widget) ? (my_chart_t*)widget : NULL;
}

static const my_chart_t* chart_const_cast(const my_widget_t* widget) {
  return my_chart_is_instance(widget) ? (const my_chart_t*)widget : NULL;
}

static bool chart_plot_rect(const my_widget_t* widget, float* x, float* y,
                            float* w, float* h) {
  if (widget == NULL || x == NULL || y == NULL || w == NULL || h == NULL) {
    return false;
  }
  *x = CHART_PAD_LEFT;
  *y = CHART_PAD_TOP;
  *w = (float)widget->rect.w - CHART_PAD_LEFT - CHART_PAD_RIGHT;
  *h = (float)widget->rect.h - CHART_PAD_TOP - CHART_PAD_BOTTOM;
  return *w > 0.0f && *h > 0.0f;
}

static void chart_range(const my_chart_t* chart, float* y_min, float* y_max) {
  size_t i;
  float lo = 0.0f;
  float hi = 1.0f;
  bool found = false;
  if (chart->range_set) {
    *y_min = chart->y_min;
    *y_max = chart->y_max;
    return;
  }
  for (i = 0; i < chart->series_count; i++) {
    size_t j;
    const my_chart_series_t* series = &chart->series[i];
    for (j = 0; j < series->count; j++) {
      float value = series->values[j];
      if (!isfinite(value)) continue;
      if (!found || value < lo) lo = value;
      if (!found || value > hi) hi = value;
      found = true;
    }
  }
  if (!found) {
    lo = CHART_DEFAULT_MIN;
    hi = CHART_DEFAULT_MAX;
  } else if (lo == hi) {
    lo -= 1.0f;
    hi += 1.0f;
  }
  *y_min = lo;
  *y_max = hi;
}

float my_chart_value_to_y(float value, float y_min, float y_max,
                          float plot_top, float plot_height) {
  float span;
  if (!isfinite(value) || !isfinite(y_min) || !isfinite(y_max) ||
      !isfinite(plot_top) || !isfinite(plot_height) || y_max <= y_min ||
      plot_height < 0.0f) {
    return plot_top;
  }
  if (value < y_min) value = y_min;
  if (value > y_max) value = y_max;
  span = y_max - y_min;
  return plot_top + plot_height * (1.0f - (value - y_min) / span);
}

static void chart_grid(my_widget_t* widget, my_vgcanvas_t* vg, float x, float y,
                       float w, float h, float y_min, float y_max) {
  size_t i;
  char text[24];
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(0xE6EAF0FFu));
  my_vgcanvas_set_line_width(vg, 1.0f);
  for (i = 0; i < CHART_GRID_LINES; i++) {
    float ratio = (float)i / (float)(CHART_GRID_LINES - 1u);
    float line_y = y + h * ratio;
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, x, line_y);
    my_vgcanvas_line_to(vg, x + w, line_y);
    my_vgcanvas_stroke(vg);
    snprintf(text, sizeof(text), "%.0f", (double)(y_max - (y_max - y_min) * ratio));
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x7B8794FFu));
    my_vgcanvas_draw_text(vg, text, 5.0f, line_y - 5.0f);
  }
  (void)widget;
}

static void chart_draw_line_series(const my_chart_t* chart, my_vgcanvas_t* vg,
                                   const my_chart_series_t* series, float x,
                                   float y, float w, float h, float y_min,
                                   float y_max) {
  size_t i;
  (void)chart;
  if (series->values == NULL || series->count == 0u) return;
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(series->color));
  my_vgcanvas_set_line_width(vg, 2.0f);
  my_vgcanvas_begin_path(vg);
  for (i = 0; i < series->count; i++) {
    float px = x + (series->count > 1u ? w * (float)i / (float)(series->count - 1u)
                                       : w * 0.5f);
    float py = my_chart_value_to_y(series->values[i], y_min, y_max, y, h);
    if (i == 0u) my_vgcanvas_move_to(vg, px, py);
    else my_vgcanvas_line_to(vg, px, py);
  }
  my_vgcanvas_stroke(vg);
}

static void chart_draw_bars(const my_chart_t* chart, my_vgcanvas_t* vg, float x,
                            float y, float w, float h, float y_min, float y_max) {
  const my_chart_series_t* series;
  size_t i;
  float zero_y;
  if (chart->series_count == 0u) return;
  series = &chart->series[0];
  if (series->values == NULL || series->count == 0u) return;
  zero_y = my_chart_value_to_y(0.0f, y_min, y_max, y, h);
  for (i = 0; i < series->count; i++) {
    float slot = w / (float)series->count;
    float bar_w = slot * 0.68f;
    float bar_x = x + slot * (float)i + (slot - bar_w) * 0.5f;
    float value_y = my_chart_value_to_y(series->values[i], y_min, y_max, y, h);
    float top = value_y < zero_y ? value_y : zero_y;
    float height = fabsf(value_y - zero_y);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(series->color));
    my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){bar_x, top, bar_w, height},
                                  3.0f);
  }
}

static void chart_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_chart_t* chart = (my_chart_t*)widget;
  float x, y, w, h, y_min, y_max;
  size_t i;
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xFFFFFFFFu));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                  (float)widget->rect.h},
                                8.0f);
  my_vgcanvas_set_font(vg, NULL, 13);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x1F2933FFu));
  if (chart->title[0] != '\0') my_vgcanvas_draw_text(vg, chart->title, 12, 8);
  if (!chart_plot_rect(widget, &x, &y, &w, &h)) return;
  chart_range(chart, &y_min, &y_max);
  chart_grid(widget, vg, x, y, w, h, y_min, y_max);
  if (chart->labels != NULL && chart->label_count > 0u) {
    size_t label_count = chart->label_count;
    size_t label_index;
    my_vgcanvas_set_font(vg, NULL, 10);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x7B8794FFu));
    for (label_index = 0; label_index < label_count; label_index++) {
      float label_x = x + (label_count > 1u
                                ? w * (float)label_index / (float)(label_count - 1u)
                                : w * 0.5f);
      my_vgcanvas_draw_text(vg, chart->labels[label_index] != NULL
                                   ? chart->labels[label_index]
                                   : "",
                            label_x - 12.0f, y + h + 6.0f);
    }
  }
  if (chart->mode == MY_CHART_BAR) {
    chart_draw_bars(chart, vg, x, y, w, h, y_min, y_max);
  } else {
    for (i = 0; i < chart->series_count; i++) {
      chart_draw_line_series(chart, vg, &chart->series[i], x, y, w, h, y_min,
                             y_max);
    }
  }
  if (chart->hover_index != CHART_HOVER_NONE && chart->series_count > 0u &&
      chart->series[0].count > 0u) {
    char tooltip[64];
    float hover_x = x + (chart->series[0].count > 1u
                             ? w * (float)chart->hover_index /
                                   (float)(chart->series[0].count - 1u)
                             : w * 0.5f);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x1F2933CCu));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){hover_x, y, 1.0f, h});
    if (my_chart_get_tooltip(widget, tooltip, sizeof(tooltip)) == MY_RET_OK) {
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x1F2933FFu));
      my_vgcanvas_fill_rounded_rect(vg,
                                    &(my_rectf_t){hover_x + 6.0f, y + 6.0f,
                                                  96.0f, 22.0f},
                                    4.0f);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xFFFFFFFFu));
      my_vgcanvas_set_font(vg, NULL, 10);
      my_vgcanvas_draw_text(vg, tooltip, hover_x + 10.0f, y + 11.0f);
    }
  }
  if (chart->show_legend) {
    float legend_x = x;
    my_vgcanvas_set_font(vg, NULL, 10);
    for (i = 0; i < chart->series_count; i++) {
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(chart->series[i].color));
      my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){legend_x, 15, 7, 7}, 2);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x52606DFFu));
      my_vgcanvas_draw_text(vg, chart->series[i].name != NULL ? chart->series[i].name : "",
                            legend_x + 11, 12);
      legend_x += 70.0f;
    }
  }
}

static my_ret_t chart_on_event(my_widget_t* widget, const my_event_t* event) {
  my_chart_t* chart = (my_chart_t*)widget;
  float x, y, w, h;
  int32_t local_x, local_y;
  size_t index;
  if (event == NULL || event->type != MY_EVENT_POINTER_MOVE ||
      !chart_plot_rect(widget, &x, &y, &w, &h) || chart->series_count == 0u) {
    return MY_RET_NOT_SUPPORTED;
  }
  local_x = event->u.pointer.x;
  local_y = event->u.pointer.y;
  my_widget_global_to_local(widget, &local_x, &local_y);
  if ((float)local_x < x || (float)local_x > x + w || (float)local_y < y ||
      (float)local_y > y + h || chart->series[0].count == 0u) {
    chart->hover_index = CHART_HOVER_NONE;
    return MY_RET_NOT_SUPPORTED;
  }
  index = chart->series[0].count > 1u
              ? (size_t)lroundf(((float)local_x - x) / w *
                                (float)(chart->series[0].count - 1u))
              : 0u;
  if (index >= chart->series[0].count) index = chart->series[0].count - 1u;
  if (chart->hover_index != index) {
    chart->hover_index = index;
    my_widget_invalidate(widget, NULL);
  }
  return MY_RET_OK;
}

static const my_widget_vtable_t s_chart_vtable = {chart_on_paint, chart_on_event,
                                                   NULL, NULL};

my_widget_t* my_chart_create(const my_allocator_t* allocator, my_chart_mode_t mode) {
  my_chart_t* chart;
  if (mode != MY_CHART_LINE && mode != MY_CHART_BAR) return NULL;
  chart = (my_chart_t*)my_mem_calloc(allocator, 1, sizeof(*chart));
  if (chart == NULL) return NULL;
  if (my_widget_init((my_widget_t*)chart, allocator, &s_chart_vtable, "chart") !=
      MY_RET_OK) {
    my_mem_free(allocator, chart);
    return NULL;
  }
  chart->mode = mode;
  chart->hover_index = CHART_HOVER_NONE;
  chart->show_legend = true;
  chart->base.widget_type = "chart";
  return (my_widget_t*)chart;
}

bool my_chart_is_instance(const my_widget_t* widget) {
  return widget != NULL && widget->vtable == &s_chart_vtable;
}

my_ret_t my_chart_set_title(my_widget_t* widget, const char* title) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  snprintf(chart->title, sizeof(chart->title), "%s", title != NULL ? title : "");
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_set_labels(my_widget_t* widget, const char* const* labels,
                             size_t count) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || (count > 0u && labels == NULL)) return MY_RET_INVALID_PARAMS;
  chart->labels = labels;
  chart->label_count = count;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_set_series(my_widget_t* widget, size_t index,
                             const my_chart_series_t* series) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || series == NULL || index >= MY_CHART_MAX_SERIES ||
      (series->count > 0u && series->values == NULL)) return MY_RET_INVALID_PARAMS;
  chart->series[index] = *series;
  if (chart->series[index].color == 0u) chart->series[index].color = s_colors[index];
  if (index >= chart->series_count) chart->series_count = index + 1u;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_clear_series(my_widget_t* widget) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  memset(chart->series, 0, sizeof(chart->series));
  chart->series_count = 0u;
  chart->hover_index = CHART_HOVER_NONE;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_set_range(my_widget_t* widget, float y_min, float y_max) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || !isfinite(y_min) || !isfinite(y_max) || y_max <= y_min)
    return MY_RET_INVALID_PARAMS;
  chart->y_min = y_min;
  chart->y_max = y_max;
  chart->range_set = true;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_set_legend_visible(my_widget_t* widget, bool visible) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  chart->show_legend = visible;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

size_t my_chart_get_hover_index(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL ? chart->hover_index : CHART_HOVER_NONE;
}

my_ret_t my_chart_get_tooltip(const my_widget_t* widget, char* buffer,
                              size_t capacity) {
  const my_chart_t* chart = chart_const_cast(widget);
  const my_chart_series_t* series;
  if (chart == NULL || buffer == NULL || capacity == 0u) return MY_RET_INVALID_PARAMS;
  if (chart->hover_index == CHART_HOVER_NONE || chart->series_count == 0u)
    return MY_RET_NOT_SUPPORTED;
  series = &chart->series[0];
  if (series->values == NULL || chart->hover_index >= series->count) return MY_RET_NOT_SUPPORTED;
  snprintf(buffer, capacity, "%s: %.2f", series->name != NULL ? series->name : "Series",
           (double)series->values[chart->hover_index]);
  return MY_RET_OK;
}
