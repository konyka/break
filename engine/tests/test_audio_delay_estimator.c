/* audio_delay_estimator: validation, exact lags with gain and noise, an
 * inverted echo, not-ready and silent inputs, chunking and reset, a
 * brute-force model, the delay line, and alignment for the echo canceller. */
#include "test_framework.h"

#include <audio/audio_delay_estimator.h>
#include <audio/audio_echo_canceller.h>

#include <math.h>
#include <string.h>

#define N 20000u

static const double kPi = 3.14159265358979323846;
static u32 g_seed = 0x13579BDu;

static i16 noise(double amplitude) {
    g_seed = g_seed * 1664525u + 1013904223u;
    double u = (double)(g_seed >> 8) / 8388608.0 - 1.0;
    return (i16)lrint(u * amplitude);
}

static i16 g_ref[N], g_cap[N];

/* g_cap[n] = gain * g_ref[n - delay] + noise of `noise_amp` */
static void make_echo(u32 delay, double gain, double noise_amp) {
    for (u32 n = 0; n < N; ++n) g_ref[n] = noise(12000.0);
    for (u32 n = 0; n < N; ++n) {
        double v = n >= delay ? gain * g_ref[n - delay] : 0.0;
        if (noise_amp > 0.0) v += noise(noise_amp);
        g_cap[n] = (i16)lrint(v);
    }
}

static double sinc(double x) {
    return fabs(x) < 1e-12 ? 1.0 : sin(kPi * x) / (kPi * x);
}

/* Band-limited reference delay, using 33 sinc taps around the requested lag. */
static void make_fractional_echo(double delay, double gain) {
    for (u32 n = 0; n < N; ++n) g_ref[n] = noise(12000.0);
    const int center = (int)floor(delay);
    for (u32 n = 0; n < N; ++n) {
        double value = 0.0;
        for (int k = center - 16; k <= center + 16; ++k) {
            const int source = (int)n - k;
            if (source >= 0 && source < (int)N) value += g_ref[source] * sinc((double)k - delay);
        }
        g_cap[n] = (i16)lrint(gain * value);
    }
}

static AudioDelayEstimator *make_estimator(u32 max_delay, u32 window) {
    AudioDelayEstimatorConfig config = {max_delay, window};
    AudioDelayEstimator *est = NULL;
    if (audio_delay_estimator_create(&config, &est) != AUDIO_OK) return NULL;
    return est;
}

TEST(create_refuses_every_invalid_config)
{
    AudioDelayEstimator *sentinel = NULL;
    const AudioDelayEstimatorConfig valid = {10u, 16u};
    ASSERT_EQ(audio_delay_estimator_create(&valid, &sentinel), AUDIO_OK);
    AudioDelayEstimator *est = sentinel;
    const AudioDelayEstimatorConfig bad[] = {
        {0u, 256u}, {AUDIO_DELAY_ESTIMATOR_MAX_DELAY + 1u, 256u}, {100u, 15u},
        {100u, AUDIO_DELAY_ESTIMATOR_MAX_WINDOW + 1u}};
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        ASSERT_EQ(audio_delay_estimator_create(&bad[i], &est), AUDIO_INVALID);
        ASSERT_TRUE(est == sentinel);
    }
    ASSERT_EQ(audio_delay_estimator_create(NULL, &est), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_estimator_create(&bad[0], NULL), AUDIO_INVALID);
    const AudioDelayEstimatorConfig limits[2] = {
        {1u, AUDIO_DELAY_ESTIMATOR_MIN_WINDOW},
        {AUDIO_DELAY_ESTIMATOR_MAX_DELAY, AUDIO_DELAY_ESTIMATOR_MAX_WINDOW}};
    for (u32 i = 0; i < 2u; ++i) {
        ASSERT_EQ(audio_delay_estimator_create(&limits[i], &est), AUDIO_OK);
        ASSERT_TRUE(est != NULL && est != sentinel);
        audio_delay_estimator_destroy(est);
    }
    audio_delay_estimator_destroy(NULL);
    audio_delay_estimator_reset(NULL);
    u32 delay = 77u;
    double corr = 2.0;
    ASSERT_TRUE(!audio_delay_estimator_estimate(NULL, &delay, &corr));
    est = make_estimator(10u, 16u);
    ASSERT_TRUE(est != NULL);
    audio_delay_estimator_push_i16(NULL, g_ref, g_cap, 1u);
    audio_delay_estimator_push_i16(est, NULL, g_cap, 1u);
    audio_delay_estimator_push_i16(est, g_ref, NULL, 1u);
    ASSERT_TRUE(!audio_delay_estimator_estimate(est, NULL, &corr));
    ASSERT_TRUE(!audio_delay_estimator_estimate(est, &delay, NULL));
    ASSERT_EQ(delay, 77u);
    audio_delay_estimator_destroy(est);
    audio_delay_estimator_destroy(sentinel);
}

