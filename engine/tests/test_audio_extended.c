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
    (void)spatial_publish(voice, voice->epoch, test_interleave_gain, 0.0f, 1.0f, 0);
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

/* ---- live PCM streams ---- */

TEST(pcm_stream_open_bounds_and_handles)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h[AUDIO_PCM_STREAM_MAX + 1u];
    AudioPcmStreamHandle extra = 0;
    u32 frames = 7u;
    u64 under = 7u;
    i16 one = 1;
    u32 written = 9u;
    ASSERT_EQ(audio_pcm_stream_open(NULL, 1u, AUDIO_BUS_MASTER, 1.0f, &h[0]), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_open(as, 0u, AUDIO_BUS_MASTER, 1.0f, &h[0]), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_open(as, 3u, AUDIO_BUS_MASTER, 1.0f, &h[0]), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, NULL), AUDIO_INVALID);
    for (u32 i = 0; i < AUDIO_PCM_STREAM_MAX; ++i) {
        ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h[i]), AUDIO_OK);
        ASSERT_NEQ(h[i], 0u);
    }
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &extra), AUDIO_OVERLOAD);
    ASSERT_EQ(audio_pcm_stream_queued(as, h[0], &frames), AUDIO_OK);
    ASSERT_EQ(frames, 0u);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h[0], &under), AUDIO_OK);
    ASSERT_EQ(under, 0u);
    /* close makes the handle stale; the slot opens again with a new handle */
    ASSERT_EQ(audio_pcm_stream_close(as, h[1]), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h[1]), AUDIO_STALE);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h[1], &one, 1u, &written), AUDIO_STALE);
    ASSERT_EQ(audio_pcm_stream_queued(as, h[1], &frames), AUDIO_STALE);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h[1], &under), AUDIO_STALE);
    ASSERT_EQ(audio_pcm_stream_open(as, 2u, AUDIO_BUS_MASTER, 1.0f, &extra), AUDIO_OK);
    ASSERT_NEQ(extra, h[1]);
    ASSERT_EQ(audio_pcm_stream_close(as, h[1]), AUDIO_STALE);
    ASSERT_EQ(audio_pcm_stream_close(as, 0u), AUDIO_INVALID);
    /* slot bits outside 1..AUDIO_PCM_STREAM_MAX */
    ASSERT_EQ(audio_pcm_stream_close(as, 7u), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_close(as, 8u), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_queued(as, (extra & ~7u) | 5u, &frames), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_close(NULL, extra), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, extra, NULL, 1u, &written), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, extra, &one, 1u, NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_queued(as, extra, NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_underruns(as, extra, NULL), AUDIO_INVALID);
    audio_system_destroy(as);
}

TEST(pcm_stream_plays_mono_and_stereo_with_gain)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle mono = 0;
    AudioPcmStreamHandle stereo = 0;
    u32 written = 0;
    f32 out[8];
    const i16 mono_pcm[2] = {16384, -8192};
    const i16 stereo_pcm[4] = {8192, -16384, 0, 32767};
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &mono), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, mono, mono_pcm, 2u, &written), AUDIO_OK);
    ASSERT_EQ(written, 2u);
    ASSERT_EQ(audio_system_render(as, out, 2u), AUDIO_OK);
    /* mono is duplicated to both channels */
    ASSERT_FLOAT_EQ(out[0], 0.5f, 1e-6f);
    ASSERT_FLOAT_EQ(out[1], 0.5f, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], -0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(out[3], -0.25f, 1e-6f);
    ASSERT_EQ(audio_pcm_stream_close(as, mono), AUDIO_OK);

    u32 bus = audio_bus_create(as, "voice");
    ASSERT_NEQ(bus, AUDIO_BUS_INVALID);
    ASSERT_EQ(audio_pcm_stream_open(as, 2u, bus, 0.5f, &stereo), AUDIO_OK);
    audio_bus_set_gain(as, bus, 0.5f);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, stereo, stereo_pcm, 2u, &written), AUDIO_OK);
    ASSERT_EQ(written, 2u);
    ASSERT_EQ(audio_system_render(as, out, 2u), AUDIO_OK);
    /* volume 0.5 x bus 0.5 */
    ASSERT_FLOAT_EQ(out[0], 0.0625f, 1e-6f);
    ASSERT_FLOAT_EQ(out[1], -0.125f, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(out[3], 32767.0f / 32768.0f * 0.25f, 1e-6f);
    /* the master fader applies on top */
    audio_bus_set_gain(as, AUDIO_BUS_MASTER, 0.5f);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, stereo, stereo_pcm, 1u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.03125f, 1e-6f);
    audio_bus_set_gain(as, AUDIO_BUS_MASTER, 1.0f);
    /* an invalid bus falls back to master; a negative volume is silence */
    ASSERT_EQ(audio_pcm_stream_close(as, stereo), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, 99u, -1.0f, &mono), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, mono, mono_pcm, 1u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_close(as, mono), AUDIO_OK);
    /* a bus id that does not exist yet is master too, even after a bus with
     * that id is created later */
    {
        u32 next_bus = bus + 1u;
        ASSERT_EQ(audio_pcm_stream_open(as, 1u, next_bus, 1.0f, &mono), AUDIO_OK);
        ASSERT_EQ(audio_bus_create(as, "later"), next_bus);
        audio_bus_set_gain(as, next_bus, 0.25f);
        ASSERT_EQ(audio_pcm_stream_write_i16(as, mono, mono_pcm, 1u, &written), AUDIO_OK);
        ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
        ASSERT_FLOAT_EQ(out[0], 0.5f, 1e-6f);
    }
    audio_system_destroy(as);
}

TEST(pcm_stream_ring_is_bounded_and_underruns_play_silence)
{
    static i16 pcm[AUDIO_PCM_STREAM_FRAMES + 16u];
    static f32 out[2u * (AUDIO_PCM_STREAM_FRAMES + 16u)];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    u32 written = 0;
    u32 queued = 0;
    u64 under = 0;
    for (u32 i = 0; i < AUDIO_PCM_STREAM_FRAMES + 16u; ++i) {
        pcm[i] = (i16)(i % 1000u + 1u);
    }
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    /* an empty stream that is rendered underruns */
    ASSERT_EQ(audio_system_render(as, out, 3u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 3u);
    /* only the ring's capacity fits */
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, AUDIO_PCM_STREAM_FRAMES + 16u, &written),
              AUDIO_OK);
    ASSERT_EQ(written, AUDIO_PCM_STREAM_FRAMES);
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, AUDIO_PCM_STREAM_FRAMES);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 1u, &written), AUDIO_OK);
    ASSERT_EQ(written, 0u);
    /* render 10 frames: the first ten samples, in order */
    ASSERT_EQ(audio_system_render(as, out, 10u), AUDIO_OK);
    for (u32 i = 0; i < 10u; ++i) {
        ASSERT_FLOAT_EQ(out[2u * i], (f32)pcm[i] / 32768.0f, 1e-7f);
    }
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, AUDIO_PCM_STREAM_FRAMES - 10u);
    /* the freed room takes more frames; they follow the queued ones */
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm + AUDIO_PCM_STREAM_FRAMES, 16u, &written),
              AUDIO_OK);
    ASSERT_EQ(written, 10u);
    ASSERT_EQ(audio_system_render(as, out, AUDIO_PCM_STREAM_FRAMES + 4u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[2u * (AUDIO_PCM_STREAM_FRAMES - 11u)],
                    (f32)pcm[AUDIO_PCM_STREAM_FRAMES - 1u] / 32768.0f, 1e-7f);
    ASSERT_FLOAT_EQ(out[2u * (AUDIO_PCM_STREAM_FRAMES - 10u)],
                    (f32)pcm[AUDIO_PCM_STREAM_FRAMES] / 32768.0f, 1e-7f);
    ASSERT_FLOAT_EQ(out[2u * (AUDIO_PCM_STREAM_FRAMES - 1u)],
                    (f32)pcm[AUDIO_PCM_STREAM_FRAMES + 9u] / 32768.0f, 1e-7f);
    /* past the queued frames: silence, counted as underrun */
    ASSERT_FLOAT_EQ(out[2u * AUDIO_PCM_STREAM_FRAMES], 0.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 3u + 4u);
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, 0u);
    /* a closed stream plays nothing and counts nothing */
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 4u, &written), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    out[0] = 1.0f;
    ASSERT_EQ(audio_system_render(as, out, 2u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.0f, 0.0f);
    /* the reopened slot starts empty, with no underruns and no stale PCM */
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, 0u);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 0u);
    audio_system_destroy(as);
}

/* The ring counters are free-running u32s. Across their wrap at 2^32 (about
 * 24.8 h of 48 kHz audio) a full ring must keep every frame in order:
 * the capacity has to divide 2^32 or two live frames share a slot. */
TEST(pcm_stream_ring_survives_counter_wraparound)
{
    static i16 pcm[AUDIO_PCM_STREAM_FRAMES];
    static f32 out[2u * AUDIO_PCM_STREAM_FRAMES];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    AudioPcmStream *stream = &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
    atomic_store(&stream->head, 0xFFFFFFF0u);
    atomic_store(&stream->tail, 0xFFFFFFF0u);
    for (u32 i = 0; i < AUDIO_PCM_STREAM_FRAMES; ++i) pcm[i] = (i16)(i + 1u);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, AUDIO_PCM_STREAM_FRAMES, &written),
              AUDIO_OK);
    ASSERT_EQ(written, AUDIO_PCM_STREAM_FRAMES);
    ASSERT_EQ(audio_system_render(as, out, AUDIO_PCM_STREAM_FRAMES), AUDIO_OK);
    for (u32 i = 0; i < AUDIO_PCM_STREAM_FRAMES; ++i) {
        ASSERT_FLOAT_EQ(out[2u * i], (f32)(i + 1u) / 32768.0f, 1e-7f);
    }
    audio_system_destroy(as);
}

static AudioPcmStreamHandle open_rate_stream(AudioSystem *as, u32 channels, u32 rate)
{
    AudioPcmStreamHandle h = 0;
    if (audio_pcm_stream_open_rate(as, channels, rate, AUDIO_BUS_MASTER, 1.0f, &h) != AUDIO_OK) {
        return 0;
    }
    return h;
}

