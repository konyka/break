#include "audio_noise_suppressor.h"

#include "audio_fft.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define AUDIO_NOISE_SUPPRESSOR_MIN_POWER 1e-12

struct AudioNoiseSuppressor {
    AudioFft *fft;
    u32 frame_size;
    u32 hop;
    u32 bins;
    u32 filled;
    u32 primed;
    u32 output_head;
    u32 output_count;
    f64 initial_noise;
    f64 noise_alpha;
    f64 noise_rise;
    f64 gain_floor;
    f64 power_scale;
    f64 *window;
    f64 *input;
    f64 *time;
    f64 *re;
    f64 *im;
    f64 *noise;
    f64 *smooth;
    f64 *overlap;
    f64 *output;
};

static bool noise_config_valid(const AudioNoiseSuppressorConfig *config) {
    if (!config || config->sample_rate < 8000u || config->sample_rate > 192000u ||
        config->frame_size < AUDIO_NOISE_SUPPRESSOR_MIN_FRAME_SIZE ||
        config->frame_size > AUDIO_NOISE_SUPPRESSOR_MAX_FRAME_SIZE ||
        (config->frame_size & (config->frame_size - 1u)) != 0u) {
        return false;
    }
    return isfinite(config->max_attenuation_db) && config->max_attenuation_db >= 0.0f &&
           config->max_attenuation_db <= 80.0f &&
           isfinite(config->noise_rise_db_per_s) && config->noise_rise_db_per_s >= 0.1f &&
           config->noise_rise_db_per_s <= 60.0f &&
           isfinite(config->initial_noise_dbfs) && config->initial_noise_dbfs >= -120.0f &&
           config->initial_noise_dbfs <= 0.0f;
}

AudioResult audio_noise_suppressor_create(const AudioNoiseSuppressorConfig *config,
                                          AudioNoiseSuppressor **out) {
    if (!out || !noise_config_valid(config)) return AUDIO_INVALID;
    AudioNoiseSuppressor *suppressor = (AudioNoiseSuppressor *)calloc(1u, sizeof(*suppressor));
    if (!suppressor) return AUDIO_OVERLOAD;
    suppressor->frame_size = config->frame_size;
    suppressor->hop = config->frame_size / 2u;
    suppressor->bins = suppressor->hop + 1u;
    const AudioResult fft_result = audio_fft_create(config->frame_size, &suppressor->fft);
    if (fft_result != AUDIO_OK) {
        free(suppressor);
        return fft_result;
    }
    const u32 size = suppressor->frame_size;
    const u32 hop = suppressor->hop;
    const u32 bins = suppressor->bins;
    suppressor->window = (f64 *)calloc(size, sizeof(f64));
    suppressor->input = (f64 *)calloc(size, sizeof(f64));
    suppressor->time = (f64 *)calloc(size, sizeof(f64));
    suppressor->re = (f64 *)calloc(bins, sizeof(f64));
    suppressor->im = (f64 *)calloc(bins, sizeof(f64));
    suppressor->noise = (f64 *)calloc(bins, sizeof(f64));
    suppressor->smooth = (f64 *)calloc(bins, sizeof(f64));
    suppressor->overlap = (f64 *)calloc(hop, sizeof(f64));
    suppressor->output = (f64 *)calloc(size, sizeof(f64));
    if (!suppressor->window || !suppressor->input || !suppressor->time ||
        !suppressor->re || !suppressor->im || !suppressor->noise || !suppressor->smooth ||
        !suppressor->overlap || !suppressor->output) {
        audio_noise_suppressor_destroy(suppressor);
        return AUDIO_OVERLOAD;
    }
    if (!audio_fft_hann(suppressor->window, size)) {
        audio_noise_suppressor_destroy(suppressor);
        return AUDIO_INVALID;
    }
    double window_power = 0.0;
    for (u32 i = 0; i < size; ++i) window_power += suppressor->window[i] * suppressor->window[i];
    suppressor->power_scale = window_power;
    suppressor->initial_noise = pow(10.0, (double)config->initial_noise_dbfs / 10.0);
    suppressor->noise_alpha = exp(-(double)hop / ((double)config->sample_rate * 0.1));
    suppressor->noise_rise = pow(10.0, (double)config->noise_rise_db_per_s *
                                        hop / ((double)config->sample_rate * 10.0));
    suppressor->gain_floor = pow(10.0, -(double)config->max_attenuation_db / 20.0);
    audio_noise_suppressor_reset(suppressor);
    *out = suppressor;
    return AUDIO_OK;
}

