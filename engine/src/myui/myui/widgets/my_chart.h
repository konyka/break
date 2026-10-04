/**
 * @file my_chart.h
 * @brief ECharts-inspired line and bar chart widget.
 */
#ifndef MY_CHART_H
#define MY_CHART_H

#include "myui/my_widget.h"

#define MY_CHART_MAX_SERIES 4u
#define MY_CHART_MAX_MARK_POINTS 8u
#define MY_CHART_MAX_MARK_LINES 4u
#define MY_CHART_MAX_MARK_AREAS 4u

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
  /** @brief Y axis binding: 0 = left axis, 1 = right axis. */
  unsigned char y_axis;
} my_chart_series_t;

/** @brief A borrowed annotation anchored to one series category sample. */
typedef struct my_chart_mark_point_t {
  size_t series_index;
  size_t category_index;
  const char* label;
} my_chart_mark_point_t;

typedef struct my_chart_t {
  my_widget_t base;
  my_chart_mode_t mode;
  char title[96];
  const char* const* labels;
  size_t label_count;
  my_chart_series_t series[MY_CHART_MAX_SERIES];
  bool series_visible[MY_CHART_MAX_SERIES];
  size_t series_count;
  float y_min;
  float y_max;
  bool range_set;
  float y2_min;
  float y2_max;
  bool range2_set;
  bool show_legend;
  bool stacked;
  bool zoom_set;
  size_t zoom_start;
  size_t zoom_end;
  char axis_title[48];
  u32 grid_line_count;
  size_t hover_index;
  my_chart_mark_point_t marks[MY_CHART_MAX_MARK_POINTS];
  size_t mark_count;
  struct {
    float value;
    const char* label;
    uint32_t color;
  } lines[MY_CHART_MAX_MARK_LINES];
  size_t line_count;
  struct {
    float y_min;
    float y_max;
    const char* label;
    uint32_t color;
  } areas[MY_CHART_MAX_MARK_AREAS];
  size_t area_count;
} my_chart_t;

my_widget_t* my_chart_create(const my_allocator_t* allocator,
                             my_chart_mode_t mode);
bool my_chart_is_instance(const my_widget_t* widget);
my_ret_t my_chart_set_title(my_widget_t* chart, const char* title);
my_ret_t my_chart_set_labels(my_widget_t* chart, const char* const* labels,
                             size_t count);
my_ret_t my_chart_set_series(my_widget_t* chart, size_t index,
                              const my_chart_series_t* series);
my_ret_t my_chart_set_series_visible(my_widget_t* chart, size_t index,
                                     bool visible);
bool my_chart_get_series_visible(const my_widget_t* chart, size_t index);
my_ret_t my_chart_set_series_axis(my_widget_t* chart, size_t index,
                                  unsigned axis);
unsigned my_chart_get_series_axis(const my_widget_t* chart, size_t index);
bool my_chart_has_secondary_axis(const my_widget_t* chart);
my_ret_t my_chart_get_axis_range(const my_widget_t* chart, unsigned axis,
                                 float* y_min, float* y_max);
my_ret_t my_chart_clear_series(my_widget_t* chart);
my_ret_t my_chart_set_range(my_widget_t* chart, float y_min, float y_max);
my_ret_t my_chart_set_secondary_range(my_widget_t* chart, float y_min,
                                      float y_max);
/** @brief Report the effective Y range (explicit or automatic). */
my_ret_t my_chart_get_range(const my_widget_t* chart, float* y_min,
                            float* y_max);
my_ret_t my_chart_set_legend_visible(my_widget_t* chart, bool visible);
my_ret_t my_chart_set_stacked(my_widget_t* chart, bool stacked);
bool my_chart_get_stacked(const my_widget_t* chart);
my_ret_t my_chart_set_data_zoom(my_widget_t* chart, size_t start,
                                size_t end);
my_ret_t my_chart_clear_data_zoom(my_widget_t* chart);
bool my_chart_get_data_zoom(const my_widget_t* chart, size_t* start,
                            size_t* end);
my_ret_t my_chart_set_axis_title(my_widget_t* chart, const char* title);
my_ret_t my_chart_set_grid_line_count(my_widget_t* chart, u32 count);
u32 my_chart_get_grid_line_count(const my_widget_t* chart);
my_ret_t my_chart_add_mark_point(my_widget_t* chart, size_t series_index,
                                 size_t category_index, const char* label);
my_ret_t my_chart_clear_mark_points(my_widget_t* chart);
size_t my_chart_get_mark_point_count(const my_widget_t* chart);
my_ret_t my_chart_add_mark_line(my_widget_t* chart, float value,
                                const char* label, uint32_t color);
my_ret_t my_chart_clear_mark_lines(my_widget_t* chart);
size_t my_chart_get_mark_line_count(const my_widget_t* chart);
my_ret_t my_chart_add_mark_area(my_widget_t* chart, float y_min, float y_max,
                                const char* label, uint32_t color);
my_ret_t my_chart_clear_mark_areas(my_widget_t* chart);
size_t my_chart_get_mark_area_count(const my_widget_t* chart);
size_t my_chart_get_hover_index(const my_widget_t* chart);
my_ret_t my_chart_get_tooltip(const my_widget_t* chart, char* buffer,
                              size_t capacity);

/** @brief Convert a value to plot-local y for deterministic layout tests. */
float my_chart_value_to_y(float value, float y_min, float y_max,
                          float plot_top, float plot_height);

/** @brief Convert a stacked segment endpoint to plot-local y. */
float my_chart_stacked_value_to_y(float value, float base, float y_min,
                                  float y_max, float plot_top,
                                  float plot_height);

/** @brief Format a Y-axis tick while preserving useful fractional precision. */
my_ret_t my_chart_format_tick(float value, char* buffer, size_t capacity);

#endif /* MY_CHART_H */
