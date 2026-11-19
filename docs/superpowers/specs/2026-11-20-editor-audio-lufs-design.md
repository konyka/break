# Design: integrated loudness in LUFS

The page reports sample peak, RMS and true peak. None of them answers "how
loud does this sound": RMS weights every frequency equally, while hearing is
far less sensitive below 100 Hz and slightly more sensitive around 2 kHz. A
delivery target is stated in LUFS (-14 for most streaming, -23 for EBU
broadcast), so a loudness figure is what tells you whether a clip is ready.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_loudness_range(doc, begin, end, out_lufs)`: the
  gated integrated loudness of `[begin, end)` in LUFS, following ITU-R
  BS.1770-4's structure: K-weighting, mean square over 400 ms blocks with
  75% overlap, a -70 LUFS absolute gate, then a relative gate 10 LU below
  the mean of the surviving blocks.
- The K-weighting is the standard's two stages (a high-shelf and a
  high-pass) with coefficients computed for the clip's own sample rate from
  the analogue prototypes, so an 8 kHz test clip and a 48 kHz recording are
  both filtered correctly rather than only the 48 kHz case being right.
- Channel weights are 1.0 for mono and both stereo channels (the standard's
  surround weights do not apply to 1 or 2 channels).
- False, writing nothing, for the same invalid ranges as the other
  measurements, and for a range shorter than one 400 ms block: an
  integrated figure over less than a block is not defined.
- A digitally silent range reports the floor, -70 LUFS, rather than -inf.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_lufs(shell)`: the view's loudness, or the -70
  floor when the view is too short or silent.
- The levels label gains " lufs <x>" when a figure is available.

## Tests

- `test_editor_audio`: a 1 kHz sine at -20 dBFS over 2 s reads about -23
  LUFS (the K-weighting's gain at 1 kHz is near 0 dB, so a -20 dBFS sine's
  loudness is its RMS, -23 dBFS, within a tolerance); doubling the amplitude
  raises it by about 6 LU; a 30 Hz tone of the same amplitude reads far
  lower than the 1 kHz one (the weighting's whole point); silence reports
  -70; a range shorter than 400 ms is rejected; the invalid ranges write
  nothing; stereo reads about 3 LU above the same signal in mono.
- `test_editor_shell`: a clip long enough to measure reports a figure in the
  label; a 100 ms clip reports the floor and the label omits it.

## Out of scope

Short-term and momentary loudness windows, loudness range (LRA), a
normalize-to-LUFS edit, the surround channel weights.

## Result

Delivered as designed. `test_editor_audio` 17/17 and `test_editor_shell`
228/228, both after a failing run.

Mutations, each failing a test: the high-pass stage skipped (leaving only the
shelf, so the 30 Hz tone no longer reads far below the 1 kHz one), the block
loudness computed with `20*log10` instead of `10*log10` of the mean square,
the relative gate replaced by the absolute floor, the too-short-range guard
removed, the channel loop stopping after channel 0, and the label naming a
loudness figure even when the measurement failed.

The 1 kHz test reads between -25 and -21 LUFS for a -20 dBFS sine, which
brackets the -23 the arithmetic predicts (a sine's RMS is 3 dB below its
peak, and the K-weighting is near unity at 1 kHz). The test asserts the band
rather than a point, because the shelf's gain at 1 kHz is not exactly 0 dB
and the gating drops no blocks for a steady tone.

The coefficients are derived from the standard's analogue prototypes at the
clip's own rate, not the tabulated 48 kHz set, so the 24 kHz test material
is filtered correctly. That is a deliberate difference from a literal
BS.1770 implementation, which only tabulates 48 kHz.
