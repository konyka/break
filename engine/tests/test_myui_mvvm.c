#include "test_framework.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "mymvvm/my_binding_context.h"
#include "mymvvm/my_binding_rule.h"
#include "mymvvm/my_items_binding.h"
#include "mymvvm/my_navigator.h"
#include "mymvvm/my_view_model.h"
#include "mymvvm/my_view_model_array.h"
#include "mymvvm_myui/my_mvvm.h"
#include "myc/my_emitter.h"
#include "mymvvm_myui/my_widget_target.h"
#include "mypal/dummy/my_pal_dummy.h"
#include "myui/my_window_manager.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_list_view.h"

static my_view_model_t* make_row(void) {
  return my_view_model_dummy_create(NULL);
}

static my_widget_t* build_row(my_widget_t* parent, size_t index,
                              my_item_props_fn_t props, void* props_ctx,
                              void* builder_ctx) {
  (void)parent;
  (void)index;
  (void)props;
  (void)props_ctx;
  (void)builder_ctx;
  return my_label_create(NULL, "row");
}

static void set_pointer_property(my_view_model_t* vm, const char* name,
                                 void* pointer) {
  my_value_t value;
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_pointer(&value, pointer), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(vm, name, &value), MY_RET_OK);
  my_value_reset(&value);
}

static void set_none_property(my_view_model_t* vm, const char* name) {
  my_value_t value;
  my_value_init(&value, NULL);
  ASSERT_EQ(my_view_model_set_prop(vm, name, &value), MY_RET_OK);
  my_value_reset(&value);
}

static void set_bool_property(my_view_model_t* vm, const char* name,
                              bool enabled) {
  my_value_t value;
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_bool(&value, enabled), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(vm, name, &value), MY_RET_OK);
  my_value_reset(&value);
}

static int g_async_nav_factory_calls;
static char g_async_nav_factory_args[MY_NAV_ARGS_LEN];
static int g_owned_page_context_destroy_count;
static my_window_t* g_existing_nav_window;
static int g_owned_template_context_destroy_count;

typedef struct navigator_page_lease_state_t {
  my_emitter_context_lease_t* lease;
  int factory_calls;
  int destroy_count;
  bool invalidate_in_factory;
} navigator_page_lease_state_t;

static my_window_t* async_nav_page_factory(my_pal_t* pal, const char* args,
                                            void* ctx) {
  my_window_t* win;
  (void)ctx;
  g_async_nav_factory_calls++;
  snprintf(g_async_nav_factory_args, sizeof(g_async_nav_factory_args), "%s",
           args != NULL ? args : "");
  win = my_window_create(NULL, pal, 160, 80, "async-nav");
  return win;
}

static void owned_page_context_destroy(void* ctx) {
  (void)ctx;
  g_owned_page_context_destroy_count++;
}

static void navigator_page_lease_destroy(void* ctx) {
  navigator_page_lease_state_t* state =
      (navigator_page_lease_state_t*)ctx;
  state->destroy_count++;
}

static my_window_t* navigator_page_lease_factory(my_pal_t* pal,
                                                 const char* args, void* ctx) {
  navigator_page_lease_state_t* state =
      (navigator_page_lease_state_t*)ctx;
  (void)args;
  state->factory_calls++;
  if (state->invalidate_in_factory) {
    my_emitter_context_lease_invalidate(state->lease);
  }
  return my_window_create(NULL, pal, 160, 80, "lease-nav");
}

static void owned_template_context_destroy(void* ctx) {
  (void)ctx;
  g_owned_template_context_destroy_count++;
}

typedef struct notify_self_remove_t {
  my_view_model_t* vm;
  my_view_model_array_t* array;
  bool called;
} notify_self_remove_t;

static void remove_vm_on_notify(void* ctx, const char* event, void* data) {
  notify_self_remove_t* state = (notify_self_remove_t*)ctx;
  (void)event;
  (void)data;
  state->called = true;
  if (state->vm != NULL) {
    my_view_model_unref(state->vm);
    state->vm = NULL;
  }
}

static void remove_array_on_notify(void* ctx, const char* event, void* data) {
  notify_self_remove_t* state = (notify_self_remove_t*)ctx;
  (void)event;
  (void)data;
  state->called = true;
  if (state->array != NULL) {
    my_view_model_array_unref(state->array);
    state->array = NULL;
  }
}

typedef struct quiet_test_vm_t {
  my_view_model_t base;
  my_value_t title;
  bool show_marker;
  my_view_model_array_t* rows;
} quiet_test_vm_t;

static void quiet_test_vm_destroy(my_object_t* object);

static my_ret_t quiet_test_vm_get_prop(my_view_model_t* vm, const char* name,
                                       my_value_t* value) {
  quiet_test_vm_t* quiet = (quiet_test_vm_t*)vm;
  if (strcmp(name, "title") == 0) {
    return my_value_copy(value, &quiet->title);
  }
  if (strcmp(name, "show_marker") == 0) {
    return my_value_set_bool(value, quiet->show_marker);
  }
  if (strcmp(name, "rows") == 0) {
    return my_value_set_pointer(value, quiet->rows);
  }
  return MY_RET_NOT_FOUND;
}

static my_ret_t quiet_test_vm_set_prop(my_view_model_t* vm, const char* name,
                                       const my_value_t* value) {
  quiet_test_vm_t* quiet = (quiet_test_vm_t*)vm;
  if (strcmp(name, "title") == 0) {
    my_value_reset(&quiet->title);
    my_value_init(&quiet->title, NULL);
    if (my_value_copy(&quiet->title, value) != MY_RET_OK) {
      return MY_RET_OOM;
    }
  } else if (strcmp(name, "show_marker") == 0 &&
             value->type == MY_VALUE_BOOL) {
    quiet->show_marker = my_value_get_bool(value);
  } else if (strcmp(name, "rows") == 0 &&
             value->type == MY_VALUE_POINTER) {
    quiet->rows = (my_view_model_array_t*)my_value_get_pointer(value);
  } else {
    return MY_RET_NOT_FOUND;
  }
  return my_view_model_notify_change(vm, name);
}

static const my_view_model_vtable_t QUIET_TEST_VM_VTABLE = {
    quiet_test_vm_get_prop, quiet_test_vm_set_prop, NULL, NULL};

static quiet_test_vm_t* quiet_test_vm_create(const char* title) {
  quiet_test_vm_t* quiet =
      (quiet_test_vm_t*)my_mem_calloc(NULL, 1u, sizeof(*quiet));
  if (quiet == NULL ||
      my_view_model_init(&quiet->base, NULL, &QUIET_TEST_VM_VTABLE) !=
          MY_RET_OK) {
    my_mem_free(NULL, quiet);
    return NULL;
  }
  my_value_init(&quiet->title, NULL);
  if (my_value_set_str(&quiet->title, title) != MY_RET_OK) {
    my_view_model_unref(&quiet->base);
    return NULL;
  }
  ((my_object_t*)quiet)->destroy = quiet_test_vm_destroy;
  return quiet;
}

static void quiet_test_vm_destroy(my_object_t* object) {
  quiet_test_vm_t* quiet = (quiet_test_vm_t*)object;
  my_value_reset(&quiet->title);
  my_view_model_destroy(&quiet->base);
  my_object_destroy(object);
}

static my_window_t* existing_nav_page_factory(my_pal_t* pal, const char* args,
                                               void* ctx) {
  (void)pal;
  (void)args;
  (void)ctx;
  return g_existing_nav_window != NULL
             ? (my_window_t*)my_widget_ref((my_widget_t*)g_existing_nav_window)
             : NULL;
}

typedef struct reentrant_nav_factory_state_t {
  my_navigator_wm_t* navigator;
  int calls;
} reentrant_nav_factory_state_t;

static my_window_t* reentrant_nav_page_factory(my_pal_t* pal, const char* args,
                                                void* ctx) {
  reentrant_nav_factory_state_t* state =
      (reentrant_nav_factory_state_t*)ctx;
  my_window_t* window;
  (void)args;
  state->calls++;
  window = my_window_create(NULL, pal, 160, 80, "reentrant-nav");
  my_navigator_wm_destroy(state->navigator);
  state->navigator = NULL;
  return window;
}

typedef struct failing_binding_target_t {
  my_binding_target_t base;
  size_t set_calls;
} failing_binding_target_t;

static my_ret_t failing_target_set_prop(my_binding_target_t* target,
                                        const char* name,
                                        const my_value_t* value) {
  failing_binding_target_t* failing = (failing_binding_target_t*)target;
  (void)name;
  (void)value;
  failing->set_calls++;
  return MY_RET_FAIL;
}

