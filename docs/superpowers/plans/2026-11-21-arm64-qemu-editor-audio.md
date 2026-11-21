# arm64 QEMU Editor Audio Test Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the existing pure-CPU `test_editor_audio` executable to the arm64 lane for an exact 190-test selection.

**Architecture:** Reuse the existing generated QEMU command and `break_editor_test` dependency closure. Append one build target and one exact-name alternative, without changing the editor-core alternative or adding an audio device/UI dependency.

**Tech Stack:** C11, CMake/CTest, GitHub Actions YAML, Ubuntu 24.04 multiarch, QEMU user emulation, Python 3 + PyYAML selection contracts.

## Global Constraints

- Previous 189 + 1 = 190; the new alternative is exactly `test_editor_audio$`.
- The test contains 23 cases covering PCM attachments, undo/redo, WAV import/export, waveform, loudness, true peak and limiting. It opens no audio device and starts no worker.
- Do not select `test_editor_audio_sink`, `test_editor_shell`, core_app audio/voice/device tests, or any `*_extra`/prefix-derived name.
- No product/test-source edits, new dependencies, skips, retries, masks, or assertion relaxation.
- Keep existing Vulkan-default/OpenGL-fallback product policy and the arm64 compile-only OpenGL configuration unchanged.
- Append documentation; preserve historical evidence and distinguish host/QEMU/native-device evidence.
- The user explicitly authorized verified commits directly on `master` and pushes to `origin/master`; no PR.

---

### Task 1: Pin and implement the exact selection

**Files:**
- Create locally (ignored): `build-core-app-net/editor_audio_selection_contract.py`
- Modify: `.github/workflows/ci.yml`
- Modify: `docs/Build_Guide.md`

- [x] **Step 1:** Write a contract that requires the build suffix `test_editor_scene_textures test_editor_audio`, the final alternative `|test_editor_audio$)`, exact old/new native CTest sets 189/190, and a one-element difference containing only `test_editor_audio`. Reject `test_editor_audio_sink`, `test_editor_audio_extra`, `test_editor_shell`, `test_core_app_audio_device`, and `test_core_app_voice`.
- [x] **Step 2:** Run the contract on the old workflow; require RED at the missing build target.
- [x] **Step 3:** Append `test_editor_audio` after `test_editor_scene_textures` in the workflow and guide build commands; append `|test_editor_audio$)` to both test expressions. Update the section title, intro and current-count paragraph to 190 while retaining the 189 editor-core baseline as history.
- [x] **Step 4:** Require the selection and lane-budget contracts GREEN, byte-identical workflow/guide commands, valid YAML and clean `git diff --check`.

### Task 2: Verify native and arm64 behavior

**Files:**
- Verify only: `engine/tests/test_editor_audio.c` and its existing CMake registration

- [x] **Step 1:** Run native `test_editor_audio`; require 23/23 and no skip.
- [x] **Step 2:** Build and run it in a clean Ubuntu 24.04 arm64 QEMU container; require 23/23 with the same test command shape as the other editor tests.
- [x] **Step 3:** Run the full native suite; require 456 tests, zero failures and only the four established platform skips.
- [x] **Step 4:** Execute the exact workflow build/test steps in a clean non-root container with source and build files owned by that user; require 190/190, audio 23/23, all previous editor counts, all old contracts/e2e, exactly one ptrace setup skip, and no root-permission skip.

### Task 3: Review, push and record evidence

**Files:**
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/superpowers/plans/2026-11-21-arm64-qemu-editor-audio.md`

- [x] **Step 1:** Obtain read-only independent review of the final diff, exact set, test dependency boundary and documentation. Reproduce and fix every Critical/Important issue before commit.
- [x] **Step 2:** Commit with `ci: run arm64 editor audio test`, push to `origin/master`, and monitor the complete CI and Windows D3D12 workflows.
- [x] **Step 3:** Download the raw arm64 job log and run `assert_arm64_log.py` for 190 with `test_editor_audio=23` plus all nine previous editor counts; require success.
- [x] **Step 4:** Append local/remote receipts and remaining gaps: editor audio UI/shell and real listening/device validation are not covered by this pure-CPU slice. Check off only completed steps.
