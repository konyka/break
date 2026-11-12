#include "test_framework.h"

#include <stdatomic.h>
#include <string.h>

#include "mypal/dummy/my_pal_dummy.h"
#include "myr/my_dirty_rects.h"
#include "myui/my_window.h"
#include "myui/my_window_manager.h"
#include "myui/widgets/my_edit.h"

typedef struct notify_probe_t {
  my_widget_removed_hook_t previous_root_hook;
  int root_calls;
  int child_calls;
  int order[2];
  bool attached[2];
} notify_probe_t;

static notify_probe_t s_notify;

static void probe_child_removed(my_widget_t* parent, my_widget_t* child) {
  int index = s_notify.root_calls + s_notify.child_calls;
  if (index < 2) {
    s_notify.order[index] = 1;
    s_notify.attached[index] = child->parent == parent;
  }
  s_notify.child_calls++;
}

static void probe_root_removed(my_widget_t* root, my_widget_t* removed) {
  int index = s_notify.root_calls + s_notify.child_calls;
  if (index < 2) {
    s_notify.order[index] = 2;
    s_notify.attached[index] = removed->parent == root;
  }
  s_notify.root_calls++;
  if (s_notify.previous_root_hook != NULL) {
    s_notify.previous_root_hook(root, removed);
  }
}

typedef struct widget_fixture_t {
  my_pal_t* pal;
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_widget_t* a;
  my_widget_t* b;
  my_widget_t* staged;
  bool notify_installed;
} widget_fixture_t;

static void widget_fixture_destroy(widget_fixture_t* fixture) {
  if (fixture->win != NULL && fixture->notify_installed) {
    my_widget_t* root = (my_widget_t*)fixture->win;
    root->removed_hook = s_notify.previous_root_hook;
    root->child_removed_hook = NULL;
  }
  my_widget_unref(fixture->staged);
  my_widget_unref(fixture->a);
  my_widget_unref(fixture->b);
  my_window_manager_destroy(fixture->wm);
  my_widget_unref((my_widget_t*)fixture->win);
  my_pal_main_loop_destroy(fixture->loop);
  my_pal_destroy(fixture->pal);
  memset(fixture, 0, sizeof(*fixture));
  memset(&s_notify, 0, sizeof(s_notify));
}

static bool widget_fixture_init(widget_fixture_t* fixture) {
  my_widget_t* root;
  my_edit_t* a_edit;
  my_edit_t* b_edit;
  my_event_t event;
  memset(fixture, 0, sizeof(*fixture));
  memset(&s_notify, 0, sizeof(s_notify));
  fixture->pal = my_pal_dummy_create(NULL);
  fixture->loop = my_pal_main_loop_create(fixture->pal);
  fixture->wm = my_window_manager_create(NULL, fixture->pal, fixture->loop);
  fixture->win = my_window_create(NULL, fixture->pal, 240, 100, "primitives");
  fixture->a = my_edit_create(NULL);
  fixture->b = my_edit_create(NULL);
  if (fixture->pal == NULL || fixture->loop == NULL || fixture->wm == NULL ||
      fixture->win == NULL || fixture->a == NULL || fixture->b == NULL) {
    goto fail;
  }
  root = my_window_widget(fixture->win);
  s_notify.previous_root_hook = ((my_widget_t*)fixture->win)->removed_hook;
  ((my_widget_t*)fixture->win)->removed_hook = probe_root_removed;
  root->child_removed_hook = probe_child_removed;
  fixture->notify_installed = true;
  a_edit = (my_edit_t*)fixture->a;
  b_edit = (my_edit_t*)fixture->b;
  if (my_widget_set_rect(fixture->a, &(my_rect_t){0, 0, 100, 30}) != MY_RET_OK ||
      my_widget_set_rect(fixture->b, &(my_rect_t){110, 0, 100, 30}) !=
          MY_RET_OK ||
      my_edit_set_text(fixture->a, "alpha") != MY_RET_OK ||
      my_edit_set_text(fixture->b, "bravo") != MY_RET_OK ||
      my_widget_add_child(root, fixture->a) != MY_RET_OK ||
      my_widget_add_child(root, fixture->b) != MY_RET_OK ||
      my_window_manager_open(fixture->wm, fixture->win) != MY_RET_OK) {
    goto fail;
  }
  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 5;
  event.u.pointer.y = 5;
  (void)my_event_dispatch(&fixture->win->dispatcher, &event);
  a_edit->cursor = 4u;
  a_edit->anchor = 1u;
  b_edit->cursor = 3u;
  b_edit->anchor = 1u;
  event = my_event_init(MY_EVENT_IME_PREEDIT);
  event.u.ime.text = "ni";
  event.u.ime.cursor = 1;
  (void)my_event_dispatch(&fixture->win->dispatcher, &event);
  if (fixture->win->dispatcher.focused != fixture->a ||
      fixture->win->dispatcher.grabbed != fixture->a || !a_edit->focused ||
      a_edit->ime_preedit == NULL ||
      !my_pal_dummy_get_ime_enabled(fixture->win->pal_window)) {
    goto fail;
  }
  return true;
fail:
  widget_fixture_destroy(fixture);
  return false;
}

