# arm64 QEMU PAL and Task System Tests Design

## Context

The arm64 lane currently selects exactly 66 tests. Six registered PAL/task tests
remain outside it: `test_platform_config`, `test_platform_null_safety`,
`test_platform_fs_write`, `test_platform_size_semantics`, `test_task`, and
`test_task_singleton`. This slice adds exactly those six and produces a 72-test
selection.

## Approaches

1. Extend the existing lane with the six direct executable tests. This reuses
   generated QEMU commands and is the recommended minimal change.
2. Add a separate PAL/task lane. This duplicates multiarch and emulator setup
   without providing needed isolation.
3. Select every platform or task prefix. This is rejected because WSI, mobile,
   compatibility-matrix, and future derived tests require separate boundaries.

## Existing Behavior and Baseline

All six tests have direct executable-target registrations and generated QEMU
commands. They need no window system or physical device.

- `test_platform_config`: ten cases for configuration validation, UTF-8 titles,
  dimensions, budgets, and opaque native handles.
- `test_platform_null_safety`: one safe null-platform query case.
- `test_platform_fs_write`: 11 cases for atomic write/commit/abort, rename/fsync
  failure outcomes, permissions, directories, symlinks, and file sizes.
- `test_platform_size_semantics`: three cases for logical/drawable size rules on
  Win32, Wayland, and Cocoa model paths.
- `test_task`: 16 cases for submission, priorities, dependencies, capacity,
  validation, and worker behavior.
- `test_task_singleton`: one process-wide ownership rejection case.

Unmodified native focused execution passes 6/6 with 10/1/11/3/16/1 case summaries
in 0.01 seconds. Unmodified cross focused execution passes the same 6/6 and
summaries in 0.15 seconds. No product or test-source change is needed.

## CI Change

Append these six targets to the existing arm64 build command:

```text
test_platform_config test_platform_null_safety test_platform_fs_write test_platform_size_semantics test_task test_task_singleton
```

Add this locally end-anchored alternative to the existing CTest selection:

```text
test_(platform_config|platform_null_safety|platform_fs_write|platform_size_semantics|task|task_singleton)$
```

The local `$` prevents future derived names from silently entering the selection.
Keep all 66 previous tests, emulator environment, object checks, verbose output,
`--no-tests=error`, 300-second timeout, and failure propagation unchanged.

No dependency, skip, retry, status mask, or assertion relaxation is introduced.
No X11 code, test, or dependency is introduced.

## TDD and Verification

1. Run a PyYAML/native-selection contract against the old workflow. Require all
   six build targets, the exact alternative, future-prefix rejection, and previous
   66 plus exactly these six = 72. Observe RED on the old build command.
2. Apply only the build-list and selection-regex edits. Require the unchanged
   contract to pass and compare the actual selected set with an explicit 72-name
   expected set.
3. Re-run native and cross focused tests; require 6/6, 10/1/11/3/16/1 case
   summaries, and no new skips.
4. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner CMake prerequisite. Require 72/72, all previous evidence, the new
   10/1/11/3/16/1 summaries, and exactly one existing QEMU ptrace setup skip.
6. Request independent read-only review, resolve adopted findings test-first,
   push the verified commits, and assert the exact-HEAD remote arm64 job log
   contains the same 72-test selection and all old/new evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, runtime thread
model, and missing-capabilities inventory without replacing history.

This is a selected 72-test suite, not full arm64 CTest. Window-system integration,
WSI, mobile/device backends, editor UI, rendering, Snowflake transport scenarios,
QUIC, GPU, and physical devices remain outside this slice unless already covered
by the existing 66 tests.
