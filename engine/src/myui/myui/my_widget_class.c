/**
 * @file my_widget_class.c
 * @brief Widget class registry: lookup + generic property access (M24a).
 *
 * XML-independent on purpose: this file must stay usable in
 * MYUI_UI_XML=OFF builds (ui2c-generated code relies on it).
 */
#include "myui/my_widget_class.h"

#include <string.h>

#include "myc/my_str.h"

#define MY_WIDGET_CLASS_MAX 64

static const my_widget_class_t* g_classes[MY_WIDGET_CLASS_MAX];
static size_t g_class_count = 0;
static bool g_builtins_done = false;

/* defined in my_widget_class_builtin.c */
void my_widget_class_register_builtins(void);

my_ret_t my_widget_class_register(const my_widget_class_t* cls) {
  size_t i;
  if (cls == NULL || cls->type == NULL || cls->create == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_class_count; i++) {
    if (my_str_eq(g_classes[i]->type, cls->type)) {
      g_classes[i] = cls; /* same type name: override */
      return MY_RET_OK;
    }
  }
  if (g_class_count >= MY_WIDGET_CLASS_MAX) {
    return MY_RET_OOM;
  }
  g_classes[g_class_count] = cls;
  g_class_count++;
  return MY_RET_OK;
}

const my_widget_class_t* my_widget_class_find(const char* type) {
  size_t i;
  if (type == NULL) {
    return NULL;
  }
  if (!g_builtins_done) {
    g_builtins_done = true;
    my_widget_class_register_builtins();
  }
  for (i = 0; i < g_class_count; i++) {
    if (my_str_eq(g_classes[i]->type, type)) {
      return g_classes[i];
    }
  }
  return NULL;
}

static const my_prop_desc_t* find_prop(const my_widget_class_t* cls,
                                       const char* name) {
  const my_prop_desc_t* p;
  if (cls == NULL || cls->props == NULL) {
    return NULL;
  }
  for (p = cls->props; p->name != NULL; p++) {
    if (my_str_eq(p->name, name)) {
      return p;
    }
  }
  return NULL;
}

my_ret_t my_widget_set_prop(my_widget_t* w, const char* name,
                            const my_value_t* v) {
  const my_prop_desc_t* p;
  if (w == NULL || name == NULL || v == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  /* base-class common properties (no class table involved) */
  if (strcmp(name, "visible") == 0) {
    return my_widget_set_visible(w, v->type == MY_VALUE_BOOL
                                        ? my_value_get_bool(v)
                                        : true);
  }
  if (strcmp(name, "enable") == 0) {
    if (v->type == MY_VALUE_BOOL) {
      w->enable = my_value_get_bool(v);
      my_widget_invalidate(w, NULL);
    }
    return MY_RET_OK;
  }
  if (strlen(name) == 1 && strchr("xywh", name[0]) != NULL) {
    my_rect_t r;
    int32_t n;
    if (v->type != MY_VALUE_INT32) {
      return MY_RET_NOT_SUPPORTED;
    }
    r = w->rect;
    n = my_value_get_int32(v);
    if (name[0] == 'x') {
      r.x = n;
    } else if (name[0] == 'y') {
      r.y = n;
    } else if (name[0] == 'w') {
      r.w = n;
    } else {
      r.h = n;
    }
    return my_widget_set_rect(w, &r);
  }
  p = find_prop(my_widget_class_find(w->widget_type), name);
  if (p == NULL || p->set == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return p->set(w, v);
}

my_ret_t my_widget_get_prop(my_widget_t* w, const char* name, my_value_t* v) {
  const my_prop_desc_t* p;
  if (w == NULL || name == NULL || v == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (strcmp(name, "visible") == 0) {
    return my_value_set_bool(v, w->visible);
  }
  if (strcmp(name, "enable") == 0) {
    return my_value_set_bool(v, w->enable);
  }
  if (strlen(name) == 1 && strchr("xywh", name[0]) != NULL) {
    int32_t n = name[0] == 'x'   ? w->rect.x
                : name[0] == 'y' ? w->rect.y
                : name[0] == 'w' ? w->rect.w
                                 : w->rect.h;
    return my_value_set_int32(v, n);
  }
  p = find_prop(my_widget_class_find(w->widget_type), name);
  if (p == NULL || p->get == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return p->get(w, v);
}

/* ---------------- typed convenience wrappers ---------------- */

my_ret_t my_widget_set_prop_str(my_widget_t* w, const char* name,
                                const char* v) {
  my_value_t val;
  my_ret_t r;
  my_value_init(&val, NULL);
  my_value_set_str(&val, v);
  r = my_widget_set_prop(w, name, &val);
  my_value_reset(&val);
  return r;
}

my_ret_t my_widget_set_prop_int(my_widget_t* w, const char* name, int32_t v) {
  my_value_t val;
  my_ret_t r;
  my_value_init(&val, NULL);
  my_value_set_int32(&val, v);
  r = my_widget_set_prop(w, name, &val);
  my_value_reset(&val);
  return r;
}

my_ret_t my_widget_set_prop_float(my_widget_t* w, const char* name, float v) {
  my_value_t val;
  my_ret_t r;
  my_value_init(&val, NULL);
  my_value_set_float(&val, v);
  r = my_widget_set_prop(w, name, &val);
  my_value_reset(&val);
  return r;
}

my_ret_t my_widget_set_prop_bool(my_widget_t* w, const char* name, bool v) {
  my_value_t val;
  my_ret_t r;
  my_value_init(&val, NULL);
  my_value_set_bool(&val, v);
  r = my_widget_set_prop(w, name, &val);
  my_value_reset(&val);
  return r;
}
