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
    /* The input device to open (as audio_capture_list_devices reports it);
     * NULL or "" opens the default. Copied at create; a reopen after a loss
     * opens it again and falls back to the default only when it is gone.
     * create returns REJECTED for a name of 128 bytes or more, a name no
     * device has, or any name with a FAKE backend. */
    const char *capture_device_name;
    AudioVoiceAlignerConfig aligner;
    AudioVoiceProcessorConfig processor;
    bool use_gcc;
    /* Capture recovery. 0 max_reopen_failures: a lost capture device makes
     * pump return UNAVAILABLE at once. Otherwise pump reopens the selected
     * input, at most once per call and reopen_interval_ms apart (monotonic
     * clock, 0 = every call), and returns UNAVAILABLE only after that many
     * consecutive refused reopens. */
    u32 reopen_interval_ms;
    u32 max_reopen_failures;
} CoreAppVoiceConfig;

typedef struct CoreAppVoice CoreAppVoice;

typedef struct {
    u64 produced;
    u64 dropped;
    u64 capture_overruns;
    u64 reference_overruns;
    u64 capture_recoveries;
    u64 capture_reopen_failures;
    /* Playback reopens the pump noticed (audio_system_recoveries). */
    u64 playback_recoveries;
} CoreAppVoiceStats;

/* Only create/thread-start allocate, and pump when it reopens a lost capture
 * (ma_device_init). Manual and threaded modes share pump. */
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
/* The error that ended the worker, readable from any thread while it runs:
 * OK while it pumps, e.g. UNAVAILABLE after the capture device was lost. */
BreakRuntimeError core_app_voice_worker_error(CoreAppVoice *voice);
/* The capture backend name (audio_capture_backend_name): "Null" means
 * miniaudio's null device, which captures only silence. */
const char *core_app_voice_capture_backend(const CoreAppVoice *voice);
/* Fills out with the capture device name; false and "" when it has none.
 * Not while the worker runs: a reopen rewrites the name. */
bool core_app_voice_capture_name(const CoreAppVoice *voice, char *out, usize capacity);
/* FAKE/NULL capture only (tests): forwards audio_capture_simulate_event. */
BreakRuntimeError core_app_voice_simulate_capture_event(CoreAppVoice *voice,
                                                        AudioCaptureEvent event);
/* Stop joins the worker before stopping devices; queued frames stay readable. */
BreakRuntimeError core_app_voice_stop(CoreAppVoice *voice);
void core_app_voice_destroy(CoreAppVoice *voice);
