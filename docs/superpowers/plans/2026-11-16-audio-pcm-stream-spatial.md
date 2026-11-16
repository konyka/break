# Spatial PCM streams (2026-11-16)

## Goal
PCM streams (network voice) play at a fixed gain. Event voices already get
distance attenuation from the listener, with occlusion, through
`event_spatial_gain`. A voice stream that belongs to a user in the world
should fade with distance the same way. This slice adds an opt-in
position to PCM streams.

## Design
- `audio_pcm_stream_set_spatial(as, handle, min_distance, max_distance,
  rolloff, occluded_gain)`: turns distance attenuation on with the same
  parameters and checks as an event (`min_distance > 0`, `max_distance >=
  min_distance`, `rolloff >= 0`, `occluded_gain` in 0..1; otherwise
  `AUDIO_INVALID`, nothing changes).
- `audio_pcm_stream_set_position(as, handle, position)`: stores the
  position and publishes the new gain. A stream without spatial settings
  returns `AUDIO_REJECTED` (checked first); a non-finite position is
  `AUDIO_INVALID` and leaves the old position and gain.
- The gain is the same inverse-distance model and occlusion ray as
  `event_spatial_gain` (shared through one helper, so both always agree).
- The listener moving (`audio_system_update` ->
  `audio_extended_listener_update`) recomputes every spatial stream's
  gain.
- The mixer reads the spatial gain from an atomic (bit pattern of an
  f32), multiplied into volume x bus x master. A non-spatial stream's
  spatial gain is 1.
- Not done: panning / HRTF (gain only, like event voices), doppler.

## Tests (TDD, `test_audio_extended`)
- argument checks for both functions; stale handle; `set_position` before
  `set_spatial` is `REJECTED`.
- gain at min distance is 1, at a farther point follows
  `min / (min + rolloff * (d - min))`, beyond max is clamped at max.
- a listener move changes the rendered gain without a new set_position.
- the occlusion ray callback multiplies `occluded_gain` in.
- a reopened slot starts non-spatial (gain 1).

## Status
- RED: the three spatial cases failed against stubs returning
  `AUDIO_FAILED`; the 52 existing cases passed.
- GREEN: `test_audio_extended` 56/56, `test_voice_playback` 3/3, all
  audio tests pass. `event_spatial_gain` now calls the shared
  `spatial_gain`; a new case checks a spatial event and a spatial stream
  at the same place get the same gain.
- Mutation: 17 mutations. The first run had two survivors:
  - `set_position` checked each coordinate itself before the shared model
    checked them again; only the first coordinate was tested. The check
    is gone; `set_position` now keeps the old position when the model
    refuses the new one, and a test checks both are unchanged.
  - the event path passing a fixed rolloff of 1 instead of its own: every
    event test used rolloff 1. The shared-model test uses rolloff 3.
  Second and third runs: all killed (one more mutation needed a different
  form to compile under `-Werror`).
- TSan (three runs) and ASan+UBSan clean.