TEST(pcm_stream_rate_bounds)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    ASSERT_EQ(audio_pcm_stream_open_rate(as, 1u, AUDIO_PCM_STREAM_MIN_RATE - 1u,
                                         AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_open_rate(as, 1u, AUDIO_PCM_STREAM_MAX_RATE + 1u,
                                         AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_open_rate(as, 3u, 16000u, AUDIO_BUS_MASTER, 1.0f, &h),
              AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_open_rate(NULL, 1u, 16000u, AUDIO_BUS_MASTER, 1.0f, &h),
              AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_open_rate(as, 1u, AUDIO_PCM_STREAM_MIN_RATE, AUDIO_BUS_MASTER,
                                         1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_open_rate(as, 2u, AUDIO_PCM_STREAM_MAX_RATE, AUDIO_BUS_MASTER,
                                         1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    audio_system_destroy(as);
}

/* 16 kHz to 48 kHz: three output frames per source frame, linearly
 * interpolated; queued counts source frames. */
TEST(pcm_stream_upsamples_16k_by_linear_interpolation)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    const i16 pcm[3] = {0, 3072, 6144}; /* 0, 0.09375, 0.1875 */
    u32 written = 0;
    u32 queued = 0;
    f32 out[2u * 6u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 3u, &written), AUDIO_OK);
    ASSERT_EQ(written, 3u);
    ASSERT_EQ(audio_system_render(as, out, 6u), AUDIO_OK);
    const f32 step = 3072.0f / 32768.0f / 3.0f;
    for (u32 i = 0; i < 6u; ++i) {
        ASSERT_FLOAT_EQ(out[2u * i], step * (f32)i, 1e-6f);
        ASSERT_FLOAT_EQ(out[2u * i + 1u], step * (f32)i, 1e-6f);
    }
    /* two source frames were passed; the third is still needed */
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, 1u);
    audio_system_destroy(as);
}

TEST(pcm_stream_rate_keeps_stereo_channels_apart)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 2u, 24000u);
    ASSERT_NEQ(h, 0u);
    const i16 pcm[6] = {0, 0, 8192, -8192, 16384, -16384};
    u32 written = 0;
    f32 out[2u * 4u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 3u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 4u), AUDIO_OK);
    /* 24 kHz: two output frames per source frame */
    ASSERT_FLOAT_EQ(out[0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], 0.125f, 1e-6f);
    ASSERT_FLOAT_EQ(out[3], -0.125f, 1e-6f);
    ASSERT_FLOAT_EQ(out[4], 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(out[5], -0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(out[6], 0.375f, 1e-6f);
    ASSERT_FLOAT_EQ(out[7], -0.375f, 1e-6f);
    audio_system_destroy(as);
}

/* Double-precision model of a fast stream: every source frame goes through
 * a 4th-order Butterworth low-pass (two RBJ biquads, cutoff 21600 Hz, in
 * transposed direct form II), then the mixer's linear interpolation picks
 * the output frames. */
typedef struct {
    double b0, b1, b2, a1, a2;
} RefBiquad;

static RefBiquad ref_lowpass(double q, u32 rate)
{
    const double pi = 3.14159265358979323846;
    double w0 = 2.0 * pi * 21600.0 / (double)rate;
    double alpha = sin(w0) / (2.0 * q);
    double c = cos(w0);
    double a0 = 1.0 + alpha;
    RefBiquad f;
    f.b0 = (1.0 - c) / 2.0 / a0;
    f.b1 = (1.0 - c) / a0;
    f.b2 = (1.0 - c) / 2.0 / a0;
    f.a1 = -2.0 * c / a0;
    f.a2 = (1.0 - alpha) / a0;
    return f;
}

/* filtered[frame * channels + c] for frames of interleaved i16 PCM */
static void ref_filter(const i16 *pcm, u32 frames, u32 channels, u32 rate, double *filtered)
{
    RefBiquad stage[2] = {ref_lowpass(0.54119610014619698, rate),
                          ref_lowpass(1.3065629648763766, rate)};
    double z[2][2][2];
    memset(z, 0, sizeof(z));
    for (u32 i = 0; i < frames; ++i) {
        for (u32 c = 0; c < channels; ++c) {
            double x = (double)pcm[(usize)i * channels + c] / 32768.0;
            for (u32 k = 0; k < 2u; ++k) {
                const RefBiquad *f = &stage[k];
                double y = f->b0 * x + z[k][c][0];
                z[k][c][0] = f->b1 * x - f->a1 * y + z[k][c][1];
                z[k][c][1] = f->b2 * x - f->a2 * y;
                x = y;
            }
            filtered[(usize)i * channels + c] = x;
        }
    }
}

/* the left output sample k of a stream whose source frames are all queued */
static double ref_output(const double *filtered, u32 frames, u32 channels, u32 rate, u32 k,
                         u32 channel)
{
    u64 pos = (u64)k * rate;
    u64 index = pos / AUDIO_PCM_SAMPLE_RATE;
    u64 rem = pos % AUDIO_PCM_SAMPLE_RATE;
    if (index >= frames || (rem != 0u && index + 1u >= frames)) return 0.0;
    double a = filtered[index * channels + channel];
    if (rem == 0u) return a;
    double b = filtered[(index + 1u) * channels + channel];
    return a + (b - a) * ((double)rem / (double)AUDIO_PCM_SAMPLE_RATE);
}

/* 96 kHz to 48 kHz: every second source frame after the low-pass (the
 * interpolation weight is zero at each output frame). */
TEST(pcm_stream_downsamples_96k)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 96000u);
    ASSERT_NEQ(h, 0u);
    i16 pcm[9];
    for (u32 i = 0; i < 9u; ++i) pcm[i] = (i16)(1000 * (i32)i);
    double filtered[9];
    ref_filter(pcm, 9u, 1u, 96000u, filtered);
    u32 written = 0;
    u32 queued = 0;
    f32 out[2u * 4u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 9u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 4u), AUDIO_OK);
    for (u32 i = 0; i < 4u; ++i) {
        ASSERT_FLOAT_EQ(out[2u * i], (f32)filtered[2u * i], 1e-6f);
        ASSERT_FLOAT_EQ(out[2u * i + 1u], (f32)filtered[2u * i], 1e-6f);
    }
    /* the ramp is filtered: past the first frame it lags the raw input */
    ASSERT_TRUE(out[6] < 6000.0f / 32768.0f - 1e-3f);
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, 1u);
    audio_system_destroy(as);
}

/* Decimation can step past the last written frame: the skipped frame is
 * passed over for output when it arrives, and the queue never counts below
 * zero. The filter still runs over it, in order. */
TEST(pcm_stream_downsample_skips_a_frame_that_arrives_late)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 96000u);
    ASSERT_NEQ(h, 0u);
    i16 pcm[9];
    for (u32 i = 0; i < 9u; ++i) pcm[i] = (i16)(1000 * (i32)i);
    double filtered[9];
    ref_filter(pcm, 9u, 1u, 96000u, filtered);
    u32 written = 0;
    u32 queued = 7u;
    u64 under = 0;
    f32 out[2u * 4u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 7u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 4u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[6], (f32)filtered[6], 1e-6f);
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, 0u);
    /* the next output needs frame 8; frame 7 is skipped once written */
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 1u);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm + 7u, 1u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 2u);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm + 8u, 1u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], (f32)filtered[8], 1e-6f);
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, 0u);
    audio_system_destroy(as);
}

/* 88.2 kHz: a non-integer ratio, so the filtered frames are interpolated */
TEST(pcm_stream_downsample_88k2_interpolates_filtered_frames)
{
    enum { kFrames = 400, kOut = 200 };
    static i16 pcm[kFrames];
    static double filtered[kFrames];
    static f32 out[2u * kOut];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 88200u);
    ASSERT_NEQ(h, 0u);
    u32 seed = 12345u;
    for (u32 i = 0; i < kFrames; ++i) {
        seed = seed * 1664525u + 1013904223u;
        pcm[i] = (i16)((i32)(seed >> 17) - 16384);
    }
    ref_filter(pcm, kFrames, 1u, 88200u, filtered);
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, kFrames, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kOut), AUDIO_OK);
    for (u32 k = 0; k < kOut; ++k) {
        ASSERT_FLOAT_EQ(out[2u * k], (f32)ref_output(filtered, kFrames, 1u, 88200u, k, 0u),
                        2e-6f);
    }
    audio_system_destroy(as);
}

static double rms_left(const f32 *out, u32 begin, u32 end)
{
    double sum = 0.0;
    for (u32 k = begin; k < end; ++k) sum += (double)out[2u * k] * out[2u * k];
    return sqrt(sum / (double)(end - begin));
}

/* +x, -x, +x, ... at 96 kHz is a tone at the stream's Nyquist rate. Taking
 * every second frame turns it into the constant +x; the low-pass has a zero
 * there, so it fades out instead. */
TEST(pcm_stream_downsample_removes_the_nyquist_tone)
{
    enum { kOut = 200 };
    static i16 pcm[2u * kOut];
    static f32 out[2u * kOut];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 96000u);
    ASSERT_NEQ(h, 0u);
    for (u32 i = 0; i < 2u * kOut; ++i) pcm[i] = (i & 1u) ? -8192 : 8192;
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 2u * kOut, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kOut), AUDIO_OK);
    for (u32 k = kOut - 50u; k < kOut; ++k) {
        ASSERT_TRUE(fabsf(out[2u * k]) < 1e-3f);
    }
    audio_system_destroy(as);
}

/* A 30 kHz tone at 96 kHz would alias to 18 kHz at the engine rate */
TEST(pcm_stream_downsample_attenuates_content_above_24k)
{
    enum { kOut = 1440 };
    static i16 pcm[2u * kOut];
    static f32 out[2u * kOut];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 96000u);
    ASSERT_NEQ(h, 0u);
    const double pi = 3.14159265358979323846;
    for (u32 i = 0; i < 2u * kOut; ++i) {
        pcm[i] = (i16)lrint(16384.0 * sin(2.0 * pi * 30000.0 * (double)i / 96000.0));
    }
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 2u * kOut, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kOut), AUDIO_OK);
    /* input RMS 0.5 / sqrt(2); 4th-order Butterworth at 30 kHz is about -19.5 dB */
    double rms = rms_left(out, 480u, 1440u);
    ASSERT_TRUE(rms < 0.2 * 0.5 / sqrt(2.0));
    ASSERT_TRUE(rms > 0.05 * 0.5 / sqrt(2.0));
    audio_system_destroy(as);
}

/* a 1 kHz tone passes within 1 dB */
TEST(pcm_stream_downsample_keeps_the_audible_band)
{
    enum { kOut = 1440 };
    static i16 pcm[2u * kOut];
    static f32 out[2u * kOut];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 96000u);
    ASSERT_NEQ(h, 0u);
    const double pi = 3.14159265358979323846;
    for (u32 i = 0; i < 2u * kOut; ++i) {
        pcm[i] = (i16)lrint(16384.0 * sin(2.0 * pi * 1000.0 * (double)i / 96000.0));
    }
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 2u * kOut, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kOut), AUDIO_OK);
    /* 960 output frames: 20 whole periods */
    double ratio = rms_left(out, 480u, 1440u) / (0.5 / sqrt(2.0));
    ASSERT_TRUE(ratio > 0.891 && ratio < 1.122);
    audio_system_destroy(as);
}

/* each channel has its own filter state */
TEST(pcm_stream_downsample_filters_stereo_channels_apart)
{
    enum { kOut = 200 };
    static i16 pcm[2u * 2u * kOut];
    static f32 out[2u * kOut];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 2u, 96000u);
    ASSERT_NEQ(h, 0u);
    for (u32 i = 0; i < 2u * kOut; ++i) {
        pcm[2u * i] = (i & 1u) ? -8192 : 8192;
        pcm[2u * i + 1u] = 16384;
    }
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 2u * kOut, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kOut), AUDIO_OK);
    for (u32 k = kOut - 50u; k < kOut; ++k) {
        ASSERT_TRUE(fabsf(out[2u * k]) < 1e-3f);
        ASSERT_FLOAT_EQ(out[2u * k + 1u], 0.5f, 1e-3f);
    }
    audio_system_destroy(as);
}

/* renders 40 frames of a 96 kHz stream holding pcm[0..80) */
static AudioResult render_fast_pattern(AudioSystem *as, AudioPcmStreamHandle h, const i16 *pcm,
                                       f32 *out)
{
    u32 written = 0;
    AudioResult result = audio_pcm_stream_write_i16(as, h, pcm, 80u, &written);
    if (result != AUDIO_OK || written != 80u) return AUDIO_FAILED;
    return audio_system_render(as, out, 40u);
}

/* A slot closed in the middle of a transient leaves no filter state or
 * progress behind: the next stream there sounds like one on a new system. */
TEST(pcm_stream_reopen_resets_the_filter)
{
    i16 first[80];
    i16 second[80];
    f32 reused[2u * 40u];
    f32 fresh[2u * 40u];
    for (u32 i = 0; i < 80u; ++i) {
        first[i] = (i16)(i % 3u == 0u ? 30000 : -20000);
        second[i] = (i16)(1000 + 37 * (i32)i);
    }
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 50000u);
    ASSERT_NEQ(h, 0u);
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, first, 80u, &written), AUDIO_OK);
    /* at 50 kHz the second output filters frames 1 and 2 but releases only
     * frame 1, so a filtered frame is still queued at close */
    ASSERT_EQ(audio_system_render(as, reused, 2u), AUDIO_OK);
    {
        const AudioPcmStream *stream =
            &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
        ASSERT_EQ(stream->filtered, 1u);
    }
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    h = open_rate_stream(as, 1u, 96000u);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(render_fast_pattern(as, h, second, reused), AUDIO_OK);
    audio_system_destroy(as);

    as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    h = open_rate_stream(as, 1u, 96000u);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(render_fast_pattern(as, h, second, fresh), AUDIO_OK);
    audio_system_destroy(as);
    for (u32 i = 0; i < 2u * 40u; ++i) ASSERT_FLOAT_EQ(reused[i], fresh[i], 0.0f);
    ASSERT_TRUE(fresh[2] != 0.0f);
}

/* A 48 kHz stream is not filtered: the samples come out as written. A slot
 * last used by a fast stream does not keep filtering. */
