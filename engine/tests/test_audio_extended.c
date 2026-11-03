#include "test_framework.h"
#include <core/log.h>
#include <audio/audio_extended.h>

void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    (void)level; (void)file; (void)line; (void)fmt;
}

static AudioPcmDesc mono_pcm(const f32 *samples, u32 frames) {
    AudioPcmDesc desc;
    desc.samples = samples;
    desc.frame_count = frames;
    desc.channels = 1;
    desc.sample_rate = AUDIO_PCM_SAMPLE_RATE;
    return desc;
}

TEST(fake_backend_renders_silence_before_any_voice)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    f32 output[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    ASSERT_EQ(audio_system_render(as, output, 4), AUDIO_OK);
    for (u32 i = 0; i < 8; ++i) ASSERT_FLOAT_EQ(output[i], 0.0f, 0.0f);
    audio_system_destroy(as);
}

TEST(clip_registration_is_bounded_and_atomic)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.25f, 0.5f, -0.5f, 1.0f};
    AudioPcmDesc pcm = mono_pcm(samples, 4);
    AudioClipHandle clip = 0;
    ASSERT_EQ(audio_clip_register(as, "step", &pcm, &clip), AUDIO_OK);
    ASSERT_NEQ(clip, 0u);
    ASSERT_EQ(audio_clip_count(as), 1u);
    ASSERT_EQ(audio_clip_used_samples(as), (usize)4);

    AudioClipHandle rejected = 99;
    ASSERT_EQ(audio_clip_register(as, "step", &pcm, &rejected), AUDIO_REJECTED);
    ASSERT_EQ(rejected, 0u);
    ASSERT_EQ(audio_clip_count(as), 1u);
    ASSERT_EQ(audio_clip_used_samples(as), (usize)4);

    AudioPcmDesc invalid = mono_pcm(samples, 4);
    invalid.sample_rate = 44100;
    ASSERT_EQ(audio_clip_register(as, "wrong-rate", &invalid, &rejected), AUDIO_INVALID);
    invalid = mono_pcm(samples, AUDIO_PCM_MAX_SAMPLES + 1u);
    ASSERT_EQ(audio_clip_register(as, "too-large", &invalid, &rejected), AUDIO_OVERLOAD);
    ASSERT_EQ(audio_clip_count(as), 1u);
    ASSERT_EQ(audio_clip_used_samples(as), (usize)4);

    for (u32 i = 1; i < AUDIO_MAX_CLIPS; ++i) {
        char name[AUDIO_NAME_MAX];
        snprintf(name, sizeof(name), "clip-%u", i);
        ASSERT_EQ(audio_clip_register(as, name, &pcm, &clip), AUDIO_OK);
    }
    ASSERT_EQ(audio_clip_count(as), AUDIO_MAX_CLIPS);
    usize used = audio_clip_used_samples(as);
    ASSERT_EQ(audio_clip_register(as, "overflow", &pcm, &rejected), AUDIO_OVERLOAD);
    ASSERT_EQ(audio_clip_count(as), AUDIO_MAX_CLIPS);
    ASSERT_EQ(audio_clip_used_samples(as), used);
    audio_system_destroy(as);
}

TEST(null_backend_create_and_destroy)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_NULL);
    ASSERT_NOT_NULL(as);
    const f32 sample = 0.5f;
    AudioPcmDesc pcm = mono_pcm(&sample, 1);
    AudioClipHandle clip = 0;
    ASSERT_EQ(audio_clip_register(as, "null-clip", &pcm, &clip), AUDIO_OK);
    audio_system_destroy(as);
}

static AudioEventDesc make_event_desc(AudioClipHandle clip) {
    AudioEventDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.clip = clip;
    desc.max_instances = 1;
    desc.retrigger = AUDIO_RETRIGGER_ALLOW;
    desc.concurrency = AUDIO_CONCURRENCY_REJECT;
    desc.volume = 1.0f;
    desc.min_distance = 1.0f;
    desc.max_distance = 100.0f;
    desc.rolloff = 1.0f;
    desc.occluded_gain = 1.0f;
    desc.bus = AUDIO_BUS_MASTER;
    return desc;
}

static AudioClipHandle register_ramp(AudioSystem *as, const f32 *samples,
                                     u32 frames) {
    AudioPcmDesc pcm = mono_pcm(samples, frames);
    AudioClipHandle clip = 0;
    if (audio_clip_register(as, "event-pcm", &pcm, &clip) != AUDIO_OK) return 0;
    return clip;
}

