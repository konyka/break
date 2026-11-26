/* Mutation fuzzer for break_crash_record_parse, the two-pass parser the crash
 * collector runs on untrusted "break-crash-v1" record text uploaded by a
 * client. Usage:
 *   fuzz_crash_record [iterations] [seed]
 * With CRASH_RECORD_LIBFUZZER=1 the same check is exported to libFuzzer.
 * Invariants, enforced on every input:
 *  - parse never reads or writes out of bounds (ASan/UBSan). The parser fills
 *    fixed-size buffers (stack_window, context_blob, modules[], build_id,
 *    module names) in pass 2 trusting pass 1's bounds, so a pass1/pass2
 *    disagreement would overflow here;
 *  - parse does not modify its input bytes;
 *  - an accepted record re-serializes within capacity and re-parses, and the
 *    serialize is idempotent (serialize(parse(serialize(parse(x)))) is byte-
 *    identical to serialize(parse(x))): acceptance has a stable canonical form,
 *    not a lenient one. */

#include <crash/break_crash.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* A byte-valid golden record to mutate from (matches test_break_crash.c). */
static usize build_seed(char *out, usize capacity) {
    static const char seed[] =
        "break-crash-v1\n"
        "signo: 0000000b\n"
        "code: 00000001\n"
        "fault_addr: 00000000deadbeef\n"
        "pid: 00000000000004d2\n"
        "tid: 000000000000162e\n"
        "rip: 0000000000401000\n"
        "rsp: 00007fffffffe000\n"
        "rbp: 00007fffffffe100\n"
        "build-id: abc123-x\n"
        "module: 0000000000002000 00000000001f0000 libc.so.6\n"
        "module: 0000000000001000 0000000000005000 app\n"
        "stack-window: 0123abcd\n"
        "context-blob: ff\n";
    usize len = sizeof(seed) - 1u; /* drop the implicit NUL */
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
            /* Grow a line in place: insert a run of hex digits just before a
             * randomly chosen newline. This lengthens a stack-window /
             * context-blob / module-name line while keeping the line structure,
             * so it actually stresses the parser's per-field length bounds
             * instead of only ever appending past the final newline. */
            usize nl = rnd() % size;
            while (nl < size && buf[nl] != '\n') ++nl;
            if (nl < size) {
                /* Mostly short runs, but sometimes a multi-KiB run so a single
                 * iteration can push a blob past its 4 KiB field bound (8192
                 * hex) from the small seed; that is what exercises the length
                 * check a dropped bound would miss. */
                usize run = (rnd() % 4u == 0u) ? 1u + rnd() % 12000u : 1u + rnd() % 64u;
                if (run > capacity - size) run = capacity - size;
                memmove(buf + nl + run, buf + nl, size - nl);
                for (usize j = 0u; j < run; ++j) buf[nl + j] = (char)("0123456789abcdef"[rnd() % 16u]);
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
    enum { k_cap = 1u << 16 };
    char *copy = (char *)malloc(size ? size : 1u);
    BreakCrashRecord *r;
    int rc = 1;
    if (!copy) return 1;
    if (size != 0u) memcpy(copy, data, size);

    r = break_crash_record_parse(copy, size);

    if (size != 0u && memcmp(copy, data, size) != 0) {
        fprintf(stderr, "fuzz_crash_record: parser modified its input\n");
        goto done;
    }
    if (!r) {
        rc = 0; /* rejection is fine */
        goto done;
    }
    /* Accepted: it must re-serialize and re-parse to a stable canonical form. */
    {
        u8 *enc1 = (u8 *)malloc(k_cap);
        u8 *enc2 = (u8 *)malloc(k_cap);
        usize n1, n2;
        BreakCrashRecord *r2 = NULL;
        if (!enc1 || !enc2) {
            free(enc1);
            free(enc2);
            rc = 0; /* allocator failure is not a parse fault */
            goto done;
        }
        n1 = break_crash_record_serialize(r, enc1, k_cap);
        if (n1 == 0u) {
            /* An accepted record that cannot serialize within 64 KiB would be a
             * contradiction, since the input that produced it was at most that. */
            fprintf(stderr, "fuzz_crash_record: accepted record failed to serialize\n");
            free(enc1);
            free(enc2);
            goto done;
        }
        r2 = break_crash_record_parse(enc1, n1);
        if (!r2) {
            fprintf(stderr, "fuzz_crash_record: re-parse of serialized record failed\n");
            free(enc1);
            free(enc2);
            goto done;
        }
        n2 = break_crash_record_serialize(r2, enc2, k_cap);
        if (n2 != n1 || memcmp(enc1, enc2, n1) != 0) {
            fprintf(stderr, "fuzz_crash_record: serialize is not idempotent\n");
            break_crash_record_destroy(r2);
            free(enc1);
            free(enc2);
            goto done;
        }
        break_crash_record_destroy(r2);
        free(enc1);
        free(enc2);
    }
    rc = 0;
done:
    if (r) break_crash_record_destroy(r);
    free(copy);
    return rc;
}

#ifdef CRASH_RECORD_LIBFUZZER
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
    for (long iteration = 0; iteration < iterations; ++iteration) {
        BreakCrashRecord *probe;
        usize size;
        memcpy(buf, seed, seed_size);
        size = mutate(buf, seed_size, k_capacity);
        if (check_payload(buf, size) != 0) {
            fprintf(stderr, "fuzz_crash_record: failed at iteration %ld, size %lu\n", iteration,
                    (unsigned long)size);
            free(buf);
            return 1;
        }
        probe = break_crash_record_parse(buf, size);
        if (probe) {
            ++accepted;
            break_crash_record_destroy(probe);
        } else {
            ++rejected;
        }
    }
    free(buf);
    printf("fuzz_crash_record: iterations=%ld accepted=%u rejected=%u\n", iterations, accepted,
           rejected);
    return 0;
}
#endif
