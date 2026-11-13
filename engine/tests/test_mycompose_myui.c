#include "test_framework.h"

#include <stdatomic.h>
#include <string.h>

#include "mypal/dummy/my_pal_dummy.h"
#include "myui/my_layout.h"
#include "myui/my_window.h"
#include "myui/my_window_manager.h"
#include "myui/mycompose/my_compose_internal.h"
#include "myui/mycompose_myui/my_compose_myui.h"
#include "myui/mycompose_myui/my_compose_myui_internal.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_edit.h"

typedef struct fixture_t {
  my_pal_t* pal;
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  MyComposeStore* store;
  MyComposeTreeBuilder* builder;
  MyComposeMyui* adapter;
  MyComposeNodeHandle root;
  MyComposeNodeHandle column;
  MyComposeNodeHandle row;
  MyComposeNodeHandle button;
  MyComposeNodeHandle edit;
  my_widget_t* button_widget;
  my_widget_t* edit_widget;
  my_widget_t* column_widget;
  my_widget_t* row_widget;
  int remember_disposes;
} fixture_t;

typedef struct view_t {
  int values;
  bool swap;
  bool omit_button;
  bool omit_edit;
  bool events;
  bool explicit_none;
  bool remember;
  uint32_t event_type;
  uint8_t event_payload;
  const char* button_type;
  const char* edit_type;
} view_t;

typedef struct style_snapshot_t {
  size_t counts[MY_STATE_COUNT];
  my_style_prop_t props[MY_STATE_COUNT][MY_STYLE_MAX_PROPS];
  char strings[MY_STATE_COUNT][MY_STYLE_MAX_PROPS][64];
} style_snapshot_t;

typedef struct tree_snapshot_t {
  my_widget_t* root_children[8];
  my_widget_t* column_children[8];
  size_t root_count;
  size_t column_count;
  my_widget_t* button;
  my_widget_t* edit;
  char button_text[64];
  bool button_text_is_null;
  uint32_t cooldown;
  char edit_text[64];
  char edit_hint[64];
  bool edit_hint_is_null;
  size_t selection_start;
  size_t selection_end;
  size_t cursor;
  size_t anchor;
  char preedit[64];
  bool has_preedit;
  int32_t ime_caret;
  my_layout_params_t layout;
  style_snapshot_t style;
  bool has_style;
  my_widget_t* focused;
  my_widget_t* grabbed;
  bool edit_focused;
  bool pal_ime;
  int remember_disposes;
} tree_snapshot_t;

static MyComposeStatus reducer_noop(void* context, const MyComposeIntent* intent,
    const void* current, uint32_t current_size, void* candidate,
    uint32_t* candidate_size, MyComposeEffectBatch* batch) {
  (void)context;
  (void)intent;
  (void)batch;
  memcpy(candidate, current, current_size);
  *candidate_size = current_size;
  return MY_COMPOSE_OK;
}

static MyComposeStatus executor_noop(void* context,
    const MyComposeEffect* effect) {
  (void)context;
  (void)effect;
  return MY_COMPOSE_OK;
}

static void remember_dispose(void* context, void* storage, uint32_t size) {
  int* count = (int*)context;
  (void)storage;
  (void)size;
  (*count)++;
}

static MyComposeNodeHandle zero_handle(void) {
  MyComposeNodeHandle zero = {0u, 0u};
  return zero;
}

static MyComposeStatus add_node(MyComposeTreeBuilder* builder,
    MyComposeNodeHandle parent, const char* key, const char* type,
    MyComposeNodeHandle* out) {
  MyComposeNodeDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.parent = parent;
  desc.key = key;
  desc.type = type;
  return my_compose_tree_builder_node(builder, &desc, out);
}

static MyComposeStatus prop(MyComposeTreeBuilder* builder,
    MyComposeNodeHandle owner, const char* name, MyComposeValue value) {
  return my_compose_tree_builder_property(builder, owner, name, &value);
}

static MyComposeValue int_value(int32_t value) {
  MyComposeValue result;
  memset(&result, 0, sizeof(result));
  result.type = MY_COMPOSE_VALUE_INT32;
  result.as.int32_value = value;
  return result;
}

static MyComposeValue color_value(uint32_t value) {
  MyComposeValue result;
  memset(&result, 0, sizeof(result));
  result.type = MY_COMPOSE_VALUE_COLOR;
  result.as.color = value;
  return result;
}

static MyComposeValue string_value(const char* value) {
  MyComposeValue result;
  memset(&result, 0, sizeof(result));
  result.type = MY_COMPOSE_VALUE_STRING;
  result.as.string.data = value;
  result.as.string.size = (uint32_t)strlen(value);
  return result;
}

static MyComposeValue none_value(void) {
  MyComposeValue result;
  memset(&result, 0, sizeof(result));
  result.type = MY_COMPOSE_VALUE_NONE;
  return result;
}

static MyComposeStatus rect_props(MyComposeTreeBuilder* builder,
    MyComposeNodeHandle node, int32_t x, int32_t y, int32_t w, int32_t h) {
  MyComposeStatus status = prop(builder, node, "x", int_value(x));
  if (status != MY_COMPOSE_OK) return status;
  status = prop(builder, node, "y", int_value(y));
  if (status != MY_COMPOSE_OK) return status;
  status = prop(builder, node, "w", int_value(w));
  if (status != MY_COMPOSE_OK) return status;
  return prop(builder, node, "h", int_value(h));
}

static MyComposeStatus declare_button(fixture_t* f, const view_t* view) {
  const char* type = view->button_type != NULL ? view->button_type : "button";
  MyComposeStatus status = add_node(f->builder, f->column, "button", type,
      &f->button);
  if (status != MY_COMPOSE_OK) return status;
  status = rect_props(f->builder, f->button, 0, 0, 100, 30);
  if (status != MY_COMPOSE_OK) return status;
  if (strcmp(type, "button") == 0 && view->explicit_none) {
    status = prop(f->builder, f->button, "text", none_value());
    if (status != MY_COMPOSE_OK) return status;
    status = prop(f->builder, f->button, "cooldown", none_value());
    if (status != MY_COMPOSE_OK) return status;
    status = prop(f->builder, f->button, "layout", none_value());
    if (status != MY_COMPOSE_OK) return status;
    status = prop(f->builder, f->button, "style:bg_color", none_value());
    if (status != MY_COMPOSE_OK) return status;
  } else if (strcmp(type, "button") == 0 && view->values != 0) {
    status = prop(f->builder, f->button, "text",
        string_value(view->values == 1 ? "first" : "changed"));
    if (status != MY_COMPOSE_OK) return status;
    if (view->values == 2) {
      status = prop(f->builder, f->button, "cooldown", int_value(12));
      if (status != MY_COMPOSE_OK) return status;
      status = prop(f->builder, f->button, "layout",
          string_value("w:50% h:1f"));
      if (status != MY_COMPOSE_OK) return status;
      status = prop(f->builder, f->button, "style:bg_color",
          color_value(0x11223344u));
      if (status != MY_COMPOSE_OK) return status;
    }
  }
  if (strcmp(type, "button") == 0 && view->events) {
    MyComposeIntent intent;
    uint8_t payload = view->event_payload != 0u ? view->event_payload : 77u;
    memset(&intent, 0, sizeof(intent));
    intent.type = view->event_type != 0u ? view->event_type : 91u;
    intent.owner.index = 200u;
    intent.owner.generation = 9u;
    intent.payload = &payload;
    intent.payload_size = 1u;
    status = my_compose_tree_builder_event(f->builder, f->button, "click",
        &intent);
    if (status != MY_COMPOSE_OK) return status;
  }
  return MY_COMPOSE_OK;
}

