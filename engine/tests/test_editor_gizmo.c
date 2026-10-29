/* Stage 4 scene editor Phase 2 Task 2: gizmo state machine tests — pure CPU.
 *
 * Covers the brief checkboxes: mode/attach/detach; handle layout
 * known-answers (fixed default camera: exact handle AABBs from the pinned
 * screen-constant sizing formula); hit-test per part incl. misses;
 * translate X/Y known-answer drags (fixed camera, known pixels -> known
 * world delta); CENTER plane translate; rotate drag (sign convention: drag
 * right = +degrees on the axis field, 0.5 deg/px); scale axis/center drags
 * (base-2 exponential, clamp >= 0.01); single-command undo/redo semantics
 * (one undo reverts a whole multi-field drag); drag with no attach -> false;
 * begin_drag miss -> false; degenerate axis/ray parallelism -> bounded
 * false; NaN/Inf guards; OOM budget sweeps (create + begin_drag command
 * allocation; end_drag commits with a zero budget because push_applied never
 * allocates); mid-drag policies (set_mode/attach/detach/destroy implicitly
 * end + commit; entity removal mid-drag discards).
 *
 * Fixed test camera: the default BreakEditorCamera (eye (0,0,5), target
 * origin, fov 60 deg) and an 800x600 viewport. World->pixel helper inverts
 * the same public view/proj matrices the core uses for screen_ray; several
 * pixels are ALSO pinned as literals so the camera geometry itself is
 * covered. */

#include "test_framework.h"

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_gizmo.h>
#include <editor/editor_test_hooks.h>

#include <float.h>
#include <math.h>
#include <string.h>

#define ED_PI 3.14159265358979323846
#define ED_DEG2RAD(d) ((f32)(d) * (f32)(ED_PI / 180.0))
#define TAN30 0.5773502691896258f
#define VW 800.0f
#define VH 600.0f

/* Default-camera scale_base for a pivot at the origin: 5 * tan(30 deg). */
#define SB0 2.886751345948129f
/* Pinned handle dimensions at SB0 (editor_gizmo.h header formula). */
#define GAP0 (0.04f * SB0)    /* 0.11547005 */
#define LEN0 (0.20f * SB0)    /* 0.57735027 */
#define THICK0 (0.016f * SB0) /* 0.04618802 */

static void assert_vec3(f32 ax, f32 ay, f32 az,
                        f32 bx, f32 by, f32 bz, f32 eps) {
    ASSERT_FLOAT_EQ(ax, bx, eps);
    ASSERT_FLOAT_EQ(ay, by, eps);
    ASSERT_FLOAT_EQ(az, bz, eps);
}

/* Column-vector M*v (e[col][row]) — same convention as the Task 1 test. */
static void mul4(const f32 m[16], const f32 v[4], f32 out[4]) {
    for (int i = 0; i < 4; i++) {
        out[i] = m[0 * 4 + i] * v[0] + m[1 * 4 + i] * v[1] +
                 m[2 * 4 + i] * v[2] + m[3 * 4 + i] * v[3];
    }
}

/* world -> viewport pixel (top-left origin) through the public matrices. */
static bool world_to_px(const BreakEditorCamera *cam,
                        f32 wx, f32 wy, f32 wz,
                        f32 *out_x, f32 *out_y) {
    f32 view[16], proj[16];
    break_editor_camera_view(cam, view);
    break_editor_camera_proj(cam, VW / VH, proj);
    f32 v[4] = { wx, wy, wz, 1.0f }, t[4], c[4];
    mul4(view, v, t);
    mul4(proj, t, c);
    if (!(c[3] > 0.0f)) return false; /* behind the camera */
    f32 ndc_x = c[0] / c[3], ndc_y = c[1] / c[3];
    *out_x = (ndc_x + 1.0f) * 0.5f * VW;
    *out_y = (1.0f - ndc_y) * 0.5f * VH;
    return true;
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

static void read_pos(BreakEditorDoc *doc, BreakEditorEntityId id, f32 out[3]) {
    for (u32 k = 0; k < 3; k++) {
        ASSERT_TRUE(break_editor_doc_get_field_f32(
            doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, k, &out[k]));
    }
}

static void read_scale(BreakEditorDoc *doc, BreakEditorEntityId id,
                       f32 out[3]) {
    for (u32 k = 0; k < 3; k++) {
        ASSERT_TRUE(break_editor_doc_get_field_f32(
            doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 6u + k, &out[k]));
    }
}

static u32 stack_size(BreakEditorDoc *doc) {
    return break_editor_cmd_stack_size(break_editor_doc_stack(doc));
}

/* Pinned pixel literals for the fixed camera (800x600, default camera). */
TEST(pixel_helper_known_answers) {
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 x, y;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &x, &y));
    ASSERT_FLOAT_EQ(x, 441.5692f, 1e-2f);
    ASSERT_FLOAT_EQ(y, 300.0f, 1e-2f);
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &x, &y));
    ASSERT_FLOAT_EQ(x, 493.5307f, 1e-2f);
    ASSERT_TRUE(world_to_px(&cam, 0, 0.4f, 0, &x, &y));
    ASSERT_FLOAT_EQ(x, 400.0f, 1e-2f);
    ASSERT_FLOAT_EQ(y, 258.4308f, 1e-2f);
    ASSERT_TRUE(world_to_px(&cam, 0.08f, 0.05f, 0, &x, &y));
    ASSERT_FLOAT_EQ(x, 408.3138f, 1e-2f);
    ASSERT_FLOAT_EQ(y, 294.8038f, 1e-2f);
    ASSERT_TRUE(world_to_px(&cam, 2.0f, 0, 0, &x, &y));
    ASSERT_FLOAT_EQ(x, 607.8461f, 1e-2f);
}

