# arm64 QEMU Extended Physics Tests Design

## Context

The arm64 lane currently selects exactly 80 tests, including eight rigid-body
physics tests. Five registered extended-physics tests remain outside it:
`test_physics_slider`, `test_cloth`, `test_rope`, `test_soft_body`, and
`test_destructible`. This slice adds exactly those five and produces an 85-test
selection. It completes arm64 coverage of every registered physics test.

## Approaches

1. Extend the existing lane with the five direct executable tests. This reuses
   generated QEMU commands and is the recommended minimal change.
2. Widen the existing physics alternative to a broad `physics` prefix. This is
   rejected: it would change an already-verified alternative and admit future
   derived names silently.
3. Add a separate lane. This duplicates the multiarch setup for no isolation gain.

## Existing Behavior and Baseline

All five tests have direct executable-target registrations
(`engine/CMakeLists.txt:5800-5828`) and generated QEMU commands. They need no GPU,
window system, or physical device.

Each test registers exactly one `RUN_TEST`, so every summary reads `1 passed`.
That count understates the content. Each case is a multi-assertion scenario:

| Test | Scenario | Assertions |
|---|---|---|
| `test_rope` | links nodes, refuses a full world | 10 |
| `test_cloth` | pins the top row and pulls it back | 24 |
| `test_destructible` | breaks only past the threshold | 30 |
| `test_physics_slider` | kills perpendicular offset, respects the limit | 12 |
| `test_soft_body` | restores offsets when stiff | 15 |

Unmodified native focused execution passes 5/5 in 0.01 seconds; unmodified cross
focused execution passes 5/5 in 0.15 seconds. No product or test-source change
is needed. A single scenario per module is thin coverage; this slice records that
fact and does not widen the tests.

## CI Change

Append these five targets to the existing arm64 build command:

```text
test_physics_slider test_cloth test_rope test_soft_body test_destructible
```

Add a new locally end-anchored alternative instead of editing the verified
rigid-body alternative:

```text
test_(physics_slider|cloth|rope|soft_body|destructible)$
```

The registry contains no other name matching these stems, and the `$` keeps
future derived names out. All 80 previous tests, emulator settings, object
checks, verbose output, `--no-tests=error`, 300-second timeout, and failure
propagation stay unchanged. No dependency, skip, retry, mask, or assertion
relaxation is introduced.

## TDD and Verification

1. Run the selection contract against the old workflow: require the five build
   targets, the exact alternative, rejection of `*_extra` names, and previous 80
   plus exactly these five = 85. Observe RED on the old build command.
2. Apply only the build-list and selection-regex edits; require GREEN against an
   explicit 85-name set.
3. Re-run native and cross focused tests; require 5/5 and no new skips.
4. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container.
   Require 85/85, all previous evidence, and exactly one existing ptrace skip.
6. Request independent read-only review, push, and assert the exact-HEAD remote
   arm64 log with the shared log checker.

## Documentation and Boundaries

Append evidence to the build guide, implementation status, extended physics
design document, and missing-capabilities inventory without replacing history.

This is a selected 85-test suite, not full arm64 CTest. Cross-build and
cross-architecture determinism, rendering, Snowflake transport scenarios, QUIC,
GPU, and physical devices remain outside it. Each extended module having a single
scenario is recorded as a coverage gap.
