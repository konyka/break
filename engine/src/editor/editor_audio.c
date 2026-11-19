#include "editor_audio.h"

#include <audio/audio_edit.h>
#include <audio/audio_wav.h>
#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BreakEditorAudioState BreakEditorAudioState;

struct BreakEditorAudioState {
    u32 sample_rate;
    u32 channels;
    u32 frames;
    i16 *samples;
};

typedef struct {
    BreakEditorCmd base;
    u32 before_frames;
    u32 after_frames;
    usize bytes;
    i16 *before;
    i16 *after;
} BreakEditorAudioSnapshotCmd;

static usize audio_state_bytes(const BreakEditorAudioState *audio) {
    return (usize)audio->frames * audio->channels * sizeof(i16);
}

bool break_editor_doc_audio_attach(BreakEditorDoc *doc, u32 sample_rate, u32 channels,
                                   const i16 *samples, u32 frames) {
    if (!doc || doc->audio || sample_rate < 8000u || sample_rate > 192000u ||
        (channels != 1u && channels != 2u) || frames > BREAK_EDITOR_AUDIO_MAX_FRAMES ||
        (!samples && frames != 0u)) {
        return false;
    }
    BreakEditorAudioState *audio = break_editor_test_calloc(sizeof(*audio));
    if (!audio) return false;
    const usize capacity = (usize)BREAK_EDITOR_AUDIO_MAX_FRAMES * channels * sizeof(i16);
    audio->samples = break_editor_test_calloc(capacity);
    if (!audio->samples) {
        free(audio);
        return false;
    }
    audio->sample_rate = sample_rate;
    audio->channels = channels;
    audio->frames = frames;
    if (frames != 0u) memcpy(audio->samples, samples, (usize)frames * channels * sizeof(i16));
    doc->audio = audio;
    doc->audio_revision++;
    doc->dirty = true;
    return true;
}

bool break_editor_doc_audio_attached(const BreakEditorDoc *doc) {
    return doc && doc->audio;
}

u32 break_editor_doc_audio_frames(const BreakEditorDoc *doc) {
    return doc && doc->audio ? doc->audio->frames : 0u;
}

u32 break_editor_doc_audio_sample_rate(const BreakEditorDoc *doc) {
    return doc && doc->audio ? doc->audio->sample_rate : 0u;
}

u32 break_editor_doc_audio_channels(const BreakEditorDoc *doc) {
    return doc && doc->audio ? doc->audio->channels : 0u;
}

const i16 *break_editor_doc_audio_samples(const BreakEditorDoc *doc) {
    return doc && doc->audio ? doc->audio->samples : NULL;
}

u64 break_editor_doc_audio_revision(const BreakEditorDoc *doc) {
    return doc ? doc->audio_revision : 0u;
}

bool break_editor_doc_audio_waveform(const BreakEditorDoc *doc, u32 columns,
                                     i16 *out_min, i16 *out_max) {
    return break_editor_doc_audio_waveform_range(
        doc, 0u, doc && doc->audio ? doc->audio->frames : 0u, columns, out_min, out_max);
}

/* channel == UINT32_MAX merges every channel; otherwise only that one. */
static bool audio_waveform_impl(const BreakEditorDoc *doc, u32 channel, u32 begin, u32 end,
                                u32 columns, i16 *out_min, i16 *out_max) {
    if (!doc || !doc->audio || !out_min || !out_max || columns == 0u ||
        columns > BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS || begin >= end ||
        end > doc->audio->frames) {
        return false;
    }
    const BreakEditorAudioState *audio = doc->audio;
    const bool merged = channel == UINT32_MAX;
    if (!merged && channel >= audio->channels) {
        return false;
    }
    const u32 step = merged ? 1u : audio->channels;
    const u32 offset = merged ? 0u : channel;
    const u64 frames = (u64)end - begin;
    for (u32 c = 0u; c < columns; ++c) {
        const u64 first = begin + (u64)c * frames / columns;
        u64 last = begin + (u64)(c + 1u) * frames / columns;
        if (last <= first) last = first + 1u;
        const i16 *sample = audio->samples + first * audio->channels + offset;
        const i16 *stop = audio->samples + last * audio->channels;
        i16 lo = *sample, hi = *sample;
        for (; sample < stop; sample += step) {
            if (*sample < lo) lo = *sample;
            if (*sample > hi) hi = *sample;
        }
        out_min[c] = lo;
        out_max[c] = hi;
    }
    return true;
}

