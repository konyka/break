#include "test_framework.h"
#include <renderer/lod_cache.h>
#ifndef _WIN32
#include <sys/stat.h>
#endif

static void make_mesh(f32 **out_v, u32 *out_vc, u32 **out_i, u32 *out_ic) {
    const u32 sectors = 64u, rings = 48u, stride = 10u;
    u32 vc = (rings + 1u) * (sectors + 1u), ic = rings * sectors * 6u;
    f32 *v = (f32 *)calloc((usize)vc * stride, sizeof(f32));
    u32 *idx = (u32 *)malloc((usize)ic * sizeof(u32));
    u32 k = 0;
    for (u32 ri = 0; ri <= rings; ri++) {
        f32 phi = (f32)ri / (f32)rings * 3.14159265f;
        for (u32 si = 0; si <= sectors; si++) {
            f32 th = (f32)si / (f32)sectors * 6.2831853f;
            f32 nx = sinf(phi) * cosf(th), ny = cosf(phi), nz = sinf(phi) * sinf(th);
            f32 r = 1.0f + 0.05f * sinf(7.0f * th) * sinf(5.0f * phi);
            f32 *p = &v[k++ * stride];
            p[0] = nx * r; p[1] = ny * r; p[2] = nz * r;
            p[3] = nx; p[4] = ny; p[5] = nz;
            p[6] = (f32)si / (f32)sectors; p[7] = (f32)ri / (f32)rings;
        }
    }
    u32 n = 0;
    for (u32 ri = 0; ri < rings; ri++)
        for (u32 si = 0; si < sectors; si++) {
            u32 a = ri * (sectors + 1u) + si, b = a + sectors + 1u;
            idx[n++] = a; idx[n++] = b; idx[n++] = a + 1u;
            idx[n++] = a + 1u; idx[n++] = b; idx[n++] = b + 1u;
        }
    *out_v = v; *out_vc = vc; *out_i = idx; *out_ic = ic;
}

static void fresh(const f32 *v, u32 vc, const u32 *idx, u32 ic, LodMeshLevels *out) {
    lod_generate_levels(v, vc, 40u, idx, ic, LOD_GEN_MAX_LEVELS, out);
}

static void assert_same(const LodMeshLevels *a, const LodMeshLevels *b) {
    ASSERT_EQ(a->level_count, b->level_count);
    ASSERT_EQ(a->scale, b->scale);
    for (u32 l = 0; l < LOD_GEN_MAX_LEVELS; l++) {
        ASSERT_EQ(a->index_count[l], b->index_count[l]);
        ASSERT_EQ(a->rel_error[l], b->rel_error[l]);
        if (l < a->level_count && l > 0u)
            ASSERT_EQ(memcmp(a->indices[l], b->indices[l], a->index_count[l] * sizeof(u32)), 0);
    }
}

static void cache_file(char *out, usize cap, const char *dir,
                       const f32 *v, u32 vc, const u32 *idx, u32 ic) {
    LodCacheKey key = lod_cache_key(v, vc, 40u, idx, ic, LOD_GEN_MAX_LEVELS);
    ASSERT_TRUE(lod_cache_path(out, cap, dir, key));
}

static u8 *read_file(const char *path, usize *size) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n < 0) { fclose(f); return NULL; }
    u8 *data = (u8 *)malloc((usize)n + 1u);
    if (data && fread(data, 1, (usize)n, f) != (usize)n) { free(data); data = NULL; }
    fclose(f);
    *size = (usize)n;
    return data;
}

static bool write_file(const char *path, const u8 *data, usize size) {
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    bool ok = fwrite(data, 1, size, f) == size;
    fclose(f);
    return ok;
}

static void regenerate_from_file(LodCache *cache, const char *path,
                                 const f32 *v, u32 vc, const u32 *idx, u32 ic,
                                 const LodMeshLevels *expected) {
    LodMeshLevels got;
    lod_cache_generate(cache, v, vc, 40u, idx, ic, LOD_GEN_MAX_LEVELS, &got);
    assert_same(&got, expected);
    lod_mesh_levels_free(&got);
    (void)path;
}

