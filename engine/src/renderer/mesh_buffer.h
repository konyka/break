#pragma once
#include <renderer/mesh_stage.h>
#include <rhi/rhi.h>

#define MESH_BUFFER_MAX_VERTS 256u
#define MESH_BUFFER_MAX_INDICES 768u

/* Owned host copy plus the descriptors a vertex and index buffer create
 * would take. No device is allocated here, and nothing is submitted to a
 * command buffer. */
typedef struct MeshBuffer {
    MeshVertex verts[MESH_BUFFER_MAX_VERTS];
    u32 indices[MESH_BUFFER_MAX_INDICES];
    u32 count;
    u32 index_count;
} MeshBuffer;

typedef struct MeshDrawDesc {
    u32 vertex_count;
    u32 stride;
    u32 index_count; /* 0 means a non-indexed draw */
} MeshDrawDesc;

/* Pack into b->verts. Vertices past MESH_BUFFER_MAX_VERTS are dropped.
 * Returns false when b is null. */
bool mesh_buffer_from_legacy(MeshBuffer *b, const MeshStageVertex *in, u32 count, u32 *dropped);
bool mesh_buffer_from_decals(MeshBuffer *b, const Decal *in, u32 count, u32 *dropped);
bool mesh_buffer_from_voxels(MeshBuffer *b, const VoxelVertex *in, u32 count, u32 *dropped);
bool mesh_buffer_from_road(MeshBuffer *b, const Vec3 *points, u32 point_count, u32 *dropped);
/* Vertex usage, byte size, and initial_data. Empty buffers return false. */
bool mesh_buffer_upload_desc(const MeshBuffer *b, RHIBufferDesc *out);
/* Index usage. Returns false when there are no indices. */
bool mesh_buffer_index_desc(const MeshBuffer *b, RHIBufferDesc *out);
/* vertex_count, stride, and index_count. Empty vertex buffers return false. */
bool mesh_buffer_draw_desc(const MeshBuffer *b, MeshDrawDesc *out);
