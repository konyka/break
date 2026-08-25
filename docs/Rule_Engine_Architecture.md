# Rule Engine Architecture

## Status and scope

This document defines the implemented v1 core boundary. The public ABI is in
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
- exact flat-key lookup for dotted fact names; nested traversal remains pending.

Deferred explicitly:

- custom functions;
- backward chaining and proof traces;
- streaming windows;
- Redis-backed streaming state;
- advanced rule control such as agenda groups, activation groups, accumulators,
  date bounds, and modules.
- nested fact traversal;

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
engine: core GRL, facts, and forward execution.
Deferred upstream families intentionally have no capability bits in this ABI.

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

The initial execution model is a bounded forward activation scan. The current
implementation evaluates rules in descending salience order and emits callback
events; equal-salience rules retain source order. General agenda scheduling
remains pending locally.

One run owns its activation scan. A matching rule applies its parsed action assignment,
then invokes the callback; the callback may further mutate facts through the supplied fact
handle. Callback failure, cancellation, and limit exhaustion stop the run and return the
corresponding status. General agenda scheduling is not implemented in v1. No parallel
execution is promised by this ABI.

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

The header uses only C99 facilities: fixed-width integers, `size_t`, named
unions, opaque pointers, and function pointers. It intentionally avoids
anonymous unions, `_Static_assert`, atomics, variadic public APIs, and C11
threading types.
