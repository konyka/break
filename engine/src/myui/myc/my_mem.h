/**
 * @file my_mem.h
 * @brief Pluggable allocator interface.
 *
 * All myui containers take a const my_allocator_t*; passing NULL selects
 * the default malloc-based allocator. A debug allocator is provided for
 * leak checking in tests.
 */
#ifndef MY_MEM_H
#define MY_MEM_H

#include "myc/my_types.h"

typedef void* (*my_alloc_fn_t)(void* ctx, size_t size);
typedef void* (*my_calloc_fn_t)(void* ctx, size_t nmemb, size_t size);
typedef void* (*my_realloc_fn_t)(void* ctx, void* ptr, size_t size);
typedef void (*my_free_fn_t)(void* ctx, void* ptr);

/** @brief Allocator vtable: function pointers plus an opaque context. */
typedef struct my_allocator_t {
  void* ctx;               /**< opaque context passed to every function */
  my_alloc_fn_t alloc;     /**< allocate size bytes, NULL on OOM */
  my_calloc_fn_t calloc;   /**< allocate zeroed nmemb*size bytes, NULL on OOM */
  my_realloc_fn_t realloc; /**< resize ptr (NULL ptr = alloc) */
  my_free_fn_t free;       /**< release ptr (NULL ptr = no-op) */
} my_allocator_t;

/** @brief Get the process-wide default allocator (malloc/calloc/realloc/free). */
const my_allocator_t* my_allocator_default(void);

/** @brief Allocate size bytes via alloc (NULL alloc = default). */
void* my_mem_alloc(const my_allocator_t* alloc, size_t size);

/** @brief Allocate zeroed nmemb*size bytes via alloc (NULL alloc = default). */
void* my_mem_calloc(const my_allocator_t* alloc, size_t nmemb, size_t size);

/** @brief Resize a block via alloc (NULL alloc = default). */
void* my_mem_realloc(const my_allocator_t* alloc, void* ptr, size_t size);

/** @brief Free a block via alloc (NULL alloc = default, NULL ptr = no-op). */
void my_mem_free(const my_allocator_t* alloc, void* ptr);

/**
 * @brief Create a debugging allocator wrapping base (NULL base = default).
 *
 * Counts outstanding allocations; use my_allocator_debug_leak_count() to
 * verify a module freed everything. Free with my_allocator_debug_destroy().
 */
my_allocator_t* my_allocator_debug_create(const my_allocator_t* base);

/** @brief Number of live (not yet freed) allocations. */
int my_allocator_debug_leak_count(const my_allocator_t* alloc);

/** @brief Destroy a debug allocator created by my_allocator_debug_create(). */
void my_allocator_debug_destroy(my_allocator_t* alloc);

#endif /* MY_MEM_H */
