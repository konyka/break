# Audio Delay-Line Crossfade Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

**Goal:** Add optional bounded crossfades to delay changes while preserving default immediate transitions.

**Architecture:** Keep the current ring and add old-target/fade counters. During a fade, evaluate old and new targets from the same history and blend by the current step; reject retarget/config/mode changes until completion.

**Tech Stack:** C11, existing `AudioDelayLine`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-delay-crossfade-design.md`.
- Zero duration is the default and preserves every old output and setter behavior.
- No allocation, future reads or hidden extra latency; in-place and arbitrary chunks remain valid.
- Active fades reject retarget/config/mode changes without state mutation.

### Task 1: API and RED

**Files:** modify `engine/src/audio/audio_delay_estimator.h`, `engine/tests/test_audio_delay_estimator.c`.

- [x] Declare the exact crossfade setter/accessor from the spec.
- [x] Add three tests for config/rejection/default behavior, hand-computed linear/in-place/chunked fades, and independent sinc/final/saturation behavior.
- [x] Build/run `test_audio_delay_estimator`; observed RED only on `audio_delay_line_set_crossfade_frames` and `audio_delay_line_crossfade_frames`.

### Task 2: Dual-reader implementation

**Files:** modify `engine/src/audio/audio_delay_estimator.c`.

- [x] Add fade state and validated setter/accessor; gate delay/sinc/config changes on no active fade.
- [x] Evaluate linear/sinc old and new targets with the current history; blend step `s=1..N` by `s/N`, decrement after each output and preserve the existing conversion/saturation rules.
- [x] Rebuild/run `test_audio_delay_estimator`; observed 21 passed, 0 failed (18 existing, three new).

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the original subframe/sinc-delay specs, and this slice's spec/plan.

- [x] Mutate fade weights, first/last steps, active-fade rejection and saturation; all six fail focused tests.
- [x] Run focused ASan+UBSan and strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` checks.
- [x] Run added-line terminology checks and independent read-only review; the fixture/documentation findings were fixed and re-review is Ready.
- [x] Incrementally update documents and commit as `audio: add crossfades to delay changes`.
- [x] Run `/tmp/full_trees.sh`; observed 430/430, 430/430 and 438/438. Verify actual counts, push `master` after green and inspect both new CI runs.

## Result

Implementation, review and verification are complete. Normal and ASan+UBSan tests pass 21/21, strict warnings and terminology checks are clean and all six mutants are killed. Independent review found a period-insensitive sinc fixture and documentation/test gaps; these were fixed and scoped re-review is Ready. The three full trees pass 430/430, 430/430 and 438/438. Remote CI inspection follows the push.
