#include "test_framework.h"

#include <audio/audio_voice_aligner.h>

#include <math.h>
#include <string.h>

#define ALIGNER_TEST_FRAMES 16384u
#define ALIGNER_TEST_PERIOD 4096u

static const double kPi = 3.14159265358979323846;
static u32 g_seed;
static i16 g_reference[ALIGNER_TEST_FRAMES];
static i16 g_capture[ALIGNER_TEST_FRAMES];
static i16 g_whole[ALIGNER_TEST_FRAMES];
static i16 g_chunked[ALIGNER_TEST_FRAMES];

#define ASSERT_FINITE_NEAR(a, b, eps) do { \
    const double actual_ = (double)(a); \
    const double expected_ = (double)(b); \
    ASSERT_TRUE(isfinite(actual_)); \
    ASSERT_TRUE(isfinite(expected_)); \
    ASSERT_TRUE(fabs(actual_ - expected_) <= (double)(eps)); \
} while (0)

static double test_random(void)
{
    g_seed = g_seed * 1664525u + 1013904223u;
    return (double)(g_seed >> 8) / 8388608.0 - 1.0;
}

static double test_sinc(double value)
{
    return fabs(value) < 1e-12 ? 1.0 : sin(kPi * value) / (kPi * value);
}

static void make_fractional_echo(double delay)
{
    g_seed = 0x4a1c39e7u;
    for (u32 n = 0u; n < ALIGNER_TEST_FRAMES; ++n) {
        g_reference[n] = (i16)lrint(test_random() * 12000.0);
    }
    const int center = (int)floor(delay);
    for (u32 n = 0u; n < ALIGNER_TEST_FRAMES; ++n) {
        double value = 0.0;
        for (int k = center - 16; k <= center + 16; ++k) {
            const int source = (int)n - k;
            if (source >= 0 && source < (int)ALIGNER_TEST_FRAMES) {
                value += g_reference[source] * test_sinc((double)k - delay);
            }
        }
        g_capture[n] = (i16)lrint(0.4 * value);
    }
}

static bool g_fail_delay;

AudioResult aligner_test_delay_hook(AudioDelayLine *line, double delay)
{
    if (g_fail_delay) return AUDIO_FAILED;
    return audio_delay_line_set_subframe_delay(line, delay);
}

static AudioVoiceAlignerConfig test_config(void)
{
    AudioVoiceAlignerConfig config;
    config.tracker.sample_rate = 16000u;
    config.tracker.max_delay_frames = 64u;
    config.tracker.window_frames = 2048u;
    config.tracker.min_abs_correlation = 0.2f;
    config.tracker.max_slew_frames_per_s = 10.0f;
    config.tracker.lock_count = 1u;
    config.tracker.hold_updates = 2u;
    config.update_period_frames = ALIGNER_TEST_PERIOD;
    return config;
}

static AudioVoiceAligner *create_aligner(const AudioVoiceAlignerConfig *config)
{
    AudioVoiceAligner *aligner = NULL;
    if (audio_voice_aligner_create(config, &aligner) != AUDIO_OK) return NULL;
    return aligner;
}

