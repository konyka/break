#include "test_framework.h"
#include <renderer/lod_skin.h>
#include <time.h>
#ifndef _WIN32
#include <sys/stat.h>
#endif

#define TUBE_JOINTS 3u

typedef struct {
    f32 pos[3];
    f32 normal[3];
    f32 uv[2];
    u32 joints[4];
    f32 weights[4];
} TestSkinVertex;

_Static_assert(sizeof(TestSkinVertex) == LOD_SKIN_VERTEX_STRIDE, "SkinnedVertex layout");

/* Tube along +x, length 3, radius 0.25, joints at x = 0 / 1 / 2 with linear
 * blends over +-0.25 around x = 1 and x = 2. */
static void make_tube(u32 rings, u32 sectors, TestSkinVertex **out_v, u32 *out_vc,
                      u32 **out_i, u32 *out_ic) {
    u32 vc = (rings + 1u) * (sectors + 1u), ic = rings * sectors * 6u;
    TestSkinVertex *v = (TestSkinVertex *)calloc(vc, sizeof(TestSkinVertex));
    u32 *idx = (u32 *)malloc((usize)ic * sizeof(u32));
    u32 k = 0;
    for (u32 ri = 0; ri <= rings; ri++) {
        f32 x = 3.0f * (f32)ri / (f32)rings;
        for (u32 si = 0; si <= sectors; si++) {
            f32 th = (f32)si / (f32)sectors * 6.2831853f;
            TestSkinVertex *p = &v[k++];
            p->pos[0] = x; p->pos[1] = 0.25f * cosf(th); p->pos[2] = 0.25f * sinf(th);
            p->normal[0] = 0.0f; p->normal[1] = cosf(th); p->normal[2] = sinf(th);
            p->uv[0] = (f32)si / (f32)sectors; p->uv[1] = x / 3.0f;
            u32 lo_joint = x < 1.5f ? 0u : 1u;
            f32 centre = x < 1.5f ? 1.0f : 2.0f;
            f32 t = (x - (centre - 0.25f)) / 0.5f;
            t = t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);
            p->joints[0] = lo_joint; p->joints[1] = lo_joint + 1u;
            p->joints[2] = 0u; p->joints[3] = 0u;
            p->weights[0] = 1.0f - t; p->weights[1] = t;
        }
    }
    u32 n = 0;
    for (u32 ri = 0; ri < rings; ri++)
        for (u32 si = 0; si < sectors; si++) {
            u32 a = ri * (sectors + 1u) + si, b = a + sectors + 1u;
            idx[n++] = a; idx[n++] = a + 1u; idx[n++] = b;
            idx[n++] = a + 1u; idx[n++] = b + 1u; idx[n++] = b;
        }
    *out_v = v; *out_vc = vc; *out_i = idx; *out_ic = ic;
}

static Mat4 mat_identity(void) {
    Mat4 m;
    memset(&m, 0, sizeof(m));
    for (u32 i = 0; i < 4u; i++) m.e[i][i] = 1.0f;
    return m;
}

static Mat4 mat_mul(const Mat4 *a, const Mat4 *b) {
    Mat4 r;
    for (u32 c = 0; c < 4u; c++)
        for (u32 row = 0; row < 4u; row++) {
            f32 s = 0.0f;
            for (u32 k = 0; k < 4u; k++) s += a->e[k][row] * b->e[c][k];
            r.e[c][row] = s;
        }
    return r;
}

/* Rotation about the z axis through (px, 0, 0). */
static Mat4 pivot_rot_z(f32 px, f32 angle) {
    Mat4 m = mat_identity();
    f32 c = cosf(angle), s = sinf(angle);
    m.e[0][0] = c; m.e[0][1] = s; m.e[1][0] = -s; m.e[1][1] = c;
    m.e[3][0] = px - c * px; m.e[3][1] = -s * px;
    return m;
}

/* Skin matrices of the 3-joint chain bent by a1 at x = 1 and a2 at x = 2. */
static void chain_pose(f32 a1, f32 a2, Mat4 *out) {
    out[0] = mat_identity();
    out[1] = pivot_rot_z(1.0f, a1);
    Mat4 r2 = pivot_rot_z(2.0f, a2);
    out[2] = mat_mul(&out[1], &r2);
}

