# Plan: mute one channel in the audio preview

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-mute-design.md`.

1. **RED**: a `test_editor_shell` case playing a stereo clip through the
   fake sink with each mute state and clicking `editor-audio-mute`. Fails to
   link while the accessors are missing.
2. **GREEN**: the preview's `mute` field and accessors, the copy at Play
   zeroing that channel in the non-solo branch, the panel's accessors, the
   button, the i18n entries (en + zh) and the reset on an attachment change.
   The label and cycle helpers are shared with Solo rather than duplicated.
3. **Mutations** (each must fail the test): the mute branch never taken, the
   channel offset dropped from the write, the range check replaced by "any
   mute set", the reset on an attachment change removed, the solo branch
   made conditional on no mute (so the mute would win), and the cycle
   jumping straight to none.
4. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
