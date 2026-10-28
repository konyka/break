# Scene Editor Phase 1 (shell + outliner + inspector + undo/redo + save/load) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver the Stage 4 Phase 1 scene editor: a `break_editor` C11 editor-core library (document model, selection, command-based undo/redo, scene save/load via `scene_serial`) plus an `editor` executable shell (BreakUI window, outliner, inspector, console, command palette, shortcut map) — with headless dummy-PAL tests — deferring 3D viewport/gizmo, diagnostics panels, and Lua console to later phases.

**Architecture:** Editor core is a formal optional C11 static library `break_editor` in `engine/CMakeLists.txt` (same pattern as `runtime_core`/`break_lua`: top-level, tests-independent, not linked into `engine`/`engine_demo`/`dxx_break`). It wraps the ECS `World` with an editor document (entity display names, selection set, dirty flag) and a bounded command stack; all mutations go through commands (apply/revert) so undo/redo is exact and snapshot-free. The shell executable `editor` lives in `engine/apps/editor/`, uses the BreakUI bridge (`engine/src/ui/myui_break.h`) for a GPU-accelerated myui window on the engine Platform, and is drivable headless through the dummy PAL for logic and smoke tests. Scene persistence uses `scene_serial` BSCN/JSON; entity names (absent from ECS and BSCN) live in an editor sidecar JSON document.

**Tech Stack:** C11 editor core and shell (matches `engine/apps/` precedent; the C++11 framework stays untouched); myui widgets (list_view/edit/menu/dialog/scroll_view); BreakUI bridge; ECS (`engine/src/ecs/ecs.h`); scene_serial BSCN/JSON; dummy PAL + PPM smoke tests; CTest; ASan/UBSan/TSan.

## Global Constraints

- C11 for everything in this plan (editor core + shell); do not modify the C++11 `framework/` tree; do not add C++ to the engine build for this plan.
- `break_editor` is a formal optional static lib: top-level `add_library` in `engine/CMakeLists.txt`, `C_STANDARD 11`, produced when `ENGINE_BUILD_TESTS=OFF`, NOT linked into `engine`/`engine_demo`/`dxx_break`.
- The `editor` executable links `break_editor`, `engine`, `break_myui`, `m` and goes through `engine_link_rhi_backend(editor)` (precedent: `engine/CMakeLists.txt:1594-1596` for engine_demo, `:1243-1251` for dxx_break).
- ECS `World` mutation is editor-owner-thread only; the UI layer mutates the document exclusively through commands — no direct `world_*` calls from widget callbacks.
- No snapshot/delta-based undo (it requires a full `BreakComponentSchemaRegistry` — out of scope). Undo/redo is command-based: every mutation command implements exact apply/revert.
- ECS has no entity names (`engine/src/ecs/ecs.h` has none) and BSCN does not store names — the editor document owns a name map keyed by `Entity{index,generation}`; on save it is written as a sidecar `<scene>.editor.json`; on load the sidecar is optional (missing sidecar => generated names `entity_<index>_<generation>`).
- Bounded everything: entity name cap 128 bytes; command stack cap 256 entries (bounded drop-oldest with a documented flag); outliner row cap derives from `world->entity_count` (≤ `ECS_MAX_ENTITIES` 64K, but list_view is virtualized); inspector field strings ≤ 128 bytes. Count AND byte overflow checks with bounded failure results.
- Scene save/load uses `scene_serial.h`: `scene_save_binary(const World*, const Scene*, path, const SerializeOptions*)` (:173-174), `scene_load_binary(World*, Scene*, path)` (:175, REPLACE semantics), JSON variants `scene_save_json`/`scene_load_json` (:201-203). Editor document save = BSCN + sidecar JSON; load = BSCN + optional sidecar.
- No raw `World*`/RHI handles/OS handles in `break_editor` PUBLIC API — opaque `BreakEditorDoc`, `BreakEditorCmdStack`; the shell translation unit may touch `World`/BreakUI directly (it is the owner).
- myui input facts the shell must honor: `my_event_t` (`engine/src/myui/mypal/my_event.h:81-114`), `MY_EVENT_KEY_DOWN/UP`, `u.key.key` (ASCII 32..126 identity; `MY_KEY_RETURN=0x100`..`MY_KEY_F12`), `u.key.modifiers` (`MY_KEYMOD_SHIFT=1/CTRL=2/ALT=4`); widget event subscription `my_widget_on(widget, "click"/"changed"/..., cb, ctx)` (`engine/src/myui/myui/my_widget.h:271`).
- Headless testing precedents to follow: dummy PAL `my_pal_dummy.h` (`my_pal_dummy_inject_event` :53, `my_pal_main_loop_pump_n` :61); window-manager test block `engine/CMakeLists.txt:2213-2220`; widget-level direct `vtable->on_event` driving (`engine/tests/test_myui_edit.c:11-35`); PPM pixel assertions (`engine/tools/myui_widgets_demo.c:74-78,393-408`).
- Test conventions: `engine/tests/test_framework.h` macros (`TEST/ASSERT_*/RUN_TEST`), per-pid temp paths via `test_tmp()` (`test_framework.h:26-46`), source-inline test executables (precedent `test_scene_serial` at `engine/CMakeLists.txt:3728-3733`).
- Normal + ASan/UBSan + TSan focused lanes per task (options `ENGINE_USE_ASAN/UBSAN/TSAN`); sanitizer trees may build the focused subset only (established precedent).
- Docs wording: editor Phase 1 is a formal optional tool target, NOT a production editor product; Stage 4 acceptance items not delivered here (3D viewport, gizmo, profiler panel, Lua console, remote session) stay explicitly pending.
- Shortcut map for Phase 1 (verbatim from the accepted requirement): `Q/W/E/R` tool selection state (select/translate/rotate/scale — state only, no gizmo yet), `F` focus-selected (camera focus is Phase 2 — Phase 1 records the intent event only), `Ctrl+S` save, `Ctrl+Z` undo, `Ctrl+Y` redo, `Ctrl+P` command palette.