bool break_editor_doc_audio_waveform_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                           u32 columns, i16 *out_min, i16 *out_max) {
    return audio_waveform_impl(doc, UINT32_MAX, begin, end, columns, out_min, out_max);
}

bool break_editor_doc_audio_waveform_channel(const BreakEditorDoc *doc, u32 channel,
                                             u32 begin, u32 end, u32 columns,
                                             i16 *out_min, i16 *out_max) {
    return channel != UINT32_MAX &&
           audio_waveform_impl(doc, channel, begin, end, columns, out_min, out_max);
}

bool break_editor_doc_audio_peak_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                       double *out_peak, double *out_rms) {
    if (!doc || !doc->audio || !out_peak || !out_rms || begin >= end ||
        end > doc->audio->frames) {
        return false;
    }
    const BreakEditorAudioState *audio = doc->audio;
    const i16 *sample = audio->samples + (usize)begin * audio->channels;
    const i16 *stop = audio->samples + (usize)end * audio->channels;
    const usize count = (usize)(end - begin) * audio->channels;
    double peak = 0.0, sum = 0.0;
    for (; sample < stop; ++sample) {
        /* in double throughout: a long range would overflow an i64 of
         * squared samples only past ~8e9 frames, but the mean needs the
         * division anyway */
        const double value = (double)*sample;
        const double magnitude = value < 0.0 ? -value : value;
        if (magnitude > peak) peak = magnitude;
        sum += value * value;
    }
    *out_peak = peak;
    *out_rms = count != 0u ? sqrt(sum / (double)count) : 0.0;
    return true;
}

/* True peak: the signal reconstructed at 4x the sample rate. A windowed
 * sinc polyphase FIR, 4 phases of 2*TP_HALF+1 taps; phase 0 is the identity
 * (sinc(0)=1, sinc(k)=0 for integer k), so the result is never below the
 * sample peak. Not the ITU-R BS.1770 filter, which this does not claim. */
#define TP_PHASES 4u
#define TP_HALF 16
#define TP_TAPS (2 * TP_HALF + 1)

static double g_tp_kernel[TP_PHASES][TP_TAPS];
static bool g_tp_kernel_ready = false;

static void audio_tp_build_kernel(void) {
    if (g_tp_kernel_ready) {
        return;
    }
    for (u32 phase = 0u; phase < TP_PHASES; ++phase) {
        const double frac = (double)phase / (double)TP_PHASES;
        double sum = 0.0;
        for (int t = 0; t < TP_TAPS; ++t) {
            const double x = (double)(t - TP_HALF) - frac;
            double sinc, window;
            if (x > -1e-12 && x < 1e-12) {
                sinc = 1.0;
            } else {
                sinc = sin(3.14159265358979323846 * x) / (3.14159265358979323846 * x);
            }
            /* Blackman over the tap span, so the kernel decays to zero */
            {
                const double n = ((double)t + 0.5) / (double)TP_TAPS;
                window = 0.42 - 0.5 * cos(2.0 * 3.14159265358979323846 * n) +
                         0.08 * cos(4.0 * 3.14159265358979323846 * n);
            }
            g_tp_kernel[phase][t] = sinc * window;
            sum += g_tp_kernel[phase][t];
        }
        /* unity DC gain, so a constant signal keeps its level */
        if (sum > 1e-9 || sum < -1e-9) {
            for (int t = 0; t < TP_TAPS; ++t) {
                g_tp_kernel[phase][t] /= sum;
            }
        }
    }
    g_tp_kernel_ready = true;
}

bool break_editor_doc_audio_true_peak_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                            double *out_peak) {
    if (!doc || !doc->audio || !out_peak || begin >= end || end > doc->audio->frames) {
        return false;
    }
    audio_tp_build_kernel();
    const BreakEditorAudioState *audio = doc->audio;
    const i64 frames = (i64)audio->frames;
    double peak = 0.0;
    for (u32 channel = 0u; channel < audio->channels; ++channel) {
        for (i64 f = (i64)begin; f < (i64)end; ++f) {
            for (u32 phase = 0u; phase < TP_PHASES; ++phase) {
                double acc = 0.0;
                for (int t = 0; t < TP_TAPS; ++t) {
                    /* outside the clip the signal is zero, so an edge range
                     * never reads past the buffer */
                    const i64 index = f + (i64)(t - TP_HALF);
                    if (index < 0 || index >= frames) {
                        continue;
                    }
                    acc += (double)audio->samples[(usize)index * audio->channels + channel] *
                           g_tp_kernel[phase][t];
                }
                if (acc < 0.0) acc = -acc;
                if (acc > peak) peak = acc;
            }
        }
    }
    *out_peak = peak;
    return true;
}