static my_ret_t failing_target_get_prop(my_binding_target_t* target,
                                        const char* name,
                                        my_value_t* value) {
  (void)target;
  (void)name;
  (void)value;
  return MY_RET_FAIL;
}

static uint32_t failing_target_on_event(my_binding_target_t* target,
                                        const char* event,
                                        my_event_callback_t callback,
                                        void* context) {
  (void)target;
  (void)event;
  (void)callback;
  (void)context;
  return 0u;
}

static my_ret_t failing_target_off_event(my_binding_target_t* target,
                                         uint32_t id) {
  (void)target;
  (void)id;
  return MY_RET_OK;
}

static const my_binding_target_vtable_t FAILING_TARGET_VTABLE = {
    failing_target_set_prop, failing_target_get_prop,
    failing_target_on_event, failing_target_off_event, NULL};

typedef struct switching_binding_target_t {
  my_binding_target_t base;
  size_t set_calls;
  size_t accepted_calls;
} switching_binding_target_t;

typedef struct switching_items_target_t {
  my_binding_target_t base;
  size_t rebuild_calls;
  size_t successful_rebuilds;
  bool fail_rebuild;
} switching_items_target_t;

typedef struct tracking_items_target_t {
  my_binding_target_t base;
  size_t rebuild_calls;
  size_t last_count;
} tracking_items_target_t;

static my_ret_t switching_target_set_prop(my_binding_target_t* target,
                                          const char* name,
                                          const my_value_t* value) {
  switching_binding_target_t* switching = (switching_binding_target_t*)target;
  const char* text = value != NULL && value->type == MY_VALUE_STR
                         ? my_value_get_str(value)
                         : NULL;
  (void)name;
  switching->set_calls++;
  if (text != NULL && strcmp(text, "new") == 0) {
    return MY_RET_FAIL;
  }
  switching->accepted_calls++;
  return MY_RET_OK;
}

static const my_binding_target_vtable_t SWITCHING_TARGET_VTABLE = {
    switching_target_set_prop, failing_target_get_prop,
    failing_target_on_event, failing_target_off_event, NULL};

static my_ret_t switching_items_rebuild(my_binding_target_t* target,
                                        const char* item_template, size_t count,
                                        my_item_props_fn_t props,
                                        void* props_ctx) {
  switching_items_target_t* switching = (switching_items_target_t*)target;
  (void)item_template;
  (void)count;
  (void)props;
  (void)props_ctx;
  switching->rebuild_calls++;
  if (switching->fail_rebuild) {
    switching->fail_rebuild = false;
    return MY_RET_FAIL;
  }
  switching->successful_rebuilds++;
  return MY_RET_OK;
}

static const my_binding_target_vtable_t SWITCHING_ITEMS_TARGET_VTABLE = {
    failing_target_set_prop, failing_target_get_prop,
    failing_target_on_event, failing_target_off_event, switching_items_rebuild};

static my_ret_t tracking_items_rebuild(my_binding_target_t* target,
                                       const char* item_template, size_t count,
                                       my_item_props_fn_t props,
                                       void* props_ctx) {
  tracking_items_target_t* tracking = (tracking_items_target_t*)target;
  (void)item_template;
  (void)props;
  (void)props_ctx;
  tracking->rebuild_calls++;
  tracking->last_count = count;
  return MY_RET_OK;
}

static const my_binding_target_vtable_t TRACKING_ITEMS_TARGET_VTABLE = {
    failing_target_set_prop, failing_target_get_prop,
    failing_target_on_event, failing_target_off_event, tracking_items_rebuild};

static my_view_model_array_t* make_rows(size_t count) {
  my_view_model_array_t* array = my_view_model_array_dummy_create(NULL);
  size_t index;
  if (array == NULL) {
    return NULL;
  }
  for (index = 0; index < count; index++) {
    my_view_model_t* row = make_row();
    if (row == NULL || my_view_model_array_dummy_push(array, row) != MY_RET_OK) {
      my_view_model_unref(row);
      my_view_model_array_unref(array);
      return NULL;
    }
    my_view_model_unref(row);
  }
  return array;
}

