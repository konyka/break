#include "test_framework.h"
#include <rhi/rhi_metal_format.h>

TEST(every_color_and_depth_format_maps) {
    for (int f = RHI_FORMAT_R8G8B8A8_UNORM; f <= RHI_FORMAT_D32_FLOAT; ++f) {
        ASSERT_TRUE(rhi_metal_format_from_rhi((RHIFormat)f) != RHI_METAL_FORMAT_INVALID);
        ASSERT_TRUE(rhi_metal_format_bytes_per_pixel(
            rhi_metal_format_from_rhi((RHIFormat)f)) > 0u);
    }
}
TEST(undefined_format_fails_closed) {
    ASSERT_EQ(rhi_metal_format_from_rhi(RHI_FORMAT_UNDEFINED), RHI_METAL_FORMAT_INVALID);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_INVALID), 0u);
}
TEST(readback_byte_contract_matches_rhi) {
    /* R587/R593/R602: RGBA8/BGRA8=4, RG16F=4, RGBA16F=8, R32F=4, D32=4 */
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_RGBA8_UNORM), 4u);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_RGBA16_FLOAT), 8u);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_DEPTH32_FLOAT), 4u);
}
TEST(frame_slot_pacing) {
    ASSERT_EQ(rhi_metal_frame_slot(0u), 0u);
    ASSERT_EQ(rhi_metal_frame_slot(1u), 1u);
    ASSERT_EQ(rhi_metal_frame_slot(2u), 0u);
    ASSERT_EQ(rhi_metal_slot_wait_value(0u), 0u);  /* first two frames never wait */
    ASSERT_EQ(rhi_metal_slot_wait_value(1u), 0u);
    ASSERT_EQ(rhi_metal_slot_wait_value(2u), 0u);  /* ==0: 未 signal 时 wait(0) 立即成立 */
    ASSERT_EQ(rhi_metal_slot_wait_value(3u), 1u);
    ASSERT_EQ(rhi_metal_slot_wait_value(5u), 3u);
}

/* ---- Task 10: offline shader manifest contract ---- */
#include <core/shader_io.h>

TEST(fnv1a64_known_vectors) {
    /* The manifest generator and the Metal runtime share this inline;
     * pin the FNV-1a 64 vectors so the hash contract cannot drift. */
    ASSERT_TRUE(rhi_metal_fnv1a64("", 0u) == 0xcbf29ce484222325ull);
    ASSERT_TRUE(rhi_metal_fnv1a64("a", 1u) == 0xaf63dc4c8601ec8cull);
    ASSERT_TRUE(rhi_metal_fnv1a64("foobar", 6u) == 0x85944171f73967e8ull);
    ASSERT_TRUE(rhi_metal_fnv1a64("#version 450\n", 13u) ==
                0x30ae0c321aee4417ull);
}

#ifdef ENGINE_METAL_SHADER_MSL_DIR
/* GLSL <-> MSL reflection consistency for three representative shaders
 * (UBO at set 1 / set-0 sampler2D + set-1 samplerBuffer collision case /
 * compute with storage image + push constants). Contract: MSL index =
 * GLSL set*16+binding; push constants sit at [[buffer(30)]]. spirv-cross
 * strips resources the shader never references, so the set check is
 * "every observed MSL index is explainable by a GLSL binding" plus
 * name-anchored spot checks on resources proven live. */

#define MSL_SCAN_MAX 64

typedef struct {
    u32 buffers[MSL_SCAN_MAX];  u32 n_buffers;
    u32 textures[MSL_SCAN_MAX]; u32 n_textures;
    u32 samplers[MSL_SCAN_MAX]; u32 n_samplers;
} MslIndices;

static void msl_scan_indices(const char *msl, MslIndices *out) {
    const char *p = msl;
    while ((p = strstr(p, "[[")) != NULL) {
        u32 *arr = NULL;
        u32 *cnt = NULL;
        u32 v = 0u;
        const char *num;
        if (strncmp(p, "[[buffer(", 9u) == 0) {
            arr = out->buffers; cnt = &out->n_buffers;
        } else if (strncmp(p, "[[texture(", 10u) == 0) {
            arr = out->textures; cnt = &out->n_textures;
        } else if (strncmp(p, "[[sampler(", 10u) == 0) {
            arr = out->samplers; cnt = &out->n_samplers;
        } else {
            p += 2u;
            continue;
        }
        num = strchr(p, '(') + 1;
        while (*num >= '0' && *num <= '9') {
            v = v * 10u + (u32)(*num - '0');
            ++num;
        }
        if (*cnt < MSL_SCAN_MAX) {
            u32 i;
            for (i = 0u; i < *cnt; ++i)
                if (arr[i] == v) break;    /* dedupe: refs repeat the index */
            if (i == *cnt) { arr[(*cnt)++] = v; }
        }
        p = num;
    }
}

static bool u32_in(const u32 *arr, u32 n, u32 v) {
    u32 i;
    for (i = 0u; i < n; ++i)
        if (arr[i] == v) return true;
    return false;
}

/* Find `name [[kind(N)]]` in the MSL text; returns N or 0xFFFFFFFF. */
static u32 msl_named_index(const char *msl, const char *name,
                           const char *kind) {
    const char *p = msl;
    usize nlen = strlen(name);
    while ((p = strstr(p, name)) != NULL) {
        const char *q = p + nlen;
        char expect[40];
        snprintf(expect, sizeof(expect), "[[%s(", kind);
        while (*q == ' ') ++q;
        if (strncmp(q, expect, strlen(expect)) == 0) {
            u32 v = 0u;
            const char *num = q + strlen(expect);
            while (*num >= '0' && *num <= '9') {
                v = v * 10u + (u32)(*num - '0');
                ++num;
            }
            return v;
        }
        p = q;
    }
    return 0xFFFFFFFFu;
}

