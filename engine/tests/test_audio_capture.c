/* audio_capture: the input ring (FAKE backend), the null device in real
 * time, and a producer/consumer pair across threads. */
#include "test_framework.h"

#include <audio/audio_capture.h>
#include <core/log.h>
#include <core/platform_thread.h>

#include <math.h>
#include <stdatomic.h>
#include <string.h>
#include <time.h>

void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    (void)level; (void)file; (void)line; (void)fmt;
}

static AudioCaptureConfig fake_config(u32 channels, u32 ring_frames) {
    AudioCaptureConfig config;
    memset(&config, 0, sizeof(config));
    config.backend = AUDIO_BACKEND_FAKE;
    config.sample_rate = 48000u;
    config.channels = channels;
    config.ring_frames = ring_frames;
    return config;
}

static AudioCapture *started_fake(u32 channels, u32 ring_frames) {
    AudioCaptureConfig config = fake_config(channels, ring_frames);
    AudioCapture *capture = NULL;
    if (audio_capture_create(&config, &capture) != AUDIO_OK) return NULL;
    if (audio_capture_start(capture) != AUDIO_OK) {
        audio_capture_destroy(capture);
        return NULL;
    }
    return capture;
}

TEST(create_refuses_every_invalid_config)
{
    AudioCapture *sentinel = (AudioCapture *)&sentinel;
    AudioCapture *capture = sentinel;
    AudioCaptureConfig config = fake_config(1u, 64u);
    ASSERT_EQ(audio_capture_create(NULL, &capture), AUDIO_INVALID);
    ASSERT_EQ(audio_capture_create(&config, NULL), AUDIO_INVALID);
    const struct { u32 rate, channels, ring; i32 backend; } bad[] = {
        {7999u, 1u, 64u, AUDIO_BACKEND_FAKE}, {192001u, 1u, 64u, AUDIO_BACKEND_FAKE},
        {48000u, 0u, 64u, AUDIO_BACKEND_FAKE}, {48000u, 3u, 64u, AUDIO_BACKEND_FAKE},
        {48000u, 1u, 0u, AUDIO_BACKEND_FAKE}, {48000u, 1u, 96u, AUDIO_BACKEND_FAKE},
        {48000u, 1u, AUDIO_CAPTURE_MAX_RING_FRAMES * 2u, AUDIO_BACKEND_FAKE},
        {48000u, 1u, 64u, AUDIO_BACKEND_FAKE + 1}, {48000u, 1u, 64u, -1}};
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        config.sample_rate = bad[i].rate;
        config.channels = bad[i].channels;
        config.ring_frames = bad[i].ring;
        config.backend = (AudioBackend)bad[i].backend;
        ASSERT_EQ(audio_capture_create(&config, &capture), AUDIO_INVALID);
        ASSERT_TRUE(capture == sentinel);
    }
    /* the limits themselves are accepted */
    config = fake_config(2u, AUDIO_CAPTURE_MAX_RING_FRAMES);
    config.sample_rate = AUDIO_CAPTURE_MIN_RATE;
    ASSERT_EQ(audio_capture_create(&config, &capture), AUDIO_OK);
    ASSERT_FALSE(audio_capture_running(capture));
    audio_capture_destroy(capture);
    config = fake_config(1u, 1u);
    config.sample_rate = AUDIO_CAPTURE_MAX_RATE;
    ASSERT_EQ(audio_capture_create(&config, &capture), AUDIO_OK);
    audio_capture_destroy(capture);
    audio_capture_destroy(NULL);
}

