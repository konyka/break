/* audio_residual_echo_suppressor: validation, reference gate/hangover, real
 * NLMS residual suppression, near-end freeze, chunking and reset. */
#include "test_framework.h"

#include <audio/audio_residual_echo_suppressor.h>
#include <audio/audio_echo_canceller.h>

#include <math.h>
#include <string.h>

#define TEST_CAPACITY 17000u

static const double kPi = 3.14159265358979323846;
static i16 g_reference[TEST_CAPACITY];
static i16 g_capture[TEST_CAPACITY];
static i16 g_unsuppressed[TEST_CAPACITY];
static i16 g_chunked[TEST_CAPACITY];

static AudioResidualEchoSuppressorConfig test_config(void) {
    AudioResidualEchoSuppressorConfig config;
    config.sample_rate = 16000u;
    config.reduction_db = 30.0f;
    config.margin_db = 6.0f;
    config.attack_ms = 5.0f;
    config.release_ms = 20.0f;
    config.path_rise_db_per_s = 60.0f;
    config.initial_path_db = -60.0f;
    config.reference_gate_dbfs = -40.0f;
    config.hangover_ms = 20.0f;
    return config;
}

static double rms(const i16 *samples, u32 offset, u32 count) {
    double sum = 0.0;
    for (u32 i = 0; i < count; ++i) {
        const double x = samples[offset + i];
        sum += x * x;
    }
    return sqrt(sum / count);
}

static double tone_amplitude(const i16 *samples, u32 offset, u32 count, double hz) {
    double re = 0.0, im = 0.0;
    for (u32 i = 0; i < count; ++i) {
        const double a = 2.0 * kPi * hz * i / 16000.0;
        re += samples[offset + i] * cos(a);
        im -= samples[offset + i] * sin(a);
    }
    return 2.0 * sqrt(re * re + im * im) / count;
}

TEST(init_validates_configuration_and_accessors)
{
    const AudioResidualEchoSuppressorConfig config = test_config();
    AudioResidualEchoSuppressor sentinel;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&sentinel, &config), AUDIO_OK);
    AudioResidualEchoSuppressor state = sentinel;
    ASSERT_EQ(audio_residual_echo_suppressor_init(NULL, &config), AUDIO_INVALID);
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, NULL), AUDIO_INVALID);
    ASSERT_EQ(memcmp(&state, &sentinel, sizeof(state)), 0);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_gain_db(&state), 0.0, 0.0);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_path_db(&state), -60.0, 0.0);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_gain_db(NULL), 0.0, 0.0);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_path_db(NULL), -120.0, 0.0);

    AudioResidualEchoSuppressorConfig bad = config;
    bad.sample_rate = 7999u;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.sample_rate = 192001u;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.reduction_db = -0.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.reduction_db = 80.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.margin_db = -0.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.margin_db = 40.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.attack_ms = 0.0f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.attack_ms = 1000.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.release_ms = 0.9f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.release_ms = 10000.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.path_rise_db_per_s = 0.0f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.path_rise_db_per_s = 60.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.initial_path_db = -120.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.initial_path_db = 0.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.reference_gate_dbfs = -80.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.reference_gate_dbfs = 0.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.hangover_ms = -0.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.hangover_ms = 1000.1f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.reduction_db = NAN;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.margin_db = NAN;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.attack_ms = NAN;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.release_ms = NAN;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.path_rise_db_per_s = NAN;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.initial_path_db = NAN;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.reference_gate_dbfs = NAN;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    bad = config; bad.hangover_ms = NAN;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_INVALID);
    ASSERT_EQ(memcmp(&state, &sentinel, sizeof(state)), 0);

    audio_residual_echo_suppressor_process_i16(&state, NULL, NULL, 0u, false);
    audio_residual_echo_suppressor_process_i16(&state, NULL, NULL, 1u, false);
    audio_residual_echo_suppressor_process_i16(NULL, NULL, NULL, 1u, true);
    audio_residual_echo_suppressor_reset(NULL);
    ASSERT_EQ(memcmp(&state, &sentinel, sizeof(state)), 0);

    bad.sample_rate = 8000u; bad.reduction_db = 0.0f; bad.margin_db = 0.0f;
    bad.attack_ms = 0.1f; bad.release_ms = 1.0f; bad.path_rise_db_per_s = 0.1f;
    bad.initial_path_db = -120.0f; bad.reference_gate_dbfs = -80.0f; bad.hangover_ms = 0.0f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_OK);
    bad.sample_rate = 192000u; bad.reduction_db = 80.0f; bad.margin_db = 40.0f;
    bad.attack_ms = 1000.0f; bad.release_ms = 10000.0f; bad.path_rise_db_per_s = 60.0f;
    bad.initial_path_db = 0.0f; bad.reference_gate_dbfs = 0.0f; bad.hangover_ms = 1000.0f;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&state, &bad), AUDIO_OK);
}

