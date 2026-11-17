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
    ASSERT_EQ(a->sinc, b->sinc);
    ASSERT_EQ(memcmp(a->history, b->history, sizeof(a->history)), 0);
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

static double drift_sinc(double value) {
    const double pi = 3.14159265358979323846;
    return fabs(value) < 1e-12 ? 1.0 : sin(pi * value) / (pi * value);
}

static double drift_sinc_window(int tap) {
    const double pi = 3.14159265358979323846;
    return 0.42 - 0.5 * cos(2.0 * pi * tap / 15.0) +
           0.08 * cos(4.0 * pi * tap / 15.0);
}

static double drift_sinc_reference_value(const i16 *in, u32 available, double position) {
    const double base = floor(position);
    const double fraction = position - base;
    if (fraction == 0.0) {
        const int source = (int)base;
        return source >= 0 && (u32)source < available ? in[source] : 0.0;
    }
    double value = 0.0, weight_sum = 0.0;
    for (int j = -7; j <= 8; ++j) {
        const double weight = drift_sinc(fraction - j) * drift_sinc_window(j + 7);
        const int source = (int)base + j;
        if (source >= 0 && (u32)source < available) value += in[source] * weight;
        weight_sum += weight;
    }
    return value / weight_sum;
}

static i16 drift_sinc_reference_sample(const i16 *in, u32 available, double position) {
    const double rounded = lrint(drift_sinc_reference_value(in, available, position));
    if (rounded > 32767.0) return 32767;
    if (rounded < -32768.0) return -32768;
    return (i16)rounded;
}

static u32 drift_sinc_reference(const i16 *in, u32 frames, double ratio,
                                u32 switch_at, double next_ratio, i16 *out) {
    double position = 0.0;
    u32 produced = 0u;
    for (u32 n = 0; n < frames; ++n) {
        if (n == switch_at) ratio = next_ratio;
        while (position + 8.0 <= (double)n) {
            out[produced++] = drift_sinc_reference_sample(in, n + 1u, position);
            position += ratio;
        }
    }
    return produced;
}

TEST(sinc_mode_validation_and_reset)
{
    AudioDriftResampler state;
    ASSERT_EQ(audio_drift_resampler_set_sinc(NULL, true), AUDIO_INVALID);
    ASSERT_TRUE(!audio_drift_resampler_sinc(NULL));
    ASSERT_EQ(audio_drift_resampler_sinc_extra_delay(NULL), 0u);
    ASSERT_EQ(audio_drift_resampler_init(&state, 1.0), AUDIO_OK);
    ASSERT_TRUE(!audio_drift_resampler_sinc(&state));
    ASSERT_EQ(audio_drift_resampler_sinc_extra_delay(&state), 0u);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&state, true), AUDIO_OK);
    ASSERT_TRUE(audio_drift_resampler_sinc(&state));
    ASSERT_EQ(audio_drift_resampler_sinc_extra_delay(&state), 8u);
    ASSERT_EQ(audio_drift_resampler_set_ratio(&state, 0.75), AUDIO_OK);
    i16 sample = 900, output[4];
    u32 produced = 99u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, &sample, 1u, output, 4u, &produced),
              AUDIO_OK);
    ASSERT_EQ(produced, 0u);
    ASSERT_EQ(state.history[0], 900);
    audio_drift_resampler_reset(&state);
    ASSERT_TRUE(audio_drift_resampler_sinc(&state));
    ASSERT_FINITE_NEAR(audio_drift_resampler_ratio(&state), 0.75, 0.0);
    ASSERT_EQ(state.next_input, 0u);
    ASSERT_FINITE_NEAR(state.next_output, 0.0, 0.0);
    for (u32 i = 0; i < 32u; ++i) ASSERT_EQ(state.history[i], 0);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&state, false), AUDIO_OK);
    ASSERT_TRUE(!audio_drift_resampler_sinc(&state));
    ASSERT_EQ(audio_drift_resampler_sinc_extra_delay(&state), 0u);
    ASSERT_EQ(audio_drift_resampler_init(&state, 1.0), AUDIO_OK);
    ASSERT_TRUE(!audio_drift_resampler_sinc(&state));
}

TEST(sinc_integer_ratios_have_eight_frame_latency)
{
    AudioDriftResampler state;
    i16 in[24], combined[24] = {0}, out[32];
    fill_input(in, 24u);
    ASSERT_EQ(audio_drift_resampler_init(&state, 1.0), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&state, true), AUDIO_OK);
    u32 produced = 99u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 8u, out, 32u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 0u);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in + 8u, 8u, out, 32u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 8u);
    for (u32 i = 0; i < 8u; ++i) ASSERT_EQ(out[i], in[i]);
    i16 zero[8] = {0};
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, zero, 8u, out + 8u, 24u, &produced),
              AUDIO_OK);
    ASSERT_EQ(produced, 8u);
    for (u32 i = 0; i < 16u; ++i) ASSERT_EQ(out[i], in[i]);

    audio_drift_resampler_reset(&state);
    ASSERT_EQ(audio_drift_resampler_set_ratio(&state, 2.0), AUDIO_OK);
    memcpy(combined, in, sizeof(i16) * 16u);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, combined, 24u, out, 32u, &produced),
              AUDIO_OK);
    ASSERT_EQ(produced, 8u);
    for (u32 i = 0; i < 8u; ++i) ASSERT_EQ(out[i], in[i * 2u]);
}

