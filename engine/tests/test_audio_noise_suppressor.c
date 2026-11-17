/* audio_noise_suppressor: configuration, exact unit-gain delay, stationary
 * noise suppression, tone preservation, chunking and reset. */
#include "test_framework.h"

#include <audio/audio_noise_suppressor.h>

#include <math.h>
#include <string.h>

#define TEST_CAPACITY 33000u

static const double kPi = 3.14159265358979323846;
static u32 g_seed = 0x51EED123u;
static i16 g_source[TEST_CAPACITY];
static i16 g_work[TEST_CAPACITY];
static i16 g_reference[TEST_CAPACITY];

static double rnd(void) {
    g_seed = g_seed * 1664525u + 1013904223u;
    return (double)(g_seed >> 8) / 8388608.0 - 1.0;
}

static AudioNoiseSuppressorConfig test_config(void) {
    AudioNoiseSuppressorConfig config;
    config.sample_rate = 16000u;
    config.frame_size = 256u;
    config.max_attenuation_db = 30.0f;
    config.noise_rise_db_per_s = 5.0f;
    config.initial_noise_dbfs = -40.0f;
    return config;
}

static double rms(const i16 *samples, u32 offset, u32 count) {
    double sum = 0.0;
    for (u32 i = 0; i < count; ++i) {
        const double x = (double)samples[offset + i];
        sum += x * x;
    }
    return sqrt(sum / count);
}

static double tone_amplitude(const i16 *samples, u32 offset, u32 count,
                             u32 sample_rate, double hz) {
    double re = 0.0, im = 0.0;
    for (u32 i = 0; i < count; ++i) {
        const double a = 2.0 * kPi * hz * i / sample_rate;
        re += samples[offset + i] * cos(a);
        im -= samples[offset + i] * sin(a);
    }
    return 2.0 * sqrt(re * re + im * im) / count;
}

TEST(create_validates_the_configuration_and_reports_latency)
{
    const AudioNoiseSuppressorConfig config = test_config();
    AudioNoiseSuppressor *sentinel = NULL;
    ASSERT_EQ(audio_noise_suppressor_create(&config, &sentinel), AUDIO_OK);
    AudioNoiseSuppressor *suppressor = sentinel;
    ASSERT_EQ(audio_noise_suppressor_latency_frames(NULL), 0u);
    ASSERT_EQ(audio_noise_suppressor_latency_frames(sentinel), 256u);
    ASSERT_EQ(audio_noise_suppressor_create(NULL, &suppressor), AUDIO_INVALID);
    ASSERT_EQ(audio_noise_suppressor_create(&config, NULL), AUDIO_INVALID);
    ASSERT_TRUE(suppressor == sentinel);

    AudioNoiseSuppressorConfig bad = config;
    bad.sample_rate = 7999u;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.sample_rate = 192001u;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.frame_size = 8u;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.frame_size = 100u;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.frame_size = 2048u;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.max_attenuation_db = -0.1f;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.max_attenuation_db = 80.1f;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.noise_rise_db_per_s = 0.0f;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.noise_rise_db_per_s = 60.1f;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.initial_noise_dbfs = -120.1f;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.initial_noise_dbfs = 0.1f;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    bad = config; bad.max_attenuation_db = NAN;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_INVALID);
    ASSERT_TRUE(suppressor == sentinel);

    bad = config; bad.frame_size = 16u;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_OK);
    ASSERT_EQ(audio_noise_suppressor_latency_frames(suppressor), 16u);
    audio_noise_suppressor_destroy(suppressor);
    bad = config; bad.frame_size = 1024u;
    ASSERT_EQ(audio_noise_suppressor_create(&bad, &suppressor), AUDIO_OK);
    audio_noise_suppressor_destroy(suppressor);

    i16 sample = 123;
    audio_noise_suppressor_process_i16(NULL, &sample, 1u);
    ASSERT_EQ(sample, 123);
    audio_noise_suppressor_process_i16(sentinel, NULL, 0u);
    audio_noise_suppressor_process_i16(sentinel, NULL, 1u);
    audio_noise_suppressor_reset(NULL);
    audio_noise_suppressor_destroy(NULL);
    audio_noise_suppressor_destroy(sentinel);
}