---

## File and Target Map

- Create: `engine/src/editor/editor_doc.h/.c` — opaque `BreakEditorDoc`: wraps `World*` (borrowed), name map, selection set, dirty flag, entity add/remove/rename/select API (all via commands internally).
- Create: `engine/src/editor/editor_cmd.h/.c` — opaque `BreakEditorCmdStack`: bounded command stack (cap 256, drop-oldest flagged), command vtable `{apply, revert, destroy, describe}`, built-in commands (add_entity, remove_entity, rename_entity, set_component_field for the registered transform fields).
- Create: `engine/src/editor/editor_scene.h/.c` — save/load: BSCN via scene_serial + sidecar `<path>.editor.json` (names + selection), load with generated-name fallback.
- Create: `engine/src/editor/editor_components.h/.c` — editor-side component field registry: for each editable component type (id, display name, bounded field descriptors {name, offset, type f32}) — Phase 1 registers the transform component(s) actually used by the demo scene (locate them in `engine/apps/duanxianxia/` or `engine/src/scene/`; if no shared transform component exists, define the editor's own `EditorTransform {f32 pos[3], rot[3], scale[3]}` component id `EDITOR_COMPONENT_TRANSFORM` and register it into the doc's World at doc create).
- Create: `engine/apps/editor/editor_main.c` — shell: platform + RHI + BreakUI window, layout (menu bar / outliner / inspector / console log view), shortcut routing, command palette.
- Create: `engine/apps/editor/editor_panels.h/.c` — panel builders over myui widgets (outliner list_view adapter, inspector form, console buffer) — kept separate from main so headless tests can build panels without the RHI window.
- Create: `engine/tests/test_editor_doc.c`, `test_editor_cmd.c`, `test_editor_scene.c` — core logic tests (no UI).
- Create: `engine/tests/test_editor_shell.c` — headless dummy-PAL shell test (window build, panel wiring, shortcut dispatch, PPM smoke).
- Modify: `engine/CMakeLists.txt` — `break_editor` lib + `editor` executable + four test executables + contract ctest.
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 4 status), and create `docs/design/editor_phase1.md`.

---

### Task 1: Editor document + command stack (undo/redo core)

**Files:**
- Create: `engine/src/editor/editor_doc.h/.c`, `engine/src/editor/editor_cmd.h/.c`
- Create: `engine/tests/test_editor_doc.c`, `engine/tests/test_editor_cmd.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces (verbatim, later tasks consume):
```c
typedef struct BreakEditorDoc BreakEditorDoc;
typedef struct BreakEditorCmdStack BreakEditorCmdStack;

BreakEditorDoc *break_editor_doc_create(void);            /* owns an internal World */
void break_editor_doc_destroy(BreakEditorDoc *doc);
void *break_editor_doc_world(BreakEditorDoc *doc);        /* borrowed World*, shell-only */

