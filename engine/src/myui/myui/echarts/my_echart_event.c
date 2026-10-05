#include "myui/echarts/my_echart_event.h"

typedef enum subscription_kind_t { SUB_EVENT, SUB_ACTION } subscription_kind_t;
typedef struct subscription_t {
  struct subscription_t* next;
  my_echart_subscription_t id;
  subscription_kind_t kind;
  my_echart_event_type_t event_type;
  void* user_data;
  bool active;
  union {
    my_echart_event_callback_t event_callback;
    my_echart_action_callback_t action_callback;
  } callback;
} subscription_t;

struct my_echart_event_adapter_t {
  const my_allocator_t* allocator;
  subscription_t* subscriptions;
  my_echart_subscription_t next_id;
  unsigned dispatch_depth;
  bool destroyed;
};

static void free_subscriptions(my_echart_event_adapter_t* adapter) {
  subscription_t* current = adapter->subscriptions;
  while (current != NULL) {
    subscription_t* next = current->next;
    my_mem_free(adapter->allocator, current);
    current = next;
  }
  adapter->subscriptions = NULL;
}

static void collect_inactive(my_echart_event_adapter_t* adapter) {
  subscription_t** link = &adapter->subscriptions;
  while (*link != NULL) {
    if (!(*link)->active) {
      subscription_t* removed = *link;
      *link = removed->next;
      my_mem_free(adapter->allocator, removed);
    } else {
      link = &(*link)->next;
    }
  }
}

static bool is_event_type_valid(my_echart_event_type_t type) {
  return type == MY_ECHART_EVENT_ANY ||
         (type >= MY_ECHART_EVENT_POINTER_DOWN &&
          type <= MY_ECHART_EVENT_KEY_RIGHT);
}

static bool is_action_type_valid(my_echart_action_type_t type) {
  return type <= MY_ECHART_ACTION_HIDE_TIP;
}

my_echart_event_adapter_t* my_echart_event_adapter_create(
    const my_allocator_t* allocator) {
  my_echart_event_adapter_t* adapter =
      (my_echart_event_adapter_t*)my_mem_calloc(allocator, 1u, sizeof(*adapter));
  if (adapter != NULL) {
    adapter->allocator = allocator;
    adapter->next_id = 1u;
  }
  return adapter;
}

void my_echart_event_adapter_destroy(my_echart_event_adapter_t* adapter) {
  if (adapter == NULL || adapter->destroyed) return;
  adapter->destroyed = true;
  if (adapter->dispatch_depth == 0u) {
    free_subscriptions(adapter);
    my_mem_free(adapter->allocator, adapter);
  }
}

static my_echart_subscription_t add_event_subscription(
    my_echart_event_adapter_t* adapter, my_echart_event_type_t type,
    my_echart_event_callback_t callback, void* user_data) {
  subscription_t* subscription;
  if (adapter == NULL || adapter->destroyed || callback == NULL ||
      !is_event_type_valid(type))
    return 0u;
  subscription = (subscription_t*)my_mem_calloc(adapter->allocator, 1u,
                                                 sizeof(*subscription));
  if (subscription == NULL) return 0u;
  subscription->id = adapter->next_id++;
  if (subscription->id == 0u) subscription->id = adapter->next_id++;
  subscription->kind = SUB_EVENT;
  subscription->event_type = type;
  subscription->user_data = user_data;
  subscription->active = true;
  subscription->callback.event_callback = callback;
  subscription->next = adapter->subscriptions;
  adapter->subscriptions = subscription;
  return subscription->id;
}

static my_echart_subscription_t add_action_subscription(
    my_echart_event_adapter_t* adapter, my_echart_action_callback_t callback,
    void* user_data) {
  subscription_t* subscription;
  if (adapter == NULL || adapter->destroyed || callback == NULL) return 0u;
  subscription = (subscription_t*)my_mem_calloc(adapter->allocator, 1u,
                                                 sizeof(*subscription));
  if (subscription == NULL) return 0u;
  subscription->id = adapter->next_id++;
  if (subscription->id == 0u) subscription->id = adapter->next_id++;
  subscription->kind = SUB_ACTION;
  subscription->user_data = user_data;
  subscription->active = true;
  subscription->callback.action_callback = callback;
  subscription->next = adapter->subscriptions;
  adapter->subscriptions = subscription;
  return subscription->id;
}

my_echart_subscription_t my_echart_event_on(my_echart_event_adapter_t* adapter,
                                             my_echart_event_type_t type,
                                             my_echart_event_callback_t callback,
                                             void* user_data) {
  return add_event_subscription(adapter, type, callback, user_data);
}

