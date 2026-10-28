# Scene Editor Phase 3 (Asset Browser + Profiler Panel + Lua Console) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver Stage 4 Phase 3: an asset browser (directory listing of mounted asset dirs), a profiler diagnostics panel (per-region frame timing), and a Lua console (evaluate Lua against the Stage 3 `break_lua` facade, with bounded ECS batch application into the editor document as undoable commands) — all headless-testable except GPU pixels.

**Architecture:** One additive PAL function (`platform_list_dir`) fills the repo's missing directory-listing primitive (POSIX `opendir` + Win32 `FindFirstFile`), consumed by an editor-side asset browser model in `break_editor` (pure CPU, bounded, filterable). The profiler panel reads the existing `core/profiler.h` per-frame region data (no profiler changes). The Lua console owns one `BreakLuaRuntime` (Stage 3 facade, linked by the `editor` executable and tests), routes script `print` and results into the existing console ring, and drains the ECS batch into the doc through the Phase 1 command stack (undoable). All panel logic lives in `editor_panels`-style shell modules with the dummy-PAL test path.

**Tech Stack:** C11; `break_editor` (Phase 1-2); `break_lua` (Stage 3); `core/profiler.h`; myui widgets (list_view/edit/text_area); dummy PAL tests; ASan/UBSan/TSan.

## Global Constraints

- C11; no new dependencies. Legacy surfaces unchanged except ONE additive PAL function `platform_list_dir` (engine/src/platform/) with tests; myui/RHI untouched this phase.
- Phase 1/2 invariants hold: doc mutations only via undoable commands; widget callbacks never call `world_*`; `break_editor`/`break_lua` stay out of engine/demos link closure of OTHER products (the `editor` executable DOES link break_lua from this phase on).
- Lua console boundaries (Stage 3 contract): one runtime, owner thread = shell thread; instruction budget armed for console evaluations (config e.g. 1,000,000 instructions, documented); sandbox as delivered (no io/debug/package/coroutine/raw*); `print` captured into the console ring; evaluation errors shown as bounded console lines (128-byte rule).
- ECS batch application: console scripts enqueue `brk.ecs.spawn()` / `brk.ecs.set(...)`; the shell drains the batch AFTER each evaluation and applies records as undoable editor commands (spawn → add_entity with a script-given or generated name; set → set_field_f32). Unknown/oversized records → bounded console error lines, never partial application of a single record. Batch capacity 256 (create(0) default) — a full batch surfaces its own bounded failure to the script (Stage 3 behavior), which the console displays.
- Profiler panel reads `profiler_last_frame()` (`engine/src/core/profiler.h:66`) and region data; the profiler is per-process global — the panel is a VIEW, never mutates profiler state, never enables/disables it (documented; the editor executable may enable the profiler in main, its own process).
- Asset browser scope: list DIR-mounted filesystem trees only (VFS paks: enumeration NOT in scope — document); root path configurable (default `engine/apps/editor/` assets dir or CWD); bounded: path ≤ 1024 bytes, entries ≤ 4096 per directory, entry name ≤ 256 bytes, depth ≤ 8; symlink policy: do not follow (document); sorting: directories-first then names (byte-wise, deterministic).
- Bounded everything, count+byte overflow checks, OOM-injection tests via `BREAK_EDITOR_TESTING` hooks; owner-thread documented; no raw World*/lua_State*/RHI handles in public APIs.
- Headless tests for all logic; GPU not involved this phase (no new rendering); live smoke rerun at closeout.
- Docs: honest wording — profiler panel is a local view of the existing profiler (no remote capture, no GPU counters); Lua console is editor-local (remote session remains Stage 5-gated pending).

---

## File and Target Map

