#include "test_framework.h"
#include <audio/audio_dsp.h>
#include <math.h>
#include <string.h>

static AudioDspStageDesc filter_stage(f32 cutoff) {
    AudioDspStageDesc stage;
    memset(&stage, 0, sizeof(stage));
    stage.type = AUDIO_DSP_FILTER;
    stage.cutoff_hz = cutoff;
    return stage;
}

static AudioDspStageDesc delay_stage(u32 frames, f32 feedback, f32 mix) {
    AudioDspStageDesc stage;
    memset(&stage, 0, sizeof(stage));
    stage.type = AUDIO_DSP_DELAY;
    stage.delay_frames = frames;
    stage.feedback = feedback;
    stage.mix = mix;
    return stage;
}

TEST(filter_step_response_matches_one_pole_reference)
{
    AudioDspChainDesc desc = {0};
    desc.stage_count = 1;
    desc.stages[0] = filter_stage(1000.0f);
    AudioDspChain chain;
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, NULL, 0, 48000), AUDIO_OK);
    f32 pcm[] = {1.0f, 1.0f};
    audio_dsp_chain_process(&chain, pcm, 2, 1);
    f32 alpha = 1.0f - expf(-2.0f * 3.14159265358979323846f * 1000.0f / 48000.0f);
    ASSERT_FLOAT_EQ(pcm[0], alpha, 1e-6f);
    ASSERT_FLOAT_EQ(pcm[1], alpha + alpha * (1.0f - alpha), 1e-6f);
}

TEST(delay_impulse_has_exact_tap_and_feedback)
{
    AudioDspChainDesc desc = {0};
    desc.stage_count = 1;
    desc.stages[0] = delay_stage(2, 0.5f, 1.0f);
    f32 storage[AUDIO_DSP_MAX_DELAY_FRAMES * 2];
    AudioDspChain chain;
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
        AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_OK);
    f32 pcm[] = {1, 0, 0, 0, 0, 0};
    const f32 expected[] = {0, 0, 1, 0, 0.5f, 0};
    audio_dsp_chain_process(&chain, pcm, 6, 1);
    for (u32 i = 0; i < 6; ++i) ASSERT_FLOAT_EQ(pcm[i], expected[i], 1e-6f);
}

TEST(reverb_impulse_has_bounded_early_taps)
{
    AudioDspChainDesc desc = {0};
    desc.stage_count = 1;
    desc.stages[0].type = AUDIO_DSP_REVERB;
    desc.stages[0].mix = 1.0f;
    desc.stages[0].room = 0.0f;
    f32 storage[AUDIO_DSP_MAX_DELAY_FRAMES * 2];
    AudioDspChain chain;
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
        AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_OK);
    f32 pcm[1000] = {0};
    pcm[0] = 1.0f;
    audio_dsp_chain_process(&chain, pcm, 1000, 1);
    const u32 taps[] = {149, 311, 587, 997};
    u32 tap = 0;
    for (u32 i = 0; i < 1000; ++i) {
        if (tap < 4 && i == taps[tap]) {
            ASSERT_FLOAT_EQ(pcm[i], 0.25f, 1e-6f);
            tap++;
        } else {
            ASSERT_FLOAT_EQ(pcm[i], 0.0f, 1e-6f);
        }
    }
    ASSERT_EQ(tap, 4u);
}

