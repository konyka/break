# Plan: per-channel waveform display

Spec: `docs/superpowers/specs/2026-11-19-editor-audio-channels-design.md`.

1. **RED (core)**: `break_editor_doc_audio_waveform_channel` declared and a
   `test_editor_audio` case over a stereo clip with a silent left channel.
   Fails to link while the function does not exist.
2. **GREEN (core)**: one `audio_waveform_impl` taking a channel, with
   `UINT32_MAX` meaning "merge every channel"; the existing range function
   forwards with that sentinel, so its behaviour is unchanged.
3. **RED (panel)**: a `test_editor_shell` case reading
   `break_editor_shell_audio_lane_count`/`_lane_column`.
4. **GREEN (panel)**: per-lane column storage (2 max, as the document only
   accepts mono and stereo), the refresh filling each lane from its channel,
   and the paint stacking the lanes with one centre line each.
5. **Mutations** (each must fail a test): the channel stride dropped, the
   channel offset dropped, the channel-range guard removed, the lane height
   not divided, every lane drawn at the same centre, and the lane count
   pinned to 1.
6. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
7. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
