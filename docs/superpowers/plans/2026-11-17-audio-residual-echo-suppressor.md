# Audio Residual Echo Suppressor Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Done

**Goal:** Add an allocation-free mono postprocessor that attenuates nonlinear residual echo after the existing NLMS canceller.

**Architecture:** Smoothed reference/error envelopes drive a bounded residual-path estimate and smooth downward expansion. An explicit near-end flag freezes adaptation and opens the gain; reference hangover covers echo tails.

**Tech Stack:** C11, existing audio result/numeric types, `audio_echo_canceller`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-17-audio-residual-echo-suppressor-design.md`.
- No allocation, locking, platform dependency or renderer access in the processing path.
- Preserve the existing AEC API and linear adaptation behavior.
- Document the caller-controlled near-end boundary and all verification limits.

### Task 1: Public state and RED

**Files:**
- Create `engine/src/audio/audio_residual_echo_suppressor.h`
- Create `engine/src/audio/audio_residual_echo_suppressor.c` (stub)
- Create `engine/tests/test_audio_residual_echo_suppressor.c`
- Modify `engine/CMakeLists.txt`

**Public API:** init, reset, `process_i16(reference,capture,frames,near_end_active)`, `gain_db`, `path_db`; caller-owned `AudioResidualEchoSuppressor` state and configuration.

- [x] Write seven tests covering validation/accessors, pass-through/hangover, real-AEC nonlinear residual suppression, near-end preservation, attack/release direction, per-frame path bounds, and chunk/reset/silence behavior.
- [x] Register the headless/audio test with `audio_residual_echo_suppressor.c` and `audio_echo_canceller.c`.
- [x] Configure `build-core-app-master` and build. Observed RED: six public symbols were undefined at link.

### Task 2: Implementation and GREEN

- [x] Implement validated state initialization, reset, 10 ms envelopes, reference gate/hangover, bounded path tracking, near-end freeze, smooth gain and i16 conversion.
- [x] Build and run `test_audio_residual_echo_suppressor`. Observed 7 passed, 0 failed.

### Task 3: Verification and delivery

- [x] Run targeted mutations, strengthening tests for observable survivors before production fixes. All 40 mutations were caught, including doubled path rise and held-reference reset.
- [x] Run ASan+UBSan, strict warnings and forbidden-terminology scans; request independent read-only review.
- [x] Update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md` and this plan without overwriting unrelated history.
- [x] Commit explicit paths as `audio: residual echo suppression after linear cancellation`, then run `/tmp/full_trees.sh`; observed 424/424, 424/424 and 432/432. Push only after review and all three trees pass, then inspect CI.

## Result

Seven focused tests are GREEN and all 40 targeted mutations were caught. ASan+UBSan and strict warnings are clean. Independent review drove exact path-rise measurements, reopening a closed gain under near-end control, finite residual measurements, continuous hangover input and complete configuration boundaries. Follow-up review found no remaining Critical/Important issues after the final explicit numeric cast. Final full-tree results: build-core-app-master 424/424, build-editor-plugins 424/424 and build-core-app-net 432/432.
