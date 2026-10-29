/* Stage 4 scene editor Phase 2 Task 1: viewport CPU core tests — camera
 * known-answers, screen->ray unprojection, BVH picking, focus/orbit/pan/zoom.
 *
 * Covers the brief checkboxes: camera init defaults (eye on +Z behind
 * target; view maps target to (0,0,-distance)); screen_ray through the
 * center equals the forward axis; corner rays diverge symmetrically; pick
 * nearest entity among three on a ray; pick miss; degenerate viewport
 * (w=0) -> bounded false; focus sets target to the entity pos and a clamped
 * fit distance; orbit clamps pitch to +/-89 deg; pan proportional to
 * distance; zoom exponential + clamped; OOM budget sweep over pick's
 * editor-owned allocations (proxy AABB array, id map, BVH struct). */

#include "test_framework.h"

#include <editor/editor_viewport.h>
#include <editor/editor_components.h>
#include <editor/editor_test_hooks.h>

#include <float.h>
#include <math.h>
#include <string.h>

#define ED_PI 3.14159265358979323846
#define ED_DEG2RAD(d) ((f32)(d) * (f32)(ED_PI / 180.0))
/* tan(30 deg), for the default 60 deg fov. */
#define ED_TAN30 0.5773502691896258f

/* Column-vector M*v for a point (w=1) under the canonical column-major
 * convention (e[col][row]): r_i = sum_j e[j][i] * v_j — same convention as
 * cam_apply_point in engine/tests/test_camera_frustum.c:43-49. */
static void apply_point4(const f32 m[16], f32 x, f32 y, f32 z, f32 out[3]) {
    f32 v[4] = { x, y, z, 1.0f };
    for (int i = 0; i < 3; i++) {
        out[i] = m[0 * 4 + i] * v[0] + m[1 * 4 + i] * v[1] +
                 m[2 * 4 + i] * v[2] + m[3 * 4 + i] * v[3];
    }
}

static void assert_vec3(f32 ax, f32 ay, f32 az,
                        f32 bx, f32 by, f32 bz, f32 eps) {
    ASSERT_FLOAT_EQ(ax, bx, eps);
    ASSERT_FLOAT_EQ(ay, by, eps);
    ASSERT_FLOAT_EQ(az, bz, eps);
}

/* eye = target + distance * (cos(pitch)*sin(yaw), sin(pitch),
 *                            cos(pitch)*cos(yaw)) */
static void camera_eye(const BreakEditorCamera *cam, f32 out[3]) {
    f32 cp = cosf(cam->pitch), sp = sinf(cam->pitch);
    f32 cy = cosf(cam->yaw), sy = sinf(cam->yaw);
    out[0] = cam->target[0] + cam->distance * cp * sy;
    out[1] = cam->target[1] + cam->distance * sp;
    out[2] = cam->target[2] + cam->distance * cp * cy;
}

static BreakEditorEntityId add_transformed(BreakEditorDoc *doc,
                                           const char *name,
                                           f32 px, f32 py, f32 pz,
                                           f32 sx, f32 sy, f32 sz) {
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, name);
    if (!break_editor_entity_id_valid(id)) return id;
    if (!break_editor_doc_add_component(doc, id,
                                        BREAK_EDITOR_COMPONENT_TRANSFORM)) {
        return BREAK_EDITOR_ENTITY_NULL;
    }
    f32 v[6] = { px, py, pz, sx, sy, sz };
    for (u32 k = 0; k < 3; k++) {
        if (!break_editor_doc_set_field_f32(
                doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, k, v[k])) {
            return BREAK_EDITOR_ENTITY_NULL;
        }
        if (!break_editor_doc_set_field_f32(
                doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 6u + k, v[3 + k])) {
            return BREAK_EDITOR_ENTITY_NULL;
        }
    }
    return id;
}

