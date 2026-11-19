# Plan: a dB grid on the audio waveform

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-db-grid-design.md`.

1. **RED**: a `test_editor_shell` case reading
   `break_editor_shell_audio_grid_count`/`_grid` and checking each entry
   against `10^(db/20) * half_lane_height`. Fails to link first.
2. **GREEN**: the level table, the per-lane loop drawing a mirrored pair per
   level that clears the 4 px gap and fits the lane, and the lane-0 model
   the accessors read (filled by the paint, so the const panel view writes
   it through one alias).
3. **Mutations** (each must fail the test): the dB exponent divided by 10
   instead of 20, either half of the fit condition removed, the model not
   reset at the start of a paint, and the lower half's y using the upper
   half's offset.
4. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
