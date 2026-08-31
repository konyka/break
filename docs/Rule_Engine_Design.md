# Rule Engine ABI Design

## Design goals

The ABI is deliberately smaller than the upstream Rust feature set. It gives
the implemented C99 core stable seams for required GRL behavior without
pretending that deferred upstream families exist locally.

The contract has four implemented objects: an engine, facts, a parsed program
candidate, and typed values. Versioned extension seams add opaque handles for
custom functions, structured values and fact lifecycle, agenda/RETE, backward
queries/proofs, streaming windows, state providers, and optional concurrency.
They do not expose parser nodes, RETE nodes, rule structs, stream records, proof
graphs, C11 threading objects, or backend-specific layouts.

## Public types

`re_engine_t`, `re_facts_t`, and `re_program_t` are opaque. Their layout is
private and may change without changing the ABI. `re_value_t` is a by-value
tagged value. `RE_VALUE_STRING` is a byte slice and is not required to be
NUL-terminated; callers provide a length. Boolean values use zero/non-zero
semantics on input and are returned as zero or one.

The initial value set is `none`, boolean, signed 64-bit integer, double, and
string. There is no pointer-valued fact type, implicit numeric coercion, or
user-defined value destructor. Those additions require a tested ABI extension.

`re_engine_capabilities` returns a bit mask for the local implementation. It is
an honest discovery mechanism, not a declaration of upstream parity; deferred
families have no bits in the base mask. `re_engine_capabilities_v2` and
`re_engine_extension_info` negotiate an ABI major/minor and extension version.
Extension IDs, capability bits, existing enum values, and existing struct field
order are append-only. A declaration in the header is not an implementation;
until a bit is reported, callers must treat that family as unsupported.

The forward `in` operator is a bounded local slice: the right-hand side may be
an array literal with 1-64 scalar elements or a structured array containing scalar members. Comparisons
use typed scalar equality, including exact `int64` equality; empty literals and
non-array/malformed right-hand sides are rejected by the parser. This does not
claim full upstream collection semantics; bounded property access and
then-action method calls are documented below.

## Function contract table

| Function | Caller owns | Engine/API owns | Failure and output rules |
|---|---|---|---|
| `re_engine_create` | allocator and input limits | returned engine | `NULL` on invalid allocator or OOM |
| `re_engine_destroy` | handle until call | all engine-owned program state | NULL-safe, no return status |
| `re_facts_create` | allocator and input limits | returned facts | `NULL` on invalid allocator or OOM |
| `re_facts_destroy` | handle until call | copied names and values | NULL-safe, no return status |
| `re_facts_set` | name/value memory after return | copied name/value | returns invalid argument, limit, or OOM without partial update |

RETE network ownership is exclusive per facts store. Creating a second network
while the store already has an attached network returns `RE_STATUS_BUSY`; the
existing network and every previously returned handle remain valid until the
caller destroys that network. Networks created through the public RETE creation
functions are caller-owned and are never adopted by an engine. An engine-created
network is engine-owned and is destroyed with the engine. Destroying the facts
store detaches a caller-owned network, including its subscription and indexed
fact memories, but does not free the network object; the caller must destroy it.
The engine uses RETE for incremental provenance and enumerates available bounded
activations for the matching rule; the IR result remains the match guard when an
exact token cannot be selected. Linear matching records a bounded condition
read-set (up to eight deduped fact paths, silent overflow) on TERM_FACT, EXISTS,
and FORALL hits - never on action right-hand sides or during backward
evaluation - and a linear derivation's premise set is the RETE lineage union the
read-set fact ids, capped at eight. Linear-path derivations go through
`re_facts_insert_logical`/`re_facts_justification_add` exactly like RETE-backed
ones. A dotted action target with a structured root writes the nested member
with its justification anchored on the root fact id, so TMS cascade retraction
removes the root (a documented bound), and a transitive premise cycle through a
dotted target surfaces `RE_STATUS_LIMIT` from the TMS dependency check.
| `re_facts_get` | output storage | returned string slice temporarily | returns not found or invalid argument; no allocation |
| `re_program_load` | source memory after return | candidate on success | output is unchanged on failure; candidate is caller-owned until install |
| `re_program_destroy` | candidate until call | candidate allocations | NULL-safe, no return status |
| `re_engine_install` | candidate until success | candidate after success | failed install preserves both handles |
| `re_engine_run` | facts, options, callback context | no callback/context retention | returns status; no background work or retained output |
| `re_engine_register_function` | descriptor memory after return; context until unregister | copied name and registration handle | transactional registration; callback/release lifetime is explicit |
| `re_engine_query` / `re_query_next` | goal input after call | query and proof handles | bounded, pull-based proof iteration; unsupported until capability is advertised |
| `re_engine_query_aggregate` | pattern and field inputs after call | output value (no string storage retained) | internal bounded query (max_depth 64, max_solutions 1024); cap or depth exhaustion reports `RE_STATUS_LIMIT` |
| `re_engine_proof_graph_stats` | engine handle | hit/miss counters | zeroes before the first cached query; NULL engine or counter is invalid argument |
| `re_stream_window_create_v1` / `re_stream_window_record_v1` | options and event name/value during call | window handle and copied event data | explicit u64 event timestamp; limits and late-event policy are part of options; tested bounded runtime |
| `re_stream_window_snapshot` / `re_stream_window_restore` | restore bytes during call; snapshot bytes through release callback | snapshot output until release; restored window state | opaque versioned bytes; no mutation on unsupported format |
| `re_engine_set_state_provider_v1` | options and descriptor during call; provider context until release/destroy | provider handle | callback or optional Redis boundary; provider failures are returned directly |
| `re_engine_executor_create` | options during call | executor handle | optional C11 backend; unsupported unless enabled |

Every function that can fail reports it directly. Destructors do not report
failure because release is unconditional and allocator release has no error
channel.

## Transaction and reentrancy rules

Fact transactions are explicit, single-owner overlays. `re_facts_begin` deep-copies
the current fact table and returns `RE_STATUS_BUSY` when another transaction is
active. Transaction mutations are isolated until `re_facts_commit`; commit swaps
the staged table before dispatching deterministic insert/update/retract events.
Direct insertion of an existing active name is an update and emits only one
`RE_FACT_UPDATE` event; insertion of a new name emits one `RE_FACT_INSERT`.
`re_facts_rollback` discards the staged table and dispatches no events. A
notification callback observes committed state; if it fails, the commit remains
committed, no compensating rollback event is emitted, and the RETE network is
invalidated for rebuild. Failed
begin operations return `RE_STATUS_OUT_OF_MEMORY` without changing live facts.

Loading and installation are separate so a caller can parse and validate a
candidate before replacing live rules. `re_engine_run` must not be called
recursively for the same engine or facts handle from an action callback; this
returns `RE_STATUS_BUSY`. `re_engine_install` also returns `RE_STATUS_BUSY`
during a run. Destruction requested by a callback is deferred until the run
returns. A callback may update facts, but must not retain either handle after
returning.

## Implemented test seams

The current focused tests establish:

1. C99 public-header usability via the `rule_engine_c99_consumer` object target.
2. Fact copy semantics and exact flat-key lookup for dotted names.
3. Candidate load failure preserving an installed program.
4. Successful install, literal and fact-reference action assignment, and
   deterministic descending-salience callback notification with source-order
   tie breaking after each assignment.
5. Callback delivery and fact mutation, cancellation, and execution limits,
   including busy and deferred-destruction behavior. Zero per-run limit fields
   select the corresponding engine defaults; a zero engine default is unlimited.
6. Capability reporting that excludes deferred features.
7. The bounded agenda-control slice: explicit `MAIN`/named focus selection,
   activation-group sibling cancellation, deterministic salience/source
   ordering, and bounded one-run enforcement of `no-loop` and
   `lock-on-active`. `re_engine_run` executes a recognize-act cycle: each
   pass recomputes the visible rules, pushes refraction-deduped activations,
   and fires the highest-salience pending activation until the agenda is
   empty, a limit is reached, or cancellation is requested. Refraction keys
   combine the rule, premise slots, and value fingerprints; pop-time
   revalidation discards stale activations without consuming the fired
   budget. Every eligible rule (up to eight ANDed fact-vs-literal
   comparisons) gets a private per-rule RETE network chained on the facts
   store; conditions the alpha memories cannot see fall back to zero-token
   activations keyed by the condition read-set. The engine-owned agenda is
   created lazily by `re_engine_agenda` (a non-const call);
   `re_engine_set_agenda_persistent` keeps pending activations and fired
   refraction keys across OK, LIMIT, and CANCELLED run exits until a program
   install resets the agenda; and `re_agenda_count`/`re_agenda_peek` expose
   pending entries in salience-descending, sequence-ascending order with true
   premise ids. These entry points ship under ABI minor 3
   (`RE_ABI_VERSION_MINOR 3u`); `RE_CAP2_AGENDA_RETE` is advertised while
   networks are attached, and `re_agenda_destroy` is a documented no-op for
   the engine-owned instance.

