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

AudioResult audio_clip_register(AudioSystem *as, const char *name,
                                const AudioPcmDesc *pcm,
                                AudioClipHandle *out_handle);
u32 audio_clip_count(const AudioSystem *as);
usize audio_clip_used_samples(const AudioSystem *as);
AudioResult audio_system_render(AudioSystem *as, f32 *stereo_out, u32 frames);
