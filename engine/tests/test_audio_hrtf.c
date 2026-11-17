/* audio_hrtf: HRTF sets (caller arrays, BHRT files, the spherical-head
 * model) and the mono-to-stereo renderer, checked against double-precision
 * reference convolutions. */
#include "test_framework.h"

#include <audio/audio_hrtf.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TAPS 7u

static u32 g_seed = 0x2545f491u;

static f32 noise(void) {
    g_seed = g_seed * 1664525u + 1013904223u;
    return (f32)((double)(g_seed >> 8) / 8388608.0 - 1.0);
}

/* Directions of the small test set and their impulse responses. */
static const AudioHrtfDirection k_dirs[3] = {{0.0f, 0.0f}, {90.0f, 0.0f}, {-90.0f, 0.0f}};
static f32 g_left[3 * TAPS], g_right[3 * TAPS];

static AudioHrtfSet *small_set(void) {
    AudioHrtfSet *set = NULL;
    g_seed = 0x1234567u;
    for (u32 i = 0; i < 3u * TAPS; i++) {
        g_left[i] = noise();
        g_right[i] = noise();
    }
    if (audio_hrtf_set_create(48000u, TAPS, 3u, k_dirs, g_left, g_right, &set) != AUDIO_OK) return NULL;
    return set;
}

/* y[n] of filter `ir` on x, in double, with zero history before x[0] */
static double conv_at(const f32 *ir, const f32 *x, u32 n) {
    double y = 0.0;
    for (u32 k = 0; k < TAPS && k <= n; k++) y += (double)ir[k] * (double)x[n - k];
    return y;
}

static bool near_f(double got, double want, double tol, const char *what, u32 frame) {
    if (fabs(got - want) <= tol) return true;
    printf("    %s frame %u: got %.9f want %.9f\n", what, frame, got, want);
    return false;
}

TEST(the_renderer_matches_a_direct_convolution_across_uneven_calls) {
    AudioHrtfSet *set = small_set();
    AudioHrtfRenderer r;
    static f32 x[300], out[600];
    const u32 chunks[] = {1u, 5u, 64u, 230u};
    u32 at = 0;
    ASSERT_NOT_NULL(set);
    for (u32 i = 0; i < 300u; i++) x[i] = noise();
    ASSERT_EQ(audio_hrtf_renderer_init(&r, set), AUDIO_OK);
    for (u32 c = 0; c < 4u; c++) {
        audio_hrtf_renderer_process(&r, x + at, out + 2u * at, chunks[c]);
        at += chunks[c];
    }
    ASSERT_EQ(at, 300u);
    for (u32 n = 0; n < 300u; n++) {
        ASSERT_TRUE(near_f(out[2u * n], conv_at(g_left, x, n), 1e-5, "left", n));
        ASSERT_TRUE(near_f(out[2u * n + 1u], conv_at(g_right, x, n), 1e-5, "right", n));
    }
    audio_hrtf_set_destroy(set);
}

/* the expected output of a renderer that fades from filter a to b, frame
 * `i` (1-based) of the fade */
static double fade_at(u32 a, u32 b, u32 i, const f32 *ears, const f32 *x, u32 n) {
    double ya = conv_at(ears + a * TAPS, x, n), yb = conv_at(ears + b * TAPS, x, n);
    double w = (double)i / (double)AUDIO_HRTF_FADE_FRAMES;
    return ya + (yb - ya) * w;
}

