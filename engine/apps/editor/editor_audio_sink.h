#pragma once
/* BreakEditorAudioSink backed by an engine PCM stream
 * (audio_pcm_stream_open_rate on the master bus, volume 1): the editor's
 * audio preview output. Each open opens a stream at the clip's rate and
 * closes the previous one; close closes it. Owner (shell) thread. */

#include "editor_audio_preview.h"

#include <audio/audio.h>
#include <audio/audio_extended.h>

typedef struct {
    AudioSystem *system; /* borrowed */
    AudioPcmStreamHandle stream;
    bool open;
} BreakEditorAudioStreamSink;

/* The sink vtable; `user` must point at a BreakEditorAudioStreamSink. */
const BreakEditorAudioSink *break_editor_audio_stream_sink(void);
/* Points `sink` at `system` (NULL = every open fails); nothing is opened. */
void break_editor_audio_stream_sink_init(BreakEditorAudioStreamSink *sink,
                                         AudioSystem *system);
