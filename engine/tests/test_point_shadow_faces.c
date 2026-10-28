/* test_point_shadow_faces.c — R647: point_shadow_compute_face_vp must render
 * each cube face so that the texel a direction lands on is the texel
 * texture(cube, direction) reads back.
 *
 * Cube addressing (GL 4.6 table 8.19, identical in D3D and Vulkan): the
 * major axis picks the face, then s = (sc / |ma| + 1) / 2 and
 * t = (tc / |ma| + 1) / 2, with s along the row and t = 0 on memory row 0.
 * Every backend renders a cube face with memory row 0 at NDC y = -1, so the
 * face VP must give NDC x = 2s - 1 and NDC y = 2t - 1 for every direction
 * whose major axis is that face. */
#include "test_framework.h"
#include <renderer/point_shadow.h>
#include <math.h>

static void cube_address(const float d[3], int *face, float *s, float *t) {
    float ax = fabsf(d[0]), ay = fabsf(d[1]), az = fabsf(d[2]);
    float sc, tc, ma;
    if (ax >= ay && ax >= az) {
        ma = ax;
        if (d[0] > 0.0f) { *face = 0; sc = -d[2]; tc = -d[1]; }
        else             { *face = 1; sc =  d[2]; tc = -d[1]; }
    } else if (ay >= az) {
        ma = ay;
        if (d[1] > 0.0f) { *face = 2; sc =  d[0]; tc =  d[2]; }
        else             { *face = 3; sc =  d[0]; tc = -d[2]; }
    } else {
        ma = az;
        if (d[2] > 0.0f) { *face = 4; sc =  d[0]; tc = -d[1]; }
        else             { *face = 5; sc = -d[0]; tc = -d[1]; }
    }
    *s = (sc / ma + 1.0f) * 0.5f;
    *t = (tc / ma + 1.0f) * 0.5f;
}

static void project(const Mat4 *m, const float p[3], float out[4]) {
    int r;
    for (r = 0; r < 4; ++r)
        out[r] = m->e[0][r] * p[0] + m->e[1][r] * p[1] + m->e[2][r] * p[2] +
                 m->e[3][r];
}

TEST(every_face_lands_where_the_cube_sampler_reads) {
    /* Off-centre, non-symmetric directions: each one distinguishes a
     * rotation or a mirror of its face. */
    static const float dirs[][3] = {
        { 1.0f,  0.3f,  0.6f}, { 1.0f, -0.5f, -0.2f},
        {-1.0f,  0.4f, -0.7f}, {-1.0f, -0.2f,  0.5f},
        { 0.3f,  1.0f,  0.6f}, {-0.5f,  1.0f, -0.4f},
        { 0.2f, -1.0f,  0.7f}, {-0.6f, -1.0f, -0.3f},
        { 0.4f,  0.7f,  1.0f}, {-0.3f, -0.5f,  1.0f},
        { 0.6f,  0.2f, -1.0f}, {-0.7f, -0.4f, -1.0f},
    };
    Vec3 light = {{2.0f, -1.0f, 3.0f}};
    Mat4 vp[POINT_SHADOW_FACES];
    int seen[POINT_SHADOW_FACES] = {0};
    unsigned i;
    point_shadow_compute_face_vp(light, 10.0f, vp);
    for (i = 0; i < sizeof(dirs) / sizeof(dirs[0]); ++i) {
        float p[3], clip[4], s, t;
        int face;
        cube_address(dirs[i], &face, &s, &t);
        p[0] = light.e[0] + dirs[i][0] * 2.0f;
        p[1] = light.e[1] + dirs[i][1] * 2.0f;
        p[2] = light.e[2] + dirs[i][2] * 2.0f;
        project(&vp[face], p, clip);
        ASSERT_TRUE(clip[3] > 0.0f);
        if (fabsf(clip[0] / clip[3] - (2.0f * s - 1.0f)) > 1e-4f ||
            fabsf(clip[1] / clip[3] - (2.0f * t - 1.0f)) > 1e-4f)
            printf("FAIL: dir %u face %d ndc (%.3f, %.3f), cube reads (%.3f, %.3f)\n",
                   i, face, clip[0] / clip[3], clip[1] / clip[3],
                   2.0f * s - 1.0f, 2.0f * t - 1.0f);
        ASSERT_FLOAT_EQ(clip[0] / clip[3], 2.0f * s - 1.0f, 1e-4f);
        ASSERT_FLOAT_EQ(clip[1] / clip[3], 2.0f * t - 1.0f, 1e-4f);
        seen[face] = 1;
    }
    for (i = 0; i < POINT_SHADOW_FACES; ++i) ASSERT_TRUE(seen[i]);
}

/* Culling: the depth pipeline culls back faces, so a face VP has to keep the
 * camera's winding — a triangle the camera sees counter-clockwise in NDC
 * (front, s x u = -f) must stay counter-clockwise in every face. */
TEST(every_face_keeps_the_camera_handedness) {
    static const float fwd[POINT_SHADOW_FACES][3] = {
        {1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}
    };
    Vec3 light = {{0.0f, 0.0f, 0.0f}};
    Mat4 vp[POINT_SHADOW_FACES];
    unsigned f;
    point_shadow_compute_face_vp(light, 10.0f, vp);
    for (f = 0; f < POINT_SHADOW_FACES; ++f) {
        /* A world triangle facing the light: its normal points back at the
         * light (-fwd), wound counter-clockwise around that normal. */
        float n[3] = { -fwd[f][0], -fwd[f][1], -fwd[f][2] };
        float a[3], b[3], c[3], ca[4], cb[4], cc[4], area;
        float u[3], v[3];
        int k;
        /* Any basis u, v with u x v = n. */
        if (fabsf(n[1]) < 0.9f) { u[0] = n[2]; u[1] = 0; u[2] = -n[0]; }
        else                    { u[0] = 0; u[1] = -n[2]; u[2] = n[1]; }
        v[0] = n[1] * u[2] - n[2] * u[1];
        v[1] = n[2] * u[0] - n[0] * u[2];
        v[2] = n[0] * u[1] - n[1] * u[0];
        for (k = 0; k < 3; ++k) {
            a[k] = 3.0f * fwd[f][k];
            b[k] = a[k] + 0.5f * u[k];
            c[k] = a[k] + 0.5f * v[k];
        }
        project(&vp[f], a, ca); project(&vp[f], b, cb); project(&vp[f], c, cc);
        area = (cb[0] / cb[3] - ca[0] / ca[3]) * (cc[1] / cc[3] - ca[1] / ca[3]) -
               (cc[0] / cc[3] - ca[0] / ca[3]) * (cb[1] / cb[3] - ca[1] / ca[3]);
        if (area <= 0.0f) printf("FAIL: face %u flips the winding\n", f);
        ASSERT_TRUE(area > 0.0f);
    }
}

TEST_MAIN_BEGIN()
    RUN_TEST(every_face_lands_where_the_cube_sampler_reads);
    RUN_TEST(every_face_keeps_the_camera_handedness);
TEST_MAIN_END()
