/* Mutation fuzzer for the editor scene load + re-save path.
 *
 * Builds a game-style BSCN (entities, components, SCENE_NODES, RESOURCES),
 * then repeatedly mutates its bytes and feeds them through
 * break_editor_doc_load_bytes; every accepted file is re-saved through
 * break_editor_doc_save (which splices the kept game chunks back) and the
 * result is loaded again. Loaders may reject anything; they must not crash,
 * read out of bounds or leak, and a re-save of an accepted file must load.
 * Usage (ASan/UBSan tree): ./fuzz_editor_scene [iterations] [seed] */

#include <editor/editor_doc.h>
#include <editor/editor_scene.h>

#include <asset/asset.h>
#include <ecs/ecs.h>
#include <scene/scene_serial.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static unsigned long long g_rng = 0x9e3779b97f4a7c15ull;
static unsigned rnd(void) {
    g_rng = g_rng * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(g_rng >> 33);
}

static unsigned char *read_all(const char *path, size_t *n) {
    FILE *f = fopen(path, "rb");
    long sz;
    unsigned char *b;
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0 || (sz = ftell(f)) <= 0 ||
        fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return NULL;
    }
    b = malloc((size_t)sz);
    if (b && fread(b, 1, (size_t)sz, f) != (size_t)sz) {
        free(b);
        b = NULL;
    }
    fclose(f);
    *n = (size_t)sz;
    return b;
}

static int build_seed(const char *path) {
    World *w = world_create();
    Scene s;
    SerializeOptions o;
    int ok;
    if (!w) return 0;
    world_register_component(w, 64u, 36u);
    for (int i = 0; i < 3; i++) {
        Entity e = world_create_entity(w);
        float *t = world_add_component(w, e, 64u);
        if (t) {
            for (int k = 0; k < 9; k++) t[k] = (float)(i * 10 + k);
        }
    }
    memset(&s, 0, sizeof(s));
    s.mesh_count = 1;
    s.meshes = calloc(1, sizeof(Mesh));
    s.node_count = 2;
    s.nodes = calloc(2, sizeof(SceneNode));
    if (!s.meshes || !s.nodes) {
        free(s.meshes);
        free(s.nodes);
        world_destroy(w);
        return 0;
    }
    s.meshes[0].index_count = 6;
    s.meshes[0].vertex_count = 4;
    for (u32 i = 0; i < 2; i++) {
        s.nodes[i].local_transform = mat4_identity();
        s.nodes[i].world_transform = mat4_identity();
        s.nodes[i].parent_index = i == 0 ? UINT32_MAX : 0u;
    }
    memset(&o, 0, sizeof(o));
    o.include_resources = true;
    ok = scene_save_binary(w, &s, path, &o);
    free(s.meshes);
    free(s.nodes);
    world_destroy(w);
    return ok;
}

int main(int argc, char **argv) {
    char seed_path[256], out_path[256], sidecar[300];
    unsigned long iters = argc > 1 ? strtoul(argv[1], NULL, 10) : 5000ul;
    size_t seed_n = 0;
    unsigned char *seed;
    unsigned long accepted = 0, resaved = 0;
    if (argc > 2) g_rng ^= strtoull(argv[2], NULL, 10);
    snprintf(seed_path, sizeof(seed_path), "/tmp/fuzz_editor_scene_%d.bscn",
             (int)getpid());
    snprintf(out_path, sizeof(out_path), "/tmp/fuzz_editor_scene_%d_out.bscn",
             (int)getpid());
    snprintf(sidecar, sizeof(sidecar), "%s%s", out_path,
             BREAK_EDITOR_SIDECAR_SUFFIX);
    if (!build_seed(seed_path) || !(seed = read_all(seed_path, &seed_n))) {
        fprintf(stderr, "fuzz_editor_scene: seed build failed\n");
        return 2;
    }
    for (unsigned long it = 0; it < iters; it++) {
        size_t n = seed_n;
        unsigned char *buf = malloc(n);
        unsigned muts = 1u + rnd() % 8u;
        BreakEditorDoc *doc;
        if (!buf) return 2;
        memcpy(buf, seed, n);
        for (unsigned m = 0; m < muts; m++) {
            size_t at = rnd() % n;
            switch (rnd() % 4u) {
            case 0: buf[at] ^= (unsigned char)(1u << (rnd() % 8u)); break;
            case 1: buf[at] = (unsigned char)rnd(); break;
            case 2: { /* 32-bit field smash: offsets, sizes, counts */
                unsigned v = rnd() % 3u == 0 ? 0xFFFFFFFFu : rnd();
                if (at + 4u <= n) memcpy(buf + at, &v, 4u);
                break;
            }
            default: if (n > 16u && rnd() % 4u == 0) n -= rnd() % (n / 4u);
            }
        }
        doc = break_editor_doc_create();
        if (!doc) return 2;
        if (break_editor_doc_load_bytes(doc, out_path, buf, n)) {
            accepted++;
            if (break_editor_doc_save(doc, out_path)) {
                BreakEditorDoc *again = break_editor_doc_create();
                resaved++;
                if (!again || !break_editor_doc_load(again, out_path)) {
                    fprintf(stderr,
                            "fuzz_editor_scene: iteration %lu: an accepted "
                            "file re-saved into an unloadable one\n", it);
                    return 1;
                }
                break_editor_doc_destroy(again);
            }
        }
        break_editor_doc_destroy(doc);
        free(buf);
    }
    printf("fuzz_editor_scene: %lu iterations, %lu accepted, %lu re-saved\n",
           iters, accepted, resaved);
    free(seed);
    remove(seed_path);
    remove(out_path);
    remove(sidecar);
    return 0;
}
