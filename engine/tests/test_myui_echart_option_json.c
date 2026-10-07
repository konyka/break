#include "test_framework.h"

#include <string.h>

#include "myui/echarts/my_echart_option.h"
#include "myui/echarts/my_echart_option_json.h"

TEST(echart_json_happy_path) {
  const char* json =
      "{\"title\":{\"text\":\"Revenue\"},\"xAxis\":{\"data\":[\"Q1\",\"Q2\"]},"
      "\"legend\":{\"show\":false},\"tooltip\":{\"show\":true},"
      "\"yAxis\":{\"min\":-2,\"max\":20},"
      "\"dataZoom\":[{\"startValue\":1,\"endValue\":8}],"
      "\"visualMap\":{\"min\":0,\"max\":100,\"inRange\":{\"color\":[\"#112233\",\"#AABBCCDD\"]}},"
      "\"grid\":[{\"left\":\"10%\",\"top\":0.2,\"width\":\"80%\",\"height\":\"70%\","
      "\"seriesIndices\":[0,1],\"yAxis\":{\"min\":-1,\"max\":11}}],"
      "\"series\":[{\"name\":\"Sales\",\"type\":\"line\",\"data\":[1,2,3],\"yAxisIndex\":1,\"itemStyle\":{\"color\":\"#123456\"}},"
      "{\"id\":\"cost\",\"type\":\"BAR\",\"data\":[4,5],\"show\":false,\"color\":4278190335}]}";
  my_echart_json_doc_t* doc = my_echart_json_doc_parse(json, strlen(json), NULL);
  const my_echart_option_input_t* input;
  my_echart_option_t copy;

  ASSERT_TRUE(doc != NULL);
  ASSERT_TRUE(my_echart_json_doc_error(doc) == NULL);
  input = my_echart_json_doc_option(doc);
  ASSERT_TRUE(input != NULL);
  ASSERT_TRUE(strcmp(input->title, "Revenue") == 0);
  ASSERT_EQ(input->x_axis_count, 2u);
  ASSERT_TRUE(input->legend_hidden);
  ASSERT_TRUE(!input->tooltip_hidden);
  ASSERT_EQ(input->series_count, 2u);
  ASSERT_TRUE(strcmp(input->series[0].id, "Sales") == 0);
  ASSERT_EQ(input->series[0].y_axis_index, 1u);
  ASSERT_EQ(input->series[1].type, MY_ECHART_BAR);
  ASSERT_TRUE(!input->series[1].show);
  ASSERT_TRUE(input->range_set);
  ASSERT_FLOAT_EQ((float)input->y_min, -2.0f, 1e-6f);
  ASSERT_TRUE(input->zoom_set);
  ASSERT_EQ(input->zoom_start, 1u);
  ASSERT_TRUE(input->visual_map_set);
  ASSERT_EQ(input->visual_map_low_color, 0x112233FFu);
  ASSERT_EQ(input->visual_map_high_color, 0xAABBCCDDu);
  ASSERT_EQ(input->grid_count, 1u);
  ASSERT_FLOAT_EQ((float)input->grids[0].left, 0.1f, 1e-6f);
  ASSERT_EQ(input->grids[0].series_count, 2u);
  ASSERT_TRUE(input->grids[0].axis_range_set[0]);
  ASSERT_EQ(my_echart_option_validate(input), MY_RET_OK);
  my_echart_option_init(&copy, NULL);
  ASSERT_EQ(my_echart_option_copy(&copy, input, NULL), MY_RET_OK);
  ASSERT_EQ(my_echart_option_validate(input), MY_RET_OK);
  my_echart_option_free(&copy);
  my_echart_json_doc_destroy(&doc);
  ASSERT_TRUE(doc == NULL);
}

TEST(echart_json_errors_and_destroy) {
  my_echart_json_doc_t* doc;
  doc = my_echart_json_doc_parse("{", 1u, NULL);
  ASSERT_TRUE(doc == NULL);
  doc = my_echart_json_doc_parse("{\"series\":[{\"type\":\"unknown\"}]}", strlen("{\"series\":[{\"type\":\"unknown\"}]}") , NULL);
  ASSERT_TRUE(doc != NULL);
  ASSERT_TRUE(my_echart_json_doc_error(doc) != NULL);
  my_echart_json_doc_destroy(&doc);
  doc = my_echart_json_doc_parse("{\"visualMap\":{\"inRange\":{\"color\":[\"nope\"]}}}", strlen("{\"visualMap\":{\"inRange\":{\"color\":[\"nope\"]}}}"), NULL);
  ASSERT_TRUE(doc != NULL);
  ASSERT_TRUE(my_echart_json_doc_error(doc) != NULL);
  my_echart_json_doc_destroy(&doc);
  doc = my_echart_json_doc_parse("{\"series\":[{\"data\":[NaN]}]}", strlen("{\"series\":[{\"data\":[NaN]}]}"), NULL);
  ASSERT_TRUE(doc == NULL || my_echart_json_doc_error(doc) != NULL);
  my_echart_json_doc_destroy(NULL);
}

