# Design: fit the amplitude zoom to the visible peak

The amplitude zoom (`2026-11-19-editor-audio-gain-design.md`) is stepped by
hand with `v`/`^`. Finding the right factor for a given recording means
clicking and looking several times, and the right factor changes as soon as
the view scrolls into a quieter part.

## Change

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_fit_gain(shell)` and
  `editor_panel_audio_fit_gain(panel)`: pick the largest allowed gain (a
  power of two in [1, 32]) whose scaled peak still fits the lane, and apply
  it through the existing `editor_panel_audio_set_gain`. Returns the gain in
  effect afterwards, so 1 for a clip already at full scale and 0 for no
  attachment.
- The peak comes from the columns the panel already holds: the largest
  absolute value across every lane of the current view. That makes the fit
  follow the view, since zooming or scrolling recomputes those columns.
- An `editor-audio-gain-fit` button ("=") on the view row, next to `v`/`^`.
- A silent view (peak 0) keeps the gain unchanged rather than jumping to
  32x, since there is nothing to fit.

## Tests

`test_editor_shell`, one case:

- No attachment: `fit_gain` returns 0 and nothing changes.
- A clip peaking at 1000 (3% of full scale) fits to 16x (16 * 1000 = 16000,
  under 32768; 32 * 1000 = 32000 would still fit, so the expectation is 32
  — the case asserts the exact value the rule gives, computed in the test
  from the peak).
- A clip already at full scale fits to 1x.
- A digitally silent clip leaves the gain where it was.
- After zooming into a quiet part of a loud clip, the fit uses that part's
  peak, not the whole clip's.
- The button runs it.

## Out of scope

Continuous (non-power-of-two) gain, a dB readout, per-lane fitting,
re-fitting automatically on every view change.

## Result

Delivered as designed. `test_editor_shell` 223/223, the case failing to link
first.

Mutations, each failing the test: the silent-view guard removed, the
`gain * peak <= 32768` term dropped from the loop condition, the peak scan
keeping the first column instead of the maximum, and the catch-up removed.
The last two survived the first version of the case and drove two additions:
a clip whose loud burst sits at the end (so the first column is not the
peak), and a fit right after an edit the page has not ticked yet (so the
catch-up is what makes it use the new clip).

The quiet-clip expectation is computed in the test from the same rule rather
than written as a literal, because the rule's answer for a 1000 peak is 32x
(32 * 1000 = 32000, still under 32768), which is easy to get wrong by hand.
