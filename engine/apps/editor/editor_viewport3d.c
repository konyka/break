/* BreakEditorViewport3D implementation — see editor_viewport3d.h for the
 * contract (lazy GPU lifecycle, frame ordering, texture-orientation flip,
 * model-matrix convention, minimal selection highlight, ownership).
 *
 * Pointer routing (viewport widget on_event; coordinates are viewport-local
 * logical px — the dispatcher delivers global coords, converted with
 * my_widget_global_to_local):
 *   left press            gizmo begin_drag when a handle is hit; otherwise
 *                         pick -> select (hit) / clear selection (miss;
 *                         Ctrl keeps it) and arm a box select
 *   left drag (empty)     past EDITOR_VIEWPORT_BOX_THRESHOLD px it becomes a
 *                         box; release selects the centers inside
 *                         (break_editor_viewport_box_select; Ctrl adds)
 *   left drag (gizmo)     break_editor_gizmo_drag; a false return mid-drag
 *                         means the drag vanished (external Ctrl+Z commit —
 *                         the documented Task 3 policy) and the widget drops
 *                         its drag state (self-healing; the up is a no-op)
 *   right / alt-left drag orbit (EDITOR_VIEWPORT_ORBIT_DEG_PER_PX per px);
 *                         while the right button is held W/A/S/D/Q/E fly
 *                         (break_editor_shell_set_flying)
 *   middle / shift-left   pan (pixel deltas rescaled so one logical pixel
 *                         pans one screen pixel at the CURRENT widget
 *                         height — camera_pan's reference height is 720)
 *   wheel                 zoom (positive delta zooms in)
 * All mutations route through the CPU core: gizmo drags are the ONLY
 * doc mutations (single undoable command per drag); camera moves are view
 * state and never touch the command stack. Camera/gizmo math always uses the
 * widget's CURRENT rect.
 *
 * Gizmo draw order: handles are drawn AFTER the proxy cubes with a depth
 * clear in between so the gizmo stays visible over scene geometry (minimal
 * editor-style overlay; no stencil/outline pass in Phase 2).
 */

#include "editor_viewport3d.h"

#include "editor_panels.h"
#include "editor_theme.h"
#include "editor_shader_source.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editor/editor_components.h>
#include <math/math.h>

#include "mypal/my_event.h"
#include "myr/my_color.h"
#include "myr/my_vgcanvas.h"
#include "myr/my_vgcanvas_break_rhi.h"
#include "myui/my_widget.h"

/* Plan bound: skip rendering below this panel size (px). */
#define EDITOR_VIEWPORT_MIN_PANEL 32
/* Proxy draw iteration shares the pick candidate bound (plan Global
 * Constraints: <= 4096 entities per query). */
#define EDITOR_VIEWPORT_MAX_DRAW BREAK_EDITOR_PICK_MAX_ENTITIES
/* Orbit rate: degrees per dragged logical pixel. */
#define EDITOR_VIEWPORT_ORBIT_DEG_PER_PX 0.25f
/* camera_pan's reference height (editor_viewport.h) for the pan rescale. */
#define EDITOR_VIEWPORT_PAN_REF_H BREAK_EDITOR_VIEWPORT_PAN_REFERENCE_HEIGHT

/* Viewport background (owned via rhi_offscreen_fbo_set_clear_color, R619). */
#define EDITOR_VIEWPORT_CLEAR_R 0.13f
#define EDITOR_VIEWPORT_CLEAR_G 0.14f
#define EDITOR_VIEWPORT_CLEAR_B 0.16f

/* Flat proxy colors: default slate, selected warm tint (documented minimal
 * selection highlight — a flat-color substitution, no outline pass). */
static const f32 k_proxy_color[4] = {0.55f, 0.58f, 0.64f, 1.0f};
static const f32 k_selected_color[4] = {1.0f, 0.62f, 0.18f, 1.0f};
/* selection outline: bright edges around the selected proxy */
static const f32 k_outline_color[4] = {1.0f, 0.92f, 0.55f, 1.0f};
#define EDITOR_VIEWPORT_OUTLINE_THICKNESS 0.035f
#define EDITOR_VIEWPORT_RING_SEGMENTS 48u
static const f32 k_gizmo_colors[5][4] = {
    {0.0f, 0.0f, 0.0f, 0.0f},                 /* PART_NONE (unused) */
    {0.90f, 0.25f, 0.25f, 1.0f},              /* X */
    {0.30f, 0.80f, 0.30f, 1.0f},              /* Y */
    {0.30f, 0.45f, 0.95f, 1.0f},              /* Z */
    {0.85f, 0.85f, 0.80f, 1.0f},              /* CENTER */
};

/* Unit cube centered at the origin, spanning [-0.5, +0.5]^3 (36 verts,
 * position-only; the proxy AABB convention half-extent = 0.5*scale matches
 * exactly). Culling is disabled on the pipeline, so winding is irrelevant. */
static const f32 k_cube_verts[36 * 3] = {
    /* -X */ -0.5f,-0.5f,-0.5f,  -0.5f, 0.5f, 0.5f,  -0.5f, 0.5f,-0.5f,
             -0.5f,-0.5f,-0.5f,  -0.5f,-0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,
    /* +X */  0.5f,-0.5f,-0.5f,   0.5f, 0.5f,-0.5f,   0.5f, 0.5f, 0.5f,
              0.5f,-0.5f,-0.5f,   0.5f, 0.5f, 0.5f,   0.5f,-0.5f, 0.5f,
    /* -Y */ -0.5f,-0.5f,-0.5f,  -0.5f,-0.5f, 0.5f,   0.5f,-0.5f, 0.5f,
             -0.5f,-0.5f,-0.5f,   0.5f,-0.5f, 0.5f,   0.5f,-0.5f,-0.5f,
    /* +Y */ -0.5f, 0.5f,-0.5f,   0.5f, 0.5f,-0.5f,   0.5f, 0.5f, 0.5f,
             -0.5f, 0.5f,-0.5f,   0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,
    /* -Z */ -0.5f,-0.5f,-0.5f,   0.5f,-0.5f,-0.5f,   0.5f, 0.5f,-0.5f,
             -0.5f,-0.5f,-0.5f,   0.5f, 0.5f,-0.5f,  -0.5f, 0.5f,-0.5f,
    /* +Z */ -0.5f,-0.5f, 0.5f,   0.5f, 0.5f, 0.5f,   0.5f,-0.5f, 0.5f,
             -0.5f,-0.5f, 0.5f,   0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,
};

