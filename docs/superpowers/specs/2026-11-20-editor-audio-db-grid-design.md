# Design: a dB grid on the audio waveform

The page reports the view's peak and RMS as numbers
(`2026-11-19-editor-audio-db-design.md`), but the waveform itself has only a
centre line. Judging "is this trace near -6 or near -20" from its height
means doing the arithmetic in your head, and the amplitude zoom changes the
mapping as soon as it is touched.

## Change

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- Each lane draws horizontal lines at fixed dBFS levels, mirrored above and
  below its centre: -6, -12, -18 and -24 dBFS. A level whose line would fall
  closer than 4 px to the centre or outside the lane is skipped, so a short
  lane or a high gain does not turn into a solid block.
- The lines use the theme's border colour (the centre line's colour) and are
  drawn before the trace, so the waveform stays readable on top.
- The levels follow the amplitude zoom: at 2x, -6 dBFS sits where -12 dBFS
  was, because the gain scales the sample-to-pixel mapping the grid shares.
- `break_editor_shell_audio_grid_count(shell)` and
  `break_editor_shell_audio_grid(shell, i, *db, *y)` report the grid the
  last paint used (one entry per drawn line, both halves, in lane 0's
  coordinates), so the mapping is testable without reading pixels.
- A grid checkbox is not added: the lines are cheap and always useful, and
  the view row is already full.

## Tests

`test_editor_shell`, one case:

- With no attachment the grid is empty.
- With a clip attached, the grid has the four levels above and below the
  centre, in lane 0's coordinates, each `y` matching
  `centre -+ 10^(db/20) * gain * half_lane_height`.
- At 4x gain the -12 dBFS line sits where -24 was at 1x, and the levels that
  no longer fit are dropped.
- A stereo clip reports the same lane-0 entries (the second lane repeats them
  at its own offset, which the paint handles).
- The entries stay within the lane and no closer than 4 px to the centre.

## Out of scope

Labels on the lines, a user-chosen level set, a logarithmic vertical axis
(the trace stays linear; only the grid is in dB), a grid on the ruler.

## Result

Delivered as designed. `test_editor_shell` 227/227, the case failing to link
first.

Mutations, each failing the test: the dB exponent divided by 10 instead of
20, the `offset < 4 px` half of the fit condition removed, the
`offset > lane_h/2` half removed, the grid model not reset at the start of a
paint, and the lower half's y computed with the upper half's offset.

Two notes:

- On the default 54 px lane only -6 and -12 dBFS clear the 4 px gap at 1x,
  so the gain assertion checks the -6 → -18 pair (one step of 4x) rather
  than -12 → -24, which the spec had assumed. The case logs nothing about
  the levels it does not find; it looks for the pair it needs and asserts
  that -6 is gone at 4x.
- The grid model is paint output, and `audio_waveform_on_paint` holds a
  `const EditorPanelAudio *`. Rather than make the whole paint path
  non-const, it writes through a single named alias with a comment saying
  why.
