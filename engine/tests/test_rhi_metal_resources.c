#include "test_framework.h"
#include <rhi/rhi.h>
#include <rhi/rhi_backend_internal.h>   /* Task 12: feature-bit forced branch */
#include <core/shader_io.h>   /* Task 10: shader_read_file (manifest e2e) */

/* Plan C Task 7: resource family contract for the native Metal backend —
 * buffers (shared storage mode for UNIFORM/initial-data, private staging
 * for pure-GPU usage, map fail-closed on private), textures (upload and
 * readback byte contract R587-R602), samplers (slot generation advances
 * across destroy), cubemaps (R624 face-major readback of all six faces)
 * and 2D texture arrays (R441 layer upload). Runs on macOS with
 * ENGINE_RHI_BACKEND_METAL; everywhere else it exits 77 (SKIP). The
 * CAMetalLayer is created offscreen, same pattern as
 * test_rhi_metal_frame_lifecycle.
 *
 * Task 8 appends the pipeline/FBO family: RHIPipelineDesc field mapping
 * (vertex layouts, depth/cull/blend state, color_format/MRT attachment
 * formats), the R616/R617 bind/bind_load clear-vs-preserve contract, the
 * R618 shadow depth clear, and the R619 caller-owned clear color. Shaders
 * ride the interim MSL-source path (newLibraryWithSource:, entry
 * convention vs_main/fs_main) until Task 10 lands the manifest loader. */
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

/* ---- Task 8: pipeline / FBO / MRT / shadow contracts ----
 * Minimal inline MSL (interim Task 8 stub path; Task 10 switches shader
 * loading to the manifest/metallib pipeline). Entry-name convention for
 * the interim path: vertex = vs_main, fragment = fs_main. */
static const char *k_msl_vs_passthrough =
    "#include <metal_stdlib>\n"
    "using namespace metal;\n"
    "vertex float4 vs_main(uint vid [[vertex_id]]) {\n"
    "    float2 p[3] = { float2(-1.0, -1.0), float2(3.0, -1.0),\n"
    "                    float2(-1.0, 3.0) };\n"
    "    return float4(p[vid], 0.5, 1.0);\n"
    "}\n";

static const char *k_msl_fs_red =
    "#include <metal_stdlib>\n"
    "using namespace metal;\n"
    "fragment float4 fs_main() { return float4(1.0, 0.0, 0.0, 1.0); }\n";

static const char *k_msl_fs_mrt =
    "#include <metal_stdlib>\n"
    "using namespace metal;\n"
    "struct MRTOut { float4 c0 [[color(0)]]; float4 c1 [[color(1)]]; };\n"
    "fragment MRTOut fs_main() {\n"
    "    MRTOut o;\n"
    "    o.c0 = float4(1.0, 0.0, 0.0, 1.0);\n"
    "    o.c1 = float4(0.0, 1.0, 0.0, 1.0);\n"
    "    return o;\n"
    "}\n";

static const char *k_msl_fs_green =
    "#include <metal_stdlib>\n"
    "using namespace metal;\n"
    "fragment float4 fs_main() { return float4(0.0, 1.0, 0.0, 1.0); }\n";

/* Task 10: the production shader path is manifest-only; the inline-MSL
 * sources in this suite compile through the ENGINE_RHI_TEST hook (the
 * pre-Task-10 interim path). Entry convention: vs_main/fs_main/cs_main. */
RHIShader rhi_test_metal_shader_create_source(RHIDevice *dev,
                                              const char *source, usize len,
                                              const char *entry,
                                              bool is_fragment);

static RHIShader make_shader(const char *msl, bool is_fragment) {
    /* Null-handle on failure; the caller asserts non-null. */
    return rhi_test_metal_shader_create_source(g_dev, msl,
                                               (usize)strlen(msl),
                                               is_fragment ? "fs_main"
                                                           : "vs_main",
                                               is_fragment);
}

/* Frame wrapper pair (rhi_frame_acquire_ex/end_ex/present_ex), same
 * pattern as test_rhi_metal_frame_lifecycle. begin_frame returns NULL on
 * failure; the caller asserts non-null. */
static RHICmdBuffer *begin_frame(void) {
    RHIResult r = RHI_RESULT_OK;
    RHICmdBuffer *cmd = rhi_frame_acquire_ex(g_dev, &r);
    if (cmd == NULL || r != RHI_RESULT_OK) return NULL;
    return cmd;
}

static void end_frame(void) {
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
}

/* Exact-match pixel for colors built from 0.0/1.0 only (unorm-exact). */
static void assert_center_px(const u8 *px, u32 w, u32 h,
                             u8 e0, u8 e1, u8 e2, u8 e3) {
    const u8 *c = px + ((usize)(h / 2u) * w + (usize)(w / 2u)) * 4u;
    ASSERT_EQ((u32)c[0], (u32)e0);
    ASSERT_EQ((u32)c[1], (u32)e1);
    ASSERT_EQ((u32)c[2], (u32)e2);
    ASSERT_EQ((u32)c[3], (u32)e3);
}

TEST(pipeline_offscreen_fbo_draw_readback) {
    /* RHIPipelineDesc mapping smoke test: default color_format (0 ==
     * swapchain, BGRA8) + no_vertex_input + depth defaults, drawn into a
     * default (BGRA8) offscreen FBO. The fullscreen red triangle covers
     * the center pixel; BGRA8 readback is native byte order B,G,R,A. */
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_red, true);
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    ASSERT_FALSE(handle_is_null(fbo.depth_tex));
    ASSERT_EQ(fbo.width, 64u);
    ASSERT_EQ(fbo.height, 64u);
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 255u, 255u);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    ASSERT_FALSE(rhi_handle_valid(fbo.fb));
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(fbo_bind_clears_default_and_bind_load_preserves) {
    /* R617/R619: bind clears to the per-FBO clear color (default
     * {0.05, 0.05, 0.1, 1.0} in BGRA bytes ~= {26, 13, 13, 255});
     * set_clear_color replaces it; bind_load preserves prior content. */
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    const u8 *c;
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);   /* clear only, no draw */
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    c = px + ((usize)32u * 64u + 32u) * 4u;
    /* 0.1*255=25.5 and 0.05*255=12.75: GPU unorm rounding, allow +-1. */
    ASSERT_TRUE(c[0] >= 25u && c[0] <= 27u);   /* B = 0.1  */
    ASSERT_TRUE(c[1] >= 12u && c[1] <= 14u);   /* G = 0.05 */
    ASSERT_TRUE(c[2] >= 12u && c[2] <= 14u);   /* R = 0.05 */
    ASSERT_EQ((u32)c[3], 255u);                /* A = 1.0  */
    /* R619: caller-owned clear color replaces the default. */
    rhi_offscreen_fbo_set_clear_color(g_dev, &fbo, 1.0f, 0.0f, 0.0f, 1.0f);
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 255u, 255u);
    /* R617 dual: bind_load preserves — a load pass with no draw leaves the
     * previous frame's pixels untouched. */
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind_load(cmd, &fbo);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 255u, 255u);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
}

TEST(mrt_two_attachments_distinct_colors) {
    /* R616: mrt bind clears every attachment to (0,0,0,0); the MRT
     * pipeline's fragment outputs land in their own attachments (RGBA8
     * here, so readback order is R,G,B,A). */
    RHIFormat formats[2] = { RHI_FORMAT_R8G8B8A8_UNORM,
                             RHI_FORMAT_R8G8B8A8_UNORM };
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_mrt, true);
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIMRTFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    desc.mrt_attachment_count = 2u;
    desc.mrt_formats[0] = formats[0];
    desc.mrt_formats[1] = formats[1];
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    fbo = rhi_mrt_fbo_create(g_dev, 64u, 64u, formats, 2u);
    ASSERT_FALSE(handle_is_null(fbo.fb));
    ASSERT_EQ(fbo.attachment_count, 2u);
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_mrt_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_mrt_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], px,
                                        sizeof(px)));
    assert_center_px(px, 64u, 64u, 255u, 0u, 0u, 255u);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], px,
                                        sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 255u, 0u, 255u);
    rhi_mrt_fbo_destroy(g_dev, &fbo);
    ASSERT_FALSE(rhi_handle_valid(fbo.fb));
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(mrt_five_attachments_create_and_clear) {
    /* RHI_MRT_MAX_ATTACHMENTS == 5: the maximum-size MRT FBO creates and
     * its bind clears all five attachments to (0,0,0,0). Six attachments
     * fail closed at the shared validator. */
    RHIFormat formats[6];
    RHIMRTFBO fbo;
    RHIMRTFBO bad;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    u32 i;
    for (i = 0u; i < 6u; ++i) formats[i] = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo = rhi_mrt_fbo_create(g_dev, 64u, 64u, formats, 5u);
    ASSERT_FALSE(handle_is_null(fbo.fb));
    ASSERT_EQ(fbo.attachment_count, 5u);
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_mrt_fbo_bind(cmd, &fbo);   /* clear only, no draw */
    rhi_mrt_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0xFFu, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[4], px,
                                        sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 0u, 0u);
    rhi_mrt_fbo_destroy(g_dev, &fbo);
    bad = rhi_mrt_fbo_create(g_dev, 64u, 64u, formats, 6u);
    ASSERT_TRUE(handle_is_null(bad.fb));
}

TEST(shadow_map_bind_clears_depth_to_one) {
    /* R618: binding a shadow map clears its depth to 1.0 (depth-only
     * pass, loadAction=Clear, clearDepth=1.0) — readback is the R602
     * D32 f32 contract, every texel exactly 1.0f. */
    RHIShadowMap sm;
    RHICmdBuffer *cmd;
    f32 depth[64u * 64u];
    u32 i;
    sm = rhi_shadow_map_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(sm.depth_tex));
    ASSERT_EQ(sm.width, 64u);
    ASSERT_EQ(sm.height, 64u);
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_bind_shadow_map(cmd, &sm);
    rhi_cmd_unbind_shadow_map(cmd, 64u, 64u);
    end_frame();
    memset(depth, 0, sizeof(depth));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, sm.depth_tex, depth,
                                        sizeof(depth)));
    for (i = 0u; i < 64u * 64u; ++i) {
        ASSERT_TRUE(depth[i] == 1.0f);
    }
    rhi_shadow_map_destroy(g_dev, &sm);
    ASSERT_FALSE(rhi_handle_valid(sm.fbo));
}

TEST(shadow_depth_pipeline_vertex_only_shader) {
    /* is_shadow_depth: the fragment shader handle may be null — the
     * Metal descriptor takes vertexFunction only (fragmentFunction=nil,
     * no color attachments, depthAttachmentPixelFormat=D32). */
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    ASSERT_FALSE(handle_is_null(vs));
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    /* desc.frag stays RHI_HANDLE_NULL. */
    desc.is_shadow_depth = true;
    desc.vertex_stride = 32u;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
}

TEST(shadow_viewport_restricts_depth_writes) {
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIShadowMap sm;
    RHICmdBuffer *cmd;
    f32 depth[64u * 64u];
    ASSERT_FALSE(handle_is_null(vs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.no_vertex_input = true;
    desc.is_shadow_depth = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    sm = rhi_shadow_map_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(sm.depth_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_bind_shadow_map(cmd, &sm);
    rhi_cmd_set_shadow_viewport(cmd, 0u, 0u, 32u, 32u);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_draw(cmd, 3u, 1u);  /* z=0.5 only in the top-left quadrant */
    rhi_cmd_unbind_shadow_map(cmd, 64u, 64u);
    end_frame();
    memset(depth, 0, sizeof(depth));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, sm.depth_tex, depth,
                                        sizeof(depth)));
    ASSERT_TRUE(depth[0] == 0.5f);
    ASSERT_TRUE(depth[31u * 64u + 31u] == 0.5f);
    ASSERT_TRUE(depth[32u] == 1.0f);
    ASSERT_TRUE(depth[32u * 64u] == 1.0f);
    ASSERT_TRUE(depth[63u * 64u + 63u] == 1.0f);
    rhi_shadow_map_destroy(g_dev, &sm);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
}

TEST(clear_depth_preserves_color) {
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_red, true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    f32 depth[64u * 64u];
    u8 px[64u * 64u * 4u];
    u32 i;
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_draw(cmd, 3u, 1u);  /* red + depth 0.5 */
    rhi_cmd_clear_depth(cmd);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.depth_tex, depth,
                                        sizeof(depth)));
    for (i = 0u; i < 64u * 64u; ++i) ASSERT_TRUE(depth[i] == 1.0f);
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 255u, 255u);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(texel_buffers_cross_4096_texel_rows) {
    static const char *k_msl_fs_texel =
        "#include <metal_stdlib>\nusing namespace metal;\n"
        "fragment float4 fs_main(texture2d<float> t0 [[texture(16)]],\n"
        "                        texture2d<float> t1 [[texture(17)]]) {\n"
        "  bool ok = all(t0.read(uint2(0, 0)) == float4(1, 2, 3, 4)) &&\n"
        "            all(t0.read(uint2(0, 1)) == float4(5, 6, 7, 8)) &&\n"
        "            all(t0.read(uint2(1, 1)) == float4(9, 10, 11, 12)) &&\n"
        "            all(t1.read(uint2(2, 0)) == float4(13, 14, 15, 16));\n"
        "  return ok ? float4(0, 1, 0, 1) : float4(1, 0, 0, 1);\n"
        "}\n";
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_texel, true);
    float *v0 = (float *)calloc(4098u * 4u, sizeof(float));
    float v1[12] = {0};
    RHIBufferDesc bdesc;
    RHIBuffer b0, b1;
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    ASSERT_NOT_NULL(v0);
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    v0[0] = 1; v0[1] = 2; v0[2] = 3; v0[3] = 4;
    v0[4096u * 4u + 0] = 5; v0[4096u * 4u + 1] = 6;
    v0[4096u * 4u + 2] = 7; v0[4096u * 4u + 3] = 8;
    v0[4097u * 4u + 0] = 9; v0[4097u * 4u + 1] = 10;
    v0[4097u * 4u + 2] = 11; v0[4097u * 4u + 3] = 12;
    v1[8] = 13; v1[9] = 14; v1[10] = 15; v1[11] = 16;
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_TEXEL;
    bdesc.size = 4098u * 4u * sizeof(float);
    bdesc.initial_data = v0;
    b0 = rhi_buffer_create(g_dev, &bdesc);
    bdesc.size = sizeof(v1);
    bdesc.initial_data = v1;
    b1 = rhi_buffer_create(g_dev, &bdesc);
    free(v0);
    ASSERT_FALSE(handle_is_null(b0));
    ASSERT_FALSE(handle_is_null(b1));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    desc.uses_texel_buffer = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_texel_buffers(cmd, b0, b1);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 255u, 0u, 255u);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_buffer_destroy(g_dev, b0);
    rhi_buffer_destroy(g_dev, b1);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

