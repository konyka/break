# Audio Delay Tracker Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Done

**Goal:** Add confidence-gated, rate-limited tracking of fractional playback-to-capture delay.

**Architecture:** A small owner-thread state machine wraps the existing subframe estimator. Pushed-frame time controls slew; accepted/rejected runs control locking and loss of lock.

**Tech Stack:** C11, `audio_delay_estimator`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-delay-tracker-design.md`.
- Do not change the estimator or delay-line APIs.
- Allocate only in create; no worker thread, clock callback or platform dependency.

### Task 1: Public API and RED

**Files:** create `engine/src/audio/audio_delay_tracker.{h,c}`, `engine/tests/test_audio_delay_tracker.c`; modify `engine/CMakeLists.txt`.

- [x] Write five tests for validation, locking, rejection/hold/unlock, time-based slew, and chunk/reset/failure behavior.
- [x] Add `test_audio_delay_tracker` with headless/audio labels and a stub source.
- [x] Configure and build in `build-core-app-master`; observed RED on nine public symbols: create/destroy/reset/push/update and four accessors.

### Task 2: Implementation

- [x] Implement failure-atomic creation around the real estimator and all state/accessors.
- [x] Implement confidence gating, accepted runs, lock/hold/unlock, pushed-time slew and exact reset.
- [x] Run the test; observed 5 passed, 0 failed.

### Task 3: Verification and delivery

- [x] Run targeted mutations and strengthen observable gaps before production fixes; 34/37 caught, with three duplicate estimator-bound checks documented.
- [x] Run ASan+UBSan, strict warnings, terminology scans and request independent review.
- [x] Update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, spec and plan.
- [x] Commit as `audio: confidence-gated fractional delay tracking`, then run `/tmp/full_trees.sh`; observed 425/425, 425/425 and 433/433. Push after review and green trees, then inspect CI.

## Result

Five focused tests are GREEN and 34/37 mutations were caught. Tests cover inverted correlation, rejection before lock, recovery between rejected runs, bidirectional slew, zero elapsed time, zero-threshold estimator failure, immediate zero-hold unlock and reset with prior rejection. All numerical comparisons reject NaN. ASan+UBSan and strict warnings are clean. Independent review and follow-up review report no remaining Critical/Important issues. Final full-tree results: build-core-app-master 425/425, build-editor-plugins 425/425 and build-core-app-net 433/433.