TEST(lod_cache_key_covers_mesh_counts_stride_and_levels) {
    f32 *v; u32 vc, ic; u32 *idx;
    make_mesh(&v, &vc, &idx, &ic);
    LodCacheKey k = lod_cache_key(v, vc, 40u, idx, ic, 3u);
    ASSERT_NEQ(lod_cache_key(v, vc - 1u, 40u, idx, ic, 3u).first, k.first);
    ASSERT_NEQ(lod_cache_key(v, vc, 32u, idx, ic, 3u).second, k.second);
    ASSERT_NEQ(lod_cache_key(v, vc, 40u, idx, ic - 3u, 3u).first, k.first);
    ASSERT_NEQ(lod_cache_key(v, vc, 40u, idx, ic, 2u).second, k.second);
    v[0] += 0.25f;
    ASSERT_NEQ(lod_cache_key(v, vc, 40u, idx, ic, 3u).first, k.first);
    v[0] -= 0.25f;
    idx[0] = idx[0] == 0u ? 1u : 0u;
    ASSERT_NEQ(lod_cache_key(v, vc, 40u, idx, ic, 3u).second, k.second);
    free(v); free(idx);
}

TEST(lod_cache_round_trip_is_identical_and_second_run_hits) {
    char dir[512]; test_tmp(dir, sizeof(dir), "lod_cache_round");
    TEST_MKDIR(dir);
    f32 *v; u32 vc, ic; u32 *idx;
    make_mesh(&v, &vc, &idx, &ic);
    LodMeshLevels want; fresh(v, vc, idx, ic, &want);
    ASSERT_TRUE(want.level_count > 1u);
    char path[1024]; cache_file(path, sizeof(path), dir, v, vc, idx, ic);
    remove(path);
    LodCache c; lod_cache_init(&c, dir);
    LodMeshLevels cold; lod_cache_generate(&c, v, vc, 40u, idx, ic, 3u, &cold);
    assert_same(&cold, &want);
    ASSERT_EQ(c.stats.misses, 1u); ASSERT_EQ(c.stats.hits, 0u);
    ASSERT_TRUE(c.stats.write_bytes > 0u);
    LodMeshLevels warm; lod_cache_generate(&c, v, vc, 40u, idx, ic, 3u, &warm);
    assert_same(&warm, &want);
    ASSERT_EQ(c.stats.hits, 1u); ASSERT_EQ(c.stats.misses, 1u);
    ASSERT_EQ(c.stats.read_bytes, c.stats.write_bytes);
    ASSERT_TRUE(c.stats.saved_ms > 0.0);
    lod_mesh_levels_free(&cold); lod_mesh_levels_free(&warm); lod_mesh_levels_free(&want);
    remove(path); TEST_RMDIR(dir); free(v); free(idx);
}

TEST(lod_cache_rejects_truncation_magic_version_and_mismatch) {
    char dir[512]; test_tmp(dir, sizeof(dir), "lod_cache_corrupt");
    TEST_MKDIR(dir);
    f32 *v; u32 vc, ic; u32 *idx;
    make_mesh(&v, &vc, &idx, &ic);
    LodMeshLevels want; fresh(v, vc, idx, ic, &want);
    char path[1024]; cache_file(path, sizeof(path), dir, v, vc, idx, ic);
    remove(path);
    LodCache c; lod_cache_init(&c, dir);
    LodMeshLevels seed; lod_cache_generate(&c, v, vc, 40u, idx, ic, 3u, &seed);
    lod_mesh_levels_free(&seed);
    usize size = 0; u8 *good = read_file(path, &size);
    ASSERT_NOT_NULL(good);
    const usize cuts[] = { 0u, 1u, 79u, 80u, 81u };
    for (u32 i = 0; i < sizeof(cuts) / sizeof(cuts[0]); i++) {
        ASSERT_TRUE(write_file(path, good, cuts[i]));
        regenerate_from_file(&c, path, v, vc, idx, ic, &want);
    }
    ASSERT_TRUE(write_file(path, good, size - 1u));
    regenerate_from_file(&c, path, v, vc, idx, ic, &want);
    u8 *bad = (u8 *)malloc(size);
    const usize offsets[] = { 0u, 8u, 16u, 60u, 72u, 80u };
    for (u32 i = 0; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        memcpy(bad, good, size); bad[offsets[i]] ^= 0x5Au;
        ASSERT_TRUE(write_file(path, bad, size));
        regenerate_from_file(&c, path, v, vc, idx, ic, &want);
    }
    memcpy(bad, good, size);
    usize first = LOD_CACHE_HEADER_SIZE + 8u * want.level_count;
    bad[first] = 0xFFu; bad[first + 1] = 0xFFu; bad[first + 2] = 0xFFu; bad[first + 3] = 0xFFu;
    ASSERT_TRUE(write_file(path, bad, size));
    regenerate_from_file(&c, path, v, vc, idx, ic, &want);
    free(bad); free(good);
    remove(path); TEST_RMDIR(dir); free(v); free(idx);
}