TEST(camera_init_defaults) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 0, 0, 0, 0);
    ASSERT_FLOAT_EQ(cam.yaw, 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(cam.pitch, 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(cam.distance, 5.0f, 1e-6f);
    ASSERT_FLOAT_EQ(cam.fov_y, ED_DEG2RAD(60.0), 1e-6f);
}

TEST(camera_view_known_answers) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    /* Default: eye on +Z behind target; view maps target -> (0,0,-distance)
     * and eye -> origin; world X is view X (no roll). */
    f32 view[16];
    break_editor_camera_view(&cam, view);
    f32 p[3];
    apply_point4(view, 0, 0, 0, p);
    assert_vec3(p[0], p[1], p[2], 0, 0, -5.0f, 1e-4f);
    apply_point4(view, 0, 0, 5.0f, p);
    assert_vec3(p[0], p[1], p[2], 0, 0, 0, 1e-4f);
    apply_point4(view, 1, 0, 5.0f, p);
    assert_vec3(p[0], p[1], p[2], 1.0f, 0, 0, 1e-4f);

    /* yaw = +90 deg: eye swings to +X, still distance 5 from the pivot. */
    cam.yaw = ED_DEG2RAD(90.0);
    break_editor_camera_view(&cam, view);
    apply_point4(view, 0, 0, 0, p);
    assert_vec3(p[0], p[1], p[2], 0, 0, -5.0f, 1e-4f);
    apply_point4(view, 5.0f, 0, 0, p); /* eye -> origin */
    assert_vec3(p[0], p[1], p[2], 0, 0, 0, 1e-4f);

    /* pitch = +45 deg elevates the camera; the pivot stays dead ahead. */
    cam.yaw = 0.0f;
    cam.pitch = ED_DEG2RAD(45.0);
    break_editor_camera_view(&cam, view);
    apply_point4(view, 0, 0, 0, p);
    assert_vec3(p[0], p[1], p[2], 0, 0, -5.0f, 1e-3f);
    f32 eye[3];
    camera_eye(&cam, eye);
    apply_point4(view, eye[0], eye[1], eye[2], p);
    assert_vec3(p[0], p[1], p[2], 0, 0, 0, 1e-3f);
}

TEST(camera_proj_known_answers) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 proj[16];
    break_editor_camera_proj(&cam, 4.0f / 3.0f, proj);
    /* mat4_perspective layout (column-major): e[0][0] = f/aspect,
     * e[1][1] = f, e[2][2] = -(far+near)/(far-near), e[2][3] = -1,
     * e[3][2] = -(2*far*near)/(far-near). */
    f32 f = 1.0f / ED_TAN30;
    ASSERT_FLOAT_EQ(proj[0 * 4 + 0], f / (4.0f / 3.0f), 1e-4f);
    ASSERT_FLOAT_EQ(proj[1 * 4 + 1], f, 1e-4f);
    ASSERT_FLOAT_EQ(proj[2 * 4 + 2],
                    -(20000.0f + 0.05f) / (20000.0f - 0.05f), 1e-4f);
    ASSERT_FLOAT_EQ(proj[2 * 4 + 3], -1.0f, 0.0f);
    ASSERT_FLOAT_EQ(proj[3 * 4 + 2],
                    -(2.0f * 20000.0f * 0.05f) / (20000.0f - 0.05f), 1e-4f);
    ASSERT_FLOAT_EQ(proj[3 * 4 + 3], 0.0f, 0.0f);
}

TEST(screen_ray_center_equals_forward) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    f32 origin[3], dir[3];
    ASSERT_TRUE(break_editor_viewport_screen_ray(&cam, 400, 300, 800, 600,
                                                 origin, dir));
    assert_vec3(origin[0], origin[1], origin[2], 0, 0, 5.0f, 1e-4f);
    assert_vec3(dir[0], dir[1], dir[2], 0, 0, -1.0f, 1e-4f);

    /* yaw = +90 deg: eye on +X, forward = -X. */
    cam.yaw = ED_DEG2RAD(90.0);
    ASSERT_TRUE(break_editor_viewport_screen_ray(&cam, 400, 300, 800, 600,
                                                 origin, dir));
    assert_vec3(origin[0], origin[1], origin[2], 5.0f, 0, 0, 1e-4f);
    assert_vec3(dir[0], dir[1], dir[2], -1.0f, 0, 0, 1e-4f);
}

TEST(screen_ray_corners_diverge) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    f32 o00[3], d00[3], o11[3], d11[3];
    ASSERT_TRUE(break_editor_viewport_screen_ray(&cam, 0, 0, 800, 600,
                                                 o00, d00));
    ASSERT_TRUE(break_editor_viewport_screen_ray(&cam, 800, 600, 800, 600,
                                                 o11, d11));
    /* Origin is always the eye. */
    assert_vec3(o00[0], o00[1], o00[2], 0, 0, 5.0f, 1e-4f);
    assert_vec3(o11[0], o11[1], o11[2], 0, 0, 5.0f, 1e-4f);
    /* Top-left origin: (0,0) is ndc (-1,+1) -> left/up; (w,h) is (+1,-1). */
    ASSERT_TRUE(d00[0] < 0.0f);
    ASSERT_TRUE(d00[1] > 0.0f);
    ASSERT_TRUE(d00[2] < 0.0f);
    ASSERT_TRUE(d11[0] > 0.0f);
    ASSERT_TRUE(d11[1] < 0.0f);
    ASSERT_TRUE(d11[2] < 0.0f);
    /* Symmetric frustum: mirrored corners, same depth slope. */
    ASSERT_FLOAT_EQ(d00[0], -d11[0], 1e-5f);
    ASSERT_FLOAT_EQ(d00[1], -d11[1], 1e-5f);
    ASSERT_FLOAT_EQ(d00[2], d11[2], 1e-5f);
    /* Normalized + diverging. */
    f32 l00 = sqrtf(d00[0] * d00[0] + d00[1] * d00[1] + d00[2] * d00[2]);
    f32 l11 = sqrtf(d11[0] * d11[0] + d11[1] * d11[1] + d11[2] * d11[2]);
    ASSERT_FLOAT_EQ(l00, 1.0f, 1e-4f);
    ASSERT_FLOAT_EQ(l11, 1.0f, 1e-4f);
    f32 dot = d00[0] * d11[0] + d00[1] * d11[1] + d00[2] * d11[2];
    ASSERT_TRUE(dot < 1.0f - 1e-3f);
}

