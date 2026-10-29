/* BreakEditorShell implementation — see editor_panels.h for the architecture,
 * the shortcut table contract, the layering rule (widget callbacks never call
 * world_* directly; every mutation routes through break_editor_doc_* /
 * break_editor_undo/redo), and the bounds documentation. */

#include "editor_panels.h"
#include "editor_shell_internal.h"
#include "editor_viewport3d.h"
#include "editor_remote.h"
#include "editor_hot_reload.h"
#include "editor_settings.h"
#include "editor_theme.h"

#ifdef BREAK_EDITOR_SHELL_TESTING
static bool g_editor_fail_diag_attach;
void break_editor_shell_fail_diag_attach_for_test(void) {
    g_editor_fail_diag_attach = true;
}
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editor/editor_cmd.h>
#include <editor/editor_i18n.h>
#include <editor/editor_components.h>
#include <editor/editor_scene.h>

#include "mypal/dummy/my_pal_dummy.h"
#include "mypal/my_event.h"
#include "mypal/my_pal.h"
#include "myui/my_layout.h"
#include "myui/my_widget.h"
#include "myui/my_window.h"
#include "myui/my_window_manager.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_list_view.h"
#include "myui/widgets/my_text_area.h"

/* ---------------- bounds (editor_panels.h header comment) ---------------- */

#define EDITOR_CONSOLE_CAPACITY 64u
#define EDITOR_CONSOLE_LINE_BYTES 128u
#define EDITOR_STATUS_BYTES 256u
#define EDITOR_ROW_CTX_POOL 64u
#define EDITOR_FIELD_CTX_POOL \
    (BREAK_EDITOR_COMPONENT_REGISTRY_CAPACITY * 9u)
#define EDITOR_PALETTE_COMMAND_COUNT 16u
#define EDITOR_EXTRA_SELECTION_MAX 64u
#define EDITOR_TEST_WINDOW_W 800
#define EDITOR_TEST_WINDOW_H 480

/* ---------------- shell state ---------------- */

typedef struct {
    BreakEditorShell *shell;   /* borrowed */
    my_widget_t *row;          /* borrowed (NULL = pool slot unused) */
    usize index;               /* bound row position (adapter index space) */
    u8 kind;                   /* 0 = outliner row, 1 = palette row */
} EditorRowCtx;

typedef struct {
    BreakEditorShell *shell;   /* borrowed */
    u32 component_id;
    u32 field_index;           /* UINT32_MAX = component add/remove button */
} EditorFieldCtx;

typedef struct {
    my_list_adapter_t base;
    BreakEditorShell *shell;   /* borrowed */
    u8 kind;                   /* 0 = outliner, 1 = palette */
} EditorListAdapter;

struct BreakEditorShell {
    /* test-path ownership (all NULL on the real-window path) */
    my_pal_t *pal;
    my_pal_main_loop_t *loop;
    my_window_manager_t *wm;
    my_window_t *win;          /* owned (test) / borrowed (real) */
    bool owns_window;

    BreakEditorDoc *doc;       /* owned */

    my_widget_t *root;         /* weak (owned by the window tree) */
    my_widget_t *tool_label;
    my_widget_t *outliner_list;
    my_widget_t *inspector;
    my_widget_t *name_edit;    /* weak: rebuilt with the inspector */
    my_widget_t *console_area;
    my_widget_t *status_label;
    my_widget_t *palette;
    my_widget_t *palette_edit;
    my_widget_t *palette_list;

    EditorListAdapter outliner_adapter;
    EditorListAdapter palette_adapter;
    EditorRowCtx row_ctxs[EDITOR_ROW_CTX_POOL];
    EditorFieldCtx field_ctxs[EDITOR_FIELD_CTX_POOL];
    u32 field_ctx_count;

    BreakEditorEntityId selected;
    /* Ctrl+click multi-select: entities selected in addition to the
     * primary `selected` (never contains it). Pruned on every sync. */
    BreakEditorEntityId extra[EDITOR_EXTRA_SELECTION_MAX];
    u32 extra_count;
    usize anchor_index; /* outliner row of the last plain/Ctrl click */
    u32 tool; /* 0 select, 1 translate, 2 rotate, 3 scale */

    /* Phase 2 Task 3 viewport state (see editor_panels.h): the camera is
     * view state (never undoable); the gizmo is glued to the selection via
     * shell_gizmo_reconcile; vp3d is the GPU side (no GPU objects on the
     * dummy-PAL test path — render is a guarded no-op there). */
    BreakEditorCamera camera;
    BreakEditorGizmo *gizmo;              /* owned */
    BreakEditorViewport3D *vp3d;          /* owned */
    my_widget_t *viewport_widget;         /* weak (owned by the tree) */
    BreakEditorEntityId gizmo_attached;   /* reconcile cache */

    /* Phase 3 Task 3 panels (opaque; owned by the shell, see
     * editor_shell_internal.h for the create/build/destroy contract): assets
     * browser under the outliner, Lua console at bottom-right, profiler view
     * under the inspector. */
    EditorPanelAssets *assets_panel;
    EditorPanelLua *lua_panel;
    EditorPanelProfiler *profiler_panel;
    /* Phase 4 Task 3: network diagnostics (pure view over `remote` below;
     * diagnostics column, under the profiler). */
    BreakEditorPanelNetwork *network_panel;
    /* render debugger (pure view over the borrowed device + vp3d stats;
     * diagnostics column, under the network panel) */
    BreakEditorPanelRender *render_panel;

    /* Phase 4 Task 1: host-attached remote session (BORROWED — DEFAULT OFF;
     * the shell only ticks it, never creates or destroys it). */
    BreakEditorRemote *remote;

    /* editor asset hot reload (BORROWED — host-owned, DEFAULT OFF) */
    BreakEditorHotReload *hot_reload;

    /* tool-window tab areas (0 bottom, 1 diagnostics): active page index
     * and the click contexts of their tab buttons */
    u32 active_tab[2];
    bool snap; /* gizmo snapping on (EDITOR_SNAP_* steps) */
    /* persisted UI preferences (editor_settings.h): saved after each
     * theme / language / tab change once a path is set; empty = off */
    char settings_path[1024];
    struct EditorTabCtx {
        BreakEditorShell *shell;
        u32 area, index;
    } tab_ctxs[5];

    bool palette_open;
    u32 palette_matches[EDITOR_PALETTE_COMMAND_COUNT];
    u32 palette_match_count;
    u32 palette_cursor; /* highlighted match (Up/Down), run by Enter */

    char console_ring[EDITOR_CONSOLE_CAPACITY][EDITOR_CONSOLE_LINE_BYTES];
    u32 console_head;  /* next write slot */
    u32 console_count; /* entries in use */
    /* joined console text: capacity lines x (line bytes + '\n') + NUL */
    char console_text[EDITOR_CONSOLE_CAPACITY *
                          (EDITOR_CONSOLE_LINE_BYTES + 1u) +
                      1u];

    char status_text[EDITOR_STATUS_BYTES];
    char note[EDITOR_CONSOLE_LINE_BYTES]; /* status-bar intent note */
    /* close guard: revision at the last unsaved-changes warning (+1 so 0 =
     * never warned) */
    u64 close_warned_rev;

    char scene_path[BREAK_EDITOR_SCENE_PATH_CAPACITY];
    bool scene_path_set;
};

/* ---------------- small helpers ---------------- */

/* All user-visible text goes through break_editor_tr (editor_i18n.h). */
static const BreakEditorTr k_tool_keys[4] = {
    BREAK_EDITOR_TR_TOOL_SELECT, BREAK_EDITOR_TR_TOOL_TRANSLATE,
    BREAK_EDITOR_TR_TOOL_ROTATE, BREAK_EDITOR_TR_TOOL_SCALE};

static const char *shell_tool_name(u32 tool) {
    return break_editor_tr(k_tool_keys[tool & 3u]);
}

enum {
    PAL_ADD_ENTITY = 0,
    PAL_REMOVE_SELECTED,
    PAL_RENAME_SELECTED,
    PAL_SAVE,
    PAL_UNDO,
    PAL_REDO,
    PAL_TOOL_SELECT,
    PAL_TOOL_TRANSLATE,
    PAL_TOOL_ROTATE,
    PAL_TOOL_SCALE,
    PAL_LANG_EN,
    PAL_LANG_ZH,
    PAL_THEME_LIGHT,
    PAL_THEME_DARK,
    PAL_DUPLICATE_SELECTED,
    PAL_TOGGLE_SNAP
};

/* Current-language text of palette command `cmd` (bounded, never NULL). */
static const char *shell_palette_text(u32 cmd, char *buf, size_t cap) {
    static const BreakEditorTr plain[PAL_TOOL_SELECT] = {
        BREAK_EDITOR_TR_CMD_ADD_ENTITY, BREAK_EDITOR_TR_CMD_REMOVE_SELECTED,
        BREAK_EDITOR_TR_CMD_RENAME_SELECTED, BREAK_EDITOR_TR_CMD_SAVE_SCENE,
        BREAK_EDITOR_TR_CMD_UNDO, BREAK_EDITOR_TR_CMD_REDO};
    if (cmd < PAL_TOOL_SELECT) {
        return break_editor_tr(plain[cmd]);
    }
    if (cmd <= PAL_TOOL_SCALE) {
        (void)snprintf(buf, cap, break_editor_tr(BREAK_EDITOR_TR_CMD_TOOL_FMT),
                       shell_tool_name(cmd - PAL_TOOL_SELECT));
        return buf;
    }
    if (cmd == PAL_LANG_EN) {
        return break_editor_tr(BREAK_EDITOR_TR_CMD_LANG_EN);
    }
    if (cmd == PAL_LANG_ZH) {
        return break_editor_tr(BREAK_EDITOR_TR_CMD_LANG_ZH);
    }
    if (cmd == PAL_THEME_LIGHT) {
        return break_editor_tr(BREAK_EDITOR_TR_CMD_THEME_LIGHT);
    }
    if (cmd == PAL_THEME_DARK) {
        return break_editor_tr(BREAK_EDITOR_TR_CMD_THEME_DARK);
    }
    if (cmd == PAL_DUPLICATE_SELECTED) {
        return break_editor_tr(BREAK_EDITOR_TR_CMD_DUPLICATE_SELECTED);
    }
    if (cmd == PAL_TOGGLE_SNAP) {
        return break_editor_tr(BREAK_EDITOR_TR_CMD_TOGGLE_SNAP);
    }
    return "?";
}

static void shell_execute_palette_command(BreakEditorShell *shell, u32 cmd);
static void shell_tabs_retranslate(BreakEditorShell *shell);
static void shell_settings_save(BreakEditorShell *shell);
static void shell_end_gizmo_drag(BreakEditorShell *shell);
static void shell_outliner_mark_selection(BreakEditorShell *shell);
static int shell_extra_index(const BreakEditorShell *shell,
                             BreakEditorEntityId id);
static void shell_set_snap(BreakEditorShell *shell, bool on);
static void shell_palette_set_open(BreakEditorShell *shell, bool open);

/* Bounded console log: appends one <=127-byte line to the ring, dropping the
 * oldest entry when full, and republishes the joined text to the read-only
 * console widget. Non-static: the Phase 3 panels route their lines (lua|
 * output, asset load notices) through it (editor_shell_internal.h). */
void editor_shell_log(BreakEditorShell *shell, const char *fmt, ...) {
    char line[EDITOR_CONSOLE_LINE_BYTES];
    va_list ap;
    size_t pos = 0u;
    u32 i;
    if (shell == NULL || fmt == NULL) {
        return;
    }
    va_start(ap, fmt);
    (void)vsnprintf(line, sizeof(line), fmt, ap);
    va_end(ap);
    line[sizeof(line) - 1u] = '\0';
    if (shell->console_count < EDITOR_CONSOLE_CAPACITY) {
        u32 slot = (shell->console_head + shell->console_count) %
                   EDITOR_CONSOLE_CAPACITY;
        memcpy(shell->console_ring[slot], line, sizeof(line));
        shell->console_count++;
    } else {
        /* ring full: overwrite the oldest, advance the head */
        memcpy(shell->console_ring[shell->console_head], line, sizeof(line));
        shell->console_head =
            (shell->console_head + 1u) % EDITOR_CONSOLE_CAPACITY;
    }
    for (i = 0u; i < shell->console_count; i++) {
        u32 slot =
            (shell->console_head + i) % EDITOR_CONSOLE_CAPACITY;
        size_t len = strlen(shell->console_ring[slot]);
        if (pos + len + 2u > sizeof(shell->console_text)) {
            break; /* bounded: never overflow the joined buffer */
        }
        memcpy(shell->console_text + pos, shell->console_ring[slot], len);
        pos += len;
        shell->console_text[pos++] = '\n';
    }
    shell->console_text[pos] = '\0';
    if (shell->console_area != NULL) {
        (void)my_text_area_set_text(shell->console_area,
                                    shell->console_text);
    }
}

static void shell_refresh_status(BreakEditorShell *shell) {
    char last[128];
    if (shell == NULL || shell->status_label == NULL) {
        return;
    }
    last[0] = '\0';
    (void)break_editor_cmd_stack_describe_last(
        break_editor_doc_stack(shell->doc), last);
    if (last[0] == '\0') {
        snprintf(last, sizeof(last), "-");
    }
    (void)snprintf(shell->status_text, sizeof(shell->status_text),
                   break_editor_tr(BREAK_EDITOR_TR_STATUS_FMT),
                   (unsigned long long)break_editor_doc_entity_count(
                       shell->doc),
                   break_editor_doc_is_dirty(shell->doc) ? 1 : 0, last,
                   shell->note);
    (void)my_label_set_text(shell->status_label, shell->status_text);
}

