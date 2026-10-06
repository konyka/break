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
#define CHART_GRID_LINES_MIN 2u
#define CHART_GRID_LINES_MAX 8u
#define CHART_DEFAULT_MIN 0.0f
#define CHART_DEFAULT_MAX 100.0f
#define CHART_HOVER_NONE SIZE_MAX
#define CHART_PI 3.14159265358979323846f

static const uint32_t s_colors[MY_CHART_MAX_SERIES] = {
    0xE85D75FFu, 0x3A86FFFF, 0xF4A261FFu, 0x2A9D8FFF};

my_ret_t my_chart_format_tick(float value, char* buffer, size_t capacity) {
  int written;
  if (!isfinite(value) || buffer == NULL || capacity == 0u) {
    return MY_RET_INVALID_PARAMS;
  }
  written = snprintf(buffer, capacity, "%.4f", (double)value);
  if (written < 0 || (size_t)written >= capacity) {
    buffer[capacity - 1u] = '\0';
    return MY_RET_FAIL;
  }
  while (written > 0 && buffer[written - 1] == '0') buffer[--written] = '\0';
  if (written > 0 && buffer[written - 1] == '.') buffer[--written] = '\0';
  return MY_RET_OK;
}

static void chart_hover_leave(void* ctx, const char* event, void* data) {
  my_chart_t* chart = (my_chart_t*)ctx;
  (void)event;
  (void)data;
  if (chart != NULL && chart->hover_index != CHART_HOVER_NONE) {
    chart->hover_index = CHART_HOVER_NONE;
    my_widget_invalidate((my_widget_t*)chart, NULL);
  }
}

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

static size_t chart_category_count(const my_chart_t* chart) {
  size_t count = 0u;
  size_t i;
  if (chart == NULL) return 0u;
  for (i = 0u; i < chart->series_count; i++) {
    if (!chart->series_visible[i]) continue;
    if (chart->series[i].count > count) count = chart->series[i].count;
  }
  return count;
}

/* Effective [begin, end) category window for dataZoom. Stale or invalid windows
 * (e.g. after series shrinking) fall back to the full range. */
static void chart_zoom_range(const my_chart_t* chart, size_t* begin,
                             size_t* count) {
  size_t total = chart_category_count(chart);
  size_t b = 0u;
  size_t e = total;
  if (chart->zoom_set && total > 0u) {
    b = chart->zoom_start;
    e = chart->zoom_end;
    if (b > total) b = total;
    if (e > total) e = total;
    if (e <= b) { b = 0u; e = total; }
  }
  *begin = b;
  *count = e - b;
}

static bool chart_category_in_window(size_t category, size_t begin,
                                     size_t count) {
  return category >= begin && category < begin + count;
}

static float chart_category_x(size_t category, size_t begin, size_t count,
                              float x, float w) {
  if (count <= 1u) return x + w * 0.5f;
  return x + w * (float)(category - begin) / (float)(count - 1u);
}

static float chart_animated_value(const my_chart_t* chart, float value) {
  return value * chart->animation_progress;
}

static uint32_t chart_visual_color(const my_chart_t* chart, float value,
                                   uint32_t fallback) {
  float t;
  uint8_t lr, lg, lb, la, hr, hg, hb, ha;
  if (!chart->visual_map_set || chart->visual_map_max <= chart->visual_map_min)
    return fallback;
  t = (value - chart->visual_map_min) /
      (chart->visual_map_max - chart->visual_map_min);
  if (t < 0.0f) t = 0.0f;
  if (t > 1.0f) t = 1.0f;
  lr = (uint8_t)(chart->visual_map_low_color >> 24);
  lg = (uint8_t)(chart->visual_map_low_color >> 16);
  lb = (uint8_t)(chart->visual_map_low_color >> 8);
  la = (uint8_t)chart->visual_map_low_color;
  hr = (uint8_t)(chart->visual_map_high_color >> 24);
  hg = (uint8_t)(chart->visual_map_high_color >> 16);
  hb = (uint8_t)(chart->visual_map_high_color >> 8);
  ha = (uint8_t)chart->visual_map_high_color;
  return ((uint32_t)(lr + (uint8_t)((hr - lr) * t)) << 24) |
         ((uint32_t)(lg + (uint8_t)((hg - lg) * t)) << 16) |
         ((uint32_t)(lb + (uint8_t)((hb - lb) * t)) << 8) |
         (uint32_t)(la + (uint8_t)((ha - la) * t));
}

static void chart_draw_visual_map(const my_chart_t* chart, my_vgcanvas_t* vg,
                                  float x, float y, float w) {
  const float map_w = 96.0f;
  char low[24], high[24];
  if (!chart->visual_map_set) return;
  (void)my_chart_format_tick(chart->visual_map_min, low, sizeof(low));
  (void)my_chart_format_tick(chart->visual_map_max, high, sizeof(high));
  for (unsigned i = 0u; i < 16u; i++) {
    float t0 = (float)i / 16.0f;
    float t1 = (float)(i + 1u) / 16.0f;
    float value = chart->visual_map_min +
                  (chart->visual_map_max - chart->visual_map_min) *
                      (t0 + t1) * 0.5f;
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(
        chart_visual_color(chart, value, chart->visual_map_low_color)));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){x + w - map_w + map_w * t0, y,
                                           map_w * (t1 - t0), 8.0f});
  }
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x52606DFFu));
  my_vgcanvas_set_font(vg, NULL, 9);
  my_vgcanvas_draw_text(vg, low, x + w - map_w, y + 19.0f);
  my_vgcanvas_draw_text(vg, high, x + w - 18.0f, y + 19.0f);
}

/* Stacked base for a value at `category_index`: the sum of same-sign visible
 * samples from lower series indices. Used by both hover markers and marks so
 * annotations land on the rendered segment instead of the raw value. */
