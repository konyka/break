# Lua Runtime (BreakLuaRuntime) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver the Stage 3 `BreakLuaRuntime` opaque C11 facade — owned Lua VM, versioned module load/reload with old-version retention, bounded C API bindings, and frame lifecycle — as a formal optional library that consumes Stage 2 Runtime Core contracts, without touching editor, online update, or LuaJIT.

**Architecture:** A new formal optional static library `break_lua` (same target pattern as `runtime_core`: top-level in `engine/CMakeLists.txt`, independent of `ENGINE_BUILD_TESTS`, never linked into `engine`/`engine_demo`/`dxx_break` by this plan). It wraps the vendored Lua 5.4 VM (`engine/external/lua/onelua.c`, existing `lua` static target) behind opaque handles. The pre-existing `engine/src/script/script_lua.c` (per-file `LuaScript`) stays untouched as the compatibility layer inside `engine`; the new facade is the stable ABI surface. Module state lives in a Lua-side state table separate from the module chunk; reload stages the new chunk, runs the old module's unload hook, and keeps the old version on any failure. Scripts reach the host only through bounded batch APIs (ECS command buffer, config table); never through raw World*/PhysicsWorld*/RHI/network pointers.

**Tech Stack:** C11; vendored Lua 5.4 (`lua` target); Stage 2 `runtime_core` contracts for error taxonomy reference only (no link dependency required for the baseline); CTest; ASan/UBSan/TSan; GCC/Clang.

## Global Constraints

- C11 only; Lua is the only runtime scripting language; no LuaJIT in this plan (documented as deferred Stage 3.5).
- New library: `break_lua` — formal optional static target, top-level in `engine/CMakeLists.txt`, produced when `ENGINE_BUILD_TESTS=OFF`, NOT linked into `engine`, `engine_demo`, or `dxx_break`.
- The compatibility layer `engine/src/script/script_lua.c`/`script_lua.h` and its test `engine/tests/test_script_lua.c` remain byte-for-byte behavior-compatible; the new facade does not replace them in this plan.
- All public handles opaque C11 types with explicit borrowed/owned lifetime rules; NO raw `World*`/`Archetype*`/`Chunk*`/`lua_State*`/OS thread handle/RHI handle/network reactor pointer crosses the public API.
- Error reporting uses the Stage 2 taxonomy shape: a `BreakLuaError` enum mirroring `OK/INVALID/CLOSED/OVERLOAD/OOM/TIMEOUT/STALE/REJECTED/FAILED` semantics (prefix `BREAK_LUA_`), defined in this plan's headers, no dependency on runtime_core headers required.
- Every bounded resource has count AND byte overflow checks and a bounded failure result: module source size cap `BREAK_LUA_MAX_MODULE_BYTES = (1u << 20)` (matches `LUA_SCRIPT_MAX_FILE_BYTES`), module count cap, args/returns cap `BREAK_LUA_MAX_VALUES = 64`, string/value copy budget.
- Hot reload rules (from the accepted design): module state table independent of the Lua chunk; old module's unload hook runs before the new module commits; script objects use stable handles (never C pointers as permanent identity); failed reload keeps the old version; modules carry version + size + FNV-1a-64 hash metadata (signature verification is a Stage 5 security task — record the metadata field, do not implement crypto); scripts MUST NOT overwrite core code, network protocol, or security policy at runtime.
- Scripts cannot reach raw RHI/physics/network handles: the only host surface is the registered batch/config API table.
- One runtime = one lua_State = one owner thread (documented owner-thread convention, same style as runtime_coordinator; no mutex to make multi-owner legal).
- Normal, ASan/UBSan, and TSan focused tests required per task; test-only hooks follow the `BREAK_LUA_TESTING` pattern compiled out of production (nm-verifiable), mirroring `BREAK_RUNTIME_TESTING`.
- Docs must distinguish "formal optional library" from "integrated into engine/demo runtime"; no integration claims.

---

## File and Target Map

