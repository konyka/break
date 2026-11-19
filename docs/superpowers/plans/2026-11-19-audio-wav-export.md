# Plan: PCM16 WAV export

Spec: `docs/superpowers/specs/2026-11-19-audio-wav-export-design.md`.

1. **Tests first (RED)**: encoder cases in `engine/tests/test_audio_wav.c`, editor save cases in `engine/tests/test_editor_audio.c`, against stubs that return INVALID / false.
2. **Implementation (GREEN)**: `audio_wav_encoded_size` and `audio_wav_encode_i16` in `engine/src/audio/audio_wav.{h,c}`; `break_editor_doc_audio_save_wav` in `engine/src/editor/editor_audio.{h,c}` with a temporary file and rename.
3. **Mutations**: wrong RIFF size field; capacity check skipped; rename skipped (write in place) or temporary file left behind on failure. Each must fail a test.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`, ASan tree for the audio/editor tests, independent review, push, CI green.