static void shell_refresh_tool_label(BreakEditorShell *shell) {
    char buf[96];
    if (shell == NULL || shell->tool_label == NULL) {
        return;
    }
    {
        int n = snprintf(buf, sizeof(buf),
                         break_editor_tr(BREAK_EDITOR_TR_TOOL_LABEL_FMT),
                         shell_tool_name(shell->tool));
        if (shell->snap && n > 0 && (usize)n < sizeof(buf)) {
            (void)snprintf(buf + n, sizeof(buf) - (usize)n, "%s",
                           break_editor_tr(BREAK_EDITOR_TR_SNAP_SUFFIX));
        }
    }
    (void)my_label_set_text(shell->tool_label, buf);
}

/* Glue between the selection and the gizmo (Phase 2 Task 3): attach when the
 * selection is valid, detach when it cleared. Idempotent — the reconcile
 * cache avoids redundant attach calls (attach ALWAYS end-drags first, Task 2
 * contract, so a redundant attach mid-drag would commit it early). Also
 * rewires the viewport's borrowed view state on selection changes (highlight
 * tint). */
static void shell_gizmo_reconcile(BreakEditorShell *shell) {
    BreakEditorEntityId want = BREAK_EDITOR_ENTITY_NULL;
    if (shell == NULL || shell->gizmo == NULL) {
        return;
    }
    if (break_editor_entity_id_valid(shell->selected)) {
        want = shell->selected;
    }
    if (!break_editor_entity_id_eq(want, shell->gizmo_attached)) {
        if (break_editor_entity_id_valid(want)) {
            break_editor_gizmo_attach(shell->gizmo, shell->doc, want);
        } else {
            break_editor_gizmo_attach(shell->gizmo, NULL,
                                      BREAK_EDITOR_ENTITY_NULL);
        }
        shell->gizmo_attached = want;
        if (shell->vp3d != NULL) {
            break_editor_viewport3d_set_view_state(
                shell->vp3d, &shell->camera, shell->gizmo, shell->selected);
        }
    }
}

/* Re-validate the shell selection against the doc; clears it when the entity
 * no longer exists (remove, undo, load). Returns true when still valid. */
static bool shell_sync_selection(BreakEditorShell *shell) {
    usize i, n;
    bool valid = false;
    if (shell == NULL) {
        return false;
    }
    if (break_editor_entity_id_valid(shell->selected)) {
        n = break_editor_doc_entity_count(shell->doc);
        for (i = 0u; i < n; i++) {
            BreakEditorEntityId id;
            const char *unused = NULL;
            if (break_editor_doc_entity_at(shell->doc, i, &id, &unused) &&
                break_editor_entity_id_eq(id, shell->selected)) {
                valid = true;
                break;
            }
        }
        if (!valid) {
            shell->selected = BREAK_EDITOR_ENTITY_NULL;
        }
    }
    {
        u32 k = 0u;
        for (u32 i = 0u; i < shell->extra_count; i++) {
            BreakEditorEntityId id = shell->extra[i];
            bool live = false;
            for (usize j = 0u; j < break_editor_doc_entity_count(shell->doc); j++) {
                BreakEditorEntityId e;
                const char *unused = NULL;
                if (break_editor_doc_entity_at(shell->doc, j, &e, &unused) &&
                    break_editor_entity_id_eq(e, id)) {
                    live = true;
                    break;
                }
            }
            if (live && !break_editor_entity_id_eq(id, shell->selected)) {
                shell->extra[k++] = id;
            }
        }
        shell->extra_count = k;
        break_editor_viewport3d_set_extra_selection(shell->vp3d, shell->extra,
                                                    shell->extra_count);
    }
    shell_gizmo_reconcile(shell);
    return valid;
}

/* Borrowed display name for an id, NULL when stale. */
static const char *shell_entity_name(BreakEditorShell *shell,
                                     BreakEditorEntityId id) {
    usize i, n = break_editor_doc_entity_count(shell->doc);
    for (i = 0u; i < n; i++) {
        BreakEditorEntityId cur;
        const char *name = NULL;
        if (break_editor_doc_entity_at(shell->doc, i, &cur, &name) &&
            break_editor_entity_id_eq(cur, id)) {
            return name;
        }
    }
    return NULL;
}

/* ---------------- inspector ---------------- */

/* Names a freshly created widget (NULL passes through) so retranslation can
 * find it later by name. */
static my_widget_t *shell_named(my_widget_t *w, const char *name) {
    if (w != NULL) {
        (void)my_widget_set_name(w, name);
    }
    return w;
}

static void shell_add_child(my_widget_t *parent, my_widget_t *child,
                            const char *params) {
    if (child == NULL) {
        return;
    }
    if (params != NULL) {
        (void)my_widget_set_layout_params(child, params);
    }
    if (my_widget_add_child(parent, child) == MY_RET_OK) {
        my_widget_unref(child); /* tree holds its own reference */
    } else {
        my_widget_unref(child);
    }
}

static void on_name_edit_activate(void *ctx, const char *event, void *data) {
    BreakEditorShell *shell = (BreakEditorShell *)ctx;
    const char *text = (const char *)data;
    (void)event;
    if (shell == NULL || text == NULL ||
        !break_editor_entity_id_valid(shell->selected)) {
        return;
    }
    shell_end_gizmo_drag(shell);
    if (break_editor_doc_rename_entity(shell->doc, shell->selected, text)) {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_RENAME_FMT), text);
    } else {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_RENAME_FAILED_FMT),
                  BREAK_EDITOR_NAME_CAPACITY);
    }
    editor_shell_refresh_all(shell);
}

static void on_field_edit_activate(void *ctx, const char *event, void *data) {
    EditorFieldCtx *fc = (EditorFieldCtx *)ctx;
    const char *text = (const char *)data;
    f32 value;
    if (fc == NULL || fc->shell == NULL || text == NULL) {
        return;
    }
    (void)event;
    if (!break_editor_parse_f32(text, &value)) {
        editor_shell_log(fc->shell, break_editor_tr(BREAK_EDITOR_TR_LOG_INVALID_F32_FMT), text);
        editor_shell_refresh_all(fc->shell);
        return;
    }
    shell_end_gizmo_drag(fc->shell);
    if (break_editor_doc_set_field_f32(fc->shell->doc, fc->shell->selected,
                                       fc->component_id, fc->field_index,
                                       value)) {
        editor_shell_log(fc->shell, break_editor_tr(BREAK_EDITOR_TR_LOG_SET_FIELD_FMT),
                  fc->component_id == BREAK_EDITOR_COMPONENT_TRANSFORM
                      ? "transform"
                      : "component",
                  (unsigned)fc->field_index, (double)value);
    } else {
        editor_shell_log(fc->shell, break_editor_tr(BREAK_EDITOR_TR_LOG_SET_FIELD_FAILED));
    }
    editor_shell_refresh_all(fc->shell);
}

static void on_component_button_click(void *ctx, const char *event,
                                      void *data) {
    EditorFieldCtx *fc = (EditorFieldCtx *)ctx;
    BreakEditorShell *shell;
    (void)event;
    (void)data;
    if (fc == NULL || fc->shell == NULL) {
        return;
    }
    shell = fc->shell;
    if (!break_editor_entity_id_valid(shell->selected)) {
        return;
    }
    if (fc->field_index == 0u) {
        /* add button */
        shell_end_gizmo_drag(shell);
        if (break_editor_doc_add_component(shell->doc, shell->selected,
                                           fc->component_id)) {
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_ADD_COMPONENT_FMT), (unsigned)fc->component_id);
        } else {
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_ADD_COMPONENT_FAILED_FMT),
                      (unsigned)fc->component_id);
        }
    } else {
        shell_end_gizmo_drag(shell);
        if (break_editor_doc_remove_component(shell->doc, shell->selected,
                                              fc->component_id)) {
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_REMOVE_COMPONENT_FMT),
                      (unsigned)fc->component_id);
        } else {
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_REMOVE_COMPONENT_FAILED_FMT),
                      (unsigned)fc->component_id);
        }
    }
    editor_shell_refresh_all(shell);
}

/* Rebuilds the inspector subtree from the current selection. Bounded: at
 * most registry-capacity (16) sections x 9 field rows; all widget names and
 * texts are capped (field name[32], edit max_len 127 codepoints). */
static void shell_rebuild_inspector(BreakEditorShell *shell) {
    my_widget_t *insp = shell->inspector;
    usize ci, cn;
    if (insp == NULL) {
        return;
    }
    while (my_widget_child_count(insp) > 0u) {
        (void)my_widget_remove_child(insp, my_widget_get_child(insp, 0u));
    }
    shell->name_edit = NULL;
    shell->field_ctx_count = 0u;

    if (!shell_sync_selection(shell)) {
        shell_add_child(insp,
                        shell_named(my_label_create(NULL, break_editor_tr(
                                        BREAK_EDITOR_TR_NO_SELECTION)),
                                    "editor-inspector-empty-label"),
                        "w:100% h:24");
        return;
    }

    /* name row */
    {
        const char *name = shell_entity_name(shell, shell->selected);
        my_widget_t *edit = my_edit_create(NULL);
        shell_add_child(insp,
                        shell_named(my_label_create(
                                        NULL, break_editor_tr(BREAK_EDITOR_TR_NAME)),
                                    "editor-inspector-name-label"),
                        "w:100% h:22");
        if (edit != NULL) {
            (void)my_widget_set_name(edit, "editor-name-edit");
            (void)my_edit_set_hint(edit,
                                   break_editor_tr(BREAK_EDITOR_TR_ENTITY_NAME_HINT));
            (void)my_edit_set_max_len(edit,
                                      BREAK_EDITOR_NAME_CAPACITY - 1u);
            (void)my_edit_set_text(edit, name != NULL ? name : "");
            (void)my_widget_on(edit, "activate", on_name_edit_activate,
                               shell);
            shell_add_child(insp, edit, "w:100% h:26");
            shell->name_edit = edit; /* weak; owned by the tree */
        }
    }

    cn = break_editor_doc_component_count(shell->doc);
    for (ci = 0u; ci < cn; ci++) {
        BreakEditorComponentInfo info;
        if (!break_editor_doc_component_info(shell->doc, ci, &info)) {
            continue;
        }
        if (break_editor_doc_has_component(shell->doc, shell->selected,
                                           info.component_id)) {
            /* header row: component name + remove button */
            my_widget_t *row = my_widget_create(NULL, "editor-comp-row");
            if (row == NULL) {
                continue;
            }
            (void)my_widget_set_layouter(
                row, my_layouter_linear_create(NULL, true, 4));
            shell_add_child(row, my_label_create(NULL, info.display_name),
                            "w:1f h:22");
            if (shell->field_ctx_count < EDITOR_FIELD_CTX_POOL) {
                EditorFieldCtx *fc =
                    &shell->field_ctxs[shell->field_ctx_count++];
                my_widget_t *btn = my_button_create(
                    NULL, break_editor_tr(BREAK_EDITOR_TR_REMOVE));
                fc->shell = shell;
                fc->component_id = info.component_id;
                fc->field_index = 1u; /* != 0 => remove */
                if (btn != NULL) {
                    char wname[48];
                    (void)snprintf(wname, sizeof(wname),
                                   "editor-component-remove-%u",
                                   (unsigned)info.component_id);
                    (void)my_widget_set_name(btn, wname);
                    (void)my_widget_on(btn, "click",
                                       on_component_button_click, fc);
                    shell_add_child(row, btn, "w:72 h:22");
                }
            }
            shell_add_child(insp, row, "w:100% h:26");
            /* field rows */
            {
                u32 fi;
                for (fi = 0u; fi < info.field_count; fi++) {
                    my_widget_t *frow;
                    my_widget_t *fedit;
                    f32 cur = 0.0f;
                    char val[64];
                    char wname[64];
                    EditorFieldCtx *fc;
                    if (shell->field_ctx_count >= EDITOR_FIELD_CTX_POOL) {
                        break;
                    }
                    frow = my_widget_create(NULL, "editor-field-row");
                    if (frow == NULL) {
                        break;
                    }
                    (void)my_widget_set_layouter(
                        frow, my_layouter_linear_create(NULL, true, 4));
                    shell_add_child(
                        frow,
                        my_label_create(NULL, info.fields[fi].name),
                        "w:76 h:22");
                    (void)break_editor_doc_get_field_f32(
                        shell->doc, shell->selected, info.component_id, fi,
                        &cur);
                    (void)snprintf(val, sizeof(val), "%.6g", (double)cur);
                    fedit = my_edit_create(NULL);
                    if (fedit == NULL) {
                        shell_add_child(insp, frow, "w:100% h:26");
                        continue;
                    }
                    (void)snprintf(wname, sizeof(wname), "editor-field-%u-%u",
                                   (unsigned)info.component_id, (unsigned)fi);
                    (void)my_widget_set_name(fedit, wname);
                    (void)my_edit_set_max_len(fedit, 63u);
                    (void)my_edit_set_text(fedit, val);
                    fc = &shell->field_ctxs[shell->field_ctx_count++];
                    fc->shell = shell;
                    fc->component_id = info.component_id;
                    fc->field_index = fi;
                    (void)my_widget_on(fedit, "activate",
                                       on_field_edit_activate, fc);
                    shell_add_child(frow, fedit, "w:1f h:24");
                    shell_add_child(insp, frow, "w:100% h:26");
                }
            }
        } else {
            /* absent component: name + add button */
            my_widget_t *row = my_widget_create(NULL, "editor-comp-row");
            if (row == NULL) {
                continue;
            }
            (void)my_widget_set_layouter(
                row, my_layouter_linear_create(NULL, true, 4));
            shell_add_child(row, my_label_create(NULL, info.display_name),
                            "w:1f h:22");
            if (shell->field_ctx_count < EDITOR_FIELD_CTX_POOL) {
                EditorFieldCtx *fc =
                    &shell->field_ctxs[shell->field_ctx_count++];
                my_widget_t *btn = my_button_create(
                    NULL, break_editor_tr(BREAK_EDITOR_TR_ADD));
                fc->shell = shell;
                fc->component_id = info.component_id;
                fc->field_index = 0u; /* 0 => add */
                if (btn != NULL) {
                    char wname[48];
                    (void)snprintf(wname, sizeof(wname),
                                   "editor-component-add-%u",
                                   (unsigned)info.component_id);
                    (void)my_widget_set_name(btn, wname);
                    (void)my_widget_on(btn, "click",
                                       on_component_button_click, fc);
                    shell_add_child(row, btn, "w:72 h:22");
                }
            }
            shell_add_child(insp, row, "w:100% h:26");
        }
    }
}

