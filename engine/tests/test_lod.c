#include "test_framework.h"
#include <renderer/lod.h>
#include <renderer/lod_gen.h>
#include <math.h>
#include <stdlib.h>

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

TEST(lod_select_unregistered_when_group0_exists) {
    /* R260: with entity 0 registered at group index 0, an unregistered entity
     * (entity_to_group[]==0) must NOT alias entity 0's LOD group. Before the fix
     * the "group_idx >= count" guard passed (0 < 1) and returned entity 0's far
     * level, also corrupting current_levels[999]. */
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);

    Vec3 obj = vec3(0.0f, 0.0f, 0.0f);
    Vec3 cam_far = vec3(1000.0f, 0.0f, 0.0f); /* would pick the coarsest level */
    u32 level = lod_select(&sys, 999, obj, cam_far, 1.0f);
    ASSERT_EQ(level, 0u); /* unregistered -> safe default, not group 0's LOD3 */

    LODMesh m = lod_get_mesh(&sys, 999);
    ASSERT_EQ(m.vertex_count, 0u); /* not entity 0's mesh */

    lod_shutdown(&sys);
}

TEST(lod_unregister_unregistered_when_group0_exists) {
    /* R344: lod_unregister must reject unregistered entities that alias slot 0.
     * Before the fix, unregister(999) with entity 0 at group 0 would swap-remove
     * entity 0 and drop count to 0. */
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    lod_register(&sys, 0, &g);
    ASSERT_EQ(sys.count, 1u);

    lod_unregister(&sys, 999);
    ASSERT_EQ(sys.count, 1u);
    ASSERT_EQ(sys.groups[0].entity_id, 0u);
    ASSERT_EQ(lod_get_level(&sys, 0), 0u);

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

/* R293: lod_update_all must index current_levels[] by entity id (as documented
 * "per entity" in lod.h and as read back by lod_get_level/lod_get_mesh), NOT by
 * the dense group slot. With non-sequential entity ids the old slot-indexed
 * writes landed on the wrong entries and lod_get_level returned a stale level. */
TEST(lod_update_all_indexes_by_entity_not_slot) {
    LODSystem sys;
    lod_init(&sys);

    LODGroup g = make_test_group(4, 10.0f);
    /* Register with entity ids that differ from their registration slot. */
    lod_register(&sys, 5, &g);   /* slot 0, entity 5 */
    lod_register(&sys, 3, &g);   /* slot 1, entity 3 */

    /* positions[] parallel to group slots: slot0(entity5) far, slot1(entity3) near. */
    Vec3 positions[2];
    positions[0] = vec3(100.0f, 0.0f, 0.0f); /* dist²=10000 > 1600 → coarsest (3) */
    positions[1] = vec3(1.0f, 0.0f, 0.0f);   /* dist²=1   < 100  → finest   (0) */
    Vec3 cam = vec3(0.0f, 0.0f, 0.0f);

    lod_update_all(&sys, cam, 1.0f, positions, 2);

    /* Before the fix these read the never-updated current_levels[5]/[3] == 0. */
    ASSERT_EQ(lod_get_level(&sys, 5), 3u);
    ASSERT_EQ(lod_get_level(&sys, 3), 0u);

    lod_shutdown(&sys);
}

/* ---- Screen-space error selection (runtime mega LOD) ---- */

/* proj factor for fov=90deg, 1000px: 1000 / (2 * tan(45deg)) = 500 px per
 * world unit at distance 1. */
TEST(lod_screen_proj_factor_matches_formula) {
    f32 pf = lod_screen_proj_factor(1.5707963f, 1000.0f);
    ASSERT_FLOAT_EQ(pf, 500.0f, 0.01f);
}

TEST(lod_screen_error_picks_coarsest_within_threshold) {
    const f32 err[3] = { 0.0f, 0.01f, 0.04f };
    const f32 pf = 500.0f;
    /* d=1: lvl1 = 5px, lvl2 = 20px -> LOD0. */
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 1.0f, pf, 1.0f, 0), 0u);
    /* d=10: lvl1 = 0.5px (<=0.8), lvl2 = 2px -> LOD1. */
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 10.0f, pf, 1.0f, 0), 1u);
    /* d=100: lvl2 = 0.2px -> LOD2. */
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 100.0f, pf, 1.0f, 0), 2u);
    /* Exactly the formula: lvl1 crosses 0.8px (lower band edge) at d = 0.01*500/0.8 = 6.25. */
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 6.2f, pf, 1.0f, 0), 0u);
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 6.3f, pf, 1.0f, 0), 1u);
}

