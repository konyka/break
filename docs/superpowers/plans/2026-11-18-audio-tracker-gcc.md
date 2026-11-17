# Audio Tracker GCC Backend Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: In progress

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

- [ ] Declare:

```c
AudioResult audio_delay_tracker_create_gcc(const AudioDelayTrackerConfig *config,
                                           AudioDelayTracker **out);
```

- [ ] Add `gcc_create_validation_and_lifecycle`, `gcc_fractional_measurements_lock_and_gate`, and `gcc_chunking_reset_and_slew`; use real fractional, uncorrelated and inverted sample sequences.
- [ ] Add `src/audio/audio_gcc_phat.c` and `src/audio/audio_fft.c` to the existing `test_audio_delay_tracker` executable; do not add a CTest target.
- [ ] Build/run `test_audio_delay_tracker`; expected RED is only the undefined `audio_delay_tracker_create_gcc` symbol.

### Task 2: Backend lifecycle and measurement routing

**Files:** modify `engine/src/audio/audio_delay_tracker.c`.

- [ ] Add `AudioGccPhat *gcc` and a backend flag; implement a common validated constructor, with the GCC history/FFT rules enforced by `audio_gcc_phat_create` and allocation-failure cleanup.
- [ ] Route destroy/reset/push only to the selected backend. Keep `frames_since_update` accounting common and single-counted.
- [ ] Route GCC update through `audio_gcc_phat_estimate_with_confidence`; leave the existing time-domain call and all downstream policy unchanged.
- [ ] Rebuild/run `test_audio_delay_tracker`; expected 8 passed, 0 failed (five existing, three new).

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the original tracker/GCC specs, and this slice's spec/plan.

- [ ] Mutate constructor backend selection, GCC confidence routing, reset routing, push routing and shared slew; every mutation must fail the focused suite.
- [ ] Compile/run ASan+UBSan with the tracker test, tracker, time estimator, GCC and FFT sources; run strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` syntax checks.
- [ ] Run added-line terminology checks and independent read-only review; address Critical/Important findings through RED-first fixes.
- [ ] Incrementally update documents and commit as `audio: add GCC backend to delay tracker`.
- [ ] Run `/tmp/full_trees.sh` on the final commit; expected 429/429, 429/429 and 437/437. Verify actual counts, push `master`, and inspect both new CI runs.

## Result

Design and plan only; no implementation or RED run has occurred.
