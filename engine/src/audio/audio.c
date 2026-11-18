#include <audio/audio.h>
#include <core/log.h>
#include <core/platform_thread.h>
#include <math.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#if defined(ENGINE_PLATFORM_IOS)
#include <TargetConditionals.h>
#if TARGET_OS_SIMULATOR
#define AUDIO_SIMULATOR_NULL_BACKEND 1
#endif
#endif

#define MINIAUDIO_IMPLEMENTATION
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
#include <miniaudio.h>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

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
    ma_context context;
    bool context_initialized;
    i16 reference_ring[AUDIO_REFERENCE_RING_FRAMES];
    atomic_uint reference_head;
    atomic_uint reference_tail;
    atomic_uint reference_active;
    atomic_uint_least64_t reference_epoch;
    atomic_uint_least64_t reference_overruns;
    atomic_bool reference_enabled;
    atomic_bool simulated_lost;   /* simulated: lost until a reopen */
    atomic_uint_least64_t stopped_since_us; /* first seen not started, 0 = started */
    atomic_uint refused_reopens;  /* simulated: reopens still to refuse */
    atomic_uint_least64_t device_recoveries;
    ma_timer clock;               /* monotonic base for the loss grace period */
};

bool audio_extended_init(AudioSystem *as, ma_engine *engine);
void audio_extended_destroy(AudioSystem *as, void *extended);
void audio_extended_listener_update(AudioSystem *as);
void audio_extended_set_bus_gain(AudioSystem *as, u32 bus, f32 gain);

/* The AudioImpl offset formula below (mirrored in audio_system_destroy) aligns
 * the trailing impl block with _Alignof(long double); pin that this satisfies
 * ma_engine's alignment. */
_Static_assert(_Alignof(long double) >= 8,
               "AudioImpl alignment relies on _Alignof(long double) >= 8");
_Static_assert((AUDIO_REFERENCE_RING_FRAMES & (AUDIO_REFERENCE_RING_FRAMES - 1u)) == 0u,
               "Reference ring capacity must be a power of two");
_Static_assert(offsetof(struct AudioImpl, engine) == 0,
               "Device callbacks cast the engine back to the impl block");

static i16 audio_reference_sample(f32 left, f32 right) {
    f32 mono = 0.5f * (left + right);
    if (!isfinite(mono)) return 0;
    if (mono > 1.0f) mono = 1.0f;
    if (mono < -1.0f) mono = -1.0f;
    return (i16)lrintf(mono * 32767.0f);
}

static void audio_reference_on_process(void *user, f32 *frames, ma_uint64 frame_count) {
    struct AudioImpl *impl = (struct AudioImpl *)user;
    if (!impl || frame_count == 0u) return;
    const u64 epoch = atomic_load_explicit(&impl->reference_epoch, memory_order_acquire);
    if (!atomic_load_explicit(&impl->reference_enabled, memory_order_acquire)) return;
#ifdef AUDIO_REFERENCE_TEST_HOOK
    AUDIO_REFERENCE_TEST_HOOK(impl);
#endif
    atomic_fetch_add_explicit(&impl->reference_active, 1u, memory_order_acq_rel);
    if (atomic_load_explicit(&impl->reference_enabled, memory_order_acquire) &&
        epoch == atomic_load_explicit(&impl->reference_epoch, memory_order_acquire)) {
        const u32 head = atomic_load_explicit(&impl->reference_head, memory_order_relaxed);
        const u32 tail = atomic_load_explicit(&impl->reference_tail, memory_order_acquire);
        const ma_uint64 room =
            (ma_uint64)(AUDIO_REFERENCE_RING_FRAMES - (head - tail));
        const ma_uint64 count = frame_count < room ? frame_count : room;
        for (ma_uint64 i = 0u; i < count; ++i) {
            const u32 slot = (head + (u32)i) & (AUDIO_REFERENCE_RING_FRAMES - 1u);
            impl->reference_ring[slot] =
                audio_reference_sample(frames[(usize)i * 2u], frames[(usize)i * 2u + 1u]);
        }
        if (count != 0u) {
            atomic_store_explicit(&impl->reference_head, head + (u32)count,
                                  memory_order_release);
        }
        if (count < frame_count) {
            atomic_fetch_add_explicit(&impl->reference_overruns, (u64)(frame_count - count),
                                      memory_order_relaxed);
        }
    }
    atomic_fetch_sub_explicit(&impl->reference_active, 1u, memory_order_release);
}

