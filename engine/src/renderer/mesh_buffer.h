#pragma once
#include <renderer/mesh_stage.h>
#include <rhi/rhi.h>

#define MESH_BUFFER_MAX_VERTS 256u

/* Owned host copy plus the descriptor a vertex buffer create would take.
 * No device is allocated here, and nothing is submitted to a command buffer. */
typedef struct MeshBuffer {
    MeshStageVertex verts[MESH_BUFFER_MAX_VERTS];
    u32 count;
} MeshBuffer;

typedef struct MeshDrawDesc {
    u32 vertex_count;
    u32 stride;
} MeshDrawDesc;

/* Pack into b->verts. Vertices past MESH_BUFFER_MAX_VERTS are dropped.
 * Returns false when b is null. */
bool mesh_buffer_from_decals(MeshBuffer *b, const Decal *in, u32 count, u32 *dropped);
bool mesh_buffer_from_voxels(MeshBuffer *b, const VoxelVertex *in, u32 count, u32 *dropped);
bool mesh_buffer_from_road(MeshBuffer *b, const Vec3 *points, u32 point_count, u32 *dropped);
/* Vertex usage, byte size, and initial_data. Empty buffers return false. */
bool mesh_buffer_upload_desc(const MeshBuffer *b, RHIBufferDesc *out);
/* vertex_count and stride for a non-indexed draw. Empty buffers return false. */
bool mesh_buffer_draw_desc(const MeshBuffer *b, MeshDrawDesc *out);
