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

#include <rhi/rhi.h>
#include "editor_panels.h"

#include "myui/my_widget.h"

typedef struct EditorPanelAssets EditorPanelAssets;
typedef struct EditorPanelLua EditorPanelLua;
typedef struct EditorPanelProfiler EditorPanelProfiler;
typedef struct EditorPanelFlow EditorPanelFlow;
typedef struct EditorPanelAudio EditorPanelAudio;

/* Shared shell services implemented in editor_panels.c. editor_shell_log
 * appends one bounded (<=127 visible bytes) line to the shared console ring;
 * editor_shell_refresh_all republishes outliner/inspector/status after a
 * document mutation. */
void editor_shell_log(BreakEditorShell *shell, const char *fmt, ...);
void editor_shell_refresh_all(BreakEditorShell *shell);
/* Re-points the scene-texture watcher at the document's RESOURCES chunk and
 * the current scene path. Call after anything that replaces the document or
 * changes where the scene lives (load, new, external reload, save-as). */
void editor_shell_sync_scene_textures(BreakEditorShell *shell);

/* Loads a .bscn scene file into the document and makes it the shell's scene
 * path (Ctrl+S target) and hot-reload target. The scene path and watcher are
 * only changed when the load succeeds. Used by the asset browser. */
bool editor_shell_load_scene(BreakEditorShell *shell, const char *path);
/* The asset browser's load: with unsaved changes the first request for a
 * path only warns (console + status); repeating it for the same path with
 * no edit in between loads (discarding the changes). A clean document
 * loads at once. Returns whether it loaded. */
bool editor_shell_load_scene_guarded(BreakEditorShell *shell, const char *path);

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
/* Image preview owned by the assets panel (editor_image_preview.h): the
 * shell forwards the render device and reads the stats. */
struct BreakEditorImagePreview *editor_panel_assets_preview(
    EditorPanelAssets *panel);
void editor_panel_assets_set_device(EditorPanelAssets *panel,
                                    RHIDevice *device);

/* Lua console panel (core: BreakEditorLuaConsole, Phase 3 Task 2). A NULL
 * console (core create failure) degrades eval to a bounded error line. */
EditorPanelLua *editor_panel_lua_create(BreakEditorShell *shell);
void editor_panel_lua_destroy(EditorPanelLua *panel);
bool editor_panel_lua_build(EditorPanelLua *panel, my_widget_t *parent);
usize editor_panel_lua_history_count(const EditorPanelLua *panel);
/* Ctrl+Shift+L: replace the console with a fresh sandbox. Returns false (and
 * leaves the panel degraded) when the new console cannot be created. */
bool editor_panel_lua_reload(EditorPanelLua *panel);

EditorPanelFlow *editor_panel_flow_create(BreakEditorShell *shell);
void editor_panel_flow_destroy(EditorPanelFlow *panel);
bool editor_panel_flow_build(EditorPanelFlow *panel, my_widget_t *parent);
void editor_panel_flow_tick(EditorPanelFlow *panel);
usize editor_panel_flow_row_count(const EditorPanelFlow *panel);
const char *editor_panel_flow_row_text(const EditorPanelFlow *panel, usize i);
void editor_panel_flow_retranslate(EditorPanelFlow *panel);

/* Audio page (editor_panel_audio.c): read-only view of the document's PCM
 * attachment (info line + min/max waveform). The tick recomputes the columns
 * when the attachment revision or the widget width changed. */
EditorPanelAudio *editor_panel_audio_create(BreakEditorShell *shell);
void editor_panel_audio_destroy(EditorPanelAudio *panel);
bool editor_panel_audio_build(EditorPanelAudio *panel, my_widget_t *parent);
void editor_panel_audio_tick(EditorPanelAudio *panel);
void editor_panel_audio_retranslate(EditorPanelAudio *panel);
const char *editor_panel_audio_info_text(const EditorPanelAudio *panel);
u32 editor_panel_audio_column_count(const EditorPanelAudio *panel);
bool editor_panel_audio_column(const EditorPanelAudio *panel, u32 i,
                               i16 *out_min, i16 *out_max);