static float chart_stacked_base(const my_chart_t* chart, size_t series_index,
                                size_t category_index, float value) {
  float base = 0.0f;
  size_t i;
  for (i = 0u; i < series_index; i++) {
    const my_chart_series_t* series = &chart->series[i];
    float sample;
    if (!chart->series_visible[i] || series->values == NULL ||
        category_index >= series->count)
      continue;
    sample = chart_animated_value(chart, series->values[category_index]);
    if ((value >= 0.0f) == (sample >= 0.0f)) base += sample;
  }
  return base;
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
  if (chart->stacked && chart->mode == MY_CHART_BAR) {
    size_t category_count = chart_category_count(chart);
    for (size_t category = 0u; category < category_count; category++) {
      float positive = 0.0f;
      float negative = 0.0f;
      for (i = 0u; i < chart->series_count; i++) {
        if (!chart->series_visible[i] || chart->series[i].values == NULL ||
            category >= chart->series[i].count) continue;
        if (chart->series[i].values[category] >= 0.0f)
          positive += chart->series[i].values[category];
        else
          negative += chart->series[i].values[category];
      }
      if (positive != 0.0f) {
        if (!found || positive > hi) hi = positive;
        found = true;
      }
      if (negative != 0.0f) {
        if (!found || negative < lo) lo = negative;
        found = true;
      }
    }
  } else for (i = 0; i < chart->series_count; i++) {
    size_t j;
    const my_chart_series_t* series = &chart->series[i];
    if (!chart->series_visible[i]) continue;
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

static unsigned chart_series_axis(const my_chart_t* chart, size_t index) {
  return chart->series[index].y_axis == 1u ? 1u : 0u;
}

static bool chart_has_secondary(const my_chart_t* chart) {
  for (size_t i = 0u; i < chart->series_count; i++) {
    if (chart_series_axis(chart, i) == 1u) return true;
  }
  return false;
}

/* Range for one axis (0=left, 1=right). Falls back to the shared/default range
 * when no series is bound to that axis. */
static void chart_axis_range(const my_chart_t* chart, unsigned axis,
                             float* y_min, float* y_max) {
  size_t i;
  float lo = 0.0f;
  float hi = 1.0f;
  bool found = false;
  if (axis == 1u) {
    if (chart->range2_set) {
      *y_min = chart->y2_min;
      *y_max = chart->y2_max;
      return;
    }
  } else if (chart->range_set) {
    *y_min = chart->y_min;
    *y_max = chart->y_max;
    return;
  }
  if (chart->stacked && chart->mode == MY_CHART_BAR) {
    size_t category_count = chart_category_count(chart);
    for (size_t category = 0u; category < category_count; category++) {
      float positive = 0.0f;
      float negative = 0.0f;
      for (i = 0u; i < chart->series_count; i++) {
        if (!chart->series_visible[i] || chart->series[i].values == NULL ||
            chart_series_axis(chart, i) != axis ||
            category >= chart->series[i].count)
          continue;
        if (chart->series[i].values[category] >= 0.0f)
          positive += chart->series[i].values[category];
        else
          negative += chart->series[i].values[category];
      }
      if (positive != 0.0f) {
        if (!found || positive > hi) hi = positive;
        found = true;
      }
      if (negative != 0.0f) {
        if (!found || negative < lo) lo = negative;
        found = true;
      }
    }
    if (found) {
      if (lo == hi) { lo -= 1.0f; hi += 1.0f; }
      *y_min = lo;
      *y_max = hi;
      return;
    }
  }
  for (i = 0u; i < chart->series_count; i++) {
    size_t j;
    const my_chart_series_t* series = &chart->series[i];
    if (!chart->series_visible[i] || chart_series_axis(chart, i) != axis)
      continue;
    for (j = 0u; j < series->count; j++) {
      float value = series->values != NULL ? series->values[j] : 0.0f;
      if (series->values == NULL || !isfinite(value)) break;
      if (!found || value < lo) lo = value;
      if (!found || value > hi) hi = value;
      found = true;
    }
  }
  if (!found) {
    if (axis == 1u) { *y_min = 0.0f; *y_max = 0.0f; return; }
    chart_range(chart, y_min, y_max);
    return;
  }
  if (lo == hi) { lo -= 1.0f; hi += 1.0f; }
  *y_min = lo;
  *y_max = hi;
}

float my_chart_value_to_y(float value, float y_min, float y_max,
                          float plot_top, float plot_height) {
  long double span;
  long double normalized;
  if (!isfinite(value) || !isfinite(y_min) || !isfinite(y_max) ||
      !isfinite(plot_top) || !isfinite(plot_height) || y_max <= y_min ||
      plot_height < 0.0f) {
    return plot_top;
  }
  if (value < y_min) value = y_min;
  if (value > y_max) value = y_max;
  span = (long double)y_max - (long double)y_min;
  normalized = ((long double)value - (long double)y_min) / span;
  return (float)((long double)plot_top +
                 (long double)plot_height * (1.0L - normalized));
}

float my_chart_stacked_value_to_y(float value, float base, float y_min,
                                  float y_max, float plot_top,
                                  float plot_height) {
  return my_chart_value_to_y(base + value, y_min, y_max, plot_top, plot_height);
}

my_ret_t my_chart_get_range(const my_widget_t* widget, float* y_min,
                            float* y_max) {
  const my_chart_t* chart = chart_const_cast(widget);
  if (chart == NULL || y_min == NULL || y_max == NULL)
    return MY_RET_INVALID_PARAMS;
  chart_range(chart, y_min, y_max);
  return MY_RET_OK;
}

my_ret_t my_chart_get_axis_range(const my_widget_t* widget, unsigned axis,
                                 float* y_min, float* y_max) {
  const my_chart_t* chart = chart_const_cast(widget);
  if (chart == NULL || axis > 1u || y_min == NULL || y_max == NULL)
    return MY_RET_INVALID_PARAMS;
  chart_axis_range(chart, axis, y_min, y_max);
  return MY_RET_OK;
}

bool my_chart_has_secondary_axis(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL && chart_has_secondary(chart);
}

static void chart_grid(my_widget_t* widget, my_vgcanvas_t* vg, float x, float y,
                       float w, float h, float y_min, float y_max) {
  my_chart_t* chart = (my_chart_t*)widget;
  u32 grid_lines = chart != NULL && chart->grid_line_count != 0u
                       ? chart->grid_line_count
                       : CHART_GRID_LINES;
  size_t i;
  char text[24];
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(0xE6EAF0FFu));
  my_vgcanvas_set_line_width(vg, 1.0f);
  for (i = 0; i < grid_lines; i++) {
    float ratio = (float)i / (float)(grid_lines - 1u);
    float line_y = y + h * ratio;
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, x, line_y);
    my_vgcanvas_line_to(vg, x + w, line_y);
    my_vgcanvas_stroke(vg);
    (void)my_chart_format_tick(y_max - (y_max - y_min) * ratio, text,
                               sizeof(text));
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x7B8794FFu));
    my_vgcanvas_draw_text(vg, text, 5.0f, line_y - 5.0f);
  }
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(0xAAB4C0FFu));
  my_vgcanvas_begin_path(vg);
  my_vgcanvas_move_to(vg, x, y);
  my_vgcanvas_line_to(vg, x, y + h);
  my_vgcanvas_line_to(vg, x + w, y + h);
  my_vgcanvas_stroke(vg);
  if (chart != NULL && chart->axis_title[0] != '\0') {
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x7B8794FFu));
    my_vgcanvas_set_font(vg, NULL, 10);
    my_vgcanvas_draw_text(vg, chart->axis_title, 5.0f, y - 4.0f);
  }
  if (chart != NULL && chart_has_secondary(chart)) {
    float y2_min, y2_max;
    chart_axis_range(chart, 1u, &y2_min, &y2_max);
    my_vgcanvas_set_font(vg, NULL, 10);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x7B8794FFu));
    for (i = 0; i < grid_lines; i++) {
      float ratio = (float)i / (float)(grid_lines - 1u);
      float line_y = y + h * ratio;
      (void)my_chart_format_tick(y2_max - (y2_max - y2_min) * ratio, text,
                                 sizeof(text));
      my_vgcanvas_draw_text(vg, text, x + w + 4.0f, line_y - 5.0f);
    }
  }
}

static void chart_draw_line_series(const my_chart_t* chart, my_vgcanvas_t* vg,
                                   size_t series_index, float x,
                                   float y, float w, float h) {
  const my_chart_series_t* series = &chart->series[series_index];
  float y_min, y_max;
  size_t begin, count;
  bool started = false;
  if (series->values == NULL || series->count == 0u) return;
  chart_axis_range(chart, chart_series_axis(chart, series_index), &y_min, &y_max);
  chart_zoom_range(chart, &begin, &count);
  if (count == 0u) return;
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(series->color));
  my_vgcanvas_set_line_width(vg, 2.0f);
  my_vgcanvas_begin_path(vg);
  for (size_t i = begin; i < begin + count && i < series->count; i++) {
    float px = chart_category_x(i, begin, count, x, w);
    float py = my_chart_value_to_y(chart_animated_value(chart, series->values[i]),
                                   y_min, y_max, y, h);
    if (!started) { my_vgcanvas_move_to(vg, px, py); started = true; }
    else my_vgcanvas_line_to(vg, px, py);
  }
  if (started) my_vgcanvas_stroke(vg);
}

static void chart_draw_scatter_series(const my_chart_t* chart,
                                      my_vgcanvas_t* vg, size_t series_index,
                                      float x, float y, float w, float h) {
  const my_chart_series_t* series = &chart->series[series_index];
  float y_min, y_max;
  size_t begin, count;
  if (series->values == NULL || series->count == 0u) return;
  chart_axis_range(chart, chart_series_axis(chart, series_index), &y_min, &y_max);
  chart_zoom_range(chart, &begin, &count);
  if (count == 0u) return;
  for (size_t i = begin; i < begin + count && i < series->count; i++) {
    float px = chart_category_x(i, begin, count, x, w);
    float py = my_chart_value_to_y(chart_animated_value(chart, series->values[i]),
                                   y_min, y_max, y, h);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(
        chart_visual_color(chart, series->values[i], series->color)));
    my_vgcanvas_fill_rounded_rect(vg,
                                  &(my_rectf_t){px - 4.0f, py - 4.0f, 8.0f, 8.0f},
                                  4.0f);
  }
}

