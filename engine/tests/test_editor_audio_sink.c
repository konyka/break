/* The editor preview sink on an engine PCM stream, rendered by the FAKE
 * (device-free) audio backend. */
#include "test_framework.h"

#include "editor_audio_sink.h"

#include <core/log.h>

#include <math.h>
#include <string.h>

/* core/log.c is not linked into this target: stub log_write for audio.c */
void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    (void)level; (void)file; (void)line; (void)fmt;
}

TEST(stream_sink_plays_written_frames_on_the_master_mix)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    BreakEditorAudioStreamSink sink;
    const BreakEditorAudioSink *vt = break_editor_audio_stream_sink();
    const i16 input[] = {1000, -1000, -2000, 2000, 3000, 1000, -4000, -2000};
    f32 stereo[16];
    u32 written = 0u, queued = 99u;
    ASSERT_NOT_NULL(as);
    ASSERT_NOT_NULL(vt);
    break_editor_audio_stream_sink_init(&sink, as);
    ASSERT_TRUE(vt->open(&sink, 48000u, 2u));
    ASSERT_TRUE(sink.open);
    ASSERT_TRUE(vt->write(&sink, input, 4u, &written));
    ASSERT_EQ(written, 4u);
    ASSERT_TRUE(vt->queued(&sink, &queued));
    ASSERT_EQ(queued, 4u);
    ASSERT_EQ(audio_system_render(as, stereo, 8u), AUDIO_OK);
    for (u32 i = 0u; i < 4u; ++i) {
        ASSERT_FLOAT_EQ(stereo[2u * i], (f32)input[2u * i] / 32768.0f, 1e-6f);
        ASSERT_FLOAT_EQ(stereo[2u * i + 1u], (f32)input[2u * i + 1u] / 32768.0f, 1e-6f);
    }
    for (u32 i = 8u; i < 16u; ++i) ASSERT_FLOAT_EQ(stereo[i], 0.0f, 1e-9f);
    ASSERT_TRUE(vt->queued(&sink, &queued));
    ASSERT_EQ(queued, 0u);
    vt->close(&sink);
    ASSERT_FALSE(sink.open);
    ASSERT_FALSE(vt->queued(&sink, &queued));
    ASSERT_FALSE(vt->write(&sink, input, 4u, &written));
    vt->close(&sink); /* closing twice is harmless */
    audio_system_destroy(as);
}

TEST(stream_sink_reopens_and_rejects_bad_formats)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    BreakEditorAudioStreamSink sink, none;
    const BreakEditorAudioSink *vt = break_editor_audio_stream_sink();
    const i16 mono[] = {8000, -8000};
    f32 stereo[4];
    u32 written = 0u;
    ASSERT_NOT_NULL(as);
    break_editor_audio_stream_sink_init(&none, NULL);
    ASSERT_FALSE(vt->open(&none, 48000u, 1u));
    break_editor_audio_stream_sink_init(&sink, as);
    ASSERT_FALSE(vt->open(&sink, 48000u, 3u));
    ASSERT_FALSE(vt->open(&sink, 4000u, 1u));
    ASSERT_FALSE(sink.open);
    /* every open replaces the previous stream: the engine has only
     * AUDIO_PCM_STREAM_MAX of them, so leaking one would exhaust it */
    for (u32 i = 0u; i < AUDIO_PCM_STREAM_MAX + 2u; ++i) {
        ASSERT_TRUE(vt->open(&sink, 48000u, 1u));
    }
    ASSERT_TRUE(vt->write(&sink, mono, 2u, &written));
    ASSERT_EQ(written, 2u);
    ASSERT_EQ(audio_system_render(as, stereo, 2u), AUDIO_OK);
    /* mono plays on both channels */
    ASSERT_FLOAT_EQ(stereo[0], 8000.0f / 32768.0f, 1e-6f);
    ASSERT_FLOAT_EQ(stereo[1], 8000.0f / 32768.0f, 1e-6f);
    ASSERT_FLOAT_EQ(stereo[2], -8000.0f / 32768.0f, 1e-6f);
    vt->close(&sink);
    for (u32 i = 0u; i < AUDIO_PCM_STREAM_MAX + 2u; ++i) {
        ASSERT_TRUE(vt->open(&sink, 8000u, 2u));
        vt->close(&sink);
    }
    audio_system_destroy(as);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_sink_plays_written_frames_on_the_master_mix);
    RUN_TEST(stream_sink_reopens_and_rejects_bad_formats);
TEST_MAIN_END()
