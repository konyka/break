#pragma once

/* Runtime Core unified types (design: docs/design/runtime_overview.md §6-§7,
 * docs/design/runtime_thread_model.md §7).
 *
 * This is a formal OPTIONAL library (`runtime_core` static target): it is
 * not linked into `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 * Subsystem-local states (Session NEW/CLOSING/CLOSED, adapter STOPPING,
 * Asset LOADING, ...) are local mappings onto BreakRuntimeState, never a
 * parallel global state machine.
 */

typedef enum BreakRuntimeError {
    BREAK_RUNTIME_OK = 0,
    BREAK_RUNTIME_INVALID,
    BREAK_RUNTIME_CLOSED,
    BREAK_RUNTIME_OVERLOAD,
    BREAK_RUNTIME_OOM,
    BREAK_RUNTIME_TIMEOUT,
    BREAK_RUNTIME_STALE,
    BREAK_RUNTIME_REJECTED,
    BREAK_RUNTIME_FAILED
} BreakRuntimeError;

typedef enum BreakRuntimeState {
    BREAK_RUNTIME_CREATED = 0,
    BREAK_RUNTIME_STARTING,
    BREAK_RUNTIME_RUNNING,
    BREAK_RUNTIME_QUIESCING,
    BREAK_RUNTIME_DRAINING,
    BREAK_RUNTIME_STOPPING,
    BREAK_RUNTIME_STOPPED,
    /* Design name "FAILED" (docs/design/runtime_overview.md §7). C11 places
     * all enumeration constants in one scope, so the state cannot share the
     * BREAK_RUNTIME_FAILED enumerator with BreakRuntimeError; the state keeps
     * the design's ordinal position under a disambiguated identifier. */
    BREAK_RUNTIME_STATE_FAILED
} BreakRuntimeState;

/* Diagnostic names ("OK", "CREATED", ...); never NULL, unknown values map to
 * "UNKNOWN". Pure string conversion, no allocation. */
const char *break_runtime_error_name(BreakRuntimeError error);
const char *break_runtime_state_name(BreakRuntimeState state);