TEST(event_allow_mixes_two_real_pcm_instances)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.25f, 0.5f, -0.5f, 1.0f};
    AudioClipHandle clip = register_ramp(as, samples, 4);
    AudioEventDesc desc = make_event_desc(clip);
    desc.max_instances = 2;
    ASSERT_EQ(audio_event_register(as, "allow", &desc), AUDIO_OK);
    AudioVoiceHandle a = 0, b = 0;
    ASSERT_EQ(audio_event_trigger(as, "allow", vec3(0, 0, 0), &a), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "allow", vec3(0, 0, 0), &b), AUDIO_OK);
    ASSERT_NEQ(a, b);
    f32 output[8];
    ASSERT_EQ(audio_system_render(as, output, 4), AUDIO_OK);
    for (u32 i = 0; i < 4; ++i) {
        ASSERT_FLOAT_EQ(output[2*i], samples[i] * 2.0f, 1e-6f);
        ASSERT_FLOAT_EQ(output[2*i+1], samples[i] * 2.0f, 1e-6f);
    }
    audio_system_destroy(as);
}

TEST(event_ignore_retrigger_does_not_add_voice)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.25f, 0.5f, -0.5f, 1.0f};
    AudioClipHandle clip = register_ramp(as, samples, 4);
    AudioEventDesc desc = make_event_desc(clip);
    desc.retrigger = AUDIO_RETRIGGER_IGNORE;
    ASSERT_EQ(audio_event_register(as, "ignore", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0, rejected = 77;
    ASSERT_EQ(audio_event_trigger(as, "ignore", vec3(0, 0, 0), &voice), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "ignore", vec3(0, 0, 0), &rejected), AUDIO_REJECTED);
    ASSERT_EQ(rejected, 0u);
    u32 count = 0;
    ASSERT_EQ(audio_event_active_count(as, "ignore", &count), AUDIO_OK);
    ASSERT_EQ(count, 1u);
    f32 output[8];
    ASSERT_EQ(audio_system_render(as, output, 4), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.25f, 1e-6f);
    audio_system_destroy(as);
}

TEST(event_restart_rewinds_the_same_voice)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    AudioClipHandle clip = register_ramp(as, samples, 6);
    AudioEventDesc desc = make_event_desc(clip);
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "restart", &desc), AUDIO_OK);
    AudioVoiceHandle first = 0, second = 0;
    ASSERT_EQ(audio_event_trigger(as, "restart", vec3(0, 0, 0), &first), AUDIO_OK);
    f32 output[12];
    ASSERT_EQ(audio_system_render(as, output, 4), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[6], 0.4f, 1e-6f);
    ASSERT_EQ(audio_event_trigger(as, "restart", vec3(0, 0, 0), &second), AUDIO_OK);
    ASSERT_EQ(second, first);
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.1f, 1e-6f);
    ASSERT_FLOAT_EQ(output[2], 0.2f, 1e-6f);
    audio_system_destroy(as);
}

TEST(event_capacity_reject_preserves_cursor_and_steal_invalidates_old_handle)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    AudioClipHandle clip = register_ramp(as, samples, 6);
    AudioEventDesc desc = make_event_desc(clip);
    ASSERT_EQ(audio_event_register(as, "capped", &desc), AUDIO_OK);
    AudioVoiceHandle first = 0, rejected = 9;
    ASSERT_EQ(audio_event_trigger(as, "capped", vec3(0, 0, 0), &first), AUDIO_OK);
    f32 output[12];
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    u32 cursor = 0;
    ASSERT_EQ(audio_voice_cursor(as, first, &cursor), AUDIO_OK);
    ASSERT_EQ(cursor, 2u);
    u32 count_before_reject = 0;
    ASSERT_EQ(audio_event_active_count(as, "capped", &count_before_reject), AUDIO_OK);
    ASSERT_EQ(count_before_reject, 1u);
    ASSERT_EQ(audio_event_trigger(as, "capped", vec3(0, 0, 0), &rejected), AUDIO_OVERLOAD);
    ASSERT_EQ(rejected, 0u);
    ASSERT_EQ(audio_voice_cursor(as, first, &cursor), AUDIO_OK);
    ASSERT_EQ(cursor, 2u);
    ASSERT_EQ(audio_voice_stop(as, first), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);

    AudioEventDesc steal = make_event_desc(clip);
    steal.concurrency = AUDIO_CONCURRENCY_STEAL_OLDEST;
    ASSERT_EQ(audio_event_register(as, "steal", &steal), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "steal", vec3(0, 0, 0), &first), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    AudioVoiceHandle replacement = 0;
    ASSERT_EQ(audio_event_trigger(as, "steal", vec3(0, 0, 0), &replacement), AUDIO_OK);
    ASSERT_NEQ(replacement, first);
    ASSERT_EQ(audio_voice_stop(as, first), AUDIO_STALE);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.1f, 1e-6f);
    audio_system_destroy(as);
}