TEST(create_validates_configuration_and_calls)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = NULL;
    ASSERT_EQ(audio_voice_aligner_create(NULL, &aligner), AUDIO_INVALID);
    ASSERT_EQ(audio_voice_aligner_create(&config, NULL), AUDIO_INVALID);
    AudioVoiceAlignerConfig bad = config;
    bad.update_period_frames = 0u;
    ASSERT_EQ(audio_voice_aligner_create(&bad, &aligner), AUDIO_INVALID);
    bad.update_period_frames = 192001u;
    ASSERT_EQ(audio_voice_aligner_create(&bad, &aligner), AUDIO_INVALID);
    bad = config;
    bad.tracker.sample_rate = 7999u;
    ASSERT_EQ(audio_voice_aligner_create(&bad, &aligner), AUDIO_INVALID);
    bad = config;
    bad.tracker.window_frames = 32768u;
    ASSERT_EQ(audio_voice_aligner_create_gcc(&bad, &aligner), AUDIO_INVALID);
    ASSERT_TRUE(aligner == NULL);

    aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    AudioVoiceAligner *original = aligner;
    bad = config;
    bad.update_period_frames = 0u;
    ASSERT_EQ(audio_voice_aligner_create(&bad, &aligner), AUDIO_INVALID);
    ASSERT_TRUE(aligner == original);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(NULL), 0.0, 0.0);
    ASSERT_EQ(audio_voice_aligner_updates(NULL), 0u);
    ASSERT_TRUE(!audio_voice_aligner_locked(NULL));
    ASSERT_TRUE(!audio_voice_aligner_uses_gcc(NULL));
    ASSERT_EQ(audio_voice_aligner_rejections(NULL), 0u);
    ASSERT_FINITE_NEAR(audio_voice_aligner_correlation(NULL), 0.0, 0.0);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 0.0, 0.0);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 0u);
    ASSERT_TRUE(!audio_voice_aligner_locked(aligner));
    ASSERT_TRUE(!audio_voice_aligner_uses_gcc(aligner));
    ASSERT_EQ(audio_voice_aligner_rejections(aligner), 0u);
    ASSERT_EQ(audio_voice_aligner_process_i16(NULL, NULL, NULL, NULL, 0u), AUDIO_INVALID);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, NULL, NULL, NULL, 0u), AUDIO_OK);
    i16 reference = 100, capture = 50, output = 77;
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, NULL, &capture, &output, 1u),
              AUDIO_INVALID);
    ASSERT_EQ(output, 77);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, &reference, NULL, &output, 1u),
              AUDIO_INVALID);
    ASSERT_EQ(output, 77);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, &reference, &capture, NULL, 1u),
              AUDIO_INVALID);
    ASSERT_EQ(capture, 50);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, &reference, &capture, &capture, 1u),
              AUDIO_INVALID);
    ASSERT_EQ(capture, 50);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 0u);
    audio_voice_aligner_destroy(NULL);
    audio_voice_aligner_destroy(aligner);
}

TEST(known_fractional_echo_updates_at_exact_period)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    make_fractional_echo(12.5);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD - 1u), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 0u);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 0.0, 0.0);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference + ALIGNER_TEST_PERIOD - 1u,
                                               g_capture + ALIGNER_TEST_PERIOD - 1u,
                                               g_whole + ALIGNER_TEST_PERIOD - 1u, 1u), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 1u);
    ASSERT_EQ(audio_voice_aligner_rejections(aligner), 0u);
    ASSERT_TRUE(audio_voice_aligner_locked(aligner));
    ASSERT_TRUE(audio_voice_aligner_correlation(aligner) >= 0.2);
    const double delay = audio_voice_aligner_delay(aligner);
    ASSERT_FINITE_NEAR(delay, 12.5, 0.25);
    ASSERT_EQ(g_whole[ALIGNER_TEST_PERIOD - 1u], g_reference[ALIGNER_TEST_PERIOD - 1u]);

    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference + ALIGNER_TEST_PERIOD,
                                               g_capture + ALIGNER_TEST_PERIOD,
                                               g_whole + ALIGNER_TEST_PERIOD, 1u), AUDIO_OK);
    const u32 whole = (u32)delay;
    const double fraction = delay - (double)whole;
    const u32 n = ALIGNER_TEST_PERIOD;
    const double expected = nearbyint((1.0 - fraction) * g_reference[n - whole] +
                                      fraction * g_reference[n - whole - 1u]);
    ASSERT_EQ(g_whole[n], (i16)expected);
    audio_voice_aligner_destroy(aligner);
}

