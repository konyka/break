#include "audio_extended.h"
#include <miniaudio.h>
#include <math.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

#define AUDIO_MAX_VOICES 32u
#define AUDIO_COMMAND_CAPACITY 16u

void audio_extended_destroy(AudioSystem *as, void *opaque);

typedef struct {
    char name[AUDIO_NAME_MAX];
    u32 sample_offset;
    u32 frame_count;
    u32 channels;
    bool used;
} AudioClip;

typedef enum {
    AUDIO_COMMAND_START = 1,
    AUDIO_COMMAND_STOP
} AudioCommandType;

typedef struct {
    AudioCommandType type;
    u32 serial;
    const f32 *samples;
    u32 frame_count;
    u32 channels;
    AudioEventDesc desc;
} AudioCommand;

typedef struct {
    ma_data_source_base base;
    ma_data_source_node node;
    bool node_initialized;
    AudioCommand commands[AUDIO_COMMAND_CAPACITY];
    atomic_uint head;
    atomic_uint tail;
    atomic_uint cursor;
    atomic_uint completed_serial;
    const f32 *samples;
    u32 frame_count;
    u32 channels;
    u32 playing_serial;
    bool playing;
    bool looping;
    f32 volume;
    u32 serial;
    bool claimed;
    bool stop_pending;
    i32 owner_event;
    u64 order;
} AudioVoice;

typedef struct {
    char name[AUDIO_NAME_MAX];
    AudioEventDesc desc;
    bool used;
} AudioEvent;

typedef struct {
    AudioSystem *owner;
    ma_engine *engine;
    AudioClip clips[AUDIO_MAX_CLIPS];
    u32 clip_count;
    usize used_samples;
    f32 pcm[AUDIO_PCM_MAX_SAMPLES];
    AudioEvent events[AUDIO_MAX_EVENTS];
    u32 event_count;
    AudioVoice voices[AUDIO_MAX_VOICES];
    u64 next_order;
} AudioExtended;

static AudioExtended *audio_extended(AudioSystem *as) {
    return as ? (AudioExtended *)as->extended : NULL;
}

static const AudioExtended *audio_extended_const(const AudioSystem *as) {
    return as ? (const AudioExtended *)as->extended : NULL;
}

static bool voice_command_space(const AudioVoice *voice) {
    u32 head = atomic_load_explicit(&voice->head, memory_order_relaxed);
    u32 tail = atomic_load_explicit(&voice->tail, memory_order_acquire);
    return head - tail < AUDIO_COMMAND_CAPACITY;
}

static bool voice_enqueue(AudioVoice *voice, const AudioCommand *command) {
    if (!voice_command_space(voice)) return false;
    u32 head = atomic_load_explicit(&voice->head, memory_order_relaxed);
    voice->commands[head & (AUDIO_COMMAND_CAPACITY - 1u)] = *command;
    atomic_store_explicit(&voice->head, head + 1u, memory_order_release);
    return true;
}

static bool voice_dequeue(AudioVoice *voice, AudioCommand *command) {
    u32 tail = atomic_load_explicit(&voice->tail, memory_order_relaxed);
    u32 head = atomic_load_explicit(&voice->head, memory_order_acquire);
    if (tail == head) return false;
    *command = voice->commands[tail & (AUDIO_COMMAND_CAPACITY - 1u)];
    atomic_store_explicit(&voice->tail, tail + 1u, memory_order_release);
    return true;
}

static void voice_finish(AudioVoice *voice, u32 serial) {
    voice->playing = false;
    atomic_store_explicit(&voice->completed_serial, serial, memory_order_release);
}

static void voice_drain_commands(AudioVoice *voice) {
    AudioCommand command;
    while (voice_dequeue(voice, &command)) {
        if (command.type == AUDIO_COMMAND_START) {
            voice->samples = command.samples;
            voice->frame_count = command.frame_count;
            voice->channels = command.channels;
            voice->playing_serial = command.serial;
            voice->looping = command.desc.looping;
            voice->volume = command.desc.volume;
            voice->playing = true;
            atomic_store_explicit(&voice->cursor, 0u, memory_order_release);
        } else if (command.type == AUDIO_COMMAND_STOP) {
            voice_finish(voice, command.serial);
        }
    }
}

