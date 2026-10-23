/* BreakEditorShell implementation — see editor_panels.h for the architecture,
 * the shortcut table contract, the layering rule (widget callbacks never call
 * world_* directly; every mutation routes through break_editor_doc_* /
 * break_editor_undo/redo), and the bounds documentation. */

#include "editor_panels.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editor/editor_cmd.h>
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
#define EDITOR_PALETTE_COMMAND_COUNT 10u
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
    u32 tool; /* 0 select, 1 translate, 2 rotate, 3 scale */
    bool palette_open;
    u32 palette_matches[EDITOR_PALETTE_COMMAND_COUNT];
    u32 palette_match_count;

    char console_ring[EDITOR_CONSOLE_CAPACITY][EDITOR_CONSOLE_LINE_BYTES];
    u32 console_head;  /* next write slot */
    u32 console_count; /* entries in use */
    /* joined console text: capacity lines x (line bytes + '\n') + NUL */
    char console_text[EDITOR_CONSOLE_CAPACITY *
                          (EDITOR_CONSOLE_LINE_BYTES + 1u) +
                      1u];

    char status_text[EDITOR_STATUS_BYTES];
    char note[EDITOR_CONSOLE_LINE_BYTES]; /* status-bar intent note */

    char scene_path[BREAK_EDITOR_SCENE_PATH_CAPACITY];
    bool scene_path_set;
};

/* ---------------- small helpers ---------------- */

static const char *const k_tool_names[4] = {"Select", "Translate", "Rotate",
                                            "Scale"};

/* Command palette entries; indices are the palette command id space. */
static const char *const k_palette_commands[EDITOR_PALETTE_COMMAND_COUNT] = {
    "Add Entity",      "Remove Selected", "Rename Selected",
    "Save Scene",      "Undo",            "Redo",
    "Tool: Select",    "Tool: Translate", "Tool: Rotate",
    "Tool: Scale"};

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
    PAL_TOOL_SCALE
};

static void shell_refresh_all(BreakEditorShell *shell);
static void shell_execute_palette_command(BreakEditorShell *shell, u32 cmd);
static void shell_palette_set_open(BreakEditorShell *shell, bool open);

/* Bounded console log: appends one <=127-byte line to the ring, dropping the
 * oldest entry when full, and republishes the joined text to the read-only
 * console widget. */
static void shell_log(BreakEditorShell *shell, const char *fmt, ...) {
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
                   "entities=%llu dirty=%d last=%.100s note=%.100s",
                   (unsigned long long)break_editor_doc_entity_count(
                       shell->doc),
                   break_editor_doc_is_dirty(shell->doc) ? 1 : 0, last,
                   shell->note);
    (void)my_label_set_text(shell->status_label, shell->status_text);
}

static void shell_refresh_tool_label(BreakEditorShell *shell) {
    char buf[64];
    if (shell == NULL || shell->tool_label == NULL) {
        return;
    }
    (void)snprintf(buf, sizeof(buf), "Tool: %s",
                   k_tool_names[shell->tool & 3u]);
    (void)my_label_set_text(shell->tool_label, buf);
}

/* Re-validate the shell selection against the doc; clears it when the entity
 * no longer exists (remove, undo, load). Returns true when still valid. */
