#pragma once
/* BreakEditorViewport3D — Stage 4 scene editor Phase 2 Task 3: the GPU half
 * of the 3D viewport (offscreen RHI render of entity proxy cubes + gizmo
 * handles, blitted into the myui layout) plus the viewport panel widget that
 * routes pointer events into the Phase 2 CPU core (editor_viewport.h /
 * editor_gizmo.h).
 *
 * Layering: this is the only editor file that creates or records GPU work.
 * The render debugger panel performs read-only RHI queries separately. All
 * camera / pick / gizmo math lives in the pure-CPU core (Tasks 1-2); the
 * widget never mutates the document except through the gizmo's undoable drag
 * commands, and camera moves (orbit/pan/zoom/focus) are view state — NOT
 * undoable (plan Global Constraints).
 *
 * GPU object lifecycle: create() allocates NO GPU objects. prepare(), called
 * explicitly or when the shell attaches a non-NULL device, creates the shader
 * pipeline and cube vertex buffer; render() can still perform that initial
 * preparation and creates/recreates the FBO for its pixel size. render() is a
 * bounded no-op without a device/cmd, below 32x32 px, or after init failure.
 *
 * Frame contract (editor_main.c): render() is called BETWEEN
 * break_ui_frame_begin() and break_ui_render() on the SAME command buffer.
 * The pass binds the viewport FBO (bind = clear, R617), draws, and unbinds
 * back to the swapchain pass with the screen size set via
 * break_editor_viewport3d_set_screen_size(). The widget's on_paint then
 * blits fbo.color_tex into the retained UI surface through
 * my_vgcanvas_break_rhi_blit_texture().
 *
 * Texture orientation (static code analysis of both backends' FBO viewport
 * conventions — rhi_gl.c gl_set_fbo_pass_state and rhi_vk.c
 * rhi_offscreen_fbo_bind both store NDC +Y at texture v=1; consistent with
 * the recorded smoke run, which captured init/survival logs only and is NOT
 * pixel evidence): the renderer negates the projection's Y scale so NDC +Y
 * (scene up) lands at texture row 0 (v=0) — matching the blit's convention
 * that v=0 samples at the dst TOP edge (the my_vgcanvas_break_rhi_blit_texture
 * / rhi_draw_image convention). The CPU-side pick/gizmo math uses the
 * UN-negated matrices; the flip is render-only.
 *
 * Model matrix convention (plan Global Constraints, Task 2 pinned):
 * EditorTransform.rot[k] is the rotation ABOUT axis k in DEGREES; the model
 * matrix composes M = T(pos) * R_y(rot.y) * R_x(rot.x) * R_z(rot.z) *
 * S(scale). break_editor_viewport3d_model_matrix is exposed (pure CPU) so
 * the headless shell tests pin the convention.
 *
 * Selection highlight (documented minimal variant): the selected entity's
 * proxy cube is drawn with a warm tint instead of the default proxy color —
 * a flat-color substitution, no outline/wireframe pass (Phase 3+).
 *
 * Threading/ownership: single-owner-thread, same convention as the document
 * and shell. The viewport BORROWS the device, camera, and gizmo (all
 * shell-owned); the shell owns the viewport and destroys it (after the panel
 * tree is detached, before/around doc teardown — GPU object destruction
 * requires the borrowed device to still be alive).
 */

#include <core/types.h>

#include <editor/editor_doc.h>
#include <editor/editor_gizmo.h>
#include <editor/editor_viewport.h>

#include <rhi/rhi.h>

#include "editor_shader_reload.h"

struct my_widget_t;
typedef struct BreakEditorShell BreakEditorShell;

typedef struct BreakEditorViewport3D BreakEditorViewport3D;

BreakEditorViewport3D *break_editor_viewport3d_create(void);
/* false retains the viewport, reload owner, source/apply pointers, device and
 * GPU objects for a later destroy retry after a worker shutdown timeout. */
bool break_editor_viewport3d_destroy(BreakEditorViewport3D *vp);

/* Initial one-shot GPU preparation through the shared shader resolver. The
 * device is borrowed and recorded before any fallible GPU/source step; device
 * migration is unsupported. Initial failure is sticky for frame-driven calls. */
bool break_editor_viewport3d_prepare(BreakEditorViewport3D *vp,
                                     void *rhi_device);
/* Build and publish a complete shader candidate atomically. Failure preserves
 * every live GPU field; an explicit call can recover initial INIT_FAILED. */
bool break_editor_viewport3d_reload_shader_source(
    BreakEditorViewport3D *vp, const void *vert, usize vert_size,
    const void *frag, usize frag_size);

void break_editor_viewport3d_set_shader_reload_logger(
    BreakEditorViewport3D *vp, BreakEditorShaderReloadLog log, void *user);
void break_editor_viewport3d_tick(BreakEditorViewport3D *vp);
bool break_editor_viewport3d_request_shader_reload(BreakEditorViewport3D *vp);
bool break_editor_viewport3d_shader_reload_stats(
    const BreakEditorViewport3D *vp, BreakEditorShaderReloadStats *out);

#ifdef BREAK_EDITOR_SHELL_TESTING
/* Test-only owner replacement for panel integration fixtures. Ownership of
 * reload transfers only on success; false retains the previous owner. */
