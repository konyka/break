# Rule Engine Completion Design — 2026-08-28

## Context

`engine/src/rule_engine/` is a C99 bounded re-implementation of the upstream
Rust `rust-rule-engine` (KSD-CO, tag `v1.21.4`, MIT — see
`docs/rule_engine_upstream.yml` / `docs/rule_engine_attribution.md`).
Prior rounds deliberately deferred: method/property calls, deffacts, templates,
persistent agenda, general provenance, backward aggregation/strategies/shared
proof graph, native Redis. This round completes **bounded** versions of those
five areas. The project evidence rule stays in force: no conformance row is
promoted without implementation + executed local test references
(`docs/rule_engine_conformance.yml`).

Upstream semantics referenced below were verified against the `v1.21.4`
sources (git tag `f80a541` / crates.io tarball).

## Conventions for all work items

- Append-only ABI: extend structs via `struct_size`; new entry points added at
  the end of `rule_engine.h` sections. Capability bits
  (`RE_CAP2_*`) are advertised only after their tests pass.
- Parser errors stay atomic (all-or-nothing per source unit).
- Status codes: `RE_STATUS_NOT_SUPPORTED` (unknown method, Redis disabled),
  `RE_STATUS_LIMIT` (caps), `RE_STATUS_INVALID_ARGUMENT` (missing template
  param, non-numeric aggregation), `RE_STATUS_NOT_FOUND` (unknown deffacts
  name, missing nested intermediate).
- Docs updated in the same commit as each feature: `rule_engine_conformance.yml`,
  `rule_engine_upstream.yml`, `docs/Rule_Engine_Design.md`,
  `docs/Rule_Engine_Architecture.md`, `docs/Implementation_Status.md`.
- TDD: failing test first, then implementation, per existing suite style
  (`engine/tests/test_rule_engine*.c`, `RUN_TEST` harness).

## Work item 1 — GRL semantics: method/property, deffacts, templates

### 1.1 Property access (nested structured fallback)

- Read path already done: `re_facts_get_path` (values.c) does exact flat-key
  first, then root-fact + structured member walk (upstream `get_nested`
  parity). This item adds **evidence**: tests covering nested reads in
  conditions, action RHS, and arithmetic operands; conformance row update.
- Write path: add `re_facts_set_path` mirroring upstream `set_nested` —
  exact flat key wins; otherwise walk the root fact's structured object;
  missing intermediate member or non-object intermediate →
  `RE_STATUS_NOT_FOUND` (no implicit object creation). Rule actions
  `a.b.c = value` route through it.
- Tests: nested write updates a structured member and is re-read by a later
  condition; flat dotted key still shadows nested walk.

### 1.2 Method calls on facts

Upstream parity (verified): in `when`, only bare-identifier function calls are
dispatched — dotted calls are not object-dispatched; in `then`,
`$Object.method(args)` is the method-call form with hardcoded
set/get conventions.

- `when` conditions: **unchanged** — calls resolve via registered functions
  only (documented bounded parity).
- `then` actions: parse `$Fact.method(arg, ...)` (`$` prefix required;
  `$` anywhere else is a parse error). New IR action kind
  `RE_IR_ACTION_METHOD_CALL` (receiver fact path, method name, arg terms).
  Execution order:
  1. `setXxx(v)` (1 arg) → structured member write of property `Xxx` on the
     receiver fact (receiver must be a structured object; arg terms evaluated
     first).
  2. `getXxx()` (0 args) → read property `Xxx`; usable as an action RHS
     operand form `$Fact.getXxx()`.
  3. `reset()` → clear receiver members; `update()` → re-store receiver
     (bounded no-op, kept for source parity).
  4. Otherwise dispatch to a registered custom action handler named
     `Fact.method`, then bare `method`. None registered →
     `RE_STATUS_NOT_SUPPORTED` (explicit failure; upstream silently no-ops —
     deliberate documented divergence).