static void chart_draw_pie(const my_chart_t* chart, my_vgcanvas_t* vg,
                           float x, float y, float w, float h) {
  const my_chart_series_t* series = NULL;
  float total = 0.0f;
  float cx = x + w * 0.5f;
  float cy = y + h * 0.5f;
  float radius = fminf(w, h) * 0.38f;
  for (size_t s = 0u; s < chart->series_count; s++) {
    if (chart->series_visible[s] && chart->series[s].values != NULL &&
        chart->series[s].count > 0u) { series = &chart->series[s]; break; }
  }
  if (series == NULL) return;
  for (size_t i = 0u; i < series->count; i++)
    if (series->values[i] > 0.0f) total += series->values[i];
  if (total <= 0.0f) return;
  float angle = -0.5f * CHART_PI;
  for (size_t i = 0u; i < series->count; i++) {
    float value = series->values[i] > 0.0f ? series->values[i] : 0.0f;
    float sweep = value / total * 2.0f * CHART_PI * chart->animation_progress;
    if (sweep <= 0.0f) continue;
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, cx, cy);
    my_vgcanvas_line_to(vg, cx + cosf(angle) * radius,
                        cy + sinf(angle) * radius);
    for (unsigned step = 1u; step <= 24u; step++) {
      float a = angle + sweep * (float)step / 24.0f;
      my_vgcanvas_line_to(vg, cx + cosf(a) * radius, cy + sinf(a) * radius);
    }
    my_vgcanvas_close_path(vg);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(s_colors[i % MY_CHART_MAX_SERIES]));
    my_vgcanvas_fill(vg);
    angle += value / total * 2.0f * CHART_PI;
  }
}

static void chart_draw_radar(const my_chart_t* chart, my_vgcanvas_t* vg,
                             float x, float y, float w, float h) {
  size_t count = chart_category_count(chart);
  float cx = x + w * 0.5f;
  float cy = y + h * 0.5f;
  float radius = fminf(w, h) * 0.36f;
  float y_min, y_max;
  if (count < 3u) return;
  chart_axis_range(chart, 0u, &y_min, &y_max);
  for (unsigned ring = 1u; ring <= 4u; ring++) {
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(0xD8DEE6AAu));
    my_vgcanvas_begin_path(vg);
    for (size_t i = 0u; i < count; i++) {
      float angle = -0.5f * CHART_PI + 2.0f * CHART_PI * (float)i / (float)count;
      float r = radius * (float)ring / 4.0f;
      float px = cx + cosf(angle) * r;
      float py = cy + sinf(angle) * r;
      if (i == 0u) my_vgcanvas_move_to(vg, px, py);
      else my_vgcanvas_line_to(vg, px, py);
    }
    my_vgcanvas_close_path(vg);
    my_vgcanvas_stroke(vg);
  }
  for (size_t i = 0u; i < count; i++) {
    float angle = -0.5f * CHART_PI + 2.0f * CHART_PI * (float)i / (float)count;
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, cx, cy);
    my_vgcanvas_line_to(vg, cx + cosf(angle) * radius,
                        cy + sinf(angle) * radius);
    my_vgcanvas_stroke(vg);
  }
  for (size_t s = 0u; s < chart->series_count; s++) {
    const my_chart_series_t* series = &chart->series[s];
    if (!chart->series_visible[s] || series->values == NULL ||
        series->count < count) continue;
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(
        chart_visual_color(chart, series->values[0], series->color) & 0x55FFFFFFu));
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(series->color));
    my_vgcanvas_set_line_width(vg, 2.0f);
    my_vgcanvas_begin_path(vg);
    for (size_t i = 0u; i < count; i++) {
      float value = chart_animated_value(chart, series->values[i]);
      float normalized = (value - y_min) / (y_max - y_min);
      if (normalized < 0.0f) normalized = 0.0f;
      if (normalized > 1.0f) normalized = 1.0f;
      float angle = -0.5f * CHART_PI + 2.0f * CHART_PI * (float)i / (float)count;
      float r = radius * normalized;
      float px = cx + cosf(angle) * r;
      float py = cy + sinf(angle) * r;
      if (i == 0u) my_vgcanvas_move_to(vg, px, py);
      else my_vgcanvas_line_to(vg, px, py);
    }
    my_vgcanvas_close_path(vg);
    my_vgcanvas_fill(vg);
    my_vgcanvas_stroke(vg);
  }
}

static void chart_draw_funnel(const my_chart_t* chart, my_vgcanvas_t* vg,
                              float x, float y, float w, float h) {
  const my_chart_series_t* series = NULL;
  float max_value = 0.0f;
  size_t count = 0u;
  for (size_t s = 0u; s < chart->series_count; s++) {
    if (chart->series_visible[s] && chart->series[s].values != NULL &&
        chart->series[s].count > 0u) { series = &chart->series[s]; break; }
  }
  if (series == NULL) return;
  for (size_t i = 0u; i < series->count; i++)
    if (series->values[i] > max_value) max_value = series->values[i];
  if (max_value <= 0.0f) return;
  count = series->count;
  float slot_h = h / (float)count;
  for (size_t i = 0u; i < count; i++) {
    float value = series->values[i] > 0.0f ? series->values[i] : 0.0f;
    float top_width = w * value / max_value * chart->animation_progress;
    float next_value = i + 1u < count && series->values[i + 1u] > 0.0f
                           ? series->values[i + 1u] : 0.0f;
    float bottom_width = w * next_value / max_value * chart->animation_progress;
    float cy = y + slot_h * ((float)i + 0.5f);
    float top_y = y + slot_h * (float)i;
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, x + (w - top_width) * 0.5f, top_y);
    my_vgcanvas_line_to(vg, x + (w + top_width) * 0.5f, top_y);
    my_vgcanvas_line_to(vg, x + (w + bottom_width) * 0.5f, top_y + slot_h);
    my_vgcanvas_line_to(vg, x + (w - bottom_width) * 0.5f, top_y + slot_h);
    my_vgcanvas_close_path(vg);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(
        chart_visual_color(chart, value, s_colors[i % MY_CHART_MAX_SERIES])));
    my_vgcanvas_fill(vg);
    if (chart->labels != NULL && i < chart->label_count &&
        chart->labels[i] != NULL) {
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xFFFFFFFFu));
      my_vgcanvas_set_font(vg, NULL, 10);
      my_vgcanvas_draw_text(vg, chart->labels[i], x + w * 0.5f - 16.0f,
                            cy - 4.0f);
    }
  }
}

static void chart_draw_heatmap(const my_chart_t* chart, my_vgcanvas_t* vg,
                               float x, float y, float w, float h) {
  size_t columns = chart_category_count(chart);
  size_t rows = 0u;
  for (size_t i = 0u; i < chart->series_count; i++)
    if (chart->series_visible[i] && chart->series[i].count > 0u) rows++;
  if (columns == 0u || rows == 0u) return;
  float cell_w = w / (float)columns;
  float cell_h = h / (float)rows;
  size_t row = 0u;
  for (size_t s = 0u; s < chart->series_count; s++) {
    const my_chart_series_t* series = &chart->series[s];
    if (!chart->series_visible[s] || series->values == NULL || series->count == 0u)
      continue;
    for (size_t col = 0u; col < series->count && col < columns; col++) {
      uint32_t color = chart_visual_color(chart, series->values[col], series->color);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(color));
      my_vgcanvas_fill_rect(vg, &(my_rectf_t){x + col * cell_w + 1.0f,
                                             y + row * cell_h + 1.0f,
                                             cell_w - 2.0f, cell_h - 2.0f});
    }
    row++;
  }
}

