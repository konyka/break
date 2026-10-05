#include "test_framework.h"

#include <string.h>

#include "myui/echarts/my_echart_event.h"

typedef struct event_log_t {
  size_t event_count;
  size_t action_count;
  my_echart_event_t event;
  my_echart_action_t action;
  my_echart_event_adapter_t* adapter;
  my_echart_subscription_t subscription;
} event_log_t;

static void on_event(void* user_data, const my_echart_event_t* event) {
  event_log_t* log = (event_log_t*)user_data;
  log->event = *event;
  log->event_count++;
}

static void on_action(void* user_data, const my_echart_action_t* action) {
  event_log_t* log = (event_log_t*)user_data;
  log->action = *action;
  log->action_count++;
}

static void remove_self(void* user_data, const my_echart_action_t* action) {
  event_log_t* log = (event_log_t*)user_data;
  (void)action;
  log->action_count++;
  ASSERT_EQ(my_echart_event_off(log->adapter, log->subscription), MY_RET_OK);
}

static void destroy_adapter(void* user_data, const my_echart_action_t* action) {
  event_log_t* log = (event_log_t*)user_data;
  (void)action;
  log->action_count++;
  my_echart_event_adapter_destroy(log->adapter);
}

TEST(echart_event_maps_pointer_and_key_payloads) {
  my_echart_event_adapter_t* adapter = my_echart_event_adapter_create(NULL);
  event_log_t log = {0};
  my_echart_subscription_t subscription;
  my_event_t native_event;

  ASSERT_NOT_NULL(adapter);
  subscription = my_echart_event_on(adapter, MY_ECHART_EVENT_ANY, on_event, &log);
  ASSERT_TRUE(subscription != MY_ECHART_SUBSCRIPTION_INVALID);

  native_event = my_event_init(MY_EVENT_POINTER_DOWN);
  native_event.time_ms = 11u;
  native_event.u.pointer.x = 20;
  native_event.u.pointer.y = 30;
  native_event.u.pointer.button = 1u;
  native_event.u.pointer.modifiers = MY_KEYMOD_SHIFT;
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event_count, 1u);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_POINTER_DOWN);
  ASSERT_EQ(log.event.x, 20);
  ASSERT_EQ(log.event.y, 30);
  ASSERT_EQ(log.event.button, 1u);
  ASSERT_EQ(log.event.modifiers, MY_KEYMOD_SHIFT);
  ASSERT_EQ(log.event.time_ms, 11u);

  native_event = my_event_init(MY_EVENT_KEY_DOWN);
  native_event.u.key.key = MY_KEY_RIGHT;
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_KEY_RIGHT);

  native_event = my_event_init(MY_EVENT_POINTER_MOVE);
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_POINTER_MOVE);
  native_event = my_event_init(MY_EVENT_POINTER_UP);
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_POINTER_UP);
  native_event = my_event_init(MY_EVENT_KEY_DOWN);
  native_event.u.key.key = MY_KEY_LEFT;
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_KEY_LEFT);
  my_echart_event_adapter_destroy(adapter);
}

TEST(echart_event_maps_wheel_and_coordinates) {
  my_echart_event_adapter_t* adapter = my_echart_event_adapter_create(NULL);
  event_log_t log = {0};
  my_event_t native_event = my_event_init(MY_EVENT_POINTER_WHEEL);

  ASSERT_NOT_NULL(adapter);
  ASSERT_TRUE(my_echart_event_on(adapter, MY_ECHART_EVENT_WHEEL, on_event, &log) !=
              MY_ECHART_SUBSCRIPTION_INVALID);
  native_event.u.pointer.x = 4;
  native_event.u.pointer.y = 8;
  native_event.u.pointer.delta = -3;
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_WHEEL);
  ASSERT_EQ(log.event.x, 4);
  ASSERT_EQ(log.event.y, 8);
  ASSERT_EQ(log.event.delta, -3);
  my_echart_event_adapter_destroy(adapter);
}

TEST(echart_event_maps_move_up_and_left_key) {
  my_echart_event_adapter_t* adapter = my_echart_event_adapter_create(NULL);
  event_log_t log = {0};
  my_event_t native_event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(adapter);
  ASSERT_TRUE(my_echart_event_on(adapter, MY_ECHART_EVENT_ANY, on_event, &log) !=
              MY_ECHART_SUBSCRIPTION_INVALID);
  native_event.u.pointer.x = -4;
  native_event.u.pointer.y = 9;
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_POINTER_MOVE);
  ASSERT_EQ(log.event.x, -4);
  ASSERT_EQ(log.event.y, 9);

  native_event = my_event_init(MY_EVENT_POINTER_UP);
  native_event.u.pointer.button = 3u;
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_POINTER_UP);
  ASSERT_EQ(log.event.button, 3u);

  native_event = my_event_init(MY_EVENT_KEY_DOWN);
  native_event.u.key.key = MY_KEY_LEFT;
  ASSERT_EQ(my_echart_event_adapter_handle(adapter, &native_event), MY_RET_OK);
  ASSERT_EQ(log.event.type, MY_ECHART_EVENT_KEY_LEFT);
  my_echart_event_adapter_destroy(adapter);
}

