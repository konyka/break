/* EditorPanelAssets — Stage 4 scene editor Phase 3 Task 3: the myui panel
 * half of the asset browser. The pure CPU view model is BreakEditorAssets
 * (Phase 3 Task 1, editor_assets.h); this file only wires it to a list_view
 * plus a path label and routes row activation.
 *
 * Rows: row 0 is the always-present ".." (parent directory, clamped at the
 * root by the model); rows 1..N bind the model's filtered listing snapshot
 * (directories first, byte-wise order). Directories render with a trailing
 * '/'. ACTIVATION GESTURE (documented decision): a single row CLICK
 * activates — myui's list_view has no double-click/Enter idiom and the
 * outliner precedent is click-activation. Click semantics:
 *   ".."      => break_editor_assets_up (clamped at the root)
 *   dir       => break_editor_assets_enter (single validated segment)
 *   *.bscn    => confirm-free break_editor_doc_load (Phase 2 documents the
 *                world swap + undo-stack clear; the console logs the load)
 *   image     => (.png .jpg .jpeg .bmp .tga) the preview below the list
 *                loads it and hot-reloads it on external edits
 *                (editor_image_preview.h; the panel owns the preview)
 *   other     => bounded "not loadable" console note, nothing else happens
 * After a successful load the WHOLE shell refreshes (outliner/inspector/
 * status) because the doc's world was swapped and the selection may have
 * been invalidated.
 *
 * Bounds: the model bounds paths/names/entry counts (editor_assets.h); the
 * panel adds only a fixed 32-entry click-context pool (virtualized rows are
 * visible+1, so this never exhausts in practice — on exhaustion rows still
 * render but lose click, the outliner precedent). Non-navigation console
 * lines go through the shell's bounded ring.
 *
 * Threading: single-owner-thread convention, same as the shell. */

#include "editor_shell_internal.h"

#include <asset/vfs.h>
#include <editor/editor_i18n.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editor/editor_assets.h>
#include <editor/editor_image.h>
#include <editor/editor_scene.h>

#include "editor_image_preview.h"
#include "editor_theme.h"
#include "myr/my_color.h"
#include "myr/my_vgcanvas.h"
#include "myr/my_vgcanvas_break_rhi.h"
#include <platform/time.h>

#include "myc/my_emitter.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_list_view.h"

#define EDITOR_ASSETS_ROW_CTX_POOL 32u

typedef struct {
    EditorPanelAssets *panel; /* borrowed */
    my_widget_t *row;         /* borrowed (NULL = pool slot unused) */
    usize index;              /* bound row position (0 = "..") */
} EditorAssetsRowCtx;

typedef struct {
    my_list_adapter_t base;
    EditorPanelAssets *panel; /* borrowed */
} EditorAssetsAdapter;

struct EditorPanelAssets {
    BreakEditorShell *shell;   /* borrowed */
    BreakEditorAssets *assets; /* owned (NULL when no root could be listed) */
    my_widget_t *list;         /* weak (owned by the window tree) */
    my_widget_t *path_label;   /* weak */
    my_widget_t *filter_edit;  /* weak: extension CSV, applied on Enter */
    char filter[128];          /* applied filter, re-applied after a re-root */
    EditorAssetsAdapter adapter;
    EditorAssetsRowCtx row_ctxs[EDITOR_ASSETS_ROW_CTX_POOL];
    /* hot refresh: throttled re-list of the CURRENT directory */
    u64 (*clock)(void *user); /* NULL = time_microseconds */
    void *clock_user;
    u64 last_refresh_us;
    bool primed;
    /* label text cache: "assets: /" + rel (bounded by the model's caps) */
    char path_text[BREAK_EDITOR_ASSETS_PATH_CAPACITY + 16u];
    /* image preview (owned) + its widgets (weak) */
    BreakEditorImagePreview *preview;
    my_widget_t *preview_label;
    my_widget_t *preview_image;
    int preview_shown_result; /* last result reflected in the label */
    u64 preview_shown_reloads;
};

/* ---------------- row rendering / activation ---------------- */

static EditorAssetsRowCtx *assets_row_ctx_alloc(EditorPanelAssets *panel,
                                                my_widget_t *row) {
    u32 i;
    for (i = 0u; i < EDITOR_ASSETS_ROW_CTX_POOL; i++) {
        if (panel->row_ctxs[i].row == NULL) {
            EditorAssetsRowCtx *rc = &panel->row_ctxs[i];
            rc->panel = panel;
            rc->row = row;
            rc->index = 0u;
            (void)my_widget_set_user_data(row, rc);
            return rc;
        }
    }
    return NULL; /* bounded: the row still renders, click is degraded */
}

