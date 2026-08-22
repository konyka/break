/**
 * @file my_object.h
 * @brief Reference-counted base object.
 *
 * Subclassing: embed my_object_t as the FIRST member, create with
 * my_object_create(), then override `destroy` with your own function
 * that frees subclass resources and finally calls my_object_destroy()
 * to free the base (name copy + struct).
 */
#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

typedef struct my_object_t my_object_t;

/** @brief Destructor: must release the object, see my_object_destroy(). */
typedef void (*my_object_destroy_fn_t)(my_object_t* obj);

/** @brief Reference-counted base object. */
struct my_object_t {
  int ref_count;                    /**< current reference count */
  char* name;                       /**< owned copy of the name (may be NULL) */
  my_object_destroy_fn_t destroy;   /**< virtual destructor */
  const my_allocator_t* allocator;  /**< allocator used for name and struct */
};

/**
 * @brief Create an object with ref_count 1 (NULL allocator = default).
 * The name is deep-copied; NULL name is allowed.
 */
my_object_t* my_object_create(const my_allocator_t* allocator, const char* name);

/** @brief Increment the reference count. Returns obj (NULL-safe). */
my_object_t* my_object_ref(my_object_t* obj);

/**
 * @brief Decrement the reference count; when it reaches 0, obj->destroy(obj)
 * is invoked. NULL-safe.
 */
void my_object_unref(my_object_t* obj);

/**
 * @brief Default destructor: frees the name copy and the object itself.
 * Installed by my_object_create(); subclass destructors must call this last.
 */
void my_object_destroy(my_object_t* obj);

#endif /* MY_OBJECT_H */
