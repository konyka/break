#pragma once

#include <audio/audio_capture.h>
#include <audio/audio_voice_aligner.h>
#include <audio/audio_voice_processor.h>
#include <network/break_online_voice.h>
#include <runtime/runtime_types.h>

#define CORE_APP_VOICE_FRAME_FRAMES 480u
#define CORE_APP_VOICE_QUEUE_CAPACITY 16u

typedef struct {
    AudioSystem *playback; /* borrowed until destroy */
    AudioBackend capture_backend;
    AudioVoiceAlignerConfig aligner;
    AudioVoiceProcessorConfig processor;
    bool use_gcc;
} CoreAppVoiceConfig;

typedef struct CoreAppVoice CoreAppVoice;

typedef struct {
    u64 produced;
    u64 dropped;
    u64 capture_overruns;
    u64 reference_overruns;
} CoreAppVoiceStats;

/* Only create/thread-start allocate. Manual and threaded modes share pump. */
BreakRuntimeError core_app_voice_create(const CoreAppVoiceConfig *config,
                                        CoreAppVoice **out);
BreakRuntimeError core_app_voice_start(CoreAppVoice *voice);
BreakRuntimeError core_app_voice_start_threaded(CoreAppVoice *voice);
/* FAKE input only: forwards to the capture device path without exposing its
 * private object. Other backends return BREAK_RUNTIME_REJECTED. */
BreakRuntimeError core_app_voice_inject(CoreAppVoice *voice, const f32 *samples, u32 frames);
BreakRuntimeError core_app_voice_pump(CoreAppVoice *voice, u32 max_packets);
BreakRuntimeError core_app_voice_pop(CoreAppVoice *voice, BreakVoiceFrame *out,
                                     bool *out_ready);
BreakRuntimeError core_app_voice_stats(CoreAppVoice *voice, CoreAppVoiceStats *out);
/* Stop joins the worker before stopping devices; queued frames stay readable. */
BreakRuntimeError core_app_voice_stop(CoreAppVoice *voice);
void core_app_voice_destroy(CoreAppVoice *voice);
