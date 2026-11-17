# Audio Robust Drift Estimation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

**Goal:** Add repeated-median robust drift estimation without changing legacy least-squares results.

**Architecture:** Reuse the estimator's accepted window and add two fixed scratch arrays allocated at create. Compute per-sample slope medians with an allocation-free heap sort, then take their median and preserve the existing mean-correlation/limit contracts.

**Tech Stack:** C11, existing `AudioDriftEstimator`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-drift-robust-design.md`.
- Legacy estimate, push/reset/ring behavior and public config remain unchanged.
- Only create allocates; robust calls mutate scratch but never stored samples.
- Failure leaves both outputs untouched, including non-finite slopes and drift-limit rejection.

### Task 1: API and RED

**Files:** modify `engine/src/audio/audio_drift_estimator.h`, `engine/tests/test_audio_drift_estimator.c`.

- [x] Declare:

```c
bool audio_drift_estimator_estimate_robust(AudioDriftEstimator *est,
                                           double *drift_ppm,
                                           double *mean_correlation);
```

- [x] Add `robust_outliers_preserve_the_clean_slope`, `robust_failure_is_atomic_and_reset_reuses_scratch`, and `robust_ring_and_large_base_preserve_negative_drift` exactly as the spec describes.
- [x] Build/run `test_audio_drift_estimator`; observed RED only on the new function.

### Task 2: Repeated-median implementation

**Files:** modify `engine/src/audio/audio_drift_estimator.c`.

- [x] Allocate/destroy `slopes` and `medians` with `window_size` entries and existing failure cleanup.
- [x] Implement exact signed u64 frame deltas, allocation-free heap sort, overflow-safe even medians and per-sample repeated-median slope.
- [x] Validate all slopes/results before writing outputs; compute mean signed correlation over all accepted samples and leave the legacy function untouched.
- [x] Rebuild/run `test_audio_drift_estimator`; observed 8 passed, 0 failed (five existing, three new).

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the original drift-estimator spec, and this slice's spec/plan.

- [x] Mutate signed frame delta, heap restoration, per-sample median, final median, combined non-finite guards, drift limit and legacy slope; all seven fail focused tests.
- [x] Run focused ASan+UBSan and strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` checks; include a 1024-sample maximum-window robust estimate.
- [x] Run added-line terminology checks and independent read-only review; no Critical/Important findings were reported.
- [x] Incrementally update documents and commit as `audio: add robust drift slope estimation`.
- [x] Run `/tmp/full_trees.sh`; observed 429/429, 429/429 and 437/437. Read actual counts, push `master` after green and inspect both new CI runs.

## Result

Implementation, review and verification are complete. Normal and ASan+UBSan tests pass 8/8, strict warnings and terminology checks are clean, all seven final mutants are killed, and independent review is Ready with no findings. The three full trees pass 429/429, 429/429 and 437/437. Remote CI inspection follows the push.
