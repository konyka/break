#include "test_framework.h"

#include "../apps/core_app/core_app_voice.h"

#include <audio/audio_extended.h>
#include <core/platform_thread.h>
#include <platform/time.h>
#include <runtime/runtime_bus.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VOICE_TEST_FRAMES CORE_APP_VOICE_FRAME_FRAMES

static const double kPi = 3.14159265358979323846;

static CoreAppVoiceConfig test_config(AudioSystem *playback)
{
    CoreAppVoiceConfig config;
    memset(&config, 0, sizeof(config));
    config.playback = playback;
    config.capture_backend = AUDIO_BACKEND_FAKE;
    config.aligner.tracker.sample_rate = 48000u;
    config.aligner.tracker.max_delay_frames = 64u;
    config.aligner.tracker.window_frames = 256u;
    config.aligner.tracker.min_abs_correlation = 0.2f;
    config.aligner.tracker.max_slew_frames_per_s = 100.0f;
    config.aligner.tracker.lock_count = 1u;
    config.aligner.tracker.hold_updates = 2u;
    config.aligner.update_period_frames = VOICE_TEST_FRAMES;
    config.processor = (AudioVoiceProcessorConfig){
        .echo = {48000u, 64u, 0.2f, 0.0f, 0.0f},
        .residual = {48000u, 0.0f, 6.0f, 5.0f, 20.0f, 60.0f, -60.0f, -40.0f, 20.0f},
        .noise = {48000u, 64u, 0.0f, 10.0f, -60.0f},
        .gate = {48000u, 1u, 6.0f, 0.0f, 5.0f, 20.0f, 10.0f, -80.0f},
        .agc = {48000u, 1u, -18.0f, 0.0f, 10.0f, 100.0f, -60.0f},
    };
    return config;
}

static CoreAppVoice *create_voice(const CoreAppVoiceConfig *config)
{
    CoreAppVoice *voice = NULL;
    if (core_app_voice_create(config, &voice) != BREAK_RUNTIME_OK) return NULL;
    return voice;
}

static AudioPcmStreamHandle open_reference_stream(AudioSystem *playback)
{
    AudioPcmStreamHandle stream = 0u;
    if (audio_pcm_stream_open(playback, 2u, AUDIO_BUS_MASTER, 1.0f, &stream) != AUDIO_OK) {
        return 0u;
    }
    return stream;
}

static void fill_capture(f32 *samples, u32 packet)
{
    for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) {
        const double t = (double)(packet * VOICE_TEST_FRAMES + i);
        samples[i] = (f32)(0.2 * sin(2.0 * kPi * 800.0 * t / 48000.0) +
                           0.02 * sin(2.0 * kPi * 2500.0 * t / 48000.0));
    }
}

static void drive_fake(CoreAppVoice *voice, AudioSystem *playback,
                       AudioPcmStreamHandle stream, const f32 *capture,
                       const i16 *stereo, f32 *rendered)
{
    ASSERT_EQ(core_app_voice_inject(voice, capture, VOICE_TEST_FRAMES), BREAK_RUNTIME_OK);
    u32 written = 0u;
    ASSERT_EQ(audio_pcm_stream_write_i16(playback, stream, stereo, VOICE_TEST_FRAMES, &written),
              AUDIO_OK);
    ASSERT_EQ(written, VOICE_TEST_FRAMES);
    ASSERT_EQ(audio_system_render(playback, rendered, VOICE_TEST_FRAMES), AUDIO_OK);
}