TEST(no_reference_passes_and_hangover_covers_the_tail)
{
    AudioResidualEchoSuppressorConfig config = test_config();
    config.hangover_ms = 50.0f;
    config.reference_gate_dbfs = -10.0f;
    AudioResidualEchoSuppressor suppressor;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&suppressor, &config), AUDIO_OK);
    for (u32 i = 0; i < 16000u; ++i) {
        const double x = 0.5 * sin(2.0 * kPi * 1000.0 * i / 16000.0);
        g_reference[i] = (i16)lrint(x * 32768.0);
        g_capture[i] = (i16)lrint(0.05 * x * 32768.0);
    }
    memcpy(g_unsuppressed, g_capture, sizeof(i16) * 16000u);
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                16000u, false);
    ASSERT_TRUE(audio_residual_echo_suppressor_gain_db(&suppressor) < -20.0f);
    const double reduction = 20.0 * log10(rms(g_unsuppressed, 15000u, 1000u) /
                                          rms(g_capture, 15000u, 1000u));
    ASSERT_TRUE(reduction > 25.0);
    ASSERT_TRUE(reduction < 35.0);

    for (u32 i = 0; i < 2400u; ++i) {
        g_reference[i] = 0;
        g_capture[i] = 16;
    }
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                800u, false);
    ASSERT_TRUE(audio_residual_echo_suppressor_gain_db(&suppressor) < -20.0f);
    ASSERT_TRUE(isfinite(audio_residual_echo_suppressor_path_db(&suppressor)));
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference + 800u,
                                                g_capture + 800u, 1600u, false);
    ASSERT_TRUE(audio_residual_echo_suppressor_gain_db(&suppressor) > -1.0f);

    const f32 before_pass = audio_residual_echo_suppressor_path_db(&suppressor);
    memset(g_capture, 0, sizeof(i16) * 400u);
    memset(g_reference, 0, sizeof(i16) * 400u);
    for (u32 i = 0; i < 400u; ++i) g_capture[i] = (i16)(i % 100u);
    memcpy(g_chunked, g_capture, sizeof(i16) * 400u);
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                400u, false);
    ASSERT_EQ(memcmp(g_capture, g_chunked, sizeof(i16) * 400u), 0);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_path_db(&suppressor), before_pass, 0.0f);
}

TEST(the_real_canceller_and_suppressor_reduce_a_nonlinear_residual)
{
    const AudioResidualEchoSuppressorConfig config = test_config();
    AudioResidualEchoSuppressor suppressor;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&suppressor, &config), AUDIO_OK);
    const AudioEchoCancellerConfig aec_config = {16000u, 64u, 0.2f, 0.0f, 0.0f};
    AudioEchoCanceller *aec = NULL;
    ASSERT_EQ(audio_echo_canceller_create(&aec_config, &aec), AUDIO_OK);
    const u32 count = 16000u;
    for (u32 i = 0; i < count; ++i) {
        const double x = 0.5 * sin(2.0 * kPi * 1000.0 * i / 16000.0);
        g_reference[i] = (i16)lrint(x * 32768.0);
        const double echo = 0.25 * x + 0.12 * x * fabs(x);
        g_capture[i] = (i16)lrint(echo * 32768.0);
    }
    audio_echo_canceller_process_i16(aec, g_reference, g_capture, count);
    memcpy(g_unsuppressed, g_capture, sizeof(i16) * count);
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                count, false);
    const double before = rms(g_unsuppressed, 12000u, 4000u);
    const double after = rms(g_capture, 12000u, 4000u);
    ASSERT_TRUE(isfinite(before));
    ASSERT_TRUE(isfinite(after));
    ASSERT_TRUE(before > 1.0);
    ASSERT_TRUE(after > 0.0);
    const double reduction_db = 20.0 * log10(before / after);
    ASSERT_TRUE(isfinite(reduction_db));
    ASSERT_TRUE(reduction_db > 10.0);
    audio_echo_canceller_destroy(aec);
}

