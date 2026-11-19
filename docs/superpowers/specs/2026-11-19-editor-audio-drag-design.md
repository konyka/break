# Design: drag to select on the editor waveform

## Problem

The Audio page selects with Shift+click only (2026-11-19-editor-audio-selection);
"拖动选择" is the last interaction gap of the waveform editor.

## Change

`apps/editor/editor_panel_audio.c`: the waveform widget handles the pointer
move and release in addition to the press.

- A primary press without Shift keeps its current behaviour (clear the
  selection, seek) and starts a drag anchored at that frame.
- While the button is down, each move selects `[min(anchor, frame),
  max(anchor, frame) + 1)`, so both the anchor and the current frame are
  included and dragging either way gives the same range. A move that stays on
  the anchor frame leaves the plain click alone (no selection).
- The release applies the same range and ends the drag. A move or release
  without a drag is not consumed (`MY_RET_FAIL`), so it bubbles normally.
- The cursor stays at the press frame, so Play plays the dragged selection.
- An attachment change (the page's catch-up) ends the drag. So does the page
  becoming invisible mid-drag (a tab switch): myui keeps the grab on the
  pressed widget, so the handler checks the widget and its ancestors and
  ends the drag instead of selecting on a hidden page.

myui's dispatcher grabs the pressed widget and routes the following moves and
the release to it, so no extra capture is needed.

## Tests

`test_editor_shell`: a drag right selects exactly the frames between the press
and the release pixel (inclusive); dragging left gives the same range; the
selection updates before the release; a press and release on the same frame
stays a plain click (seek, no selection); a second press without a release
re-anchors the drag instead of extending the previous one; a move after a
mid-drag tab switch
leaves the selection unchanged and the drag ends; a move without a press
selects nothing.

## Out of scope

Dragging the edges of an existing selection, auto-scroll, zoom.

## Result

- RED: the new `test_editor_shell` case failed with no selection after a drag, then 213/213.
- Mutations, each failing the test: the end frame not included (caught after the test moved from a ±10-frame tolerance to exact pixel-derived frames), moves ignored, a move outside a drag consumed, a still move selecting, the drag flag not set at the press.
- Self-check (the review subagent for this slice was still running): a mid-drag tab switch kept the dispatcher's grab, so moves still changed the selection on a hidden page. Fixed by ending the drag when the widget or any ancestor is invisible; a regression case covers it and removing the check fails it.
