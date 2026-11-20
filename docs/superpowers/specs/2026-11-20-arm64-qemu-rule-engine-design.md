# arm64 QEMU Rule Engine Tests Design

## Context

The arm64 lane selects exactly 131 tests. The twenty-one rule-engine tests
registered at `engine/CMakeLists.txt:3123-3251` remain outside it: `test_rule_engine`,
eighteen `test_rule_engine_*` executables, and `test_backward_machine_structure`
and `test_backward_machine_context`. This slice adds exactly those twenty-one for
a 152-test selection.

## Approaches

1. Extend the lane by name. Recommended: all twenty-one are direct executables
   with generated QEMU commands.
2. Select by label. Rejected: the rule-engine tests carry no label.
3. Add a separate lane. Rejected: duplicates the multiarch setup.

## Existing Behavior and Baseline

Every executable links only `rule_engine_core` (C99). Hiredis-backed code paths
are compiled only when `RULE_ENGINE_ENABLE_REDIS` is ON (default OFF,
`engine/CMakeLists.txt:24`); both trees leave it OFF, so hiredis is never
searched for and those paths are absent on native and cross. Ten
`test_rule_engine_stream_ext` cases (nine `redis_provider_*` probes and
`redis_roundtrip_when_service_available`) then only print `SKIP:` and count as
passed, so 47 of its 57 cases, and 633 of the 643 below, carry assertions; the
`RE_STATUS_NOT_SUPPORTED` boundary for Redis requests is still asserted.
`test_backward_machine_structure` has four cases: two read engine sources
through the configure-time `TEST_SOURCE_ROOT` (qemu-user runs on the host
filesystem, so the absolute path resolves), and two run real queries. `test_rule_engine_executor_stress` and
`rule_engine_fuzz_smoke` are out of scope (the former is not registered without
`RULE_ENGINE_ENABLE_C11_PARALLEL`; the latter is a hardening fuzz smoke).

| Test | Cases | Test | Cases |
|---|---|---|---|
| `test_rule_engine` | 98 | `test_rule_engine_plugin_parity` | 37 |
| `test_rule_engine_transactions` | 13 | `test_rule_engine_example_coverage` | 3 |
| `test_rule_engine_tms` | 19 | `test_rule_engine_query_blocks` | 25 |
| `test_rule_engine_grl_semantics` | 26 | `test_rule_engine_stream_ext` | 57 |
| `test_rule_engine_ir` | 20 | `test_rule_engine_stream_grl` | 19 |
| `test_rule_engine_forall_limits` | 5 | `test_rule_engine_stream_eval` | 22 |
| `test_rule_engine_rete_incremental` | 19 | `test_rule_engine_backward_deep_chain` | 1 |
| `test_rule_engine_agenda` | 45 | `test_backward_machine_structure` | 4 |
| `test_rule_engine_backward` | 13 | `test_backward_machine_context` | 4 |
| `test_rule_engine_backward_ext` | 55 | `test_rule_engine_backward_bindings` | 21 |
| `test_rule_engine_grl_surface` | 137 | | |

That is 643 cases. Native focused passes 21/21 with these counts. Unmodified
cross focused execution in a clean Ubuntu 24.04 container passes 21/21 with the
same counts (CTest 2.86 seconds; slowest `test_rule_engine_backward_deep_chain`
at 1.28 seconds). No product or test-source change is needed.

## CI Change

Append the twenty-one executable targets after `test_audio_wav` and add:

```text
test_rule_engine(_(transactions|tms|grl_semantics|ir|forall_limits|rete_incremental|agenda|backward|backward_ext|grl_surface|plugin_parity|example_coverage|query_blocks|stream_ext|stream_grl|stream_eval|backward_deep_chain|backward_bindings))?$|test_backward_machine_(structure|context)$
```

## TDD and Verification

1. Contract against the old workflow: twenty-one build targets, exact
   alternatives, rejection of derived names, `test_rule_engine_executor_stress`,
   and `rule_engine_fuzz_smoke`; previous 131 plus these twenty-one = 152. RED.
2. Apply the edits; GREEN on the explicit 152-name set.
3. Focused native with the new `-R`: 21/21.
4. Native full: 455, zero failures, four established skips.
5. Clean-container workflow: 152/152, exactly one ptrace setup skip.
6. Independent review, push, and assert the exact-HEAD remote log with all
   twenty-one per-test counts.

## Boundaries

A selected 152-test suite, not full arm64 CTest. Redis-backed paths, the C11
parallel executor stress test, fuzzing, and large-rule-set performance remain
outside it. `test_rule_engine_backward_deep_chain` has a single case.
Two `test_backward_machine_structure` cases check source structure, not arm64
behavior. Ten Redis cases are vacuous without the Redis option.
