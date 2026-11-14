/* Mutation fuzzer for the checkpoint reader.
 *
 * Builds a valid checkpoint through the real writer, then repeatedly mutates
 * the manifest and payload bytes and feeds them back through the real
 * manifest reader and per-kind payload lookup. Any classified failure is
 * acceptable; a crash, out-of-bounds read, leak, or a mutation that makes a
 * previously valid payload report a different kind is not. A sentinel
 * checkpoint that stays valid throughout must remain readable, so a rejected
 * mutation never corrupts unrelated state.
 *
 * Usage:
 *   fuzz_core_app_checkpoint [iterations] [seed]   random mutation run
 *   fuzz_core_app_checkpoint --emit-corpus <dir>   write the fixed manifest samples
 *   fuzz_core_app_checkpoint --replay <file>...    stage each sample as manifest.core
 *       next to the four fixed payloads and check probe and find(RUNTIME) against
 *       its `ok-`, `nofind-`, `invalid-` or `overload-` prefix; every prefix must
 *       appear at least once. */

#include "../apps/core_app/core_app_checkpoint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#include <process.h>
#define fuzz_getpid _getpid
#define fuzz_mkdir(p) _mkdir(p)
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define fuzz_getpid getpid
#define fuzz_mkdir(p) mkdir((p), 0700)
#endif

/* Joins a directory and a fixed leaf into a path buffer. The compiler cannot
 * prove a fixed literal plus an arbitrary directory fits, so the truncation is
 * handled explicitly here and every caller keeps the same bound. */
static void join_path(char *out, size_t cap, const char *directory, const char *leaf) {
    int written = snprintf(out, cap, "%s/%s", directory, leaf);
    if (written < 0 || (size_t)written >= cap) out[cap - 1u] = '\0';
}

/* The fuzzer owns one scratch tree per invocation. A previous interrupted run
 * may have left it behind, so the known files are removed before the tree is
 * rebuilt; every run therefore starts from exactly the same bytes. */
static void remove_tree(const char *directory) {
    static const char *const leaves[] = {
        "manifest.core", "scene_1.bscn", "flow_1.fg", "actors_1.sidecar",
        "runtime_1.bin"
    };
    char path[700];
    for (size_t i = 0u; i < sizeof(leaves) / sizeof(leaves[0]); ++i) {
        join_path(path, sizeof(path), directory, leaves[i]);
        (void)remove(path);
    }
#ifdef _WIN32
    (void)_rmdir(directory);
#else
    (void)rmdir(directory);
#endif
}

static unsigned long long rng_state = 0x2545F4914F6CDD1DULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* The four payloads every checkpoint in this fuzzer refers to. */
static const unsigned char k_scene[96] = {0x42u, 0x53u, 0x43u, 0x4Eu};
static const unsigned char k_flow[64] = {0x42u, 0x46u, 0x4Cu, 0x57u};
static const unsigned char k_actors[48] = {'2', ' ', 'U', 's', 'e', 'r', '\n'};
static const unsigned char k_runtime[72] = {0x43u, 0x4Fu, 0x52u, 0x45u};

static void scratch_root(char *out, size_t cap) {
    snprintf(out, cap, "fuzz_core_app_ckpt_%d", (int)fuzz_getpid());
}

static int make_directory(const char *path) {
    if (fuzz_mkdir(path) == 0) return 1;
    /* A leftover directory from an earlier crashed run is reusable. */
    char probe[600];
    join_path(probe, sizeof(probe), path, "manifest.core");
    FILE *file = fopen(probe, "rb");
    if (!file) return 0;
    fclose(file);
    return 1;
}

static int write_payload(const char *directory, const char *name, const void *bytes,
                         size_t size) {
    char path[600];
    join_path(path, sizeof(path), directory, name);
    FILE *file = fopen(path, "wb");
    if (!file) return 0;
    int ok = fwrite(bytes, 1u, size, file) == size;
    fclose(file);
    return ok;
}

