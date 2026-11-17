#include "audio_agc.h"

#include <math.h>
#include <string.h>

/* false for NaN as well as for a value outside [lo, hi] */
static bool agc_in_range(double x, double lo, double hi) {
    return x >= lo && x <= hi;
}

/* one-pole coefficient for a time constant of `ms` at `rate` frames/s */
static double agc_alpha(double ms, u32 rate) {
    return 1.0 - exp(-1000.0 / (ms * (double)rate));
}

AudioResult audio_agc_init(AudioAgc *agc, const AudioAgcConfig *config) {
    if (!agc || !config || !agc_in_range((double)config->sample_rate, 8000.0, 192000.0) ||
        (config->channels != 1u && config->channels != 2u) ||
        !agc_in_range(config->target_dbfs, -60.0, 0.0) ||
        !agc_in_range(config->max_gain_db, 0.0, 60.0) ||
        !agc_in_range(config->attack_ms, 0.1, 1000.0) ||
        !agc_in_range(config->release_ms, 1.0, 10000.0) ||
        !agc_in_range(config->gate_dbfs, -120.0, 0.0) ||
        !(config->gate_dbfs < config->target_dbfs)) {
        return AUDIO_INVALID;
    }
    AudioAgc state;
    memset(&state, 0, sizeof(state));
    state.channels = config->channels;
    state.target_db = config->target_dbfs;
    state.max_gain_db = config->max_gain_db;
    state.gate_db = config->gate_dbfs;
    state.level_alpha = agc_alpha(10.0, config->sample_rate);
    state.attack_alpha = agc_alpha(config->attack_ms, config->sample_rate);
    state.release_alpha = agc_alpha(config->release_ms, config->sample_rate);
    state.gain = 1.0;
    *agc = state;
    return AUDIO_OK;
}

void audio_agc_process_i16(AudioAgc *agc, i16 *samples, u32 frames) {
    if (!agc || !samples) return;
    for (u32 f = 0; f < frames; ++f) {
        i16 *frame = samples + (usize)f * agc->channels;
        double power = 0.0;
        for (u32 c = 0; c < agc->channels; ++c) {
            double x = (double)frame[c] / 32768.0;
            power += x * x;
        }
        agc->mean_square += agc->level_alpha * (power / agc->channels - agc->mean_square);
        /* silence has no level: log10(0) is -inf, below any gate */
        double level_db = agc->mean_square > 0.0 ? 10.0 * log10(agc->mean_square) : -HUGE_VAL;
        if (level_db >= agc->gate_db) {
            double desired = agc->target_db - level_db;
            if (desired > agc->max_gain_db) desired = agc->max_gain_db;
            if (desired < -agc->max_gain_db) desired = -agc->max_gain_db;
            double alpha = desired < agc->gain_db ? agc->attack_alpha : agc->release_alpha;
            double step = alpha * (desired - agc->gain_db);
            if (step != 0.0) {
                agc->gain_db += step;
                agc->gain = pow(10.0, agc->gain_db / 20.0);
            }
        }
        for (u32 c = 0; c < agc->channels; ++c) {
            double y = nearbyint((double)frame[c] * agc->gain);
            if (y > 32767.0) y = 32767.0;
            if (y < -32768.0) y = -32768.0;
            frame[c] = (i16)y;
        }
    }
}

f32 audio_agc_gain_db(const AudioAgc *agc) {
    return agc ? (f32)agc->gain_db : 0.0f;
}
