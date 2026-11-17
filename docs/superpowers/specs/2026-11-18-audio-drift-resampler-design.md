# Clock-Drift Resampler Design

Status: Implemented and validated; remaining limits are listed below

## Purpose

Provide the compensation counterpart to `audio_drift_estimator`: a streaming mono i16 resampler whose input/output ratio can change between calls. No hidden drift estimation or threading is built in.

## Approaches considered

1. **Stateful linear interpolation with an absolute next-output position (selected).** Small, deterministic, supports arbitrary input chunks and ratio changes without allocating history.
2. **Reuse the playback PCM stream.** That API targets mixer-owned 48 kHz output and would couple this standalone component to unrelated stream lifecycle.
3. **Sinc resampling.** Higher quality but separate configuration and more state; deferred until quality requirements justify it.

## API

Caller-owned `AudioDriftResampler` supports init, reset, set_ratio, ratio, output_capacity and process.

- Ratio is input frames per output frame, finite and in [0.1,10]. One is exact pass-through, two downsamples, 0.5 upsamples.
- `output_capacity(input_frames)` returns a safe upper bound or 0 on overflow/NULL.
- `process_i16(in,in_frames,out,out_capacity,&out_frames)` validates all arguments and capacity before changing state. It consumes every input frame and writes the actual output count only on success. Input and output buffers must not overlap.
- Reset preserves the currently configured ratio and resets position/history. Only init/reset change initial streaming state; no allocation occurs anywhere.

## Interpolation

Keep the absolute index of the next input and the absolute position of the next output. For each new input at index n, emit while position <= n. A position exactly n selects the new sample; otherwise interpolate between the previous and current samples. Advance position by ratio after every output. Ratio changes affect only future advances.

This gives exact identity, exact decimation and known half-position upsampling. Upsampling may need the next input before producing an intermediate output; the API reports the actual count rather than concealing that dependency.

## Tests

1. Ratio/NULL/capacity validation and reset behavior.
2. Ratio-one identity and ratio-two exact decimation.
3. Ratio-half known seven-sample output and arbitrary chunk equivalence.
4. A live 0.5-to-2.0 ratio transition preserves position/history with hand-calculated nonlinear samples. Insufficient-capacity failure atomicity covers a primed state, unchanged output bytes and count, plus reset/fresh equivalence.
5. A real 50 ppm estimator result drives ratio `1 + ppm*1e-6` and processes a known sequence.

Mutation, ASan+UBSan, strict warnings, independent review and three-tree verification are required before push.

## Limits

Default behavior remains mono linear interpolation. The optional fixed-kernel sinc extension is specified in `docs/superpowers/specs/2026-11-18-audio-drift-sinc-design.md`; it does not provide ratio-scaled strong-downsampling anti-aliasing. Multichannel coupling, automatic estimator wiring, closed-loop clock control and real-device validation remain unimplemented. The caller chooses the correct ratio sign for its pipeline.
