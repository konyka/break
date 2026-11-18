#include "test_framework.h"

#include "../apps/core_app/core_app_voice.h"

#include <audio/audio_extended.h>
#include <core/platform_thread.h>
#include <platform/time.h>

#include <math.h>
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

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_config_and_lifecycle);
    RUN_TEST(manual_packet_matches_independent_pipeline);
    RUN_TEST(queue_is_bounded_and_drains_after_stop);
    RUN_TEST(pump_waits_for_each_input);
    RUN_TEST(threaded_voice_produces_and_stops);
    RUN_TEST(worker_error_and_capture_backend_are_visible_while_running);
    RUN_TEST(a_capture_device_that_cannot_start_is_unavailable);
TEST_MAIN_END()
