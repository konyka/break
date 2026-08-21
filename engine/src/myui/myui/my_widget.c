/**
 * @file my_widget.c
 * @brief Widget base class implementation.
 */
#include "myui/my_widget.h"

#include <string.h>

#include "myc/my_darray.h"
#include "myc/my_str.h"
#include "myui/my_layout.h"

/* ---------------- lifecycle ---------------- */

static my_widget_t* my_widget_root(my_widget_t* widget);

static bool my_widget_rect_equal(const my_rect_t* a, const my_rect_t* b) {
  return a->x == b->x && a->y == b->y && a->w == b->w && a->h == b->h;
}

static void my_widget_mark_layout_path(my_widget_t* widget) {
  my_widget_t* ancestor;
  if (widget == NULL) {
    return;
  }
  widget->need_layout = true;
  for (ancestor = widget->parent; ancestor != NULL;
       ancestor = ancestor->parent) {
    ancestor->subtree_need_layout = true;
  }
}

static void my_widget_destroy_chain(my_object_t* obj) {
  my_widget_destroy((my_widget_t*)obj);
  my_object_destroy(obj);
}

my_ret_t my_widget_init(my_widget_t* widget, const my_allocator_t* allocator,
                        const my_widget_vtable_t* vtable, const char* name) {
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  memset(widget, 0, sizeof(*widget));
  widget->base.ref_count = 1;
  widget->base.destroy = my_widget_destroy_chain;
  widget->base.allocator = allocator;
  if (name != NULL) {
    widget->base.name = my_strdup(allocator, name);
    if (widget->base.name == NULL) {
      return MY_RET_OOM;
    }
  }
  widget->vtable = vtable;
  widget->visible = true;
  widget->enable = true;
  widget->widget_type = "widget";
  widget->children = my_darray_create(allocator, 0);
  widget->emitter = my_emitter_create(allocator);
  if (widget->children == NULL || widget->emitter == NULL) {
    /* partial failure: release what init owns; the CALLER frees the
     * struct itself (create() does, subclass factories must too) */
    my_darray_destroy(widget->children);
    my_emitter_destroy(widget->emitter);
    widget->children = NULL;
    widget->emitter = NULL;
    my_mem_free(allocator, widget->base.name);
    widget->base.name = NULL;
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

my_ret_t my_widget_subclass_init(my_widget_t* widget,
                                 const my_widget_vtable_t* vtable) {
  if (widget == NULL || vtable == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  widget->vtable = vtable;
  return MY_RET_OK;
}

my_widget_t* my_widget_create(const my_allocator_t* allocator, const char* name) {
  my_widget_t* widget =
      (my_widget_t*)my_mem_calloc(allocator, 1, sizeof(my_widget_t));
  if (widget == NULL) {
    return NULL;
  }
  if (my_widget_init(widget, allocator, NULL, name) != MY_RET_OK) {
    my_mem_free(allocator, widget);
    return NULL;
  }
  return widget;
}

void my_widget_destroy(my_widget_t* widget) {
  size_t i, n;
  if (widget == NULL) {
    return;
  }
  n = my_darray_size(widget->children);
  for (i = 0; i < n; i++) {
    my_widget_t* child =
        (my_widget_t*)my_darray_get(widget->children, i);
    child->parent = NULL;
    my_widget_unref(child);
  }
  my_darray_destroy(widget->children);
  widget->children = NULL;
  my_emitter_destroy(widget->emitter);
  widget->emitter = NULL;
  my_mem_free(((my_object_t*)widget)->allocator, widget->bind_rules);
  widget->bind_rules = NULL;
  my_mem_free(((my_object_t*)widget)->allocator, widget->tooltip);
  widget->tooltip = NULL;
  my_mem_free(((my_object_t*)widget)->allocator, widget->style_class);
  widget->style_class = NULL;
  if (widget->local_style != NULL) {
    my_style_reset(widget->local_style);
    my_mem_free(((my_object_t*)widget)->allocator, widget->local_style);
    widget->local_style = NULL;
  }
  if (widget->layouter != NULL && widget->layouter->destroy != NULL) {
    widget->layouter->destroy(widget->layouter);
  }
  widget->layouter = NULL;
}

/* ---------------- tree ---------------- */

my_ret_t my_widget_add_child(my_widget_t* parent, my_widget_t* child) {
  my_widget_t* ancestor;
  if (parent == NULL || child == NULL || child == parent) {
    return MY_RET_INVALID_PARAMS;
  }
  if (child->parent != NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  for (ancestor = parent; ancestor != NULL; ancestor = ancestor->parent) {
    if (ancestor == child) {
      return MY_RET_INVALID_PARAMS;
    }
  }
  if (my_darray_push(parent->children, my_widget_ref(child)) != MY_RET_OK) {
    my_widget_unref(child);
    return MY_RET_OOM;
  }
  child->parent = parent;
  my_widget_request_layout(parent);
  my_widget_mark_layout_path(child);
  my_widget_invalidate(parent, NULL);
  return MY_RET_OK;
}

my_ret_t my_widget_remove_child(my_widget_t* parent, my_widget_t* child) {
  size_t i, n;
  if (parent == NULL || child == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(parent->children);
  for (i = 0; i < n; i++) {
    if (my_darray_get(parent->children, i) == child) {
      my_widget_invalidate(parent, NULL);
      my_widget_t* root = my_widget_root(parent);
      if (root != NULL && root->removed_hook != NULL) {
        root->removed_hook(root, child);
      }
      my_darray_remove_at(parent->children, i);
      child->parent = NULL;
      my_widget_request_layout(parent);
      my_widget_unref(child);
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

my_widget_t* my_widget_find_child(my_widget_t* parent, const char* name) {
  size_t i, n;
  if (parent == NULL || name == NULL) {
    return NULL;
  }
  n = my_darray_size(parent->children);
  for (i = 0; i < n; i++) {
    my_widget_t* child = (my_widget_t*)my_darray_get(parent->children, i);
    if (my_str_eq(child->base.name, name)) {
      return child;
    }
  }
  return NULL;
}

my_widget_t* my_widget_find_descendant(my_widget_t* parent, const char* name) {
  size_t i, n;
  my_widget_t* hit;
  if (parent == NULL || name == NULL) {
    return NULL;
  }
  hit = my_widget_find_child(parent, name);
  if (hit != NULL) {
    return hit;
  }
  n = my_widget_child_count(parent);
  for (i = 0; i < n; i++) {
    hit = my_widget_find_descendant(my_widget_get_child(parent, i), name);
    if (hit != NULL) {
      return hit;
    }
  }
  return NULL;
}

size_t my_widget_child_count(my_widget_t* parent) {
  return parent != NULL ? my_darray_size(parent->children) : 0;
}

my_widget_t* my_widget_get_child(my_widget_t* parent, size_t index) {
  if (parent == NULL) {
    return NULL;
  }
  return (my_widget_t*)my_darray_get(parent->children, index);
}

/* ---------------- geometry ---------------- */

static my_ret_t my_widget_set_rect_impl(my_widget_t* widget,
                                        const my_rect_t* rect,
                                        bool schedule_layout) {
  my_rect_t old_rect;
  if (widget == NULL || rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (my_widget_rect_equal(&widget->rect, rect)) {
    return MY_RET_OK;
  }
  old_rect = widget->rect;
  my_widget_invalidate(widget, NULL);
  widget->rect = *rect;
  if (old_rect.w != rect->w || old_rect.h != rect->h) {
    my_widget_mark_layout_path(widget);
  }
  if (schedule_layout) {
    my_widget_request_layout(widget->parent != NULL ? widget->parent : widget);
  }
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

my_ret_t my_widget_set_rect(my_widget_t* widget, const my_rect_t* rect) {
  return my_widget_set_rect_impl(widget, rect, true);
}

my_ret_t my_widget_set_layout_rect(my_widget_t* widget,
                                   const my_rect_t* rect) {
  return my_widget_set_rect_impl(widget, rect, false);
}

void my_widget_request_layout(my_widget_t* widget) {
  my_widget_mark_layout_path(widget);
}

my_ret_t my_widget_set_visible(my_widget_t* widget, bool visible) {
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (widget->visible != visible) {
    my_widget_t* scope = widget->parent != NULL ? widget->parent : widget;
    widget->visible = visible;
    my_widget_request_layout(scope);
    my_widget_invalidate(scope, NULL);
  }
  return MY_RET_OK;
}

my_widget_state_t my_widget_current_state(const my_widget_t* widget,
                                          bool pressed) {
  if (widget == NULL || !widget->enable) {
    return MY_STATE_DISABLED;
  }
  if (pressed) {
    return MY_STATE_PRESSED;
  }
  if (widget->hovered) {
    return MY_STATE_HOVER;
  }
  return MY_STATE_NORMAL;
}

my_ret_t my_widget_set_name(my_widget_t* widget, const char* name) {
  my_object_t* obj = (my_object_t*)widget;
  char* copy;
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  copy = my_strdup(obj->allocator, name);
  if (name != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(obj->allocator, obj->name);
  obj->name = copy;
  return MY_RET_OK;
}

my_ret_t my_widget_set_user_data(my_widget_t* widget, void* user_data) {
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  widget->user_data = user_data;
  return MY_RET_OK;
}

void* my_widget_get_user_data(const my_widget_t* widget) {
  return widget == NULL ? NULL : widget->user_data;
}

my_ret_t my_widget_set_tooltip(my_widget_t* widget, const char* text) {
  const my_allocator_t* alloc;
  char* copy;
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  alloc = ((my_object_t*)widget)->allocator;
  copy = my_strdup(alloc, text);
  if (text != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(alloc, widget->tooltip);
  widget->tooltip = copy;
  return MY_RET_OK;
}

const char* my_widget_get_tooltip(const my_widget_t* widget) {
  return widget == NULL ? NULL : widget->tooltip;
}

my_ret_t my_widget_set_style_class(my_widget_t* widget, const char* cls) {
  const my_allocator_t* alloc;
  char* copy;
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  alloc = ((my_object_t*)widget)->allocator;
  copy = my_strdup(alloc, cls);
  if (cls != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(alloc, widget->style_class);
  widget->style_class = copy;
  my_widget_invalidate(widget, NULL); /* class rules may differ */
  return MY_RET_OK;
}

const char* my_widget_get_style_class(const my_widget_t* widget) {
  return widget == NULL ? NULL : widget->style_class;
}

my_ret_t my_widget_set_bind_rules(my_widget_t* widget, const char* rules) {
  const my_allocator_t* alloc;
  char* copy;
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  alloc = ((my_object_t*)widget)->allocator;
  copy = my_strdup(alloc, rules);
  if (rules != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(alloc, widget->bind_rules);
  widget->bind_rules = copy;
  return MY_RET_OK;
}

static my_widget_t* my_widget_root(my_widget_t* widget) {
  my_widget_t* p = widget;
  while (p != NULL && p->parent != NULL) {
    p = p->parent;
  }
  return p;
}

void my_widget_invalidate(my_widget_t* widget, const my_rect_t* rect) {
  my_rect_t g;
  my_rect_t bounds;
  my_rect_t clipped;
  my_widget_t* p;
  my_widget_t* root;
  if (widget == NULL) {
    return;
  }
  g = rect != NULL ? *rect : my_rect_init(0, 0, widget->rect.w, widget->rect.h);
  p = widget;
  while (p != NULL) {
    p->dirty = true;
    p = p->parent;
  }
  p = widget;
  while (p != NULL) {
    bounds = my_rect_init(0, 0, p->rect.w, p->rect.h);
    if (!my_rect_intersect(&g, &bounds, &clipped)) {
      return;
    }
    g = clipped;
    g.x += p->rect.x;
    g.y += p->rect.y;
    p = p->parent;
  }
  root = my_widget_root(widget);
  if (root != NULL && root->dirty_sink != NULL) {
    my_dirty_rects_add(root->dirty_sink, &g);
  }
}

void my_widget_local_to_global(my_widget_t* widget, int32_t* x, int32_t* y) {
  my_widget_t* p = widget;
  while (p != NULL) {
    *x += p->rect.x;
    *y += p->rect.y;
    p = p->parent;
  }
}

void my_widget_global_to_local(my_widget_t* widget, int32_t* x, int32_t* y) {
  my_widget_t* p = widget;
  while (p != NULL) {
    *x -= p->rect.x;
    *y -= p->rect.y;
    p = p->parent;
  }
}

static my_widget_t* hit_test_rec(my_widget_t* widget, int32_t x, int32_t y) {
  size_t i;
  int32_t lx, ly;
  if (!widget->visible) {
    return NULL;
  }
  lx = x - widget->rect.x;
  ly = y - widget->rect.y;
  if (lx < 0 || ly < 0 || lx >= widget->rect.w || ly >= widget->rect.h) {
    return NULL;
  }
  i = my_darray_size(widget->children);
  while (i > 0) {
    my_widget_t* child;
    my_widget_t* hit;
    i--;
    child = (my_widget_t*)my_darray_get(widget->children, i);
    /* paint-only floating overlays (no on_event, e.g. node_view's
     * minimap/rubber-band layer) must not swallow hits meant for the
     * widgets beneath them; interactive floaters (menus) keep theirs */
    if (child->floating && child->vtable->on_event == NULL) {
      continue;
    }
    hit = hit_test_rec(child, lx, ly);
    if (hit != NULL) {
      return hit;
    }
  }
  return widget;
}

my_widget_t* my_widget_hit_test(my_widget_t* widget, int32_t x, int32_t y) {
  if (widget == NULL) {
    return NULL;
  }
  return hit_test_rec(widget, x, y);
}

/* ---------------- painting ---------------- */

#define MY_WIDGET_PAINT_INLINE_CHILDREN 32

void my_widget_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  size_t i, n;
  my_widget_t* inline_children[MY_WIDGET_PAINT_INLINE_CHILDREN];
  my_widget_t** children = NULL;
  my_widget_t* held_widget;
  if (widget == NULL || vg == NULL || !widget->visible) {
    return;
  }
  held_widget = my_widget_ref(widget);
  n = my_darray_size(widget->children);
  if (n > 0) {
    children = n <= MY_WIDGET_PAINT_INLINE_CHILDREN
                   ? inline_children
                   : (my_widget_t**)my_mem_alloc(
                         ((my_object_t*)widget)->allocator,
                         n * sizeof(my_widget_t*));
    if (children == NULL) {
      my_widget_invalidate(widget, NULL);
      my_widget_unref(held_widget);
      return;
    }
    for (i = 0; i < n; i++) {
      children[i] = my_widget_ref(
          (my_widget_t*)my_darray_get(widget->children, i));
    }
  }
  widget->dirty = false;
  my_vgcanvas_save(vg);
  my_vgcanvas_translate(vg, (float)widget->rect.x, (float)widget->rect.y);
  my_vgcanvas_clip_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                         (float)widget->rect.h});
  if (widget->vtable != NULL && widget->vtable->on_paint != NULL) {
    widget->vtable->on_paint(widget, vg);
  }
  for (i = 0; i < n; i++) {
    if (children[i] != NULL && children[i]->parent == widget) {
      my_widget_paint(children[i], vg);
    }
  }
  my_vgcanvas_restore(vg);
  for (i = 0; i < n; i++) {
    my_widget_unref(children[i]);
  }
  if (children != inline_children) {
    my_mem_free(((my_object_t*)widget)->allocator, children);
  }
  my_widget_unref(held_widget);
}

/* ---------------- emitter convenience ---------------- */

uint32_t my_widget_on(my_widget_t* widget, const char* event_name,
                      my_event_callback_t callback, void* ctx) {
  if (widget == NULL) {
    return 0;
  }
  return my_emitter_on(widget->emitter, event_name, callback, ctx);
}

my_ret_t my_widget_off(my_widget_t* widget, uint32_t id) {
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return my_emitter_off(widget->emitter, id);
}
