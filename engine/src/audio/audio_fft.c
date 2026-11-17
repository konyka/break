#include "audio_fft.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

static const f64 kPi = 3.14159265358979323846;

/* A real transform of `size` runs one complex transform of m = size / 2 on
 * z[t] = x[2t] + i x[2t + 1], then splits the even and odd spectra with the
 * size-point twiddles. */
struct AudioFft {
    u32 size;
    u32 half;          /* m */
    u32 *bitrev;       /* m entries */
    f64 *cos_table;    /* size / 2 entries: cos(2 pi k / size) */
    f64 *sin_table;    /* size / 2 entries: sin(2 pi k / size) */
};

AudioResult audio_fft_create(u32 size, AudioFft **out) {
    if (!out || size < AUDIO_FFT_MIN_SIZE || size > AUDIO_FFT_MAX_SIZE ||
        (size & (size - 1u)) != 0u) {
        return AUDIO_INVALID;
    }
    AudioFft *fft = (AudioFft *)calloc(1u, sizeof(*fft));
    if (!fft) return AUDIO_OVERLOAD;
    fft->size = size;
    fft->half = size / 2u;
    fft->bitrev = (u32 *)malloc(sizeof(u32) * fft->half);
    fft->cos_table = (f64 *)malloc(sizeof(f64) * fft->half);
    fft->sin_table = (f64 *)malloc(sizeof(f64) * fft->half);
    if (!fft->bitrev || !fft->cos_table || !fft->sin_table) {
        audio_fft_destroy(fft);
        return AUDIO_OVERLOAD;
    }
    u32 bits = 0u;
    while ((1u << bits) < fft->half) ++bits;
    for (u32 i = 0; i < fft->half; ++i) {
        u32 r = 0u;
        for (u32 b = 0; b < bits; ++b) r |= ((i >> b) & 1u) << (bits - 1u - b);
        fft->bitrev[i] = r;
    }
    for (u32 k = 0; k < fft->half; ++k) {
        f64 a = 2.0 * kPi * (f64)k / (f64)size;
        fft->cos_table[k] = cos(a);
        fft->sin_table[k] = sin(a);
    }
    *out = fft;
    return AUDIO_OK;
}

void audio_fft_destroy(AudioFft *fft) {
    if (!fft) return;
    free(fft->bitrev);
    free(fft->cos_table);
    free(fft->sin_table);
    free(fft);
}

u32 audio_fft_size(const AudioFft *fft) {
    return fft ? fft->size : 0u;
}

/* In-place, unscaled complex FFT of length m = fft->half on (re, im), already
 * in bit-reversed order: sign -1 selects forward, +1 selects inverse. The
 * twiddle for a stage of length len at position j is table[j * size / len]. */
static void fft_complex(const AudioFft *fft, f64 *re, f64 *im, f64 sign) {
    const u32 m = fft->half;
    for (u32 len = 2u; len <= m; len <<= 1u) {
        const u32 step = fft->size / len;
        const u32 h = len / 2u;
        for (u32 start = 0; start < m; start += len) {
            for (u32 j = 0; j < h; ++j) {
                f64 wr = fft->cos_table[j * step];
                f64 wi = sign * fft->sin_table[j * step];
                u32 a = start + j, b = a + h;
                f64 tr = re[b] * wr - im[b] * wi;
                f64 ti = re[b] * wi + im[b] * wr;
                re[b] = re[a] - tr;
                im[b] = im[a] - ti;
                re[a] += tr;
                im[a] += ti;
            }
        }
    }
}

void audio_fft_forward(const AudioFft *fft, const f64 *x, f64 *re, f64 *im) {
    if (!fft || !x || !re || !im) return;
    const u32 m = fft->half;
    /* z[t] = x[2t] + i x[2t+1], bit-reversed into re/im[0..m) */
    for (u32 t = 0; t < m; ++t) {
        u32 r = fft->bitrev[t];
        re[r] = x[2u * t];
        im[r] = x[2u * t + 1u];
    }
    fft_complex(fft, re, im, -1.0);
    /* X[k] = E[k] + W^k O[k] with E = (Z[k] + conj Z[m-k]) / 2 and
     * O = (Z[k] - conj Z[m-k]) / 2i, W = exp(-2 pi i / size). Bins k and
     * m - k are computed together from Z[k] and Z[m - k]. */
    f64 z0r = re[0], z0i = im[0];
    re[0] = z0r + z0i;
    im[0] = 0.0;
    re[m] = z0r - z0i;
    im[m] = 0.0;
    for (u32 k = 1u; k <= m / 2u; ++k) {
        u32 j = m - k;
        f64 ar = re[k], ai = im[k], br = re[j], bi = im[j];
        f64 er = 0.5 * (ar + br), ei = 0.5 * (ai - bi);
        f64 or_ = 0.5 * (ai + bi), oi = -0.5 * (ar - br);
        f64 wr = fft->cos_table[k], wi = -fft->sin_table[k];
        f64 tr = or_ * wr - oi * wi, ti = or_ * wi + oi * wr;
        re[k] = er + tr;
        im[k] = ei + ti;
        /* X[m - k] = conj(E[k]) - conj(W^k O[k]) */
        re[j] = er - tr;
        im[j] = -(ei - ti);
    }
}

void audio_fft_inverse(const AudioFft *fft, f64 *re, f64 *im, f64 *x) {
    if (!fft || !re || !im || !x) return;
    const u32 m = fft->half;
    /* rebuild Z[k] = E[k] + i O[k] from X[k] and X[m - k], k = 0..m-1:
     * E = (X[k] + conj X[m-k]) / 2, O = (X[k] - conj X[m-k]) W^-k / 2 */
    f64 x0 = re[0], xm = re[m];
    re[0] = 0.5 * (x0 + xm);
    im[0] = 0.5 * (x0 - xm);
    for (u32 k = 1u; k <= m / 2u; ++k) {
        u32 j = m - k;
        f64 ar = re[k], ai = im[k], br = re[j], bi = im[j];
        f64 er = 0.5 * (ar + br), ei = 0.5 * (ai - bi);
        f64 dr = 0.5 * (ar - br), di = 0.5 * (ai + bi);
        f64 wr = fft->cos_table[k], wi = fft->sin_table[k];
        f64 or_ = dr * wr - di * wi, oi = dr * wi + di * wr;
        /* Z[k] = E + i O; Z[m - k] = conj(E) + i conj(O) */
        re[k] = er - oi;
        im[k] = ei + or_;
        re[j] = er + oi;
        im[j] = -ei + or_;
    }
    /* Bit-reverse in place, run the inverse complex FFT, then scale by 1 / m
     * (the real transform's 1 / size times 2). */
    for (u32 t = 0; t < m; ++t) {
        u32 r = fft->bitrev[t];
        if (r > t) {
            f64 sr = re[t], si = im[t];
            re[t] = re[r];
            im[t] = im[r];
            re[r] = sr;
            im[r] = si;
        }
    }
    fft_complex(fft, re, im, 1.0);
    const f64 scale = 1.0 / (f64)m;
    for (u32 t = 0; t < m; ++t) {
        x[2u * t] = re[t] * scale;
        x[2u * t + 1u] = im[t] * scale;
    }
}

bool audio_fft_hann(f64 *w, u32 size) {
    if (!w || size == 0u || (size & 1u) != 0u) return false;
    for (u32 t = 0; t < size; ++t) {
        w[t] = 0.5 - 0.5 * cos(2.0 * kPi * (f64)t / (f64)size);
    }
    return true;
}
