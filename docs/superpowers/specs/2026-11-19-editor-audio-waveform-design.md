# Design: editor audio waveform view

## Problem

The editor document can hold a PCM16 attachment (`editor_audio.h`: attach, WAV
import/export, undoable trim/cut/fade/normalize/mix), but the editor app never
shows it: there is no way to open a WAV from the asset browser and no waveform.
"波形 UI" is listed as missing in `docs/cross_engine/missing_capabilities.md`
(sections 10/12) and in the WAV export spec.

## Change

Core (`engine/src/editor/editor_audio.{h,c}`, tested in `test_editor_audio`):

- `break_editor_doc_audio_revision(doc)`: u64 that changes whenever the
  attachment changes: attach, every committed edit, undo and redo of an audio
  command, and detach (reset/load). It is 0 for a NULL document and survives
  detach (it is stored in the document, not in the attachment), so a view
  never mistakes a new attachment for the old one.
- `break_editor_doc_audio_waveform(doc, columns, out_min, out_max)`: splits
  the frames into `columns` contiguous ranges (column c covers frames
  `[c*frames/columns, (c+1)*frames/columns)`, computed in u64) and writes, for
  each column, the minimum and maximum sample over all channels. A column with
  no frames (columns > frames) gets the value of the frame it falls on
  (`c*frames/columns`), so the view has no gaps. False, writing nothing, for a
  NULL document or output, no attachment, zero frames, or columns of 0 or above
  `BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS` (4096). Read-only.

Shell (`engine/apps/editor`, tested in `test_editor_shell`):

- New panel TU `editor_panel_audio.c` on the `editor_shell_internal.h`
  contract (create/build/tick/retranslate/destroy). Page
  `editor-audio-panel` is the fifth tab ("Audio" / "音频") of the bottom tool
  window. It holds an info label (`editor-audio-info`) and a waveform widget
  (`editor-audio-waveform`).
- Info label: "No audio: click a .wav asset to open it" when nothing is
  attached, otherwise "<rate> Hz, <channels> ch, <seconds> s" (3 decimals).
- The tick compares the document's revision and the widget width with the
  last ones it saw; on a change it recomputes one column per pixel, capped at
  the frame count and at 4096, into fixed panel storage and invalidates the widget. The
  paint fills the background and draws one vertical line per column from min
  to max around the centre line. No allocation per tick.
- Asset browser: clicking a `*.wav` row opens the file with
  `break_editor_doc_audio_attach_wav` when the document has no attachment. With
  an attachment it only logs that one is already open: replacing it would leave
  audio snapshot commands in the history that belong to the old buffer. On
  success it logs the file name, selects the Audio tab and refreshes the panel;
  on failure it logs that the WAV could not be opened.
- Accessors for tests: `break_editor_shell_audio_info_text`,
  `break_editor_shell_audio_column_count`,
  `break_editor_shell_audio_column(shell, i, *min, *max)`.

## Tests

- `test_editor_audio`: waveform of a known mono and stereo buffer at
  columns < frames, = frames and > frames; every invalid argument returns
  false and leaves the outputs untouched; revision changes on attach, each
  edit, undo, redo and reset, and not on a failed edit or a save.
- `test_editor_shell`: the Audio tab exists and shows the empty text; clicking
  a generated WAV in the asset browser attaches it, selects the tab, and the
  info and columns match the file; an undoable edit through the document API
  changes the columns on the next tick; a second WAV click with an attachment
  logs and changes nothing; a corrupt `.wav` logs and attaches nothing; the
  language switch retranslates the empty text.

## Out of scope

Playback, selection on the waveform, editing from the UI, zoom/scroll,
replacing an open attachment, VFS paths.

## Result

- Core: three new `test_editor_audio` cases failed against stubs, then 11/11. Shell: the new `test_editor_shell` case failed against an empty page, then 207/207; the tab-count and settings-bound assertions moved from 4 to 5.
- Mutations, each failing a test: column range off by one, only the first channel scanned, no revision bump on undo/redo, no revision bump on detach, the tick ignoring the revision.
