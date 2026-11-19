# Design: amplitude zoom for the audio waveform

The waveform draws each column from `min` to `max` scaled so that full scale
(32768) fills half the widget's height. A quiet recording is then a flat
line near the middle, and the editing features built on the view (selection,
fades) are hard to aim. Horizontal zoom is covered; this adds the vertical
counterpart.

## Change

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- A display gain on the panel: a multiplier applied to the sample values
  when painting, 1x by default, doubling or halving in powers of two between
  1x and 32x. It is a view property only, so it never touches the document
  and is not undoable.
- `break_editor_shell_audio_set_gain(shell, gain)` and
  `break_editor_shell_audio_gain(shell)`, with
  `editor_panel_audio_set_gain`/`_gain` behind them. The setter snaps the
  value to the nearest allowed power of two and clamps to [1, 32]; it
  returns the gain in effect afterwards.
- Two buttons on the view row, `editor-audio-gain-up` ("^") and
  `editor-audio-gain-down` ("v"), stepping the gain by a factor of two.
- The paint clips to the widget: a scaled column is cut at the top and
  bottom edges rather than drawn outside, so a loud clip at 32x shows a
  solid band instead of overflowing into the ruler.
- An attachment change resets the gain to 1x, like the view.
- The info line gains a " | <n>x" suffix while the gain is above 1x, so the
  state is visible without reading pixels.

## Tests

`test_editor_shell`, one case:

- The default gain is 1x; `set_gain` snaps 3 to 2 (the nearest power of two
  below), clamps 100 to 32 and 0 to 1.
- The two buttons step the gain up and down, stopping at 32 and 1.
- With a quiet clip (peak 1000) the painted column height at 8x is about
  eight times the 1x height, measured through the pixel surface over the
  waveform's rows.
- A loud clip at 32x stays inside the widget: no pixel of the waveform's
  colour appears in the ruler's rows.
- The info line shows "8x" at 8x and nothing at 1x.
- A trim resets the gain to 1x.

## Out of scope

A dB scale or a logarithmic view, per-channel display, auto-gain to the
clip's peak, gain as a document property.

## Result

Delivered, with one part of the design dropped as unnecessary.

`test_editor_shell` 221/221, the new case failing first on the missing
accessors. Mutations, each failing it: the paint scale ignoring the gain, the
32x clamp removed, the gain not reset on an attachment change, the info
suffix suppressed, and the down button stepping up.

**The manual clip was removed.** The spec called for clamping each column to
the widget so a loud clip at 32x cannot paint over the ruler. Writing it as
an explicit clamp left the mutation "delete the clamp" green, and the reason
is that `my_widget_paint` already calls `my_vgcanvas_clip_rect` with the
widget's own rect for every widget (`src/myui/myui/my_widget.c:603`). The
clamp was dead code, so the column maths is back to its plain form with a
comment pointing at that clip. The test still asserts no accent pixel
reaches the ruler and that the waveform is solid at 32x.

**The 1x row measurement is not a ratio.** A +-1000 square wave at 1x spans
under one pixel of the 54 px widget, so it is drawn at the 1-pixel minimum
and `rows_8x / rows_1x` is meaningless. The case predicts the 8x height
from `gain * amplitude * h / 32768` with a +-2 px tolerance and only checks
that 8x exceeds 1x.
