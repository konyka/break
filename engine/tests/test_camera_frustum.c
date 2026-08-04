/* test_camera_frustum.c — Camera + Frustum culling unit tests
 *
 * Tests cover:
 *   - camera_init defaults
 *   - camera_view / camera_projection matrix structure
 *   - frustum plane extraction (structural checks)
 *   - frustum_test_point / aabb / sphere (consistency checks)
 *   - frustum_cull_batch (API and counting)
 */

#include "test_framework.h"
#include <renderer/camera.h>
#include <renderer/cull.h>
#include <renderer/frustum_cull.h>
#include <math.h>

#define EPS 1e-3f

/* ------------------------------------------------------------------ */
/* Camera tests                                                        */
/* ------------------------------------------------------------------ */

TEST(camera_init_defaults)
{
    Camera cam;
    camera_init(&cam, 1.047f, 16.0f/9.0f, 0.1f, 1000.0f);
    ASSERT_TRUE(fabsf(cam.position.e[0] - 0.0f) < EPS);
    ASSERT_TRUE(fabsf(cam.position.e[1] - 2.0f) < EPS);
    ASSERT_TRUE(fabsf(cam.position.e[2] - 8.0f) < EPS);
    ASSERT_TRUE(fabsf(cam.fov - 1.047f) < EPS);
    ASSERT_TRUE(fabsf(cam.near_plane - 0.1f) < EPS);
    ASSERT_TRUE(fabsf(cam.far_plane - 1000.0f) < EPS);
    ASSERT_TRUE(fabsf(cam.move_speed - 3.0f) < EPS);
}

TEST(camera_view_lookat)
{
    Camera cam;
    camera_init(&cam, 1.047f, 16.0f/9.0f, 0.1f, 100.0f);
    Mat4 v = camera_view(&cam);
    /* View matrix: last column should be w=1 */
    ASSERT_TRUE(fabsf(v.e[3][3] - 1.0f) < EPS);
}

/* R438: column-vector M*v for a point (w=1) under the canonical
 * column-major convention: r_i = sum_j e[j][i] * v_j. */
static void cam_apply_point(const Mat4 *m, Vec3 p, f32 out[4]) {
    f32 v[4] = { p.e[0], p.e[1], p.e[2], 1.0f };
    for (int i = 0; i < 4; i++)
        out[i] = m->e[0][i]*v[0] + m->e[1][i]*v[1] + m->e[2][i]*v[2] + m->e[3][i]*v[3];
}

/* R438 characterization: camera translation must actually move geometry in
 * view space (it was silently dead while the layout was transposed). */
TEST(camera_view_translation_moves_points)
{
    Camera cam;
    camera_init(&cam, 1.047f, 16.0f/9.0f, 0.1f, 1000.0f); /* eye (0,2,8), yaw=pitch=0 */
    f32 o[4];

    Mat4 v0 = camera_view(&cam);
    cam_apply_point(&v0, vec3(0.0f, 2.0f, 0.0f), o);
    ASSERT_FLOAT_EQ(o[0],  0.0f, EPS);
    ASSERT_FLOAT_EQ(o[1],  0.0f, EPS);
    ASSERT_FLOAT_EQ(o[2], -8.0f, EPS);
    ASSERT_FLOAT_EQ(o[3],  1.0f, EPS);

    /* Left-handed basis was: camera right = (-1,0,0), view x = +3.
     * Right-handed basis (R439): camera right = (+1,0,0), so a point 3 units
     * in world -X from the eye lands at view x = -3. */
    cam.position = vec3(3.0f, 2.0f, 8.0f);
    Mat4 v1 = camera_view(&cam);
    cam_apply_point(&v1, vec3(0.0f, 2.0f, 0.0f), o);
    ASSERT_FLOAT_EQ(o[0], -3.0f, EPS);
    ASSERT_FLOAT_EQ(o[1],  0.0f, EPS);
    ASSERT_FLOAT_EQ(o[2], -8.0f, EPS);
    ASSERT_FLOAT_EQ(o[3],  1.0f, EPS);
}

