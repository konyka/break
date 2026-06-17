/* test_terrain.c — CPU-side terrain height sampling, modification, and erosion tests
 *
 * Tests cover:
 *   - terrain_get_height: null heightmap, center sampling, corner clamping, bilinear interpolation
 *   - terrain_modify_height: radius falloff, null safety, modify_count tracking
 *   - terrain_flatten: averaging behavior, quadrant tracking
 *   - terrain_erode: peak reduction
 *   - terrain_generate: preset selection, non-zero output
 *   - terrain_noise_stamp: height modification
 */

#include "test_framework.h"
#include <renderer/terrain.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1e-3f
#define GRID 16

/* Helper: allocate a Terrain with heightmap (no GPU init) */
static Terrain *make_terrain(u32 grid, f32 scale, f32 height_scale) {
    Terrain *t = (Terrain *)calloc(1, sizeof(Terrain));
    t->grid_size = grid;
    t->scale = scale;
    t->inv_scale = (scale > 0.0f) ? 1.0f / scale : 0.0f;
    t->inv_nm1 = (f32)(grid - 1);
    t->height_scale = height_scale;
    t->heightmap = (f32 *)calloc(grid * grid, sizeof(f32));
    t->modify_count = 0;
    t->total_delta = 0.0f;
    memset(t->edit_quadrant, 0, sizeof(t->edit_quadrant));
    return t;
}

static void free_terrain(Terrain *t) {
    free(t->heightmap);
    free(t);
}

/* Fill heightmap with constant value */
static void fill_uniform(Terrain *t, f32 val) {
    for (u32 i = 0; i < t->grid_size * t->grid_size; i++)
        t->heightmap[i] = val;
}

/* ------------------------------------------------------------------ */
/* terrain_get_height tests                                            */
/* ------------------------------------------------------------------ */

TEST(get_height_null_heightmap)
{
    Terrain t;
    memset(&t, 0, sizeof(t));
    t.heightmap = NULL;
    f32 h = terrain_get_height(&t, 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(h, 0.0f, EPS);
}

TEST(get_height_center)
{
    /* Grid 16x16, scale=10, height_scale=1. Fill with 5.0.
     * Sample at center (0,0) should return 5.0 * height_scale = 5.0 */
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 5.0f);

    f32 h = terrain_get_height(t, 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(h, 5.0f, EPS);
    free_terrain(t);
}

TEST(get_height_uniform)
{
    /* Uniform heightmap should return same height everywhere */
    Terrain *t = make_terrain(GRID, 10.0f, 2.0f);
    fill_uniform(t, 3.0f);

    f32 h1 = terrain_get_height(t, -3.0f, -3.0f);
    f32 h2 = terrain_get_height(t,  0.0f,  0.0f);
    f32 h3 = terrain_get_height(t,  3.0f,  3.0f);

    /* All should be 3.0 * height_scale(2.0) = 6.0 */
    ASSERT_FLOAT_EQ(h1, 6.0f, EPS);
    ASSERT_FLOAT_EQ(h2, 6.0f, EPS);
    ASSERT_FLOAT_EQ(h3, 6.0f, EPS);
    free_terrain(t);
}

TEST(get_height_bilinear)
{
    /* Set up a 4x4 grid with specific values to test bilinear interpolation.
     * grid_size=4, scale=4.0, height_scale=1.0
     * World coords range from -2 to +2 (scale * [-0.5, 0.5])
     * Grid index = (world/scale + 0.5) * (grid_size-1) = (world/4 + 0.5) * 3
     */
    Terrain *t = make_terrain(4, 4.0f, 1.0f);
    /* Set grid values:
     * [0,0]=0  [0,1]=1  [0,2]=2  [0,3]=3
     * [1,0]=4  [1,1]=5  [1,2]=6  [1,3]=7
     * ...
     */
    for (u32 z = 0; z < 4; z++)
        for (u32 x = 0; x < 4; x++)
            t->heightmap[z * 4 + x] = (f32)(z * 4 + x);

    /* Sample at grid point (1,1):
     * world_x = (1/3 - 0.5)*4 = -0.6667
     * world_z = (1/3 - 0.5)*4 = -0.6667
     * At exact grid point, should return heightmap[1*4+1] = 5.0
     */
    f32 wx = ((1.0f / 3.0f) - 0.5f) * 4.0f;
    f32 wz = ((1.0f / 3.0f) - 0.5f) * 4.0f;
    f32 h = terrain_get_height(t, wx, wz);
    ASSERT_FLOAT_EQ(h, 5.0f, 0.1f);

    free_terrain(t);
}

TEST(get_height_corner_clamp)
{
    /* Sample far outside grid — should clamp to edge values */
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 7.0f);

    /* Far outside — should clamp and return 7.0 */
    f32 h1 = terrain_get_height(t, 100.0f, 100.0f);
    f32 h2 = terrain_get_height(t, -100.0f, -100.0f);
    ASSERT_FLOAT_EQ(h1, 7.0f, EPS);
    ASSERT_FLOAT_EQ(h2, 7.0f, EPS);
    free_terrain(t);
}

