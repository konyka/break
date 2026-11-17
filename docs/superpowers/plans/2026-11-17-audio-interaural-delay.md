# Spatial PCM streams: interaural time difference (2026-11-17)

Status: Done

## Goal
Panning and the rear cue only change levels. The ear further from a source
also hears it later, up to about 0.66 ms for a source straight to the side.
This slice adds an opt-in delay of the far ear for spatial PCM streams.

## Design
- `audio_pcm_stream_set_interaural_delay(as, h, enabled)`: REJECTED for a
  stream without `set_spatial`; off at open.
- Lateral amount `p = listener_pan(position)` (the cosine against the right
  vector, already used by panning), lateral angle `t = asin(|p|)`.
  Woodworth model: `seconds = r / c * (t + |p|)` with
  `r = AUDIO_PCM_STREAM_HEAD_RADIUS` (0.0875 m) and
  `c = AUDIO_PCM_STREAM_SPEED_OF_SOUND` (343 m/s); `frames = lrint(seconds *
  48000)`, 0 to 31 (`AUDIO_PCM_STREAM_ITD_MAX_FRAMES`). A source on the right
  delays the left channel, on the left the right channel. A source in
  front, behind, above or on the listener has no delay.
- The owner thread computes the signed frame count with the gain and pan
  (`set_spatial`, `set_position`, listener update) and publishes it as one
  atomic int (positive: left delayed); the mixer reads it once per callback.
- The mixer writes each played frame, after the rear cue and before gain and
  pan, into a 64-frame delay line and reads the delayed ear from it. The
  line is written while the delay is off too, so turning it on, or a source
  moving to the side, delays real history instead of inserting silence.
  Open zeroes the line. A change of delay jumps (no crossfade).

## Tests (TDD, `test_audio_extended`)
- arguments: REJECTED without spatial, INVALID handle or system, STALE.
- front, behind, above and on the listener: output exactly the input.
- straight right: left is the input 31 frames late (zeros first), right
  exact; straight left: the mirror.
- 30 degrees to the right: delay from the model (13 frames).
- turning the delay on after 40 frames plays history, not zeros; the
  listener turning to face the source removes the delay.
- stereo: the delayed ear takes its own channel; reopen clears the line.

## Not done
HRTF, elevation cues, smoothing delay changes. The delay on event voices:
see 2026-11-17-audio-event-interaural-delay.md.

## Result
- RED: the five new tests failed to compile (no setter, no `itd_frames`).
  GREEN: `test_audio_extended` 99/99.
- Mutation: 18 mutants, 3 survived the first round. Not resetting the
  enable flag at open is now caught by a reopened stream made spatial again
  on the left. The clamp to `AUDIO_PCM_STREAM_ITD_MAX_FRAMES` could not be
  reached (the pan is within -1..1) and was removed. `itd > 0` changed to
  `itd >= 0` is equivalent: with no delay the line returns the frame just
  written.

