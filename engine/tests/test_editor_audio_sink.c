/* The editor preview sink on an engine PCM stream, rendered by the FAKE
 * (device-free) audio backend. */
#include "test_framework.h"

#include "editor_audio_sink.h"

#include <editor/editor_audio.h>

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

/* The preview over the real stream: at rates that do not divide 48 kHz the
 * mixer holds the last frame(s) back for interpolation, so without the
 * finish padding the preview would never see an empty queue. */
static void play_to_the_end(u32 rate, AudioResampleMode mode)
{
    static i16 pcm[3000u];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    BreakEditorAudioStreamSink sink;
    BreakEditorAudioPreview *preview = break_editor_audio_preview_create();
    BreakEditorDoc *doc = break_editor_doc_create();
    static f32 out[2u * 1024u];
    u32 i, last = 0u;
    ASSERT_NOT_NULL(as);
    ASSERT_NOT_NULL(preview);
    ASSERT_NOT_NULL(doc);
    for (i = 0u; i < 3000u; i++) pcm[i] = (i16)((i % 50u) * 300u);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, rate, 1u, pcm, 3000u));
    break_editor_audio_stream_sink_init(&sink, as);
    sink.resample = mode;
    break_editor_audio_preview_set_sink(preview, break_editor_audio_stream_sink(), &sink);
    ASSERT_TRUE(break_editor_audio_preview_play(preview, doc));
    for (i = 0u; i < 2000u && break_editor_audio_preview_playing(preview); i++) {
        break_editor_audio_preview_pump(preview);
        const u32 pos = break_editor_audio_preview_position_frames(preview);
        if (break_editor_audio_preview_playing(preview)) {
            ASSERT_TRUE(pos >= last);
            ASSERT_TRUE(pos <= 3000u);
            last = pos;
        }
        ASSERT_EQ(audio_system_render(as, out, 1024u), AUDIO_OK);
    }
    ASSERT_FALSE(break_editor_audio_preview_playing(preview));
    ASSERT_FALSE(sink.open);
    ASSERT_TRUE(i < 2000u);
    break_editor_audio_preview_destroy(preview);
    break_editor_doc_destroy(doc);
    audio_system_destroy(as);
}

TEST(preview_stops_by_itself_at_any_rate_and_resampler)
{
    const u32 rates[] = {8000u, 22050u, 44100u, 48000u, 88200u, 96000u, 192000u};
    for (u32 r = 0u; r < sizeof(rates) / sizeof(rates[0]); ++r) {
        play_to_the_end(rates[r], AUDIO_RESAMPLE_LINEAR);
        play_to_the_end(rates[r], AUDIO_RESAMPLE_SINC);
    }
}

TEST(preview_plays_from_a_start_frame_on_the_real_stream)
{
    static i16 pcm[2u * 100u];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    BreakEditorAudioStreamSink sink;
    BreakEditorAudioPreview *preview = break_editor_audio_preview_create();
    BreakEditorDoc *doc = break_editor_doc_create();
    f32 out[2u * 8u];
    u32 i;
    ASSERT_NOT_NULL(as);
    for (i = 0u; i < 200u; i++) pcm[i] = (i16)(i * 100);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 48000u, 2u, pcm, 100u));
    break_editor_audio_stream_sink_init(&sink, as);
    break_editor_audio_preview_set_sink(preview, break_editor_audio_stream_sink(), &sink);
    ASSERT_TRUE(break_editor_audio_preview_play_from(preview, doc, 40u));
    break_editor_audio_preview_pump(preview);
    ASSERT_EQ(audio_system_render(as, out, 8u), AUDIO_OK);
    for (i = 0u; i < 8u; i++) {
        ASSERT_FLOAT_EQ(out[2u * i], (f32)pcm[2u * (40u + i)] / 32768.0f, 1e-6f);
        ASSERT_FLOAT_EQ(out[2u * i + 1u], (f32)pcm[2u * (40u + i) + 1u] / 32768.0f, 1e-6f);
    }
    ASSERT_EQ(break_editor_audio_preview_position_frames(preview), 48u);
    break_editor_audio_preview_destroy(preview);
    break_editor_doc_destroy(doc);
    audio_system_destroy(as);
}

TEST(preview_plays_only_a_range_and_stops_at_its_end)
{
    static i16 pcm[3000u];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    BreakEditorAudioStreamSink sink;
    BreakEditorAudioPreview *preview = break_editor_audio_preview_create();
    BreakEditorDoc *doc = break_editor_doc_create();
    static f32 out[2u * 512u];
    u32 i;
    for (i = 0u; i < 3000u; i++) pcm[i] = (i16)(i + 1u);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 44100u, 1u, pcm, 3000u));
    break_editor_audio_stream_sink_init(&sink, as);
    break_editor_audio_preview_set_sink(preview, break_editor_audio_stream_sink(), &sink);
    ASSERT_FALSE(break_editor_audio_preview_play_range(preview, doc, 3000u, 4000u));
    ASSERT_FALSE(break_editor_audio_preview_play_range(preview, doc, 20u, 20u));
    ASSERT_TRUE(break_editor_audio_preview_play_range(preview, doc, 1000u, 1200u));
    ASSERT_EQ(break_editor_audio_preview_length_frames(preview), 1200u);
    for (i = 0u; i < 100u && break_editor_audio_preview_playing(preview); i++) {
        break_editor_audio_preview_pump(preview);
        ASSERT_TRUE(break_editor_audio_preview_position_frames(preview) <= 1200u);
        ASSERT_EQ(audio_system_render(as, out, 512u), AUDIO_OK);
    }
    ASSERT_FALSE(break_editor_audio_preview_playing(preview));
    ASSERT_TRUE(i < 100u);
    break_editor_audio_preview_destroy(preview);
    break_editor_doc_destroy(doc);
    audio_system_destroy(as);
}

TEST_MAIN_BEGIN()
    RUN_TEST(preview_plays_only_a_range_and_stops_at_its_end);
    RUN_TEST(preview_plays_from_a_start_frame_on_the_real_stream);
    RUN_TEST(preview_stops_by_itself_at_any_rate_and_resampler);
    RUN_TEST(stream_sink_plays_written_frames_on_the_master_mix);
    RUN_TEST(stream_sink_reopens_and_rejects_bad_formats);
TEST_MAIN_END()
