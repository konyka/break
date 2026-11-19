# Plan: labels on the dB grid lines

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-grid-labels-design.md`.

1. **RED**: extend the grid case in `test_editor_shell` to read
   `break_editor_shell_audio_grid_label`. Fails to link first.
2. **GREEN**: the per-entry label text in the panel, drawn above each upper
   line when the lane leaves room for it, with the mirrored lower entry
   deliberately unlabelled; the accessor chain down to the shell.
3. **Mutations** (each must fail the test): the room-for-text condition
   always true, and the mirrored entry carrying the same label.
4. **Docs**: `docs/Implementation_Status.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
   `missing_capabilities.md` already lists the grid; this slice closes its
   "线上标注" remainder.
5. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
