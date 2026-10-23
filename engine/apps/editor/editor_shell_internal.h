#pragma once
/* Internal wiring shared between editor_panels.c (the shell) and the
 * Phase 3 Task 3 panel translation units (editor_panel_assets.c /
 * editor_panel_lua.c / editor_panel_profiler.c). NOT part of the public
 * editor_panels.h surface: the panel structs are opaque to the shell, which
 * stores one pointer per panel and reaches panel state only through these
 * functions (the editor_viewport3d.c precedent — cross-TU access goes
 * through declared functions, never struct poking).
 *
 * Lifecycle (both the real-window and the dummy-PAL test path):
 *   create  = CPU-side state only (assets model, Lua console core, profiler
 *             snapshot); called from shell_create_common AFTER the doc
 *             exists. Widgets are NOT created here.
 *   build   = widget construction into `parent`; called from
 *             shell_build_panels at the layout points. Widget pointers held
 *             by the panels are WEAK (owned by the window tree).
 *   destroy = frees ONLY the CPU-side state (never touches widgets); called
 *             from break_editor_shell_destroy BEFORE the doc is destroyed
 *             (the Lua console borrows the doc).
 *
 * Threading: single-owner-thread convention, same as the shell/document. */

#include "editor_panels.h"

#include "myui/my_widget.h"

typedef struct EditorPanelAssets EditorPanelAssets;
typedef struct EditorPanelLua EditorPanelLua;
typedef struct EditorPanelProfiler EditorPanelProfiler;

/* Shared shell services implemented in editor_panels.c. editor_shell_log
 * appends one bounded (<=127 visible bytes) line to the shared console ring;
 * editor_shell_refresh_all republishes outliner/inspector/status after a
 * document mutation. */
void editor_shell_log(BreakEditorShell *shell, const char *fmt, ...);
void editor_shell_refresh_all(BreakEditorShell *shell);

/* Assets browser panel (model: BreakEditorAssets, Phase 3 Task 1). The
 * default root at create is "." (process cwd); a create failure of the
 * default model is degraded (empty panel + label note), never fatal. */
EditorPanelAssets *editor_panel_assets_create(BreakEditorShell *shell);
void editor_panel_assets_destroy(EditorPanelAssets *panel);
bool editor_panel_assets_build(EditorPanelAssets *panel, my_widget_t *parent);
/* Re-roots the model (bounded false keeps the previous root). */
bool editor_panel_assets_set_root(EditorPanelAssets *panel,
                                  const char *root_path);
usize editor_panel_assets_row_count(const EditorPanelAssets *panel);
const char *editor_panel_assets_path_text(const EditorPanelAssets *panel);

/* Lua console panel (core: BreakEditorLuaConsole, Phase 3 Task 2). A NULL
 * console (core create failure) degrades eval to a bounded error line. */
EditorPanelLua *editor_panel_lua_create(BreakEditorShell *shell);
void editor_panel_lua_destroy(EditorPanelLua *panel);
bool editor_panel_lua_build(EditorPanelLua *panel, my_widget_t *parent);
usize editor_panel_lua_history_count(const EditorPanelLua *panel);

/* Profiler panel — PURE VIEW over profiler_last_frame(); never mutates
 * profiler state (no enable/begin/push/pop calls). */
EditorPanelProfiler *editor_panel_profiler_create(BreakEditorShell *shell);
void editor_panel_profiler_destroy(EditorPanelProfiler *panel);
bool editor_panel_profiler_build(EditorPanelProfiler *panel,
                                 my_widget_t *parent);
/* Throttled (<= 4 Hz) snapshot refresh; called from break_editor_shell_tick.
 * The first tick after create always refreshes. */
void editor_panel_profiler_tick(EditorPanelProfiler *panel);
usize editor_panel_profiler_row_count(const EditorPanelProfiler *panel);
const char *editor_panel_profiler_row_text(const EditorPanelProfiler *panel,
                                           usize i);
