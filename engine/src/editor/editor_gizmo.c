/* Editor transform gizmo state machine implementation — see
 * editor_gizmo.h for the contract (handle formula, drag math, undo
 * semantics, mid-drag policy, bounded/degenerate behavior).
 *
 * The whole drag is ONE undoable command: begin_drag allocates a
 * BreakEditorGizmoCmd (multi-field: up to 3 f32 field offsets with old/new
 * byte snapshots, same construction pattern as the Phase 1 component
 * commands in editor_components.c) and snapshots the old bytes; drag()
 * writes new values live through break_editor_doc_component_bytes (the
 * in-progress command owns the mutation — the undo stack is not touched
 * per pointer move); end_drag captures the final bytes and pushes the
 * command as already-applied via break_editor_cmd_stack_push_applied
 * (which never allocates, so end_drag commits even under an exhausted
 * budget — pinned by the OOM sweep test). A bitwise-identical final state
 * records no command, matching set_field_f32's no-op rule.
 */

#include <editor/editor_gizmo.h>

#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EG_PI_F 3.14159265358979323846f

/* ---- command object (one per drag) ---- */

typedef struct {
    BreakEditorCmd base;            /* MUST be the first member */
    u32 component_id;               /* BREAK_EDITOR_COMPONENT_TRANSFORM */
    u32 field_count;                /* <= 3 (0: ROTATE CENTER no-op drag) */
    u32 field_offset[3];            /* byte offsets within the component */
    u32 old_bits[3];                /* begin_drag snapshot */
    u32 new_bits[3];                /* end_drag snapshot */
    char mode_name[12];             /* describe: "translate"/"rotate"/"scale" */
    char part_name[8];              /* describe: "x"/"y"/"z"/"center" */
} BreakEditorGizmoCmd;

struct BreakEditorGizmo {
    BreakEditorDoc *doc;            /* borrowed; NULL = detached */
    BreakEditorEntityId id;
    BreakEditorGizmoMode mode;
    f32 scale_base;                 /* cached |eye - pivot| * tan(fov_y/2) */
    /* drag state (dragging == false: the rest is dead) */
    bool dragging;
    BreakEditorGizmoPart drag_part;
    BreakEditorGizmoCmd *cmd;       /* in-progress command (owns mutation) */
    f32 pivot0[3];                  /* begin-drag pivot (drag math anchor) */
    f32 begin_pos[3];
    f32 begin_rot[3];
    f32 begin_scale[3];
    f32 grab_s0;                    /* axis parameter at begin (translate/scale) */
    f32 plane_p0[3];                /* plane grab point at begin (CENTER) */
    f32 drag_x0;                    /* begin x pixel (rotate, CENTER scale) */
};

/* ---- small math helpers ---- */

static int eg_part_axis(BreakEditorGizmoPart part) {
    return (part >= BREAK_EDITOR_GIZMO_PART_X &&
            part <= BREAK_EDITOR_GIZMO_PART_Z)
               ? (int)(part - BREAK_EDITOR_GIZMO_PART_X)
               : -1;
}

/* Camera model of editor_viewport.h (duplicated locally — the eye formula
 * is pinned there): eye = target + R(yaw,pitch) * (0,0,distance). */
static void eg_camera_eye(const BreakEditorCamera *cam, f32 out_eye[3]) {
    f32 cp = cosf(cam->pitch), sp = sinf(cam->pitch);
    f32 cy = cosf(cam->yaw),   sy = sinf(cam->yaw);
    out_eye[0] = cam->target[0] + cam->distance * cp * sy;
    out_eye[1] = cam->target[1] + cam->distance * sp;
    out_eye[2] = cam->target[2] + cam->distance * cp * cy;
}

static bool eg_camera_sane(const BreakEditorCamera *cam) {
    return isfinite(cam->target[0]) && isfinite(cam->target[1]) &&
           isfinite(cam->target[2]) && isfinite(cam->yaw) &&
           isfinite(cam->pitch) && isfinite(cam->distance) &&
           isfinite(cam->fov_y) && cam->fov_y > 0.0f &&
           cam->fov_y < EG_PI_F && cam->distance > 0.0f;
}