TEST(items_binding_refresh_preserves_list_view_scroll_and_pool)
{
  enum { k_initial_rows = 1000, k_row_height = 24, k_scroll_row = 500 };
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_view_model_array_t* array = my_view_model_array_dummy_create(NULL);
  my_widget_t* list = my_list_view_create(NULL);
  my_widget_target_t* target;
  my_binding_context_t* context;
  size_t rows_created;
  int index;

  ASSERT_TRUE(vm != NULL);
  ASSERT_TRUE(array != NULL);
  ASSERT_TRUE(list != NULL);
  for (index = 0; index < k_initial_rows; index++) {
    my_view_model_t* row = make_row();
    ASSERT_TRUE(row != NULL);
    ASSERT_EQ(my_view_model_array_dummy_push(array, row), MY_RET_OK);
    my_view_model_unref(row);
  }
  set_pointer_property(vm, "rows", array);
  ASSERT_EQ(my_mvvm_register_template("break_mvvm_row", build_row, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(list, &(my_rect_t){0, 0, 240, 120}), MY_RET_OK);

  target = my_widget_target_create(NULL, list);
  context = my_binding_context_create(NULL, vm);
  ASSERT_TRUE(target != NULL);
  ASSERT_TRUE(context != NULL);
  ASSERT_EQ(my_binding_context_bind(
                context, (my_binding_target_t*)target,
                "v:items={rows, ItemTemplate=break_mvvm_row}"),
            MY_RET_OK);
  ASSERT_TRUE(my_widget_child_count(list) <= 8u);
  ASSERT_TRUE(my_list_view_rows_created_total(list) <= 8u);

  ASSERT_EQ(my_list_view_set_scroll_offset(list, k_scroll_row * k_row_height),
            MY_RET_OK);
  ASSERT_EQ(my_list_view_get_scroll_offset(list),
            k_scroll_row * k_row_height);
  rows_created = my_list_view_rows_created_total(list);

  {
    my_view_model_t* row = make_row();
    ASSERT_TRUE(row != NULL);
    ASSERT_EQ(my_view_model_array_dummy_push(array, row), MY_RET_OK);
    my_view_model_unref(row);
  }

  ASSERT_EQ(my_list_view_get_scroll_offset(list),
            k_scroll_row * k_row_height);
  ASSERT_EQ(my_list_view_rows_created_total(list), rows_created);
  ASSERT_TRUE(my_widget_child_count(list) <= 8u);

  my_binding_context_destroy(context);
  my_widget_target_destroy(target);
  my_widget_unref(list);
  my_view_model_array_unref(array);
  my_view_model_unref(vm);
}

TEST(binding_context_rebinds_items_and_conditions)
{
  enum { k_row_height = 24, k_initial_scroll = 500 * k_row_height };
  my_view_model_t* first_vm = my_view_model_dummy_create(NULL);
  my_view_model_t* second_vm = my_view_model_dummy_create(NULL);
  my_view_model_array_t* first_rows = make_rows(1000);
  my_view_model_array_t* second_rows = make_rows(6);
  my_widget_t* list = my_list_view_create(NULL);
  my_widget_t* marker = my_label_create(NULL, "marker");
  my_widget_target_t* list_target;
  my_widget_target_t* marker_target;
  my_binding_context_t* context;

  ASSERT_TRUE(first_vm != NULL);
  ASSERT_TRUE(second_vm != NULL);
  ASSERT_TRUE(first_rows != NULL);
  ASSERT_TRUE(second_rows != NULL);
  ASSERT_TRUE(list != NULL);
  ASSERT_TRUE(marker != NULL);
  set_pointer_property(first_vm, "rows", first_rows);
  set_pointer_property(second_vm, "rows", second_rows);
  set_bool_property(first_vm, "show_marker", true);
  set_bool_property(second_vm, "show_marker", false);
  ASSERT_EQ(my_mvvm_register_template("break_mvvm_rebind_row", build_row, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(list, &(my_rect_t){0, 0, 240, 120}), MY_RET_OK);

  list_target = my_widget_target_create(NULL, list);
  marker_target = my_widget_target_create(NULL, marker);
  context = my_binding_context_create(NULL, first_vm);
  ASSERT_TRUE(list_target != NULL);
  ASSERT_TRUE(marker_target != NULL);
  ASSERT_TRUE(context != NULL);
  ASSERT_EQ(my_binding_context_bind(
                context, (my_binding_target_t*)list_target,
                "v:items={rows, ItemTemplate=break_mvvm_rebind_row}"),
            MY_RET_OK);
  ASSERT_EQ(my_binding_context_bind(
                context, (my_binding_target_t*)marker_target,
                "v:visible={Condition=show_marker}"),
            MY_RET_OK);
  ASSERT_TRUE(marker->visible);
  ASSERT_EQ(my_list_view_set_scroll_offset(list, k_initial_scroll), MY_RET_OK);

  ASSERT_EQ(my_binding_context_set_view_model(context, second_vm), MY_RET_OK);
  ASSERT_EQ(my_list_view_get_scroll_offset(list), k_row_height);
  ASSERT_TRUE(!marker->visible);

  set_bool_property(second_vm, "show_marker", true);
  ASSERT_TRUE(marker->visible);
  set_bool_property(first_vm, "show_marker", false);
  ASSERT_TRUE(marker->visible);
  {
    my_view_model_t* row = make_row();
    ASSERT_TRUE(row != NULL);
    ASSERT_EQ(my_view_model_array_dummy_push(first_rows, row), MY_RET_OK);
    my_view_model_unref(row);
  }
  ASSERT_EQ(my_list_view_set_scroll_offset(list, 999999), MY_RET_OK);
  ASSERT_EQ(my_list_view_get_scroll_offset(list), k_row_height);
  {
    my_view_model_t* row = make_row();
    ASSERT_TRUE(row != NULL);
    ASSERT_EQ(my_view_model_array_dummy_push(second_rows, row), MY_RET_OK);
    my_view_model_unref(row);
  }
  ASSERT_EQ(my_list_view_set_scroll_offset(list, 999999), MY_RET_OK);
  ASSERT_EQ(my_list_view_get_scroll_offset(list), k_row_height * 2);

  my_binding_context_destroy(context);
  my_widget_target_destroy(marker_target);
  my_widget_target_destroy(list_target);
  my_widget_unref(marker);
  my_widget_unref(list);
  my_view_model_array_unref(second_rows);
  my_view_model_array_unref(first_rows);
  my_view_model_unref(second_vm);
  my_view_model_unref(first_vm);
}

TEST(items_binding_clears_target_when_array_is_removed)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_view_model_array_t* array = make_rows(3);
  my_widget_t* list = my_list_view_create(NULL);
  my_widget_target_t* target;
  my_binding_context_t* context;

  ASSERT_TRUE(vm != NULL);
  ASSERT_TRUE(array != NULL);
  ASSERT_TRUE(list != NULL);
  set_pointer_property(vm, "rows", array);
  ASSERT_EQ(my_widget_set_rect(list, &(my_rect_t){0, 0, 240, 120}), MY_RET_OK);
  ASSERT_EQ(my_mvvm_register_template("break_mvvm_clear_row", build_row, NULL),
            MY_RET_OK);
  target = my_widget_target_create(NULL, list);
  context = my_binding_context_create(NULL, vm);
  ASSERT_TRUE(target != NULL);
  ASSERT_TRUE(context != NULL);
  ASSERT_EQ(my_binding_context_bind(
                context, (my_binding_target_t*)target,
                "v:items={rows, ItemTemplate=break_mvvm_clear_row}"),
            MY_RET_OK);
  ASSERT_TRUE(my_widget_child_count(list) > 0u);

  set_none_property(vm, "rows");

  ASSERT_EQ(my_widget_child_count(list), 0u);
  my_binding_context_destroy(context);
  my_widget_target_destroy(target);
  my_widget_unref(list);
  my_view_model_array_unref(array);
  my_view_model_unref(vm);
}

TEST(binding_condition_handles_bulk_property_notifications)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_widget_t* marker = my_label_create(NULL, "marker");
  my_widget_target_t* target;
  my_binding_context_t* context;

  ASSERT_TRUE(vm != NULL);
  ASSERT_TRUE(marker != NULL);
  set_bool_property(vm, "show_marker", false);
  target = my_widget_target_create(NULL, marker);
  context = my_binding_context_create(NULL, vm);
  ASSERT_TRUE(target != NULL);
  ASSERT_TRUE(context != NULL);
  ASSERT_EQ(my_binding_context_bind(
                context, (my_binding_target_t*)target,
                "v:visible={Condition=show_marker}"),
            MY_RET_OK);
  ASSERT_TRUE(!marker->visible);

  set_bool_property(vm, "show_marker", true);
  ASSERT_TRUE(marker->visible);
  set_bool_property(vm, "show_marker", false);
  ASSERT_EQ(my_view_model_notify_change(vm, NULL), MY_RET_OK);
  ASSERT_TRUE(!marker->visible);

  my_binding_context_destroy(context);
  my_widget_target_destroy(target);
  my_widget_unref(marker);
  my_view_model_unref(vm);
}

TEST(binding_items_switch_failure_restores_old_context)
{
  my_view_model_t* old_vm = my_view_model_dummy_create(NULL);
  my_view_model_t* new_vm = my_view_model_dummy_create(NULL);
  my_view_model_array_t* old_rows = make_rows(2);
  my_view_model_array_t* new_rows = make_rows(4);
  switching_items_target_t target = {
      {&SWITCHING_ITEMS_TARGET_VTABLE}, 0u, 0u, false};
  my_binding_context_t* context;

  ASSERT_TRUE(old_vm != NULL);
  ASSERT_TRUE(new_vm != NULL);
  ASSERT_TRUE(old_rows != NULL);
  ASSERT_TRUE(new_rows != NULL);
  set_pointer_property(old_vm, "rows", old_rows);
  set_pointer_property(new_vm, "rows", new_rows);
  context = my_binding_context_create(NULL, old_vm);
  ASSERT_TRUE(context != NULL);
  ASSERT_EQ(my_mvvm_register_template("break_mvvm_switch_row", build_row, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_binding_context_bind(
                context, &target.base,
                "v:items={rows, ItemTemplate=break_mvvm_switch_row}"),
            MY_RET_OK);
  ASSERT_EQ(target.successful_rebuilds, 1u);

  target.fail_rebuild = true;
  ASSERT_EQ(my_binding_context_set_view_model(context, new_vm), MY_RET_FAIL);
  ASSERT_TRUE(my_binding_context_get_view_model(context) == old_vm);
  {
    my_view_model_t* row = make_row();
    ASSERT_TRUE(row != NULL);
    ASSERT_EQ(my_view_model_array_dummy_push(old_rows, row), MY_RET_OK);
    my_view_model_unref(row);
  }
  ASSERT_TRUE(target.successful_rebuilds >= 2u);
  my_binding_context_destroy(context);

  my_view_model_array_unref(new_rows);
  my_view_model_array_unref(old_rows);
  my_view_model_unref(new_vm);
  my_view_model_unref(old_vm);
}

TEST(items_binding_rejects_missing_template_without_mutating_target)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_view_model_array_t* array = make_rows(2);
  my_widget_t* container = my_widget_create(NULL, "container");
  my_widget_t* existing = my_label_create(NULL, "existing");
  my_widget_target_t* target;
  my_binding_context_t* context;

  ASSERT_TRUE(vm != NULL);
  ASSERT_TRUE(array != NULL);
  ASSERT_TRUE(container != NULL);
  ASSERT_TRUE(existing != NULL);
  ASSERT_EQ(my_widget_add_child(container, existing), MY_RET_OK);
  my_widget_unref(existing);
  set_pointer_property(vm, "rows", array);
  target = my_widget_target_create(NULL, container);
  context = my_binding_context_create(NULL, vm);
  ASSERT_TRUE(target != NULL);
  ASSERT_TRUE(context != NULL);

  ASSERT_EQ(my_binding_context_bind(
                context, (my_binding_target_t*)target,
                "v:items={rows, ItemTemplate=missing_template}"),
            MY_RET_NOT_FOUND);
  ASSERT_EQ(my_widget_child_count(container), 1u);
  ASSERT_TRUE(my_widget_get_child(container, 0) != NULL);

  my_binding_context_destroy(context);
  my_widget_target_destroy(target);
  my_widget_unref(container);
  my_view_model_array_unref(array);
  my_view_model_unref(vm);
}

