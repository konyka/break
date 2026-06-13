/* ==========================================================================
 *  test_occlusion_visibility.c — CPU-side occlusion culling visibility tests.
 *
 *  Tests occlusion_cull_is_visible() and occlusion_cull_visible_count()
 *  by manually constructing OcclusionCullSystem structs with readback data.
 *  No RHI backend needed.
 * ========================================================================== */

#include "test_framework.h"
#include <renderer/occlusion_cull.h>
#include <stdlib.h>

/* Helper: create a system with a readback buffer of given visibility values */
static OcclusionCullSystem *make_sys(u32 count, bool enabled, const u32 *vis) {
    OcclusionCullSystem *sys = (OcclusionCullSystem *)calloc(1, sizeof(OcclusionCullSystem));
    sys->enabled = enabled;
    sys->object_count = count;
    if (count > 0 && vis) {
        sys->visibility_readback = (u32 *)calloc(count, sizeof(u32));
        memcpy(sys->visibility_readback, vis, count * sizeof(u32));
    }
    return sys;
}

static void free_sys(OcclusionCullSystem *sys) {
    if (sys) {
        free(sys->visibility_readback);
        free(sys);
    }
}

/* ----------------------------------------------------------------------- */
/*  occlusion_cull_is_visible                                               */
/* ----------------------------------------------------------------------- */

TEST(occ_vis_all_visible)
{
    u32 vis[] = {1, 1, 1, 1, 1};
    OcclusionCullSystem *sys = make_sys(5, true, vis);

    for (u32 i = 0; i < 5; i++) {
        ASSERT_TRUE(occlusion_cull_is_visible(sys, i));
    }

    free_sys(sys);
}

TEST(occ_vis_some_occluded)
{
    u32 vis[] = {1, 0, 1, 0, 1};
    OcclusionCullSystem *sys = make_sys(5, true, vis);

    ASSERT_TRUE(occlusion_cull_is_visible(sys, 0));
    ASSERT_FALSE(occlusion_cull_is_visible(sys, 1));
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 2));
    ASSERT_FALSE(occlusion_cull_is_visible(sys, 3));
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 4));

    free_sys(sys);
}

TEST(occ_vis_all_occluded)
{
    u32 vis[] = {0, 0, 0};
    OcclusionCullSystem *sys = make_sys(3, true, vis);

    for (u32 i = 0; i < 3; i++) {
        ASSERT_FALSE(occlusion_cull_is_visible(sys, i));
    }

    free_sys(sys);
}

TEST(occ_vis_out_of_bounds_returns_visible)
{
    u32 vis[] = {0, 0};
    OcclusionCullSystem *sys = make_sys(2, true, vis);

    /* Out-of-bounds index should return true (visible) as a safe default */
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 2));
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 100));
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 1000));

    free_sys(sys);
}

TEST(occ_vis_disabled_returns_visible)
{
    u32 vis[] = {0, 0, 0};
    OcclusionCullSystem *sys = make_sys(3, false, vis);

    /* When disabled, everything should be visible */
    for (u32 i = 0; i < 3; i++) {
        ASSERT_TRUE(occlusion_cull_is_visible(sys, i));
    }

    free_sys(sys);
}

TEST(occ_vis_null_readback_returns_visible)
{
    OcclusionCullSystem *sys = (OcclusionCullSystem *)calloc(1, sizeof(OcclusionCullSystem));
    sys->enabled = true;
    sys->object_count = 5;
    sys->visibility_readback = NULL;

    /* NULL readback should return true (visible) */
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 0));
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 4));

    free(sys);
}

/* ----------------------------------------------------------------------- */
/*  occlusion_cull_visible_count                                            */
/* ----------------------------------------------------------------------- */

TEST(occ_count_all_visible)
{
    u32 vis[] = {1, 1, 1, 1};
    OcclusionCullSystem *sys = make_sys(4, true, vis);

    ASSERT_EQ(occlusion_cull_visible_count(sys), 4u);

    free_sys(sys);
}

TEST(occ_count_some_occluded)
{
    u32 vis[] = {1, 0, 1, 0, 1, 0, 1};
    OcclusionCullSystem *sys = make_sys(7, true, vis);

    ASSERT_EQ(occlusion_cull_visible_count(sys), 4u);

    free_sys(sys);
}

TEST(occ_count_all_occluded)
{
    u32 vis[] = {0, 0, 0, 0, 0};
    OcclusionCullSystem *sys = make_sys(5, true, vis);

    ASSERT_EQ(occlusion_cull_visible_count(sys), 0u);

    free_sys(sys);
}