enum {
    VP_DRAG_NONE = 0,
    VP_DRAG_GIZMO,
    VP_DRAG_ORBIT,
    VP_DRAG_PAN,
    VP_DRAG_BOX_PENDING, /* left press on empty space, not moved yet */
    VP_DRAG_BOX
};

/* pointer travel (logical px) before a press on empty space becomes a box */
#define EDITOR_VIEWPORT_BOX_THRESHOLD 4.0f
#define EDITOR_VIEWPORT_BOX_MAX 256u
/* ground grid: lines every unit from -HALF to +HALF on X and Z */
#define EDITOR_VIEWPORT_GRID_HALF 10u
#define EDITOR_VIEWPORT_GRID_THICKNESS 0.02f

struct BreakEditorViewport3D {
    RHIDevice *device; /* borrowed; NULL until the first live render */
    RHIOffscreenFBO fbo;
    u32 fbo_w, fbo_h;
    RHIPipeline pipeline;
    RHIPipelineBindings *bindings;
    RHIBuffer cube_vbo;
    i32 loc_mvp;
    i32 loc_color;
    int init_state; /* 0 = not attempted, 1 = ready, 2 = failed (sticky) */
    int screen_w, screen_h;

    BreakEditorShaderSource shader_source;
    BreakEditorShaderReload *shader_reload;
    BreakEditorShaderReloadLog shader_reload_log;
    void *shader_reload_log_user;

    const BreakEditorCamera *cam; /* borrowed (shell-owned) */
    BreakEditorGizmo *gizmo;      /* borrowed (shell-owned) */
    BreakEditorEntityId selected;
    const BreakEditorEntityId *extra; /* borrowed (shell) */
    u32 extra_count;

    /* render debugger: last render() call (CPU counters only) */
    int last_skip;
    u32 last_grid;
    u32 last_proxies, last_gizmo, last_draws, last_outline, last_ring,
        last_tinted;

    /* widget interaction state (one viewport widget per shell) */
    int drag_kind;
    f32 last_x, last_y;
    f32 box[4];   /* box select: press x/y, current x/y (viewport-local) */
    bool box_add; /* Ctrl held at press: add to the selection */
    bool grid_off; /* ground grid hidden (default: drawn) */
};

/* ---------------- creation / destruction ---------------- */

BreakEditorViewport3D *break_editor_viewport3d_create(void) {
    BreakEditorViewport3D *vp =
        (BreakEditorViewport3D *)calloc(1u, sizeof(BreakEditorViewport3D));
    if (vp != NULL) {
        vp->last_skip = BREAK_EDITOR_VIEWPORT3D_SKIP_NOT_RENDERED;
    }
    return vp;
}

bool break_editor_viewport3d_last_stats(const BreakEditorViewport3D *vp,
                                        BreakEditorViewport3DStats *out) {
    if (vp == NULL || out == NULL) {
        return false;
    }
    memset(out, 0, sizeof(*out));
    out->init_state = vp->init_state;
    out->skipped = vp->last_skip;
    if (rhi_handle_valid(vp->fbo.fb)) {
        out->fbo_w = vp->fbo_w;
        out->fbo_h = vp->fbo_h;
    }
    out->proxies = vp->last_proxies;
    out->gizmo_handles = vp->last_gizmo;
    out->outline_edges = vp->last_outline;
    out->ring_segments = vp->last_ring;
    out->grid_lines = vp->last_grid;
    out->tinted = vp->last_tinted;
    out->draws = vp->last_draws;
    return true;
}

const char *break_editor_viewport3d_skip_name(int skipped) {
    switch (skipped) {
    case BREAK_EDITOR_VIEWPORT3D_SKIP_NONE: return "none";
    case BREAK_EDITOR_VIEWPORT3D_SKIP_NOT_RENDERED: return "not-rendered";
    case BREAK_EDITOR_VIEWPORT3D_SKIP_NO_DEVICE: return "no-device";
    case BREAK_EDITOR_VIEWPORT3D_SKIP_PANEL_TOO_SMALL: return "panel-too-small";
    case BREAK_EDITOR_VIEWPORT3D_SKIP_NO_CAMERA: return "no-camera";
    case BREAK_EDITOR_VIEWPORT3D_SKIP_DEVICE_CHANGED: return "device-changed";
    case BREAK_EDITOR_VIEWPORT3D_SKIP_INIT_FAILED: return "init-failed";
    case BREAK_EDITOR_VIEWPORT3D_SKIP_FBO_FAILED: return "fbo-failed";
    default: return "unknown";
    }
}

bool break_editor_viewport3d_destroy(BreakEditorViewport3D *vp) {
    if (vp == NULL) {
        return true;
    }
    if (vp->shader_reload != NULL) {
        if (!break_editor_shader_reload_shutdown(vp->shader_reload)) {
            return false;
        }
        break_editor_shader_reload_destroy(vp->shader_reload);
        vp->shader_reload = NULL;
    }
    if (vp->device != NULL) {
        if (rhi_handle_valid(vp->fbo.fb)) {
            rhi_offscreen_fbo_destroy(vp->device, &vp->fbo);
        }
        if (rhi_handle_valid(vp->pipeline)) {
            rhi_pipeline_destroy(vp->device, vp->pipeline);
        }
        if (vp->bindings != NULL) {
            rhi_pipeline_bindings_destroy(vp->device, vp->bindings);
        }
        if (rhi_handle_valid(vp->cube_vbo)) {
            rhi_buffer_destroy(vp->device, vp->cube_vbo);
        }
    }
    free(vp);
    return true;
}

void break_editor_viewport3d_set_extra_selection(
    BreakEditorViewport3D *vp, const BreakEditorEntityId *ids, u32 count) {
    if (vp == NULL) return;
    vp->extra = count > 0u ? ids : NULL;
    vp->extra_count = ids != NULL ? count : 0u;
}

static bool vp_is_extra(const BreakEditorViewport3D *vp, BreakEditorEntityId id) {
    for (u32 i = 0u; i < vp->extra_count; i++) {
        if (break_editor_entity_id_eq(vp->extra[i], id)) return true;
    }
    return false;
}

void break_editor_viewport3d_set_view_state(BreakEditorViewport3D *vp,
                                            const BreakEditorCamera *cam,
                                            BreakEditorGizmo *gizmo,
                                            BreakEditorEntityId selected) {
    if (vp == NULL) {
        return;
    }
    vp->cam = cam;
    vp->gizmo = gizmo;
    vp->selected = selected;
}

