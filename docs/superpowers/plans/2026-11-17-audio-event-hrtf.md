# Audio: HRTF on event voices

Status: Done

## Goal

Spatial PCM streams render binaurally through an `AudioHrtfSet`. Give event
voices the same option so both kinds of spatial source can use HRTF.

## API

- `AudioEventDesc.hrtf` (`audio_extended.h`): `const AudioHrtfSet *`, NULL
  for none. `audio_event_register` returns INVALID when it is set without
  `spatial` or the set's rate is not `AUDIO_PCM_SAMPLE_RATE`. Events cannot
  be unregistered, so the set must outlive the `AudioSystem`.

## Behaviour

- Owner thread: `hrtf_direction_index` (shared with streams) at trigger,
  `audio_voice_set_position` and listener updates. Trigger puts the index in
  the START command; later updates store `(revision, index)` in
  `hrtf_snapshot` before the gain snapshot, like the other cues.
- Mixer: START re-initialises the voice's own renderer (empty history, also
  on RESTART) and applies the START index at once; a later index is taken
  only with its revision and crossfades over 64 frames. The mono downmix
  `0.5 (l + r)` goes through the renderer, times the voice gain; the DSP
  chain still runs after it. Panning, rear, elevation and ITD do not apply.

## Tests (`test_audio_extended`)

1. Register: needs spatial and the engine rate.
2. Mono event to the right equals direct convolution times distance gain,
   with the other cues on.
3. Stereo clip uses the downmix; set_position and listener updates move the
   index.
4. A move matches a reference renderer bit for bit.
5. RESTART starts from an empty history.

## Result

- `test_audio_extended` 129/129. Mutation: 11 of 11 killed.
