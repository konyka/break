#include "audio_delay_estimator.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/* The last `history` = window + max_delay frames of both signals, each
 * written at i and i + history, so every window is contiguous: the oldest
 * kept frame is at `pos`. */
struct AudioDelayEstimator {
    u32 max_delay;
    u32 window;
    u32 history;
    u32 pos;
    u64 pushed;
    i16 *reference; /* 2 * history */
    i16 *capture;   /* 2 * history */
};

AudioResult audio_delay_estimator_create(const AudioDelayEstimatorConfig *config,
                                         AudioDelayEstimator **out) {
    if (!config || !out || config->max_delay_frames < 1u ||
        config->max_delay_frames > AUDIO_DELAY_ESTIMATOR_MAX_DELAY ||
        config->window_frames < AUDIO_DELAY_ESTIMATOR_MIN_WINDOW ||
        config->window_frames > AUDIO_DELAY_ESTIMATOR_MAX_WINDOW) {
        return AUDIO_INVALID;
    }
    AudioDelayEstimator *est = (AudioDelayEstimator *)calloc(1u, sizeof(*est));
    if (!est) return AUDIO_OVERLOAD;
    est->max_delay = config->max_delay_frames;
    est->window = config->window_frames;
    est->history = config->window_frames + config->max_delay_frames;
    est->reference = (i16 *)calloc(2u * (usize)est->history, sizeof(i16));
    est->capture = (i16 *)calloc(2u * (usize)est->history, sizeof(i16));
    if (!est->reference || !est->capture) {
        audio_delay_estimator_destroy(est);
        return AUDIO_OVERLOAD;
    }
    *out = est;
    return AUDIO_OK;
}

void audio_delay_estimator_destroy(AudioDelayEstimator *est) {
    if (!est) return;
    free(est->reference);
    free(est->capture);
    free(est);
}

/* An estimate reads only the last `history` pushes, which a reset makes
 * the caller supply again, so forgetting needs only the count. */
void audio_delay_estimator_reset(AudioDelayEstimator *est) {
    if (est) est->pushed = 0u;
}

void audio_delay_estimator_push_i16(AudioDelayEstimator *est, const i16 *reference,
                                    const i16 *capture, u32 frames) {
    if (!est || !reference || !capture) return;
    for (u32 n = 0; n < frames; ++n) {
        est->reference[est->pos] = reference[n];
        est->reference[est->pos + est->history] = reference[n];
        est->capture[est->pos] = capture[n];
        est->capture[est->pos + est->history] = capture[n];
        est->pos = est->pos + 1u == est->history ? 0u : est->pos + 1u;
    }
    est->pushed += frames;
}

static bool delay_score(const AudioDelayEstimator *est, const i16 *cap, i64 cc,
                        u32 lag, double *score) {
    const i16 *ref = est->reference + est->pos + est->max_delay - lag;
    i64 cr = 0, rr = 0;
    for (u32 i = 0; i < est->window; ++i) {
        cr += (i64)cap[i] * ref[i];
        rr += (i64)ref[i] * ref[i];
    }
    if (rr == 0) return false;
    *score = (double)cr / sqrt((double)cc * (double)rr);
    return true;
}

static bool best_delay(AudioDelayEstimator *est, u32 *delay_frames, double *correlation) {
    if (!est || !delay_frames || !correlation || est->pushed < est->history) return false;
    const i16 *cap = est->capture + est->pos + est->max_delay;
    i64 cc = 0;
    for (u32 i = 0; i < est->window; ++i) cc += (i64)cap[i] * cap[i];
    if (cc == 0) return false;
    bool found = false;
    u32 best_lag = 0u;
    double best = 0.0;
    for (u32 lag = 0; lag <= est->max_delay; ++lag) {
        double score = 0.0;
        if (!delay_score(est, cap, cc, lag, &score)) continue;
        if (!found || fabs(score) > fabs(best)) {
            found = true;
            best = score;
            best_lag = lag;
        }
    }
    if (!found) return false;
    *delay_frames = best_lag;
    *correlation = best;
    return true;
}