Refraction bounds are deliberate. Value fingerprints hash premise content
with FNV-1a; a collision can theoretically miss a refire, doubles hash their
raw bits, and NULL/UNKNOWN/NONE/structured values mix only the type tag, so a
member-only change under a structured root does not re-activate a linear
rule. Refraction is timestep-free: an A->B->A value round trip within one run
does not refire because fired keys persist for the run (and across runs in
persistent mode) until a premise value actually changes. A linear
self-rewrite rule such as `when N + 0 > 0 then N = N + 1` now loops until
`max_firings` (default 1024), symmetric with the RETE value-fingerprint
semantics. The executor's parallel-match path captures no read-set, so linear
rules stay once-per-run there, and `RE_COMPARE_IN` fact-operand reads are not
part of the read-set. `re_limits_t` gains `max_activations_tracked` (zero
selects the 1024 default), capping pending plus fired agenda entries;
`re_agenda_peek` is O(n^2) within that bound and its rule_name borrows the
installed program's storage.

Structured-value nested fact access is implemented through the bounded
`re_facts_get_path`/`re_facts_set_path` pair and is covered by focused tests.
Dotted names in rule conditions and actions resolve exact flat-key first;
absent a flat key, reads walk the root fact's structured members and writes
update an existing structured member. Writes never create implicit intermediate
objects or flat keys through the path API (`RE_STATUS_NOT_FOUND`); a rule
then-assignment whose dotted target resolves nowhere falls back to a plain flat
`re_facts_set`. Rule declarations may optionally include `salience <int32>`
after the quoted name; matching activations execute in descending salience
order, with source order preserved for ties. Deferred behavior is not
represented as local verified conformance until implementation and focused
tests exist.

Structured arrays use decimal string member keys generated by a bounded,
allocation-free helper. The helper requires space for the terminating NUL and
fails closed when the destination is too small; append operations reject the
configured 1024-member limit before formatting, so a future limit change cannot
turn an index conversion into a truncation or buffer overwrite.

Run focused behavior evidence with:

```bash
ctest --test-dir <build> -R 'test_rule_engine|test_backward_machine|rule_engine_fuzz_smoke' --output-on-failure
```

Build the standalone ABI consumer with `cmake --build <build> --target
rule_engine_c99_consumer`. The consumer is compile-only and has no graphics or
Lua dependency. `test_backward_machine_structure` is a source-level guard for
the production routing symbols; runtime behavior is covered by the other
focused tests.

See `docs/Rule_Engine_Architecture.md` for module boundaries,
`docs/rule_engine_conformance.yml` for local/upstream status, and
`docs/Rule_Engine_Benchmark.md` for the manual workload.

## Bounded GRL semantics: method calls, deffacts, and rule templates

Rule `then` actions support `$Fact.method(arg, ...)`; the `$` prefix is
required and a `$` anywhere outside a then method call is a parse error.
Execution applies bounded conventions in order: `setXxx(v)` writes property
`Xxx` on the receiver's structured object (structured path write first, member
set-or-create second), `getXxx()` reads it and is the only conventional form
usable as an action RHS operand, `reset()` replaces the receiver with an empty
object, and `update()` is a bounded no-op kept for source parity. Any other
name dispatches to a registered function named `Fact.method`, then bare
`method`; with neither registered the run fails with
`RE_STATUS_NOT_SUPPORTED`. Upstream silently no-ops an unknown method, so the
explicit failure is a deliberate documented divergence. All writes go through
the firing transaction and notify subscribers like ordinary assignments.
Unlike a dotted assignment target, a method-call write records no TMS
justification, so TMS premise retraction does not cascade to the receiver
fact. `when` conditions are unchanged: calls there resolve through registered
functions only.

`deffacts "name" { Path = literal; }` is a local GRL extension; upstream
exposes deffacts only through its Rust API. Sets parse atomically alongside
rules and hold flat fact paths with scalar or array literals; a duplicate set
name in one source is a parse error. `re_engine_load_deffacts` asserts one
named set — or all sets for NULL — as plain non-logical facts, overwriting
duplicates, and returns `RE_STATUS_NOT_FOUND` for an unknown name. Dotted
entries update an existing structured member through `re_facts_set_path` and
otherwise become flat facts; array literals become structured array facts whose
string elements are deep-copied into fact-owned storage — structured members
own their string payloads, so facts seeded from deffacts stay valid after the
program is destroyed. `re_engine_reset_with_deffacts` clears working memory (all
facts, TMS justifications, and the agenda's pending activations and refraction
keys) and then loads every
set. Two bounded reset notes apply. Fact IDs are slot/generation pairs and a
clear restarts generations, so a caller-held `re_fact_id_t` from before a
reset can alias a fresh fact and must be discarded. And a bare clear emits no
per-fact events, so standing queries are not invalidated by it; only the
deffacts reseed's INSERT notifications invalidate them.

Rule templates are an instantiate-to-text API. `re_rule_template_create`
copies the name, condition, and action templates plus salience;
`re_rule_template_param_default` sets per-parameter defaults;
`re_rule_template_instantiate` substitutes `{{identifier}}` placeholders by
plain byte substitution and emits `rule "<rule_name>" [salience N]` when/then
text that the host parses through `re_program_load`. The rule name is emitted
unescaped, text that is not an exact `{{identifier}}` placeholder copies
through unchanged, a placeholder with neither a supplied param nor a default
fails with `RE_STATUS_INVALID_ARGUMENT` (leaving the size output untouched),
and a too-small buffer yields `RE_STATUS_LIMIT` after the required size is
reported. There is deliberately no JSON round-trip, no CLIPS deftemplate
schema validator, and no engine-side template registry.

## GRL surface parity: expressions, quantifiers, built-ins, multifield, accumulate, query blocks, action built-ins

This section records the sub-project A (2026-08-29) completion of the local
GRL/expression surface against upstream rust-rule-engine v1.21.4 (`f80a541`).
Feature coverage is the goal, bug replication is not: where upstream is
degenerate the local engine keeps its saner behavior and the divergence is
documented below. All rows are `verified_local` in
`docs/rule_engine_conformance.yml` with test refs into
`engine/tests/test_rule_engine_grl_surface.c` and
`engine/tests/test_rule_engine_query_blocks.c`.

Expression surface (Task A1). Word operator aliases `eq`/`ne`/`gt`/`gte`/`lt`/
`lte`/`not_contains` parse to the same comparison kinds as the symbolic forms;
`true`/`false`/`null` literals are case-insensitive; `%` is fmod-based modulo
(Integer result iff both operands are Integer and the result is integral);
`+` concatenates strings. The D4 comparison alignment: equality is strictly
typed (`Integer(1) != Number(1.0)`, matching upstream `PartialEq`), while
relational operators coerce through `to_number` — numeric strings coerce, and
bool/null/array/object operands make the comparison false. Documented bounds,
locked by test: string operators against non-string operands make `contains`
false and `not_contains` true; `NONE == NONE` is true (typed equality over the
tag, not three-valued logic); the strtod-based numeric-string coercion accepts
hex float spellings (`"0x1p4"`) that upstream's Rust parser rejects, while
`inf`/`infinity` spellings coerce in both; `%` computes in f64, so Integer
operands beyond 2^53 can round; a leading `true`/`false` literal in a
condition stays the whole-condition form, so bool relational rejection is
observable through fact and RHS-literal positions.

General quantifiers (Task A2). `!( <expr> )`, `exists( <expr> )`, and
`forall( <expr> )` accept arbitrary inner boolean expressions. Candidate
selection follows the upstream fact-name-prefix heuristic (D7): the target
prefix is the text before the first `.` of the leftmost field reference,
candidates are all active facts whose name equals or starts with it, and the
inner expression evaluates per candidate with the prefix rebound; a
per-candidate `NOT_FOUND` absorbs as a non-matching candidate. `forall` over
an empty candidate set is vacuously true (D6); with no dotted field reference
the inner evaluates once against the plain fact store. Quantifier conditions
never join per-rule RETE networks, and backward chaining rejects rules
carrying them with an honest `RE_STATUS_NOT_SUPPORTED`.