TEST(create_defaults_and_mode_none_hides) {
    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    /* Fresh gizmo: mode NONE, detached — no handles even after attach. */
    break_editor_gizmo_attach(g, doc, e);
    BreakEditorGizmoHandle h[BREAK_EDITOR_GIZMO_MAX_HANDLES];
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 0u);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, 441.5692f, 300,
                                               VW, VH));

    /* NULL robustness: no crashes. */
    break_editor_gizmo_set_mode(NULL, BREAK_EDITOR_GIZMO_TRANSLATE);
    break_editor_gizmo_attach(NULL, doc, e);
    break_editor_gizmo_set_view(NULL, &cam);
    ASSERT_EQ(break_editor_gizmo_handles(NULL, h, 24), 0u);
    ASSERT_EQ(break_editor_gizmo_hit(NULL, &cam, 0, 0, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    ASSERT_FALSE(break_editor_gizmo_begin_drag(NULL, &cam, 0, 0, VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(NULL, &cam, 0, 0, VW, VH));
    break_editor_gizmo_end_drag(NULL);
    break_editor_gizmo_destroy(NULL);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(mode_attach_detach) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    BreakEditorEntityId bare = break_editor_doc_add_entity(doc, "bare");
    ASSERT_TRUE(break_editor_entity_id_valid(e));
    ASSERT_TRUE(break_editor_entity_id_valid(bare));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    BreakEditorGizmoHandle h[BREAK_EDITOR_GIZMO_MAX_HANDLES];

    /* Every non-NONE mode shows 4 handles while attached. */
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_ROTATE);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_SCALE);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_NONE);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 0u);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    /* Detach via NULL doc and via the null id. */
    break_editor_gizmo_attach(g, NULL, e);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 0u);
    break_editor_gizmo_attach(g, doc, e);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    break_editor_gizmo_attach(g, doc, BREAK_EDITOR_ENTITY_NULL);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 0u);

    /* Attaching an entity without a transform: attached but no geometry
     * until a transform exists (read live per call). */
    break_editor_gizmo_attach(g, doc, bare);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 0u);
    ASSERT_TRUE(break_editor_doc_add_component(doc, bare,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);

    /* Stale id after the attached entity is removed: fully inert. */
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, bare));
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 0u);
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, 441.5692f, 300,
                                               VW, VH));

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(handle_layout_known_answers) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    /* Before any camera call the cache holds the default-camera value, which
     * equals the fixed test camera's scale at an origin pivot. */
    BreakEditorGizmoHandle h[24];
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);

    /* Order pinned: X, Y, Z, CENTER. */
    ASSERT_EQ(h[0].part, BREAK_EDITOR_GIZMO_PART_X);
    ASSERT_EQ(h[1].part, BREAK_EDITOR_GIZMO_PART_Y);
    ASSERT_EQ(h[2].part, BREAK_EDITOR_GIZMO_PART_Z);
    ASSERT_EQ(h[3].part, BREAK_EDITOR_GIZMO_PART_CENTER);

    assert_vec3(h[0].aabb_min[0], h[0].aabb_min[1], h[0].aabb_min[2],
                GAP0, -THICK0, -THICK0, 1e-5f);
    assert_vec3(h[0].aabb_max[0], h[0].aabb_max[1], h[0].aabb_max[2],
                GAP0 + LEN0, THICK0, THICK0, 1e-5f);
    assert_vec3(h[1].aabb_min[0], h[1].aabb_min[1], h[1].aabb_min[2],
                -THICK0, GAP0, -THICK0, 1e-5f);
    assert_vec3(h[1].aabb_max[0], h[1].aabb_max[1], h[1].aabb_max[2],
                THICK0, GAP0 + LEN0, THICK0, 1e-5f);
    assert_vec3(h[2].aabb_min[0], h[2].aabb_min[1], h[2].aabb_min[2],
                -THICK0, -THICK0, GAP0, 1e-5f);
    assert_vec3(h[2].aabb_max[0], h[2].aabb_max[1], h[2].aabb_max[2],
                THICK0, THICK0, GAP0 + LEN0, 1e-5f);
    assert_vec3(h[3].aabb_min[0], h[3].aabb_min[1], h[3].aabb_min[2],
                -GAP0, -GAP0, -GAP0, 1e-5f);
    assert_vec3(h[3].aabb_max[0], h[3].aabb_max[1], h[3].aabb_max[2],
                GAP0, GAP0, GAP0, 1e-5f);

    /* Capacity handling: writes min(4, capacity), returns the count. */
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 2), 2u);
    ASSERT_EQ(h[0].part, BREAK_EDITOR_GIZMO_PART_X);
    ASSERT_EQ(h[1].part, BREAK_EDITOR_GIZMO_PART_Y);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 0), 0u);
    ASSERT_EQ(break_editor_gizmo_handles(g, NULL, 24), 0u);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(handles_track_pivot_and_view_scale) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    /* Double the camera distance: world handle size doubles (screen-constant
     * formula scale_base = |eye - pivot| * tan(fov/2)). */
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    cam.distance = 10.0f; /* eye (0,0,10); pivot origin: |eye-pivot| = 10 */
    break_editor_gizmo_set_view(g, &cam);
    BreakEditorGizmoHandle h[24];
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    f32 sb = 10.0f * TAN30;
    assert_vec3(h[0].aabb_min[0], h[0].aabb_min[1], h[0].aabb_min[2],
                0.04f * sb, -0.016f * sb, -0.016f * sb, 1e-4f);
    assert_vec3(h[0].aabb_max[0], h[0].aabb_max[1], h[0].aabb_max[2],
                0.24f * sb, 0.016f * sb, 0.016f * sb, 1e-4f);

    /* Moving the pivot moves the handles; |eye - pivot| is the 3D distance
     * (here sqrt(10^2 + 10^2)), not the camera distance. */
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, 10.0f));
    break_editor_gizmo_set_view(g, &cam);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    f32 sb2 = sqrtf(200.0f) * TAN30;
    assert_vec3(h[0].aabb_min[0], h[0].aabb_min[1], h[0].aabb_min[2],
                10.0f + 0.04f * sb2, -0.016f * sb2, -0.016f * sb2, 1e-3f);

    /* hit() also refreshes the cache: back to the default camera (eye
     * (0,0,5)); |eye - pivot(10,0,0)| = sqrt(125) = 11.18. */
    break_editor_camera_init(&cam);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 0, 0, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE); /* pivot at (10,0,0): corner misses */
    f32 sb3 = sqrtf(125.0f) * TAN30;
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    assert_vec3(h[0].aabb_min[0], h[0].aabb_min[1], h[0].aabb_min[2],
                10.0f + 0.04f * sb3, -0.016f * sb3, -0.016f * sb3, 1e-3f);

    /* A degenerate camera refresh keeps the previous cache. */
    BreakEditorCamera bad;
    break_editor_camera_init(&bad);
    bad.fov_y = 0.0f;
    break_editor_gizmo_set_view(g, &bad);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    assert_vec3(h[0].aabb_min[0], h[0].aabb_min[1], h[0].aabb_min[2],
                10.0f + 0.04f * sb3, -0.016f * sb3, -0.016f * sb3, 1e-3f);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(hit_test_per_part_and_misses) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    /* Per-part hits (pixels are the projections of known world points). */
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_X);   /* ray through (0.4,0,0) */
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 400, 258.4308f, VW, VH),
              BREAK_EDITOR_GIZMO_PART_Y);   /* ray through (0,0.4,0) */
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 400, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_Z);   /* Z handle occludes CENTER here */
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 408.3138f, 294.8038f, VW, VH),
              BREAK_EDITOR_GIZMO_PART_CENTER); /* ray through (0.08,0.05,0) */

    /* Misses: ray through (2,0,0) passes the X handle; ray through
     * (0.4,0.2,0) passes just above it; far corner hits nothing. */
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 607.8461f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 279.2154f, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 790, 10, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);

    /* Same boxes in the other modes. */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_ROTATE);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_X);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_SCALE);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 400, 258.4308f, VW, VH),
              BREAK_EDITOR_GIZMO_PART_Y);

    /* NONE mode / detached / degenerate inputs: NONE. */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_NONE);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);
    break_editor_gizmo_attach(g, NULL, e);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    break_editor_gizmo_attach(g, doc, e);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 300, 0, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, NAN, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    ASSERT_EQ(break_editor_gizmo_hit(g, NULL, 441.5692f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(translate_x_drag_known_answer) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));
    break_editor_doc_clear_dirty(doc);

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    /* Live write: the field moves with the drag BEFORE end_drag; the undo
     * stack is untouched until commit. */
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.5f, 0, 0, 1e-3f);
    ASSERT_EQ(stack_size(doc), size0);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.5f, 0, 0, 1e-3f);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(translate_y_drag_known_answer) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0, 0.4f, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0, 0.9f, 0, &bx, &by));

    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    break_editor_gizmo_end_drag(g);
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0.5f, 0, 1e-3f);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(translate_center_plane_known_answer) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    /* CENTER = free translate in the camera-facing plane (z = 0 here):
     * grab (0.08,0.05,0), release at (0.58,0.35,0) -> delta (0.5,0.3,0). */
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.08f, 0.05f, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.58f, 0.35f, 0, &bx, &by));

    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    break_editor_gizmo_end_drag(g);
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.5f, 0.3f, 0, 1e-3f);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(single_undo_reverts_whole_drag) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));
    break_editor_doc_clear_dirty(doc);

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, b1x, b1y, b2x, b2y, b3x, b3y;
    ASSERT_TRUE(world_to_px(&cam, 0.08f, 0.05f, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.28f, 0.15f, 0, &b1x, &b1y));
    ASSERT_TRUE(world_to_px(&cam, 0.58f, 0.35f, 0, &b2x, &b2y));
    ASSERT_TRUE(world_to_px(&cam, 0.68f, 0.55f, 0, &b3x, &b3y));

    /* CENTER drag with THREE pointer moves: all coalesce into ONE command. */
    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, b1x, b1y, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, b2x, b2y, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, b3x, b3y, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0 + 1u);

    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.6f, 0.5f, 0, 1e-3f);

    /* ONE undo reverts the entire drag (both fields); one redo re-applies
     * the final state. */
    ASSERT_TRUE(break_editor_undo(doc));
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);
    ASSERT_TRUE(break_editor_redo(doc));
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.6f, 0.5f, 0, 1e-3f);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(rotate_drag_known_answer_and_sign) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_ROTATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, yx, yy;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0, 0.4f, 0, &yx, &yy));

    u32 size0 = stack_size(doc);
    /* Drag right +100 px on X: +50 deg on rot.x (field 3). */
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, ax + 100.0f, ay, VW, VH));
    f32 v;
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 3, &v));
    ASSERT_FLOAT_EQ(v, 50.0f, 1e-3f);
    /* Absolute-from-begin: drag back to -40 px -> -20 deg. */
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, ax - 40.0f, ay, VW, VH));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 3, &v));
    ASSERT_FLOAT_EQ(v, -20.0f, 1e-3f);
    /* Vertical movement alone changes nothing. */
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, ax - 40.0f, ay + 77.0f,
                                        VW, VH));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 3, &v));
    ASSERT_FLOAT_EQ(v, -20.0f, 1e-3f);
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0 + 1u);

    /* Other fields untouched; one undo restores rot.x. */
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 4, &v));
    ASSERT_FLOAT_EQ(v, 0.0f, 0.0f);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 3, &v));
    ASSERT_FLOAT_EQ(v, 0.0f, 0.0f);
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 3, &v));
    ASSERT_FLOAT_EQ(v, -20.0f, 1e-3f);

    /* Y axis edits rot.y (field 4). */
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, yx, yy, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, yx + 60.0f, yy, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 4, &v));
    ASSERT_FLOAT_EQ(v, 30.0f, 1e-3f);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(scale_axis_drag_known_answer) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 2, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_SCALE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    /* s - s0 = 0.5 -> factor 2^0.5; scale.x: 2 -> 2.8284271. */
    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    f32 s[3];
    read_scale(doc, e, s);
    assert_vec3(s[0], s[1], s[2], 2.8284271f, 1.0f, 1.0f, 1e-3f);

    ASSERT_TRUE(break_editor_undo(doc));
    read_scale(doc, e, s);
    assert_vec3(s[0], s[1], s[2], 2.0f, 1.0f, 1.0f, 0);
    ASSERT_TRUE(break_editor_redo(doc));
    read_scale(doc, e, s);
    assert_vec3(s[0], s[1], s[2], 2.8284271f, 1.0f, 1.0f, 1e-3f);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(scale_axis_clamps_to_min) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0,
                                            0.02f, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_SCALE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, -1.6f, 0, 0, &bx, &by));

    /* s - s0 = -2 -> factor 0.25 -> 0.005 -> clamped to 0.01. */
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    break_editor_gizmo_end_drag(g);
    f32 s[3];
    read_scale(doc, e, s);
    assert_vec3(s[0], s[1], s[2], 0.01f, 1.0f, 1.0f, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(scale_center_uniform_drag) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 2, 3, 4);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_SCALE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay;
    ASSERT_TRUE(world_to_px(&cam, 0.08f, 0.05f, 0, &ax, &ay));

    /* CENTER: uniform scale, +200 px = one octave -> (4,6,8); ONE undo
     * reverts all three fields. */
    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, ax + 200.0f, ay, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    f32 s[3];
    read_scale(doc, e, s);
    assert_vec3(s[0], s[1], s[2], 4.0f, 6.0f, 8.0f, 1e-3f);
    ASSERT_TRUE(break_editor_undo(doc));
    read_scale(doc, e, s);
    assert_vec3(s[0], s[1], s[2], 2.0f, 3.0f, 4.0f, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(scale_from_zero_is_bounded_noop) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 0, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));
    break_editor_doc_clear_dirty(doc);

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_SCALE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    /* Multiplicative drag from a zero old scale: bounded no-op false, no
     * write, no command at end_drag. */
    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    f32 s[3];
    read_scale(doc, e, s);
    assert_vec3(s[0], s[1], s[2], 0.0f, 1.0f, 1.0f, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(rotate_center_is_defined_noop) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));
    break_editor_doc_clear_dirty(doc);

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_ROTATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay;
    ASSERT_TRUE(world_to_px(&cam, 0.08f, 0.05f, 0, &ax, &ay));

    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, ax + 100.0f, ay, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(drag_without_begin_and_miss_begin_false) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    /* drag without begin -> false; end without begin -> no-op. */
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, 441.5692f, 300, VW, VH));
    break_editor_gizmo_end_drag(g);

    /* begin on a miss pixel -> false; a following drag stays inactive. */
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, 607.8461f, 300,
                                               VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, 441.5692f, 300, VW, VH));
    break_editor_gizmo_end_drag(g);
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(begin_drag_no_attach_or_none_mode_false) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);

    /* Detached. */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, 441.5692f, 300,
                                               VW, VH));
    /* Attached but mode NONE. */
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_NONE);
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, 441.5692f, 300,
                                               VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, 441.5692f, 300, VW, VH));

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(nan_inf_guards) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 2, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by, ix, iy;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));
    ASSERT_TRUE(world_to_px(&cam, 200.4f, 0, 0, &ix, &iy));

    /* NaN/Inf pointer coordinates: begin and drag reject bounded. */
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, NAN, 300, VW, VH));
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, 0, INFINITY, VW, VH));
    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, NAN, ay, VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, bx, INFINITY, VW, VH));
    /* Huge finite pixel: the ray runs (near-)parallel to the axis, so the
     * projection is degenerate -> bounded false, no write. */
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, 1e30f, ay, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0); /* no drag update landed: no command */
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    /* Computed-value guard (scale mode): a 2^200 factor overflows to Inf —
     * rejected, scale unchanged. */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_SCALE);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, ix, iy, VW, VH));
    break_editor_gizmo_end_drag(g);
    f32 s[3];
    read_scale(doc, e, s);
    assert_vec3(s[0], s[1], s[2], 2.0f, 1.0f, 1.0f, 0);

    /* Non-finite pivot: no handles, no hit, no begin. */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, INFINITY));
    BreakEditorGizmoHandle h[24];
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 0u);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 441.5692f, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_NONE);
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, 441.5692f, 300,
                                               VW, VH));
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, 0.0f));
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(degenerate_parallel_axis_bounded_false) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    /* Camera on +X looking straight down the X axis: the center ray HITS the
     * X handle, but the grab-point projection is singular -> begin fails. */
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    cam.yaw = ED_DEG2RAD(90.0);
    ASSERT_EQ(break_editor_gizmo_hit(g, &cam, 400, 300, VW, VH),
              BREAK_EDITOR_GIZMO_PART_X);
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, 400, 300, VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, 500, 300, VW, VH));

    /* Camera orbited into parallelism MID-drag: with the yaw-90 camera the
     * CENTER pixel's ray is exactly anti-parallel to the X axis, so the
     * projection is singular and that drag call is a bounded no-op false;
     * the drag survives and ends with no command. (An off-center pixel is
     * only NEAR-parallel — it yields a large but finite projection and is a
     * normal, if jumpy, update; only the singular case is rejected.) */
    BreakEditorCamera dflt;
    break_editor_camera_init(&dflt);
    f32 ax, ay;
    ASSERT_TRUE(world_to_px(&dflt, 0.4f, 0, 0, &ax, &ay));
    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &dflt, ax, ay, VW, VH));
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, 400, 300, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0);
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(mid_drag_set_mode_commits) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    /* Mode switch mid-drag: implicit end_drag commits the in-progress drag
     * as ONE command. */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_ROTATE);
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.5f, 0, 0, 1e-3f);
    /* The old drag is over. */
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, bx + 50.0f, by, VW, VH));
    /* Rotate mode took effect: same 4-handle layout. */
    BreakEditorGizmoHandle h[24];
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 4u);
    /* Single undo reverts the committed drag. */
    ASSERT_TRUE(break_editor_undo(doc));
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(mid_drag_attach_and_detach_commit) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = add_transformed(doc, "a", 0, 0, 0, 1, 1, 1);
    BreakEditorEntityId b = add_transformed(doc, "b", 5, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_entity_id_valid(b));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, a);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    /* Re-attach mid-drag: commits against the OLD entity, then switches. */
    break_editor_gizmo_attach(g, doc, b);
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    f32 pos[3];
    read_pos(doc, a, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.5f, 0, 0, 1e-3f);

    /* Detach mid-drag: commits, then hides. b's Y handle is used here: from
     * the default camera the ray toward b's X handle crosses b's Z handle
     * box first (it extends from the pivot toward +Z, nearer the camera),
     * so nearest-wins picks Z there — the Y handle has a clear line. Grab
     * (5,0.5,0) on the Y axis, release at (5,1.0,0) -> pos.y += 0.5. */
    ASSERT_TRUE(world_to_px(&cam, 5.0f, 0.5f, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 5.0f, 1.0f, 0, &bx, &by));
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    break_editor_gizmo_attach(g, NULL, b);
    ASSERT_EQ(stack_size(doc), size0 + 2u);
    read_pos(doc, b, pos);
    assert_vec3(pos[0], pos[1], pos[2], 5.0f, 0.5f, 0, 1e-3f);
    BreakEditorGizmoHandle h[24];
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 24), 0u);

    ASSERT_TRUE(break_editor_undo(doc)); /* b's drag */
    read_pos(doc, b, pos);
    assert_vec3(pos[0], pos[1], pos[2], 5.0f, 0, 0, 0);
    ASSERT_TRUE(break_editor_undo(doc)); /* a's drag */
    read_pos(doc, a, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(destroy_mid_drag_commits) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    break_editor_gizmo_destroy(g); /* mid-drag: commits first */
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.5f, 0, 0, 1e-3f);
    ASSERT_TRUE(break_editor_undo(doc));
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    break_editor_doc_destroy(doc);
}

