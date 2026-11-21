# arm64 QEMU RHI CPU slice (225 → 230)

**Goal:** run five pure-CPU RHI tests in `lane-cross-aarch64-linux`: `test_rhi_rollout_log` (rollout structured log, prints `OK`), `test_rhi_runtime_select` (49 runtime backend-selection checks with injected probes, prints `OK: 49 ...`), `test_rhi_fault_injection` (6 cases on the in-memory device from `rhi_test_device_create()`, built with `ENGINE_RHI_TEST`; `engine_rhi_headless` only supplies backend stubs that refuse work), `test_rhi_wsi_attach` (3 cases, header-inline WSI attach state machine) and `test_rhi_golden_parity` (CPU MAE/max comparison of committed Vulkan vs OpenGL golden PPMs in `engine/tests/golden`; no rendering).

**Excluded and why:** `test_rhi_vk_probe`, `test_rhi_device_type`, `test_rhi_native` (real Vulkan/GPU); `test_rhi_multi_backend_symbols` (symbol shape of the multi-backend build, not the lane's OpenGL build); RHI host CMake contracts (`*_contract`, `test_rhi_metal_ownership`).

**Constraint:** the complete `-R` expression already holds 31 capture groups; append flat exact alternatives `|name$` only.

## Task 1: selection contract
- [x] **Step 1:** Contract requires the build suffix `test_wayland_touch` + five targets, the five alternatives last, at most 31 groups, no `Too many parentheses`, exact native sets 225/230 with a five-element difference, guide/workflow byte equality and a 230 intro count. Negative probes cover every excluded name and a prefix extension.
- [x] **Step 2:** Run on the current workflow; require RED at `missing rhi cpu build targets`.
- [x] **Step 3:** Append targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 230, keeping 225 as history.
- [x] **Step 4:** Selection and lane-budget contracts GREEN, valid YAML, clean `git diff --check`.

## Task 2: verification
- [x] **Step 1:** Native focused 5/5 (6/3 counted cases; three print only `OK`).
- [x] **Step 2:** Clean Ubuntu 24.04 container: build and run the five arm64 targets under QEMU; require 5/5 with identical output, golden MAE values identical to native.
- [x] **Step 3:** Native full suite; require 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 230/230, all counted per-test numbers, all contracts/e2e, one ptrace setup skip, no root-permission skip, `assert_timeout_markers.py` OK.

## Task 3: review, push, receipts
- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [x] **Step 2:** Commit `ci: run arm64 rhi cpu tests`, push, monitor the full CI and Windows D3D12 workflows.
- [x] **Step 3:** Download the raw arm64 log and assert 230 with all counted per-test numbers.
- [x] **Step 4:** Append local/remote receipts and remaining gaps to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.
