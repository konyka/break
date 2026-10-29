#pragma once
/* Editor transform gizmo state machine — Stage 4 scene editor Phase 2
 * Task 2. PURE CPU: no RHI, no GPU, no myui. The Task 3 renderer consumes
 * break_editor_gizmo_handles() as the single source of truth for gizmo
 * geometry (hit-test AND rendering share the same AABBs).
 *
 * Modes/parts: TRANSLATE/ROTATE/SCALE (NONE hides the gizmo); parts X/Y/Z
 * plus CENTER. The gizmo attaches to an entity by BreakEditorEntityId and
 * drives the entity's EditorTransform (component id
 * BREAK_EDITOR_COMPONENT_TRANSFORM; fields pos[0..2] rot[3..5] scale[6..8]).
 *
 * Handle geometry (pinned formula — known-answer tests in
 * engine/tests/test_editor_gizmo.c):
 *   scale_base = |eye - pivot| * tan(fov_y / 2)
 * i.e. HALF the world-space viewport height at the pivot plane (screen-
 * constant sizing: handles keep a fixed on-screen size as the camera
 * orbits/zooms). pivot = the entity's current pos. With the default camera
 * (distance 5, fov 60 deg) and a pivot at the origin, scale_base =
 * 5 * tan(30 deg) = 2.8867513.
 *   gap         = BREAK_EDITOR_GIZMO_AXIS_GAP_SCALE    * scale_base (0.1154701)
 *   axis_len    = BREAK_EDITOR_GIZMO_AXIS_LEN_SCALE    * scale_base (0.5773503)
 *   thick       = BREAK_EDITOR_GIZMO_AXIS_THICK_SCALE  * scale_base (0.0461880)
 *   center_half = BREAK_EDITOR_GIZMO_CENTER_HALF_SCALE * scale_base (0.1154701)
 * Handles are WORLD-AXIS-ALIGNED AABBs (entity rotation is not applied —
 * AABBs are axis-aligned by definition):
 *   axis k in {X,Y,Z}: along k [pivot_k + gap, pivot_k + gap + axis_len];
 *                      along j != k [pivot_j - thick, pivot_j + thick]
 *   CENTER:            [pivot - center_half, pivot + center_half] per axis
 *   (the axis box starts exactly where the center box face ends)
 * Exactly 4 handles, written in the order X, Y, Z, CENTER; the hard bound is
 * BREAK_EDITOR_GIZMO_MAX_HANDLES (24, plan Global Constraints).
 *
 * The sizing cache: handles() takes no camera (fixed Phase 2 interface), so
 * the gizmo caches scale_base. The cache is refreshed from the camera passed
 * to hit/begin_drag/drag and by break_editor_gizmo_set_view — the Task 3
 * renderer calls set_view once per frame so handle sizes track camera moves
 * that happen without pointer events (orbit keys, focus). Until the first
 * refresh the cache holds the default-camera value for a pivot at the
 * camera target (5 * tan(30 deg)). A refresh with a degenerate camera or a
 * non-finite pivot leaves the previous cache value untouched.
 *
 * Hit test: direct ray-AABB slab tests over the 4 handles (no BVH — 4
 * boxes, zero allocation, OOM-free); nearest entry t wins; a box containing
 * the ray origin counts as t = 0. Degenerate camera/viewport (the same
 * inputs break_editor_viewport_screen_ray rejects) yields PART_NONE.
 *
 * Drag math (pinned by known-answer tests; all deltas are computed from the
 * BEGIN-DRAG snapshot — absolute, never incremental — so float error does
 * not accumulate over a long drag):
 *   TRANSLATE X/Y/Z: closest-point-between-two-lines between the mouse ray
 *     and the axis line (through the begin-drag pivot, along the world
 *     axis); pos[axis] = begin_pos[axis] + (s - s0). Ray (near-)parallel to
 *     the axis (1 - (dir.axis)^2 < 1e-6) is degenerate: begin_drag fails /
 *     drag is a bounded no-op false.
 *   TRANSLATE CENTER: free translate in the camera-facing plane (plane
 *     through the begin-drag pivot, normal = current camera forward);
 *     pos = begin_pos + (plane_hit - begin_plane_hit).
 *   ROTATE X/Y/Z: horizontal pixel drag only — degrees = (x - x_begin) *
 *     BREAK_EDITOR_GIZMO_ROTATE_DEG_PER_PX (0.5 deg/px). Sign convention:
 *     dragging RIGHT (increasing x) INCREASES the field value (positive
 *     rotation about the +axis, right-hand rule). rot field mapping: part X
 *     edits rot.x (field 3, pitch about X), Y edits rot.y (field 4, yaw
 *     about Y), Z edits rot.z (field 5, roll about Z). The plan's
 *     "intrinsic yaw(Y)->pitch(X)->roll(Z)" is the COMPOSITION ORDER for
 *     model matrices (M = R_y(rot.y) * R_x(rot.x) * R_z(rot.z), Task 3); the
 *     stored rot[k] is the rotation about axis k, matching the Phase 1
 *     inspector field names rot.x/rot.y/rot.z.
 *   ROTATE CENTER: defined no-op (drag returns true, no field changes, no
 *     command at end_drag) — the handle stays visible so the on-screen
 *     layout is identical across modes.
 *   SCALE X/Y/Z: per-axis multiplicative — factor = 2^(s - s0) (s the same
 *     axis projection as translate; one world unit along +axis doubles);
 *     scale[axis] = max(begin_scale[axis] * factor,
 *     BREAK_EDITOR_GIZMO_SCALE_MIN). A non-positive begin scale makes the
 *     drag a bounded no-op false (multiplicative drag is meaningless from
 *     zero/negative).
 *   SCALE CENTER: uniform — factor = 2^((x - x_begin) /
 *     BREAK_EDITOR_GIZMO_UNIFORM_SCALE_PX_PER_OCTAVE) (200 px per doubling)
 *     applied to all three scale fields with the same clamp/old-value rule.
 *
 * Undo semantics (CRITICAL): a whole drag = ONE undoable command. begin_drag
 * allocates the command and snapshots the OLD field bytes; drag() calls
 * write new values live into the component (the in-progress command owns the
 * mutation; the undo stack is NOT touched per frame); end_drag captures the
 * new bytes and pushes the command as already-applied. Pinned: one
 * break_editor_undo reverts the ENTIRE drag (all touched fields), one redo
 * re-applies the final state. A drag whose final bytes equal the begin
 * snapshot records NO command (bitwise-identical no-op, matching
 * set_field_f32). The command is a multi-field transform command (up to 3
 * f32 fields: offsets + old/new bytes), constructed like the Phase 1
 * component commands (editor_components.c) with kind
 * BREAK_EDITOR_CMD_KIND_GIZMO_TRANSFORM — set_field_f32 is NEVER called per
 * pointer move.
 *
 * Mid-drag policy (defined): set_mode, attach (including detach via a NULL
 * doc or invalid id), and a second begin_drag each perform an IMPLICIT
 * end_drag (committing the in-progress drag against the OLD doc/id) before
 * switching. break_editor_gizmo_destroy mid-drag also ends (commits) the
 * drag first — a mutation never survives without an undo command while the
 * doc is alive. If the attached entity or its transform vanished mid-drag
 * (e.g. remove_entity), end_drag DISCARDS the command instead (bounded: its
 * revert/apply could only fail anyway) and drag() calls after the removal
 * return false. The gizmo BORROWS the doc: the owner must detach or destroy
 * the gizmo before destroying the doc (same single-owner-thread convention
 * as the document; no mutex).
 *
 * Bounded behavior: handles <= 4 <= BREAK_EDITOR_GIZMO_MAX_HANDLES;
 * begin_drag with no handle hit / no attach / NONE mode / entity without a
 * finite transform / degenerate grab geometry / OOM (the command allocation
 * goes through break_editor_test_calloc, covered by the BREAK_EDITOR_TESTING
 * budget) all return false leaving the doc untouched and no drag active;
 * drag without an active begin returns false; NaN/Inf pointer coordinates,
 * camera state, or computed deltas are rejected (bounded false, no write);
 * end_drag without an active drag is a no-op and never allocates.
 */

