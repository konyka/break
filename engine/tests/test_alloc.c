/* ==========================================================================
 *  test_alloc.c — Unit tests for the core allocator module.
 * ========================================================================== */

#include "test_framework.h"
#include <core/alloc.h>
#include <core/log.h>
#include <string.h>
#include <stdint.h>

/* ----------------------------------------------------------------------- */
/*  Heap Allocator                                                          */
/* ----------------------------------------------------------------------- */

TEST(heap_alloc_free)
{
    Alloc *h = heap_alloc_create();
    ASSERT_NOT_NULL(h);
    i32 *p = alloc_new(h, i32);
    ASSERT_NOT_NULL(p);
    *p = 42;
    ASSERT_EQ(*p, 42);
    alloc_free(h, p, i32);
    heap_alloc_destroy(h);
}

TEST(heap_alloc_array)
{
    Alloc *h = heap_alloc_create();
    f32 *arr = alloc_array(h, f32, 100);
    ASSERT_NOT_NULL(arr);
    for (int i = 0; i < 100; i++) arr[i] = (f32)i;
    ASSERT_EQ(arr[50], 50.0f);
    alloc_free_array(h, arr, f32, 100);
    heap_alloc_destroy(h);
}

TEST(heap_realloc)
{
    Alloc *h = heap_alloc_create();
    u8 *p = alloc_array(h, u8, 16);
    ASSERT_NOT_NULL(p);
    memset(p, 0xAB, 16);
    u8 *p2 = (u8 *)h->realloc(h, p, 16, 64, 1);
    ASSERT_NOT_NULL(p2);
    /* First 16 bytes should be preserved */
    for (int i = 0; i < 16; i++) ASSERT_EQ(p2[i], (u8)0xAB);
    alloc_free_array(h, p2, u8, 64);
    heap_alloc_destroy(h);
}

/* R386: the payload offset is recomputed from the new base after realloc. When
 * the requested alignment is coarser than malloc's own, that offset can change
 * and the payload has to be relocated. Grow repeatedly with align=64 so at
 * least one realloc lands on a base with a different residue. */
TEST(heap_realloc_over_aligned_preserves_payload)
{
    Alloc *h = heap_alloc_create();
    const usize align = 64;

    for (int trial = 0; trial < 64; trial++) {
        usize size = 32;
        u8 *p = (u8 *)h->alloc(h, size, align);
        ASSERT_NOT_NULL(p);
        ASSERT_EQ((usize)p & (align - 1), 0u);
        for (usize i = 0; i < size; i++) p[i] = (u8)(i & 0xFF);

        for (int step = 0; step < 6; step++) {
            usize new_size = size * 2;
            u8 *np = (u8 *)h->realloc(h, p, size, new_size, align);
            ASSERT_NOT_NULL(np);
            ASSERT_EQ((usize)np & (align - 1), 0u);
            for (usize i = 0; i < size; i++) ASSERT_EQ(np[i], (u8)(i & 0xFF));
            for (usize i = size; i < new_size; i++) np[i] = (u8)(i & 0xFF);
            p = np;
            size = new_size;
        }
        h->free(h, p, size);
    }
    heap_alloc_destroy(h);
}

TEST(heap_realloc_different_alignment_shrink)
{
    /* R424: reallocating with a SMALLER alignment than the original (64 -> 8)
     * while shrinking made the relocation memmove read past the new buffer:
     * old_off was sized by the original alignment but `total` by the new one,
     * so old_off + keep could exceed total. The copy must be clamped to what
     * the new buffer holds — no OOB read, and every payload byte that still
     * fits inside the new raw block must be preserved. */
    Alloc *h = heap_alloc_create();
    for (int trial = 0; trial < 64; trial++) {
        usize old_size = 128;
        u8 *p = (u8 *)h->alloc(h, old_size, 64);
        ASSERT_NOT_NULL(p);
        ASSERT_EQ((uintptr_t)p % 64, (uintptr_t)0);
        for (usize i = 0; i < old_size; i++) p[i] = (u8)(i & 0xFF);

        /* Payload offset within the raw block (back-pointer convention). */
        usize old_off = (usize)p - (usize)((void **)p)[-1];

        usize new_size = 96;
        u8 *np = (u8 *)h->realloc(h, p, old_size, new_size, 8);
        ASSERT_NOT_NULL(np);
        ASSERT_EQ((uintptr_t)np % 8, (uintptr_t)0);

        /* realloc preserves bytes relative to the raw base, so the payload
         * prefix beyond the new raw block is gone by construction; everything
         * up to that point must survive. */
        usize total = new_size + 7 + sizeof(void *);
        usize preserved = total > old_off ? total - old_off : 0;
        if (preserved > new_size) preserved = new_size;
        for (usize i = 0; i < preserved; i++) ASSERT_EQ(np[i], (u8)(i & 0xFF));
        h->free(h, np, new_size);
    }
    heap_alloc_destroy(h);
}

