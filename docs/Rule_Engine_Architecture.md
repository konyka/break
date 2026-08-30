# Rule Engine Architecture

## Status and scope

This document defines the implemented v1 core and tested extension boundary. The public ABI is in
`engine/src/rule_engine/rule_engine.h`, with implementation paths in
`engine/src/rule_engine/allocator.c`, `facts.c`, `parser.c`, and `engine.c`.
The focused executable `engine/tests/test_rule_engine.c` is local evidence for
the implemented core; the manifests separately record upstream evidence and
deferred families.

Implemented now:

- named GRL rules with `when` conditions and parsed `then` assignment metadata;
- literal and fact-reference `then` assignments applied before callback notification;
- flat fact access with exact flat-key precedence for dotted names;
- forward execution;
- a private immutable compiled IR candidate with bounded index tables, copied term
  names, deterministic content IDs, and bounded source-envelope spans. The
  forward evaluator consumes the validated IR; backward evaluation retains
  its compatibility-tree path for the deliberately bounded query seam.
- exact flat-key-first lookup for dotted fact names with a bounded structured-member
  walk for condition reads and action writes; writes never create implicit
  intermediate objects.
- bounded object/array values and nested path lookup through the versioned value API;
- forward string operators `contains`, `startsWith`, `endsWith`, and `matches`, plus `+=` array append actions. The tested bounded `in` slice accepts non-empty literal arrays and structured arrays containing scalar members, compares booleans, strings, and numeric values with typed equality, and caps literal elements at 64; empty literals and malformed/non-array right-hand sides are rejected. This is not full upstream collection semantics.
- bounded then-action method calls `$Fact.method(...)`: set/get/reset/update
  conventions on structured receiver facts with registered-function fallback
  (`Fact.method`, then bare `method`) and explicit `RE_STATUS_NOT_SUPPORTED`
  when unhandled; `$` outside a then method call is a parse error;
- a local deffacts GRL extension: top-level named `deffacts "name" { Path = literal; }`
  sets parsed atomically with the program and asserted as plain non-logical
  facts via `re_engine_load_deffacts` / `re_engine_reset_with_deffacts`
  (clear-all then reseed);
- instantiate-to-text rule templates: `{{identifier}}` byte substitution with
  per-param defaults emitting `rule "..." [salience N] {when/then}` source
  that the host parses via `re_program_load`; no JSON round-trip and no
  engine-side template registry.
- the completed GRL/expression surface (sub-project A, 2026-08-29): word
  operator aliases, case-insensitive bool/null literals, `%` modulo, string
  `+` concatenation, D4 comparison alignment (strict typed equality,
  `to_number` relational coercion), general parenthesized
  `!(...)`/`exists(...)`/`forall(...)` quantifiers over prefix-heuristic
  candidates, the condition and utility built-in families (registry fallback
  in `builtins.c`), multifield array-shape predicates, the
  `accumulate(Type(...), func(...))` CE with result injection,
  `test(f(...))` and the `$x: Type(conds)` typed form, whitelisted action
  built-ins (`retract`/`log`/`ActivateAgendaGroup` plus the D5 workflow-trio
  registered dispatch), and GRL `query "Name" { ... }` blocks executed by
  `query_exec.c` through `re_engine_run_query`/`re_engine_run_queries`;
  bounds and divergences are enumerated in `docs/Rule_Engine_Design.md`
  ("GRL surface parity").
- the sub-project B depth parity slice (2026-08-29): TMS parity at the
  upstream `tms.rs`/`tms_test.rs` test slice (explicit support coexisting
  with logical justifications via a premise-less marker justification,
  multi-justification survival, cascade/diamond retraction, no
  re-derivation), the shared proof graph upgraded to real node/premise shape
  (bounded 32-entry premise capture with typed value fingerprints,
  generation fast path plus per-premise revalidation, opaque fallback on
  untracked reads, lazy dependent propagation,
  `re_engine_proof_graph_stats_v2`), bounded `?var` unification in backward
  goals and `goal("Rule", ...)` actuals per the upstream case table
  (sticky-consistent, no occurs check, no deferral, one-directional
  aliases), and the agenda focus stack with the `auto-focus` attribute
  (push on ActivateAgendaGroup, pop on focus-group exhaustion, bounded 32);
  bounds and ratified divergences are enumerated in
  `docs/Rule_Engine_Design.md` ("RETE/TMS/unification depth parity").