- Tests: set/get round-trip on a structured fact; reset clears; unknown
  method without handler fails; handler dispatch order; `$` misuse parse
  errors; mutation notifies subscribers like ordinary writes.

### 1.3 deffacts

Upstream is Rust-API-only (no GRL keyword); loads are explicit;
`reset_with_deffacts` = CLIPS reset.

- Local GRL extension (documented as local, not upstream parity):
  top-level `deffacts "name" { path = literal; ... }` — flat fact paths,
  scalar/array literals only, parsed atomically alongside rules.
- Runtime: program stores named deffacts sets.
  `re_engine_load_deffacts(engine, facts, name_or_NULL)` asserts one set (or
  all, NULL), plain non-logical sets, duplicates overwrite.
  `re_engine_reset_with_deffacts(engine, facts)` clears working memory
  (facts + TMS justifications + agenda state) then loads all sets.
- Tests: load seeds facts and rules fire on them; reset clears derived facts
  and reseeds; unknown name → `RE_STATUS_NOT_FOUND`; duplicate deffacts name
  in one source → parse error.

### 1.4 Rule templates

Upstream parity (`src/engine/template.rs`): string-template GRL generation,
`{{param}}` placeholders, plain substitution, defaults, generated rules are
ordinary parsed rules.

- C API: `re_rule_template_create(name, condition_template,
  action_template, salience)`; `re_rule_template_param(template, name,
  type_tag, default_or_NULL)` (type tag is metadata only — upstream does no
  substituted-value checking); `re_rule_template_instantiate(template,
  rule_name, params, param_count, out_grl_text)`; missing required param →
  `RE_STATUS_INVALID_ARGUMENT`.
- Registry on program: `re_program_add_template`,
  `re_program_generate_rules(program, template_name, instances, count)` —
  instantiates + parses through the existing parser.
- Bounded exclusions (documented): no JSON round-trip (upstream serde
  helper), no CLIPS-deftemplate fact-schema validator (upstream
  `rete/template.rs` — separate feature, stays unsupported).
- Tests: substitution with defaults; missing required param; generated rule
  parses and fires; bulk generation; `{{param}}` inside string literals
  substituted verbatim (upstream plain-substitution parity).

## Work item 2 — multi-rule activation, persistent agenda, provenance

### 2.1 Recognize–act cycle (completes multi-rule activation)

Current `re_engine_run` is a single sorted pass; rules fired earlier are
never re-activated by facts asserted later in the same run.

- Replace with an agenda loop: compute activations for all visible rules →
  fire highest salience (tie: source order) → commit its transaction →
  recompute activations → repeat until none or a limit trips.
- **Refraction**: within a run, an activation identified by
  (rule index, premise fact ids, premise generations) does not refire.
  Bounded: fired-set tuple cap (new `re_limits_t.max_activations_tracked`,
  default 1024); overflow → `RE_STATUS_LIMIT`.
- All existing controls preserved: salience/source order, no-loop,
  lock-on-active, activation-group, agenda-group/module focus, date bounds,
  `max_firings`/`max_agenda_activations`, cancellation, executor parallel
  match for pure conditions (match bits recomputed per cycle).
- RETE: extend auto-attach from single-rule programs to programs where
  **every** rule is RETE-eligible (≤8 AND-of-`fact <cmp> literal`);
  alpha memories shared across rules; per-rule token subsets drive
  per-rule activations. Ineligible programs keep the linear evaluator.
- Behavior change is intentional and documented: rules can now re-activate
  within a run when their premises change (upstream parity). Existing tests
  must stay green except where they asserted single-pass semantics — those
  are updated with a conformance note.

### 2.2 Persistent agenda

`re_agenda_t` becomes a real object owned by the engine (created lazily):
pending activation list + fired-history (refraction keys) + monotonic
activation sequence counter.

- Default unchanged: agenda cleared at the end of a successful
  `re_engine_run` (back-compat one-run semantics).
