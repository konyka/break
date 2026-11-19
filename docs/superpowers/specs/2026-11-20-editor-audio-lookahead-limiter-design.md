# Design: a look-ahead dynamic limiter

The true-peak ceiling edit
(`2026-11-20-editor-audio-tp-limit-design.md`) scales the whole clip, so one
loud transient costs the entire recording its level: a clip with a single
door slam loses 10 dB everywhere. A dynamic limiter only pulls the level down
where it is needed, and the look-ahead is what lets it do so without the
distortion a zero-delay limiter produces at the attack.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_limit_dynamic(doc, ceiling_dbfs, lookahead_ms,
  release_ms)`: applies a per-sample gain that keeps the sample peak at or
  below the ceiling, as one undoable snapshot.
- The gain envelope: for each frame, the required gain is
  `ceiling / max|sample|` over the look-ahead window starting there (1.0
  when the window is already under the ceiling). The applied gain is the
  minimum of the required gain over that window, so it is already down by
  the time the transient arrives; it then recovers towards 1.0 with a
  one-pole release of the given time constant.
- The ceiling is a dBFS sample ceiling, not dBTP: it is the per-sample
  bound the gain actually enforces, and claiming dBTP would need the limiter
  to work on the oversampled signal.
- False, changing nothing, for no attachment, a ceiling outside [-20, 0]
  dBFS, a look-ahead outside (0, 50] ms, a release outside (0, 1000] ms, and
  a silent clip.
- A clip already under the ceiling is left byte-identical and adds no history
  entry, like the static version.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_limit_dynamic(shell, ceiling, lookahead_ms,
  release_ms)`, refreshing the page and logging the edit-failed line on
  refusal.
- An `editor-audio-dyn-limit` button at -1 dBFS with 5 ms look-ahead and
  50 ms release, labelled "Limit" (en) / "动态限峰" (zh).

## Tests

- `test_editor_audio`: a clip that is quiet except for one loud burst keeps
  its quiet part's level (within a dB) while the burst is brought under the
  ceiling — which the static scale cannot do, and the test asserts the
  contrast by running both on copies of the same clip; the gain is already
  down at the sample before the burst (the look-ahead); the release brings it
  back up after; a clip already under the ceiling is untouched; the undo
  restores the samples; the rejected arguments change nothing.
- `test_editor_shell`: the button brings a hot clip under the ceiling and
  leaves its quiet part louder than the static edit would; a silent clip
  logs the edit-failed line.

## Out of scope

True-peak (oversampled) limiting, a separate attack time, per-channel gains
(the envelope is shared so the stereo image does not shift), soft-knee
compression below the ceiling.

## Result

Delivered as designed. `test_editor_audio` 22/22 and `test_editor_shell`
232/232, both after a failing run.

Mutations, each failing a test: the look-ahead window shrunk to a single
frame, the release replaced by an instant snap to the needed gain, the
already-under-ceiling early return removed, the button's ceiling changed from
-1 to -12 dBFS, and the failure path not logging.

Two assertions had to be written against the real numbers rather than the
intuition:

- The release case first asserted the gain was still "well down" (under
  1500) a few frames after the burst. It is not: the burst is 32000 against
  a 29204 ceiling, so the gain only falls to 0.91 and the quiet part under it
  reads about 2740, not a few hundred. The case now bounds it at 2800 and
  checks the recovery is at least 150 units of rise, which is what separates
  a one-pole release from a snap.
- The shell case first asserted only that the burst was *under* the ceiling,
  which a -12 dBFS ceiling also satisfies, so the button's constant was
  unpinned. It now asserts the burst lands *at* the ceiling (29000..29300).
