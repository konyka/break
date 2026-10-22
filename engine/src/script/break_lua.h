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
 *  SANDBOX STATUS (Task 2 scope): the owned state is created with the Lua
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
 *    BREAK_LUA_TIMEOUT   — a bounded wait/budget expired (Task 3 scope).
 *    BREAK_LUA_STALE     — a handle/version no longer names the live object
 *                          (Task 2 scope).
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
