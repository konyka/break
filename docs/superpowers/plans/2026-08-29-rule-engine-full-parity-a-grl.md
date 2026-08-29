# Sub-project A: GRL / Expression Surface Completion — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: superpowers:subagent-driven-development. Steps use checkbox (`- [ ]`) syntax.

**Goal:** every upstream rust-rule-engine v1.21.4 GRL/expression construct parses and evaluates in the C99 engine, with upstream semantics as verified from the tag `f80a541` sources.

**Architecture:** extend the existing parser (`parser.c`) → IR (`ir.c`) → evaluator (`ir_eval.c`) → executor (`engine.c`) pipeline; add a built-in function registry; add a GRL query-block parser + executor on top of the Phase-3 backward machine. New test suites per task under `engine/tests/`.

**Tech Stack:** C99, CMake/Ninja, clang (+MSVC matrix), ctest, `test_framework.h`.

## Global Constraints

- All constraints from `docs/superpowers/plans/2026-08-28-rule-engine-completion.md` remain in force (append-only ABI, C99, CRLF/local conventions, evidence rule, selective commits, never touch the 21 pre-existing dirty files or `.omo/`).
- Upstream semantics citations below are from tag `f80a541` sources (research verified 2026-08-29). Where upstream is degenerate (e.g. silently dropped receivers, non-short-circuit compound eval), we keep our saner local behavior and document the divergence — feature coverage is the goal, bug replication is not.
- Base commit: `4110f83`. Build: `cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug` (exists); iterate with `cmake --build build-gate --target <t> --parallel` + `ctest --test-dir build-gate -R <t> --output-on-failure`; phase gate = full rule-engine regex suite + ASan/UBSan spot.
- Ledger: `.superpowers/sdd/2026-08-29-rule-engine-full-parity/progress.md`.

## Parity decisions (binding for all tasks)

- D1. Compound `&&`/`||` evaluation: local keeps short-circuit (upstream evaluates both sides always — engine.rs L644-654). Documented divergence; side-effect-free conditions make them observationally equal.
- D2. Condition-position `Obj.Method()`: upstream has no receiver-aware dispatch (receiver silently dropped, bare-name function lookup). Local keeps our stricter behavior (full dotted name → registered function, else NOT_SUPPORTED/false). Documented divergence.
- D3. `matches` stays wildcard-substring (upstream is a substring stub too — types.rs L372-378).
- D4. Equality has NO numeric cross-coercion upstream (`Integer(1) != Number(1.0)`); relational ops coerce via `to_number()` (numeric strings coerce; bool/array/object/null → false). Local: match this exactly (check current local behavior first — adjust `re_value_compare` semantics only if divergent, with tests).
- D5. Upstream action builtins `ScheduleRule`/`CompleteWorkflow`/`SetWorkflowData` touch workflow/scheduler subsystems that don't exist locally: parse them and dispatch to a registered custom action handler; unhandled → RE_STATUS_NOT_SUPPORTED (documented bounded divergence from upstream's internal handling).
- D6. `forall` over an empty candidate set is vacuously TRUE (upstream pattern_matcher.rs).
- D7. exists/forall candidate selection uses upstream's fact-name-prefix heuristic: inner condition's target type = text before the first `.` of the leftmost field reference; candidates = all facts whose name equals or starts with that prefix; each candidate is evaluated with the prefix bound to that fact (see pattern_matcher.rs).

## Task A1: operator aliases, literal case-insensitivity, `%`, string concat

**Files:**
- Modify: `engine/src/rule_engine/parser.c` (operator lexing, literal parsing), `ir_eval.c`/`engine.c` (eval semantics if missing)
- Test: `engine/tests/test_rule_engine_grl_surface.c` (new; register in engine/CMakeLists.txt mirroring existing blocks)

**Interfaces:**
- Consumes: existing comparison ops in parser.c:380-394 area; arithmetic in parser.c:322-378; literal parsing in operand_parse_atom.
- Produces: word aliases `eq ne gt gte lt lte not_contains starts_with ends_with` (types.rs L267-283); boolean/null literals case-insensitive (`TRUE`, `False`, `NULL`); modulo `%` (f64 `%` semantics, integer result when both int and fract()==0); `+` string concatenation when either operand non-numeric — but only String+String, else error (upstream expression.rs apply_operator).