/* Determinant of the 3x3 rotation block (rows = basis vectors). */
static f32 cam_rot_block_det(const Mat4 *m) {
    f32 r0[3] = { m->e[0][0], m->e[1][0], m->e[2][0] };
    f32 r1[3] = { m->e[0][1], m->e[1][1], m->e[2][1] };
    f32 r2[3] = { m->e[0][2], m->e[1][2], m->e[2][2] };
    f32 c[3] = { r1[1]*r2[2] - r1[2]*r2[1],
                 r1[2]*r2[0] - r1[0]*r2[2],
                 r1[0]*r2[1] - r1[1]*r2[0] };
    return r0[0]*c[0] + r0[1]*c[1] + r0[2]*c[2];
}

/* R439: the camera view basis must be right-handed (det = +1). The old
 * left-handed basis (det = -1) mirrored the image and flipped winding. */
TEST(camera_view_right_handed_basis)
{
    Camera cam;
    camera_init(&cam, 1.047f, 16.0f/9.0f, 0.1f, 1000.0f); /* eye (0,2,8), yaw=pitch=0 */
    Mat4 v = camera_view(&cam);
    ASSERT_FLOAT_EQ(cam_rot_block_det(&v), 1.0f, 1e-4f);

    /* Screen-space orientation at yaw=0 (facing -Z): world +X must appear
     * view-right (view x > 0). Under the mirrored basis it was view x < 0. */
    f32 o[4];
    cam_apply_point(&v, vec3(1.0f, 2.0f, 0.0f), o);
    ASSERT_TRUE(o[0] > 0.9f && o[0] < 1.1f);

    /* A general pose: still exactly right-handed, and inv_view's rotation
     * block (the inverse rotation) is right-handed too. */
    InputState dummy = {0};
    cam.yaw = 0.8f; cam.pitch = 0.25f;
    camera_update(&cam, &dummy, 0.016f);
    Mat4 vg = camera_view(&cam);
    ASSERT_FLOAT_EQ(cam_rot_block_det(&vg), 1.0f, 1e-4f);
    Mat4 iv = camera_inv_view(&cam);
    ASSERT_FLOAT_EQ(cam_rot_block_det(&iv), 1.0f, 1e-4f);
}

/* R439: WASD strafe must track the (now right-handed) view right vector —
 * D moves along screen-right, A along screen-left. With the basis flip the
 * right vector changed sign; camera_update must use the new one or strafing
 * inverts. */
TEST(camera_update_strafe_matches_view_right)
{
    Camera cam;
    camera_init(&cam, 1.047f, 16.0f/9.0f, 0.1f, 1000.0f);
    cam.yaw = 0.7f; cam.pitch = 0.1f;
    InputState inp = {0};
    camera_update(&cam, &inp, 0.016f); /* cache trig */

    /* View right (row 0 of camera_view) at this pose. */
    Mat4 v = camera_view(&cam);
    Vec3 vright = vec3(v.e[0][0], v.e[1][0], v.e[2][0]);

    Vec3 p0 = cam.position;
    inp.keys['d'] = 2; /* held */
    camera_update(&cam, &inp, 0.1f);
    inp.keys['d'] = 0;
    Vec3 dp = vec3_sub(cam.position, p0);
    ASSERT_TRUE(vec3_dot(dp, vright) > 0.2f); /* D = screen-right */

    p0 = cam.position;
    inp.keys['a'] = 2;
    camera_update(&cam, &inp, 0.1f);
    inp.keys['a'] = 0;
    dp = vec3_sub(cam.position, p0);
    ASSERT_TRUE(vec3_dot(dp, vright) < -0.2f); /* A = screen-left */

    /* Mouse right (dx > 0) must turn the view toward screen-right:
     * forward gains a positive component along the pre-turn right vector. */
    Vec3 f0 = vec3(cam._cp * cam._sy, cam._sp, -cam._cp * cam._cy);
    inp.mouse_dx = 100.0f;
    camera_update(&cam, &inp, 0.016f);
    Vec3 f1 = vec3(cam._cp * cam._sy, cam._sp, -cam._cp * cam._cy);
    ASSERT_TRUE(vec3_dot(vec3_sub(f1, f0), vright) > 0.0f);
}