static void assets_panel_refresh(EditorPanelAssets *panel);
static void assets_preview_sync(EditorPanelAssets *panel);

void editor_panel_assets_retranslate(EditorPanelAssets *panel) {
    if (panel != NULL && panel->filter_edit != NULL) {
        (void)my_edit_set_hint(panel->filter_edit,
                               break_editor_tr(BREAK_EDITOR_TR_ASSETS_FILTER_HINT));
    }
    assets_panel_refresh(panel); /* path label + rows in the current language */
    if (panel != NULL) {
        panel->preview_shown_result = -1; /* force the label text */
        assets_preview_sync(panel);
    }
}

/* ---------------- image preview ---------------- */

static void assets_preview_log(void *user, const char *line) {
    EditorPanelAssets *panel = (EditorPanelAssets *)user;
    editor_shell_log(panel->shell, "%s", line);
}

/* Label text follows the preview state; the image widget repaints when a
 * reload lands. Cheap: compares two cached values. */
static void assets_preview_sync(EditorPanelAssets *panel) {
    BreakEditorImagePreviewStats st;
    BreakEditorTr key;
    if (panel == NULL || panel->preview == NULL ||
        !break_editor_image_preview_stats(panel->preview, &st)) {
        return;
    }
    if (st.reloads != panel->preview_shown_reloads &&
        panel->preview_image != NULL) {
        my_widget_invalidate(panel->preview_image, NULL);
    }
    panel->preview_shown_reloads = st.reloads;
    if (st.last_result == panel->preview_shown_result) {
        return;
    }
    panel->preview_shown_result = st.last_result;
    if (panel->preview_label == NULL) {
        return;
    }
    if (st.has_image) {
        char text[64];
        (void)snprintf(text, sizeof(text), "%ux%u", (unsigned)st.width,
                       (unsigned)st.height);
        (void)my_label_set_text(panel->preview_label, text);
        return;
    }
    key = st.last_result == BREAK_EDITOR_IMAGE_PREVIEW_BUSY
              ? BREAK_EDITOR_TR_PREVIEW_LOADING
          : st.last_result == BREAK_EDITOR_IMAGE_PREVIEW_EMPTY
              ? BREAK_EDITOR_TR_PREVIEW_EMPTY
              : BREAK_EDITOR_TR_PREVIEW_FAILED;
    (void)my_label_set_text(panel->preview_label, break_editor_tr(key));
}

static void assets_preview_on_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
    EditorPanelAssets *panel;
    BreakEditorImagePreviewStats st;
    RHITexture tex;
    float w, h, iw, ih, scale;
    if (widget == NULL || vg == NULL) {
        return;
    }
    w = (float)widget->rect.w;
    h = (float)widget->rect.h;
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_content_bg()));
    (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){0.0f, 0.0f, w, h});
    panel = (EditorPanelAssets *)my_widget_get_user_data(widget);
    if (panel == NULL || panel->preview == NULL ||
        !break_editor_image_preview_stats(panel->preview, &st) ||
        !st.has_image || st.width == 0u || st.height == 0u) {
        return;
    }
    tex = break_editor_image_preview_texture(panel->preview);
    if (!rhi_handle_valid(tex)) {
        return; /* headless / no device: label still shows the size */
    }
    /* aspect fit, centered */
    iw = (float)st.width;
    ih = (float)st.height;
    scale = w / iw < h / ih ? w / iw : h / ih;
    iw *= scale;
    ih *= scale;
    (void)my_vgcanvas_break_rhi_blit_texture(vg, tex, (w - iw) * 0.5f,
                                             (h - ih) * 0.5f, iw, ih);
}

static const my_widget_vtable_t s_assets_preview_vtable = {
    assets_preview_on_paint, NULL, NULL, NULL};

struct BreakEditorImagePreview *editor_panel_assets_preview(
    EditorPanelAssets *panel) {
    return panel != NULL ? panel->preview : NULL;
}

void editor_panel_assets_set_device(EditorPanelAssets *panel,
                                    RHIDevice *device) {
    if (panel != NULL) {
        break_editor_image_preview_set_device(panel->preview, device);
        if (panel->preview_image != NULL) {
            my_widget_invalidate(panel->preview_image, NULL);
        }
    }
}

