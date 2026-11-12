/**
 * @file my_widget_class_builtin.c
 * @brief Built-in widget classes: create/property adapters and the static
 * class table expanded from my_widget_class_builtin.inc (M24a).
 *
 * The adapters call the widgets' existing public setters/getters or read
 * public struct fields directly (the same thing the former MVVM property
 * router in my_widget_target.c did).
 */
#include "myc/my_str.h"
#include "myui/my_text_align.h"
#include "myui/my_widget_class.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_checkbox.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_image.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_list_view.h"
#include "myui/widgets/my_progress_bar.h"
#include "myui/widgets/my_scroll_bar.h"
#include "myui/widgets/my_slider.h"
#include "myui/widgets/my_text_area.h"

#include "myui/my_widget_class_builtin.inc"

my_ret_t my_widget_class_register_builtin_entry(const my_widget_class_t* cls);

#define BUILTIN_INSTANCE_create_widget my_widget_is_instance
#define BUILTIN_INSTANCE_create_button my_button_is_instance
#define BUILTIN_INSTANCE_create_label my_label_is_instance
#define BUILTIN_INSTANCE_create_edit my_edit_is_instance
#define BUILTIN_INSTANCE_create_checkbox my_checkbox_is_instance
#define BUILTIN_INSTANCE_create_slider my_slider_is_instance
#define BUILTIN_INSTANCE_create_progress_bar my_progress_bar_is_instance
#define BUILTIN_INSTANCE_create_text_area my_text_area_is_instance
#define BUILTIN_INSTANCE_create_list_view my_list_view_is_instance
#define BUILTIN_INSTANCE_create_image my_image_is_instance
#define BUILTIN_INSTANCE_create_scroll_bar my_scroll_bar_is_instance

/* ---------------- value coercion helpers ---------------- */

static float value_as_float(const my_value_t* v) {
  return v->type == MY_VALUE_DOUBLE ? (float)my_value_get_double(v)
         : v->type == MY_VALUE_FLOAT ? my_value_get_float(v)
         : v->type == MY_VALUE_INT32  ? (float)my_value_get_int32(v)
                                      : 0.0f;
}

static bool value_as_bool(const my_value_t* v) {
  return v->type == MY_VALUE_BOOL ? my_value_get_bool(v) : false;
}

static int32_t value_as_int32(const my_value_t* v) {
  return v->type == MY_VALUE_INT32 ? my_value_get_int32(v) : 0;
}

/* ---------------- create adapters ---------------- */

static my_widget_t* create_widget(const my_allocator_t* a) {
  return my_widget_create(a, "container");
}
static my_widget_t* create_button(const my_allocator_t* a) {
  return my_button_create(a, NULL);
}
static my_widget_t* create_label(const my_allocator_t* a) {
  return my_label_create(a, NULL);
}
static my_widget_t* create_edit(const my_allocator_t* a) {
  return my_edit_create(a);
}
static my_widget_t* create_checkbox(const my_allocator_t* a) {
  return my_checkbox_create(a, NULL);
}
static my_widget_t* create_slider(const my_allocator_t* a) {
  return my_slider_create(a);
}
static my_widget_t* create_progress_bar(const my_allocator_t* a) {
  return my_progress_bar_create(a);
}
static my_widget_t* create_text_area(const my_allocator_t* a) {
  return my_text_area_create(a);
}
static my_widget_t* create_list_view(const my_allocator_t* a) {
  return my_list_view_create(a);
}
static my_widget_t* create_image(const my_allocator_t* a) {
  return my_image_create(a);
}
static my_widget_t* create_scroll_bar(const my_allocator_t* a) {
  return my_scroll_bar_create(a);
}

/* ---------------- button ---------------- */

static my_ret_t button_prop_set_text(my_widget_t* w, const my_value_t* v) {
  return my_button_set_text(w, my_value_get_str(v));
}
static my_ret_t button_prop_get_text(const my_widget_t* w, my_value_t* v) {
  return my_value_set_str(v, ((const my_button_t*)w)->text);
}
static my_ret_t button_prop_set_cooldown(my_widget_t* w, const my_value_t* v) {
  int32_t duration = value_as_int32(v);
  if (duration < 0) {
    return MY_RET_INVALID_PARAMS;
  }
  return my_button_set_cooldown(w, (uint32_t)duration);
}
static my_ret_t button_prop_get_cooldown(const my_widget_t* w, my_value_t* v) {
  return my_value_set_int32(v, (int32_t)((const my_button_t*)w)->cooldown_ms);
}

