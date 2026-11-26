/* Mutation fuzzer for break_crash_cluster_parse, the parser the crash collector
 * runs on the persisted "break-crash-stats v1" statistics file. Usage:
 *   fuzz_crash_cluster [iterations] [seed]
 * With CRASH_CLUSTER_LIBFUZZER=1 the same check is exported to libFuzzer.
 *
 * The parser fills fixed-size buffers (sig[65], seen[65], symbol[128], up to
 * 1024 builds / 4096 seen / 4096 signatures) and then re-serializes to demand
 * the input is exactly canonical. Invariants, on every input:
 *  - parse never reads or writes out of bounds (ASan/UBSan) and never modifies
 *    its input;
 *  - whatever it accepts round-trips: break_crash_cluster_serialize of the
 *    result reproduces the input byte-for-byte (the parser itself promises
 *    this canonical-form check, so the fuzzer holds it to it);
 *  - re-parsing that serialization succeeds and serializes identically.
 *
 * The seed is built at runtime through the public cluster API, because the
 * file embeds a crypto-derived layout the fuzzer should not hand-encode. */

#include <crash/break_crash_cluster.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* Builds a small valid statistics file into `out` via the real API; returns
 * its length, or 0 on failure. */
static usize build_seed(char *out, usize capacity) {
    BreakCrashClusterStore *s = break_crash_cluster_open("/nonexistent-dir-for-fuzz-seed/stats");
    BreakCrashClusterOutcome o;
    usize n = 0u;
    static const char h1[] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";
    static const char h2[] = "fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210";
    static const char sigA[] = "aaaa567890abcdefaaaa567890abcdefaaaa567890abcdefaaaa567890abcdef";
    static const char sigB[] = "bbbb567890abcdefbbbb567890abcdefbbbb567890abcdefbbbb567890abcdef";
    if (!s) return 0u;
    if (!break_crash_cluster_register_build(s, "build-001") ||
        !break_crash_cluster_register_build(s, "build-002")) {
        break_crash_cluster_destroy(s);
        return 0u;
    }
    break_crash_cluster_add(s, h1, sigA, "build-001", "frame_alpha", &o);
    break_crash_cluster_add(s, h2, sigB, "build-002", "frame_beta", &o);
    break_crash_cluster_mark_fixed(s, sigA, "build-002");
    n = break_crash_cluster_serialize(s, out, capacity);
    break_crash_cluster_destroy(s);
    return n;
}

static usize mutate(char *buf, usize size, usize capacity) {
    unsigned ops = rnd() % 6u + 1u;
    for (unsigned i = 0u; i < ops; ++i) {
        unsigned choice = rnd() % 5u;
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
        } else if (choice == 3u && size < capacity && size != 0u) {
            /* Lengthen a line in place to stress per-field bounds (sig/seen/
             * symbol/build-id) rather than only appending past the end. */
            usize nl = rnd() % size;
            while (nl < size && buf[nl] != '\n') ++nl;
            if (nl < size) {
                usize run = (rnd() % 4u == 0u) ? 1u + rnd() % 600u : 1u + rnd() % 16u;
                if (run > capacity - size) run = capacity - size;
                memmove(buf + nl + run, buf + nl, size - nl);
                for (usize j = 0u; j < run; ++j)
                    buf[nl + j] = (char)("0123456789abcdef"[rnd() % 16u]);
                size += run;
            }
        } else if (size < capacity) {
            buf[size++] = '\n'; /* add a line break */
        }
    }
    return size;
}

/* Returns non-zero on an invariant violation. */
static int check_payload(const char *data, usize size) {
    enum { k_cap = 1u << 22 }; /* BREAK_CRASH_CLUSTER_FILE_MAX */
    char *copy = (char *)malloc(size ? size : 1u);
    BreakCrashClusterStore *s;
    int rc = 1;
    if (!copy) return 1;
    if (size != 0u) memcpy(copy, data, size);

    s = break_crash_cluster_parse(copy, size);

    if (size != 0u && memcmp(copy, data, size) != 0) {
        fprintf(stderr, "fuzz_crash_cluster: parser modified its input\n");
        goto done;
    }
    if (!s) {
        rc = 0; /* rejection is fine */
        goto done;
    }
    {
        char *enc1 = (char *)malloc(k_cap);
        char *enc2 = (char *)malloc(k_cap);
        usize n1, n2;
        BreakCrashClusterStore *s2 = NULL;
        if (!enc1 || !enc2) {
            free(enc1);
            free(enc2);
            rc = 0;
            goto done;
        }
        n1 = break_crash_cluster_serialize(s, enc1, k_cap);
        /* The parser promised the input is exactly canonical: prove it. */
        if (n1 != size || memcmp(enc1, data, size) != 0) {
            fprintf(stderr, "fuzz_crash_cluster: accepted input is not canonical\n");
            free(enc1);
            free(enc2);
            goto done;
        }
        s2 = break_crash_cluster_parse(enc1, n1);
        if (!s2) {
            fprintf(stderr, "fuzz_crash_cluster: re-parse of serialized store failed\n");
            free(enc1);
            free(enc2);
            goto done;
        }
        n2 = break_crash_cluster_serialize(s2, enc2, k_cap);
        if (n2 != n1 || memcmp(enc1, enc2, n1) != 0) {
            fprintf(stderr, "fuzz_crash_cluster: serialize is not idempotent\n");
            break_crash_cluster_destroy(s2);
            free(enc1);
            free(enc2);
            goto done;
        }
        break_crash_cluster_destroy(s2);
        free(enc1);
        free(enc2);
    }
    rc = 0;
done:
    if (s) break_crash_cluster_destroy(s);
    free(copy);
    return rc;
}

#ifdef CRASH_CLUSTER_LIBFUZZER
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (check_payload((const char *)data, size) != 0) abort();
    return 0;
}
#else
int main(int argc, char **argv) {
    enum { k_capacity = 1u << 16 };
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 2000L;
    char *buf = (char *)malloc(k_capacity);
    char seed[4096];
    usize seed_size = build_seed(seed, sizeof(seed));
    unsigned accepted = 0u;
    unsigned rejected = 0u;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;
    if (!buf || seed_size == 0u) {
        fprintf(stderr, "fuzz_crash_cluster: could not build seed\n");
        free(buf);
        return 2;
    }
    /* The untouched seed must parse, or the fuzzer is not exercising accepts. */
    if (check_payload(seed, seed_size) != 0) {
        free(buf);
        return 1;
    }
    for (long iteration = 0; iteration < iterations; ++iteration) {
        BreakCrashClusterStore *probe;
        usize size;
        memcpy(buf, seed, seed_size);
        size = mutate(buf, seed_size, k_capacity);
        if (check_payload(buf, size) != 0) {
            fprintf(stderr, "fuzz_crash_cluster: failed at iteration %ld, size %lu\n", iteration,
                    (unsigned long)size);
            free(buf);
            return 1;
        }
        probe = break_crash_cluster_parse(buf, size);
        if (probe) {
            ++accepted;
            break_crash_cluster_destroy(probe);
        } else {
            ++rejected;
        }
    }
    free(buf);
    printf("fuzz_crash_cluster: iterations=%ld accepted=%u rejected=%u\n", iterations, accepted,
           rejected);
    return 0;
}
#endif
