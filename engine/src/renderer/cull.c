#include <renderer/cull.h>

Frustum frustum_from_vp(const Mat4 *vp) {
    Frustum f;
    /* R265 (CORRECTNESS): Gribb-Hartmann on a column-major (e[col][row]) matrix.
     * A clip coordinate is clip.e[r] = sum_c vp->e[c][r] * p.e[c] (the engine's
     * own transform convention: see mat4_vec4 in lighting.c and GLSL `vp*p`), so
     * "row r" of the matrix — as a linear functional of the point — is
     *   row_r = (vp->e[0][r], vp->e[1][r], vp->e[2][r], vp->e[3][r]),
     * and its coefficient for point component i is vp->e[i][r]. The plane
     * coefficient array plane.e[i] (consumed as e0*x+e1*y+e2*z+e3 in
     * frustum_test_*) must therefore be (row3 ± row_k)[i] = vp->e[i][3] ± vp->e[i][k].
     * The old code wrote vp->e[3][i] ± vp->e[k][i] — the two matrix indices were
     * transposed, so it built the frustum of VP^T instead of VP and rejected
     * essentially every point actually inside the view (empirically 100% of
     * in-frustum points misclassified). The GPU cull path (cull.comp does
     * `vp * vec4(center,1)` directly) was correct, which is why the default
     * GPU-driven path still rendered and only these CPU fallbacks were affected.
     * The ± pattern, normalization and sign_mask are unchanged. */
    for (int i = 0; i < 4; i++) {
        f.planes[0].e[i] = vp->e[i][3] + vp->e[i][0]; /* Left */
        f.planes[1].e[i] = vp->e[i][3] - vp->e[i][0]; /* Right */
        f.planes[2].e[i] = vp->e[i][3] + vp->e[i][1]; /* Bottom */
        f.planes[3].e[i] = vp->e[i][3] - vp->e[i][1]; /* Top */
        f.planes[4].e[i] = vp->e[i][3] - vp->e[i][2]; /* Near */
        f.planes[5].e[i] = vp->e[i][3] + vp->e[i][2]; /* Far */
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
