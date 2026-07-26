/* Mutation fuzzer for the texture decode pipeline (stb_image + mip chain).
 *
 * Calls decode_pipeline_decode_sync so every iteration exercises the same
 * decode_generate_mipchain path as the worker pool, without thread timing
 * noise. The loader may reject anything; it must not crash, read or write
 * out of bounds, or leak.
 */

#include <asset/decode_pipeline.h>
#include <asset/async_loader.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Linked because decode_pipeline.c references it from decode_worker_run. */
AssetState async_loader_status(u64 request_id) {
    (void)request_id;
    return ASSET_LOADING;
}

static unsigned long rng_state = 0xDEC0DE42u;
static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* Minimal 2x2 32-bit uncompressed TGA (same layout as test_async_loader.c). */
static const unsigned char TGA_SEED[34] = {
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00,
    0x20, 0x28,
    0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

static const unsigned char PNG_SEED[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
    0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x72, 0xB6, 0x6D,
    0x34,
};

static const unsigned interesting_u32[] = {
    0u, 1u, 2u, 18u, 34u,
    0x7FFFFFFFu, 0x80000000u,
    0xFFFFFFFEu, 0xFFFFFFFFu,
};

static void mutate(unsigned char *buf, u32 *len, u32 cap, unsigned nmut) {
    u32 n = *len;
    for (unsigned m = 0; m < nmut; m++) {
        if (n >= 8 && rnd() % 3 == 0) {
            unsigned v = interesting_u32[rnd() % (sizeof(interesting_u32) / sizeof(interesting_u32[0]))];
            u32 pos = (u32)(rnd() % (n < 64 ? n / 4u : 16u)) * 4u;
            if (pos + 4u <= n)
                memcpy(buf + pos, &v, 4u);
            continue;
        }
        switch (rnd() % 5) {
        case 0:
            if (n < cap) buf[n++] = (unsigned char)(rnd() & 0xFF);
            break;
        case 1:
            if (n > 0) n = (u32)(rnd() % (n + 1u));
            break;
        case 2: {
            u32 pos = n > 0 ? (u32)(rnd() % n) : 0u;
            buf[pos] ^= (unsigned char)(1u << (rnd() % 8));
            break;
        }
        case 3:
            if (n > 0) {
                u32 pos = (u32)(rnd() % n);
                buf[pos] = 0xFF;
            }
            break;
        default:
            if (n > 0) {
                u32 pos = (u32)(rnd() % n);
                buf[pos] = 0x00;
            }
            break;
        }
    }
    *len = n;
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 5000;
    if (argc > 2) rng_state = (unsigned long)atoi(argv[2]);
    log_set_level(LOG_FATAL);

    /* Assert the unmutated TGA seed decodes — otherwise fuzz only hits reject paths. */
    {
        DecodeResult res;
        if (!decode_pipeline_decode_sync(TGA_SEED, (u32)sizeof(TGA_SEED), &res) || !res.success) {
            fprintf(stderr, "TGA seed failed to decode\n");
            return 2;
        }
        free(res.data);
    }

    enum { CAP = 65536u };
    unsigned char *scratch = (unsigned char *)malloc(CAP);
    if (!scratch) return 2;

    for (unsigned it = 0; it < iters; it++) {
        u32 base_len = (it & 1u) ? (u32)sizeof(TGA_SEED) : (u32)sizeof(PNG_SEED);
        const unsigned char *base = (it & 1u) ? TGA_SEED : PNG_SEED;
        memcpy(scratch, base, base_len);
        u32 len = base_len;
        mutate(scratch, &len, CAP, 1u + rnd() % 8u);

        DecodeResult res;
        (void)decode_pipeline_decode_sync(scratch, len, &res);
        if (res.data) free(res.data);
    }

    free(scratch);
    printf("fuzz done: %u iters\n", iters);
    return 0;
}
