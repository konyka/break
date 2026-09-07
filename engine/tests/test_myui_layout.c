#include "test_framework.h"

#include <stdint.h>

#include "myc/my_darray.h"
#include "myui/my_layout.h"

TEST(darray_rejects_capacity_growth_overflow)
{
  my_darray_t array = {(void*)(uintptr_t)1, SIZE_MAX / 2u + 1u,
                       SIZE_MAX / 2u + 1u, NULL};

  ASSERT_EQ(my_darray_push(&array, NULL), MY_RET_OOM);
  ASSERT_EQ(array.size, SIZE_MAX / 2u + 1u);
  ASSERT_EQ(array.capacity, SIZE_MAX / 2u + 1u);
  ASSERT_EQ(array.items, (void**)(uintptr_t)1);
}

TEST(darray_rejects_size_increment_overflow)
{
  my_darray_t array = {(void*)(uintptr_t)1, SIZE_MAX, SIZE_MAX, NULL};

  ASSERT_EQ(my_darray_push(&array, NULL), MY_RET_OOM);
  ASSERT_EQ(array.size, SIZE_MAX);
  ASSERT_EQ(array.capacity, SIZE_MAX);
  ASSERT_EQ(array.items, (void**)(uintptr_t)1);
}

TEST(darray_remove_does_not_wrap_last_index)
{
  my_darray_t array = {(void*)(uintptr_t)1, SIZE_MAX, SIZE_MAX, NULL};

  ASSERT_EQ(my_darray_remove_at(&array, SIZE_MAX - 1u), MY_RET_OK);
  ASSERT_EQ(array.size, SIZE_MAX - 1u);
}

TEST(layout_parser_rejects_unsafe_values)
{
  my_layout_params_t params;

  ASSERT_EQ(my_layout_params_parse("w:-1", &params), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_layout_params_parse("h:nan", &params), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_layout_params_parse("w:inf", &params), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_layout_params_parse("w:101%", &params), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_layout_params_parse("h:2147483648", &params),
            MY_RET_INVALID_PARAMS);
}

TEST(grid_layout_places_rows_in_linear_order)
{
  my_widget_t* parent = my_widget_create(NULL, "grid");
  my_widget_t* children[5];
  my_layouter_t* grid;
  size_t index;

  ASSERT_NOT_NULL(parent);
  ASSERT_EQ(my_widget_set_rect(parent, &(my_rect_t){0, 0, 100, 100}),
            MY_RET_OK);
  grid = my_layouter_grid_create(NULL, 2, 4, 6);
  ASSERT_NOT_NULL(grid);
  ASSERT_EQ(my_widget_set_layouter(parent, grid), MY_RET_OK);
  for (index = 0; index < 5; index++) {
    children[index] = my_widget_create(NULL, "cell");
    ASSERT_NOT_NULL(children[index]);
    ASSERT_EQ(my_widget_set_rect(children[index], &(my_rect_t){0, 0, 10, 20}),
              MY_RET_OK);
    ASSERT_EQ(my_widget_add_child(parent, children[index]), MY_RET_OK);
    my_widget_unref(children[index]);
  }
  ASSERT_EQ(my_widget_set_layout_params(my_widget_get_child(parent, 0),
                                        "h:20"),
            MY_RET_OK);
  my_widget_relayout(parent);

  ASSERT_EQ(my_widget_get_child(parent, 0)->rect.x, 0);
  ASSERT_EQ(my_widget_get_child(parent, 0)->rect.y, 0);
  ASSERT_EQ(my_widget_get_child(parent, 0)->rect.w, 48);
  ASSERT_EQ(my_widget_get_child(parent, 0)->rect.h, 20);
  ASSERT_EQ(my_widget_get_child(parent, 1)->rect.x, 52);
  ASSERT_EQ(my_widget_get_child(parent, 1)->rect.y, 0);
  ASSERT_EQ(my_widget_get_child(parent, 2)->rect.x, 0);
  ASSERT_EQ(my_widget_get_child(parent, 2)->rect.y, 26);
  ASSERT_EQ(my_widget_get_child(parent, 4)->rect.x, 0);
  ASSERT_EQ(my_widget_get_child(parent, 4)->rect.y, 52);

  my_widget_unref(parent);
}

TEST(grid_layout_skips_invisible_and_floating_children)
{
  my_widget_t* parent = my_widget_create(NULL, "grid");
  my_widget_t* hidden = my_widget_create(NULL, "hidden");
  my_widget_t* floating = my_widget_create(NULL, "floating");
  my_widget_t* visible = my_widget_create(NULL, "visible");

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(hidden);
  ASSERT_NOT_NULL(floating);
  ASSERT_NOT_NULL(visible);
  ASSERT_EQ(my_widget_set_rect(parent, &(my_rect_t){0, 0, 100, 100}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_layouter(
                parent, my_layouter_grid_create(NULL, 2, 0, 0)),
            MY_RET_OK);
  hidden->visible = false;
  floating->floating = true;
  ASSERT_EQ(my_widget_add_child(parent, hidden), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(parent, floating), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(parent, visible), MY_RET_OK);
  my_widget_unref(hidden);
  my_widget_unref(floating);
  my_widget_unref(visible);
  my_widget_relayout(parent);
  ASSERT_EQ(visible->rect.x, 0);
  ASSERT_EQ(visible->rect.y, 0);

  my_widget_unref(parent);
}

TEST_MAIN_BEGIN()
    RUN_TEST(darray_rejects_capacity_growth_overflow);
    RUN_TEST(darray_rejects_size_increment_overflow);
    RUN_TEST(darray_remove_does_not_wrap_last_index);
    RUN_TEST(layout_parser_rejects_unsafe_values);
    RUN_TEST(grid_layout_places_rows_in_linear_order);
    RUN_TEST(grid_layout_skips_invisible_and_floating_children);
TEST_MAIN_END()
