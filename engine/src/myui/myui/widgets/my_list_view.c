/**
 * @file my_list_view.c
 * @brief Virtualized list view.
 */
#include "myui/widgets/my_list_view.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>

#include "myui/widgets/my_scroll_bar.h"
#include "myc/my_ref_count.h"

static void lv_sync_rows(my_list_view_t* lv);

struct my_list_adapter_lease_t {
  atomic_uint ref_count;
  const my_allocator_t* allocator;
  my_list_adapter_t* adapter;
  void* context;
  my_list_adapter_destroy_fn destroy;
};

my_list_adapter_lease_t* my_list_adapter_lease_create(
    const my_allocator_t* allocator, my_list_adapter_t* adapter,
    void* context, my_list_adapter_destroy_fn destroy) {
  my_list_adapter_lease_t* lease;
  if (adapter == NULL) {
    return NULL;
  }
  lease = (my_list_adapter_lease_t*)my_mem_calloc(
      allocator, 1u, sizeof(*lease));
  if (lease == NULL) {
    return NULL;
  }
  atomic_init(&lease->ref_count, 1u);
  lease->allocator = allocator;
  lease->adapter = adapter;
  lease->context = context;
  lease->destroy = destroy;
  return lease;
}

my_list_adapter_lease_t* my_list_adapter_lease_ref(
    my_list_adapter_lease_t* lease) {
  if (lease != NULL) {
    (void)my_ref_count_try_ref(&lease->ref_count);
  }
  return lease;
}

void my_list_adapter_lease_unref(my_list_adapter_lease_t* lease) {
  if (lease == NULL || !my_ref_count_release(&lease->ref_count)) {
    return;
  }
  if (lease->destroy != NULL) {
    lease->destroy(lease->adapter, lease->context);
  }
  my_mem_free(lease->allocator, lease);
}

static bool lv_adapter_valid(const my_list_adapter_t* adapter) {
  return adapter != NULL && adapter->vtable != NULL &&
         adapter->vtable->get_count != NULL &&
         adapter->vtable->create_row != NULL &&
         adapter->vtable->bind_row != NULL;
}

static int32_t lv_i64_to_i32(int64_t value) {
  if (value > INT32_MAX) return INT32_MAX;
  if (value < INT32_MIN) return INT32_MIN;
  return (int32_t)value;
}

static bool lv_psum_reserve(my_list_view_t* lv, size_t required) {
  size_t capacity = lv->psum_capacity > 0 ? lv->psum_capacity : 8u;
  int64_t* values;
  if (required <= lv->psum_capacity) return true;
  while (capacity < required) {
    if (capacity > SIZE_MAX / 2u) {
      capacity = required;
      break;
    }
    capacity *= 2u;
  }
  if (capacity > SIZE_MAX / sizeof(*values)) return false;
  values = (int64_t*)my_mem_realloc(lv->allocator, lv->psum_values,
                                    capacity * sizeof(*values));
  if (values == NULL) return false;
  lv->psum_values = values;
  lv->psum_capacity = capacity;
  return true;
}

static void lv_psum_reset(my_list_view_t* lv) {
  if (lv_psum_reserve(lv, 1u)) {
    lv->psum_values[0] = 0;
    lv->psum_count = 1u;
  } else {
    lv->psum_count = 0u;
  }
}

typedef struct row_slot_t {
  my_widget_t* widget;
  size_t index;
} row_slot_t;

static size_t lv_count(my_list_view_t* lv) {
  return lv_adapter_valid(lv->adapter)
             ? lv->adapter->vtable->get_count(lv->adapter)
             : 0;
}

static bool lv_variable(const my_list_view_t* lv) {
  return lv_adapter_valid(lv->adapter) &&
         lv->adapter->vtable->row_height != NULL;
}

static int32_t lv_row_height(my_list_view_t* lv, size_t index) {
  int32_t height;
  if (!lv_variable(lv)) {
    return lv->row_height > 0 ? lv->row_height : 1;
  }
  height = lv->adapter->vtable->row_height(lv->adapter, index);
  /* A malformed adapter must not create zero-length rows or reverse the
   * prefix sum. Fall back to the configured fixed-row estimate. */
  return height > 0 ? height : (lv->row_height > 0 ? lv->row_height : 1);
}

