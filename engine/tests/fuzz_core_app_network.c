/* Mutation fuzzer for the core_app snapshot wire path.
 *
 * Builds a valid snapshot, encodes it, mutates the bytes (flip, truncate,
 * count, header fields, trailing garbage) and requires the decoder to agree
 * with an independent reference model of the wire rules. A rejected payload
 * must leave the caller's `out` untouched; an accepted payload must re-encode
 * to exactly the bytes it was decoded from. Accepted snapshots then cross the
 * inbound admission firewall and the bounded outbox, whose counters and FIFO
 * order are checked against shadow state. */

#include "../apps/core_app/core_app_network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

static u64 rnd64(void) {
    return ((u64)rnd() << 32) ^ (u64)rnd();
}

static u32 read_u32(const u8 *in) {
    return (u32)in[0] | ((u32)in[1] << 8) | ((u32)in[2] << 16) | ((u32)in[3] << 24);
}

static u16 read_u16(const u8 *in) {
    return (u16)((u16)in[0] | ((u16)in[1] << 8));
}

static void write_u32(u8 *out, u32 value) {
    for (u32 i = 0u; i < 4u; ++i) out[i] = (u8)((value >> (8u * i)) & 0xFFu);
}

static void write_u16(u8 *out, u16 value) {
    out[0] = (u8)(value & 0xFFu);
    out[1] = (u8)((value >> 8) & 0xFFu);
}

/* The wire rules restated without reference to the implementation. */
static CoreAppSnapshotOutcome reference_decode(const u8 *payload, size_t size) {
    if (size < CORE_APP_SNAPSHOT_HEADER_BYTES) return CORE_APP_SNAPSHOT_TRUNCATED;
    if (read_u32(payload) != CORE_APP_SNAPSHOT_MAGIC) return CORE_APP_SNAPSHOT_BAD_MAGIC;
    if (read_u16(payload + 4u) != CORE_APP_SNAPSHOT_VERSION) return CORE_APP_SNAPSHOT_BAD_VERSION;
    if (read_u16(payload + 6u) != CORE_APP_SNAPSHOT_HEADER_BYTES) {
        return CORE_APP_SNAPSHOT_BAD_VERSION;
    }
    u32 count = read_u32(payload + 28u);
    if (count > CORE_APP_SNAPSHOT_MAX_ENTITIES) return CORE_APP_SNAPSHOT_OVER_LIMIT;
    if (size < CORE_APP_SNAPSHOT_HEADER_BYTES + (size_t)count * CORE_APP_SNAPSHOT_ENTITY_BYTES) {
        return CORE_APP_SNAPSHOT_TRUNCATED;
    }
    return CORE_APP_SNAPSHOT_OK;
}

static f32 random_coordinate(void) {
    static const u32 k_special_bits[] = {
        0x7FC00000u, 0xFFC00000u, 0x7F800000u, 0xFF800000u, 0x00000001u, 0x80000000u
    };
    u32 bits;
    if (rnd() % 4u == 0u) {
        bits = k_special_bits[rnd() % (unsigned)(sizeof(k_special_bits) / sizeof(k_special_bits[0]))];
    } else {
        f32 value = (f32)((int)(rnd() % 20001u) - 10000) / 16.0f;
        memcpy(&bits, &value, sizeof(bits));
    }
    f32 out;
    memcpy(&out, &bits, sizeof(out));
    return out;
}

static void build_base(CoreAppSnapshot *snapshot, u32 schema) {
    CoreAppSnapshotEntity entities[CORE_APP_SNAPSHOT_MAX_ENTITIES];
    u32 count = rnd() % (CORE_APP_SNAPSHOT_MAX_ENTITIES + 1u);
    for (u32 i = 0u; i < count; ++i) {
        entities[i].index = rnd();
        entities[i].generation = rnd();
        entities[i].x = random_coordinate();
        entities[i].y = random_coordinate();
        entities[i].z = random_coordinate();
        entities[i].flags = rnd();
    }
    u32 snapshot_schema = rnd() % 4u == 0u ? rnd() : schema;
    if (core_app_snapshot_build(snapshot, rnd64(), rnd64() % 4u, snapshot_schema,
                                count ? entities : NULL, count) != CORE_APP_SNAPSHOT_OK) {
        fprintf(stderr, "fuzz_core_app_network: build rejected %u entities\n", count);
        exit(1);
    }
}

