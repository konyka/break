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
    AUDIO_COMMAND_STOP,
    AUDIO_COMMAND_RAMP
} AudioCommandType;

typedef struct {
    AudioCommandType type;
    u32 serial;
    u64 epoch;
    const f32 *samples;
    u32 frame_count;
    u32 channels;
    f32 dsp_alpha[AUDIO_DSP_MAX_STAGES];
    f32 initial_gain;
    f32 spatial_gain;
    u32 spatial_revision;
    f32 ramp_target;
    u32 ramp_frames;
    bool stop_after_ramp;
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
    atomic_uint_least64_t completed_epoch;
    const f32 *samples;
    u32 frame_count;
    u32 channels;
    u64 playing_epoch;
    bool playing;
    bool looping;
    f32 volume;
    f32 fade_gain;
    f32 fade_start;
    f32 fade_target;
    u32 fade_remaining;
    u32 fade_total;
    bool fade_stop;
    AudioDspChain dsp;
    f32 dsp_delay_storage[AUDIO_DSP_MAX_STAGES *
                          AUDIO_DSP_MAX_DELAY_FRAMES * 2u];
    atomic_uint_least64_t spatial_snapshot;
    atomic_uint_least64_t started_epoch;
    atomic_uint *bus_gains;
    Vec3 position;
    u32 bus;
    u32 serial;
    u64 epoch;
    u32 spatial_revision;
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
    AudioClipHandle playlist[AUDIO_MUSIC_MAX_TRACKS];
    u32 playlist_count;
    bool playlist_loop;
    u32 playlist_fade;
    f32 playlist_volume;
    u32 playlist_bus;
    bool playlist_set;
    AudioMusicState music_state;
    u32 music_index;
    u32 music_current;
    u32 music_previous;
    AudioOcclusionRayFn ray;
    void *ray_user;
    atomic_uint bus_gains[AUDIO_MAX_BUSES];
} AudioExtended;

static AudioExtended *audio_extended(AudioSystem *as) {
    return as ? (AudioExtended *)as->extended : NULL;
}

static const AudioExtended *audio_extended_const(const AudioSystem *as) {
    return as ? (const AudioExtended *)as->extended : NULL;
}

static u32 gain_to_bits(f32 gain) {
    u32 bits;
    memcpy(&bits, &gain, sizeof(bits));
    return bits;
}

static f32 gain_from_bits(u32 bits) {
    f32 gain;
    memcpy(&gain, &bits, sizeof(gain));
    return gain;
}

static u64 spatial_pack(u32 revision, f32 gain) {
    _Static_assert(sizeof(u32) == 4 && sizeof(f32) == 4,
                   "spatial snapshot requires 32-bit fields");
    _Static_assert(sizeof(u64) == 8, "spatial snapshot requires 64-bit epoch");
    return ((u64)revision << 32) | gain_to_bits(gain);
}

static u32 spatial_revision_of(u64 snapshot) {
    return (u32)(snapshot >> 32);
}