- Create: `engine/src/platform/platform_fs.h/.c` — `platform_list_dir(path, entries, capacity, out_count)` + `PlatformDirEntry {char name[256]; bool is_dir;}` (bounded; POSIX opendir/readdir; Win32 FindFirstFile under `_WIN32`).
- Create: `engine/src/editor/editor_assets.h/.c` — asset browser model: root, current dir (relative), listing cache, extension filter set, selection; pure CPU.
- Create: `engine/src/editor/editor_lua.h/.c` — console core: owns `BreakLuaRuntime` + `BreakLuaEcsBatch`; eval(input) → module chunk; print capture; batch drain → doc commands.
- Create: `engine/apps/editor/editor_panel_assets.c`, `editor_panel_profiler.c`, `editor_panel_lua.c` — panel builders + event wiring (following editor_panels.c patterns; register into the shell layout).
- Modify: `engine/apps/editor/editor_panels.c/.h` — layout: bottom area becomes tabbed or split console/lua row (define: console left, lua right), assets panel as left-bottom under outliner or a tab — pick one, document; profiler panel as right-bottom under inspector.
- Modify: `engine/CMakeLists.txt` — new sources into targets; `editor` + tests link `break_lua`; new test executables.
- Create: `engine/tests/test_editor_assets.c`, `test_editor_lua.c`; modify `engine/tests/test_editor_shell.c` (panel presence + key/event routing).
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 4 subprojects 4 and 7-partial), new `docs/design/editor_panels_phase3.md`.

---

### Task 1: platform_list_dir + asset browser model

**Files:**
- Create: `engine/src/platform/platform_fs.h/.c`
- Create: `engine/src/editor/editor_assets.h/.c`
- Create: `engine/tests/test_editor_assets.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces (verbatim):**
```c
/* engine/src/platform/platform_fs.h */
typedef struct PlatformDirEntry { char name[256]; bool is_dir; } PlatformDirEntry;
/* Lists one directory level, bounded. Returns false on OS error/overflow of path.
 * entries written until capacity; out_count = TOTAL entries found (may exceed capacity
 * => truncation is detectable). Not recursive. Does not follow symlinks (POSIX: lstat). */
bool platform_list_dir(const char *path, PlatformDirEntry *entries, u32 capacity, u32 *out_count);

/* engine/src/editor/editor_assets.h */
typedef struct BreakEditorAssets BreakEditorAssets;
BreakEditorAssets *break_editor_assets_create(const char *root_path);   /* root must exist + be a dir */
void break_editor_assets_destroy(BreakEditorAssets *assets);
bool break_editor_assets_enter(BreakEditorAssets *assets, const char *rel_subdir);  /* ".." allowed, clamped at root */
bool break_editor_assets_up(BreakEditorAssets *assets);
usize break_editor_assets_count(const BreakEditorAssets *assets);       /* after filter */
bool break_editor_assets_entry_at(const BreakEditorAssets *assets, usize i, const char **out_name, bool *out_is_dir); /* borrowed */
void break_editor_assets_set_filter(BreakEditorAssets *assets, const char *extensions_csv); /* e.g. "bscn,json,lua"; NULL/"" = all */
const char *break_editor_assets_current_rel(const BreakEditorAssets *assets); /* borrowed, "" = root */
bool break_editor_assets_abs_path(const BreakEditorAssets *assets, usize i, char *out, usize cap); /* bounded */
```
- Path safety: reject `..` escaping the root (normalize and prefix-compare); reject absolute subdirs; reject names containing '/'; NFC/encoding: byte-wise handling, no re-encoding (document).
- Sorting: directories first, then byte-wise name order — deterministic.
- The doc is NOT involved; asset browser is a view model. Loading a `.bscn` via the browser wires in Task 3's panel (calls `break_editor_doc_load`).

- [ ] RED: tests with `test_tmp()` fixture trees — list files/dirs; capacity truncation detectable; enter/up with root clamping; `..` escape rejected; absolute path rejected; filter on/off; sorting deterministic; empty dir; nonexistent root → create fails; symlink not followed (POSIX lane); name >255 bytes bounded (skip entry, continue); OOM sweeps.
- [ ] GREEN: implementation; `platform_fs.c` into `engine` src list? — DECISION: `platform_list_dir` is platform-layer, used by editor only in Phase 3; put it in `engine` (platform siblings live there) AND verify no symbol/behavior regressions, OR keep it in `break_editor` — choose `engine/src/platform/` compiled into `engine` ONLY IF that's where platform_*.c live (they are: platform.h input.c etc. in `engine`'s target); check engine/CMakeLists.txt source list and follow the existing pattern; `editor_assets.c` into `break_editor`.
- [ ] Lanes: build-sdd-p31, -asan, -tsan; focused green.
- [ ] Commit.

### Task 2: Lua console core (editor_lua)

**Files:**
- Create: `engine/src/editor/editor_lua.h/.c`
- Create: `engine/tests/test_editor_lua.c`
- Modify: `engine/CMakeLists.txt` (`break_editor` does NOT link break_lua — keep the console core in break_editor but with break_lua as a PUBLIC link? NO: decide cleanly — `editor_lua.c` consumes break_lua, so `target_link_libraries(break_editor PUBLIC break_lua)`; verify this doesn't pull break_lua into engine/demos (it doesn't — they don't link break_editor). Update the contract test accordingly.)

**Interfaces (verbatim):**
```c
typedef struct BreakEditorLuaConsole BreakEditorLuaConsole;