static size_t mutate(u8 *bytes, size_t size, size_t capacity) {
    switch (rnd() % 5u) {
        case 0u:
            if (size > 0u) bytes[rnd() % size] ^= (u8)(1u + rnd() % 255u);
            return size;
        case 1u:
            return size > 0u ? rnd() % size : 0u;
        case 2u: {
            static const u32 k_counts[] = {0u, 1u, 63u, 64u, 65u, 0xFFFFFFFFu};
            u32 count = rnd() % 2u == 0u
                            ? k_counts[rnd() % (unsigned)(sizeof(k_counts) / sizeof(k_counts[0]))]
                            : rnd();
            write_u32(bytes + 28u, count);
            return size;
        }
        case 3u:
            switch (rnd() % 3u) {
                case 0u: write_u32(bytes, rnd() % 2u ? rnd() : CORE_APP_SNAPSHOT_MAGIC ^ 1u); break;
                case 1u: write_u16(bytes + 4u, (u16)(rnd() % 3u)); break;
                default: write_u16(bytes + 6u, (u16)(30u + rnd() % 5u)); break;
            }
            return size;
        default: {
            size_t extra = rnd() % 64u;
            if (size + extra > capacity) extra = capacity - size;
            for (size_t i = 0u; i < extra; ++i) bytes[size + i] = (u8)rnd();
            return size + extra;
        }
    }
}

static CoreAppSnapshotAdmission reference_admit(const CoreAppSnapshotInbox *inbox, u16 message_id,
                                                const CoreAppSnapshot *snapshot, u64 live) {
    if (!inbox->authenticated) return CORE_APP_SNAPSHOT_REJECTED_UNAUTHENTICATED;
    if (message_id != inbox->admission_message_id) return CORE_APP_SNAPSHOT_REJECTED_UNKNOWN_MESSAGE;
    if (snapshot->schema_hash != inbox->peer_schema_hash) return CORE_APP_SNAPSHOT_REJECTED_SCHEMA;
    if (snapshot->level_generation != live) return CORE_APP_SNAPSHOT_REJECTED_STALE_LEVEL;
    return CORE_APP_SNAPSHOT_ADMITTED;
}

static int fail(const char *what, long iteration) {
    fprintf(stderr, "fuzz_core_app_network: %s at iteration %ld\n", what, iteration);
    return 1;
}

