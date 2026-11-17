#include "audio_noise_gate.h"

#include <math.h>
#include <string.h>

/* false for NaN as well as for a value outside [lo, hi] */
static bool gate_in_range(double x, double lo, double hi) {
    return x >= lo && x <= hi;
}

/* one-pole coefficient for a time constant of `ms` at `rate` frames/s */
static double gate_alpha(double ms, u32 rate) {
    return 1.0 - exp(-1000.0 / (ms * (double)rate));
}

AudioResult audio_noise_gate_init(AudioNoiseGate *gate, const AudioNoiseGateConfig *config) {
    if (!gate || !config || !gate_in_range((double)config->sample_rate, 8000.0, 192000.0) ||
        (config->channels != 1u && config->channels != 2u) ||
        !gate_in_range(config->threshold_db, 3.0, 40.0) ||
        !gate_in_range(config->reduction_db, 0.0, 80.0) ||
        !gate_in_range(config->attack_ms, 0.1, 1000.0) ||
        !gate_in_range(config->release_ms, 1.0, 10000.0) ||
        !gate_in_range(config->floor_rise_db_per_s, 0.1, 60.0) ||
        !gate_in_range(config->initial_floor_dbfs, AUDIO_NOISE_GATE_MIN_DBFS, 0.0)) {
        return AUDIO_INVALID;
    }
    AudioNoiseGate state;
    memset(&state, 0, sizeof(state));
    state.channels = config->channels;
    state.threshold_db = config->threshold_db;
    state.reduction_db = config->reduction_db;
    state.level_alpha = gate_alpha(10.0, config->sample_rate);
    state.attack_alpha = gate_alpha(config->attack_ms, config->sample_rate);
    state.release_alpha = gate_alpha(config->release_ms, config->sample_rate);
    state.floor_rise = (double)config->floor_rise_db_per_s / (double)config->sample_rate;
    state.mean_square = pow(10.0, (double)config->initial_floor_dbfs / 10.0);
    state.floor_db = config->initial_floor_dbfs;
    state.gain = 1.0;
    *gate = state;
    return AUDIO_OK;
}

void audio_noise_gate_process_i16(AudioNoiseGate *gate, i16 *samples, u32 frames) {
    if (!gate || !samples) return;
    for (u32 f = 0; f < frames; ++f) {
        i16 *frame = samples + (usize)f * gate->channels;
        double power = 0.0;
        for (u32 c = 0; c < gate->channels; ++c) {
            double x = (double)frame[c] / 32768.0;
            power += x * x;
        }
        gate->mean_square += gate->level_alpha * (power / gate->channels - gate->mean_square);
        double level_db = gate->mean_square > 0.0 ? 10.0 * log10(gate->mean_square)
                                                  : AUDIO_NOISE_GATE_MIN_DBFS;
        if (level_db < AUDIO_NOISE_GATE_MIN_DBFS) level_db = AUDIO_NOISE_GATE_MIN_DBFS;
        /* the floor falls to a quieter level at once and rises slowly */
        double risen = gate->floor_db + gate->floor_rise;
        gate->floor_db = risen < level_db ? risen : level_db;
        double target = level_db >= gate->floor_db + gate->threshold_db ? 0.0 : -gate->reduction_db;
        double alpha = target > gate->gain_db ? gate->attack_alpha : gate->release_alpha;
        gate->gain_db += alpha * (target - gate->gain_db);
        gate->gain = pow(10.0, gate->gain_db / 20.0);
        /* gain_db stays in [-reduction, 0], so the gain never exceeds 1 */
        for (u32 c = 0; c < gate->channels; ++c) {
            frame[c] = (i16)nearbyint((double)frame[c] * gate->gain);
        }
    }
}

f32 audio_noise_gate_gain_db(const AudioNoiseGate *gate) {
    return gate ? (f32)gate->gain_db : 0.0f;
}

f32 audio_noise_gate_floor_dbfs(const AudioNoiseGate *gate) {
    return gate ? (f32)gate->floor_db : (f32)AUDIO_NOISE_GATE_MIN_DBFS;
}
