#include "test_framework.h"
#include <math/math.h>
#include <math.h>
#include <float.h>

#define EPS 1e-5f

/* ---- Vec3 Tests ---- */

TEST(vec3_add) {
    Vec3 a = vec3(1.0f, 2.0f, 3.0f);
    Vec3 b = vec3(4.0f, 5.0f, 6.0f);
    Vec3 r = vec3_add(a, b);
    ASSERT_FLOAT_EQ(r.e[0], 5.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[1], 7.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[2], 9.0f, EPS);
}

TEST(vec3_sub) {
    Vec3 a = vec3(5.0f, 7.0f, 9.0f);
    Vec3 b = vec3(1.0f, 2.0f, 3.0f);
    Vec3 r = vec3_sub(a, b);
    ASSERT_FLOAT_EQ(r.e[0], 4.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[1], 5.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[2], 6.0f, EPS);
}

TEST(vec3_scale) {
    Vec3 v = vec3(2.0f, 3.0f, 4.0f);
    Vec3 r = vec3_scale(v, 2.0f);
    ASSERT_FLOAT_EQ(r.e[0], 4.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[1], 6.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[2], 8.0f, EPS);
}

TEST(vec3_normalize) {
    Vec3 v = vec3(3.0f, 0.0f, 4.0f);
    Vec3 r = vec3_normalize(v);
    ASSERT_FLOAT_EQ(vec3_len(r), 1.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[0], 3.0f / 5.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[2], 4.0f / 5.0f, EPS);
}

TEST(vec3_normalize_zero) {
    Vec3 v = vec3(0.0f, 0.0f, 0.0f);
    Vec3 r = vec3_normalize(v);
    ASSERT_FLOAT_EQ(r.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[2], 0.0f, EPS);
}

TEST(vec3_dot) {
    Vec3 a = vec3(1.0f, 2.0f, 3.0f);
    Vec3 b = vec3(4.0f, 5.0f, 6.0f);
    f32 d = vec3_dot(a, b);
    ASSERT_FLOAT_EQ(d, 32.0f, EPS);
}