- Create: `engine/src/script/break_lua.h` — public facade: types, config, lifecycle, module load/reload, call, frame hooks.
- Create: `engine/src/script/break_lua_runtime.c` — runtime/VM ownership, registry, owner-thread checks.
- Create: `engine/src/script/break_lua_module.c` — module load/stage/commit/rollback, version metadata, unload hooks.
- Create: `engine/src/script/break_lua_value.c` — BreakLuaValue marshalling (nil/bool/number/string), bounded copies.
- Create: `engine/src/script/break_lua_binding.c` — host binding registration surface (ECS batch command buffer + config), sandboxing of the Lua global environment for modules.
- Create: `engine/tests/test_break_lua_runtime.c` — lifecycle/VM/owner/error tests.
- Create: `engine/tests/test_break_lua_module.c` — load/reload/retention/stale/version tests.
- Create: `engine/tests/test_break_lua_binding.c` — binding batch/config/sandbox tests.
- Modify: `engine/CMakeLists.txt` — add `break_lua` static lib (links `lua`, PUBLIC) + three test executables + a target-contract ctest following `test_runtime_core_target_contract.cmake` precedent.
- Modify: `docs/design/runtime_hot_reload.md` (§2.3/§3.3 delivered-facts), `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 3 status), and create `docs/design/lua_runtime.md` (facade contract summary) — precise delivered-vs-design-only wording.

---

### Task 1: Runtime facade skeleton — VM ownership and lifecycle

**Files:**
- Create: `engine/src/script/break_lua.h`, `engine/src/script/break_lua_runtime.c`
- Create: `engine/tests/test_break_lua_runtime.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces (verbatim surface for this task):**
```c
typedef enum BreakLuaError {
    BREAK_LUA_OK = 0,
    BREAK_LUA_INVALID,
    BREAK_LUA_CLOSED,
    BREAK_LUA_OVERLOAD,
    BREAK_LUA_OOM,
    BREAK_LUA_TIMEOUT,
    BREAK_LUA_STALE,
    BREAK_LUA_REJECTED,
    BREAK_LUA_FAILED
} BreakLuaError;

typedef struct BreakLuaRuntime BreakLuaRuntime;

typedef struct BreakLuaRuntimeConfig {
    u32 max_modules;          /* 0 => BREAK_LUA_DEFAULT_MAX_MODULES (64) */
    u32 max_values;           /* per-call args/returns cap; 0 => 64 */
    usize max_module_bytes;   /* 0 => BREAK_LUA_MAX_MODULE_BYTES (1 MiB) */
    u64 instruction_budget;   /* per begin/end-frame hook budget; 0 => disabled */
} BreakLuaRuntimeConfig;

BreakLuaRuntime *break_lua_runtime_create(const BreakLuaRuntimeConfig *config);
void break_lua_runtime_destroy(BreakLuaRuntime *runtime);
```

- [ ] RED: tests for create/destroy, config clamping/validation (oversized caps → INVALID or clamped, documented), owner-thread enforcement probe, double-destroy rejection (test-build fail-stop), OOM injection on create paths.
- [ ] GREEN: `break_lua` target (links `lua` PUBLIC, C_STANDARD 11, top-level, outside tests block); runtime owns one `lua_State` (base libs opened; no `io`/`os.execute` exposure to modules — sandbox details land in Task 4, but the state is created here); owner thread id captured at create.
- [ ] CMake contract ctest: `break_lua` exists with `ENGINE_BUILD_TESTS=OFF`, not referenced by `engine`/`engine_demo`/`dxx_break`.
- [ ] Three trees: build-sdd-l1 (normal), build-sdd-l1-asan (ENGINE_USE_ASAN+UBSAN), build-sdd-l1-tsan (ENGINE_USE_TSAN); focused ctest green in each.
- [ ] Docs: Implementation_Status.md entry (formal optional, not integrated).

### Task 2: Module loading and versioned reload with old-version retention

**Files:**
- Create: `engine/src/script/break_lua_module.c`
- Create: `engine/tests/test_break_lua_module.c`
- Modify: `engine/src/script/break_lua.h`, `engine/CMakeLists.txt`

