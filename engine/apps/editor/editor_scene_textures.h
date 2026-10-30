#pragma once

/* Scene textures with hot reload: the texture files a loaded BSCN names in its
 * RESOURCES chunk (src/editor/editor_scene_textures.h), loaded as RHI
 * textures and kept current while the files change on disk.
 *
 * Up to BREAK_EDITOR_SCENE_TEXTURES_LOADED (8) textures are loaded at once,
 * each through its own BreakEditorImagePreview (Runtime Core reload worker +
 * file watch + transactional GPU swap), so every guarantee of that owner
 * applies per texture: a bad file keeps the previous image, the old texture
 * is destroyed only after the new one exists, shutdown is bounded.
 * Further textures in the scene are listed but reported SKIPPED.
 *
 * Paths are resolved against the directory of the scene file and must pass
 * break_editor_scene_texture_path_ok; anything else is listed UNSAFE and never
 * opened. A scene without an absolute path lists its textures as NO_BASE.
 *
 * Single owner thread: the one that calls set_scene/tick/shutdown. */

#include <core/types.h>
#include <rhi/rhi.h>

#include <editor/editor_scene_textures.h>

#define BREAK_EDITOR_SCENE_TEXTURES_LOADED 8u

typedef enum {
    BREAK_EDITOR_SCENE_TEXTURE_STATE_PENDING = 0, /* queued / decoding */
    BREAK_EDITOR_SCENE_TEXTURE_STATE_READY,       /* image current */
    BREAK_EDITOR_SCENE_TEXTURE_STATE_FAILED,      /* last load failed (an older image may remain) */
    BREAK_EDITOR_SCENE_TEXTURE_STATE_UNSAFE,      /* uri failed the path rules; never opened */
    BREAK_EDITOR_SCENE_TEXTURE_STATE_NO_BASE,     /* scene has no absolute path */
    BREAK_EDITOR_SCENE_TEXTURE_STATE_SKIPPED      /* beyond the loaded limit */
} BreakEditorSceneTextureState;

typedef struct {
    char path[BREAK_EDITOR_SCENE_TEXTURE_PATH]; /* as written in the scene */
    u32 ref_index;
    u32 used_by_materials;
    int state; /* BreakEditorSceneTextureState */
    u32 width, height; /* of the current image, 0 when none */
    u64 reloads, failed;
} BreakEditorSceneTextureInfo;

typedef struct BreakEditorSceneTextures BreakEditorSceneTextures;

BreakEditorSceneTextures *break_editor_scene_textures_create(void);
/* NULL detaches (textures are destroyed on the device they were made on). */
void break_editor_scene_textures_set_device(BreakEditorSceneTextures *st,
                                            RHIDevice *device);
/* Re-reads the document's RESOURCES chunk and (re)points the loaded set:
 * textures that stay keep their image and watcher, new ones start loading,
 * dropped ones stop and are destroyed. `scene_path` may be NULL/empty/relative
 * (-> NO_BASE). `doc` may be NULL (clears everything). Returns false only for
 * a NULL owner. Cheap to call again after a document load or reload. */
bool break_editor_scene_textures_set_scene(BreakEditorSceneTextures *st,
                                           const BreakEditorDoc *doc,
                                           const char *scene_path);
void break_editor_scene_textures_tick(BreakEditorSceneTextures *st);

u32 break_editor_scene_textures_count(const BreakEditorSceneTextures *st);
bool break_editor_scene_textures_info(const BreakEditorSceneTextures *st, u32 index,
                                      BreakEditorSceneTextureInfo *out);
RHITexture break_editor_scene_textures_texture(const BreakEditorSceneTextures *st,
                                               u32 index);
/* Bumps whenever any listed state, size or image changes (for repaint). */
u64 break_editor_scene_textures_revision(const BreakEditorSceneTextures *st);

/* Bounded stop of every worker; false keeps everything alive for a retry. */
bool break_editor_scene_textures_shutdown(BreakEditorSceneTextures *st);
void break_editor_scene_textures_destroy(BreakEditorSceneTextures *st);

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_scene_textures_set_shutdown_timeout_for_test(
    BreakEditorSceneTextures *st, u32 timeout_ms);
#endif
