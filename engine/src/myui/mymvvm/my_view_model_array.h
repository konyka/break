/**
 * @file my_view_model_array.h
 * @brief Array view model: an observable list of child view models.
 *
 * Implementations emit "items_changed" on the embedded emitter after any
 * mutation; items bindings listen to it and rebuild. The dummy
 * implementation stores my_view_model_t refs in a dynamic array.
 */
#ifndef MY_VIEW_MODEL_ARRAY_H
#define MY_VIEW_MODEL_ARRAY_H

#include "mymvvm/my_view_model.h"

typedef struct my_view_model_array_t my_view_model_array_t;

/** @brief view_model_array vtable. */
typedef struct my_view_model_array_vtable_t {
  size_t (*get_count)(my_view_model_array_t* arr);
  /** @brief Borrowed reference, NULL when out of range. */
  my_view_model_t* (*get_item)(my_view_model_array_t* arr, size_t index);
  my_ret_t (*insert)(my_view_model_array_t* arr, size_t index,
                     my_view_model_t* item);
  my_ret_t (*remove)(my_view_model_array_t* arr, size_t index);
  my_ret_t (*clear)(my_view_model_array_t* arr);
} my_view_model_array_vtable_t;

/** @brief view_model_array base "class" (ref counted like view_model). */
struct my_view_model_array_t {
  my_object_t base;
  const my_view_model_array_vtable_t* vtable;
  my_emitter_t* emitter; /**< "items_changed" */
};

/** @brief Initialize an already-allocated array vm (subclass factories). */
my_ret_t my_view_model_array_init(my_view_model_array_t* arr,
                                  const my_allocator_t* allocator,
                                  const my_view_model_array_vtable_t* vtable);

/** @brief Base cleanup for the destroy chain (frees the emitter). */
void my_view_model_array_destroy(my_view_model_array_t* arr);

static inline my_view_model_array_t* my_view_model_array_ref(
    my_view_model_array_t* arr) {
  return arr != NULL ? (my_view_model_array_t*)my_object_ref((my_object_t*)arr)
                     : NULL;
}

static inline void my_view_model_array_unref(my_view_model_array_t* arr) {
  if (arr != NULL) {
    my_object_unref((my_object_t*)arr);
  }
}

static inline size_t my_view_model_array_get_count(my_view_model_array_t* arr) {
  return arr->vtable->get_count(arr);
}

static inline my_view_model_t* my_view_model_array_get_item(
    my_view_model_array_t* arr, size_t index) {
  return arr->vtable->get_item(arr, index);
}

static inline my_ret_t my_view_model_array_insert(my_view_model_array_t* arr,
                                                  size_t index,
                                                  my_view_model_t* item) {
  return arr->vtable->insert(arr, index, item);
}

static inline my_ret_t my_view_model_array_remove(my_view_model_array_t* arr,
                                                  size_t index) {
  return arr->vtable->remove(arr, index);
}

static inline my_ret_t my_view_model_array_clear(my_view_model_array_t* arr) {
  return arr->vtable->clear(arr);
}

/** @brief Emit "items_changed" (implementations call after mutations). */
my_ret_t my_view_model_array_notify_change(my_view_model_array_t* arr);

/** @brief Dummy implementation: dynamic array of view model refs. */
my_view_model_array_t* my_view_model_array_dummy_create(
    const my_allocator_t* allocator);

/** @brief Append a child (takes over one reference). */
my_ret_t my_view_model_array_dummy_push(my_view_model_array_t* arr,
                                        my_view_model_t* item);

#endif /* MY_VIEW_MODEL_ARRAY_H */
