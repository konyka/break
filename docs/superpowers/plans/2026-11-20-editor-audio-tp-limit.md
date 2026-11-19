# Plan: a true-peak limiter

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-tp-limit-design.md`.

1. **RED (core)**: `break_editor_doc_audio_limit_true_peak` declared and a
   `test_editor_audio` case over a hot intersample sine, an already-quiet
   clip, the undo, the rejected cases, and the constant-gain property.
   Fails to link first.
2. **GREEN (core)**: measure the true peak, return early when it is already
   under the ceiling, otherwise scale the clip by `ceiling / peak` as one
   snapshot.
3. **RED/GREEN (panel)**: `break_editor_shell_audio_limit_true_peak`, the
   `editor-audio-tp-limit` button at -1 dBTP, the i18n entries (en "-1 dBTP",
   zh "限峰 -1"), and the edit-failed log on refusal.
4. **Mutations** (each must fail a test): the already-under-ceiling early
   return removed, the ceiling exponent divided by 10 instead of 20, the
   sample peak used instead of the true peak, the button's ceiling changed,
   and the failure path not logging.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
