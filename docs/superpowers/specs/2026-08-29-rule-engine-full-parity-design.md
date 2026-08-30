# Rule Engine Full-Parity Design — 2026-08-29

## Context

`engine/src/rule_engine/` is a C99 re-implementation of upstream
`rust-rule-engine` v1.21.4 (MIT). The 2026-08-28 completion round
(commits through `c13021e`) delivered bounded slices of the deferred areas.
The user has now directed: **all upstream features must be implemented**.
This spec decomposes that into four sub-projects, each with its own plan →
implementation → review → gate → push cycle.

Prior artifacts: `docs/superpowers/specs/2026-08-28-rule-engine-completion-design.md`,
`docs/superpowers/plans/2026-08-28-rule-engine-completion.md`, ledger at
`.superpowers/sdd/2026-08-28-rule-engine-completion/progress.md`.

## Hard rules inherited from the project

- Evidence rule: no conformance row is promoted without implementation +
  executed local test reference.
- Append-only ABI (`struct_size` versioning, enum tail appends, function
  appends). `RE_ABI_VERSION_MINOR` bumps once per sub-project that adds API.
- C99, clang `-Wall -Wextra -Werror -pedantic` clean, MSVC-compilable, CRLF
  per local file convention.
- Never touch the 21 pre-existing dirty non-rule-engine files or `.omo/`.
- Commit per sub-project (selective paths); push after each sub-project's
  gate passes. Full gate = clang/Ninja Debug all-target build + ctest
  `-LE graphics`; ASan + UBSan trees; MSVC rule-engine matrix;
  `rule_engine_bench` regression script; `git diff --check`.
- Upstream semantics are the reference; where upstream behavior was verified
  in the 2026-08-28 research (crate tarball v1.21.4), cite it; where a
  sub-project needs more, its planner fetches the exact upstream sources.

## Sub-project A — GRL / expression surface completion

Goal: every upstream GRL construct parses and evaluates.

1. **General quantifiers**: full `exists`/`forall` forms — parenthesized
   operands, arbitrary inner predicates over fact paths and structured
   arrays (today: only `exists fact <cmp> literal` / bounded forall).
   Negation `not (...)` over any condition (today: prefix NOT on
   comparisons via expression tree only). Keep deterministic evaluation
   order and bounded loops (element caps).
2. **Condition-position method dispatch**: `Fact.method(args)` in `when`
   evaluates the method call against the fact (set/get/reset conventions do
   not apply in conditions — conditions are read-only; dispatch is:
   `getXxx()` → member read; otherwise registered function `Fact.method`
   then `method` with the receiver value prepended... exact semantics to be
   pinned by the sub-project A plan against upstream `evaluate_expression` /
   condition evaluator; documented either way).
3. **Expression built-ins inventory**: upstream `len/length/size`,
   `isEmpty`, `contains`, string ops, coercion rules (int↔double↔string↔bool
   — upstream `types.rs` coercion table) implemented or explicitly bounded
   with the coercion matrix documented in the design docs.
4. **GRL query blocks**: `query "Name" { goal: <expr>; strategy: ...;
   max-depth: N; max-solutions: N; enable-memoization: bool; when: <cond>;
   on-success: {...}; on-failure: {...}; on-missing: {...} }` — parsed into
   program, executed via a new `re_engine_run_queries` (or per-name
   `re_engine_run_query`) API that maps to the Phase-3 backward machine
   (NOT/aggregation/strategies already exist). Compound goals split on
   `&&`/`||` per upstream `GRLQueryExecutor`.
5. **`accumulate(...)` CE**: `when` accumulate over a fact set with
   sum/count/avg/min/max (upstream `evaluate_accumulate`), feeding the
   existing accumulator machinery; result bound for use in the condition.
6. **Full GRL syntax sweep**: the sub-project A plan diffs the local grammar
   against upstream `src/parser/grl.rs` + `docs/core-features/GRL_SYNTAX.md`
   and closes the remaining gaps (or documents any final residual as
   unsupported with a reason).

## Sub-project B — RETE / TMS / unification depth

Goal: the matching core and truth maintenance reach upstream shape.

