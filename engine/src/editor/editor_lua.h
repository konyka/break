#pragma once
/* BreakEditorLuaConsole — Stage 4 scene editor Phase 3 Task 2: Lua console
 * core. Owns one Stage 3 BreakLuaRuntime + one host-owned BreakLuaEcsBatch
 * and evaluates one-line-ish Lua chunks against them, routing print output
 * and the result value to a bounded log callback and draining the ECS batch
 * into the editor document as UNDOABLE commands.
 *
 * Not a widget: this is the pure CPU core. The panel wiring (edit field,
 * history, routing into the shell console ring) is Phase 3 Task 3 scope. A
 * remote session is NOT delivered (Stage 5-gated, plan Global Constraints).
 *
 * OWNER THREAD: the thread that calls break_editor_lua_create() owns the
 * console (it is the owner of the underlying BreakLuaRuntime and the batch).
 * There is no mutex, mirroring the break_lua_runtime convention. A
 * non-owner eval logs a bounded "error: ..." line and returns false without
 * touching the Lua state; a non-owner pending_records returns 0; a
 * non-owner destroy is a contract violation handled like the break_lua
 * production convention: the call is IGNORED (nothing is freed). The
 * creating thread must destroy.
 *
 * DOCUMENT: the doc is BORROWED, never owned; it must outlive the console.
 * All doc mutations route through the Phase 1 command stack (add_entity /
 * add_component / set_field_f32), so every applied record is undoable via
 * break_editor_undo.
 *
 * EVAL PIPELINE (per break_editor_lua_eval call):
 *   1. Admission: owner check; input is scanned for a NUL within
 *      BREAK_EDITOR_LUA_INPUT_MAX_BYTES + 1 bytes — no NUL in the window or
 *      a length over the cap => bounded "error: input too long" line, false,
 *      nothing else happens.
 *   2. Expression wrap: the input is first tried as `return <input>` (the
 *      standalone lua REPL's order — a bare call like `string.rep('x',2)`
 *      parses fine as a statement, so as-is-first would silently drop
 *      expression values); only if the wrap fails to compile is the input
 *      tried AS-IS as a statement block. On a double failure the AS-IS
 *      attempt's syntax error is logged (lua REPL convention; the wrap is
 *      inline, so both attempts share the typed input's line numbers).
 *   3. Injection safety: Lua-in-Lua textual embedding is escapable (an
 *      unbalanced `end` closes a wrapper function early and the remainder
 *      would run at module STAGING time, which the Stage 3 instruction
 *      budget does not cover — break_lua.h arms budgets per frame-hook
 *      invocation only). The console therefore compiles
 *      `return function() <body> end` in a probe module first: staging that
 *      chunk only CONSTRUCTS the closure — user code never runs at staging,
 *      where the Stage 3 budget is not armed — and a body that would escape
 *      the wrapper is a syntax error there. Only probe-verified bytes are
 *      embedded in the real console module. The probe is a committed reload
 *      per eval, so probe staging runs only closure-construction either way.
 *   4. Execution: the verified body is embedded in the persistent "console"
 *      module (committed reload per eval — a fresh environment each eval;
 *      no globals leak between evals) as `local function __body() ... end`
 *      and dispatched through break_lua_runtime_begin_frame(), so the Stage
 *      3 count hook arms the 1,000,000-instruction budget on the main
 *      coroutine for exactly the user-code invocation. The hook body pcalls
 *      __body in Lua, so runtime errors — including the budget trip — are
 *      CAUGHT and stored instead of propagating: the module's frame hooks
 *      are never marked disabled (Stage 3 runaway policy) and the console is
 *      usable on the next eval; a committed reload per eval would clear any
 *      mark regardless. begin_frame is paired with end_frame.
 *   5. Reporting: captured print lines (see below), then either the bounded
 *      "error: line N: ..." line (N adjusted back to input-relative line
 *      numbers when the standard `console:N:` position prefix parses) or
 *      the single result value (first return only; strings pre-truncated to
 *      127 bytes inside Lua; table/function/userdata results are
 *      unrepresentable in BreakLuaValue and yield a bounded "error: ..."
 *      line while the eval itself still counts as successful).
 *   6. Batch drain: AFTER each eval the batch is fully drained. On a
 *      successful eval the drained records are applied (below); on a failed
 *      eval (syntax/runtime/budget) they are DISCARDED — a failed chunk
 *      never half-applies. break_editor_lua_pending_records therefore
 *      returns 0 after every eval.
 *
 * PRINT CAPTURE: the console module's chunk installs its own `print` env
 * global (shadowing the whitelisted stdout print for this module only —
 * sandbox intact): arguments are tostring'd, '\t'-joined, truncated to 127
 * visible bytes, and at most BREAK_EDITOR_LUA_MAX_PRINT_LINES (32) lines are
 * kept per eval (further prints are dropped silently; bounded).
 *
 * RECORD APPLICATION (successful evals; FIFO; per-record isolation):
 *   - BREAK_LUA_ECS_RECORD_SPAWN => break_editor_doc_add_entity(doc, NULL).
 *      The Stage 3 record layout carries NO script-given name for spawn
 *      (payload zeroed — see break_lua.h RECORD FORMAT), so the name is
 *      always the generated "entity_<index>_<generation>". Exactly ONE
 *      undoable command: a single break_editor_undo reverts a Lua spawn.
 *   - BREAK_LUA_ECS_RECORD_SET => the target is the LAST entity spawned by
 *      THIS eval (records carry no entity name; the doc selection is not
 *      visible to the console core). With no spawn this eval: bounded error
 *      line, record skipped. component/field names are matched byte-wise
 *      (case-sensitive) against the doc registry display/field names
 *      (Phase 1: "Transform" / pos.x..scale.z). If the target lacks the
 *      named registered component, an undoable add_component (zeroed bytes)
 *      is applied first; should the subsequent set_field_f32 still fail, the
 *      component add is rolled back via break_editor_undo — a record is
 *      never half-applied. Values: NUMBER (non-finite rejected) written as
 *      f32; BOOL maps to 1.0f/0.0f; STRING goes through the strict
 *      break_editor_parse_f32 (locale-independent); NONE (malformed) errors.
 *   - Unknown kind/component/field, missing target, rejected value:
 *      a bounded "error: ecs..." line; THAT record is skipped, other records
 *      still apply. A record application failure never fails the eval.
 *   Each applied record costs one (spawn/set) or two (set with implicit
 *   component add) undoable commands; a multi-record eval is multiple
 *   commands (single-record is the common case).
 *
 * BOUNDS: input <= BREAK_EDITOR_LUA_INPUT_MAX_BYTES (4096); every line
 * handed to log_fn is <= 128 bytes INCLUDING the NUL terminator (127 visible
 * bytes, truncation at the boundary); log_fn may be called from eval only
 * (and only on the owner thread). The console struct carries the fixed
 * 256-record drain buffer (batch default capacity), so eval allocates
 * nothing: the only editor-owned allocation is the console struct at
 * create (OOM-injectable via BREAK_EDITOR_TESTING). Lua-side allocations
 * (runtime state, batch, chunk compiles) are break_lua-owned and hook into
 * the BREAK_LUA_TESTING budget in test builds.
 */

