# Plan: normalize to a loudness target

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-lufs-normalize-design.md`.

1. **RED (core)**: `break_editor_doc_audio_normalize_loudness` declared and a
   `test_editor_audio` case over a quiet clip, an already-on-target clip, a
   target that would clip, the undo, and the rejected cases. Fails to link
   first.
2. **GREEN (core)**: measure the clip's integrated loudness and peak, derive
   the gain, cap it at the peak's headroom, and apply it as one snapshot.
3. **RED/GREEN (panel)**: `break_editor_shell_audio_normalize_lufs`, the
   `editor-audio-lufs-norm` button at -23 LUFS, the i18n entry, and the
   edit-failed log on refusal.
4. **Mutations** (each must fail a test): the gain exponent divided by 10
   instead of 20, the headroom cap removed, both silence guards removed, the
   button's target changed, and the failure path not logging.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
