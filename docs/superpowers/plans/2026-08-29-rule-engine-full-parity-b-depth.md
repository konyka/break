# Sub-project B: RETE / TMS / Unification Depth — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: superpowers:subagent-driven-development. Steps use checkbox (`- [ ]`) syntax.

**Goal:** close the real deltas against upstream v1.21.4's *working* deep machinery (TMS, proof graph, backward unification, agenda focus stack), per the re-scoped spec section (`docs/superpowers/specs/2026-08-29-rule-engine-full-parity-design.md` §Sub-project B). Upstream vapor (cross-rule RETE networks, dead Unifier integration, per-query-throwaway proof caches, stub parallel actions) is documented, not replicated.

**Base:** sub-project A complete (bf11de3 + merge d537c7d). Build/test/loop conventions as in the A plan (`build-gate`, focused ctest `-R "rule_engine|backward_machine"` currently 18/18, ASan tree `build-rule-fresh-asan`).

**Ledger:** `.superpowers/sdd/2026-08-29-rule-engine-full-parity/progress.md` (append B entries).

## Upstream anchors (verified from tag f80a541 sources)

- TMS (`src/rete/tms.rs`): justifications {Explicit, Logical}; Explicit unconditionally valid; Logical valid iff no premise retracted; `retract_with_cascade` recurses through `fact_dependents` with the retracted set as cycle guard; multi-justification per fact; NO re-derivation on new justification; retract never cleans the maps.
- Proof graph (`src/backward/proof_graph.rs`): `FactKey{fact_type, field, pattern}` (parse: text before first `.` = type, leading alnum_ of rest = field); node {key, handle, justifications[], dependents, valid, generation, bindings}; `insert_proof` (generation++, per-handle node, index by key, dependency edges premise→node + node.dependents); `lookup_by_key` filters valid; `invalidate_handle` per-premise justification removal + recursive dependent propagation; stats {total_nodes, cache_hits, cache_misses, invalidations, justifications_added}.
- Unification (`src/backward/unification.rs`): case table Variable↔value (bind via expression_to_value; unbound/unresolvable → false, no deferral), Literal↔Literal eq, Field↔Field name eq, Comparison/And/Or/Not structural, else false; sticky-consistent `bind` (same value ok, different → error); no occurs check; `?var` syntax in the backward expression parser.
- Agenda: AdvancedAgenda focus + focus STACK (pop when the focus group empties), auto_focus attribute switches focus on activation, Ord = salience desc + recency.

## Task B1: TMS parity closure

**Files:** Modify `engine/src/rule_engine/tms.c`, `facts.c` (only if a validity rule needs it); Test: `engine/tests/test_rule_engine_tms.c` (extend)

**Interfaces:** existing `re_facts_insert_logical`, `re_facts_justification_add/remove`, `re_facts_provenance_get`, `re_facts_is_logical`, cascade retraction.

- [ ] Step 1: port upstream's 12 TMS test semantics as local cases: explicit-not-auto-retracted; premise-removed cascade; chain A→B→C; multiple justifications (one premise retracted → fact survives iff another valid justification remains); diamond A→B,A→C,B+C→D; explicit beats logical (a fact with BOTH an explicit set and logical justifications survives premise retraction — check current local behavior: does an explicit `re_facts_set` on a logically-derived fact drop the justifications or coexist? trace facts.c/tms.c and pin semantics with a test; upstream tms.rs keeps both justification lists — match); cycle A↔B terminates.
- [ ] Step 2: implement deltas found (expect few — the local TMS already does most of this; the likely delta is explicit/logical coexistence semantics).
- [ ] Step 3: full suite green + ASan spot.

## Task B2: proof graph → real graph shape

**Files:** Modify `engine/src/rule_engine/proof_graph.c`, `re_internal.h`, `backward.c` (wiring); Test: `engine/tests/test_rule_engine_backward_ext.c`

**Interfaces:** existing engine-owned 64-entry result cache (goal+facts+generation+options keyed, hit/miss stats) becomes the lookup layer; the graph layer adds upstream's node/dependent semantics.

