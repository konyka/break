#include "lod_skin.h"
#include <meshopt_c/meshopt.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SKIN_VF 16u                     /* floats per SkinnedVertex */
#define SKIN_GRID_MAX_DIM 256u
#define SKIN_GRID_MAX_CELLS (1u << 21)

static void skin_joint_ids(const f32 *v, u32 out[4]) { memcpy(out, v + 8, 4u * sizeof(u32)); }

static u32 skin_joint(u32 j, u32 joint_count) { return j < joint_count ? j : joint_count - 1u; }

static void mat_point(const Mat4 *m, const f32 *p, f32 *out) {
    for (u32 r = 0; r < 3u; r++)
        out[r] = m->e[0][r] * p[0] + m->e[1][r] * p[1] + m->e[2][r] * p[2] + m->e[3][r];
}

static void skin_point(const f32 *v, const Mat4 *mats, u32 joint_count, f32 *out) {
    u32 jt[4];
    skin_joint_ids(v, jt);
    const f32 *w = v + 12;
    f32 sum = w[0] + w[1] + w[2] + w[3];
    if (!mats || !(sum > 0.0f) || !isfinite(sum)) {
        out[0] = v[0]; out[1] = v[1]; out[2] = v[2];
        return;
    }
    out[0] = out[1] = out[2] = 0.0f;
    for (u32 k = 0; k < 4u; k++) {
        if (w[k] == 0.0f) continue;
        f32 q[3];
        mat_point(&mats[skin_joint(jt[k], joint_count)], v, q);
        out[0] += w[k] * q[0]; out[1] += w[k] * q[1]; out[2] += w[k] * q[2];
    }
}

bool lod_skin_positions(const f32 *vertices, u32 vertex_count,
                        const Mat4 *skin_mats, u32 joint_count, f32 *out_xyz) {
    if (!vertices || !out_xyz || vertex_count == 0u) return false;
    if (skin_mats && (joint_count == 0u || joint_count > LOD_SKIN_MAX_JOINTS)) return false;
    for (u32 i = 0; i < vertex_count; i++)
        skin_point(vertices + (usize)i * SKIN_VF, skin_mats, joint_count, out_xyz + (usize)i * 3u);
    return true;
}

static bool all_finite(const f32 *p, usize n) {
    for (usize i = 0; i < n; i++)
        if (!isfinite(p[i])) return false;
    return true;
}

/* ---- exact nearest-triangle distance via a uniform grid ---- */

typedef struct {
    const f32 *pos;        /* xyz, stride 3 */
    const u32 *tri;        /* index triples */
    u32 tri_count;
    f32 lo[3], h, inv_h;
    u32 dim[3];
    u32 *cell_start;       /* [cells + 1] */
    u32 *cell_tris;
    u32 *stamp;            /* [tri_count] */
    u32 epoch;
} SkinGrid;

static void grid_free(SkinGrid *g) {
    free(g->cell_start); free(g->cell_tris); free(g->stamp);
    memset(g, 0, sizeof(*g));
}

static u32 grid_coord(const SkinGrid *g, f32 x, u32 axis) {
    f32 c = (x - g->lo[axis]) * g->inv_h;
    if (!(c > 0.0f)) return 0u;
    if (c >= (f32)g->dim[axis]) return g->dim[axis] - 1u;
    return (u32)c;
}

