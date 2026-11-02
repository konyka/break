#pragma once
#include <core/types.h>
#include <math/math.h>
#include <renderer/decal.h>
#include <renderer/voxel.h>

/* Host copy of the bytes a vertex buffer would receive. This does not
 * create a device buffer and does not draw. */
typedef struct MeshStageVertex {
    f32 px, py, pz;
    f32 nx, ny, nz;
    u32 material;
} MeshStageVertex;

typedef struct MeshVertex {
    f32 px, py, pz;
    f32 nx, ny, nz;
    u32 material;
    f32 u, v;
} MeshVertex;

/* Migrate the legacy 28-byte layout without changing its stored ABI. UVs are
 * planar on the dominant normal axis. The output is untouched on failure. */
bool mesh_vertices_migrate(const MeshStageVertex *in, u32 count,
                           MeshVertex *out, u32 cap);

/* Four corners of each decal, in the plane of its normal. A decal that
 * does not fit as a whole quad is counted in *dropped and is not written.
 * Returns the number of bytes written. */
u32 decal_stage_quads(const Decal *in, u32 count, MeshStageVertex *out, u32 cap_verts, u32 *dropped);
/* One staged vertex per voxel vertex. Material is 0. Returns bytes written. */
u32 voxel_stage_vertices(const VoxelVertex *in, u32 count, MeshStageVertex *out, u32 cap_verts, u32 *dropped);
/* One staged vertex per ribbon point (left, right, left, right, ...).
 * Normal is +Y and material is 0. A pair that does not fit is dropped whole. */
u32 road_stage_ribbon(const Vec3 *points, u32 point_count, MeshStageVertex *out, u32 cap_verts, u32 *dropped);
