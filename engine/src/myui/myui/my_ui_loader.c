/**
 * @file my_ui_loader.c
 * @brief YAML UI loader.
 */
#include "myui/my_ui_loader.h"

#ifdef MYUI_UI_YAML

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_str.h"
#include "myui/my_css.h"
#include "myui/my_layout.h"
#include "myui/my_widget_class.h"

#define MY_UI_MAX_FACTORIES 32
#define MY_UI_MAX_BIND_RULE_BYTES 512

typedef struct ui_factory_entry_t {
  char type[24];
  my_ui_factory_fn_t factory;
} ui_factory_entry_t;

static ui_factory_entry_t g_factories[MY_UI_MAX_FACTORIES];
static size_t g_factory_count;

static void ui_fail(my_ui_error_t* err, const char* message) {
  if (err != NULL && err->message[0] == '\0') {
    snprintf(err->message, sizeof(err->message), "%s", message);
  }
}

my_ret_t my_ui_loader_register(const char* type, my_ui_factory_fn_t factory) {
  size_t i;
  if (type == NULL || factory == NULL || strlen(type) >= sizeof(g_factories[0].type)) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_factory_count; i++) {
    if (my_str_eq(g_factories[i].type, type)) {
      g_factories[i].factory = factory;
      return MY_RET_OK;
    }
  }
  if (g_factory_count >= MY_UI_MAX_FACTORIES) {
    return MY_RET_OOM;
  }
  snprintf(g_factories[g_factory_count].type, sizeof(g_factories[0].type), "%s", type);
  g_factories[g_factory_count].factory = factory;
  g_factory_count++;
  return MY_RET_OK;
}

static my_ui_factory_fn_t find_factory(const char* type) {
  size_t i;
  for (i = 0; i < g_factory_count; i++) {
    if (my_str_eq(g_factories[i].type, type)) {
      return g_factories[i].factory;
    }
  }
  return NULL;
}

static const my_conf_node_t* object_value(const my_conf_node_t* object,
                                          const char* key) {
  size_t i;
  if (my_conf_type(object) != MY_CONF_OBJECT) {
    return NULL;
  }
  for (i = 0; i < my_conf_child_count(object); i++) {
    my_conf_node_t* child = my_conf_child(object, i);
    if (my_str_eq(my_conf_key(child), key)) {
      return child;
    }
  }
  return NULL;
}

static bool value_int32(const my_conf_node_t* node, int32_t fallback,
                        int32_t* out) {
  int64_t value;
  if (node == NULL) {
    *out = fallback;
    return true;
  }
  if (my_conf_type(node) != MY_CONF_INT64) {
    return false;
  }
  value = my_conf_as_int64(node, 0);
  if (value < INT32_MIN || value > INT32_MAX) {
    return false;
  }
  *out = (int32_t)value;
  return true;
}

static bool value_bool(const my_conf_node_t* node, bool fallback, bool* out) {
  if (node == NULL) {
    *out = fallback;
    return true;
  }
  if (my_conf_type(node) != MY_CONF_BOOL) {
    return false;
  }
  *out = my_conf_as_bool(node, fallback);
  return true;
}

static my_ret_t set_typed_property(my_widget_t* widget,
                                   const my_prop_desc_t* prop,
                                   const my_conf_node_t* node) {
  my_value_t value;
  my_ret_t ret = MY_RET_FAIL;
  my_value_init(&value, ((my_object_t*)widget)->allocator);
  if (prop->type == MY_PROP_STRING && my_conf_type(node) == MY_CONF_STR) {
    ret = my_value_set_str(&value, my_conf_as_str(node, NULL));
  } else if (prop->type == MY_PROP_INT && my_conf_type(node) == MY_CONF_INT64) {
    int64_t number = my_conf_as_int64(node, 0);
    ret = number >= INT32_MIN && number <= INT32_MAX
              ? my_value_set_int32(&value, (int32_t)number)
              : MY_RET_FAIL;
  } else if (prop->type == MY_PROP_FLOAT &&
             (my_conf_type(node) == MY_CONF_INT64 ||
              my_conf_type(node) == MY_CONF_DOUBLE)) {
    double number = my_conf_type(node) == MY_CONF_INT64
                        ? (double)my_conf_as_int64(node, 0)
                        : my_conf_as_double(node, 0.0);
    ret = isfinite(number) && number >= -FLT_MAX && number <= FLT_MAX
              ? my_value_set_float(&value, (float)number)
              : MY_RET_FAIL;
  } else if (prop->type == MY_PROP_BOOL && my_conf_type(node) == MY_CONF_BOOL) {
    ret = my_value_set_bool(&value, my_conf_as_bool(node, false));
  }
  if (ret == MY_RET_OK) {
    ret = prop->set(widget, &value);
  }
  my_value_reset(&value);
  return ret;
}

