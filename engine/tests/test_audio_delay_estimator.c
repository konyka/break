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
static double erle_with_delay(u32 delay) {
    static i16 ref[N], out[N];
    AudioEchoCancellerConfig config = {48000u, 32u, 0.5f, 0.0f, 0.0f};
    AudioEchoCanceller *aec = NULL;
    AudioDelayLine *line = NULL;
    if (audio_echo_canceller_create(&config, &aec) != AUDIO_OK) return -1.0;
    if (audio_delay_line_create(1000u, &line) != AUDIO_OK) return -1.0;
    audio_delay_line_set_delay(line, delay);
    audio_delay_line_process_i16(line, g_ref, ref, N);
    memcpy(out, g_cap, sizeof(out));
    audio_echo_canceller_process_i16(aec, ref, out, N);
    audio_delay_line_destroy(line);
    audio_echo_canceller_destroy(aec);
    return 10.0 * log10(power(g_cap + N - 4000u, 4000u) / power(out + N - 4000u, 4000u));
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
    RUN_TEST(the_estimated_delay_aligns_the_reference_for_the_canceller);
TEST_MAIN_END()
