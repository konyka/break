#include "lod_gen.h"
#include <meshopt_c/meshopt.h>
#include <math.h>
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

void lod_generate_levels_attr(const f32 *positions, u32 vertex_count, u32 position_stride,
                              const f32 *attributes, u32 attribute_stride,
                              const f32 *attribute_weights, u32 attribute_count,
                              const u8 *vertex_lock, const u32 *indices, u32 index_count,
                              u32 max_levels, LodMeshLevels *out) {
    if (!out) return;
    memset(out, 0, sizeof(*out));
    out->level_count = 1u;
    out->index_count[0] = index_count;
    if (!positions || !indices || vertex_count == 0u || index_count == 0u) return;
    if (max_levels > LOD_GEN_MAX_LEVELS) max_levels = LOD_GEN_MAX_LEVELS;
    if (max_levels <= 1u) return;
    if (position_stride < 12u || (position_stride & 3u) != 0u) return;
    if (attribute_count > 32u || (attribute_count > 0u && (!attributes || !attribute_weights ||
        attribute_stride < attribute_count * 4u || (attribute_stride & 3u) != 0u)))
        return;
    if (index_count % 3u != 0u) return;
    if (index_count / 3u < LOD_GEN_MIN_TRIANGLES) return;
    for (u32 i = 0; i < index_count; i++)
        if (indices[i] >= vertex_count) return;

    out->scale = meshopt_simplifyScale(positions, vertex_count, position_stride);

    u32 prev_count = index_count;
    for (u32 l = 1; l < max_levels; l++) {
        usize target = (usize)((f32)prev_count * k_level_ratio[l]);
        target -= target % 3u;
        if (target < 3u) break;
        u32 *dst = (u32 *)malloc((usize)index_count * sizeof(u32));
        if (!dst) break;
        f32 err = 0.0f;
        usize n = meshopt_simplifyWithAttributes(dst, indices, index_count,
                                                 positions, vertex_count, position_stride,
                                                 attributes, attribute_stride,
                                                 attribute_weights, attribute_count,
                                                 vertex_lock, target, k_level_error[l],
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

void lod_generate_levels(const f32 *vertices, u32 vertex_count, u32 vertex_stride,
                         const u32 *indices, u32 index_count, u32 max_levels,
                         LodMeshLevels *out) {
    if (!out) return;
    memset(out, 0, sizeof(*out));
    out->level_count = 1u;
    out->index_count[0] = index_count;
    if (!vertices || vertex_stride < 32u || (vertex_stride & 3u) != 0u) return;
    /* Attributes: normal (weight 0.5) and uv (weight 1.0), read in place from
     * the interleaved vertex (offset 12 = nrm3, 24 = uv2). */
    static const f32 weights[5] = { 0.5f, 0.5f, 0.5f, 1.0f, 1.0f };
    lod_generate_levels_attr(vertices, vertex_count, vertex_stride, vertices + 3, vertex_stride,
                             weights, 5u, NULL, indices, index_count, max_levels, out);
}

f32 lod_point_triangle_d2(const f32 *p, const f32 *a, const f32 *b, const f32 *c) {
    f32 ab[3], ac[3], ap[3], q[3];
    for (u32 k = 0; k < 3u; k++) { ab[k] = b[k] - a[k]; ac[k] = c[k] - a[k]; ap[k] = p[k] - a[k]; }
    f32 d1 = ab[0]*ap[0] + ab[1]*ap[1] + ab[2]*ap[2];
    f32 d2 = ac[0]*ap[0] + ac[1]*ap[1] + ac[2]*ap[2];
    if (d1 <= 0.0f && d2 <= 0.0f) { memcpy(q, a, sizeof(q)); goto done; }
    f32 bp[3], cp[3];
    for (u32 k = 0; k < 3u; k++) { bp[k] = p[k] - b[k]; cp[k] = p[k] - c[k]; }
    f32 d3 = ab[0]*bp[0] + ab[1]*bp[1] + ab[2]*bp[2];
    f32 d4 = ac[0]*bp[0] + ac[1]*bp[1] + ac[2]*bp[2];
    if (d3 >= 0.0f && d4 <= d3) { memcpy(q, b, sizeof(q)); goto done; }
    f32 vc = d1 * d4 - d3 * d2;
    if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f && d1 - d3 > 0.0f) {
        f32 t = d1 / (d1 - d3);
        for (u32 k = 0; k < 3u; k++) q[k] = a[k] + t * ab[k];
        goto done;
    }
    f32 d5 = ab[0]*cp[0] + ab[1]*cp[1] + ab[2]*cp[2];
    f32 d6 = ac[0]*cp[0] + ac[1]*cp[1] + ac[2]*cp[2];
    if (d6 >= 0.0f && d5 <= d6) { memcpy(q, c, sizeof(q)); goto done; }
    f32 vb = d5 * d2 - d1 * d6;
    if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f && d2 - d6 > 0.0f) {
        f32 t = d2 / (d2 - d6);
        for (u32 k = 0; k < 3u; k++) q[k] = a[k] + t * ac[k];
        goto done;
    }
    f32 va = d3 * d6 - d5 * d4;
    if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f && (d4 - d3) + (d5 - d6) > 0.0f) {
        f32 t = (d4 - d3) / ((d4 - d3) + (d5 - d6));
        for (u32 k = 0; k < 3u; k++) q[k] = b[k] + t * (c[k] - b[k]);
        goto done;
    }
    {
        f32 sum = va + vb + vc;
        if (!(sum > 0.0f)) { memcpy(q, a, sizeof(q)); goto done; } /* degenerate */
        f32 v = vb / sum, w = vc / sum;
        for (u32 k = 0; k < 3u; k++) q[k] = a[k] + ab[k] * v + ac[k] * w;
    }
done:;
    f32 dx = p[0] - q[0], dy = p[1] - q[1], dz = p[2] - q[2];
    return dx * dx + dy * dy + dz * dz;
}

