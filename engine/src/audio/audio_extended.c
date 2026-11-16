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
    f32 spatial_pan;
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
    atomic_uint_least64_t spatial_epoch;
    atomic_uint_least64_t started_epoch;
    /* (revision, pan) of a panned event, stored before the gain snapshot of
     * that revision; the mixer takes it only with that revision */
    atomic_uint_least64_t pan_snapshot;
    u32 applied_spatial_revision;
    f32 applied_spatial_gain;
    bool panned;
    f32 applied_pan_left;
    f32 applied_pan_right;
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

/* head and tail are free-running u32 counters; masking them only stays in
 * order across their wrap when the capacity divides 2^32. */
_Static_assert((AUDIO_PCM_STREAM_FRAMES & (AUDIO_PCM_STREAM_FRAMES - 1u)) == 0u,
               "AUDIO_PCM_STREAM_FRAMES must be a power of two");

/* One live PCM stream: an SPSC ring of interleaved f32 frames. The producer
 * (audio_pcm_stream_write_i16) owns `head`, the mixer callback owns `tail`.
 * `open` and `gain_bits` are published with release stores and read with
 * acquire loads by the mixer; the ring storage is allocated at open and
 * freed at close, so the mixer only touches it while `open` is set and the
 * closing thread waits for that read to finish before freeing. */
typedef struct {
    ma_data_source_base base;
    ma_data_source_node node;
    bool node_initialized;
    f32 *ring;
    u32 channels;
    u32 bus;
    /* Read position past `tail`, mixer-owned, in units where one source
     * frame is AUDIO_PCM_SAMPLE_RATE units; each output frame adds `rate`.
     * Integer arithmetic, so the position is exact for every rate. */
    u32 rate;
    u64 pos;
    /* Anti-aliasing low-pass for a stream faster than the engine rate: two
     * biquads (b0 b1 b2 a1 a2) with per-channel transposed direct form II
     * state. `filtered` counts the frames after `tail` already filtered in
     * place. Mixer-owned like `pos`; open resets them. */
    bool filter;
    double lowpass[2][5];
    double lowpass_state[2][2][2];
    u32 filtered;
    atomic_uint gain_bits;
    /* distance attenuation (audio_pcm_stream_set_spatial); written and
     * recomputed on the owner thread, the mixer reads spatial_bits only */
    atomic_uint spatial_bits;
    /* stereo panning (audio_pcm_stream_set_panning): left and right gains as
     * one 64-bit pair (spatial_pack layout, left in the high half) so the
     * mixer never sees one side updated without the other */
    atomic_uint_least64_t pan_bits;
    bool panning;
    bool spatial;
    f32 min_distance;
    f32 max_distance;
    f32 rolloff;
    f32 occluded_gain;
    Vec3 position;
    atomic_uint head;
    atomic_uint tail;
    atomic_bool open;
    atomic_bool reading;
    atomic_uint_least64_t underruns;
    u32 generation;
    atomic_uint *bus_gains;
} AudioPcmStream;

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
    AudioPcmStream pcm_streams[AUDIO_PCM_STREAM_MAX];
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

static void voice_apply_initial_spatial(AudioVoice *voice,
                                        const AudioCommand *command) {
    u64 expected = atomic_load_explicit(&voice->spatial_snapshot,
                                        memory_order_acquire);
    u64 epoch = atomic_load_explicit(&voice->spatial_epoch,
                                     memory_order_acquire);
#ifdef AUDIO_SPATIAL_TEST_HOOK
    AUDIO_SPATIAL_TEST_HOOK(voice);
#endif
    if (epoch != command->epoch ||
        spatial_revision_of(expected) != command->spatial_revision) return;
    u64 desired = spatial_pack(command->spatial_revision,
                               command->spatial_gain);
    if (atomic_compare_exchange_strong_explicit(&voice->spatial_snapshot,
            &expected, desired, memory_order_release, memory_order_acquire)) {
        voice->applied_spatial_revision = command->spatial_revision;
        voice->applied_spatial_gain = command->spatial_gain;
    }
}

/* Constant-power law shared by events and streams: pan -1 (left) .. 1
 * (right), theta = (pan + 1) * pi / 4, left cos, right sin. */
