# arm64 QEMU Editor Plugin Core Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add five pure-CPU editor plugin-core test executables to the arm64 lane for an exact 195-test selection.

**Architecture:** Reuse the existing generated QEMU commands and `break_editor_test` dependency closure. Append five build targets and one locally anchored plugin alternative; do not include the editor executable, dynamic plugin loader or shell.

**Tech Stack:** C11, CMake/CTest, GitHub Actions YAML, Ubuntu 24.04 multiarch, QEMU user emulation, Python 3 + PyYAML contracts.

## Global Constraints

- Previous 190 + 5 = 195; alternative: `test_editor_plugin_cmds$|test_editor_plugin_host$|test_editor_plugin_sections$|test_editor_plugin_panels$|test_editor_plugin_manifest$`.
- Case counts are cmds 7, host 8, sections 5, panels 9, manifest 10, total 39.
- Exclude `test_editor_plugin_manifest_cli`, `test_editor_plugin_load`, `test_editor_flow`, `test_editor_shell`, UI/device tests and all prefix-derived names.
- No product/test-source edits, dependencies, skips, retries, masks, or assertion relaxation.
- Keep Vulkan-default/OpenGL-fallback product policy and arm64 compile-only OpenGL configuration unchanged.
- Append documentation; preserve historical evidence and distinguish pure model tests from dynamic loading/UI/device evidence.
- The user authorized verified commits directly on `master` and pushes to `origin/master`; no PR.

---

### Task 1: Pin and implement the exact selection

**Files:**
- Create locally (ignored): `build-core-app-net/editor_plugin_selection_contract.py`
- Modify: `.github/workflows/ci.yml`
- Modify: `docs/Build_Guide.md`

- [ ] **Step 1:** Require build suffix `test_editor_audio test_editor_plugin_cmds test_editor_plugin_host test_editor_plugin_sections test_editor_plugin_panels test_editor_plugin_manifest`, final alternative `|test_editor_plugin_cmds$|test_editor_plugin_host$|test_editor_plugin_sections$|test_editor_plugin_panels$|test_editor_plugin_manifest$)`, exact old/new native sets 190/195, and a five-element difference. Add negative probes for manifest_cli, plugin_load, flow, shell and prefix-derived names.
- [ ] **Step 2:** Run the contract on the old workflow; require RED at the missing plugin build targets.
- [ ] **Step 3:** Append the five targets after `test_editor_audio` and the alternative after `test_editor_audio$` in both workflow and guide. Update title, intro and current-count paragraph to 195 while retaining the 190 editor-audio baseline as history.
- [ ] **Step 4:** Require selection and lane-budget contracts GREEN, byte-identical commands, valid YAML and clean `git diff --check`.

### Task 2: Verify native and arm64 behavior

**Files:**
- Verify only: the five existing `engine/tests/test_editor_plugin_*.c` registrations

- [ ] **Step 1:** Run the five native tests; require 5/5 and 7/8/5/9/10 cases.
- [ ] **Step 2:** Build and run the same five in a clean arm64 QEMU container; require 5/5 and identical counts.
- [ ] **Step 3:** Run the full native suite; require 456 tests, zero failures and only the four established platform skips.
- [ ] **Step 4:** Execute exact workflow build/test steps in a clean non-root container; require 195/195, all five plugin counts, all previous editor counts, old contracts/e2e, exactly one ptrace setup skip and no root-permission skip.

### Task 3: Review, push and record evidence

**Files:**
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/superpowers/plans/2026-11-21-arm64-qemu-editor-plugin-core.md`

- [ ] **Step 1:** Obtain read-only independent review of the final diff, exact set, dependencies and docs; reproduce and fix every Critical/Important issue.
- [ ] **Step 2:** Commit with `ci: run arm64 editor plugin core tests`, push to `origin/master`, and monitor complete CI and Windows D3D12 workflows.
- [ ] **Step 3:** Download the raw arm64 log and assert 195 with all five plugin counts and all previous editor counts.
- [ ] **Step 4:** Append local/remote receipts and remaining dynamic-loader, CLI, shell/UI and physical-device gaps. Check off only completed steps.
