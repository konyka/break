# Plan: solo one channel in the audio preview

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-solo-design.md`.

1. **RED**: a `test_editor_shell` case playing a stereo clip through the
   fake sink with each solo state and clicking `editor-audio-solo`. Fails to
   link while the accessors are missing.
2. **GREEN**: the preview's `solo` field and accessors, the copy at Play
   writing the soloed channel into every output channel, the panel's
   accessors, the cycling button with its label rule, the i18n entries
   (en + zh) and the reset on an attachment change.
3. **Mutations** (each must fail the test): the solo branch never taken, the
   channel offset dropped from the read, the range check replaced by "any
   solo set" (so an out-of-range index would mis-play), the cycle jumping
   straight to none, the reset on an attachment change removed, and the
   L/R label rule bypassed.
4. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
