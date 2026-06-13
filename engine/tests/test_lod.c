#include "test_framework.h"
#include <renderer/lod.h>

#define EPS 1e-5f

/* Helper: create a simple LOD group with known thresholds */
static LODGroup make_test_group(u32 levels, f32 base_dist) {
    LODGroup g;
    memset(&g, 0, sizeof(g));
    g.level_count = levels;
    g.bounding_radius = 1.0f;
    for (u32 i = 0; i < levels; i++) {
        f32 t = base_dist * (f32)(1u << i);
        g.thresholds[i] = t;
        g.thresholds_sq[i] = t * t;
        g.vertex_counts[i] = 1000u / (1u + i);
    }
    return g;
}

/* ---- Init/Shutdown ---- */

TEST(lod_init_defaults) {
    LODSystem sys;
    lod_init(&sys);
    ASSERT_EQ(sys.count, 0u);
    ASSERT_FLOAT_EQ(sys.bias, 0.0f, EPS);
    ASSERT_FALSE(sys.use_screen_size);
    lod_shutdown(&sys);
}

/* ---- Registration ---- */

TEST(lod_register_entity) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 1, &g);

    ASSERT_EQ(sys.count, 1u);
    lod_shutdown(&sys);
}

TEST(lod_unregister_entity) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 1, &g);
    lod_register(&sys, 2, &g);
    ASSERT_EQ(sys.count, 2u);

    lod_unregister(&sys, 1);
    ASSERT_EQ(sys.count, 1u);

    lod_shutdown(&sys);
}

/* ---- Distance-based LOD selection ---- */

TEST(lod_select_close_returns_lod0) {
    LODSystem sys;
    lod_init(&sys);

    /* thresholds: LOD0 < 10, LOD1 < 20, LOD2 < 40, LOD3 >= 40 */
    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    Vec3 obj_pos = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam_close = vec3(5.0f, 0.0f, 0.0f); /* distance = 5 < 10 */
    u32 level = lod_select(&sys, 0, obj_pos, cam_close, 1.0f);
    ASSERT_EQ(level, 0u);

    lod_shutdown(&sys);
}

TEST(lod_select_far_returns_lod3) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    Vec3 obj_pos = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam_far = vec3(100.0f, 0.0f, 0.0f); /* distance = 100 > 40 */
    u32 level = lod_select(&sys, 0, obj_pos, cam_far, 1.0f);
    ASSERT_EQ(level, 3u);

    lod_shutdown(&sys);
}

TEST(lod_select_mid_returns_lod1) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    Vec3 obj_pos = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam_mid = vec3(15.0f, 0.0f, 0.0f); /* distance = 15, threshold[0]=10, threshold[1]=20 */
    u32 level = lod_select(&sys, 0, obj_pos, cam_mid, 1.0f);
    ASSERT_EQ(level, 1u);

    lod_shutdown(&sys);
}

/* ---- Bias effect ---- */

TEST(lod_bias_positive_lowers_quality) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);
    /* Distance 8: normally LOD0 (< 10) */
    Vec3 cam = vec3(8.0f, 0.0f, 0.0f);

    u32 level_no_bias = lod_select(&sys, 0, obj, cam, 1.0f);
    ASSERT_EQ(level_no_bias, 0u);

    /* With large positive bias, effective distance increases */
    lod_set_bias(&sys, 1.0f);  /* effective_dist = 8 * (1+1) = 16 > 10 => LOD1 */
    /* Reset current level to 0 so hysteresis doesn't block */
    sys.current_levels[0] = 0;
    u32 level_biased = lod_select(&sys, 0, obj, cam, 1.0f);
    /* Positive bias should select a coarser level */
    ASSERT_TRUE(level_biased > 0u);

    lod_shutdown(&sys);
}

/* ---- Hysteresis prevents thrashing ---- */

TEST(lod_hysteresis_prevents_thrashing) {
    LODSystem sys;
    lod_init(&sys);

    /* thresholds[0] = 10. Hysteresis = 10% */
    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);

    /* First: move far to get LOD1 */
    Vec3 cam_far = vec3(15.0f, 0.0f, 0.0f);
    lod_select(&sys, 0, obj, cam_far, 1.0f);
    u32 level_far = lod_get_level(&sys, 0);
    ASSERT_EQ(level_far, 1u);

    /* Now move just barely within threshold[0]=10 but within hysteresis band.
     * Hysteresis for upgrade: effective_dist must be < threshold * (1 - 0.1) = 9.0
     * Distance 9.5 is inside [9.0, 10.0] -> should stay at LOD1 */
    Vec3 cam_borderline = vec3(9.5f, 0.0f, 0.0f);
    lod_select(&sys, 0, obj, cam_borderline, 1.0f);
    u32 level_border = lod_get_level(&sys, 0);
    ASSERT_EQ(level_border, 1u); /* should NOT switch due to hysteresis */

    /* Move well within threshold -> should upgrade to LOD0 */
    Vec3 cam_close = vec3(5.0f, 0.0f, 0.0f);
    lod_select(&sys, 0, obj, cam_close, 1.0f);
    u32 level_close = lod_get_level(&sys, 0);
    ASSERT_EQ(level_close, 0u);

    lod_shutdown(&sys);
}

/* ---- Auto thresholds ---- */

