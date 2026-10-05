#include "test_framework.h"

#include <math.h>
#include <string.h>

#include "myui/echarts/my_echart_option.h"

TEST(echart_option_copies_owned_data) {
  static const double values[] = {1.0, 2.5};
  static const char* labels[] = {"A", "B"};
  my_echart_series_input_t series = {"sales", "Sales", MY_ECHART_LINE,
                                     values, 2u, 0xE85D75FFu, 0u, NULL, true};
  my_echart_option_input_t input = {"Dashboard", labels, 2u, &series, 1u};
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

TEST_MAIN_BEGIN()
  RUN_TEST(echart_option_copies_owned_data);
  RUN_TEST(echart_option_rejects_invalid_input);
TEST_MAIN_END()
