#pragma once
/* Editor viewport CPU core — Stage 4 scene editor Phase 2 Task 1:
 * orbit camera, screen->world ray unprojection, and BVH picking.
 *
 * This is the PURE CPU half of the viewport: no RHI, no GPU, no myui. The
 * GPU panel (offscreen FBO, proxy cube rendering, pointer routing) is Task
 * 3 and consumes exactly this surface.
 *
 * Camera model (orbit camera around a pivot):
 *   eye = target + distance * (cos(pitch)*sin(yaw), sin(pitch),
 *                              cos(pitch)*cos(yaw))
 * i.e. eye = target + R(yaw,pitch) * (0,0,distance) with yaw around +Y
 * applied before pitch; at yaw == pitch == 0 the eye sits on +Z behind the
 * target and the forward axis (normalize(target - eye)) is -Z. Positive
 * pitch ELEVATES the camera above the target (it looks down at the pivot).
 * view = mat4_lookat(eye, target, +Y) (right-handed, math.h:164-168);
 * proj = mat4_perspective(fov_y, aspect, BREAK_EDITOR_VIEWPORT_NEAR,
 * BREAK_EDITOR_VIEWPORT_FAR) — right-handed GL-style clip z in [-1,1],
 * no TAA jitter, so mat4_inv_perspective's jitter terms (e[2][0..1]) are
 * exactly zero on the unprojection path.
 *
 * EditorTransform.rot convention (plan Global Constraints — DEFINED by this
 * plan, pinned here for every later consumer): rot[0..2] are intrinsic
 * yaw(Y)->pitch(X)->roll(Z) Euler angles in DEGREES. Storage mapping
 * (disambiguated and pinned by Task 2's gizmo tests): rot[k] is the
 * rotation ABOUT axis k, matching the Phase 1 inspector field names
 * (rot[0] = rot.x = pitch about X, rot[1] = rot.y = yaw about Y,
 * rot[2] = rot.z = roll about Z); "yaw->pitch->roll" is the COMPOSITION
 * ORDER for model matrices: M = R_y(rot.y) * R_x(rot.x) * R_z(rot.z).
 * Task 1 never builds
 * model matrices (proxy AABBs are axis-aligned from pos/scale alone); the
 * Task 3 proxy renderer applies rot via mat4_mul chains in exactly that
 * order.
 *
 * Entity proxy AABB (plan Global Constraints): for an entity with an
 * EditorTransform, center = pos, half-extent = 0.5*|scale| per axis with a
 * minimum of BREAK_EDITOR_PROXY_MIN_HALF_EXTENT (0.05) so zero/thin-scaled
 * entities stay pickable. Entities WITHOUT an EditorTransform have no proxy
 * and are skipped by pick. Non-finite pos/scale components also skip the
 * entity (bounded). The proxy is an EDITOR-ONLY representation — it does
 * not claim game-scene fidelity.
 *
 * Picking: pick rebuilds the BVH over all proxy AABBs ON EACH CALL
 * (documented Phase 2 choice — entity counts are editor-scale; incremental
 * bvh_refit is a later optimization). The candidate buffer is bounded by
 * BREAK_EDITOR_PICK_MAX_ENTITIES (4096, plan Global Constraints): documents
 * larger than that are queried over their first 4096 iterated entities
 * only. bvh_raycast's nearest hit (smallest BVHRayHit.t) wins; the bvh
 * object_index is the position in the compacted proxy array and maps back
 * through a parallel BreakEditorEntityId array. pick takes a non-const
 * BreakEditorDoc* only because the Phase 1 iteration API does; it performs
 * NO document mutation.
 *
 * Camera controls: orbit adds degree deltas (dx->yaw, dy->pitch) and clamps
 * pitch to +/-BREAK_EDITOR_CAMERA_PITCH_LIMIT (89°). pan moves the target
 * in the camera's right/up plane, scaled by distance (world-units per pixel
 * at the pivot plane = 2*distance*tan(fov_y/2) /
 * BREAK_EDITOR_VIEWPORT_PAN_REFERENCE_HEIGHT): drag right (dx_px > 0) moves
 * the target along -right, drag down (dy_px > 0, top-left screen origin)
 * moves it along +up. zoom is exponential — distance *=
 * expf(-BREAK_EDITOR_CAMERA_ZOOM_SPEED * wheel_delta), so positive wheel
 * delta zooms IN — clamped to [BREAK_EDITOR_CAMERA_MIN_DISTANCE,
 * BREAK_EDITOR_CAMERA_MAX_DISTANCE]. focus fits target+distance to the
 * entity's proxy AABB bounding sphere (distance = radius / tan(fov_y/2),
 * same clamp), leaving yaw/pitch untouched; focusing an entity without an
 * EditorTransform (or a stale/invalid id) is a bounded no-op.
 *
 * Degenerate inputs: screen_ray/pick return bounded false (outputs
 * untouched) on NULL arguments, w/h <= 0, non-finite x/y/w/h, non-finite or
 * degenerate camera state (fov_y outside (0, pi), distance <= 0), or a
 * degenerate perspective divide (|w| < 1e-20). orbit/pan/zoom ignore
 * non-finite deltas and non-finite camera state (bounded no-op).
 *
 * Allocation failure: pick's three editor-owned allocations (proxy AABB
 * array, entity-id map, BVH struct) go through break_editor_test_calloc, so
 * the BREAK_EDITOR_TESTING budget hooks cover them; on exhaustion pick
 * frees what it took and returns bounded false. bvh.c's INTERNAL node/
 * leaf-map/build allocations belong to the bvh translation unit and are NOT
 * hooked (same convention as the doc's internal World, whose allocations
 * belong to break_ecs_replication); bvh.c already fails bounded
 * (root = BVH_NULL) on its own OOM, which surfaces here as a clean miss.
 *
 * Threading: same single-owner-thread convention as the document (Phase 1):
 * the editor shell thread owns the camera and the doc; there is no mutex.
 * All functions are pure CPU and allocation-bounded. */