TEST(pcm_stream_at_the_engine_rate_is_not_filtered)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 96000u);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    h = open_rate_stream(as, 1u, AUDIO_PCM_SAMPLE_RATE);
    ASSERT_NEQ(h, 0u);
    const i16 pcm[4] = {8192, -8192, 8192, -8192};
    u32 written = 0;
    f32 out[2u * 4u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 4u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 4u), AUDIO_OK);
    for (u32 i = 0; i < 4u; ++i) ASSERT_FLOAT_EQ(out[2u * i], (f32)pcm[i] / 32768.0f, 0.0f);
    audio_system_destroy(as);
}

/* A stream closed part way between two source frames leaves no position
 * behind: the next stream in that slot starts on its first frame. */
TEST(pcm_stream_reopen_starts_at_the_first_frame)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const i16 pcm[3] = {0, 3072, 6144};
    /* different values: a leftover position would interpolate between them */
    const i16 fresh[2] = {9000, 3000};
    u32 written = 0;
    f32 out[2u * 2u];
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 3u, &written), AUDIO_OK);
    /* two output frames: the position is now 2/3 of a source frame in */
    ASSERT_EQ(audio_system_render(as, out, 2u), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    h = open_rate_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, fresh, 2u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 9000.0f / 32768.0f, 1e-6f);
    audio_system_destroy(as);
}

/* Missing data at a converted rate plays silence and counts as underrun;
 * the position waits, so a late write continues where playback stopped. */
TEST(pcm_stream_rate_underrun_resumes_at_the_same_position)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    const i16 first[2] = {0, 3072};
    const i16 more[1] = {6144};
    u32 written = 0;
    u64 under = 0;
    f32 out[2u * 8u];
    const f32 step = 3072.0f / 32768.0f / 3.0f;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, first, 2u, &written), AUDIO_OK);
    /* frames 0..2 interpolate 0 -> 3072; frame 3 sits exactly on source 1
     * and needs nothing else; frames 4 and 5 need source 2, which is
     * missing */
    ASSERT_EQ(audio_system_render(as, out, 6u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], step, 1e-6f);
    ASSERT_FLOAT_EQ(out[4], 2.0f * step, 1e-6f);
    ASSERT_FLOAT_EQ(out[6], 3.0f * step, 1e-6f);
    ASSERT_FLOAT_EQ(out[8], 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(out[10], 0.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 2u);
    /* the late frame continues the ramp where it stopped */
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, more, 1u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 3u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 4.0f * step, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], 5.0f * step, 1e-6f);
    ASSERT_FLOAT_EQ(out[4], 6.0f * step, 1e-6f);
    audio_system_destroy(as);
}

/* A spatial event and a spatial stream at the same place with the same
 * rolloff get the same gain: they share one distance model. */
TEST(spatial_event_and_stream_share_the_distance_model)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 one = 1.0f;
    AudioClipHandle clip = register_ramp(as, &one, 1);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.rolloff = 3.0f;
    desc.max_distance = 50.0f;
    ASSERT_EQ(audio_event_register(as, "far-call", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "far-call", vec3(5, 0, 0), &voice), AUDIO_OK);
    {
        /* the voice applies its start gain in the mixer */
        f32 output[2];
        ASSERT_EQ(audio_system_render(as, output, 1u), AUDIO_OK);
    }
    /* 1 / (1 + 3 * 4) */
    ASSERT_FLOAT_EQ(audio_voice_spatial_gain(as, voice), 1.0f / 13.0f, 1e-6f);
    AudioPcmStreamHandle h = 0;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 50.0f, 3.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(5, 0, 0)), AUDIO_OK);
    {
        AudioPcmStream *stream =
            &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
        ASSERT_FLOAT_EQ(gain_from_bits(atomic_load(&stream->spatial_bits)),
                        audio_voice_spatial_gain(as, voice), 1e-7f);
    }
    audio_system_destroy(as);
}

/* one rendered left sample of a stream holding the constant 0.5 */
static f32 render_half(AudioSystem *as, AudioPcmStreamHandle h)
{
    const i16 half[1] = {16384};
    u32 written = 0;
    f32 out[2];
    if (audio_pcm_stream_write_i16(as, h, half, 1u, &written) != AUDIO_OK || written != 1u) {
        return -1.0f;
    }
    if (audio_system_render(as, out, 1u) != AUDIO_OK) return -1.0f;
    return out[0];
}

TEST(pcm_stream_spatial_arguments)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    /* no spatial settings yet */
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(1, 0, 0)), AUDIO_REJECTED);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 0.0f, 10.0f, 1.0f, 0.5f), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 2.0f, 1.0f, 1.0f, 0.5f), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, -1.0f, 0.5f), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 1.5f), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, -0.1f), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, NAN, 10.0f, 1.0f, 0.5f), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, INFINITY, 1.0f, 0.5f), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(1, 0, 0)), AUDIO_REJECTED);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 0.5f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(2, 0, 0)), AUDIO_OK);
    {
        /* a rejected position changes neither the position nor the gain */
        AudioPcmStream *stream =
            &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
        u32 bits = atomic_load(&stream->spatial_bits);
        ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(NAN, 0, 0)), AUDIO_INVALID);
        ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(0, INFINITY, 0)), AUDIO_INVALID);
        ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(0, 0, -INFINITY)), AUDIO_INVALID);
        ASSERT_EQ(atomic_load(&stream->spatial_bits), bits);
        ASSERT_FLOAT_EQ(stream->position.e[0], 2.0f, 0.0f);
        ASSERT_FLOAT_EQ(stream->position.e[1], 0.0f, 0.0f);
        ASSERT_FLOAT_EQ(stream->position.e[2], 0.0f, 0.0f);
    }
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, 0u, 1.0f, 10.0f, 1.0f, 0.5f), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_position(NULL, h, vec3(2, 0, 0)), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 0.5f), AUDIO_STALE);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(2, 0, 0)), AUDIO_STALE);
    audio_system_destroy(as);
}

TEST(pcm_stream_spatial_gain_follows_distance_and_listener)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    /* not spatial: full gain wherever the listener is */
    audio_system_update(as, vec3(50, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f, 1e-6f);
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 0.5f), AUDIO_OK);
    /* at the origin, inside min distance: gain 1 */
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f, 1e-6f);
    /* d = 4: 1 / (1 + 1 * 3) */
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(4, 0, 0)), AUDIO_OK);
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f * 0.25f, 1e-6f);
    /* rolloff 2 at d = 4: 1 / (1 + 2 * 3) */
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 2.0f, 0.5f), AUDIO_OK);
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f / 7.0f, 1e-6f);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 0.5f), AUDIO_OK);
    /* beyond max distance: clamped at d = 10 */
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(0, 40, 0)), AUDIO_OK);
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f * 0.1f, 1e-6f);
    /* the listener moves next to the stream: the gain follows */
    audio_system_update(as, vec3(0, 38, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f * (1.0f / 2.0f), 1e-6f);
    /* a reopened slot starts without spatial settings */
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f, 1e-6f);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(4, 0, 0)), AUDIO_REJECTED);
    audio_system_destroy(as);
}

static bool g_stream_occluded;

static bool stream_occlusion_ray(void *user, Vec3 listener, Vec3 source)
{
    (void)user;
    (void)listener;
    (void)source;
    return g_stream_occluded;
}

TEST(pcm_stream_spatial_occlusion)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    audio_set_occlusion_ray_callback(as, stream_occlusion_ray, NULL);
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 0.25f), AUDIO_OK);
    g_stream_occluded = true;
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(2, 0, 0)), AUDIO_OK);
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f * 0.5f * 0.25f, 1e-6f);
    g_stream_occluded = false;
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(2, 0, 0)), AUDIO_OK);
    ASSERT_FLOAT_EQ(render_half(as, h), 0.5f * 0.5f, 1e-6f);
    audio_set_occlusion_ray_callback(as, NULL, NULL);
    audio_system_destroy(as);
}

/* both rendered samples of a stream holding the constant 0.5 */
static bool render_half_lr(AudioSystem *as, AudioPcmStreamHandle h, f32 *left, f32 *right)
{
    const i16 half[1] = {16384};
    u32 written = 0;
    f32 out[2];
    if (audio_pcm_stream_write_i16(as, h, half, 1u, &written) != AUDIO_OK || written != 1u) {
        return false;
    }
    if (audio_system_render(as, out, 1u) != AUDIO_OK) return false;
    *left = out[0];
    *right = out[1];
    /* ASSERT_FLOAT_EQ lets NaN through; a NaN pan must fail here */
    return isfinite(out[0]) && isfinite(out[1]);
}

static const f32 kCentre = 0.70710678f;

TEST(pcm_stream_panning_arguments)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, true), AUDIO_REJECTED);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, 0u, true), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_panning(NULL, h, true), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, true), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, true), AUDIO_STALE);
    audio_system_destroy(as);
}

/* listener at the origin facing -Z, up +Y: right is +X */
TEST(pcm_stream_panning_follows_the_source_side)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(2, 0, 0)), AUDIO_OK);
    /* spatial but not panned: both sides get the distance gain */
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f, 1e-6f);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, true), AUDIO_OK);
    /* hard right, distance gain 0.5 */
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f, 1e-6f);
    /* hard left */
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(-2, 0, 0)), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.0f, 1e-6f);
    /* straight ahead and straight behind: centre, -3 dB each */
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(0, 0, -2)), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f * kCentre, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f * kCentre, 1e-6f);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(0, 0, 2)), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f * kCentre, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f * kCentre, 1e-6f);
    /* 45 degrees front-right at distance sqrt(2): pan 1/sqrt(2) */
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(1, 0, -1)), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    {
        const double pi = 3.14159265358979323846;
        double gain = 1.0 / (1.0 + (sqrt(2.0) - 1.0));
        double theta = (1.0 / sqrt(2.0) + 1.0) * pi / 4.0;
        ASSERT_FLOAT_EQ(l, (f32)(0.5 * gain * cos(theta)), 1e-6f);
        ASSERT_FLOAT_EQ(r, (f32)(0.5 * gain * sin(theta)), 1e-6f);
        ASSERT_TRUE(r > l);
    }
    /* height does not pan: above the listener is centre */
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(0, 2, 0)), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f * kCentre, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f * kCentre, 1e-6f);
    audio_system_destroy(as);
}

TEST(pcm_stream_panning_follows_the_listener)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(0, 0, -2)), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, true), AUDIO_OK);
    /* the listener turns to face +X: the source at -Z is now on its left */
    audio_system_update(as, vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0));
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.0f, 1e-6f);
    /* the listener walks past it: the source is now on its right */
    audio_system_update(as, vec3(0, 0, -4), vec3(1, 0, 0), vec3(0, 1, 0));
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f, 1e-6f);
    /* forward parallel to up has no right vector: centre */
    audio_system_update(as, vec3(0, 0, -4), vec3(0, 1, 0), vec3(0, 1, 0));
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f * kCentre, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f * kCentre, 1e-6f);
    /* a source on the listener: centre, full gain */
    audio_system_update(as, vec3(0, 0, -2), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f * kCentre, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.5f * kCentre, 1e-6f);
    /* a rolled listener with non-unit vectors: forward -Z (length 3), up +X
     * (length 2), so right is -Y; the source 45 degrees down-front pans
     * half way right */
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, -3), vec3(2, 0, 0));
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(0, -1, -1)), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    {
        const double pi = 3.14159265358979323846;
        double gain = 1.0 / sqrt(2.0);
        double theta = (1.0 / sqrt(2.0) + 1.0) * pi / 4.0;
        ASSERT_FLOAT_EQ(l, (f32)(0.5 * gain * cos(theta)), 1e-6f);
        ASSERT_FLOAT_EQ(r, (f32)(0.5 * gain * sin(theta)), 1e-6f);
    }
    audio_system_destroy(as);
}

/* a stereo stream: each channel is scaled by its own side's gain */
TEST(pcm_stream_panning_scales_stereo_channels_by_side)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    ASSERT_EQ(audio_pcm_stream_open(as, 2u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(1, 0, -1)), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, true), AUDIO_OK);
    const i16 pcm[2] = {16384, 8192};
    u32 written = 0;
    f32 out[2];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 1u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    const double pi = 3.14159265358979323846;
    double gain = 1.0 / sqrt(2.0);
    double theta = (1.0 / sqrt(2.0) + 1.0) * pi / 4.0;
    ASSERT_FLOAT_EQ(out[0], (f32)(0.5 * gain * cos(theta)), 1e-6f);
    ASSERT_FLOAT_EQ(out[1], (f32)(0.25 * gain * sin(theta)), 1e-6f);
    audio_system_destroy(as);
}

