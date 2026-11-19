# Core App Voice Rate Limit Design

## Goal

The `--network` server limits how much voice (0x4006) one connection may send, so a single user cannot flood the server's jitter buffers or, with `--voice-relay`, every other user. Frames over the limit are dropped and counted before they are decoded or relayed; the session stays open.

## Behaviour

- Each slot gets a `BreakMsgRate` (`src/network/break_msg_rate.h`) for voice only, created with the slot's voice receiver on its first voice message and reset when the receiver is released.
- Limits: `CORE_APP_NET_VOICE_RATE_PER_SEC` = 120 frames/s (one 10 ms stream is 100/s, plus 20% for jitter), `CORE_APP_NET_VOICE_RATE_BURST` = 64 frames (the jitter buffer size), bytes 120 × 976 per second with a 64 × 976 burst, so the frame bucket is the one that binds for any valid frame.
- The clock is the transport's monotonic `time_microseconds() / 1000`, the same one the jitter buffer uses.
- `net_on_voice` admits the message after the slot and empty-payload checks and before the receiver push. A refused frame counts `voice_frames_rate_limited` and returns true. It is never pushed, so it is never counted as received, dropped or relayed.
- The session-layer limit (`break_session_manager_set_message_rate`) stays off: it would also throttle snapshots, physics and clock messages, whose rates differ.
- `network_stats` appends `voice_frames_rate_limited`.

## Testing

1. `test_core_app_net_transport`: stats tail ends with `voice_frames_rate_limited=0`.
2. `test_core_app_network_voice_flood` (MODE=voice_flood, server with `--voice-relay`): A and B authenticate; A sends 200 consecutive BRV2 frames as fast as TLS allows, then a barrier, and B a barrier. Requirements: `voice_frames_rate_limited >= 1`; `voice_frames_received >= 64`; `voice_frames_received + voice_frames_dropped + voice_frames_rate_limited == 200`; `voice_frames_relayed + voice_relay_dropped == voice_frames_received`; B received exactly `voice_frames_relayed` relays from A; A's barrier reply arrives (session open); trace equal to offline.
3. Existing voice, relay and mute tests send at most 22 frames per burst and must still see `voice_frames_rate_limited=0`.
4. Mutations, each must fail test 2: no admit check; limiter state reset on every message.

Out of scope: configurable limits, closing a flooding connection, limits for other message ids.

## Result

- RED: the stats tail, and voice_flood failed with `the flood was not rate limited` (B received all 64 frames the jitter buffer could hold, limited=0). GREEN after the limiter: received=64, rate_limited=136, relayed=64, B received 64.
- Mutations: no admit check; limiter re-initialised on every message. Both fail voice_flood.
- Full suite 451/451; `build-voice-relay-asan` 13 network tests pass.
