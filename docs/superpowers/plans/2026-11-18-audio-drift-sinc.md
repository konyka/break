# Audio Drift Sinc Mode Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

**Goal:** Add a causal, allocation-free sinc quality mode with explicit eight-input-frame latency to the clock-drift resampler.

**Architecture:** Add a fixed 32-entry absolute-position history to the caller-owned state. Preserve the existing linear fast path and schedule, gate sinc outputs on eight frames of lookahead, and use history-based linear interpolation only when draining a sinc backlog after a mode switch.

**Tech Stack:** C11, existing audio types/results, `test_audio_drift_resampler`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-drift-sinc-design.md`.
- Default linear output, ratio semantics and existing API behavior remain unchanged.
- No allocation, future reads beyond the current input, hidden latency or out-of-range i16 conversion.
- Validate capacity before any output or state mutation; reset preserves ratio and mode.

### Task 1: Public API and incremental RED

**Files:** modify `engine/src/audio/audio_drift_resampler.h`, `engine/tests/test_audio_drift_resampler.c`.

- [x] Declare `set_sinc`, `sinc` and `sinc_extra_delay`; add mode/reset, delayed integer/decimation, independent-kernel/chunk, mode-switch/capacity, tone/DC and full-scale saturation tests.
- [x] Extend state-equality assertions to cover `sinc` and all 32 history bytes.
- [x] Run `cmake --build build-core-app-master --target test_audio_drift_resampler -j2 && ./build-core-app-master/test_audio_drift_resampler`; observed RED only on the three new symbols.

### Task 2: Minimal implementation and GREEN

**Files:** modify `engine/src/audio/audio_drift_resampler.{h,c}`.

- [x] Add fixed history/mode state, preserve them correctly across init/reset, and write history in both modes.
- [x] Implement the exact kernel and saturation from the spec; retain the old linear previous/current equation for uninterrupted linear operation.
- [x] Add history-backed linear catch-up; for linear `pending=max(0,next_input-next_output)>1`, add `ceil(pending/ratio)` to the old capacity bound.
- [x] Rebuild and run `test_audio_drift_resampler`; observed 12 passed, 0 failed (six existing, six new).

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, and this slice's spec/plan.

- [x] Mutate the eight-frame gate, window sign, normalization, saturation, pending-capacity allowance, old linear weight and linear catch-up read; all seven mutations fail the focused test.
- [x] Run the focused test with `-fsanitize=address,undefined -fno-sanitize-recover=undefined`, and compile production/test sources with `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic -fsyntax-only`; both are clean.
- [x] Run added-line terminology checks and obtain independent read-only review; no Critical/Important findings were reported.
- [x] Update documentation incrementally, commit as `audio: add sinc mode to drift compensation`, then run `/tmp/full_trees.sh`; observed 429/429, 429/429 and 437/437 because no CTest target is added.
- [x] Push `master` only after the final committed tree passes; inspect the new remote CI runs without hiding cancelled or failed jobs.

## Result

Implementation, review and verification are complete. Independent review is Ready with no findings. The linear catch-up mutation initially survived, so a fractional 0.75-ratio switch regression was added; all seven mutants are now killed. Terminology scanning is clean, and the three full trees pass 429/429, 429/429 and 437/437. Remote CI inspection follows the push.
