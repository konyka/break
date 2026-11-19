# Design: labels on the dB grid lines

The grid (`2026-11-20-editor-audio-db-grid-design.md`) draws lines at -6,
-12, -18 and -24 dBFS, but nothing says which line is which. With the
amplitude zoom changing how many lines fit and where they sit, counting from
the centre is unreliable — at 4x the top line is -18, not -6.

## Change

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- Each drawn line gets its level written just above it at the left edge, as
  "-6", "-12" and so on (no "dB" suffix, since the readout label already
  names the unit and the lines are 1 px apart from their text).
- The text uses the ruler's secondary colour, drawn after the lines and
  before the trace, so the waveform stays on top.
- A label is skipped when the line is within the text's height of the lane's
  top or bottom edge, so it cannot spill into the neighbouring lane or the
  ruler. The line itself is still drawn.
- Only the upper half of each lane is labelled: the lower line is the same
  level mirrored, and labelling both doubles the clutter for no information.
- `break_editor_shell_audio_grid_label(shell, i, *text)` reports the label
  the last paint used for grid entry `i` (empty for an unlabelled entry), so
  the pairing of level and line is testable.

## Tests

`test_editor_shell`, extending the grid case:

- With a clip attached, each upper-half grid entry reports a label matching
  its level ("-6" for -6.0 dBFS), and each lower-half entry reports an empty
  one.
- At 4x the labels follow the levels that still fit, so the topmost entry
  reports "-18" rather than "-6".
- An entry too close to the lane's edge reports an empty label while
  `break_editor_shell_audio_grid` still reports the line.
- A label index past the count returns false.

## Out of scope

A unit suffix, labels on the right edge too, a configurable text size, a
label on the centre line (0 dBFS is the centre by definition).

## Result

Delivered as designed. `test_editor_shell` 227/227 (the grid case grew
rather than a new case being added), failing to link first.

Mutations, each failing the test: the room-for-text condition replaced by
`true`, and the mirrored lower entry carrying the same label as the upper
one.

The spec expected the "too close to the edge" path to be reachable on a
full-height lane by raising the gain. It is not: on the default 54 px lane
the levels that survive the grid's own fit rule land at most 13.5 px from
the centre, and anything past 27 px is dropped outright, so no power-of-two
gain puts a line within 11 px of the top. The stereo case is what exercises
it — a 27 px lane leaves no room above its upper lines, so those keep their
lines and lose their labels. The test asserts exactly that, and the comment
in the case says why the gain path cannot.
