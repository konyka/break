# Design: keyboard zoom and scroll for the audio waveform

The waveform has a view with buttons and wheel control
(`2026-11-19-editor-audio-zoom-design.md`,
`2026-11-19-editor-audio-wheel-design.md`). The last item left in those
specs' out-of-scope lists is reaching the view from the keyboard.

The editor's global shortcuts (`k_editor_shortcuts` in
`apps/editor/editor_panels.c`) already use the arrow keys and `Home` for the
outliner and the viewport, so the waveform's keys must be scoped: they only
act while the waveform holds the key focus, and they consume the event so it
does not also reach the shell.

## Change

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- The waveform widget becomes focusable, so a primary press gives it the key
  focus (`my_event_dispatch` focuses the nearest focusable ancestor of the
  pressed widget, which is then the waveform itself).
- While it has focus it handles `MY_EVENT_KEY_DOWN`:
  - `+` and `=` zoom in, `-` zooms out, around the view's centre.
  - `Left`/`Right` scroll the view back and forward.
  - `Home` returns the view to the whole clip.
  - Anything else is not consumed and bubbles to the shell as before.
- Each handled key consumes the event (`MY_RET_OK`), so `Left`/`Right`/`Home`
  do not also move the outliner selection or reset the 3D camera while the
  waveform is focused. Without an attachment nothing is consumed.

## Tests

`test_editor_shell`, one case:

- A press on the waveform focuses it; `+` halves the view, `-` restores it,
  `Right` and `Left` scroll by a quarter and clamp at the ends, `Home`
  returns to the whole clip.
- A handled key is consumed: with the waveform focused and a zoomed view,
  `Home` does not reset the 3D camera (the shell's `Home` action), and
  `Left`/`Right` do not change the outliner selection.
- An unhandled key still bubbles: with the waveform focused, `q` selects the
  Select tool through the shell's shortcut.
- Without an attachment none of the keys are consumed, so `Home` reaches the
  shell.

## Out of scope

A scrollbar widget, smooth scrolling, rebindable keys.

## Result

Delivered as designed. `test_editor_shell` 219/219, the new case failing
first on the focus requirement (the waveform was not focusable).

Mutations, each failing the test: the widget left non-focusable, `+` and `-`
swapped, `Left` and `Right` swapped, the key branch returning
`MY_RET_FAIL` instead of consuming, and the no-attachment guard removed.

Two notes on how the assertions had to be written:

- `my_event_dispatch` returns true only when a vtable `on_event` consumed
  the event. The shell's own shortcuts hang off an emitter listener on the
  root, which does not count as consumption, so an unhandled key dispatches
  as `false` even though the shell acted on it. The case therefore checks the
  effect (the tool label, the camera distance), not the return value.
- The shell's outliner walk uses `Up`/`Down`, not the arrows the waveform
  takes, so "the arrows do not move the outliner" cannot be observed. The
  case instead moves the focus off the waveform and checks the opposite
  direction: `Up` then walks the outliner and leaves the view untouched, and
  `+` no longer zooms.
