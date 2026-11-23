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
/* Same search and readiness rules as the integer estimate. Interpolates the
 * absolute correlation peak by a parabola, limited to +/- 0.5 frame. Returns
 * the signed score at the integer peak. Integer lag is used at the boundaries
 * or when no concave local peak exists. Outputs are untouched on failure. */
bool audio_delay_estimator_estimate_subframe(AudioDelayEstimator *est,
                                             double *delay_frames,
                                             double *correlation);

typedef struct AudioDelayLine AudioDelayLine;

/* max_delay_frames 0..AUDIO_DELAY_ESTIMATOR_MAX_DELAY; starts at delay 0 with
 * a silent history. INVALID or OVERLOAD as above. */
AudioResult audio_delay_line_create(u32 max_delay_frames, AudioDelayLine **out);
void audio_delay_line_destroy(AudioDelayLine *line); /* NULL is a no-op */
/* Clears the history to silence and cancels an active fade. Keeps the maximum,
 * current delay, sinc mode and crossfade duration; later output matches a new
 * line with the same settings. No allocation; NULL is a no-op. */
void audio_delay_line_reset(AudioDelayLine *line);
/* INVALID for NULL or a delay above the maximum. Takes effect on the next
 * frame. Immediate by default; uses the configured crossfade when nonzero. */
AudioResult audio_delay_line_set_delay(AudioDelayLine *line, u32 delay_frames);
u32 audio_delay_line_delay(const AudioDelayLine *line); /* integer part; 0 for NULL */
/* Finite delay in [0, max_delay]. For D=d+f, reads (1-f)*x[n-d] + f*x[n-d-1].
 * The integer setter is equivalent to an integer call; crossfade is optional. */
AudioResult audio_delay_line_set_subframe_delay(AudioDelayLine *line, double delay_frames);
double audio_delay_line_subframe_delay(const AudioDelayLine *line); /* 0 for NULL */
/* Selects a causal 16-tap Blackman-windowed sinc interpolator. The configured
 * delay accessors still report D, but processing delays input by D + 8.
 * INVALID for NULL; mode changes take effect on the next frame. */
AudioResult audio_delay_line_set_sinc(AudioDelayLine *line, bool enabled);
bool audio_delay_line_sinc(const AudioDelayLine *line); /* false for NULL */
u32 audio_delay_line_sinc_extra_delay(const AudioDelayLine *line); /* 0 for NULL */
/* Sets the duration of later delay transitions, 0..48000 frames. INVALID for
 * NULL/out-of-range; REJECTED while a fade is active. Zero preserves immediate
 * transitions. Delay/mode setters are also REJECTED during an active fade. */
AudioResult audio_delay_line_set_crossfade_frames(AudioDelayLine *line, u32 frames);
u32 audio_delay_line_crossfade_frames(const AudioDelayLine *line); /* 0 for NULL */
/* out[n] is the current integer, linearly interpolated, or sinc delayed input;
 * `in` and `out` may be the same buffer. */
void audio_delay_line_process_i16(AudioDelayLine *line, const i16 *in, i16 *out, u32 frames);
