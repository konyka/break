#include "test_framework.h"
#include <core/log.h>
#include <audio/audio_extended.h>
#include <float.h>
static void test_spatial_interleave(void *voice);
static void test_voice_read_interleave(void *voice);
static void test_listener_start_interleave(void *voice);
#include "../src/audio/audio.c"
#include "../src/audio/audio_extended.c"

static bool test_interleave_armed;
static f32 test_interleave_gain;
static void test_spatial_interleave(void *opaque) {
    if (!test_interleave_armed) return;
    test_interleave_armed = false;
    AudioVoice *voice = (AudioVoice *)opaque;
    (void)spatial_publish(voice, voice->epoch, test_interleave_gain);
}

static bool test_read_interleave_armed;
static AudioSystem *test_read_interleave_system;
static AudioVoice *test_read_interleave_voice;
static AudioVoiceHandle test_read_interleave_handle;
static AudioResult test_read_interleave_trigger_result;
static AudioResult test_read_interleave_position_result;
static void test_voice_read_interleave(void *opaque) {
    if (!test_read_interleave_armed || opaque != test_read_interleave_voice) return;
    test_read_interleave_armed = false;
    test_read_interleave_trigger_result = audio_event_trigger(
        test_read_interleave_system, "read-interleave", vec3(4, 0, 0),
        &test_read_interleave_handle);
    test_read_interleave_position_result = audio_voice_set_position(
        test_read_interleave_system, test_read_interleave_handle, vec3(8, 0, 0));
}

static bool test_listener_interleave_armed;
static bool test_listener_interleave_applied;
static AudioVoice *test_listener_interleave_voice;
static void test_listener_start_interleave(void *opaque) {
    if (!test_listener_interleave_armed || opaque != test_listener_interleave_voice) {
        return;
    }
    test_listener_interleave_armed = false;
    AudioVoice *voice = (AudioVoice *)opaque;
    u32 tail = atomic_load_explicit(&voice->tail, memory_order_relaxed);
    u32 head = atomic_load_explicit(&voice->head, memory_order_acquire);
    for (u32 cursor = tail; cursor != head; ++cursor) {
        const AudioCommand *command =
            &voice->commands[cursor & (AUDIO_COMMAND_CAPACITY - 1u)];
        if (command->type != AUDIO_COMMAND_START || command->epoch != voice->epoch) {
            continue;
        }
        u64 before = atomic_load_explicit(&voice->spatial_snapshot, memory_order_acquire);
        voice_apply_initial_spatial(voice, command);
        u64 after = atomic_load_explicit(&voice->spatial_snapshot, memory_order_acquire);
        test_listener_interleave_applied = before != after &&
            spatial_revision_of(after) == command->spatial_revision &&
            gain_to_bits(spatial_gain_of(after)) == gain_to_bits(command->spatial_gain);
        return;
    }
}

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

static AudioClipHandle register_named_pcm(AudioSystem *as, const char *name,
                                          const f32 *samples, u32 frames) {
    AudioPcmDesc pcm = mono_pcm(samples, frames);
    AudioClipHandle clip = 0;
    if (audio_clip_register(as, name, &pcm, &clip) != AUDIO_OK) return 0;
    return clip;
}

TEST(music_crossfade_mixes_exact_pcm)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 a[8] = {0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f};
    const f32 b[8] = {0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f};
    AudioClipHandle tracks[] = {
        register_named_pcm(as, "music-a", a, 8),
        register_named_pcm(as, "music-b", b, 8)
    };
    AudioMusicPlaylistDesc playlist;
    memset(&playlist, 0, sizeof(playlist));
    playlist.tracks = tracks;
    playlist.track_count = 2;
    playlist.crossfade_frames = 4;
    playlist.volume = 1.0f;
    ASSERT_EQ(audio_music_set_playlist(as, &playlist), AUDIO_OK);
    ASSERT_EQ(audio_music_play(as), AUDIO_OK);
    const f32 expected[] = {0.25f, 0.25f, 0.25f, 0.25f,
                            0.375f, 0.5f, 0.625f, 0.75f};
    for (u32 i = 0; i < 8; ++i) {
        ASSERT_EQ(audio_music_update(as), AUDIO_OK);
        f32 output[2];
        ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
        ASSERT_FLOAT_EQ(output[0], expected[i], 1e-6f);
        ASSERT_FLOAT_EQ(output[1], expected[i], 1e-6f);
        ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    }
    AudioMusicState state;
    u32 index = 99;
    ASSERT_EQ(audio_music_state(as, &state, &index), AUDIO_OK);
    ASSERT_EQ(state, AUDIO_MUSIC_PLAYING);
    ASSERT_EQ(index, 1u);
    audio_system_destroy(as);
}