void rhi_test_metal_set_private_texel(bool enabled);

TEST(texel_private_initial_upload_update_and_readback) {
    u8 initial[64], update[16], out[64];
    RHIBufferDesc desc;
    RHIBuffer buf;
    memset(&desc, 0, sizeof(desc));
    desc.usage = RHI_BUFFER_USAGE_TEXEL;
    desc.size = sizeof(initial);
    desc.initial_data = initial;
    for (u32 i = 0u; i < sizeof(initial); ++i) initial[i] = (u8)(i * 3u + 1u);
    rhi_test_metal_set_private_texel(true);
    buf = rhi_buffer_create(g_dev, &desc);
    rhi_test_metal_set_private_texel(false);
    ASSERT_FALSE(handle_is_null(buf));
    ASSERT_TRUE(rhi_buffer_map(g_dev, buf) == NULL);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    ASSERT_TRUE(memcmp(out, initial, sizeof(initial)) == 0);
    for (u32 i = 0u; i < sizeof(update); ++i) update[i] = (u8)(0xF0u - i);
    rhi_buffer_update_region(g_dev, buf, 32u, update, sizeof(update));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    ASSERT_TRUE(memcmp(out + 32u, update, sizeof(update)) == 0);
    ASSERT_TRUE(memcmp(out, initial, 32u) == 0);
    ASSERT_TRUE(memcmp(out + 48u, initial + 48u, 16u) == 0);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(pipeline_invalid_shader_handle_rejected) {
    /* Fail closed: a garbage shader handle never produces a pipeline. */
    RHIPipelineDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.vert.index = 0x7FFFu;
    desc.vert.generation = 0x7FFFu;
    desc.frag = desc.vert;
    ASSERT_TRUE(handle_is_null(rhi_pipeline_create(g_dev, &desc)));
}

TEST(offscreen_fbo_msaa_desc_fails_closed) {
    /* depth_resolve_supported == false (Task 3 fail-closed), so the
     * shared validator rejects sample_count > 1 on this backend even
     * though color_resolve_supported == true. 1x via create_desc works
     * and round-trips through the same code path. */
    RHIOffscreenFBODesc desc;
    RHIOffscreenFBO fbo;
    RHIOffscreenFBO ok;
    memset(&desc, 0, sizeof(desc));
    desc.width = 64u;
    desc.height = 64u;
    desc.color_format = RHI_FORMAT_B8G8R8A8_UNORM;
    desc.sample_count = 2u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &desc);
    ASSERT_TRUE(handle_is_null(fbo.fb));
    desc.sample_count = 1u;
    ok = rhi_offscreen_fbo_create_desc(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(ok.fb));
    ASSERT_EQ(ok.sample_count, 1u);
    rhi_offscreen_fbo_destroy(g_dev, &ok);
}

TEST(cubemap_depth_fbo_bind_face_clears) {
    /* R618 sibling: binding cubemap depth face 2 clears that face to
     * 1.0f. Readback via the cubemap face-major contract (R624 layout:
     * six faces of size*size f32). */
    RHICubemapDepthFBO fbo;
    RHICmdBuffer *cmd;
    f32 depth[6u * 16u * 16u];
    u32 i;
    fbo = rhi_cubemap_depth_fbo_create(g_dev, 16u);
    ASSERT_FALSE(handle_is_null(fbo.depth_tex));
    ASSERT_EQ(fbo.size, 16u);
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cubemap_depth_fbo_bind_face(cmd, &fbo, 2u);
    rhi_cubemap_depth_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(depth, 0, sizeof(depth));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.depth_tex, depth,
                                        sizeof(depth)));
    /* Face 2 cleared; other faces undefined — assert face 2 only. */
    for (i = 2u * 16u * 16u; i < 3u * 16u * 16u; ++i) {
        ASSERT_TRUE(depth[i] == 1.0f);
    }
    rhi_cubemap_depth_fbo_destroy(g_dev, &fbo);
    ASSERT_FALSE(rhi_handle_valid(fbo.fb));
}

/* ---- Task 8 review fix-round regressions (C1/C2/I1) ---- */

TEST(mrt_clear_color_after_bind_targets_mrt) {
    /* C1 regression: the engine's real sequence (main.c:6506-6507) is
     * rhi_mrt_fbo_bind immediately followed by rhi_cmd_clear_color. VK
     * semantics: vkCmdClearAttachments clears color attachment 0 of the
     * CURRENT target in place (rhi_vk.c:7063-7081) — depth and the other
     * attachments keep their content. The buggy Metal path hijacked the
     * clear into the screen pass, leaving attachment 0 at the bind-time
     * (0,0,0,0). */
    RHIFormat formats[2] = { RHI_FORMAT_R8G8B8A8_UNORM,
                             RHI_FORMAT_R8G8B8A8_UNORM };
    RHIMRTFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    fbo = rhi_mrt_fbo_create(g_dev, 64u, 64u, formats, 2u);
    ASSERT_FALSE(handle_is_null(fbo.fb));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_mrt_fbo_bind(cmd, &fbo);                        /* both -> (0,0,0,0) */
    rhi_cmd_clear_color_attachment(cmd, 1u, 1.0f, 0.0f, 0.0f, 1.0f);
    rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 1.0f, 1.0f);   /* att0 -> blue */
    rhi_mrt_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], px,
                                        sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 255u, 255u);  /* RGBA8: blue */
    memset(px, 0xFFu, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], px,
                                        sizeof(px)));
    assert_center_px(px, 64u, 64u, 255u, 0u, 0u, 255u);  /* RGBA8: red preserved */
    rhi_mrt_fbo_destroy(g_dev, &fbo);
}

TEST(r445_pipeline_overrides_sticky_depth_state) {
    /* C2 regression: the depth-stencil state is sticky encoder state.
     * Same encoder: bind a depth-tested pipeline (Less + write on) and
     * draw a z=0.5 red triangle (depth becomes 0.5), then bind an R445
     * pipeline (depth_write_disable && !depth_compare_lequal => depth
     * test fully off) and draw green. Green must win. The buggy Metal
     * path gave the R445 pipeline a nil depth state and skipped
     * setDepthStencilState: at bind, so the stale Less state discarded
     * every green fragment (0.5 < 0.5 fails). */
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs_red = make_shader(k_msl_fs_red, true);
    RHIShader fs_green = make_shader(k_msl_fs_green, true);
    RHIPipelineDesc desc;
    RHIPipeline pipe_depth, pipe_r445;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs_red));
    ASSERT_FALSE(handle_is_null(fs_green));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs_red;
    desc.no_vertex_input = true;
    /* defaults: depth test on, write on, compare Less */
    pipe_depth = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe_depth));
    desc.frag = fs_green;
    desc.depth_write_disable = true;   /* R445: && !lequal => test off */
    pipe_r445 = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe_r445));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe_depth);
    rhi_cmd_draw(cmd, 3u, 1u);         /* red, depth 0.5 written */
    rhi_cmd_bind_pipeline(cmd, pipe_r445);
    rhi_cmd_draw(cmd, 3u, 1u);         /* green must override */
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 255u, 0u, 255u);  /* BGRA green */
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe_depth);
    rhi_pipeline_destroy(g_dev, pipe_r445);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs_red);
    rhi_shader_destroy(g_dev, fs_green);
}

TEST(pass_switch_invalidates_bound_pipeline) {
    /* I1 regression: a pass switch drops all encoder state; the stale
     * bound_pipeline handle must not be replayed into the fresh encoder.
     * Fail closed (log + no draw) and the device must survive (no
     * device-lost latch from a Metal validation error). */
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_red, true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);   /* screen pass reopened */
    rhi_cmd_draw(cmd, 3u, 1u);   /* no rebind: must fail closed, not crash */
    end_frame();
    /* A Metal validation failure would latch the device lost via the
     * completion handler; the bounded idle probe must still pass. */
    ASSERT_TRUE(rhi_device_idle(g_dev));
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* ---- Task 9: compute / blit fill / screenshot / indirect / gpu timer ---- */

static const char *k_msl_cs_write_index =
    "#include <metal_stdlib>\n"
    "using namespace metal;\n"
    "kernel void cs_main(device uint *out [[buffer(0)]],\n"
    "                  uint tid [[thread_position_in_grid]]) {\n"
    "    if (tid < 256u) out[tid] = tid;\n"
    "}\n";

TEST(compute_dispatch_writes_indices) {
    /* Compute contract: storage buffer (private storage) starts zeroed,
     * one dispatch of a tid->out[tid] kernel, host readback asserts the
     * full 0..N-1 sequence. The 256-group dispatch over-covers on any
     * threadgroup size; the kernel guards tid < 256. */
    RHIShader cs = rhi_test_metal_shader_create_source(
        g_dev, k_msl_cs_write_index, (usize)strlen(k_msl_cs_write_index),
        "cs_main", false);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIBufferDesc bdesc;
    RHIBuffer buf;
    RHICmdBuffer *cmd;
    u32 out[256];
    u32 i;
    ASSERT_FALSE(handle_is_null(cs));
    memset(&desc, 0, sizeof(desc));
    desc.is_compute = true;
    desc.frag = cs;   /* VK convention: compute shader rides the frag slot */
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_STORAGE;
    bdesc.size = sizeof(out);
    buf = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(buf));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_storage_buffer(cmd, buf, 0u);
    rhi_cmd_dispatch(cmd, 256u, 1u, 1u);
    rhi_cmd_memory_barrier(cmd);
    rhi_cmd_dispatch(cmd, 256u, 1u, 1u);   /* idempotent second dispatch */
    end_frame();
    memset(out, 0xFF, sizeof(out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    for (i = 0u; i < 256u; ++i) ASSERT_EQ(out[i], i);
    rhi_buffer_destroy(g_dev, buf);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, cs);
}

TEST(buffer_size_constants_fed_to_kernel) {
    /* spirv-cross emits `constant uint* spvBufferSizeConstants
     * [[buffer(25)]]` for runtime-array SSBOs (`.length()`), one uint BYTE
     * SIZE per SSBO (the MSL divides by the element stride itself). The
     * backend must feed that table from the bound buffers' byte sizes at
     * dispatch — unbound, Metal validation hard-fails the dispatch and the
     * kernel reads garbage (P0: particle_update/cull/vert all declare it). */
    static const char *k_msl_cs_bsc =
        "#include <metal_stdlib>\n"
        "using namespace metal;\n"
        "struct BscParticle { float4 a; float4 b; float4 c; float4 d; };\n"
        "kernel void cs_main(constant uint* spvBufferSizeConstants [[buffer(25)]],\n"
        "                    device BscParticle *particles [[buffer(0)]],\n"
        "                    uint tid [[thread_position_in_grid]]) {\n"
        "    constant uint& particlesBufferSize = spvBufferSizeConstants[0];\n"
        "    uint count = particlesBufferSize / 64u;\n"
        "    if (tid < count) particles[tid].a.x = 1.0f;\n"
        "}\n";
    RHIShader cs = rhi_test_metal_shader_create_source(
        g_dev, k_msl_cs_bsc, (usize)strlen(k_msl_cs_bsc), "cs_main", false);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIBufferDesc bdesc;
    RHIBuffer buf;
    RHICmdBuffer *cmd;
    f32 out[16u * 16u];   /* 16 particles x 64B (16 floats each) */
    u32 i;
    ASSERT_FALSE(handle_is_null(cs));
    memset(&desc, 0, sizeof(desc));
    desc.is_compute = true;
    desc.frag = cs;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_STORAGE;
    bdesc.size = 16u * 64u;
    buf = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(buf));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_storage_buffer(cmd, buf, 0u);
    rhi_cmd_dispatch(cmd, 1u, 1u, 1u);
    end_frame();
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    for (i = 0u; i < 16u; ++i)
        ASSERT_TRUE(out[i * 16u] == 1.0f);   /* stride 64B = 16 floats */
    rhi_buffer_destroy(g_dev, buf);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, cs);
}

