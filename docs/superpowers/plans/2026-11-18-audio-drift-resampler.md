# Audio Drift Resampler Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Done

**Goal:** Add a streaming mono resampler whose ratio can be driven by clock-drift estimates.

**Architecture:** Absolute input/output positions and one previous sample provide allocation-free linear interpolation with arbitrary chunks and dynamic ratios.

**Tech Stack:** C11, existing audio types/results, `audio_drift_estimator`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-drift-resampler-design.md`.
- No allocation or platform dependency; input/output must not overlap.
- Validate output capacity before state changes; reset preserves the configured ratio.

### Task 1: API and RED

**Files:** create `engine/src/audio/audio_drift_resampler.{h,c}`, `engine/tests/test_audio_drift_resampler.c`; modify `engine/CMakeLists.txt`.

- [x] Write six tests for validation, identity/decimation, upsampling/chunking, a live ratio transition, primed-state capacity/reset and real-estimator ratio integration.
- [x] Register `test_audio_drift_resampler` with headless/audio labels and a stub.
- [x] Configure/build; observed RED on init/reset/set_ratio/ratio/output_capacity/process.

### Task 2: Implementation

- [x] Implement validated state, safe capacity bound, streaming interpolation, dynamic ratio and actual output counts.
- [x] Run the test; observed 6 passed, 0 failed.

### Task 3: Verification and delivery

- [x] Run targeted mutations, ASan+UBSan, strict warnings and terminology scans; 21/26 caught, with five specific survivors documented. Independent review findings were addressed; follow-up review is pending.
- [x] Update audio design, implementation status, missing capabilities, spec and plan.
- [x] Amend `audio: resample captured audio for clock drift`, then run `/tmp/full_trees.sh`; observed 428/428, 428/428 and 436/436. Push after review/green trees and inspect CI.

## Result

Six focused tests are GREEN, including exact identity/decimation, known half-position upsampling, a hand-calculated live 0.5-to-2.0 transition, primed-state capacity atomicity, reset/fresh equivalence and a real 50 ppm estimate driving a 16-to-15-output conversion. ASan+UBSan and strict warnings are clean. Independent review and follow-up review report no remaining Critical/Important issues. Final full-tree results: build-core-app-master 428/428, build-editor-plugins 428/428 and build-core-app-net 436/436.