static my_ret_t apply_class_props(my_widget_t* widget,
                                  const my_widget_class_t* cls,
                                  const my_conf_node_t* node,
                                  my_ui_error_t* err) {
  const my_prop_desc_t* prop;
  if (cls->props == NULL) {
    return MY_RET_OK;
  }
  for (prop = cls->props; prop->name != NULL; prop++) {
    const my_conf_node_t* value = object_value(node, prop->name);
    if (value != NULL && prop->set != NULL &&
        set_typed_property(widget, prop, value) != MY_RET_OK) {
      ui_fail(err, "invalid typed widget property");
      return MY_RET_FAIL;
    }
  }
  return MY_RET_OK;
}

static my_ret_t apply_bindings(my_widget_t* widget, const my_conf_node_t* node,
                               my_ui_error_t* err) {
  const my_conf_node_t* bindings = object_value(node, "bindings");
  char rules[MY_UI_MAX_BIND_RULE_BYTES];
  size_t used = 0;
  size_t i;
  if (bindings == NULL) {
    return MY_RET_OK;
  }
  if (my_conf_type(bindings) != MY_CONF_OBJECT) {
    ui_fail(err, "bindings must be a map");
    return MY_RET_FAIL;
  }
  for (i = 0; i < my_conf_child_count(bindings); i++) {
    my_conf_node_t* value = my_conf_child(bindings, i);
    const char* key = my_conf_key(value);
    const char* text;
    int wrote;
    if (key == NULL || my_conf_type(value) != MY_CONF_STR) {
      ui_fail(err, "binding values must be strings");
      return MY_RET_FAIL;
    }
    text = my_conf_as_str(value, NULL);
    wrote = snprintf(rules + used, sizeof(rules) - used, "v:%s=%s;", key, text);
    if (wrote < 0 || (size_t)wrote >= sizeof(rules) - used) {
      ui_fail(err, "bind rules too long");
      return MY_RET_FAIL;
    }
    used += (size_t)wrote;
  }
  return used == 0 ? MY_RET_OK : my_widget_set_bind_rules(widget, rules);
}

