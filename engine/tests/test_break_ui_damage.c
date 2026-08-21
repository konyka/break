#include "test_framework.h"

#include "mypal/dummy/my_pal_dummy.h"
#include "myui/my_window_manager.h"
#include "myui/my_layout.h"
#include "ui/myui_break_damage.h"

typedef struct failing_allocator_ctx_t {
  bool fail;
} failing_allocator_ctx_t;

static void *failing_alloc(void *ctx, size_t size) {
  failing_allocator_ctx_t *state = (failing_allocator_ctx_t *)ctx;
  return state->fail ? NULL : malloc(size);
}

static void *failing_calloc(void *ctx, size_t nmemb, size_t size) {
  failing_allocator_ctx_t *state = (failing_allocator_ctx_t *)ctx;
  return state->fail ? NULL : calloc(nmemb, size);
}

static void *failing_realloc(void *ctx, void *ptr, size_t size) {
  failing_allocator_ctx_t *state = (failing_allocator_ctx_t *)ctx;
  return state->fail ? NULL : realloc(ptr, size);
}

static void failing_free(void *ctx, void *ptr) {
  (void)ctx;
  free(ptr);
}

static bool damage_covers_point(const my_dirty_rects_t *damage, int32_t x,
                                int32_t y) {
  size_t index;
  for (index = 0; index < my_dirty_rects_count(damage); index++) {
    const my_rect_t *rect = my_dirty_rects_get(damage, index);
    if (my_rect_contains(rect, x, y)) {
      return true;
    }
  }
  return false;
}

static void expand_once_on_measure(my_widget_t *widget) {
  if (widget->rect.w < 100) {
    (void)my_widget_set_layout_rect(
        widget,
        &(my_rect_t){widget->rect.x, widget->rect.y, 100, widget->rect.h});
    my_widget_request_layout(widget);
  }
}

static const my_widget_vtable_t s_expand_once_vtable = {
    NULL, NULL, NULL, expand_once_on_measure};

static int g_requeue_measure_count;

static void requeue_once_on_measure(my_widget_t *widget) {
  g_requeue_measure_count++;
  if (g_requeue_measure_count == 1) {
    my_widget_request_layout(widget);
  }
}

static const my_widget_vtable_t s_requeue_once_vtable = {
    NULL, NULL, NULL, requeue_once_on_measure};

static void count_measure(my_widget_t *widget) {
  int *count = (int *)my_widget_get_user_data(widget);
  if (count != NULL) {
    (*count)++;
  }
}

static const my_widget_vtable_t s_count_measure_vtable = {
    NULL, NULL, NULL, count_measure};

static int g_paint_invalidation_count;

static void invalidate_once_on_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
  (void)vg;
  if (g_paint_invalidation_count == 0) {
    g_paint_invalidation_count++;
    my_widget_invalidate(widget, NULL);
  }
}

static const my_widget_vtable_t s_invalidate_once_vtable = {
    invalidate_once_on_paint, NULL, NULL, NULL};

typedef struct paint_child_mutation_ctx_t {
  my_widget_t *parent;
  my_widget_t *removed;
  int paint_count;
} paint_child_mutation_ctx_t;

static void remove_sibling_on_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
  paint_child_mutation_ctx_t *ctx =
      (paint_child_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)vg;
  ctx->paint_count++;
  (void)my_widget_remove_child(ctx->parent, ctx->removed);
}

static void count_child_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
  paint_child_mutation_ctx_t *ctx =
      (paint_child_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)vg;
  ctx->paint_count++;
}

static const my_widget_vtable_t s_remove_sibling_on_paint_vtable = {
    remove_sibling_on_paint, NULL, NULL, NULL};
static const my_widget_vtable_t s_count_child_paint_vtable = {
    count_child_paint, NULL, NULL, NULL};