static MyComposeStatus declare_edit(fixture_t* f, const view_t* view) {
  MyComposeStatus status = add_node(f->builder, f->column, "edit",
      view->edit_type != NULL ? view->edit_type : "edit", &f->edit);
  if (status != MY_COMPOSE_OK) return status;
  status = rect_props(f->builder, f->edit, 0, 40, 100, 30);
  if (status != MY_COMPOSE_OK) return status;
  if (strcmp(view->edit_type != NULL ? view->edit_type : "edit", "edit") == 0) {
    if (view->explicit_none) {
      status = prop(f->builder, f->edit, "text", none_value());
      if (status != MY_COMPOSE_OK) return status;
      status = prop(f->builder, f->edit, "hint", none_value());
      if (status != MY_COMPOSE_OK) return status;
    } else if (view->values != 0) {
      status = prop(f->builder, f->edit, "text",
          string_value(view->values == 1 ? "alpha" : "bravo"));
      if (status != MY_COMPOSE_OK) return status;
      status = prop(f->builder, f->edit, "hint",
          string_value(view->values == 1 ? "hint" : "newhint"));
      if (status != MY_COMPOSE_OK) return status;
    }
    if (view->remember) {
      MyComposeRememberOps ops;
      void* storage = NULL;
      memset(&ops, 0, sizeof(ops));
      ops.context = &f->remember_disposes;
      ops.dispose = remember_dispose;
      status = my_compose_tree_builder_remember(f->builder, f->edit, 0u, 7u,
          sizeof(int), _Alignof(int), &ops, &storage);
      if (status != MY_COMPOSE_OK) return status;
      if (storage != NULL) memcpy(storage, &f->remember_disposes, sizeof(int));
    }
  }
  return MY_COMPOSE_OK;
}

