# Playback Reference Tap Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: In progress

**Goal:** Deliver the final stereo engine mix as a bounded, optional mono i16 reference stream for later voice-processing integration.

**Architecture:** A fixed SPSC ring lives in `AudioImpl`. `ma_engine_config.onProcess` publishes final-mix frames on real-device and FAKE paths; owner-thread APIs control and drain the stream without allocation, locks or logging in the callback.

**Tech Stack:** C11 atomics, miniaudio engine callbacks, existing FAKE PCM rendering, `PlatformThread`, CMake/CTest, ASan/UBSan/TSan.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-playback-reference-design.md` exactly.
- Fixed 48 kHz mono i16 output, 16384-frame power-of-two ring, default disabled, drop-newest overflow policy.
- Only one producer and one consumer; no allocation, mutex, condition variable or logging in the engine callback.
- Start/stop preserve buffered frames; reset is allowed only while stopped.
- No microphone, AEC integration, delay alignment, encoding, network or acoustic-validation claims.
- Preserve existing terminology and Google-style naming; do not reintroduce removed display backends.

### Task 1: Public contract and RED tests

**Files:**
- Modify: `engine/src/audio/audio.h`
- Modify: `engine/tests/test_audio.c`
- Modify: `engine/CMakeLists.txt` (the existing `test_audio` target only)

**Interfaces:** Add the exact declarations below; no implementation yet.

```c
#define AUDIO_REFERENCE_RING_FRAMES 16384u

AudioResult audio_reference_start(AudioSystem *as);
AudioResult audio_reference_stop(AudioSystem *as);
AudioResult audio_reference_reset(AudioSystem *as);
AudioResult audio_reference_read_i16(AudioSystem *as, i16 *out,
                                     u32 max_frames, u32 *out_frames);
