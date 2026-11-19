# Plan: zoom and scroll the audio waveform

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-zoom-design.md`.

1. **RED (core)**: `break_editor_doc_audio_waveform_range` declared and the
   whole-clip function forwarding to it; a test in
   `engine/tests/test_editor_audio.c` comparing a sub-range against a manual
   min/max, plus the invalid ranges.
2. **GREEN (core)**: the per-column loop over `[begin, end)`, with the
   whole-clip entry point as `..._range(doc, 0, frames, …)`.
3. **RED (panel)**: `editor_panel_audio_zoom/scroll/view` and the four shell
   accessors as stubs; a test in `engine/tests/test_editor_shell.c` driving
   the buttons and reading the view, the columns, the cursor and the ruler.
4. **GREEN (panel)**: the view state, its reset on an attachment change, the
   range waveform call, the view-relative selection band, cursor line,
   pointer mapping and ruler ticks, and a second toolbar row carrying the
   four symbol buttons (the first row has no space left for them).
5. **Mutations** (each must fail a test): the range waveform dropping the
   `begin` offset; a narrow column covering no frame; zoom in anchored at
   the view start instead of its centre; the 16-frame floor removed; the
   scroll step halved; the pointer mapping dropping `view_begin`; the ruler
   x dropping `view_begin`; an attachment change not resetting the view.
6. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
7. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree for
   `test_editor_shell` and `test_editor_audio`, push, CI.