Built-ins (Tasks A3/A4). `engine/src/rule_engine/builtins.c` hosts two
families as a registry fallback (a registered user function of the same name
overrides the built-in): the condition family `len`/`length`/`size`,
`isEmpty`/`is_empty`, `contains`, `exists`/`notExists`/`not_exists`, and the
utility family `log`/`print`/`println`, `now`/`timestamp`, deterministic
per-engine `random`, `format`/`sprintf`, `length`/`size`/`count`,
`sum`/`add`/`max`/`min`/`avg`/`average` (INT64-preserving folds),
`round`/`floor`/`ceil`/`abs`, `contains`/`includes`, `startswith`/`endswith`,
`lowercase`/`uppercase`/`trim`, `split`, `join`. Wrong arity/types yield false
for the predicates and the documented error status for the math/string
functions; an unresolvable fact-path argument absorbs to false (true for the
negated probes). Deliberately skipped upstream-only aliases:
`maximum`/`minimum`, `ceiling`, `absolute`, `begins_with`/`ends_with`,
`tolower`/`toupper`, `strip`, `update`/`refresh`. `split` reproduces
upstream's `format!("{:?}")` debug string and escapes only quote, backslash,
`\n`, `\r`, `\t` — other control characters lack Rust-debug `\u{..}` fidelity.
`len`/`length`/`size` return INT64 where upstream returns Number (f64), so
under D4 `len(x) == 4` is true while `len(x) == 4.0` is false.

Multifield ops (Task A5). A fact-path operand followed by `count <cmp>
<numeric-literal>`, `first`, `last`, `empty`, `not_empty`/`notEmpty`, or
`collect` is an array-shape predicate: count is the element count (missing
field 0, present non-array field 1), first/last are non-empty-array predicates
carrying no binding, collect is a presence predicate. The conditions are pure
and re-evaluated, never RETE-eligible, and a resolved path joins the condition
read-set anchored on the root fact. Upstream's GRL parser exposes exactly
these spellings; `index`/`slice` exist only in upstream's RETE multifield
Rust API and are a local parse error. Count equality is strictly typed
(`count == 3.0` does not match an int64 3 — D4) while relational count
comparisons coerce the literal. Flat-vs-structured conflict: presence follows
the flat-key-first read while the array shape comes from the structured read
alone, so a flat scalar shadowing a same-path structured array member still
counts the member's elements.

Accumulate CE (Task A6). `accumulate(Type($var: field, conds...), func(...))`
flat-scans the `Type.<instance>.<field>` keys (a bare `Type.<field>` key is
the default instance), keeps instances whose mini-conditions all hold, folds
the extracted field with `sum`/`count`/`average`/`avg`/`min`/`max`, injects
the result as the fact `Type.func`, and always matches. Documented
divergences: mini-condition equality reuses `re_value_compare` (strict typed
`==`, no double epsilon); the `$var`-less count form counts matching instances
(upstream counts extracted values, 0 there); an unknown function name is a
parse-time error (upstream raises at evaluation); an instance literally named
`default` is not merged with the bare-key default instance. The injection
write makes the node impure, so accumulate rules stay off RETE networks and
evaluate at the first-pass position; the injected fact recomputes from the
current facts on every run that reaches the node (cross-run stability is
test-locked, with and without the optional executor attached), and a
follow-up condition in the same `when` can gate on it.

Query blocks (Task A7). Top-level `query "Name" { goal: ...; strategy: ...;
max-depth: ...; max-solutions: ...; enable-memoization: ...;
enable-optimization: ...; when: ...; on-success: { ... } on-failure: { ... }
on-missing: { ... } }` blocks install with the program and run through
`re_engine_run_query`/`re_engine_run_queries` on the bounded backward machine
(`engine/src/rule_engine/query_exec.c`). The goal text splits textually
(`||` before `&&`, one wrapping paren pair stripped), `!=` subgoals evaluate
directly against working memory, `enable-memoization: false` maps to the
shared-proof-graph disable flag, and `enable-optimization` is an accepted
no-op. Documented divergences: scalar fields are `;`-terminated where
upstream terminates goal/when at the newline; `on-missing` never fires — the
machine tracks no `missing_facts` list, so it folds into `on-failure`; a hard
goal error (anything `re_engine_query_bounded` propagates other than
`RE_STATUS_LIMIT`, e.g. `RE_STATUS_NOT_SUPPORTED` from the nested-quantifier
boundary) propagates without running either action block; duplicate query
names run the first match in source order. Queries never run inside
`re_engine_run`.

Action built-ins (Task A8). Whitelisted bare `name(args)` then-statements:
`retract($Obj)` sets the `_retracted_<root>` flag fact so condition reads on
that root evaluate absent (conditions only; the flag must be exactly BOOL
true; token-live pending activations re-pass the gated match at pop time);
`log(...)` prints through the utility-built-in machinery;
`ActivateAgendaGroup("g")` replaces the agenda focus for the rest of the run;
`ScheduleRule`/`CompleteWorkflow`/`SetWorkflowData` dispatch to a registered
function of the bare action name (D5 — upstream's workflow/scheduler
subsystems do not exist locally), and an unhandled one fails the run with
`RE_STATUS_NOT_SUPPORTED`. Any other bare action call stays a parse error.

`test` CE and typed form (Task A9). `test(f(args))` truthiness-tests a lone
function call result (BOOL as-is, INT64/DOUBLE nonzero, STRING non-empty,
else false) and classifies impure; `$x: Type(conds)` has exists-semantics over
the type prefix's candidates, with `$x` and bare field references rewritten to
candidate-relative `Type`-rooted paths scoped to the form (a `$var` outside
the form stays a parse error). Both stay off RETE networks and are
`RE_STATUS_NOT_SUPPORTED` to backward chaining.

Standing divergences of the whole surface: D1 — compound `&&`/`||` evaluation
short-circuits locally (upstream evaluates both sides; side-effect-free
conditions make them observationally equal); D2 — no receiver-aware condition
method dispatch (a full dotted name resolves a registered function, otherwise
`NOT_SUPPORTED`/false; upstream silently drops the receiver); D3 — `matches`
stays wildcard-substring like upstream's stub. The `exists(` spelling
disambiguates quantifier vs presence-function by scanning for a top-level
comparison/logical operator, so fully parenthesized content
(`exists((A == 1))`) and a lone typed or accumulate form
(`exists($o: Order(amount > 1))`, `exists(accumulate(...))`) read as the
function form and fail to parse — documented bounds.

Syntax sweep (Task A10). The remaining upstream `GRL_SYNTAX.md` constructs are
dispositioned as upstream-absent, locked by
`syntax_sweep_unsupported_constructs_parse_error`: block comments `/* */` are
doc-claimed but not implemented upstream (`grl.rs` `clean_text` strips only
full `//`-prefixed lines inside when-clauses) and the local parser has no
comment syntax at all — both forms are parse errors; the `enabled` rule
attribute is a struct-only field upstream (`rule.rs`) with no GRL form;
object literals `{k: v}` and index syntax `a[0]` appear in the upstream doc's
type and nested-access sections without parser support on either side.

## RETE/TMS/unification depth parity: TMS, proof graph, ?var unification, agenda focus stack

This section records the sub-project B (2026-08-29) closure of the real
deltas against the working deep machinery of upstream rust-rule-engine
v1.21.4 (`f80a541`), plus the upstream-vapor findings the parity scope
deliberately does not replicate. The source-level research behind the vapor
calls is recorded in
`docs/superpowers/specs/2026-08-29-rule-engine-full-parity-design.md`
(Sub-project B). All delivered rows are `verified_local` in
`docs/rule_engine_conformance.yml`.

TMS parity closure (Task B1, upstream `src/rete/tms.rs` +
`tests/tms_test.rs` - the 12 upstream test semantics are all ported).
Explicit support and logical justifications now coexist on one fact: an
explicit host assertion (`re_facts_insert`) over a logically-derived fact
records an explicit-support marker (a premise-less justification item, the
local encoding of upstream `JustificationType::Explicit`, invisible to the
public provenance helpers), and `re_facts_insert_logical` on a host-asserted
fact keeps both supports. Both cascade guards retract a derived fact only
when its total support count reaches zero, so explicit support is
unconditionally valid by construction. Multi-justification facts survive
single-premise retraction, diamond dependencies cascade fully, and a new
justification never re-derives the value. Markers ride `re_tms_clone`, so
transaction staged stores preserve them with no transactions.c change.
`re_facts_justification_remove` mirrors the add-side validation, so no
public input can delete a marker. Documented divergences and bounds:
insertion-time cycles are rejected with `RE_STATUS_LIMIT` where upstream
admits them and terminates via the retracted set (the cascade-cycle case
itself matches upstream `is_valid` and is pinned whitebox; eager item
removal is the local termination guarantee where upstream never cleans its
maps); `re_facts_set`/`re_facts_update` are plain value writes that never
record explicit support - only `re_facts_insert` (and `insert_logical` on an
explicit entry) does; a marker-only survivor keeps `re_facts_is_logical`
true (upstream keeps the fact in `logical_facts` until retracted);
structured-root derivations keep the pre-existing bound that premise
retraction cascades to the whole root; upstream's global TMS stats struct
has no local aggregate (per-fact equivalents are pinned instead under the
append-only ABI).

