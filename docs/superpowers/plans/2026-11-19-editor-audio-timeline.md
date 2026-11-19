# Plan: timeline ruler on the Audio page

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-timeline-design.md`.

1. **RED**: `EditorAudioTicks` + `editor_panel_audio_ticks` declared with a stub returning 0 ticks, shell accessor, test in `engine/tests/test_editor_shell.c`.
2. **GREEN**: the step ladder, labels, tick positions; the ruler widget and its paint.
3. **Mutations**: step ladder skipped (fixed step), the 60 px spacing rule dropped, the last tick outside the clip, the minutes/seconds threshold wrong. Each must fail the test.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`, ASan tree, independent review, push, CI green.
