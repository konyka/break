#include "test_framework.h"

#include <math.h>
#include <string.h>

#include "myui/echarts/my_echart_option.h"

TEST(echart_option_copies_owned_data) {
  static const double values[] = {1.0, 2.5};
  static const char* labels[] = {"A", "B"};
  my_echart_series_input_t series = {"sales", "Sales", MY_ECHART_LINE, values, 2u, 0xE85D75FFu, 0u, NULL, true, NULL};
  my_echart_option_input_t input = {"Dashboard", labels, 2u, &series, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
  my_echart_option_t option;

  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_TRUE(strcmp(option.title, "Dashboard") == 0);
  ASSERT_TRUE(strcmp(option.series[0].id, "sales") == 0);
  ASSERT_FLOAT_EQ((float)option.series[0].data[1], 2.5f, 1e-6f);
  my_echart_option_free(&option);
}

TEST(echart_option_rejects_invalid_input) {
  my_echart_option_input_t input = {0};
  my_echart_series_input_t series = {"id", "name", MY_ECHART_LINE, NULL, 1u, 0u, 0u, NULL, true, NULL};
  input.series = &series;
  input.series_count = 1u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  series.data = (const double[]){NAN};
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}

TEST(echart_option_copies_component_state) {
  static const double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 6u, 0u, 0u, NULL, true, NULL};
  my_echart_option_input_t input = {"comp", NULL, 0u, &series, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
  my_echart_option_t option;

  input.legend_hidden = true;
  input.range_set = true;
  input.y_min = -2.5;
  input.y_max = 7.5;
  input.zoom_set = true;
  input.zoom_start = 1u;
  input.zoom_end = 4u;

  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_TRUE(option.legend_hidden);
  ASSERT_TRUE(option.range_set);
  ASSERT_FLOAT_EQ((float)option.y_min, -2.5f, 1e-6f);
  ASSERT_FLOAT_EQ((float)option.y_max, 7.5f, 1e-6f);
  ASSERT_TRUE(option.zoom_set);
  ASSERT_EQ(option.zoom_start, 1u);
  ASSERT_EQ(option.zoom_end, 4u);
  my_echart_option_free(&option);
}

TEST(echart_option_rejects_invalid_component_state) {
  static const double values[] = {1.0};
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_option_input_t input = {"comp", NULL, 0u, &series, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};

  input.range_set = true;
  input.y_min = 5.0;
  input.y_max = 5.0;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  input.range_set = false;

  input.zoom_set = true;
  input.zoom_start = 3u;
  input.zoom_end = 3u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  input.zoom_end = 2u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  input.zoom_set = false;
}

TEST(echart_option_copies_visual_map_state) {
  static const double values[] = {1.0};
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_option_input_t input = {"vm", NULL, 0u, &series, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
  my_echart_option_t option;

  input.visual_map_set = true;
  input.visual_map_min = -10.0;
  input.visual_map_max = 90.0;
  input.visual_map_low_color = 0x0000FFFFu;
  input.visual_map_high_color = 0xFF0000FFu;

  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_TRUE(option.visual_map_set);
  ASSERT_FLOAT_EQ((float)option.visual_map_min, -10.0f, 1e-6f);
  ASSERT_FLOAT_EQ((float)option.visual_map_max, 90.0f, 1e-6f);
  ASSERT_EQ(option.visual_map_low_color, 0x0000FFFFu);
  ASSERT_EQ(option.visual_map_high_color, 0xFF0000FFu);
  my_echart_option_free(&option);
}

TEST(echart_option_rejects_invalid_visual_map) {
  static const double values[] = {1.0};
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_option_input_t input = {"vm", NULL, 0u, &series, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};

  input.visual_map_set = true;
  input.visual_map_min = 50.0;
  input.visual_map_max = 50.0;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  input.visual_map_min = 60.0;
  input.visual_map_max = 50.0;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}

TEST(echart_option_copies_annotations) {
  static const double values[] = {1.0, 2.0, 3.0};
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 3u, 0u, 0u, NULL, true, NULL};
  my_echart_mark_point_input_t points[] = {{0u, 1u, "peak"}, {0u, 2u, NULL}};
  my_echart_mark_line_input_t lines[] = {{42.0, "target", 0xE85D75FFu}};
  my_echart_mark_area_input_t areas[] = {{10.0, 30.0, "band", 0x3A86FF44u}};
  my_echart_option_input_t input = {"ann", NULL, 0u, &series, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
  my_echart_option_t option;

  input.mark_points = points;
  input.mark_point_count = 2u;
  input.mark_lines = lines;
  input.mark_line_count = 1u;
  input.mark_areas = areas;
  input.mark_area_count = 1u;

  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_EQ(option.mark_point_count, 2u);
  ASSERT_TRUE(strcmp(option.mark_points[0].label, "peak") == 0);
  ASSERT_TRUE(option.mark_points[1].label == NULL);
  ASSERT_EQ(option.mark_line_count, 1u);
  ASSERT_FLOAT_EQ((float)option.mark_lines[0].value, 42.0f, 1e-6f);
  ASSERT_TRUE(strcmp(option.mark_lines[0].label, "target") == 0);
  ASSERT_EQ(option.mark_area_count, 1u);
  ASSERT_FLOAT_EQ((float)option.mark_areas[0].y_min, 10.0f, 1e-6f);
  ASSERT_TRUE(strcmp(option.mark_areas[0].label, "band") == 0);
  my_echart_option_free(&option);
}

TEST(echart_option_rejects_invalid_annotations) {
  static const double values[] = {1.0};
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_mark_line_input_t lines[] = {{NAN, "bad", 0u}};
  my_echart_mark_area_input_t areas[] = {{30.0, 10.0, "bad", 0u}};
  my_echart_option_input_t input = {"ann", NULL, 0u, &series, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};

  input.mark_lines = lines;
  input.mark_line_count = 1u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);

  input.mark_lines = NULL;
  input.mark_line_count = 0u;
  input.mark_areas = areas;
  input.mark_area_count = 1u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}

TEST(echart_option_copies_tooltip_hidden) {
  static const double values[] = {1.0};
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_option_input_t input = {"tt", NULL, 0u, &series, 1u,
                                     false, false, false, 0.0, 0.0, false,
                                     0u, 0u, false, 0.0, 0.0, 0u, 0u,
                                     NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
  my_echart_option_t option;
  input.tooltip_hidden = true;
  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_TRUE(option.tooltip_hidden);
  my_echart_option_free(&option);
}

TEST(echart_option_resolves_dataset_dimensions) {
  static const double revenue[] = {10.0, 20.0, 30.0};
  static const double orders[] = {1.0, 2.0, 3.0};
  my_echart_dimension_input_t dims[2] = {
      {"revenue", revenue, 3u}, {"orders", orders, 3u}};
  my_echart_series_input_t by_dim = {"s", "S", MY_ECHART_LINE, NULL, 0u, 0u,
                                     0u, NULL, true, "orders"};
  my_echart_series_input_t inline_data = {"t", "T", MY_ECHART_LINE, revenue,
                                          3u, 0u, 0u, NULL, true, NULL};
  my_echart_series_input_t both[2] = {by_dim, inline_data};
  my_echart_option_input_t input = {"ds", NULL, 0u, both, 2u,
                                    false, false, false, 0.0, 0.0, false, 0u,
                                    0u, false, 0.0, 0.0, 0u, 0u,
                                    NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
  my_echart_option_t option;

  input.dataset = dims;
  input.dataset_count = 2u;
  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_EQ(option.series[0].data_count, 3u);
  ASSERT_FLOAT_EQ((float)option.series[0].data[0], 1.0, 1e-6f);
  ASSERT_FLOAT_EQ((float)option.series[0].data[2], 3.0, 1e-6f);
  ASSERT_EQ(option.series[1].data_count, 3u);
  ASSERT_FLOAT_EQ((float)option.series[1].data[2], 30.0, 1e-6f);
  my_echart_option_free(&option);
}

TEST(echart_option_rejects_invalid_dataset) {
  static const double revenue[] = {10.0, 20.0};
  my_echart_dimension_input_t dims[1] = {{"revenue", revenue, 2u}};
  my_echart_series_input_t missing = {"s", "S", MY_ECHART_LINE, NULL, 0u, 0u,
                                      0u, NULL, true, "unknown"};
  my_echart_series_input_t dup_source[1] = {{"s", "S", MY_ECHART_LINE, NULL,
                                             0u, 0u, 0u, NULL, true, "revenue"}};
  my_echart_dimension_input_t dup_dims[2] = {
      {"revenue", revenue, 2u}, {"revenue", revenue, 2u}};
  my_echart_dimension_input_t nan_dims[1] = {
      {"revenue", (const double[]){NAN, 1.0}, 2u}};
  my_echart_option_input_t input = {"ds", NULL, 0u, &missing, 1u,
                                    false, false, false, 0.0, 0.0, false, 0u,
                                    0u, false, 0.0, 0.0, 0u, 0u,
                                    NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};

  input.dataset = dims;
  input.dataset_count = 1u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);

  input.series = dup_source;
  input.dataset = dup_dims;
  input.dataset_count = 2u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);

  input.dataset = nan_dims;
  input.dataset_count = 1u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);

  input.dataset = NULL;
  input.dataset_count = 1u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}

