# Plan: drift compensation in the core_app voice pump

Spec: `docs/superpowers/specs/2026-11-19-core-app-voice-drift-design.md`.

1. **Aligner accessor (RED/GREEN)**: `audio_voice_aligner_correlation` with a test in `test_audio_voice_aligner`.
2. **Voice tests first (RED)**: drift convergence, disabled baseline and reset on recovery in `engine/tests/test_core_app_voice.c`; config/stats fields added so they compile.
3. **Pump wiring (GREEN)**: compensator, resampled-reference FIFO, observe/update schedule, resets on recovery/switch/playback reopen, stats; link the compensator into `core_app_voice` users in `engine/CMakeLists.txt`.
4. **core_app**: enable in `app_voice_config`, trace fields, update `test_core_app_voice_lane.cmake` expectations if they match the stopped line.
5. **Mutations**: FIFO bypassed (raw reference to the aligner), no reset on recovery, update never called. Each must fail a test.
6. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/core_app_integration.md`, spec Result.
7. **Verification**: full suite in `build-core-app-net`, ASan+UBSan and TSan voice trees, independent review, push, CI green.
