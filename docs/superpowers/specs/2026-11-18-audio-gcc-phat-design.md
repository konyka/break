# GCC-PHAT Delay Estimator Design

Status: Implemented and validated; remaining limits are listed below

## Purpose

Add a frequency-domain generalized cross-correlation with phase transform for playback-to-capture delay estimation. This complements, rather than replaces, the exact normalized time-domain estimator and its tracker.

## Approaches considered

1. **Independent object using existing real FFT (selected).** Clear ownership, no change to current estimator behavior, and allocation-free estimation after create.
2. **Add a second estimator mode to the existing object.** Shares history but makes every caller understand mode-specific size limits and scratch allocation.
3. **Defer until a full spectral tracking pipeline exists.** Unnecessary; the FFT and delay-line tests already provide the required numerical base.

## API and limits

`AudioGccPhatConfig` has maximum delay 1..96000 and correlation window 16..96000, subject to `window + max_delay <= 32768`. The FFT size is the next power of two at least twice that history, never above 65536, so correlation is linear rather than wrapped.

The opaque object supports create, destroy, reset, aligned `push_i16(reference,capture,frames)` and `estimate(&delay_frames,&peak)`. Delay is a double-frame value; peak is the signed PHAT inverse value at the selected integer lag, not a normalized correlation. Failure leaves outputs untouched until `window+max_delay` frames exist, the latest capture window is silent, or all reference history is silent.

## Algorithm

- Keep mirrored histories so the oldest-to-newest sequence is contiguous.
- Zero-pad both histories to FFT size N and compute `cross = conj(FFT(reference))*FFT(capture)`.
- Replace each cross bin by `cross/|cross|`, or zero when its magnitude is below 1e-12. Inverse FFT yields PHAT correlation.
- For capture[n]=reference[n-L], select the largest absolute value at L=0..max_delay, with the smaller lag on a tie. Return its signed peak.
- At an interior peak, parabolic-interpolate absolute inverse values with the same concavity, finite and ±0.5-frame guards as the existing subframe estimator. Boundaries and invalid curves return the integer lag.
- Only create allocates; owner-thread use, no platform dependency.

## Tests

1. Configuration including FFT-size boundary, failure atomicity, NULL and readiness/silence.
2. Exact 0 and maximum-delay endpoints; clean interior integer peaks allow 0.01-frame numerical refinement. Include an inverted echo sign, a unit-impulse PHAT peak of 1, constant-input ties and a 1000-frame delay.
3. Sinc-generated 12.25/12.5/12.75-frame signals estimate within 0.25 frame under added noise; compare integer peak with the existing time-domain estimate where appropriate.
4. Chunking and reset agree; random input uses a direct time-domain lag reference. Immediately after reset, estimation fails with untouched outputs; history-1 new frames still fail and the final frame permits estimation.
5. Direct internal pure tests pin the required power-of-two FFT size and exact earlier-tie selection; extreme-u32 configurations must not wrap the history sum into acceptance.
6. Mutation, ASan+UBSan, strict warnings, independent review and three-tree verification before push.

## Limits

No automatic drift tracking integration, clock-drift compensation, multi-channel processing, normalized confidence score or real acoustic validation. PHAT emphasizes phase and can be sensitive to low-energy spectral bins; its raw peak must not be presented as normalized correlation.