TEST(echart_option_sorts_dataset_rows) {
  static const double keys[] = {3.0, 1.0, 2.0};
  static const double vals[] = {30.0, 10.0, 20.0};
  my_echart_dimension_input_t dims[2] = {
      {"k", keys, 3u}, {"v", vals, 3u}};
  my_echart_series_input_t series = {"s", "S", MY_ECHART_LINE, NULL, 0u, 0u,
                                     0u, NULL, true, "v"};
  my_echart_option_input_t input = {"sort", NULL, 0u, &series, 1u,
                                    false, false, false, 0.0, 0.0, false, 0u,
                                    0u, false, 0.0, 0.0, 0u, 0u,
                                    NULL, 0u, NULL, 0u, NULL, 0u,
                                    NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
  my_echart_option_t option;

  input.dataset = dims;
  input.dataset_count = 2u;
  input.transform = MY_ECHART_TRANSFORM_SORT_ASC;
  input.transform_dimension = "k";
  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_EQ(option.series[0].data_count, 3u);
  ASSERT_FLOAT_EQ((float)option.series[0].data[0], 10.0, 1e-6f);
  ASSERT_FLOAT_EQ((float)option.series[0].data[1], 20.0, 1e-6f);
  ASSERT_FLOAT_EQ((float)option.series[0].data[2], 30.0, 1e-6f);
  my_echart_option_free(&option);

  input.transform = MY_ECHART_TRANSFORM_SORT_DESC;
  series.dataset_dimension = "k";
  input.series = &series;
  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_FLOAT_EQ((float)option.series[0].data[0], 3.0, 1e-6f);
  ASSERT_FLOAT_EQ((float)option.series[0].data[2], 1.0, 1e-6f);
  my_echart_option_free(&option);
}

TEST(echart_option_rejects_invalid_transform) {
  static const double keys[] = {3.0, 1.0};
  static const double ragged[] = {9.0};
  my_echart_dimension_input_t dims[2] = {
      {"k", keys, 2u}, {"rag", ragged, 1u}};
  my_echart_series_input_t series = {"s", "S", MY_ECHART_LINE, NULL, 0u, 0u,
                                     0u, NULL, true, "k"};
  my_echart_option_input_t input = {"sort", NULL, 0u, &series, 1u,
                                    false, false, false, 0.0, 0.0, false, 0u,
                                    0u, false, 0.0, 0.0, 0u, 0u,
                                    NULL, 0u, NULL, 0u, NULL, 0u,
                                    NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};

  input.dataset = dims;
  input.dataset_count = 2u;
  input.transform = MY_ECHART_TRANSFORM_SORT_ASC;
  input.transform_dimension = "missing";
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);

  input.transform_dimension = NULL;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);

  input.transform_dimension = "k";
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}

