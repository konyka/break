# Plan: wheel zoom and follow-the-playhead

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-wheel-design.md`.

1. **RED (wheel)**: `editor_panel_audio_zoom_at` declared, the waveform not
   yet handling `MY_EVENT_POINTER_WHEEL`; a test dispatching real wheel
   events over the waveform.
2. **GREEN (wheel)**: the pointer-anchored zoom, with the centre-anchored
   entry point forwarding to it, and the wheel branch in the waveform's
   `on_event` (Shift scrolls).
3. **RED (follow)**: `break_editor_shell_audio_set_follow`/`_follow` as
   stubs and no checkbox; a test pumping a playing preview past the view.
4. **GREEN (follow)**: the flag, the page jump in the tick, the
   `editor-audio-follow` checkbox on the view row, i18n en + zh.
5. **Mutations** (each must fail a test): the anchor ignored (back to the
   centre), the wheel direction flipped, Shift not distinguished, the follow
   jump using a fixed step instead of the view length, the jump running with
   the flag off, and the jump running on a full view.
6. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
7. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
