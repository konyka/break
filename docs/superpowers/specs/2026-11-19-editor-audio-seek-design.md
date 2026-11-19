# Design: seek and play cursor on the editor waveform

## Problem

The Audio page plays the attachment from the start only
(2026-11-19-editor-audio-preview); "跳转" is listed as missing, and the
waveform has no play cursor, so the user cannot see or choose where playback
is.

## Change

Preview (`apps/editor/editor_audio_preview.{h,c}`):

- `break_editor_audio_preview_play_from(preview, doc, start_frame)`: like
  `play`, starting at `start_frame` (clamped to the last frame). `play` is
  `play_from(…, 0)`. The position reported is `start + consumed`, still at
  most the clip length.
- `break_editor_audio_preview_seek(preview, doc, frame)`: while playing,
  restarts from `frame` (the sink is closed and reopened, so queued audio
  from the old position is dropped); while stopped it only records the
  frame. Returns whether it plays afterwards.
- `break_editor_audio_preview_cursor_frames`: the frame the next Play starts
  from (0 initially; set by a stopped seek; reset to 0 when playback reaches
  the end by itself).

Shell (`editor_panel_audio.c`):

- A primary-button press on the waveform maps x to a frame
  (`x * frames / width`, clamped) and seeks.
- Play starts from the cursor. Stop keeps the cursor where it was set (it
  does not move to the stopped position). An attachment change resets the
  cursor to 0.
- The paint draws a 1-pixel vertical line at the playing position, or at the
  cursor when stopped and the cursor is not 0.
- Accessors: `break_editor_shell_audio_cursor_frames`,
  `break_editor_shell_audio_seek(shell, frame)` (same as a click).

## Tests

- `test_editor_shell` with the fake sink: a click at the waveform's middle
  sets the cursor near frames/2 while stopped; Play then writes from that
  frame; a click while playing reopens the sink and writes from the new
  frame; the position includes the start; playing to the end resets the
  cursor; an edit resets it; seek past the end clamps.
- `test_editor_audio_sink`: play_from on the real stream renders the
  samples starting at the requested frame.

## Out of scope

Dragging a cursor, selections, looping, zoom.

## Result

- RED: the new `test_editor_shell` case (the cursor stayed 0) and the new `test_editor_audio_sink` case (rendering started at frame 0) failed against stubs, then 210/210 and 4/4.
- Mutations, each failing a test: writing from frame 0, position without the start, no cursor reset at the end, no cursor reset on an edit, a seek while playing not restarting, Play ignoring the cursor.
- `break_editor_audio_preview_reset_cursor` was added for the panel's reset on an attachment change.
