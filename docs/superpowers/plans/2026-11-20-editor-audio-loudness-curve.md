# Plan: a loudness curve over the waveform

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-loudness-curve-design.md`.

1. **RED (core)**: `break_editor_doc_audio_loudness_curve` declared and a
   `test_editor_audio` case over a loud-then-quiet clip, a steady one, a
   single point and the rejected arguments. Fails to link first.
2. **GREEN (core)**: one short-term measurement per point, each over the
   window ending at that point and clamped to the range's start, reusing
   `audio_window_loudness`.
3. **RED/GREEN (panel)**: the curve drawn over lane 0 from the view's own
   figures, floor values skipped, and the accessors reporting what the paint
   used.
4. **Mutations** (each must fail a test): the point position fixed at the
   range's end, the window not clamped to the range's start, the y mapping
   inverted, and the floor values drawn instead of skipped.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