static unsigned char *read_all(const char *path, long *out_size) {
    FILE *file = fopen(path, "rb");
    if (!file) return NULL;
    if (fseek(file, 0, SEEK_END) != 0) { fclose(file); return NULL; }
    long size = ftell(file);
    if (size < 0 || fseek(file, 0, SEEK_SET) != 0) { fclose(file); return NULL; }
    unsigned char *bytes = (unsigned char *)malloc((size_t)size + 1u);
    if (!bytes) { fclose(file); return NULL; }
    if (fread(bytes, 1u, (size_t)size, file) != (size_t)size) {
        free(bytes);
        fclose(file);
        return NULL;
    }
    fclose(file);
    *out_size = size;
    return bytes;
}

/* One mutation family, chosen per iteration so every family is exercised. */
static void mutate(unsigned char *bytes, long size) {
    if (size <= 0) return;
    switch (rnd() % 5u) {
        case 0u: { /* truncate */
            long keep = (long)(rnd() % (unsigned)size);
            bytes[keep] = bytes[keep]; /* keep the buffer allocation intact */
            bytes[size - 1] = 0u;
            break;
        }
        case 1u: { /* single bit flip */
            long at = (long)(rnd() % (unsigned)size);
            bytes[at] ^= (unsigned char)(1u << (rnd() % 8u));
            break;
        }
        case 2u: { /* overwrite a 4-byte little-endian word with a hostile value */
            long at = (long)(rnd() % (unsigned)(size > 4 ? size - 4 : 1));
            unsigned value = 0xFFFFFFFFu;
            memcpy(bytes + at, &value, 4u);
            break;
        }
        case 3u: { /* zero a run */
            long at = (long)(rnd() % (unsigned)size);
            long run = (long)(rnd() % 32u) + 1L;
            if (at + run > size) run = size - at;
            memset(bytes + at, 0, (size_t)run);
            break;
        }
        default: { /* duplicate a byte to shift field alignment */
            long at = (long)(rnd() % (unsigned)size);
            bytes[at] = (unsigned char)(rnd() & 0xFFu);
            break;
        }
    }
}

/* ---- Checked-in manifest corpus ------------------------------------------
 * The encoder below is written independently of the production writer so the
 * corpus pins the on-disk format rather than whatever the writer emits. */

#define CORPUS_HEADER_BYTES 40u
#define CORPUS_RECORD_BYTES 88u
#define CORPUS_MAX_BYTES 1600u

typedef struct CorpusRecord {
    u32 kind;
    const char *name;
    u64 size;
    u64 hash;
} CorpusRecord;

static u64 corpus_hash(const unsigned char *bytes, size_t size) {
    u64 hash = 14695981039346656037ULL;
    for (size_t i = 0u; i < size; ++i) {
        hash ^= (u64)bytes[i];
        hash *= 1099511628211ULL;
    }
    return hash;
}

static void corpus_put32(unsigned char *p, u32 value) {
    for (unsigned i = 0u; i < 4u; ++i) p[i] = (unsigned char)(value >> (8u * i));
}

static void corpus_put64(unsigned char *p, u64 value) {
    for (unsigned i = 0u; i < 8u; ++i) p[i] = (unsigned char)(value >> (8u * i));
}