/* Preview playback owned by the page (editor_audio_preview.h). */
struct BreakEditorAudioPreview *editor_panel_audio_preview(EditorPanelAudio *panel);
/* Play/Stop button: starts the preview (logs when there is no sink or it
 * fails) or stops it. Returns whether it is playing afterwards. */
bool editor_panel_audio_toggle(EditorPanelAudio *panel);
bool editor_panel_audio_seek(EditorPanelAudio *panel, u32 frame);
bool editor_panel_audio_select(EditorPanelAudio *panel, u32 begin, u32 end);
bool editor_panel_audio_selection(const EditorPanelAudio *panel, u32 *out_begin, u32 *out_end);
/* cut = false: trim to the selection; true: remove it. */
bool editor_panel_audio_edit_selection(EditorPanelAudio *panel, bool cut);
/* normalize = false: fade; true: normalize. Selection or whole clip. */
bool editor_panel_audio_effect(EditorPanelAudio *panel, bool normalize);

bool editor_panel_audio_zoom(EditorPanelAudio *panel, bool in);
/* The same zoom with an explicit anchor frame: it keeps its position in the
 * view, so a wheel zoom leaves the frame under the pointer where it was. */
bool editor_panel_audio_zoom_at(EditorPanelAudio *panel, bool in, u32 anchor);
bool editor_panel_audio_scroll(EditorPanelAudio *panel, bool forward);
bool editor_panel_audio_view(const EditorPanelAudio *panel, u32 *out_begin, u32 *out_end);
/* The page's Follow checkbox: while playing, the view keeps the playing
 * position inside itself by jumping a view length at a time. */
void editor_panel_audio_set_follow(EditorPanelAudio *panel, bool follow);
bool editor_panel_audio_follow(const EditorPanelAudio *panel);
/* Display-only amplitude multiplier, a power of two in [1, 32]. */
/* One lane's factor; the page-wide calls below address every lane. */
u32 editor_panel_audio_set_lane_gain(EditorPanelAudio *panel, u32 lane, u32 gain);
u32 editor_panel_audio_lane_gain(const EditorPanelAudio *panel, u32 lane);
u32 editor_panel_audio_fit_lane_gain(EditorPanelAudio *panel, u32 lane);
u32 editor_panel_audio_set_gain(EditorPanelAudio *panel, u32 gain);
u32 editor_panel_audio_gain(const EditorPanelAudio *panel);
/* One lane per channel, stacked; lane 0 is what editor_panel_audio_column
 * reads. 0 lanes without an attachment. */
u32 editor_panel_audio_fit_gain(EditorPanelAudio *panel);
/* Preview solo; BREAK_EDITOR_AUDIO_SOLO_NONE plays every channel. */
u32 editor_panel_audio_set_solo(EditorPanelAudio *panel, u32 channel);
u32 editor_panel_audio_solo(const EditorPanelAudio *panel);
/* Preview mute; BREAK_EDITOR_AUDIO_MUTE_NONE mutes nothing. */
/* Peak/RMS of the view in dBFS, floored at -120. */
/* The dB grid of the last paint, in lane 0's coordinates. */
u32 editor_panel_audio_grid_count(const EditorPanelAudio *panel);
bool editor_panel_audio_grid(const EditorPanelAudio *panel, u32 i, double *out_db,
                             i32 *out_y);
/* The label drawn for grid entry i ("" when unlabelled, NULL when i is out
 * of range). */
const char *editor_panel_audio_grid_label(const EditorPanelAudio *panel, u32 i);
/* The lane grid entry i belongs to (UINT32_MAX when i is out of range). */
u32 editor_panel_audio_grid_lane(const EditorPanelAudio *panel, u32 i);
double editor_panel_audio_peak_db(const EditorPanelAudio *panel);
/* True peak of the view in dBTP, floored at -120; may be positive. */
double editor_panel_audio_true_peak_db(const EditorPanelAudio *panel);
/* The view's integrated loudness in LUFS, or the -70 floor. */
double editor_panel_audio_lufs(const EditorPanelAudio *panel);
/* The view's short-term loudness (-70 floor) and loudness range (0 LU
 * when the view is too short). */