TEST(delayed_noise_gives_the_exact_lag)
{
    const u32 delays[4] = {0u, 1u, 237u, 800u};
    for (u32 i = 0; i < 4u; ++i) {
        AudioDelayEstimator *est = make_estimator(800u, 2048u);
        ASSERT_TRUE(est != NULL);
        make_echo(delays[i], 0.3, 1000.0);
        audio_delay_estimator_push_i16(est, g_ref, g_cap, N);
        u32 delay = 0u;
        double corr = 0.0;
        ASSERT_TRUE(audio_delay_estimator_estimate(est, &delay, &corr));
        ASSERT_EQ(delay, delays[i]);
        ASSERT_TRUE(corr > 0.9 && corr <= 1.0);
        audio_delay_estimator_destroy(est);
    }
}

TEST(an_inverted_echo_is_found_with_a_negative_correlation)
{
    AudioDelayEstimator *est = make_estimator(400u, 1024u);
    ASSERT_TRUE(est != NULL);
    make_echo(123u, -0.5, 0.0);
    audio_delay_estimator_push_i16(est, g_ref, g_cap, N);
    u32 delay = 0u;
    double corr = 0.0;
    ASSERT_TRUE(audio_delay_estimator_estimate(est, &delay, &corr));
    ASSERT_EQ(delay, 123u);
    ASSERT_TRUE(corr < -0.999 && corr >= -1.0);
    audio_delay_estimator_destroy(est);
}

TEST(no_estimate_before_enough_frames_or_on_silence)
{
    AudioDelayEstimator *est = make_estimator(100u, 64u);
    u32 delay = 9u;
    double corr = 0.5;
    ASSERT_TRUE(est != NULL);
    make_echo(10u, 0.5, 0.0);
    /* window + max_delay = 164 frames are needed */
    audio_delay_estimator_push_i16(est, g_ref, g_cap, 163u);
    ASSERT_TRUE(!audio_delay_estimator_estimate(est, &delay, &corr));
    ASSERT_EQ(delay, 9u);
    ASSERT_FLOAT_EQ(corr, 0.5, 0.0);
    audio_delay_estimator_push_i16(est, g_ref + 163u, g_cap + 163u, 1u);
    ASSERT_TRUE(audio_delay_estimator_estimate(est, &delay, &corr));
    ASSERT_EQ(delay, 10u);
    /* a silent capture window */
    static i16 zero[N];
    memset(zero, 0, sizeof(zero));
    audio_delay_estimator_push_i16(est, g_ref, zero, 64u);
    delay = 9u;
    ASSERT_TRUE(!audio_delay_estimator_estimate(est, &delay, &corr));
    ASSERT_EQ(delay, 9u);
    /* a silent reference everywhere */
    audio_delay_estimator_reset(est);
    audio_delay_estimator_push_i16(est, zero, g_cap, 400u);
    ASSERT_TRUE(!audio_delay_estimator_estimate(est, &delay, &corr));
    /* reset forgets the frames */
    audio_delay_estimator_reset(est);
    audio_delay_estimator_push_i16(est, g_ref, g_cap, 163u);
    ASSERT_TRUE(!audio_delay_estimator_estimate(est, &delay, &corr));
    audio_delay_estimator_destroy(est);
}

/* S(L) for the latest `window` capture frames ending at `end` (exclusive) */
static double brute_score(const i16 *ref, const i16 *cap, u32 end, u32 window, u32 lag) {
    i64 cr = 0, cc = 0, rr = 0;
    for (u32 i = end - window; i < end; ++i) {
        i64 c = cap[i], r = ref[i - lag];
        cr += c * r;
        cc += c * c;
        rr += r * r;
    }
    if (cc == 0 || rr == 0) return 0.0;
    return (double)cr / sqrt((double)cc * (double)rr);
}