static void audio_reference_wait_idle(struct AudioImpl *impl) {
    while (atomic_load_explicit(&impl->reference_active, memory_order_acquire) != 0u) {
        platform_thread_yield();
    }
}

AudioResult audio_reference_start(AudioSystem *as) {
    if (!as || !as->engine) return AUDIO_INVALID;
    struct AudioImpl *impl = (struct AudioImpl *)as->engine;
    atomic_store_explicit(&impl->reference_enabled, true, memory_order_release);
    return AUDIO_OK;
}

AudioResult audio_reference_stop(AudioSystem *as) {
    if (!as || !as->engine) return AUDIO_INVALID;
    struct AudioImpl *impl = (struct AudioImpl *)as->engine;
    if (atomic_exchange_explicit(&impl->reference_enabled, false, memory_order_acq_rel)) {
        atomic_fetch_add_explicit(&impl->reference_epoch, 1u, memory_order_acq_rel);
    }
    audio_reference_wait_idle(impl);
    return AUDIO_OK;
}

AudioResult audio_reference_reset(AudioSystem *as) {
    if (!as || !as->engine) return AUDIO_INVALID;
    struct AudioImpl *impl = (struct AudioImpl *)as->engine;
    if (atomic_load_explicit(&impl->reference_enabled, memory_order_acquire)) {
        return AUDIO_REJECTED;
    }
    const u32 head = atomic_load_explicit(&impl->reference_head, memory_order_acquire);
    atomic_store_explicit(&impl->reference_tail, head, memory_order_release);
    atomic_store_explicit(&impl->reference_overruns, 0u, memory_order_relaxed);
    return AUDIO_OK;
}

AudioResult audio_reference_read_i16(AudioSystem *as, i16 *out, u32 max_frames,
                                     u32 *out_frames) {
    if (!as || !as->engine || !out || !out_frames) return AUDIO_INVALID;
    struct AudioImpl *impl = (struct AudioImpl *)as->engine;
    const u32 tail = atomic_load_explicit(&impl->reference_tail, memory_order_relaxed);
    const u32 head = atomic_load_explicit(&impl->reference_head, memory_order_acquire);
    const u32 available = head - tail;
    const u32 count = available < max_frames ? available : max_frames;
    for (u32 i = 0u; i < count; ++i) {
        out[i] = impl->reference_ring[(tail + i) & (AUDIO_REFERENCE_RING_FRAMES - 1u)];
    }
    atomic_store_explicit(&impl->reference_tail, tail + count, memory_order_release);
    *out_frames = count;
    return AUDIO_OK;
}

u32 audio_reference_available(const AudioSystem *as) {
    if (!as || !as->engine) return 0u;
    const struct AudioImpl *impl = (const struct AudioImpl *)as->engine;
    return atomic_load_explicit(&impl->reference_head, memory_order_acquire) -
           atomic_load_explicit(&impl->reference_tail, memory_order_acquire);
}

u64 audio_reference_overruns(const AudioSystem *as) {
    if (!as || !as->engine) return 0u;
    const struct AudioImpl *impl = (const struct AudioImpl *)as->engine;
    return atomic_load_explicit(&impl->reference_overruns, memory_order_relaxed);
}

/* The device's user data is the engine, which is the first member of the
 * impl block, so both device callbacks reach the impl through it. */
static void audio_device_data_callback(ma_device *device, void *output, const void *input,
                                       ma_uint32 frame_count) {
    (void)input;
    ma_engine_read_pcm_frames((ma_engine *)device->pUserData, output, frame_count, NULL);
}