TEST(a_direction_change_crossfades_and_a_change_mid_fade_waits) {
    AudioHrtfSet *set = small_set();
    AudioHrtfRenderer r;
    static f32 x[220], out[440];
    const u32 F = AUDIO_HRTF_FADE_FRAMES;
    ASSERT_NOT_NULL(set);
    for (u32 i = 0; i < 220u; i++) x[i] = noise();
    ASSERT_EQ(audio_hrtf_renderer_init(&r, set), AUDIO_OK);
    audio_hrtf_renderer_process(&r, x, out, 10u);                  /* front */
    ASSERT_EQ(audio_hrtf_renderer_set_direction(&r, 80.0f, 5.0f), AUDIO_OK); /* nearest: right */
    audio_hrtf_renderer_process(&r, x + 10, out + 20, 20u);
    ASSERT_EQ(audio_hrtf_renderer_set_direction(&r, -100.0f, 0.0f), AUDIO_OK); /* left, mid-fade */
    audio_hrtf_renderer_process(&r, x + 30, out + 60, 190u);
    for (u32 n = 0; n < 220u; n++) {
        double wl, wr;
        if (n < 10u) {
            wl = conv_at(g_left, x, n);
            wr = conv_at(g_right, x, n);
        } else if (n < 10u + F) {                      /* front -> right, i = n - 9 */
            wl = fade_at(0u, 1u, n - 9u, g_left, x, n);
            wr = fade_at(0u, 1u, n - 9u, g_right, x, n);
        } else if (n < 10u + 2u * F) {                 /* right -> left starts right after */
            wl = fade_at(1u, 2u, n - 9u - F, g_left, x, n);
            wr = fade_at(1u, 2u, n - 9u - F, g_right, x, n);
        } else {
            wl = conv_at(g_left + 2u * TAPS, x, n);
            wr = conv_at(g_right + 2u * TAPS, x, n);
        }
        ASSERT_TRUE(near_f(out[2u * n], wl, 1e-5, "left", n));
        ASSERT_TRUE(near_f(out[2u * n + 1u], wr, 1e-5, "right", n));
    }
    /* the last frame of a fade is exactly the new filter's output */
    {
        AudioHrtfRenderer q;
        static f32 y[2u * (1u + AUDIO_HRTF_FADE_FRAMES)];
        f32 one[1] = {1.0f};
        ASSERT_EQ(audio_hrtf_renderer_init(&q, set), AUDIO_OK);
        audio_hrtf_renderer_process(&q, one, y, 1u);
        ASSERT_EQ(audio_hrtf_renderer_set_direction(&q, 90.0f, 0.0f), AUDIO_OK);
        memset(x, 0, sizeof(x));
        audio_hrtf_renderer_process(&q, x, y + 2, F);
        /* frame F of the fade sees the impulse F frames back: past the taps, so 0 */
        ASSERT_TRUE(y[2u * F] == 0.0f && y[2u * F + 1u] == 0.0f);
    }
    audio_hrtf_set_destroy(set);
}

