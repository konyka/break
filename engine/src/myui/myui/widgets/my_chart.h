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
#define MY_CHART_MAX_GRIDS 4u
#define MY_CHART_NO_GRID SIZE_MAX
#define MY_CHART_GROUP_MAX_GROUPS 8u
#define MY_CHART_GROUP_MAX_CHARTS 8u

typedef enum my_chart_mode_t {
  MY_CHART_LINE = 0,
  MY_CHART_BAR,
  MY_CHART_SCATTER,
  MY_CHART_PIE,
  MY_CHART_RADAR,
  MY_CHART_FUNNEL,
  MY_CHART_HEATMAP,
  MY_CHART_BOXPLOT,
  MY_CHART_CANDLESTICK,
  MY_CHART_GAUGE,
  MY_CHART_SANKEY,
  MY_CHART_PARALLEL,
  MY_CHART_TREEMAP,
  MY_CHART_GRAPH,
  MY_CHART_CALENDAR,
  MY_CHART_THEME_RIVER
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

typedef struct my_chart_mark_line_state_t {
  float value;
  const char* label;
  uint32_t color;
} my_chart_mark_line_state_t;

typedef struct my_chart_mark_area_state_t {
  float y_min;
  float y_max;
  const char* label;
  uint32_t color;
} my_chart_mark_area_state_t;

/** @brief One plot area: fractional rect plus the series drawn inside it. */
typedef struct my_chart_grid_desc_t {
  float left;
  float top;
  float width;
  float height;
  size_t series_indices[MY_CHART_MAX_SERIES];
  size_t series_count;
  bool range_set;
  float y_min;
  float y_max;
  bool range2_set;
  float y2_min;
  float y2_max;
  bool visible;
  bool link_axis_pointer;
} my_chart_grid_desc_t;

/** @brief Borrowed renderer state committed atomically to a chart widget. */
typedef struct my_chart_snapshot_t {
  my_chart_mode_t mode;
  const char* title;
  const char* const* labels;
  size_t label_count;
  const my_chart_series_t* series;
  const bool* series_visible;
  size_t series_count;
  bool stacked;
  bool show_legend;
  bool tooltip_enabled;
  bool range_set;
  float y_min;
  float y_max;
  bool zoom_set;
  size_t zoom_start;
  size_t zoom_end;
  bool visual_map_set;
  float visual_map_min;
  float visual_map_max;
  uint32_t visual_map_low_color;
  uint32_t visual_map_high_color;
  const my_chart_mark_point_t* marks;
  size_t mark_count;
  const my_chart_mark_line_state_t* lines;
  size_t line_count;
  const my_chart_mark_area_state_t* areas;
  size_t area_count;
} my_chart_snapshot_t;

typedef struct my_chart_t {
  my_widget_t base;
  my_chart_mode_t mode;
  char title[96];
  const char* const* labels;
  size_t label_count;
  my_chart_series_t series[MY_CHART_MAX_SERIES];
  bool series_visible[MY_CHART_MAX_SERIES];
  size_t series_count;
  float grid_y_min[MY_CHART_MAX_GRIDS];
  float grid_y_max[MY_CHART_MAX_GRIDS];
  bool grid_range_set[MY_CHART_MAX_GRIDS];
  float grid_y2_min[MY_CHART_MAX_GRIDS];
  float grid_y2_max[MY_CHART_MAX_GRIDS];
  bool grid_range2_set[MY_CHART_MAX_GRIDS];
  float grid_left[MY_CHART_MAX_GRIDS];
  float grid_top[MY_CHART_MAX_GRIDS];
  float grid_width[MY_CHART_MAX_GRIDS];
  float grid_height[MY_CHART_MAX_GRIDS];
  bool grid_explicit[MY_CHART_MAX_GRIDS];
  bool grid_visible[MY_CHART_MAX_GRIDS];
  bool grid_link_axis_pointer[MY_CHART_MAX_GRIDS];
  size_t grid_count;
  unsigned char series_grid[MY_CHART_MAX_SERIES];
  unsigned char paint_grid;
  unsigned char hover_grid;
  bool show_legend;
  bool tooltip_enabled;
  bool stacked;
  float animation_progress;
  bool visual_map_set;
  float visual_map_min;
  float visual_map_max;
  uint32_t visual_map_low_color;
  uint32_t visual_map_high_color;
  bool brush_active;
  size_t brush_start;
  size_t brush_end;
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
my_ret_t my_chart_set_grid_count(my_widget_t* chart, size_t count);
size_t my_chart_get_grid_count(const my_widget_t* chart);
my_ret_t my_chart_set_grid(my_widget_t* chart, size_t index,
                           const my_chart_grid_desc_t* desc);
my_ret_t my_chart_set_grid_link(my_widget_t* chart, size_t grid, bool linked);
bool my_chart_get_grid_link(const my_widget_t* chart, size_t grid);
size_t my_chart_get_series_grid(const my_widget_t* chart, size_t series);
my_ret_t my_chart_get_grid_rect(const my_widget_t* chart, size_t index,
                                float* x, float* y, float* w, float* h);
my_ret_t my_chart_get_grid_range(const my_widget_t* chart, size_t index,
                                 unsigned axis, float* y_min, float* y_max);
size_t chart_grid_at(const my_widget_t* chart, int32_t local_x,
                     int32_t local_y);
my_ret_t my_chart_apply_snapshot(my_widget_t* chart,
                                 const my_chart_snapshot_t* snapshot);
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
/** @brief Set deterministic render progress for external animation drivers. */
my_ret_t my_chart_set_animation_progress(my_widget_t* chart, float progress);
float my_chart_get_animation_progress(const my_widget_t* chart);
my_ret_t my_chart_set_visual_map(my_widget_t* chart, float min_value,
                                 float max_value, uint32_t low_color,
                                 uint32_t high_color);
my_ret_t my_chart_clear_visual_map(my_widget_t* chart);
bool my_chart_has_visual_map(const my_widget_t* chart);
my_ret_t my_chart_get_brush(const my_widget_t* chart, size_t* start,
                            size_t* end);
my_ret_t my_chart_clear_brush(my_widget_t* chart);
my_ret_t my_chart_set_data_zoom(my_widget_t* chart, size_t start,
                                size_t end);
my_ret_t my_chart_clear_data_zoom(my_widget_t* chart);
bool my_chart_get_data_zoom(const my_widget_t* chart, size_t* start,
                             size_t* end);
/**
 * @brief Join a weak chart group for dataZoom synchronization.
 *
 * The fixed registry supports MY_CHART_GROUP_MAX_GROUPS groups with
 * MY_CHART_GROUP_MAX_CHARTS charts each. Joined charts automatically leave
 * the registry during destruction.
 */
my_ret_t my_chart_group_join(my_widget_t* chart, unsigned group_id);
/** @brief Leave a chart group explicitly. */
my_ret_t my_chart_group_leave(my_widget_t* chart);
/** @brief Return the number of charts joined to group_id. */
size_t my_chart_group_size(unsigned group_id);
/** @brief Notify peer charts after a successful dataZoom update. */
void my_chart_group_notify(my_widget_t* chart, size_t start, size_t end);
/** @brief Notify peer charts after clearing dataZoom. */
void my_chart_group_clear_notify(my_widget_t* chart);
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
size_t my_chart_hit_test(const my_widget_t* chart, int32_t local_x,
                         int32_t local_y);
my_ret_t my_chart_get_tooltip(const my_widget_t* chart, char* buffer,
                              size_t capacity);
my_ret_t my_chart_get_accessible_description(const my_widget_t* chart,
                                             char* buffer, size_t capacity);

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