**Interfaces (verbatim surface added to break_lua.h):**
```c
typedef struct BreakLuaReloadReport {
    u32 old_version;
    u32 new_version;
    u64 old_hash;        /* FNV-1a-64 of source bytes */
    u64 new_hash;
    bool committed;      /* false => old version still live */
    u32 error_line;      /* 0 when not applicable */
    char error[128];     /* truncated loader/runtime error */
} BreakLuaReloadReport;

BreakLuaError break_lua_runtime_load_module(
    BreakLuaRuntime *runtime, const char *module_name,
    const void *source, usize source_size);

BreakLuaError break_lua_runtime_reload_module(
    BreakLuaRuntime *runtime, const char *module_name,
    const void *source, usize source_size,
    BreakLuaReloadReport *report);
```

- [ ] RED: load module (chunk runs in module environment, `module.state` table persists separately from the chunk); duplicate load without reload → REJECTED; source size > cap → OVERLOAD/INVALID (bounded, documented); reload success bumps version and runs old unload hook before commit; reload with syntax error keeps old version serving calls (committed == false); reload with runtime error during staging keeps old version; module count cap → OVERLOAD; stale/unknown module name → INVALID/STALE per contract.
- [ ] GREEN: staging approach — new chunk compiled+executed in a fresh per-module environment; on success the old module's `on_unload` (optional) runs, then the new environment + state table atomically replace the old; on any failure the old registration is untouched. Version = monotonically increasing u32 per module; hash = FNV-1a-64 over source bytes. Report fields fully populated on both paths.
- [ ] Overflow checks: count and byte arithmetic checked; all failure paths bounded and leak-free (ASan lane proves).
- [ ] Three trees green; docs update (runtime_hot_reload.md §2.3 delivered note).

### Task 3: Value marshalling, module calls, and frame lifecycle

**Files:**
- Create: `engine/src/script/break_lua_value.c`
- Create: `engine/tests/test_break_lua_value.c` (or fold into test_break_lua_module.c if it stays cohesive)
- Modify: `engine/src/script/break_lua.h`, `engine/CMakeLists.txt`

**Interfaces (verbatim surface added to break_lua.h):**
```c
typedef enum BreakLuaValueType {
    BREAK_LUA_VALUE_NIL = 0,
    BREAK_LUA_VALUE_BOOL,
    BREAK_LUA_VALUE_NUMBER,   /* f64 */
    BREAK_LUA_VALUE_STRING    /* bounded copy, NUL-terminated */
} BreakLuaValueType;

typedef struct BreakLuaValue {
    BreakLuaValueType type;
    union { bool b; f64 n; struct { char data[128]; u32 len; } s; } as;
} BreakLuaValue;

BreakLuaError break_lua_runtime_call(
    BreakLuaRuntime *runtime, const char *module_name,
    const char *function_name, const BreakLuaValue *args, usize arg_count,
    BreakLuaValue *returns, usize return_capacity);

void break_lua_runtime_begin_frame(BreakLuaRuntime *runtime, double delta_seconds);
void break_lua_runtime_end_frame(BreakLuaRuntime *runtime);
```

- [ ] RED: call with mixed arg/return types round-trip; string truncation/over-cap → bounded error (OVERLOAD) not overflow; call unknown module/function → INVALID; arg_count > max_values → OVERLOAD; begin/end frame dispatch to modules' `on_update`-style hooks with dt; frame hook error policy (module error → bounded error event, other modules continue; exact policy documented); instruction budget enforcement (budget exceeded → hook aborts with FAILED, module marked, next frame policy documented).
- [ ] GREEN: marshalling with checked copies; per-call Lua stack discipline (balanced on all exits); frame hooks iterate a stable registry snapshot so a module reloading mid-frame cannot corrupt iteration.
- [ ] Three trees green (TSan: owner-thread convention documented; concurrency test only for owner-enforcement rejection probes).
- [ ] Docs: lua_runtime.md created with the full facade contract.

