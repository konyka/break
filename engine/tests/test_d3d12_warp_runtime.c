#include <rhi/rhi.h>
#include "test_framework.h"
/* Forces WARP via ENGINE_D3D12_WARP=1 (set in CTest ENVIRONMENT) so the
 * windows-d3d12 lane has a deterministic software GPU-runtime floor.
 * Evidence rule: WARP receipts are recorded with gpu=WARP and never
 * upgrade the evidence level past GPU-runtime. */
static RHIDevice *g_dev;

TEST(warp_device_identity_is_honest) {
    RHIDeviceInfo info;
    ASSERT_TRUE(rhi_device_get_info(g_dev, &info));
    ASSERT_EQ(info.backend, RHI_BACKEND_D3D12);
    /* WARP reports Microsoft Basic Render Driver; refuse to masquerade. */
    ASSERT_TRUE(strstr(info.device_name, "Basic Render") != NULL ||
                strstr(info.device_name, "WARP") != NULL);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);
}

/* R715-5: the offscreen FBO path is the next layer the demo needs, and the
 * only honest way to prove it works is pixels, not handle plumbing. Bind
 * clears to a caller-owned colour, unbind restores the swapchain target, and
 * the colour texture is read back and compared. */
TEST(offscreen_fbo_clear_round_trips_pixels) {
    RHIOffscreenFBODesc desc;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    const int expect[4] = { 64, 128, 191, 255 }; /* 0.25/0.5/0.75/1.0 */
    int c;
    memset(&desc, 0, sizeof(desc));
    desc.width = 8u;
    desc.height = 8u;
    desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));
    ASSERT_TRUE(rhi_handle_valid(fbo.color_tex));
    ASSERT_TRUE(rhi_handle_valid(fbo.depth_tex));
    ASSERT_EQ(fbo.width, 8u);
    ASSERT_EQ(fbo.height, 8u);
    ASSERT_EQ(fbo.sample_count, 1u);

    rhi_offscreen_fbo_set_clear_color(g_dev, &fbo, 0.25f, 0.5f, 0.75f, 1.0f);
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);     /* fresh bind clears */
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (c = 0; c < 4; ++c) {
        int diff = (int)px[c] - expect[c];
        if (diff < 0) diff = -diff;
        ASSERT_TRUE(diff <= 2);
    }
    /* The whole 8x8 must be cleared, not just the first pixel. */
    for (c = 4; c < (int)sizeof(px); c += 4) {
        ASSERT_EQ(px[c + 0], px[0]);
        ASSERT_EQ(px[c + 1], px[1]);
        ASSERT_EQ(px[c + 2], px[2]);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    ASSERT_FALSE(rhi_handle_valid(fbo.fb));
}

/* Isolate rasterisation from bindings: the probe sidecar declares no
 * registers and no uniform block, so a green triangle here proves pipeline
 * creation, FBO binding and draw submission work on their own. */
TEST(probe_triangle_rasterises_into_offscreen_fbo) {
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    int i;
    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "probe_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "probe_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs; pdesc.no_vertex_input = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        ASSERT_TRUE(px[i + 0] < 60);    /* R: not the clear colour */
        ASSERT_TRUE(px[i + 1] > 200);   /* G: the probe's green */
        ASSERT_TRUE(px[i + 2] < 60);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* Push constants + POSITION-only vertex input, no texture involved. The
 * quad is authored in NDC, so it can only rasterise if u_transform really
 * reached the shader - a dropped or zeroed root constant would collapse
 * every vertex onto the origin. A central square also proves the viewport
 * maps NDC onto the whole target rather than a corner sliver. */
TEST(push_constants_transform_reaches_the_shader) {
    static const float quad[6 * 3] = {
        -0.5f, -0.5f, 0.0f,  0.5f, -0.5f, 0.0f,  0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f
    };
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    int i;
    int green_px = 0;
    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "probe_vb_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "probe_vb_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 12u;   /* POSITION only */
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));
    i32 loc = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_transform");
    ASSERT_TRUE(loc >= 0);

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(quad);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = quad;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, (u32)loc, identity, sizeof(identity));
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4)
        if (px[i + 1] > 200) green_px++;
    /* Central half (NDC -0.5..0.5 over an 8px target) and not the corners. */
    ASSERT_TRUE(green_px > 0 && green_px < 64);
    ASSERT_TRUE(px[0 + 1] < 60);            /* corner 0 stays clear */
    ASSERT_TRUE(px[((7 * 8) + 7) * 4 + 1] < 60); /* opposite corner too */
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(blit_texture_binding_samples_red_into_offscreen_fbo) {
    static const unsigned char red[2 * 2 * 4] = {
        255, 0, 0, 255, 255, 0, 0, 255,
        255, 0, 0, 255, 255, 0, 0, 255
    };
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tex_desc;
    RHITexture tex;
    RHIShader vs, fs;
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    int i;
    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    memset(&tex_desc, 0, sizeof(tex_desc));
    tex_desc.width = 2u; tex_desc.height = 2u;
    tex_desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tex_desc.mip_levels = 1u;
    tex_desc.data = red;
    tex = rhi_texture_create(g_dev, &tex_desc);
    ASSERT_TRUE(rhi_handle_valid(tex));

    vs = rhi_shader_create(g_dev, "blit_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "blit_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs; pdesc.no_vertex_input = true;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, 0u, identity, sizeof(identity));
    rhi_cmd_bind_texture(cmd, tex, (RHISampler){0}, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        ASSERT_TRUE(px[i + 0] > 240);
        ASSERT_TRUE(px[i + 1] < 15);
        ASSERT_TRUE(px[i + 2] < 15);
        ASSERT_TRUE(px[i + 3] > 240);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, tex);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) return 77;
    printf("=== Running Tests ===\n");
    RUN_TEST(warp_device_identity_is_honest);
    RUN_TEST(offscreen_fbo_clear_round_trips_pixels);
    RUN_TEST(probe_triangle_rasterises_into_offscreen_fbo);
    RUN_TEST(push_constants_transform_reaches_the_shader);
    RUN_TEST(blit_texture_binding_samples_red_into_offscreen_fbo);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
