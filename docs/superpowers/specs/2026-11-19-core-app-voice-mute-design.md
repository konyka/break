# Core App Per-User Voice Mute Design

## Goal

A user connected to a `--voice-relay` server can tell the server to stop (and later resume) forwarding one other user's voice to it. The server then skips that recipient for that source. Proven end to end with the real executable and two real TLS + AUTH-v2 peers.

## Wire format

New message `BREAK_NET_MESSAGE_ID_CORE_VOICE_MUTE` (0x4008), peer to server, version 1..1, `AUTHENTICATED`, `IDEMPOTENT`, exactly `BREAK_NET_CORE_VOICE_MUTE_PAYLOAD` = 16 bytes. Default registry count becomes 29 (crypto on) / 28 (off).

Little-endian payload (`core_app_network.h`):

- `[0]` u32 magic `0x54554D56` ("VMUT")
- `[4]` u32 flags: bit 0 = 1 mute, 0 unmute; every other bit zero
- `[8]` u64 target session id, non-zero (the number the target received in its welcome, as named in relay headers)

Codec: `core_app_voice_mute_encode(target, muted, out, capacity, out_size)` and `core_app_voice_mute_decode(payload, size, out_target, out_muted)`. Size, magic, unknown flag bits and a zero target are rejected; no output is written on failure.

## Server behaviour

- Handler `net_on_voice_mute` on the CoreAppThread. It finds the slot (unknown or closing: return false, counted by the session layer). A payload that does not decode is counted in `voice_mute_rejected`, and the session stays open (return true).
- Each slot keeps up to `CORE_APP_NET_VOICE_MUTE_CAPACITY` = 16 muted source ids. Mute adds the id if absent; unmute removes it; both are idempotent. A mute when the list is full is counted in `voice_mute_rejected`. Every decoded request counts `voice_mute_requests`. Session ids are never reused, so an id for a user who left is harmless; it is cleared with the slot.
- The list is cleared whenever the slot is released or reused (same place the voice receiver is released), so a new connection never inherits mutes.
- `net_send_voice_relay` skips a recipient whose list holds the frame's source and counts `voice_frames_muted` (one per skipped recipient).
- Mutes work whether or not `--voice-relay` is on; without relay they only change counters.
- `network_stats` appends `voice_mute_requests`, `voice_mute_rejected`, `voice_frames_muted`.

## Determinism and isolation

Only transport state changes. The non-network trace stays equal to an offline run.

## Testing

1. `test_core_app_network`: golden bytes for mute and unmute; malformed payloads (short, long, bad magic, unknown flag bits, zero target) rejected with outputs untouched; encode refuses a zero target, NULL buffers and a short buffer.
2. `test_break_session`: 0x4008 definition and count 29 / 28.
3. `test_core_app_net_transport`: stats tail with the three new fields at 0.
4. `test_core_app_network_voice_mute` (MODE=voice_mute, server with `--voice-relay`): A and B authenticate. B sends a malformed mute, then mute(A), then a barrier. A sends 20 tone frames (sequences 0..19) plus a duplicate and a wrong-rate frame, then a barrier; B's barrier must see no relay. B sends unmute(A) and a barrier. A sends sequences 20..39 the same way; B must receive exactly those 20 relays from A, consecutive, decodable, peak at least 4000. Server stats: `voice_frames_received=40`, `voice_frames_dropped=4`, `voice_frames_relayed=20`, `voice_frames_muted=20`, `voice_mute_requests=2`, `voice_mute_rejected=1`; trace equal to offline.
5. Mutations, each must fail test 4: mute ignored in the relay; unmute does not remove; malformed mute applied as a mute of the decoded bits (decode check skipped).

Out of scope: server-side mixing, voice rate limits, telling the target it was muted, persisting mutes across reconnects.