u32 audio_reference_available(const AudioSystem *as);
u64 audio_reference_overruns(const AudioSystem *as);
```

- [ ] Include `audio/audio_extended.h` and `core/platform_thread.h` in `test_audio.c`; link `Threads::Threads` to `test_audio` without adding a CTest target.
- [ ] Add `reference_disabled_until_started_and_validates_calls`: NULL/invalid calls, initial empty state, idempotent start/stop, read-after-stop, and `AUDIO_REJECTED` for running reset with unchanged availability/counters.
- [ ] Add `reference_tap_matches_final_stereo_mix`: open a real stereo `AudioPcmStream` on FAKE, write known i16 frames, call `audio_system_render`, and derive each expected reference independently:

```c
f32 mono = 0.5f * (stereo[2u * i] + stereo[2u * i + 1u]);
if (!isfinite(mono)) mono = 0.0f;
if (mono > 1.0f) mono = 1.0f;
if (mono < -1.0f) mono = -1.0f;
i16 expected = (i16)lrintf(mono * 32767.0f);
```

  Assert exact reference samples, frame counts, unchanged stereo output, and no additional samples after stop.
- [ ] Add `reference_ring_is_bounded_and_resettable_when_stopped`: render capacity+256 frames without reading; assert 16384 available and 256 overruns; drain, render/drain another capacity to cross the ring-index boundary, stop/reset, and assert zero available/overruns.
- [ ] Add `reference_concurrent_render_and_read_wrap_without_overruns`: a producer renders 256-frame blocks and yields while `audio_reference_available(as) > AUDIO_REFERENCE_RING_FRAMES / 2u`; the consumer drains until twice the ring capacity has arrived. Assert exact total, zero overruns and successful thread/result teardown.
- [ ] Register four tests in `TEST_MAIN_BEGIN`, taking `test_audio` from 24 to 28 cases.

Run:

```bash
cmake --build build-core-app-master --target test_audio -j16
```

Expected RED: linker errors only for the six new `audio_reference_*` symbols; no unrelated compile failure.

### Task 2: Final-mix callback and SPSC implementation

**Files:**
- Modify: `engine/src/audio/audio.c`

**Interfaces:** Implement every declaration from Task 1; preserve all existing audio behavior.

- [ ] Include `<stdatomic.h>` and add fixed reference state to `AudioImpl`:

```c
i16 reference_ring[AUDIO_REFERENCE_RING_FRAMES];
atomic_uint reference_head;
atomic_uint reference_tail;
atomic_uint_least64_t reference_overruns;
atomic_bool reference_enabled;
```

  Add a compile-time power-of-two assertion for `AUDIO_REFERENCE_RING_FRAMES`.
- [ ] Implement final-mix conversion with the exact Task 1 formula. The callback accepts `(void *user, f32 *frames, ma_uint64 frame_count)`, keeps the frame count 64-bit through room/drop calculations, and never changes `frames`.
- [ ] In `audio_system_create_ex`, set the following before `ma_engine_init`; use `impl` directly as callback user data:

```c
engine_config.onProcess = audio_reference_on_process;
engine_config.pProcessUserData = impl;
```

- [ ] Implement producer/consumer with the same memory-order pattern as `audio_capture.c`: producer owns head, acquires tail and release-publishes head; consumer owns tail, acquires head and release-publishes tail. Ring indices use `counter & (AUDIO_REFERENCE_RING_FRAMES - 1u)`.
- [ ] Implement lifecycle exactly: calloc supplies initially disabled/empty state; start/stop are idempotent and preserve frames; reset while enabled returns `AUDIO_REJECTED`, otherwise tail=head and overruns=0; invalid reads leave `*out_frames` untouched.
- [ ] Keep teardown unchanged: `ma_engine_uninit` remains before freeing the enclosing allocation.

Run:

```bash
cmake --build build-core-app-master --target test_audio -j16
./build-core-app-master/test_audio
ctest --test-dir build-core-app-master -R '^test_audio$' --output-on-failure
```

Expected GREEN: 28/28 and CTest 1/1, with no new warnings.

### Task 3: Concurrency, mutation and delivery evidence

**Files:**
- Modify: `docs/design/audio_extended.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Modify: `docs/superpowers/specs/2026-11-18-audio-playback-reference-design.md`
- Modify: `docs/superpowers/plans/2026-11-18-audio-playback-reference.md`

- [ ] Rebuild and run the final test in the existing sanitizer trees:

```bash
cmake --build /tmp/editor-audio-asan --target test_audio -j16
/tmp/editor-audio-asan/test_audio
cmake --build /tmp/build-audio-tsan --target test_audio -j16
/tmp/build-audio-tsan/test_audio
```

Expected: 28/28 in each, no ASan/UBSan/TSan report. The concurrent case must execute rather than be skipped.
- [ ] Compile `audio.c` with strict C11 warnings (`-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic -Werror`, miniaudio as a system include) and record the command. Treat warnings as failures.
- [ ] Independently mutate disabled gating, mono downmix, release head publication, drop accounting and running-reset rejection. Require the lifecycle/mix/bounds/concurrency tests to catch each observable change; document any non-observable memory-order mutation instead of claiming it was killed.
- [ ] Perform added-line terminology and `git diff --check` scans. Obtain independent read-only review; fix Critical/Important findings through RED-first tests and scoped re-review.
- [ ] Append actual results and remaining integration limits to the listed documents. Commit implementation as `audio: add playback reference tap`.
- [ ] Run `/tmp/full_trees.sh` on the committed tree. Expected counts remain 432/432, 432/432 and 440/440 because no CTest target is added. Read actual output and failure lines, not only the script exit status.
- [ ] If documentation changes amend the implementation commit, rerun all three trees on the amended final commit. Fetch `origin/master`, resolve any divergence without force-push, push `master`, and inspect the new main, Windows D3D12 and Proton runs. Verify real MSVC `/W4 /WX` success.

## Result

Task 1 is pending; no production implementation has started.
