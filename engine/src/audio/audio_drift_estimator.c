#include "audio_drift_estimator.h"

#include <math.h>
#include <stdlib.h>

struct AudioDriftEstimator {
    u32 size;
    u32 pos;
    u32 count;
    bool has_last;
    u64 last_frame;
    double min_correlation;
    double max_drift_ppm;
    u64 *frames;
    double *delays;
    double *correlations;
};

static bool drift_in_range(double value, double low, double high) {
    return value >= low && value <= high;
}

AudioResult audio_drift_estimator_create(const AudioDriftEstimatorConfig *config,
                                         AudioDriftEstimator **out) {
    if (!config || !out || config->window_size < 2u || config->window_size > 1024u ||
        !drift_in_range(config->min_abs_correlation, 0.0, 1.0) ||
        !drift_in_range(config->max_abs_drift_ppm, 1.0, 10000.0)) {
        return AUDIO_INVALID;
    }
    AudioDriftEstimator *est = (AudioDriftEstimator *)calloc(1u, sizeof(*est));
    if (!est) return AUDIO_OVERLOAD;
    est->size = config->window_size;
    est->min_correlation = config->min_abs_correlation;
    est->max_drift_ppm = config->max_abs_drift_ppm;
    est->frames = (u64 *)calloc(est->size, sizeof(u64));
    est->delays = (double *)calloc(est->size, sizeof(double));
    est->correlations = (double *)calloc(est->size, sizeof(double));
    if (!est->frames || !est->delays || !est->correlations) {
        audio_drift_estimator_destroy(est);
        return AUDIO_OVERLOAD;
    }
    *out = est;
    return AUDIO_OK;
}

void audio_drift_estimator_destroy(AudioDriftEstimator *est) {
    if (!est) return;
    free(est->frames);
    free(est->delays);
    free(est->correlations);
    free(est);
}

void audio_drift_estimator_reset(AudioDriftEstimator *est) {
    if (!est) return;
    est->pos = 0u;
    est->count = 0u;
    est->has_last = false;
    est->last_frame = 0u;
}

bool audio_drift_estimator_push(AudioDriftEstimator *est, u64 frame_index,
                                double delay_frames, double correlation) {
    if (!est || !isfinite(delay_frames) || !isfinite(correlation) ||
        fabs(correlation) < est->min_correlation ||
        (est->has_last && frame_index <= est->last_frame)) {
        return false;
    }
    u32 index;
    if (est->count < est->size) {
        index = (est->pos + est->count) % est->size;
        ++est->count;
    } else {
        index = est->pos;
        est->pos = (est->pos + 1u) % est->size;
    }
    est->frames[index] = frame_index;
    est->delays[index] = delay_frames;
    est->correlations[index] = correlation;
    est->last_frame = frame_index;
    est->has_last = true;
    return true;
}

bool audio_drift_estimator_estimate(AudioDriftEstimator *est,
                                    double *drift_ppm, double *mean_correlation) {
    if (!est || !drift_ppm || !mean_correlation || est->count < 2u) return false;
    const u64 base = est->frames[est->pos];
    double mean_x = 0.0, mean_y = 0.0, mean_c = 0.0;
    for (u32 i = 0; i < est->count; ++i) {
        mean_x += (double)(est->frames[i] - base);
        mean_y += est->delays[i];
        mean_c += est->correlations[i];
    }
    mean_x /= est->count;
    mean_y /= est->count;
    mean_c /= est->count;
    double numerator = 0.0, denominator = 0.0;
    for (u32 i = 0; i < est->count; ++i) {
        const double x = (double)(est->frames[i] - base) - mean_x;
        const double y = est->delays[i] - mean_y;
        numerator += x * y;
        denominator += x * x;
    }
    if (denominator <= 0.0) return false;
    const double drift = numerator / denominator * 1e6;
    if (!isfinite(drift) || !isfinite(mean_c) || fabs(drift) > est->max_drift_ppm) {
        return false;
    }
    *drift_ppm = drift;
    *mean_correlation = mean_c;
    return true;
}

u32 audio_drift_estimator_count(const AudioDriftEstimator *est) {
    return est ? est->count : 0u;
}