TEST(echart_option_filters_dataset_rows) {
  static const double keys[] = {1.0, 5.0, 3.0, 2.0};
  static const double vals[] = {10.0, 50.0, 30.0, 20.0};
  my_echart_dimension_input_t dims[2] = {
      {"k", keys, 4u}, {"v", vals, 4u}};
  my_echart_series_input_t series = {"s", "S", MY_ECHART_LINE, NULL, 0u, 0u,
                                     0u, NULL, true, "v"};
  my_echart_option_input_t input = {"f", NULL, 0u, &series, 1u,
                                    false, false, false, 0.0, 0.0, false, 0u,
                                    0u, false, 0.0, 0.0, 0u, 0u,
                                    NULL, 0u, NULL, 0u, NULL, 0u,
                                    NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL,
                                    MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
  my_echart_option_t option;

  input.dataset = dims;
  input.dataset_count = 2u;
  input.transform = MY_ECHART_TRANSFORM_FILTER;
  input.filter_dimension = "k";
  input.filter_op = MY_ECHART_FILTER_GT;
  input.filter_value = 2.0;
  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_EQ(option.series[0].data_count, 2u);
  ASSERT_FLOAT_EQ((float)option.series[0].data[0], 50.0, 1e-6f);
  ASSERT_FLOAT_EQ((float)option.series[0].data[1], 30.0, 1e-6f);
  my_echart_option_free(&option);

  input.filter_op = MY_ECHART_FILTER_LE;
  input.filter_value = 2.0;
  series.dataset_dimension = "k";
  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_EQ(option.series[0].data_count, 2u);
  ASSERT_FLOAT_EQ((float)option.series[0].data[0], 1.0, 1e-6f);
  ASSERT_FLOAT_EQ((float)option.series[0].data[1], 2.0, 1e-6f);
  my_echart_option_free(&option);
}

TEST(echart_option_rejects_invalid_filter) {
  static const double keys[] = {1.0, 2.0};
  my_echart_dimension_input_t dims[1] = {{"k", keys, 2u}};
  my_echart_series_input_t series = {"s", "S", MY_ECHART_LINE, NULL, 0u, 0u,
                                     0u, NULL, true, "k"};
  my_echart_option_input_t input = {"f", NULL, 0u, &series, 1u,
                                    false, false, false, 0.0, 0.0, false, 0u,
                                    0u, false, 0.0, 0.0, 0u, 0u,
                                    NULL, 0u, NULL, 0u, NULL, 0u,
                                    NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL,
                                    MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};

  input.dataset = dims;
  input.dataset_count = 1u;
  input.transform = MY_ECHART_TRANSFORM_FILTER;
  input.filter_dimension = "missing";
  input.filter_op = MY_ECHART_FILTER_EQ;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);

  input.filter_dimension = NULL;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}


