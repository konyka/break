/* Editor scene dependency graph: the kept RESOURCES chunk of a loaded BSCN
 * declared in a BreakAssetGraph (break_scene_manifest_graph_build), with the
 * scene directory as the texture base. Real BSCN bytes from
 * scene_save_binary plus malformed documents. */

#include "test_framework.h"

#include <editor/editor_doc.h>
#include <editor/editor_scene.h>
#include <editor/editor_scene_deps.h>

#include <asset/asset.h>
#include <asset/asset_graph.h>
#include <ecs/ecs.h>
#include <scene/scene_serial.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void tmp_path(char *out, usize cap, const char *name) {
    snprintf(out, cap, "%s/%s", test_tmp_root(), name);
}

/* Two textures (a.png, sub/b.png), two materials: material 0 uses a.png as
 * albedo and b.png as normal map, material 1 uses b.png as albedo. */
static bool save_textured_scene(const char *path, bool with_resources) {
    World *w = world_create();
    Scene s;
    SerializeOptions opts;
    bool ok;
    if (!w) return false;
    memset(&s, 0, sizeof(s));
    if (with_resources) {
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
    }
    memset(&opts, 0, sizeof(opts));
    opts.include_resources = with_resources;
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

/* The manifest guids of the saved scene, read back with the public parser. */
static bool manifest_of(const BreakEditorDoc *doc, SceneResource **res, u32 *count) {
    const u8 *bytes = NULL;
    u32 size = 0, version = 0;
    if (!break_editor_doc_kept_chunk(doc, BSCN_CHUNK_RESOURCES, &bytes, &size, &version))
        return false;
    return scene_resources_parse_chunk(bytes, size, version, res, count);
}

static const SceneResource *find_res(const SceneResource *res, u32 count, u32 type,
                                     u32 ref_index) {
    for (u32 i = 0; i < count; i++) {
        if (res[i].type == type && res[i].ref_index == ref_index) return &res[i];
    }
    return NULL;
}

static bool contains_id(const BreakAssetId *ids, u32 n, BreakAssetId id) {
    for (u32 i = 0; i < n; i++) {
        if (ids[i] == id) return true;
    }
    return false;
}

TEST(build_declares_the_manifest_of_a_real_bscn) {
    char path[512];
    tmp_path(path, sizeof(path), "scene_deps_real.bscn");
    ASSERT_TRUE(save_textured_scene(path, true));
    BreakEditorDoc *doc = doc_from(path);
    ASSERT_NOT_NULL(doc);
    SceneResource *res = NULL;
    u32 count = 0;
    ASSERT_TRUE(manifest_of(doc, &res, &count));

    BreakEditorSceneDeps deps;
    memset(&deps, 0xAB, sizeof(deps));
    ASSERT_EQ(break_editor_scene_deps_build(doc, path, &deps), BREAK_EDITOR_SCENE_DEPS_OK);
    ASSERT_NOT_NULL(deps.graph);
    ASSERT_EQ(deps.stats.textures, 2u);
    ASSERT_EQ(deps.stats.materials, 2u);
    ASSERT_EQ(deps.stats.meshes, 0u);
    ASSERT_EQ(deps.stats.dangling_links, 0u);

    /* the scene id is outside the manifest, like the core_app deps stage */
    ASSERT_TRUE(deps.scene_id != 0u);
    for (u32 i = 0; i < count; i++) ASSERT_TRUE(res[i].guid != deps.scene_id);
    BreakAssetGraphStats gs;
    break_asset_graph_stats(deps.graph, &gs);
    ASSERT_EQ(gs.nodes, count + 1u);

    /* a texture change reaches the material using it and the scene */
    const SceneResource *tex_b = NULL;
    for (u32 i = 0; i < count; i++) {
        if (res[i].type == (u32)BSCN_RES_TEXTURE && strcmp(res[i].path, "sub/b.png") == 0)
            tex_b = &res[i];
    }
    ASSERT_NOT_NULL(tex_b);
    const SceneResource *mat0 = find_res(res, count, (u32)BSCN_RES_MATERIAL, 0u);
    const SceneResource *mat1 = find_res(res, count, (u32)BSCN_RES_MATERIAL, 1u);
    ASSERT_NOT_NULL(mat0);
    ASSERT_NOT_NULL(mat1);
    BreakAssetId out[8];
    u32 n = 0;
    ASSERT_EQ(break_asset_graph_dependents(deps.graph, tex_b->guid, out, 8, &n),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_TRUE(contains_id(out, n, mat0->guid));
    ASSERT_TRUE(contains_id(out, n, mat1->guid));
    ASSERT_TRUE(contains_id(out, n, deps.scene_id));

    /* the scene loads after all of its entries */
    BreakAssetId problem = 0;
    ASSERT_EQ(break_asset_graph_load_order(deps.graph, deps.scene_id, out, 8, &n, &problem),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(n, count + 1u);
    ASSERT_EQ(out[n - 1u], deps.scene_id);

    break_editor_scene_deps_free(&deps);
    ASSERT_TRUE(deps.graph == NULL);
    ASSERT_EQ(deps.scene_id, 0u);
    break_editor_scene_deps_free(&deps); /* repeated free is safe */
    free(res);
    break_editor_doc_destroy(doc);
    remove(path);
}

TEST(texture_paths_resolve_against_the_scene_directory) {
    char path[512];
    tmp_path(path, sizeof(path), "scene_deps_paths.bscn");
    ASSERT_TRUE(save_textured_scene(path, true));
    BreakEditorDoc *doc = doc_from(path);
    ASSERT_NOT_NULL(doc);
    BreakEditorSceneDeps deps;
    ASSERT_EQ(break_editor_scene_deps_build(doc, path, &deps), BREAK_EDITOR_SCENE_DEPS_OK);

    char expect_a[600], expect_b[600];
    snprintf(expect_a, sizeof(expect_a), "%s/a.png", test_tmp_root());
    snprintf(expect_b, sizeof(expect_b), "%s/sub/b.png", test_tmp_root());
    BreakAssetId ids[4];
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, expect_b, ids, 4), 1u);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, expect_a, ids, 4), 1u);
    /* every non-texture entry and the scene reload from the scene file */
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, path, ids, 4), 3u);
    ASSERT_TRUE(contains_id(ids, 3u, deps.scene_id));
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, "a.png", ids, 4), 0u);
    /* capacity bounds the copy; the true count is still returned */
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, path, ids, 1), 3u);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, path, NULL, 0), 3u);
    /* a NULL output with a capacity only counts */
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, path, NULL, 4), 3u);
    /* a struct whose path records are gone matches nothing */
    BreakEditorSceneDeps stripped = deps;
    stripped.internal = NULL;
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&stripped, path, ids, 4), 0u);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(NULL, path, ids, 4), 0u);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, NULL, ids, 4), 0u);
    break_editor_scene_deps_free(&deps);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, path, ids, 4), 0u);

    /* a backslash separates the directory too, like the texture resolver */
    ASSERT_EQ(break_editor_scene_deps_build(doc, "C:\\scenes\\level.bscn", &deps),
              BREAK_EDITOR_SCENE_DEPS_OK);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, "C:\\scenes/a.png", ids, 4), 1u);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, "a.png", ids, 4), 0u);
    break_editor_scene_deps_free(&deps);
    /* the later separator wins whichever kind it is */
    ASSERT_EQ(break_editor_scene_deps_build(doc, "C:\\scenes/sub\\level.bscn", &deps),
              BREAK_EDITOR_SCENE_DEPS_OK);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, "C:\\scenes/sub/a.png", ids, 4), 1u);
    break_editor_scene_deps_free(&deps);
    ASSERT_EQ(break_editor_scene_deps_build(doc, "C:\\scenes\\sub/level.bscn", &deps),
              BREAK_EDITOR_SCENE_DEPS_OK);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, "C:\\scenes\\sub/a.png", ids, 4), 1u);
    break_editor_scene_deps_free(&deps);
    break_editor_doc_destroy(doc);
    remove(path);
}