bool audio_delay_estimator_estimate(AudioDelayEstimator *est, u32 *delay_frames,
                                    double *correlation) {
    return best_delay(est, delay_frames, correlation);
}

bool audio_delay_estimator_estimate_subframe(AudioDelayEstimator *est,
                                             double *delay_frames,
                                             double *correlation) {
    u32 lag = 0u;
    double best = 0.0;
    if (!best_delay(est, &lag, &best)) return false;
    double result = lag;
    if (lag > 0u && lag < est->max_delay) {
        const i16 *cap = est->capture + est->pos + est->max_delay;
        i64 cc = 0;
        for (u32 i = 0; i < est->window; ++i) cc += (i64)cap[i] * cap[i];
        double before = 0.0, after = 0.0;
        if (delay_score(est, cap, cc, lag - 1u, &before) &&
            delay_score(est, cap, cc, lag + 1u, &after)) {
            const double a = fabs(before), b = fabs(best), c = fabs(after);
            const double denominator = a - 2.0 * b + c;
            if (denominator < 0.0) {
                const double offset = 0.5 * (a - c) / denominator;
                if (isfinite(offset) && fabs(offset) <= 0.5) result += offset;
            }
        }
    }
    *delay_frames = result;
    *correlation = best;
    return true;
}

#define AUDIO_DELAY_LINE_SINC_EXTRA_DELAY 8u
#define AUDIO_DELAY_LINE_HISTORY_PADDING 32u

static const double kPi = 3.14159265358979323846;

struct AudioDelayLine {
    u32 max_delay;
    u32 size;
    u32 write;
    double delay;
    double fade_from;
    u32 crossfade_frames;
    u32 fade_total;
    u32 fade_remaining;
    bool sinc;
    i16 *buffer;
};

AudioResult audio_delay_line_create(u32 max_delay_frames, AudioDelayLine **out) {
    if (!out || max_delay_frames > AUDIO_DELAY_ESTIMATOR_MAX_DELAY) return AUDIO_INVALID;
    AudioDelayLine *line = (AudioDelayLine *)calloc(1u, sizeof(*line));
    if (!line) return AUDIO_OVERLOAD;
    line->max_delay = max_delay_frames;
    line->size = max_delay_frames + AUDIO_DELAY_LINE_HISTORY_PADDING + 1u;
    line->buffer = (i16 *)calloc(line->size, sizeof(i16));
    if (!line->buffer) {
        free(line);
        return AUDIO_OVERLOAD;
    }
    *out = line;
    return AUDIO_OK;
}

void audio_delay_line_destroy(AudioDelayLine *line) {
    if (!line) return;
    free(line->buffer);
    free(line);
}

void audio_delay_line_reset(AudioDelayLine *line) {
    if (!line) return;
    memset(line->buffer, 0, (size_t)line->size * sizeof(i16));
    line->write = 0u;
    line->fade_from = 0.0;
    line->fade_total = 0u;
    line->fade_remaining = 0u;
}

static AudioResult delay_line_change(AudioDelayLine *line, double delay) {
    if (line->fade_remaining > 0u) return AUDIO_REJECTED;
    if (line->delay == delay) return AUDIO_OK;
    if (line->crossfade_frames > 0u) {
        line->fade_from = line->delay;
        line->fade_total = line->crossfade_frames;
        line->fade_remaining = line->crossfade_frames;
    }
    line->delay = delay;
    return AUDIO_OK;
}

AudioResult audio_delay_line_set_delay(AudioDelayLine *line, u32 delay_frames) {
    if (!line || delay_frames > line->max_delay) return AUDIO_INVALID;
    return delay_line_change(line, delay_frames);
}

u32 audio_delay_line_delay(const AudioDelayLine *line) {
    return line ? (u32)line->delay : 0u;
}

AudioResult audio_delay_line_set_subframe_delay(AudioDelayLine *line, double delay_frames) {
    if (!line || !isfinite(delay_frames) || delay_frames < 0.0 ||
        delay_frames > (double)line->max_delay) {
        return AUDIO_INVALID;
    }
    return delay_line_change(line, delay_frames);
}

