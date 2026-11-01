#pragma once
#include <core/types.h>
#include <math/math.h>

typedef struct VoxelVertex {
    Vec3 position;
    Vec3 normal;
} VoxelVertex;

/* Emit one quad (4 vertices) for every exposed face of a non-zero block.
 * `blocks` is row-major x + y * size_x + z * size_x * size_y, 0 = empty.
 * Returns the number of vertices written. Faces that do not fit are counted
 * in *dropped_faces. */
u32 voxel_build_faces(const u8 *blocks, u32 size_x, u32 size_y, u32 size_z, f32 cell,
                      VoxelVertex *out, u32 cap, u32 *dropped_faces);
