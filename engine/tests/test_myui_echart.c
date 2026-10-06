#include "test_framework.h"
#include "myui/echarts/my_echart.h"

TEST(echart_set_option_replace_and_lazy_update) {
  static const double a[] = {1.0, 2.0};
  static const double b[] = {3.0};
  my_echart_series_input_t sa = {"a", "A", MY_ECHART_LINE, a, 2u, 0u, 0u, NULL, true};
  my_echart_series_input_t sb = {"b", "B", MY_ECHART_BAR, b, 1u, 0u, 0u, NULL, true};
  my_echart_option_input_t first = {"one", NULL, 0u, &sa, 1u, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u};
  my_echart_option_input_t second = {"two", NULL, 0u, &sb, 1u, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u};
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
  my_echart_series_input_t series = {"sales", "Sales", MY_ECHART_LINE, values, 1u, 0u, 0u, NULL, true};
  my_echart_option_input_t input = {"one", NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u};
  my_echart_action_t action = {MY_ECHART_ACTION_LEGEND_UNSELECT, "sales"};
  my_echart_t* chart = my_echart_create(NULL);
  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_echart_set_option(chart, &input, true, false), MY_RET_OK);
  ASSERT_EQ(my_echart_model_dispatch_action(chart, &action), MY_RET_OK);
  ASSERT_FALSE(my_echart_get_option(chart)->series[0].show);
  action.type = MY_ECHART_ACTION_LEGEND_SELECT;
  ASSERT_EQ(my_echart_model_dispatch_action(chart, &action), MY_RET_OK);
  ASSERT_TRUE(my_echart_get_option(chart)->series[0].show);
  my_echart_destroy(chart);
}

TEST_MAIN_BEGIN()
  RUN_TEST(echart_set_option_replace_and_lazy_update);
  RUN_TEST(echart_legend_action_reduces_model_state);
TEST_MAIN_END()
