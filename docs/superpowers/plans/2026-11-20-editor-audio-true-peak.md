# Plan: true-peak measurement

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-true-peak-design.md`.

1. **RED (core)**: `break_editor_doc_audio_true_peak_range` declared and a
   `test_editor_audio` case over an intersample sine, a square wave,
   silence, sub-ranges, the clip's edges and stereo. Fails to link first.
2. **GREEN (core)**: the polyphase windowed-sinc kernel built once, and the
   4-phase pass over the range with out-of-clip taps read as zero.
3. **RED/GREEN (panel)**: `break_editor_shell_audio_true_peak_db` and the
   "tp <x> dB" part of the levels label, with `audio_panel_levels_ex`
   carrying the extra figure so the cheap callers keep their two.
4. **Mutations** (each must fail a test): only phase 0 evaluated, the upper
   bounds check dropped, the DC normalization removed, the peak scan keeping
   the first value, the channel loop stopping after channel 0, and the
   absolute value dropped.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