TEST(chunking_and_a_brute_force_model_agree)
{
    const u32 max_delay = 300u, window = 512u;
    make_echo(77u, 0.2, 3000.0);
    /* the brute-force best lag and score at the end of the data */
    u32 best = 0u;
    double best_score = 0.0;
    for (u32 lag = 0; lag <= max_delay; ++lag) {
        double s = brute_score(g_ref, g_cap, N, window, lag);
        if (fabs(s) > fabs(best_score)) {
            best_score = s;
            best = lag;
        }
    }
    ASSERT_EQ(best, 77u);
    const u32 sizes[4] = {N, 1u, 7u, 480u};
    for (u32 s = 0; s < 4u; ++s) {
        AudioDelayEstimator *est = make_estimator(max_delay, window);
        ASSERT_TRUE(est != NULL);
        /* earlier pushes are forgotten by reset */
        audio_delay_estimator_push_i16(est, g_cap, g_ref, 1000u);
        audio_delay_estimator_reset(est);
        for (u32 at = 0; at < N; at += sizes[s]) {
            u32 n = N - at < sizes[s] ? N - at : sizes[s];
            audio_delay_estimator_push_i16(est, g_ref + at, g_cap + at, n);
        }
        u32 delay = 0u;
        double corr = 0.0;
        ASSERT_TRUE(audio_delay_estimator_estimate(est, &delay, &corr));
        ASSERT_EQ(delay, best);
        ASSERT_FLOAT_EQ(corr, best_score, 1e-12);
        audio_delay_estimator_destroy(est);
    }
}

TEST(ties_pick_the_smaller_lag)
{
    /* a reference with period 50 matches every multiple of 50 equally */
    AudioDelayEstimator *est = make_estimator(200u, 400u);
    static i16 ref[2000], cap[2000];
    ASSERT_TRUE(est != NULL);
    for (u32 n = 0; n < 2000u; ++n) {
        ref[n] = (i16)(((n % 50u) * 997u) % 20000u) - 10000;
    }
    for (u32 n = 0; n < 2000u; ++n) cap[n] = n >= 150u ? ref[n - 150u] : 0;
    audio_delay_estimator_push_i16(est, ref, cap, 2000u);
    u32 delay = 999u;
    double corr = 0.0;
    ASSERT_TRUE(audio_delay_estimator_estimate(est, &delay, &corr));
    ASSERT_EQ(delay, 0u);
    ASSERT_FLOAT_EQ(corr, 1.0, 1e-12);
    double fractional = 99.0;
    ASSERT_TRUE(audio_delay_estimator_estimate_subframe(est, &fractional, &corr));
    ASSERT_FLOAT_EQ(fractional, 0.0, 0.0);
    ASSERT_FLOAT_EQ(corr, 1.0, 1e-12);
    audio_delay_estimator_destroy(est);
}

TEST(fractional_echoes_are_estimated_within_a_tolerance)
{
    const double delays[] = {3.25, 12.5, 31.75};
    for (u32 s = 0; s < 3u; ++s) {
        AudioDelayEstimator *est = make_estimator(64u, 2048u);
        ASSERT_TRUE(est != NULL);
        make_fractional_echo(delays[s], 0.4);
        audio_delay_estimator_push_i16(est, g_ref, g_cap, N);
        double delay = 0.0, corr = 0.0;
        ASSERT_TRUE(audio_delay_estimator_estimate_subframe(est, &delay, &corr));
        ASSERT_TRUE(isfinite(delay));
        ASSERT_TRUE(fabs(delay - delays[s]) < 0.25);
        const double distance = fabs(delays[s] - floor(delays[s] + 0.5));
        const double expected_corr = sinc(distance);
        ASSERT_TRUE(fabs(corr - expected_corr) <= 0.1 && corr <= 1.0);
        u32 integer_delay = 0u;
        double integer_corr = 0.0;
        ASSERT_TRUE(audio_delay_estimator_estimate(est, &integer_delay, &integer_corr));
        ASSERT_FLOAT_EQ(corr, integer_corr, 1e-12);
        ASSERT_TRUE(fabs((double)integer_delay - delays[s]) <= 0.5);
        audio_delay_estimator_destroy(est);
    }
    const u32 endpoints[] = {0u, 64u};
    for (u32 s = 0; s < 2u; ++s) {
        AudioDelayEstimator *est = make_estimator(64u, 2048u);
        ASSERT_TRUE(est != NULL);
        make_echo(endpoints[s], 0.4, 0.0);
        audio_delay_estimator_push_i16(est, g_ref, g_cap, N);
        double delay = 99.0, corr = 0.0;
        ASSERT_TRUE(audio_delay_estimator_estimate_subframe(est, &delay, &corr));
        ASSERT_FLOAT_EQ(delay, (double)endpoints[s], 0.0);
        audio_delay_estimator_destroy(est);
    }
}

