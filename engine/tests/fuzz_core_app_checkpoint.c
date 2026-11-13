/* Mutation fuzzer for the checkpoint reader.
 *
 * Builds a valid checkpoint through the real writer, then repeatedly mutates
 * the manifest and payload bytes and feeds them back through the real
 * manifest reader and per-kind payload lookup. Any classified failure is
 * acceptable; a crash, out-of-bounds read, leak, or a mutation that makes a
 * previously valid payload report a different kind is not. A sentinel
 * checkpoint that stays valid throughout must remain readable, so a rejected
 * mutation never corrupts unrelated state. */

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

int main(int argc, char **argv) {
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

    static const unsigned char scene[96] = {0x42u, 0x53u, 0x43u, 0x4Eu};
    static const unsigned char flow[64] = {0x42u, 0x46u, 0x4Cu, 0x57u};
    static const unsigned char actors[48] = {'2', ' ', 'U', 's', 'e', 'r', '\n'};
    static const unsigned char runtime[72] = {0x43u, 0x4Fu, 0x52u, 0x45u};
    CoreAppCheckpointFile files[4];
    memset(files, 0, sizeof(files));
    if (!write_payload(directory, "scene_1.bscn", scene, sizeof(scene))) return 1;
    if (!write_payload(directory, "flow_1.fg", flow, sizeof(flow))) return 1;
    if (!write_payload(directory, "actors_1.sidecar", actors, sizeof(actors))) return 1;
    if (!write_payload(directory, "runtime_1.bin", runtime, sizeof(runtime))) return 1;
    for (u32 i = 0u; i < 4u; ++i) {
        u32 index = 0u;
        CoreAppCheckpointKind kind = CORE_APP_CHECKPOINT_SCENE;
        const void *bytes = scene;
        usize size = sizeof(scene);
        switch (i) {
            case 0: index = 0u; kind = CORE_APP_CHECKPOINT_SCENE; bytes = scene; size = sizeof(scene); break;
            case 1: index = 1u; kind = CORE_APP_CHECKPOINT_FLOW; bytes = flow; size = sizeof(flow); break;
            case 2: index = 2u; kind = CORE_APP_CHECKPOINT_ACTORS; bytes = actors; size = sizeof(actors); break;
            default: index = 3u; kind = CORE_APP_CHECKPOINT_RUNTIME; bytes = runtime; size = sizeof(runtime); break;
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
    if (!write_payload(sentinel, "scene_1.bscn", scene, sizeof(scene)) ||
        !write_payload(sentinel, "flow_1.fg", flow, sizeof(flow)) ||
        !write_payload(sentinel, "actors_1.sidecar", actors, sizeof(actors)) ||
        !write_payload(sentinel, "runtime_1.bin", runtime, sizeof(runtime))) {
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
    char cleanup[600];
    join_path(cleanup, sizeof(cleanup), directory, "manifest.core");
    (void)remove(cleanup);
    printf("fuzz_core_app_checkpoint: iterations=%ld accepted=%ld rejected=%ld\n",
           iterations, accepted, rejected);
    return 0;
}
