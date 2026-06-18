#include <renderer/cull.h>

Frustum frustum_from_vp(const Mat4 *vp) {
    Frustum f;
    for (int i = 0; i < 4; i++) {
        f.planes[0].e[i] = vp->e[3][i] + vp->e[0][i]; /* Left */
        f.planes[1].e[i] = vp->e[3][i] - vp->e[0][i]; /* Right */
        f.planes[2].e[i] = vp->e[3][i] + vp->e[1][i]; /* Bottom */
        f.planes[3].e[i] = vp->e[3][i] - vp->e[1][i]; /* Top */
        f.planes[4].e[i] = vp->e[3][i] - vp->e[2][i]; /* Near */
        f.planes[5].e[i] = vp->e[3][i] + vp->e[2][i]; /* Far */
    }
    for (int p = 0; p < 6; p++) {
        f32 len2 = f.planes[p].e[0] * f.planes[p].e[0] +
                   f.planes[p].e[1] * f.planes[p].e[1] +
                   f.planes[p].e[2] * f.planes[p].e[2];
        if (len2 > 1e-12f) {
            f32 inv = fast_rsqrt(len2);
            f.planes[p].e[0] *= inv;
            f.planes[p].e[1] *= inv;
            f.planes[p].e[2] *= inv;
            f.planes[p].e[3] *= inv;
        }
        /* Precompute sign mask for p-vertex selection in batch culling. */
        f.sign_mask[p] = (f.planes[p].e[0] >= 0.0f ? 1u : 0u)
                       | (f.planes[p].e[1] >= 0.0f ? 2u : 0u)
                       | (f.planes[p].e[2] >= 0.0f ? 4u : 0u);
    }
    return f;
}

bool frustum_test_point(const Frustum *f, Vec3 p) {
    for (int i = 0; i < 6; i++) {
        f32 d = f->planes[i].e[0] * p.e[0] +
                f->planes[i].e[1] * p.e[1] +
                f->planes[i].e[2] * p.e[2] +
                f->planes[i].e[3];
        if (d < 0.0f) return false;
    }
    return true;
}

bool frustum_test_aabb(const Frustum *f, Vec3 aabb_min, Vec3 aabb_max) {
    for (int i = 0; i < 6; i++) {
        u32 sm = f->sign_mask[i];
        Vec3 positive = {{
            (sm & 1u) ? aabb_max.e[0] : aabb_min.e[0],
            (sm & 2u) ? aabb_max.e[1] : aabb_min.e[1],
            (sm & 4u) ? aabb_max.e[2] : aabb_min.e[2],
        }};
        f32 d = f->planes[i].e[0] * positive.e[0] +
                f->planes[i].e[1] * positive.e[1] +
                f->planes[i].e[2] * positive.e[2] +
                f->planes[i].e[3];
        if (d < 0.0f) return false;
    }
    return true;
}

bool frustum_test_sphere(const Frustum *f, Vec3 center, f32 radius) {
    for (int i = 0; i < 6; i++) {
        f32 d = f->planes[i].e[0] * center.e[0] +
                f->planes[i].e[1] * center.e[1] +
                f->planes[i].e[2] * center.e[2] +
                f->planes[i].e[3];
        if (d < -radius) return false;
    }
    return true;
}