/* Every device backend miniaudio enables, in its order of preference (Null
 * last), each with a context the system owns. The engine keeps the
 * context's log, so a reopen must not free it with the old device. Like
 * ma_device_init_ex, the next backend is tried when the context or the
 * device does not open, and iOS playback uses the playback session. */
static ma_result audio_engine_init_with_context(struct AudioImpl *impl,
                                                ma_engine_config *engine_config,
                                                bool use_null) {
    ma_backend backends[MA_BACKEND_COUNT];
    size_t backend_count = 0u;
    if (use_null) {
        backends[0] = ma_backend_null;
        backend_count = 1u;
    } else if (ma_get_enabled_backends(backends, MA_BACKEND_COUNT, &backend_count) !=
               MA_SUCCESS) {
        return MA_NO_BACKEND;
    }
    ma_context_config context_config = ma_context_config_init();
#if defined(MA_APPLE_MOBILE)
    context_config.coreaudio.sessionCategory = ma_ios_session_category_playback;
#endif
    ma_result result = MA_NO_BACKEND;
    for (size_t i = 0u; i < backend_count; ++i) {
        result = ma_context_init(&backends[i], 1, &context_config, &impl->context);
        if (result != MA_SUCCESS) continue;
        engine_config->pContext = &impl->context;
        result = ma_engine_init(engine_config, &impl->engine);
        if (result == MA_SUCCESS) {
            impl->context_initialized = true;
            return MA_SUCCESS;
        }
        ma_context_uninit(&impl->context);
    }
    engine_config->pContext = NULL;
    return result;
}

AudioSystem *audio_system_create_ex(AudioBackend backend) {
    if (backend < AUDIO_BACKEND_DEFAULT || backend > AUDIO_BACKEND_FAKE) {
        return NULL;
    }
    usize as_sz  = sizeof(AudioSystem);
    usize align  = _Alignof(long double);
    usize as_off = (as_sz + align - 1) & ~(align - 1);
    u8 *audio_block = (u8 *)calloc(1, as_off + sizeof(struct AudioImpl));
    if (!audio_block) {
        LOG_ERROR("Audio: system allocation failed");
        return NULL;
    }
    AudioSystem *as  = (AudioSystem *)audio_block;
    struct AudioImpl *impl = (struct AudioImpl *)(audio_block + as_off);
    ma_timer_init(&impl->clock);
    ma_engine_config engine_config = ma_engine_config_init();
    const ma_engine_config *engine_config_ptr = &engine_config;
    ma_result result;
    bool use_null = backend == AUDIO_BACKEND_NULL;

#if defined(AUDIO_SIMULATOR_NULL_BACKEND)
    if (backend == AUDIO_BACKEND_DEFAULT) use_null = true;
#endif

    engine_config.channels = 2;
    engine_config.sampleRate = 48000;
    engine_config.onProcess = audio_reference_on_process;
    engine_config.pProcessUserData = impl;
    engine_config.dataCallback = audio_device_data_callback;
    engine_config.noDevice = backend == AUDIO_BACKEND_FAKE ? MA_TRUE : MA_FALSE;
    result = backend == AUDIO_BACKEND_FAKE
                 ? ma_engine_init(engine_config_ptr, &impl->engine)
                 : audio_engine_init_with_context(impl, &engine_config, use_null);
    if (result != MA_SUCCESS) {
        LOG_ERROR("Failed to init audio engine (%d)", result);
        if (impl->context_initialized) ma_context_uninit(&impl->context);
        free(as);
        return NULL;
    }

    as->engine = impl;
    as->backend = use_null && backend == AUDIO_BACKEND_DEFAULT ?
                  AUDIO_BACKEND_NULL : backend;
    as->source_cap = AUDIO_MAX_SOURCES;
    as->sources = calloc(as->source_cap, sizeof(AudioSource));
    if (!as->sources) {
        LOG_ERROR("Audio: sources allocation failed");
        ma_engine_uninit(&impl->engine);
        if (impl->context_initialized) ma_context_uninit(&impl->context);
        free(as);
        return NULL;
    }
    as->source_count = 0;
    as->listener_forward = vec3(0, 0, -1);
    as->listener_up = vec3(0, 1, 0);
    audio_bus_table_reset(as);
    if (!audio_extended_init(as, &impl->engine)) {
        LOG_ERROR("Audio: fixed voice pool initialization failed");
        free(as->sources);
        ma_engine_uninit(&impl->engine);
        if (impl->context_initialized) ma_context_uninit(&impl->context);
        free(as);
        return NULL;
    }

    if (use_null) LOG_WARN("Audio system initialized with null backend (silent)");
    else LOG_INFO("Audio system initialized");
    return as;
}

