/* Scene texture model: the kept RESOURCES chunk of a loaded BSCN, read-only.
 * Pure CPU. Real BSCN bytes from scene_save_binary, plus hand-built v1/v2
 * layouts and malformed chunks. */

#include "test_framework.h"

#include <editor/editor_doc.h>
#include <editor/editor_scene.h>
#include <editor/editor_scene_textures.h>

#include <asset/asset.h>
#include <ecs/ecs.h>
#include <scene/scene_serial.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void tmp_path(char *out, usize cap, const char *name) {
    const char *dir = getenv("TMPDIR");
    snprintf(out, cap, "%s/%s", dir && dir[0] ? dir : "/tmp", name);
}

/* A scene with two textures (uris a.png / b.png) and two materials: material
 * 0 uses a.png as albedo and b.png as normal map; material 1 uses b.png as
 * albedo. Texture handles carry arbitrary indices (7 and 9) like real glTF
 * loads. Returns false on a save failure. */
static bool save_textured_scene(const char *path) {
    World *w = world_create();
    Scene s;
    SerializeOptions opts;
    bool ok;
    if (!w) return false;
    memset(&s, 0, sizeof(s));
    s.material_count = 2;
    s.materials = (Material *)calloc(2, sizeof(Material));
    s.texture_source_count = 2;
    s.texture_sources = (SceneTextureSource *)calloc(2, sizeof(SceneTextureSource));
    if (!s.materials || !s.texture_sources) return false;
    s.texture_sources[0].handle_index = 7;
    snprintf(s.texture_sources[0].uri, sizeof(s.texture_sources[0].uri), "a.png");
    s.texture_sources[1].handle_index = 9;
    snprintf(s.texture_sources[1].uri, sizeof(s.texture_sources[1].uri), "sub/b.png");
    s.materials[0].albedo.index = 7;
    s.materials[0].albedo.generation = 1;
    s.materials[0].normal_map.index = 9;
    s.materials[0].normal_map.generation = 1;
    s.materials[1].albedo.index = 9;
    s.materials[1].albedo.generation = 1;
    for (int m = 0; m < 2; m++) {
        s.materials[m].base_color[0] = s.materials[m].base_color[1] =
            s.materials[m].base_color[2] = s.materials[m].base_color[3] = 1.0f;
        s.materials[m].metallic_factor = 1.0f;
        s.materials[m].roughness_factor = 1.0f;
        s.materials[m].occlusion_strength = 1.0f;
        s.materials[m].alpha_cutoff = 0.5f;
    }
    memset(&opts, 0, sizeof(opts));
    opts.include_resources = true;
    ok = scene_save_binary(w, &s, path, &opts);
    free(s.materials);
    free(s.texture_sources);
    world_destroy(w);
    return ok;
}

static BreakEditorDoc *doc_from(const char *path) {
    BreakEditorDoc *doc = break_editor_doc_create();
    if (doc && !break_editor_doc_load(doc, path)) {
        break_editor_doc_destroy(doc);
        return NULL;
    }
    return doc;
}

TEST(parse_reads_textures_and_material_links_from_a_real_bscn) {
    char path[512];
    BreakEditorSceneTexture tex[BREAK_EDITOR_SCENE_TEXTURES_MAX];
    BreakEditorSceneMaterial mat[8];
    u32 mat_total = 0;
    tmp_path(path, sizeof(path), "scene_tex_real.bscn");
    ASSERT_TRUE(save_textured_scene(path));
    BreakEditorDoc *doc = doc_from(path);
    ASSERT_NOT_NULL(doc);

    u32 n = break_editor_scene_textures_parse(doc, tex, BREAK_EDITOR_SCENE_TEXTURES_MAX,
                                              mat, 8, &mat_total);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(mat_total, 2u);
    ASSERT_STR_EQ(tex[0].path, "a.png");
    ASSERT_STR_EQ(tex[1].path, "sub/b.png");
    ASSERT_EQ(tex[0].ref_index, 7u);
    ASSERT_EQ(tex[1].ref_index, 9u);
    /* a.png: albedo of material 0 -> 1 user; b.png: normal of 0 + albedo of 1 -> 2 */
    ASSERT_EQ(tex[0].used_by_materials, 1u);
    ASSERT_EQ(tex[1].used_by_materials, 2u);
    ASSERT_EQ(mat[0].slot_texture[0], 7u);   /* albedo */
    ASSERT_EQ(mat[0].slot_texture[2], 9u);   /* normal */
    ASSERT_EQ(mat[0].slot_texture[1], 0xffffffffu); /* no metallic-roughness */
    ASSERT_EQ(mat[1].slot_texture[0], 9u);
    break_editor_doc_destroy(doc);
    remove(path);
}

