#pragma once

#include <core/types.h>

/* ==========================================================================
 *  break_lua — Stage 3 formal optional Lua runtime facade (skeleton).
 *
 *  A BreakLuaRuntime owns exactly one vendored Lua 5.4 lua_State behind an
 *  opaque handle. This header is the stable ABI surface; no lua_State, raw
 *  host handle (World, RHI, network, OS thread), or OS primitive ever
 *  crosses the public API.
 *
 *  OWNER THREAD (binding constraint): the thread that calls
 *  break_lua_runtime_create() becomes the owner. Every other function in this
 *  header must be called from that owner thread; the runtime deliberately
 *  contains no mutex, and arbitrary multi-owner use is a contract violation,
 *  not a supported mode (same convention as runtime_coordinator.h).
 *  break_lua_runtime_check_owner() is the documented probe; owner-only query
 *  APIs return BREAK_LUA_REJECTED from any other thread.
 *
 *  SANDBOX STATUS (delivered in Task 4): the owned state is created with the
 *  Lua standard libraries opened (luaL_openlibs) on the BASE global table,
 *  but module environments never see that table: every module chunk runs in
 *  a per-module environment whose metatable __index resolves to a fixed
 *  WHITELIST (see HOST BINDINGS AND SANDBOX below) — no io, no os.execute,
 *  no raw coroutine, no debug/package/load* — and the script-visible `break`
 *  table chain is read-only. Scripts reach the host exclusively through the
 *  bounded `break.ecs.*` / `break.config.*` surface; no raw host handle
 *  (World, RHI, physics, network, OS thread) is ever reachable from Lua.
 *
 *  Error taxonomy (mirrors the Stage 2 runtime_core shape):
 *    BREAK_LUA_OK        — success.
 *    BREAK_LUA_INVALID   — malformed call (NULL argument) or a config whose
 *                          caps exceed the documented hard ceilings.
 *    BREAK_LUA_CLOSED    — admission after the runtime has begun closing
 *                          (reserved; no close semantics exist yet — no API
 *                          maps to it).
 *    BREAK_LUA_OVERLOAD  — a bounded resource (module count, value count,
 *                          module bytes) would exceed its cap.
 *    BREAK_LUA_OOM       — allocation failure.
 *    BREAK_LUA_TIMEOUT   — a bounded wait/budget expired (reserved; no API
 *                          maps to it yet — the instruction budget reports
 *                          FAILED-class fault records, not TIMEOUT).
 *    BREAK_LUA_STALE     — a handle/version no longer names the live object
 *                          (Task 2 scope: reload of a never-loaded name;
 *                          Task 3 scope: call into a never-loaded name).
 *    BREAK_LUA_REJECTED  — a meaningful request rejected by policy, e.g. an
 *                          owner-only API called from a non-owner thread.
 *    BREAK_LUA_FAILED    — sticky failure / bounded operation failure.
 * ========================================================================== */

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

typedef struct BreakLuaRuntime BreakLuaRuntime; /* opaque, owned by the caller */

/* Trust-boundary caps. BREAK_LUA_MAX_MODULE_BYTES matches
 * LUA_SCRIPT_MAX_FILE_BYTES (script_lua.h): no module source larger than
 * 1 MiB is ever staged. BREAK_LUA_MAX_MODULES is the hard ceiling for the
 * module registry; BREAK_LUA_MAX_VALUES is the hard per-call args/returns
 * cap. */
#define BREAK_LUA_MAX_MODULE_BYTES (1u << 20)
#define BREAK_LUA_DEFAULT_MAX_MODULES 64u
#define BREAK_LUA_MAX_MODULES 1024u
#define BREAK_LUA_MAX_VALUES 64u

typedef struct BreakLuaRuntimeConfig {
    u32 max_modules;          /* 0 => BREAK_LUA_DEFAULT_MAX_MODULES (64) */
    u32 max_values;           /* per-call args/returns cap; 0 => 64 */
    usize max_module_bytes;   /* 0 => BREAK_LUA_MAX_MODULE_BYTES (1 MiB) */
    u64 instruction_budget;   /* per begin/end-frame hook budget; 0 => disabled */
} BreakLuaRuntimeConfig;

/* Creates a runtime owning one freshly opened lua_State (standard libraries
 * included; see SANDBOX STATUS above). `config` may be NULL (all defaults).
 *
 * Validation is fail-closed, never clamped: a config field above its hard
 * ceiling (max_modules > BREAK_LUA_MAX_MODULES, max_values >
 * BREAK_LUA_MAX_VALUES, max_module_bytes > BREAK_LUA_MAX_MODULE_BYTES) makes
 * create return NULL (the INVALID class of failure). create also returns NULL
 * on allocation failure (the OOM class): the runtime struct, the Lua state,
 * and the standard-library open all fail closed (the open runs under
 * lua_pcall, so a Lua-side allocation error cannot panic), and a partial
 * initialization frees everything it already acquired. A NULL return never
 * yields a half-usable runtime.
 *
 * The calling thread is recorded as the owner thread. */
