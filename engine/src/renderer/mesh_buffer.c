#include <renderer/mesh_buffer.h>
#include <string.h>

static void index_quads(MeshBuffer *b) {
    u32 quads = b->count / 4u;
    u32 limit = MESH_BUFFER_MAX_INDICES / 6u;
    if (quads > limit) quads = limit;
    b->index_count = 0;
    for (u32 q = 0; q < quads; q++) {
        u32 base = q * 4u;
        u32 *ix = &b->indices[b->index_count];
        ix[0] = base;
        ix[1] = base + 1u;
        ix[2] = base + 2u;
        ix[3] = base;
        ix[4] = base + 2u;
        ix[5] = base + 3u;
        b->index_count += 6u;
    }
}

static void index_ribbon(MeshBuffer *b) {
    u32 pairs = b->count / 2u;
    b->index_count = 0;
    if (pairs < 2u) return;
    u32 segs = pairs - 1u;
    u32 limit = MESH_BUFFER_MAX_INDICES / 6u;
    if (segs > limit) segs = limit;
    for (u32 s = 0; s < segs; s++) {
        u32 base = s * 2u;
        u32 *ix = &b->indices[b->index_count];
        ix[0] = base;
        ix[1] = base + 1u;
        ix[2] = base + 3u;
        ix[3] = base;
        ix[4] = base + 3u;
        ix[5] = base + 2u;
        b->index_count += 6u;
    }
}

bool mesh_buffer_from_legacy(MeshBuffer *b, const MeshStageVertex *in, u32 count, u32 *dropped) {
    if (!b || (count > 0u && !in)) return false;
    memset(b, 0, sizeof *b);
    u32 n = count < MESH_BUFFER_MAX_VERTS ? count : MESH_BUFFER_MAX_VERTS;
    if (!mesh_vertices_migrate(in, n, b->verts, MESH_BUFFER_MAX_VERTS)) return false;
    b->count = n;
    if (dropped) *dropped = count - n;
    index_quads(b);
    return true;
}

bool mesh_buffer_from_decals(MeshBuffer *b, const Decal *in, u32 count, u32 *dropped) {
    if (!b) return false;
    MeshStageVertex legacy[MESH_BUFFER_MAX_VERTS];
    u32 bytes = decal_stage_quads(in, count, legacy, MESH_BUFFER_MAX_VERTS, dropped);
    return mesh_buffer_from_legacy(b, legacy, bytes / (u32)sizeof(MeshStageVertex), NULL);
}

bool mesh_buffer_from_voxels(MeshBuffer *b, const VoxelVertex *in, u32 count, u32 *dropped) {
    if (!b) return false;
    MeshStageVertex legacy[MESH_BUFFER_MAX_VERTS];
    u32 bytes = voxel_stage_vertices(in, count, legacy, MESH_BUFFER_MAX_VERTS, dropped);
    return mesh_buffer_from_legacy(b, legacy, bytes / (u32)sizeof(MeshStageVertex), NULL);
}

bool mesh_buffer_from_road(MeshBuffer *b, const Vec3 *points, u32 point_count, u32 *dropped) {
    if (!b) return false;
    MeshStageVertex legacy[MESH_BUFFER_MAX_VERTS];
    u32 bytes = road_stage_ribbon(points, point_count, legacy, MESH_BUFFER_MAX_VERTS, dropped);
    if (!mesh_buffer_from_legacy(b, legacy, bytes / (u32)sizeof(MeshStageVertex), NULL)) return false;
    index_ribbon(b);
    return true;
}

bool mesh_buffer_upload_desc(const MeshBuffer *b, RHIBufferDesc *out) {
    if (!b || !out || b->count == 0u) return false;
    out->usage = RHI_BUFFER_USAGE_VERTEX;
    out->size = (usize)b->count * sizeof(MeshVertex);
    out->initial_data = b->verts;
    return true;
}

bool mesh_buffer_index_desc(const MeshBuffer *b, RHIBufferDesc *out) {
    if (!b || !out || b->index_count == 0u) return false;
    out->usage = RHI_BUFFER_USAGE_INDEX;
    out->size = (usize)b->index_count * sizeof(u32);
    out->initial_data = b->indices;
    return true;
}

bool mesh_buffer_draw_desc(const MeshBuffer *b, MeshDrawDesc *out) {
    if (!b || !out || b->count == 0u) return false;
    out->vertex_count = b->count;
    out->stride = (u32)sizeof(MeshVertex);
    out->index_count = b->index_count;
    return true;
}