/* ---------------- outliner list adapter ---------------- */

static EditorRowCtx *shell_row_ctx_alloc(BreakEditorShell *shell,
                                         my_widget_t *row, u8 kind) {
    u32 i;
    for (i = 0u; i < EDITOR_ROW_CTX_POOL; i++) {
        if (shell->row_ctxs[i].row == NULL) {
            EditorRowCtx *rc = &shell->row_ctxs[i];
            rc->shell = shell;
            rc->row = row;
            rc->index = 0u;
            rc->kind = kind;
            (void)my_widget_set_user_data(row, rc);
            return rc;
        }
    }
    return NULL; /* bounded: rows still render, click is degraded */
}

/* Ctrl+click: toggle the row's entity in the selection. Adding makes it
 * the primary (the previous primary joins the extras); removing the primary
 * promotes the most recently added extra. */
static bool shell_toggle_select_index(BreakEditorShell *shell, usize index) {
    BreakEditorEntityId id;
    const char *unused = NULL;
    int at;
    if (!break_editor_doc_entity_at(shell->doc, index, &id, &unused)) {
        return false;
    }
    at = shell_extra_index(shell, id);
    if (break_editor_entity_id_eq(id, shell->selected)) {
        shell->selected = BREAK_EDITOR_ENTITY_NULL;
        if (shell->extra_count > 0u) {
            shell->selected = shell->extra[--shell->extra_count];
        }
    } else if (at >= 0) {
        shell->extra[at] = shell->extra[--shell->extra_count];
    } else {
        if (break_editor_entity_id_valid(shell->selected)) {
            if (shell->extra_count >= EDITOR_EXTRA_SELECTION_MAX) return false;
            shell->extra[shell->extra_count++] = shell->selected;
        }
        shell->selected = id;
    }
    shell_outliner_mark_selection(shell);
    break_editor_viewport3d_set_extra_selection(shell->vp3d, shell->extra,
                                                shell->extra_count);
    shell_rebuild_inspector(shell);
    shell_refresh_status(shell);
    return true;
}

/* Shift+click: rows anchor..to (either order) become the selection, `to`
 * the primary; with `add` (Shift+Ctrl) the range joins the current one. */
static bool shell_select_range(BreakEditorShell *shell, usize anchor, usize to,
                               bool add) {
    usize lo = anchor < to ? anchor : to, hi = anchor < to ? to : anchor;
    usize n = break_editor_doc_entity_count(shell->doc);
    BreakEditorEntityId primary;
    const char *unused = NULL;
    if (hi >= n) hi = n == 0u ? 0u : n - 1u;
    if (n == 0u || !break_editor_doc_entity_at(shell->doc, to, &primary, &unused)) {
        return false;
    }
    if (!add) {
        shell->extra_count = 0u;
    } else if (break_editor_entity_id_valid(shell->selected) &&
               !break_editor_entity_id_eq(shell->selected, primary) &&
               shell_extra_index(shell, shell->selected) < 0 &&
               shell->extra_count < EDITOR_EXTRA_SELECTION_MAX) {
        shell->extra[shell->extra_count++] = shell->selected;
    }
    for (usize i = lo; i <= hi; i++) {
        BreakEditorEntityId id;
        if (!break_editor_doc_entity_at(shell->doc, i, &id, &unused) ||
            break_editor_entity_id_eq(id, primary) ||
            shell_extra_index(shell, id) >= 0) {
            continue;
        }
        if (shell->extra_count >= EDITOR_EXTRA_SELECTION_MAX) break;
        shell->extra[shell->extra_count++] = id;
    }
    {
        int at = shell_extra_index(shell, primary);
        if (at >= 0) shell->extra[at] = shell->extra[--shell->extra_count];
    }
    shell->selected = primary;
    shell_outliner_mark_selection(shell);
    break_editor_viewport3d_set_extra_selection(shell->vp3d, shell->extra,
                                                shell->extra_count);
    shell_rebuild_inspector(shell);
    shell_refresh_status(shell);
    return true;
}

static void on_row_click(void *ctx, const char *event, void *data) {
    EditorRowCtx *rc = (EditorRowCtx *)ctx;
    (void)event;
    if (rc == NULL || rc->shell == NULL) {
        return;
    }
    if (rc->kind == 0u) {
        const my_event_t *pe = (const my_event_t *)data;
        bool ptr = pe != NULL && (pe->type == MY_EVENT_POINTER_UP ||
                                  pe->type == MY_EVENT_POINTER_DOWN);
        bool ctrl = ptr && (pe->u.pointer.modifiers & MY_KEYMOD_CTRL) != 0u;
        bool shift = ptr && (pe->u.pointer.modifiers & MY_KEYMOD_SHIFT) != 0u;
        if (shift) {
            (void)shell_select_range(rc->shell, rc->shell->anchor_index,
                                     rc->index, ctrl);
        } else if (ctrl) {
            rc->shell->anchor_index = rc->index;
            (void)shell_toggle_select_index(rc->shell, rc->index);
        } else {
            rc->shell->anchor_index = rc->index;
            rc->shell->extra_count = 0u;
            break_editor_viewport3d_set_extra_selection(rc->shell->vp3d, NULL, 0u);
            (void)break_editor_shell_select_index(rc->shell, rc->index);
        }
    } else {
        BreakEditorShell *shell = rc->shell;
        if (rc->index < shell->palette_match_count) {
            u32 cmd = shell->palette_matches[rc->index];
            char text[96];
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_PALETTE_FMT),
                             shell_palette_text(cmd, text, sizeof(text)));
            shell_execute_palette_command(shell, cmd);
        }
        shell_palette_set_open(shell, false);
        editor_shell_refresh_all(shell);
    }
}

/* Outliner row selection class ("selected" → theme selection tint). Only
 * writes on change: set_style_class invalidates the row. */
static int shell_extra_index(const BreakEditorShell *shell,
                             BreakEditorEntityId id) {
    for (u32 i = 0u; i < shell->extra_count; i++) {
        if (break_editor_entity_id_eq(shell->extra[i], id)) return (int)i;
    }
    return -1;
}

static bool shell_is_selected(const BreakEditorShell *shell,
                              BreakEditorEntityId id) {
    return break_editor_entity_id_valid(id) &&
           (break_editor_entity_id_eq(id, shell->selected) ||
            shell_extra_index(shell, id) >= 0);
}

static void shell_row_mark_selected(BreakEditorShell *shell, my_widget_t *row,
                                    usize index) {
    BreakEditorEntityId id;
    const char *unused = NULL;
    const char *cls = my_widget_get_style_class(row);
    bool want = break_editor_doc_entity_at(shell->doc, index, &id, &unused) &&
                shell_is_selected(shell, id);
    bool have = cls != NULL && strcmp(cls, "selected") == 0;
    if (want != have) {
        (void)my_widget_set_style_class(row, want ? "selected" : NULL);
    }
}

/* Re-mark the live outliner rows after a selection change that does not
 * rebind them (row click, viewport pick). */
static void shell_outliner_mark_selection(BreakEditorShell *shell) {
    usize i, n;
    if (shell->outliner_list == NULL) {
        return;
    }
    n = my_widget_child_count(shell->outliner_list);
    for (i = 0u; i < n; i++) {
        my_widget_t *row = my_widget_get_child(shell->outliner_list, i);
        EditorRowCtx *rc;
        if (row == NULL) {
            continue;
        }
        rc = (EditorRowCtx *)my_widget_get_user_data(row);
        if (rc >= &shell->row_ctxs[0] &&
            rc < &shell->row_ctxs[EDITOR_ROW_CTX_POOL] && rc->row == row &&
            rc->kind == 0u) {
            shell_row_mark_selected(shell, row, rc->index);
        }
    }
}

static size_t editor_adapter_count(my_list_adapter_t *adapter) {
    EditorListAdapter *a =
        (EditorListAdapter *)((char *)adapter -
                              offsetof(EditorListAdapter, base));
    if (a->kind == 0u) {
        return (size_t)break_editor_doc_entity_count(a->shell->doc);
    }
    return (size_t)a->shell->palette_match_count;
}

static my_widget_t *editor_adapter_create_row(my_list_adapter_t *adapter) {
    EditorListAdapter *a =
        (EditorListAdapter *)((char *)adapter -
                              offsetof(EditorListAdapter, base));
    my_widget_t *row = my_button_create(NULL, "");
    if (row == NULL) {
        return NULL;
    }
    (void)my_widget_set_name(row, a->kind == 0u ? "editor-outliner-row"
                                                : "editor-palette-row");
    {
        EditorRowCtx *rc = shell_row_ctx_alloc(a->shell, row, a->kind);
        if (rc != NULL) {
            (void)my_widget_on(row, "click", on_row_click, rc);
        }
    }
    return row;
}

static void editor_adapter_bind_row(my_list_adapter_t *adapter,
                                    my_widget_t *row, size_t index) {
    EditorListAdapter *a =
        (EditorListAdapter *)((char *)adapter -
                              offsetof(EditorListAdapter, base));
    EditorRowCtx *rc = (EditorRowCtx *)my_widget_get_user_data(row);
    if (rc != NULL) {
        rc->index = (usize)index;
    }
    if (a->kind == 0u) {
        BreakEditorEntityId id;
        const char *name = NULL;
        /* entity_at rejects NULL out_id/out_name (editor_doc.c:157) — both
         * out-params must be real, otherwise every row binds "<stale>" */
        if (break_editor_doc_entity_at(a->shell->doc, (usize)index, &id,
                                       &name) &&
            name != NULL) {
            (void)my_button_set_text(row, name);
        } else {
            (void)my_button_set_text(row,
                                     break_editor_tr(BREAK_EDITOR_TR_STALE_ROW));
        }
        shell_row_mark_selected(a->shell, row, (usize)index);
    } else {
        if (index < a->shell->palette_match_count) {
            char text[96];
            bool hl = (u32)index == a->shell->palette_cursor;
            const char *cls = my_widget_get_style_class(row);
            (void)my_button_set_text(
                row, shell_palette_text(a->shell->palette_matches[index], text,
                                        sizeof(text)));
            if (hl != (cls != NULL && strcmp(cls, "selected") == 0)) {
                (void)my_widget_set_style_class(row, hl ? "selected" : NULL);
            }
        } else {
            (void)my_button_set_text(row,
                                     break_editor_tr(BREAK_EDITOR_TR_STALE_ROW));
        }
    }
}

static const my_list_adapter_vtable_t k_editor_adapter_vtable = {
    editor_adapter_count, editor_adapter_create_row, editor_adapter_bind_row,
    NULL};

static my_ret_t palette_on_event(my_widget_t *widget, const my_event_t *event) {
    (void)widget;
    /* Swallow only pointer events on the palette's own padding (they must not
     * fall through to the viewport). Key events keep bubbling to the shell
     * root: Escape/Ctrl+P close the palette from there. */
    if (event != NULL && event->type >= MY_EVENT_POINTER_DOWN &&
        event->type <= MY_EVENT_POINTER_WHEEL) {
        return MY_RET_OK;
    }
    return MY_RET_NOT_SUPPORTED;
}

/* ---------------- command palette ---------------- */

static bool editor_str_contains_casefold(const char *haystack,
                                         const char *needle) {
    size_t hlen, nlen, i;
    if (haystack == NULL || needle == NULL) {
        return false;
    }
    hlen = strlen(haystack);
    nlen = strlen(needle);
    if (nlen == 0u) {
        return true;
    }
    if (nlen > hlen) {
        return false;
    }
    for (i = 0u; i + nlen <= hlen; i++) {
        size_t j;
        bool eq = true;
        for (j = 0u; j < nlen; j++) {
            char a = haystack[i + j];
            char b = needle[j];
            if (a >= 'A' && a <= 'Z') {
                a = (char)(a - 'A' + 'a');
            }
            if (b >= 'A' && b <= 'Z') {
                b = (char)(b - 'A' + 'a');
            }
            if (a != b) {
                eq = false;
                break;
            }
        }
        if (eq) {
            return true;
        }
    }
    return false;
}