TEST(echart_option_copies_multi_grid) {
  static const double values[] = {1.0, 2.0, 3.0};
  static const size_t grid0_series[] = {0u};
  static const size_t grid1_series[] = {1u};
  my_echart_series_input_t series[] = {
      {"a", "A", MY_ECHART_LINE, values, 3u, 0u, 0u, NULL, true, NULL},
      {"b", "B", MY_ECHART_LINE, values, 3u, 0u, 0u, NULL, true, NULL}};
  my_echart_grid_input_t grids[] = {
      {0.05, 0.05, 0.9, 0.4, grid0_series, 1u, true, 0.0, 10.0, false, 0.0,
       0.0, false},
      {0.05, 0.55, 0.9, 0.4, grid1_series, 1u, false, 0.0, 0.0, true, 0.0,
       5.0, false}};
  my_echart_option_input_t input = {"multi", NULL, 0u, series, 2u,
                                   false, false, false, 0.0, 0.0, false, 0u, 0u,
                                   false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u,
                                   NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE,
                                   NULL, MY_ECHART_FILTER_EQ, NULL, 0.0,
                                   grids, 2u};
  my_echart_option_t option;

  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  ASSERT_EQ(option.grid_count, 2u);
  ASSERT_FLOAT_EQ((float)option.grids[0].left, 0.05f, 1e-6f);
  ASSERT_EQ(option.grids[0].series_count, 1u);
  ASSERT_EQ(option.grids[0].series_indices[0], 0u);
  ASSERT_TRUE(option.grids[0].range_set);
  ASSERT_FLOAT_EQ((float)option.grids[1].y2_max, 5.0f, 1e-6f);
  my_echart_option_free(&option);
}