TEST(sinc_fractional_dynamic_ratio_matches_reference_and_chunks)
{
    i16 in[64], expected[128], direct[128], chunked[128];
    for (u32 i = 0; i < 64u; ++i) in[i] = (i16)(((int)i * 1789 % 26000) - 13000);
    const u32 expected_count = drift_sinc_reference(in, 64u, 0.75, 24u, 1.25, expected);
    AudioDriftResampler a, b;
    ASSERT_EQ(audio_drift_resampler_init(&a, 0.75), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_init(&b, 0.75), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&a, true), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&b, true), AUDIO_OK);
    u32 direct_count = 0u, count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&a, in, 24u, direct, 128u, &count), AUDIO_OK);
    direct_count += count;
    ASSERT_EQ(audio_drift_resampler_set_ratio(&a, 1.25), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&a, in + 24u, 40u, direct + direct_count,
                                               128u - direct_count, &count), AUDIO_OK);
    direct_count += count;
    ASSERT_EQ(direct_count, expected_count);
    for (u32 i = 0; i < expected_count; ++i) ASSERT_EQ(direct[i], expected[i]);

    const u32 chunks[] = {1u, 7u, 2u, 13u};
    u32 at = 0u, chunk = 0u, chunked_count = 0u;
    while (at < 64u) {
        if (at == 24u) ASSERT_EQ(audio_drift_resampler_set_ratio(&b, 1.25), AUDIO_OK);
        const u32 n = 64u - at < chunks[chunk % 4u] ? 64u - at : chunks[chunk % 4u];
        ASSERT_EQ(audio_drift_resampler_process_i16(&b, in + at, n, chunked + chunked_count,
                                                   128u - chunked_count, &count), AUDIO_OK);
        chunked_count += count;
        at += n;
        ++chunk;
    }
    ASSERT_EQ(chunked_count, expected_count);
    ASSERT_EQ(memcmp(chunked, expected, sizeof(i16) * expected_count), 0);
}

TEST(sinc_mode_switch_capacity_and_failure_are_atomic)
{
    AudioDriftResampler state;
    i16 in[18], out[32], retry[32];
    fill_input(in, 18u);
    ASSERT_EQ(audio_drift_resampler_init(&state, 1.0), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&state, true), AUDIO_OK);
    u32 count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in, 16u, out, 32u, &count), AUDIO_OK);
    ASSERT_EQ(count, 8u);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&state, false), AUDIO_OK);
    const AudioDriftResampler before = state;
    const u32 required = audio_drift_resampler_output_capacity(&state, 1u);
    ASSERT_EQ(required, 11u);
    memset(retry, 0x55, sizeof(retry));
    i16 retry_before[32];
    memcpy(retry_before, retry, sizeof(retry));
    u32 produced = 99u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in + 16u, 1u, retry,
                                               required - 1u, &produced), AUDIO_INVALID);
    ASSERT_EQ(produced, 99u);
    assert_same_state(&state, &before);
    ASSERT_EQ(memcmp(retry, retry_before, sizeof(retry)), 0);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in + 16u, 1u, out + 8u,
                                               24u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 9u);
    for (u32 i = 0; i < 17u; ++i) ASSERT_EQ(out[i], in[i]);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&state, true), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, in + 17u, 1u, out, 32u,
                                               &produced), AUDIO_OK);
    ASSERT_EQ(produced, 0u);
    i16 zero[8] = {0};
    ASSERT_EQ(audio_drift_resampler_process_i16(&state, zero, 8u, out, 32u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 1u);
    ASSERT_EQ(out[0], in[17]);

    AudioDriftResampler fractional;
    i16 samples[33], fractional_out[64];
    fill_input(samples, 33u);
    ASSERT_EQ(audio_drift_resampler_init(&fractional, 0.75), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&fractional, true), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&fractional, samples, 32u, fractional_out,
                                               64u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 31u);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&fractional, false), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&fractional, samples + 32u, 1u,
                                               fractional_out + 31u, 33u, &produced), AUDIO_OK);
    ASSERT_EQ(produced, 12u);
    for (u32 i = 0; i < 12u; ++i) {
        const double position = 23.25 + 0.75 * i;
        const u32 whole = (u32)position;
        const double fraction = position - whole;
        const i16 expected = (i16)lrint((1.0 - fraction) * samples[whole] +
                                        fraction * samples[whole + 1u]);
        ASSERT_EQ(fractional_out[31u + i], expected);
    }
}

static double drift_tone_amplitude(const i16 *samples, u32 frames, double step) {
    const double pi = 3.14159265358979323846;
    double sine = 0.0, cosine = 0.0;
    for (u32 i = 0; i < frames; ++i) {
        sine += samples[i] * sin(2.0 * pi * i * step);
        cosine += samples[i] * cos(2.0 * pi * i * step);
    }
    return 2.0 * sqrt(sine * sine + cosine * cosine) / frames;
}

