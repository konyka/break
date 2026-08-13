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
    u32       generation; /* R419: ABA guard, bumped each time the slot is freed */
    f32       volume;     /* R435: last set source volume (bus recomposition) */
    f32       applied_gain; /* Last gain submitted to miniaudio (or pending activation). */
    u32       bus;        /* R435: routing bus; AUDIO_BUS_MASTER by default */
};

/* ---- R435: mixing buses ----
 * The bus table lives inside AudioSystem: reset on audio_system_create,
 * gone after audio_system_destroy. Slot 0 is the master bus. */

static void audio_bus_table_reset(AudioSystem *as) {
    memset(as->buses, 0, sizeof(as->buses));
    as->bus_count = 1;
    as->buses[AUDIO_BUS_MASTER].gain = 1.0f;
    strncpy(as->buses[AUDIO_BUS_MASTER].name, "master",
            sizeof(as->buses[AUDIO_BUS_MASTER].name) - 1);
}

static bool audio_bus_valid(const AudioSystem *as, u32 bus) {
    /* R550-F: bus_count never exceeds AUDIO_MAX_BUSES (audio_bus_create
     * enforces it), so the extra capacity comparison is runtime-redundant —
     * but it keeps every buses[] subscript downstream provably in-bounds for
     * the compiler (Release GCC -Warray-bounds fired on the inlined
     * invalid-id test paths with a constant 999 id). */
    return as && bus < as->bus_count && bus < AUDIO_MAX_BUSES;
}

/* Effective gain pushed to miniaudio: volume x bus gain x master gain.
 * The master bus IS the master fader, so a source routed to bus 0 skips the
 * separate bus factor (otherwise master gain would be applied twice). */
static f32 audio_source_effective_gain(const AudioSystem *as,
                                       const AudioSource *src) {
    f32 bus_gain = 1.0f;
    if (src->bus != AUDIO_BUS_MASTER && audio_bus_valid(as, src->bus)) {
        bus_gain = as->buses[src->bus].gain;
    }
    return audio_effective_gain(src->volume, bus_gain,
                                as->buses[AUDIO_BUS_MASTER].gain);
}

static void audio_source_apply_gain(AudioSystem *as, AudioSource *src) {
    src->applied_gain = audio_source_effective_gain(as, src);
    if (src->active) {
        ma_sound_set_volume(&src->sound, src->applied_gain);
    }
}

/* R419 (HANDLE ABA): source handles were bare slot indices (id+1) recycled via
 * the free-list, so a stale handle silently aliased a new sound on the same
 * slot. Handles now pack a per-slot generation in the upper 24 bits and the
 * slot+1 in the low 8 bits (AUDIO_MAX_SOURCES=32, so slot+1 always fits).
 * The public handle type (u32) is unchanged; generation 0 keeps the first
 * handle for a slot numerically identical to the old scheme. */
#define AUDIO_HANDLE_GEN_SHIFT 8u
#define AUDIO_HANDLE_SLOT_MASK 0xFFu

static u32 audio_make_handle(const AudioSource *src, u32 slot) {
    return (src->generation << AUDIO_HANDLE_GEN_SHIFT) | (slot + 1u);
}