/* Integrated loudness (ITU-R BS.1770-4 structure). The K-weighting is two
 * biquads: a high-shelf (+4 dB above ~1.5 kHz) and a high-pass at ~38 Hz.
 * The standard tabulates coefficients for 48 kHz; these are derived for the
 * clip's own rate from the same analogue prototypes, so a low-rate clip is
 * filtered correctly instead of only 48 kHz being right. */
typedef struct {
    double b0, b1, b2, a1, a2;
} AudioBiquad;

/* The 48 kHz reference coefficients come from poles/zeros at
 * f0 = 1681.97 Hz, Q = 0.7071, gain +3.9998 dB (shelf) and
 * f0 = 38.135 Hz, Q = 0.5003 (high-pass). */
static void audio_k_shelf(double rate, AudioBiquad *out) {
    const double f0 = 1681.974450955533, g_db = 3.999843853973347, q = 0.7071752369554196;
    const double k = tan(3.14159265358979323846 * f0 / rate);
    const double vh = pow(10.0, g_db / 20.0);
    const double vb = pow(vh, 0.4996667741545416);
    const double denom = 1.0 + k / q + k * k;
    out->b0 = (vh + vb * k / q + k * k) / denom;
    out->b1 = 2.0 * (k * k - vh) / denom;
    out->b2 = (vh - vb * k / q + k * k) / denom;
    out->a1 = 2.0 * (k * k - 1.0) / denom;
    out->a2 = (1.0 - k / q + k * k) / denom;
}

static void audio_k_highpass(double rate, AudioBiquad *out) {
    const double f0 = 38.13547087602444, q = 0.5003270373238773;
    const double k = tan(3.14159265358979323846 * f0 / rate);
    const double denom = 1.0 + k / q + k * k;
    out->b0 = 1.0;
    out->b1 = -2.0;
    out->b2 = 1.0;
    out->a1 = 2.0 * (k * k - 1.0) / denom;
    out->a2 = (1.0 - k / q + k * k) / denom;
}

/* y[n] = b0 x[n] + b1 x[n-1] + b2 x[n-2] - a1 y[n-1] - a2 y[n-2] */
typedef struct {
    double x1, x2, y1, y2;
} AudioBiquadState;

static double audio_biquad_step(const AudioBiquad *f, AudioBiquadState *s, double x) {
    const double y = f->b0 * x + f->b1 * s->x1 + f->b2 * s->x2 - f->a1 * s->y1 -
                     f->a2 * s->y2;
    s->x2 = s->x1;
    s->x1 = x;
    s->y2 = s->y1;
    s->y1 = y;
    return y;
}

#define AUDIO_LUFS_BLOCK_MS 400u
#define AUDIO_LUFS_STEP_DIV 4u /* 75% overlap */
#define AUDIO_LUFS_MAX_BLOCKS 4096u

/* K-weighted loudness of each `window` frame window, stepped by `step`,
 * over [begin, end). Shared by the integrated, short-term and range
 * measurements, which differ only in those two lengths and in how they
 * reduce the result. Returns the window count, 0 when the range cannot
 * hold one; `out_lufs` and `out_mean` each receive that many entries. */