TEST(vec3_cross) {
    Vec3 x = vec3(1.0f, 0.0f, 0.0f);
    Vec3 y = vec3(0.0f, 1.0f, 0.0f);
    Vec3 z = vec3_cross(x, y);
    ASSERT_FLOAT_EQ(z.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(z.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(z.e[2], 1.0f, EPS);
}

TEST(vec3_lerp) {
    Vec3 a = vec3(0.0f, 0.0f, 0.0f);
    Vec3 b = vec3(10.0f, 20.0f, 30.0f);
    Vec3 r = vec3_lerp(a, b, 0.5f);
    ASSERT_FLOAT_EQ(r.e[0], 5.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[1], 10.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[2], 15.0f, EPS);
}

TEST(vec3_distance) {
    Vec3 a = vec3(1.0f, 0.0f, 0.0f);
    Vec3 b = vec3(4.0f, 0.0f, 0.0f);
    f32 d = vec3_distance(a, b);
    ASSERT_FLOAT_EQ(d, 3.0f, EPS);
}

/* ---- Mat4 Tests ---- */

TEST(mat4_identity_diagonal) {
    Mat4 m = mat4_identity();
    ASSERT_FLOAT_EQ(m.e[0][0], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[1][1], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[2][2], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[3][3], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[0][1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[1][0], 0.0f, EPS);
}

TEST(mat4_multiply_identity) {
    Mat4 a = mat4_translation(1.0f, 2.0f, 3.0f);
    Mat4 id = mat4_identity();
    Mat4 r = mat4_mul(a, id);
    ASSERT_FLOAT_EQ(r.e[3][0], 1.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[3][1], 2.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[3][2], 3.0f, EPS);
}

TEST(mat4_inverse_translation) {
    Mat4 t = mat4_translation(5.0f, -3.0f, 7.0f);
    Mat4 inv = mat4_inverse(t);
    Mat4 result = mat4_mul(t, inv);
    /* Should be identity */
    ASSERT_FLOAT_EQ(result.e[0][0], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[1][1], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[2][2], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[3][3], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[3][0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[3][1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[3][2], 0.0f, EPS);
}

TEST(mat4_inverse_scaling) {
    Mat4 s = mat4_scaling(2.0f, 3.0f, 4.0f);
    Mat4 inv = mat4_inverse(s);
    Mat4 result = mat4_mul(s, inv);
    ASSERT_FLOAT_EQ(result.e[0][0], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[1][1], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[2][2], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[3][3], 1.0f, EPS);
}

/* ---- Quaternion Tests ---- */

TEST(quat_identity_check) {
    Quat q = quat_identity();
    ASSERT_FLOAT_EQ(q.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[2], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[3], 1.0f, EPS);
}

TEST(quat_normalize) {
    Quat q = {{1.0f, 2.0f, 3.0f, 4.0f}};
    Quat n = quat_normalize(q);
    f32 len = sqrtf(n.e[0]*n.e[0] + n.e[1]*n.e[1] + n.e[2]*n.e[2] + n.e[3]*n.e[3]);
    ASSERT_FLOAT_EQ(len, 1.0f, EPS);
}

TEST(quat_inverse_unit) {
    /* quat_inverse assumes unit quaternion: inverse = conjugate */
    Quat q = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), 1.0f);
    Quat inv = quat_inverse(q);
    Quat result = quat_mul(q, inv);
    ASSERT_FLOAT_EQ(result.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[2], 0.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[3], 1.0f, EPS);
}

TEST(quat_multiply_identity) {
    Quat q = quat_from_axis_angle(vec3(0.0f, 0.0f, 1.0f), 0.5f);
    Quat id = quat_identity();
    Quat r = quat_mul(q, id);
    ASSERT_FLOAT_EQ(r.e[0], q.e[0], EPS);
    ASSERT_FLOAT_EQ(r.e[1], q.e[1], EPS);
    ASSERT_FLOAT_EQ(r.e[2], q.e[2], EPS);
    ASSERT_FLOAT_EQ(r.e[3], q.e[3], EPS);
}

TEST(quat_slerp_endpoints) {
    Quat a = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), 0.0f);
    Quat b = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), 1.57f);

    /* t=0 should give a */
    Quat r0 = quat_slerp(a, b, 0.0f);
    ASSERT_FLOAT_EQ(r0.e[0], a.e[0], EPS);
    ASSERT_FLOAT_EQ(r0.e[1], a.e[1], EPS);
    ASSERT_FLOAT_EQ(r0.e[2], a.e[2], EPS);
    ASSERT_FLOAT_EQ(r0.e[3], a.e[3], EPS);

    /* t=1 should give b */
    Quat r1 = quat_slerp(a, b, 1.0f);
    ASSERT_FLOAT_EQ(r1.e[0], b.e[0], EPS);
    ASSERT_FLOAT_EQ(r1.e[1], b.e[1], EPS);
    ASSERT_FLOAT_EQ(r1.e[2], b.e[2], EPS);
    ASSERT_FLOAT_EQ(r1.e[3], b.e[3], EPS);
}

TEST(quat_slerp_midpoint) {
    Quat a = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), 0.0f);
    Quat b = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), 1.0f);
    Quat mid = quat_slerp(a, b, 0.5f);
    /* Midpoint should be unit quaternion */
    f32 len = sqrtf(mid.e[0]*mid.e[0] + mid.e[1]*mid.e[1] +
                    mid.e[2]*mid.e[2] + mid.e[3]*mid.e[3]);
    ASSERT_FLOAT_EQ(len, 1.0f, EPS);
}

TEST(quat_rotate_vec3_axis) {
    /* 90 degrees around Y axis: (1,0,0) -> (0,0,-1) */
    f32 pi_half = 3.14159265f * 0.5f;
    Quat q = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), pi_half);
    Vec3 v = vec3(1.0f, 0.0f, 0.0f);
    Vec3 r = quat_rotate_vec3(q, v);
    ASSERT_FLOAT_EQ(r.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[2], -1.0f, EPS);
}

/* ---- mat4_from_quat Tests ---- */

