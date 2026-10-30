#include "editor_scene_textures.h"

#include "editor_image_preview.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCENE_TEXTURES_PATH_CAP BREAK_EDITOR_IMAGE_PREVIEW_PATH_CAPACITY
#define SCENE_TEXTURES_RETIRED_MAX 16u

typedef struct {
    BreakEditorSceneTexture src;
    int state;     /* meaningful when preview == NULL */
    char abs_path[SCENE_TEXTURES_PATH_CAP];
    BreakEditorImagePreview *preview; /* NULL unless this file is being followed */
    /* last published snapshot, to detect changes for the revision counter */
    int seen_state;
    u32 seen_w, seen_h;
    u64 seen_reloads, seen_failed;
} SceneTexSlot;

struct BreakEditorSceneTextures {
    SceneTexSlot slots[BREAK_EDITOR_SCENE_TEXTURES_MAX];
    u32 count;
    /* previews dropped by set_scene whose worker did not stop in time; they
     * are retried on every tick and must be gone before shutdown succeeds */
    BreakEditorImagePreview *retired[SCENE_TEXTURES_RETIRED_MAX];
    RHIDevice *device;
    u64 revision;
    u32 shutdown_timeout_ms; /* 0 = the preview owner's default */
    bool stopped;
};

BreakEditorSceneTextures *break_editor_scene_textures_create(void) {
    return (BreakEditorSceneTextures *)calloc(1u, sizeof(BreakEditorSceneTextures));
}

static void apply_timeout(BreakEditorSceneTextures *st, BreakEditorImagePreview *p) {
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (st->shutdown_timeout_ms != 0u) {
        break_editor_image_preview_set_shutdown_timeout_for_test(p, st->shutdown_timeout_ms);
    }
#else
    (void)st;
    (void)p;
#endif
}

/* Stops a preview and frees it. A preview whose worker does not stop in time
 * is parked in retired[] and retried later; with no room left it is leaked
 * rather than freed under a running worker (the preview owner's own rule). */
static void preview_retire(BreakEditorSceneTextures *st, BreakEditorImagePreview *p) {
    if (p == NULL) {
        return;
    }
    apply_timeout(st, p);
    if (break_editor_image_preview_shutdown(p)) {
        break_editor_image_preview_destroy(p);
        return;
    }
    for (u32 i = 0; i < SCENE_TEXTURES_RETIRED_MAX; i++) {
        if (st->retired[i] == NULL) {
            st->retired[i] = p;
            return;
        }
    }
    break_editor_image_preview_destroy(p); /* leaks on timeout, by contract */
}

static void retired_retry(BreakEditorSceneTextures *st) {
    for (u32 i = 0; i < SCENE_TEXTURES_RETIRED_MAX; i++) {
        BreakEditorImagePreview *p = st->retired[i];
        if (p != NULL && break_editor_image_preview_shutdown(p)) {
            break_editor_image_preview_destroy(p);
            st->retired[i] = NULL;
        }
    }
}

void break_editor_scene_textures_set_device(BreakEditorSceneTextures *st,
                                            RHIDevice *device) {
    if (st == NULL || st->device == device) {
        return;
    }
    st->device = device;
    for (u32 i = 0; i < st->count; i++) {
        if (st->slots[i].preview != NULL) {
            break_editor_image_preview_set_device(st->slots[i].preview, device);
        }
    }
}

static int preview_state(const SceneTexSlot *slot, BreakEditorImagePreviewStats *s) {
    memset(s, 0, sizeof(*s));
    if (slot->preview == NULL || !break_editor_image_preview_stats(slot->preview, s)) {
        return slot->state;
    }
    switch (s->last_result) {
    case BREAK_EDITOR_IMAGE_PREVIEW_UNAVAILABLE:
    case BREAK_EDITOR_IMAGE_PREVIEW_FAILED_KEEP_OLD:
        return BREAK_EDITOR_SCENE_TEXTURE_STATE_FAILED;
    case BREAK_EDITOR_IMAGE_PREVIEW_APPLIED:
        return BREAK_EDITOR_SCENE_TEXTURE_STATE_READY;
    default:
        return s->has_image ? BREAK_EDITOR_SCENE_TEXTURE_STATE_READY
                            : BREAK_EDITOR_SCENE_TEXTURE_STATE_PENDING;
    }
}

static bool slot_snapshot_changed(SceneTexSlot *slot) {
    BreakEditorImagePreviewStats s;
    int state = preview_state(slot, &s);
    bool changed = state != slot->seen_state || s.width != slot->seen_w ||
                   s.height != slot->seen_h || s.reloads != slot->seen_reloads ||
                   s.failed != slot->seen_failed;
    slot->seen_state = state;
    slot->seen_w = s.width;
    slot->seen_h = s.height;
    slot->seen_reloads = s.reloads;
    slot->seen_failed = s.failed;
    return changed;
}

