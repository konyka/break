#include <renderer/mesh_stage.h>

static void write_vert(MeshStageVertex *v, Vec3 p, Vec3 n, u32 material) {
    v->px = p.e[0];
    v->py = p.e[1];
    v->pz = p.e[2];
    v->nx = n.e[0];
    v->ny = n.e[1];
    v->nz = n.e[2];
    v->material = material;
}

bool mesh_vertices_migrate(const MeshStageVertex *in, u32 count,
                           MeshVertex *out, u32 cap) {
    if (count > cap || (count > 0u && (!in || !out))) return false;
    for (u32 i = 0; i < count; i++) {
        MeshStageVertex src = in[i];
        MeshVertex *dst = &out[i];
        dst->px = src.px;
        dst->py = src.py;
        dst->pz = src.pz;
        dst->nx = src.nx;
        dst->ny = src.ny;
        dst->nz = src.nz;
        dst->material = src.material;
        f32 ax = fabsf(src.nx);
        f32 ay = fabsf(src.ny);
        f32 az = fabsf(src.nz);
        if (ay >= ax && ay >= az) {
            dst->u = src.px;
            dst->v = src.pz;
        } else if (ax >= az) {
            dst->u = src.pz;
            dst->v = src.py;
        } else {
            dst->u = src.px;
            dst->v = src.py;
        }
    }
    return true;
}

static void decal_axes(Vec3 normal, Vec3 *tangent, Vec3 *bitangent) {
    if (fabsf(normal.e[1]) > 0.9f) {
        *tangent = vec3(1.0f, 0.0f, 0.0f);
        *bitangent = vec3(0.0f, 0.0f, 1.0f);
        return;
    }
    Vec3 t = vec3_cross(vec3(0.0f, 1.0f, 0.0f), normal);
    f32 len = vec3_len(t);
    if (len < 1.0e-6f) t = vec3(1.0f, 0.0f, 0.0f);
    else t = vec3_scale(t, 1.0f / len);
    *tangent = t;
    *bitangent = vec3_cross(normal, t);
}

u32 decal_stage_quads(const Decal *in, u32 count, MeshStageVertex *out, u32 cap_verts, u32 *dropped) {
    if (dropped) *dropped = 0;
    if (!in || (cap_verts > 0 && !out)) return 0;
    u32 written = 0;
    u32 drop = 0;
    for (u32 i = 0; i < count; i++) {
        Vec3 n = in[i].normal;
        if (!(in[i].size > 0.0f) || !isfinite(in[i].size) ||
            !isfinite(in[i].position.e[0]) || !isfinite(in[i].position.e[1]) || !isfinite(in[i].position.e[2]) ||
            !isfinite(n.e[0]) || !isfinite(n.e[1]) || !isfinite(n.e[2])) {
            drop++;
            continue;
        }
        if (written + 4u > cap_verts) {
            drop++;
            continue;
        }
        Vec3 tangent, bitangent;
        decal_axes(n, &tangent, &bitangent);
        f32 h = in[i].size * 0.5f;
        Vec3 c = in[i].position;
        Vec3 tx = vec3_scale(tangent, h);
        Vec3 bz = vec3_scale(bitangent, h);
        Vec3 corners[4];
        corners[0] = vec3_sub(vec3_sub(c, tx), bz);
        corners[1] = vec3_sub(vec3_add(c, tx), bz);
        corners[2] = vec3_add(vec3_add(c, tx), bz);
        corners[3] = vec3_add(vec3_sub(c, tx), bz);
        for (u32 k = 0; k < 4u; k++) write_vert(&out[written + k], corners[k], n, in[i].material);
        written += 4u;
    }
    if (dropped) *dropped = drop;
    return written * (u32)sizeof(MeshStageVertex);
}

u32 voxel_stage_vertices(const VoxelVertex *in, u32 count, MeshStageVertex *out, u32 cap_verts, u32 *dropped) {
    if (dropped) *dropped = 0;
    if (!in || (cap_verts > 0 && !out)) return 0;
    u32 n = count < cap_verts ? count : cap_verts;
    for (u32 i = 0; i < n; i++) write_vert(&out[i], in[i].position, in[i].normal, 0u);
    if (dropped) *dropped = count - n;
    return n * (u32)sizeof(MeshStageVertex);
}

u32 road_stage_ribbon(const Vec3 *points, u32 point_count, MeshStageVertex *out, u32 cap_verts, u32 *dropped) {
    if (dropped) *dropped = 0;
    if (!points || (cap_verts > 0 && !out)) return 0;
    u32 pairs = point_count / 2u;
    u32 fit = cap_verts / 2u;
    u32 n = pairs < fit ? pairs : fit;
    Vec3 up = vec3(0.0f, 1.0f, 0.0f);
    for (u32 i = 0; i < n; i++) {
        write_vert(&out[i * 2u], points[i * 2u], up, 0u);
        write_vert(&out[i * 2u + 1u], points[i * 2u + 1u], up, 0u);
    }
    if (dropped) *dropped = pairs - n;
    if ((point_count & 1u) != 0u && dropped) *dropped += 1u;
    return n * 2u * (u32)sizeof(MeshStageVertex);
}