bool break_editor_shell_palette_set_filter(BreakEditorShell *shell,
                                           const char *text) {
    u32 i;
    if (shell == NULL || text == NULL) {
        return false;
    }
    shell->palette_match_count = 0u;
    shell->palette_cursor = 0u;
    for (i = 0u; i < EDITOR_PALETTE_COMMAND_COUNT; i++) {
        char cmd_text[96];
        if (editor_str_contains_casefold(
                shell_palette_text(i, cmd_text, sizeof(cmd_text)), text)) {
            shell->palette_matches[shell->palette_match_count++] = i;
        }
    }
    if (shell->palette_list != NULL) {
        (void)my_list_view_refresh(shell->palette_list);
    }
    return true;
}

static void shell_palette_set_open(BreakEditorShell *shell, bool open) {
    if (shell == NULL || shell->palette == NULL) {
        return;
    }
    shell->palette_open = open;
    (void)my_widget_set_visible(shell->palette, open);
    if (open) {
        /* center the floating palette over the shell root */
        int32_t rw = shell->root != NULL ? shell->root->rect.w : 800;
        int32_t rh = shell->root != NULL ? shell->root->rect.h : 480;
        int32_t w = rw - 80 > 420 ? 420 : (rw - 80 > 120 ? rw - 80 : 120);
        int32_t h = rh - 120 > 300 ? 300 : (rh - 120 > 120 ? rh - 120 : 120);
        (void)my_widget_set_rect(shell->palette,
                                 &(my_rect_t){(rw - w) / 2, (rh - h) / 3, w,
                                              h});
        (void)my_edit_set_text(shell->palette_edit, "");
        (void)break_editor_shell_palette_set_filter(shell, "");
        if (shell->win != NULL) {
            my_event_dispatcher_set_focus(&shell->win->dispatcher,
                                          shell->palette_edit);
        }
    } else if (shell->win != NULL && shell->root != NULL) {
        /* return key focus to the shell root so shortcuts keep working */
        my_event_dispatcher_set_focus(&shell->win->dispatcher, shell->root);
    }
}

static void on_palette_edit_changed(void *ctx, const char *event,
                                    void *data) {
    BreakEditorShell *shell = (BreakEditorShell *)ctx;
    (void)event;
    if (shell != NULL && data != NULL) {
        (void)break_editor_shell_palette_set_filter(shell,
                                                    (const char *)data);
    }
}

static void shell_execute_palette_first(BreakEditorShell *shell);

static void on_palette_edit_activate(void *ctx, const char *event,
                                     void *data) {
    BreakEditorShell *shell = (BreakEditorShell *)ctx;
    (void)event;
    (void)data;
    if (shell != NULL) {
        shell_execute_palette_first(shell);
    }
}

/* ---------------- actions (all doc mutations via commands) ---------------- */

static void shell_do_add_entity(BreakEditorShell *shell) {
    shell_end_gizmo_drag(shell);
    BreakEditorEntityId id = break_editor_doc_add_entity(shell->doc, NULL);
    if (break_editor_entity_id_valid(id)) {
        const char *name = shell_entity_name(shell, id);
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_ADD_ENTITY_FMT), name != NULL ? name : "?");
        shell->selected = id;
    } else {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_ADD_ENTITY_FAILED));
    }
    editor_shell_refresh_all(shell);
}

/* Ctrl+D / palette: duplicate the selection (one undoable command) and
 * select the copy. */
static void shell_do_duplicate_selected(BreakEditorShell *shell) {
    BreakEditorEntityId id = BREAK_EDITOR_ENTITY_NULL;
    if (break_editor_entity_id_valid(shell->selected)) {
        shell_end_gizmo_drag(shell);
        id = break_editor_doc_duplicate_entity(shell->doc, shell->selected);
    }
    if (break_editor_entity_id_valid(id)) {
        const char *name = shell_entity_name(shell, id);
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_DUPLICATE_FMT),
                         name != NULL ? name : "?");
        shell->selected = id;
    } else {
        editor_shell_log(shell, "%s",
                         break_editor_tr(BREAK_EDITOR_TR_LOG_DUPLICATE_FAILED));
    }
    editor_shell_refresh_all(shell);
}

static void shell_do_remove_selected(BreakEditorShell *shell) {
    if (shell->extra_count > 0u) {
        BreakEditorEntityId ids[EDITOR_EXTRA_SELECTION_MAX + 1u];
        u32 n = 0u, removed;
        if (break_editor_entity_id_valid(shell->selected)) {
            ids[n++] = shell->selected;
        }
        for (u32 i = 0u; i < shell->extra_count; i++) ids[n++] = shell->extra[i];
        shell_end_gizmo_drag(shell);
        removed = break_editor_doc_remove_entities(shell->doc, ids, n);
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_REMOVE_MANY_FMT),
                         (unsigned)removed);
        shell->extra_count = 0u;
        editor_shell_refresh_all(shell);
        return;
    }
    if (!break_editor_entity_id_valid(shell->selected)) {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_REMOVE_NO_SELECTION));
        return;
    }
    {
        /* remove_entity clears the slot (editor_doc.c slot_clear zeroes
         * name[0]), invalidating the borrowed entity_at name — copy it
         * BEFORE the mutation. */
        char name[BREAK_EDITOR_NAME_CAPACITY];
        const char *borrowed = shell_entity_name(shell, shell->selected);
        if (borrowed != NULL) {
            (void)snprintf(name, sizeof(name), "%s", borrowed);
        } else {
            name[0] = '\0';
        }
        shell_end_gizmo_drag(shell);
        if (break_editor_doc_remove_entity(shell->doc, shell->selected)) {
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_REMOVE_ENTITY_FMT),
                      name[0] != '\0' ? name : "?");
        } else {
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_REMOVE_ENTITY_FAILED));
        }
    }
    editor_shell_refresh_all(shell);
}

static void shell_do_save(BreakEditorShell *shell) {
    if (!shell->scene_path_set) {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_SAVE_NO_PATH));
        (void)snprintf(shell->note, sizeof(shell->note), "save: no path");
        shell_refresh_status(shell);
        return;
    }
    if (break_editor_doc_save(shell->doc, shell->scene_path)) {
        break_editor_hot_reload_note_saved(shell->hot_reload);
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_SAVED_FMT), shell->scene_path);
        (void)snprintf(shell->note, sizeof(shell->note), "saved");
    } else {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_SAVE_FAILED_FMT), shell->scene_path);
        (void)snprintf(shell->note, sizeof(shell->note), "save failed");
    }
    shell_refresh_status(shell);
}

static void shell_do_undo(BreakEditorShell *shell) {
    /* Task 3 mid-drag policy: an external undo during an active gizmo drag
     * first ENDS+COMMITS the drag (one command), then the undo below reverts
     * exactly that committed drag. end_drag without an active drag is a
     * documented no-op. */
    if (shell->gizmo != NULL) {
        break_editor_gizmo_end_drag(shell->gizmo);
    }
    if (break_editor_undo(shell->doc)) {
        char last[128];
        last[0] = '\0';
        (void)break_editor_cmd_stack_describe_last(
            break_editor_doc_stack(shell->doc), last);
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_UNDO_OK_FMT),
                  last[0] != '\0' ? last : "-");
    } else {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_UNDO_NOTHING));
    }
    editor_shell_refresh_all(shell);
}

static void shell_do_redo(BreakEditorShell *shell) {
    /* Same mid-drag policy as undo (documented: external history ops close
     * the drag first). */
    if (shell->gizmo != NULL) {
        break_editor_gizmo_end_drag(shell->gizmo);
    }
    if (break_editor_redo(shell->doc)) {
        char last[128];
        last[0] = '\0';
        (void)break_editor_cmd_stack_describe_last(
            break_editor_doc_stack(shell->doc), last);
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_REDO_OK_FMT),
                  last[0] != '\0' ? last : "-");
    } else {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_REDO_NOTHING));
    }
    editor_shell_refresh_all(shell);
}

static void shell_do_tool(BreakEditorShell *shell, u32 tool) {
    shell->tool = tool & 3u;
    /* Phase 2 Task 3: the tool IS the gizmo mode (NONE/TRANSLATE/ROTATE/
     * SCALE share the 0..3 numbering). set_mode mid-drag implicitly
     * end+commits the in-progress drag (Task 2 contract). */
    if (shell->gizmo != NULL) {
        break_editor_gizmo_set_mode(shell->gizmo,
                                    (BreakEditorGizmoMode)shell->tool);
    }
    shell_refresh_tool_label(shell);
    editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_TOOL_FMT),
                     shell_tool_name(shell->tool));
    shell_refresh_status(shell);
}

static void shell_do_focus_selected(BreakEditorShell *shell) {
    /* Phase 2 Task 3: real camera focus on the selection's proxy AABB (view
     * state — deliberately NOT an undoable command). */
    if (break_editor_entity_id_valid(shell->selected)) {
        const char *name = shell_entity_name(shell, shell->selected);
        break_editor_camera_focus(&shell->camera, shell->doc,
                                  shell->selected);
        (void)snprintf(shell->note, sizeof(shell->note),
                       break_editor_tr(BREAK_EDITOR_TR_NOTE_FOCUS_FMT),
                       name != NULL ? name : "?");
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_FOCUS_FMT),
                  name != NULL ? name : "?", (double)shell->camera.target[0],
                  (double)shell->camera.target[1],
                  (double)shell->camera.target[2]);
        if (shell->viewport_widget != NULL) {
            my_widget_invalidate(shell->viewport_widget, NULL);
        }
    } else {
        (void)snprintf(shell->note, sizeof(shell->note), "%s",
                       break_editor_tr(BREAK_EDITOR_TR_LOG_FOCUS_NO_SELECTION));
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_FOCUS_NO_SELECTION));
    }
    shell_refresh_status(shell);
}

static void shell_execute_palette_command(BreakEditorShell *shell, u32 cmd) {
    if (shell == NULL || cmd >= EDITOR_PALETTE_COMMAND_COUNT) {
        return;
    }    switch (cmd) {
    case PAL_ADD_ENTITY:
        shell_do_add_entity(shell);
        break;
    case PAL_REMOVE_SELECTED:
        shell_do_remove_selected(shell);
        break;
    case PAL_RENAME_SELECTED:
        if (break_editor_entity_id_valid(shell->selected) &&
            shell->name_edit != NULL && shell->win != NULL) {
            my_event_dispatcher_set_focus(&shell->win->dispatcher,
                                          shell->name_edit);
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_RENAME_HINT));
        } else {
            editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_RENAME_NO_SELECTION));
        }
        break;
    case PAL_SAVE:
        shell_do_save(shell);
        break;
    case PAL_UNDO:
        shell_do_undo(shell);
        break;
    case PAL_REDO:
        shell_do_redo(shell);
        break;
    case PAL_TOOL_SELECT:
        shell_do_tool(shell, 0u);
        break;
    case PAL_TOOL_TRANSLATE:
        shell_do_tool(shell, 1u);
        break;
    case PAL_TOOL_ROTATE:
        shell_do_tool(shell, 2u);
        break;
    case PAL_TOOL_SCALE:
        shell_do_tool(shell, 3u);
        break;
    case PAL_LANG_EN:
        (void)break_editor_shell_set_language(shell, BREAK_EDITOR_LANG_EN_US);
        break;
    case PAL_LANG_ZH:
        (void)break_editor_shell_set_language(shell, BREAK_EDITOR_LANG_ZH_CN);
        break;
    case PAL_THEME_LIGHT:
        (void)break_editor_shell_set_theme(shell, true);
        break;
    case PAL_THEME_DARK:
        (void)break_editor_shell_set_theme(shell, false);
        break;
    case PAL_DUPLICATE_SELECTED:
        shell_do_duplicate_selected(shell);
        break;
    case PAL_TOGGLE_SNAP:
        shell_set_snap(shell, !shell->snap);
        break;
    default:
        break;
    }
}

/* Runs the highlighted match (the first one unless Up/Down moved it). */
static void shell_execute_palette_first(BreakEditorShell *shell) {
    if (shell->palette_match_count > 0u) {
        u32 cmd = shell->palette_matches[shell->palette_cursor <
                                                 shell->palette_match_count
                                             ? shell->palette_cursor
                                             : 0u];
        char text[96];
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_PALETTE_FMT),
                         shell_palette_text(cmd, text, sizeof(text)));
        shell_execute_palette_command(shell, cmd);
    }
    shell_palette_set_open(shell, false);
    editor_shell_refresh_all(shell);
}

/* ---------------- toolbar buttons ---------------- */

static void on_add_button_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    shell_do_add_entity((BreakEditorShell *)ctx);
}

static void on_remove_button_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    shell_do_remove_selected((BreakEditorShell *)ctx);
}

/* ---------------- shortcut table + dispatch ---------------- */

enum {
    ACT_TOOL_SELECT = 0,
    ACT_TOOL_TRANSLATE,
    ACT_TOOL_ROTATE,
    ACT_TOOL_SCALE,
    ACT_FOCUS_SELECTED,
    ACT_SAVE,
    ACT_UNDO,
    ACT_REDO,
    ACT_PALETTE_TOGGLE,
    ACT_DUPLICATE,
    ACT_DELETE,
    ACT_TOGGLE_SNAP
};

typedef struct {
    u32 key;       /* ASCII letter (folded) */
    u32 modifiers; /* MY_KEYMOD bitmask; SHIFT is ignored for letters */
    u32 action;
} EditorShortcut;

