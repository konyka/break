# Plan: short-term loudness and loudness range

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-lra-design.md`.

1. **RED (core)**: both functions declared and a `test_editor_audio` case
   over a steady tone, a half-loud/half-quiet clip, a quiet tail, silence
   and the short ranges. Fails to link first.
2. **GREEN (core)**: the integrated measurement's block loop becomes
   `audio_window_loudness(doc, begin, end, window, step, …)`, shared by all
   three measurements; the short-term figure is one window ending at the
   range's end, and the LRA gates the 3 s/1 s windows and takes the
   95th minus the 10th percentile.
3. **RED/GREEN (panel)**: the two accessors and the " lra <x> LU" part of
   the levels label, added only when a figure exists.
4. **Mutations** (each must fail a test): the short-term window taken from
   the range's start instead of its end, the LRA step equal to the window
   (no overlap), the 10th percentile replaced by the minimum, and the label
   naming a range even when the measurement failed.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