static MyComposeStatus begin_view(fixture_t* f, const view_t* view) {
  MyComposeStatus status = my_compose_tree_builder_begin(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  status = add_node(f->builder, zero_handle(), NULL, "@root", &f->root);
  if (status != MY_COMPOSE_OK) return status;
  status = add_node(f->builder, f->root, "column", "@column", &f->column);
  if (status != MY_COMPOSE_OK) return status;
  status = rect_props(f->builder, f->column, 0, 0, 200, 100);
  if (status != MY_COMPOSE_OK) return status;
  if (view->swap) {
    if (!view->omit_edit) {
      status = declare_edit(f, view);
      if (status != MY_COMPOSE_OK) return status;
    }
    if (!view->omit_button) {
      status = declare_button(f, view);
      if (status != MY_COMPOSE_OK) return status;
    }
  } else {
    if (!view->omit_button) {
      status = declare_button(f, view);
      if (status != MY_COMPOSE_OK) return status;
    }
    if (!view->omit_edit) {
      status = declare_edit(f, view);
      if (status != MY_COMPOSE_OK) return status;
    }
  }
  status = add_node(f->builder, f->root, "row", "@row", &f->row);
  if (status != MY_COMPOSE_OK) return status;
  return rect_props(f->builder, f->row, 0, 110, 200, 30);
}

static MyComposeStatus apply_view(fixture_t* f, const view_t* view) {
  MyComposeStatus status = begin_view(f, view);
  const MyComposeDiff* diff;
  if (status != MY_COMPOSE_OK) return status;
  status = my_compose_tree_builder_end(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  diff = my_compose_tree_builder_diff(f->builder);
  if (diff == NULL) return MY_COMPOSE_FAILED;
  status = my_compose_myui_stage(f->adapter, diff);
  if (status != MY_COMPOSE_OK) {
    my_compose_myui_rollback(f->adapter);
    return status;
  }
  status = my_compose_tree_builder_finalize(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  my_compose_myui_commit(f->adapter);
  f->button_widget = my_compose_myui_widget(f->adapter, f->button);
  f->edit_widget = my_compose_myui_widget(f->adapter, f->edit);
  f->column_widget = my_compose_myui_widget(f->adapter, f->column);
  f->row_widget = my_compose_myui_widget(f->adapter, f->row);
  return MY_COMPOSE_OK;
}

static void fixture_destroy(fixture_t* f) {
  my_compose_myui_destroy(f->adapter);
  my_compose_tree_builder_destroy(f->builder);
  my_compose_store_destroy(f->store);
  my_window_manager_destroy(f->wm);
  my_widget_unref((my_widget_t*)f->win);
  my_pal_main_loop_destroy(f->loop);
  my_pal_destroy(f->pal);
  memset(f, 0, sizeof(*f));
}

static bool fixture_init_empty_ex(fixture_t* f, bool csd) {
  int state = 0;
  memset(f, 0, sizeof(*f));
  f->pal = my_pal_dummy_create(NULL);
  if (f->pal != NULL) my_pal_dummy_set_needs_csd(f->pal, csd);
  f->loop = my_pal_main_loop_create(f->pal);
  f->wm = my_window_manager_create(NULL, f->pal, f->loop);
  f->win = my_window_create(NULL, f->pal, 240, 180, "compose");
  f->store = my_compose_store_create(&state, sizeof(state), NULL, NULL,
      reducer_noop, NULL, executor_noop);
  f->builder = my_compose_tree_builder_create();
  if (f->pal == NULL || f->loop == NULL || f->wm == NULL || f->win == NULL ||
      f->store == NULL || f->builder == NULL ||
      my_window_manager_open(f->wm, f->win) != MY_RET_OK) {
    fixture_destroy(f);
    return false;
  }
  f->adapter = my_compose_myui_create(f->win, f->builder, f->store);
  if (f->adapter == NULL) {
    fixture_destroy(f);
    return false;
  }
  return true;
}

static bool fixture_init_empty(fixture_t* f) {
  return fixture_init_empty_ex(f, false);
}

static bool fixture_init(fixture_t* f) {
  view_t initial;
  memset(&initial, 0, sizeof(initial));
  initial.values = 1;
  initial.events = true;
  initial.remember = true;
  if (!fixture_init_empty(f)) return false;
  if (apply_view(f, &initial) != MY_COMPOSE_OK) {
    fixture_destroy(f);
    return false;
  }
  return true;
}

static void focus_edit(fixture_t* f) {
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  my_edit_t* edit = (my_edit_t*)f->edit_widget;
  event.u.pointer.x = 5;
  event.u.pointer.y = 45;
  (void)my_event_dispatch(&f->win->dispatcher, &event);
  edit->cursor = 4u;
  edit->anchor = 1u;
  event = my_event_init(MY_EVENT_IME_PREEDIT);
  event.u.ime.text = "ni";
  event.u.ime.cursor = 1;
  (void)my_event_dispatch(&f->win->dispatcher, &event);
}

static void style_snapshot_capture(my_widget_t* widget, style_snapshot_t* out,
    bool* has_style) {
  size_t state;
  size_t index;
  memset(out, 0, sizeof(*out));
  *has_style = widget->local_style != NULL;
  if (widget->local_style == NULL) return;
  for (state = 0u; state < MY_STATE_COUNT; state++) {
    out->counts[state] = widget->local_style->counts[state];
    for (index = 0u; index < out->counts[state]; index++) {
      const my_style_prop_t* source = &widget->local_style->props[state][index];
      out->props[state][index] = *source;
      if (source->value.type == MY_VALUE_STR && source->value.u.str != NULL) {
        size_t length = strlen(source->value.u.str);
        if (length >= sizeof(out->strings[state][index])) {
          length = sizeof(out->strings[state][index]) - 1u;
        }
        memcpy(out->strings[state][index], source->value.u.str, length);
        out->strings[state][index][length] = '\0';
        out->props[state][index].value.u.str = out->strings[state][index];
      }
    }
  }
}

static void snapshot_capture(fixture_t* f, tree_snapshot_t* out) {
  my_widget_t* root = my_window_widget(f->win);
  my_button_t* button = (my_button_t*)f->button_widget;
  my_edit_t* edit = (my_edit_t*)f->edit_widget;
  size_t index;
  memset(out, 0, sizeof(*out));
  out->root_count = my_widget_child_count(root);
  out->column_count = my_widget_child_count(f->column_widget);
  for (index = 0u; index < out->root_count && index < 8u; index++) {
    out->root_children[index] = my_widget_get_child(root, index);
  }
  for (index = 0u; index < out->column_count && index < 8u; index++) {
    out->column_children[index] = my_widget_get_child(f->column_widget, index);
  }
  out->button = f->button_widget;
  out->edit = f->edit_widget;
  out->button_text_is_null = button->text == NULL;
  if (button->text != NULL) snprintf(out->button_text, sizeof(out->button_text), "%s", button->text);
  out->cooldown = button->cooldown_ms;
  snprintf(out->edit_text, sizeof(out->edit_text), "%s", my_edit_get_text(f->edit_widget));
  out->edit_hint_is_null = edit->hint == NULL;
  if (edit->hint != NULL) snprintf(out->edit_hint, sizeof(out->edit_hint), "%s", edit->hint);
  my_edit_get_selection(f->edit_widget, &out->selection_start, &out->selection_end);
  out->cursor = edit->cursor;
  out->anchor = edit->anchor;
  out->has_preedit = edit->ime_preedit != NULL;
  if (edit->ime_preedit != NULL) snprintf(out->preedit, sizeof(out->preedit), "%s", edit->ime_preedit);
  out->ime_caret = edit->ime_caret;
  out->layout = f->button_widget->layout_params;
  style_snapshot_capture(f->button_widget, &out->style, &out->has_style);
  out->focused = f->win->dispatcher.focused;
  out->grabbed = f->win->dispatcher.grabbed;
  out->edit_focused = edit->focused;
  out->pal_ime = my_pal_dummy_get_ime_enabled(f->win->pal_window);
  out->remember_disposes = f->remember_disposes;
}

static bool value_snapshot_equal(const my_value_t* a, const my_value_t* b) {
  if (a->type != b->type) return false;
  if (a->type == MY_VALUE_STR) {
    const char* as = a->u.str != NULL ? a->u.str : "";
    const char* bs = b->u.str != NULL ? b->u.str : "";
    return strcmp(as, bs) == 0;
  }
  if (a->type == MY_VALUE_NONE) return true;
  return memcmp(&a->u, &b->u, sizeof(a->u)) == 0;
}

static bool style_snapshot_matches(const my_widget_t* widget,
    const style_snapshot_t* snapshot, bool had_style) {
  size_t state;
  size_t index;
  if ((widget->local_style != NULL) != had_style) return false;
  if (!had_style) return true;
  for (state = 0u; state < MY_STATE_COUNT; state++) {
    if (widget->local_style->counts[state] != snapshot->counts[state]) return false;
    for (index = 0u; index < snapshot->counts[state]; index++) {
      const my_style_prop_t* a = &widget->local_style->props[state][index];
      const my_style_prop_t* b = &snapshot->props[state][index];
      if (strcmp(a->key, b->key) != 0 ||
          !value_snapshot_equal(&a->value, &b->value)) return false;
    }
  }
  return true;
}

static bool snapshot_matches(fixture_t* f, const tree_snapshot_t* snapshot) {
  my_widget_t* root = my_window_widget(f->win);
  my_button_t* button = (my_button_t*)f->button_widget;
  my_edit_t* edit = (my_edit_t*)f->edit_widget;
  size_t start = 0u;
  size_t end = 0u;
  size_t index;
  if (my_widget_child_count(root) != snapshot->root_count ||
      my_widget_child_count(f->column_widget) != snapshot->column_count) return false;
  for (index = 0u; index < snapshot->root_count; index++) {
    if (my_widget_get_child(root, index) != snapshot->root_children[index]) return false;
  }
  for (index = 0u; index < snapshot->column_count; index++) {
    if (my_widget_get_child(f->column_widget, index) != snapshot->column_children[index]) return false;
  }
  if (f->button_widget != snapshot->button || f->edit_widget != snapshot->edit ||
      (button->text == NULL) != snapshot->button_text_is_null ||
      (button->text != NULL && strcmp(button->text, snapshot->button_text) != 0) ||
      button->cooldown_ms != snapshot->cooldown ||
      strcmp(my_edit_get_text(f->edit_widget), snapshot->edit_text) != 0 ||
      (edit->hint == NULL) != snapshot->edit_hint_is_null ||
      (edit->hint != NULL && strcmp(edit->hint, snapshot->edit_hint) != 0)) return false;
  my_edit_get_selection(f->edit_widget, &start, &end);
  if (start != snapshot->selection_start || end != snapshot->selection_end ||
      edit->cursor != snapshot->cursor || edit->anchor != snapshot->anchor ||
      (edit->ime_preedit != NULL) != snapshot->has_preedit ||
      (edit->ime_preedit != NULL && strcmp(edit->ime_preedit, snapshot->preedit) != 0) ||
      edit->ime_caret != snapshot->ime_caret ||
      memcmp(&f->button_widget->layout_params, &snapshot->layout,
          sizeof(snapshot->layout)) != 0 ||
      !style_snapshot_matches(f->button_widget, &snapshot->style,
          snapshot->has_style) ||
      f->win->dispatcher.focused != snapshot->focused ||
      f->win->dispatcher.grabbed != snapshot->grabbed ||
      edit->focused != snapshot->edit_focused ||
      my_pal_dummy_get_ime_enabled(f->win->pal_window) != snapshot->pal_ime ||
      f->remember_disposes != snapshot->remember_disposes) return false;
  return true;
}

TEST(initial_create_reorder_and_type_replace_have_one_finalize) {
  fixture_t f;
  view_t view;
  my_widget_t* old_button;
  my_widget_t* old_edit;
  MyComposeNodeHandle old_edit_handle;
  ASSERT_TRUE(fixture_init(&f));
  ASSERT_NOT_NULL(f.button_widget);
  ASSERT_NOT_NULL(f.edit_widget);
  ASSERT_NOT_NULL(f.row_widget);
  ASSERT_NOT_NULL(f.column_widget);
  old_button = f.button_widget;
  old_edit = f.edit_widget;
  old_edit_handle = f.edit;
  focus_edit(&f);
  ASSERT_TRUE(f.win->dispatcher.focused == f.edit_widget);

  memset(&view, 0, sizeof(view));
  view.values = 1;
  view.events = true;
  view.swap = true;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_TRUE(f.button_widget == old_button);
  ASSERT_TRUE(f.edit_widget == old_edit);
  ASSERT_TRUE(my_widget_get_child(f.column_widget, 0u) == old_edit);
  ASSERT_TRUE(my_widget_get_child(f.column_widget, 1u) == old_button);
  ASSERT_TRUE(f.win->dispatcher.focused == old_edit);
  ASSERT_TRUE(f.win->dispatcher.grabbed == old_edit);
  ASSERT_TRUE(my_pal_dummy_get_ime_enabled(f.win->pal_window));
  ASSERT_EQ(f.remember_disposes, 0);

  my_widget_ref(old_edit);
  view.edit_type = "button";
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_TRUE(f.edit_widget != old_edit);
  ASSERT_EQ(f.remember_disposes, 1);
  ASSERT_EQ(my_compose_store_dispatch(f.store, &(MyComposeIntent){
      .type = 91u, .owner = old_edit_handle}), MY_COMPOSE_STALE);
  ASSERT_EQ(my_emitter_emit(old_edit->emitter, "changed", NULL), MY_RET_OK);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, 0u);
  my_widget_unref(old_edit);
  fixture_destroy(&f);
}

TEST(delete_defers_focus_ime_cleanup_and_listener_revoke_until_commit) {
  fixture_t f;
  view_t view;
  my_widget_t* removed;
  MyComposeNodeHandle removed_handle;
  MyComposeStatus status;
  ASSERT_TRUE(fixture_init(&f));
  focus_edit(&f);
  removed = my_widget_ref(f.edit_widget);
  removed_handle = f.edit;
  memset(&view, 0, sizeof(view));
  view.values = 1;
  view.events = true;
  view.edit_type = "button";
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  status = my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder));
  ASSERT_EQ(status, MY_COMPOSE_OK);
  ASSERT_TRUE(f.win->dispatcher.focused == removed);
  ASSERT_TRUE(f.win->dispatcher.grabbed == removed);
  ASSERT_TRUE(my_pal_dummy_get_ime_enabled(f.win->pal_window));
  ASSERT_EQ(f.remember_disposes, 0);
  ASSERT_EQ(my_compose_tree_builder_finalize(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(f.remember_disposes, 1);
  ASSERT_TRUE(f.win->dispatcher.focused == removed);
  my_compose_myui_commit(f.adapter);
  ASSERT_TRUE(f.win->dispatcher.focused == NULL);
  ASSERT_TRUE(f.win->dispatcher.grabbed == NULL);
  ASSERT_FALSE(my_pal_dummy_get_ime_enabled(f.win->pal_window));
  ASSERT_EQ(my_compose_store_dispatch(f.store, &(MyComposeIntent){
      .type = 1u, .owner = removed_handle}), MY_COMPOSE_STALE);
  my_widget_unref(removed);
  fixture_destroy(&f);
}

TEST(listener_forces_owner_and_event_omission_keeps_owner_generation) {
  fixture_t f;
  view_t view;
  uint32_t generation;
  uint64_t accepted;
  my_event_t event;
  ASSERT_TRUE(fixture_init(&f));
  generation = f.store->owners[f.button.index].generation;
  ASSERT_EQ(generation, f.button.generation);
  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 5;
  event.u.pointer.y = 5;
  (void)my_event_dispatch(&f.win->dispatcher, &event);
  event = my_event_init(MY_EVENT_POINTER_UP);
  event.u.pointer.x = 5;
  event.u.pointer.y = 5;
  (void)my_event_dispatch(&f.win->dispatcher, &event);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, 1u);
  ASSERT_EQ(f.store->intents[0].intent.owner.index, f.button.index);
  ASSERT_EQ(f.store->intents[0].intent.owner.generation, f.button.generation);
  ASSERT_EQ(f.store->intents[0].intent.type, 91u);
  ASSERT_EQ(f.store->intents[0].intent.payload_size, 1u);
  ASSERT_EQ(f.store->intents[0].payload[0], 77u);

  accepted = my_compose_store_diagnostics(f.store)->accepted_intents;
  memset(&view, 0, sizeof(view));
  view.values = 1;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(f.store->owners[f.button.index].generation, generation);
  ASSERT_EQ(my_emitter_emit(f.button_widget->emitter, "click", NULL), MY_RET_OK);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, accepted);
  fixture_destroy(&f);
}

