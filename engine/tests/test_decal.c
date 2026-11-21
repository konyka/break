#include "test_framework.h"
#include <renderer/decal.h>
#include <math.h>

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

/* On a slope the normal tilts away from the uphill side and stays unit
 * length; edge cells clamp their neighbours instead of reading outside. */
TEST(decal_normal_follows_the_slope) {
    /* height rises with x: 0, 1, 2 per column, 3 rows */
    f32 heights[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
    Decal in[2];
    memset(in, 0, sizeof(in));
    in[0].position = vec3(1.5f, 0, 1.5f);
    in[0].size = 1.0f;
    in[1].position = vec3(0.2f, 0, 0.2f);
    in[1].size = 1.0f;
    Decal out[2];
    u32 dropped = 9;
    ASSERT_EQ(decal_place_on_heightfield(in, 2, out, 2, heights, 3, 3, 1.0f, 1.0f, &dropped), 2u);
    ASSERT_EQ(dropped, 0u);
    ASSERT_FLOAT_EQ(out[0].position.e[1], 1.0f, 1e-6);
    ASSERT_TRUE(out[0].normal.e[0] < -0.5f);
    ASSERT_FLOAT_EQ(out[0].normal.e[2], 0.0f, 1e-6);
    ASSERT_FLOAT_EQ(vec3_len(out[0].normal), 1.0f, 1e-5);
    /* the corner cell has no left neighbour: half the central slope */
    ASSERT_FLOAT_EQ(out[1].position.e[1], 0.0f, 1e-6);
    ASSERT_TRUE(out[1].normal.e[0] < 0.0f && out[1].normal.e[0] > out[0].normal.e[0]);
}

/* Decals beyond the output capacity, with a non-positive size or a
 * non-finite position count as dropped; the output keeps input order. */
TEST(decal_capacity_and_bad_decals_are_dropped) {
    f32 heights[4] = {1, 1, 1, 1};
    Decal in[5];
    memset(in, 0, sizeof(in));
    for (u32 i = 0; i < 5u; i++) {
        in[i].position = vec3(0.5f, 0, 0.5f);
        in[i].size = 1.0f;
        in[i].material = i;
    }
    in[1].size = 0.0f;
    in[2].position.e[0] = NAN;
    Decal out[2];
    u32 dropped = 0;
    ASSERT_EQ(decal_place_on_heightfield(in, 5, out, 2, heights, 2, 2, 1.0f, 1.0f, &dropped), 2u);
    ASSERT_EQ(dropped, 3u);
    ASSERT_EQ(out[0].material, 0u);
    ASSERT_EQ(out[1].material, 3u);
}

/* Invalid grids or scales place nothing and report zero drops. */
TEST(decal_rejects_bad_heightfields) {
    f32 heights[4] = {1, 1, 1, 1};
    Decal in;
    memset(&in, 0, sizeof(in));
    in.position = vec3(0.5f, 0, 0.5f);
    in.size = 1.0f;
    Decal out;
    u32 dropped = 7;
    ASSERT_EQ(decal_place_on_heightfield(&in, 1, &out, 1, heights, 0, 2, 1.0f, 1.0f, &dropped), 0u);
    ASSERT_EQ(dropped, 0u);
    ASSERT_EQ(decal_place_on_heightfield(&in, 1, &out, 1, heights, 2, 2, 0.0f, 1.0f, &dropped), 0u);
    ASSERT_EQ(decal_place_on_heightfield(&in, 1, &out, 1, heights, 2, 2, 1.0f, NAN, &dropped), 0u);
    ASSERT_EQ(decal_place_on_heightfield(&in, 1, &out, 1, NULL, 2, 2, 1.0f, 1.0f, &dropped), 0u);
    ASSERT_EQ(decal_place_on_heightfield(&in, 1, NULL, 1, heights, 2, 2, 1.0f, 1.0f, &dropped), 0u);
    ASSERT_EQ(decal_place_on_heightfield(&in, 1, &out, 1, heights, 2, 2, 1.0f, 1.0f, NULL), 1u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(decal_snaps_to_height_and_drops_outside);
    RUN_TEST(decal_normal_follows_the_slope);
    RUN_TEST(decal_capacity_and_bad_decals_are_dropped);
    RUN_TEST(decal_rejects_bad_heightfields);
TEST_MAIN_END()
