# Plan: a look-ahead dynamic limiter

Spec: `docs/superpowers/specs/2026-11-20-editor-audio-lookahead-limiter-design.md`.

1. **RED (core)**: `break_editor_doc_audio_limit_dynamic` declared and a
   `test_editor_audio` case over a quiet clip with one loud burst, checking
   the burst is bounded, the gain is already down before it, the release is
   gradual, and the quiet part keeps more level than a static scale leaves
   it. Fails to link first.
2. **GREEN (core)**: the per-frame gain from the look-ahead window's
   requirement, an immediate attack, a one-pole release, and the early
   return for a clip already under the ceiling.
3. **RED/GREEN (panel)**: `break_editor_shell_audio_limit_dynamic`, the
   `editor-audio-dyn-limit` button at -1 dBFS / 5 ms / 50 ms, the i18n
   entries, and the edit-failed log.
4. **Mutations** (each must fail a test): the look-ahead window shrunk to
   one frame, the release replaced by an instant snap, the
   already-under-ceiling early return removed, the button's ceiling changed,
   and the failure path not logging.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`,
   `docs/design/audio_extended.md`,
   `docs/design/editor_panels_phase3.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
