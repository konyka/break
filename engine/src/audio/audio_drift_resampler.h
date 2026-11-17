#pragma once
/* Streaming mono resampling for clock-drift compensation, with a dynamic
 * input-frames-per-output-frame ratio (docs/design/audio_extended.md,
 * "Clock drift compensation"). Caller-owned state, no allocation. */

#include <audio/audio.h>

typedef struct {
    double ratio;
    double next_output;
    u64 next_input;
    i16 previous;
    bool sinc;
    i16 history[32];
} AudioDriftResampler;

/* Ratio is finite and in [0.1,10]. INVALID for NULL/out-of-range values. */
AudioResult audio_drift_resampler_init(AudioDriftResampler *resampler, double ratio);
/* Preserve the current ratio and interpolation mode; reset position/history. */
void audio_drift_resampler_reset(AudioDriftResampler *resampler);
AudioResult audio_drift_resampler_set_ratio(AudioDriftResampler *resampler, double ratio);
double audio_drift_resampler_ratio(const AudioDriftResampler *resampler); /* 0 for NULL */
/* Sinc mode uses a causal 16-tap kernel and eight input frames of lookahead.
 * Mode changes apply to the next processing call. INVALID for NULL. */
AudioResult audio_drift_resampler_set_sinc(AudioDriftResampler *resampler, bool enabled);
bool audio_drift_resampler_sinc(const AudioDriftResampler *resampler); /* false for NULL */
u32 audio_drift_resampler_sinc_extra_delay(const AudioDriftResampler *resampler);
/* Safe upper bound for a new input chunk, or 0 for NULL, zero input or overflow. */
u32 audio_drift_resampler_output_capacity(const AudioDriftResampler *resampler,
                                          u32 input_frames);
/* Consume all input and write the actual output count only on success. Input
 * and output buffers must not overlap. Capacity is checked before any state
 * change. Zero input is a valid no-op. */
AudioResult audio_drift_resampler_process_i16(AudioDriftResampler *resampler,
                                              const i16 *in, u32 input_frames,
                                              i16 *out, u32 out_capacity,
                                              u32 *out_frames);
