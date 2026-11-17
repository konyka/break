#include "audio_capture.h"

#include <math.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
#include <miniaudio.h>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

/* One producer (the device callback, or the injecting thread for FAKE) owns
 * `head`; the reader owns `tail`. Both run free as u32, so the ring size
 * must divide 2^32 (a power of two).
 *
 * Two device slots let a reopen open the new device before closing the old
 * one; `active` names the open slot, and notifications from the other slot
 * (the one being closed) are ignored. Only one device runs at a time, so the
 * ring keeps a single producer. */
struct AudioCapture {
    AudioBackend backend;
    u32 sample_rate;
    u32 channels;
    u32 ring_frames;
    i16 *ring;
    atomic_uint head;
    atomic_uint tail;
    atomic_uint_least64_t overruns;
    atomic_uint_least64_t reroutes;
    atomic_bool wanted; /* start requested and not stopped since */
    atomic_bool lost;   /* stopped while wanted, without a stop request */
    atomic_uint active;
    bool context_ready;
    bool device_ready;
    char device_name[128];
    ma_context context;
    ma_device devices[2];
};

static i16 capture_sample(f32 x) {
    if (!isfinite(x)) return 0;
    if (x > 1.0f) x = 1.0f;
    if (x < -1.0f) x = -1.0f;
    return (i16)lrintf(x * 32767.0f);
}

/* Producer side: copies what fits, counts the rest as overruns. Never
 * blocks, allocates or logs. */
static void capture_write(AudioCapture *capture, const f32 *samples, u32 frames) {
    u32 head = atomic_load_explicit(&capture->head, memory_order_relaxed);
    u32 tail = atomic_load_explicit(&capture->tail, memory_order_acquire);
    u32 room = capture->ring_frames - (head - tail);
    u32 count = frames < room ? frames : room;
    for (u32 i = 0; i < count; ++i) {
        i16 *dst = capture->ring +
                   (usize)((head + i) & (capture->ring_frames - 1u)) * capture->channels;
        for (u32 c = 0; c < capture->channels; ++c) {
            dst[c] = capture_sample(samples[(usize)i * capture->channels + c]);
        }
    }
    atomic_store_explicit(&capture->head, head + count, memory_order_release);
    if (count < frames) {
        atomic_fetch_add_explicit(&capture->overruns, (u64)(frames - count),
                                  memory_order_relaxed);
    }
}

static void capture_data_callback(ma_device *device, void *output, const void *input,
                                  ma_uint32 frames) {
    (void)output;
    AudioCapture *capture = (AudioCapture *)device->pUserData;
    if (input) capture_write(capture, (const f32 *)input, (u32)frames);
}

/* Device thread (or the simulating thread for FAKE). A stop is a loss only
 * while capture is wanted: requested stops clear `wanted` first. */
static void capture_on_event(AudioCapture *capture, AudioCaptureEvent event) {
    if (event == AUDIO_CAPTURE_EVENT_DEVICE_LOST) {
        if (atomic_load_explicit(&capture->wanted, memory_order_acquire)) {
            atomic_store_explicit(&capture->lost, true, memory_order_release);
        }
    } else {
        atomic_fetch_add_explicit(&capture->reroutes, 1u, memory_order_relaxed);
    }
}

static void capture_notification_callback(const ma_device_notification *notification) {
    ma_device *device = notification->pDevice;
    AudioCapture *capture = (AudioCapture *)device->pUserData;
    u32 active = atomic_load_explicit(&capture->active, memory_order_acquire);
    if (device != &capture->devices[active]) return;
    if (notification->type == ma_device_notification_type_stopped) {
        capture_on_event(capture, AUDIO_CAPTURE_EVENT_DEVICE_LOST);
    } else if (notification->type == ma_device_notification_type_rerouted) {
        capture_on_event(capture, AUDIO_CAPTURE_EVENT_REROUTED);
    }
}

