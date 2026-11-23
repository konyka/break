/* audio_voice_processor: nested validation, manual-chain equivalence,
 * arbitrary chunks, reset, spectral-latency drain and stage bypass. */
#include "test_framework.h"

#include <audio/audio_voice_processor.h>

#include <math.h>
#include <string.h>

#define N 4096u

static const double kPi = 3.14159265358979323846;
static i16 g_ref[N], g_expected[N], g_whole[N], g_chunked[N];

static AudioVoiceProcessorConfig test_config(void) {
    AudioVoiceProcessorConfig config = {
        .echo = {16000u, 64u, 0.2f, 0.5f, 2.0f},
        .residual = {16000u, 30.0f, 6.0f, 5.0f, 20.0f, 60.0f, -60.0f, -40.0f, 20.0f},
        .noise = {16000u, 64u, 30.0f, 10.0f, -60.0f},
        .gate = {16000u, 1u, 6.0f, 30.0f, 5.0f, 20.0f, 10.0f, -80.0f},
        .agc = {16000u, 1u, -18.0f, 12.0f, 10.0f, 100.0f, -60.0f},
    };
    return config;
}

static AudioVoiceProcessor *make_processor(const AudioVoiceProcessorConfig *config) {
    AudioVoiceProcessor *processor = NULL;
    if (audio_voice_processor_create(config, &processor) != AUDIO_OK) return NULL;
    return processor;
}

static void fill_stream(u32 count) {
    for (u32 i = 0; i < count; ++i) {
        const double x = 0.4 * sin(2.0 * kPi * 800.0 * i / 16000.0);
        const double noise = 0.015 * sin(2.0 * kPi * 2500.0 * i / 16000.0);
        const double near = i >= count / 2u
            ? 0.12 * sin(2.0 * kPi * 440.0 * i / 16000.0) : 0.0;
        g_ref[i] = (i16)lrint(x * 32768.0);
        g_expected[i] = (i16)lrint((0.25 * x + 0.12 * x * fabs(x) + noise + near) * 32768.0);
    }
}

static void manual_chain_process_skipping(const AudioVoiceProcessorConfig *config,
                                          i16 *samples, u32 frames, u32 skip) {
    AudioEchoCanceller *aec = NULL;
    AudioNoiseSuppressor *noise = NULL;
    AudioResidualEchoSuppressor residual;
    AudioNoiseGate gate;
    AudioAgc agc;
    ASSERT_EQ(audio_echo_canceller_create(&config->echo, &aec), AUDIO_OK);
    ASSERT_EQ(audio_residual_echo_suppressor_init(&residual, &config->residual), AUDIO_OK);
    ASSERT_EQ(audio_noise_suppressor_create(&config->noise, &noise), AUDIO_OK);
    ASSERT_EQ(audio_noise_gate_init(&gate, &config->gate), AUDIO_OK);
    ASSERT_EQ(audio_agc_init(&agc, &config->agc), AUDIO_OK);
    if (!(skip & AUDIO_VOICE_PROCESSOR_STAGE_ECHO)) {
        audio_residual_echo_suppressor_process_with_aec(&residual, aec, g_ref, samples, frames);
    }
    if (!(skip & AUDIO_VOICE_PROCESSOR_STAGE_NOISE)) audio_noise_suppressor_process_i16(noise, samples, frames);
    if (!(skip & AUDIO_VOICE_PROCESSOR_STAGE_GATE)) audio_noise_gate_process_i16(&gate, samples, frames);
    if (!(skip & AUDIO_VOICE_PROCESSOR_STAGE_AGC)) audio_agc_process_i16(&agc, samples, frames);
    audio_noise_suppressor_destroy(noise);
    audio_echo_canceller_destroy(aec);
}

static void manual_chain_process(const AudioVoiceProcessorConfig *config, i16 *samples,
                                 u32 frames) {
    manual_chain_process_skipping(config, samples, frames, 0u);
}