static f32 *skinned(const TestSkinVertex *v, u32 vc, const Mat4 *mats) {
    f32 *p = (f32 *)malloc((usize)vc * 3u * sizeof(f32));
    if (p && !lod_skin_positions((const f32 *)v, vc, mats, TUBE_JOINTS, p)) { free(p); p = NULL; }
    return p;
}

/* Deviation of LODn from LOD0 under one pose (lod_authored_error on the
 * skinned positions; independent of lod_skin's own measurement). */
static f32 measured(const TestSkinVertex *v, u32 vc, const u32 *idx, u32 ic,
                    const u32 *li, u32 lic, const Mat4 *mats) {
    f32 *p = skinned(v, vc, mats);
    if (!p) return -1.0f;
    f32 e = lod_authored_error(p, vc, idx, ic, p, vc, li, lic, 12u);
    free(p);
    return e;
}

static f64 now_ms(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (f64)ts.tv_sec * 1000.0 + (f64)ts.tv_nsec / 1e6;
}

TEST(lod_skin_levels_reference_original_vertices_and_keep_skin_data) {
    TestSkinVertex *v; u32 vc, ic; u32 *idx;
    make_tube(64u, 32u, &v, &vc, &idx, &ic);
    TestSkinVertex *copy = (TestSkinVertex *)malloc(vc * sizeof(TestSkinVertex));
    memcpy(copy, v, vc * sizeof(TestSkinVertex));
    Mat4 poses[4 * TUBE_JOINTS];
    for (u32 p = 0; p < 4u; p++) chain_pose(0.3f * (f32)p, -0.4f * (f32)p, &poses[p * TUBE_JOINTS]);
    LodMeshLevels lv;
    lod_generate_levels_skinned((const f32 *)v, vc, idx, ic, poses, 4u, TUBE_JOINTS, 3u, &lv);
    ASSERT_TRUE(lv.level_count >= 2u);
    ASSERT_EQ(lv.index_count[0], ic);
    ASSERT_EQ(lv.rel_error[0], 0.0f);
    ASSERT_TRUE(lv.scale > 0.0f);
    for (u32 l = 1; l < lv.level_count; l++) {
        ASSERT_TRUE(lv.index_count[l] > 0u && lv.index_count[l] % 3u == 0u);
        ASSERT_TRUE(lv.index_count[l] < lv.index_count[l - 1u]);
        ASSERT_TRUE(lv.rel_error[l] >= lv.rel_error[l - 1u]);
        for (u32 i = 0; i < lv.index_count[l]; i++) ASSERT_TRUE(lv.indices[l][i] < vc);
    }
    ASSERT_EQ(memcmp(copy, v, vc * sizeof(TestSkinVertex)), 0);
    lod_mesh_levels_free(&lv);
    free(copy); free(v); free(idx);
}

