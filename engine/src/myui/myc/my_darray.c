/**
 * @file my_darray.c
 * @brief Dynamic array of void* elements.
 */
#include "myc/my_darray.h"

#include <string.h>

#define MY_DARRAY_DEFAULT_CAPACITY 8

my_darray_t* my_darray_create(const my_allocator_t* allocator, size_t init_capacity) {
  my_darray_t* arr = (my_darray_t*)my_mem_calloc(allocator, 1, sizeof(my_darray_t));
  if (arr == NULL) {
    return NULL;
  }
  arr->allocator = allocator;
  if (init_capacity > 0) {
    arr->items = (void**)my_mem_calloc(allocator, init_capacity, sizeof(void*));
    if (arr->items == NULL) {
      my_mem_free(allocator, arr);
      return NULL;
    }
    arr->capacity = init_capacity;
  }
  return arr;
}

static my_ret_t my_darray_reserve(my_darray_t* arr, size_t capacity) {
  void** items;
  size_t new_capacity = arr->capacity > 0 ? arr->capacity : MY_DARRAY_DEFAULT_CAPACITY;
  while (new_capacity < capacity) {
    new_capacity *= 2;
  }
  items = (void**)my_mem_realloc(arr->allocator, arr->items,
                                 new_capacity * sizeof(void*));
  if (items == NULL) {
    return MY_RET_OOM;
  }
  arr->items = items;
  arr->capacity = new_capacity;
  return MY_RET_OK;
}

my_ret_t my_darray_push(my_darray_t* arr, void* item) {
  if (arr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (arr->size >= arr->capacity) {
    my_ret_t ret = my_darray_reserve(arr, arr->size + 1);
    if (ret != MY_RET_OK) {
      return ret;
    }
  }
  arr->items[arr->size++] = item;
  return MY_RET_OK;
}

void* my_darray_get(const my_darray_t* arr, size_t index) {
  if (arr == NULL || index >= arr->size) {
    return NULL;
  }
  return arr->items[index];
}

my_ret_t my_darray_remove_at(my_darray_t* arr, size_t index) {
  if (arr == NULL || index >= arr->size) {
    return MY_RET_INVALID_PARAMS;
  }
  if (index + 1 < arr->size) {
    memmove(arr->items + index, arr->items + index + 1,
            (arr->size - index - 1) * sizeof(void*));
  }
  arr->size--;
  return MY_RET_OK;
}

size_t my_darray_size(const my_darray_t* arr) {
  return arr != NULL ? arr->size : 0;
}

my_ret_t my_darray_clear(my_darray_t* arr) {
  if (arr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  arr->size = 0;
  return MY_RET_OK;
}

void my_darray_destroy(my_darray_t* arr) {
  if (arr == NULL) {
    return;
  }
  my_mem_free(arr->allocator, arr->items);
  my_mem_free(arr->allocator, arr);
}
