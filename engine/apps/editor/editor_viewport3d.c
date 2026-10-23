/* BreakEditorViewport3D implementation — see editor_viewport3d.h for the
 * contract (lazy GPU lifecycle, frame ordering, texture-orientation flip,
 * model-matrix convention, minimal selection highlight, ownership).
 *
 * Pointer routing (viewport widget on_event; coordinates are viewport-local
 * logical px — the dispatcher delivers global coords, converted with
 * my_widget_global_to_local):
 *   left press            gizmo begin_drag when a handle is hit; otherwise
 *                         pick -> select (hit) / clear selection (miss)
 *   left drag (gizmo)     break_editor_gizmo_drag; a false return mid-drag
 *                         means the drag vanished (external Ctrl+Z commit —
 *                         the documented Task 3 policy) and the widget drops
 *                         its drag state (self-healing; the up is a no-op)
 *   right / alt-left drag orbit (EDITOR_VIEWPORT_ORBIT_DEG_PER_PX per px)
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <core/shader_io.h>
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
    VP_DRAG_PAN
};

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

    const BreakEditorCamera *cam; /* borrowed (shell-owned) */
    BreakEditorGizmo *gizmo;      /* borrowed (shell-owned) */
    BreakEditorEntityId selected;

    /* widget interaction state (one viewport widget per shell) */
    int drag_kind;
    f32 last_x, last_y;
};

/* ---------------- creation / destruction ---------------- */

BreakEditorViewport3D *break_editor_viewport3d_create(void) {
    return (BreakEditorViewport3D *)calloc(1u, sizeof(BreakEditorViewport3D));
}