static void chart_draw_boxplot(const my_chart_t* chart, my_vgcanvas_t* vg,
                               float x, float y, float w, float h) {
  size_t visible = 0u;
  for (size_t i = 0u; i < chart->series_count; i++)
    if (chart->series_visible[i] && chart->series[i].values != NULL &&
        chart->series[i].count >= 5u) visible++;
  if (visible == 0u) return;
  for (size_t s = 0u, slot = 0u; s < chart->series_count; s++) {
    const my_chart_series_t* series = &chart->series[s];
    float y_min, y_max;
    float center_x, box_w;
    float y_q1, y_q3, y_med, y_lo, y_hi;
    if (!chart->series_visible[s] || series->values == NULL || series->count < 5u)
      continue;
    chart_axis_range(chart, chart_series_axis(chart, s), &y_min, &y_max);
    center_x = x + w * ((float)slot + 0.5f) / (float)visible;
    box_w = w / (float)visible * 0.5f;
    y_lo = my_chart_value_to_y(series->values[0], y_min, y_max, y, h);
    y_q1 = my_chart_value_to_y(series->values[1], y_min, y_max, y, h);
    y_med = my_chart_value_to_y(series->values[2], y_min, y_max, y, h);
    y_q3 = my_chart_value_to_y(series->values[3], y_min, y_max, y, h);
    y_hi = my_chart_value_to_y(series->values[4], y_min, y_max, y, h);
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(series->color));
    my_vgcanvas_set_line_width(vg, 2.0f);
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, center_x, y_lo);
    my_vgcanvas_line_to(vg, center_x, y_hi);
    my_vgcanvas_move_to(vg, center_x - box_w * 0.5f, y_lo);
    my_vgcanvas_line_to(vg, center_x + box_w * 0.5f, y_lo);
    my_vgcanvas_move_to(vg, center_x - box_w * 0.5f, y_hi);
    my_vgcanvas_line_to(vg, center_x + box_w * 0.5f, y_hi);
    my_vgcanvas_stroke(vg);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(
        chart_visual_color(chart, series->values[2], series->color)));
    my_vgcanvas_fill_rounded_rect(vg,
                                  &(my_rectf_t){center_x - box_w * 0.5f,
                                                fminf(y_q1, y_q3), box_w,
                                                fabsf(y_q3 - y_q1)}, 3.0f);
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(0x1F2933FFu));
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, center_x - box_w * 0.5f, y_med);
    my_vgcanvas_line_to(vg, center_x + box_w * 0.5f, y_med);
    my_vgcanvas_stroke(vg);
    slot++;
  }
}

static void chart_draw_bars(const my_chart_t* chart, my_vgcanvas_t* vg, float x,
                            float y, float w, float h, float y_min, float y_max) {
  size_t category_count = 0u;
  size_t series_index;
  float zero_y;
  if (chart->series_count == 0u) return;
  for (series_index = 0u; series_index < chart->series_count; series_index++) {
    if (!chart->series_visible[series_index]) continue;
    if (chart->series[series_index].count > category_count)
      category_count = chart->series[series_index].count;
  }
  {
    size_t begin, window;
    chart_zoom_range(chart, &begin, &window);
    if (window == 0u) return;
    zero_y = my_chart_value_to_y(0.0f, y_min, y_max, y, h);
    for (size_t category = begin; category < begin + window; category++) {
      float slot = w / (float)window;
      float group_width = slot * 0.82f;
      float group_left = x + slot * (float)(category - begin) +
                         (slot - group_width) * 0.5f;
      float group_slot = group_width / (float)chart->series_count;
      float positive_base = 0.0f;
      float negative_base = 0.0f;
      if (category >= category_count) break;
      for (series_index = 0u; series_index < chart->series_count; series_index++) {
        const my_chart_series_t* series = &chart->series[series_index];
        float bar_w;
        float bar_x;
        float value_y;
        float sy_min = y_min;
        float sy_max = y_max;
        float top;
        float height;
        if (!chart->series_visible[series_index] || series->values == NULL ||
            category >= series->count) continue;
        chart_axis_range(chart, chart_series_axis(chart, series_index), &sy_min,
                         &sy_max);
        if (chart->stacked) {
          bar_w = group_width;
          bar_x = group_left;
        } else {
          bar_w = group_slot * 0.82f;
          bar_x = group_left + group_slot * (float)series_index +
                  (group_slot - bar_w) * 0.5f;
        }
        value_y = my_chart_value_to_y(
            chart_animated_value(chart, series->values[category]), sy_min, sy_max,
            y, h);
        if (chart->stacked) {
          float value = chart_animated_value(chart, series->values[category]);
          float base = value >= 0.0f ? positive_base : negative_base;
          float base_y = my_chart_value_to_y(base, sy_min, sy_max, y, h);
          float end_y = my_chart_value_to_y(base + value, sy_min, sy_max, y, h);
          if (value >= 0.0f) {
            top = end_y < base_y ? end_y : base_y;
            height = fabsf(end_y - base_y);
            positive_base += value;
          } else {
            top = base_y < end_y ? base_y : end_y;
            height = fabsf(end_y - base_y);
            negative_base += value;
          }
        } else {
          top = value_y < zero_y ? value_y : zero_y;
          height = fabsf(value_y - zero_y);
        }
        my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(series->color));
        my_vgcanvas_fill_rounded_rect(vg,
                                      &(my_rectf_t){bar_x, top, bar_w, height},
                                      3.0f);
      }
    }
    return;
  }
}

static void chart_draw_hover_markers(const my_chart_t* chart, my_vgcanvas_t* vg,
                                     float x, float y, float w, float h,
                                     float y_min, float y_max) {
  size_t i;
  size_t category_count = chart_category_count(chart);
  size_t begin, window;
  if (chart->hover_index == CHART_HOVER_NONE || category_count == 0u) return;
  chart_zoom_range(chart, &begin, &window);
  if (window == 0u ||
      !chart_category_in_window(chart->hover_index, begin, window))
    return;
  for (i = 0u; i < chart->series_count; i++) {
    const my_chart_series_t* series = &chart->series[i];
    float point_x;
    float point_y;
    float sy_min = y_min;
    float sy_max = y_max;
    if (!chart->series_visible[i] || series->values == NULL ||
        chart->hover_index >= series->count) continue;
    point_x = chart_category_x(chart->hover_index, begin, window, x, w);
    chart_axis_range(chart, chart_series_axis(chart, i), &sy_min, &sy_max);
    if (chart->stacked && chart->mode == MY_CHART_BAR) {
      float value = chart_animated_value(chart, series->values[chart->hover_index]);
      float base = chart_stacked_base(chart, i, chart->hover_index, value);
      point_y = my_chart_stacked_value_to_y(value, base, sy_min, sy_max, y, h);
    } else {
      point_y = my_chart_value_to_y(chart_animated_value(
                                      chart, series->values[chart->hover_index]),
                                    sy_min, sy_max, y, h);
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x1F2933FFu));
    my_vgcanvas_fill_rounded_rect(vg,
                                  &(my_rectf_t){point_x - 5.0f, point_y - 5.0f,
                                                10.0f, 10.0f},
                                  3.0f);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xFFFFFFFFu));
    my_vgcanvas_fill_rounded_rect(vg,
                                  &(my_rectf_t){point_x - 2.0f, point_y - 2.0f,
                                                4.0f, 4.0f},
                                  1.5f);
  }
}

