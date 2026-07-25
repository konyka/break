/* Mutation fuzzer for the glTF loader.
 *
 * R390 added the missing cgltf_validate call; this exercises that fix at scale
 * and explores what validate still permits. Mutates both a GLB container (so the
 * binary chunk header is fuzzed too) and a JSON glTF, then feeds each through
 * asset_load_gltf under ASan+UBSan. The loader may reject anything; it must not
 * crash, read or write out of bounds, or leak.
 *
 * Every attribute loop runs before the first rhi_buffer_create, so stub RHI
 * symbols and dev = NULL reach all the interesting code.
 */

#include <asset/asset.h>
#include <asset/async_loader.h>
#include <core/log.h>
#include <rhi/rhi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- RHI / async stubs (link-only) ---- */

RHIDevice *g_current_device = NULL;
static RHIBuffer  s_null_buffer  = {0};
static RHITexture s_null_texture = {0};

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc; return s_null_buffer;
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    (void)dev; (void)buf; (void)data; (void)size;
}
u32 rhi_frame_index(RHIDevice *dev) { (void)dev; return 0u; }
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc; return s_null_texture;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) { (void)dev; (void)tex; }
u64 async_loader_request(const char *path, AsyncLoadCallback cb, void *user) {
    (void)path; (void)cb; (void)user; return 0u;
}
u64 async_loader_request_texture(const char *path, AsyncLoadCallback cb, void *user, i32 pri) {
    (void)path; (void)cb; (void)user; (void)pri; return 0u;
}

/* ---- fuzzer ---- */

static unsigned long rng_state = 0x5EED1234u;
static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* A JSON seed with a skin, animation and indexed primitive, so the skinning and
 * animation paths are reachable — they are the parts cgltf_validate says least
 * about. The buffer holds 3 VEC3 positions plus room for joints/weights. */
static const char *JSON_SEED =
"{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
"\"scenes\":[{\"nodes\":[0,1]}],"
"\"nodes\":[{\"mesh\":0,\"skin\":0},{\"name\":\"joint0\"}],"
"\"skins\":[{\"joints\":[1],\"inverseBindMatrices\":4}],"
"\"animations\":[{\"channels\":[{\"sampler\":0,\"target\":{\"node\":1,\"path\":\"translation\"}}],"
"\"samplers\":[{\"input\":5,\"output\":6,\"interpolation\":\"LINEAR\"}]}],"
"\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0,\"NORMAL\":1,"
"\"TEXCOORD_0\":2,\"JOINTS_0\":7,\"WEIGHTS_0\":8},\"indices\":3}]}],"
"\"accessors\":["
 "{\"bufferView\":0,\"componentType\":5126,\"count\":3,\"type\":\"VEC3\"},"
 "{\"bufferView\":0,\"componentType\":5126,\"count\":3,\"type\":\"VEC3\"},"
 "{\"bufferView\":1,\"componentType\":5126,\"count\":3,\"type\":\"VEC2\"},"
 "{\"bufferView\":2,\"componentType\":5123,\"count\":3,\"type\":\"SCALAR\"},"
 "{\"bufferView\":3,\"componentType\":5126,\"count\":1,\"type\":\"MAT4\"},"
 "{\"bufferView\":4,\"componentType\":5126,\"count\":2,\"type\":\"SCALAR\"},"
 "{\"bufferView\":5,\"componentType\":5126,\"count\":2,\"type\":\"VEC3\"},"
 "{\"bufferView\":6,\"componentType\":5121,\"count\":3,\"type\":\"VEC4\"},"
 "{\"bufferView\":7,\"componentType\":5126,\"count\":3,\"type\":\"VEC4\"}],"
"\"bufferViews\":["
 "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36},"
 "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":24},"
 "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":6},"
 "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":64},"
 "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":8},"
 "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":24},"
 "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":12},"
 "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":48}],"
"\"buffers\":[{\"byteLength\":128,\"uri\":\"data:application/octet-stream;base64,"
"AAAAAAAAAAAAAAAAAACAPwAAAAAAAAAAAAAAAAAAgD8AAAAAAAAAAAAAgD8AAIA/AAAAAAAAgD8A"
"AIA/AACAPwAAAAAAAAAAAAAAAAAAgD8AAAAAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAACAPwAA"
"AAAAAAAAAAAAAAAAgD8=\"}]}";

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

/* Boundary values for the u32 fields in the GLB header/chunk table. */
static const unsigned interesting_u32[] = {
    0u, 1u, 2u, 12u, 20u,
    0x7FFFFFFFu, 0x80000000u,
    0xFFFFFFFEu, 0xFFFFFFFFu,
};