TEST(screen_ray_degenerate_bounded_false) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 origin[3], dir[3];

    ASSERT_FALSE(break_editor_viewport_screen_ray(&cam, 0, 0, 0, 600,
                                                  origin, dir));
    ASSERT_FALSE(break_editor_viewport_screen_ray(&cam, 0, 0, 800, 0,
                                                  origin, dir));
    ASSERT_FALSE(break_editor_viewport_screen_ray(&cam, 0, 0, -100, 600,
                                                  origin, dir));
    ASSERT_FALSE(break_editor_viewport_screen_ray(&cam, NAN, 0, 800, 600,
                                                  origin, dir));
    ASSERT_FALSE(break_editor_viewport_screen_ray(&cam, 0, INFINITY, 800, 600,
                                                  origin, dir));
    ASSERT_FALSE(break_editor_viewport_screen_ray(&cam, 0, 0, NAN, 600,
                                                  origin, dir));
    ASSERT_FALSE(break_editor_viewport_screen_ray(NULL, 0, 0, 800, 600,
                                                  origin, dir));
    ASSERT_FALSE(break_editor_viewport_screen_ray(&cam, 0, 0, 800, 600,
                                                  NULL, dir));
    ASSERT_FALSE(break_editor_viewport_screen_ray(&cam, 0, 0, 800, 600,
                                                  origin, NULL));

    /* Degenerate camera state. */
    BreakEditorCamera bad;
    break_editor_camera_init(&bad);
    bad.fov_y = 0.0f;
    ASSERT_FALSE(break_editor_viewport_screen_ray(&bad, 0, 0, 800, 600,
                                                  origin, dir));
    bad.fov_y = (f32)ED_PI;
    ASSERT_FALSE(break_editor_viewport_screen_ray(&bad, 0, 0, 800, 600,
                                                  origin, dir));
    break_editor_camera_init(&bad);
    bad.distance = 0.0f;
    ASSERT_FALSE(break_editor_viewport_screen_ray(&bad, 0, 0, 800, 600,
                                                  origin, dir));
    break_editor_camera_init(&bad);
    bad.yaw = NAN;
    ASSERT_FALSE(break_editor_viewport_screen_ray(&bad, 0, 0, 800, 600,
                                                  origin, dir));
}

TEST(pick_nearest_of_three_on_ray) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    /* Insertion order far/mid/near so proxy order != distance order. */
    BreakEditorEntityId far_e = add_transformed(doc, "far", 0, 0, -15, 1, 1, 1);
    BreakEditorEntityId mid_e = add_transformed(doc, "mid", 0, 0, -10, 1, 1, 1);
    BreakEditorEntityId near_e = add_transformed(doc, "near", 0, 0, -5, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(far_e));
    ASSERT_TRUE(break_editor_entity_id_valid(mid_e));
    ASSERT_TRUE(break_editor_entity_id_valid(near_e));
    break_editor_doc_clear_dirty(doc);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam); /* eye (0,0,5), forward -Z */
    BreakEditorPickResult res;
    ASSERT_TRUE(break_editor_viewport_pick(doc, &cam, 400, 300, 800, 600,
                                           &res));
    ASSERT_TRUE(break_editor_entity_id_eq(res.id, near_e));
    /* Ray: origin (0,0,5), dir (0,0,-1); near proxy front face z = -4.5. */
    ASSERT_FLOAT_EQ(res.t, 9.5f, 1e-3f);

    /* Picking performs no document mutation. */
    ASSERT_EQ(break_editor_doc_entity_count(doc), 3u);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    break_editor_doc_destroy(doc);
}

