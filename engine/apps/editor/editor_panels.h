#pragma once
/* BreakEditorShell — Stage 4 scene editor Phase 1 shell + panels (Task 4).
 *
 * The shell owns ONE BreakEditorDoc and the myui widget tree that edits it:
 * toolbar (add/remove entity buttons + tool state label), left outliner
 * (virtualized my_list_view over break_editor_doc_entity_*), center 3D
 * viewport panel (Phase 2 Task 3: offscreen RHI render blitted into the
 * layout + pointer routing into the CPU viewport/gizmo core), right inspector
 * (selected entity name edit + editable component f32 fields), bottom row
 * (Phase 3 Task 3: two columns — the bounded 64-entry console log ring on a
 * read-only my_text_area left, the Lua console right), a status bar
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
 *   Q/W/E/R   gizmo mode NONE/TRANSLATE/ROTATE/SCALE + tool label (Phase 2)
 *   F         focus the camera on the selected entity (Phase 2: real
 *             break_editor_camera_focus on the proxy AABB; view state, not
 *             undoable)
 *   Ctrl+S    save to the path set via break_editor_shell_set_scene_path
 *   Ctrl+Z/Y  undo/redo via the doc command stack; mid-gizmo-drag they first
 *             END+COMMIT the in-progress drag (Task 3 policy, pinned by
 *             mid_drag_ctrl_z_commits_then_undoes_the_drag) so the undo
 *             reverts exactly that one committed drag command
 *   Ctrl+P    toggle the command palette
 *   Escape    close the palette (while open)
 *   Return    execute the first filtered palette command (while open)
 *
 * Phase 2 Task 3 viewport panel: the middle row is outliner w:25% +
 * viewport w:1f h:100% + inspector w:28%. The shell owns the
 * BreakEditorCamera (view state), the BreakEditorGizmo (glued to the
 * selection: attach on select, detach when the selection clears), and the
 * BreakEditorViewport3D (GPU side). The viewport widget routes pointer
 * events into the CPU core: left press = gizmo begin_drag else pick+select
 * (miss clears the selection), left-drag with an active gizmo = gizmo drag,
 * right/alt-left drag = orbit, middle/shift-left drag = pan, wheel = zoom.
 * The widget invalidates itself every frame while visible (live 3D view;
 * see break_editor_shell_tick) so the retained UI repaints it — the plan's
 * documented intended damage exception. The dummy-PAL test path has no RHI
 * device: break_editor_shell_render_viewport is a guarded no-op there and no
 * GPU call ever happens (pinned by
 * viewport_render_without_device_is_bounded_noop).
 *
 * Phase 3 Task 3 panels (design doc: docs/design/editor_panels_phase3.md):
 *   - ASSETS browser under the outliner (bottom of the left column, h:40%):
 *     path label + list_view over the Phase 3 Task 1 BreakEditorAssets
 *     model; row 0 is always ".."; row click activates — dirs navigate,
 *     a .bscn loads confirm-free via break_editor_doc_load (world swap +
 *     undo-stack clear are the Phase 2 documented semantics; the load is
 *     logged to the console ring), other files get a bounded note.
 *   - LUA console at bottom-right: the bottom row became two columns —
 *     console ring left (w:1f), Lua panel right (w:40%, my_edit + Enter
 *     evaluates through the Phase 3 Task 2 BreakEditorLuaConsole; core
 *     output lines land in the SHARED console ring prefixed "lua| ").
 *     my_edit has no history recall, so the panel owns a bounded 32-entry
 *     history with Up/Down set_text recall.
 *   - PROFILER view under the inspector (h:30%): pure view — snapshots
 *     profiler_last_frame() at <= 4 Hz from break_editor_shell_tick into
 *     top-N (N<=16) "<name> <ms> ms" rows; NEVER mutates profiler state.
 *   - NETWORK diagnostics under the profiler (Phase 4 Task 3, h:20%; the
 *     right column is the diagnostics area): pure view of the attached
 *     remote's reactor/session/admission/connection state at <= 4 Hz;
 *     "remote: off" when none is attached.
 *   The panel structs are opaque to the shell (one pointer each);
 *   cross-TU wiring goes through editor_shell_internal.h (the
 *   editor_viewport3d.c precedent).
 *
 * Bounds: console ring 64 entries x 128 bytes; palette filter and name edits
 * capped at 127 codepoints (name cap is the doc's BREAK_EDITOR_NAME_CAPACITY);
 * scene path capped at BREAK_EDITOR_SCENE_PATH_CAPACITY; the row-click
 * context pool is fixed at 64 entries per shell (virtualized lists create
 * only visible+1 rows; on exhaustion rows still render but lose click).
 * Phase 3 Task 3 additions: assets row-click pool 32; Lua history 32 entries
 * x 1024 bytes + 255-codepoint edit cap (an edit-sourced line always fits a
 * history entry); profiler snapshot 16 rows x 80 bytes refreshed at <= 4 Hz;
 * assets/profiler paths and rows bounded by the Task 1 model caps.
 * Phase 4 Task 3: network snapshot 16 rows x 96 bytes refreshed at <= 4 Hz
 * (5 fixed rows + up to 11 connection rows).
 *
 * Threading: single-owner-thread convention, same as the document. */

