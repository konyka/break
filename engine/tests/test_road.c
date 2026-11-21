#include "test_framework.h"
#include <renderer/road.h>
#include <math.h>

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

static void flat(f32 *heights, u32 n, f32 h) {
    for (u32 i = 0; i < n; i++) heights[i] = h;
}

/* The ribbon edges are perpendicular to the local direction in XZ: a road
 * heading along +Z gets edges offset in X. The last point reuses the
 * previous segment's direction. */
TEST(road_edges_are_perpendicular_to_the_direction) {
    f32 heights[16];
    flat(heights, 16, 1.0f);
    Vec3 points[2] = {vec3(1.5f, 0, 0.5f), vec3(1.5f, 0, 2.5f)};
    Vec3 out[4];
    u32 dropped = 9;
    ASSERT_EQ(road_build_ribbon(points, 2, 0.5f, heights, 4, 4, 1.0f, 3.0f, out, 2, &dropped), 2u);
    ASSERT_EQ(dropped, 0u);
    for (u32 i = 0; i < 2u; i++) {
        ASSERT_FLOAT_EQ(out[i * 2u].e[2], out[i * 2u + 1u].e[2], 1e-6);
        f32 dx = out[i * 2u].e[0] - out[i * 2u + 1u].e[0];
        ASSERT_FLOAT_EQ(dx < 0 ? -dx : dx, 1.0f, 1e-5);
        ASSERT_FLOAT_EQ(out[i * 2u].e[1], 3.0f, 1e-6);
    }
    /* the vertical component of the direction is ignored */
    Vec3 hill[2] = {vec3(0.5f, 0, 0.5f), vec3(2.5f, 40.0f, 0.5f)};
    ASSERT_EQ(road_build_ribbon(hill, 2, 0.5f, heights, 4, 4, 1.0f, 1.0f, out, 2, &dropped), 2u);
    ASSERT_FLOAT_EQ(out[0].e[0], out[1].e[0], 1e-6);
    f32 dz = out[0].e[2] - out[1].e[2];
    ASSERT_FLOAT_EQ(dz < 0 ? -dz : dz, 1.0f, 1e-5);
}

/* A point that repeats the next one has no direction and is dropped (its
 * duplicate, which points onward, is kept), as are points past the output
 * capacity. */
TEST(road_drops_repeated_points_and_overflow) {
    f32 heights[16];
    flat(heights, 16, 0.0f);
    Vec3 points[4] = {vec3(0.5f, 0, 0.5f), vec3(0.5f, 0, 0.5f), vec3(1.5f, 0, 0.5f), vec3(2.5f, 0, 0.5f)};
    Vec3 out[2];
    u32 dropped = 0;
    ASSERT_EQ(road_build_ribbon(points, 4, 0.5f, heights, 4, 4, 1.0f, 1.0f, out, 1, &dropped), 1u);
    ASSERT_EQ(dropped, 3u);
    ASSERT_FLOAT_EQ(out[0].e[0], 0.5f, 1e-6);
    ASSERT_FLOAT_EQ(out[0].e[2], 1.0f, 1e-6);
}

/* Fewer than two points, a non-positive width or cell and bad grids build
 * nothing. */
TEST(road_rejects_bad_inputs) {
    f32 heights[4] = {0, 0, 0, 0};
    Vec3 points[2] = {vec3(0.5f, 0, 0.5f), vec3(1.5f, 0, 0.5f)};
    Vec3 out[4];
    u32 dropped = 5;
    ASSERT_EQ(road_build_ribbon(points, 1, 0.5f, heights, 2, 2, 1.0f, 1.0f, out, 2, &dropped), 0u);
    ASSERT_EQ(dropped, 0u);
    ASSERT_EQ(road_build_ribbon(points, 2, 0.0f, heights, 2, 2, 1.0f, 1.0f, out, 2, &dropped), 0u);
    ASSERT_EQ(road_build_ribbon(points, 2, 0.5f, heights, 2, 2, -1.0f, 1.0f, out, 2, &dropped), 0u);
    ASSERT_EQ(road_build_ribbon(points, 2, 0.5f, heights, 0, 2, 1.0f, 1.0f, out, 2, &dropped), 0u);
    ASSERT_EQ(road_build_ribbon(points, 2, 0.5f, heights, 2, 2, 1.0f, INFINITY, out, 2, &dropped), 0u);
    ASSERT_EQ(road_build_ribbon(points, 2, 0.5f, heights, 2, 2, 1.0f, 1.0f, NULL, 2, &dropped), 0u);
    ASSERT_EQ(road_build_ribbon(points, 2, 0.5f, heights, 2, 2, 1.0f, 1.0f, out, 2, NULL), 2u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(road_ribbon_follows_height_and_width);
    RUN_TEST(road_edges_are_perpendicular_to_the_direction);
    RUN_TEST(road_drops_repeated_points_and_overflow);
    RUN_TEST(road_rejects_bad_inputs);
TEST_MAIN_END()
