# Offline Audio Editing Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Done

**Goal:** Add allocation-free mono/stereo i16 trim, cut, fade, normalize and mix primitives.

**Architecture:** Small in-place buffer functions with explicit validation, frame counts and clamped double-precision scaling.

**Tech Stack:** C11, existing audio types/results, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-edit-design.md`.
- No GUI, timeline, undo, file I/O, allocation or platform dependency.
- Validate ranges and pointers before mutation; zero-length behavior is defined.

### Task 1: API and RED

**Files:** create `engine/src/audio/audio_edit.{h,c}`, `engine/tests/test_audio_edit.c`; modify `engine/CMakeLists.txt`.

- [x] Write six tests for checked buffer arithmetic, validation, trim/cut, fades, normalization and mixing.
- [x] Register `test_audio_edit` with headless/audio labels and a stub.
- [x] Configure/build; observed RED on the five public editing functions.

### Task 2: Implementation

- [x] Implement validated trim/cut, linear fades, peak normalization and clamped prefix mixing.
- [x] Run the test; observed 6 passed, 0 failed.

### Task 3: Verification and delivery

- [x] Run targeted mutations, ASan+UBSan, strict warnings and terminology scans; 30/32 caught after the safety refactor, with two defensive survivors documented. Independent review and follow-up review report no remaining Critical/Important issues.
- [x] Update audio design, implementation status, missing capabilities, spec and plan.
- [x] Amend `audio: add offline pcm editing primitives`, then run `/tmp/full_trees.sh`; observed 429/429, 429/429 and 437/437. Push after review/green trees and inspect CI.

## Result

Six focused tests are GREEN and 30/32 mutations were caught. Checked spans and usize indexing protect large buffers on all platforms; fade rounding no longer narrows through long. Mix buffers are documented nonoverlapping, and full/empty/failure/stereo boundaries are covered. ASan+UBSan and strict warnings are clean. Independent review and follow-up review found no remaining Critical/Important issues. Final full-tree results: build-core-app-master 429/429, build-editor-plugins 429/429 and build-core-app-net 437/437.
