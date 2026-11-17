# Audio Drift Estimator Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Done

**Goal:** Estimate clock drift in ppm from confidence-gated fractional delay measurements.

**Architecture:** A bounded ring of accepted frame/delay/correlation samples feeds centered least-squares regression with relative frame indices.

**Tech Stack:** C11, existing audio types/results, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-drift-estimator-design.md`.
- Only create allocates; no wall-clock, tracker or platform dependency.
- Reject low-confidence, non-finite and non-increasing samples without changing state; estimates are failure-atomic.

### Task 1: API and RED

**Files:** create `engine/src/audio/audio_drift_estimator.{h,c}`, `engine/tests/test_audio_drift_estimator.c`; modify `engine/CMakeLists.txt`.

- [x] Write five tests for validation, known positive drift, rejection/failure, ring/reset and large-base negative drift.
- [x] Register `test_audio_drift_estimator` with headless/audio labels and a stub.
- [x] Configure/build; observed RED on create/destroy/reset/push/estimate/count.

### Task 2: Implementation

- [x] Implement validated ring storage, accepted-sample rules and relative-index regression with bounded outputs.
- [x] Run the test; observed 5 passed, 0 failed.

### Task 3: Verification and delivery

- [x] Run targeted mutations, ASan+UBSan, strict warnings and terminology scans; 25/26 caught, with the unreachable zero-denominator guard documented. Independent review is running.
- [x] Update audio design, implementation status, missing capabilities, spec and plan.
- [x] Commit as `audio: estimate clock drift from delay measurements`, then run `/tmp/full_trees.sh`; observed 427/427, 427/427 and 435/435. Push after review/green trees and inspect CI.

## Result

Five focused tests are GREEN and 25/26 mutations were caught. The ring test found and fixed an unsigned-underflow bug caused by using slot zero instead of the oldest ring frame as the regression base. A hand-computed non-collinear regression and differently sloped evicted samples strengthen the numerical oracle. ASan+UBSan and strict warnings are clean. Independent review found no Critical/Important issues, and its minor test/wording recommendations were addressed. Final full-tree results: build-core-app-master 427/427, build-editor-plugins 427/427 and build-core-app-net 435/435.
