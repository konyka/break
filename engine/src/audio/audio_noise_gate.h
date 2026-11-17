#pragma once
/* Noise reduction for captured voice in the time domain: a downward
 * expander that learns the noise floor and attenuates frames that stay near
 * it (docs/design/audio_extended.md, "Noise gate"). Owner thread only; no
 * allocation. */

#include <audio/audio.h>

#define AUDIO_NOISE_GATE_MIN_DBFS (-120.0)

typedef struct {
    u32 sample_rate;         /* 8000..192000 */
    u32 channels;            /* 1 or 2 */
    f32 threshold_db;        /* 3..40, how far above the floor opens the gate */
    f32 reduction_db;        /* 0..80, attenuation while closed */
    f32 attack_ms;           /* 0.1..1000, time constant while opening */
    f32 release_ms;          /* 1..10000, time constant while closing */
    f32 floor_rise_db_per_s; /* 0.1..60, how fast the floor follows a louder level */
    f32 initial_floor_dbfs;  /* -120..0 */
} AudioNoiseGateConfig;

typedef struct {
    u32 channels;
    double threshold_db;
    double reduction_db;
    double level_alpha; /* one-pole coefficient of the mean square, 10 ms */
    double attack_alpha;
    double release_alpha;
    double floor_rise;  /* dB per frame */
    double mean_square;
    double floor_db;
    double gain_db;
    double gain;        /* 10^(gain_db / 20) */
} AudioNoiseGate;

/* INVALID for a NULL argument or a config out of range; *gate is written
 * only on success. The gate starts open (0 dB) with the level detector
 * and the floor at initial_floor_dbfs. */
AudioResult audio_noise_gate_init(AudioNoiseGate *gate, const AudioNoiseGateConfig *config);
/* In place, `frames` interleaved frames. */
void audio_noise_gate_process_i16(AudioNoiseGate *gate, i16 *samples, u32 frames);
f32 audio_noise_gate_gain_db(const AudioNoiseGate *gate);
f32 audio_noise_gate_floor_dbfs(const AudioNoiseGate *gate);
