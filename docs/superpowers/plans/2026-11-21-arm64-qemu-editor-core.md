# arm64 QEMU Editor Core Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add nine directly executable editor-core tests and their existing target contract to the arm64 lane for an exact 189-test selection.

**Architecture:** Reuse the nine generated QEMU commands and the host CMake target contract. Append the nine build targets after `test_world_stream_world`, then add one locally anchored editor alternative without changing earlier alternatives.

**Tech Stack:** C11, CMake/CTest, GitHub Actions YAML, Ubuntu 24.04 multiarch, QEMU user emulation, Python 3 + PyYAML for the local selection contract.

## Global Constraints

- Previous 179 + 10 = 189. The selected editor set is exactly `test_editor_(doc|cmd|scene|components|viewport|gizmo|assets|i18n|scene_textures)$|test_break_editor_target_contract$`.
- The nine executable tests contain 12/30/18/27/22/30/21/8/9 cases respectively, 177 in total; the target contract is host-side source-structure evidence, not arm64 execution evidence.
- Do not select `test_editor_audio`, `test_editor_shell`, plugin/CLI tests, Lua editor integration, font/platform tests, `test_editor_audio_sink`, or any GPU/window test. Those require separately reviewed dependencies or runtime adapters.
- No product/test-source edits, dependency changes, skips, retries, masks, or assertion relaxation.
- Keep Vulkan as the default product backend and OpenGL as the final fallback/render-comparison backend. The existing arm64 compile-only OpenGL configuration is unchanged.
- The user explicitly authorized verified commits directly on `master` and pushes to `origin/master`; no PR is required.
- Append documentation; do not overwrite historical evidence. Distinguish focused QEMU evidence from native UI, GPU, remote-session, and physical-device evidence.

---

### Task 1: Pin the exact editor-core selection with a failing contract

**Files:**
- Create locally (ignored verification helper): `build-core-app-net/editor_core_selection_contract.py`
- Test: `.github/workflows/ci.yml`, `docs/Build_Guide.md`

**Interfaces:**
- Consumes: the existing `lane-cross-aarch64-linux` build/run steps and native CTest registry.
- Produces: an exact 189-test set and a locally anchored editor alternative.

- [x] **Step 1:** Copy the verified world-selection helper and change its new target set and alternative to:

```python
targets = 'test_editor_doc test_editor_cmd test_editor_scene test_editor_components test_editor_viewport test_editor_gizmo test_editor_assets test_editor_i18n test_editor_scene_textures'
assert build.rstrip().endswith('test_world_stream_world ' + targets), 'missing editor-core build targets'
alternative = '|test_editor_(doc|cmd|scene|components|viewport|gizmo|assets|i18n|scene_textures)$|test_break_editor_target_contract$)'
assert run.count(alternative) == 1, 'missing exact editor-core alternative'
editor = set('test_editor_doc test_editor_cmd test_editor_scene test_editor_components test_editor_viewport test_editor_gizmo test_editor_assets test_editor_i18n test_editor_scene_textures test_break_editor_target_contract'.split())
expected = previous | physics | extended | animation | ai | audio | rule | kernel | world | editor
assert len(selected) == 189
```

  Add negative probes for `test_editor_audio`, `test_editor_shell`, `test_editor_plugin_cmds`, `test_editor_plugin_manifest_cli`, `test_editor_lua`, `test_editor_fonts`, `test_editor_audio_sink`, `test_editor_doc_extra`, and `test_break_editor_target_contract_x`.

- [x] **Step 2:** Run `python3 build-core-app-net/editor_core_selection_contract.py` on the unmodified workflow. Expected: FAIL with `missing editor-core build targets`; do not edit product code to address this CI-selection failure.

### Task 2: Add only the CI wiring and usage documentation

**Files:**
- Modify: `.github/workflows/ci.yml` (arm64 build target list and `-R` expression)
- Modify: `docs/Build_Guide.md` (mirror command and current-selection explanation)
- Modify: `docs/superpowers/plans/2026-11-21-arm64-qemu-editor-core.md` (check off completed evidence only)

- [x] **Step 1:** Append the nine executable targets after `test_world_stream_world` in both build commands and append the exact editor alternative at the end of both `-R` expressions. Do not reformat unrelated workflow jobs or historical guide sections.
- [x] **Step 2:** Replace the guide's single current-count paragraph with a 189-test paragraph: 179 prior tests plus nine editor executables (177 cases) plus one host target contract. Keep the preceding 164-test world-baseline paragraph as history.
- [x] **Step 3:** Run the selection contract and `python3 build-core-app-net/lane_budget_contract.py`. Expected: `exact 189-test editor-core selection and anchor contract passed`; lane budget reports 189 with the unchanged 600-second guard and 25-minute job cap.
- [x] **Step 4:** Run `git diff --check` and parse the workflow with PyYAML. Expected: no whitespace errors and valid YAML.

### Task 3: Verify unmodified behavior natively and under arm64 QEMU

**Files:**
- Verify only: the nine existing editor test sources and `engine/tests/test_break_editor_target_contract.cmake`

- [x] **Step 1:** Run the focused native expression; require 10/10 with no skip and per-test counts 12/30/18/27/22/30/21/8/9.
- [x] **Step 2:** In a clean Ubuntu 24.04 Podman container, reproduce the workflow's multiarch configure command and build the nine targets before changing CI. Run the focused expression under `qemu-aarch64 -L /`; require 10/10 and identical per-test counts. The host CMake contract is not executed by QEMU.
- [x] **Step 3:** Run the native full suite from `build-core-app-net`; require 456 tests, zero failures, and only the four established platform skips.
- [x] **Step 4:** Run the full arm64 selection in the clean container using the exact workflow environment and `timeout 600`; require 189/189, all 177 editor cases, and exactly one established ptrace setup skip. No retry or parallel CTest.

### Task 4: Independent review, push, and evidence closeout

**Files:**
- Modify: `docs/Implementation_Status.md` (new top entry)
- Modify: `docs/cross_engine/missing_capabilities.md` (append editor-core arm64 evidence and remaining boundaries)
- Modify: `docs/Build_Guide.md`, `docs/superpowers/plans/2026-11-21-arm64-qemu-editor-core.md` (final measured evidence)

- [x] **Step 1:** Obtain a read-only independent review of the final diff and exact selected set. Address every Critical/Important finding with a failing reproduction before a fix; record accepted Minor clarifications.
- [x] **Step 2:** Commit the reviewed CI/documentation change with `ci: run arm64 headless editor core tests`, push to `origin/master`, and monitor the arm64 job plus the overall workflow.
- [x] **Step 3:** Download the raw arm64 log and run the existing `assert_arm64_log.py` adapted for 189 and the nine editor counts. Require zero failed tests, all existing contract/e2e evidence, and exactly one ptrace setup skip.
- [x] **Step 4:** Append the local and remote receipts, review disposition, and explicit non-coverage: editor shell/UI, audio editor, plugins, Lua editor integration, font/platform behavior, Snowflake remote session, GPU/window rendering, and physical arm64 devices.
