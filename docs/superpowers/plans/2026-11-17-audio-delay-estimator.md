# Audio: delay estimation and a reference delay line for echo cancellation

Status: Done

## Goal

`audio_echo_canceller` needs the playback reference aligned with the
capture, and the caller had to know the speaker-to-microphone latency. Add
an estimator that finds that delay from the signals, and a delay line that
applies it to the reference before the canceller.

## API (`engine/src/audio/audio_delay_estimator.h`)

- `AudioDelayEstimatorConfig { max_delay_frames 1..96000, window_frames
  16..96000 }`; create/destroy/reset/push_i16/estimate.
- `estimate`: the latest `window` capture frames c(i) against the reference
  r(i - L) for L = 0..max_delay. Score `S(L) = sum c r / sqrt(sum c^2 *
  sum r^2)` with exact i64 sums. Returns the L with the largest |S| (the
  smaller L on a tie) and S. False until window + max_delay frames were
  pushed, or when the capture window or every reference window is silent.
- `AudioDelayLine`: create(max_delay 0..96000), set_delay, delay,
  process_i16 (out may alias in); out[n] = in[n - delay], silence before
  the first frame; a new delay reads the history at once.

## Tests (`test_audio_delay_estimator`)

1. Config validation, `*out` untouched; NULL handling. Reset clears only
   the push count (older frames are never read).
2. White noise delayed by 0, 1, 237 and max_delay frames, with gain 0.3
   and added noise: the estimate is exact and |S| is high.
3. An inverted echo (negative gain) is found with S < 0.
4. Not enough frames, a silent capture, a silent reference: false.
5. Pushing in chunks of 1, 7 and 480 gives the same estimate as one push;
   reset forgets everything.
6. A brute-force reference model agrees on S at every lag (exact).
7. Delay line: identity at 0, delay of 5 across chunk boundaries, in-place,
   changing the delay reads the history, max delay, invalid delay.
8. End to end: echo with a 300-frame latency through a 32-tap canceller.
   Unaligned, the echo stays; aligned by the estimated delay, ERLE > 30 dB.

## Result

- `test_audio_delay_estimator`: 8 tests (a tie test was added: a periodic
  reference picks the smallest lag). RED on link, then GREEN.
- End to end: a 300-frame echo through a 32-tap canceller, ERLE below 3 dB
  unaligned and above 30 dB aligned by the estimate.
- Mutations: the first round left 1 of 27 alive; clearing the history and
  position in reset had no effect and was removed. Final: 26 of 26 caught.
- ASan+UBSan and `-Wshadow -Wdouble-promotion` clean.
- Not done: sub-frame precision, GCC-PHAT or frequency-domain speed-up,
  drift tracking and clock-drift compensation.