static u32 audio_window_loudness(const BreakEditorDoc *doc, u32 begin, u32 end,
                                 u32 window, u32 step, double *out_lufs,
                                 double *out_mean, u32 capacity) {
    const BreakEditorAudioState *audio = doc->audio;
    const u32 rate = audio->sample_rate;
    if (rate == 0u || window == 0u || step == 0u || end - begin < window) {
        return 0u;
    }
    u32 count = (end - begin - window) / step + 1u;
    if (count > capacity) count = capacity;
    AudioBiquad shelf, highpass;
    audio_k_shelf((double)rate, &shelf);
    audio_k_highpass((double)rate, &highpass);
    for (u32 w = 0u; w < count; ++w) {
        out_mean[w] = 0.0;
    }
    for (u32 channel = 0u; channel < audio->channels; ++channel) {
        AudioBiquadState s1 = {0.0, 0.0, 0.0, 0.0}, s2 = {0.0, 0.0, 0.0, 0.0};
        for (u32 f = begin; f < end; ++f) {
            const double x =
                (double)audio->samples[(usize)f * audio->channels + channel] / 32768.0;
            const double y = audio_biquad_step(&highpass, &s2,
                                               audio_biquad_step(&shelf, &s1, x));
            const double sq = y * y;
            /* the frame belongs to every window covering it */
            const u32 rel = f - begin;
            const u32 first = rel >= window ? (rel - window) / step + 1u : 0u;
            for (u32 w = first; w < count; ++w) {
                const u32 start = w * step;
                if (rel < start) {
                    break;
                }
                if (rel < start + window) {
                    out_mean[w] += sq;
                }
            }
        }
    }
    for (u32 w = 0u; w < count; ++w) {
        out_mean[w] /= (double)window; /* channel weights are 1 for 1-2 ch */
        out_lufs[w] = out_mean[w] > 0.0 ? -0.691 + 10.0 * log10(out_mean[w])
                                        : BREAK_EDITOR_AUDIO_LUFS_FLOOR;
    }
    return count;
}

bool break_editor_doc_audio_loudness_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                           double *out_lufs) {
    static double block_lufs[AUDIO_LUFS_MAX_BLOCKS];
    static double block_mean[AUDIO_LUFS_MAX_BLOCKS];
    if (!doc || !doc->audio || !out_lufs || begin >= end || end > doc->audio->frames) {
        return false;
    }
    const u32 rate = doc->audio->sample_rate;
    const u32 block = (u32)((u64)rate * AUDIO_LUFS_BLOCK_MS / 1000u);
    const u32 blocks = audio_window_loudness(doc, begin, end, block,
                                             block / AUDIO_LUFS_STEP_DIV, block_lufs,
                                             block_mean, AUDIO_LUFS_MAX_BLOCKS);
    if (blocks == 0u) {
        return false; /* an integrated figure needs at least one block */
    }
    /* the absolute gate, then a relative gate 10 LU below what survives */
    double above_sum = 0.0;
    u32 above_count = 0u;
    for (u32 b = 0u; b < blocks; ++b) {
        if (block_lufs[b] > BREAK_EDITOR_AUDIO_LUFS_FLOOR) {
            above_sum += block_mean[b];
            above_count++;
        }
    }
    if (above_count == 0u) {
        *out_lufs = BREAK_EDITOR_AUDIO_LUFS_FLOOR;
        return true;
    }
    {
        const double relative =
            -0.691 + 10.0 * log10(above_sum / (double)above_count) - 10.0;
        double gated_sum = 0.0;
        u32 count = 0u;
        for (u32 b = 0u; b < blocks; ++b) {
            if (block_lufs[b] > BREAK_EDITOR_AUDIO_LUFS_FLOOR && block_lufs[b] > relative) {
                gated_sum += block_mean[b];
                count++;
            }
        }
        *out_lufs = count != 0u ? -0.691 + 10.0 * log10(gated_sum / (double)count)
                                : BREAK_EDITOR_AUDIO_LUFS_FLOOR;
    }
    if (*out_lufs < BREAK_EDITOR_AUDIO_LUFS_FLOOR) {
        *out_lufs = BREAK_EDITOR_AUDIO_LUFS_FLOOR;
    }
    return true;
}

#define AUDIO_SHORT_TERM_MS 3000u
#define AUDIO_LRA_STEP_MS 1000u
#define AUDIO_LRA_MAX_WINDOWS 2048u

bool break_editor_doc_audio_short_term_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                             double *out_lufs) {
    static double win_lufs[1];
    static double win_mean[1];
    if (!doc || !doc->audio || !out_lufs || begin >= end || end > doc->audio->frames) {
        return false;
    }
    /* the last 3 seconds of the range: one window ending at `end` */
    const u32 window = (u32)((u64)doc->audio->sample_rate * AUDIO_SHORT_TERM_MS / 1000u);
    if (window == 0u || end - begin < window) {
        return false;
    }
    if (audio_window_loudness(doc, end - window, end, window, window, win_lufs, win_mean,
                              1u) == 0u) {
        return false;
    }
    *out_lufs = win_lufs[0] > BREAK_EDITOR_AUDIO_LUFS_FLOOR
                    ? win_lufs[0]
                    : BREAK_EDITOR_AUDIO_LUFS_FLOOR;
    return true;
}

