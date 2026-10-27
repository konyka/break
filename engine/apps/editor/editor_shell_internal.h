#pragma once
/* Internal wiring shared between editor_panels.c (the shell) and the
 * Phase 3 Task 3 panel translation units (editor_panel_assets.c /
 * editor_panel_lua.c / editor_panel_profiler.c). NOT part of the public
 * editor_panels.h surface: the panel structs are opaque to the shell, which
 * stores one pointer per panel and reaches panel state only through these
 * functions (the editor_viewport3d.c precedent — cross-TU access goes
 * through declared functions, never struct poking).
 *
 * Phase 4 Task 3 adds editor_panel_network.c on the same contract.
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

/* Loads a .bscn scene file into the document and makes it the shell's scene
 * path (Ctrl+S target) and hot-reload target. The scene path and watcher are
 * only changed when the load succeeds. Used by the asset browser. */
bool editor_shell_load_scene(BreakEditorShell *shell, const char *path);

/* Hot-reload host wiring (editor_hot_reload.c): the shell calls these from
 * its destroy/attach paths. */
struct BreakEditorHotReload;
void editor_hot_reload_shell_destroyed(struct BreakEditorHotReload *hr,
                                       BreakEditorShell *shell);
void editor_hot_reload_attach(struct BreakEditorHotReload *hr,
                              BreakEditorShell *shell);

/* Assets browser panel (model: BreakEditorAssets, Phase 3 Task 1). The
 * default root at create is "." (process cwd); a create failure of the
 * default model is degraded (empty panel + label note), never fatal. */
EditorPanelAssets *editor_panel_assets_create(BreakEditorShell *shell);
void editor_panel_assets_destroy(EditorPanelAssets *panel);
bool editor_panel_assets_build(EditorPanelAssets *panel, my_widget_t *parent);
/* Re-roots the model (bounded false keeps the previous root). */
void editor_panel_assets_tick(EditorPanelAssets *panel);
void editor_panel_assets_set_clock(EditorPanelAssets *panel,
                                   u64 (*clock)(void *user), void *user);
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

/* Network diagnostics panel (Phase 4 Task 3) — PURE VIEW over the borrowed
 * host-attached remote (read-only editor_remote.h accessors only; never
 * steps/sends/closes/transitions). Mirrors the profiler lifecycle; built
 * into the diagnostics column (editor-right-panel) directly under the
 * profiler at h:20%. The shell forwards every break_editor_shell_set_remote
 * attach/detach through editor_panel_network_set_remote (forces a refresh
 * on the next tick). remote == NULL renders one "remote: off" row. A build
 * failure degrades to no network widgets (non-fatal, void per the plan's
 * verbatim interface). */
typedef struct BreakEditorPanelNetwork BreakEditorPanelNetwork;
struct BreakEditorRemote;
BreakEditorPanelNetwork *editor_panel_network_create(
    BreakEditorShell *shell, struct BreakEditorRemote *remote);
void editor_panel_network_destroy(BreakEditorPanelNetwork *p);
void editor_panel_network_build(BreakEditorPanelNetwork *p,
                                my_widget_t *parent);
/* <= 4 Hz snapshot (250,000 us), never mutates; called from
 * break_editor_shell_tick BEFORE the remote tick. */
void editor_panel_network_tick(BreakEditorPanelNetwork *p);
void editor_panel_network_set_remote(BreakEditorPanelNetwork *p,
                                     struct BreakEditorRemote *remote);
/* Test seam: injectable monotonic clock (NULL = time_microseconds). */
void editor_panel_network_set_clock(BreakEditorPanelNetwork *p,
                                    u64 (*clock)(void *user), void *user);
uint32_t editor_panel_network_row_count(const BreakEditorPanelNetwork *p);
const char *editor_panel_network_row_text(const BreakEditorPanelNetwork *p,
                                          uint32_t index);

/* Render debugger panel (editor_panel_render.c) — pure view over a borrowed
 * RHI device + the viewport's last-render/shader-reload stats; same lifecycle
 * as the network panel, built beside it in the shared diagnostics row at h:20%. */
typedef struct BreakEditorPanelRender BreakEditorPanelRender;
struct BreakEditorViewport3D;
BreakEditorPanelRender *editor_panel_render_create(BreakEditorShell *shell);
void editor_panel_render_destroy(BreakEditorPanelRender *p);
void editor_panel_render_build(BreakEditorPanelRender *p, my_widget_t *parent);
void editor_panel_render_tick(BreakEditorPanelRender *p,
                              const struct BreakEditorViewport3D *vp);
void editor_panel_render_set_device(BreakEditorPanelRender *p, void *device);
void editor_panel_render_set_source(BreakEditorPanelRender *p,
                                    const BreakEditorRenderSource *source);
void editor_panel_render_set_clock(BreakEditorPanelRender *p,
                                   u64 (*clock)(void *user), void *user);
uint32_t editor_panel_render_row_count(const BreakEditorPanelRender *p);
const char *editor_panel_render_row_text(const BreakEditorPanelRender *p,
                                         uint32_t index);

/* Reverse-teardown seam (editor_remote.c): break_editor_shell_destroy calls
 * this FIRST for its attached remote (while the doc is still alive). When
 * the remote belongs to `shell`, it drops its back-pointer, destroys its
 * doc-borrowing console core, and stops its reactor, so the orphaned remote
 * is inert: a later tick is a no-op and break_editor_remote_destroy never
 * touches the freed shell or its network panel. NULL remote / foreign shell
 * is a no-op. */
void editor_remote_shell_destroyed(struct BreakEditorRemote *r,
                                   BreakEditorShell *shell);
