# Audio: acoustic echo cancellation for captured voice

Status: Done

## Goal

When the speakers play the far side of a voice call, the microphone picks
it up and sends it back as echo. Add an echo canceller for the owner thread
that learns the speaker-to-microphone path from the playback signal and
subtracts the predicted echo from the capture, before the noise gate and AGC.

## API (`engine/src/audio/audio_echo_canceller.h`)

- `AudioEchoCancellerConfig { sample_rate, taps, step_size,
  double_talk_threshold, hangover_ms }`. Ranges: rate 8000..192000, taps
  1..`AUDIO_ECHO_CANCELLER_MAX_TAPS` (8192), step size 0.001..1, double-talk
  threshold 0..1 (0 turns detection off), hangover 0..1000 ms. INVALID
  otherwise; OVERLOAD when memory runs out; `*out` written only on success.
- `audio_echo_canceller_create`, `_destroy` (NULL is a no-op), `_reset`,
  `_process_i16(aec, reference, capture, frames)` (mono, capture in place),
  `_weight(aec, k)`.
- The caller aligns the reference with the capture (the playback samples
  that reach the microphone in the same frame, or earlier); the filter
  covers an echo path up to `taps` frames long.

## Behaviour

- x = reference / 32768, d = capture / 32768. History x(n), x(n-1), ...,
  x(n-taps+1).
- Prediction y = sum w(k) x(n-k) (k ascending); error e = d - y; output
  `nearbyint(e * 32768)` clamped to i16.
- NLMS update w(k) += mu * e * x(n-k) / (sum x^2 + taps * 1e-6).
- Geigel double-talk detection: when the threshold is above 0 and
  |d| > threshold * max|x(n-k)|, the near side is talking (silence on
  both sides is not double talk); the filter
  stops adapting for that frame and the next hangover frames.
- Frame by frame; chunking does not change the output.

## Tests (`test_audio_echo_canceller`)

1. Config validation, `*out` untouched, destroy NULL.
2. White-noise reference through a two-tap echo path: echo return loss
   enhancement above 30 dB after one second; weights near the path.
3. Silent reference: the capture passes unchanged.
4. Double talk: with detection the weights stay near the path and the
   near-side tone keeps its level; without it the weights move further.
5. Echo path change: the filter converges again.
6. Reset clears the weights and the history.
7. Chunk sizes 1, 7 and 480 give identical output; an independent
   reference model agrees within 1 LSB.

## Result

- `test_audio_echo_canceller`: 8 tests. RED on link, then GREEN.
- The first double-talk run gave only 18 dB SNR at mu = 0.5: the detector
  fires only once the near tone exceeds the threshold, and the updates in
  the frames before that move the weights. The test uses mu = 0.1 and also
  checks that the weights stay frozen after detection (31 dB with
  detection, 12 dB without).
- Mutations: the first round left 4 of 35 alive. Added tests for threshold
  0 still learning, out-of-range weight reads, and silence not starting a
  hangover. The double-talk comparison became strict `>`, and the unused
  i16 history mirror was removed. Final: 34 of 34 caught.
- ASan+UBSan and `-Wshadow -Wdouble-promotion` clean.
- Not done: automatic delay estimation between reference and capture,
  nonlinear residual echo suppression, a frequency-domain implementation,
  a stereo reference, and real speaker and microphone verification.