TEST(fill_buffer_pattern_and_clamp_readback) {
    /* rhi_cmd_fill_buffer fills the u32 pattern (VK vkCmdFillBuffer
     * parity); 0xABABABAB is byte-uniform. Offset+size clamp against the
     * buffer (R425) instead of overrunning. */
    RHIBufferDesc bdesc;
    RHIBuffer buf;
    RHICmdBuffer *cmd;
    u8 out[256];
    u32 i;
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_STORAGE;
    bdesc.size = sizeof(out);
    buf = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(buf));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_fill_buffer(cmd, buf, 0u, sizeof(out), 0xABABABABu);
    end_frame();
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    for (i = 0u; i < sizeof(out); ++i) ASSERT_EQ((u32)out[i], 0xABu);
    /* Clamped tail fill: [200, 256) -> 0xCD, head stays 0xAB. */
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_fill_buffer(cmd, buf, 200u, 200u, 0xCDCDCDCDu);
    end_frame();
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, out, 0u, sizeof(out)));
    for (i = 0u; i < 200u; ++i) ASSERT_EQ((u32)out[i], 0xABu);
    for (i = 200u; i < 256u; ++i) ASSERT_EQ((u32)out[i], 0xCDu);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(screenshot_clear_color_and_post_present_refused) {
    /* rhi.h:815-826 / R577: screenshot is legal from frame_begin until
     * present; here it runs post-frame_end pre-present and must carry the
     * just-committed frame's pixels. The drawable is BGRA8, so readback
     * byte order is B,G,R,A (native, same as VK's raw copy). Post-present
     * calls are refused (false + log). */
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    const u8 *c;
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_begin_render_pass(cmd);
    rhi_cmd_clear_color(cmd, 0.1f, 0.2f, 0.3f, 1.0f);
    rhi_cmd_end_render_pass(cmd);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_screenshot(g_dev, 0u, 0u, 64u, 64u, px, sizeof(px)));
    c = px + ((usize)32u * 64u + 32u) * 4u;
    ASSERT_TRUE(c[0] >= 75u && c[0] <= 78u);    /* B = 0.3 */
    ASSERT_TRUE(c[1] >= 50u && c[1] <= 52u);    /* G = 0.2 */
    ASSERT_TRUE(c[2] >= 24u && c[2] <= 27u);    /* R = 0.1 */
    ASSERT_EQ((u32)c[3], 255u);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_FALSE(rhi_screenshot(g_dev, 0u, 0u, 64u, 64u, px, sizeof(px)));
}

TEST(screenshot_rows_are_top_down) {
    /* rhi.h row-order contract: top-left origin, rows top-down on every
     * backend. Red is scissored to the top half of the drawable (Metal
     * scissor is top-left origin), so row 0 must read red and the last row
     * the blue clear. A bottom-up readback swaps them. */
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_red, true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    const u8 *top;
    const u8 *bottom;
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_begin_render_pass(cmd);
    rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 1.0f, 1.0f);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_scissor_top_left(cmd, 0u, 0u, 64u, 32u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_cmd_end_render_pass(cmd);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_screenshot(g_dev, 0u, 0u, 64u, 64u, px, sizeof(px)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    top = px + 32u * 4u;
    bottom = px + ((usize)63u * 64u + 32u) * 4u;
    ASSERT_EQ((u32)top[0], 0u);       /* B,G,R,A: red */
    ASSERT_EQ((u32)top[2], 255u);
    ASSERT_EQ((u32)bottom[0], 255u);  /* blue clear */
    ASSERT_EQ((u32)bottom[2], 0u);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(draw_indirect_executes_arg_buffer) {
    /* Non-indexed indirect: the 16-byte arg record {vertexCount,
     * instanceCount, vertexStart, baseInstance} is ABI-identical in VK
     * (VkDrawIndirectCommand) and Metal (MTLDrawPrimitivesIndirectArguments). */
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_red, true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIBufferDesc bdesc;
    RHIBuffer args;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    u32 record[4] = { 3u, 1u, 0u, 0u };
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_INDIRECT;
    bdesc.size = sizeof(record);
    bdesc.initial_data = record;
    args = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(args));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_draw_indirect(g_dev, args, 0u, 1u, (u32)sizeof(record));
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 255u, 255u);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_buffer_destroy(g_dev, args);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(draw_indexed_indirect_executes_arg_buffer) {
    /* Indexed indirect: the 20-byte record {indexCount, instanceCount,
     * firstIndex, vertexOffset, firstInstance} matches
     * MTLDrawIndexedPrimitivesIndirectArguments; the index buffer rides
     * rhi_cmd_bind_index_buffer (U16 here). */
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_red, true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIBufferDesc bdesc;
    RHIBuffer args, ibuf;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    u32 record[5] = { 3u, 1u, 0u, 0u, 0u };
    u16 indices[3] = { 0u, 1u, 2u };
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_INDIRECT;
    bdesc.size = sizeof(record);
    bdesc.initial_data = record;
    args = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(args));
    bdesc.usage = RHI_BUFFER_USAGE_INDEX;
    bdesc.size = sizeof(indices);
    bdesc.initial_data = indices;
    ibuf = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(ibuf));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_index_buffer(cmd, ibuf, 0u, false);
    rhi_cmd_draw_indexed_indirect(g_dev, args, 0u, 1u, (u32)sizeof(record));
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 255u, 255u);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_buffer_destroy(g_dev, args);
    rhi_buffer_destroy(g_dev, ibuf);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(gpu_timer_roundtrip_smoke) {
    /* MTLCounterSampleBuffer timestamp pair around a clear-only pass.
     * Hardware-dependent value: assert create succeeds and the elapsed
     * query is non-negative and non-crashing after a bounded idle. */
    RHIGPUTimer *t;
    RHICmdBuffer *cmd;
    f64 ms;
    t = rhi_gpu_timer_create(g_dev);
    ASSERT_NOT_NULL(t);
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_gpu_timer_begin(t);
    rhi_cmd_begin_render_pass(cmd);
    rhi_cmd_clear_color(cmd, 0.2f, 0.2f, 0.2f, 1.0f);
    rhi_cmd_end_render_pass(cmd);
    rhi_gpu_timer_end(t);
    end_frame();
    ASSERT_TRUE(rhi_device_idle(g_dev));
    ms = rhi_gpu_timer_elapsed_ms(t);
    ASSERT_TRUE(ms >= 0.0);
    rhi_gpu_timer_destroy(g_dev, t);
}

TEST(gpu_timer_destroy_with_pending_sample_is_safe) {
    /* I2 regression: a begin called between passes pends a raw timer
     * pointer on the cmd buffer; destroying the timer before the next pass
     * open must sweep the pending entry, or the drain dereferences freed
     * memory (UAF). On this degraded host the sample pends without a csb,
     * which exercises the identical list path. */
    RHIGPUTimer *t;
    RHICmdBuffer *cmd;
    t = rhi_gpu_timer_create(g_dev);
    ASSERT_NOT_NULL(t);
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_gpu_timer_begin(t);            /* no pass open: sample pends */
    rhi_gpu_timer_destroy(g_dev, t);   /* must sweep the pending entry */
    /* Do not touch t past this point. */
    rhi_cmd_begin_render_pass(cmd);    /* drain must not deref the freed timer */
    rhi_cmd_clear_color(cmd, 0.1f, 0.1f, 0.1f, 1.0f);
    rhi_cmd_end_render_pass(cmd);
    end_frame();
    ASSERT_TRUE(rhi_device_idle(g_dev));
}

/* ---- Task 10: offline manifest end-to-end ---- */

TEST(manifest_real_shader_resolves) {
    /* The production path: hash the GLSL text of real engine shaders and
     * resolve the offline-converted function (engine.metallib beside the
     * executable, or the manifest's embedded MSL fallback). A hash miss
     * must fail closed (no runtime GLSL compile). */
    char path[1024];
    usize len = 0u;
    char *src;
    RHIShader sh;
    snprintf(path, sizeof(path), "%s/post_vk.vert", ENGINE_SHADER_SOURCE_DIR);
    src = shader_read_file(path, &len);
    ASSERT_NOT_NULL(src);
    sh = rhi_shader_create(g_dev, src, len, false);
    ASSERT_FALSE(handle_is_null(sh));
    free(src);
    rhi_shader_destroy(g_dev, sh);
    snprintf(path, sizeof(path), "%s/blinn_phong_vk.frag",
             ENGINE_SHADER_SOURCE_DIR);
    src = shader_read_file(path, &len);
    ASSERT_NOT_NULL(src);
    sh = rhi_shader_create(g_dev, src, len, true);
    ASSERT_FALSE(handle_is_null(sh));
    free(src);
    rhi_shader_destroy(g_dev, sh);
    snprintf(path, sizeof(path), "%s/cull.comp", ENGINE_SHADER_SOURCE_DIR);
    src = shader_read_file(path, &len);
    ASSERT_NOT_NULL(src);
    sh = rhi_shader_create_compute(g_dev, src, len);
    ASSERT_FALSE(handle_is_null(sh));
    free(src);
    rhi_shader_destroy(g_dev, sh);
    /* Miss: a valid GLSL text that no engine shader matches. */
    {
        static const char *bogus = "#version 450\nvoid main() { }\n";
        ASSERT_TRUE(handle_is_null(
            rhi_shader_create(g_dev, bogus, (usize)strlen(bogus), false)));
    }
}

/* ---- Task 11: push-constant / uniform-offset golden ---- */

static const char *const k_push_names[] = {
    "u_model",
    "u_view",
    "u_proj",
    "u_prev_mvp",
    "u_light_vp",
    "u_light_dir",
    "u_shadow_bias",
    "u_light_color",
    "u_water_y",
    "u_ambient",
    "u_time",
    "u_camera_pos",
    "u_water_color",
    "u_mvp",
    "u_light_pos",
    "u_far_plane",
    "u_taa_curr_vp",
    "u_taa_prev_vp",
    "u_taa_inv_proj",
    "u_screen_w",
    "u_screen_h",
    "u_taa_blend",
    "u_taa_first_frame",
    "u_fxaa_threshold",
    "u_taa_use_velocity",
    "u_tm_exposure",
    "u_tm_gamma",
    "u_tm_mode",
    "u_cg_saturation",
    "u_cg_contrast",
    "u_cg_brightness",
    "u_cg_temperature",
    "u_cg_tint",
    "u_cine_aberration",
    "u_cine_vignette",
    "u_cine_grain",
    "u_cine_time",
    "push.dt",
    "push.view",
    "push.proj",
    "u_roughness",
    "u_face",
    "u_face_size",
    "u_mip_size",
    "u_sun_dir",
    "u_sun_color",
    "u_cc_vp",
    "u_cc_params0",
    "u_cc_params1",
    "u_cull_vp",
    "u_cull_count",
    "u_cull_hi_z_width",
    "u_cull_hi_z_height",
    "u_cull_use_hi_z",
    "u_cull_write_draws",
    "pc_view_proj",
    "pc_object_count",
    "pc_hi_z_width",
    "pc_hi_z_height",
    "pc_output_size",
    "total_draws",
    "u_prev_vp",
    "u_vol_inv_proj",
    "u_vol_view",
    "u_vol_ldx",
    "u_vol_ldy",
    "u_vol_ldz",
    "u_vol_lcx",
    "u_vol_lcy",
    "u_vol_lcz",
    "u_vol_density",
    "u_vol_fog_r",
    "u_vol_fog_g",
    "u_vol_fog_b",
    "u_vol_sw",
    "u_vol_sh",
    "u_vol_inv_view",
    "u_lf_light_x",
    "u_lf_light_y",
    "u_lf_intensity",
    "u_lf_sw",
    "u_lf_sh",
    "u_lf_lc_r",
    "u_lf_lc_g",
    "u_lf_lc_b",
    "u_ssgi_inv_proj",
    "u_ssgi_proj",
    "u_ssgi_radius",
    "u_ssgi_intensity",
    "u_ssgi_sw",
    "u_ssgi_sh",
    "u_fxaa_sw",
    "u_fxaa_sh",
    "u_tm_screen_w",
    "u_tm_screen_h",
    "u_cine_sw",
    "u_cine_sh",
    "u_dof_focus",
    "u_dof_range",
    "u_dof_near",
    "u_dof_far",
    "u_dof_sw",
    "u_dof_sh",
    "u_ssr_proj",
    "u_ssr_inv_proj",
    "u_ssr_view",
    "u_ssr_sw",
    "u_ssr_sh",
    "u_ssr_max_steps",
    "u_ssr_stride",
    "u_ssr_thickness",
    "u_taa_sw",
    "u_taa_sh",
    "u_ssao_proj",
    "u_ssao_inv_proj",
    "u_ssao_sw",
    "u_ssao_sh",
    "u_ssao_radius",
    "u_ssao_bias",
    "u_dv_mode",
    "u_dv_near",
    "u_dv_far",
    "u_dv_split0",
    "u_dv_split1",
    "u_dv_split2",
    "u_dv_split3",
    "u_ca_strength",
    "u_vignette_strength",
    "u_vignette_softness",
    "u_grain_strength",
    "u_sharp_strength",
    "u_sharp_sw",
    "u_sharp_sh",
    "u_ups_rw",
    "u_ups_rh",
    "u_ups_dw",
    "u_ups_dh",
    "u_ups_sharp",
    "u_ups_copy_only",
    "u_ups_first_frame",
    "u_ups_inv_proj",
    "u_ups_prev_vp",
    "u_lum_w",
    "u_lum_h",
    "u_lum_speed",
    "u_lum_dt",
    "u_gr_sun_x",
    "u_gr_sun_y",
    "u_gr_intensity",
    "u_gr_decay",
    "u_gr_sw",
    "u_gr_sh",
    "u_mb_strength",
    "u_mb_sw",
    "u_mb_sh",
    "u_mb_inv_proj",
    "u_mb_prev_vp",
    "u_mb_use_velocity",
    "u_cs_light_x",
    "u_cs_light_y",
    "u_cs_light_z",
    "u_cs_inv_proj",
    "u_cs_sw",
    "u_cs_sh",
    "u_threshold",
    "u_direction",
    "u_bloom_strength",
    "u_sss_strength",
    "u_sss_sw",
    "u_sss_sh",
    "u_sss_max_dist",
    "u_sssv_strength",
    "u_sssv_sw",
    "u_sssv_sh",
    "u_sssv_max_dist",
    "u_fog_near",
    "u_fog_far",
    "u_near",
    "u_far",
    "u_point_count",
    "u_dir_count",
    "u_fog_color",
    "u_underwater",
    "u_point_shadow_far_planes",
    "u_pom_enabled",
    "u_occlusion_strength",
    "u_mr_factor",
    "u_emissive_factor",
    "u_inv_vp",
    "u_albedo",
    "u_inv_proj",
    "u_curr_vp"
};

