# Design: drift compensation in the core_app voice pump

## Problem

`AudioDriftCompensator` (`engine/src/audio/audio_drift_compensator.h`) closes
the clock drift loop as a component, but the core_app voice pump
(`engine/apps/core_app/core_app_voice.c`) still feeds the raw playback
reference to the aligner. When the playback and capture devices run on
different clocks the echo path delay walks away and the echo canceller loses
it. Drift compensation in the voice pipeline is listed as missing in
`docs/cross_engine/missing_capabilities.md`.

## Change

- `CoreAppVoiceConfig` gains `bool drift_enabled` and
  `AudioDriftCompensatorConfig drift`. With `drift_enabled` false the pump is
  byte-for-byte what it is today (existing tests keep passing unchanged).
- `core_app_voice_create` creates the compensator when enabled; INVALID for a
  config the compensator refuses.
- Pump, per packet, when enabled: raw reference frames are resampled through
  the compensator into a resampled-reference FIFO (capacity 4096 frames), and
  the aligner gets the oldest 480 FIFO frames instead of the raw read. A
  packet is ready when 480 capture frames are available and the FIFO holds 480
  frames or 480 raw reference frames can be read.
- Measurement: `audio_voice_aligner` gains `audio_voice_aligner_correlation`
  (the tracker's latest score). After each packet whose aligner update count
  grew and whose tracker is locked, the pump calls
  `audio_drift_compensator_observe(capture_frames_total, delay, correlation)`.
  Every `drift.min_samples` accepted observations it calls `update`; the next
  observation after a successful update is skipped (its window still holds the
  old ratio).
- Recovery, switch and playback reopen reset the compensator and empty the
  FIFO: a new device has its own clock.
- `CoreAppVoiceStats` gains `drift_corrections` (u64) and
  `drift_correction_ppb` (i64, `correction_ppm * 1000`, rounded).
- core_app enables it in `app_voice_config` (window 32, min_samples 32,
  max 300 ppm, gain 0.5, observe every 10 packets) and the voice `result=stopped` trace line appends
  `drift_corrections=N drift_ppb=M`.

## Tests

- `test_core_app_voice`: a fake playback renders a noise reference; the test
  builds the capture from the rendered reference on a clock drifting by
  +100 ppm and injects it. After 40 s of packets `drift_corrections > 0` and
  `drift_correction_ppb` is within 10 ppm of 100 000. With `drift_enabled`
  false the same run keeps `drift_corrections == 0`.
- A capture recovery resets the correction to 0.
- Existing voice and runtime tests unchanged (they leave drift disabled or see
  no correction within their short runs); the voice lane contract matches the
  new trace fields.

## Out of scope

Multichannel, sinc mode, real acoustic validation.

## Result

- `audio_voice_aligner_correlation`: RED (stub returned 0) then GREEN in `test_audio_voice_aligner`.
- Voice pump: the two new `test_core_app_voice` cases failed first (no correction; create accepted a zero gain), then 18/18.
- `CoreAppVoiceConfig.drift_observe_packets` (1..1000) was added to pace measurements; core_app uses window 32, min_samples 32, gain 0.5, every 10 packets.
- Mutations: FIFO bypassed, no reset on recovery, update never called, create ignoring the observe period. Each fails a test.
- Voice lane and device contracts match the new `drift_corrections=` and `drift_ppb=` fields.
- Review round 1: Not ready. Critical: with a ratio above 1 one raw packet resamples to 479 frames, the readiness check only asked for 480 ring frames, and the second refill read came up short, so the pump returned FAILED. Fixed: readiness needs `ceil(missing * ratio) + 2` raw frames rounded up to whole packets; refills loop by packet. New tests: a playback clock 200 ppm slower (no failure, converges near -200 ppm); a capture switch and a playback reopen reset the ratio (20 tests). The +100 ppm case also checks that compensation leaves at least 6 dB less residual echo than no compensation (about 10.3 dB here). Mutations (old readiness, no reset on switch, no reset on playback reopen) each fail a test.
