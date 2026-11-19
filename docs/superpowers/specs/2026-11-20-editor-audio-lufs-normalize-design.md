# Design: normalize to a loudness target

The page can now measure loudness, but the only normalize it offers works on
peak (`break_editor_doc_audio_normalize_range`, a dBFS target). Delivery
targets are stated in LUFS, and peak-normalizing to -1 dBFS leaves a quiet
recording quiet. Turning the measurement into an edit is the step that makes
it useful.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_normalize_loudness(doc, target_lufs)`: measures
  the whole clip's integrated loudness, then applies the constant gain that
  moves it to `target_lufs`, as one undoable snapshot command like the other
  edits.
- The gain is capped so the result cannot clip: if reaching the target would
  push the sample peak past full scale, the gain is reduced to land the peak
  at full scale instead, and the function still succeeds. The achieved
  loudness is then above or below the target, which the caller can re-measure.
- False, changing nothing, for no attachment, a target outside
  [-70, 0] LUFS, a clip too short to measure (under one 400 ms block), and a
  digitally silent clip (no gain can give silence a loudness).
- Rounding is the same as the peak normalize: per sample, with saturation.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_normalize_lufs(shell, target)` runs it on the
  document and refreshes the page; a failure logs the existing edit-failed
  line.
- An `editor-audio-lufs-norm` button on the view row normalizes to -23 LUFS
  (the EBU R128 target), labelled "-23 LUFS" through the i18n table.

## Tests

- `test_editor_audio`: a -40 LUFS clip normalized to -23 measures about -23
  afterwards; normalizing a clip that is already at the target changes it by
  at most a rounding step; a target that would clip lands the peak at full
  scale and reports success with a loudness below the target; the undo
  restores the original samples byte for byte; the rejected cases change
  nothing and add no history entry.
- `test_editor_shell`: the button moves the view's loudness towards -23; a
  silent clip logs the edit-failed line and leaves the clip alone.

## Out of scope

A loudness target in the settings, true-peak limiting rather than gain
reduction (so a clip can still exceed -1 dBTP), per-channel gains, a
dialogue-gated target.

## Result

Delivered as designed. `test_editor_audio` 19/19 and `test_editor_shell`
229/229, both after a failing run.

Mutations, each failing a test: the gain exponent divided by 10 instead of
20, the headroom cap removed, both silence guards removed at once, the
button's target changed from -23 to -14, and the failure path not logging.

Two notes on what the tests can and cannot pin:

- **Counting saturated samples does not detect clipping here.** A sine scaled
  to full scale legitimately has one sample per cycle at 32767, so the first
  version of the headroom assertion (fewer than 40 samples at full scale)
  failed on correct output with 5000. The peak-to-RMS ratio is the real
  discriminator: it stays at a sine's √2 when the gain was reduced and
  collapses towards 1 when saturation flattens the waveform. The case asserts
  that ratio.
- **The two silence guards are redundant with each other.** The loudness
  floor check and the `peak <= 0` check both reject a digitally silent clip,
  so removing either one alone leaves the suite green; removing both is red.
  The case pins that silence is refused, not which guard does it, and the
  code keeps both because each is the natural precondition of the value it
  guards.

One thing the suite caught that this slice got wrong: the button's label was
"-23 LUFS" in both language tables, and `test_editor_i18n`'s
`chinese_table_is_actually_translated` rejects a zh-CN entry identical to its
en-US one. The Chinese label is now "归一 -23" ("normalize -23"). The check is
right to insist: a number-only label still needs the verb in the reader's
language.
