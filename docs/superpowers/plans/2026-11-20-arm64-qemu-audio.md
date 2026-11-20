# arm64 QEMU Audio Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the twenty-three audio tests to the arm64 lane for an exact 131-test selection.

**Architecture:** Reuse generated commands: twenty-two direct QEMU executables and one host `cmake -P` contract. Append twenty-two build targets after `test_break_ai_smart_object` and add one new locally anchored alternative.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Previous 108 + 23 = 131. Do not select `test_core_app_voice`, `test_core_app_voice_lane`, `test_editor_audio`, or `test_editor_audio_sink`.
- Alternative: `test_audio(_(extended|dsp|hrtf|capture|agc|noise_gate|echo_canceller|delay_estimator|fft|noise_suppressor|residual_echo_suppressor|delay_tracker|gcc_phat|drift_estimator|drift_resampler|drift_compensator|edit|voice_processor|voice_aligner|wav|realtime_contract))?$|test_voice_playback$`.
- No product/test-source edits, dependency, skip, retry, mask, or assertion relaxation.

---

### Task 1: CI selection and documentation

- [x] **Step 1:** Run `build-core-app-net/audio_selection_contract.py` on the old workflow; expected FAIL at `missing audio build targets`.
- [x] **Step 2:** Append the twenty-two targets and the alternative in `.github/workflows/ci.yml` and `docs/Build_Guide.md`.
- [x] **Step 3:** Re-run the contract; expected `exact 131-test audio selection and anchor contract passed`; confirm byte-identical regex.
- [x] **Step 4:** Focused native with the new `-R` (23/23) and unmodified cross baseline (23/23, 356 cases).
- [x] **Step 5:** Append status, design, and missing-capability evidence. Commit as `ci: run arm64 audio tests`.

### Task 2: Final verification and remote proof

- [ ] **Step 1:** Native full regression; require 455, zero failures, four established skips.
- [ ] **Step 2:** Clean-container workflow; require 131/131 and exactly one ptrace setup skip.
- [ ] **Step 3:** Read-only review; fix adopted findings. Fetch/rebase if needed and push.
- [ ] **Step 4:** `build-core-app-net/assert_arm64_log.py <log> 131` with all twenty-two `NAME=COUNT` pairs from the spec table. Record URLs, commit `docs: record arm64 audio CI results`, push.
