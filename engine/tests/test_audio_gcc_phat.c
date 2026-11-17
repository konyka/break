/* audio_gcc_phat: configuration, readiness/silence, exact/inverted/fractional
 * delays, chunking/reset and a direct time-domain lag reference. */
#include "test_framework.h"

#include <audio/audio_gcc_phat.h>
#include <audio/audio_gcc_phat_internal.h>

#include <math.h>
#include <string.h>

#define N 8192u

static const double kPi = 3.14159265358979323846;
static u32 g_seed = 0xC0FFEE11u;
static i16 g_ref[N], g_cap[N];

static double rnd(void) {
    g_seed = g_seed * 1664525u + 1013904223u;
    return (double)(g_seed >> 8) / 8388608.0 - 1.0;
}

static i16 noise(double amplitude) {
    return (i16)lrint(rnd() * amplitude);
}

static void make_echo(u32 delay, double gain, double noise_amp) {
    for (u32 n = 0; n < N; ++n) g_ref[n] = noise(12000.0);
    for (u32 n = 0; n < N; ++n) {
        double value = n >= delay ? gain * g_ref[n - delay] : 0.0;
        if (noise_amp > 0.0) value += noise(noise_amp);
        g_cap[n] = (i16)lrint(value);
    }
}

static double sinc(double x) {
    return fabs(x) < 1e-12 ? 1.0 : sin(kPi * x) / (kPi * x);
}

static void make_fractional_echo(double delay, double noise_amp) {
    for (u32 n = 0; n < N; ++n) g_ref[n] = noise(12000.0);
    const int center = (int)floor(delay);
    for (u32 n = 0; n < N; ++n) {
        double value = 0.0;
        for (int k = center - 16; k <= center + 16; ++k) {
            const int source = (int)n - k;
            if (source >= 0 && source < (int)N) value += g_ref[source] * sinc((double)k - delay);
        }
        if (noise_amp > 0.0) value += noise(noise_amp);
        g_cap[n] = (i16)lrint(0.4 * value);
    }
}

static AudioGccPhat *make_phat(u32 max_delay, u32 window) {
    const AudioGccPhatConfig config = {max_delay, window};
    AudioGccPhat *phat = NULL;
    if (audio_gcc_phat_create(&config, &phat) != AUDIO_OK) return NULL;
    return phat;
}