TEST(omission_and_explicit_none_restore_defaults_and_intrinsic_layout) {
  fixture_t f;
  view_t view;
  ASSERT_TRUE(fixture_init(&f));
  memset(&view, 0, sizeof(view));
  view.values = 2;
  view.events = true;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_STR_EQ(((my_button_t*)f.button_widget)->text, "changed");
  ASSERT_EQ(((my_button_t*)f.button_widget)->cooldown_ms, 12u);
  ASSERT_EQ(f.button_widget->layout_params.w_mode, MY_LAYOUT_PERCENT);
  ASSERT_EQ(f.button_widget->layout_params.h_mode, MY_LAYOUT_FLEX);
  ASSERT_EQ(f.button_widget->local_style->counts[MY_STATE_NORMAL], 1u);

  view.values = 0;
  view.events = false;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_TRUE(((my_button_t*)f.button_widget)->text == NULL);
  ASSERT_EQ(((my_button_t*)f.button_widget)->cooldown_ms, 0u);
  ASSERT_EQ(f.button_widget->layout_params.w_mode, MY_LAYOUT_AUTO);
  ASSERT_EQ(f.button_widget->layout_params.h_mode, MY_LAYOUT_AUTO);
  ASSERT_TRUE(f.button_widget->layouter == my_layouter_default());
  ASSERT_TRUE(f.column_widget->layouter != my_layouter_default());
  ASSERT_TRUE(f.row_widget->layouter != my_layouter_default());
  ASSERT_TRUE(f.button_widget->local_style == NULL ||
      f.button_widget->local_style->counts[MY_STATE_NORMAL] == 0u);
  ASSERT_STR_EQ(my_edit_get_text(f.edit_widget), "");
  ASSERT_TRUE(((my_edit_t*)f.edit_widget)->hint == NULL);

  view.values = 2;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  view.values = 0;
  view.explicit_none = true;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_TRUE(((my_button_t*)f.button_widget)->text == NULL);
  ASSERT_EQ(((my_button_t*)f.button_widget)->cooldown_ms, 0u);
  ASSERT_EQ(f.button_widget->layout_params.w_mode, MY_LAYOUT_AUTO);
  ASSERT_TRUE(f.button_widget->local_style == NULL ||
      f.button_widget->local_style->counts[MY_STATE_NORMAL] == 0u);
  ASSERT_STR_EQ(my_edit_get_text(f.edit_widget), "");
  fixture_destroy(&f);
}