TEST(lod_skin_multi_pose_beats_bind_only_in_bent_pose) {
    TestSkinVertex *v; u32 vc, ic; u32 *idx;
    make_tube(64u, 32u, &v, &vc, &idx, &ic);
    Mat4 poses[3 * TUBE_JOINTS];
    chain_pose(0.0f, 0.0f, &poses[0]);
    chain_pose(1.2f, 0.0f, &poses[TUBE_JOINTS]);
    chain_pose(0.6f, -1.2f, &poses[2u * TUBE_JOINTS]);
    LodMeshLevels bind_only, multi;
    lod_generate_levels((const f32 *)v, vc, LOD_SKIN_VERTEX_STRIDE, idx, ic, 3u, &bind_only);
    lod_generate_levels_skinned((const f32 *)v, vc, idx, ic, poses, 3u, TUBE_JOINTS, 3u, &multi);
    ASSERT_TRUE(bind_only.level_count >= 2u);
    ASSERT_TRUE(multi.level_count >= 2u);
    f32 worst_bind = 0.0f, worst_multi = 0.0f;
    for (u32 p = 1; p < 3u; p++) {
        f32 eb = measured(v, vc, idx, ic, bind_only.indices[1], bind_only.index_count[1],
                          &poses[p * TUBE_JOINTS]);
        f32 em = measured(v, vc, idx, ic, multi.indices[1], multi.index_count[1],
                          &poses[p * TUBE_JOINTS]);
        ASSERT_TRUE(eb >= 0.0f && em >= 0.0f);
        if (eb > worst_bind) worst_bind = eb;
        if (em > worst_multi) worst_multi = em;
    }
    printf("(bind-only L1 %u idx err %.4f, multi-pose L1 %u idx err %.4f, scale %.3f) ",
           bind_only.index_count[1], (double)worst_bind, multi.index_count[1],
           (double)worst_multi, (double)multi.scale);
    ASSERT_TRUE(worst_bind > 4.0f * worst_multi);
    ASSERT_TRUE(worst_bind > 0.05f);
    for (u32 l = 1; l < multi.level_count; l++) {
        for (u32 p = 0; p < 3u; p++) {
            f32 e = measured(v, vc, idx, ic, multi.indices[l], multi.index_count[l],
                             &poses[p * TUBE_JOINTS]);
            ASSERT_TRUE(e >= 0.0f);
            ASSERT_TRUE(multi.rel_error[l] * multi.scale >= e * (1.0f - 1e-4f));
        }
        f32 eb = measured(v, vc, idx, ic, multi.indices[l], multi.index_count[l], NULL);
        ASSERT_TRUE(multi.rel_error[l] * multi.scale >= eb * (1.0f - 1e-4f));
    }
    lod_mesh_levels_free(&bind_only); lod_mesh_levels_free(&multi);
    free(v); free(idx);
}

TEST(lod_skin_more_than_eight_poses_are_subsampled) {
    TestSkinVertex *v; u32 vc, ic; u32 *idx;
    make_tube(48u, 24u, &v, &vc, &idx, &ic);
    Mat4 poses[20 * TUBE_JOINTS];
    for (u32 p = 0; p < 20u; p++)
        chain_pose(0.06f * (f32)p, -0.05f * (f32)p, &poses[p * TUBE_JOINTS]);
    LodMeshLevels lv;
    lod_generate_levels_skinned((const f32 *)v, vc, idx, ic, poses, 20u, TUBE_JOINTS, 3u, &lv);
    ASSERT_TRUE(lv.level_count >= 2u);
    /* the first and last poses are always among the sampled ones */
    f32 e0 = measured(v, vc, idx, ic, lv.indices[1], lv.index_count[1], &poses[0]);
    f32 e19 = measured(v, vc, idx, ic, lv.indices[1], lv.index_count[1], &poses[19u * TUBE_JOINTS]);
    ASSERT_TRUE(lv.rel_error[1] * lv.scale >= e0 * (1.0f - 1e-4f));
    ASSERT_TRUE(lv.rel_error[1] * lv.scale >= e19 * (1.0f - 1e-4f));
    lod_mesh_levels_free(&lv);
    free(v); free(idx);
}

static u32 dominant(const TestSkinVertex *v) {
    u32 b = 0;
    for (u32 k = 1; k < 4u; k++) if (v->weights[k] > v->weights[b]) b = k;
    return v->joints[b];
}