TEST(echart_event_action_dispatch_and_safe_lifecycle) {
  my_echart_event_adapter_t* adapter = my_echart_event_adapter_create(NULL);
  event_log_t log = {0};
  my_echart_subscription_t subscription;
  my_echart_action_t action = {0};

  ASSERT_NOT_NULL(adapter);
  subscription = my_echart_action_on(adapter, on_action, &log);
  ASSERT_TRUE(subscription != MY_ECHART_SUBSCRIPTION_INVALID);
  action.type = MY_ECHART_ACTION_DATA_ZOOM;
  action.series_index = 2u;
  action.data_index = 5u;
  action.start = 10.0;
  action.end = 80.0;
  ASSERT_EQ(my_echart_dispatch_action(adapter, &action), MY_RET_OK);
  ASSERT_EQ(log.action_count, 1u);
  ASSERT_EQ(log.action.type, MY_ECHART_ACTION_DATA_ZOOM);
  ASSERT_EQ(log.action.series_index, 2u);
  ASSERT_FLOAT_EQ((float)log.action.start, 10.0f, 1e-6f);

  ASSERT_EQ(my_echart_event_off(adapter, subscription), MY_RET_OK);
  ASSERT_EQ(my_echart_dispatch_action(adapter, &action), MY_RET_OK);
  ASSERT_EQ(log.action_count, 1u);
  my_echart_event_adapter_destroy(adapter);
}

TEST(echart_event_rejects_unknown_types) {
  my_echart_event_adapter_t* adapter = my_echart_event_adapter_create(NULL);
  event_log_t log = {0};
  my_echart_action_t action = {0};

  ASSERT_NOT_NULL(adapter);
  ASSERT_EQ(my_echart_event_on(adapter, (my_echart_event_type_t)99, on_event,
                               &log), MY_ECHART_SUBSCRIPTION_INVALID);
  action.type = (my_echart_action_type_t)99;
  ASSERT_EQ(my_echart_dispatch_action(adapter, &action), MY_RET_INVALID_PARAMS);
  my_echart_event_adapter_destroy(adapter);
}

TEST(echart_event_dispatches_all_supported_actions) {
  static const my_echart_action_type_t types[] = {
      MY_ECHART_ACTION_HIGHLIGHT, MY_ECHART_ACTION_LEGEND_SELECT,
      MY_ECHART_ACTION_DATA_ZOOM, MY_ECHART_ACTION_BRUSH,
      MY_ECHART_ACTION_SHOW_TIP, MY_ECHART_ACTION_HIDE_TIP};
  my_echart_event_adapter_t* adapter = my_echart_event_adapter_create(NULL);
  event_log_t log = {0};
  my_echart_action_t action = {0};
  size_t i;

  ASSERT_NOT_NULL(adapter);
  ASSERT_TRUE(my_echart_action_on(adapter, on_action, &log) !=
              MY_ECHART_SUBSCRIPTION_INVALID);
  for (i = 0u; i < sizeof(types) / sizeof(types[0]); i++) {
    action.type = types[i];
    ASSERT_EQ(my_echart_dispatch_action(adapter, &action), MY_RET_OK);
    ASSERT_EQ(log.action.type, types[i]);
  }
  ASSERT_EQ(log.action_count, sizeof(types) / sizeof(types[0]));
  my_echart_event_adapter_destroy(adapter);
}

TEST(echart_event_callback_can_remove_itself) {
  my_echart_event_adapter_t* adapter = my_echart_event_adapter_create(NULL);
  event_log_t log = {0};
  my_echart_action_t action = {0};

  ASSERT_NOT_NULL(adapter);
  log.adapter = adapter;
  log.subscription = my_echart_action_on(adapter, remove_self, &log);
  ASSERT_TRUE(log.subscription != MY_ECHART_SUBSCRIPTION_INVALID);
  ASSERT_EQ(my_echart_dispatch_action(adapter, &action), MY_RET_OK);
  ASSERT_EQ(my_echart_dispatch_action(adapter, &action), MY_RET_OK);
  ASSERT_EQ(log.action_count, 1u);
  my_echart_event_adapter_destroy(adapter);
}

TEST(echart_event_destroy_stops_remaining_callbacks) {
  my_echart_event_adapter_t* adapter = my_echart_event_adapter_create(NULL);
  event_log_t log = {0};
  my_echart_action_t action = {0};

  ASSERT_NOT_NULL(adapter);
  log.adapter = adapter;
  ASSERT_TRUE(my_echart_action_on(adapter, on_action, &log) !=
              MY_ECHART_SUBSCRIPTION_INVALID);
  ASSERT_TRUE(my_echart_action_on(adapter, destroy_adapter, &log) !=
              MY_ECHART_SUBSCRIPTION_INVALID);
  ASSERT_EQ(my_echart_dispatch_action(adapter, &action), MY_RET_OK);
  ASSERT_EQ(log.action_count, 1u);
}

TEST_MAIN_BEGIN()
  RUN_TEST(echart_event_maps_pointer_and_key_payloads);
  RUN_TEST(echart_event_maps_wheel_and_coordinates);
  RUN_TEST(echart_event_maps_move_up_and_left_key);
  RUN_TEST(echart_event_action_dispatch_and_safe_lifecycle);
  RUN_TEST(echart_event_rejects_unknown_types);
  RUN_TEST(echart_event_dispatches_all_supported_actions);
  RUN_TEST(echart_event_callback_can_remove_itself);
  RUN_TEST(echart_event_destroy_stops_remaining_callbacks);
TEST_MAIN_END()
