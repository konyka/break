#include "audio_hrtf.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * HRTF sets and the binaural renderer (docs/design/audio_extended.md,
 * "HRTF"). A set owns copies of its directions, their unit vectors and both
 * ears' impulse responses. The renderer keeps a mirrored history (every
 * sample written at cursor and cursor + taps) so one contiguous window of
 * `taps` samples always ends at the newest input.
 */

#define HRTF_PI 3.14159265358979323846
#define HRTF_COINCIDENT 1e-6
#define HEAD_RADIUS_M 0.0875
#define SOUND_SPEED_MPS 343.0
#define SHADOW_ALPHA_MIN 0.1
#define SHADOW_THETA_MIN_RAD (150.0 * HRTF_PI / 180.0)
#define PINNA_ECHOES 5u
#define PINNA_REFERENCE_RATE 44100.0

struct AudioHrtfSet {
    u32 sample_rate;
    u32 taps;
    u32 count;
    AudioHrtfDirection *directions;
    double *vectors; /* 3 per direction */
    f32 *left;
    f32 *right;
};

/* NaN fails every comparison and infinities fall outside the ranges */
static bool angles_valid(f32 azimuth, f32 elevation) {
    return azimuth >= -180.0f && azimuth <= 180.0f && elevation >= -90.0f && elevation <= 90.0f;
}

static void unit_vector(f32 azimuth, f32 elevation, double *v) {
    double az = (double)azimuth * HRTF_PI / 180.0, el = (double)elevation * HRTF_PI / 180.0;
    v[0] = cos(el) * sin(az);
    v[1] = sin(el);
    v[2] = cos(el) * cos(az);
}

static bool coincident(const double *a, const double *b) {
    return fabs(a[0] - b[0]) <= HRTF_COINCIDENT && fabs(a[1] - b[1]) <= HRTF_COINCIDENT &&
           fabs(a[2] - b[2]) <= HRTF_COINCIDENT;
}

static bool samples_valid(const f32 *s, usize n) {
    for (usize i = 0; i < n; i++) {
        if (!isfinite(s[i]) || fabsf(s[i]) > AUDIO_HRTF_MAX_SAMPLE) return false;
    }
    return true;
}

static bool shape_valid(u32 sample_rate, u32 taps, u32 count) {
    return sample_rate >= AUDIO_HRTF_MIN_SAMPLE_RATE && sample_rate <= AUDIO_HRTF_MAX_SAMPLE_RATE &&
           taps >= 1u && taps <= AUDIO_HRTF_MAX_TAPS && count >= 1u && count <= AUDIO_HRTF_MAX_DIRECTIONS;
}

void audio_hrtf_set_destroy(AudioHrtfSet *set) {
    if (!set) return;
    free(set->directions);
    free(set->vectors);
    free(set->left);
    free(set->right);
    free(set);
}

AudioResult audio_hrtf_set_create(u32 sample_rate, u32 taps, u32 count,
                                  const AudioHrtfDirection *directions,
                                  const f32 *left, const f32 *right,
                                  AudioHrtfSet **out) {
    AudioHrtfSet *set;
    usize samples;
    if (!out || !directions || !left || !right || !shape_valid(sample_rate, taps, count)) {
        return AUDIO_INVALID;
    }
    samples = (usize)count * taps;
    for (u32 i = 0; i < count; i++) {
        if (!angles_valid(directions[i].azimuth, directions[i].elevation)) return AUDIO_INVALID;
    }
    if (!samples_valid(left, samples) || !samples_valid(right, samples)) return AUDIO_INVALID;
    set = (AudioHrtfSet *)calloc(1u, sizeof(*set));
    if (!set) return AUDIO_OVERLOAD;
    set->directions = (AudioHrtfDirection *)malloc((usize)count * sizeof(*set->directions));
    set->vectors = (double *)malloc((usize)count * 3u * sizeof(*set->vectors));
    set->left = (f32 *)malloc(samples * sizeof(f32));
    set->right = (f32 *)malloc(samples * sizeof(f32));
    if (!set->directions || !set->vectors || !set->left || !set->right) {
        audio_hrtf_set_destroy(set);
        return AUDIO_OVERLOAD;
    }
    for (u32 i = 0; i < count; i++) {
        unit_vector(directions[i].azimuth, directions[i].elevation, set->vectors + 3u * i);
        for (u32 j = 0; j < i; j++) {
            if (coincident(set->vectors + 3u * i, set->vectors + 3u * j)) {
                audio_hrtf_set_destroy(set);
                return AUDIO_INVALID;
            }
        }
    }
    memcpy(set->directions, directions, (usize)count * sizeof(*directions));
    memcpy(set->left, left, samples * sizeof(f32));
    memcpy(set->right, right, samples * sizeof(f32));
    set->sample_rate = sample_rate;
    set->taps = taps;
    set->count = count;
    *out = set;
    return AUDIO_OK;
}
static u32 read_u32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static f32 read_f32(const u8 *p) {
    u32 bits = read_u32(p);
    f32 v;
    memcpy(&v, &bits, sizeof(v));
    return v;
}