#include <core/types.h>

#include <editor/editor_doc.h>
#include <editor/editor_gizmo.h>
#include <editor/editor_viewport.h>
#include <rhi/rhi.h>

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

/* ---------------- Phase 2 Task 3: viewport panel ---------------- */

/* Borrowed viewport panel widget (NULL before the tree is built). */
struct my_widget_t *break_editor_shell_viewport_widget(BreakEditorShell *shell);
/* Borrowed viewport GPU side (shell-owned; never NULL on a live shell). */
struct BreakEditorViewport3D *break_editor_shell_viewport3d(
    BreakEditorShell *shell);
/* Borrowed mutable camera (view state — mutations are NOT undoable by
 * design; the viewport widget's pointer routing drives this). */
BreakEditorCamera *break_editor_shell_camera(BreakEditorShell *shell);
/* Borrowed gizmo (shell-owned; attached to the selection). */
BreakEditorGizmo *break_editor_shell_gizmo(BreakEditorShell *shell);
/* Current gizmo mode == the shell tool state (NONE/TRANSLATE/ROTATE/SCALE). */
BreakEditorGizmoMode break_editor_shell_gizmo_mode(
    const BreakEditorShell *shell);
/* Selection from a viewport pick: valid id selects (+ gizmo attach);
 * BREAK_EDITOR_ENTITY_NULL clears (+ detach). Bounded false only for a NULL
 * shell. Routes the refresh fan-out like a row click. */
bool break_editor_shell_select_id(BreakEditorShell *shell,
                                  BreakEditorEntityId id);
/* Republish the status/inspector/outliner (viewport gizmo drags end here so
 * the status bar's last-command text tracks them). */
void break_editor_shell_refresh(BreakEditorShell *shell);
/* Per-frame housekeeping from the editor main loop: invalidates the viewport
 * widget while visible (live-view damage) and reconciles the gizmo attach
 * with the selection. Safe no-op on NULL. */
void break_editor_shell_tick(BreakEditorShell *shell);
/* Renders the 3D viewport pass into cmd (between break_ui_frame_begin and
 * break_ui_render). Guarded no-op without a live device/cmd or before the
 * panel tree exists — the dummy-PAL test path never touches the GPU. */
void break_editor_shell_render_viewport(BreakEditorShell *shell,
                                        void *rhi_device, void *rhi_cmd,
                                        int drawable_w, int drawable_h,
                                        int logical_w, int logical_h);

/* ---------------- Phase 3 Task 3: assets / lua / profiler panels --------- */

/* Re-roots the assets browser model (BreakEditorAssets, Task 1) at an
 * existing directory; the assets panel refreshes to the new root. Bounded
 * false for NULL shell/path, an over-cap path, or an unlistable root (the
 * previous model is kept). The default root at shell create is "." (the
 * process cwd). */
bool break_editor_shell_set_assets_root(BreakEditorShell *shell,
                                        const char *root_path);
/* Test seam: injects the monotonic clock behind the browser's 1 s live
 * refresh throttle (NULL = time_microseconds). */
void break_editor_shell_set_assets_clock_for_test(BreakEditorShell *shell,
                                                  u64 (*clock)(void *user),
                                                  void *user);
/* Assets panel row count INCLUDING the always-present ".." top row. */
usize break_editor_shell_assets_row_count(const BreakEditorShell *shell);
/* Borrowed assets path label text ("assets: /<rel>"). */
const char *break_editor_shell_assets_path_text(const BreakEditorShell *shell);

/* Lua console history depth (bounded at 32 entries; my_edit has no history
 * recall, so the panel owns it — Up/Down set_text). */
usize break_editor_shell_lua_history_count(const BreakEditorShell *shell);

/* Profiler panel snapshot rows (top-N by duration, N <= 16, refreshed from
 * profiler_last_frame at <= 4 Hz from break_editor_shell_tick; the panel is
 * a pure view and NEVER mutates profiler state). row_text returns a borrowed
 * "<name> <ms> ms" line, NULL out of range. */
usize break_editor_shell_profiler_row_count(const BreakEditorShell *shell);
const char *break_editor_shell_profiler_row_text(const BreakEditorShell *shell,
                                                 usize i);