- [ ] Step 1: failing tests — each alias in a rule (`when A eq 1`, `B not_contains "x"`, etc.); `TRUE`/`False`/`NULL` literals; `N % 3 == 0`; `"a" + "b"` concat in action RHS; concat with non-string → error path.
- [ ] Step 2: build → fail. Step 3: implement. Step 4: pass. Step 5: full rule-engine suite green.
- [ ] Step 6: coercion audit test: `Integer(1) == Number(1.0)` must be FALSE (D4); `"42" > 5` TRUE (string→number coercion on relational); `"abc" > 5` FALSE. Fix `re_value_compare` if divergent.

## Task A2: general `!(...)`, `exists(...)`, `forall(...)`

**Files:**
- Modify: `parser.c` (new condition forms in the expression parser — currently `exists fact <cmp> literal` only; `exists(` with parens currently returns NOT_SUPPORTED), `ir.h`/`ir.c` (nested condition operands), `ir_validate.c`, `ir_eval.c` (evaluation with prefix-heuristic candidate sets)
- Test: `engine/tests/test_rule_engine_grl_surface.c`

**Interfaces:**
- Consumes: existing RE_EXPR_NOT/EXISTS/FORALL kinds; `re_facts_get_path`; the AND/OR tree machinery.
- Produces:
  - `!( <expr> )` — negation of any parenthesized condition expression (upstream `!` prefix form; keep our existing `not` keyword too).
  - `exists( <expr> )` / `forall( <expr> )` — inner is any boolean expression. Evaluation per D6/D7: extract target type = text before first `.` of the leftmost field ref in the inner expr; candidates = facts whose name == prefix or starts with it; for each candidate evaluate inner with the prefix rebound to that candidate's value (nested structured access continues to work via get_path on the rebound root); exists = any, forall = all (vacuous-true). If no target type extractable → evaluate inner against the plain fact store (upstream's fallback).
  - Existing restricted forms (`exists fact <cmp> literal`, bounded `forall` array form) keep working — they parse into the same nodes.