static bool grid_build(SkinGrid *g, const f32 *pos, const u32 *tri, u32 index_count) {
    memset(g, 0, sizeof(*g));
    g->pos = pos; g->tri = tri; g->tri_count = index_count / 3u;
    if (g->tri_count == 0u) return false;
    f32 lo[3] = { 3.0e38f, 3.0e38f, 3.0e38f }, hi[3] = { -3.0e38f, -3.0e38f, -3.0e38f };
    f64 edge_sum = 0.0;
    for (u32 t = 0; t < g->tri_count; t++) {
        f32 tlo[3] = { 3.0e38f, 3.0e38f, 3.0e38f }, thi[3] = { -3.0e38f, -3.0e38f, -3.0e38f };
        for (u32 c = 0; c < 3u; c++) {
            const f32 *p = pos + (usize)tri[t * 3u + c] * 3u;
            for (u32 a = 0; a < 3u; a++) {
                if (p[a] < tlo[a]) tlo[a] = p[a];
                if (p[a] > thi[a]) thi[a] = p[a];
            }
        }
        f32 ext = 0.0f;
        for (u32 a = 0; a < 3u; a++) {
            if (tlo[a] < lo[a]) lo[a] = tlo[a];
            if (thi[a] > hi[a]) hi[a] = thi[a];
            if (thi[a] - tlo[a] > ext) ext = thi[a] - tlo[a];
        }
        edge_sum += ext;
    }
    f32 max_ext = 0.0f;
    for (u32 a = 0; a < 3u; a++) if (hi[a] - lo[a] > max_ext) max_ext = hi[a] - lo[a];
    f32 h = (f32)(edge_sum / g->tri_count);
    if (!(h > max_ext / (f32)SKIN_GRID_MAX_DIM)) h = max_ext / (f32)SKIN_GRID_MAX_DIM;
    if (!(h > 0.0f) || !isfinite(h)) h = 1.0f;
    for (;;) {
        u64 cells = 1u;
        for (u32 a = 0; a < 3u; a++) {
            f32 n = floorf((hi[a] - lo[a]) / h) + 1.0f;
            g->dim[a] = n > (f32)SKIN_GRID_MAX_DIM ? SKIN_GRID_MAX_DIM : (u32)n;
            cells *= g->dim[a];
        }
        if (cells <= SKIN_GRID_MAX_CELLS) break;
        h *= 1.5f;
    }
    memcpy(g->lo, lo, sizeof(lo));
    g->h = h; g->inv_h = 1.0f / h;
    usize cells = (usize)g->dim[0] * g->dim[1] * g->dim[2];
    g->cell_start = (u32 *)calloc(cells + 1u, sizeof(u32));
    g->stamp = (u32 *)calloc(g->tri_count, sizeof(u32));
    if (!g->cell_start || !g->stamp) { grid_free(g); return false; }
    u64 refs = 0u;
    for (u32 pass = 0; pass < 2u; pass++) {
        for (u32 t = 0; t < g->tri_count; t++) {
            u32 c0[3], c1[3];
            for (u32 a = 0; a < 3u; a++) {
                f32 tlo = 3.0e38f, thi = -3.0e38f;
                for (u32 c = 0; c < 3u; c++) {
                    f32 x = pos[(usize)tri[t * 3u + c] * 3u + a];
                    if (x < tlo) tlo = x;
                    if (x > thi) thi = x;
                }
                c0[a] = grid_coord(g, tlo, a); c1[a] = grid_coord(g, thi, a);
            }
            for (u32 z = c0[2]; z <= c1[2]; z++)
                for (u32 y = c0[1]; y <= c1[1]; y++)
                    for (u32 x = c0[0]; x <= c1[0]; x++) {
                        usize cell = ((usize)z * g->dim[1] + y) * g->dim[0] + x;
                        if (pass == 0u) { g->cell_start[cell + 1u]++; refs++; }
                        else g->cell_tris[g->cell_start[cell]++] = t;
                    }
        }
        if (pass == 0u) {
            if (refs > UINT32_MAX) { grid_free(g); return false; }
            for (usize c = 0; c < cells; c++) g->cell_start[c + 1u] += g->cell_start[c];
            g->cell_tris = (u32 *)malloc((usize)(refs ? refs : 1u) * sizeof(u32));
            if (!g->cell_tris) { grid_free(g); return false; }
        }
    }
    /* the fill pass advanced every start to the next cell's start */
    for (usize c = cells; c > 0u; c--) g->cell_start[c] = g->cell_start[c - 1u];
    g->cell_start[0] = 0u;
    return true;
}

