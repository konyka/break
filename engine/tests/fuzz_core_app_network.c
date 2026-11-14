/* Mutation fuzzer for the core_app snapshot wire path.
 *
 * Builds a valid snapshot, encodes it, mutates the bytes (flip, truncate,
 * count, header fields, trailing garbage) and requires the decoder to agree
 * with an independent reference model of the wire rules. A rejected payload
 * must leave the caller's `out` untouched; an accepted payload must re-encode
 * to exactly the bytes it was decoded from. Accepted snapshots then cross the
 * inbound admission firewall and the bounded outbox, whose counters and FIFO
 * order are checked against shadow state.
 *
 * Usage:
 *   fuzz_core_app_network [iterations] [seed]   random mutation run
 *   fuzz_core_app_network --emit-corpus <dir>   write the fixed wire samples
 *   fuzz_core_app_network --replay <file>...    check each sample against the
 *       outcome named by its file prefix (ok, truncated, bad_magic,
 *       bad_version, over_limit); every outcome must appear at least once. */

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

typedef struct CorpusKind {
    const char *prefix;
    CoreAppSnapshotOutcome outcome;
} CorpusKind;

static const CorpusKind k_corpus_kinds[] = {
    {"ok", CORE_APP_SNAPSHOT_OK},
    {"truncated", CORE_APP_SNAPSHOT_TRUNCATED},
    {"bad_magic", CORE_APP_SNAPSHOT_BAD_MAGIC},
    {"bad_version", CORE_APP_SNAPSHOT_BAD_VERSION},
    {"over_limit", CORE_APP_SNAPSHOT_OVER_LIMIT},
};
enum { k_corpus_kind_count = (int)(sizeof(k_corpus_kinds) / sizeof(k_corpus_kinds[0])) };
enum { k_corpus_level_generation = 2 };
enum { k_corpus_max_file_bytes = CORE_APP_SNAPSHOT_MAX_BYTES + 256 };

/* The file name prefix before the first '-' names the expected outcome. */
static int corpus_kind_of(const char *path) {
    const char *base = path;
    for (const char *p = path; *p; ++p) {
        if (*p == '/' || *p == '\\') base = p + 1;
    }
    const char *dash = strchr(base, '-');
    if (!dash) return -1;
    size_t len = (size_t)(dash - base);
    for (int i = 0; i < k_corpus_kind_count; ++i) {
        if (strlen(k_corpus_kinds[i].prefix) == len &&
            memcmp(k_corpus_kinds[i].prefix, base, len) == 0) {
            return i;
        }
    }
    return -1;
}

