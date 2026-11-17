#include "audio_drift_resampler.h"

#include <math.h>

static bool drift_ratio_valid(double ratio) {
    return isfinite(ratio) && ratio >= 0.1 && ratio <= 10.0;
}

AudioResult audio_drift_resampler_init(AudioDriftResampler *resampler, double ratio) {
    if (!resampler || !drift_ratio_valid(ratio)) return AUDIO_INVALID;
    resampler->ratio = ratio;
    audio_drift_resampler_reset(resampler);
    return AUDIO_OK;
}

void audio_drift_resampler_reset(AudioDriftResampler *resampler) {
    if (!resampler) return;
    resampler->next_output = 0.0;
    resampler->next_input = 0u;
    resampler->previous = 0;
}

AudioResult audio_drift_resampler_set_ratio(AudioDriftResampler *resampler, double ratio) {
    if (!resampler || !drift_ratio_valid(ratio)) return AUDIO_INVALID;
    resampler->ratio = ratio;
    return AUDIO_OK;
}

double audio_drift_resampler_ratio(const AudioDriftResampler *resampler) {
    return resampler ? resampler->ratio : 0.0;
}

u32 audio_drift_resampler_output_capacity(const AudioDriftResampler *resampler,
                                          u32 input_frames) {
    if (!resampler || input_frames == 0u) return 0u;
    const double bound = ceil((double)input_frames / resampler->ratio) + 2.0;
    return bound > (double)UINT32_MAX ? 0u : (u32)bound;
}

AudioResult audio_drift_resampler_process_i16(AudioDriftResampler *resampler,
                                              const i16 *in, u32 input_frames,
                                              i16 *out, u32 out_capacity,
                                              u32 *out_frames) {
    if (!resampler || !out_frames) return AUDIO_INVALID;
    if (input_frames == 0u) {
        *out_frames = 0u;
        return AUDIO_OK;
    }
    if (!in || !out) return AUDIO_INVALID;
    const u32 required = audio_drift_resampler_output_capacity(resampler, input_frames);
    if (required == 0u || out_capacity < required) return AUDIO_INVALID;
    u32 produced = 0u;
    for (u32 i = 0; i < input_frames; ++i) {
        const i16 current = in[i];
        const double index = (double)resampler->next_input;
        while (resampler->next_output <= index) {
            double fraction = resampler->next_output - (index - 1.0);
            if (fraction < 0.0) fraction = 0.0;
            if (fraction > 1.0) fraction = 1.0;
            const double value = (1.0 - fraction) * resampler->previous + fraction * current;
            out[produced++] = (i16)nearbyint(value);
            resampler->next_output += resampler->ratio;
        }
        resampler->previous = current;
        ++resampler->next_input;
    }
    *out_frames = produced;
    return AUDIO_OK;
}