static void assets_panel_refresh(EditorPanelAssets *panel) {
    const char *rel;
    if (panel == NULL) {
        return;
    }
    rel = panel->assets != NULL
              ? break_editor_assets_current_rel(panel->assets)
              : NULL;
    if (rel == NULL) {
        (void)snprintf(panel->path_text, sizeof(panel->path_text), "%s",
                       break_editor_tr(BREAK_EDITOR_TR_ASSETS_UNAVAILABLE));
    } else {
        (void)snprintf(panel->path_text, sizeof(panel->path_text),
                       break_editor_tr(BREAK_EDITOR_TR_ASSETS_PATH_FMT), rel);
    }
    if (panel->path_label != NULL) {
        (void)my_label_set_text(panel->path_label, panel->path_text);
    }
    if (panel->list != NULL) {
        (void)my_list_view_refresh(panel->list);
    }
}


/* Pak listing (2026-10-30): read-only; mounts the archive in a private VFS,
 * logs at most EDITOR_PAK_LIST_MAX entry lines plus a "more" line, then
 * drops the VFS. The current scene and document are untouched. */
#define EDITOR_PAK_LIST_MAX 16u

typedef struct {
    BreakEditorShell *shell;
    u32 total;
} EditorPakList;

static bool assets_pak_count(void *user, const char *path, u32 size) {
    (void)path;
    (void)size;
    ((EditorPakList *)user)->total++;
    return true;
}

static bool assets_pak_line(void *user, const char *path, u32 size) {
    EditorPakList *l = (EditorPakList *)user;
    editor_shell_log(l->shell, break_editor_tr(BREAK_EDITOR_TR_LOG_PAK_ENTRY_FMT),
                     path, (unsigned)size);
    return ++l->total < EDITOR_PAK_LIST_MAX;
}

static void assets_list_pak(BreakEditorShell *shell, const char *path,
                            const char *name) {
    EditorPakList l;
    u32 total;
    VFS *vfs = vfs_create();
    if (vfs == NULL || !vfs_mount_pak(vfs, path)) {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_PAK_FAILED_FMT),
                         name);
        vfs_destroy(vfs);
        return;
    }
    l.shell = shell;
    l.total = 0u;
    (void)vfs_enumerate_pak(vfs, assets_pak_count, &l);
    total = l.total;
    editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_PAK_HEADER_FMT),
                     name, (unsigned)total);
    l.total = 0u;
    (void)vfs_enumerate_pak(vfs, assets_pak_line, &l);
    if (total > l.total) {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_PAK_MORE_FMT),
                         (unsigned)(total - l.total));
    }
    vfs_destroy(vfs);
}

