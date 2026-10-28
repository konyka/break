# Scene Editor Phase 2 (3D Viewport + Gizmo + Camera) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the Phase 2 3D viewport to the scene editor: a pure-CPU viewport core (editor camera, screen→ray, BVH picking, transform gizmo state machine, focus-selected) inside `break_editor`, and a GPU viewport panel in the `editor` shell (offscreen RHI render of entity proxy cubes + gizmo, blitted into the myui layout), making Q/W/E/R gizmo modes and F focus real.

**Architecture:** All logic is pure CPU and headless-testable in `engine/src/editor/editor_viewport.h/.c` (camera orbit/pan/zoom, unproject via `mat4_inv_perspective` + `camera_inv_view`, ray construction, BVH raycast over per-entity proxy AABBs, gizmo hit-test and drag state machine producing undoable doc commands). The GPU side is a thin shell layer: a new myui RHI-canvas texture-blit extension slot, a viewport panel widget whose `on_paint` blits the current offscreen FBO texture, and an editor-side mini renderer (one unlit color pipeline + proxy cube mesh + gizmo handles). The renderer and widget are exercised by build/link + a live-window smoke run only; every behavior claim comes from the CPU core tests.

**Tech Stack:** C11; `break_editor` (Phase 1); `engine` math (`mat4_inv_perspective` math.h:241, `camera_inv_view` camera.h:29), `bvh_raycast` (physics/bvh.h:54, pure CPU); RHI offscreen FBO (rhi.h:768-800); myui widget on_paint/invalidate (my_widget.h:55,250); dummy PAL shell tests; ASan/UBSan/TSan.

## Global Constraints

