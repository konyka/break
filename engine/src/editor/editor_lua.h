#pragma once
/* BreakEditorLuaConsole — Stage 4 scene editor Phase 3 Task 2: Lua console
 * core. Owns two Stage 3 BreakLuaRuntimes (a console runtime holding the
 * host-owned ECS batch binding, and a batch-free probe runtime used for
 * compile validation) and evaluates one-line-ish Lua chunks, routing print
 * output and the result value to a bounded log callback and draining the
 * ECS batch into the editor document as UNDOABLE commands.
 *
 * Not a widget: this is the pure CPU core. The panel wiring (edit field,
 * history, routing into the shell console ring) is Phase 3 Task 3 scope. A
 * remote session is NOT delivered (Stage 5-gated, plan Global Constraints).
 *
 * OWNER THREAD: the thread that calls break_editor_lua_create() owns the
 * console (it is the owner of both underlying BreakLuaRuntimes and the
 * batch). There is no mutex, mirroring the break_lua_runtime convention. A
 * non-owner eval logs a bounded "error: ..." line and returns false without
 * touching any Lua state; a non-owner pending_records returns 0; a
 * non-owner destroy is a contract violation handled like the break_lua
 * production convention: the call is IGNORED (nothing is freed). The
 * creating thread must destroy.
 *
 * LOG CALLBACK THREADING (precise): log_fn is invoked synchronously from
 * break_editor_lua_eval on WHATEVER THREAD CALLED eval — normal output is
 * always produced on the owner thread (only owner evals run), but the
 * non-owner rejection notice is logged from the calling (non-owner) thread
 * by design. A sink shared across threads must tolerate that one call site
 * (the console itself never calls log_fn concurrently with itself).
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
 *      attempt's error is logged (lua REPL convention; the wrap is inline,
 *      so both attempts share the typed input's line numbers).
 *   3. Compile probe (injection safety) — the REAL layers (fix round 2; the
 *      round-1 "dual-probe disjointness" claim was false — a
 *      `local p = function() <B> end` wrapper is expression context too —
 *      and the redundant probe L was dropped): the harness embeds the body
 *      in a STATEMENT context (`local function __body() <B> end`), whose
 *      own compile rejects every EXPRESSION-continuation escape (a
 *      statement cannot start with an operator — the review's C1 payload
 *      `end .. (function() while true do end end)() .. function() return 0`
 *      dies here with a plain syntax error, before anything runs on the
 *      console runtime). The probe answers the complementary question —
 *      could the body escape as a STATEMENT sequence? — by compiling
 *      `return function() <B> end` on the probe runtime: nothing may
 *      follow a return, so statement continuations fail the probe compile
 *      (e.g. `end while true do`). A body that passes the probe AND embeds
 *      cleanly is a syntactically complete block: the console runtime
 *      never stages user code. A body escaping ONLY the probe (expression
 *      continuation) is staged once on the PROBE runtime — which has no
 *      batch bound, so it cannot enqueue ECS records, and is budget-armed,
 *      so it cannot hang — and is then rejected by the harness compile.
 *      Both runtimes carry the staging budget as defense in depth
 *      (break_lua arms the count hook over module staging execution and
 *      the commit-path on_unload since fix round 1 — see break_lua.h
 *      INSTRUCTION BUDGET).
 *      Wedged/lost-runtime recovery (fix round 3 — symmetric on BOTH
 *      runtimes): a crafted escape that ran at probe staging could raw-set
 *      a vetoing on_unload on the probe module's env, and the wedge
 *      surfaces at the NEXT probe reload — possibly on an eval that itself
 *      fails at console staging. The console therefore health-checks the
 *      probe runtime with a trivial known-good reload on EVERY failed eval
 *      path (probe failure AND harness stage failure) and recreates it on
 *      veto. The console runtime gets the equivalent path: its health check
 *      (reloading the seed harness) runs on the stage-failure path and on
 *      any dispatch-outcome-unreadable failure; on failure the runtime is
 *      destroyed (releasing the batch binding — the batch stays host-owned)
 *      and recreated + rebound + reseeded. Post-round-3 the console runtime
 *      is not wedgable from the sandbox (the shadow-proof epilogue always
 *      clears on_unload) — this path defends against FUTURE unknown wedge
 *      classes. A lost runtime (Lua-side OOM in init/recreate leaves it
 *      NULL) is lazily re-initialized at the next eval's admission; until
 *      then evals fail bounded with "error: console: console/probe runtime
 *      unavailable" — degraded, never a crash, never permanent (pinned by
 *      console_runtime_recovers_from_lua_oom).
 *   4. Execution: the verified body is embedded in the persistent "console"
 *      module (committed reload per eval — a fresh environment each eval;
 *      no globals leak between evals) as `local function __body() ... end`
 *      and dispatched through break_lua_runtime_begin_frame(), so the Stage
 *      3 count hook arms the 1,000,000-instruction budget on the main
 *      coroutine for exactly the user-code invocation. LEXICAL ISOLATION
 *      (fix round 3): __body is the ONLY chunk-top local; every harness
 *      local (captured stdlib pcall/tostring/type/select/table.concat/
 *      table.unpack, the capture table, the outcome markers) lives in a
 *      `do ... end` block that FOLLOWS __body's definition — a scope the
 *      body is lexically outside of. Body assignments to harness names
 *      (`__tostring = ...`, `__DONE = true`, ...) therefore hit ENV fields,
 *      never harness locals (the round-1/2 shared-chunk-scope upvalue
 *      channel — review NEW-C1/C2 — is closed); the body's only visible
 *      upvalue is __body itself, whose mid-run overwrite is harmless (the
 *      running call is unaffected; the harness never re-references it).
 *      The hook pcalls __body with the sandboxed pcall — since fix round 4
 *      (NEW-C4) that pcall is BUDGET-TRANSPARENT: ordinary runtime errors
 *      are returned as (false, msg) and stored in __E, but the
 *      instruction-budget trip is an unforgeable host-owned sentinel VALUE
 *      that every script-level pcall/xpcall re-raises uninspected — a trip
 *      is uncatchable at any nesting depth and kills on_frame_begin
 *      (propagating to the per-hook pcall; the module is marked
 *      hooks-disabled per the Stage 3 runaway policy, and the next eval's
 *      committed reload clears the mark — the console stays usable). The C
 *      side recognizes the trip via the break_lua_runtime_budget_trip_count
 *      delta across the dispatch and reports "error: break_lua:
 *      instruction budget exceeded" (bounded). Because a trip skips the
 *      epilogue, a body that set on_unload before looping would veto the
 *      NEXT reload's commit — closed by calling the PREVIOUS env's pinned
 *      __console_cleanup (clears on_unload/on_frame_end there) before every
 *      reload; the console-runtime health check + recreate stays as the
 *      backstop. begin_frame is paired with end_frame. The epilogue nils
 *      on_unload AND on_frame_end on every non-trip path (a plain
 *      `on_unload = function() error('veto') end` eval cannot wedge the
 *      console; a body-defined on_frame_end never dispatches — the console
 *      is eval-based, not a frame loop) and then sets __DONE.
 *   5. Outcome + reporting: the C side reads the outcome channel ONLY
 *      through function references pinned via
 *      break_lua_runtime_ref_function after the harness reload commits and
 *      BEFORE the dispatch (the body cannot have run yet) — invoked with
 *      break_lua_runtime_call_ref and released after the read (fix round 3,
 *      NEW-C3: no post-dispatch env-field calls, so a body-overwritten or
 *      looping getter substitutes nothing and cannot hang the host through
 *      the unbudgeted call path). Success is computed from host-trusted
 *      markers only (fix round 2, N2): __DONE (set true only as the hook's
 *      last statement) AND __E (the body pcall's error, empty on success) —
 *      both lexically isolated upvalues; eval_ok = __DONE && __E-empty. A
 *      harness that dies anywhere (OOM-class only, post-round-3) leaves
 *      __DONE false and the eval fails CLOSED: bounded error line, records
 *      discarded, never a false success. Then: captured print lines (see
 *      below), and either the bounded "error: line N: ..." line (N adjusted
 *      back to input-relative line numbers when the standard `console:N:`
 *      position prefix parses; position-less messages — e.g. the count-hook
 *      trip text for a top-level spin — are logged verbatim, bounded) or
 *      the single result value (first return only; strings pre-truncated to
 *      127 bytes inside Lua; table/function/userdata results are
 *      unrepresentable in BreakLuaValue and yield a bounded "error: ..."
 *      line while the eval itself still counts as successful).
 *   6. Batch drain: AFTER each eval the batch is fully drained. On a
 *      successful eval the drained records are applied (below); on a failed
 *      eval (syntax/runtime/budget) they are DISCARDED — a failed chunk
 *      never half-applies. Early-return paths cannot leave residue: probe
 *      staging runs on the batch-free probe runtime and harness staging
 *      runs host-controlled definitions only, so only the dispatch ever
 *      enqueues. break_editor_lua_pending_records therefore returns 0
 *      after every eval.
 *
 * VERSION CHURN: only committed reloads bump a module's u32 version (Stage
 * 3 contract — a failed reload consumes no version). A successful eval
 * commits exactly 2 reloads (probe_r, console) plus 3 ref captures+releases
 * (fixed-slot handles, no versions); the failing attempts of a rejected
 * input consume none, and a wedged-probe recreation adds one trivial probe
 * reload per failed eval. Version-space exhaustion (2^32-1 committed
 * reloads on one module) is a checked, fail-closed BREAK_LUA_REJECTED
 * surfaced as a bounded error line — unreachable in practice (4 billion
 * successful evals).
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
 * bytes, truncation at the boundary); log_fn is invoked from eval only (see
 * LOG CALLBACK THREADING above for the precise thread rule). The console
 * struct carries the fixed 256-record drain buffer (batch default
 * capacity), so eval allocates nothing: the only editor-owned allocation is
 * the console struct at create (OOM-injectable via BREAK_EDITOR_TESTING).
 * Lua-side allocations (two runtimes, batch, chunk compiles) are
 * break_lua-owned and hook into the BREAK_LUA_TESTING budget in test
 * builds.
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
/* Console instruction budget per eval (armed over the eval's frame-hook
 * dispatch AND over module staging/commit execution — see EVAL PIPELINE). */
#define BREAK_EDITOR_LUA_INSTRUCTION_BUDGET 1000000u

/* NULL doc or NULL log_fn => NULL. Also NULL on allocation failure
 * (console struct, Lua runtimes, or batch — partial setup is fully torn
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