TEST(create_validates_config_and_lifecycle)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = NULL;
    ASSERT_EQ(core_app_voice_create(NULL, &voice), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_create(&config, NULL), BREAK_RUNTIME_INVALID);
    CoreAppVoiceConfig bad = config;
    bad.playback = NULL;
    ASSERT_EQ(core_app_voice_create(&bad, &voice), BREAK_RUNTIME_INVALID);
    bad = config;
    bad.aligner.tracker.sample_rate = 16000u;
    ASSERT_EQ(core_app_voice_create(&bad, &voice), BREAK_RUNTIME_INVALID);
    bad = config;
    bad.processor.gate.channels = 2u;
    ASSERT_EQ(core_app_voice_create(&bad, &voice), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(voice == NULL);
    ASSERT_EQ(core_app_voice_start(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_stop(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_pump(NULL, 1u), BREAK_RUNTIME_INVALID);

    voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_FALSE(core_app_voice_aligner_sinc(voice));
    ASSERT_EQ(core_app_voice_aligner_crossfade_frames(voice), 0u);
    ASSERT_FALSE(core_app_voice_aligner_sinc(NULL));
    ASSERT_EQ(core_app_voice_aligner_crossfade_frames(NULL), 0u);
    BreakVoiceFrame frame = {0};
    bool ready = true;
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(!ready);
    ASSERT_EQ(core_app_voice_pop(voice, NULL, &ready), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(!ready);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_stats(voice, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    f32 capture[240] = {0};
    f32 rendered[480];
    ASSERT_EQ(core_app_voice_inject(voice, capture, 240u), BREAK_RUNTIME_OK);
    ASSERT_EQ(audio_system_render(playback, rendered, 240u), AUDIO_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(!ready);
    ASSERT_EQ(core_app_voice_pump(voice, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    CoreAppVoiceStats stats = {0};
    ASSERT_EQ(core_app_voice_stats(voice, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.produced, 0u);
    ASSERT_EQ(stats.dropped, 0u);
    ASSERT_EQ(stats.capture_overruns, 0u);
    ASSERT_EQ(stats.reference_overruns, 0u);
    core_app_voice_destroy(voice);
    core_app_voice_destroy(NULL);
    audio_system_destroy(playback);
}

TEST(manual_packet_matches_independent_pipeline)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);

    f32 capture_f32[VOICE_TEST_FRAMES];
    i16 capture_i16[VOICE_TEST_FRAMES];
    i16 stereo_i16[VOICE_TEST_FRAMES * 2u];
    for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) {
        capture_f32[i] = (f32)(0.2 * sin(2.0 * kPi * 800.0 * i / 48000.0) +
                               0.02 * sin(2.0 * kPi * 2500.0 * i / 48000.0));
        capture_i16[i] = (i16)lrintf(capture_f32[i] * 32767.0f);
        stereo_i16[2u * i] = (i16)(1000 + (i32)(i % 100u));
        stereo_i16[2u * i + 1u] = (i16)(-2000 + (i32)(i % 80u));
    }
    capture_f32[0] = 0.25f;
    capture_i16[0] = (i16)lrintf(capture_f32[0] * 32767.0f);
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    drive_fake(voice, playback, stream, capture_f32, stereo_i16, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    i16 raw_reference[VOICE_TEST_FRAMES];
    for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) {
        f32 mono = 0.5f * (rendered[2u * i] + rendered[2u * i + 1u]);
        if (!isfinite(mono)) mono = 0.0f;
        if (mono > 1.0f) mono = 1.0f;
        if (mono < -1.0f) mono = -1.0f;
        raw_reference[i] = (i16)lrintf(mono * 32767.0f);
    }

    AudioVoiceAligner *aligner = NULL;
    AudioVoiceProcessor *processor = NULL;
    ASSERT_EQ(audio_voice_aligner_create(&config.aligner, &aligner), AUDIO_OK);
    ASSERT_EQ(audio_voice_processor_create(&config.processor, &processor), AUDIO_OK);
    i16 aligned[VOICE_TEST_FRAMES];
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, raw_reference, capture_i16, aligned,
                                               VOICE_TEST_FRAMES), AUDIO_OK);
    audio_voice_processor_process_i16(processor, aligned, capture_i16, VOICE_TEST_FRAMES);
    BreakVoiceFrame frame = {0};
    bool ready = false;
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(frame.sequence, 0u);
    ASSERT_EQ(frame.sample_rate, 48000u);
    ASSERT_EQ(frame.channels, 1u);
    ASSERT_EQ(frame.sample_count, VOICE_TEST_FRAMES);
    ASSERT_TRUE(memcmp(frame.samples, capture_i16, sizeof(capture_i16)) == 0);
    CoreAppVoiceStats stats = {0};
    ASSERT_EQ(core_app_voice_stats(voice, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.produced, 1u);
    ASSERT_EQ(stats.dropped, 0u);
    ASSERT_EQ(stats.capture_overruns, 0u);
    ASSERT_EQ(stats.reference_overruns, 0u);
    audio_voice_aligner_destroy(aligner);
    audio_voice_processor_destroy(processor);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

TEST(aligner_modes_match_an_independent_pipeline)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    CoreAppVoiceConfig config = test_config(playback);
    config.aligner_crossfade_frames = 48001u;
    CoreAppVoice *voice = NULL;
    ASSERT_EQ(core_app_voice_create(&config, &voice), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(voice == NULL);
    config.aligner_sinc = true;
    config.aligner_crossfade_frames = 480u;
    voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);

    AudioVoiceAligner *aligner = NULL;
    AudioVoiceProcessor *processor = NULL;
    ASSERT_EQ(audio_voice_aligner_create(&config.aligner, &aligner), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_set_sinc(aligner, true), AUDIO_OK);
    ASSERT_EQ(audio_voice_aligner_set_crossfade_frames(aligner, 480u), AUDIO_OK);
    ASSERT_EQ(audio_voice_processor_create(&config.processor, &processor), AUDIO_OK);
    for (u32 packet = 0u; packet < 6u; ++packet) {
        f32 capture_f32[VOICE_TEST_FRAMES];
        i16 capture_i16[VOICE_TEST_FRAMES];
        i16 stereo_i16[VOICE_TEST_FRAMES * 2u];
        for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) {
            const u32 t = packet * VOICE_TEST_FRAMES + i;
            const i16 played = (i16)(6000.0 * sin(2.0 * kPi * 700.0 * t / 48000.0) +
                                     (i32)((t * 2654435761u) >> 22) - 512);
            stereo_i16[2u * i] = played;
            stereo_i16[2u * i + 1u] = played;
            const u32 echo = t >= 20u ? t - 20u : 0u;
            capture_f32[i] = t >= 20u
                ? (f32)(0.1 * sin(2.0 * kPi * 700.0 * echo / 48000.0))
                : 0.0f;
            capture_i16[i] = (i16)lrintf(capture_f32[i] * 32767.0f);
        }
        f32 rendered[VOICE_TEST_FRAMES * 2u];
        drive_fake(voice, playback, stream, capture_f32, stereo_i16, rendered);
        ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
        i16 raw_reference[VOICE_TEST_FRAMES];
        for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) {
            f32 mono = 0.5f * (rendered[2u * i] + rendered[2u * i + 1u]);
            if (!isfinite(mono)) mono = 0.0f;
            if (mono > 1.0f) mono = 1.0f;
            if (mono < -1.0f) mono = -1.0f;
            raw_reference[i] = (i16)lrintf(mono * 32767.0f);
        }
        i16 aligned[VOICE_TEST_FRAMES];
        ASSERT_EQ(audio_voice_aligner_process_i16(aligner, raw_reference, capture_i16, aligned,
                                                   VOICE_TEST_FRAMES), AUDIO_OK);
        audio_voice_processor_process_i16(processor, aligned, capture_i16, VOICE_TEST_FRAMES);
        BreakVoiceFrame frame = {0};
        bool ready = false;
        ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
        ASSERT_TRUE(ready);
        ASSERT_TRUE(memcmp(frame.samples, capture_i16, sizeof(capture_i16)) == 0);
    }
    ASSERT_TRUE(audio_voice_aligner_locked(aligner));
    ASSERT_TRUE(fabs(audio_voice_aligner_delay(aligner) - 20.0) < 1.0);
    ASSERT_TRUE(core_app_voice_aligner_sinc(voice));
    ASSERT_EQ(core_app_voice_aligner_crossfade_frames(voice), 480u);
    audio_voice_aligner_destroy(aligner);
    audio_voice_processor_destroy(processor);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

TEST(queue_is_bounded_and_drains_after_stop)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    i16 stereo[VOICE_TEST_FRAMES * 2u] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    f32 capture[VOICE_TEST_FRAMES];
    for (u32 packet = 0u; packet < CORE_APP_VOICE_QUEUE_CAPACITY + 1u; ++packet) {
        fill_capture(capture, packet);
        drive_fake(voice, playback, stream, capture, stereo, rendered);
        ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    }
    CoreAppVoiceStats stats = {0};
    ASSERT_EQ(core_app_voice_stats(voice, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.produced, CORE_APP_VOICE_QUEUE_CAPACITY);
    ASSERT_EQ(stats.dropped, 1u);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < CORE_APP_VOICE_QUEUE_CAPACITY; ++i) {
        BreakVoiceFrame frame = {0};
        bool ready = false;
        ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
        ASSERT_TRUE(ready);
        ASSERT_EQ(frame.sequence, i);
    }
    BreakVoiceFrame frame = {0};
    bool ready = true;
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(!ready);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    fill_capture(capture, CORE_APP_VOICE_QUEUE_CAPACITY + 1u);
    drive_fake(voice, playback, stream, capture, stereo, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(frame.sequence, CORE_APP_VOICE_QUEUE_CAPACITY + 1u);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    ASSERT_EQ(audio_pcm_stream_close(playback, stream), AUDIO_OK);
    audio_system_destroy(playback);
}

TEST(pump_waits_for_each_input)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    f32 capture[VOICE_TEST_FRAMES] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    BreakVoiceFrame frame = {0};
    bool ready = true;
    ASSERT_EQ(core_app_voice_inject(voice, capture, VOICE_TEST_FRAMES), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(!ready);
    ASSERT_EQ(audio_system_render(playback, rendered, VOICE_TEST_FRAMES), AUDIO_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(frame.sequence, 0u);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);

    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(audio_system_render(playback, rendered, VOICE_TEST_FRAMES), AUDIO_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(!ready);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

TEST(threaded_voice_produces_and_stops)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    const BreakRuntimeError started = core_app_voice_start_threaded(voice);
    f32 capture[VOICE_TEST_FRAMES];
    fill_capture(capture, 0u);
    i16 stereo[VOICE_TEST_FRAMES * 2u] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    BreakVoiceFrame frame = {0};
    bool ready = false;
    BreakRuntimeError inject_result = BREAK_RUNTIME_OK;
    BreakRuntimeError pop_result = BREAK_RUNTIME_OK;
    AudioResult render_result = AUDIO_OK;
    BreakRuntimeError external_pump = BREAK_RUNTIME_OK;
    if (started == BREAK_RUNTIME_OK) {
        external_pump = core_app_voice_pump(voice, 1u);
        for (u32 attempt = 0u; attempt < 1000u && !ready; ++attempt) {
            inject_result = core_app_voice_inject(voice, capture, VOICE_TEST_FRAMES);
            u32 written = 0u;
            const AudioResult write_result = audio_pcm_stream_write_i16(
                playback, stream, stereo, VOICE_TEST_FRAMES, &written);
            render_result = audio_system_render(playback, rendered, VOICE_TEST_FRAMES);
            if (inject_result != BREAK_RUNTIME_OK || write_result != AUDIO_OK ||
                written != VOICE_TEST_FRAMES || render_result != AUDIO_OK) {
                break;
            }
            pop_result = core_app_voice_pop(voice, &frame, &ready);
            if (pop_result != BREAK_RUNTIME_OK) break;
            if (!ready) time_sleep_us(1000u);
        }
    }
    const BreakRuntimeError stopped = core_app_voice_stop(voice);
    ASSERT_EQ(started, BREAK_RUNTIME_OK);
    ASSERT_EQ(inject_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(render_result, AUDIO_OK);
    ASSERT_EQ(pop_result, BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(frame.sequence, 0u);
    ASSERT_EQ(frame.sample_count, VOICE_TEST_FRAMES);
    ASSERT_EQ(stopped, BREAK_RUNTIME_OK);
    ASSERT_EQ(external_pump, BREAK_RUNTIME_REJECTED);
    CoreAppVoiceStats stats = {0};
    ASSERT_EQ(core_app_voice_stats(voice, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.capture_overruns, 0u);
    ASSERT_EQ(stats.reference_overruns, 0u);
    core_app_voice_destroy(voice);
    ASSERT_EQ(audio_pcm_stream_close(playback, stream), AUDIO_OK);
    audio_system_destroy(playback);
}

TEST(worker_error_and_capture_backend_are_visible_while_running)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    ASSERT_EQ(core_app_voice_worker_error(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_STR_EQ(core_app_voice_capture_backend(NULL), "none");
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_STR_EQ(core_app_voice_capture_backend(voice), "fake");
    ASSERT_EQ(core_app_voice_simulate_capture_event(NULL, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_start_threaded(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_worker_error(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    BreakRuntimeError seen = BREAK_RUNTIME_OK;
    for (u32 attempt = 0u; attempt < 2000u && seen == BREAK_RUNTIME_OK; ++attempt) {
        seen = core_app_voice_worker_error(voice);
        if (seen == BREAK_RUNTIME_OK) time_sleep_us(1000u);
    }
    ASSERT_EQ(seen, BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_UNAVAILABLE);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

TEST(a_capture_device_that_cannot_start_is_unavailable)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(core_app_voice_start_threaded(voice), BREAK_RUNTIME_UNAVAILABLE);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

static CoreAppVoiceConfig recovery_config(AudioSystem *playback, u32 interval_ms,
                                          u32 max_failures)
{
    CoreAppVoiceConfig config = test_config(playback);
    config.reopen_interval_ms = interval_ms;
    config.max_reopen_failures = max_failures;
    return config;
}

static void voice_stats(CoreAppVoice *voice, CoreAppVoiceStats *out)
{
    memset(out, 0, sizeof(*out));
    ASSERT_EQ(core_app_voice_stats(voice, out), BREAK_RUNTIME_OK);
}

TEST(a_lost_capture_is_reopened_and_the_reference_backlog_dropped)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = recovery_config(playback, 0u, 3u);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    i16 stereo[VOICE_TEST_FRAMES * 2u] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    f32 capture[VOICE_TEST_FRAMES];
    fill_capture(capture, 0u);
    drive_fake(voice, playback, stream, capture, stereo, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    /* playback keeps rendering while nothing is captured */
    for (u32 i = 0u; i < 3u; ++i) {
        ASSERT_EQ(audio_system_render(playback, rendered, VOICE_TEST_FRAMES), AUDIO_OK);
    }
    ASSERT_TRUE(audio_reference_available(playback) >= 3u * VOICE_TEST_FRAMES);
    ASSERT_EQ(core_app_voice_pump(voice, 4u), BREAK_RUNTIME_OK);
    ASSERT_TRUE(audio_reference_available(playback) < VOICE_TEST_FRAMES);
    CoreAppVoiceStats stats;
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_recoveries, 1u);
    ASSERT_EQ(stats.capture_reopen_failures, 0u);
    fill_capture(capture, 1u);
    drive_fake(voice, playback, stream, capture, stereo, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    for (u32 sequence = 0u; sequence < 2u; ++sequence) {
        BreakVoiceFrame frame = {0};
        bool ready = false;
        ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
        ASSERT_TRUE(ready);
        ASSERT_EQ(frame.sequence, sequence);
    }
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    ASSERT_EQ(audio_pcm_stream_close(playback, stream), AUDIO_OK);
    audio_system_destroy(playback);
}

TEST(a_reopened_capture_processes_like_a_fresh_pipeline)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = recovery_config(playback, 0u, 3u);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    i16 stereo[VOICE_TEST_FRAMES * 2u] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    f32 capture[VOICE_TEST_FRAMES];
    fill_capture(capture, 0u);
    drive_fake(voice, playback, stream, capture, stereo, rendered);
    fill_capture(capture, 7u);
    for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) capture[i] *= 4.0f;
    drive_fake(voice, playback, stream, capture, stereo, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    /* the second packet is still captured but stale once the device is lost */
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 4u), BREAK_RUNTIME_OK);
    f32 fresh_f32[VOICE_TEST_FRAMES];
    i16 fresh_i16[VOICE_TEST_FRAMES];
    fill_capture(fresh_f32, 1u);
    for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) {
        fresh_i16[i] = (i16)lrintf(fresh_f32[i] * 32767.0f);
    }
    drive_fake(voice, playback, stream, fresh_f32, stereo, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    AudioVoiceAligner *aligner = NULL;
    AudioVoiceProcessor *processor = NULL;
    ASSERT_EQ(audio_voice_aligner_create(&config.aligner, &aligner), AUDIO_OK);
    ASSERT_EQ(audio_voice_processor_create(&config.processor, &processor), AUDIO_OK);
    const i16 silent[VOICE_TEST_FRAMES] = {0};
    i16 aligned[VOICE_TEST_FRAMES];
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, silent, fresh_i16, aligned,
                                               VOICE_TEST_FRAMES), AUDIO_OK);
    audio_voice_processor_process_i16(processor, aligned, fresh_i16, VOICE_TEST_FRAMES);
    BreakVoiceFrame frame = {0};
    bool ready = false;
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(frame.sequence, 0u);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(frame.sequence, 1u);
    ASSERT_TRUE(memcmp(frame.samples, fresh_i16, sizeof(fresh_i16)) == 0);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    audio_voice_aligner_destroy(aligner);
    audio_voice_processor_destroy(processor);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    ASSERT_EQ(audio_pcm_stream_close(playback, stream), AUDIO_OK);
    audio_system_destroy(playback);
}

TEST(a_playback_reopen_drops_capture_that_has_no_reference)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    i16 stereo[VOICE_TEST_FRAMES * 2u] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    f32 capture[VOICE_TEST_FRAMES];
    fill_capture(capture, 0u);
    drive_fake(voice, playback, stream, capture, stereo, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    /* the playback device is gone: capture keeps arriving, no reference */
    fill_capture(capture, 7u);
    for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) capture[i] *= 4.0f;
    ASSERT_EQ(core_app_voice_inject(voice, capture, VOICE_TEST_FRAMES), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(audio_system_simulate_event(playback, AUDIO_SYSTEM_EVENT_DEVICE_LOST), AUDIO_OK);
    ASSERT_EQ(audio_system_reopen(playback), AUDIO_OK);
    ASSERT_EQ(audio_system_recoveries(playback), 1u);
    f32 fresh_f32[VOICE_TEST_FRAMES];
    i16 fresh_i16[VOICE_TEST_FRAMES];
    fill_capture(fresh_f32, 1u);
    for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) {
        fresh_i16[i] = (i16)lrintf(fresh_f32[i] * 32767.0f);
    }
    drive_fake(voice, playback, stream, fresh_f32, stereo, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 4u), BREAK_RUNTIME_OK);
    AudioVoiceAligner *aligner = NULL;
    AudioVoiceProcessor *processor = NULL;
    ASSERT_EQ(audio_voice_aligner_create(&config.aligner, &aligner), AUDIO_OK);
    ASSERT_EQ(audio_voice_processor_create(&config.processor, &processor), AUDIO_OK);
    const i16 silent[VOICE_TEST_FRAMES] = {0};
    i16 aligned[VOICE_TEST_FRAMES];
    ASSERT_EQ(audio_voice_aligner_process_i16(aligner, silent, fresh_i16, aligned,
                                               VOICE_TEST_FRAMES), AUDIO_OK);
    audio_voice_processor_process_i16(processor, aligned, fresh_i16, VOICE_TEST_FRAMES);
    BreakVoiceFrame frame = {0};
    bool ready = false;
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(frame.sequence, 0u);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(frame.sequence, 1u);
    ASSERT_TRUE(memcmp(frame.samples, fresh_i16, sizeof(fresh_i16)) == 0);
    ASSERT_EQ(core_app_voice_pop(voice, &frame, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    CoreAppVoiceStats stats;
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.playback_recoveries, 1u);
    audio_voice_aligner_destroy(aligner);
    audio_voice_processor_destroy(processor);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    ASSERT_EQ(audio_pcm_stream_close(playback, stream), AUDIO_OK);
    audio_system_destroy(playback);
}

TEST(refused_reopens_are_retried_until_the_limit_of_consecutive_failures)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = recovery_config(playback, 0u, 3u);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    CoreAppVoiceStats stats;
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < 2u; ++i) {
        ASSERT_EQ(core_app_voice_simulate_capture_event(voice,
                                                        AUDIO_CAPTURE_EVENT_REOPEN_REFUSED),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_reopen_failures, 1u);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_reopen_failures, 2u);
    ASSERT_EQ(stats.capture_recoveries, 0u);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_recoveries, 1u);
    /* a recovery resets the consecutive count: three more refusals end it
     * on the third, not the first */
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < 3u; ++i) {
        ASSERT_EQ(core_app_voice_simulate_capture_event(voice,
                                                        AUDIO_CAPTURE_EVENT_REOPEN_REFUSED),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_UNAVAILABLE);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_reopen_failures, 5u);
    ASSERT_EQ(stats.capture_recoveries, 1u);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

TEST(reopen_attempts_wait_for_the_interval)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = recovery_config(playback, 10000u, 3u);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_REOPEN_REFUSED),
              BREAK_RUNTIME_OK);
    CoreAppVoiceStats stats;
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_reopen_failures, 1u);
    ASSERT_EQ(stats.capture_recoveries, 0u);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

TEST(the_worker_recovers_a_lost_capture_and_keeps_running)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = recovery_config(playback, 0u, 3u);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_EQ(core_app_voice_start_threaded(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    CoreAppVoiceStats stats;
    memset(&stats, 0, sizeof(stats));
    for (u32 attempt = 0u; attempt < 2000u && stats.capture_recoveries == 0u; ++attempt) {
        ASSERT_EQ(core_app_voice_stats(voice, &stats), BREAK_RUNTIME_OK);
        if (stats.capture_recoveries == 0u) time_sleep_us(1000u);
    }
    ASSERT_EQ(stats.capture_recoveries, 1u);
    ASSERT_EQ(core_app_voice_worker_error(voice), BREAK_RUNTIME_OK);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    f32 capture[VOICE_TEST_FRAMES];
    fill_capture(capture, 0u);
    i16 stereo[VOICE_TEST_FRAMES * 2u] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    const u64 produced_before = stats.produced;
    for (u32 attempt = 0u; attempt < 1000u && stats.produced == produced_before; ++attempt) {
        if (core_app_voice_inject(voice, capture, VOICE_TEST_FRAMES) != BREAK_RUNTIME_OK) break;
        u32 written = 0u;
        if (audio_pcm_stream_write_i16(playback, stream, stereo, VOICE_TEST_FRAMES,
                                       &written) != AUDIO_OK ||
            audio_system_render(playback, rendered, VOICE_TEST_FRAMES) != AUDIO_OK) {
            break;
        }
        ASSERT_EQ(core_app_voice_stats(voice, &stats), BREAK_RUNTIME_OK);
        if (stats.produced == produced_before) time_sleep_us(1000u);
    }
    ASSERT_TRUE(stats.produced > produced_before);
    ASSERT_EQ(core_app_voice_worker_error(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    ASSERT_EQ(audio_pcm_stream_close(playback, stream), AUDIO_OK);
    audio_system_destroy(playback);
}

TEST(a_named_capture_device_opens_and_an_unknown_name_is_rejected)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    CoreAppVoiceConfig config = recovery_config(playback, 0u, 3u);
    config.capture_backend = AUDIO_BACKEND_NULL;
    char name[64] = "NULL Capture Device";
    config.capture_device_name = name;
    CoreAppVoice *voice = NULL;
    ASSERT_EQ(core_app_voice_create(&config, &voice), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(voice);
    /* the voice keeps its own copy of the name */
    memset(name, 0, sizeof(name));
    char opened[128] = {0};
    ASSERT_TRUE(core_app_voice_capture_name(voice, opened, sizeof(opened)));
    ASSERT_STR_EQ(opened, "NULL Capture Device");
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    CoreAppVoiceStats stats;
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_recoveries, 1u);
    ASSERT_TRUE(core_app_voice_capture_name(voice, opened, sizeof(opened)));
    ASSERT_STR_EQ(opened, "NULL Capture Device");
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);

    voice = NULL;
    config.capture_device_name = "no such microphone";
    ASSERT_EQ(core_app_voice_create(&config, &voice), BREAK_RUNTIME_REJECTED);
    ASSERT_TRUE(voice == NULL);
    config.capture_backend = AUDIO_BACKEND_FAKE;
    config.capture_device_name = "fake";
    ASSERT_EQ(core_app_voice_create(&config, &voice), BREAK_RUNTIME_REJECTED);
    ASSERT_TRUE(voice == NULL);
    char long_name[200];
    memset(long_name, 'a', sizeof(long_name) - 1u);
    long_name[sizeof(long_name) - 1u] = '\0';
    config.capture_backend = AUDIO_BACKEND_NULL;
    config.capture_device_name = long_name;
    ASSERT_EQ(core_app_voice_create(&config, &voice), BREAK_RUNTIME_REJECTED);
    ASSERT_TRUE(voice == NULL);
    config.capture_device_name = "";
    ASSERT_EQ(core_app_voice_create(&config, &voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

static void pump_until_handled(CoreAppVoice *voice, u64 handled)
{
    CoreAppVoiceStats stats;
    for (u32 attempt = 0u; attempt < 4u; ++attempt) {
        ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
        voice_stats(voice, &stats);
        if (stats.capture_switches + stats.capture_switch_rejected +
                stats.capture_switch_failures >= handled) {
            return;
        }
    }
}

/* A started voice switches its capture device on the pumping thread: by
 * name, refused for a name no device has (the old device keeps capturing),
 * and back to the default. A loss afterwards reopens the switched name. */
TEST(a_running_voice_switches_its_capture_device)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    CoreAppVoiceConfig config = recovery_config(playback, 0u, 3u);
    config.capture_backend = AUDIO_BACKEND_NULL;
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_EQ(core_app_voice_request_capture_device(NULL, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_request_capture_device(voice, "NULL Capture Device"),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    char long_name[200];
    memset(long_name, 'a', sizeof(long_name) - 1u);
    long_name[sizeof(long_name) - 1u] = '\0';
    ASSERT_EQ(core_app_voice_request_capture_device(voice, long_name), BREAK_RUNTIME_REJECTED);

    ASSERT_EQ(core_app_voice_request_capture_device(voice, "NULL Capture Device"),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_request_capture_device(voice, NULL), BREAK_RUNTIME_OVERLOAD);
    pump_until_handled(voice, 1u);
    CoreAppVoiceStats stats;
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_switches, 1u);
    char opened[128] = {0};
    ASSERT_TRUE(core_app_voice_capture_name(voice, opened, sizeof(opened)));
    ASSERT_STR_EQ(opened, "NULL Capture Device");

    ASSERT_EQ(core_app_voice_request_capture_device(voice, "no such microphone"),
              BREAK_RUNTIME_OK);
    pump_until_handled(voice, 2u);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_switches, 1u);
    ASSERT_EQ(stats.capture_switch_rejected, 1u);
    ASSERT_TRUE(core_app_voice_capture_name(voice, opened, sizeof(opened)));
    ASSERT_STR_EQ(opened, "NULL Capture Device");

    /* the switched name is the one a loss reopens */
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_recoveries, 1u);
    ASSERT_TRUE(core_app_voice_capture_name(voice, opened, sizeof(opened)));
    ASSERT_STR_EQ(opened, "NULL Capture Device");

    ASSERT_EQ(core_app_voice_request_capture_device(voice, ""), BREAK_RUNTIME_OK);
    pump_until_handled(voice, 3u);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_switches, 2u);
    ASSERT_EQ(stats.capture_switch_rejected, 1u);
    ASSERT_EQ(stats.capture_switch_failures, 0u);
    ASSERT_EQ(core_app_voice_request_capture_device(voice, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_request_capture_device(voice, NULL), BREAK_RUNTIME_REJECTED);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

/* A FAKE capture has no named device: the switch is refused and the
 * capture keeps producing frames. */
TEST(a_fake_capture_refuses_a_named_switch_and_keeps_producing)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_request_capture_device(voice, "fake"), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    i16 stereo[VOICE_TEST_FRAMES * 2u] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    f32 capture[VOICE_TEST_FRAMES];
    fill_capture(capture, 0u);
    drive_fake(voice, playback, stream, capture, stereo, rendered);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    CoreAppVoiceStats stats;
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_switch_rejected, 1u);
    ASSERT_EQ(stats.capture_switches, 0u);
    ASSERT_EQ(stats.produced, 1u);
    /* the default switch is accepted on a FAKE capture */
    ASSERT_EQ(core_app_voice_request_capture_device(voice, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_switches, 1u);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    ASSERT_EQ(audio_pcm_stream_close(playback, stream), AUDIO_OK);
    audio_system_destroy(playback);
}

static CoreAppVoiceConfig drift_config(AudioSystem *playback, bool enabled)
{
    CoreAppVoiceConfig config = test_config(playback);
    config.reopen_interval_ms = 0u;
    config.max_reopen_failures = 3u;
    config.drift_enabled = enabled;
    config.drift.estimator.window_size = 32u;
    config.drift.estimator.min_abs_correlation = 0.5f;
    config.drift.estimator.max_abs_drift_ppm = 1000.0f;
    config.drift.min_samples = 32u;
    config.drift.max_correction_ppm = 300.0f;
    config.drift.gain = 0.5f;
    config.drift_observe_packets = 10u;
    return config;
}

#define DRIFT_TEST_PACKETS 4000u

/* Energy of the processed capture over the last quarter of a drifting run:
 * the capture is pure echo, so this is what echo cancellation left. */
static double g_residual_energy;

/* The playback device runs (1 - drift) times as fast as the capture device:
 * for every capture packet it renders that many times fewer (more, when the
 * drift is negative) reference frames, and the capture holds the rendered
 * reference on its own clock, `start_delay` frames late. Returns the stats
 * after DRIFT_TEST_PACKETS packets. */
static bool run_drifting_devices(CoreAppVoice *voice, AudioSystem *playback, double drift,
                                 double start_delay, CoreAppVoiceStats *out)
{
    g_residual_energy = 0.0;
    const u32 history_frames =
        (u32)((double)(DRIFT_TEST_PACKETS * VOICE_TEST_FRAMES) * (1.0 + fabs(drift)) + 16.0);
    f32 *history = (f32 *)calloc(history_frames, sizeof(f32));
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    bool ok = history != NULL && stream != 0u &&
              core_app_voice_start(voice) == BREAK_RUNTIME_OK;
    u32 seed = 0x5eed1234u;
    u32 rendered_total = 0u;
    for (u32 packet = 0u; ok && packet < DRIFT_TEST_PACKETS; ++packet) {
        const u32 target = (u32)floor((double)(packet + 1u) * VOICE_TEST_FRAMES * (1.0 - drift));
        const u32 frames = target - rendered_total;
        i16 stereo[VOICE_TEST_FRAMES * 2u + 4u];
        f32 rendered[VOICE_TEST_FRAMES * 2u + 4u];
        for (u32 i = 0u; i < frames; ++i) {
            seed = seed * 1664525u + 1013904223u;
            const i16 value = (i16)((i32)(seed >> 16) % 12000 - 6000);
            stereo[2u * i] = value;
            stereo[2u * i + 1u] = value;
        }
        u32 written = 0u;
        ok = audio_pcm_stream_write_i16(playback, stream, stereo, frames, &written) == AUDIO_OK &&
             written == frames && audio_system_render(playback, rendered, frames) == AUDIO_OK;
        for (u32 i = 0u; ok && i < frames; ++i) {
            history[rendered_total + i] = 0.5f * (rendered[2u * i] + rendered[2u * i + 1u]);
        }
        rendered_total = target;
        f32 capture[VOICE_TEST_FRAMES];
        for (u32 i = 0u; i < VOICE_TEST_FRAMES; ++i) {
            const double n = (double)(packet * VOICE_TEST_FRAMES + i);
            const double position = (1.0 - drift) * n - start_delay;
            if (position < 0.0) {
                capture[i] = 0.0f;
                continue;
            }
            const u32 whole = (u32)position;
            const double fraction = position - (double)whole;
            capture[i] = (f32)(0.5 * ((1.0 - fraction) * history[whole] +
                                      fraction * history[whole + 1u]));
        }
        ok = ok && core_app_voice_inject(voice, capture, VOICE_TEST_FRAMES) == BREAK_RUNTIME_OK &&
             core_app_voice_pump(voice, 2u) == BREAK_RUNTIME_OK;
        BreakVoiceFrame frame;
        bool ready = true;
        while (ok && ready) {
            ok = core_app_voice_pop(voice, &frame, &ready) == BREAK_RUNTIME_OK;
            if (!ok || !ready || packet < DRIFT_TEST_PACKETS * 3u / 4u) continue;
            for (u32 i = 0u; i < frame.sample_count; ++i) {
                g_residual_energy += (double)frame.samples[i] * frame.samples[i];
            }
        }
    }
    ok = ok && core_app_voice_stats(voice, out) == BREAK_RUNTIME_OK;
    if (stream != 0u) (void)audio_pcm_stream_close(playback, stream);
    free(history);
    return ok;
}

TEST(drift_between_the_devices_is_compensated)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = drift_config(playback, true);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    CoreAppVoiceStats stats;
    memset(&stats, 0, sizeof(stats));
    ASSERT_TRUE(run_drifting_devices(voice, playback, 100e-6, 10.0, &stats));
    const double compensated_residual = g_residual_energy;
    ASSERT_TRUE(stats.drift_corrections > 0u);
    ASSERT_TRUE(llabs((long long)stats.drift_correction_ppb - 100000ll) < 10000ll);
    ASSERT_TRUE(stats.produced > DRIFT_TEST_PACKETS - 20u);
    /* a reopened capture is a new clock: the ratio starts over */
    const u64 corrections = stats.drift_corrections;
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_recoveries, 1u);
    ASSERT_EQ(stats.drift_correction_ppb, 0);
    ASSERT_EQ(stats.drift_corrections, corrections);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);

    /* the same devices without compensation leave at least 6 dB more echo */
    const CoreAppVoiceConfig off = drift_config(playback, false);
    voice = create_voice(&off);
    ASSERT_NOT_NULL(voice);
    ASSERT_TRUE(run_drifting_devices(voice, playback, 100e-6, 10.0, &stats));
    ASSERT_TRUE(compensated_residual > 0.0);
    ASSERT_TRUE(g_residual_energy > 4.0 * compensated_residual);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

TEST(drift_compensation_off_leaves_the_reference_alone)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    CoreAppVoiceConfig config = drift_config(playback, false);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    CoreAppVoiceStats stats;
    memset(&stats, 0, sizeof(stats));
    ASSERT_TRUE(run_drifting_devices(voice, playback, 100e-6, 10.0, &stats));
    ASSERT_EQ(stats.drift_corrections, 0u);
    ASSERT_EQ(stats.drift_correction_ppb, 0);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);

    /* an enabled config the compensator refuses fails create */
    config = drift_config(playback, true);
    config.drift.gain = 0.0f;
    voice = NULL;
    ASSERT_EQ(core_app_voice_create(&config, &voice), BREAK_RUNTIME_INVALID);
    config = drift_config(playback, true);
    config.drift_observe_packets = 0u;
    ASSERT_EQ(core_app_voice_create(&config, &voice), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(voice == NULL);
    audio_system_destroy(playback);
}

