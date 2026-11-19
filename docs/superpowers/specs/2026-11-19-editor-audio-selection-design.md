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
  success the selection and cursor are cleared; the edit is undoable
  through the document history like any other command, and the page
  refreshes on the next tick through the revision.
- The selection is cleared on any attachment change (revision).
- The paint fills the selected columns with a translucent band behind the
  bars.
- Info line: while a selection exists and nothing plays, the info line ends
  with " | sel <a> - <b> s".
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

Dragging, keyboard selection, fade/normalize on a selection, play the
selection only, loop.

## Result

- RED: the new `test_editor_shell` case failed against stubs (no buttons), then 211/211.
- Mutations, each failing the test: the pressed frame not included, Shift ignored, the selection not cleared on an attachment change, Cut calling trim, a plain click not clearing the selection.
- `editor_panel_audio_edit_selection` stops a running preview and refreshes the page at once (not only on the next tick).
