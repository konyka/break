#pragma once
/* R434: CSM texel snapping — quantize the light view matrix translation to
 * the shadow-map texel grid so the light view-projection does not drift by
 * sub-texel amounts as the camera moves (removes shadow-edge shimmering).
 * Pure CPU-side matrix math shared by the VK and GL backends. */
#include <math/math.h>

/* Snap the light-space x/y translation of `lview` (e[0][3], e[1][3] — with the
 * engine's view-matrix convention where row i of lview dotted with (p,1) gives
 * the light-space coordinate, this is the light-space offset of the world
 * origin) onto the shadow-map texel grid, in place. A fixed world point P maps
 * to light-space (R*P + t)/texel; with t quantized to whole texels and R fixed
 * per sun direction, P's texel coordinate shifts only by whole texels as the
 * camera moves — no sub-texel shimmer.
 * `ortho_extent` is the half-width of the cascade's symmetric ortho
 * projection (light-space span = 2*ortho_extent); `shadow_map_size` is the
 * per-cascade shadow map resolution in texels.
 * Only the x/y (ortho plane) rows are quantized; depth is left untouched.
 * Idempotent: snapping an already-snapped matrix is a no-op.
 * Degenerate inputs (non-positive extent, zero size) leave lview unchanged. */
static inline void shadow_snap_lview_to_texel(Mat4 *lview,
                                              f32 ortho_extent, u32 shadow_map_size) {
    if (!lview || ortho_extent <= 0.0f || shadow_map_size == 0u) return;
    f32 texel = (2.0f * ortho_extent) / (f32)shadow_map_size;
    /* Round to the nearest texel multiple (half rounds up, deterministic at
     * the +/-0.5 texel boundary). */
    lview->e[0][3] = floorf(lview->e[0][3] / texel + 0.5f) * texel;
    lview->e[1][3] = floorf(lview->e[1][3] / texel + 0.5f) * texel;
}
