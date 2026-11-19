# Plan: switch the voice capture device at runtime

Spec: `docs/superpowers/specs/2026-11-19-core-app-runtime-capture-switch-design.md`.

1. **Scenario (RED → GREEN)**: tests in `test_core_app_runtime.c` for `voice-capture-device`; add `CORE_APP_SCENARIO_VOICE_CAPTURE_DEVICE` to `scenario.h`, parse it in `scenario.c` with `device_name()`, accept it in `app_scenario_supported`. Add fuzz substitutions.
2. **Voice mailbox (RED → GREEN)**: tests in `test_core_app_voice.c` (switch by name, unknown name, back to default, OVERLOAD, REJECTED before start and for 128 bytes, loss after switch). Implement `core_app_voice_request_capture_device`, the pending handling in `core_app_voice_pump`, and the three stats.
3. **core_app wiring (RED → GREEN)**: extend `test_core_app_voice_lane.cmake` and the stopped-line regex in `test_core_app_voice_device.cmake`; add the scenario event handling, the result polling in `app_voice_tick`, and the stopped-line fields.
4. **Real device**: add the unknown-name + default scenario to `test_core_app_voice_device.cmake`; run it on this host.
5. **Mutations**: the three in the spec, each must fail a test; restore sources.
6. **Docs**: `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, `docs/design/audio_extended.md`, `docs/design/core_app_integration.md`, spec Result.
7. **Verification**: full suite in `build-core-app-net`; ASan+UBSan and TSan voice-recovery trees with the audio regex; independent review; push; CI green.
