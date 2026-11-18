# Core App Voice Send Plan

Spec: `docs/superpowers/specs/2026-11-18-core-app-voice-send-design.md`.

## Tasks

- [ ] 1. RED: `test_break_session` expects message 0x4006 (`BREAK_NET_MESSAGE_ID_CORE_VOICE`), version 1..1, payload limit `BREAK_VOICE_MAX_DATAGRAM_SIZE`, AUTHENTICATED, idempotent; registry count 27/26.
- [ ] 2. GREEN: register the message in `break_net_message_registry.{h,c}`.
- [ ] 3. RED: `test_core_app_network.cmake` MODE=voice and the client `voice` scenario; ctest `test_core_app_network_voice`. Fails: no voice message arrives.
- [ ] 4. GREEN: `CoreAppNetworkHooks.voice_frame`, BRV2 encode in `app_voice_consume`, `core_app_runtime` links `break_online`, transport `net_voice_frame` and the two counters.
- [ ] 5. Mutations: no hook call; BRV1 instead of BRV2. Both must fail test 3.
- [ ] 6. Offline contract: `test_core_app_network_offline` nm check still passes (no break_net/session/snow symbols).
- [ ] 7. Independent review, fix findings.
- [ ] 8. Docs: `core_app_integration.md`, `audio_extended.md`, `Implementation_Status.md`, `missing_capabilities.md`, the network message table if any.
- [ ] 9. Three trees, push, CI.
