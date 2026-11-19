#include "editor_audio_sink.h"

static void stream_sink_close(void *user) {
    BreakEditorAudioStreamSink *sink = (BreakEditorAudioStreamSink *)user;
    if (sink == NULL || !sink->open) {
        return;
    }
    (void)audio_pcm_stream_close(sink->system, sink->stream);
    sink->open = false;
    sink->stream = 0u;
}

static bool stream_sink_open(void *user, u32 sample_rate, u32 channels) {
    BreakEditorAudioStreamSink *sink = (BreakEditorAudioStreamSink *)user;
    AudioPcmStreamHandle handle = 0u;
    if (sink == NULL || sink->system == NULL) {
        return false;
    }
    stream_sink_close(sink);
    if (audio_pcm_stream_open_rate(sink->system, channels, sample_rate, AUDIO_BUS_MASTER, 1.0f,
                                   &handle) != AUDIO_OK) {
        return false;
    }
    sink->stream = handle;
    sink->open = true;
    return true;
}

static bool stream_sink_write(void *user, const i16 *samples, u32 frames, u32 *out_written) {
    BreakEditorAudioStreamSink *sink = (BreakEditorAudioStreamSink *)user;
    return sink != NULL && sink->open &&
           audio_pcm_stream_write_i16(sink->system, sink->stream, samples, frames,
                                      out_written) == AUDIO_OK;
}

static bool stream_sink_queued(void *user, u32 *out_frames) {
    BreakEditorAudioStreamSink *sink = (BreakEditorAudioStreamSink *)user;
    return sink != NULL && sink->open &&
           audio_pcm_stream_queued(sink->system, sink->stream, out_frames) == AUDIO_OK;
}

static const BreakEditorAudioSink k_stream_sink = {stream_sink_open, stream_sink_write,
                                                   stream_sink_queued, stream_sink_close};

const BreakEditorAudioSink *break_editor_audio_stream_sink(void) { return &k_stream_sink; }

void break_editor_audio_stream_sink_init(BreakEditorAudioStreamSink *sink,
                                         AudioSystem *system) {
    if (sink != NULL) {
        sink->system = system;
        sink->stream = 0u;
        sink->open = false;
    }
}
