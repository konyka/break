#include <network/break_voice_mixer.h>

#include <core/platform_thread.h>

#include <stdlib.h>
#include <string.h>

#define BREAK_VOICE_MIXER_PUMP_FRAMES 64u

typedef struct MixerSource {
    u64 session;
    u64 last_push_ms;
    BreakVoiceReceiver *receiver;
} MixerSource;

struct BreakVoiceMixer {
    PlatformThreadId owner;
    BreakVoiceMixerConfig config;
    /* live sources in insertion order: entries [0, count) */
    MixerSource *sources;
    u32 count;
    u32 next_sequence;
    BreakVoiceMixerStats stats;
    /* receiver counts of the sources already removed */
    BreakVoiceReceiverStats removed;
};

static bool mixer_owner(const BreakVoiceMixer *mixer)
{
    return platform_thread_id_equal(mixer->owner, platform_thread_current_id());
}

BreakRuntimeError break_voice_mixer_create(const BreakVoiceMixerConfig *config,
                                           BreakVoiceMixer **out)
{
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!config || config->max_sources == 0u ||
        config->max_sources > BREAK_VOICE_MIXER_MAX_SOURCES) {
        return BREAK_RUNTIME_INVALID;
    }
    /* the receiver is the authority on which stream formats are valid */
    BreakVoiceReceiver *probe = NULL;
    BreakRuntimeError result = break_voice_receiver_create(NULL, &config->stream, &probe);
    if (result != BREAK_RUNTIME_OK) return result;
    break_voice_receiver_destroy(probe);
    BreakVoiceMixer *mixer = (BreakVoiceMixer *)calloc(1u, sizeof(*mixer));
    if (!mixer) return BREAK_RUNTIME_OOM;
    mixer->sources = (MixerSource *)calloc(config->max_sources, sizeof(*mixer->sources));
    if (!mixer->sources) {
        free(mixer);
        return BREAK_RUNTIME_OOM;
    }
    mixer->owner = platform_thread_current_id();
    mixer->config = *config;
    *out = mixer;
    return BREAK_RUNTIME_OK;
}

void break_voice_mixer_destroy(BreakVoiceMixer *mixer)
{
    if (!mixer || !mixer_owner(mixer)) return;
    for (u32 i = 0u; i < mixer->count; ++i) {
        break_voice_receiver_destroy(mixer->sources[i].receiver);
    }
    free(mixer->sources);
    free(mixer);
}

static void mixer_remove(BreakVoiceMixer *mixer, u32 index)
{
    BreakVoiceReceiverStats receiver;
    if (break_voice_receiver_stats(mixer->sources[index].receiver, &receiver) ==
        BREAK_RUNTIME_OK) {
        mixer->removed.accepted += receiver.accepted;
        mixer->removed.played += receiver.played;
        mixer->removed.concealed += receiver.concealed;
        mixer->removed.invalid += receiver.invalid;
    }
    break_voice_receiver_destroy(mixer->sources[index].receiver);
    memmove(&mixer->sources[index], &mixer->sources[index + 1u],
            (mixer->count - index - 1u) * sizeof(*mixer->sources));
    mixer->count--;
}

/* The source idle longest among those idle for at least the timeout, or -1. */
static i32 mixer_evictable(const BreakVoiceMixer *mixer, u64 now_ms)
{
    const u32 timeout = mixer->config.idle_timeout_ms;
    i32 chosen = -1;
    u64 longest = 0u;
    if (timeout == 0u) return -1;
    for (u32 i = 0u; i < mixer->count; ++i) {
        const u64 last = mixer->sources[i].last_push_ms;
        const u64 idle = now_ms > last ? now_ms - last : 0u;
        if (idle >= timeout && (chosen < 0 || idle > longest)) {
            chosen = (i32)i;
            longest = idle;
        }
    }
    return chosen;
}