TEST(music_loop_crossfade_wraps_to_first_track)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 a[] = {0.25f, 0.25f, 0.25f, 0.25f};
    const f32 b[] = {0.75f, 0.75f, 0.75f, 0.75f};
    AudioClipHandle tracks[] = {
        register_named_pcm(as, "loop-a", a, 4),
        register_named_pcm(as, "loop-b", b, 4)
    };
    AudioMusicPlaylistDesc playlist;
    memset(&playlist, 0, sizeof(playlist));
    playlist.tracks = tracks;
    playlist.track_count = 2;
    playlist.loop = true;
    playlist.crossfade_frames = 2;
    playlist.volume = 1.0f;
    ASSERT_EQ(audio_music_set_playlist(as, &playlist), AUDIO_OK);
    ASSERT_EQ(audio_music_play(as), AUDIO_OK);
    const f32 expected[] = {0.25f, 0.25f, 0.5f, 0.75f, 0.5f, 0.25f};
    for (u32 i = 0; i < 6; ++i) {
        ASSERT_EQ(audio_music_update(as), AUDIO_OK);
        f32 output[2];
        ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
        ASSERT_FLOAT_EQ(output[0], expected[i], 1e-6f);
        ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    }
    AudioMusicState state;
    u32 index = 99;
    ASSERT_EQ(audio_music_state(as, &state, &index), AUDIO_OK);
    ASSERT_EQ(state, AUDIO_MUSIC_PLAYING);
    ASSERT_EQ(index, 0u);
    audio_system_destroy(as);
}

TEST(music_playlist_validation_is_atomic_and_running_replacement_rejected)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 a[] = {0.25f, 0.25f, 0.25f, 0.25f};
    const f32 b[] = {0.75f, 0.75f, 0.75f, 0.75f};
    AudioClipHandle tracks[] = {
        register_named_pcm(as, "atomic-a", a, 4),
        register_named_pcm(as, "atomic-b", b, 4)
    };
    AudioMusicPlaylistDesc playlist;
    memset(&playlist, 0, sizeof(playlist));
    playlist.tracks = tracks;
    playlist.track_count = 2;
    playlist.crossfade_frames = 1;
    playlist.volume = 1.0f;
    ASSERT_EQ(audio_music_set_playlist(as, &playlist), AUDIO_OK);
    AudioMusicPlaylistDesc invalid = playlist;
    invalid.crossfade_frames = 5;
    ASSERT_EQ(audio_music_set_playlist(as, &invalid), AUDIO_INVALID);
    AudioClipHandle stale[] = {999};
    invalid = playlist;
    invalid.tracks = stale;
    invalid.track_count = 1;
    ASSERT_EQ(audio_music_set_playlist(as, &invalid), AUDIO_STALE);
    ASSERT_EQ(audio_music_play(as), AUDIO_OK);
    ASSERT_EQ(audio_music_set_playlist(as, &playlist), AUDIO_REJECTED);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.25f, 1e-6f);
    audio_system_destroy(as);
}

TEST(music_zero_fade_advances_and_stops)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 a[] = {0.25f, 0.25f};
    const f32 b[] = {0.75f, 0.75f};
    AudioClipHandle tracks[] = {
        register_named_pcm(as, "zero-a", a, 2),
        register_named_pcm(as, "zero-b", b, 2)
    };
    AudioMusicPlaylistDesc playlist;
    memset(&playlist, 0, sizeof(playlist));
    playlist.tracks = tracks;
    playlist.track_count = 2;
    playlist.volume = 1.0f;
    ASSERT_EQ(audio_music_set_playlist(as, &playlist), AUDIO_OK);
    ASSERT_EQ(audio_music_play(as), AUDIO_OK);
    f32 output[4];
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    AudioMusicState state;
    u32 index = 99;
    ASSERT_EQ(audio_music_state(as, &state, &index), AUDIO_OK);
    ASSERT_EQ(state, AUDIO_MUSIC_PLAYING);
    ASSERT_EQ(index, 1u);
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.75f, 1e-6f);
    ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    ASSERT_EQ(audio_music_state(as, &state, &index), AUDIO_OK);
    ASSERT_EQ(state, AUDIO_MUSIC_STOPPED);
    audio_system_destroy(as);
}

typedef struct {
    bool blocked;
    u32 calls;
    Vec3 listener;
    Vec3 source;
} FakeRay;

static bool fake_occlusion_ray(void *user, Vec3 listener, Vec3 source) {
    FakeRay *ray = (FakeRay *)user;
    ray->calls++;
    ray->listener = listener;
    ray->source = source;
    return ray->blocked;
}