static bool edit_selection_is(my_widget_t* edit, size_t start, size_t end) {
  size_t actual_start = 0u;
  size_t actual_end = 0u;
  my_edit_get_selection(edit, &actual_start, &actual_end);
  return actual_start == start && actual_end == end;
}

static bool fixture_interaction_is_preserved(const widget_fixture_t* fixture) {
  const my_edit_t* a_edit = (const my_edit_t*)fixture->a;
  return edit_selection_is(fixture->a, 1u, 4u) &&
         edit_selection_is(fixture->b, 1u, 3u) &&
         fixture->win->dispatcher.focused == fixture->a &&
         fixture->win->dispatcher.grabbed == fixture->a && a_edit->focused &&
         a_edit->ime_preedit != NULL &&
         strcmp(a_edit->ime_preedit, "ni") == 0 && a_edit->ime_caret == 1 &&
         my_pal_dummy_get_ime_enabled(fixture->win->pal_window);
}

TEST(reorder_preserves_edit_identity_selection_and_dispatch_state)
{
  widget_fixture_t fixture;
  my_widget_t* root;
  unsigned int a_refs;
  unsigned int b_refs;
  ASSERT_TRUE(widget_fixture_init(&fixture));
  root = my_window_widget(fixture.win);
  a_refs = atomic_load(&fixture.a->base.ref_count);
  b_refs = atomic_load(&fixture.b->base.ref_count);
  ASSERT_EQ(my_widget_reorder_child(root, fixture.a, 1u), MY_RET_OK);
  ASSERT_TRUE(my_widget_get_child(root, 0u) == fixture.b);
  ASSERT_TRUE(my_widget_get_child(root, 1u) == fixture.a);
  ASSERT_TRUE(fixture.a->parent == root && fixture.b->parent == root);
  ASSERT_EQ(atomic_load(&fixture.a->base.ref_count), a_refs);
  ASSERT_EQ(atomic_load(&fixture.b->base.ref_count), b_refs);
  ASSERT_TRUE(fixture_interaction_is_preserved(&fixture));
  ASSERT_STR_EQ(my_edit_get_text(fixture.a), "alpha");
  ASSERT_STR_EQ(my_edit_get_text(fixture.b), "bravo");
  ASSERT_EQ(s_notify.root_calls, 0);
  ASSERT_EQ(s_notify.child_calls, 0);
  widget_fixture_destroy(&fixture);
}