/* A playback clock slower than the capture clock needs a ratio above 1,
 * where one raw read can fall a frame short of a packet. */
TEST(a_slower_playback_clock_is_compensated_without_failing)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = drift_config(playback, true);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    CoreAppVoiceStats stats;
    memset(&stats, 0, sizeof(stats));
    ASSERT_TRUE(run_drifting_devices(voice, playback, -200e-6, 60.0, &stats));
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    ASSERT_TRUE(stats.drift_corrections > 0u);
    ASSERT_TRUE(llabs((long long)stats.drift_correction_ppb + 200000ll) < 20000ll);
    ASSERT_TRUE(stats.produced > DRIFT_TEST_PACKETS - 20u);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

/* Compensation adds no latency: one packet of reference and capture is
 * enough for one packet of voice, as without it. */
TEST(drift_compensation_produces_each_packet_without_waiting)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = drift_config(playback, true);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    AudioPcmStreamHandle stream = open_reference_stream(playback);
    ASSERT_NEQ(stream, 0u);
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    i16 stereo[VOICE_TEST_FRAMES * 2u] = {0};
    f32 rendered[VOICE_TEST_FRAMES * 2u];
    f32 capture[VOICE_TEST_FRAMES];
    CoreAppVoiceStats stats;
    for (u32 packet = 0u; packet < 3u; ++packet) {
        fill_capture(capture, packet);
        drive_fake(voice, playback, stream, capture, stereo, rendered);
        ASSERT_EQ(core_app_voice_pump(voice, 4u), BREAK_RUNTIME_OK);
        voice_stats(voice, &stats);
        ASSERT_EQ(stats.produced, packet + 1u);
    }
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    ASSERT_EQ(audio_pcm_stream_close(playback, stream), AUDIO_OK);
    audio_system_destroy(playback);
}

