#pragma once
/* Scene texture model: a read-only view of the textures and the material
 * links a loaded BSCN carries in its RESOURCES chunk.
 *
 * The editor keeps the chunk as the game wrote it (editor_scene.h); this
 * parses it for display and for hot reload of the texture files. It is NOT a
 * link from the editor's entities to materials: BSCN has none. Pure CPU, no
 * allocation, single owner thread.
 *
 * Paths come from the file and are untrusted: break_editor_scene_texture_path_ok
 * and _resolve are the only way to turn one into something that may be opened. */

#include <core/types.h>

#include <editor/editor_doc.h>

#define BREAK_EDITOR_SCENE_TEXTURES_MAX 64u
#define BREAK_EDITOR_SCENE_TEXTURE_PATH 64u /* incl. NUL; a name is at most 63 chars */
#define BREAK_EDITOR_SCENE_TEXTURE_NONE 0xffffffffu

typedef struct {
    u32 ref_index;          /* the texture entry's ref_index (RHI handle index at save time) */
    char path[BREAK_EDITOR_SCENE_TEXTURE_PATH]; /* raw, NUL-terminated, may be empty/unsafe */
    u32 used_by_materials;  /* distinct materials linking it in any slot (v3 files only) */
} BreakEditorSceneTexture;

typedef struct {
    u32 ref_index;          /* material slot */
    /* albedo, metallic-roughness, normal, emissive, occlusion -> texture
     * ref_index, or BREAK_EDITOR_SCENE_TEXTURE_NONE (empty or unknown: v1/v2
     * files and path-only references carry no links) */
    u32 slot_texture[5];
} BreakEditorSceneMaterial;

/* Fills `out` with up to `cap` texture entries and `mats` with up to
 * `mat_cap` material entries (both optional-capacity: pass NULL/0 to skip
 * materials). `mat_total` (optional) receives the true material count.
 * Returns the number of textures written. A missing, truncated or otherwise
 * malformed RESOURCES chunk yields 0 and mat_total 0 — never partial data.
 * `used_by_materials` counts every material, including ones beyond mat_cap. */
u32 break_editor_scene_textures_parse(const BreakEditorDoc *doc,
                                      BreakEditorSceneTexture *out, u32 cap,
                                      BreakEditorSceneMaterial *mats,
                                      u32 mat_cap, u32 *mat_total);

/* The same parse over a RESOURCES chunk payload (`version` = the BSCN header
 * version of its file). This is what the document-based call runs on the kept
 * chunk; it is separate so the bounds handling can be tested with chunks the
 * game loader would never let into a document. */
u32 break_editor_scene_textures_parse_chunk(const u8 *bytes, u32 size,
                                            u32 version,
                                            BreakEditorSceneTexture *out,
                                            u32 cap,
                                            BreakEditorSceneMaterial *mats,
                                            u32 mat_cap, u32 *mat_total);

/* A texture path the editor may open: 1..63 printable ASCII characters, no
 * backslash or ':', relative, no empty / "." / ".." segment. */
bool break_editor_scene_texture_path_ok(const char *path);

/* scene directory + uri into `out`. false (nothing usable written) when the
 * uri fails path_ok, the scene path is not absolute or has no directory, or
 * the result does not fit with its NUL. */
bool break_editor_scene_texture_resolve(const char *scene_path, const char *uri,
                                        char *out, usize cap);

/* Makes `path` absolute for resolve(): an absolute path is copied as is; a
 * relative one is joined to `cwd` (which must itself be absolute), dropping
 * leading "./" segments. The scene path comes from the user, so ".." in it
 * is kept as typed. false when either is empty/NULL, cwd is not absolute, or
 * the result does not fit with its NUL (nothing is truncated). */
bool break_editor_scene_texture_make_absolute(const char *path, const char *cwd,
                                              char *out, usize cap);