- New opt-in: `re_engine_set_agenda_persistent(engine, enabled)`. When
  enabled, pending activations and fired-history survive across runs; a
  premise generation change re-activates. TMS cascade-retraction cancels
  activations whose premises lost justification.
- Inspection: `re_engine_agenda(engine, &agenda)` (replaces the current
  `NOT_SUPPORTED` stub), `re_agenda_count`, `re_agenda_peek(index, &entry)`
  exposing rule name, salience, sequence, premise ids. `re_agenda_destroy`
  remains a no-op for engine-owned instances (documented).
- `RE_CAP2_AGENDA_RETE` advertised once tests pass.

### 2.3 Complete provenance

Current lineage exists only on the RETE path (engine-owned network).

- Track fact reads during condition evaluation: `ir_eval` records read paths
  into a bounded per-evaluation read-set (cap 16; overflow → evaluation
  falls back to RETE-less firing without logical insert, status stays OK —
  documented bound).
- On firing, premises = RETE lineage (if any) ∪ read-set fact ids; stored
  via existing `re_facts_insert_logical` / `re_facts_justification_add`
  (multi-producer already supported).
- `re_facts_provenance_get` gains direct tests (producer rule, premise ids,
  multi-producer accumulation, cascade retraction via TMS).
- Documented bound: provenance covers forward derivations; backward proofs
  remain per-query plus the shared graph of work item 3.

## Work item 3 — backward: negation, aggregation, strategies, shared proof graph

Upstream parity anchors: negation-as-failure (closed-world, **no
stratification**); `SearchStrategy::{DepthFirst, BreadthFirst, Iterative}`
with BFS implemented as iterative-deepening; aggregation via a
`query_aggregate` API (`count/sum/avg/min/max/first/last`); proof graph
shared via an engine-held graph with generation-based invalidation.

### 3.1 Query-level negation

- Query strings accept prefix `NOT <goal>`: succeeds (empty bindings) iff
  the subgoal is unprovable; fails if any solution exists. Bounded: `NOT `
  prefix only (upstream also has `!(...)` — excluded, documented).
- Existing condition-level `NOT` unchanged. No stratification checks
  (upstream parity); cycle safety via existing active-path detection.

### 3.2 Query aggregation

- New API `re_engine_query_aggregate(engine, facts, kind, field_or_NULL,
  pattern, out_value)`: runs the bounded query with `max_solutions` at the
  configured cap, folds solution bindings over `field` with
  count/sum/avg/min/max/first/last (reuses `re_accumulator_kind_t`).
  Non-numeric fold input for sum/avg/min/max → `RE_STATUS_INVALID_ARGUMENT`.
- Bounded exclusions (documented): percentile/stddev/count-distinct.

### 3.3 Search strategies

- `re_query_config_t` (append-only) gains `strategy`:
  `RE_QUERY_STRATEGY_DEPTH_FIRST` (default, current machine),
  `RE_QUERY_STRATEGY_BREADTH_FIRST` = iterative-deepening over the existing
  DFS machine (re-run with depth caps 1, 2, 4, … up to `max_depth` until a
  solution appears — upstream parity: upstream BFS is likewise
  iterative-deepening; backward queries execute no actions, so re-probing is
  side-effect free), `RE_QUERY_STRATEGY_ITERATIVE` alias of BFS.
- Per-probe `max_depth`; total probe cap (depth increment ≤ 32) →
  `RE_STATUS_LIMIT`.

### 3.4 Shared proof graph

- Engine-owned `re_proof_graph_t`: map goal-string → cached proof
  (nodes/edges/bindings) stamped with the engine's fact-mutation
  generation. Queries consult first; on success insert. Stale entries
  (generation mismatch) are skipped and evicted lazily.
- Bounded: 64-entry cap; on full, clear-all (simple, deterministic).
  Opt-out per query via `re_query_config_t.share_proof_graph = 0`.
  Statistics: `re_engine_proof_graph_stats(engine, &hits, &misses)`.