- [ ] Step 1: failing tests — `!(A == 1)`; `exists(Score.value > 90)` over facts `Score1`/`Score2`; `forall(Alert.level == "low")` incl. vacuous-true on zero candidates; nested `!exists(...)`; `exists(A == 1 && B == 2)` with the AND inside.
- [ ] Step 2-5: TDD cycle; full suite green (watch: the existing `exists(` → NOT_SUPPORTED test must be updated — it's the intended behavior change; note it in the report).

## Task A3: condition built-in functions

**Files:**
- Modify: `engine.c` (function resolution path) or a new `builtins.c` added to rule_engine_core; `re_internal.h` if a registry node type is needed
- Test: `engine/tests/test_rule_engine_grl_surface.c`

**Interfaces:**
- Produces: engine-level built-in functions available in `when` conditions (and action RHS where they make sense), matching upstream condition_evaluator.rs semantics: `len`/`length`/`size` (String byte len, Array elem count, else false-ish), `isEmpty`/`is_empty` (String/Array empty, Null→true, else false), `contains(x, y)` (String∋substr or Array ∋ element by typed equality), `exists("field")` / `notExists`/`not_exists("field")` (fact presence via get/get_nested — CAREFUL: name collides with the quantifier keyword; the function form has parentheses+quoted/bare arg, the quantifier form has a parenthesized condition — disambiguate in the parser by context, document the rule). Unknown condition function behavior: check current local behavior (error vs false); upstream forward = false, backward = false; local currently returns an error status — decide: keep NOT_SUPPORTED for parse-time-unknown, but a REGISTERED-then-unregistered function evaluates to false; document.
- Built-ins are overridable by user-registered functions of the same name (user wins) — document.

- [ ] Step 1: failing tests per built-in incl. wrong-type args and user-override. Step 2-5: TDD cycle; full suite green.

## Task A4: action/RHS utility built-ins

**Files:**
- Modify: `builtins.c` (from A3) or `engine.c`
- Test: `engine/tests/test_rule_engine_grl_surface.c`

**Interfaces:**
- Produces (upstream engine.rs L1411 table, as callable functions in action RHS and `$...` args evaluation): `log/print/println` (join args with " ", return message string; log also writes to stdout via the engine's log convention — check if a log callback exists; else stdout), `now`/`timestamp` (unix secs as string), `random` (0-99 or <max; deterministic seeding hook: use a per-engine counter/seed so tests are deterministic — document), `format`/`sprintf`, `length`/`size`/`count`, `sum`/`add`, `max`, `min`, `avg`/`average`, `round`, `floor`, `ceil`, `abs`, `contains`/`includes`, `startswith`, `endswith`, `lowercase`, `uppercase`, `trim`, `split`, `join`.

- [ ] Step 1: failing tests (a representative from each family + edge cases: empty args, wrong types). Step 2-5: TDD cycle; full suite green.

## Task A5: multifield condition ops on array fields

**Files:**
- Modify: `parser.c`, `ir.h`/`ir.c`, `ir_validate.c`, `ir_eval.c`
- Test: `engine/tests/test_rule_engine_grl_surface.c`

**Interfaces:**
- Produces (upstream multifield regexes grl.rs L115-155, forward engine.rs L1115-1164 semantics): `F.arr count <cmp> n` (array length compare; missing field → count 0), `F.arr first` / `F.arr last` (true iff non-empty array — no binding), `F.arr empty` (missing field → TRUE), `F.arr not_empty` / `notEmpty` (missing → false), plus keep existing `in`. (Upstream `collect` returns "true iff field exists" — include it.)

- [ ] Step 1: failing tests per op incl. missing-field semantics. Step 2-5: TDD cycle; full suite green.

## Task A6: `accumulate(...)` CE

**Files:**
- Modify: `parser.c`, `ir.h`/`ir.c`, `ir_validate.c`, `ir_eval.c` or `engine.c`
- Test: `engine/tests/test_rule_engine_grl_surface.c`

**Interfaces:**
- Produces (upstream grl.rs L834-881 + engine.rs L701-830 semantics): `accumulate(Type($var: field, cond1, ...), func(...))` where func ∈ sum/count/average/avg/min/max; flat-scan fact keys starting with `"Type."`; group by instance segment; per-instance mini-eval of the string conditions (operator scan order `== != >= <= > <`; RHS quote-stripped; typed compare); collect the extract field from matching instances; fold (sum f64 / count i64 / average f64 / min/max; empty → 0 semantics per upstream); inject result as fact key `"Type.func"`; the accumulate condition itself evaluates TRUE always. Document the upstream quirks reproduced vs skipped (e.g. upstream's operator scan order bug where `>=` inside a condition string is found before `>` — replicate or fix? DECISION: fix (scan longest-first), document divergence).

- [ ] Step 1: failing tests — sum over `Order.*.amount` with conditions; count; empty-set → 0; result readable by a follow-up condition in the same `when`. Step 2-5: TDD cycle; full suite green.

## Task A7: GRL query blocks

**Files:**
- Modify: `parser.c` (top-level `query "Name" { ... }` form), `ir.h`/`ir.c`/`ir_validate.c` (query tables), `engine.c` or new `query_exec.c` (executor); `rule_engine.h` (API append)
- Test: `engine/tests/test_rule_engine_grl_surface.c`

**Interfaces:**
- Consumes: Phase-3 backward machine (`re_engine_query_bounded`, strategies, NOT, aggregation), facts, run loop.
- Produces:
  - Grammar (upstream grl_query.rs L17-42): `query "Name" { goal: <expr>; strategy: depth-first|breadth-first|iterative; max-depth: N; max-solutions: N; enable-memoization: bool; enable-optimization: bool; when: <expr>; on-success: {...}; on-failure: {...}; on-missing: {...} }` — only `goal:` required; defaults per upstream (strategy depth-first, max-depth 10, max-solutions 1, memoization true, optimization true-but-documented-noop).
  - API: `re_status_t re_engine_run_queries(re_engine_t *engine, re_facts_t *facts);` (runs all query blocks in source order) and `re_status_t re_engine_run_query(re_engine_t *engine, re_facts_t *facts, re_string_t name);` (NOT_FOUND if absent).
  - Executor semantics (upstream L692-742): `when` gate via a simple expression eval (use our condition evaluator); false → skip (no actions); goal splitting TEXTUAL: both `&&` and `||` → strip outer parens, split `||`, each part split `&&`; subgoals containing `!=` are evaluated directly against facts (no rule derivation); merge bindings/solutions from successful branches; provable → on-success; else missing-facts non-empty → on-missing (our machine doesn't track missing_facts — map: DISPROVED/UNKNOWN → on-failure; document the on-missing mapping decision); actions: `Name = true|false|<f64>|"string"` (flat fact set) and calls `LogMessage/Request/Print/Debug` (stdout/stderr per upstream); unknown call → warning not error (route to a log callback if one exists, else stderr).
- [ ] Step 1: failing tests — full block parse; when-gate skip; on-success assignment writes a fact; on-failure path; strategy/max-depth honored; unknown query name → NOT_FOUND. Step 2-5: TDD cycle; full suite green.

## Task A8: action built-ins (retract/log/agenda-group/workflow seam)

**Files:**
- Modify: `parser.c`, `ir.h`/`ir.c`, `engine.c`
- Test: `engine/tests/test_rule_engine_grl_surface.c`

**Interfaces:**
- Produces:
  - `retract($Obj)` action → sets flag fact `_retracted_<Obj> = true`; field conditions whose leftmost object prefix has the flag evaluate false (upstream engine.rs L964-975/L1240-1247). Also: `retract` on the flag reverses it? No — upstream only sets. Ours: same + document.
  - `log(...)` action → Log (stdout or log callback).
  - `ActivateAgendaGroup("g")` → sets the engine's agenda focus to group g for the remainder of the run (maps to our agenda-group focus machinery).
  - `ScheduleRule(ms, "rule")`, `CompleteWorkflow("w")`, `SetWorkflowData("k=v")` → per D5: dispatch to registered custom handler (name = the action name), else RE_STATUS_NOT_SUPPORTED.

- [ ] Step 1: failing tests per action. Step 2-5: TDD cycle; full suite green.

## Task A9: `test(...)` CE and typed `$x: Type(conds)`

**Files:**
- Modify: `parser.c`, `ir_eval.c`
- Test: `engine/tests/test_rule_engine_grl_surface.c`

**Interfaces:**
- Produces: `test(f(args))` CE — evaluates the function/expression and truthiness-tests the result (to_bool: Bool as-is; String non-empty; Number ≠0; Integer ≠0; Array/Object non-empty; Null/Expression→false — types.rs L106). Typed `$x: Type(conds)` — upstream binds $x to the matching fact (used by RETE loader); local forward engine: evaluate conds with the Type prefix heuristic (same candidate machinery as A2); the binding is used in later conditions/actions as `$x.field` — if full variable binding is too deep a change, bound it: implement as exists-semantics + document.

- [ ] Step 1: failing tests. Step 2-5: TDD cycle; full suite green.

## Task A10: syntax sweep + docs + phase commit + push

- [ ] Step 1: diff the local grammar against upstream GRL_SYNTAX.md inventory one final time; every remaining gap gets either a test+fix or a conformance note with reason.
- [ ] Step 2: docs — conformance.yml rows (quantifiers-general, builtins, multifield, accumulate, query-blocks, action-builtins, operator-aliases), upstream.yml updates, Design/Architecture sections, Implementation_Status dated entry.
- [ ] Step 3: full gate (clang Debug all-target + ctest `-LE graphics`; ASan+UBSan trees; MSVC rule-engine matrix; bench regression; `git diff --check`).
- [ ] Step 4: selective commit (`engine/src/rule_engine/`, new/changed test files, `engine/CMakeLists.txt`, five docs) — message: "Complete GRL surface: quantifiers, builtins, multifield, accumulate, query blocks, action builtins". Push origin master (fetch+merge first if remote moved).
