#pragma once
/* Microphone capture: an input device feeds a single-producer
 * single-consumer ring of 16-bit frames that the owner thread reads
 * (docs/design/audio_extended.md, "Capture"). */

#include <audio/audio.h>

#define AUDIO_CAPTURE_MIN_RATE 8000u
#define AUDIO_CAPTURE_MAX_RATE 192000u
#define AUDIO_CAPTURE_MAX_RING_FRAMES (1u << 20)

typedef struct AudioCapture AudioCapture;

typedef struct {
    /* DEFAULT: the system's default input. NULL: miniaudio's null device,
     * which delivers silence in real time. FAKE: no device; frames come from
     * audio_capture_inject. */
    AudioBackend backend;
    u32 sample_rate; /* AUDIO_CAPTURE_MIN_RATE..AUDIO_CAPTURE_MAX_RATE */
    u32 channels;    /* 1 or 2 */
    u32 ring_frames; /* a power of two, at most AUDIO_CAPTURE_MAX_RING_FRAMES */
} AudioCaptureConfig;

/* INVALID for a NULL argument or a config out of range, OVERLOAD when memory
 * runs out, FAILED when the device does not open. *out is written only on
 * success. The capture starts stopped. */
AudioResult audio_capture_create(const AudioCaptureConfig *config, AudioCapture **out);
/* Stops a running device first. NULL is a no-op. */
void audio_capture_destroy(AudioCapture *capture);

/* Both are idempotent. FAILED when the device refuses. */
AudioResult audio_capture_start(AudioCapture *capture);
AudioResult audio_capture_stop(AudioCapture *capture);
bool audio_capture_running(const AudioCapture *capture);

/* Copies up to max_frames of the oldest captured frames (interleaved by
 * channel) and releases them. The owner thread is the only reader. */
AudioResult audio_capture_read_i16(AudioCapture *capture, i16 *out, u32 max_frames,
                                   u32 *out_frames);
u32 audio_capture_available(const AudioCapture *capture);
/* Frames dropped because the ring was full (the newest ones are dropped). */
u64 audio_capture_overruns(const AudioCapture *capture);

/* FAKE only: writes `frames` interleaved f32 frames through the same path
 * as the device callback (non-finite samples become 0, the rest are
 * clamped to [-1, 1] and rounded to i16 by x * 32767). REJECTED for another
 * backend or a stopped capture. One injecting thread at a time. */
AudioResult audio_capture_inject(AudioCapture *capture, const f32 *samples, u32 frames);