/* R438 characterization: VP ground truth for the default camera. */
TEST(camera_vp_ground_truth)
{
    Camera cam;
    camera_init(&cam, 1.047f, 16.0f/9.0f, 0.1f, 1000.0f); /* pos (0,2,8) facing -Z */
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    f32 clip[4];

    /* Point 8 units in front on the view axis: clip w = 8, ndc ≈ (0,0,0.975). */
    cam_apply_point(&vp, vec3(0.0f, 2.0f, 0.0f), clip);
    ASSERT_FLOAT_EQ(clip[3], 8.0f, 1e-2f);
    ASSERT_FLOAT_EQ(clip[0] / clip[3], 0.0f, EPS);
    ASSERT_FLOAT_EQ(clip[1] / clip[3], 0.0f, EPS);
    ASSERT_FLOAT_EQ(clip[2] / clip[3], 0.9752f, 1e-3f);

    /* Point behind the camera: w must be negative. */
    cam_apply_point(&vp, vec3(0.0f, 2.0f, 20.0f), clip);
    ASSERT_TRUE(clip[3] < 0.0f);
}

TEST(camera_view_matches_lookat)
{
    /* Verify camera_view output matches mat4_lookat for the same parameters.
     * Both now use the engine convention (translation in column 3).
     * Minor numerical differences from vec3_normalize are expected. */
    Camera cam;
    camera_init(&cam, 1.047f, 1.5f, 0.1f, 200.0f);
    InputState dummy = {0};

    /* Test 1: general orientation */
    cam.yaw = 0.8f; cam.pitch = 0.25f;
    cam.position = vec3(3.0f, 2.0f, -5.0f);
    camera_update(&cam, &dummy, 0.016f);
    Mat4 v_direct = camera_view(&cam);
    Vec3 fwd = {{cam._cp * cam._sy, cam._sp, -cam._cp * cam._cy}};
    Mat4 v_lookat = mat4_lookat(cam.position, vec3_add(cam.position, fwd), vec3(0, 1, 0));
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            ASSERT_TRUE(fabsf(v_direct.e[c][r] - v_lookat.e[c][r]) < 1e-4f);

    /* Test 2: near gimbal-lock (high pitch, small cp stresses normalize) */
    cam.yaw = 2.0f; cam.pitch = 1.5f;
    cam.position = vec3(-1.0f, 5.0f, 0.0f);
    camera_update(&cam, &dummy, 0.016f);
    v_direct = camera_view(&cam);
    fwd = vec3(cam._cp * cam._sy, cam._sp, -cam._cp * cam._cy);
    v_lookat = mat4_lookat(cam.position, vec3_add(cam.position, fwd), vec3(0, 1, 0));
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            ASSERT_TRUE(fabsf(v_direct.e[c][r] - v_lookat.e[c][r]) < 1e-4f);
}

TEST(camera_projection_perspective)
{
    Camera cam;
    camera_init(&cam, 1.5708f, 1.0f, 1.0f, 100.0f);  /* 90 deg */
    Mat4 p = camera_projection(&cam);
    /* f = 1/tan(pi/4) = 1.0. e[0][0] = f/aspect = 1.0 */
    ASSERT_TRUE(fabsf(p.e[0][0] - 1.0f) < EPS);
    ASSERT_TRUE(fabsf(p.e[1][1] - 1.0f) < EPS);
    /* e[2][3] should be -1 (perspective divide row) */
    ASSERT_TRUE(fabsf(p.e[2][3] - (-1.0f)) < EPS);
}