/* ---------------- label ---------------- */

static my_ret_t label_prop_set_text(my_widget_t* w, const my_value_t* v) {
  return my_label_set_text(w, my_value_get_str(v));
}
static my_ret_t label_prop_get_text(const my_widget_t* w, my_value_t* v) {
  return my_value_set_str(v, ((const my_label_t*)w)->text);
}
static my_ret_t label_prop_set_align(my_widget_t* w, const my_value_t* v) {
  return my_label_set_align(w, my_text_align_parse(my_value_get_str(v)));
}
static my_ret_t label_prop_get_align(const my_widget_t* w, my_value_t* v) {
  return my_value_set_str(v,
                          my_text_align_str(((const my_label_t*)w)->align));
}

/* ---------------- edit ---------------- */

static my_ret_t edit_prop_set_hint(my_widget_t* w, const my_value_t* v) {
  return my_edit_set_hint(w, my_value_get_str(v));
}
static my_ret_t edit_prop_set_password(my_widget_t* w, const my_value_t* v) {
  return my_edit_set_password(w, value_as_bool(v));
}
static my_ret_t edit_prop_set_readonly(my_widget_t* w, const my_value_t* v) {
  return my_edit_set_readonly(w, value_as_bool(v));
}
static my_ret_t edit_prop_set_max_len(my_widget_t* w, const my_value_t* v) {
  return my_edit_set_max_len(w, (size_t)value_as_int32(v));
}
static my_ret_t edit_prop_set_text(my_widget_t* w, const my_value_t* v) {
  return my_edit_set_text(w, my_value_get_str(v));
}
static my_ret_t edit_prop_get_text(const my_widget_t* w, my_value_t* v) {
  return my_value_set_str(v, my_edit_get_text((my_widget_t*)w));
}

/* ---------------- checkbox ("value" aliases "checked" for MVVM) ---------------- */

static my_ret_t checkbox_prop_set_text(my_widget_t* w, const my_value_t* v) {
  return my_checkbox_set_text(w, my_value_get_str(v));
}
static my_ret_t checkbox_prop_get_text(const my_widget_t* w, my_value_t* v) {
  return my_value_set_str(v, ((const my_checkbox_t*)w)->text);
}
static my_ret_t checkbox_prop_set_checked(my_widget_t* w, const my_value_t* v) {
  return my_checkbox_set_checked(w, value_as_bool(v));
}
static my_ret_t checkbox_prop_get_checked(const my_widget_t* w,
                                          my_value_t* v) {
  return my_value_set_bool(v, my_checkbox_get_checked((my_widget_t*)w));
}

/* ---------------- slider ---------------- */

static my_ret_t slider_prop_set_min(my_widget_t* w, const my_value_t* v) {
  return my_slider_set_range(w, value_as_float(v), ((my_slider_t*)w)->max);
}
static my_ret_t slider_prop_get_min(const my_widget_t* w, my_value_t* v) {
  return my_value_set_float(v, ((const my_slider_t*)w)->min);
}
static my_ret_t slider_prop_set_max(my_widget_t* w, const my_value_t* v) {
  return my_slider_set_range(w, ((my_slider_t*)w)->min, value_as_float(v));
}
static my_ret_t slider_prop_get_max(const my_widget_t* w, my_value_t* v) {
  return my_value_set_float(v, ((const my_slider_t*)w)->max);
}
static my_ret_t slider_prop_set_step(my_widget_t* w, const my_value_t* v) {
  return my_slider_set_step(w, value_as_float(v));
}
static my_ret_t slider_prop_set_value(my_widget_t* w, const my_value_t* v) {
  return my_slider_set_value(w, value_as_float(v));
}
static my_ret_t slider_prop_get_value(const my_widget_t* w, my_value_t* v) {
  return my_value_set_double(v, (double)my_slider_get_value((my_widget_t*)w));
}

