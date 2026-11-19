# Plan: fit the amplitude zoom to the visible peak

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-autogain-design.md`.

1. **RED**: a `test_editor_shell` case calling
   `break_editor_shell_audio_fit_gain` and clicking
   `editor-audio-gain-fit`. Fails to link while the function is missing.
2. **GREEN**: `editor_panel_audio_fit_gain` scanning the panel's columns for
   the loudest sample across lanes, picking the largest allowed power of two
   that keeps `gain * peak <= 32768`, and applying it through the existing
   setter; plus the "=" button on the view row.
3. **Mutations** (each must fail the test): the silent-view guard removed,
   the peak check dropped from the loop condition, the peak scan keeping the
   first column instead of the maximum, and the catch-up removed.
4. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