static void chart_draw_mark_points(const my_chart_t* chart, my_vgcanvas_t* vg,
                                   float x, float y, float w, float h,
                                   float y_min, float y_max) {
  size_t category_count = chart_category_count(chart);
  size_t begin, window;
  if (category_count == 0u) return;
  chart_zoom_range(chart, &begin, &window);
  if (window == 0u) return;
  my_vgcanvas_set_font(vg, NULL, 10);
  for (size_t m = 0u; m < chart->mark_count; m++) {
    const my_chart_mark_point_t* mark = &chart->marks[m];
    const my_chart_series_t* series;
    float px;
    float py;
    float sy_min = y_min;
    float sy_max = y_max;
    if (mark->series_index >= chart->series_count ||
        !chart->series_visible[mark->series_index])
      continue;
    series = &chart->series[mark->series_index];
    if (series->values == NULL || mark->category_index >= series->count) continue;
    if (!chart_category_in_window(mark->category_index, begin, window)) continue;
    px = chart_category_x(mark->category_index, begin, window, x, w);
    chart_axis_range(chart, chart_series_axis(chart, mark->series_index), &sy_min,
                     &sy_max);
    if (chart->stacked && chart->mode == MY_CHART_BAR) {
      float value = chart_animated_value(chart, series->values[mark->category_index]);
      float base = chart_stacked_base(chart, mark->series_index,
                                      mark->category_index, value);
      py = my_chart_stacked_value_to_y(value, base, sy_min, sy_max, y, h);
    } else {
      py = my_chart_value_to_y(chart_animated_value(
                                   chart, series->values[mark->category_index]),
                               sy_min, sy_max, y, h);
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(series->color));
    my_vgcanvas_fill_rounded_rect(vg,
                                  &(my_rectf_t){px - 4.0f, py - 4.0f, 8.0f, 8.0f},
                                  2.0f);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x1F2933FFu));
    my_vgcanvas_draw_text(vg, mark->label != NULL ? mark->label : "",
                          px + 6.0f, py - 4.0f);
  }
}

static void chart_draw_mark_lines(const my_chart_t* chart, my_vgcanvas_t* vg,
                                  float x, float y, float w, float h,
                                  float y_min, float y_max) {
  if (chart->line_count == 0u) return;
  my_vgcanvas_set_font(vg, NULL, 10);
  for (size_t m = 0u; m < chart->line_count; m++) {
    float line_y;
    uint32_t color = chart->lines[m].color != 0u ? chart->lines[m].color
                                                 : 0x9AA5B1FFu;
    if (chart->lines[m].value < y_min || chart->lines[m].value > y_max) continue;
    line_y = my_chart_value_to_y(chart->lines[m].value, y_min, y_max, y, h);
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(color));
    my_vgcanvas_set_line_width(vg, 1.0f);
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, x, line_y);
    my_vgcanvas_line_to(vg, x + w, line_y);
    my_vgcanvas_stroke(vg);
    if (chart->lines[m].label != NULL && chart->lines[m].label[0] != '\0') {
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(color));
      my_vgcanvas_draw_text(vg, chart->lines[m].label, x + w - 48.0f,
                            line_y - 4.0f);
    }
  }
}

static void chart_draw_mark_areas(const my_chart_t* chart, my_vgcanvas_t* vg,
                                  float x, float y, float w, float h,
                                  float y_min, float y_max) {
  if (chart->area_count == 0u) return;
  my_vgcanvas_set_font(vg, NULL, 10);
  for (size_t m = 0u; m < chart->area_count; m++) {
    float top_value = chart->areas[m].y_max;
    float bottom_value = chart->areas[m].y_min;
    float top_y;
    float bottom_y;
    uint32_t color = chart->areas[m].color != 0u ? chart->areas[m].color
                                                 : 0x3A86FF33u;
    if (top_value < y_min || bottom_value > y_max) continue;
    top_y = my_chart_value_to_y(top_value, y_min, y_max, y, h);
    bottom_y = my_chart_value_to_y(bottom_value, y_min, y_max, y, h);
    if (bottom_y < top_y) { float t = top_y; top_y = bottom_y; bottom_y = t; }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(color));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){x, top_y, w, bottom_y - top_y});
    if (chart->areas[m].label != NULL && chart->areas[m].label[0] != '\0') {
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x52606DFFu));
      my_vgcanvas_draw_text(vg, chart->areas[m].label, x + 4.0f, top_y - 4.0f);
    }
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
  if (chart->mode != MY_CHART_PIE && chart->mode != MY_CHART_RADAR &&
      chart->mode != MY_CHART_FUNNEL && chart->mode != MY_CHART_HEATMAP) {
    chart_grid(widget, vg, x, y, w, h, y_min, y_max);
    chart_draw_visual_map(chart, vg, x, y + 2.0f, w);
  }
  if (chart->labels != NULL && chart->label_count > 0u) {
    size_t label_count = chart->label_count;
    size_t label_index;
    size_t data_count = chart_category_count(chart);
    size_t zoom_begin, zoom_window;
    if (data_count > 0u && label_count > data_count) label_count = data_count;
    chart_zoom_range(chart, &zoom_begin, &zoom_window);
    my_vgcanvas_set_font(vg, NULL, 10);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x7B8794FFu));
    for (label_index = zoom_begin;
         label_index < zoom_begin + zoom_window && label_index < label_count;
         label_index++) {
      float label_x = chart_category_x(label_index, zoom_begin, zoom_window, x, w);
      my_vgcanvas_draw_text(vg, chart->labels[label_index] != NULL
                                   ? chart->labels[label_index]
                                   : "",
                            label_x - 12.0f, y + h + 6.0f);
    }
  }
  if (chart->mode == MY_CHART_BOXPLOT) {
    chart_draw_boxplot(chart, vg, x, y, w, h);
  } else if (chart->mode == MY_CHART_HEATMAP) {
    chart_draw_heatmap(chart, vg, x, y, w, h);
  } else if (chart->mode == MY_CHART_PIE) {
    chart_draw_pie(chart, vg, x, y, w, h);
  } else if (chart->mode == MY_CHART_BAR) {
    chart_draw_bars(chart, vg, x, y, w, h, y_min, y_max);
  } else if (chart->mode == MY_CHART_RADAR) {
    chart_draw_radar(chart, vg, x, y, w, h);
  } else if (chart->mode == MY_CHART_FUNNEL) {
    chart_draw_funnel(chart, vg, x, y, w, h);
  } else if (chart->mode == MY_CHART_SCATTER) {
    for (i = 0; i < chart->series_count; i++) {
      if (!chart->series_visible[i]) continue;
      chart_draw_scatter_series(chart, vg, i, x, y, w, h);
    }
  } else {
    for (i = 0; i < chart->series_count; i++) {
      if (!chart->series_visible[i]) continue;
      chart_draw_line_series(chart, vg, i, x, y, w, h);
    }
  }
  chart_draw_hover_markers(chart, vg, x, y, w, h, y_min, y_max);
  chart_draw_mark_points(chart, vg, x, y, w, h, y_min, y_max);
  chart_draw_mark_lines(chart, vg, x, y, w, h, y_min, y_max);
  chart_draw_mark_areas(chart, vg, x, y, w, h, y_min, y_max);
  if (chart->brush_active && chart->brush_start != SIZE_MAX &&
      chart->brush_end != SIZE_MAX) {
    size_t begin = chart->brush_start < chart->brush_end ? chart->brush_start
                                                         : chart->brush_end;
    size_t end = chart->brush_start < chart->brush_end ? chart->brush_end
                                                       : chart->brush_start;
    size_t zoom_begin, zoom_window;
    chart_zoom_range(chart, &zoom_begin, &zoom_window);
    if (zoom_window > 1u && end >= zoom_begin && begin < zoom_begin + zoom_window) {
      if (begin < zoom_begin) begin = zoom_begin;
      if (end >= zoom_begin + zoom_window) end = zoom_begin + zoom_window - 1u;
      float bx = chart_category_x(begin, zoom_begin, zoom_window, x, w);
      float ex = chart_category_x(end, zoom_begin, zoom_window, x, w);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x3A86FF33u));
      my_vgcanvas_fill_rect(vg, &(my_rectf_t){bx, y, ex - bx, h});
    }
  }
  if (chart->hover_index != CHART_HOVER_NONE &&
      chart_category_count(chart) > 0u) {
    char tooltip[64];
    size_t zoom_begin, zoom_window;
    chart_zoom_range(chart, &zoom_begin, &zoom_window);
    if (zoom_window > 0u &&
        chart_category_in_window(chart->hover_index, zoom_begin, zoom_window)) {
    float hover_x = chart_category_x(chart->hover_index, zoom_begin, zoom_window,
                                     x, w);
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
  }
  if (chart->show_legend) {
    float legend_x = x;
    my_vgcanvas_set_font(vg, NULL, 10);
    for (i = 0; i < chart->series_count; i++) {
      uint32_t color = chart->series_visible[i] ? chart->series[i].color
                                                : 0xB8C2CC88u;
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(color));
      my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){legend_x, 21, 7, 7}, 2);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(
          chart->series_visible[i] ? 0x52606DFFu : 0x9AA5B1FFu));
      my_vgcanvas_draw_text(vg, chart->series[i].name != NULL ? chart->series[i].name : "",
                            legend_x + 11, 18);
      legend_x += 70.0f;
    }
  }
}