static u32 corpus_get32(const unsigned char *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static u64 corpus_get64(const unsigned char *p) {
    return (u64)corpus_get32(p) | ((u64)corpus_get32(p + 4) << 32);
}

/* The four records that match the payloads replay writes to disk. */
static void corpus_default_records(CorpusRecord out[4]) {
    out[0] = (CorpusRecord){CORE_APP_CHECKPOINT_SCENE, "scene_1.bscn", sizeof(k_scene),
                            corpus_hash(k_scene, sizeof(k_scene))};
    out[1] = (CorpusRecord){CORE_APP_CHECKPOINT_FLOW, "flow_1.fg", sizeof(k_flow),
                            corpus_hash(k_flow, sizeof(k_flow))};
    out[2] = (CorpusRecord){CORE_APP_CHECKPOINT_ACTORS, "actors_1.sidecar", sizeof(k_actors),
                            corpus_hash(k_actors, sizeof(k_actors))};
    out[3] = (CorpusRecord){CORE_APP_CHECKPOINT_RUNTIME, "runtime_1.bin", sizeof(k_runtime),
                            corpus_hash(k_runtime, sizeof(k_runtime))};
}

/* Header plus `count` records; the size field matches the encoded length. */
static size_t corpus_encode(unsigned char out[CORPUS_MAX_BYTES], u64 generation,
                            const CorpusRecord *records, u32 count) {
    size_t size = CORPUS_HEADER_BYTES + (size_t)count * CORPUS_RECORD_BYTES;
    memset(out, 0, CORPUS_MAX_BYTES);
    memcpy(out, "CORECKPT", 8u);
    corpus_put32(out + 8, 1u);
    corpus_put32(out + 12, CORPUS_HEADER_BYTES);
    corpus_put64(out + 16, (u64)size);
    corpus_put64(out + 24, generation);
    corpus_put32(out + 32, count);
    for (u32 i = 0u; i < count; ++i) {
        unsigned char *record = out + CORPUS_HEADER_BYTES + (size_t)i * CORPUS_RECORD_BYTES;
        size_t name_length = strlen(records[i].name);
        corpus_put32(record, records[i].kind);
        corpus_put32(record + 4, (u32)name_length);
        corpus_put64(record + 8, records[i].size);
        corpus_put64(record + 16, records[i].hash);
        memcpy(record + 24, records[i].name, name_length);
    }
    return size;
}

static unsigned char *corpus_record(unsigned char *bytes, u32 index) {
    return bytes + CORPUS_HEADER_BYTES + (size_t)index * CORPUS_RECORD_BYTES;
}

static int emit_bytes(const char *dir, const char *name, const unsigned char *bytes,
                      size_t size) {
    char path[1024];
    int n = snprintf(path, sizeof(path), "%s/%s.core", dir, name);
    if (n < 0 || (size_t)n >= sizeof(path)) return 1;
    FILE *file = fopen(path, "wb");
    if (!file) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot write %s\n", path);
        return 1;
    }
    size_t written = size ? fwrite(bytes, 1u, size, file) : 0u;
    int closed = fclose(file);
    return written == size && closed == 0 ? 0 : 1;
}

/* Encodes the default four records, lets `edit` change one field, writes it. */
#define EMIT_EDITED(label, edit)                                          \
    do {                                                                  \
        size = corpus_encode(bytes, 1u, base, 4u);                        \
        edit;                                                             \
        rc |= emit_bytes(dir, label, bytes, size);                        \
    } while (0)

/* Default records with one record renamed, so every basename rule is pinned. */
static size_t corpus_encode_renamed(unsigned char out[CORPUS_MAX_BYTES], u32 index,
                                    const char *name) {
    CorpusRecord records[4];
    corpus_default_records(records);
    records[index].name = name;
    return corpus_encode(out, 1u, records, 4u);
}

