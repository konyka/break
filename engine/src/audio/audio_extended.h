#pragma once

#include <audio/audio.h>
#include <audio/audio_dsp.h>

#define AUDIO_MAX_CLIPS 48u
#define AUDIO_PCM_MAX_SAMPLES 1048576u
#define AUDIO_PCM_SAMPLE_RATE 48000u
#define AUDIO_NAME_MAX 48u

typedef u32 AudioClipHandle;

typedef struct {
    const f32 *samples;
    u32 frame_count;
    u32 channels;
    u32 sample_rate;
} AudioPcmDesc;

#define AUDIO_MAX_EVENTS 32u
#define AUDIO_EVENT_MAX_VOICES 30u

typedef u32 AudioVoiceHandle;

typedef enum {
    AUDIO_RETRIGGER_ALLOW = 0,
    AUDIO_RETRIGGER_RESTART,
    AUDIO_RETRIGGER_IGNORE
} AudioRetriggerPolicy;

typedef enum {
    AUDIO_CONCURRENCY_REJECT = 0,
    AUDIO_CONCURRENCY_STEAL_OLDEST
} AudioConcurrencyPolicy;

typedef struct {
    AudioClipHandle clip;
    u32 max_instances;
    AudioRetriggerPolicy retrigger;
    AudioConcurrencyPolicy concurrency;
    f32 volume;
    bool looping;
    bool spatial;
    f32 min_distance;
    f32 max_distance;
    f32 rolloff;
    f32 occluded_gain;
    u32 bus;
    AudioDspChainDesc dsp;
    /* Constant-power stereo pan from the listener's orientation, like
     * audio_pcm_stream_set_panning. Requires `spatial`. */
    bool panned;
    /* Rear low-pass cue from the listener's orientation, like
     * audio_pcm_stream_set_rear_cue: none in front or to the side, down to
     * AUDIO_PCM_STREAM_REAR_CUTOFF_HZ straight behind. Each voice keeps its
     * own filter state, reset when it starts. Requires `spatial`. */
    bool rear_cue;
    /* Interaural time difference from the listener's orientation, like
     * audio_pcm_stream_set_interaural_delay: the far ear hears the voice up
     * to AUDIO_PCM_STREAM_ITD_MAX_FRAMES later. Each voice keeps its own
     * delay line, zeroed when it starts. Requires `spatial`. */
    bool interaural_delay;
} AudioEventDesc;

AudioResult audio_event_register(AudioSystem *as, const char *name,
                                 const AudioEventDesc *desc);
AudioResult audio_event_trigger(AudioSystem *as, const char *name, Vec3 pos,
                                AudioVoiceHandle *out_voice);
AudioResult audio_voice_stop(AudioSystem *as, AudioVoiceHandle voice);
AudioResult audio_voice_cursor(AudioSystem *as, AudioVoiceHandle voice,
                               u32 *out_frame);
typedef bool (*AudioOcclusionRayFn)(void *user, Vec3 listener, Vec3 source);
void audio_set_occlusion_ray_callback(AudioSystem *as,
    AudioOcclusionRayFn fn, void *user);
AudioResult audio_voice_set_position(AudioSystem *as,
    AudioVoiceHandle voice, Vec3 position);
f32 audio_voice_spatial_gain(AudioSystem *as, AudioVoiceHandle voice);
AudioResult audio_event_active_count(AudioSystem *as, const char *name,
                                     u32 *out_count);

#define AUDIO_MUSIC_MAX_TRACKS 16u

typedef enum {
    AUDIO_MUSIC_STOPPED = 0,
    AUDIO_MUSIC_PLAYING,
    AUDIO_MUSIC_CROSSFADING,
    AUDIO_MUSIC_STOPPING
} AudioMusicState;

typedef struct {
    const AudioClipHandle *tracks;
    u32 track_count;
    bool loop;
    u32 crossfade_frames;
    f32 volume;
    u32 bus;
} AudioMusicPlaylistDesc;