static void pan_gains(double pan, f32 *left, f32 *right) {
    const double pi = 3.14159265358979323846;
    double theta = (pan + 1.0) * pi / 4.0;
    *left = (f32)cos(theta);
    *right = (f32)sin(theta);
}

static void voice_set_pan(AudioVoice *voice, f32 pan) {
    if (voice->panned) {
        pan_gains(pan, &voice->applied_pan_left, &voice->applied_pan_right);
    } else {
        voice->applied_pan_left = 1.0f;
        voice->applied_pan_right = 1.0f;
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
            voice->panned = command.desc.panned;
            voice_set_pan(voice, command.spatial_pan);
            voice_apply_initial_spatial(voice, &command);
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
                u64 spatial_epoch = atomic_load_explicit(&voice->spatial_epoch,
                                                         memory_order_acquire);
#ifdef AUDIO_VOICE_READ_TEST_HOOK
                AUDIO_VOICE_READ_TEST_HOOK(voice);
#endif
                u64 snapshot = atomic_load_explicit(&voice->spatial_snapshot,
                                                    memory_order_acquire);
                u64 verified_epoch = atomic_load_explicit(&voice->spatial_epoch,
                                                          memory_order_acquire);
                u32 revision = spatial_revision_of(snapshot);
                if (spatial_epoch == verified_epoch &&
                    spatial_epoch == voice->playing_epoch &&
                    revision > voice->applied_spatial_revision) {
                    voice->applied_spatial_revision = revision;
                    voice->applied_spatial_gain = spatial_gain_of(snapshot);
                    if (voice->panned) {
                        u64 pan = atomic_load_explicit(&voice->pan_snapshot,
                                                       memory_order_acquire);
                        if (spatial_revision_of(pan) == revision) {
                            voice_set_pan(voice, spatial_gain_of(pan));
                        }
                    }
                }
                f32 spatial_gain = voice->applied_spatial_gain;
                f32 gain = voice->volume * voice->fade_gain * bus_gain *
                           master_gain * spatial_gain;
                left = voice->samples[sample] * gain * voice->applied_pan_left;
                right = (voice->channels == 2 ? voice->samples[sample + 1u]
                                              : voice->samples[sample]) *
                        gain * voice->applied_pan_right;
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

/* Runs the low-pass over queued frames, in order, until `count` frames
 * after `tail` are filtered. Every frame goes through once, including the
 * ones decimation skips. */
static void pcm_stream_filter_to(AudioPcmStream *stream, u32 tail, u32 count) {
    while (stream->filtered < count) {
        f32 *frame = stream->ring +
            (usize)((tail + stream->filtered) & (AUDIO_PCM_STREAM_FRAMES - 1u)) *
                stream->channels;
        for (u32 c = 0; c < stream->channels; ++c) {
            double x = frame[c];
            for (u32 k = 0; k < 2u; ++k) {
                const double *f = stream->lowpass[k];
                double *z = stream->lowpass_state[k][c];
                double y = f[0] * x + z[0];
                z[0] = f[1] * x - f[3] * y + z[1];
                z[1] = f[2] * x - f[4] * y;
                x = y;
            }
            frame[c] = (f32)x;
        }
        stream->filtered++;
    }
}

/* Mixer side of a PCM stream: plays queued frames, then silence. */
static ma_result pcm_stream_read(ma_data_source *source, void *output,
                                 ma_uint64 frames, ma_uint64 *frames_read) {
    AudioPcmStream *stream = (AudioPcmStream *)source;
    f32 *out = (f32 *)output;
    u64 missing = 0;
    atomic_store_explicit(&stream->reading, true, memory_order_seq_cst);
    bool open = atomic_load_explicit(&stream->open, memory_order_seq_cst);
    u32 tail = atomic_load_explicit(&stream->tail, memory_order_relaxed);
    u32 head = open ? atomic_load_explicit(&stream->head, memory_order_acquire) : tail;
    f32 gain = 0.0f;
    f32 pan_left = 1.0f;
    f32 pan_right = 1.0f;
    if (open) {
        u64 pan = atomic_load_explicit(&stream->pan_bits, memory_order_relaxed);
        pan_left = gain_from_bits((u32)(pan >> 32));
        pan_right = spatial_gain_of(pan);
        f32 bus_gain = stream->bus == AUDIO_BUS_MASTER ? 1.0f :
            gain_from_bits(atomic_load_explicit(&stream->bus_gains[stream->bus],
                                                memory_order_relaxed));
        f32 master_gain = gain_from_bits(atomic_load_explicit(
            &stream->bus_gains[AUDIO_BUS_MASTER], memory_order_relaxed));
        gain = gain_from_bits(atomic_load_explicit(&stream->gain_bits, memory_order_relaxed)) *
               gain_from_bits(atomic_load_explicit(&stream->spatial_bits, memory_order_relaxed)) *
               bus_gain * master_gain;
    }
    /* An output frame interpolates source frames tail+i and tail+i+1, i the
     * whole part of the position, weighted by the remainder. A remainder of
     * zero needs only frame tail+i. A fast stream low-passes those frames
     * first, and any it releases unread. Frames the position has passed are
     * released. While data is missing the position does not move. The
     * position and filter belong to an open stream: a closed slot is being
     * reset by open on another thread, so they are not read then (nothing
     * plays; with no queued frames the filter is never reached). */
    u64 pos = open ? stream->pos : 0u;
    for (ma_uint64 frame = 0; frame < frames; ++frame) {
        f32 left = 0.0f;
        f32 right = 0.0f;
        u32 index = (u32)(pos / AUDIO_PCM_SAMPLE_RATE);
        u32 rem = (u32)(pos % AUDIO_PCM_SAMPLE_RATE);
        u32 queued = head - tail;
        if (index < queued && (rem == 0u || index + 1u < queued)) {
            if (stream->filter) pcm_stream_filter_to(stream, tail, index + (rem == 0u ? 1u : 2u));
            const f32 *a = stream->ring +
                (usize)((tail + index) & (AUDIO_PCM_STREAM_FRAMES - 1u)) * stream->channels;
            left = a[0];
            right = stream->channels == 2u ? a[1] : left;
            if (rem != 0u) {
                const f32 *b = stream->ring +
                    (usize)((tail + index + 1u) & (AUDIO_PCM_STREAM_FRAMES - 1u)) *
                        stream->channels;
                f32 w = (f32)rem / (f32)AUDIO_PCM_SAMPLE_RATE;
                f32 bl = b[0];
                f32 br = stream->channels == 2u ? b[1] : bl;
                left += (bl - left) * w;
                right += (br - right) * w;
            }
            left *= gain * pan_left;
            right *= gain * pan_right;
            pos += stream->rate;
            /* release whole frames behind the position, but never more
             * than are queued: decimation may step past the last one */
            u32 passed = (u32)(pos / AUDIO_PCM_SAMPLE_RATE);
            if (passed > queued) passed = queued;
            if (stream->filter) {
                pcm_stream_filter_to(stream, tail, passed);
                stream->filtered -= passed;
            }
            tail += passed;
            pos -= (u64)passed * AUDIO_PCM_SAMPLE_RATE;
        } else {
            missing++;
        }
        if (out) {
            out[frame * 2u] = left;
            out[frame * 2u + 1u] = right;
        }
    }
    if (open) {
        stream->pos = pos;
        atomic_store_explicit(&stream->tail, tail, memory_order_release);
        if (missing != 0u) {
            atomic_fetch_add_explicit(&stream->underruns, missing, memory_order_relaxed);
        }
    }
    atomic_store_explicit(&stream->reading, false, memory_order_release);
    if (frames_read) *frames_read = frames;
    return MA_SUCCESS;
}

static ma_result pcm_stream_seek(ma_data_source *source, ma_uint64 frame) {
    (void)source; (void)frame;
    return MA_NOT_IMPLEMENTED;
}

static ma_result pcm_stream_format(ma_data_source *source, ma_format *format,
                                   u32 *channels, u32 *sample_rate,
                                   ma_channel *channel_map, usize channel_cap) {
    (void)source; (void)channel_map; (void)channel_cap;
    *format = ma_format_f32;
    *channels = 2;
    *sample_rate = AUDIO_PCM_SAMPLE_RATE;
    return MA_SUCCESS;
}

static ma_result pcm_stream_cursor(ma_data_source *source, ma_uint64 *cursor) {
    (void)source;
    *cursor = 0;
    return MA_NOT_IMPLEMENTED;
}

static ma_result pcm_stream_length(ma_data_source *source, ma_uint64 *length) {
    (void)source;
    *length = 0;
    return MA_NOT_IMPLEMENTED;
}

static const ma_data_source_vtable AUDIO_PCM_STREAM_VTABLE = {
    pcm_stream_read, pcm_stream_seek, pcm_stream_format, pcm_stream_cursor,
    pcm_stream_length, NULL, MA_DATA_SOURCE_SELF_MANAGED_RANGE_AND_LOOP_POINT
};

static u64 pcm_stream_pan_pack(f32 left, f32 right) {
    return ((u64)gain_to_bits(left) << 32) | gain_to_bits(right);
}

/* Handles are (generation << 3) | (slot + 1); 0 is never a handle. */
static AudioPcmStreamHandle pcm_stream_handle(u32 slot, u32 generation) {
    return (generation << 3) | (slot + 1u);
}

static AudioResult pcm_stream_lookup(AudioSystem *as, AudioPcmStreamHandle handle,
                                     AudioPcmStream **out) {
    AudioExtended *ext = audio_extended(as);
    if (!ext || handle == 0u) return AUDIO_INVALID;
    u32 slot = (handle & 7u) - 1u;
    if (slot >= AUDIO_PCM_STREAM_MAX) return AUDIO_INVALID;
    AudioPcmStream *stream = &ext->pcm_streams[slot];
    if (!atomic_load_explicit(&stream->open, memory_order_acquire) ||
        pcm_stream_handle(slot, stream->generation) != handle) {
        return AUDIO_STALE;
    }
    *out = stream;
    return AUDIO_OK;
}

/* 4th-order Butterworth low-pass at 0.45 x the engine rate for a stream
 * faster than the engine; RBJ biquads, bilinear transform at the stream
 * rate. Slower streams are not filtered. */
static void pcm_stream_reset_filter(AudioPcmStream *stream, u32 sample_rate) {
    static const double kQ[2] = {0.54119610014619698, 1.3065629648763766};
    const double pi = 3.14159265358979323846;
    stream->filter = sample_rate > AUDIO_PCM_SAMPLE_RATE;
    stream->filtered = 0u;
    memset(stream->lowpass_state, 0, sizeof(stream->lowpass_state));
    if (!stream->filter) return;
    double w0 = 2.0 * pi * (0.45 * AUDIO_PCM_SAMPLE_RATE) / (double)sample_rate;
    double c = cos(w0);
    for (u32 k = 0; k < 2u; ++k) {
        double alpha = sin(w0) / (2.0 * kQ[k]);
        double a0 = 1.0 + alpha;
        stream->lowpass[k][0] = (1.0 - c) / 2.0 / a0;
        stream->lowpass[k][1] = (1.0 - c) / a0;
        stream->lowpass[k][2] = (1.0 - c) / 2.0 / a0;
        stream->lowpass[k][3] = -2.0 * c / a0;
        stream->lowpass[k][4] = (1.0 - alpha) / a0;
    }
}

AudioResult audio_pcm_stream_open_rate(AudioSystem *as, u32 channels, u32 sample_rate, u32 bus,
                                       f32 volume, AudioPcmStreamHandle *out_handle) {
    AudioExtended *ext = audio_extended(as);
    if (!ext || !out_handle || (channels != 1u && channels != 2u) ||
        sample_rate < AUDIO_PCM_STREAM_MIN_RATE || sample_rate > AUDIO_PCM_STREAM_MAX_RATE) {
        return AUDIO_INVALID;
    }
    for (u32 slot = 0; slot < AUDIO_PCM_STREAM_MAX; ++slot) {
        AudioPcmStream *stream = &ext->pcm_streams[slot];
        if (atomic_load_explicit(&stream->open, memory_order_acquire)) continue;
        f32 *ring = (f32 *)calloc((usize)AUDIO_PCM_STREAM_FRAMES * channels, sizeof(f32));
        if (!ring) return AUDIO_FAILED;
        stream->ring = ring;
        stream->channels = channels;
        stream->bus = bus < as->bus_count && bus < AUDIO_MAX_BUSES ? bus : AUDIO_BUS_MASTER;
        atomic_store_explicit(&stream->gain_bits,
                              gain_to_bits(isfinite(volume) && volume > 0.0f ? volume : 0.0f),
                              memory_order_relaxed);
        stream->rate = sample_rate;
        stream->pos = 0u;
        pcm_stream_reset_filter(stream, sample_rate);
        stream->spatial = false;
        stream->panning = false;
        atomic_store_explicit(&stream->pan_bits, pcm_stream_pan_pack(1.0f, 1.0f),
                              memory_order_relaxed);
        stream->position = vec3(0, 0, 0);
        atomic_store_explicit(&stream->spatial_bits, gain_to_bits(1.0f), memory_order_relaxed);
        atomic_store_explicit(&stream->head, 0u, memory_order_relaxed);
        atomic_store_explicit(&stream->tail, 0u, memory_order_relaxed);
        atomic_store_explicit(&stream->underruns, 0u, memory_order_relaxed);
        stream->generation = (stream->generation + 1u) & 0x1fffffffu;
        if (stream->generation == 0u) stream->generation = 1u;
        atomic_store_explicit(&stream->open, true, memory_order_seq_cst);
        *out_handle = pcm_stream_handle(slot, stream->generation);
        return AUDIO_OK;
    }
    return AUDIO_OVERLOAD;
}

AudioResult audio_pcm_stream_open(AudioSystem *as, u32 channels, u32 bus, f32 volume,
                                  AudioPcmStreamHandle *out_handle) {
    return audio_pcm_stream_open_rate(as, channels, AUDIO_PCM_SAMPLE_RATE, bus, volume,
                                      out_handle);
}

AudioResult audio_pcm_stream_write_i16(AudioSystem *as, AudioPcmStreamHandle handle,
                                       const i16 *samples, u32 frame_count,
                                       u32 *out_written) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!samples || !out_written) return AUDIO_INVALID;
    u32 head = atomic_load_explicit(&stream->head, memory_order_relaxed);
    u32 tail = atomic_load_explicit(&stream->tail, memory_order_acquire);
    u32 room = AUDIO_PCM_STREAM_FRAMES - (head - tail);
    u32 count = frame_count < room ? frame_count : room;
    for (u32 i = 0; i < count; ++i) {
        f32 *dst = stream->ring +
                   (usize)((head + i) & (AUDIO_PCM_STREAM_FRAMES - 1u)) * stream->channels;
        for (u32 c = 0; c < stream->channels; ++c) {
            dst[c] = (f32)samples[(usize)i * stream->channels + c] / 32768.0f;
        }
    }
    atomic_store_explicit(&stream->head, head + count, memory_order_release);
    *out_written = count;
    return AUDIO_OK;
}

