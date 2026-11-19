# Plan: drag to select on the editor waveform

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-drag-design.md`.

1. **RED**: `audio_page_selects_by_dragging_the_waveform` in `engine/tests/test_editor_shell.c` (press, two moves, release through the real dispatcher).
2. **GREEN**: drag state in the panel, move/release handling in the waveform's `on_event`.
3. **Mutations**: end not inclusive, moves ignored, a move outside a drag consumed, a still move selecting, the drag not started. Each must fail the test.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`, ASan tree, independent review, push, CI green.
