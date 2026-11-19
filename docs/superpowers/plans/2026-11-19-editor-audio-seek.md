# Plan: seek and play cursor on the editor waveform

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-seek-design.md`.

1. **RED**: declare `play_from`, `seek`, `cursor_frames` (stubs that ignore the start), the shell accessors, and tests in `test_editor_shell.c` and `test_editor_audio_sink.c`.
2. **GREEN**: start offset in the preview, cursor state, waveform pointer handler and cursor line in `editor_panel_audio.c`.
3. **Mutations**: start offset ignored in the write, position without the start, cursor not reset at the end, cursor not reset on an edit, seek while playing not reopening the sink. Each must fail a test.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`, ASan tree, independent review, push, CI green.