#include <core/types.h>

#include <editor/editor_doc.h>

/* Default orbit distance after break_editor_camera_init. */
#define BREAK_EDITOR_CAMERA_DEFAULT_DISTANCE 5.0f
/* Default vertical field of view after init: 60 degrees in radians. */
#define BREAK_EDITOR_CAMERA_DEFAULT_FOV_Y 1.0471975511965976f
/* Shared distance clamp for focus and zoom (plan: focus clamps
 * [0.05, 1e4]; zoom uses the same bounds). */
#define BREAK_EDITOR_CAMERA_MIN_DISTANCE 0.05f
#define BREAK_EDITOR_CAMERA_MAX_DISTANCE 1e4f
/* Pitch clamp magnitude: 89 degrees in radians. */
#define BREAK_EDITOR_CAMERA_PITCH_LIMIT 1.5533430342749532f
/* Exponential zoom rate per wheel tick. */
#define BREAK_EDITOR_CAMERA_ZOOM_SPEED 0.1f

/* Fixed clip planes for break_editor_camera_proj (editor-scale scenes;
 * far covers the maximum orbit distance plus proxy extents). */
#define BREAK_EDITOR_VIEWPORT_NEAR 0.05f
#define BREAK_EDITOR_VIEWPORT_FAR 20000.0f
/* Pan speed reference: pixels of a 720-high viewport at the pivot plane. */
#define BREAK_EDITOR_VIEWPORT_PAN_REFERENCE_HEIGHT 720.0f

/* Pick candidate buffer bound (plan Global Constraints: <= 4096 entities
 * per query). */
#define BREAK_EDITOR_PICK_MAX_ENTITIES 4096u
/* Minimum per-axis proxy AABB half-extent (pickability clamp). */
#define BREAK_EDITOR_PROXY_MIN_HALF_EXTENT 0.05f

typedef struct BreakEditorCamera {
    f32 target[3];     /* orbit/focus pivot */
    f32 yaw;           /* radians, around +Y */
    f32 pitch;         /* radians, orbit clamps to [-89°, +89°]
                          (BREAK_EDITOR_CAMERA_PITCH_LIMIT) */
    f32 distance;      /* zoom/focus clamp to [BREAK_EDITOR_CAMERA_MIN_DISTANCE,
                          BREAK_EDITOR_CAMERA_MAX_DISTANCE] = [0.05, 1e4] */
    f32 fov_y;         /* radians, default 60° */
} BreakEditorCamera;

void break_editor_camera_init(BreakEditorCamera *cam);
/* eye position derived: target + R(yaw,pitch) * (0,0,distance); view = mat4_lookat(eye, target, up=+Y) */
void break_editor_camera_view(const BreakEditorCamera *cam, f32 out_view[16]);
void break_editor_camera_proj(const BreakEditorCamera *cam, f32 aspect, f32 out_proj[16]);

/* screen (x,y logical px, top-left origin, w/h viewport size) → world ray */
bool break_editor_viewport_screen_ray(const BreakEditorCamera *cam,
    f32 x, f32 y, f32 w, f32 h, f32 out_origin[3], f32 out_dir[3]);

typedef struct BreakEditorPickResult { BreakEditorEntityId id; f32 t; } BreakEditorPickResult;
/* BVH over per-entity proxy AABBs from EditorTransform; nearest hit wins; false when no hit */
bool break_editor_viewport_pick(BreakEditorDoc *doc, const BreakEditorCamera *cam,
    f32 x, f32 y, f32 w, f32 h, BreakEditorPickResult *out);

/* Box (marquee) select: stores, in document iteration order, every entity
 * whose EditorTransform pos projects strictly in front of the camera
 * (clip w > near) to a screen point inside the rectangle spanned by
 * (x0,y0)-(x1,y1) (logical px, top-left origin, corners in any order,
 * edges inclusive) of a w x h viewport. Entities without a transform or
 * with non-finite pos are skipped; the scan is bounded by
 * BREAK_EDITOR_PICK_MAX_ENTITIES. Returns the stored count (<= cap);
 * 0 on NULL arguments, cap 0, non-finite inputs, w/h <= 0 or a degenerate
 * camera. Allocation-free, no document mutation. */
u32 break_editor_viewport_box_select(BreakEditorDoc *doc,
    const BreakEditorCamera *cam, f32 x0, f32 y0, f32 x1, f32 y1,
    f32 w, f32 h, BreakEditorEntityId *out, u32 cap);

void break_editor_camera_focus(BreakEditorCamera *cam, const BreakEditorDoc *doc, BreakEditorEntityId id); /* fits target+distance to the entity's proxy AABB, distance clamped [0.05, 1e4] */
void break_editor_camera_orbit(BreakEditorCamera *cam, f32 dx_deg, f32 dy_deg);
void break_editor_camera_pan(BreakEditorCamera *cam, f32 dx_px, f32 dy_px);   /* scaled by distance */
void break_editor_camera_zoom(BreakEditorCamera *cam, f32 wheel_delta);      /* exponential, clamped */
