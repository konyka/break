#pragma once
#include <core/types.h>
#include <math/math.h>

/* Build a ribbon. Each input point becomes a left/right pair in `out`
 * (left at 2*i, right at 2*i+1). Y comes from the heightfield. Points
 * outside the grid are dropped. Returns the number of pairs written. */
u32 road_build_ribbon(const Vec3 *points, u32 count, f32 half_width,
                      const f32 *heights, u32 width, u32 depth,
                      f32 cell, f32 height_scale,
                      Vec3 *out, u32 cap_pairs, u32 *dropped);