void audio_noise_suppressor_destroy(AudioNoiseSuppressor *suppressor) {
    if (!suppressor) return;
    audio_fft_destroy(suppressor->fft);
    free(suppressor->window);
    free(suppressor->input);
    free(suppressor->time);
    free(suppressor->re);
    free(suppressor->im);
    free(suppressor->noise);
    free(suppressor->smooth);
    free(suppressor->overlap);
    free(suppressor->output);
    free(suppressor);
}

void audio_noise_suppressor_reset(AudioNoiseSuppressor *suppressor) {
    if (!suppressor) return;
    const u32 size = suppressor->frame_size;
    memset(suppressor->input, 0, sizeof(f64) * size);
    memset(suppressor->overlap, 0, sizeof(f64) * suppressor->hop);
    memset(suppressor->output, 0, sizeof(f64) * size);
    for (u32 k = 0; k < suppressor->bins; ++k) {
        suppressor->noise[k] = suppressor->initial_noise;
        suppressor->smooth[k] = suppressor->initial_noise;
    }
    suppressor->filled = suppressor->hop;
    suppressor->primed = 0u;
    suppressor->output_head = 0u;
    suppressor->output_count = size;
}

u32 audio_noise_suppressor_latency_frames(const AudioNoiseSuppressor *suppressor) {
    return suppressor ? suppressor->frame_size : 0u;
}

static void noise_process_block(AudioNoiseSuppressor *suppressor) {
    const u32 size = suppressor->frame_size;
    const u32 hop = suppressor->hop;
    for (u32 i = 0; i < size; ++i) suppressor->time[i] = suppressor->input[i] * suppressor->window[i];
    audio_fft_forward(suppressor->fft, suppressor->time, suppressor->re, suppressor->im);
    for (u32 k = 0; k < suppressor->bins; ++k) {
        const double re = suppressor->re[k], im = suppressor->im[k];
        double power = (re * re + im * im) / suppressor->power_scale;
        if (power < AUDIO_NOISE_SUPPRESSOR_MIN_POWER) power = AUDIO_NOISE_SUPPRESSOR_MIN_POWER;
        double smooth = suppressor->smooth[k];
        smooth += (1.0 - suppressor->noise_alpha) * (power - smooth);
        suppressor->smooth[k] = smooth;
        double noise = suppressor->noise[k] * suppressor->noise_rise;
        if (noise > smooth) noise = smooth;
        suppressor->noise[k] = noise;
        double gain = 1.0 - 2.0 * noise / power;
        if (gain < suppressor->gain_floor) gain = suppressor->gain_floor;
        suppressor->re[k] = re * gain;
        suppressor->im[k] = im * gain;
    }
    audio_fft_inverse(suppressor->fft, suppressor->re, suppressor->im, suppressor->time);
    for (u32 i = 0; i < hop; ++i) {
        const double y = suppressor->time[i] + suppressor->overlap[i];
        suppressor->overlap[i] = suppressor->time[i + hop];
        if (suppressor->primed) {
            const u32 pos = (suppressor->output_head + suppressor->output_count) % size;
            suppressor->output[pos] = y;
            ++suppressor->output_count;
        }
    }
    suppressor->primed = 1u;
    memmove(suppressor->input, suppressor->input + hop, sizeof(f64) * hop);
    suppressor->filled = hop;
}

void audio_noise_suppressor_process_i16(AudioNoiseSuppressor *suppressor,
                                        i16 *samples, u32 frames) {
    if (!suppressor || (!samples && frames != 0u)) return;
    for (u32 i = 0; i < frames; ++i) {
        const double input = (double)samples[i] / 32768.0;
        double output = 0.0;
        if (suppressor->output_count != 0u) {
            output = suppressor->output[suppressor->output_head];
            suppressor->output_head = (suppressor->output_head + 1u) % suppressor->frame_size;
            --suppressor->output_count;
        }
        double scaled = output * 32768.0;
        if (scaled > 32767.0) scaled = 32767.0;
        if (scaled < -32768.0) scaled = -32768.0;
        samples[i] = (i16)nearbyint(scaled);
        suppressor->input[suppressor->filled++] = input;
        if (suppressor->filled == suppressor->frame_size) noise_process_block(suppressor);
    }
}
