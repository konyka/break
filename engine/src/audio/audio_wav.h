#pragma once
/* Allocation-free PCM16 RIFF/WAVE validation, little-endian decoding and
 * canonical encoding. */

#include <audio/audio.h>

typedef struct {
    u32 sample_rate;
    u32 channels;
    u32 frames;
} AudioWavInfo;

/* Supports PCM16 mono/stereo. The complete input is validated before any output
 * write. NULL samples are valid only for a zero-frame file. */
AudioResult audio_wav_decode_i16(const void *data, usize size, AudioWavInfo *info,
                                 i16 *samples, u32 frame_capacity);

#define AUDIO_WAV_HEADER_SIZE 44u

/* Bytes of the canonical file for `frames` frames of 1 or 2 channels; INVALID
 * for NULL, another channel count or a file above 4 GiB. */
AudioResult audio_wav_encoded_size(u32 channels, u32 frames, usize *out_size);
/* Writes a canonical 44-byte header (RIFF, 16-byte PCM fmt chunk, data
 * chunk) and the little-endian samples. info must be something
 * audio_wav_decode_i16 accepts (rate 8000..192000, 1 or 2 channels); NULL
 * samples are valid only for zero frames. INVALID, with nothing written, for
 * a bad argument or a capacity below the encoded size. */
AudioResult audio_wav_encode_i16(const AudioWavInfo *info, const i16 *samples, void *out,
                                 usize capacity, usize *out_size);