TEST(spatial_event_combines_distance_and_ray_occlusion)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1, 1, 1, 1};
    AudioClipHandle clip = register_ramp(as, samples, 4);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.occluded_gain = 0.25f;
    ASSERT_EQ(audio_event_register(as, "spatial", &desc), AUDIO_OK);
    FakeRay ray;
    memset(&ray, 0, sizeof(ray));
    audio_set_occlusion_ray_callback(as, fake_occlusion_ray, &ray);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "spatial", vec3(2, 0, 0), &voice), AUDIO_OK);
    ASSERT_EQ(ray.calls, 1u);
    ASSERT_FLOAT_EQ(ray.source.e[0], 2.0f, 0.0f);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 1e-6f);
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), 0.5f, 1e-6f);

    ray.blocked = true;
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(2, 0, 0)), AUDIO_OK);
    ASSERT_EQ(ray.calls, 2u);
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), 0.125f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.125f, 1e-6f);

    audio_system_update(as, vec3(1, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_EQ(ray.calls, 3u);
    ASSERT_FLOAT_EQ(ray.listener.e[0], 1.0f, 0.0f);
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), 0.25f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.25f, 1e-6f);
    audio_system_update(as, vec3(1, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_EQ(ray.calls, 3u);

    f32 before = audio_voice_spatial_gain(as, voice);
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(NAN, 0, 0)), AUDIO_INVALID);
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), before, 0.0f);
    ASSERT_EQ(audio_voice_set_position(as, 0, vec3(0, 0, 0)), AUDIO_STALE);
    audio_system_destroy(as);
}

TEST(nonspatial_event_never_casts_ray)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 sample = 1.0f;
    AudioClipHandle clip = register_ramp(as, &sample, 1);
    AudioEventDesc desc = make_event_desc(clip);
    ASSERT_EQ(audio_event_register(as, "flat", &desc), AUDIO_OK);
    FakeRay ray;
    memset(&ray, 0, sizeof(ray));
    ray.blocked = true;
    audio_set_occlusion_ray_callback(as, fake_occlusion_ray, &ray);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "flat", vec3(100, 0, 0), &voice), AUDIO_OK);
    ASSERT_EQ(ray.calls, 0u);
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), 1.0f, 0.0f);
    audio_system_destroy(as);
}

TEST(extended_voice_uses_bus_and_master_gain)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 sample = 1.0f;
    AudioClipHandle clip = register_ramp(as, &sample, 1);
    u32 bus = audio_bus_create(as, "extended-sfx");
    ASSERT_NEQ(bus, AUDIO_BUS_INVALID);
    AudioEventDesc desc = make_event_desc(clip);
    desc.bus = bus;
    ASSERT_EQ(audio_event_register(as, "bused", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "bused", vec3(0, 0, 0), &voice), AUDIO_OK);
    audio_bus_set_gain(as, bus, 0.5f);
    audio_bus_set_gain(as, AUDIO_BUS_MASTER, 0.5f);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.25f, 1e-6f);
    audio_system_destroy(as);
}

static void wav_u16(u8 *out, u32 value) {
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8);
}

static void wav_u32(u8 *out, u32 value) {
    wav_u16(out, value & 0xFFFFu);
    wav_u16(out + 2, value >> 16);
}

static bool write_pcm_wav(const char *path) {
    u8 header[44] = {0};
    memcpy(header, "RIFF", 4);
    wav_u32(header + 4, 44);
    memcpy(header + 8, "WAVEfmt ", 8);
    wav_u32(header + 16, 16);
    wav_u16(header + 20, 1);
    wav_u16(header + 22, 1);
    wav_u32(header + 24, 48000);
    wav_u32(header + 28, 96000);
    wav_u16(header + 32, 2);
    wav_u16(header + 34, 16);
    memcpy(header + 36, "data", 4);
    wav_u32(header + 40, 8);
    const i16 samples[] = {8192, 16384, -16384, 32767};
    FILE *file = fopen(path, "wb");
    if (!file) return false;
    bool ok = fwrite(header, 1, sizeof(header), file) == sizeof(header) &&
              fwrite(samples, sizeof(samples[0]), 4, file) == 4;
    fclose(file);
    return ok;
}

TEST(legacy_file_apis_render_predecoded_pcm)
{
    char path[512];
    test_tmp(path, sizeof(path), "audio-legacy.pcm");
    ASSERT_TRUE(write_pcm_wav(path));
    for (u32 mode = 0; mode < 2; ++mode) {
        AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
        ASSERT_NOT_NULL(as);
        u32 voice = mode == 0 ? audio_play(as, path, 1.0f, true) :
            audio_play_streamed(as, path, 1.0f, true, false, vec3(0, 0, 0));
        ASSERT_NEQ(voice, 0u);
        f32 output[10];
        ASSERT_EQ(audio_system_render(as, output, 5), AUDIO_OK);
        ASSERT_FLOAT_EQ(output[0], 0.0f, 0.0f);
        ASSERT_FLOAT_EQ(output[1], 0.0f, 0.0f);
        const f32 expected[] = {0.25f, 0.5f, -0.5f, 32767.0f / 32768.0f};
        for (u32 i = 0; i < 4; ++i) {
            ASSERT_FLOAT_EQ(output[2*(i+1)], expected[i], 1e-5f);
            ASSERT_FLOAT_EQ(output[2*(i+1)+1], expected[i], 1e-5f);
        }
        audio_stop(as, voice);
        audio_system_destroy(as);
    }
    ASSERT_EQ(remove(path), 0);
}