Proof graph - real graph shape (Task B2, upstream
`src/backward/proof_graph.rs`). The 64-entry result cache stays the lookup
layer; the graph semantics now ride on it. Every backward run under the
dispatch wrapper captures a bounded (32, deduped-by-path) premise set of
{path, present, FNV-1a typed value fingerprint} covering each fact read -
absent reads are recorded with present=0, so a later first assert still
invalidates - and cache hits merge the served entry's premises into an
enclosing capture. Each store records one informational node per proof
(trace-root rule name + valid flag) with the producing run's premise set.
Lookup keeps generation equality as the fast path and, on serial mismatch,
re-resolves each premise and compares presence plus typed fingerprint: an
entry whose premises all hold survives an unrelated mutation (the headline
behavioral upgrade over the pre-B2 coarse drop), and any flip unlinks the
whole entry - the local analog of upstream `lookup_by_key` filtering invalid
nodes. Any untracked influence (user function mid-proof, premise-cap
overflow, allocation failure) flips the capture opaque and pins the entry to
the coarse generation check; soundness is never traded for precision. Stats:
`re_engine_proof_graph_stats` keeps its two-pointer ABI, and the appended
`re_engine_proof_graph_stats_v2` fills a struct_size-versioned
`re_proof_graph_stats_t` {hits, misses, invalidations, stores, evictions}
(the 64-entry clear-all flush counts as evictions). Dependent propagation is
lazy - an invalidated dependent is detected by re-validation at its next
consult - rather than upstream's eager `invalidate_handle` recursion;
semantically equivalent for a result cache. Documented bounds: object/array
facts fingerprint by type tag only (a future member-level read path must be
captured or flip the capture opaque), and the node `valid` flag is upstream
shape-fidelity no production code consumes.

Backward `?var` unification (Task B3, upstream
`src/backward/unification.rs` case table). A `?var` token on either side of
`==` in a query goal string switches the comparison to unification: a bound
variable resolves to its value; an unbound variable with a resolvable other
side binds and surfaces via `re_proof_binding_get` under the verbatim `?s`
name; an unresolvable side is no match (`RE_QUERY_UNKNOWN` on an absent fact
read, identical to the literal path); two unbound variables (`?x == ?y`)
are `RE_QUERY_DISPROVED` - nothing was read, so the result is cacheable with
an empty premise set and can never flip. Rebinding is sticky-consistent:
the same value is fine, a different value fails that proof branch (never an
engine error). `goal("Rule", a1, ...)` query strings admit literal, `?var`,
and fact-path actuals (nested calls/arithmetic are
`RE_STATUS_INVALID_ARGUMENT`); an unbound `?var` actual leaves the formal
unbound and records a formal-to-`?var` alias, and when the formal later
claims a concrete value the alias rebinds the `?var` sticky-consistently.
Condition equality with an unbound formal claims the other side's concrete
value through the existing operand path, so every fact read stays
premise-captured. Aggregation folds `?var` bindings with no API change.
Documented bounds (upstream parity): no occurs check, no deferral, values
are scalars/arrays compared by typed equality (never element-wise), and
aliases are one-directional value propagation - no union-find, and
propagation requires the same formal name hop-to-hop. Upstream's own
`Unifier` is never called by its search engine (dead integration), so the
case table is mapped onto the machine's two real binding points rather than
ported as a module. Minor surface notes: direct-goal literals are int64-only
while `goal()` actuals lex decimal spellings as doubles (consistent with the
pre-existing `==` path), and an absent fact operand inside a rule condition
resolves to false through the pre-existing rule-goal fallback.

