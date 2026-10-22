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
 *  SANDBOX STATUS (unchanged through Task 3): the owned state is created with the Lua
 *  standard libraries opened (luaL_openlibs), so `os`/`io` are present on the
 *  global environment, and module environments currently inherit them via
 *  metatable fallback. Per-module environments with a whitelisted global set
 *  (no io / no os.execute / no raw host access) are Task 4 scope; scripts
 *  have no host-surface bindings yet at all (also Task 4).
 *
 *  Error taxonomy (mirrors the Stage 2 runtime_core shape):
 *    BREAK_LUA_OK        — success.
 *    BREAK_LUA_INVALID   — malformed call (NULL argument) or a config whose
 *                          caps exceed the documented hard ceilings.
 *    BREAK_LUA_CLOSED    — admission after the runtime has begun closing
 *                          (reserved for later tasks; nothing closes in
 *                          Task 1).
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
 *  resolve to the runtime's base environment (a whitelisted sandbox is
 *  Task 4 scope). The environment carries a `state` global naming the
 *  module's persistent state table; the chunk's own globals are private to
 *  the environment and NEVER survive a reload, while the state table
 *  persists by identity across reloads (contents preserved). A chunk that
 *  overwrites or nils its own `state` global forfeits that persistence: the
 *  next reload then stages against a fresh empty state table.
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
 *  itself); names that would only resolve through the environment
 *  metatable's _G fallback (e.g. stdlib globals like tostring) do NOT
 *  resolve and answer INVALID. Check order, all bounded:
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
 *  Lua-visible bindings (Task 4 scope; exercised in tests via a test-only
 *  binding); the host calling reload between begin_frame and end_frame sees
 *  each dispatch snapshot independently.
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
 *  cumulative across modules or frames. While a hook runs under the budget,
 *  any nested Lua execution on the owned state counts toward the same
 *  budget. Exceeding the budget aborts the hook with an error: the fault is
 *  recorded like any hook error (with a budget flag) and the module is
 *  MARKED — its frame hooks are skipped on subsequent dispatches until the
 *  next committed reload clears the mark (a fail-closed, deterministic
 *  runaway-module policy). Other modules are unaffected.
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