static void grid_visit_cell(SkinGrid *g, const f32 *p, u32 x, u32 y, u32 z, f32 *best) {
    usize cell = ((usize)z * g->dim[1] + y) * g->dim[0] + x;
    for (u32 k = g->cell_start[cell]; k < g->cell_start[cell + 1u]; k++) {
        u32 t = g->cell_tris[k];
        if (g->stamp[t] == g->epoch) continue;
        g->stamp[t] = g->epoch;
        const u32 *i = g->tri + (usize)t * 3u;
        f32 d2 = lod_point_triangle_d2(p, g->pos + (usize)i[0] * 3u, g->pos + (usize)i[1] * 3u,
                                       g->pos + (usize)i[2] * 3u);
        if (d2 < *best) *best = d2;
    }
}

/* Exact squared distance from p to the nearest grid triangle. After shell r
 * (cells at Chebyshev index distance <= r from p's clamped cell) every
 * unvisited triangle lies outside the visited cell box, so the search stops
 * once best is within the distance from p to that box's open faces (faces
 * on the grid boundary have nothing behind them). */
static f32 grid_nearest_d2(SkinGrid *g, const f32 *p) {
    if (++g->epoch == 0u) {
        memset(g->stamp, 0, (usize)g->tri_count * sizeof(u32));
        g->epoch = 1u;
    }
    i32 c[3];
    for (u32 a = 0; a < 3u; a++) c[a] = (i32)grid_coord(g, p[a], a);
    i32 max_r = (i32)g->dim[0];
    if ((i32)g->dim[1] > max_r) max_r = (i32)g->dim[1];
    if ((i32)g->dim[2] > max_r) max_r = (i32)g->dim[2];
    f32 best = 3.0e38f;
    for (i32 r = 0; r <= max_r; r++) {
        i32 lo[3], hi[3];
        for (u32 a = 0; a < 3u; a++) {
            lo[a] = c[a] - r < 0 ? 0 : c[a] - r;
            hi[a] = c[a] + r >= (i32)g->dim[a] ? (i32)g->dim[a] - 1 : c[a] + r;
        }
        for (i32 z = lo[2]; z <= hi[2]; z++)
            for (i32 y = lo[1]; y <= hi[1]; y++) {
                bool face = z == c[2] - r || z == c[2] + r || y == c[1] - r || y == c[1] + r;
                if (face) {
                    for (i32 x = lo[0]; x <= hi[0]; x++)
                        grid_visit_cell(g, p, (u32)x, (u32)y, (u32)z, &best);
                } else {
                    if (c[0] - r >= 0) grid_visit_cell(g, p, (u32)(c[0] - r), (u32)y, (u32)z, &best);
                    if (r > 0 && c[0] + r < (i32)g->dim[0])
                        grid_visit_cell(g, p, (u32)(c[0] + r), (u32)y, (u32)z, &best);
                }
            }
        f32 reach = 3.0e38f;
        for (u32 a = 0; a < 3u; a++) {
            if (lo[a] > 0) {
                f32 d = p[a] - (g->lo[a] + (f32)lo[a] * g->h);
                if (d < reach) reach = d;
            }
            if (hi[a] < (i32)g->dim[a] - 1) {
                f32 d = g->lo[a] + (f32)(hi[a] + 1) * g->h - p[a];
                if (d < reach) reach = d;
            }
        }
        if (reach < 0.0f) reach = 0.0f;
        if (reach >= 3.0e38f || best <= reach * reach) break;
    }
    return best;
}

/* Deviation of LODn from LOD0 in one pose: every LOD0 vertex that LODn
 * drops (used0[v] == 1; 2 = kept, distance 0) against the LODn surface, and LODn centroids / edge midpoints against LOD0 (LODn's own
 * vertices are LOD0 vertices, at distance 0). Returns -1 on failure. */