TEST(pcm_stream_panning_off_and_reopen_restore_equal_gains)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(2, 0, 0)), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, true), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.0f, 1e-6f);
    /* new spatial settings keep panning on */
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 2.0f, 1.0f), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.5f / 3.0f, 1e-6f);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, false), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f / 3.0f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.5f / 3.0f, 1e-6f);
    /* a later position update stays unpanned */
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(2, 0, 0)), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f / 3.0f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.5f / 3.0f, 1e-6f);
    ASSERT_EQ(audio_pcm_stream_set_panning(as, h, true), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    /* the reopened slot is neither spatial nor panned */
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f, 0.0f);
    ASSERT_FLOAT_EQ(r, 0.5f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 1.0f, 10.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(2, 0, 0)), AUDIO_OK);
    ASSERT_TRUE(render_half_lr(as, h, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f, 1e-6f);
    audio_system_destroy(as);
}

/* one rendered frame; false when a sample is not finite */
static bool render_lr(AudioSystem *as, f32 *left, f32 *right)
{
    f32 out[2];
    if (audio_system_render(as, out, 1u) != AUDIO_OK) return false;
    *left = out[0];
    *right = out[1];
    return isfinite(out[0]) && isfinite(out[1]);
}

static AudioClipHandle register_ones(AudioSystem *as, u32 frames)
{
    static const f32 ones[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    return register_ramp(as, ones, frames);
}

TEST(event_panning_requires_spatial)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 2u));
    desc.panned = true;
    ASSERT_EQ(audio_event_register(as, "pan-flat", &desc), AUDIO_INVALID);
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "pan-flat", &desc), AUDIO_OK);
    audio_system_destroy(as);
}

TEST(panned_event_follows_the_source_and_the_listener)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 16u));
    desc.spatial = true;
    desc.panned = true;
    desc.looping = true;
    ASSERT_EQ(audio_event_register(as, "pan-loop", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_event_trigger(as, "pan-loop", vec3(2, 0, 0), &voice), AUDIO_OK);
    /* listener at the origin facing -Z: +X is hard right, distance gain 0.5 */
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.5f, 1e-6f);
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(-2, 0, 0)), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.0f, 1e-6f);
    /* facing +X the right vector is +Z: the source at -X is centred */
    audio_system_update(as, vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0));
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f * kCentre, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.5f * kCentre, 1e-6f);
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(0, 0, 4)), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f, 1e-6f);
    /* only the listener turns, to face -X: right is -Z, so +Z is hard left */
    audio_system_update(as, vec3(0, 0, 0), vec3(-1, 0, 0), vec3(0, 1, 0));
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.0f, 1e-6f);
    audio_system_destroy(as);
}

/* A RESTART's new pan never reaches PCM the old epoch still renders */
TEST(panned_event_restart_keeps_the_old_pan_on_held_pcm)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 2u));
    desc.spatial = true;
    desc.panned = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "pan-restart", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    f32 output[2];
    ASSERT_EQ(audio_event_trigger(as, "pan-restart", vec3(2, 0, 0), &handle), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(output[1], 0.5f, 1e-6f);
    ASSERT_EQ(audio_event_trigger(as, "pan-restart", vec3(-4, 0, 0), &handle), AUDIO_OK);
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(-8, 0, 0)), AUDIO_OK);
    AudioExtended *ext = (AudioExtended *)as->extended;
    AudioVoice *voice = &ext->voices[(handle & 0xFFu) - 1u];
    render_with_held_commands(voice, output);
    ASSERT_FLOAT_EQ(output[0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(output[1], 0.5f, 1e-6f);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.125f, 1e-6f);
    ASSERT_FLOAT_EQ(output[1], 0.0f, 1e-6f);
    audio_system_destroy(as);
}

/* The mixer takes a pan only together with the gain revision it belongs
 * to; a pan stored for a revision not yet published is not used. */
TEST(panned_event_keeps_its_pan_until_that_revision_is_published)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 16u));
    desc.spatial = true;
    desc.panned = true;
    desc.looping = true;
    ASSERT_EQ(audio_event_register(as, "pan-revision", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_event_trigger(as, "pan-revision", vec3(2, 0, 0), &handle), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(r, 0.5f, 1e-6f);
    AudioExtended *ext = (AudioExtended *)as->extended;
    AudioVoice *voice = &ext->voices[(handle & 0xFFu) - 1u];
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(-4, 0, 0)), AUDIO_OK);
    /* a later publish has stored its pan but not yet its gain */
    atomic_store(&voice->pan_snapshot, spatial_pack(voice->spatial_revision + 1u, -1.0f));
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f, 1e-6f);
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(-4, 0, 0)), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(r, 0.0f, 1e-6f);
    audio_system_destroy(as);
}

TEST(panned_event_scales_a_stereo_clip_by_side)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    const f32 samples[2] = {0.5f, 0.25f};
    AudioPcmDesc pcm = mono_pcm(samples, 1u);
    pcm.channels = 2u;
    AudioClipHandle clip = 0;
    ASSERT_EQ(audio_clip_register(as, "pan-stereo-clip", &pcm, &clip), AUDIO_OK);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.panned = true;
    ASSERT_EQ(audio_event_register(as, "pan-stereo", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_event_trigger(as, "pan-stereo", vec3(1, 0, -1), &voice), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    const double pi = 3.14159265358979323846;
    double gain = 1.0 / sqrt(2.0);
    double theta = (1.0 / sqrt(2.0) + 1.0) * pi / 4.0;
    ASSERT_FLOAT_EQ(l, (f32)(0.5 * gain * cos(theta)), 1e-6f);
    ASSERT_FLOAT_EQ(r, (f32)(0.25 * gain * sin(theta)), 1e-6f);
    audio_system_destroy(as);
}

/* ---- sinc resampling ---- */

static double ref_lanczos(double x)
{
    if (x == 0.0) return 1.0;
    const double pi = 3.14159265358979323846;
    double a = pi * x;
    double b = pi * x / 8.0;
    return sin(a) / a * (sin(b) / b);
}

/* Output k of a sinc stream holding frames[0..count) (interleaved, zero
 * before frame 0); NAN when the lookahead is not queued. */
static double ref_sinc_output(const double *frames, u32 count, u32 channels, u32 rate, u32 k,
                              u32 channel)
{
    u64 pos = (u64)k * rate;
    i64 index = (i64)(pos / AUDIO_PCM_SAMPLE_RATE);
    u64 rem = pos % AUDIO_PCM_SAMPLE_RATE;
    if (index + (i64)AUDIO_PCM_STREAM_SINC_LOOKAHEAD >= (i64)count) return NAN;
    if (rem == 0u) return frames[index * channels + channel];
    double f = (double)rem / (double)AUDIO_PCM_SAMPLE_RATE;
    double sum = 0.0;
    double weights = 0.0;
    for (i64 j = -7; j <= 8; ++j) {
        double w = ref_lanczos((double)j - f);
        i64 at = index + j;
        double x = at < 0 ? 0.0 : frames[at * channels + channel];
        sum += x * w;
        weights += w;
    }
    return sum / weights;
}

static void random_pcm(i16 *pcm, u32 samples, u32 seed)
{
    for (u32 i = 0; i < samples; ++i) {
        seed = seed * 1664525u + 1013904223u;
        pcm[i] = (i16)((i32)(seed >> 17) - 16384);
    }
}

static void pcm_to_double(const i16 *pcm, u32 samples, double *out)
{
    for (u32 i = 0; i < samples; ++i) out[i] = (double)pcm[i] / 32768.0;
}

static AudioPcmStreamHandle open_sinc_stream(AudioSystem *as, u32 channels, u32 rate)
{
    AudioPcmStreamHandle h = open_rate_stream(as, channels, rate);
    if (h == 0u || audio_pcm_stream_set_resample(as, h, AUDIO_RESAMPLE_SINC) != AUDIO_OK) {
        return 0u;
    }
    return h;
}

TEST(pcm_stream_resample_arguments)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(audio_pcm_stream_set_resample(as, h, (AudioResampleMode)2), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_resample(as, 0u, AUDIO_RESAMPLE_SINC), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_resample(NULL, h, AUDIO_RESAMPLE_SINC), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_resample(as, h, AUDIO_RESAMPLE_LINEAR), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_resample(as, h, AUDIO_RESAMPLE_SINC), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_resample(as, h, AUDIO_RESAMPLE_SINC), AUDIO_STALE);
    /* a reopened slot interpolates linearly: two frames play at once */
    h = open_rate_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    const i16 pcm[2] = {0, 3072};
    u32 written = 0;
    u64 under = 9u;
    f32 out[2u * 2u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 2u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 2u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[2], 3072.0f / 32768.0f / 3.0f, 1e-6f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 0u);
    audio_system_destroy(as);
}

TEST(pcm_stream_sinc_matches_the_lanczos_model)
{
    enum { kFrames = 200, kOut = 560 };
    static i16 pcm[kFrames];
    static double frames[kFrames];
    static f32 out[2u * kOut];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_sinc_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    random_pcm(pcm, kFrames, 777u);
    pcm_to_double(pcm, kFrames, frames);
    u32 written = 0;
    u64 under = 9u;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, kFrames, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kOut), AUDIO_OK);
    for (u32 k = 0; k < kOut; ++k) {
        double want = ref_sinc_output(frames, kFrames, 1u, 16000u, k, 0u);
        ASSERT_TRUE(isfinite(want));
        ASSERT_FLOAT_EQ(out[2u * k], (f32)want, 2e-6f);
        ASSERT_FLOAT_EQ(out[2u * k + 1u], (f32)want, 2e-6f);
    }
    /* sinc output is not the linear one */
    ASSERT_TRUE(fabs(out[2] - (frames[0] + (frames[1] - frames[0]) / 3.0)) > 1e-4);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 0u);
    audio_system_destroy(as);
}

/* An output needs AUDIO_PCM_STREAM_SINC_LOOKAHEAD frames past its position;
 * until then the stream underruns and the position waits. */
TEST(pcm_stream_sinc_waits_for_the_lookahead)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_sinc_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    i16 pcm[9];
    double frames[9];
    random_pcm(pcm, 9u, 4242u);
    pcm_to_double(pcm, 9u, frames);
    u32 written = 0;
    u64 under = 0;
    f32 out[2u * 3u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 8u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 1u);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm + 8u, 1u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 3u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], (f32)frames[0], 0.0f);
    for (u32 k = 1; k < 3u; ++k) {
        ASSERT_FLOAT_EQ(out[2u * k], (f32)ref_sinc_output(frames, 9u, 1u, 16000u, k, 0u), 2e-6f);
    }
    /* the next output sits past frame 0 and needs frame 9 */
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 0.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 2u);
    audio_system_destroy(as);
}

/* RMS error of a 4 kHz tone at 16 kHz against the ideal 48 kHz tone */
static double tone_error(AudioResampleMode mode)
{
    enum { kFrames = 600, kOut = 1500 };
    static i16 pcm[kFrames];
    static f32 out[2u * kOut];
    const double pi = 3.14159265358979323846;
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    if (!as) return -1.0;
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 16000u);
    double error = -1.0;
    u32 written = 0;
    for (u32 i = 0; i < kFrames; ++i) {
        pcm[i] = (i16)lrint(16384.0 * sin(2.0 * pi * 4000.0 * (double)i / 16000.0));
    }
    if (h != 0u && audio_pcm_stream_set_resample(as, h, mode) == AUDIO_OK &&
        audio_pcm_stream_write_i16(as, h, pcm, kFrames, &written) == AUDIO_OK &&
        audio_system_render(as, out, kOut) == AUDIO_OK) {
        double sum = 0.0;
        for (u32 k = 300u; k < kOut; ++k) {
            double ideal = 0.5 * sin(2.0 * pi * 4000.0 * (double)k / 48000.0);
            sum += (out[2u * k] - ideal) * (out[2u * k] - ideal);
        }
        error = sqrt(sum / (double)(kOut - 300u));
    }
    audio_system_destroy(as);
    return error;
}

TEST(pcm_stream_sinc_reconstructs_a_high_tone)
{
    double linear = tone_error(AUDIO_RESAMPLE_LINEAR);
    double sinc = tone_error(AUDIO_RESAMPLE_SINC);
    ASSERT_TRUE(linear > 0.05);
    ASSERT_TRUE(sinc >= 0.0 && sinc < 0.002);
}