- explicit null/unknown values and generation-safe fact lifecycle notifications.
- a bounded fact-store truth-maintenance slice at upstream test-slice parity
  (sub-project B): explicit and logical facts, copied producer names,
  generation-safe premise IDs, duplicate-coalesced justifications, and
  cascading retraction after final support removal; explicit support
  (recorded as a premise-less marker justification) is unconditionally valid
  and coexists with logical justifications on the same fact, matching
  upstream `tms.rs`/`tms_test.rs` semantics including multi-justification
  survival, diamond cascades, and no re-derivation on a new justification.
  This slice is transactional and capped by the existing fact/allocator
  limits; it is `bounded_behavior` (insertion-time cycle rejection is
  stricter than upstream), not a general RETE producer-inference network.
- a recognize-act agenda cycle with bounded persistence: per-run refraction on
  (rule, premise slots, value fingerprints), pop-time revalidation of pending
  activations, one private RETE network per eligible rule (up to eight ANDed
  fact-vs-literal comparisons, no cross-rule alpha sharing) with a
  read-set-keyed linear fallback, an opt-in persistent agenda surviving
  OK/LIMIT/CANCELLED exits until program install, and bounded inspection via
  `re_agenda_count`/`re_agenda_peek`; `re_limits_t` gains
  `max_activations_tracked` (zero selects the 1024 default) under ABI minor 3.
- a bounded, non-capability-bearing query seam for exact flat goals and
  recursive rule bodies with literal/propagated formal binding, nested goal
  operands, and registered custom-function operands, extended in Phase 3 with
  query-level `NOT` negation-as-failure (closed-world, no stratification,
  LIMIT propagated never inverted), bounded query aggregation
  (COUNT/SUM/AVERAGE/MIN/MAX/FIRST/LAST folded over an internal bounded query
  at max_depth 64 / max_solutions 1024), per-query search strategies
  (BREADTH_FIRST and ITERATIVE share an iterative-deepening wrapper over the
  DFS machine), bounded `?var` unification per the upstream case table
  (sticky-consistent, no occurs check, no deferral, one-directional
  aliases), and a bounded engine-owned shared proof graph caching final
  query results (64 entries, clear-all eviction, real node/premise shape
  with per-premise revalidation over a generation fast path, deep-cloned
  served proofs); arbitrary predicate unification and
  shared-subgraph/upstream proof provenance remain pending. The
  bounded binding slice stores each successful derivation path as owned nodes
   and deterministic parent/child edges. These edges describe the active
   goal-call stack for that derivation, such as `Top -> A` or `Top -> B`;
   they are not general producer provenance and are not shared between proofs.
- backward condition evaluation uses heap-backed continuation frames for
  TRUE/FALSE, COMPARE, NOT, AND, and OR nodes. Checked frame growth and enclosing
  environment/trace checkpoints preserve failed-branch rollback. Goal and custom
  function operand evaluation still uses the existing operand path and may
  re-enter goal proving; operand continuation migration is deferred.
- extended stream aggregation over retained, type/key-filtered window events:
  count/sum/average plus the appended min/max/first/last kinds under
  struct_size-gated result fields, with window-owned first/last borrows and
  `RE_STATUS_NOT_FOUND` on an empty filtered set for the four new kinds;
- an optional native Redis state-provider adapter compiled into
  `rule_engine_core` only when `RULE_ENGINE_ENABLE_REDIS` is ON and CMake
  discovers hiredis, with the Redis kind otherwise unchanged at
  `RE_STATUS_NOT_SUPPORTED` and no silent fallback;