my_echart_subscription_t my_echart_action_on(my_echart_event_adapter_t* adapter,
                                              my_echart_action_callback_t callback,
                                              void* user_data) {
  return add_action_subscription(adapter, callback, user_data);
}

my_ret_t my_echart_event_off(my_echart_event_adapter_t* adapter,
                             my_echart_subscription_t subscription) {
  subscription_t** link;
  if (adapter == NULL || adapter->destroyed || subscription == 0u)
    return MY_RET_INVALID_PARAMS;
  link = &adapter->subscriptions;
  while (*link != NULL) {
    if ((*link)->id == subscription) {
      subscription_t* removed = *link;
      if (adapter->dispatch_depth != 0u) {
        removed->active = false;
      } else {
        *link = removed->next;
        my_mem_free(adapter->allocator, removed);
      }
      return MY_RET_OK;
    }
    link = &(*link)->next;
  }
  return MY_RET_NOT_FOUND;
}

static my_echart_event_type_t map_type(const my_event_t* event) {
  if (event->type == MY_EVENT_POINTER_DOWN) return MY_ECHART_EVENT_POINTER_DOWN;
  if (event->type == MY_EVENT_POINTER_MOVE) return MY_ECHART_EVENT_POINTER_MOVE;
  if (event->type == MY_EVENT_POINTER_UP) return MY_ECHART_EVENT_POINTER_UP;
  if (event->type == MY_EVENT_POINTER_WHEEL) return MY_ECHART_EVENT_WHEEL;
  if (event->type == MY_EVENT_KEY_DOWN && event->u.key.key == MY_KEY_LEFT)
    return MY_ECHART_EVENT_KEY_LEFT;
  if (event->type == MY_EVENT_KEY_DOWN && event->u.key.key == MY_KEY_RIGHT)
    return MY_ECHART_EVENT_KEY_RIGHT;
  return MY_ECHART_EVENT_ANY;
}

my_ret_t my_echart_event_adapter_handle(my_echart_event_adapter_t* adapter,
                                         const my_event_t* event) {
  my_echart_event_t semantic;
  subscription_t* current;
  if (adapter == NULL || event == NULL || adapter->destroyed)
    return MY_RET_INVALID_PARAMS;
  semantic.type = map_type(event);
  if (semantic.type == MY_ECHART_EVENT_ANY) return MY_RET_NOT_FOUND;
  semantic.time_ms = event->time_ms;
  semantic.x = 0;
  semantic.y = 0;
  semantic.delta = 0;
  semantic.button = 0u;
  if (event->type == MY_EVENT_KEY_DOWN) {
    semantic.modifiers = event->u.key.modifiers;
  } else {
    semantic.x = event->u.pointer.x;
    semantic.y = event->u.pointer.y;
    semantic.delta = event->u.pointer.delta;
    semantic.button = event->u.pointer.button;
    semantic.modifiers = event->u.pointer.modifiers;
  }
  semantic.series_index = MY_ECHART_INDEX_NONE;
  semantic.data_index = MY_ECHART_INDEX_NONE;
  semantic.category_index = MY_ECHART_INDEX_NONE;
  adapter->dispatch_depth++;
  current = adapter->subscriptions;
  while (current != NULL && !adapter->destroyed) {
    subscription_t* next = current->next;
    if (current->active && current->kind == SUB_EVENT &&
        (current->event_type == MY_ECHART_EVENT_ANY ||
         current->event_type == semantic.type))
      current->callback.event_callback(current->user_data, &semantic);
    current = next;
  }
  adapter->dispatch_depth--;
  if (adapter->dispatch_depth == 0u) collect_inactive(adapter);
  if (adapter->destroyed && adapter->dispatch_depth == 0u) {
    free_subscriptions(adapter);
    my_mem_free(adapter->allocator, adapter);
  }
  return MY_RET_OK;
}

my_ret_t my_echart_dispatch_action(my_echart_event_adapter_t* adapter,
                                   const my_echart_action_t* action) {
  subscription_t* current;
  if (adapter == NULL || action == NULL || adapter->destroyed ||
      !is_action_type_valid(action->type))
    return MY_RET_INVALID_PARAMS;
  adapter->dispatch_depth++;
  current = adapter->subscriptions;
  while (current != NULL && !adapter->destroyed) {
    subscription_t* next = current->next;
    if (current->active && current->kind == SUB_ACTION)
      current->callback.action_callback(current->user_data, action);
    current = next;
  }
  adapter->dispatch_depth--;
  if (adapter->dispatch_depth == 0u) collect_inactive(adapter);
  if (adapter->destroyed && adapter->dispatch_depth == 0u) {
    free_subscriptions(adapter);
    my_mem_free(adapter->allocator, adapter);
  }
  return MY_RET_OK;
}
