# Plan: dynamic limiting in the oversampled domain

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-tp-dynamic-design.md`.

1. **RED (core)**: `break_editor_doc_audio_limit_dynamic_true_peak` declared
   and a `test_editor_audio` case over a clip whose samples are under a
   -1 dBFS ceiling while its reconstruction is not. Fails to link first.
2. **GREEN (core)**: `audio_tp_per_frame` reconstructing each frame's worst
   phase with the measurement's own kernel, then the same look-ahead
   envelope driven by those values instead of the stored samples.
3. **RED/GREEN (panel)**: the shell call, the `editor-audio-dyn-tp-limit`
   button, the i18n entries, and the edit-failed log.
4. **Mutations** (each must fail a test): the per-frame reconstruction
   replaced by the sample magnitude, the already-under-ceiling early return
   removed, and the button calling the sample-domain limiter instead.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
