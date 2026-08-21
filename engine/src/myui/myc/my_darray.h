/**
 * @file my_darray.h
 * @brief Dynamic array of void* elements, grows on demand.
 */
#ifndef MY_DARRAY_H
#define MY_DARRAY_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

/** @brief Dynamic array storing opaque pointers. */
typedef struct my_darray_t {
  void** items;                    /**< element storage (capacity slots) */
  size_t size;                     /**< number of elements in use */
  size_t capacity;                 /**< allocated slots */
  const my_allocator_t* allocator; /**< allocator (NULL = default) */
} my_darray_t;

/**
 * @brief Create a darray.
 * @param allocator allocator to use, NULL for the default allocator.
 * @param init_capacity initial capacity hint (0 = a small default).
 * @return the new darray, or NULL on OOM.
 */
my_darray_t* my_darray_create(const my_allocator_t* allocator, size_t init_capacity);

/** @brief Append item (may be NULL). Grows automatically. */
my_ret_t my_darray_push(my_darray_t* arr, void* item);

/** @brief Get element at index, NULL if out of range or arr is NULL. */
void* my_darray_get(const my_darray_t* arr, size_t index);

/**
 * @brief Remove element at index, shifting the tail down.
 * @return MY_RET_OK, or MY_RET_INVALID_PARAMS if index is out of range.
 */
my_ret_t my_darray_remove_at(my_darray_t* arr, size_t index);

/** @brief Number of elements (0 if arr is NULL). */
size_t my_darray_size(const my_darray_t* arr);

/** @brief Remove all elements (capacity is kept). */
my_ret_t my_darray_clear(my_darray_t* arr);

/** @brief Free the array and its storage (elements are NOT freed). */
void my_darray_destroy(my_darray_t* arr);

#endif /* MY_DARRAY_H */
