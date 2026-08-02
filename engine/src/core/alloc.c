#include <core/alloc.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

/* ---- Heap Allocator ---- */

/* R429: align_up_pow2 moved to alloc.h as a static inline so pool.c and
 * arena_alloc can share it (same non-pow2 rounding as R420 introduced). */

static void *heap_alloc_fn(Alloc *self, usize size, usize align) {
    (void)self;
    /* R419: clamp align like pool_init does — align==0 makes extra=SIZE_MAX,
     * which slips past the overflow guard and computes aligned==0 (wild write).
     * The mask trick below also requires a power-of-two align >= pointer size
     * so the back-pointer slot ((void**)aligned)[-1] stays aligned. */
    align = align_up_pow2(align);  /* R420: also rounds non-pow2 up */
    if (align == 0) return NULL;   /* R420: next pow2 overflowed usize */
    usize extra = align - 1;
    usize total = size + extra + sizeof(void *);
    /* R158: Guard against usize overflow — without this, a very large size
     * wraps to a small value and malloc returns a tiny buffer. */
    if (total < size) return NULL;
    void *raw = malloc(total);
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
    (void)self;
    if (!ptr) return heap_alloc_fn(self, new_size, align);
    void *raw = ((void **)ptr)[-1];
    /* R386: realloc preserves bytes relative to `raw`, but the payload sits at
     * a padded offset that is recomputed from the *new* base. When malloc's
     * own alignment is coarser than `align` those two offsets can differ (e.g.
     * align=32 with a 16-byte-aligned heap: old base ≡0 gives offset 32, new
     * base ≡16 gives offset 16), so the returned pointer no longer points at
     * the preserved bytes. Remember the old offset and relocate if it moved. */
    usize old_off = (usize)ptr - (usize)raw;
    /* R419: same align clamp as heap_alloc_fn (align==0 → extra=SIZE_MAX).
     * R420: also round non-pow2 aligns up — the mask below needs pow2. */
    align = align_up_pow2(align);
    if (align == 0) return NULL;
    usize extra = align - 1;
    usize total = new_size + extra + sizeof(void *);
    /* R158: Guard against usize overflow. */
    if (total < new_size) return NULL;
    void *new_raw = realloc(raw, total);
    if (!new_raw) return NULL;
    usize addr = (usize)new_raw + sizeof(void *);
    usize aligned = (addr + extra) & ~(align - 1);
    usize new_off = aligned - (usize)new_raw;
    if (new_off != old_off) {
        usize keep = old_size < new_size ? old_size : new_size;
        /* R424: the source sits at old_off (the ORIGINAL alignment's offset)
         * but `total` was sized with the NEW alignment — reallocating with a
         * smaller align than the original can put old_off + keep past the end
         * of the new buffer. Clamp the copy to what the buffer actually holds. */
        if (old_off + keep > total) keep = total > old_off ? total - old_off : 0;
        if (keep) memmove((void *)aligned, (u8 *)new_raw + old_off, keep);
    }
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
        /* R420: `total_allocated += new_size - old_size` underflows usize on
         * shrink — add the delta or subtract the difference explicitly. */
        if (new_size >= old_size) d->total_allocated += new_size - old_size;
        else                      d->total_allocated -= old_size - new_size;
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