TEST(zero_attenuation_is_the_input_delayed_by_one_frame_size)
{
    const u32 sizes[] = {16u, 64u, 256u, 1024u};
    for (u32 s = 0; s < 4u; ++s) {
        AudioNoiseSuppressorConfig config = test_config();
        config.frame_size = sizes[s];
        config.max_attenuation_db = 0.0f;
        const u32 size = config.frame_size;
        const u32 count = 8u * size + 13u;
        const u32 total = count + size;
        for (u32 i = 0; i < count; ++i) {
            if (i % 17u == 0u) {
                g_source[i] = 32767;
            } else if (i % 19u == 0u) {
                g_source[i] = -32768;
            } else {
                g_source[i] = (i16)lrint(rnd() * 32767.0);
            }
        }
        memset(g_source + count, 0, sizeof(i16) * size);
        memcpy(g_work, g_source, sizeof(i16) * total);
        AudioNoiseSuppressor *suppressor = NULL;
        ASSERT_EQ(audio_noise_suppressor_create(&config, &suppressor), AUDIO_OK);
        audio_noise_suppressor_process_i16(suppressor, g_work, total);
        for (u32 i = 0; i < total; ++i) {
            const i16 expected = i < size ? 0 : g_source[i - size];
            ASSERT_EQ(g_work[i], expected);
        }
        audio_noise_suppressor_destroy(suppressor);
    }
}

TEST(stationary_white_noise_is_attenuated_after_convergence)
{
    AudioNoiseSuppressorConfig config = test_config();
    const u32 count = 32000u;
    const u32 total = count + config.frame_size;
    for (u32 i = 0; i < count; ++i) g_source[i] = (i16)lrint(rnd() * 1000.0);
    memset(g_source + count, 0, sizeof(i16) * config.frame_size);
    memcpy(g_work, g_source, sizeof(i16) * total);
    AudioNoiseSuppressor *suppressor = NULL;
    ASSERT_EQ(audio_noise_suppressor_create(&config, &suppressor), AUDIO_OK);
    audio_noise_suppressor_process_i16(suppressor, g_work, total);
    const double before = rms(g_source, 16000u, 16000u);
    const double after = rms(g_work, 16000u + config.frame_size, 16000u);
    ASSERT_TRUE(isfinite(before));
    ASSERT_TRUE(isfinite(after));
    const double reduction_db = 20.0 * log10(before / after);
    ASSERT_TRUE(reduction_db > 10.0);
    audio_noise_suppressor_destroy(suppressor);

    config.max_attenuation_db = 6.0f;
    memcpy(g_work, g_source, sizeof(i16) * total);
    suppressor = NULL;
    ASSERT_EQ(audio_noise_suppressor_create(&config, &suppressor), AUDIO_OK);
    audio_noise_suppressor_process_i16(suppressor, g_work, total);
    const double limited_after = rms(g_work, 16000u + config.frame_size, 16000u);
    const double limited_db = 20.0 * log10(before / limited_after);
    ASSERT_TRUE(isfinite(limited_db));
    ASSERT_TRUE(limited_db <= 8.0);
    audio_noise_suppressor_destroy(suppressor);
}