static int emit_corpus(const char *dir) {
    unsigned char bytes[CORPUS_MAX_BYTES];
    CorpusRecord base[4];
    corpus_default_records(base);
    CorpusRecord edited[4];
    size_t size = 0u;
    int rc = 0;

    EMIT_EDITED("ok-basic", (void)0);
    size = corpus_encode(bytes, 0xFFFFFFFFFFFFFFFFULL, base, 4u);
    rc |= emit_bytes(dir, "ok-max_generation", bytes, size);
    edited[0] = base[3];
    edited[1] = base[0];
    edited[2] = base[1];
    edited[3] = base[2];
    size = corpus_encode(bytes, 7u, edited, 4u);
    rc |= emit_bytes(dir, "ok-runtime_first", bytes, size);
    size = corpus_encode(bytes, 2u, &base[3], 1u);
    rc |= emit_bytes(dir, "ok-runtime_only", bytes, size);

    size = corpus_encode(bytes, 1u, base, 3u);
    rc |= emit_bytes(dir, "nofind-missing_runtime", bytes, size);
    EMIT_EDITED("nofind-duplicate_runtime_kind",
                corpus_put32(corpus_record(bytes, 0u), CORE_APP_CHECKPOINT_RUNTIME));
    EMIT_EDITED("nofind-unknown_kind", corpus_put32(corpus_record(bytes, 3u), 99u));

    EMIT_EDITED("invalid-magic", bytes[0] = 'X');
    EMIT_EDITED("invalid-version", corpus_put32(bytes + 8, 2u));
    EMIT_EDITED("invalid-header_bytes", corpus_put32(bytes + 12, 48u));
    EMIT_EDITED("invalid-size_field", corpus_put64(bytes + 16, (u64)size + 1u));
    EMIT_EDITED("invalid-size_field_high_bits",
                corpus_put64(bytes + 16, (u64)size | (1ULL << 32)));
    EMIT_EDITED("invalid-reserved_word", corpus_put32(bytes + 36, 1u));
    EMIT_EDITED("invalid-generation_zero", corpus_put64(bytes + 24, 0u));
    size = corpus_encode(bytes, 1u, base, 0u);
    rc |= emit_bytes(dir, "invalid-count_zero", bytes, size);
    EMIT_EDITED("invalid-count_mismatch", corpus_put32(bytes + 32, 3u));
    EMIT_EDITED("invalid-truncated_record",
                (size -= 1u, corpus_put64(bytes + 16, (u64)size)));
    EMIT_EDITED("invalid-name_length_zero", corpus_put32(corpus_record(bytes, 0u) + 4, 0u));
    EMIT_EDITED("invalid-name_length_short", corpus_put32(corpus_record(bytes, 0u) + 4, 5u));
    EMIT_EDITED("invalid-name_length_long", corpus_put32(corpus_record(bytes, 0u) + 4, 13u));
    EMIT_EDITED("invalid-name_padding", corpus_record(bytes, 0u)[24 + 60] = 1u);
    EMIT_EDITED("invalid-kind_zero", corpus_put32(corpus_record(bytes, 0u), 0u));
    EMIT_EDITED("invalid-payload_hash",
                corpus_put64(corpus_record(bytes, 3u) + 16, base[3].hash + 1u));
    EMIT_EDITED("invalid-payload_size",
                corpus_put64(corpus_record(bytes, 3u) + 8, base[3].size + 1u));
    size = corpus_encode_renamed(bytes, 3u, "absent.bin");
    rc |= emit_bytes(dir, "invalid-payload_missing", bytes, size);
    size = corpus_encode_renamed(bytes, 0u, "scene_1.bscn.");
    rc |= emit_bytes(dir, "invalid-name_trailing_dot", bytes, size);
    size = corpus_encode_renamed(bytes, 0u, "scene..bscn");
    rc |= emit_bytes(dir, "invalid-name_dot_dot", bytes, size);
    size = corpus_encode_renamed(bytes, 0u, "sub/scene_1.bscn");
    rc |= emit_bytes(dir, "invalid-name_slash", bytes, size);
    size = corpus_encode_renamed(bytes, 0u, "sub\\scene_1.bscn");
    rc |= emit_bytes(dir, "invalid-name_backslash", bytes, size);
    size = corpus_encode_renamed(bytes, 0u, "scene 1.bscn");
    rc |= emit_bytes(dir, "invalid-name_space", bytes, size);
    size = corpus_encode_renamed(bytes, 0u, "MANIFEST.CORE");
    rc |= emit_bytes(dir, "invalid-name_manifest", bytes, size);
    size = corpus_encode_renamed(bytes, 1u, "SCENE_1.BSCN");
    rc |= emit_bytes(dir, "invalid-name_duplicate_case", bytes, size);
    /* Same payload listed twice under one name: every record probes on its own,
       so only the duplicate-name rule rejects it on a case-sensitive filesystem. */
    memcpy(edited, base, sizeof(edited));
    edited[1] = base[0];
    edited[1].kind = CORE_APP_CHECKPOINT_FLOW;
    size = corpus_encode(bytes, 1u, edited, 4u);
    rc |= emit_bytes(dir, "invalid-name_duplicate_exact", bytes, size);
    size = corpus_encode(bytes, 1u, base, 4u);
    rc |= emit_bytes(dir, "invalid-short_header", bytes, CORPUS_HEADER_BYTES - 1u);
    rc |= emit_bytes(dir, "invalid-empty", bytes, 0u);

    EMIT_EDITED("overload-count_17", corpus_put32(bytes + 32, 17u));
    EMIT_EDITED("overload-name_length_64", corpus_put32(corpus_record(bytes, 0u) + 4, 64u));
    EMIT_EDITED("overload-payload_over_limit",
                corpus_put64(corpus_record(bytes, 0u) + 8,
                             (u64)CORE_APP_CHECKPOINT_MAX_FILE_BYTES + 1u));
    size = corpus_encode(bytes, 1u, base, 4u);
    rc |= emit_bytes(dir, "overload-file_over_limit", bytes,
                     CORPUS_HEADER_BYTES + 16u * CORPUS_RECORD_BYTES + 1u);

    if (rc == 0) printf("fuzz_core_app_checkpoint: corpus written to %s\n", dir);
    return rc;
}

