# Core App Voice Send Plan

Spec: `docs/superpowers/specs/2026-11-18-core-app-voice-send-design.md`.

## Tasks

- [x] 1. RED: `test_break_session` expects message 0x4006 (`BREAK_NET_MESSAGE_ID_CORE_VOICE`), version 1..1, payload limit `BREAK_VOICE_MAX_DATAGRAM_SIZE`, AUTHENTICATED, idempotent; registry count 27/26.
- [x] 2. GREEN: register the message in `break_net_message_registry.{h,c}`.
- [x] 3. RED: `test_core_app_network.cmake` MODE=voice and the client `voice` scenario; ctest `test_core_app_network_voice`. Fails: no voice message arrives.
- [x] 4. GREEN: `CoreAppNetworkHooks.voice_frame`, BRV2 encode in `app_voice_consume`, `core_app_runtime` links `break_online`, transport `net_voice_frame` and the two counters.
- [x] 5. Mutations: no hook call; BRV1 instead of BRV2. Both must fail test 3.
- [x] 6. Offline contract: `test_core_app_network_offline` nm check still passes (no break_net/session/snow symbols).
- [x] 7. Independent review, fix findings.
- [x] 8. Docs: `core_app_integration.md`, `audio_extended.md`, `Implementation_Status.md`, `missing_capabilities.md`, the network message table if any.
- [ ] 9. Three trees, push, CI.

## Review round 1 (agent-312, Not ready)

- Important 1 (libcrypto pulled into offline core_app): fixed by moving the BRV2 encode into `net_voice_frame`, so the hook passes `const BreakVoiceFrame *` and `core_app_runtime` keeps its HEAD link list; only `core_app` links `break_online` in transport builds. Added an offline check for `break_voice_`/`break_crypto_` symbols plus a readelf confirmation.
- Important 2 (test could fail on timing): the client now accepts `gaps <= voice_frames_skipped`; `malformed`, `played` and the peak stay strict.
- Minor 3 (uncounted rejects): `voice_frames_invalid` counter added to `network_stats`.
- Minor 4 (stale comments): fixed in `core_app.h`, `core_app.c`, the client header and the CMake driver header.
- Minor 5 (0x4006 from a peer untested): the client now sends one back and must still receive the next snapshot; the driver requires `session_handler_failed >= 1`.
- Minor 6 (pre-existing underflow pattern in the client timeout arithmetic): left as is, consistent with the existing loops.

## Review round 2 (agent-312, Ready)

- Removed the non-discriminating `session_handler_failed` driver check; fixed the spec body; added the invalid/skipped transport unit test and the sequence-clock receiver test; client clock driven by sequence; skip check before encode.
- [x] 7. Independent review: Ready after round 2.
