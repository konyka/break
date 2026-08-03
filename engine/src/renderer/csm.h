#pragma once
/* R434: CSM texel snapping — quantize the light view matrix translation to
 * the shadow-map texel grid so the light view-projection does not drift by
 * sub-texel amounts as the camera moves (removes shadow-edge shimmering).
 * Pure CPU-side matrix math shared by the VK and GL backends. */
#include <math/math.h>

/* R438: build the cascade light view matrix (canonical column-major layout,
 * left-handed basis matching camera_view). Extracted from main.c so tests
 * can reuse the exact production construction.
 * `center` is the cascade slice center in world space, `light_dir` the
 * normalized sun direction (unit, pointing from sun toward scene), `extent`
 * the cascade half-extent (eye = center - light_dir*extent).
 * R247: zenith fallback — when light_dir ∥ world up, light_dir × (0,1,0)
 * collapses; fall back to a fixed orthonormal basis in the XZ plane so the
 * matrix stays invertible. */
static inline Mat4 shadow_cascade_lview(Vec3 center, Vec3 light_dir, f32 extent) {
    f32 fx = light_dir.e[0], fy = light_dir.e[1], fz = light_dir.e[2];
    f32 s_len2 = fx * fx + fz * fz;
    f32 sx, sz, ux, uy, uz;
    if (s_len2 > 1e-12f) {
        f32 inv_sl = fast_rsqrt(s_len2);
        /* s = normalize(light_dir × (0,1,0)) = (-fz, 0, fx) / len */
        sx = -fz * inv_sl;
        sz =  fx * inv_sl;
        /* u = normalize(cross(s_unnorm, f)) = cross(s_unnorm, f) * inv_sl
         * cross(s_unnorm, f) = (-fy*fx, fx²+fz², -fy*fz).
         * For unit light_dir: u_len2 = s_len2, so inv_ul = inv_sl (no extra rsqrt). */
        ux = -fy * fx * inv_sl;
        uy = (fx * fx + fz * fz) * inv_sl;
        uz = -fy * fz * inv_sl;
    } else {
        /* R247: sun_dir ∥ world up (zenith sun — reachable via a loaded
         * save whose sun_elevation ≈ ±π/2, which is not range-clamped).
         * Fall back to a fixed orthonormal basis in the XZ plane (row2 = -f
         * stays valid for f = (0,±1,0); this keeps lview invertible). */
        sx = -1.0f; sz = 0.0f;
        ux =  0.0f; uy = 0.0f; uz = 1.0f;
    }
    f32 ex = center.e[0] - fx * extent;
    f32 ey = center.e[1] - fy * extent;
    f32 ez = center.e[2] - fz * extent;
    Mat4 lview;
    /* Canonical column-major (e[col][row]): basis in rows 0..2, translation
     * in e[3][0..2] — same layout as camera_view/mat4_lookat after R438. */
    lview.e[0][0] = -sx;  lview.e[1][0] = 0.0f; lview.e[2][0] = -sz;  lview.e[3][0] = sx*ex + sz*ez;
    lview.e[0][1] = ux;   lview.e[1][1] = uy;   lview.e[2][1] = uz;   lview.e[3][1] = -(ux*ex + uy*ey + uz*ez);
    lview.e[0][2] = -fx;  lview.e[1][2] = -fy;  lview.e[2][2] = -fz;  lview.e[3][2] = fx*ex + fy*ey + fz*ez;
    lview.e[0][3] = 0.0f; lview.e[1][3] = 0.0f; lview.e[2][3] = 0.0f; lview.e[3][3] = 1.0f;
    return lview;
}

/* Snap the light-space x/y translation of `lview` (e[3][0], e[3][1] — with the
 * engine's canonical column-major view-matrix convention where row i of lview
 * dotted with (p,1) gives the light-space coordinate, this is the light-space
 * offset of the world origin) onto the shadow-map texel grid, in place. A fixed
 * world point P maps to light-space (R*P + t)/texel; with t quantized to whole
 * texels and R fixed per sun direction, P's texel coordinate shifts only by
 * whole texels as the camera moves — no sub-texel shimmer.
 * `ortho_extent` is the half-width of the cascade's symmetric ortho
 * projection (light-space span = 2*ortho_extent); `shadow_map_size` is the
 * per-cascade shadow map resolution in texels.
 * Only the x/y (ortho plane) components are quantized; depth is left untouched.
 * Idempotent: snapping an already-snapped matrix is a no-op.
 * Degenerate inputs (non-positive extent, zero size) leave lview unchanged. */
static inline void shadow_snap_lview_to_texel(Mat4 *lview,
                                              f32 ortho_extent, u32 shadow_map_size) {
    if (!lview || ortho_extent <= 0.0f || shadow_map_size == 0u) return;
    f32 texel = (2.0f * ortho_extent) / (f32)shadow_map_size;
    /* Round to the nearest texel multiple (half rounds up, deterministic at
     * the +/-0.5 texel boundary). */
    lview->e[3][0] = floorf(lview->e[3][0] / texel + 0.5f) * texel;
    lview->e[3][1] = floorf(lview->e[3][1] / texel + 0.5f) * texel;
}