TEST(a_scene_without_resources_has_only_the_scene_node) {
    char path[512];
    tmp_path(path, sizeof(path), "scene_deps_empty.bscn");
    ASSERT_TRUE(save_textured_scene(path, false));
    BreakEditorDoc *doc = doc_from(path);
    ASSERT_NOT_NULL(doc);
    BreakEditorSceneDeps deps;
    ASSERT_EQ(break_editor_scene_deps_build(doc, path, &deps), BREAK_EDITOR_SCENE_DEPS_OK);
    ASSERT_NOT_NULL(deps.graph);
    ASSERT_EQ(deps.scene_id, 1u);
    BreakAssetGraphStats gs;
    break_asset_graph_stats(deps.graph, &gs);
    ASSERT_EQ(gs.nodes, 1u);
    ASSERT_EQ(gs.edges, 0u);
    break_editor_scene_deps_free(&deps);

    /* a fresh document has no kept chunk either */
    BreakEditorDoc *fresh = break_editor_doc_create();
    ASSERT_NOT_NULL(fresh);
    ASSERT_EQ(break_editor_scene_deps_build(fresh, path, &deps), BREAK_EDITOR_SCENE_DEPS_OK);
    ASSERT_EQ(deps.scene_id, 1u);
    break_editor_scene_deps_free(&deps);
    break_editor_doc_destroy(fresh);
    break_editor_doc_destroy(doc);
    remove(path);
}

