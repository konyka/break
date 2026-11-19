# Plan: mix the voice of several peers

Spec: `docs/superpowers/specs/2026-11-19-break-voice-mixer-design.md`.

1. **Tests first (RED)**: `engine/tests/test_break_voice_mixer.c` with the five cases of the spec; register `test_break_voice_mixer` in `engine/CMakeLists.txt` next to `test_break_online_voice` (same link line, labels).
2. **Implementation (GREEN)**: `engine/src/network/break_voice_mixer.h/.c`, added to the `break_online` source list. Source table allocated at create; a receiver per source created on its first frame; insertion-order sum with i32 accumulation and i16 saturation.
3. **Mutations**: no saturation; eviction ignoring the idle timeout; `concealed` set when any input was concealed. Each must fail a test; restore sources.
4. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/core_app_integration.md`, spec Result.
5. **Verification**: full suite in `build-core-app-net`; the ASan+UBSan and TSan voice trees with `test_break_voice_mixer` added to the regex; independent review; push; CI green.
