#ifndef MY_ECHART_OPTION_H
#define MY_ECHART_OPTION_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

#define MY_ECHART_MAX_SERIES 8u
#define MY_ECHART_MAX_TITLE 128u
#define MY_ECHART_MAX_ID 64u
#define MY_ECHART_MAX_MARK_POINTS 8u
#define MY_ECHART_MAX_MARK_LINES 4u
#define MY_ECHART_MAX_MARK_AREAS 4u
#define MY_ECHART_MAX_AXES_PER_GRID 3u

typedef enum my_echart_series_type_t {
  MY_ECHART_LINE = 0,
  MY_ECHART_BAR,
  MY_ECHART_SCATTER,
  MY_ECHART_PIE,
  MY_ECHART_RADAR,
  MY_ECHART_FUNNEL,
  MY_ECHART_HEATMAP,
  MY_ECHART_BOXPLOT,
  MY_ECHART_CANDLESTICK,
  MY_ECHART_GAUGE,
  MY_ECHART_SANKEY,
  MY_ECHART_PARALLEL,
  MY_ECHART_TREEMAP,
  MY_ECHART_GRAPH,
  MY_ECHART_CALENDAR,
  MY_ECHART_THEME_RIVER
} my_echart_series_type_t;

typedef enum my_echart_transform_t {
  MY_ECHART_TRANSFORM_NONE = 0,
  MY_ECHART_TRANSFORM_SORT_ASC,
  MY_ECHART_TRANSFORM_SORT_DESC,
  MY_ECHART_TRANSFORM_FILTER
} my_echart_transform_t;

typedef enum my_echart_filter_op_t {
  MY_ECHART_FILTER_EQ = 0,
  MY_ECHART_FILTER_NE,
  MY_ECHART_FILTER_GT,
  MY_ECHART_FILTER_GE,
  MY_ECHART_FILTER_LT,
  MY_ECHART_FILTER_LE
} my_echart_filter_op_t;

typedef struct my_echart_dimension_input_t {
  const char* name;
  const double* values;
  size_t count;
} my_echart_dimension_input_t;

typedef struct my_echart_series_input_t {
  const char* id;
  const char* name;
  my_echart_series_type_t type;
  const double* data;
  size_t data_count;
  uint32_t color;
  unsigned y_axis_index;
  const char* stack;
  bool show;
  const char* dataset_dimension;
  bool label_show;
} my_echart_series_input_t;

typedef struct my_echart_mark_point_input_t {
  size_t series_index;
  size_t category_index;
  const char* label;
} my_echart_mark_point_input_t;

typedef struct my_echart_mark_line_input_t {
  double value;
  const char* label;
  uint32_t color;
} my_echart_mark_line_input_t;

typedef struct my_echart_mark_area_input_t {
  double y_min;
  double y_max;
  const char* label;
  uint32_t color;
} my_echart_mark_area_input_t;

#define MY_ECHART_MAX_GRIDS 4u

typedef struct my_echart_grid_input_t {
  double left;
  double top;
  double width;
  double height;
  const size_t* series_indices;
  size_t series_count;
  bool axis_range_set[MY_ECHART_MAX_AXES_PER_GRID];
  double axis_min[MY_ECHART_MAX_AXES_PER_GRID];
  double axis_max[MY_ECHART_MAX_AXES_PER_GRID];
  size_t axis_count;
  bool link_axis_pointer;
} my_echart_grid_input_t;

typedef struct my_echart_option_input_t {
  const char* title;
  const char* const* x_axis_data;
  size_t x_axis_count;
  const my_echart_series_input_t* series;
  size_t series_count;
  bool legend_hidden;
  bool tooltip_hidden;
  bool range_set;
  double y_min;
  double y_max;
  bool zoom_set;
  size_t zoom_start;
  size_t zoom_end;
  bool visual_map_set;
  double visual_map_min;
  double visual_map_max;
  uint32_t visual_map_low_color;
  uint32_t visual_map_high_color;
  const my_echart_mark_point_input_t* mark_points;
  size_t mark_point_count;
  const my_echart_mark_line_input_t* mark_lines;
  size_t mark_line_count;
  const my_echart_mark_area_input_t* mark_areas;
  size_t mark_area_count;
  const my_echart_dimension_input_t* dataset;
  size_t dataset_count;
  my_echart_transform_t transform;
  const char* transform_dimension;
  my_echart_filter_op_t filter_op;
  const char* filter_dimension;
  double filter_value;
  const my_echart_grid_input_t* grids;
  size_t grid_count;
  bool zoom_slider;
} my_echart_option_input_t;

typedef struct my_echart_series_t {
  char* id;
  char* name;
  my_echart_series_type_t type;
  double* data;
  size_t data_count;
  uint32_t color;
  unsigned y_axis_index;
  char* stack;
  bool show;
  bool label_show;
} my_echart_series_t;

typedef struct my_echart_mark_point_t {
  size_t series_index;
  size_t category_index;
  char* label;
} my_echart_mark_point_t;

typedef struct my_echart_mark_line_t {
  double value;
  char* label;
  uint32_t color;
} my_echart_mark_line_t;

typedef struct my_echart_mark_area_t {
  double y_min;
  double y_max;
  char* label;
  uint32_t color;
} my_echart_mark_area_t;

typedef struct my_echart_grid_t {
  double left;
  double top;
  double width;
  double height;
  size_t* series_indices;
  size_t series_count;
  bool axis_range_set[MY_ECHART_MAX_AXES_PER_GRID];
  double axis_min[MY_ECHART_MAX_AXES_PER_GRID];
  double axis_max[MY_ECHART_MAX_AXES_PER_GRID];
  size_t axis_count;
  bool link_axis_pointer;
} my_echart_grid_t;

typedef struct my_echart_option_t {
  const my_allocator_t* allocator;
  char* title;
  char** x_axis_data;
  size_t x_axis_count;
  my_echart_series_t* series;
  size_t series_count;
  bool legend_hidden;
  bool tooltip_hidden;
  bool range_set;
  double y_min;
  double y_max;
  bool zoom_set;
  size_t zoom_start;
  size_t zoom_end;
  bool visual_map_set;
  double visual_map_min;
  double visual_map_max;
  uint32_t visual_map_low_color;
  uint32_t visual_map_high_color;
  my_echart_mark_point_t* mark_points;
  size_t mark_point_count;
  my_echart_mark_line_t* mark_lines;
  size_t mark_line_count;
  my_echart_mark_area_t* mark_areas;
  size_t mark_area_count;
  my_echart_grid_t* grids;
  size_t grid_count;
  bool zoom_slider;
} my_echart_option_t;

void my_echart_option_init(my_echart_option_t* option,
                           const my_allocator_t* allocator);
void my_echart_option_free(my_echart_option_t* option);
my_ret_t my_echart_option_copy(my_echart_option_t* dst,
                               const my_echart_option_input_t* src,
                               const my_allocator_t* allocator);
my_ret_t my_echart_option_validate(const my_echart_option_input_t* input);

#endif
