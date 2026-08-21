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

/* ---------------- table expansion ---------------- */

#define EMIT_PROP_ROW(name, type, set_fn, get_fn) {name, type, set_fn, get_fn},
#define EMIT_EVENT_ROW(ev) ev,
#define EMIT_CLASS_TABLES(tag, create_fn, create_str, PROPS, EVENTS)    \
  static const my_prop_desc_t props_of_##create_fn[] = {                \
      PROPS(EMIT_PROP_ROW){NULL, MY_PROP_STRING, NULL, NULL}};          \
  static const char* const events_of_##create_fn[] = {                  \
      EVENTS(EMIT_EVENT_ROW) NULL};

MYUI_BUILTIN_CLASSES(EMIT_CLASS_TABLES)

#define EMIT_CLASS_ROW(tag, create_fn, create_str, PROPS, EVENTS) \
  {tag, create_fn, props_of_##create_fn, events_of_##create_fn},

static const my_widget_class_t BUILTIN_CLASSES[] = {
    MYUI_BUILTIN_CLASSES(EMIT_CLASS_ROW)};

void my_widget_class_register_builtins(void) {
  size_t i;
  for (i = 0; i < sizeof(BUILTIN_CLASSES) / sizeof(BUILTIN_CLASSES[0]); i++) {
    my_widget_class_register(&BUILTIN_CLASSES[i]);
  }
}