TEST(irregular_chunks_match_whole_blocks)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *whole = create_aligner(&config);
    AudioVoiceAligner *chunked = create_aligner(&config);
    ASSERT_NOT_NULL(whole);
    ASSERT_NOT_NULL(chunked);
    make_fractional_echo(12.5);
    ASSERT_EQ(audio_voice_aligner_process_i16(whole, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_FRAMES), AUDIO_OK);
    static const u32 chunks[] = {1u, 7u, 31u, 128u};
    u32 offset = 0u;
    u32 step = 0u;
    while (offset < ALIGNER_TEST_FRAMES) {
        const u32 remaining = ALIGNER_TEST_FRAMES - offset;
        const u32 chunk = remaining < chunks[step % 4u] ? remaining : chunks[step % 4u];
        ASSERT_EQ(audio_voice_aligner_process_i16(chunked, g_reference + offset,
                                                   g_capture + offset, g_chunked + offset,
                                                   chunk), AUDIO_OK);
        offset += chunk;
        ++step;
    }
    ASSERT_TRUE(memcmp(g_whole, g_chunked, sizeof(g_whole)) == 0);
    ASSERT_EQ(audio_voice_aligner_updates(whole), ALIGNER_TEST_FRAMES / ALIGNER_TEST_PERIOD);
    ASSERT_EQ(audio_voice_aligner_updates(chunked), audio_voice_aligner_updates(whole));
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(chunked), audio_voice_aligner_delay(whole),
                       0.0);
    ASSERT_EQ(audio_voice_aligner_locked(chunked), audio_voice_aligner_locked(whole));
    ASSERT_EQ(audio_voice_aligner_rejections(chunked), audio_voice_aligner_rejections(whole));
    audio_voice_aligner_destroy(whole);
    audio_voice_aligner_destroy(chunked);
}

TEST(silent_capture_rejects_without_moving_delay)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    make_fractional_echo(12.5);
    memset(g_capture, 0, ALIGNER_TEST_PERIOD * sizeof(g_capture[0]));
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 1u);
    ASSERT_EQ(audio_voice_aligner_rejections(aligner), 1u);
    ASSERT_TRUE(!audio_voice_aligner_locked(aligner));
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 0.0, 0.0);
    ASSERT_FINITE_NEAR(audio_voice_aligner_correlation(aligner), 0.0, 0.0);
    ASSERT_TRUE(memcmp(g_whole, g_reference, ALIGNER_TEST_PERIOD * sizeof(g_reference[0])) == 0);

    make_fractional_echo(12.5);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 2u);
    ASSERT_EQ(audio_voice_aligner_rejections(aligner), 1u);
    ASSERT_TRUE(audio_voice_aligner_locked(aligner));
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 12.5, 0.25);
    audio_voice_aligner_destroy(aligner);
}

TEST(gcc_constructor_applies_known_delay)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = NULL;
    make_fractional_echo(12.5);
    ASSERT_EQ(audio_voice_aligner_create_gcc(&config, &aligner), AUDIO_OK);
    ASSERT_NOT_NULL(aligner);
    ASSERT_TRUE(audio_voice_aligner_uses_gcc(aligner));
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 1u);
    ASSERT_EQ(audio_voice_aligner_rejections(aligner), 0u);
    ASSERT_TRUE(audio_voice_aligner_locked(aligner));
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 12.5, 0.25);
    audio_voice_aligner_destroy(aligner);
}

TEST(delay_failure_restores_update_schedule)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    make_fractional_echo(12.5);
    g_fail_delay = true;
    const AudioResult failed = audio_voice_aligner_process_i16(
        aligner, g_reference, g_capture, g_whole, ALIGNER_TEST_PERIOD);
    g_fail_delay = false;
    const AudioResult one = audio_voice_aligner_process_i16(
        aligner, g_reference + ALIGNER_TEST_PERIOD, g_capture + ALIGNER_TEST_PERIOD,
        g_whole + ALIGNER_TEST_PERIOD, 1u);
    const u64 updates_after_one = audio_voice_aligner_updates(aligner);
    const double delay_after_one = audio_voice_aligner_delay(aligner);
    const AudioResult remainder = audio_voice_aligner_process_i16(
        aligner, g_reference + ALIGNER_TEST_PERIOD + 1u,
        g_capture + ALIGNER_TEST_PERIOD + 1u, g_whole + ALIGNER_TEST_PERIOD + 1u,
        ALIGNER_TEST_PERIOD - 1u);
    ASSERT_EQ(failed, AUDIO_FAILED);
    ASSERT_EQ(one, AUDIO_OK);
    ASSERT_EQ(updates_after_one, 1u);
    ASSERT_FINITE_NEAR(delay_after_one, 0.0, 0.0);
    ASSERT_EQ(remainder, AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 2u);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 12.5, 0.25);
    audio_voice_aligner_destroy(aligner);
}