/* command-driven mutations (all fail bounded): */
u32  break_editor_doc_add_entity(BreakEditorDoc *doc, const char *name); /* 0 on failure; returns editor entity handle = Entity flattened (index|generation<<32 is FORBIDDEN — use struct) */
```
(Decision to implement and pin in tests: use `typedef struct { u32 index; u32 generation; } BreakEditorEntityId` matching `Entity` layout in `engine/src/ecs/ecs.h:14-17`; no u64 flattening.)
```c
bool break_editor_doc_remove_entity(BreakEditorDoc *doc, BreakEditorEntityId id);
bool break_editor_doc_rename_entity(BreakEditorDoc *doc, BreakEditorEntityId id, const char *name);
usize break_editor_doc_entity_count(const BreakEditorDoc *doc);
bool break_editor_doc_entity_at(const BreakEditorDoc *doc, usize i, BreakEditorEntityId *out_id, const char **out_name); /* borrowed name */
bool break_editor_doc_is_dirty(const BreakEditorDoc *doc);

BreakEditorCmdStack *break_editor_cmd_stack_create(u32 capacity /* 0 => 256 */);
void break_editor_cmd_stack_destroy(BreakEditorCmdStack *stack);
bool break_editor_undo(BreakEditorDoc *doc);   /* false when empty */
bool break_editor_redo(BreakEditorDoc *doc);   /* false when empty */
```
- Internals: doc owns one `World` (via `world_create`/`world_destroy`, `engine/src/ecs/ecs.h:118-119`), a bounded name map (open-addressing or sorted array; key = {index,generation}; name ≤ 128 bytes), and one cmd stack. Every public mutation routes through a command object {apply, revert, destroy, describe(char buf[128])} pushed onto the stack; overflow drops the oldest executed command (flag `dropped_oldest` readable for tests) and clears redo.

- [ ] RED: tests — add/remove/rename entities; names bounded (128-byte cap, truncation or bounded rejection — pick rejection `false`, document); remove nonexistent → false; undo add → entity gone and name freed; redo add → SAME Entity id restored (pin: command stores the created id; revert destroys by id; redo re-creates — verify ECS allows id reuse deterministically or store component snapshot in the command; choose the design that makes redo-after-undo exact and test it); stack overflow at cap → oldest dropped + flag; redo cleared on new mutation; dirty flag set/cleared; OOM injection on command allocation → mutation fails bounded, doc unchanged.
- [ ] GREEN: implementation + `break_editor` target (top-level static lib; links nothing beyond `m`; compiles `editor_doc.c`/`editor_cmd.c` + needs `ecs.c` — DEPEND on the existing formal `break_ecs_replication` library which already owns `ecs.c` (Task 1 of Stage 2, `engine/CMakeLists.txt:313-324`) via `target_link_libraries(break_editor PUBLIC break_ecs_replication)`; do NOT compile ecs.c again).
- [ ] Contract ctest (precedent `test_break_lua_target_contract.cmake`): break_editor exists with tests OFF, links break_ecs_replication, not referenced by engine/demos.
- [ ] Lanes: build-sdd-e1, build-sdd-e1-asan, build-sdd-e1-tsan; focused green.
- [ ] Commit "feat(editor): ...".

### Task 2: Scene save/load round-trip (BSCN + editor sidecar)

**Files:**
- Create: `engine/src/editor/editor_scene.h/.c`
- Create: `engine/tests/test_editor_scene.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Task 1 doc API; `scene_serial.h:173-177` (`scene_save_binary`/`scene_load_binary`/`scene_probe_binary`); the `Scene*` render-scene argument: Phase 1 passes a doc-owned empty render `Scene` (check `asset.h:151-186` — if `scene_save_binary` tolerates a zeroed Scene, use that; otherwise document the minimal Scene the editor constructs).
- Produces:
```c
bool break_editor_doc_save(BreakEditorDoc *doc, const char *path);  /* <path> BSCN + <path>.editor.json sidecar; clears dirty */
bool break_editor_doc_load(BreakEditorDoc *doc, const char *path);  /* REPLACE semantics; missing sidecar => generated names */
```
- Sidecar JSON (hand-rolled, bounded; do NOT add a JSON dependency — check whether the repo already has one under engine/src or engine/external first, e.g. the cJSON used by myui echarts adapter `engine/src/myui/myui/echarts/`; reuse what exists): `{"version":1,"entities":[{"index":u32,"generation":u32,"name":"..."}],...}` with a 4 MiB sidecar cap and UTF-8-escaped quotes.

