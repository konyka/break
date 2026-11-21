#include "test_framework.h"
#include <renderer/world_stream.h>

TEST(stream_loads_near_and_unloads_far) {
    enum { N = 12 };
    bool resident[N * N];
    memset(resident, 0, sizeof(resident));
    StreamWant out[64];
    u32 n = world_stream_want(5, 5, N, N, resident, N * N, out, 64);
    bool saw_center = false;
    for (u32 i = 0; i < n; i++) {
        if (out[i].tile_x == 5 && out[i].tile_z == 5) {
            saw_center = true;
            ASSERT_TRUE(out[i].resident);
        }
    }
    ASSERT_TRUE(saw_center);

    memset(resident, 1, sizeof(resident));
    n = world_stream_want(5, 5, N, N, resident, N * N, out, 64);
    bool center_again = false;
    bool saw_far = false;
    bool saw_ring = false;
    for (u32 i = 0; i < n; i++) {
        if (out[i].tile_x == 5 && out[i].tile_z == 5) center_again = true;
        if (out[i].tile_x == 8 && out[i].tile_z == 5) {
            saw_far = true;
            ASSERT_FALSE(out[i].resident);
        }
        if (out[i].tile_x == 7 && out[i].tile_z == 5) saw_ring = true;
    }
    ASSERT_FALSE(center_again);
    ASSERT_TRUE(saw_far);
    ASSERT_FALSE(saw_ring);

    StreamWant one;
    one.tile_x = 99;
    n = world_stream_want(5, 5, N, N, resident, N * N, &one, 1);
    ASSERT_EQ(n, 1u);
    ASSERT_TRUE(one.tile_x < N);
}

/* A camera in a corner loads only the tiles that exist: the 2x2 corner
 * block, in row-major order. */
TEST(stream_clips_the_load_ring_at_the_world_edge) {
    enum { N = 6 };
    bool resident[N * N];
    memset(resident, 0, sizeof(resident));
    StreamWant out[16];
    u32 n = world_stream_want(0, 0, N, N, resident, N * N, out, 16);
    ASSERT_EQ(n, 4u);
    ASSERT_EQ(out[0].tile_x, 0u);
    ASSERT_EQ(out[0].tile_z, 0u);
    ASSERT_EQ(out[1].tile_x, 1u);
    ASSERT_EQ(out[2].tile_z, 1u);
    for (u32 i = 0; i < n; i++) ASSERT_TRUE(out[i].resident);
}

/* Tiles at Chebyshev distance 2 are a keep band: neither loaded when
 * absent nor unloaded when present. Distance 3 diagonally unloads. */
TEST(stream_keeps_the_distance_two_band) {
    enum { N = 9 };
    bool resident[N * N];
    memset(resident, 0, sizeof(resident));
    resident[2 * N + 2] = true;  /* (2,2): distance 2 from (4,4) */
    resident[1 * N + 1] = true;  /* (1,1): distance 3 */
    resident[4 * N + 6] = true;  /* (6,4): distance 2 */
    StreamWant out[32];
    u32 n = world_stream_want(4, 4, N, N, resident, N * N, out, 32);
    u32 loads = 0;
    bool unloaded_far = false;
    for (u32 i = 0; i < n; i++) {
        ASSERT_FALSE(out[i].tile_x == 2 && out[i].tile_z == 2);
        ASSERT_FALSE(out[i].tile_x == 6 && out[i].tile_z == 4);
        if (out[i].resident) loads++;
        if (!out[i].resident && out[i].tile_x == 1 && out[i].tile_z == 1) unloaded_far = true;
    }
    ASSERT_EQ(loads, 9u);
    ASSERT_TRUE(unloaded_far);
    ASSERT_EQ(n, 10u);
}

/* Short resident arrays, empty grids, overflowing sizes and a NULL output
 * with capacity are refused. */
TEST(stream_rejects_bad_grids) {
    bool resident[4] = {false, false, false, false};
    StreamWant out[4];
    ASSERT_EQ(world_stream_want(0, 0, 2, 2, resident, 3, out, 4), 0u);
    ASSERT_EQ(world_stream_want(0, 0, 0, 2, resident, 4, out, 4), 0u);
    ASSERT_EQ(world_stream_want(0, 0, 2, 2, NULL, 4, out, 4), 0u);
    ASSERT_EQ(world_stream_want(0, 0, 2, 2, resident, 4, NULL, 4), 0u);
    ASSERT_EQ(world_stream_want(0, 0, 0x10000u, 0x10001u, resident, 4, out, 4), 0u);
    ASSERT_EQ(world_stream_want(0, 0, 2, 2, resident, 4, NULL, 0), 0u);
    ASSERT_EQ(world_stream_want(0, 0, 2, 2, resident, 4, out, 4), 4u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_loads_near_and_unloads_far);
    RUN_TEST(stream_clips_the_load_ring_at_the_world_edge);
    RUN_TEST(stream_keeps_the_distance_two_band);
    RUN_TEST(stream_rejects_bad_grids);
TEST_MAIN_END()