AudioResult audio_pcm_stream_queued(AudioSystem *as, AudioPcmStreamHandle handle,
                                    u32 *out_frames) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!out_frames) return AUDIO_INVALID;
    *out_frames = atomic_load_explicit(&stream->head, memory_order_relaxed) -
                  atomic_load_explicit(&stream->tail, memory_order_acquire);
    return AUDIO_OK;
}

AudioResult audio_pcm_stream_underruns(AudioSystem *as, AudioPcmStreamHandle handle,
                                       u64 *out_frames) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!out_frames) return AUDIO_INVALID;
    *out_frames = atomic_load_explicit(&stream->underruns, memory_order_relaxed);
    return AUDIO_OK;
}

static AudioResult spatial_gain(AudioExtended *ext, f32 min_distance, f32 max_distance,
                                f32 rolloff, f32 occluded_gain, Vec3 position,
                                f32 *out_gain);

/* Pan of `position` against the listener's right vector (forward x up):
 * the cosine of the angle between them, -1 left .. 1 right. A source on the
 * listener or a listener without a right vector is centred (0). */
static double listener_pan(const AudioSystem *as, Vec3 position) {
    double d[3], f[3], u[3];
    for (u32 i = 0; i < 3; ++i) {
        d[i] = (double)position.e[i] - as->listener_pos.e[i];
        f[i] = as->listener_forward.e[i];
        u[i] = as->listener_up.e[i];
    }
    double right[3] = {f[1] * u[2] - f[2] * u[1], f[2] * u[0] - f[0] * u[2],
                       f[0] * u[1] - f[1] * u[0]};
    double dlen = sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    double rlen = sqrt(right[0] * right[0] + right[1] * right[1] + right[2] * right[2]);
    double flen = sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
    double ulen = sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
    double pan = 0.0;
    if (dlen > 0.0 && rlen > 1e-9 * flen * ulen) {
        pan = (d[0] * right[0] + d[1] * right[1] + d[2] * right[2]) / (dlen * rlen);
        if (pan > 1.0) pan = 1.0;
        if (pan < -1.0) pan = -1.0;
    }
    return pan;
}