AudioResult audio_music_set_playlist(AudioSystem *as,
    const AudioMusicPlaylistDesc *desc);
AudioResult audio_music_play(AudioSystem *as);
AudioResult audio_music_stop(AudioSystem *as);
AudioResult audio_music_update(AudioSystem *as);
AudioResult audio_music_state(AudioSystem *as, AudioMusicState *out_state,
                              u32 *out_track_index);

/* ---- Live PCM streams ----
 * A stream plays PCM that arrives while it plays (network voice, generated
 * audio). The producer writes 16-bit PCM from one thread; the mixer reads
 * it from a bounded single-producer / single-consumer ring of
 * AUDIO_PCM_STREAM_FRAMES frames (about 341 ms) at the engine rate
 * (48 kHz) and plays silence when the ring runs dry (an underrun). The
 * capacity is a power of two so the free-running ring counters stay
 * correct when they wrap. Gain is volume x bus x
 * master, like event voices. A closed stream's handle is stale; the slot
 * is reused with a new generation. */
#define AUDIO_PCM_STREAM_MAX 4u
#define AUDIO_PCM_STREAM_FRAMES 16384u

typedef u32 AudioPcmStreamHandle;

#define AUDIO_PCM_STREAM_MIN_RATE 8000u
#define AUDIO_PCM_STREAM_MAX_RATE 192000u

/* channels 1 or 2; an invalid bus falls back to master; volume < 0 is 0.
 * OVERLOAD when all AUDIO_PCM_STREAM_MAX streams are open. The stream plays
 * at the engine rate (AUDIO_PCM_SAMPLE_RATE). */
AudioResult audio_pcm_stream_open(AudioSystem *as, u32 channels, u32 bus, f32 volume,
                                  AudioPcmStreamHandle *out_handle);
/* Same, for PCM written at sample_rate (AUDIO_PCM_STREAM_MIN_RATE ..
 * AUDIO_PCM_STREAM_MAX_RATE). The mixer converts it to the engine rate by
 * linear interpolation (audio_pcm_stream_set_resample selects sinc). A stream faster than the engine rate first goes
 * through a 4th-order Butterworth low-pass at 21.6 kHz, so content above
 * 24 kHz is attenuated instead of folding back (about -19 dB at 30 kHz for
 * 96 kHz input; less right above 24 kHz). Upsampling is not filtered. Ring
 * frames and queued counts are in stream-rate frames. */
AudioResult audio_pcm_stream_open_rate(AudioSystem *as, u32 channels, u32 sample_rate, u32 bus,
                                       f32 volume, AudioPcmStreamHandle *out_handle);
/* Copies up to frame_count interleaved frames (i16 / 32768) and reports how
 * many fit; never blocks. Producer thread only. */
AudioResult audio_pcm_stream_write_i16(AudioSystem *as, AudioPcmStreamHandle handle,
                                       const i16 *samples, u32 frame_count,
                                       u32 *out_written);
AudioResult audio_pcm_stream_queued(AudioSystem *as, AudioPcmStreamHandle handle,
                                    u32 *out_frames);
/* Frames of silence played because the ring was empty while open. */
AudioResult audio_pcm_stream_underruns(AudioSystem *as, AudioPcmStreamHandle handle,
                                       u64 *out_frames);
AudioResult audio_pcm_stream_close(AudioSystem *as, AudioPcmStreamHandle handle);
/* Turns on distance attenuation for a stream, with the same model, checks
 * and occlusion ray as a spatial event: min_distance > 0, max_distance >=
 * min_distance, rolloff >= 0, occluded_gain in 0..1 (else INVALID, nothing
 * changes). The stream keeps its position (the origin until set). The
 * listener (audio_system_update) and the position both update the gain. */
AudioResult audio_pcm_stream_set_spatial(AudioSystem *as, AudioPcmStreamHandle handle,
                                         f32 min_distance, f32 max_distance, f32 rolloff,
                                         f32 occluded_gain);
