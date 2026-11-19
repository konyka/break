# Design: true-peak measurement

`break_editor_doc_audio_peak_range` reports the largest stored sample. That
is the sample peak, and it understates the real analogue level: a signal
whose samples straddle a waveform crest reconstructs above both of them. A
clip that normalize left at -1.0 dBFS sample peak can reach +0.5 dBTP, which
is what a broadcast check or a lossy encoder will object to.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_true_peak_range(doc, begin, end, out_peak)`: the
  largest absolute value of the signal reconstructed at 4x the sample rate,
  per channel, over `[begin, end)`. Same invalid-range rules as the sample
  peak, and the value is a double that may exceed 32768 (a reconstruction
  can overshoot full scale).
- The interpolation is a windowed-sinc polyphase FIR: 4 phases of a 33-tap
  kernel (8 samples either side), Blackman-windowed, built once into a
  static table at first use. Phase 0 is the identity, so the result is never
  below the sample peak.
- Samples outside the range are read from the clip when they exist and
  treated as zero past its ends, so a range at the clip's edge does not read
  out of bounds.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_true_peak_db(shell)`: the view's true peak in
  dBTP, with the same -120 floor. Values above full scale are positive dB
  and are not clamped — that is the point of the measurement.
- The levels label gains " tp <x> dB" after the peak and RMS figures.

## Tests

- `test_editor_audio`: a full-scale square wave's true peak is at or above
  its sample peak; a sine sampled so its crest falls between samples reports
  a true peak above the sample peak (the classic intersample case); a silent
  clip reports 0; a sub-range sees only its own samples; the invalid ranges
  write nothing; a range at the clip's start and end does not fault (checked
  under ASan).
- `test_editor_shell`: a clip normalized to -1 dBFS reports a true peak at or
  above its sample peak; the label carries the "tp" figure; a silent clip
  reports the floor.

## Out of scope

The exact ITU-R BS.1770 4x filter coefficients (this is a windowed sinc, not
the standard's filter), LUFS, a true-peak limiter, oversampling factors
above 4.

## Result

Delivered as designed. `test_editor_audio` 16/16 and `test_editor_shell`
228/228, both after a failing run.

Mutations, each failing a test: only phase 0 evaluated (which reduces the
measurement to the sample peak), the `index >= frames` bounds check dropped,
the kernel's DC normalization removed, the peak scan keeping the first value
instead of the maximum, the channel loop stopping after channel 0, and the
absolute value dropped.

Three numbers in the test came from running it, and are worth stating:

- The intersample sine reads 1.431x its sample peak. That is the expected
  physics: samples at ±45° of a sine read `sin(45°) = 0.707` of the
  amplitude, so recovering the crest is a factor of √2. The assertion is a
  band around it rather than the 1.3 upper bound the spec guessed.
- A sub-range starting right after a loud passage is not quiet: the kernel
  reaches 16 samples back, so the loud half bleeds in. The case measures
  from 216 rather than 200 and says why.
- An all-negative constant clip reports 20459 for an 18000 magnitude. The
  clip's edge is a step against the zero outside it, and a sinc
  reconstruction rings past the level there. The bound allows it, with a
  comment that a real recording has no such step.
