#pragma once
/* Closed-loop clock drift compensation: delay measurements feed
 * audio_drift_estimator, each update turns the residual delay slope into a
 * new audio_drift_resampler ratio, and the playback reference is resampled
 * with it (docs/superpowers/specs/2026-11-19-audio-drift-compensator-design.md).
 * Mono, owner thread; only create allocates. */

#include <audio/audio_drift_estimator.h>
#include <audio/audio_drift_resampler.h>

typedef struct {
    AudioDriftEstimatorConfig estimator;
    u32 min_samples;         /* 2..estimator.window_size */
    f32 max_correction_ppm;  /* 1..estimator.max_abs_drift_ppm */
    f32 gain;                /* (0, 1] */
    bool robust;             /* repeated-median slope instead of least squares */
} AudioDriftCompensatorConfig;

typedef struct AudioDriftCompensator AudioDriftCompensator;

/* INVALID for NULL or out-of-range config, OVERLOAD when memory runs out;
 * *out is written only on success. */
AudioResult audio_drift_compensator_create(const AudioDriftCompensatorConfig *config,
                                           AudioDriftCompensator **out);
void audio_drift_compensator_destroy(AudioDriftCompensator *comp); /* NULL is a no-op */
/* Ratio back to 1, estimator window and resampler position cleared; the
 * corrections and clamped counters are kept. */
void audio_drift_compensator_reset(AudioDriftCompensator *comp);
/* One delay measurement of the resampled reference against the capture:
 * positive when the capture trails the reference (audio_delay_estimator's
 * sign), frame_index counting capture frames. False when the estimator
 * refuses it (see audio_drift_estimator_push). The first measurement after
 * an update still covers samples resampled with the old ratio; skipping it
 * removes that bias. */
bool audio_drift_compensator_observe(AudioDriftCompensator *comp, u64 frame_index,
                                     double delay_frames, double correlation);
/* With at least min_samples measurements and a successful estimate, sets
 * ratio = ratio * (1 - gain * slope), limits |ratio - 1| to
 * max_correction_ppm, clears the estimator window and returns true.
 * Otherwise false and nothing changes. */
bool audio_drift_compensator_update(AudioDriftCompensator *comp);
double audio_drift_compensator_ratio(const AudioDriftCompensator *comp); /* 0 for NULL */
/* (1 - ratio) * 1e6: the drift the current ratio removes; 0 for NULL. */
double audio_drift_compensator_correction_ppm(const AudioDriftCompensator *comp);
u64 audio_drift_compensator_corrections(const AudioDriftCompensator *comp); /* 0 for NULL */
u64 audio_drift_compensator_clamped(const AudioDriftCompensator *comp);     /* 0 for NULL */
/* Safe output bound for a new input chunk; 0 for NULL or zero input. */
u32 audio_drift_compensator_output_capacity(const AudioDriftCompensator *comp,
                                            u32 input_frames);
/* Resamples the reference with the current ratio (linear interpolation).
 * Same contract as audio_drift_resampler_process_i16. */
AudioResult audio_drift_compensator_process_i16(AudioDriftCompensator *comp,
                                                const i16 *in, u32 input_frames,
                                                i16 *out, u32 out_capacity,
                                                u32 *out_frames);