enum { k_expect_ok, k_expect_nofind, k_expect_invalid, k_expect_overload, k_expect_none };

static int corpus_expectation(const char *path) {
    const char *base = path;
    for (const char *p = path; *p; ++p) {
        if (*p == '/' || *p == '\\') base = p + 1;
    }
    if (strncmp(base, "ok-", 3u) == 0) return k_expect_ok;
    if (strncmp(base, "nofind-", 7u) == 0) return k_expect_nofind;
    if (strncmp(base, "invalid-", 8u) == 0) return k_expect_invalid;
    if (strncmp(base, "overload-", 9u) == 0) return k_expect_overload;
    return k_expect_none;
}

static int write_default_payloads(const char *directory) {
    return write_payload(directory, "scene_1.bscn", k_scene, sizeof(k_scene)) &&
           write_payload(directory, "flow_1.fg", k_flow, sizeof(k_flow)) &&
           write_payload(directory, "actors_1.sidecar", k_actors, sizeof(k_actors)) &&
           write_payload(directory, "runtime_1.bin", k_runtime, sizeof(k_runtime));
}

static int payloads_unchanged(const char *directory) {
    static const char *const names[] = {"scene_1.bscn", "flow_1.fg", "actors_1.sidecar",
                                        "runtime_1.bin"};
    const unsigned char *const expected[] = {k_scene, k_flow, k_actors, k_runtime};
    const size_t sizes[] = {sizeof(k_scene), sizeof(k_flow), sizeof(k_actors),
                            sizeof(k_runtime)};
    for (size_t i = 0u; i < 4u; ++i) {
        char path[700];
        join_path(path, sizeof(path), directory, names[i]);
        long size = 0;
        unsigned char *bytes = read_all(path, &size);
        int same = bytes && (size_t)size == sizes[i] && memcmp(bytes, expected[i], sizes[i]) == 0;
        free(bytes);
        if (!same) return 0;
    }
    return 1;
}

static const char *expectation_name(int expect) {
    switch (expect) {
        case k_expect_ok: return "OK";
        case k_expect_nofind: return "probe OK, find INVALID";
        case k_expect_invalid: return "INVALID";
        default: return "OVERLOAD";
    }
}

