# Named Audio Devices Plan

Design: `docs/superpowers/specs/2026-11-18-named-audio-devices-design.md`.

## Tasks

1. RED `test_audio`: `playback_devices_are_listed_by_backend`, `a_named_playback_device_opens_and_an_unknown_name_is_rejected`, `switching_playback_device_keeps_sources_and_the_reference_tap`, `an_unknown_switch_target_changes_nothing`, `reopen_keeps_the_selected_device`. They fail to compile (no `audio_system_list_devices`, `audio_system_create_named`, `audio_system_switch_device`, `audio_system_selected_device`).
2. GREEN `audio.h` / `audio.c`: a `selected_device[128]` in `AudioImpl`; a helper that resolves a name to an `ma_device_id` through the owned context; `audio_engine_init_with_context` takes the optional id (`engine_config.pPlaybackDeviceID`); `audio_reopen_device` uses the selected id and falls back to the default when the name is gone; `audio_system_switch_device` opens the new device stopped with the engine's allocation callbacks, then uninitialises and frees the old one, swaps `engine.pDevice`, starts the new one and counts a recovery.
3. RED `test_core_app_voice`: named NULL capture creates; an unknown name is REJECTED. GREEN `CoreAppVoiceConfig.capture_device_name`, used by create (`audio_capture_create_named`) and by recovery (`audio_capture_reopen`).
4. RED `test_core_app_runtime`: `core_app_audio_start_device_named` on NULL with an unknown name is REJECTED with the rejected trace line; with the null device's name it reports unavailable as today (Null is not a device). GREEN core_app_audio.
5. core_app: `CoreAppConfig.audio_device_name` / `voice_capture_device_name`, the CLI options and their dependency errors, the voice rejected line, REJECTED mapped to exit 2.
6. cmake contract `test_core_app_named_device.cmake`: unknown output name exits 2 with the rejected line; CLI dependency errors; on a real device, the default device's listed name reaches `result=ready device=<name>` (skip 77 without one).
7. Mutations from the design, docs (`audio_extended.md`, `core_app_integration.md`, `Implementation_Status.md`, `missing_capabilities.md`), the three build trees, independent review, commit, push, CI.
