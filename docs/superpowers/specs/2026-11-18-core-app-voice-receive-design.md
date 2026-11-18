# Core App Voice Receive Design

## Goal

The `--network` transport accepts `BREAK_NET_MESSAGE_ID_CORE_VOICE` (0x4006) from authenticated peers instead of rejecting it, decodes it through one `BreakVoiceReceiver` (jitter buffer) per connection, plays the buffered frames out on the transport's monotonic clock, and reports what it received. Proven end to end with the real executable and a real TLS + AUTH-v2 peer that sends a tone.

## Scope

In scope:

- Handler `net_on_voice` registered for 0x4006 in `net_start`. It runs on the CoreAppThread (session manager poll), finds the slot and requires that it exists and is not closing (the session layer already admits 0x4006 only in the AUTHENTICATED phase; `net_slot_live` would refuse voice that arrives in the same pump batch as AUTH, before `net_sync_sessions` marks the slot). An empty payload is counted as dropped and accepted. It creates the slot's receiver on the first voice message (48 kHz, mono, 480 samples, `jitter_delay_ms = 40`, `jitter_capacity = 64` (the receiver maximum, so a burst of buffered frames on the ordered TLS stream never overflows), `queue_capacity = 4`), pushes the payload and pumps it at once, so the receiver inbox never holds more than one datagram. It returns false (counted by the session layer as `handler_failed`) only when the slot is unknown or closing, or the receiver cannot be created or rejects the push.
- `net_tick` pops the frames whose playout time has come, per slot, after `net_pump`, at most 16 per slot per tick (a frame with a far later sequence would otherwise make the receiver conceal every missing frame before it in one loop); the tail flush pops at most 128. Played frames update `voice_peak` (largest absolute sample); concealed frames are counted.
- Tail flush: when a slot is released (connection closed or transport error, and in `net_destroy`), the remaining buffered frames are popped with `now = UINT64_MAX`, so every frame the peer sent before it closed is played or concealed in order, then the receiver statistics are added to the totals and the receiver is destroyed.
- `network_stats` appends `voice_frames_received` (receiver `accepted`), `voice_frames_played`, `voice_frames_concealed`, `voice_frames_dropped` (receiver `invalid + duplicate + stale + overload`) and `voice_peak`. `net_destroy` releases all receivers before it traces the statistics.

Out of scope (later slices): mixing or rendering peer voice, forwarding voice between peers, per-peer muting, drift compensation, per-peer rate limits beyond the session layer's own, Opus.

## Determinism and isolation

Received voice only changes transport counters. It never reaches the level, the simulation, the audio device or the voice lane, so the non-network trace stays equal to an offline run. The offline `core_app` still links no voice codec or crypto (the existing nm check).

## Errors

- Malformed, wrong-format, duplicate, stale or overflowing frames are counted by the receiver and summed in `voice_frames_dropped`; the session stays open.
- Receiver creation failure: the message is rejected and counted; later messages retry the creation.

## Testing

1. `test_break_online_voice`: `voice_pop_at_max_time_flushes_buffered_frames_in_order` documents the tail-flush contract (three buffered frames pop in order with `now = UINT64_MAX`, none concealed, then nothing is ready).
2. `test_core_app_network` MODE=voice: after decoding the server's 30 frames, the client sends a burst of 20 consecutive BRV2 frames of a 0.25 tone (sequences 0..19), one duplicate of sequence 19 and one frame with the wrong sample rate, then a clock probe; the probe reply proves the server applied every voice message first (one session's messages are applied in order), and it must still receive a snapshot. With the 40 ms playout delay most of the burst is still buffered when the peer closes, so it plays only through the tail flush. The driver requires `voice_frames_received=20`, `voice_frames_played=20`, `voice_frames_concealed=0`, `voice_frames_dropped=2`, `voice_peak >= 4000`, and the existing non-network trace equality.
3. Mutations: no handler registration; no tail flush; peak taken before decode (always 0). Each must fail test 2.

## Revisions during implementation

- The first RED run with frames paced 10 ms apart counted only one dropped frame: the peer closed before the server had read its last message. A clock probe sent after the voice now acts as a barrier, and the frames are sent as one burst so the tail flush is exercised.
- Mutations (handler not registered; no tail flush; peak not updated) each fail `test_core_app_network_voice`.