static my_ret_t apply_common(my_widget_t* widget, const my_conf_node_t* node,
                             my_ui_error_t* err) {
  const my_conf_node_t* value;
  const char* text;
  int32_t x, y, w, h;
  bool visible, enable;
  if (my_conf_type(node) != MY_CONF_OBJECT ||
      !value_int32(object_value(node, "x"), 0, &x) ||
      !value_int32(object_value(node, "y"), 0, &y) ||
      !value_int32(object_value(node, "w"), 0, &w) ||
      !value_int32(object_value(node, "h"), 0, &h) ||
      !value_bool(object_value(node, "visible"), true, &visible) ||
      !value_bool(object_value(node, "enable"), true, &enable)) {
    ui_fail(err, "invalid common widget property");
    return MY_RET_FAIL;
  }
  value = object_value(node, "name");
  if (value != NULL) {
    if (my_conf_type(value) != MY_CONF_STR) {
      ui_fail(err, "name must be a string");
      return MY_RET_FAIL;
    }
    my_widget_set_name(widget, my_conf_as_str(value, NULL));
  }
  my_widget_set_rect(widget, &(my_rect_t){x, y, w, h});
  my_widget_set_visible(widget, visible);
  widget->enable = enable;
  value = object_value(node, "tooltip");
  if (value != NULL) {
    if (my_conf_type(value) != MY_CONF_STR) {
      ui_fail(err, "tooltip must be a string");
      return MY_RET_FAIL;
    }
    my_widget_set_tooltip(widget, my_conf_as_str(value, NULL));
  }
  value = object_value(node, "class");
  if (value != NULL) {
    if (my_conf_type(value) != MY_CONF_STR) {
      ui_fail(err, "class must be a string");
      return MY_RET_FAIL;
    }
    my_widget_set_style_class(widget, my_conf_as_str(value, NULL));
  }
  value = object_value(node, "lp");
  if (value != NULL && (my_conf_type(value) != MY_CONF_STR ||
                        my_widget_set_layout_params(widget,
                            my_conf_as_str(value, NULL)) != MY_RET_OK)) {
    ui_fail(err, "invalid lp");
    return MY_RET_FAIL;
  }
  value = object_value(node, "layout");
  if (value != NULL) {
    if (my_conf_type(value) != MY_CONF_STR) {
      ui_fail(err, "layout must be a string");
      return MY_RET_FAIL;
    }
    text = my_conf_as_str(value, NULL);
    if (strncmp(text, "linear:", 7) == 0) {
      bool horizontal = text[7] == 'h';
      int32_t spacing = 0;
      const char* colon = strchr(text + 7, ':');
      if (colon != NULL) {
        spacing = (int32_t)strtol(colon + 1, NULL, 10);
      }
      my_widget_set_layouter(widget,
                             my_layouter_linear_create(NULL, horizontal, spacing));
    }
  }
  return apply_bindings(widget, node, err);
}

static my_widget_t* build_node(const my_allocator_t* allocator, my_pal_t* pal,
                               const my_conf_node_t* node, my_ui_error_t* err);

static my_widget_t* build_children(const my_allocator_t* allocator, my_pal_t* pal,
                                   my_widget_t* parent, const my_conf_node_t* node,
                                   my_ui_error_t* err) {
  const my_conf_node_t* children = object_value(node, "children");
  size_t i;
  if (children == NULL) {
    return parent;
  }
  if (my_conf_type(children) != MY_CONF_ARRAY) {
    ui_fail(err, "children must be a sequence");
    return NULL;
  }
  for (i = 0; i < my_conf_child_count(children); i++) {
    my_widget_t* child = build_node(allocator, pal, my_conf_child(children, i), err);
    if (child == NULL) {
      return NULL;
    }
    if (my_widget_add_child(parent, child) != MY_RET_OK) {
      my_widget_unref(child);
      ui_fail(err, "failed to attach child widget");
      return NULL;
    }
    my_widget_unref(child);
  }
  return parent;
}

static my_widget_t* build_node(const my_allocator_t* allocator, my_pal_t* pal,
                               const my_conf_node_t* node, my_ui_error_t* err) {
  const my_conf_node_t* type_node;
  const char* type;
  const my_widget_class_t* cls;
  my_ui_factory_fn_t factory;
  my_widget_t* widget;
  (void)pal;
  if (my_conf_type(node) != MY_CONF_OBJECT ||
      (type_node = object_value(node, "type")) == NULL ||
      my_conf_type(type_node) != MY_CONF_STR) {
    ui_fail(err, "widget requires a string type");
    return NULL;
  }
  type = my_conf_as_str(type_node, NULL);
  if (my_str_eq(type, "window")) {
    ui_fail(err, "window is only allowed as root");
    return NULL;
  }
  factory = find_factory(type);
  cls = factory == NULL ? my_widget_class_find(type) : NULL;
  if (factory != NULL) {
    widget = factory(allocator, node);
  } else if (cls != NULL) {
    widget = cls->create(allocator);
  } else {
    ui_fail(err, "unknown widget type");
    return NULL;
  }
  if (widget == NULL || (cls != NULL && apply_class_props(widget, cls, node, err) != MY_RET_OK) ||
      apply_common(widget, node, err) != MY_RET_OK ||
      build_children(allocator, pal, widget, node, err) == NULL) {
    my_widget_unref(widget);
    return NULL;
  }
  return widget;
}

