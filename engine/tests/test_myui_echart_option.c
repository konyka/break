#include "test_framework.h"

#include <math.h>
#include <string.h>

#include "myui/echarts/my_echart_option.h"

TEST(echart_option_copies_owned_data) {
  static const double values[] = {1.0, 2.5};
  static const char* labels[] = {"A", "B"};
  my_echart_series_input_t series = {"sales", "Sales", MY_ECHART_LINE,
                                     values, 2u, 0xE85D75FFu, 0u, NULL, true};
  my_echart_option_input_t input = {"Dashboard", labels, 2u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u};
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
  my_echart_series_input_t series = {"id", "name", MY_ECHART_LINE, NULL,
                                     1u, 0u, 0u, NULL, true};
  input.series = &series;
  input.series_count = 1u;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  series.data = (const double[]){NAN};
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}

TEST(echart_option_copies_component_state) {
  static const double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 6u,
                                     0u, 0u, NULL, true};
  my_echart_option_input_t input = {"comp", NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u};
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
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 1u,
                                     0u, 0u, NULL, true};
  my_echart_option_input_t input = {"comp", NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u};

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
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 1u,
                                     0u, 0u, NULL, true};
  my_echart_option_input_t input = {"vm", NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u};
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
  my_echart_series_input_t series = {"z", "Z", MY_ECHART_LINE, values, 1u,
                                     0u, 0u, NULL, true};
  my_echart_option_input_t input = {"vm", NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u};

  input.visual_map_set = true;
  input.visual_map_min = 50.0;
  input.visual_map_max = 50.0;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
  input.visual_map_min = 60.0;
  input.visual_map_max = 50.0;
  ASSERT_EQ(my_echart_option_validate(&input), MY_RET_INVALID_PARAMS);
}

TEST_MAIN_BEGIN()
  RUN_TEST(echart_option_copies_owned_data);
  RUN_TEST(echart_option_rejects_invalid_input);
  RUN_TEST(echart_option_copies_component_state);
  RUN_TEST(echart_option_rejects_invalid_component_state);
  RUN_TEST(echart_option_copies_visual_map_state);
  RUN_TEST(echart_option_rejects_invalid_visual_map);
TEST_MAIN_END()