/** @brief Prefix sum: height of rows [0, i). Lazily filled (M9c). */
static int64_t lv_psum_to(my_list_view_t* lv, size_t i) {
  int64_t acc;
  if (lv->psum_count == 0u) { /* lazily created (only used in variable mode) */
    lv_psum_reset(lv);
    if (lv->psum_count == 0u) return 0;
  }
  while (lv->psum_count <= i) {
    /* psum[n] = psum[n-1] + height(row n-1): psum[i] = height of [0, i) */
    size_t n = lv->psum_count;
    int32_t h = lv_row_height(lv, n - 1);
    acc = lv->psum_values[n - 1];
    if (acc > INT64_MAX - h) {
      /* Keep the last valid prefix entry and stop extending the cache. */
      return acc;
    }
    if (!lv_psum_reserve(lv, n + 1u)) {
      return acc;
    }
    lv->psum_values[lv->psum_count++] = acc + h;
  }
  return lv->psum_values[i];
}

/** @brief Total content height; estimated until all rows are measured. */
static int64_t lv_content_height(my_list_view_t* lv) {
  size_t count = lv_count(lv);
  if (!lv_variable(lv)) {
    if (count > (size_t)(INT64_MAX / lv->row_height)) return INT64_MAX;
    return (int64_t)count * lv->row_height;
  }
  if (lv->psum_count >= count) {
    return count > 0 ? lv_psum_to(lv, count) : 0;
  }
  {
    /* measured part + unmeasured part x average seen so far */
    size_t filled = lv->psum_count;
    int64_t known = filled > 0 ? lv_psum_to(lv, filled) : 0;
    double avg = filled > 0 ? (double)known / (double)filled : 24.0;
    double estimated = avg * (double)(count - filled);
    if (estimated >= (double)INT64_MAX - (double)known) return INT64_MAX;
    return known + (int64_t)estimated;
  }
}

static void lv_sync_scroll_bar(my_list_view_t* lv) {
  int64_t content;
  int64_t max;
  if (lv->scroll_bar == NULL) {
    return;
  }
  if (lv->syncing_scroll_bar) {
    return;
  }
  lv->syncing_scroll_bar = true;
  content = lv_content_height(lv);
  max = content - ((my_widget_t*)lv)->rect.h;
  my_scroll_bar_set_page_size(
      lv->scroll_bar, content > 0
                          ? (float)((my_widget_t*)lv)->rect.h / (float)content
                          : 1.0f);
  my_scroll_bar_set_value(lv->scroll_bar,
                          max > 0 ? (float)lv->scroll_offset / (float)max
                                  : 0.0f);
  lv->syncing_scroll_bar = false;
}

static void on_scroll_bar_changed(void* ctx, const char* event, void* data) {
  my_list_view_t* lv = (my_list_view_t*)ctx;
  int64_t max;
  (void)event;
  (void)data;
  if (lv == NULL || lv->syncing || lv->syncing_scroll_bar ||
      lv->scroll_bar == NULL) {
    return;
  }
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
  return max > INT32_MAX ? INT32_MAX : max > 0 ? (int32_t)max : 0;
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
    if (my_darray_push(lv->pool, slot->widget) != MY_RET_OK) {
      /* The extra reference acquired for the pool has no owner on OOM. */
      my_widget_unref(slot->widget);
    }
    my_mem_free(lv->allocator, slot);
  }
}

static void lv_discard_pool(my_list_view_t* lv) {
  while (my_darray_size(lv->pool) > 0) {
    size_t index = my_darray_size(lv->pool) - 1;
    my_widget_t* row = (my_widget_t*)my_darray_get(lv->pool, index);
    my_darray_remove_at(lv->pool, index);
    my_widget_unref(row);
  }
}

static void lv_drop_adapter_lease(my_list_view_t* lv) {
  my_list_adapter_lease_t* lease = lv->adapter_lease;
  lv->adapter_lease = NULL;
  if (lease != NULL) {
    my_list_adapter_lease_unref(lease);
  }
}

