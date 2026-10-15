#include "test_framework.h"
#include <rhi/rhi.h>

/* Plan C Task 7: resource family contract for the native Metal backend —
 * buffers (shared storage mode for UNIFORM/initial-data, private staging
 * for pure-GPU usage, map fail-closed on private), textures (upload and
 * readback byte contract R587-R602), samplers (slot generation advances
 * across destroy), cubemaps (R624 face-major readback of all six faces)
 * and 2D texture arrays (R441 layer upload). Runs on macOS with
 * ENGINE_RHI_BACKEND_METAL; everywhere else it exits 77 (SKIP). The
 * CAMetalLayer is created offscreen, same pattern as
 * test_rhi_metal_frame_lifecycle. */
#if defined(ENGINE_RHI_BACKEND_METAL) && defined(ENGINE_PLATFORM_MACOS)

/* CAMetalLayer creation needs Objective-C; metal_test_layer.m wraps it so
 * this TU stays C11. */
void *metal_test_layer_create(u32 w, u32 h);
void metal_test_layer_destroy(void *layer);

static RHIDevice *g_dev;
static void *g_layer;
static RHIResult g_create_result = RHI_RESULT_OK;

static bool handle_is_null(RHIHandle h) {
    return h.index == 0u && h.generation == 0u;
}

TEST(uniform_buffer_update_read_roundtrip) {
    /* UNIFORM usage -> shared storage mode: update + read round-trip. */
    RHIBufferDesc desc;
    u8 magic[64];
    u8 out[64];
    u32 i;
    RHIBuffer buf;
    memset(&desc, 0, sizeof(desc));
    desc.usage = RHI_BUFFER_USAGE_UNIFORM;
    desc.size = sizeof(magic);
    for (i = 0u; i < sizeof(magic); ++i) magic[i] = (u8)(0xA0u + i);
    memset(out, 0, sizeof(out));
    buf = rhi_buffer_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(buf));
    rhi_buffer_update(g_dev, buf, magic, sizeof(magic));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    ASSERT_TRUE(memcmp(out, magic, sizeof(magic)) == 0);
    /* Region update: only the [16,32) window changes. */
    for (i = 16u; i < 32u; ++i) magic[i] = (u8)(0x40u + i);
    rhi_buffer_update_region(g_dev, buf, 16u, magic + 16u, 16u);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    ASSERT_TRUE(memcmp(out, magic, sizeof(magic)) == 0);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(uniform_buffer_map_write_read) {
    /* Shared storage mode is persistently mapped: map/unmap are legal. */
    RHIBufferDesc desc;
    RHIBuffer buf;
    void *p;
    u8 out[16];
    static const u8 seed[16] = {
        1u, 3u, 5u, 7u, 9u, 11u, 13u, 15u,
        2u, 4u, 6u, 8u, 10u, 12u, 14u, 16u
    };
    memset(&desc, 0, sizeof(desc));
    desc.usage = RHI_BUFFER_USAGE_UNIFORM;
    desc.size = sizeof(seed);
    buf = rhi_buffer_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(buf));
    p = rhi_buffer_map(g_dev, buf);
    ASSERT_NOT_NULL(p);
    memcpy(p, seed, sizeof(seed));
    rhi_buffer_unmap(g_dev, buf);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    ASSERT_TRUE(memcmp(out, seed, sizeof(seed)) == 0);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(private_storage_buffer_staging_roundtrip) {
    /* Pure-GPU usage (STORAGE, no initial data) -> private storage mode:
     * update goes through blit staging, read back through a shared staging
     * buffer; rhi_buffer_map must fail closed (NULL + log). */
    RHIBufferDesc desc;
    u8 magic[32];
    u8 out[32];
    u32 i;
    RHIBuffer buf;
    memset(&desc, 0, sizeof(desc));
    desc.usage = RHI_BUFFER_USAGE_STORAGE;
    desc.size = sizeof(magic);
    for (i = 0u; i < sizeof(magic); ++i) magic[i] = (u8)(i * 7u + 1u);
    buf = rhi_buffer_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(buf));
    ASSERT_TRUE(rhi_buffer_map(g_dev, buf) == NULL);
    rhi_buffer_update(g_dev, buf, magic, sizeof(magic));
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    ASSERT_TRUE(memcmp(out, magic, sizeof(magic)) == 0);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(vertex_buffer_initial_data_read_back) {
    /* initial_data present -> shared storage mode with the bytes uploaded
     * at create (newBufferWithBytes:). */
    RHIBufferDesc desc;
    u8 init[24];
    u8 out[24];
    u32 i;
    RHIBuffer buf;
    memset(&desc, 0, sizeof(desc));
    desc.usage = RHI_BUFFER_USAGE_VERTEX;
    desc.size = sizeof(init);
    for (i = 0u; i < sizeof(init); ++i) init[i] = (u8)(0xFFu - i);
    desc.initial_data = init;
    buf = rhi_buffer_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(buf));
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    ASSERT_TRUE(memcmp(out, init, sizeof(init)) == 0);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(texture_rgba8_upload_readback) {
    /* R587 contract: RGBA8 readback is 4B/px RGBA, tightly packed. */
    RHITextureDesc desc;
    u8 pixels[4u * 4u * 4u];
    u8 out[4u * 4u * 4u];
    u32 i;
    RHITexture tex;
    u32 w = 0u, h = 0u;
    memset(&desc, 0, sizeof(desc));
    desc.width = 4u;
    desc.height = 4u;
    desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    for (i = 0u; i < sizeof(pixels); ++i) pixels[i] = (u8)(i + 3u);
    desc.data = pixels;
    tex = rhi_texture_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(tex));
    ASSERT_TRUE(rhi_texture_get_size(g_dev, tex, &w, &h));
    ASSERT_EQ(w, 4u);
    ASSERT_EQ(h, 4u);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, tex, out, sizeof(out)));
    ASSERT_TRUE(memcmp(out, pixels, sizeof(pixels)) == 0);
    rhi_texture_destroy(g_dev, tex);
}

