# Design: a true-peak limiter

Normalizing to a loudness target caps its gain at the *sample* peak's
headroom, so the result can still exceed full scale between samples: a clip
at -1 dBFS sample peak may sit at +0.5 dBTP, which a lossy encoder or a
broadcast check will reject. The measurement exists
(`2026-11-20-editor-audio-true-peak-design.md`); what is missing is an edit
that brings a clip under a dBTP ceiling.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_limit_true_peak(doc, ceiling_dbtp)`: measures the
  clip's true peak and, when it is above the ceiling, applies the constant
  gain that brings it to the ceiling, as one undoable snapshot. When the clip
  is already under the ceiling it changes nothing and returns true (the
  postcondition holds either way), without adding a history entry.
- A constant gain, not a dynamic limiter: the whole clip is scaled, so the
  waveform's shape and its loudness range are untouched. The name says
  "limit" because the postcondition is a ceiling, and the doc comment is
  explicit that this is gain reduction rather than per-sample limiting.
- False, changing nothing, for no attachment, a ceiling outside
  [-20, 0] dBTP, and a digitally silent clip.
- The achieved true peak is at or below the ceiling, within the rounding of
  one i16 step, which the test checks by re-measuring.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_limit_true_peak(shell, ceiling)` runs it and
  refreshes the page; a refusal logs the existing edit-failed line.
- An `editor-audio-tp-limit` button on the view row at -1 dBTP, the usual
  delivery ceiling, labelled "-1 dBTP" (en) / "限峰 -1" (zh).

## Tests

- `test_editor_audio`: a clip whose true peak is above the ceiling is brought
  to it (re-measured); a clip already below is left byte-identical and adds no
  history entry; the undo restores the samples; the rejected cases change
  nothing; the loudness drops by about the same amount the peak did, showing
  it is a constant gain.
- `test_editor_shell`: the button brings a hot clip under -1 dBTP; a silent
  clip logs the edit-failed line.

## Out of scope

A look-ahead dynamic limiter (per-sample gain), an oversampled reconstruction
in the edit itself (the measurement's 4x is used to decide the gain, not to
resample), a ceiling in the settings.

## Result

Delivered as designed. `test_editor_audio` 21/21 and `test_editor_shell`
231/231, both after a failing run.

Mutations, each failing a test: the already-under-ceiling early return
removed (which would add a history entry for a no-op), the ceiling exponent
divided by 10 instead of 20, the *sample* peak measured instead of the true
peak (the whole point of the edit), the button's ceiling changed from -1 to
-6 dBTP, and the failure path not logging.

The shell case needed a 32000-amplitude sine rather than 25000: at 25000 the
intersample reconstruction reaches 35355, which is -2.25 dBTP and already
under the -1 ceiling, so the button had nothing to do. At 32000 the figure is
positive, which is the case the ceiling exists for.

The i18n table's "actually translated" check applies here too, so the
Chinese label is "限峰 -1" rather than a copy of "-1 dBTP".