static bool write_sine_wav(const char *path) {
    u8 header[44] = {0};
    memcpy(header, "RIFF", 4);
    wav_u32(header + 4, 96036);
    memcpy(header + 8, "WAVEfmt ", 8);
    wav_u32(header + 16, 16);
    wav_u16(header + 20, 1);
    wav_u16(header + 22, 1);
    wav_u32(header + 24, 48000);
    wav_u32(header + 28, 96000);
    wav_u16(header + 32, 2);
    wav_u16(header + 34, 16);
    memcpy(header + 36, "data", 4);
    wav_u32(header + 40, 96000);
    FILE *file = fopen(path, "wb");
    if (!file) return false;
    bool ok = fwrite(header, 1, sizeof(header), file) == sizeof(header);
    for (u32 i = 0; i < 48000 && ok; ++i) {
        f32 phase = 2.0f * 3.14159265358979323846f * 1000.0f *
                    (f32)i / 48000.0f;
        i16 sample = (i16)(sinf(phase) * 8192.0f);
        ok = fwrite(&sample, sizeof(sample), 1, file) == 1;
    }
    fclose(file);
    return ok;
}

TEST(legacy_decoded_play_3d_doppler_changes_pcm)
{
    char path[512];
    test_tmp(path, sizeof(path), "audio-doppler.pcm");
    ASSERT_TRUE(write_sine_wav(path));
    AudioSystem *slow = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    AudioSystem *fast = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(slow);
    ASSERT_NOT_NULL(fast);
    audio_play_3d(slow, path, vec3(1, 0, 0), 1.0f, true);
    audio_play_3d(fast, path, vec3(1, 0, 0), 1.0f, true);
    ASSERT_EQ(slow->source_count, 1u);
    ASSERT_EQ(fast->source_count, 1u);
    ASSERT_TRUE(slow->sources[0].active);
    ASSERT_TRUE(fast->sources[0].active);
    ma_sound_set_velocity(&slow->sources[0].sound, 0, 0, 0);
    ma_sound_set_velocity(&fast->sources[0].sound, 100, 0, 0);
    static f32 slow_pcm[9600];
    static f32 fast_pcm[9600];
    ASSERT_EQ(audio_system_render(slow, slow_pcm, 4800), AUDIO_OK);
    ASSERT_EQ(audio_system_render(fast, fast_pcm, 4800), AUDIO_OK);
    ASSERT_EQ(audio_system_render(slow, slow_pcm, 4800), AUDIO_OK);
    ASSERT_EQ(audio_system_render(fast, fast_pcm, 4800), AUDIO_OK);
    ASSERT_NEQ(memcmp(slow_pcm, fast_pcm, sizeof(slow_pcm)), 0);
    audio_system_destroy(slow);
    audio_system_destroy(fast);
    ASSERT_EQ(remove(path), 0);
}

static void render_dsp_fixture(f32 output[16]) {
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    if (!as) return;
    const f32 samples[] = {1, 0, 0, 0, 0, 0, 0, 0};
    AudioClipHandle clip = register_ramp(as, samples, 8);
    AudioEventDesc desc = make_event_desc(clip);
    desc.dsp.stage_count = 2;
    desc.dsp.stages[0].type = AUDIO_DSP_FILTER;
    desc.dsp.stages[0].cutoff_hz = 1000.0f;
    desc.dsp.stages[1].type = AUDIO_DSP_DELAY;
    desc.dsp.stages[1].delay_frames = 2;
    desc.dsp.stages[1].mix = 1.0f;
    if (audio_event_register(as, "fixture", &desc) == AUDIO_OK) {
        AudioVoiceHandle voice;
        if (audio_event_trigger(as, "fixture", vec3(0, 0, 0), &voice) == AUDIO_OK) {
            memset(output, 0, 16 * sizeof(f32));
            audio_system_render(as, output, 8);
        }
    }
    audio_system_destroy(as);
}

TEST(fake_backend_pcm_is_bit_exact_across_instances)
{
    f32 first[16], second[16];
    render_dsp_fixture(first);
    render_dsp_fixture(second);
    ASSERT_EQ(memcmp(first, second, sizeof(first)), 0);
    ASSERT_TRUE(first[4] != 0.0f);
}

TEST(null_backend_accepts_concurrent_command_lifecycle)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_NULL);
    ASSERT_NOT_NULL(as);
    f32 samples[4800];
    for (u32 i = 0; i < 4800; ++i) samples[i] = 0.1f;
    AudioClipHandle clip = register_named_pcm(as, "null-loop", samples, 4800);
    AudioEventDesc desc = make_event_desc(clip);
    desc.looping = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "null-event", &desc), AUDIO_OK);
    AudioClipHandle tracks[] = {clip, clip};
    AudioMusicPlaylistDesc playlist;
    memset(&playlist, 0, sizeof(playlist));
    playlist.tracks = tracks;
    playlist.track_count = 2;
    playlist.loop = true;
    playlist.crossfade_frames = 16;
    playlist.volume = 0.5f;
    ASSERT_EQ(audio_music_set_playlist(as, &playlist), AUDIO_OK);
    ASSERT_EQ(audio_music_play(as), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    for (u32 i = 0; i < 64; ++i) {
        AudioResult triggered = audio_event_trigger(as, "null-event",
            vec3((f32)(i % 4), 0, 0), &voice);
        ASSERT_TRUE(triggered == AUDIO_OK || triggered == AUDIO_OVERLOAD);
        audio_system_update(as, vec3((f32)(i % 3), 0, 0),
                            vec3(0, 0, -1), vec3(0, 1, 0));
        ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    }
    if (voice) (void)audio_voice_stop(as, voice);
    (void)audio_music_stop(as);
    audio_system_destroy(as);
}