TEST(begin_while_dragging_ends_previous) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    /* The X handle moved with the entity to x in [0.6155, 1.1928]; the ray
     * through (0.9,0,0) still hits it. A second begin implicitly commits
     * the first drag. */
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, bx, by, VW, VH));
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    break_editor_gizmo_end_drag(g); /* no movement: no second command */
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.5f, 0, 0, 1e-3f);
    ASSERT_TRUE(break_editor_undo(doc));
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(entity_removed_mid_drag_discards) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));

    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    u32 size0 = stack_size(doc);
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    /* Removing the entity mid-drag: later drag calls fail bounded and
     * end_drag DISCARDS the command (only the remove lands on the stack). */
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, e));
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, bx + 50.0f, by, VW, VH));
    break_editor_gizmo_end_drag(g);
    ASSERT_EQ(stack_size(doc), size0 + 1u);

    /* Undoing the remove restores the entity with its transform (the
     * remove command snapshots components, 2026-10-29): the bytes are the
     * ones live at removal, i.e. the mid-drag position, since the discarded
     * drag never committed a command of its own. The stack stays coherent. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(break_editor_doc_has_component(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM));
    {
        f32 x = 0.0f;
        ASSERT_TRUE(break_editor_doc_get_field_f32(
            doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &x));
        ASSERT_TRUE(x > 0.0f); /* moved along +X by the drag before removal */
    }

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

