# Audio Tracker GCC Backend Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

**Goal:** Let `AudioDelayTracker` select GCC-PHAT at construction while sharing the existing confidence and tracking policy.

**Architecture:** Add a separate GCC constructor and an internal common constructor. Hold only the selected estimator object, route push/reset/update through it, and keep the state machine unchanged.

**Tech Stack:** C11, existing delay tracker/estimator, GCC-PHAT normalized confidence, real FFT, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-tracker-gcc-design.md`.
- `AudioDelayTrackerConfig` layout and the default constructor behavior remain unchanged.
- Only the selected backend is allocated; only create allocates.
- Both backends use signed normalized correlation and identical lock/hold/unlock/slew policy.

### Task 1: Constructor API and RED

**Files:** modify `engine/src/audio/audio_delay_tracker.h`, `engine/tests/test_audio_delay_tracker.c`, `engine/CMakeLists.txt`.

- [x] Declare:

```c
AudioResult audio_delay_tracker_create_gcc(const AudioDelayTrackerConfig *config,
                                           AudioDelayTracker **out);
```

- [x] Add `gcc_create_validation_and_lifecycle`, `gcc_fractional_measurements_lock_and_gate`, and `gcc_chunking_reset_and_slew`; use real fractional, uncorrelated and inverted sample sequences.
- [x] Add `src/audio/audio_gcc_phat.c` and `src/audio/audio_fft.c` to the existing `test_audio_delay_tracker` executable; do not add a CTest target.
- [x] Build/run `test_audio_delay_tracker`; observed RED only on `audio_delay_tracker_create_gcc`.

### Task 2: Backend lifecycle and measurement routing

**Files:** modify `engine/src/audio/audio_delay_tracker.c`.

- [x] Add `AudioGccPhat *gcc` and a backend flag; implement a common validated constructor, with the GCC history/FFT rules enforced by `audio_gcc_phat_create` and allocation-failure cleanup.
- [x] Route destroy/reset/push only to the selected backend. Keep `frames_since_update` accounting common and single-counted.
- [x] Route GCC update through `audio_gcc_phat_estimate_with_confidence`; leave the existing time-domain call and all downstream policy unchanged.
- [x] Rebuild/run `test_audio_delay_tracker`; observed 8 passed, 0 failed (five existing, three new).

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the original tracker/GCC specs, and this slice's spec/plan.

- [x] Mutate constructor backend selection, GCC confidence routing, reset routing, push routing and shared slew, plus removal of only the GCC reset call; every mutation fails the focused suite.
- [x] Compile/run ASan+UBSan with the tracker test, tracker, time estimator, GCC and FFT sources; run strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` syntax checks.
- [x] Run added-line terminology checks and independent read-only review; the reset coverage finding was fixed and re-review is Ready.
- [x] Incrementally update documents and commit as `audio: add GCC backend to delay tracker`.
- [x] Run `/tmp/full_trees.sh` on the final commit; observed 429/429, 429/429 and 437/437. Verify actual counts, push `master`, and inspect both new CI runs.

## Result

Implementation, review and verification are complete. Normal and ASan+UBSan tests pass 8/8, strict warnings and terminology checks are clean, and all six mutants are killed. Review found a ready-state GCC reset test gap; the regression was added and scoped re-review is Ready with no remaining issues. The three full trees pass 429/429, 429/429 and 437/437. Remote CI inspection follows the push.
