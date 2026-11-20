# arm64 QEMU ECS Replication Tests Design

## Context

The arm64 lane currently selects exactly 38 tests. Four registered ECS tests
remain outside it: `test_ecs`, `test_ecs_system`, `test_ecs_replication`, and
`test_replication_target_contract`. This slice adds exactly those four and
produces a 42-test selection.

## Approaches

1. Extend the existing lane with the four registered tests. This reuses the
   current emulator and host-CMake contract and is the recommended minimal
   change.
2. Add a separate ECS lane. This duplicates the multiarch setup without providing
   needed isolation.
3. Select all ECS-prefixed or replication-prefixed tests without local anchors.
   This is rejected because future derived tests would silently change the
   promised selection.

## Existing Behavior and Baseline

The three executable tests have direct target registrations and generated QEMU
commands. The target contract is a host-CMake source-structure check and does
not execute target code.

- `test_ecs`: 45 cases for world cloning/replacement, entity identity and
  recycling, component storage/alignment, queries, edge caches, and malformed
  input handling.
- `test_ecs_system`: six cases for serial/parallel iteration, mutation,
  scheduling, empty workloads, and nested dispatch.
- `test_ecs_replication`: 35 cases for snapshots, schema hashing, transactional
  delta apply/rollback, entity identity, AOI sets, and hostile input rejection.
- `test_replication_target_contract`: verifies formal source ownership, absence
  of test-only fault injection in the production library, and removal of the
  legacy fragment-only target.

Unmodified native focused execution passes 4/4 with 45/6/35 case summaries and
`formal replication target contract passed` in 0.04 seconds. Unmodified cross
focused execution passes the same 4/4 and summaries in 0.16 seconds. No product
or test-source change is needed.

## CI Change

Append these targets to the existing arm64 build command:

```text
test_ecs test_ecs_system test_ecs_replication
```

The contract has no binary target. Add these locally end-anchored alternatives
to the existing CTest selection:

```text
test_ecs(_system|_replication)?$
test_replication_target_contract$
```

The local `$` tokens are required because the overall expression intentionally
has no global end anchor. They prevent future names such as
`test_ecs_system_extra` or `test_replication_target_contract_extra` from silently
entering this exact four-test addition.

Keep all 38 previous tests, emulator environment, object checks, verbose output,
`--no-tests=error`, 300-second timeout, and failure propagation unchanged. No
dependency, skip, retry, status mask, or assertion relaxation is introduced.

## TDD and Verification

1. Run a PyYAML/native-selection contract against the old workflow. Require the
   three build targets, both exact alternatives, local anchor rejection of
   future-prefixed names, and previous 38 plus exactly these four = 42. Observe
   RED on the old build command.
2. Apply only the build-list and selection-regex edits. Require the unchanged
   contract to pass and compare the actual selected set with an explicit 42-name
   expected set.
3. Re-run native and cross focused tests; require 4/4, 45/6/35 case summaries,
   the formal replication contract, and no new skips.
4. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner CMake prerequisite. Require 42/42, all previous evidence, the new
   45/6/35 summaries and contract, and exactly one existing QEMU ptrace setup
   skip.
6. Request independent read-only review, resolve adopted findings test-first,
   push the verified commits, and assert the exact-HEAD remote arm64 job log
   contains the same 42-test selection and all old/new evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, ECS
snapshot/replication/AOI design document, and missing-capabilities inventory
without replacing history.

This is a selected 42-test suite, not full arm64 CTest. Lua, world streaming,
editor, rendering, Snowflake transport scenarios, QUIC, production deployment,
GPU, and physical devices remain outside this slice unless already covered by
the existing 38 tests.