/* Pivot = the attached entity's pos (transform fields 0..2). Bounded false
 * when detached, the entity/transform is gone, or pos is non-finite. */
static bool eg_pivot(const BreakEditorGizmo *g, f32 out[3]) {
    for (u32 k = 0; k < 3; k++) {
        if (!break_editor_doc_get_field_f32(
                g->doc, g->id, BREAK_EDITOR_COMPONENT_TRANSFORM, k,
                &out[k])) {
            return false;
        }
    }
    return isfinite(out[0]) && isfinite(out[1]) && isfinite(out[2]);
}

/* Refresh the screen-constant sizing cache (header contract). Failure
 * leaves the previous value untouched. */
static void eg_refresh_scale(BreakEditorGizmo *g,
                             const BreakEditorCamera *cam) {
    if (!g->doc || !cam || !eg_camera_sane(cam)) return;
    f32 pivot[3];
    if (!eg_pivot(g, pivot)) return;
    f32 eye[3];
    eg_camera_eye(cam, eye);
    f32 dx = eye[0] - pivot[0], dy = eye[1] - pivot[1],
        dz = eye[2] - pivot[2];
    f32 dist = sqrtf(dx * dx + dy * dy + dz * dz);
    f32 t = tanf(cam->fov_y * 0.5f);
    f32 sb = dist * t;
    if (!isfinite(sb) || !(sb > 0.0f)) return;
    g->scale_base = sb;
}

/* The pinned handle layout (editor_gizmo.h): 4 world-axis-aligned AABBs in
 * the order X, Y, Z, CENTER. */
static void eg_build_handles(const f32 pivot[3], f32 scale_base,
                             BreakEditorGizmoHandle out[4]) {
    f32 gap = BREAK_EDITOR_GIZMO_AXIS_GAP_SCALE * scale_base;
    f32 len = BREAK_EDITOR_GIZMO_AXIS_LEN_SCALE * scale_base;
    f32 th = BREAK_EDITOR_GIZMO_AXIS_THICK_SCALE * scale_base;
    f32 ch = BREAK_EDITOR_GIZMO_CENTER_HALF_SCALE * scale_base;
    for (int k = 0; k < 3; k++) {
        BreakEditorGizmoHandle *h = &out[k];
        h->part = (BreakEditorGizmoPart)(BREAK_EDITOR_GIZMO_PART_X + k);
        for (int j = 0; j < 3; j++) {
            h->aabb_min[j] = pivot[j] - th;
            h->aabb_max[j] = pivot[j] + th;
        }
        h->aabb_min[k] = pivot[k] + gap;
        h->aabb_max[k] = pivot[k] + gap + len;
    }
    out[3].part = BREAK_EDITOR_GIZMO_PART_CENTER;
    for (int j = 0; j < 3; j++) {
        out[3].aabb_min[j] = pivot[j] - ch;
        out[3].aabb_max[j] = pivot[j] + ch;
    }
}

/* Slab ray-AABB test (rd need not be normalized; t is in rd units). A box
 * containing the ray origin reports t = 0. */
static bool eg_ray_aabb(const f32 ro[3], const f32 rd[3], const f32 bmin[3],
                        const f32 bmax[3], f32 *out_t) {
    f32 tmin = 0.0f;
    f32 tmax = FLT_MAX;
    for (int k = 0; k < 3; k++) {
        if (fabsf(rd[k]) < 1e-20f) {
            if (ro[k] < bmin[k] || ro[k] > bmax[k]) return false;
            continue;
        }
        f32 inv = 1.0f / rd[k];
        f32 t0 = (bmin[k] - ro[k]) * inv;
        f32 t1 = (bmax[k] - ro[k]) * inv;
        if (t0 > t1) {
            f32 tmp = t0;
            t0 = t1;
            t1 = tmp;
        }
        if (t0 > tmin) tmin = t0;
        if (t1 < tmax) tmax = t1;
        if (tmin > tmax) return false;
    }
    *out_t = tmin;
    return true;
}