/* Snapping: translate/scale results round to the step, rotate to whole
 * multiples of the degree step; 0 disables. The value is snapped, not the
 * delta, so an off-grid start lands on the grid. Setters reject negative
 * or non-finite steps (keep the previous setting). */
TEST(snap_rounds_translate_rotate_and_scale) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0.1f, 0, 0, 1, 1, 1);
    BreakEditorGizmo *g = break_editor_gizmo_create();
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by, pos[3], v;

    ASSERT_TRUE(break_editor_gizmo_set_snap(g, 0.25f, 15.0f, 0.5f));
    {
        f32 t, r, sc;
        break_editor_gizmo_get_snap(g, &t, &r, &sc);
        ASSERT_FLOAT_EQ(t, 0.25f, 0.0f);
        ASSERT_FLOAT_EQ(r, 15.0f, 0.0f);
        ASSERT_FLOAT_EQ(sc, 0.5f, 0.0f);
    }
    /* translate: 0.1 + 0.5 = 0.6 -> 0.5 */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);
    ASSERT_TRUE(world_to_px(&cam, 0.5f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 1.0f, 0, 0, &bx, &by));
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    read_pos(doc, e, pos);
    ASSERT_FLOAT_EQ(pos[0], 0.5f, 1e-5f);
    break_editor_gizmo_end_drag(g);
    /* rotate: +100 px = +50 deg -> 45 */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_ROTATE);
    ASSERT_TRUE(world_to_px(&cam, 0.5f + 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, ax + 100.0f, ay, VW, VH));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 3, &v));
    ASSERT_FLOAT_EQ(v, 45.0f, 1e-4f);
    break_editor_gizmo_end_drag(g);
    /* scale never snaps below one step (a zero scale is not reachable) */
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_SCALE);
    ASSERT_TRUE(world_to_px(&cam, 0.5f + 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.5f - 3.0f, 0, 0, &bx, &by));
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 6, &v));
    ASSERT_FLOAT_EQ(v, 0.5f, 1e-5f);
    break_editor_gizmo_end_drag(g);
    /* off: unchanged behaviour (0.5 + 0.37 stays 0.87) */
    ASSERT_TRUE(break_editor_gizmo_set_snap(g, 0.0f, 0.0f, 0.0f));
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 1.27f, 0, 0, &bx, &by));
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    read_pos(doc, e, pos);
    ASSERT_FLOAT_EQ(pos[0], 0.87f, 1e-3f);
    break_editor_gizmo_end_drag(g);
    /* bad steps rejected, setting kept */
    ASSERT_TRUE(break_editor_gizmo_set_snap(g, 1.0f, 10.0f, 0.1f));
    ASSERT_FALSE(break_editor_gizmo_set_snap(g, -1.0f, 10.0f, 0.1f));
    ASSERT_FALSE(break_editor_gizmo_set_snap(g, NAN, 10.0f, 0.1f));
    ASSERT_FALSE(break_editor_gizmo_set_snap(NULL, 1.0f, 1.0f, 1.0f));
    {
        f32 t, r, sc;
        break_editor_gizmo_get_snap(g, &t, &r, &sc);
        ASSERT_FLOAT_EQ(t, 1.0f, 0.0f);
    }
    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

