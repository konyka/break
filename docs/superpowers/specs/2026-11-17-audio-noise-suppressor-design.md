# Spectral Noise Suppressor Design

Status: Implemented and validated; remaining limits are listed below

## Purpose

Add mono captured-voice spectral noise reduction without replacing the existing time-domain noise gate. The suppressor must run on the owner thread, allocate only during creation, accept arbitrary input chunks in place, and produce deterministic output with a fixed disclosed delay.

## Approaches considered

1. **STFT with smoothed per-bin noise tracking and over-subtracted Wiener-style gain (selected).** It uses the new `audio_fft`, needs no dependency, attenuates noise between tonal components, and has independently testable numerical behavior.
2. **Keep only the existing time-domain noise gate.** This has lower delay but cannot remove noise while a louder signal keeps the gate open, so it does not meet the spectral-reduction gap.
3. **Integrate a learned or external codec noise reducer.** This would add model/dependency and licensing constraints and is outside this bounded slice.

## Public contract

`AudioNoiseSuppressorConfig` contains sample rate 8000..192000, FFT frame size 16..1024 (a power of two), maximum attenuation 0..80 dB, noise-floor rise 0.1..60 dB/s, and initial noise floor -120..0 dBFS. Invalid input returns `AUDIO_INVALID`; allocation failure returns `AUDIO_OVERLOAD`; `*out` changes only on success.

The opaque `AudioNoiseSuppressor` supports create, destroy, reset, in-place mono i16 processing, and `audio_noise_suppressor_latency_frames`. Latency equals `frame_size`; NULL returns zero. To drain a stream, feed `frame_size` silence frames.

## Signal flow

- Use a periodic Hann analysis window, `audio_fft_forward`, per-bin gain, `audio_fft_inverse`, and unwindowed overlap-add at 50% overlap. The two Hann contributions sum to one, so unit gain reconstructs the input exactly apart from floating-point rounding.
- Normalize input by 32768. For raw bin power `(re^2 + im^2) / sum(window^2)`, use `P = max(raw, 1e-12)` (-120 dBFS) for both noise tracking and gain, so silence has a defined ratio. Smooth P independently per bin with a 100 ms exponential average S. The noise floor falls immediately to S and rises by at most the configured dB/s per completed hop, never above S. Keeping S separate avoids treating every raw random dip as the stationary noise level.
- Apply amplitude gain `max(10^(-max_attenuation_db/20), 1 - 2*noise/P)`. The fixed factor 2 is over-subtraction: the original unit factor produced only 6.0 dB suppression in the white-noise test after convergence, below the required 10 dB. Zero attenuation still has gain exactly one.
- Prime the transform with a half-window of zeros. Discard the first block's negative-time output. This makes unit-gain reconstruction exact from the first real sample rather than fading in the first half-window.
- An N-entry output ring starts with N zeros. Each completed non-priming block appends N/2 samples. Output index n corresponds to processed input n-N, and arbitrary chunking does not change the sequence.

`reset` restores the exact post-create state, including noise estimates, zero history, overlap, output delay and block phase. Processing performs no allocation, file I/O or locking.

## Validation

1. Validate all configuration bounds, power-of-two sizes, failure atomicity and NULL handling.
2. At 0 dB attenuation, output must equal input delayed by exactly N frames for different sizes and arbitrary chunks.
3. Stationary white noise must lose at least 10 dB of power after convergence with a 30 dB attenuation limit.
4. During startup and the documented tracking transient, a 440 Hz tone in noise retains its projected amplitude within 1 dB while the separate noise case proves suppression. A sustained tone is eventually learned as noise; a two-second test with a fast 60 dB/s rise must show at least 10 dB attenuation in the final quarter second.
5. One-call and 1/7/255-frame chunk processing must be identical; reset after loud training must match a fresh object processing a quiet tone; silence stays zero.
6. Mutation testing must cover validation, delay/ring behavior, priming, windowing, noise tracking, gain floor and overlap-add. Run ASan+UBSan, strict warnings, independent review and all three full test trees before push.

## Limits

Mono only; no learned model, multi-channel coupling, automatic latency compensation in the voice transport, or real-microphone listening validation in this slice. Sustained tones and other stationary sounds are eventually learned as noise; only the configured tracking transient preserves them. Those limitations must remain explicit in the documentation.