- a header-documented threading contract (above `re_engine_create`):
  single-threaded engine/facts/window/provider handles, conflicting mutation
  during a run returns `RE_STATUS_BUSY`, action-callback fact writes stage into
  the firing's transaction, allocator callbacks must not re-enter any
  rule-engine API on an in-flight handle, and the C11 executor evaluates
  read-only conditions in private workers.

Deferred explicitly:

- cross-rule RETE/RETE-UL execution and general multi-rule producer
  inference - upstream's own cross-rule machinery is vapor (no shared
  alpha/beta state in any execution path, dead Unifier integration, dead
  integrated proof caching, stub parallel actions), documented in
  `docs/Rule_Engine_Design.md` and not replicated per the evidence rule;
- arbitrary predicate unification (structured terms, occurs check,
  union-find) and the upstream shared-subgraph proof provenance graph;
  bounded recursive binding, nested goal operands, custom function operands,
  derivation-path enumeration, query-level negation, bounded query
  aggregation, strategy selection, bounded `?var` unification, and the
  real-shape shared proof graph result cache are implemented and remain
  deliberately narrower than upstream semantics;
- general stream patterns, joins, and watermarks. Redis-backed streaming state
  is an optional backend with a native adapter (compiled only with
  `RULE_ENGINE_ENABLE_REDIS` plus discovered hiredis, `RE_STATUS_NOT_SUPPORTED`
  otherwise); the portable bounded in-memory provider is implemented;