BreakLuaRuntime *break_lua_runtime_create(const BreakLuaRuntimeConfig *config);

/* Closes the owned lua_State and releases the runtime. NULL is a no-op.
 * Owner-thread-only. Destroying the same runtime twice (or a foreign pointer)
 * is a contract violation: test builds (BREAK_LUA_TESTING) fail-stop with a
 * diagnostic abort before freeing; production behavior is undefined, same
 * convention as the runtime_core owned-message registry. */
void break_lua_runtime_destroy(BreakLuaRuntime *runtime);

/* Copies the effective config (defaults substituted) into `out_config`.
 * Owner-only: BREAK_LUA_REJECTED from any non-owner thread. NULL runtime or
 * NULL out_config -> BREAK_LUA_INVALID. */
BreakLuaError break_lua_runtime_effective_config(
    const BreakLuaRuntime *runtime, BreakLuaRuntimeConfig *out_config);

/* Documented owner-thread probe: BREAK_LUA_OK on the owner thread,
 * BREAK_LUA_REJECTED from any other thread, BREAK_LUA_INVALID for NULL. */
BreakLuaError break_lua_runtime_check_owner(const BreakLuaRuntime *runtime);

/* Lifetime count of instruction-budget trips on this runtime (frame hooks,
 * module staging, on_unload — every armed execution). Hosts use the delta
 * across an eval/dispatch to distinguish a budget trip from a
 * dispatch-level fault. Owner-only query: returns 0 for NULL or from a
 * non-owner thread (bounded no-op; no error channel exists on a value
 * return). */
u64 break_lua_runtime_budget_trip_count(const BreakLuaRuntime *runtime);

/* Stable diagnostic name for each BreakLuaError ("OK", "INVALID", ...);
 * "UNKNOWN" for values outside the enum. */
const char *break_lua_error_name(BreakLuaError error);

/* ==========================================================================
 *  Modules (Task 2): versioned load/reload with old-version retention.
 *
 *  MODULE MODEL: a module is registered under a NUL-terminated name of at
 *  most BREAK_LUA_MAX_MODULE_NAME_BYTES - 1 chars (longer -> INVALID, a
 *  bounded check that never reads past that many bytes). Loading compiles
 *  and executes the source as a TEXT chunk (binary/bytecode chunks are
 *  rejected by the loader) in a fresh per-module environment whose globals
 *  resolve to the runtime's fixed whitelist sandbox (see HOST BINDINGS AND
 *  SANDBOX below; the base global table is never reachable from modules).
 *  The environment carries a `state` global naming the
 *  module's persistent state table; the chunk's own globals are private to
 *  the environment and NEVER survive a reload, while the state table
 *  persists by identity across reloads (contents preserved). A chunk that
 *  overwrites `state` with ANOTHER TABLE keeps that table: it becomes the
 *  persisted state from then on. Only nil'ing `state` (or replacing it
 *  with a non-table value) forfeits persistence: the next reload then
 *  stages against a fresh empty state table.
 *
 *  IDENTITY: a module version is name + monotonically increasing u32
 *  (1 at first load, +1 per committed reload); hashes are FNV-1a-64 over
 *  the exact source bytes. No lua_State* or module pointer ever crosses
 *  this API.
 *
 *  ATOMICITY: reload stages the new chunk (compile + execute in a fresh
 *  environment wired to the preserved state table); only when staging fully
 *  succeeds does the old environment's optional `on_unload` function run
 *  (pcall-protected), and only when that succeeds does the commit retire
 *  the old environment and install the new one. Any failure — syntax error,
 *  staging runtime error, on_unload error, OOM — leaves the old
 *  version fully live and serving (committed == false). A module whose
 *  on_unload always errors vetoes every reload: it wedges at its current
 *  version by its own policy choice. on_unload must be a raw field of the
 *  module environment (i.e. defined by the chunk itself); a missing or
 *  non-function field is simply skipped.
 *
 *  STATE ROLLBACK: the state table is the module's own data and is never
 *  rolled back. A staged chunk that writes to `state` and THEN fails leaves
 *  its partial writes visible to the old version; only the
 *  environment/version commit is atomic.
 *
 *  ERROR SURFACES: malformed calls (NULL runtime/name/source, empty or
 *  overlong name, zero size) -> BREAK_LUA_INVALID. Non-owner thread ->
 *  BREAK_LUA_REJECTED. source_size over the runtime's max_module_bytes ->
 *  BREAK_LUA_OVERLOAD (the cap is inclusive: exactly-at-cap is admitted).
 *  Registry full on first load -> BREAK_LUA_OVERLOAD. Duplicate load of a
 *  live name without reload -> BREAK_LUA_REJECTED (checked before the count
 *  cap, so a full registry still answers duplicates correctly). Reload of a
 *  name that was never loaded -> BREAK_LUA_STALE (the name names no live
 *  object; reload is never an implicit load). Loader/staging/on_unload
 *  failure -> BREAK_LUA_FAILED; Lua-side allocation failure anywhere in the
 *  operation -> BREAK_LUA_OOM (every Lua entry point runs under lua_pcall;
 *  a Lua error can never panic the process). Version-space exhaustion
 *  (live version == UINT32_MAX) -> BREAK_LUA_REJECTED, a checked bound.
 * ========================================================================== */