TEST(lod_screen_error_hysteresis_band_holds_level) {
    const f32 err[3] = { 0.0f, 0.01f, 0.04f };
    const f32 pf = 500.0f;
    /* lvl1 at 1px exactly at d=5. In-band distances (1px*0.8..1.2 -> d 4.17..6.25)
     * keep whatever level is current. */
    for (f32 d = 4.3f; d < 6.2f; d += 0.1f) {
        ASSERT_EQ(lod_select_by_screen_error(err, 3, d, pf, 1.0f, 0), 0u);
        ASSERT_EQ(lod_select_by_screen_error(err, 3, d, pf, 1.0f, 1), 1u);
    }
    /* Leaving the band switches. */
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 4.1f, pf, 1.0f, 1), 0u);
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 6.3f, pf, 1.0f, 0), 1u);
}

TEST(lod_screen_error_sweep_no_flicker) {
    /* Camera moves monotonically away then back with sub-step jitter; the
     * level sequence must be monotonic in each direction (no A-B-A). */
    const f32 err[3] = { 0.0f, 0.01f, 0.04f };
    const f32 pf = 500.0f;
    u32 cur = 0u, changes = 0u;
    for (int i = 0; i < 4000; i++) {
        f32 d = 1.0f + (f32)i * 0.05f + ((i & 1) ? 0.02f : -0.02f);
        u32 nl = lod_select_by_screen_error(err, 3, d, pf, 1.0f, cur);
        ASSERT_TRUE(nl >= cur);
        if (nl != cur) changes++;
        cur = nl;
    }
    ASSERT_EQ(cur, 2u);
    ASSERT_EQ(changes, 2u);
    changes = 0u;
    for (int i = 4000; i >= 0; i--) {
        f32 d = 1.0f + (f32)i * 0.05f + ((i & 1) ? 0.02f : -0.02f);
        u32 nl = lod_select_by_screen_error(err, 3, d, pf, 1.0f, cur);
        ASSERT_TRUE(nl <= cur);
        if (nl != cur) changes++;
        cur = nl;
    }
    ASSERT_EQ(cur, 0u);
    ASSERT_EQ(changes, 2u);
}

TEST(lod_screen_error_degenerate_inputs) {
    const f32 err[3] = { 0.0f, 0.01f, 0.04f };
    ASSERT_EQ(lod_select_by_screen_error(err, 1, 1000.0f, 500.0f, 1.0f, 0), 0u);
    ASSERT_EQ(lod_select_by_screen_error(NULL, 3, 1000.0f, 500.0f, 1.0f, 0), 0u);
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 1000.0f, 500.0f, 0.0f, 2), 0u);
    /* Camera inside the sphere -> dist clamps, LOD0. */
    ASSERT_EQ(lod_select_by_screen_error(err, 3, -5.0f, 500.0f, 1.0f, 2), 0u);
    /* current_level out of range clamps to the coarsest. */
    ASSERT_EQ(lod_select_by_screen_error(err, 3, 1000.0f, 500.0f, 1.0f, 9), 2u);
}

TEST(lod_select_screen_error_uses_sphere_surface_distance) {
    const f32 err[3] = { 0.0f, 0.01f, 0.04f };
    Vec3 cam = vec3(0.0f, 0.0f, 0.0f);
    /* center 106.25 away, radius 100 -> surface distance 6.25: same result as dist 6.3/6.2 band edge. */
    u32 a = lod_select_screen_error(err, 3, vec3(0.0f, 0.0f, -106.3f), 100.0f, cam,
                                    1.5707963f, 1000.0f, 1.0f, 0);
    u32 b = lod_select_screen_error(err, 3, vec3(0.0f, 0.0f, -106.2f), 100.0f, cam,
                                    1.5707963f, 1000.0f, 1.0f, 0);
    ASSERT_EQ(a, 1u);
    ASSERT_EQ(b, 0u);
}

/* ---- LOD generation ---- */

