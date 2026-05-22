#pragma once
#include <core/types.h>
#include <stdalign.h>

/* ---- Allocator Interface ----
 *
 * Hot-path allocators (Arena) are inline in headers.
 * Cold-path allocators (Heap) use vtable indirection.
 */

typedef struct Alloc Alloc;

struct Alloc {
    void *(*alloc)(Alloc *self, usize size, usize align);
    void  (*free)(Alloc *self, void *ptr, usize size);
    void *(*realloc)(Alloc *self, void *ptr, usize old_size, usize new_size, usize align);
};

/* ---- Type-safe allocation macros ---- */
#define alloc_new(a, T)        ((T *)(a)->alloc((a), sizeof(T), alignof(T)))
#define alloc_array(a, T, n)   ((T *)(a)->alloc((a), sizeof(T) * (n), alignof(T)))
#define alloc_free(a, p, T)    ((a)->free((a), (p), sizeof(T)))
#define alloc_free_array(a, p, T, n) ((a)->free((a), (p), sizeof(T) * (n)))

/* ---- Heap Allocator (vtable, wraps malloc/free) ---- */
Alloc *heap_alloc_create(void);
void   heap_alloc_destroy(Alloc *a);

/* ---- Arena Allocator (inline, zero-overhead) ---- */
typedef struct {
    Alloc   base;
    u8     *buffer;
    usize   capacity;
    usize   offset;
} Arena;

void *arena_alloc_wrapper(Alloc *self, usize size, usize align);
void  arena_free_wrapper(Alloc *self, void *ptr, usize size);
void *arena_realloc_wrapper(Alloc *self, void *ptr, usize old_size, usize new_size, usize align);

static inline void arena_init(Arena *a, void *buffer, usize capacity) {
    a->base = (Alloc){
        .alloc   = arena_alloc_wrapper,
        .free    = arena_free_wrapper,
        .realloc = arena_realloc_wrapper,
    };
    a->buffer   = (u8 *)buffer;
    a->capacity = capacity;
    a->offset   = 0;
}

static inline void *arena_alloc(Alloc *self, usize size, usize align) {
    Arena *a = (Arena *)self;
    usize current = (usize)(a->buffer + a->offset);
    usize aligned = (current + align - 1) & ~(align - 1);
    usize offset  = aligned - (usize)a->buffer + size;
    if (offset > a->capacity) return NULL;
    void *ptr = a->buffer + (aligned - (usize)a->buffer);
    a->offset = offset;
    return ptr;
}

static inline void arena_free_all(Arena *a) {
    a->offset = 0;
}

static inline Alloc arena_to_alloc(Arena *a) {
    return a->base;
}

/* ---- Debug Allocator (wraps another, tracks usage) ---- */
typedef struct {
    Alloc     base;
    Alloc    *inner;
    usize     total_allocated;
    usize     peak_allocated;
    usize     alloc_count;
    usize     free_count;
} DebugAlloc;

Alloc *debug_alloc_create(Alloc *inner);
void   debug_alloc_destroy(Alloc *a);
void   debug_alloc_report(const Alloc *a);
