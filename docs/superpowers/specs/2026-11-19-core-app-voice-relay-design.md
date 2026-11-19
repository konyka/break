# Core App Voice Relay Design

## Goal

With `--voice-relay`, the `--network` server forwards every voice frame it accepts from one authenticated peer to every other authenticated peer, tagged with the sender's session number, so peers can talk to each other through the server. Proven end to end with the real executable and two real TLS + AUTH-v2 peers.

## Wire format

New message `BREAK_NET_MESSAGE_ID_CORE_VOICE_RELAY` (0x4007), server to peer, version 1..1, `AUTHENTICATED`, `IDEMPOTENT`, payload limit `BREAK_NET_CORE_VOICE_RELAY_MAX_PAYLOAD` = 16 + 976 = 992 bytes. The default registry count becomes 28 (crypto on) / 27 (off).

Little-endian payload (`core_app_network.h`):

- `[0]` u32 magic `0x594C5256` ("VRLY")
- `[4]` u32 reserved, zero
- `[8]` u64 source session id, non-zero (the number the source peer received in its own session welcome)
- `[16]` the frame bytes exactly as the source sent them (one BRV1 or BRV2 frame, 1..976 bytes)

Codec: `core_app_voice_relay_encode(source, frame, frame_size, out, capacity, out_size)` and `core_app_voice_relay_decode(payload, size, out_source, out_frame, out_frame_size)`. Decode returns a pointer into the payload and checks size bounds, magic, reserved bytes and a non-zero source; it does not parse the frame (the receiver does). On failure no output is written.

A separate id, instead of reusing 0x4006, keeps the existing voice contract unchanged and lets a client keep one jitter buffer per source: two talkers' sequence numbers are independent and would collide in one buffer.

## Server behaviour

- `--voice-relay` is a network option (requires `--network`, rejected otherwise with "network options require --network"); `CoreAppNetTransportConfig.voice_relay` carries it. Default off: a user's voice is never forwarded unless the operator asked for it.
- `net_on_voice` compares the slot receiver's `accepted` count before and after the pump. Only a frame the receiver accepted (well-formed, right format, not duplicate, not stale, not overflowing) is relayed. The source id comes from `break_session_manager_session_id` for the connection, because voice can be applied in the same batch as AUTH, before the slot's own session id is recorded; a zero id is not relayed.
- Accepted frames are copied into a transport-owned ring of 32 entries (source id, size, bytes). The handler never sends: sends wait in `net_send_pending` until the reactor event queue is empty, like every other send, so a close for a reused key cannot misroute a frame. A full ring counts `voice_relay_dropped`.
- `net_send_pending` encodes each queued frame once and sends it to every sendable slot whose session id differs from the source. Each successful send counts `voice_frames_relayed`; overload and closed sends use the existing counters. Entries still queued at destroy are counted as `voice_relay_dropped`.
- `network_stats` appends `voice_frames_relayed` and `voice_relay_dropped`.
- The server registers no handler for 0x4007: a peer that sends one is counted by the session layer as `handler_failed` and stays connected.

## Determinism and isolation

Relaying only touches transport state. The non-network trace stays equal to an offline run. The relay codec is plain byte packing in `core_app_network.c` and pulls no voice codec or crypto into the offline build.

## Testing

1. `test_core_app_network`: golden-byte round trip; every malformed payload (short, empty frame, over the limit, bad magic, reserved bits, zero source) is rejected and leaves outputs untouched; encode rejects a NULL or empty frame, a frame over 976 bytes, a zero source and a short buffer.
2. `test_break_session`: 0x4007 definition (v1..1, 992 B, AUTHENTICATED, IDEMPOTENT) and count 28 / 27.
3. `test_core_app_net_transport`: stats line ends with `voice_peak=0 voice_frames_relayed=0 voice_relay_dropped=0`.
4. `test_core_app_network_voice_relay` (MODE=voice_relay, server with `--voice-relay`): peers A and B authenticate. A sends 20 consecutive BRV2 tone frames, a duplicate and one wrong-rate frame, then a clock probe as a barrier. After A's reply, B sends a clock probe and reads until its reply; on the way it must receive exactly 20 relay messages, all from A's session id, consecutive sequences 0..19, which decode through a real receiver with a peak of at least 4000. A then sends a second probe and must see no relay message before its reply. Server stats: `voice_frames_relayed=20`, `voice_relay_dropped=0`, `voice_frames_received=20`, `voice_frames_dropped=2`; non-network trace equal to offline.
5. `test_core_app_network_voice_relay_off` (MODE=voice_relay_off, same client flow, no flag): B must receive no relay message; `voice_frames_relayed=0`.
6. `test_core_app_target_contract`: `--voice-relay` without `--network` is rejected.
7. Mutations, each must fail test 4 or 5: source not excluded; relay not gated by the flag; relay before the accepted check (duplicate relayed).

Out of scope: per-peer muting, mixing peer voice on the server, voice rate limits, drift compensation, Opus.

## Result

- All new tests went RED first (undeclared constants and codec, stats tail, CLI contract) and are GREEN. End to end: B received 20 relay messages from A's session, consecutive, all decoded, peak 9334; A received none; with the flag off B received none.
- Mutations: source not excluded (fails voice_relay: `ra_never_receives_own_voice`, echoed=20); relay not gated by the flag (fails voice_relay_off); relay before the accepted check (fails voice_relay). A first attempt at the source mutation (`&& 0`) did not compile under `-Werror` and was replaced by `t->session_ids[i] == 0u`.
- Full suite 449/449. The existing sanitizer trees build without the network transport, so a new tree `build-voice-relay-asan` (ASan + UBSan, Snowflake, network on) ran the 11 network tests, all passing.
- Review (Ready) minors addressed: `voice_frames_relayed` documented as one per recipient send; server-side overload/stale frames are not relayed and a newly welcomed peer can receive up to 32 queued frames (documented); the test barrier computes the remaining time once so it cannot wrap; `usize` in the sender.