static BreakEditorGizmoPart eg_hit_impl(const BreakEditorGizmo *g,
                                        const BreakEditorCamera *cam,
                                        f32 x, f32 y, f32 w, f32 h) {
    if (!g->doc || g->mode == BREAK_EDITOR_GIZMO_NONE) {
        return BREAK_EDITOR_GIZMO_PART_NONE;
    }
    f32 pivot[3];
    if (!eg_pivot(g, pivot)) return BREAK_EDITOR_GIZMO_PART_NONE;
    f32 ro[3], rd[3];
    if (!break_editor_viewport_screen_ray(cam, x, y, w, h, ro, rd)) {
        return BREAK_EDITOR_GIZMO_PART_NONE;
    }
    BreakEditorGizmoHandle hs[4];
    eg_build_handles(pivot, g->scale_base, hs);
    f32 best = FLT_MAX;
    BreakEditorGizmoPart part = BREAK_EDITOR_GIZMO_PART_NONE;
    for (int i = 0; i < 4; i++) {
        f32 t;
        if (eg_ray_aabb(ro, rd, hs[i].aabb_min, hs[i].aabb_max, &t) &&
            t < best) {
            best = t;
            part = hs[i].part;
        }
    }
    return part;
}

/* Closest-point-between-two-lines, axis line (p0, unit axis e_axis) vs ray
 * (ro, rd, |rd| == 1): returns the parameter s along the AXIS (so s is a
 * world-space distance from p0). Lines (near-)parallel
 * (1 - (rd.e)^2 < 1e-6) or non-finite: bounded false. */
static bool eg_axis_project(const f32 ro[3], const f32 rd[3],
                            const f32 p0[3], int axis, f32 *out_s) {
    f32 w0[3] = { p0[0] - ro[0], p0[1] - ro[1], p0[2] - ro[2] };
    f32 b = rd[axis]; /* rd . e_axis */
    f32 d = w0[axis]; /* w0 . e_axis */
    f32 e = rd[0] * w0[0] + rd[1] * w0[1] + rd[2] * w0[2];
    f32 denom = 1.0f - b * b;
    if (!isfinite(denom) || denom < 1e-6f) return false;
    f32 s = (b * e - d) / denom;
    if (!isfinite(s)) return false;
    *out_s = s;
    return true;
}

/* Ray intersection with the camera-facing plane through p0 (normal = the
 * camera forward axis). Bounded false on a (near-)parallel ray or
 * non-finite result. */
static bool eg_plane_hit(const BreakEditorCamera *cam, const f32 ro[3],
                         const f32 rd[3], const f32 p0[3], f32 out[3]) {
    f32 eye[3];
    eg_camera_eye(cam, eye);
    f32 n[3] = { cam->target[0] - eye[0], cam->target[1] - eye[1],
                 cam->target[2] - eye[2] };
    f32 nl = sqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    if (!isfinite(nl) || !(nl > 1e-12f)) return false;
    n[0] /= nl;
    n[1] /= nl;
    n[2] /= nl;
    f32 denom = n[0] * rd[0] + n[1] * rd[1] + n[2] * rd[2];
    if (!isfinite(denom) || fabsf(denom) < 1e-8f) return false;
    f32 t = (n[0] * (p0[0] - ro[0]) + n[1] * (p0[1] - ro[1]) +
             n[2] * (p0[2] - ro[2])) /
            denom;
    if (!isfinite(t)) return false;
    out[0] = ro[0] + t * rd[0];
    out[1] = ro[1] + t * rd[1];
    out[2] = ro[2] + t * rd[2];
    return isfinite(out[0]) && isfinite(out[1]) && isfinite(out[2]);
}

/* ---- command vtable ---- */

static u8 *eg_transform_bytes(BreakEditorDoc *doc, BreakEditorEntityId id) {
    return break_editor_doc_component_bytes(doc, id,
                                            BREAK_EDITOR_COMPONENT_TRANSFORM);
}

