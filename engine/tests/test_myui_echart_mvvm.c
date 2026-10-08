#include "test_framework.h"
#include "myui/echarts/my_echart_mvvm.h"
#include "mymvvm/my_view_model.h"
#include "myui/widgets/my_chart.h"
#include <string.h>
TEST(echart_mvvm_syncs_option_pointer) {
  static const double values[] = {1.0,2.0}; my_echart_series_input_t s = {"v", "Values", MY_ECHART_LINE, values, 2, 0, 0, NULL, true, NULL, false}; my_echart_option_input_t in = {"MVVM", NULL, 0, &s, 1, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u, false}; my_echart_option_t o; my_view_model_t* vm=my_view_model_dummy_create(NULL); my_binding_context_t* c=my_binding_context_create(NULL,vm); my_widget_t* w=my_chart_create(NULL,MY_CHART_LINE); my_echart_adapter_t* a; my_echart_mvvm_binding_t* b; my_value_t v;
  ASSERT_NOT_NULL(vm); ASSERT_NOT_NULL(c); ASSERT_NOT_NULL(w); my_echart_option_init(&o,NULL); ASSERT_EQ(my_echart_option_copy(&o,&in,NULL),MY_RET_OK); a=my_echart_adapter_create(w,NULL); ASSERT_NOT_NULL(a); my_value_init(&v,NULL); my_value_set_pointer(&v,&o); ASSERT_EQ(my_view_model_set_prop(vm,"option",&v),MY_RET_OK); b=my_echart_mvvm_bind_option(NULL,c,a,"option"); ASSERT_NOT_NULL(b); ASSERT_TRUE(strcmp(((my_chart_t*)w)->title,"MVVM")==0); my_echart_mvvm_unbind_option(b); my_value_reset(&v); my_echart_adapter_destroy(a); my_widget_unref(w); my_binding_context_destroy(c); my_view_model_unref(vm); my_echart_option_free(&o);
}
TEST(echart_mvvm_property_notification_updates_chart) {
  static const double values[] = {1.0};
  my_echart_series_input_t s = {"v", "V", MY_ECHART_LINE, values, 1, 0, 0, NULL, true, NULL, false};
  my_echart_option_input_t in = {"First", NULL, 0, &s, 1, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u, false};
  my_echart_option_t first, second;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_binding_context_t* c = my_binding_context_create(NULL, vm);
  my_widget_t* w = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* a;
  my_echart_mvvm_binding_t* b;
  my_value_t v;
  ASSERT_NOT_NULL(vm); ASSERT_NOT_NULL(c); ASSERT_NOT_NULL(w);
  my_echart_option_init(&first, NULL); my_echart_option_init(&second, NULL);
  ASSERT_EQ(my_echart_option_copy(&first, &in, NULL), MY_RET_OK);
  in.title = "Second";
  ASSERT_EQ(my_echart_option_copy(&second, &in, NULL), MY_RET_OK);
  a = my_echart_adapter_create(w, NULL); ASSERT_NOT_NULL(a);
  my_value_init(&v, NULL); my_value_set_pointer(&v, &first);
  ASSERT_EQ(my_view_model_set_prop(vm, "option", &v), MY_RET_OK);
  b = my_echart_mvvm_bind_option(NULL, c, a, "option"); ASSERT_NOT_NULL(b);
  my_value_reset(&v); my_value_init(&v, NULL); my_value_set_pointer(&v, &second);
  ASSERT_EQ(my_view_model_set_prop(vm, "option", &v), MY_RET_OK);
  ASSERT_TRUE(strcmp(((my_chart_t*)w)->title, "Second") == 0);
  my_echart_mvvm_unbind_option(b); my_value_reset(&v); my_echart_adapter_destroy(a);
  my_widget_unref(w); my_binding_context_destroy(c); my_view_model_unref(vm);
  my_echart_option_free(&first); my_echart_option_free(&second);
}
TEST(echart_mvvm_syncs_multi_grid_option) {
  static const double values[] = {1.0, 2.0, 3.0};
  static const size_t g0[] = {0u};
  static const size_t g1[] = {1u};
  my_echart_series_input_t series[] = {
      {"a", "A", MY_ECHART_LINE, values, 3, 0, 0, NULL, true, NULL, false},
      {"b", "B", MY_ECHART_LINE, values, 3, 0, 0, NULL, true, NULL,
       false}};
  my_echart_grid_input_t grids[] = {
      {.left = 0.05, .top = 0.05, .width = 0.9, .height = 0.4,
       .series_indices = g0, .series_count = 1u, .axis_count = 1u},
      {.left = 0.05, .top = 0.55, .width = 0.9, .height = 0.4,
       .series_indices = g1, .series_count = 1u, .axis_count = 1u}};
  my_echart_option_input_t in = {"MG", NULL, 0, series, 2, false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u, NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, grids, 2u, false};
  my_echart_option_t o;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_binding_context_t* c = my_binding_context_create(NULL, vm);
  my_widget_t* w = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* a;
  my_echart_mvvm_binding_t* b;
  my_value_t v;
  ASSERT_NOT_NULL(vm); ASSERT_NOT_NULL(c); ASSERT_NOT_NULL(w);
  my_echart_option_init(&o, NULL);
  ASSERT_EQ(my_echart_option_copy(&o, &in, NULL), MY_RET_OK);
  a = my_echart_adapter_create(w, NULL); ASSERT_NOT_NULL(a);
  my_value_init(&v, NULL); my_value_set_pointer(&v, &o);
  ASSERT_EQ(my_view_model_set_prop(vm, "option", &v), MY_RET_OK);
  b = my_echart_mvvm_bind_option(NULL, c, a, "option"); ASSERT_NOT_NULL(b);
  ASSERT_EQ((size_t)my_chart_get_grid_count(w), 2u);
  ASSERT_EQ((size_t)my_chart_get_series_grid(w, 1u), 1u);
  my_echart_mvvm_unbind_option(b); my_value_reset(&v);
  my_echart_adapter_destroy(a); my_widget_unref(w);
  my_binding_context_destroy(c); my_view_model_unref(vm);
  my_echart_option_free(&o);
}

TEST_MAIN_BEGIN()
RUN_TEST(echart_mvvm_syncs_option_pointer);
RUN_TEST(echart_mvvm_property_notification_updates_chart);
RUN_TEST(echart_mvvm_syncs_multi_grid_option);
TEST_MAIN_END()