/* Golden block generated by test_rhi_push_offset_dump on the Vulkan backend
 * (this repo, RTX 4060 Laptop, 2026-10-16). The Metal cascade is a
 * mechanical port of the VK table body; this block is the byte-exact
 * contract. Regenerate by running test_rhi_push_offset_dump and pasting its
 * stdout. */
/* The golden block is one logical literal longer than the ISO C99 4095-char
 * minimum; silence the warning for this declaration only (Mac-only test). */
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverlength-strings"
#endif
static const char k_push_offset_golden[] =
    "default u_model 0\n"
    "default u_view 64\n"
    "default u_proj 128\n"
    "default u_prev_mvp 192\n"
    "default u_light_dir 192\n"
    "default u_light_color 208\n"
    "default u_ambient 224\n"
    "default u_camera_pos 240\n"
    "default u_taa_curr_vp 0\n"
    "default u_taa_prev_vp 64\n"
    "default u_taa_inv_proj 128\n"
    "default u_taa_blend 200\n"
    "default u_taa_first_frame 204\n"
    "default u_fxaa_threshold 8\n"
    "default u_taa_use_velocity 208\n"
    "default u_tm_exposure 0\n"
    "default u_tm_gamma 4\n"
    "default u_tm_mode 16\n"
    "default u_cg_saturation 0\n"
    "default u_cg_contrast 4\n"
    "default u_cg_brightness 8\n"
    "default u_cg_temperature 12\n"
    "default u_cg_tint 16\n"
    "default u_cine_aberration 0\n"
    "default u_cine_vignette 4\n"
    "default u_cine_grain 8\n"
    "default u_cine_time 12\n"
    "default u_sun_dir 128\n"
    "default u_sun_color 144\n"
    "default u_prev_vp 192\n"
    "default u_vol_inv_proj 0\n"
    "default u_vol_view 64\n"
    "default u_vol_ldx 128\n"
    "default u_vol_ldy 132\n"
    "default u_vol_ldz 136\n"
    "default u_vol_lcx 140\n"
    "default u_vol_lcy 144\n"
    "default u_vol_lcz 148\n"
    "default u_vol_density 152\n"
    "default u_vol_fog_r 156\n"
    "default u_vol_fog_g 160\n"
    "default u_vol_fog_b 164\n"
    "default u_vol_sw 168\n"
    "default u_vol_sh 172\n"
    "default u_vol_inv_view 176\n"
    "default u_lf_light_x 0\n"
    "default u_lf_light_y 4\n"
    "default u_lf_intensity 8\n"
    "default u_lf_sw 12\n"
    "default u_lf_sh 16\n"
    "default u_lf_lc_r 20\n"
    "default u_lf_lc_g 24\n"
    "default u_lf_lc_b 28\n"
    "default u_ssgi_inv_proj 0\n"
    "default u_ssgi_proj 64\n"
    "default u_ssgi_radius 128\n"
    "default u_ssgi_intensity 132\n"
    "default u_ssgi_sw 136\n"
    "default u_ssgi_sh 140\n"
    "default u_fxaa_sw 0\n"
    "default u_fxaa_sh 4\n"
    "default u_tm_screen_w 8\n"
    "default u_tm_screen_h 12\n"
    "default u_cine_sw 16\n"
    "default u_cine_sh 20\n"
    "default u_dof_focus 0\n"
    "default u_dof_range 4\n"
    "default u_dof_near 8\n"
    "default u_dof_far 12\n"
    "default u_dof_sw 16\n"
    "default u_dof_sh 20\n"
    "default u_ssr_proj 0\n"
    "default u_ssr_inv_proj 64\n"
    "default u_ssr_view 128\n"
    "default u_ssr_sw 192\n"
    "default u_ssr_sh 196\n"
    "default u_ssr_max_steps 200\n"
    "default u_ssr_stride 204\n"
    "default u_ssr_thickness 208\n"
    "default u_taa_sw 192\n"
    "default u_taa_sh 196\n"
    "default u_ssao_proj 0\n"
    "default u_ssao_inv_proj 64\n"
    "default u_ssao_sw 128\n"
    "default u_ssao_sh 132\n"
    "default u_ssao_radius 136\n"
    "default u_ssao_bias 140\n"
    "default u_dv_mode 0\n"
    "default u_dv_near 4\n"
    "default u_dv_far 8\n"
    "default u_dv_split0 12\n"
    "default u_dv_split1 16\n"
    "default u_dv_split2 20\n"
    "default u_dv_split3 24\n"
    "default u_ca_strength 0\n"
    "default u_vignette_strength 4\n"
    "default u_vignette_softness 8\n"
    "default u_grain_strength 12\n"
    "default u_sharp_strength 0\n"
    "default u_sharp_sw 4\n"
    "default u_sharp_sh 8\n"
    "default u_ups_rw 0\n"
    "default u_ups_rh 4\n"
    "default u_ups_dw 8\n"
    "default u_ups_dh 12\n"
    "default u_ups_sharp 16\n"
    "default u_ups_copy_only 20\n"
    "default u_ups_first_frame 24\n"
    "default u_ups_inv_proj 32\n"
    "default u_ups_prev_vp 96\n"
    "default u_lum_w 0\n"
    "default u_lum_h 4\n"
    "default u_lum_speed 8\n"
    "default u_lum_dt 12\n"
    "default u_gr_sun_x 0\n"
    "default u_gr_sun_y 4\n"
    "default u_gr_intensity 8\n"
    "default u_gr_decay 12\n"
    "default u_gr_sw 16\n"
    "default u_gr_sh 20\n"
    "default u_mb_strength 0\n"
    "default u_mb_sw 4\n"
    "default u_mb_sh 8\n"
    "default u_mb_inv_proj 12\n"
    "default u_mb_prev_vp 76\n"
    "default u_mb_use_velocity 140\n"
    "default u_cs_light_x 0\n"
    "default u_cs_light_y 4\n"
    "default u_cs_light_z 8\n"
    "default u_cs_inv_proj 12\n"
    "default u_cs_sw 76\n"
    "default u_cs_sh 80\n"
    "default u_threshold 0\n"
    "default u_direction 0\n"
    "default u_bloom_strength 0\n"
    "default u_sss_strength 0\n"
    "default u_sss_sw 4\n"
    "default u_sss_sh 8\n"
    "default u_sss_max_dist 12\n"
    "default u_sssv_strength 0\n"
    "default u_sssv_sw 4\n"
    "default u_sssv_sh 8\n"
    "default u_sssv_max_dist 12\n"
    "default u_inv_proj 0\n"
    "default u_curr_vp 64\n"
    "terrain u_view 0\n"
    "terrain u_proj 64\n"
    "terrain u_light_vp 128\n"
    "terrain u_light_dir 192\n"
    "terrain u_shadow_bias 204\n"
    "terrain u_light_color 208\n"
    "terrain u_water_y 220\n"
    "terrain u_ambient 224\n"
    "terrain u_time 236\n"
    "terrain u_camera_pos 240\n"
    "water u_view 0\n"
    "water u_proj 64\n"
    "water u_light_vp 128\n"
    "water u_shadow_bias 220\n"
    "water u_water_y 224\n"
    "water u_time 204\n"
    "water u_camera_pos 192\n"
    "water u_water_color 208\n"
    "combined_aa u_taa_curr_vp 0\n"
    "combined_aa u_taa_prev_vp 64\n"
    "combined_aa u_taa_inv_proj 128\n"
    "combined_aa u_screen_w 192\n"
    "combined_aa u_screen_h 196\n"
    "combined_aa u_taa_blend 200\n"
    "combined_aa u_taa_first_frame 204\n"
    "combined_aa u_fxaa_threshold 208\n"
    "combined_aa u_taa_use_velocity 212\n"
    "combined_color u_screen_w 48\n"
    "combined_color u_screen_h 52\n"
    "combined_color u_tm_exposure 0\n"
    "combined_color u_tm_gamma 4\n"
    "combined_color u_tm_mode 8\n"
    "combined_color u_cg_saturation 12\n"
    "combined_color u_cg_contrast 16\n"
    "combined_color u_cg_brightness 20\n"
    "combined_color u_cg_temperature 24\n"
    "combined_color u_cg_tint 28\n"
    "combined_color u_cine_aberration 32\n"
    "combined_color u_cine_vignette 36\n"
    "combined_color u_cine_grain 40\n"
    "combined_color u_cine_time 44\n"
    "shadow_depth u_model 0\n"
    "shadow_depth u_light_vp 64\n"
    "shadow_depth u_mvp 64\n"
    "shadow_depth u_light_pos 128\n"
    "shadow_depth u_far_plane 144\n"
    "skinned_gbuffer u_model 0\n"
    "skinned_gbuffer u_view 64\n"
    "skinned_gbuffer u_proj 128\n"
    "skinned_gbuffer u_prev_mvp 192\n"
    "clustered u_model 0\n"
    "clustered u_view 64\n"
    "clustered u_prev_mvp 192\n"
    "clustered u_shadow_bias 184\n"
    "clustered u_ambient 144\n"
    "clustered u_camera_pos 128\n"
    "clustered u_taa_curr_vp 0\n"
    "clustered u_taa_prev_vp 64\n"
    "clustered u_taa_inv_proj 128\n"
    "clustered u_screen_w 160\n"
    "clustered u_screen_h 164\n"
    "clustered u_taa_blend 200\n"
    "clustered u_taa_first_frame 204\n"
    "clustered u_fxaa_threshold 8\n"
    "clustered u_taa_use_velocity 208\n"
    "clustered u_tm_exposure 0\n"
    "clustered u_tm_gamma 4\n"
    "clustered u_tm_mode 16\n"
    "clustered u_cg_saturation 0\n"
    "clustered u_cg_contrast 4\n"
    "clustered u_cg_brightness 8\n"
    "clustered u_cg_temperature 12\n"
    "clustered u_cg_tint 16\n"
    "clustered u_cine_aberration 0\n"
    "clustered u_cine_vignette 4\n"
    "clustered u_cine_grain 8\n"
    "clustered u_cine_time 12\n"
    "clustered u_sun_dir 128\n"
    "clustered u_sun_color 144\n"
    "clustered u_prev_vp 192\n"
    "clustered u_vol_inv_proj 0\n"
    "clustered u_vol_view 64\n"
    "clustered u_vol_ldx 128\n"
    "clustered u_vol_ldy 132\n"
    "clustered u_vol_ldz 136\n"
    "clustered u_vol_lcx 140\n"
    "clustered u_vol_lcy 144\n"
    "clustered u_vol_lcz 148\n"
    "clustered u_vol_density 152\n"
    "clustered u_vol_fog_r 156\n"
    "clustered u_vol_fog_g 160\n"
    "clustered u_vol_fog_b 164\n"
    "clustered u_vol_sw 168\n"
    "clustered u_vol_sh 172\n"
    "clustered u_vol_inv_view 176\n"
    "clustered u_lf_light_x 0\n"
    "clustered u_lf_light_y 4\n"
    "clustered u_lf_intensity 8\n"
    "clustered u_lf_sw 12\n"
    "clustered u_lf_sh 16\n"
    "clustered u_lf_lc_r 20\n"
    "clustered u_lf_lc_g 24\n"
    "clustered u_lf_lc_b 28\n"
    "clustered u_ssgi_inv_proj 0\n"
    "clustered u_ssgi_proj 64\n"
    "clustered u_ssgi_radius 128\n"
    "clustered u_ssgi_intensity 132\n"
    "clustered u_ssgi_sw 136\n"
    "clustered u_ssgi_sh 140\n"
    "clustered u_fxaa_sw 0\n"
    "clustered u_fxaa_sh 4\n"
    "clustered u_tm_screen_w 8\n"
    "clustered u_tm_screen_h 12\n"
    "clustered u_cine_sw 16\n"
    "clustered u_cine_sh 20\n"
    "clustered u_dof_focus 0\n"
    "clustered u_dof_range 4\n"
    "clustered u_dof_near 8\n"
    "clustered u_dof_far 12\n"
    "clustered u_dof_sw 16\n"
    "clustered u_dof_sh 20\n"
    "clustered u_ssr_proj 0\n"
    "clustered u_ssr_inv_proj 64\n"
    "clustered u_ssr_view 128\n"
    "clustered u_ssr_sw 192\n"
    "clustered u_ssr_sh 196\n"
    "clustered u_ssr_max_steps 200\n"
    "clustered u_ssr_stride 204\n"
    "clustered u_ssr_thickness 208\n"
    "clustered u_taa_sw 192\n"
    "clustered u_taa_sh 196\n"
    "clustered u_ssao_proj 0\n"
    "clustered u_ssao_inv_proj 64\n"
    "clustered u_ssao_sw 128\n"
    "clustered u_ssao_sh 132\n"
    "clustered u_ssao_radius 136\n"
    "clustered u_ssao_bias 140\n"
    "clustered u_dv_mode 0\n"
    "clustered u_dv_near 4\n"
    "clustered u_dv_far 8\n"
    "clustered u_dv_split0 12\n"
    "clustered u_dv_split1 16\n"
    "clustered u_dv_split2 20\n"
    "clustered u_dv_split3 24\n"
    "clustered u_ca_strength 0\n"
    "clustered u_vignette_strength 4\n"
    "clustered u_vignette_softness 8\n"
    "clustered u_grain_strength 12\n"
    "clustered u_sharp_strength 0\n"
    "clustered u_sharp_sw 4\n"
    "clustered u_sharp_sh 8\n"
    "clustered u_ups_rw 0\n"
    "clustered u_ups_rh 4\n"
    "clustered u_ups_dw 8\n"
    "clustered u_ups_dh 12\n"
    "clustered u_ups_sharp 16\n"
    "clustered u_ups_copy_only 20\n"
    "clustered u_ups_first_frame 24\n"
    "clustered u_ups_inv_proj 32\n"
    "clustered u_ups_prev_vp 96\n"
    "clustered u_lum_w 0\n"
    "clustered u_lum_h 4\n"
    "clustered u_lum_speed 8\n"
    "clustered u_lum_dt 12\n"
    "clustered u_gr_sun_x 0\n"
    "clustered u_gr_sun_y 4\n"
    "clustered u_gr_intensity 8\n"
    "clustered u_gr_decay 12\n"
    "clustered u_gr_sw 16\n"
    "clustered u_gr_sh 20\n"
    "clustered u_mb_strength 0\n"
    "clustered u_mb_sw 4\n"
    "clustered u_mb_sh 8\n"
    "clustered u_mb_inv_proj 12\n"
    "clustered u_mb_prev_vp 76\n"
    "clustered u_mb_use_velocity 140\n"
    "clustered u_cs_light_x 0\n"
    "clustered u_cs_light_y 4\n"
    "clustered u_cs_light_z 8\n"
    "clustered u_cs_inv_proj 12\n"
    "clustered u_cs_sw 76\n"
    "clustered u_cs_sh 80\n"
    "clustered u_threshold 0\n"
    "clustered u_direction 0\n"
    "clustered u_bloom_strength 0\n"
    "clustered u_sss_strength 0\n"
    "clustered u_sss_sw 4\n"
    "clustered u_sss_sh 8\n"
    "clustered u_sss_max_dist 12\n"
    "clustered u_sssv_strength 0\n"
    "clustered u_sssv_sw 4\n"
    "clustered u_sssv_sh 8\n"
    "clustered u_sssv_max_dist 12\n"
    "clustered u_fog_near 140\n"
    "clustered u_fog_far 156\n"
    "clustered u_near 168\n"
    "clustered u_far 172\n"
    "clustered u_point_count 176\n"
    "clustered u_dir_count 180\n"
    "clustered u_fog_color 192\n"
    "clustered u_underwater 204\n"
    "clustered u_point_shadow_far_planes 208\n"
    "clustered u_pom_enabled 224\n"
    "clustered u_occlusion_strength 228\n"
    "clustered u_mr_factor 232\n"
    "clustered u_emissive_factor 240\n"
    "clustered u_inv_proj 0\n"
    "clustered u_curr_vp 64\n"
    "nonclustered_tbo u_view 0\n"
    "nonclustered_tbo u_proj 64\n"
    "nonclustered_tbo u_light_dir 128\n"
    "nonclustered_tbo u_light_color 144\n"
    "nonclustered_tbo u_ambient 160\n"
    "nonclustered_tbo u_camera_pos 176\n"
    "compute push.dt 0\n"
    "compute push.view 0\n"
    "compute push.proj 64\n"
    "compute u_roughness 0\n"
    "compute u_face 4\n"
    "compute u_face_size 8\n"
    "compute u_mip_size 8\n"
    "compute u_sun_dir 16\n"
    "compute u_sun_color 32\n"
    "compute u_cc_vp 0\n"
    "compute u_cc_params0 64\n"
    "compute u_cc_params1 80\n"
    "compute u_cull_vp 0\n"
    "compute u_cull_count 64\n"
    "compute u_cull_hi_z_width 68\n"
    "compute u_cull_hi_z_height 72\n"
    "compute u_cull_use_hi_z 76\n"
    "compute u_cull_write_draws 80\n"
    "compute pc_view_proj 0\n"
    "compute pc_object_count 64\n"
    "compute pc_hi_z_width 68\n"
    "compute pc_hi_z_height 72\n"
    "compute pc_output_size 0\n"
    "compute total_draws 0\n"
    "storage push.view 0\n"
    "storage push.proj 64\n"
    "no_vertex_input u_model 0\n"
    "no_vertex_input u_view 64\n"
    "no_vertex_input u_proj 128\n"
    "no_vertex_input u_prev_mvp 192\n"
    "no_vertex_input u_camera_pos 64\n"
    "no_vertex_input u_taa_curr_vp 0\n"
    "no_vertex_input u_taa_prev_vp 64\n"
    "no_vertex_input u_taa_inv_proj 128\n"
    "no_vertex_input u_screen_w 80\n"
    "no_vertex_input u_screen_h 84\n"
    "no_vertex_input u_taa_blend 200\n"
    "no_vertex_input u_taa_first_frame 204\n"
    "no_vertex_input u_fxaa_threshold 8\n"
    "no_vertex_input u_taa_use_velocity 208\n"
    "no_vertex_input u_tm_exposure 0\n"
    "no_vertex_input u_tm_gamma 4\n"
    "no_vertex_input u_tm_mode 16\n"
    "no_vertex_input u_cg_saturation 0\n"
    "no_vertex_input u_cg_contrast 4\n"
    "no_vertex_input u_cg_brightness 8\n"
    "no_vertex_input u_cg_temperature 12\n"
    "no_vertex_input u_cg_tint 16\n"
    "no_vertex_input u_cine_aberration 0\n"
    "no_vertex_input u_cine_vignette 4\n"
    "no_vertex_input u_cine_grain 8\n"
    "no_vertex_input u_cine_time 12\n"
    "no_vertex_input u_sun_dir 128\n"
    "no_vertex_input u_sun_color 144\n"
    "no_vertex_input u_prev_vp 128\n"
    "no_vertex_input u_vol_inv_proj 0\n"
    "no_vertex_input u_vol_view 64\n"
    "no_vertex_input u_vol_ldx 128\n"
    "no_vertex_input u_vol_ldy 132\n"
    "no_vertex_input u_vol_ldz 136\n"
    "no_vertex_input u_vol_lcx 140\n"
    "no_vertex_input u_vol_lcy 144\n"
    "no_vertex_input u_vol_lcz 148\n"
    "no_vertex_input u_vol_density 152\n"
    "no_vertex_input u_vol_fog_r 156\n"
    "no_vertex_input u_vol_fog_g 160\n"
    "no_vertex_input u_vol_fog_b 164\n"
    "no_vertex_input u_vol_sw 168\n"
    "no_vertex_input u_vol_sh 172\n"
    "no_vertex_input u_vol_inv_view 176\n"
    "no_vertex_input u_lf_light_x 0\n"
    "no_vertex_input u_lf_light_y 4\n"
    "no_vertex_input u_lf_intensity 8\n"
    "no_vertex_input u_lf_sw 12\n"
    "no_vertex_input u_lf_sh 16\n"
    "no_vertex_input u_lf_lc_r 20\n"
    "no_vertex_input u_lf_lc_g 24\n"
    "no_vertex_input u_lf_lc_b 28\n"
    "no_vertex_input u_ssgi_inv_proj 0\n"
    "no_vertex_input u_ssgi_proj 64\n"
    "no_vertex_input u_ssgi_radius 128\n"
    "no_vertex_input u_ssgi_intensity 132\n"
    "no_vertex_input u_ssgi_sw 136\n"
    "no_vertex_input u_ssgi_sh 140\n"
    "no_vertex_input u_fxaa_sw 0\n"
    "no_vertex_input u_fxaa_sh 4\n"
    "no_vertex_input u_tm_screen_w 8\n"
    "no_vertex_input u_tm_screen_h 12\n"
    "no_vertex_input u_cine_sw 16\n"
    "no_vertex_input u_cine_sh 20\n"
    "no_vertex_input u_dof_focus 0\n"
    "no_vertex_input u_dof_range 4\n"
    "no_vertex_input u_dof_near 8\n"
    "no_vertex_input u_dof_far 12\n"
    "no_vertex_input u_dof_sw 16\n"
    "no_vertex_input u_dof_sh 20\n"
    "no_vertex_input u_ssr_proj 0\n"
    "no_vertex_input u_ssr_inv_proj 64\n"
    "no_vertex_input u_ssr_view 128\n"
    "no_vertex_input u_ssr_sw 192\n"
    "no_vertex_input u_ssr_sh 196\n"
    "no_vertex_input u_ssr_max_steps 200\n"
    "no_vertex_input u_ssr_stride 204\n"
    "no_vertex_input u_ssr_thickness 208\n"
    "no_vertex_input u_taa_sw 192\n"
    "no_vertex_input u_taa_sh 196\n"
    "no_vertex_input u_ssao_proj 0\n"
    "no_vertex_input u_ssao_inv_proj 64\n"
    "no_vertex_input u_ssao_sw 128\n"
    "no_vertex_input u_ssao_sh 132\n"
    "no_vertex_input u_ssao_radius 136\n"
    "no_vertex_input u_ssao_bias 140\n"
    "no_vertex_input u_dv_mode 0\n"
    "no_vertex_input u_dv_near 4\n"
    "no_vertex_input u_dv_far 8\n"
    "no_vertex_input u_dv_split0 12\n"
    "no_vertex_input u_dv_split1 16\n"
    "no_vertex_input u_dv_split2 20\n"
    "no_vertex_input u_dv_split3 24\n"
    "no_vertex_input u_ca_strength 0\n"
    "no_vertex_input u_vignette_strength 4\n"
    "no_vertex_input u_vignette_softness 8\n"
    "no_vertex_input u_grain_strength 12\n"
    "no_vertex_input u_sharp_strength 0\n"
    "no_vertex_input u_sharp_sw 4\n"
    "no_vertex_input u_sharp_sh 8\n"
    "no_vertex_input u_ups_rw 0\n"
    "no_vertex_input u_ups_rh 4\n"
    "no_vertex_input u_ups_dw 8\n"
    "no_vertex_input u_ups_dh 12\n"
    "no_vertex_input u_ups_sharp 16\n"
    "no_vertex_input u_ups_copy_only 20\n"
    "no_vertex_input u_ups_first_frame 24\n"
    "no_vertex_input u_ups_inv_proj 32\n"
    "no_vertex_input u_ups_prev_vp 96\n"
    "no_vertex_input u_lum_w 0\n"
    "no_vertex_input u_lum_h 4\n"
    "no_vertex_input u_lum_speed 8\n"
    "no_vertex_input u_lum_dt 12\n"
    "no_vertex_input u_gr_sun_x 0\n"
    "no_vertex_input u_gr_sun_y 4\n"
    "no_vertex_input u_gr_intensity 8\n"
    "no_vertex_input u_gr_decay 12\n"
    "no_vertex_input u_gr_sw 16\n"
    "no_vertex_input u_gr_sh 20\n"
    "no_vertex_input u_mb_strength 0\n"
    "no_vertex_input u_mb_sw 4\n"
    "no_vertex_input u_mb_sh 8\n"
    "no_vertex_input u_mb_inv_proj 12\n"
    "no_vertex_input u_mb_prev_vp 76\n"
    "no_vertex_input u_mb_use_velocity 140\n"
    "no_vertex_input u_cs_light_x 0\n"
    "no_vertex_input u_cs_light_y 4\n"
    "no_vertex_input u_cs_light_z 8\n"
    "no_vertex_input u_cs_inv_proj 12\n"
    "no_vertex_input u_cs_sw 76\n"
    "no_vertex_input u_cs_sh 80\n"
    "no_vertex_input u_threshold 0\n"
    "no_vertex_input u_direction 0\n"
    "no_vertex_input u_bloom_strength 0\n"
    "no_vertex_input u_sss_strength 0\n"
    "no_vertex_input u_sss_sw 4\n"
    "no_vertex_input u_sss_sh 8\n"
    "no_vertex_input u_sss_max_dist 12\n"
    "no_vertex_input u_sssv_strength 0\n"
    "no_vertex_input u_sssv_sw 4\n"
    "no_vertex_input u_sssv_sh 8\n"
    "no_vertex_input u_sssv_max_dist 12\n"
    "no_vertex_input u_inv_vp 0\n"
    "no_vertex_input u_inv_proj 0\n"
    "no_vertex_input u_curr_vp 64\n"
    "nvi_tbo u_model 0\n"
    "nvi_tbo u_view 64\n"
    "nvi_tbo u_prev_mvp 192\n"
    "nvi_tbo u_shadow_bias 184\n"
    "nvi_tbo u_ambient 144\n"
    "nvi_tbo u_camera_pos 128\n"
    "nvi_tbo u_taa_curr_vp 0\n"
    "nvi_tbo u_taa_prev_vp 64\n"
    "nvi_tbo u_taa_inv_proj 128\n"
    "nvi_tbo u_screen_w 160\n"
    "nvi_tbo u_screen_h 164\n"
    "nvi_tbo u_taa_blend 200\n"
    "nvi_tbo u_taa_first_frame 204\n"
    "nvi_tbo u_fxaa_threshold 8\n"
    "nvi_tbo u_taa_use_velocity 208\n"
    "nvi_tbo u_tm_exposure 0\n"
    "nvi_tbo u_tm_gamma 4\n"
    "nvi_tbo u_tm_mode 16\n"
    "nvi_tbo u_cg_saturation 0\n"
    "nvi_tbo u_cg_contrast 4\n"
    "nvi_tbo u_cg_brightness 8\n"
    "nvi_tbo u_cg_temperature 12\n"
    "nvi_tbo u_cg_tint 16\n"
    "nvi_tbo u_cine_aberration 0\n"
    "nvi_tbo u_cine_vignette 4\n"
    "nvi_tbo u_cine_grain 8\n"
    "nvi_tbo u_cine_time 12\n"
    "nvi_tbo u_sun_dir 128\n"
    "nvi_tbo u_sun_color 144\n"
    "nvi_tbo u_prev_vp 128\n"
    "nvi_tbo u_vol_inv_proj 0\n"
    "nvi_tbo u_vol_view 64\n"
    "nvi_tbo u_vol_ldx 128\n"
    "nvi_tbo u_vol_ldy 132\n"
    "nvi_tbo u_vol_ldz 136\n"
    "nvi_tbo u_vol_lcx 140\n"
    "nvi_tbo u_vol_lcy 144\n"
    "nvi_tbo u_vol_lcz 148\n"
    "nvi_tbo u_vol_density 152\n"
    "nvi_tbo u_vol_fog_r 156\n"
    "nvi_tbo u_vol_fog_g 160\n"
    "nvi_tbo u_vol_fog_b 164\n"
    "nvi_tbo u_vol_sw 168\n"
    "nvi_tbo u_vol_sh 172\n"
    "nvi_tbo u_vol_inv_view 176\n"
    "nvi_tbo u_lf_light_x 0\n"
    "nvi_tbo u_lf_light_y 4\n"
    "nvi_tbo u_lf_intensity 8\n"
    "nvi_tbo u_lf_sw 12\n"
    "nvi_tbo u_lf_sh 16\n"
    "nvi_tbo u_lf_lc_r 20\n"
    "nvi_tbo u_lf_lc_g 24\n"
    "nvi_tbo u_lf_lc_b 28\n"
    "nvi_tbo u_ssgi_inv_proj 0\n"
    "nvi_tbo u_ssgi_proj 64\n"
    "nvi_tbo u_ssgi_radius 128\n"
    "nvi_tbo u_ssgi_intensity 132\n"
    "nvi_tbo u_ssgi_sw 136\n"
    "nvi_tbo u_ssgi_sh 140\n"
    "nvi_tbo u_fxaa_sw 0\n"
    "nvi_tbo u_fxaa_sh 4\n"
    "nvi_tbo u_tm_screen_w 8\n"
    "nvi_tbo u_tm_screen_h 12\n"
    "nvi_tbo u_cine_sw 16\n"
    "nvi_tbo u_cine_sh 20\n"
    "nvi_tbo u_dof_focus 0\n"
    "nvi_tbo u_dof_range 4\n"
    "nvi_tbo u_dof_near 8\n"
    "nvi_tbo u_dof_far 12\n"
    "nvi_tbo u_dof_sw 16\n"
    "nvi_tbo u_dof_sh 20\n"
    "nvi_tbo u_ssr_proj 0\n"
    "nvi_tbo u_ssr_inv_proj 64\n"
    "nvi_tbo u_ssr_view 128\n"
    "nvi_tbo u_ssr_sw 192\n"
    "nvi_tbo u_ssr_sh 196\n"
    "nvi_tbo u_ssr_max_steps 200\n"
    "nvi_tbo u_ssr_stride 204\n"
    "nvi_tbo u_ssr_thickness 208\n"
    "nvi_tbo u_taa_sw 192\n"
    "nvi_tbo u_taa_sh 196\n"
    "nvi_tbo u_ssao_proj 0\n"
    "nvi_tbo u_ssao_inv_proj 64\n"
    "nvi_tbo u_ssao_sw 128\n"
    "nvi_tbo u_ssao_sh 132\n"
    "nvi_tbo u_ssao_radius 136\n"
    "nvi_tbo u_ssao_bias 140\n"
    "nvi_tbo u_dv_mode 0\n"
    "nvi_tbo u_dv_near 4\n"
    "nvi_tbo u_dv_far 8\n"
    "nvi_tbo u_dv_split0 12\n"
    "nvi_tbo u_dv_split1 16\n"
    "nvi_tbo u_dv_split2 20\n"
    "nvi_tbo u_dv_split3 24\n"
    "nvi_tbo u_ca_strength 0\n"
    "nvi_tbo u_vignette_strength 4\n"
    "nvi_tbo u_vignette_softness 8\n"
    "nvi_tbo u_grain_strength 12\n"
    "nvi_tbo u_sharp_strength 0\n"
    "nvi_tbo u_sharp_sw 4\n"
    "nvi_tbo u_sharp_sh 8\n"
    "nvi_tbo u_ups_rw 0\n"
    "nvi_tbo u_ups_rh 4\n"
    "nvi_tbo u_ups_dw 8\n"
    "nvi_tbo u_ups_dh 12\n"
    "nvi_tbo u_ups_sharp 16\n"
    "nvi_tbo u_ups_copy_only 20\n"
    "nvi_tbo u_ups_first_frame 24\n"
    "nvi_tbo u_ups_inv_proj 32\n"
    "nvi_tbo u_ups_prev_vp 96\n"
    "nvi_tbo u_lum_w 0\n"
    "nvi_tbo u_lum_h 4\n"
    "nvi_tbo u_lum_speed 8\n"
    "nvi_tbo u_lum_dt 12\n"
    "nvi_tbo u_gr_sun_x 0\n"
    "nvi_tbo u_gr_sun_y 4\n"
    "nvi_tbo u_gr_intensity 8\n"
    "nvi_tbo u_gr_decay 12\n"
    "nvi_tbo u_gr_sw 16\n"
    "nvi_tbo u_gr_sh 20\n"
    "nvi_tbo u_mb_strength 0\n"
    "nvi_tbo u_mb_sw 4\n"
    "nvi_tbo u_mb_sh 8\n"
    "nvi_tbo u_mb_inv_proj 12\n"
    "nvi_tbo u_mb_prev_vp 76\n"
    "nvi_tbo u_mb_use_velocity 140\n"
    "nvi_tbo u_cs_light_x 0\n"
    "nvi_tbo u_cs_light_y 4\n"
    "nvi_tbo u_cs_light_z 8\n"
    "nvi_tbo u_cs_inv_proj 12\n"
    "nvi_tbo u_cs_sw 76\n"
    "nvi_tbo u_cs_sh 80\n"
    "nvi_tbo u_threshold 0\n"
    "nvi_tbo u_direction 0\n"
    "nvi_tbo u_bloom_strength 0\n"
    "nvi_tbo u_sss_strength 0\n"
    "nvi_tbo u_sss_sw 4\n"
    "nvi_tbo u_sss_sh 8\n"
    "nvi_tbo u_sss_max_dist 12\n"
    "nvi_tbo u_sssv_strength 0\n"
    "nvi_tbo u_sssv_sw 4\n"
    "nvi_tbo u_sssv_sh 8\n"
    "nvi_tbo u_sssv_max_dist 12\n"
    "nvi_tbo u_fog_near 140\n"
    "nvi_tbo u_fog_far 156\n"
    "nvi_tbo u_near 168\n"
    "nvi_tbo u_far 172\n"
    "nvi_tbo u_point_count 176\n"
    "nvi_tbo u_dir_count 180\n"
    "nvi_tbo u_fog_color 192\n"
    "nvi_tbo u_underwater 204\n"
    "nvi_tbo u_point_shadow_far_planes 208\n"
    "nvi_tbo u_pom_enabled 224\n"
    "nvi_tbo u_occlusion_strength 228\n"
    "nvi_tbo u_mr_factor 232\n"
    "nvi_tbo u_emissive_factor 240\n"
    "nvi_tbo u_inv_proj 0\n"
    "nvi_tbo u_curr_vp 64\n"
    "";
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