static f32 pose_deviation(SkinGrid *g0, const f32 *pos, const u8 *used0, u32 vertex_count,
                          const u32 *li, u32 lic) {
    SkinGrid gl;
    if (!grid_build(&gl, pos, li, lic)) return -1.0f;
    f32 worst = 0.0f;
    for (u32 v = 0; v < vertex_count; v++) {
        if (used0[v] != 1u) continue;
        f32 d2 = grid_nearest_d2(&gl, pos + (usize)v * 3u);
        if (d2 > worst) worst = d2;
    }
    grid_free(&gl);
    for (u32 t = 0; t < lic / 3u; t++) {
        const f32 *a = pos + (usize)li[t * 3u] * 3u;
        const f32 *b = pos + (usize)li[t * 3u + 1u] * 3u;
        const f32 *c = pos + (usize)li[t * 3u + 2u] * 3u;
        f32 q[4][3];
        for (u32 k = 0; k < 3u; k++) {
            q[0][k] = (a[k] + b[k] + c[k]) * (1.0f / 3.0f);
            q[1][k] = 0.5f * (a[k] + b[k]);
            q[2][k] = 0.5f * (b[k] + c[k]);
            q[3][k] = 0.5f * (c[k] + a[k]);
        }
        for (u32 s = 0; s < 4u; s++) {
            f32 d2 = grid_nearest_d2(g0, q[s]);
            if (d2 > worst) worst = d2;
        }
    }
    f32 e = sqrtf(worst);
    return isfinite(e) ? e : -1.0f;
}

static u32 dominant_joint(const f32 *v, u32 joint_count) {
    u32 jt[4];
    skin_joint_ids(v, jt);
    const f32 *w = v + 12;
    u32 best = 0u;
    for (u32 k = 1; k < 4u; k++) if (w[k] > w[best]) best = k;
    return w[best] > 0.0f ? skin_joint(jt[best], joint_count) : 0u;
}

static bool skinned_input_valid(const f32 *vertices, u32 vertex_count, const u32 *indices,
                                u32 index_count, const Mat4 *poses, u32 pose_count,
                                u32 joint_count) {
    if (!vertices || !indices || vertex_count == 0u || index_count == 0u || index_count % 3u) return false;
    if (joint_count == 0u || joint_count > LOD_SKIN_MAX_JOINTS) return false;
    if (pose_count > 0u && !poses) return false;
    if (pose_count > 0u && (usize)pose_count > ((usize)-1 - 16u) / sizeof(Mat4) / joint_count) return false;
    if ((u64)vertex_count * (5u + 3u * LOD_SKIN_MAX_POSES) * sizeof(f32) > (u64)(usize)-1 / 2u) return false;
    for (u32 i = 0; i < index_count; i++)
        if (indices[i] >= vertex_count) return false;
    for (u32 v = 0; v < vertex_count; v++)
        if (!all_finite(vertices + (usize)v * SKIN_VF, 8u)) return false;
    if (pose_count > 0u &&
        !all_finite((const f32 *)(const void *)poses, (usize)pose_count * joint_count * 16u))
        return false;
    return true;
}

static void fallback_levels(LodMeshLevels *out, u32 index_count) {
    lod_mesh_levels_free(out);
    out->level_count = 1u;
    out->index_count[0] = index_count;
}