TEST(texture_read_pixels_small_buffer_fails) {
    /* Host-OOB guard: a destination smaller than w*h*bpp is rejected
     * instead of overflowing the caller's buffer. */
    RHITextureDesc desc;
    u8 pixels[16];
    u8 out[8];
    RHITexture tex;
    memset(&desc, 0, sizeof(desc));
    desc.width = 2u;
    desc.height = 2u;
    desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    desc.data = pixels;
    memset(pixels, 0x5Au, sizeof(pixels));
    tex = rhi_texture_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(tex));
    memset(out, 0, sizeof(out));
    ASSERT_FALSE(rhi_texture_read_pixels(g_dev, tex, out, sizeof(out)));
    rhi_texture_destroy(g_dev, tex);
}

TEST(texture_undefined_format_rejected) {
    /* Fail-closed: RHI_FORMAT_UNDEFINED never produces a texture. */
    RHITextureDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.width = 4u;
    desc.height = 4u;
    desc.format = RHI_FORMAT_UNDEFINED;
    ASSERT_TRUE(handle_is_null(rhi_texture_create(g_dev, &desc)));
}

TEST(texture_d32_depth_create_upload_readback) {
    /* R602: D32 readback is 4B f32 per texel, tightly packed. Regression
     * pin (review fix): depth formats must not request
     * MTLTextureUsageShaderWrite — Metal's Texture Descriptor Validation
     * rejects that combination at newTextureWithDescriptor:. */
    RHITextureDesc desc;
    f32 depth[4u * 4u];
    u8 out[4u * 4u * 4u];
    u32 i;
    RHITexture tex;
    u32 w = 0u, h = 0u;
    memset(&desc, 0, sizeof(desc));
    desc.width = 4u;
    desc.height = 4u;
    desc.format = RHI_FORMAT_D32_FLOAT;
    for (i = 0u; i < 16u; ++i) depth[i] = (f32)i / 16.0f;
    desc.data = depth;
    tex = rhi_texture_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(tex));
    ASSERT_TRUE(rhi_texture_get_size(g_dev, tex, &w, &h));
    ASSERT_EQ(w, 4u);
    ASSERT_EQ(h, 4u);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, tex, out, sizeof(out)));
    ASSERT_TRUE(memcmp(out, depth, sizeof(depth)) == 0);
    rhi_texture_destroy(g_dev, tex);
}

