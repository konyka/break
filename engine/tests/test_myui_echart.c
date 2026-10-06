#include "test_framework.h"
#include "myui/echarts/my_echart.h"

#include <stdio.h>

TEST(echart_set_option_replace_and_lazy_update) {
  static const double a[] = {1.0, 2.0};
  static const double b[] = {3.0};
  my_echart_series_input_t sa = {"a", "A", MY_ECHART_LINE, a, 2u, 0u, 0u, NULL, true, NULL};
  my_echart_series_input_t sb = {"b", "B", MY_ECHART_BAR, b, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_option_input_t first = {"one", NULL, 0u, &sa, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0};
  my_echart_option_input_t second = {"two", NULL, 0u, &sb, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0};
  my_echart_t* chart = my_echart_create(NULL);

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_echart_set_option(chart, &first, true, false), MY_RET_OK);
  ASSERT_TRUE(strcmp(my_echart_get_option(chart)->title, "one") == 0);
  ASSERT_EQ(my_echart_set_option(chart, &second, true, true), MY_RET_OK);
  ASSERT_TRUE(strcmp(my_echart_get_option(chart)->title, "one") == 0);
  ASSERT_EQ(my_echart_flush(chart), MY_RET_OK);
  ASSERT_TRUE(strcmp(my_echart_get_option(chart)->title, "two") == 0);
  my_echart_destroy(chart);
}

TEST(echart_legend_action_reduces_model_state) {
  static const double values[] = {1.0};
  my_echart_series_input_t series = {"sales", "Sales", MY_ECHART_LINE, values, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_option_input_t input = {"one", NULL, 0u, &series, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0};
  my_echart_model_action_t action = {MY_ECHART_MODEL_ACTION_LEGEND_UNSELECT, "sales"};
  my_echart_t* chart = my_echart_create(NULL);
  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_echart_set_option(chart, &input, true, false), MY_RET_OK);
  ASSERT_EQ(my_echart_model_dispatch_action(chart, &action), MY_RET_OK);
  ASSERT_FALSE(my_echart_get_option(chart)->series[0].show);
  action.type = MY_ECHART_MODEL_ACTION_LEGEND_SELECT;
  ASSERT_EQ(my_echart_model_dispatch_action(chart, &action), MY_RET_OK);
  ASSERT_TRUE(my_echart_get_option(chart)->series[0].show);
  my_echart_destroy(chart);
}

TEST(echart_merge_appends_new_series) {
  static const double a[] = {1.0, 2.0};
  static const double b[] = {3.0};
  my_echart_series_input_t sa[2] = {
      {"a", "A", MY_ECHART_LINE, a, 2u, 0u, 0u, NULL, true, NULL},
      {"b", "B", MY_ECHART_LINE, b, 1u, 0u, 0u, NULL, true, NULL}};
  my_echart_option_input_t first = {"m", NULL, 0u, &sa[0], 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0};
  my_echart_option_input_t both = {"m2", NULL, 0u, sa, 2u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0};
  my_echart_t* chart = my_echart_create(NULL);
  const my_echart_option_t* option;

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_echart_set_option(chart, &first, true, false), MY_RET_OK);
  ASSERT_EQ(my_echart_set_option(chart, &both, false, false), MY_RET_OK);
  option = my_echart_get_option(chart);
  ASSERT_EQ(option->series_count, 2u);
  ASSERT_TRUE(strcmp(option->series[0].id, "a") == 0);
  ASSERT_TRUE(strcmp(option->series[1].id, "b") == 0);
  ASSERT_TRUE(strcmp(option->title, "m2") == 0);
  my_echart_destroy(chart);
}

