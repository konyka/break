#include <renderer/mesh_buffer.h>
#include <string.h>

static u32 take_bytes(MeshBuffer *b, u32 bytes) {
    u32 n = bytes / (u32)sizeof(MeshStageVertex);
    if (n > MESH_BUFFER_MAX_VERTS) n = MESH_BUFFER_MAX_VERTS;
    b->count = n;
    return n;
}

bool mesh_buffer_from_decals(MeshBuffer *b, const Decal *in, u32 count, u32 *dropped) {
    if (!b) return false;
    memset(b, 0, sizeof *b);
    u32 bytes = decal_stage_quads(in, count, b->verts, MESH_BUFFER_MAX_VERTS, dropped);
    take_bytes(b, bytes);
    return true;
}

bool mesh_buffer_from_voxels(MeshBuffer *b, const VoxelVertex *in, u32 count, u32 *dropped) {
    if (!b) return false;
    memset(b, 0, sizeof *b);
    u32 bytes = voxel_stage_vertices(in, count, b->verts, MESH_BUFFER_MAX_VERTS, dropped);
    take_bytes(b, bytes);
    return true;
}

bool mesh_buffer_from_road(MeshBuffer *b, const Vec3 *points, u32 point_count, u32 *dropped) {
    if (!b) return false;
    memset(b, 0, sizeof *b);
    u32 bytes = road_stage_ribbon(points, point_count, b->verts, MESH_BUFFER_MAX_VERTS, dropped);
    take_bytes(b, bytes);
    return true;
}

bool mesh_buffer_upload_desc(const MeshBuffer *b, RHIBufferDesc *out) {
    if (!b || !out || b->count == 0u) return false;
    out->usage = RHI_BUFFER_USAGE_VERTEX;
    out->size = (usize)b->count * sizeof(MeshStageVertex);
    out->initial_data = b->verts;
    return true;
}

bool mesh_buffer_draw_desc(const MeshBuffer *b, MeshDrawDesc *out) {
    if (!b || !out || b->count == 0u) return false;
    out->vertex_count = b->count;
    out->stride = (u32)sizeof(MeshStageVertex);
    return true;
}
