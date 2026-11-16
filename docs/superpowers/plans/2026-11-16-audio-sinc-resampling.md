# PCM streams: windowed-sinc resampling (2026-11-16)

Status: Done

## Goal
A PCM stream at a rate other than the engine rate (48 kHz) is converted by
linear interpolation. Linear interpolation dulls the top of the band (a
4 kHz tone at 16 kHz input loses about 1.8 dB) and leaves images (the same
tone produces a 12 kHz image about 21 dB down). This slice adds an opt-in
band-limited interpolator per stream.

## Design
- `AudioResampleMode { AUDIO_RESAMPLE_LINEAR = 0, AUDIO_RESAMPLE_SINC }` and
  `audio_pcm_stream_set_resample(as, h, mode)`. INVALID for an unknown mode,
  a zero handle or no system; STALE for a closed handle. Open resets the
  mode to linear, so existing callers keep their output.
- Kernel: Lanczos with a = 8 (16 taps), cutoff at the source Nyquist rate.
  An output between source frames i and i+1 at fraction f is
  `sum_j x[i+j] L(j - f) / sum_j L(j - f)` for j = -7 .. 8, where
  `L(x) = sinc(x) sinc(x / 8)`. The weights are normalised so a constant
  passes unchanged. f = 0 gives frame i exactly.
- Lookahead: an output needs frames up to i + 8, so a sinc stream plays
  silence (an underrun, the position does not move) until 9 frames past
  the position are queued. That is 8 source frames of latency (0.5 ms at
  16 kHz).
- History: frames before `tail` are released to the producer. The mixer
  copies every released frame (after the low-pass, for fast streams) into
  an 8-frame history ring it owns, in both modes, so switching to sinc
  mid-stream uses the real past frames. Open zeroes the frames (the push
  counter is free-running and needs no reset); frames before the stream
  start are zero.
- A stream faster than 48 kHz still runs the Butterworth low-pass first;
  the mixer filters frames up to i + 8 before reading them.
- A stream at the engine rate has no fractional positions; sinc mode does
  not change it (no lookahead, samples come out as written).
- The mode is an atomic read once per mixer callback; the owner thread
  may change it at any time.

## Tests (TDD, `test_audio_extended`)
- arguments: invalid mode, handle, system; stale handle; reopen is linear.
- 16 kHz random input matches a double-precision Lanczos model.
- lookahead: 8 queued frames underrun, the 9th starts playback at the
  first position; the model's values follow.
- quality: a 4 kHz tone at 16 kHz has a much smaller error against the
  ideal 48 kHz tone than linear interpolation gives.
- 88.2 kHz input: Butterworth then sinc matches the model.
- stereo channels stay apart.
- engine rate: unchanged, no lookahead.
- reopen clears the history; a linear-to-sinc switch uses the real past
  frames.

## Not done
Polyphase tables, variable kernel width for strong decimation (the
Butterworth still does the anti-aliasing), resampling of clip voices.

## Result
- RED: 7 of 8 new tests failed against a stub (the engine-rate test passes
  by design), 73 existing passed. GREEN: `test_audio_extended` 81/81,
  `test_voice_playback` 4/4, audio ctest 5/5 (the realtime contract range
  `pcm_stream_filter_to` .. `pcm_stream_read` covers the new helpers).
- Mutation: 20 mutants in the first round, 2 survived. The kernel's sign
  shortcut `sin(pi (j - f)) = -(-1)^j sin(pi f)` was replaced by the direct
  `sin(pi x)` (the shortcut's sign could not be told apart by the
  normalised weights, so it was not worth keeping); the history counter
  reset at open was redundant and was removed. Final run: 19 mutants, all
  killed.
- Numbers (4 kHz tone at 16 kHz, RMS error against the ideal 48 kHz tone,
  amplitude 0.5): linear 0.075, sinc 0.00026.
- ASan+UBSan and three TSan runs: no reports.