static int replay_one(const char *path, int *seen) {
    int kind = corpus_kind_of(path);
    if (kind < 0) {
        fprintf(stderr, "fuzz_core_app_network: %s: unknown outcome prefix\n", path);
        return 1;
    }
    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "fuzz_core_app_network: %s: cannot open\n", path);
        return 1;
    }
    u8 *bytes = (u8 *)malloc(k_corpus_max_file_bytes + 1);
    if (!bytes) {
        fclose(file);
        return 1;
    }
    size_t size = fread(bytes, 1u, (size_t)k_corpus_max_file_bytes + 1u, file);
    fclose(file);
    if (size > (size_t)k_corpus_max_file_bytes) {
        fprintf(stderr, "fuzz_core_app_network: %s: larger than %d bytes\n", path,
                k_corpus_max_file_bytes);
        free(bytes);
        return 1;
    }
    /* Exact-size copy so ASan sees any read past the payload. */
    u8 *payload = (u8 *)malloc(size ? size : 1u);
    CoreAppSnapshot *decoded = (CoreAppSnapshot *)malloc(sizeof(*decoded));
    CoreAppSnapshot *sentinel = (CoreAppSnapshot *)malloc(sizeof(*sentinel));
    u8 *reencoded = (u8 *)malloc(CORE_APP_SNAPSHOT_MAX_BYTES);
    int rc = 1;
    if (!payload || !decoded || !sentinel || !reencoded) goto done;
    memcpy(payload, bytes, size);
    memset(decoded, 0xA5, sizeof(*decoded));
    memset(sentinel, 0xA5, sizeof(*sentinel));
    CoreAppSnapshotOutcome want = k_corpus_kinds[kind].outcome;
    CoreAppSnapshotOutcome outcome = core_app_snapshot_decode(payload, size, decoded);
    if (outcome != want || reference_decode(payload, size) != want) {
        fprintf(stderr, "fuzz_core_app_network: %s: decode=%d reference=%d expected=%d\n", path,
                (int)outcome, (int)reference_decode(payload, size), (int)want);
        goto done;
    }
    if (outcome != CORE_APP_SNAPSHOT_OK) {
        if (memcmp(decoded, sentinel, sizeof(*decoded)) != 0) {
            fprintf(stderr, "fuzz_core_app_network: %s: rejected payload wrote into out\n", path);
            goto done;
        }
    } else {
        size_t needed = 0u;
        if (core_app_snapshot_encode(decoded, reencoded, CORE_APP_SNAPSHOT_MAX_BYTES, &needed) !=
                CORE_APP_SNAPSHOT_OK ||
            needed > size || memcmp(reencoded, payload, needed) != 0) {
            fprintf(stderr, "fuzz_core_app_network: %s: does not re-encode to its bytes\n", path);
            goto done;
        }
        u32 schema = core_app_snapshot_schema_hash();
        if (decoded->schema_hash != schema) {
            fprintf(stderr, "fuzz_core_app_network: %s: schema 0x%08x is not the current 0x%08x; "
                    "regenerate the corpus with --emit-corpus\n", path,
                    (unsigned)decoded->schema_hash, (unsigned)schema);
            goto done;
        }
        CoreAppSnapshotInbox inbox;
        core_app_snapshot_inbox_init(&inbox, true, (u16)CORE_APP_SNAPSHOT_MESSAGE_ID, schema);
        if (core_app_snapshot_admit(&inbox, (u16)CORE_APP_SNAPSHOT_MESSAGE_ID, decoded,
                                    decoded->level_generation) != CORE_APP_SNAPSHOT_ADMITTED ||
            core_app_snapshot_admit(&inbox, (u16)CORE_APP_SNAPSHOT_MESSAGE_ID, decoded,
                                    decoded->level_generation + 1u) !=
                CORE_APP_SNAPSHOT_REJECTED_STALE_LEVEL ||
            inbox.accepted_snapshots != 1u || inbox.rejected_stale_level != 1u) {
            fprintf(stderr, "fuzz_core_app_network: %s: admission is wrong\n", path);
            goto done;
        }
    }
    seen[kind]++;
    rc = 0;
done:
    free(bytes);
    free(payload);
    free(decoded);
    free(sentinel);
    free(reencoded);
    return rc;
}

static int replay_corpus(int count, char **paths) {
    int seen[k_corpus_kind_count] = {0};
    for (int i = 0; i < count; ++i) {
        if (replay_one(paths[i], seen) != 0) return 1;
    }
    for (int i = 0; i < k_corpus_kind_count; ++i) {
        if (seen[i] == 0) {
            fprintf(stderr, "fuzz_core_app_network: corpus has no '%s' file\n",
                    k_corpus_kinds[i].prefix);
            return 1;
        }
    }
    printf("fuzz_core_app_network: replayed=%d ok=%d truncated=%d bad_magic=%d bad_version=%d "
           "over_limit=%d\n", count, seen[0], seen[1], seen[2], seen[3], seen[4]);
    return 0;
}
static int emit_file(const char *dir, const char *name, const u8 *bytes, size_t size) {
    char path[1024];
    int n = snprintf(path, sizeof(path), "%s/%s.bin", dir, name);
    if (n < 0 || (size_t)n >= sizeof(path)) return 1;
    FILE *file = fopen(path, "wb");
    if (!file) {
        fprintf(stderr, "fuzz_core_app_network: cannot write %s\n", path);
        return 1;
    }
    size_t written = size ? fwrite(bytes, 1u, size, file) : 0u;
    int closed = fclose(file);
    return written == size && closed == 0 ? 0 : 1;
}

/* Fixed snapshot with `count` entities; no random numbers, so the corpus is
 * reproducible from the source alone. */
