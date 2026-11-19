# Design: dynamic limiting in the oversampled domain

The dynamic limiter (`2026-11-20-editor-audio-lookahead-limiter-design.md`)
bounds the *sample* peak. A signal whose samples straddle a crest still
reconstructs above the ceiling, so a clip limited to -1 dBFS can leave a
converter or encoder at +0.4 dBTP. The static true-peak edit solves that by
scaling everything; what is missing is the dynamic version — per-sample gain
against a true-peak ceiling.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_limit_dynamic_true_peak(doc, ceiling_dbtp,
  lookahead_ms, release_ms)`: the same look-ahead envelope, but the
  requirement at each frame comes from the reconstructed signal rather than
  the stored samples.
- The reconstruction reuses the true-peak measurement's polyphase kernel: for
  each frame, the largest magnitude among its 4 interpolated phases is the
  value the ceiling applies to. That is computed once into a per-frame array
  before the envelope pass, so the gain loop stays one pass.
- Because the gain varies per frame, the result's true peak is not exactly
  the ceiling: lowering a frame's gain also lowers its neighbours'
  reconstruction, so the achieved peak lands at or below the ceiling. The
  function guarantees "at or below", and the test re-measures to check it.
- The arguments and refusals match the sample-domain version, with the
  ceiling in dBTP.
- Bounded work: the per-frame reconstruction array is the same static
  allocation style as the waveform columns, sized for
  `BREAK_EDITOR_AUDIO_MAX_FRAMES`.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_limit_dynamic_true_peak(shell, ceiling,
  lookahead_ms, release_ms)` and an `editor-audio-dyn-tp-limit` button at
  -1 dBTP / 5 ms / 50 ms, labelled "Limit TP" (en) / "动态限真峰" (zh).

## Tests

- `test_editor_audio`: a clip whose intersample peaks exceed the ceiling
  while its samples do not is brought under the ceiling (re-measured),
  which the sample-domain limiter leaves alone — the test runs both on
  copies and asserts the contrast; the quiet part keeps its level; the undo
  restores the samples; a clip already under the ceiling is untouched; the
  rejected arguments change nothing.
- `test_editor_shell`: the button brings a hot clip under -1 dBTP; a silent
  clip logs the edit-failed line.

## Out of scope

An oversampled *output* (the edit still writes the original rate), a
separate attack time, per-channel envelopes, iterating the gain to land
exactly on the ceiling.

## Result

Delivered as designed. `test_editor_audio` 23/23 and `test_editor_shell`
233/233, both after a failing run.

Mutations, each failing a test: the per-frame reconstruction replaced by the
stored sample's magnitude (which is exactly the case this edit exists for),
the already-under-ceiling early return removed, and the button wired to the
sample-domain limiter instead of this one.

The core case is built around a signal the sample-domain limiter cannot see:
a sine sampled at ±45° of its crest, amplitude 29000, so the samples read
20506 — under the -1 dBFS ceiling of 29204 — while the reconstruction
reaches past it. The case runs the sample-domain limiter first and asserts it
leaves the clip byte-identical with its true peak still above the ceiling,
then runs this one and re-measures. That contrast is the whole justification
for the second function, so the test states it directly rather than only
checking the new one in isolation.
