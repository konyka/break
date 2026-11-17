#pragma once
/* Residual echo suppression after linear echo cancellation: reference/error
 * envelope ratios, reference hangover and caller-controlled near-end freeze
 * (docs/design/audio_extended.md, "Residual echo suppression"). Mono owner
 * thread, caller-owned state, no allocation. */

#include <audio/audio.h>

#define AUDIO_RESIDUAL_ECHO_MIN_DB (-120.0)

typedef struct {
    u32 sample_rate;         /* 8000..192000 */
    f32 reduction_db;        /* 0..80 */
    f32 margin_db;           /* 0..40, ratio allowance above the learned path */
    f32 attack_ms;           /* 0.1..1000, time constant while opening */
    f32 release_ms;          /* 1..10000, time constant while closing */
    f32 path_rise_db_per_s;  /* 0.1..60 */
    f32 initial_path_db;     /* -120..0, initial error/reference power ratio */
    f32 reference_gate_dbfs; /* -80..0 */
    f32 hangover_ms;         /* 0..1000, reference-active tail time */
} AudioResidualEchoSuppressorConfig;

typedef struct {
    double reduction_db;
    double margin_db;
    double level_alpha;
    double attack_alpha;
    double release_alpha;
    double path_rise;
    double initial_path_db;
    double reference_gate_power;
    double reference_mean_square;
    double error_mean_square;
    double held_reference_power;
    double path_db;
    double gain_db;
    double gain;
    u32 hangover_frames;
    u32 hold;
} AudioResidualEchoSuppressor;

/* INVALID for NULL or an out-of-range/NaN config; *suppressor is written only
 * on success. */
AudioResult audio_residual_echo_suppressor_init(AudioResidualEchoSuppressor *suppressor,
                                                const AudioResidualEchoSuppressorConfig *config);
void audio_residual_echo_suppressor_reset(AudioResidualEchoSuppressor *suppressor);
/* `capture` is the AEC output, modified in place. `reference` is the aligned
 * playback signal. near_end_active freezes the path and opens the gain. NULL
 * signal pointers are accepted only when frames is zero. */
void audio_residual_echo_suppressor_process_i16(AudioResidualEchoSuppressor *suppressor,
                                                const i16 *reference, i16 *capture,
                                                u32 frames, bool near_end_active);
typedef struct AudioEchoCanceller AudioEchoCanceller;
/* Per frame: AEC, its near-end state, then residual suppression. This function
 * performs AEC itself; do not also process the same capture with the AEC. */
void audio_residual_echo_suppressor_process_with_aec(AudioResidualEchoSuppressor *suppressor,
                                                     AudioEchoCanceller *aec,
                                                     const i16 *reference, i16 *capture,
                                                     u32 frames);
f32 audio_residual_echo_suppressor_gain_db(const AudioResidualEchoSuppressor *suppressor);
f32 audio_residual_echo_suppressor_path_db(const AudioResidualEchoSuppressor *suppressor);
