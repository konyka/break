# Audio Subframe Delay Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Done

**Goal:** Add fractional delay estimates and fractional reference alignment without changing existing integer behavior.

**Architecture:** Share one normalized-correlation search between integer and subframe estimators, interpolate the best absolute peak with a local parabola, and linearly interpolate two existing delay-line history reads.

**Tech Stack:** C11, existing delay estimator/delay line, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-17-audio-subframe-delay-design.md`.
- Preserve integer estimate ties, readiness/failure atomicity and integer delay-line output exactly.
- Allocate only in existing create functions; no dependency or platform code.

### Task 1: Failing incremental tests

**Files:** modify `engine/src/audio/audio_delay_estimator.h`, `engine/tests/test_audio_delay_estimator.c` and `engine/src/audio/audio_delay_estimator.c`.

- [x] Add sinc-generated 3.25/12.5/31.75-frame tests with 0.25-frame tolerance and sinc-based correlation references, endpoint/failure checks, fractional delay-line validation, in-place/chunked reads and integer compatibility.
- [x] Build `test_audio_delay_estimator` in `build-core-app-master`. Observed RED after correcting a test-only missing constant: the three new symbols were undefined at link.

### Task 2: Implementation

- [x] Extract a shared best-lag search, then add concave absolute-peak parabolic interpolation with integer fallback.
- [x] Add finite/range-checked subframe delay state and two-read linear interpolation while preserving integer output.
- [x] Run the existing plus new tests; observed 11 passed, 0 failed.

### Task 3: Delivery

- [x] Run targeted mutations for the shared search, curve fallback, offset, fractional reads, validation and integer compatibility; 16/18 caught and two mathematical guards documented.
- [x] Run ASan+UBSan, strict warnings and forbidden-terminology scans; fix the test generator's tail OOB and use aligned real sentinels. Independent review is running.
- [x] Update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the spec and this plan.
- [x] Commit as `audio: subframe delay estimation and reference alignment`; run `/tmp/full_trees.sh`, then push only if all three trees and review pass. Test counts remain 424/424, 424/424 and 432/432 because no CTest target is added. Inspect CI after push.

## Result

Eleven focused tests are GREEN. Sixteen of 18 mutations were caught; the concavity and locality guards are justified by exact-arithmetic best-local-maximum inequalities, with direct zero-denominator fallback and finite-offset defense. ASan+UBSan and strict warnings are clean after fixing the test generator's tail bounds. Independent review and follow-up review report no remaining Critical/Important issues. Final full-tree results: build-core-app-master 424/424, build-editor-plugins 424/424 and build-core-app-net 432/432. A system file-table exhaustion run and an isolated asset-diagnostic failure were investigated; the same final trees passed after recovery, including a complete 432-test rerun of the third tree.
