# arm64 QEMU editor/core_app CPU slice (230 → 236)

**Goal:** run six pure-CPU targets in `lane-cross-aarch64-linux`: `test_editor_input_script` (8 cases), `test_editor_settings` (7; environment variables only feed path resolution, real save/load goes to a `test_tmp` directory), `test_editor_fonts` (7; simulated distro font layouts under a temp root plus the bundled JetBrains Mono / Noto Sans SC; the lane has no arm64 fontconfig, so the real-system case falls back to the built-in path table: with the build dir a direct child of the checkout root it finds the two bundled faces through the exe-relative lookup (`2 candidates, cjk` in a clean container; the focused run under /tmp finds 0), and on the hosted runner the table may add preinstalled DejaVu/Liberation faces and does not exercise system font discovery), `test_editor_audio_sink` (5; FAKE audio backend, no device), `test_core_app_mesh` (3) and `test_core_app_runtime` (60; reads `assets/core_app`, has a threaded audio stress case, no fork).

**Excluded and why:** `test_core_app_voice` (~12 s natively, polls with `time_sleep_us`, timing-sensitive under emulation; not measured under QEMU), `test_core_app_voice_lane`, core_app lifecycle/asset contracts (driver scripts and host CMake), editor shell/Lua, plugin dynamic loading.

**Constraint:** the complete `-R` expression already holds 31 capture groups; append flat exact alternatives `|name$` only.

## Task 1: selection contract
- [x] **Step 1:** Contract requires the build suffix `test_rhi_golden_parity` + six targets, the six alternatives last, at most 31 groups, no `Too many parentheses`, exact native sets 230/236 with a six-element difference, guide/workflow byte equality and a 236 intro count. Negative probes cover every excluded name and prefix extensions.
- [x] **Step 2:** Run on the current workflow; require RED at `missing editor/core_app cpu build targets`.
- [x] **Step 3:** Append targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 236, keeping 230 as history.
- [x] **Step 4:** Selection and lane-budget contracts GREEN, valid YAML, clean `git diff --check`.

## Task 2: verification
- [x] **Step 1:** Native focused 6/6 with 8/7/7/5/3/60 cases.
- [x] **Step 2:** Clean Ubuntu 24.04 container: build and run the six arm64 targets under QEMU; require 6/6 with identical counts.
- [x] **Step 3:** Native full suite; require 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 236/236, all counted per-test numbers, all contracts/e2e, one ptrace setup skip, no root-permission skip, `assert_timeout_markers.py` OK.

## Task 3: review, push, receipts
- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [x] **Step 2:** Commit `ci: run arm64 editor and core_app cpu tests`, push, monitor the full CI and Windows D3D12 workflows.
- [ ] **Step 3:** Download the raw arm64 log and assert 236 with all counted per-test numbers.
- [ ] **Step 4:** Append local/remote receipts and remaining gaps to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.