### Task 4: Host bindings — bounded ECS batch commands and config; module sandbox

**Files:**
- Create: `engine/src/script/break_lua_binding.c`
- Create: `engine/tests/test_break_lua_binding.c`
- Modify: `engine/src/script/break_lua.h`, `engine/CMakeLists.txt`

**Interfaces (verbatim surface added to break_lua.h):**
```c
typedef struct BreakLuaEcsBatch BreakLuaEcsBatch;   /* opaque; host-drained */

BreakLuaError break_lua_runtime_bind_ecs_batch(
    BreakLuaRuntime *runtime, BreakLuaEcsBatch *batch);   /* borrowed host object */

typedef struct BreakLuaConfigBinding {
    const char *key;          /* borrowed */
    double min_value;
    double max_value;
    double initial_value;
} BreakLuaConfigBinding;

BreakLuaError break_lua_runtime_bind_config(
    BreakLuaRuntime *runtime, const BreakLuaConfigBinding *entries,
    usize entry_count);
```

Script surface (Lua side): `break.ecs.spawn()` / `break.ecs.set(component, field, value)` enqueue into the bounded batch (capacity from config; full → Lua-visible bounded failure, never blocks, never touches World directly); `break.config.get(key)` reads clamped host config. No `io`, no `os.execute`, no `ffi`-style raw access; module environments carry only whitelisted globals.

- [ ] RED: batch enqueue visible to host drain with FIFO order and bounded capacity (full → OVERLOAD surfaced to script as false/error); batch is host-drained (facade never applies to a World itself in this task — no World pointer exists here); config get with clamping; sandbox: module chunk attempting `os.execute`/`io.open` fails (functions absent); script cannot overwrite `break.*` core table (read-only metatable or equivalent); batch pointer never reachable from Lua.
- [ ] GREEN: binding registration with count/byte checks; batch command record format documented (kind u16 + payload); host drain API `break_lua_ecs_batch_drain(batch, out_records, capacity)` defined in header (implementation may live in binding.c; batch itself is host-owned).
- [ ] Three trees green.
- [ ] Docs: lua_runtime.md binding contract + security wording (scripts cannot reach raw RHI/physics/network handles — acceptance criterion).

### Task 5: Validation and documentation closeout

**Files:**
- Modify: `engine/CMakeLists.txt` (only if a real fix is needed)
- Modify: `docs/design/lua_runtime.md`, `docs/design/runtime_hot_reload.md`, `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md`
- Modify: `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md` (check only evidence-backed Stage 3 boxes)

- [ ] Clean normal tree: build `break_lua` + all three test executables + full default target set; focused ctest green.
- [ ] Clean ASan/UBSan and TSan trees: same builds; focused lanes green; no sanitizer reports.
- [ ] Verify `ENGINE_BUILD_TESTS=OFF` builds `break_lua`; verify production `libbreak_lua.a` has zero test-hook symbols (nm).
- [ ] Verify compatibility layer untouched: `test_script_lua` still passes; `git diff` over `engine/src/script/script_lua.*` is empty for the whole branch.
- [ ] Roadmap Stage 3 status update: mark delivered subprojects 1-4 with evidence; subproject 5 (LuaJIT) stays pending with its gating condition.
- [ ] `git diff --check` clean on branch code/docs (vendored reference docs excluded).

## Cross-cutting Review Gates

- Every task: RED evidence before production code; GREEN normal/ASan/TSan evidence after.
- No public API leaks `lua_State*` or any raw host handle; module identity is by name + version, never by pointer.
- Every capacity: count and byte overflow checks + bounded failure + a test preserving old state.
- Reload is atomic from the caller's view: old version serves until the new version commits; failure keeps old version (acceptance criterion).
- Scripts cannot reach raw RHI/physics/network handles; the `break.*` surface is the only host contact (acceptance criterion).
- Legacy `script_lua` behavior unchanged; `test_script_lua` green in every lane.
- A task is complete only after focused code review, documentation update, and `git diff --check` on its range.
