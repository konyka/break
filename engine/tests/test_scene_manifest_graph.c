/* A loaded scene's resource manifest declared as an asset dependency graph:
 * textures <- materials <- meshes <- scene, with reload paths. */
#include "test_framework.h"

#include <asset/scene_manifest_graph.h>
#include <scene/scene_serial.h>

#include <stdio.h>
#include <string.h>

enum { kSceneId = 1000u };

static SceneResource res(u64 guid, u32 type, u32 ref_index) {
    SceneResource r;
    memset(&r, 0, sizeof(r));
    memset(r.tex_slots, 0xff, sizeof(r.tex_slots));
    r.guid = guid;
    r.type = type;
    r.ref_index = ref_index;
    return r;
}

/* textures 7 (albedo.png) and 9 (normal.png, no path for 9b);
 * material 0 uses 7 as albedo and 9 as normal, material 1 uses 7;
 * mesh 0 uses material 1, skinned mesh 0 uses material 0, mesh 1 has no
 * inline descriptor. */
static u32 sample(SceneResource *out) {
    u32 n = 0u;
    out[n] = res(101u, BSCN_RES_TEXTURE, 7u);
    snprintf(out[n++].path, sizeof(out[0].path), "albedo.png");
    out[n] = res(102u, BSCN_RES_TEXTURE, 9u);
    snprintf(out[n++].path, sizeof(out[0].path), "normal.png");
    out[n] = res(201u, BSCN_RES_MATERIAL, 0u);
    out[n].flags = 1u;
    out[n].tex_slots[0] = 7u;
    out[n++].tex_slots[2] = 9u;
    out[n] = res(202u, BSCN_RES_MATERIAL, 1u);
    out[n].flags = 1u;
    out[n++].tex_slots[0] = 7u;
    out[n] = res(301u, BSCN_RES_MESH, 0u);
    out[n].flags = 1u;
    out[n++].u2 = 1u;
    out[n] = res(302u, BSCN_RES_SKINNED_MESH, 0u);
    out[n].flags = 1u;
    out[n++].u2 = 0u;
    out[n++] = res(303u, BSCN_RES_MESH, 1u);
    out[n++] = res(900u, BSCN_RES_SCENE, 0u); /* ignored */
    return n;
}

typedef struct {
    BreakAssetId id[16];
    char path[16][BREAK_SCENE_MANIFEST_MAX_PATH];
    u32 count;
} Paths;

static void on_path(void *user, BreakAssetId id, const char *path) {
    Paths *p = (Paths *)user;
    if (p->count < 16u) {
        p->id[p->count] = id;
        snprintf(p->path[p->count], sizeof(p->path[0]), "%s", path);
        p->count++;
    }
}

static const char *path_of(const Paths *p, BreakAssetId id) {
    for (u32 i = 0u; i < p->count; ++i) {
        if (p->id[i] == id) return p->path[i];
    }
    return NULL;
}

static BreakAssetGraph *make(u32 capacity, u32 edges) {
    BreakAssetGraphConfig cfg;
    BreakAssetGraph *g = NULL;
    memset(&cfg, 0, sizeof cfg);
    cfg.capacity = capacity;
    cfg.max_edges = edges;
    return break_asset_graph_create(&cfg, &g) == BREAK_ASSET_GRAPH_OK ? g : NULL;
}

static BreakSceneManifestGraphConfig config(Paths *paths) {
    BreakSceneManifestGraphConfig c;
    memset(&c, 0, sizeof(c));
    c.scene_id = kSceneId;
    c.scene_path = "levels/hall.bscn";
    c.texture_base_dir = "levels/tex";
    c.path = paths ? on_path : NULL;
    c.path_user = paths;
    return c;
}

static i32 index_of(const BreakAssetId *list, u32 count, BreakAssetId id) {
    for (u32 i = 0u; i < count; ++i) {
        if (list[i] == id) return (i32)i;
    }
    return -1;
}