/* ---------------- progress_bar ---------------- */

static my_ret_t progress_bar_prop_set_value(my_widget_t* w,
                                            const my_value_t* v) {
  return my_progress_bar_set_value(w, value_as_float(v));
}
static my_ret_t progress_bar_prop_get_value(const my_widget_t* w,
                                            my_value_t* v) {
  return my_value_set_double(v,
                             (double)my_progress_bar_get_value((my_widget_t*)w));
}

/* ---------------- text_area ---------------- */

static my_ret_t text_area_prop_set_hint(my_widget_t* w, const my_value_t* v) {
  return my_text_area_set_hint(w, my_value_get_str(v));
}
static my_ret_t text_area_prop_set_readonly(my_widget_t* w,
                                            const my_value_t* v) {
  return my_text_area_set_readonly(w, value_as_bool(v));
}
static my_ret_t text_area_prop_set_wrap(my_widget_t* w, const my_value_t* v) {
  return my_text_area_set_wrap(w, value_as_bool(v));
}
static my_ret_t text_area_prop_get_wrap(const my_widget_t* w, my_value_t* v) {
  return my_value_set_bool(v, ((const my_text_area_t*)w)->wrap);
}
static my_ret_t text_area_prop_set_align(my_widget_t* w, const my_value_t* v) {
  return my_text_area_set_align(w, my_text_align_parse(my_value_get_str(v)));
}
static my_ret_t text_area_prop_get_align(const my_widget_t* w, my_value_t* v) {
  return my_value_set_str(
      v, my_text_align_str(((const my_text_area_t*)w)->align));
}
static my_ret_t text_area_prop_set_max_len(my_widget_t* w,
                                           const my_value_t* v) {
  return my_text_area_set_max_len(w, (size_t)value_as_int32(v));
}
static my_ret_t text_area_prop_set_text(my_widget_t* w, const my_value_t* v) {
  return my_text_area_set_text(w, my_value_get_str(v));
}
static my_ret_t text_area_prop_get_text(const my_widget_t* w, my_value_t* v) {
  return my_value_set_str(v, my_text_area_get_text((my_widget_t*)w));
}

/* ---------------- list_view ---------------- */

static my_ret_t list_view_prop_set_row_height(my_widget_t* w,
                                              const my_value_t* v) {
  return my_list_view_set_row_height(w, value_as_int32(v));
}
static my_ret_t list_view_prop_get_row_height(const my_widget_t* w,
                                              my_value_t* v) {
  return my_value_set_int32(v, ((const my_list_view_t*)w)->row_height);
}

/* ---------------- image ---------------- */

static my_ret_t image_prop_set_src(my_widget_t* w, const my_value_t* v) {
  return my_image_set_image(w, my_value_get_str(v));
}
static my_ret_t image_prop_set_scale(my_widget_t* w, const my_value_t* v) {
  const char* s = my_value_get_str(v);
  my_image_scale_t mode = MY_IMAGE_SCALE_FIT; /* unknown names fall to FIT */
  if (my_str_eq(s, "none")) {
    mode = MY_IMAGE_SCALE_NONE;
  } else if (my_str_eq(s, "center")) {
    mode = MY_IMAGE_SCALE_CENTER;
  } else if (my_str_eq(s, "fill")) {
    mode = MY_IMAGE_SCALE_FILL;
  }
  return my_image_set_scale_mode(w, mode);
}

/* ---------------- transactional property snapshots ---------------- */

static void prop_snapshot_init(my_widget_t* w, my_prop_snapshot_t* snapshot) {
  memset(snapshot, 0, sizeof(*snapshot));
  my_value_init(&snapshot->value, ((my_object_t*)w)->allocator);
}

static my_ret_t button_text_capture(my_widget_t* w,
    my_prop_snapshot_t* snapshot) {
  prop_snapshot_init(w, snapshot);
  return my_value_set_str(&snapshot->value, ((my_button_t*)w)->text);
}

static void button_text_discard(my_widget_t* w, my_prop_snapshot_t* snapshot) {
  (void)w;
  my_value_reset(&snapshot->value);
}

