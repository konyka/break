/**
 * @file my_view_model_array.c
 * @brief view_model_array base + dummy implementation.
 */
#include "mymvvm/my_view_model_array.h"

#include <string.h>

#include "myc/my_darray.h"

my_ret_t my_view_model_array_init(my_view_model_array_t* arr,
                                  const my_allocator_t* allocator,
                                  const my_view_model_array_vtable_t* vtable) {
  if (arr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  memset(arr, 0, sizeof(*arr));
  arr->base.ref_count = 1;
  arr->base.allocator = allocator;
  arr->vtable = vtable;
  arr->emitter = my_emitter_create(allocator);
  return arr->emitter != NULL ? MY_RET_OK : MY_RET_OOM;
}

void my_view_model_array_destroy(my_view_model_array_t* arr) {
  if (arr != NULL) {
    my_emitter_destroy(arr->emitter);
    arr->emitter = NULL;
  }
}

my_ret_t my_view_model_array_notify_change(my_view_model_array_t* arr) {
  if (arr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return my_emitter_emit(arr->emitter, "items_changed", NULL);
}

/* ---------------- dummy ---------------- */

typedef struct my_view_model_array_dummy_t {
  my_view_model_array_t base;
  const my_allocator_t* allocator;
  my_darray_t* items; /**< my_view_model_t* (owned refs) */
} my_view_model_array_dummy_t;

static size_t dummy_get_count(my_view_model_array_t* arr) {
  return my_darray_size(((my_view_model_array_dummy_t*)arr)->items);
}

static my_view_model_t* dummy_get_item(my_view_model_array_t* arr,
                                       size_t index) {
  return (my_view_model_t*)my_darray_get(
      ((my_view_model_array_dummy_t*)arr)->items, index);
}

static my_ret_t dummy_insert(my_view_model_array_t* arr, size_t index,
                             my_view_model_t* item) {
  my_view_model_array_dummy_t* d = (my_view_model_array_dummy_t*)arr;
  size_t i, n;
  if (item == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  /* simple append-at-index via push + shift (lists are small in practice) */
  if (my_darray_push(d->items, my_view_model_ref(item)) != MY_RET_OK) {
    my_view_model_unref(item);
    return MY_RET_OOM;
  }
  n = my_darray_size(d->items);
  for (i = n - 1; i > index && i > 0; i--) {
    void** items = d->items->items;
    void* tmp = items[i];
    items[i] = items[i - 1];
    items[i - 1] = tmp;
  }
  return my_view_model_array_notify_change(arr);
}

static my_ret_t dummy_remove(my_view_model_array_t* arr, size_t index) {
  my_view_model_array_dummy_t* d = (my_view_model_array_dummy_t*)arr;
  my_view_model_t* item = (my_view_model_t*)my_darray_get(d->items, index);
  if (item == NULL) {
    return MY_RET_NOT_FOUND;
  }
  my_darray_remove_at(d->items, index);
  my_view_model_unref(item);
  return my_view_model_array_notify_change(arr);
}

static my_ret_t dummy_clear(my_view_model_array_t* arr) {
  my_view_model_array_dummy_t* d = (my_view_model_array_dummy_t*)arr;
  while (my_darray_size(d->items) > 0) {
    size_t last = my_darray_size(d->items) - 1;
    my_view_model_unref((my_view_model_t*)my_darray_get(d->items, last));
    my_darray_remove_at(d->items, last);
  }
  return my_view_model_array_notify_change(arr);
}

static const my_view_model_array_vtable_t s_dummy_array_vtable = {
    dummy_get_count, dummy_get_item, dummy_insert, dummy_remove, dummy_clear};

static void dummy_array_destroy_chain(my_object_t* obj) {
  my_view_model_array_dummy_t* d = (my_view_model_array_dummy_t*)obj;
  while (my_darray_size(d->items) > 0) {
    size_t last = my_darray_size(d->items) - 1;
    my_view_model_unref((my_view_model_t*)my_darray_get(d->items, last));
    my_darray_remove_at(d->items, last);
  }
  my_darray_destroy(d->items);
  my_view_model_array_destroy((my_view_model_array_t*)d);
  my_object_destroy(obj);
}

my_view_model_array_t* my_view_model_array_dummy_create(
    const my_allocator_t* allocator) {
  my_view_model_array_dummy_t* d =
      (my_view_model_array_dummy_t*)my_mem_calloc(
          allocator, 1, sizeof(my_view_model_array_dummy_t));
  if (d == NULL) {
    return NULL;
  }
  if (my_view_model_array_init((my_view_model_array_t*)d, allocator,
                               &s_dummy_array_vtable) != MY_RET_OK) {
    my_mem_free(allocator, d);
    return NULL;
  }
  ((my_object_t*)d)->destroy = dummy_array_destroy_chain;
  d->allocator = allocator;
  d->items = my_darray_create(allocator, 0);
  if (d->items == NULL) {
    my_object_unref((my_object_t*)d);
    return NULL;
  }
  return (my_view_model_array_t*)d;
}

my_ret_t my_view_model_array_dummy_push(my_view_model_array_t* arr,
                                        my_view_model_t* item) {
  if (arr == NULL || arr->vtable != &s_dummy_array_vtable || item == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (my_darray_push(((my_view_model_array_dummy_t*)arr)->items,
                     my_view_model_ref(item)) != MY_RET_OK) {
    my_view_model_unref(item);
    return MY_RET_OOM;
  }
  return my_view_model_array_notify_change(arr);
}
