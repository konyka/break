/* Mutation fuzzer for break_update_manifest_parse, the parser the update client
 * runs on the untrusted canonical "break-manifest-v1" text before any
 * signature check. Usage:
 *   fuzz_update_manifest [iterations] [seed]
 * With UPDATE_MANIFEST_LIBFUZZER=1 the same check is exported to libFuzzer.
 *
 * parse enforces a strict canonical form (ordered headers, decimal without
 * leading zeros with overflow checks, 64-hex chunk hashes, byte-sorted unique
 * chunk names, an 88-char base64 signature as the last line) and returns NULL
 * on ANY deviation. There is no serializer to round-trip against, so the
 * invariants are structural:
 *  - parse never reads or writes out of bounds (ASan/UBSan) and never modifies
 *    its input;
 *  - an accepted manifest exposes only in-bounds data: chunk_count matches how
 *    many chunk_at indices succeed, chunk_at fails past the count and its
 *    out_name is a readable string, and channel/platform are readable strings.
 *    This walks every accessor so an over-count or a dangling name pointer
 *    trips the sanitizer. */

#include <update/break_update.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* A structurally valid manifest (matches test_break_update.c), signature line
 * is canonical base64 of 64 zero bytes: parses, though it would not verify. */
static usize build_seed(char *out, usize capacity) {
    static const char seed[] =
        "break-manifest-v1\n"
        "version: 1.2.3\n"
        "channel: stable\n"
        "platform: linux-x86-64\n"
        "min-version: 0.9.0\n"
        "chunk: 31ca71057907d32be7a05d519e2ba060fc5e1ff59090021896e1019b1f819d33 4096 bin/engine\n"
        "chunk: a2e73e0d4b1284d0cbc821a45ab40ba2f52ade27152f2fc0a6cf75a8b15225c7 1048576 data/base.pak\n"
        "chunk: 715fcc4e06d98e89e24f0cd56313d2689b70cb421259aaadcff6807f0f6faf57 2048 shaders/pbr.spv\n"
        "signature: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAA==\n";
    usize len = sizeof(seed) - 1u;
    if (len > capacity) return 0u;
    memcpy(out, seed, len);
    return len;
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
            /* Lengthen a line in place to stress field/line length bounds. */
            usize nl = rnd() % size;
            while (nl < size && buf[nl] != '\n') ++nl;
            if (nl < size) {
                usize run = (rnd() % 4u == 0u) ? 1u + rnd() % 300u : 1u + rnd() % 16u;
                if (run > capacity - size) run = capacity - size;
                memmove(buf + nl + run, buf + nl, size - nl);
                for (usize j = 0u; j < run; ++j)
                    buf[nl + j] = (char)("0123456789abcdef./-"[rnd() % 19u]);
                size += run;
            }
        } else if (size < capacity) {
            buf[size++] = (rnd() & 1u) ? '\n' : (char)('0' + rnd() % 10u);
        }
    }
    return size;
}

/* Returns non-zero on an invariant violation. */
static int check_payload(const char *data, usize size) {
    char *copy = (char *)malloc(size ? size : 1u);
    BreakUpdateManifest *m;
    int rc = 1;
    if (!copy) return 1;
    if (size != 0u) memcpy(copy, data, size);

    m = break_update_manifest_parse(copy, size);

    if (size != 0u && memcmp(copy, data, size) != 0) {
        fprintf(stderr, "fuzz_update_manifest: parser modified its input\n");
        goto done;
    }
    if (!m) {
        rc = 0; /* rejection is fine */
        goto done;
    }
    {
        u32 ver[3], minver[3];
        const char *channel = break_update_manifest_channel(m);
        const char *platform = break_update_manifest_platform(m);
        u64 count = break_update_manifest_chunk_count(m);
        u64 idx;
        break_update_manifest_version(m, ver);
        break_update_manifest_min_version(m, minver);
        /* channel/platform must be readable C strings. */
        if (channel) (void)strlen(channel);
        if (platform) (void)strlen(platform);
        /* Every index below the count resolves with a readable name; the first
         * index at the count must fail. */
        for (idx = 0u; idx < count; ++idx) {
            const char *name = NULL;
            u8 hash[32];
            u64 csize = 0u;
            if (!break_update_manifest_chunk_at(m, idx, &name, hash, &csize)) {
                fprintf(stderr, "fuzz_update_manifest: chunk_at failed below count\n");
                goto done;
            }
            if (name) (void)strlen(name);
            (void)hash;
            (void)csize;
        }
        {
            const char *name = NULL;
            u8 hash[32];
            u64 csize = 0u;
            if (break_update_manifest_chunk_at(m, count, &name, hash, &csize)) {
                fprintf(stderr, "fuzz_update_manifest: chunk_at succeeded at count\n");
                goto done;
            }
        }
        /* compatible() must not read out of bounds for arbitrary args. */
        (void)break_update_manifest_compatible(m, "stable", "linux-x86-64", 1u, 2u, 3u);
    }
    rc = 0;
done:
    if (m) break_update_manifest_destroy(m);
    free(copy);
    return rc;
}

#ifdef UPDATE_MANIFEST_LIBFUZZER
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
    char seed[1024];
    usize seed_size = build_seed(seed, sizeof(seed));
    unsigned accepted = 0u;
    unsigned rejected = 0u;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;
    if (!buf || seed_size == 0u) {
        free(buf);
        return 2;
    }
    /* The untouched seed must parse, or the fuzzer never exercises accepts. */
    if (check_payload(seed, seed_size) != 0) {
        free(buf);
        return 1;
    }
    {
        BreakUpdateManifest *m = break_update_manifest_parse(seed, seed_size);
        if (!m) {
            fprintf(stderr, "fuzz_update_manifest: seed did not parse\n");
            free(buf);
            return 1;
        }
        break_update_manifest_destroy(m);
    }
    for (long iteration = 0; iteration < iterations; ++iteration) {
        BreakUpdateManifest *probe;
        usize size;
        memcpy(buf, seed, seed_size);
        size = mutate(buf, seed_size, k_capacity);
        if (check_payload(buf, size) != 0) {
            fprintf(stderr, "fuzz_update_manifest: failed at iteration %ld, size %lu\n", iteration,
                    (unsigned long)size);
            free(buf);
            return 1;
        }
        probe = break_update_manifest_parse(buf, size);
        if (probe) {
            ++accepted;
            break_update_manifest_destroy(probe);
        } else {
            ++rejected;
        }
    }
    free(buf);
    printf("fuzz_update_manifest: iterations=%ld accepted=%u rejected=%u\n", iterations, accepted,
           rejected);
    return 0;
}
#endif
