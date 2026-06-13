#pragma once
#include <core/types.h>
#include <core/alloc.h>

/* ---- Pool Allocator ----
 *
 * Fixed-size block allocator with an intrusive free list. O(1) acquire/release,
 * zero fragmentation for same-sized objects (components, particles, nodes, ...).
 *
 * Two ways to provide backing storage:
 *   - pool_init():       caller supplies a buffer (stack/arena/static).
 *   - pool_init_alloc(): the pool mallocs (and owns) its buffer.
 *
 * Also exposes the engine `Alloc` vtable so a Pool can be passed anywhere an
 * `Alloc *` is expected; vtable alloc() returns a block when the requested
 * size fits in block_size, else NULL.
 */

typedef struct {
    Alloc  base;          /* must stay first: enables (Alloc*)pool casts */
    u8    *buffer;
    usize  block_size;    /* usable bytes per block (>= requested, aligned) */
    usize  block_count;
    usize  used;          /* blocks currently handed out */
    void  *free_list;     /* singly-linked list threaded through free blocks */
    void  *owns_base;     /* malloc base to free (NULL for caller-owned) */
    bool   owns_buffer;   /* free() owns_base on pool_destroy */
} Pool;

/* Initialize over a caller-owned buffer. block_size is rounded up to `align`.
 * Returns the number of blocks the buffer can hold (0 on bad args). */
usize pool_init(Pool *p, void *buffer, usize buffer_size, usize block_size, usize align);

/* Initialize with a malloc'd, pool-owned buffer of block_count blocks. */
bool  pool_init_alloc(Pool *p, usize block_size, usize block_count, usize align);

/* Free an owned buffer (no-op for caller-owned buffers) and zero the pool. */
void  pool_destroy(Pool *p);

/* O(1) acquire a zero-uninitialized block, or NULL when exhausted. */
void *pool_acquire(Pool *p);

/* Return a block previously handed out by pool_acquire. NULL is ignored. */
void  pool_release(Pool *p, void *ptr);

/* Reclaim every block (rebuilds the free list). Does not touch contents. */
void  pool_reset(Pool *p);

/* True if ptr lies on a valid block boundary inside this pool. */
bool  pool_owns(const Pool *p, const void *ptr);

static inline usize pool_used(const Pool *p)     { return p ? p->used : 0; }
static inline usize pool_capacity(const Pool *p) { return p ? p->block_count : 0; }
static inline usize pool_available(const Pool *p) {
    return p ? (p->block_count - p->used) : 0;
}

/* Typed convenience. */
#define pool_init_for(p, buf, buf_size, T) \
    pool_init((p), (buf), (buf_size), sizeof(T), alignof(T))
#define pool_acquire_as(p, T) ((T *)pool_acquire((p)))