typedef struct {
    const char *tag;
    RHIPipelineDesc desc;
} PushCfg;

TEST(push_offsets_match_vk_golden) {
    /* Identical configs/names/iteration order as the VK dump: rebuild every
     * line on the Metal side and byte-compare with the golden block. */
    static const PushCfg cfgs[] = {
        { "default", {0} },
        { "terrain", { .terrain_layout = true } },
        { "water", { .water_layout = true } },
        { "combined_aa", { .combined_aa_layout = true } },
        { "combined_color", { .combined_color_layout = true } },
        { "shadow_depth", { .is_shadow_depth = true } },
        { "skinned_gbuffer", { .skinned_vertex = true, .uses_texel_buffer = true } },
        { "clustered", { .uses_texel_buffer = true } },
        { "nonclustered_tbo", { .uses_texel_buffer = true, .is_instanced = true } },
        { "compute", { .is_compute = true } },
        { "storage", { .uses_storage = true } },
        { "no_vertex_input", { .no_vertex_input = true } },
        { "nvi_tbo", { .no_vertex_input = true, .uses_texel_buffer = true } },
    };
    static const char *k_msl_vs =
        "#include <metal_stdlib>\nusing namespace metal;\n"
        "vertex float4 vs_main() { return float4(0.0); }\n";
    static const char *k_msl_fs =
        "#include <metal_stdlib>\nusing namespace metal;\n"
        "fragment float4 fs_main() { return float4(1.0); }\n";
    static const char *k_msl_cs =
        "#include <metal_stdlib>\nusing namespace metal;\n"
        "kernel void cs_main() { }\n";
    static char buf[64u * 1024u];
    usize pos = 0u;
    u32 ci, ni;
    RHIShader vs = rhi_test_metal_shader_create_source(
        g_dev, k_msl_vs, (usize)strlen(k_msl_vs), "vs_main", false);
    RHIShader fs = rhi_test_metal_shader_create_source(
        g_dev, k_msl_fs, (usize)strlen(k_msl_fs), "fs_main", true);
    RHIShader cs = rhi_test_metal_shader_create_source(
        g_dev, k_msl_cs, (usize)strlen(k_msl_cs), "cs_main", false);
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    ASSERT_FALSE(handle_is_null(cs));
    for (ci = 0u; ci < sizeof(cfgs) / sizeof(cfgs[0]); ++ci) {
        RHIPipelineDesc desc = cfgs[ci].desc;
        RHIPipeline pipe;
        desc.vert = vs;
        desc.frag = cfgs[ci].desc.is_compute ? cs : fs;
        pipe = rhi_pipeline_create(g_dev, &desc);
        ASSERT_FALSE(handle_is_null(pipe));
        RHIPipelineBindings *bindings = rhi_pipeline_bindings_create(g_dev, pipe);
        ASSERT_NOT_NULL(bindings);
        for (ni = 0u; ni < sizeof(k_push_names) / sizeof(k_push_names[0]); ++ni) {
            i32 off = rhi_pipeline_get_uniform_location(g_dev, pipe,
                                                        k_push_names[ni]);
            ASSERT_EQ(rhi_pipeline_bindings_resolve(bindings, k_push_names[ni]), off);
            if (off >= 0) {
                int wrote = snprintf(buf + pos, sizeof(buf) - pos,
                                     "%s %s %d\n", cfgs[ci].tag,
                                     k_push_names[ni], (int)off);
                ASSERT_TRUE(wrote > 0 && (usize)wrote < sizeof(buf) - pos);
                pos += (usize)wrote;
            }
        }
        rhi_pipeline_bindings_destroy(g_dev, bindings);
        rhi_pipeline_destroy(g_dev, pipe);
    }
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
    rhi_shader_destroy(g_dev, cs);
    buf[pos] = '\0';
    ASSERT_EQ(pos, (usize)strlen(k_push_offset_golden));
    if (memcmp(buf, k_push_offset_golden, pos) != 0) {
        usize d;
        for (d = 0u; d < pos && buf[d] == k_push_offset_golden[d]; ++d) { }
        printf("golden mismatch at byte %llu: got '%.40s' want '%.40s'\n",
               (unsigned long long)d, buf + d, k_push_offset_golden + d);
        ASSERT_TRUE(false);
    }
}