TEST(event_global_voice_capacity_and_natural_completion)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.25f, 0.25f};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.max_instances = AUDIO_EVENT_MAX_VOICES;
    ASSERT_EQ(audio_event_register(as, "many", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0, first = 0;
    for (u32 i = 0; i < AUDIO_EVENT_MAX_VOICES; ++i) {
        ASSERT_EQ(audio_event_trigger(as, "many", vec3(0, 0, 0), &voice), AUDIO_OK);
        if (i == 0) first = voice;
    }
    ASSERT_EQ(audio_event_trigger(as, "many", vec3(0, 0, 0), &voice), AUDIO_OVERLOAD);
    u32 count = 0;
    ASSERT_EQ(audio_event_active_count(as, "many", &count), AUDIO_OK);
    ASSERT_EQ(count, AUDIO_EVENT_MAX_VOICES);
    f32 output[8];
    ASSERT_EQ(audio_system_render(as, output, 4), AUDIO_OK);
    ASSERT_EQ(audio_event_active_count(as, "many", &count), AUDIO_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(audio_voice_stop(as, first), AUDIO_STALE);
    audio_system_destroy(as);
}

TEST(event_registry_rejects_invalid_and_overflow_without_trigger)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 sample = 0.25f;
    AudioClipHandle clip = register_ramp(as, &sample, 1);
    AudioEventDesc desc = make_event_desc(clip);
    for (u32 i = 0; i < AUDIO_MAX_EVENTS; ++i) {
        char name[AUDIO_NAME_MAX];
        snprintf(name, sizeof(name), "event-%u", i);
        ASSERT_EQ(audio_event_register(as, name, &desc), AUDIO_OK);
    }
    ASSERT_EQ(audio_event_register(as, "overflow", &desc), AUDIO_OVERLOAD);
    AudioVoiceHandle voice = 1;
    ASSERT_EQ(audio_event_trigger(as, "overflow", vec3(0, 0, 0), &voice), AUDIO_INVALID);
    ASSERT_EQ(voice, 0u);
    audio_system_destroy(as);
}

TEST(event_dsp_delay_changes_real_engine_pcm)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1, 0, 0, 0};
    AudioClipHandle clip = register_ramp(as, samples, 4);
    AudioEventDesc desc = make_event_desc(clip);
    desc.dsp.stage_count = 1;
    desc.dsp.stages[0].type = AUDIO_DSP_DELAY;
    desc.dsp.stages[0].delay_frames = 2;
    desc.dsp.stages[0].feedback = 0.0f;
    desc.dsp.stages[0].mix = 1.0f;
    ASSERT_EQ(audio_event_register(as, "delayed", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "delayed", vec3(0, 0, 0), &voice), AUDIO_OK);
    f32 output[8];
    ASSERT_EQ(audio_system_render(as, output, 4), AUDIO_OK);
    const f32 expected[] = {0, 0, 1, 0};
    for (u32 i = 0; i < 4; ++i) ASSERT_FLOAT_EQ(output[2*i], expected[i], 1e-6f);
    audio_system_destroy(as);
}

TEST_MAIN_BEGIN()
    RUN_TEST(fake_backend_renders_silence_before_any_voice);
    RUN_TEST(clip_registration_is_bounded_and_atomic);
    RUN_TEST(null_backend_create_and_destroy);
    RUN_TEST(event_allow_mixes_two_real_pcm_instances);
    RUN_TEST(event_ignore_retrigger_does_not_add_voice);
    RUN_TEST(event_restart_rewinds_the_same_voice);
    RUN_TEST(event_capacity_reject_preserves_cursor_and_steal_invalidates_old_handle);
    RUN_TEST(event_global_voice_capacity_and_natural_completion);
    RUN_TEST(event_registry_rejects_invalid_and_overflow_without_trigger);
    RUN_TEST(event_dsp_delay_changes_real_engine_pcm);
TEST_MAIN_END()