TEST(the_first_direction_applies_at_once_and_a_repeat_starts_no_fade) {
    AudioHrtfSet *set = small_set();
    AudioHrtfRenderer r;
    static f32 x[100], out[200];
    ASSERT_NOT_NULL(set);
    for (u32 i = 0; i < 100u; i++) x[i] = noise();
    ASSERT_EQ(audio_hrtf_renderer_init(&r, set), AUDIO_OK);
    ASSERT_EQ(audio_hrtf_renderer_set_direction(&r, 90.0f, 0.0f), AUDIO_OK);
    ASSERT_EQ(audio_hrtf_renderer_set_direction(&r, -90.0f, 0.0f), AUDIO_OK);
    audio_hrtf_renderer_process(&r, x, out, 40u);
    /* the same filter again, and a direction mapping to it: no fade */
    ASSERT_EQ(audio_hrtf_renderer_set_direction(&r, -85.0f, 3.0f), AUDIO_OK);
    audio_hrtf_renderer_process(&r, x + 40, out + 80, 60u);
    for (u32 n = 0; n < 100u; n++) {
        ASSERT_TRUE(near_f(out[2u * n], conv_at(g_left + 2u * TAPS, x, n), 1e-5, "left", n));
        ASSERT_TRUE(near_f(out[2u * n + 1u], conv_at(g_right + 2u * TAPS, x, n), 1e-5, "right", n));
    }
    /* out of range: refused, the renderer is unchanged */
    ASSERT_EQ(audio_hrtf_renderer_set_direction(&r, 181.0f, 0.0f), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_renderer_set_direction(&r, 0.0f, -91.0f), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_renderer_set_direction(&r, NAN, 0.0f), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_renderer_set_direction(NULL, 0.0f, 0.0f), AUDIO_INVALID);
    ASSERT_EQ(r.current, 2u);
    ASSERT_EQ(r.next, 2u);
    ASSERT_EQ(audio_hrtf_renderer_init(&r, NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_renderer_init(NULL, set), AUDIO_INVALID);
    audio_hrtf_set_destroy(set);
}

TEST(the_nearest_direction_wraps_azimuth_and_breaks_ties_by_index) {
    const AudioHrtfDirection dirs[6] = {{0.0f, 0.0f}, {90.0f, 0.0f}, {-90.0f, 0.0f},
                                        {180.0f, 0.0f}, {0.0f, 90.0f}, {45.0f, 0.0f}};
    static f32 l[6], rr[6];
    AudioHrtfSet *set = NULL;
    for (u32 i = 0; i < 6u; i++) l[i] = rr[i] = 0.5f;
    ASSERT_EQ(audio_hrtf_set_create(44100u, 1u, 6u, dirs, l, rr, &set), AUDIO_OK);
    for (u32 i = 0; i < 6u; i++) ASSERT_EQ(audio_hrtf_set_nearest(set, dirs[i].azimuth, dirs[i].elevation), i);
    ASSERT_EQ(audio_hrtf_set_nearest(set, 170.0f, 0.0f), 3u);
    ASSERT_EQ(audio_hrtf_set_nearest(set, -175.0f, 0.0f), 3u);
    ASSERT_EQ(audio_hrtf_set_nearest(set, -180.0f, 0.0f), 3u);
    ASSERT_EQ(audio_hrtf_set_nearest(set, 30.0f, 89.0f), 4u);
    ASSERT_EQ(audio_hrtf_set_nearest(set, 40.0f, 10.0f), 5u);
    ASSERT_EQ(audio_hrtf_set_nearest(set, -60.0f, -20.0f), 2u);
    ASSERT_EQ(audio_hrtf_set_nearest(set, 181.0f, 0.0f), UINT32_MAX);
    ASSERT_EQ(audio_hrtf_set_nearest(set, 0.0f, 90.5f), UINT32_MAX);
    ASSERT_EQ(audio_hrtf_set_nearest(set, INFINITY, 0.0f), UINT32_MAX);
    ASSERT_EQ(audio_hrtf_set_nearest(NULL, 0.0f, 0.0f), UINT32_MAX);
    audio_hrtf_set_destroy(set);
    {
        /* straight ahead is exactly as far from either side: the lower index wins */
        const AudioHrtfDirection lr[2] = {{90.0f, 0.0f}, {-90.0f, 0.0f}};
        const AudioHrtfDirection rl[2] = {{-90.0f, 0.0f}, {90.0f, 0.0f}};
        ASSERT_EQ(audio_hrtf_set_create(44100u, 1u, 2u, lr, l, rr, &set), AUDIO_OK);
        ASSERT_EQ(audio_hrtf_set_nearest(set, 0.0f, 0.0f), 0u);
        audio_hrtf_set_destroy(set);
        ASSERT_EQ(audio_hrtf_set_create(44100u, 1u, 2u, rl, l, rr, &set), AUDIO_OK);
        ASSERT_EQ(audio_hrtf_set_nearest(set, 0.0f, 0.0f), 0u);
        audio_hrtf_set_destroy(set);
    }
}

TEST(create_copies_its_input_and_refuses_every_invalid_argument) {
    AudioHrtfSet *set = small_set();
    AudioHrtfSet *out = (AudioHrtfSet *)(uintptr_t)1u;
    AudioHrtfDirection d[3];
    AudioHrtfDirection got;
    f32 keep = g_left[TAPS + 2u];
    ASSERT_NOT_NULL(set);
    g_left[TAPS + 2u] = 3.0f;          /* the set holds a copy */
    ASSERT_TRUE(audio_hrtf_set_left(set, 1u)[2] == keep);
    g_left[TAPS + 2u] = keep;
    ASSERT_TRUE(audio_hrtf_set_right(set, 2u)[TAPS - 1u] == g_right[3u * TAPS - 1u]);
    ASSERT_EQ(audio_hrtf_set_count(set), 3u);
    ASSERT_EQ(audio_hrtf_set_taps(set), TAPS);
    ASSERT_EQ(audio_hrtf_set_sample_rate(set), 48000u);
    ASSERT_TRUE(audio_hrtf_set_direction(set, 2u, &got) && got.azimuth == -90.0f && got.elevation == 0.0f);
    ASSERT_FALSE(audio_hrtf_set_direction(set, 3u, &got));
    ASSERT_TRUE(audio_hrtf_set_left(set, 3u) == NULL);
    ASSERT_TRUE(audio_hrtf_set_right(NULL, 0u) == NULL);
    ASSERT_EQ(audio_hrtf_set_count(NULL), 0u);
    audio_hrtf_set_destroy(set);
    audio_hrtf_set_destroy(NULL);

    memcpy(d, k_dirs, sizeof(d));
#define REFUSED(call) do { out = (AudioHrtfSet *)(uintptr_t)1u; ASSERT_EQ((call), AUDIO_INVALID); \
        ASSERT_TRUE(out == (AudioHrtfSet *)(uintptr_t)1u); } while (0)
    REFUSED(audio_hrtf_set_create(7999u, TAPS, 3u, d, g_left, g_right, &out));
    REFUSED(audio_hrtf_set_create(192001u, TAPS, 3u, d, g_left, g_right, &out));
    REFUSED(audio_hrtf_set_create(48000u, 0u, 3u, d, g_left, g_right, &out));
    REFUSED(audio_hrtf_set_create(48000u, AUDIO_HRTF_MAX_TAPS + 1u, 3u, d, g_left, g_right, &out));
    REFUSED(audio_hrtf_set_create(48000u, TAPS, 0u, d, g_left, g_right, &out));
    REFUSED(audio_hrtf_set_create(48000u, TAPS, AUDIO_HRTF_MAX_DIRECTIONS + 1u, d, g_left, g_right, &out));
    REFUSED(audio_hrtf_set_create(48000u, TAPS, 3u, NULL, g_left, g_right, &out));
    REFUSED(audio_hrtf_set_create(48000u, TAPS, 3u, d, NULL, g_right, &out));
    REFUSED(audio_hrtf_set_create(48000u, TAPS, 3u, d, g_left, NULL, &out));
    ASSERT_EQ(audio_hrtf_set_create(48000u, TAPS, 3u, d, g_left, g_right, NULL), AUDIO_INVALID);
    {
        const f32 bad_angles[][2] = {{180.5f, 0.0f}, {-180.5f, 0.0f}, {0.0f, 90.5f}, {0.0f, -90.5f},
                                     {NAN, 0.0f}, {0.0f, INFINITY}};
        for (u32 i = 0; i < sizeof(bad_angles) / sizeof(bad_angles[0]); i++) {
            d[1].azimuth = bad_angles[i][0];
            d[1].elevation = bad_angles[i][1];
            REFUSED(audio_hrtf_set_create(48000u, TAPS, 3u, d, g_left, g_right, &out));
        }
        memcpy(d, k_dirs, sizeof(d));
    }
    {
        /* coincident directions: the same angles, -180 vs 180, and two azimuths straight up */
        const AudioHrtfDirection twins[][2] = {{{90.0f, 0.0f}, {90.0f, 0.0f}},
                                               {{180.0f, 0.0f}, {-180.0f, 0.0f}},
                                               {{0.0f, 90.0f}, {120.0f, 90.0f}}};
        for (u32 i = 0; i < 3u; i++) {
            d[1] = twins[i][0];
            d[2] = twins[i][1];
            REFUSED(audio_hrtf_set_create(48000u, TAPS, 3u, d, g_left, g_right, &out));
        }
        memcpy(d, k_dirs, sizeof(d));
    }
    {
        const f32 bad_samples[] = {4.5f, -4.01f, NAN, INFINITY};
        for (u32 i = 0; i < 4u; i++) {
            f32 l = g_left[2u * TAPS + 3u], r = g_right[0];
            g_left[2u * TAPS + 3u] = bad_samples[i];
            REFUSED(audio_hrtf_set_create(48000u, TAPS, 3u, d, g_left, g_right, &out));
            g_left[2u * TAPS + 3u] = l;
            g_right[0] = bad_samples[i];
            REFUSED(audio_hrtf_set_create(48000u, TAPS, 3u, d, g_left, g_right, &out));
            g_right[0] = r;
        }
        g_left[0] = 4.0f; /* the limit itself is allowed */
        ASSERT_EQ(audio_hrtf_set_create(8000u, TAPS, 3u, d, g_left, g_right, &out), AUDIO_OK);
        audio_hrtf_set_destroy(out);
    }
#undef REFUSED
}

