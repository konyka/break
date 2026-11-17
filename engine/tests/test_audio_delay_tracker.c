/* audio_delay_tracker: validation, locking, confidence loss, time-limited
 * drift, chunking, reset and estimator failure. */
#include "test_framework.h"

#include <audio/audio_delay_tracker.h>

#include <math.h>
#include <string.h>

#define N 20000u

static const double kPi = 3.14159265358979323846;
static u32 g_seed = 0x7412ABCDu;
static i16 g_ref[N], g_cap[N];

static double rnd(void) {
    g_seed = g_seed * 1664525u + 1013904223u;
    return (double)(g_seed >> 8) / 8388608.0 - 1.0;
}

#define ASSERT_FINITE_NEAR(a, b, eps) do { \
    const double actual_ = (double)(a); \
    const double expected_ = (double)(b); \
    ASSERT_TRUE(isfinite(actual_)); \
    ASSERT_TRUE(isfinite(expected_)); \
    ASSERT_TRUE(fabs(actual_ - expected_) <= (double)(eps)); \
} while (0)

static double sinc(double x) {
    return fabs(x) < 1e-12 ? 1.0 : sin(kPi * x) / (kPi * x);
}

static void make_fractional_echo(double delay) {
    for (u32 n = 0; n < N; ++n) g_ref[n] = (i16)lrint(rnd() * 12000.0);
    const int center = (int)floor(delay);
    for (u32 n = 0; n < N; ++n) {
        double value = 0.0;
        for (int k = center - 16; k <= center + 16; ++k) {
            const int source = (int)n - k;
            if (source >= 0 && source < (int)N) value += g_ref[source] * sinc((double)k - delay);
        }
        g_cap[n] = (i16)lrint(0.4 * value);
    }
}

static void make_inverted_fractional_echo(double delay) {
    make_fractional_echo(delay);
    for (u32 n = 0; n < N; ++n) g_cap[n] = (i16)-g_cap[n];
}

static void make_uncorrelated(void) {
    for (u32 n = 0; n < N; ++n) {
        g_ref[n] = (i16)lrint(rnd() * 12000.0);
        g_cap[n] = (i16)lrint(rnd() * 12000.0);
    }
}

static AudioDelayTrackerConfig test_config(void) {
    AudioDelayTrackerConfig config;
    config.sample_rate = 16000u;
    config.max_delay_frames = 64u;
    config.window_frames = 2048u;
    config.min_abs_correlation = 0.2f;
    config.max_slew_frames_per_s = 10.0f;
    config.lock_count = 2u;
    config.hold_updates = 2u;
    return config;
}

static AudioDelayTracker *make_tracker(const AudioDelayTrackerConfig *config) {
    AudioDelayTracker *tracker = NULL;
    if (audio_delay_tracker_create(config, &tracker) != AUDIO_OK) return NULL;
    return tracker;
}

TEST(create_validates_config_and_initial_accessors)
{
    const AudioDelayTrackerConfig config = test_config();
    AudioDelayTracker *sentinel = make_tracker(&config);
    ASSERT_TRUE(sentinel != NULL);
    AudioDelayTracker *tracker = sentinel;
    ASSERT_EQ(audio_delay_tracker_create(NULL, &tracker), AUDIO_INVALID);
    ASSERT_EQ(audio_delay_tracker_create(&config, NULL), AUDIO_INVALID);
    AudioDelayTrackerConfig bad = config;
    bad.sample_rate = 7999u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.sample_rate = 192001u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.max_delay_frames = 0u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.max_delay_frames = AUDIO_DELAY_ESTIMATOR_MAX_DELAY + 1u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.window_frames = 15u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.window_frames = AUDIO_DELAY_ESTIMATOR_MAX_WINDOW + 1u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.min_abs_correlation = -0.1f;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.min_abs_correlation = 1.1f;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.max_slew_frames_per_s = 0.0f;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.max_slew_frames_per_s = 96000.1f;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.lock_count = 0u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.lock_count = 1001u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.hold_updates = 1001u;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    bad = config; bad.min_abs_correlation = NAN;
    ASSERT_EQ(audio_delay_tracker_create(&bad, &tracker), AUDIO_INVALID);
    ASSERT_TRUE(tracker == sentinel);
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(NULL), 0.0, 0.0);
    ASSERT_FINITE_NEAR(audio_delay_tracker_correlation(NULL), 0.0, 0.0);
    ASSERT_TRUE(!audio_delay_tracker_locked(NULL));
    ASSERT_EQ(audio_delay_tracker_rejections(NULL), 0u);
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(sentinel), 0.0, 0.0);
    ASSERT_TRUE(!audio_delay_tracker_locked(sentinel));
    ASSERT_EQ(audio_delay_tracker_rejections(sentinel), 0u);
    audio_delay_tracker_reset(NULL);
    audio_delay_tracker_push_i16(NULL, g_ref, g_cap, 1u);
    ASSERT_TRUE(!audio_delay_tracker_update(NULL));
    audio_delay_tracker_destroy(NULL);
    audio_delay_tracker_destroy(sentinel);
}