1. **General incremental RETE**: one shared network per engine-facts pair:
   shared alpha memories across rules (keyed by condition signature), beta
   joins with incremental (per-fact-event) token propagation instead of
   full rebuild, per-rule production nodes feeding the agenda. Replaces the
   per-rule private networks internally; the public
   `re_engine_rete_network` seam keeps working. Existing bounds (≤8
   conditions) are lifted to a documented higher cap with graceful
   linear-evaluator fallback beyond it.
2. **General TMS**: justifications on any derivation depth, multi-producer
   already exists; add retraction of premises through derived-fact chains of
   arbitrary depth, and non-logical overrides (explicit set beats logical)
   with documented precedence.
3. **Arbitrary unification in backward**: goals unifying variables on both
   sides (`X == Y`, `X == Fact.field`, structured patterns), occurs-check
   policy documented (upstream has no occurs check — mirror), shared
   substitution environment across AND/OR branches.
4. **Shared-subgraph producer provenance graph**: evolve the Task-14 result
   cache into a real graph: nodes keyed by (goal, bindingshape), edges =
   derivations, shared across queries, TMS-style invalidation propagation
   through dependents (upstream `ProofGraph` semantics), while keeping the
   existing result-cache behavior as the lookup layer.

## Sub-project C — streaming completion

1. **GRL stream syntax**: `name: Type from stream("s") over window(10 min,
   sliding|tumbling)` (nom grammar upstream; local parser extension),
   session windows in GRL too (upstream lacks it — local extension,
   documented).
2. **Stream patterns**: multi-event patterns with joins across streams and
   watermark support (event-time watermarks driving window closure and
   late-event policy) per upstream `streaming/operators.rs` +
   `watermark.rs`.
3. **StreamAnalytics**: TTL-cached aggregation, `moving_average`,
   `detect_anomalies` (z-score), `calculate_trend`; aggregation kinds
   CountDistinct/StdDev/Percentile appended to the stream aggregate enum.
4. **Stream rule evaluation**: window aggregates injected as facts at rule
   execution (`WindowEventCount`, per-field Sum/Average/Min/Max), matching
   upstream `streaming/engine.rs:341` behavior, over the existing
   single-consumer event feed (no tokio equivalent — the local engine stays
   single-threaded per the documented concurrency contract; the upstream
   channel/RwLock topology is documented as not applicable).

## Sub-project D — ecosystem

1. **Plugin boundary parity**: upstream's built-in plugin suite
   (`src/plugins/`) inventory; local equivalents as registered built-in
   functions where they are pure (string/math/collection helpers); anything
   engine-host-specific documented as out of scope with reasons.
2. **Example coverage**: for each upstream example family in
   `docs/rule_engine_upstream.yml`'s inventory, a C-side smoke demo test
   that exercises the corresponding feature family (not a file-by-file
   port — the repo has no examples tree; coverage is via tests).
3. **Redis runtime verification**: attempt to locate or stand up a Redis
   service (localhost:6379 probe, `redis-server` on PATH, or
   RE_TEST_REDIS_URL). If a service is available: enable
   RULE_ENGINE_ENABLE_REDIS + hiredis, run the roundtrip test, promote the
   conformance row to runtime-verified. If unavailable: the row stays
   compile-verified optional_backend — this is the one allowed exception,
   per the project's "unavailable evidence is not a pass" rule.
4. **all-features documentation**: map upstream's `all-features` cargo
   switch to the local CMake option set (a documented list, since a single
   switch is not meaningful locally).

## Explicitly out of scope (impossible or non-semantics)

- Rust-specific surface (serde traits, `Send`/`Sync` bounds, tokio runtime).
- Upstream doc-site/example binaries as such (covered via tests per D.2).
- Performance parity claims beyond the existing bench thresholds.

## Process per sub-project

1. Sub-project plan written (writing-plans skill), grounded in freshly
   fetched upstream sources for the exact semantics.
2. SDD execution: implementer + reviewer per task, fix rounds, ledger at
   `.superpowers/sdd/2026-08-29-rule-engine-full-parity/progress.md`.
3. Sub-project gate: full gate checklist; commit; push.
4. Docs updated with the same commit (conformance.yml rows promoted only
   with test evidence).