TEST(parse_without_resources_or_with_null_args_is_zero) {
    BreakEditorSceneTexture tex[4];
    BreakEditorSceneMaterial mat[2];
    u32 mat_total = 99;
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_editor_scene_textures_parse(doc, tex, 4, mat, 2, &mat_total), 0u);
    ASSERT_EQ(mat_total, 0u);
    ASSERT_EQ(break_editor_scene_textures_parse(NULL, tex, 4, mat, 2, &mat_total), 0u);
    ASSERT_EQ(break_editor_scene_textures_parse(doc, NULL, 4, mat, 2, &mat_total), 0u);
    ASSERT_EQ(break_editor_scene_textures_parse(doc, tex, 0, mat, 2, &mat_total), 0u);
    /* optional outputs may be NULL */
    ASSERT_EQ(break_editor_scene_textures_parse(doc, tex, 4, NULL, 0, NULL), 0u);
    break_editor_doc_destroy(doc);
}

TEST(parse_truncates_to_the_caller_capacity_without_overflow) {
    char path[512];
    BreakEditorSceneTexture tex[1];
    BreakEditorSceneMaterial mat[1];
    u32 mat_total = 0;
    tmp_path(path, sizeof(path), "scene_tex_cap.bscn");
    ASSERT_TRUE(save_textured_scene(path));
    BreakEditorDoc *doc = doc_from(path);
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_editor_scene_textures_parse(doc, tex, 1, mat, 1, &mat_total), 1u);
    ASSERT_STR_EQ(tex[0].path, "a.png");
    ASSERT_EQ(mat_total, 2u); /* the true total is still reported */
    break_editor_doc_destroy(doc);
    remove(path);
}