- [ ] RED: round-trip — build doc (3 entities, names, transform components), save, destroy, load into fresh doc: entity count/generations equal, names equal, components byte-equal; load without sidecar → generated `entity_<index>_<generation>` names; save→load clears/sets dirty correctly; corrupt sidecar → load still succeeds with generated names + warning log; oversize name in sidecar bounded-rejected; file > 64 MiB BSCN rejected by scene_serial's own cap (verify, don't re-implement).
- [ ] GREEN: editor_scene.c; add to break_editor; link needs scene_serial — check which existing target owns `scene_serial.c` (if none formal, add `src/scene/scene_serial.c` + its minimal deps explicitly to break_editor sources, single ownership, no duplicate compilation with test_scene_serial which compiles its own copy at `engine/CMakeLists.txt:3728-3733` — that's the existing inline pattern, acceptable, but break_editor must own exactly one copy).
- [ ] Lanes: build-sdd-e2*; focused green incl. Task 1 tests.
- [ ] Commit.

### Task 3: Editor component registry + inspector data model

**Files:**
- Create: `engine/src/editor/editor_components.h/.c`
- Modify: `engine/tests/test_editor_doc.c` (extend) or create `engine/tests/test_editor_components.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces:
```c
typedef struct BreakEditorField { char name[32]; u32 offset; u8 type; /* 0=f32 */ } BreakEditorField;
typedef struct BreakEditorComponentInfo {
    u32 component_id; char display_name[32];
    BreakEditorField fields[8]; u32 field_count;
} BreakEditorComponentInfo;

usize break_editor_doc_component_count(const BreakEditorDoc *doc); /* registered editable types */
bool break_editor_doc_component_info(const BreakEditorDoc *doc, usize i, BreakEditorComponentInfo *out);
bool break_editor_doc_has_component(const BreakEditorDoc *doc, BreakEditorEntityId id, u32 component_id);
bool break_editor_doc_get_field_f32(const BreakEditorDoc *doc, BreakEditorEntityId id, u32 component_id, u32 field_index, f32 *out);
bool break_editor_doc_set_field_f32(BreakEditorDoc *doc, BreakEditorEntityId id, u32 component_id, u32 field_index, f32 value); /* via command — undoable */
```
- Decision to implement: register the editor's own `EditorTransform` component (id chosen above `WORLD_MAX_COMPONENTS`-safe bound, see `ecs.h` component cap 128 — verify a free id; document it) registered into the doc World at create via `world_register_component` (`ecs.h:124`); add/remove-component commands included: `break_editor_doc_add_component(doc, id, component_id)` / `remove_component` (undoable, component bytes snapshotted into the command ≤ component size, cap 256 bytes).

- [ ] RED: registry enumeration; has/get/set field; set via command → undo restores previous value byte-exact; add/remove component undoable with byte snapshot; unregistered component id → bounded false; field index OOB → false; string→f32 parse helper for inspector (`break_editor_parse_f32(const char*, f32*)` — strict, no `strtod` locale surprises beyond C89 behavior, bounded 64-byte input).
- [ ] GREEN: implementation; lanes build-sdd-e3*; commit.

### Task 4: Editor shell — window, layout, panels, shortcuts (headless-testable)

**Files:**
- Create: `engine/apps/editor/editor_main.c`, `engine/apps/editor/editor_panels.h/.c`
- Create: `engine/tests/test_editor_shell.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Task 1-3 doc/cmd/component APIs; BreakUI bridge `engine/src/ui/myui_break.h:32-64` for the real window; dummy PAL path for tests (`my_pal_dummy.h`); widgets: `my_list_view` (adapter vtable `engine/src/myui/myui/widgets/my_list_view.h:25-36,80-84`), `my_edit` (`my_edit.h:49-59`, "changed"/"activate"), `my_button` ("click"), `my_menu`/`my_menu_popup` (`my_menu.h:23-34`), `my_label`, `my_scroll_view`; layout via `my_widget_set_layouter` + linear layouter (`my_layout.h:43-86`) with `"w:50% h:1f"`-style params (`my_widget_set_layout_params`, `my_layout.h:27`).
- Produces (for tests):
```c
typedef struct BreakEditorShell BreakEditorShell;
BreakEditorShell *break_editor_shell_create_for_test(void); /* dummy PAL, no RHI */
void break_editor_shell_destroy(BreakEditorShell *shell);
bool break_editor_shell_dispatch_key(BreakEditorShell *shell, u32 key, u32 modifiers); /* returns consumed */
```
- Shell layout (per accepted requirement): menu/toolbar top; left outliner (list_view + add/remove/rename via my_edit inline or dialog); right inspector (component list + f32 fields via my_edit rows); bottom console (read-only multi-line my_text_area or label list, fed by a bounded 64-entry log ring); status bar (dirty marker, entity count, last command description).
- Shortcut routing: a single key-table {key, modifiers, action} in editor_panels.c; Q/W/E/R set tool state label; Ctrl+S save-as dialog path (Phase 1: fixed `test_tmp()`-style session path settable via `break_editor_shell_set_scene_path`); Ctrl+Z/Y undo/redo; Ctrl+P opens palette = my_edit + my_list_view filtered over registered command names (commands: add entity, remove selected, rename selected, save, undo, redo, tool select/translate/rotate/scale); palette executes on "activate".
- Widget callbacks never call `world_*` directly — only `break_editor_doc_*`/`break_editor_undo/redo` (assert by code review + a test that no UI callback bypasses the command stack: e.g. rename via outliner then undo must revert the displayed name).

- [ ] RED: headless test — create shell for test; inject key events via `my_pal_dummy_inject_event` or direct `break_editor_shell_dispatch_key`; assert: Ctrl+Z after add-entity removes the outliner row (row count via list adapter); Ctrl+P palette opens and filters; Q/W/E/R updates tool state label text; Ctrl+S saves to the configured path (file exists); PPM smoke: paint the shell window to `my_lcd_mem` and assert non-background pixels > 0 (precedent myui_widgets_demo).
- [ ] GREEN: editor_panels.c + editor_main.c; `editor` executable target (links `break_editor engine break_myui m` + `engine_link_rhi_backend(editor)`); test executable links `break_editor` + dummy PAL sources per the `:2213-2220` precedent.
- [ ] Lanes: build-sdd-e4*; focused green incl. all prior editor tests.
- [ ] `docs/design/editor_phase1.md`: shell architecture, shortcut table, panel map, what remains Phase 2+.
- [ ] Commit.

### Task 5: Validation and documentation closeout

**Files:**
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md`, `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`
- Modify: `engine/CMakeLists.txt` only if a real fix is needed

- [ ] Clean normal tree: build `break_editor` + `editor` + all four editor tests + full default targets; focused ctest green.
- [ ] ASan/UBSan + TSan trees: focused editor lane green, zero sanitizer reports.
- [ ] `ENGINE_BUILD_TESTS=OFF` builds `break_editor` and `editor`; nm on `libbreak_editor.a` shows zero test-hook symbols.
- [ ] Full non-graphics/non-fuzz suite in the normal tree; classify failures (graphics-gated / platform-skip / pre-existing flake `test_break_replication_fragment` / branch-caused = must fix).
- [ ] Smoke-run `editor` binary headless if a dummy/headless RHI path exists (ENGINE_RHI_BACKEND=headless build) — document the exact command and result; do not claim GPU validation.
- [ ] Docs: roadmap Stage 4 — mark subprojects 1 (shell/palette), 2 (outliner/inspector), 3 (property editing + undo/redo), 4-partial (asset browser NOT delivered — keep unchecked), 5 (viewport/gizmo — unchecked; scene save-load part delivered) precisely; subprojects 6/7 unchecked. Create/refresh `docs/design/editor_phase1.md` delivered-facts.
- [ ] `git diff --check` clean on branch range.

## Cross-cutting Review Gates

- Every task: RED evidence before production code; GREEN normal/ASan/TSan after.
- No widget callback calls `world_*` directly; all mutations through commands (spot-check in review).
- Every capacity: count AND byte overflow checks + bounded failure + test.
- Legacy untouched: `engine/src/ecs/*`, `engine/src/scene/*`, myui sources, `script_lua.*` — zero-diff expectation except where a task explicitly adds sources to targets.
- `break_editor` and `editor` stay out of `engine`/`engine_demo`/`dxx_break`; no new dependency of `engine` on editor code.
- Docs never claim Phase 2+ deliverables (3D viewport, gizmo, profiler/console diagnostics panels beyond the log ring, Lua console, remote session).
- A task completes only after focused code review, doc update, and `git diff --check` on its range.
