#pragma once
/* Allocation-free PCM16 RIFF/WAVE validation and little-endian decoding. */

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
