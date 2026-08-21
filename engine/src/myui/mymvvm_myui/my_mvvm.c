/**
 * @file my_mvvm.c
 * @brief MVVM convenience layer for myui.
 */
#include "mymvvm_myui/my_mvvm.h"

#include <string.h>

#include "myc/my_str.h"
#include "mymvvm_myui/my_widget_target.h"

/* ---------------- template registry ---------------- */

#define MY_MVVM_MAX_TEMPLATES 16

static my_item_template_t g_templates[MY_MVVM_MAX_TEMPLATES];
static size_t g_template_count = 0;

my_ret_t my_mvvm_register_template(const char* name, my_item_builder_fn_t fn,
                                   void* ctx) {
  size_t i;
  if (name == NULL || fn == NULL || strlen(name) >= 32) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_template_count; i++) {
    if (my_str_eq(g_templates[i].name, name)) {
      g_templates[i].build = fn;
      g_templates[i].ctx = ctx;
      return MY_RET_OK;
    }
  }
  if (g_template_count >= MY_MVVM_MAX_TEMPLATES) {
    return MY_RET_OOM;
  }
  strncpy(g_templates[g_template_count].name, name, 31);
  g_templates[g_template_count].build = fn;
  g_templates[g_template_count].ctx = ctx;
  g_template_count++;
  return MY_RET_OK;
}

const my_item_template_t* my_mvvm_find_template(const char* name) {
  size_t i;
  if (name == NULL) {
    return NULL;
  }
  for (i = 0; i < g_template_count; i++) {
    if (my_str_eq(g_templates[i].name, name)) {
      return &g_templates[i];
    }
  }
  return NULL;
}

/* ---------------- my_mvvm_bind ---------------- */

/** @brief CloseWindow support: close the bound window after the command. */
static void on_close_window_click(void* ctx, const char* event, void* data) {
  my_mvvm_context_t* mc = (my_mvvm_context_t*)ctx;
  (void)event;
  (void)data;
  if (mc->wm != NULL && mc->win != NULL) {
    my_window_manager_close(mc->wm, mc->win);
  }
}

static my_ret_t bind_widget_rules(my_mvvm_context_t* mc, my_widget_t* widget) {
  char rules[512];
  char* cur;
  if (widget->bind_rules == NULL) {
    return MY_RET_OK;
  }
  if (strlen(widget->bind_rules) >= sizeof(rules)) {
    return MY_RET_INVALID_PARAMS;
  }
  {
    my_widget_target_t* target =
        my_widget_target_create(mc->allocator, widget);
    if (target == NULL) {
      return MY_RET_OOM;
    }
    if (my_darray_push(mc->targets, target) != MY_RET_OK) {
      my_widget_target_destroy(target);
      return MY_RET_OOM;
    }
    strcpy(rules, widget->bind_rules);
    cur = rules;
    while (*cur != '\0') {
      char* sep = strchr(cur, ';');
      my_binding_rule_t rule;
      my_ret_t ret;
      if (sep != NULL) {
        *sep = '\0';
      }
      ret = my_binding_rule_parse(cur, &rule);
      if (ret != MY_RET_OK) {
        return ret;
      }
      ret = my_binding_context_bind(mc->ctx, (my_binding_target_t*)target, cur);
      if (ret != MY_RET_OK) {
        return ret;
      }
      if (rule.type == MY_RULE_COMMAND && rule.close_window) {
        my_widget_on(widget, "click", on_close_window_click, mc);
      }
      if (sep == NULL) {
        break;
      }
      cur = sep + 1;
    }
  }
  return MY_RET_OK;
}

static my_ret_t bind_tree(my_mvvm_context_t* mc, my_widget_t* widget) {
  size_t i, n;
  my_ret_t ret = bind_widget_rules(mc, widget);
  if (ret != MY_RET_OK) {
    return ret;
  }
  n = my_widget_child_count(widget);
  for (i = 0; i < n; i++) {
    ret = bind_tree(mc, my_widget_get_child(widget, i));
    if (ret != MY_RET_OK) {
      return ret;
    }
  }
  return MY_RET_OK;
}

my_mvvm_context_t* my_mvvm_bind(my_window_manager_t* wm, my_window_t* win,
                                my_view_model_t* vm) {
  my_mvvm_context_t* mc;
  if (win == NULL || vm == NULL) {
    return NULL;
  }
  mc = (my_mvvm_context_t*)my_mem_calloc(NULL, 1, sizeof(my_mvvm_context_t));
  if (mc == NULL) {
    return NULL;
  }
  mc->wm = wm;
  mc->win = win;
  mc->ctx = my_binding_context_create(NULL, vm);
  mc->targets = my_darray_create(NULL, 0);
  if (mc->ctx == NULL || mc->targets == NULL ||
      bind_tree(mc, (my_widget_t*)win) != MY_RET_OK) {
    my_mvvm_context_destroy(mc);
    return NULL;
  }
  return mc;
}

