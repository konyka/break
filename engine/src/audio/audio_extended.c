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
    f32 spatial_rear;
    i32 spatial_itd;
    f32 spatial_tilt;
    u32 spatial_hrtf;
    u32 spatial_revision;
    f32 ramp_target;
    u32 ramp_frames;
    bool stop_after_ramp;
    AudioEventDesc desc;
} AudioCommand;

/* The interaural delay of one stream or voice, mixer-owned: the past frames
 * after the rear cue, the delay in use (positive delays the left ear), and
 * while `fade` > 0 the delay being faded out. `primed` is false until the
 * first frame, which takes its target delay without a fade. */
typedef struct {
    f32 line[AUDIO_PCM_STREAM_ITD_LINE_FRAMES][2];
    u32 written;
    i32 current;
    i32 previous;
    u32 fade;
    bool primed;
} ItdLine;

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
    /* (revision, rear cue coefficient), published the same way */
    atomic_uint_least64_t rear_snapshot;
    /* (revision, interaural delay in frames as f32), published the same way */
    atomic_uint_least64_t itd_snapshot;
    /* (revision, elevation tilt amount), published the same way */
    atomic_uint_least64_t tilt_snapshot;
    /* (revision, HRTF set index), published the same way */
    atomic_uint_least64_t hrtf_snapshot;
    u32 applied_spatial_revision;
    f32 applied_spatial_gain;
    bool panned;
    f32 applied_pan_left;
    f32 applied_pan_right;
    bool rear_cue;
    f32 applied_rear_alpha;
    f32 rear_state[2];
    bool interaural_delay;
    i32 applied_itd;
    ItdLine itd;
    f32 applied_tilt;
    f32 tilt_state[2];
    /* the event's HRTF set (NULL for none), its renderer and the set index
     * in use; mixer-owned, set up by START */
    const AudioHrtfSet *hrtf_set;
    AudioHrtfRenderer hrtf;
    u32 applied_hrtf_index;
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
    /* AudioResampleMode, set by the owner thread, read once per callback */
    atomic_uint resample;
    /* The last released frames (after the low-pass), the sinc kernel's
     * past. `remembered` counts frames pushed, free-running (the power-of-two
     * size keeps the ring in order across its wrap). Mixer-owned; open zeroes
     * the frames, so the count needs no reset. */
    f32 history[AUDIO_PCM_STREAM_SINC_LOOKAHEAD][2];
    u32 remembered;
    /* rear cue (audio_pcm_stream_set_rear_cue): the one-pole coefficient,
     * published by the owner thread, and the per-channel state, mixer-owned
     * like `pos`; open resets both */
    atomic_uint rear_alpha_bits;
    bool rear_cue;
    f32 rear_state[2];
    /* interaural delay (audio_pcm_stream_set_interaural_delay): the signed
     * frame count (positive delays the left ear), published by the owner
     * thread, and the mixer-owned line (ItdLine, like `pos`, written while
     * the delay is off) that crossfades between counts; open zeroes both */
    atomic_int itd_frames;
    bool interaural_delay;
    ItdLine itd;
    /* elevation cue (audio_pcm_stream_set_elevation_cue): the tilt amount,
     * published by the owner thread, and the per-channel low-pass state,
     * mixer-owned like `pos` and run while the cue is off; open resets both */
    atomic_uint elevation_bits;
    bool elevation_cue;
    f32 elevation_state[2];
    /* HRTF (audio_pcm_stream_set_hrtf): the attached set (0 when none,
     * stored seq_cst so the owner can wait out a read that still uses the
     * previous one), the nearest set index of the source direction, and an
     * attach count; all written by the owner thread, which keeps its own
     * copy of the set in hrtf_owner. The renderer and the attach count it
     * was started for are mixer-owned like `pos`; open resets them. */
    atomic_uintptr_t hrtf_set;
    atomic_uint hrtf_index;
    atomic_uint hrtf_attach;
    const AudioHrtfSet *hrtf_owner;
    AudioHrtfRenderer hrtf;
    u32 hrtf_applied_attach;
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

