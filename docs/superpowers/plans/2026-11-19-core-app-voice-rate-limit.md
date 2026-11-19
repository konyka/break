# Core App Voice Rate Limit Plan

Spec: `docs/superpowers/specs/2026-11-19-core-app-voice-rate-limit-design.md`.

Trees: `build-core-app-net` (full ctest), `build-voice-relay-asan` (network tests).

## Task 1: stats field

RED: `test_core_app_net_transport` expects `voice_frames_rate_limited=0` at the end of the stats line. GREEN: counter and format.

## Task 2: end to end

RED: `test_core_app_net_client` mode `voice-flood` (A sends 200 frames, then barriers on A and B; report line with B's relay count), driver MODE=voice_flood, CMake test `test_core_app_network_voice_flood`. It must fail before the limiter exists (`voice_frames_rate_limited` stays 0).

## Task 3: limiter

GREEN: per-slot `BreakMsgRate` and ready flag, initialised with the receiver, reset in `net_voice_release`; admit before push in `net_on_voice`. Link `break_msg_rate.c` into `core_app` and `test_core_app_net_transport` if not already.

## Task 4: guard existing tests

Voice, relay, relay_off and mute drivers require `voice_frames_rate_limited=0`.

## Task 5: mutations, docs, review, push

Mutations: no admit check; limiter re-initialised on every message. Docs: `Implementation_Status.md`, `missing_capabilities.md`, `audio_extended.md`, `core_app_integration.md`. Review, full ctest, ASan network tree, push, three CI workflows green.