/* Bumpy sphere: deterministic displacement so simplification has real error. */
static void make_bumpy_sphere(u32 sectors, u32 rings, f32 **out_v, u32 *out_vc,
                              u32 **out_i, u32 *out_ic) {
    u32 vc = (rings + 1u) * (sectors + 1u);
    u32 ic = rings * sectors * 6u;
    f32 *v = (f32 *)malloc((usize)vc * 8u * sizeof(f32));
    u32 *idx = (u32 *)malloc((usize)ic * sizeof(u32));
    u32 k = 0;
    for (u32 ri = 0; ri <= rings; ri++) {
        f32 phi = (f32)ri / (f32)rings * 3.14159265f;
        for (u32 si = 0; si <= sectors; si++) {
            f32 th = (f32)si / (f32)sectors * 6.2831853f;
            f32 nx = sinf(phi) * cosf(th), ny = cosf(phi), nz = sinf(phi) * sinf(th);
            f32 r = 1.0f + 0.05f * sinf(7.0f * th) * sinf(5.0f * phi);
            f32 *p = &v[k++ * 8u];
            p[0] = nx * r; p[1] = ny * r; p[2] = nz * r;
            p[3] = nx; p[4] = ny; p[5] = nz;
            p[6] = (f32)si / (f32)sectors; p[7] = (f32)ri / (f32)rings;
        }
    }
    u32 n = 0;
    for (u32 ri = 0; ri < rings; ri++)
        for (u32 si = 0; si < sectors; si++) {
            u32 a = ri * (sectors + 1u) + si, b = a + sectors + 1u;
            idx[n++] = a; idx[n++] = b; idx[n++] = a + 1u;
            idx[n++] = a + 1u; idx[n++] = b; idx[n++] = b + 1u;
        }
    *out_v = v; *out_vc = vc; *out_i = idx; *out_ic = ic;
}

TEST(lod_generate_levels_bumpy_sphere) {
    f32 *v; u32 vc, ic; u32 *idx;
    make_bumpy_sphere(96, 64, &v, &vc, &idx, &ic);
    LodMeshLevels lv;
    lod_generate_levels(v, vc, 32u, idx, ic, LOD_GEN_MAX_LEVELS, &lv);
    ASSERT_EQ(lv.level_count, 3u);
    ASSERT_EQ(lv.index_count[0], ic);
    ASSERT_TRUE(lv.scale > 1.9f && lv.scale < 2.3f);
    for (u32 l = 1; l < lv.level_count; l++) {
        ASSERT_TRUE(lv.index_count[l] > 0u);
        ASSERT_EQ(lv.index_count[l] % 3u, 0u);
        ASSERT_TRUE((f32)lv.index_count[l] <= (f32)lv.index_count[l - 1] * LOD_GEN_STOP_RATIO);
        ASSERT_TRUE(lv.rel_error[l] >= lv.rel_error[l - 1]);
        ASSERT_TRUE(lv.rel_error[l] <= 0.05f + 1e-6f);
        for (u32 i = 0; i < lv.index_count[l]; i++) ASSERT_TRUE(lv.indices[l][i] < vc);
    }
    ASSERT_TRUE(lv.rel_error[1] > 0.0f);
    lod_mesh_levels_free(&lv);
    ASSERT_EQ(lv.level_count, 0u);
    free(v); free(idx);
}

TEST(lod_generate_levels_small_mesh_skipped) {
    f32 *v; u32 vc, ic; u32 *idx;
    make_bumpy_sphere(16, 12, &v, &vc, &idx, &ic); /* 384 tris < 512 */
    LodMeshLevels lv;
    lod_generate_levels(v, vc, 32u, idx, ic, LOD_GEN_MAX_LEVELS, &lv);
    ASSERT_EQ(lv.level_count, 1u);
    ASSERT_TRUE(lv.indices[1] == NULL);
    lod_mesh_levels_free(&lv);
    free(v); free(idx);
}