TEST(mat4_from_quat_identity) {
    Quat q = quat_identity();
    Mat4 m = mat4_from_quat(q);
    ASSERT_FLOAT_EQ(m.e[0][0], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[1][1], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[2][2], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[3][3], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[0][1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[1][0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[2][0], 0.0f, EPS);
}

TEST(mat4_from_quat_90_y) {
    /* 90 degrees around Y axis */
    f32 pi_half = 3.14159265f * 0.5f;
    Quat q = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), pi_half);
    Mat4 m = mat4_from_quat(q);
    /* Rotation 90° around Y: (1,0,0) -> (0,0,-1) */
    ASSERT_FLOAT_EQ(m.e[0][0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[0][2], -1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[2][0], 1.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[2][2], 0.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[1][1], 1.0f, EPS);
}

TEST(mat4_from_quat_matches_quat_rotate) {
    /* mat4_from_quat should produce same result as quat_rotate_vec3 */
    Quat q = quat_from_axis_angle(vec3(0.0f, 0.0f, 1.0f), 1.0f);
    Vec3 v = vec3(1.0f, 2.0f, 3.0f);
    Vec3 rotated = quat_rotate_vec3(q, v);

    Mat4 m = mat4_from_quat(q);
    /* Apply rotation: v' = M * v (column-major: e[col][row]) */
    Vec3 mat_rot;
    mat_rot.e[0] = m.e[0][0]*v.e[0] + m.e[1][0]*v.e[1] + m.e[2][0]*v.e[2];
    mat_rot.e[1] = m.e[0][1]*v.e[0] + m.e[1][1]*v.e[1] + m.e[2][1]*v.e[2];
    mat_rot.e[2] = m.e[0][2]*v.e[0] + m.e[1][2]*v.e[1] + m.e[2][2]*v.e[2];

    ASSERT_FLOAT_EQ(mat_rot.e[0], rotated.e[0], EPS);
    ASSERT_FLOAT_EQ(mat_rot.e[1], rotated.e[1], EPS);
    ASSERT_FLOAT_EQ(mat_rot.e[2], rotated.e[2], EPS);
}

/* ---- mat4_ortho Tests ---- */

TEST(mat4_ortho_symmetric) {
    Mat4 m = mat4_ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    /* Symmetric viewport: translation should be 0 on x,y */
    ASSERT_FLOAT_EQ(m.e[3][0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[3][1], 0.0f, EPS);
    /* Diagonal should be correct */
    ASSERT_FLOAT_EQ(m.e[0][0], 2.0f / 20.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[1][1], 2.0f / 20.0f, EPS);
    ASSERT_FLOAT_EQ(m.e[2][2], -2.0f / 99.9f, EPS);
    ASSERT_FLOAT_EQ(m.e[3][3], 1.0f, EPS);
}

TEST(mat4_ortho_off_center) {
    Mat4 m = mat4_ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    /* Off-center: x translation should be -1 */
    ASSERT_FLOAT_EQ(m.e[3][0], -(800.0f + 0.0f) / (800.0f - 0.0f), EPS);
    ASSERT_FLOAT_EQ(m.e[3][1], -(600.0f + 0.0f) / (600.0f - 0.0f), EPS);
}

/* ---- Quaternion Composition ---- */

TEST(quat_mul_composition) {
    /* Two 90° rotations around Y should equal one 180° rotation */
    f32 pi_half = 3.14159265f * 0.5f;
    Quat q90 = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), pi_half);
    Quat q180 = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), pi_half * 2.0f);

    Quat composed = quat_mul(q90, q90);

    /* Result should rotate (1,0,0) the same as 180° */
    Vec3 v = vec3(1.0f, 0.0f, 0.0f);
    Vec3 r_composed = quat_rotate_vec3(composed, v);
    Vec3 r_180 = quat_rotate_vec3(q180, v);

    ASSERT_FLOAT_EQ(r_composed.e[0], r_180.e[0], EPS);
    ASSERT_FLOAT_EQ(r_composed.e[1], r_180.e[1], EPS);
    ASSERT_FLOAT_EQ(r_composed.e[2], r_180.e[2], EPS);
}