static void le32(u8 *p, u32 v) { for (int i = 0; i < 4; i++) p[i] = (u8)(v >> (8 * i)); }
static void lef(u8 *p, f32 v) { u32 b; memcpy(&b, &v, 4u); le32(p, b); }

/* BHRT v1 bytes for 2 directions of 2 taps */
static usize build_file(u8 *b) {
    const f32 vals[2][6] = {{-30.0f, 15.0f, 0.25f, -0.5f, 1.0f, 0.125f},
                            {150.0f, -40.0f, 2.0f, -4.0f, 0.0f, 3.5f}};
    le32(b, AUDIO_HRTF_FILE_MAGIC);
    le32(b + 4, 1u);
    le32(b + 8, 44100u);
    le32(b + 12, 2u);
    le32(b + 16, 2u);
    for (u32 i = 0; i < 2u; i++) {
        for (u32 k = 0; k < 6u; k++) lef(b + 20u + 24u * i + 4u * k, vals[i][k]);
    }
    return 20u + 2u * 24u;
}

TEST(a_bhrt_file_round_trips_and_every_bad_byte_is_refused) {
    u8 b[96];
    usize n = build_file(b);
    AudioHrtfSet *set = NULL;
    AudioHrtfDirection d;
    ASSERT_EQ(n, 68u);
    ASSERT_TRUE(b[0] == 'B' && b[1] == 'H' && b[2] == 'R' && b[3] == 'T');
    ASSERT_EQ(audio_hrtf_set_parse(b, n, &set), AUDIO_OK);
    ASSERT_EQ(audio_hrtf_set_count(set), 2u);
    ASSERT_EQ(audio_hrtf_set_taps(set), 2u);
    ASSERT_EQ(audio_hrtf_set_sample_rate(set), 44100u);
    ASSERT_TRUE(audio_hrtf_set_direction(set, 1u, &d) && d.azimuth == 150.0f && d.elevation == -40.0f);
    ASSERT_TRUE(audio_hrtf_set_left(set, 0u)[0] == 0.25f && audio_hrtf_set_left(set, 0u)[1] == -0.5f);
    ASSERT_TRUE(audio_hrtf_set_right(set, 0u)[0] == 1.0f && audio_hrtf_set_right(set, 0u)[1] == 0.125f);
    ASSERT_TRUE(audio_hrtf_set_left(set, 1u)[1] == -4.0f && audio_hrtf_set_right(set, 1u)[1] == 3.5f);
    audio_hrtf_set_destroy(set);
    for (usize k = 0; k < n; k++) {
        set = (AudioHrtfSet *)(uintptr_t)1u;
        ASSERT_EQ(audio_hrtf_set_parse(b, k, &set), AUDIO_INVALID);
        ASSERT_TRUE(set == (AudioHrtfSet *)(uintptr_t)1u);
    }
    b[n] = 0u;
    ASSERT_EQ(audio_hrtf_set_parse(b, n + 1u, &set), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_set_parse(NULL, n, &set), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_set_parse(b, n, NULL), AUDIO_INVALID);
    {
        const struct { usize at; u32 v; bool is_float; f32 f; } bad[] = {
            {0u, 0x54524843u, false, 0.0f},  /* magic */
            {4u, 2u, false, 0.0f},           /* version */
            {4u, 0u, false, 0.0f},
            {8u, 7999u, false, 0.0f},        /* sample rate */
            {8u, 192001u, false, 0.0f},
            {12u, 0u, false, 0.0f},          /* taps: size then disagrees as well */
            {12u, 1u, false, 0.0f},
            {12u, 129u, false, 0.0f},
            {16u, 0u, false, 0.0f},          /* count */
            {16u, 3u, false, 0.0f},
            {16u, 0xffffffffu, false, 0.0f},
            {20u, 0u, true, 181.0f},         /* azimuth */
            {20u, 0u, true, NAN},
            {24u, 0u, true, -91.0f},         /* elevation */
            {28u, 0u, true, 4.5f},           /* a left sample */
            {40u, 0u, true, INFINITY},       /* a right sample of direction 1... */
            {64u, 0u, true, -5.0f},          /* ...and the last byte group of the file */
        };
        for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
            build_file(b);
            if (bad[i].is_float) lef(b + bad[i].at, bad[i].f); else le32(b + bad[i].at, bad[i].v);
            set = (AudioHrtfSet *)(uintptr_t)1u;
            if (audio_hrtf_set_parse(b, n, &set) != AUDIO_INVALID) {
                printf("    corruption %u at %zu was accepted\n", i, (size_t)bad[i].at);
                ASSERT_TRUE(false);
            }
            ASSERT_TRUE(set == (AudioHrtfSet *)(uintptr_t)1u);
        }
        /* two coincident directions */
        build_file(b);
        lef(b + 44u, -30.0f);
        lef(b + 48u, 15.0f);
        ASSERT_EQ(audio_hrtf_set_parse(b, n, &set), AUDIO_INVALID);
    }
}