static const EditorShortcut k_editor_shortcuts[] = {
    {'q', MY_KEYMOD_NONE, ACT_TOOL_SELECT},
    {'w', MY_KEYMOD_NONE, ACT_TOOL_TRANSLATE},
    {'e', MY_KEYMOD_NONE, ACT_TOOL_ROTATE},
    {'r', MY_KEYMOD_NONE, ACT_TOOL_SCALE},
    {'f', MY_KEYMOD_NONE, ACT_FOCUS_SELECTED},
    {'s', MY_KEYMOD_CTRL, ACT_SAVE},
    {'z', MY_KEYMOD_CTRL, ACT_UNDO},
    {'y', MY_KEYMOD_CTRL, ACT_REDO},
    {'p', MY_KEYMOD_CTRL, ACT_PALETTE_TOGGLE},
    {'d', MY_KEYMOD_CTRL, ACT_DUPLICATE},
    {MY_KEY_DELETE, MY_KEYMOD_NONE, ACT_DELETE},
    {'g', MY_KEYMOD_CTRL, ACT_TOGGLE_SNAP},
};

bool break_editor_shell_dispatch_key(BreakEditorShell *shell, u32 key,
                                     u32 modifiers) {
    size_t i;
    u32 relevant;
    if (shell == NULL) {
        return false;
    }
    /* the open palette owns Escape / Return */
    if (shell->palette_open && modifiers == MY_KEYMOD_NONE) {
        if (key == MY_KEY_ESCAPE) {
            shell_palette_set_open(shell, false);
            return true;
        }
        if (key == MY_KEY_RETURN) {
            shell_execute_palette_first(shell);
            return true;
        }
        if (key == MY_KEY_UP || key == MY_KEY_DOWN) {
            u32 n = shell->palette_match_count;
            if (n > 0u) {
                shell->palette_cursor =
                    key == MY_KEY_DOWN
                        ? (shell->palette_cursor + 1u) % n
                        : (shell->palette_cursor + n - 1u) % n;
                if (shell->palette_list != NULL) {
                    (void)my_list_view_refresh(shell->palette_list);
                }
            }
            return true;
        }
    }
    /* ASCII letters fold to lowercase; the generic letter table ignores SHIFT */
    if (key >= 'A' && key <= 'Z') {
        key = key - 'A' + 'a';
    }
    if (key == 'r' &&
        modifiers == (MY_KEYMOD_CTRL | MY_KEYMOD_SHIFT)) {
        if (!break_editor_viewport3d_request_shader_reload(shell->vp3d)) {
            editor_shell_log(shell, "%s",
                             break_editor_tr(BREAK_EDITOR_TR_LOG_SR_UNAVAILABLE));
        }
        return true;
    }
    relevant = (key >= 'a' && key <= 'z')
                   ? modifiers & (MY_KEYMOD_CTRL | MY_KEYMOD_ALT)
                   : modifiers & (MY_KEYMOD_SHIFT | MY_KEYMOD_CTRL |
                                  MY_KEYMOD_ALT);
    for (i = 0u;
         i < sizeof(k_editor_shortcuts) / sizeof(k_editor_shortcuts[0]);
         i++) {
        const EditorShortcut *sc = &k_editor_shortcuts[i];
        if (sc->key != key || sc->modifiers != relevant) {
            continue;
        }
        switch (sc->action) {
        case ACT_TOOL_SELECT:
            shell_do_tool(shell, 0u);
            break;
        case ACT_TOOL_TRANSLATE:
            shell_do_tool(shell, 1u);
            break;
        case ACT_TOOL_ROTATE:
            shell_do_tool(shell, 2u);
            break;
        case ACT_TOOL_SCALE:
            shell_do_tool(shell, 3u);
            break;
        case ACT_FOCUS_SELECTED:
            shell_do_focus_selected(shell);
            break;
        case ACT_SAVE:
            shell_do_save(shell);
            break;
        case ACT_UNDO:
            shell_do_undo(shell);
            break;
        case ACT_REDO:
            shell_do_redo(shell);
            break;
        case ACT_PALETTE_TOGGLE:
            shell_palette_set_open(shell, !shell->palette_open);
            break;
        case ACT_DUPLICATE:
            shell_do_duplicate_selected(shell);
            break;
        case ACT_TOGGLE_SNAP:
            shell_set_snap(shell, !shell->snap);
            break;
        case ACT_DELETE:
            if (break_editor_entity_id_valid(shell->selected)) {
                shell_do_remove_selected(shell);
            }
            break;
        default:
            return false;
        }
        return true;
    }
    return false;
}

/* Real-window key route: the myui dispatcher bubbles unconsumed key events
 * from the focused widget up to the shell root (editor_panels.h header). */
static void shell_on_root_key_down(void *ctx, const char *event, void *data) {
    BreakEditorShell *shell = (BreakEditorShell *)ctx;
    const my_event_t *e = (const my_event_t *)data;
    (void)event;
    if (shell != NULL && e != NULL && e->type == MY_EVENT_KEY_DOWN) {
        (void)break_editor_shell_dispatch_key(shell, e->u.key.key,
                                              e->u.key.modifiers);
    }
}

/* ---------------- refresh fan-out ---------------- */

/* Non-static: the Phase 3 assets panel calls this after a .bscn load (the
 * world swap invalidates the selection and every panel's displayed state). */
static void shell_set_label(BreakEditorShell *shell, const char *name,
                            const char *text) {
    my_widget_t *w = my_widget_find_descendant(shell->root, name);
    if (w != NULL) {
        (void)my_label_set_text(w, text);
    }
}

static void shell_set_button(BreakEditorShell *shell, const char *name,
                             const char *text) {
    my_widget_t *w = my_widget_find_descendant(shell->root, name);
    if (w != NULL) {
        (void)my_button_set_text(w, text);
    }
}

/* Re-applies the current language to every text the shell and its panels
 * own. Console lines already written are history and stay as they were. */
static void shell_retranslate(BreakEditorShell *shell) {
    if (shell->root != NULL) {
        shell_set_button(shell, "editor-add-button",
                         break_editor_tr(BREAK_EDITOR_TR_ADD));
        shell_set_button(shell, "editor-remove-button",
                         break_editor_tr(BREAK_EDITOR_TR_REMOVE));
        shell_set_label(shell, "editor-outliner-label",
                        break_editor_tr(BREAK_EDITOR_TR_OUTLINER));
    }
    if (shell->palette_edit != NULL) {
        (void)my_edit_set_hint(shell->palette_edit,
                               break_editor_tr(BREAK_EDITOR_TR_COMMAND_HINT));
    }
    editor_panel_assets_retranslate(shell->assets_panel);
    editor_panel_lua_retranslate(shell->lua_panel);
    editor_panel_profiler_retranslate(shell->profiler_panel);
    editor_panel_network_retranslate(shell->network_panel);
    editor_panel_render_retranslate(shell->render_panel);
    shell_tabs_retranslate(shell);
    /* palette rows and filter follow the current language */
    if (shell->palette_open && shell->palette_edit != NULL) {
        (void)break_editor_shell_palette_set_filter(
            shell, my_edit_get_text(shell->palette_edit));
    } else if (shell->palette_list != NULL) {
        (void)my_list_view_refresh(shell->palette_list);
    }
    /* tool label, status bar and the inspector (rebuilt from scratch) */
    editor_shell_refresh_all(shell);
}

bool break_editor_shell_set_language(BreakEditorShell *shell,
                                     BreakEditorLang lang) {
    if (shell == NULL || !break_editor_i18n_set_lang(lang)) {
        return false;
    }
    shell_retranslate(shell);
    editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_LANGUAGE_FMT),
                     break_editor_i18n_lang_name(lang));
    shell_settings_save(shell);
    return true;
}

void editor_shell_refresh_all(BreakEditorShell *shell) {
    if (shell == NULL) {
        return;
    }
    (void)shell_sync_selection(shell);
    if (shell->outliner_list != NULL) {
        (void)my_list_view_refresh(shell->outliner_list);
    }
    shell_rebuild_inspector(shell);
    shell_refresh_status(shell);
    shell_refresh_tool_label(shell);
    /* A rebind recycles the outliner rows and the inspector is rebuilt:
     * when the focused widget was one of them, myui clears focus and every
     * later key (Delete, Ctrl+D, Ctrl+Z...) would go nowhere. Hand it back
     * to the shell root, where the shortcuts live. */
    if (shell->win != NULL && shell->root != NULL &&
        shell->win->dispatcher.focused == NULL) {
        my_event_dispatcher_set_focus(&shell->win->dispatcher, shell->root);
    }
}

/* ---------------- tool-window tabs ---------------- */

/* Pages are looked up by name: each panel module owns its section and the
 * tree holds the reference, so the shell keeps no widget pointers that a
 * failed build could leave dangling. */
static const char *const k_tab_pages[2][3] = {
    {"editor-console", "editor-lua-panel", NULL},
    {"editor-profiler-panel", "editor-network-panel", "editor-render-panel"}};
static const BreakEditorTr k_tab_labels[2][3] = {
    {BREAK_EDITOR_TR_TAB_CONSOLE, BREAK_EDITOR_TR_TAB_LUA, BREAK_EDITOR_TR_COUNT},
    {BREAK_EDITOR_TR_TAB_PROFILER, BREAK_EDITOR_TR_TAB_NETWORK,
     BREAK_EDITOR_TR_TAB_RENDER}};
static const u32 k_tab_count[2] = {2u, 3u};
static const char *const k_tab_strips[2] = {"editor-bottom-tabs",
                                            "editor-diag-tabs"};

static my_widget_t *shell_find(BreakEditorShell *shell, const char *name) {
    return shell->root != NULL ? my_widget_find_descendant(shell->root, name)
                               : NULL;
}

static void shell_tabs_apply(BreakEditorShell *shell, u32 area) {
    my_widget_t *strip = shell_find(shell, k_tab_strips[area]);
    u32 i;
    for (i = 0u; i < k_tab_count[area]; i++) {
        my_widget_t *page = shell_find(shell, k_tab_pages[area][i]);
        bool on = i == shell->active_tab[area];
        if (page != NULL) {
            (void)my_widget_set_visible(page, on);
        }
        if (strip != NULL && i < my_widget_child_count(strip)) {
            (void)my_widget_set_style_class(my_widget_get_child(strip, i),
                                            on ? "active" : NULL);
        }
    }
    if (strip != NULL && strip->parent != NULL) {
        my_widget_invalidate(strip->parent, NULL);
    }
}

static void shell_tabs_retranslate(BreakEditorShell *shell) {
    u32 area, i;
    for (area = 0u; area < 2u; area++) {
        my_widget_t *strip = shell_find(shell, k_tab_strips[area]);
        for (i = 0u; strip != NULL && i < k_tab_count[area] &&
                     i < my_widget_child_count(strip);
             i++) {
            (void)my_button_set_text(my_widget_get_child(strip, i),
                                     break_editor_tr(k_tab_labels[area][i]));
        }
    }
}

static void on_tab_click(void *ctx, const char *event, void *data) {
    struct EditorTabCtx *tc = (struct EditorTabCtx *)ctx;
    (void)event;
    (void)data;
    if (tc != NULL) {
        (void)break_editor_shell_select_tab(tc->shell, tc->area, tc->index);
    }
}

/* Adds the strip for `area` to `parent` (a vertical container). Call
 * BEFORE the pages are added (myui appends children), then
 * shell_tabs_finish once they are. Non-fatal: without a strip the pages
 * stay tiled under their own layout params. */
static void shell_tabs_build(BreakEditorShell *shell, my_widget_t *parent,
                             u32 area, u32 ctx_base) {
    my_widget_t *strip = my_widget_create(NULL, k_tab_strips[area]);
    u32 i;
    if (strip == NULL) {
        return;
    }
    (void)my_widget_set_layouter(strip, my_layouter_linear_create(NULL, true, 0));
    for (i = 0u; i < k_tab_count[area]; i++) {
        my_widget_t *tab =
            my_button_create(NULL, break_editor_tr(k_tab_labels[area][i]));
        struct EditorTabCtx *tc = &shell->tab_ctxs[ctx_base + i];
        if (tab == NULL) {
            continue;
        }
        (void)my_widget_set_name(tab, "editor-tab");
        tc->shell = shell;
        tc->area = area;
        tc->index = i;
        (void)my_widget_on(tab, "click", on_tab_click, tc);
        /* bottom strip is full width: fixed CLion-like tabs; the narrow
         * diagnostics strip splits its width evenly */
        shell_add_child(strip, tab, area == 0u ? "w:110 h:100%" : "w:1f h:100%");
    }
    shell_add_child(parent, strip, "w:100% h:26");
}

/* After the pages exist: each fills the area under the strip, only the
 * active one is shown. */
static void shell_tabs_finish(BreakEditorShell *shell, u32 area) {
    u32 i;
    if (shell_find(shell, k_tab_strips[area]) == NULL) {
        return; /* no strip: keep the tiled fallback */
    }
    for (i = 0u; i < k_tab_count[area]; i++) {
        my_widget_t *page = shell_find(shell, k_tab_pages[area][i]);
        if (page != NULL) {
            (void)my_widget_set_layout_params(page, "w:100% h:1f");
        }
    }
    shell->active_tab[area] = 0u;
    shell_tabs_apply(shell, area);
}

bool break_editor_shell_select_tab(BreakEditorShell *shell, u32 area,
                                   u32 index) {
    if (shell == NULL || area >= 2u || index >= k_tab_count[area]) {
        return false;
    }
    shell->active_tab[area] = index;
    shell_tabs_apply(shell, area);
    shell_settings_save(shell);
    return true;
}