const char *audio_system_backend_name(const AudioSystem *as) {
    if (!as || !as->engine) return "none";
    if (as->backend == AUDIO_BACKEND_FAKE) return "fake";
    struct AudioImpl *impl = (struct AudioImpl *)as->engine;
    ma_device *device = ma_engine_get_device(&impl->engine);
    if (!device || !device->pContext) return "none";
    return ma_get_backend_name(device->pContext->backend);
}

bool audio_system_device_name(const AudioSystem *as, char *out, usize capacity) {
    if (!out || capacity == 0u) return false;
    snprintf(out, capacity, "%s", "none");
    if (!as || !as->engine || as->backend == AUDIO_BACKEND_FAKE) return false;
    struct AudioImpl *impl = (struct AudioImpl *)as->engine;
    ma_device *device = ma_engine_get_device(&impl->engine);
    if (!device || ma_device_get_state(device) == ma_device_state_uninitialized) return false;
    ma_device_info info;
    memset(&info, 0, sizeof(info));
    if (ma_device_get_info(device, ma_device_type_playback, &info) != MA_SUCCESS ||
        info.name[0] == '\0') {
        return false;
    }
    snprintf(out, capacity, "%s", info.name);
    return true;
}

static struct AudioImpl *audio_impl(const AudioSystem *as) {
    return as ? (struct AudioImpl *)as->engine : NULL;
}

/* Backends stop and restart a device on their own (a PulseAudio suspend, a
 * WASAPI reroute on the notification thread), so a device counts as lost
 * only once it has stayed out of the started state this long. */
#define AUDIO_DEVICE_LOSS_GRACE_US 250000u

/* Microseconds on miniaudio's monotonic timer, never 0 (0 means started). */
static u64 audio_now_us(struct AudioImpl *impl) {
    return (u64)(ma_timer_get_time_in_seconds(&impl->clock) * 1000000.0) + 1u;
}

static bool audio_device_started(struct AudioImpl *impl) {
    ma_device *device = ma_engine_get_device(&impl->engine);
    return device && ma_device_get_state(device) == ma_device_state_started;
}

bool audio_system_lost(const AudioSystem *as) {
    struct AudioImpl *impl = audio_impl(as);
    if (!impl) return false;
    if (atomic_load_explicit(&impl->simulated_lost, memory_order_acquire)) return true;
    if (as->backend == AUDIO_BACKEND_FAKE) return false;
    /* Nothing here stops the playback device on purpose, and miniaudio
     * posts no stop notification when a backend fails to stop a stream
     * whose device went away, so the device state decides. */
    if (audio_device_started(impl)) {
        atomic_store_explicit(&impl->stopped_since_us, 0u, memory_order_relaxed);
        return false;
    }
    const u64 now = audio_now_us(impl);
    u64 since = atomic_load_explicit(&impl->stopped_since_us, memory_order_relaxed);
    if (since == 0u) {
        atomic_store_explicit(&impl->stopped_since_us, now, memory_order_relaxed);
        return false;
    }
    return now - since >= AUDIO_DEVICE_LOSS_GRACE_US;
}

u64 audio_system_recoveries(const AudioSystem *as) {
    struct AudioImpl *impl = audio_impl(as);
    return impl ? atomic_load_explicit(&impl->device_recoveries, memory_order_acquire) : 0u;
}

