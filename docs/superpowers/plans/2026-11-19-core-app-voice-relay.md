# Core App Voice Relay Plan

Spec: `docs/superpowers/specs/2026-11-19-core-app-voice-relay-design.md`.

Build tree `build-core-app-net` (`cmake --build . -j16 && ctest -j16`); sanitizer trees `build-voice-recovery-asan` / `build-voice-recovery-tsan` with the voice regex plus `test_core_app_network_voice_relay.*`.

## Task 1: registry entry 0x4007

1. RED: `test_break_session` asserts the 0x4007 definition and count 28 / 27.
2. GREEN: `BREAK_NET_MESSAGE_ID_CORE_VOICE_RELAY`, `BREAK_NET_CORE_VOICE_RELAY_MAX_PAYLOAD` in `break_net_message_registry.h`; entry in the default table; count 28 / 27.

## Task 2: relay codec

1. RED: `test_core_app_network` golden round trip and malformed-payload tests.
2. GREEN: `CORE_APP_VOICE_RELAY_*` constants and `core_app_voice_relay_encode/decode` in `core_app_network.h/.c`; transport `_Static_assert`s that the id and the max payload match the registry.

## Task 3: transport relay

1. RED: `test_core_app_net_transport` stats tail with `voice_frames_relayed=0 voice_relay_dropped=0`.
2. GREEN: `voice_relay` config field, ring of 32 entries, accepted-count gate in `net_on_voice`, send in `net_send_pending` after welcomes and before clock replies, destroy counts leftover entries, two stats fields.

## Task 4: CLI flag

1. RED: target contract `--voice-relay` without `--network` is rejected.
2. GREEN: `--voice-relay` in `main.c` (usage, parsing, `net_option_seen`).

## Task 5: end to end

1. RED: `test_core_app_net_client` mode `voice-relay` (peers A and B as in the spec), driver MODE=voice_relay and voice_relay_off, two CMake tests.
2. GREEN: run both; confirm they fail before Task 3/4 code is wired (check by mutation) and pass after.

## Task 6: mutations

Source not excluded; relay without the flag; relay before the accepted check. Each must compile and fail Task 5 tests.

## Task 7: docs, review, push

`Implementation_Status.md`, `missing_capabilities.md`, `audio_extended.md`, `core_app_integration.md`, `session_protocol.md` (0x4007 row and count). Independent read-only review, full ctest, both sanitizer trees, push, three CI workflows green.
