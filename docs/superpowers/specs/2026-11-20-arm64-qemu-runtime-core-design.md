# arm64 QEMU Runtime Core Tests Design

## Context

The arm64 lane currently selects exactly 33 crash, update, security, network,
aspect, and core_app tests. `test_runtime_core` and
`test_runtime_core_target_contract` are registered in the cross tree but are not
built or run by that lane. This slice adds only those two tests, producing an
exact 35-test selection.

## Approaches

1. Extend the existing lane with the two runtime_core tests. This reuses the
   configured emulator and dependency chain and is the recommended minimal
   change.
2. Add a separate runtime lane. This would duplicate the multiarch setup for no
   isolation benefit because both tests are already registered in the existing
   tree.
3. Run the full cross CTest suite. This is rejected: many unrelated tests need
   separate target-tool, asset, platform, or device adaptation.

## Existing Behavior and Baseline

`test_runtime_core` links the formal `runtime_core` static library and contains
nine lifecycle-coordinator cases. CMake's executable-target emulation runs it
with the existing `CMAKE_CROSSCOMPILING_EMULATOR`.

`test_runtime_core_target_contract` is a host CMake source-structure check. It
reads `engine/CMakeLists.txt`, does not execute target code, and needs no QEMU,
NM, or compile runner.

Unmodified native focused execution passes 2/2 with nine unit cases and the
target contract. Unmodified cross focused execution, using the workflow's full
multiarch dependency step, also passes 2/2 with the same evidence. No product or
test-source change is needed.

## CI Change

Append `test_runtime_core` to the existing arm64 build target command. The
contract has no binary target to append.

Add this single alternative to the existing CTest selection:

```text
test_runtime_core($|_target_contract)
```

The end anchor inside the alternative is intentional: it excludes
`test_runtime_io`, `test_runtime_reload`, `test_runtime_facade`, and every other
runtime-prefixed test. Keep the existing outer anchors, verbose output,
`--no-tests=error`, 300-second timeout, emulator environment, object checks, and
failure propagation unchanged.

No dependency, skip, retry, filter beyond the two named tests, status mask, or
assertion relaxation is introduced.

## TDD and Verification

1. Run a PyYAML/native-selection contract against the old workflow. Require the
   new build target, exact regex alternative, and previous 33 plus exactly these
   two tests = 35; observe RED on the old build command.
2. Apply only the build-list and selection-regex edits, then require the same
   contract to pass. Confirm the actual selected set contains no other runtime
   tests.
3. Re-run native focused and cross focused tests; require nine unit cases, the
   target contract, and 2/2 CTest success without new skips.
4. Run the native full suite and require 455 tests, zero failures, and only the
   four established platform skips.
5. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner-provided CMake prerequisite. Require 35/35, all previous evidence,
   nine runtime_core cases, the runtime_core contract, and exactly one existing
   QEMU ptrace setup skip.
6. Request independent read-only review, push the verified commits, and inspect
   the exact-HEAD remote arm64 job log for the same 35-test and summary evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, missing
capabilities inventory, and runtime overview. Do not replace existing history.

This is a selected 35-test suite, not full arm64 CTest. Runtime IO/reload/facade,
Lua, ECS, Snowflake transport scenarios, QUIC, production deployment, GPU, and
physical devices remain outside this slice unless already covered by the
existing 33 tests.