void lod_generate_levels_skinned(const f32 *vertices, u32 vertex_count,
                                 const u32 *indices, u32 index_count,
                                 const Mat4 *poses, u32 pose_count, u32 joint_count,
                                 u32 max_levels, LodMeshLevels *out) {
    if (!out) return;
    memset(out, 0, sizeof(*out));
    out->level_count = 1u;
    out->index_count[0] = index_count;
    if (max_levels > LOD_GEN_MAX_LEVELS) max_levels = LOD_GEN_MAX_LEVELS;
    if (max_levels <= 1u || index_count / 3u < LOD_GEN_MIN_TRIANGLES) return;
    if (!skinned_input_valid(vertices, vertex_count, indices, index_count, poses, pose_count,
                             joint_count))
        return;

    u32 sample_count = pose_count < LOD_SKIN_MAX_POSES ? pose_count : LOD_SKIN_MAX_POSES;
    u32 sample[LOD_SKIN_MAX_POSES];
    for (u32 s = 0; s < sample_count; s++)
        sample[s] = sample_count > 1u
            ? (u32)(((u64)s * (pose_count - 1u) + (sample_count - 1u) / 2u) / (sample_count - 1u))
            : 0u;

    f32 scale = meshopt_simplifyScale(vertices, vertex_count, LOD_SKIN_VERTEX_STRIDE);
    f32 inv_scale = scale > 0.0f ? 1.0f / scale : 1.0f;
    u32 attr_count = 5u + 3u * sample_count;
    f32 weights[5u + 3u * LOD_SKIN_MAX_POSES];
    for (u32 k = 0; k < attr_count; k++) weights[k] = k < 3u ? 0.5f : 1.0f;
    f32 *attrs = (f32 *)malloc((usize)vertex_count * attr_count * sizeof(f32));
    f32 *pos = (f32 *)malloc((usize)vertex_count * 3u * sizeof(f32));
    u8 *used0 = (u8 *)calloc(vertex_count, LOD_GEN_MAX_LEVELS - 1u);
    u8 *lock = NULL;
    if (!attrs || !pos || !used0) goto done;
    for (u32 v = 0; v < vertex_count; v++) {
        const f32 *src = vertices + (usize)v * SKIN_VF;
        f32 *a = attrs + (usize)v * attr_count;
        memcpy(a, src + 3, 5u * sizeof(f32));
        for (u32 s = 0; s < sample_count; s++) {
            skin_point(src, poses + (usize)sample[s] * joint_count, joint_count, a + 5u + 3u * s);
            for (u32 k = 0; k < 3u; k++) a[5u + 3u * s + k] *= inv_scale;
        }
    }
    if (!all_finite(attrs, (usize)vertex_count * attr_count)) goto done;
    if (sample_count == 0u) {
        lock = (u8 *)calloc(vertex_count, 1u);
        if (!lock) goto done;
        for (u32 t = 0; t < index_count; t += 3u)
            for (u32 e = 0; e < 3u; e++) {
                u32 a = indices[t + e], b = indices[t + (e + 1u) % 3u];
                if (dominant_joint(vertices + (usize)a * SKIN_VF, joint_count) !=
                    dominant_joint(vertices + (usize)b * SKIN_VF, joint_count)) {
                    lock[a] = (u8)meshopt_SimplifyVertex_Lock;
                    lock[b] = (u8)meshopt_SimplifyVertex_Lock;
                }
            }
    }

    lod_generate_levels_attr(vertices, vertex_count, LOD_SKIN_VERTEX_STRIDE,
                             attrs, attr_count * (u32)sizeof(f32), weights, attr_count,
                             lock, indices, index_count, max_levels, out);
    if (out->level_count <= 1u) goto done;
    out->scale = scale;

    for (u32 l = 1; l < out->level_count; l++) {
        u8 *mask = used0 + (usize)(l - 1u) * vertex_count;
        for (u32 i = 0; i < index_count; i++) mask[indices[i]] = 1u;
        for (u32 i = 0; i < out->index_count[l]; i++) mask[out->indices[l][i]] = 2u;
    }
    f32 err[LOD_GEN_MAX_LEVELS] = { 0.0f };
    for (u32 s = 0; s <= sample_count; s++) {
        const Mat4 *mats = s == 0u ? NULL : poses + (usize)sample[s - 1u] * joint_count;
        lod_skin_positions(vertices, vertex_count, mats, joint_count, pos);
        SkinGrid g0;
        if (!grid_build(&g0, pos, indices, index_count)) { fallback_levels(out, index_count); goto done; }
        for (u32 l = 1; l < out->level_count; l++) {
            f32 d = pose_deviation(&g0, pos, used0 + (usize)(l - 1u) * vertex_count, vertex_count,
                                   out->indices[l], out->index_count[l]);
            if (d < 0.0f) { grid_free(&g0); fallback_levels(out, index_count); goto done; }
            if (d > err[l]) err[l] = d;
        }
        grid_free(&g0);
    }
    for (u32 l = 1; l < out->level_count; l++) {
        f32 rel = scale > 0.0f ? err[l] / scale : 0.0f;
        out->rel_error[l] = rel > out->rel_error[l - 1u] ? rel : out->rel_error[l - 1u];
    }
done:
    free(attrs); free(pos); free(used0); free(lock);
}