static my_ret_t chart_on_event(my_widget_t* widget, const my_event_t* event) {
  my_chart_t* chart = (my_chart_t*)widget;
  float x, y, w, h;
  int32_t local_x, local_y;
  size_t index;
  if (event == NULL || !chart_plot_rect(widget, &x, &y, &w, &h)) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (event->type == MY_EVENT_KEY_DOWN && chart_category_count(chart) > 0u) {
    size_t begin, window;
    size_t next = chart->hover_index == CHART_HOVER_NONE ? 0u : chart->hover_index;
    chart_zoom_range(chart, &begin, &window);
    if (window == 0u) return MY_RET_NOT_SUPPORTED;
    if (event->u.key.key == MY_KEY_LEFT) {
      if (next > begin) next--;
    } else if (event->u.key.key == MY_KEY_RIGHT) {
      if (next + 1u < begin + window) next++;
    } else {
      return MY_RET_NOT_SUPPORTED;
    }
    chart->hover_index = next;
    my_widget_invalidate(widget, NULL);
    return MY_RET_OK;
  }
  local_x = event->u.pointer.x;
  local_y = event->u.pointer.y;
  my_widget_global_to_local(widget, &local_x, &local_y);
  if ((event->type == MY_EVENT_POINTER_DOWN || event->type == MY_EVENT_POINTER_MOVE ||
       event->type == MY_EVENT_POINTER_UP) && event->u.pointer.button == 1u &&
      chart->mode != MY_CHART_PIE && (float)local_x >= x &&
      (float)local_x <= x + w && (float)local_y >= y &&
      (float)local_y <= y + h) {
    size_t begin, window, category;
    chart_zoom_range(chart, &begin, &window);
    if (window == 0u) return MY_RET_NOT_SUPPORTED;
    category = begin + (window > 1u
                            ? (size_t)lroundf(((float)local_x - x) / w *
                                              (float)(window - 1u))
                            : 0u);
    if (category >= begin + window) category = begin + window - 1u;
    if (event->type == MY_EVENT_POINTER_DOWN) {
      chart->brush_active = true;
      chart->brush_start = category;
      chart->brush_end = category;
    } else if (event->type == MY_EVENT_POINTER_MOVE && chart->brush_active) {
      chart->brush_end = category;
    } else if (event->type == MY_EVENT_POINTER_UP && chart->brush_active) {
      chart->brush_end = category;
      my_widget_invalidate(widget, NULL);
      return MY_RET_OK;
    }
    my_widget_invalidate(widget, NULL);
    return MY_RET_OK;
  }
  if (chart->mode == MY_CHART_PIE && event->type == MY_EVENT_POINTER_MOVE) {
    const my_chart_series_t* series = NULL;
    float cx = x + w * 0.5f;
    float cy = y + h * 0.5f;
    float radius = fminf(w, h) * 0.38f;
    float dx = (float)local_x - cx;
    float dy = (float)local_y - cy;
    float distance = sqrtf(dx * dx + dy * dy);
    float total = 0.0f;
    float angle;
    if (distance > radius) {
      chart->hover_index = CHART_HOVER_NONE;
      return MY_RET_NOT_SUPPORTED;
    }
    for (size_t s = 0u; s < chart->series_count; s++) {
      if (chart->series_visible[s] && chart->series[s].values != NULL &&
          chart->series[s].count > 0u) {
        series = &chart->series[s];
        break;
      }
    }
    if (series == NULL) return MY_RET_NOT_SUPPORTED;
    for (size_t i = 0u; i < series->count; i++)
      if (series->values[i] > 0.0f) total += series->values[i];
    if (total <= 0.0f) return MY_RET_NOT_SUPPORTED;
    angle = atan2f(dy, dx) + 0.5f * CHART_PI;
    if (angle < 0.0f) angle += 2.0f * CHART_PI;
    for (size_t i = 0u; i < series->count; i++) {
      float sweep = (series->values[i] > 0.0f ? series->values[i] : 0.0f) /
                    total * 2.0f * CHART_PI;
      if (angle <= sweep) { index = i; break; }
      angle -= sweep;
      index = i;
    }
    if (chart->hover_index != index) {
      chart->hover_index = index;
      my_widget_invalidate(widget, NULL);
    }
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_POINTER_DOWN && event->u.pointer.button == 1u &&
      chart->show_legend && local_y >= 10 && local_y <= 32) {
    float offset = (float)local_x - x;
    if (offset >= 0.0f) {
      size_t index = (size_t)(offset / 70.0f);
      if (index < chart->series_count && offset >= index * 70.0f &&
          offset < index * 70.0f + 70.0f) {
        chart->series_visible[index] = !chart->series_visible[index];
        chart->hover_index = CHART_HOVER_NONE;
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
      }
    }
    return MY_RET_NOT_SUPPORTED;
  }
  if (event->type != MY_EVENT_POINTER_MOVE || chart_category_count(chart) == 0u) {
    return MY_RET_NOT_SUPPORTED;
  }
  if ((float)local_x < x || (float)local_x > x + w || (float)local_y < y ||
       (float)local_y > y + h) {
    chart->hover_index = CHART_HOVER_NONE;
    return MY_RET_NOT_SUPPORTED;
  }
  {
    size_t category_count = chart_category_count(chart);
    size_t begin, window;
    chart_zoom_range(chart, &begin, &window);
    if (window == 0u) return MY_RET_NOT_SUPPORTED;
    if (window > 1u)
      index = begin + (size_t)lroundf(((float)local_x - x) / w *
                                      (float)(window - 1u));
    else
      index = begin;
    if (index >= begin + window) index = begin + window - 1u;
    if (index >= category_count) index = category_count - 1u;
  }
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
  if (mode != MY_CHART_LINE && mode != MY_CHART_BAR && mode != MY_CHART_SCATTER &&
      mode != MY_CHART_PIE && mode != MY_CHART_RADAR && mode != MY_CHART_FUNNEL &&
      mode != MY_CHART_HEATMAP && mode != MY_CHART_BOXPLOT)
    return NULL;
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
  chart->stacked = false;
  chart->animation_progress = 1.0f;
  chart->brush_start = SIZE_MAX;
  chart->brush_end = SIZE_MAX;
  for (size_t i = 0u; i < MY_CHART_MAX_SERIES; i++) chart->series_visible[i] = true;
  chart->base.widget_type = "chart";
  my_emitter_on(chart->base.emitter, "hover_leave", chart_hover_leave, chart);
  return (my_widget_t*)chart;
}

bool my_chart_is_instance(const my_widget_t* widget) {
  return widget != NULL && widget->vtable == &s_chart_vtable;
}

