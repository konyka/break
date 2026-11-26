/* Mutation fuzzer for break_runtime_metrics_retry_load, which parses a retry
 * backlog image read back from disk. The file is outside the process's
 * control: a crash mid-write, a bad sector or a tampered file can hand it any
 * bytes. Usage:
 *   fuzz_runtime_metrics_retry_load [iterations] [seed]
 * With RUNTIME_METRICS_RETRY_LOAD_LIBFUZZER=1 the same check is exported to
 * libFuzzer. Invariants, enforced on every input:
 *  - load never reads past the input or writes past the queue (ASan/UBSan);
 *  - a rejected input reports INVALID with *out_loaded = 0 and leaves the
 *    queue exactly as it was (same stats, same head payload);
 *  - an accepted input round-trips: saving a fresh queue loaded from it
 *    reproduces the input byte for byte, so acceptance is exact. */

#include <runtime/runtime_metrics.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { k_capacity = 8, k_max_payload = 32 };

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

static u32 fuzz_crc32(const unsigned char *p, size_t n) {
    u32 crc = 0xFFFFFFFFu;
    for (size_t i = 0u; i < n; ++i) {
        crc ^= p[i];
        for (int b = 0; b < 8; ++b) crc = (crc & 1u) ? (crc >> 1) ^ 0xEDB88320u : crc >> 1;
    }
    return ~crc;
}

static BreakRuntimeMetricsRetryQueue *make_queue(void) {
    BreakRuntimeMetricsRetryConfig cfg;
    BreakRuntimeMetricsRetryQueue *q = NULL;
    memset(&cfg, 0, sizeof(cfg));
    cfg.capacity = k_capacity;
    cfg.max_payload_bytes = k_max_payload;
    return break_runtime_metrics_retry_create(&cfg, &q) == BREAK_RUNTIME_OK ? q : NULL;
}

/* A real image from the library itself, so mutations start from valid bytes. */
static size_t build_seed(unsigned char *out, size_t cap) {
    BreakRuntimeMetricsRetryQueue *q = make_queue();
    u32 attempts = 0u;
    usize len = 0u;
    if (!q) return 0u;
    (void)break_runtime_metrics_retry_enqueue(q, "BRKM1 a counter 1\n", 18u);
    (void)break_runtime_metrics_retry_record_attempt(q, &attempts);
    (void)break_runtime_metrics_retry_enqueue(q, "x", 1u);
    (void)break_runtime_metrics_retry_enqueue(q, "BRKM1 q.depth gauge 7\n", 22u);
    if (break_runtime_metrics_retry_save(q, out, cap, &len) != BREAK_RUNTIME_OK) len = 0u;
    break_runtime_metrics_retry_destroy(q);
    return len;
}

static size_t mutate(unsigned char *buf, size_t size, size_t capacity) {
    unsigned ops = rnd() % 5u + 1u;
    for (unsigned i = 0u; i < ops; ++i) {
        unsigned choice = rnd() % 5u;
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
        } else if (choice == 3u && size > 9u) {
            /* Overwrite the count or an entry length field with an extreme. */
            static const u32 extremes[] = {0u, 1u, 2u, 255u, 65536u, 0x7FFFFFFFu, 0xFFFFFFFFu};
            u32 v = extremes[rnd() % (sizeof extremes / sizeof extremes[0])];
            size_t at = (rnd() & 1u) ? 5u : 9u + 4u + (rnd() % (size - 9u));
            for (size_t k = 0u; k < 4u && at + k < size; ++k) buf[at + k] = (unsigned char)(v >> (8u * k));
        } else if (size > 0u) {
            size = rnd() % size; /* truncate */
        }
    }
    /* Re-seal half of the inputs so mutations reach the checks behind the
     * CRC instead of all dying at the checksum. */
    if (size >= 4u && (rnd() & 1u)) {
        u32 crc = fuzz_crc32(buf, size - 4u);
        buf[size - 4u] = (unsigned char)crc;
        buf[size - 3u] = (unsigned char)(crc >> 8);
        buf[size - 2u] = (unsigned char)(crc >> 16);
        buf[size - 1u] = (unsigned char)(crc >> 24);
    }
    return size;
}

