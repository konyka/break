# Plan: a scroll bar for the audio waveform view

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-scrollbar-design.md`.

1. **RED**: a `test_editor_shell` case reading and driving
   `editor-audio-scrollbar`. Fails while the widget does not exist.
2. **GREEN**: the horizontal bar below the waveform, an
   `audio_panel_sync_scrollbar` call in the panel's refresh (which every
   view change already goes through), and a "changed" handler mapping the
   value back to a view start.
3. **Mutations** (each must fail the test): `page_size` pinned to 1, the
   value divided by the clip length instead of the scrollable range, the
   handler using the clip length, and the sync call removed.
4. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