TEST(invalid_arguments_leave_nothing_built) {
    char path[512];
    tmp_path(path, sizeof(path), "scene_deps_args.bscn");
    ASSERT_TRUE(save_textured_scene(path, true));
    BreakEditorDoc *doc = doc_from(path);
    ASSERT_NOT_NULL(doc);
    BreakEditorSceneDeps deps;
    memset(&deps, 0xAB, sizeof(deps));
    ASSERT_EQ(break_editor_scene_deps_build(NULL, path, &deps), BREAK_EDITOR_SCENE_DEPS_INVALID);
    ASSERT_TRUE(deps.graph == NULL);
    ASSERT_EQ(deps.scene_id, 0u);
    ASSERT_EQ(break_editor_scene_deps_build(doc, NULL, &deps), BREAK_EDITOR_SCENE_DEPS_INVALID);
    ASSERT_TRUE(deps.graph == NULL);
    ASSERT_EQ(break_editor_scene_deps_build(doc, "", &deps), BREAK_EDITOR_SCENE_DEPS_INVALID);
    ASSERT_EQ(break_editor_scene_deps_build(doc, path, NULL), BREAK_EDITOR_SCENE_DEPS_INVALID);

    /* a scene path the manifest builder cannot hold: BREAK_SCENE_MANIFEST_MAX_PATH
     * characters or more, with its whole length a directory part */
    char long_path[BREAK_SCENE_MANIFEST_MAX_PATH + 8];
    memset(long_path, 'x', sizeof(long_path) - 1u);
    long_path[0] = '/';
    long_path[sizeof(long_path) - 3u] = '/';
    long_path[sizeof(long_path) - 1u] = '\0';
    memset(&deps, 0xAB, sizeof(deps));
    ASSERT_EQ(break_editor_scene_deps_build(doc, long_path, &deps),
              BREAK_EDITOR_SCENE_DEPS_INVALID);
    ASSERT_TRUE(deps.graph == NULL);
    ASSERT_EQ(deps.scene_id, 0u);
    long_path[BREAK_SCENE_MANIFEST_MAX_PATH] = '\0'; /* exactly the limit */
    ASSERT_EQ(break_editor_scene_deps_build(doc, long_path, &deps),
              BREAK_EDITOR_SCENE_DEPS_INVALID);
    /* one under the limit is accepted when there is no texture base to join */
    BreakEditorDoc *bare = break_editor_doc_create();
    ASSERT_NOT_NULL(bare);
    long_path[BREAK_SCENE_MANIFEST_MAX_PATH - 1u] = '\0';
    ASSERT_EQ(break_editor_scene_deps_build(bare, long_path, &deps), BREAK_EDITOR_SCENE_DEPS_OK);
    ASSERT_EQ(break_editor_scene_deps_ids_for_path(&deps, long_path, NULL, 0), 1u);
    break_editor_scene_deps_free(&deps);
    break_editor_doc_destroy(bare);
    break_editor_doc_destroy(doc);
    remove(path);
}

TEST(scene_id_follows_the_core_app_rule) {
    SceneResource res[3];
    memset(res, 0, sizeof(res));
    ASSERT_EQ(break_editor_scene_deps_scene_id(NULL, 0u), 1u);
    res[0].guid = 5u;
    res[1].guid = 40u;
    res[2].guid = 7u;
    ASSERT_EQ(break_editor_scene_deps_scene_id(res, 3u), 41u);
    /* the top guid leaves no room above: the first unused id */
    res[1].guid = UINT64_MAX;
    res[0].guid = 1u;
    res[2].guid = 2u;
    ASSERT_EQ(break_editor_scene_deps_scene_id(res, 3u), 3u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(build_declares_the_manifest_of_a_real_bscn);
    RUN_TEST(texture_paths_resolve_against_the_scene_directory);
    RUN_TEST(a_scene_without_resources_has_only_the_scene_node);
    RUN_TEST(invalid_arguments_leave_nothing_built);
    RUN_TEST(scene_id_follows_the_core_app_rule);
TEST_MAIN_END()