TEST(items_binding_rejects_wrong_property_type_without_losing_old_array)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_view_model_array_t* array = make_rows(2);
  tracking_items_target_t target = {
      {&TRACKING_ITEMS_TARGET_VTABLE}, 0u, 0u};
  my_binding_context_t* context;

  ASSERT_TRUE(vm != NULL);
  ASSERT_TRUE(array != NULL);
  set_pointer_property(vm, "rows", array);
  ASSERT_EQ(my_mvvm_register_template("break_mvvm_type_row", build_row, NULL),
            MY_RET_OK);
  context = my_binding_context_create(NULL, vm);
  ASSERT_TRUE(context != NULL);
  ASSERT_EQ(my_binding_context_bind(
                context, &target.base,
                "v:items={rows, ItemTemplate=break_mvvm_type_row}"),
            MY_RET_OK);
  ASSERT_EQ(target.last_count, 2u);

  {
    my_value_t value;
    my_value_init(&value, NULL);
    ASSERT_EQ(my_value_set_str(&value, "not-an-array"), MY_RET_OK);
    ASSERT_EQ(my_view_model_set_prop(vm, "rows", &value), MY_RET_OK);
    my_value_reset(&value);
  }

  ASSERT_EQ(target.last_count, 2u);
  {
    my_view_model_t* row = make_row();
    ASSERT_TRUE(row != NULL);
    ASSERT_EQ(my_view_model_array_dummy_push(array, row), MY_RET_OK);
    my_view_model_unref(row);
  }
  ASSERT_EQ(target.last_count, 3u);

  my_binding_context_destroy(context);
  my_view_model_array_unref(array);
  my_view_model_unref(vm);
}

TEST(binding_items_switch_wrong_type_restores_old_context)
{
  my_view_model_t* old_vm = my_view_model_dummy_create(NULL);
  my_view_model_t* new_vm = my_view_model_dummy_create(NULL);
  my_view_model_array_t* old_rows = make_rows(2);
  tracking_items_target_t target = {
      {&TRACKING_ITEMS_TARGET_VTABLE}, 0u, 0u};
  my_binding_context_t* context;

  ASSERT_TRUE(old_vm != NULL);
  ASSERT_TRUE(new_vm != NULL);
  ASSERT_TRUE(old_rows != NULL);
  set_pointer_property(old_vm, "rows", old_rows);
  {
    my_value_t value;
    my_value_init(&value, NULL);
    ASSERT_EQ(my_value_set_str(&value, "invalid"), MY_RET_OK);
    ASSERT_EQ(my_view_model_set_prop(new_vm, "rows", &value), MY_RET_OK);
    my_value_reset(&value);
  }
  ASSERT_EQ(my_mvvm_register_template("break_mvvm_switch_type_row", build_row,
                                      NULL), MY_RET_OK);
  context = my_binding_context_create(NULL, old_vm);
  ASSERT_TRUE(context != NULL);
  ASSERT_EQ(my_binding_context_bind(
                context, &target.base,
                "v:items={rows, ItemTemplate=break_mvvm_switch_type_row}"),
            MY_RET_OK);
  ASSERT_EQ(target.last_count, 2u);

  ASSERT_EQ(my_binding_context_set_view_model(context, new_vm),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(my_binding_context_get_view_model(context) == old_vm);
  {
    my_view_model_t* row = make_row();
    ASSERT_TRUE(row != NULL);
    ASSERT_EQ(my_view_model_array_dummy_push(old_rows, row), MY_RET_OK);
    my_view_model_unref(row);
  }
  ASSERT_EQ(target.last_count, 3u);

  my_binding_context_destroy(context);
  my_view_model_array_unref(old_rows);
  my_view_model_unref(new_vm);
  my_view_model_unref(old_vm);
}

TEST(binding_rejects_initial_target_sync_failure)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  failing_binding_target_t target = {{&FAILING_TARGET_VTABLE}, 0u};
  my_value_t value;

  ASSERT_TRUE(vm != NULL);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "initial"), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(vm, "title", &value), MY_RET_OK);
  my_value_reset(&value);

  {
    my_binding_context_t* context = my_binding_context_create(NULL, vm);
    ASSERT_TRUE(context != NULL);
    ASSERT_EQ(my_binding_context_bind(
                  context, &target.base, "v:text={title}"),
              MY_RET_FAIL);
    ASSERT_EQ(target.set_calls, 1u);
    ASSERT_EQ(my_view_model_notify_change(vm, "title"), MY_RET_OK);
    ASSERT_EQ(target.set_calls, 1u);
    my_binding_context_destroy(context);
  }
  my_view_model_unref(vm);
}

TEST(binding_vm_switch_failure_restores_old_context)
{
  my_view_model_t* old_vm = my_view_model_dummy_create(NULL);
  my_view_model_t* new_vm = my_view_model_dummy_create(NULL);
  switching_binding_target_t target = {{&SWITCHING_TARGET_VTABLE}, 0u, 0u};
  my_value_t value;
  my_binding_context_t* context;

  ASSERT_TRUE(old_vm != NULL);
  ASSERT_TRUE(new_vm != NULL);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "old"), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(old_vm, "title", &value), MY_RET_OK);
  my_value_reset(&value);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "new"), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(new_vm, "title", &value), MY_RET_OK);
  my_value_reset(&value);

  context = my_binding_context_create(NULL, old_vm);
  ASSERT_TRUE(context != NULL);
  ASSERT_EQ(my_binding_context_bind(context, &target.base, "v:text={title}"),
            MY_RET_OK);
  ASSERT_EQ(target.accepted_calls, 1u);
  ASSERT_EQ(my_binding_context_set_view_model(context, new_vm), MY_RET_FAIL);
  ASSERT_TRUE(my_binding_context_get_view_model(context) == old_vm);

  ASSERT_EQ(my_view_model_notify_change(old_vm, "title"), MY_RET_OK);
  ASSERT_EQ(target.accepted_calls, 3u);
  ASSERT_EQ(my_view_model_notify_change(new_vm, "title"), MY_RET_OK);
  ASSERT_EQ(target.accepted_calls, 3u);

  my_binding_context_destroy(context);
  my_view_model_unref(new_vm);
  my_view_model_unref(old_vm);
}

TEST(widget_target_keeps_widget_alive_until_binding_destroy)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_widget_t* label = my_label_create(NULL, "initial");
  my_widget_target_t* target;
  my_binding_context_t* context;
  my_value_t value;

  ASSERT_NOT_NULL(vm);
  ASSERT_NOT_NULL(label);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "first"), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(vm, "title", &value), MY_RET_OK);
  my_value_reset(&value);
  target = my_widget_target_create(NULL, label);
  context = my_binding_context_create(NULL, vm);
  ASSERT_NOT_NULL(target);
  ASSERT_NOT_NULL(context);
  ASSERT_EQ(my_binding_context_bind(context, (my_binding_target_t*)target,
                                   "v:text={title}"), MY_RET_OK);

  my_widget_unref(label);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "second"), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(vm, "title", &value), MY_RET_OK);
  my_value_reset(&value);

  my_binding_context_destroy(context);
  my_widget_target_destroy(target);
  my_view_model_unref(vm);
}

TEST(widget_target_survives_widget_tree_removal)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_widget_t* container = my_widget_create(NULL, "container");
  my_widget_t* label = my_label_create(NULL, "initial");
  my_widget_target_t* target;
  my_binding_context_t* context;
  my_value_t value;

  ASSERT_NOT_NULL(vm);
  ASSERT_NOT_NULL(container);
  ASSERT_NOT_NULL(label);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "before-remove"), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(vm, "title", &value), MY_RET_OK);
  my_value_reset(&value);
  ASSERT_EQ(my_widget_add_child(container, label), MY_RET_OK);
  target = my_widget_target_create(NULL, label);
  context = my_binding_context_create(NULL, vm);
  ASSERT_NOT_NULL(target);
  ASSERT_NOT_NULL(context);
  ASSERT_EQ(my_binding_context_bind(context, (my_binding_target_t*)target,
                                   "v:text={title}"), MY_RET_OK);
  my_widget_unref(label);
  ASSERT_EQ(my_widget_remove_child(container, my_widget_get_child(container, 0)),
            MY_RET_OK);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "after-remove"), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(vm, "title", &value), MY_RET_OK);
  my_value_reset(&value);

  my_binding_context_destroy(context);
  my_widget_target_destroy(target);
  my_widget_unref(container);
  my_view_model_unref(vm);
}

TEST(widget_target_items_ignores_forged_list_type)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_view_model_array_t* array = make_rows(2);
  my_widget_t* container = my_widget_create(NULL, "container");
  my_widget_target_t* target;
  my_binding_context_t* context;

  ASSERT_NOT_NULL(vm);
  ASSERT_NOT_NULL(array);
  ASSERT_NOT_NULL(container);
  container->widget_type = "list_view";
  set_pointer_property(vm, "rows", array);
  ASSERT_EQ(my_mvvm_register_template("break_mvvm_forged_list", build_row,
                                      NULL), MY_RET_OK);
  target = my_widget_target_create(NULL, container);
  context = my_binding_context_create(NULL, vm);
  ASSERT_NOT_NULL(target);
  ASSERT_NOT_NULL(context);
  ASSERT_EQ(my_binding_context_bind(
                context, (my_binding_target_t*)target,
                "v:items={rows, ItemTemplate=break_mvvm_forged_list}"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_child_count(container), 2u);

  my_binding_context_destroy(context);
  my_widget_target_destroy(target);
  my_widget_unref(container);
  my_view_model_array_unref(array);
  my_view_model_unref(vm);
}

