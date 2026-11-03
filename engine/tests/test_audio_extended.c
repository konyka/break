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

TEST_MAIN_BEGIN()
    RUN_TEST(fake_backend_renders_silence_before_any_voice);
    RUN_TEST(clip_registration_is_bounded_and_atomic);
    RUN_TEST(null_backend_create_and_destroy);
TEST_MAIN_END()