TEST(property_failure_restores_complete_snapshot_without_setter_rewind) {
  fixture_t f;
  view_t view;
  tree_snapshot_t before;
  ASSERT_TRUE(fixture_init(&f));
  memset(&view, 0, sizeof(view));
  view.values = 2;
  view.events = true;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  focus_edit(&f);
  snapshot_capture(&f, &before);
  view.values = 1;
  f.adapter->fault.property_widget = f.edit_widget;
  f.adapter->fault.property_name = "text";
  f.adapter->fault.fail_after_property_error = true;
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_FAILED);
  ASSERT_TRUE(snapshot_matches(&f, &before));
  ASSERT_EQ(f.adapter->stats.property_restore_set_calls, 0u);
  ASSERT_EQ(f.adapter->stats.notifies, 0u);
  my_compose_myui_rollback(f.adapter);
  ASSERT_TRUE(snapshot_matches(&f, &before));
  fixture_destroy(&f);
}

TEST(null_style_rollback_restores_exact_pointer_and_allows_reuse) {
  fixture_t f;
  view_t view;
  const my_style_t* original;
  const my_value_t* color;
  ASSERT_TRUE(fixture_init(&f));
  original = f.button_widget->local_style;
  ASSERT_TRUE(original == NULL);
  memset(&view, 0, sizeof(view));
  view.values = 2;
  view.events = true;
  f.adapter->fault.property_widget = f.edit_widget;
  f.adapter->fault.property_name = "text";
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_FAILED);
  ASSERT_TRUE(f.button_widget->local_style == original);
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_NOT_NULL(f.button_widget->local_style);
  ASSERT_EQ(f.button_widget->local_style->counts[MY_STATE_NORMAL], 1u);
  color = my_style_get(f.button_widget->local_style, MY_STATE_NORMAL, "bg_color");
  ASSERT_NOT_NULL(color);
  ASSERT_EQ(my_value_get_uint32(color), 0x11223344u);
  fixture_destroy(&f);
}

TEST(factory_insert_and_style_capacity_failures_leave_original_tree) {
  fixture_t f;
  view_t view;
  tree_snapshot_t before;
  char key[32];
  size_t index;
  ASSERT_TRUE(fixture_init(&f));
  memset(&view, 0, sizeof(view));
  view.values = 2;
  view.events = true;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  focus_edit(&f);
  snapshot_capture(&f, &before);

  view.values = 1;
  f.adapter->fault.factory_call = 1u;
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_OK);
  my_compose_myui_rollback(f.adapter);
  ASSERT_TRUE(snapshot_matches(&f, &before));

  view.edit_type = "button";
  f.adapter->fault.factory_call = 1u;
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_FAILED);
  ASSERT_TRUE(snapshot_matches(&f, &before));

  view.edit_type = "button";
  f.adapter->fault.factory_call = 0u;
  f.adapter->fault.insert_call = 1u;
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_FAILED);
  ASSERT_TRUE(snapshot_matches(&f, &before));

  f.adapter->fault.insert_call = 0u;
  for (index = f.button_widget->local_style->counts[MY_STATE_NORMAL];
      index < MY_STYLE_MAX_PROPS; index++) {
    snprintf(key, sizeof(key), "k%02u", (unsigned)index);
    ASSERT_EQ(my_widget_style_set(f.button_widget, MY_STATE_NORMAL, key,
        &(my_value_t){.type = MY_VALUE_INT32, .u.i32 = (int32_t)index}), MY_RET_OK);
  }
  snapshot_capture(&f, &before);
  view.values = 2;
  view.edit_type = NULL;
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(prop(f.builder, f.button, "style:border_width", int_value(2)),
      MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_OVERLOAD);
  ASSERT_TRUE(snapshot_matches(&f, &before));
  fixture_destroy(&f);
}

TEST(first_and_second_detach_failures_restore_original_order) {
  fixture_t f;
  view_t view;
  tree_snapshot_t before;
  size_t case_index;
  ASSERT_TRUE(fixture_init(&f));
  memset(&view, 0, sizeof(view));
  view.values = 2;
  view.events = true;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  focus_edit(&f);
  view.values = 0;
  view.events = false;
  for (case_index = 1u; case_index <= 2u; case_index++) {
    snapshot_capture(&f, &before);
    view.button_type = "widget";
    view.edit_type = "widget";
    f.adapter->fault.detach_call = (uint32_t)case_index;
    f.adapter->fault.fail_after_detach_error = true;
    ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_myui_stage(f.adapter,
        my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_FAILED);
    ASSERT_TRUE(snapshot_matches(&f, &before));
    ASSERT_EQ(f.adapter->stats.notifies, 0u);
    f.adapter->fault.detach_call = 0u;
    f.adapter->fault.fail_after_detach_error = false;
    view.button_type = NULL;
    view.edit_type = NULL;
  }
  fixture_destroy(&f);
}