/* Takes one simulated refusal, if any is pending. */
static bool audio_take_refusal(struct AudioImpl *impl) {
    u32 pending = atomic_load_explicit(&impl->refused_reopens, memory_order_acquire);
    while (pending > 0u) {
        if (atomic_compare_exchange_weak_explicit(&impl->refused_reopens, &pending,
                                                  pending - 1u, memory_order_acq_rel,
                                                  memory_order_acquire)) {
            return true;
        }
    }
    return false;
}

static void audio_mark_recovered(struct AudioImpl *impl) {
    atomic_store_explicit(&impl->simulated_lost, false, memory_order_release);
    atomic_store_explicit(&impl->stopped_since_us, 0u, memory_order_relaxed);
    atomic_fetch_add_explicit(&impl->device_recoveries, 1u, memory_order_acq_rel);
}

/* Replaces the engine's device in place: same memory, same format, the
 * default output. The node graph, and with it every source, is untouched.
 * On WASAPI the COM notification thread may still reroute or restart the
 * old device between the started check and ma_device_uninit; the 250 ms
 * grace period makes that window rare, it is not closed. */
static AudioResult audio_reopen_device(struct AudioImpl *impl) {
    ma_engine *engine = &impl->engine;
    ma_device *device = ma_engine_get_device(engine);
    if (!device) return AUDIO_FAILED;
    ma_device_uninit(device);
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = ma_engine_get_channels(engine);
    config.sampleRate = ma_engine_get_sample_rate(engine);
    config.dataCallback = audio_device_data_callback;
    config.pUserData = engine;
    config.noPreSilencedOutputBuffer = MA_TRUE;
    config.noClip = MA_TRUE;
    ma_result result = ma_device_init(&impl->context, &config, device);
    if (result != MA_SUCCESS) {
        /* closed and zeroed (uninitialized state): the names report "none"
         * and the system stays lost until a reopen works */
        memset(device, 0, sizeof(*device));
        LOG_WARN("Audio: playback device reopen failed (%d)", result);
        return AUDIO_FAILED;
    }
    if (ma_device_start(device) != MA_SUCCESS) {
        LOG_WARN("Audio: reopened playback device did not start");
        return AUDIO_FAILED;
    }
    audio_mark_recovered(impl);
    return AUDIO_OK;
}

AudioResult audio_system_reopen(AudioSystem *as) {
    struct AudioImpl *impl = audio_impl(as);
    if (!impl) return AUDIO_INVALID;
    if (audio_take_refusal(impl)) return AUDIO_FAILED;
    const bool simulated = atomic_load_explicit(&impl->simulated_lost, memory_order_acquire);
    if (as->backend == AUDIO_BACKEND_FAKE) {
        if (simulated) audio_mark_recovered(impl);
        return AUDIO_OK;
    }
    /* A device the backend restarted by itself is left alone. */
    if (!simulated && audio_device_started(impl)) {
        atomic_store_explicit(&impl->stopped_since_us, 0u, memory_order_relaxed);
        return AUDIO_OK;
    }
    return audio_reopen_device(impl);
}

AudioResult audio_system_simulate_event(AudioSystem *as, AudioSystemEvent event) {
    struct AudioImpl *impl = audio_impl(as);
    if (!impl || (event != AUDIO_SYSTEM_EVENT_DEVICE_LOST &&
                  event != AUDIO_SYSTEM_EVENT_REOPEN_REFUSED)) {
        return AUDIO_INVALID;
    }
    if (as->backend == AUDIO_BACKEND_DEFAULT) return AUDIO_REJECTED;
    if (event == AUDIO_SYSTEM_EVENT_REOPEN_REFUSED) {
        atomic_fetch_add_explicit(&impl->refused_reopens, 1u, memory_order_acq_rel);
    } else {
        atomic_store_explicit(&impl->simulated_lost, true, memory_order_release);
    }
    return AUDIO_OK;
}

AudioSystem *audio_system_create(void) {
    return audio_system_create_ex(AUDIO_BACKEND_DEFAULT);
}