TEST(near_end_activity_preserves_the_tone_and_freezes_the_path)
{
    const AudioResidualEchoSuppressorConfig config = test_config();
    AudioResidualEchoSuppressor suppressor;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&suppressor, &config), AUDIO_OK);
    const u32 count = 16000u;
    for (u32 i = 0; i < count; ++i) {
        const double x = 0.5 * sin(2.0 * kPi * 1000.0 * i / 16000.0);
        g_reference[i] = (i16)lrint(x * 32768.0);
        g_capture[i] = (i16)lrint(0.05 * x * 32768.0);
    }
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                count, false);
    ASSERT_TRUE(audio_residual_echo_suppressor_gain_db(&suppressor) < -20.0f);
    const f32 closed_path = audio_residual_echo_suppressor_path_db(&suppressor);

    for (u32 i = 0; i < count; ++i) {
        const double x = 0.5 * sin(2.0 * kPi * 1000.0 * i / 16000.0);
        const double near = 0.2 * sin(2.0 * kPi * 440.0 * i / 16000.0);
        g_reference[i] = (i16)lrint(x * 32768.0);
        g_capture[i] = (i16)lrint((near + 0.02 * x) * 32768.0);
    }
    memcpy(g_unsuppressed, g_capture, sizeof(i16) * count);
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                count, true);
    const double before = tone_amplitude(g_unsuppressed, 12000u, 4000u, 440.0);
    const double after = tone_amplitude(g_capture, 12000u, 4000u, 440.0);
    ASSERT_TRUE(isfinite(before));
    ASSERT_TRUE(isfinite(after));
    ASSERT_TRUE(fabs(20.0 * log10(after / before)) < 1.0);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_path_db(&suppressor), closed_path, 0.0);
    ASSERT_TRUE(audio_residual_echo_suppressor_gain_db(&suppressor) > -0.01f);
}

TEST(gain_closes_with_release_and_opens_with_attack)
{
    AudioResidualEchoSuppressorConfig config = test_config();
    config.attack_ms = 100.0f;
    config.release_ms = 1.0f;
    config.initial_path_db = 0.0f;
    config.reference_gate_dbfs = -40.0f;
    AudioResidualEchoSuppressor suppressor;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&suppressor, &config), AUDIO_OK);
    for (u32 i = 0; i < 100u; ++i) {
        const double x = sin(2.0 * kPi * 1000.0 * i / 16000.0);
        g_reference[i] = (i16)lrint(0.5 * x * 32768.0);
        g_capture[i] = (i16)lrint(0.05 * x * 32768.0);
    }
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                100u, false);
    ASSERT_TRUE(audio_residual_echo_suppressor_gain_db(&suppressor) < -20.0f);
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                100u, true);
    ASSERT_TRUE(audio_residual_echo_suppressor_gain_db(&suppressor) < -20.0f);
}

TEST(path_tracking_is_bounded_and_never_exceeds_zero_db)
{
    AudioResidualEchoSuppressorConfig config = test_config();
    config.initial_path_db = -20.0f;
    AudioResidualEchoSuppressor suppressor;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&suppressor, &config), AUDIO_OK);
    const u32 count = 16000u;
    for (u32 i = 0; i < count; ++i) {
        const double x = sin(2.0 * kPi * 1000.0 * i / 16000.0);
        g_reference[i] = (i16)lrint(0.5 * x * 32768.0);
        g_capture[i] = (i16)lrint(0.4 * x * 32768.0);
    }
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                1000u, true);
    const double initial = (double)audio_residual_echo_suppressor_path_db(&suppressor);
    const double step = (double)config.path_rise_db_per_s / config.sample_rate;
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                1u, false);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_path_db(&suppressor), initial + step, 1e-4);
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference + 1u,
                                                g_capture + 1u, 999u, false);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_path_db(&suppressor),
                    initial + 1000.0 * step, 1e-4);
    for (u32 i = 0; i < 100u; ++i) {
        audio_residual_echo_suppressor_process_i16(&suppressor, g_reference + i,
                                                    g_capture + i, 1u, false);
        const double error_power = suppressor.error_mean_square > 1e-12
            ? suppressor.error_mean_square : 1e-12;
        const double reference_power = suppressor.held_reference_power > 1e-12
            ? suppressor.held_reference_power : 1e-12;
        const double ratio = 10.0 * log10(error_power / reference_power);
        const double learned = ratio < 0.0 ? ratio : 0.0;
        ASSERT_TRUE((double)audio_residual_echo_suppressor_path_db(&suppressor) <= learned + 1e-5);
    }
    ASSERT_TRUE(audio_residual_echo_suppressor_path_db(&suppressor) < -10.0f);
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference + 100u,
                                                g_capture + 100u, count - 100u, false);
    const f32 loud_path = audio_residual_echo_suppressor_path_db(&suppressor);
    ASSERT_TRUE(loud_path > -5.0f);
    ASSERT_TRUE(loud_path <= 0.0f);
    for (u32 i = 0; i < count; ++i) {
        g_capture[i] = (i16)lrint(0.01 * sin(2.0 * kPi * 1000.0 * i / 16000.0) * 32768.0);
    }
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                2000u, false);
    ASSERT_TRUE(audio_residual_echo_suppressor_path_db(&suppressor) < loud_path - 10.0f);
    for (u32 i = 0; i < count; ++i) {
        g_capture[i] = (i16)lrint(sin(2.0 * kPi * 1000.0 * i / 16000.0) * 32767.0);
    }
    audio_residual_echo_suppressor_process_i16(&suppressor, g_reference, g_capture,
                                                count, false);
    ASSERT_FLOAT_EQ(audio_residual_echo_suppressor_path_db(&suppressor), 0.0, 1e-4);
}

