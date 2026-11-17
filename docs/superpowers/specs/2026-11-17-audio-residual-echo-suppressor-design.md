# Residual Echo Suppressor Design

Status: Implemented and validated; remaining limits are listed below

## Purpose

Suppress nonlinear echo left by the linear NLMS canceller without adding FFT latency or changing the canceller. The module is a mono, owner-thread postprocessor between `audio_echo_canceller_process_i16` and spectral/noise-gate processing.

## Approaches considered

1. **Reference/error envelope ratio with explicit near-end control (selected).** A residual-path estimate learns the AEC-error-to-reference power ratio. It is small, deterministic, allocation-free and testable end to end with the real canceller.
2. **Spectral coherence suppression.** This can address frequency-specific residual echo but adds STFT delay and needs a reliable coherence estimator; it is a later enhancement.
3. **Add nonlinear terms to the adaptive filter.** This can cancel modelled nonlinearities but changes the verified NLMS loop and does not provide a postprocessing safety net for unmodelled distortion.

## API and boundaries

`AudioResidualEchoSuppressorConfig` contains sample rate 8000..192000, reduction 0..80 dB, residual margin 0..40 dB, attack 0.1..1000 ms, release 1..10000 ms, path rise 0.1..60 dB/s, initial path -120..0 dB, reference gate -80..0 dBFS and hangover 0..1000 ms.

The caller-owned state supports init, reset, process, gain and path accessors. Init validates every field and writes the state only on success. Processing is mono and in place:

```c
void audio_residual_echo_suppressor_process_i16(AudioResidualEchoSuppressor *suppressor,
    const i16 *reference, i16 *capture, u32 frames, bool near_end_active);
```

The caller sets `near_end_active` from its detector. When true, the path estimate freezes and the gain opens. If false, reference-active frames update the residual path. The module does not infer near-end activity and must not be presented as an autonomous voice-activity detector.

## Algorithm

- Smooth reference and AEC-error power independently with a 10 ms one-pole filter.
- Reference power at or above the configured gate is active. Keep the last active power for the configured hangover so decaying echo tails can still be attenuated.
- For controlled residual frames, compute `ratio_db = 10 log10(max(error_power,1e-12)/max(active_reference_power,1e-12))`, clamp the learned ratio to at most 0 dB, lower the path immediately and raise it no faster than the configured dB/s.
- If the ratio is within `path + margin`, target the configured negative reduction; otherwise pass while the path adapts. Near-end activity or no active/hangover reference always targets 0 dB and does not adapt.
- Smooth gain changes with attack while opening and release while closing. Gain is in [-reduction,0] dB and never amplifies.
- Reset restores initial powers, path, gain, hangover and held reference power. Arbitrary chunks are equivalent to one call.

## Tests

1. Every configuration bound, NaN, NULL, failure atomicity and accessors.
2. No reference and near-end-controlled frames pass without learning; hangover suppresses a residual tail.
3. End to end with the real NLMS canceller: a nonlinear echo made from `0.25*x + 0.12*x*|x|` leaves residual energy, and the suppressor reduces the final half-second RMS by at least 10 dB.
4. A near-end tone mixed with residual echo stays within 1 dB when `near_end_active=true`, and the path estimate is unchanged.
5. Chunking is identical; reset matches a freshly initialized state; silence remains zero.
6. Mutation, ASan+UBSan, strict warnings, independent review and three-tree verification are required before push.

## Limits

Mono envelope suppression only; no spectral coherence, automatic near-end inference, stereo reference, or real acoustic verification. Incorrect near-end control can either pass residual echo or suppress wanted sound, so the control requirement is part of the public contract.