static void on_assets_row_click(void *ctx, const char *event, void *data) {
    EditorAssetsRowCtx *rc = (EditorAssetsRowCtx *)ctx;
    EditorPanelAssets *panel;
    BreakEditorShell *shell;
    (void)event;
    (void)data;
    if (rc == NULL || rc->panel == NULL) {
        return;
    }
    panel = rc->panel;
    shell = panel->shell;
    if (panel->assets == NULL) {
        return;
    }
    if (rc->index == 0u) {
        /* ".." — up, clamped at the root by the model */
        (void)break_editor_assets_up(panel->assets);
        assets_panel_refresh(panel);
        return;
    }
    {
        usize ei = rc->index - 1u;
        const char *name = NULL;
        bool is_dir = false;
        if (!break_editor_assets_entry_at(panel->assets, ei, &name,
                                          &is_dir) ||
            name == NULL) {
            return;
        }
        if (is_dir) {
            /* enter validates the exact listed name (single segment) */
            if (break_editor_assets_enter(panel->assets, name)) {
                assets_panel_refresh(panel);
            }
            return;
        }
        /* a file: only .bscn scenes are loadable */
        {
            size_t len = strlen(name);
            if (len >= 5u && strcmp(name + len - 5u, ".bscn") == 0) {
                char path[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
                if (break_editor_assets_abs_path(panel->assets, ei, path,
                                                 sizeof(path))) {
                    /* world swap + undo-stack clear + scene path / watcher
                     * update, all in the shell helper */
                    (void)editor_shell_load_scene_guarded(shell, path);
                }
            } else if (len >= 4u && strcmp(name + len - 4u, ".pak") == 0) {
                char path[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
                if (break_editor_assets_abs_path(panel->assets, ei, path,
                                                 sizeof(path))) {
                    assets_list_pak(shell, path, name);
                }
            } else if (break_editor_image_is_supported_name(name)) {
                char path[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
                if (break_editor_assets_abs_path(panel->assets, ei, path,
                                                 sizeof(path))) {
                    (void)break_editor_image_preview_set_path(panel->preview,
                                                              path);
                    assets_preview_sync(panel);
                }
            } else {
                editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_ASSET_NOT_SCENE_FMT),
                                 name);
            }
        }
    }
}

static size_t assets_adapter_count(my_list_adapter_t *adapter) {
    EditorAssetsAdapter *a =
        (EditorAssetsAdapter *)((char *)adapter -
                                offsetof(EditorAssetsAdapter, base));
    if (a->panel->assets == NULL) {
        return 1u; /* just the ".." row (clamped no-op at the root) */
    }
    return (size_t)break_editor_assets_count(a->panel->assets) + 1u;
}

static my_widget_t *assets_adapter_create_row(my_list_adapter_t *adapter) {
    EditorAssetsAdapter *a =
        (EditorAssetsAdapter *)((char *)adapter -
                                offsetof(EditorAssetsAdapter, base));
    my_widget_t *row = my_button_create(NULL, "");
    if (row == NULL) {
        return NULL;
    }
    (void)my_widget_set_name(row, "editor-assets-row");
    {
        EditorAssetsRowCtx *rc = assets_row_ctx_alloc(a->panel, row);
        if (rc != NULL) {
            (void)my_widget_on(row, "click", on_assets_row_click, rc);
        }
    }
    return row;
}

static void assets_adapter_bind_row(my_list_adapter_t *adapter,
                                    my_widget_t *row, size_t index) {
    EditorAssetsAdapter *a =
        (EditorAssetsAdapter *)((char *)adapter -
                                offsetof(EditorAssetsAdapter, base));
    EditorAssetsRowCtx *rc = (EditorAssetsRowCtx *)my_widget_get_user_data(row);
    if (rc != NULL) {
        rc->index = (usize)index;
    }
    if (index == 0u) {
        (void)my_button_set_text(row, "..");
        return;
    }
    {
        const char *name = NULL;
        bool is_dir = false;
        if (a->panel->assets != NULL &&
            break_editor_assets_entry_at(a->panel->assets, (usize)index - 1u,
                                         &name, &is_dir) &&
            name != NULL) {
            if (is_dir) {
                char label[BREAK_EDITOR_ASSETS_NAME_CAPACITY + 1u];
                (void)snprintf(label, sizeof(label), "%s/", name);
                (void)my_button_set_text(row, label);
            } else {
                (void)my_button_set_text(row, name);
            }
        } else {
            (void)my_button_set_text(row,
                                     break_editor_tr(BREAK_EDITOR_TR_STALE_ROW));
        }
    }
}

static const my_list_adapter_vtable_t k_assets_adapter_vtable = {
    assets_adapter_count, assets_adapter_create_row, assets_adapter_bind_row,
    NULL};

/* ---------------- lifecycle ---------------- */

EditorPanelAssets *editor_panel_assets_create(BreakEditorShell *shell) {
    EditorPanelAssets *panel;
    if (shell == NULL) {
        return NULL;
    }
    panel = (EditorPanelAssets *)calloc(1u, sizeof(EditorPanelAssets));
    if (panel == NULL) {
        return NULL;
    }
    panel->shell = shell;
    /* default root: the process cwd (documented; a failure degrades to an
     * empty panel — re-root later via editor_panel_assets_set_root) */
    panel->assets = break_editor_assets_create(".");
    panel->path_text[0] = '\0';
    /* a preview create failure degrades to "no preview" (NULL-safe API) */
    panel->preview = break_editor_image_preview_create();
    break_editor_image_preview_set_logger(panel->preview, assets_preview_log,
                                          panel);
    panel->preview_shown_result = -1;
    return panel;
}

void editor_panel_assets_destroy(EditorPanelAssets *panel) {
    if (panel == NULL) {
        return;
    }
    /* CPU-side state only — the widgets belong to the window tree. The
     * preview's texture needs the device alive: the shell is destroyed
     * before the device (editor_main), so this releases it in time. A
     * preview whose worker does not stop in time is leaked, not freed
     * under the worker (editor_image_preview_destroy contract). */
    break_editor_image_preview_destroy(panel->preview);
    break_editor_assets_destroy(panel->assets);
    free(panel);
}

/* Enter in the filter box: apply the extension CSV; empty shows everything.
 * The model matches tokens byte-wise and case-sensitively, so the box
 * normalises what a person types: ASCII lower case, spaces and a leading
 * '.' dropped ("bscn, .PNG" -> "bscn,png"). Directories always stay. */
static void on_assets_filter_activate(void *ctx, const char *event,
                                      void *data) {
    EditorPanelAssets *panel = (EditorPanelAssets *)ctx;
    const char *text = (const char *)data;
    (void)event;
    if (panel == NULL || text == NULL) {
        return;
    }
    {
        usize o = 0u;
        bool token_start = true;
        for (const char *c = text; *c != '\0' && o + 1u < sizeof(panel->filter);
             c++) {
            char ch = *c;
            if (ch == ' ' || ch == '\t') continue;
            if (ch == '.' && token_start) continue;
            if (ch >= 'A' && ch <= 'Z') ch = (char)(ch - 'A' + 'a');
            panel->filter[o++] = ch;
            token_start = ch == ',';
        }
        panel->filter[o] = '\0';
    }
    if (panel->assets != NULL) {
        break_editor_assets_set_filter(panel->assets, panel->filter);
    }
    assets_panel_refresh(panel);
}

bool editor_panel_assets_build(EditorPanelAssets *panel, my_widget_t *parent) {
    my_widget_t *section;
    if (panel == NULL || parent == NULL) {
        return false;
    }
    section = my_widget_create(NULL, "editor-assets-panel");
    if (section == NULL) {
        return false;
    }
    (void)my_widget_set_layouter(section,
                                 my_layouter_linear_create(NULL, false, 2));
    panel->path_label = my_label_create(
        NULL, break_editor_tr(BREAK_EDITOR_TR_ASSETS_PREFIX));
    if (panel->path_label == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(panel->path_label, "editor-assets-path");
    (void)my_widget_set_layout_params(panel->path_label, "w:100% h:22");
    if (my_widget_add_child(section, panel->path_label) == MY_RET_OK) {
        my_widget_unref(panel->path_label); /* tree holds its own reference */
    } else {
        my_widget_unref(panel->path_label);
        my_widget_unref(section);
        return false;
    }
    panel->filter_edit = my_edit_create(NULL);
    if (panel->filter_edit == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(panel->filter_edit, "editor-assets-filter");
    (void)my_edit_set_hint(panel->filter_edit,
                           break_editor_tr(BREAK_EDITOR_TR_ASSETS_FILTER_HINT));
    (void)my_edit_set_max_len(panel->filter_edit, sizeof(panel->filter) - 1u);
    (void)my_widget_on(panel->filter_edit, "activate", on_assets_filter_activate,
                       panel);
    (void)my_widget_set_layout_params(panel->filter_edit, "w:100% h:24");
    if (my_widget_add_child(section, panel->filter_edit) == MY_RET_OK) {
        my_widget_unref(panel->filter_edit);
    } else {
        my_widget_unref(panel->filter_edit);
        panel->filter_edit = NULL;
        my_widget_unref(section);
        return false;
    }
    panel->list = my_list_view_create(NULL);
    if (panel->list == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(panel->list, "editor-assets-list");
    panel->adapter.base.vtable = &k_assets_adapter_vtable;
    panel->adapter.panel = panel;
    if (my_list_view_set_adapter(panel->list, &panel->adapter.base) !=
        MY_RET_OK) {
        my_widget_unref(panel->list);
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_layout_params(panel->list, "w:100% h:1f");
    if (my_widget_add_child(section, panel->list) == MY_RET_OK) {
        my_widget_unref(panel->list); /* tree holds its own reference */
    } else {
        my_widget_unref(panel->list);
        my_widget_unref(section);
        return false;
    }
    /* under the outliner: bottom-left section, 40% of the column height */
    (void)my_widget_set_layout_params(section, "w:100% h:40%");
    if (my_widget_add_child(parent, section) == MY_RET_OK) {
        my_widget_unref(section); /* tree holds its own reference */
    } else {
        my_widget_unref(section);
        return false;
    }
    /* preview section: its own row under the browser, so the list keeps
     * its height. State/size label + painted image area. */
    {
        my_widget_t *pv = my_widget_create(NULL, "editor-assets-preview-panel");
        if (pv == NULL) {
            return false;
        }
        (void)my_widget_set_layouter(pv, my_layouter_linear_create(NULL, false, 2));
        panel->preview_label = my_label_create(
            NULL, break_editor_tr(BREAK_EDITOR_TR_PREVIEW_EMPTY));
        if (panel->preview_label == NULL) {
            my_widget_unref(pv);
            return false;
        }
        (void)my_widget_set_name(panel->preview_label,
                                 "editor-assets-preview-label");
        (void)my_widget_set_layout_params(panel->preview_label, "w:100% h:20");
        if (my_widget_add_child(pv, panel->preview_label) == MY_RET_OK) {
            my_widget_unref(panel->preview_label);
        } else {
            my_widget_unref(panel->preview_label);
            panel->preview_label = NULL;
            my_widget_unref(pv);
            return false;
        }
        panel->preview_image = my_widget_create(NULL, "editor-assets-preview");
        if (panel->preview_image == NULL ||
            my_widget_subclass_init(panel->preview_image,
                                    &s_assets_preview_vtable) != MY_RET_OK) {
            if (panel->preview_image != NULL) {
                my_widget_unref(panel->preview_image);
            }
            panel->preview_image = NULL;
            my_widget_unref(pv);
            return false;
        }
        (void)my_widget_set_name(panel->preview_image, "editor-assets-preview");
        (void)my_widget_set_user_data(panel->preview_image, panel);
        (void)my_widget_set_layout_params(panel->preview_image, "w:100% h:1f");
        if (my_widget_add_child(pv, panel->preview_image) == MY_RET_OK) {
            my_widget_unref(panel->preview_image);
        } else {
            my_widget_unref(panel->preview_image);
            panel->preview_image = NULL;
            my_widget_unref(pv);
            return false;
        }
        (void)my_widget_set_layout_params(pv, "w:100% h:20%");
        if (my_widget_add_child(parent, pv) == MY_RET_OK) {
            my_widget_unref(pv);
        } else {
            my_widget_unref(pv);
            panel->preview_label = NULL;
            panel->preview_image = NULL;
            return false;
        }
    }
    assets_panel_refresh(panel);
    return true;
}

/* Live listing: the retained UI only repaints on damage, so the directory
 * the browser shows is re-listed at most once per EDITOR_ASSETS_REFRESH_US
 * and the panel repaints only when the listing actually changed. A recursive
 * watcher is deliberately not used: the default root is the process cwd
 * (a full-tree inotify walk of a repository checkout took seconds), and one
 * directory level is all the panel ever shows. */
#define EDITOR_ASSETS_REFRESH_US 1000000u

void editor_panel_assets_tick(EditorPanelAssets *panel) {
    u64 now;
    bool changed = false;
    if (panel == NULL) {
        return;
    }
    assets_preview_sync(panel); /* reflects the previous frame's preview tick */
    if (panel->assets == NULL) {
        return;
    }
    now = panel->clock != NULL ? panel->clock(panel->clock_user)
                               : time_microseconds();
    if (!panel->primed) {
        /* the panel was just painted by build/set_root; start the interval */
        panel->primed = true;
        panel->last_refresh_us = now;
        return;
    }
    if (now - panel->last_refresh_us < EDITOR_ASSETS_REFRESH_US) {
        return;
    }
    panel->last_refresh_us = now;
    (void)break_editor_assets_refresh(panel->assets, &changed);
    if (changed) {
        assets_panel_refresh(panel);
    }
}

void editor_panel_assets_set_clock(EditorPanelAssets *panel,
                                   u64 (*clock)(void *user), void *user) {
    if (panel != NULL) {
        panel->clock = clock;
        panel->clock_user = user;
        panel->primed = false;
    }
}

bool editor_panel_assets_set_root(EditorPanelAssets *panel,
                                  const char *root_path) {
    BreakEditorAssets *fresh;
    if (panel == NULL || root_path == NULL) {
        return false;
    }
    fresh = break_editor_assets_create(root_path);
    if (fresh == NULL) {
        return false; /* bounded: previous root/model kept */
    }
    break_editor_assets_destroy(panel->assets);
    panel->assets = fresh;
    if (panel->filter[0] != '\0') {
        break_editor_assets_set_filter(panel->assets, panel->filter);
    }
    panel->primed = false;
    assets_panel_refresh(panel);
    return true;
}

usize editor_panel_assets_row_count(const EditorPanelAssets *panel) {
    if (panel == NULL) {
        return 0u;
    }
    if (panel->assets == NULL) {
        return 1u; /* the ".." row still renders */
    }
    return break_editor_assets_count(panel->assets) + 1u;
}

const char *editor_panel_assets_path_text(const EditorPanelAssets *panel) {
    return panel != NULL ? panel->path_text : "";
}
