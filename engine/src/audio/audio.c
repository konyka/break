#include <audio/audio.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

struct AudioSource {
    ma_sound  sound;
    bool      active;
};

struct AudioImpl {
    ma_engine engine;
};

AudioSystem *audio_system_create(void) {
    /* Single alloc: AudioSystem + AudioImpl (aligned to max_align_t) */
    usize as_sz  = sizeof(AudioSystem);
    usize align  = _Alignof(max_align_t);
    usize as_off = (as_sz + align - 1) & ~(align - 1);
    u8 *audio_block = (u8 *)calloc(1, as_off + sizeof(struct AudioImpl));
    if (!audio_block) {
        LOG_ERROR("Audio: system allocation failed");
        return NULL;
    }
    AudioSystem *as  = (AudioSystem *)audio_block;
    struct AudioImpl *impl = (struct AudioImpl *)(audio_block + as_off);

    ma_result result = ma_engine_init(NULL, &impl->engine);
    if (result != MA_SUCCESS) {
        LOG_ERROR("Failed to init audio engine (%d)", result);
        free(as);
        return NULL;
    }

    as->engine = impl;
    as->source_cap = 32;
    as->sources = calloc(as->source_cap, sizeof(AudioSource));
    if (!as->sources) {
        LOG_ERROR("Audio: sources allocation failed");
        ma_engine_uninit(&impl->engine);
        free(as);
        return NULL;
    }
    as->source_count = 0;
    as->listener_forward = vec3(0, 0, -1);
    as->listener_up = vec3(0, 1, 0);

    LOG_INFO("Audio system initialized");
    return as;
}

void audio_system_destroy(AudioSystem *as) {
    if (!as) return;
    /* Recompute impl pointer from the same single-allocation layout */
    usize as_sz  = sizeof(AudioSystem);
    usize align  = _Alignof(max_align_t);
    usize as_off = (as_sz + align - 1) & ~(align - 1);
    struct AudioImpl *impl = (struct AudioImpl *)((u8 *)as + as_off);

    for (u32 i = 0; i < as->source_count; i++) {
        if (as->sources[i].active) {
            ma_sound_uninit(&as->sources[i].sound);
        }
    }
    ma_engine_uninit(&impl->engine);
    free(as->sources);
    free(as); /* single free: AudioSystem + AudioImpl */
}

void audio_system_update(AudioSystem *as, Vec3 listener_pos, Vec3 forward, Vec3 up) {
    if (!as || !as->engine) return;

    /* Dirty check: skip 3 miniaudio calls when listener hasn't moved */
    bool moved = (as->listener_pos.e[0] != listener_pos.e[0] ||
                  as->listener_pos.e[1] != listener_pos.e[1] ||
                  as->listener_pos.e[2] != listener_pos.e[2] ||
                  as->listener_forward.e[0] != forward.e[0] ||
                  as->listener_forward.e[1] != forward.e[1] ||
                  as->listener_forward.e[2] != forward.e[2] ||
                  as->listener_up.e[0] != up.e[0] ||
                  as->listener_up.e[1] != up.e[1] ||
                  as->listener_up.e[2] != up.e[2]);
    if (!moved) return;

    as->listener_pos = listener_pos;
    as->listener_forward = forward;
    as->listener_up = up;

    struct AudioImpl *impl = as->engine;
    ma_engine_listener_set_position(&impl->engine, 0,
        listener_pos.e[0], listener_pos.e[1], listener_pos.e[2]);
    ma_engine_listener_set_direction(&impl->engine, 0,
        forward.e[0], forward.e[1], forward.e[2]);
    ma_engine_listener_set_world_up(&impl->engine, 0,
        up.e[0], up.e[1], up.e[2]);
}

/* Acquire a source slot: free-list first, then bump-allocate */
static u32 audio_acquire_slot(AudioSystem *as) {
    if (as->free_count > 0) {
        return as->free_list[--as->free_count];
    }
    if (as->source_count < as->source_cap) {
        return as->source_count++;
    }
    return UINT32_MAX;  /* exhausted */
}

