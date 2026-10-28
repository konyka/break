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

#include <editor/editor_i18n.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editor/editor_assets.h>
#include <editor/editor_scene.h>
#include <platform/time.h>

#include "myc/my_emitter.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_button.h"
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
    EditorAssetsAdapter adapter;
    EditorAssetsRowCtx row_ctxs[EDITOR_ASSETS_ROW_CTX_POOL];
    /* hot refresh: throttled re-list of the CURRENT directory */
    u64 (*clock)(void *user); /* NULL = time_microseconds */
    void *clock_user;
    u64 last_refresh_us;
    bool primed;
    /* label text cache: "assets: /" + rel (bounded by the model's caps) */
    char path_text[BREAK_EDITOR_ASSETS_PATH_CAPACITY + 16u];
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

void editor_panel_assets_retranslate(EditorPanelAssets *panel) {
    assets_panel_refresh(panel); /* path label + rows in the current language */
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
                    (void)editor_shell_load_scene(shell, path);
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
    return panel;
}

void editor_panel_assets_destroy(EditorPanelAssets *panel) {
    if (panel == NULL) {
        return;
    }
    /* CPU-side state only — the widgets belong to the window tree */
    break_editor_assets_destroy(panel->assets);
    free(panel);
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
    if (panel == NULL || panel->assets == NULL) {
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