static bool reset_matches_fresh(bool use_gcc)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *used = NULL;
    AudioVoiceAligner *fresh = NULL;
    const AudioResult a = use_gcc ? audio_voice_aligner_create_gcc(&config, &used)
                                  : audio_voice_aligner_create(&config, &used);
    const AudioResult b = use_gcc ? audio_voice_aligner_create_gcc(&config, &fresh)
                                  : audio_voice_aligner_create(&config, &fresh);
    if (a != AUDIO_OK || b != AUDIO_OK) return false;
    make_fractional_echo(12.5);
    const u32 primed = ALIGNER_TEST_PERIOD + 1000u;
    bool ok = audio_voice_aligner_process_i16(used, g_reference, g_capture, g_whole,
                                              primed) == AUDIO_OK &&
              audio_voice_aligner_updates(used) == 1u &&
              audio_voice_aligner_locked(used) &&
              audio_voice_aligner_delay(used) > 12.0;
    audio_voice_aligner_reset(used);
    ok = ok && audio_voice_aligner_updates(used) == 0u &&
         audio_voice_aligner_delay(used) == 0.0 &&
         !audio_voice_aligner_locked(used) &&
         audio_voice_aligner_rejections(used) == 0u &&
         audio_voice_aligner_correlation(used) == 0.0 &&
         audio_voice_aligner_uses_gcc(used) == use_gcc;
    make_fractional_echo(20.25);
    const u32 total = 3u * ALIGNER_TEST_PERIOD;
    for (u32 n = 0u; ok && n < total; n += 1531u) {
        const u32 count = total - n < 1531u ? total - n : 1531u;
        ok = audio_voice_aligner_process_i16(used, g_reference + n, g_capture + n,
                                             g_whole + n, count) == AUDIO_OK &&
             audio_voice_aligner_process_i16(fresh, g_reference + n, g_capture + n,
                                             g_chunked + n, count) == AUDIO_OK &&
             audio_voice_aligner_updates(used) == audio_voice_aligner_updates(fresh) &&
             audio_voice_aligner_delay(used) == audio_voice_aligner_delay(fresh);
    }
    ok = ok && memcmp(g_whole, g_chunked, total * sizeof(i16)) == 0 &&
         audio_voice_aligner_updates(used) == 3u &&
         fabs(audio_voice_aligner_delay(used) - 20.25) <= 0.25;
    audio_voice_aligner_destroy(used);
    audio_voice_aligner_destroy(fresh);
    return ok;
}

TEST(reset_matches_a_fresh_aligner)
{
    audio_voice_aligner_reset(NULL);
    ASSERT_TRUE(reset_matches_fresh(false));
    ASSERT_TRUE(reset_matches_fresh(true));
}

static double zero_lag_correlation(const i16 *a, const i16 *b, u32 begin, u32 end)
{
    double ab = 0.0, aa = 0.0, bb = 0.0;
    for (u32 n = begin; n < end; ++n) {
        ab += (double)a[n] * b[n];
        aa += (double)a[n] * a[n];
        bb += (double)b[n] * b[n];
    }
    return aa > 0.0 && bb > 0.0 ? ab / sqrt(aa * bb) : 0.0;
}

