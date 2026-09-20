/**
 * @file my_chart.h
 * @brief ECharts-inspired line and bar chart widget.
 */
#ifndef MY_CHART_H
#define MY_CHART_H

#include "myui/my_widget.h"

#define MY_CHART_MAX_SERIES 4u

typedef enum my_chart_mode_t {
  MY_CHART_LINE = 0,
  MY_CHART_BAR
} my_chart_mode_t;

/** @brief A borrowed data series; caller owns name and values. */
typedef struct my_chart_series_t {
  const char* name;
  const float* values;
  size_t count;
  uint32_t color;
} my_chart_series_t;

typedef struct my_chart_t {
  my_widget_t base;
  my_chart_mode_t mode;
  char title[96];
  const char* const* labels;
  size_t label_count;
  my_chart_series_t series[MY_CHART_MAX_SERIES];
  size_t series_count;
  float y_min;
  float y_max;
  bool range_set;
  bool show_legend;
  size_t hover_index;
} my_chart_t;

my_widget_t* my_chart_create(const my_allocator_t* allocator,
                             my_chart_mode_t mode);
bool my_chart_is_instance(const my_widget_t* widget);
my_ret_t my_chart_set_title(my_widget_t* chart, const char* title);
my_ret_t my_chart_set_labels(my_widget_t* chart, const char* const* labels,
                             size_t count);
my_ret_t my_chart_set_series(my_widget_t* chart, size_t index,
                             const my_chart_series_t* series);
my_ret_t my_chart_clear_series(my_widget_t* chart);
my_ret_t my_chart_set_range(my_widget_t* chart, float y_min, float y_max);
my_ret_t my_chart_set_legend_visible(my_widget_t* chart, bool visible);
size_t my_chart_get_hover_index(const my_widget_t* chart);
my_ret_t my_chart_get_tooltip(const my_widget_t* chart, char* buffer,
                              size_t capacity);

/** @brief Convert a value to plot-local y for deterministic layout tests. */
float my_chart_value_to_y(float value, float y_min, float y_max,
                          float plot_top, float plot_height);

/** @brief Format a Y-axis tick while preserving useful fractional precision. */
my_ret_t my_chart_format_tick(float value, char* buffer, size_t capacity);

#endif /* MY_CHART_H */
