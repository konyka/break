# Design: wheel zoom and follow-the-playhead for the audio waveform

The waveform now has a view (`2026-11-19-editor-audio-zoom-design.md`) with
`+`/`-`/`<`/`>` buttons. Two things from that spec's "out of scope" remain:
reaching the zoom without the buttons, and keeping a zoomed view on the
playing position.

## Change

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- The waveform consumes `MY_EVENT_POINTER_WHEEL`: a positive delta zooms in,
  a negative one zooms out, one step per row, through the same
  `editor_panel_audio_zoom` the buttons use. The frame under the pointer
  stays under the pointer, so zooming at the right edge keeps that edge.
  Plain scrolling without a modifier zooms; with Shift it scrolls the view
  (`editor_panel_audio_scroll`), one step per row, forward on a negative
  delta so it reads like scrolling right.
- `break_editor_shell_audio_set_follow(shell, on)` and
  `break_editor_shell_audio_follow(shell)` with a `editor-audio-follow`
  checkbox on the view row, off by default. While it is on and the preview
  is playing, the tick keeps the playing position inside the view: when it
  passes the view's end, the view jumps forward by its own length, keeping
  the same length (clamped to the clip's end); when it is before the view's
  start, the view jumps back the same way. A view covering the whole clip
  never moves.
- Zooming at a point needs a pointer-anchored variant of the existing
  centre-anchored zoom, so `editor_panel_audio_zoom_at(panel, in, frame)`
  carries the anchor and `editor_panel_audio_zoom` calls it with the view's
  centre.

## Tests

`test_editor_shell`, one case each:

- Wheel: a wheel event over the left quarter of the waveform zooms in and
  keeps that quarter's frame under the pointer; wheeling out returns to the
  whole clip; a Shift wheel scrolls instead of zooming, in both directions
  and clamped at both ends; a wheel over an empty page changes nothing.
- Follow: with a zoomed view and the checkbox on, pumping the preview past
  the view's end moves the view forward by its length and keeps the position
  inside it; with the checkbox off the view stays put; a full view never
  moves; stopping playback stops the following.

## Out of scope

Keyboard zoom shortcuts, a scrollbar widget, smooth (per-frame) scrolling
rather than page jumps.

## Result

Delivered as designed. `test_editor_shell` 218/218, with both new cases
failing first (the wheel one on the view length, the follow one on the
missing checkbox).

Mutations, each failing a test: the anchor fraction replaced by the view
centre, the wheel direction flipped, the Shift branch never taken, the
follow jump stepping one frame instead of a view length, and the follow flag
ignored. Two assertions were tightened during that pass: the follow case now
pins the exact view after each jump (`[1500,2500)` to `[2500,3500)`, then
back to `[0,1000)`), because a one-frame step first survived.

One planned guard turned out to be redundant: an explicit "a full view never
moves" early return is unnecessary, since a view covering the clip always
contains the position and the containment check returns first. Removing the
guard kept the suite green, so the code now carries the containment check
alone with a comment, and the test still covers the full-view case.

The right-edge assertion is a tolerance, not an equality: anchoring at pixel
`w-1` keeps that frame in the last percent of the view rather than exactly at
its end, which is what the fraction-preserving math gives.
