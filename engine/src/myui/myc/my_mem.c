/**
 * @file my_mem.c
 * @brief Allocator interface: default malloc implementation + debug counter.
 */
#include "myc/my_mem.h"

#include <stdlib.h>

/* ---------------- default allocator ---------------- */

static void* default_alloc(void* ctx, size_t size) {
  (void)ctx;
  return malloc(size);
}

static void* default_calloc(void* ctx, size_t nmemb, size_t size) {
  (void)ctx;
  return calloc(nmemb, size);
}

static void* default_realloc(void* ctx, void* ptr, size_t size) {
  (void)ctx;
  return realloc(ptr, size);
}

static void default_free(void* ctx, void* ptr) {
  (void)ctx;
  free(ptr);
}

const my_allocator_t* my_allocator_default(void) {
  static const my_allocator_t s_default = {NULL, default_alloc, default_calloc,
                                           default_realloc, default_free};
  return &s_default;
}

/* ---------------- convenience wrappers ---------------- */

void* my_mem_alloc(const my_allocator_t* alloc, size_t size) {
  if (alloc == NULL) {
    alloc = my_allocator_default();
  }
  return alloc->alloc(alloc->ctx, size);
}

void* my_mem_calloc(const my_allocator_t* alloc, size_t nmemb, size_t size) {
  if (alloc == NULL) {
    alloc = my_allocator_default();
  }
  return alloc->calloc(alloc->ctx, nmemb, size);
}

void* my_mem_realloc(const my_allocator_t* alloc, void* ptr, size_t size) {
  if (alloc == NULL) {
    alloc = my_allocator_default();
  }
  return alloc->realloc(alloc->ctx, ptr, size);
}

void my_mem_free(const my_allocator_t* alloc, void* ptr) {
  if (ptr == NULL) {
    return;
  }
  if (alloc == NULL) {
    alloc = my_allocator_default();
  }
  alloc->free(alloc->ctx, ptr);
}

/* ---------------- debug (counting) allocator ---------------- */

typedef struct my_debug_allocator_ctx_t {
  const my_allocator_t* base; /**< wrapped allocator, never NULL */
  int live_count;             /**< outstanding allocations */
} my_debug_allocator_ctx_t;

static void* debug_alloc(void* ctx, size_t size) {
  my_debug_allocator_ctx_t* c = (my_debug_allocator_ctx_t*)ctx;
  void* p = c->base->alloc(c->base->ctx, size);
  if (p != NULL) {
    c->live_count++;
  }
  return p;
}

static void* debug_calloc(void* ctx, size_t nmemb, size_t size) {
  my_debug_allocator_ctx_t* c = (my_debug_allocator_ctx_t*)ctx;
  void* p = c->base->calloc(c->base->ctx, nmemb, size);
  if (p != NULL) {
    c->live_count++;
  }
  return p;
}

static void* debug_realloc(void* ctx, void* ptr, size_t size) {
  my_debug_allocator_ctx_t* c = (my_debug_allocator_ctx_t*)ctx;
  void* p = c->base->realloc(c->base->ctx, ptr, size);
  if (p != NULL && ptr == NULL) {
    c->live_count++; /* realloc(NULL, size) behaves like alloc */
  }
  return p;
}

static void debug_free(void* ctx, void* ptr) {
  my_debug_allocator_ctx_t* c = (my_debug_allocator_ctx_t*)ctx;
  if (ptr == NULL) {
    return;
  }
  c->base->free(c->base->ctx, ptr);
  c->live_count--;
}

my_allocator_t* my_allocator_debug_create(const my_allocator_t* base) {
  my_allocator_t* alloc;
  my_debug_allocator_ctx_t* ctx;

  if (base == NULL) {
    base = my_allocator_default();
  }

  alloc = (my_allocator_t*)base->calloc(base->ctx, 1, sizeof(my_allocator_t));
  ctx = (my_debug_allocator_ctx_t*)base->calloc(base->ctx, 1,
                                                sizeof(my_debug_allocator_ctx_t));
  if (alloc == NULL || ctx == NULL) {
    base->free(base->ctx, alloc);
    base->free(base->ctx, ctx);
    return NULL;
  }

  ctx->base = base;
  ctx->live_count = 0;

  alloc->ctx = ctx;
  alloc->alloc = debug_alloc;
  alloc->calloc = debug_calloc;
  alloc->realloc = debug_realloc;
  alloc->free = debug_free;
  return alloc;
}

int my_allocator_debug_leak_count(const my_allocator_t* alloc) {
  const my_debug_allocator_ctx_t* c;
  if (alloc == NULL) {
    return -1;
  }
  c = (const my_debug_allocator_ctx_t*)alloc->ctx;
  return c->live_count;
}

void my_allocator_debug_destroy(my_allocator_t* alloc) {
  my_debug_allocator_ctx_t* c;
  const my_allocator_t* base;
  if (alloc == NULL) {
    return;
  }
  c = (my_debug_allocator_ctx_t*)alloc->ctx;
  base = c->base;
  base->free(base->ctx, c);
  base->free(base->ctx, alloc);
}
