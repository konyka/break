#pragma once

#include <core/types.h>
#include <network/break_online_voice.h>
#include <runtime/runtime_types.h>

#include <stdio.h>

#include "core_app_network.h"

struct BreakRuntimeBus;
struct BreakRuntimeCoordinator;
struct BreakRuntimeWorldSession;
typedef struct CoreAppConfig CoreAppConfig;
typedef struct CoreApp CoreApp;

typedef enum CoreAppRenderMode {
    CORE_APP_RENDER_RECORD = 0,
    CORE_APP_RENDER_AUTO,
    CORE_APP_RENDER_VULKAN,
    CORE_APP_RENDER_OPENGL
} CoreAppRenderMode;

typedef enum CoreAppAudioMode {
    CORE_APP_AUDIO_RECORD = 0,
    CORE_APP_AUDIO_NULL,
    CORE_APP_AUDIO_DEVICE
} CoreAppAudioMode;

/* Off by default: a run without --voice writes no voice event. FAKE pumps
 * deterministic PCM on the CoreAppThread; DEVICE needs the audio device lane
 * and runs the voice worker on the default capture device. */
typedef enum CoreAppVoiceMode {
    CORE_APP_VOICE_OFF = 0,
    CORE_APP_VOICE_FAKE,
    CORE_APP_VOICE_DEVICE
} CoreAppVoiceMode;

/* Optional network channel, borrowed for the whole run. The runtime library
 * never links a transport: the executable supplies these callbacks only in
 * a build with the authenticated transport, so an offline core_app links no
 * break_net, break_session or snow symbols. Every callback runs on the
 * CoreAppThread. tick
 * receives read-only POD copies plus the physics_state_hash of the live
 * world after the step, and returns nothing, so a network failure
 * can only change network diagnostics, never the simulation. The four stop
 * callbacks follow the runtime coordinator phases and must be idempotent
 * because rollback may call them after a partial start. */
typedef struct CoreAppNetworkHooks {
    void *user;
    BreakRuntimeError (*start)(void *user, FILE *trace);
    void (*tick)(void *user, u32 tick, u64 level_generation,
                 const CoreAppSnapshotEntity *entities, u32 entity_count, u64 physics_hash);
    BreakRuntimeError (*stop_admission)(void *user);
    BreakRuntimeError (*stop_producers)(void *user);
    BreakRuntimeError (*drain)(void *user);
    BreakRuntimeError (*destroy)(void *user);
    /* Optional. After tick, the runtime asks whether a peer reported a
     * physics desync; if so it encodes a physics_sync correction of the live
     * world and hands the bytes over, borrowed for the call only. */
    bool (*physics_correction_wanted)(void *user);
    void (*physics_correction)(void *user, u32 tick, const u8 *data, usize size);
    /* Optional. Each PCM voice frame the CoreAppThread pops, borrowed for
     * the call only. The transport encodes it (BRV2, IMA ADPCM), so the
     * runtime links no codec; real time: it sends now or drops the frame,
     * and returns nothing. */
    void (*voice_frame)(void *user, const BreakVoiceFrame *frame);
    /* Optional. Called once before start with a bus the runtime owns; the
     * transport then publishes one CORE_APP_NET_EVENT_KIND notice per
     * network event on it, which the CoreAppThread drains after every tick
     * and totals at stop ("event=network_events"). */
    BreakRuntimeError (*attach_bus)(void *user, struct BreakRuntimeBus *bus);
    /* Optional World control adapter. Both hooks are present together in the
     * real transport; NULL keeps the original five-subsystem composition. */
    BreakRuntimeError (*world_adapter_register)(void *user, struct BreakRuntimeBus *bus,
                                                struct BreakRuntimeCoordinator *coordinator);
    struct BreakRuntimeWorldSession *(*world_adapter)(void *user);
} CoreAppNetworkHooks;

/* The network event notice kind (core_app_net_transport.h has the layout). */
#define CORE_APP_NET_EVENT_KIND 0x0702u

/* Corrections above the net payload cap are never encoded. */
#define CORE_APP_PHYSICS_CORRECTION_MAX_BYTES (64u * 1024u)

/* Diagnostics hooks are borrowed for the whole run. Each snapshot and its
 * rhi_backend/gpu_name strings are borrowed only for the publish callback,
 * which runs synchronously on the CoreAppThread; copy them in the callback to
 * retain them. */
typedef struct CoreAppDiagnosticsSnapshot {
    u32 tick;
    const char *rhi_backend;
    const char *gpu_name;
    bool network_live;
    u64 network_events_seen;
    u64 network_events_dropped;
    u32 key_down_count;
    u32 pad_connected_count;
    u32 touch_count;
    u32 gesture_count;
    u32 touch_status;
    u32 haptic_status;
} CoreAppDiagnosticsSnapshot;

typedef void (*CoreAppDiagnosticsPublishFn)(
    void *user, const CoreAppDiagnosticsSnapshot *snapshot);
typedef struct CoreAppDiagnosticsHooks {
    void *user;
    CoreAppDiagnosticsPublishFn publish;
} CoreAppDiagnosticsHooks;

struct CoreAppConfig {
    const char *asset_root;
    const char *scenario_path;
    const char *checkpoint_dir;
    const char *trace_path;
    const char *screenshot_path;
    CoreAppRenderMode render_mode;
    CoreAppAudioMode audio_mode;
    CoreAppVoiceMode voice_mode;
    /* Forces AUDIO_BACKEND_NULL for the voice capture device, so the
     * "no microphone" path is reachable on a host that has one. */
    bool voice_null_capture;
    /* Voice aligner modes (CoreAppVoiceConfig aligner_sinc and
     * aligner_crossfade_frames); both off by default. */
    bool voice_aligner_sinc;
    u32 voice_aligner_crossfade_frames;
    /* Voice processor stages to skip (AUDIO_VOICE_PROCESSOR_STAGE_*); 0 runs
     * all of them. */
    u32 voice_bypass_stages;
    /* Device names as the audio device lists report them; NULL or "" opens
     * the default. A name no device has ends the run with REJECTED (exit 2),
     * never with the "no device" result, even without require_device. */
    const char *audio_device_name;
    const char *voice_capture_device_name;
    bool fixed_step;
    bool require_device;
    bool network;
    const CoreAppNetworkHooks *network_hooks;
    u32 max_frames;
    const CoreAppDiagnosticsHooks *diagnostics;
};

BreakRuntimeError core_app_run(const CoreAppConfig *config, int *out_exit_code);