TEST(chunking_reset_and_silence_are_deterministic)
{
    AudioResidualEchoSuppressorConfig config = test_config();
    config.initial_path_db = 0.0f;
    AudioResidualEchoSuppressor whole, chunked;
    ASSERT_EQ(audio_residual_echo_suppressor_init(&whole, &config), AUDIO_OK);
    ASSERT_EQ(audio_residual_echo_suppressor_init(&chunked, &config), AUDIO_OK);
    const u32 count = 3000u;
    for (u32 i = 0; i < count; ++i) {
        const double x = 0.4 * sin(2.0 * kPi * 800.0 * i / 16000.0);
        g_reference[i] = (i16)lrint(x * 32768.0);
        g_capture[i] = (i16)lrint(0.08 * x * fabs(x) * 32768.0);
    }
    memcpy(g_unsuppressed, g_capture, sizeof(i16) * count);
    memcpy(g_chunked, g_capture, sizeof(i16) * count);
    audio_residual_echo_suppressor_process_i16(&whole, g_reference, g_capture,
                                                count, false);
    const u32 chunks[] = {1u, 7u, 255u, 13u};
    u32 offset = 0u, index = 0u;
    while (offset < count) {
        u32 n = chunks[index % 4u];
        if (n > count - offset) n = count - offset;
        audio_residual_echo_suppressor_process_i16(&chunked, g_reference + offset,
                                                   g_chunked + offset, n, false);
        offset += n;
        ++index;
    }
    ASSERT_EQ(memcmp(g_capture, g_chunked, sizeof(i16) * count), 0);
    ASSERT_TRUE(whole.gain_db < -10.0);
    whole.hold = 7u;
    audio_residual_echo_suppressor_reset(&whole);
    ASSERT_EQ(whole.hold, 0u);
    ASSERT_FLOAT_EQ(whole.reference_mean_square, 0.0, 0.0);
    ASSERT_FLOAT_EQ(whole.error_mean_square, 0.0, 0.0);
    ASSERT_FLOAT_EQ(whole.held_reference_power, 0.0, 0.0);
    ASSERT_EQ(audio_residual_echo_suppressor_init(&chunked, &config), AUDIO_OK);
    memcpy(g_capture, g_unsuppressed, sizeof(i16) * count);
    memcpy(g_chunked, g_unsuppressed, sizeof(i16) * count);
    audio_residual_echo_suppressor_process_i16(&whole, g_reference, g_capture,
                                                count, false);
    audio_residual_echo_suppressor_process_i16(&chunked, g_reference, g_chunked,
                                                count, false);
    ASSERT_EQ(memcmp(g_capture, g_chunked, sizeof(i16) * count), 0);
    memset(g_capture, 0, sizeof(i16) * count);
    memset(g_reference, 0, sizeof(i16) * count);
    audio_residual_echo_suppressor_process_i16(&whole, g_reference, g_capture,
                                                count, false);
    for (u32 i = 0; i < count; ++i) ASSERT_EQ(g_capture[i], 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(init_validates_configuration_and_accessors);
    RUN_TEST(no_reference_passes_and_hangover_covers_the_tail);
    RUN_TEST(the_real_canceller_and_suppressor_reduce_a_nonlinear_residual);
    RUN_TEST(near_end_activity_preserves_the_tone_and_freezes_the_path);
    RUN_TEST(gain_closes_with_release_and_opens_with_attack);
    RUN_TEST(path_tracking_is_bounded_and_never_exceeds_zero_db);
    RUN_TEST(chunking_reset_and_silence_are_deterministic);
TEST_MAIN_END()