TEST(duplicate_key_and_external_reorder_fail_before_factory) {
  fixture_t f;
  view_t view;
  MyComposeDiffOp duplicate_ops[2];
  MyComposeDiff duplicate;
  uint32_t factory_calls;
  ASSERT_TRUE(fixture_init(&f));
  memset(&view, 0, sizeof(view));
  view.values = 1;
  view.events = true;
  view.edit_type = "button";
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  duplicate = *my_compose_tree_builder_diff(f.builder);
  ASSERT_EQ(duplicate.count, 2u);
  duplicate_ops[0] = duplicate.ops[1];
  duplicate_ops[1] = duplicate.ops[1];
  duplicate.ops = duplicate_ops;
  duplicate.count = 2u;
  factory_calls = f.adapter->stats.factory_calls;
  ASSERT_EQ(my_compose_myui_stage(f.adapter, &duplicate),
      MY_COMPOSE_DUPLICATE_KEY);
  ASSERT_EQ(f.adapter->stats.factory_calls, factory_calls);
  my_compose_myui_rollback(f.adapter);

  ASSERT_EQ(my_widget_reorder_child(my_window_widget(f.win), f.row_widget, 0u),
      MY_RET_OK);
  view.edit_type = NULL;
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_CONFLICT);
  ASSERT_EQ(f.adapter->stats.factory_calls, factory_calls);
  fixture_destroy(&f);
}

TEST(string_property_without_transaction_callbacks_is_not_supported) {
  fixture_t f;
  view_t view;
  uint32_t factory_calls;
  ASSERT_TRUE(fixture_init(&f));
  memset(&view, 0, sizeof(view));
  view.values = 1;
  view.edit_type = "label";
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(prop(f.builder, f.edit, "text", string_value("label")),
      MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  factory_calls = f.adapter->stats.factory_calls;
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_NOT_SUPPORTED);
  ASSERT_EQ(f.adapter->stats.factory_calls, factory_calls);
  fixture_destroy(&f);
}

static MyComposeStatus apply_event_transition(fixture_t* f,
    MyComposeNodeHandle nodes[128], uint32_t version, uint32_t update_count,
    bool commit) {
  MyComposeStatus status = my_compose_tree_builder_begin(f->builder);
  uint32_t node;
  if (status != MY_COMPOSE_OK) return status;
  status = add_node(f->builder, zero_handle(), NULL, "@root", &f->root);
  if (status != MY_COMPOSE_OK) return status;
  status = add_node(f->builder, f->root, "column", "@column", &f->column);
  if (status != MY_COMPOSE_OK) return status;
  for (node = 0u; node < 128u; node++) {
    char key[16];
    uint32_t event_index;
    snprintf(key, sizeof(key), "e%u", (unsigned)node);
    status = add_node(f->builder, f->column, key, "edit", &nodes[node]);
    if (status != MY_COMPOSE_OK) return status;
    for (event_index = 0u; event_index < 2u; event_index++) {
      MyComposeIntent intent;
      uint8_t payload = (uint8_t)(node +
          (node < update_count ? version : 1u));
      memset(&intent, 0, sizeof(intent));
      intent.type = 101u + event_index;
      intent.payload = &payload;
      intent.payload_size = 1u;
      status = my_compose_tree_builder_event(f->builder, nodes[node],
          event_index == 0u ? "changed" : "activate", &intent);
      if (status != MY_COMPOSE_OK) return status;
    }
  }
  status = my_compose_tree_builder_end(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  status = my_compose_myui_stage(f->adapter,
      my_compose_tree_builder_diff(f->builder));
  if (status != MY_COMPOSE_OK || !commit) return status;
  status = my_compose_tree_builder_finalize(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  my_compose_myui_commit(f->adapter);
  return MY_COMPOSE_OK;
}

static void verify_event_transition(fixture_t* f,
    MyComposeNodeHandle nodes[128], uint32_t version, uint32_t update_count) {
  uint32_t node;
  for (node = 0u; node < 128u; node++) {
    my_widget_t* widget = my_compose_myui_widget(f->adapter, nodes[node]);
    uint32_t event_index;
    ASSERT_NOT_NULL(widget);
    for (event_index = 0u; event_index < 2u; event_index++) {
      uint64_t accepted = my_compose_store_diagnostics(f->store)->accepted_intents;
      uint32_t queue_index;
      uint8_t expected_payload = (uint8_t)(node +
          (node < update_count ? version : 1u));
      ASSERT_EQ(my_emitter_emit(widget->emitter,
          event_index == 0u ? "changed" : "activate", NULL), MY_RET_OK);
      ASSERT_EQ(my_compose_store_diagnostics(f->store)->accepted_intents,
          accepted + 1u);
      ASSERT_EQ(f->store->intent_count, 1u);
      queue_index = (f->store->intent_head + f->store->intent_count - 1u) %
          MY_COMPOSE_INTENT_CAPACITY;
      ASSERT_EQ(f->store->intents[queue_index].intent.type, 101u + event_index);
      ASSERT_EQ(f->store->intents[queue_index].intent.owner.index,
          nodes[node].index);
      ASSERT_EQ(f->store->intents[queue_index].intent.owner.generation,
          nodes[node].generation);
      ASSERT_EQ(f->store->intents[queue_index].payload[0], expected_payload);
      ASSERT_EQ(my_compose_store_reduce(f->store), MY_COMPOSE_OK);
    }
  }
}

TEST(listener_history_uses_both_banks_and_rolls_back_only_new_leases) {
  fixture_t f;
  MyComposeNodeHandle nodes[128];
  uint64_t accepted;
  ASSERT_TRUE(fixture_init_empty(&f));
  ASSERT_EQ(apply_event_transition(&f, nodes, 1u, 128u, true), MY_COMPOSE_OK);
  ASSERT_EQ(apply_event_transition(&f, nodes, 2u, 64u, true), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_diff(f.builder)->count, 128u);
  verify_event_transition(&f, nodes, 2u, 64u);

  ASSERT_EQ(apply_event_transition(&f, nodes, 3u, 128u, true), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_diff(f.builder)->count, 256u);
  verify_event_transition(&f, nodes, 3u, 128u);

  ASSERT_EQ(apply_event_transition(&f, nodes, 4u, 128u, false), MY_COMPOSE_OK);
  accepted = my_compose_store_diagnostics(f.store)->accepted_intents;
  ASSERT_EQ(my_emitter_emit(my_compose_myui_widget(f.adapter, nodes[0])->emitter,
      "changed", NULL), MY_RET_OK);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, accepted);
  my_compose_myui_rollback(f.adapter);
  verify_event_transition(&f, nodes, 3u, 128u);
  ASSERT_EQ(apply_event_transition(&f, nodes, 4u, 128u, true), MY_COMPOSE_OK);
  verify_event_transition(&f, nodes, 4u, 128u);
  fixture_destroy(&f);
}

TEST(listener_update_and_type_replace_revoke_old_lease) {
  fixture_t f;
  view_t view;
  my_widget_t* old_button;
  MyComposeNodeHandle old_handle;
  uint32_t owner_generation;
  ASSERT_TRUE(fixture_init(&f));
  ASSERT_EQ(my_emitter_emit(f.button_widget->emitter, "click", NULL), MY_RET_OK);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, 1u);
  memset(&view, 0, sizeof(view));
  view.values = 1;
  view.events = true;
  view.event_type = 92u;
  view.event_payload = 88u;
  owner_generation = f.store->owners[f.button.index].generation;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_emitter_emit(f.button_widget->emitter, "click", NULL), MY_RET_OK);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, 2u);
  ASSERT_EQ(f.store->intents[1].intent.type, 92u);
  ASSERT_EQ(f.store->intents[1].payload[0], 88u);
  ASSERT_EQ(f.store->intents[1].intent.owner.index, f.button.index);
  ASSERT_EQ(f.store->intents[1].intent.owner.generation, f.button.generation);
  ASSERT_EQ(f.store->owners[f.button.index].generation, owner_generation);

  old_button = my_widget_ref(f.button_widget);
  old_handle = f.button;
  view.button_type = "edit";
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_TRUE(f.button_widget != old_button);
  ASSERT_EQ(my_emitter_emit(old_button->emitter, "click", NULL), MY_RET_OK);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, 2u);
  ASSERT_EQ(my_compose_store_dispatch(f.store, &(MyComposeIntent){
      .type = 92u, .owner = old_handle}), MY_COMPOSE_STALE);
  my_widget_unref(old_button);
  fixture_destroy(&f);
}