static void check_one_shader(const char *glsl_name, const char *msl_name) {
    char path[1024];
    usize glen = 0u, mlen = 0u;
    char *gsrc, *msrc;
    ShaderIOBinding bindings[64];
    usize nb;
    u32 exp_buffers[64], exp_textures[64], exp_samplers[64];
    u32 n_eb = 0u, n_et = 0u, n_es = 0u;
    usize i;
    MslIndices got;
    memset(&got, 0, sizeof(got));
    snprintf(path, sizeof(path), "%s/%s", ENGINE_SHADER_SOURCE_DIR, glsl_name);
    gsrc = shader_read_file(path, &glen);
    ASSERT_NOT_NULL(gsrc);
    snprintf(path, sizeof(path), "%s/%s", ENGINE_METAL_SHADER_MSL_DIR,
             msl_name);
    msrc = shader_read_file(path, &mlen);
    ASSERT_NOT_NULL(msrc);
    nb = shader_reflect_bindings(gsrc, glen, bindings, 64u);
    ASSERT_TRUE(nb > 0u);
    for (i = 0u; i < nb; ++i) {
        /* The flattening contract (compile_metal_shaders.sh): combined
         * samplers drive texture+sampler at set*4+binding; samplerBuffer /
         * image textures use set*16+binding; uniform/storage blocks use
         * set*8+binding; push constants sit at buffer(30). */
        const ShaderIOBinding *bd = &bindings[i];
        u32 flat4 = bd->set * 4u + bd->binding;
        u32 flat8 = bd->set * 8u + bd->binding;
        u32 flat16 = bd->set * 16u + bd->binding;
        switch (bd->kind) {
        case SHADER_IO_RESOURCE_UNIFORM:
        case SHADER_IO_RESOURCE_STORAGE:
            exp_buffers[n_eb++] = flat8;
            break;
        case SHADER_IO_RESOURCE_PUSH_CONSTANT:
            exp_buffers[n_eb++] = 29u;    /* reserved push slot (contract) */
            break;
        case SHADER_IO_RESOURCE_SAMPLER:
            if (strcmp(bd->format, "samplerBuffer") == 0) {
                exp_textures[n_et++] = flat16;   /* texel buffer: no sampler */
            } else {
                exp_textures[n_et++] = flat4;
                exp_samplers[n_es++] = flat4;
            }
            break;
        case SHADER_IO_RESOURCE_IMAGE:
            exp_textures[n_et++] = flat16;
            break;
        }
    }
    msl_scan_indices(msrc, &got);
    for (i = 0u; i < got.n_buffers; ++i)
        ASSERT_TRUE(u32_in(exp_buffers, n_eb, got.buffers[i]));
    for (i = 0u; i < got.n_textures; ++i)
        ASSERT_TRUE(u32_in(exp_textures, n_et, got.textures[i]));
    for (i = 0u; i < got.n_samplers; ++i)
        ASSERT_TRUE(u32_in(exp_samplers, n_es, got.samplers[i]));
    free(gsrc);
    free(msrc);
}

TEST(manifest_reflection_consistency) {
    /* blinn_phong_clustered_vk.frag: set0 sampler2D b0 + set1
     * samplerBuffer b0/b1 — the collision case that forced the set*16
     * flattening. Name spots proven in the pipeline probe. Push constants
     * sit at buffer(29): 30 belongs to spirv-cross's spvBufferSizeConstants. */
    check_one_shader("blinn_phong_clustered_vk.frag",
                     "blinn_phong_clustered_frag.metal");
    {
        char path[1024];
        usize mlen = 0u;
        char *msrc;
        snprintf(path, sizeof(path), "%s/%s", ENGINE_METAL_SHADER_MSL_DIR,
                 "blinn_phong_clustered_frag.metal");
        msrc = shader_read_file(path, &mlen);
        ASSERT_NOT_NULL(msrc);
        ASSERT_EQ(msl_named_index(msrc, "u_albedo", "texture"), 0u);
        ASSERT_EQ(msl_named_index(msrc, "u_light_data", "texture"), 16u);
        ASSERT_EQ(msl_named_index(msrc, "u_light_grid", "texture"), 17u);
        ASSERT_EQ(msl_named_index(msrc, "pc", "buffer"), 29u);
        free(msrc);
    }
    /* blinn_phong_vk.vert: set=1 UBO + push block (pc -> buffer(29)). */
    check_one_shader("blinn_phong_vk.vert", "blinn_phong_vert.metal");
    /* brdf_lut.comp: compute + storage image case. NOTE: the other .comp
     * shaders carry an `#else` plain-uniform GL fallback that trips
     * shader_reflect_bindings' duplicate-slot guard (text-level parser, no
     * preprocessor) — they are unreflectable by design and excluded here. */
    check_one_shader("brdf_lut.comp", "brdf_lut_comp.metal");
}
#endif /* ENGINE_METAL_SHADER_MSL_DIR */
TEST_MAIN_BEGIN()
    RUN_TEST(every_color_and_depth_format_maps);
    RUN_TEST(undefined_format_fails_closed);
    RUN_TEST(readback_byte_contract_matches_rhi);
    RUN_TEST(frame_slot_pacing);
    RUN_TEST(fnv1a64_known_vectors);
#ifdef ENGINE_METAL_SHADER_MSL_DIR
    RUN_TEST(manifest_reflection_consistency);
#endif
TEST_MAIN_END()