TEST(mvvm_close_window_listener_is_removed_with_context)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;
  my_widget_t* button;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_mvvm_context_t* context;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(vm);
  win = my_window_create(NULL, pal, 160, 80, "mvvm-close");
  button = my_button_create(NULL, "close");
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_set_bind_rules(
                button, "v:on_click={close, CloseWindow=true}"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  context = my_mvvm_bind(NULL, win, vm);
  ASSERT_NOT_NULL(context);
  my_widget_unref(button);

  my_mvvm_context_destroy(context);
  /* Must not call on_close_window_click() with the freed context. */
  ASSERT_EQ(my_emitter_emit(button->emitter, "click", NULL),
            MY_RET_OK);

  my_widget_unref((my_widget_t*)win);
  my_view_model_unref(vm);
  my_pal_destroy(pal);
}

typedef struct async_binding_thread_args_t {
  my_mvvm_context_t* context;
  my_ret_t result;
} async_binding_thread_args_t;

typedef struct async_submit_worker_t {
  my_mvvm_context_t* context;
  unsigned int attempts;
  unsigned int accepted;
  unsigned int pending;
} async_submit_worker_t;

typedef struct manager_race_worker_t {
  my_mvvm_context_t* context;
  pthread_mutex_t* mutex;
  pthread_cond_t* condition;
  bool* ready;
  my_ret_t result;
} manager_race_worker_t;

static void* async_binding_notify_thread(void* data) {
  async_binding_thread_args_t* args =
      (async_binding_thread_args_t*)data;
  args->result = my_mvvm_context_notify_change_async(args->context, "title");
  return NULL;
}

static void* async_binding_bulk_notify_thread(void* data) {
  async_binding_thread_args_t* args =
      (async_binding_thread_args_t*)data;
  args->result = my_mvvm_context_notify_change_async(args->context, NULL);
  return NULL;
}

static void* async_binding_set_property_thread(void* data) {
  async_binding_thread_args_t* args =
      (async_binding_thread_args_t*)data;
  my_value_t value;
  char text[] = "thread-copy";
  my_value_init(&value, NULL);
  args->result = my_value_set_str(&value, text);
  if (args->result == MY_RET_OK) {
    args->result = my_mvvm_context_set_property_async(
        args->context, "title", &value);
  }
  my_value_reset(&value);
  text[0] = 'X';
  return NULL;
}

static void* async_submit_worker(void* data) {
  async_submit_worker_t* worker = (async_submit_worker_t*)data;
  my_value_t value;
  unsigned int i;
  my_value_init(&value, NULL);
  if (my_value_set_int32(&value, 7) == MY_RET_OK) {
    for (i = 0u; i < worker->attempts; i++) {
      my_ret_t ret = my_mvvm_context_set_property_async(
          worker->context, "count", &value);
      if (ret == MY_RET_OK) {
        worker->accepted++;
      } else if (ret == MY_RET_PENDING) {
        worker->pending++;
      }
    }
  }
  my_value_reset(&value);
  my_mvvm_context_unref(worker->context);
  return NULL;
}

static void* manager_race_worker(void* data) {
  manager_race_worker_t* worker = (manager_race_worker_t*)data;
  if (pthread_mutex_lock(worker->mutex) != 0) {
    return NULL;
  }
  while (!*worker->ready) {
    if (pthread_cond_wait(worker->condition, worker->mutex) != 0) {
      (void)pthread_mutex_unlock(worker->mutex);
      return NULL;
    }
  }
  if (pthread_mutex_unlock(worker->mutex) != 0) {
    return NULL;
  }
  worker->result = my_mvvm_context_notify_change_async(worker->context,
                                                       "title");
  my_mvvm_context_unref(worker->context);
  return NULL;
}

