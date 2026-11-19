# Design: a loudness curve over the waveform

The page reports loudness as three numbers for the whole view (integrated,
short-term at the end, and the range). None of them says *where* a clip is
loud: finding the passage that drags the integrated figure down means
zooming around and re-reading the numbers.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_loudness_curve(doc, begin, end, points, out_lufs)`:
  fills `points` short-term loudness values, each measured over the 3-second
  window ending at its own position, spread evenly across `[begin, end)`.
  Positions whose window would start before `begin` use the window from
  `begin` onwards, so the first points are shorter-window estimates rather
  than gaps.
- False, writing nothing, for the usual invalid ranges, `points` outside
  1..256, and a range shorter than one 400 ms block.
- Values are floored at -70 LUFS, like the other loudness functions.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- The waveform draws the curve over lane 0 as a polyline in the theme's
  secondary text colour: one point per 8 pixels of width, mapped from
  [-60, 0] LUFS onto the lane's height, bottom to top. A value at the floor
  is not drawn, so a silent passage leaves a gap rather than a line pinned to
  the bottom.
- The curve is recomputed with the columns (so it follows the view) and
  skipped when the view is too short to measure.
- `break_editor_shell_audio_curve_count(shell)` and
  `break_editor_shell_audio_curve(shell, i, *lufs, *x, *y)` report what the
  last paint used.

## Tests

- `test_editor_audio`: a clip that is loud then quiet gives a curve whose
  first points are well above its last; the point count matches the request;
  a steady clip's points are all within a LU of each other; the rejected
  arguments write nothing.
- `test_editor_shell`: a long enough view reports a curve whose points sit
  inside the waveform and whose y falls as the loudness falls; a 100 ms view
  reports no curve.

## Out of scope

A separate curve per lane, a filled area rather than a line, the integrated
or LRA figures drawn as reference lines, a curve on the ruler.

## Result

Delivered as designed. `test_editor_audio` 20/20 and `test_editor_shell`
230/230, both after a failing run.

Mutations, each failing a test: the point position fixed at the range's end
(so every point reads the same figure), the window not clamped to the range's
start, the y mapping inverted, and the floor values drawn instead of skipped.

The last one needed a case of its own. With a loud-then-quiet clip every
point is above the floor, so drawing the floor values changes nothing
observable. The shell case now also measures a loud-then-digitally-silent
clip, where the silent half produces floor values: the curve has strictly
fewer points than the quiet-half clip's, and every reported point is above
the floor.
