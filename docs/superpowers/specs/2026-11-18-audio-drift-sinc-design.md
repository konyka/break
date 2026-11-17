# Sinc Clock-Drift Compensation Design

Status: Approved for autonomous implementation under the active goal

## Purpose

Add an optional high-quality interpolation mode to `AudioDriftResampler` while preserving every default linear output, dynamic-ratio behavior, caller ownership and allocation-free operation.

## Approaches considered

1. **Fixed causal 16-tap Blackman-windowed sinc with eight input frames of lookahead (selected).** Matches the delay-line quality mode, supports arbitrary chunking and near-unity drift ratios, and needs only fixed caller-owned history.
2. **Ratio-scaled long sinc kernel.** Would add strong-downsampling anti-aliasing, but requires up to 160 taps, variable latency and substantially more complex mode/ratio transitions; rejected for this drift-focused slice.
3. **Reuse `AudioDelayLine` or the mixer PCM stream.** Neither owns absolute dynamic resampling positions; reuse would couple unrelated lifecycle and latency contracts.

## API and state

- `AudioResult audio_drift_resampler_set_sinc(AudioDriftResampler *resampler, bool enabled)`; NULL returns `AUDIO_INVALID`.
- `bool audio_drift_resampler_sinc(const AudioDriftResampler *resampler)`; false for NULL.
- `u32 audio_drift_resampler_sinc_extra_delay(const AudioDriftResampler *resampler)`; eight input frames when enabled, zero otherwise/NULL.
- Extend the caller-owned struct with `bool sinc` and `i16 history[32]`; existing fields remain. Consumers rebuild against the new header. No heap allocation is added.
- Init selects linear mode. Reset preserves ratio and mode, resets positions/`previous`, and zeroes history. Setters are owner-thread calls between processing calls.

## Processing

Every input frame is written to `history[index % 32]` in both modes, so enabling sinc uses real past samples. Default linear processing retains its existing previous/current equation and output schedule.

In sinc mode, an output at absolute input position `p` is emitted only when `p + 8 <= current_input_index`. This includes integer positions, keeping latency fixed at eight input frames. For `i=floor(p)` and `f=p-i`:

- Zero fractional part reads exact input `i` after the same lookahead gate.
- Otherwise, for `j=-7..8`, read input `i+j` and use weight `sinc(f-j) * Blackman(j+7)` with the standard window `0.42 - 0.5*cos(2πtap/15) + 0.08*cos(4πtap/15)`.
- Inputs before position zero are zero. Normalize by the full kernel weight sum, round with `nearbyint`, then saturate to `[-32768,32767]` before converting to i16.
- No future sample beyond the current input is read. The 32-entry ring covers the oldest possible tap with margin.

When switching from sinc to linear, pending positions are drained from history with ordinary linear interpolation rather than duplicating the latest sample. Let `pending=max(0, next_input-next_output)`. The old bound is `ceil(input_frames/ratio)+2`; when linear and `pending>1`, add `ceil(pending/ratio)`. Uninterrupted linear has `pending<=1`, and sinc retains the old bound because its lookahead gate can only reduce output count. Overflow still returns zero. Capacity validation precedes all state and output changes.

The actual output count remains authoritative. Finite streams must append enough zero input to drain wanted positions; zero-input processing remains a no-op and is not an implicit flush.

## Tests

Add six tests to the existing six-test suite:

1. Mode/NULL/accessor contracts, init default and reset preservation.
2. Ratio-one delayed identity and ratio-two exact decimation, including explicit zero-padding tail drain.
3. Independent fractional-kernel reference at ratio 0.75 with a live change to 1.25, including initial silence and arbitrary chunk equivalence.
4. Both mode-switch directions, sinc-to-linear backlog capacity and output correctness, and primed-state capacity-failure atomicity including history bytes.
5. High-frequency amplitude and converged DC gain versus the linear mode.
6. Positive and negative full-scale overshoot saturation.

Run targeted mutations, ASan+UBSan, strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

Mono only. The fixed kernel improves fractional interpolation and near-unity drift compensation; it is not a ratio-scaled anti-aliasing filter for strong downsampling. No crossfade, automatic estimator wiring, closed-loop control, flush API or real-device validation is added. OpenGL/Vulkan and all unrelated subsystems remain unchanged.