/* Resolve a handle to its source, or NULL if the handle is stale/invalid. */
static AudioSource *audio_resolve(AudioSystem *as, u32 handle) {
    if (!as) return NULL;
    u32 slot = handle & AUDIO_HANDLE_SLOT_MASK;
    if (slot == 0 || slot > as->source_count) return NULL;
    AudioSource *src = &as->sources[slot - 1u];
    if ((handle >> AUDIO_HANDLE_GEN_SHIFT) != src->generation) return NULL;
    return src;
}

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
    audio_bus_table_reset(as); /* R435: master bus exists from birth */

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
    /* R423: NULL path guard (audio_play_streamed already has one). */
    if (!as || !as->engine || !path) return 0;

    u32 id = audio_acquire_slot(as);
    if (id == UINT32_MAX) return 0;

    struct AudioImpl *impl = as->engine;
    AudioSource *src = &as->sources[id];

    /* R270 (CORRECTNESS): audio_play() takes no position — it is the 2D /
     * non-positional variant (UI, music), paired with audio_play_3d() which
     * adds a world position. miniaudio enables spatialization BY DEFAULT
     * (flags=0) and initializes a sound's position to the origin (0,0,0), so a
     * "2D" sound played here was actually spatialized: once the listener moved
     * away from the origin (audio_system_update follows the camera every
     * frame), it attenuated by listener distance — e.g. listener at (10,0,0)
     * with the sound pinned at the origin gives inverse-model gain
     * 1/(1+(10-1)) = 0.1 instead of the intended full-volume 1.0. The
     * streaming path already guards this (audio_play_streamed sets
     * MA_SOUND_FLAG_NO_SPATIALIZATION when !spatial); mirror it here so 2D
     * sounds stay 2D. audio_play_3d re-enables spatialization explicitly. */
    ma_result result = ma_sound_init_from_file(&impl->engine, path,
                                               MA_SOUND_FLAG_NO_SPATIALIZATION,
                                               NULL, NULL, &src->sound);
    if (result != MA_SUCCESS) {
        LOG_WARN("Failed to load sound: %s (%d)", path, result);
        /* Return slot to free-list */
        if (as->free_count < AUDIO_MAX_SOURCES) {
            as->free_list[as->free_count++] = id;
        }
        return 0;
    }

    src->volume = volume;             /* R435: remember for bus recomposition */
    src->bus = AUDIO_BUS_MASTER;      /* R435: recycled slots re-route to master */
    src->applied_gain = audio_source_effective_gain(as, src);
    ma_sound_set_volume(&src->sound, src->applied_gain);
    ma_sound_set_looping(&src->sound, looping);
    ma_sound_start(&src->sound);
    src->active = true;
    return audio_make_handle(src, id);
}

void audio_play_3d(AudioSystem *as, const char *path, Vec3 position, f32 volume, bool looping) {
    u32 handle = audio_play(as, path, volume, looping);
    if (handle == 0) return;
    AudioSource *src = audio_resolve(as, handle);
    if (!src) return;
    /* R270 (CORRECTNESS): audio_play() now inits with NO_SPATIALIZATION, so a
     * 3D sound must re-enable it (and pick the same inverse-distance model the
     * streaming 3D path uses) before positioning it. */
    ma_sound_set_spatialization_enabled(&src->sound, MA_TRUE);
    ma_sound_set_attenuation_model(&src->sound, ma_attenuation_model_inverse);
    ma_sound_set_position(&src->sound, position.e[0], position.e[1], position.e[2]);
}

void audio_stop(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0) return;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return; /* R419: stale or out-of-range handle — no-op */
    if (src->active) {
        ma_sound_stop(&src->sound);
        ma_sound_uninit(&src->sound);
        src->active = false;
        /* R419: invalidate outstanding handles before recycling the slot.
         * R423: wrap at 24 bits — at generation 2^24 the raw increment made
         * generation<<8 truncate to 0, so audio_resolve rejected the very next
         * handle issued for this slot (sound unstoppable, slot leaked). The
         * wrap accepts a theoretical ABA (stale gen-0 handle resolving after
         * exactly 2^24 recycles) over that breakage. */
        src->generation = (src->generation + 1u) & 0xFFFFFFu;
        u32 idx = (source_id & AUDIO_HANDLE_SLOT_MASK) - 1u;
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

    src->volume = volume;             /* R435 */
    src->bus = AUDIO_BUS_MASTER;      /* R435 */
    src->applied_gain = audio_source_effective_gain(as, src);
    ma_sound_set_volume(&src->sound, src->applied_gain);
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
    return audio_make_handle(src, id);
}

void audio_source_set_position(AudioSystem *as, u32 source_id, Vec3 position) {
    if (!as || source_id == 0) return;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return; /* R419: stale handle — no-op */
    if (src->active) {
        ma_sound_set_position(&src->sound, position.e[0], position.e[1], position.e[2]);
    }
}

