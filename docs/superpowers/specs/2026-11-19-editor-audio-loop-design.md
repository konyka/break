# Design: loop the played audio range

## Problem

Preview playback always stops at the end of the clip or of the selection
(2026-11-19-editor-audio-{preview,selection}); "循环" is the last playback
gap of the Audio page.

## Change

- `break_editor_audio_preview_set_loop` / `_loop`
  (`apps/editor/editor_audio_preview.{h,c}`): off after create. When the
  played range ends and the output has drained, the preview rewinds to the
  range's start frame and writes it again instead of stopping. The sink stays
  open, so nothing is closed or reopened between passes and the cursor is
  untouched. A sink error during the re-arm stops playback as usual.
- The page gets a "Loop" / "循环" checkbox (`editor-audio-loop`) in the
  toolbar. `break_editor_shell_audio_set_loop(shell, loop)` sets it (and the
  box) and returns the state afterwards; `break_editor_shell_audio_loop`
  reads it. The flag survives Stop and an attachment change; turning it off
  while playing stops at the next end.
- Everything that already stops playback still does: Stop, an attachment
  change (the page's catch-up), a sink that refuses to accept frames.

## Tests

`test_editor_shell`: with the loop off the clip still stops at its end; with
it on a selection is written again from its start without closing the sink,
and keeps looping; Stop ends it and keeps the flag and the selection;
turning it off mid-play stops at the next end; an edit while looping stops
it; the checkbox toggles the loop through a real pointer click and follows
the language.

## Out of scope

Loop count, a loop region separate from the selection, crossfading the seam.

## Result

- RED: the new `test_editor_shell` case failed with no Loop checkbox, then 215/215.
- Mutations, each failing the test: the re-arm skipped, the rewind to frame 0 instead of the range start, no write after the rewind, the panel not forwarding the flag to the preview, the checkbox "changed" handler not connected.
