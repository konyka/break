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
