# Audio: HRTF sets and a binaural renderer

Status: Done

## Goal

missing_capabilities section 10 lists HRTF as missing. The mixer has a
constant-power pan, an ITD delay line, a rear low-pass and an elevation tilt,
all separate approximations. Add the HRTF building block on its own:
per-direction left/right impulse responses, a loader for measured sets, a
built-in structural model, and an allocation-free renderer that convolves a
mono signal to stereo. Wiring it into PCM streams and event voices is the next
slice.

## API (`engine/src/audio/audio_hrtf.{h,c}`)

- Directions: azimuth in degrees, 0 straight ahead, positive to the right,
  [-180, 180]; elevation in degrees, positive up, [-90, 90].
- `AudioHrtfSet`: `count` directions (1..`AUDIO_HRTF_MAX_DIRECTIONS` = 2048),
  `taps` per ear (1..`AUDIO_HRTF_MAX_TAPS` = 128), sample rate
  8000..192000. Created by:
  - `audio_hrtf_set_create(sample_rate, taps, count, directions, left, right, &out)`
    from caller arrays (copied);
  - `audio_hrtf_set_parse(bytes, size, &out)` from the `BHRT` v1 file;
  - `audio_hrtf_set_create_spherical_head(sample_rate, taps, &out)`: the
    Brown and Duda (1998) structural model sampled every 15 degrees of
    azimuth and elevation (-45..90).
- `audio_hrtf_set_nearest(set, az, el)`: the index whose unit vector has the
  largest dot product with the requested one (ties: lowest index).
- `AudioHrtfRenderer` (caller-owned struct, no allocation): `init(set)`,
  `set_direction(az, el)`, `process(mono, stereo, frames)`. A change of
  direction crossfades the outputs of the old and new filters linearly over
  `AUDIO_HRTF_FADE_FRAMES` (64) frames; a change during a fade waits for it to
  finish. The first direction after init applies at once.

## File format `BHRT` v1 (little-endian)

`[0]` u32 magic `BHRT`, `[4]` u32 version 1, `[8]` u32 sample rate,
`[12]` u32 taps, `[16]` u32 count, then `count` records of
`f32 azimuth, f32 elevation, taps × f32 left, taps × f32 right`. The size must
be exact. Every value must be finite, angles in range, |sample| <= 4, and no
two directions may coincide (unit vectors within 1e-6).

## Tests (`engine/tests/test_audio_hrtf.c`)

1. Renderer against a double-precision direct convolution for a fixed
   direction, across process calls of uneven size.
2. Crossfade against a reference that mixes the two convolutions; a change
   mid-fade is deferred; init applies at once.
3. Nearest direction: exact hits, wrap at ±180, the pole, ties.
4. `create` and `parse` reject every invalid argument without output;
   golden `BHRT` round trip; every truncation and each field corruption is
   refused.
5. Spherical head model: front is symmetric (left == right); mirrored
   azimuths swap ears; a right source reaches the right ear first (onset
   gap equals the Woodworth ITD within a frame); the far ear has less high
   frequency energy; elevations differ in their IRs.

## Result

- `test_audio_hrtf` 8/8 passes. Test 5's high-frequency check became a
  DFT band ratio (8-16 kHz over <1 kHz, far ear < 0.25 x near ear); added
  the 2048-direction limit, the top direction, behind symmetry, equal DC
  sums and Nyquist gain = alpha ratio.
- Mutation: 44 of 45 killed; "mirror copy" at 180 degrees is equivalent.
- Shadow check rc=0. Wiring into PCM streams and event voices is next.
