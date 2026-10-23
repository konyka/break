/* EditorPanelLua — Stage 4 scene editor Phase 3 Task 3: the myui panel half
 * of the Lua console. The eval pipeline, sandbox, ECS batch drain, and undo
 * integration all live in the pure CPU core (Phase 3 Task 2, editor_lua.h);
 * this file wires a my_edit input to it.
 *
 * CONTRACT (documented in docs/design/editor_panels_phase3.md):
 *   - Enter ("activate" on the edit) evaluates the typed chunk through
 *     break_editor_lua_eval. The input is echoed to the SHARED console ring
 *     as "lua| > <input>" and every core output line lands there too with
 *     the "lua| " prefix (the core bounds each line to <=127 visible bytes).
 *     The edit field is cleared for the next line and the whole shell
 *     refreshes (a Lua spawn/set mutates the doc through undoable commands,
 *     so the outliner/inspector/status must republish).
 *   - History: my_edit has NO history recall (my_edit.h — its undo stack is
 *     user-edit history, not command history), so the panel owns a bounded
 *     32-entry ring. Up/Down recall (my_edit does not consume those keys —
 *     edit_on_key returns MY_RET_FAIL for them, so the dispatcher's
 *     "key_down" emitter path fires on the focused edit). Up walks
 *     newest->oldest, Down walks back; the in-progress line is stashed on
 *     the first Up and restored when Down walks past the newest entry.
 *     Consecutive duplicates are not re-pushed.
 *   - Bounds: the edit is capped at 255 codepoints, so an edit-sourced line
 *     is at most 255*4 = 1020 bytes and ALWAYS fits a 1024-byte history
 *     entry (no truncation of recalled text; the core accepts up to 4096
 *     bytes — the panel deliberately caps the widget lower, documented).
 *   - A NULL console (core create failure, e.g. OOM) degrades eval to a
 *     bounded "lua| error: console unavailable" line — the panel still
 *     builds and the rest of the shell is unaffected.
 *
 * Threading: single-owner-thread convention. The shell thread owns the core
 * (it created it); all evals happen on that thread inside the activate
 * handler. destroy is called by the shell BEFORE the doc is destroyed (the
 * console borrows the doc).
 *
 * Threading note for the log callback: the core invokes log_fn synchronously
 * from the calling thread of eval — here always the shell thread. */

#include "editor_shell_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editor/editor_lua.h>

#include "mypal/my_event.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_label.h"

#define EDITOR_LUA_HISTORY_CAPACITY 32u
#define EDITOR_LUA_HISTORY_BYTES 1024u /* holds any 255-codepoint edit line */
#define EDITOR_LUA_EDIT_MAX_CODEPOINTS 255u

struct EditorPanelLua {
    BreakEditorShell *shell;      /* borrowed */
    BreakEditorLuaConsole *console; /* owned (NULL = degraded) */
    my_widget_t *edit;            /* weak (owned by the window tree) */
    char history[EDITOR_LUA_HISTORY_CAPACITY][EDITOR_LUA_HISTORY_BYTES];
    u32 history_count;
    u32 history_cursor; /* == history_count when not browsing */
    char stash[EDITOR_LUA_HISTORY_BYTES]; /* in-progress line, first Up */
};

/* Core output -> shared console ring with the lua| prefix. */
static void lua_panel_log(void *ctx, const char *line) {
    BreakEditorShell *shell = (BreakEditorShell *)ctx;
    if (line != NULL) {
        editor_shell_log(shell, "lua| %s", line);
    }
}

static void lua_history_push(EditorPanelLua *panel, const char *text) {
    size_t len;
    if (text == NULL || text[0] == '\0') {
        return;
    }
    /* consecutive duplicates are not re-pushed */
    if (panel->history_count > 0u &&
        strcmp(panel->history[panel->history_count - 1u], text) == 0) {
        return;
    }
    if (panel->history_count == EDITOR_LUA_HISTORY_CAPACITY) {
        /* bounded: drop the oldest */
        memmove(panel->history[0], panel->history[1],
                (EDITOR_LUA_HISTORY_CAPACITY - 1u) *
                    EDITOR_LUA_HISTORY_BYTES);
        panel->history_count--;
    }
    len = strlen(text);
    if (len >= EDITOR_LUA_HISTORY_BYTES) {
        len = EDITOR_LUA_HISTORY_BYTES - 1u; /* unreachable from the edit */
    }
    memcpy(panel->history[panel->history_count], text, len);
    panel->history[panel->history_count][len] = '\0';
    panel->history_count++;
}

static void lua_history_reset_browse(EditorPanelLua *panel) {
    panel->history_cursor = panel->history_count;
    panel->stash[0] = '\0';
}

static void on_lua_edit_activate(void *ctx, const char *event, void *data) {
    EditorPanelLua *panel = (EditorPanelLua *)ctx;
    const char *text = (const char *)data;
    (void)event;
    if (panel == NULL || text == NULL || text[0] == '\0') {
        return; /* empty line: no eval, no history */
    }
    editor_shell_log(panel->shell, "lua| > %s", text);
    lua_history_push(panel, text);
    lua_history_reset_browse(panel);
    if (panel->console != NULL) {
        (void)break_editor_lua_eval(panel->console, text);
    } else {
        editor_shell_log(panel->shell, "lua| error: console unavailable");
    }
    if (panel->edit != NULL) {
        (void)my_edit_set_text(panel->edit, "");
    }
    /* a Lua spawn/set routed undoable commands into the doc — republish */
    editor_shell_refresh_all(panel->shell);
}