static bool shell_sync_selection(BreakEditorShell *shell) {
    usize i, n;
    if (shell == NULL ||
        !break_editor_entity_id_valid(shell->selected)) {
        return false;
    }
    n = break_editor_doc_entity_count(shell->doc);
    for (i = 0u; i < n; i++) {
        BreakEditorEntityId id;
        const char *unused = NULL;
        if (break_editor_doc_entity_at(shell->doc, i, &id, &unused) &&
            break_editor_entity_id_eq(id, shell->selected)) {
            return true;
        }
    }
    shell->selected = BREAK_EDITOR_ENTITY_NULL;
    return false;
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

static void shell_add_child(my_widget_t *parent, my_widget_t *child,
                            const char *params) {
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
    if (break_editor_doc_rename_entity(shell->doc, shell->selected, text)) {
        shell_log(shell, "rename entity -> '%s'", text);
    } else {
        shell_log(shell, "rename failed (name cap %u bytes)",
                  BREAK_EDITOR_NAME_CAPACITY);
    }
    shell_refresh_all(shell);
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
        shell_log(fc->shell, "invalid f32: '%s'", text);
        shell_refresh_all(fc->shell);
        return;
    }
    if (break_editor_doc_set_field_f32(fc->shell->doc, fc->shell->selected,
                                       fc->component_id, fc->field_index,
                                       value)) {
        shell_log(fc->shell, "set %s field %u = %g",
                  fc->component_id == BREAK_EDITOR_COMPONENT_TRANSFORM
                      ? "transform"
                      : "component",
                  (unsigned)fc->field_index, (double)value);
    } else {
        shell_log(fc->shell, "set field failed");
    }
    shell_refresh_all(fc->shell);
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
        if (break_editor_doc_add_component(shell->doc, shell->selected,
                                           fc->component_id)) {
            shell_log(shell, "add component %u", (unsigned)fc->component_id);
        } else {
            shell_log(shell, "add component %u failed",
                      (unsigned)fc->component_id);
        }
    } else {
        if (break_editor_doc_remove_component(shell->doc, shell->selected,
                                              fc->component_id)) {
            shell_log(shell, "remove component %u",
                      (unsigned)fc->component_id);
        } else {
            shell_log(shell, "remove component %u failed",
                      (unsigned)fc->component_id);
        }
    }
    shell_refresh_all(shell);
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
        shell_add_child(insp, my_label_create(NULL, "No selection"),
                        "w:100% h:24");
        return;
    }

    /* name row */
    {
        const char *name = shell_entity_name(shell, shell->selected);
        my_widget_t *edit = my_edit_create(NULL);
        shell_add_child(insp, my_label_create(NULL, "Name"), "w:100% h:22");
        if (edit != NULL) {
            (void)my_widget_set_name(edit, "editor-name-edit");
            (void)my_edit_set_hint(edit, "entity name");
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
                my_widget_t *btn = my_button_create(NULL, "Remove");
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
                my_widget_t *btn = my_button_create(NULL, "Add");
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

static void on_row_click(void *ctx, const char *event, void *data) {
    EditorRowCtx *rc = (EditorRowCtx *)ctx;
    (void)event;
    (void)data;
    if (rc == NULL || rc->shell == NULL) {
        return;
    }
    if (rc->kind == 0u) {
        (void)break_editor_shell_select_index(rc->shell, rc->index);
    } else {
        BreakEditorShell *shell = rc->shell;
        if (rc->index < shell->palette_match_count) {
            u32 cmd = shell->palette_matches[rc->index];
            shell_log(shell, "palette: %s", k_palette_commands[cmd]);
            shell_execute_palette_command(shell, cmd);
        }
        shell_palette_set_open(shell, false);
        shell_refresh_all(shell);
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
        const char *name = NULL;
        if (break_editor_doc_entity_at(a->shell->doc, (usize)index, NULL,
                                       &name) &&
            name != NULL) {
            (void)my_button_set_text(row, name);
        } else {
            (void)my_button_set_text(row, "<stale>");
        }
    } else {
        if (index < a->shell->palette_match_count) {
            (void)my_button_set_text(
                row, k_palette_commands[a->shell->palette_matches[index]]);
        } else {
            (void)my_button_set_text(row, "<stale>");
        }
    }
}

static const my_list_adapter_vtable_t k_editor_adapter_vtable = {
    editor_adapter_count, editor_adapter_create_row, editor_adapter_bind_row,
    NULL};

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
    for (i = 0u; i < EDITOR_PALETTE_COMMAND_COUNT; i++) {
        if (editor_str_contains_casefold(k_palette_commands[i], text)) {
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
    BreakEditorEntityId id = break_editor_doc_add_entity(shell->doc, NULL);
    if (break_editor_entity_id_valid(id)) {
        const char *name = shell_entity_name(shell, id);
        shell_log(shell, "add entity '%s'", name != NULL ? name : "?");
        shell->selected = id;
    } else {
        shell_log(shell, "add entity failed (bounded)");
    }
    shell_refresh_all(shell);
}

static void shell_do_remove_selected(BreakEditorShell *shell) {
    if (!break_editor_entity_id_valid(shell->selected)) {
        shell_log(shell, "remove: no selection");
        return;
    }
    {
        const char *name = shell_entity_name(shell, shell->selected);
        if (break_editor_doc_remove_entity(shell->doc, shell->selected)) {
            shell_log(shell, "remove entity '%s'", name != NULL ? name : "?");
        } else {
            shell_log(shell, "remove entity failed");
        }
    }
    shell_refresh_all(shell);
}

static void shell_do_save(BreakEditorShell *shell) {
    if (!shell->scene_path_set) {
        shell_log(shell, "save: no scene path configured");
        (void)snprintf(shell->note, sizeof(shell->note), "save: no path");
        shell_refresh_status(shell);
        return;
    }
    if (break_editor_doc_save(shell->doc, shell->scene_path)) {
        shell_log(shell, "saved %s", shell->scene_path);
        (void)snprintf(shell->note, sizeof(shell->note), "saved");
    } else {
        shell_log(shell, "save failed %s", shell->scene_path);
        (void)snprintf(shell->note, sizeof(shell->note), "save failed");
    }
    shell_refresh_status(shell);
}

static void shell_do_undo(BreakEditorShell *shell) {
    if (break_editor_undo(shell->doc)) {
        char last[128];
        last[0] = '\0';
        (void)break_editor_cmd_stack_describe_last(
            break_editor_doc_stack(shell->doc), last);
        shell_log(shell, "undo ok (now last: %s)",
                  last[0] != '\0' ? last : "-");
    } else {
        shell_log(shell, "undo: nothing to undo");
    }
    shell_refresh_all(shell);
}

static void shell_do_redo(BreakEditorShell *shell) {
    if (break_editor_redo(shell->doc)) {
        char last[128];
        last[0] = '\0';
        (void)break_editor_cmd_stack_describe_last(
            break_editor_doc_stack(shell->doc), last);
        shell_log(shell, "redo ok (now last: %s)",
                  last[0] != '\0' ? last : "-");
    } else {
        shell_log(shell, "redo: nothing to redo");
    }
    shell_refresh_all(shell);
}

static void shell_do_tool(BreakEditorShell *shell, u32 tool) {
    shell->tool = tool & 3u;
    shell_refresh_tool_label(shell);
    shell_log(shell, "tool %s", k_tool_names[shell->tool]);
    shell_refresh_status(shell);
}

static void shell_do_focus_selected(BreakEditorShell *shell) {
    /* Phase 1 records the intent only; the camera focus is Phase 2. */
    if (break_editor_entity_id_valid(shell->selected)) {
        const char *name = shell_entity_name(shell, shell->selected);
        (void)snprintf(shell->note, sizeof(shell->note),
                       "focus '%s' (Phase 2 camera pending)",
                       name != NULL ? name : "?");
        shell_log(shell, "focus selected '%s' (intent recorded; camera is "
                         "Phase 2)",
                  name != NULL ? name : "?");
    } else {
        (void)snprintf(shell->note, sizeof(shell->note), "focus: no selection");
        shell_log(shell, "focus: no selection");
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
            shell_log(shell, "rename: edit the Name field, Enter commits");
        } else {
            shell_log(shell, "rename: no selection");
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
    default:
        break;
    }
}

static void shell_execute_palette_first(BreakEditorShell *shell) {
    if (shell->palette_match_count > 0u) {
        u32 cmd = shell->palette_matches[0u];
        shell_log(shell, "palette: %s", k_palette_commands[cmd]);
        shell_execute_palette_command(shell, cmd);
    }
    shell_palette_set_open(shell, false);
    shell_refresh_all(shell);
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
    ACT_PALETTE_TOGGLE
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
    }
    /* ASCII letters fold to lowercase; SHIFT is ignored for them */
    if (key >= 'A' && key <= 'Z') {
        key = key - 'A' + 'a';
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

static void shell_refresh_all(BreakEditorShell *shell) {
    if (shell == NULL) {
        return;
    }
    (void)shell_sync_selection(shell);
    if (shell->outliner_list != NULL) {
        (void)my_list_view_refresh(shell->outliner_list);
    }
    shell_rebuild_inspector(shell);
    shell_refresh_status(shell);
}

/* ---------------- widget tree build ---------------- */

static bool shell_build_panels(BreakEditorShell *shell, my_widget_t *content) {
    my_widget_t *root;
    my_widget_t *toolbar;
    my_widget_t *middle;
    my_widget_t *outliner_panel;
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
    add_btn = my_button_create(NULL, "Add");
    if (add_btn == NULL) {
        my_widget_unref(toolbar);
        return false;
    }
    (void)my_widget_set_name(add_btn, "editor-add-button");
    (void)my_widget_on(add_btn, "click", on_add_button_click, shell);
    shell_add_child(toolbar, add_btn, "w:64 h:24");
    remove_btn = my_button_create(NULL, "Remove");
    if (remove_btn == NULL) {
        my_widget_unref(toolbar);
        return false;
    }
    (void)my_widget_set_name(remove_btn, "editor-remove-button");
    (void)my_widget_on(remove_btn, "click", on_remove_button_click, shell);
    shell_add_child(toolbar, remove_btn, "w:72 h:24");
    shell->tool_label = my_label_create(NULL, "Tool: Select");
    if (shell->tool_label == NULL) {
        my_widget_unref(toolbar);
        return false;
    }
    (void)my_widget_set_name(shell->tool_label, "editor-tool-label");
    shell_add_child(toolbar, shell->tool_label, "w:140 h:24");
    shell_add_child(root, toolbar, "w:100% h:28");

    /* middle row: outliner | inspector */
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
    shell_add_child(outliner_panel, my_label_create(NULL, "Outliner"),
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
    shell_add_child(middle, outliner_panel, "w:34% h:100%");

    shell->inspector = my_widget_create(NULL, "editor-inspector");
    if (shell->inspector == NULL) {
        my_widget_unref(middle);
        return false;
    }
    (void)my_widget_set_layouter(
        shell->inspector, my_layouter_linear_create(NULL, false, 2));
    shell_add_child(middle, shell->inspector, "w:1f h:100%");
    shell_add_child(root, middle, "w:100% h:1f");

    /* console (read-only log view fed by the 64-entry ring) */
    shell->console_area = my_text_area_create(NULL);
    if (shell->console_area == NULL) {
        return false;
    }
    (void)my_widget_set_name(shell->console_area, "editor-console");
    (void)my_text_area_set_readonly(shell->console_area, true);
    (void)my_text_area_set_hint(shell->console_area, "console");
    shell_add_child(root, shell->console_area, "w:100% h:96");

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
    shell->palette->floating = true;
    (void)my_widget_set_layouter(shell->palette,
                                 my_layouter_linear_create(NULL, false, 2));
    shell->palette_edit = my_edit_create(NULL);
    if (shell->palette_edit == NULL) {
        return false;
    }
    (void)my_widget_set_name(shell->palette_edit, "editor-palette-edit");
    (void)my_edit_set_hint(shell->palette_edit, "command");
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
    shell->win = win;
    shell->selected = BREAK_EDITOR_ENTITY_NULL;
    content = my_window_widget(win);
    if (!shell_build_panels(shell, content)) {
        /* drop any partially built tree so the (possibly borrowed) window
         * is left untouched */
        if (shell->root != NULL) {
            (void)my_widget_remove_child(content, shell->root);
        }
        break_editor_doc_destroy(shell->doc);
        free(shell);
        return NULL;
    }
    /* shortcuts work before any widget is clicked */
    my_event_dispatcher_set_focus(&win->dispatcher, shell->root);
    shell_log(shell, "editor shell ready");
    return shell;
}

BreakEditorShell *break_editor_shell_create(struct my_window_t *win) {
    return shell_create_common(win);
}

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

void break_editor_shell_destroy(BreakEditorShell *shell) {
    if (shell == NULL) {
        return;
    }
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
    break_editor_doc_destroy(shell->doc);
    free(shell);
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
    return true;
}