/* REJECTED for a stream without set_spatial (checked first); INVALID for
 * a non-finite position, which leaves the position and gain unchanged. */
AudioResult audio_pcm_stream_set_position(AudioSystem *as, AudioPcmStreamHandle handle,
                                          Vec3 position);
/* Constant-power stereo panning of a spatial stream from the listener's
 * orientation (right = forward x up): a source on the right plays louder on
 * the right channel, centre is -3 dB on both. Off at open. REJECTED for a
 * stream without set_spatial. Front and back sound the same (no HRTF). */
AudioResult audio_pcm_stream_set_panning(AudioSystem *as, AudioPcmStreamHandle handle,
                                         bool enabled);

/* Low-pass cutoff of the rear cue for a source straight behind. */
#define AUDIO_PCM_STREAM_REAR_CUTOFF_HZ 5000.0f

/* Front/back cue for a spatial stream (no HRTF): a one-pole low-pass that
 * grows as the source moves behind the listener (forward vector), from
 * none at the side plane to AUDIO_PCM_STREAM_REAR_CUTOFF_HZ straight
 * behind. A source in front or to the side plays exactly as without the
 * cue. Off at open. REJECTED for a stream without set_spatial. */
AudioResult audio_pcm_stream_set_rear_cue(AudioSystem *as, AudioPcmStreamHandle handle,
                                          bool enabled);

/* Head model of the interaural delay (Woodworth). */
#define AUDIO_PCM_STREAM_HEAD_RADIUS 0.0875f
#define AUDIO_PCM_STREAM_SPEED_OF_SOUND 343.0f
/* The delay of a source straight to the side, in 48 kHz frames. */
#define AUDIO_PCM_STREAM_ITD_MAX_FRAMES 31u
/* Frames of past output kept per stream for the delay (a power of two). */
#define AUDIO_PCM_STREAM_ITD_LINE_FRAMES 64u

/* Interaural time difference for a spatial stream (no HRTF): the ear away
 * from the source hears it later, by r / c * (asin(p) + p) seconds with p the
 * lateral amount used by panning, rounded to whole frames (0 in front,
 * behind, above or on the listener; AUDIO_PCM_STREAM_ITD_MAX_FRAMES straight
 * to the side). A change of delay jumps without a crossfade. Off at open.
 * REJECTED for a stream without set_spatial. */
AudioResult audio_pcm_stream_set_interaural_delay(AudioSystem *as, AudioPcmStreamHandle handle,
                                                  bool enabled);

typedef enum {
    AUDIO_RESAMPLE_LINEAR = 0,
    AUDIO_RESAMPLE_SINC
} AudioResampleMode;

/* Source frames a sinc stream needs queued past its position before it
 * plays (latency: 0.5 ms at 16 kHz). */
#define AUDIO_PCM_STREAM_SINC_LOOKAHEAD 8u

/* Rate conversion of a stream opened with audio_pcm_stream_open_rate.
 * LINEAR (the default at open) interpolates between two frames. SINC uses a
 * 16-tap Lanczos kernel (a = 8) with normalised weights: flat to near the
 * source Nyquist rate and few images, at the cost of
 * AUDIO_PCM_STREAM_SINC_LOOKAHEAD frames of latency; until those are queued
 * the stream underruns. Past frames come from a history the mixer keeps in
 * both modes, so a switch mid-stream is seamless. A stream faster than the
 * engine still gets the Butterworth low-pass first; a stream at the engine
 * rate is not changed. INVALID for an unknown mode. */
AudioResult audio_pcm_stream_set_resample(AudioSystem *as, AudioPcmStreamHandle handle,
                                          AudioResampleMode mode);

AudioResult audio_clip_register(AudioSystem *as, const char *name,
                                const AudioPcmDesc *pcm,
                                AudioClipHandle *out_handle);
u32 audio_clip_count(const AudioSystem *as);
usize audio_clip_used_samples(const AudioSystem *as);
AudioResult audio_system_render(AudioSystem *as, f32 *stereo_out, u32 frames);