typedef void (*BreakEditorLuaLogFn)(void *ctx, const char *line); /* bounded lines, ≤128 bytes enforced by callee */

BreakEditorLuaConsole *break_editor_lua_create(BreakEditorDoc *doc, BreakEditorLuaLogFn log_fn, void *log_ctx);
void break_editor_lua_destroy(BreakEditorLuaConsole *console);

/* Evaluates `input` as a Lua chunk in the console module environment:
 * - wraps `return <expr>` convenience (bare expression input auto-returns),
 * - print() output and the (single) result value are logged via log_fn,
 * - errors → log_fn("error: ...") bounded,
 * - armed with the console instruction budget (1,000,000; main-coroutine scope per Stage 3 contract),
 * - after a successful eval, drains the ECS batch and applies records to the doc as undoable commands. */
bool break_editor_lua_eval(BreakEditorLuaConsole *console, const char *input);

usize break_editor_lua_pending_records(const BreakEditorLuaConsole *console); /* test accessor: batch residue, should be 0 after eval */
```
- Implementation notes: use Stage 3 facade — one `BreakLuaRuntime` (config: max_modules 8, instruction_budget 1000000), `break_lua_ecs_batch_create(0)` (default 256) + `break_lua_runtime_bind_ecs_batch`; load a persistent "console" module whose environment gets the print capture; eval = load chunk via a fresh named module per eval OR a single module with `load_module` replacing a thunk — CHOOSE: accumulate a module `console` and call its thunk function set per eval via `break_lua_runtime_call`; simplest correct shape wins, document it. Stage 3 call contract (break_lua.h:234+) governs what functions are callable — console chunk defines a global function and eval calls it.
- Batch drain mapping: `BREAK_LUA_ECS_RECORD` kinds (check engine/src/script/break_lua.h:501-547 for exact kind/value enums and record layout) → spawn = `break_editor_doc_add_entity(doc, name-or-NULL)`; set(component, field, value) — map component/field NAMES to the Phase 3 registry (EditorTransform fields pos.x etc.); unknown component/field → bounded console error line; partial record never applied.
- Undo: each applied record = one editor command (existing kinds); a multi-record eval = multiple commands (document; single-record case is the common one).

- [ ] RED: tests — eval arithmetic returns result logged; print captured (multi-line bounded); syntax error / runtime error bounded error lines; budget trip (infinite loop) → bounded error, console still usable next eval; spawn record creates entity (undoable — undo removes it); set record on selected/last-spawned entity sets field (undo restores); unknown field → error line, doc unchanged; batch residue 0 after eval; OOM sweeps; owner-thread probe.
- [ ] GREEN: editor_lua.h/.c; CMake: break_editor PUBLIC break_lua; contract test update; test target links break_lua_test variant policy — NOTE: break_lua has its own test variant `break_lua_test`; test_editor_lua links break_editor_test + break_lua_test.
- [ ] Lanes: build-sdd-p32, -asan, -tsan; focused green (incl. break_lua lanes regression).
- [ ] Commit.

### Task 3: Panels wiring (assets / profiler / lua) + layout

**Files:**
- Create: `engine/apps/editor/editor_panel_assets.c`, `editor_panel_profiler.c`, `editor_panel_lua.c`
- Modify: `engine/apps/editor/editor_panels.c/.h` (layout + registration; extend `editor_panels.h` test accessors)
- Modify: `engine/tests/test_editor_shell.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Tasks 1-2 models; profiler read API (`profiler_last_frame` :66, `ProfilerFrame` fields :19-33, region access via the frame's region storage — read profiler.h fully); myui list_view/edit/label/text_area.
- Layout decision (implement + document): bottom row becomes two columns — console (existing log ring) left `w:1f`, Lua console right `w:40%` (my_edit input + Enter evaluates, output ALSO goes to the shared console ring prefixed `lua|`); assets panel goes under the outliner as a bottom-left section `h:40%` (list_view + path label); profiler panel under the inspector `h:30%` (top-N regions by duration, N≤16, updated 4×/s — throttle documented).
- Assets panel behavior: Enter/double-click on a `.bscn` directory entry → confirm-free `break_editor_doc_load` (Phase 2 documents the world-swap + undo-stack clear; console logs the load); directories navigate; `..` row on top.
- Lua console: eval on "activate"; history (bounded 32 entries, Up/Down recall — my_edit supports? check my_edit.h; if no history support, keep history in the panel and set_text on Up/Down).
- Profiler panel: pure view; reads last frame each refresh tick; renders `name ms` rows via labels/list_view; never touches profiler state.

- [ ] RED: headless shell tests — assets panel lists fixture root (inject `break_editor_assets` with test_tmp root), navigation updates rows, `.bscn` activation loads doc (entity count changes + console line); lua panel: typed `return 1+2` + activate → console ring contains `lua| 3`; spawn via lua → outliner count +1, Ctrl+Z reverts; profiler panel populates rows after pumping a frame with profiler enabled in the test process; layout presence assertions.
- [ ] GREEN: panels + wiring; `editor` executable links break_lua (update target).
- [ ] Lanes: build-sdd-p33, -asan, -tsan; focused editor lane green; full default build.
- [ ] Live smoke rerun (same 6s DISPLAY=:0 shape); record.
- [ ] Docs: docs/design/editor_panels_phase3.md (panels, Lua console contract, asset browser scope/limits, profiler view scope); Implementation_Status.md entry.
- [ ] Commit.

### Task 4: Validation and documentation closeout

**Files:**
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 4: subproject 4 asset browser delivered-with-limits, subproject 6 profiler panel partial — only local profiler view delivered; network/render debugger pending; subproject 7 Lua console delivered editor-local; remote session still Stage 5-gated), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`.
- Modify: `engine/CMakeLists.txt` only if a real fix is needed.

- [ ] Clean normal tree: full default build + editor lane + `editor` executable; focused ctest green.
- [ ] ASan/UBSan + TSan trees: editor lane green, zero reports; break_lua lanes still green.
- [ ] `ENGINE_BUILD_TESTS=OFF` builds break_editor + editor; nm: zero test-hook symbols in production archives.
- [ ] Full non-graphics/non-fuzz suite; classify failures (graphics / platform-skip / pre-cleared flake test_break_replication_fragment + pre-existing test_vulkan golden drift / branch-caused=fix).
- [ ] Contract test green (source lists + link changes covered).
- [ ] Live smoke rerun; record command + log + honest framing.
- [ ] `git diff --check` clean on branch range.

## Cross-cutting Review Gates

- RED before production code; GREEN normal/ASan/TSan after.
- Doc mutations only via commands — including Lua-driven spawns/sets (pin: Ctrl+Z reverts a Lua spawn).
- Lua console inherits Stage 3 sandbox; no new host surface beyond ecs batch + config + print capture; no io/os.execute/debug/coroutine.
- Profiler panel never mutates profiler state.
- platform_list_dir is the ONLY platform-layer change; POSIX + Win32 branches; bounded; symlink policy documented.
- No GPU behavior claims; smoke run honestly framed.
- A task completes only after focused code review, doc update, and `git diff --check` on its range.