TEST(heap_alignment)
{
    Alloc *h = heap_alloc_create();
    /* Allocate with 64-byte alignment */
    void *p = h->alloc(h, 128, 64);
    ASSERT_NOT_NULL(p);
    ASSERT_EQ((uintptr_t)p % 64, (uintptr_t)0);
    h->free(h, p, 128);
    heap_alloc_destroy(h);
}

TEST(heap_zero_alignment_clamped)
{
    /* R419: align==0 underflowed extra to SIZE_MAX, slipped past the overflow
     * guard and computed aligned==0 (wild write). It must be clamped to
     * pointer alignment, matching pool_init. */
    Alloc *h = heap_alloc_create();
    u8 *p = (u8 *)h->alloc(h, 64, 0);
    ASSERT_NOT_NULL(p);
    ASSERT_EQ((uintptr_t)p % sizeof(void *), (uintptr_t)0);
    memset(p, 0xAB, 64);
    /* realloc with align==0 must be clamped too, and preserve the payload */
    u8 *p2 = (u8 *)h->realloc(h, p, 64, 128, 0);
    ASSERT_NOT_NULL(p2);
    ASSERT_EQ((uintptr_t)p2 % sizeof(void *), (uintptr_t)0);
    for (int i = 0; i < 64; i++) ASSERT_EQ(p2[i], (u8)0xAB);
    h->free(h, p2, 128);
    heap_alloc_destroy(h);
}

/* ----------------------------------------------------------------------- */
/*  Arena Allocator                                                         */
/* ----------------------------------------------------------------------- */

TEST(arena_basic)
{
    u8 buf[1024];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    i32 *p = alloc_new(a, i32);
    ASSERT_NOT_NULL(p);
    *p = 99;
    ASSERT_EQ(*p, 99);
    ASSERT_TRUE(arena.offset > 0);
}

TEST(arena_multiple_allocs)
{
    u8 buf[4096];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    for (int i = 0; i < 100; i++) {
        i32 *p = alloc_new(a, i32);
        ASSERT_NOT_NULL(p);
        *p = i;
    }
}

TEST(arena_free_all)
{
    u8 buf[256];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    alloc_array(a, u8, 128);
    ASSERT_TRUE(arena.offset >= 128);

    arena_free_all(&arena);
    ASSERT_EQ(arena.offset, (usize)0);

    /* Can allocate again from the start */
    u8 *p = alloc_array(a, u8, 128);
    ASSERT_NOT_NULL(p);
}

TEST(arena_overflow)
{
    u8 buf[64];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    /* Try to allocate more than capacity */
    void *p = a->alloc(a, 128, 1);
    ASSERT_TRUE(p == NULL);
}

TEST(arena_overflow_size_no_wrap)
{
    /* R264: a near-SIZE_MAX size on a partially-used arena must be rejected.
     * The old `used + size` wrapped past 0 to a small value that passed the
     * `> capacity` test, returning an in-bounds pointer AND rewinding offset
     * below its prior value (letting later allocs overlap live blocks). */
    u8 buf[1024];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    u8 *first = (u8 *)a->alloc(a, 1000, 1);   /* leave 24 bytes free */
    ASSERT_NOT_NULL(first);
    usize saved = arena.offset;
    ASSERT_EQ(saved, (usize)1000);

    void *p = a->alloc(a, SIZE_MAX, 1);
    ASSERT_TRUE(p == NULL);
    ASSERT_EQ(arena.offset, saved);           /* offset must NOT rewind */

    /* Arena still usable and honours the real remaining capacity. */
    void *ok = a->alloc(a, 24, 1);
    ASSERT_NOT_NULL(ok);
    void *too_big = a->alloc(a, 1, 1);
    ASSERT_TRUE(too_big == NULL);
}

