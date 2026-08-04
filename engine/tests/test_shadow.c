/* R434: CSM texel snapping tests.
 * Verifies that shadow_snap_lview_to_texel() quantizes the light view matrix
 * translation (e[3][0], e[3][1] — the light-space x/y offset, per the engine's
 * canonical column-major view convention (R438) where row i of lview dotted
 * with (p,1) gives the light-space coordinate) to the shadow-map texel grid,
 * so camera motion only shifts a fixed world point's shadow position by
 * whole texels. */
#include "test_framework.h"
#include <renderer/csm.h>
#include <math/math.h>
#include <math.h>

#define EPS 1e-5f

/* Build the cascade light view matrix via the exact production helper
 * (extracted from main.c into csm.h at R438). */
static Mat4 build_lview(Vec3 center, Vec3 light_dir, f32 extent) {
    return shadow_cascade_lview(center, light_dir, extent);
}

/* Light-space x/y of a world point: row i of lview dotted with (p,1),
 * the engine's documented view-matrix semantics (see camera_view).
 * R438 canonical layout: row i = (e[0][i], e[1][i], e[2][i], e[3][i]). */
static void light_xy(const Mat4 *lview, Vec3 p, f32 *lx, f32 *ly) {
    *lx = lview->e[0][0]*p.e[0] + lview->e[1][0]*p.e[1] + lview->e[2][0]*p.e[2] + lview->e[3][0];
    *ly = lview->e[0][1]*p.e[0] + lview->e[1][1]*p.e[1] + lview->e[2][1]*p.e[2] + lview->e[3][1];
}

/* Grid-aligned base view: rotation from the light direction (as main.c builds
 * it), translation set to exact texel multiples so frame deltas are exact.
 * A camera sliding along the light-right axis moves the x translation by
 * exactly -delta texels. */
static Mat4 base_lview(Vec3 light_dir, f32 extent, f32 texel) {
    Mat4 lv = build_lview(vec3(10.0f, 5.0f, -7.0f), light_dir, extent);
    lv.e[3][0] = 37.0f * texel;
    lv.e[3][1] = -11.0f * texel;
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
        lv_raw.e[3][0] -= deltas[i] * texel; /* camera slid along light-right */
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
        lv.e[3][0] -= deltas[i] * texel;
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
    f32 tx = lv.e[3][0], ty = lv.e[3][1], tz = lv.e[3][2];
    shadow_snap_lview_to_texel(&lv, extent, size);
    shadow_snap_lview_to_texel(&lv, extent, size);
    ASSERT_FLOAT_EQ(lv.e[3][0], tx, texel * 1e-3f);
    ASSERT_FLOAT_EQ(lv.e[3][1], ty, texel * 1e-3f);
    ASSERT_FLOAT_EQ(lv.e[3][2], tz, EPS); /* depth row untouched */
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
    f32 gx = lv.e[3][0] / texel, gy = lv.e[3][1] / texel;
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
    lv.e[3][0] = (3.0f + 0.5f) * texel;  /* x at +0.5 boundary -> rounds to 4 */
    lv.e[3][1] = (7.0f - 0.5f) * texel;  /* y at -0.5 boundary -> rounds to 7 */
    shadow_snap_lview_to_texel(&lv, extent, size);
    ASSERT_FLOAT_EQ(lv.e[3][0], 4.0f * texel, EPS);
    ASSERT_FLOAT_EQ(lv.e[3][1], 7.0f * texel, EPS);
    /* Snapped boundary result is a fixed point. */
    shadow_snap_lview_to_texel(&lv, extent, size);
    ASSERT_FLOAT_EQ(lv.e[3][0], 4.0f * texel, EPS);
    ASSERT_FLOAT_EQ(lv.e[3][1], 7.0f * texel, EPS);
}

/* Degenerate inputs must leave the matrix untouched. */
TEST(shadow_snap_guard_degenerate) {
    Vec3 center = vec3(1.0f, 2.0f, 3.0f);
    Mat4 lv = build_lview(center, vec3_normalize(vec3(0.0f, -1.0f, 0.1f)), 10.0f);
    Mat4 orig = lv;
    shadow_snap_lview_to_texel(&lv, 0.0f, 1024);   /* zero extent */
    ASSERT_FLOAT_EQ(lv.e[3][0], orig.e[3][0], EPS);
    shadow_snap_lview_to_texel(&lv, -5.0f, 1024);  /* negative extent */
    ASSERT_FLOAT_EQ(lv.e[3][0], orig.e[3][0], EPS);
    shadow_snap_lview_to_texel(&lv, 10.0f, 0u);    /* zero map size */
    ASSERT_FLOAT_EQ(lv.e[3][0], orig.e[3][0], EPS);
}

/* R438 characterization: the cascade box corners must fill the ±1 NDC cube
 * under cascade_vp, not collapse to a point. Builds the cascade light view
 * the same way main.c does (eye = center - light_dir*extent, left-handed
 * lookat basis, symmetric ortho of half-width `extent`, depth 0.1..2*extent).
 * NOTE: the task-statement shorthand "corners inside ±1" is not sufficient
 * on its own — the collapsed (broken) projection also lands inside the cube;
 * the spread assertions below are what actually fail on the broken layout. */
