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
- exact flat-key lookup for dotted fact names; structured-value path traversal is
  bounded and separately tested, while rule-condition fallback remains flat-key only.
- bounded object/array values and nested path lookup through the versioned value API;
- explicit null/unknown values and generation-safe fact lifecycle notifications.
- a bounded, non-capability-bearing query seam for exact flat goals and
  recursive rule bodies with literal/propagated formal binding; general
  unification and shared-subgraph/upstream proof provenance remain pending. The
  bounded binding slice stores each successful derivation path as owned nodes
  and deterministic parent/child edges.
- backward condition evaluation uses heap-backed continuation frames for
  TRUE/FALSE, COMPARE, NOT, AND, and OR nodes. Checked frame growth and enclosing
  environment/trace checkpoints preserve failed-branch rollback. Goal and custom
  function operand evaluation still uses the existing operand path and may
  re-enter goal proving; operand continuation migration is deferred.

Deferred explicitly:

- full upstream RETE/RETE-UL execution, persistent agenda/TMS, and general producer provenance;
- arbitrary argument unification, shared-subgraph proof graphs, and upstream
  proof strategies; bounded recursive binding and derivation-path enumeration
  are implemented and remain deliberately narrower than upstream semantics;
- native Redis-backed streaming state. The portable bounded in-memory provider is implemented;
- persistent agenda control and full upstream truth-maintenance behavior.

The bounded agenda-control subset enforces `MAIN`/named program focus,
activation-group sibling cancellation, and the tested one-run `no-loop` and
`lock-on-active` guards. Rule metadata remains immutable and runtime state is
allocated for the run, so callback pointers and contexts are never retained.
Persistent agenda state, focus stacks/cycles, and full TMS remain pending. The bounded RETE mode
supports up to eight flat fact-vs-literal comparisons joined by conjunction, retains private
alpha/beta/token memories across runs, and incrementally refreshes affected condition memories on
lifecycle events. Other expressions use the linear evaluator.

The private advanced test seam covers accumulator value behavior, bounded module
declarations/imports/exports with cycle rejection and focused visibility, and
injected-clock ownership. Module behavior is intentionally private and bounded;
it does not advertise a public module ABI, complete date parsing, or agenda/RETE
support.

The local status is limited to behavior covered by
`engine/tests/test_rule_engine.c`; these statuses match
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
tests; Redis remains unsupported at runtime.
The separate tested correlation seam filters retained events by type and
string-valued key, counts first/second pairs within a timeout, and computes
count, numeric sum, or numeric average without changing retention.

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
claim that native Redis support is enabled. Redis remains an explicit
`RE_STATUS_NOT_SUPPORTED` boundary. Native enablement requires a CMake-detected
hiredis-compatible header/library and a separately supplied controlled Redis
integration endpoint; absent either prerequisite, configuration must keep the
adapter disabled. Redis failures must propagate as provider errors and must
never fall back to empty or in-memory state.

## Lifetime and ownership

- `re_engine_t`, `re_facts_t`, and `re_program_t` are opaque, single-owner
  handles. Each create/load operation returns ownership to the caller.
- `re_engine_install` consumes a successfully installed program. After a
  successful call the engine owns it; callers must not destroy or reuse it.
  On failure ownership stays with the caller.
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

The current forward runtime evaluates the immutable program and fires activations
in descending salience order with source order as the stable tie-breaker. The
supported single-rule conjunction path also retains a private incremental RETE
network across runs and fact lifecycle events; other rule programs use the
bounded linear evaluator.

## Bounded RETE milestone

`engine/src/rule_engine/rete.c` contains a bounded runtime seam for a narrow
two-condition conjunction over flat facts. It subscribes to generation-safe
insert/update/retract events, retains alpha memories and beta token pairs across
runs, stores fact-id lineage plus optional rule-name provenance, and removes
stale records after lifecycle changes. A matching single-rule run installs this
network and reuses it for the same fact handle. The implementation is not full
RETE-UL: it has no persistent agenda, truth maintenance, or general condition
graph. Agenda groups, streaming, backward chaining, concurrency, and all other
RETE features remain outside this milestone.

One run owns its activation list. A matching rule applies its parsed action
assignment, then invokes the callback; the callback may further mutate facts
through the supplied fact handle. Callback failure, cancellation, and limit
exhaustion stop the run and return the corresponding status. Salience ordering
is locally verified; persistent agenda groups, full producer-provenance
semantics, and public agenda/RETE handles remain unsupported. The optional C11
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
worker in this contract.

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
`Ready == true`, boolean composition, operands, formal bindings, and
non-zero-argument goals covered by the focused tests. Neither path claims
arbitrary upstream unification or shared-subgraph provenance.