TEST(the_manifest_becomes_a_load_order_with_the_scene_last) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    BreakSceneManifestGraphConfig c = config(NULL);
    BreakSceneManifestGraphStats st;
    BreakAssetId order[16];
    u32 count = 0u;
    ASSERT_TRUE(g != NULL);
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(st.textures, 2u);
    ASSERT_EQ(st.materials, 2u);
    ASSERT_EQ(st.meshes, 3u);
    ASSERT_EQ(st.dangling_links, 0u);
    ASSERT_FALSE(break_asset_graph_contains(g, 900u));
    ASSERT_EQ(break_asset_graph_load_order(g, kSceneId, order, 16u, &count, NULL), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 8u);
    ASSERT_EQ(order[count - 1u], (BreakAssetId)kSceneId);
    ASSERT_TRUE(index_of(order, count, 101u) < index_of(order, count, 201u));
    ASSERT_TRUE(index_of(order, count, 102u) < index_of(order, count, 201u));
    ASSERT_TRUE(index_of(order, count, 101u) < index_of(order, count, 202u));
    ASSERT_TRUE(index_of(order, count, 202u) < index_of(order, count, 301u));
    ASSERT_TRUE(index_of(order, count, 201u) < index_of(order, count, 302u));
    ASSERT_TRUE(index_of(order, count, 303u) >= 0);
    break_asset_graph_destroy(g);
}

TEST(a_changed_texture_lists_its_materials_meshes_and_the_scene) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    BreakSceneManifestGraphConfig c = config(NULL);
    BreakSceneManifestGraphStats st;
    BreakAssetId out[16];
    u32 count = 0u;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    /* normal.png: material 0, skinned mesh 0, scene */
    ASSERT_EQ(break_asset_graph_dependents(g, 102u, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_EQ(out[0], 201u);
    ASSERT_EQ(out[1], 302u);
    ASSERT_EQ(out[2], (BreakAssetId)kSceneId);
    /* albedo.png reaches both materials and both described meshes */
    ASSERT_EQ(break_asset_graph_dependents(g, 101u, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 5u);
    ASSERT_TRUE(index_of(out, count, 303u) < 0);
    break_asset_graph_destroy(g);
}

TEST(each_id_reports_the_file_it_reloads_from) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    Paths paths;
    BreakSceneManifestGraphConfig c;
    BreakSceneManifestGraphStats st;
    memset(&paths, 0, sizeof(paths));
    c = config(&paths);
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(paths.count, 8u);
    ASSERT_STR_EQ(path_of(&paths, 101u), "levels/tex/albedo.png");
    ASSERT_STR_EQ(path_of(&paths, 102u), "levels/tex/normal.png");
    ASSERT_STR_EQ(path_of(&paths, 201u), "levels/hall.bscn");
    ASSERT_STR_EQ(path_of(&paths, 301u), "levels/hall.bscn");
    ASSERT_STR_EQ(path_of(&paths, (BreakAssetId)kSceneId), "levels/hall.bscn");
    /* no base dir: the entry path as-is; a texture without a path lives in
     * the scene file */
    r[1].path[0] = '\0';
    break_asset_graph_destroy(g);
    g = make(32u, 64u);
    memset(&paths, 0, sizeof(paths));
    c.texture_base_dir = NULL;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    ASSERT_STR_EQ(path_of(&paths, 101u), "albedo.png");
    ASSERT_STR_EQ(path_of(&paths, 102u), "levels/hall.bscn");
    break_asset_graph_destroy(g);
    g = make(32u, 64u);
    memset(&paths, 0, sizeof(paths));
    c.texture_base_dir = "";
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    ASSERT_STR_EQ(path_of(&paths, 101u), "albedo.png");
    break_asset_graph_destroy(g);
}

TEST(links_to_absent_entries_are_counted_and_left_out) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    BreakSceneManifestGraphConfig c = config(NULL);
    BreakSceneManifestGraphStats st;
    BreakAssetId order[16];
    u32 count = 0u;
    r[2].tex_slots[4] = 55u; /* no texture with ref_index 55 */
    r[4].u2 = 8u;            /* no material 8 */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(st.dangling_links, 2u);
    ASSERT_EQ(break_asset_graph_load_order(g, kSceneId, order, 16u, &count, NULL), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 8u);
    /* mesh 0 now needs nothing */
    ASSERT_EQ(break_asset_graph_load_order(g, 301u, order, 16u, &count, NULL), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 1u);
    break_asset_graph_destroy(g);
}