u32 audio_play(AudioSystem *as, const char *path, f32 volume, bool looping) {
    if (!as || !as->engine) return 0;

    u32 id = audio_acquire_slot(as);
    if (id == UINT32_MAX) return 0;

    struct AudioImpl *impl = as->engine;
    AudioSource *src = &as->sources[id];

    ma_result result = ma_sound_init_from_file(&impl->engine, path, 0, NULL, NULL, &src->sound);
    if (result != MA_SUCCESS) {
        LOG_WARN("Failed to load sound: %s (%d)", path, result);
        /* Return slot to free-list */
        if (as->free_count < AUDIO_MAX_SOURCES) {
            as->free_list[as->free_count++] = id;
        }
        return 0;
    }

    ma_sound_set_volume(&src->sound, volume);
    ma_sound_set_looping(&src->sound, looping);
    ma_sound_start(&src->sound);
    src->active = true;
    return id + 1;
}

void audio_play_3d(AudioSystem *as, const char *path, Vec3 position, f32 volume, bool looping) {
    u32 id = audio_play(as, path, volume, looping);
    if (id == 0) return;
    AudioSource *src = &as->sources[id - 1];
    ma_sound_set_position(&src->sound, position.e[0], position.e[1], position.e[2]);
}

void audio_stop(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0 || source_id > as->source_count) return;
    u32 idx = source_id - 1;
    AudioSource *src = &as->sources[idx];
    if (src->active) {
        ma_sound_stop(&src->sound);
        ma_sound_uninit(&src->sound);
        src->active = false;
        /* Return slot to free-list for reuse */
        if (as->free_count < AUDIO_MAX_SOURCES) {
            as->free_list[as->free_count++] = idx;
        }
    }
}

u32 audio_play_streamed(AudioSystem *as, const char *path, f32 volume,
                        bool looping, bool spatial, Vec3 position) {
    if (!as || !as->engine || !path) return 0;

    u32 id = audio_acquire_slot(as);
    if (id == UINT32_MAX) return 0;

    struct AudioImpl *impl = as->engine;
    AudioSource *src = &as->sources[id];

    ma_uint32 flags = MA_SOUND_FLAG_STREAM;
    if (!spatial) flags |= MA_SOUND_FLAG_NO_SPATIALIZATION;

    ma_result result = ma_sound_init_from_file(&impl->engine, path, flags, NULL, NULL, &src->sound);
    if (result != MA_SUCCESS) {
        LOG_WARN("Failed to stream sound: %s (%d)", path, result);
        if (as->free_count < AUDIO_MAX_SOURCES) {
            as->free_list[as->free_count++] = id;
        }
        return 0;
    }

    ma_sound_set_volume(&src->sound, volume);
    ma_sound_set_looping(&src->sound, looping);
    if (spatial) {
        ma_sound_set_spatialization_enabled(&src->sound, MA_TRUE);
        ma_sound_set_attenuation_model(&src->sound, ma_attenuation_model_inverse);
        ma_sound_set_position(&src->sound, position.e[0], position.e[1], position.e[2]);
    }
    ma_sound_start(&src->sound);
    src->active = true;
    LOG_INFO("Audio: streaming '%s' (source %u, %s)", path, id + 1,
             spatial ? "3D" : "2D");
    return id + 1;
}

void audio_source_set_position(AudioSystem *as, u32 source_id, Vec3 position) {
    if (!as || source_id == 0 || source_id > as->source_count) return;
    AudioSource *src = &as->sources[source_id - 1];
    if (src->active) {
        ma_sound_set_position(&src->sound, position.e[0], position.e[1], position.e[2]);
    }
}

void audio_source_set_attenuation(AudioSystem *as, u32 source_id,
                                  f32 min_dist, f32 max_dist, f32 rolloff) {
    if (!as || source_id == 0 || source_id > as->source_count) return;
    AudioSource *src = &as->sources[source_id - 1];
    if (!src->active) return;
    ma_sound_set_attenuation_model(&src->sound, ma_attenuation_model_inverse);
    ma_sound_set_min_distance(&src->sound, min_dist);
    ma_sound_set_max_distance(&src->sound, max_dist);
    ma_sound_set_rolloff(&src->sound, rolloff);
}