TEST(delete_revokes_old_listener_lease) {
  fixture_t f;
  view_t view;
  my_widget_t* old_button;
  MyComposeNodeHandle old_handle;
  ASSERT_TRUE(fixture_init(&f));
  ASSERT_EQ(my_emitter_emit(f.button_widget->emitter, "click", NULL), MY_RET_OK);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, 1u);
  old_button = my_widget_ref(f.button_widget);
  old_handle = f.button;
  memset(&view, 0, sizeof(view));
  view.values = 1;
  view.events = true;
  view.omit_button = true;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_emitter_emit(old_button->emitter, "click", NULL), MY_RET_OK);
  ASSERT_EQ(my_compose_store_diagnostics(f.store)->accepted_intents, 1u);
  ASSERT_EQ(my_compose_store_dispatch(f.store, &(MyComposeIntent){
      .type = 91u, .owner = old_handle}), MY_COMPOSE_STALE);
  my_widget_unref(old_button);
  fixture_destroy(&f);
}

TEST(delete_generation_retirement_is_rejected_before_finalize) {
  fixture_t f;
  view_t view;
  tree_snapshot_t before;
  uint32_t factory_calls;
  ASSERT_TRUE(fixture_init(&f));
  memset(&view, 0, sizeof(view));
  view.values = 1;
  view.events = true;
  view.omit_button = true;
  ASSERT_EQ(my_compose_myui_internal_seed_generation(f.adapter, f.button,
      UINT32_MAX - 1u), MY_COMPOSE_OK);
  snapshot_capture(&f, &before);
  factory_calls = f.adapter->stats.factory_calls;
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_OVERLOAD);
  ASSERT_EQ(f.adapter->stats.factory_calls, factory_calls);
  ASSERT_EQ(f.builder->state, MY_COMPOSE_BUILD_ENDED);
  ASSERT_EQ(f.store->owners[f.button.index].generation, UINT32_MAX - 1u);
  ASSERT_TRUE(f.store->owners[f.button.index].active);
  ASSERT_TRUE(snapshot_matches(&f, &before));
  fixture_destroy(&f);
}