TEST(detach_reinsert_defers_cleanup_until_explicit_notify)
{
  widget_fixture_t fixture;
  my_widget_t* root;
  unsigned int refs;
  ASSERT_TRUE(widget_fixture_init(&fixture));
  root = my_window_widget(fixture.win);
  refs = atomic_load(&fixture.a->base.ref_count);
  ASSERT_EQ(my_widget_detach_child(root, fixture.a, &fixture.staged), MY_RET_OK);
  ASSERT_TRUE(fixture.staged == fixture.a);
  ASSERT_TRUE(fixture.a->parent == NULL);
  ASSERT_EQ(my_widget_child_count(root), 1u);
  ASSERT_TRUE(my_widget_get_child(root, 0u) == fixture.b);
  ASSERT_EQ(atomic_load(&fixture.a->base.ref_count), refs);
  ASSERT_EQ(s_notify.root_calls, 0);
  ASSERT_EQ(s_notify.child_calls, 0);
  ASSERT_TRUE(fixture_interaction_is_preserved(&fixture));

  ASSERT_EQ(my_widget_insert_child(root, fixture.staged, 1u), MY_RET_OK);
  fixture.staged = NULL;
  ASSERT_TRUE(fixture.a->parent == root);
  ASSERT_TRUE(my_widget_get_child(root, 0u) == fixture.b);
  ASSERT_TRUE(my_widget_get_child(root, 1u) == fixture.a);
  ASSERT_EQ(atomic_load(&fixture.a->base.ref_count), refs);
  ASSERT_EQ(s_notify.root_calls, 0);
  ASSERT_EQ(s_notify.child_calls, 0);
  ASSERT_TRUE(fixture_interaction_is_preserved(&fixture));

  ASSERT_EQ(my_widget_detach_child(root, fixture.a, &fixture.staged), MY_RET_OK);
  ASSERT_EQ(s_notify.root_calls, 0);
  ASSERT_EQ(s_notify.child_calls, 0);
  ASSERT_TRUE(fixture_interaction_is_preserved(&fixture));
  my_widget_notify_child_removed(root, fixture.staged);
  ASSERT_EQ(s_notify.root_calls, 1);
  ASSERT_EQ(s_notify.child_calls, 1);
  ASSERT_TRUE(fixture.win->dispatcher.focused == NULL);
  ASSERT_TRUE(fixture.win->dispatcher.grabbed == NULL);
  ASSERT_FALSE(((my_edit_t*)fixture.a)->focused);
  ASSERT_TRUE(((my_edit_t*)fixture.a)->ime_preedit == NULL);
  ASSERT_FALSE(my_pal_dummy_get_ime_enabled(fixture.win->pal_window));
  ASSERT_TRUE(edit_selection_is(fixture.a, 1u, 4u));
  ASSERT_TRUE(fixture.staged->parent == NULL);
  ASSERT_EQ(my_widget_child_count(root), 1u);
  my_widget_unref(fixture.staged);
  fixture.staged = NULL;
  ASSERT_EQ(atomic_load(&fixture.a->base.ref_count), 1u);
  widget_fixture_destroy(&fixture);
}