AudioResult audio_hrtf_set_parse(const void *bytes, usize size, AudioHrtfSet **out) {
    const u8 *b = (const u8 *)bytes;
    u32 rate, taps, count;
    u64 want;
    AudioHrtfDirection *dirs;
    f32 *left, *right;
    AudioResult res;
    if (!b || !out || size < AUDIO_HRTF_FILE_HEADER_BYTES) return AUDIO_INVALID;
    if (read_u32(b) != AUDIO_HRTF_FILE_MAGIC || read_u32(b + 4) != AUDIO_HRTF_FILE_VERSION) {
        return AUDIO_INVALID;
    }
    rate = read_u32(b + 8);
    taps = read_u32(b + 12);
    count = read_u32(b + 16);
    if (!shape_valid(rate, taps, count)) return AUDIO_INVALID;
    want = (u64)AUDIO_HRTF_FILE_HEADER_BYTES + (u64)count * (8u + 8u * (u64)taps);
    if ((u64)size != want) return AUDIO_INVALID;
    dirs = (AudioHrtfDirection *)malloc((usize)count * sizeof(*dirs));
    left = (f32 *)malloc((usize)count * taps * sizeof(f32));
    right = (f32 *)malloc((usize)count * taps * sizeof(f32));
    if (!dirs || !left || !right) {
        free(dirs);
        free(left);
        free(right);
        return AUDIO_OVERLOAD;
    }
    for (u32 i = 0; i < count; i++) {
        const u8 *p = b + AUDIO_HRTF_FILE_HEADER_BYTES + (usize)i * (8u + 8u * (usize)taps);
        dirs[i].azimuth = read_f32(p);
        dirs[i].elevation = read_f32(p + 4);
        for (u32 k = 0; k < taps; k++) {
            left[(usize)i * taps + k] = read_f32(p + 8u + 4u * (usize)k);
            right[(usize)i * taps + k] = read_f32(p + 8u + 4u * ((usize)taps + k));
        }
    }
    res = audio_hrtf_set_create(rate, taps, count, dirs, left, right, out);
    free(dirs);
    free(left);
    free(right);
    return res;
}

u32 audio_hrtf_set_count(const AudioHrtfSet *set) { return set ? set->count : 0u; }
u32 audio_hrtf_set_taps(const AudioHrtfSet *set) { return set ? set->taps : 0u; }
u32 audio_hrtf_set_sample_rate(const AudioHrtfSet *set) { return set ? set->sample_rate : 0u; }

const f32 *audio_hrtf_set_left(const AudioHrtfSet *set, u32 index) {
    return set && index < set->count ? set->left + (usize)index * set->taps : NULL;
}

const f32 *audio_hrtf_set_right(const AudioHrtfSet *set, u32 index) {
    return set && index < set->count ? set->right + (usize)index * set->taps : NULL;
}

bool audio_hrtf_set_direction(const AudioHrtfSet *set, u32 index, AudioHrtfDirection *out) {
    if (!set || !out || index >= set->count) return false;
    *out = set->directions[index];
    return true;
}

u32 audio_hrtf_set_nearest(const AudioHrtfSet *set, f32 azimuth, f32 elevation) {
    double v[3], best_dot = -INFINITY;
    u32 best = UINT32_MAX;
    if (!set || !angles_valid(azimuth, elevation)) return UINT32_MAX;
    unit_vector(azimuth, elevation, v);
    for (u32 i = 0; i < set->count; i++) {
        const double *w = set->vectors + 3u * i;
        double dot = v[0] * w[0] + v[1] * w[1] + v[2] * w[2];
        if (dot > best_dot) {
            best_dot = dot;
            best = i;
        }
    }
    return best;
}
/* One ear of the spherical head: `cos_theta` is the cosine of the angle
 * between the source and the ear axis, `abs_az` the source azimuth's
 * magnitude and `el` its elevation, both in degrees. */