static int head_equals(BreakRuntimeMetricsRetryQueue *q, const char *expect, size_t n) {
    const void *bytes = NULL;
    usize len = 0u;
    u32 attempts = 0u;
    if (break_runtime_metrics_retry_peek(q, &bytes, &len, &attempts) != BREAK_RUNTIME_OK) return 0;
    return len == n && memcmp(bytes, expect, n) == 0;
}

/* Returns non-zero on an invariant violation. */
static int check_payload(const unsigned char *data, size_t size) {
    BreakRuntimeMetricsRetryQueue *q = make_queue();
    BreakRuntimeMetricsRetryStats before, after;
    unsigned char *copy;
    u32 loaded = 0xDEADBEEFu;
    BreakRuntimeError r;
    int rc = 1;
    if (!q) return 0;
    copy = (unsigned char *)malloc(size ? size : 1u);
    if (!copy) {
        break_runtime_metrics_retry_destroy(q);
        return 0;
    }
    if (size) memcpy(copy, data, size);
    (void)break_runtime_metrics_retry_enqueue(q, "resident", 8u);
    (void)break_runtime_metrics_retry_stats(q, &before);

    r = break_runtime_metrics_retry_load(q, copy, size, &loaded);

    if (r != BREAK_RUNTIME_OK) {
        if (r != BREAK_RUNTIME_INVALID) {
            fprintf(stderr, "fuzz_retry_load: unexpected result %d\n", (int)r);
            goto done;
        }
        (void)break_runtime_metrics_retry_stats(q, &after);
        if (loaded != 0u || memcmp(&before, &after, sizeof before) != 0 ||
            !head_equals(q, "resident", 8u)) {
            fprintf(stderr, "fuzz_retry_load: rejected input changed the queue\n");
            goto done;
        }
        rc = 0;
        goto done;
    }
    /* Accepted: load the same bytes into an empty queue and save it again. */
    {
        BreakRuntimeMetricsRetryQueue *fresh = make_queue();
        unsigned char *again;
        usize again_len = 0u;
        u32 n = 0u;
        if (!fresh) {
            rc = 0;
            goto done;
        }
        again = (unsigned char *)malloc(size + 1u);
        if (!again ||
            break_runtime_metrics_retry_load(fresh, copy, size, &n) != BREAK_RUNTIME_OK) {
            free(again);
            break_runtime_metrics_retry_destroy(fresh);
            fprintf(stderr, "fuzz_retry_load: accepted input failed to reload\n");
            goto done;
        }
        /* Only an image that fits the ring without eviction can round-trip. */
        if (n <= (u32)k_capacity) {
            if (break_runtime_metrics_retry_save(fresh, again, size + 1u, &again_len) !=
                    BREAK_RUNTIME_OK ||
                again_len != size || memcmp(again, copy, size) != 0) {
                free(again);
                break_runtime_metrics_retry_destroy(fresh);
                fprintf(stderr, "fuzz_retry_load: accepted input is not canonical\n");
                goto done;
            }
        }
        free(again);
        break_runtime_metrics_retry_destroy(fresh);
    }
    rc = 0;
done:
    free(copy);
    break_runtime_metrics_retry_destroy(q);
    return rc;
}

#ifdef RUNTIME_METRICS_RETRY_LOAD_LIBFUZZER
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (check_payload(data, size) != 0) abort();
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
        BreakRuntimeMetricsRetryQueue *probe = make_queue();
        u32 n = 0u;
        size_t size;
        memcpy(buf, seed, seed_size);
        size = mutate(buf, seed_size, k_buf);
        if (check_payload(buf, size) != 0) {
            fprintf(stderr, "fuzz_runtime_metrics_retry_load: failed at iteration %ld, size %lu\n",
                    iteration, (unsigned long)size);
            break_runtime_metrics_retry_destroy(probe);
            free(buf);
            return 1;
        }
        if (probe && break_runtime_metrics_retry_load(probe, buf, size, &n) == BREAK_RUNTIME_OK) {
            ++accepted;
        } else {
            ++rejected;
        }
        break_runtime_metrics_retry_destroy(probe);
    }
    free(buf);
    printf("fuzz_runtime_metrics_retry_load: iterations=%ld accepted=%u rejected=%u\n", iterations,
           accepted, rejected);
    return 0;
}
#endif
