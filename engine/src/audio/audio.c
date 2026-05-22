#include <audio/audio.h>
#include <core/log.h>
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
    AudioSystem *as = calloc(1, sizeof(AudioSystem));
    struct AudioImpl *impl = calloc(1, sizeof(struct AudioImpl));

    ma_result result = ma_engine_init(NULL, &impl->engine);
    if (result != MA_SUCCESS) {
        LOG_ERROR("Failed to init audio engine (%d)", result);
        free(impl);
        free(as);
        return NULL;
    }

    as->engine = impl;
    as->source_cap = 32;
    as->sources = calloc(as->source_cap, sizeof(AudioSource));
    as->source_count = 0;
    as->listener_forward = vec3(0, 0, -1);
    as->listener_up = vec3(0, 1, 0);

    LOG_INFO("Audio system initialized");
    return as;
}

void audio_system_destroy(AudioSystem *as) {
    if (!as) return;
    struct AudioImpl *impl = as->engine;
    if (!impl) { free(as); return; }

    for (u32 i = 0; i < as->source_count; i++) {
        if (as->sources[i].active) {
            ma_sound_uninit(&as->sources[i].sound);
        }
    }
    ma_engine_uninit(&impl->engine);
    free(as->sources);
    free(impl);
    free(as);
}

void audio_system_update(AudioSystem *as, Vec3 listener_pos, Vec3 forward, Vec3 up) {
    if (!as || !as->engine) return;
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

u32 audio_play(AudioSystem *as, const char *path, f32 volume, bool looping) {
    if (!as || !as->engine) return 0;
    if (as->source_count >= as->source_cap) return 0;

    struct AudioImpl *impl = as->engine;
    u32 id = as->source_count++;
    AudioSource *src = &as->sources[id];

    ma_result result = ma_sound_init_from_file(&impl->engine, path, 0, NULL, NULL, &src->sound);
    if (result != MA_SUCCESS) {
        LOG_WARN("Failed to load sound: %s (%d)", path, result);
        as->source_count--;
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
    AudioSource *src = &as->sources[source_id - 1];
    if (src->active) {
        ma_sound_stop(&src->sound);
    }
}

void audio_set_listener(AudioSystem *as, Vec3 pos, Vec3 forward, Vec3 up) {
    audio_system_update(as, pos, forward, up);
}