static void head_ear(u32 sample_rate, u32 taps, double cos_theta, double abs_az, double el, double *ir) {
    static const double rho[PINNA_ECHOES] = {0.5, -1.0, 0.5, -0.25, 0.25};
    static const double a_n[PINNA_ECHOES] = {1.0, 5.0, 5.0, 5.0, 5.0};
    static const double b_n[PINNA_ECHOES] = {2.0, 4.0, 7.0, 11.0, 13.0};
    static const double d_n[PINNA_ECHOES] = {1.0, 0.5, 0.5, 0.5, 0.5};
    const double fs = (double)sample_rate, head = HEAD_RADIUS_M / SOUND_SPEED_MPS;
    const double theta = acos(cos_theta < -1.0 ? -1.0 : (cos_theta > 1.0 ? 1.0 : cos_theta));
    const double half_az = abs_az * HRTF_PI / 360.0, up = (90.0 - el) * HRTF_PI / 180.0;
    double tau, alpha, k, b0, b1, a1, x1 = 0.0, y1 = 0.0;
    long onset;
    memset(ir, 0, (usize)taps * sizeof(*ir));
    tau = theta < HRTF_PI / 2.0 ? -head * cos(theta) : head * (theta - HRTF_PI / 2.0);
    onset = lrint((tau + head) * fs);
    if (onset < 0 || (u32)onset >= taps) return;
    ir[onset] = 1.0;
    for (u32 n = 0; n < PINNA_ECHOES; n++) {
        double t = (a_n[n] * cos(half_az) * sin(d_n[n] * up) + b_n[n]) * fs / PINNA_REFERENCE_RATE;
        double at = (double)onset + t, whole = floor(at), frac = at - whole;
        long i = (long)whole;
        if (i >= 0 && (u32)i < taps) ir[i] += rho[n] * (1.0 - frac);
        if (i + 1 >= 0 && (u32)(i + 1) < taps) ir[i + 1] += rho[n] * frac;
    }
    alpha = (1.0 + SHADOW_ALPHA_MIN / 2.0) + (1.0 - SHADOW_ALPHA_MIN / 2.0) * cos(theta / SHADOW_THETA_MIN_RAD * HRTF_PI);
    k = fs * head; /* fs / omega0 with omega0 = c / a */
    b0 = (1.0 + alpha * k) / (1.0 + k);
    b1 = (1.0 - alpha * k) / (1.0 + k);
    a1 = (1.0 - k) / (1.0 + k);
    for (u32 i = 0; i < taps; i++) {
        double x = ir[i], y = b0 * x + b1 * x1 - a1 * y1;
        x1 = x;
        y1 = y;
        ir[i] = y;
    }
}

AudioResult audio_hrtf_set_create_spherical_head(u32 sample_rate, u32 taps, AudioHrtfSet **out) {
    enum { kElevations = 9, kAzimuths = 24, kCount = kElevations * kAzimuths + 1 };
    AudioHrtfDirection dirs[kCount];
    double *ir, *left, *right, peak = 0.0;
    f32 *lf, *rf;
    usize samples;
    AudioResult res;
    u32 n = 0;
    if (!out || sample_rate < AUDIO_HRTF_MIN_SAMPLE_RATE || sample_rate > AUDIO_HRTF_MAX_SAMPLE_RATE ||
        taps < 1u || taps > AUDIO_HRTF_MAX_TAPS) {
        return AUDIO_INVALID;
    }
    for (int e = 0; e < kElevations; e++) {
        for (int a = 0; a < kAzimuths; a++) {
            dirs[n].azimuth = (f32)(-165 + 15 * a);
            dirs[n].elevation = (f32)(-45 + 15 * e);
            n++;
        }
    }
    dirs[n].azimuth = 0.0f;
    dirs[n].elevation = 90.0f;
    samples = (usize)kCount * taps;
    ir = (double *)malloc((usize)taps * sizeof(double));
    left = (double *)malloc(samples * sizeof(double));
    right = (double *)malloc(samples * sizeof(double));
    lf = (f32 *)malloc(samples * sizeof(f32));
    rf = (f32 *)malloc(samples * sizeof(f32));
    if (!ir || !left || !right || !lf || !rf) {
        res = AUDIO_OVERLOAD;
        goto done;
    }
    for (u32 i = 0; i < (u32)kCount; i++) {
        double az = fabs((double)dirs[i].azimuth), el = (double)dirs[i].elevation;
        double lateral = cos(el * HRTF_PI / 180.0) * sin(az * HRTF_PI / 180.0);
        double *near_ear = dirs[i].azimuth > 0.0f ? right : left;
        double *far_ear = dirs[i].azimuth > 0.0f ? left : right;
        head_ear(sample_rate, taps, lateral, az, el, near_ear + (usize)i * taps);
        if (az == 180.0) { /* sin(pi) is not 0: copy so both ears match; at 0 they already do */
            memcpy(far_ear + (usize)i * taps, near_ear + (usize)i * taps, (usize)taps * sizeof(double));
        } else {
            head_ear(sample_rate, taps, -lateral, az, el, far_ear + (usize)i * taps);
        }
    }
    for (usize i = 0; i < samples; i++) {
        if (fabs(left[i]) > peak) peak = fabs(left[i]);
        if (fabs(right[i]) > peak) peak = fabs(right[i]);
    }
    if (peak <= 0.0) peak = 1.0;
    for (usize i = 0; i < samples; i++) {
        lf[i] = (f32)(left[i] / peak);
        rf[i] = (f32)(right[i] / peak);
    }
    res = audio_hrtf_set_create(sample_rate, taps, (u32)kCount, dirs, lf, rf, out);
done:
    free(ir);
    free(left);
    free(right);
    free(lf);
    free(rf);
    return res;
}

