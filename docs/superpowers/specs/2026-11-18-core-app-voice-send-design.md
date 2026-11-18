# Core App Voice Send Design

## Goal

Send the voice frames that the core_app voice lane already produces to every authenticated peer of the `--network` transport, as BRV2 (IMA ADPCM) payloads in a new registered message, and prove it end to end with the real executable and a real TLS + AUTH-v2 peer that decodes the audio.

## Scope

In scope:

- Registry: `BREAK_NET_MESSAGE_ID_CORE_VOICE = 0x4006`, protocol version 1, AUTHENTICATED phase only, `BREAK_NET_DUPLICATE_IDEMPOTENT`, payload limit `BREAK_NET_CORE_VOICE_MAX_PAYLOAD = BREAK_VOICE_MAX_DATAGRAM_SIZE` (976, one BRV1 frame of 480 samples, so a BRV1 sender stays admissible). The registry count grows by one (27 with crypto, 26 without).
- `CoreAppNetworkHooks` gains an optional `voice_frame(void *user, const u8 *data, usize size)`. The bytes are borrowed for the call. NULL keeps today's behaviour; `start` validation does not require it.
- `app_voice_consume` (CoreAppThread, every tick and in the voice drain) encodes each popped frame with `break_voice_encode_adpcm` and hands it to `voice_frame` while the network subsystem is live. The voice lane diagnostics (sequence gaps, peak) are computed from the PCM frame as before, so `--voice=fake` traces stay identical with and without `--network`.
- Transport `net_voice_frame`: while `started && producing` and the reactor event queue is empty, sends the bytes to every sendable slot (welcomed, live). It never queues: voice is real time, so a frame that cannot go out now is dropped. Counters `voice_frames_sent` (per peer send), `voice_frames_skipped` (frame not offered because not producing or events pending) and the existing `send_overloads`/`send_closed`. Both new counters are appended to `network_stats`.
- The server is send-only: a peer that sends 0x4006 has no handler, which the session manager already counts; the session stays open.

Out of scope (later slices): receiving and mixing peer voice on the server, per-peer voice routing or muting, jitter/drift handling on a real peer, tail flush, device recovery, Opus.

## Ordering and determinism

The voice subsystem is index 1 and network index 0, so network `stop_producers` runs before the voice drain: frames popped during drain are offered but skipped once `producing` is false. Network output never feeds back into the voice lane or the simulation; the hook returns nothing.

## Errors

- `voice_frame` is optional; a hook table with it NULL behaves as before.
- Encode failure: a 480-sample mono 48 kHz frame from our own pump always encodes, so a failure is a defect. `app_voice_consume` returns `BREAK_RUNTIME_FAILED` and the run fails with `stage=voice`. Encoding only happens when the hook is set, so offline traces do not change.
- Send failures (overload, closed) only change transport counters, never the run.

## Testing

1. `test_break_session`: registry contains 0x4006 with the fields above; count updated.
2. `test_core_app_network` MODE=voice (new ctest `test_core_app_network_voice`, transport builds only, not WIN32): core_app with `--voice=fake --network` for 300 ticks next to `test_core_app_net_client ... voice`. The client authenticates, collects 30 voice messages, checks each is version 1, `BRV2`, 48000 Hz, 1 channel, 480 samples, exactly `BREAK_VOICE_ADPCM_SIZE(1, 480)` bytes, consecutive sequences, decodes them through `BreakVoiceReceiver` and reports `voice frames=30 gaps=0 peak=K` with K > 4000 (tone amplitude 0.25 = 8191). The driver requires `voice_frames_sent >= 30`, the voice ready/stopped lines, and that all non-network trace lines equal an offline `--voice=fake` run of the same scenario.
3. Mutation checks: dropping the hook call, or sending raw PCM instead of BRV2, must make test 2 fail.