void audio_source_set_volume(AudioSystem *as, u32 source_id, f32 volume) {
    if (!as || source_id == 0 || source_id > as->source_count) return;
    AudioSource *src = &as->sources[source_id - 1];
    if (src->active) ma_sound_set_volume(&src->sound, volume);
}

void audio_source_start(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0 || source_id > as->source_count) return;
    AudioSource *src = &as->sources[source_id - 1];
    if (src->active) ma_sound_start(&src->sound);
}

void audio_source_stop(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0 || source_id > as->source_count) return;
    AudioSource *src = &as->sources[source_id - 1];
    /* R241: Pause only — ma_sound_stop halts playback but preserves the cursor
     * and keeps the sound initialized and its slot allocated (unlike audio_stop,
     * which uninits the sound and returns the slot to the free-list). This lets
     * audio_source_start() resume from the same position. */
    if (src->active) ma_sound_stop(&src->sound);
}

bool audio_source_at_end(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0 || source_id > as->source_count) return true;
    AudioSource *src = &as->sources[source_id - 1];
    if (!src->active) return true;
    return ma_sound_at_end(&src->sound) == MA_TRUE;
}

f32 audio_source_cursor_seconds(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0 || source_id > as->source_count) return 0.0f;
    AudioSource *src = &as->sources[source_id - 1];
    if (!src->active) return 0.0f;
    float cursor = 0.0f;
    ma_sound_get_cursor_in_seconds(&src->sound, &cursor);
    return (f32)cursor;
}

void audio_set_listener(AudioSystem *as, Vec3 pos, Vec3 forward, Vec3 up) {
    audio_system_update(as, pos, forward, up);
}

/* ---- Device enumeration & selection ---- */

u32 audio_get_device_count(AudioSystem *sys) {
    if (!sys || !sys->engine) return 0;

    /* Return cached result to avoid re-creating ma_context (10-100ms) each call */
    if (sys->devices_enumerated) return sys->device_count;

    ma_context context;
    if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS) {
        LOG_WARN("Failed to init audio context for device enumeration");
        return 0;
    }

    ma_device_info *playback_infos = NULL;
    ma_uint32       playback_count = 0;
    ma_device_info *capture_infos  = NULL;
    ma_uint32       capture_count  = 0;

    if (ma_context_get_devices(&context, &playback_infos, &playback_count,
                               &capture_infos, &capture_count) != MA_SUCCESS) {
        ma_context_uninit(&context);
        return 0;
    }

    sys->device_count = playback_count < AUDIO_MAX_DEVICES ? playback_count : AUDIO_MAX_DEVICES;
    for (u32 i = 0; i < sys->device_count; i++) {
        strncpy(sys->devices[i].name, playback_infos[i].name, 127);
        sys->devices[i].name[127] = '\0';
        /* Use index as id (miniaudio's ma_device_id is an opaque struct) */
        snprintf(sys->devices[i].id, 63, "%u", i);
        sys->devices[i].id[63] = '\0';
        sys->devices[i].is_default = (bool)playback_infos[i].isDefault;
    }

    sys->devices_enumerated = true;
    ma_context_uninit(&context);
    return sys->device_count;
}

bool audio_get_device_info(AudioSystem *sys, u32 index, AudioDeviceInfo *out) {
    if (!sys || index >= sys->device_count || !out) return false;
    *out = sys->devices[index];
    return true;
}

bool audio_set_device(AudioSystem *sys, const char *device_id) {
    if (!sys || !device_id) return false;

    u32 idx = (u32)atoi(device_id);
    if (idx >= sys->device_count) return false;

    /* Record current device name */
    strncpy(sys->current_device, sys->devices[idx].name, 127);
    sys->current_device[127] = '\0';

    /* NOTE: miniaudio's ma_engine does not support hot-swapping the output
     * device directly. We record the selection here; it will take effect on
     * the next audio_system_create / engine reinit. */
    LOG_INFO("Audio device queued for next reinit: %s", sys->current_device);
    return false; /* hot-swap not supported; caller must reinit audio system */
}

const char *audio_get_current_device(AudioSystem *sys) {
    if (!sys) return "unknown";
    if (sys->current_device[0] == '\0') return "default";
    return sys->current_device;
}
