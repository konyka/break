# Plan: editor audio waveform view

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-waveform-design.md`.

1. **Core RED**: waveform and revision cases in `engine/tests/test_editor_audio.c` against stubs (`waveform` returns false, `revision` returns 0).
2. **Core GREEN**: `audio_revision` field in `BreakEditorDoc`, bumped in attach, snapshot apply/revert/commit and detach; `break_editor_doc_audio_waveform`.
3. **Shell RED**: Audio tab, WAV click, edit refresh, refusal, corrupt file and retranslate cases in `engine/tests/test_editor_shell.c` against a panel that builds an empty page.
4. **Shell GREEN**: `apps/editor/editor_panel_audio.c`, fifth bottom tab, asset browser `.wav` branch, i18n strings (en + zh), shell accessors, CMake (editor app + `test_editor_shell`).
5. **Mutations**: column range off by one, channel ignored in min/max, revision not bumped on undo, revision not bumped on detach, tick ignoring the revision. Each must fail a test.
6. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, the editor design doc that lists the tool window tabs, spec Result.
7. **Verification**: full suite in `build-core-app-net`, ASan tree for the editor tests, independent review, push, CI green.