static void mutate_bin(unsigned char *buf, long n, unsigned nmut) {
    for (unsigned m = 0; m < nmut; m++) {
        /* GLB is a 12-byte header plus 8-byte chunk headers; word-level writes
         * into the first 64 bytes are what reach the container parser. */
        if (n > 64 && rnd() % 2 == 0) {
            unsigned v = interesting_u32[rnd() % (sizeof(interesting_u32) / sizeof(interesting_u32[0]))];
            memcpy(buf + (size_t)(rnd() % 16u) * 4u, &v, sizeof(v));
            continue;
        }
        long pos = (long)(rnd() % (unsigned)n);
        switch (rnd() % 4) {
        case 0: buf[pos] = (unsigned char)(rnd() & 0xFF); break;
        case 1: buf[pos] ^= (unsigned char)(1u << (rnd() % 8)); break;
        case 2: buf[pos] = 0xFF; break;
        default: buf[pos] = 0x00; break;
        }
    }
}

/* For JSON, prefer digit edits: they retain parseable structure while driving the
 * counts, offsets and indices that the loader's bounds depend on. Random bytes
 * mostly produce JSON syntax errors that never reach the read paths. */
static void mutate_json(char *s, long n, unsigned nmut) {
    static const char *digits = "0123456789";
    for (unsigned m = 0; m < nmut; m++) {
        if (rnd() % 4 == 0) {
            long pos = (long)(rnd() % (unsigned)n);
            s[pos] = (char)(rnd() & 0x7F);
            continue;
        }
        /* Walk to a random digit and perturb it. */
        long start = (long)(rnd() % (unsigned)n);
        for (long k = 0; k < n; k++) {
            long pos = (start + k) % n;
            if (s[pos] >= '0' && s[pos] <= '9') {
                switch (rnd() % 3) {
                case 0: s[pos] = digits[rnd() % 10]; break;
                case 1: s[pos] = '9'; break;
                default: s[pos] = '0'; break;
                }
                break;
            }
        }
    }
}

static void load_once(const char *path) {
    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));
    if (asset_load_gltf(&ctx, path, &scene))
        asset_scene_free(&ctx, &scene);
    else
        asset_scene_free(&ctx, &scene); /* must be safe on the failure path too */
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 5000;
    if (argc > 2) rng_state = (unsigned long)atoi(argv[2]);
    const char *glb_seed = argc > 3 ? argv[3] : "engine/assets/test.glb";
    log_set_level(LOG_FATAL);

    const char *mut_glb = "/tmp/fuzz_mut.glb";
    const char *mut_json = "/tmp/fuzz_mut.gltf";

    long glen = 0;
    unsigned char *gbase = read_file(glb_seed, &glen);
    if (!gbase)
        fprintf(stderr, "note: GLB seed '%s' unavailable, JSON only\n", glb_seed);

    long jlen = (long)strlen(JSON_SEED);
    char *jbase = (char *)malloc((size_t)jlen + 1);
    if (!jbase) return 2;
    memcpy(jbase, JSON_SEED, (size_t)jlen + 1);

    /* The unmutated JSON seed must load, else the fuzzer only sees reject paths. */
    if (!write_file(mut_json, (const unsigned char *)jbase, jlen)) return 2;
    {
        AssetCtx ctx;
        asset_ctx_init(&ctx, NULL);
        ctx.vfs = NULL;
        Scene scene;
        memset(&scene, 0, sizeof(scene));
        if (!asset_load_gltf(&ctx, mut_json, &scene)) {
            fprintf(stderr, "JSON seed rejected — fuzzer would only cover reject paths\n");
            return 2;
        }
        printf("seed: %u nodes, %u meshes, %u skinned, %u joints, %u anims\n",
               scene.node_count, scene.mesh_count, scene.skinned_mesh_count,
               scene.joint_count, scene.anim_clip_count);
        asset_scene_free(&ctx, &scene);
    }

    unsigned char *gscratch = gbase ? (unsigned char *)malloc((size_t)glen) : NULL;
    char *jscratch = (char *)malloc((size_t)jlen + 1);
    if (!jscratch) return 2;

    for (unsigned it = 0; it < iters; it++) {
        if (gscratch) {
            memcpy(gscratch, gbase, (size_t)glen);
            mutate_bin(gscratch, glen, 1 + rnd() % 6);
            if (write_file(mut_glb, gscratch, glen)) load_once(mut_glb);
        }
        memcpy(jscratch, jbase, (size_t)jlen + 1);
        mutate_json(jscratch, jlen, 1 + rnd() % 6);
        if (write_file(mut_json, (const unsigned char *)jscratch, jlen)) load_once(mut_json);
    }

    printf("fuzz done: %u iters (glb %s)\n", iters, gbase ? "yes" : "skipped");
    free(gbase); free(gscratch); free(jbase); free(jscratch);
    remove(mut_glb); remove(mut_json);
    return 0;
}