TEST(binding_context_async_notify_runs_only_on_bound_loop)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  quiet_test_vm_t* quiet = quiet_test_vm_create("old");
  my_view_model_t* vm = quiet != NULL ? &quiet->base : NULL;
  my_widget_t* label = my_label_create(NULL, "old");
  my_widget_target_t* target;
  my_mvvm_context_t* context;
  my_value_t value;
  pthread_t thread;
  async_binding_thread_args_t args;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  ASSERT_NOT_NULL(loop);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(wm);
  win = my_window_create(NULL, pal, 160, 80, "async-binding");
  ASSERT_NOT_NULL(vm);
  ASSERT_NOT_NULL(label);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), label), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  target = my_widget_target_create(NULL, label);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(target);
  ASSERT_NOT_NULL(context);
  ASSERT_EQ(my_binding_context_bind(context->ctx, (my_binding_target_t*)target,
                                    "v:text={title}"), MY_RET_OK);

  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "new"), MY_RET_OK);
  my_value_reset(&quiet->title);
  my_value_init(&quiet->title, NULL);
  ASSERT_EQ(my_value_copy(&quiet->title, &value), MY_RET_OK);
  my_value_reset(&value);
  ASSERT_EQ(strcmp(((my_label_t*)label)->text, "old"), 0);

  args.context = context;
  args.result = MY_RET_FAIL;
  ASSERT_EQ(pthread_create(&thread, NULL, async_binding_notify_thread, &args), 0);
  ASSERT_EQ(pthread_join(thread, NULL), 0);
  ASSERT_EQ(args.result, MY_RET_OK);
  ASSERT_EQ(strcmp(((my_label_t*)label)->text, "old"), 0);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);

  ASSERT_EQ(strcmp(((my_label_t*)label)->text, "new"), 0);
  my_mvvm_context_destroy(context);
  my_widget_target_destroy(target);
  my_widget_unref(label);
  my_view_model_unref(vm);
  my_window_manager_destroy(wm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(binding_context_async_notify_is_cancelled_on_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  quiet_test_vm_t* quiet = quiet_test_vm_create("old");
  my_view_model_t* vm = quiet != NULL ? &quiet->base : NULL;
  my_mvvm_context_t* context;
  async_binding_thread_args_t args;
  pthread_t thread;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  ASSERT_NOT_NULL(loop);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(wm);
  win = my_window_create(NULL, pal, 160, 80, "async-binding-cancel");
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_NOT_NULL(vm);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);
  args.context = context;
  args.result = MY_RET_FAIL;
  ASSERT_EQ(pthread_create(&thread, NULL, async_binding_notify_thread, &args), 0);
  ASSERT_EQ(pthread_join(thread, NULL), 0);
  ASSERT_EQ(args.result, MY_RET_OK);
  my_mvvm_context_destroy(context);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  my_view_model_unref(vm);
  my_window_manager_destroy(wm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(mvvm_async_notify_is_cancelled_on_manager_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_mvvm_context_t* context;
  async_binding_thread_args_t args;
  pthread_t thread;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 80, "async-manager-cancel");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(vm);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);
  args.context = context;
  args.result = MY_RET_FAIL;
  ASSERT_EQ(pthread_create(&thread, NULL, async_binding_notify_thread, &args), 0);
  ASSERT_EQ(pthread_join(thread, NULL), 0);
  ASSERT_EQ(args.result, MY_RET_OK);
  my_window_manager_destroy(wm);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  my_mvvm_context_destroy(context);
  my_view_model_unref(vm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(mvvm_async_property_write_copies_value_and_updates_binding)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  quiet_test_vm_t* quiet = quiet_test_vm_create("old");
  my_view_model_t* vm = quiet != NULL ? &quiet->base : NULL;
  my_widget_t* label = my_label_create(NULL, "old");
  my_mvvm_context_t* context;
  async_binding_thread_args_t args;
  my_value_t pointer_value;
  pthread_t thread;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 80, "async-property");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(vm);
  ASSERT_NOT_NULL(label);
  ASSERT_EQ(my_widget_set_bind_rules(label, "v:text={title}"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), label), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);
  ASSERT_EQ(strcmp(((my_label_t*)label)->text, "old"), 0);

  args.context = context;
  args.result = MY_RET_FAIL;
  ASSERT_EQ(pthread_create(&thread, NULL, async_binding_set_property_thread,
                           &args), 0);
  ASSERT_EQ(pthread_join(thread, NULL), 0);
  ASSERT_EQ(args.result, MY_RET_OK);
  ASSERT_EQ(strcmp(((my_label_t*)label)->text, "old"), 0);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(strcmp(((my_label_t*)label)->text, "thread-copy"), 0);

  my_value_init(&pointer_value, NULL);
  ASSERT_EQ(my_value_set_pointer(&pointer_value, label), MY_RET_OK);
  ASSERT_EQ(my_mvvm_context_set_property_async(context, "title",
                                                &pointer_value),
            MY_RET_NOT_SUPPORTED);
  my_value_reset(&pointer_value);
  my_mvvm_context_destroy(context);
  my_widget_unref(label);
  my_view_model_unref(vm);
  my_window_manager_destroy(wm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(mvvm_async_property_submission_is_bounded)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_mvvm_context_t* context;
  my_value_t value;
  char large[4098];
  size_t i;
  size_t accepted = 0u;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 80, "async-bounded");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(vm);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);

  for (i = 0u; i < sizeof(large) - 1u; i++) {
    large[i] = 'a';
  }
  large[sizeof(large) - 1u] = '\0';
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, large), MY_RET_OK);
  ASSERT_EQ(my_mvvm_context_set_property_async(context, "count", &value),
            MY_RET_INVALID_PARAMS);
  my_value_reset(&value);

  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_int32(&value, 1), MY_RET_OK);
  for (i = 0u; i < 65u; i++) {
    my_ret_t ret = my_mvvm_context_set_property_async(context, "count", &value);
    if (ret == MY_RET_OK) {
      accepted++;
    } else {
      ASSERT_EQ(ret, MY_RET_PENDING);
    }
  }
  ASSERT_EQ(accepted, 64u);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(my_mvvm_context_set_property_async(context, "count", &value),
            MY_RET_OK);
  my_value_reset(&value);

  my_mvvm_context_destroy(context);
  my_view_model_unref(vm);
  my_window_manager_destroy(wm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(mvvm_context_ref_keeps_async_submission_alive)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_mvvm_context_t* context;
  async_binding_thread_args_t args;
  pthread_t thread;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 80, "async-context-ref");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(vm);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);
  args.context = my_mvvm_context_ref(context);
  args.result = MY_RET_FAIL;

  my_mvvm_context_destroy(context);
  ASSERT_EQ(pthread_create(&thread, NULL, async_binding_notify_thread, &args), 0);
  ASSERT_EQ(pthread_join(thread, NULL), 0);
  ASSERT_EQ(args.result, MY_RET_OK);
  my_window_manager_destroy(wm);
  my_mvvm_context_unref(args.context);
  my_view_model_unref(vm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(mvvm_async_bulk_refreshes_data_condition_and_items)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  quiet_test_vm_t* quiet = quiet_test_vm_create("old");
  my_view_model_t* vm = quiet != NULL ? &quiet->base : NULL;
  my_view_model_array_t* rows = make_rows(1);
  my_widget_t* label = my_label_create(NULL, "old");
  my_widget_t* marker = my_label_create(NULL, "marker");
  my_widget_t* list = my_list_view_create(NULL);
  my_mvvm_context_t* context;
  async_binding_thread_args_t args;
  pthread_t thread;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(vm);
  ASSERT_NOT_NULL(rows);
  ASSERT_NOT_NULL(label);
  ASSERT_NOT_NULL(marker);
  ASSERT_NOT_NULL(list);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 240, 160, "async-bulk");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_mvvm_register_template("break_mvvm_async_bulk", build_row,
                                      NULL), MY_RET_OK);
  quiet->rows = rows;
  quiet->show_marker = false;
  ASSERT_EQ(my_widget_set_bind_rules(label, "v:text={title}"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_bind_rules(marker,
                                     "v:visible={Condition=show_marker}"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_bind_rules(
                list, "v:items={rows, ItemTemplate=break_mvvm_async_bulk}"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(list, &(my_rect_t){0, 0, 240, 80}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), label), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), marker), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), list), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);
  ASSERT_FALSE(marker->visible);
  ASSERT_EQ(my_widget_child_count(list), 1u);

  my_value_reset(&quiet->title);
  my_value_init(&quiet->title, NULL);
  ASSERT_EQ(my_value_set_str(&quiet->title, "bulk-new"), MY_RET_OK);
  quiet->show_marker = true;
  args.context = context;
  args.result = MY_RET_FAIL;
  ASSERT_EQ(pthread_create(&thread, NULL, async_binding_bulk_notify_thread,
                           &args),
            0);
  ASSERT_EQ(pthread_join(thread, NULL), 0);
  ASSERT_EQ(args.result, MY_RET_OK);
  ASSERT_EQ(strcmp(((my_label_t*)label)->text, "old"), 0);
  ASSERT_FALSE(marker->visible);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(strcmp(((my_label_t*)label)->text, "bulk-new"), 0);
  ASSERT_TRUE(marker->visible);
  ASSERT_EQ(my_widget_child_count(list), 1u);

  my_mvvm_context_destroy(context);
  my_widget_unref(label);
  my_widget_unref(marker);
  my_widget_unref(list);
  my_view_model_array_unref(rows);
  my_view_model_unref(vm);
  my_window_manager_destroy(wm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(mvvm_async_concurrent_workers_release_context_on_workers)
{
  enum { worker_count = 4, attempts = 32 };
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_mvvm_context_t* context;
  async_submit_worker_t workers[worker_count];
  pthread_t threads[worker_count];
  unsigned int i, accepted = 0u, pending = 0u;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(vm);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 80, "async-workers");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);
  for (i = 0u; i < worker_count; i++) {
    workers[i].context = my_mvvm_context_ref(context);
    workers[i].attempts = attempts;
    workers[i].accepted = 0u;
    workers[i].pending = 0u;
    ASSERT_NOT_NULL(workers[i].context);
    ASSERT_EQ(pthread_create(&threads[i], NULL, async_submit_worker,
                             &workers[i]), 0);
  }
  my_mvvm_context_destroy(context);
  for (i = 0u; i < worker_count; i++) {
    ASSERT_EQ(pthread_join(threads[i], NULL), 0);
    accepted += workers[i].accepted;
    pending += workers[i].pending;
  }
  ASSERT_EQ(accepted, 64u);
  ASSERT_EQ(pending, worker_count * attempts - 64u);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, UINT32_MAX), 64u);
  my_window_manager_destroy(wm);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);

  my_view_model_unref(vm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(mvvm_manager_destroy_races_worker_context_release)
{
  enum { worker_count = 4 };
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_mvvm_context_t* context;
  pthread_t threads[worker_count];
  manager_race_worker_t args[worker_count];
  pthread_mutex_t mutex;
  pthread_cond_t condition;
  bool ready = false;
  unsigned int i;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(vm);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 80, "async-manager-race");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);
  ASSERT_EQ(pthread_mutex_init(&mutex, NULL), 0);
  ASSERT_EQ(pthread_cond_init(&condition, NULL), 0);
  for (i = 0u; i < worker_count; i++) {
    args[i].context = my_mvvm_context_ref(context);
    args[i].mutex = &mutex;
    args[i].condition = &condition;
    args[i].ready = &ready;
    args[i].result = MY_RET_FAIL;
    ASSERT_EQ(pthread_create(&threads[i], NULL, manager_race_worker,
                             &args[i]), 0);
  }
  my_window_manager_destroy(wm);
  my_mvvm_context_destroy(context);
  ASSERT_EQ(pthread_mutex_lock(&mutex), 0);
  ready = true;
  ASSERT_EQ(pthread_cond_broadcast(&condition), 0);
  ASSERT_EQ(pthread_mutex_unlock(&mutex), 0);
  for (i = 0u; i < worker_count; i++) {
    ASSERT_EQ(pthread_join(threads[i], NULL), 0);
    ASSERT_EQ(args[i].result, MY_RET_PENDING);
  }
  ASSERT_EQ(pthread_cond_destroy(&condition), 0);
  ASSERT_EQ(pthread_mutex_destroy(&mutex), 0);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, UINT32_MAX), 1u);

  my_view_model_unref(vm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_destroy_clears_default_without_clobbering_replacement)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* first;
  my_navigator_wm_t* second;
  my_navigator_wm_t* replacement;
  my_navigator_request_t request = {0};

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  first = my_navigator_wm_create(NULL, wm, pal);
  second = my_navigator_wm_create(NULL, wm, pal);
  replacement = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(second);
  ASSERT_NOT_NULL(replacement);

  my_navigator_set_default(&first->base);
  my_navigator_wm_destroy(first);
  ASSERT_EQ(my_navigator_request(&request), MY_RET_NOT_FOUND);

  my_navigator_set_default(&second->base);
  my_navigator_set_default(&replacement->base);
  my_navigator_wm_destroy(second);
  ASSERT_EQ(my_navigator_request(&request), MY_RET_NOT_FOUND);
  my_navigator_wm_destroy(replacement);
  ASSERT_EQ(my_navigator_request(&request), MY_RET_NOT_FOUND);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_survives_window_manager_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(navigator);
  my_navigator_set_default(&navigator->base);

  my_window_manager_destroy(wm);
  ASSERT_EQ(my_navigator_request(&request), MY_RET_NOT_FOUND);
  my_navigator_wm_destroy(navigator);
  ASSERT_EQ(my_navigator_request(&request), MY_RET_NOT_FOUND);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_async_request_copies_request_and_runs_on_loop)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};

  g_async_nav_factory_calls = 0;
  g_async_nav_factory_args[0] = '\0';
  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(navigator);
  ASSERT_EQ(my_navigator_wm_add_page(navigator, "detail",
                                     async_nav_page_factory, NULL), MY_RET_OK);
  request.type = MY_NAV_TO;
  snprintf(request.target, sizeof(request.target), "%s", "detail");
  snprintf(request.args, sizeof(request.args), "%s", "id=42");
  ASSERT_EQ(my_navigator_wm_request_async(navigator, loop, &request),
            MY_RET_OK);
  snprintf(request.target, sizeof(request.target), "%s", "missing");
  snprintf(request.args, sizeof(request.args), "%s", "id=changed");
  ASSERT_EQ(g_async_nav_factory_calls, 0);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(g_async_nav_factory_calls, 1);
  ASSERT_EQ(strcmp(g_async_nav_factory_args, "id=42"), 0);
  ASSERT_EQ(my_window_manager_close(wm, my_window_manager_top(wm)),
            MY_RET_OK);
  my_navigator_wm_destroy(navigator);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_async_request_is_cancelled_on_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};

  g_async_nav_factory_calls = 0;
  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(navigator);
  ASSERT_EQ(my_navigator_wm_add_page(navigator, "detail",
                                     async_nav_page_factory, NULL), MY_RET_OK);
  request.type = MY_NAV_TO;
  snprintf(request.target, sizeof(request.target), "%s", "detail");
  ASSERT_EQ(my_navigator_wm_request_async(navigator, loop, &request),
            MY_RET_OK);
  my_navigator_wm_destroy(navigator);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, UINT32_MAX), 1u);
  ASSERT_EQ(g_async_nav_factory_calls, 0);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_async_request_is_cancelled_on_manager_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};

  g_async_nav_factory_calls = 0;
  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(navigator);
  ASSERT_EQ(my_navigator_wm_add_page(navigator, "detail",
                                     async_nav_page_factory, NULL), MY_RET_OK);
  request.type = MY_NAV_TO;
  snprintf(request.target, sizeof(request.target), "%s", "detail");
  ASSERT_EQ(my_navigator_wm_request_async(navigator, loop, &request),
            MY_RET_OK);
  my_window_manager_destroy(wm);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, UINT32_MAX), 1u);
  ASSERT_EQ(g_async_nav_factory_calls, 0);
  my_navigator_wm_destroy(navigator);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_owned_page_context_releases_once)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  int context = 7;

  g_owned_page_context_destroy_count = 0;
  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(navigator);
  ASSERT_EQ(my_navigator_wm_add_page_owned(
                navigator, "owned", async_nav_page_factory, &context,
                owned_page_context_destroy),
            MY_RET_OK);
  my_navigator_wm_destroy(navigator);
  ASSERT_EQ(g_owned_page_context_destroy_count, 1);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_propagates_window_open_failure)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  g_existing_nav_window = my_window_create(NULL, pal, 160, 80, "existing");
  ASSERT_NOT_NULL(navigator);
  ASSERT_NOT_NULL(g_existing_nav_window);
  ASSERT_EQ(my_window_manager_open(wm, g_existing_nav_window), MY_RET_OK);
  ASSERT_EQ(my_navigator_wm_add_page(navigator, "existing",
                                     existing_nav_page_factory, NULL), MY_RET_OK);
  my_navigator_set_default(&navigator->base);
  request.type = MY_NAV_TO;
  snprintf(request.target, sizeof(request.target), "%s", "existing");
  ASSERT_EQ(my_navigator_request(&request), MY_RET_INVALID_PARAMS);
  my_widget_unref((my_widget_t*)g_existing_nav_window);
  g_existing_nav_window = NULL;
  my_window_manager_destroy(wm);
  my_navigator_wm_destroy(navigator);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_async_request_rejects_foreign_loop)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_pal_main_loop_t* foreign_loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  foreign_loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(navigator);
  request.type = MY_NAV_BACK;
  ASSERT_EQ(my_navigator_wm_request_async(navigator, foreign_loop, &request),
            MY_RET_INVALID_PARAMS);
  my_navigator_wm_destroy(navigator);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(foreign_loop);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_factory_can_destroy_navigator_without_use_after_free)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};
  reentrant_nav_factory_state_t state = {0};

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(navigator);
  state.navigator = navigator;
  ASSERT_EQ(my_navigator_wm_add_page(navigator, "reentrant",
                                     reentrant_nav_page_factory, &state),
            MY_RET_OK);
  my_navigator_set_default(&navigator->base);
  request.type = MY_NAV_TO;
  snprintf(request.target, sizeof(request.target), "%s", "reentrant");
  ASSERT_EQ(my_navigator_request(&request), MY_RET_NOT_FOUND);
  ASSERT_EQ(state.calls, 1);
  ASSERT_EQ(my_navigator_request(&request), MY_RET_NOT_FOUND);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_page_lease_skips_invalidated_factory)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};
  navigator_page_lease_state_t state = {0};

  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(navigator);
  state.lease = my_emitter_context_lease_create(NULL, &state,
                                                navigator_page_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_navigator_wm_add_page_lease(
                navigator, "lease", navigator_page_lease_factory,
                state.lease), MY_RET_OK);
  my_navigator_set_default(&navigator->base);
  my_emitter_context_lease_invalidate(state.lease);
  my_emitter_context_lease_unref(state.lease);
  state.lease = NULL;
  request.type = MY_NAV_TO;
  snprintf(request.target, sizeof(request.target), "%s", "lease");
  ASSERT_EQ(my_navigator_request(&request), MY_RET_NOT_FOUND);
  ASSERT_EQ(state.factory_calls, 0);
  my_navigator_wm_destroy(navigator);
  ASSERT_EQ(state.destroy_count, 1);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(navigator_page_lease_invalidation_during_factory_allows_current_call)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_navigator_wm_t* navigator;
  my_navigator_request_t request = {0};
  navigator_page_lease_state_t state = {0};

  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  navigator = my_navigator_wm_create(NULL, wm, pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(navigator);
  state.invalidate_in_factory = true;
  state.lease = my_emitter_context_lease_create(NULL, &state,
                                                navigator_page_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_navigator_wm_add_page_lease(
                navigator, "lease", navigator_page_lease_factory,
                state.lease), MY_RET_OK);
  my_navigator_set_default(&navigator->base);
  request.type = MY_NAV_TO;
  snprintf(request.target, sizeof(request.target), "%s", "lease");
  ASSERT_EQ(my_navigator_request(&request), MY_RET_OK);
  ASSERT_EQ(state.factory_calls, 1);
  ASSERT_EQ(my_window_manager_count(wm), 1u);
  my_emitter_context_lease_unref(state.lease);
  state.lease = NULL;
  my_window_manager_close(wm, my_window_manager_top(wm));
  my_navigator_wm_destroy(navigator);
  ASSERT_EQ(state.destroy_count, 1);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(mvvm_owned_template_context_releases_on_replace_and_unregister)
{
  int first = 1;
  int second = 2;
  const my_item_template_t* template_entry;

  g_owned_template_context_destroy_count = 0;
  ASSERT_EQ(my_mvvm_register_template_owned(
                "owned_mvvm_template", build_row, &first,
                owned_template_context_destroy),
            MY_RET_OK);
  template_entry = my_mvvm_find_template("owned_mvvm_template");
  ASSERT_NOT_NULL(template_entry);
  ASSERT_EQ(template_entry->ctx, &first);
  ASSERT_EQ(my_mvvm_register_template_owned(
                "owned_mvvm_template", build_row, &second,
                owned_template_context_destroy),
            MY_RET_OK);
  ASSERT_EQ(g_owned_template_context_destroy_count, 1);
  ASSERT_EQ(my_mvvm_unregister_template("owned_mvvm_template"), MY_RET_OK);
  ASSERT_EQ(g_owned_template_context_destroy_count, 2);
  ASSERT_EQ(my_mvvm_unregister_template("owned_mvvm_template"),
            MY_RET_NOT_FOUND);
}

TEST(mvvm_context_clears_manager_before_close_window_callback)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_widget_t* button;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_mvvm_context_t* context;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(vm);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 80, "mvvm-manager-life");
  button = my_button_create(NULL, "close");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_set_bind_rules(
                button, "v:on_click={close, CloseWindow=true}"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  context = my_mvvm_bind(wm, win, vm);
  ASSERT_NOT_NULL(context);
  my_widget_unref(button);

  my_window_manager_destroy(wm);
  ASSERT_EQ(my_emitter_emit(button->emitter, "click", NULL),
            MY_RET_OK);
  my_mvvm_context_destroy(context);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
  my_view_model_unref(vm);
}

