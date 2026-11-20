# arm64 QEMU Lua Runtime Tests Design

## Context

The arm64 lane currently selects exactly 42 tests. The ten `break_lua`-labelled
tests are registered but not selected: nine executable tests plus one host-CMake
target contract. This slice adds exactly those ten and produces a 52-test
selection.

## Approaches

1. Extend the existing lane with the ten named tests. This reuses generated QEMU
   commands and the existing contract, and is the recommended minimal change.
2. Add a separate Lua lane. This duplicates multiarch and emulator setup without
   providing needed isolation.
3. Select the `break_lua` label or an unanchored name prefix. This is rejected for
   the existing name-regex workflow because future tests could silently change
   the exact selection; this slice uses explicit locally anchored names.

## Existing Behavior and Baseline

The nine executable tests have direct target registrations and generated QEMU
commands. `test_break_lua_target_contract` is a host-CMake source-structure check
and does not execute target code.

Coverage comprises 126 executable cases:

- runtime lifecycle/configuration: 9;
- module load/versioned reload/failure retention: 24;
- values/calls/frame dispatch/function references: 34;
- host bindings/ECS batches/config/sandbox/budget behavior: 33;
- stable host handles: 4;
- bounded table marshalling: 5;
- opt-in debugging and stepping: 9;
- kernel Lua integration: 4;
- applying drained Lua ECS records to a world: 4.

The target contract verifies formal target ownership, vendored Lua linkage,
test-only hook isolation, debug target wiring, and the absence of unintended
consumer links.

Unmodified native focused execution passes 10/10 with summaries
9/24/34/33/4/5/9/4/4 and the target contract in 0.41 seconds. Unmodified cross
focused execution passes the same 10/10 and summaries in 1.62 seconds. No product
or test-source change is needed.

## CI Change

Append these nine executable targets to the existing arm64 build command:

```text
test_break_lua_runtime test_break_lua_module test_break_lua_value test_break_lua_binding test_break_lua_handle test_break_lua_table test_break_lua_debug test_break_kernel_lua test_break_lua_ecs_apply
```

The contract has no binary target. Add these locally end-anchored alternatives
to the existing CTest selection:

```text
test_break_lua_(runtime|module|value|binding|handle|table|debug|ecs_apply|target_contract)$
test_break_kernel_lua$
```

The local `$` tokens prevent future derived names from silently entering the
selection. The legacy compatibility test `test_script_lua` is intentionally not
included in this Stage 3 runtime slice.

Keep all 42 previous tests, emulator environment, object checks, verbose output,
`--no-tests=error`, 300-second timeout, and failure propagation unchanged. No
dependency, skip, retry, status mask, or assertion relaxation is introduced.

## TDD and Verification

1. Run a PyYAML/native-selection contract against the old workflow. Require all
   nine build targets, both exact alternatives, future-prefix rejection, and
   previous 42 plus exactly these ten = 52. Observe RED on the old build command.
2. Apply only the build-list and selection-regex edits. Require the unchanged
   contract to pass and compare the actual selected set with an explicit 52-name
   expected set.
3. Re-run native and cross focused tests; require 10/10, all nine case summaries,
   the target contract, and no new skips.
4. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner CMake prerequisite. Require 52/52, all previous evidence, all Lua
   summaries and contract, and exactly one existing QEMU ptrace setup skip.
6. Request independent read-only review, resolve adopted findings test-first,
   push the verified commits, and assert the exact-HEAD remote arm64 job log
   contains the same 52-test selection and all old/new evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, Lua runtime
design document, and missing-capabilities inventory without replacing history.

This is a selected 52-test suite, not full arm64 CTest. Legacy script compatibility,
LuaJIT, editor UI, rendering, world streaming, Snowflake transport scenarios,
QUIC, production deployment, GPU, and physical devices remain outside this slice
unless already covered by the existing 42 tests.