TEST(event_overload_does_not_run_spatial_ray)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 sample = 0.5f;
    AudioClipHandle clip = register_ramp(as, &sample, 1);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "full-commands", &desc), AUDIO_OK);
    FakeRay ray;
    memset(&ray, 0, sizeof(ray));
    audio_set_occlusion_ray_callback(as, fake_occlusion_ray, &ray);
    AudioVoiceHandle voice = 0;
    for (u32 i = 0; i < 16; ++i) {
        ASSERT_EQ(audio_event_trigger(as, "full-commands", vec3(1, 0, 0), &voice),
                  AUDIO_OK);
    }
    ASSERT_EQ(ray.calls, 16u);
    ASSERT_EQ(audio_event_trigger(as, "full-commands", vec3(1, 0, 0), &voice),
              AUDIO_OVERLOAD);
    ASSERT_EQ(ray.calls, 16u);
    ASSERT_EQ(voice, 0u);
    audio_system_destroy(as);
}

TEST(stop_then_restart_before_drain_keeps_new_epoch_live)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.1f, 0.2f, 0.3f, 0.4f};
    AudioClipHandle clip = register_ramp(as, samples, 4);
    AudioEventDesc desc = make_event_desc(clip);
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "stop-restart", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0, restarted = 0;
    ASSERT_EQ(audio_event_trigger(as, "stop-restart", vec3(0, 0, 0), &voice), AUDIO_OK);
    f32 output[8];
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    ASSERT_EQ(audio_voice_stop(as, voice), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "stop-restart", vec3(0, 0, 0), &restarted), AUDIO_OK);
    ASSERT_EQ(restarted, voice);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.1f, 1e-6f);
    u32 count = 0, cursor = 0;
    ASSERT_EQ(audio_event_active_count(as, "stop-restart", &count), AUDIO_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(audio_voice_cursor(as, restarted, &cursor), AUDIO_OK);
    ASSERT_EQ(cursor, 1u);
    audio_system_destroy(as);
}

TEST(natural_end_then_restart_issues_live_generation)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.1f, 0.2f};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "natural-restart", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0, restarted = 0;
    ASSERT_EQ(audio_event_trigger(as, "natural-restart", vec3(0, 0, 0), &voice), AUDIO_OK);
    f32 output[4];
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "natural-restart", vec3(0, 0, 0), &restarted), AUDIO_OK);
    ASSERT_NEQ(restarted, voice);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.1f, 1e-6f);
    u32 count = 0;
    ASSERT_EQ(audio_event_active_count(as, "natural-restart", &count), AUDIO_OK);
    ASSERT_EQ(count, 1u);
    audio_system_destroy(as);
}

TEST(restart_defers_cursor_reset_until_start_is_consumed)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    AudioClipHandle clip = register_ramp(as, samples, 6);
    AudioEventDesc desc = make_event_desc(clip);
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "cursor-restart", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "cursor-restart", vec3(0, 0, 0), &voice), AUDIO_OK);
    f32 output[4];
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "cursor-restart", vec3(0, 0, 0), &voice), AUDIO_OK);
    u32 cursor = 0;
    ASSERT_EQ(audio_voice_cursor(as, voice, &cursor), AUDIO_OK);
    ASSERT_EQ(cursor, 2u);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.1f, 1e-6f);
    audio_system_destroy(as);
}

TEST(restart_spatial_gain_changes_with_start_epoch)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1.0f, 1.0f};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "gain-restart", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "gain-restart", vec3(2, 0, 0), &voice), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "gain-restart", vec3(4, 0, 0), &voice), AUDIO_OK);
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), 0.5f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.25f, 1e-6f);
    audio_system_destroy(as);
}

