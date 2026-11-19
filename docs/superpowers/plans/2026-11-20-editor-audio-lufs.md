# Plan: integrated loudness in LUFS

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-lufs-design.md`.

1. **RED (core)**: `break_editor_doc_audio_loudness_range` declared and a
   `test_editor_audio` case over 1 kHz and 30 Hz tones, an amplitude
   doubling, stereo, silence, a too-short range and the invalid ranges.
   Fails to link first.
2. **GREEN (core)**: the two K-weighting biquads derived for the clip's own
   rate, one filtered pass per channel accumulated into 400 ms blocks with
   75% overlap, then the -70 LUFS absolute gate and the -10 LU relative
   gate.
3. **RED/GREEN (panel)**: `break_editor_shell_audio_lufs` and the
   "lufs <x>" part of the levels label, added only when a figure exists.
4. **Mutations** (each must fail a test): the high-pass stage skipped, the
   block loudness using 20*log10 instead of 10*log10, the relative gate
   replaced by the floor, the too-short guard removed, the channel loop
   stopping after channel 0, and the label naming a figure even when the
   measurement failed.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
