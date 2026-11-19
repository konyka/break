# Plan: editor audio preview playback

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-preview-design.md`.

1. **Preview RED**: `editor_audio_preview.h` + stub `.c`; shell cases with a fake sink in `engine/tests/test_editor_shell.c`; Play/Stop button and shell accessors stubbed.
2. **Preview GREEN**: snapshot copy, pump, self-stop, position; panel button, tick pump, revision stop, info suffix; i18n (en + zh).
3. **Sink RED/GREEN**: `editor_audio_sink.{h,c}` and `engine/tests/test_editor_audio_sink.c` on the FAKE backend; CMake target and test.
4. **App wiring**: `editor_main.c` creates the audio system and sets the sink; destroyed after the shell.
5. **Mutations**: pump ignores the sink's `written` count; no self-stop; position ignores the queue; no stop on a revision change; sink close not called. Each must fail a test.
6. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/editor_panels_phase3.md`, spec Result.
7. **Verification**: full suite in `build-core-app-net`, ASan tree, independent review, push, CI green.
