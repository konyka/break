# Audio Sinc Delay-Line Mode Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

**Goal:** Add a causal 16-tap sinc interpolation mode with an explicit eight-frame added delay to the existing delay line.

**Architecture:** Extend history while preserving configured delay limits, then evaluate a normalized Blackman-windowed sinc kernel around the delayed position.

**Tech Stack:** C11, existing delay estimator/line, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-sinc-delay-design.md`.
- Default linear and all existing integer behavior must remain unchanged.
- No future samples, allocation after create, or hidden latency; D+8 is explicit.

### Task 1: Incremental RED

**Files:** modify `engine/src/audio/audio_delay_estimator.h`, `engine/src/audio/audio_delay_estimator.c`, `engine/tests/test_audio_delay_estimator.c`.

- [x] Add mode/accessor validation, D+8 integer behavior, a direct fractional-kernel reference, frequency/DC checks and reset/bound cases.
- [x] Build `test_audio_delay_estimator`; expected RED on set_sinc, sinc and sinc_extra_delay.

### Task 2: Implementation

- [x] Extend history and separate maximum from ring size; add mode state and normalized causal kernel.
- [x] Run the tests; 18 passed, 0 failed (eleven existing, seven new including the review-driven saturation regression).

### Task 3: Delivery

- [x] Run targeted mutations, ASan+UBSan, strict warnings, terminology scans and independent review.
- [x] Update audio design, implementation status, missing capabilities, spec and plan.
- [x] Commit as `audio: add causal sinc mode to the delay line`; run `/tmp/full_trees.sh`, with 429/429, 429/429 and 437/437 because no CTest target is added. Push after review/green trees and inspect CI.

## Result

Implementation, review and verification are complete. Independent review found and drove a full-scale saturation fix; scoped re-review approved the fix with no remaining Critical/Important issues. Six targeted mutants are killed, normal/ASan+UBSan tests pass 18/18, strict warnings and added-line terminology scans are clean, and the three full trees pass 429/429, 429/429 and 437/437. Remote CI inspection follows the push.
