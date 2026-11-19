# Core App Per-User Voice Mute Plan

Spec: `docs/superpowers/specs/2026-11-19-core-app-voice-mute-design.md`.

Trees: `build-core-app-net` (full ctest), `build-voice-relay-asan` (ASan + UBSan, network on: `test_core_app_network.*`, `test_core_app_net_transport`, `test_break_session`, `test_core_app_target_contract`).

## Task 1: registry entry 0x4008

RED: `test_break_session` asserts the definition (v1..1, 16 B, AUTHENTICATED, IDEMPOTENT) and count 29 / 28. GREEN: id, payload constant, table entry.

## Task 2: mute codec

RED: `test_core_app_network` golden bytes, malformed payloads, encode refusals. GREEN: `CORE_APP_VOICE_MUTE_*` and `core_app_voice_mute_encode/decode`; transport `#error` / `_Static_assert` against the registry.

## Task 3: transport

RED: `test_core_app_net_transport` stats tail with `voice_mute_requests=0 voice_mute_rejected=0 voice_frames_muted=0`. GREEN: per-slot list of 16 ids, `net_on_voice_mute`, clear on slot release, skip in `net_send_voice_relay`, three stats fields.

## Task 4: end to end

RED: `test_core_app_net_client` mode `voice-mute`; `client_send_tone_burst` takes a first sequence; driver MODE=voice_mute; CMake test `test_core_app_network_voice_mute`. GREEN after Task 3.

## Task 5: mutations

Mute ignored in the relay; unmute does not remove; decode result ignored. Each must compile and fail Task 4.

## Task 6: docs, review, push

`Implementation_Status.md`, `missing_capabilities.md`, `audio_extended.md`, `core_app_integration.md`, `session_protocol.md`. Independent read-only review, full ctest, ASan network tree, push, three CI workflows green.