TEST(cascade_vp_corners_fill_unit_cube) {
    Vec3 light_dir = vec3_normalize(vec3(0.3f, -1.0f, 0.2f));
    Vec3 cam_pos = vec3(0.0f, 2.0f, 8.0f);
    Vec3 cam_fwd = vec3(0.0f, 0.0f, -1.0f);
    f32 zn = 0.1f, zf = 40.0f;
    f32 extent = zf - zn;
    Vec3 center = vec3_add(cam_pos, vec3_scale(cam_fwd, (zn + zf) * 0.5f));

    /* R438: exact production construction extracted to csm.h. */
    Mat4 lview = shadow_cascade_lview(center, light_dir, extent);
    Mat4 lproj = mat4_ortho(-extent, extent, -extent, extent, 0.1f, extent * 2.0f);
    Mat4 vp = mat4_mul_ortho_diag(lproj, lview); /* same composed path as main.c */

    /* Light-space axes: sign of s/u does not matter — both ± appear. */
    Vec3 f = light_dir;
    Vec3 s = vec3_normalize(vec3_cross(f, vec3(0.0f, 1.0f, 0.0f)));
    Vec3 u = vec3_cross(s, f);

    f32 min_x = 1e30f, max_x = -1e30f, min_y = 1e30f, max_y = -1e30f;
    f32 min_z = 1e30f, max_z = -1e30f;
    for (int i = 0; i < 8; i++) {
        Vec3 p = center;
        p = vec3_add(p, vec3_scale(s, (i & 1) ? extent : -extent));
        p = vec3_add(p, vec3_scale(u, (i & 2) ? extent : -extent));
        p = vec3_add(p, vec3_scale(f, (i & 4) ? extent : -extent));
        f32 v[4] = { p.e[0], p.e[1], p.e[2], 1.0f };
        f32 ndc[3];
        for (int r = 0; r < 3; r++)
            ndc[r] = vp.e[0][r]*v[0] + vp.e[1][r]*v[1] + vp.e[2][r]*v[2] + vp.e[3][r]*v[3];
        /* 0.02 margin: near=0.1 offset pushes the far corner slightly past ±1. */
        ASSERT_TRUE(ndc[0] > -1.02f && ndc[0] < 1.02f);
        ASSERT_TRUE(ndc[1] > -1.02f && ndc[1] < 1.02f);
        ASSERT_TRUE(ndc[2] > -1.02f && ndc[2] < 1.02f);
        if (ndc[0] < min_x) min_x = ndc[0];
        if (ndc[0] > max_x) max_x = ndc[0];
        if (ndc[1] < min_y) min_y = ndc[1];
        if (ndc[1] > max_y) max_y = ndc[1];
        if (ndc[2] < min_z) min_z = ndc[2];
        if (ndc[2] > max_z) max_z = ndc[2];
    }
    /* The 8 corners must span the cube — a collapsed projection (all corners
     * mapping to ~(0,0,-1), the broken-layout symptom) fails these. */
    ASSERT_TRUE(max_x > 0.5f && min_x < -0.5f);
    ASSERT_TRUE(max_y > 0.5f && min_y < -0.5f);
    ASSERT_TRUE(max_z - min_z > 0.5f);
}

/* Determinant of the 3x3 rotation block (rows = basis vectors). */
static f32 lview_rot_det(const Mat4 *m) {
    f32 r0[3] = { m->e[0][0], m->e[1][0], m->e[2][0] };
    f32 r1[3] = { m->e[0][1], m->e[1][1], m->e[2][1] };
    f32 r2[3] = { m->e[0][2], m->e[1][2], m->e[2][2] };
    f32 c[3] = { r1[1]*r2[2] - r1[2]*r2[1],
                 r1[2]*r2[0] - r1[0]*r2[2],
                 r1[0]*r2[1] - r1[1]*r2[0] };
    return r0[0]*c[0] + r0[1]*c[1] + r0[2]*c[2];
}

/* R439: the cascade light view must use the same right-handed basis as
 * camera_view (det = +1) — including the zenith fallback. The old
 * left-handed lview mirrored the shadow-map parameterization; depth render
 * and sampling shared it so shadows stayed self-consistent, but the basis
 * flip must carry CSM along. */
TEST(cascade_lview_right_handed_det) {
    Mat4 lv = build_lview(vec3(10.0f, 5.0f, -7.0f),
                          vec3_normalize(vec3(0.3f, -1.0f, 0.2f)), 50.0f);
    ASSERT_FLOAT_EQ(lview_rot_det(&lv), 1.0f, 1e-4f);

    /* Zenith fallback (light_dir ∥ world up), both signs. */
    Mat4 lz_down = build_lview(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), 50.0f);
    ASSERT_FLOAT_EQ(lview_rot_det(&lz_down), 1.0f, 1e-4f);
    Mat4 lz_up = build_lview(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 50.0f);
    ASSERT_FLOAT_EQ(lview_rot_det(&lz_up), 1.0f, 1e-4f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(cascade_vp_corners_fill_unit_cube);
    RUN_TEST(cascade_lview_right_handed_det);
    RUN_TEST(shadow_snap_stable_under_subtexel_camera_move);
    RUN_TEST(shadow_snap_shifts_only_whole_texels);
    RUN_TEST(shadow_snap_idempotent);
    RUN_TEST(shadow_snap_grid_aligned);
    RUN_TEST(shadow_snap_half_texel_boundary);
    RUN_TEST(shadow_snap_guard_degenerate);
TEST_MAIN_END()