## Work item 4 — streaming, Redis boundary, concurrency boundary

### 4.1 Streaming aggregation completion

Upstream window ops include min/max/first/last in addition to
count/sum/average.

- Extend `re_stream_window_aggregate_v1` kinds with `MIN`, `MAX`, `FIRST`,
  `LAST` over the retained, type/key-filtered events. Empty window →
  `RE_STATUS_NOT_FOUND`. Non-numeric field for MIN/MAX →
  `RE_STATUS_INVALID_ARGUMENT`.

### 4.2 Redis boundary

Documented boundary stays: discovery failure leaves the option disabled;
no silent fallback; unavailable service = unavailable evidence, not a pass.

- CMake option `RULE_ENGINE_ENABLE_REDIS` (default OFF). When ON:
  `find_path` + `find_library` for hiredis; found → compile
  `redis_provider.c` implementing the `re_state_provider_t` v1 vtable over
  the **synchronous** hiredis API (upstream parity: upstream uses the sync
  `redis` crate connection): key = `prefix + ":" + name`, value =
  length-prefixed bytes, TTL via `PSETEX`/`PEXPIRE`. Not found → option
  forced OFF with a CMake `STATUS` message.
- Without hiredis, `RE_STATE_PROVIDER_REDIS` keeps returning
  `RE_STATUS_NOT_SUPPORTED`; existing boundary tests stay green.
- Integration test runs only when `RE_TEST_REDIS_URL` is set; otherwise the
  test skips itself (recorded as unavailable evidence).

### 4.3 Concurrency boundary hardening

- Header contract documented: engine/facts/windows/providers are
  single-threaded; mutation during `re_engine_run` → `RE_STATUS_BUSY`
  (existing flags); C11 executor workers evaluate read-only conditions.
- Audit `extensions.c` / `tumbling_session.c` / `stream_correlation.c` for
  missing in-use guards on snapshot/restore/aggregate vs record; add the
  minimal flag where absent.
- Extend `test_rule_engine_executor_stress.c` with a case asserting BUSY on
  mutation attempts during a run (orchestrated single-thread through the
  public flags, plus the existing threaded stress).

## Work item 5 — full gate, selective commit, push

Gate (mirrors `.github/workflows/ci.yml` windows-clang + documented
hardening extras; graphics label excluded on Windows per Build_Guide):

1. Clang/Ninja Debug: configure `cmake -S engine -B build-gate -G Ninja
   -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug`, build all +
   `dxx_break`, `ctest -LE graphics --output-on-failure`.
2. MSVC Ninja Debug and Release: build + `ctest -LE graphics`.
3. Presets `hardening-asan` and `hardening-ubsan` (clang): build + full
   ctest (includes `rule_engine_fuzz_smoke`, `executor_stress`).
4. Bench regression: build `rule_engine_bench`, run
   `engine/scripts/rule_engine_bench_regression.cmake` against
   `rule_engine_bench_thresholds.txt`.
5. `git diff --check` clean on the committed set.

Commit plan (selective): one commit for this design doc; then one commit per
work item (sources + tests + CMake registration + the five docs). The 21
pre-existing dirty files outside `engine/src/rule_engine`,
`engine/tests/test_rule_engine*`, and `docs/` are **not** part of this work
and remain uncommitted. Push to `origin master` only after every gate step
is green.

## Testing strategy

New suites (registered in `engine/CMakeLists.txt` beside the existing ones):

- `test_rule_engine_grl_semantics.c` — 1.1–1.4.
- `test_rule_engine_agenda.c` — 2.1–2.3 (cycle, refraction, persistence,
  provenance on the linear path).
- `test_rule_engine_backward_ext.c` — 3.1–3.4.
- `test_rule_engine_stream_ext.c` — 4.1–4.2 (Redis skip-path covered in the
  existing suite).

Allocator-failure injection and limit-overflow paths follow the existing
suites' patterns. Sanitizer presets must run the new suites clean.