TEST(lod_skin_no_poses_locks_dominant_joint_boundaries) {
    TestSkinVertex *v; u32 vc, ic; u32 *idx;
    make_tube(64u, 32u, &v, &vc, &idx, &ic);
    LodMeshLevels lv;
    lod_generate_levels_skinned((const f32 *)v, vc, idx, ic, NULL, 0u, TUBE_JOINTS, 3u, &lv);
    ASSERT_TRUE(lv.level_count >= 2u);
    u8 *boundary = (u8 *)calloc(vc, 1u);
    u32 boundary_count = 0u;
    for (u32 t = 0; t < ic; t += 3u)
        for (u32 e = 0; e < 3u; e++) {
            u32 a = idx[t + e], b = idx[t + (e + 1u) % 3u];
            if (dominant(&v[a]) != dominant(&v[b])) boundary[a] = boundary[b] = 1u;
        }
    for (u32 i = 0; i < vc; i++) boundary_count += boundary[i];
    ASSERT_TRUE(boundary_count > 0u);
    for (u32 l = 1; l < lv.level_count; l++) {
        u8 *seen = (u8 *)calloc(vc, 1u);
        for (u32 i = 0; i < lv.index_count[l]; i++) seen[lv.indices[l][i]] = 1u;
        u32 missing = 0u;
        for (u32 i = 0; i < vc; i++) if (boundary[i] && !seen[i]) missing++;
        free(seen);
        ASSERT_EQ(missing, 0u);
        f32 e = measured(v, vc, idx, ic, lv.indices[l], lv.index_count[l], NULL);
        ASSERT_TRUE(lv.rel_error[l] * lv.scale >= e * (1.0f - 1e-4f));
    }
    free(boundary);
    lod_mesh_levels_free(&lv);
    free(v); free(idx);
}

static u32 rng_next(u32 *s) {
    *s ^= *s << 13; *s ^= *s >> 17; *s ^= *s << 5;
    return *s;
}

static f32 rng_f(u32 *s, f32 lo, f32 hi) {
    return lo + (hi - lo) * (f32)(rng_next(s) & 0xFFFFFFu) / 16777215.0f;
}

TEST(lod_skin_bounds_contain_skinned_vertices_for_random_poses) {
    TestSkinVertex *v; u32 vc, ic; u32 *idx;
    make_tube(32u, 16u, &v, &vc, &idx, &ic);
    LodSphere js[TUBE_JOINTS];
    lod_skin_joint_spheres((const f32 *)v, vc, TUBE_JOINTS, js);
    for (u32 j = 0; j < TUBE_JOINTS; j++) ASSERT_TRUE(js[j].r > 0.0f);
    u32 seed = 0x1234567u;
    for (u32 trial = 0; trial < 200u; trial++) {
        Mat4 mats[TUBE_JOINTS];
        if (trial % 2u == 0u) {
            chain_pose(rng_f(&seed, -3.0f, 3.0f), rng_f(&seed, -3.0f, 3.0f), mats);
            for (u32 j = 0; j < TUBE_JOINTS; j++) {
                mats[j].e[3][0] += 5.0f; mats[j].e[3][2] -= 2.0f;
            }
        } else {
            for (u32 j = 0; j < TUBE_JOINTS; j++) {
                mats[j] = mat_identity();
                for (u32 c = 0; c < 3u; c++)
                    for (u32 r = 0; r < 3u; r++) mats[j].e[c][r] = rng_f(&seed, -2.0f, 2.0f);
                for (u32 r = 0; r < 3u; r++) mats[j].e[3][r] = rng_f(&seed, -10.0f, 10.0f);
            }
        }
        LodSphere b = lod_skin_bounds(js, TUBE_JOINTS, mats);
        ASSERT_TRUE(b.r > 0.0f);
        f32 *p = skinned(v, vc, mats);
        ASSERT_NOT_NULL(p);
        f32 worst = 0.0f;
        for (u32 i = 0; i < vc; i++) {
            f32 dx = p[i * 3u] - b.c[0], dy = p[i * 3u + 1u] - b.c[1], dz = p[i * 3u + 2u] - b.c[2];
            f32 d = sqrtf(dx * dx + dy * dy + dz * dz);
            if (d - b.r > worst) worst = d - b.r;
        }
        free(p);
        if (worst > 0.0f) printf("trial %u outside by %g ", trial, (double)worst);
        ASSERT_TRUE(worst <= 0.0f);
    }
    LodSphere empty[2] = { { { 0, 0, 0 }, -1.0f }, { { 0, 0, 0 }, -1.0f } };
    Mat4 id[2] = { mat_identity(), mat_identity() };
    ASSERT_TRUE(lod_skin_bounds(empty, 2u, id).r < 0.0f);
    ASSERT_TRUE(lod_skin_bounds(NULL, 2u, id).r < 0.0f);
    ASSERT_TRUE(lod_skin_bounds(js, 0u, id).r < 0.0f);
    free(v); free(idx);
}

