#include <core/alloc.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

/* ---- Heap Allocator ---- */

static void *heap_alloc_fn(Alloc *self, usize size, usize align) {
    (void)self;
    usize extra = align - 1;
    void *raw = malloc(size + extra + sizeof(void *));
    if (!raw) return NULL;
    usize addr = (usize)raw + sizeof(void *);
    usize aligned = (addr + extra) & ~(align - 1);
    ((void **)aligned)[-1] = raw;
    return (void *)aligned;
}

static void heap_free_fn(Alloc *self, void *ptr, usize size) {
    (void)self; (void)size;
    if (!ptr) return;
    void *raw = ((void **)ptr)[-1];
    free(raw);
}

static void *heap_realloc_fn(Alloc *self, void *ptr, usize old_size,
                              usize new_size, usize align) {
    (void)self; (void)old_size;
    if (!ptr) return heap_alloc_fn(self, new_size, align);
    void *raw = ((void **)ptr)[-1];
    usize extra = align - 1;
    void *new_raw = realloc(raw, new_size + extra + sizeof(void *));
    if (!new_raw) return NULL;
    usize addr = (usize)new_raw + sizeof(void *);
    usize aligned = (addr + extra) & ~(align - 1);
    ((void **)aligned)[-1] = new_raw;
    return (void *)aligned;
}

static Alloc heap_vtable = {
    .alloc   = heap_alloc_fn,
    .free    = heap_free_fn,
    .realloc = heap_realloc_fn,
};

Alloc *heap_alloc_create(void) {
    return &heap_vtable;
}

void heap_alloc_destroy(Alloc *a) {
    (void)a;
}

/* ---- Arena -> Alloc wrapper ---- */

void *arena_alloc_wrapper(Alloc *self, usize size, usize align) {
    return arena_alloc(self, size, align);
}

void arena_free_wrapper(Alloc *self, void *ptr, usize size) {
    (void)self; (void)ptr; (void)size;
}

void *arena_realloc_wrapper(Alloc *self, void *ptr, usize old_size,
                               usize new_size, usize align) {
    void *new_ptr = arena_alloc(self, new_size, align);
    if (new_ptr && ptr) {
        usize copy = old_size < new_size ? old_size : new_size;
        memcpy(new_ptr, ptr, copy);
    }
    return new_ptr;
}

/* ---- Debug Allocator ---- */

static void *debug_alloc_fn(Alloc *self, usize size, usize align) {
    DebugAlloc *d = (DebugAlloc *)self;
    void *ptr = d->inner->alloc(d->inner, size, align);
    if (ptr) {
        d->total_allocated += size;
        d->alloc_count++;
        if (d->total_allocated > d->peak_allocated)
            d->peak_allocated = d->total_allocated;
    }
    return ptr;
}

static void debug_free_fn(Alloc *self, void *ptr, usize size) {
    DebugAlloc *d = (DebugAlloc *)self;
    if (ptr) {
        d->total_allocated -= size;
        d->free_count++;
    }
    d->inner->free(d->inner, ptr, size);
}

static void *debug_realloc_fn(Alloc *self, void *ptr, usize old_size,
                               usize new_size, usize align) {
    DebugAlloc *d = (DebugAlloc *)self;
    void *new_ptr = d->inner->realloc(d->inner, ptr, old_size, new_size, align);
    if (new_ptr) {
        d->total_allocated += new_size - old_size;
        if (d->total_allocated > d->peak_allocated)
            d->peak_allocated = d->total_allocated;
    }
    return new_ptr;
}

Alloc *debug_alloc_create(Alloc *inner) {
    DebugAlloc *d = (DebugAlloc *)malloc(sizeof(DebugAlloc));
    if (!d) return NULL;
    d->base = (Alloc){
        .alloc   = debug_alloc_fn,
        .free    = debug_free_fn,
        .realloc = debug_realloc_fn,
    };
    d->inner           = inner;
    d->total_allocated = 0;
    d->peak_allocated  = 0;
    d->alloc_count     = 0;
    d->free_count      = 0;
    return (Alloc *)d;
}

void debug_alloc_destroy(Alloc *a) {
    if (!a) return;
    DebugAlloc *d = (DebugAlloc *)a;
    debug_alloc_report(a);
    free(d);
}

void debug_alloc_report(const Alloc *a) {
    const DebugAlloc *d = (const DebugAlloc *)a;
    LOG_INFO("DebugAlloc: allocs=%zu frees=%zu peak=%zu bytes leaked=%zu bytes",
             d->alloc_count, d->free_count,
             d->peak_allocated, d->total_allocated);
}