/* Bounded storage for a module name including its NUL terminator. */
#define BREAK_LUA_MAX_MODULE_NAME_BYTES 128u

/* Reload outcome. Fully written on EVERY return path when non-NULL:
 * malformed-call (INVALID), non-owner (REJECTED) and unknown-name (STALE)
 * exits write a zeroed report; exits after the live module was identified
 * fill old_version/old_hash from the live registry entry.
 *   committed   — true only when the new version replaced the old.
 *   old_version — live version before the call (0 when no module named).
 *   new_version — old_version + 1 when committed; equal to old_version
 *                 otherwise (a failed reload consumes no version).
 *   old_hash    — FNV-1a-64 of the live source bytes (0 when no module).
 *   new_hash    — FNV-1a-64 of the candidate source once it passed the
 *                 admission checks; 0 when rejected before hashing.
 *   error_line  — source line parsed from the Lua loader/runtime message,
 *                 0 when not applicable (non-Lua failures, or messages
 *                 without a position prefix).
 *   error       — NUL-terminated Lua loader/runtime error text, truncated
 *                 to fit; empty string when not applicable. */
typedef struct BreakLuaReloadReport {
    u32 old_version;
    u32 new_version;
    u64 old_hash;        /* FNV-1a-64 of source bytes */
    u64 new_hash;
    bool committed;      /* false => old version still live */
    u32 error_line;      /* 0 when not applicable */
    char error[128];     /* truncated loader/runtime error */
} BreakLuaReloadReport;

/* Compiles and executes `source` (exactly `source_size` bytes, need not be
 * NUL-terminated) as module `module_name`. Owner-thread-only. See MODULES
 * above for the full error contract. On BREAK_LUA_OK the module is live at
 * version 1; on any other return nothing is registered. */
BreakLuaError break_lua_runtime_load_module(
    BreakLuaRuntime *runtime, const char *module_name,
    const void *source, usize source_size);

/* Stages a replacement chunk for the live module `module_name` and commits
 * it atomically per the MODULES contract above. `report` may be NULL (no
 * details wanted); when non-NULL it is fully written on every return path
 * (see BreakLuaReloadReport). */
BreakLuaError break_lua_runtime_reload_module(
    BreakLuaRuntime *runtime, const char *module_name,
    const void *source, usize source_size,
    BreakLuaReloadReport *report);