/* Up/Down history recall. Fires on the edit's "key_down" emitter — my_edit
 * consumes neither key (edit_on_key falls through to MY_RET_FAIL), so the
 * dispatcher emits here before bubbling to the shell root. */
static void on_lua_edit_key_down(void *ctx, const char *event, void *data) {
    EditorPanelLua *panel = (EditorPanelLua *)ctx;
    const my_event_t *e = (const my_event_t *)data;
    (void)event;
    if (panel == NULL || e == NULL || e->type != MY_EVENT_KEY_DOWN ||
        panel->edit == NULL || e->u.key.modifiers != 0u) {
        return;
    }
    if (e->u.key.key == MY_KEY_UP) {
        if (panel->history_count == 0u || panel->history_cursor == 0u) {
            return; /* clamped at the oldest */
        }
        if (panel->history_cursor == panel->history_count) {
            /* first Up: stash the in-progress line */
            const char *cur = my_edit_get_text(panel->edit);
            (void)snprintf(panel->stash, sizeof(panel->stash), "%s",
                           cur != NULL ? cur : "");
        }
        panel->history_cursor--;
        (void)my_edit_set_text(panel->edit,
                               panel->history[panel->history_cursor]);
    } else if (e->u.key.key == MY_KEY_DOWN) {
        if (panel->history_cursor == panel->history_count) {
            return; /* already at the live line */
        }
        panel->history_cursor++;
        if (panel->history_cursor == panel->history_count) {
            (void)my_edit_set_text(panel->edit, panel->stash);
        } else {
            (void)my_edit_set_text(panel->edit,
                                   panel->history[panel->history_cursor]);
        }
    }
}

EditorPanelLua *editor_panel_lua_create(BreakEditorShell *shell) {
    EditorPanelLua *panel;
    if (shell == NULL) {
        return NULL;
    }
    panel = (EditorPanelLua *)calloc(1u, sizeof(EditorPanelLua));
    if (panel == NULL) {
        return NULL;
    }
    panel->shell = shell;
    /* the core borrows the doc (shell-owned) and logs into the shared ring
     * via lua_panel_log; NULL = degraded (bounded error line per eval) */
    panel->console = break_editor_lua_create(break_editor_shell_doc(shell),
                                             lua_panel_log, shell);
    panel->history_cursor = 0u;
    return panel;
}

void editor_panel_lua_destroy(EditorPanelLua *panel) {
    if (panel == NULL) {
        return;
    }
    /* CPU-side state only — the edit widget belongs to the window tree. The
     * console borrows the doc: the shell destroys panels before the doc. */
    break_editor_lua_destroy(panel->console);
    free(panel);
}

bool editor_panel_lua_build(EditorPanelLua *panel, my_widget_t *parent) {
    my_widget_t *section;
    my_widget_t *label;
    if (panel == NULL || parent == NULL) {
        return false;
    }
    section = my_widget_create(NULL, "editor-lua-panel");
    if (section == NULL) {
        return false;
    }
    (void)my_widget_set_layouter(section,
                                 my_layouter_linear_create(NULL, false, 2));
    label = my_label_create(NULL, "Lua");
    if (label == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(label, "editor-lua-label");
    (void)my_widget_set_layout_params(label, "w:100% h:22");
    if (my_widget_add_child(section, label) == MY_RET_OK) {
        my_widget_unref(label); /* tree holds its own reference */
    } else {
        my_widget_unref(label);
        my_widget_unref(section);
        return false;
    }
    panel->edit = my_edit_create(NULL);
    if (panel->edit == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(panel->edit, "editor-lua-edit");
    (void)my_edit_set_hint(panel->edit, "lua — Enter evaluates");
    (void)my_edit_set_max_len(panel->edit, EDITOR_LUA_EDIT_MAX_CODEPOINTS);
    (void)my_widget_on(panel->edit, "activate", on_lua_edit_activate, panel);
    (void)my_widget_on(panel->edit, "key_down", on_lua_edit_key_down, panel);
    (void)my_widget_set_layout_params(panel->edit, "w:100% h:26");
    if (my_widget_add_child(section, panel->edit) == MY_RET_OK) {
        my_widget_unref(panel->edit); /* tree holds its own reference */
    } else {
        my_widget_unref(panel->edit);
        my_widget_unref(section);
        return false;
    }
    /* bottom row right column: 40% of the row width */
    (void)my_widget_set_layout_params(section, "w:40% h:100%");
    if (my_widget_add_child(parent, section) == MY_RET_OK) {
        my_widget_unref(section); /* tree holds its own reference */
    } else {
        my_widget_unref(section);
        return false;
    }
    return true;
}

usize editor_panel_lua_history_count(const EditorPanelLua *panel) {
    return panel != NULL ? (usize)panel->history_count : 0u;
}