TEST(camera_projection_aspect)
{
    Camera cam;
    camera_init(&cam, 1.5708f, 2.0f, 1.0f, 100.0f);
    Mat4 p = camera_projection(&cam);
    /* aspect=2: e[0][0] = 1/(2*tan(45)) = 0.5 */
    ASSERT_TRUE(fabsf(p.e[0][0] - 0.5f) < EPS);
    ASSERT_TRUE(fabsf(p.e[1][1] - 1.0f) < EPS);
}

/* ------------------------------------------------------------------ */
/* Frustum tests — structural + API consistency                        */
/* ------------------------------------------------------------------ */

TEST(frustum_from_vp_produces_normalized_planes)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    /* All 6 plane normals should be roughly unit length */
    for (int i = 0; i < 6; i++) {
        f32 len = sqrtf(f.planes[i].e[0]*f.planes[i].e[0] +
                        f.planes[i].e[1]*f.planes[i].e[1] +
                        f.planes[i].e[2]*f.planes[i].e[2]);
        ASSERT_TRUE(len > 0.5f && len < 1.5f);
    }
}

TEST(frustum_extract_matches_from_vp)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);

    Frustum f1 = frustum_from_vp(&vp);
    Frustum f2;
    frustum_extract(&f2, &vp);

    /* Both methods should produce the same planes */
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            ASSERT_TRUE(fabsf(f1.planes[i].e[j] - f2.planes[i].e[j]) < EPS);
        }
        /* R245: sign_mask must also match — batch/AABB culling depends on it. */
        ASSERT_EQ(f1.sign_mask[i], f2.sign_mask[i]);
    }
}

/* R265: a point/volume directly in front of the camera must test VISIBLE.
 * The pre-fix Gribb-Hartmann extraction transposed the matrix indices (built
 * the frustum of VP^T) and reported essentially every in-view point as OUTSIDE.
 * The old tests only asserted that genuinely-outside points are outside, so an
 * all-rejecting frustum passed them; this pins the inside case. Cross-checked
 * against the engine's own clip-space test clip = VP*p (clip.e[r] = sum_c
 * vp.e[c][r]*p.e[c]) so it stays convention-consistent. */
static bool clip_inside(const Mat4 *vp, Vec3 p)
{
    f32 c[4];
    for (int r = 0; r < 4; r++) {
        c[r] = vp->e[0][r]*p.e[0] + vp->e[1][r]*p.e[1] + vp->e[2][r]*p.e[2] + vp->e[3][r];
    }
    f32 w = c[3];
    if (w <= 0.0f) return false;
    return c[0] >= -w && c[0] <= w && c[1] >= -w && c[1] <= w && c[2] >= -w && c[2] <= w;
}

TEST(frustum_point_in_front_visible)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f); /* default pos (0,2,8), looking -Z */
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    /* Directly in front, well inside near/far — must be visible. */
    Vec3 front = vec3(0, 2, -5);
    ASSERT_TRUE(clip_inside(&vp, front));      /* ground truth */
    ASSERT_TRUE(frustum_test_point(&f, front)); /* frustum agrees */
    ASSERT_TRUE(frustum_test_sphere(&f, front, 1.0f));
    ASSERT_TRUE(frustum_test_aabb(&f, vec3(-1, 1, -6), vec3(1, 3, -4)));

    /* Behind the camera stays outside. */
    Vec3 behind = vec3(0, 2, 50);
    ASSERT_TRUE(!clip_inside(&vp, behind));
    ASSERT_TRUE(!frustum_test_point(&f, behind));

    /* Extract path must match and also report the front point visible. */
    Frustum fe;
    frustum_extract(&fe, &vp);
    ASSERT_TRUE(frustum_test_point(&fe, front));
    ASSERT_TRUE(!frustum_test_point(&fe, behind));
}

TEST(frustum_point_behind_camera_outside)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    /* Point well behind the camera (positive Z) should be outside */
    ASSERT_TRUE(!frustum_test_point(&f, vec3(0, 0, 50)));
}

