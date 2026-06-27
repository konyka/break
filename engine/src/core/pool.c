#include <core/pool.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

/* ---- helpers ---- */

static usize align_up(usize v, usize align) {
    return (v + align - 1) & ~(align - 1);
}

/* Rebuild the intrusive free list across all blocks (last -> NULL). */
static void pool_build_free_list(Pool *p) {
    p->free_list = NULL;
    /* Thread back-to-front so acquire() hands out ascending addresses first. */
    for (usize i = p->block_count; i-- > 0;) {
        void *block = p->buffer + i * p->block_size;
        *(void **)block = p->free_list;
        p->free_list = block;
    }
    p->used = 0;
}

/* ---- Alloc vtable adapters ---- */

static void *pool_vt_alloc(Alloc *self, usize size, usize align) {
    Pool *p = (Pool *)self;
    (void)align;
    if (size > p->block_size) return NULL;
    return pool_acquire(p);
}

static void pool_vt_free(Alloc *self, void *ptr, usize size) {
    (void)size;
    pool_release((Pool *)self, ptr);
}

static void *pool_vt_realloc(Alloc *self, void *ptr, usize old_size,
                             usize new_size, usize align) {
    Pool *p = (Pool *)self;
    (void)old_size; (void)align;
    /* Same fixed block already satisfies any size that fits. */
    if (new_size <= p->block_size) return ptr ? ptr : pool_acquire(p);
    return NULL; /* cannot grow beyond a block */
}

static void pool_set_vtable(Pool *p) {
    p->base.alloc   = pool_vt_alloc;
    p->base.free    = pool_vt_free;
    p->base.realloc = pool_vt_realloc;
}

/* ---- public API ---- */

usize pool_init(Pool *p, void *buffer, usize buffer_size, usize block_size, usize align) {
    if (!p || !buffer || block_size == 0) return 0;
    if (align == 0) align = sizeof(void *);

    /* A block must hold at least a free-list pointer, and be pointer-aligned so
     * the threaded *(void**) writes are well defined. */
    if (align < sizeof(void *)) align = sizeof(void *);
    usize bs = align_up(block_size, align);
    if (bs < sizeof(void *)) bs = sizeof(void *);

    /* Align the start of the usable region within the caller buffer. */
    usize start = align_up((usize)buffer, align);
    usize pad = start - (usize)buffer;
    if (pad >= buffer_size) return 0;
    usize usable = buffer_size - pad;

    usize count = usable / bs;
    if (count == 0) return 0;

    memset(p, 0, sizeof(*p));
    pool_set_vtable(p);
    p->buffer      = (u8 *)start;
    p->block_size  = bs;
    p->block_count = count;
    p->owns_buffer = false;
    pool_build_free_list(p);
    return count;
}

bool pool_init_alloc(Pool *p, usize block_size, usize block_count, usize align) {
    if (!p || block_size == 0 || block_count == 0) return false;
    if (align == 0) align = sizeof(void *);
    if (align < sizeof(void *)) align = sizeof(void *);
    usize bs = align_up(block_size, align);

    /* Over-allocate by `align` so pool_init can align the start within it. */
    /* R158: Guard against usize overflow in bs * block_count. */
    if (block_count > SIZE_MAX / bs) return false;
    usize bytes = bs * block_count + align;
    void *raw = malloc(bytes);
    if (!raw) return false;

    usize n = pool_init(p, raw, bytes, bs, align);
    if (n == 0) { free(raw); return false; }

    /* pool_init() set up a caller-owned view; mark it pool-owned and remember
     * the malloc base so pool_destroy() can release it. */
    p->owns_buffer = true;
    p->owns_base   = raw;
    return true;
}

void pool_destroy(Pool *p) {
    if (!p) return;
    if (p->owns_buffer && p->owns_base) free(p->owns_base);
    memset(p, 0, sizeof(*p));
}

void *pool_acquire(Pool *p) {
    if (!p || !p->free_list) return NULL;
    void *block = p->free_list;
    p->free_list = *(void **)block;
    p->used++;
    return block;
}

void pool_release(Pool *p, void *ptr) {
    if (!p || !ptr) return;
    *(void **)ptr = p->free_list;
    p->free_list = ptr;
    if (p->used > 0) p->used--;
}

void pool_reset(Pool *p) {
    if (!p) return;
    pool_build_free_list(p);
}

bool pool_owns(const Pool *p, const void *ptr) {
    if (!p || !ptr) return false;
    const u8 *b = (const u8 *)ptr;
    if (b < p->buffer) return false;
    usize off = (usize)(b - p->buffer);
    if (off >= p->block_count * p->block_size) return false;
    return (off % p->block_size) == 0;
}
