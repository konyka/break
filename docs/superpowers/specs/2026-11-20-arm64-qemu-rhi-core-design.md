# arm64 QEMU RenderGraph and RHI Core Tests Design

## Context

The arm64 lane currently selects exactly 56 tests. Five registered headless
RenderGraph/RHI tests remain outside it: `test_render_graph`, `test_rhi_dispatch`,
`test_rhi_capabilities`, `test_rhi_error_contract`, and
`test_rhi_frame_lifecycle_contract`. This slice adds exactly those five and
produces a 61-test selection.

## Approaches

1. Extend the existing lane with the five direct executable tests. This reuses
   generated QEMU commands and is the recommended minimal change.
2. Add a separate RHI lane. This duplicates multiarch and emulator setup without
   providing needed isolation.
3. Select every RHI-prefixed test. This is rejected because shader tools, runtime
   selection, WSI, backend-specific checks, and GPU paths require separate
   boundaries.

## Existing Behavior and Baseline

All five tests have direct executable-target registrations and generated QEMU
commands. They use headless or stubbed RHI paths and need no physical graphics
device.

- `test_rhi_dispatch`: 44 dispatch checks.
- `test_rhi_capabilities`: 59 cases for device-scoped handles, frame ownership,
  lifecycle results, resource validation, damage history, and safe defaults.
- `test_rhi_error_contract`: seven cases for error-family mapping and sticky
  device/surface/sync failure behavior.
- `test_rhi_frame_lifecycle_contract`: five cases for acquire/submit/present/drain
  aliases, readiness, lost/out-of-date handling, and per-thread in-flight rules.
- `test_render_graph`: 22 cases for graph compilation, topological ordering,
  dead-pass culling, resource ownership, execution, reset, and statistics.

Unmodified native focused execution passes 5/5 with 44 dispatch checks and
59/7/5/22 case summaries in 0.01 seconds. Unmodified cross focused execution
passes the same 5/5 and evidence in 0.13 seconds. No product or test-source
change is needed.

## CI Change

Append these five targets to the existing arm64 build command:

```text
test_render_graph test_rhi_dispatch test_rhi_capabilities test_rhi_error_contract test_rhi_frame_lifecycle_contract
```

Add these locally end-anchored alternatives to the existing CTest selection:

```text
test_render_graph$
test_rhi_(dispatch|capabilities|error_contract|frame_lifecycle_contract)$
```

The local `$` tokens prevent future derived names from silently entering the
selection. Keep all 56 previous tests, emulator environment, object checks,
verbose output, `--no-tests=error`, 300-second timeout, and failure propagation
unchanged.

No dependency, skip, retry, status mask, or assertion relaxation is introduced.

## TDD and Verification

1. Run a PyYAML/native-selection contract against the old workflow. Require all
   five build targets, both exact alternatives, future-prefix rejection, and
   previous 56 plus exactly these five = 61. Observe RED on the old build command.
2. Apply only the build-list and selection-regex edits. Require the unchanged
   contract to pass and compare the actual selected set with an explicit 61-name
   expected set.
3. Re-run native and cross focused tests; require 5/5, 44 dispatch checks, the
   59/7/5/22 case summaries, and no new skips.
4. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner CMake prerequisite. Require 61/61, all previous evidence, the new
   dispatch and case summaries, and exactly one existing QEMU ptrace setup skip.
6. Request independent read-only review, resolve adopted findings test-first,
   push the verified commits, and assert the exact-HEAD remote arm64 job log
   contains the same 61-test selection and all old/new evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, RHI runtime
backend design document, and missing-capabilities inventory without replacing
history.

This is a selected 61-test suite using headless/stubbed paths, not full arm64
CTest. Runtime backend selection/rollout, WSI integration, shader tooling, real
OpenGL/Vulkan execution, visual parity, GPU, and physical devices remain outside
this slice unless already covered by the existing 56 tests.
