/**
 * @file my_list_view.c
 * @brief Virtualized list view.
 */
#include "myui/widgets/my_list_view.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myui/widgets/my_scroll_bar.h"

static void lv_sync_rows(my_list_view_t* lv);

typedef struct row_slot_t {
  my_widget_t* widget;
  size_t index;
} row_slot_t;

static size_t lv_count(my_list_view_t* lv) {
  return lv->adapter != NULL ? lv->adapter->vtable->get_count(lv->adapter) : 0;
}

static bool lv_variable(const my_list_view_t* lv) {
  return lv->adapter != NULL && lv->adapter->vtable->row_height != NULL;
}

/** @brief Prefix sum: height of rows [0, i). Lazily filled (M9c). */
static int64_t lv_psum_to(my_list_view_t* lv, size_t i) {
  int64_t acc;
  if (lv->psum == NULL) { /* lazily created (only used in variable mode) */
    lv->psum = my_darray_create(lv->allocator, 0);
    if (lv->psum == NULL) {
      return 0;
    }
    my_darray_push(lv->psum, (void*)0); /* psum[0] = height of rows [0,0) = 0 */
  }
  while (my_darray_size(lv->psum) <= i) {
    /* psum[n] = psum[n-1] + height(row n-1): psum[i] = height of [0, i) */
    size_t n = my_darray_size(lv->psum);
    int32_t h = lv->adapter->vtable->row_height(lv->adapter, n - 1);
    acc = n > 0 ? (int64_t)(size_t)my_darray_get(lv->psum, n - 1) : 0;
    my_darray_push(lv->psum, (void*)(size_t)(acc + h));
  }
  return (int64_t)(size_t)my_darray_get(lv->psum, i);
}

/** @brief Total content height; estimated until all rows are measured. */
static int64_t lv_content_height(my_list_view_t* lv) {
  size_t count = lv_count(lv);
  if (!lv_variable(lv)) {
    return (int64_t)count * lv->row_height;
  }
  if (my_darray_size(lv->psum) >= count) {
    return count > 0 ? lv_psum_to(lv, count) : 0;
  }
  {
    /* measured part + unmeasured part x average seen so far */
    size_t filled = my_darray_size(lv->psum);
    int64_t known = filled > 0 ? lv_psum_to(lv, filled) : 0;
    double avg = filled > 0 ? (double)known / (double)filled : 24.0;
    return known + (int64_t)(avg * (double)(count - filled));
  }
}

static void lv_sync_scroll_bar(my_list_view_t* lv) {
  int64_t content;
  int64_t max;
  if (lv->scroll_bar == NULL) {
    return;
  }
  content = lv_content_height(lv);
  max = content - ((my_widget_t*)lv)->rect.h;
  my_scroll_bar_set_page_size(
      lv->scroll_bar, content > 0
                          ? (float)((my_widget_t*)lv)->rect.h / (float)content
                          : 1.0f);
  my_scroll_bar_set_value(lv->scroll_bar,
                          max > 0 ? (float)lv->scroll_offset / (float)max
                                  : 0.0f);
}

static void on_scroll_bar_changed(void* ctx, const char* event, void* data) {
  my_list_view_t* lv = (my_list_view_t*)ctx;
  int64_t max;
  (void)event;
  (void)data;
  max = lv_content_height(lv) - ((my_widget_t*)lv)->rect.h;
  if (max < 0) {
    max = 0;
  }
  lv->scroll_offset =
      (int32_t)(my_scroll_bar_get_value(lv->scroll_bar) * (float)max);
  lv_sync_rows(lv);
  lv_sync_scroll_bar(lv);
  my_widget_invalidate((my_widget_t*)lv, NULL);
}

static int32_t lv_max_offset(my_list_view_t* lv) {
  int64_t content = lv_content_height(lv);
  int64_t max = content - ((my_widget_t*)lv)->rect.h;
  return max > 0 ? (int32_t)max : 0;
}