TEST(collects_damage_from_all_windows)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *root = my_window_create(NULL, pal, 400, 300, "root");
  my_window_t *dialog = my_window_create(NULL, pal, 100, 80, "dialog");
  my_dirty_rects_t damage;
  const my_rect_t *rect;

  ((my_widget_t*)dialog)->rect.x = 100;
  ((my_widget_t*)dialog)->rect.y = 80;
  ASSERT_EQ(my_window_manager_open(wm, root), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, dialog), MY_RET_OK);
  my_widget_unref((my_widget_t*)root);
  my_widget_unref((my_widget_t*)dialog);
  my_dirty_rects_clear(&root->dirty);
  my_dirty_rects_clear(&dialog->dirty);
  ASSERT_EQ(my_dirty_rects_add(&root->dirty, &(my_rect_t){10, 10, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_dirty_rects_add(&dialog->dirty,
                               &(my_rect_t){120, 100, 10, 10}), MY_RET_OK);

  break_ui_collect_surface_damage(wm, &damage);
  ASSERT_EQ(my_dirty_rects_count(&damage), 2u);
  rect = my_dirty_rects_get(&damage, 0);
  ASSERT_TRUE(rect != NULL);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(expands_damage_across_overlapping_stack)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *root = my_window_create(NULL, pal, 400, 300, "root");
  my_window_t *dialog = my_window_create(NULL, pal, 100, 80, "dialog");
  my_dirty_rects_t damage;

  ((my_widget_t*)dialog)->rect.x = 100;
  ((my_widget_t*)dialog)->rect.y = 80;
  ASSERT_EQ(my_window_manager_open(wm, root), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, dialog), MY_RET_OK);
  my_widget_unref((my_widget_t*)root);
  my_widget_unref((my_widget_t*)dialog);
  my_dirty_rects_clear(&root->dirty);
  my_dirty_rects_clear(&dialog->dirty);
  my_dirty_rects_init(&damage);
  ASSERT_EQ(my_dirty_rects_add(&damage, &(my_rect_t){110, 90, 20, 20}),
            MY_RET_OK);

  break_ui_expand_surface_damage(wm, &damage);
  ASSERT_EQ(my_dirty_rects_count(&root->dirty), 1u);
  ASSERT_EQ(my_dirty_rects_count(&dialog->dirty), 1u);

  my_dirty_rects_clear(&root->dirty);
  my_dirty_rects_clear(&dialog->dirty);
  my_dirty_rects_clear(&damage);
  ASSERT_EQ(my_dirty_rects_add(&damage, &(my_rect_t){10, 10, 20, 20}),
            MY_RET_OK);
  break_ui_expand_surface_damage(wm, &damage);
  ASSERT_EQ(my_dirty_rects_count(&root->dirty), 1u);
  ASSERT_EQ(my_dirty_rects_count(&dialog->dirty), 0u);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(structural_window_changes_invalidate_shared_surface)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *root = my_window_create(NULL, pal, 400, 300, "root");
  my_widget_t *child = my_widget_create(NULL, "child");
  my_dirty_rects_t damage;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(child);
  ASSERT_EQ(my_window_manager_open(wm, root), MY_RET_OK);
  my_widget_unref((my_widget_t *)root);
  ASSERT_EQ(my_widget_set_rect(child, &(my_rect_t){20, 30, 80, 40}),
            MY_RET_OK);
  my_dirty_rects_clear(&root->dirty);

  ASSERT_EQ(my_widget_add_child(my_window_widget(root), child), MY_RET_OK);
  break_ui_collect_surface_damage(wm, &damage);
  ASSERT_TRUE(my_dirty_rects_count(&damage) > 0);

  my_dirty_rects_clear(&root->dirty);
  ASSERT_EQ(my_widget_remove_child(my_window_widget(root), child), MY_RET_OK);
  break_ui_collect_surface_damage(wm, &damage);
  ASSERT_TRUE(my_dirty_rects_count(&damage) > 0);

  ASSERT_EQ(my_widget_add_child(my_window_widget(root), child), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(root), child),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_add_child(child, my_window_widget(root)),
            MY_RET_INVALID_PARAMS);

  my_widget_unref(child);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(geometry_and_layout_changes_invalidate_shared_surface)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *root = my_window_create(NULL, pal, 400, 300, "root");
  my_widget_t *child = my_widget_create(NULL, "child");
  my_dirty_rects_t damage;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(child);
  ASSERT_EQ(my_widget_set_rect(child, &(my_rect_t){20, 30, 80, 40}),
            MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, root), MY_RET_OK);
  my_widget_unref((my_widget_t *)root);
  ASSERT_EQ(my_widget_add_child(my_window_widget(root), child), MY_RET_OK);
  my_dirty_rects_clear(&root->dirty);
  ((my_widget_t *)root)->need_layout = false;

  ASSERT_EQ(my_widget_set_rect(child, &(my_rect_t){140, 90, 30, 20}),
            MY_RET_OK);
  break_ui_collect_surface_damage(wm, &damage);
  ASSERT_TRUE(damage_covers_point(&damage, 21, 31));
  ASSERT_TRUE(damage_covers_point(&damage, 141, 91));
  ASSERT_TRUE(((my_widget_t *)root)->subtree_need_layout);

  my_dirty_rects_clear(&root->dirty);
  ((my_widget_t *)root)->need_layout = false;
  ((my_widget_t *)root)->subtree_need_layout = false;
  ASSERT_EQ(my_widget_set_layout_params(child, "w:30 h:20"), MY_RET_OK);
  ASSERT_TRUE(((my_widget_t *)root)->need_layout);
  break_ui_collect_surface_damage(wm, &damage);
  ASSERT_TRUE(my_dirty_rects_count(&damage) > 0);

  my_widget_unref(child);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(layout_settles_before_shared_surface_damage_collection)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *root = my_window_create(NULL, pal, 400, 300, "root");
  my_widget_t *child = my_widget_create(NULL, "measured-child");
  my_dirty_rects_t damage;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(child);
  ASSERT_EQ(my_widget_subclass_init(child, &s_expand_once_vtable), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(child, &(my_rect_t){20, 30, 10, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, root), MY_RET_OK);
  my_widget_unref((my_widget_t *)root);
  ASSERT_EQ(my_widget_add_child(my_window_widget(root), child), MY_RET_OK);
  my_dirty_rects_clear(&root->dirty);
  my_widget_request_layout(child);
  my_widget_invalidate(child, NULL);

  ASSERT_EQ(my_window_prepare_layout(root), MY_RET_OK);
  ASSERT_FALSE(((my_widget_t *)root)->need_layout);
  break_ui_collect_surface_damage(wm, &damage);
  ASSERT_TRUE(damage_covers_point(&damage, 119, 31));

  my_widget_unref(child);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(layout_requeues_current_widget_and_skips_clean_subtrees)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *root = my_window_create(NULL, pal, 400, 300, "root");
  my_widget_t *left = my_widget_create(NULL, "left");
  my_widget_t *right = my_widget_create(NULL, "right");
  int left_measures = 0;
  int right_measures = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(left);
  ASSERT_NOT_NULL(right);
  ASSERT_EQ(my_widget_subclass_init((my_widget_t *)root,
                                    &s_requeue_once_vtable),
            MY_RET_OK);
  g_requeue_measure_count = 0;
  my_widget_request_layout((my_widget_t *)root);
  ASSERT_EQ(my_window_prepare_layout(root), MY_RET_OK);
  ASSERT_EQ(g_requeue_measure_count, 2);

  ASSERT_EQ(my_widget_subclass_init(left, &s_count_measure_vtable), MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(right, &s_count_measure_vtable), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(left, &left_measures), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(right, &right_measures), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)root, left), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)root, right), MY_RET_OK);
  ASSERT_EQ(my_window_prepare_layout(root), MY_RET_OK);
  left_measures = 0;
  right_measures = 0;

  ASSERT_EQ(my_widget_set_rect(left, &(my_rect_t){10, 10, 40, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_window_prepare_layout(root), MY_RET_OK);
  ASSERT_EQ(left_measures, 1);
  ASSERT_EQ(right_measures, 0);

  my_widget_unref(left);
  my_widget_unref(right);
  my_object_unref((my_object_t *)root);
  my_pal_destroy(pal);
}

TEST(parent_destruction_detaches_retained_children)
{
  my_widget_t *parent = my_widget_create(NULL, "parent");
  my_widget_t *child = my_widget_create(NULL, "child");
  my_widget_t *next_parent = my_widget_create(NULL, "next-parent");

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(child);
  ASSERT_NOT_NULL(next_parent);
  ASSERT_EQ(my_widget_add_child(parent, child), MY_RET_OK);
  ASSERT_TRUE(child->parent == parent);

  my_widget_unref(parent);
  ASSERT_TRUE(child->parent == NULL);
  ASSERT_EQ(my_widget_add_child(next_parent, child), MY_RET_OK);

  my_widget_unref(next_parent);
  my_widget_unref(child);
}

TEST(invalidation_during_paint_survives_for_next_frame)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *root = my_window_create(NULL, pal, 100, 80, "root");
  my_widget_t *child = my_widget_create(NULL, "paint-invalidates");

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(child);
  ASSERT_EQ(my_widget_subclass_init(child, &s_invalidate_once_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(child, &(my_rect_t){10, 10, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)root, child), MY_RET_OK);
  g_paint_invalidation_count = 0;
  my_widget_invalidate((my_widget_t *)root, NULL);

  my_window_paint(root);
  ASSERT_EQ(g_paint_invalidation_count, 1);
  ASSERT_TRUE(my_dirty_rects_count(&root->dirty) > 0);

  my_widget_unref(child);
  my_object_unref((my_object_t *)root);
  my_pal_destroy(pal);
}

TEST(window_record_failure_keeps_dirty)
{
  failing_allocator_ctx_t allocator_ctx = {false};
  my_allocator_t allocator = {&allocator_ctx, failing_alloc, failing_calloc,
                               failing_realloc, failing_free};
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *root = my_window_create(&allocator, pal, 100, 80, "root");

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(root);
  my_dirty_rects_clear(&root->dirty);
  my_widget_invalidate((my_widget_t *)root, NULL);
  ASSERT_TRUE(my_dirty_rects_count(&root->dirty) > 0);

  allocator_ctx.fail = true;
  ASSERT_EQ(my_window_record_dirty(root), MY_RET_FAIL);
  ASSERT_TRUE(my_dirty_rects_count(&root->dirty) > 0);

  allocator_ctx.fail = false;
  my_object_unref((my_object_t *)root);
  my_pal_destroy(pal);
}

TEST(restoring_dirty_snapshot_preserves_new_invalidation)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *root = my_window_create(NULL, pal, 100, 80, "root");
  my_dirty_rects_t snapshot;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(root);
  my_dirty_rects_clear(&root->dirty);
  ASSERT_EQ(my_dirty_rects_add(&root->dirty, &(my_rect_t){10, 10, 10, 10}),
            MY_RET_OK);
  snapshot = root->dirty;
  my_dirty_rects_clear(&root->dirty);
  ASSERT_EQ(my_dirty_rects_add(&root->dirty, &(my_rect_t){40, 40, 10, 10}),
            MY_RET_OK);

  my_window_restore_dirty(root, &snapshot);
  ASSERT_TRUE(damage_covers_point(&root->dirty, 11, 11));
  ASSERT_TRUE(damage_covers_point(&root->dirty, 41, 41));
  ASSERT_TRUE(((my_widget_t *)root)->dirty);

  my_object_unref((my_object_t *)root);
  my_pal_destroy(pal);
}