int main(int argc, char **argv) {
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 2000L;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;

    const u32 schema = core_app_snapshot_schema_hash();
    enum { k_capacity = CORE_APP_SNAPSHOT_MAX_BYTES + 64 };
    u8 *wire = (u8 *)malloc(k_capacity);
    CoreAppSnapshot *snapshot = (CoreAppSnapshot *)malloc(sizeof(*snapshot));
    CoreAppSnapshot *decoded = (CoreAppSnapshot *)malloc(sizeof(*decoded));
    CoreAppSnapshot *sentinel = (CoreAppSnapshot *)malloc(sizeof(*sentinel));
    CoreAppSnapshot *popped = (CoreAppSnapshot *)malloc(sizeof(*popped));
    CoreAppSnapshotOutbox *outbox = (CoreAppSnapshotOutbox *)malloc(sizeof(*outbox));
    u8 *reencoded = (u8 *)malloc(CORE_APP_SNAPSHOT_MAX_BYTES);
    if (!wire || !snapshot || !decoded || !sentinel || !popped || !outbox || !reencoded) {
        fprintf(stderr, "fuzz_core_app_network: out of memory\n");
        return 1;
    }
    memset(sentinel, 0xA5, sizeof(*sentinel));
    core_app_snapshot_outbox_init(outbox);
    u64 shadow_frames[CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY];
    u32 shadow_head = 0u;
    u32 shadow_count = 0u;
    u64 pushes = 0u;

    long accepted = 0;
    long rejected = 0;
    long admitted = 0;
    long outcome_counts[CORE_APP_SNAPSHOT_OVER_LIMIT + 1] = {0};
    for (long iteration = 0; iteration < iterations; ++iteration) {
        build_base(snapshot, schema);
        size_t size = 0u;
        if (core_app_snapshot_encode(snapshot, wire, k_capacity, &size) != CORE_APP_SNAPSHOT_OK) {
            return fail("encode rejected a built snapshot", iteration);
        }
        if (rnd() % 8u != 0u) size = mutate(wire, size, k_capacity);

        /* An exact-size heap copy lets ASan see any read past the payload. */
        u8 *payload = (u8 *)malloc(size ? size : 1u);
        if (!payload) return fail("out of memory", iteration);
        memcpy(payload, wire, size);
        memset(decoded, 0xA5, sizeof(*decoded));
        CoreAppSnapshotOutcome outcome = core_app_snapshot_decode(payload, size, decoded);
        CoreAppSnapshotOutcome expected = reference_decode(payload, size);
        if (outcome != expected) {
            fprintf(stderr, "fuzz_core_app_network: decode=%d reference=%d size=%lu\n",
                    (int)outcome, (int)expected, (unsigned long)size);
            return fail("decode disagrees with the reference model", iteration);
        }
        outcome_counts[outcome]++;
        if (outcome != CORE_APP_SNAPSHOT_OK) {
            free(payload);
            if (memcmp(decoded, sentinel, sizeof(*decoded)) != 0) {
                return fail("a rejected payload wrote into out", iteration);
            }
            rejected++;
            continue;
        }
        accepted++;
        size_t needed = 0u;
        if (core_app_snapshot_encode(decoded, reencoded, CORE_APP_SNAPSHOT_MAX_BYTES, &needed) !=
                CORE_APP_SNAPSHOT_OK ||
            needed > size || memcmp(reencoded, payload, needed) != 0) {
            free(payload);
            return fail("an accepted payload does not re-encode to its own bytes", iteration);
        }
        free(payload);

        CoreAppSnapshotInbox inbox;
        u16 admission_id = rnd() % 4u == 0u ? (u16)rnd() : (u16)CORE_APP_SNAPSHOT_MESSAGE_ID;
        u32 peer_schema = rnd() % 4u == 0u ? rnd() : schema;
        core_app_snapshot_inbox_init(&inbox, rnd() % 5u != 0u, admission_id, peer_schema);
        unsigned calls = 1u + rnd() % 4u;
        for (unsigned call = 0u; call < calls; ++call) {
            u16 message_id = rnd() % 3u == 0u ? (u16)rnd() : (u16)CORE_APP_SNAPSHOT_MESSAGE_ID;
            u64 live = rnd64() % 4u;
            CoreAppSnapshotAdmission want = reference_admit(&inbox, message_id, decoded, live);
            CoreAppSnapshotAdmission got = core_app_snapshot_admit(&inbox, message_id, decoded, live);
            if (got != want) return fail("admission disagrees with the reference model", iteration);
            if (got == CORE_APP_SNAPSHOT_ADMITTED) admitted++;
        }
        u64 total = inbox.accepted_snapshots + inbox.rejected_unknown_message +
                    inbox.rejected_unauthenticated + inbox.rejected_schema +
                    inbox.rejected_stale_level;
        if (total != calls) return fail("admission counters do not sum to the call count", iteration);

        pushes++;
        bool fits = shadow_count < CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY;
        CoreAppSnapshotOutcome pushed = core_app_snapshot_outbox_push(outbox, decoded);
        if ((pushed == CORE_APP_SNAPSHOT_OK) != fits) {
            return fail("outbox push disagrees with its capacity", iteration);
        }
        if (fits) {
            shadow_frames[(shadow_head + shadow_count) % CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY] =
                decoded->frame_id;
            shadow_count++;
        }
        if (outbox->count != shadow_count || outbox->enqueued + outbox->dropped != pushes) {
            return fail("outbox counters drifted", iteration);
        }
        unsigned pops = rnd() % 3u;
        for (unsigned p = 0u; p < pops; ++p) {
            bool have = core_app_snapshot_outbox_pop(outbox, popped);
            if (have != (shadow_count != 0u)) return fail("outbox pop disagrees with its count", iteration);
            if (!have) break;
            if (popped->frame_id != shadow_frames[shadow_head]) {
                return fail("outbox pop is not FIFO", iteration);
            }
            shadow_head = (shadow_head + 1u) % CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY;
            shadow_count--;
        }
    }

    printf("fuzz_core_app_network: iterations=%ld accepted=%ld rejected=%ld admitted=%ld "
           "truncated=%ld bad_magic=%ld bad_version=%ld over_limit=%ld enqueued=%llu dropped=%llu\n",
           iterations, accepted, rejected, admitted, outcome_counts[CORE_APP_SNAPSHOT_TRUNCATED],
           outcome_counts[CORE_APP_SNAPSHOT_BAD_MAGIC], outcome_counts[CORE_APP_SNAPSHOT_BAD_VERSION],
           outcome_counts[CORE_APP_SNAPSHOT_OVER_LIMIT], (unsigned long long)outbox->enqueued,
           (unsigned long long)outbox->dropped);
    free(wire);
    free(snapshot);
    free(decoded);
    free(sentinel);
    free(popped);
    free(outbox);
    free(reencoded);
    return 0;
}
