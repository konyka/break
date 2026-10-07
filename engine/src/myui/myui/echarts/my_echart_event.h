#ifndef MY_ECHART_EVENT_H
#define MY_ECHART_EVENT_H

#include "myc/my_mem.h"
#include "myc/my_error.h"
#include "mypal/my_event.h"

#include <stddef.h>
#include <stdint.h>

#define MY_ECHART_INDEX_NONE SIZE_MAX
#define MY_ECHART_SUBSCRIPTION_INVALID ((my_echart_subscription_t)0u)

typedef enum my_echart_event_type_t {
  MY_ECHART_EVENT_ANY = 0,
  MY_ECHART_EVENT_POINTER_DOWN,
  MY_ECHART_EVENT_POINTER_MOVE,
  MY_ECHART_EVENT_POINTER_UP,
  MY_ECHART_EVENT_WHEEL,
  MY_ECHART_EVENT_KEY_LEFT,
  MY_ECHART_EVENT_KEY_RIGHT
} my_echart_event_type_t;

/** Semantic event payload. Series/data/category indexes are optional hints. */
typedef struct my_echart_event_t {
  my_echart_event_type_t type;
  uint64_t time_ms;
  int32_t x;
  int32_t y;
  int32_t delta;
  uint8_t button;
  uint8_t modifiers;
  size_t series_index;
  size_t data_index;
  size_t category_index;
} my_echart_event_t;

typedef enum my_echart_action_type_t {
  MY_ECHART_ACTION_HIGHLIGHT = 0,
  MY_ECHART_ACTION_LEGEND_SELECT,
  MY_ECHART_ACTION_DATA_ZOOM,
  MY_ECHART_ACTION_BRUSH,
  MY_ECHART_ACTION_SHOW_TIP,
  MY_ECHART_ACTION_HIDE_TIP
} my_echart_action_type_t;

typedef struct my_echart_action_t {
  my_echart_action_type_t type;
  size_t series_index;
  size_t data_index;
  size_t category_index;
  const char* name;
  double start;
  double end;
} my_echart_action_t;

typedef uint64_t my_echart_subscription_t;
typedef struct my_echart_t my_echart_t;
typedef struct my_echart_event_adapter_t my_echart_event_adapter_t;
typedef void (*my_echart_event_callback_t)(void*, const my_echart_event_t*);
typedef void (*my_echart_action_callback_t)(void*, const my_echart_action_t*);

my_echart_event_adapter_t* my_echart_event_adapter_create(
    const my_allocator_t* allocator);
void my_echart_event_adapter_destroy(my_echart_event_adapter_t* adapter);
my_ret_t my_echart_event_adapter_attach_model(my_echart_event_adapter_t* adapter,
                                              my_echart_t* model);
void my_echart_event_model_destroyed(my_echart_t* model);
my_echart_subscription_t my_echart_event_on(my_echart_event_adapter_t* adapter,
                                             my_echart_event_type_t type,
                                             my_echart_event_callback_t callback,
                                             void* user_data);
my_echart_subscription_t my_echart_action_on(my_echart_event_adapter_t* adapter,
                                              my_echart_action_callback_t callback,
                                              void* user_data);
my_ret_t my_echart_event_off(my_echart_event_adapter_t* adapter,
                             my_echart_subscription_t subscription);
my_ret_t my_echart_event_adapter_handle(my_echart_event_adapter_t* adapter,
                                         const my_event_t* event);
my_ret_t my_echart_dispatch_action(my_echart_event_adapter_t* adapter,
                                   const my_echart_action_t* action);

#endif