static void lv_clamp_scroll(my_list_view_t* lv) {
  int32_t max = lv_max_offset(lv);
  if (lv->scroll_offset < 0) {
    lv->scroll_offset = 0;
  }
  if (lv->scroll_offset > max) {
    lv->scroll_offset = max;
  }
}

static my_widget_t* lv_pool_pop(my_list_view_t* lv) {
  size_t n = my_darray_size(lv->pool);
  my_widget_t* w = NULL;
  if (n > 0) {
    w = (my_widget_t*)my_darray_get(lv->pool, n - 1);
    my_darray_remove_at(lv->pool, n - 1);
  }
  return w;
}

/** @brief Recycle all active rows into the pool. */
static void lv_recycle_all(my_list_view_t* lv) {
  my_widget_t* self = (my_widget_t*)lv;
  while (my_darray_size(lv->active) > 0) {
    row_slot_t* slot =
        (row_slot_t*)my_darray_get(lv->active, my_darray_size(lv->active) - 1);
    my_darray_remove_at(lv->active, my_darray_size(lv->active) - 1);
    my_widget_ref(slot->widget); /* pool takes its ref BEFORE the tree's goes */
    my_widget_remove_child(self, slot->widget);
    my_darray_push(lv->pool, slot->widget);
    my_mem_free(lv->allocator, slot);
  }
}

/** @brief Rebuild the visible row set from the adapter. */
static void lv_sync_rows(my_list_view_t* lv) {
  my_widget_t* self = (my_widget_t*)lv;
  size_t count = lv_count(lv);
  size_t first, need, i;
  if (lv->adapter == NULL || lv->row_height <= 0 || self->rect.h <= 0) {
    return;
  }
  lv_clamp_scroll(lv);
  lv_recycle_all(lv);
  if (lv_variable(lv)) {
    /* variable heights: binary-search the first visible row in psum,
     * then walk forward while rows intersect the viewport (+1 buffer) */
    size_t lo = 0, hi = count;
    while (lo < hi) {
      size_t mid = (lo + hi) / 2;
      if (lv_psum_to(lv, mid + 1) <= lv->scroll_offset) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    first = lo;
    {
      int64_t y = first < count ? lv_psum_to(lv, first) : 0;
      need = 0;
      while (first + need < count &&
             y < (int64_t)lv->scroll_offset + self->rect.h + lv->row_height) {
        y += lv->adapter->vtable->row_height(lv->adapter, first + need);
        need++;
      }
      if (need == 0 && first > 0) {
        first--;
        need = 1;
      }
    }
  } else {
    first = (size_t)(lv->scroll_offset / lv->row_height);
    need = (size_t)(self->rect.h / lv->row_height) + 2; /* +1 buffer row */
  }
  if (first >= count) {
    return;
  }
  if (first + need > count) {
    need = count - first;
  }
  for (i = 0; i < need; i++) {
    size_t index = first + i;
    int32_t row_y, row_h;
    my_widget_t* row = lv_pool_pop(lv);
    row_slot_t* slot;
    if (row == NULL) {
      row = lv->adapter->vtable->create_row(lv->adapter);
      if (row == NULL) {
        return;
      }
      lv->rows_created_total++;
    }
    lv->adapter->vtable->bind_row(lv->adapter, row, index);
    if (lv_variable(lv)) {
      row_y = (int32_t)(lv_psum_to(lv, index) - lv->scroll_offset);
      row_h = lv->adapter->vtable->row_height(lv->adapter, index);
    } else {
      row_y = (int32_t)(index * (size_t)lv->row_height) - lv->scroll_offset;
      row_h = lv->row_height;
    }
    my_widget_set_rect(row, &(my_rect_t){0, row_y, self->rect.w, row_h});
    slot = (row_slot_t*)my_mem_calloc(lv->allocator, 1, sizeof(row_slot_t));
    if (slot == NULL) {
      my_widget_unref(row);
      return;
    }
    slot->widget = row;
    slot->index = index;
    my_widget_add_child(self, row);
    my_widget_unref(row); /* tree holds the ref while visible */
    my_darray_push(lv->active, slot);
  }
}

static void lv_on_layout_changed(my_list_view_t* lv) {
  lv_sync_rows(lv);
  lv_sync_scroll_bar(lv);
  my_widget_invalidate((my_widget_t*)lv, NULL);
}

my_ret_t my_list_view_set_scroll_bar(my_widget_t* list_view,
                                     my_widget_t* bar) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  if (list_view == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  lv->scroll_bar = bar;
  if (bar != NULL) {
    my_widget_on(bar, "changed", on_scroll_bar_changed, lv);
  }
  lv_sync_scroll_bar(lv);
  return MY_RET_OK;
}

/* ---------------- vtable ---------------- */

static void lv_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_list_view_t* lv = (my_list_view_t*)widget;
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                          0xFFFFFFFFu);
  int32_t max = lv_max_offset(lv);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  /* scrollbar indicator */
  if (max > 0) {
    size_t count = lv_count(lv);
    float track = (float)widget->rect.h;
    float content = (float)(count * (size_t)lv->row_height);
    float thumb_h = track * (float)widget->rect.h / content;
    float thumb_y = track * (float)lv->scroll_offset / content;
    if (thumb_h < 12.0f) {
      thumb_h = 12.0f;
    }
    my_vgcanvas_set_fill_color(vg, my_color_rgba(120, 120, 120, 180));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)widget->rect.w - 4, thumb_y,
                                            4, thumb_h});
  }
}