TEST(validation_noop_and_latency)
{
    const AudioVoiceProcessorConfig config = test_config();
    AudioVoiceProcessor *sentinel = make_processor(&config);
    ASSERT_TRUE(sentinel != NULL);
    ASSERT_EQ(audio_voice_processor_latency_frames(sentinel), 64u);
    ASSERT_EQ(audio_voice_processor_latency_frames(NULL), 0u);
    AudioVoiceProcessor *processor = sentinel;
    ASSERT_EQ(audio_voice_processor_create(NULL, &processor), AUDIO_INVALID);
    ASSERT_EQ(audio_voice_processor_create(&config, NULL), AUDIO_INVALID);
    AudioVoiceProcessorConfig bad = config;
    bad.noise.sample_rate = 8000u;
    ASSERT_EQ(audio_voice_processor_create(&bad, &processor), AUDIO_INVALID);
    bad = config; bad.gate.channels = 2u;
    ASSERT_EQ(audio_voice_processor_create(&bad, &processor), AUDIO_INVALID);
    bad = config; bad.agc.channels = 2u;
    ASSERT_EQ(audio_voice_processor_create(&bad, &processor), AUDIO_INVALID);
    bad = config; bad.noise.frame_size = 63u;
    ASSERT_EQ(audio_voice_processor_create(&bad, &processor), AUDIO_INVALID);
    ASSERT_TRUE(processor == sentinel);
    audio_voice_processor_process_i16(sentinel, NULL, NULL, 0u);
    audio_voice_processor_process_i16(sentinel, NULL, NULL, 1u);
    audio_voice_processor_process_i16(NULL, NULL, NULL, 1u);
    i16 reference = 0, output = 0;
    audio_voice_processor_process_i16(NULL, &reference, &output, 1u);
    audio_voice_processor_reset(NULL);
    audio_voice_processor_destroy(NULL);
    audio_voice_processor_destroy(sentinel);
}

TEST(manual_chain_and_arbitrary_chunks_match)
{
    const AudioVoiceProcessorConfig config = test_config();
    fill_stream(N);
    memcpy(g_whole, g_expected, sizeof(g_expected));
    memcpy(g_chunked, g_expected, sizeof(g_chunked));
    AudioVoiceProcessor *whole = make_processor(&config);
    AudioVoiceProcessor *chunked = make_processor(&config);
    ASSERT_TRUE(whole != NULL && chunked != NULL);
    manual_chain_process(&config, g_expected, N);

    audio_voice_processor_process_i16(whole, g_ref, g_whole, N);
    ASSERT_EQ(memcmp(g_whole, g_expected, sizeof(g_expected)), 0);
    const u32 chunks[] = {1u, 7u, 64u, 255u};
    u32 at = 0u, index = 0u;
    while (at < N) {
        const u32 n = N - at < chunks[index % 4u] ? N - at : chunks[index % 4u];
        audio_voice_processor_process_i16(chunked, g_ref + at, g_chunked + at, n);
        at += n;
        ++index;
    }
    ASSERT_EQ(memcmp(g_chunked, g_expected, sizeof(g_expected)), 0);
    audio_voice_processor_destroy(whole);
    audio_voice_processor_destroy(chunked);
}

TEST(reset_matches_fresh_and_zero_padding_drains)
{
    const AudioVoiceProcessorConfig config = test_config();
    const u32 count = 2048u;
    fill_stream(count);
    memcpy(g_whole, g_expected, sizeof(i16) * count);
    memcpy(g_chunked, g_expected, sizeof(i16) * count);
    AudioVoiceProcessor *used = make_processor(&config);
    AudioVoiceProcessor *fresh = make_processor(&config);
    ASSERT_TRUE(used != NULL && fresh != NULL);
    audio_voice_processor_process_i16(used, g_ref, g_whole, count);
    audio_voice_processor_reset(used);
    memcpy(g_whole, g_expected, sizeof(i16) * count);
    audio_voice_processor_process_i16(used, g_ref, g_whole, count);
    audio_voice_processor_process_i16(fresh, g_ref, g_chunked, count);
    ASSERT_EQ(memcmp(g_whole, g_chunked, sizeof(i16) * count), 0);

    static i16 zero[64];
    memset(zero, 0, sizeof(zero));
    memset(g_ref + count, 0, sizeof(i16) * 64u);
    memset(g_expected + count, 0, sizeof(i16) * 64u);
    memset(g_whole + count, 0, sizeof(i16) * 64u);
    memset(g_chunked + count, 0, sizeof(i16) * 64u);
    audio_voice_processor_process_i16(used, zero, g_whole + count, 64u);
    audio_voice_processor_process_i16(fresh, zero, g_chunked + count, 64u);
    manual_chain_process(&config, g_expected, count + 64u);
    ASSERT_EQ(memcmp(g_whole, g_expected, sizeof(i16) * (count + 64u)), 0);
    ASSERT_EQ(memcmp(g_chunked, g_expected, sizeof(i16) * (count + 64u)), 0);
    ASSERT_EQ(audio_voice_processor_latency_frames(used), 64u);
    audio_voice_processor_destroy(used);
    audio_voice_processor_destroy(fresh);
}