TEST(lod_cache_unwritable_directory_falls_back) {
    char dir[512]; test_tmp(dir, sizeof(dir), "lod_cache_missing/nested");
    f32 *v; u32 vc, ic; u32 *idx;
    make_mesh(&v, &vc, &idx, &ic);
    LodMeshLevels want; fresh(v, vc, idx, ic, &want);
    LodCache c; lod_cache_init(&c, dir);
    LodMeshLevels got; lod_cache_generate(&c, v, vc, 40u, idx, ic, 3u, &got);
    assert_same(&got, &want);
    ASSERT_TRUE(c.stats.io_failed);
    ASSERT_EQ(c.stats.hits, 0u);
    lod_mesh_levels_free(&got); lod_mesh_levels_free(&want); free(v); free(idx);
}

TEST(lod_cache_second_writer_leaves_valid_file_and_off_has_no_io) {
    char dir[512]; test_tmp(dir, sizeof(dir), "lod_cache_writers");
    TEST_MKDIR(dir);
    f32 *v; u32 vc, ic; u32 *idx;
    make_mesh(&v, &vc, &idx, &ic);
    LodMeshLevels want; fresh(v, vc, idx, ic, &want);
    char path[1024]; cache_file(path, sizeof(path), dir, v, vc, idx, ic);
    remove(path);
    LodCache a, b; lod_cache_init(&a, dir); lod_cache_init(&b, dir);
    LodMeshLevels la, lb;
    lod_cache_generate(&a, v, vc, 40u, idx, ic, 3u, &la);
    lod_cache_generate(&b, v, vc, 40u, idx, ic, 3u, &lb);
    lod_mesh_levels_free(&la); lod_mesh_levels_free(&lb);
    LodCache c; lod_cache_init(&c, dir);
    LodMeshLevels got; lod_cache_generate(&c, v, vc, 40u, idx, ic, 3u, &got);
    assert_same(&got, &want);
    ASSERT_EQ(c.stats.hits, 1u);
    lod_mesh_levels_free(&got);
    LodCache off; lod_cache_init(&off, "");
    lod_cache_generate(&off, v, vc, 40u, idx, ic, 3u, &got);
    assert_same(&got, &want);
    ASSERT_EQ(off.stats.hits + off.stats.misses + off.stats.read_bytes + off.stats.write_bytes, 0u);
    lod_mesh_levels_free(&got); lod_mesh_levels_free(&want);
    remove(path); TEST_RMDIR(dir); free(v); free(idx);
}

TEST_MAIN_BEGIN()
    RUN_TEST(lod_cache_key_covers_mesh_counts_stride_and_levels);
    RUN_TEST(lod_cache_round_trip_is_identical_and_second_run_hits);
    RUN_TEST(lod_cache_rejects_truncation_magic_version_and_mismatch);
    RUN_TEST(lod_cache_unwritable_directory_falls_back);
    RUN_TEST(lod_cache_second_writer_leaves_valid_file_and_off_has_no_io);
TEST_MAIN_END()
