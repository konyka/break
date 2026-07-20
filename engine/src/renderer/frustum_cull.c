#include <renderer/frustum_cull.h>
#include <math.h>

/*
 * frustum_extract - Gribb-Hartmann method
 *
 * Mat4 layout: e[col][row], column-major.
 * Row i of the matrix = e[0][i], e[1][i], e[2][i], e[3][i]
 *
 * Planes (inward-pointing normals):
 *   Left:   row3 + row0
 *   Right:  row3 - row0
 *   Bottom: row3 + row1
 *   Top:    row3 - row1
 *   Near:   row3 - row2
 *   Far:    row3 + row2
 */
void frustum_extract(Frustum *f, const Mat4 *vp)
{
    /* Extract 6 planes using Gribb-Hartmann method.
     * Row j of column-major Mat4: vp->e[0][j], vp->e[1][j], vp->e[2][j], vp->e[3][j] */
    for (int i = 0; i < 4; i++) {
        f->planes[0].e[i] = vp->e[3][i] + vp->e[0][i]; /* Left */
        f->planes[1].e[i] = vp->e[3][i] - vp->e[0][i]; /* Right */
        f->planes[2].e[i] = vp->e[3][i] + vp->e[1][i]; /* Bottom */
        f->planes[3].e[i] = vp->e[3][i] - vp->e[1][i]; /* Top */
        f->planes[4].e[i] = vp->e[3][i] - vp->e[2][i]; /* Near:   row3 - row2 */
        f->planes[5].e[i] = vp->e[3][i] + vp->e[2][i]; /* Far:    row3 + row2 */
    }

    /* Normalize each plane using fast_rsqrt (SSE rsqrt + Newton-Raphson) */
    for (int p = 0; p < 6; p++) {
        f32 len2 =
            f->planes[p].e[0] * f->planes[p].e[0] +
            f->planes[p].e[1] * f->planes[p].e[1] +
            f->planes[p].e[2] * f->planes[p].e[2];
        if (len2 > 1e-12f) {
            f32 inv = fast_rsqrt(len2);
            f->planes[p].e[0] *= inv;
            f->planes[p].e[1] *= inv;
            f->planes[p].e[2] *= inv;
            f->planes[p].e[3] *= inv;
        }
        /* R245: frustum_cull_batch / frustum_test_aabb select the p-vertex via
         * f->sign_mask. frustum_from_vp fills it, but frustum_extract previously
         * left it untouched, so an extract-produced frustum (esp. from a zeroed
         * struct) had sign_mask==0 → every plane picked the min corner → wrong
         * cull results. Compute it identically to frustum_from_vp. */
        f->sign_mask[p] = (f->planes[p].e[0] >= 0.0f ? 1u : 0u)
                        | (f->planes[p].e[1] >= 0.0f ? 2u : 0u)
                        | (f->planes[p].e[2] >= 0.0f ? 4u : 0u);
    }
}

/*
 * frustum_cull_batch - Batch AABB frustum culling
 *
 * Tests each AABB against the 6 frustum planes using the p-vertex method.
 * Returns the number of visible objects and fills visible_indices with their
 * indices.
 */
u32 frustum_cull_batch(const Frustum *f, const CullAABB *aabbs, u32 count,
                       u32 *visible_indices)
{
    u32 visible = 0;

    for (u32 i = 0; i < count; i++) {
        bool inside = true;

        for (int p = 0; p < 6; p++) {
            /* p-vertex: use precomputed sign mask to select max/min components */
            u32 sm = f->sign_mask[p];
            f32 px = (sm & 1u) ? aabbs[i].max.e[0] : aabbs[i].min.e[0];
            f32 py = (sm & 2u) ? aabbs[i].max.e[1] : aabbs[i].min.e[1];
            f32 pz = (sm & 4u) ? aabbs[i].max.e[2] : aabbs[i].min.e[2];

            f32 dist = f->planes[p].e[0] * px +
                       f->planes[p].e[1] * py +
                       f->planes[p].e[2] * pz +
                       f->planes[p].e[3];

            if (dist < 0.0f) {
                inside = false;
                break;
            }
        }

        if (inside) {
            visible_indices[visible] = i;
            visible++;
        }
    }

    return visible;
}
