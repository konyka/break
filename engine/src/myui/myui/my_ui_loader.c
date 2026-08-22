/**
 * @file my_ui_loader.c
 * @brief XML UI loader.
 */
#include "myui/my_ui_loader.h"

#ifdef MYUI_UI_XML

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_str.h"
#include "myui/my_css.h"
#include "myui/my_layout.h"
#include "myui/my_widget_class.h"

/* ---------------- factory registry ---------------- */

#define MY_UI_MAX_FACTORIES 32

typedef struct ui_factory_entry_t {
  char tag[24];
  my_ui_factory_fn_t factory;
} ui_factory_entry_t;

static ui_factory_entry_t g_factories[MY_UI_MAX_FACTORIES];
static size_t g_factory_count = 0;

my_ret_t my_ui_loader_register(const char* tag, my_ui_factory_fn_t factory) {
  size_t i;
  if (tag == NULL || factory == NULL || strlen(tag) >= 24) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_factory_count; i++) {
    if (my_str_eq(g_factories[i].tag, tag)) {
      g_factories[i].factory = factory;
      return MY_RET_OK;
    }
  }
  if (g_factory_count >= MY_UI_MAX_FACTORIES) {
    return MY_RET_OOM;
  }
  strncpy(g_factories[g_factory_count].tag, tag, 23);
  g_factories[g_factory_count].factory = factory;
  g_factory_count++;
  return MY_RET_OK;
}

static my_ui_factory_fn_t find_factory(const char* tag) {
  size_t i;
  for (i = 0; i < g_factory_count; i++) {
    if (my_str_eq(g_factories[i].tag, tag)) {
      return g_factories[i].factory;
    }
  }
  return NULL;
}

/* ---------------- attribute helpers ---------------- */

static int32_t attr_int(const my_xml_node_t* node, const char* name,
                        int32_t fallback) {
  const char* s = my_xml_node_attr(node, name);
  return s != NULL ? (int32_t)strtol(s, NULL, 10) : fallback;
}

static bool attr_bool(const my_xml_node_t* node, const char* name,
                      bool fallback) {
  const char* s = my_xml_node_attr(node, name);
  if (s == NULL) {
    return fallback;
  }
  return my_str_eq(s, "true") || my_str_eq(s, "1");
}

/* ---------------- built-in widget classes (M24a) ---------------- */

/**
 * @brief Apply the class property table to a freshly created widget:
 * properties are applied in table row order, each only when the XML node
 * carries a same-named attribute (mirrors the former make_* factories).
 */
static void apply_class_props(my_widget_t* widget,
                              const my_widget_class_t* cls,
                              const my_xml_node_t* node) {
  const my_prop_desc_t* p;
  if (cls->props == NULL) {
    return;
  }
  for (p = cls->props; p->name != NULL; p++) {
    const char* s = my_xml_node_attr(node, p->name);
    my_value_t v;
    if (s == NULL || p->set == NULL) {
      continue;
    }
    my_value_init(&v, ((my_object_t*)widget)->allocator);
    switch (p->type) {
      case MY_PROP_STRING:
        my_value_set_str(&v, s);
        break;
      case MY_PROP_INT:
        my_value_set_int32(&v, (int32_t)strtol(s, NULL, 10));
        break;
      case MY_PROP_FLOAT:
        my_value_set_float(&v, strtof(s, NULL));
        break;
      case MY_PROP_BOOL:
        my_value_set_bool(&v, my_str_eq(s, "true") || my_str_eq(s, "1"));
        break;
      default:
        break;
    }
    p->set(widget, &v);
    my_value_reset(&v);
  }
}

/* ---------------- generic attribute application ---------------- */

