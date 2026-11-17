# Sinc Delay-Line Mode Design

Status: Implemented and locally verified

## Purpose

Add an optional high-quality fractional interpolation mode to the existing delay line, without changing default linear output or integer compatibility.

## Approaches considered

1. **Sixteen-tap Blackman-windowed sinc with eight extra delay frames (selected).** Provides a causal real-time kernel and preserves the existing API/history model.
2. **Noncausal sinc without added delay.** Cannot work for small positive fractional delays because it needs future samples; rejected.
3. **Linear only.** Lower cost, but leaves the documented high-frequency quality gap.

## API

- `AudioResult audio_delay_line_set_sinc(AudioDelayLine *line, bool enabled)`; NULL returns INVALID.
- `bool audio_delay_line_sinc(const AudioDelayLine *line)`; false for NULL.
- `u32 audio_delay_line_sinc_extra_delay(const AudioDelayLine *line)`; eight when enabled, zero otherwise/NULL.

Sinc mode adds eight frames to the selected delay, so the effective delay is D+8. Integer and subframe accessors continue to report D, while the extra-delay accessor makes the added latency explicit.

## Algorithm

- Extend history allocation by 32 entries; retain the configured maximum separately from ring size. Existing linear and integer behavior is unchanged.
- For fractional D=d+f, evaluate at D+8. For tap j=-7..8, read source delay d+8+j and weight `sinc(f-j) * Blackman(tap)`, where tap=j+7 and Blackman uses `0.42 - 0.5*cos(2πtap/15) + 0.08*cos(4πtap/15)`.
- Normalize each result by the sum of kernel weights and round to i16. Sinc overshoot saturates to [-32768, 32767] after rounding, avoiding an out-of-range floating-to-integer conversion. Zero fractional part uses one exact read. All reads stay within allocated history, including maximum delay and initial silence.
- Mode changes take effect on the next frame without a crossfade. In-place and arbitrary chunk processing remain valid. Only create allocates.

## Tests

1. Mode/NULL/accessor validation, unchanged configured maximum and exact default behavior.
2. Integer D under sinc has exactly D+8 delay; switching back restores D.
3. A direct independent kernel reference checks fractional output, initial silence, in-place and chunking.
4. An 8 kHz tone at 48 kHz keeps at least 95% amplitude after convergence, while linear interpolation is about 86.6%; DC remains unity.
5. Reset/reuse, maximum-delay bounds and existing estimator/AEC tests remain green.
6. Adversarial full-scale histories produce positive and negative overshoot and verify saturation.

Mutation, ASan+UBSan, strict warnings, independent review and three-tree verification are required before push.

## Limits

Eight-frame added latency, mono only, no adaptive quality selection or real acoustic verification. Optional dual-reader delay crossfades are specified in `2026-11-18-audio-delay-crossfade-design.md`; active fades reject retargeting. The kernel is not a full sample-rate converter; drift compensation remains with the resampler.
