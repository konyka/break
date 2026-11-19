#include "core_app_voice.h"

#include <core/platform_thread.h>
#include <platform/time.h>

#include <stdatomic.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define CORE_APP_VOICE_DRIFT_FIFO_FRAMES 4096u

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
    char capture_device_name[128];
    u32 reopen_interval_ms;
    u32 max_reopen_failures;
    u32 consecutive_reopen_failures;
    bool reopen_attempted;
    u64 last_reopen_us;
    atomic_uint_least64_t capture_recoveries;
    atomic_uint_least64_t capture_reopen_failures;
    u64 seen_playback_recoveries;
    atomic_uint_least64_t playback_recoveries;
    /* One-slot switch mailbox: the requester writes the name while pending
     * is false, the pumping thread reads it while pending is true. */
    char requested_name[128];
    atomic_bool switch_pending;
    atomic_uint_least64_t capture_switches;
    atomic_uint_least64_t capture_switch_rejected;
    atomic_uint_least64_t capture_switch_failures;
    /* Drift compensation (pumping thread), NULL when off: the playback
     * reference resampled with the current ratio, waiting for alignment. */
    AudioDriftCompensator *drift;
    i16 drift_fifo[CORE_APP_VOICE_DRIFT_FIFO_FRAMES];
    u32 drift_fifo_frames;
    u32 drift_observe_packets;
    u32 drift_packets_since_observe;
    u32 drift_min_samples;
    u32 drift_accepted;
    bool drift_skip_next;
    u64 drift_seen_updates;
    u64 capture_frames_total;
    atomic_uint_least64_t drift_corrections;
    atomic_int_least64_t drift_correction_ppb;
    PlatformThread worker;
    PlatformThreadId worker_id;
    atomic_int worker_error;
    bool worker_started;
    bool started;
    atomic_bool stop_requested;
    atomic_bool worker_ready;
};

_Static_assert(sizeof(((CoreAppVoice *)0)->requested_name) ==
                   sizeof(((CoreAppVoice *)0)->capture_device_name),
               "A switched name is copied whole into the stored device name");
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
    const char *name = config->capture_device_name ? config->capture_device_name : "";
    const usize name_length = strlen(name);
    if (name_length >= sizeof(((CoreAppVoice *)0)->capture_device_name)) {
        return BREAK_RUNTIME_REJECTED;
    }
    CoreAppVoice *voice = (CoreAppVoice *)calloc(1u, sizeof(*voice));
    if (!voice) return BREAK_RUNTIME_OOM;
    memcpy(voice->capture_device_name, name, name_length + 1u);
    voice->playback = config->playback;
    voice->reopen_interval_ms = config->reopen_interval_ms;
    voice->max_reopen_failures = config->max_reopen_failures;
    voice->seen_playback_recoveries = audio_system_recoveries(config->playback);
    const AudioCaptureConfig capture_config = {
        config->capture_backend, 48000u, 1u, 4096u};
    AudioResult result = audio_capture_create_named(&capture_config, voice->capture_device_name,
                                                    &voice->capture);
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
    if (result == AUDIO_OK && config->drift_enabled) {
        result = config->drift_observe_packets == 0u || config->drift_observe_packets > 1000u
                     ? AUDIO_INVALID
                     : audio_drift_compensator_create(&config->drift, &voice->drift);
    }
    if (result != AUDIO_OK) {
        audio_voice_processor_destroy(voice->processor);
        audio_voice_aligner_destroy(voice->aligner);
        audio_capture_destroy(voice->capture);
        free(voice);
        return voice_audio_error(result);
    }
    voice->drift_observe_packets = config->drift_observe_packets;
    voice->drift_min_samples = config->drift.min_samples;
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

/* A new device has its own clock: the ratio, the measurements and the
 * resampled reference that was waiting all start over. */
static void voice_drift_reset(CoreAppVoice *voice) {
    if (!voice->drift) return;
    audio_drift_compensator_reset(voice->drift);
    voice->drift_fifo_frames = 0u;
    voice->drift_packets_since_observe = 0u;
    voice->drift_accepted = 0u;
    voice->drift_skip_next = false;
    voice->drift_seen_updates = audio_voice_aligner_updates(voice->aligner);
    atomic_store_explicit(&voice->drift_correction_ppb, 0, memory_order_relaxed);
}

