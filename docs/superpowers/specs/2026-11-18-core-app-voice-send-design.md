# Core App Voice Send Design

## Goal

Send the voice frames that the core_app voice lane already produces to every authenticated peer of the `--network` transport, as BRV2 (IMA ADPCM) payloads in a new registered message, and prove it end to end with the real executable and a real TLS + AUTH-v2 peer that decodes the audio.

## Scope

In scope:

- Registry: `BREAK_NET_MESSAGE_ID_CORE_VOICE = 0x4006`, protocol version 1, AUTHENTICATED phase only, `BREAK_NET_DUPLICATE_IDEMPOTENT`, payload limit `BREAK_NET_CORE_VOICE_MAX_PAYLOAD = BREAK_VOICE_MAX_DATAGRAM_SIZE` (976, one BRV1 frame of 480 samples, so a BRV1 sender stays admissible). The registry count grows by one (27 with crypto, 26 without).
- `CoreAppNetworkHooks` gains an optional `voice_frame(void *user, const BreakVoiceFrame *frame)`. The PCM frame is borrowed for the call. NULL keeps today's behaviour; `start` validation does not require it.
- `app_voice_consume` (CoreAppThread, every tick and in the voice drain) hands each popped PCM frame to `voice_frame` while the network subsystem is live. The voice lane diagnostics (sequence gaps, peak) are computed as before, so `--voice=fake` traces stay identical with and without `--network`.
- Transport `net_voice_frame`: a NULL frame counts as `voice_frames_invalid`; while not `started && producing`, or while the reactor event queue is not empty, the frame is skipped (`voice_frames_skipped`) before it is encoded; otherwise it is encoded as BRV2 (an encoder rejection counts as invalid) and sent to every sendable slot (welcomed, live). It never queues: voice is real time. Counters `voice_frames_sent` (per peer send), `voice_frames_skipped`, `voice_frames_invalid` are appended to `network_stats`; send results also use the existing `send_overloads`/`send_closed`.
- The server is send-only: a peer that sends 0x4006 has no handler, which the session manager already counts; the session stays open.

Out of scope (later slices): receiving and mixing peer voice on the server, per-peer voice routing or muting, jitter/drift handling on a real peer, tail flush, device recovery, Opus.

## Ordering and determinism

The voice subsystem is index 1 and network index 0, so network `stop_producers` runs before the voice drain: frames popped during drain are offered but skipped once `producing` is false. Network output never feeds back into the voice lane or the simulation; the hook returns nothing.

## Errors

- `voice_frame` is optional; a hook table with it NULL behaves as before.
- Encode failure: counted as `voice_frames_invalid` and the frame is dropped; the run continues (see the revisions below).
- Send failures (overload, closed) only change transport counters, never the run.

## Testing

1. `test_break_session`: registry contains 0x4006 with the fields above; count updated.
2. `test_core_app_network` MODE=voice (new ctest `test_core_app_network_voice`, transport builds only, not WIN32): core_app with `--voice=fake --network` for 300 ticks next to `test_core_app_net_client ... voice`. The client authenticates, collects 30 voice messages, checks each is version 1, `BRV2`, 48000 Hz, 1 channel, 480 samples, exactly `BREAK_VOICE_ADPCM_SIZE(1, 480)` bytes, consecutive sequences, decodes them through `BreakVoiceReceiver` and reports `voice frames=30 gaps=0 peak=K` with K > 4000 (tone amplitude 0.25 = 8191). The driver requires `voice_frames_sent >= 30`, the voice ready/stopped lines, and that all non-network trace lines equal an offline `--voice=fake` run of the same scenario.
3. Mutation checks: dropping the hook call, or sending raw PCM instead of BRV2, must make test 2 fail.

## Revisions after independent review (2026-11-18)

- Encoding moved from `app_voice_consume` into `net_voice_frame`: the hook takes `const BreakVoiceFrame *` and `core_app_runtime` keeps its HEAD link list, so an offline `core_app` and `core_app_asset_bake` no longer reach libcrypto through `break_online`. `core_app` links `break_online` only when the transport is built; the offline contract now also rejects `break_voice_`/`break_crypto_` symbols.
- The voice hook no longer fails the run: an unencodable frame is counted as `voice_frames_invalid` and dropped (a defect upstream is visible, not fatal).
- The client accepts sequence gaps up to `voice_frames_skipped`, because `net_voice_frame` drops frames by design when a clock reply is still unprocessed; `malformed=0`, `played=30` and the peak check stay strict.
- The client sends one `0x4006` back and must still receive the next snapshot, covering the "server never handles peer voice" behaviour.
- Stale comments updated in `core_app.{h,c}`, the client header and the CMake driver header.

## Second review (agent-312, Ready, four Minor)

- `session_handler_failed >= 1` in the driver proved nothing (other traffic already exceeds it); removed. The client check `v_session_survives_voice_sent` is the evidence.
- Spec body bullets above edited in place to match the code.
- `test_core_app_net_transport` case `voice_frame_counts_invalid_and_skipped_frames`: NULL and `sample_count=0` while producing give invalid=2, two frames after `stop_producers` give skipped=2 (removing the skip gate fails it). `test_break_online_voice` case `voice_sequence_clock_conceals_a_skipped_frame_and_plays_the_next`: with the sequence clock a skipped frame is concealed once and all four received frames play.
- The client clock is now driven by the sequence (`(sequence - first) * 10 ms`), so `played == frames` holds after a server-side skip.
- The transport checks `started`/`producing`/event queue before encoding.