AudioResult audio_system_render(AudioSystem *as, f32 *stereo_out, u32 frames) {
    if (!as || !as->engine || !stereo_out || frames == 0) return AUDIO_INVALID;
    if (as->backend != AUDIO_BACKEND_FAKE) return AUDIO_REJECTED;
    struct AudioImpl *impl = as->engine;
    ma_result result = ma_engine_read_pcm_frames(&impl->engine, stereo_out,
                                                 frames, NULL);
    if (result != MA_SUCCESS) return AUDIO_FAILED;
    return AUDIO_OK;
}

void audio_system_destroy(AudioSystem *as) {
    if (!as) return;
    /* Recompute impl pointer from the same single-allocation layout */
    usize as_sz  = sizeof(AudioSystem);
    usize align  = _Alignof(long double);
    usize as_off = (as_sz + align - 1) & ~(align - 1);
    struct AudioImpl *impl = (struct AudioImpl *)((u8 *)as + as_off);

    audio_extended_destroy(as, as->extended);
    for (u32 i = 0; i < as->source_count; i++) {
        if (as->sources[i].active) {
            ma_sound_uninit(&as->sources[i].sound);
        }
    }
    ma_engine_uninit(&impl->engine);
    if (impl->context_initialized) ma_context_uninit(&impl->context);
    free(as->sources);
    free(as); /* single free: AudioSystem + AudioImpl */
}

void audio_system_update(AudioSystem *as, Vec3 listener_pos, Vec3 forward, Vec3 up) {
    if (!as || !as->engine) return;
    for (u32 i = 0; i < 3; ++i) {
        if (!isfinite(listener_pos.e[i]) || !isfinite(forward.e[i]) ||
            !isfinite(up.e[i])) return;
    }

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
    audio_extended_listener_update(as);
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
        MA_SOUND_FLAG_NO_SPATIALIZATION | MA_SOUND_FLAG_DECODE,
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

u32 audio_play_3d_source(AudioSystem *as, const char *path, Vec3 position, f32 volume,
                         bool looping) {
    if (!as || !as->engine || !path) return 0;

    u32 id = audio_acquire_slot(as);
    if (id == UINT32_MAX) return 0;

    struct AudioImpl *impl = as->engine;
    AudioSource *src = &as->sources[id];

    /* Spatial variant of audio_play(); miniaudio spatializes unless explicitly
     * disabled. Spatialization state and the world position are set BEFORE
     * ma_sound_start, mirroring audio_play_streamed's spatial init — routing
     * through audio_play() started the sound 2D at the origin and only then
     * re-spatialized it, so the first mixing quantum could play unspatialized. */
    ma_result result = ma_sound_init_from_file(&impl->engine, path,
        MA_SOUND_FLAG_DECODE,
        NULL, NULL, &src->sound);
    if (result != MA_SUCCESS) {
        LOG_WARN("Failed to load sound: %s (%d)", path, result);
        /* Return slot to free-list */
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
    /* R270: same inverse-distance model as the streaming 3D path. */
    ma_sound_set_spatialization_enabled(&src->sound, MA_TRUE);
    ma_sound_set_attenuation_model(&src->sound, ma_attenuation_model_inverse);
    ma_sound_set_position(&src->sound, position.e[0], position.e[1], position.e[2]);
    ma_sound_start(&src->sound);
    src->active = true;
    return audio_make_handle(src, id);
}

void audio_play_3d(AudioSystem *as, const char *path, Vec3 position, f32 volume, bool looping) {
    (void)audio_play_3d_source(as, path, position, volume, looping);
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

    ma_uint32 flags = MA_SOUND_FLAG_DECODE;
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
    if (!audio_bus_valid(as, bus) || !isfinite(gain)) return;
    if (gain < 0.0f) gain = 0.0f;          /* R435: clamp non-negative */
    as->buses[bus].gain = gain;
    audio_extended_set_bus_gain(as, bus, gain);
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
#if defined(AUDIO_SIMULATOR_NULL_BACKEND)
    sys->devices_enumerated = true;
    sys->device_count = 0u;
    return 0u;
#endif

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
