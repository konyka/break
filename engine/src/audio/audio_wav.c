#include "audio_wav.h"

#include <string.h>

static u16 wav_read_u16(const u8 *data) {
    return (u16)((u16)data[0] | ((u16)data[1] << 8u));
}

static u32 wav_read_u32(const u8 *data) {
    return (u32)data[0] | ((u32)data[1] << 8u) | ((u32)data[2] << 16u) |
           ((u32)data[3] << 24u);
}

AudioResult audio_wav_decode_i16(const void *data, usize size, AudioWavInfo *info,
                                 i16 *samples, u32 frame_capacity) {
    if (!data || !info || size < 12u) return AUDIO_INVALID;
    const u8 *bytes = (const u8 *)data;
    if (memcmp(bytes, "RIFF", 4u) != 0 || memcmp(bytes + 8u, "WAVE", 4u) != 0) {
        return AUDIO_INVALID;
    }
    if ((u64)wav_read_u32(bytes + 4u) + 8u != (u64)size) return AUDIO_INVALID;

    bool have_fmt = false, have_data = false;
    AudioWavInfo parsed = {0};
    const u8 *pcm = NULL;
    u32 pcm_size = 0u;
    usize pos = 12u;
    while (pos < size) {
        if (size - pos < 8u) return AUDIO_INVALID;
        const u8 *chunk = bytes + pos;
        const u32 chunk_size = wav_read_u32(chunk + 4u);
        const usize payload = pos + 8u;
        if ((usize)chunk_size > size - payload) return AUDIO_INVALID;
        const u8 *payload_data = bytes + payload;
        if (memcmp(chunk, "fmt ", 4u) == 0) {
            if (have_fmt || have_data || chunk_size < 16u) return AUDIO_INVALID;
            const u16 format = wav_read_u16(payload_data);
            const u16 channels = wav_read_u16(payload_data + 2u);
            const u32 rate = wav_read_u32(payload_data + 4u);
            const u32 byte_rate = wav_read_u32(payload_data + 8u);
            const u16 align = wav_read_u16(payload_data + 12u);
            const u16 bits = wav_read_u16(payload_data + 14u);
            if (format != 1u || (channels != 1u && channels != 2u) ||
                rate < 8000u || rate > 192000u || bits != 16u ||
                align != (u16)(channels * 2u) || byte_rate != rate * align) {
                return AUDIO_INVALID;
            }
            parsed.sample_rate = rate;
            parsed.channels = channels;
            have_fmt = true;
        } else if (memcmp(chunk, "data", 4u) == 0) {
            if (have_data || !have_fmt) return AUDIO_INVALID;
            pcm = payload_data;
            pcm_size = chunk_size;
            have_data = true;
        }
        pos = payload + chunk_size;
        if (chunk_size & 1u) {
            if (pos >= size) return AUDIO_INVALID;
            ++pos;
        }
    }
    if (!have_fmt || !have_data) return AUDIO_INVALID;
    const u32 align = parsed.channels * 2u;
    if (pcm_size % align != 0u) return AUDIO_INVALID;
    const u32 frames = pcm_size / align;
    if (frames > frame_capacity || (frames != 0u && !samples)) return AUDIO_INVALID;
    for (u32 i = 0; i < frames * parsed.channels; ++i) {
        const u32 encoded = wav_read_u16(pcm + i * 2u);
        const i32 signed_value = encoded >= 32768u ? (i32)encoded - 65536 : (i32)encoded;
        samples[i] = (i16)signed_value;
    }
    parsed.frames = frames;
    *info = parsed;
    return AUDIO_OK;
}