static int audio_double_compare(const void *a, const void *b) {
    const double x = *(const double *)a, y = *(const double *)b;
    return x < y ? -1 : (x > y ? 1 : 0);
}

bool break_editor_doc_audio_loudness_range_lra(const BreakEditorDoc *doc, u32 begin,
                                               u32 end, double *out_lra) {
    static double win_lufs[AUDIO_LRA_MAX_WINDOWS];
    static double win_mean[AUDIO_LRA_MAX_WINDOWS];
    static double kept[AUDIO_LRA_MAX_WINDOWS];
    if (!doc || !doc->audio || !out_lra || begin >= end || end > doc->audio->frames) {
        return false;
    }
    const u32 rate = doc->audio->sample_rate;
    const u32 window = (u32)((u64)rate * AUDIO_SHORT_TERM_MS / 1000u);
    const u32 step = (u32)((u64)rate * AUDIO_LRA_STEP_MS / 1000u);
    const u32 count = audio_window_loudness(doc, begin, end, window, step, win_lufs,
                                            win_mean, AUDIO_LRA_MAX_WINDOWS);
    if (count < 2u) {
        return false; /* one window is a level, not a range */
    }
    /* the absolute gate, then a relative gate 20 LU below the survivors */
    double above_sum = 0.0;
    u32 above_count = 0u;
    for (u32 w = 0u; w < count; ++w) {
        if (win_lufs[w] > BREAK_EDITOR_AUDIO_LUFS_FLOOR) {
            above_sum += win_mean[w];
            above_count++;
        }
    }
    if (above_count < 2u) {
        return false;
    }
    {
        const double relative =
            -0.691 + 10.0 * log10(above_sum / (double)above_count) - 20.0;
        u32 kept_count = 0u;
        for (u32 w = 0u; w < count; ++w) {
            if (win_lufs[w] > BREAK_EDITOR_AUDIO_LUFS_FLOOR && win_lufs[w] > relative) {
                kept[kept_count++] = win_lufs[w];
            }
        }
        if (kept_count < 2u) {
            return false;
        }
        qsort(kept, kept_count, sizeof(kept[0]), audio_double_compare);
        {
            /* the 10th and 95th percentiles of what survived */
            const u32 low = (u32)(((double)kept_count - 1.0) * 0.10 + 0.5);
            const u32 high = (u32)(((double)kept_count - 1.0) * 0.95 + 0.5);
            *out_lra = kept[high] - kept[low];
        }
    }
    if (*out_lra < 0.0) {
        *out_lra = 0.0;
    }
    return true;
}

void break_editor_audio_detach(BreakEditorDoc *doc) {
    if (!doc || !doc->audio) return;
    free(doc->audio->samples);
    free(doc->audio);
    doc->audio = NULL;
    doc->audio_revision++;
}

static void audio_snapshot_destroy(BreakEditorCmd *command) {
    BreakEditorAudioSnapshotCmd *snapshot = (BreakEditorAudioSnapshotCmd *)command;
    free(snapshot->before);
    free(snapshot->after);
    free(snapshot);
}

static bool audio_snapshot_restore(BreakEditorDoc *doc, u32 frames, const i16 *samples,
                                   usize bytes) {
    if (!doc || !doc->audio || (bytes != 0u && !samples)) return false;
    if (bytes != 0u) memcpy(doc->audio->samples, samples, bytes);
    doc->audio->frames = frames;
    doc->audio_revision++;
    return true;
}

static bool audio_snapshot_apply(BreakEditorCmd *command, BreakEditorDoc *doc) {
    BreakEditorAudioSnapshotCmd *snapshot = (BreakEditorAudioSnapshotCmd *)command;
    return audio_snapshot_restore(doc, snapshot->after_frames, snapshot->after, snapshot->bytes);
}

static bool audio_snapshot_revert(BreakEditorCmd *command, BreakEditorDoc *doc) {
    BreakEditorAudioSnapshotCmd *snapshot = (BreakEditorAudioSnapshotCmd *)command;
    return audio_snapshot_restore(doc, snapshot->before_frames, snapshot->before, snapshot->bytes);
}

static void audio_snapshot_describe(const BreakEditorCmd *command, char buf[128]) {
    snprintf(buf, 128, "audio %.96s", command->name);
}