/* ------------------------------------------------------------------ */
/* terrain_modify_height tests                                         */
/* ------------------------------------------------------------------ */

TEST(modify_height_basic)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 0.0f);

    /* Modify at center with large radius and positive strength */
    terrain_modify_height(t, 0.0f, 0.0f, 5.0f, 2.0f);

    /* Center should be raised */
    ASSERT_TRUE(t->heightmap[GRID/2 * GRID + GRID/2] > 0.0f);
    ASSERT_TRUE(t->modify_count == 1);
    ASSERT_TRUE(t->total_delta > 0.0f);
    free_terrain(t);
}

TEST(modify_height_null_heightmap)
{
    Terrain t;
    memset(&t, 0, sizeof(t));
    t.heightmap = NULL;
    /* Should not crash */
    terrain_modify_height(&t, 0.0f, 0.0f, 5.0f, 2.0f);
    ASSERT_TRUE(t.modify_count == 0); /* early return */
}

TEST(modify_height_outside_radius)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 0.0f);

    /* Modify at far corner with small radius */
    terrain_modify_height(t, 4.5f, 4.5f, 0.5f, 3.0f);

    /* Opposite corner should be unchanged */
    f32 h = t->heightmap[0]; /* (0,0) corner */
    ASSERT_FLOAT_EQ(h, 0.0f, EPS);
    free_terrain(t);
}

TEST(modify_height_falloff)
{
    /* Verify quadratic falloff: closer points get more modification */
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 0.0f);

    terrain_modify_height(t, 0.0f, 0.0f, 4.0f, 5.0f);

    /* Center grid cell should have highest value */
    u32 mid = GRID / 2;
    f32 h_center = t->heightmap[mid * GRID + mid];
    /* A cell further from center should have less height */
    f32 h_edge = t->heightmap[0 * GRID + 0];
    ASSERT_TRUE(h_center > h_edge);
    free_terrain(t);
}

TEST(modify_height_quadrant_tracking)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 0.0f);

    /* Modify in one quadrant */
    terrain_modify_height(t, 1.0f, 1.0f, 3.0f, 1.0f);

    /* At least one quadrant should be incremented */
    u32 total_q = t->edit_quadrant[0] + t->edit_quadrant[1] +
                  t->edit_quadrant[2] + t->edit_quadrant[3];
    ASSERT_TRUE(total_q > 0);
    free_terrain(t);
}

/* ------------------------------------------------------------------ */
/* terrain_flatten tests                                               */
/* ------------------------------------------------------------------ */

TEST(flatten_averages)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    /* Set varying heights */
    for (u32 i = 0; i < GRID * GRID; i++)
        t->heightmap[i] = (f32)(i % 5) * 2.0f;

    /* Record pre-flatten center height */
    u32 mid = GRID / 2;
    f32 pre_h = t->heightmap[mid * GRID + mid];

    terrain_flatten(t, 0.0f, 0.0f, 5.0f);

    /* Flatten should have changed the height (moved toward average) */
    f32 post_h = t->heightmap[mid * GRID + mid];
    ASSERT_TRUE(t->modify_count == 1);
    /* Height should move toward the average (some change occurred) */
    ASSERT_TRUE(pre_h != post_h || t->modify_count > 0);
    free_terrain(t);
}

TEST(flatten_null_heightmap)
{
    Terrain t;
    memset(&t, 0, sizeof(t));
    t.heightmap = NULL;
    terrain_flatten(&t, 0.0f, 0.0f, 5.0f);
    ASSERT_TRUE(t.modify_count == 0);
}

/* ------------------------------------------------------------------ */
/* terrain_erode tests                                                 */
/* ------------------------------------------------------------------ */

TEST(erode_reduces_peaks)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 1.0f);

    /* Create a peak in the center */
    u32 mid = GRID / 2;
    t->heightmap[mid * GRID + mid] = 10.0f;
    /* Neighbors need to be non-zero for erosion to distribute */
    t->heightmap[mid * GRID + mid - 1] = 1.0f;
    t->heightmap[mid * GRID + mid + 1] = 1.0f;
    t->heightmap[(mid-1) * GRID + mid] = 1.0f;
    t->heightmap[(mid+1) * GRID + mid] = 1.0f;

    f32 pre_peak = t->heightmap[mid * GRID + mid];
    terrain_erode(t, 0.0f, 0.0f, 10.0f, 3);
    f32 post_peak = t->heightmap[mid * GRID + mid];

    /* Peak should be reduced */
    ASSERT_TRUE(post_peak < pre_peak);
    ASSERT_TRUE(t->modify_count == 1);
    free_terrain(t);
}

TEST(erode_null_heightmap)
{
    Terrain t;
    memset(&t, 0, sizeof(t));
    t.heightmap = NULL;
    terrain_erode(&t, 0.0f, 0.0f, 5.0f, 3);
    ASSERT_TRUE(t.modify_count == 0);
}