TEST(subframe_estimates_handle_inversion_and_failure)
{
    AudioDelayEstimator *est = make_estimator(64u, 256u);
    ASSERT_TRUE(est != NULL);
    make_fractional_echo(12.5, -0.4);
    audio_delay_estimator_push_i16(est, g_ref, g_cap, 319u);
    double delay = 9.0, corr = 0.5;
    ASSERT_TRUE(!audio_delay_estimator_estimate_subframe(est, &delay, &corr));
    ASSERT_FLOAT_EQ(delay, 9.0, 0.0);
    ASSERT_FLOAT_EQ(corr, 0.5, 0.0);
    ASSERT_TRUE(!audio_delay_estimator_estimate_subframe(NULL, &delay, &corr));
    ASSERT_TRUE(!audio_delay_estimator_estimate_subframe(est, NULL, &corr));
    ASSERT_TRUE(!audio_delay_estimator_estimate_subframe(est, &delay, NULL));
    audio_delay_estimator_push_i16(est, g_ref + 319u, g_cap + 319u, 1u);
    ASSERT_TRUE(audio_delay_estimator_estimate_subframe(est, &delay, &corr));
    ASSERT_TRUE(fabs(delay - 12.5) < 0.25);
    ASSERT_TRUE(corr < 0.0 && fabs(-corr - sinc(0.5)) <= 0.1 && corr >= -1.0);
    audio_delay_estimator_destroy(est);
}

TEST(the_delay_line_interpolates_fractional_delays)
{
    AudioDelayLine *line = NULL;
    ASSERT_EQ(audio_delay_line_create(8u, &line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(NULL, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, -0.01), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 8.01), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, NAN), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, INFINITY), AUDIO_INVALID);
    ASSERT_FLOAT_EQ(audio_delay_line_subframe_delay(NULL), 0.0, 0.0);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 2.25), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_delay(line), 2u);
    ASSERT_FLOAT_EQ(audio_delay_line_subframe_delay(line), 2.25, 0.0);
    i16 in[16], buf[16];
    for (u32 i = 0; i < 16u; ++i) in[i] = (i16)(((int)i - 8) * 401);
    memcpy(buf, in, sizeof(in));
    audio_delay_line_process_i16(line, buf, buf, 3u);
    audio_delay_line_process_i16(line, buf + 3u, buf + 3u, 13u);
    for (u32 i = 0; i < 16u; ++i) {
        const i16 previous = i < 3u ? 0 : in[i - 3u];
        const i16 expected = i < 2u ? 0
            : (i16)lrint((3.0 * in[i - 2u] + previous) / 4.0);
        ASSERT_EQ(buf[i], expected);
    }
    audio_delay_line_destroy(line);
    line = NULL;
    ASSERT_EQ(audio_delay_line_create(8u, &line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_delay(line, 2u), AUDIO_OK);
    ASSERT_FLOAT_EQ(audio_delay_line_subframe_delay(line), 2.0, 0.0);
    memcpy(buf, in, sizeof(in));
    audio_delay_line_process_i16(line, buf, buf, 16u);
    for (u32 i = 0; i < 16u; ++i) ASSERT_EQ(buf[i], i < 2u ? 0 : in[i - 2u]);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 8.0), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 8.01), AUDIO_INVALID);
    ASSERT_FLOAT_EQ(audio_delay_line_subframe_delay(line), 8.0, 0.0);
    audio_delay_line_destroy(line);
    ASSERT_EQ(audio_delay_line_create(0u, &line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 0.25), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 0.0), AUDIO_OK);
    audio_delay_line_process_i16(line, in, buf, 16u);
    ASSERT_EQ(memcmp(in, buf, sizeof(in)), 0);
    audio_delay_line_destroy(line);
}

