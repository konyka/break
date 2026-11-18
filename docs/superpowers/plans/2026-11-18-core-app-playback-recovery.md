# Core App Playback Device Recovery Plan

Design: `docs/superpowers/specs/2026-11-18-core-app-playback-recovery-design.md`.

## Tasks

1. RED `test_audio`: add `playback_loss_is_reported_and_reopen_recovers`, `refused_playback_reopen_keeps_the_system_lost_once_per_event` and `playback_recovery_calls_validate_their_arguments`. They fail to compile (no `audio_system_lost`, `audio_system_reopen`, `AudioSystemEvent`).
2. GREEN `audio.h` / `audio.c`: `AudioSystemEvent`, the three functions, the custom data and notification callbacks passed to `ma_engine_init`, and the `lost`, `reopening` and `refused_reopens` atomics in `AudioImpl`. `audio_system_destroy` sets `reopening` before uninitializing the engine. (Superseded during review: no notification callback; loss is the simulated flag or the device out of the started state for 250 ms on miniaudio's monotonic timer, tracked by `simulated_lost`, `stopped_since_us`, `refused_reopens` and `device_recoveries`; see the spec's Revisions.)
3. RED `test_core_app_runtime`: add the four recovery tests and append `device_recoveries=0 device_reopen_failures=0` to the existing stopped-line expectations. They fail to compile (no fields).
4. GREEN `core_app_audio.h` / `.c`: `reopen_interval_ms`, `max_reopen_failures`, `device_recoveries`, `device_reopen_failures` and the private attempt state; `sound_recover_device` called from the synchronous drain and from the owner loop before each command it applies; the trace fields.
5. `test_core_app_audio_device.cmake`: require the two fields on the stopped line.
6. Mutations from the design, then docs: `docs/design/audio_extended.md`, `docs/design/core_app_integration.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`.
7. Build and run the full suite in `build-core-app-net`, the voice and audio tests in the ASan/UBSan and TSan trees, independent review, commit, push, CI.
8. Review fixes (see spec Revisions): backend fallback loop, iOS session category, state-based loss with a grace period, reopen skips a started device, `audio_system_recoveries` and `voice_follow_playback_reopen`, the voice `playback_recoveries` trace field, three failure-path tests, the owner-blocking note in `core_app_audio.h`.