TEST(a_slot_naming_the_same_texture_twice_is_one_dependency) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    BreakSceneManifestGraphConfig c = config(NULL);
    BreakSceneManifestGraphStats st;
    BreakAssetGraphStats gs;
    r[2].tex_slots[1] = 7u; /* albedo and metallic-roughness from one image */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    break_asset_graph_stats(g, &gs);
    /* 201: 2, 202: 1, 301: 1, 302: 1, scene: 5 */
    ASSERT_EQ(gs.edges, 10u);
    break_asset_graph_destroy(g);
}

TEST(a_failed_build_leaves_the_graph_as_it_was) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(8u, 64u); /* room for 1 + 6 of the 8 */
    BreakSceneManifestGraphConfig c = config(NULL);
    BreakSceneManifestGraphStats st;
    BreakAssetGraphStats gs;
    Paths paths;
    ASSERT_EQ(break_asset_graph_add(g, 5u, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    memset(&paths, 0, sizeof(paths));
    c.path = on_path;
    c.path_user = &paths;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OVERLOAD);
    break_asset_graph_stats(g, &gs);
    ASSERT_EQ(gs.nodes, 1u);
    ASSERT_EQ(gs.edges, 0u);
    ASSERT_EQ(paths.count, 0u);
    break_asset_graph_destroy(g);
    /* too few edges */
    g = make(32u, 9u);
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OVERLOAD);
    break_asset_graph_stats(g, &gs);
    ASSERT_EQ(gs.nodes, 0u);
    ASSERT_EQ(gs.edges, 0u);
    break_asset_graph_destroy(g);
    /* an id already declared */
    g = make(32u, 64u);
    ASSERT_EQ(break_asset_graph_add(g, 202u, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_EXISTS);
    break_asset_graph_stats(g, &gs);
    ASSERT_EQ(gs.nodes, 1u);
    ASSERT_EQ(paths.count, 0u);
    break_asset_graph_destroy(g);
}

TEST(malformed_input_is_invalid) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    BreakSceneManifestGraphConfig c = config(NULL);
    BreakSceneManifestGraphStats st;
    BreakAssetGraphStats gs;
    char long_dir[BREAK_SCENE_MANIFEST_MAX_PATH];
    ASSERT_EQ(break_scene_manifest_graph_build(NULL, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, NULL, &st), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, NULL), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_scene_manifest_graph_build(&c, NULL, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    c.scene_id = 0u;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    c.scene_id = 201u; /* collides with a material guid */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    c.scene_id = 101u; /* collides with a texture guid */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    c = config(NULL);
    c.scene_path = NULL;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    c.scene_path = "";
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    c = config(NULL);
    memset(long_dir, 'd', sizeof(long_dir) - 1u);
    long_dir[sizeof(long_dir) - 1u] = '\0';
    c.texture_base_dir = long_dir;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    c = config(NULL);
    r[3].guid = 0u;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    r[3].guid = 201u; /* duplicate guid */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    n = sample(r);
    r[3].ref_index = 0u; /* two materials with ref_index 0 */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    n = sample(r);
    r[6].ref_index = 0u; /* a static mesh with the same ref_index as mesh 0 */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    break_asset_graph_stats(g, &gs);
    ASSERT_EQ(gs.nodes, 0u);
    /* an empty manifest declares just the scene */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, NULL, 0u, g, &st), BREAK_ASSET_GRAPH_OK);
    ASSERT_TRUE(break_asset_graph_contains(g, kSceneId));
    ASSERT_EQ(st.textures + st.materials + st.meshes, 0u);
    break_asset_graph_destroy(g);
}