TEST(the_delay_line_shifts_frames_by_the_delay)
{
    AudioDelayLine *sentinel = NULL;
    ASSERT_EQ(audio_delay_line_create(8u, &sentinel), AUDIO_OK);
    AudioDelayLine *line = sentinel;
    ASSERT_EQ(audio_delay_line_create(AUDIO_DELAY_ESTIMATOR_MAX_DELAY + 1u, &line),
              AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_create(4u, NULL), AUDIO_INVALID);
    ASSERT_TRUE(line == sentinel);
    /* a zero maximum is a pass-through */
    ASSERT_EQ(audio_delay_line_create(0u, &line), AUDIO_OK);
    i16 in[16], out[16];
    for (u32 i = 0; i < 16u; ++i) in[i] = (i16)(100 + i);
    audio_delay_line_process_i16(line, in, out, 16u);
    ASSERT_EQ(memcmp(in, out, sizeof(in)), 0);
    ASSERT_EQ(audio_delay_line_set_delay(line, 1u), AUDIO_INVALID);
    audio_delay_line_destroy(line);
    ASSERT_EQ(audio_delay_line_create(8u, &line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_delay(line), 0u);
    ASSERT_EQ(audio_delay_line_set_delay(line, 9u), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_set_delay(NULL, 1u), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_delay(NULL), 0u);
    ASSERT_EQ(audio_delay_line_set_delay(line, 5u), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_delay(line), 5u);
    /* across chunks, in place: silence first, then the input 5 frames late */
    i16 buf[16];
    memcpy(buf, in, sizeof(in));
    audio_delay_line_process_i16(line, buf, buf, 3u);
    audio_delay_line_process_i16(line, buf + 3, buf + 3, 13u);
    for (u32 i = 0; i < 16u; ++i) ASSERT_EQ(buf[i], i < 5u ? 0 : in[i - 5u]);
    /* a shorter delay reads the history at once: frames 14 and 15 again */
    ASSERT_EQ(audio_delay_line_set_delay(line, 2u), AUDIO_OK);
    i16 more[4] = {200, 201, 202, 203};
    audio_delay_line_process_i16(line, more, out, 4u);
    ASSERT_EQ(out[0], in[14]);
    ASSERT_EQ(out[1], in[15]);
    ASSERT_EQ(out[2], 200);
    ASSERT_EQ(out[3], 201);
    /* the maximum delay */
    ASSERT_EQ(audio_delay_line_set_delay(line, 8u), AUDIO_OK);
    audio_delay_line_process_i16(line, in, out, 8u);
    ASSERT_EQ(out[0], in[12]);
    ASSERT_EQ(out[7], 203);
    audio_delay_line_process_i16(NULL, in, out, 1u);
    audio_delay_line_process_i16(line, NULL, out, 1u);
    audio_delay_line_process_i16(line, in, NULL, 1u);
    audio_delay_line_destroy(line);
    audio_delay_line_destroy(sentinel);
    audio_delay_line_destroy(NULL);
}

static double power(const i16 *x, u32 n) {
    double s = 0.0;
    for (u32 i = 0; i < n; ++i) s += (double)x[i] * x[i];
    return s / n + 1e-9;
}

/* runs the canceller over g_ref/g_cap with the reference delayed by `delay`
 * and returns the ERLE of the last 4000 frames in dB */
static double erle_with_delay_mode(u32 delay, bool use_sinc) {
    static i16 ref[N], out[N];
    AudioEchoCancellerConfig config = {48000u, 32u, 0.5f, 0.0f, 0.0f};
    AudioEchoCanceller *aec = NULL;
    AudioDelayLine *line = NULL;
    if (audio_echo_canceller_create(&config, &aec) != AUDIO_OK) return -1.0;
    if (audio_delay_line_create(1000u, &line) != AUDIO_OK) return -1.0;
    if (audio_delay_line_set_sinc(line, use_sinc) != AUDIO_OK) return -1.0;
    audio_delay_line_set_delay(line, delay);
    audio_delay_line_process_i16(line, g_ref, ref, N);
    memcpy(out, g_cap, sizeof(out));
    audio_echo_canceller_process_i16(aec, ref, out, N);
    audio_delay_line_destroy(line);
    audio_echo_canceller_destroy(aec);
    return 10.0 * log10(power(g_cap + N - 4000u, 4000u) / power(out + N - 4000u, 4000u));
}

static double erle_with_delay(u32 delay) {
    return erle_with_delay_mode(delay, false);
}

TEST(the_delay_line_sinc_mode_validates_arguments)
{
    AudioDelayLine *line = NULL;
    ASSERT_EQ(audio_delay_line_set_sinc(NULL, true), AUDIO_INVALID);
    ASSERT_TRUE(!audio_delay_line_sinc(NULL));
    ASSERT_EQ(audio_delay_line_sinc_extra_delay(NULL), 0u);
    ASSERT_EQ(audio_delay_line_create(8u, &line), AUDIO_OK);
    ASSERT_TRUE(!audio_delay_line_sinc(line));
    ASSERT_EQ(audio_delay_line_sinc_extra_delay(line), 0u);
    ASSERT_EQ(audio_delay_line_set_sinc(line, true), AUDIO_OK);
    ASSERT_TRUE(audio_delay_line_sinc(line));
    ASSERT_EQ(audio_delay_line_sinc_extra_delay(line), 8u);
    ASSERT_EQ(audio_delay_line_set_delay(line, 8u), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_delay(line, 9u), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 8.0), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 8.01), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_line_set_sinc(line, false), AUDIO_OK);
    ASSERT_TRUE(!audio_delay_line_sinc(line));
    ASSERT_EQ(audio_delay_line_sinc_extra_delay(line), 0u);
    audio_delay_line_destroy(line);
}