void lod_skin_joint_spheres(const f32 *vertices, u32 vertex_count, u32 joint_count,
                            LodSphere *out) {
    if (!out || joint_count == 0u || joint_count > LOD_SKIN_MAX_JOINTS) return;
    f32 lo[LOD_SKIN_MAX_JOINTS][3], hi[LOD_SKIN_MAX_JOINTS][3];
    for (u32 j = 0; j < joint_count; j++) {
        out[j].c[0] = out[j].c[1] = out[j].c[2] = 0.0f;
        out[j].r = -1.0f;
        for (u32 a = 0; a < 3u; a++) { lo[j][a] = 3.0e38f; hi[j][a] = -3.0e38f; }
    }
    if (!vertices) return;
    for (u32 pass = 0; pass < 2u; pass++) {
        for (u32 v = 0; v < vertex_count; v++) {
            const f32 *src = vertices + (usize)v * SKIN_VF;
            const f32 *w = src + 12;
            f32 sum = w[0] + w[1] + w[2] + w[3];
            if (!(sum > 0.0f) || !isfinite(sum) || !all_finite(src, 3u)) continue;
            u32 jt[4];
            skin_joint_ids(src, jt);
            for (u32 k = 0; k < 4u; k++) {
                if (!(w[k] > 0.0f)) continue;
                u32 j = skin_joint(jt[k], joint_count);
                if (pass == 0u) {
                    for (u32 a = 0; a < 3u; a++) {
                        if (src[a] < lo[j][a]) lo[j][a] = src[a];
                        if (src[a] > hi[j][a]) hi[j][a] = src[a];
                    }
                } else {
                    f32 dx = src[0] - out[j].c[0], dy = src[1] - out[j].c[1], dz = src[2] - out[j].c[2];
                    f32 d = sqrtf(dx * dx + dy * dy + dz * dz);
                    if (d > out[j].r) out[j].r = d;
                }
            }
        }
        if (pass == 0u) {
            for (u32 j = 0; j < joint_count; j++) {
                if (lo[j][0] > hi[j][0]) continue;
                for (u32 a = 0; a < 3u; a++) out[j].c[a] = 0.5f * (lo[j][a] + hi[j][a]);
                out[j].r = 0.0f;
            }
        }
    }
    for (u32 j = 0; j < joint_count; j++)
        if (out[j].r >= 0.0f) out[j].r = out[j].r * (1.0f + 1e-5f) + 1e-6f;
}

/* Upper bound on the spectral norm of the 3x3 part: sqrt of the Gershgorin
 * bound on A^T A (max_i sum_j |c_i . c_j|), which equals the max column norm
 * when the columns are orthogonal (rotation x scale). */
static f32 mat_norm_bound(const Mat4 *m) {
    f32 g[3][3];
    for (u32 i = 0; i < 3u; i++)
        for (u32 j = 0; j < 3u; j++)
            g[i][j] = m->e[i][0] * m->e[j][0] + m->e[i][1] * m->e[j][1] + m->e[i][2] * m->e[j][2];
    f32 best = 0.0f;
    for (u32 i = 0; i < 3u; i++) {
        f32 row = fabsf(g[i][0]) + fabsf(g[i][1]) + fabsf(g[i][2]);
        if (row > best) best = row;
    }
    return sqrtf(best) * (1.0f + 1e-5f);
}

LodSphere lod_skin_bounds(const LodSphere *joint_spheres, u32 joint_count,
                          const Mat4 *skin_mats) {
    LodSphere acc = { { 0.0f, 0.0f, 0.0f }, -1.0f };
    if (!joint_spheres || !skin_mats || joint_count == 0u || joint_count > LOD_SKIN_MAX_JOINTS)
        return acc;
    for (u32 j = 0; j < joint_count; j++) {
        const LodSphere *s = &joint_spheres[j];
        if (!(s->r >= 0.0f)) continue;
        LodSphere t;
        mat_point(&skin_mats[j], s->c, t.c);
        t.r = s->r * mat_norm_bound(&skin_mats[j]);
        if (!all_finite(t.c, 3u) || !isfinite(t.r)) continue;
        if (acc.r < 0.0f) { acc = t; continue; }
        f32 d[3] = { t.c[0] - acc.c[0], t.c[1] - acc.c[1], t.c[2] - acc.c[2] };
        f32 dist = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
        if (dist + t.r <= acc.r) continue;
        if (dist + acc.r <= t.r) { acc = t; continue; }
        f32 r = 0.5f * (dist + acc.r + t.r);
        f32 k = (r - acc.r) / dist;
        for (u32 a = 0; a < 3u; a++) acc.c[a] += d[a] * k;
        acc.r = r;
    }
    if (acc.r >= 0.0f) {
        f32 mag = fabsf(acc.c[0]) + fabsf(acc.c[1]) + fabsf(acc.c[2]);
        acc.r = acc.r * (1.0f + 1e-5f) + mag * 1e-6f;
    }
    return acc;
}