static bool voice_reference_ready(const CoreAppVoice *voice) {
    if (voice->drift && voice->drift_fifo_frames >= CORE_APP_VOICE_FRAME_FRAMES) return true;
    return audio_reference_available(voice->playback) >= CORE_APP_VOICE_FRAME_FRAMES;
}

/* One packet of reference: the raw read, or with drift compensation the
 * oldest resampled frames, refilled from one raw read when short. */
static AudioResult voice_read_reference(CoreAppVoice *voice, i16 *out) {
    u32 frames = 0u;
    if (!voice->drift) {
        const AudioResult result = audio_reference_read_i16(voice->playback, out,
                                                            CORE_APP_VOICE_FRAME_FRAMES, &frames);
        return result == AUDIO_OK && frames != CORE_APP_VOICE_FRAME_FRAMES ? AUDIO_FAILED
                                                                           : result;
    }
    while (voice->drift_fifo_frames < CORE_APP_VOICE_FRAME_FRAMES) {
        i16 raw[CORE_APP_VOICE_FRAME_FRAMES];
        AudioResult result = audio_reference_read_i16(voice->playback, raw,
                                                      CORE_APP_VOICE_FRAME_FRAMES, &frames);
        if (result != AUDIO_OK) return result;
        if (frames != CORE_APP_VOICE_FRAME_FRAMES) return AUDIO_FAILED;
        u32 produced = 0u;
        result = audio_drift_compensator_process_i16(
            voice->drift, raw, frames, voice->drift_fifo + voice->drift_fifo_frames,
            CORE_APP_VOICE_DRIFT_FIFO_FRAMES - voice->drift_fifo_frames, &produced);
        if (result != AUDIO_OK) return result;
        voice->drift_fifo_frames += produced;
    }
    memcpy(out, voice->drift_fifo, CORE_APP_VOICE_FRAME_FRAMES * sizeof(*out));
    voice->drift_fifo_frames -= CORE_APP_VOICE_FRAME_FRAMES;
    memmove(voice->drift_fifo, voice->drift_fifo + CORE_APP_VOICE_FRAME_FRAMES,
            voice->drift_fifo_frames * sizeof(*voice->drift_fifo));
    return AUDIO_OK;
}

/* After the aligner updated while locked, every drift_observe_packets
 * packets: one delay measurement; every min_samples accepted ones: a ratio
 * update. The first measurement after an update still covers the old ratio. */
static void voice_drift_observe(CoreAppVoice *voice) {
    if (!voice->drift) return;
    const u64 updates = audio_voice_aligner_updates(voice->aligner);
    const bool updated = updates != voice->drift_seen_updates;
    voice->drift_seen_updates = updates;
    if (++voice->drift_packets_since_observe < voice->drift_observe_packets) return;
    if (!updated || !audio_voice_aligner_locked(voice->aligner)) return;
    voice->drift_packets_since_observe = 0u;
    if (voice->drift_skip_next) {
        voice->drift_skip_next = false;
        return;
    }
    if (!audio_drift_compensator_observe(voice->drift, voice->capture_frames_total,
                                         audio_voice_aligner_delay(voice->aligner),
                                         audio_voice_aligner_correlation(voice->aligner))) {
        return;
    }
    if (++voice->drift_accepted < voice->drift_min_samples) return;
    voice->drift_accepted = 0u;
    if (!audio_drift_compensator_update(voice->drift)) return;
    voice->drift_skip_next = true;
    atomic_fetch_add_explicit(&voice->drift_corrections, 1u, memory_order_relaxed);
    atomic_store_explicit(&voice->drift_correction_ppb,
                          (i64)llround(audio_drift_compensator_correction_ppm(voice->drift) * 1000.0),
                          memory_order_relaxed);
}