static u32 onset(const f32 *ir, u32 taps) {
    for (u32 i = 0; i < taps; i++) {
        if (fabsf(ir[i]) > 1e-9f) return i;
    }
    return taps;
}

/* energy of DFT bins lo..hi of a `taps`-long impulse response */
static double band_energy(const f32 *ir, u32 taps, u32 lo, u32 hi) {
    double sum = 0.0;
    for (u32 b = lo; b <= hi; b++) {
        double re = 0.0, im = 0.0;
        for (u32 n = 0; n < taps; n++) {
            double a = -2.0 * 3.14159265358979323846 * (double)b * (double)n / (double)taps;
            re += (double)ir[n] * cos(a);
            im += (double)ir[n] * sin(a);
        }
        sum += re * re + im * im;
    }
    return sum;
}

/* high (about 8-16 kHz at 48 kHz, 128 taps) over low (below about 1 kHz) */
static double hf_over_lf(const f32 *ir) { return band_energy(ir, 128u, 22u, 42u) / band_energy(ir, 128u, 0u, 2u); }

/* |H(-1)| of a 128-tap response */
static double nyquist_gain(const f32 *ir) {
    double s = 0.0;
    for (u32 n = 0; n < 128u; n++) s += (n & 1u) ? -(double)ir[n] : (double)ir[n];
    return fabs(s);
}

