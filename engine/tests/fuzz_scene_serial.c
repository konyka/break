/* Mutation fuzzer for the BSCN / JSON scene loaders.
 *
 * Builds a valid scene, saves it, then repeatedly applies random byte mutations
 * and feeds the result back through scene_load_binary / scene_load_json under
 * ASan+UBSan. Loaders are allowed to reject anything; they are not allowed to
 * crash, read out of bounds, or leak. */

#include <ecs/ecs.h>
#include <scene/scene_serial.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { COMP_A = 1, COMP_B = 2 };
typedef struct { float x, y, z; } CompA;
typedef struct { unsigned id; float w; } CompB;

static unsigned long rng_state = 0x12345678u;
static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

static unsigned char *read_file(const char *p, long *out_len) {
    FILE *f = fopen(p, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long n = ftell(f);
    if (n <= 0 || fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    unsigned char *b = (unsigned char *)malloc((size_t)n);
    if (!b) { fclose(f); return NULL; }
    if (fread(b, 1, (size_t)n, f) != (size_t)n) { free(b); fclose(f); return NULL; }
    fclose(f);
    *out_len = n;
    return b;
}

static int write_file(const char *p, const unsigned char *b, long n) {
    FILE *f = fopen(p, "wb");
    if (!f) return 0;
    int ok = fwrite(b, 1, (size_t)n, f) == (size_t)n;
    fclose(f);
    return ok;
}

static void register_components(World *w) {
    world_register_component(w, COMP_A, sizeof(CompA));
    world_register_component(w, COMP_B, sizeof(CompB));
}

static void make_seed_scene(World *w, Scene *s) {
    memset(s, 0, sizeof(*s));
    for (int i = 0; i < 6; i++) {
        Entity e = world_create_entity(w);
        CompA *a = (CompA *)world_add_component(w, e, COMP_A);
        if (a) { a->x = (float)i; a->y = 1.0f; a->z = 2.0f; }
        if (i % 2) {
            CompB *b = (CompB *)world_add_component(w, e, COMP_B);
            if (b) { b->id = (unsigned)i; b->w = 0.5f; }
        }
    }
    s->node_count = 4;
    s->nodes = (SceneNode *)calloc(4, sizeof(SceneNode));
    for (unsigned i = 0; i < 4; i++) {
        s->nodes[i].parent_index = i ? i - 1u : 0xFFFFFFFFu;
        s->nodes[i].mesh_index = i;
        s->nodes[i].has_mesh = true;
    }
    s->mesh_count = 2;
    s->meshes = (Mesh *)calloc(2, sizeof(Mesh));
    s->material_count = 2;
    s->materials = (Material *)calloc(2, sizeof(Material));
}

/* Random byte flips / splices, biased toward the header+table region where
 * offsets and counts live. */
static void mutate(unsigned char *buf, long n, unsigned nmut) {
    for (unsigned m = 0; m < nmut; m++) {
        long pos;
        if (rnd() % 3 == 0 && n > 64) pos = (long)(rnd() % 64);
        else pos = (long)(rnd() % (unsigned)n);
        switch (rnd() % 4) {
        case 0: buf[pos] = (unsigned char)(rnd() & 0xFF); break;
        case 1: buf[pos] ^= (unsigned char)(1u << (rnd() % 8)); break;
        case 2: buf[pos] = 0xFF; break;
        default: buf[pos] = 0x00; break;
        }
    }
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 20000;
    if (argc > 2) rng_state = (unsigned long)atoi(argv[2]);
    log_set_level(LOG_FATAL);

    const char *bscn = "/tmp/fuzz_seed.bscn";
    const char *json = "/tmp/fuzz_seed.json";
    const char *mut_b = "/tmp/fuzz_mut.bscn";
    const char *mut_j = "/tmp/fuzz_mut.json";

    /* Seed corpus. */
    {
        World *w = world_create();
        register_components(w);
        Scene s;
        make_seed_scene(w, &s);
        SerializeOptions opts = { .include_resources = true, .pretty_json = false };
        if (!scene_save_binary(w, &s, bscn, &opts)) { fprintf(stderr, "seed bscn failed\n"); return 2; }
        if (!scene_save_json(w, &s, json, &opts))   { fprintf(stderr, "seed json failed\n"); return 2; }
        free(s.meshes); free(s.materials);
        scene_serial_free(&s); /* owns nodes + resources */
        world_destroy(w);
    }

    long blen = 0, jlen = 0;
    unsigned char *bbase = read_file(bscn, &blen);
    unsigned char *jbase = read_file(json, &jlen);
    if (!bbase || !jbase) { fprintf(stderr, "read seed failed\n"); return 2; }

    unsigned char *scratch = (unsigned char *)malloc((size_t)(blen > jlen ? blen : jlen));
    unsigned b_ok = 0, j_ok = 0;

    for (unsigned it = 0; it < iters; it++) {
        /* --- BSCN --- */
        memcpy(scratch, bbase, (size_t)blen);
        mutate(scratch, blen, 1 + rnd() % 8);
        if (write_file(mut_b, scratch, blen)) {
            World *w = world_create();
            register_components(w);
            Scene s; memset(&s, 0, sizeof(s));
            if (scene_load_binary(w, &s, mut_b)) b_ok++;
            scene_serial_free(&s);
            world_destroy(w);
            (void)scene_probe_binary(mut_b);
        }

        /* --- JSON --- */
        memcpy(scratch, jbase, (size_t)jlen);
        mutate(scratch, jlen, 1 + rnd() % 8);
        if (write_file(mut_j, scratch, jlen)) {
            World *w = world_create();
            register_components(w);
            Scene s; memset(&s, 0, sizeof(s));
            if (scene_load_json(w, &s, mut_j)) j_ok++;
            scene_serial_free(&s);
            world_destroy(w);
        }
    }

    printf("fuzz done: %u iters, bscn accepted %u, json accepted %u\n",
           iters, b_ok, j_ok);
    free(bbase); free(jbase); free(scratch);
    remove(bscn); remove(json); remove(mut_b); remove(mut_j);
    return 0;
}
