#include "test_framework.h"

#include "mymvvm/my_binding_context.h"
#include "mymvvm/my_view_model.h"
#include "mymvvm/my_view_model_array.h"
#include "mymvvm_myui/my_mvvm.h"
#include "mymvvm_myui/my_widget_target.h"
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

static void set_bool_property(my_view_model_t* vm, const char* name,
                              bool enabled) {
  my_value_t value;
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_bool(&value, enabled), MY_RET_OK);
  ASSERT_EQ(my_view_model_set_prop(vm, name, &value), MY_RET_OK);
  my_value_reset(&value);
}

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

TEST_MAIN_BEGIN()
    RUN_TEST(items_binding_refresh_preserves_list_view_scroll_and_pool);
    RUN_TEST(binding_context_rebinds_items_and_conditions);
TEST_MAIN_END()