static bool bypass_matches_manual_chain(u32 skip)
{
    AudioVoiceProcessorConfig config = test_config();
    config.bypass_stages = skip;
    fill_stream(N);
    static i16 full[N];
    memcpy(full, g_expected, sizeof(full));
    memcpy(g_whole, g_expected, sizeof(g_whole));
    memcpy(g_chunked, g_expected, sizeof(g_chunked));
    manual_chain_process(&config, full, N);
    manual_chain_process_skipping(&config, g_chunked, N, skip);
    AudioVoiceProcessor *processor = make_processor(&config);
    if (!processor) return false;
    for (u32 at = 0u; at < N; at += 97u) {
        const u32 n = N - at < 97u ? N - at : 97u;
        audio_voice_processor_process_i16(processor, g_ref + at, g_whole + at, n);
    }
    const bool ok = memcmp(g_whole, g_chunked, sizeof(g_whole)) == 0 &&
                    memcmp(g_whole, full, sizeof(g_whole)) != 0;
    audio_voice_processor_destroy(processor);
    return ok;
}

TEST(each_bypassed_stage_matches_a_chain_without_it)
{
    ASSERT_TRUE(bypass_matches_manual_chain(AUDIO_VOICE_PROCESSOR_STAGE_ECHO));
    ASSERT_TRUE(bypass_matches_manual_chain(AUDIO_VOICE_PROCESSOR_STAGE_NOISE));
    ASSERT_TRUE(bypass_matches_manual_chain(AUDIO_VOICE_PROCESSOR_STAGE_GATE));
    ASSERT_TRUE(bypass_matches_manual_chain(AUDIO_VOICE_PROCESSOR_STAGE_AGC));
    ASSERT_TRUE(bypass_matches_manual_chain(AUDIO_VOICE_PROCESSOR_STAGE_ECHO | AUDIO_VOICE_PROCESSOR_STAGE_AGC));
}

TEST(bypass_validation_latency_identity_and_reset)
{
    AudioVoiceProcessorConfig config = test_config();
    AudioVoiceProcessor *sentinel = make_processor(&config);
    ASSERT_TRUE(sentinel != NULL);
    AudioVoiceProcessor *processor = sentinel;
    config.bypass_stages = AUDIO_VOICE_PROCESSOR_STAGE_ALL + 1u;
    ASSERT_EQ(audio_voice_processor_create(&config, &processor), AUDIO_INVALID);
    config.bypass_stages = 0x80000000u;
    ASSERT_EQ(audio_voice_processor_create(&config, &processor), AUDIO_INVALID);
    ASSERT_TRUE(processor == sentinel);
    audio_voice_processor_destroy(sentinel);

    config.bypass_stages = AUDIO_VOICE_PROCESSOR_STAGE_ALL;
    processor = make_processor(&config);
    ASSERT_TRUE(processor != NULL);
    ASSERT_EQ(audio_voice_processor_latency_frames(processor), 0u);
    fill_stream(N);
    memcpy(g_whole, g_expected, sizeof(g_whole));
    audio_voice_processor_process_i16(processor, g_ref, g_whole, N);
    ASSERT_EQ(memcmp(g_whole, g_expected, sizeof(g_whole)), 0);
    audio_voice_processor_destroy(processor);

    config.bypass_stages = AUDIO_VOICE_PROCESSOR_STAGE_ECHO;
    processor = make_processor(&config);
    ASSERT_TRUE(processor != NULL);
    ASSERT_EQ(audio_voice_processor_latency_frames(processor), 64u);
    audio_voice_processor_destroy(processor);

    config.bypass_stages = AUDIO_VOICE_PROCESSOR_STAGE_GATE | AUDIO_VOICE_PROCESSOR_STAGE_NOISE;
    AudioVoiceProcessor *used = make_processor(&config);
    AudioVoiceProcessor *fresh = make_processor(&config);
    ASSERT_TRUE(used != NULL && fresh != NULL);
    ASSERT_EQ(audio_voice_processor_latency_frames(used), 0u);
    const u32 count = 2048u;
    fill_stream(count);
    memcpy(g_whole, g_expected, sizeof(i16) * count);
    audio_voice_processor_process_i16(used, g_ref, g_whole, count);
    audio_voice_processor_reset(used);
    memcpy(g_whole, g_expected, sizeof(i16) * count);
    memcpy(g_chunked, g_expected, sizeof(i16) * count);
    audio_voice_processor_process_i16(used, g_ref, g_whole, count);
    audio_voice_processor_process_i16(fresh, g_ref, g_chunked, count);
    ASSERT_EQ(memcmp(g_whole, g_chunked, sizeof(i16) * count), 0);
    audio_voice_processor_destroy(used);
    audio_voice_processor_destroy(fresh);
}

TEST_MAIN_BEGIN()
    RUN_TEST(validation_noop_and_latency);
    RUN_TEST(manual_chain_and_arbitrary_chunks_match);
    RUN_TEST(reset_matches_fresh_and_zero_padding_drains);
    RUN_TEST(each_bypassed_stage_matches_a_chain_without_it);
    RUN_TEST(bypass_validation_latency_identity_and_reset);
TEST_MAIN_END()
