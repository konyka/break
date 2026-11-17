/* audio_drift_estimator: validation, known slopes, rejection, ring/reset and
 * large-base negative drift. */
#include "test_framework.h"

#include <audio/audio_drift_estimator.h>

#include <math.h>

#define ASSERT_FINITE_NEAR(a, b, eps) do { \
    const double actual_ = (double)(a); \
    const double expected_ = (double)(b); \
    ASSERT_TRUE(isfinite(actual_)); \
    ASSERT_TRUE(isfinite(expected_)); \
    ASSERT_TRUE(fabs(actual_ - expected_) <= (double)(eps)); \
} while (0)

static AudioDriftEstimatorConfig test_config(void) {
    AudioDriftEstimatorConfig config;
    config.window_size = 16u;
    config.min_abs_correlation = 0.2f;
    config.max_abs_drift_ppm = 1000.0f;
    return config;
}

static AudioDriftEstimator *make_estimator(const AudioDriftEstimatorConfig *config) {
    AudioDriftEstimator *est = NULL;
    if (audio_drift_estimator_create(config, &est) != AUDIO_OK) return NULL;
    return est;
}

TEST(create_validates_config_and_initial_state)
{
    const AudioDriftEstimatorConfig config = test_config();
    AudioDriftEstimator *sentinel = make_estimator(&config);
    ASSERT_TRUE(sentinel != NULL);
    AudioDriftEstimator *est = sentinel;
    ASSERT_EQ(audio_drift_estimator_create(NULL, &est), AUDIO_INVALID);
    ASSERT_EQ(audio_drift_estimator_create(&config, NULL), AUDIO_INVALID);
    AudioDriftEstimatorConfig bad = config;
    bad.window_size = 1u;
    ASSERT_EQ(audio_drift_estimator_create(&bad, &est), AUDIO_INVALID);
    bad = config; bad.window_size = 1025u;
    ASSERT_EQ(audio_drift_estimator_create(&bad, &est), AUDIO_INVALID);
    bad = config; bad.min_abs_correlation = -0.1f;
    ASSERT_EQ(audio_drift_estimator_create(&bad, &est), AUDIO_INVALID);
    bad = config; bad.min_abs_correlation = 1.1f;
    ASSERT_EQ(audio_drift_estimator_create(&bad, &est), AUDIO_INVALID);
    bad = config; bad.max_abs_drift_ppm = 0.0f;
    ASSERT_EQ(audio_drift_estimator_create(&bad, &est), AUDIO_INVALID);
    bad = config; bad.max_abs_drift_ppm = 10000.1f;
    ASSERT_EQ(audio_drift_estimator_create(&bad, &est), AUDIO_INVALID);
    bad = config; bad.min_abs_correlation = NAN;
    ASSERT_EQ(audio_drift_estimator_create(&bad, &est), AUDIO_INVALID);
    ASSERT_TRUE(est == sentinel);
    ASSERT_EQ(audio_drift_estimator_count(NULL), 0u);
    ASSERT_EQ(audio_drift_estimator_count(sentinel), 0u);
    double drift = 9.0, corr = 0.5;
    ASSERT_TRUE(!audio_drift_estimator_estimate(sentinel, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, 9.0, 0.0);
    ASSERT_FINITE_NEAR(corr, 0.5, 0.0);
    ASSERT_TRUE(audio_drift_estimator_push(sentinel, 1000u, 1.0, config.min_abs_correlation));
    ASSERT_EQ(audio_drift_estimator_count(sentinel), 1u);
    audio_drift_estimator_reset(NULL);
    audio_drift_estimator_destroy(NULL);
    audio_drift_estimator_destroy(sentinel);
}

TEST(uneven_frames_recover_positive_drift_and_mean_correlation)
{
    const AudioDriftEstimatorConfig config = test_config();
    AudioDriftEstimator *est = make_estimator(&config);
    ASSERT_TRUE(est != NULL);
    double mean = 0.0;
    for (u32 i = 0; i < 16u; ++i) {
        const u64 frame = 1000u + i * 16000u + (i % 3u) * 100u;
        const double delay = 100.0 + 50e-6 * (double)(frame - 1000u);
        const double correlation = (i & 1u) ? 1.0 : 0.8;
        ASSERT_TRUE(audio_drift_estimator_push(est, frame, delay, correlation));
        mean += correlation;
    }
    double drift = 0.0, corr = 0.0;
    ASSERT_TRUE(audio_drift_estimator_estimate(est, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, 50.0, 1e-6);
    ASSERT_FINITE_NEAR(corr, mean / 16.0, 1e-12);
    ASSERT_EQ(audio_drift_estimator_count(est), 16u);
    audio_drift_estimator_reset(est);
    const u64 frames[] = {0u, 1000u, 3000u, 6000u};
    const double delays[] = {1.0, 2.0, 2.0, 4.0};
    for (u32 i = 0; i < 4u; ++i) {
        ASSERT_TRUE(audio_drift_estimator_push(est, frames[i], delays[i], 1.0));
    }
    ASSERT_TRUE(audio_drift_estimator_estimate(est, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, (9.5 / 21.0) * 1000.0, 1e-6);
    ASSERT_FINITE_NEAR(corr, 1.0, 0.0);
    audio_drift_estimator_destroy(est);
}

TEST(rejection_and_degenerate_estimates_leave_state_and_outputs_untouched)
{
    const AudioDriftEstimatorConfig config = test_config();
    AudioDriftEstimator *est = make_estimator(&config);
    ASSERT_TRUE(est != NULL);
    ASSERT_TRUE(audio_drift_estimator_push(est, 100u, 10.0, 0.9));
    ASSERT_TRUE(!audio_drift_estimator_push(est, 200u, 10.1, 0.1));
    ASSERT_TRUE(!audio_drift_estimator_push(est, 200u, NAN, 0.9));
    ASSERT_TRUE(!audio_drift_estimator_push(est, 200u, 10.1, NAN));
    ASSERT_TRUE(!audio_drift_estimator_push(est, 200u, INFINITY, 0.9));
    ASSERT_TRUE(!audio_drift_estimator_push(est, 100u, 10.0, 0.9));
    ASSERT_TRUE(!audio_drift_estimator_push(est, 99u, 10.0, 0.9));
    ASSERT_EQ(audio_drift_estimator_count(est), 1u);
    double drift = 9.0, corr = 0.5;
    ASSERT_TRUE(!audio_drift_estimator_estimate(est, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, 9.0, 0.0);
    ASSERT_FINITE_NEAR(corr, 0.5, 0.0);
    ASSERT_TRUE(audio_drift_estimator_push(est, 200u, 10.1, 0.9));
    ASSERT_TRUE(!audio_drift_estimator_push(est, 200u, 10.1, 0.9));
    ASSERT_EQ(audio_drift_estimator_count(est), 2u);
    audio_drift_estimator_destroy(est);

    AudioDriftEstimatorConfig limited = config;
    limited.max_abs_drift_ppm = 10.0f;
    est = make_estimator(&limited);
    ASSERT_TRUE(est != NULL);
    ASSERT_TRUE(audio_drift_estimator_push(est, 0u, 0.0, 1.0));
    ASSERT_TRUE(audio_drift_estimator_push(est, 1000u, 1.0, 1.0));
    ASSERT_TRUE(!audio_drift_estimator_estimate(est, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, 9.0, 0.0);
    ASSERT_FINITE_NEAR(corr, 0.5, 0.0);
    audio_drift_estimator_destroy(est);
}

TEST(ring_keeps_the_latest_slope_and_reset_allows_reuse)
{
    AudioDriftEstimatorConfig config = test_config();
    config.window_size = 4u;
    AudioDriftEstimator *est = make_estimator(&config);
    ASSERT_TRUE(est != NULL);
    for (u32 i = 0; i < 6u; ++i) {
        const u64 frame = i * 1000u;
        ASSERT_TRUE(audio_drift_estimator_push(est, frame,
                    i < 2u ? (i == 0u ? -20.0 : 30.0) : 5.0 + 25e-6 * frame, 0.9));
    }
    double drift = 0.0, corr = 0.0;
    ASSERT_TRUE(audio_drift_estimator_estimate(est, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, 25.0, 1e-6);
    ASSERT_FINITE_NEAR(corr, 0.9, 1e-12);
    ASSERT_EQ(audio_drift_estimator_count(est), 4u);
    audio_drift_estimator_reset(est);
    ASSERT_EQ(audio_drift_estimator_count(est), 0u);
    ASSERT_TRUE(!audio_drift_estimator_estimate(est, &drift, &corr));
    for (u32 i = 0; i < 6u; ++i) {
        const u64 frame = i * 1000u;
        ASSERT_TRUE(audio_drift_estimator_push(est, frame,
                    i < 2u ? (i == 0u ? -20.0 : 30.0) : 5.0 + 25e-6 * frame, 0.9));
    }
    ASSERT_TRUE(audio_drift_estimator_estimate(est, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, 25.0, 1e-6);
    audio_drift_estimator_destroy(est);
}

TEST(large_frame_base_preserves_negative_drift)
{
    const AudioDriftEstimatorConfig config = test_config();
    AudioDriftEstimator *est = make_estimator(&config);
    ASSERT_TRUE(est != NULL);
    const u64 base = UINT64_MAX - 10000u;
    for (u32 i = 0; i < 8u; ++i) {
        const u64 frame = base + i * 1000u;
        const double delay = 100.0 - 40e-6 * (double)(frame - base);
        ASSERT_TRUE(audio_drift_estimator_push(est, frame, delay, -0.8));
    }
    double drift = 0.0, corr = 0.0;
    ASSERT_TRUE(audio_drift_estimator_estimate(est, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, -40.0, 1e-6);
    ASSERT_FINITE_NEAR(corr, -0.8, 1e-12);
    audio_drift_estimator_destroy(est);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_config_and_initial_state);
    RUN_TEST(uneven_frames_recover_positive_drift_and_mean_correlation);
    RUN_TEST(rejection_and_degenerate_estimates_leave_state_and_outputs_untouched);
    RUN_TEST(ring_keeps_the_latest_slope_and_reset_allows_reuse);
    RUN_TEST(large_frame_base_preserves_negative_drift);
TEST_MAIN_END()
