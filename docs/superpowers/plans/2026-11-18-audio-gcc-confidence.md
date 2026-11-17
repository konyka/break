# Audio GCC Normalized Confidence Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

**Goal:** Add a signed normalized-correlation confidence result to GCC-PHAT without changing the existing raw-peak API.

**Architecture:** Share the existing PHAT calculation through an internal helper that also reports the selected integer lag. The new public wrapper computes direct sample-domain normalized correlation at that lag with exact i64 products.

**Tech Stack:** C11, existing `AudioGccPhat`/`AudioFft`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-gcc-confidence-design.md`.
- Existing `audio_gcc_phat_estimate` delay, raw peak, readiness and silence behavior remain unchanged.
- The new confidence is `cr/sqrt(cc*rr)` at the selected integer lag, not a rescaled PHAT peak.
- Failure leaves both new outputs untouched; only create allocates.

### Task 1: API and failing tests

**Files:** modify `engine/src/audio/audio_gcc_phat.h`, `engine/tests/test_audio_gcc_phat.c`.

- [x] Declare this exact interface:

```c
bool audio_gcc_phat_estimate_with_confidence(AudioGccPhat *phat,
                                             double *delay_frames,
                                             double *confidence);
```

- [x] Add `confidence_failure_is_atomic_and_delay_matches_legacy`: initialize outputs to sentinels, check NULL/not-ready/silent failures, then compare repeated old/new delay results after a real echo is pushed.
- [x] Add `confidence_matches_direct_signed_sample_correlation`: implement an independent i64 `cr/cc/rr` reference and check clean, noisy, inverted, fractional and maximum-lag inputs to 1e-12. Assert [-1,1] and lower absolute confidence when capture noise increases.
- [x] Run `cmake --build build-core-app-master --target test_audio_gcc_phat -j2 && ./build-core-app-master/test_audio_gcc_phat`; observed RED only on `audio_gcc_phat_estimate_with_confidence`.

### Task 2: Shared PHAT core and confidence

**Files:** modify `engine/src/audio/audio_gcc_phat.c`.

- [x] Extract the existing calculation into a static helper with an optional selected-lag output; keep the old public wrapper's behavior byte-for-byte at its outputs.
- [x] Implement the new wrapper using local delay/peak temporaries and exact integer-lag `cr/cc/rr` loops. Return false without writing outputs when `rr==0`.
- [x] Rebuild and run `test_audio_gcc_phat`; observed 8 passed, 0 failed (six existing, two new).

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the original GCC spec, and this slice's spec/plan.

- [x] Mutate `cr`, the denominator, selected-lag indexing, zero-energy guard and failure-output writes; all five make the focused suite fail.
- [x] Compile/run with `-fsanitize=address,undefined -fno-sanitize-recover=undefined` using `test_audio_gcc_phat.c`, `audio_gcc_phat.c`, `audio_fft.c` and `-lm`; check strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` syntax.
- [x] Run added-line terminology checks and independent read-only review; no Critical/Important findings were reported.
- [x] Incrementally update all listed documents and commit as `audio: add normalized confidence to GCC delay estimation`.
- [x] Run `/tmp/full_trees.sh` on the committed tree; observed 429/429, 429/429 and 437/437. Read the counts rather than relying on the script exit code, then push `master` and inspect both new CI runs.

## Result

Implementation, review and verification are complete. Normal and ASan+UBSan tests pass 8/8, strict warnings and terminology checks are clean, all five mutants are killed, and independent review is Ready with no findings. The three full trees pass 429/429, 429/429 and 437/437. Remote CI inspection follows the push.
