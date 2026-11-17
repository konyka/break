#pragma once
/* Relative clock drift from confidence-gated fractional delay measurements,
 * using a bounded sliding-window linear regression
 * (docs/design/audio_extended.md, "Clock drift estimation"). Owner thread;
 * only create allocates. The resampling compensator is a separate component. */

#include <audio/audio.h>

typedef struct {
    u32 window_size;          /* 2..1024 accepted samples */
    f32 min_abs_correlation;  /* 0..1 */
    f32 max_abs_drift_ppm;    /* 1..10000 */
} AudioDriftEstimatorConfig;

typedef struct AudioDriftEstimator AudioDriftEstimator;

/* INVALID for NULL/out-of-range config, OVERLOAD on allocation failure; *out
 * is written only on success. */
AudioResult audio_drift_estimator_create(const AudioDriftEstimatorConfig *config,
                                         AudioDriftEstimator **out);
void audio_drift_estimator_destroy(AudioDriftEstimator *est); /* NULL is a no-op */
void audio_drift_estimator_reset(AudioDriftEstimator *est);
/* Accept finite delay/correlation, |correlation| at least the configured minimum
 * and a strictly increasing frame index. False leaves the window unchanged. */
bool audio_drift_estimator_push(AudioDriftEstimator *est, u64 frame_index,
                                double delay_frames, double correlation);
/* Least-squares delay slope in ppm and the signed mean accepted correlation.
 * False with untouched outputs for insufficient/degenerate samples, non-finite
 * results or drift beyond the configured absolute limit. */
bool audio_drift_estimator_estimate(AudioDriftEstimator *est,
                                    double *drift_ppm, double *mean_correlation);
/* Repeated-median slope using the same accepted samples and mean correlation.
 * False with untouched outputs on invalid inputs, non-finite intermediates or
 * drift beyond the configured limit. */
bool audio_drift_estimator_estimate_robust(AudioDriftEstimator *est,
                                           double *drift_ppm,
                                           double *mean_correlation);
u32 audio_drift_estimator_count(const AudioDriftEstimator *est); /* 0 for NULL */