TEST(nonfinite_listener_preserves_previous_spatial_state)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1, 1, 1, 1};
    AudioClipHandle clip = register_ramp(as, samples, 4);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "listener-guard", &desc), AUDIO_OK);
    FakeRay ray;
    memset(&ray, 0, sizeof(ray));
    audio_set_occlusion_ray_callback(as, fake_occlusion_ray, &ray);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "listener-guard", vec3(2, 0, 0), &voice), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_EQ(ray.calls, 1u);
    audio_system_update(as, vec3(NAN, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_EQ(ray.calls, 1u);
    ASSERT_FLOAT_EQ(as->listener_pos.e[0], 0.0f, 0.0f);
    audio_system_update(as, vec3(INFINITY, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_EQ(ray.calls, 1u);
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), 0.5f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 1e-6f);

    audio_system_update(as, vec3(FLT_MAX, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_EQ(ray.calls, 2u);
    ASSERT_TRUE(isfinite(audio_voice_spatial_gain(as, voice)));
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), 0.01f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.01f, 1e-6f);
    audio_system_destroy(as);
}

TEST(stop_pending_voice_does_not_ray_or_reposition)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1, 1};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "stop-ray", &desc), AUDIO_OK);
    FakeRay ray;
    memset(&ray, 0, sizeof(ray));
    audio_set_occlusion_ray_callback(as, fake_occlusion_ray, &ray);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "stop-ray", vec3(2, 0, 0), &voice), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_EQ(audio_voice_stop(as, voice), AUDIO_OK);
    ASSERT_EQ(ray.calls, 1u);
    audio_system_update(as, vec3(1, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_EQ(ray.calls, 1u);
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(3, 0, 0)), AUDIO_REJECTED);
    ASSERT_EQ(ray.calls, 1u);
    audio_system_destroy(as);
}

TEST(bus_nonfinite_gain_is_rejected_consistently)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1, 1};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    u32 bus = audio_bus_create(as, "finite-bus");
    AudioEventDesc desc = make_event_desc(clip);
    desc.bus = bus;
    ASSERT_EQ(audio_event_register(as, "finite-bus-event", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "finite-bus-event", vec3(0, 0, 0), &voice), AUDIO_OK);
    audio_bus_set_gain(as, bus, 0.5f);
    audio_bus_set_gain(as, bus, NAN);
    audio_bus_set_gain(as, bus, INFINITY);
    audio_bus_set_gain(as, bus, -INFINITY);
    ASSERT_FLOAT_EQ(audio_bus_gain(as, bus), 0.5f, 0.0f);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 1e-6f);
    audio_system_destroy(as);
}

TEST(event_registration_distinguishes_stale_clip)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(999);
    ASSERT_EQ(audio_event_register(as, "stale-clip", &desc), AUDIO_STALE);
    desc.clip = 0;
    ASSERT_EQ(audio_event_register(as, "invalid-clip", &desc), AUDIO_INVALID);
    AudioVoiceHandle voice = 1;
    ASSERT_EQ(audio_event_trigger(as, "stale-clip", vec3(0, 0, 0), &voice), AUDIO_INVALID);
    ASSERT_EQ(voice, 0u);
    audio_system_destroy(as);
}

TEST(trigger_position_before_first_drain_uses_latest_revision)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 sample = 1.0f;
    AudioClipHandle clip = register_ramp(as, &sample, 1);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "revision-trigger", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "revision-trigger", vec3(2, 0, 0), &voice), AUDIO_OK);
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(4, 0, 0)), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(output[1], 0.25f, 1e-6f);
    audio_system_destroy(as);
}

TEST(listener_before_first_drain_uses_latest_revision)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 sample = 1.0f;
    AudioClipHandle clip = register_ramp(as, &sample, 1);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "revision-listener", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "revision-listener", vec3(2, 0, 0), &voice), AUDIO_OK);
    audio_system_update(as, vec3(1, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 1.0f, 1e-6f);
    audio_system_destroy(as);
}

TEST(restart_position_before_drain_uses_latest_revision)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1.0f, 1.0f};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "revision-restart", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "revision-restart", vec3(2, 0, 0), &voice), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "revision-restart", vec3(4, 0, 0), &voice), AUDIO_OK);
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(8, 0, 0)), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.125f, 1e-6f);
    audio_system_destroy(as);
}

TEST(music_zero_fade_replay_update_waits_for_start)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 a[] = {0.25f, 0.25f};
    const f32 b[] = {0.75f, 0.75f};
    AudioClipHandle tracks[] = {
        register_named_pcm(as, "revision-music-a", a, 2),
        register_named_pcm(as, "revision-music-b", b, 2)
    };
    AudioMusicPlaylistDesc playlist;
    memset(&playlist, 0, sizeof(playlist));
    playlist.tracks = tracks;
    playlist.track_count = 2;
    playlist.loop = true;
    playlist.volume = 1.0f;
    ASSERT_EQ(audio_music_set_playlist(as, &playlist), AUDIO_OK);
    ASSERT_EQ(audio_music_play(as), AUDIO_OK);
    f32 output[4];
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    AudioMusicState state;
    u32 index = 99;
    ASSERT_EQ(audio_music_state(as, &state, &index), AUDIO_OK);
    ASSERT_EQ(index, 1u);
    ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    ASSERT_EQ(audio_music_state(as, &state, &index), AUDIO_OK);
    ASSERT_EQ(state, AUDIO_MUSIC_PLAYING);
    ASSERT_EQ(index, 1u);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.75f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    ASSERT_EQ(audio_music_state(as, &state, &index), AUDIO_OK);
    ASSERT_EQ(index, 0u);
    ASSERT_EQ(audio_music_update(as), AUDIO_OK);
    ASSERT_EQ(audio_music_state(as, &state, &index), AUDIO_OK);
    ASSERT_EQ(state, AUDIO_MUSIC_PLAYING);
    ASSERT_EQ(index, 0u);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.25f, 1e-6f);
    audio_system_destroy(as);
}