TEST(paint_child_snapshot_handles_tree_mutation)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *root = my_window_create(NULL, pal, 100, 80, "root");
  my_widget_t *first = my_widget_create(NULL, "first");
  my_widget_t *removed = my_widget_create(NULL, "removed");
  my_widget_t *last = my_widget_create(NULL, "last");
  paint_child_mutation_ctx_t first_ctx = {(my_widget_t *)root, removed, 0};
  paint_child_mutation_ctx_t last_ctx = {(my_widget_t *)root, NULL, 0};

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(removed);
  ASSERT_NOT_NULL(last);
  ASSERT_EQ(my_widget_subclass_init(first, &s_remove_sibling_on_paint_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(last, &s_count_child_paint_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(first, &first_ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(last, &last_ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)root, first), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)root, removed), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)root, last), MY_RET_OK);
  my_widget_unref(first);
  my_widget_unref(removed);
  my_widget_unref(last);
  my_widget_invalidate((my_widget_t *)root, NULL);

  my_window_paint(root);
  ASSERT_EQ(first_ctx.paint_count, 1);
  ASSERT_EQ(last_ctx.paint_count, 1);
  ASSERT_TRUE(removed->parent == NULL);

  my_object_unref((my_object_t *)root);
  my_pal_destroy(pal);
}

TEST_MAIN_BEGIN()
    RUN_TEST(collects_damage_from_all_windows);
    RUN_TEST(expands_damage_across_overlapping_stack);
    RUN_TEST(structural_window_changes_invalidate_shared_surface);
    RUN_TEST(geometry_and_layout_changes_invalidate_shared_surface);
    RUN_TEST(layout_settles_before_shared_surface_damage_collection);
    RUN_TEST(layout_requeues_current_widget_and_skips_clean_subtrees);
    RUN_TEST(parent_destruction_detaches_retained_children);
    RUN_TEST(invalidation_during_paint_survives_for_next_frame);
    RUN_TEST(window_record_failure_keeps_dirty);
    RUN_TEST(restoring_dirty_snapshot_preserves_new_invalidation);
    RUN_TEST(paint_child_snapshot_handles_tree_mutation);
TEST_MAIN_END()