/* path rules */
TEST(path_ok_accepts_relative_names_and_rejects_everything_else) {
    ASSERT_TRUE(break_editor_scene_texture_path_ok("a.png"));
    ASSERT_TRUE(break_editor_scene_texture_path_ok("sub/dir/b-1_2.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok(""));
    ASSERT_FALSE(break_editor_scene_texture_path_ok(NULL));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("/etc/passwd"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("../x.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("a/../x.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("a/.."));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("a\\b.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("C:/x.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("a//b.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("a\tb.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("a\nb.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("a\x7f.png"));
    ASSERT_FALSE(break_editor_scene_texture_path_ok("caf\xc3\xa9.png")); /* ASCII only */
    {
        char longp[80];
        memset(longp, 'a', sizeof(longp));
        longp[63] = '\0';
        ASSERT_TRUE(break_editor_scene_texture_path_ok(longp));
        longp[64] = '\0';
        longp[63] = 'a';
        ASSERT_FALSE(break_editor_scene_texture_path_ok(longp)); /* 64 chars: over */
    }
}

TEST(resolve_joins_against_the_scene_directory) {
    char out[128];
    ASSERT_TRUE(break_editor_scene_texture_resolve("/proj/scenes/level.bscn", "a.png", out, sizeof(out)));
    ASSERT_STR_EQ(out, "/proj/scenes/a.png");
    ASSERT_TRUE(break_editor_scene_texture_resolve("/proj/scenes/level.bscn", "sub/b.png", out, sizeof(out)));
    ASSERT_STR_EQ(out, "/proj/scenes/sub/b.png");
    /* a scene path without a directory is not absolute: refuse (the image
     * preview needs an absolute path) */
    ASSERT_FALSE(break_editor_scene_texture_resolve("level.bscn", "a.png", out, sizeof(out)));
    ASSERT_FALSE(break_editor_scene_texture_resolve("./level.bscn", "a.png", out, sizeof(out)));
    ASSERT_FALSE(break_editor_scene_texture_resolve("/proj/level.bscn", "../a.png", out, sizeof(out)));
    ASSERT_FALSE(break_editor_scene_texture_resolve("/proj/level.bscn", "/abs.png", out, sizeof(out)));
    ASSERT_FALSE(break_editor_scene_texture_resolve(NULL, "a.png", out, sizeof(out)));
    ASSERT_FALSE(break_editor_scene_texture_resolve("/proj/level.bscn", NULL, out, sizeof(out)));
    ASSERT_FALSE(break_editor_scene_texture_resolve("/proj/level.bscn", "a.png", NULL, 0));
    /* too small: refused, not truncated */
    ASSERT_FALSE(break_editor_scene_texture_resolve("/proj/scenes/level.bscn", "a.png", out, 10));
    ASSERT_FALSE(break_editor_scene_texture_resolve("/proj/scenes/level.bscn", "a.png", out, strlen("/proj/scenes/a.png")));
    ASSERT_TRUE(break_editor_scene_texture_resolve("/proj/scenes/level.bscn", "a.png", out, strlen("/proj/scenes/a.png") + 1u));
}


/* ---- hand-built RESOURCES chunks inside an otherwise real BSCN ---- */

typedef struct { u8 *p; usize n; usize cap; } Buf;
static void b_put(Buf *b, const void *d, usize n) {
    if (b->n + n > b->cap) return;
    memcpy(b->p + b->n, d, n);
    b->n += n;
}
static void b_u32(Buf *b, u32 v) { b_put(b, &v, 4); }
static void b_u64(Buf *b, u64 v) { b_put(b, &v, 8); }
static void b_f32z(Buf *b, u32 n) { for (u32 i = 0; i < n; i++) b_u32(b, 0); }

/* one entry; layout follows the file version like the real writer */
static void b_entry(Buf *b, u32 version, u32 type, u32 ref, bool inline_desc,
                    const u32 slots[5], const char *path, u32 declared_plen) {
    b_u64(b, 0x1234u);
    b_u32(b, type);
    b_u32(b, ref);
    b_u32(b, inline_desc ? 1u : 0u);
    if (inline_desc) {
        b_f32z(b, 3);                       /* u0..u2 */
        if (version == BSCN_VERSION) {
            for (int i = 0; i < 5; i++) b_u32(b, slots ? slots[i] : 0xffffffffu);
        }
        b_f32z(b, version == BSCN_VERSION_V1 ? 8u : 12u);
    }
    b_u32(b, declared_plen);
    b_put(b, path, strlen(path) < declared_plen ? strlen(path) : declared_plen);
    for (usize i = strlen(path); i < declared_plen; i++) { u8 z = 'x'; b_put(b, &z, 1); }
}

/* Re-wraps a real BSCN: same chunks except RESOURCES, header version forced. */
static bool rewrap(const u8 *file, usize size, u32 version, const u8 *res,
                   u32 res_size, u8 *out, usize cap, usize *out_size) {
    BscnHeader h;
    BscnChunkEntry in_t[16], out_t[16];
    const u8 *src[16];
    u32 srcs[16];
    usize at;
    if (size < sizeof(h)) return false;
    memcpy(&h, file, sizeof(h));
    if (h.chunk_count == 0 || h.chunk_count > 16) return false;
    memcpy(in_t, file + sizeof(h), sizeof(BscnChunkEntry) * h.chunk_count);
    for (u32 i = 0; i < h.chunk_count; i++) {
        if (in_t[i].type == BSCN_CHUNK_RESOURCES) { src[i] = res; srcs[i] = res_size; }
        else { src[i] = file + in_t[i].offset; srcs[i] = in_t[i].size; }
    }
    h.version = version;
    at = sizeof(h) + sizeof(BscnChunkEntry) * h.chunk_count;
    for (u32 i = 0; i < h.chunk_count; i++) {
        out_t[i] = in_t[i];
        out_t[i].size = srcs[i];
        out_t[i].offset = (u32)at;
        at += srcs[i];
    }
    if (at > cap) return false;
    memcpy(out, &h, sizeof(h));
    memcpy(out + sizeof(h), out_t, sizeof(BscnChunkEntry) * h.chunk_count);
    for (u32 i = 0; i < h.chunk_count; i++) {
        memcpy(out + out_t[i].offset, src[i], srcs[i]);
    }
    *out_size = at;
    return true;
}

static u8 g_file[1 << 16];
static u8 g_res[1 << 12];
static u8 g_new[1 << 16];

/* Loads `res` as the RESOURCES chunk of a BSCN of the given version. */
static BreakEditorDoc *doc_with_res(u32 version, const u8 *res, u32 res_size) {
    char path[512];
    FILE *f;
    usize n, out_n = 0;
    BreakEditorDoc *doc;
    tmp_path(path, sizeof(path), "scene_tex_base.bscn");
    if (!save_textured_scene(path)) return NULL;
    f = fopen(path, "rb");
    if (!f) return NULL;
    n = fread(g_file, 1, sizeof(g_file), f);
    fclose(f);
    remove(path);
    if (!rewrap(g_file, n, version, res, res_size, g_new, sizeof(g_new), &out_n)) return NULL;
    doc = break_editor_doc_create();
    if (!doc) return NULL;
    tmp_path(path, sizeof(path), "scene_tex_wrapped.bscn");
    if (!break_editor_doc_load_bytes(doc, path, g_new, out_n)) {
        break_editor_doc_destroy(doc);
        return NULL;
    }
    return doc;
}

TEST(older_layouts_parse_without_material_links) {
    for (u32 version = BSCN_VERSION_V1; version <= BSCN_VERSION_V2; version++) {
        Buf b = {g_res, 0, sizeof(g_res)};
        BreakEditorSceneTexture tex[4];
        BreakEditorSceneMaterial mat[2];
        u32 mat_total = 0;
        b_u32(&b, 3);
        b_entry(&b, version, BSCN_RES_TEXTURE, 5, false, NULL, "t.png", 5);
        b_entry(&b, version, BSCN_RES_MATERIAL, 0, true, NULL, "", 0);
        b_entry(&b, version, BSCN_RES_MESH, 0, true, NULL, "", 0);
        BreakEditorDoc *doc = doc_with_res(version, g_res, (u32)b.n);
        ASSERT_NOT_NULL(doc);
        ASSERT_EQ(break_editor_scene_textures_parse(doc, tex, 4, mat, 2, &mat_total), 1u);
        ASSERT_STR_EQ(tex[0].path, "t.png");
        ASSERT_EQ(tex[0].ref_index, 5u);
        ASSERT_EQ(tex[0].used_by_materials, 0u);   /* v1/v2 carry no links */
        ASSERT_EQ(mat_total, 1u);
        for (int i = 0; i < 5; i++) ASSERT_EQ(mat[0].slot_texture[i], 0xffffffffu);
        break_editor_doc_destroy(doc);
    }
}

TEST(path_longer_than_63_is_cut_like_the_game_loader_and_stays_in_bounds) {
    Buf b = {g_res, 0, sizeof(g_res)};
    BreakEditorSceneTexture tex[2];
    char long_path[120];
    memset(long_path, 'a', sizeof(long_path) - 1u);
    long_path[sizeof(long_path) - 1u] = '\0';
    b_u32(&b, 2);
    b_entry(&b, BSCN_VERSION, BSCN_RES_TEXTURE, 1, false, NULL, long_path, 100);
    b_entry(&b, BSCN_VERSION, BSCN_RES_TEXTURE, 2, false, NULL, "next.png", 8);
    BreakEditorDoc *doc = doc_with_res(BSCN_VERSION, g_res, (u32)b.n);
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_editor_scene_textures_parse(doc, tex, 2, NULL, 0, NULL), 2u);
    ASSERT_EQ(strlen(tex[0].path), 63u);
    ASSERT_STR_EQ(tex[1].path, "next.png"); /* the 37 skipped bytes did not shift the next entry */
    /* a 63+ char path is not openable */
    ASSERT_FALSE(break_editor_scene_texture_path_ok(tex[0].path) && strlen(tex[0].path) > 63u);
    break_editor_doc_destroy(doc);
}

static u32 parse_raw(const Buf *b, u32 version, u32 *mat_total) {
    BreakEditorSceneTexture tex[4];
    return break_editor_scene_textures_parse_chunk(b->p, (u32)b->n, version, tex,
                                                   4, NULL, 0, mat_total);
}

/* These chunks never reach a document (the game loader rejects the file), so
 * the chunk parser is fed directly; every one must give 0 and no partial data. */
TEST(malformed_resources_chunks_yield_nothing) {
    Buf b;
    u32 mat_total = 7;

    /* sanity: a well-formed chunk of the same construction parses */
    b = (Buf){g_res, 0, sizeof(g_res)};
    b_u32(&b, 1);
    b_entry(&b, BSCN_VERSION, BSCN_RES_TEXTURE, 1, false, NULL, "abc", 3);
    ASSERT_EQ(parse_raw(&b, BSCN_VERSION, &mat_total), 1u);

    /* count larger than the bytes can hold */
    b = (Buf){g_res, 0, sizeof(g_res)};
    b_u32(&b, 0x7fffffffu);
    ASSERT_EQ(parse_raw(&b, BSCN_VERSION, &mat_total), 0u);
    ASSERT_EQ(mat_total, 0u);

    /* declared entry cut short by the end of the chunk, at every length */
    b = (Buf){g_res, 0, sizeof(g_res)};
    b_u32(&b, 1);
    b_entry(&b, BSCN_VERSION, BSCN_RES_MATERIAL, 1, true, NULL, "abc", 3);
    {
        usize full = b.n;
        for (usize cut = 4u; cut < full; cut++) {
            Buf t = {g_res, cut, sizeof(g_res)};
            ASSERT_EQ(parse_raw(&t, BSCN_VERSION, &mat_total), 0u);
        }
    }

    /* path length claims more bytes than remain */
    b = (Buf){g_res, 0, sizeof(g_res)};
    b_u32(&b, 1);
    b_u64(&b, 1);
    b_u32(&b, BSCN_RES_TEXTURE);
    b_u32(&b, 1);
    b_u32(&b, 0);
    b_u32(&b, 0xfffffff0u);
    ASSERT_EQ(parse_raw(&b, BSCN_VERSION, &mat_total), 0u);

    /* trailing bytes after the last entry */
    b = (Buf){g_res, 0, sizeof(g_res)};
    b_u32(&b, 1);
    b_entry(&b, BSCN_VERSION, BSCN_RES_TEXTURE, 1, false, NULL, "abc", 3);
    b_u32(&b, 0xdeadbeefu);
    ASSERT_EQ(parse_raw(&b, BSCN_VERSION, &mat_total), 0u);

    /* unknown flag bits */
    b = (Buf){g_res, 0, sizeof(g_res)};
    b_u32(&b, 1);
    b_u64(&b, 1);
    b_u32(&b, BSCN_RES_TEXTURE);
    b_u32(&b, 1);
    b_u32(&b, 0x80u);
    b_u32(&b, 0);
    ASSERT_EQ(parse_raw(&b, BSCN_VERSION, &mat_total), 0u);

    /* unknown BSCN version, empty chunk, NULL chunk */
    b = (Buf){g_res, 0, sizeof(g_res)};
    b_u32(&b, 0);
    ASSERT_EQ(parse_raw(&b, 99u, &mat_total), 0u);
    ASSERT_EQ(parse_raw(&b, 0u, &mat_total), 0u);
    ASSERT_EQ(parse_raw(&b, BSCN_VERSION, &mat_total), 0u); /* valid but empty */
    {
        BreakEditorSceneTexture tex[1];
        ASSERT_EQ(break_editor_scene_textures_parse_chunk(NULL, 8, BSCN_VERSION, tex, 1, NULL, 0, &mat_total), 0u);
        ASSERT_EQ(break_editor_scene_textures_parse_chunk(g_res, 3, BSCN_VERSION, tex, 1, NULL, 0, &mat_total), 0u);
    }

    /* a v3 chunk read as v2 (or the reverse) is misaligned and rejected, not
     * misread: the version decides the descriptor size */
    b = (Buf){g_res, 0, sizeof(g_res)};
    b_u32(&b, 1);
    b_entry(&b, BSCN_VERSION, BSCN_RES_MATERIAL, 1, true, NULL, "", 0);
    ASSERT_EQ(parse_raw(&b, BSCN_VERSION_V2, &mat_total), 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(parse_reads_textures_and_material_links_from_a_real_bscn);
    RUN_TEST(parse_without_resources_or_with_null_args_is_zero);
    RUN_TEST(parse_truncates_to_the_caller_capacity_without_overflow);
    RUN_TEST(path_ok_accepts_relative_names_and_rejects_everything_else);
    RUN_TEST(resolve_joins_against_the_scene_directory);
    RUN_TEST(older_layouts_parse_without_material_links);
    RUN_TEST(path_longer_than_63_is_cut_like_the_game_loader_and_stays_in_bounds);
    RUN_TEST(malformed_resources_chunks_yield_nothing);
TEST_MAIN_END()
