# Plan: amplitude zoom for the audio waveform

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-gain-design.md`.

1. **RED**: a `test_editor_shell` case reading the gain, clicking the two
   buttons and measuring the painted rows through the LCD buffer. Fails
   while the accessors and the buttons do not exist.
2. **GREEN**: the `gain` field (1 at create, reset on an attachment
   change), `editor_panel_audio_set_gain`/`_gain` with the snap and clamp,
   the paint scale multiplied by the gain, the " | <n>x" info suffix, and
   the two buttons on the view row.
3. **Mutations** (each must fail the test): the paint scale ignoring the
   gain, the 32x clamp removed, the reset on an attachment change removed,
   the info suffix suppressed, and the down button stepping up.
4. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
