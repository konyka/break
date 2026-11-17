#pragma once
/* Delay between the playback reference and the captured echo, by
 * normalised cross-correlation, and a delay line that aligns the reference
 * for audio_echo_canceller (docs/design/audio_extended.md, "Delay
 * estimation"). Mono, owner thread only; allocates only in create. */

#include <audio/audio.h>

#define AUDIO_DELAY_ESTIMATOR_MAX_DELAY 96000u
#define AUDIO_DELAY_ESTIMATOR_MIN_WINDOW 16u
#define AUDIO_DELAY_ESTIMATOR_MAX_WINDOW 96000u

typedef struct {
    u32 max_delay_frames; /* 1..AUDIO_DELAY_ESTIMATOR_MAX_DELAY, lags 0..max are searched */
    u32 window_frames;    /* MIN_WINDOW..MAX_WINDOW, capture frames correlated per estimate */
} AudioDelayEstimatorConfig;

typedef struct AudioDelayEstimator AudioDelayEstimator;

/* INVALID for a NULL argument or a config out of range, OVERLOAD when memory
 * runs out; *out is written only on success. */
AudioResult audio_delay_estimator_create(const AudioDelayEstimatorConfig *config,
                                         AudioDelayEstimator **out);
void audio_delay_estimator_destroy(AudioDelayEstimator *est); /* NULL is a no-op */
/* Forgets every pushed frame. */
void audio_delay_estimator_reset(AudioDelayEstimator *est);
/* Appends `frames` aligned frames of the playback reference and the
 * capture. */
void audio_delay_estimator_push_i16(AudioDelayEstimator *est, const i16 *reference,
                                    const i16 *capture, u32 frames);
/* Correlates the latest window_frames of the capture with the reference
 * at every lag 0..max_delay_frames and writes the lag with the largest
 * |correlation| (the smaller lag on a tie) and that correlation in [-1, 1].
 * False (outputs untouched) until window + max_delay frames were pushed, or
 * when the capture window or every reference window is silent. Costs
 * (max_delay + 1) * window multiply-adds. */
bool audio_delay_estimator_estimate(AudioDelayEstimator *est, u32 *delay_frames,
                                    double *correlation);

typedef struct AudioDelayLine AudioDelayLine;

/* max_delay_frames 0..AUDIO_DELAY_ESTIMATOR_MAX_DELAY; starts at delay 0 with
 * a silent history. INVALID or OVERLOAD as above. */
AudioResult audio_delay_line_create(u32 max_delay_frames, AudioDelayLine **out);
void audio_delay_line_destroy(AudioDelayLine *line); /* NULL is a no-op */
/* INVALID for NULL or a delay above the maximum. Takes effect on the next
 * frame, reading the history at the new delay (no crossfade). */
AudioResult audio_delay_line_set_delay(AudioDelayLine *line, u32 delay_frames);
u32 audio_delay_line_delay(const AudioDelayLine *line); /* 0 for NULL */
/* out[n] = in[n - delay]; `in` and `out` may be the same buffer. */
void audio_delay_line_process_i16(AudioDelayLine *line, const i16 *in, i16 *out, u32 frames);
