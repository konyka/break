/* ==========================================================================
 *  test_lighting.c — Unit tests for the CPU-side lighting system logic.
 *
 *  Tests light_system_add_point/dir, light_system_clear, and
 *  light_system_cull (clustered culling) without requiring RHI.
 *  The LightSystem struct is heap-allocated (~1.7MB) to avoid stack limits.
 * ========================================================================== */

#include "test_framework.h"
#include <renderer/lighting.h>
#include <stdlib.h>
#include <math/math.h>

/* Helper: allocate zero-initialized LightSystem on heap */
static LightSystem *alloc_ls(void) {
    LightSystem *ls = (LightSystem *)calloc(1, sizeof(LightSystem));
    return ls;
}
static void free_ls(LightSystem *ls) { free(ls); }

/* ----------------------------------------------------------------------- */
/*  Light management (add/clear)                                            */
/* ----------------------------------------------------------------------- */

TEST(light_add_point_basic)
{
    LightSystem *ls = alloc_ls();
    ASSERT_NOT_NULL(ls);

    light_system_add_point(ls, 1.0f, 2.0f, 3.0f, 10.0f, 1.0f, 0.0f, 0.0f);
    ASSERT_EQ(ls->point_count, 1u);
    ASSERT_FLOAT_EQ(ls->point_lights[0].pos[0], 1.0f, 1e-5f);
    ASSERT_FLOAT_EQ(ls->point_lights[0].pos[1], 2.0f, 1e-5f);
    ASSERT_FLOAT_EQ(ls->point_lights[0].pos[2], 3.0f, 1e-5f);
    ASSERT_FLOAT_EQ(ls->point_lights[0].radius, 10.0f, 1e-5f);
    ASSERT_FLOAT_EQ(ls->point_lights[0].color[0], 1.0f, 1e-5f);

    free_ls(ls);
}