my_ret_t my_chart_apply_snapshot(my_widget_t* widget,
                                 const my_chart_snapshot_t* snapshot) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || snapshot == NULL || snapshot->title == NULL ||
      snapshot->series_count > MY_CHART_MAX_SERIES ||
      (snapshot->label_count > 0u && snapshot->labels == NULL) ||
      (snapshot->series_count > 0u && snapshot->series == NULL) ||
      (snapshot->series_count > 0u && snapshot->series_visible == NULL) ||
      snapshot->mode < MY_CHART_LINE || snapshot->mode > MY_CHART_BOXPLOT)
    return MY_RET_INVALID_PARAMS;
  if (strlen(snapshot->title) >= sizeof(chart->title)) return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < snapshot->label_count; i++)
    if (snapshot->labels[i] == NULL) return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < snapshot->series_count; i++) {
    const my_chart_series_t* series = &snapshot->series[i];
    if (series->name == NULL || series->y_axis > 1u ||
        (series->count > 0u && series->values == NULL))
      return MY_RET_INVALID_PARAMS;
    for (size_t j = 0u; j < series->count; j++)
      if (!isfinite(series->values[j])) return MY_RET_INVALID_PARAMS;
  }
  if (snapshot->range_set && (!isfinite(snapshot->y_min) ||
                              !isfinite(snapshot->y_max) ||
                              snapshot->y_max <= snapshot->y_min))
    return MY_RET_INVALID_PARAMS;
  if (snapshot->zoom_set && snapshot->zoom_end <= snapshot->zoom_start)
    return MY_RET_INVALID_PARAMS;
  if (snapshot->visual_map_set &&
      (!isfinite(snapshot->visual_map_min) ||
       !isfinite(snapshot->visual_map_max) ||
       snapshot->visual_map_max <= snapshot->visual_map_min))
    return MY_RET_INVALID_PARAMS;
  if (snapshot->mark_count > MY_CHART_MAX_MARK_POINTS ||
      (snapshot->mark_count > 0u && snapshot->marks == NULL) ||
      snapshot->line_count > MY_CHART_MAX_MARK_LINES ||
      (snapshot->line_count > 0u && snapshot->lines == NULL) ||
      snapshot->area_count > MY_CHART_MAX_MARK_AREAS ||
      (snapshot->area_count > 0u && snapshot->areas == NULL))
    return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < snapshot->line_count; i++)
    if (!isfinite(snapshot->lines[i].value)) return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < snapshot->area_count; i++)
    if (!isfinite(snapshot->areas[i].y_min) ||
        !isfinite(snapshot->areas[i].y_max) ||
        snapshot->areas[i].y_max <= snapshot->areas[i].y_min)
      return MY_RET_INVALID_PARAMS;
  chart->mode = snapshot->mode;
  snprintf(chart->title, sizeof(chart->title), "%s", snapshot->title);
  chart->labels = snapshot->labels;
  chart->label_count = snapshot->label_count;
  memcpy(chart->series, snapshot->series,
         snapshot->series_count * sizeof(*snapshot->series));
  memcpy(chart->series_visible, snapshot->series_visible,
         snapshot->series_count * sizeof(*snapshot->series_visible));
  for (size_t i = snapshot->series_count; i < MY_CHART_MAX_SERIES; i++) {
    memset(&chart->series[i], 0, sizeof(chart->series[i]));
    chart->series_visible[i] = false;
  }
  chart->series_count = snapshot->series_count;
  chart->stacked = snapshot->stacked;
  chart->show_legend = snapshot->show_legend;
  chart->range_set = snapshot->range_set;
  chart->y_min = snapshot->y_min;
  chart->y_max = snapshot->y_max;
  chart->zoom_set = snapshot->zoom_set;
  chart->zoom_start = snapshot->zoom_start;
  chart->zoom_end = snapshot->zoom_end;
  chart->visual_map_set = snapshot->visual_map_set;
  chart->visual_map_min = snapshot->visual_map_min;
  chart->visual_map_max = snapshot->visual_map_max;
  chart->visual_map_low_color = snapshot->visual_map_low_color;
  chart->visual_map_high_color = snapshot->visual_map_high_color;
  for (size_t i = 0u; i < snapshot->mark_count; i++) {
    chart->marks[i] = snapshot->marks[i];
    chart->marks[i].label = snapshot->marks[i].label;
  }
  for (size_t i = 0u; i < snapshot->line_count; i++) {
    chart->lines[i].value = snapshot->lines[i].value;
    chart->lines[i].label = snapshot->lines[i].label;
    chart->lines[i].color = snapshot->lines[i].color;
  }
  for (size_t i = 0u; i < snapshot->area_count; i++) {
    chart->areas[i].y_min = snapshot->areas[i].y_min;
    chart->areas[i].y_max = snapshot->areas[i].y_max;
    chart->areas[i].label = snapshot->areas[i].label;
    chart->areas[i].color = snapshot->areas[i].color;
  }
  chart->mark_count = snapshot->mark_count;
  chart->line_count = snapshot->line_count;
  chart->area_count = snapshot->area_count;
  chart->hover_index = CHART_HOVER_NONE;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
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
  size_t i;
  if (chart == NULL || series == NULL || index >= MY_CHART_MAX_SERIES ||
      index > chart->series_count ||
      (series->count > 0u && series->values == NULL)) return MY_RET_INVALID_PARAMS;
  for (i = 0; i < series->count; i++) {
    if (!isfinite(series->values[i])) return MY_RET_INVALID_PARAMS;
  }
  chart->series[index] = *series;
  if (chart->series[index].color == 0u) chart->series[index].color = s_colors[index];
  chart->series_visible[index] = true;
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

my_ret_t my_chart_set_series_visible(my_widget_t* widget, size_t index,
                                     bool visible) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || index >= chart->series_count) return MY_RET_INVALID_PARAMS;
  chart->series_visible[index] = visible;
  chart->hover_index = CHART_HOVER_NONE;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_set_series_axis(my_widget_t* widget, size_t index,
                                  unsigned axis) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || index >= chart->series_count || axis > 1u)
    return MY_RET_INVALID_PARAMS;
  chart->series[index].y_axis = (unsigned char)axis;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

unsigned my_chart_get_series_axis(const my_widget_t* widget, size_t index) {
  const my_chart_t* chart = chart_const_cast(widget);
  if (chart == NULL || index >= chart->series_count) return 0u;
  return chart_series_axis(chart, index);
}

bool my_chart_get_series_visible(const my_widget_t* widget, size_t index) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL && index < chart->series_count && chart->series_visible[index];
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

my_ret_t my_chart_set_secondary_range(my_widget_t* widget, float y_min,
                                      float y_max) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || !isfinite(y_min) || !isfinite(y_max) || y_max <= y_min)
    return MY_RET_INVALID_PARAMS;
  chart->y2_min = y_min;
  chart->y2_max = y_max;
  chart->range2_set = true;
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

my_ret_t my_chart_set_stacked(my_widget_t* widget, bool stacked) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  chart->stacked = stacked;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

bool my_chart_get_stacked(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL && chart->stacked;
}

my_ret_t my_chart_set_visual_map(my_widget_t* widget, float min_value,
                                 float max_value, uint32_t low_color,
                                 uint32_t high_color) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || !isfinite(min_value) || !isfinite(max_value) ||
      max_value <= min_value)
    return MY_RET_INVALID_PARAMS;
  chart->visual_map_set = true;
  chart->visual_map_min = min_value;
  chart->visual_map_max = max_value;
  chart->visual_map_low_color = low_color;
  chart->visual_map_high_color = high_color;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_clear_visual_map(my_widget_t* widget) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  chart->visual_map_set = false;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

bool my_chart_has_visual_map(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL && chart->visual_map_set;
}

my_ret_t my_chart_get_brush(const my_widget_t* widget, size_t* start,
                            size_t* end) {
  const my_chart_t* chart = chart_const_cast(widget);
  if (chart == NULL || start == NULL || end == NULL)
    return MY_RET_INVALID_PARAMS;
  if (!chart->brush_active) return MY_RET_NOT_SUPPORTED;
  *start = chart->brush_start < chart->brush_end ? chart->brush_start
                                                 : chart->brush_end;
  *end = chart->brush_start < chart->brush_end ? chart->brush_end
                                               : chart->brush_start;
  return MY_RET_OK;
}