static BreakEditorAudioSnapshotCmd *audio_snapshot_create(BreakEditorDoc *doc,
                                                          const char *operation) {
    BreakEditorAudioSnapshotCmd *snapshot = break_editor_test_calloc(sizeof(*snapshot));
    if (!snapshot) return NULL;
    snapshot->base.apply = audio_snapshot_apply;
    snapshot->base.revert = audio_snapshot_revert;
    snapshot->base.destroy = audio_snapshot_destroy;
    snapshot->base.describe = audio_snapshot_describe;
    snapshot->base.kind = BREAK_EDITOR_CMD_KIND_AUDIO_SNAPSHOT;
    break_editor_name_copy(snapshot->base.name, operation);
    snapshot->before_frames = doc->audio->frames;
    snapshot->after_frames = doc->audio->frames;
    snapshot->bytes = audio_state_bytes(doc->audio);
    if (snapshot->bytes != 0u) {
        snapshot->before = break_editor_test_calloc(snapshot->bytes);
        snapshot->after = break_editor_test_calloc(snapshot->bytes);
        if (!snapshot->before || !snapshot->after) {
            audio_snapshot_destroy(&snapshot->base);
            return NULL;
        }
        memcpy(snapshot->before, doc->audio->samples, snapshot->bytes);
        memcpy(snapshot->after, doc->audio->samples, snapshot->bytes);
    }
    return snapshot;
}

static bool audio_snapshot_commit(BreakEditorAudioSnapshotCmd *snapshot, BreakEditorDoc *doc,
                                  u32 after_frames) {
    snapshot->after_frames = after_frames;
    if (!snapshot->base.apply(&snapshot->base, doc)) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    break_editor_cmd_stack_push_applied(doc, &snapshot->base);
    doc->dirty = true;
    return true;
}

bool break_editor_doc_audio_trim(BreakEditorDoc *doc, u32 begin, u32 end) {
    if (!doc || !doc->audio || begin > end || end > doc->audio->frames) return false;
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "trim");
    if (!snapshot) return false;
    u32 frames = 0u;
    const AudioResult result = audio_edit_trim_i16(snapshot->after, snapshot->before_frames,
                                                   doc->audio->channels, begin, end, &frames);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, frames);
}

bool break_editor_doc_audio_cut(BreakEditorDoc *doc, u32 begin, u32 end) {
    if (!doc || !doc->audio || begin > end || end > doc->audio->frames) return false;
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "cut");
    if (!snapshot) return false;
    u32 frames = 0u;
    const AudioResult result = audio_edit_cut_i16(snapshot->after, snapshot->before_frames,
                                                  doc->audio->channels, begin, end, &frames);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, frames);
}

bool break_editor_doc_audio_fade(BreakEditorDoc *doc, double fade_in_ms, double fade_out_ms) {
    if (!doc || !doc->audio || !isfinite(fade_in_ms) || !isfinite(fade_out_ms) ||
        fade_in_ms < 0.0 || fade_out_ms < 0.0) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "fade");
    if (!snapshot) return false;
    const AudioResult result = audio_edit_fade_i16(snapshot->after, snapshot->before_frames,
                                                   doc->audio->channels,
                                                   doc->audio->sample_rate, fade_in_ms,
                                                   fade_out_ms);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

bool break_editor_doc_audio_normalize(BreakEditorDoc *doc, double target_dbfs) {
    if (!doc || !doc->audio || !isfinite(target_dbfs) || target_dbfs < -120.0 ||
        target_dbfs > 0.0) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "normalize");
    if (!snapshot) return false;
    const AudioResult result = audio_edit_normalize_i16(snapshot->after, snapshot->before_frames,
                                                        doc->audio->channels, target_dbfs);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

static bool audio_range_valid(const BreakEditorDoc *doc, u32 begin, u32 end) {
    return doc && doc->audio && begin < end && end <= doc->audio->frames;
}

bool break_editor_doc_audio_fade_range(BreakEditorDoc *doc, u32 begin, u32 end,
                                       double fade_in_ms, double fade_out_ms) {
    if (!audio_range_valid(doc, begin, end) || !isfinite(fade_in_ms) ||
        !isfinite(fade_out_ms) || fade_in_ms < 0.0 || fade_out_ms < 0.0) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "fade");
    if (!snapshot) return false;
    const u32 channels = doc->audio->channels;
    const AudioResult result =
        audio_edit_fade_i16(snapshot->after + (usize)begin * channels, end - begin, channels,
                            doc->audio->sample_rate, fade_in_ms, fade_out_ms);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