AudioResult audio_hrtf_renderer_init(AudioHrtfRenderer *r, const AudioHrtfSet *set) {
    if (!r || !set) return AUDIO_INVALID;
    memset(r, 0, sizeof(*r));
    r->set = set;
    r->taps = set->taps;
    r->current = r->next = audio_hrtf_set_nearest(set, 0.0f, 0.0f);
    r->pending = UINT32_MAX;
    return AUDIO_OK;
}

AudioResult audio_hrtf_renderer_set_direction(AudioHrtfRenderer *r, f32 azimuth, f32 elevation) {
    u32 idx;
    if (!r || !r->set) return AUDIO_INVALID;
    idx = audio_hrtf_set_nearest(r->set, azimuth, elevation);
    if (idx == UINT32_MAX) return AUDIO_INVALID;
    if (!r->started) {
        r->current = r->next = idx;
    } else if (r->next != r->current) {
        r->pending = idx;
    } else {
        r->next = idx; /* == current: stays idle */
        r->fade = 0u;
        r->pending = UINT32_MAX;
    }
    return AUDIO_OK;
}

static f32 convolve(const f32 *ir, const f32 *window_end, u32 taps) {
    f32 y = 0.0f;
    for (u32 k = 0; k < taps; k++) y += ir[k] * window_end[-(i32)k];
    return y;
}

void audio_hrtf_renderer_process(AudioHrtfRenderer *r, const f32 *mono, f32 *stereo, u32 frames) {
    if (!r || !r->set || !mono || !stereo) return;
    for (u32 n = 0; n < frames; n++) {
        const u32 taps = r->taps;
        const f32 *end;
        const f32 *cl, *cr;
        f32 yl, yr;
        if (r->next == r->current && r->pending != UINT32_MAX) {
            if (r->pending != r->current) {
                r->next = r->pending;
                r->fade = 0u;
            }
            r->pending = UINT32_MAX;
        }
        r->history[r->cursor] = r->history[r->cursor + taps] = mono[n];
        end = r->history + r->cursor + taps;
        r->cursor = r->cursor + 1u == taps ? 0u : r->cursor + 1u;
        cl = r->set->left + (usize)r->current * taps;
        cr = r->set->right + (usize)r->current * taps;
        yl = convolve(cl, end, taps);
        yr = convolve(cr, end, taps);
        if (r->next != r->current) {
            const f32 *nl = r->set->left + (usize)r->next * taps;
            const f32 *nr = r->set->right + (usize)r->next * taps;
            f32 bl = convolve(nl, end, taps), br = convolve(nr, end, taps);
            r->fade++;
            if (r->fade >= AUDIO_HRTF_FADE_FRAMES) {
                yl = bl;
                yr = br;
                r->current = r->next;
                r->fade = 0u;
            } else {
                f32 w = (f32)r->fade / (f32)AUDIO_HRTF_FADE_FRAMES;
                yl += (bl - yl) * w;
                yr += (br - yr) * w;
            }
        }
        stereo[2u * n] = yl;
        stereo[2u * n + 1u] = yr;
        r->started = true;
    }
}