/* A skinned mesh and a static mesh may share a ref_index: they are separate
 * index spaces. */
TEST(skinned_and_static_meshes_have_separate_slots) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    BreakSceneManifestGraphConfig c = config(NULL);
    BreakSceneManifestGraphStats st;
    ASSERT_EQ(r[5].type, (u32)BSCN_RES_SKINNED_MESH);
    ASSERT_EQ(r[5].ref_index, r[4].ref_index);
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    break_asset_graph_destroy(g);
}

TEST(ignored_entries_are_not_checked_and_only_textures_have_their_own_file) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    Paths paths;
    BreakSceneManifestGraphConfig c;
    BreakSceneManifestGraphStats st;
    char long_path[BREAK_SCENE_MANIFEST_MAX_PATH + 1u];
    memset(&paths, 0, sizeof(paths));
    c = config(&paths);
    r[7].guid = (BreakAssetId)kSceneId; /* the BSCN_RES_SCENE entry */
    /* first, so later entries are compared with it: shares a material's guid */
    memmove(r + 1, r, n * sizeof(r[0]));
    r[0] = res(201u, BSCN_RES_SCENE, 1u);
    n++;
    snprintf(r[3].path, sizeof(r[3].path), "mat.json"); /* a material path */
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    ASSERT_STR_EQ(path_of(&paths, 201u), "levels/hall.bscn");
    break_asset_graph_destroy(g);
    /* a scene path one past the limit */
    g = make(32u, 64u);
    memset(long_path, 's', sizeof(long_path) - 1u);
    long_path[sizeof(long_path) - 1u] = '\0';
    c.scene_path = long_path;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_INVALID);
    long_path[BREAK_SCENE_MANIFEST_MAX_PATH - 1u] = '\0';
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    break_asset_graph_destroy(g);
}

/* Links resolve within their own type: a texture listed first with the
 * mesh's material index is not the mesh's material. */
TEST(links_resolve_within_their_own_type) {
    SceneResource r[16];
    u32 n = sample(r);
    BreakAssetGraph *g = make(32u, 64u);
    BreakSceneManifestGraphConfig c = config(NULL);
    BreakSceneManifestGraphStats st;
    BreakAssetId out[16];
    u32 count = 0u;
    memmove(r + 1, r, n * sizeof(r[0]));
    r[0] = res(103u, BSCN_RES_TEXTURE, 1u); /* ref_index 1 like material 1 */
    n++;
    ASSERT_EQ(break_scene_manifest_graph_build(&c, r, n, g, &st), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_dependents(g, 103u, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(break_asset_graph_dependents(g, 202u, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 2u); /* mesh 0 and the scene */
    break_asset_graph_destroy(g);
}

TEST_MAIN_BEGIN()
    RUN_TEST(the_manifest_becomes_a_load_order_with_the_scene_last);
    RUN_TEST(a_changed_texture_lists_its_materials_meshes_and_the_scene);
    RUN_TEST(each_id_reports_the_file_it_reloads_from);
    RUN_TEST(links_to_absent_entries_are_counted_and_left_out);
    RUN_TEST(a_slot_naming_the_same_texture_twice_is_one_dependency);
    RUN_TEST(a_failed_build_leaves_the_graph_as_it_was);
    RUN_TEST(malformed_input_is_invalid);
    RUN_TEST(skinned_and_static_meshes_have_separate_slots);
    RUN_TEST(ignored_entries_are_not_checked_and_only_textures_have_their_own_file);
    RUN_TEST(links_resolve_within_their_own_type);
TEST_MAIN_END()
