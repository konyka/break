#include "editor_scene_deps.h"

#include <editor/editor_scene.h>
#include <scene/scene_serial.h>

#include <stdlib.h>
#include <string.h>

typedef struct PathRecord {
    BreakAssetId id;
    char path[BREAK_SCENE_MANIFEST_MAX_PATH];
} PathRecord;

typedef struct PathStore {
    u32 count;
    PathRecord records[];
} PathStore;

BreakAssetId break_editor_scene_deps_scene_id(const SceneResource *resources, u32 count) {
    BreakAssetId top = 0;
    for (u32 i = 0; i < count; ++i) {
        if (resources[i].guid > top) top = resources[i].guid;
    }
    if (top != UINT64_MAX) return top + 1u;
    for (BreakAssetId id = 1u;; ++id) {
        bool used = false;
        for (u32 i = 0; i < count && !used; ++i) {
            used = resources[i].guid == id;
        }
        if (!used) return id;
    }
}

/* scene_path is shorter than BREAK_SCENE_MANIFEST_MAX_PATH (checked by the
 * caller), so its directory part fits `out`. '/' and '\\' both separate,
 * like break_editor_scene_texture_resolve. */
static void scene_dir(const char *scene_path, char *out) {
    usize n = 0u;
    for (usize i = 0u; scene_path[i] != '\0'; i++) {
        if (scene_path[i] == '/' || scene_path[i] == '\\') n = i;
    }
    memcpy(out, scene_path, n);
    out[n] = '\0';
}

static void record_path(void *user, BreakAssetId id, const char *path) {
    PathStore *store = (PathStore *)user;
    PathRecord *rec = &store->records[store->count++];
    rec->id = id;
    /* the manifest builder only reports paths it already bounded */
    strncpy(rec->path, path, BREAK_SCENE_MANIFEST_MAX_PATH - 1u);
    rec->path[BREAK_SCENE_MANIFEST_MAX_PATH - 1u] = '\0';
}

BreakEditorSceneDepsResult break_editor_scene_deps_build(const BreakEditorDoc *doc,
                                                         const char *scene_path,
                                                         BreakEditorSceneDeps *out) {
    const u8 *bytes = NULL;
    u32 size = 0, version = 0;
    bool kept;
    SceneResource *res = NULL;
    u32 count = 0;
    PathStore *store;
    BreakAssetGraphConfig graph_config;
    BreakAssetGraph *graph = NULL;
    char dir[BREAK_SCENE_MANIFEST_MAX_PATH];
    BreakSceneManifestGraphConfig manifest;
    BreakEditorSceneDepsResult result = BREAK_EDITOR_SCENE_DEPS_FAILED;

    if (out) memset(out, 0, sizeof(*out));
    if (!doc || !out || !scene_path || scene_path[0] == '\0') {
        return BREAK_EDITOR_SCENE_DEPS_INVALID;
    }
    /* a longer path cannot be declared; reject it before copying anything */
    if (strlen(scene_path) >= BREAK_SCENE_MANIFEST_MAX_PATH) return BREAK_EDITOR_SCENE_DEPS_INVALID;

    kept = break_editor_doc_kept_chunk(doc, BSCN_CHUNK_RESOURCES, &bytes, &size, &version);
    if (kept && !scene_resources_parse_chunk(bytes, size, version, &res, &count)) {
        return BREAK_EDITOR_SCENE_DEPS_FAILED;
    }

    store = (PathStore *)calloc(1, sizeof(PathStore) + (count + 1u) * sizeof(PathRecord));
    if (!store) {
        free(res);
        return BREAK_EDITOR_SCENE_DEPS_OOM;
    }
    memset(&graph_config, 0, sizeof(graph_config));
    graph_config.capacity = count + 1u;
    graph_config.max_edges = count * 6u + 1u;
    if (break_asset_graph_create(&graph_config, &graph) != BREAK_ASSET_GRAPH_OK) {
        free(store);
        free(res);
        return BREAK_EDITOR_SCENE_DEPS_OOM;
    }
    scene_dir(scene_path, dir);
    memset(&manifest, 0, sizeof(manifest));
    manifest.scene_id = break_editor_scene_deps_scene_id(res, count);
    manifest.scene_path = scene_path;
    manifest.texture_base_dir = dir;
    manifest.path = record_path;
    manifest.path_user = store;
    if (break_scene_manifest_graph_build(&manifest, res, count, graph, &out->stats) ==
        BREAK_ASSET_GRAPH_OK) {
        out->graph = graph;
        out->scene_id = manifest.scene_id;
        out->internal = store;
        result = BREAK_EDITOR_SCENE_DEPS_OK;
    } else {
        break_asset_graph_destroy(graph);
        free(store);
        memset(out, 0, sizeof(*out));
        result = BREAK_EDITOR_SCENE_DEPS_FAILED;
    }
    free(res);
    return result;
}

void break_editor_scene_deps_free(BreakEditorSceneDeps *deps) {
    if (!deps) return;
    if (deps->graph) break_asset_graph_destroy(deps->graph);
    free(deps->internal);
    memset(deps, 0, sizeof(*deps));
}

u32 break_editor_scene_deps_ids_for_path(const BreakEditorSceneDeps *deps, const char *path,
                                         BreakAssetId *out, u32 cap) {
    const PathStore *store;
    u32 total = 0;
    if (!deps || !deps->graph || !path || !deps->internal) return 0;
    store = (const PathStore *)deps->internal;
    for (u32 i = 0; i < store->count; ++i) {
        if (strcmp(store->records[i].path, path) != 0) continue;
        if (total < cap && out) out[total] = store->records[i].id;
        total++;
    }
    return total;
}
