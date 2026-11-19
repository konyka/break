# Plan: keyboard zoom and scroll for the audio waveform

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-keys-design.md`.

1. **RED**: a `test_editor_shell` case that focuses the waveform with a
   press and expects `+`/`-`/arrows/`Home` to move the view, to be consumed,
   and unknown keys to bubble. Fails while the widget is not focusable and
   handles no keys.
2. **GREEN**: mark the waveform focusable at build, and handle
   `MY_EVENT_KEY_DOWN` in its `on_event` through the existing
   `editor_panel_audio_zoom`/`_scroll` plus a view reset for `Home`.
3. **Mutations** (each must fail the test): the key branch returning
   `MY_RET_NOT_SUPPORTED` instead of consuming, `+` and `-` swapped,
   `Left`/`Right` swapped, `Home` zooming instead of resetting, and the
   widget left non-focusable.
4. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
