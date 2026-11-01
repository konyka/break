#pragma once
#include <core/types.h>
#include <math/math.h>

typedef struct Decal {
    Vec3 position;
    Vec3 normal;
    f32 size;
    u32 material;
} Decal;

/* Snap each decal onto the heightfield. Valid decals are packed at the
 * front of `out`. A decal whose xz falls outside the grid is counted in
 * *dropped and is not written. Returns the number written. */
u32 decal_place_on_heightfield(const Decal *in, u32 count,
                               Decal *out, u32 cap,
                               const f32 *heights, u32 width, u32 depth,
                               f32 cell, f32 height_scale, u32 *dropped);