TEST(push_constants_out_of_range_dropped) {
    /* rhi_push_range_fits: writes beyond the declared range drop with a
     * warning and must not corrupt staging or crash the subsequent draw. */
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = make_shader(k_msl_fs_red, true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    u8 blob[256];
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    memset(blob, 0x11, sizeof(blob));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, 200u, blob, 100u);   /* 200+100 > 256: dropped */
    rhi_cmd_push_constants(cmd, 0u, blob, sizeof(blob));   /* exact fit */
    rhi_cmd_set_uniform_mat4(cmd, 192u, (const f32 *)blob);   /* 192+64 = 256: fits */
    rhi_cmd_set_uniform_mat4(cmd, 200u, (const f32 *)blob);   /* over: dropped */
    rhi_cmd_set_uniform_f32(cmd, -1, 1.0f);   /* unknown name: silent no-op */
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    ASSERT_TRUE(rhi_device_idle(g_dev));
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    assert_center_px(px, 64u, 64u, 0u, 0u, 255u, 255u);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(set_uniform_mat4_column0_as_color) {
    /* End-to-end push: u_model@0 (default layout) staged via
     * set_uniform_mat4 reaches the fragment shader at [[buffer(29)]]. */
    static const char *k_msl_fs_mat =
        "#include <metal_stdlib>\n"
        "using namespace metal;\n"
        "struct Push { float4x4 m; };\n"
        "fragment float4 fs_main(constant Push& pc [[buffer(29)]]) {\n"
        "    return float4(pc.m[0].xyz, 1.0);\n"
        "}\n";
    f32 m[16];
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = rhi_test_metal_shader_create_source(
        g_dev, k_msl_fs_mat, (usize)strlen(k_msl_fs_mat), "fs_main", true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    i32 loc;
    u32 i;
    u8 px[64u * 64u * 4u];
    const u8 *c;
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    loc = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_model");
    ASSERT_EQ(loc, 0);
    for (i = 0u; i < 16u; ++i) m[i] = 0.0f;
    m[0] = 1.0f;   /* column 0 = (1, 0, 0, 0) -> red */
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, loc, m);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    c = px + ((usize)32u * 64u + 32u) * 4u;
    ASSERT_EQ((u32)c[0], 0u);
    ASSERT_EQ((u32)c[1], 0u);
    ASSERT_EQ((u32)c[2], 255u);
    ASSERT_EQ((u32)c[3], 255u);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(push_replays_across_blit_interlude) {
    /* I1 regression: setBytes is ENCODER state. A blit interlude
     * (fill_buffer) closes the encoder; the resumed pass's next draw must
     * re-bind buffer(29) or the fragment reads never-set garbage (black).
     * VK's push constants are command-buffer state and survive. */
    static const char *k_msl_fs_mat =
        "#include <metal_stdlib>\n"
        "using namespace metal;\n"
        "struct Push { float4x4 m; };\n"
        "fragment float4 fs_main(constant Push& pc [[buffer(29)]]) {\n"
        "    return float4(pc.m[0].xyz, 1.0);\n"
        "}\n";
    f32 m[16];
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = rhi_test_metal_shader_create_source(
        g_dev, k_msl_fs_mat, (usize)strlen(k_msl_fs_mat), "fs_main", true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHIBufferDesc bdesc;
    RHIBuffer scratch;
    RHICmdBuffer *cmd;
    u32 i;
    u8 px[64u * 64u * 4u];
    const u8 *c;
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_STORAGE;
    bdesc.size = 64u;
    scratch = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(scratch));
    for (i = 0u; i < 16u; ++i) m[i] = 0.0f;
    m[0] = 1.0f;
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, 0, m);
    rhi_cmd_draw(cmd, 3u, 1u);                      /* flush binds buffer(29) */
    rhi_cmd_fill_buffer(cmd, scratch, 0u, 64u, 0u); /* blit interlude: ends encoder */
    rhi_offscreen_fbo_bind_load(cmd, &fbo);         /* resume with Load */
    rhi_cmd_bind_pipeline(cmd, pipe);               /* rebind pipeline state */
    rhi_cmd_draw(cmd, 3u, 1u);                      /* must re-bind buffer(29) */
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    c = px + ((usize)32u * 64u + 32u) * 4u;
    ASSERT_EQ((u32)c[2], 255u);   /* still red — buffer(29) replayed */
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_buffer_destroy(g_dev, scratch);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(uniform_buffer_binds_and_replays_after_pass_switch) {
    /* I2 regression: VK-defers the UBO descriptor to draw time; Metal must
     * replay set*Buffer after an encoder rebuild. uses_textures pipeline ->
     * ubo_set 1 -> MSL buffer index 8. */
    static const char *k_msl_fs_ubo =
        "#include <metal_stdlib>\n"
        "using namespace metal;\n"
        "struct Factors { float4 c; };\n"
        "fragment float4 fs_main(constant Factors& f [[buffer(8)]]) {\n"
        "    return f.c;\n"
        "}\n";
    f32 red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs = rhi_test_metal_shader_create_source(
        g_dev, k_msl_fs_ubo, (usize)strlen(k_msl_fs_ubo), "fs_main", true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHIBufferDesc bdesc;
    RHIBuffer ubo, scratch;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    const u8 *c;
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs;
    desc.no_vertex_input = true;
    desc.uses_textures = true;   /* ubo_set = 1 -> index 8 */
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe));
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_UNIFORM;
    bdesc.size = sizeof(red);
    bdesc.initial_data = red;
    ubo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(ubo));
    bdesc.usage = RHI_BUFFER_USAGE_STORAGE;
    bdesc.initial_data = NULL;
    bdesc.size = 64u;
    scratch = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(scratch));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_uniform_buffer(cmd, ubo, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);                       /* flush binds the UBO */
    rhi_cmd_fill_buffer(cmd, scratch, 0u, 64u, 0u);  /* encoder rebuild */
    rhi_offscreen_fbo_bind_load(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_draw(cmd, 3u, 1u);                       /* must re-bind the UBO */
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    c = px + ((usize)32u * 64u + 32u) * 4u;
    ASSERT_EQ((u32)c[2], 255u);   /* still red — UBO replayed */
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_buffer_destroy(g_dev, ubo);
    rhi_buffer_destroy(g_dev, scratch);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(uniform_buffer_replays_with_pipeline_ubi_set_of_each_draw) {
    /* VK-parity gap (terrain crash): the UBO bind is recorded once per frame,
     * but the MSL buffer index depends on the BOUND PIPELINE's ubo_set
     * (uses_textures+uses_texel_buffer+uses_storage). A first draw with
     * ubo_set=0 consumed the dirty flag at index 0, so a later draw whose
     * pipeline needs index 8 drew with buffer(8) unbound — Metal validation
     * aborts (terrain_vert__forward_mrt 'missing Buffer binding at index 8').
     * The flush must re-apply the recorded UBO at EVERY draw, computed from
     * that draw's pipeline. */
    static const char *k_msl_fs_const =
        "#include <metal_stdlib>\n"
        "using namespace metal;\n"
        "fragment float4 fs_main() { return float4(0.0, 1.0, 0.0, 1.0); }\n";
    static const char *k_msl_fs_ubo8 =
        "#include <metal_stdlib>\n"
        "using namespace metal;\n"
        "struct Factors { float4 c; };\n"
        "fragment float4 fs_main(constant Factors& f [[buffer(8)]]) {\n"
        "    return f.c;\n"
        "}\n";
    f32 red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    RHIShader vs = make_shader(k_msl_vs_passthrough, false);
    RHIShader fs_a = rhi_test_metal_shader_create_source(
        g_dev, k_msl_fs_const, (usize)strlen(k_msl_fs_const), "fs_main", true);
    RHIShader fs_b = rhi_test_metal_shader_create_source(
        g_dev, k_msl_fs_ubo8, (usize)strlen(k_msl_fs_ubo8), "fs_main", true);
    RHIPipelineDesc desc;
    RHIPipeline pipe_a, pipe_b;
    RHIOffscreenFBO fbo;
    RHIBufferDesc bdesc;
    RHIBuffer ubo;
    RHICmdBuffer *cmd;
    u8 px[64u * 64u * 4u];
    const u8 *c;
    ASSERT_FALSE(handle_is_null(vs));
    ASSERT_FALSE(handle_is_null(fs_a));
    ASSERT_FALSE(handle_is_null(fs_b));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs;
    desc.frag = fs_a;
    desc.no_vertex_input = true;   /* ubo_set = 0 -> index 0 */
    desc.depth_compare_lequal = true;
    desc.depth_write_disable = true;   /* offscreen FBO: no depth race A vs B */
    pipe_a = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe_a));
    desc.frag = fs_b;
    desc.uses_textures = true;     /* ubo_set = 1 -> index 8 */
    pipe_b = rhi_pipeline_create(g_dev, &desc);
    ASSERT_FALSE(handle_is_null(pipe_b));
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_UNIFORM;
    bdesc.size = sizeof(red);
    bdesc.initial_data = red;
    ubo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_FALSE(handle_is_null(ubo));
    fbo = rhi_offscreen_fbo_create(g_dev, 64u, 64u);
    ASSERT_FALSE(handle_is_null(fbo.color_tex));
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_uniform_buffer(cmd, ubo, 0u);   /* recorded once, up front */
    rhi_cmd_bind_pipeline(cmd, pipe_a);
    rhi_cmd_draw(cmd, 3u, 1u);   /* consumes the dirty flag at index 0 */
    rhi_cmd_bind_pipeline(cmd, pipe_b);
    rhi_cmd_draw(cmd, 3u, 1u);   /* must still bind the UBO at index 8 */
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    end_frame();
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    c = px + ((usize)32u * 64u + 32u) * 4u;
    ASSERT_EQ((u32)c[2], 255u);   /* red from the UBO, not garbage */
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_buffer_destroy(g_dev, ubo);
    rhi_pipeline_destroy(g_dev, pipe_a);
    rhi_pipeline_destroy(g_dev, pipe_b);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs_a);
    rhi_shader_destroy(g_dev, fs_b);
}

