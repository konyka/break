/* Mutation fuzzer for break_http's response-head parser (parse_head), which
 * runs on bytes from an untrusted server: the status line and headers of every
 * update, crash-upload and metrics response. Usage:
 *   fuzz_http_head [iterations] [seed]
 * With HTTP_HEAD_LIBFUZZER=1 the same check is exported to libFuzzer.
 *
 * parse_head is static, so this file includes break_http.c directly (the
 * test_audio.c / test_pad_linux_feedback.c precedent) and does not link the
 * break_http library. Each input is copied into an exact-size heap buffer, so
 * any read past the head's length trips ASan. Invariants:
 *  - parse_head never reads or writes out of bounds (ASan/UBSan);
 *  - an accepted head has a status in 100..599, and a parsed Content-Range
 *    has first <= last;
 *  - the result is deterministic: a second parse of the same bytes gives the
 *    same verdict and the same fields. */

#include "../src/net_http/break_http.c"

#include <stdint.h>

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

static const char *const k_seeds[] = {
    "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nContent-Type: text/plain\r\n\r\n",
    "HTTP/1.1 206 Partial Content\r\nContent-Length: 100\r\n"
    "Content-Range: bytes 0-99/1000\r\n\r\n",
    "HTTP/1.0 204 No Content\r\n\r\n",
    "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nContent-Encoding: identity\r\n\r\n",
    "HTTP/1.1 206 Partial Content\r\nContent-Length: 10\r\nContent-Range: bytes 10-19/*\r\n\r\n",
};
#define SEED_COUNT (sizeof(k_seeds) / sizeof(k_seeds[0]))

static usize mutate(char *buf, usize size, usize capacity) {
    static const char k_alpha[] = "\r\n: -/*0123456789abcdefHTTPContent-LengthRange";
    unsigned ops = rnd() % 6u + 1u;
    for (unsigned i = 0u; i < ops; ++i) {
        unsigned choice = rnd() % 5u;
        if (choice == 0u && size != 0u) {
            buf[rnd() % size] = (char)(rnd() & 0xFFu); /* flip a byte */
        } else if (choice == 1u && size < capacity) {
            usize at = rnd() % (size + 1u);
            memmove(buf + at + 1u, buf + at, size - at);
            buf[at] = k_alpha[rnd() % (sizeof(k_alpha) - 1u)]; /* insert a grammar byte */
            ++size;
        } else if (choice == 2u && size != 0u) {
            usize at = rnd() % size;
            memmove(buf + at, buf + at + 1u, size - at - 1u);
            --size; /* delete */
        } else if (choice == 3u && size < capacity && size != 0u) {
            /* Duplicate a random slice in place: repeats header lines so the
             * 64-header cap and duplicate-header refusals are reached. */
            usize from = rnd() % size;
            usize run = 1u + rnd() % 64u;
            if (run > size - from) run = size - from;
            if (run > capacity - size) run = capacity - size;
            memmove(buf + from + run, buf + from, size - from);
            size += run;
        } else if (size != 0u) {
            size -= rnd() % (size < 8u ? size : 8u); /* truncate the tail */
        }
    }
    return size;
}

/* Returns non-zero on an invariant violation. */
static int check_payload(const char *data, usize size) {
    char *copy;
    Head a, b;
    bool ok_a, ok_b;
    if (size == 0u) return 0;
    copy = (char *)malloc(size);
    if (!copy) return 0;
    memcpy(copy, data, size);
    ok_a = parse_head(copy, size, &a);
    ok_b = parse_head(copy, size, &b);
    free(copy);
    if (ok_a != ok_b || (ok_a && memcmp(&a, &b, sizeof(a)) != 0)) {
        fprintf(stderr, "fuzz_http_head: parse is not deterministic\n");
        return 1;
    }
    if (ok_a) {
        if (a.status < 100 || a.status > 599) {
            fprintf(stderr, "fuzz_http_head: accepted status %d\n", a.status);
            return 1;
        }
        if (a.have_cr && a.cr_last < a.cr_first) {
            fprintf(stderr, "fuzz_http_head: accepted inverted Content-Range\n");
            return 1;
        }
    }
    return 0;
}

#ifdef HTTP_HEAD_LIBFUZZER
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size > BREAK_HTTP_MAX_HEAD) return 0;
    if (check_payload((const char *)data, size) != 0) abort();
    return 0;
}
#else
int main(int argc, char **argv) {
    enum { k_capacity = BREAK_HTTP_MAX_HEAD };
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 2000L;
    char *buf = (char *)malloc(k_capacity);
    unsigned accepted = 0u;
    unsigned rejected = 0u;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;
    if (!buf) return 2;
    /* Every untouched seed must parse, or the fuzzer never exercises accepts. */
    for (usize s = 0u; s < SEED_COUNT; ++s) {
        Head h;
        if (!parse_head(k_seeds[s], strlen(k_seeds[s]), &h)) {
            fprintf(stderr, "fuzz_http_head: seed %lu did not parse\n", (unsigned long)s);
            free(buf);
            return 1;
        }
    }
    for (long iteration = 0; iteration < iterations; ++iteration) {
        const char *seed = k_seeds[rnd() % SEED_COUNT];
        usize size = strlen(seed);
        Head h;
        memcpy(buf, seed, size);
        size = mutate(buf, size, k_capacity);
        if (check_payload(buf, size) != 0) {
            fprintf(stderr, "fuzz_http_head: failed at iteration %ld, size %lu\n", iteration,
                    (unsigned long)size);
            free(buf);
            return 1;
        }
        if (size != 0u && parse_head(buf, size, &h)) {
            ++accepted;
        } else {
            ++rejected;
        }
    }
    free(buf);
    printf("fuzz_http_head: iterations=%ld accepted=%u rejected=%u\n", iterations, accepted,
           rejected);
    return 0;
}
#endif