static my_ret_t lv_on_event(my_widget_t* widget, const my_event_t* event) {
  my_list_view_t* lv = (my_list_view_t*)widget;
  switch (event->type) {
    case MY_EVENT_POINTER_WHEEL: {
      int32_t before = lv->scroll_offset;
      lv->scroll_offset -= event->u.pointer.delta * lv->row_height * 3;
      lv_clamp_scroll(lv);
      if (lv->scroll_offset == before) {
        return MY_RET_FAIL; /* at the limit: bubble to outer scroll containers */
      }
      lv_on_layout_changed(lv);
      return MY_RET_OK;
    }
    case MY_EVENT_POINTER_DOWN:
      lv->drag_y = event->u.pointer.y;
      lv->drag_start_offset = lv->scroll_offset;
      return MY_RET_OK;
    case MY_EVENT_POINTER_MOVE:
      if (lv->drag_y >= 0) {
        int32_t dy = lv->drag_y - event->u.pointer.y;
        lv->scroll_offset = lv->drag_start_offset + dy;
        lv_clamp_scroll(lv);
        lv_on_layout_changed(lv);
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    case MY_EVENT_POINTER_UP:
      if (lv->drag_y >= 0) {
        lv->drag_y = -1;
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    case MY_EVENT_KEY_DOWN:
      if (event->u.key.key == MY_KEY_PAGE_DOWN ||
          event->u.key.key == MY_KEY_PAGE_UP) {
        int32_t page = ((my_widget_t*)lv)->rect.h > 0
                           ? ((my_widget_t*)lv)->rect.h
                           : 100;
        lv->scroll_offset += event->u.key.key == MY_KEY_PAGE_DOWN ? page
                                                                  : -page;
        lv_clamp_scroll(lv);
        lv_on_layout_changed(lv);
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    default:
      return MY_RET_FAIL;
  }
}

static void lv_on_layout(my_widget_t* widget) {
  lv_sync_rows((my_list_view_t*)widget);
}

static const my_widget_vtable_t s_lv_vtable = {lv_on_paint, lv_on_event,
                                               lv_on_layout, NULL};

static void lv_destroy_chain(my_object_t* obj) {
  my_list_view_t* lv = (my_list_view_t*)obj;
  size_t i, n;
  if (lv->active != NULL) {
    n = my_darray_size(lv->active);
    for (i = 0; i < n; i++) {
      my_mem_free(lv->allocator, my_darray_get(lv->active, i));
    }
    my_darray_destroy(lv->active);
  }
  if (lv->pool != NULL) {
    n = my_darray_size(lv->pool);
    for (i = 0; i < n; i++) {
      my_widget_unref((my_widget_t*)my_darray_get(lv->pool, i));
    }
    my_darray_destroy(lv->pool);
  }
  my_darray_destroy(lv->psum);
  my_widget_destroy((my_widget_t*)lv);
  my_object_destroy(obj);
}

my_widget_t* my_list_view_create(const my_allocator_t* allocator) {
  my_list_view_t* lv =
      (my_list_view_t*)my_mem_calloc(allocator, 1, sizeof(my_list_view_t));
  if (lv == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)lv, allocator, &s_lv_vtable, "list_view") !=
      MY_RET_OK) {
    my_mem_free(allocator, lv);
    return NULL;
  }
  ((my_object_t*)lv)->destroy = lv_destroy_chain;
  lv->allocator = allocator;
  lv->row_height = 24;
  lv->drag_y = -1;
  lv->active = my_darray_create(allocator, 0);
  lv->pool = my_darray_create(allocator, 0);
  if (lv->active == NULL || lv->pool == NULL) {
    my_object_unref((my_object_t*)lv);
    return NULL;
  }
  ((my_widget_t*)lv)->widget_type = "list_view";
  ((my_widget_t*)lv)->focusable = true;
  return (my_widget_t*)lv;
}

my_ret_t my_list_view_set_row_height(my_widget_t* list_view, int32_t height) {
  if (list_view == NULL || height <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_list_view_t*)list_view)->row_height = height;
  lv_on_layout_changed((my_list_view_t*)list_view);
  return MY_RET_OK;
}