static void assert_single_level(const LodMeshLevels *lv, u32 ic) {
    ASSERT_EQ(lv->level_count, 1u);
    ASSERT_EQ(lv->index_count[0], ic);
    for (u32 l = 0; l < LOD_GEN_MAX_LEVELS; l++) ASSERT_TRUE(lv->indices[l] == NULL);
}

TEST(lod_skin_invalid_input_falls_back_to_lod0) {
    TestSkinVertex *v; u32 vc, ic; u32 *idx;
    make_tube(48u, 24u, &v, &vc, &idx, &ic);
    Mat4 poses[2 * TUBE_JOINTS];
    chain_pose(0.5f, 0.5f, poses);
    chain_pose(-0.5f, 0.2f, poses + TUBE_JOINTS);
    const f32 *fv = (const f32 *)v;
    LodMeshLevels lv;
    lod_generate_levels_skinned(NULL, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, ic);
    lod_generate_levels_skinned(fv, vc, NULL, ic, poses, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, ic);
    lod_generate_levels_skinned(fv, 0u, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, ic);
    lod_generate_levels_skinned(fv, vc, idx, 0u, poses, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, 0u);
    lod_generate_levels_skinned(fv, vc, idx, ic - 1u, poses, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, ic - 1u);
    lod_generate_levels_skinned(fv, vc, idx, ic, poses, 2u, 0u, 3u, &lv);
    assert_single_level(&lv, ic);
    lod_generate_levels_skinned(fv, vc, idx, ic, poses, 2u, LOD_SKIN_MAX_JOINTS + 1u, 3u, &lv);
    assert_single_level(&lv, ic);
    lod_generate_levels_skinned(fv, vc, idx, ic, NULL, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, ic);
    lod_generate_levels_skinned(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 1u, &lv);
    assert_single_level(&lv, ic);
    lod_generate_levels_skinned(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, NULL);
    u32 saved = idx[7];
    idx[7] = vc;
    lod_generate_levels_skinned(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, ic);
    idx[7] = saved;
    Mat4 bad[2 * TUBE_JOINTS];
    memcpy(bad, poses, sizeof(bad));
    bad[4].e[1][2] = NAN;
    lod_generate_levels_skinned(fv, vc, idx, ic, bad, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, ic);
    f32 saved_pos = v[3].pos[1];
    v[3].pos[1] = INFINITY;
    lod_generate_levels_skinned(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &lv);
    assert_single_level(&lv, ic);
    v[3].pos[1] = saved_pos;
    ASSERT_FALSE(lod_skin_positions(fv, vc, poses, 0u, NULL));

    /* Out-of-range joints (clamped) and zero weights (bind position) still
     * produce valid levels. */
    for (u32 i = 0; i < vc; i += 7u) { v[i].joints[0] = 1000u; v[i].joints[1] = 0xFFFFFFFFu; }
    for (u32 i = 3; i < vc; i += 11u) memset(v[i].weights, 0, sizeof(v[i].weights));
    lod_generate_levels_skinned(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &lv);
    ASSERT_TRUE(lv.level_count >= 2u);
    for (u32 l = 1; l < lv.level_count; l++) {
        for (u32 i = 0; i < lv.index_count[l]; i++) ASSERT_TRUE(lv.indices[l][i] < vc);
        ASSERT_TRUE(isfinite(lv.rel_error[l]));
    }
    lod_mesh_levels_free(&lv);
    lod_generate_levels_skinned(fv, vc, idx, ic, NULL, 0u, TUBE_JOINTS, 3u, &lv);
    ASSERT_TRUE(lv.level_count >= 1u);
    lod_mesh_levels_free(&lv);
    LodSphere js[TUBE_JOINTS];
    lod_skin_joint_spheres(fv, vc, TUBE_JOINTS, js);
    Mat4 mats[TUBE_JOINTS];
    chain_pose(0.8f, -0.6f, mats);
    LodSphere b = lod_skin_bounds(js, TUBE_JOINTS, mats);
    f32 *p = skinned(v, vc, mats);
    ASSERT_NOT_NULL(p);
    for (u32 i = 0; i < vc; i++) {
        f32 s = v[i].weights[0] + v[i].weights[1] + v[i].weights[2] + v[i].weights[3];
        if (!(s > 0.0f)) continue;
        f32 dx = p[i * 3u] - b.c[0], dy = p[i * 3u + 1u] - b.c[1], dz = p[i * 3u + 2u] - b.c[2];
        if (!(sqrtf(dx * dx + dy * dy + dz * dz) <= b.r)) { free(p); ASSERT_TRUE(false); }
    }
    free(p);
    lod_skin_joint_spheres(NULL, vc, TUBE_JOINTS, js);
    for (u32 j = 0; j < TUBE_JOINTS; j++) ASSERT_TRUE(js[j].r < 0.0f);
    free(v); free(idx);
}