TEST(structure_primitives_validate_indices_ownership_and_cycles)
{
  my_widget_t* parent = my_widget_create(NULL, "parent");
  my_widget_t* child = my_widget_create(NULL, "child");
  my_widget_t* outsider = my_widget_create(NULL, "outsider");
  my_widget_t* inserted;
  my_widget_t* staged = NULL;
  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(child);
  ASSERT_NOT_NULL(outsider);
  ASSERT_EQ(my_widget_add_child(parent, child), MY_RET_OK);
  ASSERT_EQ(my_widget_reorder_child(parent, child, 1u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_reorder_child(parent, outsider, 0u), MY_RET_NOT_FOUND);
  ASSERT_EQ(my_widget_detach_child(parent, outsider, &staged), MY_RET_NOT_FOUND);
  ASSERT_TRUE(staged == NULL);
  ASSERT_EQ(my_widget_detach_child(parent, child, NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_insert_child(parent, child, 0u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_insert_child(parent, outsider, 2u), MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(outsider->parent == NULL);
  ASSERT_EQ(atomic_load(&outsider->base.ref_count), 1u);
  ASSERT_EQ(my_widget_insert_child(child, parent, 0u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_insert_child(parent, parent, 0u), MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(child->parent == parent && parent->parent == NULL);

  inserted = outsider;
  ASSERT_EQ(my_widget_insert_child(parent, outsider, 1u), MY_RET_OK);
  outsider = NULL;
  ASSERT_EQ(my_widget_child_count(parent), 2u);
  ASSERT_TRUE(my_widget_get_child(parent, 1u) == inserted);
  ASSERT_TRUE(inserted->parent == parent);
  ASSERT_EQ(atomic_load(&inserted->base.ref_count), 1u);
  ASSERT_EQ(my_widget_reorder_child(parent, child, 1u), MY_RET_OK);
  ASSERT_TRUE(my_widget_get_child(parent, 0u) == inserted);
  ASSERT_TRUE(my_widget_get_child(parent, 1u) == child);
  ASSERT_EQ(my_widget_detach_child(parent, inserted, &staged), MY_RET_OK);
  ASSERT_TRUE(staged == inserted && inserted->parent == NULL);
  ASSERT_EQ(atomic_load(&inserted->base.ref_count), 1u);
  ASSERT_EQ(my_widget_insert_child(parent, staged, 0u), MY_RET_OK);
  staged = NULL;
  ASSERT_TRUE(my_widget_get_child(parent, 0u) == inserted);
  ASSERT_EQ(atomic_load(&inserted->base.ref_count), 1u);

  my_widget_unref(child);
  my_widget_unref(parent);
}

TEST(remove_child_notifies_attached_child_then_releases_tree_reference)
{
  my_widget_t* parent = my_widget_create(NULL, "parent");
  my_widget_t* child = my_widget_create(NULL, "child");
  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(child);
  memset(&s_notify, 0, sizeof(s_notify));
  parent->removed_hook = probe_root_removed;
  parent->child_removed_hook = probe_child_removed;
  ASSERT_EQ(my_widget_add_child(parent, child), MY_RET_OK);
  ASSERT_EQ(atomic_load(&child->base.ref_count), 2u);
  ASSERT_EQ(my_widget_remove_child(parent, child), MY_RET_OK);
  ASSERT_EQ(s_notify.child_calls, 1);
  ASSERT_EQ(s_notify.root_calls, 1);
  ASSERT_EQ(s_notify.order[0], 1);
  ASSERT_EQ(s_notify.order[1], 2);
  ASSERT_TRUE(s_notify.attached[0]);
  ASSERT_TRUE(s_notify.attached[1]);
  ASSERT_TRUE(child->parent == NULL);
  ASSERT_EQ(my_widget_child_count(parent), 0u);
  ASSERT_EQ(atomic_load(&child->base.ref_count), 1u);
  ASSERT_EQ(my_widget_remove_child(parent, child), MY_RET_NOT_FOUND);
  ASSERT_EQ(s_notify.child_calls, 1);
  ASSERT_EQ(s_notify.root_calls, 1);
  my_widget_unref(child);
  my_widget_unref(parent);
  memset(&s_notify, 0, sizeof(s_notify));
}

TEST(style_unset_compacts_storage_and_restores_state_fallback)
{
  my_style_t style;
  my_value_t value;
  my_style_init(&style, NULL);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_int32(&value, 11), MY_RET_OK);
  ASSERT_EQ(my_style_set(&style, MY_STATE_NORMAL, "first", &value), MY_RET_OK);
  ASSERT_EQ(my_value_set_str(&value, "owned-middle"), MY_RET_OK);
  ASSERT_EQ(my_style_set(&style, MY_STATE_NORMAL, "middle", &value), MY_RET_OK);
  ASSERT_EQ(my_value_set_str(&value, "owned-last"), MY_RET_OK);
  ASSERT_EQ(my_style_set(&style, MY_STATE_NORMAL, "last", &value), MY_RET_OK);
  ASSERT_EQ(my_value_set_int32(&value, 7), MY_RET_OK);
  ASSERT_EQ(my_style_set(&style, MY_STATE_NORMAL, "tone", &value), MY_RET_OK);
  ASSERT_EQ(my_value_set_int32(&value, 8), MY_RET_OK);
  ASSERT_EQ(my_style_set(&style, MY_STATE_HOVER, "tone", &value), MY_RET_OK);

  ASSERT_EQ(my_style_unset(&style, MY_STATE_NORMAL, "middle"), MY_RET_OK);
  ASSERT_EQ(style.counts[MY_STATE_NORMAL], 3u);
  ASSERT_STR_EQ(style.props[MY_STATE_NORMAL][0].key, "first");
  ASSERT_STR_EQ(style.props[MY_STATE_NORMAL][1].key, "last");
  ASSERT_STR_EQ(style.props[MY_STATE_NORMAL][2].key, "tone");
  ASSERT_STR_EQ(my_value_get_str(&style.props[MY_STATE_NORMAL][1].value),
                "owned-last");
  ASSERT_EQ(my_value_type(&style.props[MY_STATE_NORMAL][3].value), MY_VALUE_NONE);
  ASSERT_TRUE(my_style_get(&style, MY_STATE_NORMAL, "middle") == NULL);
  ASSERT_EQ(my_style_unset(&style, MY_STATE_NORMAL, "middle"), MY_RET_NOT_FOUND);
  ASSERT_EQ(my_style_unset(&style, MY_STATE_HOVER, "tone"), MY_RET_OK);
  ASSERT_EQ(style.counts[MY_STATE_HOVER], 0u);
  ASSERT_EQ(my_value_get_int32(
                my_style_get(&style, MY_STATE_HOVER, "tone")),
            7);
  ASSERT_EQ(my_style_unset(&style, MY_STATE_HOVER, "tone"), MY_RET_NOT_FOUND);
  ASSERT_EQ(my_value_get_int32(
                my_style_get(&style, MY_STATE_NORMAL, "tone")),
            7);
  ASSERT_EQ(my_style_unset(&style, MY_STATE_COUNT, "tone"),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_style_unset(&style, MY_STATE_NORMAL, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_style_unset(NULL, MY_STATE_NORMAL, "tone"),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_style_unset(&style, MY_STATE_NORMAL,
                           "this-key-is-definitely-too-long-for-style"),
            MY_RET_INVALID_PARAMS);
  my_value_reset(&value);
  my_style_reset(&style);
}

TEST(widget_style_unset_restores_theme_and_invalidates_full_coverage)
{
  my_widget_t* widget = my_widget_create(NULL, "sample");
  my_theme_t* theme = my_theme_create(NULL);
  my_dirty_rects_t dirty;
  my_value_t value;
  const my_rect_t* damage;
  ASSERT_NOT_NULL(widget);
  ASSERT_NOT_NULL(theme);
  my_dirty_rects_init(&dirty);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_widget_set_rect(widget, &(my_rect_t){10, 20, 30, 40}), MY_RET_OK);
  widget->dirty_sink = &dirty;
  ASSERT_EQ(my_widget_apply_theme(widget, theme), MY_RET_OK);
  ASSERT_EQ(my_theme_set_color(theme, "widget", NULL, MY_STATE_NORMAL,
                               MY_STYLE_BG_COLOR, 0x11223344u),
            MY_RET_OK);
  ASSERT_EQ(my_value_set_uint32(&value, 0x55667788u), MY_RET_OK);
  ASSERT_EQ(my_widget_style_set(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                &value),
            MY_RET_OK);
  ASSERT_EQ(my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                      MY_STYLE_BG_COLOR, 0u),
            0x55667788u);
  my_dirty_rects_clear(&dirty);
  widget->dirty = false;

  ASSERT_EQ(my_widget_style_unset(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR),
            MY_RET_OK);
  ASSERT_EQ(my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                      MY_STYLE_BG_COLOR, 0u),
            0x11223344u);
  ASSERT_EQ(widget->local_style->counts[MY_STATE_NORMAL], 0u);
  ASSERT_TRUE(widget->dirty);
  ASSERT_EQ(my_dirty_rects_count(&dirty), 1u);
  damage = my_dirty_rects_get(&dirty, 0u);
  ASSERT_NOT_NULL(damage);
  ASSERT_TRUE(damage->x == 10 && damage->y == 20 && damage->w == 30 &&
              damage->h == 40);

  my_dirty_rects_clear(&dirty);
  widget->dirty = false;
  ASSERT_EQ(my_widget_style_unset(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR),
            MY_RET_NOT_FOUND);
  ASSERT_FALSE(widget->dirty);
  ASSERT_EQ(my_dirty_rects_count(&dirty), 0u);
  ASSERT_EQ(my_widget_style_unset(widget, MY_STATE_COUNT, MY_STYLE_BG_COLOR),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_style_unset(widget, MY_STATE_NORMAL, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_style_unset(NULL, MY_STATE_NORMAL, MY_STYLE_BG_COLOR),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_style_unset(widget, MY_STATE_NORMAL,
                                  "this-key-is-definitely-too-long-for-style"),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(widget->dirty);
  ASSERT_EQ(my_dirty_rects_count(&dirty), 0u);
  my_value_reset(&value);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST_MAIN_BEGIN()
RUN_TEST(reorder_preserves_edit_identity_selection_and_dispatch_state);
RUN_TEST(detach_reinsert_defers_cleanup_until_explicit_notify);
RUN_TEST(structure_primitives_validate_indices_ownership_and_cycles);
RUN_TEST(remove_child_notifies_attached_child_then_releases_tree_reference);
RUN_TEST(style_unset_compacts_storage_and_restores_state_fallback);
RUN_TEST(widget_style_unset_restores_theme_and_invalidates_full_coverage);
TEST_MAIN_END()