static my_ret_t apply_common(my_widget_t* widget, const my_xml_node_t* node,
                             my_ui_error_t* err) {
  const char* name = my_xml_node_attr(node, "name");
  const char* lp = my_xml_node_attr(node, "lp");
  const char* layout = my_xml_node_attr(node, "layout");
  size_t i;
  char rules[512];
  size_t rules_len = 0;

  if (name != NULL) {
    my_widget_set_name(widget, name);
  }
  my_widget_set_rect(widget, &(my_rect_t){attr_int(node, "x", 0),
                                          attr_int(node, "y", 0),
                                          attr_int(node, "w", 0),
                                          attr_int(node, "h", 0)});
  if (my_xml_node_attr(node, "visible") != NULL) {
    my_widget_set_visible(widget, attr_bool(node, "visible", true));
  }
  if (my_xml_node_attr(node, "enable") != NULL) {
    widget->enable = attr_bool(node, "enable", true);
  }
  if (my_xml_node_attr(node, "tooltip") != NULL) {
    my_widget_set_tooltip(widget, my_xml_node_attr(node, "tooltip"));
  }
  if (my_xml_node_attr(node, "class") != NULL) {
    my_widget_set_style_class(widget, my_xml_node_attr(node, "class"));
  }
  if (lp != NULL &&
      my_widget_set_layout_params(widget, lp) != MY_RET_OK) {
    if (err != NULL) {
      err->line = node->line;
      snprintf(err->message, sizeof(err->message), "bad lp: %s", lp);
    }
    return MY_RET_FAIL;
  }
  if (layout != NULL && strncmp(layout, "linear:", 7) == 0) {
    bool horizontal = layout[7] == 'h';
    int32_t spacing = 0;
    const char* colon = strchr(layout + 7, ':');
    if (colon != NULL) {
      spacing = (int32_t)strtol(colon + 1, NULL, 10);
    }
    my_widget_set_layouter(widget,
                           my_layouter_linear_create(NULL, horizontal, spacing));
  }

  /* collect v:* attributes into bind_rules (";" separated) */
  rules[0] = '\0';
  for (i = 0; i < node->attr_count; i++) {
    const char* an = node->attrs[i].name;
    const char* av = node->attrs[i].value;
    size_t need;
    if (strncmp(an, "v:", 2) != 0) {
      continue;
    }
    need = strlen(an) + 1 + strlen(av) + 1; /* "name=value;" */
    if (rules_len + need >= sizeof(rules)) {
      if (err != NULL) {
        err->line = node->line;
        snprintf(err->message, sizeof(err->message), "bind rules too long");
      }
      return MY_RET_FAIL;
    }
    rules_len += (size_t)snprintf(rules + rules_len, sizeof(rules) - rules_len,
                                  "%s=%s;", an, av);
  }
  if (rules_len > 0) {
    my_widget_set_bind_rules(widget, rules);
  }
  return MY_RET_OK;
}

/* ---------------- recursive build ---------------- */

static my_widget_t* build_node(const my_allocator_t* allocator, my_pal_t* pal,
                               const my_xml_node_t* node, my_ui_error_t* err);

static my_widget_t* build_children(const my_allocator_t* allocator,
                                   my_pal_t* pal, my_widget_t* parent,
                                   const my_xml_node_t* node,
                                   my_ui_error_t* err) {
  size_t i;
  for (i = 0; i < node->child_count; i++) {
    const my_xml_node_t* child = my_xml_node_child(node, i);
    my_widget_t* w;
    if (my_str_eq(child->name, "style")) {
      continue; /* handled at window level */
    }
    w = build_node(allocator, pal, child, err);
    if (w == NULL) {
      return NULL;
    }
    my_widget_add_child(parent, w);
    my_widget_unref(w);
  }
  return parent;
}

static my_widget_t* build_node(const my_allocator_t* allocator, my_pal_t* pal,
                               const my_xml_node_t* node, my_ui_error_t* err) {
  my_widget_t* widget;
  my_ui_factory_fn_t factory;
  (void)pal;

  if (my_str_eq(node->name, "window")) {
    if (err != NULL) {
      err->line = node->line;
      snprintf(err->message, sizeof(err->message),
               "<window> only allowed as root");
    }
    return NULL;
  }
  /* custom-registered factories take precedence; built-in tags are
   * created through the widget class table (M24a) */
  factory = find_factory(node->name);
  if (factory != NULL) {
    widget = factory(allocator, node);
  } else {
    const my_widget_class_t* cls = my_widget_class_find(node->name);
    if (cls == NULL) {
      if (err != NULL) {
        err->line = node->line;
        snprintf(err->message, sizeof(err->message), "unknown tag <%s>",
                 node->name);
      }
      return NULL;
    }
    widget = cls->create(allocator);
    if (widget != NULL) {
      apply_class_props(widget, cls, node);
    }
  }
  if (widget == NULL) {
    return NULL;
  }
  if (apply_common(widget, node, err) != MY_RET_OK ||
      build_children(allocator, pal, widget, node, err) == NULL) {
    my_widget_unref(widget);
    return NULL;
  }
  return widget;
}

