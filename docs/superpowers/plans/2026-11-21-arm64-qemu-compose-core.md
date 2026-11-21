# arm64 QEMU Compose Core Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the five C Compose core test executables to the arm64 lane for an exact 200-test selection.

**Architecture:** Reuse the generated QEMU commands. Append five build targets and five flat exact-name alternatives; the full `-R` expression is already at CTest's 31-capture-group limit, so no new group may be added.

**Tech Stack:** C11, CMake/CTest, GitHub Actions YAML, Ubuntu 24.04 multiarch, QEMU user emulation, Python 3 + PyYAML contracts.

## Global Constraints

- Previous 195 + 5 = 200. Alternatives: `test_mycompose_tree$|test_mycompose_remember$|test_mycompose_store$|test_mycompose_runtime$|test_mycompose_async$`.
- Case counts: tree 28, remember 8, store 27, runtime 8, async 17, total 88. tree/remember/store/runtime link only `mycompose`; async links `mycompose_myui`, the dummy PAL and threads (no fork, no window, no GPU).
- The expression must keep at most 31 capture groups (`(` count). An extra group makes CTest print `RegularExpression::compile(): Too many parentheses` and select zero tests with exit code 0.
- Exclude `test_mycompose_myui`, `test_mycompose_widget_primitives`, all `test_mycompose_cpp20*`, `test_mycompose_gpu_*` and prefix-derived names. C++20 parity and GPU tests are separate slices.
- No product/test-source edits, dependencies, skips, retries, masks or assertion relaxation.
- Keep Vulkan-default/OpenGL-fallback product policy and the arm64 compile-only OpenGL configuration unchanged.
- Append documentation; preserve history. The user authorized verified commits directly on `master`; no PR.

---

### Task 1: Pin and implement the exact selection

**Files:**
- Create locally (ignored): `build-core-app-net/compose_selection_contract.py`
- Modify: `.github/workflows/ci.yml`, `docs/Build_Guide.md`

- [x] **Step 1:** Contract requires the build suffix `test_editor_plugin_manifest test_mycompose_tree test_mycompose_remember test_mycompose_store test_mycompose_runtime test_mycompose_async`, the final five flat alternatives, at most 31 capture groups, exact native sets 195/200 with a five-element difference, guide/workflow byte equality and a 200 intro count. Negative probes: `test_mycompose_myui`, `test_mycompose_widget_primitives`, `test_mycompose_cpp20`, `test_mycompose_gpu_opengl`, `test_mycompose_tree_extra`.
- [x] **Step 2:** Run it on the current workflow; require RED at `missing compose build targets`.
- [x] **Step 3:** Append the five targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 200, keeping 195 as history.
- [x] **Step 4:** Require the selection and lane-budget contracts GREEN, valid YAML and clean `git diff --check`.

### Task 2: Verify native and arm64 behavior

- [x] **Step 1:** Native focused 5/5 with 28/8/27/8/17.
- [x] **Step 2:** Clean Ubuntu 24.04 container: build the five arm64 targets and run under QEMU; require 5/5 with identical counts.
- [x] **Step 3:** Native full suite; require 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 200/200, all 20 per-test counts (5 compose + 15 editor), all contracts/e2e, one ptrace setup skip, no root-permission skip.

### Task 3: Review, push and record evidence

- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [ ] **Step 2:** Commit `ci: run arm64 compose core tests`, push to `origin/master`, monitor the full CI and Windows D3D12 workflows.
- [ ] **Step 3:** Download the raw arm64 log and assert 200 with all 20 per-test counts.
- [ ] **Step 4:** Append local/remote receipts and remaining gaps (Compose myui/widget integration, C++20 parity on arm64, GPU compose) to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.
