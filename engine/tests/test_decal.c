#include "test_framework.h"
#include <renderer/decal.h>

TEST(decal_snaps_to_height_and_drops_outside) {
    f32 heights[4] = {2.0f, 2.0f, 2.0f, 2.0f};
    Decal in[2];
    memset(in, 0, sizeof(in));
    in[0].position = vec3(0.5f, 99.0f, 0.5f);
    in[0].size = 0.25f;
    in[0].material = 3;
    in[1].position = vec3(-1.0f, 0, 0.5f);
    in[1].size = 0.25f;
    in[1].material = 1;
    Decal out[2];
    out[1].material = 77;
    u32 dropped = 0;
    u32 n = decal_place_on_heightfield(in, 2, out, 2, heights, 2, 2, 1.0f, 3.0f, &dropped);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(dropped, 1u);
    ASSERT_FLOAT_EQ(out[0].position.e[1], 6.0f, 1e-4);
    ASSERT_TRUE(out[0].normal.e[1] > 0.9f);
    ASSERT_EQ(out[0].material, 3u);
    ASSERT_EQ(out[1].material, 77u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(decal_snaps_to_height_and_drops_outside);
TEST_MAIN_END()
