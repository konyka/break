/* Mutation fuzzer for BRWD/v1. Usage: fuzz_world_delta_wire [iterations] [seed].
 * With WORLD_DELTA_WIRE_LIBFUZZER=1 the same payload check is exported to
 * libFuzzer. Accepted payloads must re-encode byte-for-byte; rejected payloads
 * must leave a zeroed output and the input unchanged. */

#include <ecs/world_delta_wire.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

static void write_u32(u8 *out, u32 value) {
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
    out[2] = (u8)(value >> 16u);
    out[3] = (u8)(value >> 24u);
}

static bool message_is_zero(const BreakWorldDeltaWire *message) {
    BreakWorldDeltaWire zero;
    memset(&zero, 0, sizeof(zero));
    return memcmp(message, &zero, sizeof(zero)) == 0;
}

static int check_payload(const u8 *data, size_t size, BreakWorldDeltaWireResult *outcome) {
    u8 *payload = (u8 *)malloc(size ? size : 1u);
    u8 *reencoded = NULL;
    BreakWorldDeltaWire decoded;
    BreakWorldDeltaWireResult result;
    usize encoded_size = 0u;
    int rc = 1;
    if (!payload) return 1;
    if (size != 0u) memcpy(payload, data, size);
    memset(&decoded, 0xa5, sizeof(decoded));
    result = break_world_delta_wire_decode(payload, size, &decoded);
    if (outcome) *outcome = result;
    if (size != 0u && memcmp(payload, data, size) != 0) {
        fprintf(stderr, "fuzz_world_delta_wire: decoder modified its input\n");
        goto done;
    }
    if (result != BREAK_WORLD_DELTA_WIRE_OK) {
        if (!message_is_zero(&decoded)) {
            fprintf(stderr, "fuzz_world_delta_wire: rejected payload left a nonzero output\n");
            goto done;
        }
        rc = 0;
        goto done;
    }
    if (break_world_delta_wire_encoded_size(&decoded, &encoded_size) != BREAK_WORLD_DELTA_WIRE_OK ||
        encoded_size != size) {
        fprintf(stderr, "fuzz_world_delta_wire: accepted payload has a different encoded size\n");
        goto done;
    }
    reencoded = (u8 *)malloc(encoded_size ? encoded_size : 1u);
    if (!reencoded) goto done;
    if (break_world_delta_wire_encode(&decoded, reencoded, encoded_size, &encoded_size) !=
            BREAK_WORLD_DELTA_WIRE_OK ||
        encoded_size != size || memcmp(reencoded, payload, size) != 0) {
        fprintf(stderr, "fuzz_world_delta_wire: accepted payload is not canonical\n");
        goto done;
    }
    rc = 0;

done:
    free(reencoded);
    if (result == BREAK_WORLD_DELTA_WIRE_OK) break_world_delta_wire_clear(&decoded);
    free(payload);
    return rc;
}

static size_t mutate(u8 *wire, size_t size, size_t capacity) {
    static const u32 counts[] = {
        0u, 1u, 2u, 3u, BREAK_WORLD_DELTA_WIRE_MAX_RECORD_COUNT,
        BREAK_WORLD_DELTA_WIRE_MAX_RECORD_COUNT + 1u, UINT32_MAX
    };
    switch (rnd() % 7u) {
    case 0u:
        if (size != 0u) wire[rnd() % size] ^= (u8)(1u + rnd() % 255u);
        return size;
    case 1u:
        return size != 0u ? rnd() % size : 0u;
    case 2u:
        if (size >= 60u) write_u32(wire + 56u, counts[rnd() % 7u]);
        return size;
    case 3u:
        if (size >= 94u) {
            static const u32 sizes[] = {0u, 1u, 3u, 4u, 5u, 65535u, UINT32_MAX};
            write_u32(wire + 90u, sizes[rnd() % 7u]);
        }
        return size;
    case 4u:
        if (size >= 8u) {
            switch (rnd() % 3u) {
            case 0u: wire[rnd() % 4u] ^= (u8)(1u + rnd() % 255u); break;
            case 1u: wire[4u] = (u8)(rnd() % 3u); break;
            default: wire[6u] = (u8)(rnd() % 5u); break;
            }
        }
        return size;
    case 5u: {
        size_t extra = rnd() % 32u;
        if (extra > capacity - size) extra = capacity - size;
        for (size_t i = 0u; i < extra; ++i) wire[size + i] = (u8)rnd();
        return size + extra;
    }
    default:
        if (size != 0u) wire[rnd() % size] = rnd() % 2u ? 0u : 0xffu;
        return size;
    }
}

