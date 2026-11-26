/* Mutation fuzzer for the break_prediction wire decoders (input batches from
 * clients, snapshots from the server). Usage:
 *   fuzz_prediction_wire [iterations] [seed]
 * With PREDICTION_WIRE_LIBFUZZER=1 the same check is exported to libFuzzer.
 * Invariants, enforced on every input:
 *  - decoders never read past the input (ASan/UBSan);
 *  - a rejected input reports INVALID with a zeroed output;
 *  - an accepted input re-encodes to exactly the same bytes, and its byte
 *    pointer lies inside the input;
 *  - feeding an accepted batch to an inbox applies inputs in strict tick
 *    order and never more than the batch holds. */

#include <network/break_prediction_wire.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { k_input_size = 4, k_state_size = 8 };

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

static bool copy_step(void *user, const void *state, const void *input, void *out_state) {
    (void)user;
    memcpy(out_state, state, k_state_size);
    memcpy(out_state, input, k_input_size);
    return true;
}

static size_t build_input_seed(unsigned char *out, size_t cap, unsigned count) {
    static const unsigned char start[k_state_size] = {0};
    BreakPredictionConfig cfg;
    BreakPrediction *p = NULL;
    usize len = 0u;
    memset(&cfg, 0, sizeof cfg);
    cfg.state_size = k_state_size;
    cfg.input_size = k_input_size;
    cfg.capacity = 64u;
    cfg.step = copy_step;
    cfg.initial_tick = 0u;
    cfg.initial_state = start;
    if (break_prediction_create(&cfg, &p) != BREAK_PREDICTION_OK) return 0u;
    for (unsigned i = 0u; i < count; ++i) {
        unsigned char in[k_input_size] = {(unsigned char)i, 1, 2, 3};
        (void)break_prediction_apply_input(p, i + 1u, in);
    }
    if (break_prediction_wire_encode_inputs(p, out, cap, &len) != BREAK_PREDICTION_OK) len = 0u;
    break_prediction_destroy(p);
    return len;
}

static size_t build_snapshot_seed(unsigned char *out, size_t cap) {
    static const unsigned char state[k_state_size] = {9, 8, 7, 6, 5, 4, 3, 2};
    usize len = 0u;
    if (break_prediction_wire_encode_snapshot(42u, state, k_state_size, out, cap, &len) !=
        BREAK_PREDICTION_OK)
        return 0u;
    return len;
}

static size_t mutate(unsigned char *buf, size_t size, size_t capacity) {
    unsigned ops = rnd() % 4u + 1u;
    for (unsigned i = 0u; i < ops; ++i) {
        unsigned choice = rnd() % 6u;
        if (choice == 0u && size != 0u) {
            buf[rnd() % size] = (unsigned char)rnd();
        } else if (choice == 1u && size < capacity) {
            size_t at = rnd() % (size + 1u);
            memmove(buf + at + 1u, buf + at, size - at);
            buf[at] = (unsigned char)rnd();
            ++size;
        } else if (choice == 2u && size != 0u) {
            size_t at = rnd() % size;
            memmove(buf + at, buf + at + 1u, size - at - 1u);
            --size;
        } else if (choice == 3u && size >= 16u) {
            /* extreme tick */
            static const unsigned long long ticks[] = {0ull, 1ull, 0xFFFFFFFFull,
                                                       0xFFFFFFFFFFFFFFFEull,
                                                       0xFFFFFFFFFFFFFFFFull};
            unsigned long long t = ticks[rnd() % (sizeof ticks / sizeof ticks[0])];
            for (unsigned k = 0u; k < 8u; ++k) buf[8u + k] = (unsigned char)(t >> (8u * k));
        } else if (choice == 4u && size >= 8u) {
            /* extreme count or size byte */
            static const unsigned char vals[] = {0u, 1u, 31u, 32u, 33u, 255u};
            buf[4u + rnd() % 4u] = vals[rnd() % sizeof vals];
        } else if (size > 0u) {
            size = rnd() % size;
        }
    }
    return size;
}

typedef struct {
    u64 expect;
    u32 calls;
    int bad;
} ApplyCheck;

static bool ordered_apply(void *user, u64 tick, const void *input) {
    ApplyCheck *c = (ApplyCheck *)user;
    (void)input;
    if (tick != c->expect) c->bad = 1;
    c->expect = tick + 1u;
    c->calls++;
    return true;
}

