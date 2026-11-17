# AEC Residual Integration Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: In progress

**Goal:** Reuse the AEC near-end decision for residual suppression with exact per-frame behavior.

**Architecture:** Track the existing Geigel/hangover decision in AEC without altering adaptation, expose it read-only, and add a residual-pipeline convenience function that calls AEC then suppression for each frame.

**Tech Stack:** C11, existing AEC and residual suppressor, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-aec-residual-integration-design.md`.
- Existing PCM, weights, adaptation and standalone residual behavior remain unchanged.
- A detected frame is active even with zero hangover; zero-frame/invalid calls preserve state.
- No allocation, locks, threads or new CTest targets.

### Task 1: APIs and RED

**Files:** modify `engine/src/audio/audio_echo_canceller.h`, `engine/src/audio/audio_residual_echo_suppressor.h`, `engine/tests/test_audio_echo_canceller.c`, `engine/tests/test_audio_residual_echo_suppressor.c`.

- [ ] Declare `bool audio_echo_canceller_near_end_active(const AudioEchoCanceller *aec)` and the exact integrated function from the spec.
- [ ] Add `near_end_state_tracks_detection_hangover_and_reset` to the AEC suite, including disabled detection and zero-hangover detection.
- [ ] Add `integrated_pipeline_matches_manual_frame_steps` to the residual suite; compare PCM/path/gain/AEC weights with manual per-frame calls, verify a final near-end burst opens gain, and check invalid/zero calls.
- [ ] Build/run both existing targets; expected RED is undefined references only to the two new symbols. Existing suite sizes are AEC 8 and residual 7.

### Task 2: State tracking and per-frame pipeline

**Files:** modify `engine/src/audio/audio_echo_canceller.c`, `engine/src/audio/audio_residual_echo_suppressor.c`.

- [ ] Add/reset the AEC state flag; set it for a Geigel match or consumed hangover frame, clear it on ordinary adaptation, and add the accessor.
- [ ] Implement the integrated function as a frame loop calling the existing AEC, accessor and residual functions in that order; validate pointers before any mutation.
- [ ] Rebuild/run both targets; expected AEC 9/9 and residual 8/8.

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the original AEC/residual specs, and this slice's spec/plan.

- [ ] Mutate state assignment, zero-hangover behavior, reset clearing, wrapper ordering and wrapper routing; all must fail at least one focused suite.
- [ ] Run ASan+UBSan separately for both suites and strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` syntax checks for changed production/test sources.
- [ ] Run added-line terminology checks and independent read-only review; fix Critical/Important findings through RED-first tests.
- [ ] Incrementally update documents and commit as `audio: integrate AEC near-end state with residual suppression`.
- [ ] Run `/tmp/full_trees.sh`; expected 429/429, 429/429 and 437/437. Read actual counts, push `master` after green and inspect both new CI runs.

## Result

Design and plan only; implementation and RED have not started.