void break_editor_viewport3d_destroy(BreakEditorViewport3D *vp) {
    if (vp == NULL) {
        return;
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

/* ---------------- lazy GPU init ---------------- */

/* Shader source lookup honoring BREAK_SHADER_DIR, then the engine-relative
 * prefixes (the myui_break.c break_ui_read_shader precedent). */
static char *vp_read_shader(const char *path, usize *out_len) {
    static const char *const prefixes[] = {"", "engine/", "../engine/",
                                           "../../engine/"};
    const char *env = getenv("BREAK_SHADER_DIR");
    size_t i;
    if (env != NULL && env[0] != '\0') {
        char buf[1024];
        char *src;
        snprintf(buf, sizeof(buf), "%s/%s", env, path);
        src = shader_read_file(buf, out_len);
        if (src != NULL) {
            return src;
        }
    }
    for (i = 0u; i < sizeof(prefixes) / sizeof(prefixes[0]); i++) {
        char buf[1024];
        char *src;
        snprintf(buf, sizeof(buf), "%s%s", prefixes[i], path);
        src = shader_read_file(buf, out_len);
        if (src != NULL) {
            return src;
        }
    }
    return NULL;
}

static RHIShader vp_load_shader(RHIDevice *dev, const char *path,
                                bool fragment) {
    usize len = 0u;
    char *src = vp_read_shader(path, &len);
    RHIShader shader;
    if (src == NULL) {
        return RHI_HANDLE_NULL;
    }
    shader = rhi_shader_create(dev, src, len, fragment);
    free(src);
    return shader;
}

/* Bounded one-shot init; failures are sticky (init_state = 2, logged once)
 * so a missing shader never spams per frame. */
static bool vp_lazy_init(BreakEditorViewport3D *vp, RHIDevice *dev) {
    RHICapabilities caps;
    char vert_path[96], frag_path[96];
    RHIShader vs, fs;
    RHIPipelineDesc desc;
    RHIBufferDesc bdesc;
    if (vp->init_state == 1) {
        return true;
    }
    if (vp->init_state == 2) {
        return false;
    }
    vp->init_state = 2; /* flipped to 1 only on full success */

    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/editor_color.vert",
                             (RHIShaderVariant)caps.shader_variant, vert_path,
                             sizeof(vert_path)) ||
        !shader_variant_path("shaders/editor_color.frag",
                             (RHIShaderVariant)caps.shader_variant, frag_path,
                             sizeof(frag_path))) {
        fprintf(stderr, "editor viewport3d: shader variant resolution failed\n");
        return false;
    }
    vs = vp_load_shader(dev, vert_path, false);
    fs = vp_load_shader(dev, frag_path, true);
    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        fprintf(stderr, "editor viewport3d: shader load failed (%s / %s)\n",
                vert_path, frag_path);
        return false;
    }
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.vertex_stride = 12u; /* position-only vec3 (both backends) */
    desc.disable_culling = true;
    /* depth: default LESS + write on (the FBO bind clears depth to 1.0) */
    vp->pipeline = rhi_pipeline_create(dev, &desc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    if (!rhi_handle_valid(vp->pipeline)) {
        fprintf(stderr, "editor viewport3d: pipeline create failed\n");
        return false;
    }
    vp->bindings = rhi_pipeline_bindings_create(dev, vp->pipeline);
    if (vp->bindings == NULL) {
        fprintf(stderr, "editor viewport3d: bindings create failed\n");
        return false;
    }
    vp->loc_mvp = rhi_pipeline_bindings_resolve(vp->bindings, "u_mvp");
    vp->loc_color = rhi_pipeline_bindings_resolve(vp->bindings, "u_color");
    if (vp->loc_mvp < 0 || vp->loc_color < 0) {
        fprintf(stderr, "editor viewport3d: uniform resolve failed\n");
        return false;
    }
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = sizeof(k_cube_verts);
    bdesc.initial_data = k_cube_verts;
    vp->cube_vbo = rhi_buffer_create(dev, &bdesc);
    if (!rhi_handle_valid(vp->cube_vbo)) {
        fprintf(stderr, "editor viewport3d: cube vbo create failed\n");
        return false;
    }
    vp->device = dev;
    vp->init_state = 1;
    return true;
}

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

    if (vp == NULL || doc == NULL || dev == NULL || cmd == NULL) {
        return;
    }
    if (panel_w < EDITOR_VIEWPORT_MIN_PANEL ||
        panel_h < EDITOR_VIEWPORT_MIN_PANEL) {
        return; /* plan bound: tiny panels skip the pass entirely */
    }
    if (vp->cam == NULL) {
        return; /* view state not wired yet */
    }
    if (vp->device != NULL && vp->device != dev) {
        return; /* device swap is unsupported (documented, bounded) */
    }
    if (!vp_lazy_init(vp, dev)) {
        return;
    }
    vp_fbo_ensure(vp, (u32)panel_w, (u32)panel_h);
    if (!rhi_handle_valid(vp->fbo.fb)) {
        return;
    }

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
        vp_draw_box(vp, cmd, &view_proj, model,
                    break_editor_entity_id_eq(id, vp->selected)
                        ? k_selected_color
                        : k_proxy_color);
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
            {
                static const f32 zero_rot[3] = {0.0f, 0.0f, 0.0f};
                break_editor_viewport3d_model_matrix(center, zero_rot, extent,
                                                     model);
            }
            vp_draw_box(vp, cmd, &view_proj, model, color);
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
    my_vgcanvas_set_fill_color(vg, my_color_rgba(30u, 31u, 34u, 255u));
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
}

static void viewport_end_interaction(my_widget_t *widget,
                                     BreakEditorShell *shell,
                                     BreakEditorViewport3D *vp) {
    if (vp->drag_kind == VP_DRAG_GIZMO &&
        break_editor_shell_gizmo(shell) != NULL) {
        break_editor_gizmo_end_drag(break_editor_shell_gizmo(shell));
        break_editor_shell_refresh(shell); /* status last= tracks the drag */
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
        vp->last_x = lx;
        vp->last_y = ly;
        vp->drag_kind = VP_DRAG_NONE;
        if (button == 2u || (button == 1u &&
                             (mods & MY_KEYMOD_SHIFT) != 0u)) {
            vp->drag_kind = VP_DRAG_PAN;
        } else if (button == 3u ||
                   (button == 1u && (mods & MY_KEYMOD_ALT) != 0u)) {
            vp->drag_kind = VP_DRAG_ORBIT;
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
                    (void)break_editor_shell_select_id(
                        shell, BREAK_EDITOR_ENTITY_NULL);
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