TEST(a_tone_in_noise_keeps_its_amplitude)
{
    AudioNoiseSuppressorConfig config = test_config();
    config.noise_rise_db_per_s = 2.0f;
    config.initial_noise_dbfs = -50.0f;
    const u32 count = 16000u;
    const u32 total = count + config.frame_size;
    for (u32 i = 0; i < count; ++i) {
        const double x = 0.2 * sin(2.0 * kPi * 440.0 * i / 16000.0) + 0.01 * rnd();
        g_source[i] = (i16)lrint(x * 32768.0);
    }
    memset(g_source + count, 0, sizeof(i16) * config.frame_size);
    memcpy(g_work, g_source, sizeof(i16) * total);
    AudioNoiseSuppressor *suppressor = NULL;
    ASSERT_EQ(audio_noise_suppressor_create(&config, &suppressor), AUDIO_OK);
    audio_noise_suppressor_process_i16(suppressor, g_work, total);
    const double before = tone_amplitude(g_source, 12000u, 4000u, 16000u, 440.0);
    const double after = tone_amplitude(g_work, 12000u + config.frame_size, 4000u,
                                        16000u, 440.0);
    ASSERT_TRUE(isfinite(before));
    ASSERT_TRUE(isfinite(after));
    const double change_db = 20.0 * log10(after / before);
    ASSERT_TRUE(change_db > -1.0);
    ASSERT_TRUE(change_db < 1.0);
    audio_noise_suppressor_destroy(suppressor);
}

TEST(a_quiet_tone_above_the_initial_floor_is_preserved)
{
    const AudioNoiseSuppressorConfig config = test_config();
    const u32 count = 4000u;
    const u32 total = count + config.frame_size;
    for (u32 i = 0; i < count; ++i) {
        g_source[i] = (i16)lrint(0.05 * 32768.0 *
                                 sin(2.0 * kPi * 440.0 * i / 16000.0));
    }
    memset(g_source + count, 0, sizeof(i16) * config.frame_size);
    memcpy(g_work, g_source, sizeof(i16) * total);
    AudioNoiseSuppressor *suppressor = NULL;
    ASSERT_EQ(audio_noise_suppressor_create(&config, &suppressor), AUDIO_OK);
    audio_noise_suppressor_process_i16(suppressor, g_work, total);
    const double before = tone_amplitude(g_source, 0u, count, 16000u, 440.0);
    const double after = tone_amplitude(g_work, config.frame_size, count, 16000u, 440.0);
    ASSERT_TRUE(isfinite(before));
    ASSERT_TRUE(isfinite(after));
    const double change_db = 20.0 * log10(after / before);
    ASSERT_TRUE(change_db > -1.0);
    ASSERT_TRUE(change_db < 1.0);
    audio_noise_suppressor_destroy(suppressor);
}

TEST(a_sustained_tone_is_eventually_learned_as_noise)
{
    AudioNoiseSuppressorConfig config = test_config();
    config.noise_rise_db_per_s = 60.0f;
    config.initial_noise_dbfs = -50.0f;
    const u32 count = 32000u;
    const u32 total = count + config.frame_size;
    for (u32 i = 0; i < count; ++i) {
        g_source[i] = (i16)lrint(0.2 * 32768.0 *
                                 sin(2.0 * kPi * 440.0 * i / 16000.0));
    }
    memset(g_source + count, 0, sizeof(i16) * config.frame_size);
    memcpy(g_work, g_source, sizeof(i16) * total);
    AudioNoiseSuppressor *suppressor = NULL;
    ASSERT_EQ(audio_noise_suppressor_create(&config, &suppressor), AUDIO_OK);
    audio_noise_suppressor_process_i16(suppressor, g_work, total);
    const double before = tone_amplitude(g_source, 28000u, 4000u, 16000u, 440.0);
    const double after = tone_amplitude(g_work, 28000u + config.frame_size, 4000u,
                                        16000u, 440.0);
    ASSERT_TRUE(isfinite(before));
    ASSERT_TRUE(isfinite(after));
    const double change_db = 20.0 * log10(after / before);
    ASSERT_TRUE(change_db < -10.0);
    audio_noise_suppressor_destroy(suppressor);
}