TEST(pick_miss) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    /* Empty doc: bounded false. */
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    BreakEditorPickResult res;
    ASSERT_FALSE(break_editor_viewport_pick(doc, &cam, 400, 300, 800, 600,
                                            &res));

    /* Entity far off the center ray: corner ray misses. */
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, -5, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));
    ASSERT_FALSE(break_editor_viewport_pick(doc, &cam, 0, 0, 800, 600, &res));
    /* ...but the center ray hits it. */
    ASSERT_TRUE(break_editor_viewport_pick(doc, &cam, 400, 300, 800, 600,
                                           &res));
    ASSERT_TRUE(break_editor_entity_id_eq(res.id, e));

    break_editor_doc_destroy(doc);
}

TEST(pick_skips_entities_without_transform) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    /* A has no transform (skipped); B and D do; C has none. The BVH
     * object_index maps back through the compacted proxy array, so the
     * result must be B even though B is not doc row 0. */
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    BreakEditorEntityId b = add_transformed(doc, "b", 0, 0, -5, 1, 1, 1);
    BreakEditorEntityId c = break_editor_doc_add_entity(doc, "c");
    BreakEditorEntityId d = add_transformed(doc, "d", 0, 0, -10, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_entity_id_valid(b));
    ASSERT_TRUE(break_editor_entity_id_valid(c));
    ASSERT_TRUE(break_editor_entity_id_valid(d));

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    BreakEditorPickResult res;
    ASSERT_TRUE(break_editor_viewport_pick(doc, &cam, 400, 300, 800, 600,
                                           &res));
    ASSERT_TRUE(break_editor_entity_id_eq(res.id, b));
    ASSERT_FLOAT_EQ(res.t, 9.5f, 1e-3f);

    /* Remove every transform: the ray hits nothing. */
    ASSERT_TRUE(break_editor_doc_remove_component(
        doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_remove_component(
        doc, d, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_FALSE(break_editor_viewport_pick(doc, &cam, 400, 300, 800, 600,
                                            &res));

    break_editor_doc_destroy(doc);
}

TEST(pick_degenerate_viewport_false) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, -5, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    BreakEditorPickResult res;
    ASSERT_FALSE(break_editor_viewport_pick(doc, &cam, 400, 300, 0, 600,
                                            &res));
    ASSERT_FALSE(break_editor_viewport_pick(doc, &cam, 400, 300, 800, 0,
                                            &res));
    ASSERT_FALSE(break_editor_viewport_pick(doc, &cam, NAN, 300, 800, 600,
                                            &res));
    ASSERT_FALSE(break_editor_viewport_pick(NULL, &cam, 400, 300, 800, 600,
                                            &res));
    ASSERT_FALSE(break_editor_viewport_pick(doc, NULL, 400, 300, 800, 600,
                                            &res));
    ASSERT_FALSE(break_editor_viewport_pick(doc, &cam, 400, 300, 800, 600,
                                            NULL));

    break_editor_doc_destroy(doc);
}

TEST(focus_sets_target_and_distance) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "hero", 10, 20, 30,
                                            2, 4, 2);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    cam.yaw = ED_DEG2RAD(30.0);
    cam.pitch = ED_DEG2RAD(15.0);
    break_editor_camera_focus(&cam, doc, e);

    /* target = proxy center = pos; half-extents (1,2,1) -> radius sqrt(6);
     * distance = radius / tan(fov/2), within [0.05, 1e4]. yaw/pitch kept. */
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 10, 20, 30, 0);
    f32 want = sqrtf(6.0f) / ED_TAN30;
    ASSERT_FLOAT_EQ(cam.distance, want, 1e-3f);
    ASSERT_TRUE(cam.distance >= 0.05f && cam.distance <= 1e4f);
    ASSERT_FLOAT_EQ(cam.yaw, ED_DEG2RAD(30.0), 1e-6f);
    ASSERT_FLOAT_EQ(cam.pitch, ED_DEG2RAD(15.0), 1e-6f);

    break_editor_doc_destroy(doc);
}