bool break_editor_viewport3d_replace_shader_reload_for_test(
    BreakEditorViewport3D *vp, BreakEditorShaderReload *reload);
void break_editor_viewport3d_set_shader_reload_shutdown_timeout_for_test(
    BreakEditorViewport3D *vp, u32 timeout_ms);
typedef struct {
    RHIPipeline pipeline;
    const void *bindings;
    i32 loc_mvp, loc_color;
    RHIBuffer vbo;
} BreakEditorViewport3DGpuState;
void break_editor_viewport3d_gpu_state_for_test(
    const BreakEditorViewport3D *vp, BreakEditorViewport3DGpuState *out);
#endif

/* Borrowed view-state wiring (shell-owned camera/gizmo; selected entity for
 * the highlight tint). Call again whenever the selection changes; NULL
 * camera disables rendering (bounded no-op). */
void break_editor_viewport3d_set_view_state(BreakEditorViewport3D *vp,
                                            const BreakEditorCamera *cam,
                                            BreakEditorGizmo *gizmo,
                                            BreakEditorEntityId selected);

/* Full-drawable pixel size, refreshed per frame before render() — the FBO
 * unbind restores the swapchain pass with these extents. */
void break_editor_viewport3d_set_screen_size(BreakEditorViewport3D *vp,
                                             int screen_w, int screen_h);

/* Called from editor_main.c between break_ui_frame_begin and break_ui_render
 * on the same command buffer. panel_w/h are DEVICE pixels (logical rect x
 * input scale). Bounded no-op: NULL args, panel < 32x32, or init failure. */
void break_editor_viewport3d_render(BreakEditorViewport3D *vp,
                                    BreakEditorDoc *doc, void *rhi_device,
                                    void *rhi_cmd, int panel_w, int panel_h);

/* Render debugger (docs/design/editor_render_debugger.md): CPU-side record of
 * the LAST render() call — counters the pass already has, never a GPU
 * readback. "skipped" names why nothing was drawn (or NONE when it was). */
typedef enum {
    BREAK_EDITOR_VIEWPORT3D_INIT_NOT_ATTEMPTED = 0,
    BREAK_EDITOR_VIEWPORT3D_INIT_READY = 1,
    BREAK_EDITOR_VIEWPORT3D_INIT_FAILED = 2
} BreakEditorViewport3DInitState;

typedef enum {
    BREAK_EDITOR_VIEWPORT3D_SKIP_NONE = 0,
    BREAK_EDITOR_VIEWPORT3D_SKIP_NOT_RENDERED, /* no render() call yet */
    BREAK_EDITOR_VIEWPORT3D_SKIP_NO_DEVICE,
    BREAK_EDITOR_VIEWPORT3D_SKIP_PANEL_TOO_SMALL,
    BREAK_EDITOR_VIEWPORT3D_SKIP_NO_CAMERA,
    BREAK_EDITOR_VIEWPORT3D_SKIP_DEVICE_CHANGED,
    BREAK_EDITOR_VIEWPORT3D_SKIP_INIT_FAILED,
    BREAK_EDITOR_VIEWPORT3D_SKIP_FBO_FAILED
} BreakEditorViewport3DSkip;

typedef struct BreakEditorViewport3DStats {
    int init_state;   /* BreakEditorViewport3DInitState */
    int skipped;      /* BreakEditorViewport3DSkip */
    u32 fbo_w, fbo_h; /* 0 when no FBO exists */
    u32 proxies;      /* entity proxy boxes drawn */
    u32 gizmo_handles;/* gizmo handle boxes drawn */
    u32 draws;        /* draw calls recorded (proxies + handles + outline) */
    u32 outline_edges;/* selection outline edge boxes drawn (0 or 12) */
} BreakEditorViewport3DStats;

/* False on NULL arguments. */
bool break_editor_viewport3d_last_stats(const BreakEditorViewport3D *vp,
                                        BreakEditorViewport3DStats *out);
/* Stable short name for a skip reason ("none", "no-device", ...). */
const char *break_editor_viewport3d_skip_name(int skipped);

/* The current FBO color texture; RHI_HANDLE_NULL before the first successful
 * render (the widget paints a placeholder then). Borrowed. */
RHITexture break_editor_viewport3d_color_texture(
    const BreakEditorViewport3D *vp);

/* Pure-CPU model matrix from an EditorTransform (pos + R_y(rot.y) *
 * R_x(rot.x) * R_z(rot.z) in DEGREES + scale), column-major out16. Exposed
 * for the headless known-answer tests. */
void break_editor_viewport3d_model_matrix(const f32 pos[3],
                                          const f32 rot_deg[3],
                                          const f32 scale[3], f32 out16[16]);

/* Selection outline: the 12 edges of the unit proxy cube as thin boxes
 * (cross-section `thickness`, length 1 + thickness so the corners close)
 * in the space of `model`, written as column-major matrices. Returns 12, or
 * 0 for a NULL model / non-positive or non-finite thickness. Pure CPU. */
u32 break_editor_viewport3d_outline_edges(const f32 model[16], f32 thickness,
                                          f32 out[12][16]);

/* Viewport panel widget (myui subclass: custom on_paint blit + pointer
 * routing into the CPU core). Borrows the shell; the tree owns the widget.
 * NULL on bounded allocation failure. */
struct my_widget_t *break_editor_viewport3d_widget_create(
    BreakEditorShell *shell);
