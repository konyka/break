# Design: a dB readout for the visible audio

The page shows the waveform in linear sample values: the gain button says
"8x", and the only level information is the shape of the trace. Deciding
whether a recording is too quiet, or whether a normalize actually reached its
target, means comparing peaks by eye. A number in dBFS answers it directly,
and it is the unit the existing normalize API already takes.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_peak_range(doc, begin, end, out_peak, out_rms)`:
  the largest absolute sample and the RMS over `[begin, end)` across every
  channel, both as doubles in [0, 32768]. False, writing nothing, for the
  same invalid ranges as the waveform functions.
- RMS is computed in double over the raw samples, so a long range cannot
  overflow.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_peak_db(shell)` and
  `break_editor_shell_audio_rms_db(shell)`: the peak and RMS of the current
  view in dBFS, with digital silence reported as a floor of -120 dB rather
  than negative infinity. 0 dB without an attachment is ambiguous, so both
  return the floor there too.
- The info line gains " | peak <x> dB rms <y> dB" (one decimal) when an
  attachment is present, after the existing length and gain parts.
- The figures follow the view, so zooming into a quiet passage reports that
  passage.

## Tests

- `test_editor_audio`: a full-scale square wave reports peak 32767 and an
  RMS equal to its amplitude; a half-amplitude one reports half; a silent
  clip reports 0 for both; a sub-range picks up only its own samples; the
  invalid ranges write nothing.
- `test_editor_shell`: a clip at -6 dBFS (amplitude 16384) reports a peak
  near -6.0 and an RMS near -6.0 for a square wave; a silent clip reports
  the -120 floor; the info line carries both numbers; after zooming into a
  quiet half the numbers drop; a normalize to -1 dBFS makes the peak read
  about -1.0.

## Out of scope

A true-peak (oversampled) measurement, LUFS or any weighted loudness, a
per-channel readout, a dB grid on the waveform.

## Result

Delivered, with the readout moved off the info line.

`test_editor_audio` 15/15 and `test_editor_shell` 226/226, both after a
failing run. Mutations, each failing a test: RMS replaced by the peak, the
peak scan keeping the first sample instead of the maximum, the dB factor
changed from 20 to 10, the levels measured over the whole clip instead of the
view, and the label's two numbers swapped.

**The dB text is its own label, not an info-line suffix.** Appending it to
the info line broke four existing cases that assert the line exactly
("8000 Hz, 2 ch, 0.050 s" and friends). Rather than rewrite those
assertions, the readout went to `editor-audio-levels` on the view row, which
leaves the info line exactly what its format string says.

Two test-data notes, both from mutations that first survived:

- A square wave has RMS equal to its peak, and its peak is in the first
  sample. Both the core and the panel cases now include a clip with one loud
  frame among quiet ones, which separates the two figures and moves the peak
  off the first sample.
- `audio_db_of`'s `value <= 0.0` guard is not pinned by a mutation, and it
  cannot be: `log10(0)` is `-inf`, which the floor comparison already maps to
  -120. The guard is there to avoid raising `FE_DIVBYZERO`, and the comment
  says so.
