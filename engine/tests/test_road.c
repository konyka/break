#include "test_framework.h"
#include <renderer/road.h>

TEST(road_ribbon_follows_height_and_width) {
    f32 heights[16];
    for (int i = 0; i < 16; i++) heights[i] = 2.0f;
    Vec3 points[3];
    points[0] = vec3(0.5f, 50.0f, 0.5f);
    points[1] = vec3(2.5f, 50.0f, 0.5f);
    points[2] = vec3(-1.0f, 0.0f, 0.5f);
    Vec3 out[6];
    out[4] = vec3(7, 7, 7);
    u32 dropped = 0;
    u32 pairs = road_build_ribbon(points, 3, 1.0f, heights, 4, 4, 1.0f, 1.0f, out, 3, &dropped);
    ASSERT_EQ(pairs, 2u);
    ASSERT_EQ(dropped, 1u);
    ASSERT_FLOAT_EQ(out[0].e[1], 2.0f, 1e-4);
    ASSERT_FLOAT_EQ(out[1].e[1], 2.0f, 1e-4);
    f32 width = out[0].e[2] - out[1].e[2];
    if (width < 0) width = -width;
    ASSERT_FLOAT_EQ(width, 2.0f, 1e-4);
    ASSERT_FLOAT_EQ(out[4].e[0], 7.0f, 1e-5);
}

TEST_MAIN_BEGIN()
    RUN_TEST(road_ribbon_follows_height_and_width);
TEST_MAIN_END()
