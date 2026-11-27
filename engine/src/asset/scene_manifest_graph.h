#pragma once
/* Declares the assets of a loaded scene's resource manifest (BSCN RESOURCES
 * chunk, Scene.resources) in a BreakAssetGraph, so load order and hot reload
 * follow the scene's real dependencies:
 *
 *  - a texture entry needs nothing;
 *  - a material entry needs the texture entries its tex_slots link to;
 *  - a mesh or skinned-mesh entry with an inline descriptor needs the
 *    material entry its u2 names;
 *  - the scene itself (`scene_id`) needs every mesh, skinned mesh and
 *    material entry.
 *
 * Each entry's id is its manifest guid. A link to an entry the manifest does
 * not contain is counted in `dangling_links` and left out, matching the
 * best-effort rebind (asset_scene_rebind_textures). The `path` callback, when
 * given, receives the file each declared id reloads from: base_dir + '/' +
 * the entry path for a texture with a path, and `scene_path` for everything
 * else (materials and meshes live in the scene file).
 *
 * All or nothing: on any failure nothing stays declared and no path is
 * reported. Design: docs/design/runtime_asset_streaming.md
 * "场景 manifest 依赖图". */
#include <asset/asset.h>
#include <asset/asset_graph.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_SCENE_MANIFEST_MAX_PATH 260u

typedef void (*BreakSceneManifestPathFn)(void *user, BreakAssetId id, const char *path);

typedef struct BreakSceneManifestGraphConfig {
    BreakAssetId scene_id;        /* non-zero, distinct from every entry guid */
    const char *scene_path;       /* required, non-empty */
    const char *texture_base_dir; /* NULL or empty: texture paths as-is */
    BreakSceneManifestPathFn path; /* may be NULL */
    void *path_user;
} BreakSceneManifestGraphConfig;

typedef struct BreakSceneManifestGraphStats {
    u32 textures;
    u32 materials;
    u32 meshes; /* static and skinned */
    u32 dangling_links;
} BreakSceneManifestGraphStats;

/* INVALID: NULL graph/config/stats, a NULL resource array with a non-zero
 * count, scene_id 0 or equal to an entry guid, missing scene_path, an entry
 * guid of 0, two entries with one guid or type+ref_index, a scene_path of
 * BREAK_SCENE_MANIFEST_MAX_PATH or more, or a texture_base_dir leaving no
 * room for an entry path. Ignored entries are not checked. EXISTS: an id
 * is already declared. OVERLOAD: the graph has no room. Other entry types
 * (BSCN_RES_SCENE) are ignored. */
BreakAssetGraphResult break_scene_manifest_graph_build(const BreakSceneManifestGraphConfig *config,
                                                       const SceneResource *resources,
                                                       u32 resource_count, BreakAssetGraph *graph,
                                                       BreakSceneManifestGraphStats *out_stats);

#ifdef __cplusplus
}
#endif
