/**
 * @file my_widget_target.c
 * @brief Widget <-> binding target adapter.
 */
#include "mymvvm_myui/my_widget_target.h"

#include <string.h>

#include "myc/my_str.h"
#include "mymvvm_myui/my_mvvm.h"
#include "myui/my_widget_class.h"
#include "myui/widgets/my_list_view.h"

/* ---------------- properties ---------------- */

static my_ret_t target_set_prop(my_binding_target_t* t, const char* name,
                                const my_value_t* v) {
  my_widget_target_t* wt = (my_widget_target_t*)t;
  my_ret_t r = my_widget_set_prop(wt->widget, name, v);
  if (r == MY_RET_NOT_SUPPORTED && strcmp(name, "value") == 0) {
    /* generic "value" fallback store for widgets without a value prop */
    my_value_reset(&wt->value);
    my_value_init(&wt->value, wt->allocator);
    return my_value_copy(&wt->value, v);
  }
  return r;
}

static my_ret_t target_get_prop(my_binding_target_t* t, const char* name,
                                my_value_t* v) {
  my_widget_target_t* wt = (my_widget_target_t*)t;
  my_ret_t r = my_widget_get_prop(wt->widget, name, v);
  if (r == MY_RET_NOT_SUPPORTED && strcmp(name, "value") == 0) {
    return my_value_copy(v, &wt->value);
  }
  return r;
}

/* ---------------- events ---------------- */

static uint32_t target_on_event(my_binding_target_t* t, const char* event,
                                my_event_callback_t cb, void* ctx) {
  return my_widget_on(((my_widget_target_t*)t)->widget, event, cb, ctx);
}

static my_ret_t target_off_event(my_binding_target_t* t, uint32_t id) {
  return my_widget_off(((my_widget_target_t*)t)->widget, id);
}

/* ---------------- items ---------------- */

/* items binding on a list_view: virtualized via an adapter (M8b) */
typedef struct items_adapter_t {
  my_list_adapter_t base;
  const my_allocator_t* allocator;
  const my_item_template_t* tmpl;
  size_t count;
  my_item_props_fn_t props;
  void* props_ctx;
} items_adapter_t;

static size_t items_adapter_count(my_list_adapter_t* adapter) {
  return ((items_adapter_t*)adapter)->count;
}

static my_widget_t* items_adapter_create_row(my_list_adapter_t* adapter) {
  items_adapter_t* a = (items_adapter_t*)adapter;
  return my_widget_create(a->allocator, "row");
}

static void items_adapter_bind_row(my_list_adapter_t* adapter,
                                   my_widget_t* row, size_t index) {
  items_adapter_t* a = (items_adapter_t*)adapter;
  my_widget_t* content;
  while (my_widget_child_count(row) > 0) {
    my_widget_remove_child(row, my_widget_get_child(row, 0));
  }
  content = a->tmpl->build(row, index, a->props, a->props_ctx, a->tmpl->ctx);
  if (content != NULL) {
    my_widget_set_rect(content, &(my_rect_t){0, 0, row->rect.w, row->rect.h});
    my_widget_add_child(row, content);
    my_widget_unref(content);
  }
}

static const my_list_adapter_vtable_t ITEMS_ADAPTER_VTABLE = {
    items_adapter_count, items_adapter_create_row, items_adapter_bind_row,
    NULL};

static void items_adapter_destroy(my_widget_target_t* wt) {
  items_adapter_t* a = (items_adapter_t*)wt->items_adapter;
  if (a != NULL) {
    my_mem_free(wt->allocator, a);
    wt->items_adapter = NULL;
  }
}

static my_ret_t target_rebuild_items(my_binding_target_t* t,
                                     const char* item_template, size_t count,
                                     my_item_props_fn_t props,
                                     void* props_ctx) {
  my_widget_target_t* wt = (my_widget_target_t*)t;
  my_widget_t* container = wt->widget;
  size_t i;
  const my_item_template_t* tmpl = my_mvvm_find_template(item_template);

  /* list_view: virtualized path (M8b) */
  if (my_str_eq(container->widget_type, "list_view")) {
    items_adapter_t* a = (items_adapter_t*)wt->items_adapter;
    if (tmpl == NULL) {
      return MY_RET_NOT_FOUND;
    }
    if (a != NULL && a->tmpl == tmpl) {
      a->count = count;
      a->props = props;
      a->props_ctx = props_ctx;
      return my_list_view_refresh(container);
    }
    a = (items_adapter_t*)my_mem_calloc(wt->allocator, 1,
                                        sizeof(items_adapter_t));
    if (a == NULL) {
      return MY_RET_OOM;
    }
    a->base.vtable = &ITEMS_ADAPTER_VTABLE;
    a->allocator = wt->allocator;
    a->tmpl = tmpl;
    a->count = count;
    a->props = props;
    a->props_ctx = props_ctx;
    items_adapter_destroy(wt); /* replace previous */
    wt->items_adapter = a;
    return my_list_view_set_adapter(container, (my_list_adapter_t*)a);
  }

  while (my_widget_child_count(container) > 0) {
    my_widget_remove_child(container, my_widget_get_child(container, 0));
  }
  if (tmpl == NULL) {
    return MY_RET_NOT_FOUND;
  }
  for (i = 0; i < count; i++) {
    my_widget_t* child = tmpl->build(container, i, props, props_ctx, tmpl->ctx);
    if (child != NULL) {
      my_widget_add_child(container, child);
      my_widget_unref(child);
    }
  }
  my_widget_invalidate(container, NULL);
  return MY_RET_OK;
}

/* ---------------- lifecycle ---------------- */

static const my_binding_target_vtable_t WIDGET_TARGET_VTABLE = {
    target_set_prop, target_get_prop, target_on_event, target_off_event,
    target_rebuild_items};

my_widget_target_t* my_widget_target_create(const my_allocator_t* allocator,
                                            my_widget_t* widget) {
  my_widget_target_t* wt;
  if (widget == NULL) {
    return NULL;
  }
  wt = (my_widget_target_t*)my_mem_calloc(allocator, 1,
                                          sizeof(my_widget_target_t));
  if (wt == NULL) {
    return NULL;
  }
  wt->base.vtable = &WIDGET_TARGET_VTABLE;
  wt->allocator = allocator;
  wt->widget = widget;
  my_value_init(&wt->value, allocator);
  return wt;
}

void my_widget_target_destroy(my_widget_target_t* target) {
  if (target != NULL) {
    items_adapter_destroy(target);
    my_value_reset(&target->value);
    my_mem_free(target->allocator, target);
  }
}