- C11; no new dependencies; no changes to `framework/`, `engine/src/ecs`, `engine/src/scene`, `engine/src/script*`; myui changes limited to ONE additive vgcanvas extension slot (RHI texture blit) + its tests — no behavior change to existing slots (Phase 1's adjudicated my_list_view fix stays untouched).
- Phase 1 invariants hold: all doc mutations through undoable commands; widget callbacks never call `world_*`; `break_editor` stays a formal optional lib out of engine/demos; `editor` executable links `break_editor break_myui engine m` + `engine_link_rhi_backend(editor)`.
- `EditorTransform.rot` semantics are UNDEFINED until this plan: this plan defines them as intrinsic **yaw(Y)→pitch(X)→roll(Z)** degrees, applied when building model matrices (`mat4_mul` chains); pin by tests.
- Entity proxy rendering: one unit cube per entity with an EditorTransform; proxy AABB half-extent = `0.5 * scale` (per-axis, min clamp 0.05 for pickability); the proxy is an EDITOR-ONLY rendering representation — it does not claim game-scene fidelity (the Phase 1 documented SCENE_NODES-dropped limitation stands; no Scene ownership added in this phase).
- Bounded: gizmo handles ≤ 24; pick candidate buffer ≤ 4096 entities per query; drag float math guarded against degenerate rays (parallel-to-axis fallback); viewport panel min size 32×32; FBO recreated on resize only.
- GPU paths are not headless-testable (RHI headless backend is fail-closed, engine/CMakeLists.txt:161-167); ALL behavior tests target the CPU core; GPU code is verified by compilation + a live-window smoke run recorded honestly (no GPU-correctness claims).
- `break_ui_frame_begin` may skip frames without damage (myui_break.c:554-558); the viewport widget must `my_widget_invalidate` every frame while visible (viewport is a live 3D view; this is intended).
- Shortcut updates: W/E/R now switch gizmo MODE (translate/rotate/scale) AND update the tool label; Q = select mode (gizmo hidden); F = focus camera on selected entity (real behavior); Ctrl+S/Z/Y/P unchanged.
- Docs: viewport is an editor tool view; no claims of game-scene rendering parity, no GPU-validation claims without a recorded run.

---

## File and Target Map

- Create: `engine/src/editor/editor_viewport.h/.c` — CPU core: `BreakEditorCamera` (orbit target + yaw/pitch/distance), screen→ray, pick, gizmo state machine.
- Create: `engine/apps/editor/editor_viewport3d.h/.c` — GPU side: offscreen FBO lifecycle, proxy/gizmo rendering, viewport panel widget (custom on_paint), pointer routing into the CPU core.
- Create: `engine/shaders/editor_color.vert` + `engine/shaders/editor_color.frag` — minimal unlit vertex-color/flat-color pair (loaded via `shader_read_file`, engine/src/core/shader_io.h:41; runtime path resolution precedent `break_ui_read_shader` myui_break.c:48-70 honoring `BREAK_SHADER_DIR`).
- Modify: `engine/src/myui/myr/my_vgcanvas_break_rhi.h/.c` — additive `rhi_blit_texture` extension (new public function, not a vtable change): blit an `RHITexture` into a dst rect within the current frame's command stream.
- Modify: `engine/apps/editor/editor_panels.c/.h` — insert viewport panel between outliner and inspector (middle row, `w:1f h:100%`), wire W/E/R/Q/F to the core, per-frame invalidate + render hook from editor_main.c.
- Modify: `engine/apps/editor/editor_main.c` — viewport render call between `break_ui_frame_begin` and `break_ui_render` (same cmd; precedent demo main.c:8648-8655).
- Create: `engine/tests/test_editor_viewport.c` — CPU core tests (camera math, ray construction, picking, gizmo drag, focus).
- Modify: `engine/tests/test_editor_shell.c` — viewport panel presence, key routing W/E/R/Q/F into core state (headless, no GPU).
- Modify: `engine/CMakeLists.txt` — new sources into `break_editor`/`break_editor_test`/`editor`; new test executable; shader assets note (runtime-loaded, not compiled).
- Modify: `docs/design/editor_phase1.md` (or rename split into `docs/design/editor_viewport.md`), `docs/Implementation_Status.md`, roadmap Stage 4 subproject 5.

---

### Task 1: Viewport CPU core — camera, unproject, ray, picking

**Files:**
- Create: `engine/src/editor/editor_viewport.h/.c`
- Create: `engine/tests/test_editor_viewport.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces (verbatim — later tasks consume):**
```c
typedef struct BreakEditorCamera {
    f32 target[3];     /* orbit/focus pivot */
    f32 yaw;           /* radians, around +Y */
    f32 pitch;         /* radians, clamped to (-89°, +89°) */
    f32 distance;      /* > 0.01 */
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

void break_editor_camera_focus(BreakEditorCamera *cam, const BreakEditorDoc *doc, BreakEditorEntityId id); /* fits target+distance to the entity's proxy AABB, distance clamped [0.05, 1e4] */
void break_editor_camera_orbit(BreakEditorCamera *cam, f32 dx_deg, f32 dy_deg);
void break_editor_camera_pan(BreakEditorCamera *cam, f32 dx_px, f32 dy_px);   /* scaled by distance */
void break_editor_camera_zoom(BreakEditorCamera *cam, f32 wheel_delta);      /* exponential, clamped */
```

- Consumes: `mat4_inv_perspective` (math.h:241-250 — check its jitter term; use the non-jittered variant or zero jitter), `camera_inv_view`-equivalent math (camera.h:29 — note: this operates on the renderer `Camera` struct; the editor camera is a separate type, so implement the inverse-view transform locally with `mat4_lookat`/`mat4_inverse` (math.h:163/168/198) or hand-rolled basis math — pick the simplest correct form and pin by tests), `bvh_build`/`bvh_raycast`/`bvh_free` (physics/bvh.h:38/54), doc read APIs from Phase 1 (entity iteration via `break_editor_doc_entity_count/entity_at`, `get_field_f32` for pos/scale; component id `EDITOR_COMPONENT_TRANSFORM` = 64, `break_editor_doc_has_component`).
- Implementation notes: mat4×vec4 helper does not exist — write a local static one (precedent `cam_apply_point` engine/tests/test_camera_frustum.c:43-49); screen→ray = inv_proj * ndc(x,y,1) then inv_view, normalize, guard degenerate w; pick rebuilds the BVH per call in Phase 2 (entity counts are editor-scale; document; incremental refit is a later optimization).

- [ ] RED: camera view/proj known-answer tests (init defaults: eye on +Z behind target; view maps target to origin); screen_ray through center = forward axis; corners diverge correctly; pick nearest entity among three on a ray; pick miss; degenerate viewport (w=0) → false bounded; focus sets target to entity pos and sane distance; orbit clamps pitch; pan proportional to distance; zoom clamps; OOM paths (BVH alloc) bounded via `break_editor_test_calloc` budget hooks.
- [ ] GREEN: implementation; add to `break_editor`/`break_editor_test`; register `test_editor_viewport` (LABELS "headless;editor").
- [ ] Lanes: build-sdd-v1, -asan, -tsan; focused green incl. Phase 1 editor tests.
- [ ] Commit "feat(editor): ...".

### Task 2: Gizmo state machine (pure CPU)

**Files:**
- Create: `engine/src/editor/editor_gizmo.h/.c` (or fold into editor_viewport.c if it stays < 600 lines — prefer a separate file)
- Create: `engine/tests/test_editor_gizmo.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces (verbatim):**
```c
typedef enum BreakEditorGizmoMode { BREAK_EDITOR_GIZMO_NONE = 0, BREAK_EDITOR_GIZMO_TRANSLATE, BREAK_EDITOR_GIZMO_ROTATE, BREAK_EDITOR_GIZMO_SCALE } BreakEditorGizmoMode;
typedef enum BreakEditorGizmoPart { BREAK_EDITOR_GIZMO_PART_NONE = 0, BREAK_EDITOR_GIZMO_PART_X, BREAK_EDITOR_GIZMO_PART_Y, BREAK_EDITOR_GIZMO_PART_Z, BREAK_EDITOR_GIZMO_PART_CENTER } BreakEditorGizmoPart;

typedef struct BreakEditorGizmo BreakEditorGizmo;   /* opaque */
BreakEditorGizmo *break_editor_gizmo_create(void);
void break_editor_gizmo_destroy(BreakEditorGizmo *g);
void break_editor_gizmo_set_mode(BreakEditorGizmo *g, BreakEditorGizmoMode mode);   /* NONE hides */
void break_editor_gizmo_attach(BreakEditorGizmo *g, BreakEditorDoc *doc, BreakEditorEntityId id); /* NONE detaches */

/* Handle geometry for hit-testing AND for the Task 3 renderer (single source of truth): */
typedef struct BreakEditorGizmoHandle { BreakEditorGizmoPart part; f32 aabb_min[3]; f32 aabb_max[3]; } BreakEditorGizmoHandle;
usize break_editor_gizmo_handles(const BreakEditorGizmo *g, BreakEditorGizmoHandle *out, usize capacity); /* ≤ 24 */

/* Pointer drive (viewport-local logical px): */
BreakEditorGizmoPart break_editor_gizmo_hit(const BreakEditorGizmo *g, const BreakEditorCamera *cam, f32 x, f32 y, f32 w, f32 h);
bool break_editor_gizmo_begin_drag(BreakEditorGizmo *g, const BreakEditorCamera *cam, f32 x, f32 y, f32 w, f32 h); /* false when no handle hit */
bool break_editor_gizmo_drag(BreakEditorGizmo *g, const BreakEditorCamera *cam, f32 x, f32 y, f32 w, f32 h);      /* applies UNDOABLE doc commands */
void break_editor_gizmo_end_drag(BreakEditorGizmo *g);
```

- Drag math (define + pin): translate on axis = project mouse ray onto the handle axis using closest-point-between-two-lines (ray from camera, axis line through entity pivot); delta applied via `break_editor_doc_set_field_f32` commands (undoable — pin undo restores pre-drag value); rotate mode maps horizontal drag to euler degrees on the axis field (document sign convention); scale mode per-axis multiplicative from drag distance (clamp ≥ 0.01); CENTER handle = free translate in the camera-facing plane. During a drag, aggregate into ONE undoable command (begin-drag snapshots old values; drag updates write through a coalescing command — define: the command is created at begin_drag, updated during drag, committed at end_drag; pin by single-undo-reverts-whole-drag test). Camera moves (orbit/pan/zoom) are NOT undoable (view state).
- Bounded: handles ≤ 24; degenerate axis/ray parallelism → drag no-op (bounded false); NaN/Inf guard on computed deltas (reject).

- [ ] RED: mode/attach/detach; handle layout known-answers (axis handles offset along axes from pivot, scaled to screen-constant size — define the size formula and pin it); hit-test per part; translate drag along X by known pixels → known world delta (fixed camera); rotate/scale drags; single-command undo semantics; drag with no attach → false; NaN-guard test.
- [ ] GREEN: implementation; lanes build-sdd-v2*; commit.

### Task 3: GPU viewport panel + renderer + shell wiring

**Files:**
- Create: `engine/apps/editor/editor_viewport3d.h/.c`, `engine/shaders/editor_color.vert`, `engine/shaders/editor_color.frag`
- Modify: `engine/src/myui/myr/my_vgcanvas_break_rhi.h/.c` (additive `my_vgcanvas_break_rhi_blit_texture(vg, RHITexture tex, dst x/y/w/h)` — implemented with the existing post_tex pipeline inside the RHI canvas; no vtable change, no change to image-cache slots)
- Modify: `engine/apps/editor/editor_panels.c/.h`, `engine/apps/editor/editor_main.c`
- Modify: `engine/tests/test_editor_shell.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Tasks 1-2 core; RHI offscreen FBO (rhi.h:768-800: `rhi_offscreen_fbo_create_fmt`, `bind`/`bind_load` contract R617, `unbind`, `set_clear_color`); `rhi_cmd_set_viewport`/`set_scissor_top_left` (:564/:567); pipeline create (`rhi_shader_create` :481, `rhi_pipeline_create` :483, `rhi_cmd_set_uniform_mat4` :594); cube geometry hand-rolled (36 verts, unit cube) as a static vertex buffer (`rhi_buffer_create` — find exact signature in rhi.h).
- Produces (shell-internal, tested headlessly where possible):
```c
typedef struct BreakEditorViewport3D BreakEditorViewport3D;  /* GPU side, shell-owned */
BreakEditorViewport3D *break_editor_viewport3d_create(void); /* no GPU objects until first frame with a live device */
void break_editor_viewport3d_destroy(BreakEditorViewport3D *vp);
/* called from editor_main.c between break_ui_frame_begin and break_ui_render, same cmd: */
void break_editor_viewport3d_render(BreakEditorViewport3D *vp, BreakEditorDoc *doc, void *rhi_device, void *rhi_cmd, int panel_w, int panel_h);
```
- Widget: custom `my_widget` subclass `on_paint` calls `my_vgcanvas_break_rhi_blit_texture` with the current FBO `color_tex`; per-frame `my_widget_invalidate` while visible. Pointer events on the widget (`pointer_down/move/up/wheel`, my_event_dispatch.c:68-74 + grab semantics :270-297) route: left-press → gizmo hit/begin_drag else pick (select entity via shell selection); left-drag with active gizmo → gizmo_drag; right/alt-drag → orbit; middle/shift-drag → pan; wheel → zoom. All camera/gizmo math calls the Task 1-2 core with the widget's CURRENT rect (per-frame updated).
- Layout: middle row becomes outliner `w:25%` + viewport `w:1f h:100%` + inspector `w:28%` (adjust, keep both existing panels); palette/console unchanged.
- W/E/R/Q/F wiring: update `shell_do_*` handlers to call gizmo_set_mode / camera focus on selected; keep status-bar labels in sync (Phase 1 behavior preserved for label text).
- FBO lifecycle: create lazily on first render with size = panel pixel size (logical × input scale); recreate only on size change; `bind` = clear (R617 contract); skip render when panel < 32×32.
- Headless: `test_editor_shell` extension — viewport widget exists in tree, W/E/R/Q update gizmo mode label/state, F on selection updates camera target (assert via shell accessor), pointer events on the viewport widget reach the core (dummy PAL inject), no GPU calls occur in the dummy-PAL path (guard: viewport3d_render never called when device is NULL).

- [ ] RED: shell headless tests above (they must fail before wiring); CPU-observable parts only.
- [ ] GREEN: implementation; `editor` builds and links on all configured backends present on this host.
- [ ] Lanes: build-sdd-v3, -asan, -tsan focused green (editor lane incl. new shell tests); full build of default targets.
- [ ] Live smoke run (honest evidence): `DISPLAY=:0 timeout -s TERM 6 ./editor /tmp/vp_smoke.bscn` (or the Task 5-established equivalent); record exact command, log lines, and that it is a smoke run, not GPU validation. If a scripted interaction is feasible (env-var-driven? do NOT add one — keep scope), note manual verification as pending.
- [ ] Docs: `docs/design/editor_viewport.md` (camera/gizmo math contracts, FBO/blit path, damage/invalidate policy, pick proxy semantics, Phase 3+ exclusions: selection highlight outline, rotation rings, snap grid, multi-select, scene-fidelity rendering).
- [ ] Commit(s).

### Task 4: Validation and documentation closeout

**Files:**
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 4 subproject 5: viewport/gizmo/focus delivered; scene-fidelity/SCENE_NODES ownership still pending), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md` (evidence-backed boxes only), `docs/design/editor_phase1.md` or new `editor_viewport.md` final states.
- Modify: `engine/CMakeLists.txt` only if a real fix is needed.

- [ ] Clean normal tree: full default build + editor lane (all editor tests incl. viewport/gizmo) + `editor` executable.
- [ ] ASan/UBSan + TSan trees: editor lane green, zero reports.
- [ ] `ENGINE_BUILD_TESTS=OFF` tree builds break_editor + editor; nm hook-free archives.
- [ ] Full non-graphics/non-fuzz suite; classify failures (graphics / platform-skip / pre-cleared flake test_break_replication_fragment / branch-caused=fix).
- [ ] Contract test still green (break_editor source list changed — update assertions if tracked).
- [ ] Live smoke rerun post-merge-candidate state; record command/output.
- [ ] `git diff --check` clean on branch range.

## Cross-cutting Review Gates

- RED before production code per task; GREEN normal/ASan/TSan after.
- All doc mutations from gizmo drags are single undoable commands (pin: one undo reverts a whole drag).
- Camera/gizmo/pick math is pure CPU and deterministic; no pointer/World/RHI handles in `editor_viewport.h`/`editor_gizmo.h` public surfaces beyond Phase 1's documented doc accessors.
- The myui RHI-canvas change is strictly additive (new function); existing slots and the image cache contract unchanged; Phase 1's my_list_view fix untouched.
- GPU code carries no behavior claims beyond compile/link + recorded smoke run.
- Widget callbacks never call `world_*`; camera changes are view state (non-undoable) by design.
- A task completes only after focused code review, doc update, and `git diff --check` on its range.