static MyComposeStatus apply_style_transition(fixture_t* f, bool second,
    MyComposeNodeHandle nodes[8]) {
  static const char* const states[] = {"normal", "hover", "pressed", "disabled"};
  MyComposeStatus status = my_compose_tree_builder_begin(f->builder);
  uint32_t node;
  uint32_t state;
  uint32_t index;
  if (status != MY_COMPOSE_OK) return status;
  status = add_node(f->builder, zero_handle(), NULL, "@root", &f->root);
  if (status != MY_COMPOSE_OK) return status;
  status = add_node(f->builder, f->root, "column", "@column", &f->column);
  if (status != MY_COMPOSE_OK) return status;
  for (node = 0u; node < 8u; node++) {
    char key[16];
    snprintf(key, sizeof(key), "b%u", (unsigned)node);
    status = add_node(f->builder, f->column, key, "button", &nodes[node]);
    if (status != MY_COMPOSE_OK) return status;
    for (state = 0u; state < MY_STATE_COUNT; state++) {
      for (index = 0u; index < MY_STYLE_MAX_PROPS; index++) {
        char name[64];
        snprintf(name, sizeof(name), "style:%s:%c%02u", states[state],
            second ? 'b' : 'a', (unsigned)index);
        status = prop(f->builder, nodes[node], name, int_value(second ? 2 : 1));
        if (status != MY_COMPOSE_OK) return status;
      }
    }
  }
  status = my_compose_tree_builder_end(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  status = my_compose_myui_stage(f->adapter,
      my_compose_tree_builder_diff(f->builder));
  if (status != MY_COMPOSE_OK) return status;
  status = my_compose_tree_builder_finalize(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  my_compose_myui_commit(f->adapter);
  return MY_COMPOSE_OK;
}

static MyComposeStatus apply_retained_root_transition(fixture_t* f,
    MyComposeNodeHandle nodes[8], bool omit_root) {
  static const char* const states[] = {"normal", "hover", "pressed", "disabled"};
  MyComposeStatus status = my_compose_tree_builder_begin(f->builder);
  uint32_t node;
  uint32_t state;
  uint32_t index;
  if (status != MY_COMPOSE_OK) return status;
  status = add_node(f->builder, zero_handle(), NULL, "@root", &f->root);
  if (status != MY_COMPOSE_OK) return status;
  if (!omit_root) {
    for (state = 0u; state < MY_STATE_COUNT; state++) {
      for (index = 0u; index < MY_STYLE_MAX_PROPS; index++) {
        char name[64];
        snprintf(name, sizeof(name), "style:%s:r%02u", states[state],
            (unsigned)index);
        status = prop(f->builder, f->root, name, int_value(3));
        if (status != MY_COMPOSE_OK) return status;
      }
    }
  }
  status = add_node(f->builder, f->root, "column", "@column", &f->column);
  if (status != MY_COMPOSE_OK) return status;
  for (node = 0u; node < 8u; node++) {
    char key[16];
    snprintf(key, sizeof(key), "b%u", (unsigned)node);
    status = add_node(f->builder, f->column, key, "button", &nodes[node]);
    if (status != MY_COMPOSE_OK) return status;
    if (node == 7u) continue;
    for (state = 0u; state < MY_STATE_COUNT; state++) {
      for (index = 0u; index < MY_STYLE_MAX_PROPS; index++) {
        char name[64];
        snprintf(name, sizeof(name), "style:%s:b%02u", states[state],
            (unsigned)index);
        status = prop(f->builder, nodes[node], name, int_value(2));
        if (status != MY_COMPOSE_OK) return status;
      }
    }
  }
  status = my_compose_tree_builder_end(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  status = my_compose_myui_stage(f->adapter,
      my_compose_tree_builder_diff(f->builder));
  if (status != MY_COMPOSE_OK) return status;
  status = my_compose_tree_builder_finalize(f->builder);
  if (status != MY_COMPOSE_OK) return status;
  my_compose_myui_commit(f->adapter);
  return MY_COMPOSE_OK;
}

TEST(retained_root_updates_are_captured_once_within_1024_operations) {
  fixture_t f;
  MyComposeNodeHandle nodes[8];
  my_widget_t* root;
  uint32_t captures;
  uint32_t state;
  ASSERT_TRUE(fixture_init_empty(&f));
  ASSERT_EQ(apply_style_transition(&f, false, nodes), MY_COMPOSE_OK);
  root = my_compose_myui_widget(f.adapter, f.root);
  captures = f.adapter->stats.property_captures;
  ASSERT_EQ(apply_retained_root_transition(&f, nodes, false), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_diff(f.builder)->count, 1024u);
  ASSERT_EQ(f.adapter->stats.property_captures - captures, 1024u);
  for (state = 0u; state < MY_STATE_COUNT; state++) {
    const my_value_t* value;
    ASSERT_EQ(root->local_style->counts[state], 16u);
    value = my_style_get(root->local_style, (my_widget_state_t)state, "r00");
    ASSERT_NOT_NULL(value);
    ASSERT_EQ(my_value_get_int32(value), 3);
  }
  ASSERT_EQ(apply_retained_root_transition(&f, nodes, true), MY_COMPOSE_OK);
  for (state = 0u; state < MY_STATE_COUNT; state++) {
    ASSERT_EQ(root->local_style->counts[state], 0u);
  }
  fixture_destroy(&f);
}

TEST(property_journal_accepts_1024_updates) {
  fixture_t f;
  MyComposeNodeHandle nodes[8];
  uint32_t node;
  uint32_t state;
  ASSERT_TRUE(fixture_init_empty(&f));
  ASSERT_EQ(apply_style_transition(&f, false, nodes), MY_COMPOSE_OK);
  ASSERT_EQ(apply_style_transition(&f, true, nodes), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_diff(f.builder)->count, 1024u);
  for (node = 0u; node < 8u; node++) {
    my_widget_t* widget = my_compose_myui_widget(f.adapter, nodes[node]);
    ASSERT_NOT_NULL(widget);
    for (state = 0u; state < MY_STATE_COUNT; state++) {
      const my_value_t* value;
      ASSERT_EQ(widget->local_style->counts[state], 16u);
      value = my_style_get(widget->local_style, (my_widget_state_t)state, "b00");
      ASSERT_NOT_NULL(value);
      ASSERT_EQ(my_value_get_int32(value), 2);
    }
  }
  fixture_destroy(&f);
}

TEST(csd_root_survives_rollback_and_next_stage) {
  fixture_t f;
  view_t view;
  tree_snapshot_t before;
  my_widget_t* content;
  ASSERT_TRUE(fixture_init_empty_ex(&f, true));
  content = my_window_widget(f.win);
  ASSERT_TRUE(f.win->csd);
  ASSERT_TRUE(content != (my_widget_t*)f.win);
  ASSERT_TRUE(content->parent == (my_widget_t*)f.win);
  memset(&view, 0, sizeof(view));
  view.values = 2;
  view.events = true;
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  snapshot_capture(&f, &before);

  view.values = 1;
  f.adapter->fault.property_widget = f.edit_widget;
  f.adapter->fault.property_name = "text";
  f.adapter->fault.fail_after_property_error = true;
  ASSERT_EQ(begin_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_tree_builder_end(f.builder), MY_COMPOSE_OK);
  ASSERT_EQ(my_compose_myui_stage(f.adapter,
      my_compose_tree_builder_diff(f.builder)), MY_COMPOSE_FAILED);
  my_compose_myui_rollback(f.adapter);
  ASSERT_TRUE(snapshot_matches(&f, &before));
  ASSERT_TRUE(content->parent == (my_widget_t*)f.win);
  ASSERT_TRUE(my_window_widget(f.win) == content);

  memset(&f.adapter->fault, 0, sizeof(f.adapter->fault));
  ASSERT_EQ(apply_view(&f, &view), MY_COMPOSE_OK);
  ASSERT_STR_EQ(((my_button_t*)f.button_widget)->text, "first");
  ASSERT_TRUE(content->parent == (my_widget_t*)f.win);
  fixture_destroy(&f);
}

TEST(window_close_closes_bound_store) {
  fixture_t f;
  MyComposeIntent intent;
  ASSERT_TRUE(fixture_init(&f));
  memset(&intent, 0, sizeof(intent));
  intent.type = 1u;
  my_window_notify_closed(f.win);
  ASSERT_TRUE(f.store->closed);
  ASSERT_EQ(my_compose_store_dispatch(f.store, &intent), MY_COMPOSE_CANCELLED);
  fixture_destroy(&f);
}

TEST_MAIN_BEGIN()
  RUN_TEST(initial_create_reorder_and_type_replace_have_one_finalize);
  RUN_TEST(delete_defers_focus_ime_cleanup_and_listener_revoke_until_commit);
  RUN_TEST(listener_forces_owner_and_event_omission_keeps_owner_generation);
  RUN_TEST(omission_and_explicit_none_restore_defaults_and_intrinsic_layout);
  RUN_TEST(property_failure_restores_complete_snapshot_without_setter_rewind);
  RUN_TEST(null_style_rollback_restores_exact_pointer_and_allows_reuse);
  RUN_TEST(factory_insert_and_style_capacity_failures_leave_original_tree);
  RUN_TEST(first_and_second_detach_failures_restore_original_order);
  RUN_TEST(duplicate_key_and_external_reorder_fail_before_factory);
  RUN_TEST(string_property_without_transaction_callbacks_is_not_supported);
  RUN_TEST(listener_history_uses_both_banks_and_rolls_back_only_new_leases);
  RUN_TEST(listener_update_and_type_replace_revoke_old_lease);
  RUN_TEST(delete_revokes_old_listener_lease);
  RUN_TEST(delete_generation_retirement_is_rejected_before_finalize);
  RUN_TEST(retained_root_updates_are_captured_once_within_1024_operations);
  RUN_TEST(property_journal_accepts_1024_updates);
  RUN_TEST(csd_root_survives_rollback_and_next_stage);
  RUN_TEST(window_close_closes_bound_store);
TEST_MAIN_END()