/* ==========================================================================
 *  Values and calls (Task 3): bounded marshalling between C and a module
 *  environment's chunk-defined functions.
 *
 *  VALUE MODEL: BreakLuaValue is a bounded tagged union: nil, bool, f64
 *  number, or a string of at most BREAK_LUA_VALUE_STRING_CAPACITY - 1 bytes
 *  plus its NUL terminator (len counts the payload bytes, excluding the
 *  terminator). Produced strings are always NUL-terminated at data[len].
 *  Lua values outside this model (tables, functions, userdata, threads)
 *  are unrepresentable and fail the call bounded (see below) rather than
 *  being silently coerced.
 *
 *  CALL CONTRACT (break_lua_runtime_call): the target function must be a
 *  RAW field of the module's live environment (i.e. defined by the chunk
 *  itself); names that only resolve through the environment metatable's
 *  whitelist fallback (e.g. stdlib globals like tostring) do NOT resolve
 *  and answer INVALID. Check order, all bounded:
 *    - NULL runtime, NULL/empty/overlong module or function name (same
 *      128-byte cap as module names), NULL args with arg_count > 0, NULL
 *      returns with return_capacity > 0 -> BREAK_LUA_INVALID. Malformed
 *      calls never touch the Lua state.
 *    - Non-owner thread -> BREAK_LUA_REJECTED (checked first, before any
 *      shape check, so an attacker thread learns nothing about names).
 *    - arg_count or return_capacity over the runtime's max_values ->
 *      BREAK_LUA_OVERLOAD (exactly-at-cap is admitted).
 *    - A module name that names no live module -> BREAK_LUA_STALE (same
 *      contract as reload; never an implicit load).
 *    - Field missing or not a function -> BREAK_LUA_INVALID.
 *    - A STRING argument whose len >= BREAK_LUA_VALUE_STRING_CAPACITY (the
 *      bounded buffer cannot hold that many bytes) -> BREAK_LUA_OVERLOAD.
 *    - Lua error raised by the function -> BREAK_LUA_FAILED; Lua-side
 *      allocation failure anywhere -> BREAK_LUA_OOM (the whole call runs
 *      under the runtime's pcall-protected op dispatch; a Lua error can
 *      never panic the process).
 *    - A returned string of len >= BREAK_LUA_VALUE_STRING_CAPACITY ->
 *      BREAK_LUA_OVERLOAD (bounded; no overflow ever occurs).
 *    - An unrepresentable return type -> BREAK_LUA_FAILED.
 *  RETURN BUFFER: once admission has passed (module found, caps OK), all
 *  return_capacity slots are NIL-initialised before marshalling, so any
 *  post-admission failure leaves them NIL. The function is invoked with
 *  exactly return_capacity wanted results: Lua nil-pads when it returns
 *  fewer and discards extras when it returns more, so the buffer is always
 *  fully written and the Lua stack stays balanced on every exit. Pre-
 *  admission failures (INVALID/REJECTED/OVERLOAD-caps/STALE) do not write
 *  the returns buffer.
 *
 *  FRAME LIFECYCLE (begin_frame/end_frame): each call dispatches to the
 *  modules' frame hooks. Hook names (pinned by tests): on_frame_begin(dt)
 *  receives the delta_seconds verbatim as a Lua number; on_frame_end()
 *  takes no arguments. A hook must be a raw function field of the module
 *  environment; a module without the hook is simply skipped (not an error).
 *  Hook results are discarded. begin_frame and end_frame are independent
 *  dispatches — pairing them is the host's responsibility; either may be
 *  called alone. begin_frame increments a u64 frame sequence used for
 *  diagnostics.
 *
 *  SNAPSHOT: every dispatch first takes a stable snapshot of the registry:
 *  each occupied module's live environment is pinned by a Lua stack
 *  reference (ref-based, never a registry-slot pointer) together with its
 *  name and its hooks-disabled flag. The dispatch then serves exactly that
 *  snapshot: a module reloaded mid-dispatch keeps serving its pinned (old)
 *  environment for the rest of the dispatch — the pin keeps the retired
 *  table alive — and the new environment serves from the next dispatch; a
 *  module disabled at capture stays skipped for the whole dispatch even if
 *  reloaded mid-dispatch. Reload can only re-enter mid-dispatch through
 *  Lua-visible bindings; the production `break.*` surface (Task 4)
 *  deliberately exposes no reload binding, so the path is exercised in
 *  tests via a test-only binding. The host calling reload between
 *  begin_frame and end_frame sees each dispatch snapshot independently.
 *
 *  HOOK ERROR POLICY: every hook invocation runs under its own lua_pcall.
 *  A failing hook produces a bounded error record in the runtime (module
 *  name, hook name, message truncated to 127 bytes + NUL, frame sequence,
 *  lifetime counter; observable in this task through the BREAK_LUA_TESTING
 *  probes) and the dispatch CONTINUES with the remaining modules. An
 *  ordinary hook error does not disable the module: it serves again next
 *  frame.
 *
 *  INSTRUCTION BUDGET (config.instruction_budget, 0 = disabled): when set,
 *  every hook invocation runs under a per-invocation Lua count hook
 *  (lua_sethook LUA_MASKCOUNT); budgets above 2^31-1 are clamped to
 *  2^31-1 instructions. The accounting is per hook invocation, NOT
 *  cumulative across modules or frames. The SAME per-invocation arming
 *  covers every other module-code execution the facade performs (Phase 3
 *  Task 2 review fix — before it, these paths ran unbudgeted and a
 *  forever-looping chunk could hang the host thread):
 *    - module STAGING chunk execution (the load/reload chunk run): a trip
 *      aborts staging with a bounded BREAK_LUA_FAILED ("break_lua:
 *      instruction budget exceeded"); a failed load registers nothing, a
 *      failed reload retains the old version per the MODULES contract, and
 *      no hooks-disabled mark is set (the runaway policy below governs
 *      frame hooks only);
 *    - the commit-path on_unload hook: a trip is an on_unload failure —
 *      the reload is vetoed (bounded), the old version stays live;
 *    - module functions invoked through break_lua_runtime_call /
 *      break_lua_runtime_call_ref remain UNARMED (documented — hosts
 *      needing a budget there dispatch through frame hooks instead).
 *  TRIP VALUE AND CATCHABILITY (fix round 4, NEW-C4): the trip raises a
 *  host-owned SENTINEL value (a lightuserdata naming a runtime field),
 *  never a string. Scripts cannot construct, obtain, or compare it — no
 *  lightuserdata-producing API exists in the sandbox — and the sandboxed
 *  pcall/xpcall (see HOST BINDINGS AND SANDBOX) RE-RAISE it uninspected
 *  instead of returning it: SCRIPTS CANNOT CATCH THE BUDGET-TRIP ERROR;
 *  ALL OTHER ERRORS REMAIN CATCHABLE (ordinary pcall/xpcall semantics,
 *  (false, err) results, xpcall handler invoked post-unwind). One trip
 *  therefore always propagates through any depth of script pcall nesting
 *  to the host-side catcher (per-hook pcall / staging pcall / commit
 *  pcall) and terminates the protected execution. Residual truth: the
 *  count hook resets its countdown before firing (Lua 5.4
 *  resethookcount), so a single pcall round may burn up to the budget
 *  before the trip fires — but because the trip is uncatchable, exactly
 *  one trip terminates the eval/dispatch and the bound holds. The
 *  sentinel carries NO position prefix (raised bare via lua_error); error
 *  capture maps it to the canonical text "break_lua: instruction budget
 *  exceeded" with error_line 0. break_lua_runtime_budget_trip_count()
 *  exposes the lifetime trip counter for hosts that must distinguish a
 *  trip from a dispatch-level fault.
 *  COROUTINE SCOPE (the Task 3 review
 *  limit, closed by the Task 4 sandbox): Lua 5.4 hooks are per-coroutine —
 *  a raw `coroutine` global would let a module escape the armed count
 *  (lstate.c: lua_newthread -> resethookcount gives a fresh thread a fresh
 *  countdown, and a load-time thread carries hook mask 0). Module
 *  environments therefore do NOT expose `coroutine` at all (see HOST
 *  BINDINGS AND SANDBOX below): module code can only ever run on the main
 *  coroutine, so every nested Lua execution inside a budgeted hook (pcall
 *  chains, the test-only reloader, the break.ecs/break.config closures,
 *  etc.) decrements the same armed countdown — and because the trip value
 *  is uncatchable from scripts (see TRIP VALUE above), the nested pcall
 *  chain cannot absorb it. Exceeding the budget aborts
 *  the hook with an error: the fault is recorded like any hook error (with a
 *  budget flag) and the module is MARKED — its frame hooks are skipped on
 *  subsequent dispatches until the next committed reload clears the mark
 *  (a fail-closed, deterministic runaway-module policy). Other modules are
 *  unaffected.
 *
 *  OWNER THREAD: break_lua_runtime_call returns BREAK_LUA_REJECTED from a
 *  non-owner thread. begin_frame/end_frame return void, so a non-owner call
 *  is a contract violation handled like double-destroy: test builds
 *  (BREAK_LUA_TESTING) fail-stop with a diagnostic abort; production builds
 *  ignore the call (no-op). NULL runtime is a no-op for begin/end_frame.
 * ========================================================================== */

