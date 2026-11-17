/* audio_drift_resampler: validation, identity/decimation, upsampling/chunks,
 * capacity/reset and a real drift-estimate ratio. */
#include "test_framework.h"

#include <audio/audio_drift_resampler.h>
#include <audio/audio_drift_estimator.h>

#include <math.h>
#include <string.h>

#define ASSERT_FINITE_NEAR(a, b, eps) do { \
    const double actual_ = (double)(a); \
    const double expected_ = (double)(b); \
    ASSERT_TRUE(isfinite(actual_)); \
    ASSERT_TRUE(isfinite(expected_)); \
    ASSERT_TRUE(fabs(actual_ - expected_) <= (double)(eps)); \
} while (0)

static void fill_input(i16 *in, u32 count) {
    for (u32 i = 0; i < count; ++i) in[i] = (i16)((int)i * 100 - 800);
}

static void assert_same_state(const AudioDriftResampler *a, const AudioDriftResampler *b) {
    ASSERT_FINITE_NEAR(a->ratio, b->ratio, 0.0);
    ASSERT_FINITE_NEAR(a->next_output, b->next_output, 0.0);
    ASSERT_EQ(a->next_input, b->next_input);
    ASSERT_EQ(a->previous, b->previous);
}

TEST(init_ratio_capacity_and_null_contracts)
{
    AudioDriftResampler state;
    ASSERT_EQ(audio_drift_resampler_init(&state, 1.0), AUDIO_OK);
    const AudioDriftResampler sentinel = state;
    ASSERT_EQ(audio_drift_resampler_init(NULL, 1.0), AUDIO_INVALID);
    const double bad[] = {0.0, 0.09, 10.1, NAN, INFINITY, -1.0};
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        ASSERT_EQ(audio_drift_resampler_init(&state, bad[i]), AUDIO_INVALID);
        ASSERT_EQ(audio_drift_resampler_set_ratio(&state, bad[i]), AUDIO_INVALID);
        assert_same_state(&state, &sentinel);
    }
    ASSERT_EQ(audio_drift_resampler_set_ratio(NULL, 1.0), AUDIO_INVALID);
    ASSERT_FINITE_NEAR(audio_drift_resampler_ratio(NULL), 0.0, 0.0);
    ASSERT_FINITE_NEAR(audio_drift_resampler_ratio(&state), 1.0, 0.0);
    ASSERT_EQ(audio_drift_resampler_output_capacity(NULL, 1u), 0u);
    ASSERT_EQ(audio_drift_resampler_output_capacity(&state, 0u), 0u);
    u32 produced = 99u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, NULL, 0u, NULL, 0u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 0u);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, NULL, 0u, NULL, 0u, NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_drift_resampler_set_ratio(&state, 0.1), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_output_capacity(&state, UINT32_MAX), 0u);
    i16 sample = 1, output = 0;
    produced = 99u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, NULL, 1u, &output, 16u, &produced), AUDIO_INVALID);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, &sample, 1u, NULL, 16u, &produced), AUDIO_INVALID);
    ASSERT_EQ(produced, 99u);
    audio_drift_resampler_reset(NULL);
}

TEST(identity_and_exact_decimation)
{
    i16 in[16], out[18];
    fill_input(in, 16u);
    AudioDriftResampler state;
    ASSERT_EQ(audio_drift_resampler_init(&state, 1.0), AUDIO_OK);
    u32 produced = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 16u, out,
                  audio_drift_resampler_output_capacity(&state, 16u), &produced), AUDIO_OK);
    ASSERT_EQ(produced, 16u);
    ASSERT_EQ(memcmp(in, out, sizeof(in)), 0);
    audio_drift_resampler_reset(&state);
    ASSERT_EQ(audio_drift_resampler_set_ratio(&state, 2.0), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 8u, out,
                  audio_drift_resampler_output_capacity(&state, 8u), &produced), AUDIO_OK);
    ASSERT_EQ(produced, 4u);
    for (u32 i = 0; i < 4u; ++i) ASSERT_EQ(out[i], in[i * 2u]);
}

TEST(half_positions_and_arbitrary_chunks_match)
{
    i16 in[4] = {0, 100, 200, 300};
    i16 out[16];
    AudioDriftResampler state;
    ASSERT_EQ(audio_drift_resampler_init(&state, 0.5), AUDIO_OK);
    u32 produced = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 4u, out, 16u, &produced), AUDIO_OK);
    const i16 expected[] = {0, 50, 100, 150, 200, 250, 300};
    ASSERT_EQ(produced, 7u);
    for (u32 i = 0; i < 7u; ++i) ASSERT_EQ(out[i], expected[i]);

    i16 stream[32], whole[64], chunked[64];
    fill_input(stream, 32u);
    AudioDriftResampler a, b;
    ASSERT_EQ(audio_drift_resampler_init(&a, 0.75), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_init(&b, 0.75), AUDIO_OK);
    u32 whole_count = 0u, chunked_count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&a, stream, 32u, whole, 64u, &whole_count), AUDIO_OK);
    const u32 chunks[] = {1u, 7u, 2u, 13u};
    u32 at = 0u, index = 0u;
    while (at < 32u) {
        u32 n = 32u - at < chunks[index % 4u] ? 32u - at : chunks[index % 4u];
        u32 produced_chunk = 0u;
        ASSERT_EQ(audio_drift_resampler_process_i16(&b, stream + at, n,
                      chunked + chunked_count, 64u - chunked_count, &produced_chunk), AUDIO_OK);
        chunked_count += produced_chunk;
        at += n;
        ++index;
    }
    ASSERT_EQ(whole_count, chunked_count);
    ASSERT_EQ(memcmp(whole, chunked, sizeof(i16) * whole_count), 0);
}

