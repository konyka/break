#include "audio_drift_compensator.h"

#include <math.h>
#include <stdlib.h>

struct AudioDriftCompensator {
    AudioDriftEstimator *estimator;
    AudioDriftResampler resampler;
    u32 min_samples;
    double max_correction;
    double gain;
    bool robust;
    u64 corrections;
    u64 clamped;
};

static bool compensator_config_valid(const AudioDriftCompensatorConfig *config) {
    if (!config) return false;
    if (config->min_samples < 2u || config->min_samples > config->estimator.window_size) {
        return false;
    }
    if (!isfinite(config->max_correction_ppm) || config->max_correction_ppm < 1.0f ||
        !(config->max_correction_ppm <= config->estimator.max_abs_drift_ppm)) {
        return false;
    }
    return isfinite(config->gain) && config->gain > 0.0f && config->gain <= 1.0f;
}

AudioResult audio_drift_compensator_create(const AudioDriftCompensatorConfig *config,
                                           AudioDriftCompensator **out) {
    if (!out || !compensator_config_valid(config)) return AUDIO_INVALID;
    AudioDriftCompensator *comp = (AudioDriftCompensator *)calloc(1u, sizeof(*comp));
    if (!comp) return AUDIO_OVERLOAD;
    const AudioResult result = audio_drift_estimator_create(&config->estimator, &comp->estimator);
    if (result != AUDIO_OK) {
        free(comp);
        return result;
    }
    (void)audio_drift_resampler_init(&comp->resampler, 1.0);
    comp->min_samples = config->min_samples;
    comp->max_correction = (double)config->max_correction_ppm * 1e-6;
    comp->gain = (double)config->gain;
    comp->robust = config->robust;
    *out = comp;
    return AUDIO_OK;
}

void audio_drift_compensator_destroy(AudioDriftCompensator *comp) {
    if (!comp) return;
    audio_drift_estimator_destroy(comp->estimator);
    free(comp);
}

void audio_drift_compensator_reset(AudioDriftCompensator *comp) {
    if (!comp) return;
    audio_drift_estimator_reset(comp->estimator);
    (void)audio_drift_resampler_set_ratio(&comp->resampler, 1.0);
    audio_drift_resampler_reset(&comp->resampler);
}

bool audio_drift_compensator_observe(AudioDriftCompensator *comp, u64 frame_index,
                                     double delay_frames, double correlation) {
    if (!comp) return false;
    return audio_drift_estimator_push(comp->estimator, frame_index, delay_frames, correlation);
}

bool audio_drift_compensator_update(AudioDriftCompensator *comp) {
    if (!comp || audio_drift_estimator_count(comp->estimator) < comp->min_samples) return false;
    double drift_ppm = 0.0;
    double correlation = 0.0;
    const bool estimated =
        comp->robust
            ? audio_drift_estimator_estimate_robust(comp->estimator, &drift_ppm, &correlation)
            : audio_drift_estimator_estimate(comp->estimator, &drift_ppm, &correlation);
    if (!estimated) return false;
    double ratio = comp->resampler.ratio * (1.0 - comp->gain * drift_ppm * 1e-6);
    if (!isfinite(ratio)) return false;
    if (ratio > 1.0 + comp->max_correction) {
        ratio = 1.0 + comp->max_correction;
        comp->clamped++;
    } else if (ratio < 1.0 - comp->max_correction) {
        ratio = 1.0 - comp->max_correction;
        comp->clamped++;
    }
    if (audio_drift_resampler_set_ratio(&comp->resampler, ratio) != AUDIO_OK) return false;
    /* the residual slope changes with the ratio: older measurements are stale */
    audio_drift_estimator_reset(comp->estimator);
    comp->corrections++;
    return true;
}

double audio_drift_compensator_ratio(const AudioDriftCompensator *comp) {
    return comp ? comp->resampler.ratio : 0.0;
}

double audio_drift_compensator_correction_ppm(const AudioDriftCompensator *comp) {
    return comp ? (1.0 - comp->resampler.ratio) * 1e6 : 0.0;
}

u64 audio_drift_compensator_corrections(const AudioDriftCompensator *comp) {
    return comp ? comp->corrections : 0u;
}

u64 audio_drift_compensator_clamped(const AudioDriftCompensator *comp) {
    return comp ? comp->clamped : 0u;
}

u32 audio_drift_compensator_output_capacity(const AudioDriftCompensator *comp,
                                            u32 input_frames) {
    return comp ? audio_drift_resampler_output_capacity(&comp->resampler, input_frames) : 0u;
}

AudioResult audio_drift_compensator_process_i16(AudioDriftCompensator *comp,
                                                const i16 *in, u32 input_frames,
                                                i16 *out, u32 out_capacity,
                                                u32 *out_frames) {
    if (!comp) return AUDIO_INVALID;
    return audio_drift_resampler_process_i16(&comp->resampler, in, input_frames, out,
                                             out_capacity, out_frames);
}