/* An out-of-range mode (caller error) is clamped to NONE (hidden) instead of
 * being stored: no handles, no drag. */
TEST(set_mode_out_of_range_hides_the_gizmo) {
    BreakEditorDoc *doc = break_editor_doc_create();
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    BreakEditorGizmo *g = break_editor_gizmo_create();
    BreakEditorGizmoHandle h[4];
    BreakEditorCamera cam;
    f32 ax, ay;
    ASSERT_NOT_NULL(g);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, (BreakEditorGizmoMode)42);
    ASSERT_EQ(break_editor_gizmo_handles(g, h, 4u), 0u);
    break_editor_camera_init(&cam);
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_FALSE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

/* Rotation rings (visual): in ROTATE mode each axis gets a ring of
 * `segments` small boxes on the circle of radius gap + axis_len around the
 * pivot, in the plane perpendicular to that axis. Other modes / detached /
 * bad arguments yield 0. Pure CPU, same sizing source as the handles. */
TEST(rotate_rings_lie_on_circles_around_the_pivot) {
    BreakEditorDoc *doc = break_editor_doc_create();
    BreakEditorEntityId e = add_transformed(doc, "box", 1, 2, 3, 1, 1, 1);
    BreakEditorGizmo *g = break_editor_gizmo_create();
    BreakEditorGizmoRingSeg seg[3 * 32];
    BreakEditorCamera cam;
    usize n;
    break_editor_camera_init(&cam);
    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);
    ASSERT_EQ(break_editor_gizmo_rings(g, 32u, seg, 3u * 32u), 0u);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_ROTATE);
    break_editor_gizmo_set_view(g, &cam);
    n = break_editor_gizmo_rings(g, 32u, seg, 3u * 32u);
    ASSERT_EQ(n, 96u);
    {
        f32 sb = 0.0f, radius;
        BreakEditorGizmoHandle h[4];
        ASSERT_EQ(break_editor_gizmo_handles(g, h, 4u), 4u);
        /* radius = gap + axis_len = far end of the X handle - pivot.x */
        radius = h[0].aabb_max[0] - 1.0f;
        (void)sb;
        for (usize i = 0; i < n; i++) {
            u32 a = seg[i].axis;
            f32 d[3] = {seg[i].center[0] - 1.0f, seg[i].center[1] - 2.0f,
                        seg[i].center[2] - 3.0f};
            ASSERT_TRUE(a < 3u);
            ASSERT_FLOAT_EQ(d[a], 0.0f, 1e-5f); /* in the axis' plane */
            ASSERT_FLOAT_EQ(sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]),
                            radius, 1e-4f);
            ASSERT_TRUE(seg[i].half_size > 0.0f);
            ASSERT_EQ(a, (u32)(i / 32u)); /* X ring, then Y, then Z */
        }
    }
    /* bounds */
    ASSERT_EQ(break_editor_gizmo_rings(g, 32u, seg, 10u), 0u); /* too small */
    ASSERT_EQ(break_editor_gizmo_rings(g, 2u, seg, 96u), 0u);  /* < 3 segs */
    ASSERT_EQ(break_editor_gizmo_rings(NULL, 32u, seg, 96u), 0u);
    break_editor_gizmo_attach(g, NULL, BREAK_EDITOR_ENTITY_NULL);
    ASSERT_EQ(break_editor_gizmo_rings(g, 32u, seg, 96u), 0u);
    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST(oom_budget_sweeps) {
    /* create: single editor-owned allocation. */
    break_editor_test_set_alloc_budget(0);
    ASSERT_TRUE(break_editor_gizmo_create() == NULL);
    break_editor_test_set_alloc_budget(1);
    BreakEditorGizmo *g = break_editor_gizmo_create();
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_NOT_NULL(g);

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = add_transformed(doc, "box", 0, 0, 0, 1, 1, 1);
    ASSERT_TRUE(break_editor_entity_id_valid(e));
    break_editor_doc_clear_dirty(doc);

    break_editor_gizmo_attach(g, doc, e);
    break_editor_gizmo_set_mode(g, BREAK_EDITOR_GIZMO_TRANSLATE);

    BreakEditorCamera cam;
    break_editor_camera_init(&cam);
    f32 ax, ay, bx, by;
    ASSERT_TRUE(world_to_px(&cam, 0.4f, 0, 0, &ax, &ay));
    ASSERT_TRUE(world_to_px(&cam, 0.9f, 0, 0, &bx, &by));

    /* begin_drag allocates exactly one command object: budget 0 fails
     * bounded (no drag, doc untouched), budget 1 is the first success. */
    u32 size0 = stack_size(doc);
    break_editor_test_set_alloc_budget(0);
    bool began = break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_FALSE(began);
    ASSERT_FALSE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    ASSERT_EQ(stack_size(doc), size0);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    f32 pos[3];
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    break_editor_test_set_alloc_budget(1);
    began = break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_TRUE(began);
    break_editor_gizmo_end_drag(g); /* no movement: no command */
    ASSERT_EQ(stack_size(doc), size0);

    /* end_drag commits with an exhausted budget: push_applied never
     * allocates. */
    ASSERT_TRUE(break_editor_gizmo_begin_drag(g, &cam, ax, ay, VW, VH));
    ASSERT_TRUE(break_editor_gizmo_drag(g, &cam, bx, by, VW, VH));
    break_editor_test_set_alloc_budget(0);
    break_editor_gizmo_end_drag(g);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_EQ(stack_size(doc), size0 + 1u);
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0.5f, 0, 0, 1e-3f);
    ASSERT_TRUE(break_editor_undo(doc));
    read_pos(doc, e, pos);
    assert_vec3(pos[0], pos[1], pos[2], 0, 0, 0, 0);

    break_editor_gizmo_destroy(g);
    break_editor_doc_destroy(doc);
}

