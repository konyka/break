#include "audio_wav.h"

#include <stdint.h>
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

static void wav_write_u16(u8 *out, u32 value) {
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void wav_write_u32(u8 *out, u32 value) {
    for (u32 i = 0; i < 4u; ++i) out[i] = (u8)(value >> (i * 8u));
}

AudioResult audio_wav_encoded_size(u32 channels, u32 frames, usize *out_size) {
    if (!out_size || (channels != 1u && channels != 2u)) return AUDIO_INVALID;
    const u64 size = (u64)AUDIO_WAV_HEADER_SIZE + (u64)frames * channels * 2u;
    /* the RIFF size field holds size - 8 */
    if (size - 8u > UINT32_MAX || size > (u64)SIZE_MAX) return AUDIO_INVALID;
    *out_size = (usize)size;
    return AUDIO_OK;
}

AudioResult audio_wav_encode_i16(const AudioWavInfo *info, const i16 *samples, void *out,
                                 usize capacity, usize *out_size) {
    if (!info || !out || !out_size || info->sample_rate < 8000u ||
        info->sample_rate > 192000u || (info->frames != 0u && !samples)) {
        return AUDIO_INVALID;
    }
    usize size = 0u;
    if (audio_wav_encoded_size(info->channels, info->frames, &size) != AUDIO_OK ||
        capacity < size) {
        return AUDIO_INVALID;
    }
    u8 *bytes = (u8 *)out;
    const u32 align = info->channels * 2u;
    const u32 data_size = (u32)(size - AUDIO_WAV_HEADER_SIZE);
    memcpy(bytes, "RIFF", 4u);
    wav_write_u32(bytes + 4u, (u32)(size - 8u));
    memcpy(bytes + 8u, "WAVEfmt ", 8u);
    wav_write_u32(bytes + 16u, 16u);
    wav_write_u16(bytes + 20u, 1u);
    wav_write_u16(bytes + 22u, info->channels);
    wav_write_u32(bytes + 24u, info->sample_rate);
    wav_write_u32(bytes + 28u, info->sample_rate * align);
    wav_write_u16(bytes + 32u, align);
    wav_write_u16(bytes + 34u, 16u);
    memcpy(bytes + 36u, "data", 4u);
    wav_write_u32(bytes + 40u, data_size);
    const u32 count = info->frames * info->channels;
    for (u32 i = 0; i < count; ++i) {
        wav_write_u16(bytes + AUDIO_WAV_HEADER_SIZE + i * 2u, (u16)samples[i]);
    }
    *out_size = size;
    return AUDIO_OK;
}