double audio_delay_line_subframe_delay(const AudioDelayLine *line) {
    return line ? line->delay : 0.0;
}

AudioResult audio_delay_line_set_sinc(AudioDelayLine *line, bool enabled) {
    if (!line) return AUDIO_INVALID;
    if (line->fade_remaining > 0u) return AUDIO_REJECTED;
    line->sinc = enabled;
    return AUDIO_OK;
}

bool audio_delay_line_sinc(const AudioDelayLine *line) {
    return line ? line->sinc : false;
}

u32 audio_delay_line_sinc_extra_delay(const AudioDelayLine *line) {
    return line && line->sinc ? AUDIO_DELAY_LINE_SINC_EXTRA_DELAY : 0u;
}

AudioResult audio_delay_line_set_crossfade_frames(AudioDelayLine *line, u32 frames) {
    if (!line || frames > 48000u) return AUDIO_INVALID;
    if (line->fade_remaining > 0u) return AUDIO_REJECTED;
    line->crossfade_frames = frames;
    return AUDIO_OK;
}

u32 audio_delay_line_crossfade_frames(const AudioDelayLine *line) {
    return line ? line->crossfade_frames : 0u;
}

static u32 delay_line_read_index(const AudioDelayLine *line, u32 delay) {
    return line->write >= delay ? line->write - delay
                                : line->write + line->size - delay;
}

static double normalized_sinc(double value) {
    return fabs(value) < 1e-12 ? 1.0 : sin(kPi * value) / (kPi * value);
}

static double delay_line_sinc_sample(const AudioDelayLine *line, u32 whole,
                                     double fraction) {
    if (fraction == 0.0) {
        return line->buffer[delay_line_read_index(
            line, whole + AUDIO_DELAY_LINE_SINC_EXTRA_DELAY)];
    }
    double value = 0.0, weight_sum = 0.0;
    for (int j = -7; j <= 8; ++j) {
        const int tap = j + 7;
        const double window = 0.42 - 0.5 * cos(2.0 * kPi * tap / 15.0) +
                              0.08 * cos(4.0 * kPi * tap / 15.0);
        const double weight = normalized_sinc(fraction - j) * window;
        const u32 source_delay = (u32)((int)whole + 8 + j);
        value += line->buffer[delay_line_read_index(line, source_delay)] * weight;
        weight_sum += weight;
    }
    return value / weight_sum;
}

static double delay_line_value(const AudioDelayLine *line, double delay) {
    const u32 whole = (u32)delay;
    const double fraction = delay - (double)whole;
    if (line->sinc) return delay_line_sinc_sample(line, whole, fraction);
    const u32 read = delay_line_read_index(line, whole);
    const u32 previous = read == 0u ? line->size - 1u : read - 1u;
    return (1.0 - fraction) * line->buffer[read] + fraction * line->buffer[previous];
}

static i16 delay_line_sinc_i16(double value) {
    const double rounded = nearbyint(value);
    if (rounded > 32767.0) return 32767;
    if (rounded < -32768.0) return -32768;
    return (i16)rounded;
}

void audio_delay_line_process_i16(AudioDelayLine *line, const i16 *in, i16 *out, u32 frames) {
    if (!line || !in || !out) return;
    for (u32 n = 0; n < frames; ++n) {
        /* written first, so a delay of 0 passes the frame straight through
         * and `out` may alias `in` */
        line->buffer[line->write] = in[n];
        double value = delay_line_value(line, line->delay);
        if (line->fade_remaining > 0u) {
            const u32 step = line->fade_total - line->fade_remaining + 1u;
            const double weight = (double)step / line->fade_total;
            const double old_value = delay_line_value(line, line->fade_from);
            value = old_value * (1.0 - weight) + value * weight;
            --line->fade_remaining;
        }
        out[n] = line->sinc ? delay_line_sinc_i16(value) : (i16)nearbyint(value);
        line->write = line->write + 1u == line->size ? 0u : line->write + 1u;
    }
}
