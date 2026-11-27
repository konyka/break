#pragma once
/* Scene dependency graph for the editor: the kept RESOURCES chunk of a
 * loaded document declared in a BreakAssetGraph, so a texture or material
 * change names everything that must be rebuilt (design:
 * docs/design/runtime_asset_streaming.md "编辑器的场景依赖图").
 *
 * The scene id follows the core_app rule (one above the highest manifest
 * guid, or the first unused id when that overflows). Texture entries reload
 * from the scene directory + their manifest path; every other entry and the
 * scene reload from the scene file itself.
 *
 * Single owner thread, CPU only. The graph is owned by the struct and freed
 * by break_editor_scene_deps_free, which is safe on a zeroed or already
 * freed struct. A failure leaves the struct cleared. */
#include <asset/asset_graph.h>
#include <asset/scene_manifest_graph.h>
#include <editor/editor_doc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum BreakEditorSceneDepsResult {
    BREAK_EDITOR_SCENE_DEPS_OK = 0,
    BREAK_EDITOR_SCENE_DEPS_INVALID, /* NULL argument, empty scene path */
    BREAK_EDITOR_SCENE_DEPS_OOM,
    BREAK_EDITOR_SCENE_DEPS_FAILED /* the manifest builder rejected the chunk */
} BreakEditorSceneDepsResult;

typedef struct BreakEditorSceneDeps {
    BreakAssetGraph *graph; /* owned; NULL when nothing is built */
    BreakAssetId scene_id;  /* 0 when nothing is built */
    BreakSceneManifestGraphStats stats;
    void *internal; /* owned reload-path records; not for callers */
} BreakEditorSceneDeps;

/* The scene node id the deps stage uses for this manifest: one above the
 * highest entry guid, or the first unused id starting at 1 when the highest
 * is UINT64_MAX. An empty manifest gets 1. */
BreakAssetId break_editor_scene_deps_scene_id(const SceneResource *resources, u32 count);

/* Declares the document's kept RESOURCES chunk (an absent chunk is an empty
 * manifest). `scene_path` is the file the document was loaded from and must
 * be non-empty; its directory is the texture base. On OK the struct owns a
 * graph; on failure it is cleared. */
BreakEditorSceneDepsResult break_editor_scene_deps_build(const BreakEditorDoc *doc,
                                                         const char *scene_path,
                                                         BreakEditorSceneDeps *out);

/* Frees the owned graph and clears the struct. Safe on NULL and on repeat. */
void break_editor_scene_deps_free(BreakEditorSceneDeps *deps);

/* The declared ids whose reload path is exactly `path`, up to `cap` copied
 * into `out`. Returns the true count, 0 for a NULL deps/path, an unbuilt
 * struct, or a path that matches nothing. `out` may be NULL when cap is 0. */
u32 break_editor_scene_deps_ids_for_path(const BreakEditorSceneDeps *deps, const char *path,
                                         BreakAssetId *out, u32 cap);

/* Everything to rebuild after the file `path` changed: every asset that
 * depends, directly or not, on an id whose reload path is exactly `path`,
 * in the scene's load order (dependencies before dependents, each once).
 * Ids that `path` itself reloads are not listed, since that reload covers
 * them. Returns the true count and copies up to `cap` into `out` (`out` may
 * be NULL). 0 for NULL deps/path, an unbuilt struct, a path that matches
 * nothing, or an allocation failure. */
u32 break_editor_scene_deps_dependents_of_path(const BreakEditorSceneDeps *deps,
                                               const char *path,
                                               BreakAssetId *out, u32 cap);

#ifdef __cplusplus
}
#endif
