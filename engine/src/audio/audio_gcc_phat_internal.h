#pragma once
/* Internal pure contracts shared by the implementation and its focused tests;
 * not part of the public audio API. */

#include <audio/audio.h>

/* Smallest power of two >= 2 * history; valid histories are <= 32768. */
u32 audio_gcc_phat_fft_size(u32 history);
/* Select the largest absolute value, keeping its sign and the smaller index
 * on an exact tie. Inputs are valid non-NULL arrays with count > 0. */
void audio_gcc_phat_select_peak(const f64 *values, u32 count,
                                u32 *best_lag, double *peak);