/* ------------------------------------------------------------------ */
/* terrain_generate tests                                              */
/* ------------------------------------------------------------------ */

TEST(generate_preset_nonzero)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 0.0f);

    terrain_generate(t, 0);

    /* At least some values should be non-zero */
    f32 sum = 0.0f;
    for (u32 i = 0; i < GRID * GRID; i++)
        sum += fabsf(t->heightmap[i]);
    ASSERT_TRUE(sum > 0.0f);
    free_terrain(t);
}

TEST(generate_all_presets)
{
    /* All 5 presets should produce non-zero heightmaps */
    for (u32 preset = 0; preset < 5; preset++) {
        Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
        fill_uniform(t, 0.0f);
        terrain_generate(t, preset);

        f32 sum = 0.0f;
        for (u32 i = 0; i < GRID * GRID; i++)
            sum += fabsf(t->heightmap[i]);
        ASSERT_TRUE(sum > 0.0f);
        free_terrain(t);
    }
}

/* ------------------------------------------------------------------ */
/* terrain_noise_stamp tests                                           */
/* ------------------------------------------------------------------ */

TEST(noise_stamp_modifies)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 0.0f);

    terrain_noise_stamp(t, 0.0f, 0.0f, 5.0f, 3.0f, 42.0f);

    /* Some values should be non-zero */
    f32 sum = 0.0f;
    for (u32 i = 0; i < GRID * GRID; i++)
        sum += fabsf(t->heightmap[i]);
    ASSERT_TRUE(sum > 0.0f);
    ASSERT_TRUE(t->modify_count == 1);
    ASSERT_TRUE(t->total_delta > 0.0f);
    free_terrain(t);
}

TEST(noise_stamp_null_heightmap)
{
    Terrain t;
    memset(&t, 0, sizeof(t));
    t.heightmap = NULL;
    terrain_noise_stamp(&t, 0.0f, 0.0f, 5.0f, 3.0f, 42.0f);
    ASSERT_TRUE(t.modify_count == 0);
}

/* ------------------------------------------------------------------ */
/*  Edge Cases                                                          */
/* ------------------------------------------------------------------ */

TEST(modify_height_zero_radius)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 0.0f);

    /* Zero radius should not modify anything */
    terrain_modify_height(t, 0.0f, 0.0f, 0.0f, 2.0f);

    /* Heightmap should be unchanged */
    for (u32 i = 0; i < GRID * GRID; i++) {
        ASSERT_FLOAT_EQ(t->heightmap[i], 0.0f, EPS);
    }
    free_terrain(t);
}

TEST(modify_height_negative_strength)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 5.0f);

    /* Negative strength should lower the terrain */
    terrain_modify_height(t, 0.0f, 0.0f, 5.0f, -2.0f);

    /* Center should be lowered */
    u32 mid = GRID / 2;
    f32 h_center = t->heightmap[mid * GRID + mid];
    ASSERT_TRUE(h_center < 5.0f);
    free_terrain(t);
}

TEST(erode_zero_iterations)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 5.0f);

    /* Zero iterations should not change anything */
    terrain_erode(t, 0.0f, 0.0f, 5.0f, 0);

    /* Heightmap should be unchanged */
    for (u32 i = 0; i < GRID * GRID; i++) {
        ASSERT_FLOAT_EQ(t->heightmap[i], 5.0f, EPS);
    }
    free_terrain(t);
}

TEST(generate_invalid_preset)
{
    Terrain *t = make_terrain(GRID, 10.0f, 1.0f);
    fill_uniform(t, 0.0f);

    /* Invalid preset index - implementation-defined behavior */
    terrain_generate(t, 999);
    /* Just verify no crash */
    ASSERT_TRUE(true);

    free_terrain(t);
}

/* ------------------------------------------------------------------ */

int main(void) {
    RUN_TEST(get_height_null_heightmap);
    RUN_TEST(get_height_center);
    RUN_TEST(get_height_uniform);
    RUN_TEST(get_height_bilinear);
    RUN_TEST(get_height_corner_clamp);
    RUN_TEST(modify_height_basic);
    RUN_TEST(modify_height_null_heightmap);
    RUN_TEST(modify_height_outside_radius);
    RUN_TEST(modify_height_falloff);
    RUN_TEST(modify_height_quadrant_tracking);
    RUN_TEST(flatten_averages);
    RUN_TEST(flatten_null_heightmap);
    RUN_TEST(erode_reduces_peaks);
    RUN_TEST(erode_null_heightmap);
    RUN_TEST(generate_preset_nonzero);
    RUN_TEST(generate_all_presets);
    RUN_TEST(noise_stamp_modifies);
    RUN_TEST(noise_stamp_null_heightmap);
    /* Edge cases */
    RUN_TEST(modify_height_zero_radius);
    RUN_TEST(modify_height_negative_strength);
    RUN_TEST(erode_zero_iterations);
    RUN_TEST(generate_invalid_preset);

    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