/* Bounded payload capacity of a BreakLuaValue string INCLUDING its NUL
 * terminator: the largest representable payload is 127 bytes. */
#define BREAK_LUA_VALUE_STRING_CAPACITY 128u

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

/* Calls the chunk-defined function `function_name` of the live module
 * `module_name` with `args`[0..arg_count) and writes up to
 * return_capacity marshalled results into `returns`. Owner-thread-only.
 * See VALUES AND CALLS above for the full bounded error contract. */
BreakLuaError break_lua_runtime_call(
    BreakLuaRuntime *runtime, const char *module_name,
    const char *function_name, const BreakLuaValue *args, usize arg_count,
    BreakLuaValue *returns, usize return_capacity);

/* Dispatches on_frame_begin(delta_seconds) to every module in a stable
 * registry snapshot, then returns. Owner-thread-only; see FRAME LIFECYCLE
 * above for the snapshot, error, and budget contracts. */
void break_lua_runtime_begin_frame(BreakLuaRuntime *runtime, double delta_seconds);

/* Dispatches on_frame_end() exactly like begin_frame dispatches
 * on_frame_begin. */
void break_lua_runtime_end_frame(BreakLuaRuntime *runtime);

/* ==========================================================================
 *  Function references (Stage 4 Phase 3 Task 2 review addition):
 *  host-pinned module functions.
 *
 *  break_lua_runtime_ref_function captures a chunk-defined RAW env function
 *  field (the same lookup rule as break_lua_runtime_call: whitelist-fallback
 *  names do not resolve) into a host handle: the function VALUE is pinned in
 *  the Lua registry, so break_lua_runtime_call_ref later invokes THAT
 *  function without consulting the module environment again. A chunk that
 *  overwrote the env field between capture and call cannot substitute
 *  another function — the env is never re-read — and cannot turn the
 *  outcome read into a hang, because the pinned function is the
 *  chunk-defined one as committed (the capture window is the host's
 *  responsibility: capture after a reload commits and before any dispatch
 *  runs the chunk).
 *
 *  HANDLES: a handle is a u32 slot index < BREAK_LUA_MAX_FN_REFS per
 *  runtime, released with break_lua_runtime_unref_function. Slots are
 *  reused after release with NO generation counter — a handle stale from
 *  before an unref may alias a LATER pin of the same slot; the documented
 *  console pattern (capture after commit, release after the read, never
 *  hold a handle across a release) avoids aliasing. A pinned
 *  function survives the module's reload (its upvalues are the RETIRED
 *  chunk's locals — a caller that needs the new version's functions must
 *  re-capture; this is the documented pattern) and is released wholesale at
 *  runtime destroy (lua_close tears the registry down); using a handle
 *  after its runtime's destroy is a contract violation.
 *
 *  ERROR SURFACES (owner thread checked FIRST on every API, before any
 *  shape check):
 *    - ref_function: NULL runtime/out_ref, NULL/empty/overlong module or
 *      function name (128-byte cap as module names) -> INVALID; non-owner
 *      -> REJECTED; unknown module -> STALE; field missing or not a
 *      function -> INVALID; no free handle slot -> OVERLOAD; Lua-side
 *      allocation failure (the registry pin) -> OOM. *out_ref is written
 *      only on BREAK_LUA_OK.
 *    - call_ref: NULL runtime -> INVALID; non-owner -> REJECTED; handle >=
 *      BREAK_LUA_MAX_FN_REFS or naming a free slot -> INVALID; arg/return
 *      caps and marshalling exactly as break_lua_runtime_call (OVERLOAD for
 *      over-cap counts and over-long strings, FAILED for Lua errors and
 *      unrepresentable returns, OOM for Lua-side allocation failure; the
 *      returns buffer is NIL-prefilled once admission passes).
 *      call_ref is — like break_lua_runtime_call — NOT armed with the
 *      instruction budget (the budget covers frame-hook dispatches and
 *      module staging/commit); pin and call only host-trusted functions.
 *    - unref_function: NULL runtime -> INVALID; non-owner -> REJECTED;
 *      handle >= cap or naming a free slot (including a double unref) ->
 *      INVALID, bounded, no fail-stop.
 * ========================================================================== */

