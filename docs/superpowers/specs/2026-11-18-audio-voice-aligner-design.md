# Voice Alignment Controller Design

Status: Implemented and locally verified

## Purpose

Connect the existing raw playback/capture delay estimator to the reference delay line with deterministic scheduling. Today callers must manually push samples, decide when to update the tracker and copy its delay into the line. This slice supplies that missing control loop as a mono owner-thread component.

## Approaches considered

1. **A dedicated `AudioVoiceAligner` owning a tracker and delay line (selected).** The component has one responsibility: consume raw reference/capture frames, update on exact frame boundaries and emit aligned reference. Both estimator backends remain available through explicit constructors.
2. **Extend `AudioVoiceProcessor` with tracking.** This would mix alignment, device timing and DSP configuration into an already integrated processing chain, making each stage harder to verify independently. Rejected.
3. **Add only an update-due helper to the tracker.** Smaller, but callers would still need to reproduce delay-line application and boundary-safe chunking. Rejected because it does not close the alignment-control gap.

## Public API

Add `audio/audio_voice_aligner.h`:

```c
typedef struct {
    AudioDelayTrackerConfig tracker;
    u32 update_period_frames; /* 1..192000 */
} AudioVoiceAlignerConfig;

typedef struct AudioVoiceAligner AudioVoiceAligner;

AudioResult audio_voice_aligner_create(const AudioVoiceAlignerConfig *config,
                                       AudioVoiceAligner **out);
AudioResult audio_voice_aligner_create_gcc(const AudioVoiceAlignerConfig *config,
                                           AudioVoiceAligner **out);
void audio_voice_aligner_destroy(AudioVoiceAligner *aligner);
AudioResult audio_voice_aligner_process_i16(AudioVoiceAligner *aligner,
                                            const i16 *reference, const i16 *capture,
                                            i16 *aligned_reference, u32 frames);
double audio_voice_aligner_delay(const AudioVoiceAligner *aligner);
u64 audio_voice_aligner_updates(const AudioVoiceAligner *aligner);
bool audio_voice_aligner_locked(const AudioVoiceAligner *aligner);
bool audio_voice_aligner_uses_gcc(const AudioVoiceAligner *aligner);
u64 audio_voice_aligner_rejections(const AudioVoiceAligner *aligner);
```

- Creation validates the nested tracker configuration and a nonzero period no greater than 192000. GCC creation also inherits the existing GCC history/FFT limits. Failure leaves `*out` unchanged; allocation failure returns `AUDIO_OVERLOAD`.
- `destroy(NULL)` is a no-op. Destruction releases the line, tracker and controller. There is no reset API in this slice because the existing delay line has no reset operation; use a new instance for an independent stream.
- NULL accessors return zero/false. `updates` counts scheduled tracker calls, including rejected estimates; `rejections` forwards the tracker's cumulative rejected count. `uses_gcc` records the constructor-selected backend so integration tests cannot confuse two equally accurate estimators.
- `delay` is the delay actually applied by the line, not merely a new estimator measurement.

## Data flow and scheduling

For each input frame, the tracker receives the **raw** reference and capture. The delay line receives the same raw reference and writes the aligned reference. Capture is never modified.

Processing is divided at exact `update_period_frames` boundaries, regardless of caller chunk sizes:

1. Push the next raw chunk to the tracker and process the same reference chunk through the delay line.
2. When the countdown reaches zero, increment `updates` and call `audio_delay_tracker_update` once.
3. An accepted measurement is applied with `audio_delay_line_set_subframe_delay`; rejected/low-confidence results leave the existing delay unchanged.
4. Reset the countdown to the configured period. A changed delay therefore takes effect on the next frame after the boundary, never retroactively on the chunk just emitted.

The line uses its existing default linear interpolation with immediate transitions. This slice does not enable sinc or crossfade modes and does not add a pending-target queue.

`reference` and `aligned_reference` may be the same buffer because the tracker push precedes line processing. Capture and output must not overlap; at least exact pointer equality is rejected before any state mutation. A zero-frame call with a valid controller returns `AUDIO_OK` and permits NULL signal pointers. Other NULL signal pointers return `AUDIO_INVALID` before any state or output changes. An unexpected line-set error is returned; already processed prefix frames are not rolled back.

Only creation allocates. Processing, scheduling and accessors run on the owner thread and create no hidden thread, lock, log or file activity.

## TDD and verification

Add `test_audio_voice_aligner`, linked directly to the aligner, tracker, time-domain estimator, GCC-PHAT and FFT sources without opening an audio device.

1. Declare the API and register tests first; observe unresolved new symbols as RED.
2. Validate constructors, nested/period failures, unchanged output handles, NULL accessors, zero-frame calls, invalid signal pointers and capture/output aliasing.
3. Use a deterministic nonperiodic reference and a known 12.5-frame fractional echo. Verify the first update occurs exactly at the configured period, the boundary frame retains the old delay, and the next frame matches an independent fractional-delay calculation using the reported delay. Inject a delay-setting failure and require the next update to wait a complete new period; verify lock/rejection/update accessors and both constructor backends.
4. Feed identical streams in whole blocks and irregular 1/7/31/128-frame chunks. Require byte-identical aligned output and identical update/delay/lock state at the same total frame count.
5. Feed reference activity with a silent capture window; require scheduled update/rejection counts to advance while delay remains zero. Exercise both default and GCC constructors with the known echo.
6. Run normal and ASan+UBSan tests plus strict C11 warnings. Mutate raw-versus-aligned estimator routing, exact scheduling, delay application, GCC construction and argument validation; require focused failures.
7. Obtain independent read-only review, update the audio design and capability/status documents without removing old limitations, run all three delivery trees, push `master`, and inspect main/Windows/Proton CI including MSVC.

## Limits

This component aligns already available PCM buffers. It does not open playback/capture devices, read the reference ring, run AEC or `AudioVoiceProcessor`, compensate clock drift, encode/send datagrams, perform crossfade/sinc transitions, support multiple channels or provide acoustic/listening validation. Core-app integration remains a separate slice.