static void button_text_restore(my_widget_t* w, my_prop_snapshot_t* snapshot) {
  my_button_t* button = (my_button_t*)w;
  char* saved = snapshot->value.type == MY_VALUE_STR ? snapshot->value.u.str : NULL;
  snapshot->value.type = button->text != NULL ? MY_VALUE_STR : MY_VALUE_NONE;
  snapshot->value.u.str = button->text;
  button->text = saved;
  my_widget_invalidate(w, NULL);
}

static my_ret_t button_cooldown_capture(my_widget_t* w,
    my_prop_snapshot_t* snapshot) {
  prop_snapshot_init(w, snapshot);
  return my_value_set_uint32(&snapshot->value, ((my_button_t*)w)->cooldown_ms);
}

static void button_cooldown_restore(my_widget_t* w,
    my_prop_snapshot_t* snapshot) {
  ((my_button_t*)w)->cooldown_ms = my_value_get_uint32(&snapshot->value);
}

#define EDIT_SNAPSHOT_FIELDS(X) \
  X(char*, text)                \
  X(char*, masked)              \
  X(char*, hint)                \
  X(char*, ime_preedit)
#define EDIT_FIELD_DECL(type, name) type name;

static void edit_prop_discard(my_widget_t* w, my_prop_snapshot_t* snapshot);

typedef struct edit_prop_snapshot_t {
  EDIT_SNAPSHOT_FIELDS(EDIT_FIELD_DECL)
  size_t cursor;
  size_t anchor;
  int32_t scroll_x;
  size_t max_len;
  int32_t ime_caret;
  bool readonly;
  bool password;
} edit_prop_snapshot_t;

static my_ret_t edit_snapshot_string(my_edit_t* edit, const char* source,
    char** out) {
  *out = my_strdup(edit->allocator, source);
  return source != NULL && *out == NULL ? MY_RET_OOM : MY_RET_OK;
}

static my_ret_t edit_prop_capture(my_widget_t* w,
    my_prop_snapshot_t* snapshot) {
  my_edit_t* edit = (my_edit_t*)w;
  edit_prop_snapshot_t* saved;
  prop_snapshot_init(w, snapshot);
  saved = (edit_prop_snapshot_t*)my_mem_calloc(edit->allocator, 1u,
      sizeof(*saved));
  if (saved == NULL) return MY_RET_OOM;
  snapshot->state = saved;
#define EDIT_CAPTURE_STRING(type, name)                                      \
  if (edit_snapshot_string(edit, edit->name, &saved->name) != MY_RET_OK) {   \
    edit_prop_discard(w, snapshot);                                          \
    return MY_RET_OOM;                                                       \
  }
  EDIT_SNAPSHOT_FIELDS(EDIT_CAPTURE_STRING)
#undef EDIT_CAPTURE_STRING
  saved->cursor = edit->cursor;
  saved->anchor = edit->anchor;
  saved->scroll_x = edit->scroll_x;
  saved->max_len = edit->max_len;
  saved->ime_caret = edit->ime_caret;
  saved->readonly = edit->readonly;
  saved->password = edit->password;
  return MY_RET_OK;
}

static void edit_prop_discard(my_widget_t* w, my_prop_snapshot_t* snapshot) {
  my_edit_t* edit = (my_edit_t*)w;
  edit_prop_snapshot_t* saved = (edit_prop_snapshot_t*)snapshot->state;
  if (saved != NULL) {
#define EDIT_FREE_STRING(type, name) my_mem_free(edit->allocator, saved->name);
    EDIT_SNAPSHOT_FIELDS(EDIT_FREE_STRING)
#undef EDIT_FREE_STRING
    my_mem_free(edit->allocator, saved);
    snapshot->state = NULL;
  }
  my_value_reset(&snapshot->value);
}

static void edit_prop_restore(my_widget_t* w, my_prop_snapshot_t* snapshot) {
  my_edit_t* edit = (my_edit_t*)w;
  edit_prop_snapshot_t* saved = (edit_prop_snapshot_t*)snapshot->state;
#define EDIT_SWAP_STRING(type, name) \
  do {                               \
    type temporary = saved->name;    \
    saved->name = edit->name;        \
    edit->name = temporary;          \
  } while (0);
  EDIT_SNAPSHOT_FIELDS(EDIT_SWAP_STRING)
#undef EDIT_SWAP_STRING
  edit->cursor = saved->cursor;
  edit->anchor = saved->anchor;
  edit->scroll_x = saved->scroll_x;
  edit->max_len = saved->max_len;
  edit->ime_caret = saved->ime_caret;
  edit->readonly = saved->readonly;
  edit->password = saved->password;
  my_widget_invalidate(w, NULL);
}

