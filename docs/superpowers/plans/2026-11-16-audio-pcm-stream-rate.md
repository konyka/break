# PCM streams at other sample rates (2026-11-16)

## Goal
`audio_pcm_stream_*` plays at the engine rate (48 kHz) only. Voice is
usually sent at 8, 16 or 24 kHz to save bandwidth, and the voice receiver
accepts any rate from 1 to 192000 Hz, so a 16 kHz voice stream could not
be played without the caller resampling it. This slice lets a stream take
PCM at its own rate and converts it to 48 kHz in the mixer.

## Design
- `audio_pcm_stream_open_rate(as, channels, sample_rate, bus, volume,
  &handle)`; `audio_pcm_stream_open` stays and means 48 kHz.
  `sample_rate` is 8000..192000 Hz; anything else is `AUDIO_INVALID`.
- The ring keeps source-rate frames and keeps its capacity of
  `AUDIO_PCM_STREAM_FRAMES` (16384, a power of two so the free-running
  counters wrap correctly). That is about 341 ms at 48 kHz and longer at
  lower rates (about 1 s at 16 kHz), which only means a voice stream can
  buffer more.
- The mixer converts by linear interpolation. The read position is an
  integer in units where one source frame is 48000 units; each output
  frame adds the stream's rate. Each output frame reads the two source
  frames around the position, so no frame is consumed until the position
  passes it. (A 32.32 fixed-point step was tried first: 1/3 rounds down,
  the position drifted low, and the 16 kHz test saw one frame too many
  queued. The integer form is exact for every rate.) Linear interpolation is enough for voice; no low-pass filter
  is applied when downsampling (a 96 kHz stream will alias above 24 kHz,
  documented, not tested).
- Underrun: when the next source frame needed is not in the ring, the
  output frame is silence and counts as an underrun; the phase does not
  advance past missing data, so a late write continues where playback
  stopped.
- `queued` stays in source frames.

## Tests (TDD, `test_audio_extended`)
- `open_rate` bounds: 7999 and 192001 fail, 8000 and 192000 open.
- 16 kHz mono: three output frames per source frame; interpolation gives
  the exact values between two known samples.
- 24 kHz stereo keeps the channels apart.
- 96 kHz: two source frames per output frame (takes every other frame
  when the interpolation weight is 0); a frame that decimation steps past
  before it is written is skipped once it arrives.
- a stream reopened in the slot of one closed between two source frames
  starts on its own first frame.
- underrun at a non-48 kHz rate: missing data plays silence, counts, and
  a later write resumes from the same source position.
- `test_voice_playback`: a 16 kHz voice stream end to end.

## Status
- RED: the five rate cases failed against a stub `open_rate` returning
  `AUDIO_FAILED`; the 45 existing cases passed.
- GREEN: `test_audio_extended` 52/52, `test_voice_playback` 3/3 (new
  `voice_at_16k_plays_through_a_rate_converting_stream`: 16 kHz voice
  through the real receiver, every source sample at its 48 kHz position
  and the frames between interpolated, no underrun).
- The first implementation used a 32.32 fixed-point step; 16000/48000 is
  not exact in binary, the position drifted low, and the 16 kHz case saw
  one frame too many queued. The position is now an integer in
  1/48000-frame units, exact for every rate.
- TSan found a race in the rewritten mixer callback: it read the stream
  position of a closed slot while `open` on another thread reset it. The
  callback now reads the position only for an open stream. Five TSan runs
  and an ASan+UBSan run are clean.
- Mutation: 19 mutations. One survived the first two runs: the position
  reset in `open`. The reopen test wrote two equal samples, so a leftover
  fractional position interpolated between equal values and changed
  nothing; with different samples it fails. Third run: all killed.
