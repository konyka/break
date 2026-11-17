# Audio: microphone capture

Status: Done

## Goal

Network voice can be received, decoded and played, but nothing records it.
Add a capture module that opens an input device and hands the owner thread
16-bit PCM frames, ready for `break_voice_encode*`.

## API (`engine/src/audio/audio_capture.h`)

- `AudioCaptureConfig { backend, sample_rate, channels, ring_frames }`:
  DEFAULT opens the system's default input, NULL miniaudio's silent null
  device, FAKE no device (frames come from `audio_capture_inject`).
  Rate 8000..192000, 1 or 2 channels, ring a power of two up to 2^20 frames.
- `audio_capture_create` (INVALID for a bad config or NULL out, FAILED when
  the device does not open; `*out` only on success), `_destroy` (NULL no-op,
  stops a running device).
- `_start` / `_stop` (idempotent), `_running`.
- `_read_i16(cap, out, max_frames, &n)`: oldest frames first, interleaved.
- `_available`, `_overruns` (frames dropped because the ring was full).
- `_inject(cap, f32 samples, frames)`: FAKE only (REJECTED otherwise, and
  while stopped); the same write path the device callback uses.

## Behaviour

- One producer (the device callback, or the injecting thread for FAKE), one
  consumer (the owner thread). Free-running u32 head/tail, release/acquire.
- f32 to i16: non-finite is 0, clamp to [-1, 1], `lrintf(x * 32767)`.
- A full ring drops the newest frames and counts them; the callback never
  blocks, allocates or logs (added to `test_audio_realtime_contract`).

## Tests (`test_audio_capture`)

1. Config validation; `*out` untouched on failure.
2. FAKE: conversion (clamp, rounding, non-finite), order, partial reads,
   wrap across the ring end, stereo interleaving.
3. Overrun keeps the oldest frames and counts the rest.
4. Inject rejected while stopped and on a NULL device; start/stop idempotent.
5. NULL device: start delivers silent frames within 2 s; stop, restart,
   destroy while running.
6. Producer and consumer threads: a ramp arrives in order, no frame lost
   when the consumer keeps up (TSan tree).

## Result

- `test_audio_capture` 7/7; the realtime contract covers the callback
  (fails with an injected malloc). Mutation: 20 of 20 killed. TSan and
  ASan+UBSan clean, shadow check clean.