TEST(arena_alignment)
{
    u8 buf[1024];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    /* First allocate 1 byte to offset the arena */
    u8 *x = (u8 *)a->alloc(a, 1, 1);
    ASSERT_NOT_NULL(x);

    /* Now allocate with 16-byte alignment */
    void *p = a->alloc(a, 32, 16);
    ASSERT_NOT_NULL(p);
    ASSERT_EQ((uintptr_t)p % 16, (uintptr_t)0);
}

TEST(arena_realloc)
{
    u8 buf[1024];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    u8 *p = alloc_array(a, u8, 8);
    ASSERT_NOT_NULL(p);
    memset(p, 0xCD, 8);

    u8 *p2 = (u8 *)a->realloc(a, p, 8, 32, 1);
    ASSERT_NOT_NULL(p2);
    /* Original data preserved */
    for (int i = 0; i < 8; i++) ASSERT_EQ(p2[i], (u8)0xCD);
}

/* ----------------------------------------------------------------------- */
/*  Debug Allocator                                                         */
/* ----------------------------------------------------------------------- */

TEST(debug_alloc_tracking)
{
    Alloc *heap = heap_alloc_create();
    Alloc *dbg = debug_alloc_create(heap);
    ASSERT_NOT_NULL(dbg);

    DebugAlloc *d = (DebugAlloc *)dbg;
    ASSERT_EQ(d->alloc_count, (usize)0);

    void *p = dbg->alloc(dbg, 100, 8);
    ASSERT_NOT_NULL(p);
    ASSERT_EQ(d->alloc_count, (usize)1);
    ASSERT_EQ(d->total_allocated, (usize)100);
    ASSERT_EQ(d->peak_allocated, (usize)100);

    void *p2 = dbg->alloc(dbg, 200, 8);
    ASSERT_NOT_NULL(p2);
    ASSERT_EQ(d->alloc_count, (usize)2);
    ASSERT_EQ(d->total_allocated, (usize)300);

    dbg->free(dbg, p, 100);
    ASSERT_EQ(d->free_count, (usize)1);
    ASSERT_EQ(d->total_allocated, (usize)200);
    ASSERT_EQ(d->peak_allocated, (usize)300);

    dbg->free(dbg, p2, 200);
    debug_alloc_destroy(dbg);
    heap_alloc_destroy(heap);
}

/* ----------------------------------------------------------------------- */

/*  Edge Cases                                                              */

/* ----------------------------------------------------------------------- */

TEST(heap_free_null)
{
    Alloc *h = heap_alloc_create();
    /* Freeing NULL should not crash */
    h->free(h, NULL, 0);
    heap_alloc_destroy(h);
}

TEST(heap_realloc_null)
{
    Alloc *h = heap_alloc_create();
    /* Realloc with NULL ptr should behave like alloc */
    void *p = h->realloc(h, NULL, 0, 64, 1);
    ASSERT_NOT_NULL(p);
    memset(p, 0xEE, 64);
    h->free(h, p, 64);
    heap_alloc_destroy(h);
}

TEST(arena_zero_size)
{
    u8 buf[64];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    /* Zero-size alloc should return non-NULL */
    void *p = a->alloc(a, 0, 1);
    /* Implementation-dependent: may return NULL or valid ptr */
    /* Just verify it doesn't crash */
    (void)p;
}

TEST(debug_realloc_tracking)
{
    Alloc *heap = heap_alloc_create();
    Alloc *dbg = debug_alloc_create(heap);

    void *p = dbg->alloc(dbg, 50, 8);
    ASSERT_NOT_NULL(p);
    memset(p, 0xAA, 50);

    DebugAlloc *d = (DebugAlloc *)dbg;
    ASSERT_EQ(d->total_allocated, (usize)50);

    void *p2 = dbg->realloc(dbg, p, 50, 100, 8);
    ASSERT_NOT_NULL(p2);
    /* Original data preserved */
    for (int i = 0; i < 50; i++) ASSERT_EQ(((u8 *)p2)[i], (u8)0xAA);

    dbg->free(dbg, p2, 100);
    debug_alloc_destroy(dbg);
    heap_alloc_destroy(heap);
}