/* ---- Task 12: acceleration structures ---- */

static RHIBuffer make_data_buffer(RHIBufferUsage usage, const void *data,
                                  usize size) {
    RHIBufferDesc d;
    memset(&d, 0, sizeof(d));
    d.usage = usage;
    d.size = size;
    d.initial_data = data;
    return rhi_buffer_create(g_dev, &d);
}

/* Task 12 review (M1): component-level conversion hook. */
bool rhi_test_metal_convert_tlas_record(RHIDevice *dev, const u8 *rec,
                                        u8 *out68);

TEST(acceleration_structure_lifecycle_and_tlas) {
    /* RT-capable path (M2: supportsRaytracing == YES): BLAS one-triangle
     * create + build + nonzero device address; one-instance TLAS sizes +
     * build through the VK-ABI record conversion. The fail-closed twin is
     * the next test (forced feature-bit clear). */
    static const f32 verts[9] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    static const u32 indices[3] = { 0u, 1u, 2u };
    RHIBuffer vb, ib, scratch, inst, tscratch;
    RHIBLASOneTriangleDesc d;
    RHIAccelerationStructureBuildSizes sizes;
    RHIAccelerationStructure blas, tlas;
    RHIAccelerationStructureDesc adesc;
    u64 addr;
    RHITLASInstanceDesc idesc;
    u8 rec[RHI_TLAS_INSTANCE_SIZE];
    RHICmdBuffer *cmd;
    if ((g_dev->capabilities.feature_bits &
         RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u) {
        /* This host cannot take the RT path; the fail-closed twin covers
         * the other branch. */
        return;
    }
    vb = make_data_buffer(RHI_BUFFER_USAGE_STORAGE, verts, sizeof(verts));
    ib = make_data_buffer(RHI_BUFFER_USAGE_STORAGE, indices,
                          sizeof(indices));
    ASSERT_FALSE(handle_is_null(vb));
    ASSERT_FALSE(handle_is_null(ib));
    memset(&d, 0, sizeof(d));
    d.vertex_buffer = vb;
    d.vertex_offset = 0u;
    d.vertex_count = 3u;
    d.vertex_stride = 12u;
    d.vertex_format = RHI_VERTEX_FORMAT_R32G32B32_SFLOAT;
    d.index_buffer = ib;
    d.index_offset = 0u;
    d.index_count = 3u;
    d.indexed = true;
    memset(&sizes, 0, sizeof(sizes));
    ASSERT_TRUE(rhi_blas_one_triangle_get_build_sizes(g_dev, &d, &sizes));
    ASSERT_TRUE(sizes.acceleration_structure_size > 0u);
    ASSERT_TRUE(sizes.build_scratch_size > 0u);
    memset(&adesc, 0, sizeof(adesc));
    adesc.type = RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL;
    adesc.storage_size = sizes.acceleration_structure_size;
    blas = rhi_acceleration_structure_create(g_dev, &adesc);
    ASSERT_FALSE(handle_is_null(blas));
    scratch = make_data_buffer(RHI_BUFFER_USAGE_STORAGE, NULL,
                               sizes.build_scratch_size);
    ASSERT_FALSE(handle_is_null(scratch));
    ASSERT_TRUE(rhi_build_blas_one_triangle(g_dev, blas, &d, scratch, 0u));
    addr = rhi_acceleration_structure_get_device_address(g_dev, blas);
    ASSERT_TRUE(addr != 0u);
    /* TLAS one instance with a NON-identity transform (review M1: an
     * identity matrix is transpose-invisible). */
    memset(&idesc, 0, sizeof(idesc));
    idesc.transform[0] = 2.0f;    /* non-uniform scale + translation */
    idesc.transform[5] = 3.0f;
    idesc.transform[10] = 4.0f;
    idesc.transform[3] = 10.0f;
    idesc.transform[7] = 20.0f;
    idesc.transform[11] = 30.0f;
    idesc.instance_mask = 0xFFu;
    ASSERT_TRUE(rhi_tlas_instance_encode(rec, sizeof(rec), addr, &idesc));
    inst = make_data_buffer(
        (RHIBufferUsage)(RHI_BUFFER_USAGE_STORAGE |
                         RHI_BUFFER_USAGE_DEVICE_ADDRESS),
        rec, sizeof(rec));
    ASSERT_FALSE(handle_is_null(inst));
    memset(&sizes, 0, sizeof(sizes));
    ASSERT_TRUE(rhi_tlas_one_instance_get_build_sizes(g_dev, inst, &sizes));
    ASSERT_TRUE(sizes.acceleration_structure_size > 0u);
    adesc.type = RHI_ACCELERATION_STRUCTURE_TOP_LEVEL;
    adesc.storage_size = sizes.acceleration_structure_size;
    tlas = rhi_acceleration_structure_create(g_dev, &adesc);
    ASSERT_FALSE(handle_is_null(tlas));
    tscratch = make_data_buffer(RHI_BUFFER_USAGE_STORAGE, NULL,
                                sizes.build_scratch_size);
    ASSERT_FALSE(handle_is_null(tscratch));
    ASSERT_TRUE(rhi_build_tlas_one_instance(g_dev, tlas, inst, tscratch, 0u));
    /* Bind on the compute path: legal call, no crash. */
    cmd = begin_frame();
    ASSERT_NOT_NULL(cmd);
    rhi_cmd_bind_acceleration_structure(cmd, tlas, 0u);
    end_frame();
    ASSERT_TRUE(rhi_device_idle(g_dev));
    rhi_acceleration_structure_destroy(g_dev, tlas);
    rhi_acceleration_structure_destroy(g_dev, blas);
    rhi_buffer_destroy(g_dev, vb);
    rhi_buffer_destroy(g_dev, ib);
    rhi_buffer_destroy(g_dev, scratch);
    rhi_buffer_destroy(g_dev, inst);
    rhi_buffer_destroy(g_dev, tscratch);
}

TEST(tlas_record_conversion_component_exact) {
    /* Review M1: component-level check of the VK-ABI -> MTL conversion
     * (transpose + unpacking), via the ENGINE_RHI_TEST hook. Non-uniform
     * scale + translation: columns[0]=(2,0,0) columns[1]=(0,3,0)
     * columns[2]=(0,0,4) columns[3]=(10,20,30). */
    RHIAccelerationStructureDesc adesc;
    RHIAccelerationStructure blas;
    u64 addr;
    RHITLASInstanceDesc idesc;
    u8 rec[RHI_TLAS_INSTANCE_SIZE];
    u8 out[68];
    const f32 *f = (const f32 *)out;
    const u32 *w = (const u32 *)(out + 48);
    if ((g_dev->capabilities.feature_bits &
         RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u) return;
    memset(&adesc, 0, sizeof(adesc));
    adesc.type = RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL;
    adesc.storage_size = 256u;
    blas = rhi_acceleration_structure_create(g_dev, &adesc);
    ASSERT_FALSE(handle_is_null(blas));
    addr = rhi_acceleration_structure_get_device_address(g_dev, blas);
    ASSERT_TRUE(addr != 0u);
    memset(&idesc, 0, sizeof(idesc));
    idesc.transform[0] = 2.0f;
    idesc.transform[5] = 3.0f;
    idesc.transform[10] = 4.0f;
    idesc.transform[3] = 10.0f;
    idesc.transform[7] = 20.0f;
    idesc.transform[11] = 30.0f;
    idesc.instance_custom_index = 0x123456u;
    idesc.instance_mask = 0xA5u;
    idesc.sbt_record_offset = 0x654321u;
    ASSERT_TRUE(rhi_tlas_instance_encode(rec, sizeof(rec), addr, &idesc));
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_test_metal_convert_tlas_record(g_dev, rec, out));
    /* columns[0] = (t0, t4, t8) — the transpose direction is asserted. */
    ASSERT_TRUE(f[0] == 2.0f && f[1] == 0.0f && f[2] == 0.0f);
    /* columns[1] = (t1, t5, t9) */
    ASSERT_TRUE(f[3] == 0.0f && f[4] == 3.0f && f[5] == 0.0f);
    /* columns[2] = (t2, t6, t10) */
    ASSERT_TRUE(f[6] == 0.0f && f[7] == 0.0f && f[8] == 4.0f);
    /* columns[3] = (t3, t7, t11) = translation */
    ASSERT_TRUE(f[9] == 10.0f && f[10] == 20.0f && f[11] == 30.0f);
    /* options(0) mask(A5) iftOffset(0x654321) asIndex(0) userID(0x123456) */
    ASSERT_EQ(w[0], 0u);
    ASSERT_EQ(w[1], 0xA5u);
    ASSERT_EQ(w[2], 0x654321u);
    ASSERT_EQ(w[3], 0u);
    ASSERT_EQ(w[4], 0x123456u);
    rhi_acceleration_structure_destroy(g_dev, blas);
}

TEST(acceleration_structure_fail_closed_when_feature_cleared) {
    /* Forced-branch simulation of a supportsRaytracing==NO host (the only
     * RT-capable machine in this plan is the M2): every RT entry point must
     * fail closed without crashing. */
    u32 saved = g_dev->capabilities.feature_bits;
    bool rt = (saved & RHI_FEATURE_ACCELERATION_STRUCTURE) != 0u;
    RHIAccelerationStructureDesc adesc;
    RHIAccelerationStructureBuildSizes sizes;
    RHIAccelerationStructure blas = RHI_HANDLE_NULL;
    RHIAccelerationStructure tlas = RHI_HANDLE_NULL;
    RHIBuffer vb = RHI_HANDLE_NULL, ib = RHI_HANDLE_NULL;
    RHIBuffer scratch = RHI_HANDLE_NULL, inst = RHI_HANDLE_NULL;
    RHIBLASOneTriangleDesc d;
    /* Prepare real handles while RT is on so the build gates are hit with
     * VALID handles (wrapper-level handle checks pass, the backend's
     * metal_rt_available gate is what must fail). */
    if (rt) {
        static const f32 verts[9] = { 0, 0, 0, 1, 0, 0, 0, 1, 0 };
        static const u32 indices[3] = { 0u, 1u, 2u };
        memset(&adesc, 0, sizeof(adesc));
        adesc.type = RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL;
        adesc.storage_size = 256u;
        blas = rhi_acceleration_structure_create(g_dev, &adesc);
        adesc.type = RHI_ACCELERATION_STRUCTURE_TOP_LEVEL;
        tlas = rhi_acceleration_structure_create(g_dev, &adesc);
        vb = make_data_buffer(RHI_BUFFER_USAGE_STORAGE, verts,
                              sizeof(verts));
        ib = make_data_buffer(RHI_BUFFER_USAGE_STORAGE, indices,
                              sizeof(indices));
        scratch = make_data_buffer(RHI_BUFFER_USAGE_STORAGE, NULL, 4096u);
        inst = make_data_buffer(
            (RHIBufferUsage)(RHI_BUFFER_USAGE_STORAGE |
                             RHI_BUFFER_USAGE_DEVICE_ADDRESS),
            NULL, (usize)RHI_TLAS_INSTANCE_SIZE);
    } else {
        inst = make_data_buffer(
            (RHIBufferUsage)(RHI_BUFFER_USAGE_STORAGE |
                             RHI_BUFFER_USAGE_DEVICE_ADDRESS),
            NULL, (usize)RHI_TLAS_INSTANCE_SIZE);
    }
    g_dev->capabilities.feature_bits &=
        ~(RHI_FEATURE_ACCELERATION_STRUCTURE | RHI_FEATURE_RAY_QUERY);
    memset(&adesc, 0, sizeof(adesc));
    adesc.type = RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL;
    adesc.storage_size = 256u;
    ASSERT_TRUE(handle_is_null(
        rhi_acceleration_structure_create(g_dev, &adesc)));
    memset(&sizes, 0, sizeof(sizes));
    ASSERT_FALSE(handle_is_null(inst));
    ASSERT_FALSE(rhi_tlas_one_instance_get_build_sizes(g_dev, inst, &sizes));
    ASSERT_TRUE(sizes.acceleration_structure_size == 0u);
    if (rt) {
        /* Review I2: every remaining entry point fails closed too. */
        memset(&d, 0, sizeof(d));
        d.vertex_buffer = vb;
        d.vertex_offset = 0u;
        d.vertex_count = 3u;
        d.vertex_stride = 12u;
        d.vertex_format = RHI_VERTEX_FORMAT_R32G32B32_SFLOAT;
        d.index_buffer = ib;
        d.index_offset = 0u;
        d.index_count = 3u;
        d.indexed = true;
        memset(&sizes, 0, sizeof(sizes));
        ASSERT_FALSE(rhi_blas_one_triangle_get_build_sizes(g_dev, &d,
                                                           &sizes));
        ASSERT_FALSE(rhi_build_blas_one_triangle(g_dev, blas, &d, scratch,
                                                 0u));
        ASSERT_FALSE(rhi_build_tlas_one_instance(g_dev, tlas, inst, scratch,
                                                 0u));
    }
    /* Bind must be a no-op (LOG_ERROR) even with a garbage handle — and
     * must not crash. */
    {
        RHICmdBuffer *cmd = begin_frame();
        RHIAccelerationStructure bogus;
        ASSERT_NOT_NULL(cmd);
        bogus.index = 0x7FFFu;
        bogus.generation = 0x7FFFu;
        rhi_cmd_bind_acceleration_structure(cmd, bogus, 0u);
        end_frame();
    }
    ASSERT_TRUE(rhi_device_idle(g_dev));
    if (rt) {
        rhi_acceleration_structure_destroy(g_dev, blas);
        rhi_acceleration_structure_destroy(g_dev, tlas);
        rhi_buffer_destroy(g_dev, vb);
        rhi_buffer_destroy(g_dev, ib);
        rhi_buffer_destroy(g_dev, scratch);
    }
    rhi_buffer_destroy(g_dev, inst);
    g_dev->capabilities.feature_bits = saved;
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
    RUN_TEST(pipeline_offscreen_fbo_draw_readback);
    RUN_TEST(fbo_bind_clears_default_and_bind_load_preserves);
    RUN_TEST(mrt_two_attachments_distinct_colors);
    RUN_TEST(mrt_five_attachments_create_and_clear);
    RUN_TEST(shadow_map_bind_clears_depth_to_one);
    RUN_TEST(shadow_depth_pipeline_vertex_only_shader);
    RUN_TEST(shadow_viewport_restricts_depth_writes);
    RUN_TEST(clear_depth_preserves_color);
    RUN_TEST(texel_buffers_cross_4096_texel_rows);
    RUN_TEST(texel_private_initial_upload_update_and_readback);
    RUN_TEST(pipeline_invalid_shader_handle_rejected);
    RUN_TEST(offscreen_fbo_msaa_desc_fails_closed);
    RUN_TEST(cubemap_depth_fbo_bind_face_clears);
    RUN_TEST(mrt_clear_color_after_bind_targets_mrt);
    RUN_TEST(r445_pipeline_overrides_sticky_depth_state);
    RUN_TEST(pass_switch_invalidates_bound_pipeline);
    RUN_TEST(compute_dispatch_writes_indices);
    RUN_TEST(buffer_size_constants_fed_to_kernel);
    RUN_TEST(fill_buffer_pattern_and_clamp_readback);
    RUN_TEST(screenshot_clear_color_and_post_present_refused);
    RUN_TEST(screenshot_rows_are_top_down);
    RUN_TEST(draw_indirect_executes_arg_buffer);
    RUN_TEST(draw_indexed_indirect_executes_arg_buffer);
    RUN_TEST(gpu_timer_roundtrip_smoke);
    RUN_TEST(gpu_timer_destroy_with_pending_sample_is_safe);
    RUN_TEST(manifest_real_shader_resolves);
    RUN_TEST(push_offsets_match_vk_golden);
    RUN_TEST(push_constants_out_of_range_dropped);
    RUN_TEST(set_uniform_mat4_column0_as_color);
    RUN_TEST(push_replays_across_blit_interlude);
    RUN_TEST(uniform_buffer_binds_and_replays_after_pass_switch);
    RUN_TEST(uniform_buffer_replays_with_pipeline_ubi_set_of_each_draw);
    RUN_TEST(acceleration_structure_lifecycle_and_tlas);
    RUN_TEST(tlas_record_conversion_component_exact);
    RUN_TEST(acceleration_structure_fail_closed_when_feature_cleared);
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