u32 break_editor_shell_palette_cursor(const BreakEditorShell *shell) {
    return shell != NULL ? shell->palette_cursor : 0u;
}

u32 break_editor_shell_active_tab(const BreakEditorShell *shell, u32 area) {
    return shell != NULL && area < 2u ? shell->active_tab[area] : 0u;
}

/* Every shell-level doc mutation ends a live gizmo drag first, so the drag
 * commits as its own command BEFORE the mutation (editor_viewport.md §10
 * item 2) instead of interleaving with it. No-op without a drag. */
static void shell_end_gizmo_drag(BreakEditorShell *shell) {
    if (shell != NULL && shell->gizmo != NULL &&
        break_editor_gizmo_is_dragging(shell->gizmo)) {
        break_editor_gizmo_end_drag(shell->gizmo);
    }
}

/* Gizmo snapping: defaults close to common DCC/engine steps. */
#define EDITOR_SNAP_TRANSLATE 0.25f
#define EDITOR_SNAP_ROTATE_DEG 15.0f
#define EDITOR_SNAP_SCALE 0.1f

static void shell_set_snap(BreakEditorShell *shell, bool on) {
    if (shell == NULL) {
        return;
    }
    shell->snap = on;
    (void)break_editor_gizmo_set_snap(shell->gizmo,
                                      on ? EDITOR_SNAP_TRANSLATE : 0.0f,
                                      on ? EDITOR_SNAP_ROTATE_DEG : 0.0f,
                                      on ? EDITOR_SNAP_SCALE : 0.0f);
    shell_refresh_tool_label(shell);
    shell_settings_save(shell);
}

/* Best-effort: a failed write is logged, never fatal (UI state only). */
static void shell_settings_save(BreakEditorShell *shell) {
    BreakEditorSettings st;
    if (shell == NULL || shell->settings_path[0] == '\0') {
        return;
    }
    break_editor_settings_defaults(&st);
    st.light_theme = break_editor_theme_is_light();
    st.has_lang = true;
    st.lang = break_editor_i18n_lang();
    st.bottom_tab = shell->active_tab[0];
    st.diag_tab = shell->active_tab[1];
    st.snap = shell->snap;
    if (!break_editor_settings_save(&st, shell->settings_path)) {
        editor_shell_log(shell, "settings: could not write %s",
                         shell->settings_path);
    }
}

bool break_editor_shell_use_settings(BreakEditorShell *shell, const char *path,
                                     bool keep_current_lang) {
    BreakEditorSettings st;
    usize n;
    if (shell == NULL || path == NULL) {
        return false;
    }
    n = strlen(path);
    if (n == 0u || n >= sizeof(shell->settings_path)) {
        return false; /* never truncate a path we would write to */
    }
    break_editor_settings_defaults(&st);
    (void)break_editor_settings_load(&st, path);
    shell->settings_path[0] = '\0'; /* no saves while applying */
    if (st.light_theme != break_editor_theme_is_light()) {
        (void)break_editor_shell_set_theme(shell, st.light_theme);
    }
    if (st.has_lang && !keep_current_lang &&
        st.lang != break_editor_i18n_lang()) {
        (void)break_editor_shell_set_language(shell, st.lang);
    }
    (void)break_editor_shell_select_tab(shell, 0u, st.bottom_tab);
    (void)break_editor_shell_select_tab(shell, 1u, st.diag_tab);
    shell_set_snap(shell, st.snap);
    memcpy(shell->settings_path, path, n + 1u);
    return true;
}

/* ---------------- widget tree build ---------------- */

static bool shell_build_panels(BreakEditorShell *shell, my_widget_t *content) {
    my_widget_t *root;
    my_widget_t *toolbar;
    my_widget_t *middle;
    my_widget_t *outliner_panel;
    my_widget_t *right_panel;
    my_widget_t *bottom;
    my_widget_t *add_btn;
    my_widget_t *remove_btn;

    /* window content reflows the shell root on resize; the palette overlay
     * is a floating child, skipped by the layouters */
    if (my_widget_set_layouter(content,
                               my_layouter_linear_create(NULL, false, 0)) !=
        MY_RET_OK) {
        return false;
    }
    root = my_widget_create(NULL, "editor-root");
    if (root == NULL) {
        return false;
    }
    (void)my_widget_set_layout_params(root, "w:100% h:1f");
    if (my_widget_add_child(content, root) != MY_RET_OK) {
        my_widget_unref(root);
        return false;
    }
    my_widget_unref(root); /* tree holds the reference; shell keeps a weak */
    shell->root = root;
    root->focusable = true;
    (void)my_widget_set_layouter(root, my_layouter_linear_create(NULL, false, 2));

    /* toolbar */
    toolbar = my_widget_create(NULL, "editor-toolbar");
    if (toolbar == NULL) {
        return false;
    }
    (void)my_widget_set_layouter(toolbar,
                                 my_layouter_linear_create(NULL, true, 4));
    add_btn = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_ADD));
    if (add_btn == NULL) {
        my_widget_unref(toolbar);
        return false;
    }
    (void)my_widget_set_name(add_btn, "editor-add-button");
    (void)my_widget_on(add_btn, "click", on_add_button_click, shell);
    shell_add_child(toolbar, add_btn, "w:64 h:24");
    remove_btn = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_REMOVE));
    if (remove_btn == NULL) {
        my_widget_unref(toolbar);
        return false;
    }
    (void)my_widget_set_name(remove_btn, "editor-remove-button");
    (void)my_widget_on(remove_btn, "click", on_remove_button_click, shell);
    shell_add_child(toolbar, remove_btn, "w:72 h:24");
    shell->tool_label = my_label_create(NULL, "");
    if (shell->tool_label == NULL) {
        my_widget_unref(toolbar);
        return false;
    }
    (void)my_widget_set_name(shell->tool_label, "editor-tool-label");
    shell_add_child(toolbar, shell->tool_label, "w:140 h:24");
    shell_add_child(root, toolbar, "w:100% h:28");

    /* middle row: outliner column 25% | viewport 1f | right column 28%
     * (Phase 2; Phase 3 Task 3 nests assets under the outliner and the
     * profiler under the inspector) */
    middle = my_widget_create(NULL, "editor-middle");
    if (middle == NULL) {
        return false;
    }
    (void)my_widget_set_layouter(middle,
                                 my_layouter_linear_create(NULL, true, 2));

    outliner_panel = my_widget_create(NULL, "editor-outliner-panel");
    if (outliner_panel == NULL) {
        my_widget_unref(middle);
        return false;
    }
    (void)my_widget_set_layouter(
        outliner_panel, my_layouter_linear_create(NULL, false, 2));
    shell_add_child(outliner_panel,
                    shell_named(my_label_create(
                                    NULL, break_editor_tr(BREAK_EDITOR_TR_OUTLINER)),
                                "editor-outliner-label"),
                    "w:100% h:22");
    shell->outliner_list = my_list_view_create(NULL);
    if (shell->outliner_list == NULL) {
        my_widget_unref(middle);
        return false;
    }
    (void)my_widget_set_name(shell->outliner_list, "editor-outliner");
    shell->outliner_adapter.base.vtable = &k_editor_adapter_vtable;
    shell->outliner_adapter.shell = shell;
    shell->outliner_adapter.kind = 0u;
    if (my_list_view_set_adapter(shell->outliner_list,
                                 &shell->outliner_adapter.base) != MY_RET_OK) {
        my_widget_unref(middle);
        return false;
    }
    shell_add_child(outliner_panel, shell->outliner_list, "w:100% h:1f");
    /* Phase 3 Task 3: assets browser below the outliner (h:40% of the left
     * column, set by the panel build) */
    if (!editor_panel_assets_build(shell->assets_panel, outliner_panel)) {
        my_widget_unref(middle);
        return false;
    }
    shell_add_child(middle, outliner_panel, "w:25% h:100%");

    /* viewport panel (Phase 2 Task 3): custom on_paint blit + pointer
     * routing; the widget borrows the shell via user_data */
    shell->viewport_widget = break_editor_viewport3d_widget_create(shell);
    if (shell->viewport_widget == NULL) {
        my_widget_unref(middle);
        return false;
    }
    shell_add_child(middle, shell->viewport_widget, "w:1f h:100%");

    /* Phase 3 Task 3: the right column is a container — inspector (h:1f)
     * over the profiler view (h:30% of the column, set by the panel
     * build) */
    right_panel = my_widget_create(NULL, "editor-right-panel");
    if (right_panel == NULL) {
        my_widget_unref(middle);
        return false;
    }
    (void)my_widget_set_layouter(right_panel,
                                 my_layouter_linear_create(NULL, false, 2));
    shell->inspector = my_widget_create(NULL, "editor-inspector");
    if (shell->inspector == NULL) {
        my_widget_unref(right_panel);
        my_widget_unref(middle);
        return false;
    }
    (void)my_widget_set_layouter(
        shell->inspector, my_layouter_linear_create(NULL, false, 2));
    shell_add_child(right_panel, shell->inspector, "w:100% h:1f");
    /* Diagnostics tool window under the inspector (design
     * 2026-10-29-editor-tool-window-tabs): a tab strip over the profiler,
     * network and render debugger pages, one shown at a time. The profiler
     * build is fatal as before; network/render build failures are not (no
     * widgets for that page). */
    {
        my_widget_t *diag = my_widget_create(NULL, "editor-diag-row");
        if (diag != NULL) {
            (void)my_widget_set_layouter(
                diag, my_layouter_linear_create(NULL, false, 0));
            (void)my_widget_set_layout_params(diag, "w:100% h:45%");
            /* Attach the empty row BEFORE building either panel. If this
             * append fails, the row dies empty and both weak list pointers
             * stay NULL; building first would leave them dangling. */
#ifdef BREAK_EDITOR_SHELL_TESTING
            if (g_editor_fail_diag_attach) {
                g_editor_fail_diag_attach = false;
                my_widget_unref(diag);
                diag = NULL;
            }
#endif
            if (diag != NULL &&
                my_widget_add_child(right_panel, diag) == MY_RET_OK) {
                my_widget_unref(diag); /* tree holds its own reference */
                shell_tabs_build(shell, diag, 1u, 2u);
                if (!editor_panel_profiler_build(shell->profiler_panel, diag)) {
                    my_widget_unref(middle);
                    return false;
                }
                editor_panel_network_build(shell->network_panel, diag);
                editor_panel_render_build(shell->render_panel, diag);
                /* shell_tabs_finish(1) runs once `middle` is in the tree
                 * (pages are looked up from the shell root) */
            } else if (diag != NULL) {
                my_widget_unref(diag);
                diag = NULL;
            }
        }
        if (diag == NULL &&
            !editor_panel_profiler_build(shell->profiler_panel, right_panel)) {
            my_widget_unref(right_panel);
            my_widget_unref(middle);
            return false;
        }
    }
    shell_add_child(middle, right_panel, "w:28% h:100%");
    shell_add_child(root, middle, "w:100% h:1f");
    shell_tabs_finish(shell, 1u);

    /* Phase 3 Task 3: the bottom row is two columns — the console (existing
     * 64-entry log ring, read-only) left w:1f, the Lua console right w:40%
     * (set by the panel build) */
    bottom = my_widget_create(NULL, "editor-bottom");
    if (bottom == NULL) {
        return false;
    }
    /* Console / Lua tool window: tab strip over one page at a time */
    (void)my_widget_set_layouter(bottom,
                                 my_layouter_linear_create(NULL, false, 0));
    shell_tabs_build(shell, bottom, 0u, 0u);
    shell->console_area = my_text_area_create(NULL);
    if (shell->console_area == NULL) {
        my_widget_unref(bottom);
        return false;
    }
    (void)my_widget_set_name(shell->console_area, "editor-console");
    (void)my_text_area_set_readonly(shell->console_area, true);
    (void)my_text_area_set_hint(shell->console_area, "console");
    shell_add_child(bottom, shell->console_area, "w:1f h:100%");
    if (!editor_panel_lua_build(shell->lua_panel, bottom)) {
        my_widget_unref(bottom);
        return false;
    }
    shell_add_child(root, bottom, "w:100% h:160");
    shell_tabs_finish(shell, 0u);

    /* status bar */
    shell->status_label = my_label_create(NULL, "");
    if (shell->status_label == NULL) {
        return false;
    }
    (void)my_widget_set_name(shell->status_label, "editor-status");
    (void)my_label_set_align(shell->status_label, MY_TEXT_ALIGN_LEFT);
    shell_add_child(root, shell->status_label, "w:100% h:22");

    /* command palette overlay (floating, hidden until Ctrl+P) */
    shell->palette = my_widget_create(NULL, "editor-palette");
    if (shell->palette == NULL) {
        return false;
    }
    /* Interactive floater: myui's hit test skips floating children whose
     * vtable has no on_event (paint-only overlays). The palette is a plain
     * container, so without this slot its rows never received a click — the
     * pointer fell through to the widgets underneath. Consume events on the
     * container itself (padding), rows still get theirs first. */
    {
        static const my_widget_vtable_t k_palette_vtable = {
            NULL, palette_on_event, NULL, NULL};
        shell->palette->vtable = &k_palette_vtable;
    }
    shell->palette->floating = true;
    (void)my_widget_set_layouter(shell->palette,
                                 my_layouter_linear_create(NULL, false, 2));
    shell->palette_edit = my_edit_create(NULL);
    if (shell->palette_edit == NULL) {
        return false;
    }
    (void)my_widget_set_name(shell->palette_edit, "editor-palette-edit");
    (void)my_edit_set_hint(shell->palette_edit,
                           break_editor_tr(BREAK_EDITOR_TR_COMMAND_HINT));
    (void)my_edit_set_max_len(shell->palette_edit, 63u);
    (void)my_widget_on(shell->palette_edit, "changed",
                       on_palette_edit_changed, shell);
    (void)my_widget_on(shell->palette_edit, "activate",
                       on_palette_edit_activate, shell);
    shell_add_child(shell->palette, shell->palette_edit, "w:100% h:26");
    shell->palette_list = my_list_view_create(NULL);
    if (shell->palette_list == NULL) {
        return false;
    }
    (void)my_widget_set_name(shell->palette_list, "editor-palette-list");
    shell->palette_adapter.base.vtable = &k_editor_adapter_vtable;
    shell->palette_adapter.shell = shell;
    shell->palette_adapter.kind = 1u;
    if (my_list_view_set_adapter(shell->palette_list,
                                 &shell->palette_adapter.base) != MY_RET_OK) {
        return false;
    }
    shell_add_child(shell->palette, shell->palette_list, "w:100% h:1f");
    shell->palette->visible = false;
    shell_add_child(root, shell->palette, NULL);
    shell->palette->rect = my_rect_init(0, 0, 420, 300);

    /* shortcut route + initial focus */
    (void)my_widget_on(root, "key_down", shell_on_root_key_down, shell);
    shell_rebuild_inspector(shell);
    shell_refresh_tool_label(shell);
    shell_refresh_status(shell);
    return true;
}

