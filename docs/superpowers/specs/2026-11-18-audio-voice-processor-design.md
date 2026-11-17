# Voice Processor Pipeline Design

Status: Approved for autonomous implementation under the active goal

## Purpose

Compose the existing capture-processing components into one owner-thread mono pipeline, so later device/network integration does not duplicate ordering, lifecycle or reset logic.

## Approaches considered

1. **Standalone `AudioVoiceProcessor` composed from existing modules (selected).** Independently testable, explicit configuration and lifecycle, no core_app or network dependency.
2. **Implement the chain directly in core_app.** Fewer files initially, but mixes device/application lifecycle with DSP ordering and is harder to verify; deferred until this pipeline exists.
3. **Add another AEC-only wrapper.** Duplicates the new residual integration without addressing spectral noise, gate, AGC or reset composition; rejected.

## API and configuration

New `engine/src/audio/audio_voice_processor.{h,c}`:

```c
typedef struct {
    AudioEchoCancellerConfig echo;
    AudioResidualEchoSuppressorConfig residual;
    AudioNoiseSuppressorConfig noise;
    AudioNoiseGateConfig gate;
    AudioAgcConfig agc;
} AudioVoiceProcessorConfig;

AudioResult audio_voice_processor_create(const AudioVoiceProcessorConfig *config,
                                         AudioVoiceProcessor **out);
void audio_voice_processor_destroy(AudioVoiceProcessor *processor);
void audio_voice_processor_reset(AudioVoiceProcessor *processor);
void audio_voice_processor_process_i16(AudioVoiceProcessor *processor,
                                       const i16 *reference, i16 *capture, u32 frames);
u32 audio_voice_processor_latency_frames(const AudioVoiceProcessor *processor);
```

- All five sample rates must match; gate and AGC channels must be mono. Each module's existing ranges apply unchanged.
- NULL config/out or validation failure returns `AUDIO_INVALID`; allocation failure returns `AUDIO_OVERLOAD`; `*out` is written only on success and partial construction is destroyed.
- Processing is mono, owner-thread and in-place. The aligned playback reference is required. NULL pointers are accepted only for zero frames; other invalid calls are no-ops.
- Reset restores every component's post-create state while preserving configuration. Only create allocates.

## Processing order

For each input block:

1. `audio_residual_echo_suppressor_process_with_aec` performs per-frame AEC and near-end-aware residual suppression.
2. `audio_noise_suppressor_process_i16` applies Hann/STFT spectral noise reduction.
3. `audio_noise_gate_process_i16` applies the downward expander.
4. `audio_agc_process_i16` applies bounded automatic gain.

`latency_frames` reports the spectral suppressor's fixed `frame_size`; other components add no positional delay. As with the standalone suppressor, append that many zero frames to drain a finite stream. No automatic device capture, reference alignment, encoding or network transmission is hidden in this component.

## Tests

Add `test_audio_voice_processor` with three tests:

1. NULL/mismatched-rate/multichannel/invalid nested configs, success-only output, initial latency and zero/invalid no-op behavior.
2. A deterministic echo/noise/near-end stream matches a manually constructed five-stage chain byte-for-byte; arbitrary chunks match one whole call.
3. Reset matches a fresh processor, and zero-padding drains the spectral latency deterministically.

Run targeted stage-order/reset/routing mutations, ASan+UBSan, strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

Mono only, fixed chain with no bypass policy, no production device/network wiring, no automatic delay tracking or real acoustic validation. Core app integration remains a separate follow-up project.
