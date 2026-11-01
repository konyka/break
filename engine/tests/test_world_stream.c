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

TEST_MAIN_BEGIN()
    RUN_TEST(stream_loads_near_and_unloads_far);
TEST_MAIN_END()