TEST(sinc_quality_preserves_tone_and_converged_dc)
{
    const double pi = 3.14159265358979323846;
    i16 in[2048], sinc_out[4098], linear_out[4098];
    for (u32 i = 0; i < 2048u; ++i) in[i] = (i16)lrint(12000.0 * sin(2.0 * pi * i / 6.0));
    AudioDriftResampler sinc_state, linear_state;
    ASSERT_EQ(audio_drift_resampler_init(&sinc_state, 0.5), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_init(&linear_state, 0.5), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&sinc_state, true), AUDIO_OK);
    u32 sinc_count = 0u, linear_count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&sinc_state, in, 2048u, sinc_out, 4098u,
                                               &sinc_count), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&linear_state, in, 2048u, linear_out, 4098u,
                                               &linear_count), AUDIO_OK);
    ASSERT_TRUE(sinc_count >= 1024u && linear_count >= 1024u);
    const double sinc_amplitude = drift_tone_amplitude(sinc_out + sinc_count - 1024u, 1024u,
                                                       1.0 / 12.0);
    const double linear_amplitude = drift_tone_amplitude(linear_out + linear_count - 1024u, 1024u,
                                                         1.0 / 12.0);
    ASSERT_TRUE(sinc_amplitude >= 11400.0);
    ASSERT_TRUE(linear_amplitude < sinc_amplitude * 0.98);

    AudioDriftResampler dc_state;
    i16 dc_in[64], dc_out[128];
    for (u32 i = 0; i < 64u; ++i) dc_in[i] = 1234;
    ASSERT_EQ(audio_drift_resampler_init(&dc_state, 0.75), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&dc_state, true), AUDIO_OK);
    u32 dc_count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&dc_state, dc_in, 64u, dc_out, 128u,
                                               &dc_count), AUDIO_OK);
    ASSERT_TRUE(dc_count >= 16u);
    for (u32 i = dc_count - 16u; i < dc_count; ++i) ASSERT_EQ(dc_out[i], 1234);
}

TEST(sinc_full_scale_overshoot_saturates)
{
    i16 positive[64] = {0}, negative[64] = {0};
    i16 expected_positive[130], expected_negative[130], out_positive[130], out_negative[130];
    for (int j = -7; j <= 8; ++j) {
        const double weight = drift_sinc(0.5 - j) * drift_sinc_window(j + 7);
        const int source = 16 + j;
        positive[source] = weight >= 0.0 ? 32767 : -32768;
        negative[source] = weight >= 0.0 ? -32768 : 32767;
    }
    ASSERT_TRUE(drift_sinc_reference_value(positive, 64u, 16.5) > 32767.0);
    ASSERT_TRUE(drift_sinc_reference_value(negative, 64u, 16.5) < -32768.0);
    const u32 positive_count = drift_sinc_reference(positive, 64u, 0.5, 64u, 0.5,
                                                    expected_positive);
    const u32 negative_count = drift_sinc_reference(negative, 64u, 0.5, 64u, 0.5,
                                                    expected_negative);
    ASSERT_EQ(positive_count, negative_count);
    AudioDriftResampler a, b;
    ASSERT_EQ(audio_drift_resampler_init(&a, 0.5), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_init(&b, 0.5), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&a, true), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_set_sinc(&b, true), AUDIO_OK);
    u32 a_count = 0u, b_count = 0u;
    ASSERT_EQ(audio_drift_resampler_process_i16(&a, positive, 64u, out_positive, 130u,
                                               &a_count), AUDIO_OK);
    ASSERT_EQ(audio_drift_resampler_process_i16(&b, negative, 64u, out_negative, 130u,
                                               &b_count), AUDIO_OK);
    ASSERT_EQ(a_count, positive_count);
    ASSERT_EQ(b_count, negative_count);
    ASSERT_EQ(memcmp(out_positive, expected_positive, sizeof(i16) * positive_count), 0);
    ASSERT_EQ(memcmp(out_negative, expected_negative, sizeof(i16) * negative_count), 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(init_ratio_capacity_and_null_contracts);
    RUN_TEST(identity_and_exact_decimation);
    RUN_TEST(half_positions_and_arbitrary_chunks_match);
    RUN_TEST(ratio_changes_preserve_the_stream_position);
    RUN_TEST(capacity_failure_is_atomic_and_reset_matches_fresh);
    RUN_TEST(a_real_drift_estimate_drives_the_resampler_ratio);
    RUN_TEST(sinc_mode_validation_and_reset);
    RUN_TEST(sinc_integer_ratios_have_eight_frame_latency);
    RUN_TEST(sinc_fractional_dynamic_ratio_matches_reference_and_chunks);
    RUN_TEST(sinc_mode_switch_capacity_and_failure_are_atomic);
    RUN_TEST(sinc_quality_preserves_tone_and_converged_dc);
    RUN_TEST(sinc_full_scale_overshoot_saturates);
TEST_MAIN_END()