TEST(chunking_does_not_change_the_output)
{
    const AudioNoiseSuppressorConfig config = test_config();
    const u32 count = 3000u;
    const u32 total = count + config.frame_size;
    for (u32 i = 0; i < count; ++i) {
        g_source[i] = (i16)lrint((0.1 * sin(2.0 * kPi * 700.0 * i / 16000.0) +
                                  0.02 * rnd()) * 32768.0);
    }
    memset(g_source + count, 0, sizeof(i16) * config.frame_size);
    memcpy(g_work, g_source, sizeof(i16) * total);
    memcpy(g_reference, g_source, sizeof(i16) * total);
    AudioNoiseSuppressor *whole = NULL, *chunked = NULL;
    ASSERT_EQ(audio_noise_suppressor_create(&config, &whole), AUDIO_OK);
    ASSERT_EQ(audio_noise_suppressor_create(&config, &chunked), AUDIO_OK);
    audio_noise_suppressor_process_i16(whole, g_work, total);
    const u32 chunks[] = {1u, 7u, 255u, 13u};
    u32 offset = 0u, index = 0u;
    while (offset < total) {
        u32 n = chunks[index % 4u];
        if (n > total - offset) n = total - offset;
        audio_noise_suppressor_process_i16(chunked, g_reference + offset, n);
        offset += n;
        ++index;
    }
    ASSERT_EQ(memcmp(g_work, g_reference, sizeof(i16) * total), 0);
    audio_noise_suppressor_destroy(whole);
    audio_noise_suppressor_destroy(chunked);
}

TEST(reset_matches_a_fresh_object_and_silence_stays_zero)
{
    AudioNoiseSuppressorConfig config = test_config();
    config.initial_noise_dbfs = -10.0f;
    const u32 training_count = 8000u;
    const u32 count = 4000u;
    const u32 total = count + config.frame_size;
    for (u32 i = 0; i < training_count; ++i) g_source[i] = (i16)lrint(rnd() * 30000.0);
    memcpy(g_work, g_source, sizeof(i16) * training_count);
    AudioNoiseSuppressor *reused = NULL, *fresh = NULL;
    ASSERT_EQ(audio_noise_suppressor_create(&config, &reused), AUDIO_OK);
    ASSERT_EQ(audio_noise_suppressor_create(&config, &fresh), AUDIO_OK);
    audio_noise_suppressor_process_i16(reused, g_work, training_count);
    audio_noise_suppressor_reset(reused);

    for (u32 i = 0; i < count; ++i) {
        g_source[i] = (i16)lrint(0.05 * 32768.0 *
                                 sin(2.0 * kPi * 440.0 * i / 16000.0));
    }
    memset(g_source + count, 0, sizeof(i16) * config.frame_size);
    memcpy(g_work, g_source, sizeof(i16) * total);
    memcpy(g_reference, g_source, sizeof(i16) * total);
    audio_noise_suppressor_process_i16(reused, g_work, total);
    audio_noise_suppressor_process_i16(fresh, g_reference, total);
    ASSERT_EQ(memcmp(g_work, g_reference, sizeof(i16) * total), 0);

    audio_noise_suppressor_reset(reused);
    memset(g_work, 0, sizeof(i16) * total);
    audio_noise_suppressor_process_i16(reused, g_work, total);
    for (u32 i = 0; i < total; ++i) ASSERT_EQ(g_work[i], 0);
    audio_noise_suppressor_destroy(reused);
    audio_noise_suppressor_destroy(fresh);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_the_configuration_and_reports_latency);
    RUN_TEST(zero_attenuation_is_the_input_delayed_by_one_frame_size);
    RUN_TEST(stationary_white_noise_is_attenuated_after_convergence);
    RUN_TEST(a_tone_in_noise_keeps_its_amplitude);
    RUN_TEST(a_quiet_tone_above_the_initial_floor_is_preserved);
    RUN_TEST(a_sustained_tone_is_eventually_learned_as_noise);
    RUN_TEST(chunking_does_not_change_the_output);
    RUN_TEST(reset_matches_a_fresh_object_and_silence_stays_zero);
TEST_MAIN_END()