/* For an `ok-` sample the manifest bytes themselves say what find must return. */
static int check_found_record(const char *path, const unsigned char *bytes, long size,
                              const CoreAppCheckpointFile *found, u64 generation) {
    if (size < (long)CORPUS_HEADER_BYTES || generation != corpus_get64(bytes + 24)) {
        fprintf(stderr, "fuzz_core_app_checkpoint: %s: generation %llu does not match\n",
                path, (unsigned long long)generation);
        return 1;
    }
    u32 count = corpus_get32(bytes + 32);
    for (u32 i = 0u; i < count; ++i) {
        const unsigned char *record = bytes + CORPUS_HEADER_BYTES + (size_t)i * CORPUS_RECORD_BYTES;
        if ((long)(CORPUS_HEADER_BYTES + (size_t)(i + 1u) * CORPUS_RECORD_BYTES) > size) break;
        if (corpus_get32(record) != CORE_APP_CHECKPOINT_RUNTIME) continue;
        u32 name_length = corpus_get32(record + 4);
        if (found->kind == CORE_APP_CHECKPOINT_RUNTIME && found->size == corpus_get64(record + 8) &&
            found->hash == corpus_get64(record + 16) && name_length < 64u &&
            strlen(found->name) == name_length &&
            memcmp(found->name, record + 24, name_length) == 0)
            return 0;
        break;
    }
    fprintf(stderr, "fuzz_core_app_checkpoint: %s: find returned a different record\n", path);
    return 1;
}

static int replay_one(const char *directory, const char *path, int counts[4]) {
    int expect = corpus_expectation(path);
    if (expect == k_expect_none) {
        fprintf(stderr, "fuzz_core_app_checkpoint: %s: unknown prefix\n", path);
        return 1;
    }
    long size = 0;
    unsigned char *bytes = read_all(path, &size);
    if (!bytes) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot read %s\n", path);
        return 1;
    }
    if (!write_payload(directory, "manifest.core", bytes, (size_t)size)) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot stage %s\n", path);
        free(bytes);
        return 1;
    }
    BreakRuntimeError probe = core_app_checkpoint_probe(directory);
    CoreAppCheckpointFile found;
    memset(&found, 0, sizeof(found));
    u64 generation = 0u;
    BreakRuntimeError find =
        core_app_checkpoint_find(directory, CORE_APP_CHECKPOINT_RUNTIME, &found, &generation);
    BreakRuntimeError want_probe = BREAK_RUNTIME_OK;
    BreakRuntimeError want_find = BREAK_RUNTIME_OK;
    if (expect == k_expect_nofind) want_find = BREAK_RUNTIME_INVALID;
    if (expect == k_expect_invalid) want_probe = want_find = BREAK_RUNTIME_INVALID;
    if (expect == k_expect_overload) want_probe = want_find = BREAK_RUNTIME_OVERLOAD;
    int rc = 0;
    if (probe != want_probe || find != want_find) {
        fprintf(stderr, "fuzz_core_app_checkpoint: %s: probe=%d find=%d, expected %s\n", path,
                (int)probe, (int)find, expectation_name(expect));
        rc = 1;
    } else if (expect == k_expect_ok) {
        rc = check_found_record(path, bytes, size, &found, generation);
    }
    free(bytes);
    if (rc == 0) counts[expect]++;
    return rc;
}

