# Playback Reference Tap Design

Status: Implemented and locally verified

## Purpose

Expose the engine's final playback mix as a bounded mono PCM stream for later echo-cancellation integration. The current voice processor requires an aligned playback reference, but `AudioSystem` exposes no real-device reference path. This slice supplies that primitive without pretending that zero reference samples are echo cancellation.

## Approaches considered

1. **Fixed SPSC ring behind `ma_engine_config.onProcess` (selected).** Real-device rendering and offline FAKE rendering share the same final-mix callback. Storage belongs to the existing audio allocation, so the callback performs no allocation, locking or logging.
2. **Separately allocated reference object.** More flexible ownership, but adds create/destroy ordering and a second lifetime to synchronize with the engine device. Rejected as unnecessary for one fixed-format tap per system.
3. **Poll `audio_system_render` for reference samples.** This only drives FAKE/no-device rendering and does not observe a real playback callback. Rejected because it cannot close the production-reference gap.

## Public API

Add to `audio/audio.h`:

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

- The tap is initially disabled. `start` enables writes and is idempotent; `stop` disables writes and is idempotent. Neither operation discards buffered frames.
- `reset` is valid only while stopped. It atomically discards unread frames and resets the overrun counter. While running it returns `AUDIO_REJECTED` without changing state.
- NULL system pointers return `AUDIO_INVALID` from state-changing calls; query functions then return zero. `read_i16` requires non-NULL output and frame-count pointers even for a zero capacity request. Invalid reads do not write outputs.
- Reading is valid while running or stopped, so stopping does not strand the final buffered frames. There is one consumer, normally the voice owner thread.
- `available` is an atomic snapshot and can be used for bounded producer throttling; a concurrent snapshot is naturally approximate.

## Capture point and conversion

Configure `ma_engine_config.onProcess` and `pProcessUserData` before `ma_engine_init`. The callback receives the internal implementation pointer, not a partially initialized public object.

The callback receives the final stereo `f32` mix after `ma_engine_read_pcm_frames`, for both an internal real device and explicit FAKE rendering. It does not modify playback output. Each frame becomes:

```text
mono = 0.5 * (left + right)
non-finite -> 0; otherwise clamp to [-1, 1]
i16 = lrintf(mono * 32767)
```

The stream is fixed at the engine's 48 kHz rate. This slice performs no delay alignment or clock-drift compensation; later consumers must provide those stages before AEC.

## Ring and threading

`AudioImpl` gains fixed storage for 16384 mono `i16` frames, free-running atomic `u32` head/tail counters, an atomic enabled flag, an atomic in-flight callback count, an atomic `u64` stop-generation counter and an atomic `u64` overrun counter. The power-of-two capacity is compile-time checked.

- The engine callback is the only producer. It reads the current generation with its first enabled observation, increments the in-flight count, then rechecks both enabled and generation before writing. It exits without writing if stop began or the captured generation is stale. Otherwise it loads its own head and acquires the consumer tail, writes at most the available room, release-publishes the new head, then decrements the in-flight count.
- A full ring drops the newest frames and counts dropped frames, matching `AudioCapture` policy. The callback handles miniaudio's 64-bit frame count without truncating it before bounds checks.
- The consumer acquires the head, copies the oldest available frames and release-updates its own tail. No heap access occurs in either hot path.
- Start/stop/reset and reads use owner-thread control. An effective stop stores disabled and advances the generation before waiting on this low-frequency control path until the in-flight count reaches zero; it never makes the audio callback wait. The generation check closes the window where a callback observed enabled but had not registered as active before a stop/reset/restart sequence. Reset is restricted to stopped state with no remaining producer.
- `audio_system_destroy` retains its existing ordering: engine uninitialization stops the device callback before the single allocation containing the reference state is freed. No additional allocation or teardown is needed.

## TDD and verification

Extend the existing `test_audio` target so the overall CTest target count does not change:

1. Declare the API and add tests first; verify RED as unresolved new symbols.
2. Lifecycle/validation: initially disabled, invalid calls, idempotent start/stop, stopped drain and running-reset rejection.
3. Real FAKE mix: write known PCM through a real stereo PCM stream, render it, and independently derive every expected mono i16 sample from the returned final stereo buffer. Verify that tapping does not alter output.
4. Ring bounds: fill beyond capacity, verify exactly 16384 retained frames and the exact dropped-frame count; drain, refill and drain again across ring-index wrap, then stop/reset and verify empty/zero counters.
5. Concurrency: one thread performs repeated FAKE renders while the owner reads; throttle before the ring can overflow, render enough frames to wrap, and verify total delivery with zero overruns. Link the existing cross-platform thread wrapper explicitly.
6. Run normal, ASan+UBSan and TSan `test_audio` plus strict C11 warnings; use the real MSVC CI job for that compiler's `/W4 /WX` verification. Mutate final-mix downmix, disabled gating, head publication, overflow accounting and reset rejection; require focused evidence for each behaviorally observable mutation.
7. Update `audio_extended.md`, `Implementation_Status.md` and `missing_capabilities.md` without deleting prior limitations. Obtain independent read-only review, run all three delivery trees, push `master`, and inspect new CI runs.

## Limits

This is a reference-capture primitive, not an integrated voice pipeline. It does not open a microphone, align playback to capture, run `AudioVoiceProcessor`, encode datagrams, send network traffic, resample to another rate or perform acoustic/listening validation. Those remain separately verifiable slices.
