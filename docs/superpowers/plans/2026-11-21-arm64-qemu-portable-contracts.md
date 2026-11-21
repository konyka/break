# arm64 QEMU portable cross-platform contract slice (240 → 246)

**Goal:** run six existing executables that compile another platform's code through simulation headers or portable back ends: `test_glad_wgl_loader` (simulated WGL/DLL entry points; prints `PASS:`), `test_platform_wsi_lifecycle` (8; `SIMULATE_WAYLAND`), `test_d3d12_lifetime_hresult_contract` (7; no D3D12 calls), `test_net_loop_qnx` (17) and `test_qnx_perf_smoke` (3; QNX network loop on the poll back end over loopback), `test_break_plugin_unsupported` (1; fail-closed loader on platforms without dynamic loading).

**Excluded and why:** `test_core_app_assets` launches the arm64 asset baker through `system()`; qemu-user passes `execve` to the host kernel, so the host x86 `/bin/sh` runs and its exec of the arm64 baker fails with ENOEXEC because no aarch64 binfmt_misc handler is registered (`Exec format error`, 9 of 24 cases fail in the local container; whether the hosted runner registers binfmt is unverified). `test_platform_vk_surface_abi` needs Vulkan (no arm64 Vulkan dev package in the lane). `test_rhi_vk_probe`, `test_rhi_native`, `test_input_extended_single_cpu` (devices, CPU affinity).

**Constraint:** the complete `-R` expression already holds 31 capture groups; append flat exact alternatives `|name$` only.

## Task 1: selection contract
- [x] **Step 1:** Contract requires the build suffix `test_editor_shell` + six targets, the six alternatives last, at most 31 groups, no `Too many parentheses`, exact native sets 240/246 with a six-element difference, guide/workflow byte equality and a 246 intro count. Negative probes cover every excluded name and prefix extensions.
- [x] **Step 2:** Run on the current workflow; require RED at `missing portable contract build targets`.
- [x] **Step 3:** Append targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 246, keeping 240 as history.
- [x] **Step 4:** Selection and lane-budget contracts GREEN, valid YAML, clean `git diff --check`.

## Task 2: verification
- [x] **Step 1:** Native focused: all six pass (8/7/17/3/1 counted cases, glad prints `PASS:`).
- [x] **Step 2:** Clean Ubuntu 24.04 container: build and run the six arm64 targets under QEMU; 6/6 with identical counts. `test_core_app_assets` was tried alongside and fails as described, so it stays out.
- [x] **Step 3:** Native full suite; 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 246/246, all counted per-test numbers, all contracts/e2e, one platform setup skip, no root-permission skip, `assert_timeout_markers.py` OK.

## Task 3: review, push, receipts
- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [x] **Step 2:** Commit `ci: run arm64 portable contract tests`, push, monitor the full CI and Windows D3D12 workflows.
- [ ] **Step 3:** Download the raw arm64 log and assert 246 with all counted per-test numbers.
- [ ] **Step 4:** Append local/remote receipts and remaining gaps to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.
