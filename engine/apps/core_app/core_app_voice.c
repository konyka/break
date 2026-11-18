#include "core_app_voice.h"

#include <core/platform_thread.h>
#include <platform/time.h>

#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

struct CoreAppVoice {
    AudioSystem *playback;
    AudioCapture *capture;
    AudioVoiceAligner *aligner;
    AudioVoiceProcessor *processor;
    BreakVoiceFrame queue[CORE_APP_VOICE_QUEUE_CAPACITY];
    atomic_uint head;
    atomic_uint tail;
    atomic_uint_least64_t produced;
    atomic_uint_least64_t dropped;
    u32 next_sequence;
    PlatformThread worker;
    PlatformThreadId worker_id;
    atomic_int worker_error;
    bool worker_started;
    bool started;
    atomic_bool stop_requested;
    atomic_bool worker_ready;
};

_Static_assert((CORE_APP_VOICE_QUEUE_CAPACITY & (CORE_APP_VOICE_QUEUE_CAPACITY - 1u)) == 0u,
               "Voice queue capacity must be a power of two");

static BreakRuntimeError voice_audio_error(AudioResult result) {
    switch (result) {
        case AUDIO_OK: return BREAK_RUNTIME_OK;
        case AUDIO_INVALID: return BREAK_RUNTIME_INVALID;
        case AUDIO_STALE: return BREAK_RUNTIME_STALE;
        case AUDIO_OVERLOAD: return BREAK_RUNTIME_OOM;
        case AUDIO_REJECTED: return BREAK_RUNTIME_REJECTED;
        case AUDIO_FAILED: return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_FAILED;
}

/* A capture device that cannot be opened or started is an environment fact
 * (no microphone, device busy, device gone), not a defect in the caller. */
static BreakRuntimeError voice_capture_error(AudioResult result) {
    return result == AUDIO_FAILED ? BREAK_RUNTIME_UNAVAILABLE : voice_audio_error(result);
}

BreakRuntimeError core_app_voice_create(const CoreAppVoiceConfig *config,
                                        CoreAppVoice **out) {
    if (!out || !config || !config->playback ||
        config->aligner.tracker.sample_rate != 48000u ||
        config->processor.echo.sample_rate != 48000u) {
        return BREAK_RUNTIME_INVALID;
    }
    CoreAppVoice *voice = (CoreAppVoice *)calloc(1u, sizeof(*voice));
    if (!voice) return BREAK_RUNTIME_OOM;
    voice->playback = config->playback;
    const AudioCaptureConfig capture_config = {
        config->capture_backend, 48000u, 1u, 4096u};
    AudioResult result = audio_capture_create(&capture_config, &voice->capture);
    if (result != AUDIO_OK) {
        free(voice);
        return voice_capture_error(result);
    }
    if (config->use_gcc) {
        result = audio_voice_aligner_create_gcc(&config->aligner, &voice->aligner);
    } else {
        result = audio_voice_aligner_create(&config->aligner, &voice->aligner);
    }
    if (result != AUDIO_OK) {
        audio_capture_destroy(voice->capture);
        free(voice);
        return voice_audio_error(result);
    }
    result = audio_voice_processor_create(&config->processor, &voice->processor);
    if (result != AUDIO_OK) {
        audio_voice_aligner_destroy(voice->aligner);
        audio_capture_destroy(voice->capture);
        free(voice);
        return voice_audio_error(result);
    }
    atomic_store_explicit(&voice->worker_error, (int)BREAK_RUNTIME_OK, memory_order_relaxed);
    *out = voice;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_voice_start(CoreAppVoice *voice) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    if (voice->started) return BREAK_RUNTIME_OK;
    BreakRuntimeError result = voice_audio_error(audio_reference_start(voice->playback));
    if (result != BREAK_RUNTIME_OK) return result;
    result = voice_capture_error(audio_capture_start(voice->capture));
    if (result != BREAK_RUNTIME_OK) {
        (void)audio_reference_stop(voice->playback);
        return result;
    }
    atomic_store_explicit(&voice->worker_error, (int)BREAK_RUNTIME_OK, memory_order_relaxed);
    voice->started = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_voice_inject(CoreAppVoice *voice, const f32 *samples, u32 frames) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    return voice_audio_error(audio_capture_inject(voice->capture, samples, frames));
}

static BreakRuntimeError voice_pump_packet(CoreAppVoice *voice) {
    i16 reference[CORE_APP_VOICE_FRAME_FRAMES];
    i16 capture[CORE_APP_VOICE_FRAME_FRAMES];
    i16 aligned[CORE_APP_VOICE_FRAME_FRAMES];
    u32 reference_frames = 0u;
    u32 capture_frames = 0u;
    AudioResult result = audio_capture_read_i16(voice->capture, capture,
                                                CORE_APP_VOICE_FRAME_FRAMES,
                                                &capture_frames);
    if (result != AUDIO_OK || capture_frames != CORE_APP_VOICE_FRAME_FRAMES) {
        return result == AUDIO_OK ? BREAK_RUNTIME_FAILED : voice_audio_error(result);
    }
    result = audio_reference_read_i16(voice->playback, reference,
                                      CORE_APP_VOICE_FRAME_FRAMES, &reference_frames);
    if (result != AUDIO_OK || reference_frames != CORE_APP_VOICE_FRAME_FRAMES) {
        return result == AUDIO_OK ? BREAK_RUNTIME_FAILED : voice_audio_error(result);
    }
    result = audio_voice_aligner_process_i16(voice->aligner, reference, capture, aligned,
                                             CORE_APP_VOICE_FRAME_FRAMES);
    if (result != AUDIO_OK) return voice_audio_error(result);
    audio_voice_processor_process_i16(voice->processor, aligned, capture,
                                      CORE_APP_VOICE_FRAME_FRAMES);

    BreakVoiceFrame frame;
    memset(&frame, 0, sizeof(frame));
    frame.sequence = voice->next_sequence++;
    frame.sample_rate = 48000u;
    frame.channels = 1u;
    frame.sample_count = CORE_APP_VOICE_FRAME_FRAMES;
    memcpy(frame.samples, capture, sizeof(capture));
    const u32 head = atomic_load_explicit(&voice->head, memory_order_relaxed);
    const u32 tail = atomic_load_explicit(&voice->tail, memory_order_acquire);
    if (head - tail >= CORE_APP_VOICE_QUEUE_CAPACITY) {
        atomic_fetch_add_explicit(&voice->dropped, 1u, memory_order_relaxed);
        return BREAK_RUNTIME_OK;
    }
    voice->queue[head & (CORE_APP_VOICE_QUEUE_CAPACITY - 1u)] = frame;
    atomic_store_explicit(&voice->head, head + 1u, memory_order_release);
    atomic_fetch_add_explicit(&voice->produced, 1u, memory_order_relaxed);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_voice_pump(CoreAppVoice *voice, u32 max_packets) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    if (!voice->started) return BREAK_RUNTIME_REJECTED;
    if (voice->worker_started &&
        !platform_thread_id_equal(platform_thread_current_id(), voice->worker_id)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (max_packets == 0u) return BREAK_RUNTIME_OK;
    if (audio_capture_lost(voice->capture)) return BREAK_RUNTIME_UNAVAILABLE;
    for (u32 packet = 0u; packet < max_packets; ++packet) {
        if (audio_capture_available(voice->capture) < CORE_APP_VOICE_FRAME_FRAMES ||
            audio_reference_available(voice->playback) < CORE_APP_VOICE_FRAME_FRAMES) {
            break;
        }
        const BreakRuntimeError result = voice_pump_packet(voice);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_voice_pop(CoreAppVoice *voice, BreakVoiceFrame *out,
                                     bool *out_ready) {
    if (!voice || !out || !out_ready) return BREAK_RUNTIME_INVALID;
    *out_ready = false;
    const u32 tail = atomic_load_explicit(&voice->tail, memory_order_relaxed);
    const u32 head = atomic_load_explicit(&voice->head, memory_order_acquire);
    if (head == tail) return BREAK_RUNTIME_OK;
    *out = voice->queue[tail & (CORE_APP_VOICE_QUEUE_CAPACITY - 1u)];
    atomic_store_explicit(&voice->tail, tail + 1u, memory_order_release);
    *out_ready = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_voice_stats(CoreAppVoice *voice, CoreAppVoiceStats *out) {
    if (!voice || !out) return BREAK_RUNTIME_INVALID;
    CoreAppVoiceStats stats = {
        atomic_load_explicit(&voice->produced, memory_order_relaxed),
        atomic_load_explicit(&voice->dropped, memory_order_relaxed),
        audio_capture_overruns(voice->capture),
        audio_reference_overruns(voice->playback),
    };
    *out = stats;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_voice_worker_error(CoreAppVoice *voice) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    return (BreakRuntimeError)atomic_load_explicit(&voice->worker_error, memory_order_acquire);
}

const char *core_app_voice_capture_backend(const CoreAppVoice *voice) {
    return voice ? audio_capture_backend_name(voice->capture) : "none";
}

bool core_app_voice_capture_name(const CoreAppVoice *voice, char *out, usize capacity) {
    return audio_capture_device_name(voice ? voice->capture : NULL, out, capacity);
}

BreakRuntimeError core_app_voice_simulate_capture_event(CoreAppVoice *voice,
                                                        AudioCaptureEvent event) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    return voice_audio_error(audio_capture_simulate_event(voice->capture, event));
}

static PLATFORM_THREAD_RET voice_worker_main(PLATFORM_THREAD_ARG argument) {
    CoreAppVoice *voice = (CoreAppVoice *)argument;
    voice->worker_id = platform_thread_current_id();
    atomic_store_explicit(&voice->worker_ready, true, memory_order_release);
    while (!atomic_load_explicit(&voice->stop_requested, memory_order_acquire)) {
        const u64 before = atomic_load_explicit(&voice->produced, memory_order_relaxed);
        const BreakRuntimeError result = core_app_voice_pump(voice, 4u);
        if (result != BREAK_RUNTIME_OK) {
            atomic_store_explicit(&voice->worker_error, (int)result, memory_order_release);
            break;
        }
        if (atomic_load_explicit(&voice->produced, memory_order_relaxed) == before) {
            time_sleep_us(1000u);
        }
    }
    return PLATFORM_THREAD_RETURN;
}

BreakRuntimeError core_app_voice_start_threaded(CoreAppVoice *voice) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    if (voice->started || voice->worker_started) return BREAK_RUNTIME_REJECTED;
    BreakRuntimeError result = core_app_voice_start(voice);
    if (result != BREAK_RUNTIME_OK) return result;
    atomic_store_explicit(&voice->stop_requested, false, memory_order_release);
    atomic_store_explicit(&voice->worker_ready, false, memory_order_relaxed);
    voice->worker_started = true;
    if (platform_thread_create(&voice->worker, voice_worker_main, voice)) {
        while (!atomic_load_explicit(&voice->worker_ready, memory_order_acquire)) {
            platform_thread_yield();
        }
        return BREAK_RUNTIME_OK;
    }
    voice->worker_started = false;
    (void)core_app_voice_stop(voice);
    return BREAK_RUNTIME_FAILED;
}

BreakRuntimeError core_app_voice_stop(CoreAppVoice *voice) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    if (voice->worker_started) {
        atomic_store_explicit(&voice->stop_requested, true, memory_order_release);
        platform_thread_join(voice->worker);
        voice->worker_started = false;
        atomic_store_explicit(&voice->worker_ready, false, memory_order_relaxed);
    }
    BreakRuntimeError result =
        (BreakRuntimeError)atomic_load_explicit(&voice->worker_error, memory_order_acquire);
    if (voice->started) {
        const AudioResult capture_result = audio_capture_stop(voice->capture);
        const AudioResult reference_result = audio_reference_stop(voice->playback);
        voice->started = false;
        if (result == BREAK_RUNTIME_OK && capture_result != AUDIO_OK) {
            result = voice_audio_error(capture_result);
        }
        if (result == BREAK_RUNTIME_OK && reference_result != AUDIO_OK) {
            result = voice_audio_error(reference_result);
        }
    }
    return result;
}

void core_app_voice_destroy(CoreAppVoice *voice) {
    if (!voice) return;
    (void)core_app_voice_stop(voice);
    audio_voice_processor_destroy(voice->processor);
    audio_voice_aligner_destroy(voice->aligner);
    audio_capture_destroy(voice->capture);
    free(voice);
}