TEST(create_validates_config_readiness_and_silence)
{
    const AudioGccPhatConfig config = {64u, 1024u};
    AudioGccPhat *sentinel = make_phat(64u, 1024u);
    ASSERT_TRUE(sentinel != NULL);
    AudioGccPhat *phat = sentinel;
    const AudioGccPhatConfig bad[] = {
        {0u, 1024u}, {96001u, 1024u}, {64u, 15u}, {64u, 96001u},
        {AUDIO_GCC_PHAT_MAX_HISTORY, 16u}, {1u, AUDIO_GCC_PHAT_MAX_HISTORY},
        {UINT32_MAX, 16u}, {1u, UINT32_MAX}, {UINT32_MAX, UINT32_MAX},
        {1000u, UINT32_MAX - 997u}};
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        ASSERT_EQ(audio_gcc_phat_create(&bad[i], &phat), AUDIO_INVALID);
        ASSERT_TRUE(phat == sentinel);
    }
    ASSERT_EQ(audio_gcc_phat_create(NULL, &phat), AUDIO_INVALID);
    ASSERT_EQ(audio_gcc_phat_create(&config, NULL), AUDIO_INVALID);
    const AudioGccPhatConfig largest = {AUDIO_GCC_PHAT_MAX_HISTORY - 16u, 16u};
    ASSERT_EQ(audio_gcc_phat_create(&largest, &phat), AUDIO_OK);
    audio_gcc_phat_destroy(phat);
    audio_gcc_phat_destroy(NULL);
    audio_gcc_phat_reset(NULL);
    double delay = 9.0, peak = 0.5;
    ASSERT_TRUE(!audio_gcc_phat_estimate(NULL, &delay, &peak));
    phat = make_phat(64u, 1024u);
    ASSERT_TRUE(phat != NULL);
    make_echo(17u, 0.4, 0.0);
    audio_gcc_phat_push_i16(NULL, g_ref, g_cap, 1u);
    audio_gcc_phat_push_i16(phat, NULL, g_cap, 1u);
    audio_gcc_phat_push_i16(phat, g_ref, NULL, 1u);
    audio_gcc_phat_push_i16(phat, g_ref, g_cap, 1087u);
    ASSERT_TRUE(!audio_gcc_phat_estimate(phat, &delay, &peak));
    ASSERT_TRUE(!audio_gcc_phat_estimate(phat, NULL, &peak));
    ASSERT_TRUE(!audio_gcc_phat_estimate(phat, &delay, NULL));
    ASSERT_FLOAT_EQ(delay, 9.0, 0.0);
    ASSERT_FLOAT_EQ(peak, 0.5, 0.0);
    audio_gcc_phat_push_i16(phat, g_ref + 1087u, g_cap + 1087u, 1u);
    ASSERT_TRUE(audio_gcc_phat_estimate(phat, &delay, &peak));
    ASSERT_TRUE(fabs(delay - 17.0) < 0.01);
    static i16 zero[N];
    memset(zero, 0, sizeof(zero));
    audio_gcc_phat_push_i16(phat, g_ref, zero, 1024u);
    ASSERT_TRUE(!audio_gcc_phat_estimate(phat, &delay, &peak));
    audio_gcc_phat_reset(phat);
    audio_gcc_phat_push_i16(phat, zero, g_cap, 1088u);
    ASSERT_TRUE(!audio_gcc_phat_estimate(phat, &delay, &peak));
    audio_gcc_phat_destroy(phat);
    audio_gcc_phat_destroy(sentinel);
}

TEST(exact_and_inverted_echoes_have_known_lags_and_peak_signs)
{
    const u32 delays[] = {0u, 1u, 17u, 1000u};
    for (u32 s = 0; s < 4u; ++s) {
        AudioGccPhat *phat = make_phat(1000u, 1024u);
        ASSERT_TRUE(phat != NULL);
        make_echo(delays[s], 0.4, 1000.0);
        audio_gcc_phat_push_i16(phat, g_ref, g_cap, N);
        double delay = 99.0, peak = 0.0;
        ASSERT_TRUE(audio_gcc_phat_estimate(phat, &delay, &peak));
        if (delays[s] == 0u || delays[s] == 1000u) {
            ASSERT_FLOAT_EQ(delay, (double)delays[s], 0.0);
        } else {
            ASSERT_TRUE(fabs(delay - (double)delays[s]) < 0.01);
        }
        ASSERT_TRUE(isfinite(peak));
        ASSERT_TRUE(peak > 0.0);
        audio_gcc_phat_destroy(phat);
    }
    AudioGccPhat *phat = make_phat(64u, 1024u);
    ASSERT_TRUE(phat != NULL);
    make_echo(17u, -0.4, 0.0);
    audio_gcc_phat_push_i16(phat, g_ref, g_cap, N);
    double delay = 0.0, peak = 0.0;
    ASSERT_TRUE(audio_gcc_phat_estimate(phat, &delay, &peak));
    ASSERT_TRUE(fabs(delay - 17.0) < 0.01);
    ASSERT_TRUE(peak < 0.0);

    memset(g_ref, 0, sizeof(g_ref));
    memset(g_cap, 0, sizeof(g_cap));
    g_ref[N - 1000u] = 32767;
    g_cap[N - 983u] = 32767;
    audio_gcc_phat_reset(phat);
    audio_gcc_phat_push_i16(phat, g_ref, g_cap, N);
    ASSERT_TRUE(audio_gcc_phat_estimate(phat, &delay, &peak));
    ASSERT_FLOAT_EQ(delay, 17.0, 0.0);
    ASSERT_FLOAT_EQ(peak, 1.0, 1e-9);
    for (u32 n = 0; n < N; ++n) g_ref[n] = g_cap[n] = 1000;
    audio_gcc_phat_reset(phat);
    audio_gcc_phat_push_i16(phat, g_ref, g_cap, N);
    ASSERT_TRUE(audio_gcc_phat_estimate(phat, &delay, &peak));
    ASSERT_FLOAT_EQ(delay, 0.0, 0.0);
    audio_gcc_phat_destroy(phat);

    phat = make_phat(1000u, 16u);
    ASSERT_TRUE(phat != NULL);
    memset(g_ref, 0, sizeof(g_ref));
    memset(g_cap, 0, sizeof(g_cap));
    g_ref[N - 1016u] = 32767;
    g_cap[N - 16u] = 32767;
    audio_gcc_phat_push_i16(phat, g_ref, g_cap, N);
    ASSERT_TRUE(audio_gcc_phat_estimate(phat, &delay, &peak));
    ASSERT_FLOAT_EQ(delay, 1000.0, 0.0);
    ASSERT_FLOAT_EQ(peak, 1.0, 1e-9);
    audio_gcc_phat_destroy(phat);
}

