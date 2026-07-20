/* ==========================================================================
 *  test_alloc.c — Unit tests for the core allocator module.
 * ========================================================================== */

#include "test_framework.h"
#include <core/alloc.h>
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

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(heap_alloc_free);
    RUN_TEST(heap_alloc_array);
    RUN_TEST(heap_realloc);
    RUN_TEST(heap_alignment);
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
TEST_MAIN_END()