TEST(frustum_point_far_outside)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    /* Point extremely far away should be outside */
    ASSERT_TRUE(!frustum_test_point(&f, vec3(0, 0, -500)));
}

TEST(frustum_point_lateral_outside)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    /* Point far to the side should be outside */
    ASSERT_TRUE(!frustum_test_point(&f, vec3(100, 0, -5)));
}

TEST(frustum_aabb_behind_camera)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    /* Box entirely behind camera */
    ASSERT_TRUE(!frustum_test_aabb(&f, vec3(-1,-1,10), vec3(1,1,20)));
}

TEST(frustum_sphere_far_outside)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    ASSERT_TRUE(!frustum_test_sphere(&f, vec3(100, 100, 100), 1.0f));
}

TEST(frustum_cull_batch_empty)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    u32 vis[4];
    u32 count = frustum_cull_batch(&f, NULL, 0, vis);
    ASSERT_EQ(count, 0u);
}

TEST(frustum_cull_batch_all_behind)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    CullAABB boxes[2];
    boxes[0].min = vec3(-1, -1, 10);
    boxes[0].max = vec3( 1,  1, 20);
    boxes[1].min = vec3(-1, -1, 30);
    boxes[1].max = vec3( 1,  1, 40);

    u32 vis[2];
    u32 count = frustum_cull_batch(&f, boxes, 2, vis);
    ASSERT_EQ(count, 0u);
}

TEST(frustum_cull_batch_filters_behind)
{
    /* Verify batch culling rejects boxes behind the camera
     * while potentially accepting boxes in other configurations */
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    CullAABB boxes[3];
    boxes[0].min = vec3(-1, -1, 10);  /* behind camera */
    boxes[0].max = vec3( 1,  1, 20);
    boxes[1].min = vec3(50, 50, 50);  /* far outside */
    boxes[1].max = vec3(51, 51, 51);
    boxes[2].min = vec3(-1, -1, 200); /* behind + far */
    boxes[2].max = vec3( 1,  1, 210);

    u32 vis[3];
    u32 count = frustum_cull_batch(&f, boxes, 3, vis);
    /* None of these should be visible */
    ASSERT_EQ(count, 0u);
}

/* ------------------------------------------------------------------ */
/*  Edge Cases                                                          */
/* ------------------------------------------------------------------ */

TEST(camera_extreme_fov)
{
    Camera cam;
    /* Very wide FOV (170 degrees) */
    camera_init(&cam, 2.967f, 1.0f, 0.1f, 100.0f);
    Mat4 p = camera_projection(&cam);
    /* Should not crash - just verify matrix is valid */
    ASSERT_TRUE(fabsf(p.e[0][0]) > 0.01f);
    ASSERT_TRUE(fabsf(p.e[1][1]) > 0.01f);
}

TEST(camera_near_far_equal)
{
    Camera cam;
    /* near == far (degenerate) - should not crash */
    camera_init(&cam, 1.047f, 1.0f, 10.0f, 10.0f);
    Mat4 p = camera_projection(&cam);
    /* Result is undefined but should not crash */
    (void)p;
}

TEST(frustum_zero_radius_sphere)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    /* Zero-radius sphere behind camera should be outside */
    ASSERT_TRUE(!frustum_test_sphere(&f, vec3(0, 0, 50), 0.0f));
}

TEST(frustum_point_aabb)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(&vp);

    /* Point AABB (min == max) behind camera */
    ASSERT_TRUE(!frustum_test_aabb(&f, vec3(0, 0, 50), vec3(0, 0, 50)));
}

