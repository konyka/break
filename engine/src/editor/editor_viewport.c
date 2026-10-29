/* Editor viewport CPU core implementation — see editor_viewport.h for the
 * contract (camera model, proxy AABB semantics, per-call BVH rebuild,
 * bounded degenerate/OOM paths, single owner thread). */

#include <editor/editor_viewport.h>

#include <editor/editor_components.h>
#include <editor/editor_test_hooks.h>

#include <math/math.h>
#include <physics/bvh.h>

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ED_PI_F 3.14159265358979323846f
#define ED_DEG_TO_RAD (ED_PI_F / 180.0f)

static f32 ed_clampf(f32 v, f32 lo, f32 hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

static bool ed_finite3(const f32 v[3]) {
    return isfinite(v[0]) && isfinite(v[1]) && isfinite(v[2]);
}

static bool ed_camera_finite(const BreakEditorCamera *cam) {
    return ed_finite3(cam->target) && isfinite(cam->yaw) &&
           isfinite(cam->pitch) && isfinite(cam->distance) &&
           isfinite(cam->fov_y);
}

/* Column-vector M*v under the canonical column-major convention
 * (e[col][row], math.h R438): r_i = sum_j e[j][i] * v_j — the mat4 x vec4
 * helper math.h does not provide (test-only precedent cam_apply_point,
 * engine/tests/test_camera_frustum.c:43-49). */
static void ed_mat4_mul_vec4(const Mat4 *m, const f32 v[4], f32 out[4]) {
    for (int i = 0; i < 4; i++) {
        out[i] = m->e[0][i] * v[0] + m->e[1][i] * v[1] +
                 m->e[2][i] * v[2] + m->e[3][i] * v[3];
    }
}

static void ed_camera_eye(const BreakEditorCamera *cam, f32 out_eye[3]) {
    f32 cp = cosf(cam->pitch), sp = sinf(cam->pitch);
    f32 cy = cosf(cam->yaw),   sy = sinf(cam->yaw);
    out_eye[0] = cam->target[0] + cam->distance * cp * sy;
    out_eye[1] = cam->target[1] + cam->distance * sp;
    out_eye[2] = cam->target[2] + cam->distance * cp * cy;
}

/* Proxy AABB for an entity: center = pos, half-extent = 0.5*|scale| per
 * axis, min clamp BREAK_EDITOR_PROXY_MIN_HALF_EXTENT. Bounded false when
 * the entity lacks an EditorTransform, a field read fails, or any pos/scale
 * component is non-finite (skipped, never picked/focused). */
static bool ed_entity_proxy_aabb(const BreakEditorDoc *doc,
                                 BreakEditorEntityId id, BVHAABB *out) {
    if (!break_editor_doc_has_component(doc, id,
                                        BREAK_EDITOR_COMPONENT_TRANSFORM)) {
        return false;
    }
    f32 pos[3], scale[3];
    for (u32 k = 0; k < 3; k++) {
        if (!break_editor_doc_get_field_f32(
                doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, k, &pos[k]) ||
            !break_editor_doc_get_field_f32(
                doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 6u + k,
                &scale[k])) {
            return false;
        }
    }
    for (int k = 0; k < 3; k++) {
        if (!isfinite(pos[k]) || !isfinite(scale[k])) return false;
        f32 half = 0.5f * fabsf(scale[k]);
        if (half < BREAK_EDITOR_PROXY_MIN_HALF_EXTENT) {
            half = BREAK_EDITOR_PROXY_MIN_HALF_EXTENT;
        }
        out->min.e[k] = pos[k] - half;
        out->max.e[k] = pos[k] + half;
    }
    return true;
}

void break_editor_camera_init(BreakEditorCamera *cam) {
    if (!cam) return;
    cam->target[0] = 0.0f;
    cam->target[1] = 0.0f;
    cam->target[2] = 0.0f;
    cam->yaw = 0.0f;
    cam->pitch = 0.0f;
    cam->distance = BREAK_EDITOR_CAMERA_DEFAULT_DISTANCE;
    cam->fov_y = BREAK_EDITOR_CAMERA_DEFAULT_FOV_Y;
}

void break_editor_camera_view(const BreakEditorCamera *cam, f32 out_view[16]) {
    f32 eye[3];
    ed_camera_eye(cam, eye);
    Mat4 m = mat4_lookat(vec3(eye[0], eye[1], eye[2]),
                         vec3(cam->target[0], cam->target[1], cam->target[2]),
                         vec3(0.0f, 1.0f, 0.0f));
    memcpy(out_view, m.e, sizeof(m.e));
}

void break_editor_camera_proj(const BreakEditorCamera *cam, f32 aspect, f32 out_proj[16]) {
    Mat4 m = mat4_perspective(cam->fov_y, aspect,
                              BREAK_EDITOR_VIEWPORT_NEAR,
                              BREAK_EDITOR_VIEWPORT_FAR);
    memcpy(out_proj, m.e, sizeof(m.e));
}

bool break_editor_viewport_screen_ray(const BreakEditorCamera *cam,
    f32 x, f32 y, f32 w, f32 h, f32 out_origin[3], f32 out_dir[3]) {
    if (!cam || !out_origin || !out_dir) return false;
    if (!isfinite(x) || !isfinite(y) || !isfinite(w) || !isfinite(h)) {
        return false;
    }
    if (!(w > 0.0f) || !(h > 0.0f)) return false;
    if (!ed_camera_finite(cam)) return false;
    if (!(cam->fov_y > 0.0f) || !(cam->fov_y < ED_PI_F)) return false;
    if (!(cam->distance > 0.0f)) return false;

    /* Unproject the pixel through the SAME public matrices: ndc (top-left
     * origin -> y flips) at the far plane (z=+1) -> inv_proj -> inv_view.
     * mat4_inv_perspective's TAA jitter terms (e[2][0..1]) are exactly zero
     * here because break_editor_camera_proj never jitters. */
    f32 view16[16], proj16[16];
    break_editor_camera_view(cam, view16);
    break_editor_camera_proj(cam, w / h, proj16);
    Mat4 view, proj;
    memcpy(&view, view16, sizeof(view));
    memcpy(&proj, proj16, sizeof(proj));
    Mat4 inv_proj = mat4_inv_perspective(proj);
    Mat4 inv_view = mat4_inverse(view);

    f32 ndc[4] = { 2.0f * x / w - 1.0f, 1.0f - 2.0f * y / h, 1.0f, 1.0f };
    f32 vp[4];
    ed_mat4_mul_vec4(&inv_proj, ndc, vp);
    if (!isfinite(vp[0]) || !isfinite(vp[1]) || !isfinite(vp[2]) ||
        !isfinite(vp[3]) || !(fabsf(vp[3]) > 1e-20f)) {
        return false;
    }
    f32 inv_w = 1.0f / vp[3];
    f32 v3[4] = { vp[0] * inv_w, vp[1] * inv_w, vp[2] * inv_w, 1.0f };
    if (!ed_finite3(v3)) return false;

    f32 wp[4];
    ed_mat4_mul_vec4(&inv_view, v3, wp);
    if (!ed_finite3(wp)) return false;

    f32 eye[3];
    ed_camera_eye(cam, eye);
    f32 d[3] = { wp[0] - eye[0], wp[1] - eye[1], wp[2] - eye[2] };
    f32 len_sq = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
    if (!isfinite(len_sq) || !(len_sq > 1e-24f)) return false;
    f32 inv_len = 1.0f / sqrtf(len_sq);

    out_origin[0] = eye[0];
    out_origin[1] = eye[1];
    out_origin[2] = eye[2];
    out_dir[0] = d[0] * inv_len;
    out_dir[1] = d[1] * inv_len;
    out_dir[2] = d[2] * inv_len;
    return true;
}

bool break_editor_viewport_pick(BreakEditorDoc *doc, const BreakEditorCamera *cam,
    f32 x, f32 y, f32 w, f32 h, BreakEditorPickResult *out) {
    if (!doc || !cam || !out) return false;

    f32 origin[3], dir[3];
    if (!break_editor_viewport_screen_ray(cam, x, y, w, h, origin, dir)) {
        return false;
    }

    usize total = break_editor_doc_entity_count(doc);
    if (total == 0) return false;
    /* Plan bound: pick candidate buffer <= 4096 entities per query. */
    if (total > BREAK_EDITOR_PICK_MAX_ENTITIES) {
        total = BREAK_EDITOR_PICK_MAX_ENTITIES;
    }

    /* Editor-owned allocations (budget-hooked under BREAK_EDITOR_TESTING):
     * proxy AABB array, parallel entity-id map, BVH struct. bvh.c's
     * INTERNAL allocations belong to the bvh TU and are unhooked (Phase 1
     * World convention); bvh_build fails bounded (root = BVH_NULL) on its
     * own OOM, surfacing here as a clean miss. */
    BVHAABB *aabbs = (BVHAABB *)break_editor_test_calloc(total * sizeof(BVHAABB));
    BreakEditorEntityId *ids = (BreakEditorEntityId *)break_editor_test_calloc(
        total * sizeof(BreakEditorEntityId));
    BVH *bvh = (BVH *)break_editor_test_calloc(sizeof(BVH));
    if (!aabbs || !ids || !bvh) {
        free(aabbs);
        free(ids);
        free(bvh);
        return false;
    }

    /* Compacted proxy array: entities without an EditorTransform (or with
     * non-finite pos/scale) are skipped; the bvh object_index is the proxy
     * array position and maps back through ids[]. */
    u32 n = 0;
    for (usize i = 0; i < total; i++) {
        BreakEditorEntityId id;
        const char *name = NULL;
        if (!break_editor_doc_entity_at(doc, i, &id, &name)) continue;
        if (!ed_entity_proxy_aabb(doc, id, &aabbs[n])) continue;
        ids[n] = id;
        n++;
    }

    bool hit = false;
    BVHRayHit ray_hit;
    if (n > 0) {
        /* Phase 2 choice (documented in the header): the BVH is rebuilt on
         * every pick; entity counts are editor-scale. */
        bvh_init(bvh, n);
        bvh_build(bvh, aabbs, n);
        hit = bvh_raycast(bvh, vec3(origin[0], origin[1], origin[2]),
                          vec3(dir[0], dir[1], dir[2]), FLT_MAX, &ray_hit);
        if (hit && ray_hit.object_index < n) {
            out->id = ids[ray_hit.object_index];
            out->t = ray_hit.t;
        } else {
            hit = false;
        }
    }

    bvh_destroy(bvh); /* safe on a zeroed/partially initialized struct */
    free(aabbs);
    free(ids);
    free(bvh);
    return hit;
}

u32 break_editor_viewport_box_select(BreakEditorDoc *doc,
    const BreakEditorCamera *cam, f32 x0, f32 y0, f32 x1, f32 y1,
    f32 w, f32 h, BreakEditorEntityId *out, u32 cap) {
    if (!doc || !cam || !out || cap == 0) return 0;
    if (!isfinite(x0) || !isfinite(y0) || !isfinite(x1) || !isfinite(y1) ||
        !isfinite(w) || !isfinite(h)) {
        return 0;
    }
    if (!(w > 0.0f) || !(h > 0.0f)) return 0;
    if (!ed_camera_finite(cam)) return 0;
    if (!(cam->fov_y > 0.0f) || !(cam->fov_y < ED_PI_F)) return 0;
    if (!(cam->distance > 0.0f)) return 0;

    f32 lo_x = x0 < x1 ? x0 : x1, hi_x = x0 < x1 ? x1 : x0;
    f32 lo_y = y0 < y1 ? y0 : y1, hi_y = y0 < y1 ? y1 : y0;

    f32 view16[16], proj16[16];
    break_editor_camera_view(cam, view16);
    break_editor_camera_proj(cam, w / h, proj16);
    Mat4 view, proj;
    memcpy(&view, view16, sizeof(view));
    memcpy(&proj, proj16, sizeof(proj));
    Mat4 vp = mat4_mul(proj, view);

    usize total = break_editor_doc_entity_count(doc);
    if (total > BREAK_EDITOR_PICK_MAX_ENTITIES) {
        total = BREAK_EDITOR_PICK_MAX_ENTITIES;
    }
    u32 n = 0;
    for (usize i = 0; i < total && n < cap; i++) {
        BreakEditorEntityId id;
        const char *name = NULL;
        if (!break_editor_doc_entity_at(doc, i, &id, &name)) continue;
        if (!break_editor_doc_has_component(doc, id,
                                            BREAK_EDITOR_COMPONENT_TRANSFORM)) {
            continue;
        }
        f32 p[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        bool ok = true;
        for (u32 k = 0; k < 3 && ok; k++) {
            ok = break_editor_doc_get_field_f32(
                     doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, k, &p[k]) &&
                 isfinite(p[k]);
        }
        if (!ok) continue;
        f32 clip[4];
        ed_mat4_mul_vec4(&vp, p, clip);
        if (!isfinite(clip[0]) || !isfinite(clip[1]) || !isfinite(clip[3]) ||
            !(clip[3] > BREAK_EDITOR_VIEWPORT_NEAR)) {
            continue;
        }
        f32 sx = (clip[0] / clip[3] + 1.0f) * 0.5f * w;
        f32 sy = (1.0f - clip[1] / clip[3]) * 0.5f * h;
        if (sx >= lo_x && sx <= hi_x && sy >= lo_y && sy <= hi_y) {
            out[n++] = id;
        }
    }
    return n;
}

void break_editor_camera_focus(BreakEditorCamera *cam, const BreakEditorDoc *doc,
                               BreakEditorEntityId id) {
    if (!cam || !doc || !break_editor_entity_id_valid(id)) return;
    if (!ed_camera_finite(cam)) return;
    if (!(cam->fov_y > 0.0f) || !(cam->fov_y < ED_PI_F)) return;

    BVHAABB box;
    if (!ed_entity_proxy_aabb(doc, id, &box)) return;

    /* Fit the proxy's bounding sphere vertically: distance =
     * radius / tan(fov_y/2), clamped [0.05, 1e4]. yaw/pitch untouched. */
    f32 half[3] = {
        0.5f * (box.max.e[0] - box.min.e[0]),
        0.5f * (box.max.e[1] - box.min.e[1]),
        0.5f * (box.max.e[2] - box.min.e[2]),
    };
    f32 radius = sqrtf(half[0] * half[0] + half[1] * half[1] +
                       half[2] * half[2]);
    f32 t = tanf(cam->fov_y * 0.5f);
    if (!(t > 1e-6f)) return;
    f32 distance = radius / t;

    cam->target[0] = 0.5f * (box.min.e[0] + box.max.e[0]);
    cam->target[1] = 0.5f * (box.min.e[1] + box.max.e[1]);
    cam->target[2] = 0.5f * (box.min.e[2] + box.max.e[2]);
    cam->distance = ed_clampf(distance, BREAK_EDITOR_CAMERA_MIN_DISTANCE,
                              BREAK_EDITOR_CAMERA_MAX_DISTANCE);
}

void break_editor_camera_orbit(BreakEditorCamera *cam, f32 dx_deg, f32 dy_deg) {
    if (!cam || !isfinite(dx_deg) || !isfinite(dy_deg)) return;
    if (!isfinite(cam->yaw) || !isfinite(cam->pitch)) return;
    cam->yaw += dx_deg * ED_DEG_TO_RAD;
    cam->pitch = ed_clampf(cam->pitch + dy_deg * ED_DEG_TO_RAD,
                           -BREAK_EDITOR_CAMERA_PITCH_LIMIT,
                           BREAK_EDITOR_CAMERA_PITCH_LIMIT);
}

void break_editor_camera_pan(BreakEditorCamera *cam, f32 dx_px, f32 dy_px) {
    if (!cam || !isfinite(dx_px) || !isfinite(dy_px)) return;
    if (!ed_camera_finite(cam)) return;
    if (!(cam->distance > 0.0f)) return;
    if (!(cam->fov_y > 0.0f) || !(cam->fov_y < ED_PI_F)) return;

    f32 eye[3];
    ed_camera_eye(cam, eye);
    Vec3 target = vec3(cam->target[0], cam->target[1], cam->target[2]);
    Vec3 fwd = vec3_sub(target, vec3(eye[0], eye[1], eye[2]));
    f32 fl = vec3_len(fwd);
    if (!(fl > 1e-12f) || !isfinite(fl)) return;
    fwd = vec3_scale(fwd, 1.0f / fl);

    /* Camera right/up in world space (same basis as mat4_lookat). The +/-89
     * deg pitch clamp keeps fwd off +Y, so this cross never degenerates. */
    Vec3 right = vec3_cross(fwd, vec3(0.0f, 1.0f, 0.0f));
    f32 rl = vec3_len(right);
    if (!(rl > 1e-6f) || !isfinite(rl)) return;
    right = vec3_scale(right, 1.0f / rl);
    Vec3 up = vec3_cross(right, fwd);

    /* World-units per pixel at the pivot plane, scaled by distance. */
    f32 wpp = 2.0f * cam->distance * tanf(cam->fov_y * 0.5f) /
              BREAK_EDITOR_VIEWPORT_PAN_REFERENCE_HEIGHT;
    Vec3 delta = vec3_add(vec3_scale(right, -dx_px * wpp),
                          vec3_scale(up, dy_px * wpp));
    cam->target[0] += delta.e[0];
    cam->target[1] += delta.e[1];
    cam->target[2] += delta.e[2];
}

void break_editor_camera_zoom(BreakEditorCamera *cam, f32 wheel_delta) {
    if (!cam || !isfinite(wheel_delta)) return;
    if (!isfinite(cam->distance)) return;
    f32 d = cam->distance * expf(-BREAK_EDITOR_CAMERA_ZOOM_SPEED * wheel_delta);
    cam->distance = ed_clampf(d, BREAK_EDITOR_CAMERA_MIN_DISTANCE,
                              BREAK_EDITOR_CAMERA_MAX_DISTANCE);
}