Agenda focus stack + auto-focus (Task B4, upstream `src/rete/agenda.rs`
`AdvancedAgenda`). `ActivateAgendaGroup("g")` pushes the current focus and
switches; when the focus group's activations are exhausted (pending queue
drained after every rule had its first pass) the previous focus pops back
and the recognize-act loop continues, and an empty stack ends the run with
the focus left on the exhausted group (exactly upstream's `pop()?`). The
stack lives on the program next to the focus (not on the agenda) so it
shares the A8 focus lifetime: persistent-agenda runs interrupted by LIMIT
pop back in the next run, and program install resets it for free. The
static pre-set focus is the bottom of stack; the plain setter clears
saved-focus history. The stack is bounded at 32
(`RE_AGENDA_FOCUS_STACK_MAX`); overflow discards the saved focus and the
switch still happens. The `auto-focus true|false` attribute follows the
`no-loop` grammar idiom (any other value or a duplicate is a parse error),
mirrors into the IR, bypasses the compute gate for its rule (upstream
evaluates rules group-agnostically), and switches focus only when the push
creates a genuinely new pending entry - dedup and refraction hits never
re-switch. Group-less auto-focus is a documented no-op. Ratified
divergences: the NULL no-focus state is never stacked (no upstream
MAIN-return; this preserves the ratified A8 mid-run-switch behavior), and
cross-group pending activations drain via the A8 pop-time stale gate and
re-push when their group regains focus (pure conditions re-push, so their
net firings match upstream's per-group heaps; impure rules keep their
first-pass-only bound and do not re-fire that run; activation sequence
numbers may differ). An out-of-focus
pure auto-focus rule re-evaluates every recompute cycle, mirroring upstream;
the 32-cap overflow path is documented but not unit-tested.

Upstream vapor - documented, not replicated (spec Sub-project B, item 5).
Cross-rule alpha sharing and beta token propagation do not exist in any
upstream execution path ("RETE-UL" is a per-rule boolean expression tree;
the named BetaNode/TokenPool/NodeSharing utilities are unused by any
engine); upstream's `Unifier` (`src/backward/unification.rs`) is never
called by the backward search; upstream's integrated proof-graph caching is
dead (fresh graph per query plus an insert/lookup key mismatch); the
parallel engine's actions are no-ops and it is not wired into the main
engine; ConflictResolutionStrategy beyond salience+recency and RETE-UL
accumulate value binding are likewise documented non-goals. Mapping note:
the local engine corresponds to upstream RustRuleEngine + BackwardEngine +
the streaming seams; ReteUlEngine/IncrementalEngine engine-level quirks
(100/1000 iteration caps, `<name>_fired` fact insertion,
no_loop-default-true, update-all-facts-of-type actions) are
upstream-degenerate and deliberately not replicated.

## Streaming completion parity: aggregate kinds, StreamAnalytics, GRL stream syntax, watermark closure, joins, stream rule evaluation

This section records the sub-project C (2026-08-30) closure of the streaming
deltas against upstream rust-rule-engine v1.21.4 (`f80a541`), plus the
streaming surfaces the parity scope documents but does not replicate. The
upstream anchors with f80a541 file:line citations live in
`docs/superpowers/plans/2026-08-30-rule-engine-full-parity-c-streaming.md`;
the citations below refer to those anchors. All delivered rows are
`verified_local` in `docs/rule_engine_conformance.yml`.

Aggregate kinds (Task C1, upstream `src/streaming/aggregator.rs:12`). The
`re_stream_aggregate_kind_t` enum gained tail-appended
`RE_STREAM_AGGREGATE_COUNT_DISTINCT = 8`, `RE_STREAM_AGGREGATE_STDDEV = 9`,
and `RE_STREAM_AGGREGATE_PERCENTILE = 10`; `RE_ABI_VERSION_MINOR` bumped once
for the whole sub-project (3u to 4u). STDDEV is population standard deviation
(variance sums `(v - mean)^2` over N, :233) and requires at least two numeric
values, else `RE_STATUS_NOT_FOUND` (upstream `None`); PERCENTILE sorts the
numeric values ascending and takes the nearest-rank index
`round(p/100 * (n - 1))` on a 0-100 scale (:253), with the percentile carried
on the struct_size-gated tail of `re_stream_filter_options_t` (an uncovered
or out-of-range value, NaN included, is `RE_STATUS_INVALID_ARGUMENT`, while
pre-append filter sizes keep working for every other kind); COUNT_DISTINCT
reports in the existing `count` field under typed equality over `re_value_t`
(bitwise double comparison) - upstream counts distinct `format!("{:?}")`
debug strings, which would equate `1` and `1.0`, a documented divergence.
STDDEV/PERCENTILE join the numeric folds, so a non-numeric matching event is
`RE_STATUS_INVALID_ARGUMENT` exactly like SUM/AVERAGE/MIN/MAX, and an empty
filtered set is `RE_STATUS_NOT_FOUND` for all three new kinds while COUNT
keeps 0/OK. `re_stream_aggregate_result_t` gained `stddev`/`percentile` by
tail append under the same struct_size pair-gating idiom as the Task-16
fields.

StreamAnalytics (Task C2, upstream `src/streaming/aggregator.rs:285`).
`re_stream_analytics_create` builds an engine-allocator handle whose TTL
cache hits iff `current_time_ms - entry_ts < ttl` (:311), serving the cached
clone without refreshing the timestamp; on a miss it recomputes through the
window aggregate, evicts every past-TTL entry (:323), inserts the fresh one,
and returns. Cache identity is the caller key plus kind plus filter identity
(event_type, and percentile for PERCENTILE compared bitwise) - a documented
hardening over upstream string-only keys. The host supplies
`current_time_ms`; the engine samples no clock (single-threaded handle
contract). `re_stream_analytics_moving_average` folds the last N
caller-supplied window handles into one global `sum(events)/count(events)`
over numeric events of the given name (:329) - never an average of per-window
averages. `re_stream_analytics_detect_anomalies` requires at least 3 windows
and at least 10 historical numeric values (all windows except the last),
computes population mean/stddev over the historical set, and flags
last-window events with `|z| > threshold`, reporting their timestamps in
window order (:357). `re_stream_analytics_calculate_trend` averages per
window, half-splits the contributing windows (second half takes the odd
extra), and maps `change_percent = (second_avg - first_avg)/first_avg * 100`
to INCREASING (> +5), DECREASING (< -5), else STABLE (:399, :416, :430).
Documented divergences: the local field mapping is the event name plus its
numeric scalar (local events carry a name and one typed scalar, not data
maps); upstream divides the moving average by the whole window event count
while local counts only numeric events of the name; detect_anomalies reports
timestamps because local events have no IDs (upstream returns event IDs), is
`RE_STATUS_INVALID_ARGUMENT` below 3 windows and `RE_STATUS_NOT_FOUND` below
10 historical values (upstream silently returns no anomalies), flags nothing
on zero historical stddev (upstream would flag unequal values via infinite
z-scores), and uses the buffer-capacity idiom (`RE_STATUS_LIMIT` plus the
total in `out_count`; NULL,0 is the sizing query); calculate_trend is
`RE_STATUS_INVALID_ARGUMENT` below 2 windows (upstream returns Stable) and
STABLE when `first_avg == 0` (documented division guard; upstream f64
division yields inf/NaN); cache misses whose fold fails are not cached
(upstream caches `None`), and the evict-before-insert order differs from
upstream only in the unobservable TTL-0 corner.

GRL stream syntax (Task C3, upstream `src/parser/grl/stream_syntax.rs`). The
condition grammar accepts `var: EventType from stream("name") over
window(<digits> <unit>, sliding|tumbling)` into a `RE_EXPR_STREAM_PATTERN`
node (append-only internal enum) mirrored into the IR with owned payload
strings and a `re_ir_validate` well-formedness branch, so
`re_engine_install` hard-rejects malformed stream-pattern IR. The event type
is optional and an identifier that is exactly `from` is not consumed as a
type (:216 - `e: from stream("events")` is legal; `From` and `fromage` ARE
types); the window clause is optional (:93); the stream name runs to the next
quote with no escape processing; the duration is digits + required whitespace
+ unit with exactly the upstream case-sensitive set (:166-179 -
ms/millisecond(s), sec/second(s), min/minute(s), hour(s); anything else is a
parse error) stored as duration_ms; kinds are sliding|tumbling (:192) plus
`session`, accepted as a documented LOCAL EXTENSION mapping to
`RE_STREAM_WINDOW_SESSION` with the duration as the session timeout -
upstream's GRL parser rejects `session` even though `WindowType::Session`
exists in its Rust enum. Variables follow the binding idiom, duplicates in
one rule are a validation error, and the per-rule stream-pattern scope is
capped at 16. Duration overflow (digits beyond u64 or unit multiplication) is
a parse error where upstream wraps in release builds. The
and-of-two-stream-patterns composition (upstream's `pattern && pattern` join
spelling, :429) is a parse error because that grammar production is vapor
upstream - `join_conditions` is always empty and nothing consumes
`StreamJoinPattern`; mixed pattern-and-ordinary conditions and `or`
compositions parse and are gated at evaluation. Rules carrying stream-pattern
CEs stay off RETE networks (`collect()` admits only fact/literal
comparisons), are impure (first-pass-only evaluation, never on executor
workers), and stay honestly `RE_STATUS_NOT_SUPPORTED` to backward chaining -
upstream has no stream-CE backward evaluation to mirror.

Watermark-driven closure (Task C4, upstream `src/streaming/watermark.rs` and
`src/streaming/window.rs`). `re_stream_window_options_t` gained the
struct_size-gated `watermark_drives_closure` flag (default 0 = the pre-C
behavior, forced 0 when the caller's struct_size does not cover it). With the
flag on, each record is gated against the window's CURRENT watermark before
the late gate: a tumbling bucket is closed when
`watermark >= bucket_end + allowed_lateness_ms` and a record's session target
when `watermark >= (timestamp_ms + retention_ms) + allowed_lateness_ms`
(saturating arithmetic; a record that advances the watermark may close older
buckets as a side effect). Closed + DROP reports `RE_STATUS_NOT_FOUND`,
closed + ERROR reports `RE_STATUS_ERROR`, and closed + ACCEPT records only
when the target is still retained (tumbling: the current bucket; session:
inside the retained session), else `RE_STATUS_NOT_FOUND`. Sliding windows
never reach the gate (record-gate only, documented inert). The gate is
provably outcome-neutral for DROP/ERROR - closure is strictly stronger than
the late gate there - so its observable teeth are exactly the ACCEPT clause;
closed buckets stay readable for aggregation until the usual eviction.
Upstream watermarks never drive window closure except join-node eviction, so
this wiring is a documented local composition over the upstream
late/watermark semantics (`is_late` = event_time < watermark, :43; allowed
lateness `lateness <= max` processes else drops, :236-247; late events never
advance the watermark, :340; the processing-time Periodic strategy is not
applicable to the single-threaded contract).

Cross-stream joins (Task C4, upstream `src/rete/stream_join_node.rs`). The
standalone join API delivers `re_stream_join_type_t` {INNER, LEFT_OUTER,
RIGHT_OUTER, FULL_OUTER} (:11), `re_stream_join_strategy_t` kinds
TIME_WINDOW{duration_ms}, COUNT_WINDOW{count}, SESSION_WINDOW{gap_ms} (:24),
and `re_stream_join_match_t` {key, left/right timestamp, join timestamp} with
0 marking an absent side (:35). One match is queued per strategy-satisfying
same-key pair at record time for any join type; TIME_WINDOW/SESSION_WINDOW
match when `|left_ts - right_ts| <= duration_ms/gap_ms` (upstream compares
whole seconds; local uniformly ms, documented); COUNT_WINDOW matches every
same-key pair and never times out; the join timestamp is the later of the two
matched timestamps. Unmatched outer sides emit exactly once when the single
monotonic watermark passes them (`watermark - ts > window_size`, strict; the
local composition of upstream's `update_watermark` eviction, :204) and never
re-emit, reproducing upstream's observable join-manager outcome with one
emission point (no eager processing-time emission, no watermark-time re-scan
of buffered pairs); non-advancing watermark updates are accepted no-ops
(advance-only rule, watermark.rs:131). Bounds: 256 distinct keys per side (a
257th is `RE_STATUS_LIMIT`), 64 buffered events per key with drop-oldest plus
a dropped counter, 256 queued matches with drop-oldest;
`re_stream_join_drain` uses the capacity idiom (`RE_STATUS_LIMIT` + total in
`out_count`; NULL,0 sizing query), and match keys borrow join-owned storage
valid until destroy. Documented divergences: the record value is validated
but not retained (no join output surfaces payloads), an empty key is
`RE_STATUS_INVALID_ARGUMENT` (upstream silently skips keyless events), and
the `side` argument is validated without partitioning state (one watermark
per node). Upstream does not connect its join node to StreamRuleEngine; the
local API is likewise a host-driven C seam, and the GRL `&&` join form stays
a parse error.

Stream rule evaluation (Task C5, upstream `src/streaming/engine.rs:341-378`).
The engine carries a bounded stream registry (16 names, `RE_STATUS_LIMIT` at
the cap, replace-on-duplicate, borrowed window handles the host keeps
owning - `re_engine_destroy` frees only the name copies, `RE_STATUS_BUSY`
mid-run, unregister a documented no-op for unknown names).
`re_engine_stream_run(engine, facts, window)` injects the upstream
execute_rules fact set into the caller's facts and runs the whole rule base
once: always `WindowEventCount` (DOUBLE, the upstream f64 count - the pinned
parity usage `when WindowEventCount > 5`, :478-481, is test-covered),
`WindowStartTime`, `WindowEndTime`, `WindowDurationMs` (INT64 ms, clamped)
from the window bounds (:347-353 - tumbling reports the current bucket span
even while empty, sliding the [oldest retained, watermark] span, session the
open session span, empty windows all-zero), plus per-event-name
`<name>Sum/Average/Min/Max` DOUBLE folds over numeric retained values
(:364-376 - the local field mapping is the event name; upstream auto-detects
numeric fields over event data maps, :383; a name with only non-numeric
events gets no facts). Every injection is a plain `re_facts_set`, so each
write is host-visible, overwrites stale facts, and bumps the facts mutation
serial - the B2 proof-graph cache keys on that serial, so no stale backward
result survives across two stream runs. Upstream runs the rule base per
window into a fresh `Facts` with actions uncaptured (:304-306); the local
mapping is a host loop of `re_engine_stream_run` per stream into the host's
own facts. The GRL stream-pattern CE evaluates against the registered window:
the optional Type filters by event name, the optional window clause restricts
to the sliding span `[watermark - duration, watermark]` (saturating), the
current tumbling bucket, or the current open session, and no clause reads all
retained events; a rule fires once per run when any retained event qualifies
(exists semantics, first qualifying event in timestamp order the nominal
binding). Ratified divergences: an unregistered stream reports
`RE_STATUS_NOT_SUPPORTED`, never `NOT_FOUND`, because
`compute_rule_activations` (engine.c:755) would swallow `NOT_FOUND` as a
silent non-match; a zero-duration tumbling clause is
`RE_STATUS_INVALID_ARGUMENT` (the upstream `ts / 0` division would panic);
and the CE has exists/single-activation semantics - upstream never evaluates
stream-pattern CEs at all (its engine fans the rule base out per window via
fact injection), so there is no per-event activation multiplicity to mirror,
and fact-premise refraction would collapse identical activations anyway.

Upstream vapor and not-applicable surfaces - documented, not replicated
(anchors in the C plan). The GRL `pattern && pattern` join grammar exists
(`src/parser/grl/stream_syntax.rs:429`) but `join_conditions` is always empty
and nothing consumes `StreamJoinPattern`; the `src/streaming/operators.rs`
offline fluent stream API is not wired into the upstream engine; the tokio
mpsc channel + `Arc<RwLock<WindowManager>>` + batch-task topology of
`src/streaming/engine.rs:183-262` is not applicable to the single-threaded
local handle contract, so the local composition is a synchronous host-driven
seam; and sequence-pattern CEP beyond the delivered pair correlation stays
bounded because upstream itself has no live sequence matcher. The working
streaming machinery upstream actually has is delivered by the rows above.

## Ecosystem parity: plugin boundary, example coverage, Redis probe, feature mapping

This section records sub-project D (2026-08-30/31), the final parity slice
against upstream rust-rule-engine v1.21.4 (`f80a541`): the plugin boundary,
example-family coverage, the Redis runtime probe, and the cargo-feature
mapping. Upstream anchors with f80a541 file:line citations live in
`docs/superpowers/plans/2026-08-30-rule-engine-full-parity-d-ecosystem.md`.
All delivered rows are `verified_local` in `docs/rule_engine_conformance.yml`.

Plugin boundary (Task D1). Upstream ships exactly five plugins
(`src/plugins/mod.rs:1-11`), none feature-gated and none auto-loaded; each
implements `RulePlugin` (`src/engine/plugin.rs:48`) and attaches via
`engine.load_plugin` (`src/engine/engine.rs:1977`). There is deliberately no
local `load_plugin` surface: the registered-function callback boundary stays
the host-extension equivalent with override-first precedence, and the pure
plugin helpers are name-dispatched engine built-ins in `builtins.c`. Of the
29 registered upstream plugin functions, 8 were already covered by the A3/A4
built-in families (min/max/sum/avg, length/contains, join, isEmpty); D1 added
the 15 missing pure helpers — `concat`/`repeat`/`substring`
(`string_utils.rs:148/:163/:190`), `sqrt` (`math_utils.rs:170`),
`first`/`last`/`reverse`/`slice`/`keys`/`values`
(`collection_utils.rs:286/:308/:330/:372/:404/:421`),
`isEmail`/`isPhone`/`isUrl`/`isNumeric`/`inRange`
(`validation.rs:179/:191/:203/:215/:246`) — plus the `StringReplace` action
body (`string_utils.rs:129`) as a `replace()` function, all pure-classified
and pinned by `test_rule_engine_plugin_parity.c` (33 tests). Fetched-body
behaviors are pinned exactly: empty `first`/`last` yield Null, `isUrl` also
accepts `ftp://`, and `replace` with an empty `from` inserts at UTF-8
codepoint boundaries (upstream-exact). Documented out, not replicated: the
`date_utils` family (environment-clock reads, `date_utils.rs:61-62`; A4
`now`/`timestamp` is the bounded local equivalent), the fact-mutating
CamelCase plugin actions (mapped to the expression functions plus plain
assignment), and 15 metadata-declared-but-never-registered upstream items
(vapor: StringSplit, StringJoin, padLeft, padRight, Modulo, Power, Ceil,
Floor, random, ArrayMap, ParseDate, AddHours, DateDiff, dayOfYear,
ValidateNumeric). Upstream's lib.rs marketing ("44+ actions & 33+ functions")
overcounts the actually registered 33 actions + 29 functions.

Example coverage (Task D2). The pinned upstream manifest holds 29
`[[example]]` entries in seven family directories; `session_window_demo`
additionally exists at `examples/session_window_demo.rs` as an
auto-discovered target outside the manifest and is mapped with the streaming
machinery. No local Rust examples exist, so coverage means a local behavioral
equivalent exercised by a named test; the verbatim per-family mapping table
lives in the header comment of
`engine/tests/test_rule_engine_example_coverage.c`. Three new smokes cover
shapes no existing suite pinned end-to-end — ex01 (fraud_detection/grule_demo
forward chaining over structured facts), ex03 (action_handlers_grl_demo via
registered-function expression dispatch), ex09 (grl_query_demo/
ecommerce_approval_demo over the bounded backward machine); every other
family maps to an existing suite or a documented not_applicable
(05-performance to the deterministic bench baseline regression,
parallel_engine_demo and rete_ul_drools_style are upstream vapor,
10-module-system is covered_bounded by the local defmodule/import machinery).
Two bounded divergences the mapping records: upstream's arbitrary bare
`then ActionName(...)` spelling is a locked local parse error for
non-whitelisted names, and the backward condition matcher reads flat fact
names only (no dotted object traversal; the forward matcher walks) — the ex09
smoke uses flat keys and pins this shape.

Redis exception (Task D3). The streaming-redis row stays `optional_backend`
compile-verified — the spec's one allowed exception. The 2026-08-31 probe
(verbatim evidence in
`.superpowers/sdd/2026-08-29-rule-engine-full-parity/task-d3-report.md`)
found a genuine Redis 8.10.1 service (MSYS2 Windows build, ~5.5-day uptime)
live at 127.0.0.1:6379 — refuting an earlier same-day probe that recorded no
service — but the hiredis development files are absent everywhere probed
(PATH, mingw roots, a VCPKG_ROOT with no installed/ tree, the Redis install
tree itself, no vendored repo copy), so `RULE_ENGINE_ENABLE_REDIS=ON`
force-disables at configure time ("no fallback",
`engine/CMakeLists.txt:736-753`) and the roundtrip test stays compiled out
(`#if RE_HAS_HIREDIS`) even with `RE_TEST_REDIS_URL` set against the live
service. The blocker is the absent client, not the service; service
availability is time-dependent and must be re-probed at any future promotion
attempt (the promotion recipe is recorded in the D3 report).

Feature mapping (Task D4). Upstream declares `default = []`,
`streaming = ["tokio"]`, `streaming-redis = ["streaming","redis"]`,
`backward-chaining = []` with no aggregate feature, so `--all-features` means
exactly {streaming, streaming-redis, backward-chaining}. Locally: streaming
and backward-chaining are always on — compiled into `rule_engine_core`
unconditionally with no gate; streaming-redis maps to
`RULE_ENGINE_ENABLE_REDIS` with hiredis auto-detection (force-OFF when the
client is absent); and the remaining toggles are tooling options rather than
upstream features — `RULE_ENGINE_ENABLE_C11_PARALLEL` (optional executor),
`ENGINE_USE_ASAN`/`ENGINE_USE_UBSAN` (sanitizers), `ENGINE_BUILD_TESTS` (test
targets). No single all-features switch exists locally; the mapping is this
documented list (the upstream.yml all-features row).

## Tested private advanced slice

The current focused suite exercises a private, non-capability-bearing slice for
module declarations with bounded `export: all|none` and `import: Name` statements,
transactional unknown-import/cycle rejection, declared module focus, and
qualified rule names in the form `Module::Rule`. A focused module executes its
own rules plus rules exported by directly imported modules; this is a private
bounded slice and is not a capability-bearing public module ABI. Deterministic
accumulator evaluation and injected clock plumbing for date-bounded rules remain
private test seams.

## Extension ABI contracts

### Streaming windows

`re_stream_window_options_t` is a versioned, C99-only options struct. The
`kind` selects a tumbling, sliding, or session window. `retention_ms`,
`max_events`, and `max_bytes` are hard bounds; `allowed_lateness_ms` and
`late_event_policy` define the input boundary. `re_stream_window_record_v1`
accepts `re_event_timestamp_ms_t`, an unsigned 64-bit millisecond event-time
value. It does not accept a duration disguised as a timestamp, and the runtime
must not replace it with local wall-clock time.

Names and values are copied during the record call. A successful record may
still be rejected by a limit or late-event policy; no partial event is visible
on failure. With the struct_size-gated `watermark_drives_closure` option off
(the default, and the pre-C behavior), record-time watermark handling is
exactly the configured late-event policy; with it on, tumbling buckets and
session targets close once the current watermark passes their end plus
allowed lateness - the streaming completion parity section records the exact
formulas and the ACCEPT-clause teeth.

The tested correlation subset is separate from window storage. It provides
count, numeric sum, numeric average, and the appended minimum/maximum over
retained events filtered by event type and an optional string-valued key, plus
first/last selection of the earliest/latest matching event by timestamp with
insertion order breaking ties. Sub-project C appended three more kinds -
count-distinct (reported in the `count` field under typed equality over
`re_value_t`; upstream counts distinct debug-string spellings, a documented
divergence), population stddev (at least two numeric values required, else
`RE_STATUS_NOT_FOUND`), and nearest-rank percentile on a 0-100 scale from the
struct_size-gated filter tail field (an uncovered or out-of-range percentile,
NaN included, is `RE_STATUS_INVALID_ARGUMENT`; pre-append filter sizes keep
working for every other kind). SUM/AVERAGE/MIN/MAX/STDDEV/PERCENTILE fold
numeric values only - a non-numeric matching event is
`RE_STATUS_INVALID_ARGUMENT` for all six - while FIRST/LAST accept any value
type and COUNT_DISTINCT tolerates any mix. An empty filtered set reports
`RE_STATUS_NOT_FOUND` for every kind except COUNT, which keeps its 0/OK
behavior.
`re_stream_aggregate_result_t` grew by tail append only: callers pass
`struct_size`, fields before `minimum` require only the pre-append size, and
each appended field group (minimum/maximum/first/last, then
stddev/percentile) is written only when `struct_size` covers it, so old-size
callers keep the old fields untouched. The first/last values copy the retained
event value; STRING data is borrowed from the window and stays valid until the
next window mutation or destroy. It also counts deterministic
first-type/second-type pairs sharing the optional key within a bounded timeout.
Stream patterns, joins, analytics, and stream rule evaluation are claimed by
the streaming completion parity section; concurrency and Redis state remain
unclaimed here.

### Snapshot and restore

`re_stream_window_snapshot` returns immutable bytes plus a release callback.
The caller must invoke that callback at most once, passing the original pointer,
size, and context. A null release callback means the snapshot has no release
action and its bytes remain valid only for the documented call-owned lifetime.
`re_stream_window_restore` borrows its input only for the call and must reject
unknown `format_version` values without changing the window. The bytes are an
opaque format contract, not a promise of JSON, a host-memory image, or
cross-version compatibility. Verified local tumbling windows use half-open
event-time buckets; verified session windows extend through the configured
retention gap and start a new session after that gap. Both retain bounded
events and copied values and apply the configured late-event policy.

### State providers and Redis boundary

`re_state_provider_options_t` identifies either a callback provider or the
optional Redis provider and carries an operation timeout. The public ABI has no
Redis client, socket, thread, or retry type. Redis configuration and transport
are private to a separately enabled backend. Provider errors are surfaced as
direct statuses and are never silently converted to local-memory success.
`re_provider_error_t` names the stable error classes that a future provider
adapter may expose: unavailable, timeout, serialization, and conflict.
The portable in-memory provider is runtime-supported through its dedicated
constructor with bounded keys/values, deterministic snapshots, injected-clock
TTL, and atomic staged restore. Native Redis remains optional and returns
`RE_STATUS_NOT_SUPPORTED` when unavailable; it is not implied by the ABI. The
native adapter (`redis_provider.c`) compiles into `rule_engine_core` only when
the CMake option `RULE_ENGINE_ENABLE_REDIS` (default OFF) is ON and the
configure step discovers a hiredis header and library, which also defines
`RE_HAS_HIREDIS`; a missing client force-disables the option with a STATUS
message - no silent fallback and no hard error, replacing the former
FATAL_ERROR stub - and without `RE_HAS_HIREDIS` the
`RE_STATE_PROVIDER_REDIS` kind keeps returning `RE_STATUS_NOT_SUPPORTED`.
Alternatively, `RULE_ENGINE_REDIS_SOURCE_DIR` may point to a Redis source tree
or a hiredis source directory; CMake builds the bundled hiredis C sources as a
private static target and applies the same `RE_HAS_HIREDIS` boundary. This
source path is useful for reproducible builds and does not expose hiredis in
the public ABI.
The adapter mirrors the in-memory provider's vtable over the synchronous
hiredis API: keys are `<prefix>:<name>`, values are raw bytes (a type tag
followed by the payload), TTL uses millisecond PSETEX/PTTL with SET/GET/DEL,
and failures record `RE_PROVIDER_ERROR_UNAVAILABLE` with a message in
`last_error`. Because the v1 provider options carry no connection field, the
adapter takes its connection from the `RE_REDIS_URL` environment variable
(default `redis://127.0.0.1:6379`) with the fixed key prefix `re`. Discovery
alone is not runtime evidence: enablement still requires the integration
environment to supply a controlled Redis server, the roundtrip test runs only
when `RE_TEST_REDIS_URL` names one (otherwise it prints SKIP and counts
green), and no credentials belong in the repository. With Redis 8.10.1 as the
source directory, the source-backed build and live roundtrip are verified in
the local integration matrix.

## Bounded backward query slice

The focused suite exercises a bounded, non-capability-bearing query seam only;
the backward-proof capability bit remains clear. Phase 3 kept it that way
deliberately: `re_engine_capabilities_v2` does not set
`RE_CAP2_BACKWARD_PROOFS` and `re_engine_extension_info` reports
`RE_EXTENSION_BACKWARD_PROOFS` as `RE_STATUS_NOT_SUPPORTED`, because arbitrary
predicate unification and upstream shared-subgraph provenance remain
unsupported and the seam is promoted only when that claim can be honest.
`re_engine_query_bounded` accepts exact flat fact goals of the form
`Name == literal`, `Name == Variable`, or `Name == ?var` (bounded
unification per the depth parity section), argument-bearing
`goal("Rule", actual, ...)` query strings, plus exact installed rule names.
Rule declarations may optionally use bounded formal parameters, for example
`rule "Lookup"(Key)`. Conditions may use `goal("RuleName")` unchanged, or the
 parsed explicit form `goal("RuleName", actual, ...)`; bounded formal/actual
  binding queries, nested goal operands, and registered custom-function
  operands use the mature semantic evaluator; the explicit machine
  remains reserved for simple zero-argument chains. The parser rejects malformed, duplicate, and
over-bound formal/actual argument lists deterministically.
The zero-argument form traverses installed rules with explicit `max_depth` bounds
and active-path cycle detection. Results distinguish proved,
disproved, unknown, and depth-limit outcomes. Successful queries expose
immutable proofs with copied bindings and deterministic source-order traces of
the recursive rule-name path. `max_solutions` enumerates alternative rules for
 the queried rule; each proof also owns deterministic derivation-path nodes and
   parent/child edges. An edge connects a node to its immediate trace-parent
   goal, so sibling alternatives such as `Top -> A` and `Top -> B` are distinct
   proofs rather than a shared graph. Shared-subgraph/upstream producer
   provenance and arbitrary predicate unification remain unsupported.
   `re_query_next` transfers ownership of the returned proof to the caller: it
   remains valid after fact mutation and query destruction, while proofs not yet
   returned are released by the query. Fact mutation invalidates only the
   query's remaining proofs.

Phase 3 extends the same seam, still without advertising the capability bit.
A leading `NOT ` prefix on a query goal is negation-as-failure under the
closed-world assumption: a provable subgoal yields `RE_QUERY_DISPROVED` with
zero solutions, an unprovable or disproved subgoal yields `RE_QUERY_PROVED`
with one empty-binding proof whose trace names the full `NOT <goal>` text, and
a depth-limited subgoal reports `RE_QUERY_LIMIT` unchanged because inverting a
limited search would be unsound. There is no stratification pass - upstream
likewise restricts NOT to a goal prefix. Nested `NOT NOT` unwraps one level
per recursion, the prefix is case-sensitive and consumes no `max_depth` level
(the subgoal re-enters the dispatcher with the caller's normalized options and
`max_solutions` 1), an empty remainder is `RE_STATUS_INVALID_ARGUMENT`, and
the inversion composes with the selected search strategy because it applies to
the strategy-selected subgoal result. An exact-form `goal("RuleName")` query
string unwraps to the bare rule goal; a rule literally named `goal("X")`
collides with the unwrap.

`re_engine_query_aggregate` runs a pattern (an ordinary query goal string)
through an internal bounded query - `max_depth` 64, `max_solutions` 1024, DFS -
and folds the named binding over the solutions in DFS order. Kinds are
`RE_ACCUM_COUNT`/`SUM`/`AVERAGE`/`MIN`/`MAX` plus the appended
`RE_ACCUM_FIRST`/`LAST`. Result typing follows the upstream aggregation rules:
COUNT is `RE_VALUE_INT64`, AVERAGE `RE_VALUE_DOUBLE`, and SUM/MIN/MAX stay
`RE_VALUE_INT64` when every folded value was INT64 - a deliberate difference
from `re_accumulator_evaluate`'s always-DOUBLE, noted in the header. FIRST/LAST
copy the first/last carrier's binding value; a STRING result is
`RE_STATUS_NOT_SUPPORTED` because proof string storage dies with the internal
query. An empty solution set yields COUNT 0 with `RE_STATUS_OK` and
`RE_STATUS_NOT_FOUND` for every other kind; a non-numeric fold input is
`RE_STATUS_INVALID_ARGUMENT`. Reaching the 1024-solution cap reports
`RE_STATUS_LIMIT` because an exact fit cannot be told apart from a truncated
set, as does a depth-limited internal search. Percentile, stddev,
count-distinct, GROUP BY, and nested or multi-variable aggregation are
excluded; upstream's GRL query-block/WHERE surface is not parsed. The INT64
fold accumulates with unchecked addition, so extreme sums overflow (wrap)
without a status.

`re_query_options_t` appends `strategy` and `disable_shared_proof_graph` under
the existing `struct_size` versioning: a struct that does not cover the
appended tail gets DFS with sharing on, a sub-size struct is
`RE_STATUS_INVALID_ARGUMENT`, and a strategy value outside [0, 2] is
`RE_STATUS_INVALID_ARGUMENT`. `RE_QUERY_STRATEGY_BREADTH_FIRST` and
`RE_QUERY_STRATEGY_ITERATIVE` share one iterative-deepening wrapper over the
DFS machine - the goal is re-proven with `max_depth` caps 1, 2, 4, ... up to
the configured maximum (default 64), the first cap with at least one solution
wins, and more than 32 doublings reports `RE_STATUS_LIMIT`. Backward queries
execute no actions, so re-probing is side-effect free. Upstream iterative
deepening is likewise DFS probes at rising depth caps; upstream breadth-first
is a separate queue-based search that is not modeled. A winning capped probe
reports PROVED even though deeper branches were cut - the cap is the strategy
mechanism, not a search failure.

The shared proof graph is a lazily created engine-owned cache of final query
results (PROVED/DISPROVED only; LIMIT/UNKNOWN are never cached), consulted
after option normalization and keyed on the exact goal text, the facts
identity, the normalized options (`max_depth`, `max_solutions`, `strategy`),
and the engine config serial, and stamped with the facts mutation generation.
It holds at most 64 entries and clears every entry when full (counted as
evictions); served proofs are deep clones, and a served query wires the same
invalidation subscription a fresh run gets. `config_serial` bumps on program
install and function register/unregister, and `mutation_serial` now also
bumps on retraction, so TMS cascades and retract-only transactions still
force revalidation of cached proofs. Sub-project B replaced the coarse
per-facts invalidation with the real graph shape described in the depth
parity section: each run captures a bounded premise set (32, deduped by
path, typed value fingerprints, absent reads recorded), and on a serial
mismatch each premise is re-resolved - an entry whose premises all hold
survives an unrelated mutation, while any flip unlinks the entry. Untracked
influences (user function mid-proof, premise-cap overflow, allocation
failure) flip the capture opaque and keep the coarse generation semantics
for that entry. Entries key on the facts pointer value but never dereference
it, so there is no use-after-free; a destroy-plus-realloc at the same
address with a matching generation could alias and is parked as a documented
residual risk. `disable_shared_proof_graph` bypasses lookup, store, and
stats entirely (no stats movement), `re_engine_proof_graph_stats` reports
hits and misses - zeroes before the first cached query - and the appended
`re_engine_proof_graph_stats_v2` adds invalidations, stores, and evictions
in a struct_size-versioned struct. A NOT query counts the subgoal consult in
the stats, so one fresh `NOT X` records two misses. The upstream
shared-subgraph producer-provenance graph is not modeled.

Names and string slices returned by proof binding, trace, and node getters are
borrowed from the proof and remain valid until `re_proof_destroy`; callers must
not retain them afterward. Proof records are append-only ABI values, but
getters require the complete record size currently defined by this header.

Custom function callbacks receive borrowed engine/facts handles and a read-only
argument array; they write one output value and must not retain pointers after
return. In this ABI, names are exact byte-sensitive matches, registrations are
engine-local, and duplicate names resolve to the newest registration. Calls may
appear in `when` operands and action values, with nested calls evaluated
depth-first and arguments evaluated left-to-right. Missing functions return
`RE_STATUS_NOT_FOUND`; callback statuses propagate unchanged; callback-owned
arity and type checks conventionally return `RE_STATUS_INVALID_ARGUMENT`.
Registration is rejected while the engine is running. Unregister is deferred
when called during an in-flight call, and invokes the descriptor release callback
at most once after the call completes; the opaque unregister API is void, so a
busy unregister is a no-op rather than a returned status.

Structured values use opaque value handles so ownership and recursive layout can
evolve without changing `re_value_t`. Objects and arrays copy their inputs and
bound keys, depth, and collection size. Structured values are copied and
destroyed recursively only through the documented maximum nesting depth of 64;
attempting to add a child beyond that bound returns `RE_STATUS_LIMIT`.
`RE_VALUE_NULL`, `RE_VALUE_UNKNOWN`, and
`RE_STATUS_NOT_FOUND` distinguish explicit null, unknown, and missing paths.
Fact lifecycle IDs contain a slot and generation; retract invalidates the old
generation, and insert/update/retract notifications carry copied-name/value
snapshots during the callback. Subscription destruction removes the callback
before its context is reused.

Agenda/RETE handles are inspection/control views, not public node layouts.
Backward queries are pull-based and proofs are immutable opaque results; query
and proof destruction is caller-owned. Windows copy event data, apply configured
retention limits, and do not retain caller buffers. State providers own their
backend context and report backend failure rather than silently falling back.
Concurrency is opt-in and opaque: only pure read-only conditions run in private
workers, deterministic activation merge is followed by serial actions/callbacks,
and the base C99 ABI does not include C11 thread types. Shared mutable engine or
facts operations return `RE_STATUS_BUSY` during worker matching. The threading
contract is documented in the header above `re_engine_create` and is
test-locked: engine, facts, windows, and providers are single-threaded handles
that callers must externally synchronize; while `re_engine_run` is active,
re-entering the run, opening a user transaction, or resetting working memory
returns `RE_STATUS_BUSY`; fact writes from an action callback stage into the
firing's transaction and commit with it rather than being rejected; and
allocator callbacks must not re-enter any rule-engine API on a handle involved
in the in-flight operation.

All extension entry points may return `RE_STATUS_NOT_SUPPORTED` until their
capability bit is advertised. Status labels in the conformance manifest mean:
`exact_parity` matches upstream semantics; `equivalent_behavior` preserves the
observable contract through a different implementation; `optional_backend`
requires a separately enabled provider; and `unsupported` has no local
implementation. `pending` means the contract is scoped but not verified.

## ABI evolution policy

New enum values may be appended. Existing enum numeric values and struct field
order must not change after implementation begins. New optional capabilities
use the versioned query and opaque handles rather than adding fields to existing
public structs. ABI minor 3 makes one deliberate exception:
`max_activations_tracked` is appended to `re_limits_t`, which has no
`struct_size` field; positional initializers and zero-init keep prior behavior
at source level, but code compiled against the old layout must be recompiled.
Extension declarations do not claim custom functions, backward
chaining, streaming, Redis state, advanced agenda controls, or concurrency are
complete.