bool break_editor_doc_audio_normalize_range(BreakEditorDoc *doc, u32 begin, u32 end,
                                            double target_dbfs) {
    if (!audio_range_valid(doc, begin, end) || !isfinite(target_dbfs) ||
        target_dbfs < -120.0 || target_dbfs > 0.0) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "normalize");
    if (!snapshot) return false;
    const u32 channels = doc->audio->channels;
    const AudioResult result = audio_edit_normalize_i16(
        snapshot->after + (usize)begin * channels, end - begin, channels, target_dbfs);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

bool break_editor_doc_audio_mix(BreakEditorDoc *doc, const i16 *source,
                                u32 source_frames, double gain) {
    if (!doc || !doc->audio || !isfinite(gain) || gain < -8.0 || gain > 8.0 ||
        (!source && source_frames != 0u)) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "mix");
    if (!snapshot) return false;
    const AudioResult result = audio_edit_mix_i16(snapshot->after, snapshot->before_frames,
                                                  source, source_frames,
                                                  doc->audio->channels, gain);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

#define BREAK_EDITOR_WAV_MAX_BYTES (1L << 20)

bool break_editor_doc_audio_attach_wav(BreakEditorDoc *doc, const char *path) {
    if (!doc || doc->audio || !path || path[0] == '\0') return false;
    FILE *file = fopen(path, "rb");
    if (!file) return false;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return false;
    }
    const long length = ftell(file);
    if (length <= 0 || length > BREAK_EDITOR_WAV_MAX_BYTES) {
        fclose(file);
        return false;
    }
    const usize size = (usize)length;
    u8 *data = break_editor_test_calloc(size);
    if (!data) {
        fclose(file);
        return false;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        free(data);
        fclose(file);
        return false;
    }
    const bool read_ok = fread(data, 1u, size, file) == size;
    const bool close_ok = fclose(file) == 0;
    if (!read_ok || !close_ok) {
        free(data);
        return false;
    }
    const usize pcm_capacity = (usize)BREAK_EDITOR_AUDIO_MAX_FRAMES * 2u * sizeof(i16);
    i16 *pcm = break_editor_test_calloc(pcm_capacity);
    if (!pcm) {
        free(data);
        return false;
    }
    AudioWavInfo info;
    const AudioResult result = audio_wav_decode_i16(data, size, &info, pcm,
                                                    BREAK_EDITOR_AUDIO_MAX_FRAMES);
    bool attached = false;
    if (result == AUDIO_OK) {
        attached = break_editor_doc_audio_attach(doc, info.sample_rate, info.channels,
                                                 pcm, info.frames);
    }
    free(pcm);
    free(data);
    return attached;
}

/* rename(2) replaces atomically on POSIX; Windows rename() fails when the
 * destination exists, so it is removed first (best effort, as for scenes). */
static bool editor_audio_rename_replace(const char *tmp, const char *dst) {
#if defined(_WIN32)
    remove(dst);
#endif
    return rename(tmp, dst) == 0;
}

bool break_editor_doc_audio_save_wav(const BreakEditorDoc *doc, const char *path) {
    if (!doc || !doc->audio || !path || path[0] == '\0') return false;
    const BreakEditorAudioState *audio = doc->audio;
    char tmp[1024];
    const int length = snprintf(tmp, sizeof(tmp), "%s.tmp", path);
    if (length < 0 || (usize)length >= sizeof(tmp)) return false;
    usize size = 0u;
    if (audio_wav_encoded_size(audio->channels, audio->frames, &size) != AUDIO_OK) return false;
    u8 *data = break_editor_test_calloc(size);
    if (!data) return false;
    const AudioWavInfo info = {audio->sample_rate, audio->channels, audio->frames};
    usize encoded = 0u;
    bool ok = audio_wav_encode_i16(&info, audio->samples, data, size, &encoded) == AUDIO_OK;
    FILE *file = ok ? fopen(tmp, "wb") : NULL;
    if (file) {
        const bool written = fwrite(data, 1u, encoded, file) == encoded;
        const bool closed = fclose(file) == 0;
        ok = written && closed && editor_audio_rename_replace(tmp, path);
        if (!ok) remove(tmp);
    } else {
        ok = false;
    }
    free(data);
    return ok;
}