TEST(echart_merge_rejects_capacity_overflow) {
  static const double v[] = {1.0};
  my_echart_series_input_t series[MY_ECHART_MAX_SERIES + 1u];
  my_echart_option_input_t input;
  my_echart_series_input_t first_series = {"s0", "S0", MY_ECHART_LINE, v, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_t* chart;
  char ids[MY_ECHART_MAX_SERIES + 1u][8];
  for (size_t i = 0u; i <= MY_ECHART_MAX_SERIES; i++) {
    snprintf(ids[i], sizeof(ids[i]), "s%zu", i);
    series[i] = (my_echart_series_input_t){ids[i], ids[i], MY_ECHART_LINE, v,
                                           1u, 0u, 0u, NULL, true, NULL};
  }
  input = (my_echart_option_input_t){"cap", NULL, 0u, series,
                                     MY_ECHART_MAX_SERIES + 1u, false, false,
                                     false, 0.0, 0.0, false, 0u, 0u, false,
                                     0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u,
                                     NULL, 0u, NULL, 0u,
                                     MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0};
  chart = my_echart_create(NULL);
  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_echart_set_option(chart, &input, true, false), MY_RET_INVALID_PARAMS);
  input.series_count = 1u;
  input.series = &first_series;
  ASSERT_EQ(my_echart_set_option(chart, &input, true, false), MY_RET_OK);
  input.series = series;
  input.series_count = MY_ECHART_MAX_SERIES + 1u;
  ASSERT_EQ(my_echart_set_option(chart, &input, false, false),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_echart_get_option(chart)->series_count, 1u);
  my_echart_destroy(chart);
}

TEST(echart_revision_tracks_committed_mutations) {
  static const double a[] = {1.0};
  my_echart_series_input_t sa = {"a", "A", MY_ECHART_LINE, a, 1u, 0u, 0u, NULL, true, NULL};
  my_echart_option_input_t input = {"r", NULL, 0u, &sa, 1u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0};
  my_echart_model_action_t action = {MY_ECHART_MODEL_ACTION_LEGEND_TOGGLE_SELECT, "a"};
  my_echart_t* chart = my_echart_create(NULL);
  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_echart_revision(chart), 0u);
  ASSERT_EQ(my_echart_set_option(chart, &input, true, false), MY_RET_OK);
  ASSERT_EQ(my_echart_revision(chart), 1u);
  ASSERT_EQ(my_echart_set_option(chart, &input, true, true), MY_RET_OK);
  ASSERT_EQ(my_echart_revision(chart), 1u);
  ASSERT_EQ(my_echart_flush(chart), MY_RET_OK);
  ASSERT_EQ(my_echart_revision(chart), 2u);
  ASSERT_EQ(my_echart_model_dispatch_action(chart, &action), MY_RET_OK);
  ASSERT_EQ(my_echart_revision(chart), 3u);
  ASSERT_EQ(my_echart_revision(NULL), 0u);
  my_echart_destroy(chart);
}

TEST(echart_remove_series_compacts_and_bumps_revision) {
  static const double a[] = {1.0};
  static const double b[] = {2.0};
  my_echart_series_input_t sa[2] = {
      {"a", "A", MY_ECHART_LINE, a, 1u, 0u, 0u, NULL, true, NULL},
      {"b", "B", MY_ECHART_LINE, b, 1u, 0u, 0u, NULL, true, NULL}};
  my_echart_option_input_t input = {"rm", NULL, 0u, sa, 2u, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0};
  my_echart_t* chart = my_echart_create(NULL);
  const my_echart_option_t* option;

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_echart_set_option(chart, &input, true, false), MY_RET_OK);
  ASSERT_EQ(my_echart_remove_series(chart, NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_echart_remove_series(chart, "zz"), MY_RET_NOT_FOUND);
  ASSERT_EQ(my_echart_remove_series(chart, "a"), MY_RET_OK);
  option = my_echart_get_option(chart);
  ASSERT_EQ(option->series_count, 1u);
  ASSERT_TRUE(strcmp(option->series[0].id, "b") == 0);
  ASSERT_EQ(my_echart_revision(chart), 2u);
  ASSERT_EQ(my_echart_remove_series(chart, "b"), MY_RET_OK);
  ASSERT_EQ(my_echart_get_option(chart)->series_count, 0u);
  ASSERT_EQ(my_echart_remove_series(chart, "b"), MY_RET_NOT_FOUND);
  my_echart_destroy(chart);
}

TEST_MAIN_BEGIN()
  RUN_TEST(echart_set_option_replace_and_lazy_update);
  RUN_TEST(echart_legend_action_reduces_model_state);
  RUN_TEST(echart_merge_appends_new_series);
  RUN_TEST(echart_merge_rejects_capacity_overflow);
  RUN_TEST(echart_revision_tracks_committed_mutations);
  RUN_TEST(echart_remove_series_compacts_and_bumps_revision);
TEST_MAIN_END()
