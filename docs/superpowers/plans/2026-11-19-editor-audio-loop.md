# Plan: loop the played audio range

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-loop-design.md`.

1. **RED**: preview `set_loop`/`loop` and the shell accessors as stubs, the Loop checkbox missing; test in `engine/tests/test_editor_shell.c`.
2. **GREEN**: the loop flag, the re-arm in `pump` (write half factored out), the checkbox and its handler, i18n en + zh.
3. **Mutations**: the re-arm skipped, rewinding to frame 0 instead of the range start, no write after the rewind, the panel not forwarding the flag, the checkbox handler not connected. Each must fail the test.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`, ASan tree, independent review, push, CI green.