/* a fast stream: the Butterworth low-pass, then the sinc kernel */
TEST(pcm_stream_sinc_after_the_downsampling_filter)
{
    enum { kFrames = 400, kOut = 200 };
    static i16 pcm[kFrames];
    static double filtered[kFrames];
    static f32 out[2u * kOut];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_sinc_stream(as, 1u, 88200u);
    ASSERT_NEQ(h, 0u);
    random_pcm(pcm, kFrames, 99u);
    ref_filter(pcm, kFrames, 1u, 88200u, filtered);
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, kFrames, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kOut), AUDIO_OK);
    for (u32 k = 0; k < kOut; ++k) {
        double want = ref_sinc_output(filtered, kFrames, 1u, 88200u, k, 0u);
        ASSERT_TRUE(isfinite(want));
        ASSERT_FLOAT_EQ(out[2u * k], (f32)want, 2e-6f);
    }
    audio_system_destroy(as);
}

TEST(pcm_stream_sinc_keeps_stereo_channels_apart)
{
    enum { kFrames = 100, kOut = 150 };
    static i16 pcm[2u * kFrames];
    static double frames[2u * kFrames];
    static f32 out[2u * kOut];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_sinc_stream(as, 2u, 24000u);
    ASSERT_NEQ(h, 0u);
    random_pcm(pcm, 2u * kFrames, 31337u);
    pcm_to_double(pcm, 2u * kFrames, frames);
    u32 written = 0;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, kFrames, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kOut), AUDIO_OK);
    for (u32 k = 0; k < kOut; ++k) {
        for (u32 c = 0; c < 2u; ++c) {
            double want = ref_sinc_output(frames, kFrames, 2u, 24000u, k, c);
            ASSERT_TRUE(isfinite(want));
            ASSERT_FLOAT_EQ(out[2u * k + c], (f32)want, 2e-6f);
        }
    }
    audio_system_destroy(as);
}

/* at the engine rate there is nothing to interpolate and no lookahead */
TEST(pcm_stream_sinc_at_the_engine_rate_is_unchanged)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_sinc_stream(as, 1u, AUDIO_PCM_SAMPLE_RATE);
    ASSERT_NEQ(h, 0u);
    const i16 pcm[4] = {8192, -8192, 4096, -4096};
    u32 written = 0;
    u64 under = 9u;
    f32 out[2u * 4u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, 4u, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 4u), AUDIO_OK);
    for (u32 i = 0; i < 4u; ++i) ASSERT_FLOAT_EQ(out[2u * i], (f32)pcm[i] / 32768.0f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_underruns(as, h, &under), AUDIO_OK);
    ASSERT_EQ(under, 0u);
    audio_system_destroy(as);
}

/* Frames played (and released) in linear mode are the sinc kernel's past
 * when the mode changes; a reopened slot's past is silence again. */
TEST(pcm_stream_sinc_history_survives_a_switch_and_resets_on_reopen)
{
    enum { kFrames = 20 };
    i16 pcm[kFrames];
    double frames[kFrames];
    random_pcm(pcm, kFrames, 2024u);
    pcm_to_double(pcm, kFrames, frames);
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_rate_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    u32 written = 0;
    u32 queued = 0;
    static f32 out[2u * 30u];
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, pcm, kFrames, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 30u), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_queued(as, h, &queued), AUDIO_OK);
    ASSERT_EQ(queued, 10u);
    ASSERT_EQ(audio_pcm_stream_set_resample(as, h, AUDIO_RESAMPLE_SINC), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 3u), AUDIO_OK);
    for (u32 k = 30u; k < 33u; ++k) {
        ASSERT_FLOAT_EQ(out[2u * (k - 30u)],
                        (f32)ref_sinc_output(frames, kFrames, 1u, 16000u, k, 0u), 2e-6f);
    }
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);

    i16 next[kFrames];
    double next_frames[kFrames];
    random_pcm(next, kFrames, 5u);
    pcm_to_double(next, kFrames, next_frames);
    h = open_sinc_stream(as, 1u, 16000u);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(audio_pcm_stream_write_i16(as, h, next, kFrames, &written), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, 30u), AUDIO_OK);
    for (u32 k = 0; k < 30u; ++k) {
        ASSERT_FLOAT_EQ(out[2u * k],
                        (f32)ref_sinc_output(next_frames, kFrames, 1u, 16000u, k, 0u), 2e-6f);
    }
    audio_system_destroy(as);
}

/* ---- rear cue ---- */

static double ref_rear_alpha(double behind)
{
    const double pi = 3.14159265358979323846;
    double rear = 1.0 - exp(-2.0 * pi * 5000.0 / 48000.0);
    return 1.0 - behind * (1.0 - rear);
}

/* a 48 kHz spatial mono stream inside min distance (gain 1, no pan) */
static AudioPcmStreamHandle open_cue_stream(AudioSystem *as, u32 channels, Vec3 position,
                                            bool cue)
{
    AudioPcmStreamHandle h = 0;
    if (audio_pcm_stream_open(as, channels, AUDIO_BUS_MASTER, 1.0f, &h) != AUDIO_OK ||
        audio_pcm_stream_set_spatial(as, h, 10.0f, 100.0f, 1.0f, 1.0f) != AUDIO_OK ||
        audio_pcm_stream_set_position(as, h, position) != AUDIO_OK ||
        (cue && audio_pcm_stream_set_rear_cue(as, h, true) != AUDIO_OK)) {
        return 0u;
    }
    return h;
}

static bool play_frames(AudioSystem *as, AudioPcmStreamHandle h, const i16 *pcm, u32 frames,
                        f32 *out)
{
    u32 written = 0;
    if (audio_pcm_stream_write_i16(as, h, pcm, frames, &written) != AUDIO_OK ||
        written != frames) {
        return false;
    }
    if (audio_system_render(as, out, frames) != AUDIO_OK) return false;
    for (u32 i = 0; i < 2u * frames; ++i) {
        if (!isfinite(out[i])) return false;
    }
    return true;
}

TEST(pcm_stream_rear_cue_arguments)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_rear_cue(as, h, true), AUDIO_REJECTED);
    ASSERT_EQ(audio_pcm_stream_set_rear_cue(as, 0u, true), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_rear_cue(NULL, h, true), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 10.0f, 100.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_rear_cue(as, h, true), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_rear_cue(as, h, false), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_rear_cue(as, h, true), AUDIO_STALE);
    audio_system_destroy(as);
}

TEST(pcm_stream_rear_cue_leaves_front_and_side_untouched)
{
    enum { kFrames = 64 };
    i16 pcm[kFrames];
    static f32 out[2u * kFrames];
    random_pcm(pcm, kFrames, 8080u);
    const Vec3 places[3] = {vec3(0, 0, -2), vec3(2, 0, 0), vec3(-1, 3, -1)};
    for (u32 p = 0; p < 3u; ++p) {
        AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
        ASSERT_NOT_NULL(as);
        AudioPcmStreamHandle h = open_cue_stream(as, 1u, places[p], true);
        ASSERT_NEQ(h, 0u);
        ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
        for (u32 i = 0; i < kFrames; ++i) {
            ASSERT_FLOAT_EQ(out[2u * i], (f32)pcm[i] / 32768.0f, 0.0f);
            ASSERT_FLOAT_EQ(out[2u * i + 1u], (f32)pcm[i] / 32768.0f, 0.0f);
        }
        /* no filter coefficient above 1 for a source in front */
        AudioPcmStream *stream = &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
        ASSERT_EQ(atomic_load(&stream->rear_alpha_bits), gain_to_bits(1.0f));
        audio_system_destroy(as);
    }
    /* a source on the listener has no direction: no filter, and no NaN */
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_cue_stream(as, 1u, vec3(0, 0, 0), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    for (u32 i = 0; i < kFrames; ++i) ASSERT_FLOAT_EQ(out[2u * i], (f32)pcm[i] / 32768.0f, 0.0f);
    {
        AudioPcmStream *stream = &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
        ASSERT_EQ(atomic_load(&stream->rear_alpha_bits), gain_to_bits(1.0f));
    }
    audio_system_destroy(as);
}

/* the step response of y += alpha (x - y), starting from 0 */
static void check_step(const f32 *out, u32 frames, u32 stride, double alpha, double level,
                       bool *ok)
{
    double y = 0.0;
    for (u32 i = 0; i < frames; ++i) {
        y += alpha * (level - y);
        if (fabs(out[stride * i] - y) > 2e-6) *ok = false;
    }
}

TEST(pcm_stream_rear_cue_filters_a_source_behind)
{
    enum { kFrames = 24 };
    i16 step[kFrames];
    static f32 out[2u * kFrames];
    for (u32 i = 0; i < kFrames; ++i) step[i] = 16384;
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_cue_stream(as, 1u, vec3(0, 0, 2), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, step, kFrames, out));
    bool ok = true;
    check_step(out, kFrames, 2u, ref_rear_alpha(1.0), 0.5, &ok);
    check_step(out + 1, kFrames, 2u, ref_rear_alpha(1.0), 0.5, &ok);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(out[0] < 0.3f);
    audio_system_destroy(as);

    /* 45 degrees behind and to the left: alpha blends by -cos(angle); the
     * forward vector need not be unit length */
    as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, -3), vec3(0, 1, 0));
    h = open_cue_stream(as, 1u, vec3(-2, 0, 2), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, step, kFrames, out));
    check_step(out, kFrames, 2u, ref_rear_alpha(1.0 / sqrt(2.0)), 0.5, &ok);
    ASSERT_TRUE(ok);
    /* turning the cue off passes the signal exactly again */
    ASSERT_EQ(audio_pcm_stream_set_rear_cue(as, h, false), AUDIO_OK);
    ASSERT_TRUE(play_frames(as, h, step, 2u, out));
    ASSERT_FLOAT_EQ(out[0], 0.5f, 0.0f);
    audio_system_destroy(as);
}

/* a +x, -x tone at the 24 kHz Nyquist rate: about a third behind */
TEST(pcm_stream_rear_cue_dulls_high_frequencies)
{
    enum { kFrames = 200 };
    i16 tone[kFrames];
    static f32 out[2u * kFrames];
    for (u32 i = 0; i < kFrames; ++i) tone[i] = (i & 1u) ? -16384 : 16384;
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_cue_stream(as, 1u, vec3(0, -1, 3), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, tone, kFrames, out));
    double rear = 1.0 - exp(-2.0 * 3.14159265358979323846 * 5000.0 / 48000.0);
    double behind = 3.0 / sqrt(10.0);
    double a = 1.0 - behind * (1.0 - rear);
    double steady = 0.5 * a / (2.0 - a);
    for (u32 k = kFrames - 50u; k < kFrames; ++k) {
        ASSERT_FLOAT_EQ(fabsf(out[2u * k]), (f32)steady, 1e-5f);
    }
    ASSERT_TRUE(steady < 0.2);
    audio_system_destroy(as);
}

/* the listener turns round: the source is now in front and the filter
 * stops at once, with no tail of the old state */