bool break_editor_scene_textures_set_scene(BreakEditorSceneTextures *st,
                                           const BreakEditorDoc *doc,
                                           const char *scene_path) {
    BreakEditorSceneTexture parsed[BREAK_EDITOR_SCENE_TEXTURES_MAX];
    SceneTexSlot fresh[BREAK_EDITOR_SCENE_TEXTURES_MAX];
    bool claimed[BREAK_EDITOR_SCENE_TEXTURES_MAX];
    u32 n, loaded = 0u;
    if (st == NULL || st->stopped) {
        return false;
    }
    n = doc != NULL ? break_editor_scene_textures_parse(
                          doc, parsed, BREAK_EDITOR_SCENE_TEXTURES_MAX, NULL, 0u, NULL)
                    : 0u;
    memset(fresh, 0, sizeof(fresh));
    memset(claimed, 0, sizeof(claimed));
    for (u32 i = 0; i < n; i++) {
        SceneTexSlot *slot = &fresh[i];
        slot->src = parsed[i];
        slot->seen_state = -1;
        if (!break_editor_scene_texture_path_ok(parsed[i].path)) {
            slot->state = BREAK_EDITOR_SCENE_TEXTURE_STATE_UNSAFE;
            continue;
        }
        if (scene_path == NULL ||
            !break_editor_scene_texture_resolve(scene_path, parsed[i].path,
                                                slot->abs_path,
                                                sizeof(slot->abs_path))) {
            slot->abs_path[0] = '\0';
            slot->state = BREAK_EDITOR_SCENE_TEXTURE_STATE_NO_BASE;
            continue;
        }
        if (loaded >= BREAK_EDITOR_SCENE_TEXTURES_LOADED) {
            slot->state = BREAK_EDITOR_SCENE_TEXTURE_STATE_SKIPPED;
            continue;
        }
        loaded++;
        /* a followed file that stays in the scene keeps its preview */
        for (u32 k = 0; k < st->count; k++) {
            if (!claimed[k] && st->slots[k].preview != NULL &&
                strcmp(st->slots[k].abs_path, slot->abs_path) == 0) {
                claimed[k] = true;
                slot->preview = st->slots[k].preview;
                st->slots[k].preview = NULL;
                break;
            }
        }
        if (slot->preview == NULL) {
            slot->preview = break_editor_image_preview_create();
            if (slot->preview == NULL ||
                (apply_timeout(st, slot->preview),
                 break_editor_image_preview_set_device(slot->preview, st->device),
                 !break_editor_image_preview_set_path(slot->preview, slot->abs_path))) {
                preview_retire(st, slot->preview);
                slot->preview = NULL;
                slot->state = BREAK_EDITOR_SCENE_TEXTURE_STATE_FAILED;
            }
        }
    }
    for (u32 k = 0; k < st->count; k++) {
        preview_retire(st, st->slots[k].preview); /* previews nobody claimed */
        st->slots[k].preview = NULL;
    }
    memcpy(st->slots, fresh, sizeof(fresh));
    st->count = n;
    for (u32 i = 0; i < n; i++) {
        (void)slot_snapshot_changed(&st->slots[i]);
    }
    st->revision++;
    return true;
}

void break_editor_scene_textures_tick(BreakEditorSceneTextures *st) {
    bool changed = false;
    if (st == NULL || st->stopped) {
        return;
    }
    retired_retry(st);
    for (u32 i = 0; i < st->count; i++) {
        if (st->slots[i].preview != NULL) {
            break_editor_image_preview_tick(st->slots[i].preview);
            if (slot_snapshot_changed(&st->slots[i])) {
                changed = true;
            }
        }
    }
    if (changed) {
        st->revision++;
    }
}

u32 break_editor_scene_textures_count(const BreakEditorSceneTextures *st) {
    return st != NULL ? st->count : 0u;
}

bool break_editor_scene_textures_info(const BreakEditorSceneTextures *st, u32 index,
                                      BreakEditorSceneTextureInfo *out) {
    BreakEditorImagePreviewStats s;
    const SceneTexSlot *slot;
    if (st == NULL || out == NULL || index >= st->count) {
        return false;
    }
    slot = &st->slots[index];
    memset(out, 0, sizeof(*out));
    memcpy(out->path, slot->src.path, sizeof(out->path));
    out->ref_index = slot->src.ref_index;
    out->used_by_materials = slot->src.used_by_materials;
    out->state = preview_state(slot, &s);
    out->width = s.width;
    out->height = s.height;
    out->reloads = s.reloads;
    out->failed = s.failed;
    return true;
}

RHITexture break_editor_scene_textures_texture(const BreakEditorSceneTextures *st,
                                               u32 index) {
    if (st == NULL || index >= st->count || st->slots[index].preview == NULL) {
        return RHI_HANDLE_NULL;
    }
    return break_editor_image_preview_texture(st->slots[index].preview);
}

u64 break_editor_scene_textures_revision(const BreakEditorSceneTextures *st) {
    return st != NULL ? st->revision : 0u;
}

bool break_editor_scene_textures_shutdown(BreakEditorSceneTextures *st) {
    bool ok = true;
    if (st == NULL) {
        return false;
    }
    for (u32 i = 0; i < st->count; i++) {
        BreakEditorImagePreview *p = st->slots[i].preview;
        if (p != NULL) {
            apply_timeout(st, p);
            if (!break_editor_image_preview_shutdown(p)) {
                ok = false;
            }
        }
    }
    retired_retry(st);
    for (u32 i = 0; i < SCENE_TEXTURES_RETIRED_MAX; i++) {
        if (st->retired[i] != NULL) {
            ok = false;
        }
    }
    if (ok) {
        st->stopped = true;
    }
    return ok;
}

void break_editor_scene_textures_destroy(BreakEditorSceneTextures *st) {
    if (st == NULL) {
        return;
    }
    if (!break_editor_scene_textures_shutdown(st)) {
        return; /* leaked rather than freed under a running worker */
    }
    for (u32 i = 0; i < st->count; i++) {
        break_editor_image_preview_destroy(st->slots[i].preview);
        st->slots[i].preview = NULL;
    }
    free(st);
}

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_scene_textures_set_shutdown_timeout_for_test(
    BreakEditorSceneTextures *st, u32 timeout_ms) {
    if (st != NULL) {
        st->shutdown_timeout_ms = timeout_ms;
    }
}
#endif