TEST(lod_group_auto_thresholds) {
    LODGroup g;
    memset(&g, 0, sizeof(g));
    g.level_count = 4;
    lod_group_set_auto_thresholds(&g, 10.0f);
    ASSERT_FLOAT_EQ(g.thresholds[0], 10.0f, EPS);
    ASSERT_FLOAT_EQ(g.thresholds[1], 20.0f, EPS);
    ASSERT_FLOAT_EQ(g.thresholds[2], 40.0f, EPS);
    ASSERT_FLOAT_EQ(g.thresholds[3], 80.0f, EPS);
}

/* ---- Edge Cases ---- */

TEST(lod_select_zero_distance) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    /* Camera at same position as object */
    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam = vec3(0.0f, 0.0f, 0.0f);
    u32 level = lod_select(&sys, 0, obj, cam, 1.0f);
    ASSERT_EQ(level, 0u); /* Should be highest quality */

    lod_shutdown(&sys);
}

TEST(lod_select_unregistered_entity) {
    LODSystem sys;
    lod_init(&sys);

    /* Try to select LOD for entity that was never registered */
    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam = vec3(5.0f, 0.0f, 0.0f);
    u32 level = lod_select(&sys, 999, obj, cam, 1.0f);
    ASSERT_EQ(level, 0u); /* Should return 0 safely */

    lod_shutdown(&sys);
}

TEST(lod_single_level_group) {
    LODSystem sys;
    lod_init(&sys);

    /* Group with only 1 level */
    LODGroup g;
    memset(&g, 0, sizeof(g));
    g.level_count = 1;
    g.thresholds[0] = 100.0f;
    g.thresholds_sq[0] = 100.0f * 100.0f;
    g.vertex_counts[0] = 1000;
    lod_register(&sys, 0, &g);

    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam = vec3(50.0f, 0.0f, 0.0f);
    u32 level = lod_select(&sys, 0, obj, cam, 1.0f);
    ASSERT_EQ(level, 0u); /* Only one level available */

    lod_shutdown(&sys);
}

TEST(lod_negative_bias) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);
    /* Distance 25: normally LOD2 (thresholds: 10, 20, 40) */
    Vec3 cam = vec3(25.0f, 0.0f, 0.0f);

    u32 level_no_bias = lod_select(&sys, 0, obj, cam, 1.0f);
    ASSERT_EQ(level_no_bias, 2u);

    /* With negative bias, effective distance decreases -> better quality */
    lod_set_bias(&sys, -0.5f);  /* effective_dist = 25 * 0.5 = 12.5 -> LOD1 */
    sys.current_levels[0] = 0; /* Reset to avoid hysteresis */
    u32 level_biased = lod_select(&sys, 0, obj, cam, 1.0f);
    ASSERT_TRUE(level_biased <= 1u);

    lod_shutdown(&sys);
}

TEST(lod_get_mesh_unregistered) {
    LODSystem sys;
    lod_init(&sys);

    LODMesh m = lod_get_mesh(&sys, 999);
    ASSERT_EQ(m.vertex_count, 0u);

    lod_shutdown(&sys);
}

TEST(lod_select_very_large_distance) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    /* Very large distance - should return highest LOD level */
    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam = vec3(1e6f, 0.0f, 0.0f);
    u32 level = lod_select(&sys, 0, obj, cam, 1.0f);
    ASSERT_EQ(level, 3u); /* Should be maximum level */

    lod_shutdown(&sys);
}

TEST(lod_zero_level_count_group) {
    LODSystem sys;
    lod_init(&sys);

    /* Group with zero levels - edge case */
    LODGroup g;
    memset(&g, 0, sizeof(g));
    g.level_count = 0;
    lod_register(&sys, 0, &g);

    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam = vec3(5.0f, 0.0f, 0.0f);
    u32 level = lod_select(&sys, 0, obj, cam, 1.0f);
    /* Zero levels - implementation-defined, just verify no crash */
    (void)level;
    ASSERT_TRUE(true);

    lod_shutdown(&sys);
}

TEST(lod_register_many_entities) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);

    /* Register many entities */
    for (u32 i = 0; i < 100; i++) {
        lod_register(&sys, i, &g);
    }

    ASSERT_EQ(sys.count, 100u);

    lod_shutdown(&sys);
}

TEST_MAIN_BEGIN()
    RUN_TEST(lod_init_defaults);
    RUN_TEST(lod_register_entity);
    RUN_TEST(lod_unregister_entity);
    RUN_TEST(lod_select_close_returns_lod0);
    RUN_TEST(lod_select_far_returns_lod3);
    RUN_TEST(lod_select_mid_returns_lod1);
    RUN_TEST(lod_bias_positive_lowers_quality);
    RUN_TEST(lod_hysteresis_prevents_thrashing);
    RUN_TEST(lod_group_auto_thresholds);
    /* Edge cases */
    RUN_TEST(lod_select_zero_distance);
    RUN_TEST(lod_select_unregistered_entity);
    RUN_TEST(lod_single_level_group);
    RUN_TEST(lod_negative_bias);
    RUN_TEST(lod_get_mesh_unregistered);
    RUN_TEST(lod_select_very_large_distance);
    RUN_TEST(lod_zero_level_count_group);
    RUN_TEST(lod_register_many_entities);
TEST_MAIN_END()