TEST(lod_generate_levels_rejects_bad_indices) {
    f32 *v; u32 vc, ic; u32 *idx;
    make_bumpy_sphere(64, 32, &v, &vc, &idx, &ic);
    idx[5] = vc + 3u;
    LodMeshLevels lv;
    lod_generate_levels(v, vc, 32u, idx, ic, LOD_GEN_MAX_LEVELS, &lv);
    ASSERT_EQ(lv.level_count, 1u);
    lod_mesh_levels_free(&lv);
    /* index_count not a multiple of 3 */
    idx[5] = 0u;
    lod_generate_levels(v, vc, 32u, idx, ic - 1u, LOD_GEN_MAX_LEVELS, &lv);
    ASSERT_EQ(lv.level_count, 1u);
    lod_mesh_levels_free(&lv);
    /* max_levels = 1 -> nothing generated */
    lod_generate_levels(v, vc, 32u, idx, ic, 1u, &lv);
    ASSERT_EQ(lv.level_count, 1u);
    lod_mesh_levels_free(&lv);
    free(v); free(idx);
}

/* ---- Bake-table validator ---- */

/* Two nodes: node0 has 2 levels over verts [0,4), node1 one level over [4,8). */
static u32 g_bv_idx[] = { 0,1,2, 0,2,3,   0,1,2,   4,5,6, 4,6,7 };
static u32 g_bv_cmds[3 * 5] = {
    6, 1, 0, 0, 0,
    3, 1, 6, 0, 0,
    6, 1, 9, 0, 0,
};
static const u32 g_bv_base[2]  = { 0, 2 };
static const u8  g_bv_lc[2]    = { 2, 1 };
static const u32 g_bv_vbase[2] = { 0, 4 };
static const u32 g_bv_vcnt[2]  = { 4, 4 };
static const u32 g_bv_cnode[3] = { 0, 0, 1 };
static const u8  g_bv_clvl[3]  = { 0, 1, 0 };

static bool bv_run(char *err) {
    return lod_bake_validate(g_bv_cmds, 3, g_bv_idx, 15, 8, g_bv_base, g_bv_lc,
                             g_bv_vbase, g_bv_vcnt, 2, g_bv_cnode, g_bv_clvl, err, 256);
}

TEST(lod_bake_validate_accepts_consistent_tables) {
    char err[256] = {0};
    ASSERT_TRUE(bv_run(err));
}

TEST(lod_bake_validate_catches_errors) {
    char err[256];
    /* vertex_offset != 0 (the R687 double-offset class). */
    g_bv_cmds[2 * 5 + 3] = 4;
    ASSERT_FALSE(bv_run(err));
    g_bv_cmds[2 * 5 + 3] = 0;
    /* index range past the end. */
    g_bv_cmds[2 * 5 + 2] = 12;
    ASSERT_FALSE(bv_run(err));
    g_bv_cmds[2 * 5 + 2] = 9;
    /* index referencing another node's vertices. */
    g_bv_idx[7] = 5;
    ASSERT_FALSE(bv_run(err));
    g_bv_idx[7] = 1;
    /* index beyond the vertex buffer. */
    g_bv_idx[14] = 8;
    ASSERT_FALSE(bv_run(err));
    g_bv_idx[14] = 7;
    ASSERT_TRUE(bv_run(err));
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
    RUN_TEST(lod_select_unregistered_when_group0_exists);
    RUN_TEST(lod_unregister_unregistered_when_group0_exists);
    RUN_TEST(lod_single_level_group);
    RUN_TEST(lod_negative_bias);
    RUN_TEST(lod_get_mesh_unregistered);
    RUN_TEST(lod_select_very_large_distance);
    RUN_TEST(lod_zero_level_count_group);
    RUN_TEST(lod_register_many_entities);
    RUN_TEST(lod_update_all_indexes_by_entity_not_slot);
    /* Runtime mega LOD: screen-error selection, generation, bake tables */
    RUN_TEST(lod_screen_proj_factor_matches_formula);
    RUN_TEST(lod_screen_error_picks_coarsest_within_threshold);
    RUN_TEST(lod_screen_error_hysteresis_band_holds_level);
    RUN_TEST(lod_screen_error_sweep_no_flicker);
    RUN_TEST(lod_screen_error_degenerate_inputs);
    RUN_TEST(lod_select_screen_error_uses_sphere_surface_distance);
    RUN_TEST(lod_generate_levels_bumpy_sphere);
    RUN_TEST(lod_generate_levels_small_mesh_skipped);
    RUN_TEST(lod_generate_levels_rejects_bad_indices);
    RUN_TEST(lod_bake_validate_accepts_consistent_tables);
    RUN_TEST(lod_bake_validate_catches_errors);
TEST_MAIN_END()
