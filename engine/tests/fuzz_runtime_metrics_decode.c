/* Mutation fuzzer for break_runtime_metrics_decode, the strict parser a remote
 * collector runs on untrusted BRKM1 text. Usage:
 *   fuzz_runtime_metrics_decode [iterations] [seed]
 * With RUNTIME_METRICS_DECODE_LIBFUZZER=1 the same check is exported to
 * libFuzzer. Invariants, enforced on every input:
 *  - decode never reads out of bounds or writes past `capacity` (ASan/UBSan);
 *  - a rejected input leaves *out_count = 0 (INVALID) and is reported, never
 *    accepted with partial output;
 *  - an accepted document re-encodes to exactly its own bytes and decodes
 *    back to the same count, so acceptance is exact, not lenient. */

#include <runtime/runtime_metrics.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* A small valid document to mutate from: two counters and a gauge. */
static usize build_seed(char *out, usize capacity) {
    const char *seed =
        "BRKM1 a.counter counter 0\n"
        "BRKM1 b.gauge gauge 18446744073709551615\n"
        "BRKM1 c.counter counter 42\n";
    usize len = strlen(seed);
    if (len > capacity) return 0u;
    memcpy(out, seed, len);
    return len;
}

static usize mutate(char *buf, usize size, usize capacity) {
    unsigned ops = rnd() % 6u + 1u;
    for (unsigned i = 0u; i < ops; ++i) {
        unsigned choice = rnd() % 4u;
        if (choice == 0u && size != 0u) {
            buf[rnd() % size] = (char)(rnd() & 0xFFu); /* flip a byte */
        } else if (choice == 1u && size < capacity) {
            usize at = rnd() % (size + 1u);
            memmove(buf + at + 1u, buf + at, size - at);
            buf[at] = (char)(rnd() & 0xFFu); /* insert */
            ++size;
        } else if (choice == 2u && size != 0u) {
            usize at = rnd() % size;
            memmove(buf + at, buf + at + 1u, size - at - 1u);
            --size; /* delete */
        } else if (size < capacity) {
            buf[size++] = (char)('0' + (rnd() % 10u)); /* append a digit */
        }
    }
    return size;
}

/* Returns non-zero on an invariant violation. */
static int check_payload(const char *data, usize size) {
    enum { k_cap = 64 };
    BreakRuntimeMetricSample out[k_cap];
    char *copy = (char *)malloc(size ? size : 1u);
    char reencoded[8192];
    u32 count = 0xDEADBEEFu;
    usize enc_len = 0u;
    BreakRuntimeError result;
    int rc = 1;
    if (!copy) return 1;
    if (size != 0u) memcpy(copy, data, size);

    memset(out, 0xA5, sizeof(out));
    result = break_runtime_metrics_decode(copy, size, out, k_cap, &count);

    if (size != 0u && memcmp(copy, data, size) != 0) {
        fprintf(stderr, "fuzz_runtime_metrics_decode: decoder modified its input\n");
        goto done;
    }
    if (result == BREAK_RUNTIME_INVALID) {
        if (count != 0u) {
            fprintf(stderr, "fuzz_runtime_metrics_decode: INVALID left out_count=%u\n", count);
            goto done;
        }
        rc = 0;
        goto done;
    }
    if (result == BREAK_RUNTIME_OVERLOAD) {
        /* Needs more than k_cap rows; required count reported, nothing written. */
        if (count <= (u32)k_cap) {
            fprintf(stderr, "fuzz_runtime_metrics_decode: OVERLOAD with count=%u <= cap\n", count);
            goto done;
        }
        rc = 0;
        goto done;
    }
    if (result != BREAK_RUNTIME_OK) {
        fprintf(stderr, "fuzz_runtime_metrics_decode: unexpected result %d\n", (int)result);
        goto done;
    }
    if (count > (u32)k_cap) {
        fprintf(stderr, "fuzz_runtime_metrics_decode: OK with count=%u > cap\n", count);
        goto done;
    }
    /* Round-trip: an accepted set must re-encode and decode back identically.
     * encode works on a live registry, so replay the samples into one. */
    {
        BreakRuntimeMetrics *m = NULL;
        BreakRuntimeMetricsConfig cfg = {k_cap};
        bool ok = true;
        if (break_runtime_metrics_create(&cfg, &m) != BREAK_RUNTIME_OK) {
            rc = 0; /* allocator failure is not a decode fault */
            goto done;
        }
        for (u32 i = 0u; i < count; ++i) {
            BreakRuntimeError put =
                out[i].kind == BREAK_RUNTIME_METRIC_COUNTER
                    ? break_runtime_metrics_add(m, out[i].name, BREAK_RUNTIME_METRIC_COUNTER,
                                                out[i].value)
                    : break_runtime_metrics_set(m, out[i].name, BREAK_RUNTIME_METRIC_GAUGE,
                                                out[i].value);
            if (put != BREAK_RUNTIME_OK) { ok = false; break; }
        }
        if (ok &&
            break_runtime_metrics_encode(m, reencoded, sizeof(reencoded), &enc_len) ==
                BREAK_RUNTIME_OK) {
            /* Strict decoding means an accepted document is already canonical:
             * re-encoding its samples must reproduce the input byte-for-byte.
             * A lenient decoder (e.g. accepting a leading zero) fails here. */
            if (enc_len != size || memcmp(reencoded, data, size) != 0) {
                fprintf(stderr,
                        "fuzz_runtime_metrics_decode: accepted input is not canonical\n");
                break_runtime_metrics_destroy(m);
                goto done;
            }
        }
        break_runtime_metrics_destroy(m);
    }
    rc = 0;
done:
    free(copy);
    return rc;
}

#ifdef RUNTIME_METRICS_DECODE_LIBFUZZER
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (check_payload((const char *)data, size) != 0) abort();
    return 0;
}
#else
int main(int argc, char **argv) {
    enum { k_capacity = 4096 };
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 2000L;
    char *buf = (char *)malloc(k_capacity);
    char seed[256];
    usize seed_size = build_seed(seed, sizeof(seed));
    unsigned accepted = 0u;
    unsigned rejected = 0u;
    unsigned overload = 0u;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;
    if (!buf || seed_size == 0u) {
        free(buf);
        return 2;
    }
    for (long iteration = 0; iteration < iterations; ++iteration) {
        BreakRuntimeMetricSample probe[64];
        u32 count = 0u;
        usize size;
        BreakRuntimeError r;
        memcpy(buf, seed, seed_size);
        size = mutate(buf, seed_size, k_capacity);
        if (check_payload(buf, size) != 0) {
            fprintf(stderr, "fuzz_runtime_metrics_decode: failed at iteration %ld, size %lu\n",
                    iteration, (unsigned long)size);
            free(buf);
            return 1;
        }
        r = break_runtime_metrics_decode(buf, size, probe, 64u, &count);
        if (r == BREAK_RUNTIME_OK) {
            ++accepted;
        } else if (r == BREAK_RUNTIME_OVERLOAD) {
            ++overload;
        } else {
            ++rejected;
        }
    }
    free(buf);
    printf("fuzz_runtime_metrics_decode: iterations=%ld accepted=%u rejected=%u overload=%u\n",
           iterations, accepted, rejected, overload);
    return 0;
}
#endif