static double aligned_correlation(bool sinc, double *delay)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    if (!aligner) return -2.0;
    if (audio_voice_aligner_set_sinc(aligner, sinc) != AUDIO_OK) return -2.0;
    make_fractional_echo(12.5);
    const u32 total = 2u * ALIGNER_TEST_PERIOD;
    if (audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                        total) != AUDIO_OK) {
        return -2.0;
    }
    *delay = audio_voice_aligner_delay(aligner);
    audio_voice_aligner_destroy(aligner);
    return zero_lag_correlation(g_whole, g_capture, ALIGNER_TEST_PERIOD + 64u, total);
}

TEST(sinc_and_crossfade_settings_validate_and_default_off)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    ASSERT_FALSE(audio_voice_aligner_sinc(aligner));
    ASSERT_EQ(audio_voice_aligner_crossfade_frames(aligner), 0u);
    ASSERT_EQ(audio_voice_aligner_set_sinc(NULL, true), AUDIO_INVALID);
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(NULL, 4u), AUDIO_INVALID);
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(aligner, 48001u), AUDIO_INVALID);
    ASSERT_FALSE(audio_voice_aligner_sinc(NULL));
    ASSERT_EQ(audio_voice_aligner_crossfade_frames(NULL), 0u);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, true), AUDIO_OK);
    ASSERT_TRUE(audio_voice_aligner_sinc(aligner));
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(aligner, 480u), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_crossfade_frames(aligner), 480u);
    /* below the sinc latency the output is late by the fixed 8 frames */
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 8.0, 0.0);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, false), AUDIO_OK);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 0.0, 0.0);
    audio_voice_aligner_destroy(aligner);
}

TEST(sinc_mode_compensates_its_latency)
{
    double linear_delay = 0.0, sinc_delay = 0.0;
    const double linear = aligned_correlation(false, &linear_delay);
    const double sinc = aligned_correlation(true, &sinc_delay);
    ASSERT_FINITE_NEAR(linear_delay, 12.5, 0.25);
    ASSERT_FINITE_NEAR(sinc_delay, 12.5, 0.25);
    /* an uncompensated 8-frame lag correlates near zero */
    ASSERT_TRUE(sinc > 0.95);
    ASSERT_TRUE(sinc > linear + 0.03);
}

TEST(updates_during_a_fade_are_skipped_not_failed)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(aligner, 6000u), AUDIO_OK);
    make_fractional_echo(12.5);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD + 1u), AUDIO_OK);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 12.5, 0.25);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, true), AUDIO_REJECTED);
    ASSERT_FALSE(audio_voice_aligner_sinc(aligner));
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(aligner, 0u), AUDIO_REJECTED);
    /* the second update lands 4096 frames into the 6000-frame fade */
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference + ALIGNER_TEST_PERIOD + 1u,
                                               g_capture + ALIGNER_TEST_PERIOD + 1u,
                                               g_whole + ALIGNER_TEST_PERIOD + 1u,
                                               3u * ALIGNER_TEST_PERIOD - 1u), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 4u);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 12.5, 0.25);
    audio_voice_aligner_destroy(aligner);
}

static bool configured_reset_matches_fresh(void)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *used = create_aligner(&config);
    AudioVoiceAligner *fresh = create_aligner(&config);
    if (!used || !fresh) return false;
    bool ok = audio_voice_aligner_set_sinc(used, true) == AUDIO_OK &&
              audio_voice_aligner_set_crossfade_frames(used, 1000u) == AUDIO_OK &&
              audio_voice_aligner_set_sinc(fresh, true) == AUDIO_OK &&
              audio_voice_aligner_set_crossfade_frames(fresh, 1000u) == AUDIO_OK;
    make_fractional_echo(12.5);
    ok = ok && audio_voice_aligner_process_i16(used, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD + 300u) == AUDIO_OK;
    audio_voice_aligner_reset(used);
    ok = ok && audio_voice_aligner_sinc(used) &&
         audio_voice_aligner_crossfade_frames(used) == 1000u &&
         audio_voice_aligner_delay(used) == audio_voice_aligner_delay(fresh) &&
         audio_voice_aligner_set_crossfade_frames(used, 1000u) == AUDIO_OK;
    make_fractional_echo(20.25);
    const u32 total = 3u * ALIGNER_TEST_PERIOD;
    ok = ok && audio_voice_aligner_process_i16(used, g_reference, g_capture, g_whole,
                                               total) == AUDIO_OK &&
         audio_voice_aligner_process_i16(fresh, g_reference, g_capture, g_chunked,
                                         total) == AUDIO_OK &&
         memcmp(g_whole, g_chunked, total * sizeof(i16)) == 0 &&
         audio_voice_aligner_delay(used) == audio_voice_aligner_delay(fresh);
    audio_voice_aligner_destroy(used);
    audio_voice_aligner_destroy(fresh);
    return ok;
}