static bool gizmo_cmd_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorGizmoCmd *c = (BreakEditorGizmoCmd *)self;
    u8 *base = eg_transform_bytes(doc, self->id);
    if (!base) return false; /* entity/component gone: bounded failure */
    for (u32 i = 0; i < c->field_count; i++) {
        memcpy(base + c->field_offset[i], &c->new_bits[i], sizeof(u32));
    }
    return true;
}

static bool gizmo_cmd_revert(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorGizmoCmd *c = (BreakEditorGizmoCmd *)self;
    u8 *base = eg_transform_bytes(doc, self->id);
    if (!base) return false;
    for (u32 i = 0; i < c->field_count; i++) {
        memcpy(base + c->field_offset[i], &c->old_bits[i], sizeof(u32));
    }
    return true;
}

static void gizmo_cmd_destroy(BreakEditorCmd *self) {
    free(self);
}

static void gizmo_cmd_describe(const BreakEditorCmd *self, char buf[128]) {
    const BreakEditorGizmoCmd *c = (const BreakEditorGizmoCmd *)self;
    snprintf(buf, 128, "gizmo %.12s %.8s (%u:%u)", c->mode_name,
             c->part_name, self->id.index, self->id.generation);
}

/* Field offsets come from the doc's component registry (never hardcoded). */
static bool eg_field_offset(BreakEditorDoc *doc, u32 field_index,
                            u32 *out_offset) {
    const BreakEditorComponentReg *reg =
        break_editor_doc_find_component(doc, BREAK_EDITOR_COMPONENT_TRANSFORM);
    if (!reg || field_index >= reg->field_count) return false;
    *out_offset = reg->fields[field_index].offset;
    return true;
}

/* ---- lifecycle ---- */

BreakEditorGizmo *break_editor_gizmo_create(void) {
    BreakEditorGizmo *g = break_editor_test_calloc(sizeof(*g));
    if (!g) return NULL;
    g->mode = BREAK_EDITOR_GIZMO_NONE;
    g->id = BREAK_EDITOR_ENTITY_NULL;
    /* Header contract: until the first camera refresh the cache holds the
     * default camera's scale for a pivot at the camera target. */
    g->scale_base = BREAK_EDITOR_CAMERA_DEFAULT_DISTANCE *
                    tanf(BREAK_EDITOR_CAMERA_DEFAULT_FOV_Y * 0.5f);
    return g;
}

void break_editor_gizmo_destroy(BreakEditorGizmo *g) {
    if (!g) return;
    break_editor_gizmo_end_drag(g); /* mid-drag: commits first (contract) */
    free(g);
}

void break_editor_gizmo_set_mode(BreakEditorGizmo *g,
                                 BreakEditorGizmoMode mode) {
    if (!g) return;
    break_editor_gizmo_end_drag(g); /* documented implicit end+commit */
    g->mode = mode;
}

void break_editor_gizmo_attach(BreakEditorGizmo *g, BreakEditorDoc *doc,
                               BreakEditorEntityId id) {
    if (!g) return;
    break_editor_gizmo_end_drag(g); /* commits against the OLD doc/id */
    if (!doc || !break_editor_entity_id_valid(id)) {
        g->doc = NULL;
        g->id = BREAK_EDITOR_ENTITY_NULL;
        return;
    }
    g->doc = doc;
    g->id = id;
}

void break_editor_gizmo_set_view(BreakEditorGizmo *g,
                                 const BreakEditorCamera *cam) {
    if (!g) return;
    eg_refresh_scale(g, cam);
}

usize break_editor_gizmo_handles(const BreakEditorGizmo *g,
                                 BreakEditorGizmoHandle *out,
                                 usize capacity) {
    if (!g || !out || capacity == 0) return 0;
    if (!g->doc || g->mode == BREAK_EDITOR_GIZMO_NONE) return 0;
    f32 pivot[3];
    if (!eg_pivot(g, pivot)) return 0;
    BreakEditorGizmoHandle all[4];
    eg_build_handles(pivot, g->scale_base, all);
    usize n = capacity < 4u ? capacity : 4u;
    memcpy(out, all, n * sizeof(all[0]));
    return n; /* <= 4 <= BREAK_EDITOR_GIZMO_MAX_HANDLES */
}