/** @brief Rebuild the visible row set from the adapter. */
static void lv_sync_rows(my_list_view_t* lv) {
  my_widget_t* self = (my_widget_t*)lv;
  size_t count;
  size_t first, need, i;
  if (lv == NULL || lv->syncing) {
    return;
  }
  lv->syncing = true;
  my_widget_ref(self);
  count = lv_count(lv);
  if (!lv_adapter_valid(lv->adapter) || lv->row_height <= 0 ||
      self->rect.h <= 0) {
    goto done;
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
        y += lv_row_height(lv, first + need);
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
    goto done;
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
        goto done;
      }
      lv->rows_created_total++;
    }
    lv->adapter->vtable->bind_row(lv->adapter, row, index);
    if (lv_variable(lv)) {
      row_y = lv_i64_to_i32(lv_psum_to(lv, index) - lv->scroll_offset);
      row_h = lv_row_height(lv, index);
    } else {
      row_y = lv_i64_to_i32(
          index > (size_t)(INT64_MAX / lv->row_height)
              ? INT64_MAX
              : (int64_t)index * lv->row_height - lv->scroll_offset);
      row_h = lv->row_height;
    }
    my_widget_set_rect(row, &(my_rect_t){0, row_y, self->rect.w, row_h});
    slot = (row_slot_t*)my_mem_calloc(lv->allocator, 1, sizeof(row_slot_t));
    if (slot == NULL) {
      my_widget_unref(row);
      goto done;
    }
    slot->widget = row;
    slot->index = index;
    if (my_widget_add_child(self, row) != MY_RET_OK) {
      /* not attached: row is still ours; slot must not dangle on it */
      my_widget_unref(row);
      my_mem_free(lv->allocator, slot);
      goto done;
    }
    my_widget_unref(row); /* tree holds the ref while visible */
    if (my_darray_push(lv->active, slot) != MY_RET_OK) {
      my_widget_remove_child(self, row); /* tree drops its ref, row dies */
      my_mem_free(lv->allocator, slot);
      goto done;
    }
  }
done:
  lv->syncing = false;
  my_widget_unref(self);
}

static void lv_on_layout_changed(my_list_view_t* lv) {
  lv_sync_rows(lv);
  lv_sync_scroll_bar(lv);
  my_widget_invalidate((my_widget_t*)lv, NULL);
}

my_ret_t my_list_view_set_scroll_bar(my_widget_t* list_view,
                                     my_widget_t* bar) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  uint32_t listener_id;
  if (!my_list_view_is_instance(list_view)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->syncing) {
    return MY_RET_PENDING;
  }
  if (bar != NULL && !my_scroll_bar_is_instance(bar)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (bar == lv->scroll_bar) {
    lv_sync_scroll_bar(lv);
    return MY_RET_OK;
  }
  if (bar != NULL) {
    listener_id = my_widget_on(bar, "changed", on_scroll_bar_changed, lv);
    if (listener_id == 0u) return MY_RET_OOM;
  } else {
    listener_id = 0u;
  }
  if (lv->scroll_bar != NULL && lv->scroll_bar_listener_id != 0u) {
    (void)my_widget_off(lv->scroll_bar, lv->scroll_bar_listener_id);
  }
  if (lv->scroll_bar != NULL) {
    my_widget_unref(lv->scroll_bar);
  }
  lv->scroll_bar = bar;
  lv->scroll_bar_listener_id = listener_id;
  if (lv->scroll_bar != NULL) {
    my_widget_ref(lv->scroll_bar);
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
    float track = (float)widget->rect.h;
    float content = (float)lv_content_height(lv);
    if (content <= 0.0f || !isfinite(content)) {
      content = FLT_MAX;
    }
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

bool my_list_view_is_instance(const my_widget_t* widget) {
  return widget != NULL && widget->vtable == &s_lv_vtable;
}

static void lv_destroy_chain(my_object_t* obj) {
  my_list_view_t* lv = (my_list_view_t*)obj;
  size_t i, n;
  if (lv->scroll_bar != NULL && lv->scroll_bar_listener_id != 0u) {
    (void)my_widget_off(lv->scroll_bar, lv->scroll_bar_listener_id);
    lv->scroll_bar_listener_id = 0u;
  }
  if (lv->scroll_bar != NULL) {
    my_widget_unref(lv->scroll_bar);
    lv->scroll_bar = NULL;
  }
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
  lv_drop_adapter_lease(lv);
  my_mem_free(lv->allocator, lv->psum_values);
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
  if (!my_list_view_is_instance(list_view) || height <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (((my_list_view_t*)list_view)->syncing) {
    return MY_RET_PENDING;
  }
  ((my_list_view_t*)list_view)->row_height = height;
  lv_on_layout_changed((my_list_view_t*)list_view);
  return MY_RET_OK;
}

my_ret_t my_list_view_set_adapter(my_widget_t* list_view,
                                  my_list_adapter_t* adapter) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  if (!my_list_view_is_instance(list_view)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->syncing) {
    return MY_RET_PENDING;
  }
  if (adapter != NULL && !lv_adapter_valid(adapter)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->adapter == adapter) {
    lv_on_layout_changed(lv);
    return MY_RET_OK;
  }
  /* Rows belong to their factory. Never recycle an old adapter's widgets
   * through a replacement adapter with a different private row contract. */
  lv_recycle_all(lv);
  lv_discard_pool(lv);
  lv_psum_reset(lv);
  lv_drop_adapter_lease(lv);
  lv->adapter = adapter;
  lv->scroll_offset = 0;
  lv_on_layout_changed(lv);
  return MY_RET_OK;
}

my_ret_t my_list_view_set_adapter_lease(
    my_widget_t* list_view, my_list_adapter_lease_t* lease) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  my_list_adapter_t* adapter = lease != NULL ? lease->adapter : NULL;
  if (!my_list_view_is_instance(list_view)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->syncing) {
    return MY_RET_PENDING;
  }
  if (adapter != NULL && !lv_adapter_valid(adapter)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lease != NULL && lv->adapter == adapter &&
      lv->adapter_lease != NULL && lv->adapter_lease != lease) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->adapter == adapter && lv->adapter_lease == lease) {
    lv_on_layout_changed(lv);
    return MY_RET_OK;
  }
  my_list_adapter_lease_ref(lease);
  lv_recycle_all(lv);
  lv_discard_pool(lv);
  lv_psum_reset(lv);
  lv_drop_adapter_lease(lv);
  lv->adapter = adapter;
  lv->adapter_lease = lease;
  lv->scroll_offset = 0;
  lv_on_layout_changed(lv);
  return MY_RET_OK;
}