void my_mvvm_context_destroy(my_mvvm_context_t* mc) {
  size_t i, n;
  if (mc == NULL) {
    return;
  }
  my_binding_context_destroy(mc->ctx);
  n = my_darray_size(mc->targets);
  for (i = 0; i < n; i++) {
    my_widget_target_destroy((my_widget_target_t*)my_darray_get(mc->targets, i));
  }
  my_darray_destroy(mc->targets);
  my_mem_free(mc->allocator, mc);
}

/* ---------------- navigator (window manager backed) ---------------- */

typedef struct page_entry_t {
  char name[32];
  my_page_factory_fn_t factory;
  void* ctx;
} page_entry_t;

static my_ret_t nav_wm_handle(my_navigator_t* nav,
                              const my_navigator_request_t* req) {
  my_navigator_wm_t* n = (my_navigator_wm_t*)nav;
  size_t i, count;
  switch (req->type) {
    case MY_NAV_TO:
      count = my_darray_size(n->pages);
      for (i = 0; i < count; i++) {
        page_entry_t* p = (page_entry_t*)my_darray_get(n->pages, i);
        if (my_str_eq(p->name, req->target)) {
          my_window_t* win = p->factory(n->pal, req->args, p->ctx);
          if (win == NULL) {
            return MY_RET_FAIL;
          }
          my_window_manager_open(n->wm, win);
          my_widget_unref((my_widget_t*)win);
          return MY_RET_OK;
        }
      }
      return MY_RET_NOT_FOUND;
    case MY_NAV_BACK: {
      my_window_t* top = my_window_manager_top(n->wm);
      return top != NULL ? my_window_manager_close(n->wm, top)
                         : MY_RET_NOT_FOUND;
    }
    case MY_NAV_HOME:
      return my_window_manager_back_to_home(n->wm);
    case MY_NAV_REPLACE: {
      my_window_t* top = my_window_manager_top(n->wm);
      my_navigator_request_t to = *req;
      if (top != NULL) {
        my_window_manager_close(n->wm, top);
      }
      to.type = MY_NAV_TO;
      return nav_wm_handle(nav, &to);
    }
    default:
      return MY_RET_INVALID_PARAMS;
  }
}

my_navigator_wm_t* my_navigator_wm_create(const my_allocator_t* allocator,
                                          my_window_manager_t* wm,
                                          my_pal_t* pal) {
  my_navigator_wm_t* n;
  if (wm == NULL || pal == NULL) {
    return NULL;
  }
  n = (my_navigator_wm_t*)my_mem_calloc(allocator, 1, sizeof(my_navigator_wm_t));
  if (n == NULL) {
    return NULL;
  }
  n->base.handle_request = nav_wm_handle;
  n->allocator = allocator;
  n->wm = wm;
  n->pal = pal;
  n->pages = my_darray_create(allocator, 0);
  if (n->pages == NULL) {
    my_mem_free(allocator, n);
    return NULL;
  }
  return n;
}

void my_navigator_wm_destroy(my_navigator_wm_t* nav) {
  size_t i, count;
  if (nav == NULL) {
    return;
  }
  count = my_darray_size(nav->pages);
  for (i = 0; i < count; i++) {
    my_mem_free(nav->allocator, my_darray_get(nav->pages, i));
  }
  my_darray_destroy(nav->pages);
  my_mem_free(nav->allocator, nav);
}

my_ret_t my_navigator_wm_add_page(my_navigator_wm_t* nav, const char* name,
                                  my_page_factory_fn_t factory, void* ctx) {
  page_entry_t* p;
  if (nav == NULL || name == NULL || factory == NULL || strlen(name) >= 32) {
    return MY_RET_INVALID_PARAMS;
  }
  p = (page_entry_t*)my_mem_calloc(nav->allocator, 1, sizeof(page_entry_t));
  if (p == NULL) {
    return MY_RET_OOM;
  }
  strncpy(p->name, name, 31);
  p->factory = factory;
  p->ctx = ctx;
  if (my_darray_push(nav->pages, p) != MY_RET_OK) {
    my_mem_free(nav->allocator, p);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}
