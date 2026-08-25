# Rule Engine ABI Design

## Design goals

The ABI is deliberately smaller than the upstream Rust feature set. It gives
the implemented C99 core stable seams for required GRL behavior without
pretending that deferred upstream families exist locally.

The contract has four objects: an engine, facts, a parsed program candidate,
and typed values. There are no public parser nodes, RETE nodes, rule structs,
stream records, proof graphs, or backend-specific handles.

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
families have no bits in this version.

## Function contract table

| Function | Caller owns | Engine/API owns | Failure and output rules |
|---|---|---|---|
| `re_engine_create` | allocator and input limits | returned engine | `NULL` on invalid allocator or OOM |
| `re_engine_destroy` | handle until call | all engine-owned program state | NULL-safe, no return status |
| `re_facts_create` | allocator and input limits | returned facts | `NULL` on invalid allocator or OOM |
| `re_facts_destroy` | handle until call | copied names and values | NULL-safe, no return status |
| `re_facts_set` | name/value memory after return | copied name/value | returns invalid argument, limit, or OOM without partial update |
| `re_facts_get` | output storage | returned string slice temporarily | returns not found or invalid argument; no allocation |
| `re_program_load` | source memory after return | candidate on success | output is unchanged on failure; candidate is caller-owned until install |
| `re_program_destroy` | candidate until call | candidate allocations | NULL-safe, no return status |
| `re_engine_install` | candidate until success | candidate after success | failed install preserves both handles |
| `re_engine_run` | facts, options, callback context | no callback/context retention | returns status; no background work or retained output |

Every function that can fail reports it directly. Destructors do not report
failure because release is unconditional and allocator release has no error
channel.

## Transaction and reentrancy rules

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
   deterministic source-order callback notification after each assignment.
5. Callback delivery and fact mutation, cancellation, and execution limits,
   including busy and deferred-destruction behavior. Zero per-run limit fields
   select the corresponding engine defaults; a zero engine default is unlimited.
6. Capability reporting that excludes deferred features.

Nested fact traversal and salience ordering are intentionally pending. Dotted
names, including action references, resolve only by exact flat-key lookup; no
nested fallback is implemented. Deferred behavior is not represented as local
verified conformance until implementation and focused tests exist.

Run focused behavior evidence with `ctest --test-dir <build> -R
test_rule_engine --output-on-failure`; build the standalone ABI consumer with
`cmake --build <build> --target rule_engine_c99_consumer`. The consumer is
compile-only and has no graphics or Lua dependency.

See `docs/Rule_Engine_Architecture.md` for module boundaries,
`docs/rule_engine_conformance.yml` for local/upstream status, and
`docs/Rule_Engine_Benchmark.md` for the manual workload.

## ABI evolution policy

New enum values may be appended. Existing enum numeric values and struct field
order must not change after implementation begins. New optional capabilities
should be exposed through a versioned capability query in a later tested
extension, not by adding speculative fields to this header. In particular,
custom functions, backward chaining, streaming, Redis state, and advanced
agenda controls stay outside this first ABI.