static void shell_shader_reload_log(void *user, const char *line) {
    BreakEditorShell *shell = (BreakEditorShell *)user;
    if (shell != NULL && line != NULL) {
        editor_shell_log(shell, "%s", line);
    }
}

static BreakEditorShell *shell_create_common(my_window_t *win) {
    BreakEditorShell *shell;
    my_widget_t *content;
    if (win == NULL) {
        return NULL;
    }
    shell = (BreakEditorShell *)calloc(1u, sizeof(BreakEditorShell));
    if (shell == NULL) {
        return NULL;
    }
    shell->doc = break_editor_doc_create();
    if (shell->doc == NULL) {
        free(shell);
        return NULL;
    }
    /* Phase 2 Task 3 owned viewport state (pure CPU here — vp3d has no GPU
     * objects until a first render with a live device) */
    break_editor_camera_init(&shell->camera);
    shell->gizmo = break_editor_gizmo_create();
    shell->vp3d = break_editor_viewport3d_create();
    if (shell->gizmo == NULL || shell->vp3d == NULL) {
        break_editor_viewport3d_destroy(shell->vp3d);
        break_editor_gizmo_destroy(shell->gizmo);
        break_editor_doc_destroy(shell->doc);
        free(shell);
        return NULL;
    }
    break_editor_viewport3d_set_view_state(shell->vp3d, &shell->camera,
                                           shell->gizmo,
                                           BREAK_EDITOR_ENTITY_NULL);
    break_editor_viewport3d_set_shader_reload_logger(
        shell->vp3d, shell_shader_reload_log, shell);
    /* Phase 3 Task 3 panel CPU state (see editor_shell_internal.h): needs
     * the doc (the Lua console borrows it; the assets model lists ".").
     * Panel create fails only on allocation — a degraded assets model or
     * Lua console inside a panel is NOT fatal (the panel logs bounded
     * error lines instead). */
    shell->assets_panel = editor_panel_assets_create(shell);
    shell->lua_panel = editor_panel_lua_create(shell);
    shell->profiler_panel = editor_panel_profiler_create(shell);
    /* no remote at create (DEFAULT OFF): break_editor_shell_set_remote
     * forwards later attaches to the panel */
    shell->network_panel = editor_panel_network_create(shell, NULL);
    shell->render_panel = editor_panel_render_create(shell);
    if (shell->assets_panel == NULL || shell->lua_panel == NULL ||
        shell->profiler_panel == NULL || shell->network_panel == NULL ||
        shell->render_panel == NULL) {
        editor_panel_render_destroy(shell->render_panel);
        editor_panel_network_destroy(shell->network_panel);
        editor_panel_profiler_destroy(shell->profiler_panel);
        editor_panel_lua_destroy(shell->lua_panel);
        editor_panel_assets_destroy(shell->assets_panel);
        break_editor_viewport3d_destroy(shell->vp3d);
        break_editor_gizmo_destroy(shell->gizmo);
        break_editor_doc_destroy(shell->doc);
        free(shell);
        return NULL;
    }
    shell->win = win;
    shell->selected = BREAK_EDITOR_ENTITY_NULL;
    content = my_window_widget(win);
    if (!shell_build_panels(shell, content)) {
        /* drop any partially built tree so the (possibly borrowed) window
         * is left untouched */
        if (shell->root != NULL) {
            (void)my_widget_remove_child(content, shell->root);
        }
        editor_panel_render_destroy(shell->render_panel);
        editor_panel_network_destroy(shell->network_panel);
        editor_panel_profiler_destroy(shell->profiler_panel);
        editor_panel_lua_destroy(shell->lua_panel);
        editor_panel_assets_destroy(shell->assets_panel);
        break_editor_viewport3d_destroy(shell->vp3d);
        break_editor_gizmo_destroy(shell->gizmo);
        break_editor_doc_destroy(shell->doc);
        free(shell);
        return NULL;
    }
    /* JetBrains New UI dark look (editor_theme.c); a sheet that fails to
     * parse keeps the default theme and is logged, never fatal */
    if (!break_editor_theme_apply(win)) {
        editor_shell_log(shell, "theme: the editor style sheet did not apply");
    }
    /* shortcuts work before any widget is clicked */
    my_event_dispatcher_set_focus(&win->dispatcher, shell->root);
    editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_READY));
    return shell;
}

bool break_editor_shell_set_theme(BreakEditorShell *shell, bool light) {
    if (shell == NULL || shell->win == NULL) {
        return false;
    }
    if (!break_editor_theme_apply_mode(shell->win, light)) {
        editor_shell_log(shell, "theme: the editor style sheet did not apply");
        return false;
    }
    /* self-painting widgets (viewport surround, preview) read the mode */
    my_widget_invalidate((my_widget_t *)shell->win, NULL);
    shell_settings_save(shell);
    return true;
}

BreakEditorShell *break_editor_shell_create(struct my_window_t *win) {
    return shell_create_common(win);
}

#ifdef BREAK_EDITOR_SHELL_TESTING
BreakEditorShell *break_editor_shell_create_for_test(void) {
    my_pal_t *pal;
    my_pal_main_loop_t *loop;
    my_window_manager_t *wm;
    my_window_t *win;
    BreakEditorShell *shell;

    pal = my_pal_dummy_create(NULL);
    if (pal == NULL) {
        return NULL;
    }
    loop = my_pal_main_loop_create(pal);
    if (loop == NULL) {
        my_pal_destroy(pal);
        return NULL;
    }
    wm = my_window_manager_create(NULL, pal, loop);
    if (wm == NULL) {
        my_pal_main_loop_destroy(loop);
        my_pal_destroy(pal);
        return NULL;
    }
    win = my_window_create(NULL, pal, EDITOR_TEST_WINDOW_W,
                           EDITOR_TEST_WINDOW_H, "editor-test");
    if (win == NULL) {
        my_window_manager_destroy(wm);
        my_pal_main_loop_destroy(loop);
        my_pal_destroy(pal);
        return NULL;
    }
    if (my_window_manager_open(wm, win) != MY_RET_OK) {
        my_widget_unref((my_widget_t *)win);
        my_window_manager_destroy(wm);
        my_pal_main_loop_destroy(loop);
        my_pal_destroy(pal);
        return NULL;
    }
    shell = shell_create_common(win);
    if (shell == NULL) {
        (void)my_window_manager_close(wm, win);
        my_widget_unref((my_widget_t *)win);
        my_window_manager_destroy(wm);
        my_pal_main_loop_destroy(loop);
        my_pal_destroy(pal);
        return NULL;
    }
    shell->pal = pal;
    shell->loop = loop;
    shell->wm = wm;
    shell->owns_window = true;
    return shell;
}
#endif

bool break_editor_shell_destroy(BreakEditorShell *shell) {
    if (shell == NULL) {
        return true;
    }
    /* A timed-out shader worker retains pointers into the viewport. Stop it
     * before any other teardown; false leaves the complete shell intact. */
    if (shell->vp3d != NULL &&
        !break_editor_viewport3d_destroy(shell->vp3d)) {
        return false;
    }
    shell->vp3d = NULL;
    /* a still-attached remote (host destroyed the shell first) is orphaned
     * before anything is freed: it drops its back-pointer and its
     * doc-borrowing console, so its later destroy never reaches this shell */
    editor_remote_shell_destroyed(shell->remote, shell);
    shell->remote = NULL;
    /* same for an attached hot-reload object: it drops its shell pointer, so
     * its later tick/destroy never reaches freed memory */
    editor_hot_reload_shell_destroyed(shell->hot_reload, shell);
    shell->hot_reload = NULL;
    editor_panel_network_set_remote(shell->network_panel, NULL);
    if (shell->owns_window) {
        /* the window teardown destroys the whole panel tree */
        (void)my_window_manager_close(shell->wm, shell->win);
        my_widget_unref((my_widget_t *)shell->win);
        my_window_manager_destroy(shell->wm);
        my_pal_main_loop_destroy(shell->loop);
        my_pal_destroy(shell->pal);
    } else if (shell->win != NULL && shell->root != NULL) {
        /* borrowed window: detach the panel tree (drops its only ref) */
        (void)my_widget_remove_child(my_window_widget(shell->win),
                                     shell->root);
    }
    /* The gizmo borrows the doc: destroy it FIRST (a mid-drag destroy
     * end+commits against the still-live doc, Task 2 contract). The
     * viewport's GPU objects need the RHI device alive — on the real path
     * editor_main destroys the shell before rhi_device_destroy; on the
     * dummy-PAL path vp3d holds no GPU objects at all. The Phase 3 panels
     * free CPU-side state only (their widgets died with the tree above);
     * the Lua console borrows the doc, so panels go before the doc too. */
    editor_panel_render_destroy(shell->render_panel);
    editor_panel_network_destroy(shell->network_panel);
    editor_panel_profiler_destroy(shell->profiler_panel);
    editor_panel_lua_destroy(shell->lua_panel);
    editor_panel_assets_destroy(shell->assets_panel);
    break_editor_gizmo_destroy(shell->gizmo);
    break_editor_doc_destroy(shell->doc);
    free(shell);
    return true;
}

/* ---------------- public inspection surface ---------------- */

BreakEditorDoc *break_editor_shell_doc(BreakEditorShell *shell) {
    return shell != NULL ? shell->doc : NULL;
}

struct my_window_t *break_editor_shell_window(BreakEditorShell *shell) {
    return shell != NULL ? shell->win : NULL;
}

struct my_widget_t *break_editor_shell_root(BreakEditorShell *shell) {
    return shell != NULL ? shell->root : NULL;
}

usize break_editor_shell_outliner_count(const BreakEditorShell *shell) {
    return shell != NULL ? break_editor_doc_entity_count(shell->doc) : 0u;
}

const char *break_editor_shell_tool_text(const BreakEditorShell *shell) {
    static const char *const fallback = "";
    const my_label_t *label;
    if (shell == NULL || shell->tool_label == NULL) {
        return fallback;
    }
    label = (const my_label_t *)shell->tool_label;
    return label->text != NULL ? label->text : fallback;
}

const char *break_editor_shell_status_text(const BreakEditorShell *shell) {
    if (shell == NULL) {
        return "";
    }
    return shell->status_text;
}

const char *break_editor_shell_console_text(const BreakEditorShell *shell) {
    if (shell == NULL) {
        return "";
    }
    return shell->console_text;
}

const char *break_editor_shell_name_edit_text(const BreakEditorShell *shell) {
    if (shell == NULL || shell->name_edit == NULL) {
        return "";
    }
    return my_edit_get_text(shell->name_edit);
}

u32 break_editor_shell_selection_count(const BreakEditorShell *shell) {
    if (shell == NULL) return 0u;
    return (break_editor_entity_id_valid(shell->selected) ? 1u : 0u) +
           shell->extra_count;
}

BreakEditorEntityId break_editor_shell_selected(const BreakEditorShell *shell) {
    if (shell == NULL) {
        return BREAK_EDITOR_ENTITY_NULL;
    }
    return shell->selected;
}

bool break_editor_shell_select_index(BreakEditorShell *shell, usize i) {
    BreakEditorEntityId id;
    const char *unused = NULL;
    if (shell == NULL) {
        return false;
    }
    if (!break_editor_doc_entity_at(shell->doc, (usize)i, &id, &unused)) {
        return false;
    }
    shell->selected = id;
    shell_outliner_mark_selection(shell);
    shell_rebuild_inspector(shell);
    shell_refresh_status(shell);
    return true;
}

bool break_editor_shell_palette_is_open(const BreakEditorShell *shell) {
    return shell != NULL && shell->palette_open;
}

usize break_editor_shell_palette_count(const BreakEditorShell *shell) {
    return shell != NULL ? (usize)shell->palette_match_count : 0u;
}