#define SKIN_KEY_TAG 0x4E494B53u /* "SKIN" */

/* Hashed beyond lod_cache_key: tag, layout version, joint_count, pose_count,
 * the pose matrices (only the sampled ones affect output, but all are hashed
 * so the key is a pure function of the caller's input). */
static u8 *skin_extra_key(const Mat4 *poses, u32 pose_count, u32 joint_count, usize *size) {
    usize mats = (poses && pose_count) ? (usize)pose_count * joint_count * sizeof(Mat4) : 0u;
    *size = 16u + mats;
    u8 *k = (u8 *)malloc(*size);
    if (!k) return NULL;
    u32 head[4] = { SKIN_KEY_TAG, 1u, joint_count, mats ? pose_count : 0u };
    for (u32 i = 0; i < 4u; i++)
        for (u32 b = 0; b < 4u; b++) k[i * 4u + b] = (u8)(head[i] >> (b * 8u));
    if (mats) memcpy(k + 16u, poses, mats);
    return k;
}

LodCacheKey lod_skin_cache_key(const f32 *vertices, u32 vertex_count,
                               const u32 *indices, u32 index_count,
                               const Mat4 *poses, u32 pose_count, u32 joint_count,
                               u32 max_levels) {
    usize size = 0u;
    u8 *extra = (pose_count > 0u && (!poses || joint_count == 0u ||
                 (usize)pose_count > ((usize)-1 - 16u) / sizeof(Mat4) / joint_count))
        ? NULL : skin_extra_key(poses, pose_count, joint_count, &size);
    static const u8 k_tag_only[4] = { 'S', 'K', 'I', 'N' };
    LodCacheKey key = lod_cache_key_ex(vertices, vertex_count, LOD_SKIN_VERTEX_STRIDE, indices,
                                       index_count, max_levels,
                                       extra ? (const void *)extra : (const void *)k_tag_only,
                                       extra ? size : sizeof(k_tag_only));
    free(extra);
    return key;
}

typedef struct {
    const f32 *vertices;
    u32 vertex_count;
    const u32 *indices;
    u32 index_count;
    const Mat4 *poses;
    u32 pose_count, joint_count, max_levels;
} SkinGenArgs;

static void skin_generate_cb(void *user, LodMeshLevels *out) {
    const SkinGenArgs *a = (const SkinGenArgs *)user;
    lod_generate_levels_skinned(a->vertices, a->vertex_count, a->indices, a->index_count,
                                a->poses, a->pose_count, a->joint_count, a->max_levels, out);
}

void lod_skin_cache_generate(LodCache *cache, const f32 *vertices, u32 vertex_count,
                             const u32 *indices, u32 index_count,
                             const Mat4 *poses, u32 pose_count, u32 joint_count,
                             u32 max_levels, LodMeshLevels *out) {
    if (!out) return;
    SkinGenArgs args = { vertices, vertex_count, indices, index_count, poses, pose_count,
                         joint_count, max_levels };
    usize size = 0u;
    u8 *extra = NULL;
    if (skinned_input_valid(vertices, vertex_count, indices, index_count, poses, pose_count,
                            joint_count))
        extra = skin_extra_key(poses, pose_count, joint_count, &size);
    if (!extra) {
        memset(out, 0, sizeof(*out));
        skin_generate_cb(&args, out);
        return;
    }
    lod_cache_generate_ex(cache, vertices, vertex_count, LOD_SKIN_VERTEX_STRIDE, indices,
                          index_count, max_levels, extra, size, skin_generate_cb, &args, out);
    free(extra);
}