TEST(filter_then_delay_applies_both_stages)
{
    AudioDspChainDesc desc = {0};
    desc.stage_count = 2;
    desc.stages[0] = filter_stage(1000.0f);
    desc.stages[1] = delay_stage(2, 0.0f, 1.0f);
    f32 storage[AUDIO_DSP_MAX_DELAY_FRAMES * 2];
    AudioDspChain chain;
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
        AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_OK);
    f32 pcm[] = {1, 0, 0, 0};
    audio_dsp_chain_process(&chain, pcm, 4, 1);
    f32 alpha = 1.0f - expf(-2.0f * 3.14159265358979323846f * 1000.0f / 48000.0f);
    ASSERT_FLOAT_EQ(pcm[0], 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(pcm[1], 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(pcm[2], alpha, 1e-6f);
    ASSERT_FLOAT_EQ(pcm[3], alpha * (1.0f - alpha), 1e-6f);
}

TEST(dsp_invalid_input_preserves_existing_chain)
{
    AudioDspChain chain;
    memset(&chain, 0, sizeof(chain));
    AudioDspChainDesc desc = {0};
    desc.stage_count = AUDIO_DSP_MAX_STAGES + 1u;
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, NULL, 0, 48000), AUDIO_OVERLOAD);
    ASSERT_EQ(chain.stage_count, 0u);
    desc.stage_count = 1;
    desc.stages[0] = delay_stage(AUDIO_DSP_MAX_DELAY_FRAMES + 1u, 0, 1);
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, NULL, 0, 48000), AUDIO_INVALID);
    desc.stages[0] = delay_stage(2, 0, 1);
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, NULL, 0, 48000), AUDIO_OVERLOAD);
    ASSERT_EQ(chain.stage_count, 0u);
}

TEST(dsp_rejects_nonfinite_parameters)
{
    AudioDspChain chain;
    memset(&chain, 0, sizeof(chain));
    AudioDspChainDesc desc = {0};
    desc.stage_count = 1;
    const f32 invalid[] = {NAN, INFINITY, -INFINITY};
    for (u32 i = 0; i < 3; ++i) {
        desc.stages[0] = filter_stage(invalid[i]);
        ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, NULL, 0, 48000), AUDIO_INVALID);
        desc.stages[0] = delay_stage(2, invalid[i], 1.0f);
        f32 storage[AUDIO_DSP_MAX_DELAY_FRAMES * 2];
        ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
            AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_INVALID);
        desc.stages[0] = delay_stage(2, 0.5f, invalid[i]);
        ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
            AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_INVALID);
        desc.stages[0].type = AUDIO_DSP_REVERB;
        desc.stages[0].room = invalid[i];
        desc.stages[0].mix = 1.0f;
        ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
            AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_INVALID);
        desc.stages[0].room = 0.5f;
        desc.stages[0].mix = invalid[i];
        ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
            AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_INVALID);
    }
    ASSERT_EQ(chain.stage_count, 0u);
}

TEST(dsp_stereo_filter_state_is_independent)
{
    AudioDspChainDesc desc = {0};
    desc.stage_count = 1;
    desc.stages[0] = filter_stage(1000.0f);
    AudioDspChain chain;
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, NULL, 0, 48000), AUDIO_OK);
    f32 pcm[] = {1, 0, 1, 0};
    audio_dsp_chain_process(&chain, pcm, 2, 2);
    f32 alpha = 1.0f - expf(-2.0f * 3.14159265358979323846f * 1000.0f / 48000.0f);
    ASSERT_FLOAT_EQ(pcm[0], alpha, 1e-6f);
    ASSERT_FLOAT_EQ(pcm[1], 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(pcm[2], alpha + alpha * (1.0f - alpha), 1e-6f);
    ASSERT_FLOAT_EQ(pcm[3], 0.0f, 0.0f);
}