TEST(pcm_stream_rear_cue_follows_the_listener)
{
    enum { kFrames = 16 };
    i16 pcm[kFrames];
    static f32 out[2u * kFrames];
    random_pcm(pcm, kFrames, 1234u);
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_cue_stream(as, 1u, vec3(0, 0, 2), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    ASSERT_TRUE(fabsf(out[2u * (kFrames - 1u)] - (f32)pcm[kFrames - 1u] / 32768.0f) > 1e-3f);
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    for (u32 i = 0; i < kFrames; ++i) {
        ASSERT_FLOAT_EQ(out[2u * i], (f32)pcm[i] / 32768.0f, 0.0f);
    }
    /* the listener steps past it: behind again, filtered from the current
     * signal on (the state followed it) */
    audio_system_update(as, vec3(0, 0, 4), vec3(0, 0, 1), vec3(0, 1, 0));
    i16 step[4] = {16384, 16384, 16384, 16384};
    ASSERT_TRUE(play_frames(as, h, step, 4u, out));
    double a = ref_rear_alpha(1.0);
    double y = (double)pcm[kFrames - 1u] / 32768.0;
    for (u32 i = 0; i < 4u; ++i) {
        y += a * (0.5 - y);
        ASSERT_FLOAT_EQ(out[2u * i], (f32)y, 2e-6f);
        ASSERT_FLOAT_EQ(out[2u * i + 1u], (f32)y, 2e-6f);
    }
    audio_system_destroy(as);
}

TEST(pcm_stream_rear_cue_keeps_stereo_state_apart_and_resets_on_reopen)
{
    enum { kFrames = 12 };
    i16 pcm[2u * kFrames];
    static f32 out[2u * kFrames];
    for (u32 i = 0; i < kFrames; ++i) {
        pcm[2u * i] = 16384;
        pcm[2u * i + 1u] = -8192;
    }
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_cue_stream(as, 2u, vec3(0, 0, 2), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    bool ok = true;
    check_step(out, kFrames, 2u, ref_rear_alpha(1.0), 0.5, &ok);
    check_step(out + 1, kFrames, 2u, ref_rear_alpha(1.0), -0.25, &ok);
    ASSERT_TRUE(ok);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    /* the reopened slot has no coefficient left, even before set_spatial */
    ASSERT_EQ(audio_pcm_stream_open(as, 2u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_TRUE(play_frames(as, h, pcm, 2u, out));
    ASSERT_FLOAT_EQ(out[0], 0.5f, 0.0f);
    ASSERT_FLOAT_EQ(out[1], -0.25f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    /* and the cue off */
    h = open_cue_stream(as, 2u, vec3(0, 0, 2), false);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, pcm, 2u, out));
    ASSERT_FLOAT_EQ(out[0], 0.5f, 0.0f);
    ASSERT_FLOAT_EQ(out[1], -0.25f, 0.0f);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    /* and its filter starts from silence, not from the last stream */
    h = open_cue_stream(as, 2u, vec3(0, 0, 2), true);
    ASSERT_NEQ(h, 0u);
    {
        AudioPcmStream *stream = &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
        stream->rear_state[0] = 0.9f;
        stream->rear_state[1] = 0.9f;
        ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    }
    h = open_cue_stream(as, 2u, vec3(0, 0, 2), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    check_step(out, kFrames, 2u, ref_rear_alpha(1.0), 0.5, &ok);
    check_step(out + 1, kFrames, 2u, ref_rear_alpha(1.0), -0.25, &ok);
    ASSERT_TRUE(ok);
    audio_system_destroy(as);
}

/* ---- interaural delay ---- */

/* the model's delay of the far ear, in frames, for lateral amount |pan| */
static i32 ref_itd_frames(double lateral)
{
    double seconds = 0.0875 / 343.0 * (asin(lateral) + lateral);
    return (i32)lrint(seconds * 48000.0);
}

/* a 48 kHz spatial stream inside min distance (gain 1, no pan) */
static AudioPcmStreamHandle open_itd_stream(AudioSystem *as, u32 channels, Vec3 position,
                                            bool delay)
{
    AudioPcmStreamHandle h = 0;
    if (audio_pcm_stream_open(as, channels, AUDIO_BUS_MASTER, 1.0f, &h) != AUDIO_OK ||
        audio_pcm_stream_set_spatial(as, h, 10.0f, 100.0f, 1.0f, 1.0f) != AUDIO_OK ||
        audio_pcm_stream_set_position(as, h, position) != AUDIO_OK ||
        (delay && audio_pcm_stream_set_interaural_delay(as, h, true) != AUDIO_OK)) {
        return 0u;
    }
    return h;
}

static i32 published_itd(AudioSystem *as, AudioPcmStreamHandle h)
{
    AudioPcmStream *stream = &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
    return (i32)atomic_load(&stream->itd_frames);
}

/* out[2k + ear] is in[k - delay] (0 before the start), the other ear exact */
static bool check_delayed(const f32 *out, const i16 *pcm, u32 frames, u32 ear, u32 delay)
{
    for (u32 k = 0; k < frames; ++k) {
        f32 want = k < delay ? 0.0f : (f32)pcm[k - delay] / 32768.0f;
        f32 exact = (f32)pcm[k] / 32768.0f;
        if (out[2u * k + ear] != want || out[2u * k + (1u - ear)] != exact) return false;
    }
    return true;
}

TEST(pcm_stream_interaural_delay_arguments)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = 0;
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_interaural_delay(as, h, true), AUDIO_REJECTED);
    ASSERT_EQ(audio_pcm_stream_set_interaural_delay(as, 0u, true), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_interaural_delay(NULL, h, true), AUDIO_INVALID);
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 10.0f, 100.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_interaural_delay(as, h, true), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_interaural_delay(as, h, false), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_interaural_delay(as, h, true), AUDIO_STALE);
    audio_system_destroy(as);
}

TEST(pcm_stream_interaural_delay_leaves_the_median_plane_untouched)
{
    enum { kFrames = 48 };
    i16 pcm[kFrames];
    static f32 out[2u * kFrames];
    random_pcm(pcm, kFrames, 4242u);
    const Vec3 places[4] = {vec3(0, 0, -2), vec3(0, 0, 2), vec3(0, 2, 0), vec3(0, 0, 0)};
    for (u32 p = 0; p < 4u; ++p) {
        AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
        ASSERT_NOT_NULL(as);
        AudioPcmStreamHandle h = open_itd_stream(as, 1u, places[p], true);
        ASSERT_NEQ(h, 0u);
        ASSERT_EQ(published_itd(as, h), 0);
        ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
        ASSERT_TRUE(check_delayed(out, pcm, kFrames, 0u, 0u));
        audio_system_destroy(as);
    }
}

TEST(pcm_stream_interaural_delay_delays_the_far_ear)
{
    enum { kFrames = 80 };
    i16 pcm[kFrames];
    static f32 out[2u * kFrames];
    random_pcm(pcm, kFrames, 777u);
    ASSERT_EQ(ref_itd_frames(1.0), (i32)AUDIO_PCM_STREAM_ITD_MAX_FRAMES);
    /* straight right: the left ear is late */
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_itd_stream(as, 1u, vec3(2, 0, 0), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(published_itd(as, h), (i32)AUDIO_PCM_STREAM_ITD_MAX_FRAMES);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    ASSERT_TRUE(check_delayed(out, pcm, kFrames, 0u, AUDIO_PCM_STREAM_ITD_MAX_FRAMES));
    audio_system_destroy(as);
    /* straight left: the right ear is late */
    as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    h = open_itd_stream(as, 1u, vec3(-2, 0, 0), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(published_itd(as, h), -(i32)AUDIO_PCM_STREAM_ITD_MAX_FRAMES);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    ASSERT_TRUE(check_delayed(out, pcm, kFrames, 1u, AUDIO_PCM_STREAM_ITD_MAX_FRAMES));
    audio_system_destroy(as);
    /* 30 degrees right of ahead: |pan| = 0.5 */
    as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    h = open_itd_stream(as, 1u, vec3(1.0f, 0.0f, -1.7320508f), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(ref_itd_frames(0.5), 13);
    ASSERT_EQ(published_itd(as, h), 13);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    ASSERT_TRUE(check_delayed(out, pcm, kFrames, 0u, 13u));
    audio_system_destroy(as);
}

TEST(pcm_stream_interaural_delay_plays_history_and_follows_the_listener)
{
    enum { kFrames = 40 };
    i16 pcm[3u * kFrames];
    static f32 out[2u * kFrames];
    random_pcm(pcm, 3u * kFrames, 99u);
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_itd_stream(as, 1u, vec3(2, 0, 0), false);
    ASSERT_NEQ(h, 0u);
    ASSERT_EQ(published_itd(as, h), 0);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    ASSERT_TRUE(check_delayed(out, pcm, kFrames, 0u, 0u));
    /* turned on: the late ear plays frames already heard, not silence */
    ASSERT_EQ(audio_pcm_stream_set_interaural_delay(as, h, true), AUDIO_OK);
    ASSERT_TRUE(play_frames(as, h, pcm + kFrames, kFrames, out));
    for (u32 k = 0; k < kFrames; ++k) {
        ASSERT_FLOAT_EQ(out[2u * k],
                        (f32)pcm[kFrames + k - AUDIO_PCM_STREAM_ITD_MAX_FRAMES] / 32768.0f, 0.0f);
        ASSERT_FLOAT_EQ(out[2u * k + 1u], (f32)pcm[kFrames + k] / 32768.0f, 0.0f);
    }
    /* the listener turns to face the source: no delay */
    audio_system_update(as, vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0));
    ASSERT_EQ(published_itd(as, h), 0);
    ASSERT_TRUE(play_frames(as, h, pcm + 2u * kFrames, kFrames, out));
    ASSERT_TRUE(check_delayed(out, pcm + 2u * kFrames, kFrames, 0u, 0u));
    /* turned off: no delay wherever the source is */
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_EQ(published_itd(as, h), (i32)AUDIO_PCM_STREAM_ITD_MAX_FRAMES);
    ASSERT_EQ(audio_pcm_stream_set_interaural_delay(as, h, false), AUDIO_OK);
    ASSERT_EQ(published_itd(as, h), 0);
    audio_system_destroy(as);
}

TEST(pcm_stream_interaural_delay_keeps_stereo_ears_apart_and_resets_on_reopen)
{
    enum { kFrames = 48 };
    i16 pcm[2u * kFrames];
    static f32 out[2u * kFrames];
    random_pcm(pcm, 2u * kFrames, 5150u);
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmStreamHandle h = open_itd_stream(as, 2u, vec3(-2, 0, 0), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    for (u32 k = 0; k < kFrames; ++k) {
        f32 late = k < AUDIO_PCM_STREAM_ITD_MAX_FRAMES ? 0.0f :
            (f32)pcm[2u * (k - AUDIO_PCM_STREAM_ITD_MAX_FRAMES) + 1u] / 32768.0f;
        ASSERT_FLOAT_EQ(out[2u * k], (f32)pcm[2u * k] / 32768.0f, 0.0f);
        ASSERT_FLOAT_EQ(out[2u * k + 1u], late, 0.0f);
    }
    {
        AudioPcmStream *stream = &((AudioExtended *)as->extended)->pcm_streams[(h & 7u) - 1u];
        for (u32 i = 0; i < AUDIO_PCM_STREAM_ITD_LINE_FRAMES; ++i) {
            stream->itd_line[i][0] = 0.9f;
            stream->itd_line[i][1] = 0.9f;
        }
    }
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    /* the reopened slot has no delay, even before set_spatial */
    ASSERT_EQ(audio_pcm_stream_open(as, 2u, AUDIO_BUS_MASTER, 1.0f, &h), AUDIO_OK);
    ASSERT_EQ(published_itd(as, h), 0);
    /* nor once it is spatial again: the delay is off until asked for */
    ASSERT_EQ(audio_pcm_stream_set_spatial(as, h, 10.0f, 100.0f, 1.0f, 1.0f), AUDIO_OK);
    ASSERT_EQ(audio_pcm_stream_set_position(as, h, vec3(-2, 0, 0)), AUDIO_OK);
    ASSERT_EQ(published_itd(as, h), 0);
    ASSERT_EQ(audio_pcm_stream_close(as, h), AUDIO_OK);
    /* and its line starts from silence, not from the last stream */
    h = open_itd_stream(as, 2u, vec3(-2, 0, 0), true);
    ASSERT_NEQ(h, 0u);
    ASSERT_TRUE(play_frames(as, h, pcm, kFrames, out));
    for (u32 k = 0; k < AUDIO_PCM_STREAM_ITD_MAX_FRAMES; ++k) {
        ASSERT_FLOAT_EQ(out[2u * k + 1u], 0.0f, 0.0f);
    }
    audio_system_destroy(as);
}

/* ---- event rear cue ---- */

TEST(event_rear_cue_requires_spatial)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 2u));
    desc.rear_cue = true;
    ASSERT_EQ(audio_event_register(as, "rear-flat", &desc), AUDIO_INVALID);
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "rear-flat", &desc), AUDIO_OK);
    audio_system_destroy(as);
}

/* renders the whole clip of one triggered event */
static bool render_event_clip(const f32 *clip_pcm, u32 frames, Vec3 position, bool cue, f32 *out)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    if (!as) return false;
    AudioEventDesc desc = make_event_desc(register_ramp(as, clip_pcm, frames));
    desc.spatial = true;
    desc.rear_cue = cue;
    AudioVoiceHandle voice = 0;
    bool ok = audio_event_register(as, "rear-clip", &desc) == AUDIO_OK &&
              audio_event_trigger(as, "rear-clip", position, &voice) == AUDIO_OK &&
              audio_system_render(as, out, frames) == AUDIO_OK;
    audio_system_destroy(as);
    for (u32 i = 0; ok && i < 2u * frames; ++i) ok = isfinite(out[i]);
    return ok;
}

