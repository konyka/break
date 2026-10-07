#include "test_framework.h"

#include "myui/widgets/my_chart.h"

static my_widget_t* create_chart(const float* values, size_t count) {
  my_chart_series_t series = {"series", values, count, 0xE85D75FFu, 0u};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);

  if (chart == NULL || my_chart_set_series(chart, 0u, &series) != MY_RET_OK) {
    my_widget_unref(chart);
    return NULL;
  }
  return chart;
}

TEST(chart_group_propagates_data_zoom) {
  static const float a_values[] = {1, 2, 3, 4, 5, 6};
  static const float b_values[] = {1, 2, 3};
  my_widget_t* chart_a = create_chart(a_values, 6u);
  my_widget_t* chart_b = create_chart(b_values, 3u);
  size_t start = 0u;
  size_t end = 0u;

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  ASSERT_EQ(my_chart_group_join(chart_a, 1u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_b, 1u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_size(1u), 2u);
  ASSERT_EQ(my_chart_set_data_zoom(chart_a, 1u, 4u), MY_RET_OK);
  ASSERT_TRUE(my_chart_get_data_zoom(chart_a, &start, &end));
  ASSERT_EQ(start, 1u);
  ASSERT_EQ(end, 4u);
  ASSERT_TRUE(my_chart_get_data_zoom(chart_b, &start, &end));
  ASSERT_EQ(start, 1u);
  ASSERT_EQ(end, 4u);
  ASSERT_EQ(my_chart_clear_data_zoom(chart_a), MY_RET_OK);
  ASSERT_FALSE(my_chart_get_data_zoom(chart_b, NULL, NULL));
  ASSERT_EQ(my_chart_group_leave(chart_a), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_b), MY_RET_OK);
  my_widget_unref(chart_a);
  my_widget_unref(chart_b);
}

TEST(chart_group_auto_leaves_on_destroy) {
  static const float values[] = {1, 2, 3};
  my_widget_t* chart_a = create_chart(values, 3u);
  my_widget_t* chart_b = create_chart(values, 3u);

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  ASSERT_EQ(my_chart_group_join(chart_a, 7u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_b, 7u), MY_RET_OK);
  my_widget_unref(chart_a);
  ASSERT_EQ(my_chart_group_size(7u), 1u);
  ASSERT_EQ(my_chart_set_data_zoom(chart_b, 0u, 2u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_b), MY_RET_OK);
  my_widget_unref(chart_b);
}

TEST(chart_group_leave_stops_data_zoom_propagation) {
  static const float values[] = {1, 2, 3, 4};
  my_widget_t* chart_a = create_chart(values, 4u);
  my_widget_t* chart_b = create_chart(values, 4u);

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  ASSERT_EQ(my_chart_group_join(chart_a, 1u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_b, 1u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_b), MY_RET_OK);
  ASSERT_EQ(my_chart_group_size(1u), 1u);
  ASSERT_EQ(my_chart_set_data_zoom(chart_a, 1u, 3u), MY_RET_OK);
  ASSERT_FALSE(my_chart_get_data_zoom(chart_b, NULL, NULL));
  ASSERT_EQ(my_chart_group_leave(chart_a), MY_RET_OK);
  ASSERT_EQ(my_chart_group_size(1u), 0u);
  my_widget_unref(chart_a);
  my_widget_unref(chart_b);
}

TEST(chart_groups_are_isolated_and_rejoin_moves_membership) {
  static const float values[] = {1, 2, 3, 4};
  my_widget_t* chart_a = create_chart(values, 4u);
  my_widget_t* chart_b = create_chart(values, 4u);
  my_widget_t* chart_c = create_chart(values, 4u);

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  ASSERT_NOT_NULL(chart_c);
  ASSERT_EQ(my_chart_group_join(chart_a, 1u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_b, 2u), MY_RET_OK);
  ASSERT_EQ(my_chart_set_data_zoom(chart_a, 1u, 3u), MY_RET_OK);
  ASSERT_FALSE(my_chart_get_data_zoom(chart_b, NULL, NULL));
  ASSERT_EQ(my_chart_group_join(chart_c, 1u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_c, 2u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_size(1u), 1u);
  ASSERT_EQ(my_chart_group_size(2u), 2u);
  ASSERT_EQ(my_chart_group_leave(chart_a), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_b), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_c), MY_RET_OK);
  my_widget_unref(chart_a);
  my_widget_unref(chart_b);
  my_widget_unref(chart_c);
}

TEST(chart_group_rejects_null_charts) {
  ASSERT_EQ(my_chart_group_join(NULL, 1u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_group_leave(NULL), MY_RET_INVALID_PARAMS);
}

TEST(chart_group_propagates_hover) {
  static const float values[] = {1, 2, 3};
  my_widget_t* chart_a = create_chart(values, 3u);
  my_widget_t* chart_b = create_chart(values, 3u);
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  chart_a->rect.w = 320;
  chart_a->rect.h = 180;
  chart_b->rect.w = 320;
  chart_b->rect.h = 180;
  ASSERT_EQ(my_chart_group_join(chart_a, 3u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_b, 3u), MY_RET_OK);
  event.u.pointer.x = 180;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart_a->vtable->on_event(chart_a, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart_a), 1u);
  ASSERT_EQ(my_chart_get_hover_index(chart_b), 1u);
  ASSERT_EQ(my_chart_group_leave(chart_a), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_b), MY_RET_OK);
  my_widget_unref(chart_a);
  my_widget_unref(chart_b);
}