static int check_inputs(const unsigned char *data, size_t size) {
    BreakPredictionInputBatch b;
    unsigned char *copy = (unsigned char *)malloc(size ? size : 1u);
    int rc = 1;
    if (!copy) return 0;
    if (size) memcpy(copy, data, size);
    if (break_prediction_wire_decode_inputs(copy, size, k_input_size, &b) != BREAK_PREDICTION_OK) {
        if (b.first_tick != 0u || b.count != 0u || b.input_size != 0u || b.inputs != NULL) {
            fprintf(stderr, "fuzz_prediction_wire: rejected batch left output\n");
            goto done;
        }
        rc = 0;
        goto done;
    }
    if (b.inputs != copy + BREAK_PREDICTION_WIRE_INPUT_HEADER ||
        size != BREAK_PREDICTION_WIRE_INPUT_HEADER + (size_t)b.count * k_input_size) {
        fprintf(stderr, "fuzz_prediction_wire: accepted batch is not exact\n");
        goto done;
    }
    {
        BreakPredictionInbox box;
        ApplyCheck c;
        u32 got = 0u;
        /* start the inbox somewhere inside or before the batch */
        u64 start = b.first_tick - (rnd() % 2u == 0u && b.first_tick > 1u ? 1u : 0u) +
                    (u64)(rnd() % (b.count + 1u));
        memset(&c, 0, sizeof c);
        c.expect = start;
        break_prediction_inbox_init(&box, start);
        if (break_prediction_inbox_accept(&box, &b, ordered_apply, &c, &got) != BREAK_PREDICTION_OK ||
            c.bad || got != c.calls || got > b.count) {
            fprintf(stderr, "fuzz_prediction_wire: inbox applied out of order\n");
            goto done;
        }
    }
    rc = 0;
done:
    free(copy);
    return rc;
}

static int check_snapshot(const unsigned char *data, size_t size) {
    BreakPredictionSnapshot s;
    unsigned char *copy = (unsigned char *)malloc(size ? size : 1u);
    unsigned char again[64];
    usize len = 0u;
    int rc = 1;
    if (!copy) return 0;
    if (size) memcpy(copy, data, size);
    if (break_prediction_wire_decode_snapshot(copy, size, k_state_size, &s) != BREAK_PREDICTION_OK) {
        if (s.tick != 0u || s.state_size != 0u || s.state != NULL) {
            fprintf(stderr, "fuzz_prediction_wire: rejected snapshot left output\n");
            goto done;
        }
        rc = 0;
        goto done;
    }
    if (break_prediction_wire_encode_snapshot(s.tick, s.state, s.state_size, again, sizeof again,
                                              &len) != BREAK_PREDICTION_OK ||
        len != size || memcmp(again, copy, size) != 0) {
        fprintf(stderr, "fuzz_prediction_wire: accepted snapshot is not canonical\n");
        goto done;
    }
    rc = 0;
done:
    free(copy);
    return rc;
}

#ifdef PREDICTION_WIRE_LIBFUZZER
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (check_inputs(data, size) != 0 || check_snapshot(data, size) != 0) abort();
    return 0;
}
#else
int main(int argc, char **argv) {
    enum { k_buf = 1024 };
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 2000L;
    unsigned char seeds[3][k_buf];
    size_t seed_sizes[3];
    unsigned char *buf = (unsigned char *)malloc(k_buf);
    unsigned accepted = 0u;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;
    seed_sizes[0] = build_input_seed(seeds[0], k_buf, 3u);
    seed_sizes[1] = build_input_seed(seeds[1], k_buf, 40u);
    seed_sizes[2] = build_snapshot_seed(seeds[2], k_buf);
    if (!buf || !seed_sizes[0] || !seed_sizes[1] || !seed_sizes[2]) {
        free(buf);
        return 2;
    }
    for (long it = 0; it < iterations; ++it) {
        unsigned which = rnd() % 3u;
        size_t size;
        BreakPredictionInputBatch b;
        BreakPredictionSnapshot s;
        memcpy(buf, seeds[which], seed_sizes[which]);
        size = mutate(buf, seed_sizes[which], k_buf);
        if (check_inputs(buf, size) != 0 || check_snapshot(buf, size) != 0) {
            fprintf(stderr, "fuzz_prediction_wire: failed at iteration %ld, size %lu\n", it,
                    (unsigned long)size);
            free(buf);
            return 1;
        }
        if (break_prediction_wire_decode_inputs(buf, size, k_input_size, &b) == BREAK_PREDICTION_OK ||
            break_prediction_wire_decode_snapshot(buf, size, k_state_size, &s) == BREAK_PREDICTION_OK)
            ++accepted;
    }
    free(buf);
    printf("fuzz_prediction_wire: iterations=%ld accepted=%u\n", iterations, accepted);
    return 0;
}
#endif
