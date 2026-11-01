#include "test_framework.h"
#include <ai/break_ai.h>
#include <stdlib.h>

static f32 *grid(u32 w, u32 d, f32 fill) {
    f32 *h = (f32 *)calloc((size_t)w * d, sizeof(f32));
    if (!h) {
        return NULL;
    }
    for (u32 i = 0; i < w * d; i++) h[i] = fill;
    return h;
}

TEST(bake_connects_flat_ground_and_splits_a_wall) {
    f32 *flat = grid(64, 64, 0.0f);
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = flat;
    field.width = 64;
    field.depth = 64;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    BreakNavMesh *mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    ASSERT_TRUE(break_nav_same_component(mesh, vec3(2.5f, 0, 2.5f), vec3(60.5f, 0, 60.5f)));
    break_nav_mesh_destroy(mesh);

    for (u32 z = 0; z < 64; z++) flat[z * 64u + 32u] = 10.0f;
    field.heights = flat;
    mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    ASSERT_FALSE(break_nav_same_component(mesh, vec3(8.5f, 0, 8.5f), vec3(50.5f, 0, 8.5f)));
    break_nav_mesh_destroy(mesh);
    free(flat);
}

TEST(slope_threshold_is_inclusive) {
    f32 heights[2] = {0.0f, 1.0f};
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = heights;
    field.width = 2;
    field.depth = 1;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    BreakNavMesh *mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    ASSERT_TRUE(break_nav_same_component(mesh, vec3(0.5f, 0, 0.2f), vec3(1.5f, 0, 0.2f)));
    break_nav_mesh_destroy(mesh);
    heights[1] = 1.5f;
    mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    ASSERT_FALSE(break_nav_same_component(mesh, vec3(0.5f, 0, 0.2f), vec3(1.5f, 0, 0.2f)));
    break_nav_mesh_destroy(mesh);
}

TEST(bake_rejects_oversized_fields) {
    f32 one = 0.0f;
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = &one;
    field.width = 1025;
    field.depth = 1;
    field.cell = 1.0f;
    ASSERT_TRUE(break_nav_bake_heightfield(&field, 45.0f, 0.0f) == NULL);
    field.width = 0;
    ASSERT_TRUE(break_nav_bake_heightfield(&field, 45.0f, 0.0f) == NULL);
    field.width = 2;
    field.heights = NULL;
    ASSERT_TRUE(break_nav_bake_heightfield(&field, 45.0f, 0.0f) == NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(bake_connects_flat_ground_and_splits_a_wall);
    RUN_TEST(slope_threshold_is_inclusive);
    RUN_TEST(bake_rejects_oversized_fields);
TEST_MAIN_END()