TEST(focus_clamps_and_noop_paths) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    /* Huge proxy -> distance clamps to 1e4. */
    BreakEditorEntityId big = add_transformed(doc, "big", 0, 0, 0,
                                              1e5f, 1e5f, 1e5f);
    ASSERT_TRUE(break_editor_entity_id_valid(big));
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    break_editor_camera_focus(&cam, doc, big);
    ASSERT_FLOAT_EQ(cam.distance, 1e4f, 0.0f);

    /* Minimum-size proxy (scale 0 -> half clamp 0.05 per axis) with a very
     * wide fov -> radius / tan(fov/2) < 0.05 -> clamps to 0.05. */
    BreakEditorEntityId tiny = add_transformed(doc, "tiny", 1, 2, 3,
                                               0, 0, 0);
    ASSERT_TRUE(break_editor_entity_id_valid(tiny));
    break_editor_camera_init(&cam);
    cam.fov_y = ED_DEG2RAD(170.0);
    break_editor_camera_focus(&cam, doc, tiny);
    ASSERT_FLOAT_EQ(cam.distance, 0.05f, 0.0f);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 1, 2, 3, 0);

    /* Entity without a transform: bounded no-op. */
    BreakEditorEntityId bare = break_editor_doc_add_entity(doc, "bare");
    ASSERT_TRUE(break_editor_entity_id_valid(bare));
    break_editor_camera_init(&cam);
    BreakEditorCamera before = cam;
    break_editor_camera_focus(&cam, doc, bare);
    ASSERT_TRUE(memcmp(&cam, &before, sizeof(cam)) == 0);

    /* Stale id (wrong generation): bounded no-op. */
    BreakEditorEntityId stale = { bare.index, bare.generation + 1u };
    break_editor_camera_focus(&cam, doc, stale);
    ASSERT_TRUE(memcmp(&cam, &before, sizeof(cam)) == 0);

    /* NULL args: no crash, no change. */
    break_editor_camera_focus(NULL, doc, big);
    break_editor_camera_focus(&cam, NULL, big);
    break_editor_camera_focus(&cam, doc, BREAK_EDITOR_ENTITY_NULL);
    ASSERT_TRUE(memcmp(&cam, &before, sizeof(cam)) == 0);

    break_editor_doc_destroy(doc);
}

TEST(orbit_clamps_pitch) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    break_editor_camera_orbit(&cam, 30.0f, 0.0f);
    ASSERT_FLOAT_EQ(cam.yaw, ED_DEG2RAD(30.0), 1e-6f);
    ASSERT_FLOAT_EQ(cam.pitch, 0.0f, 0.0f);

    /* Pitch clamps at +/-89 deg. */
    break_editor_camera_orbit(&cam, 0.0f, 200.0f);
    ASSERT_FLOAT_EQ(cam.pitch, ED_DEG2RAD(89.0), 1e-6f);
    break_editor_camera_orbit(&cam, 0.0f, -500.0f);
    ASSERT_FLOAT_EQ(cam.pitch, ED_DEG2RAD(-89.0), 1e-6f);
    /* A small delta inside the range applies 1:1. */
    break_editor_camera_orbit(&cam, -15.0f, 10.0f);
    ASSERT_FLOAT_EQ(cam.yaw, ED_DEG2RAD(15.0), 1e-5f);
    ASSERT_FLOAT_EQ(cam.pitch, ED_DEG2RAD(-79.0), 1e-5f);

    /* Target/distance untouched; non-finite deltas ignored. */
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 0, 0, 0, 0);
    ASSERT_FLOAT_EQ(cam.distance, 5.0f, 1e-6f);
    f32 yaw = cam.yaw, pitch = cam.pitch;
    break_editor_camera_orbit(&cam, NAN, 0.0f);
    break_editor_camera_orbit(&cam, 0.0f, INFINITY);
    ASSERT_FLOAT_EQ(cam.yaw, yaw, 0.0f);
    ASSERT_FLOAT_EQ(cam.pitch, pitch, 0.0f);
}

TEST(pan_scales_with_distance) {
    /* world-units per pixel at the pivot plane:
     * 2 * distance * tan(fov/2) / 720. */
    BreakEditorCamera cam;
    break_editor_camera_init(&cam); /* distance 5, fov 60 */
    break_editor_camera_pan(&cam, 36.0f, 0.0f);
    /* Drag right moves the target along -right; default right = +X. */
    ASSERT_FLOAT_EQ(cam.target[0], -0.28867513f, 1e-5f);
    ASSERT_FLOAT_EQ(cam.target[1], 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(cam.target[2], 0.0f, 0.0f);

    /* Drag down (screen y down) moves the target along +up (default +Y). */
    break_editor_camera_init(&cam);
    break_editor_camera_pan(&cam, 0.0f, 72.0f);
    ASSERT_FLOAT_EQ(cam.target[0], 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(cam.target[1], 0.57735027f, 1e-5f);
    ASSERT_FLOAT_EQ(cam.target[2], 0.0f, 0.0f);

    /* Double the distance doubles the displacement (proportionality). */
    BreakEditorCamera far_cam;
    break_editor_camera_init(&far_cam);
    far_cam.distance = 10.0f;
    break_editor_camera_pan(&far_cam, 36.0f, 0.0f);
    ASSERT_FLOAT_EQ(far_cam.target[0], -0.57735027f, 1e-5f);

    /* Non-finite deltas are ignored. */
    break_editor_camera_init(&cam);
    break_editor_camera_pan(&cam, NAN, 1.0f);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 0, 0, 0, 0);
}

TEST(zoom_exponential_clamped) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    /* Positive wheel delta zooms in exponentially: d *= exp(-0.1). */
    break_editor_camera_zoom(&cam, 1.0f);
    ASSERT_FLOAT_EQ(cam.distance, 4.5241871f, 1e-4f);
    break_editor_camera_init(&cam);
    break_editor_camera_zoom(&cam, -1.0f);
    ASSERT_FLOAT_EQ(cam.distance, 5.5258549f, 1e-4f);

    /* Clamped at 1e4 above and 0.05 below. */
    cam.distance = 1e4f;
    break_editor_camera_zoom(&cam, -1.0f);
    ASSERT_FLOAT_EQ(cam.distance, 1e4f, 0.0f);
    break_editor_camera_init(&cam);
    break_editor_camera_zoom(&cam, 200.0f);
    ASSERT_FLOAT_EQ(cam.distance, 0.05f, 0.0f);

    /* Non-finite delta ignored. */
    break_editor_camera_init(&cam);
    break_editor_camera_zoom(&cam, NAN);
    ASSERT_FLOAT_EQ(cam.distance, 5.0f, 1e-6f);
}