TEST(camera_inv_view_product_is_identity)
{
    /* R52-fix: V * inv(V) must equal identity matrix. */
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.yaw = 0.7f;
    cam.pitch = 0.3f;
    cam.position = vec3(1.0f, 2.0f, 5.0f);
    /* Must call camera_update to populate _cy/_sy/_cp/_sp */
    InputState dummy_input = {0};
    camera_update(&cam, &dummy_input, 0.016f);
    /* Update again after changing yaw/pitch so trig is fresh */
    cam.yaw = 0.7f; cam.pitch = 0.3f;
    camera_update(&cam, &dummy_input, 0.016f);

    Mat4 v = camera_view(&cam);
    Mat4 iv = camera_inv_view(&cam);
    Mat4 prod = mat4_mul(v, iv);
    Mat4 ident = mat4_identity();
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            ASSERT_TRUE(fabsf(prod.e[c][r] - ident.e[c][r]) < 1e-4f);
}

TEST(camera_inv_view_matches_generic_inverse)
{
    /* R52-fix: analytical inv(V) must match generic mat4_inverse(V). */
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(3.0f, -1.0f, 7.0f);
    InputState dummy_input = {0};
    camera_update(&cam, &dummy_input, 0.016f);
    cam.yaw = 1.2f; cam.pitch = -0.4f;
    camera_update(&cam, &dummy_input, 0.016f);

    Mat4 v = camera_view(&cam);
    Mat4 iv_analytical = camera_inv_view(&cam);
    Mat4 iv_ref = mat4_inverse(v);
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            ASSERT_TRUE(fabsf(iv_analytical.e[c][r] - iv_ref.e[c][r]) < 1e-4f);
}

TEST(camera_inv_view_near_gimbal_lock)
{
    /* R52-fix: V * inv(V) = I even near gimbal lock (pitch ≈ ±π/2). */
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0.0f, 5.0f, 0.0f);
    InputState dummy_input = {0};
    /* Test pitch near +π/2 */
    cam.yaw = 0.0f; cam.pitch = 1.56f;
    camera_update(&cam, &dummy_input, 0.016f);
    Mat4 v = camera_view(&cam);
    Mat4 iv = camera_inv_view(&cam);
    Mat4 prod = mat4_mul(v, iv);
    Mat4 ident = mat4_identity();
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            ASSERT_TRUE(fabsf(prod.e[c][r] - ident.e[c][r]) < 1e-4f);
    /* Test pitch near -π/2 */
    cam.pitch = -1.56f;
    camera_update(&cam, &dummy_input, 0.016f);
    v = camera_view(&cam);
    iv = camera_inv_view(&cam);
    prod = mat4_mul(v, iv);
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            ASSERT_TRUE(fabsf(prod.e[c][r] - ident.e[c][r]) < 1e-4f);
}

/* R53-fix: End-to-end verification that inv(V)*inv(P) matches inv(VP).
 * This tests the composition used in main.c's frame_inv_vp computation. */
TEST(camera_inv_vp_matches_generic) {
    Camera cam;
    camera_init(&cam, 1.047f, 1.5f, 0.1f, 200.0f);
    cam.position = vec3(3.0f, 2.0f, -5.0f);
    InputState dummy = {0};
    cam.yaw = 0.8f; cam.pitch = 0.25f;
    camera_update(&cam, &dummy, 0.016f);

    Mat4 view = camera_view(&cam);
    Mat4 proj = camera_projection(&cam);
    proj.e[2][0] = 0.0003f; proj.e[2][1] = -0.0005f; /* TAA jitter */

    Mat4 vp = mat4_mul_proj_view(proj, view);
    Mat4 inv_vp_fast = mat4_mul(camera_inv_view(&cam), mat4_inv_perspective(proj));
    Mat4 inv_vp_ref  = mat4_inverse(vp);
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            ASSERT_TRUE(fabsf(inv_vp_fast.e[c][r] - inv_vp_ref.e[c][r]) < 1e-3f);
}

/* R53-fix: End-to-end verification of inv(VP) with third-person offset.
 * Reproduces main.c's third-person flow: view offset via R*fwd*tp,
 * then inv(VP) = (inv_view with eye-fwd*tp) * inv_proj.
 * Must match generic mat4_inverse(VP). */
