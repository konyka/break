# Core App Voice PCM Pump Design

Status: Approved for implementation under the standing autonomous delivery request

## Purpose

Provide a real capture-to-processed-PCM component using the existing capture, playback-reference, alignment and voice-processing primitives. It supports deterministic manual pumping and a dedicated owner thread. CLI and network transport integration are separate slices.

## Approaches considered

1. **Manual pump plus optional owner thread, with an SPSC PCM-frame queue (selected).** Tests can drive exact FAKE input/output while production uses the same pump on a dedicated thread. The consumer receives immutable PCM frames without sharing device or processor state.
2. **Encode and send directly from the capture callback or voice thread.** Rejected: it would couple real-time device ownership to codec/network backpressure and bypass the CoreAppThread handoff.
3. **Poll devices directly in the main loop.** Rejected: frame pacing and shutdown would depend on simulation work, and the threaded path would not be exercised.

## API and ownership

Add `apps/core_app/core_app_voice.h` and `.c`:

```c
#define CORE_APP_VOICE_FRAME_FRAMES 480u
#define CORE_APP_VOICE_QUEUE_CAPACITY 16u

typedef struct {
    AudioSystem *playback; /* borrowed until destroy */
    AudioBackend capture_backend;
    AudioVoiceAlignerConfig aligner;
    AudioVoiceProcessorConfig processor;
    bool use_gcc;
} CoreAppVoiceConfig;

typedef struct CoreAppVoice CoreAppVoice;

typedef struct {
    u64 produced;
    u64 dropped;
    u64 capture_overruns;
    u64 reference_overruns;
} CoreAppVoiceStats;

BreakRuntimeError core_app_voice_create(const CoreAppVoiceConfig *config,
                                        CoreAppVoice **out);
BreakRuntimeError core_app_voice_start(CoreAppVoice *voice);
BreakRuntimeError core_app_voice_start_threaded(CoreAppVoice *voice);
BreakRuntimeError core_app_voice_pump(CoreAppVoice *voice, u32 max_packets);
BreakRuntimeError core_app_voice_pop(CoreAppVoice *voice, BreakVoiceFrame *out,
                                     bool *out_ready);
BreakRuntimeError core_app_voice_stats(CoreAppVoice *voice, CoreAppVoiceStats *out);
BreakRuntimeError core_app_voice_stop(CoreAppVoice *voice);
void core_app_voice_destroy(CoreAppVoice *voice);
```

- Creation owns a new 48 kHz mono `AudioCapture` (4096-frame ring), `AudioVoiceAligner` and `AudioVoiceProcessor`. Playback is borrowed. The nested tracker sample rate must be 48000; nested processor validation remains authoritative for its modules.
- Creation validates all pointers/ranges before starting any device and destroys partially created components on failure. `*out` is written only on success. `destroy(NULL)` is a no-op; destroy first performs an idempotent stop.
- `start` enables the playback reference and starts capture, in that order; failure reverses the reference start. It is idempotent and does not clear queued frames or reset sequence/state on a later restart.
- `start_threaded` uses the same start, then launches a worker whose only device/PCM processing call is the shared pump. A thread-creation failure stops capture/reference and leaves the object stopped.
- `stop` requests worker termination and joins it before stopping capture/reference. Already buffered queue frames remain readable. No spectral tail is flushed in this slice.
- Only one consumer calls `pop`. `out_ready=false` on an empty queue; invalid arguments return `BREAK_RUNTIME_INVALID`. The queue and all PCM frames remain bounded.

## Pump and data flow

Each packet is exactly 480 frames (10 ms at 48 kHz):

1. If capture is lost, return `BREAK_RUNTIME_UNAVAILABLE`; no automatic reopen is attempted.
2. Wait until both capture and the playback-reference ring contain at least 480 frames; otherwise return `BREAK_RUNTIME_OK` without changing sequence or output.
3. Read exactly 480 raw frames from each. Raw reference/capture enter `AudioVoiceAligner`; its aligned reference and in-place capture then enter `AudioVoiceProcessor`.
4. Fill a `BreakVoiceFrame` with the next sequence, 48000 Hz, mono and 480 samples. Sequence advances for every processed packet, including a dropped packet, so later transport can detect a gap.
5. Publish the frame into a 16-entry SPSC queue with release/acquire head/tail. A full queue drops the newest packet and increments `dropped`; the producer never blocks.

`max_packets` bounds one pump call; zero is a no-op. Manual callers and the worker use identical code. The worker pumps at most four packets and sleeps 1 ms when no packet was produced. A worker error is latched and returned by stop. No callback, mixer command, network or simulation object is accessed by the worker beyond the reference-specific `AudioSystem` API.

`stats` reports queued/dropped packet counts and the current capture/reference device overrun counters. Produced/dropped counters are atomic so diagnostics can run while the worker is active. Queue capacity is a compile-time power of two. There is no dynamic allocation, lock, log or file I/O in pump/pop; all allocations occur at create or thread start.

## TDD and verification

Add `test_core_app_voice` using real FAKE capture and FAKE playback rendering:

1. Declare the API and register tests first; obtain RED from unresolved symbols.
2. Validate creation, nested formats, NULL calls, start/stop idempotence, stopped drain and empty pop. Verify no output before both streams have a full packet.
3. Inject a known 480-frame FAKE capture and render known stereo playback. Independently reproduce device f32→i16 conversion, reference downmix, alignment and voice processing with separate objects; require exact PCM, sequence and format equality with the component output.
4. Process capacity+1 packets without popping; require exactly 16 queued frames in order, one dropped packet and no sequence reuse. Drain after stop.
5. Run the threaded path with bounded producer/wait loops; receive a real packet and verify stop joins the worker without sanitizer findings.
6. Run normal, ASan+UBSan and TSan tests plus strict warnings. Mutate packet gating, reference/capture routing, processing order, sequence/drop accounting, queue publication and worker shutdown; require focused evidence.
7. Obtain independent read-only review and update audio/status/capability documents. Do not claim CLI, network encoding/send, production deployment, drift compensation or acoustic validation. Run all three delivery trees, push `master`, and inspect main/Windows/Proton CI.

## Limits

This slice delivers the reusable voice PCM pump only. It does not add a `core_app` CLI option, call network hooks, encode/send datagrams, recover a lost capture device, flush the processing tail, compensate clock drift or provide real microphone/speaker/listening evidence. Those boundaries remain explicit.