static my_ret_t edit_prop_get_hint(const my_widget_t* w, my_value_t* v) {
  return my_value_set_str(v, ((const my_edit_t*)w)->hint);
}
static my_ret_t edit_prop_get_password(const my_widget_t* w, my_value_t* v) {
  return my_value_set_bool(v, ((const my_edit_t*)w)->password);
}
static my_ret_t edit_prop_get_readonly(const my_widget_t* w, my_value_t* v) {
  return my_value_set_bool(v, ((const my_edit_t*)w)->readonly);
}
static my_ret_t edit_prop_get_max_len(const my_widget_t* w, my_value_t* v) {
  size_t value = ((const my_edit_t*)w)->max_len;
  return my_value_set_int32(v, value > INT32_MAX ? INT32_MAX : (int32_t)value);
}

/* ---------------- table expansion ---------------- */

#define TXN_CAPTURE_button_prop_set_text button_text_capture
#define TXN_DISCARD_button_prop_set_text button_text_discard
#define TXN_RESTORE_button_prop_set_text button_text_restore
#define TXN_CAPTURE_button_prop_set_cooldown button_cooldown_capture
#define TXN_DISCARD_button_prop_set_cooldown button_text_discard
#define TXN_RESTORE_button_prop_set_cooldown button_cooldown_restore
#define TXN_CAPTURE_edit_prop_set_hint edit_prop_capture
#define TXN_DISCARD_edit_prop_set_hint edit_prop_discard
#define TXN_RESTORE_edit_prop_set_hint edit_prop_restore
#define TXN_CAPTURE_edit_prop_set_password edit_prop_capture
#define TXN_DISCARD_edit_prop_set_password edit_prop_discard
#define TXN_RESTORE_edit_prop_set_password edit_prop_restore
#define TXN_CAPTURE_edit_prop_set_readonly edit_prop_capture
#define TXN_DISCARD_edit_prop_set_readonly edit_prop_discard
#define TXN_RESTORE_edit_prop_set_readonly edit_prop_restore
#define TXN_CAPTURE_edit_prop_set_max_len edit_prop_capture
#define TXN_DISCARD_edit_prop_set_max_len edit_prop_discard
#define TXN_RESTORE_edit_prop_set_max_len edit_prop_restore
#define TXN_CAPTURE_edit_prop_set_text edit_prop_capture
#define TXN_DISCARD_edit_prop_set_text edit_prop_discard
#define TXN_RESTORE_edit_prop_set_text edit_prop_restore
#define TXN_CAPTURE_label_prop_set_text NULL
#define TXN_DISCARD_label_prop_set_text NULL
#define TXN_RESTORE_label_prop_set_text NULL
#define TXN_CAPTURE_label_prop_set_align NULL
#define TXN_DISCARD_label_prop_set_align NULL
#define TXN_RESTORE_label_prop_set_align NULL
#define TXN_CAPTURE_checkbox_prop_set_text NULL
#define TXN_DISCARD_checkbox_prop_set_text NULL
#define TXN_RESTORE_checkbox_prop_set_text NULL
#define TXN_CAPTURE_checkbox_prop_set_checked NULL
#define TXN_DISCARD_checkbox_prop_set_checked NULL
#define TXN_RESTORE_checkbox_prop_set_checked NULL
#define TXN_CAPTURE_slider_prop_set_min NULL
#define TXN_DISCARD_slider_prop_set_min NULL
#define TXN_RESTORE_slider_prop_set_min NULL
#define TXN_CAPTURE_slider_prop_set_max NULL
#define TXN_DISCARD_slider_prop_set_max NULL
#define TXN_RESTORE_slider_prop_set_max NULL
#define TXN_CAPTURE_slider_prop_set_step NULL
#define TXN_DISCARD_slider_prop_set_step NULL
#define TXN_RESTORE_slider_prop_set_step NULL
#define TXN_CAPTURE_slider_prop_set_value NULL
#define TXN_DISCARD_slider_prop_set_value NULL
#define TXN_RESTORE_slider_prop_set_value NULL
#define TXN_CAPTURE_progress_bar_prop_set_value NULL
#define TXN_DISCARD_progress_bar_prop_set_value NULL
#define TXN_RESTORE_progress_bar_prop_set_value NULL
#define TXN_CAPTURE_text_area_prop_set_hint NULL
#define TXN_DISCARD_text_area_prop_set_hint NULL
#define TXN_RESTORE_text_area_prop_set_hint NULL
#define TXN_CAPTURE_text_area_prop_set_readonly NULL
#define TXN_DISCARD_text_area_prop_set_readonly NULL
#define TXN_RESTORE_text_area_prop_set_readonly NULL
#define TXN_CAPTURE_text_area_prop_set_wrap NULL
#define TXN_DISCARD_text_area_prop_set_wrap NULL
#define TXN_RESTORE_text_area_prop_set_wrap NULL
#define TXN_CAPTURE_text_area_prop_set_align NULL
#define TXN_DISCARD_text_area_prop_set_align NULL
#define TXN_RESTORE_text_area_prop_set_align NULL
#define TXN_CAPTURE_text_area_prop_set_max_len NULL
#define TXN_DISCARD_text_area_prop_set_max_len NULL
#define TXN_RESTORE_text_area_prop_set_max_len NULL
#define TXN_CAPTURE_text_area_prop_set_text NULL
#define TXN_DISCARD_text_area_prop_set_text NULL
#define TXN_RESTORE_text_area_prop_set_text NULL
#define TXN_CAPTURE_list_view_prop_set_row_height NULL
#define TXN_DISCARD_list_view_prop_set_row_height NULL
#define TXN_RESTORE_list_view_prop_set_row_height NULL
#define TXN_CAPTURE_image_prop_set_src NULL
#define TXN_DISCARD_image_prop_set_src NULL
#define TXN_RESTORE_image_prop_set_src NULL
#define TXN_CAPTURE_image_prop_set_scale NULL
#define TXN_DISCARD_image_prop_set_scale NULL
#define TXN_RESTORE_image_prop_set_scale NULL
#define TXN_CAPTURE(set_fn) TXN_CAPTURE_##set_fn
#define TXN_DISCARD(set_fn) TXN_DISCARD_##set_fn
#define TXN_RESTORE(set_fn) TXN_RESTORE_##set_fn