The bounded agenda-control subset enforces `MAIN`/named program focus,
activation-group sibling cancellation, and the tested one-run `no-loop` and
`lock-on-active` guards. Rule metadata remains immutable and callback pointers
and contexts are never retained. `re_engine_run` executes a recognize-act
cycle: recompute visible rules, push refraction-deduped activations, pop the
highest-salience pending entry, and fire it until the agenda empties, a limit
is reached, or cancellation is requested. Pop-time revalidation discards stale
activations without consuming the fired budget. The agenda focus is a
bounded stack (32): ActivateAgendaGroup pushes the current focus and
switches, exhaustion of the focus group pops the previous focus back, and
the `auto-focus` rule attribute switches focus when an activation push is
genuinely new; the NULL no-focus state is never stacked (documented
divergence from upstream's MAIN-return). Focus cycles and general TMS
producer inference remain pending. Every eligible rule gets a private RETE network (up to
eight fact-vs-literal comparisons joined by conjunction) chained on the facts
store without cross-rule alpha sharing; networks retain alpha/beta/token
memories across runs and incrementally refresh affected condition memories on
lifecycle events. Conditions outside the comparison slice use the linear
evaluator and produce zero-token activations keyed by the condition read-set.
The opt-in persistent agenda (`re_engine_set_agenda_persistent`) keeps pending
activations and fired refraction keys across OK, LIMIT, and CANCELLED exits
until the next program install resets them; `re_agenda_count` and
`re_agenda_peek` inspect pending entries in pop order with true premise ids.

The private advanced test seam covers accumulator value behavior, bounded module
declarations/imports/exports with cycle rejection and focused visibility, and
injected-clock ownership. Module behavior is intentionally private and bounded;
it does not advertise a public module ABI, complete date parsing, or agenda/RETE
support.

The local status is limited to behavior covered by the registered rule-engine
tests, including `engine/tests/test_rule_engine.c`, the transaction, TMS, RETE,
agenda, backward, machine-structure, machine-context, binding, grl-semantics,
grl-surface, query-blocks, fuzz-smoke, and
optional executor-stress targets; these statuses match
`docs/rule_engine_conformance.yml`. `docs/rule_engine_upstream.yml` records
upstream evidence only. No deferred family has an ABI placeholder.

## Module boundaries

Plain-text dependency diagram:

```
caller/application
        |
        v
rule_engine.h ABI
        |
        +--> loader/parser --> immutable candidate program
        |
        +--> fact store --> typed values and copied fact names
        |
         +--> matcher/activation scan --> required forward execution
        |
         +--> action boundary --> caller callback notification
        |
        +--> allocator/error/limit boundary
```

The rule engine may depend on C99 standard headers and its private parser,
fact, matcher, and agenda modules. It must not depend on RHI, renderer, ECS,
Lua, UI, filesystem, or platform window APIs. File and network loading are
caller responsibilities: callers read bytes and pass a bounded source slice to
`re_program_load`.

`re_engine_capabilities` reports only capabilities implemented by the local
engine: core GRL, facts, and forward execution. `re_engine_capabilities_v2` and
`re_engine_extension_info` are versioned discovery seams. Their extension IDs
and capability bits are append-only; a present bit means the backend is enabled,
not merely that the header has a declaration. The extension declarations below
are versioned seams. Implemented extensions are advertised by the v2 capability
mask; unsupported operations return `RE_STATUS_NOT_SUPPORTED`.

The extension families are: custom functions; structured values; fact lifecycle;
agenda/RETE; backward queries/proofs; streaming windows; state providers (with
Redis as an optional backend); and optional concurrency. C11 threading types,
worker ownership, and scheduling remain private to a backend.

### Streaming and state contract

The header reserves independent version `1` contracts for streaming windows and
state providers. `re_event_timestamp_ms_t` is an explicit unsigned 64-bit
millisecond timestamp; it is event time supplied by the caller, not wall-clock
time sampled by the engine. Window kinds are tumbling, sliding, and session.
Options carry retention duration, event and byte limits, allowed lateness, and a
late-event policy (`drop`, `accept`, or `error`). A zero limit is not defined by
this foundation and must be rejected or assigned by a future versioned
implementation rather than guessed by callers.

Window event names and values are copied during a successful record call. No
caller buffer is retained. The local runtime verifies half-open tumbling
buckets of `retention_ms`, session extension until `retention_ms` after the
latest event, event-time late policies, and event/byte bounds. Empty windows
are snapshot-able and restore preserves deterministic opaque bytes. Sliding
behavior remains covered by focused window, aggregate, correlation, and snapshot
tests; Redis is an optional backend whose native adapter compiles only with
discovered hiredis and stays `RE_STATUS_NOT_SUPPORTED` otherwise.
The separate tested correlation seam filters retained events by type and
string-valued key, counts first/second pairs within a timeout, and computes
count, numeric sum, numeric average, minimum, and maximum, and selects the
first/last matching event by timestamp, without changing retention.

Snapshots are caller-owned output bytes until the matching `release` callback;
the callback receives the exact pointer and size and is called at most once.
Restore borrows the supplied bytes for the duration of the call and never takes
ownership. A snapshot has an explicit format version and is opaque bytes; the
format is not JSON, host structs, or a portable serialization until a future
format specification says so. A provider must reject an unknown format version
without modifying state.

State providers are opaque and return direct `re_status_t` results. The portable
provider is deterministic, in-memory, bounded by configured key/value limits,
and uses an injected clock for TTL tests. Its snapshot format is versioned and
deterministic; restore stages all entries before replacing existing state. A backend
may classify an operational failure as unavailable, timeout, serialization, or
conflict through the provider-error contract; the engine must not silently fall
back to local state. Redis is an optional provider boundary only: this ABI does
not include a Redis client, connection type, network API, retry policy, or
claim that native Redis support is enabled. The native adapter
(`redis_provider.c`) compiles into `rule_engine_core` only when
`RULE_ENGINE_ENABLE_REDIS` is ON and CMake discovers a hiredis header/library
(defining `RE_HAS_HIREDIS`); a missing client force-disables the option with a
STATUS message and no silent fallback, and without the macro the Redis kind
remains an explicit `RE_STATUS_NOT_SUPPORTED` boundary. The adapter connects
through the `RE_REDIS_URL` environment variable (default
`redis://127.0.0.1:6379`) with the fixed key prefix `re`, stores raw-byte
values under `<prefix>:<name>` keys via PSETEX/SET/GET/DEL/PTTL, and reports
failures as `RE_PROVIDER_ERROR_UNAVAILABLE` through `last_error`. Runtime
enablement additionally requires a separately supplied controlled Redis
integration endpoint; absent either prerequisite, configuration must keep the
adapter disabled, and on the current host the adapter is compile-verified only.
Redis failures must propagate as provider errors and must
never fall back to empty or in-memory state.

## Lifetime and ownership

- `re_engine_t`, `re_facts_t`, and `re_program_t` are opaque, single-owner
  handles. Each create/load operation returns ownership to the caller.
- `re_engine_install` consumes a successfully installed program. After a
  successful call the engine owns it; callers must not destroy or reuse it.
  On failure ownership stays with the caller.
- A network created by `re_rete_network_create*` is caller-owned and is never
  adopted by an engine. A network created internally for engine execution is
  engine-owned and is released with the engine. A facts store owns the network
  subscription while attached; destroying the store detaches caller-owned
  networks and clears their indexed state without freeing the network handle.
- `re_engine_destroy`, `re_facts_destroy`, and `re_program_destroy` release all
  owned allocations and accept `NULL`.
- Fact names, source bytes, and string values are copied at the call boundary.
  Input pointers may be released after the call returns.
- `re_facts_get` returns a value whose string slice is borrowed from `facts`.
  It is invalid after the next fact mutation or facts destruction.
- Callback pointers and callback context are borrowed only during
  `re_engine_run`; the engine does not retain them.
- Extension descriptors are copied at registration. Names and immediate value
  inputs are copied; descriptor contexts remain owned by the caller until the
  matching unregister/destroy callback. A release callback runs once, after no
  invocation can remain. Callback pointers and contexts must remain valid until
  that release point.
- Opaque extension handles have single-owner lifetimes. Returned values,
  subscriptions, proof handles, agenda/RETE views, windows, providers, and
  executors are borrowed or owned exactly as stated by their future extension
  contract; NULL destruction is safe. Destroying a subscription ends callback
  delivery before releasing its context. No placeholder function retains caller
  output storage.
- A created window or provider is owned by the caller and must be destroyed
  exactly once. Versioned option and descriptor inputs are borrowed for the
  call; provider context ownership follows its release callback.
- Snapshot output is owned by the caller only through its release callback;
  snapshot bytes are immutable while borrowed by the caller. Restore input is
  borrowed and is not retained.
- Engine and facts handles are busy during a run. Installation returns
  `RE_STATUS_BUSY`; destruction requested by a callback is deferred until the
  run unwinds. Callbacks must not retain or use a handle after returning.

## Transactional loading

`re_program_load` parses a candidate without changing an engine. A parse,
allocation, or limit failure destroys no installed program. `re_engine_install`
is the commit point: the replacement becomes visible atomically to subsequent
runs, and the prior program remains valid until the engine commits the new
candidate. A failed install leaves both handles unchanged.

## Execution model

The forward runtime runs a recognize-act cycle over the immutable program: each
pass recomputes visible rules, pushes refraction-deduped activations, and fires
the highest-salience pending activation with source order as the stable
tie-breaker, until the agenda empties, a limit is reached, or cancellation is
requested. Every eligible rule retains a private incremental per-rule RETE
network across runs and fact lifecycle events; conditions outside the bounded
comparison slice use the linear evaluator with read-set-keyed activations.

## Bounded RETE milestone

`engine/src/rule_engine/rete.c` contains a bounded runtime seam for ANDed
fact-vs-literal comparisons over flat facts, capped at eight conditions per
rule. It subscribes to generation-safe insert/update/retract events, retains
alpha memories and beta token pairs across runs, stores fact-id lineage plus
optional rule-name provenance, and removes stale records after lifecycle
changes. A run installs one private network per eligible rule, chained on the
facts store without cross-rule alpha sharing, and reuses it for the same fact
handle. An activation's lineage is the premise set used when its firing creates
a new logical fact; the recognize-act loop revalidates each pending activation
at pop time before firing it. The implementation is not full RETE-UL: it has
no truth maintenance or general condition graph. Agenda groups, streaming,
backward chaining, concurrency, and all other RETE features remain outside
this milestone.

### Bounded truth maintenance milestone

`engine/src/rule_engine/tms.c` owns a private justification table attached to
the fact store. `re_facts_insert_logical` records one copied producer-rule
name and a bounded, generation-safe premise set. Justifications are
deterministically stored, duplicate records coalesce, and a logical fact is
retracted only after its final justification is removed. Retraction removes
dependent justifications and propagates through dependent logical facts.
Transactions clone and swap this metadata with the fact table, so rollback
does not alter live TMS state. A RETE-backed action derives a new target as a
logical fact and records the activation's fact IDs; an existing explicit target
remains explicit. Stale premise IDs and self-cycles are rejected.
The ABI exposes inspection and mutation helpers for this tested slice only.
Sub-project B closed the explicit/logical coexistence delta against upstream
`tms.rs`: explicit host assertions record a premise-less explicit-support
marker, both supports coexist on one fact, and cascade guards retract only
at zero total support - the twelve upstream TMS test semantics are ported in
`test_rule_engine_tms.c`. General multi-rule RETE producer inference and
arbitrary unification remain unsupported.

Outside the opt-in persistent agenda mode, a run owns its activation list. Each
fired activation executes all parsed action
  assignments and its callback in one fact transaction; changes become visible only
  after action processing succeeds, then fact notifications are emitted from the
  committed state. If a notification callback returns an error, the commit remains
  committed and no compensating rollback event is emitted. The RETE
network is invalidated so its derived state is rebuilt before subsequent use.
Cancellation and limit exhaustion roll back the in-flight activation and stop
the run with the corresponding status. Salience ordering
is locally verified; agenda groups and general multi-rule producer-provenance
inference remain unsupported. The optional C11
backend evaluates only pure read-only conditions in private workers, merges
matches using existing salience/source ordering, and applies actions and
callbacks serially. It is disabled unless `RULE_ENGINE_ENABLE_C11_PARALLEL` is
enabled; mutating operations return `RE_STATUS_BUSY` during worker matching.

## Allocator and errors

The allocator is optional; `NULL` selects the engine default. Every allocation
and release associated with a handle uses the allocator selected when that
handle was created. An allocator must remain alive until its handle is
destroyed and must return `NULL` on failure without terminating the process.

All public fallible functions return `re_status_t` or a nullable handle.
`RE_STATUS_OK` is zero; negative values are errors. `RE_STATUS_PARSE_ERROR`,
`RE_STATUS_LIMIT`, and `RE_STATUS_CANCELLED` are observable control-flow
outcomes, not logging-only conditions. The ABI has no global last-error string;
diagnostic text is deferred until a tested diagnostic API is needed.

## Limits, cancellation, and callbacks

Limits supplied at engine/facts/program creation are copied; run-option limits
are borrowed for the duration of `re_engine_run`. All limits are optional. A
zero run-option field selects the corresponding engine default; zero in the
engine default means no limit. A non-zero `max_agenda_activations` allows exactly
that many matching activations, and a non-zero `max_firings` allows exactly that
many executed rules. The activation limit is reported before the next matching
activation, while reaching the firing limit returns `RE_STATUS_LIMIT` after that
allowed assignment and callback complete.
The implementation must check source bytes, rules, facts, agenda activations, and
firings at their respective boundaries. Cancellation is polled at bounded execution points;
the callback returns non-zero to request cancellation. A callback is not
invoked after cancellation or a terminal limit error.

## Thread safety and ABI rules

Handles are not concurrently mutable. A caller may use independent handles on
different threads, but must externally synchronize every operation involving
the same engine or facts handle. Callbacks execute on the calling thread.
There is no implicit global lock, thread-local error state, or background
worker in this contract. The header documents the full threading contract
above `re_engine_create`, and the busy semantics are test-locked: engine,
facts, windows, and providers are single-threaded handles; while
`re_engine_run` is active, re-entering the run, opening a user transaction, or
resetting working memory returns `RE_STATUS_BUSY` (the existing
running/notifying/transaction flags cover these vectors, so no new guards were
needed); fact writes from an action callback stage into the firing's
transaction and commit with it rather than being rejected; allocator callbacks
must not re-enter any rule-engine API on a handle involved in the in-flight
operation; and the optional C11 executor evaluates only read-only conditions
in private workers, merging matches back on the engine thread for serial
actions and callbacks.

Extension limits are inherited from `re_limits_t` and may only add bounded
fields through a later versioned options struct. Implementations must reject
unknown required versions with `RE_STATUS_NOT_SUPPORTED`, reject undersized
structs with `RE_STATUS_INVALID_ARGUMENT`, and never read beyond `struct_size`.
Errors remain direct `re_status_t` results: unsupported backend, unavailable
optional provider, limit exhaustion, cancellation, busy/reentrant use, and
invalid ownership are distinct observable outcomes where applicable.

The header uses only C99 facilities: fixed-width integers, `size_t`, named
unions, opaque pointers, and function pointers. It intentionally avoids
anonymous unions, `_Static_assert`, atomics, variadic public APIs, and C11
threading types.
# Backward query execution paths

The explicit goal frame machine handles zero-argument goal queries whose
selected rules have one of these conditions:

- `true`
- a zero-argument `goal("RuleName")` transition

It uses checked heap frames for rule selection and return transitions, and
preserves the query depth, cycle, trace, and maximum-solution limits for this
subset. The production query entry point selects this path when the goal graph
matches the supported shape; otherwise it uses the bounded compatibility path
in `backward.c`, which also covers direct fact comparisons such as
`Ready == true`, supported boolean composition, literal/propagated formal
bindings, nested goal operands, and registered custom-function operands. The
compatibility path still rejects arbitrary predicate unification and shared
proof subgraphs. It likewise rejects the sub-project A condition forms it
cannot evaluate honestly - nested parenthesized quantifiers, multifield
predicates, accumulate, `test()`, and the typed form report
`RE_STATUS_NOT_SUPPORTED` rather than proving through the legacy operand
comparison, and backward chaining does not consult the built-in function
families. Neither path claims
arbitrary upstream unification or shared-subgraph provenance.

Above both paths, `re_backward_machine_dispatch` owns query argument and
option normalization (including the `re_query_options_t` `struct_size`
versioning for the appended `strategy` and `disable_shared_proof_graph`
fields), the leading-`NOT` negation-as-failure inversion, strategy selection,
and the shared proof graph consult/store. The NOT subgoal re-enters the
dispatcher with the caller's normalized options and `max_solutions` 1, so the
inversion always applies to the strategy-selected result and a cached entry
holds the final negation-resolved result for its exact goal text.
`RE_QUERY_STRATEGY_BREADTH_FIRST` and `RE_QUERY_STRATEGY_ITERATIVE` run one
capped DFS pass per probe with doubling depth caps (1, 2, 4, ... up to the
configured maximum; first cap with at least one solution wins; more than 32
doublings reports `RE_STATUS_LIMIT`). The shared proof graph
(`proof_graph.c`) is a lazily created engine-owned 64-entry cache of final
PROVED/DISPROVED results, consulted after normalization and keyed on the exact
goal text, facts identity, normalized options, and `config_serial`, stamped
with the facts `mutation_serial`; served proofs are deep clones with their own
invalidation subscription, a full table clears every entry (counted as
evictions), and `re_engine_proof_graph_stats` exposes hits/misses while the
appended `re_engine_proof_graph_stats_v2` adds invalidations, stores, and
evictions. Each store records an informational node per proof plus the
producing run's bounded premise set (32 entries, typed value fingerprints,
absent reads recorded); a serial mismatch on lookup revalidates
premise-by-premise, so an entry survives mutations its premises did not
observe, and untracked influences flip the capture opaque back to the coarse
generation check. `re_engine_query_aggregate`
lives in `backward.c` but only composes the public query API: an internal
bounded query (max_depth 64, max_solutions 1024, DFS) whose named binding is
folded over the solutions.
