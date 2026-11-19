# Plan: fade and normalize on a range, from the Audio page

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-range-effects-design.md`.

1. **Core RED/GREEN**: `break_editor_doc_audio_fade_range` / `normalize_range` stubs that ignore the range, test in `engine/tests/test_editor_audio.c`, then the range implementations.
2. **Shell RED/GREEN**: Fade/Normalize buttons and `break_editor_shell_audio_fade` / `normalize`; test in `engine/tests/test_editor_shell.c`; i18n en + zh.
3. **Mutations**: range length off by one, normalize over the whole clip, empty range accepted; shell begin ignoring the selection, fade and normalize swapped, the no-selection end wrong. Each must fail a test.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`, ASan tree, independent review, push, CI green.
