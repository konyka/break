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
    Frustum f = frustum_from_vp(vp);

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

    Frustum f1 = frustum_from_vp(vp);
    Frustum f2;
    frustum_extract(&f2, &vp);

    /* Both methods should produce the same planes */
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            ASSERT_TRUE(fabsf(f1.planes[i].e[j] - f2.planes[i].e[j]) < EPS);
        }
    }
}

TEST(frustum_point_behind_camera_outside)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    cam.position = vec3(0, 0, 0);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(vp);

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
    Frustum f = frustum_from_vp(vp);

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
    Frustum f = frustum_from_vp(vp);

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
    Frustum f = frustum_from_vp(vp);

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
    Frustum f = frustum_from_vp(vp);

    ASSERT_TRUE(!frustum_test_sphere(&f, vec3(100, 100, 100), 1.0f));
}

TEST(frustum_cull_batch_empty)
{
    Camera cam;
    camera_init(&cam, 1.047f, 1.0f, 0.1f, 100.0f);
    Mat4 v = camera_view(&cam);
    Mat4 p = camera_projection(&cam);
    Mat4 vp = mat4_mul(p, v);
    Frustum f = frustum_from_vp(vp);

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
    Frustum f = frustum_from_vp(vp);

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
    Frustum f = frustum_from_vp(vp);

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
    Frustum f = frustum_from_vp(vp);

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
    Frustum f = frustum_from_vp(vp);

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
    /* Apply third-person offset to view: t_new = t + R*fwd*tp */
    view.e[0][3] += (view.e[0][0]*fwd.e[0] + view.e[0][1]*fwd.e[1] + view.e[0][2]*fwd.e[2]) * tp;
    view.e[1][3] += (view.e[1][0]*fwd.e[0] + view.e[1][1]*fwd.e[1] + view.e[1][2]*fwd.e[2]) * tp;
    view.e[2][3] += (view.e[2][0]*fwd.e[0] + view.e[2][1]*fwd.e[1] + view.e[2][2]*fwd.e[2]) * tp;

    Mat4 proj = camera_projection(&cam);
    Mat4 vp = mat4_mul(proj, view);

    /* Analytical: inv(V) with eye adjusted by -fwd*tp, then * inv(P) */
    Mat4 iv = camera_inv_view(&cam);
    iv.e[0][3] -= fwd.e[0] * tp;
    iv.e[1][3] -= fwd.e[1] * tp;
    iv.e[2][3] -= fwd.e[2] * tp;
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
    RUN_TEST(camera_projection_perspective);
    RUN_TEST(camera_projection_aspect);
    RUN_TEST(frustum_from_vp_produces_normalized_planes);
    RUN_TEST(frustum_extract_matches_from_vp);
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
