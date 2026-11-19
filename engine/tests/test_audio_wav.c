/* PCM WAV parsing: known little-endian samples, chunk padding, zero frames,
 * malformed layouts and output/capacity failure atomicity; canonical
 * encoding and round trips through the decoder. */
#include "test_framework.h"

#include <audio/audio_wav.h>

#include <string.h>

static void put16(u8 *out, u16 value) {
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void put32(u8 *out, u32 value) {
    for (u32 i = 0; i < 4u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static void write_chunk(u8 *out, usize *pos, const char id[4], const u8 *payload, u32 size) {
    memcpy(out + *pos, id, 4u);
    put32(out + *pos + 4u, size);
    if (size != 0u) memcpy(out + *pos + 8u, payload, size);
    *pos += 8u + size;
    if (size & 1u) out[(*pos)++] = 0u;
}

static usize make_wav(u8 *out, const i16 *samples, u32 frames, u32 channels) {
    memcpy(out, "RIFF", 4u);
    memcpy(out + 8u, "WAVE", 4u);
    usize pos = 12u;
    u8 fmt[16] = {0};
    put16(fmt, 1u);
    put16(fmt + 2u, (u16)channels);
    put32(fmt + 4u, 16000u);
    const u32 align = channels * 2u;
    put32(fmt + 8u, 16000u * align);
    put16(fmt + 12u, (u16)align);
    put16(fmt + 14u, 16u);
    write_chunk(out, &pos, "fmt ", fmt, 16u);
    u8 payload[64] = {0};
    for (u32 i = 0; i < frames * channels; ++i) put16(payload + i * 2u, (u16)samples[i]);
    write_chunk(out, &pos, "data", payload, frames * channels * 2u);
    put32(out + 4u, (u32)(pos - 8u));
    return pos;
}

static void expect_invalid(const void *data, usize size, u32 capacity) {
    AudioWavInfo info = {99u, 98u, 97u};
    i16 out[8];
    memset(out, 0x55, sizeof(out));
    ASSERT_EQ(audio_wav_decode_i16(data, size, &info, out, capacity), AUDIO_INVALID);
    ASSERT_EQ(info.sample_rate, 99u);
    ASSERT_EQ(info.channels, 98u);
    ASSERT_EQ(info.frames, 97u);
    ASSERT_EQ(out[0], 0x5555);
}

TEST(mono_and_stereo_decode_known_samples)
{
    u8 data[128];
    const i16 mono[] = {1234, -2345};
    usize size = make_wav(data, mono, 2u, 1u);
    AudioWavInfo info = {0};
    i16 out[8];
    ASSERT_EQ(audio_wav_decode_i16(data, size, &info, out, 8u), AUDIO_OK);
    ASSERT_EQ(info.sample_rate, 16000u);
    ASSERT_EQ(info.channels, 1u);
    ASSERT_EQ(info.frames, 2u);
    ASSERT_EQ(memcmp(out, mono, sizeof(mono)), 0);

    const i16 stereo[] = {-32768, 32767, -1000, 1000};
    size = make_wav(data, stereo, 2u, 2u);
    ASSERT_EQ(audio_wav_decode_i16(data, size, &info, out, 8u), AUDIO_OK);
    ASSERT_EQ(info.channels, 2u);
    ASSERT_EQ(info.frames, 2u);
    ASSERT_EQ(memcmp(out, stereo, sizeof(stereo)), 0);
}

TEST(extended_fmt_unknown_chunks_and_zero_frames)
{
    u8 data[128] = {0};
    memcpy(data, "RIFF", 4u);
    memcpy(data + 8u, "WAVE", 4u);
    usize pos = 12u;
    u8 fmt[18] = {0};
    put16(fmt, 1u); put16(fmt + 2u, 1u); put32(fmt + 4u, 16000u);
    put32(fmt + 8u, 32000u); put16(fmt + 12u, 2u); put16(fmt + 14u, 16u);
    write_chunk(data, &pos, "fmt ", fmt, 18u);
    const u8 odd[] = {1u, 2u, 3u};
    write_chunk(data, &pos, "JUNK", odd, 3u);
    const u8 even[] = {4u, 5u};
    write_chunk(data, &pos, "NOTE", even, 2u);
    const u8 sample[] = {0x34, 0x12};
    write_chunk(data, &pos, "data", sample, 2u);
    put32(data + 4u, (u32)(pos - 8u));
    AudioWavInfo info;
    i16 out[2];
    ASSERT_EQ(audio_wav_decode_i16(data, pos, &info, out, 2u), AUDIO_OK);
    ASSERT_EQ(out[0], 4660);

    size_t zero_size = make_wav(data, NULL, 0u, 1u);
    ASSERT_EQ(audio_wav_decode_i16(data, zero_size, &info, NULL, 0u), AUDIO_OK);
    ASSERT_EQ(info.frames, 0u);
}

TEST(malformed_layouts_and_truncation_are_rejected)
{
    u8 data[128], copy[128];
    const i16 samples[] = {1234, -2345};
    const usize size = make_wav(data, samples, 2u, 1u);
    expect_invalid(NULL, size, 8u);
    expect_invalid(data, size, 0u);
    for (usize n = 0; n < size; ++n) expect_invalid(data, n, 8u);
    memcpy(copy, data, size); memcpy(copy, "RIFX", 4u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); memcpy(copy + 8u, "WVAE", 4u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put32(copy + 4u, 0u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put32(copy + 4u, UINT32_MAX); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put32(copy + 16u, 15u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put16(copy + 20u, 2u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put16(copy + 22u, 0u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put32(copy + 24u, 0u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put16(copy + 34u, 8u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put16(copy + 32u, 4u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put32(copy + 28u, 1u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put32(copy + 36u, 3u); expect_invalid(copy, size, 8u);
    memcpy(copy, data, size); put32(copy + 16u, UINT32_MAX); expect_invalid(copy, size, 8u);

    memcpy(copy, data, size);
    memcpy(copy + size, "x", 1u);
    expect_invalid(copy, size + 1u, 8u);

    memcpy(copy + size, "JUNK", 4u);
    put32(copy + size + 4u, 3u);
    copy[size + 8u] = 1u;
    copy[size + 9u] = 2u;
    copy[size + 10u] = 3u;
    put32(copy + 4u, (u32)(size + 11u - 8u));
    expect_invalid(copy, size + 11u, 8u);

    memcpy(copy + size, "JUNK", 4u);
    put32(copy + size + 4u, UINT32_MAX - 1u);
    put32(copy + 4u, (u32)(size + 8u - 8u));
    expect_invalid(copy, size + 8u, 8u);

    usize pos = 12u;
    memset(copy, 0, sizeof(copy));
    memcpy(copy, "RIFF", 4u); memcpy(copy + 8u, "WAVE", 4u);
    u8 fmt[16] = {0};
    put16(fmt, 1u); put16(fmt + 2u, 1u); put32(fmt + 4u, 16000u);
    put32(fmt + 8u, 32000u); put16(fmt + 12u, 2u); put16(fmt + 14u, 16u);
    write_chunk(copy, &pos, "fmt ", fmt, 16u);
    write_chunk(copy, &pos, "fmt ", fmt, 16u);
    write_chunk(copy, &pos, "data", NULL, 0u);
    put32(copy + 4u, (u32)(pos - 8u));
    expect_invalid(copy, pos, 8u);

    pos = 12u;
    memset(copy, 0, sizeof(copy));
    memcpy(copy, "RIFF", 4u); memcpy(copy + 8u, "WAVE", 4u);
    write_chunk(copy, &pos, "data", NULL, 0u);
    write_chunk(copy, &pos, "fmt ", fmt, 16u);
    put32(copy + 4u, (u32)(pos - 8u));
    expect_invalid(copy, pos, 8u);
}

TEST(output_and_capacity_failures_are_atomic)
{
    u8 data[128];
    const i16 samples[] = {1234, -2345};
    const usize size = make_wav(data, samples, 2u, 1u);
    AudioWavInfo info = {99u, 98u, 97u};
    i16 out[2] = {111, 222};
    ASSERT_EQ(audio_wav_decode_i16(data, size, NULL, out, 2u), AUDIO_INVALID);
    ASSERT_EQ(out[0], 111);
    expect_invalid(data, size, 1u);
    ASSERT_EQ(audio_wav_decode_i16(data, size, &info, NULL, 2u), AUDIO_INVALID);
    ASSERT_EQ(info.frames, 97u);
    ASSERT_EQ(audio_wav_decode_i16(data, size, &info, out, 2u), AUDIO_OK);
    ASSERT_EQ(out[0], 1234);
    ASSERT_EQ(out[1], -2345);
}

static const u8 kMonoHeader[AUDIO_WAV_HEADER_SIZE] = {
    'R', 'I', 'F', 'F', 40u, 0u, 0u, 0u, 'W', 'A', 'V', 'E',
    'f', 'm', 't', ' ', 16u, 0u, 0u, 0u, 1u, 0u, 1u, 0u,
    0x80u, 0x3eu, 0u, 0u, 0x00u, 0x7du, 0u, 0u, 2u, 0u, 16u, 0u,
    'd', 'a', 't', 'a', 4u, 0u, 0u, 0u};

TEST(encode_writes_the_canonical_header_and_samples)
{
    const i16 mono[] = {1234, -2345};
    const AudioWavInfo info = {16000u, 1u, 2u};
    usize size = 0u;
    ASSERT_EQ(audio_wav_encoded_size(1u, 2u, &size), AUDIO_OK);
    ASSERT_EQ(size, 48u);
    u8 out[64];
    memset(out, 0xaa, sizeof(out));
    usize written = 0u;
    ASSERT_EQ(audio_wav_encode_i16(&info, mono, out, sizeof(out), &written), AUDIO_OK);
    ASSERT_EQ(written, 48u);
    ASSERT_EQ(memcmp(out, kMonoHeader, sizeof(kMonoHeader)), 0);
    ASSERT_EQ(out[44], 0xd2u);
    ASSERT_EQ(out[45], 0x04u);
    ASSERT_EQ(out[46], 0xd7u);
    ASSERT_EQ(out[47], 0xf6u);
    ASSERT_EQ(out[48], 0xaau);

    /* stereo at 48 kHz: block align 4, byte rate 192000 */
    const i16 stereo[] = {1, -1, 32767, -32768};
    const AudioWavInfo stereo_info = {48000u, 2u, 2u};
    ASSERT_EQ(audio_wav_encode_i16(&stereo_info, stereo, out, sizeof(out), &written), AUDIO_OK);
    ASSERT_EQ(written, 52u);
    ASSERT_EQ(out[4], 44u);
    ASSERT_EQ(out[22], 2u);
    ASSERT_EQ(out[24] | (out[25] << 8) | (out[26] << 16), 48000);
    ASSERT_EQ(out[28] | (out[29] << 8) | (out[30] << 16), 192000);
    ASSERT_EQ(out[32], 4u);
    ASSERT_EQ(out[40], 8u);
}

TEST(encoded_files_decode_back_exactly)
{
    i16 samples[64];
    for (u32 i = 0u; i < 64u; ++i) samples[i] = (i16)((i32)i * 1031 - 32768);
    const u32 channels_list[] = {1u, 2u};
    const u32 rates[] = {8000u, 44100u, 192000u};
    for (u32 c = 0u; c < 2u; ++c) {
        for (u32 r = 0u; r < 3u; ++r) {
            for (u32 frames = 0u; frames <= 32u; frames += 16u) {
                const AudioWavInfo info = {rates[r], channels_list[c], frames};
                u8 encoded[256];
                usize size = 0u;
                ASSERT_EQ(audio_wav_encode_i16(&info, frames ? samples : NULL, encoded,
                                               sizeof(encoded), &size), AUDIO_OK);
                AudioWavInfo decoded = {0u, 0u, 0u};
                i16 back[64];
                ASSERT_EQ(audio_wav_decode_i16(encoded, size, &decoded, back, 32u), AUDIO_OK);
                ASSERT_EQ(decoded.sample_rate, info.sample_rate);
                ASSERT_EQ(decoded.channels, info.channels);
                ASSERT_EQ(decoded.frames, frames);
                ASSERT_EQ(memcmp(back, samples, frames * info.channels * sizeof(i16)), 0);
            }
        }
    }
}

TEST(encode_failures_write_nothing)
{
    const i16 mono[] = {1234, -2345};
    u8 out[64];
    memset(out, 0x55, sizeof(out));
    usize written = 77u;
    AudioWavInfo info = {16000u, 1u, 2u};
    ASSERT_EQ(audio_wav_encode_i16(NULL, mono, out, sizeof(out), &written), AUDIO_INVALID);
    ASSERT_EQ(audio_wav_encode_i16(&info, NULL, out, sizeof(out), &written), AUDIO_INVALID);
    ASSERT_EQ(audio_wav_encode_i16(&info, mono, NULL, sizeof(out), &written), AUDIO_INVALID);
    ASSERT_EQ(audio_wav_encode_i16(&info, mono, out, sizeof(out), NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_wav_encode_i16(&info, mono, out, 47u, &written), AUDIO_INVALID);
    info.sample_rate = 7999u;
    ASSERT_EQ(audio_wav_encode_i16(&info, mono, out, sizeof(out), &written), AUDIO_INVALID);
    info.sample_rate = 192001u;
    ASSERT_EQ(audio_wav_encode_i16(&info, mono, out, sizeof(out), &written), AUDIO_INVALID);
    info.sample_rate = 16000u;
    info.channels = 3u;
    ASSERT_EQ(audio_wav_encode_i16(&info, mono, out, sizeof(out), &written), AUDIO_INVALID);
    info.channels = 0u;
    ASSERT_EQ(audio_wav_encode_i16(&info, mono, out, sizeof(out), &written), AUDIO_INVALID);
    ASSERT_EQ(written, 77u);
    for (u32 i = 0u; i < sizeof(out); ++i) ASSERT_EQ(out[i], 0x55u);

    usize size = 5u;
    ASSERT_EQ(audio_wav_encoded_size(3u, 1u, &size), AUDIO_INVALID);
    ASSERT_EQ(audio_wav_encoded_size(1u, 1u, NULL), AUDIO_INVALID);
    /* 2 channels * 2 bytes * 0x40000000 frames does not fit the RIFF size */
    ASSERT_EQ(audio_wav_encoded_size(2u, 0x40000000u, &size), AUDIO_INVALID);
    ASSERT_EQ(size, 5u);
    ASSERT_EQ(audio_wav_encoded_size(2u, 0x3ffffff0u, &size), AUDIO_OK);
    ASSERT_EQ(size, (usize)AUDIO_WAV_HEADER_SIZE + (usize)0x3ffffff0u * 4u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(mono_and_stereo_decode_known_samples);
    RUN_TEST(extended_fmt_unknown_chunks_and_zero_frames);
    RUN_TEST(malformed_layouts_and_truncation_are_rejected);
    RUN_TEST(output_and_capacity_failures_are_atomic);
    RUN_TEST(encode_writes_the_canonical_header_and_samples);
    RUN_TEST(encoded_files_decode_back_exactly);
    RUN_TEST(encode_failures_write_nothing);
TEST_MAIN_END()
