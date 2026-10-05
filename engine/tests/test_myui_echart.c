#include "test_framework.h"
#include "myui/echarts/my_echart.h"

TEST(echart_set_option_replace_and_lazy_update) {
  static const double a[] = {1.0, 2.0};
  static const double b[] = {3.0};
  my_echart_series_input_t sa = {"a", "A", MY_ECHART_LINE, a, 2u, 0u, 0u, NULL, true};
  my_echart_series_input_t sb = {"b", "B", MY_ECHART_BAR, b, 1u, 0u, 0u, NULL, true};
  my_echart_option_input_t first = {"one", NULL, 0u, &sa, 1u};
  my_echart_option_input_t second = {"two", NULL, 0u, &sb, 1u};
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

TEST_MAIN_BEGIN()
  RUN_TEST(echart_set_option_replace_and_lazy_update);
TEST_MAIN_END()
