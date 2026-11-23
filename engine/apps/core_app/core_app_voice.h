#pragma once

#include <audio/audio_capture.h>
#include <audio/audio_drift_compensator.h>
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
    /* Aligner delay line modes (audio_voice_aligner_set_sinc and
     * _set_crossfade_frames); zero keeps linear, immediate changes. The
     * crossfade applies to later delay updates. create returns INVALID for a
     * crossfade the aligner refuses (above 48000). */
    bool aligner_sinc;
    u32 aligner_crossfade_frames;
    /* Capture recovery. 0 max_reopen_failures: a lost capture device makes
     * pump return UNAVAILABLE at once. Otherwise pump reopens the selected
     * input, at most once per call and reopen_interval_ms apart (monotonic
     * clock, 0 = every call), and returns UNAVAILABLE only after that many
     * consecutive refused reopens. */
    u32 reopen_interval_ms;
    u32 max_reopen_failures;
    /* Clock drift compensation: the playback reference is resampled by an
     * AudioDriftCompensator before alignment, fed with the locked aligner
     * delay every drift_observe_packets packets (1..1000) while it is
     * locked. Off: the raw reference is aligned as is. create returns
     * INVALID for a drift config the compensator refuses. */
    bool drift_enabled;
    AudioDriftCompensatorConfig drift;
    u32 drift_observe_packets;
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
    /* Runtime capture switches (core_app_voice_request_capture_device):
     * opened, refused for the name, failed for another reason. */
    u64 capture_switches;
    u64 capture_switch_rejected;
    u64 capture_switch_failures;
    /* Drift ratio updates applied, and the drift the current ratio removes
     * in parts per billion; a new device resets the ratio (not the count). */
    u64 drift_corrections;
    i64 drift_correction_ppb;
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
/* The aligner's delay line modes as applied at create; false/0 for NULL.
 * Both are fixed at create and never written again, so any thread may read
 * them while the worker runs. */
bool core_app_voice_aligner_sinc(const CoreAppVoice *voice);
u32 core_app_voice_aligner_crossfade_frames(const CoreAppVoice *voice);
/* The error that ended the worker, readable from any thread while it runs:
 * OK while it pumps, e.g. UNAVAILABLE after the capture device was lost. */
BreakRuntimeError core_app_voice_worker_error(CoreAppVoice *voice);
/* The capture backend name (audio_capture_backend_name): "Null" means
 * miniaudio's null device, which captures only silence. */
const char *core_app_voice_capture_backend(const CoreAppVoice *voice);
/* Fills out with the capture device name; false and "" when it has none.
 * Not while the worker runs: a reopen rewrites the name. */
bool core_app_voice_capture_name(const CoreAppVoice *voice, char *out, usize capacity);
/* Asks the pumping thread to open another input device (NULL or "" for the
 * default) on its next pump. One request at a time from one requesting
 * thread: OVERLOAD while an earlier one is still pending, REJECTED for a
 * name of 128 bytes or more or a voice that is not started, INVALID for
 * NULL. The pump keeps the old device when the name is unknown (no fallback
 * to the default); a switched name is the one a later loss reopens. The
 * result shows up in the capture_switch* stats. */
BreakRuntimeError core_app_voice_request_capture_device(CoreAppVoice *voice, const char *name);
/* FAKE/NULL capture only (tests): forwards audio_capture_simulate_event. */
BreakRuntimeError core_app_voice_simulate_capture_event(CoreAppVoice *voice,
                                                        AudioCaptureEvent event);
/* Stop joins the worker before stopping devices; queued frames stay readable. */
/* Device events on the runtime message bus (design:
 * docs/design/runtime_message_model.md "语音设备事件接入总线"). After
 * core_app_voice_attach_bus the pumping thread publishes one message of
 * kind CORE_APP_VOICE_EVENT_KIND per device event, so the owner learns of
 * them from its own queue instead of polling counters. The payload is a
 * CoreAppVoiceEvent in little-endian order (CORE_APP_VOICE_EVENT_SIZE
 * bytes). attach registers the kind as a control kind (it still arrives
 * when data has filled a subscriber queue) unless it is registered
 * already, with the same parameters; subscribers subscribe to it on the
 * bus. A full subscriber queue drops that subscriber's copy and the voice
 * counts it in CoreAppVoiceEventStats; the pumping thread never waits. The
 * bus must outlive the voice or be detached (NULL) while the voice is
 * stopped. attach is REJECTED while started. */
#define CORE_APP_VOICE_EVENT_KIND 0x0701u
#define CORE_APP_VOICE_EVENT_VERSION 1u
#define CORE_APP_VOICE_EVENT_SIZE 16u

typedef enum {
    CORE_APP_VOICE_EVENT_CAPTURE_RECOVERED = 1,
    CORE_APP_VOICE_EVENT_CAPTURE_REOPEN_FAILED = 2,
    CORE_APP_VOICE_EVENT_CAPTURE_UNAVAILABLE = 3, /* gave up: the worker stops */
    CORE_APP_VOICE_EVENT_PLAYBACK_RECOVERED = 4,
    CORE_APP_VOICE_EVENT_CAPTURE_SWITCHED = 5,
    CORE_APP_VOICE_EVENT_CAPTURE_SWITCH_REJECTED = 6,
    CORE_APP_VOICE_EVENT_CAPTURE_SWITCH_FAILED = 7
} CoreAppVoiceEventType;

typedef struct {
    u32 type;  /* CoreAppVoiceEventType */
    u32 reserved;
    u64 count; /* the matching CoreAppVoiceStats counter after the event; 0
                * for CAPTURE_UNAVAILABLE */
} CoreAppVoiceEvent;

typedef struct {
    u64 published;    /* copies delivered to at least one subscriber */
    u64 undelivered;  /* events at least one subscriber missed */
} CoreAppVoiceEventStats;

struct BreakRuntimeBus;
BreakRuntimeError core_app_voice_attach_bus(CoreAppVoice *voice, struct BreakRuntimeBus *bus);
BreakRuntimeError core_app_voice_event_stats(CoreAppVoice *voice, CoreAppVoiceEventStats *out);
/* Decodes a payload; false for a wrong size or an unknown type. */
bool core_app_voice_event_decode(const void *data, usize size, CoreAppVoiceEvent *out);

BreakRuntimeError core_app_voice_stop(CoreAppVoice *voice);
void core_app_voice_destroy(CoreAppVoice *voice);
