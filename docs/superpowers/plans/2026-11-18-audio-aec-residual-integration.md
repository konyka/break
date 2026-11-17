# AEC Residual Integration Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

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

- [x] Declare `bool audio_echo_canceller_near_end_active(const AudioEchoCanceller *aec)` and the exact integrated function from the spec.
- [x] Add `near_end_state_tracks_detection_hangover_and_reset` to the AEC suite, including disabled detection, zero-hangover detection and full hangover expiry.
- [x] Add `integrated_pipeline_matches_manual_frame_steps` to the residual suite; compare PCM/path/gain/AEC weights with manual per-frame calls, verify a final near-end burst opens gain, and check invalid/zero calls with a diagnostic frame.
- [x] Build/run both existing targets; observed RED only on the two new symbols. Existing suite sizes were AEC 8 and residual 7.

### Task 2: State tracking and per-frame pipeline

**Files:** modify `engine/src/audio/audio_echo_canceller.c`, `engine/src/audio/audio_residual_echo_suppressor.c`.

- [x] Add/reset the AEC state flag; set it for a Geigel match or consumed hangover frame, clear it on ordinary adaptation, and add the accessor.
- [x] Implement the integrated function as a frame loop calling the existing AEC, accessor and residual functions in that order; validate pointers before any mutation.
- [x] Rebuild/run both targets; observed AEC 9/9 and residual 8/8.

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the original residual spec, and this slice's spec/plan.

- [x] Mutate state assignment, zero-hangover behavior, reset clearing, wrapper ordering/routing and the suppressor guard; all fail at least one focused suite.
- [x] Run ASan+UBSan separately for both suites and strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` syntax checks for changed production/test sources.
- [x] Run added-line terminology checks and independent read-only review; the test-evidence findings were fixed and re-review is Ready.
- [x] Incrementally update documents and commit as `audio: integrate AEC near-end state with residual suppression`.
- [x] Run `/tmp/full_trees.sh`; observed 429/429, 429/429 and 437/437. Read actual counts, push `master` after green and inspect both new CI runs.

## Result

Implementation, review and verification are complete. AEC passes 9/9 and residual suppression 8/8 in normal and ASan+UBSan runs; strict warnings and terminology checks are clean and all seven mutants are killed. Independent review found test-evidence gaps, which were fixed; scoped re-review is Ready with no remaining issues. The three full trees pass 429/429, 429/429 and 437/437. Remote CI inspection follows the push.