#include <core/types.h>

#include <editor/editor_doc.h>
#include <editor/editor_viewport.h>

typedef enum BreakEditorGizmoMode { BREAK_EDITOR_GIZMO_NONE = 0, BREAK_EDITOR_GIZMO_TRANSLATE, BREAK_EDITOR_GIZMO_ROTATE, BREAK_EDITOR_GIZMO_SCALE } BreakEditorGizmoMode;
typedef enum BreakEditorGizmoPart { BREAK_EDITOR_GIZMO_PART_NONE = 0, BREAK_EDITOR_GIZMO_PART_X, BREAK_EDITOR_GIZMO_PART_Y, BREAK_EDITOR_GIZMO_PART_Z, BREAK_EDITOR_GIZMO_PART_CENTER } BreakEditorGizmoPart;

/* Hard handle bound (plan Global Constraints); the gizmo emits exactly 4. */
#define BREAK_EDITOR_GIZMO_MAX_HANDLES 24u
/* Screen-constant sizing: multiples of scale_base = |eye - pivot| *
 * tan(fov_y/2) (half the world-space viewport height at the pivot plane). */
#define BREAK_EDITOR_GIZMO_AXIS_GAP_SCALE 0.04f
#define BREAK_EDITOR_GIZMO_AXIS_LEN_SCALE 0.20f
#define BREAK_EDITOR_GIZMO_AXIS_THICK_SCALE 0.016f
#define BREAK_EDITOR_GIZMO_CENTER_HALF_SCALE 0.04f
/* Rotate drag rate: degrees per horizontal pixel. */
#define BREAK_EDITOR_GIZMO_ROTATE_DEG_PER_PX 0.5f
/* Uniform (CENTER) scale drag: horizontal pixels per 2x factor. */
#define BREAK_EDITOR_GIZMO_UNIFORM_SCALE_PX_PER_OCTAVE 200.0f
/* Scale clamp: results never drop below this magnitude. */
#define BREAK_EDITOR_GIZMO_SCALE_MIN 0.01f