TEST(lod_skin_cache_key_covers_poses_and_round_trips) {
    char dir[1024]; test_tmp(dir, sizeof(dir), "lod_skin_cache");
    TEST_MKDIR(dir);
    TestSkinVertex *v; u32 vc, ic; u32 *idx;
    make_tube(48u, 24u, &v, &vc, &idx, &ic);
    const f32 *fv = (const f32 *)v;
    Mat4 poses[2 * TUBE_JOINTS];
    chain_pose(0.9f, 0.0f, poses);
    chain_pose(0.3f, -0.9f, poses + TUBE_JOINTS);
    LodCacheKey k = lod_skin_cache_key(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u);
    LodCacheKey s = lod_cache_key(fv, vc, LOD_SKIN_VERTEX_STRIDE, idx, ic, 3u);
    ASSERT_TRUE(k.first != s.first || k.second != s.second);
    LodCacheKey k0 = lod_skin_cache_key(fv, vc, idx, ic, NULL, 0u, TUBE_JOINTS, 3u);
    ASSERT_TRUE(k0.first != s.first || k0.second != s.second);
    ASSERT_TRUE(k0.first != k.first || k0.second != k.second);
    LodCacheKey k1 = lod_skin_cache_key(fv, vc, idx, ic, poses, 1u, TUBE_JOINTS, 3u);
    ASSERT_TRUE(k1.first != k.first || k1.second != k.second);
    LodCacheKey kj = lod_skin_cache_key(fv, vc, idx, ic, poses, 1u, TUBE_JOINTS + 1u, 3u);
    ASSERT_TRUE(kj.first != k1.first || kj.second != k1.second);
    poses[4].e[3][1] += 0.001f;
    LodCacheKey kp = lod_skin_cache_key(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u);
    ASSERT_TRUE(kp.first != k.first || kp.second != k.second);
    poses[4].e[3][1] -= 0.001f;
    LodCacheKey again = lod_skin_cache_key(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u);
    ASSERT_TRUE(again.first == k.first && again.second == k.second);

    char path[1024];
    ASSERT_TRUE(lod_cache_path(path, sizeof(path), dir, k));
    remove(path);
    LodMeshLevels want;
    lod_generate_levels_skinned(fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &want);
    ASSERT_TRUE(want.level_count >= 2u);
    LodCache c; lod_cache_init(&c, dir);
    LodMeshLevels cold, warm;
    lod_skin_cache_generate(&c, fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &cold);
    ASSERT_EQ(c.stats.misses, 1u);
    ASSERT_TRUE(c.stats.write_bytes > 0u);
    lod_skin_cache_generate(&c, fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &warm);
    ASSERT_EQ(c.stats.hits, 1u);
    const LodMeshLevels *got[2] = { &cold, &warm };
    for (u32 g = 0; g < 2u; g++) {
        ASSERT_EQ(got[g]->level_count, want.level_count);
        ASSERT_EQ(got[g]->scale, want.scale);
        for (u32 l = 0; l < want.level_count; l++) {
            ASSERT_EQ(got[g]->index_count[l], want.index_count[l]);
            ASSERT_EQ(got[g]->rel_error[l], want.rel_error[l]);
            if (l > 0u)
                ASSERT_EQ(memcmp(got[g]->indices[l], want.indices[l],
                                 want.index_count[l] * sizeof(u32)), 0);
        }
    }
    /* A different pose set misses (separate file) instead of reusing. */
    LodMeshLevels other;
    lod_skin_cache_generate(&c, fv, vc, idx, ic, poses, 1u, TUBE_JOINTS, 3u, &other);
    ASSERT_EQ(c.stats.misses, 2u);
    ASSERT_EQ(c.stats.hits, 1u);
    char other_path[1024];
    ASSERT_TRUE(lod_cache_path(other_path, sizeof(other_path), dir, k1));
    lod_mesh_levels_free(&other);
    /* No directory: direct generation. */
    LodCache off; lod_cache_init(&off, NULL);
    LodMeshLevels direct;
    lod_skin_cache_generate(&off, fv, vc, idx, ic, poses, 2u, TUBE_JOINTS, 3u, &direct);
    ASSERT_EQ(direct.level_count, want.level_count);
    ASSERT_EQ(off.stats.hits + off.stats.misses, 0u);
    lod_mesh_levels_free(&direct);
    /* Invalid input through the cache path still falls back. */
    LodMeshLevels bad;
    lod_skin_cache_generate(&c, fv, vc, idx, ic, poses, 2u, 0u, 3u, &bad);
    ASSERT_EQ(bad.level_count, 1u);
    lod_mesh_levels_free(&bad);
    lod_mesh_levels_free(&cold); lod_mesh_levels_free(&warm); lod_mesh_levels_free(&want);
    remove(path); remove(other_path); TEST_RMDIR(dir);
    free(v); free(idx);
}