TEST(pick_oom_budget_sweep) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, -5, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));
    break_editor_doc_clear_dirty(doc);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    /* Pick takes three editor-owned allocations (proxy AABB array, entity
     * id map, BVH struct): budgets 0..2 fail bounded, 3 is first success.
     * bvh.c's internal allocations belong to the bvh TU and are unhooked. */
    for (u64 budget = 0; budget < 3; budget++) {
        break_editor_test_set_alloc_budget(budget);
        BreakEditorPickResult res;
        bool hit = break_editor_viewport_pick(doc, &cam, 400, 300, 800, 600,
                                              &res);
        break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
        ASSERT_FALSE(hit);
    }

    break_editor_test_set_alloc_budget(3);
    BreakEditorPickResult res;
    bool hit = break_editor_viewport_pick(doc, &cam, 400, 300, 800, 600,
                                          &res);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_TRUE(hit);
    ASSERT_TRUE(break_editor_entity_id_eq(res.id, e));
    ASSERT_FLOAT_EQ(res.t, 9.5f, 1e-3f);

    /* OOM left the document untouched. */
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    break_editor_doc_destroy(doc);
}

TEST(box_select_center_inside_rect) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    /* Camera eye (0,0,5) looking -Z; 800x600 viewport. */
    BreakEditorEntityId center = add_transformed(doc, "c", 0, 0, 0, 1, 1, 1);
    BreakEditorEntityId right = add_transformed(doc, "r", 2, 0, 0, 1, 1, 1);
    BreakEditorEntityId behind = add_transformed(doc, "b", 0, 0, 10, 1, 1, 1);
    BreakEditorEntityId bare = break_editor_doc_add_entity(doc, "bare");
    ASSERT_TRUE(break_editor_entity_id_valid(center));
    ASSERT_TRUE(break_editor_entity_id_valid(right));
    ASSERT_TRUE(break_editor_entity_id_valid(behind));
    ASSERT_TRUE(break_editor_entity_id_valid(bare));
    break_editor_doc_clear_dirty(doc);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    BreakEditorEntityId ids[8];

    /* Small box around the screen center: only the centered entity (the
     * entity behind the eye projects to the center too but is culled). */
    u32 n = break_editor_viewport_box_select(doc, &cam, 380, 280, 420, 320,
                                             800, 600, ids, 8);
    ASSERT_EQ(n, 1u);
    ASSERT_TRUE(break_editor_entity_id_eq(ids[0], center));

    /* Corners given in reverse order normalize; the wide box takes both
     * in-front entities in document order. x=2 at depth 5 projects to
     * 400 + 2/(5*tan30) * 300 ~= 607.8 px. */
    n = break_editor_viewport_box_select(doc, &cam, 700, 350, 100, 250,
                                         800, 600, ids, 8);
    ASSERT_EQ(n, 2u);
    ASSERT_TRUE(break_editor_entity_id_eq(ids[0], center));
    ASSERT_TRUE(break_editor_entity_id_eq(ids[1], right));

    /* Capacity bounds the output; the return is the stored count. */
    n = break_editor_viewport_box_select(doc, &cam, 100, 250, 700, 350,
                                         800, 600, ids, 1);
    ASSERT_EQ(n, 1u);
    ASSERT_TRUE(break_editor_entity_id_eq(ids[0], center));

    /* Box that excludes the center but keeps the right entity. */
    n = break_editor_viewport_box_select(doc, &cam, 590, 280, 630, 320,
                                         800, 600, ids, 8);
    ASSERT_EQ(n, 1u);
    ASSERT_TRUE(break_editor_entity_id_eq(ids[0], right));

    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    break_editor_doc_destroy(doc);
}