TEST(dsp_filter_delay_order_has_reference_pcm)
{
    AudioDspChainDesc first = {0};
    first.stage_count = 2;
    first.stages[0] = filter_stage(1000.0f);
    first.stages[1] = delay_stage(2, 0.0f, 1.0f);
    AudioDspChainDesc second = first;
    second.stages[0] = first.stages[1];
    second.stages[1] = first.stages[0];
    f32 storage_a[AUDIO_DSP_MAX_DELAY_FRAMES * 2];
    f32 storage_b[AUDIO_DSP_MAX_DELAY_FRAMES * 2];
    AudioDspChain chain_a, chain_b;
    ASSERT_EQ(audio_dsp_chain_init(&chain_a, &first, storage_a,
        AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_OK);
    ASSERT_EQ(audio_dsp_chain_init(&chain_b, &second, storage_b,
        AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_OK);
    f32 pcm_a[] = {1, 0, 0, 0};
    f32 pcm_b[] = {1, 0, 0, 0};
    audio_dsp_chain_process(&chain_a, pcm_a, 4, 1);
    audio_dsp_chain_process(&chain_b, pcm_b, 4, 1);
    f32 alpha = 1.0f - expf(-2.0f * 3.14159265358979323846f * 1000.0f / 48000.0f);
    const f32 expected[] = {0, 0, alpha, alpha * (1.0f - alpha)};
    for (u32 i = 0; i < 4; ++i) {
        ASSERT_FLOAT_EQ(pcm_a[i], expected[i], 1e-6f);
        ASSERT_FLOAT_EQ(pcm_b[i], expected[i], 1e-6f);
    }
}

TEST(dsp_delay_stereo_state_is_independent)
{
    AudioDspChainDesc desc = {0};
    desc.stage_count = 1;
    desc.stages[0] = delay_stage(2, 0.5f, 1.0f);
    f32 storage[AUDIO_DSP_MAX_DELAY_FRAMES * 2];
    AudioDspChain chain;
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
        AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_OK);
    f32 pcm[] = {1, 0.5f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const f32 expected[] = {0, 0, 0, 0, 1, 0.5f, 0, 0, 0.5f, 0.25f, 0, 0};
    audio_dsp_chain_process(&chain, pcm, 6, 2);
    for (u32 i = 0; i < 12; ++i) ASSERT_FLOAT_EQ(pcm[i], expected[i], 1e-6f);
}

TEST(dsp_reverb_stereo_state_is_independent)
{
    AudioDspChainDesc desc = {0};
    desc.stage_count = 1;
    desc.stages[0].type = AUDIO_DSP_REVERB;
    desc.stages[0].mix = 1.0f;
    desc.stages[0].room = 0.0f;
    f32 storage[AUDIO_DSP_MAX_DELAY_FRAMES * 2];
    AudioDspChain chain;
    ASSERT_EQ(audio_dsp_chain_init(&chain, &desc, storage,
        AUDIO_DSP_MAX_DELAY_FRAMES * 2, 48000), AUDIO_OK);
    f32 pcm[2000] = {0};
    pcm[0] = 1.0f;
    pcm[1] = 0.5f;
    audio_dsp_chain_process(&chain, pcm, 1000, 2);
    const u32 taps[] = {149, 311, 587, 997};
    u32 tap = 0;
    for (u32 frame = 0; frame < 1000; ++frame) {
        if (tap < 4 && frame == taps[tap]) {
            ASSERT_FLOAT_EQ(pcm[frame*2], 0.25f, 1e-6f);
            ASSERT_FLOAT_EQ(pcm[frame*2+1], 0.125f, 1e-6f);
            tap++;
        } else {
            ASSERT_FLOAT_EQ(pcm[frame*2], 0.0f, 1e-6f);
            ASSERT_FLOAT_EQ(pcm[frame*2+1], 0.0f, 1e-6f);
        }
    }
    ASSERT_EQ(tap, 4u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(filter_step_response_matches_one_pole_reference);
    RUN_TEST(delay_impulse_has_exact_tap_and_feedback);
    RUN_TEST(reverb_impulse_has_bounded_early_taps);
    RUN_TEST(filter_then_delay_applies_both_stages);
    RUN_TEST(dsp_invalid_input_preserves_existing_chain);
    RUN_TEST(dsp_rejects_nonfinite_parameters);
    RUN_TEST(dsp_stereo_filter_state_is_independent);
    RUN_TEST(dsp_filter_delay_order_has_reference_pcm);
    RUN_TEST(dsp_delay_stereo_state_is_independent);
    RUN_TEST(dsp_reverb_stereo_state_is_independent);
TEST_MAIN_END()