/* A capture switch and a playback reopen are new clocks too. */
TEST(a_capture_switch_and_a_playback_reopen_reset_the_drift_ratio)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = drift_config(playback, true);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    CoreAppVoiceStats stats;
    memset(&stats, 0, sizeof(stats));
    ASSERT_TRUE(run_drifting_devices(voice, playback, 100e-6, 10.0, &stats));
    ASSERT_TRUE(stats.drift_correction_ppb != 0);
    ASSERT_EQ(core_app_voice_request_capture_device(voice, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.capture_switches, 1u);
    ASSERT_EQ(stats.drift_correction_ppb, 0);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);

    voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    ASSERT_TRUE(run_drifting_devices(voice, playback, 100e-6, 10.0, &stats));
    ASSERT_TRUE(stats.drift_correction_ppb != 0);
    ASSERT_EQ(audio_system_simulate_event(playback, AUDIO_SYSTEM_EVENT_DEVICE_LOST), AUDIO_OK);
    ASSERT_EQ(audio_system_reopen(playback), AUDIO_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    voice_stats(voice, &stats);
    ASSERT_EQ(stats.playback_recoveries, 1u);
    ASSERT_EQ(stats.drift_correction_ppb, 0);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    audio_system_destroy(playback);
}

/* ---- device events on the runtime bus ---- */

