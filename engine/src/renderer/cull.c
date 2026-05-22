#include <renderer/cull.h>

Frustum frustum_from_vp(Mat4 vp) {
    Frustum f;
    for (int i = 0; i < 4; i++) {
        f.planes[0].e[i] = vp.e[3][i] + vp.e[0][i];
        f.planes[1].e[i] = vp.e[3][i] - vp.e[0][i];
        f.planes[2].e[i] = vp.e[3][i] + vp.e[1][i];
        f.planes[3].e[i] = vp.e[3][i] - vp.e[1][i];
        f.planes[4].e[i] = vp.e[3][i] + vp.e[2][i];
        f.planes[5].e[i] = vp.e[3][i] - vp.e[2][i];
    }
    for (int p = 0; p < 6; p++) {
        f32 len = sqrtf(
            f.planes[p].e[0] * f.planes[p].e[0] +
            f.planes[p].e[1] * f.planes[p].e[1] +
            f.planes[p].e[2] * f.planes[p].e[2]
        );
        if (len > 0.0001f) {
            f.planes[p].e[0] /= len;
            f.planes[p].e[1] /= len;
            f.planes[p].e[2] /= len;
            f.planes[p].e[3] /= len;
        }
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
        Vec3 positive = {{
            f->planes[i].e[0] >= 0.0f ? aabb_max.e[0] : aabb_min.e[0],
            f->planes[i].e[1] >= 0.0f ? aabb_max.e[1] : aabb_min.e[1],
            f->planes[i].e[2] >= 0.0f ? aabb_max.e[2] : aabb_min.e[2],
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