TEST(view_model_notify_listener_can_release_model)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  notify_self_remove_t state = {vm, NULL, false};

  ASSERT_NOT_NULL(vm);
  ASSERT_TRUE(my_emitter_on(vm->emitter, "prop:title", remove_vm_on_notify,
                            &state) != 0u);
  ASSERT_EQ(my_view_model_notify_change(vm, "title"), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.vm == NULL);
}

TEST(binding_rule_rejects_ambiguous_options)
{
  my_binding_rule_t rule;

  ASSERT_EQ(my_binding_rule_parse("v:text={name, , Mode=Once}", &rule),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_binding_rule_parse("v:text={name, Args=call(}", &rule),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_binding_rule_parse("v:text={name, Args=call)}", &rule),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_binding_rule_parse(
                "v:text={name, Mode=Once, Mode=TwoWay}", &rule),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_binding_rule_parse(
                "v:visible={Condition=show_marker, Mode=Once}", &rule),
            MY_RET_INVALID_PARAMS);
}

TEST(binding_rule_accepts_nested_option_arguments)
{
  my_binding_rule_t rule;

  ASSERT_EQ(my_binding_rule_parse(
                "v:value={age, Validator=range(0,(150))}", &rule),
            MY_RET_OK);
  ASSERT_EQ(strcmp(rule.validator, "range"), 0);
  ASSERT_EQ(strcmp(rule.validator_args, "0,(150)"), 0);
}