typedef struct {
    BreakRuntimeBus *bus;
    BreakRuntimeQueue *queue;
    u32 subscriber;
} EventFixture;

static bool events_open(EventFixture *f, u32 queue_capacity)
{
    BreakRuntimeQueueConfig qc = {queue_capacity, 0u};
    memset(f, 0, sizeof(*f));
    if (break_runtime_bus_create(&f->bus) != BREAK_RUNTIME_OK) return false;
    if (break_runtime_queue_create(&qc, &f->queue) != BREAK_RUNTIME_OK) return false;
    return true;
}

static bool events_subscribe(EventFixture *f)
{
    const u16 kind = CORE_APP_VOICE_EVENT_KIND;
    return break_runtime_bus_subscribe(f->bus, "owner", f->queue, &kind, 1u, &f->subscriber) ==
           BREAK_RUNTIME_OK;
}

static void events_close(EventFixture *f)
{
    if (f->bus && f->subscriber) (void)break_runtime_bus_unsubscribe(f->bus, f->subscriber);
    break_runtime_queue_destroy(f->queue);
    break_runtime_bus_destroy(f->bus);
}

/* Pops one event; false when the queue is empty. */
static bool next_event(EventFixture *f, CoreAppVoiceEvent *out)
{
    BreakRuntimeOwnedMessage *message = NULL;
    BreakRuntimeMessageView view;
    memset(&view, 0, sizeof(view));
    if (break_runtime_queue_poll(f->queue, &message) != BREAK_RUNTIME_OK || message == NULL) {
        return false;
    }
    bool ok = break_runtime_message_view(message, &view) == BREAK_RUNTIME_OK &&
              view.kind == CORE_APP_VOICE_EVENT_KIND &&
              view.version == CORE_APP_VOICE_EVENT_VERSION &&
              (view.flags & BREAK_RUNTIME_MESSAGE_FLAG_CONTROL) != 0u &&
              core_app_voice_event_decode(view.data, view.size, out);
    break_runtime_message_release(message);
    return ok;
}