void break_editor_viewport3d_set_screen_size(BreakEditorViewport3D *vp,
                                             int screen_w, int screen_h) {
    if (vp != NULL && screen_w > 0 && screen_h > 0) {
        vp->screen_w = screen_w;
        vp->screen_h = screen_h;
    }
}

RHITexture break_editor_viewport3d_color_texture(
    const BreakEditorViewport3D *vp) {
    if (vp == NULL || !rhi_handle_valid(vp->fbo.color_tex)) {
        return RHI_HANDLE_NULL;
    }
    return vp->fbo.color_tex;
}

/* ---------------- model matrix (pure CPU, headless-pinned) ---------------- */

void break_editor_viewport3d_model_matrix(const f32 pos[3],
                                          const f32 rot_deg[3],
                                          const f32 scale[3], f32 out16[16]) {
    /* M = T(pos) * R_y(rot.y) * R_x(rot.x) * R_z(rot.z) * S(scale), degrees
     * (header + plan convention). Column-major e[col][row], column-vector. */
    const f32 d = 3.14159265358979323846f / 180.0f;
    f32 rx = rot_deg[0] * d, ry = rot_deg[1] * d, rz = rot_deg[2] * d;
    f32 cx = cosf(rx), sx = sinf(rx);
    f32 cy = cosf(ry), sy = sinf(ry);
    f32 cz = cosf(rz), sz = sinf(rz);
    Mat4 my, mx, mz, s, t, m;
    memset(&my, 0, sizeof(my));
    memset(&mx, 0, sizeof(mx));
    memset(&mz, 0, sizeof(mz));
    /* R_y: x' = cy*x + sy*z; z' = -sy*x + cy*z */
    my.e[0][0] = cy;  my.e[0][2] = -sy;
    my.e[1][1] = 1.0f;
    my.e[2][0] = sy;  my.e[2][2] = cy;
    my.e[3][3] = 1.0f;
    /* R_x: y' = cx*y - sx*z; z' = sx*y + cx*z */
    mx.e[0][0] = 1.0f;
    mx.e[1][1] = cx;  mx.e[1][2] = sx;
    mx.e[2][1] = -sx; mx.e[2][2] = cx;
    mx.e[3][3] = 1.0f;
    /* R_z: x' = cz*x - sz*y; y' = sz*x + cz*y */
    mz.e[0][0] = cz;  mz.e[0][1] = sz;
    mz.e[1][0] = -sz; mz.e[1][1] = cz;
    mz.e[2][2] = 1.0f;
    mz.e[3][3] = 1.0f;
    s = mat4_scaling(scale[0], scale[1], scale[2]);
    t = mat4_translation(pos[0], pos[1], pos[2]);
    m = mat4_mul(my, mat4_mul(mx, mat4_mul(mz, s)));
    m = mat4_mul(t, m);
    memcpy(out16, m.e, sizeof(m.e));
}

u32 break_editor_viewport3d_outline_edges(const f32 model[16], f32 thickness,
                                          f32 out[12][16]) {
    Mat4 m;
    u32 n = 0u;
    if (model == NULL || out == NULL || !isfinite(thickness) ||
        !(thickness > 0.0f)) {
        return 0u;
    }
    memcpy(&m, model, sizeof(m));
    /* for each axis a: 4 edges at (+-0.5, +-0.5) on the other two axes */
    for (u32 a = 0u; a < 3u; a++) {
        u32 b = (a + 1u) % 3u, c = (a + 2u) % 3u;
        for (u32 q = 0u; q < 4u; q++) {
            f32 off[3] = {0.0f, 0.0f, 0.0f}, size[3];
            Mat4 local, world;
            off[b] = (q & 1u) ? 0.5f : -0.5f;
            off[c] = (q & 2u) ? 0.5f : -0.5f;
            size[a] = 1.0f + thickness;
            size[b] = thickness;
            size[c] = thickness;
            local = mat4_mul(mat4_translation(off[0], off[1], off[2]),
                             mat4_scaling(size[0], size[1], size[2]));
            world = mat4_mul(m, local);
            memcpy(out[n++], world.e, sizeof(world.e));
        }
    }
    return n;
}

u32 break_editor_viewport3d_grid_lines(f32 half_extent, f32 spacing,
                                       f32 thickness, f32 (*out)[16],
                                       u32 cap) {
    u32 n = 0u, per_axis;
    f32 len;
    if (out == NULL || cap == 0u || !isfinite(half_extent) ||
        !isfinite(spacing) || !isfinite(thickness) || !(half_extent > 0.0f) ||
        !(spacing > 0.0f) || !(thickness > 0.0f)) {
        return 0u;
    }
    per_axis = (u32)floorf(2.0f * half_extent / spacing + 1e-4f) + 1u;
    len = 2.0f * half_extent + thickness;
    for (u32 axis = 0u; axis < 2u; axis++) {
        for (u32 k = 0u; k < per_axis && n < cap; k++) {
            f32 at = -half_extent + (f32)k * spacing;
            Mat4 m = axis == 0u
                         ? mat4_mul(mat4_translation(0.0f, 0.0f, at),
                                    mat4_scaling(len, thickness, thickness))
                         : mat4_mul(mat4_translation(at, 0.0f, 0.0f),
                                    mat4_scaling(thickness, thickness, len));
            memcpy(out[n++], m.e, sizeof(m.e));
        }
    }
    return n;
}

void break_editor_viewport3d_set_grid(BreakEditorViewport3D *vp, bool on) {
    if (vp != NULL) {
        vp->grid_off = !on;
    }
}

/* ---------------- transactional GPU init / shader replacement ---------------- */

typedef struct {
    RHIPipeline pipeline;
    RHIPipelineBindings *bindings;
    RHIBuffer vbo;
    i32 loc_mvp, loc_color;
    bool owns_vbo;
} VpGpuCandidate;

static void vp_candidate_discard(RHIDevice *dev, VpGpuCandidate *candidate) {
    if (rhi_handle_valid(candidate->pipeline)) {
        rhi_pipeline_destroy(dev, candidate->pipeline);
    }
    if (candidate->bindings != NULL) {
        rhi_pipeline_bindings_destroy(dev, candidate->bindings);
    }
    if (candidate->owns_vbo && rhi_handle_valid(candidate->vbo)) {
        rhi_buffer_destroy(dev, candidate->vbo);
    }
}

