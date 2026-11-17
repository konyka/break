#pragma once
/* Radix-2 FFT for audio analysis: a complex transform in place, a real
 * forward/inverse pair of size n through one complex transform of n / 2,
 * and the periodic Hann window (docs/design/audio_extended.md, "FFT").
 * Plans hold the twiddle and bit-reversal tables; create allocates,
 * everything else does not. A plan is read-only after create and may be
 * shared by threads that bring their own buffers. */

#include <audio/audio.h>

#define AUDIO_FFT_MIN_SIZE 4u
#define AUDIO_FFT_MAX_SIZE 65536u

typedef struct AudioFft AudioFft;

/* `size` is a power of two in MIN_SIZE..MAX_SIZE, the number of real
 * samples. INVALID otherwise, OVERLOAD when memory runs out; *out is written
 * only on success. */
AudioResult audio_fft_create(u32 size, AudioFft **out);
void audio_fft_destroy(AudioFft *fft); /* NULL is a no-op */
u32 audio_fft_size(const AudioFft *fft); /* 0 for NULL */

/* Real input x[0..size) to bins 0..size/2: re[k] + i im[k] =
 * sum x[t] exp(-2 pi i k t / size). im[0] and im[size/2] are 0. `re` and `im`
 * hold size/2 + 1 values each; x is not modified. The buffers x, re and im
 * must not overlap. */
void audio_fft_forward(const AudioFft *fft, const f64 *x, f64 *re, f64 *im);
/* The inverse of forward: x[t] = (1 / size) sum over all size bins, with
 * bins above size/2 the conjugates of the ones below. im[0] and
 * im[size/2] are ignored. `re` and `im` are used as scratch and left
 * unspecified. The buffers re, im and x must not overlap. */
void audio_fft_inverse(const AudioFft *fft, f64 *re, f64 *im, f64 *x);

/* w[t] = 0.5 - 0.5 cos(2 pi t / size), t in [0, size). With a hop of size/2
 * the shifted windows sum to 1. False for NULL, size 0 or an odd size. */
bool audio_fft_hann(f64 *w, u32 size);
