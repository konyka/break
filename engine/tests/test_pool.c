/* test_pool.c — Pool allocator unit tests */

#include "test_framework.h"
#include <core/pool.h>
#include <string.h>

typedef struct { u32 a; u32 b; f32 c; } Item;

TEST(init_over_buffer_reports_capacity)
{
    u8 buf[256];
    Pool p;
    usize n = pool_init_for(&p, buf, sizeof(buf), Item);
    ASSERT_TRUE(n > 0);
    ASSERT_EQ(pool_capacity(&p), n);
    ASSERT_EQ(pool_used(&p), (usize)0);
    ASSERT_EQ(pool_available(&p), n);
    pool_destroy(&p);
}

TEST(acquire_release_roundtrip)
{
    Pool p;
    ASSERT_TRUE(pool_init_alloc(&p, sizeof(Item), 4, alignof(Item)));
    ASSERT_EQ(pool_capacity(&p), (usize)4);

    Item *a = pool_acquire_as(&p, Item);
    Item *b = pool_acquire_as(&p, Item);
    ASSERT_TRUE(a != NULL);
    ASSERT_TRUE(b != NULL);
    ASSERT_TRUE(a != b);
    ASSERT_EQ(pool_used(&p), (usize)2);

    /* Blocks must be writable and independent. */
    a->a = 11; b->a = 22;
    ASSERT_EQ(a->a, 11u);
    ASSERT_EQ(b->a, 22u);

    pool_release(&p, a);
    ASSERT_EQ(pool_used(&p), (usize)1);

    /* Freed block is recycled (LIFO) on next acquire. */
    Item *c = pool_acquire_as(&p, Item);
    ASSERT_TRUE(c == a);
    ASSERT_EQ(pool_used(&p), (usize)2);

    pool_destroy(&p);
}

TEST(exhaustion_returns_null)
{
    Pool p;
    ASSERT_TRUE(pool_init_alloc(&p, sizeof(Item), 3, alignof(Item)));
    void *x0 = pool_acquire(&p);
    void *x1 = pool_acquire(&p);
    void *x2 = pool_acquire(&p);
    ASSERT_TRUE(x0 && x1 && x2);
    ASSERT_EQ(pool_available(&p), (usize)0);

    void *x3 = pool_acquire(&p);
    ASSERT_TRUE(x3 == NULL);

    pool_release(&p, x1);
    void *x4 = pool_acquire(&p);
    ASSERT_TRUE(x4 == x1);

    pool_destroy(&p);
}

TEST(reset_reclaims_all)
{
    Pool p;
    ASSERT_TRUE(pool_init_alloc(&p, sizeof(Item), 8, alignof(Item)));
    for (int i = 0; i < 5; i++) (void)pool_acquire(&p);
    ASSERT_EQ(pool_used(&p), (usize)5);

    pool_reset(&p);
    ASSERT_EQ(pool_used(&p), (usize)0);
    ASSERT_EQ(pool_available(&p), (usize)8);

    /* All blocks usable again after reset. */
    int got = 0;
    while (pool_acquire(&p)) got++;
    ASSERT_EQ(got, 8);

    pool_destroy(&p);
}

TEST(owns_detects_membership)
{
    Pool p;
    ASSERT_TRUE(pool_init_alloc(&p, sizeof(Item), 4, alignof(Item)));
    Item *a = pool_acquire_as(&p, Item);
    ASSERT_TRUE(pool_owns(&p, a));

    Item outside = {0};
    ASSERT_TRUE(!pool_owns(&p, &outside));
    ASSERT_TRUE(!pool_owns(&p, NULL));

    /* A misaligned interior pointer is not a valid block boundary. */
    ASSERT_TRUE(!pool_owns(&p, (u8 *)a + 1));

    pool_destroy(&p);
}

TEST(blocks_are_aligned)
{
    Pool p;
    ASSERT_TRUE(pool_init_alloc(&p, sizeof(Item), 6, 16));
    for (int i = 0; i < 6; i++) {
        void *blk = pool_acquire(&p);
        ASSERT_TRUE(blk != NULL);
        ASSERT_EQ(((usize)blk) % 16u, (usize)0);
    }
    pool_destroy(&p);
}

TEST(vtable_alloc_interface)
{
    Pool p;
    ASSERT_TRUE(pool_init_alloc(&p, sizeof(Item), 4, alignof(Item)));
    Alloc *a = (Alloc *)&p;

    Item *it = alloc_new(a, Item);
    ASSERT_TRUE(it != NULL);
    ASSERT_EQ(pool_used(&p), (usize)1);

    /* Oversized request must fail (block too small). */
    void *too_big = a->alloc(a, p.block_size + 1, 8);
    ASSERT_TRUE(too_big == NULL);

    alloc_free(a, it, Item);
    ASSERT_EQ(pool_used(&p), (usize)0);

    pool_destroy(&p);
}

TEST(tiny_buffer_zero_capacity)
{
    u8 tiny[4];
    Pool p;
    usize n = pool_init(&p, tiny, sizeof(tiny), sizeof(Item), alignof(Item));
    ASSERT_EQ(n, (usize)0);
    ASSERT_TRUE(pool_acquire(&p) == NULL);
}

int main(void)
{
    RUN_TEST(init_over_buffer_reports_capacity);
    RUN_TEST(acquire_release_roundtrip);
    RUN_TEST(exhaustion_returns_null);
    RUN_TEST(reset_reclaims_all);
    RUN_TEST(owns_detects_membership);
    RUN_TEST(blocks_are_aligned);
    RUN_TEST(vtable_alloc_interface);
    RUN_TEST(tiny_buffer_zero_capacity);

    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
