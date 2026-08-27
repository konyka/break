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
claim full upstream collection, property, or method-call semantics.

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
caller destroys that network. The engine uses RETE for incremental provenance,
but rule matching remains tied to the IR rule result when an exact token cannot
be selected, rather than treating a nonzero activation count as a rule match.
| `re_facts_get` | output storage | returned string slice temporarily | returns not found or invalid argument; no allocation |
| `re_program_load` | source memory after return | candidate on success | output is unchanged on failure; candidate is caller-owned until install |
| `re_program_destroy` | candidate until call | candidate allocations | NULL-safe, no return status |
| `re_engine_install` | candidate until success | candidate after success | failed install preserves both handles |
| `re_engine_run` | facts, options, callback context | no callback/context retention | returns status; no background work or retained output |
| `re_engine_register_function` | descriptor memory after return; context until unregister | copied name and registration handle | transactional registration; callback/release lifetime is explicit |
| `re_engine_query` / `re_query_next` | goal input after call | query and proof handles | bounded, pull-based proof iteration; unsupported until capability is advertised |
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
   `lock-on-active`. The bounded single-rule conjunction path retains private
   incremental RETE memories and fact-id/rule-name activation provenance; the
   runtime does not claim persistent agenda state or post-focus-cycle reactivation.

Structured-value nested fact traversal is implemented only through the bounded
`re_facts_get_path` API and is covered by focused tests. Rule declarations still
resolve dotted condition/action names through exact flat-key lookup; they do not
fall back to structured traversal. Rule declarations may optionally include
`salience <int32>` after the quoted name; matching activations execute in
descending salience order, with source order preserved for ties. Dotted
names, including action references, resolve only by exact flat-key lookup; no
nested fallback is implemented. Deferred behavior is not represented as local
verified conformance until implementation and focused tests exist.

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
on failure. Exact watermark, eviction, and session-gap behavior are not
specified until the runtime implementation is tested.

The tested correlation subset is separate from window storage. It provides
count, numeric sum, and numeric average over retained events filtered by event
type and an optional string-valued key. It also counts deterministic
first-type/second-type pairs sharing the optional key within a bounded timeout.
This does not claim general stream patterns, joins, concurrency, or Redis state.

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
current build has no native Redis adapter enabled. A future adapter must be
enabled only after CMake detects a usable hiredis-compatible header and
library, and only when the integration environment supplies a controlled
Redis server. Missing client files, failed CMake discovery, or a missing test
service must leave the option disabled; no credentials belong in the repository.

## Bounded backward query slice

The focused suite exercises a bounded, non-capability-bearing query seam only;
the backward-proof capability bit remains clear.
`re_engine_query_bounded` accepts exact flat fact goals of the form
`Name == literal` or `Name == Variable`, plus exact installed rule names.
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
facts operations return `RE_STATUS_BUSY` during worker matching.

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
public structs. Extension declarations do not claim custom functions, backward
chaining, streaming, Redis state, advanced agenda controls, or concurrency are
complete.