#include <core/types.h>

#include <editor/editor_doc.h>

typedef struct BreakEditorLuaConsole BreakEditorLuaConsole;

/* Bounded lines, <=128 bytes (incl. NUL) enforced by the callee. */
typedef void (*BreakEditorLuaLogFn)(void *ctx, const char *line);

/* Longest accepted eval input in bytes (NUL excluded). */
#define BREAK_EDITOR_LUA_INPUT_MAX_BYTES 4096u
/* Print lines captured per eval; each truncated to 127 visible bytes. */
#define BREAK_EDITOR_LUA_MAX_PRINT_LINES 32u
/* Console instruction budget per eval (Stage 3 frame-hook scope). */
#define BREAK_EDITOR_LUA_INSTRUCTION_BUDGET 1000000u

/* NULL doc or NULL log_fn => NULL. Also NULL on allocation failure
 * (console struct, Lua runtime, or batch — partial setup is fully torn
 * down). The calling thread becomes the owner. */
BreakEditorLuaConsole *break_editor_lua_create(BreakEditorDoc *doc,
                                               BreakEditorLuaLogFn log_fn,
                                               void *log_ctx);
/* NULL is a no-op. Owner-thread-only: a non-owner destroy is a contract
 * violation and is IGNORED (nothing freed), mirroring the break_lua
 * production convention. */
void break_editor_lua_destroy(BreakEditorLuaConsole *console);

/* See EVAL PIPELINE above. Returns false on rejection (non-owner, malformed
 * input, over-long input), on syntax/runtime/budget errors, and on internal
 * Lua-facade failures; true when the chunk ran (record-level application
 * errors are reported as log lines and do not flip the result). Every
 * failure is surfaced as a bounded "error: ..." log line. */
bool break_editor_lua_eval(BreakEditorLuaConsole *console, const char *input);

/* Test accessor: batch residue, 0 after any eval. Implemented as a bounded
 * drain-and-discard count (the batch has no count query); non-owner or NULL
 * => 0. */
usize break_editor_lua_pending_records(const BreakEditorLuaConsole *console);