/* One-pole coefficient of the elevation cue's low-pass. */
static f32 elevation_tilt_alpha(void) {
    return (f32)(1.0 - exp(-2.0 * 3.14159265358979323846 *
                           (double)AUDIO_PCM_STREAM_ELEVATION_CUTOFF_HZ /
                           (double)AUDIO_PCM_SAMPLE_RATE));
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

_Static_assert((AUDIO_PCM_STREAM_ITD_LINE_FRAMES & (AUDIO_PCM_STREAM_ITD_LINE_FRAMES - 1u)) == 0u,
               "AUDIO_PCM_STREAM_ITD_LINE_FRAMES must be a power of two");
_Static_assert(AUDIO_PCM_STREAM_ITD_MAX_FRAMES < AUDIO_PCM_STREAM_ITD_LINE_FRAMES,
               "the delay line must hold the longest delay");

/* how many frames back ear `ear` (0 left, 1 right) hears under `delay` */
static u32 itd_ear_back(i32 delay, u32 ear) {
    if (ear == 0u) return delay > 0 ? (u32)delay : 0u;
    return delay < 0 ? (u32)(-delay) : 0u;
}

/* Pushes one frame into the line (shared by streams and voices) and replaces
 * *left and *right with what each ear hears under `target`. The first frame
 * takes `target` directly. A later change starts a crossfade over
 * AUDIO_PCM_STREAM_ITD_FADE_FRAMES frames: step s of it mixes the old ear
 * sample by 1 - s / FADE and the new one by s / FADE, so the last step is
 * the new delay alone. A change during a fade waits for the fade to end. An
 * ear whose delay is the same under both stays exact. */
static void itd_line_process(ItdLine *itd, i32 target, f32 *left, f32 *right) {
    f32 *slot = itd->line[itd->written & (AUDIO_PCM_STREAM_ITD_LINE_FRAMES - 1u)];
    slot[0] = *left;
    slot[1] = *right;
    if (!itd->primed) {
        itd->current = target;
        itd->primed = true;
    } else if (itd->fade == 0u && target != itd->current) {
        itd->previous = itd->current;
        itd->current = target;
        itd->fade = AUDIO_PCM_STREAM_ITD_FADE_FRAMES;
    }
    f32 t = 1.0f;
    if (itd->fade > 0u) {
        t = (f32)(AUDIO_PCM_STREAM_ITD_FADE_FRAMES - itd->fade + 1u) /
            (f32)AUDIO_PCM_STREAM_ITD_FADE_FRAMES;
    }
    f32 heard[2];
    for (u32 ear = 0; ear < 2u; ++ear) {
        u32 back = itd_ear_back(itd->current, ear);
        f32 now = itd->line[(itd->written - back) & (AUDIO_PCM_STREAM_ITD_LINE_FRAMES - 1u)][ear];
        heard[ear] = now;
        if (itd->fade > 0u) {
            u32 old_back = itd_ear_back(itd->previous, ear);
            if (old_back != back) {
                f32 old = itd->line[(itd->written - old_back) &
                                    (AUDIO_PCM_STREAM_ITD_LINE_FRAMES - 1u)][ear];
                heard[ear] = old * (1.0f - t) + now * t;
            }
        }
    }
    if (itd->fade > 0u) itd->fade--;
    itd->written++;
    *left = heard[0];
    *right = heard[1];
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
            voice->rear_cue = command.desc.rear_cue;
            voice->applied_rear_alpha = command.spatial_rear;
            voice->rear_state[0] = 0.0f;
            voice->rear_state[1] = 0.0f;
            voice->interaural_delay = command.desc.interaural_delay;
            voice->applied_itd = command.spatial_itd;
            memset(&voice->itd, 0, sizeof(voice->itd));
            voice->applied_tilt = command.spatial_tilt;
            voice->tilt_state[0] = 0.0f;
            voice->tilt_state[1] = 0.0f;
            voice->hrtf_set = command.desc.hrtf;
            voice->applied_hrtf_index = command.spatial_hrtf;
            if (voice->hrtf_set) {
                (void)audio_hrtf_renderer_init(&voice->hrtf, voice->hrtf_set);
                (void)audio_hrtf_renderer_set_index(&voice->hrtf, command.spatial_hrtf);
            }
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
    const f32 tilt_alpha = elevation_tilt_alpha();
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
                    if (voice->rear_cue) {
                        u64 rear = atomic_load_explicit(&voice->rear_snapshot,
                                                        memory_order_acquire);
                        if (spatial_revision_of(rear) == revision) {
                            voice->applied_rear_alpha = spatial_gain_of(rear);
                        }
                    }
                    if (voice->interaural_delay) {
                        u64 itd = atomic_load_explicit(&voice->itd_snapshot,
                                                       memory_order_acquire);
                        if (spatial_revision_of(itd) == revision) {
                            voice->applied_itd = (i32)spatial_gain_of(itd);
                        }
                    }
                    /* an event without the cue always publishes 0 */
                    u64 tilt = atomic_load_explicit(&voice->tilt_snapshot,
                                                    memory_order_acquire);
                    if (spatial_revision_of(tilt) == revision) {
                        voice->applied_tilt = spatial_gain_of(tilt);
                    }
                    if (voice->hrtf_set) {
                        u64 index = atomic_load_explicit(&voice->hrtf_snapshot,
                                                         memory_order_acquire);
                        if (spatial_revision_of(index) == revision) {
                            voice->applied_hrtf_index = (u32)(index & 0xFFFFFFFFu);
                            (void)audio_hrtf_renderer_set_index(&voice->hrtf,
                                                                voice->applied_hrtf_index);
                        }
                    }
                }
                f32 spatial_gain = voice->applied_spatial_gain;
                f32 gain = voice->volume * voice->fade_gain * bus_gain *
                           master_gain * spatial_gain;
                f32 in_left = voice->samples[sample];
                f32 in_right = voice->channels == 2 ? voice->samples[sample + 1u]
                                                    : in_left;
                f32 mono = 0.5f * (in_left + in_right);
                /* the rear cue filters before the gain; with the cue off
                 * the state follows the signal, so turning it on later
                 * starts from the current level */
                if (voice->applied_rear_alpha < 1.0f) {
                    f32 a = voice->applied_rear_alpha;
                    voice->rear_state[0] += a * (in_left - voice->rear_state[0]);
                    voice->rear_state[1] += a * (in_right - voice->rear_state[1]);
                    in_left = voice->rear_state[0];
                    in_right = voice->rear_state[1];
                } else {
                    voice->rear_state[0] = in_left;
                    voice->rear_state[1] = in_right;
                }
                /* the tilt's low-pass always runs, like a stream's */
                voice->tilt_state[0] += tilt_alpha * (in_left - voice->tilt_state[0]);
                voice->tilt_state[1] += tilt_alpha * (in_right - voice->tilt_state[1]);
                if (voice->applied_tilt != 0.0f) {
                    in_left += voice->applied_tilt * (in_left - voice->tilt_state[0]);
                    in_right += voice->applied_tilt * (in_right - voice->tilt_state[1]);
                }
                itd_line_process(&voice->itd, voice->applied_itd, &in_left, &in_right);
                if (voice->hrtf_set) {
                    /* the other cues' states keep running above */
                    f32 ears[2];
                    audio_hrtf_renderer_process(&voice->hrtf, &mono, ears, 1u);
                    left = ears[0] * gain;
                    right = ears[1] * gain;
                } else {
                    left = in_left * gain * voice->applied_pan_left;
                    right = in_right * gain * voice->applied_pan_right;
                }
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

_Static_assert((AUDIO_PCM_STREAM_SINC_LOOKAHEAD & (AUDIO_PCM_STREAM_SINC_LOOKAHEAD - 1u)) == 0u,
               "AUDIO_PCM_STREAM_SINC_LOOKAHEAD must be a power of two");

/* Frame `offset` after `tail`; a negative offset is a released frame from
 * the history (offset >= -7). */
static const f32 *pcm_stream_frame_at(const AudioPcmStream *stream, u32 tail, i32 offset) {
    if (offset < 0) {
        return stream->history[(stream->remembered + (u32)offset) &
                               (AUDIO_PCM_STREAM_SINC_LOOKAHEAD - 1u)];
    }
    return stream->ring +
        (usize)((tail + (u32)offset) & (AUDIO_PCM_STREAM_FRAMES - 1u)) * stream->channels;
}

static void pcm_stream_remember(AudioPcmStream *stream, u32 frame) {
    const f32 *src = pcm_stream_frame_at(stream, frame, 0);
    f32 *dst = stream->history[stream->remembered & (AUDIO_PCM_STREAM_SINC_LOOKAHEAD - 1u)];
    dst[0] = src[0];
    dst[1] = stream->channels == 2u ? src[1] : src[0];
    stream->remembered++;
}

/* 16-tap Lanczos (a = 8) between frames index and index + 1 at rem /
 * AUDIO_PCM_SAMPLE_RATE, taps index-7 .. index+8, weights normalised so a
 * constant passes unchanged. rem is not zero. */
static void pcm_stream_sinc(const AudioPcmStream *stream, u32 tail, u32 index, u32 rem,
                            f32 *left, f32 *right) {
    const double pi = 3.14159265358979323846;
    double f = (double)rem / (double)AUDIO_PCM_SAMPLE_RATE;
    double acc[2] = {0.0, 0.0};
    double weights = 0.0;
    for (i32 j = -7; j <= 8; ++j) {
        double x = (double)j - f;
        double w = sin(pi * x) / (pi * x) * (sin(pi * x / 8.0) / (pi * x / 8.0));
        const f32 *frame = pcm_stream_frame_at(stream, tail, (i32)index + j);
        acc[0] += frame[0] * w;
        acc[1] += frame[stream->channels == 2u ? 1u : 0u] * w;
        weights += w;
    }
    *left = (f32)(acc[0] / weights);
    *right = (f32)(acc[1] / weights);
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
    f32 rear_alpha = 1.0f;
    f32 tilt = 0.0f;
    i32 itd = 0;
    const AudioHrtfSet *hrtf = NULL;
    if (open) {
        /* seq_cst after `reading`: set_hrtf either sees this read or this
         * read sees its new set */
        hrtf = (const AudioHrtfSet *)atomic_load_explicit(&stream->hrtf_set,
                                                          memory_order_seq_cst);
        if (hrtf) {
            u32 attach = atomic_load_explicit(&stream->hrtf_attach, memory_order_relaxed);
            /* every set_hrtf counts an attach, so a new set is a new count */
            if (attach != stream->hrtf_applied_attach) {
                (void)audio_hrtf_renderer_init(&stream->hrtf, hrtf);
                stream->hrtf_applied_attach = attach;
            }
            (void)audio_hrtf_renderer_set_index(
                &stream->hrtf, atomic_load_explicit(&stream->hrtf_index, memory_order_relaxed));
        }
        itd = atomic_load_explicit(&stream->itd_frames, memory_order_relaxed);
        tilt = gain_from_bits(atomic_load_explicit(&stream->elevation_bits,
                                                   memory_order_relaxed));
        rear_alpha = gain_from_bits(atomic_load_explicit(&stream->rear_alpha_bits,
                                                         memory_order_relaxed));
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
    /* sinc needs AUDIO_PCM_STREAM_SINC_LOOKAHEAD frames past the position,
     * even on a whole frame, so the latency stays the same */
    bool sinc = open && stream->rate != AUDIO_PCM_SAMPLE_RATE &&
                atomic_load_explicit(&stream->resample, memory_order_relaxed) ==
                    (unsigned)AUDIO_RESAMPLE_SINC;
    const f32 tilt_alpha = elevation_tilt_alpha();
    for (ma_uint64 frame = 0; frame < frames; ++frame) {
        f32 left = 0.0f;
        f32 right = 0.0f;
        u32 index = (u32)(pos / AUDIO_PCM_SAMPLE_RATE);
        u32 rem = (u32)(pos % AUDIO_PCM_SAMPLE_RATE);
        u32 queued = head - tail;
        u32 need = sinc ? index + AUDIO_PCM_STREAM_SINC_LOOKAHEAD + 1u
                        : index + (rem == 0u ? 1u : 2u);
        if (need <= queued) {
            if (stream->filter) pcm_stream_filter_to(stream, tail, need);
            const f32 *a = stream->ring +
                (usize)((tail + index) & (AUDIO_PCM_STREAM_FRAMES - 1u)) * stream->channels;
            left = a[0];
            right = stream->channels == 2u ? a[1] : left;
            if (rem != 0u && sinc) {
                pcm_stream_sinc(stream, tail, index, rem, &left, &right);
            } else if (rem != 0u) {
                const f32 *b = stream->ring +
                    (usize)((tail + index + 1u) & (AUDIO_PCM_STREAM_FRAMES - 1u)) *
                        stream->channels;
                f32 w = (f32)rem / (f32)AUDIO_PCM_SAMPLE_RATE;
                f32 bl = b[0];
                f32 br = stream->channels == 2u ? b[1] : bl;
                left += (bl - left) * w;
                right += (br - right) * w;
            }
            f32 mono = 0.5f * (left + right);
            /* the rear cue's state follows the signal while it is off, so
             * it starts from the current frame when it engages */
            if (rear_alpha < 1.0f) {
                stream->rear_state[0] += rear_alpha * (left - stream->rear_state[0]);
                stream->rear_state[1] += rear_alpha * (right - stream->rear_state[1]);
                left = stream->rear_state[0];
                right = stream->rear_state[1];
            } else {
                stream->rear_state[0] = left;
                stream->rear_state[1] = right;
            }
            /* the tilt's low-pass runs while the cue is off or level, so it
             * starts from the current signal when it engages */
            stream->elevation_state[0] += tilt_alpha * (left - stream->elevation_state[0]);
            stream->elevation_state[1] += tilt_alpha * (right - stream->elevation_state[1]);
            if (tilt != 0.0f) {
                left += tilt * (left - stream->elevation_state[0]);
                right += tilt * (right - stream->elevation_state[1]);
            }
            itd_line_process(&stream->itd, itd, &left, &right);
            if (hrtf) {
                /* the other cues' states keep running above, so a detach
                 * continues from the current signal */
                f32 ears[2];
                audio_hrtf_renderer_process(&stream->hrtf, &mono, ears, 1u);
                left = ears[0] * gain;
                right = ears[1] * gain;
            } else {
                left *= gain * pan_left;
                right *= gain * pan_right;
            }
            pos += stream->rate;
            /* release whole frames behind the position, but never more
             * than are queued: decimation may step past the last one */
            u32 passed = (u32)(pos / AUDIO_PCM_SAMPLE_RATE);
            if (passed > queued) passed = queued;
            if (stream->filter) {
                pcm_stream_filter_to(stream, tail, passed);
                stream->filtered -= passed;
            }
            for (u32 r = 0; r < passed; ++r) pcm_stream_remember(stream, tail + r);
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
        atomic_store_explicit(&stream->resample, (unsigned)AUDIO_RESAMPLE_LINEAR,
                              memory_order_relaxed);
        memset(stream->history, 0, sizeof(stream->history));
        stream->rear_cue = false;
        atomic_store_explicit(&stream->rear_alpha_bits, gain_to_bits(1.0f), memory_order_relaxed);
        stream->rear_state[0] = 0.0f;
        stream->rear_state[1] = 0.0f;
        stream->elevation_cue = false;
        atomic_store_explicit(&stream->elevation_bits, gain_to_bits(0.0f), memory_order_relaxed);
        stream->elevation_state[0] = 0.0f;
        stream->elevation_state[1] = 0.0f;
        stream->interaural_delay = false;
        atomic_store_explicit(&stream->itd_frames, 0, memory_order_relaxed);
        memset(&stream->itd, 0, sizeof(stream->itd));
        stream->hrtf_owner = NULL;
        atomic_store_explicit(&stream->hrtf_set, (uintptr_t)0u, memory_order_relaxed);
        atomic_store_explicit(&stream->hrtf_index, 0u, memory_order_relaxed);
        memset(&stream->hrtf, 0, sizeof(stream->hrtf));
        stream->hrtf_applied_attach = 0u;
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

/* One-pole coefficient of the rear cue: 1 (no filter) for a source in
 * front, to the side, on the listener or with a zero forward vector; down to
 * the AUDIO_PCM_STREAM_REAR_CUTOFF_HZ coefficient straight behind, by the
 * cosine of the angle past the side plane. */
static f32 rear_cue_alpha(const AudioSystem *as, Vec3 position) {
    const double pi = 3.14159265358979323846;
    double d[3], f[3];
    for (u32 i = 0; i < 3; ++i) {
        d[i] = (double)position.e[i] - as->listener_pos.e[i];
        f[i] = as->listener_forward.e[i];
    }
    double dlen = sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    double flen = sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
    if (!(dlen > 0.0) || !(flen > 0.0)) return 1.0f;
    double behind = -(d[0] * f[0] + d[1] * f[1] + d[2] * f[2]) / (dlen * flen);
    if (behind <= 0.0) return 1.0f;
    if (behind > 1.0) behind = 1.0;
    double rear = 1.0 - exp(-2.0 * pi * (double)AUDIO_PCM_STREAM_REAR_CUTOFF_HZ /
                            (double)AUDIO_PCM_SAMPLE_RATE);
    return (f32)(1.0 - behind * (1.0 - rear));
}

/* Tilt amount of the elevation cue: the cosine of the angle between the
 * source direction and the up vector, scaled by
 * AUDIO_PCM_STREAM_ELEVATION_BOOST above; 0 for a level source, a source on
 * the listener or a zero up vector. */
static f32 elevation_amount(const AudioSystem *as, Vec3 position) {
    double d[3], u[3];
    for (u32 i = 0; i < 3; ++i) {
        d[i] = (double)position.e[i] - as->listener_pos.e[i];
        u[i] = as->listener_up.e[i];
    }
    double dlen = sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    double ulen = sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
    if (!(dlen > 0.0) || !(ulen > 0.0)) return 0.0f;
    double e = (d[0] * u[0] + d[1] * u[1] + d[2] * u[2]) / (dlen * ulen);
    return (f32)(e > 0.0 ? e * (double)AUDIO_PCM_STREAM_ELEVATION_BOOST : e);
}

/* Signed far-ear delay in frames (positive: the left ear, source on the
 * right) from the Woodworth model on the panning's lateral amount. The pan is
 * within -1..1, so the delay is at most AUDIO_PCM_STREAM_ITD_MAX_FRAMES. */
static i32 interaural_delay_frames(const AudioSystem *as, Vec3 position) {
    double pan = listener_pan(as, position);
    double lateral = fabs(pan);
    double seconds = (double)AUDIO_PCM_STREAM_HEAD_RADIUS /
                     (double)AUDIO_PCM_STREAM_SPEED_OF_SOUND * (asin(lateral) + lateral);
    i32 frames = (i32)lrint(seconds * (double)AUDIO_PCM_SAMPLE_RATE);
    return pan < 0.0 ? -frames : frames;
}

/* The set direction nearest to `position` in the listener frame: x along
 * right = forward x up, z along forward, y along right x forward. A source
 * on the listener or a listener without a right vector is straight ahead. */
static u32 hrtf_direction_index(const AudioSystem *as, const AudioHrtfSet *set, Vec3 position) {
    const double pi = 3.14159265358979323846;
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
    f32 azimuth = 0.0f;
    f32 elevation = 0.0f;
    if (dlen > 0.0 && rlen > 1e-9 * flen * ulen) {
        double r[3], fw[3];
        for (u32 i = 0; i < 3; ++i) {
            r[i] = right[i] / rlen;
            fw[i] = f[i] / flen;
        }
        double up[3] = {r[1] * fw[2] - r[2] * fw[1], r[2] * fw[0] - r[0] * fw[2],
                        r[0] * fw[1] - r[1] * fw[0]};
        double x = d[0] * r[0] + d[1] * r[1] + d[2] * r[2];
        double y = d[0] * up[0] + d[1] * up[1] + d[2] * up[2];
        double z = d[0] * fw[0] + d[1] * fw[1] + d[2] * fw[2];
        azimuth = (f32)(atan2(x, z) * 180.0 / pi);
        elevation = (f32)(atan2(y, sqrt(x * x + z * z)) * 180.0 / pi);
        if (azimuth > 180.0f) azimuth = 180.0f;
        if (azimuth < -180.0f) azimuth = -180.0f;
        if (elevation > 90.0f) elevation = 90.0f;
        if (elevation < -90.0f) elevation = -90.0f;
    }
    return audio_hrtf_set_nearest(set, azimuth, elevation);
}

static u64 pcm_stream_pan(const AudioSystem *as, Vec3 position) {
    f32 left = 1.0f;
    f32 right = 1.0f;
    pan_gains(listener_pan(as, position), &left, &right);
    return pcm_stream_pan_pack(left, right);
}

/* Recomputes and publishes a spatial stream's gain (and pan, rear cue and
 * interaural delay, when on) for its position. */
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
    atomic_store_explicit(&stream->rear_alpha_bits,
                          gain_to_bits(stream->rear_cue ?
                                       rear_cue_alpha(ext->owner, stream->position) : 1.0f),
                          memory_order_relaxed);
    atomic_store_explicit(&stream->elevation_bits,
                          gain_to_bits(stream->elevation_cue ?
                                       elevation_amount(ext->owner, stream->position) : 0.0f),
                          memory_order_relaxed);
    atomic_store_explicit(&stream->itd_frames,
                          stream->interaural_delay ?
                              interaural_delay_frames(ext->owner, stream->position) : 0,
                          memory_order_relaxed);
    if (stream->hrtf_owner) {
        atomic_store_explicit(&stream->hrtf_index,
                              hrtf_direction_index(ext->owner, stream->hrtf_owner,
                                                   stream->position),
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

AudioResult audio_pcm_stream_set_rear_cue(AudioSystem *as, AudioPcmStreamHandle handle,
                                          bool enabled) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!stream->spatial) return AUDIO_REJECTED;
    stream->rear_cue = enabled;
    return pcm_stream_publish_spatial(audio_extended(as), stream);
}

AudioResult audio_pcm_stream_set_interaural_delay(AudioSystem *as, AudioPcmStreamHandle handle,
                                                  bool enabled) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!stream->spatial) return AUDIO_REJECTED;
    stream->interaural_delay = enabled;
    return pcm_stream_publish_spatial(audio_extended(as), stream);
}

AudioResult audio_pcm_stream_set_elevation_cue(AudioSystem *as, AudioPcmStreamHandle handle,
                                               bool enabled) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!stream->spatial) return AUDIO_REJECTED;
    stream->elevation_cue = enabled;
    return pcm_stream_publish_spatial(audio_extended(as), stream);
}

AudioResult audio_pcm_stream_set_hrtf(AudioSystem *as, AudioPcmStreamHandle handle,
                                      const AudioHrtfSet *set) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (!stream->spatial) return AUDIO_REJECTED;
    if (set && audio_hrtf_set_sample_rate(set) != AUDIO_PCM_SAMPLE_RATE) return AUDIO_INVALID;
    stream->hrtf_owner = set;
    if (set) {
        atomic_store_explicit(&stream->hrtf_index,
                              hrtf_direction_index(as, set, stream->position),
                              memory_order_relaxed);
    }
    /* the index and attach count are stored before the set that publishes
     * them; a mixer that sees the set sees them too */
    atomic_fetch_add_explicit(&stream->hrtf_attach, 1u, memory_order_relaxed);
    atomic_store_explicit(&stream->hrtf_set, (uintptr_t)set, memory_order_seq_cst);
    /* a read that loaded the previous set may still be using it */
    while (atomic_load_explicit(&stream->reading, memory_order_seq_cst)) {
    }
    return AUDIO_OK;
}