static void apply_style(my_window_t* window, const my_conf_node_t* root) {
  const my_conf_node_t* style = object_value(root, "style");
  const char* text;
  if (style == NULL || my_conf_type(style) != MY_CONF_STR || window->theme == NULL) {
    return;
  }
  text = my_conf_as_str(style, NULL);
  if (strchr(text, '{') != NULL) {
    my_theme_load_css(window->theme, text);
  } else {
    my_theme_load_str(window->theme, text);
  }
}

my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* yaml_str, my_ui_error_t* err) {
  my_conf_error_t yaml_error;
  my_conf_node_t* root;
  const my_conf_node_t* type_node;
  my_widget_t* result;
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  if (yaml_str == NULL || strlen(yaml_str) > MY_UI_MAX_YAML_BYTES) {
    ui_fail(err, "YAML input exceeds resource budget");
    return NULL;
  }
  root = my_conf_parse_yaml(allocator, yaml_str, strlen(yaml_str), &yaml_error);
  if (root == NULL) {
    if (err != NULL) {
      err->line = yaml_error.line;
      snprintf(err->message, sizeof(err->message), "yaml: %.70s (col %d)",
               yaml_error.msg, yaml_error.col);
    }
    return NULL;
  }
  type_node = object_value(root, "type");
  if (type_node != NULL && my_conf_type(type_node) == MY_CONF_STR &&
      my_str_eq(my_conf_as_str(type_node, NULL), "window")) {
    int32_t width, height;
    const my_conf_node_t* title = object_value(root, "title");
    my_window_t* window;
    if (pal == NULL || !value_int32(object_value(root, "w"), 640, &width) ||
        !value_int32(object_value(root, "h"), 480, &height) ||
        (title != NULL && my_conf_type(title) != MY_CONF_STR)) {
      ui_fail(err, "window requires pal, integer size, and string title");
      my_conf_destroy(root);
      return NULL;
    }
    window = my_window_create(allocator, pal, width, height,
                              title != NULL ? my_conf_as_str(title, NULL) : NULL);
    result = (my_widget_t*)window;
    if (window != NULL && (apply_common(result, root, err) != MY_RET_OK ||
                           build_children(allocator, pal, result, root, err) == NULL)) {
      my_widget_unref(result);
      result = NULL;
    } else if (window != NULL) {
      apply_style(window, root);
    }
  } else {
    result = build_node(allocator, pal, root, err);
  }
  my_conf_destroy(root);
  return result;
}

my_widget_t* my_ui_load_file(const my_allocator_t* allocator, my_pal_t* pal,
                             const char* path, my_ui_error_t* err) {
  FILE* file;
  long size;
  char* buffer;
  my_widget_t* result;
  if (path == NULL || (file = fopen(path, "rb")) == NULL ||
      fseek(file, 0, SEEK_END) != 0 || (size = ftell(file)) < 0 ||
      fseek(file, 0, SEEK_SET) != 0) {
    if (file != NULL) {
      fclose(file);
    }
    return NULL;
  }
  buffer = (char*)my_mem_alloc(allocator, (size_t)size + 1u);
  if (buffer == NULL || fread(buffer, 1, (size_t)size, file) != (size_t)size) {
    fclose(file);
    my_mem_free(allocator, buffer);
    return NULL;
  }
  fclose(file);
  buffer[size] = '\0';
  result = my_ui_load_str(allocator, pal, buffer, err);
  my_mem_free(allocator, buffer);
  return result;
}

#else

my_ret_t my_ui_loader_register(const char* type, my_ui_factory_fn_t factory) {
  (void)type;
  (void)factory;
  return MY_RET_NOT_SUPPORTED;
}

my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* yaml_str, my_ui_error_t* err) {
  (void)allocator;
  (void)pal;
  (void)yaml_str;
  (void)err;
  return NULL;
}

my_widget_t* my_ui_load_file(const my_allocator_t* allocator, my_pal_t* pal,
                             const char* path, my_ui_error_t* err) {
  (void)allocator;
  (void)pal;
  (void)path;
  (void)err;
  return NULL;
}

#endif