static BreakRuntimeError mixer_find_or_add(BreakVoiceMixer *mixer, u64 session, u64 now_ms,
                                           MixerSource **out)
{
    for (u32 i = 0u; i < mixer->count; ++i) {
        if (mixer->sources[i].session == session) {
            *out = &mixer->sources[i];
            return BREAK_RUNTIME_OK;
        }
    }
    if (mixer->count == mixer->config.max_sources) {
        const i32 evict = mixer_evictable(mixer, now_ms);
        if (evict < 0) {
            mixer->stats.sources_refused++;
            return BREAK_RUNTIME_OVERLOAD;
        }
        mixer_remove(mixer, (u32)evict);
        mixer->stats.sources_evicted++;
    }
    BreakVoiceReceiver *receiver = NULL;
    const BreakRuntimeError result =
        break_voice_receiver_create(NULL, &mixer->config.stream, &receiver);
    if (result != BREAK_RUNTIME_OK) return result;
    MixerSource *entry = &mixer->sources[mixer->count++];
    entry->session = session;
    entry->last_push_ms = now_ms;
    entry->receiver = receiver;
    mixer->stats.sources_created++;
    *out = entry;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_voice_mixer_push(BreakVoiceMixer *mixer, u64 source,
                                         const void *bytes, u32 size, u64 now_ms)
{
    if (!mixer || !bytes || size == 0u || size > BREAK_VOICE_MAX_DATAGRAM_SIZE ||
        source == 0u) {
        return BREAK_RUNTIME_INVALID;
    }
    if (!mixer_owner(mixer)) return BREAK_RUNTIME_REJECTED;
    MixerSource *entry = NULL;
    BreakRuntimeError result = mixer_find_or_add(mixer, source, now_ms, &entry);
    if (result != BREAK_RUNTIME_OK) return result;
    entry->last_push_ms = now_ms;
    result = break_voice_receiver_push(entry->receiver, bytes, size);
    if (result != BREAK_RUNTIME_OK) return result;
    return break_voice_receiver_pump(entry->receiver, BREAK_VOICE_MIXER_PUMP_FRAMES, now_ms);
}

BreakRuntimeError break_voice_mixer_pop(BreakVoiceMixer *mixer, u64 now_ms,
                                        BreakVoicePlayback *out, bool *out_ready)
{
    if (!mixer || !out || !out_ready) return BREAK_RUNTIME_INVALID;
    *out_ready = false;
    if (!mixer_owner(mixer)) return BREAK_RUNTIME_REJECTED;
    const u16 sample_count = mixer->config.stream.sample_count;
    i32 sum[BREAK_VOICE_MAX_SAMPLES];
    u32 contributors = 0u;
    bool all_concealed = true;
    memset(sum, 0, sizeof(sum));
    for (u32 i = 0u; i < mixer->count; ++i) {
        BreakVoicePlayback playback;
        bool ready = false;
        const BreakRuntimeError result =
            break_voice_receiver_pop(mixer->sources[i].receiver, now_ms, &playback, &ready);
        if (result != BREAK_RUNTIME_OK) return result;
        if (!ready) continue;
        contributors++;
        if (!playback.concealed) all_concealed = false;
        for (u32 s = 0u; s < sample_count; ++s) sum[s] += playback.samples[s];
    }
    if (contributors == 0u) return BREAK_RUNTIME_OK;
    BreakVoicePlayback mixed;
    memset(&mixed, 0, sizeof(mixed));
    mixed.sequence = mixer->next_sequence++;
    mixed.sample_count = sample_count;
    mixed.concealed = all_concealed;
    for (u32 s = 0u; s < sample_count; ++s) {
        i32 value = sum[s];
        if (value > 32767) {
            value = 32767;
            mixer->stats.clipped_samples++;
        } else if (value < -32768) {
            value = -32768;
            mixer->stats.clipped_samples++;
        }
        mixed.samples[s] = (i16)value;
    }
    mixer->stats.mixed_frames++;
    *out = mixed;
    *out_ready = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_voice_mixer_stats(BreakVoiceMixer *mixer, BreakVoiceMixerStats *out)
{
    if (!mixer || !out) return BREAK_RUNTIME_INVALID;
    if (!mixer_owner(mixer)) return BREAK_RUNTIME_REJECTED;
    BreakVoiceMixerStats stats = mixer->stats;
    stats.sources = mixer->count;
    stats.accepted = mixer->removed.accepted;
    stats.played = mixer->removed.played;
    stats.concealed = mixer->removed.concealed;
    stats.invalid = mixer->removed.invalid;
    for (u32 i = 0u; i < mixer->count; ++i) {
        BreakVoiceReceiverStats receiver;
        const BreakRuntimeError result =
            break_voice_receiver_stats(mixer->sources[i].receiver, &receiver);
        if (result != BREAK_RUNTIME_OK) return result;
        stats.accepted += receiver.accepted;
        stats.played += receiver.played;
        stats.concealed += receiver.concealed;
        stats.invalid += receiver.invalid;
    }
    *out = stats;
    return BREAK_RUNTIME_OK;
}
