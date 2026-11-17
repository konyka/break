# Audio Noise Suppressor Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Done

**Goal:** Implement deterministic mono spectral noise reduction using the existing FFT, with fixed latency and arbitrary-chunk processing.

**Architecture:** A private Hann/STFT engine smooths each bin's power, applies bounded minimum tracking to that smoothed target, and uses over-subtracted Wiener-style gains. A primed overlap-add pipeline and N-sample output ring provide exact unit-gain reconstruction delayed by N frames.

**Tech Stack:** C11, `audio_fft`, existing audio numeric/result types, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-17-audio-noise-suppressor-design.md`.
- No new dependency, renderer interaction or platform-specific code.
- Owner-thread, mono, in-place i16 processing; allocate only in create.
- Do not overwrite existing documentation; append or correct only statements affected by this feature.

### Task 1: Public contract and failing tests

**Files:**
- Create: `engine/src/audio/audio_noise_suppressor.h`
- Create: `engine/src/audio/audio_noise_suppressor.c` (stub for RED)
- Create: `engine/tests/test_audio_noise_suppressor.c`
- Modify: `engine/CMakeLists.txt`

**Produces:**
```c
typedef struct AudioNoiseSuppressor AudioNoiseSuppressor;
AudioResult audio_noise_suppressor_create(const AudioNoiseSuppressorConfig *config,
                                          AudioNoiseSuppressor **out);
void audio_noise_suppressor_destroy(AudioNoiseSuppressor *suppressor);
void audio_noise_suppressor_reset(AudioNoiseSuppressor *suppressor);
void audio_noise_suppressor_process_i16(AudioNoiseSuppressor *suppressor,
                                        i16 *samples, u32 frames);
u32 audio_noise_suppressor_latency_frames(const AudioNoiseSuppressor *suppressor);
```

- [x] Write eight tests: configuration/latency, exact delayed unit-gain reconstruction with full-scale inputs, white-noise attenuation and its 6 dB limit, startup/transient tone preservation, initial-floor preservation, sustained-tone learning, chunk equivalence, and reset/silence.
- [x] Register `test_audio_noise_suppressor` with headless/audio labels and build it against the stub.
- [x] Run `cmake .` in `build-core-app-master`, then build the target. Observed RED: the five public symbols were undefined at link.

### Task 2: Minimum complete implementation

- [x] Implement failure-atomic allocation and configuration validation.
- [x] Implement Hann/STFT, normalized power, a 100 ms smoothed target with bounded minimum tracking, factor-2 over-subtracted Wiener-style gain, inverse transform and primed overlap-add.
- [x] Implement the N-sample delay ring, in-place chunk processing and exact reset.
- [x] Run `./build-core-app-master/test_audio_noise_suppressor`. Observed GREEN: 8 passed, 0 failed.

### Task 3: Review and repository verification

- [x] Run focused mutations. Strengthen tests for observable survivors; distinguish proven behavioral equivalences from defensive guards and OOM-only differences in the status document.
- [x] Run ASan+UBSan and `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic -fsyntax-only`.
- [x] Complete independent review and the follow-up review of sustained-tone behavior and survivor wording; no Critical or Important issues remain.
- [x] Append the design and verification results to `docs/design/audio_extended.md`, `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; mark this plan Done with observed counts after final verification.
- [x] Commit explicit paths as `audio: spectral noise suppression for captured voice`. Run `/tmp/full_trees.sh` after committing so the clean HEAD archive contains the new files. Observed 423/423, 423/423 and 431/431; push `master` and inspect CI as the release step.

## Result

Eight focused tests are GREEN. White noise is reduced by about 11.0 dB; the 6 dB per-bin floor uses a documented 2 dB aggregate RMS tolerance. Startup/tracking-transient tones are preserved, while a sustained tone is explicitly tested to become learned noise. Of 37 mutations, 32 were caught; three survivors are behavioral equivalences under the current schedule, one is an OOM-priority difference, and the power clamp remains a defensive guard without an equivalence claim. Independent review and follow-up review report no Critical or Important issues. Final full-tree results: build-core-app-master 423/423, build-editor-plugins 423/423 and build-core-app-net 431/431.