/* Hard ceiling for simultaneously pinned function references per runtime. */
#define BREAK_LUA_MAX_FN_REFS 16u

BreakLuaError break_lua_runtime_ref_function(
    BreakLuaRuntime *runtime, const char *module_name,
    const char *function_name, u32 *out_ref);

BreakLuaError break_lua_runtime_call_ref(
    BreakLuaRuntime *runtime, u32 ref,
    const BreakLuaValue *args, usize arg_count,
    BreakLuaValue *returns, usize return_capacity);

BreakLuaError break_lua_runtime_unref_function(BreakLuaRuntime *runtime,
                                               u32 ref);

/* ==========================================================================
 *  Host bindings and module sandbox (Task 4): bounded ECS batch commands,
 *  clamped config reads, and the whitelisted module environment.
 *
 *  SECURITY BOUNDARY (acceptance criterion): scripts cannot reach raw
 *  RHI/physics/network handles — no World pointer exists anywhere in
 *  break_lua, and no host pointer of any kind is ever pushed into the Lua
 *  state. The ONLY host contact surface is the script-visible `break` table
 *  chain described below; the bound batch pointer lives in C registry-side
 *  storage (the runtime struct) and is never reachable from Lua (no
 *  lightuserdata, no userdata — the `break` chain enumerates to nothing and
 *  contains only proxy tables and C closures).
 *
 *  MODULE SANDBOX: every module chunk executes in a fresh per-module
 *  environment whose metatable __index resolves to a fixed per-runtime
 *  WHITELIST table (built once at create, held in the Lua registry — itself
 *  never script-reachable). Whitelisted globals:
 *    - base functions: assert, error, ipairs, pairs, select,
 *      tonumber, tostring, type, print; plus the _VERSION string;
 *    - pcall/xpcall as BUDGET-TRANSPARENT wrappers (fix round 4, NEW-C4):
 *      ordinary errors behave exactly like the base functions ((false,
 *      err) results; the xpcall handler is invoked by the wrapper after
 *      the call returns — post-unwind, which is safe here because the
 *      debug library is absent), but the instruction-budget trip value
 *      (see INSTRUCTION BUDGET) is RE-RAISED uninspected instead of being
 *      returned: scripts cannot catch a trip at any nesting depth, and
 *      never observe the sentinel value at all;
 *    - libraries (exposed through read-through proxies, see below):
 *      string, table, math, utf8 (full tables);
 *    - os SUBSET: exactly os.clock / os.time / os.date (a rebuilt table;
 *      os.execute, os.exit, os.remove, os.rename, os.getenv, os.setlocale,
 *      os.tmpname are absent);
 *    - the `break` table (below) — registered under the literal name
 *      "break" AND under the alias `brk` naming the SAME proxy: `break` is
 *      a reserved Lua keyword, so the design brief's literal
 *      `break.ecs.spawn()` is not spellable Lua syntax; scripts write
 *      `brk.ecs.spawn()` (or `_G["break"].ecs.spawn()`). Both names resolve
 *      to one identical read-only table;
 *    - env._G names the module's own environment (standard sandbox idiom).
 *  ABSENT by construction (the whitelist never copies them): io, debug,
 *  package, require, coroutine, load, loadstring, loadfile, dofile,
 *  collectgarbage, warn, unpack, next, rawget, rawset, rawequal, rawlen,
 *  setmetatable, getmetatable. load/dofile/loadfile/loadstring are DROPPED
 *  entirely (not restricted): modules are host-fed source only, so no
 *  script-side chunk compilation path exists to police. Raw-access and
 *  metatable-mutating base functions are deliberately excluded: they are
 *  the only Lua-side paths that could shadow a read-through proxy's fields,
 *  so without them the proxies below are unforgeable from scripts.
 *  `coroutine` is dropped because Lua 5.4 count hooks are per-coroutine and
 *  a resumed thread would escape the Task 3 instruction budget (lstate.c:
 *  lua_newthread -> resethookcount); with no `coroutine` global, all module
 *  execution stays on the main coroutine and inside the armed budget.
 *
 *  READ-ONLY TABLES: every script-visible binding/stdlib table (the `break`
 *  chain, string/table/math/utf8, the os subset) is a per-runtime
 *  read-through PROXY: an empty table whose metatable __index names the
 *  registry-held implementation table and whose __newindex raises
 *  ("attempted to mutate a read-only table"), with a locked metatable.
 *  Assignment (`break.ecs.spawn = f`) raises a bounded Lua error; with
 *  rawset/setmetatable absent from the whitelist there is no script path
 *  around the guard, and a module cannot poison a sibling module's stdlib.
 *  pairs() over a proxy yields nothing (it is raw-empty).
 *
 *  ECS BATCH: BreakLuaEcsBatch is an opaque HOST-OWNED bounded FIFO command
 *  buffer, created and destroyed by the host (break_lua_ecs_batch_create /
 *  break_lua_ecs_batch_destroy) and BORROWED by a runtime through
 *  break_lua_runtime_bind_ecs_batch. Scripts enqueue command records via
 *  break.ecs.spawn() / break.ecs.set(component, field, value); the host
 *  drains them with break_lua_ecs_batch_drain. The facade NEVER applies
 *  records anywhere: no World pointer exists in break_lua, application is
 *  entirely the host's business. Enqueue never blocks: a full batch makes
 *  the script call return (false, "break.ecs: batch full") — a Lua-visible
 *  bounded failure, not an error, not a wait.
 *    - Script argument validation runs BEFORE the batch is consulted and is
 *      the same bounded (false, message) failure: component/field must be
 *      strings of 1..BREAK_LUA_ECS_NAME_CAPACITY-1 bytes; the value must be
 *      a number, a boolean, or a string of at most
 *      BREAK_LUA_ECS_VALUE_STRING_CAPACITY-1 bytes; anything else is
 *      rejected and nothing is enqueued.
 *    - break.ecs.spawn() enqueues a BREAK_LUA_ECS_RECORD_SPAWN record
 *      (payload zeroed, value_type BREAK_LUA_ECS_VALUE_NONE) and returns
 *      true; break.ecs.set(...) enqueues BREAK_LUA_ECS_RECORD_SET.
 *    - With no batch bound, both return (false, "break.ecs: no batch
 *      bound"); the argument shapes are still validated first.
 *
 *  RECORD FORMAT (the drain wire format): BreakLuaEcsRecord is fixed-size
 *  POD — a u16 kind (BREAK_LUA_ECS_RECORD_*) plus a bounded payload: u16
 *  value_type (BREAK_LUA_ECS_VALUE_*; NONE for SPAWN), NUL-terminated
 *  component/field names bounded to BREAK_LUA_ECS_NAME_CAPACITY bytes
 *  including the terminator (zeroed for SPAWN), and a value union (f64 /
 *  bool / bounded NUL-terminated string of at most
 *  BREAK_LUA_ECS_VALUE_STRING_CAPACITY - 1 payload bytes). Drain copies
 *  records verbatim in FIFO order.
 *
 *  CONFIG: break_lua_runtime_bind_config registers a batch of
 *  {key, min, max, initial} entries; break.config.get(key) returns the
 *  stored value as a Lua number. Values are clamped to [min, max] AT BIND
 *  TIME (initial out of range -> the clamped bound is stored), so script
 *  reads always observe an in-range value. Unknown or malformed keys return
 *  (nil, message); no script-visible failure raises. Dynamic host-side
 *  updates are out of scope for this task: bound values are fixed until
 *  destroy.
 *
 *  ERROR SURFACES (all bounded; owner thread is checked FIRST, before any
 *  shape check, on every API):
 *    - break_lua_ecs_batch_create: capacity 0 -> default
 *      BREAK_LUA_ECS_BATCH_DEFAULT_CAPACITY; capacity above
 *      BREAK_LUA_ECS_BATCH_MAX_CAPACITY or a capacity*sizeof(record)
 *      multiply that would overflow size_t -> NULL (INVALID class,
 *      fail-closed); allocation failure -> NULL (OOM class).
 *    - break_lua_ecs_batch_destroy: NULL is a no-op; owner-thread-only —
 *      a non-owner destroy is a contract violation (test builds fail-stop
 *      abort; production ignores the call). Double destroy (or a foreign
 *      pointer) is a contract violation: test builds fail-stop with a
 *      diagnostic abort before freeing; production behavior is undefined.
 *    - break_lua_ecs_batch_drain: returns the number of records copied
 *      (FIFO); NULL batch, NULL out_records, or zero capacity -> 0; a
 *      non-owner call -> 0 (bounded no-op, the batch is untouched). The
 *      batch owner thread is the thread that created it.
 *    - break_lua_runtime_bind_ecs_batch: NULL runtime/batch -> INVALID;
 *      non-owner (of the runtime OR the batch) -> REJECTED; runtime already
 *      has a batch bound, or the batch is already bound to a runtime ->
 *      REJECTED (binding is one-to-one and one-shot for the runtime's
 *      lifetime; runtime destroy releases the binding, the batch stays
 *      host-owned). No Lua state is touched.
 *    - break_lua_runtime_bind_config: entry_count 0 -> OK no-op (entries may
 *      be NULL); NULL entries with entry_count > 0 -> INVALID; entry_count
 *      above BREAK_LUA_MAX_CONFIG_BINDINGS, or a cumulative count that
 *      would exceed it -> OVERLOAD; per entry: NULL/empty key or a key of
 *      BREAK_LUA_MAX_CONFIG_KEY_BYTES or more bytes -> INVALID; NaN
 *      min/max/initial or min > max -> INVALID; a duplicate key (within the
 *      call or against already-bound keys) -> REJECTED; store allocation
 *      failure -> OOM. Validation is all-or-nothing: a rejected call
 *      registers nothing. No Lua state is touched.
 * ========================================================================== */

