# Audio Robust Drift Estimation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: In progress

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

- [ ] Declare:

```c
bool audio_drift_estimator_estimate_robust(AudioDriftEstimator *est,
                                           double *drift_ppm,
                                           double *mean_correlation);
```

- [ ] Add `robust_outliers_preserve_the_clean_slope`, `robust_failure_is_atomic_and_reset_reuses_scratch`, and `robust_ring_and_large_base_preserve_negative_drift` exactly as the spec describes.
- [ ] Build/run `test_audio_drift_estimator`; expected RED is only an undefined reference to the new function.

### Task 2: Repeated-median implementation

**Files:** modify `engine/src/audio/audio_drift_estimator.c`.

- [ ] Allocate/destroy `slopes` and `medians` with `window_size` entries and existing failure cleanup.
- [ ] Implement exact signed u64 frame deltas, allocation-free heap sort, overflow-safe even medians and per-sample repeated-median slope.
- [ ] Validate all slopes/results before writing outputs; compute mean signed correlation over all accepted samples and leave the legacy function untouched.
- [ ] Rebuild/run `test_audio_drift_estimator`; expected 8 passed, 0 failed (five existing, three new).

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the original drift-estimator spec, and this slice's spec/plan.

- [ ] Mutate signed frame delta, heap ordering, per-sample median, final median, non-finite/output guards and the legacy slope; all must fail focused tests.
- [ ] Run focused ASan+UBSan and strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` checks; include a 1024-sample maximum-window robust estimate.
- [ ] Run added-line terminology checks and independent read-only review; fix Critical/Important findings through failing tests first.
- [ ] Incrementally update documents and commit as `audio: add robust drift slope estimation`.
- [ ] Run `/tmp/full_trees.sh`; expected 429/429, 429/429 and 437/437. Read actual counts, push `master` after green and inspect both new CI runs.

## Result

Design and plan only; implementation and RED have not started.
