# core_app voice lane under the arm64 cross emulator (258 → 259)

**Goal:** run `test_core_app_voice_lane` in `lane-cross-aarch64-linux`. Its host driver `engine/tests/test_core_app_voice_lane.cmake` launched `core_app` directly in two places, so a cross build could not run it.

## Task 1: driver
- [x] **Step 1:** Contract `build-core-app-net/voice_lane_runner_contract.py`: every core_app launch is prefixed by `${CORE_APP_RUNNER}`; the add_test passes `-DCORE_APP_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}`.
- [x] **Step 2:** RED on the old driver (`2 of 2`); implement; GREEN; native voice lane and lifecycle load/unload pass.

## Task 2: lane
- [x] **Step 1:** arm64 QEMU trial in a clean Ubuntu 24.04 container: passes in 4.38 s.
- [x] **Step 2:** Selection contract `voice_lane_selection_contract.py`: one flat exact alternative appended, build list unchanged, 31 groups, native 258/259 with a one-element difference; RED then GREEN; Build_Guide 1.5 updated with the 258 paragraph kept as history.
- [x] **Step 3:** Native full 456/456; clean non-root container 259/259.
- [x] **Step 4:** Independent review; commit, push, monitor CI; assert the remote log at 259; record receipts.