TEST(ratio_changes_preserve_the_stream_position)
{
    i16 in[] = {0, 100, 300, 600, 1000, 1500, 2100, 2800};
    i16 out[16];
    AudioDriftResampler state;
    ASSERT_EQ(audio_drift_resampler_init(&state, 0.5), AUDIO_OK);
    u32 count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 2u, out, 16u, &count), AUDIO_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_EQ(audio_drift_resampler_set_ratio(&state, 2.0), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in + 2u, 6u, out + 3u, 13u, &count), AUDIO_OK);
    ASSERT_EQ(count, 3u);
    const i16 expected[] = {0, 50, 100, 200, 800, 1800};
    for (u32 i = 0; i < 6u; ++i) ASSERT_EQ(out[i], expected[i]);
    ASSERT_EQ(state.next_input, 8u);
    ASSERT_FINITE_NEAR(state.next_output, 7.5, 1e-12);
}

TEST(capacity_failure_is_atomic_and_reset_matches_fresh)
{
    i16 in[4] = {0, 100, 200, 300};
    i16 out[16];
    AudioDriftResampler state;
    ASSERT_EQ(audio_drift_resampler_init(&state, 0.5), AUDIO_OK);
    u32 produced = 99u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 4u, out, 0u, &produced), AUDIO_INVALID);
    ASSERT_EQ(produced, 99u);
    ASSERT_FINITE_NEAR(state.next_output, 0.0, 0.0);
    ASSERT_EQ(state.next_input, 0u);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 4u, out, 16u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 7u);
    ASSERT_EQ(audio_drift_resampler_set_ratio(&state, 0.75), AUDIO_OK);
    audio_drift_resampler_reset(&state);
    ASSERT_FINITE_NEAR(audio_drift_resampler_ratio(&state), 0.75, 0.0);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 4u, out, 16u, &produced), AUDIO_OK);
    AudioDriftResampler fresh;
    ASSERT_EQ(audio_drift_resampler_init(&fresh, 0.75), AUDIO_OK);
    i16 expected[16];
    u32 fresh_count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&fresh, in, 4u, expected, 16u, &fresh_count), AUDIO_OK);
    ASSERT_EQ(produced, fresh_count);
    ASSERT_EQ(memcmp(out, expected, sizeof(i16) * produced), 0);

    AudioDriftResampler uninterrupted = state;
    const u32 required = audio_drift_resampler_output_capacity(&state, 4u);
    ASSERT_TRUE(required > 1u);
    i16 retry[16];
    memset(retry, 0x55, sizeof(retry));
    i16 before_bytes[16];
    memcpy(before_bytes, retry, sizeof(retry));
    produced = 99u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 4u, retry,
                  required - 1u, &produced), AUDIO_INVALID);
    ASSERT_EQ(produced, 99u);
    assert_same_state(&state, &uninterrupted);
    ASSERT_EQ(memcmp(retry, before_bytes, sizeof(retry)), 0);
    u32 retry_count = 0u, uninterrupted_count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 4u, out, 16u, &retry_count), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&uninterrupted, in, 4u, retry, 16u,
                  &uninterrupted_count), AUDIO_OK);
    ASSERT_EQ(retry_count, uninterrupted_count);
    ASSERT_EQ(memcmp(out, retry, sizeof(i16) * retry_count), 0);
}

TEST(a_real_drift_estimate_drives_the_resampler_ratio)
{
    const AudioDriftEstimatorConfig config = {8u, 0.2f, 1000.0f};
    AudioDriftEstimator *est = NULL;
    ASSERT_EQ(audio_drift_estimator_create(&config, &est), AUDIO_OK);
    for (u32 i = 0; i < 8u; ++i) {
        const u64 frame = i * 1000u;
        ASSERT_TRUE(audio_drift_estimator_push(est, frame, 10.0 + 50e-6 * frame, 0.9));
    }
    double drift = 0.0, corr = 0.0;
    ASSERT_TRUE(audio_drift_estimator_estimate(est, &drift, &corr));
    ASSERT_FINITE_NEAR(drift, 50.0, 1e-6);
    AudioDriftResampler state;
    ASSERT_EQ(audio_drift_resampler_init(&state, 1.0), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_ratio(&state, 1.0 + drift * 1e-6), AUDIO_OK);
    ASSERT_FINITE_NEAR(audio_drift_resampler_ratio(&state), 1.00005, 1e-12);
    i16 in[16], out[18];
    fill_input(in, 16u);
    u32 produced = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 16u, out, 18u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 15u);
    for (u32 i = 0; i < produced; ++i) ASSERT_EQ(out[i], in[i]);
    audio_drift_estimator_destroy(est);
}

TEST_MAIN_BEGIN()
    RUN_TEST(init_ratio_capacity_and_null_contracts);
    RUN_TEST(identity_and_exact_decimation);
    RUN_TEST(half_positions_and_arbitrary_chunks_match);
    RUN_TEST(ratio_changes_preserve_the_stream_position);
    RUN_TEST(capacity_failure_is_atomic_and_reset_matches_fresh);
    RUN_TEST(a_real_drift_estimate_drives_the_resampler_ratio);
TEST_MAIN_END()