/* Brown-Duda: alpha_min 0.1 at theta_min 150 degrees */
static double shadow_alpha(double theta) { return 1.05 + 0.95 * cos(theta * 180.0 / 150.0); }

TEST(create_accepts_the_most_directions_and_refuses_one_more) {
    static AudioHrtfDirection d[AUDIO_HRTF_MAX_DIRECTIONS + 1u];
    static f32 s[AUDIO_HRTF_MAX_DIRECTIONS + 1u];
    AudioHrtfSet *set = NULL, *out = (AudioHrtfSet *)(uintptr_t)1u;
    for (u32 i = 0; i <= AUDIO_HRTF_MAX_DIRECTIONS; i++) {
        d[i].azimuth = -180.0f + 0.125f * (f32)i;
        d[i].elevation = 0.0f;
        s[i] = 0.5f;
    }
    ASSERT_EQ(audio_hrtf_set_create(48000u, 1u, AUDIO_HRTF_MAX_DIRECTIONS, d, s, s, &set), AUDIO_OK);
    ASSERT_EQ(audio_hrtf_set_count(set), AUDIO_HRTF_MAX_DIRECTIONS);
    audio_hrtf_set_destroy(set);
    ASSERT_EQ(audio_hrtf_set_create(48000u, 1u, AUDIO_HRTF_MAX_DIRECTIONS + 1u, d, s, s, &out), AUDIO_INVALID);
    ASSERT_TRUE(out == (AudioHrtfSet *)(uintptr_t)1u);
}