static bool vp_candidate_build(BreakEditorViewport3D *vp,
                               VpGpuCandidate *candidate, const void *vert,
                               usize vert_size, const void *frag,
                               usize frag_size) {
    RHIDevice *dev = vp->device;
    RHIShader vs = RHI_HANDLE_NULL, fs = RHI_HANDLE_NULL;
    RHIPipelineDesc desc;
    RHIBufferDesc bdesc;
    memset(candidate, 0, sizeof(*candidate));
    candidate->loc_mvp = -1;
    candidate->loc_color = -1;
    if (vert == NULL || frag == NULL) {
        return false;
    }
    vs = rhi_shader_create(dev, (const char *)vert, vert_size, false);
    fs = rhi_shader_create(dev, (const char *)frag, frag_size, true);
    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        fprintf(stderr, "editor viewport3d: shader load failed\n");
        return false;
    }
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.vertex_stride = 12u; /* position-only vec3 (both backends) */
    desc.disable_culling = true;
    /* depth: default LESS + write on (the FBO bind clears depth to 1.0) */
    candidate->pipeline = rhi_pipeline_create(dev, &desc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    if (!rhi_handle_valid(candidate->pipeline)) {
        fprintf(stderr, "editor viewport3d: pipeline create failed\n");
        goto fail;
    }
    candidate->bindings = rhi_pipeline_bindings_create(dev, candidate->pipeline);
    if (candidate->bindings == NULL) {
        fprintf(stderr, "editor viewport3d: bindings create failed\n");
        goto fail;
    }
    candidate->loc_mvp = rhi_pipeline_bindings_resolve(candidate->bindings,
                                                        "u_mvp");
    candidate->loc_color = rhi_pipeline_bindings_resolve(candidate->bindings,
                                                          "u_color");
    if (candidate->loc_mvp < 0 || candidate->loc_color < 0) {
        fprintf(stderr, "editor viewport3d: uniform resolve failed\n");
        goto fail;
    }
    if (rhi_handle_valid(vp->cube_vbo)) {
        candidate->vbo = vp->cube_vbo;
    } else {
        memset(&bdesc, 0, sizeof(bdesc));
        bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
        bdesc.size = sizeof(k_cube_verts);
        bdesc.initial_data = k_cube_verts;
        candidate->vbo = rhi_buffer_create(dev, &bdesc);
        candidate->owns_vbo = true;
        if (!rhi_handle_valid(candidate->vbo)) {
            fprintf(stderr, "editor viewport3d: cube vbo create failed\n");
            goto fail;
        }
    }
    return true;

fail:
    vp_candidate_discard(dev, candidate);
    return false;
}

static void vp_candidate_publish(BreakEditorViewport3D *vp,
                                 VpGpuCandidate *candidate) {
    RHIPipeline old_pipeline = vp->pipeline;
    RHIPipelineBindings *old_bindings = vp->bindings;
    /* candidate->owns_vbo implies there was no live VBO to retire: the build
     * reuses an existing one and creates its own only when none exists */
    vp->pipeline = candidate->pipeline;
    vp->bindings = candidate->bindings;
    vp->loc_mvp = candidate->loc_mvp;
    vp->loc_color = candidate->loc_color;
    vp->cube_vbo = candidate->vbo;
    vp->init_state = BREAK_EDITOR_VIEWPORT3D_INIT_READY;
    if (rhi_handle_valid(old_pipeline)) {
        rhi_pipeline_destroy(vp->device, old_pipeline);
    }
    if (old_bindings != NULL) {
        rhi_pipeline_bindings_destroy(vp->device, old_bindings);
    }
}

bool break_editor_viewport3d_reload_shader_source(
    BreakEditorViewport3D *vp, const void *vert, usize vert_size,
    const void *frag, usize frag_size) {
    VpGpuCandidate candidate;
    if (vp == NULL || vp->device == NULL ||
        !vp_candidate_build(vp, &candidate, vert, vert_size, frag, frag_size)) {
        return false;
    }
    vp_candidate_publish(vp, &candidate);
    return true;
}

static bool vp_shader_reload_apply(void *user, const void *vert,
                                   usize vert_size, const void *frag,
                                   usize frag_size) {
    return break_editor_viewport3d_reload_shader_source(
        (BreakEditorViewport3D *)user, vert, vert_size, frag, frag_size);
}

void break_editor_viewport3d_set_shader_reload_logger(
    BreakEditorViewport3D *vp, BreakEditorShaderReloadLog log, void *user) {
    if (vp == NULL) {
        return;
    }
    vp->shader_reload_log = log;
    vp->shader_reload_log_user = user;
    break_editor_shader_reload_set_logger(vp->shader_reload, log, user);
}

void break_editor_viewport3d_tick(BreakEditorViewport3D *vp) {
    if (vp != NULL) {
        break_editor_shader_reload_tick(vp->shader_reload);
    }
}

bool break_editor_viewport3d_request_shader_reload(BreakEditorViewport3D *vp) {
    return vp != NULL &&
           break_editor_shader_reload_request(vp->shader_reload);
}

bool break_editor_viewport3d_shader_reload_stats(
    const BreakEditorViewport3D *vp, BreakEditorShaderReloadStats *out) {
    if (vp == NULL || out == NULL) {
        return false;
    }
    if (vp->shader_reload == NULL) {
        memset(out, 0, sizeof(*out));
        out->last_result = BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE;
        return true;
    }
    return break_editor_shader_reload_stats(vp->shader_reload, out);
}

