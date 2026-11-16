# Spatial PCM streams: front/back cue (2026-11-16)

Status: Done

## Goal
Stereo panning only tells left from right: a source straight ahead and one
straight behind sound the same. Without HRTF, the usual cheap cue is the
head shadow: sound from behind loses its top end. This slice adds an
opt-in low-pass that grows as a spatial stream moves behind the listener.

## Design
- `audio_pcm_stream_set_rear_cue(as, h, enabled)`: REJECTED for a stream
  without `set_spatial`; off at open.
- Behind amount `b = max(0, -cos(angle(source - listener, forward)))`, 0 for
  a source in front or to the side, 1 straight behind; 0 for a source on
  the listener or a zero forward vector.
- One-pole low-pass `y += alpha (x - y)` per channel, with
  `alpha = 1 - b (1 - alpha_rear)` and
  `alpha_rear = 1 - exp(-2 pi AUDIO_PCM_STREAM_REAR_CUTOFF_HZ / 48000)`
  (5 kHz, alpha_rear about 0.48). alpha is continuous across the side
  plane; alpha = 1 means no filter.
- The owner thread computes alpha with the gain (`set_spatial`,
  `set_position`, listener update) and publishes it as one atomic f32;
  the mixer reads it once per callback.
- The mixer filters each played frame after interpolation and before gain
  and pan. With alpha = 1 the frame passes exactly and the state follows
  it, so turning the cue on, or a source moving behind, starts from the
  current signal (no click from a stale state). The state is mixer-owned
  like `pos`; open resets it.

## Tests (TDD, `test_audio_extended`)
- arguments: REJECTED without spatial, INVALID handle or system, STALE.
- a source in front or to the side: output exactly as without the cue.
- straight behind: the step response matches the one-pole model.
- 45 degrees behind: alpha from the blend formula.
- the listener turns round: the filter stops and the signal passes exactly.
- a 24 kHz tone behind is attenuated to about a third; in front it is not.
- stereo channels keep separate state; reopen resets the cue and state.

## Not done
HRTF, interaural time delay, elevation cues, the cue on event voices.

## Result
- RED: 5 of 6 new tests failed against a stub (front/side passes by design,
  the cue must not change it), 81 existing passed. GREEN:
  `test_audio_extended` 87/87, `test_voice_playback` 4/4, audio ctest 5/5.
- Mutation: 21 mutants, 5 survived the first round. Tests were added for the
  right channel's state following the signal, a source on the listener, the
  exact coefficient 1 in front, a non-unit forward vector and a reopened
  non-spatial slot; the front check became `behind <= 0`. All 5 then killed.
- ASan+UBSan and three TSan runs: no reports.