- [ ] Step 1: extend the graph: per-goal entries gain a node list with justifications {rule_name, premise fact ids/keys} and dependents; store path records the proving rule + premise ids (available from proofs' trace/premise info — check what proofs carry; if insufficient, capture premises during the backward run).
- [ ] Step 2: invalidation upgrade: on fact mutation, instead of the coarse per-facts generation drop, per-premise invalidation propagates through dependents (a cached result whose proof's premises are all still valid SURVIVES an unrelated mutation — this is the real behavioral upgrade; keep the generation check as the fast path, per-premise as the precise path... simpler: replace coarse invalidation with per-premise entirely if the premise sets are recorded; decide by implementation cleanliness, document).
- [ ] Step 3: keep the 64-entry cap + clear-all bound; stats API gains invalidations count (append to the stats function or add fields — ABI: re_engine_proof_graph_stats currently takes hits/misses out-params; add `re_engine_proof_graph_stats_v2` or extend? Prefer extending the SAME function only if signature unchanged... it takes two pointers; add a new v2 call with a stats struct).
- [ ] Step 4: tests: upstream's 6 proof_graph integration cases ported (basic, invalidation chain A→B→C, multiple justifications survive partial invalidation, hit/miss stats, FactKey parsing equivalent, dependency propagation) + the existing cache tests stay green.
- [ ] Step 5: full suite + ASan.

## Task B3: backward unification with `?var`

**Files:** Modify `engine/src/rule_engine/backward.c` (+ maybe `backward_machine*.c`), `parser.c` only if goal-string syntax needs it; Test: `engine/tests/test_rule_engine_backward_ext.c`

**Interfaces:** existing goal strings (`Name == literal`, `Name == Variable` formals via goal("Rule") machinery), the proof binding surface.

- [ ] Step 1: `?var` operands in query goal strings: `User.Score >= 80` stays a proof query; `User.Score == ?s` binds `?s` per solution (bindings surface in proofs via the existing re_proof_binding_get). Variable-on-either-side unify per the upstream case table: bound variable → its value; unbound + resolvable → bind; unresolvable → no match (no deferral); two unbound variables → no match; sticky-consistent (same var rebound to a different value → that branch fails, not an engine error).
- [ ] Step 2: `?var` flows through goal("Rule") formals/actuals (bind_arguments path) and the aggregation API (`re_engine_query_aggregate` field names a binding — `?s` should work there).
- [ ] Step 3: no occurs check (upstream parity — document); no structured-term unification (values are scalars/arrays — array-element unification: bound to typed equality only, document).
- [ ] Step 4: tests: bind from fact, bind through rule goal chains, sticky-consistency conflict fails the branch, `?x == ?y` unbound both sides → no match, aggregation over `?s` bindings, multi-solution binding enumeration under max_solutions.
- [ ] Step 5: full suite + ASan.

## Task B4: agenda focus stack + auto-focus

**Files:** Modify `engine/src/rule_engine/engine.c`, `parser.c` (auto-focus attribute), `ir.h`/`ir.c` (attribute), `agenda.c`; Test: `engine/tests/test_rule_engine_agenda.c`

**Interfaces:** existing agenda-group focus (program->agenda_focus), ActivateAgendaGroup action (A8), persistent agenda.

- [ ] Step 1: focus STACK: `ActivateAgendaGroup("g")` pushes the current focus and switches; when the focus group's activations are exhausted, the previous focus pops back (upstream AdvancedAgenda semantics). Document interaction with the static pre-set focus.
- [ ] Step 2: `auto-focus` rule attribute (GRL: `auto-focus true|false` following the existing attribute idiom): when a rule WITH auto-focus and an agenda-group fires, its group becomes the focus automatically. (Upstream: auto_focus switches focus on activation-add; local mapping: on activation push — pick push-time to mirror upstream, document.)
- [ ] Step 3: tests: push/pop sequence across two groups; exhaustion pops back; auto-focus switches; interaction with persistent agenda; parse/validate errors (auto-focus on a group-less rule → parse error? upstream allows it — decide: allow, no-op, document).
- [ ] Step 4: full suite + ASan.

## Task B5: docs + phase commit + push

- [ ] Step 1: conformance.yml: rework `rete-ul-tms-persistent-agenda` and `backward-arbitrary-unification-proof-sharing` known_gaps rows → the real delivered state (TMS parity verified_local; unification bounded ?var; proof graph real-shape; agenda focus stack); new rows for the upstream-vapor documentation (RETE-UL mapping note). upstream.yml: rete/tms/backward rows updated with the vapor findings cited (file:line of the upstream sources proving dead code — keep the research honest).
- [ ] Step 2: Design.md/Architecture.md sections; Implementation_Status.md dated entry.
- [ ] Step 3: full gate (clang Debug all-target + ctest -LE graphics; ASan+UBSan; MSVC rule-engine matrix; bench regression; git diff --check).
- [ ] Step 4: selective commit + push (fetch+merge first if the remote moved).
