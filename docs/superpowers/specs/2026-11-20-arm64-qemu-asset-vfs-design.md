# arm64 QEMU Asset VFS and Hot Reload Tests Design

## Context

The arm64 lane currently selects exactly 52 tests. Four registered asset/VFS and
hot-reload executables remain outside it: `test_vfs`, `test_async_loader`,
`test_filewatch_backend`, and `test_hotreload`. This slice adds exactly those
four and produces a 56-test selection.

## Approaches

1. Extend the existing lane with the four direct executable tests. This reuses
   generated QEMU commands and is the recommended minimal change.
2. Add a separate asset lane. This duplicates multiarch and emulator setup without
   providing needed isolation.
3. Select broad asset or hot-reload prefixes. This is rejected because unrelated
   or future derived tests would silently enter the exact selection.

## Existing Behavior and Baseline

All four tests have direct executable-target registrations and generated QEMU
commands. None needs a nested compiler, host-CMake driver, target-tool wrapper,
or external asset-path translation.

- `test_async_loader`: 17 cases for asynchronous request lifecycle, cancellation,
  failure handling, queues, and decode/IO worker shutdown.
- `test_hotreload`: seven cases for bounded shader/resource file reads and reload
  validation with stubbed rendering interfaces.
- `test_vfs`: 36 cases for mounts, path normalization, file IO, traversal
  rejection, and malformed input handling.
- `test_filewatch_backend`: 26 cases for backend-selection policy and safe event
  path normalization.

Unmodified native focused execution passes 4/4 with 17/7/36/26 case summaries in
0.05 seconds. Unmodified cross focused execution passes the same 4/4 and
summaries in 0.32 seconds. No product or test-source change is needed.

## CI Change

Append these four targets to the existing arm64 build command:

```text
test_vfs test_async_loader test_filewatch_backend test_hotreload
```

Add this locally end-anchored alternative to the existing CTest selection:

```text
test_(vfs|async_loader|filewatch_backend|hotreload)$
```

The local `$` prevents future derived names such as `test_vfs_extra` from
silently entering the selection. Keep all 52 previous tests, emulator
environment, object checks, verbose output, `--no-tests=error`, 300-second
timeout, and failure propagation unchanged.

No dependency, skip, retry, status mask, or assertion relaxation is introduced.

## TDD and Verification

1. Run a PyYAML/native-selection contract against the old workflow. Require all
   four build targets, the exact alternative, future-prefix rejection, and
   previous 52 plus exactly these four = 56. Observe RED on the old build command.
2. Apply only the build-list and selection-regex edits. Require the unchanged
   contract to pass and compare the actual selected set with an explicit 56-name
   expected set.
3. Re-run native and cross focused tests; require 4/4, 17/7/36/26 case summaries,
   and no new skips.
4. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner CMake prerequisite. Require 56/56, all previous evidence, the new
   17/7/36/26 summaries, and exactly one existing QEMU ptrace setup skip.
6. Request independent read-only review, resolve adopted findings test-first,
   push the verified commits, and assert the exact-HEAD remote arm64 job log
   contains the same 56-test selection and all old/new evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, runtime asset
streaming and hot-reload design documents, and missing-capabilities inventory
without replacing history.

This is a selected 56-test suite, not full arm64 CTest. Material/scene texture
integration, glTF, world streaming, editor UI, rendering, LuaJIT, Snowflake
transport scenarios, QUIC, production deployment, GPU, and physical devices
remain outside this slice unless already covered by the existing 52 tests.