TEST(repeated_estimates_are_deterministic)
{
    AudioGccPhat *phat = make_phat(64u, 1024u);
    ASSERT_TRUE(phat != NULL);
    make_echo(23u, 0.4, 1000.0);
    audio_gcc_phat_push_i16(phat, g_ref, g_cap, N);
    double a = 0.0, b = 0.0, pa = 0.0, pb = 0.0;
    ASSERT_TRUE(audio_gcc_phat_estimate(phat, &a, &pa));
    ASSERT_TRUE(audio_gcc_phat_estimate(phat, &b, &pb));
    ASSERT_FLOAT_EQ(a, b, 0.0);
    ASSERT_FLOAT_EQ(pa, pb, 0.0);
    ASSERT_TRUE(fabs(a - 23.0) < 0.01);
    audio_gcc_phat_destroy(phat);
}

TEST(fractional_echoes_with_noise_have_subframe_peaks)
{
    const double delays[] = {12.25, 12.5, 12.75};
    for (u32 s = 0; s < 3u; ++s) {
        AudioGccPhat *phat = make_phat(64u, 2048u);
        ASSERT_TRUE(phat != NULL);
        make_fractional_echo(delays[s], 1000.0);
        audio_gcc_phat_push_i16(phat, g_ref, g_cap, N);
        double delay = 0.0, peak = 0.0;
        ASSERT_TRUE(audio_gcc_phat_estimate(phat, &delay, &peak));
        ASSERT_TRUE(isfinite(delay));
        ASSERT_TRUE(isfinite(peak));
        ASSERT_TRUE(fabs(delay - delays[s]) < 0.25);
        audio_gcc_phat_destroy(phat);
    }
}

static u32 direct_best_lag(u32 maximum, u32 window) {
    u32 best = 0u;
    double best_score = 0.0;
    for (u32 lag = 0; lag <= maximum; ++lag) {
        i64 cr = 0, cc = 0, rr = 0;
        for (u32 i = N - window; i < N; ++i) {
            const i64 c = g_cap[i], r = g_ref[i - lag];
            cr += c * r;
            cc += c * c;
            rr += r * r;
        }
        if (cc == 0 || rr == 0) continue;
        const double score = fabs((double)cr / sqrt((double)cc * (double)rr));
        if (score > best_score) {
            best_score = score;
            best = lag;
        }
    }
    return best;
}

