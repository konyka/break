# Audio Drift Sinc Mode Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: In progress

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

- [ ] Declare `set_sinc`, `sinc` and `sinc_extra_delay`; add mode/reset, delayed integer/decimation, independent-kernel/chunk, mode-switch/capacity, tone/DC and full-scale saturation tests.
- [ ] Extend state-equality assertions to cover `sinc` and all 32 history bytes.
- [ ] Run `cmake --build build-core-app-master --target test_audio_drift_resampler -j2 && ./build-core-app-master/test_audio_drift_resampler`; expected RED is a link failure on the three new symbols, not a compile error.

### Task 2: Minimal implementation and GREEN

**Files:** modify `engine/src/audio/audio_drift_resampler.{h,c}`.

- [ ] Add fixed history/mode state, preserve them correctly across init/reset, and write history in both modes.
- [ ] Implement the exact kernel and saturation from the spec; retain the old linear previous/current equation for uninterrupted linear operation.
- [ ] Add history-backed linear catch-up; for linear `pending=max(0,next_input-next_output)>1`, add `ceil(pending/ratio)` to the old capacity bound.
- [ ] Rebuild and run `test_audio_drift_resampler`; expected 12 passed, 0 failed (six existing, six new).

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, and this slice's spec/plan.

- [ ] Mutate the eight-frame gate, window sign, normalization, saturation, pending-capacity allowance and old linear weight; every mutation must make the focused test fail.
- [ ] Run the focused test with `-fsanitize=address,undefined -fno-sanitize-recover=undefined`, and compile production/test sources with `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic -fsyntax-only`.
- [ ] Run added-line terminology checks and obtain independent read-only review; fix Critical/Important findings through new RED tests first.
- [ ] Update documentation incrementally, commit as `audio: add sinc mode to drift compensation`, then run `/tmp/full_trees.sh`; expected 429/429, 429/429 and 437/437 because no CTest target is added.
- [ ] Push `master` only after the final committed tree passes; inspect the new remote CI runs without hiding cancelled or failed jobs.

## Result

Design and plan only; no implementation or RED run has occurred.
