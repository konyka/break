# arm64 QEMU Physics Tests Design

## Context

The arm64 lane currently selects exactly 72 tests. Eight registered physics tests
remain outside it: `test_physics`, `test_physics_replay`, `test_physics_sync`,
`test_physics_hinge`, `test_physics_cone_twist`, `test_physics_identity`,
`test_ragdoll`, and `test_vehicle`. This slice adds exactly those eight and
produces an 80-test selection.

## Approaches

1. Extend the existing lane with the eight direct executable tests. This reuses
   generated QEMU commands and is the recommended minimal change.
2. Add a separate physics lane. This duplicates multiarch and emulator setup
   without providing needed isolation.
3. Select every `physics`-prefixed or physics-labelled test. This is rejected
   because cloth, rope, soft-body, destructible, slider, and future derived tests
   need their own baselines and boundaries.

## Existing Behavior and Baseline

All eight tests have direct executable-target registrations and generated QEMU
commands. They need no GPU, window system, or physical device.

- `test_physics`: 83 cases for the core rigid-body world.
- `test_physics_replay`: four cases for record/replay round trip, first-divergent
  step reporting, and malformed-input rejection.
- `test_physics_sync`: 13 cases for lockstep comparison, divergence latching,
  correction, delta encoding, baselines, and malformed-packet rejection.
- `test_physics_hinge`: three hinge-constraint cases.
- `test_physics_cone_twist`: eight cone-twist constraint cases.
- `test_physics_identity`: five cases for stale handles, slot reuse, tombstones,
  and generation exhaustion.
- `test_ragdoll`: ten ragdoll cases.
- `test_vehicle`: nine vehicle cases.

Unmodified native focused execution passes 8/8 with 83/4/13/3/8/5/10/9 case
summaries in 0.02 seconds. Unmodified cross focused execution passes the same 8/8
and summaries in 0.29 seconds. No product or test-source change is needed.

## Determinism Boundary

The replay and sync tests record and compare within a single process on one
architecture. Passing under arm64 therefore shows determinism *within* arm64. It
does not show that a recording made on x86-64 replays identically on arm64, or
that an x86-64 peer and an arm64 peer stay in lockstep. Cross-architecture
floating-point determinism is a separate claim that would need a test exchanging
recordings between architectures; this slice makes no such claim.

## CI Change

Append these eight targets to the existing arm64 build command:

```text
test_physics test_physics_replay test_physics_sync test_physics_hinge test_physics_cone_twist test_physics_identity test_ragdoll test_vehicle
```

Add this locally end-anchored alternative to the existing CTest selection:

```text
test_(physics(_replay|_sync|_hinge|_cone_twist|_identity)?|ragdoll|vehicle)$
```

The trailing `$` covers the whole optional suffix group, so names such as
`test_physics_extra`, `test_physics_slider`, and `test_ragdoll_extra` stay
excluded. Keep all 72 previous tests, emulator environment, object checks,
verbose output, `--no-tests=error`, 300-second timeout, and failure propagation
unchanged.

No dependency, skip, retry, status mask, or assertion relaxation is introduced.

## TDD and Verification

1. Run a PyYAML/native-selection contract against the old workflow. Require all
   eight build targets, the exact alternative, rejection of future and sibling
   physics names, and previous 72 plus exactly these eight = 80. Observe RED on
   the old build command.
2. Apply only the build-list and selection-regex edits. Require the unchanged
   contract to pass and compare the actual selected set with an explicit 80-name
   expected set.
3. Re-run native and cross focused tests; require 8/8, 83/4/13/3/8/5/10/9, and no
   new skips.
4. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner CMake prerequisite. Require 80/80, all previous evidence, the new
   case summaries, and exactly one existing QEMU ptrace setup skip.
6. Request independent read-only review, resolve adopted findings test-first,
   push the verified commits, and assert the exact-HEAD remote arm64 job log
   contains the same 80-test selection and all old/new evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, extended
physics design document, and missing-capabilities inventory without replacing
history.

This is a selected 80-test suite, not full arm64 CTest. Cloth, rope, soft-body,
destructible, slider, cross-architecture determinism, rendering, Snowflake
transport scenarios, QUIC, GPU, and physical devices remain outside this slice
unless already covered by the existing 72 tests.