TEST(echart_option_rejects_invalid_multi_grid) {
  static const double values[] = {1.0, 2.0, 3.0};
  static const size_t series_idx[] = {0u};
  my_echart_series_input_t series[] = {
      {"a", "A", MY_ECHART_LINE, values, 3u, 0u, 0u, NULL, true, NULL},
      {"b", "B", MY_ECHART_LINE, values, 3u, 0u, 0u, NULL, true, NULL}};
  my_echart_grid_input_t grids[4];
  my_echart_option_input_t input = {"multi", NULL, 0u, series, 2u,
                                   false, false, false, 0.0, 0.0, false, 0u, 0u,
                                   false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u,
                                   NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE,
                                   NULL, MY_ECHART_FILTER_EQ, NULL, 0.0,
                                   grids, 2u};
  static const size_t series_idx1[] = {1u};
  memset(grids, 0, sizeof(grids));
  grids[0].left = 0.05; grids[0].top = 0.05;
  grids[0].width = 0.9; grids[0].height = 0.4;
  grids[0].series_indices = series_idx;
  grids[0].series_count = 1u;
  grids[1] = grids[0];
  grids[1].top = 0.55;
  grids[1].series_indices = series_idx1;

  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_OK);
  grids[0].left = -0.1;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  grids[0].left = 0.05;
  grids[0].width = 1.5;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  grids[0].width = 0.9;
  grids[0].height = NAN;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  grids[0].height = 0.4;
  grids[0].series_count = 1u;
  grids[0].series_indices = (const size_t[]){99u};
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  grids[0].series_indices = series_idx;
  grids[1].series_indices = (const size_t[]){0u};
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  grids[1].series_indices = series_idx;
  grids[0].range_set = true;
  grids[0].y_min = 10.0;
  grids[0].y_max = 0.0;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  grids[0].range_set = false;
  input.grid_count = 5u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  input.grid_count = 2u;
  input.grids = NULL;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  input.grids = grids;
  input.series_count = 1u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}

TEST_MAIN_BEGIN()
  RUN_TEST(echart_option_copies_owned_data);
  RUN_TEST(echart_option_copies_multi_grid);
  RUN_TEST(echart_option_rejects_invalid_multi_grid);
  RUN_TEST(echart_option_rejects_invalid_input);
  RUN_TEST(echart_option_copies_component_state);
  RUN_TEST(echart_option_rejects_invalid_component_state);
  RUN_TEST(echart_option_copies_visual_map_state);
  RUN_TEST(echart_option_rejects_invalid_visual_map);
  RUN_TEST(echart_option_copies_annotations);
  RUN_TEST(echart_option_rejects_invalid_annotations);
  RUN_TEST(echart_option_copies_tooltip_hidden);
  RUN_TEST(echart_option_resolves_dataset_dimensions);
  RUN_TEST(echart_option_rejects_invalid_dataset);
  RUN_TEST(echart_option_sorts_dataset_rows);
  RUN_TEST(echart_option_rejects_invalid_transform);
  RUN_TEST(echart_option_filters_dataset_rows);
  RUN_TEST(echart_option_rejects_invalid_filter);
TEST_MAIN_END()