my_ret_t my_list_view_set_adapter(my_widget_t* list_view,
                                  my_list_adapter_t* adapter) {
  if (list_view == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_list_view_t*)list_view)->adapter = adapter;
  ((my_list_view_t*)list_view)->scroll_offset = 0;
  lv_on_layout_changed((my_list_view_t*)list_view);
  return MY_RET_OK;
}

my_ret_t my_list_view_refresh(my_widget_t* list_view) {
  if (list_view == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  lv_on_layout_changed((my_list_view_t*)list_view);
  return MY_RET_OK;
}

my_ret_t my_list_view_invalidate_row_heights(my_widget_t* list_view) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  if (list_view == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->psum != NULL) {
    my_darray_clear(lv->psum);
    my_darray_push(lv->psum, (void*)0); /* keep the psum[0] = 0 invariant */
  }
  lv_on_layout_changed(lv);
  return MY_RET_OK;
}

my_ret_t my_list_view_invalidate_row_height(my_widget_t* list_view,
                                            size_t index) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  if (list_view == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->psum != NULL) {
    /* keep psum[0..index] (heights of rows < index), drop the tail */
    while (my_darray_size(lv->psum) > index + 1) {
      my_darray_remove_at(lv->psum, my_darray_size(lv->psum) - 1);
    }
  }
  lv_on_layout_changed(lv);
  return MY_RET_OK;
}

my_ret_t my_list_view_set_scroll_offset(my_widget_t* list_view, int32_t offset) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  if (list_view == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  lv->scroll_offset = offset;
  lv_clamp_scroll(lv);
  lv_on_layout_changed(lv);
  return MY_RET_OK;
}

int32_t my_list_view_get_scroll_offset(my_widget_t* list_view) {
  return list_view != NULL ? ((my_list_view_t*)list_view)->scroll_offset : 0;
}

size_t my_list_view_rows_created_total(my_widget_t* list_view) {
  return list_view != NULL ? ((my_list_view_t*)list_view)->rows_created_total : 0;
}
