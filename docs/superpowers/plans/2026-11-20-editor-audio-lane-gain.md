# Plan: per-lane amplitude zoom

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-lane-gain-design.md`.

1. **RED**: a `test_editor_shell` case over a stereo clip whose channels are
   32x apart, reading `break_editor_shell_audio_lane_gain` and friends.
   Fails to link first.
2. **GREEN**: the gain becomes an array of one factor per lane; the
   page-wide setter and fit loop over the lanes; the paint and the dB grid
   take the lane's own factor; the info suffix shows "<a>x/<b>x" when the
   lanes differ.
3. **Grid model**: it recorded lane 0 only, which left the per-lane paint
   scale unpinnable. It now records every lane with a lane index, exposed as
   `break_editor_shell_audio_grid_lane`, and the existing grid case asserts
   the lane of each entry.
4. **Mutations** (each must fail the test): the paint scale taking lane 0's
   factor for every lane, the out-of-range lane clamped to 0 instead of
   rejected, the info suffix always treating the lanes as uniform, the
   page-wide fit fitting lane 0 repeatedly, and the page-wide setter writing
   lane 0 repeatedly.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