BreakEditorGizmoPart break_editor_gizmo_hit(const BreakEditorGizmo *g,
                                            const BreakEditorCamera *cam,
                                            f32 x, f32 y, f32 w, f32 h) {
    if (!g || !cam) return BREAK_EDITOR_GIZMO_PART_NONE;
    /* The sizing cache is a memoized function of (camera, pivot); refreshing
     * it from this const entry point keeps hit() and handles() in agreement
     * (same pattern as the const-doc cast in editor_components.c). */
    eg_refresh_scale((BreakEditorGizmo *)g, cam);
    return eg_hit_impl(g, cam, x, y, w, h);
}

/* ---- drag state machine ---- */

bool break_editor_gizmo_begin_drag(BreakEditorGizmo *g,
                                   const BreakEditorCamera *cam,
                                   f32 x, f32 y, f32 w, f32 h) {
    if (!g || !cam) return false;
    if (g->dragging) {
        break_editor_gizmo_end_drag(g); /* documented implicit end+commit */
    }
    if (!g->doc || g->mode == BREAK_EDITOR_GIZMO_NONE) return false;
    eg_refresh_scale(g, cam);
    BreakEditorGizmoPart part = eg_hit_impl(g, cam, x, y, w, h);
    if (part == BREAK_EDITOR_GIZMO_PART_NONE) return false;

    /* Begin-drag snapshot of all 9 transform fields (the drag math is
     * absolute from these; the command stores the old bytes). */
    f32 fields[9];
    for (u32 i = 0; i < 9; i++) {
        if (!break_editor_doc_get_field_f32(
                g->doc, g->id, BREAK_EDITOR_COMPONENT_TRANSFORM, i,
                &fields[i])) {
            return false;
        }
    }
    for (int k = 0; k < 3; k++) {
        if (!isfinite(fields[k])) return false; /* pivot must be finite */
        g->pivot0[k] = fields[k];
        g->begin_pos[k] = fields[k];
        g->begin_rot[k] = fields[3 + k];
        g->begin_scale[k] = fields[6 + k];
    }

    /* Grab parameters per mode/part; degenerate grab geometry fails the
     * begin bounded (no command, no drag). */
    int axis = eg_part_axis(part);
    if (axis >= 0 && (g->mode == BREAK_EDITOR_GIZMO_TRANSLATE ||
                      g->mode == BREAK_EDITOR_GIZMO_SCALE)) {
        f32 ro[3], rd[3];
        if (!break_editor_viewport_screen_ray(cam, x, y, w, h, ro, rd)) {
            return false;
        }
        if (!eg_axis_project(ro, rd, g->pivot0, axis, &g->grab_s0)) {
            return false; /* ray (near-)parallel to the axis */
        }
    } else if (part == BREAK_EDITOR_GIZMO_PART_CENTER &&
               g->mode == BREAK_EDITOR_GIZMO_TRANSLATE) {
        f32 ro[3], rd[3];
        if (!break_editor_viewport_screen_ray(cam, x, y, w, h, ro, rd)) {
            return false;
        }
        if (!eg_plane_hit(cam, ro, rd, g->pivot0, g->plane_p0)) {
            return false;
        }
    }
    g->drag_x0 = x; /* rotate and CENTER scale read it; harmless otherwise */

    /* The single command object for the whole drag (budget-hooked). */
    BreakEditorGizmoCmd *c = break_editor_test_calloc(sizeof(*c));
    if (!c) return false; /* OOM: bounded false, doc unchanged, no drag */
    c->base.apply = gizmo_cmd_apply;
    c->base.revert = gizmo_cmd_revert;
    c->base.destroy = gizmo_cmd_destroy;
    c->base.describe = gizmo_cmd_describe;
    c->base.kind = BREAK_EDITOR_CMD_KIND_GIZMO_TRANSFORM;
    c->base.id = g->id;
    c->component_id = BREAK_EDITOR_COMPONENT_TRANSFORM;

    static const char *const k_mode_names[] = { "none", "translate",
                                                "rotate", "scale" };
    static const char *const k_part_names[] = { "none", "x", "y", "z",
                                                "center" };
    snprintf(c->mode_name, sizeof(c->mode_name), "%.8s",
             k_mode_names[g->mode <= BREAK_EDITOR_GIZMO_SCALE ? g->mode : 0]);
    snprintf(c->part_name, sizeof(c->part_name), "%.7s",
             k_part_names[part <= BREAK_EDITOR_GIZMO_PART_CENTER ? part : 0]);

    /* Field slots: translate X/Y/Z -> pos[axis]; CENTER -> pos[0..2];
     * rotate X/Y/Z -> rot[axis]; CENTER -> none; scale X/Y/Z ->
     * scale[axis]; CENTER -> scale[0..2]. */
    u32 first = 0;
    if (axis >= 0) {
        if (g->mode == BREAK_EDITOR_GIZMO_ROTATE) first = 3u + (u32)axis;
        else if (g->mode == BREAK_EDITOR_GIZMO_SCALE) first = 6u + (u32)axis;
        else first = (u32)axis;
        c->field_count = 1;
        if (!eg_field_offset(g->doc, first, &c->field_offset[0])) goto fail;
        u32 bits;
        memcpy(&bits, &fields[first], sizeof(u32));
        c->old_bits[0] = bits;
    } else if (g->mode == BREAK_EDITOR_GIZMO_TRANSLATE ||
               g->mode == BREAK_EDITOR_GIZMO_SCALE) {
        first = (g->mode == BREAK_EDITOR_GIZMO_SCALE) ? 6u : 0u;
        c->field_count = 3;
        for (u32 k = 0; k < 3; k++) {
            if (!eg_field_offset(g->doc, first + k, &c->field_offset[k])) {
                goto fail;
            }
            u32 bits;
            memcpy(&bits, &fields[first + k], sizeof(u32));
            c->old_bits[k] = bits;
        }
    } else {
        c->field_count = 0; /* ROTATE CENTER: defined no-op drag */
    }

    g->cmd = c;
    g->drag_part = part;
    g->dragging = true;
    return true;

fail:
    c->base.destroy(&c->base);
    return false;
}