TEST(binding_target_rejects_missing_vtable_safely)
{
  my_binding_target_t target = {NULL};
  my_binding_target_vtable_t empty_vtable = {0};
  my_value_t value;

  my_value_init(&value, NULL);
  ASSERT_EQ(my_binding_target_set_prop(&target, "text", &value),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_binding_target_get_prop(&target, "text", &value),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_binding_target_on_event(&target, "changed", NULL, NULL), 0u);
  ASSERT_EQ(my_binding_target_off_event(&target, 1u), MY_RET_INVALID_PARAMS);

  target.vtable = &empty_vtable;
  ASSERT_EQ(my_binding_target_set_prop(&target, "text", &value),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_binding_target_get_prop(&target, "text", &value),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_binding_target_on_event(&target, "changed", NULL, NULL), 0u);
  ASSERT_EQ(my_binding_target_off_event(&target, 1u), MY_RET_NOT_SUPPORTED);
  my_value_reset(&value);
}

TEST(items_binding_rejects_missing_vtable_safely)
{
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_binding_context_t* context = my_binding_context_create(NULL, vm);
  my_binding_target_t target = {NULL};
  my_binding_rule_t rule;
  my_ret_t error = MY_RET_OK;

  ASSERT_NOT_NULL(vm);
  ASSERT_NOT_NULL(context);
  ASSERT_EQ(my_binding_rule_parse("v:items={rows, ItemTemplate=row}", &rule),
            MY_RET_OK);
  ASSERT_TRUE(my_items_binding_create(NULL, context, &target, &rule, &error) ==
              NULL);
  ASSERT_EQ(error, MY_RET_NOT_SUPPORTED);
  my_binding_context_destroy(context);
  my_view_model_unref(vm);
}

TEST(view_model_array_rejects_missing_vtable_safely)
{
  my_view_model_array_t array = {0};
  my_view_model_array_vtable_t empty_vtable = {0};

  ASSERT_EQ(my_view_model_array_get_count(&array), 0u);
  ASSERT_TRUE(my_view_model_array_get_item(&array, 0u) == NULL);
  ASSERT_EQ(my_view_model_array_insert(&array, 0u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_view_model_array_remove(&array, 0u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_view_model_array_clear(&array), MY_RET_INVALID_PARAMS);

  array.vtable = &empty_vtable;
  ASSERT_EQ(my_view_model_array_get_count(&array), 0u);
  ASSERT_TRUE(my_view_model_array_get_item(&array, 0u) == NULL);
  ASSERT_EQ(my_view_model_array_insert(&array, 0u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_view_model_array_remove(&array, 0u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_view_model_array_clear(&array), MY_RET_INVALID_PARAMS);
}

TEST(view_model_array_notify_listener_can_release_array)
{
  my_view_model_array_t* array = my_view_model_array_dummy_create(NULL);
  notify_self_remove_t state = {NULL, array, false};

  ASSERT_NOT_NULL(array);
  ASSERT_TRUE(my_emitter_on(array->emitter, "items_changed",
                            remove_array_on_notify, &state) != 0u);
  ASSERT_EQ(my_view_model_array_notify_change(array), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.array == NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(items_binding_refresh_preserves_list_view_scroll_and_pool);
    RUN_TEST(binding_context_rebinds_items_and_conditions);
    RUN_TEST(items_binding_clears_target_when_array_is_removed);
    RUN_TEST(binding_condition_handles_bulk_property_notifications);
    RUN_TEST(binding_items_switch_failure_restores_old_context);
    RUN_TEST(items_binding_rejects_missing_template_without_mutating_target);
    RUN_TEST(items_binding_rejects_wrong_property_type_without_losing_old_array);
    RUN_TEST(binding_items_switch_wrong_type_restores_old_context);
    RUN_TEST(binding_rejects_initial_target_sync_failure);
    RUN_TEST(binding_vm_switch_failure_restores_old_context);
    RUN_TEST(widget_target_keeps_widget_alive_until_binding_destroy);
    RUN_TEST(widget_target_survives_widget_tree_removal);
    RUN_TEST(widget_target_items_ignores_forged_list_type);
    RUN_TEST(mvvm_close_window_listener_is_removed_with_context);
    RUN_TEST(navigator_destroy_clears_default_without_clobbering_replacement);
    RUN_TEST(navigator_survives_window_manager_destroy);
    RUN_TEST(navigator_async_request_copies_request_and_runs_on_loop);
    RUN_TEST(navigator_async_request_is_cancelled_on_destroy);
    RUN_TEST(navigator_async_request_is_cancelled_on_manager_destroy);
    RUN_TEST(navigator_owned_page_context_releases_once);
    RUN_TEST(navigator_propagates_window_open_failure);
    RUN_TEST(navigator_async_request_rejects_foreign_loop);
    RUN_TEST(navigator_factory_can_destroy_navigator_without_use_after_free);
    RUN_TEST(navigator_page_lease_skips_invalidated_factory);
    RUN_TEST(navigator_page_lease_invalidation_during_factory_allows_current_call);
    RUN_TEST(mvvm_owned_template_context_releases_on_replace_and_unregister);
    RUN_TEST(mvvm_context_clears_manager_before_close_window_callback);
    RUN_TEST(view_model_notify_listener_can_release_model);
    RUN_TEST(view_model_array_notify_listener_can_release_array);
    RUN_TEST(binding_rule_rejects_ambiguous_options);
    RUN_TEST(binding_rule_accepts_nested_option_arguments);
    RUN_TEST(binding_target_rejects_missing_vtable_safely);
    RUN_TEST(items_binding_rejects_missing_vtable_safely);
    RUN_TEST(view_model_array_rejects_missing_vtable_safely);
    RUN_TEST(binding_context_async_notify_runs_only_on_bound_loop);
    RUN_TEST(binding_context_async_notify_is_cancelled_on_destroy);
    RUN_TEST(mvvm_async_notify_is_cancelled_on_manager_destroy);
    RUN_TEST(mvvm_async_property_write_copies_value_and_updates_binding);
    RUN_TEST(mvvm_async_property_submission_is_bounded);
    RUN_TEST(mvvm_context_ref_keeps_async_submission_alive);
    RUN_TEST(mvvm_async_bulk_refreshes_data_condition_and_items);
    RUN_TEST(mvvm_async_concurrent_workers_release_context_on_workers);
    RUN_TEST(mvvm_manager_destroy_races_worker_context_release);
TEST_MAIN_END()
