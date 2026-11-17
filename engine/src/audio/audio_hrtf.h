#pragma once
/* Head-related transfer functions: per-direction left/right impulse
 * responses and an allocation-free renderer that convolves a mono signal to
 * stereo (docs/design/audio_extended.md, "HRTF").
 *
 * Directions: azimuth in degrees, 0 straight ahead, positive to the right,
 * [-180, 180]; elevation in degrees, positive up, [-90, 90]. The unit vector
 * of (az, el) is (cos el sin az, sin el, cos el cos az) with x right, y up,
 * z ahead. */

#include <audio/audio.h>

#define AUDIO_HRTF_MAX_DIRECTIONS 2048u
#define AUDIO_HRTF_MAX_TAPS 128u
#define AUDIO_HRTF_MIN_SAMPLE_RATE 8000u
#define AUDIO_HRTF_MAX_SAMPLE_RATE 192000u
#define AUDIO_HRTF_MAX_SAMPLE 4.0f       /* |impulse response sample| */
#define AUDIO_HRTF_FADE_FRAMES 64u       /* crossfade on a direction change */
#define AUDIO_HRTF_FILE_MAGIC 0x54524842u /* "BHRT" */
#define AUDIO_HRTF_FILE_VERSION 1u
#define AUDIO_HRTF_FILE_HEADER_BYTES 20u

typedef struct AudioHrtfSet AudioHrtfSet;

typedef struct {
    f32 azimuth;
    f32 elevation;
} AudioHrtfDirection;

/* Copies `count` directions and, for each, `taps` left and `taps` right
 * samples (direction i at left[i * taps], right[i * taps]). INVALID for a
 * NULL pointer, a count, tap count or sample rate out of range, a
 * non-finite or out-of-range angle or sample, or two directions whose unit
 * vectors coincide; OVERLOAD when memory runs out. *out is written only on
 * success. */
AudioResult audio_hrtf_set_create(u32 sample_rate, u32 taps, u32 count,
                                  const AudioHrtfDirection *directions,
                                  const f32 *left, const f32 *right,
                                  AudioHrtfSet **out);

/* Reads a "BHRT" v1 file (little-endian): u32 magic, u32 version, u32
 * sample rate, u32 taps, u32 count, then per direction f32 azimuth, f32
 * elevation, taps f32 left, taps f32 right. The size must be exact; the
 * values obey the audio_hrtf_set_create rules. */
AudioResult audio_hrtf_set_parse(const void *bytes, usize size, AudioHrtfSet **out);

/* The structural model of Brown and Duda (1998): a spherical head (radius
 * 0.0875 m, sound at 343 m/s) gives each ear a one-pole one-zero head shadow
 * and a delay; five pinna echoes depend on azimuth and elevation. Sampled
 * every 15 degrees of azimuth and of elevation from -45 to 90 (one direction
 * straight up), 217 directions. */
AudioResult audio_hrtf_set_create_spherical_head(u32 sample_rate, u32 taps,
                                                 AudioHrtfSet **out);

void audio_hrtf_set_destroy(AudioHrtfSet *set); /* NULL is a no-op */
u32 audio_hrtf_set_count(const AudioHrtfSet *set);
u32 audio_hrtf_set_taps(const AudioHrtfSet *set);
u32 audio_hrtf_set_sample_rate(const AudioHrtfSet *set);
/* Borrowed; NULL for an index out of range. */
const f32 *audio_hrtf_set_left(const AudioHrtfSet *set, u32 index);
const f32 *audio_hrtf_set_right(const AudioHrtfSet *set, u32 index);
bool audio_hrtf_set_direction(const AudioHrtfSet *set, u32 index, AudioHrtfDirection *out);

/* The direction whose unit vector is closest (largest dot product) to that
 * of (azimuth, elevation); ties go to the lowest index. Angles outside their
 * range or not finite give UINT32_MAX, as does a NULL set. */
u32 audio_hrtf_set_nearest(const AudioHrtfSet *set, f32 azimuth, f32 elevation);

/* Caller-owned; process never allocates and never locks. */
typedef struct {
    const AudioHrtfSet *set;
    u32 taps;
    u32 current;          /* the filter in use */
    u32 next;             /* the filter faded towards; == current when idle */
    u32 pending;          /* requested while a fade runs */
    u32 fade;             /* frames of the fade done, 0 when idle */
    u32 cursor;           /* history write position */
    bool started;         /* a frame was processed */
    f32 history[2u * AUDIO_HRTF_MAX_TAPS];
} AudioHrtfRenderer;

/* Zero history, the direction nearest straight ahead. The set must outlive
 * the renderer. */
AudioResult audio_hrtf_renderer_init(AudioHrtfRenderer *r, const AudioHrtfSet *set);
/* Picks the nearest direction. Before the first processed frame it applies
 * at once; after that a change crossfades the two filters' outputs linearly
 * over AUDIO_HRTF_FADE_FRAMES frames (frame i of the fade, 1-based, weighs
 * the new output i / AUDIO_HRTF_FADE_FRAMES). A change while a fade runs
 * waits for it to end. INVALID for angles out of range. */
AudioResult audio_hrtf_renderer_set_direction(AudioHrtfRenderer *r, f32 azimuth, f32 elevation);
/* mono[frames] -> stereo[2 * frames], interleaved left/right. */
void audio_hrtf_renderer_process(AudioHrtfRenderer *r, const f32 *mono, f32 *stereo, u32 frames);
