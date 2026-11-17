#include "audio_residual_echo_suppressor.h"

#include "audio_echo_canceller.h"

#include <math.h>
#include <string.h>

static bool residual_in_range(double value, double low, double high) {
    return value >= low && value <= high;
}

static double residual_alpha(double milliseconds, u32 sample_rate) {
    return 1.0 - exp(-1000.0 / (milliseconds * (double)sample_rate));
}

AudioResult audio_residual_echo_suppressor_init(AudioResidualEchoSuppressor *suppressor,
                                                const AudioResidualEchoSuppressorConfig *config) {
    if (!suppressor || !config ||
        !residual_in_range((double)config->sample_rate, 8000.0, 192000.0) ||
        !residual_in_range(config->reduction_db, 0.0, 80.0) ||
        !residual_in_range(config->margin_db, 0.0, 40.0) ||
        !residual_in_range(config->attack_ms, 0.1, 1000.0) ||
        !residual_in_range(config->release_ms, 1.0, 10000.0) ||
        !residual_in_range(config->path_rise_db_per_s, 0.1, 60.0) ||
        !residual_in_range(config->initial_path_db, AUDIO_RESIDUAL_ECHO_MIN_DB, 0.0) ||
        !residual_in_range(config->reference_gate_dbfs, -80.0, 0.0) ||
        !residual_in_range(config->hangover_ms, 0.0, 1000.0)) {
        return AUDIO_INVALID;
    }
    AudioResidualEchoSuppressor state;
    memset(&state, 0, sizeof(state));
    state.reduction_db = config->reduction_db;
    state.margin_db = config->margin_db;
    state.level_alpha = residual_alpha(10.0, config->sample_rate);
    state.attack_alpha = residual_alpha(config->attack_ms, config->sample_rate);
    state.release_alpha = residual_alpha(config->release_ms, config->sample_rate);
    state.path_rise = (double)config->path_rise_db_per_s / (double)config->sample_rate;
    state.initial_path_db = config->initial_path_db;
    state.reference_gate_power = pow(10.0, (double)config->reference_gate_dbfs / 10.0);
    state.hangover_frames =
        (u32)lrint((double)config->hangover_ms * (double)config->sample_rate / 1000.0);
    *suppressor = state;
    audio_residual_echo_suppressor_reset(suppressor);
    return AUDIO_OK;
}

void audio_residual_echo_suppressor_reset(AudioResidualEchoSuppressor *suppressor) {
    if (!suppressor) return;
    suppressor->reference_mean_square = 0.0;
    suppressor->error_mean_square = 0.0;
    suppressor->held_reference_power = 0.0;
    suppressor->path_db = suppressor->initial_path_db;
    suppressor->gain_db = 0.0;
    suppressor->gain = 1.0;
    suppressor->hold = 0u;
}

void audio_residual_echo_suppressor_process_i16(AudioResidualEchoSuppressor *suppressor,
                                                const i16 *reference, i16 *capture,
                                                u32 frames, bool near_end_active) {
    if (!suppressor || ((!reference || !capture) && frames != 0u)) return;
    for (u32 n = 0; n < frames; ++n) {
        const double x = (double)reference[n] / 32768.0;
        const double error = (double)capture[n] / 32768.0;
        suppressor->reference_mean_square +=
            suppressor->level_alpha * (x * x - suppressor->reference_mean_square);
        suppressor->error_mean_square +=
            suppressor->level_alpha * (error * error - suppressor->error_mean_square);

        bool reference_active = suppressor->reference_mean_square >= suppressor->reference_gate_power;
        if (reference_active) {
            suppressor->held_reference_power = suppressor->reference_mean_square;
            suppressor->hold = suppressor->hangover_frames;
        } else if (suppressor->hold > 0u) {
            --suppressor->hold;
            reference_active = true;
        }
        double target_db = 0.0;
        if (reference_active && !near_end_active) {
            const double error_power = suppressor->error_mean_square > 1e-12
                ? suppressor->error_mean_square : 1e-12;
            const double reference_power = suppressor->held_reference_power > 1e-12
                ? suppressor->held_reference_power : 1e-12;
            const double ratio_db = 10.0 * log10(error_power / reference_power);
            const double learned_db = ratio_db < 0.0 ? ratio_db : 0.0;
            suppressor->path_db += suppressor->path_rise;
            if (suppressor->path_db > learned_db) suppressor->path_db = learned_db;
            if (ratio_db <= suppressor->path_db + suppressor->margin_db) {
                target_db = -suppressor->reduction_db;
            }
        }
        const double alpha = target_db > suppressor->gain_db
            ? suppressor->attack_alpha : suppressor->release_alpha;
        suppressor->gain_db += alpha * (target_db - suppressor->gain_db);
        suppressor->gain = pow(10.0, suppressor->gain_db / 20.0);
        capture[n] = (i16)nearbyint((double)capture[n] * suppressor->gain);
    }
}

void audio_residual_echo_suppressor_process_with_aec(AudioResidualEchoSuppressor *suppressor,
                                                     AudioEchoCanceller *aec,
                                                     const i16 *reference, i16 *capture,
                                                     u32 frames) {
    if (!suppressor || !aec || frames == 0u || !reference || !capture) return;
    for (u32 n = 0; n < frames; ++n) {
        audio_echo_canceller_process_i16(aec, reference + n, capture + n, 1u);
        const bool near_end = audio_echo_canceller_near_end_active(aec);
        audio_residual_echo_suppressor_process_i16(suppressor, reference + n, capture + n,
                                                  1u, near_end);
    }
}

f32 audio_residual_echo_suppressor_gain_db(const AudioResidualEchoSuppressor *suppressor) {
    return suppressor ? (f32)suppressor->gain_db : 0.0f;
}

f32 audio_residual_echo_suppressor_path_db(const AudioResidualEchoSuppressor *suppressor) {
    return suppressor ? (f32)suppressor->path_db : (f32)AUDIO_RESIDUAL_ECHO_MIN_DB;
}