my_ret_t my_chart_clear_brush(my_widget_t* widget) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  chart->brush_active = false;
  chart->brush_start = SIZE_MAX;
  chart->brush_end = SIZE_MAX;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_set_animation_progress(my_widget_t* widget, float progress) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || !isfinite(progress) || progress < 0.0f || progress > 1.0f)
    return MY_RET_INVALID_PARAMS;
  chart->animation_progress = progress;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

float my_chart_get_animation_progress(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL ? chart->animation_progress : 0.0f;
}

my_ret_t my_chart_set_data_zoom(my_widget_t* widget, size_t start,
                                size_t end) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || end <= start) return MY_RET_INVALID_PARAMS;
  chart->zoom_set = true;
  chart->zoom_start = start;
  chart->zoom_end = end;
  chart->hover_index = CHART_HOVER_NONE;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_clear_data_zoom(my_widget_t* widget) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  chart->zoom_set = false;
  chart->zoom_start = 0u;
  chart->zoom_end = 0u;
  chart->hover_index = CHART_HOVER_NONE;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

bool my_chart_get_data_zoom(const my_widget_t* widget, size_t* start,
                            size_t* end) {
  const my_chart_t* chart = chart_const_cast(widget);
  if (chart == NULL || !chart->zoom_set) return false;
  if (start != NULL) *start = chart->zoom_start;
  if (end != NULL) *end = chart->zoom_end;
  return true;
}

my_ret_t my_chart_set_axis_title(my_widget_t* widget, const char* title) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  snprintf(chart->axis_title, sizeof(chart->axis_title), "%s",
           title != NULL ? title : "");
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_set_grid_line_count(my_widget_t* widget, u32 count) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || count < CHART_GRID_LINES_MIN ||
      count > CHART_GRID_LINES_MAX)
    return MY_RET_INVALID_PARAMS;
  chart->grid_line_count = count;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

u32 my_chart_get_grid_line_count(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  if (chart == NULL) return 0u;
  return chart->grid_line_count != 0u ? chart->grid_line_count
                                      : CHART_GRID_LINES;
}

my_ret_t my_chart_add_mark_point(my_widget_t* widget, size_t series_index,
                                 size_t category_index, const char* label) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || series_index >= chart->series_count ||
      category_index >= chart->series[series_index].count ||
      chart->mark_count >= MY_CHART_MAX_MARK_POINTS)
    return MY_RET_INVALID_PARAMS;
  chart->marks[chart->mark_count].series_index = series_index;
  chart->marks[chart->mark_count].category_index = category_index;
  chart->marks[chart->mark_count].label = label;
  chart->mark_count++;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_clear_mark_points(my_widget_t* widget) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  memset(chart->marks, 0, sizeof(chart->marks));
  chart->mark_count = 0u;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

size_t my_chart_get_mark_point_count(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL ? chart->mark_count : 0u;
}

my_ret_t my_chart_add_mark_line(my_widget_t* widget, float value,
                                const char* label, uint32_t color) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || !isfinite(value) ||
      chart->line_count >= MY_CHART_MAX_MARK_LINES)
    return MY_RET_INVALID_PARAMS;
  chart->lines[chart->line_count].value = value;
  chart->lines[chart->line_count].label = label;
  chart->lines[chart->line_count].color = color;
  chart->line_count++;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_clear_mark_lines(my_widget_t* widget) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  memset(chart->lines, 0, sizeof(chart->lines));
  chart->line_count = 0u;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

size_t my_chart_get_mark_line_count(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL ? chart->line_count : 0u;
}

my_ret_t my_chart_add_mark_area(my_widget_t* widget, float y_min, float y_max,
                                const char* label, uint32_t color) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL || !isfinite(y_min) || !isfinite(y_max) || y_max <= y_min ||
      chart->area_count >= MY_CHART_MAX_MARK_AREAS)
    return MY_RET_INVALID_PARAMS;
  chart->areas[chart->area_count].y_min = y_min;
  chart->areas[chart->area_count].y_max = y_max;
  chart->areas[chart->area_count].label = label;
  chart->areas[chart->area_count].color = color;
  chart->area_count++;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_chart_clear_mark_areas(my_widget_t* widget) {
  my_chart_t* chart = chart_cast(widget);
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  memset(chart->areas, 0, sizeof(chart->areas));
  chart->area_count = 0u;
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

size_t my_chart_get_mark_area_count(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL ? chart->area_count : 0u;
}

size_t my_chart_get_hover_index(const my_widget_t* widget) {
  const my_chart_t* chart = chart_const_cast(widget);
  return chart != NULL ? chart->hover_index : CHART_HOVER_NONE;
}

my_ret_t my_chart_get_tooltip(const my_widget_t* widget, char* buffer,
                              size_t capacity) {
  const my_chart_t* chart = chart_const_cast(widget);
  size_t i;
  size_t written = 0u;
  bool found = false;
  bool has_series = false;
  if (chart == NULL || buffer == NULL || capacity == 0u) return MY_RET_INVALID_PARAMS;
  if (chart->hover_index == CHART_HOVER_NONE || chart->series_count == 0u)
    return MY_RET_NOT_SUPPORTED;
  buffer[0] = '\0';
  if (chart->labels != NULL && chart->hover_index < chart->label_count &&
      chart->labels[chart->hover_index] != NULL &&
      chart->labels[chart->hover_index][0] != '\0') {
    int result = snprintf(buffer, capacity, "%s: ",
                          chart->labels[chart->hover_index]);
    if (result < 0 || (size_t)result >= capacity) {
      buffer[capacity - 1u] = '\0';
      return MY_RET_FAIL;
    }
    written = (size_t)result;
  }
  for (i = 0u; i < chart->series_count; i++) {
    const my_chart_series_t* series = &chart->series[i];
    int result;
    if (!chart->series_visible[i] || series->values == NULL ||
        chart->hover_index >= series->count) continue;
    result = snprintf(buffer + written, capacity - written, "%s%s: %.2f",
                      has_series ? ", " : "",
                      series->name != NULL ? series->name : "Series",
                      (double)series->values[chart->hover_index]);
    if (result < 0 || (size_t)result >= capacity - written) {
      buffer[capacity - 1u] = '\0';
      return MY_RET_FAIL;
    }
    written += (size_t)result;
    found = true;
    has_series = true;
  }
  if (!found) return MY_RET_NOT_SUPPORTED;
  return MY_RET_OK;
}

my_ret_t my_chart_get_accessible_description(const my_widget_t* widget,
                                             char* buffer, size_t capacity) {
  const my_chart_t* chart = chart_const_cast(widget);
  size_t category_count;
  const char* mode;
  int written;
  if (chart == NULL || buffer == NULL || capacity == 0u)
    return MY_RET_INVALID_PARAMS;
  category_count = chart_category_count(chart);
  mode = chart->mode == MY_CHART_LINE ? "line" :
         chart->mode == MY_CHART_BAR ? "bar" :
         chart->mode == MY_CHART_SCATTER ? "scatter" : "pie";
  written = snprintf(buffer, capacity, "%s: %s chart, %zu series, %zu categories",
                     chart->title[0] != '\0' ? chart->title : "Chart", mode,
                     chart->series_count, category_count);
  if (written < 0 || (size_t)written >= capacity) {
    buffer[capacity - 1u] = '\0';
    return MY_RET_FAIL;
  }
  for (size_t i = 0u; i < chart->series_count && (size_t)written < capacity; i++) {
    int appended = snprintf(buffer + written, capacity - (size_t)written,
                            "%s%s", i == 0u ? "; " : ", ",
                            chart->series[i].name != NULL ? chart->series[i].name
                                                           : "Series");
    if (appended < 0 || (size_t)appended >= capacity - (size_t)written) {
      buffer[capacity - 1u] = '\0';
      return MY_RET_FAIL;
    }
    written += appended;
  }
  return MY_RET_OK;
}
