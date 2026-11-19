# Core App Runtime Playback Device Switch Plan

Spec: `docs/superpowers/specs/2026-11-19-core-app-runtime-device-switch-design.md`.

Trees: `build-core-app-net` (full ctest), `build-voice-recovery-asan` and `build-voice-recovery-tsan` (audio regex: `test_audio`, `test_core_app_runtime`, `test_core_app_voice.*`, `test_core_app_audio_device`, `test_audio_capture`, `test_audio_extended`, `test_core_app_named_device`).

## Task 1: scenario command

RED: `test_core_app_runtime` parses `audio-device NAME WITH SPACES`, a bare `audio-device`, and rejects a 128-byte name and a control character. GREEN: `CORE_APP_SCENARIO_AUDIO_DEVICE`, rest-of-line name into `event.path`.

## Task 2: audio request

RED: `test_core_app_runtime` owner-thread test on a NULL-backend system (switch to "NULL Playback Device", refuse "no such speaker", back to default; calls on the owner; stopped line `device_switches=2 device_switch_rejected=1 device_switch_failures=0`); record mode REJECTED; existing stopped-line assertions get the three new fields. GREEN: command kind, name field, `core_app_audio_request_device`, apply on the owner, counters, trace lines.

## Task 3: core_app wiring

RED: `test_core_app_named_device.cmake` runtime switch scenario (device hosts) and the record-mode rejection (all hosts). GREEN: scenario event handling in `core_app.c`, `app_scenario_supported`.

## Task 4: mutations, docs, review, push

Mutations from the spec. Docs: `Implementation_Status.md`, `missing_capabilities.md`, `audio_extended.md`, `core_app_integration.md`. Review, full ctest, both sanitizer trees, push, three CI workflows green.
