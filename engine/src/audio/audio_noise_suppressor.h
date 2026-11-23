#pragma once
/* Spectral noise reduction for captured mono voice: Hann STFT, adaptive
 * per-bin noise floors and bounded, over-subtracted Wiener-style gains
 * (docs/design/audio_extended.md, "Spectral noise suppression"). Owner thread
 * only; only create allocates. Processing has a fixed frame_size delay. */

#include <audio/audio.h>

#define AUDIO_NOISE_SUPPRESSOR_MIN_FRAME_SIZE 16u
#define AUDIO_NOISE_SUPPRESSOR_MAX_FRAME_SIZE 1024u

typedef struct {
    u32 sample_rate;         /* 8000..192000 */
    u32 frame_size;          /* 16..1024, a power of two */
    f32 max_attenuation_db;  /* 0..80; 0 is exact delayed reconstruction */
    f32 noise_rise_db_per_s; /* 0.1..60, upward tracking speed */
    f32 initial_noise_dbfs;  /* -120..0, per-bin initial noise power */
} AudioNoiseSuppressorConfig;

typedef struct AudioNoiseSuppressor AudioNoiseSuppressor;

/* INVALID for NULL or an out-of-range config, OVERLOAD on allocation failure;
 * *out is written only on success. */
AudioResult audio_noise_suppressor_create(const AudioNoiseSuppressorConfig *config,
                                          AudioNoiseSuppressor **out);
void audio_noise_suppressor_destroy(AudioNoiseSuppressor *suppressor); /* NULL is a no-op */
/* Restore the exact post-create state. NULL is a no-op. */
void audio_noise_suppressor_reset(AudioNoiseSuppressor *suppressor);
/* Mono in-place processing. Arbitrary chunks produce the same sequence as one
 * call. Feed frame_size silence frames to drain. NULL samples are accepted only
 * when frames is zero; a NULL suppressor is a no-op. */
void audio_noise_suppressor_process_i16(AudioNoiseSuppressor *suppressor,
                                        i16 *samples, u32 frames);
/* frame_size for a valid object, 0 for NULL. */
u32 audio_noise_suppressor_latency_frames(const AudioNoiseSuppressor *suppressor);

#define AUDIO_NOISE_SUPPRESSOR_BANK_MAX_CHANNELS 8u

/* Interleaved multichannel suppression: one independent mono suppressor per
 * channel, so every channel matches a mono object fed that channel alone.
 * Owner thread only; only create allocates. */
typedef struct AudioNoiseSuppressorBank AudioNoiseSuppressorBank;

/* channels 1..AUDIO_NOISE_SUPPRESSOR_BANK_MAX_CHANNELS; the config is checked
 * as for the mono object. INVALID or OVERLOAD as there; *out is written only
 * on success. */
AudioResult audio_noise_suppressor_bank_create(const AudioNoiseSuppressorConfig *config,
                                               u32 channels, AudioNoiseSuppressorBank **out);
void audio_noise_suppressor_bank_destroy(AudioNoiseSuppressorBank *bank); /* NULL is a no-op */
void audio_noise_suppressor_bank_reset(AudioNoiseSuppressorBank *bank);   /* NULL is a no-op */
/* In-place interleaved PCM; frames counts frames per channel. Arbitrary
 * chunks produce the same output as one call. NULL samples are accepted only
 * when frames is zero; a NULL bank is a no-op. */
void audio_noise_suppressor_bank_process_interleaved_i16(AudioNoiseSuppressorBank *bank,
                                                         i16 *samples, u32 frames);
u32 audio_noise_suppressor_bank_channels(const AudioNoiseSuppressorBank *bank); /* 0 for NULL */
/* frame_size, as for the mono object; 0 for NULL. */
u32 audio_noise_suppressor_bank_latency_frames(const AudioNoiseSuppressorBank *bank);
