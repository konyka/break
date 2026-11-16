/* Network voice reaches the mixer: BRV1 frames go through the real
 * break_online_voice receiver (reorder, jitter delay) and are written into
 * an audio PCM stream; the FAKE backend renders what a device would play. */
#include "test_framework.h"

#include <audio/audio_extended.h>
#include <core/log.h>
#include <network/break_online_voice.h>

#include <core/platform_thread.h>

#include <stdatomic.h>
#include <string.h>

void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    (void)level; (void)file; (void)line; (void)fmt;
}

#define VOICE_RATE 48000u
#define VOICE_SAMPLES 480u /* 10 ms of mono at 48 kHz */

static BreakRuntimeError push_voice_frame_at(BreakVoiceReceiver *receiver, u32 rate,
                                            u16 samples, u32 sequence, i16 base)
{
    BreakVoiceFrame frame;
    u8 wire[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0;
    memset(&frame, 0, sizeof(frame));
    frame.sequence = sequence;
    frame.sample_rate = rate;
    frame.channels = 1u;
    frame.sample_count = samples;
    for (u32 i = 0; i < samples; ++i) frame.samples[i] = (i16)(base + (i16)i);
    BreakRuntimeError e = break_voice_encode(&frame, wire, sizeof(wire), &size);
    if (e != BREAK_RUNTIME_OK) return e;
    return break_voice_receiver_push(receiver, wire, size);
}

static BreakRuntimeError push_voice_frame(BreakVoiceReceiver *receiver, u32 sequence, i16 base)
{
    return push_voice_frame_at(receiver, VOICE_RATE, VOICE_SAMPLES, sequence, base);
}

TEST(received_voice_frames_play_through_a_pcm_stream_in_order)
{
    static f32 out[2u * VOICE_SAMPLES];
    BreakVoiceStreamConfig config;
    BreakVoiceReceiver *receiver = NULL;
    BreakVoicePlayback playback;
    AudioPcmStreamHandle stream = 0;
    bool ready = false;
    u32 written = 0;
    memset(&config, 0, sizeof(config));
    config.sample_rate = VOICE_RATE;
    config.channels = 1u;
    config.sample_count = VOICE_SAMPLES;
    config.jitter_delay_ms = 20u;
    config.jitter_capacity = 8u;
    config.queue_capacity = 8u;
    ASSERT_EQ(break_voice_receiver_create(NULL, &config, &receiver), BREAK_RUNTIME_OK);
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_EQ(audio_pcm_stream_open(as, 1u, AUDIO_BUS_MASTER, 1.0f, &stream), AUDIO_OK);

    /* frames arrive out of order */
    ASSERT_EQ(push_voice_frame(receiver, 2u, 3000), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_voice_frame(receiver, 1u, 1000), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 2u, 0u), BREAK_RUNTIME_OK);

    /* the producer moves every ready frame into the stream */
    for (u64 now = 0u; now <= 40u; now += 10u) {
        ASSERT_EQ(break_voice_receiver_pop(receiver, now, &playback, &ready), BREAK_RUNTIME_OK);
        if (!ready) continue;
        ASSERT_EQ(audio_pcm_stream_write_i16(as, stream, playback.samples,
                                             playback.sample_count, &written),
                  AUDIO_OK);
        ASSERT_EQ(written, (u32)playback.sample_count);
    }
    {
        u32 queued = 0;
        ASSERT_EQ(audio_pcm_stream_queued(as, stream, &queued), AUDIO_OK);
        ASSERT_EQ(queued, 2u * VOICE_SAMPLES);
    }
    /* the mixer plays sequence 1 then sequence 2, as the sender produced */
    ASSERT_EQ(audio_system_render(as, out, VOICE_SAMPLES), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 1000.0f / 32768.0f, 1e-7f);
    ASSERT_FLOAT_EQ(out[1], 1000.0f / 32768.0f, 1e-7f);
    ASSERT_FLOAT_EQ(out[2u * (VOICE_SAMPLES - 1u)], (f32)(1000 + 479) / 32768.0f, 1e-7f);
    ASSERT_EQ(audio_system_render(as, out, VOICE_SAMPLES), AUDIO_OK);
    ASSERT_FLOAT_EQ(out[0], 3000.0f / 32768.0f, 1e-7f);
    {
        u64 under = 1u;
        ASSERT_EQ(audio_pcm_stream_underruns(as, stream, &under), AUDIO_OK);
        ASSERT_EQ(under, 0u);
    }
    ASSERT_EQ(audio_pcm_stream_close(as, stream), AUDIO_OK);
    audio_system_destroy(as);
    break_voice_receiver_destroy(receiver);
}

/* A 16 kHz voice stream (160 samples = 10 ms) plays through a stream opened
 * at 16 kHz: every source sample comes out at its 48 kHz position, the
 * frames in between interpolated. */
