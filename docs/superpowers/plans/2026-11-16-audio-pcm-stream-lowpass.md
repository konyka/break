# PCM streams: low-pass filter before downsampling (2026-11-16)

Status: Done. RED: 6 of the 9 new / rewritten `test_audio_extended` tests
failed on the unfiltered mixer (the 1 kHz passband, reopen and engine-rate
tests hold without a filter too and passed, as expected).
GREEN: `test_audio_extended` 63/63, `test_voice_playback` 4/4 (new
`fast_stream_filter_races_with_a_mixer_thread`), `test_audio_realtime_contract`
passes with the filter helper added to its checked callback bodies.
24 mutations, all killed (one, the `filtered` reset at open, survived
first; the reopen test now closes a 50 kHz stream with one filtered frame
still queued). TSan five runs and ASan+UBSan: no reports.

## Goal
`audio_pcm_stream_open_rate` converts a stream to the 48 kHz engine rate by
linear interpolation. For a stream faster than 48 kHz nothing removes the
content above 24 kHz first, so it folds back into the audible band
(`audio_extended.h` says so; `docs/Implementation_Status.md` lists it as
missing). This slice adds an anti-aliasing low-pass filter for those
streams. Streams at 48 kHz or below are unchanged.

## Design
- Enabled only when the stream rate is above `AUDIO_PCM_SAMPLE_RATE`.
- 4th-order Butterworth low-pass: two biquads (RBJ cookbook form,
  Q = 0.5412 and 1.3066), cutoff 21600 Hz (0.45 x 48000), coefficients
  computed for the stream rate at open with the bilinear transform. The
  DC gain is 1 and the response has a zero at the stream's Nyquist rate.
- Per channel, per stage, transposed direct form II state (2 values).
- The mixer filters ring frames in place, in order, each exactly once.
  Frames in `[tail, head)` belong to the consumer until `tail` passes
  them, so writing them back is safe. A mixer-private count `filtered`
  (frames after `tail` already filtered) tracks progress. Before a frame
  is read for interpolation, and before frames are released by the
  position step, the mixer filters up to that frame. Decimation skips
  frames for output, but the filter still sees every one of them.
- Filter state, coefficients and `filtered` are mixer-owned and follow the
  same rule as `pos`: open resets them on the owner thread while the slot
  is closed; the mixer reads or writes them only after seeing `open`.
- The filter helper runs in the audio callback; the realtime contract test
  gains a check that it does not allocate, free or do file I/O.

## Tests (TDD, `test_audio_extended`)
The test file builds an independent double-precision reference (same
filter, applied to every input frame, then decimated / interpolated).
- `pcm_stream_downsamples_96k`: output equals the reference instead of
  the raw even frames (the old exact values were the unfiltered ones).
- `pcm_stream_downsample_skips_a_frame_that_arrives_late`: same queue and
  underrun checks; the frame after the late one equals the reference, so
  the late frame went through the filter in order.
- 88.2 kHz (non-integer ratio) output equals interpolated reference.
- 96 kHz alternating +x/-x (the stream's Nyquist rate): unfiltered output
  is the constant x; filtered it settles near 0.
- 96 kHz 30 kHz sine: output RMS far below the unfiltered alias.
- 96 kHz 1 kHz sine: RMS within 1 dB of the input.
- Stereo: Nyquist tone on the left, DC on the right; left settles near 0,
  right stays at the DC level.
- Reopen: a slot closed mid-transient (50 kHz, one filtered frame still
  queued), reopened at 96 kHz, gives the same output as a fresh system
  for the same input (no leaked filter state or count).
- `test_voice_playback`: the producer / close / mixer-thread race also runs
  at 96 kHz, so TSan and ASan see the in-place filtering.
- 16k / 24k / 48k tests stay exact (filter off).

## Verification
RED then GREEN; mutation run over the new code; shadow check; ASan+UBSan
and TSan (`test_audio_extended`, `test_voice_playback`);
`test_audio_realtime_contract`; three full trees.

## Not done
Polyphase / windowed-sinc resampling (linear interpolation remains for the
rate conversion itself); filtering when upsampling (the interpolation
images above the source band are not removed); microphone capture and
encoding; panning / HRTF.
