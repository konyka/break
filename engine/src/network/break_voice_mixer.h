#pragma once
/* Mixes the voice of several peers into one playback frame
 * (docs/superpowers/specs/2026-11-19-break-voice-mixer-design.md). One
 * BreakVoiceReceiver (jitter buffer, concealment) per source session; every
 * source shares one stream format. Owner thread (the creating thread) only;
 * only create allocates the source table, and a source's receiver is created
 * on its first frame. */

#include <network/break_online_voice.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_VOICE_MIXER_MAX_SOURCES 16u

typedef struct BreakVoiceMixer BreakVoiceMixer;

typedef struct BreakVoiceMixerConfig {
    BreakVoiceStreamConfig stream; /* used for every source receiver */
    u32 max_sources;               /* 1..BREAK_VOICE_MIXER_MAX_SOURCES */
    /* 0: a source is never evicted. Keep it above stream.jitter_delay_ms,
     * or an evicted source can still hold frames that have not played. */
    u32 idle_timeout_ms;
} BreakVoiceMixerConfig;

typedef struct BreakVoiceMixerStats {
    u32 sources; /* live now */
    u64 sources_created;
    u64 sources_evicted;
    u64 sources_refused;
    u64 mixed_frames;
    u64 clipped_samples;
    /* summed over every receiver, evicted ones included: never decrease */
    u64 accepted;
    u64 played;
    u64 concealed;
    u64 invalid;
} BreakVoiceMixerStats;

/* INVALID for NULL arguments, max_sources out of range or a stream config
 * BreakVoiceReceiver refuses; OOM when memory runs out. *out is written only
 * on success. */
BreakRuntimeError break_voice_mixer_create(const BreakVoiceMixerConfig *config,
                                           BreakVoiceMixer **out);
/* NULL or a call off the owner thread is a no-op. */
void break_voice_mixer_destroy(BreakVoiceMixer *mixer);
/* Hands one BRV1/BRV2 frame from `source` (a nonzero session id) to that
 * source's receiver and decodes it. A new source takes a free entry, else
 * the source idle longest (at least idle_timeout_ms since its last push,
 * timeout nonzero) is evicted; otherwise OVERLOAD and sources_refused counts.
 * A malformed frame returns OK and is counted by the receiver (invalid); it
 * still takes an entry for a new source. INVALID for a NULL mixer or bytes,
 * source 0, size 0 or a size above BREAK_VOICE_MAX_DATAGRAM_SIZE (no entry
 * is taken); REJECTED off the owner thread. */
BreakRuntimeError break_voice_mixer_push(BreakVoiceMixer *mixer, u64 source,
                                         const void *bytes, u32 size, u64 now_ms);
/* Pops at most one due playback from every source and sums them in source
 * insertion order, saturating each sample to i16 (clipped_samples counts the
 * saturated ones). *out_ready is false when no source had a frame due.
 * out->sequence is the mixer's own frame counter; out->concealed is true only
 * when every contributing frame was concealed. Call it once per frame
 * period: every receiver keeps its own playout clock, so draining it in a
 * loop can return partial mixes when the sources' due times differ. */
BreakRuntimeError break_voice_mixer_pop(BreakVoiceMixer *mixer, u64 now_ms,
                                        BreakVoicePlayback *out, bool *out_ready);
BreakRuntimeError break_voice_mixer_stats(BreakVoiceMixer *mixer, BreakVoiceMixerStats *out);

#ifdef __cplusplus
}
#endif