static size_t corpus_encode(u8 *out, u32 count, bool special_floats) {
    static const u32 k_special_bits[] = {0x7FC00000u, 0xFF800000u, 0x00000001u, 0x80000000u};
    CoreAppSnapshotEntity entities[CORE_APP_SNAPSHOT_MAX_ENTITIES];
    for (u32 i = 0u; i < count; ++i) {
        entities[i].index = i;
        entities[i].generation = 1u + i % 3u;
        entities[i].x = (f32)i * 0.5f;
        entities[i].y = -(f32)i;
        entities[i].z = 100.0f + (f32)i;
        entities[i].flags = i & 7u;
        if (special_floats) {
            memcpy(&entities[i].x, &k_special_bits[i % 4u], sizeof(f32));
            memcpy(&entities[i].z, &k_special_bits[(i + 1u) % 4u], sizeof(f32));
        }
    }
    CoreAppSnapshot *snapshot = (CoreAppSnapshot *)malloc(sizeof(*snapshot));
    size_t size = 0u;
    if (!snapshot ||
        core_app_snapshot_build(snapshot, 1000u + count, k_corpus_level_generation,
                                core_app_snapshot_schema_hash(), count ? entities : NULL,
                                count) != CORE_APP_SNAPSHOT_OK ||
        core_app_snapshot_encode(snapshot, out, CORE_APP_SNAPSHOT_MAX_BYTES, &size) !=
            CORE_APP_SNAPSHOT_OK) {
        size = 0u;
    }
    free(snapshot);
    return size;
}

static int emit_corpus(const char *dir) {
    u8 *bytes = (u8 *)calloc(1u, k_corpus_max_file_bytes);
    if (!bytes) return 1;
    int rc = 0;
    size_t size;

    size = corpus_encode(bytes, 0u, false);
    rc |= emit_file(dir, "ok-empty", bytes, size);
    size = corpus_encode(bytes, 1u, false);
    rc |= emit_file(dir, "ok-one", bytes, size);
    size = corpus_encode(bytes, CORE_APP_SNAPSHOT_MAX_ENTITIES, false);
    rc |= emit_file(dir, "ok-full", bytes, size);
    size = corpus_encode(bytes, 4u, true);
    rc |= emit_file(dir, "ok-special_floats", bytes, size);
    size = corpus_encode(bytes, 1u, false);
    for (u32 i = 0u; i < 16u; ++i) bytes[size + i] = (u8)(0xF0u + i);
    rc |= emit_file(dir, "ok-trailing_bytes", bytes, size + 16u);

    rc |= emit_file(dir, "truncated-empty", bytes, 0u);
    size = corpus_encode(bytes, 0u, false);
    rc |= emit_file(dir, "truncated-header", bytes, size - 1u);
    size = corpus_encode(bytes, 1u, false);
    rc |= emit_file(dir, "truncated-entity", bytes, size - 1u);
    size = corpus_encode(bytes, CORE_APP_SNAPSHOT_MAX_ENTITIES, false);
    rc |= emit_file(dir, "truncated-full_missing_entity", bytes,
                    size - CORE_APP_SNAPSHOT_ENTITY_BYTES);
    size = corpus_encode(bytes, 0u, false);
    write_u32(bytes + 28u, 1u);
    rc |= emit_file(dir, "truncated-count_without_entities", bytes, size);

    size = corpus_encode(bytes, 1u, false);
    write_u32(bytes, CORE_APP_SNAPSHOT_MAGIC ^ 1u);
    rc |= emit_file(dir, "bad_magic-flipped_bit", bytes, size);
    write_u32(bytes, 0u);
    rc |= emit_file(dir, "bad_magic-zero", bytes, size);

    size = corpus_encode(bytes, 1u, false);
    write_u16(bytes + 4u, 0u);
    rc |= emit_file(dir, "bad_version-zero", bytes, size);
    write_u16(bytes + 4u, CORE_APP_SNAPSHOT_VERSION + 1u);
    rc |= emit_file(dir, "bad_version-next", bytes, size);
    size = corpus_encode(bytes, 1u, false);
    write_u16(bytes + 6u, CORE_APP_SNAPSHOT_HEADER_BYTES - 1u);
    rc |= emit_file(dir, "bad_version-header_bytes", bytes, size);

    size = corpus_encode(bytes, 0u, false);
    write_u32(bytes + 28u, CORE_APP_SNAPSHOT_MAX_ENTITIES + 1u);
    rc |= emit_file(dir, "over_limit-count_65", bytes, size);
    write_u32(bytes + 28u, 0xFFFFFFFFu);
    rc |= emit_file(dir, "over_limit-count_max", bytes, size);

    free(bytes);
    if (rc == 0) printf("fuzz_core_app_network: corpus written to %s\n", dir);
    return rc;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--replay") == 0) return replay_corpus(argc - 2, argv + 2);
    if (argc == 3 && strcmp(argv[1], "--emit-corpus") == 0) return emit_corpus(argv[2]);
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
