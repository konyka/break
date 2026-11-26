/* Mutation fuzzer for break_runtime_metrics_decompress, which decodes a
 * compressed metrics document received from another process or read back
 * from disk. Usage:
 *   fuzz_runtime_metrics_decompress [iterations] [seed]
 * With RUNTIME_METRICS_DECOMPRESS_LIBFUZZER=1 the same check is exported to
 * libFuzzer. Invariants, enforced on every input:
 *  - decompress never reads past the input or writes past the output
 *    (ASan/UBSan);
 *  - a rejected input reports INVALID with *out_len = 0;
 *  - an accepted stream is exact: without its last byte, or with one more
 *    byte appended, it is rejected;
 *  - an accepted input yields exactly the length its header claims, and
 *    compressing that output and decompressing it again reproduces it;
 *  - compress followed by decompress returns random raw bytes unchanged. */

#include <runtime/runtime_metrics.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { k_out_cap = 1u << 16 };

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* A real stream from the library itself, so mutations start from valid bytes. */
static size_t build_seed(unsigned char *out, size_t cap) {
    static const char text[] =
        "BRKM1 net.session.bytes_sent counter 1024\n"
        "BRKM1 net.session.bytes_received counter 2048\n"
        "BRKM1 net.session.rtt_ms gauge 17\n"
        "BRKM1 net.session.rtt_ms gauge 17\n"
        "BRKM1 render.frame.cpu_us histogram 10 20 40 80 160\n"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
    usize len = 0u;
    if (break_runtime_metrics_compress(text, sizeof text - 1u, out, cap, &len) !=
        BREAK_RUNTIME_OK)
        return 0u;
    return len;
}

static void put_le(unsigned char *p, size_t at, size_t size, u32 v, size_t width) {
    for (size_t k = 0u; k < width && at + k < size; ++k) p[at + k] = (unsigned char)(v >> (8u * k));
}

static size_t mutate(unsigned char *buf, size_t size, size_t capacity) {
    unsigned ops = rnd() % 5u + 1u;
    for (unsigned i = 0u; i < ops; ++i) {
        unsigned choice = rnd() % 6u;
        if (choice == 0u && size != 0u) {
            buf[rnd() % size] = (unsigned char)rnd(); /* flip a byte */
        } else if (choice == 1u && size < capacity) {
            size_t at = rnd() % (size + 1u);
            memmove(buf + at + 1u, buf + at, size - at);
            buf[at] = (unsigned char)rnd(); /* insert */
            ++size;
        } else if (choice == 2u && size != 0u) {
            size_t at = rnd() % size;
            memmove(buf + at, buf + at + 1u, size - at - 1u);
            --size; /* delete */
        } else if (choice == 3u && size >= 9u) {
            /* Overwrite the header length with an extreme. */
            static const u32 extremes[] = {0u, 1u, 2u, 255u, 65535u, 65536u, 16u * 1024u * 1024u,
                                           16u * 1024u * 1024u + 1u, 0xFFFFFFFFu};
            put_le(buf, 5u, size, extremes[rnd() % (sizeof extremes / sizeof extremes[0])], 4u);
        } else if (choice == 4u && size > 10u) {
            /* Overwrite a two-byte field past the header with an extreme
             * distance; it lands on a match distance often enough. */
            static const u32 distances[] = {0u, 1u, 2u, 3u, 4u, 0x7FFFu, 0xFFFFu};
            size_t at = 9u + rnd() % (size - 10u);
            put_le(buf, at, size, distances[rnd() % (sizeof distances / sizeof distances[0])], 2u);
        } else if (size > 0u) {
            size = rnd() % size; /* truncate */
        }
    }
    return size;
}

static u32 header_length(const unsigned char *p) {
    return (u32)p[5] | ((u32)p[6] << 8) | ((u32)p[7] << 16) | ((u32)p[8] << 24);
}

/* Compresses `n` bytes of `data` and decompresses them again; non-zero when
 * the result differs. */
static int round_trip(const unsigned char *data, size_t n) {
    usize packed_len = 0u;
    usize again_len = 0u;
    unsigned char *packed = (unsigned char *)malloc(BREAK_RUNTIME_METRICS_COMPRESS_BOUND(n));
    unsigned char *again = (unsigned char *)malloc(n ? n : 1u);
    int rc = 1;
    if (!packed || !again) {
        rc = 0;
        goto done;
    }
    if (break_runtime_metrics_compress(data, n, packed, BREAK_RUNTIME_METRICS_COMPRESS_BOUND(n),
                                       &packed_len) != BREAK_RUNTIME_OK ||
        packed_len > BREAK_RUNTIME_METRICS_COMPRESS_BOUND(n)) {
        fprintf(stderr, "fuzz_decompress: compress failed on %lu bytes\n", (unsigned long)n);
        goto done;
    }
    if (break_runtime_metrics_decompress(packed, packed_len, again, n, &again_len) !=
            BREAK_RUNTIME_OK ||
        again_len != n || (n && memcmp(again, data, n) != 0)) {
        fprintf(stderr, "fuzz_decompress: round trip changed %lu bytes\n", (unsigned long)n);
        goto done;
    }
    rc = 0;
done:
    free(packed);
    free(again);
    return rc;
}

