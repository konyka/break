# Break online voice: mix the voice of several peers

## Problem

The server relays each peer's voice frame (`0x4007`, source session id + BRV1/BRV2 frame) to every other peer. A receiving peer has one `BreakVoiceReceiver` (jitter buffer, concealment) per stream, but nothing combines several sources into one playback frame. Every consumer would have to keep its own map of receivers and its own summing loop.

## Design

New component in `break_online` (`src/network/break_voice_mixer.h/.c`), same owner-thread rule as `BreakVoiceReceiver`.

- `BreakVoiceMixerConfig`: `stream` (a `BreakVoiceStreamConfig` used for every source receiver, socket NULL), `max_sources` (1..`BREAK_VOICE_MIXER_MAX_SOURCES` = 16), `idle_timeout_ms` (0 = never evict).
- `break_voice_mixer_create(config, &out)` / `destroy`. Only create allocates the source table; a source's receiver is created on its first frame.
- `break_voice_mixer_push(mixer, source, bytes, size, now_ms)`: source 0 is INVALID. A new source takes a free entry; with none free the oldest idle source (`now_ms - last_push_ms >= idle_timeout_ms`, timeout > 0) is evicted, otherwise OVERLOAD (counted `sources_refused`). The bytes go to that source's receiver (`push` + `pump`); the receiver's own result is returned (a malformed frame is counted by the receiver, not by the mixer).
- `break_voice_mixer_pop(mixer, now_ms, out, &ready)`: pops at most one playback from every source receiver and sums them sample by sample in i32, saturating to i16 (`clipped_samples` counts each saturated sample). `ready` is true when at least one source produced a frame; `out->sequence` is the mixer's own frame counter, `concealed` is true only when every contributing frame was concealed, `sample_count` is the stream's.
- `break_voice_mixer_stats`: `sources` (live now), `sources_created`, `sources_evicted`, `sources_refused`, `mixed_frames`, `clipped_samples`, plus the sum of the receivers' `accepted`/`played`/`concealed`/`invalid`.
- Sources are kept in insertion order, so the sum order and the trace are deterministic.

## Testing (`test_break_voice_mixer`, registered next to `test_break_online_voice`)

1. Two sources with known PCM mix to the exact sum; a third with a large value saturates and counts clipped samples.
2. One source whose next frame is late conceals; with the other source present the output is not marked concealed.
3. Source 0, NULL arguments, bad config (0 or 17 sources) are INVALID; pop on another thread is REJECTED.
4. A 17th source is refused with OVERLOAD while all are active; after the idle timeout the oldest is evicted and the new source is admitted.
5. A malformed frame from one source leaves the others' output unchanged.
6. Mutations: summing without saturation; eviction ignoring the idle timeout; `concealed` set when any input was concealed.

Out of scope: gain per source, wiring the mixer into core_app (core_app has no client mode), resampling between sources of different rates (all sources share one stream format).