TEST(configured_reset_matches_a_fresh_configured_aligner)
{
    ASSERT_TRUE(configured_reset_matches_fresh());
}

TEST(switching_sinc_after_a_measurement_keeps_the_total_delay)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    make_fractional_echo(12.5);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD), AUDIO_OK);
    const double measured = audio_voice_aligner_delay(aligner);
    ASSERT_FINITE_NEAR(measured, 12.5, 0.25);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, true), AUDIO_OK);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), measured, 1e-12);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, false), AUDIO_OK);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), measured, 1e-12);
    audio_voice_aligner_reset(aligner);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, true), AUDIO_OK);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), 8.0, 0.0);
    audio_voice_aligner_destroy(aligner);
}

TEST(switching_sinc_is_immediate_and_keeps_the_crossfade)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    make_fractional_echo(12.5);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD), AUDIO_OK);
    const double measured = audio_voice_aligner_delay(aligner);
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(aligner, 480u), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, true), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_crossfade_frames(aligner), 480u);
    /* accepted only when the switch started no fade */
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(aligner, 480u), AUDIO_OK);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), measured, 1e-12);
    audio_voice_aligner_destroy(aligner);
}

TEST(a_skipped_update_is_not_reapplied_by_a_mode_switch)
{
    const AudioVoiceAlignerConfig config = test_config();
    AudioVoiceAligner *aligner = create_aligner(&config);
    ASSERT_NOT_NULL(aligner);
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(aligner, 6000u), AUDIO_OK);
    make_fractional_echo(12.5);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference, g_capture, g_whole,
                                               ALIGNER_TEST_PERIOD), AUDIO_OK);
    const double applied = audio_voice_aligner_delay(aligner);
    /* a new echo: the second update measures a different delay mid-fade */
    make_fractional_echo(30.0);
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, g_reference + ALIGNER_TEST_PERIOD,
                                               g_capture + ALIGNER_TEST_PERIOD,
                                               g_whole + ALIGNER_TEST_PERIOD,
                                               ALIGNER_TEST_PERIOD + 2000u), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_updates(aligner), 2u);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), applied, 0.0);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, true), AUDIO_OK);
    ASSERT_FINITE_NEAR(audio_voice_aligner_delay(aligner), applied, 1e-12);
    audio_voice_aligner_destroy(aligner);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_configuration_and_calls);
    RUN_TEST(known_fractional_echo_updates_at_exact_period);
    RUN_TEST(irregular_chunks_match_whole_blocks);
    RUN_TEST(silent_capture_rejects_without_moving_delay);
    RUN_TEST(gcc_constructor_applies_known_delay);
    RUN_TEST(delay_failure_restores_update_schedule);
    RUN_TEST(reset_matches_a_fresh_aligner);
    RUN_TEST(sinc_and_crossfade_settings_validate_and_default_off);
    RUN_TEST(sinc_mode_compensates_its_latency);
    RUN_TEST(updates_during_a_fade_are_skipped_not_failed);
    RUN_TEST(configured_reset_matches_a_fresh_configured_aligner);
    RUN_TEST(switching_sinc_after_a_measurement_keeps_the_total_delay);
    RUN_TEST(switching_sinc_is_immediate_and_keeps_the_crossfade);
    RUN_TEST(a_skipped_update_is_not_reapplied_by_a_mode_switch);
TEST_MAIN_END()