TEST(camera_inv_vp_third_person) {
    Camera cam;
    camera_init(&cam, 1.047f, 1.5f, 0.1f, 200.0f);
    cam.position = vec3(3.0f, 2.0f, -5.0f);
    InputState dummy = {0};
    cam.yaw = 0.8f; cam.pitch = 0.25f;
    camera_update(&cam, &dummy, 0.016f);

    Mat4 view = camera_view(&cam);
    f32 tp = 5.0f;
    /* cam_fwd with new convention: (cp*sy, sp, -cp*cy) */
    Vec3 fwd = {{cam._cp * cam._sy, cam._sp, -cam._cp * cam._cy}};
    /* Apply third-person offset to view: t_new = t + R*fwd*tp.
     * R438 canonical layout: translation in e[3][i], row i = e[0..2][i]. */
    view.e[3][0] += (view.e[0][0]*fwd.e[0] + view.e[1][0]*fwd.e[1] + view.e[2][0]*fwd.e[2]) * tp;
    view.e[3][1] += (view.e[0][1]*fwd.e[0] + view.e[1][1]*fwd.e[1] + view.e[2][1]*fwd.e[2]) * tp;
    view.e[3][2] += (view.e[0][2]*fwd.e[0] + view.e[1][2]*fwd.e[1] + view.e[2][2]*fwd.e[2]) * tp;

    Mat4 proj = camera_projection(&cam);
    Mat4 vp = mat4_mul(proj, view);

    /* Analytical: inv(V) with eye adjusted by -fwd*tp, then * inv(P).
     * R438 canonical layout: eye in e[3][0..2]. */
    Mat4 iv = camera_inv_view(&cam);
    iv.e[3][0] -= fwd.e[0] * tp;
    iv.e[3][1] -= fwd.e[1] * tp;
    iv.e[3][2] -= fwd.e[2] * tp;
    Mat4 inv_vp_fast = mat4_mul(iv, mat4_inv_perspective(proj));

    /* Reference: generic inverse */
    Mat4 inv_vp_ref = mat4_inverse(vp);

    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            ASSERT_TRUE(fabsf(inv_vp_fast.e[c][r] - inv_vp_ref.e[c][r]) < 1e-3f);
}

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */

TEST_MAIN_BEGIN()
    RUN_TEST(camera_init_defaults);
    RUN_TEST(camera_view_lookat);
    RUN_TEST(camera_view_translation_moves_points);
    RUN_TEST(camera_view_right_handed_basis);
    RUN_TEST(camera_update_strafe_matches_view_right);
    RUN_TEST(camera_vp_ground_truth);
    RUN_TEST(camera_view_matches_lookat);
    RUN_TEST(camera_projection_perspective);
    RUN_TEST(camera_projection_aspect);
    RUN_TEST(frustum_from_vp_produces_normalized_planes);
    RUN_TEST(frustum_extract_matches_from_vp);
    RUN_TEST(frustum_point_in_front_visible);
    RUN_TEST(frustum_point_behind_camera_outside);
    RUN_TEST(frustum_point_far_outside);
    RUN_TEST(frustum_point_lateral_outside);
    RUN_TEST(frustum_aabb_behind_camera);
    RUN_TEST(frustum_sphere_far_outside);
    RUN_TEST(frustum_cull_batch_empty);
    RUN_TEST(frustum_cull_batch_all_behind);
    RUN_TEST(frustum_cull_batch_filters_behind);
    /* Edge cases */
    RUN_TEST(camera_extreme_fov);
    RUN_TEST(camera_near_far_equal);
    RUN_TEST(frustum_zero_radius_sphere);
    RUN_TEST(frustum_point_aabb);
    /* Inverse view matrix correctness */
    RUN_TEST(camera_inv_view_product_is_identity);
    RUN_TEST(camera_inv_view_matches_generic_inverse);
    RUN_TEST(camera_inv_view_near_gimbal_lock);
    /* Inverse VP composition */
    RUN_TEST(camera_inv_vp_matches_generic);
    RUN_TEST(camera_inv_vp_third_person);
TEST_MAIN_END()
