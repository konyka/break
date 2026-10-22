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
 *  SANDBOX STATUS (Task 1 scope): the owned state is created with the Lua
 *  standard libraries opened (luaL_openlibs), so `os`/`io` are present on the
 *  global environment. Per-module environments with a whitelisted global set
 *  (no io / no os.execute / no raw host access) are Task 4 scope; no module
 *  loading exists yet (Task 2), so nothing script-controlled can reach this
 *  state through the public API.
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