bool break_editor_viewport3d_prepare(BreakEditorViewport3D *vp,
                                     void *rhi_device) {
    RHIDevice *dev = (RHIDevice *)rhi_device;
    RHICapabilities caps;
    BreakEditorShaderBytes vert, frag;
    bool ok;
    if (vp == NULL || dev == NULL) {
        return false;
    }
    if (vp->device != NULL && vp->device != dev) {
        return false;
    }
    if (vp->device == NULL) {
        vp->device = dev;
    }
    if (vp->init_state == BREAK_EDITOR_VIEWPORT3D_INIT_READY) {
        return true;
    }
    if (vp->init_state == BREAK_EDITOR_VIEWPORT3D_INIT_FAILED) {
        return false;
    }
    vp->init_state = BREAK_EDITOR_VIEWPORT3D_INIT_FAILED;
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !break_editor_shader_source_configure(
            &vp->shader_source, (RHIShaderVariant)caps.shader_variant)) {
        fprintf(stderr, "editor viewport3d: shader variant resolution failed\n");
        return false;
    }
    vp->shader_reload = break_editor_shader_reload_create(
        &vp->shader_source, vp_shader_reload_apply, vp);
    break_editor_shader_reload_set_logger(
        vp->shader_reload, vp->shader_reload_log, vp->shader_reload_log_user);
    memset(&vert, 0, sizeof(vert));
    memset(&frag, 0, sizeof(frag));
    if (!break_editor_shader_source_read(
            &vp->shader_source, BREAK_EDITOR_SHADER_VERTEX, &vert) ||
        !break_editor_shader_source_read(&vp->shader_source,
                                         BREAK_EDITOR_SHADER_FRAGMENT, &frag)) {
        break_editor_shader_source_destroy_bytes(&vert);
        break_editor_shader_source_destroy_bytes(&frag);
        fprintf(stderr, "editor viewport3d: shader source read failed (%s / %s)\n",
                break_editor_shader_source_path(
                    &vp->shader_source, BREAK_EDITOR_SHADER_VERTEX),
                break_editor_shader_source_path(
                    &vp->shader_source, BREAK_EDITOR_SHADER_FRAGMENT));
        return false;
    }
    {
        char *ev = NULL, *ef = NULL;
        usize evn = 0u, efn = 0u;
        char deps[BREAK_EDITOR_SHADER_MAX_DEPS][96];
        u32 nd = 0u;
        ok = break_editor_shader_source_expand(&vp->shader_source, vert.data,
                                               vert.size, &ev, &evn, deps,
                                               &nd);
        break_editor_shader_reload_watch_deps(vp->shader_reload,
                                              (const char (*)[96])deps, nd);
        if (ok) {
            ok = break_editor_shader_source_expand(&vp->shader_source,
                                                   frag.data, frag.size, &ef,
                                                   &efn, deps, &nd);
            break_editor_shader_reload_watch_deps(
                vp->shader_reload, (const char (*)[96])deps, nd);
        }
        if (ok) {
            ok = break_editor_viewport3d_reload_shader_source(vp, ev, evn,
                                                              ef, efn);
        } else {
            fprintf(stderr, "editor viewport3d: shader #include failed\n");
        }
        free(ev);
        free(ef);
    }
    break_editor_shader_source_destroy_bytes(&vert);
    break_editor_shader_source_destroy_bytes(&frag);
    return ok;
}

#ifdef BREAK_EDITOR_SHELL_TESTING
bool break_editor_viewport3d_replace_shader_reload_for_test(
    BreakEditorViewport3D *vp, BreakEditorShaderReload *reload) {
    if (vp == NULL) {
        return false;
    }
    if (vp->shader_reload == reload) {
        return true;
    }
    if (vp->shader_reload != NULL) {
        if (!break_editor_shader_reload_shutdown(vp->shader_reload)) {
            return false;
        }
        break_editor_shader_reload_destroy(vp->shader_reload);
    }
    vp->shader_reload = reload;
    return true;
}

void break_editor_viewport3d_set_shader_reload_shutdown_timeout_for_test(
    BreakEditorViewport3D *vp, u32 timeout_ms) {
    if (vp != NULL) {
        break_editor_shader_reload_set_shutdown_timeout_for_test(
            vp->shader_reload, timeout_ms);
    }
}

void break_editor_viewport3d_gpu_state_for_test(
    const BreakEditorViewport3D *vp, BreakEditorViewport3DGpuState *out) {
    if (out == NULL) {
        return;
    }
    memset(out, 0, sizeof(*out));
    if (vp == NULL) {
        return;
    }
    out->pipeline = vp->pipeline;
    out->bindings = vp->bindings;
    out->loc_mvp = vp->loc_mvp;
    out->loc_color = vp->loc_color;
    out->vbo = vp->cube_vbo;
}
#endif

static void vp_fbo_ensure(BreakEditorViewport3D *vp, u32 w, u32 h) {
    if (vp->fbo_w == w && vp->fbo_h == h && rhi_handle_valid(vp->fbo.fb)) {
        return; /* recreated on size change ONLY (plan bound) */
    }
    if (rhi_handle_valid(vp->fbo.fb)) {
        rhi_offscreen_fbo_destroy(vp->device, &vp->fbo);
    }
    vp->fbo = rhi_offscreen_fbo_create_fmt(vp->device, w, h,
                                           RHI_FORMAT_R8G8B8A8_UNORM);
    vp->fbo_w = w;
    vp->fbo_h = h;
    if (rhi_handle_valid(vp->fbo.fb)) {
        rhi_offscreen_fbo_set_clear_color(vp->device, &vp->fbo,
                                          EDITOR_VIEWPORT_CLEAR_R,
                                          EDITOR_VIEWPORT_CLEAR_G,
                                          EDITOR_VIEWPORT_CLEAR_B, 1.0f);
    }
}

/* ---------------- render ---------------- */

static void vp_draw_box(BreakEditorViewport3D *vp, RHICmdBuffer *cmd,
                        const Mat4 *view_proj, const f32 model[16],
                        const f32 color[4]) {
    Mat4 m, mvp;
    memcpy(&m, model, sizeof(m));
    mvp = mat4_mul(*view_proj, m);
    rhi_cmd_set_uniform_mat4(cmd, vp->loc_mvp, &mvp.e[0][0]);
    rhi_cmd_set_uniform_vec4(cmd, vp->loc_color, color[0], color[1], color[2],
                             color[3]);
    rhi_cmd_draw(cmd, 36u, 1u);
    vp->last_draws++;
}

static bool vp_entity_transform(const BreakEditorDoc *doc,
                                BreakEditorEntityId id, f32 pos[3],
                                f32 rot[3], f32 scale[3]) {
    u32 k;
    if (!break_editor_doc_has_component(doc, id,
                                        BREAK_EDITOR_COMPONENT_TRANSFORM)) {
        return false;
    }
    for (k = 0u; k < 9u; k++) {
        f32 *dst = k < 3u ? &pos[k] : (k < 6u ? &rot[k - 3u]
                                              : &scale[k - 6u]);
        if (!break_editor_doc_get_field_f32(
                doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, k, dst) ||
            !isfinite(*dst)) {
            return false;
        }
    }
    return true;
}