bool break_editor_shell_set_scene_path(BreakEditorShell *shell,
                                       const char *path) {
    size_t len;
    if (shell == NULL || path == NULL) {
        return false;
    }
    len = strlen(path);
    if (len == 0u || len + 1u > sizeof(shell->scene_path)) {
        return false;
    }
    memcpy(shell->scene_path, path, len + 1u);
    shell->scene_path_set = true;
    /* a path the watcher cannot take is reported on the console by the
     * hot-reload object; the save target is still accepted */
    (void)break_editor_hot_reload_set_scene(shell->hot_reload,
                                            shell->scene_path);
    return true;
}

bool break_editor_shell_request_close(BreakEditorShell *shell) {
    u64 rev;
    if (shell == NULL || !break_editor_doc_is_dirty(shell->doc)) {
        return true;
    }
    rev = break_editor_cmd_stack_revision(break_editor_doc_stack(shell->doc)) + 1u;
    if (shell->close_warned_rev == rev) {
        return true; /* second request with no edit since the warning */
    }
    shell->close_warned_rev = rev;
    editor_shell_log(shell, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_CLOSE_UNSAVED));
    (void)snprintf(shell->note, sizeof(shell->note), "%s",
                   break_editor_tr(BREAK_EDITOR_TR_LOG_CLOSE_UNSAVED));
    shell_refresh_status(shell);
    return false;
}

bool break_editor_shell_open_scene(BreakEditorShell *shell, const char *path) {
    FILE *f;
    if (shell == NULL || path == NULL || path[0] == '\0') {
        return false;
    }
    f = fopen(path, "rb");
    if (f == NULL) {
        /* new scene: nothing to load yet, saving creates it */
        return break_editor_shell_set_scene_path(shell, path);
    }
    fclose(f);
    /* existing file: load it; on failure keep it out of the save target so
     * Ctrl+S cannot overwrite it with the (empty) current document */
    return editor_shell_load_scene(shell, path);
}

const char *break_editor_shell_scene_path(const BreakEditorShell *shell) {
    return shell != NULL && shell->scene_path_set ? shell->scene_path : "";
}

bool editor_shell_load_scene(BreakEditorShell *shell, const char *path) {
    size_t len;
    if (shell == NULL || path == NULL) {
        return false;
    }
    len = strlen(path);
    break_editor_gizmo_end_drag(shell->gizmo);
    if (!break_editor_doc_load(shell->doc, path)) {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_LOAD_FAILED_FMT), path);
        editor_shell_refresh_all(shell);
        return false;
    }
    editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_LOAD_FMT), path);
    if (len > 0u && len + 1u <= sizeof(shell->scene_path)) {
        memcpy(shell->scene_path, path, len + 1u);
        shell->scene_path_set = true;
        (void)break_editor_hot_reload_set_scene(shell->hot_reload,
                                                shell->scene_path);
    }
    /* world swap + undo-stack clear: refresh everything */
    editor_shell_refresh_all(shell);
    return true;
}

/* ---------------- Phase 2 Task 3: viewport panel ---------------- */

struct my_widget_t *break_editor_shell_viewport_widget(
    BreakEditorShell *shell) {
    return shell != NULL ? shell->viewport_widget : NULL;
}

struct BreakEditorViewport3D *break_editor_shell_viewport3d(
    BreakEditorShell *shell) {
    return shell != NULL ? shell->vp3d : NULL;
}

BreakEditorCamera *break_editor_shell_camera(BreakEditorShell *shell) {
    return shell != NULL ? &shell->camera : NULL;
}

BreakEditorGizmo *break_editor_shell_gizmo(BreakEditorShell *shell) {
    return shell != NULL ? shell->gizmo : NULL;
}

BreakEditorGizmoMode break_editor_shell_gizmo_mode(
    const BreakEditorShell *shell) {
    return shell != NULL ? (BreakEditorGizmoMode)(shell->tool & 3u)
                         : BREAK_EDITOR_GIZMO_NONE;
}

bool break_editor_shell_select_id(BreakEditorShell *shell,
                                  BreakEditorEntityId id) {
    if (shell == NULL) {
        return false;
    }
    /* an id that is stale/absent is cleared by the sync inside the refresh */
    shell->selected = id;
    editor_shell_refresh_all(shell);
    return true;
}

void break_editor_shell_refresh(BreakEditorShell *shell) {
    editor_shell_refresh_all(shell);
}

void break_editor_shell_tick(BreakEditorShell *shell) {
    if (shell == NULL) {
        return;
    }
    /* Live 3D view: the retained UI only repaints on damage, so the
     * viewport widget takes damage every frame while visible (documented
     * intended exception, plan Global Constraints). */
    if (shell->viewport_widget != NULL && shell->viewport_widget->visible) {
        my_widget_invalidate(shell->viewport_widget, NULL);
    }
    (void)shell_sync_selection(shell); /* keeps the gizmo attach current */
    /* Phase 3 Task 3: the profiler view snapshots profiler_last_frame at
     * <= 4 Hz (throttle documented in editor_panel_profiler.c); pure read,
     * never touches profiler state. */
    editor_panel_profiler_tick(shell->profiler_panel);
    /* asset browser: throttled re-list of the current directory so files
     * created/removed by external tools appear without navigating */
    editor_panel_assets_tick(shell->assets_panel);
    /* image preview: pump its reload owner and swap a finished texture
     * before frame_begin, like the shader owner */
    break_editor_image_preview_tick(
        editor_panel_assets_preview(shell->assets_panel));
    /* Phase 4 Task 3: the network view snapshots the attached remote at
     * <= 4 Hz (pure read — editor_panel_network.c); it runs BEFORE the
     * remote tick, so a refresh never observes a half-applied frame. */
    editor_panel_network_tick(shell->network_panel);
    /* render debugger: <= 4 Hz pure read of the borrowed device and the
     * viewport's last-render stats */
    editor_panel_render_tick(shell->render_panel, shell->vp3d);
    break_editor_viewport3d_tick(shell->vp3d);
    /* Phase 4 Task 1: the host-attached remote (DEFAULT OFF — the shell
     * never creates one; editor_main --remote / tests attach it via
     * break_editor_shell_set_remote) is driven exactly once per tick on the
     * shell thread: one poll_adapter cycle, so the protocol handlers satisfy
     * the doc/Lua/command owner-thread rule by construction. NULL = the
     * pre-remote behavior, byte-identical. */
    break_editor_remote_tick(shell->remote);
    /* editor asset hot reload (DEFAULT OFF): external scene edits are staged
     * by Runtime Core workers and committed here, on the shell thread. */
    break_editor_hot_reload_tick(shell->hot_reload);
}

void break_editor_shell_set_hot_reload(BreakEditorShell *shell,
                                       BreakEditorHotReload *hr) {
    if (shell == NULL) {
        return;
    }
    shell->hot_reload = hr;
    if (hr != NULL) {
        editor_hot_reload_attach(hr, shell);
        (void)break_editor_hot_reload_set_scene(
            hr, shell->scene_path_set ? shell->scene_path : NULL);
    }
}

BreakEditorHotReload *break_editor_shell_hot_reload(BreakEditorShell *shell) {
    return shell != NULL ? shell->hot_reload : NULL;
}

/* Phase 4 Task 1 host wiring (editor_remote.h): attaches/detaches the
 * remote the shell tick drives. The shell BORROWS the remote — the host
 * (tests / editor_main --remote) owns its lifetime and destroys it. */
void break_editor_shell_set_remote(BreakEditorShell *shell,
                                   BreakEditorRemote *remote) {
    if (shell == NULL) {
        return;
    }
    /* symmetric detach: break_editor_remote_destroy calls this with NULL to
     * release the shell's borrow; a NEW remote must be attached explicitly
     * (the shell never adopts one silently). */
    shell->remote = remote;
    /* Phase 4 Task 3: the network panel borrows the same remote (and drops
     * it on detach — remote destroy detaches through here) */
    editor_panel_network_set_remote(shell->network_panel, remote);
}

BreakEditorRemote *break_editor_shell_remote(BreakEditorShell *shell) {
    return shell != NULL ? shell->remote : NULL;
}

/* ---------------- Phase 3 Task 3: panel accessors ---------------- */

bool break_editor_shell_set_assets_root(BreakEditorShell *shell,
                                        const char *root_path) {
    if (shell == NULL) {
        return false;
    }
    return editor_panel_assets_set_root(shell->assets_panel, root_path);
}

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_shell_set_assets_clock_for_test(BreakEditorShell *shell,
                                                  u64 (*clock)(void *user),
                                                  void *user) {
    if (shell != NULL) {
        editor_panel_assets_set_clock(shell->assets_panel, clock, user);
    }
}
#endif

usize break_editor_shell_assets_row_count(const BreakEditorShell *shell) {
    return shell != NULL
               ? editor_panel_assets_row_count(shell->assets_panel)
               : 0u;
}

const char *break_editor_shell_assets_path_text(const BreakEditorShell *shell) {
    return shell != NULL
               ? editor_panel_assets_path_text(shell->assets_panel)
               : "";
}

usize break_editor_shell_lua_history_count(const BreakEditorShell *shell) {
    return shell != NULL
               ? editor_panel_lua_history_count(shell->lua_panel)
               : 0u;
}

usize break_editor_shell_profiler_row_count(const BreakEditorShell *shell) {
    return shell != NULL
               ? editor_panel_profiler_row_count(shell->profiler_panel)
               : 0u;
}

const char *break_editor_shell_profiler_row_text(const BreakEditorShell *shell,
                                                 usize i) {
    return shell != NULL
               ? editor_panel_profiler_row_text(shell->profiler_panel, i)
               : NULL;
}

/* ---------------- Phase 4 Task 3: network panel accessors ---------------- */

uint32_t break_editor_shell_network_row_count(const BreakEditorShell *shell) {
    return shell != NULL ? editor_panel_network_row_count(shell->network_panel)
                         : 0u;
}

const char *break_editor_shell_network_row_text(const BreakEditorShell *shell,
                                                uint32_t index) {
    return shell != NULL
               ? editor_panel_network_row_text(shell->network_panel, index)
               : NULL;
}

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_shell_set_network_clock_for_test(BreakEditorShell *shell,
                                                   u64 (*clock)(void *user),
                                                   void *user) {
    if (shell == NULL) {
        return;
    }
    editor_panel_network_set_clock(shell->network_panel, clock, user);
}
#endif

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_shell_network_tick_for_test(BreakEditorShell *shell) {
    if (shell == NULL) {
        return;
    }
    editor_panel_network_tick(shell->network_panel);
}
#endif

void break_editor_shell_render_viewport(BreakEditorShell *shell,
                                        void *rhi_device, void *rhi_cmd,
                                        int drawable_w, int drawable_h,
                                        int logical_w, int logical_h) {
    int panel_w, panel_h;
    if (shell == NULL || shell->vp3d == NULL) {
        return;
    }
    if (rhi_device == NULL || rhi_cmd == NULL) {
        /* Keep the render debugger honest even on the guarded no-device
         * path: record the skip instead of leaving a stale prior frame. */
        break_editor_viewport3d_render(shell->vp3d, shell->doc, rhi_device,
                                       rhi_cmd, 0, 0);
        return;
    }
    if (shell->viewport_widget == NULL || !shell->viewport_widget->visible) {
        return; /* hidden viewport: no GPU work */
    }
    /* panel pixel size = logical rect x input scale */
    {
        f32 sx = logical_w > 0 ? (f32)drawable_w / (f32)logical_w : 1.0f;
        f32 sy = logical_h > 0 ? (f32)drawable_h / (f32)logical_h : 1.0f;
        panel_w = (int)((f32)shell->viewport_widget->rect.w * sx + 0.5f);
        panel_h = (int)((f32)shell->viewport_widget->rect.h * sy + 0.5f);
    }
    break_editor_viewport3d_set_screen_size(shell->vp3d, drawable_w,
                                            drawable_h);
    break_editor_viewport3d_render(shell->vp3d, shell->doc, rhi_device,
                                   rhi_cmd, panel_w, panel_h);
}

/* ---------------- render debugger panel accessors ---------------- */

void break_editor_shell_set_render_device(BreakEditorShell *shell,
                                          RHIDevice *device) {
    if (shell != NULL) {
        editor_panel_render_set_device(shell->render_panel, device);
        editor_panel_assets_set_device(shell->assets_panel, device);
        if (device != NULL) {
            (void)break_editor_viewport3d_prepare(shell->vp3d, device);
        }
    }
}

bool break_editor_shell_image_preview_stats(const BreakEditorShell *shell,
                                            BreakEditorImagePreviewStats *out) {
    return shell != NULL &&
           break_editor_image_preview_stats(
               editor_panel_assets_preview(shell->assets_panel), out);
}

uint32_t break_editor_shell_render_row_count(const BreakEditorShell *shell) {
    return shell != NULL ? editor_panel_render_row_count(shell->render_panel)
                         : 0u;
}

const char *break_editor_shell_render_row_text(const BreakEditorShell *shell,
                                               uint32_t index) {
    return shell != NULL
               ? editor_panel_render_row_text(shell->render_panel, index)
               : NULL;
}

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_shell_set_render_source_for_test(
    BreakEditorShell *shell, const BreakEditorRenderSource *source) {
    if (shell != NULL) {
        editor_panel_render_set_source(shell->render_panel, source);
    }
}
#endif

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_shell_set_render_clock_for_test(BreakEditorShell *shell,
                                                  u64 (*clock)(void *user),
                                                  void *user) {
    if (shell != NULL) {
        editor_panel_render_set_clock(shell->render_panel, clock, user);
    }
}
#endif