TEST(box_select_degenerate_bounded_zero) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_entity_id_valid(
        add_transformed(doc, "c", 0, 0, 0, 1, 1, 1)));
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    BreakEditorEntityId ids[4];
    ASSERT_EQ(break_editor_viewport_box_select(NULL, &cam, 0, 0, 800, 600,
                                               800, 600, ids, 4), 0u);
    ASSERT_EQ(break_editor_viewport_box_select(doc, NULL, 0, 0, 800, 600,
                                               800, 600, ids, 4), 0u);
    ASSERT_EQ(break_editor_viewport_box_select(doc, &cam, 0, 0, 800, 600,
                                               800, 600, NULL, 4), 0u);
    ASSERT_EQ(break_editor_viewport_box_select(doc, &cam, 0, 0, 800, 600,
                                               800, 600, ids, 0), 0u);
    ASSERT_EQ(break_editor_viewport_box_select(doc, &cam, 0, 0, 800, 600,
                                               0, 600, ids, 4), 0u);
    ASSERT_EQ(break_editor_viewport_box_select(doc, &cam, NAN, 0, 800, 600,
                                               800, 600, ids, 4), 0u);
    cam.distance = 0.0f;
    ASSERT_EQ(break_editor_viewport_box_select(doc, &cam, 0, 0, 800, 600,
                                               800, 600, ids, 4), 0u);
    break_editor_camera_init(&cam);
    ASSERT_EQ(break_editor_viewport_box_select(doc, &cam, 0, 0, 800, 600,
                                               800, 600, ids, 4), 1u);
    break_editor_doc_destroy(doc);
}

TEST(fly_moves_target_along_camera_axes) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam); /* eye (0,0,5), forward -Z, right +X */
    break_editor_camera_fly(&cam, 1.0f, 0.0f, 0.0f);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 0, 0, -1, 1e-5f);
    break_editor_camera_fly(&cam, 0.0f, 2.0f, 0.0f);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 2, 0, -1, 1e-5f);
    break_editor_camera_fly(&cam, 0.0f, 0.0f, -0.5f);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 2, -0.5f, -1, 1e-5f);
    /* the eye moves with the target: orientation and distance unchanged */
    ASSERT_FLOAT_EQ(cam.yaw, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(cam.pitch, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(cam.distance, 5.0f, 1e-6f);

    /* yawed 90 deg: eye on +X, forward -X, right -Z; pitched down keeps
     * forward moves along the view direction (it has a Y part) */
    break_editor_camera_init(&cam);
    cam.yaw = ED_DEG2RAD(90);
    break_editor_camera_fly(&cam, 1.0f, 1.0f, 0.0f);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], -1, 0, -1, 1e-5f);
    break_editor_camera_init(&cam);
    cam.pitch = ED_DEG2RAD(30);
    break_editor_camera_fly(&cam, 2.0f, 0.0f, 0.0f);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2],
                0, -1.0f, -2.0f * 0.8660254f, 1e-5f);

    /* bounded no-ops */
    break_editor_camera_init(&cam);
    break_editor_camera_fly(&cam, NAN, 0.0f, 0.0f);
    break_editor_camera_fly(&cam, 0.0f, INFINITY, 0.0f);
    break_editor_camera_fly(NULL, 1.0f, 0.0f, 0.0f);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 0, 0, 0, 0.0f);
}

TEST(fly_step_scales_with_distance) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    ASSERT_FLOAT_EQ(break_editor_camera_fly_step(&cam),
                    5.0f * BREAK_EDITOR_CAMERA_FLY_STEP_FRACTION, 1e-6f);
    cam.distance = BREAK_EDITOR_CAMERA_MIN_DISTANCE;
    ASSERT_TRUE(break_editor_camera_fly_step(&cam) >=
                BREAK_EDITOR_CAMERA_FLY_MIN_STEP);
    ASSERT_FLOAT_EQ(break_editor_camera_fly_step(NULL), 0.0f, 0.0f);
}