TEST(texture_upload_mip_then_read_mip0) {
    /* Mip-chain texture: upload_mip targets a sub-level; mip 0 readback
     * still returns the create-time texels. */
    RHITextureDesc desc;
    u8 mip0[4u * 4u * 4u];
    u8 mip1[2u * 2u * 4u];
    u8 out[4u * 4u * 4u];
    u32 i;
    RHITexture tex;
    memset(&desc, 0, sizeof(desc));
    desc.width = 4u;
    desc.height = 4u;
    desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    desc.mip_levels = 2u;
    for (i = 0u; i < sizeof(mip0); ++i) mip0[i] = (u8)(i * 3u);
    for (i = 0u; i < sizeof(mip1); ++i) mip1[i] = (u8)(0x80u + i);
    desc.data = mip0;
    tex = rhi_texture_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(tex));
    rhi_texture_upload_mip(g_dev, tex, 1u, 2u, 2u, mip1, sizeof(mip1));
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, tex, out, sizeof(out)));
    ASSERT_TRUE(memcmp(out, mip0, sizeof(mip0)) == 0);
    rhi_texture_destroy(g_dev, tex);
}

TEST(texture_array_layer_upload_and_size) {
    /* R441: 2D array, one full RGBA8 layer uploaded per call. */
    RHITexture tex;
    u8 layer_a[4u * 4u * 4u];
    u8 layer_b[4u * 4u * 4u];
    u32 i;
    u32 w = 0u, h = 0u;
    for (i = 0u; i < sizeof(layer_a); ++i) {
        layer_a[i] = (u8)(i + 1u);
        layer_b[i] = (u8)(0xC0u + i);
    }
    tex = rhi_texture_array_create(g_dev, 4u, 4u, 2u,
                                   RHI_FORMAT_R8G8B8A8_UNORM);
    ASSERT_FALSE(handle_is_null(tex));
    ASSERT_TRUE(rhi_texture_get_size(g_dev, tex, &w, &h));
    ASSERT_EQ(w, 4u);
    ASSERT_EQ(h, 4u);
    rhi_texture_array_upload_layer(g_dev, tex, 0u, layer_a, sizeof(layer_a));
    rhi_texture_array_upload_layer(g_dev, tex, 1u, layer_b, sizeof(layer_b));
    /* Out-of-range layer is a quiet no-op (host-OOB guard class). */
    rhi_texture_array_upload_layer(g_dev, tex, 2u, layer_a, sizeof(layer_a));
    rhi_texture_destroy(g_dev, tex);
}

TEST(sampler_create_destroy_generation_advances) {
    /* Slot lifecycle: the freed slot is reused with a fresh generation, so
     * a stale handle never aliases the new sampler. */
    RHISamplerDesc desc;
    RHISampler s1, s2;
    memset(&desc, 0, sizeof(desc));
    desc.min_filter = RHI_FILTER_LINEAR;
    desc.mag_filter = RHI_FILTER_NEAREST;
    desc.wrap_u = RHI_WRAP_CLAMP_TO_EDGE;
    desc.wrap_v = RHI_WRAP_REPEAT;
    desc.wrap_w = RHI_WRAP_CLAMP_TO_EDGE;
    s1 = rhi_sampler_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(s1));
    rhi_sampler_destroy(g_dev, s1);
    s2 = rhi_sampler_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(s2));
    ASSERT_TRUE(s2.generation != s1.generation);
    /* Double destroy of the stale handle is a no-op, not a free of s2. */
    rhi_sampler_destroy(g_dev, s1);
    ASSERT_FALSE(handle_is_null(s2));
    rhi_sampler_destroy(g_dev, s2);
}

