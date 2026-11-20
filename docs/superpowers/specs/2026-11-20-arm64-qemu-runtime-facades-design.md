# arm64 QEMU Runtime Facades Tests Design

## Context

The arm64 lane selects exactly 35 tests, including runtime_core's nine lifecycle
cases and target contract. Three other registered runtime tests remain outside
it: `test_runtime_facade`, `test_runtime_io`, and `test_runtime_reload`. This
slice adds those three executables and produces an exact 38-test selection.

## Approaches

1. Extend the existing lane with the three already-registered executables. This
   reuses their generated QEMU commands and is the recommended minimal change.
2. Add a separate runtime-facade lane. This duplicates the multiarch and emulator
   setup without providing needed isolation.
3. Select every runtime-prefixed or every headless test. This is rejected because
   it would mix unrelated targets and weaken the explicit per-family coverage
   boundary.

## Existing Behavior and Baseline

All three tests are direct executable-target registrations, so CMake already
prefixes their cross CTest commands with `/usr/bin/qemu-aarch64 -L /`.

- `test_runtime_facade`: 18 cases for owned messages, bounded queues, task
  draining, and cross-thread correlation IDs.
- `test_runtime_io`: 16 cases for thread ownership and asynchronous VFS IO,
  including timeout, cancellation, stale generations, overload, and failure
  injection.
- `test_runtime_reload`: 34 cases for reload ownership/commit/cancel/shutdown
  and profiler record/export/window behavior.

They link the existing test-only `runtime_core_test` variant and need no nested
compiler, target tool, asset path translation, or host-CMake driver change.

Unmodified native focused execution passes 3/3 with 18/16/34 case summaries in
0.78 seconds. Unmodified cross focused execution with the workflow multiarch
dependencies passes the same 3/3 and 18/16/34 in 1.41 seconds. No product or
test-source change is needed.

## CI Change

Append these targets to the existing arm64 build command:

```text
test_runtime_facade test_runtime_io test_runtime_reload
```

Add this single alternative to the existing CTest selection:

```text
test_runtime_(facade|io|reload)
```

The existing final outer anchor limits this alternative to exactly the three
names. Keep the runtime_core unit/contract alternative and all 35 previous tests
unchanged. Emulator environment, object checks, verbose output,
`--no-tests=error`, 300-second timeout, and failure propagation remain intact.

No dependency, skip, retry, status mask, or assertion relaxation is introduced.

## TDD and Verification

1. Run a PyYAML/native-selection contract against the old workflow. Require the
   three build targets, exact regex alternative, and previous 35 plus exactly
   these three = 38; observe RED on the old build command.
2. Apply only the build-list and selection-regex edits. Require the unchanged
   contract to pass and compare the actual selected set with an explicit 38-name
   expected set.
3. Re-run native and cross focused tests; require 3/3, 18/16/34 case summaries,
   and no new skips.
4. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner CMake prerequisite. Require 38/38, all previous evidence, the new
   18/16/34 summaries, and exactly one existing QEMU ptrace setup skip.
6. Request independent read-only review, push the verified commits, and assert
   the exact-HEAD remote arm64 job log contains the same 38-test selection and
   all old/new evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, runtime
overview, and missing-capabilities inventory without replacing history.

This is a selected 38-test suite, not full arm64 CTest. Lua/ECS, editor, rendering,
Snowflake transport scenarios, QUIC, production deployment, GPU, and physical
devices remain outside this slice unless already covered by the existing 35
tests.