/* Copies a NUL-terminated name into dst, truncated to fit. */
static void capture_copy_name(char *dst, usize capacity, const char *src) {
    usize n = strlen(src);
    if (n >= capacity) n = capacity - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static bool capture_backend_valid(AudioBackend backend) {
    return backend >= AUDIO_BACKEND_DEFAULT && backend <= AUDIO_BACKEND_FAKE;
}

/* A context for a device backend: NULL selects miniaudio's null backend. */
static ma_result capture_context_init(AudioBackend backend, ma_context *context) {
    if (backend == AUDIO_BACKEND_NULL) {
        ma_backend null_backend = ma_backend_null;
        return ma_context_init(&null_backend, 1, NULL, context);
    }
    return ma_context_init(NULL, 0, NULL, context);
}

u32 audio_capture_list_devices(AudioBackend backend, AudioDeviceInfo *out, u32 capacity) {
    if (!capture_backend_valid(backend) || backend == AUDIO_BACKEND_FAKE ||
        (!out && capacity > 0u)) {
        return 0u;
    }
    ma_context context;
    if (capture_context_init(backend, &context) != MA_SUCCESS) return 0u;
    ma_device_info *infos = NULL;
    ma_uint32 count = 0;
    if (ma_context_get_devices(&context, NULL, NULL, &infos, &count) != MA_SUCCESS) {
        ma_context_uninit(&context);
        return 0u;
    }
    for (u32 i = 0; i < count && i < capacity; ++i) {
        memset(&out[i], 0, sizeof(out[i]));
        capture_copy_name(out[i].name, sizeof(out[i].name), infos[i].name);
        snprintf(out[i].id, sizeof(out[i].id), "%u", i);
        out[i].is_default = infos[i].isDefault != 0;
    }
    ma_context_uninit(&context);
    return (u32)count;
}

/* Opens the named device (NULL: the default) in `slot`, stopped, and on
 * success copies its name into capture->device_name. REJECTED when no device
 * has the name, FAILED when it does not open; the slot and the name are then
 * left as they were. */
static AudioResult capture_open_device(AudioCapture *capture, u32 slot, const char *device_name) {
    ma_device_id chosen;
    bool found = false;
    if (device_name) {
        ma_device_info *infos = NULL;
        ma_uint32 count = 0;
        if (ma_context_get_devices(&capture->context, NULL, NULL, &infos, &count) == MA_SUCCESS) {
            for (ma_uint32 i = 0; i < count && !found; ++i) {
                if (strcmp(infos[i].name, device_name) == 0) {
                    chosen = infos[i].id;
                    found = true;
                }
            }
        }
        if (!found) return AUDIO_REJECTED;
    }
    ma_device_config device_config = ma_device_config_init(ma_device_type_capture);
    device_config.capture.pDeviceID = found ? &chosen : NULL;
    device_config.capture.format = ma_format_f32;
    device_config.capture.channels = capture->channels;
    device_config.sampleRate = capture->sample_rate;
    device_config.dataCallback = capture_data_callback;
    device_config.notificationCallback = capture_notification_callback;
    device_config.pUserData = capture;
    ma_device *device = &capture->devices[slot];
    if (ma_device_init(&capture->context, &device_config, device) != MA_SUCCESS) {
        return AUDIO_FAILED;
    }
    ma_device_info info;
    memset(&info, 0, sizeof(info));
    capture->device_name[0] = '\0';
    if (ma_device_get_info(device, ma_device_type_capture, &info) == MA_SUCCESS) {
        capture_copy_name(capture->device_name, sizeof(capture->device_name), info.name);
    }
    return AUDIO_OK;
}

static ma_device *capture_device(AudioCapture *capture) {
    return &capture->devices[atomic_load_explicit(&capture->active, memory_order_relaxed)];
}

/* Lost by notification, or a device that stopped while wanted without
 * posting one (miniaudio posts no stop notification when the backend fails
 * to stop a stream whose device was unplugged). */
static bool capture_is_lost(const AudioCapture *capture) {
    if (atomic_load_explicit(&capture->lost, memory_order_acquire)) return true;
    if (!capture->device_ready || !atomic_load_explicit(&capture->wanted, memory_order_acquire)) {
        return false;
    }
    u32 active = atomic_load_explicit(&capture->active, memory_order_relaxed);
    return ma_device_get_state(&capture->devices[active]) == ma_device_state_stopped;
}

AudioResult audio_capture_create(const AudioCaptureConfig *config, AudioCapture **out) {
    return audio_capture_create_named(config, NULL, out);
}

AudioResult audio_capture_create_named(const AudioCaptureConfig *config, const char *device_name,
                                       AudioCapture **out) {
    bool named = device_name && device_name[0] != '\0';
    if (!config || !out || !capture_backend_valid(config->backend) ||
        config->sample_rate < AUDIO_CAPTURE_MIN_RATE ||
        config->sample_rate > AUDIO_CAPTURE_MAX_RATE ||
        (config->channels != 1u && config->channels != 2u) || config->ring_frames == 0u ||
        config->ring_frames > AUDIO_CAPTURE_MAX_RING_FRAMES ||
        (config->ring_frames & (config->ring_frames - 1u)) != 0u) {
        return AUDIO_INVALID;
    }
    if (named && config->backend == AUDIO_BACKEND_FAKE) return AUDIO_REJECTED;
    AudioCapture *capture = (AudioCapture *)calloc(1, sizeof(*capture));
    if (!capture) return AUDIO_OVERLOAD;
    capture->ring = (i16 *)calloc((usize)config->ring_frames * config->channels, sizeof(i16));
    if (!capture->ring) {
        free(capture);
        return AUDIO_OVERLOAD;
    }
    capture->backend = config->backend;
    capture->sample_rate = config->sample_rate;
    capture->channels = config->channels;
    capture->ring_frames = config->ring_frames;
    atomic_init(&capture->head, 0u);
    atomic_init(&capture->tail, 0u);
    atomic_init(&capture->overruns, 0u);
    atomic_init(&capture->reroutes, 0u);
    atomic_init(&capture->wanted, false);
    atomic_init(&capture->lost, false);
    atomic_init(&capture->active, 0u);
    if (config->backend == AUDIO_BACKEND_FAKE) {
        capture_copy_name(capture->device_name, sizeof(capture->device_name), "fake");
    } else {
        /* the context lives as long as the device: a device id points into
         * the context's enumeration */
        if (capture_context_init(config->backend, &capture->context) != MA_SUCCESS) {
            audio_capture_destroy(capture);
            return AUDIO_FAILED;
        }
        capture->context_ready = true;
        AudioResult result = capture_open_device(capture, 0u, named ? device_name : NULL);
        if (result != AUDIO_OK) {
            audio_capture_destroy(capture);
            return result;
        }
        capture->device_ready = true;
    }
    *out = capture;
    return AUDIO_OK;
}

void audio_capture_destroy(AudioCapture *capture) {
    if (!capture) return;
    /* uninit stops a running device and waits for its callback */
    if (capture->device_ready) ma_device_uninit(capture_device(capture));
    if (capture->context_ready) ma_context_uninit(&capture->context);
    free(capture->ring);
    free(capture);
}

AudioResult audio_capture_start(AudioCapture *capture) {
    if (!capture) return AUDIO_INVALID;
    if (capture_is_lost(capture)) return AUDIO_FAILED;
    if (atomic_load_explicit(&capture->wanted, memory_order_acquire)) return AUDIO_OK;
    /* set after the start, so a device still starting never reads as lost */
    if (capture->device_ready && ma_device_start(capture_device(capture)) != MA_SUCCESS) {
        return AUDIO_FAILED;
    }
    atomic_store_explicit(&capture->wanted, true, memory_order_release);
    return AUDIO_OK;
}

AudioResult audio_capture_stop(AudioCapture *capture) {
    if (!capture) return AUDIO_INVALID;
    if (!atomic_load_explicit(&capture->wanted, memory_order_acquire)) return AUDIO_OK;
    /* cleared before the stop so its notification is not a loss */
    atomic_store_explicit(&capture->wanted, false, memory_order_release);
    if (capture->device_ready && ma_device_stop(capture_device(capture)) != MA_SUCCESS) {
        atomic_store_explicit(&capture->wanted, true, memory_order_release);
        return AUDIO_FAILED;
    }
    return AUDIO_OK;
}

bool audio_capture_lost(const AudioCapture *capture) {
    return capture && capture_is_lost(capture);
}

u64 audio_capture_reroutes(const AudioCapture *capture) {
    return capture ? atomic_load_explicit(&capture->reroutes, memory_order_relaxed) : 0u;
}

AudioResult audio_capture_reopen(AudioCapture *capture, const char *device_name) {
    if (!capture) return AUDIO_INVALID;
    bool named = device_name && device_name[0] != '\0';
    if (capture->backend == AUDIO_BACKEND_FAKE) {
        if (named) return AUDIO_REJECTED;
        atomic_store_explicit(&capture->lost, false, memory_order_release);
        return AUDIO_OK;
    }
    u32 old_slot = atomic_load_explicit(&capture->active, memory_order_relaxed);
    u32 new_slot = 1u - old_slot;
    AudioResult result = capture_open_device(capture, new_slot, named ? device_name : NULL);
    if (result != AUDIO_OK) return result;
    /* from here the old device's notifications are ignored; its uninit
     * waits for its last callback, so the new one becomes the only
     * producer */
    atomic_store_explicit(&capture->active, new_slot, memory_order_release);
    ma_device_uninit(&capture->devices[old_slot]);
    atomic_store_explicit(&capture->lost, false, memory_order_release);
    if (atomic_load_explicit(&capture->wanted, memory_order_acquire) &&
        ma_device_start(&capture->devices[new_slot]) != MA_SUCCESS) {
        /* the old device is closed already: report the new one as lost */
        atomic_store_explicit(&capture->lost, true, memory_order_release);
        return AUDIO_FAILED;
    }
    return AUDIO_OK;
}

AudioResult audio_capture_simulate_event(AudioCapture *capture, AudioCaptureEvent event) {
    if (!capture || (event != AUDIO_CAPTURE_EVENT_DEVICE_LOST &&
                     event != AUDIO_CAPTURE_EVENT_REROUTED)) {
        return AUDIO_INVALID;
    }
    if (capture->backend == AUDIO_BACKEND_DEFAULT) return AUDIO_REJECTED;
    capture_on_event(capture, event);
    return AUDIO_OK;
}

bool audio_capture_device_name(const AudioCapture *capture, char *out, usize capacity) {
    if (!out || capacity == 0u) return false;
    out[0] = '\0';
    if (!capture || capture->device_name[0] == '\0') return false;
    capture_copy_name(out, capacity, capture->device_name);
    return true;
}

bool audio_capture_running(const AudioCapture *capture) {
    return capture && atomic_load_explicit(&capture->wanted, memory_order_acquire) &&
           !capture_is_lost(capture);
}

AudioResult audio_capture_read_i16(AudioCapture *capture, i16 *out, u32 max_frames,
                                   u32 *out_frames) {
    if (!capture || !out || !out_frames) return AUDIO_INVALID;
    u32 tail = atomic_load_explicit(&capture->tail, memory_order_relaxed);
    u32 head = atomic_load_explicit(&capture->head, memory_order_acquire);
    u32 count = head - tail < max_frames ? head - tail : max_frames;
    for (u32 i = 0; i < count; ++i) {
        const i16 *src = capture->ring +
                         (usize)((tail + i) & (capture->ring_frames - 1u)) * capture->channels;
        memcpy(out + (usize)i * capture->channels, src, capture->channels * sizeof(i16));
    }
    atomic_store_explicit(&capture->tail, tail + count, memory_order_release);
    *out_frames = count;
    return AUDIO_OK;
}

u32 audio_capture_available(const AudioCapture *capture) {
    if (!capture) return 0u;
    return atomic_load_explicit(&capture->head, memory_order_acquire) -
           atomic_load_explicit(&capture->tail, memory_order_acquire);
}

u64 audio_capture_overruns(const AudioCapture *capture) {
    return capture ? atomic_load_explicit(&capture->overruns, memory_order_relaxed) : 0u;
}

AudioResult audio_capture_inject(AudioCapture *capture, const f32 *samples, u32 frames) {
    if (!capture || !samples) return AUDIO_INVALID;
    if (capture->backend != AUDIO_BACKEND_FAKE || !audio_capture_running(capture)) {
        return AUDIO_REJECTED;
    }
    capture_write(capture, samples, frames);
    return AUDIO_OK;
}