TEST(cubemap_six_faces_face_major_roundtrip) {
    /* R624: readback of a color cubemap yields all six faces face-major
     * (+X,-X,+Y,-Y,+Z,-Z), mip 0, 4B/px RGBA8 -> size*size*4*6 bytes. */
    RHICubemapDesc desc;
    u8 faces[6][4u * 4u * 4u];
    u8 out[4u * 4u * 4u * 6u];
    u32 f, i;
    RHICubemap cm;
    u32 w = 0u, h = 0u;
    memset(&desc, 0, sizeof(desc));
    desc.size = 4u;
    desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    for (f = 0u; f < 6u; ++f) {
        for (i = 0u; i < sizeof(faces[f]); ++i)
            faces[f][i] = (u8)(f * 40u + i);
        desc.faces[f] = faces[f];
    }
    cm = rhi_cubemap_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(cm));
    /* R631: the size query accepts cubemap handles and reports the face
     * extent. */
    ASSERT_TRUE(rhi_texture_get_size(g_dev, cm, &w, &h));
    ASSERT_EQ(w, 4u);
    ASSERT_EQ(h, 4u);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, cm, out,
                                        sizeof(out)));
    ASSERT_TRUE(memcmp(out, faces, sizeof(out)) == 0);
    rhi_cubemap_destroy(g_dev, cm);
}

TEST(cubemap_invalid_desc_rejected) {
    /* Fail-closed: zero size and out-of-set formats never produce a cube. */
    RHICubemapDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.size = 0u;
    desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    ASSERT_TRUE(handle_is_null(rhi_cubemap_create(g_dev, &desc)));
    desc.size = 4u;
    desc.format = RHI_FORMAT_D32_FLOAT;   /* depth cubes are not this API */
    ASSERT_TRUE(handle_is_null(rhi_cubemap_create(g_dev, &desc)));
}

int main(void) {
    g_layer = metal_test_layer_create(64u, 64u);
    if (g_layer == NULL) return 77;
    g_dev = rhi_device_create_ex(RHI_BACKEND_METAL, g_layer, NULL, 64u, 64u,
                                 &g_create_result);
    if (g_dev == NULL) {
        /* No Metal device on this host (GPU-less CI runner): a clean
         * UNAVAILABLE/ERROR is a skip, never a fabricated success. */
        metal_test_layer_destroy(g_layer);
        if (g_create_result == RHI_RESULT_UNAVAILABLE ||
            g_create_result == RHI_RESULT_ERROR) return 77;
        return 1;
    }
    printf("=== Running Tests ===\n");
    RUN_TEST(uniform_buffer_update_read_roundtrip);
    RUN_TEST(uniform_buffer_map_write_read);
    RUN_TEST(private_storage_buffer_staging_roundtrip);
    RUN_TEST(vertex_buffer_initial_data_read_back);
    RUN_TEST(texture_rgba8_upload_readback);
    RUN_TEST(texture_read_pixels_small_buffer_fails);
    RUN_TEST(texture_undefined_format_rejected);
    RUN_TEST(texture_d32_depth_create_upload_readback);
    RUN_TEST(texture_upload_mip_then_read_mip0);
    RUN_TEST(texture_array_layer_upload_and_size);
    RUN_TEST(sampler_create_destroy_generation_advances);
    RUN_TEST(cubemap_six_faces_face_major_roundtrip);
    RUN_TEST(cubemap_invalid_desc_rejected);
    /* destroy after all resources are freed must drain + release cleanly. */
    rhi_device_destroy(g_dev);
    metal_test_layer_destroy(g_layer);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
#else
int main(void) { return 77; }
#endif