static size_t build_seed(u8 *out, size_t capacity, bool delta) {
    BreakWorldDeltaRecord records[2];
    static const u8 payload[] = {0xdeu, 0xadu, 0xbeu, 0xefu};
    BreakWorldDeltaWire message;
    usize size = 0u;
    memset(records, 0, sizeof(records));
    memset(&message, 0, sizeof(message));
    records[0].kind = BREAK_DELTA_ENTITY_CREATE;
    records[0].entity = (Entity){1u, 1u};
    records[1].kind = BREAK_DELTA_COMPONENT_ADD;
    records[1].entity = records[0].entity;
    records[1].component = 11u;
    records[1].bytes = payload;
    records[1].size = sizeof(payload);
    message.kind = delta ? BREAK_WORLD_DELTA_WIRE_DELTA : BREAK_WORLD_DELTA_WIRE_FULL;
    message.schema_hash = UINT64_C(0x1122334455667788);
    message.level_generation = UINT64_C(0x99aabbccddeeff00);
    message.base_snapshot_id = delta ? 9u : 0u;
    message.target_snapshot_id = UINT64_C(0x0102030405060708);
    message.base_tick = delta ? 1u : 0u;
    message.target_tick = 2u;
    message.record_count = 2u;
    message.records = records;
    if (break_world_delta_wire_encode(&message, out, capacity, &size) != BREAK_WORLD_DELTA_WIRE_OK) {
        return 0u;
    }
    return size;
}

#ifdef WORLD_DELTA_WIRE_LIBFUZZER
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (check_payload(data, size, NULL) != 0) abort();
    return 0;
}
#else
int main(int argc, char **argv) {
    enum { k_capacity = 4096 };
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 2000L;
    u8 seed_full[128];
    u8 seed_delta[128];
    u8 *wire = (u8 *)malloc(k_capacity);
    size_t full_size = build_seed(seed_full, sizeof(seed_full), false);
    size_t delta_size = build_seed(seed_delta, sizeof(seed_delta), true);
    unsigned accepted = 0u;
    unsigned rejected = 0u;
    unsigned over_limit = 0u;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;
    if (!wire || full_size == 0u || delta_size == 0u) {
        free(wire);
        return 2;
    }
    for (long iteration = 0; iteration < iterations; ++iteration) {
        size_t size;
        BreakWorldDeltaWireResult outcome = BREAK_WORLD_DELTA_WIRE_INVALID;
        if (rnd() % 2u == 0u) {
            memcpy(wire, seed_full, full_size);
            size = full_size;
        } else {
            memcpy(wire, seed_delta, delta_size);
            size = delta_size;
        }
        size = mutate(wire, size, k_capacity);
        if (check_payload(wire, size, &outcome) != 0) {
            fprintf(stderr, "fuzz_world_delta_wire: failed at iteration %ld, size %lu\n",
                    iteration, (unsigned long)size);
            free(wire);
            return 1;
        }
        if (outcome == BREAK_WORLD_DELTA_WIRE_OK) {
            ++accepted;
        } else if (outcome == BREAK_WORLD_DELTA_WIRE_OVER_LIMIT) {
            ++over_limit;
        } else {
            ++rejected;
        }
    }
    free(wire);
    printf("fuzz_world_delta_wire: iterations=%ld accepted=%u rejected=%u over_limit=%u\n",
           iterations, accepted, rejected, over_limit);
    return 0;
}
#endif