TEST(quat_from_axis_angle_zero_axis) {
    /* Zero axis should return identity */
    Quat q = quat_from_axis_angle(vec3(0.0f, 0.0f, 0.0f), 1.5f);
    ASSERT_FLOAT_EQ(q.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[2], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[3], 1.0f, EPS);
}

/* ---- mat4_mul Associativity ---- */

TEST(mat4_mul_associativity) {
    Mat4 a = mat4_translation(1.0f, 2.0f, 3.0f);
    Mat4 b = mat4_scaling(2.0f, 3.0f, 4.0f);
    Quat q = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), 0.7f);
    Mat4 c = mat4_from_quat(q);

    /* (A*B)*C == A*(B*C) */
    Mat4 ab_c = mat4_mul(mat4_mul(a, b), c);
    Mat4 a_bc = mat4_mul(a, mat4_mul(b, c));

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            ASSERT_FLOAT_EQ(ab_c.e[col][row], a_bc.e[col][row], 1e-3f);
        }
    }
}

/* ---- mat4_inverse Rotation ---- */

TEST(mat4_inverse_rotation) {
    Quat q = quat_from_axis_angle(vec3(1.0f, 1.0f, 0.0f), 1.2f);
    Mat4 m = mat4_from_quat(q);
    Mat4 inv = mat4_inverse(m);
    Mat4 result = mat4_mul(m, inv);

    /* Should be identity */
    ASSERT_FLOAT_EQ(result.e[0][0], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[1][1], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[2][2], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[3][3], 1.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[0][1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[1][0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[2][0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(result.e[0][2], 0.0f, EPS);
}

/* ---- vec3 edge cases ---- */

TEST(vec3_cross_anticommutative) {
    /* a x b = -(b x a) */
    Vec3 a = vec3(1.0f, 2.0f, 3.0f);
    Vec3 b = vec3(4.0f, 5.0f, 6.0f);
    Vec3 ab = vec3_cross(a, b);
    Vec3 ba = vec3_cross(b, a);
    ASSERT_FLOAT_EQ(ab.e[0], -ba.e[0], EPS);
    ASSERT_FLOAT_EQ(ab.e[1], -ba.e[1], EPS);
    ASSERT_FLOAT_EQ(ab.e[2], -ba.e[2], EPS);
}

TEST(vec3_lerp_endpoints) {
    Vec3 a = vec3(-5.0f, 10.0f, 0.0f);
    Vec3 b = vec3(5.0f, -10.0f, 20.0f);
    Vec3 r0 = vec3_lerp(a, b, 0.0f);
    Vec3 r1 = vec3_lerp(a, b, 1.0f);
    ASSERT_FLOAT_EQ(r0.e[0], a.e[0], EPS);
    ASSERT_FLOAT_EQ(r0.e[1], a.e[1], EPS);
    ASSERT_FLOAT_EQ(r1.e[0], b.e[0], EPS);
    ASSERT_FLOAT_EQ(r1.e[2], b.e[2], EPS);
}

/* ---- Edge Cases ---- */

TEST(vec3_normalize_zero_length) {
    /* Zero vector normalize should not crash and return zero */
    Vec3 v = vec3(0.0f, 0.0f, 0.0f);
    Vec3 n = vec3_normalize(v);
    ASSERT_FLOAT_EQ(n.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(n.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(n.e[2], 0.0f, EPS);
}

TEST(vec3_scale_zero) {
    Vec3 a = vec3(1.0f, 2.0f, 3.0f);
    Vec3 r = vec3_scale(a, 0.0f);
    ASSERT_FLOAT_EQ(r.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(r.e[2], 0.0f, EPS);
}

TEST(mat4_inverse_singular) {
    /* Zero matrix inverse should not crash */
    Mat4 z = mat4_scaling(0.0f, 0.0f, 0.0f);
    Mat4 inv = mat4_inverse(z);
    /* Result is undefined, just verify no crash */
    (void)inv;
}

TEST(quat_from_axis_angle_zero_angle) {
    /* Zero angle should give identity */
    Quat q = quat_from_axis_angle(vec3(1.0f, 0.0f, 0.0f), 0.0f);
    ASSERT_FLOAT_EQ(q.e[0], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[1], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[2], 0.0f, EPS);
    ASSERT_FLOAT_EQ(q.e[3], 1.0f, EPS);
}

TEST(quat_slerp_same_quat) {
    /* Slerp with same start/end should return that quat */
    Quat a = quat_from_axis_angle(vec3(0.0f, 1.0f, 0.0f), 0.5f);
    Quat r = quat_slerp(a, a, 0.5f);
    ASSERT_FLOAT_EQ(r.e[0], a.e[0], EPS);
    ASSERT_FLOAT_EQ(r.e[1], a.e[1], EPS);
    ASSERT_FLOAT_EQ(r.e[2], a.e[2], EPS);
    ASSERT_FLOAT_EQ(r.e[3], a.e[3], EPS);
}

TEST(quat_normalize_zero) {
    /* Zero quaternion normalize should not crash */
    Quat q = {{0.0f, 0.0f, 0.0f, 0.0f}};
    Quat n = quat_normalize(q);
    /* Result is undefined, just verify no crash */
    (void)n;
    ASSERT_TRUE(true);
}

TEST(vec3_len_large_values) {
    /* Large values should not overflow */
    Vec3 v = vec3(1e10f, 1e10f, 1e10f);
    f32 len = vec3_len(v);
    ASSERT_TRUE(len > 0.0f);
    ASSERT_TRUE(isfinite(len));
}

TEST(mat4_perspective_extreme_aspect) {
    /* Extreme aspect ratio should not crash */
    Mat4 p = mat4_perspective(1.0f, 1000.0f, 0.1f, 100.0f);
    /* Just verify no NaN or Inf */
    ASSERT_TRUE(isfinite(p.e[0][0]));
    ASSERT_TRUE(isfinite(p.e[1][1]));
}

TEST_MAIN_BEGIN()
    /* Vec3 */
    RUN_TEST(vec3_add);
    RUN_TEST(vec3_sub);
    RUN_TEST(vec3_scale);
    RUN_TEST(vec3_normalize);
    RUN_TEST(vec3_normalize_zero);
    RUN_TEST(vec3_dot);
    RUN_TEST(vec3_cross);
    RUN_TEST(vec3_lerp);
    RUN_TEST(vec3_distance);
    RUN_TEST(vec3_cross_anticommutative);
    RUN_TEST(vec3_lerp_endpoints);
    /* Mat4 */
    RUN_TEST(mat4_identity_diagonal);
    RUN_TEST(mat4_multiply_identity);
    RUN_TEST(mat4_inverse_translation);
    RUN_TEST(mat4_inverse_scaling);
    RUN_TEST(mat4_from_quat_identity);
    RUN_TEST(mat4_from_quat_90_y);
    RUN_TEST(mat4_from_quat_matches_quat_rotate);
    RUN_TEST(mat4_ortho_symmetric);
    RUN_TEST(mat4_ortho_off_center);
    RUN_TEST(mat4_mul_associativity);
    RUN_TEST(mat4_inverse_rotation);
    /* Quaternion */
    RUN_TEST(quat_identity_check);
    RUN_TEST(quat_normalize);
    RUN_TEST(quat_inverse_unit);
    RUN_TEST(quat_multiply_identity);
    RUN_TEST(quat_slerp_endpoints);
    RUN_TEST(quat_slerp_midpoint);
    RUN_TEST(quat_rotate_vec3_axis);
    RUN_TEST(quat_mul_composition);
    RUN_TEST(quat_from_axis_angle_zero_axis);
    /* Edge cases */
    RUN_TEST(vec3_normalize_zero_length);
    RUN_TEST(vec3_scale_zero);
    RUN_TEST(mat4_inverse_singular);
    RUN_TEST(quat_from_axis_angle_zero_angle);
    RUN_TEST(quat_slerp_same_quat);
    RUN_TEST(quat_normalize_zero);
    RUN_TEST(vec3_len_large_values);
    RUN_TEST(mat4_perspective_extreme_aspect);
TEST_MAIN_END()