TEST(device_events_are_published_on_the_bus)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    CoreAppVoiceConfig config = recovery_config(playback, 0u, 3u);
    config.capture_backend = AUDIO_BACKEND_NULL;
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    EventFixture f;
    ASSERT_TRUE(events_open(&f, 16u));
    ASSERT_EQ(core_app_voice_attach_bus(NULL, f.bus), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_attach_bus(voice, f.bus), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_attach_bus(voice, f.bus), BREAK_RUNTIME_OK); /* idempotent */
    ASSERT_TRUE(events_subscribe(&f));
    ASSERT_EQ(core_app_voice_start(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_attach_bus(voice, NULL), BREAK_RUNTIME_REJECTED);

    CoreAppVoiceEvent event = {0u, 0u, 0u};
    ASSERT_FALSE(next_event(&f, &event)); /* nothing happened yet */
    /* a refused reopen, then a recovery */
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_REOPEN_REFUSED),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_TRUE(next_event(&f, &event));
    ASSERT_EQ(event.type, (u32)CORE_APP_VOICE_EVENT_CAPTURE_REOPEN_FAILED);
    ASSERT_EQ(event.count, 1u);
    ASSERT_TRUE(next_event(&f, &event));
    ASSERT_EQ(event.type, (u32)CORE_APP_VOICE_EVENT_CAPTURE_RECOVERED);
    ASSERT_EQ(event.count, 1u);
    /* switches: accepted, refused */
    ASSERT_EQ(core_app_voice_request_capture_device(voice, "NULL Capture Device"),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_request_capture_device(voice, "no such microphone"),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_TRUE(next_event(&f, &event));
    ASSERT_EQ(event.type, (u32)CORE_APP_VOICE_EVENT_CAPTURE_SWITCHED);
    ASSERT_EQ(event.count, 1u);
    ASSERT_TRUE(next_event(&f, &event));
    ASSERT_EQ(event.type, (u32)CORE_APP_VOICE_EVENT_CAPTURE_SWITCH_REJECTED);
    ASSERT_EQ(event.count, 1u);
    /* a playback reopen */
    ASSERT_EQ(audio_system_simulate_event(playback, AUDIO_SYSTEM_EVENT_DEVICE_LOST), AUDIO_OK);
    ASSERT_EQ(audio_system_reopen(playback), AUDIO_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_TRUE(next_event(&f, &event));
    ASSERT_EQ(event.type, (u32)CORE_APP_VOICE_EVENT_PLAYBACK_RECOVERED);
    ASSERT_EQ(event.count, 1u);
    /* giving up: three refusals in a row */
    ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
              BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < 3u; ++i) {
        ASSERT_EQ(core_app_voice_simulate_capture_event(voice,
                                                        AUDIO_CAPTURE_EVENT_REOPEN_REFUSED),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_UNAVAILABLE);
    for (u64 n = 2u; n <= 4u; ++n) {
        ASSERT_TRUE(next_event(&f, &event));
        ASSERT_EQ(event.type, (u32)CORE_APP_VOICE_EVENT_CAPTURE_REOPEN_FAILED);
        ASSERT_EQ(event.count, n);
    }
    ASSERT_TRUE(next_event(&f, &event));
    ASSERT_EQ(event.type, (u32)CORE_APP_VOICE_EVENT_CAPTURE_UNAVAILABLE);
    ASSERT_EQ(event.count, 0u);
    /* the repeated UNAVAILABLE pump does not repeat the event */
    ASSERT_EQ(core_app_voice_pump(voice, 1u), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_FALSE(next_event(&f, &event));
    CoreAppVoiceEventStats es;
    ASSERT_EQ(core_app_voice_event_stats(voice, &es), BREAK_RUNTIME_OK);
    ASSERT_EQ(es.published, 9u);
    ASSERT_EQ(es.undelivered, 0u);
    ASSERT_EQ(core_app_voice_event_stats(NULL, &es), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_attach_bus(voice, NULL), BREAK_RUNTIME_OK);
    core_app_voice_destroy(voice);
    events_close(&f);
    audio_system_destroy(playback);
}

TEST(device_events_never_block_the_pumping_thread)
{
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = recovery_config(playback, 0u, 1000u);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    EventFixture f;
    ASSERT_TRUE(events_open(&f, 2u));
    ASSERT_EQ(core_app_voice_attach_bus(voice, f.bus), BREAK_RUNTIME_OK);
    ASSERT_TRUE(events_subscribe(&f));
    /* a subscriber that never drains: the worker keeps running */
    ASSERT_EQ(core_app_voice_start_threaded(voice), BREAK_RUNTIME_OK);
    CoreAppVoiceStats stats;
    memset(&stats, 0, sizeof(stats));
    for (u32 round = 0u; round < 5u; ++round) {
        const u64 before = stats.capture_recoveries;
        ASSERT_EQ(core_app_voice_simulate_capture_event(voice, AUDIO_CAPTURE_EVENT_DEVICE_LOST),
                  BREAK_RUNTIME_OK);
        for (u32 attempt = 0u; attempt < 2000u && stats.capture_recoveries == before; ++attempt) {
            ASSERT_EQ(core_app_voice_stats(voice, &stats), BREAK_RUNTIME_OK);
            if (stats.capture_recoveries == before) time_sleep_us(1000u);
        }
        ASSERT_EQ(stats.capture_recoveries, before + 1u);
    }
    ASSERT_EQ(core_app_voice_worker_error(voice), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_stop(voice), BREAK_RUNTIME_OK);
    CoreAppVoiceEventStats es;
    ASSERT_EQ(core_app_voice_event_stats(voice, &es), BREAK_RUNTIME_OK);
    ASSERT_EQ(es.published, 2u);
    ASSERT_EQ(es.undelivered, 3u);
    CoreAppVoiceEvent event = {0u, 0u, 0u};
    ASSERT_TRUE(next_event(&f, &event));
    ASSERT_EQ(event.count, 1u);
    ASSERT_TRUE(next_event(&f, &event));
    ASSERT_EQ(event.count, 2u);
    ASSERT_FALSE(next_event(&f, &event));
    core_app_voice_destroy(voice);
    events_close(&f);
    audio_system_destroy(playback);
}

TEST(event_payloads_decode_strictly_and_kinds_must_match)
{
    u8 bytes[CORE_APP_VOICE_EVENT_SIZE] = {5, 0, 0, 0, 0, 0, 0, 0, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
    CoreAppVoiceEvent event = {0u, 0u, 0u};
    ASSERT_TRUE(core_app_voice_event_decode(bytes, sizeof(bytes), &event));
    ASSERT_EQ(event.type, 5u);
    ASSERT_EQ(event.count, 0x0102030405060708ull);
    ASSERT_FALSE(core_app_voice_event_decode(bytes, sizeof(bytes) - 1u, &event));
    ASSERT_FALSE(core_app_voice_event_decode(NULL, sizeof(bytes), &event));
    ASSERT_FALSE(core_app_voice_event_decode(bytes, sizeof(bytes), NULL));
    bytes[0] = 0u;
    ASSERT_FALSE(core_app_voice_event_decode(bytes, sizeof(bytes), &event));
    bytes[0] = 8u;
    ASSERT_FALSE(core_app_voice_event_decode(bytes, sizeof(bytes), &event));
    bytes[0] = 1u;
    bytes[4] = 1u; /* reserved must be zero */
    ASSERT_FALSE(core_app_voice_event_decode(bytes, sizeof(bytes), &event));

    /* a bus that already has the kind with other parameters is refused */
    AudioSystem *playback = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(playback);
    const CoreAppVoiceConfig config = test_config(playback);
    CoreAppVoice *voice = create_voice(&config);
    ASSERT_NOT_NULL(voice);
    BreakRuntimeBus *bus = NULL;
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OK);
    BreakRuntimeBusKind other;
    memset(&other, 0, sizeof(other));
    other.kind = CORE_APP_VOICE_EVENT_KIND;
    other.max_version = 1u;
    other.max_payload = 8u;
    other.name = "something.else";
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &other), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_attach_bus(voice, bus), BREAK_RUNTIME_REJECTED);
    core_app_voice_destroy(voice);
    break_runtime_bus_destroy(bus);
    audio_system_destroy(playback);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_config_and_lifecycle);
    RUN_TEST(manual_packet_matches_independent_pipeline);
    RUN_TEST(queue_is_bounded_and_drains_after_stop);
    RUN_TEST(pump_waits_for_each_input);
    RUN_TEST(threaded_voice_produces_and_stops);
    RUN_TEST(worker_error_and_capture_backend_are_visible_while_running);
    RUN_TEST(a_capture_device_that_cannot_start_is_unavailable);
    RUN_TEST(a_lost_capture_is_reopened_and_the_reference_backlog_dropped);
    RUN_TEST(a_reopened_capture_processes_like_a_fresh_pipeline);
    RUN_TEST(a_playback_reopen_drops_capture_that_has_no_reference);
    RUN_TEST(refused_reopens_are_retried_until_the_limit_of_consecutive_failures);
    RUN_TEST(reopen_attempts_wait_for_the_interval);
    RUN_TEST(the_worker_recovers_a_lost_capture_and_keeps_running);
    RUN_TEST(a_named_capture_device_opens_and_an_unknown_name_is_rejected);
    RUN_TEST(a_running_voice_switches_its_capture_device);
    RUN_TEST(a_fake_capture_refuses_a_named_switch_and_keeps_producing);
    RUN_TEST(drift_between_the_devices_is_compensated);
    RUN_TEST(drift_compensation_off_leaves_the_reference_alone);
    RUN_TEST(a_slower_playback_clock_is_compensated_without_failing);
    RUN_TEST(a_capture_switch_and_a_playback_reopen_reset_the_drift_ratio);
    RUN_TEST(drift_compensation_produces_each_packet_without_waiting);
    RUN_TEST(device_events_are_published_on_the_bus);
    RUN_TEST(device_events_never_block_the_pumping_thread);
    RUN_TEST(event_payloads_decode_strictly_and_kinds_must_match);
    RUN_TEST(aligner_modes_match_an_independent_pipeline);
TEST_MAIN_END()