static BreakRuntimeError voice_pump_packet(CoreAppVoice *voice) {
    i16 reference[CORE_APP_VOICE_FRAME_FRAMES];
    i16 capture[CORE_APP_VOICE_FRAME_FRAMES];
    i16 aligned[CORE_APP_VOICE_FRAME_FRAMES];
    u32 capture_frames = 0u;
    AudioResult result = audio_capture_read_i16(voice->capture, capture,
                                                CORE_APP_VOICE_FRAME_FRAMES,
                                                &capture_frames);
    if (result != AUDIO_OK || capture_frames != CORE_APP_VOICE_FRAME_FRAMES) {
        return result == AUDIO_OK ? BREAK_RUNTIME_FAILED : voice_audio_error(result);
    }
    result = voice_read_reference(voice, reference);
    if (result != AUDIO_OK) return voice_audio_error(result);
    result = audio_voice_aligner_process_i16(voice->aligner, reference, capture, aligned,
                                             CORE_APP_VOICE_FRAME_FRAMES);
    if (result != AUDIO_OK) return voice_audio_error(result);
    voice->capture_frames_total += CORE_APP_VOICE_FRAME_FRAMES;
    voice_drift_observe(voice);
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

/* The reference rendered while nothing was captured has no matching
 * capture, and frames captured before the loss end before the gap; keeping
 * either would misalign echo cancellation after a reopen. The aligner keeps
 * its delay estimate and settles again on the new frames. */
static void voice_discard_stale(CoreAppVoice *voice) {
    i16 scratch[CORE_APP_VOICE_FRAME_FRAMES];
    u32 frames = 0u;
    while (audio_capture_available(voice->capture) > 0u &&
           audio_capture_read_i16(voice->capture, scratch, CORE_APP_VOICE_FRAME_FRAMES,
                                  &frames) == AUDIO_OK &&
           frames > 0u) {
    }
    while (audio_reference_available(voice->playback) > 0u &&
           audio_reference_read_i16(voice->playback, scratch, CORE_APP_VOICE_FRAME_FRAMES,
                                    &frames) == AUDIO_OK &&
           frames > 0u) {
    }
}

/* Pumping thread only. OK when the capture runs again; UNAVAILABLE when
 * recovery is off or the consecutive refusals reached the limit; REJECTED
 * while the interval since the last attempt runs, or when an attempt was
 * refused below the limit. */
static BreakRuntimeError voice_recover_capture(CoreAppVoice *voice) {
    if (voice->max_reopen_failures == 0u ||
        voice->consecutive_reopen_failures >= voice->max_reopen_failures) {
        return BREAK_RUNTIME_UNAVAILABLE;
    }
    const u64 now = time_microseconds();
    if (voice->reopen_attempted &&
        now - voice->last_reopen_us < (u64)voice->reopen_interval_ms * 1000u) {
        return BREAK_RUNTIME_REJECTED;
    }
    voice->reopen_attempted = true;
    voice->last_reopen_us = now;
    AudioResult reopened = audio_capture_reopen(voice->capture, voice->capture_device_name);
    if (reopened == AUDIO_REJECTED && voice->capture_device_name[0] != '\0') {
        /* the selected input is gone: the default keeps voice running */
        reopened = audio_capture_reopen(voice->capture, NULL);
    }
    if (reopened != AUDIO_OK) {
        voice->consecutive_reopen_failures++;
        atomic_fetch_add_explicit(&voice->capture_reopen_failures, 1u, memory_order_relaxed);
        return voice->consecutive_reopen_failures >= voice->max_reopen_failures
                   ? BREAK_RUNTIME_UNAVAILABLE
                   : BREAK_RUNTIME_REJECTED;
    }
    voice->consecutive_reopen_failures = 0u;
    voice_discard_stale(voice);
    voice_drift_reset(voice);
    audio_voice_processor_reset(voice->processor);
    atomic_fetch_add_explicit(&voice->capture_recoveries, 1u, memory_order_relaxed);
    return BREAK_RUNTIME_OK;
}

/* After the playback device was reopened the reference ring holds only
 * frames rendered since, while the capture ring also holds the frames
 * captured during the gap, which have no reference. The oldest capture
 * frames beyond the reference backlog are dropped so both start together,
 * and the processor forgets the echo path it learned before the gap. */
static void voice_follow_playback_reopen(CoreAppVoice *voice) {
    const u64 recoveries = audio_system_recoveries(voice->playback);
    if (recoveries == voice->seen_playback_recoveries) return;
    voice->seen_playback_recoveries = recoveries;
    voice_drift_reset(voice);
    i16 scratch[CORE_APP_VOICE_FRAME_FRAMES];
    for (;;) {
        const u32 capture = audio_capture_available(voice->capture);
        const u32 reference = audio_reference_available(voice->playback);
        if (capture <= reference) break;
        u32 drop = capture - reference;
        if (drop > CORE_APP_VOICE_FRAME_FRAMES) drop = CORE_APP_VOICE_FRAME_FRAMES;
        u32 frames = 0u;
        if (audio_capture_read_i16(voice->capture, scratch, drop, &frames) != AUDIO_OK ||
            frames == 0u) {
            break;
        }
    }
    audio_voice_processor_reset(voice->processor);
    atomic_fetch_add_explicit(&voice->playback_recoveries, 1u, memory_order_relaxed);
}

BreakRuntimeError core_app_voice_request_capture_device(CoreAppVoice *voice, const char *name) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    const char *text = name ? name : "";
    const usize length = strlen(text);
    if (!voice->started || length >= sizeof(voice->requested_name)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (atomic_load_explicit(&voice->switch_pending, memory_order_acquire)) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    memcpy(voice->requested_name, text, length + 1u);
    atomic_store_explicit(&voice->switch_pending, true, memory_order_release);
    return BREAK_RUNTIME_OK;
}

/* Pumping thread only. An unknown name keeps the old device; a failure that
 * left the capture lost is handled by the recovery of the stored name. */
static void voice_switch_capture(CoreAppVoice *voice) {
    if (!atomic_load_explicit(&voice->switch_pending, memory_order_acquire)) return;
    const AudioResult result = audio_capture_reopen(voice->capture, voice->requested_name);
    if (result == AUDIO_OK) {
        memcpy(voice->capture_device_name, voice->requested_name,
               sizeof(voice->capture_device_name));
        voice->consecutive_reopen_failures = 0u;
        voice_discard_stale(voice);
        voice_drift_reset(voice);
        audio_voice_processor_reset(voice->processor);
        atomic_fetch_add_explicit(&voice->capture_switches, 1u, memory_order_relaxed);
    } else if (result == AUDIO_REJECTED) {
        atomic_fetch_add_explicit(&voice->capture_switch_rejected, 1u, memory_order_relaxed);
    } else {
        atomic_fetch_add_explicit(&voice->capture_switch_failures, 1u, memory_order_relaxed);
    }
    atomic_store_explicit(&voice->switch_pending, false, memory_order_release);
}

BreakRuntimeError core_app_voice_pump(CoreAppVoice *voice, u32 max_packets) {
    if (!voice) return BREAK_RUNTIME_INVALID;
    if (!voice->started) return BREAK_RUNTIME_REJECTED;
    if (voice->worker_started &&
        !platform_thread_id_equal(platform_thread_current_id(), voice->worker_id)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (max_packets == 0u) return BREAK_RUNTIME_OK;
    voice_switch_capture(voice);
    if (audio_capture_lost(voice->capture)) {
        const BreakRuntimeError recovered = voice_recover_capture(voice);
        if (recovered == BREAK_RUNTIME_REJECTED) return BREAK_RUNTIME_OK;
        if (recovered != BREAK_RUNTIME_OK) return recovered;
    }
    voice_follow_playback_reopen(voice);
    for (u32 packet = 0u; packet < max_packets; ++packet) {
        if (audio_capture_available(voice->capture) < CORE_APP_VOICE_FRAME_FRAMES ||
            !voice_reference_ready(voice)) {
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
        atomic_load_explicit(&voice->capture_recoveries, memory_order_relaxed),
        atomic_load_explicit(&voice->capture_reopen_failures, memory_order_relaxed),
        atomic_load_explicit(&voice->playback_recoveries, memory_order_relaxed),
        atomic_load_explicit(&voice->capture_switches, memory_order_relaxed),
        atomic_load_explicit(&voice->capture_switch_rejected, memory_order_relaxed),
        atomic_load_explicit(&voice->capture_switch_failures, memory_order_relaxed),
        atomic_load_explicit(&voice->drift_corrections, memory_order_relaxed),
        atomic_load_explicit(&voice->drift_correction_ppb, memory_order_relaxed),
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
    audio_drift_compensator_destroy(voice->drift);
    audio_voice_processor_destroy(voice->processor);
    audio_voice_aligner_destroy(voice->aligner);
    audio_capture_destroy(voice->capture);
    free(voice);
}