TEST(chart_group_propagates_hover_clear) {
  static const float values[] = {1, 2, 3};
  my_widget_t* chart_a = create_chart(values, 3u);
  my_widget_t* chart_b = create_chart(values, 3u);
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  chart_a->rect.w = 320;
  chart_a->rect.h = 180;
  chart_b->rect.w = 320;
  chart_b->rect.h = 180;
  ASSERT_EQ(my_chart_group_join(chart_a, 4u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_b, 4u), MY_RET_OK);
  event.u.pointer.x = 180;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart_a->vtable->on_event(chart_a, &event), MY_RET_OK);
  event.u.pointer.x = 0;
  event.u.pointer.y = 0;
  ASSERT_EQ(chart_a->vtable->on_event(chart_a, &event), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart_a), SIZE_MAX);
  ASSERT_EQ(my_chart_get_hover_index(chart_b), SIZE_MAX);
  ASSERT_EQ(my_chart_group_leave(chart_a), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_b), MY_RET_OK);
  my_widget_unref(chart_a);
  my_widget_unref(chart_b);
}

TEST(chart_group_propagates_funnel_hover) {
  static const float values[] = {100.0f, 60.0f, 30.0f};
  my_chart_series_t series = {"series", values, 3u, 0xE85D75FFu, 0u};
  my_widget_t* chart_a = my_chart_create(NULL, MY_CHART_FUNNEL);
  my_widget_t* chart_b = my_chart_create(NULL, MY_CHART_FUNNEL);
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  chart_a->rect.w = 320;
  chart_a->rect.h = 180;
  chart_b->rect.w = 320;
  chart_b->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart_a, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart_b, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_a, 7u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_b, 7u), MY_RET_OK);
  event.u.pointer.x = 175;
  event.u.pointer.y = 92;
  ASSERT_EQ(chart_a->vtable->on_event(chart_a, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart_b), 1u);
  event.u.pointer.x = 10;
  event.u.pointer.y = 10;
  ASSERT_EQ(chart_a->vtable->on_event(chart_a, &event), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart_b), SIZE_MAX);
  ASSERT_EQ(my_chart_group_leave(chart_a), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_b), MY_RET_OK);
  my_widget_unref(chart_a);
  my_widget_unref(chart_b);
}

TEST(chart_group_hover_does_not_affect_ungrouped_chart) {
  static const float values[] = {1, 2, 3};
  my_widget_t* chart_a = create_chart(values, 3u);
  my_widget_t* chart_b = create_chart(values, 3u);
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  chart_a->rect.w = 320;
  chart_a->rect.h = 180;
  chart_b->rect.w = 320;
  chart_b->rect.h = 180;
  ASSERT_EQ(my_chart_group_join(chart_a, 5u), MY_RET_OK);
  event.u.pointer.x = 180;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart_a->vtable->on_event(chart_a, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart_a), 1u);
  ASSERT_EQ(my_chart_get_hover_index(chart_b), SIZE_MAX);
  ASSERT_EQ(my_chart_group_leave(chart_a), MY_RET_OK);
  my_widget_unref(chart_a);
  my_widget_unref(chart_b);
}

TEST(chart_group_clears_shorter_peer_hover) {
  static const float long_values[] = {1, 2, 3, 4, 5};
  static const float short_values[] = {1, 2};
  my_widget_t* chart_a = create_chart(long_values, 5u);
  my_widget_t* chart_b = create_chart(short_values, 2u);

  ASSERT_NOT_NULL(chart_a);
  ASSERT_NOT_NULL(chart_b);
  ASSERT_EQ(my_chart_group_join(chart_a, 6u), MY_RET_OK);
  ASSERT_EQ(my_chart_group_join(chart_b, 6u), MY_RET_OK);
  ASSERT_EQ(my_chart_set_hover_index(chart_a, 4u), MY_RET_OK);
  my_chart_group_hover_notify(chart_a, 4u);
  ASSERT_EQ(my_chart_get_hover_index(chart_a), 4u);
  ASSERT_EQ(my_chart_get_hover_index(chart_b), SIZE_MAX);
  ASSERT_EQ(my_chart_group_leave(chart_a), MY_RET_OK);
  ASSERT_EQ(my_chart_group_leave(chart_b), MY_RET_OK);
  my_widget_unref(chart_a);
  my_widget_unref(chart_b);
}

TEST_MAIN_BEGIN()
  RUN_TEST(chart_group_propagates_data_zoom);
  RUN_TEST(chart_group_leave_stops_data_zoom_propagation);
  RUN_TEST(chart_groups_are_isolated_and_rejoin_moves_membership);
  RUN_TEST(chart_group_rejects_null_charts);
  RUN_TEST(chart_group_auto_leaves_on_destroy);
  RUN_TEST(chart_group_propagates_hover);
  RUN_TEST(chart_group_propagates_hover_clear);
  RUN_TEST(chart_group_propagates_funnel_hover);
  RUN_TEST(chart_group_hover_does_not_affect_ungrouped_chart);
  RUN_TEST(chart_group_clears_shorter_peer_hover);
TEST_MAIN_END()
