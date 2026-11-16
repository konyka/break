# Audio PCM stream for network voice playback (2026-11-16)

## Goal
`break_online_voice` receives `BRV1` frames, reorders them and hands out
decoded `i16` PCM (`BreakVoicePlayback`), but nothing plays that PCM:
`pop` "does not mix and does not call the audio device"
(`docs/design/online_session_network.md` §4). The audio system only plays
registered clips and files. This slice adds a streaming PCM source to the
audio system so received voice (or any producer of live PCM) reaches the
mixer, buses and device.

## Design
- `audio_extended.h`: an `AudioPcmStream` API on `AudioSystem`.
  - `audio_pcm_stream_open(as, channels (1|2), bus, volume, &handle)`:
    at most `AUDIO_PCM_STREAM_MAX` (4) streams. Each owns a lock-free
    single-producer / single-consumer ring of
    `AUDIO_PCM_STREAM_FRAMES` (48000 / 4 = 12000 frames, 250 ms at the
    48 kHz engine rate) interleaved `f32` frames, allocated at open.
  - `audio_pcm_stream_write_i16(as, handle, samples, frame_count,
    &written)`: converts `i16` to `f32` (x / 32768) and copies as many
    frames as fit; returns `AUDIO_OK` with `written <= frame_count`.
    Never blocks, never allocates. The producer is one thread (the
    caller's, e.g. LogicThread after `break_voice_receiver_pop`).
  - `audio_pcm_stream_queued(as, handle, &frames)`: frames waiting.
  - `audio_pcm_stream_close(as, handle)`: stops and frees the stream;
    the slot can be reused with a new generation (stale handles fail).
  - The mixer side reads the ring in its data-source callback: it plays
    what is queued and outputs silence on underrun, counting underrun
    frames (`audio_pcm_stream_underruns`). Gain is volume x bus x master,
    like event voices.
  - Sample rate: the stream is at the engine rate (48 kHz). The voice
    receiver's stream config must match; a rate converter is out of
    scope.
- Test seam: the FAKE backend renders on the calling thread
  (`audio_system_render`), so tests drive the consumer side directly.

## Tests (TDD, `test_audio_extended`)
- open bounds (channels 0/3, NULL handle, bus fallback, the fifth open
  fails); stale handle after close; reopen.
- write converts and the render outputs `samples / 32768` for mono
  (duplicated to both channels) and stereo; volume and bus gain apply.
- the ring is bounded: writing more than the capacity writes only what
  fits; `queued` reports it; rendering drains it.
- underrun: rendering more frames than queued outputs the queued PCM then
  silence, and the underrun counter grows by the missing frames.
- an end-to-end case in a new `test_voice_playback` (it links the real
  `break_online` receiver): `break_voice_encode` -> receiver push / pump /
  pop with frames sent out of order -> `audio_pcm_stream_write_i16` ->
  render gives the original PCM in sender order, with no underrun.

## Status
- RED: the three stream cases failed against stubs returning
  `AUDIO_FAILED`; the 41 existing `test_audio_extended` cases passed.
- GREEN: `test_audio_extended` 44/44, `test_voice_playback` 2/2, every
  audio-labelled test passes. Full ctest: default and plugins-ON trees
  414/414.
- `test_audio_realtime_contract` now also checks `pcm_stream_read` (no
  allocation, file I/O, decoder or event calls in the mixer callback). A
  `free(NULL)` planted in the callback made it fail.
- Mutation: 22 mutations, five survived the first run:
  - the underrun counter stayed correct when it skipped closed streams,
    because a closed stream is never read with a stale handle; the check
    was redundant and is gone (a closed stream counts nothing because its
    counter is reset on reopen and not visible while closed);
  - slot bits above `AUDIO_PCM_STREAM_MAX`, the master fader, a bus id
    that is not created yet, and a reopened slot's counters were not
    tested; four assertions now cover them.
  Second run: 21 mutations, all killed.
- Threading: the producer owns `head`, the mixer owns `tail`. `close`
  clears `open`, then waits for a mixer read in progress (`reading`)
  before freeing the ring.
- `test_voice_playback` adds `producer_and_close_race_with_a_mixer_thread`:
  a second thread renders continuously while the test opens, fills and
  closes a stream 200 times and checks every rendered sample is silence or
  the written value. It is clean under TSan (three runs) and ASan+UBSan.
  With the wait in `close` removed, ASan reports a heap-use-after-free in
  16 of 20 runs.
  The first version used C11 `<threads.h>`; under TSan the thread
  segfaulted inside `__tsan_func_entry` before any test code ran, so the
  test uses `core/platform_thread.h` like the other threaded tests.
- Not done: sample-rate conversion (the stream runs at the engine's
  48 kHz, so a voice stream must use that rate), spatial positioning of a
  stream, capture from a microphone.
