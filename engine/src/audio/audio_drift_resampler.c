#include "audio_drift_resampler.h"

#include <math.h>
#include <string.h>

#define AUDIO_DRIFT_RESAMPLER_SINC_DELAY 8u

static const double kPi = 3.14159265358979323846;

static bool drift_ratio_valid(double ratio) {
    return isfinite(ratio) && ratio >= 0.1 && ratio <= 10.0;
}

AudioResult audio_drift_resampler_init(AudioDriftResampler *resampler, double ratio) {
    if (!resampler || !drift_ratio_valid(ratio)) return AUDIO_INVALID;
    resampler->ratio = ratio;
    resampler->sinc = false;
    audio_drift_resampler_reset(resampler);
    return AUDIO_OK;
}

void audio_drift_resampler_reset(AudioDriftResampler *resampler) {
    if (!resampler) return;
    resampler->next_output = 0.0;
    resampler->next_input = 0u;
    resampler->previous = 0;
    memset(resampler->history, 0, sizeof(resampler->history));
}

AudioResult audio_drift_resampler_set_ratio(AudioDriftResampler *resampler, double ratio) {
    if (!resampler || !drift_ratio_valid(ratio)) return AUDIO_INVALID;
    resampler->ratio = ratio;
    return AUDIO_OK;
}

double audio_drift_resampler_ratio(const AudioDriftResampler *resampler) {
    return resampler ? resampler->ratio : 0.0;
}

AudioResult audio_drift_resampler_set_sinc(AudioDriftResampler *resampler, bool enabled) {
    if (!resampler) return AUDIO_INVALID;
    resampler->sinc = enabled;
    return AUDIO_OK;
}

bool audio_drift_resampler_sinc(const AudioDriftResampler *resampler) {
    return resampler ? resampler->sinc : false;
}

u32 audio_drift_resampler_sinc_extra_delay(const AudioDriftResampler *resampler) {
    return resampler && resampler->sinc ? AUDIO_DRIFT_RESAMPLER_SINC_DELAY : 0u;
}

u32 audio_drift_resampler_output_capacity(const AudioDriftResampler *resampler,
                                          u32 input_frames) {
    if (!resampler || input_frames == 0u) return 0u;
    double bound = ceil((double)input_frames / resampler->ratio) + 2.0;
    const double pending = (double)resampler->next_input - resampler->next_output;
    if (!resampler->sinc && pending > 1.0) {
        bound += ceil(pending / resampler->ratio);
    }
    return bound > (double)UINT32_MAX ? 0u : (u32)bound;
}

static i16 drift_history_at(const AudioDriftResampler *resampler, u64 index) {
    return resampler->history[index % 32u];
}

static double drift_linear_history_sample(const AudioDriftResampler *resampler,
                                          double position) {
    const u64 whole = (u64)floor(position);
    const double fraction = position - (double)whole;
    return (1.0 - fraction) * drift_history_at(resampler, whole) +
           fraction * drift_history_at(resampler, whole + 1u);
}

static double drift_normalized_sinc(double value) {
    return fabs(value) < 1e-12 ? 1.0 : sin(kPi * value) / (kPi * value);
}

static double drift_sinc_sample(const AudioDriftResampler *resampler, double position) {
    const u64 whole = (u64)floor(position);
    const double fraction = position - (double)whole;
    if (fraction == 0.0) return drift_history_at(resampler, whole);
    double value = 0.0, weight_sum = 0.0;
    for (int j = -7; j <= 8; ++j) {
        const int tap = j + 7;
        const double window = 0.42 - 0.5 * cos(2.0 * kPi * tap / 15.0) +
                              0.08 * cos(4.0 * kPi * tap / 15.0);
        const double weight = drift_normalized_sinc(fraction - j) * window;
        if (j >= 0 || whole >= (u64)(-j)) {
            const u64 source = j < 0 ? whole - (u64)(-j) : whole + (u64)j;
            value += drift_history_at(resampler, source) * weight;
        }
        weight_sum += weight;
    }
    return value / weight_sum;
}

static i16 drift_sinc_i16(double value) {
    const double rounded = nearbyint(value);
    if (rounded > 32767.0) return 32767;
    if (rounded < -32768.0) return -32768;
    return (i16)rounded;
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
        resampler->history[resampler->next_input % 32u] = current;
        if (resampler->sinc) {
            while (resampler->next_output + AUDIO_DRIFT_RESAMPLER_SINC_DELAY <= index) {
                out[produced++] = drift_sinc_i16(drift_sinc_sample(resampler,
                                                                    resampler->next_output));
                resampler->next_output += resampler->ratio;
            }
        } else {
            while (resampler->next_output <= index) {
                double value = 0.0;
                if (resampler->next_output < index - 1.0) {
                    value = drift_linear_history_sample(resampler, resampler->next_output);
                } else {
                    double fraction = resampler->next_output - (index - 1.0);
                    if (fraction < 0.0) fraction = 0.0;
                    if (fraction > 1.0) fraction = 1.0;
                    value = (1.0 - fraction) * resampler->previous + fraction * current;
                }
                out[produced++] = (i16)nearbyint(value);
                resampler->next_output += resampler->ratio;
            }
        }
        resampler->previous = current;
        ++resampler->next_input;
    }
    *out_frames = produced;
    return AUDIO_OK;
}
