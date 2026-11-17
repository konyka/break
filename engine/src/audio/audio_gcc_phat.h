#pragma once
/* Generalized cross-correlation with phase transform for playback-to-capture
 * delay, using the existing real FFT (docs/design/audio_extended.md,
 * "Delay estimation"). Mono owner thread; only create allocates. */

#include <audio/audio.h>

#define AUDIO_GCC_PHAT_MAX_HISTORY 32768u

typedef struct {
    u32 max_delay_frames; /* 1..96000, lags 0..max are searched */
    u32 window_frames;    /* 16..96000; window + max_delay <= 32768 */
} AudioGccPhatConfig;

typedef struct AudioGccPhat AudioGccPhat;

/* INVALID for NULL, out-of-range values or a history requiring an FFT above
 * 65536; OVERLOAD on allocation failure. *out is written only on success. */
AudioResult audio_gcc_phat_create(const AudioGccPhatConfig *config, AudioGccPhat **out);
void audio_gcc_phat_destroy(AudioGccPhat *phat); /* NULL is a no-op */
void audio_gcc_phat_reset(AudioGccPhat *phat);
void audio_gcc_phat_push_i16(AudioGccPhat *phat, const i16 *reference,
                             const i16 *capture, u32 frames);
/* Writes the estimated delay in frames and the signed, non-normalized PHAT
 * peak. False with untouched outputs until history is full, or when the latest
 * capture window is silent or the entire reference history is silent. Interior
 * absolute peaks receive guarded parabolic
 * refinement; boundaries and invalid curves return the integer lag. */
bool audio_gcc_phat_estimate(AudioGccPhat *phat, double *delay_frames, double *peak);
