# Plan: waveform selection with Trim and Cut

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-selection-design.md`.

1. **RED**: shell accessors and the Trim/Cut buttons as stubs (no selection, no edit); i18n keys; test `audio_page_selects_and_trims_or_cuts` in `engine/tests/test_editor_shell.c`.
2. **GREEN**: selection state, Shift press handling, buttons, revision clearing, selection band, info suffix.
3. **Mutations**: end not inclusive of the pressed frame, Shift ignored, selection not cleared on an edit, Cut calling trim, clear-on-plain-click missing. Each must fail a test.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`, ASan tree, independent review, push, CI green.
