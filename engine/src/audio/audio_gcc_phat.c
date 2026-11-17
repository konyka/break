#include "audio_gcc_phat.h"

#include "audio_fft.h"
#include "audio_delay_estimator.h"
#include "audio_gcc_phat_internal.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

struct AudioGccPhat {
    u32 max_delay;
    u32 window;
    u32 history;
    u32 pos;
    u64 pushed;
    u32 fft_size;
    u32 bins;
    AudioFft *fft;
    i16 *reference;
    i16 *capture;
    f64 *re;
    f64 *im;
    f64 *capture_re;
    f64 *capture_im;
    f64 *time;
};

u32 audio_gcc_phat_fft_size(u32 history) {
    u32 size = 1u;
    while (size < 2u * history) size <<= 1u;
    return size;
}

void audio_gcc_phat_select_peak(const f64 *values, u32 count,
                                u32 *best_lag, double *peak) {
    *best_lag = 0u;
    *peak = values[0];
    for (u32 i = 1u; i < count; ++i) {
        if (fabs(values[i]) > fabs(*peak)) {
            *best_lag = i;
            *peak = values[i];
        }
    }
}

AudioResult audio_gcc_phat_create(const AudioGccPhatConfig *config, AudioGccPhat **out) {
    if (!config || !out || config->max_delay_frames < 1u ||
        config->max_delay_frames > AUDIO_DELAY_ESTIMATOR_MAX_DELAY ||
        config->window_frames < AUDIO_DELAY_ESTIMATOR_MIN_WINDOW ||
        config->window_frames > AUDIO_DELAY_ESTIMATOR_MAX_WINDOW ||
        config->window_frames + config->max_delay_frames > AUDIO_GCC_PHAT_MAX_HISTORY) {
        return AUDIO_INVALID;
    }
    AudioGccPhat *phat = (AudioGccPhat *)calloc(1u, sizeof(*phat));
    if (!phat) return AUDIO_OVERLOAD;
    phat->max_delay = config->max_delay_frames;
    phat->window = config->window_frames;
    phat->history = config->window_frames + config->max_delay_frames;
    phat->fft_size = audio_gcc_phat_fft_size(phat->history);
    phat->bins = phat->fft_size / 2u + 1u;
    AudioResult result = audio_fft_create(phat->fft_size, &phat->fft);
    if (result != AUDIO_OK) {
        free(phat);
        return result;
    }
    phat->reference = (i16 *)calloc(2u * (usize)phat->history, sizeof(i16));
    phat->capture = (i16 *)calloc(2u * (usize)phat->history, sizeof(i16));
    phat->re = (f64 *)calloc(phat->bins, sizeof(f64));
    phat->im = (f64 *)calloc(phat->bins, sizeof(f64));
    phat->capture_re = (f64 *)calloc(phat->bins, sizeof(f64));
    phat->capture_im = (f64 *)calloc(phat->bins, sizeof(f64));
    phat->time = (f64 *)calloc(phat->fft_size, sizeof(f64));
    if (!phat->reference || !phat->capture || !phat->re || !phat->im ||
        !phat->capture_re || !phat->capture_im || !phat->time) {
        audio_gcc_phat_destroy(phat);
        return AUDIO_OVERLOAD;
    }
    *out = phat;
    return AUDIO_OK;
}

void audio_gcc_phat_destroy(AudioGccPhat *phat) {
    if (!phat) return;
    audio_fft_destroy(phat->fft);
    free(phat->reference);
    free(phat->capture);
    free(phat->re);
    free(phat->im);
    free(phat->capture_re);
    free(phat->capture_im);
    free(phat->time);
    free(phat);
}

void audio_gcc_phat_reset(AudioGccPhat *phat) {
    if (!phat) return;
    phat->pos = 0u;
    phat->pushed = 0u;
}

void audio_gcc_phat_push_i16(AudioGccPhat *phat, const i16 *reference,
                             const i16 *capture, u32 frames) {
    if (!phat || !reference || !capture) return;
    for (u32 n = 0; n < frames; ++n) {
        phat->reference[phat->pos] = reference[n];
        phat->reference[phat->pos + phat->history] = reference[n];
        phat->capture[phat->pos] = capture[n];
        phat->capture[phat->pos + phat->history] = capture[n];
        phat->pos = phat->pos + 1u == phat->history ? 0u : phat->pos + 1u;
    }
    phat->pushed += frames;
}

bool audio_gcc_phat_estimate(AudioGccPhat *phat, double *delay_frames, double *peak) {
    if (!phat || !delay_frames || !peak || phat->pushed < phat->history) return false;
    const i16 *reference = phat->reference + phat->pos;
    const i16 *capture = phat->capture + phat->pos;
    i64 cc = 0;
    for (u32 i = 0; i < phat->window; ++i) {
        const i16 value = capture[phat->max_delay + i];
        cc += (i64)value * value;
    }
    if (cc == 0) return false;
    bool reference_nonzero = false;
    for (u32 i = 0; i < phat->history; ++i) {
        if (reference[i] != 0) {
            reference_nonzero = true;
            break;
        }
    }
    if (!reference_nonzero) return false;

    memset(phat->time, 0, sizeof(f64) * phat->fft_size);
    for (u32 i = 0; i < phat->history; ++i) phat->time[i] = (double)reference[i] / 32768.0;
    audio_fft_forward(phat->fft, phat->time, phat->re, phat->im);
    memset(phat->time, 0, sizeof(f64) * phat->fft_size);
    for (u32 i = 0; i < phat->history; ++i) phat->time[i] = (double)capture[i] / 32768.0;
    audio_fft_forward(phat->fft, phat->time, phat->capture_re, phat->capture_im);
    for (u32 k = 0; k < phat->bins; ++k) {
        const double cr = phat->re[k] * phat->capture_re[k] +
                          phat->im[k] * phat->capture_im[k];
        const double ci = phat->re[k] * phat->capture_im[k] -
                          phat->im[k] * phat->capture_re[k];
        const double magnitude = sqrt(cr * cr + ci * ci);
        if (magnitude > 1e-12) {
            phat->re[k] = cr / magnitude;
            phat->im[k] = ci / magnitude;
        } else {
            phat->re[k] = 0.0;
            phat->im[k] = 0.0;
        }
    }
    audio_fft_inverse(phat->fft, phat->re, phat->im, phat->time);

    u32 best_lag = 0u;
    double best = 0.0;
    audio_gcc_phat_select_peak(phat->time, phat->max_delay + 1u, &best_lag, &best);
    double result = best_lag;
    if (best_lag > 0u && best_lag < phat->max_delay) {
        const double a = fabs(phat->time[best_lag - 1u]);
        const double b = fabs(best);
        const double c = fabs(phat->time[best_lag + 1u]);
        const double denominator = a - 2.0 * b + c;
        if (denominator < 0.0) {
            const double offset = 0.5 * (a - c) / denominator;
            if (isfinite(offset) && fabs(offset) <= 0.5) result += offset;
        }
    }
    *delay_frames = result;
    *peak = best;
    return true;
}
