/* R434: CSM texel snapping tests.
 * Verifies that shadow_snap_lview_to_texel() quantizes the light view matrix
 * translation (e[0][3], e[1][3] — the light-space x/y offset, per the engine's
 * row-major view convention where row i of lview dotted with p gives the
 * light-space coordinate) to the shadow-map texel grid, so camera motion only
 * shifts a fixed world point's shadow position by whole texels. */
#include "test_framework.h"
#include <renderer/csm.h>
#include <math/math.h>
#include <math.h>

#define EPS 1e-5f

/* Build the cascade light view matrix the same way main.c does:
 * eye = center - light_dir * extent, left-handed lookat basis. */
static Mat4 build_lview(Vec3 center, Vec3 light_dir, f32 extent) {
    Vec3 eye = vec3_sub(center, vec3_scale(light_dir, extent));
    Vec3 up = vec3(0.0f, 1.0f, 0.0f);
    return mat4_lookat(eye, center, up);
}

/* Light-space x/y of a world point: row i of lview dotted with (p,1),
 * the engine's documented view-matrix semantics (see camera_view). */
static void light_xy(const Mat4 *lview, Vec3 p, f32 *lx, f32 *ly) {
    *lx = lview->e[0][0]*p.e[0] + lview->e[0][1]*p.e[1] + lview->e[0][2]*p.e[2] + lview->e[0][3];
    *ly = lview->e[1][0]*p.e[0] + lview->e[1][1]*p.e[1] + lview->e[1][2]*p.e[2] + lview->e[1][3];
}

/* Grid-aligned base view: rotation from the light direction (as main.c builds
 * it), translation set to exact texel multiples so frame deltas are exact.
 * A camera sliding along the light-right axis moves the x translation by
 * exactly -delta texels. */
static Mat4 base_lview(Vec3 light_dir, f32 extent, f32 texel) {
    Mat4 lv = build_lview(vec3(10.0f, 5.0f, -7.0f), light_dir, extent);
    lv.e[0][3] = 37.0f * texel;
    lv.e[1][3] = -11.0f * texel;
    return lv;
}

/* Sub-texel camera moves that stay within one texel cell must not move the
 * light-space position of a fixed world point (unsnapped matrices must drift). */
TEST(shadow_snap_stable_under_subtexel_camera_move) {
    Vec3 light_dir = vec3_normalize(vec3(0.3f, -1.0f, 0.2f));
    f32 extent = 50.0f;
    u32 size = 1024;
    f32 texel = 2.0f * extent / (f32)size;
    Vec3 point = vec3(12.3f, 1.0f, -5.5f);

    Mat4 lv0 = base_lview(light_dir, extent, texel);
    f32 ref_x, ref_y;
    light_xy(&lv0, point, &ref_x, &ref_y);

    const f32 deltas[] = { 0.31f, -0.42f, 0.17f };
    for (int i = 0; i < 3; i++) {
        Mat4 lv_raw = lv0;
        lv_raw.e[0][3] -= deltas[i] * texel; /* camera slid along light-right */
        Mat4 lv_snap = lv_raw;
        shadow_snap_lview_to_texel(&lv_snap, extent, size);

        f32 sx, sy, rx, ry;
        light_xy(&lv_snap, point, &sx, &sy);
        light_xy(&lv_raw, point, &rx, &ry);

        /* Snapped: fixed world point keeps the exact same light-space x/y. */
        ASSERT_FLOAT_EQ(sx, ref_x, EPS);
        ASSERT_FLOAT_EQ(sy, ref_y, EPS);

        /* Control: without snapping the position drifts by ~|delta| texels. */
        f32 drift_texels = fabsf(rx - ref_x) / texel;
        ASSERT_TRUE(drift_texels > 0.05f);
    }
}

/* Larger camera moves may cross texel cells, but snapped shifts must be whole
 * texels only; the unsnapped shift carries the sub-texel fraction. */
TEST(shadow_snap_shifts_only_whole_texels) {
    Vec3 light_dir = vec3_normalize(vec3(0.3f, -1.0f, 0.2f));
    f32 extent = 50.0f;
    u32 size = 1024;
    f32 texel = 2.0f * extent / (f32)size;
    Vec3 point = vec3(12.3f, 1.0f, -5.5f);

    Mat4 lv0 = base_lview(light_dir, extent, texel);
    f32 ref_x, ref_y;
    light_xy(&lv0, point, &ref_x, &ref_y);

    /* Fractional parts are all > 0.05 so the raw drift is visibly non-integer. */
    const f32 deltas[] = { 0.83f, -1.27f, 2.45f };
    for (int i = 0; i < 3; i++) {
        Mat4 lv = lv0;
        lv.e[0][3] -= deltas[i] * texel;
        shadow_snap_lview_to_texel(&lv, extent, size);
        f32 sx, sy;
        light_xy(&lv, point, &sx, &sy);

        f32 disp = (sx - ref_x) / texel;
        ASSERT_FLOAT_EQ(disp, roundf(disp), 1e-3f);       /* whole texels only */
        ASSERT_TRUE(fabsf(disp) <= ceilf(fabsf(deltas[i])) + 1e-3f);

        f32 raw_disp = deltas[i]; /* exact: base translation is grid-aligned */
        ASSERT_TRUE(fabsf(raw_disp - roundf(raw_disp)) > 0.05f);
    }
}