TEST(rear_cue_event_leaves_front_and_side_untouched)
{
    enum { kFrames = 64 };
    i16 pcm[kFrames];
    static f32 clip_pcm[kFrames];
    static f32 with_cue[2u * kFrames];
    static f32 without[2u * kFrames];
    random_pcm(pcm, kFrames, 4242u);
    for (u32 i = 0; i < kFrames; ++i) clip_pcm[i] = (f32)pcm[i] / 32768.0f;
    /* in front, to the side, and on the listener (no direction, no NaN) */
    const Vec3 places[3] = {vec3(0, 0, -2), vec3(2, 0, 0), vec3(0, 0, 0)};
    for (u32 p = 0; p < 3u; ++p) {
        ASSERT_TRUE(render_event_clip(clip_pcm, kFrames, places[p], true, with_cue));
        ASSERT_TRUE(render_event_clip(clip_pcm, kFrames, places[p], false, without));
        ASSERT_EQ(memcmp(with_cue, without, sizeof(with_cue)), 0);
    }
}

TEST(rear_cue_event_filters_a_source_behind)
{
    enum { kFrames = 16 };
    static const f32 ones[kFrames] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    static f32 out[2u * kFrames];
    /* straight behind at distance 2: gain 0.5, filtered from silence */
    ASSERT_TRUE(render_event_clip(ones, kFrames, vec3(0, 0, 2), true, out));
    bool ok = true;
    check_step(out, kFrames, 2u, ref_rear_alpha(1.0), 0.5, &ok);
    check_step(out + 1, kFrames, 2u, ref_rear_alpha(1.0), 0.5, &ok);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(out[0] < 0.3f);
    /* without the cue the same source is a plain 0.5 */
    ASSERT_TRUE(render_event_clip(ones, kFrames, vec3(0, 0, 2), false, out));
    for (u32 i = 0; i < 2u * kFrames; ++i) ASSERT_FLOAT_EQ(out[i], 0.5f, 0.0f);
}

TEST(rear_cue_event_follows_the_listener)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 16u));
    desc.spatial = true;
    desc.rear_cue = true;
    desc.looping = true;
    ASSERT_EQ(audio_event_register(as, "rear-loop", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_event_trigger(as, "rear-loop", vec3(0, 0, 2), &voice), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    double a = ref_rear_alpha(1.0);
    ASSERT_FLOAT_EQ(l, (f32)(a * 0.5), 2e-6f);
    ASSERT_FLOAT_EQ(r, (f32)(a * 0.5), 2e-6f);
    /* the listener turns round: the source is in front, the filter is off */
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f, 0.0f);
    ASSERT_FLOAT_EQ(r, 0.5f, 0.0f);
    /* the source moves behind again: the state followed the signal, so a
     * constant input is not dipped; the filter sits before the gain, so a
     * new distance gain applies at once */
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(0, 0, -2)), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f, 2e-6f);
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(0, 0, -4)), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.25f, 2e-6f);
    ASSERT_FLOAT_EQ(r, 0.25f, 2e-6f);
    /* turning the listener alone moves the source in front, then behind */
    AudioVoice *slot = &((AudioExtended *)as->extended)->voices[(voice & 0xFFu) - 1u];
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(slot->applied_rear_alpha, 1.0f, 0.0f);
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(slot->applied_rear_alpha, (f32)a, 1e-6f);
    audio_system_destroy(as);
}

/* A RESTART's new coefficient never reaches PCM the old epoch still renders */
TEST(rear_cue_event_restart_keeps_the_old_alpha_on_held_pcm)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 4u));
    desc.spatial = true;
    desc.rear_cue = true;
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "rear-restart", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    f32 output[2];
    ASSERT_EQ(audio_event_trigger(as, "rear-restart", vec3(0, 0, -2), &handle), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 0.0f);
    ASSERT_EQ(audio_event_trigger(as, "rear-restart", vec3(0, 0, 2), &handle), AUDIO_OK);
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(0, 0, 2)), AUDIO_OK);
    AudioExtended *ext = (AudioExtended *)as->extended;
    AudioVoice *voice = &ext->voices[(handle & 0xFFu) - 1u];
    render_with_held_commands(voice, output);
    ASSERT_FLOAT_EQ(output[0], 0.5f, 0.0f);
    ASSERT_FLOAT_EQ(output[1], 0.5f, 0.0f);
    /* the new epoch starts its filter from silence */
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], (f32)(ref_rear_alpha(1.0) * 0.5), 2e-6f);
    ASSERT_FLOAT_EQ(output[1], (f32)(ref_rear_alpha(1.0) * 0.5), 2e-6f);
    audio_system_destroy(as);
}

/* The mixer takes a coefficient only together with the gain revision it
 * belongs to; one stored for a revision not yet published is not used. */
TEST(rear_cue_event_keeps_its_alpha_until_that_revision_is_published)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 16u));
    desc.spatial = true;
    desc.rear_cue = true;
    desc.looping = true;
    ASSERT_EQ(audio_event_register(as, "rear-revision", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_event_trigger(as, "rear-revision", vec3(0, 0, 2), &handle), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    double a = ref_rear_alpha(1.0);
    double y = a * 0.5;
    ASSERT_FLOAT_EQ(l, (f32)y, 2e-6f);
    AudioExtended *ext = (AudioExtended *)as->extended;
    AudioVoice *voice = &ext->voices[(handle & 0xFFu) - 1u];
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(0, 0, -2)), AUDIO_OK);
    /* a later publish has stored its coefficient but not yet its gain */
    atomic_store(&voice->rear_snapshot, spatial_pack(voice->spatial_revision + 1u, 0.01f));
    ASSERT_TRUE(render_lr(as, &l, &r));
    y += a * (0.5 - y);
    ASSERT_FLOAT_EQ(l, (f32)y, 2e-6f);
    ASSERT_FLOAT_EQ(r, (f32)y, 2e-6f);
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(0, 0, -2)), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_FLOAT_EQ(l, 0.5f, 0.0f);
    ASSERT_FLOAT_EQ(r, 0.5f, 0.0f);
    audio_system_destroy(as);
}

TEST(rear_cue_event_keeps_stereo_state_apart)
{
    enum { kFrames = 12 };
    static f32 samples[2u * kFrames];
    static f32 out[2u * kFrames];
    for (u32 i = 0; i < kFrames; ++i) {
        samples[2u * i] = 0.5f;
        samples[2u * i + 1u] = -0.25f;
    }
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioPcmDesc pcm = mono_pcm(samples, kFrames);
    pcm.channels = 2u;
    AudioClipHandle clip = 0;
    ASSERT_EQ(audio_clip_register(as, "rear-stereo-clip", &pcm, &clip), AUDIO_OK);
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.rear_cue = true;
    ASSERT_EQ(audio_event_register(as, "rear-stereo", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "rear-stereo", vec3(0, 0, 2), &voice), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kFrames), AUDIO_OK);
    bool ok = true;
    check_step(out, kFrames, 2u, ref_rear_alpha(1.0), 0.25, &ok);
    check_step(out + 1, kFrames, 2u, ref_rear_alpha(1.0), -0.125, &ok);
    ASSERT_TRUE(ok);
    audio_system_destroy(as);
}

/* ---- event interaural delay ---- */

TEST(event_interaural_delay_requires_spatial)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = make_event_desc(register_ones(as, 2u));
    desc.interaural_delay = true;
    ASSERT_EQ(audio_event_register(as, "itd-flat", &desc), AUDIO_INVALID);
    desc.spatial = true;
    ASSERT_EQ(audio_event_register(as, "itd-flat", &desc), AUDIO_OK);
    audio_system_destroy(as);
}

/* a spatial event inside min distance (gain 1, no pan) */
static AudioEventDesc itd_event_desc(AudioClipHandle clip, bool delay)
{
    AudioEventDesc desc = make_event_desc(clip);
    desc.spatial = true;
    desc.min_distance = 10.0f;
    desc.interaural_delay = delay;
    return desc;
}

/* renders the whole clip of one triggered event */
static bool render_itd_event(const f32 *clip_pcm, u32 channels, u32 frames, Vec3 position,
                             bool delay, f32 *out)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    if (!as) return false;
    AudioPcmDesc pcm = mono_pcm(clip_pcm, frames);
    pcm.channels = channels;
    AudioClipHandle clip = 0;
    AudioEventDesc desc;
    AudioVoiceHandle voice = 0;
    bool ok = audio_clip_register(as, "itd-clip", &pcm, &clip) == AUDIO_OK;
    desc = itd_event_desc(clip, delay);
    ok = ok && audio_event_register(as, "itd-event", &desc) == AUDIO_OK &&
         audio_event_trigger(as, "itd-event", position, &voice) == AUDIO_OK &&
         audio_system_render(as, out, frames) == AUDIO_OK;
    audio_system_destroy(as);
    for (u32 i = 0; ok && i < 2u * frames; ++i) ok = isfinite(out[i]);
    return ok;
}

/* out[2k + ear] is clip[k - delay] (0 before the start), the other ear exact */
static bool check_event_delayed(const f32 *out, const f32 *clip, u32 frames, u32 ear, u32 delay)
{
    for (u32 k = 0; k < frames; ++k) {
        f32 want = k < delay ? 0.0f : clip[k - delay];
        if (out[2u * k + ear] != want || out[2u * k + (1u - ear)] != clip[k]) return false;
    }
    return true;
}

TEST(interaural_delay_event_delays_the_far_ear)
{
    enum { kFrames = 64 };
    i16 pcm[kFrames];
    static f32 clip[kFrames];
    static f32 with_delay[2u * kFrames];
    static f32 without[2u * kFrames];
    random_pcm(pcm, kFrames, 1357u);
    for (u32 i = 0; i < kFrames; ++i) clip[i] = (f32)pcm[i] / 32768.0f;
    ASSERT_TRUE(render_itd_event(clip, 1u, kFrames, vec3(2, 0, 0), true, with_delay));
    ASSERT_TRUE(check_event_delayed(with_delay, clip, kFrames, 0u,
                                    AUDIO_PCM_STREAM_ITD_MAX_FRAMES));
    ASSERT_TRUE(render_itd_event(clip, 1u, kFrames, vec3(-2, 0, 0), true, with_delay));
    ASSERT_TRUE(check_event_delayed(with_delay, clip, kFrames, 1u,
                                    AUDIO_PCM_STREAM_ITD_MAX_FRAMES));
    /* the cue off: no delay to the side */
    ASSERT_TRUE(render_itd_event(clip, 1u, kFrames, vec3(2, 0, 0), false, without));
    ASSERT_TRUE(check_event_delayed(without, clip, kFrames, 0u, 0u));
    /* in front, behind, above and on the listener: as with the cue off */
    const Vec3 places[4] = {vec3(0, 0, -2), vec3(0, 0, 2), vec3(0, 2, 0), vec3(0, 0, 0)};
    for (u32 p = 0; p < 4u; ++p) {
        ASSERT_TRUE(render_itd_event(clip, 1u, kFrames, places[p], true, with_delay));
        ASSERT_TRUE(render_itd_event(clip, 1u, kFrames, places[p], false, without));
        ASSERT_EQ(memcmp(with_delay, without, sizeof(with_delay)), 0);
    }
}