/* ---------------- Phase 4 Task 1: remote session host wiring -------------- */

struct BreakEditorRemote;
/* Attaches the host-owned remote session the shell tick drives once per
 * frame (DEFAULT OFF: NULL remote = the pre-remote behavior, byte-identical
 * — pinned by remote_disabled_leaves_shell_untouched). The shell BORROWS
 * the remote: the host (editor_main --remote / tests) owns its lifetime and
 * destroys it. NULL shell is a no-op; NULL remote detaches. */
void break_editor_shell_set_remote(BreakEditorShell *shell,
                                   struct BreakEditorRemote *remote);
/* Borrowed remote the shell tick drives (NULL when unattached — the
 * default). */
struct BreakEditorRemote *break_editor_shell_remote(BreakEditorShell *shell);

/* ---------------- editor asset hot reload host wiring --------------- */

struct BreakEditorHotReload;
/* Attaches the host-owned hot-reload object the shell tick drives once per
 * frame. The shell BORROWS it; the host creates and destroys it
 * (break_editor_hot_reload_destroy detaches itself). Attaching points the
 * object at the current scene path; NULL shell is a no-op, NULL detaches. */
void break_editor_shell_set_hot_reload(BreakEditorShell *shell,
                                       struct BreakEditorHotReload *hr);
struct BreakEditorHotReload *break_editor_shell_hot_reload(
    BreakEditorShell *shell);
/* Configured scene path (Ctrl+S target); "" when none is set. */
const char *break_editor_shell_scene_path(const BreakEditorShell *shell);

/* ---------------- Phase 4 Task 3: network diagnostics panel --------------- */

/* Network panel snapshot rows (<= 16 rows x 96 bytes, refreshed at <= 4 Hz
 * from break_editor_shell_tick; pure view over the attached remote — NEVER
 * steps, sends, closes, or transitions). No remote attached => exactly one
 * "remote: off" row. Row layout: editor_panel_network.c header. row_text
 * returns a borrowed line, NULL out of range. */
uint32_t break_editor_shell_network_row_count(const BreakEditorShell *shell);
const char *break_editor_shell_network_row_text(const BreakEditorShell *shell,
                                                uint32_t index);
/* Test seams: inject the panel's monotonic clock (NULL = the platform
 * clock) to pin the 250,000 us throttle deterministically, and tick ONLY
 * the network panel (no remote step — stable sources for comparisons). */
void break_editor_shell_set_network_clock_for_test(BreakEditorShell *shell,
                                                   u64 (*clock)(void *user),
                                                   void *user);
void break_editor_shell_network_tick_for_test(BreakEditorShell *shell);
#ifdef BREAK_EDITOR_SHELL_TESTING
/* One-shot failure of the shared diagnostics row attachment, for the
 * lifetime regression test. Never compiled into the production editor. */
void break_editor_shell_fail_diag_attach_for_test(void);
#endif

/* ---------------- render debugger panel ----------------
 * Pure view (docs/design/editor_render_debugger.md): backend / GPU / caps /
 * status / resource slots of the BORROWED render device plus the viewport's
 * last-render stats, <= 16 rows x 96 bytes refreshed at <= 4 Hz from
 * break_editor_shell_tick. NULL device renders one "render: no device" row.
 * The host attaches the device after creating the shell and detaches it
 * (NULL) before destroying the device. */
void break_editor_shell_set_render_device(BreakEditorShell *shell,
                                          RHIDevice *device);
uint32_t break_editor_shell_render_row_count(const BreakEditorShell *shell);
const char *break_editor_shell_render_row_text(const BreakEditorShell *shell,
                                               uint32_t index);

/* Read-only data sources the panel queries (production = the RHI and rollout
 * queries; tests inject fakes so no GPU is needed). */
typedef struct BreakEditorRenderSource {
    bool (*device_info)(const void *dev, RHIDeviceInfo *out);
    bool (*capabilities)(const void *dev, RHICapabilities *out);
    RHIDeviceStatus (*status)(const void *dev);
    u32 (*frame_index)(const void *dev);
    bool (*resource_usage)(const void *dev, u32 *used, u32 *capacity);
    const char *(*backend_name)(void);
    const char *(*selection_reason)(void);
} BreakEditorRenderSource;
/* Test seams: NULL source = production RHI queries; NULL clock =
 * time_microseconds (250,000 us throttle, first tick after create or after
 * any device attach/detach always refreshes). */
void break_editor_shell_set_render_source_for_test(
    BreakEditorShell *shell, const BreakEditorRenderSource *source);
void break_editor_shell_set_render_clock_for_test(BreakEditorShell *shell,
                                                  u64 (*clock)(void *user),
                                                  void *user);