my_ret_t my_list_view_refresh(my_widget_t* list_view) {
  if (!my_list_view_is_instance(list_view)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (((my_list_view_t*)list_view)->syncing) {
    return MY_RET_PENDING;
  }
  lv_on_layout_changed((my_list_view_t*)list_view);
  return MY_RET_OK;
}

my_ret_t my_list_view_invalidate_row_heights(my_widget_t* list_view) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  if (!my_list_view_is_instance(list_view)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (((my_list_view_t*)list_view)->syncing) {
    return MY_RET_PENDING;
  }
  lv_psum_reset(lv);
  lv_on_layout_changed(lv);
  return MY_RET_OK;
}

my_ret_t my_list_view_invalidate_row_height(my_widget_t* list_view,
                                            size_t index) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  if (!my_list_view_is_instance(list_view)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->syncing) {
    return MY_RET_PENDING;
  }
  if (lv->psum_count > 0u) {
    /* keep psum[0..index] (heights of rows < index), drop the tail */
    if (index == SIZE_MAX) {
      return MY_RET_INVALID_PARAMS;
    }
    if (lv->psum_count > index + 1u) {
      lv->psum_count = index + 1u;
    }
  }
  lv_on_layout_changed(lv);
  return MY_RET_OK;
}

my_ret_t my_list_view_set_scroll_offset(my_widget_t* list_view, int32_t offset) {
  my_list_view_t* lv = (my_list_view_t*)list_view;
  if (!my_list_view_is_instance(list_view)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (lv->syncing) {
    return MY_RET_PENDING;
  }
  lv->scroll_offset = offset;
  lv_clamp_scroll(lv);
  lv_on_layout_changed(lv);
  return MY_RET_OK;
}

int32_t my_list_view_get_scroll_offset(my_widget_t* list_view) {
  return my_list_view_is_instance(list_view)
             ? ((my_list_view_t*)list_view)->scroll_offset
             : 0;
}

size_t my_list_view_rows_created_total(my_widget_t* list_view) {
  return my_list_view_is_instance(list_view)
             ? ((my_list_view_t*)list_view)->rows_created_total
             : 0;
}