TEST(voice_at_16k_plays_through_a_rate_converting_stream)
{
    static f32 out[2u * 480u];
    BreakVoiceStreamConfig config;
    BreakVoiceReceiver *receiver = NULL;
    BreakVoicePlayback playback;
    AudioPcmStreamHandle stream = 0;
    bool ready = false;
    u32 written = 0;
    memset(&config, 0, sizeof(config));
    config.sample_rate = 16000u;
    config.channels = 1u;
    config.sample_count = 160u;
    config.jitter_delay_ms = 0u;
    config.jitter_capacity = 8u;
    config.queue_capacity = 8u;
    ASSERT_EQ(break_voice_receiver_create(NULL, &config, &receiver), BREAK_RUNTIME_OK);
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_EQ(audio_pcm_stream_open_rate(as, 1u, 16000u, AUDIO_BUS_MASTER, 1.0f, &stream),
              AUDIO_OK);
    ASSERT_EQ(push_voice_frame_at(receiver, 16000u, 160u, 1u, 0), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_voice_frame_at(receiver, 16000u, 160u, 2u, 160), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 2u, 0u), BREAK_RUNTIME_OK);
    for (u64 now = 0u; now <= 20u; now += 10u) {
        ASSERT_EQ(break_voice_receiver_pop(receiver, now, &playback, &ready), BREAK_RUNTIME_OK);
        if (!ready) continue;
        ASSERT_EQ(audio_pcm_stream_write_i16(as, stream, playback.samples,
                                             playback.sample_count, &written),
                  AUDIO_OK);
        ASSERT_EQ(written, (u32)playback.sample_count);
    }
    /* 10 ms of output: 480 frames at 48 kHz from 160 source samples */
    ASSERT_EQ(audio_system_render(as, out, 480u), AUDIO_OK);
    for (u32 k = 0; k < 160u; ++k) {
        ASSERT_FLOAT_EQ(out[2u * (3u * k)], (f32)k / 32768.0f, 1e-7f);
        ASSERT_FLOAT_EQ(out[2u * (3u * k + 1u)], ((f32)k + 1.0f / 3.0f) / 32768.0f, 1e-7f);
    }
    {
        u64 under = 1u;
        ASSERT_EQ(audio_pcm_stream_underruns(as, stream, &under), AUDIO_OK);
        ASSERT_EQ(under, 0u);
    }
    audio_system_destroy(as);
    break_voice_receiver_destroy(receiver);
}

typedef struct MixerThread {
    AudioSystem *as;
    bool filtered;
    atomic_bool stop;
    atomic_uint renders;
    bool bad_sample;
} MixerThread;

/* A 96 kHz stream of the constant 0.25 goes through the anti-aliasing
 * low-pass: its step response starts near 0.017 and overshoots to about
 * 0.289 before settling. */
static bool filtered_sample_ok(f32 v)
{
    return v == 0.0f || (v > 0.01f && v < 0.3f);
}

/* Renders like a device callback, on its own thread. Every sample is either
 * silence or one the producer wrote (filtered for a fast stream), so a torn
 * read shows up as a value outside that set. */
static PLATFORM_THREAD_RET mixer_thread_main(PLATFORM_THREAD_ARG arg)
{
    MixerThread *m = (MixerThread *)arg;
    f32 out[2u * 64u];
    while (!atomic_load(&m->stop)) {
        if (audio_system_render(m->as, out, 64u) != AUDIO_OK) {
            m->bad_sample = true;
            return PLATFORM_THREAD_RETURN;
        }
        for (u32 i = 0; i < 128u; ++i) {
            if (m->filtered ? !filtered_sample_ok(out[i])
                            : (out[i] != 0.0f && out[i] != 0.25f)) {
                m->bad_sample = true;
            }
        }
        atomic_fetch_add(&m->renders, 1u);
    }
    return PLATFORM_THREAD_RETURN;
}

/* The producer opens at `rate`, writes and closes while another thread
 * mixes: no torn samples, and close waits for a read in progress before
 * freeing the ring (run under TSan / ASan to see races and use-after-free;
 * at 96 kHz the mixer also filters the ring in place). */
static void race_producer_with_mixer(u32 rate)
{
    static i16 pcm[256];
    MixerThread m;
    PlatformThread thread;
    AudioPcmStreamHandle stream = 0;
    u32 written = 0;
    for (u32 i = 0; i < 256u; ++i) pcm[i] = 8192;
    memset(&m, 0, sizeof(m));
    m.as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(m.as);
    m.filtered = rate > AUDIO_PCM_SAMPLE_RATE;
    atomic_init(&m.stop, false);
    atomic_init(&m.renders, 0u);
    ASSERT_TRUE(platform_thread_create(&thread, mixer_thread_main, &m));
    for (u32 round = 0; round < 200u; ++round) {
        ASSERT_EQ(audio_pcm_stream_open_rate(m.as, 1u, rate, AUDIO_BUS_MASTER, 1.0f, &stream),
                  AUDIO_OK);
        for (u32 k = 0; k < 8u; ++k) {
            ASSERT_EQ(audio_pcm_stream_write_i16(m.as, stream, pcm, 256u, &written), AUDIO_OK);
        }
        ASSERT_EQ(audio_pcm_stream_close(m.as, stream), AUDIO_OK);
    }
    /* let the mixer run at least once after the last close */
    {
        u32 seen = atomic_load(&m.renders);
        while (atomic_load(&m.renders) < seen + 2u) {
        }
    }
    atomic_store(&m.stop, true);
    platform_thread_join(thread);
    ASSERT_FALSE(m.bad_sample);
    ASSERT_TRUE(atomic_load(&m.renders) > 0u);
    audio_system_destroy(m.as);
}

TEST(producer_and_close_race_with_a_mixer_thread)
{
    race_producer_with_mixer(AUDIO_PCM_SAMPLE_RATE);
}

TEST(fast_stream_filter_races_with_a_mixer_thread)
{
    race_producer_with_mixer(96000u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(received_voice_frames_play_through_a_pcm_stream_in_order);
    RUN_TEST(voice_at_16k_plays_through_a_rate_converting_stream);
    RUN_TEST(producer_and_close_race_with_a_mixer_thread);
    RUN_TEST(fast_stream_filter_races_with_a_mixer_thread);
TEST_MAIN_END()