static f32 spatial_gain_of(u64 snapshot) {
    return gain_from_bits((u32)(snapshot & 0xFFFFFFFFu));
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

static void voice_finish(AudioVoice *voice, u64 epoch) {
    voice->playing = false;
    atomic_store_explicit(&voice->completed_epoch, epoch, memory_order_release);
}

static void voice_configure_dsp(AudioVoice *voice,
                                const AudioCommand *command) {
    memset(&voice->dsp, 0, sizeof(voice->dsp));
    voice->dsp.stage_count = command->desc.dsp.stage_count;
    voice->dsp.sample_rate = AUDIO_PCM_SAMPLE_RATE;
    u32 delay_stage = 0;
    for (u32 i = 0; i < command->desc.dsp.stage_count; ++i) {
        AudioDspStage *stage = &voice->dsp.stages[i];
        stage->desc = command->desc.dsp.stages[i];
        stage->alpha = command->dsp_alpha[i];
        if (stage->desc.type != AUDIO_DSP_FILTER) {
            stage->delay_line = voice->dsp_delay_storage +
                delay_stage * AUDIO_DSP_MAX_DELAY_FRAMES * 2u;
            memset(stage->delay_line, 0,
                   AUDIO_DSP_MAX_DELAY_FRAMES * 2u * sizeof(f32));
            delay_stage++;
        }
    }
}

static void voice_drain_commands(AudioVoice *voice) {
    AudioCommand command;
    while (voice_dequeue(voice, &command)) {
        if (command.type == AUDIO_COMMAND_START) {
            voice->samples = command.samples;
            voice->frame_count = command.frame_count;
            voice->channels = command.channels;
            voice->playing_epoch = command.epoch;
            voice->looping = command.desc.looping;
            voice->volume = command.desc.volume;
            voice->bus = command.desc.bus;
            voice->fade_gain = command.initial_gain;
            voice->fade_start = command.initial_gain;
            voice->fade_target = command.ramp_frames > 0 ?
                                 command.ramp_target : command.initial_gain;
            voice->fade_remaining = command.ramp_frames;
            voice->fade_total = command.ramp_frames;
            voice->fade_stop = command.stop_after_ramp;
            u64 snapshot = atomic_load_explicit(&voice->spatial_snapshot,
                                                memory_order_acquire);
            if (spatial_revision_of(snapshot) == command.spatial_revision) {
                atomic_store_explicit(&voice->spatial_snapshot,
                    spatial_pack(command.spatial_revision, command.spatial_gain),
                    memory_order_release);
            }
            voice_configure_dsp(voice, &command);
            voice->playing = true;
            atomic_store_explicit(&voice->cursor, 0u, memory_order_release);
            atomic_store_explicit(&voice->started_epoch, command.epoch,
                                  memory_order_release);
        } else if (command.type == AUDIO_COMMAND_STOP) {
            if (command.epoch == voice->playing_epoch) {
                voice_finish(voice, command.epoch);
            }
        } else if (command.type == AUDIO_COMMAND_RAMP) {
            if (command.epoch != voice->playing_epoch) continue;
            voice->fade_start = voice->fade_gain;
            voice->fade_target = command.ramp_target;
            voice->fade_remaining = command.ramp_frames;
            voice->fade_total = command.ramp_frames;
            voice->fade_stop = command.stop_after_ramp;
            if (command.ramp_frames == 0) {
                voice->fade_gain = command.ramp_target;
                if (command.stop_after_ramp) voice_finish(voice, command.epoch);
            }
        }
    }
}

static void voice_advance_fade(AudioVoice *voice) {
    if (voice->fade_remaining == 0) return;
    u32 done = voice->fade_total - voice->fade_remaining + 1u;
    f32 t = (f32)done / (f32)voice->fade_total;
    voice->fade_gain = voice->fade_start +
                       (voice->fade_target - voice->fade_start) * t;
    voice->fade_remaining--;
    if (voice->fade_remaining == 0 && voice->fade_stop) {
        voice_finish(voice, voice->playing_epoch);
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
            voice_advance_fade(voice);
            u32 cursor = atomic_load_explicit(&voice->cursor, memory_order_relaxed);
            if (cursor >= voice->frame_count) {
                voice_finish(voice, voice->playing_epoch);
            } else {
                u64 sample = (u64)cursor * voice->channels;
                f32 bus_gain = voice->bus == AUDIO_BUS_MASTER ? 1.0f :
                    gain_from_bits(atomic_load_explicit(
                        &voice->bus_gains[voice->bus], memory_order_relaxed));
                f32 master_gain = gain_from_bits(atomic_load_explicit(
                    &voice->bus_gains[AUDIO_BUS_MASTER], memory_order_relaxed));
                f32 spatial_gain = spatial_gain_of(atomic_load_explicit(
                    &voice->spatial_snapshot, memory_order_relaxed));
                f32 gain = voice->volume * voice->fade_gain * bus_gain *
                           master_gain * spatial_gain;
                left = voice->samples[sample] * gain;
                right = voice->channels == 2 ?
                        voice->samples[sample + 1u] * gain : left;
                cursor++;
                if (cursor == voice->frame_count) {
                    if (voice->looping) cursor = 0;
                    else voice_finish(voice, voice->playing_epoch);
                }
                atomic_store_explicit(&voice->cursor, cursor, memory_order_release);
            }
        }
        f32 rendered[2] = {left, right};
        audio_dsp_chain_process(&voice->dsp, rendered, 1, 2);
        if (out) {
            out[frame * 2u] = rendered[0];
            out[frame * 2u + 1u] = rendered[1];
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
    ext->music_current = UINT32_MAX;
    ext->music_previous = UINT32_MAX;
    for (u32 i = 0; i < AUDIO_MAX_BUSES; ++i) {
        atomic_init(&ext->bus_gains[i], gain_to_bits(1.0f));
    }

    for (u32 i = 0; i < AUDIO_MAX_VOICES; ++i) {
        AudioVoice *voice = &ext->voices[i];
        voice->owner_event = -1;
        voice->bus_gains = ext->bus_gains;
        atomic_init(&voice->head, 0);
        atomic_init(&voice->tail, 0);
        atomic_init(&voice->cursor, 0);
        atomic_init(&voice->completed_epoch, 0);
        atomic_init(&voice->spatial_snapshot, spatial_pack(0, 1.0f));
        atomic_init(&voice->started_epoch, 0);
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
    if (!ext || !valid_name(name) || !desc || desc->clip == 0 ||
        desc->max_instances == 0 ||
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
    if (!clip_resolve(ext, desc->clip)) return AUDIO_STALE;
    AudioResult dsp_result = audio_dsp_chain_validate(&desc->dsp,
                                                       AUDIO_PCM_SAMPLE_RATE);
    if (dsp_result != AUDIO_OK) return dsp_result;
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
        if (voice->claimed && atomic_load_explicit(&voice->completed_epoch,
                memory_order_acquire) == voice->epoch) {
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

static AudioResult event_spatial_gain(AudioExtended *ext,
    const AudioEventDesc *desc, Vec3 position, f32 *out_gain) {
    if (!out_gain) return AUDIO_INVALID;
    if (!desc->spatial) {
        *out_gain = 1.0f;
        return AUDIO_OK;
    }
    Vec3 listener = ext->owner->listener_pos;
    for (u32 i = 0; i < 3; ++i) {
        if (!isfinite(listener.e[i]) || !isfinite(position.e[i])) {
            return AUDIO_INVALID;
        }
    }
    double dx = (double)position.e[0] - listener.e[0];
    double dy = (double)position.e[1] - listener.e[1];
    double dz = (double)position.e[2] - listener.e[2];
    double distance = sqrt(dx * dx + dy * dy + dz * dz);
    double minimum = desc->min_distance;
    double maximum = desc->max_distance;
    double clamped = distance < minimum ? minimum :
                     (distance > maximum ? maximum : distance);
    double denominator = minimum + desc->rolloff * (clamped - minimum);
    double gain = minimum / denominator;
    if (!isfinite(distance) || !isfinite(gain)) return AUDIO_INVALID;
    if (gain < 0.0f) gain = 0.0f;
    if (gain > 1.0f) gain = 1.0f;
    if (ext->ray && ext->ray(ext->ray_user, listener, position)) {
        gain *= desc->occluded_gain;
    }
    if (!isfinite(gain)) return AUDIO_INVALID;
    *out_gain = (f32)gain;
    return isfinite(*out_gain) ? AUDIO_OK : AUDIO_INVALID;
}

static AudioResult spatial_publish(AudioVoice *voice, u64 epoch, f32 gain) {
    if (epoch == 0 || voice->epoch != epoch) return AUDIO_STALE;
    if (voice->spatial_revision == UINT32_MAX) return AUDIO_OVERLOAD;
    u32 revision = voice->spatial_revision + 1u;
    voice->spatial_revision = revision;
    atomic_store_explicit(&voice->spatial_snapshot,
                          spatial_pack(revision, gain), memory_order_release);
    return AUDIO_OK;
}

static AudioResult voice_start_pcm(AudioExtended *ext, u32 slot,
    AudioClipHandle clip_handle, const AudioEventDesc *desc, i32 owner,
    bool new_generation, f32 initial_gain, u32 ramp_frames,
    Vec3 position, f32 spatial_gain, AudioVoiceHandle *out) {
    AudioVoice *voice = &ext->voices[slot];
    if (voice->epoch == UINT64_MAX) return AUDIO_OVERLOAD;
    if (!voice_command_space(voice)) return AUDIO_OVERLOAD;
    AudioClip *clip = clip_resolve(ext, clip_handle);
    if (!clip) return AUDIO_STALE;

    u32 serial = new_generation ? (voice->serial + 1u) & 0xFFFFFFu : voice->serial;
    u64 epoch = voice->epoch + 1u;
    AudioCommand command;
    memset(&command, 0, sizeof(command));
    command.type = AUDIO_COMMAND_START;
    command.serial = serial;
    command.epoch = epoch;
    command.samples = &ext->pcm[clip->sample_offset];
    command.frame_count = clip->frame_count;
    command.channels = clip->channels;
    command.initial_gain = initial_gain;
    command.spatial_gain = spatial_gain;
    command.spatial_revision = 1;
    command.ramp_target = 1.0f;
    command.ramp_frames = ramp_frames;
    command.desc = *desc;
    for (u32 i = 0; i < command.desc.dsp.stage_count; ++i) {
        if (command.desc.dsp.stages[i].type == AUDIO_DSP_FILTER) {
            command.dsp_alpha[i] = audio_dsp_filter_alpha(
                command.desc.dsp.stages[i].cutoff_hz, AUDIO_PCM_SAMPLE_RATE);
        }
    }

    f32 previous_gain = spatial_gain_of(atomic_load_explicit(
        &voice->spatial_snapshot, memory_order_relaxed));
    voice->spatial_revision = 1;
    atomic_store_explicit(&voice->spatial_snapshot,
                          spatial_pack(1, previous_gain), memory_order_release);
    (void)voice_enqueue(voice, &command);
    voice->serial = serial;
    voice->epoch = epoch;
    voice->claimed = true;
    voice->owner_event = owner;
    voice->order = ++ext->next_order;
    voice->stop_pending = false;
    voice->position = position;
    if (out) *out = voice_handle(slot, serial);
    return AUDIO_OK;
}

static AudioResult voice_start(AudioExtended *ext, u32 slot, u32 event_index,
                               bool new_generation, Vec3 position,
                               AudioVoiceHandle *out) {
    if (ext->voices[slot].epoch == UINT64_MAX) return AUDIO_OVERLOAD;
    if (!voice_command_space(&ext->voices[slot])) return AUDIO_OVERLOAD;
    AudioEvent *event = &ext->events[event_index];
    f32 spatial_gain = 0.0f;
    AudioResult spatial_result = event_spatial_gain(ext, &event->desc,
                                                    position, &spatial_gain);
    if (spatial_result != AUDIO_OK) return spatial_result;
    return voice_start_pcm(ext, slot, event->desc.clip, &event->desc,
        (i32)event_index, new_generation, 1.0f, 0, position, spatial_gain, out);
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
        return voice_start(ext, (u32)newest, (u32)event_index, false,
                           pos, out_voice);
    }

    i32 selected = -1;
    if (count < desc->max_instances) selected = free_event_voice(ext);
    else if (desc->concurrency == AUDIO_CONCURRENCY_STEAL_OLDEST) {
        selected = event_voice_by_order(ext, (u32)event_index, true);
    } else {
        return AUDIO_OVERLOAD;
    }
    if (selected < 0) return AUDIO_OVERLOAD;
    return voice_start(ext, (u32)selected, (u32)event_index, true,
                       pos, out_voice);
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
    command.epoch = voice->epoch;
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

void audio_set_occlusion_ray_callback(AudioSystem *as,
    AudioOcclusionRayFn fn, void *user) {
    AudioExtended *ext = audio_extended(as);
    if (!ext) return;
    ext->ray = fn;
    ext->ray_user = user;
}

AudioResult audio_voice_set_position(AudioSystem *as,
    AudioVoiceHandle handle, Vec3 position) {
    AudioExtended *ext = audio_extended(as);
    if (!ext || !isfinite(position.e[0]) || !isfinite(position.e[1]) ||
        !isfinite(position.e[2])) return AUDIO_INVALID;
    reap_voices(ext);
    AudioVoice *voice = voice_resolve(ext, handle, NULL);
    if (!voice || voice->owner_event < 0) return AUDIO_STALE;
    if (voice->stop_pending) return AUDIO_REJECTED;
    if (voice->spatial_revision == UINT32_MAX) return AUDIO_OVERLOAD;
    f32 gain = 0.0f;
    AudioResult result = event_spatial_gain(ext,
        &ext->events[voice->owner_event].desc, position, &gain);
    if (result != AUDIO_OK) return result;
    result = spatial_publish(voice, voice->epoch, gain);
    if (result != AUDIO_OK) return result;
    voice->position = position;
    return AUDIO_OK;
}

f32 audio_voice_spatial_gain(AudioSystem *as, AudioVoiceHandle handle) {
    AudioExtended *ext = audio_extended(as);
    AudioVoice *voice = voice_resolve(ext, handle, NULL);
    if (!voice) return 0.0f;
    return spatial_gain_of(atomic_load_explicit(&voice->spatial_snapshot,
                                                memory_order_acquire));
}

void audio_extended_listener_update(AudioSystem *as) {
    AudioExtended *ext = audio_extended(as);
    if (!ext) return;
    reap_voices(ext);
    for (u32 i = 2; i < AUDIO_MAX_VOICES; ++i) {
        AudioVoice *voice = &ext->voices[i];
        if (!voice->claimed || voice->owner_event < 0 || voice->stop_pending ||
            voice->spatial_revision == UINT32_MAX) {
            continue;
        }
        f32 gain = 0.0f;
        if (event_spatial_gain(ext, &ext->events[voice->owner_event].desc,
                               voice->position, &gain) == AUDIO_OK) {
            (void)spatial_publish(voice, voice->epoch, gain);
        }
    }
}

void audio_extended_set_bus_gain(AudioSystem *as, u32 bus, f32 gain) {
    AudioExtended *ext = audio_extended(as);
    if (!ext || bus >= AUDIO_MAX_BUSES || !isfinite(gain)) return;
    atomic_store_explicit(&ext->bus_gains[bus], gain_to_bits(gain),
                          memory_order_release);
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

static AudioEventDesc music_event_desc(const AudioExtended *ext) {
    AudioEventDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.volume = ext->playlist_volume;
    desc.bus = ext->playlist_bus;
    return desc;
}

static bool music_voice_done(const AudioExtended *ext, u32 slot) {
    if (slot == UINT32_MAX) return true;
    const AudioVoice *voice = &ext->voices[slot];
    return !voice->claimed || atomic_load_explicit(&voice->completed_epoch,
        memory_order_acquire) == voice->epoch;
}

static void music_clear(AudioExtended *ext) {
    ext->music_state = AUDIO_MUSIC_STOPPED;
    ext->music_current = UINT32_MAX;
    ext->music_previous = UINT32_MAX;
    ext->music_index = 0;
}

static AudioResult music_ramp_out(AudioExtended *ext, u32 slot, u32 frames) {
    AudioVoice *voice = &ext->voices[slot];
    AudioCommand command;
    memset(&command, 0, sizeof(command));
    command.type = AUDIO_COMMAND_RAMP;
    command.serial = voice->serial;
    command.epoch = voice->epoch;
    command.ramp_target = 0.0f;
    command.ramp_frames = frames;
    command.stop_after_ramp = true;
    if (!voice_enqueue(voice, &command)) return AUDIO_OVERLOAD;
    return AUDIO_OK;
}

static AudioResult music_start_next(AudioExtended *ext, u32 next_index) {
    u32 old_slot = ext->music_current;
    u32 new_slot = old_slot == 0 ? 1u : 0u;
    if (ext->voices[new_slot].claimed) return AUDIO_OVERLOAD;
    if (!voice_command_space(&ext->voices[new_slot])) return AUDIO_OVERLOAD;
    if (old_slot != UINT32_MAX && ext->voices[old_slot].claimed &&
        !voice_command_space(&ext->voices[old_slot])) return AUDIO_OVERLOAD;

    AudioEventDesc desc = music_event_desc(ext);
    f32 initial_gain = ext->playlist_fade > 0 ? 0.0f : 1.0f;
    AudioResult result = voice_start_pcm(ext, new_slot,
        ext->playlist[next_index], &desc, -2, true, initial_gain,
        ext->playlist_fade, vec3(0, 0, 0), 1.0f, NULL);
    if (result != AUDIO_OK) return result;
    if (old_slot != UINT32_MAX && ext->voices[old_slot].claimed) {
        if (ext->playlist_fade > 0) {
            result = music_ramp_out(ext, old_slot, ext->playlist_fade);
        } else {
            AudioCommand command;
            memset(&command, 0, sizeof(command));
            command.type = AUDIO_COMMAND_STOP;
            command.serial = ext->voices[old_slot].serial;
            command.epoch = ext->voices[old_slot].epoch;
            result = voice_enqueue(&ext->voices[old_slot], &command) ?
                     AUDIO_OK : AUDIO_OVERLOAD;
        }
        if (result != AUDIO_OK) return result;
    }
    ext->music_previous = ext->playlist_fade > 0 ? old_slot : UINT32_MAX;
    ext->music_current = new_slot;
    ext->music_index = next_index;
    ext->music_state = ext->playlist_fade > 0 ?
                       AUDIO_MUSIC_CROSSFADING : AUDIO_MUSIC_PLAYING;
    return AUDIO_OK;
}

AudioResult audio_music_set_playlist(AudioSystem *as,
    const AudioMusicPlaylistDesc *desc) {
    AudioExtended *ext = audio_extended(as);
    if (!ext || !desc || !desc->tracks || desc->track_count == 0 ||
        !isfinite(desc->volume) || desc->volume < 0.0f ||
        desc->bus >= as->bus_count) return AUDIO_INVALID;
    if (ext->music_state != AUDIO_MUSIC_STOPPED) return AUDIO_REJECTED;
    if (desc->track_count > AUDIO_MUSIC_MAX_TRACKS) return AUDIO_OVERLOAD;
    for (u32 i = 0; i < desc->track_count; ++i) {
        AudioClip *clip = clip_resolve(ext, desc->tracks[i]);
        if (!clip) return AUDIO_STALE;
        if (desc->crossfade_frames > clip->frame_count) return AUDIO_INVALID;
    }
    memcpy(ext->playlist, desc->tracks,
           desc->track_count * sizeof(ext->playlist[0]));
    ext->playlist_count = desc->track_count;
    ext->playlist_loop = desc->loop;
    ext->playlist_fade = desc->crossfade_frames;
    ext->playlist_volume = desc->volume;
    ext->playlist_bus = desc->bus;
    ext->playlist_set = true;
    return AUDIO_OK;
}

AudioResult audio_music_play(AudioSystem *as) {
    AudioExtended *ext = audio_extended(as);
    if (!ext || !ext->playlist_set) return AUDIO_INVALID;
    if (ext->music_state != AUDIO_MUSIC_STOPPED) return AUDIO_REJECTED;
    reap_voices(ext);
    AudioEventDesc desc = music_event_desc(ext);
    AudioResult result = voice_start_pcm(ext, 0, ext->playlist[0], &desc,
        -2, true, 1.0f, 0, vec3(0, 0, 0), 1.0f, NULL);
    if (result != AUDIO_OK) return result;
    ext->music_current = 0;
    ext->music_previous = UINT32_MAX;
    ext->music_index = 0;
    ext->music_state = AUDIO_MUSIC_PLAYING;
    return AUDIO_OK;
}

AudioResult audio_music_stop(AudioSystem *as) {
    AudioExtended *ext = audio_extended(as);
    if (!ext) return AUDIO_INVALID;
    if (ext->music_state == AUDIO_MUSIC_STOPPED) return AUDIO_OK;
    reap_voices(ext);
    u32 slots[2] = {ext->music_current, ext->music_previous};
    for (u32 i = 0; i < 2; ++i) {
        if (slots[i] != UINT32_MAX && ext->voices[slots[i]].claimed &&
            !voice_command_space(&ext->voices[slots[i]])) return AUDIO_OVERLOAD;
    }
    for (u32 i = 0; i < 2; ++i) {
        if (slots[i] == UINT32_MAX || !ext->voices[slots[i]].claimed) continue;
        AudioCommand command;
        memset(&command, 0, sizeof(command));
        command.type = AUDIO_COMMAND_STOP;
        command.serial = ext->voices[slots[i]].serial;
        command.epoch = ext->voices[slots[i]].epoch;
        if (!voice_enqueue(&ext->voices[slots[i]], &command)) return AUDIO_OVERLOAD;
    }
    ext->music_state = AUDIO_MUSIC_STOPPING;
    if (music_voice_done(ext, ext->music_current) &&
        music_voice_done(ext, ext->music_previous)) music_clear(ext);
    return AUDIO_OK;
}

AudioResult audio_music_update(AudioSystem *as) {
    AudioExtended *ext = audio_extended(as);
    if (!ext) return AUDIO_INVALID;
    reap_voices(ext);
    if (ext->music_state == AUDIO_MUSIC_STOPPED) return AUDIO_OK;
    if (ext->music_state == AUDIO_MUSIC_STOPPING) {
        if (music_voice_done(ext, ext->music_current) &&
            music_voice_done(ext, ext->music_previous)) music_clear(ext);
        return AUDIO_OK;
    }
    if (ext->music_state == AUDIO_MUSIC_CROSSFADING) {
        if (music_voice_done(ext, ext->music_previous)) {
            ext->music_previous = UINT32_MAX;
            ext->music_state = AUDIO_MUSIC_PLAYING;
        }
        return AUDIO_OK;
    }

    AudioVoice *current = &ext->voices[ext->music_current];
    if (atomic_load_explicit(&current->started_epoch, memory_order_acquire) !=
        current->epoch) return AUDIO_OK;
    AudioClip *clip = clip_resolve(ext, ext->playlist[ext->music_index]);
    if (!clip) return AUDIO_STALE;
    u32 cursor = atomic_load_explicit(&current->cursor, memory_order_acquire);
    if (cursor < clip->frame_count - ext->playlist_fade) return AUDIO_OK;
    bool has_next = ext->music_index + 1u < ext->playlist_count ||
                    ext->playlist_loop;
    if (!has_next) {
        if (ext->playlist_fade > 0 && !music_voice_done(ext, ext->music_current)) {
            if (!voice_command_space(&ext->voices[ext->music_current])) {
                return AUDIO_OVERLOAD;
            }
            AudioResult result = music_ramp_out(ext, ext->music_current,
                                                 ext->playlist_fade);
            if (result != AUDIO_OK) return result;
            ext->music_state = AUDIO_MUSIC_STOPPING;
        } else if (music_voice_done(ext, ext->music_current)) {
            music_clear(ext);
        }
        return AUDIO_OK;
    }
    u32 next = ext->music_index + 1u < ext->playlist_count ?
               ext->music_index + 1u : 0u;
    return music_start_next(ext, next);
}

AudioResult audio_music_state(AudioSystem *as, AudioMusicState *out_state,
                              u32 *out_track_index) {
    AudioExtended *ext = audio_extended(as);
    if (!ext || (!out_state && !out_track_index)) return AUDIO_INVALID;
    if (out_state) *out_state = ext->music_state;
    if (out_track_index) *out_track_index = ext->music_index;
    return AUDIO_OK;
}