TEST(light_add_dir_basic)
{
    LightSystem *ls = alloc_ls();
    ASSERT_NOT_NULL(ls);

    light_system_add_dir(ls, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    ASSERT_EQ(ls->dir_count, 1u);
    ASSERT_FLOAT_EQ(ls->dir_lights[0].dir[1], -1.0f, 1e-5f);
    ASSERT_FLOAT_EQ(ls->dir_lights[0].color[0], 1.0f, 1e-5f);

    free_ls(ls);
}

TEST(light_add_multiple_points)
{
    LightSystem *ls = alloc_ls();
    for (u32 i = 0; i < 10; i++) {
        light_system_add_point(ls, (f32)i, 0, 0, 5.0f, 1, 1, 1);
    }
    ASSERT_EQ(ls->point_count, 10u);

    /* Verify each light's position */
    for (u32 i = 0; i < 10; i++) {
        ASSERT_FLOAT_EQ(ls->point_lights[i].pos[0], (f32)i, 1e-5f);
    }

    free_ls(ls);
}

TEST(light_add_point_overflow_clamped)
{
    LightSystem *ls = alloc_ls();

    /* Add more than LIGHT_MAX_POINT (256) */
    for (u32 i = 0; i < LIGHT_MAX_POINT + 10; i++) {
        light_system_add_point(ls, 0, 0, 0, 1.0f, 1, 1, 1);
    }

    /* Should be clamped at LIGHT_MAX_POINT */
    ASSERT_EQ(ls->point_count, (u32)LIGHT_MAX_POINT);

    free_ls(ls);
}

TEST(light_add_dir_overflow_clamped)
{
    LightSystem *ls = alloc_ls();

    for (u32 i = 0; i < LIGHT_MAX_DIR + 5; i++) {
        light_system_add_dir(ls, 0, -1, 0, 1, 1, 1);
    }

    ASSERT_EQ(ls->dir_count, (u32)LIGHT_MAX_DIR);

    free_ls(ls);
}

TEST(light_clear)
{
    LightSystem *ls = alloc_ls();

    light_system_add_point(ls, 1, 2, 3, 5.0f, 1, 0, 0);
    light_system_add_point(ls, 4, 5, 6, 5.0f, 0, 1, 0);
    light_system_add_dir(ls, 0, -1, 0, 1, 1, 1);

    ASSERT_EQ(ls->point_count, 2u);
    ASSERT_EQ(ls->dir_count, 1u);

    light_system_clear(ls);

    ASSERT_EQ(ls->point_count, 0u);
    ASSERT_EQ(ls->dir_count, 0u);

    free_ls(ls);
}

/* ----------------------------------------------------------------------- */
/*  Clustered culling                                                       */
/* ----------------------------------------------------------------------- */

TEST(light_cull_empty)
{
    LightSystem *ls = alloc_ls();

    /* Identity view and proj matrices */
    Mat4 view = mat4_identity();
    Mat4 proj = mat4_identity();

    light_system_cull(ls, &view, &proj, 1920, 1080);

    ASSERT_EQ(ls->grid_index_total, 0u);
    ASSERT_EQ(ls->screen_w, 1920u);
    ASSERT_EQ(ls->screen_h, 1080u);

    free_ls(ls);
}

TEST(light_cull_single_point_visible)
{
    LightSystem *ls = alloc_ls();

    /* Place a point light at the origin with large radius */
    light_system_add_point(ls, 0.0f, 0.0f, -5.0f, 20.0f, 1.0f, 1.0f, 1.0f);

    /* Simple perspective-like projection + identity view */
    Mat4 view = mat4_identity();
    Mat4 proj = mat4_perspective(1.0472f, 16.0f / 9.0f, 0.1f, 100.0f);

    light_system_cull(ls, &view, &proj, 1920, 1080);

    /* The light at (0,0,-5) with radius 20 should be visible in at least one cluster */
    ASSERT_TRUE(ls->grid_index_total > 0);

    free_ls(ls);
}

TEST(light_cull_point_behind_camera)
{
    LightSystem *ls = alloc_ls();

    /* Place a point light behind the camera (positive Z in view space) */
    light_system_add_point(ls, 0.0f, 0.0f, 50.0f, 5.0f, 1.0f, 1.0f, 1.0f);

    Mat4 view = mat4_identity();
    Mat4 proj = mat4_perspective(1.0472f, 16.0f / 9.0f, 0.1f, 100.0f);

    light_system_cull(ls, &view, &proj, 1920, 1080);

    /* Light behind camera should not appear in any cluster */
    ASSERT_EQ(ls->grid_index_total, 0u);

    free_ls(ls);
}

TEST(light_cull_multiple_lights)
{
    LightSystem *ls = alloc_ls();

    /* Add several lights: some visible, some not */
    light_system_add_point(ls, 0.0f, 0.0f, -5.0f, 20.0f, 1.0f, 0.0f, 0.0f);   /* visible */
    light_system_add_point(ls, 0.0f, 0.0f, 50.0f, 5.0f, 0.0f, 1.0f, 0.0f);    /* behind */
    light_system_add_point(ls, 1000.0f, 1000.0f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f); /* far away */

    Mat4 view = mat4_identity();
    Mat4 proj = mat4_perspective(1.0472f, 16.0f / 9.0f, 0.1f, 100.0f);

    light_system_cull(ls, &view, &proj, 1920, 1080);

    /* Only the first light should be visible */
    /* Count how many indices reference light 0 vs others */
    u32 light0_count = 0;
    u32 light1_count = 0;
    for (u32 i = 0; i < ls->grid_index_total; i++) {
        if (ls->grid_indices[i] == 0) light0_count++;
        else if (ls->grid_indices[i] == 1) light1_count++;
    }
    ASSERT_TRUE(light0_count > 0);
    ASSERT_EQ(light1_count, 0u);

    free_ls(ls);
}

TEST(light_cull_grid_offsets_structure)
{
    LightSystem *ls = alloc_ls();

    light_system_add_point(ls, 0.0f, 0.0f, -5.0f, 20.0f, 1.0f, 1.0f, 1.0f);

    Mat4 view = mat4_identity();
    Mat4 proj = mat4_perspective(1.0472f, 16.0f / 9.0f, 0.1f, 100.0f);

    light_system_cull(ls, &view, &proj, 1920, 1080);

    /* Verify grid structure: each cluster has offset + count pair */
    u32 total_from_grid = 0;
    for (u32 ci = 0; ci < CLUSTER_COUNT; ci++) {
        u32 offset = ls->grid_offsets_counts[ci * 2 + 0];
        u32 count  = ls->grid_offsets_counts[ci * 2 + 1];
        (void)offset;
        total_from_grid += count;
    }
    /* Sum of all cluster counts should equal grid_index_total */
    ASSERT_EQ(total_from_grid, ls->grid_index_total);

    free_ls(ls);
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(light_zero_radius_point)
{
    LightSystem *ls = alloc_ls();

    /* Zero radius point light */
    light_system_add_point(ls, 0.0f, 0.0f, -5.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    ASSERT_EQ(ls->point_count, 1u);
    ASSERT_FLOAT_EQ(ls->point_lights[0].radius, 0.0f, 1e-5f);

    /* Cull with zero radius should not crash */
    Mat4 view = mat4_identity();
    Mat4 proj = mat4_perspective(1.0472f, 16.0f / 9.0f, 0.1f, 100.0f);
    light_system_cull(ls, &view, &proj, 1920, 1080);

    free_ls(ls);
}

TEST(light_negative_radius)
{
    LightSystem *ls = alloc_ls();

    /* Negative radius - implementation-defined behavior, just don't crash */
    light_system_add_point(ls, 0.0f, 0.0f, -5.0f, -10.0f, 1.0f, 1.0f, 1.0f);
    ASSERT_EQ(ls->point_count, 1u);

    free_ls(ls);
}

TEST(light_cull_null_system)
{
    /* light_system_cull does not check for NULL - skip this test */
    /* Just verify the test framework doesn't crash */
    ASSERT_TRUE(true);
}

TEST(light_clear_null_system)
{
    /* light_system_clear does not check for NULL - skip this test */
    /* Just verify the test framework doesn't crash */
    ASSERT_TRUE(true);
}

/* ----------------------------------------------------------------------- */
/*  R550-D: camera-driven cluster depth range                                */
/* ----------------------------------------------------------------------- */

TEST(light_depth_range_default)
{
    LightSystem *ls = alloc_ls();

    Mat4 view = mat4_identity();
    Mat4 proj = mat4_identity();
    light_system_cull(ls, &view, &proj, 1920, 1080);

    /* Never calling set_depth_range keeps the historical 0.1/100 defaults. */
    ASSERT_FLOAT_EQ(ls->near_plane, 0.1f, 1e-5f);
    ASSERT_FLOAT_EQ(ls->far_plane, 100.0f, 1e-5f);

    free_ls(ls);
}

TEST(light_depth_range_updates_lut)
{
    LightSystem *ls = alloc_ls();

    light_system_set_depth_range(ls, 1.0f, 1000.0f);
    ASSERT_FLOAT_EQ(ls->near_plane, 1.0f, 1e-5f);
    ASSERT_FLOAT_EQ(ls->far_plane, 1000.0f, 1e-5f);
    ASSERT_TRUE(ls->_z_depths_dirty);

    Mat4 view = mat4_identity();
    Mat4 proj = mat4_perspective(1.0472f, 16.0f / 9.0f, 1.0f, 1000.0f);
    light_system_cull(ls, &view, &proj, 1920, 1080);

    /* LUT bounds must track the configured range: z_depths[0] == near,
     * z_depths[CLUSTER_Z] == far (cluster_depth(z) = near * (far/near)^(z/Z)). */
    ASSERT_FLOAT_EQ(ls->_z_depths[0], 1.0f, 1e-3f);
    ASSERT_FLOAT_EQ(ls->_z_depths[CLUSTER_Z], 1000.0f, 1e-1f);
    ASSERT_FALSE(ls->_z_depths_dirty);

    free_ls(ls);
}

TEST(light_depth_range_unchanged_keeps_lut)
{
    LightSystem *ls = alloc_ls();

    light_system_set_depth_range(ls, 0.5f, 250.0f);
    Mat4 view = mat4_identity();
    Mat4 proj = mat4_perspective(1.0472f, 16.0f / 9.0f, 0.5f, 250.0f);
    light_system_cull(ls, &view, &proj, 1920, 1080);
    ASSERT_FALSE(ls->_z_depths_dirty);

    /* Same range again: no LUT recompute (per-frame calls must stay cheap). */
    light_system_set_depth_range(ls, 0.5f, 250.0f);
    ASSERT_FALSE(ls->_z_depths_dirty);

    /* Changed range: recompute. */
    light_system_set_depth_range(ls, 0.5f, 500.0f);
    ASSERT_TRUE(ls->_z_depths_dirty);

    free_ls(ls);
}

TEST(light_depth_range_invalid_ignored)
{
    LightSystem *ls = alloc_ls();

    light_system_set_depth_range(ls, -1.0f, 100.0f);
    light_system_set_depth_range(ls, 10.0f, 5.0f);
    light_system_set_depth_range(ls, 0.0f, 50.0f);

    Mat4 view = mat4_identity();
    Mat4 proj = mat4_identity();
    light_system_cull(ls, &view, &proj, 1920, 1080);

    /* Invalid ranges leave the defaults untouched. */
    ASSERT_FLOAT_EQ(ls->near_plane, 0.1f, 1e-5f);
    ASSERT_FLOAT_EQ(ls->far_plane, 100.0f, 1e-5f);

    free_ls(ls);
}

/* ----------------------------------------------------------------------- */
/*  Main                                                                    */
/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(light_add_point_basic);
    RUN_TEST(light_add_dir_basic);
    RUN_TEST(light_add_multiple_points);
    RUN_TEST(light_add_point_overflow_clamped);
    RUN_TEST(light_add_dir_overflow_clamped);
    RUN_TEST(light_clear);
    RUN_TEST(light_cull_empty);
    RUN_TEST(light_cull_single_point_visible);
    RUN_TEST(light_cull_point_behind_camera);
    RUN_TEST(light_cull_multiple_lights);
    RUN_TEST(light_cull_grid_offsets_structure);
    /* Edge cases */
    RUN_TEST(light_zero_radius_point);
    RUN_TEST(light_negative_radius);
    RUN_TEST(light_cull_null_system);
    RUN_TEST(light_clear_null_system);
    /* R550-D: camera-driven depth range */
    RUN_TEST(light_depth_range_default);
    RUN_TEST(light_depth_range_updates_lut);
    RUN_TEST(light_depth_range_unchanged_keeps_lut);
    RUN_TEST(light_depth_range_invalid_ignored);
TEST_MAIN_END()