TEST(lod_skin_generation_time_20k_triangles_8_poses) {
    TestSkinVertex *v; u32 vc, ic; u32 *idx;
    make_tube(160u, 64u, &v, &vc, &idx, &ic);
    Mat4 poses[8 * TUBE_JOINTS];
    for (u32 p = 0; p < 8u; p++)
        chain_pose(0.2f * (f32)p, -0.15f * (f32)p, &poses[p * TUBE_JOINTS]);
    f64 t0 = now_ms();
    LodMeshLevels lv;
    lod_generate_levels_skinned((const f32 *)v, vc, idx, ic, poses, 8u, TUBE_JOINTS, 3u, &lv);
    f64 ms = now_ms() - t0;
    f64 t1 = now_ms();
    LodMeshLevels st;
    lod_generate_levels((const f32 *)v, vc, LOD_SKIN_VERTEX_STRIDE, idx, ic, 3u, &st);
    f64 static_ms = now_ms() - t1;
    printf("(%u tris: skinned %.1f ms [L1 %u L2 %u idx, rel %.4f %.4f], static %.1f ms) ",
           ic / 3u, ms, lv.index_count[1], lv.index_count[2], (double)lv.rel_error[1],
           (double)lv.rel_error[2], static_ms);
    ASSERT_TRUE(lv.level_count >= 2u);
    ASSERT_TRUE(ms < 10000.0);
    lod_mesh_levels_free(&lv); lod_mesh_levels_free(&st);
    free(v); free(idx);
}

TEST_MAIN_BEGIN()
    RUN_TEST(lod_skin_levels_reference_original_vertices_and_keep_skin_data);
    RUN_TEST(lod_skin_multi_pose_beats_bind_only_in_bent_pose);
    RUN_TEST(lod_skin_more_than_eight_poses_are_subsampled);
    RUN_TEST(lod_skin_no_poses_locks_dominant_joint_boundaries);
    RUN_TEST(lod_skin_bounds_contain_skinned_vertices_for_random_poses);
    RUN_TEST(lod_skin_invalid_input_falls_back_to_lod0);
    RUN_TEST(lod_skin_cache_key_covers_poses_and_round_trips);
    RUN_TEST(lod_skin_generation_time_20k_triangles_8_poses);
TEST_MAIN_END()
