#include "audio_capture.h"

#include <math.h>
#include <stdatomic.h>
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
 * must divide 2^32 (a power of two). */
struct AudioCapture {
    AudioBackend backend;
    u32 channels;
    u32 ring_frames;
    i16 *ring;
    atomic_uint head;
    atomic_uint tail;
    atomic_uint_least64_t overruns;
    atomic_bool running;
    bool context_ready;
    bool device_ready;
    ma_context context;
    ma_device device;
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

AudioResult audio_capture_create(const AudioCaptureConfig *config, AudioCapture **out) {
    if (!config || !out || config->backend < AUDIO_BACKEND_DEFAULT ||
        config->backend > AUDIO_BACKEND_FAKE ||
        config->sample_rate < AUDIO_CAPTURE_MIN_RATE ||
        config->sample_rate > AUDIO_CAPTURE_MAX_RATE ||
        (config->channels != 1u && config->channels != 2u) || config->ring_frames == 0u ||
        config->ring_frames > AUDIO_CAPTURE_MAX_RING_FRAMES ||
        (config->ring_frames & (config->ring_frames - 1u)) != 0u) {
        return AUDIO_INVALID;
    }
    AudioCapture *capture = (AudioCapture *)calloc(1, sizeof(*capture));
    if (!capture) return AUDIO_OVERLOAD;
    capture->ring = (i16 *)calloc((usize)config->ring_frames * config->channels, sizeof(i16));
    if (!capture->ring) {
        free(capture);
        return AUDIO_OVERLOAD;
    }
    capture->backend = config->backend;
    capture->channels = config->channels;
    capture->ring_frames = config->ring_frames;
    atomic_init(&capture->head, 0u);
    atomic_init(&capture->tail, 0u);
    atomic_init(&capture->overruns, 0u);
    atomic_init(&capture->running, false);
    if (config->backend != AUDIO_BACKEND_FAKE) {
        ma_context *context = NULL;
        if (config->backend == AUDIO_BACKEND_NULL) {
            ma_backend null_backend = ma_backend_null;
            if (ma_context_init(&null_backend, 1, NULL, &capture->context) != MA_SUCCESS) {
                audio_capture_destroy(capture);
                return AUDIO_FAILED;
            }
            capture->context_ready = true;
            context = &capture->context;
        }
        ma_device_config device_config = ma_device_config_init(ma_device_type_capture);
        device_config.capture.format = ma_format_f32;
        device_config.capture.channels = config->channels;
        device_config.sampleRate = config->sample_rate;
        device_config.dataCallback = capture_data_callback;
        device_config.pUserData = capture;
        if (ma_device_init(context, &device_config, &capture->device) != MA_SUCCESS) {
            audio_capture_destroy(capture);
            return AUDIO_FAILED;
        }
        capture->device_ready = true;
    }
    *out = capture;
    return AUDIO_OK;
}

void audio_capture_destroy(AudioCapture *capture) {
    if (!capture) return;
    /* uninit stops a running device and waits for its callback */
    if (capture->device_ready) ma_device_uninit(&capture->device);
    if (capture->context_ready) ma_context_uninit(&capture->context);
    free(capture->ring);
    free(capture);
}

AudioResult audio_capture_start(AudioCapture *capture) {
    if (!capture) return AUDIO_INVALID;
    if (atomic_load_explicit(&capture->running, memory_order_acquire)) return AUDIO_OK;
    if (capture->device_ready && ma_device_start(&capture->device) != MA_SUCCESS) {
        return AUDIO_FAILED;
    }
    atomic_store_explicit(&capture->running, true, memory_order_release);
    return AUDIO_OK;
}

AudioResult audio_capture_stop(AudioCapture *capture) {
    if (!capture) return AUDIO_INVALID;
    if (!atomic_load_explicit(&capture->running, memory_order_acquire)) return AUDIO_OK;
    if (capture->device_ready && ma_device_stop(&capture->device) != MA_SUCCESS) {
        return AUDIO_FAILED;
    }
    atomic_store_explicit(&capture->running, false, memory_order_release);
    return AUDIO_OK;
}

bool audio_capture_running(const AudioCapture *capture) {
    return capture && atomic_load_explicit(&capture->running, memory_order_acquire);
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
    if (capture->backend != AUDIO_BACKEND_FAKE ||
        !atomic_load_explicit(&capture->running, memory_order_acquire)) {
        return AUDIO_REJECTED;
    }
    capture_write(capture, samples, frames);
    return AUDIO_OK;
}