TEST(the_spherical_head_model_has_the_expected_symmetries_and_cues) {
    AudioHrtfSet *set = NULL, *out = (AudioHrtfSet *)(uintptr_t)1u;
    const double head = 0.0875 / 343.0 * 48000.0;
    u32 front, idx, mirror;
    f32 peak = 0.0f;
    ASSERT_EQ(audio_hrtf_set_create_spherical_head(7999u, 64u, &out), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_set_create_spherical_head(48000u, 0u, &out), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_set_create_spherical_head(48000u, 129u, &out), AUDIO_INVALID);
    ASSERT_EQ(audio_hrtf_set_create_spherical_head(48000u, 64u, NULL), AUDIO_INVALID);
    ASSERT_TRUE(out == (AudioHrtfSet *)(uintptr_t)1u);
    ASSERT_EQ(audio_hrtf_set_create_spherical_head(48000u, 128u, &set), AUDIO_OK);
    ASSERT_EQ(audio_hrtf_set_count(set), 217u);
    ASSERT_EQ(audio_hrtf_set_taps(set), 128u);
    for (u32 i = 0; i < audio_hrtf_set_count(set); i++) {
        for (u32 k = 0; k < 128u; k++) {
            f32 a = fabsf(audio_hrtf_set_left(set, i)[k]), b = fabsf(audio_hrtf_set_right(set, i)[k]);
            if (a > peak) peak = a;
            if (b > peak) peak = b;
        }
    }
    ASSERT_TRUE(peak > 0.5f && peak <= 1.0f);
    front = audio_hrtf_set_nearest(set, 0.0f, 0.0f);
    ASSERT_TRUE(memcmp(audio_hrtf_set_left(set, front), audio_hrtf_set_right(set, front), 128u * 4u) == 0);
    for (u32 e = 0; e < 3u; e++) {
        const f32 el[] = {-30.0f, 0.0f, 45.0f};
        idx = audio_hrtf_set_nearest(set, 180.0f, el[e]); /* straight behind */
        ASSERT_TRUE(memcmp(audio_hrtf_set_left(set, idx), audio_hrtf_set_right(set, idx), 128u * 4u) == 0);
    }
    {
        const f32 az[] = {30.0f, 60.0f, 90.0f, 135.0f};
        const f32 el[] = {0.0f, 15.0f, -45.0f, 60.0f};
        for (u32 a = 0; a < 4u; a++) {
            for (u32 e = 0; e < 4u; e++) {
                idx = audio_hrtf_set_nearest(set, az[a], el[e]);
                mirror = audio_hrtf_set_nearest(set, -az[a], el[e]);
                ASSERT_TRUE(idx != mirror);
                ASSERT_TRUE(memcmp(audio_hrtf_set_left(set, idx), audio_hrtf_set_right(set, mirror), 512u) == 0);
                ASSERT_TRUE(memcmp(audio_hrtf_set_right(set, idx), audio_hrtf_set_left(set, mirror), 512u) == 0);
            }
        }
    }
    {
        /* a source on the right reaches the right ear first, by the Woodworth ITD */
        const f32 az[] = {30.0f, 60.0f, 90.0f};
        for (u32 a = 0; a < 3u; a++) {
            double p = sin((double)az[a] * 3.14159265358979323846 / 180.0);
            double want = head * (asin(p) + p);
            idx = audio_hrtf_set_nearest(set, az[a], 0.0f);
            {
                u32 l = onset(audio_hrtf_set_left(set, idx), 128u), r = onset(audio_hrtf_set_right(set, idx), 128u);
                ASSERT_TRUE(r < l);
                if (fabs((double)(l - r) - want) > 1.0) {
                    printf("    az %.0f: onset gap %u, Woodworth %.2f frames\n", (double)az[a], l - r, want);
                    ASSERT_TRUE(false);
                }
            }
        }
        /* the shadowed far ear keeps relatively less high-frequency energy */
        for (u32 a = 0; a < 3u; a++) {
            idx = audio_hrtf_set_nearest(set, az[a], 0.0f);
            ASSERT_TRUE(hf_over_lf(audio_hrtf_set_left(set, idx)) <
                        0.25 * hf_over_lf(audio_hrtf_set_right(set, idx)));
        }
    }
    {
        /* elevation changes the pinna echoes: the impulse responses differ */
        u32 up = audio_hrtf_set_nearest(set, 0.0f, 45.0f), down = audio_hrtf_set_nearest(set, 0.0f, -45.0f);
        double diff = 0.0;
        ASSERT_TRUE(up != front && down != front && up != down);
        for (u32 k = 0; k < 128u; k++) {
            diff += fabs((double)audio_hrtf_set_left(set, up)[k] - audio_hrtf_set_left(set, down)[k]);
            diff += fabs((double)audio_hrtf_set_left(set, up)[k] - audio_hrtf_set_left(set, front)[k]);
        }
        ASSERT_TRUE(diff > 0.1);
        ASSERT_EQ(audio_hrtf_set_nearest(set, 77.0f, 89.0f), audio_hrtf_set_nearest(set, -150.0f, 88.0f));
        {
            AudioHrtfDirection top;
            ASSERT_TRUE(audio_hrtf_set_direction(set, audio_hrtf_set_nearest(set, 0.0f, 90.0f), &top));
            ASSERT_TRUE(top.elevation == 90.0f);
        }
    }
    {
        /* the shadow and the pinna echoes keep DC: every response has the same sum */
        double first = 0.0;
        for (u32 i = 0; i < audio_hrtf_set_count(set); i++) {
            double sl = 0.0, sr = 0.0;
            for (u32 k = 0; k < 128u; k++) {
                sl += audio_hrtf_set_left(set, i)[k];
                sr += audio_hrtf_set_right(set, i)[k];
            }
            if (i == 0u) first = sl;
            ASSERT_TRUE(fabs(sl - first) < 1e-4 && fabs(sr - first) < 1e-4);
        }
        ASSERT_TRUE(first > 0.1);
    }
    {
        /* at Nyquist the shadow filter's gain is alpha(theta), theta the angle
         * between the source and the ear axis */
        const f32 az[] = {15.0f, 45.0f, 90.0f, 150.0f};
        const f32 el[] = {0.0f, 30.0f, -45.0f};
        for (u32 a = 0; a < 4u; a++) {
            for (u32 e = 0; e < 3u; e++) {
                double lat = cos((double)el[e] * 3.14159265358979323846 / 180.0) *
                             sin((double)az[a] * 3.14159265358979323846 / 180.0);
                double want = shadow_alpha(acos(-lat)) / shadow_alpha(acos(lat));
                idx = audio_hrtf_set_nearest(set, az[a], el[e]);
                ASSERT_TRUE(fabs(nyquist_gain(audio_hrtf_set_left(set, idx)) /
                                 nyquist_gain(audio_hrtf_set_right(set, idx)) - want) < 1e-3 * want);
            }
        }
    }
    {
        AudioHrtfRenderer r;
        ASSERT_EQ(audio_hrtf_renderer_init(&r, set), AUDIO_OK);
        ASSERT_EQ(r.current, front);
        ASSERT_EQ(r.next, front);
    }
    audio_hrtf_set_destroy(set);
}

TEST_MAIN_BEGIN()
    RUN_TEST(the_renderer_matches_a_direct_convolution_across_uneven_calls);
    RUN_TEST(a_direction_change_crossfades_and_a_change_mid_fade_waits);
    RUN_TEST(the_first_direction_applies_at_once_and_a_repeat_starts_no_fade);
    RUN_TEST(the_nearest_direction_wraps_azimuth_and_breaks_ties_by_index);
    RUN_TEST(create_copies_its_input_and_refuses_every_invalid_argument);
    RUN_TEST(a_bhrt_file_round_trips_and_every_bad_byte_is_refused);
    RUN_TEST(create_accepts_the_most_directions_and_refuses_one_more);
    RUN_TEST(the_spherical_head_model_has_the_expected_symmetries_and_cues);
TEST_MAIN_END()