static void apply_style_children(my_window_t* win, const my_xml_node_t* root) {
  size_t i;
  for (i = 0; i < root->child_count; i++) {
    const my_xml_node_t* child = my_xml_node_child(root, i);
    if (my_str_eq(child->name, "style") && child->text != NULL &&
        win->theme != NULL) {
      /* M18b: a <style> block containing '{' is CSS (my_theme_load_css);
       * otherwise the legacy text format. Both coexist. */
      if (strchr(child->text, '{') != NULL) {
        my_theme_load_css(win->theme, child->text);
      } else {
        my_theme_load_str(win->theme, child->text);
      }
    }
  }
}

my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* xml_str, my_ui_error_t* err) {
  my_xml_doc_t* doc;
  my_xml_error_t xerr;
  my_widget_t* result = NULL;

  if (xml_str == NULL) {
    return NULL;
  }
  doc = my_xml_parse(allocator, xml_str, &xerr);
  if (doc == NULL) {
    if (err != NULL) {
      err->line = xerr.line;
      snprintf(err->message, sizeof(err->message), "xml: %s (col %d)",
               xerr.message, xerr.col);
    }
    return NULL;
  }

  if (my_str_eq(doc->root->name, "window")) {
    my_window_t* win;
    if (pal == NULL) {
      if (err != NULL) {
        err->line = doc->root->line;
        snprintf(err->message, sizeof(err->message),
                 "<window> root requires a pal");
      }
      my_xml_doc_destroy(doc);
      return NULL;
    }
    win = my_window_create(allocator, pal, attr_int(doc->root, "w", 640),
                           attr_int(doc->root, "h", 480),
                           my_xml_node_attr(doc->root, "title"));
    if (win != NULL) {
      if (apply_common((my_widget_t*)win, doc->root, err) != MY_RET_OK ||
          build_children(allocator, pal, (my_widget_t*)win, doc->root, err) ==
              NULL) {
        my_widget_unref((my_widget_t*)win);
        win = NULL;
      } else {
        apply_style_children(win, doc->root);
      }
    }
    result = (my_widget_t*)win;
  } else {
    result = build_node(allocator, pal, doc->root, err);
  }
  my_xml_doc_destroy(doc);
  return result;
}

my_widget_t* my_ui_load_file(const my_allocator_t* allocator, my_pal_t* pal,
                             const char* path, my_ui_error_t* err) {
  FILE* f;
  long size;
  char* buf;
  my_widget_t* result;
  if (path == NULL) {
    return NULL;
  }
  f = fopen(path, "rb");
  if (f == NULL) {
    return NULL;
  }
  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);
  buf = (char*)my_mem_alloc(allocator, (size_t)size + 1);
  if (buf == NULL || fread(buf, 1, (size_t)size, f) != (size_t)size) {
    fclose(f);
    my_mem_free(allocator, buf);
    return NULL;
  }
  fclose(f);
  buf[size] = '\0';
  result = my_ui_load_str(allocator, pal, buf, err);
  my_mem_free(allocator, buf);
  return result;
}

#else /* !MYUI_UI_XML */

my_ret_t my_ui_loader_register(const char* tag, my_ui_factory_fn_t factory) {
  (void)tag;
  (void)factory;
  return MY_RET_NOT_SUPPORTED;
}

my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* xml_str, my_ui_error_t* err) {
  (void)allocator;
  (void)pal;
  (void)xml_str;
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

#endif /* MYUI_UI_XML */
