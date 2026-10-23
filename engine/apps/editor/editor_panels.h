#pragma once
/* BreakEditorShell — Stage 4 scene editor Phase 1 shell + panels (Task 4).
 *
 * The shell owns ONE BreakEditorDoc and the myui widget tree that edits it:
 * toolbar (add/remove entity buttons + tool state label), left outliner
 * (virtualized my_list_view over break_editor_doc_entity_*), right inspector
 * (selected entity name edit + editable component f32 fields), bottom console
 * (bounded 64-entry log ring on a read-only my_text_area), a status bar
 * (entity count / dirty marker / last command description), and a Ctrl+P
 * command palette (my_edit + filtered my_list_view over the registered
 * command names; executes on "activate").
 *
 * Layering rule (plan Global Constraints): widget callbacks NEVER call
 * world_* directly — every document mutation routes through
 * break_editor_doc_* / break_editor_undo/redo so the command stack stays the
 * single mutation path. Pinned by test_editor_shell.c
 * (rename_via_name_edit_then_undo_reverts_displayed_name and
 * inspector_field_edit_routes_through_command_stack).
 *
 * Selection lives on the SHELL (BreakEditorEntityId selected), not on the
 * doc: the doc API surface from Tasks 1-3 has no selection set, and Phase 1
 * keeps it that way (the sidecar stores names only). Outliner row clicks set
 * it via break_editor_shell_select_index; any refresh re-validates it against
 * the doc and clears it when the entity no longer exists.
 *
 * Window binding: break_editor_shell_create(win) builds the panel tree into
 * the window's content widget (BORROWED window — the BreakUI bridge owns it;
 * editor_main.c path). break_editor_shell_create_for_test() instead creates
 * its own dummy-PAL platform + main loop + window manager + 800x480 window
 * (headless, no RHI) and builds into that. Both paths share every panel
 * builder and the shortcut table, so the headless tests exercise the same
 * wiring the real window uses. The shell root is attached with a linear
 * layouter on the window content widget so window resizes reflow the panels
 * (the palette overlay is a floating child, skipped by layouters).
 *
 * Key routing in the real window: the shell listens for "key_down" on its
 * root container; the myui dispatcher bubbles unconsumed key events from the
 * focused widget up to it (my_event_dispatch.c: KEY_DOWN delivers to the
 * focused widget and bubbles to parents), so shortcuts fire only when the
 * focused widget did not consume the key (e.g. typing Q into an edit field
 * does not switch tools). The shell focuses its root container at create so
 * shortcuts work before any widget is clicked. Tests bypass dispatch and call
 * break_editor_shell_dispatch_key directly.
 *
 * Shortcut table (single table in editor_panels.c; letter keys ignore SHIFT,
 * Ctrl/Alt must match exactly):
 *   Q/W/E/R   tool state select/translate/rotate/scale (label only, no gizmo)
 *   F         focus-selected intent — status/console note only (camera is
 *             Phase 2)
 *   Ctrl+S    save to the path set via break_editor_shell_set_scene_path
 *   Ctrl+Z/Y  undo/redo via the doc command stack
 *   Ctrl+P    toggle the command palette
 *   Escape    close the palette (while open)
 *   Return    execute the first filtered palette command (while open)
 *
 * Bounds: console ring 64 entries x 128 bytes; palette filter and name edits
 * capped at 127 codepoints (name cap is the doc's BREAK_EDITOR_NAME_CAPACITY);
 * scene path capped at BREAK_EDITOR_SCENE_PATH_CAPACITY; the row-click
 * context pool is fixed at 64 entries per shell (virtualized lists create
 * only visible+1 rows; on exhaustion rows still render but lose click).
 *
 * Threading: single-owner-thread convention, same as the document. */

#include <core/types.h>

#include <editor/editor_doc.h>

struct my_window_t;
struct my_widget_t;

typedef struct BreakEditorShell BreakEditorShell;

/* Real-window path: builds the panel tree into win's content widget. The
 * window is borrowed; the doc and the panel tree are shell-owned. NULL on
 * bounded failure (allocation). */
BreakEditorShell *break_editor_shell_create(struct my_window_t *win);

/* Headless test path: dummy PAL + own 800x480 window, no RHI. */
BreakEditorShell *break_editor_shell_create_for_test(void);

/* NULL is a no-op. The real-window path detaches the panel tree from the
 * borrowed window; the test path tears down its window/wm/loop/pal. */
void break_editor_shell_destroy(BreakEditorShell *shell);

/* Shortcut router (see the header table). Returns true when the key was
 * consumed by a shortcut (or by the open palette's Escape/Return). */
bool break_editor_shell_dispatch_key(BreakEditorShell *shell, u32 key,
                                     u32 modifiers);

/* Configures the Ctrl+S / palette-save target (bounded copy; false on NULL
 * shell/path or over-cap path, leaving the previous path unchanged). */
bool break_editor_shell_set_scene_path(BreakEditorShell *shell,
                                       const char *path);

/* Read-only inspection surface (borrowed results; used by the headless tests
 * and by editor_main for status plumbing). */
BreakEditorDoc *break_editor_shell_doc(BreakEditorShell *shell); /* borrowed */
struct my_window_t *break_editor_shell_window(BreakEditorShell *shell);
struct my_widget_t *break_editor_shell_root(BreakEditorShell *shell);
usize break_editor_shell_outliner_count(const BreakEditorShell *shell);
const char *break_editor_shell_tool_text(const BreakEditorShell *shell);
const char *break_editor_shell_status_text(const BreakEditorShell *shell);
const char *break_editor_shell_console_text(const BreakEditorShell *shell);
const char *break_editor_shell_name_edit_text(const BreakEditorShell *shell);
BreakEditorEntityId break_editor_shell_selected(const BreakEditorShell *shell);

/* Selects the entity at outliner row i (the row-click handler routes here).
 * Bounded false for i >= entity count; clears nothing on failure. */
bool break_editor_shell_select_index(BreakEditorShell *shell, usize i);

/* Command palette inspection/control (the my_edit "changed" handler routes
 * through break_editor_shell_palette_set_filter). */
bool break_editor_shell_palette_is_open(const BreakEditorShell *shell);
usize break_editor_shell_palette_count(const BreakEditorShell *shell);
bool break_editor_shell_palette_set_filter(BreakEditorShell *shell,
                                           const char *text);
