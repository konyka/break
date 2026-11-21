# arm64 QEMU plugin loading, editor Lua and editor shell slice (236 → 240)

**Goal:** run four existing targets in `lane-cross-aarch64-linux`: `test_break_plugin` (11 cases; loads five real shared-library test plugins through the system plugin loader (dlopen of a verified memfd copy), including bad-ABI, register-failure and missing-entry fixtures, and proves an attacker fixture swapped in after verification is never loaded), `test_editor_plugin_load` (5; loads the editor fixture plugins), `test_editor_lua` (37; editor Lua console core) and `test_editor_shell` (headless editor shell; 233 cases natively, 185 in the lane because the 48 remote-session and network-panel cases compile only with `BREAK_ENABLE_SNOWFLAKE=ON`, which the lane does not configure; a 49th, purely local camera-pose case was wrongly inside that gate and was moved out first).

**Excluded and why:** `test_break_plugin_unsupported` (only meaningful on platforms without dynamic loading), `test_break_system_target_contract` and `test_editor_plugin_manifest_cli` (host CMake drivers), `test_core_app_voice` (sleep-polling, timing-sensitive).

**Constraint:** the complete `-R` expression already holds 31 capture groups; append flat exact alternatives `|name$` only.

## Task 1: selection contract
- [x] **Step 1:** Contract requires the build suffix `test_core_app_runtime` + four targets, the four alternatives last, at most 31 groups, no `Too many parentheses`, exact native sets 236/240 with a four-element difference, guide/workflow byte equality and a 240 intro count. Negative probes cover every excluded name and prefix extensions.
- [x] **Step 2:** Run on the current workflow; require RED at `missing plugin/lua/shell build targets`.
- [x] **Step 3:** Append targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 240, keeping 236 as history.
- [x] **Step 4:** Selection and lane-budget contracts GREEN, valid YAML, clean `git diff --check`.

## Task 2: verification
- [x] **Step 1:** Native focused 4/4 with 11/5/37/233 cases.
- [x] **Step 2:** Clean Ubuntu 24.04 container: build and run the four arm64 targets under QEMU; require 4/4 with 11/5/37 cases and the shell difference fully explained by the Snowflake-gated remote cases (184 before the camera-pose fix, 185 after).
- [x] **Step 3:** Native full suite; require 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 240/240, all counted per-test numbers, all contracts/e2e, one ptrace setup skip, no root-permission skip, `assert_timeout_markers.py` OK, and the lane still well inside its 600 s guard.

## Task 3: review, push, receipts
- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [x] **Step 2:** Commit `ci: run arm64 plugin, editor lua and shell tests`, push, monitor the full CI and Windows D3D12 workflows.
- [ ] **Step 3:** Download the raw arm64 log and assert 240 with all counted per-test numbers.
- [ ] **Step 4:** Append local/remote receipts and remaining gaps to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.
