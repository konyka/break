#include "audio_extended.h"
#include <miniaudio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define AUDIO_MAX_VOICES 32u

void audio_extended_destroy(AudioSystem *as, void *opaque);

typedef struct {
    char name[AUDIO_NAME_MAX];
    u32 sample_offset;
    u32 frame_count;
    u32 channels;
    bool used;
} AudioClip;

typedef struct {
    ma_data_source_base base;
    ma_sound sound;
    bool sound_initialized;
} AudioVoice;

typedef struct {
    AudioSystem *owner;
    ma_engine *engine;
    AudioClip clips[AUDIO_MAX_CLIPS];
    u32 clip_count;
    usize used_samples;
    f32 pcm[AUDIO_PCM_MAX_SAMPLES];
    AudioVoice voices[AUDIO_MAX_VOICES];
} AudioExtended;

static AudioExtended *audio_extended(AudioSystem *as) {
    return as ? (AudioExtended *)as->extended : NULL;
}

static const AudioExtended *audio_extended_const(const AudioSystem *as) {
    return as ? (const AudioExtended *)as->extended : NULL;
}

static ma_result voice_read(ma_data_source *source, void *output,
                            ma_uint64 frames, ma_uint64 *frames_read) {
    (void)source;
    ma_silence_pcm_frames(output, frames, ma_format_f32, 2);
    if (frames_read) *frames_read = frames;
    return MA_SUCCESS;
}

static ma_result voice_seek(ma_data_source *source, ma_uint64 frame) {
    (void)source; (void)frame;
    return MA_NOT_IMPLEMENTED;
}

static ma_result voice_format(ma_data_source *source, ma_format *format,
                              u32 *channels, u32 *sample_rate,
                              ma_channel *channel_map, usize channel_cap) {
    (void)source; (void)channel_map; (void)channel_cap;
    *format = ma_format_f32;
    *channels = 2;
    *sample_rate = AUDIO_PCM_SAMPLE_RATE;
    return MA_SUCCESS;
}

static ma_result voice_cursor(ma_data_source *source, ma_uint64 *cursor) {
    (void)source;
    *cursor = 0;
    return MA_NOT_IMPLEMENTED;
}

static ma_result voice_length(ma_data_source *source, ma_uint64 *length) {
    (void)source;
    *length = 0;
    return MA_NOT_IMPLEMENTED;
}

static const ma_data_source_vtable AUDIO_VOICE_VTABLE = {
    voice_read, voice_seek, voice_format, voice_cursor, voice_length,
    NULL, MA_DATA_SOURCE_SELF_MANAGED_RANGE_AND_LOOP_POINT
};

bool audio_extended_init(AudioSystem *as, ma_engine *engine) {
    if (!as || !engine || as->extended) return false;
    AudioExtended *ext = (AudioExtended *)calloc(1, sizeof(*ext));
    if (!ext) return false;
    ext->owner = as;
    ext->engine = engine;

    for (u32 i = 0; i < AUDIO_MAX_VOICES; ++i) {
        AudioVoice *voice = &ext->voices[i];
        ma_data_source_config config = ma_data_source_config_init();
        config.vtable = &AUDIO_VOICE_VTABLE;
        if (ma_data_source_init(&config, &voice->base) != MA_SUCCESS) {
            audio_extended_destroy(as, ext);
            return false;
        }
        if (ma_sound_init_from_data_source(engine, &voice->base,
                MA_SOUND_FLAG_NO_SPATIALIZATION, NULL,
                &voice->sound) != MA_SUCCESS) {
            ma_data_source_uninit(&voice->base);
            audio_extended_destroy(as, ext);
            return false;
        }
        voice->sound_initialized = true;
        if (ma_sound_start(&voice->sound) != MA_SUCCESS) {
            audio_extended_destroy(as, ext);
            return false;
        }
    }
    as->extended = ext;
    return true;
}

void audio_extended_destroy(AudioSystem *as, void *opaque) {
    AudioExtended *ext = (AudioExtended *)opaque;
    if (!ext) return;
    for (u32 i = 0; i < AUDIO_MAX_VOICES; ++i) {
        AudioVoice *voice = &ext->voices[i];
        if (voice->sound_initialized) {
            ma_sound_uninit(&voice->sound);
            voice->sound_initialized = false;
        }
        if (voice->base.vtable) ma_data_source_uninit(&voice->base);
    }
    if (as && as->extended == ext) as->extended = NULL;
    free(ext);
}

static bool valid_name(const char *name) {
    if (!name || name[0] == '\0') return false;
    for (u32 i = 0; i < AUDIO_NAME_MAX; ++i) {
        if (name[i] == '\0') return true;
    }
    return false;
}

AudioResult audio_clip_register(AudioSystem *as, const char *name,
                                const AudioPcmDesc *pcm,
                                AudioClipHandle *out_handle) {
    if (!out_handle) return AUDIO_INVALID;
    *out_handle = 0;
    AudioExtended *ext = audio_extended(as);
    if (!ext || !valid_name(name) || !pcm || !pcm->samples ||
        pcm->frame_count == 0 || (pcm->channels != 1 && pcm->channels != 2) ||
        pcm->sample_rate != AUDIO_PCM_SAMPLE_RATE) return AUDIO_INVALID;
    for (u32 i = 0; i < AUDIO_MAX_CLIPS; ++i) {
        if (ext->clips[i].used && strcmp(ext->clips[i].name, name) == 0) {
            return AUDIO_REJECTED;
        }
    }
    if (ext->clip_count >= AUDIO_MAX_CLIPS) return AUDIO_OVERLOAD;
    u64 sample_count = (u64)pcm->frame_count * pcm->channels;
    if (sample_count > AUDIO_PCM_MAX_SAMPLES ||
        sample_count > (u64)(AUDIO_PCM_MAX_SAMPLES - ext->used_samples)) {
        return AUDIO_OVERLOAD;
    }
    for (u64 i = 0; i < sample_count; ++i) {
        if (!isfinite(pcm->samples[i])) return AUDIO_INVALID;
    }

    u32 slot = ext->clip_count;
    AudioClip *clip = &ext->clips[slot];
    memcpy(clip->name, name, strlen(name) + 1);
    clip->sample_offset = (u32)ext->used_samples;
    clip->frame_count = pcm->frame_count;
    clip->channels = pcm->channels;
    memcpy(&ext->pcm[ext->used_samples], pcm->samples,
           (usize)sample_count * sizeof(f32));
    clip->used = true;
    ext->used_samples += (usize)sample_count;
    ext->clip_count++;
    *out_handle = slot + 1u;
    return AUDIO_OK;
}

u32 audio_clip_count(const AudioSystem *as) {
    const AudioExtended *ext = audio_extended_const(as);
    return ext ? ext->clip_count : 0;
}

usize audio_clip_used_samples(const AudioSystem *as) {
    const AudioExtended *ext = audio_extended_const(as);
    return ext ? ext->used_samples : 0;
}