/* snap(snap(m)) == snap(m): second snap must not move the translation. */
TEST(shadow_snap_idempotent) {
    Vec3 light_dir = vec3_normalize(vec3(0.3f, -1.0f, 0.2f));
    f32 extent = 50.0f;
    u32 size = 1024;
    f32 texel = 2.0f * extent / (f32)size;
    Vec3 center = vec3(-33.7f, 12.1f, 48.9f);

    Mat4 lv = build_lview(center, light_dir, extent);
    shadow_snap_lview_to_texel(&lv, extent, size);
    f32 tx = lv.e[0][3], ty = lv.e[1][3], tz = lv.e[2][3];
    shadow_snap_lview_to_texel(&lv, extent, size);
    shadow_snap_lview_to_texel(&lv, extent, size);
    ASSERT_FLOAT_EQ(lv.e[0][3], tx, texel * 1e-3f);
    ASSERT_FLOAT_EQ(lv.e[1][3], ty, texel * 1e-3f);
    ASSERT_FLOAT_EQ(lv.e[2][3], tz, EPS); /* depth row untouched */
}

/* After snapping, the light-space x/y translation sits on the texel grid. */
TEST(shadow_snap_grid_aligned) {
    Vec3 light_dir = vec3_normalize(vec3(-0.6f, -0.8f, 0.35f));
    f32 extent = 75.0f;
    u32 size = 1024;
    f32 texel = 2.0f * extent / (f32)size;
    Vec3 center = vec3(123.45f, -6.7f, 8.91f);

    Mat4 lv = build_lview(center, light_dir, extent);
    shadow_snap_lview_to_texel(&lv, extent, size);
    f32 gx = lv.e[0][3] / texel, gy = lv.e[1][3] / texel;
    ASSERT_FLOAT_EQ(gx, roundf(gx), 1e-3f);
    ASSERT_FLOAT_EQ(gy, roundf(gy), 1e-3f);
}

/* Texel boundary +/-0.5: half rounds up deterministically and stays stable.
 * Uses power-of-two texel (2*64/1024 = 0.125) so boundary values are exact. */
TEST(shadow_snap_half_texel_boundary) {
    f32 extent = 64.0f;
    u32 size = 1024;
    f32 texel = 2.0f * extent / (f32)size; /* 0.125, exact */

    Mat4 lv = mat4_identity();
    lv.e[0][3] = (3.0f + 0.5f) * texel;  /* x at +0.5 boundary -> rounds to 4 */
    lv.e[1][3] = (7.0f - 0.5f) * texel;  /* y at -0.5 boundary -> rounds to 7 */
    shadow_snap_lview_to_texel(&lv, extent, size);
    ASSERT_FLOAT_EQ(lv.e[0][3], 4.0f * texel, EPS);
    ASSERT_FLOAT_EQ(lv.e[1][3], 7.0f * texel, EPS);
    /* Snapped boundary result is a fixed point. */
    shadow_snap_lview_to_texel(&lv, extent, size);
    ASSERT_FLOAT_EQ(lv.e[0][3], 4.0f * texel, EPS);
    ASSERT_FLOAT_EQ(lv.e[1][3], 7.0f * texel, EPS);
}

/* Degenerate inputs must leave the matrix untouched. */
TEST(shadow_snap_guard_degenerate) {
    Vec3 center = vec3(1.0f, 2.0f, 3.0f);
    Mat4 lv = build_lview(center, vec3_normalize(vec3(0.0f, -1.0f, 0.1f)), 10.0f);
    Mat4 orig = lv;
    shadow_snap_lview_to_texel(&lv, 0.0f, 1024);   /* zero extent */
    ASSERT_FLOAT_EQ(lv.e[0][3], orig.e[0][3], EPS);
    shadow_snap_lview_to_texel(&lv, -5.0f, 1024);  /* negative extent */
    ASSERT_FLOAT_EQ(lv.e[0][3], orig.e[0][3], EPS);
    shadow_snap_lview_to_texel(&lv, 10.0f, 0u);    /* zero map size */
    ASSERT_FLOAT_EQ(lv.e[0][3], orig.e[0][3], EPS);
}

TEST_MAIN_BEGIN()
    RUN_TEST(shadow_snap_stable_under_subtexel_camera_move);
    RUN_TEST(shadow_snap_shifts_only_whole_texels);
    RUN_TEST(shadow_snap_idempotent);
    RUN_TEST(shadow_snap_grid_aligned);
    RUN_TEST(shadow_snap_half_texel_boundary);
    RUN_TEST(shadow_snap_guard_degenerate);
TEST_MAIN_END()