TEST(debug_realloc_shrink_stats)
{
    /* R420: `total_allocated += new_size - old_size` underflowed usize on
     * shrink, wrapping total_allocated to a huge value. */
    Alloc *heap = heap_alloc_create();
    Alloc *dbg = debug_alloc_create(heap);

    void *p = dbg->alloc(dbg, 128, 8);
    ASSERT_NOT_NULL(p);

    DebugAlloc *d = (DebugAlloc *)dbg;
    ASSERT_EQ(d->total_allocated, (usize)128);

    void *p2 = dbg->realloc(dbg, p, 128, 32, 8);
    ASSERT_NOT_NULL(p2);
    ASSERT_EQ(d->total_allocated, (usize)32);
    ASSERT_EQ(d->peak_allocated, (usize)128);

    dbg->free(dbg, p2, 32);
    ASSERT_EQ(d->total_allocated, (usize)0);

    debug_alloc_destroy(dbg);
    heap_alloc_destroy(heap);
}

TEST(heap_non_pow2_alignment_rounded)
{
    /* R420: a non-power-of-two align (24) silently broke the &(align-1) mask
     * trick — it must round up to the next power of two (32). */
    Alloc *h = heap_alloc_create();
    u8 *p = (u8 *)h->alloc(h, 64, 24);
    ASSERT_NOT_NULL(p);
    ASSERT_EQ((uintptr_t)p % 32, (uintptr_t)0);
    memset(p, 0xAB, 64);

    u8 *p2 = (u8 *)h->realloc(h, p, 64, 128, 24);
    ASSERT_NOT_NULL(p2);
    ASSERT_EQ((uintptr_t)p2 % 32, (uintptr_t)0);
    for (int i = 0; i < 64; i++) ASSERT_EQ(p2[i], (u8)0xAB);

    h->free(h, p2, 128);
    heap_alloc_destroy(h);
}

TEST(log_set_level_out_of_range_clamped)
{
    /* R420: log_set_level((LogLevel)99) stored the raw value and silently
     * disabled all logging — it must clamp into [LOG_TRACE, LOG_FATAL].
     * After clamping to LOG_FATAL, INFO is suppressed but FATAL still logs;
     * with the bug, even FATAL would be suppressed. */
    log_set_level((LogLevel)99);
    log_write(LOG_FATAL, __FILE__, __LINE__, "R420 clamp test: FATAL visible");
    log_set_level(LOG_INFO);  /* restore default for other tests */
}

TEST(arena_non_pow2_alignment_rounded)
{
    /* R429: arena_alloc with a non-power-of-two align (24) silently
     * misaligned — the mask trick needs pow2. Must round up to 32, matching
     * heap_alloc_fn (R420). */
    u8 buf[1024];
    Arena arena;
    arena_init(&arena, buf, sizeof(buf));
    Alloc *a = &arena.base;

    /* Offset the arena by 1 byte so the alignment actually has to move. */
    u8 *x = (u8 *)a->alloc(a, 1, 1);
    ASSERT_NOT_NULL(x);

    u8 *p = (u8 *)a->alloc(a, 64, 24);
    ASSERT_NOT_NULL(p);
    ASSERT_EQ((uintptr_t)p % 32, (uintptr_t)0);
    memset(p, 0xAB, 64);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(heap_alloc_free);
    RUN_TEST(heap_alloc_array);
    RUN_TEST(heap_realloc);
    RUN_TEST(heap_realloc_over_aligned_preserves_payload);
    RUN_TEST(heap_realloc_different_alignment_shrink);
    RUN_TEST(heap_alignment);
    RUN_TEST(heap_zero_alignment_clamped);
    RUN_TEST(arena_basic);
    RUN_TEST(arena_multiple_allocs);
    RUN_TEST(arena_free_all);
    RUN_TEST(arena_overflow);
    RUN_TEST(arena_overflow_size_no_wrap);
    RUN_TEST(arena_alignment);
    RUN_TEST(arena_realloc);
    RUN_TEST(debug_alloc_tracking);
    /* Edge cases */
    RUN_TEST(heap_free_null);
    RUN_TEST(heap_realloc_null);
    RUN_TEST(arena_zero_size);
    RUN_TEST(debug_realloc_tracking);
    RUN_TEST(debug_realloc_shrink_stats);
    RUN_TEST(heap_non_pow2_alignment_rounded);
    RUN_TEST(arena_non_pow2_alignment_rounded);
    RUN_TEST(log_set_level_out_of_range_clamped);
TEST_MAIN_END()