TEST(epoch_max_retires_voice_without_wrapping_to_zero)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 sample = 1.0f;
    AudioClipHandle clip = register_ramp(as, &sample, 1);
    AudioEventDesc desc = make_event_desc(clip);
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "epoch-boundary", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "epoch-boundary", vec3(0, 0, 0), &voice), AUDIO_OK);
    AudioExtended *ext = (AudioExtended *)as->extended;
    u32 slot = (voice & 0xFFu) - 1u;
    ASSERT_EQ(ext->voices[slot].epoch, 1u);
    ext->voices[slot].epoch = UINT64_MAX - 1u;
    ASSERT_EQ(audio_event_trigger(as, "epoch-boundary", vec3(0, 0, 0), &voice), AUDIO_OK);
    ASSERT_EQ(ext->voices[slot].epoch, UINT64_MAX);
    u64 snapshot = atomic_load(&ext->voices[slot].spatial_snapshot);
    u32 serial = ext->voices[slot].serial;
    u64 order = ext->voices[slot].order;
    ASSERT_EQ(audio_event_trigger(as, "epoch-boundary", vec3(0, 0, 0), &voice),
              AUDIO_OVERLOAD);
    ASSERT_EQ(ext->voices[slot].epoch, UINT64_MAX);
    ASSERT_EQ(ext->voices[slot].serial, serial);
    ASSERT_EQ(ext->voices[slot].order, order);
    ASSERT_EQ(atomic_load(&ext->voices[slot].spatial_snapshot), snapshot);
    ASSERT_EQ(voice, 0u);
    audio_system_destroy(as);
}

TEST(extended_stereo_clip_preserves_interleaved_pcm)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {0.25f, -0.5f, 0.75f, -1.0f};
    AudioPcmDesc pcm = mono_pcm(samples, 2);
    pcm.channels = 2;
    AudioClipHandle clip = 0;
    ASSERT_EQ(audio_clip_register(as, "stereo-clip", &pcm, &clip), AUDIO_OK);
    AudioEventDesc desc = make_event_desc(clip);
    ASSERT_EQ(audio_event_register(as, "stereo-event", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "stereo-event", vec3(0, 0, 0), &voice), AUDIO_OK);
    f32 output[4];
    ASSERT_EQ(audio_system_render(as, output, 2), AUDIO_OK);
    for (u32 i = 0; i < 4; ++i) ASSERT_FLOAT_EQ(output[i], samples[i], 1e-6f);
    audio_system_destroy(as);
}

TEST(start_initial_gain_cas_preserves_interleaved_revision)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 sample = 1.0f;
    AudioClipHandle clip = register_ramp(as, &sample, 1);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "cas-interleave", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "cas-interleave", vec3(2, 0, 0), &voice), AUDIO_OK);
    test_interleave_gain = 0.25f;
    test_interleave_armed = true;
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(output[1], 0.25f, 1e-6f);
    audio_system_destroy(as);
}

static void render_with_held_commands(AudioVoice *voice, f32 output[2]) {
    u32 tail = atomic_load(&voice->tail);
    u32 head = atomic_load(&voice->head);
    atomic_store(&voice->tail, head);
    (void)voice_read(&voice->base, output, 1, NULL);
    atomic_store(&voice->tail, tail);
}

TEST(restart_new_epoch_does_not_modulate_held_old_pcm)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1.0f, 1.0f};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "held-restart", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    ASSERT_EQ(audio_event_trigger(as, "held-restart", vec3(2, 0, 0), &handle), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_EQ(audio_event_trigger(as, "held-restart", vec3(4, 0, 0), &handle), AUDIO_OK);
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(8, 0, 0)), AUDIO_OK);
    AudioExtended *ext = (AudioExtended *)as->extended;
    AudioVoice *voice = &ext->voices[(handle & 0xFFu) - 1u];
    render_with_held_commands(voice, output);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.125f, 1e-6f);
    audio_system_destroy(as);
}

TEST(restart_between_epoch_and_snapshot_loads_keeps_old_pcm_gain)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1.0f, 1.0f};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "read-interleave", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    ASSERT_EQ(audio_event_trigger(as, "read-interleave", vec3(2, 0, 0), &handle), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 1e-6f);

    AudioExtended *ext = (AudioExtended *)as->extended;
    test_read_interleave_system = as;
    test_read_interleave_voice = &ext->voices[(handle & 0xFFu) - 1u];
    test_read_interleave_handle = handle;
    test_read_interleave_armed = true;
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_TRUE(!test_read_interleave_armed);
    ASSERT_EQ(test_read_interleave_trigger_result, AUDIO_OK);
    ASSERT_EQ(test_read_interleave_position_result, AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.125f, 1e-6f);
    audio_system_destroy(as);
}

