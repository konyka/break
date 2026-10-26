#include "lod_gen.h"
#include <meshopt_c/meshopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Per-level targets: fraction of the previous level's index count and the
 * relative error cap (meshopt target_error, fraction of the mesh extent). */
static const f32 k_level_ratio[LOD_GEN_MAX_LEVELS] = { 1.0f, 0.5f, 0.5f };
static const f32 k_level_error[LOD_GEN_MAX_LEVELS] = { 0.0f, 0.02f, 0.05f };

void lod_mesh_levels_free(LodMeshLevels *levels) {
    if (!levels) return;
    for (u32 l = 0; l < LOD_GEN_MAX_LEVELS; l++) free(levels->indices[l]);
    memset(levels, 0, sizeof(*levels));
}

void lod_generate_levels(const f32 *vertices, u32 vertex_count, u32 vertex_stride,
                         const u32 *indices, u32 index_count, u32 max_levels,
                         LodMeshLevels *out) {
    if (!out) return;
    memset(out, 0, sizeof(*out));
    out->level_count = 1u;
    out->index_count[0] = index_count;
    if (!vertices || !indices || vertex_count == 0u || index_count == 0u) return;
    if (max_levels > LOD_GEN_MAX_LEVELS) max_levels = LOD_GEN_MAX_LEVELS;
    if (max_levels <= 1u) return;
    if (vertex_stride < 32u || (vertex_stride & 3u) != 0u) return;
    if (index_count % 3u != 0u) return;
    if (index_count / 3u < LOD_GEN_MIN_TRIANGLES) return;
    for (u32 i = 0; i < index_count; i++)
        if (indices[i] >= vertex_count) return;

    out->scale = meshopt_simplifyScale(vertices, vertex_count, vertex_stride);

    /* Attributes: normal (weight 0.5) and uv (weight 1.0), read in place from
     * the interleaved vertex (offset 12 = nrm3, 24 = uv2). */
    static const f32 weights[5] = { 0.5f, 0.5f, 0.5f, 1.0f, 1.0f };
    const f32 *attrs = vertices + 3;

    u32 prev_count = index_count;
    for (u32 l = 1; l < max_levels; l++) {
        usize target = (usize)((f32)prev_count * k_level_ratio[l]);
        target -= target % 3u;
        if (target < 3u) break;
        u32 *dst = (u32 *)malloc((usize)index_count * sizeof(u32));
        if (!dst) break;
        f32 err = 0.0f;
        usize n = meshopt_simplifyWithAttributes(dst, indices, index_count,
                                                 vertices, vertex_count, vertex_stride,
                                                 attrs, vertex_stride, weights, 5,
                                                 NULL, target, k_level_error[l],
                                                 meshopt_SimplifyLockBorder, &err);
        if (n == 0u || n % 3u != 0u ||
            (f32)n > (f32)prev_count * LOD_GEN_STOP_RATIO) {
            free(dst);
            break;
        }
        meshopt_optimizeVertexCache(dst, dst, n, vertex_count);
        u32 *shrunk = (u32 *)realloc(dst, n * sizeof(u32));
        out->indices[l] = shrunk ? shrunk : dst;
        out->index_count[l] = (u32)n;
        out->rel_error[l] = err > out->rel_error[l - 1u] ? err : out->rel_error[l - 1u];
        out->level_count = l + 1u;
        prev_count = (u32)n;
    }
}

bool lod_bake_validate(const u32 *cmds, u32 cmd_count,
                       const u32 *indices, u32 index_total, u32 vertex_total,
                       const u32 *node_cmd_base, const u8 *node_level_count,
                       const u32 *node_vbase, const u32 *node_vcount, u32 node_count,
                       const u32 *cmd_node, const u8 *cmd_level,
                       char *err, usize err_len) {
#define LBV_FAIL(...) do { if (err && err_len) snprintf(err, err_len, __VA_ARGS__); return false; } while (0)
    if (!cmds || !indices || !node_cmd_base || !node_level_count || !node_vbase ||
        !node_vcount || !cmd_node || !cmd_level)
        LBV_FAIL("null table");
    u32 expect_base = 0u;
    for (u32 b = 0; b < node_count; b++) {
        if (node_level_count[b] == 0u) LBV_FAIL("node %u has 0 levels", b);
        if (node_cmd_base[b] != expect_base)
            LBV_FAIL("node %u cmd_base %u != %u (not contiguous)", b, node_cmd_base[b], expect_base);
        if (node_vbase[b] > vertex_total || node_vcount[b] > vertex_total - node_vbase[b])
            LBV_FAIL("node %u vertex range [%u,+%u) exceeds %u", b, node_vbase[b], node_vcount[b], vertex_total);
        for (u32 l = 0; l < node_level_count[b]; l++) {
            u32 ci = node_cmd_base[b] + l;
            if (ci >= cmd_count) LBV_FAIL("node %u level %u cmd %u >= %u", b, l, ci, cmd_count);
            if (cmd_node[ci] != b) LBV_FAIL("cmd %u node %u != %u", ci, cmd_node[ci], b);
            if (cmd_level[ci] != l) LBV_FAIL("cmd %u level %u != %u", ci, cmd_level[ci], l);
        }
        expect_base += node_level_count[b];
    }
    if (expect_base != cmd_count) LBV_FAIL("node levels sum %u != cmd count %u", expect_base, cmd_count);
    for (u32 ci = 0; ci < cmd_count; ci++) {
        const u32 *c = &cmds[ci * 5u];
        u32 ic = c[0], fi = c[2];
        i32 vo = (i32)c[3];
        if (c[1] != 1u) LBV_FAIL("cmd %u instance_count %u", ci, c[1]);
        if (vo != 0) LBV_FAIL("cmd %u vertex_offset %d (absolute indices need 0)", ci, vo);
        if (ic == 0u || ic % 3u != 0u) LBV_FAIL("cmd %u index_count %u", ci, ic);
        if (fi > index_total || ic > index_total - fi)
            LBV_FAIL("cmd %u range [%u,+%u) exceeds %u indices", ci, fi, ic, index_total);
        u32 b = cmd_node[ci];
        if (b >= node_count) LBV_FAIL("cmd %u node %u >= %u", ci, b, node_count);
        u32 lo = node_vbase[b], hi = node_vbase[b] + node_vcount[b];
        for (u32 k = 0; k < ic; k++) {
            u32 v = indices[fi + k] + (u32)vo;
            if (v >= vertex_total) LBV_FAIL("cmd %u index %u -> vertex %u >= %u", ci, k, v, vertex_total);
            if (v < lo || v >= hi)
                LBV_FAIL("cmd %u index %u -> vertex %u outside node %u range [%u,%u)", ci, k, v, b, lo, hi);
        }
    }
    return true;
#undef LBV_FAIL
}