TEST(interaural_delay_event_plays_history_and_follows_the_listener)
{
    enum { kClip = 64, kFrames = 40 };
    i16 pcm[kClip];
    static f32 clip[kClip];
    static f32 out[2u * kFrames];
    random_pcm(pcm, kClip, 2468u);
    for (u32 i = 0; i < kClip; ++i) clip[i] = (f32)pcm[i] / 32768.0f;
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioClipHandle handle = register_ramp(as, clip, kClip);
    AudioEventDesc desc = itd_event_desc(handle, true);
    desc.looping = true;
    ASSERT_EQ(audio_event_register(as, "itd-loop", &desc), AUDIO_OK);
    AudioVoiceHandle voice = 0;
    ASSERT_EQ(audio_event_trigger(as, "itd-loop", vec3(0, 0, -2), &voice), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kFrames), AUDIO_OK);
    for (u32 k = 0; k < kFrames; ++k) {
        ASSERT_FLOAT_EQ(out[2u * k], clip[k], 0.0f);
        ASSERT_FLOAT_EQ(out[2u * k + 1u], clip[k], 0.0f);
    }
    /* moved to the right: the left ear plays frames already heard */
    ASSERT_EQ(audio_voice_set_position(as, voice, vec3(2, 0, 0)), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, out, kFrames), AUDIO_OK);
    for (u32 k = 0; k < kFrames; ++k) {
        u32 now = (kFrames + k) % kClip;
        u32 late = (kFrames + k - AUDIO_PCM_STREAM_ITD_MAX_FRAMES) % kClip;
        ASSERT_FLOAT_EQ(out[2u * k], clip[late], 0.0f);
        ASSERT_FLOAT_EQ(out[2u * k + 1u], clip[now], 0.0f);
    }
    /* the listener turns to face the source: no delay */
    audio_system_update(as, vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0));
    ASSERT_EQ(audio_system_render(as, out, kFrames), AUDIO_OK);
    for (u32 k = 0; k < kFrames; ++k) {
        u32 now = (2u * kFrames + k) % kClip;
        ASSERT_FLOAT_EQ(out[2u * k], clip[now], 0.0f);
        ASSERT_FLOAT_EQ(out[2u * k + 1u], clip[now], 0.0f);
    }
    /* turning back alone brings the delay back, on the right ear now */
    audio_system_update(as, vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));
    ASSERT_EQ(audio_system_render(as, out, 1u), AUDIO_OK);
    AudioVoice *slot = &((AudioExtended *)as->extended)->voices[(voice & 0xFFu) - 1u];
    ASSERT_EQ(slot->applied_itd, -(i32)AUDIO_PCM_STREAM_ITD_MAX_FRAMES);
    audio_system_destroy(as);
}

/* A RESTART's new count never reaches PCM the old epoch still renders, and
 * the new epoch's line starts from silence */
TEST(interaural_delay_event_restart_keeps_the_old_delay_on_held_pcm)
{
    enum { kClip = 8 };
    const f32 clip[kClip] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f};
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = itd_event_desc(register_ramp(as, clip, kClip), true);
    desc.retrigger = AUDIO_RETRIGGER_RESTART;
    ASSERT_EQ(audio_event_register(as, "itd-restart", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    f32 output[2];
    ASSERT_EQ(audio_event_trigger(as, "itd-restart", vec3(0, 0, -2), &handle), AUDIO_OK);
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.1f, 0.0f);
    ASSERT_EQ(audio_event_trigger(as, "itd-restart", vec3(2, 0, 0), &handle), AUDIO_OK);
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(2, 0, 0)), AUDIO_OK);
    AudioExtended *ext = (AudioExtended *)as->extended;
    AudioVoice *voice = &ext->voices[(handle & 0xFFu) - 1u];
    render_with_held_commands(voice, output);
    ASSERT_FLOAT_EQ(output[0], 0.2f, 0.0f);
    ASSERT_FLOAT_EQ(output[1], 0.2f, 0.0f);
    for (u32 i = 0; i < AUDIO_PCM_STREAM_ITD_LINE_FRAMES; ++i) {
        voice->itd_line[i][0] = 0.9f;
        voice->itd_line[i][1] = 0.9f;
    }
    ASSERT_EQ(audio_system_render(as, output, 1), AUDIO_OK);
    ASSERT_FLOAT_EQ(output[0], 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(output[1], 0.1f, 0.0f);
    audio_system_destroy(as);
}

/* The mixer takes a count only together with the gain revision it belongs
 * to; one stored for a revision not yet published is not used. */
TEST(interaural_delay_event_keeps_its_delay_until_that_revision_is_published)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    AudioEventDesc desc = itd_event_desc(register_ones(as, 16u), true);
    desc.looping = true;
    ASSERT_EQ(audio_event_register(as, "itd-revision", &desc), AUDIO_OK);
    AudioVoiceHandle handle = 0;
    f32 l = -1.0f, r = -1.0f;
    ASSERT_EQ(audio_event_trigger(as, "itd-revision", vec3(2, 0, 0), &handle), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    AudioVoice *voice = &((AudioExtended *)as->extended)->voices[(handle & 0xFFu) - 1u];
    ASSERT_EQ(voice->applied_itd, (i32)AUDIO_PCM_STREAM_ITD_MAX_FRAMES);
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(0, 0, -2)), AUDIO_OK);
    atomic_store(&voice->itd_snapshot, spatial_pack(voice->spatial_revision + 1u, 5.0f));
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_EQ(voice->applied_itd, (i32)AUDIO_PCM_STREAM_ITD_MAX_FRAMES);
    ASSERT_EQ(audio_voice_set_position(as, handle, vec3(0, 0, -2)), AUDIO_OK);
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_EQ(voice->applied_itd, 0);
    /* an event with the cue off ignores a stored count */
    AudioEventDesc flat = itd_event_desc(register_named_pcm(as, "itd-flat-pcm",
                                                            (const f32[]){1, 1, 1, 1}, 4u),
                                         false);
    flat.looping = true;
    ASSERT_EQ(audio_event_register(as, "itd-off", &flat), AUDIO_OK);
    AudioVoiceHandle off = 0;
    ASSERT_EQ(audio_event_trigger(as, "itd-off", vec3(2, 0, 0), &off), AUDIO_OK);
    AudioVoice *plain = &((AudioExtended *)as->extended)->voices[(off & 0xFFu) - 1u];
    ASSERT_TRUE(render_lr(as, &l, &r));
    /* a count stored under the very revision the mixer adopts next */
    {
        u32 next = plain->spatial_revision + 1u;
        atomic_store(&plain->itd_snapshot, spatial_pack(next, 9.0f));
        atomic_store(&plain->spatial_snapshot, spatial_pack(next, 1.0f));
        plain->spatial_revision = next;
    }
    ASSERT_TRUE(render_lr(as, &l, &r));
    ASSERT_EQ(plain->applied_spatial_revision, plain->spatial_revision);
    ASSERT_EQ(plain->applied_itd, 0);
    ASSERT_FLOAT_EQ(l, r, 0.0f);
    audio_system_destroy(as);
}

TEST(interaural_delay_event_delays_the_far_ears_own_channel)
{
    enum { kFrames = 48 };
    i16 pcm[2u * kFrames];
    static f32 clip[2u * kFrames];
    static f32 out[2u * kFrames];
    random_pcm(pcm, 2u * kFrames, 8642u);
    for (u32 i = 0; i < 2u * kFrames; ++i) clip[i] = (f32)pcm[i] / 32768.0f;
    ASSERT_TRUE(render_itd_event(clip, 2u, kFrames, vec3(-2, 0, 0), true, out));
    for (u32 k = 0; k < kFrames; ++k) {
        f32 late = k < AUDIO_PCM_STREAM_ITD_MAX_FRAMES ? 0.0f :
            clip[2u * (k - AUDIO_PCM_STREAM_ITD_MAX_FRAMES) + 1u];
        ASSERT_FLOAT_EQ(out[2u * k], clip[2u * k], 0.0f);
        ASSERT_FLOAT_EQ(out[2u * k + 1u], late, 0.0f);
    }
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
    RUN_TEST(pcm_stream_open_bounds_and_handles);
    RUN_TEST(pcm_stream_plays_mono_and_stereo_with_gain);
    RUN_TEST(pcm_stream_ring_is_bounded_and_underruns_play_silence);
    RUN_TEST(pcm_stream_ring_survives_counter_wraparound);
    RUN_TEST(pcm_stream_rate_bounds);
    RUN_TEST(pcm_stream_upsamples_16k_by_linear_interpolation);
    RUN_TEST(pcm_stream_rate_keeps_stereo_channels_apart);
    RUN_TEST(pcm_stream_downsamples_96k);
    RUN_TEST(pcm_stream_downsample_skips_a_frame_that_arrives_late);
    RUN_TEST(pcm_stream_downsample_88k2_interpolates_filtered_frames);
    RUN_TEST(pcm_stream_downsample_removes_the_nyquist_tone);
    RUN_TEST(pcm_stream_downsample_attenuates_content_above_24k);
    RUN_TEST(pcm_stream_downsample_keeps_the_audible_band);
    RUN_TEST(pcm_stream_downsample_filters_stereo_channels_apart);
    RUN_TEST(pcm_stream_reopen_resets_the_filter);
    RUN_TEST(pcm_stream_at_the_engine_rate_is_not_filtered);
    RUN_TEST(pcm_stream_rate_underrun_resumes_at_the_same_position);
    RUN_TEST(pcm_stream_reopen_starts_at_the_first_frame);
    RUN_TEST(pcm_stream_spatial_arguments);
    RUN_TEST(pcm_stream_spatial_gain_follows_distance_and_listener);
    RUN_TEST(pcm_stream_spatial_occlusion);
    RUN_TEST(spatial_event_and_stream_share_the_distance_model);
    RUN_TEST(pcm_stream_panning_arguments);
    RUN_TEST(pcm_stream_panning_follows_the_source_side);
    RUN_TEST(pcm_stream_panning_follows_the_listener);
    RUN_TEST(pcm_stream_panning_scales_stereo_channels_by_side);
    RUN_TEST(pcm_stream_panning_off_and_reopen_restore_equal_gains);
    RUN_TEST(event_panning_requires_spatial);
    RUN_TEST(panned_event_follows_the_source_and_the_listener);
    RUN_TEST(panned_event_restart_keeps_the_old_pan_on_held_pcm);
    RUN_TEST(panned_event_keeps_its_pan_until_that_revision_is_published);
    RUN_TEST(panned_event_scales_a_stereo_clip_by_side);
    RUN_TEST(pcm_stream_resample_arguments);
    RUN_TEST(pcm_stream_sinc_matches_the_lanczos_model);
    RUN_TEST(pcm_stream_sinc_waits_for_the_lookahead);
    RUN_TEST(pcm_stream_sinc_reconstructs_a_high_tone);
    RUN_TEST(pcm_stream_sinc_after_the_downsampling_filter);
    RUN_TEST(pcm_stream_sinc_keeps_stereo_channels_apart);
    RUN_TEST(pcm_stream_sinc_at_the_engine_rate_is_unchanged);
    RUN_TEST(pcm_stream_sinc_history_survives_a_switch_and_resets_on_reopen);
    RUN_TEST(pcm_stream_rear_cue_arguments);
    RUN_TEST(pcm_stream_rear_cue_leaves_front_and_side_untouched);
    RUN_TEST(pcm_stream_rear_cue_filters_a_source_behind);
    RUN_TEST(pcm_stream_rear_cue_dulls_high_frequencies);
    RUN_TEST(pcm_stream_rear_cue_follows_the_listener);
    RUN_TEST(pcm_stream_rear_cue_keeps_stereo_state_apart_and_resets_on_reopen);
    RUN_TEST(pcm_stream_interaural_delay_arguments);
    RUN_TEST(pcm_stream_interaural_delay_leaves_the_median_plane_untouched);
    RUN_TEST(pcm_stream_interaural_delay_delays_the_far_ear);
    RUN_TEST(pcm_stream_interaural_delay_plays_history_and_follows_the_listener);
    RUN_TEST(pcm_stream_interaural_delay_keeps_stereo_ears_apart_and_resets_on_reopen);
    RUN_TEST(event_rear_cue_requires_spatial);
    RUN_TEST(rear_cue_event_leaves_front_and_side_untouched);
    RUN_TEST(rear_cue_event_filters_a_source_behind);
    RUN_TEST(rear_cue_event_follows_the_listener);
    RUN_TEST(rear_cue_event_restart_keeps_the_old_alpha_on_held_pcm);
    RUN_TEST(rear_cue_event_keeps_its_alpha_until_that_revision_is_published);
    RUN_TEST(rear_cue_event_keeps_stereo_state_apart);
    RUN_TEST(event_interaural_delay_requires_spatial);
    RUN_TEST(interaural_delay_event_delays_the_far_ear);
    RUN_TEST(interaural_delay_event_plays_history_and_follows_the_listener);
    RUN_TEST(interaural_delay_event_restart_keeps_the_old_delay_on_held_pcm);
    RUN_TEST(interaural_delay_event_keeps_its_delay_until_that_revision_is_published);
    RUN_TEST(interaural_delay_event_delays_the_far_ears_own_channel);
TEST_MAIN_END()
