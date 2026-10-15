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

static RHIShader make_shader(const char *msl, bool is_fragment) {
    /* Null-handle on failure; the caller asserts non-null. */
    return rhi_shader_create(g_dev, msl, (usize)strlen(msl), is_fragment);
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
    assert_center_px(px, 64u, 64u, 0u, 0u, 0u, 0u);      /* untouched */
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
    RHIShader cs = rhi_shader_create_compute(g_dev, k_msl_cs_write_index,
                                             (usize)strlen(k_msl_cs_write_index));
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
    RUN_TEST(pipeline_invalid_shader_handle_rejected);
    RUN_TEST(offscreen_fbo_msaa_desc_fails_closed);
    RUN_TEST(cubemap_depth_fbo_bind_face_clears);
    RUN_TEST(mrt_clear_color_after_bind_targets_mrt);
    RUN_TEST(r445_pipeline_overrides_sticky_depth_state);
    RUN_TEST(pass_switch_invalidates_bound_pipeline);
    RUN_TEST(compute_dispatch_writes_indices);
    RUN_TEST(fill_buffer_pattern_and_clamp_readback);
    RUN_TEST(screenshot_clear_color_and_post_present_refused);
    RUN_TEST(draw_indirect_executes_arg_buffer);
    RUN_TEST(draw_indexed_indirect_executes_arg_buffer);
    RUN_TEST(gpu_timer_roundtrip_smoke);
    RUN_TEST(gpu_timer_destroy_with_pending_sample_is_safe);
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