typedef struct BreakEditorGizmo BreakEditorGizmo;   /* opaque */
BreakEditorGizmo *break_editor_gizmo_create(void);
void break_editor_gizmo_destroy(BreakEditorGizmo *g);
void break_editor_gizmo_set_mode(BreakEditorGizmo *g, BreakEditorGizmoMode mode);   /* NONE hides */
void break_editor_gizmo_attach(BreakEditorGizmo *g, BreakEditorDoc *doc, BreakEditorEntityId id); /* NONE detaches */

/* Handle geometry for hit-testing AND for the Task 3 renderer (single source of truth): */
typedef struct BreakEditorGizmoHandle { BreakEditorGizmoPart part; f32 aabb_min[3]; f32 aabb_max[3]; } BreakEditorGizmoHandle;
usize break_editor_gizmo_handles(const BreakEditorGizmo *g, BreakEditorGizmoHandle *out, usize capacity); /* ≤ 24 */

/* Refreshes the screen-constant sizing cache from the given camera (the
 * Task 3 renderer calls this once per frame; hit/begin_drag/drag refresh it
 * too). No-op on NULL, degenerate camera, detached gizmo, or non-finite
 * pivot (the previous cache value is kept). */
/* Snapping (0 = off per kind): translate results round to multiples of
 * `translate_step` world units, rotate to multiples of `rotate_deg`, scale
 * to multiples of `scale_step` and never below one step. The resulting
 * value is snapped (not the delta). false for NULL or a negative /
 * non-finite step (previous setting kept). Applies to drags begun later
 * and to the current one from its next drag() call. */
bool break_editor_gizmo_set_snap(BreakEditorGizmo *g, f32 translate_step,
                                 f32 rotate_deg, f32 scale_step);
void break_editor_gizmo_get_snap(const BreakEditorGizmo *g, f32 *translate_step,
                                 f32 *rotate_deg, f32 *scale_step);
void break_editor_gizmo_set_view(BreakEditorGizmo *g, const BreakEditorCamera *cam);

/* Pointer drive (viewport-local logical px): */
BreakEditorGizmoPart break_editor_gizmo_hit(const BreakEditorGizmo *g, const BreakEditorCamera *cam, f32 x, f32 y, f32 w, f32 h);
bool break_editor_gizmo_begin_drag(BreakEditorGizmo *g, const BreakEditorCamera *cam, f32 x, f32 y, f32 w, f32 h); /* false when no handle hit */
bool break_editor_gizmo_drag(BreakEditorGizmo *g, const BreakEditorCamera *cam, f32 x, f32 y, f32 w, f32 h);      /* applies UNDOABLE doc commands */
void break_editor_gizmo_end_drag(BreakEditorGizmo *g);