/* Returns non-zero on an invariant violation. */
static int check_payload(const unsigned char *data, size_t size) {
    unsigned char *copy = (unsigned char *)malloc(size ? size : 1u);
    unsigned char *out = (unsigned char *)malloc(k_out_cap);
    usize out_len = 0xDEADBEEFu;
    BreakRuntimeError r;
    int rc = 1;
    if (!copy || !out) {
        rc = 0;
        goto done;
    }
    if (size) memcpy(copy, data, size);

    r = break_runtime_metrics_decompress(copy, size, out, k_out_cap, &out_len);

    if (r == BREAK_RUNTIME_INVALID) {
        if (out_len != 0u) {
            fprintf(stderr, "fuzz_decompress: rejected input reported %lu bytes\n",
                    (unsigned long)out_len);
            goto done;
        }
        rc = 0;
        goto done;
    }
    if (r == BREAK_RUNTIME_OVERLOAD) {
        if (size < 9u || out_len != header_length(copy) || out_len <= k_out_cap) {
            fprintf(stderr, "fuzz_decompress: overload did not report the claimed length\n");
            goto done;
        }
        rc = 0;
        goto done;
    }
    if (r != BREAK_RUNTIME_OK) {
        fprintf(stderr, "fuzz_decompress: unexpected result %d\n", (int)r);
        goto done;
    }
    if (size < 9u || out_len != header_length(copy)) {
        fprintf(stderr, "fuzz_decompress: accepted output length differs from its header\n");
        goto done;
    }
    /* Every byte of an accepted stream is needed and nothing may follow it:
     * dropping the last byte or appending one must both be rejected. */
    {
        unsigned char *longer = (unsigned char *)malloc(size + 1u);
        usize n = 0u;
        int exact = 1;
        if (break_runtime_metrics_decompress(copy, size - 1u, out, k_out_cap, &n) !=
            BREAK_RUNTIME_INVALID)
            exact = 0;
        if (longer) {
            memcpy(longer, copy, size);
            longer[size] = 0u;
            if (break_runtime_metrics_decompress(longer, size + 1u, out, k_out_cap, &n) !=
                BREAK_RUNTIME_INVALID)
                exact = 0;
            free(longer);
        }
        if (!exact) {
            fprintf(stderr, "fuzz_decompress: accepted stream is not exact in length\n");
            goto done;
        }
        r = break_runtime_metrics_decompress(copy, size, out, k_out_cap, &out_len);
    }
    rc = r == BREAK_RUNTIME_OK ? round_trip(out, out_len) : 1;
done:
    free(copy);
    free(out);
    return rc;
}

#ifdef RUNTIME_METRICS_DECOMPRESS_LIBFUZZER
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (check_payload(data, size) != 0) abort();
    if (size <= 4096u && round_trip(data, size) != 0) abort();
    return 0;
}
#else
int main(int argc, char **argv) {
    enum { k_buf = 4096 };
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 2000L;
    unsigned char seed[k_buf];
    unsigned char *buf = (unsigned char *)malloc(k_buf);
    size_t seed_size = build_seed(seed, sizeof seed);
    unsigned accepted = 0u;
    unsigned rejected = 0u;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;
    if (!buf || seed_size == 0u) {
        free(buf);
        return 2;
    }
    if (check_payload(seed, seed_size) != 0) {
        free(buf);
        return 1;
    }
    for (long iteration = 0; iteration < iterations; ++iteration) {
        usize n = 0u;
        size_t size;
        unsigned char probe[256];
        memcpy(buf, seed, seed_size);
        size = mutate(buf, seed_size, k_buf);
        if (check_payload(buf, size) != 0) {
            fprintf(stderr, "fuzz_runtime_metrics_decompress: failed at iteration %ld, size %lu\n",
                    iteration, (unsigned long)size);
            free(buf);
            return 1;
        }
        if (break_runtime_metrics_decompress(buf, size, probe, sizeof probe, &n) ==
            BREAK_RUNTIME_OK) {
            ++accepted;
        } else {
            ++rejected;
        }
        /* Raw round trip on random bytes drawn from a small alphabet, so
         * matches of every length and distance occur. */
        {
            size_t raw_len = rnd() % 1024u;
            unsigned alphabet = rnd() % 4u + 1u;
            for (size_t k = 0u; k < raw_len; ++k) buf[k] = (unsigned char)('a' + rnd() % alphabet);
            if (round_trip(buf, raw_len) != 0) {
                fprintf(stderr, "fuzz_runtime_metrics_decompress: raw round trip failed at %ld\n",
                        iteration);
                free(buf);
                return 1;
            }
        }
    }
    free(buf);
    printf("fuzz_runtime_metrics_decompress: iterations=%ld accepted=%u rejected=%u\n",
           iterations, accepted, rejected);
    return 0;
}
#endif
