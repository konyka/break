# Plan: a dB readout for the visible audio

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-db-design.md`.

1. **RED (core)**: `break_editor_doc_audio_peak_range` declared and a
   `test_editor_audio` case over square waves, a mixed clip, silence and the
   invalid ranges. Fails to link first.
2. **GREEN (core)**: one pass over the range in double, tracking the largest
   magnitude and the sum of squares.
3. **RED (panel)**: a `test_editor_shell` case reading
   `break_editor_shell_audio_peak_db`/`_rms_db` and the readout label.
4. **GREEN (panel)**: `audio_db_of` with the -120 floor, `audio_panel_levels`
   over the current view, the two accessors, and an
   `editor-audio-levels` label on the view row refreshed with the info line.
5. **Mutations** (each must fail a test): RMS replaced by the peak, the peak
   scan keeping the first sample, the dB factor 10 instead of 20, the levels
   read over the whole clip instead of the view, and the label's two numbers
   swapped.
6. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
7. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
