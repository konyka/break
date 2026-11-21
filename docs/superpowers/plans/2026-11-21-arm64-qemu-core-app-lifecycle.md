# core_app lifecycle tests under the arm64 cross emulator

**Goal:** let the twelve `test_core_app_lifecycle_*` tests run in a cross build. The driver `engine/tests/test_core_app_lifecycle.cmake` launches `core_app` directly; under a cross build that is an arm64 binary the host cannot execute. Add `CORE_APP_RUNNER` (the `CMAKE_CROSSCOMPILING_EMULATOR` list, empty natively), as `test_core_app_network.cmake` already does, and keep the `LD_PRELOAD` fault-injection block native-only: qemu-user passes the environment through, so the host loader rejects (and warns about) the arm64 preload while the guest loader may still apply it; whether the fault hooks and stderr checks hold under emulation is unverified.

## Task 1: driver
- [x] **Step 1:** Contract `build-core-app-net/lifecycle_runner_contract.py`: every direct `core_app` launch in the driver (four) is prefixed by `${CORE_APP_RUNNER}`; the `LD_PRELOAD` launch is not; the fault block is gated on `FAULT_SUPPORTED AND NOT CORE_APP_RUNNER` with an explicit `UNVERIFIED` message for the emulated case; all ten lifecycle `add_test` blocks (twelve tests, three from the input `foreach`) pass `-DCORE_APP_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}`.
- [x] **Step 2:** RED on the old driver (`core_app launch without CORE_APP_RUNNER: 4 of 4`).
- [x] **Step 3:** Implement; contract GREEN.
- [x] **Step 4:** Native: all twelve lifecycle tests pass and the load/unload run still executes fault injection (no `UNVERIFIED`).

## Task 2: arm64
- [x] **Step 1:** Clean Ubuntu 24.04 container: build `core_app`, its asset baker and the preload library for arm64; run the twelve lifecycle tests under QEMU; record which pass, their times, and the `UNVERIFIED` line.
- [x] **Step 2:** If they pass within budget, add the passing tests to `lane-cross-aarch64-linux` as flat exact alternatives (31-group limit) with a selection contract, update Build_Guide 1.5, run the full non-root lane, review, push, and record receipts. Otherwise document the gap.

## Task 3: docs and push
- [x] **Step 1:** Native full suite 456/456; independent review; commit, push, monitor CI; record receipts in `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`.
