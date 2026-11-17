# Audio GCC-PHAT Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Done

**Goal:** Add an allocation-free-after-create GCC-PHAT delay estimator with fractional peak interpolation.

**Architecture:** Mirrored input histories feed zero-padded real FFTs. Normalized cross-spectrum phase is inverse-transformed, searched at allowed lags and parabolically refined.

**Tech Stack:** C11, `audio_fft`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-gcc-phat-design.md`.
- No change to existing estimator/tracker behavior and no new dependency.
- Reject configurations whose required FFT exceeds 65536; only create allocates.

### Task 1: API and RED

**Files:** create `engine/src/audio/audio_gcc_phat.{h,c}`, `engine/tests/test_audio_gcc_phat.c`; modify `engine/CMakeLists.txt`.

- [x] Write six tests for validation/readiness/silence, direct FFT-size and exact-tie contracts, exact and inverted delays, fractional noisy signals, deterministic repetition, chunk/reset and a direct time-domain lag reference.
- [x] Register `test_audio_gcc_phat` with headless/audio labels and a stub.
- [x] Configure/build; observed RED on create/destroy/reset/push/estimate.

### Task 2: Implementation

- [x] Implement validated histories, FFT planning/scratch, phase-normalized cross spectrum, inverse peak search and guarded parabolic refinement.
- [x] Run `test_audio_gcc_phat`; observed 6 passed, 0 failed.

### Task 3: Verification and delivery

- [x] Run targeted mutations, ASan+UBSan, strict warnings and terminology scans; 22/27 caught after direct internal contracts and extreme-input regressions. Independent review and follow-up review report no remaining Critical/Important issues.
- [x] Update audio design, implementation status, missing capabilities, spec and plan.
- [x] Amend `audio: gcc-phat delay estimation with subframe peaks`, then run `/tmp/full_trees.sh`; observed 426/426, 426/426 and 434/434. Push after review/green trees and inspect CI.

## Result

Six focused tests are GREEN, including direct FFT-size and exact-tie contracts, an impulse peak of 1, exact endpoints, inverted sign, a 1000-frame lag and noisy fractional delays within 0.25 frame. Reset is tested for immediate and history-minus-one failure. Extreme-u32 inputs cannot wrap into acceptance. ASan+UBSan and strict warnings are clean. Mutation coverage is 22/27 with five specific survivors documented. Independent review and follow-up review found no remaining Critical/Important issues. Final full-tree results: build-core-app-master 426/426, build-editor-plugins 426/426 and build-core-app-net 434/434.
