# Editor plugin manifest CLI under the arm64 cross emulator (260 → 261)

**Goal:** run `test_editor_plugin_manifest_cli` in `lane-cross-aarch64-linux`. Its host driver ran `editor` directly through `cmake -E env`, and the lane did not build `editor`.

## Task 1: driver
- [x] **Step 1:** Contract `build-core-app-net/manifest_cli_runner_contract.py`: the single editor launch is prefixed by `${EDITOR_RUNNER}`; the add_test passes `-DEDITOR_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}`.
- [x] **Step 2:** RED against HEAD (`1 of 1`); implement; GREEN; native pass.

## Task 2: lane
- [x] **Step 1:** arm64 QEMU trial: passes in 0.16 s.
- [x] **Step 2:** Selection contract `manifest_cli_selection_contract.py`: build list gains `editor`, one flat exact alternative appended, 31 groups, native 260/261 with a one-element difference; RED then GREEN; Build_Guide 1.5 updated with the 260 paragraph kept as history.
- [x] **Step 3:** Native full 456/456.
- [x] **Step 4:** Clean non-root container 261/261; independent review; commit and push.
- [x] **Step 5:** Monitor CI; assert the remote log at 261; record receipts.
