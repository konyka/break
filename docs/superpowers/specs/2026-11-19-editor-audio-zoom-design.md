# Design: zoom and scroll the audio waveform

## Problem

The waveform always spans the whole clip, so a 65536-frame attachment gives
about 80 frames per pixel and fine edits are impossible. "缩放" (and the
scrolling it needs) is the last gap of the waveform editor.

## Change

Core (`src/editor/editor_audio.{h,c}`, `test_editor_audio`):

- `break_editor_doc_audio_waveform_range(doc, begin, end, columns, out_min,
  out_max)`: the existing per-column min/max over `[begin, end)` instead of
  the whole clip. `break_editor_doc_audio_waveform` is
  `..._range(doc, 0, frames, …)`. False, writing nothing, for an empty or
  out-of-clip range and the same invalid arguments as before.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- View state `[view_begin, view_end)`, the whole clip by default and reset
  by any attachment change.
- `break_editor_shell_audio_zoom(shell, in)`: halves (in) or doubles (out)
  the view length around its centre, clamped to the clip and to at least 16
  frames; returns whether the view changed. Buttons `editor-audio-zoom-in`
  ("+") and `editor-audio-zoom-out` ("-").
- `break_editor_shell_audio_scroll(shell, forward)`: moves the view by a
  quarter of its length, clamped to the clip. Buttons
  `editor-audio-scroll-left` ("<") and `editor-audio-scroll-right` (">").
- `break_editor_shell_audio_view(shell, *begin, *end)` reports the view.
- The waveform, the ruler, the selection band, the cursor line, and every
  pointer mapping (click, Shift, drag) use the view instead of the clip, so
  the x in pixels maps to `view_begin + x * view_len / width`.
- The ruler's tick step is chosen for the view, so zooming in shows finer
  ticks; the labels stay absolute clip times.
- Zoom in keeps the selection and the cursor; the selection band is clipped
  to the view and the cursor line is drawn only when it is inside it.

## Tests

- `test_editor_audio`: the range waveform matches the whole-clip one for the
  full range, and matches a manual min/max for a sub-range; invalid ranges.
- `test_editor_shell`: the default view is the whole clip; zoom in halves it
  around the centre and the waveform columns then come from that part; zoom
  out and the clamps; scrolling moves by a quarter and stops at both ends; a
  click inside a zoomed view selects the mapped frame; the ruler ticks use
  the view; an attachment change resets the view.

## Out of scope

Wheel and keyboard zoom, a scrollbar widget, auto-scroll while playing.

## Result

Delivered as designed, with one deviation: the four view buttons sit on their
own 20 px row (`editor-audio-view-bar`) between the toolbar and the ruler.
Putting them on the toolbar shrank the info label to 174 px and broke the
existing 200 px regression assertion.

`test_editor_audio` 13/13 and `test_editor_shell` 216/216, both after a
failing stub run. Seven mutations all turn the suite red: the range waveform
without the `begin` offset, a narrow column covering no frame (which first
survived, so the test gained a stereo case), zoom in anchored at the view
start, the 16-frame floor removed, the scroll step halved, the pointer
mapping without `view_begin`, the ruler x without `view_begin`, and an
attachment change that does not reset the view. Two of the test's assertions
were added during that pass: a click and a ruler tick read inside the
scrolled view `[2000, 4000)`, which is what pins both `view_begin` offsets.

No independent review this round (the previous reviewer run took 47 minutes).
Self-checks instead: the info label still measures above 200 px at the default
size, the ruler's first tick lands at a round time inside the view with
`x >= 0`, and the tick's `seen_view_*` comparison recomputes the columns after
a zoom.
