#pragma once
/* Automatic gain control for captured voice: brings 16-bit frames towards
 * a target level, holds the gain below a noise gate and never wraps
 * (docs/design/audio_extended.md, "Automatic gain control"). Owner thread
 * only; no allocation. */

#include <audio/audio.h>

typedef struct {
    u32 sample_rate; /* 8000..192000 */
    u32 channels;    /* 1 or 2 */
    f32 target_dbfs; /* -60..0, the RMS level to reach */
    f32 max_gain_db; /* 0..60, the most the gain boosts or cuts */
    f32 attack_ms;   /* 0.1..1000, time constant while the gain falls */
    f32 release_ms;  /* 1..10000, time constant while the gain rises */
    f32 gate_dbfs;   /* -120..0 and below target_dbfs; below it the gain holds */
} AudioAgcConfig;

/* Double precision: near the settled gain the per-frame steps are far
 * below an f32 ulp. */
typedef struct {
    u32 channels;
    double target_db;
    double max_gain_db;
    double gate_db;
    double level_alpha;   /* one-pole coefficient of the mean square, 10 ms */
    double attack_alpha;
    double release_alpha;
    double mean_square;
    double gain_db;
    double gain;          /* 10^(gain_db / 20) */
} AudioAgc;

/* INVALID for a NULL argument or a config out of range; *agc is written
 * only on success. The gain starts at 0 dB. */
AudioResult audio_agc_init(AudioAgc *agc, const AudioAgcConfig *config);
/* In place, `frames` interleaved frames. */
void audio_agc_process_i16(AudioAgc *agc, i16 *samples, u32 frames);
f32 audio_agc_gain_db(const AudioAgc *agc);
