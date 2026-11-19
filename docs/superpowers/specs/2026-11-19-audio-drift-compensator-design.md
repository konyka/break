# Design: closed-loop clock drift compensator

## Problem

`audio_drift_estimator` turns delay measurements into a drift in ppm and
`audio_drift_resampler` resamples with a dynamic ratio, but nothing closes the
loop: no component turns a measured delay slope into a ratio, and the voice
pipeline therefore has no drift compensation (listed as missing in
`docs/cross_engine/missing_capabilities.md` and `docs/design/audio_extended.md`).

## Model

The capture holds an echo of the playback reference: `capture[n] ≈ ref[n - d(n)]`.
With a relative clock drift `s` (frames of delay per frame), `d(n) = d0 + s·n`.
Resampling the reference with ratio `r` (input frames per output frame) gives
`ref'[m] = ref[m·r]`, and the delay measured against `ref'` has the residual
slope `s' = 1 - (1 - s) / r`. The slope is zero for `r = 1 - s`. Given the
current ratio and a measured residual slope, the ratio that removes it is
`r · (1 - s')`; the compensator applies `r_new = r · (1 - gain · s')`.

## Component

`engine/src/audio/audio_drift_compensator.{h,c}`, compiled into the audio
library next to the estimator and resampler. Mono, owner thread, only create
allocates (through the estimator).

```c
typedef struct {
    AudioDriftEstimatorConfig estimator;
    u32 min_samples;          /* 2..estimator.window_size */
    f32 max_correction_ppm;   /* 1..estimator.max_abs_drift_ppm */
    f32 gain;                 /* (0, 1] */
    bool robust;              /* repeated-median instead of least squares */
} AudioDriftCompensatorConfig;
```

- `create` / `destroy` (NULL no-op) / `reset` (ratio back to 1, estimator and
  resampler cleared, counters kept).
- `observe(frame_index, delay_frames, correlation)`: forwards to the
  estimator, returns whether it was accepted.
- `update()`: when at least `min_samples` measurements are held and the
  estimate succeeds, computes the new ratio, clamps `|r - 1|` to
  `max_correction_ppm · 1e-6`, applies it to the resampler, clears the
  estimator window (the residual slope changes with the ratio) and returns
  true. Otherwise false and nothing changes.
- `ratio()`, `correction_ppm()` (`(1 - r) · 1e6`, the drift the ratio
  removes), `corrections()` (applied updates), `clamped()` (updates that hit
  the limit).
- `output_capacity(input_frames)` and `process_i16(in, frames, out, cap,
  out_frames)`: the reference passes through the resampler (linear mode).

Errors: INVALID for NULL or out-of-range config, OVERLOAD when memory runs out;
`*out` written only on success.

## Tests (`test_audio_drift_compensator`)

1. Config validation, NULL handling, initial state (ratio 1, no corrections).
2. Closed loop on the delay model: a true drift of +100 ppm, measurements
   computed from the residual slope of the current ratio; after a few updates
   the ratio is `1 - 100e-6` within 1e-7 and the correction is 100 ppm.
3. Clamp: +500 ppm with a 200 ppm limit stops at `1 - 200e-6` and counts
   `clamped`.
4. Too few or low-confidence measurements: `update` is false and the ratio
   does not move.
5. Processing: ratio 1 is the identity; after a correction 100 000 input frames
   give the output count the ratio implies (±2).
6. `reset` returns the ratio to 1 and empties the window.

## Out of scope

Wiring into the core_app voice pump (next slice), multichannel, sinc mode for
the compensator, real device validation.