TEST(chunking_reset_and_direct_reference_agree)
{
    const u32 maximum = 64u, window = 1024u;
    make_echo(37u, 0.3, 500.0);
    const u32 expected = direct_best_lag(maximum, window);
    ASSERT_EQ(expected, 37u);
    AudioGccPhat *whole = make_phat(maximum, window);
    AudioGccPhat *chunked = make_phat(maximum, window);
    ASSERT_TRUE(whole != NULL && chunked != NULL);
    audio_gcc_phat_push_i16(whole, g_ref, g_cap, N);
    const u32 chunks[] = {1u, 7u, 480u};
    u32 at = 0u, index = 0u;
    while (at < N) {
        u32 n = N - at < chunks[index % 3u] ? N - at : chunks[index % 3u];
        audio_gcc_phat_push_i16(chunked, g_ref + at, g_cap + at, n);
        at += n;
        ++index;
    }
    double a = 0.0, b = 0.0, pa = 0.0, pb = 0.0;
    ASSERT_TRUE(audio_gcc_phat_estimate(whole, &a, &pa));
    ASSERT_TRUE(audio_gcc_phat_estimate(chunked, &b, &pb));
    ASSERT_TRUE(fabs(a - (double)expected) < 0.01);
    ASSERT_FLOAT_EQ(a, b, 0.0);
    ASSERT_FLOAT_EQ(pa, pb, 0.0);
    audio_gcc_phat_reset(whole);
    a = 99.0; pa = 0.5;
    ASSERT_TRUE(!audio_gcc_phat_estimate(whole, &a, &pa));
    ASSERT_FLOAT_EQ(a, 99.0, 0.0);
    ASSERT_FLOAT_EQ(pa, 0.5, 0.0);
    audio_gcc_phat_push_i16(whole, g_ref, g_cap, maximum + window - 1u);
    ASSERT_TRUE(!audio_gcc_phat_estimate(whole, &a, &pa));
    audio_gcc_phat_push_i16(whole, g_ref + maximum + window - 1u, g_cap + maximum + window - 1u, 1u);
    ASSERT_TRUE(audio_gcc_phat_estimate(whole, &a, &pa));
    audio_gcc_phat_reset(whole);
    audio_gcc_phat_destroy(chunked);
    chunked = make_phat(maximum, window);
    ASSERT_TRUE(chunked != NULL);
    audio_gcc_phat_push_i16(whole, g_ref, g_cap, N);
    audio_gcc_phat_push_i16(chunked, g_ref, g_cap, N);
    ASSERT_TRUE(audio_gcc_phat_estimate(whole, &a, &pa));
    ASSERT_TRUE(audio_gcc_phat_estimate(chunked, &b, &pb));
    ASSERT_FLOAT_EQ(a, b, 0.0);
    ASSERT_FLOAT_EQ(pa, pb, 0.0);
    audio_gcc_phat_destroy(whole);
    audio_gcc_phat_destroy(chunked);
}

TEST(internal_fft_size_and_exact_tie_selection)
{
    const struct { u32 history, size; } sizes[] = {
        {16u, 32u}, {1016u, 2048u}, {1088u, 4096u}, {2024u, 4096u}, {32768u, 65536u}};
    for (u32 i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i) {
        ASSERT_EQ(audio_gcc_phat_fft_size(sizes[i].history), sizes[i].size);
    }
    const f64 values[] = {0.0, 1.0, -1.0, 1.0, 0.5};
    u32 lag = 99u;
    double peak = 0.0;
    audio_gcc_phat_select_peak(values, 5u, &lag, &peak);
    ASSERT_EQ(lag, 1u);
    ASSERT_FLOAT_EQ(peak, 1.0, 0.0);
    const f64 negative[] = {-1.0, -1.0};
    audio_gcc_phat_select_peak(negative, 2u, &lag, &peak);
    ASSERT_EQ(lag, 0u);
    ASSERT_FLOAT_EQ(peak, -1.0, 0.0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_config_readiness_and_silence);
    RUN_TEST(internal_fft_size_and_exact_tie_selection);
    RUN_TEST(exact_and_inverted_echoes_have_known_lags_and_peak_signs);
    RUN_TEST(repeated_estimates_are_deterministic);
    RUN_TEST(fractional_echoes_with_noise_have_subframe_peaks);
    RUN_TEST(chunking_reset_and_direct_reference_agree);
TEST_MAIN_END()