void audio_source_set_attenuation(AudioSystem *as, u32 source_id,
                                  f32 min_dist, f32 max_dist, f32 rolloff) {
    if (!as || source_id == 0) return;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return; /* R419: stale handle — no-op */
    if (!src->active) return;
    ma_sound_set_attenuation_model(&src->sound, ma_attenuation_model_inverse);
    ma_sound_set_min_distance(&src->sound, min_dist);
    ma_sound_set_max_distance(&src->sound, max_dist);
    ma_sound_set_rolloff(&src->sound, rolloff);
}

void audio_source_set_volume(AudioSystem *as, u32 source_id, f32 volume) {
    if (!as || source_id == 0) return;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return; /* R419: stale handle — no-op */
    src->volume = volume; /* R435: keep raw (no clamp, existing policy); the
                           * effective gain clamps negatives at compose time */
    audio_source_apply_gain(as, src);
}

/* ---- R435: mixing buses (public API) ---- */

u32 audio_bus_create(AudioSystem *as, const char *name) {
    if (!as || !name) return AUDIO_BUS_INVALID;
    if (as->bus_count >= AUDIO_MAX_BUSES) {
        LOG_WARN("Audio: bus table full (%u buses)", (u32)AUDIO_MAX_BUSES);
        return AUDIO_BUS_INVALID;
    }
    u32 id = as->bus_count++;
    AudioBus *b = &as->buses[id];
    strncpy(b->name, name, sizeof(b->name) - 1);
    b->name[sizeof(b->name) - 1] = '\0';
    b->gain = 1.0f;
    return id;
}

void audio_bus_set_gain(AudioSystem *as, u32 bus, f32 gain) {
    if (!audio_bus_valid(as, bus)) return; /* R435: invalid id — refuse */
    if (gain < 0.0f) gain = 0.0f;          /* R435: clamp non-negative */
    as->buses[bus].gain = gain;
    /* Master participates in every route; regular buses only affect members. */
    for (u32 i = 0; i < as->source_count; i++) {
        AudioSource *src = &as->sources[i];
        if (bus == AUDIO_BUS_MASTER || src->bus == bus) {
            audio_source_apply_gain(as, src);
        }
    }
}

f32 audio_bus_gain(AudioSystem *as, u32 bus) {
    if (!as) return 1.0f;
    if (!audio_bus_valid(as, bus)) {
        return as->buses[AUDIO_BUS_MASTER].gain; /* R435: fall back to master */
    }
    return as->buses[bus].gain;
}

void audio_source_set_bus(AudioSystem *as, u32 source_id, u32 bus) {
    if (!as || source_id == 0) return;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return; /* R419: stale handle — no-op */
    if (!audio_bus_valid(as, bus)) {
        bus = AUDIO_BUS_MASTER; /* R435: invalid id — fall back to master */
    }
    src->bus = bus;
    audio_source_apply_gain(as, src);
}

void audio_source_start(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0) return;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return; /* R419: stale handle — no-op */
    if (src->active) ma_sound_start(&src->sound);
}

void audio_source_stop(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0) return;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return; /* R419: stale handle — no-op */
    /* R241: Pause only — ma_sound_stop halts playback but preserves the cursor
     * and keeps the sound initialized and its slot allocated (unlike audio_stop,
     * which uninits the sound and returns the slot to the free-list). This lets
     * audio_source_start() resume from the same position. */
    if (src->active) ma_sound_stop(&src->sound);
}

bool audio_source_at_end(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0) return true;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return true; /* R419: stale handle — treat as ended */
    if (!src->active) return true;
    return ma_sound_at_end(&src->sound) == MA_TRUE;
}

f32 audio_source_cursor_seconds(AudioSystem *as, u32 source_id) {
    if (!as || source_id == 0) return 0.0f;
    AudioSource *src = audio_resolve(as, source_id);
    if (!src) return 0.0f; /* R419: stale handle */
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