TEST(listener_start_cas_loss_republishes_same_listener)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1.0f, 1.0f};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "listener-cas", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    ASSERT_EQ(audio_event_trigger(as, "listener-cas", vec3(2, 0, 0), &handle), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 1e-6f);
    ASSERT_EQ(audio_event_trigger(as, "listener-cas", vec3(4, 0, 0), &handle), AUDIO_OK);

    AudioExtended *ext = (AudioExtended *)as->extended;
    test_listener_interleave_voice = &ext->voices[(handle & 0xFFu) - 1u];
    test_listener_interleave_applied = false;
    test_listener_interleave_armed = true;
    audio_system_update(as, vec3(12, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_TRUE(!test_listener_interleave_armed);
    ASSERT_TRUE(test_listener_interleave_applied);
    audio_system_update(as, vec3(12, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, handle), 0.125f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.125f, 1e-6f);
    audio_system_destroy(as);
}

TEST(revision_max_is_atomic_and_retires_spatial_starts)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[] = {1.0f, 1.0f};
    AudioClipHandle clip = register_ramp(as, samples, 2);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "revision-boundary", &desc), AUDIO_OK);
    FakeRay ray;
    memset(&ray, 0, sizeof(ray));
    audio_set_occlusion_ray_callback(as, fake_occlusion_ray, &ray);
    AudioVoiceHandle handle = 0;
    ASSERT_EQ(audio_event_trigger(as, "revision-boundary", vec3(2, 0, 0), &handle), AUDIO_OK);
    f32 output[2];
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    AudioExtended *ext = (AudioExtended *)as->extended;
    AudioVoice *voice = &ext->voices[(handle & 0xFFu) - 1u];
    voice->spatial_revision = UINT32_MAX - 1u;
    atomic_store(&voice->spatial_snapshot,
        spatial_pack(UINT32_MAX - 1u, spatial_gain_of(
            atomic_load(&voice->spatial_snapshot))));
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(4, 0, 0)), AUDIO_OK);
    ASSERT_EQ(voice->spatial_revision, UINT32_MAX);
    u64 snapshot = atomic_load(&voice->spatial_snapshot);
    u64 epoch = voice->epoch;
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(8, 0, 0)), AUDIO_OVERLOAD);
    ASSERT_EQ(ray.calls, 2u);
    ASSERT_EQ(atomic_load(&voice->spatial_snapshot), snapshot);
    ASSERT_EQ(audio_event_trigger(as, "revision-boundary", vec3(4, 0, 0), &handle),
              AUDIO_OVERLOAD);
    ASSERT_EQ(voice->epoch, epoch);
    ASSERT_EQ(atomic_load(&voice->spatial_snapshot), snapshot);
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
    RUN_TEST(music_crossfade_mixes_exact_pcm);
    RUN_TEST(music_loop_crossfade_wraps_to_first_track);
    RUN_TEST(music_playlist_validation_is_atomic_and_running_replacement_rejected);
    RUN_TEST(music_zero_fade_advances_and_stops);
    RUN_TEST(spatial_event_combines_distance_and_ray_occlusion);
    RUN_TEST(nonspatial_event_never_casts_ray);
    RUN_TEST(extended_voice_uses_bus_and_master_gain);
    RUN_TEST(legacy_file_apis_render_predecoded_pcm);
    RUN_TEST(fake_backend_pcm_is_bit_exact_across_instances);
    RUN_TEST(null_backend_accepts_concurrent_command_lifecycle);
    RUN_TEST(event_overload_does_not_run_spatial_ray);
    RUN_TEST(stop_then_restart_before_drain_keeps_new_epoch_live);
    RUN_TEST(natural_end_then_restart_issues_live_generation);
    RUN_TEST(restart_defers_cursor_reset_until_start_is_consumed);
    RUN_TEST(restart_spatial_gain_changes_with_start_epoch);
    RUN_TEST(nonfinite_listener_preserves_previous_spatial_state);
    RUN_TEST(stop_pending_voice_does_not_ray_or_reposition);
    RUN_TEST(bus_nonfinite_gain_is_rejected_consistently);
    RUN_TEST(event_registration_distinguishes_stale_clip);
    RUN_TEST(legacy_decoded_play_3d_doppler_changes_pcm);
    RUN_TEST(trigger_position_before_first_drain_uses_latest_revision);
    RUN_TEST(listener_before_first_drain_uses_latest_revision);
    RUN_TEST(restart_position_before_drain_uses_latest_revision);
    RUN_TEST(music_zero_fade_replay_update_waits_for_start);
    RUN_TEST(epoch_max_retires_voice_without_wrapping_to_zero);
    RUN_TEST(extended_stereo_clip_preserves_interleaved_pcm);
    RUN_TEST(start_initial_gain_cas_preserves_interleaved_revision);
    RUN_TEST(restart_new_epoch_does_not_modulate_held_old_pcm);
    RUN_TEST(restart_between_epoch_and_snapshot_loads_keeps_old_pcm_gain);
    RUN_TEST(listener_start_cas_loss_republishes_same_listener);
    RUN_TEST(revision_max_is_atomic_and_retires_spatial_starts);
TEST_MAIN_END()
