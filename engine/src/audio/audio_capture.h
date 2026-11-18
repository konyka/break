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

/* Both are idempotent. start is FAILED when the device refuses or is lost. */
AudioResult audio_capture_start(AudioCapture *capture);
AudioResult audio_capture_stop(AudioCapture *capture);
/* False while the device is lost. */
bool audio_capture_running(const AudioCapture *capture);

typedef enum {
    AUDIO_CAPTURE_EVENT_DEVICE_LOST = 0,
    AUDIO_CAPTURE_EVENT_REROUTED,
    /* Simulation only: the next audio_capture_reopen fails with AUDIO_FAILED
     * and changes nothing, as if no input device could be opened. Each event
     * refuses one reopen. */
    AUDIO_CAPTURE_EVENT_REOPEN_REFUSED,
} AudioCaptureEvent;

/* The device stopped without a stop request (unplugged, disabled, taken by
 * the system). Owner thread. Frames captured before stay readable; call
 * audio_capture_reopen to continue. */
bool audio_capture_lost(const AudioCapture *capture);
/* How often the backend moved the stream to another device on its own. */
u64 audio_capture_reroutes(const AudioCapture *capture);
/* Opens the named input device (NULL or empty: the default) and closes the
 * old one; restarts it when capture was running (a stop request after a
 * loss is kept). The ring and its frames are kept and the lost state is
 * cleared. REJECTED for a name no device has or a FAKE backend with a name,
 * FAILED when the device does not open; the old device and state are left
 * as they were on failure. The pumping thread; never concurrent with
 * start, stop, destroy or audio_capture_device_name. */
AudioResult audio_capture_reopen(AudioCapture *capture, const char *device_name);
/* FAKE and NULL backends only (tests): delivers `event` through the device
 * notification path (REOPEN_REFUSED only arms one refused reopen). INVALID
 * for NULL or an unknown event, REJECTED for the DEFAULT backend. */
AudioResult audio_capture_simulate_event(AudioCapture *capture, AudioCaptureEvent event);

/* Copies up to max_frames of the oldest captured frames (interleaved by
 * channel) and releases them. The owner thread is the only reader. */
AudioResult audio_capture_read_i16(AudioCapture *capture, i16 *out, u32 max_frames,
                                   u32 *out_frames);
u32 audio_capture_available(const AudioCapture *capture);
/* Frames dropped because the ring was full (the newest ones are dropped). */
u64 audio_capture_overruns(const AudioCapture *capture);

/* Input devices of a backend: DEFAULT the system's, NULL miniaudio's null
 * device ("NULL Capture Device"), FAKE none. Writes up to `capacity`
 * entries (id is the index as decimal text, the order of a later call with
 * the same backend) and returns how many devices exist, which may exceed
 * capacity; 0 when the backend cannot be enumerated. `out` may be NULL
 * when capacity is 0. */
u32 audio_capture_list_devices(AudioBackend backend, AudioDeviceInfo *out, u32 capacity);

/* Like audio_capture_create, opening the input device with the given name
 * (as audio_capture_list_devices reports it) instead of the default. NULL or
 * an empty name opens the default. REJECTED for a FAKE backend with a name
 * or a name no device has; *out is written only on success. */
AudioResult audio_capture_create_named(const AudioCaptureConfig *config, const char *device_name,
                                       AudioCapture **out);
/* The name of the opened device into out ("fake" for FAKE). False and ""
 * (when out has room) for a NULL capture or a device without a name. */
bool audio_capture_device_name(const AudioCapture *capture, char *out, usize capacity);
/* The backend behind the opened device: miniaudio's name ("PulseAudio",
 * "ALSA", "Null", ...), "fake" for FAKE, "none" for NULL. A static string. */
const char *audio_capture_backend_name(const AudioCapture *capture);

/* FAKE only: writes `frames` interleaved f32 frames through the same path
 * as the device callback (non-finite samples become 0, the rest are
 * clamped to [-1, 1] and rounded to i16 by x * 32767). REJECTED for another
 * backend or a stopped capture. One injecting thread at a time. */
AudioResult audio_capture_inject(AudioCapture *capture, const f32 *samples, u32 frames);
