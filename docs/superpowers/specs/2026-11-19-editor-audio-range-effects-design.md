# Design: fade and normalize on a range, from the Audio page

## Problem

`break_editor_doc_audio_fade` and `normalize` work on the whole attachment
and the Audio page has no button for either. "对选区淡入淡出/归一化" is the
next audio gap after the selection slice (2026-11-19).

## Change

Core (`src/editor/editor_audio.{h,c}`, `test_editor_audio`):

- `break_editor_doc_audio_fade_range(doc, begin, end, fade_in_ms,
  fade_out_ms)` and `break_editor_doc_audio_normalize_range(doc, begin, end,
  target_dbfs)`: the same primitives (`audio_edit_fade_i16`,
  `audio_edit_normalize_i16`) applied to frames `[begin, end)` only; frames
  outside are byte-identical. One snapshot command per successful call,
  undoable; false (nothing changes, no history entry) for an empty or
  out-of-clip range or the same invalid arguments as the whole-clip calls.
  The normalize peak is measured inside the range. Digital silence in the
  range reports success and changes nothing (the primitive's behaviour), so
  it still records one undoable command, like the whole-clip call. A range
  shorter than the fade length is faded within the range.
- The whole-clip functions are unchanged.

Shell (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- Buttons `editor-audio-fade` ("Fade"/"淡入淡出", 10 ms in and out) and
  `editor-audio-normalize` ("Normalize"/"归一化", -1 dBFS) act on the
  selection, or on the whole clip when there is none. Like Trim/Cut they
  stop a running preview and refresh the page; the selection is cleared by
  the revision change. Without an attachment they log "audio edit failed".

## Tests

- `test_editor_audio`: a ramp buffer; fade_range and normalize_range change
  exactly the range (compared against the primitive applied to a copy of
  that slice) and leave the rest untouched; undo/redo restore and reapply;
  invalid ranges and arguments return false with no history entry; stereo.
- `test_editor_shell`: Normalize with a selection changes only it; Fade
  without one changes the whole clip; both are undoable; labels follow the
  language.

## Out of scope

Configurable fade length or target level, other effects (gain, reverse).

## Result

- Core: the new `test_editor_audio` case failed against stubs that ignored the range, then 12/12. Shell: the new `test_editor_shell` case failed against a stub, then 212/212.
- Mutations, each failing a test: fade range one frame longer, normalize over `[0, end)`, an empty range accepted; the shell ignoring the selection start, fade and normalize swapped, the no-selection end at half the clip.
- Self-checked after the review subagent was interrupted: digital silence (one undoable no-op command), a range shorter than the fade length, and the toolbar's six buttons leaving the info label over 200 px at the default window size are all pinned by tests.
