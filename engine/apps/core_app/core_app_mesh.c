#include "core_app_mesh.h"

#include <scene/scene_serial.h>

/* The scene contract is 32 bytes (pos3 + normal3 + uv2) while MeshVertex is
 * 36 (the same fields plus a material index), so a flat copy would misalign
 * every vertex. This conversion is pure and unit-tested separately so the
 * stride rule has a regression test independent of any device. */
bool core_app_mesh_convert_vertices(const u8 *vertices, u32 vertex_count,
                                   MeshVertex *out, u32 capacity) {
    if (vertex_count != 0u && !vertices) return false;
    if (!out || vertex_count > capacity) return false;
    for (u32 i = 0u; i < vertex_count; ++i) {
        const f32 *source = (const f32 *)(vertices + (usize)i * BSCN_MESH_VERTEX_STRIDE);
        MeshVertex *target = &out[i];
        target->px = source[0];
        target->py = source[1];
        target->pz = source[2];
        target->nx = source[3];
        target->ny = source[4];
        target->nz = source[5];
        target->material = 0u;
        target->u = source[6];
        target->v = source[7];
    }
    return true;
}