static u64 pcm_stream_pan(const AudioSystem *as, Vec3 position) {
    f32 left = 1.0f;
    f32 right = 1.0f;
    pan_gains(listener_pan(as, position), &left, &right);
    return pcm_stream_pan_pack(left, right);
}

/* Recomputes and publishes a spatial stream's gain (and pan, when panned)
 * for its position. */
static AudioResult pcm_stream_publish_spatial(AudioExtended *ext, AudioPcmStream *stream) {
    f32 gain = 1.0f;
    AudioResult result = spatial_gain(ext, stream->min_distance, stream->max_distance,
                                      stream->rolloff, stream->occluded_gain,
                                      stream->position, &gain);
    if (result != AUDIO_OK) return result;
    atomic_store_explicit(&stream->spatial_bits, gain_to_bits(gain), memory_order_relaxed);
    if (stream->panning) {
        atomic_store_explicit(&stream->pan_bits, pcm_stream_pan(ext->owner, stream->position),
                              memory_order_relaxed);
    }
    return AUDIO_OK;
}

AudioResult audio_pcm_stream_set_spatial(AudioSystem *as, AudioPcmStreamHandle handle,
                                         f32 min_distance, f32 max_distance, f32 rolloff,
                                         f32 occluded_gain) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!isfinite(min_distance) || min_distance <= 0.0f ||
        !isfinite(max_distance) || max_distance < min_distance ||
        !isfinite(rolloff) || rolloff < 0.0f ||
        !isfinite(occluded_gain) || occluded_gain < 0.0f || occluded_gain > 1.0f) {
        return AUDIO_INVALID;
    }
    stream->min_distance = min_distance;
    stream->max_distance = max_distance;
    stream->rolloff = rolloff;
    stream->occluded_gain = occluded_gain;
    stream->spatial = true;
    return pcm_stream_publish_spatial(audio_extended(as), stream);
}

