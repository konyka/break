# Plan: closed-loop clock drift compensator

Spec: `docs/superpowers/specs/2026-11-19-audio-drift-compensator-design.md`.

1. **Tests first (RED)**: `engine/tests/test_audio_drift_compensator.c` with the six cases of the spec; register `test_audio_drift_compensator` next to `test_audio_drift_resampler` in `engine/CMakeLists.txt` (same sources plus the compensator, `m`, same label group). Build against a stub that returns INVALID / false.
2. **Implementation (GREEN)**: `engine/src/audio/audio_drift_compensator.h/.c`, added to the audio library source list beside the estimator and resampler.
3. **Mutations**: ratio update with the wrong sign; no clamp; estimator window not cleared after a correction. Each must fail a test; restore sources.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`; ASan+UBSan and TSan trees with the new test in the regex; independent review; push; CI green.