TEST(focus_many_fits_the_union_of_proxies) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = add_transformed(doc, "a", -3, 0, 0, 1, 1, 1);
    BreakEditorEntityId b = add_transformed(doc, "b", 3, 0, 0, 1, 1, 1);
    BreakEditorEntityId bare = break_editor_doc_add_entity(doc, "bare");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_entity_id_valid(b));
    BreakEditorEntityId ids[3] = { a, bare, b };

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    cam.yaw = ED_DEG2RAD(20.0);
    break_editor_camera_focus_many(&cam, doc, ids, 3u);
    /* union box x [-3.5, 3.5], y/z [-0.5, 0.5]: center origin, half
     * extents (3.5, 0.5, 0.5); entities without a transform are ignored */
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 0, 0, 0, 1e-6f);
    f32 r = sqrtf(3.5f * 3.5f + 0.25f + 0.25f);
    ASSERT_FLOAT_EQ(cam.distance, r / ED_TAN30, 1e-3f);
    ASSERT_FLOAT_EQ(cam.yaw, ED_DEG2RAD(20.0), 1e-6f);

    /* a single id matches break_editor_camera_focus */
    BreakEditorCamera one;
    break_editor_camera_init(&one);
    break_editor_camera_init(&cam);
    break_editor_camera_focus(&one, doc, b);
    break_editor_camera_focus_many(&cam, doc, &b, 1u);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2],
                one.target[0], one.target[1], one.target[2], 0.0f);
    ASSERT_FLOAT_EQ(cam.distance, one.distance, 0.0f);

    /* nothing focusable / bad args: untouched */
    break_editor_camera_init(&cam);
    break_editor_camera_focus_many(&cam, doc, &bare, 1u);
    break_editor_camera_focus_many(&cam, doc, NULL, 2u);
    break_editor_camera_focus_many(&cam, doc, ids, 0u);
    break_editor_camera_focus_many(&cam, NULL, ids, 3u);
    assert_vec3(cam.target[0], cam.target[1], cam.target[2], 0, 0, 0, 0.0f);
    ASSERT_FLOAT_EQ(cam.distance, 5.0f, 0.0f);
    break_editor_doc_destroy(doc);
}

static bool skip_id(void *user, BreakEditorEntityId id) {
    return break_editor_entity_id_eq(*(const BreakEditorEntityId *)user, id);
}

TEST(pick_and_box_select_honor_a_skip_filter) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId near_e = add_transformed(doc, "near", 0, 0, -5, 1, 1, 1);
    BreakEditorEntityId far_e = add_transformed(doc, "far", 0, 0, -10, 1, 1, 1);
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    BreakEditorPickResult res;
    /* skipping the near one picks through it */
    ASSERT_TRUE(break_editor_viewport_pick_ex(doc, &cam, 400, 300, 800, 600,
                                              skip_id, &near_e, &res));
    ASSERT_TRUE(break_editor_entity_id_eq(res.id, far_e));
    /* NULL filter = plain pick */
    ASSERT_TRUE(break_editor_viewport_pick_ex(doc, &cam, 400, 300, 800, 600,
                                              NULL, NULL, &res));
    ASSERT_TRUE(break_editor_entity_id_eq(res.id, near_e));
    BreakEditorEntityId ids[4];
    ASSERT_EQ(break_editor_viewport_box_select_ex(doc, &cam, 300, 200, 500,
                                                  400, 800, 600, skip_id,
                                                  &far_e, ids, 4), 1u);
    ASSERT_TRUE(break_editor_entity_id_eq(ids[0], near_e));
    ASSERT_EQ(break_editor_viewport_box_select(doc, &cam, 300, 200, 500, 400,
                                               800, 600, ids, 4), 2u);
    break_editor_doc_destroy(doc);
}

TEST_MAIN_BEGIN()
    RUN_TEST(camera_init_defaults);
    RUN_TEST(camera_view_known_answers);
    RUN_TEST(camera_proj_known_answers);
    RUN_TEST(screen_ray_center_equals_forward);
    RUN_TEST(screen_ray_corners_diverge);
    RUN_TEST(screen_ray_degenerate_bounded_false);
    RUN_TEST(pick_nearest_of_three_on_ray);
    RUN_TEST(pick_miss);
    RUN_TEST(pick_skips_entities_without_transform);
    RUN_TEST(pick_degenerate_viewport_false);
    RUN_TEST(focus_sets_target_and_distance);
    RUN_TEST(focus_clamps_and_noop_paths);
    RUN_TEST(orbit_clamps_pitch);
    RUN_TEST(pan_scales_with_distance);
    RUN_TEST(zoom_exponential_clamped);
    RUN_TEST(pick_oom_budget_sweep);
    RUN_TEST(box_select_center_inside_rect);
    RUN_TEST(box_select_degenerate_bounded_zero);
    RUN_TEST(fly_moves_target_along_camera_axes);
    RUN_TEST(fly_step_scales_with_distance);
    RUN_TEST(focus_many_fits_the_union_of_proxies);
    RUN_TEST(pick_and_box_select_honor_a_skip_filter);
TEST_MAIN_END()
