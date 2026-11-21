# Packer roundtrip under the arm64 cross emulator (259 → 260)

**Goal:** run `test_packer_roundtrip` in `lane-cross-aarch64-linux`. Its host driver `engine/tests/test_packer_roundtrip.cmake` launched `packer` and `verify_pak` directly in seven places.

## Task 1: driver
- [x] **Step 1:** Contract `build-core-app-net/packer_runner_contract.py`: all seven tool launches are prefixed by `${TOOL_RUNNER}`; the add_test passes `-DTOOL_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}`.
- [x] **Step 2:** RED (`7 of 7`); implement; GREEN; native pass.

## Task 2: lane
- [x] **Step 1:** arm64 QEMU trial: passes in 0.38 s.
- [x] **Step 2:** Selection contract `packer_selection_contract.py`: build list gains `packer verify_pak`, one flat exact alternative appended, 31 groups, native 259/260 with a one-element difference; RED then GREEN; Build_Guide 1.5 updated with the 259 paragraph kept as history.
- [x] **Step 3:** Native full 456/456.
- [x] **Step 4:** Clean non-root container 260/260; independent review; commit, push, monitor CI; assert the remote log at 260; record receipts.
