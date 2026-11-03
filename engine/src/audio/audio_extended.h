#pragma once

#include <audio/audio.h>

#define AUDIO_MAX_CLIPS 48u
#define AUDIO_PCM_MAX_SAMPLES 1048576u
#define AUDIO_PCM_SAMPLE_RATE 48000u
#define AUDIO_NAME_MAX 48u

typedef u32 AudioClipHandle;

typedef struct {
    const f32 *samples;
    u32 frame_count;
    u32 channels;
    u32 sample_rate;
} AudioPcmDesc;

#define AUDIO_MAX_EVENTS 32u
#define AUDIO_EVENT_MAX_VOICES 30u

typedef u32 AudioVoiceHandle;

typedef enum {
    AUDIO_RETRIGGER_ALLOW = 0,
    AUDIO_RETRIGGER_RESTART,
    AUDIO_RETRIGGER_IGNORE
} AudioRetriggerPolicy;

typedef enum {
    AUDIO_CONCURRENCY_REJECT = 0,
    AUDIO_CONCURRENCY_STEAL_OLDEST
} AudioConcurrencyPolicy;

typedef struct {
    AudioClipHandle clip;
    u32 max_instances;
    AudioRetriggerPolicy retrigger;
    AudioConcurrencyPolicy concurrency;
    f32 volume;
    bool looping;
    bool spatial;
    f32 min_distance;
    f32 max_distance;
    f32 rolloff;
    f32 occluded_gain;
    u32 bus;
} AudioEventDesc;

AudioResult audio_event_register(AudioSystem *as, const char *name,
                                 const AudioEventDesc *desc);
AudioResult audio_event_trigger(AudioSystem *as, const char *name, Vec3 pos,
                                AudioVoiceHandle *out_voice);
AudioResult audio_voice_stop(AudioSystem *as, AudioVoiceHandle voice);
AudioResult audio_voice_cursor(AudioSystem *as, AudioVoiceHandle voice,
                               u32 *out_frame);
AudioResult audio_event_active_count(AudioSystem *as, const char *name,
                                     u32 *out_count);

AudioResult audio_clip_register(AudioSystem *as, const char *name,
                                const AudioPcmDesc *pcm,
                                AudioClipHandle *out_handle);
u32 audio_clip_count(const AudioSystem *as);
usize audio_clip_used_samples(const AudioSystem *as);
AudioResult audio_system_render(AudioSystem *as, f32 *stereo_out, u32 frames);