static f32 lod_one_sided_d2(const f32 *pv, u32 pvc, const f32 *tv, const u32 *ti, u32 tic,
                            u32 stride_f) {
    u32 tris = tic / 3u;
    u32 samples = LOD_AUTHORED_ERROR_BUDGET / (tris ? tris : 1u);
    if (samples < 64u) samples = 64u;
    if (samples > pvc) samples = pvc;
    f32 worst = 0.0f;
    for (u32 s = 0; s < samples; s++) {
        u32 vi = (u32)((u64)s * pvc / samples);
        const f32 *p = pv + (usize)vi * stride_f;
        f32 best = 3.0e38f;
        for (u32 t = 0; t < tris && best > 0.0f; t++) {
            f32 d2 = lod_point_triangle_d2(p, tv + (usize)ti[t * 3u] * stride_f,
                                      tv + (usize)ti[t * 3u + 1u] * stride_f,
                                      tv + (usize)ti[t * 3u + 2u] * stride_f);
            if (d2 < best) best = d2;
        }
        if (best > worst) worst = best;
    }
    return worst;
}

f32 lod_authored_error(const f32 *base_v, u32 base_vc, const u32 *base_i, u32 base_ic,
                       const f32 *alt_v, u32 alt_vc, const u32 *alt_i, u32 alt_ic,
                       u32 vertex_stride) {
    if (!base_v || !base_i || !alt_v || !alt_i || vertex_stride < 12u || vertex_stride % 4u ||
        base_vc == 0u || alt_vc == 0u || base_ic < 3u || alt_ic < 3u ||
        base_ic % 3u || alt_ic % 3u)
        return -1.0f;
    for (u32 i = 0; i < base_ic; i++) if (base_i[i] >= base_vc) return -1.0f;
    for (u32 i = 0; i < alt_ic; i++) if (alt_i[i] >= alt_vc) return -1.0f;
    u32 sf = vertex_stride / 4u;
    f32 a = lod_one_sided_d2(alt_v, alt_vc, base_v, base_i, base_ic, sf);
    f32 b = lod_one_sided_d2(base_v, base_vc, alt_v, alt_i, alt_ic, sf);
    f32 e = sqrtf(a > b ? a : b);
    return isfinite(e) ? e : -1.0f;
}

bool lod_bake_validate_ex(const u32 *cmds, u32 cmd_count,
                          const u32 *indices, u32 index_total, u32 vertex_total,
                          const u32 *node_cmd_base, const u8 *node_level_count,
                          const u32 *node_vbase, const u32 *node_vcount, u32 node_count,
                          const u32 *cmd_node, const u8 *cmd_level,
                          const u32 *cmd_vbase, const u32 *cmd_vcount,
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
        u32 lo = cmd_vbase ? cmd_vbase[ci] : node_vbase[b];
        u32 count = cmd_vcount ? cmd_vcount[ci] : node_vcount[b];
        if (lo > vertex_total || count > vertex_total - lo)
            LBV_FAIL("cmd %u vertex range [%u,+%u) exceeds %u", ci, lo, count, vertex_total);
        u32 hi = lo + count;
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

bool lod_bake_validate(const u32 *cmds, u32 cmd_count,
                       const u32 *indices, u32 index_total, u32 vertex_total,
                       const u32 *node_cmd_base, const u8 *node_level_count,
                       const u32 *node_vbase, const u32 *node_vcount, u32 node_count,
                       const u32 *cmd_node, const u8 *cmd_level,
                       char *err, usize err_len) {
    return lod_bake_validate_ex(cmds, cmd_count, indices, index_total, vertex_total,
                                node_cmd_base, node_level_count, node_vbase, node_vcount,
                                node_count, cmd_node, cmd_level, NULL, NULL, err, err_len);
}