typedef struct BreakLuaEcsBatch BreakLuaEcsBatch;   /* opaque; host-drained */

/* Batch capacity bounds (records). create(0) selects the default. */
#define BREAK_LUA_ECS_BATCH_DEFAULT_CAPACITY 256u
#define BREAK_LUA_ECS_BATCH_MAX_CAPACITY 4096u

/* Bounded record payload: component/field names and string values,
 * INCLUDING their NUL terminators (largest payload is capacity - 1). */
#define BREAK_LUA_ECS_NAME_CAPACITY 64u
#define BREAK_LUA_ECS_VALUE_STRING_CAPACITY 64u

/* Record kinds (BreakLuaEcsRecord.kind). */
typedef enum BreakLuaEcsRecordKind {
    BREAK_LUA_ECS_RECORD_SPAWN = 1,
    BREAK_LUA_ECS_RECORD_SET = 2
} BreakLuaEcsRecordKind;

/* Value tags (BreakLuaEcsRecord.value_type). */
typedef enum BreakLuaEcsValueKind {
    BREAK_LUA_ECS_VALUE_NONE = 0,
    BREAK_LUA_ECS_VALUE_NUMBER = 1,
    BREAK_LUA_ECS_VALUE_BOOL = 2,
    BREAK_LUA_ECS_VALUE_STRING = 3
} BreakLuaEcsValueKind;

