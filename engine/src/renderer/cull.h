#pragma once
#include <core/types.h>
#include <math/math.h>

typedef struct {
    Vec4 planes[6];
    u32  sign_mask[6];  /* bit 0/1/2 = plane normal e[0]/e[1]/e[2] >= 0 */
} Frustum;

Frustum frustum_from_vp(const Mat4 *vp);

static inline bool frustum_test_aabb(const Frustum *f, Vec3 aabb_min, Vec3 aabb_max) {
    for (int i = 0; i < 6; i++) {
        u32 sm = f->sign_mask[i];
        f32 px = (sm & 1u) ? aabb_max.e[0] : aabb_min.e[0];
        f32 py = (sm & 2u) ? aabb_max.e[1] : aabb_min.e[1];
        f32 pz = (sm & 4u) ? aabb_max.e[2] : aabb_min.e[2];
        f32 d = f->planes[i].e[0] * px +
                f->planes[i].e[1] * py +
                f->planes[i].e[2] * pz +
                f->planes[i].e[3];
        if (d < 0.0f) return false;
    }
    return true;
}

static inline bool frustum_test_point(const Frustum *f, Vec3 p) {
    for (int i = 0; i < 6; i++) {
        f32 d = f->planes[i].e[0] * p.e[0] +
                f->planes[i].e[1] * p.e[1] +
                f->planes[i].e[2] * p.e[2] +
                f->planes[i].e[3];
        if (d < 0.0f) return false;
    }
    return true;
}

static inline bool frustum_test_sphere(const Frustum *f, Vec3 center, f32 radius) {
    for (int i = 0; i < 6; i++) {
        f32 d = f->planes[i].e[0] * center.e[0] +
                f->planes[i].e[1] * center.e[1] +
                f->planes[i].e[2] * center.e[2] +
                f->planes[i].e[3];
        if (d < -radius) return false;
    }
    return true;
}