static ma_result voice_read(ma_data_source *source, void *output,
                            ma_uint64 frames, ma_uint64 *frames_read) {
    AudioVoice *voice = (AudioVoice *)source;
    f32 *out = (f32 *)output;
    voice_drain_commands(voice);
    for (ma_uint64 frame = 0; frame < frames; ++frame) {
        f32 left = 0.0f;
        f32 right = 0.0f;
        if (voice->playing) {
            u32 cursor = atomic_load_explicit(&voice->cursor, memory_order_relaxed);
            if (cursor >= voice->frame_count) {
                voice_finish(voice, voice->playing_serial);
            } else {
                u64 sample = (u64)cursor * voice->channels;
                left = voice->samples[sample] * voice->volume;
                right = voice->channels == 2 ?
                        voice->samples[sample + 1u] * voice->volume : left;
                cursor++;
                if (cursor == voice->frame_count) {
                    if (voice->looping) cursor = 0;
                    else voice_finish(voice, voice->playing_serial);
                }
                atomic_store_explicit(&voice->cursor, cursor, memory_order_release);
            }
        }
        if (out) {
            out[frame * 2u] = left;
            out[frame * 2u + 1u] = right;
        }
    }
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
    AudioVoice *voice = (AudioVoice *)source;
    *cursor = atomic_load_explicit(&voice->cursor, memory_order_acquire);
    return MA_SUCCESS;
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
        voice->owner_event = -1;
        atomic_init(&voice->head, 0);
        atomic_init(&voice->tail, 0);
        atomic_init(&voice->cursor, 0);
        atomic_init(&voice->completed_serial, 0);
        ma_data_source_config config = ma_data_source_config_init();
        config.vtable = &AUDIO_VOICE_VTABLE;
        if (ma_data_source_init(&config, &voice->base) != MA_SUCCESS) {
            audio_extended_destroy(as, ext);
            return false;
        }
        ma_data_source_node_config node_config =
            ma_data_source_node_config_init(&voice->base);
        if (ma_data_source_node_init(ma_engine_get_node_graph(engine),
                &node_config, NULL, &voice->node) != MA_SUCCESS) {
            audio_extended_destroy(as, ext);
            return false;
        }
        voice->node_initialized = true;
        if (ma_node_attach_output_bus(&voice->node, 0,
                ma_engine_get_endpoint(engine), 0) != MA_SUCCESS) {
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
        if (voice->node_initialized) {
            ma_data_source_node_uninit(&voice->node, NULL);
            voice->node_initialized = false;
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

static AudioClip *clip_resolve(AudioExtended *ext, AudioClipHandle handle) {
    if (!ext || handle == 0 || handle > ext->clip_count) return NULL;
    AudioClip *clip = &ext->clips[handle - 1u];
    return clip->used ? clip : NULL;
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

static i32 event_find(AudioExtended *ext, const char *name) {
    if (!ext || !name) return -1;
    for (u32 i = 0; i < ext->event_count; ++i) {
        if (ext->events[i].used && strcmp(ext->events[i].name, name) == 0) {
            return (i32)i;
        }
    }
    return -1;
}

AudioResult audio_event_register(AudioSystem *as, const char *name,
                                 const AudioEventDesc *desc) {
    AudioExtended *ext = audio_extended(as);
    if (!ext || !valid_name(name) || !desc ||
        !clip_resolve(ext, desc->clip) || desc->max_instances == 0 ||
        desc->max_instances > AUDIO_EVENT_MAX_VOICES ||
        desc->retrigger < AUDIO_RETRIGGER_ALLOW ||
        desc->retrigger > AUDIO_RETRIGGER_IGNORE ||
        desc->concurrency < AUDIO_CONCURRENCY_REJECT ||
        desc->concurrency > AUDIO_CONCURRENCY_STEAL_OLDEST ||
        !isfinite(desc->volume) || desc->volume < 0.0f ||
        !isfinite(desc->min_distance) || desc->min_distance <= 0.0f ||
        !isfinite(desc->max_distance) || desc->max_distance < desc->min_distance ||
        !isfinite(desc->rolloff) || desc->rolloff < 0.0f ||
        !isfinite(desc->occluded_gain) || desc->occluded_gain < 0.0f ||
        desc->occluded_gain > 1.0f || desc->bus >= as->bus_count) {
        return AUDIO_INVALID;
    }
    if (event_find(ext, name) >= 0) return AUDIO_REJECTED;
    if (ext->event_count >= AUDIO_MAX_EVENTS) return AUDIO_OVERLOAD;

    AudioEvent *event = &ext->events[ext->event_count];
    memcpy(event->name, name, strlen(name) + 1);
    event->desc = *desc;
    event->used = true;
    ext->event_count++;
    return AUDIO_OK;
}

static void reap_voices(AudioExtended *ext) {
    for (u32 i = 0; i < AUDIO_MAX_VOICES; ++i) {
        AudioVoice *voice = &ext->voices[i];
        if (voice->claimed && atomic_load_explicit(&voice->completed_serial,
                memory_order_acquire) == voice->serial) {
            voice->claimed = false;
            voice->owner_event = -1;
            voice->stop_pending = false;
        }
    }
}

static u32 event_voice_count(const AudioExtended *ext, u32 event_index) {
    u32 count = 0;
    for (u32 i = 2; i < AUDIO_MAX_VOICES; ++i) {
        if (ext->voices[i].claimed &&
            ext->voices[i].owner_event == (i32)event_index) count++;
    }
    return count;
}

static i32 event_voice_by_order(AudioExtended *ext, u32 event_index,
                                bool oldest) {
    i32 selected = -1;
    for (u32 i = 2; i < AUDIO_MAX_VOICES; ++i) {
        AudioVoice *voice = &ext->voices[i];
        if (!voice->claimed || voice->owner_event != (i32)event_index) continue;
        if (selected < 0 ||
            (oldest && voice->order < ext->voices[selected].order) ||
            (!oldest && voice->order > ext->voices[selected].order)) {
            selected = (i32)i;
        }
    }
    return selected;
}

static i32 free_event_voice(AudioExtended *ext) {
    for (u32 i = 2; i < AUDIO_MAX_VOICES; ++i) {
        if (!ext->voices[i].claimed) return (i32)i;
    }
    return -1;
}

static AudioVoiceHandle voice_handle(u32 slot, u32 serial) {
    return ((serial & 0xFFFFFFu) << 8) | (slot + 1u);
}

static AudioResult voice_start(AudioExtended *ext, u32 slot, u32 event_index,
                               bool new_generation, AudioVoiceHandle *out) {
    AudioVoice *voice = &ext->voices[slot];
    if (!voice_command_space(voice)) return AUDIO_OVERLOAD;
    AudioEvent *event = &ext->events[event_index];
    AudioClip *clip = clip_resolve(ext, event->desc.clip);
    if (!clip) return AUDIO_STALE;

    u32 serial = new_generation ? (voice->serial + 1u) & 0xFFFFFFu : voice->serial;
    AudioCommand command;
    memset(&command, 0, sizeof(command));
    command.type = AUDIO_COMMAND_START;
    command.serial = serial;
    command.samples = &ext->pcm[clip->sample_offset];
    command.frame_count = clip->frame_count;
    command.channels = clip->channels;
    command.desc = event->desc;

    voice->serial = serial;
    voice->claimed = true;
    voice->owner_event = (i32)event_index;
    voice->order = ++ext->next_order;
    voice->stop_pending = false;
    atomic_store_explicit(&voice->cursor, 0u, memory_order_release);
    if (!voice_enqueue(voice, &command)) return AUDIO_OVERLOAD;
    *out = voice_handle(slot, serial);
    return AUDIO_OK;
}

AudioResult audio_event_trigger(AudioSystem *as, const char *name, Vec3 pos,
                                AudioVoiceHandle *out_voice) {
    if (!out_voice) return AUDIO_INVALID;
    *out_voice = 0;
    AudioExtended *ext = audio_extended(as);
    i32 event_index = event_find(ext, name);
    if (!ext || event_index < 0 || !isfinite(pos.e[0]) ||
        !isfinite(pos.e[1]) || !isfinite(pos.e[2])) return AUDIO_INVALID;
    reap_voices(ext);
    AudioEventDesc *desc = &ext->events[event_index].desc;
    u32 count = event_voice_count(ext, (u32)event_index);
    if (desc->retrigger == AUDIO_RETRIGGER_IGNORE && count > 0) {
        return AUDIO_REJECTED;
    }
    if (desc->retrigger == AUDIO_RETRIGGER_RESTART && count > 0) {
        i32 newest = event_voice_by_order(ext, (u32)event_index, false);
        return voice_start(ext, (u32)newest, (u32)event_index, false, out_voice);
    }

    i32 selected = -1;
    if (count < desc->max_instances) selected = free_event_voice(ext);
    else if (desc->concurrency == AUDIO_CONCURRENCY_STEAL_OLDEST) {
        selected = event_voice_by_order(ext, (u32)event_index, true);
    } else {
        return AUDIO_OVERLOAD;
    }
    if (selected < 0) return AUDIO_OVERLOAD;
    return voice_start(ext, (u32)selected, (u32)event_index, true, out_voice);
}

static AudioVoice *voice_resolve(AudioExtended *ext, AudioVoiceHandle handle,
                                 u32 *out_slot) {
    u32 slot = (handle & 0xFFu);
    if (!ext || slot == 0 || slot > AUDIO_MAX_VOICES) return NULL;
    slot--;
    AudioVoice *voice = &ext->voices[slot];
    if (!voice->claimed || ((handle >> 8) & 0xFFFFFFu) != voice->serial) {
        return NULL;
    }
    if (out_slot) *out_slot = slot;
    return voice;
}

AudioResult audio_voice_stop(AudioSystem *as, AudioVoiceHandle handle) {
    AudioExtended *ext = audio_extended(as);
    reap_voices(ext);
    AudioVoice *voice = voice_resolve(ext, handle, NULL);
    if (!voice) return AUDIO_STALE;
    if (voice->stop_pending) return AUDIO_REJECTED;
    if (!voice_command_space(voice)) return AUDIO_OVERLOAD;
    AudioCommand command;
    memset(&command, 0, sizeof(command));
    command.type = AUDIO_COMMAND_STOP;
    command.serial = voice->serial;
    voice->stop_pending = true;
    if (!voice_enqueue(voice, &command)) return AUDIO_OVERLOAD;
    return AUDIO_OK;
}

AudioResult audio_voice_cursor(AudioSystem *as, AudioVoiceHandle handle,
                               u32 *out_frame) {
    if (!out_frame) return AUDIO_INVALID;
    *out_frame = 0;
    AudioExtended *ext = audio_extended(as);
    AudioVoice *voice = voice_resolve(ext, handle, NULL);
    if (!voice) return AUDIO_STALE;
    *out_frame = atomic_load_explicit(&voice->cursor, memory_order_acquire);
    return AUDIO_OK;
}

AudioResult audio_event_active_count(AudioSystem *as, const char *name,
                                     u32 *out_count) {
    if (!out_count) return AUDIO_INVALID;
    *out_count = 0;
    AudioExtended *ext = audio_extended(as);
    i32 event_index = event_find(ext, name);
    if (!ext || event_index < 0) return AUDIO_INVALID;
    reap_voices(ext);
    *out_count = event_voice_count(ext, (u32)event_index);
    return AUDIO_OK;
}