double editor_panel_audio_short_term_lufs(const EditorPanelAudio *panel);
double editor_panel_audio_lra(const EditorPanelAudio *panel);
double editor_panel_audio_rms_db(const EditorPanelAudio *panel);
u32 editor_panel_audio_set_mute(EditorPanelAudio *panel, u32 channel);
u32 editor_panel_audio_mute(const EditorPanelAudio *panel);
u32 editor_panel_audio_lane_count(const EditorPanelAudio *panel);
bool editor_panel_audio_lane_column(const EditorPanelAudio *panel, u32 lane, u32 i,
                                    i16 *out_min, i16 *out_max);

/* The page's Loop checkbox: forwards to the preview and updates the box. */
void editor_panel_audio_set_loop(EditorPanelAudio *panel, bool loop);

/* Timeline ruler model (design 2026-11-19-editor-audio-timeline): the ticks
 * for the current clip and the ruler's width, at least 60 px apart. */
#define EDITOR_AUDIO_TICKS_MAX 32u
typedef struct {
    u32 count;
    u32 frame[EDITOR_AUDIO_TICKS_MAX];
    i32 x[EDITOR_AUDIO_TICKS_MAX];
    char label[EDITOR_AUDIO_TICKS_MAX][16];
} EditorAudioTicks;
/* False (count 0) without an attachment, frames or width. */
bool editor_panel_audio_ticks(const EditorPanelAudio *panel, EditorAudioTicks *out);
/* Asset browser: opens a .wav file into the document's attachment (only when
 * none is attached), logs the outcome, selects the Audio tab on success. */
bool editor_shell_open_audio(BreakEditorShell *shell, const char *path,
                             const char *name);

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
struct BreakEditorSceneTextures;
/* `textures` (optional) adds the scene-texture rows after the fixed ones;
 * the panel only reads it. */
void editor_panel_render_tick(BreakEditorPanelRender *p,
                              const struct BreakEditorViewport3D *vp,
                              const struct BreakEditorSceneTextures *textures);
/* Marks the rows stale so the next tick rebuilds them (a texture changed). */
void editor_panel_render_invalidate(BreakEditorPanelRender *p);
void editor_panel_render_set_device(BreakEditorPanelRender *p, void *device);
void editor_panel_render_set_source(BreakEditorPanelRender *p,
                                    const BreakEditorRenderSource *source);
void editor_panel_render_set_clock(BreakEditorPanelRender *p,
                                   u64 (*clock)(void *user), void *user);
uint32_t editor_panel_render_row_count(const BreakEditorPanelRender *p);
const char *editor_panel_render_row_text(const BreakEditorPanelRender *p,
                                         uint32_t index);

/* Re-apply the current editor language (editor_i18n.h) to each panel's own
 * titles and hints; called by break_editor_shell_set_language. NULL-safe. */
void editor_panel_assets_retranslate(EditorPanelAssets *panel);
void editor_panel_lua_retranslate(EditorPanelLua *panel);
void editor_panel_profiler_retranslate(EditorPanelProfiler *panel);
void editor_panel_network_retranslate(BreakEditorPanelNetwork *p);
void editor_panel_render_retranslate(BreakEditorPanelRender *p);

/* Reverse-teardown seam (editor_remote.c): break_editor_shell_destroy calls
 * this FIRST for its attached remote (while the doc is still alive). When
 * the remote belongs to `shell`, it drops its back-pointer, destroys its
 * doc-borrowing console core, and stops its reactor, so the orphaned remote
 * is inert: a later tick is a no-op and break_editor_remote_destroy never
 * touches the freed shell or its network panel. NULL remote / foreign shell
 * is a no-op. */
void editor_remote_shell_destroyed(struct BreakEditorRemote *r,
                                   BreakEditorShell *shell);