TEST(fractional_measurements_lock_after_the_configured_count)
{
    const AudioDelayTrackerConfig config = test_config();
    AudioDelayTracker *tracker = make_tracker(&config);
    ASSERT_TRUE(tracker != NULL);
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_TRUE(!audio_delay_tracker_locked(tracker));
    ASSERT_TRUE(fabs(audio_delay_tracker_delay(tracker) - 12.5) < 0.25);
    ASSERT_TRUE(audio_delay_tracker_correlation(tracker) > 0.5);
    make_uncorrelated();
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(!audio_delay_tracker_update(tracker));
    ASSERT_TRUE(!audio_delay_tracker_locked(tracker));
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_TRUE(!audio_delay_tracker_locked(tracker));
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_TRUE(audio_delay_tracker_locked(tracker));
    ASSERT_EQ(audio_delay_tracker_rejections(tracker), 1u);
    make_inverted_fractional_echo(12.5);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_TRUE(audio_delay_tracker_correlation(tracker) < -0.5);
    ASSERT_TRUE(fabs(audio_delay_tracker_delay(tracker) - 12.5) < 0.25);
    ASSERT_TRUE(audio_delay_tracker_locked(tracker));
    audio_delay_tracker_destroy(tracker);
}

TEST(low_confidence_holds_then_unlocks_without_moving_delay)
{
    const AudioDelayTrackerConfig config = test_config();
    AudioDelayTracker *tracker = make_tracker(&config);
    ASSERT_TRUE(tracker != NULL);
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_TRUE(audio_delay_tracker_locked(tracker));
    make_uncorrelated();
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(!audio_delay_tracker_update(tracker));
    ASSERT_EQ(audio_delay_tracker_rejections(tracker), 1u);
    ASSERT_TRUE(audio_delay_tracker_locked(tracker));
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    const double accepted_delay = audio_delay_tracker_delay(tracker);
    make_uncorrelated();
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(!audio_delay_tracker_update(tracker));
    ASSERT_EQ(audio_delay_tracker_rejections(tracker), 2u);
    ASSERT_TRUE(audio_delay_tracker_locked(tracker));
    ASSERT_TRUE(!audio_delay_tracker_update(tracker));
    ASSERT_EQ(audio_delay_tracker_rejections(tracker), 3u);
    ASSERT_TRUE(audio_delay_tracker_locked(tracker));
    ASSERT_TRUE(!audio_delay_tracker_update(tracker));
    ASSERT_EQ(audio_delay_tracker_rejections(tracker), 4u);
    ASSERT_TRUE(!audio_delay_tracker_locked(tracker));
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(tracker), accepted_delay, 0.0);
    audio_delay_tracker_destroy(tracker);

    AudioDelayTrackerConfig zero_config = test_config();
    zero_config.lock_count = 1u;
    zero_config.hold_updates = 0u;
    tracker = make_tracker(&zero_config);
    ASSERT_TRUE(tracker != NULL);
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_TRUE(audio_delay_tracker_locked(tracker));
    const double locked_delay = audio_delay_tracker_delay(tracker);
    make_uncorrelated();
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(!audio_delay_tracker_update(tracker));
    ASSERT_TRUE(!audio_delay_tracker_locked(tracker));
    ASSERT_EQ(audio_delay_tracker_rejections(tracker), 1u);
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(tracker), locked_delay, 0.0);
    audio_delay_tracker_destroy(tracker);
}