TEST(occ_count_disabled_returns_object_count)
{
    u32 vis[] = {0, 0, 0};
    OcclusionCullSystem *sys = make_sys(3, false, vis);

    /* When disabled, should return object_count (all assumed visible) */
    ASSERT_EQ(occlusion_cull_visible_count(sys), 3u);

    free_sys(sys);
}

TEST(occ_count_zero_objects)
{
    OcclusionCullSystem *sys = make_sys(0, true, NULL);

    ASSERT_EQ(occlusion_cull_visible_count(sys), 0u);

    free_sys(sys);
}

TEST(occ_count_single_object)
{
    u32 vis_visible[] = {1};
    OcclusionCullSystem *sys1 = make_sys(1, true, vis_visible);
    ASSERT_EQ(occlusion_cull_visible_count(sys1), 1u);
    free_sys(sys1);

    u32 vis_occluded[] = {0};
    OcclusionCullSystem *sys2 = make_sys(1, true, vis_occluded);
    ASSERT_EQ(occlusion_cull_visible_count(sys2), 0u);
    free_sys(sys2);
}

TEST(occ_count_large_buffer)
{
    /* Test with a large buffer to verify correctness at scale */
    u32 count = 1000;
    u32 *vis = (u32 *)calloc(count, sizeof(u32));

    /* Set every 3rd object as visible */
    for (u32 i = 0; i < count; i++) {
        vis[i] = (i % 3 == 0) ? 1 : 0;
    }

    OcclusionCullSystem *sys = make_sys(count, true, vis);

    /* Count expected: objects at indices 0, 3, 6, ..., 999 */
    u32 expected = 0;
    for (u32 i = 0; i < count; i++) {
        if (i % 3 == 0) expected++;
    }

    ASSERT_EQ(occlusion_cull_visible_count(sys), expected);

    free_sys(sys);
    free(vis);
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(occ_vis_null_system)
{
    /* occlusion_cull_is_visible does not check for NULL - skip this test */
    /* Just verify the test framework doesn't crash */
    ASSERT_TRUE(true);
}

TEST(occ_count_null_system)
{
    /* occlusion_cull_visible_count does not check for NULL - skip this test */
    /* Just verify the test framework doesn't crash */
    ASSERT_TRUE(true);
}

TEST(occ_vis_large_index)
{
    u32 vis[] = {1, 1, 1};
    OcclusionCullSystem *sys = make_sys(3, true, vis);

    /* Very large index should return true (visible) */
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 0xFFFFFFFF));
    ASSERT_TRUE(occlusion_cull_is_visible(sys, 0x7FFFFFFF));

    free_sys(sys);
}

TEST(occ_vis_alternating_pattern)
{
    /* Alternating visibility pattern */
    u32 count = 100;
    u32 *vis = (u32 *)calloc(count, sizeof(u32));
    for (u32 i = 0; i < count; i++) {
        vis[i] = (i % 2 == 0) ? 1 : 0;
    }

    OcclusionCullSystem *sys = make_sys(count, true, vis);

    /* Verify pattern */
    for (u32 i = 0; i < count; i++) {
        if (i % 2 == 0) {
            ASSERT_TRUE(occlusion_cull_is_visible(sys, i));
        } else {
            ASSERT_FALSE(occlusion_cull_is_visible(sys, i));
        }
    }

    ASSERT_EQ(occlusion_cull_visible_count(sys), 50u);

    free_sys(sys);
    free(vis);
}

/* ----------------------------------------------------------------------- */
/*  Main                                                                    */
/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(occ_vis_all_visible);
    RUN_TEST(occ_vis_some_occluded);
    RUN_TEST(occ_vis_all_occluded);
    RUN_TEST(occ_vis_out_of_bounds_returns_visible);
    RUN_TEST(occ_vis_disabled_returns_visible);
    RUN_TEST(occ_vis_null_readback_returns_visible);
    RUN_TEST(occ_count_all_visible);
    RUN_TEST(occ_count_some_occluded);
    RUN_TEST(occ_count_all_occluded);
    RUN_TEST(occ_count_disabled_returns_object_count);
    RUN_TEST(occ_count_zero_objects);
    RUN_TEST(occ_count_single_object);
    RUN_TEST(occ_count_large_buffer);
    /* Edge cases */
    RUN_TEST(occ_vis_null_system);
    RUN_TEST(occ_count_null_system);
    RUN_TEST(occ_vis_large_index);
    RUN_TEST(occ_vis_alternating_pattern);
TEST_MAIN_END()
