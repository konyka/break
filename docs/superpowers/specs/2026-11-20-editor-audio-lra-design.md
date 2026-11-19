# Design: short-term loudness and loudness range

Integrated LUFS (`2026-11-20-editor-audio-lufs-design.md`) is one number for
the whole view. It cannot distinguish a clip that sits steadily at -23 LUFS
from one that alternates between -35 and -12: both integrate to about the
same figure, but the second will be unlistenable without a compressor. EBU
R128 answers this with the loudness range (LRA), computed from the
distribution of 3-second short-term windows.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_short_term_range(doc, begin, end, out_lufs)`: the
  loudness of the last 3 seconds of the range, i.e. the short-term figure
  at the range's end point. False for a range shorter than 3 s.
- `break_editor_doc_audio_loudness_range_lra(doc, begin, end, out_lra)`: the
  LRA in LU, from 3-second windows stepped by 1 second: drop windows below
  -70 LUFS, drop those more than 20 LU below the mean of the survivors, then
  take the 95th percentile minus the 10th. False for a range with fewer than
  two surviving windows, since a range is not defined by one window.
- Both reuse the K-weighting and the block machinery of the integrated
  measurement; the shared part moves into one helper that takes the window
  length and step rather than being copied.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_short_term_lufs(shell)` and
  `break_editor_shell_audio_lra(shell)`, both reporting the floor (-70 LUFS
  and 0 LU) when the view is too short.
- The levels label gains " lra <x> LU" when a figure is available, after the
  integrated figure.

## Tests

- `test_editor_audio`: a steady tone over 5 s has an LRA near 0 and a
  short-term figure close to its integrated one; a clip alternating between
  two levels 20 LU apart reports an LRA in that neighbourhood; a clip whose
  last 3 s are much quieter than its start reports a short-term figure well
  below its integrated one; a range under 3 s is rejected by both; a range
  with one window is rejected by the LRA but not the short-term; silence is
  the floor.
- `test_editor_shell`: a long enough view reports both figures and the label
  names the LRA; a 1 s view reports the floors and the label omits it.

## Out of scope

Momentary (400 ms) loudness as a separate accessor (the integrated
measurement's blocks are already 400 ms), a loudness graph over time, a
normalize-to-LUFS edit.

## Result

Delivered as designed. `test_editor_audio` 18/18 and `test_editor_shell`
228/228, both after a failing run.

Mutations, each failing a test: the short-term window taken from the range's
start rather than its end, the LRA's step set equal to its window (losing the
overlap), the 10th percentile replaced by the minimum, and the label naming a
range when the measurement failed.

**One thing the tests cannot separate.** The -20 LU relative gate and the
10th-percentile trim both drop the same window at the lengths available here.
`break_editor_doc_audio_attach` caps a clip at 65536 frames and refuses a
rate below 8 kHz, so the longest measurable clip is 8.19 s — six 3-second
windows stepped by one second. With six windows the 10th percentile index is
1 and the 95th is 5, so a single quiet outlier is removed by the percentile
whether or not the relative gate fires, and replacing the gate with the
absolute floor leaves the suite green. The case pins that one of the two
acts, and says so in a comment; the relative gate's own arithmetic is pinned
by the integrated measurement's case, which uses the same expression at -10
LU.

The refactor was the point of ordering this after the integrated slice: the
block loop, the K-weighting setup and the per-channel filtering now exist
once in `audio_window_loudness`, and the three measurements differ only in
the window length, the step, and how they reduce the per-window figures.