bool break_editor_gizmo_drag(BreakEditorGizmo *g,
                             const BreakEditorCamera *cam,
                             f32 x, f32 y, f32 w, f32 h) {
    if (!g || !cam) return false;
    if (!g->dragging) return false;
    if (!isfinite(x) || !isfinite(y) || !isfinite(w) || !isfinite(h)) {
        return false;
    }
    eg_refresh_scale(g, cam);
    int axis = eg_part_axis(g->drag_part);

    /* New field values, absolute from the begin-drag snapshot. */
    f32 new_vals[3] = { 0.0f, 0.0f, 0.0f };
    if (g->mode == BREAK_EDITOR_GIZMO_TRANSLATE && axis >= 0) {
        f32 ro[3], rd[3], s;
        if (!break_editor_viewport_screen_ray(cam, x, y, w, h, ro, rd)) {
            return false;
        }
        if (!eg_axis_project(ro, rd, g->pivot0, axis, &s)) return false;
        new_vals[0] = g->begin_pos[axis] + (s - g->grab_s0);
    } else if (g->mode == BREAK_EDITOR_GIZMO_TRANSLATE) { /* CENTER */
        f32 ro[3], rd[3], p[3];
        if (!break_editor_viewport_screen_ray(cam, x, y, w, h, ro, rd)) {
            return false;
        }
        if (!eg_plane_hit(cam, ro, rd, g->pivot0, p)) return false;
        for (int k = 0; k < 3; k++) {
            new_vals[k] = g->begin_pos[k] + (p[k] - g->plane_p0[k]);
        }
    } else if (g->mode == BREAK_EDITOR_GIZMO_ROTATE) {
        if (axis < 0) return true; /* CENTER: defined no-op (contract) */
        /* Sign convention: dragging right (x increasing) adds positive
         * degrees to the axis field. */
        new_vals[0] = g->begin_rot[axis] +
                      (x - g->drag_x0) * BREAK_EDITOR_GIZMO_ROTATE_DEG_PER_PX;
    } else { /* SCALE */
        if (axis >= 0) {
            f32 ro[3], rd[3], s;
            if (!break_editor_viewport_screen_ray(cam, x, y, w, h, ro, rd)) {
                return false;
            }
            if (!eg_axis_project(ro, rd, g->pivot0, axis, &s)) return false;
            if (!(g->begin_scale[axis] > 0.0f)) return false; /* contract */
            /* factor = 2^(s - s0): one world unit along +axis doubles. */
            f32 v = g->begin_scale[axis] * powf(2.0f, s - g->grab_s0);
            if (v < BREAK_EDITOR_GIZMO_SCALE_MIN) {
                v = BREAK_EDITOR_GIZMO_SCALE_MIN;
            }
            new_vals[0] = v;
        } else { /* CENTER: uniform, 200 px per octave */
            f32 factor = powf(2.0f, (x - g->drag_x0) /
                                        BREAK_EDITOR_GIZMO_UNIFORM_SCALE_PX_PER_OCTAVE);
            for (int k = 0; k < 3; k++) {
                if (!(g->begin_scale[k] > 0.0f)) return false;
                f32 v = g->begin_scale[k] * factor;
                if (v < BREAK_EDITOR_GIZMO_SCALE_MIN) {
                    v = BREAK_EDITOR_GIZMO_SCALE_MIN;
                }
                new_vals[k] = v;
            }
        }
    }
    for (u32 i = 0; i < g->cmd->field_count; i++) {
        if (!isfinite(new_vals[i])) return false; /* NaN/Inf guard: reject */
    }

    /* Live write through the in-progress command's field slots;
     * bitwise-identical writes are skipped (set_field_f32 convention). */
    u8 *base = eg_transform_bytes(g->doc, g->id);
    if (!base) return false; /* entity/component vanished mid-drag */
    bool changed = false;
    for (u32 i = 0; i < g->cmd->field_count; i++) {
        u32 bits, cur;
        memcpy(&bits, &new_vals[i], sizeof(u32));
        memcpy(&cur, base + g->cmd->field_offset[i], sizeof(u32));
        if (cur != bits) {
            memcpy(base + g->cmd->field_offset[i], &bits, sizeof(u32));
            changed = true;
        }
    }
    if (changed) g->doc->dirty = true;
    return true;
}

void break_editor_gizmo_end_drag(BreakEditorGizmo *g) {
    if (!g || !g->dragging) return;
    BreakEditorGizmoCmd *c = g->cmd;
    g->dragging = false;
    g->drag_part = BREAK_EDITOR_GIZMO_PART_NONE;
    g->cmd = NULL;
    if (!c) return;

    u8 *base = eg_transform_bytes(g->doc, g->id);
    if (!base) {
        /* Entity/component vanished mid-drag: DISCARD (bounded) — the
         * command's revert/apply could only fail anyway. */
        c->base.destroy(&c->base);
        return;
    }
    bool same = true;
    for (u32 i = 0; i < c->field_count; i++) {
        u32 cur;
        memcpy(&cur, base + c->field_offset[i], sizeof(u32));
        c->new_bits[i] = cur;
        if (cur != c->old_bits[i]) same = false;
    }
    if (same) {
        c->base.destroy(&c->base); /* bitwise-identical: no command */
        return;
    }
    /* Commit: the doc already shows the final state; push as applied.
     * push_applied never allocates, so this succeeds under any budget. */
    break_editor_cmd_stack_push_applied(g->doc, &c->base);
    g->doc->dirty = true;
}