#define EMIT_PROP_ROW(name, type, set_fn, get_fn)                         \
  {name, type, set_fn, get_fn, TXN_CAPTURE(set_fn), TXN_DISCARD(set_fn), \
      TXN_RESTORE(set_fn)},
#define EMIT_EVENT_ROW(ev) ev,
#define EMIT_CLASS_TABLES(tag, create_fn, create_str, PROPS, EVENTS)       \
  static const my_prop_desc_t props_of_##create_fn[] = {                   \
      PROPS(EMIT_PROP_ROW){NULL, MY_PROP_STRING, NULL, NULL, NULL, NULL,   \
                           NULL}};                                         \
  static const char* const events_of_##create_fn[] = {                     \
      EVENTS(EMIT_EVENT_ROW) NULL};

MYUI_BUILTIN_CLASSES(EMIT_CLASS_TABLES)

#define EMIT_CLASS_ROW(tag, create_fn, create_str, PROPS, EVENTS) \
  {tag, create_fn, props_of_##create_fn, events_of_##create_fn, \
   BUILTIN_INSTANCE_##create_fn},

static const my_widget_class_t BUILTIN_CLASSES[] = {
    MYUI_BUILTIN_CLASSES(EMIT_CLASS_ROW)};

my_ret_t my_widget_class_register_builtins(void) {
  size_t i;
  for (i = 0; i < sizeof(BUILTIN_CLASSES) / sizeof(BUILTIN_CLASSES[0]); i++) {
    my_ret_t ret = my_widget_class_register_builtin_entry(&BUILTIN_CLASSES[i]);
    if (ret != MY_RET_OK) return ret;
  }
  return MY_RET_OK;
}
