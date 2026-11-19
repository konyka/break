# Design: waveform selection with Trim and Cut on the Audio page

## Problem

The document already has undoable `break_editor_doc_audio_trim(begin, end)`
and `cut(begin, end)` (`src/editor/editor_audio.h`), but the Audio page has no
way to choose a range or run them: "选区编辑" is the next audio gap in
`docs/cross_engine/missing_capabilities.md` after seek (2026-11-19).

## Change

Panel (`apps/editor/editor_panel_audio.c`):

- Selection state: `[begin, end)` frames, empty when `begin == end`.
- A primary press without Shift seeks (as before) and clears the selection.
  A primary press with Shift selects from the cursor to the pressed frame
  (in either order; the pressed frame and the cursor frame are both
  included, so `begin = min` and `end = max + 1`, clamped to the clip). The cursor stays where it was.
- Buttons `editor-audio-trim` ("Trim"/"裁剪") and `editor-audio-cut`
  ("Cut"/"剪切") run `trim(begin, end)` / `cut(begin, end)` on the document.
  Without a selection they log "select a range first (Shift+click)". On
  success the selection and cursor are cleared, a running preview stops and
  the page refreshes at once; the edit is undoable through the document
  history like any other command. A Trim of the whole clip would change
  nothing and is refused like an empty selection.
- The selection is cleared on any attachment change (revision).
- The paint fills the selected columns with the theme's selection colour
  (opaque) behind the mid line and the bars.
- Info line: while a selection exists and nothing plays, the info line ends
  with " | sel <a> - <b> s" (while playing it shows the position instead).
  A Shift press anchors at the cursor (the last seek point), not at the
  moving play line; a Shift press while a range plays changes the selection
  but not the range being played.
- Every entry point (select, Shift press, Trim/Cut, seek) first catches up
  with an attachment change no tick has seen yet (an undo in the same
  frame), so a selection made on an older version of the clip is never
  applied.
- Accessors: `break_editor_shell_audio_select(shell, begin, end)` (the same
  as a Shift press pair, for tests and the remote), `..._audio_selection(shell,
  *begin, *end)` (false when empty), `..._audio_trim(shell)`,
  `..._audio_cut(shell)`.

## Tests

`test_editor_shell`: Shift+click after a click selects the range between
them; a plain click clears it; Trim keeps exactly the selected samples and
Undo restores them; Cut removes them; both clear the selection; without a
selection they log and change nothing; an edit clears the selection; the
selection clamps to the clip; button labels follow the language.

## Out of scope

Dragging, keyboard selection, fade/normalize on a selection, loop (playing
the selection only was added later, see the follow-up under Result).

## Result

- RED: the new `test_editor_shell` case failed against stubs (no buttons), then 211/211.
- Mutations, each failing the test: the pressed frame not included, Shift ignored, the selection not cleared on an attachment change, Cut calling trim, a plain click not clearing the selection.
- `editor_panel_audio_edit_selection` stops a running preview and refreshes the page at once (not only on the next tick).
- Review (Not ready, fixed): select and Trim/Cut did not catch up with an attachment change that no tick had seen, so an undo followed by Trim in the same frame trimmed the old frame range out of the restored clip. They now share the page's catch-up (also used by seek and the Shift anchor); a regression case pins it, and removing either guard fails it. Also: a whole-clip Trim is refused (mutation fails), Trim/Cut stopping a playing preview is tested, the info suffix is asserted in full, the band is described as opaque.
- Follow-up (play the selection): with a selection, Play plays only `[begin, end)` through `break_editor_audio_preview_play_range` and stops at the end of the range (the silent tail follows the range end); position and length are clip frames, so the info line reads "<pos> / <end> s". Without a selection Play starts from the cursor as before. Tests: a shell case (fake sink: exactly the range is written, the position includes the start, it stops at the end, the selection stays and replays) and a real-stream case at 44.1 kHz (stops by itself, position never past the range end; an empty or out-of-clip range is refused). Mutations: the panel ignoring the selection end, the preview copying past the range end; both fail.
- Range-play review (Not ready, fixed): the end of a range reset the cursor to 0 like the end of the clip, so the cursor line vanished and the next Shift press anchored at 0; now only reaching the clip end resets it. A seek inside the playing range keeps the range end (outside it plays to the clip end). New checks: the output's tail after the range is silence (filling it with the following samples fails), the cursor survives a range end, play_from past the end clamps to the last frame, a reversed range is refused, rendered samples of a 44.1 kHz range never exceed the range's last sample, a replay reopens the sink. Mutations for each fail a test.
