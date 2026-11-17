#include "audio_echo_canceller.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

struct AudioEchoCanceller {
    u32 taps;
    double step_size;
    double double_talk_threshold;
    u32 hangover_frames;
    u32 hold;
    u32 cursor;
    u64 energy;
    bool near_end_active;
    double *weights;
    double *history;
    i16 *history_i16;
};

/* false for NaN as well as for a value outside [lo, hi] */
static bool aec_in_range(double x, double lo, double hi) {
    return x >= lo && x <= hi;
}

AudioResult audio_echo_canceller_create(const AudioEchoCancellerConfig *config,
                                        AudioEchoCanceller **out) {
    if (!config || !out || !aec_in_range((double)config->sample_rate, 8000.0, 192000.0) ||
        config->taps < 1u || config->taps > AUDIO_ECHO_CANCELLER_MAX_TAPS ||
        !aec_in_range(config->step_size, 0.001, 1.0) ||
        !aec_in_range(config->double_talk_threshold, 0.0, 1.0) ||
        !aec_in_range(config->hangover_ms, 0.0, 1000.0)) {
        return AUDIO_INVALID;
    }
    AudioEchoCanceller *aec = (AudioEchoCanceller *)calloc(1u, sizeof(*aec));
    if (!aec) return AUDIO_OVERLOAD;
    aec->taps = config->taps;
    aec->step_size = config->step_size;
    aec->double_talk_threshold = config->double_talk_threshold;
    aec->hangover_frames =
        (u32)lrint((double)config->hangover_ms * (double)config->sample_rate / 1000.0);
    aec->weights = (double *)calloc(config->taps, sizeof(double));
    aec->history = (double *)calloc(2u * (usize)config->taps, sizeof(double));
    aec->history_i16 = (i16 *)calloc(config->taps, sizeof(i16));
    if (!aec->weights || !aec->history || !aec->history_i16) {
        audio_echo_canceller_destroy(aec);
        return AUDIO_OVERLOAD;
    }
    *out = aec;
    return AUDIO_OK;
}

void audio_echo_canceller_destroy(AudioEchoCanceller *aec) {
    if (!aec) return;
    free(aec->weights);
    free(aec->history);
    free(aec->history_i16);
    free(aec);
}

void audio_echo_canceller_reset(AudioEchoCanceller *aec) {
    if (!aec) return;
    memset(aec->weights, 0, sizeof(double) * aec->taps);
    memset(aec->history, 0, sizeof(double) * 2u * aec->taps);
    memset(aec->history_i16, 0, sizeof(i16) * aec->taps);
    aec->hold = 0u;
    aec->cursor = 0u;
    aec->energy = 0u;
    aec->near_end_active = false;
}

void audio_echo_canceller_process_i16(AudioEchoCanceller *aec, const i16 *reference,
                                      i16 *capture, u32 frames) {
    if (!aec || !reference || !capture) return;
    const u32 taps = aec->taps;
    for (u32 n = 0; n < frames; ++n) {
        /* the oldest sample leaves the window, the newest enters at k = 0 */
        u32 at = aec->cursor == 0u ? taps - 1u : aec->cursor - 1u;
        i32 old = aec->history_i16[at];
        i32 now = reference[n];
        aec->energy -= (u64)(old * old);
        aec->energy += (u64)(now * now);
        double x_now = (double)now / 32768.0;
        aec->history[at] = x_now;
        aec->history[at + taps] = x_now;
        aec->history_i16[at] = (i16)now;
        aec->cursor = at;

        const double *x = aec->history + at;
        double y = 0.0, peak = 0.0;
        for (u32 k = 0; k < taps; ++k) {
            y += aec->weights[k] * x[k];
            if (fabs(x[k]) > peak) peak = fabs(x[k]);
        }
        double d = (double)capture[n] / 32768.0;
        double e = d - y;
        double v = nearbyint(e * 32768.0);
        if (v > 32767.0) v = 32767.0;
        if (v < -32768.0) v = -32768.0;
        capture[n] = (i16)v;

        /* Geigel: a near side louder than the far side's recent peak; silence
         * on both sides is not double talk */
        if (aec->double_talk_threshold > 0.0 && fabs(d) > aec->double_talk_threshold * peak) {
            aec->hold = aec->hangover_frames;
            aec->near_end_active = true;
            continue;
        }
        if (aec->hold > 0u) {
            --aec->hold;
            aec->near_end_active = true;
            continue;
        }
        aec->near_end_active = false;
        double g = aec->step_size * e /
                   ((double)aec->energy / 1073741824.0 + (double)taps * 1e-6);
        for (u32 k = 0; k < taps; ++k) aec->weights[k] += g * x[k];
    }
}

double audio_echo_canceller_weight(const AudioEchoCanceller *aec, u32 k) {
    return aec && k < aec->taps ? aec->weights[k] : 0.0;
}

bool audio_echo_canceller_near_end_active(const AudioEchoCanceller *aec) {
    return aec ? aec->near_end_active : false;
}