TEST(locked_drift_is_limited_by_pushed_time)
{
    AudioDelayTrackerConfig config = test_config();
    config.max_slew_frames_per_s = 2.0f;
    config.lock_count = 1u;
    AudioDelayTracker *tracker = make_tracker(&config);
    ASSERT_TRUE(tracker != NULL);
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_TRUE(audio_delay_tracker_locked(tracker));
    const double initial = audio_delay_tracker_delay(tracker);
    make_fractional_echo(30.25);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(tracker), initial + 2.5, 1e-12);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(tracker), initial + 2.5, 1e-12);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(tracker), initial + 5.0, 1e-12);
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(tracker, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(tracker));
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(tracker), initial + 2.5, 1e-12);
    audio_delay_tracker_destroy(tracker);
}

TEST(chunking_reset_and_estimator_failure_match_a_fresh_tracker)
{
    const AudioDelayTrackerConfig config = test_config();
    AudioDelayTracker *whole = make_tracker(&config);
    AudioDelayTracker *chunked = make_tracker(&config);
    ASSERT_TRUE(whole != NULL && chunked != NULL);
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(whole, g_ref, g_cap, N);
    const u32 chunks[] = {1u, 7u, 480u};
    u32 at = 0u, index = 0u;
    while (at < N) {
        u32 n = N - at < chunks[index % 3u] ? N - at : chunks[index % 3u];
        audio_delay_tracker_push_i16(chunked, g_ref + at, g_cap + at, n);
        at += n;
        ++index;
    }
    ASSERT_TRUE(audio_delay_tracker_update(whole));
    ASSERT_TRUE(audio_delay_tracker_update(chunked));
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(whole), audio_delay_tracker_delay(chunked), 0.0);
    ASSERT_FINITE_NEAR(audio_delay_tracker_correlation(whole),
                    audio_delay_tracker_correlation(chunked), 1e-12);
    ASSERT_TRUE(audio_delay_tracker_update(whole));
    ASSERT_TRUE(audio_delay_tracker_update(chunked));
    ASSERT_EQ(audio_delay_tracker_locked(whole), audio_delay_tracker_locked(chunked));
    make_uncorrelated();
    audio_delay_tracker_push_i16(whole, g_ref, g_cap, N);
    ASSERT_TRUE(!audio_delay_tracker_update(whole));
    ASSERT_EQ(audio_delay_tracker_rejections(whole), 1u);
    audio_delay_tracker_reset(whole);
    ASSERT_EQ(audio_delay_tracker_rejections(whole), 0u);
    audio_delay_tracker_destroy(chunked);
    chunked = make_tracker(&config);
    ASSERT_TRUE(chunked != NULL);
    make_fractional_echo(12.5);
    audio_delay_tracker_push_i16(whole, g_ref, g_cap, N);
    audio_delay_tracker_push_i16(chunked, g_ref, g_cap, N);
    ASSERT_TRUE(audio_delay_tracker_update(whole));
    ASSERT_TRUE(audio_delay_tracker_update(chunked));
    ASSERT_FINITE_NEAR(audio_delay_tracker_delay(whole), audio_delay_tracker_delay(chunked), 0.0);
    ASSERT_EQ(audio_delay_tracker_rejections(whole), 0u);
    audio_delay_tracker_reset(whole);
    audio_delay_tracker_push_i16(whole, g_ref, g_cap, 100u);
    ASSERT_TRUE(!audio_delay_tracker_update(whole));
    ASSERT_EQ(audio_delay_tracker_rejections(whole), 1u);
    ASSERT_TRUE(!audio_delay_tracker_locked(whole));

    AudioDelayTrackerConfig zero_config = config;
    zero_config.min_abs_correlation = 0.0f;
    AudioDelayTracker *zero = make_tracker(&zero_config);
    ASSERT_TRUE(zero != NULL);
    audio_delay_tracker_push_i16(zero, g_ref, g_cap, 100u);
    ASSERT_TRUE(!audio_delay_tracker_update(zero));
    ASSERT_EQ(audio_delay_tracker_rejections(zero), 1u);
    audio_delay_tracker_destroy(zero);
    audio_delay_tracker_destroy(whole);
    audio_delay_tracker_destroy(chunked);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_config_and_initial_accessors);
    RUN_TEST(fractional_measurements_lock_after_the_configured_count);
    RUN_TEST(low_confidence_holds_then_unlocks_without_moving_delay);
    RUN_TEST(locked_drift_is_limited_by_pushed_time);
    RUN_TEST(chunking_reset_and_estimator_failure_match_a_fresh_tracker);
TEST_MAIN_END()