AudioResult audio_pcm_stream_set_position(AudioSystem *as, AudioPcmStreamHandle handle,
                                          Vec3 position) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!stream->spatial) return AUDIO_REJECTED;
    /* spatial_gain refuses a non-finite position; keep the old one then */
    Vec3 previous = stream->position;
    stream->position = position;
    result = pcm_stream_publish_spatial(audio_extended(as), stream);
    if (result != AUDIO_OK) stream->position = previous;
    return result;
}

AudioResult audio_pcm_stream_set_panning(AudioSystem *as, AudioPcmStreamHandle handle,
                                         bool enabled) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!stream->spatial) return AUDIO_REJECTED;
    stream->panning = enabled;
    if (!enabled) {
        atomic_store_explicit(&stream->pan_bits, pcm_stream_pan_pack(1.0f, 1.0f),
                              memory_order_relaxed);
        return AUDIO_OK;
    }
    return pcm_stream_publish_spatial(audio_extended(as), stream);
}

AudioResult audio_pcm_stream_close(AudioSystem *as, AudioPcmStreamHandle handle) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    atomic_store_explicit(&stream->open, false, memory_order_seq_cst);
    /* a read that saw `open` set may still be using the ring */
    while (atomic_load_explicit(&stream->reading, memory_order_seq_cst)) {
    }
    free(stream->ring);
    stream->ring = NULL;
    return AUDIO_OK;
}

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
        atomic_init(&voice->spatial_epoch, 0);
        atomic_init(&voice->started_epoch, 0);
        atomic_init(&voice->pan_snapshot, spatial_pack(0, 0.0f));
        voice->applied_spatial_gain = 1.0f;
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
    for (u32 i = 0; i < AUDIO_PCM_STREAM_MAX; ++i) {
        AudioPcmStream *stream = &ext->pcm_streams[i];
        stream->bus_gains = ext->bus_gains;
        atomic_init(&stream->gain_bits, gain_to_bits(0.0f));
        atomic_init(&stream->spatial_bits, gain_to_bits(1.0f));
        atomic_init(&stream->pan_bits, pcm_stream_pan_pack(1.0f, 1.0f));
        atomic_init(&stream->head, 0);
        atomic_init(&stream->tail, 0);
        atomic_init(&stream->open, false);
        atomic_init(&stream->reading, false);
        atomic_init(&stream->underruns, 0);
        ma_data_source_config config = ma_data_source_config_init();
        config.vtable = &AUDIO_PCM_STREAM_VTABLE;
        if (ma_data_source_init(&config, &stream->base) != MA_SUCCESS) {
            audio_extended_destroy(as, ext);
            return false;
        }
        ma_data_source_node_config node_config =
            ma_data_source_node_config_init(&stream->base);
        if (ma_data_source_node_init(ma_engine_get_node_graph(engine),
                &node_config, NULL, &stream->node) != MA_SUCCESS) {
            audio_extended_destroy(as, ext);
            return false;
        }
        stream->node_initialized = true;
        if (ma_node_attach_output_bus(&stream->node, 0,
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
    for (u32 i = 0; i < AUDIO_PCM_STREAM_MAX; ++i) {
        AudioPcmStream *stream = &ext->pcm_streams[i];
        if (stream->node_initialized) {
            ma_data_source_node_uninit(&stream->node, NULL);
            stream->node_initialized = false;
        }
        if (stream->base.vtable) ma_data_source_uninit(&stream->base);
        free(stream->ring);
        stream->ring = NULL;
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
        desc->occluded_gain > 1.0f || desc->bus >= as->bus_count ||
        (desc->panned && !desc->spatial)) {
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

/* Inverse-distance attenuation from the listener with the occlusion ray;
 * shared by spatial events and spatial PCM streams. */
static AudioResult spatial_gain(AudioExtended *ext, f32 min_distance, f32 max_distance,
                                f32 rolloff, f32 occluded_gain, Vec3 position,
                                f32 *out_gain) {
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
    double minimum = min_distance;
    double maximum = max_distance;
    double clamped = distance < minimum ? minimum :
                     (distance > maximum ? maximum : distance);
    double denominator = minimum + rolloff * (clamped - minimum);
    double gain = minimum / denominator;
    if (!isfinite(distance) || !isfinite(gain)) return AUDIO_INVALID;
    if (gain < 0.0f) gain = 0.0f;
    if (gain > 1.0f) gain = 1.0f;
    if (ext->ray && ext->ray(ext->ray_user, listener, position)) {
        gain *= occluded_gain;
    }
    if (!isfinite(gain)) return AUDIO_INVALID;
    *out_gain = (f32)gain;
    return isfinite(*out_gain) ? AUDIO_OK : AUDIO_INVALID;
}

static AudioResult event_spatial_gain(AudioExtended *ext,
    const AudioEventDesc *desc, Vec3 position, f32 *out_gain) {
    if (!out_gain) return AUDIO_INVALID;
    if (!desc->spatial) {
        *out_gain = 1.0f;
        return AUDIO_OK;
    }
    return spatial_gain(ext, desc->min_distance, desc->max_distance, desc->rolloff,
                        desc->occluded_gain, position, out_gain);
}

static f32 event_pan(const AudioExtended *ext, const AudioEventDesc *desc, Vec3 position) {
    return desc->panned ? (f32)listener_pan(ext->owner, position) : 0.0f;
}

/* The pan is stored under the revision before the gain snapshot that
 * publishes it, so a mixer that sees the gain revision also sees its pan. */
static AudioResult spatial_publish(AudioVoice *voice, u64 epoch, f32 gain, f32 pan) {
    for (;;) {
        if (epoch == 0 || voice->epoch != epoch ||
            atomic_load_explicit(&voice->spatial_epoch, memory_order_acquire) != epoch) {
            return AUDIO_STALE;
        }
        if (voice->spatial_revision == UINT32_MAX) return AUDIO_OVERLOAD;
        u64 expected = atomic_load_explicit(&voice->spatial_snapshot,
                                            memory_order_acquire);
        if (spatial_revision_of(expected) != voice->spatial_revision) {
            return AUDIO_OVERLOAD;
        }
        u32 revision = voice->spatial_revision + 1u;
        u64 desired = spatial_pack(revision, gain);
        atomic_store_explicit(&voice->pan_snapshot, spatial_pack(revision, pan),
                              memory_order_release);
#ifdef AUDIO_SPATIAL_PUBLISH_TEST_HOOK
        AUDIO_SPATIAL_PUBLISH_TEST_HOOK(voice);
#endif
        if (atomic_compare_exchange_strong_explicit(&voice->spatial_snapshot,
                &expected, desired, memory_order_release, memory_order_acquire)) {
            voice->spatial_revision = revision;
            return AUDIO_OK;
        }
    }
}

static AudioResult spatial_begin_start(AudioVoice *voice, u64 epoch,
                                       u32 revision) {
    u64 expected = atomic_load_explicit(&voice->spatial_snapshot,
                                        memory_order_acquire);
    if (spatial_revision_of(expected) != voice->spatial_revision) {
        return AUDIO_OVERLOAD;
    }
    u64 desired = spatial_pack(revision, spatial_gain_of(expected));
    if (!atomic_compare_exchange_strong_explicit(&voice->spatial_snapshot,
            &expected, desired, memory_order_release, memory_order_acquire)) {
        return AUDIO_OVERLOAD;
    }
    voice->spatial_revision = revision;
    atomic_store_explicit(&voice->spatial_epoch, epoch, memory_order_release);
    return AUDIO_OK;
}

static AudioResult voice_start_pcm(AudioExtended *ext, u32 slot,
    AudioClipHandle clip_handle, const AudioEventDesc *desc, i32 owner,
    bool new_generation, f32 initial_gain, u32 ramp_frames,
    Vec3 position, f32 spatial_gain, AudioVoiceHandle *out) {
    AudioVoice *voice = &ext->voices[slot];
    if (voice->epoch == UINT64_MAX || voice->spatial_revision == UINT32_MAX) {
        return AUDIO_OVERLOAD;
    }
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
    command.spatial_revision = voice->spatial_revision + 1u;
    command.ramp_target = 1.0f;
    command.ramp_frames = ramp_frames;
    command.desc = *desc;
    command.spatial_pan = event_pan(ext, desc, position);
    for (u32 i = 0; i < command.desc.dsp.stage_count; ++i) {
        if (command.desc.dsp.stages[i].type == AUDIO_DSP_FILTER) {
            command.dsp_alpha[i] = audio_dsp_filter_alpha(
                command.desc.dsp.stages[i].cutoff_hz, AUDIO_PCM_SAMPLE_RATE);
        }
    }

    /* No pan_snapshot store here: begin_start moves the gain revision while
     * the old epoch may still adopt it (with its old gain), and that PCM must
     * keep its old pan too. START carries the new pan. */
    AudioResult spatial_result = spatial_begin_start(voice, epoch,
                                                      command.spatial_revision);
    if (spatial_result != AUDIO_OK) return spatial_result;
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
    if (ext->voices[slot].epoch == UINT64_MAX ||
        ext->voices[slot].spatial_revision == UINT32_MAX) return AUDIO_OVERLOAD;
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
    const AudioEventDesc *desc = &ext->events[voice->owner_event].desc;
    AudioResult result = event_spatial_gain(ext, desc, position, &gain);
    if (result != AUDIO_OK) return result;
    result = spatial_publish(voice, voice->epoch, gain, event_pan(ext, desc, position));
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
    for (u32 i = 0; i < AUDIO_PCM_STREAM_MAX; ++i) {
        AudioPcmStream *stream = &ext->pcm_streams[i];
        if (stream->spatial && atomic_load_explicit(&stream->open, memory_order_acquire)) {
            (void)pcm_stream_publish_spatial(ext, stream);
        }
    }
    reap_voices(ext);
    for (u32 i = 2; i < AUDIO_MAX_VOICES; ++i) {
        AudioVoice *voice = &ext->voices[i];
        if (!voice->claimed || voice->owner_event < 0 || voice->stop_pending ||
            voice->spatial_revision == UINT32_MAX) {
            continue;
        }
        f32 gain = 0.0f;
        const AudioEventDesc *desc = &ext->events[voice->owner_event].desc;
        if (event_spatial_gain(ext, desc, voice->position, &gain) == AUDIO_OK) {
            (void)spatial_publish(voice, voice->epoch, gain,
                                  event_pan(ext, desc, voice->position));
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