void break_editor_viewport3d_render(BreakEditorViewport3D *vp,
                                    BreakEditorDoc *doc, void *rhi_device,
                                    void *rhi_cmd, int panel_w,
                                    int panel_h) {
    RHIDevice *dev = (RHIDevice *)rhi_device;
    RHICmdBuffer *cmd = (RHICmdBuffer *)rhi_cmd;
    f32 view16[16], proj16[16];
    Mat4 view, proj, view_proj;
    usize total, i;

    if (vp == NULL) {
        return;
    }
    vp->last_proxies = vp->last_gizmo = vp->last_draws = vp->last_outline =
        vp->last_ring = vp->last_tinted = vp->last_grid = 0u;
    if (doc == NULL || dev == NULL || cmd == NULL) {
        vp->last_skip = BREAK_EDITOR_VIEWPORT3D_SKIP_NO_DEVICE;
        return;
    }
    if (panel_w < EDITOR_VIEWPORT_MIN_PANEL ||
        panel_h < EDITOR_VIEWPORT_MIN_PANEL) {
        vp->last_skip = BREAK_EDITOR_VIEWPORT3D_SKIP_PANEL_TOO_SMALL;
        return; /* plan bound: tiny panels skip the pass entirely */
    }
    if (vp->cam == NULL) {
        vp->last_skip = BREAK_EDITOR_VIEWPORT3D_SKIP_NO_CAMERA;
        return; /* view state not wired yet */
    }
    if (vp->device != NULL && vp->device != dev) {
        vp->last_skip = BREAK_EDITOR_VIEWPORT3D_SKIP_DEVICE_CHANGED;
        return; /* device swap is unsupported (documented, bounded) */
    }
    if (!break_editor_viewport3d_prepare(vp, dev)) {
        vp->last_skip = BREAK_EDITOR_VIEWPORT3D_SKIP_INIT_FAILED;
        return;
    }
    vp_fbo_ensure(vp, (u32)panel_w, (u32)panel_h);
    if (!rhi_handle_valid(vp->fbo.fb)) {
        vp->last_skip = BREAK_EDITOR_VIEWPORT3D_SKIP_FBO_FAILED;
        return;
    }
    vp->last_skip = BREAK_EDITOR_VIEWPORT3D_SKIP_NONE;

    /* Screen-constant gizmo sizing tracks the camera once per frame. */
    if (vp->gizmo != NULL) {
        break_editor_gizmo_set_view(vp->gizmo, vp->cam);
    }

    break_editor_camera_view(vp->cam, view16);
    break_editor_camera_proj(vp->cam, (f32)panel_w / (f32)panel_h, proj16);
    /* Texture orientation flip (header): the FBO bind viewport stores NDC
     * +Y at texture v=1 on both backends, while the blit samples v=0 at the
     * dst TOP edge — negate the projection Y scale so scene-up lands at
     * v=0. Render-side only; pick/gizmo math uses the un-negated matrices. */
    proj16[5] = -proj16[5]; /* e[1][1] */
    memcpy(&view, view16, sizeof(view));
    memcpy(&proj, proj16, sizeof(proj));
    view_proj = mat4_mul(proj, view);

    rhi_offscreen_fbo_bind(cmd, &vp->fbo); /* bind = clear (R617) */
    rhi_cmd_bind_pipeline(cmd, vp->pipeline);
    rhi_cmd_bind_vertex_buffer(cmd, vp->cube_vbo, 0u);

    /* Ground grid first, under everything (depth-tested like the proxies);
     * the lines through the origin take the X (red) / Z (blue) axis tint */
    if (!vp->grid_off) {
        static const f32 k_grid_color[4] = {0.30f, 0.31f, 0.34f, 1.0f};
        static const f32 k_grid_x[4] = {0.55f, 0.24f, 0.24f, 1.0f};
        static const f32 k_grid_z[4] = {0.24f, 0.33f, 0.60f, 1.0f};
        f32 lines[2u * (2u * EDITOR_VIEWPORT_GRID_HALF + 1u)][16];
        u32 nl = break_editor_viewport3d_grid_lines(
            (f32)EDITOR_VIEWPORT_GRID_HALF, 1.0f,
            EDITOR_VIEWPORT_GRID_THICKNESS, lines,
            (u32)(sizeof(lines) / sizeof(lines[0])));
        for (u32 g = 0u; g < nl; g++) {
            const f32 *color = k_grid_color;
            if (g == EDITOR_VIEWPORT_GRID_HALF) {
                color = k_grid_x; /* along X through z = 0 */
            } else if (g == 3u * EDITOR_VIEWPORT_GRID_HALF + 1u) {
                color = k_grid_z; /* along Z through x = 0 */
            }
            vp_draw_box(vp, cmd, &view_proj, lines[g], color);
        }
        vp->last_grid = nl;
    }

    /* Entity proxies: one unit cube per entity with an EditorTransform. */
    total = break_editor_doc_entity_count(doc);
    if (total > EDITOR_VIEWPORT_MAX_DRAW) {
        total = EDITOR_VIEWPORT_MAX_DRAW; /* bounded */
    }
    for (i = 0u; i < total; i++) {
        BreakEditorEntityId id;
        const char *name = NULL;
        f32 pos[3], rot[3], scale[3], model[16];
        if (!break_editor_doc_entity_at(doc, i, &id, &name)) {
            continue;
        }
        if (!vp_entity_transform(doc, id, pos, rot, scale)) {
            continue;
        }
        break_editor_viewport3d_model_matrix(pos, rot, scale, model);
        vp->last_proxies++;
        if (break_editor_entity_id_eq(id, vp->selected)) {
            f32 edges[12][16];
            u32 ne = break_editor_viewport3d_outline_edges(
                model, EDITOR_VIEWPORT_OUTLINE_THICKNESS, edges);
            vp_draw_box(vp, cmd, &view_proj, model, k_selected_color);
            for (u32 e = 0u; e < ne; e++) {
                vp_draw_box(vp, cmd, &view_proj, edges[e], k_outline_color);
            }
            vp->last_outline = ne;
            vp->last_tinted++;
        } else if (vp_is_extra(vp, id)) {
            vp_draw_box(vp, cmd, &view_proj, model, k_selected_color);
            vp->last_tinted++;
        } else {
            vp_draw_box(vp, cmd, &view_proj, model, k_proxy_color);
        }
    }

    /* Gizmo handles on top of the proxies (depth cleared first). */
    if (vp->gizmo != NULL) {
        BreakEditorGizmoHandle handles[BREAK_EDITOR_GIZMO_MAX_HANDLES];
        usize n = break_editor_gizmo_handles(vp->gizmo, handles,
                                             BREAK_EDITOR_GIZMO_MAX_HANDLES);
        usize h;
        if (n > 0u) {
            rhi_cmd_clear_depth(cmd);
        }
        for (h = 0u; h < n; h++) {
            const BreakEditorGizmoHandle *gh = &handles[h];
            f32 model[16];
            f32 center[3], extent[3];
            int part = (int)gh->part;
            u32 k;
            const f32 *color;
            if (part < 0 || part > 4) {
                continue;
            }
            for (k = 0u; k < 3u; k++) {
                center[k] = 0.5f * (gh->aabb_min[k] + gh->aabb_max[k]);
                extent[k] = gh->aabb_max[k] - gh->aabb_min[k];
                if (!isfinite(center[k]) || !isfinite(extent[k]) ||
                    extent[k] <= 0.0f) {
                    break;
                }
            }
            if (k < 3u) {
                continue;
            }
            color = k_gizmo_colors[part];
            vp->last_gizmo++;
            {
                static const f32 zero_rot[3] = {0.0f, 0.0f, 0.0f};
                break_editor_viewport3d_model_matrix(center, zero_rot, extent,
                                                     model);
            }
            vp_draw_box(vp, cmd, &view_proj, model, color);
        }
        /* rotate mode: one ring of small cubes per axis (visual only; the
         * handles above stay the hit targets) */
        {
            BreakEditorGizmoRingSeg ring[3u * EDITOR_VIEWPORT_RING_SEGMENTS];
            usize nr = break_editor_gizmo_rings(
                vp->gizmo, EDITOR_VIEWPORT_RING_SEGMENTS, ring,
                3u * EDITOR_VIEWPORT_RING_SEGMENTS);
            for (usize r = 0u; r < nr; r++) {
                static const f32 zero_rot[3] = {0.0f, 0.0f, 0.0f};
                f32 ext[3], model[16];
                ext[0] = ext[1] = ext[2] = 2.0f * ring[r].half_size;
                break_editor_viewport3d_model_matrix(ring[r].center, zero_rot,
                                                     ext, model);
                vp_draw_box(vp, cmd, &view_proj, model,
                            k_gizmo_colors[1u + ring[r].axis]);
            }
            vp->last_ring = (u32)nr;
        }
    }

    rhi_offscreen_fbo_unbind(cmd, vp->screen_w > 0 ? vp->screen_w : panel_w,
                             vp->screen_h > 0 ? vp->screen_h : panel_h);
}