TEST(sinc_integer_delays_have_eight_extra_frames)
{
    AudioDelayLine *line = NULL;
    i16 in[40], out[40];
    for (u32 i = 0; i < 40u; ++i) in[i] = (i16)(1000 + 37 * (int)i);
    ASSERT_EQ(audio_delay_line_create(16u, &line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(line, true), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_delay(line, 2u), AUDIO_OK);
    audio_delay_line_process_i16(line, in, out, 20u);
    for (u32 i = 0; i < 20u; ++i) ASSERT_EQ(out[i], i < 10u ? 0 : in[i - 10u]);
    ASSERT_EQ(audio_delay_line_set_sinc(line, false), AUDIO_OK);
    audio_delay_line_process_i16(line, in + 20u, out + 20u, 20u);
    for (u32 i = 20u; i < 40u; ++i) ASSERT_EQ(out[i], in[i - 2u]);
    ASSERT_EQ(audio_delay_line_delay(line), 2u);
    audio_delay_line_destroy(line);
}

static double sinc_reference_value(const i16 *in, u32 n, double delay) {
    const u32 whole = (u32)delay;
    const double fraction = delay - (double)whole;
    double value = 0.0, weight_sum = 0.0;
    for (int j = -7; j <= 8; ++j) {
        const int tap = j + 7;
        const double window = 0.42 - 0.5 * cos(2.0 * kPi * tap / 15.0) +
                              0.08 * cos(4.0 * kPi * tap / 15.0);
        const double weight = sinc(fraction - j) * window;
        const int source = (int)n - (int)whole - 8 - j;
        if (source >= 0) value += in[source] * weight;
        weight_sum += weight;
    }
    return value / weight_sum;
}

static i16 sinc_reference_sample(const i16 *in, u32 n, double delay) {
    const double rounded = lrint(sinc_reference_value(in, n, delay));
    if (rounded > 32767.0) return 32767;
    if (rounded < -32768.0) return -32768;
    return (i16)rounded;
}

TEST(sinc_fractional_delays_match_an_independent_kernel)
{
    AudioDelayLine *direct_line = NULL, *chunked_line = NULL;
    i16 in[48], expected[48], direct[48], chunked[48];
    for (u32 i = 0; i < 48u; ++i) {
        in[i] = (i16)(((int)i * 977 % 24000) - 12000);
        expected[i] = sinc_reference_sample(in, i, 2.25);
    }
    ASSERT_EQ(audio_delay_line_create(8u, &direct_line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_create(8u, &chunked_line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(direct_line, true), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(chunked_line, true), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(direct_line, 2.25), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(chunked_line, 2.25), AUDIO_OK);
    audio_delay_line_process_i16(direct_line, in, direct, 48u);
    memcpy(chunked, in, sizeof(in));
    audio_delay_line_process_i16(chunked_line, chunked, chunked, 1u);
    for (u32 at = 1u; at < 48u; at += 7u) {
        const u32 frames = 48u - at < 7u ? 48u - at : 7u;
        audio_delay_line_process_i16(chunked_line, chunked + at, chunked + at, frames);
    }
    for (u32 i = 0; i < 48u; ++i) {
        ASSERT_EQ(direct[i], expected[i]);
        ASSERT_EQ(chunked[i], expected[i]);
    }
    audio_delay_line_destroy(direct_line);
    audio_delay_line_destroy(chunked_line);
}

TEST(sinc_full_scale_overshoot_saturates)
{
    AudioDelayLine *positive_line = NULL, *negative_line = NULL;
    i16 positive_in[64] = {0}, negative_in[64] = {0};
    i16 positive_out[64], negative_out[64];
    for (int j = -7; j <= 8; ++j) {
        const int tap = j + 7;
        const double window = 0.42 - 0.5 * cos(2.0 * kPi * tap / 15.0) +
                              0.08 * cos(4.0 * kPi * tap / 15.0);
        const double weight = sinc(0.5 - j) * window;
        const int source = 31 - 8 - j;
        positive_in[source] = weight >= 0.0 ? 32767 : -32768;
        negative_in[source] = weight >= 0.0 ? -32768 : 32767;
    }
    ASSERT_TRUE(sinc_reference_value(positive_in, 31u, 0.5) > 32767.0);
    ASSERT_TRUE(sinc_reference_value(negative_in, 31u, 0.5) < -32768.0);
    ASSERT_EQ(audio_delay_line_create(1u, &positive_line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_create(1u, &negative_line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(positive_line, true), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(negative_line, true), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(positive_line, 0.5), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(negative_line, 0.5), AUDIO_OK);
    audio_delay_line_process_i16(positive_line, positive_in, positive_out, 64u);
    audio_delay_line_process_i16(negative_line, negative_in, negative_out, 64u);
    for (u32 i = 0; i < 64u; ++i) {
        ASSERT_EQ(positive_out[i], sinc_reference_sample(positive_in, i, 0.5));
        ASSERT_EQ(negative_out[i], sinc_reference_sample(negative_in, i, 0.5));
    }
    audio_delay_line_destroy(positive_line);
    audio_delay_line_destroy(negative_line);
}

static double tone_amplitude(const i16 *samples, u32 frames) {
    double sine = 0.0, cosine = 0.0;
    for (u32 i = 0; i < frames; ++i) {
        const double phase = 2.0 * kPi * i / 6.0;
        sine += samples[i] * sin(phase);
        cosine += samples[i] * cos(phase);
    }
    return 2.0 * sqrt(sine * sine + cosine * cosine) / frames;
}

TEST(sinc_interpolation_preserves_high_frequency_tones_and_dc)
{
    AudioDelayLine *sinc_line = NULL, *linear_line = NULL, *dc_line = NULL;
    i16 in[2048], sinc_out[2048], linear_out[2048];
    for (u32 i = 0; i < 2048u; ++i) {
        in[i] = (i16)lrint(12000.0 * sin(2.0 * kPi * i / 6.0));
    }
    ASSERT_EQ(audio_delay_line_create(1u, &sinc_line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_create(1u, &linear_line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(sinc_line, true), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(sinc_line, 0.5), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(linear_line, 0.5), AUDIO_OK);
    audio_delay_line_process_i16(sinc_line, in, sinc_out, 2048u);
    audio_delay_line_process_i16(linear_line, in, linear_out, 2048u);
    const double sinc_amplitude = tone_amplitude(sinc_out + 1024u, 1024u);
    const double linear_amplitude = tone_amplitude(linear_out + 1024u, 1024u);
    ASSERT_TRUE(sinc_amplitude >= 11400.0);
    ASSERT_FLOAT_EQ(linear_amplitude, 10386.9295, 0.001);
    audio_delay_line_destroy(sinc_line);
    audio_delay_line_destroy(linear_line);

    i16 dc_in[32], dc_out[32];
    for (u32 i = 0; i < 32u; ++i) dc_in[i] = 1234;
    ASSERT_EQ(audio_delay_line_create(0u, &dc_line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(dc_line, true), AUDIO_OK);
    audio_delay_line_process_i16(dc_line, dc_in, dc_out, 32u);
    for (u32 i = 0; i < 32u; ++i) ASSERT_EQ(dc_out[i], i < 8u ? 0 : 1234);
    audio_delay_line_destroy(dc_line);
}

TEST(sinc_maximum_delay_and_recreate_preserve_bounds)
{
    AudioDelayLine *line = NULL;
    i16 in[24], out[24];
    for (u32 i = 0; i < 24u; ++i) in[i] = (i16)(300 + 19 * (int)i);
    ASSERT_EQ(audio_delay_line_create(4u, &line), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(line, true), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 4.0), AUDIO_OK);
    audio_delay_line_process_i16(line, in, out, 24u);
    for (u32 i = 0; i < 24u; ++i) ASSERT_EQ(out[i], i < 12u ? 0 : in[i - 12u]);
    ASSERT_EQ(audio_delay_line_set_subframe_delay(line, 4.25), AUDIO_INVALID);
    ASSERT_FLOAT_EQ(audio_delay_line_subframe_delay(line), 4.0, 0.0);
    ASSERT_EQ(audio_delay_line_set_sinc(line, false), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_set_sinc(line, true), AUDIO_OK);
    ASSERT_EQ(audio_delay_line_sinc_extra_delay(line), 8u);
    audio_delay_line_destroy(line);

    ASSERT_EQ(audio_delay_line_create(4u, &line), AUDIO_OK);
    ASSERT_TRUE(!audio_delay_line_sinc(line));
    ASSERT_EQ(audio_delay_line_set_delay(line, 4u), AUDIO_OK);
    audio_delay_line_process_i16(line, in, out, 4u);
    for (u32 i = 0; i < 4u; ++i) ASSERT_EQ(out[i], 0);
    audio_delay_line_destroy(line);
}

TEST(sinc_latency_can_be_compensated_for_the_canceller)
{
    make_echo(300u, 0.4, 0.0);
    AudioDelayEstimator *est = make_estimator(1000u, 4096u);
    ASSERT_TRUE(est != NULL);
    audio_delay_estimator_push_i16(est, g_ref, g_cap, N);
    u32 delay = 0u;
    double corr = 0.0;
    ASSERT_TRUE(audio_delay_estimator_estimate(est, &delay, &corr));
    ASSERT_EQ(delay, 300u);
    audio_delay_estimator_destroy(est);
    ASSERT_TRUE(erle_with_delay_mode(delay - 8u, true) > 30.0);
}

TEST(the_estimated_delay_aligns_the_reference_for_the_canceller)
{
    /* a 300-frame latency, longer than the 32-tap filter */
    make_echo(300u, 0.4, 0.0);
    AudioDelayEstimator *est = make_estimator(1000u, 4096u);
    ASSERT_TRUE(est != NULL);
    audio_delay_estimator_push_i16(est, g_ref, g_cap, N);
    u32 delay = 0u;
    double corr = 0.0;
    ASSERT_TRUE(audio_delay_estimator_estimate(est, &delay, &corr));
    ASSERT_EQ(delay, 300u);
    audio_delay_estimator_destroy(est);
    /* leave a few taps of margin before the echo */
    ASSERT_TRUE(erle_with_delay(0u) < 3.0);
    ASSERT_TRUE(erle_with_delay(delay - 4u) > 30.0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_refuses_every_invalid_config);
    RUN_TEST(delayed_noise_gives_the_exact_lag);
    RUN_TEST(an_inverted_echo_is_found_with_a_negative_correlation);
    RUN_TEST(no_estimate_before_enough_frames_or_on_silence);
    RUN_TEST(chunking_and_a_brute_force_model_agree);
    RUN_TEST(ties_pick_the_smaller_lag);
    RUN_TEST(fractional_echoes_are_estimated_within_a_tolerance);
    RUN_TEST(subframe_estimates_handle_inversion_and_failure);
    RUN_TEST(the_delay_line_interpolates_fractional_delays);
    RUN_TEST(the_delay_line_shifts_frames_by_the_delay);
    RUN_TEST(the_delay_line_sinc_mode_validates_arguments);
    RUN_TEST(sinc_integer_delays_have_eight_extra_frames);
    RUN_TEST(sinc_fractional_delays_match_an_independent_kernel);
    RUN_TEST(sinc_full_scale_overshoot_saturates);
    RUN_TEST(sinc_interpolation_preserves_high_frequency_tones_and_dc);
    RUN_TEST(sinc_maximum_delay_and_recreate_preserve_bounds);
    RUN_TEST(sinc_latency_can_be_compensated_for_the_canceller);
    RUN_TEST(the_estimated_delay_aligns_the_reference_for_the_canceller);
TEST_MAIN_END()
