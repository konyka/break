#include <audio/audio_wav.h>

#include <stdio.h>
#include <string.h>

static void put16(u8 *out, u16 value) {
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void put32(u8 *out, u32 value) {
    for (u32 i = 0; i < 4u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static usize valid_seed(u8 *out) {
    memcpy(out, "RIFF", 4u);
    put32(out + 4u, 44u);
    memcpy(out + 8u, "WAVEfmt ", 8u);
    put32(out + 16u, 16u);
    put16(out + 20u, 1u);
    put16(out + 22u, 2u);
    put32(out + 24u, 16000u);
    put32(out + 28u, 64000u);
    put16(out + 32u, 4u);
    put16(out + 34u, 16u);
    memcpy(out + 36u, "data", 4u);
    put32(out + 40u, 8u);
    put16(out + 44u, 1000u);
    put16(out + 46u, 2000u);
    put16(out + 48u, 3000u);
    put16(out + 50u, 4000u);
    return 52u;
}

int main(int argc, char **argv) {
    u32 iterations = 20000u;
    if (argc > 2) return 2;
    if (argc == 2) {
        const int parsed = sscanf(argv[1], "%u", &iterations);
        if (parsed != 1 || iterations == 0u) return 2;
    }
    u32 rng = 0x57415645u;
    u8 data[256], seed[52];
    const usize seed_size = valid_seed(seed);
    i16 out[128];
    u32 accepted = 0u, rejected = 0u;
    for (u32 i = 0; i < iterations; ++i) {
        usize size = 0u;
        if (i % 4u == 0u) {
            rng = rng * 1664525u + 1013904223u;
            size = rng % 257u;
            for (usize n = 0; n < size; ++n) {
                rng = rng * 1664525u + 1013904223u;
                data[n] = (u8)(rng >> 24u);
            }
        } else {
            memcpy(data, seed, seed_size);
            size = seed_size;
            const u32 changes = i % 16u == 1u ? 0u : 1u + i % 8u;
            for (u32 change = 0; change < changes; ++change) {
                rng = rng * 1664525u + 1013904223u;
                data[rng % size] ^= (u8)(rng >> 16u);
            }
            if (i % 5u == 0u) size = rng % (seed_size + 1u);
        }
        AudioWavInfo info;
        const AudioResult result = audio_wav_decode_i16(data, size, &info, out, 64u);
        if (result == AUDIO_OK) ++accepted;
        else ++rejected;
    }
    if (accepted == 0u || rejected == 0u) return 1;
    return 0;
}