AudioResult audio_pcm_stream_set_resample(AudioSystem *as, AudioPcmStreamHandle handle,
                                          AudioResampleMode mode) {
    AudioPcmStream *stream = NULL;
    AudioResult result = pcm_stream_lookup(as, handle, &stream);
    if (result != AUDIO_OK) return result;
    if (mode != AUDIO_RESAMPLE_LINEAR && mode != AUDIO_RESAMPLE_SINC) return AUDIO_INVALID;
    atomic_store_explicit(&stream->resample, (unsigned)mode, memory_order_relaxed);
    return AUDIO_OK;
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
        atomic_init(&voice->rear_snapshot, spatial_pack(0, 1.0f));
        atomic_init(&voice->itd_snapshot, spatial_pack(0, 0.0f));
        atomic_init(&voice->tilt_snapshot, spatial_pack(0, 0.0f));
        atomic_init(&voice->hrtf_snapshot, (u64)0u);
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
        atomic_init(&stream->resample, (unsigned)AUDIO_RESAMPLE_LINEAR);
        atomic_init(&stream->rear_alpha_bits, gain_to_bits(1.0f));
        atomic_init(&stream->itd_frames, 0);
        atomic_init(&stream->hrtf_set, (uintptr_t)0u);
        atomic_init(&stream->hrtf_index, 0u);
        atomic_init(&stream->hrtf_attach, 0u);
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
        (desc->panned && !desc->spatial) || (desc->rear_cue && !desc->spatial) ||
        (desc->interaural_delay && !desc->spatial) || (desc->elevation_cue && !desc->spatial) ||
        (desc->hrtf && (!desc->spatial ||
                        audio_hrtf_set_sample_rate(desc->hrtf) != AUDIO_PCM_SAMPLE_RATE))) {
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

static f32 event_rear(const AudioExtended *ext, const AudioEventDesc *desc, Vec3 position) {
    return desc->rear_cue ? rear_cue_alpha(ext->owner, position) : 1.0f;
}

static i32 event_itd(const AudioExtended *ext, const AudioEventDesc *desc, Vec3 position) {
    return desc->interaural_delay ? interaural_delay_frames(ext->owner, position) : 0;
}

static f32 event_tilt(const AudioExtended *ext, const AudioEventDesc *desc, Vec3 position) {
    return desc->elevation_cue ? elevation_amount(ext->owner, position) : 0.0f;
}

static u32 event_hrtf(const AudioExtended *ext, const AudioEventDesc *desc, Vec3 position) {
    return desc->hrtf ? hrtf_direction_index(ext->owner, desc->hrtf, position) : 0u;
}

/* The pan, rear coefficient, interaural delay, tilt and HRTF index are
 * stored under the revision before the gain snapshot that publishes it, so a
 * mixer that sees the gain revision also sees them. */
static AudioResult spatial_publish(AudioVoice *voice, u64 epoch, f32 gain, f32 pan,
                                   f32 rear, i32 itd, f32 tilt, u32 hrtf) {
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
        atomic_store_explicit(&voice->rear_snapshot, spatial_pack(revision, rear),
                              memory_order_release);
        atomic_store_explicit(&voice->itd_snapshot, spatial_pack(revision, (f32)itd),
                              memory_order_release);
        atomic_store_explicit(&voice->tilt_snapshot, spatial_pack(revision, tilt),
                              memory_order_release);
        atomic_store_explicit(&voice->hrtf_snapshot, ((u64)revision << 32) | hrtf,
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
    command.spatial_rear = event_rear(ext, desc, position);
    command.spatial_itd = event_itd(ext, desc, position);
    command.spatial_tilt = event_tilt(ext, desc, position);
    command.spatial_hrtf = event_hrtf(ext, desc, position);
    for (u32 i = 0; i < command.desc.dsp.stage_count; ++i) {
        if (command.desc.dsp.stages[i].type == AUDIO_DSP_FILTER) {
            command.dsp_alpha[i] = audio_dsp_filter_alpha(
                command.desc.dsp.stages[i].cutoff_hz, AUDIO_PCM_SAMPLE_RATE);
        }
    }

    /* No pan, rear, itd, tilt or HRTF snapshot store here: begin_start moves
     * the gain revision while the old epoch may still adopt it (with its old
     * gain), and that PCM must keep its old pan, rear coefficient, delay,
     * tilt and direction too. START carries the new ones. */
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
    result = spatial_publish(voice, voice->epoch, gain, event_pan(ext, desc, position),
                             event_rear(ext, desc, position), event_itd(ext, desc, position),
                             event_tilt(ext, desc, position), event_hrtf(ext, desc, position));
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
                                  event_pan(ext, desc, voice->position),
                                  event_rear(ext, desc, voice->position),
                                  event_itd(ext, desc, voice->position),
                                  event_tilt(ext, desc, voice->position),
                                  event_hrtf(ext, desc, voice->position));
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