TEST(echart_json_annotations_dataset_sort) {
  const char* json = "{\"series\":[{\"type\":\"line\",\"data\":[],\"markPoint\":{\"data\":[{\"coord\":[1,9],\"name\":\"peak\"}]},\"markLine\":{\"data\":[{\"yAxis\":42,\"name\":\"avg\",\"itemStyle\":{\"color\":\"#FF0000\"}}]},\"markArea\":{\"data\":[{\"yAxisRange\":[10,20],\"name\":\"band\",\"itemStyle\":{\"color\":\"#00FF0080\"}}]}}],\"dataset\":{\"source\":{\"sales\":[1,2,3],\"profit\":[4,5,6]}},\"transform\":{\"type\":\"sort\",\"config\":{\"dimension\":\"sales\",\"order\":\"desc\"}}}";
  my_echart_json_doc_t* doc = my_echart_json_doc_parse(json, strlen(json), NULL);
  const my_echart_option_input_t* input = my_echart_json_doc_option(doc);
  my_echart_option_t copy;
  ASSERT_TRUE(doc != NULL);
  ASSERT_TRUE(my_echart_json_doc_error(doc) == NULL);
  ASSERT_EQ(input->mark_point_count, 1u);
  ASSERT_EQ(input->mark_points[0].series_index, 0u);
  ASSERT_EQ(input->mark_points[0].category_index, 1u);
  ASSERT_EQ(input->mark_line_count, 1u);
  ASSERT_EQ(input->mark_lines[0].color, 0xFF0000FFu);
  ASSERT_EQ(input->mark_area_count, 1u);
  ASSERT_EQ(input->mark_areas[0].color, 0x00FF0080u);
  ASSERT_EQ(input->dataset_count, 2u);
  ASSERT_TRUE(strcmp(input->dataset[0].name, "sales") == 0);
  ASSERT_EQ(input->transform, MY_ECHART_TRANSFORM_SORT_DESC);
  my_echart_option_init(&copy, NULL);
  ASSERT_EQ(my_echart_option_copy(&copy, input, NULL), MY_RET_OK);
  ASSERT_EQ(my_echart_option_validate(input), MY_RET_OK);
  my_echart_option_free(&copy);
  my_echart_json_doc_destroy(&doc);
}

TEST(echart_json_dataset_filter) {
  const char* json = "{\"dataset\":{\"source\":{\"profit\":[1,5,8]}},\"transform\":{\"type\":\"filter\",\"config\":{\"dimension\":\"profit\",\"op\":\"gt\",\"value\":4}}}";
  my_echart_json_doc_t* doc = my_echart_json_doc_parse(json, strlen(json), NULL);
  const my_echart_option_input_t* input = my_echart_json_doc_option(doc);
  ASSERT_TRUE(doc != NULL);
  ASSERT_TRUE(my_echart_json_doc_error(doc) == NULL);
  ASSERT_EQ(input->transform, MY_ECHART_TRANSFORM_FILTER);
  ASSERT_EQ(input->filter_op, MY_ECHART_FILTER_GT);
  ASSERT_FLOAT_EQ((float)input->filter_value, 4.0f, 1e-6f);
  my_echart_json_doc_destroy(&doc);
}

TEST(echart_json_annotation_and_dataset_errors) {
  my_echart_json_doc_t* doc;
  doc = my_echart_json_doc_parse("{\"series\":[{\"markPoint\":{\"data\":[{\"coord\":[1]}]}}]}", strlen("{\"series\":[{\"markPoint\":{\"data\":[{\"coord\":[1]}]}}]}"), NULL);
  ASSERT_TRUE(doc != NULL); ASSERT_TRUE(my_echart_json_doc_error(doc) != NULL); my_echart_json_doc_destroy(&doc);
  doc = my_echart_json_doc_parse("{\"transform\":{\"type\":\"filter\",\"config\":{\"dimension\":\"x\",\"op\":\"wat\",\"value\":1}}}", strlen("{\"transform\":{\"type\":\"filter\",\"config\":{\"dimension\":\"x\",\"op\":\"wat\",\"value\":1}}}"), NULL);
  ASSERT_TRUE(doc != NULL); ASSERT_TRUE(my_echart_json_doc_error(doc) != NULL); my_echart_json_doc_destroy(&doc);
  doc = my_echart_json_doc_parse("{\"dataset\":{\"source\":{\"x\":[1,\"bad\"]}}}", strlen("{\"dataset\":{\"source\":{\"x\":[1,\"bad\"]}}}"), NULL);
  ASSERT_TRUE(doc != NULL); ASSERT_TRUE(my_echart_json_doc_error(doc) != NULL); my_echart_json_doc_destroy(&doc);
}

TEST_MAIN_BEGIN()
  RUN_TEST(echart_json_happy_path);
  RUN_TEST(echart_json_errors_and_destroy);
  RUN_TEST(echart_json_annotations_dataset_sort);
  RUN_TEST(echart_json_dataset_filter);
  RUN_TEST(echart_json_annotation_and_dataset_errors);
TEST_MAIN_END()