static int replay_corpus(int count, char **paths) {
    char root[256];
    scratch_root(root, sizeof(root));
    char directory[600];
    join_path(directory, sizeof(directory), root, "replay");
    remove_tree(directory);
    remove_tree(root);
    if (!make_directory(root) || !make_directory(directory) ||
        !write_default_payloads(directory)) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot prepare %s\n", directory);
        remove_tree(directory);
        remove_tree(root);
        return 1;
    }
    int counts[4] = {0, 0, 0, 0};
    int rc = 0;
    for (int i = 0; i < count && rc == 0; ++i) rc = replay_one(directory, paths[i], counts);
    if (rc == 0 && !payloads_unchanged(directory)) {
        fprintf(stderr, "fuzz_core_app_checkpoint: replay modified a payload\n");
        rc = 1;
    }
    remove_tree(directory);
    remove_tree(root);
    if (rc != 0) return 1;
    if (counts[k_expect_ok] == 0 || counts[k_expect_nofind] == 0 ||
        counts[k_expect_invalid] == 0 || counts[k_expect_overload] == 0) {
        fprintf(stderr, "fuzz_core_app_checkpoint: corpus needs ok, nofind, invalid and "
                "overload files (ok=%d nofind=%d invalid=%d overload=%d)\n",
                counts[k_expect_ok], counts[k_expect_nofind], counts[k_expect_invalid],
                counts[k_expect_overload]);
        return 1;
    }
    printf("fuzz_core_app_checkpoint: replayed=%d ok=%d nofind=%d invalid=%d overload=%d\n",
           count, counts[k_expect_ok], counts[k_expect_nofind], counts[k_expect_invalid],
           counts[k_expect_overload]);
    return 0;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--replay") == 0) return replay_corpus(argc - 2, argv + 2);
    if (argc == 3 && strcmp(argv[1], "--emit-corpus") == 0) return emit_corpus(argv[2]);
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 500L;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 500L;

    char root[256];
    char directory[600];
    scratch_root(root, sizeof(root));
    char sentinel[600];
    join_path(directory, sizeof(directory), root, "valid");
    join_path(sentinel, sizeof(sentinel), root, "sentinel");
    remove_tree(directory);
    remove_tree(sentinel);
    remove_tree(root);
    if (!make_directory(root)) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot create %s\n", root);
        return 1;
    }
    if (!make_directory(directory)) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot create %s\n", directory);
        return 1;
    }

    CoreAppCheckpointFile files[4];
    memset(files, 0, sizeof(files));
    if (!write_payload(directory, "scene_1.bscn", k_scene, sizeof(k_scene))) return 1;
    if (!write_payload(directory, "flow_1.fg", k_flow, sizeof(k_flow))) return 1;
    if (!write_payload(directory, "actors_1.sidecar", k_actors, sizeof(k_actors))) return 1;
    if (!write_payload(directory, "runtime_1.bin", k_runtime, sizeof(k_runtime))) return 1;
    for (u32 i = 0u; i < 4u; ++i) {
        u32 index = 0u;
        CoreAppCheckpointKind kind = CORE_APP_CHECKPOINT_SCENE;
        const void *bytes = k_scene;
        usize size = sizeof(k_scene);
        switch (i) {
            case 0: index = 0u; kind = CORE_APP_CHECKPOINT_SCENE; bytes = k_scene; size = sizeof(k_scene); break;
            case 1: index = 1u; kind = CORE_APP_CHECKPOINT_FLOW; bytes = k_flow; size = sizeof(k_flow); break;
            case 2: index = 2u; kind = CORE_APP_CHECKPOINT_ACTORS; bytes = k_actors; size = sizeof(k_actors); break;
            default: index = 3u; kind = CORE_APP_CHECKPOINT_RUNTIME; bytes = k_runtime; size = sizeof(k_runtime); break;
        }
        files[index].kind = kind;
        files[index].size = (u64)size;
        files[index].hash = 0u;
        {
            u64 hash = 14695981039346656037ULL;
            const unsigned char *cursor = (const unsigned char *)bytes;
            for (usize b = 0u; b < size; ++b) {
                hash ^= (u64)cursor[b];
                hash *= 1099511628211ULL;
            }
            files[index].hash = hash;
        }
        if (index == 0u) strcpy(files[index].name, "scene_1.bscn");
        else if (index == 1u) strcpy(files[index].name, "flow_1.fg");
        else if (index == 2u) strcpy(files[index].name, "actors_1.sidecar");
        else strcpy(files[index].name, "runtime_1.bin");
    }
    if (core_app_checkpoint_write_manifest(directory, files, 4u, 1u) != BREAK_RUNTIME_OK) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot write the valid manifest\n");
        return 1;
    }
    if (core_app_checkpoint_probe(directory) != BREAK_RUNTIME_OK) {
        fprintf(stderr, "fuzz_core_app_checkpoint: the valid checkpoint does not probe\n");
        return 1;
    }

    /* A second, untouched checkpoint acts as the sentinel: nothing a mutation
       does to the first may affect it. */
    if (!make_directory(sentinel)) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot create %s\n", sentinel);
        return 1;
    }
    if (!write_payload(sentinel, "scene_1.bscn", k_scene, sizeof(k_scene)) ||
        !write_payload(sentinel, "flow_1.fg", k_flow, sizeof(k_flow)) ||
        !write_payload(sentinel, "actors_1.sidecar", k_actors, sizeof(k_actors)) ||
        !write_payload(sentinel, "runtime_1.bin", k_runtime, sizeof(k_runtime))) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot write the sentinel payloads\n");
        return 1;
    }
    if (core_app_checkpoint_write_manifest(sentinel, files, 4u, 1u) != BREAK_RUNTIME_OK) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot write the sentinel manifest\n");
        return 1;
    }
    char sentinel_path[600];
    join_path(sentinel_path, sizeof(sentinel_path), sentinel, "manifest.core");
    long sentinel_size = 0;
    unsigned char *sentinel_before = read_all(sentinel_path, &sentinel_size);
    if (!sentinel_before) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot read the sentinel manifest\n");
        return 1;
    }

    char manifest_path[600];
    join_path(manifest_path, sizeof(manifest_path), directory, "manifest.core");
    long manifest_size = 0;
    unsigned char *manifest = read_all(manifest_path, &manifest_size);
    if (!manifest) {
        fprintf(stderr, "fuzz_core_app_checkpoint: cannot read the mutated manifest\n");
        free(sentinel_before);
        return 1;
    }

    long accepted = 0;
    long rejected = 0;
    for (long iteration = 0; iteration < iterations; ++iteration) {
        unsigned char *mutated = (unsigned char *)malloc((size_t)manifest_size + 1u);
        if (!mutated) break;
        memcpy(mutated, manifest, (size_t)manifest_size);
        mutate(mutated, manifest_size);
        if (!write_payload(directory, "manifest.core", mutated, (size_t)manifest_size)) {
            free(mutated);
            break;
        }
        free(mutated);

        BreakRuntimeError probe = core_app_checkpoint_probe(directory);
        if (probe == BREAK_RUNTIME_OK) {
            accepted++;
            CoreAppCheckpointFile found;
            u64 generation = 0u;
            (void)core_app_checkpoint_find(directory, CORE_APP_CHECKPOINT_RUNTIME, &found,
                                           &generation);
        } else {
            rejected++;
        }

        /* The sentinel is never written, so it must still read back exactly. */
        long after_size = 0;
        unsigned char *sentinel_after = read_all(sentinel_path, &after_size);
        if (!sentinel_after || after_size != sentinel_size ||
            memcmp(sentinel_before, sentinel_after, (size_t)sentinel_size) != 0) {
            fprintf(stderr, "fuzz_core_app_checkpoint: sentinel changed at iteration %ld\n",
                    iteration);
            free(sentinel_after);
            free(sentinel_before);
            free(manifest);
            return 1;
        }
        free(sentinel_after);
        if (core_app_checkpoint_probe(sentinel) != BREAK_RUNTIME_OK) {
            fprintf(stderr, "fuzz_core_app_checkpoint: sentinel stopped probing at %ld\n",
                    iteration);
            free(sentinel_before);
            free(manifest);
            return 1;
        }
    }

    free(sentinel_before);
    free(manifest);
    remove_tree(directory);
    remove_tree(sentinel);
    remove_tree(root);
    printf("fuzz_core_app_checkpoint: iterations=%ld accepted=%ld rejected=%ld\n",
           iterations, accepted, rejected);
    return 0;
}