/* One drained command record: kind u16 + bounded payload (see RECORD FORMAT
 * above). Fixed-size POD; drain copies records verbatim. */
typedef struct BreakLuaEcsRecord {
    u16 kind;        /* BreakLuaEcsRecordKind */
    u16 value_type;  /* BreakLuaEcsValueKind (NONE for SPAWN) */
    char component[BREAK_LUA_ECS_NAME_CAPACITY]; /* SET; zeroed for SPAWN */
    char field[BREAK_LUA_ECS_NAME_CAPACITY];     /* SET; zeroed for SPAWN */
    union {
        f64 n;                                   /* VALUE_NUMBER */
        bool b;                                  /* VALUE_BOOL */
        struct {
            char data[BREAK_LUA_ECS_VALUE_STRING_CAPACITY];
            u32 len; /* payload bytes, excluding the NUL terminator */
        } s;                                     /* VALUE_STRING */
    } value;
} BreakLuaEcsRecord;

/* Creates a host-owned batch of `capacity` records (0 -> default capacity).
 * The calling thread becomes the batch owner. See ERROR SURFACES above. */
BreakLuaEcsBatch *break_lua_ecs_batch_create(usize capacity);

/* Destroys a batch. NULL is a no-op. Owner-thread-only; see ERROR SURFACES.
 * Destroying a still-bound batch is legal: the binding is released first
 * (the runtime then answers scripts with "no batch bound"). */
void break_lua_ecs_batch_destroy(BreakLuaEcsBatch *batch);

/* Copies up to `capacity` oldest records (FIFO) into out_records and removes
 * them from the batch; returns the number copied. See ERROR SURFACES. */
usize break_lua_ecs_batch_drain(BreakLuaEcsBatch *batch,
                                BreakLuaEcsRecord *out_records,
                                usize capacity);

/* Borrows the host-owned batch into the runtime: break.ecs.spawn/set calls
 * from modules enqueue into it until runtime destroy (or batch destroy).
 * Owner-thread-only. See ERROR SURFACES above. */
BreakLuaError break_lua_runtime_bind_ecs_batch(
    BreakLuaRuntime *runtime, BreakLuaEcsBatch *batch);   /* borrowed host object */

/* Hard ceiling for the total number of bound config entries per runtime,
 * and the bounded key scan cap (a key of this many bytes or more is
 * INVALID). */
#define BREAK_LUA_MAX_CONFIG_BINDINGS 256u
#define BREAK_LUA_MAX_CONFIG_KEY_BYTES 128u

typedef struct BreakLuaConfigBinding {
    const char *key;          /* borrowed */
    double min_value;
    double max_value;
    double initial_value;
} BreakLuaConfigBinding;

/* Registers `entry_count` config entries (all-or-nothing validation; values
 * clamped to [min, max] at bind time). Owner-thread-only. See ERROR
 * SURFACES above. */
BreakLuaError break_lua_runtime_bind_config(
    BreakLuaRuntime *runtime, const BreakLuaConfigBinding *entries,
    usize entry_count);