TEST(injected_frames_are_converted_and_read_in_order)
{
    AudioCapture *capture = started_fake(1u, 16u);
    ASSERT_NOT_NULL(capture);
    const f32 in[8] = {0.0f, 0.5f, -0.5f, 1.0f, -1.0f, 2.0f, -3.0f, NAN};
    const i16 expect[8] = {0, 16384, -16384, 32767, -32767, 32767, -32767, 0};
    i16 out[8];
    u32 n = 99u;
    ASSERT_EQ(audio_capture_inject(capture, in, 8u), AUDIO_OK);
    ASSERT_EQ(audio_capture_available(capture), 8u);
    ASSERT_EQ(audio_capture_read_i16(capture, out, 3u, &n), AUDIO_OK);
    ASSERT_EQ(n, 3u);
    ASSERT_EQ(audio_capture_available(capture), 5u);
    ASSERT_EQ(audio_capture_read_i16(capture, out + 3, 8u, &n), AUDIO_OK);
    ASSERT_EQ(n, 5u);
    for (u32 i = 0; i < 8u; ++i) ASSERT_EQ(out[i], expect[i]);
    ASSERT_EQ(audio_capture_read_i16(capture, out, 8u, &n), AUDIO_OK);
    ASSERT_EQ(n, 0u);
    {
        const f32 inf[2] = {INFINITY, -INFINITY};
        ASSERT_EQ(audio_capture_inject(capture, inf, 2u), AUDIO_OK);
        ASSERT_EQ(audio_capture_read_i16(capture, out, 2u, &n), AUDIO_OK);
        ASSERT_EQ(out[0], 0);
        ASSERT_EQ(out[1], 0);
    }
    ASSERT_EQ(audio_capture_read_i16(NULL, out, 1u, &n), AUDIO_INVALID);
    ASSERT_EQ(audio_capture_read_i16(capture, NULL, 1u, &n), AUDIO_INVALID);
    ASSERT_EQ(audio_capture_read_i16(capture, out, 1u, NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_capture_inject(capture, NULL, 1u), AUDIO_INVALID);
    ASSERT_EQ(audio_capture_inject(NULL, in, 1u), AUDIO_INVALID);
    audio_capture_destroy(capture);
}

TEST(stereo_frames_wrap_around_the_ring)
{
    AudioCapture *capture = started_fake(2u, 8u);
    ASSERT_NOT_NULL(capture);
    f32 in[2u * 6u];
    i16 out[2u * 6u];
    u32 n = 0u;
    /* 5 frames in, 5 out, then 6 more cross the end of the 8-frame ring */
    for (u32 round = 0; round < 2u; ++round) {
        u32 frames = round == 0u ? 5u : 6u;
        for (u32 i = 0; i < frames; ++i) {
            in[2u * i] = (f32)(round * 10u + i) / 100.0f;
            in[2u * i + 1u] = -(f32)(round * 10u + i) / 100.0f;
        }
        ASSERT_EQ(audio_capture_inject(capture, in, frames), AUDIO_OK);
        ASSERT_EQ(audio_capture_read_i16(capture, out, 6u, &n), AUDIO_OK);
        ASSERT_EQ(n, frames);
        for (u32 i = 0; i < frames; ++i) {
            i16 v = (i16)lrintf((f32)(round * 10u + i) / 100.0f * 32767.0f);
            ASSERT_EQ(out[2u * i], v);
            ASSERT_EQ(out[2u * i + 1u], (i16)-v);
        }
    }
    ASSERT_EQ(audio_capture_overruns(capture), 0u);
    audio_capture_destroy(capture);
}

TEST(a_full_ring_keeps_the_oldest_frames_and_counts_the_rest)
{
    AudioCapture *capture = started_fake(1u, 4u);
    ASSERT_NOT_NULL(capture);
    const f32 in[6] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    i16 out[6];
    u32 n = 0u;
    ASSERT_EQ(audio_capture_inject(capture, in, 6u), AUDIO_OK);
    ASSERT_EQ(audio_capture_available(capture), 4u);
    ASSERT_EQ(audio_capture_overruns(capture), 2u);
    ASSERT_EQ(audio_capture_read_i16(capture, out, 6u, &n), AUDIO_OK);
    ASSERT_EQ(n, 4u);
    for (u32 i = 0; i < 4u; ++i) ASSERT_EQ(out[i], (i16)lrintf(in[i] * 32767.0f));
    ASSERT_EQ(audio_capture_inject(capture, in, 5u), AUDIO_OK);
    ASSERT_EQ(audio_capture_overruns(capture), 3u);
    audio_capture_destroy(capture);
}

TEST(start_and_stop_are_idempotent_and_gate_injection)
{
    AudioCaptureConfig config = fake_config(1u, 8u);
    AudioCapture *capture = NULL;
    const f32 one = 0.25f;
    ASSERT_EQ(audio_capture_create(&config, &capture), AUDIO_OK);
    ASSERT_EQ(audio_capture_inject(capture, &one, 1u), AUDIO_REJECTED);
    ASSERT_EQ(audio_capture_start(capture), AUDIO_OK);
    ASSERT_EQ(audio_capture_start(capture), AUDIO_OK);
    ASSERT_TRUE(audio_capture_running(capture));
    ASSERT_EQ(audio_capture_inject(capture, &one, 1u), AUDIO_OK);
    ASSERT_EQ(audio_capture_stop(capture), AUDIO_OK);
    ASSERT_EQ(audio_capture_stop(capture), AUDIO_OK);
    ASSERT_FALSE(audio_capture_running(capture));
    ASSERT_EQ(audio_capture_inject(capture, &one, 1u), AUDIO_REJECTED);
    /* frames captured before the stop can still be read */
    ASSERT_EQ(audio_capture_available(capture), 1u);
    ASSERT_EQ(audio_capture_start(NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_capture_stop(NULL), AUDIO_INVALID);
    ASSERT_FALSE(audio_capture_running(NULL));
    ASSERT_EQ(audio_capture_available(NULL), 0u);
    ASSERT_EQ(audio_capture_overruns(NULL), 0u);
    audio_capture_destroy(capture);
}

static void sleep_ms(u32 ms) {
#if defined(_WIN32)
    Sleep(ms);
#else
    struct timespec ts = {0, (long)ms * 1000000L};
    nanosleep(&ts, NULL);
#endif
}

TEST(the_null_device_delivers_silent_frames_in_real_time)
{
    AudioCaptureConfig config = fake_config(1u, 1u << 15);
    AudioCapture *capture = NULL;
    const f32 one = 0.25f;
    config.backend = AUDIO_BACKEND_NULL;
    ASSERT_EQ(audio_capture_create(&config, &capture), AUDIO_OK);
    ASSERT_EQ(audio_capture_inject(capture, &one, 1u), AUDIO_REJECTED);
    for (u32 pass = 0; pass < 2u; ++pass) {
        ASSERT_EQ(audio_capture_start(capture), AUDIO_OK);
        ASSERT_EQ(audio_capture_inject(capture, &one, 1u), AUDIO_REJECTED);
        u32 got = 0u;
        bool silent = true;
        for (u32 tries = 0; tries < 200u && got < 480u; ++tries) {
            i16 out[256];
            u32 n = 0u;
            ASSERT_EQ(audio_capture_read_i16(capture, out, 256u, &n), AUDIO_OK);
            for (u32 i = 0; i < n; ++i) silent = silent && out[i] == 0;
            got += n;
            if (n == 0u) sleep_ms(10u);
        }
        ASSERT_TRUE(got >= 480u);
        ASSERT_TRUE(silent);
        ASSERT_EQ(audio_capture_stop(capture), AUDIO_OK);
    }
    /* destroy stops a running device */
    ASSERT_EQ(audio_capture_start(capture), AUDIO_OK);
    audio_capture_destroy(capture);
}

#define THREAD_FRAMES 20000u

typedef struct {
    AudioCapture *capture;
    atomic_bool done;
} Producer;

static PLATFORM_THREAD_RET producer_main(PLATFORM_THREAD_ARG arg) {
    Producer *p = (Producer *)arg;
    f32 chunk[100];
    for (u32 sent = 0; sent < THREAD_FRAMES; sent += 100u) {
        for (u32 i = 0; i < 100u; ++i) chunk[i] = (f32)((sent + i) % 30000u) / 32767.0f;
        while (audio_capture_available(p->capture) > 1024u - 100u) platform_thread_yield();
        (void)audio_capture_inject(p->capture, chunk, 100u);
    }
    atomic_store(&p->done, true);
    return (PLATFORM_THREAD_RET)0;
}

TEST(a_producer_thread_and_the_reader_lose_nothing)
{
    Producer p;
    PlatformThread thread;
    p.capture = started_fake(1u, 1024u);
    atomic_init(&p.done, false);
    ASSERT_NOT_NULL(p.capture);
    ASSERT_TRUE(platform_thread_create(&thread, producer_main, &p));
    u32 got = 0u;
    bool ordered = true;
    while (got < THREAD_FRAMES) {
        i16 out[333];
        u32 n = 0u;
        if (audio_capture_read_i16(p.capture, out, 333u, &n) != AUDIO_OK) break;
        for (u32 i = 0; i < n; ++i) ordered = ordered && out[i] == (i16)((got + i) % 30000u);
        got += n;
        if (n == 0u) {
            if (atomic_load(&p.done) && audio_capture_available(p.capture) == 0u) break;
            platform_thread_yield();
        }
    }
    platform_thread_join(thread);
    ASSERT_EQ(got, THREAD_FRAMES);
    ASSERT_TRUE(ordered);
    ASSERT_EQ(audio_capture_overruns(p.capture), 0u);
    audio_capture_destroy(p.capture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_refuses_every_invalid_config);
    RUN_TEST(injected_frames_are_converted_and_read_in_order);
    RUN_TEST(stereo_frames_wrap_around_the_ring);
    RUN_TEST(a_full_ring_keeps_the_oldest_frames_and_counts_the_rest);
    RUN_TEST(start_and_stop_are_idempotent_and_gate_injection);
    RUN_TEST(the_null_device_delivers_silent_frames_in_real_time);
    RUN_TEST(a_producer_thread_and_the_reader_lose_nothing);
TEST_MAIN_END()