TEST_MAIN_BEGIN()
    RUN_TEST(pixel_helper_known_answers);
    RUN_TEST(create_defaults_and_mode_none_hides);
    RUN_TEST(mode_attach_detach);
    RUN_TEST(handle_layout_known_answers);
    RUN_TEST(handles_track_pivot_and_view_scale);
    RUN_TEST(hit_test_per_part_and_misses);
    RUN_TEST(translate_x_drag_known_answer);
    RUN_TEST(translate_y_drag_known_answer);
    RUN_TEST(translate_center_plane_known_answer);
    RUN_TEST(single_undo_reverts_whole_drag);
    RUN_TEST(rotate_drag_known_answer_and_sign);
    RUN_TEST(scale_axis_drag_known_answer);
    RUN_TEST(scale_axis_clamps_to_min);
    RUN_TEST(scale_center_uniform_drag);
    RUN_TEST(scale_from_zero_is_bounded_noop);
    RUN_TEST(rotate_center_is_defined_noop);
    RUN_TEST(drag_without_begin_and_miss_begin_false);
    RUN_TEST(begin_drag_no_attach_or_none_mode_false);
    RUN_TEST(nan_inf_guards);
    RUN_TEST(degenerate_parallel_axis_bounded_false);
    RUN_TEST(mid_drag_set_mode_commits);
    RUN_TEST(mid_drag_attach_and_detach_commit);
    RUN_TEST(destroy_mid_drag_commits);
    RUN_TEST(begin_while_dragging_ends_previous);
    RUN_TEST(entity_removed_mid_drag_discards);
    RUN_TEST(snap_rounds_translate_rotate_and_scale);
    RUN_TEST(set_mode_out_of_range_hides_the_gizmo);
    RUN_TEST(rotate_rings_lie_on_circles_around_the_pivot);
    RUN_TEST(oom_budget_sweeps);
TEST_MAIN_END()