/* ---------------- viewport panel widget ---------------- */

static void viewport_on_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
    BreakEditorShell *shell;
    BreakEditorViewport3D *vp;
    RHITexture tex;
    if (widget == NULL || vg == NULL) {
        return;
    }
    /* Placeholder so the panel is never a transparent hole (also the only
     * paint on the dummy-PAL path, where no FBO exists). */
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_content_bg()));
    (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){0.0f, 0.0f,
                                                  (float)widget->rect.w,
                                                  (float)widget->rect.h});
    shell = (BreakEditorShell *)my_widget_get_user_data(widget);
    vp = shell != NULL ? break_editor_shell_viewport3d(shell) : NULL;
    tex = break_editor_viewport3d_color_texture(vp);
    if (rhi_handle_valid(tex)) {
        /* Foreign canvas (dummy-PAL LCD): the blit rejects it bounded. */
        (void)my_vgcanvas_break_rhi_blit_texture(
            vg, tex, 0.0f, 0.0f, (float)widget->rect.w,
            (float)widget->rect.h);
    }
    if (shell != NULL) {
        const char *line = break_editor_shell_viewport_overlay_text(shell);
        int32_t tw = 0, th = 0;
        if (line[0] != '\0') {
            my_vgcanvas_set_font(vg, NULL, 12);
            if (my_vgcanvas_measure_text(vg, line, &tw, &th) == MY_RET_OK) {
                my_vgcanvas_set_fill_color(vg,
                                           my_color_from_rgba32(0x000000A0u));
                (void)my_vgcanvas_fill_rect(
                    vg, &(my_rectf_t){4.0f, 4.0f, (float)tw + 12.0f,
                                      (float)th + 6.0f});
                my_vgcanvas_set_fill_color(
                    vg, my_color_from_rgba32(BREAK_EDITOR_THEME_TEXT));
                (void)my_vgcanvas_draw_text(vg, line, 10.0f, 7.0f);
            }
        }
    }
    {
        f32 r[4];
        if (break_editor_viewport3d_box_rect(vp, r)) {
            float x0 = r[0] < r[2] ? r[0] : r[2];
            float y0 = r[1] < r[3] ? r[1] : r[3];
            float bw = fabsf(r[2] - r[0]), bh = fabsf(r[3] - r[1]);
            u32 accent = BREAK_EDITOR_THEME_ACCENT;
            my_vgcanvas_set_fill_color(
                vg, my_color_from_rgba32((accent & 0xffffff00u) | 0x30u));
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x0, y0, bw, bh});
            my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(accent));
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x0, y0, bw, 1.0f});
            (void)my_vgcanvas_fill_rect(
                vg, &(my_rectf_t){x0, y0 + bh - 1.0f, bw, 1.0f});
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x0, y0, 1.0f, bh});
            (void)my_vgcanvas_fill_rect(
                vg, &(my_rectf_t){x0 + bw - 1.0f, y0, 1.0f, bh});
        }
    }
}

bool break_editor_viewport3d_box_rect(const BreakEditorViewport3D *vp,
                                      f32 out4[4]) {
    if (vp == NULL || vp->drag_kind != VP_DRAG_BOX) {
        return false;
    }
    if (out4 != NULL) {
        memcpy(out4, vp->box, sizeof(vp->box));
    }
    return true;
}

static void viewport_end_interaction(my_widget_t *widget,
                                     BreakEditorShell *shell,
                                     BreakEditorViewport3D *vp) {
    if (vp->drag_kind == VP_DRAG_GIZMO &&
        break_editor_shell_gizmo(shell) != NULL) {
        break_editor_gizmo_end_drag(break_editor_shell_gizmo(shell));
        break_editor_shell_refresh(shell); /* status last= tracks the drag */
    } else if (vp->drag_kind == VP_DRAG_ORBIT) {
        break_editor_shell_set_flying(shell, false);
    } else if (vp->drag_kind == VP_DRAG_BOX && vp->cam != NULL) {
        BreakEditorEntityId ids[EDITOR_VIEWPORT_BOX_MAX];
        u32 n = break_editor_viewport_box_select(
            break_editor_shell_doc(shell), break_editor_shell_camera(shell),
            vp->box[0], vp->box[1], vp->box[2], vp->box[3],
            (f32)widget->rect.w, (f32)widget->rect.h, ids,
            EDITOR_VIEWPORT_BOX_MAX);
        vp->drag_kind = VP_DRAG_NONE;
        (void)break_editor_shell_select_ids(shell, ids, n, vp->box_add);
    }
    vp->drag_kind = VP_DRAG_NONE;
    my_widget_invalidate(widget, NULL);
}

static my_ret_t viewport_on_event(my_widget_t *widget,
                                  const my_event_t *event) {
    BreakEditorShell *shell;
    BreakEditorViewport3D *vp;
    BreakEditorCamera *cam;
    BreakEditorGizmo *gizmo;
    f32 lx, ly, w, h;
    int32_t gx, gy;
    if (widget == NULL || event == NULL) {
        return MY_RET_INVALID_PARAMS;
    }
    shell = (BreakEditorShell *)my_widget_get_user_data(widget);
    if (shell == NULL) {
        return MY_RET_FAIL;
    }
    vp = break_editor_shell_viewport3d(shell);
    cam = break_editor_shell_camera(shell);
    gizmo = break_editor_shell_gizmo(shell);
    if (vp == NULL || cam == NULL) {
        return MY_RET_FAIL;
    }
    gx = event->u.pointer.x;
    gy = event->u.pointer.y;
    my_widget_global_to_local(widget, &gx, &gy);
    lx = (f32)gx;
    ly = (f32)gy;
    w = (f32)widget->rect.w;
    h = (f32)widget->rect.h;
    if (!(w > 0.0f) || !(h > 0.0f)) {
        return MY_RET_FAIL;
    }

    switch (event->type) {
    case MY_EVENT_POINTER_DOWN: {
        u8 button = event->u.pointer.button;
        u8 mods = event->u.pointer.modifiers;
        /* a second button during a gizmo drag: commit that drag first, or
         * the switch below would orphan it uncommitted (§10 item 1) */
        if (vp->drag_kind == VP_DRAG_GIZMO && gizmo != NULL) {
            break_editor_gizmo_end_drag(gizmo);
            break_editor_shell_refresh(shell);
        }
        vp->last_x = lx;
        vp->last_y = ly;
        if (vp->drag_kind == VP_DRAG_ORBIT) {
            break_editor_shell_set_flying(shell, false);
        }
        vp->drag_kind = VP_DRAG_NONE;
        if (button == 2u || (button == 1u &&
                             (mods & MY_KEYMOD_SHIFT) != 0u)) {
            vp->drag_kind = VP_DRAG_PAN;
        } else if (button == 3u ||
                   (button == 1u && (mods & MY_KEYMOD_ALT) != 0u)) {
            vp->drag_kind = VP_DRAG_ORBIT;
            /* right button: look around and fly with WASD/QE */
            break_editor_shell_set_flying(shell, button == 3u);
        } else if (button == 1u) {
            if (gizmo != NULL &&
                break_editor_gizmo_begin_drag(gizmo, cam, lx, ly, w, h)) {
                vp->drag_kind = VP_DRAG_GIZMO;
            } else if (gizmo != NULL &&
                       break_editor_gizmo_hit(gizmo, cam, lx, ly, w, h) !=
                           BREAK_EDITOR_GIZMO_PART_NONE) {
                /* Over a handle but the drag grab failed (degenerate ray /
                 * bounded false): keep the selection — the pointer was
                 * clearly aimed at the gizmo, not at empty space. */
            } else {
                /* pick -> select; a miss clears the selection */
                BreakEditorPickResult pick;
                if (break_editor_viewport_pick(break_editor_shell_doc(shell),
                                               cam, lx, ly, w, h, &pick)) {
                    (void)break_editor_shell_select_id(shell, pick.id);
                } else {
                    /* empty space: maybe the start of a box select; a plain
                     * press clears, Ctrl keeps the selection to add to */
                    vp->drag_kind = VP_DRAG_BOX_PENDING;
                    vp->box_add = (mods & MY_KEYMOD_CTRL) != 0u;
                    vp->box[0] = vp->box[2] = lx;
                    vp->box[1] = vp->box[3] = ly;
                    if (!vp->box_add) {
                        (void)break_editor_shell_select_id(
                            shell, BREAK_EDITOR_ENTITY_NULL);
                    }
                }
            }
        }
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
    }
    case MY_EVENT_POINTER_MOVE: {
        f32 dx = lx - vp->last_x;
        f32 dy = ly - vp->last_y;
        vp->last_x = lx;
        vp->last_y = ly;
        if (vp->drag_kind == VP_DRAG_GIZMO) {
            if (gizmo == NULL ||
                !break_editor_gizmo_drag(gizmo, cam, lx, ly, w, h)) {
                /* external commit (mid-drag Ctrl+Z policy) ended the drag:
                 * drop the widget state so further moves are inert */
                vp->drag_kind = VP_DRAG_NONE;
            }
        } else if (vp->drag_kind == VP_DRAG_ORBIT) {
            break_editor_camera_orbit(cam,
                                      dx * EDITOR_VIEWPORT_ORBIT_DEG_PER_PX,
                                      dy * EDITOR_VIEWPORT_ORBIT_DEG_PER_PX);
        } else if (vp->drag_kind == VP_DRAG_BOX_PENDING ||
                   vp->drag_kind == VP_DRAG_BOX) {
            vp->box[2] = lx;
            vp->box[3] = ly;
            if (vp->drag_kind == VP_DRAG_BOX_PENDING &&
                (fabsf(lx - vp->box[0]) > EDITOR_VIEWPORT_BOX_THRESHOLD ||
                 fabsf(ly - vp->box[1]) > EDITOR_VIEWPORT_BOX_THRESHOLD)) {
                vp->drag_kind = VP_DRAG_BOX;
            }
        } else if (vp->drag_kind == VP_DRAG_PAN) {
            /* rescale so one dragged logical pixel moves one screen pixel
             * at the pivot plane for the CURRENT widget height */
            f32 s = EDITOR_VIEWPORT_PAN_REF_H / h;
            break_editor_camera_pan(cam, dx * s, dy * s);
        } else {
            return MY_RET_NOT_SUPPORTED; /* hover move: not consumed */
        }
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
    }
    case MY_EVENT_POINTER_UP:
        viewport_end_interaction(widget, shell, vp);
        return MY_RET_OK;
    case MY_EVENT_POINTER_WHEEL:
        break_editor_camera_zoom(cam, (f32)event->u.pointer.delta);
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
    default:
        return MY_RET_NOT_SUPPORTED;
    }
}

static const my_widget_vtable_t s_viewport_vtable = {
    viewport_on_paint, viewport_on_event, NULL, NULL};

my_widget_t *break_editor_viewport3d_widget_create(BreakEditorShell *shell) {
    my_widget_t *widget = my_widget_create(NULL, "editor-viewport");
    if (widget == NULL) {
        return NULL;
    }
    if (my_widget_subclass_init(widget, &s_viewport_vtable) != MY_RET_OK) {
        my_widget_unref(widget);
        return NULL;
    }
    (void)my_widget_set_user_data(widget, shell);
    return widget;
}
