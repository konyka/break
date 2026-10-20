#include <rhi/rhi.h>
#include "test_framework.h"
/* Forces WARP via ENGINE_D3D12_WARP=1 (set in CTest ENVIRONMENT) so the
 * windows-d3d12 lane has a deterministic software GPU-runtime floor.
 * Evidence rule: WARP receipts are recorded with gpu=WARP and never
 * upgrade the evidence level past GPU-runtime. */
static RHIDevice *g_dev;

/* R600: u_camera_pos is no longer a push member — it rides the temporal CBV
 * at register b1, byte-identical to main.c's ForwardTemporalUbo and to the
 * GLSL ForwardTemporal block. Every blinn_phong draw here must publish it
 * through rhi_cmd_bind_uniform_buffer(cmd, ubo, 1); writing it as a uniform
 * would be a no-op now that resolve() returns -1, and a silently zeroed
 * camera is the exact failure this layout exists to make impossible. */
typedef struct {
    float cam_pos[3];
    float cam_pad;
    float prev_vp[16];
    float prev_model[16];
} WARPForwardTemporal;

static RHIBuffer warp_forward_temporal_create(RHIDevice *dev, float x, float y, float z)
{
    WARPForwardTemporal t;
    RHIBufferDesc desc;
    RHIBuffer ubo;
    memset(&t, 0, sizeof(t));
    t.cam_pos[0] = x; t.cam_pos[1] = y; t.cam_pos[2] = z;
    /* Identity prev_vp / prev_model: the non-MRT sidecar never reads them,
     * but the CBV is sized by the block, so it must carry them anyway. */
    t.prev_vp[0] = 1.0f; t.prev_vp[5] = 1.0f;
    t.prev_vp[10] = 1.0f; t.prev_vp[15] = 1.0f;
    t.prev_model[0] = 1.0f; t.prev_model[5] = 1.0f;
    t.prev_model[10] = 1.0f; t.prev_model[15] = 1.0f;
    memset(&desc, 0, sizeof(desc));
    desc.usage = RHI_BUFFER_USAGE_UNIFORM;
    desc.size = sizeof(t);
    desc.initial_data = &t;
    ubo = rhi_buffer_create(dev, &desc);
    return ubo;
}

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

/* Plan D Task 2: a GLSL path must resolve to its hand-authored HLSL sidecar
 * and the resulting pipeline must actually render. The name mapping itself is
 * a string table in test_d3d12_shader_contract; what only a live device can
 * prove is that a resolved handle carries real bytecode and drives a real
 * draw, so this binds a known red texture through rhi_cmd_bind_texture,
 * blits a fullscreen triangle into an 8x8 FBO and compares every pixel.
 *
 * Both path forms are asserted, because the amended brief requires the
 * primary mapping and the self-resolution to be equally load-bearing:
 * "shaders/blit.vert" is what the engine actually passes (GLSL in, sidecar
 * out), while "shaders/blit_hlsl.vert" is the form a caller already holding
 * the sidecar name would pass. Both pipelines must reflect the same
 * u_transform and both must produce the same red frame — otherwise a
 * regression that only breaks one form still shows up here. */
static void blit_path_draw(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo,
                           RHIPipeline pipe, RHITexture tex,
                           const float *identity) {
    rhi_offscreen_fbo_bind(cmd, fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, 0u, identity, 16u * sizeof(float));
    rhi_cmd_bind_texture(cmd, tex, (RHISampler){0}, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);          /* oversized triangle, no VBO */
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
}

TEST(shader_paths_resolve_to_blit_sidecars_and_render_red) {
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
    /* Form A: the GLSL path the engine passes, mapped onto the sidecar. */
    RHIShader vs_glsl, fs_glsl;
    /* Form B: the sidecar name itself, resolving to itself. */
    RHIShader vs_self, fs_self;
    RHIPipeline pipe_glsl, pipe_self;
    RHIPipelineDesc pdesc;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc_glsl, loc_self;
    int form;
    int i;

    vs_glsl = rhi_shader_create_path(g_dev, "shaders/blit.vert", false);
    fs_glsl = rhi_shader_create_path(g_dev, "shaders/blit.frag", true);
    vs_self = rhi_shader_create_path(g_dev, "shaders/blit_hlsl.vert", false);
    fs_self = rhi_shader_create_path(g_dev, "shaders/blit_hlsl.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs_glsl));
    ASSERT_TRUE(rhi_handle_valid(fs_glsl));
    ASSERT_TRUE(rhi_handle_valid(vs_self));
    ASSERT_TRUE(rhi_handle_valid(fs_self));

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

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.no_vertex_input = true;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.vert = vs_glsl; pdesc.frag = fs_glsl;
    pipe_glsl = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe_glsl));
    pdesc.vert = vs_self; pdesc.frag = fs_self;
    pipe_self = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe_self));

    /* Reflection is the cheapest proof the handles carry the real blit
     * sidecar rather than a stub that happens to have a valid slot: only
     * blit_hlsl.vert declares u_transform. Absolute first — blit_hlsl.vert
     * pins it at byte offset 0 (`// rhi:uniform u_transform 0`), so a
     * relative-only check would still pass if both forms resolved to the
     * same wrong shader. Identical offsets then show both forms agree. */
    loc_glsl = rhi_pipeline_get_uniform_location(g_dev, pipe_glsl, "u_transform");
    loc_self = rhi_pipeline_get_uniform_location(g_dev, pipe_self, "u_transform");
    ASSERT_EQ(loc_glsl, 0);
    ASSERT_EQ(loc_self, 0);
    ASSERT_EQ(loc_glsl, loc_self);

    for (form = 0; form < 2; ++form) {
        RHIPipeline pipe = form == 0 ? pipe_glsl : pipe_self;
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        blit_path_draw(cmd, &fbo, pipe, tex, identity);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

        /* A fresh bind cleared the target, so every pixel must come from the
         * sampled red texture: a shader that failed to run would leave the
         * clear colour behind. */
        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (i = 0; i < (int)sizeof(px); i += 4) {
            ASSERT_TRUE(px[i + 0] > 240);
            ASSERT_TRUE(px[i + 1] < 15);
            ASSERT_TRUE(px[i + 2] < 15);
            ASSERT_TRUE(px[i + 3] > 240);
        }
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    }

    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, tex);
    rhi_pipeline_destroy(g_dev, pipe_glsl);
    rhi_pipeline_destroy(g_dev, pipe_self);
    rhi_shader_destroy(g_dev, vs_glsl);
    rhi_shader_destroy(g_dev, fs_glsl);
    rhi_shader_destroy(g_dev, vs_self);
    rhi_shader_destroy(g_dev, fs_self);
}

/* Sidecar Task 2: the first REAL renderer pipeline on D3D12, proven with
 * pixels. Two independent claims are under test.
 *
 * (1) Offset resolution. The sidecar publishes its layout through
 * `// rhi:uniform <name> <byte offset>` markers, and the D3D12 backend turns
 * those markers into the name -> byte-offset table behind
 * rhi_pipeline_get_uniform_location (rhi_d3d12.c:2824-2827 reads the VS and
 * PS sources into one table). Asserting the numbers proves the markers parse;
 * it does NOT prove the values written at those offsets reach the shader. The
 * second draw below closes that gap by writing a distinct colour through
 * u_ambient and reading it back out of the pixels.
 *
 * (2) Shading. Every one of the 64 pixels must equal the sampled albedo,
 * which only happens when model/view/proj are identity, the texture is bound
 * at unit 0, and every lighting uniform landed where the sidecar says.
 *
 * Degenerate-lighting analysis — why these exact uniform values:
 * The GLSL reduces to `albedo * (u_ambient + u_light_color * diff) +
 * u_light_color * spec * 0.15`. This test picks geometry that zeroes BOTH
 * lighting terms on its own, so the expected colour is the albedo regardless
 * of the specular exponent (the sidecar follows the GLSL's five squarings,
 * exponent 32, not the plan prose's "spec^8"):
 *
 *   N = (0,0,1)  — every vertex carries it, so it interpolates constant and
 *                  normalize() is a no-op.
 *   u_light_dir = (0,-1,0) -> L = (0,1,0).
 *   diff = max(dot(N,L),0) = max(0,0) = 0.
 *   V = normalize(u_camera_pos - world) with u_camera_pos = (0,0,-10) and the
 *   triangle on the z=0 plane, so V.z = -10/len < 0 strictly and V is never
 *   zero-length. H = normalize(L + V) then has H.z = V.z/|L+V| < 0, so
 *   spec = max(dot(N,H),0) = max(negative,0) = 0.
 *
 * Two NaN hazards this deliberately avoids, because NaN propagates through
 * multiplication and 0 * NaN is NaN (so a zero light colour would NOT rescue
 * a broken H):
 *   - u_camera_pos coinciding with a vertex/pixel would make normalize(0).
 *     The camera sits at z=-10, ten units from the geometry, and no vertex is
 *     near it.
 *   - L = -V at any point would make L+V = 0 and H = normalize(0). The
 *     viewport-centre pixel is world (0,0,0); with L = (0,0,1) (the obvious
 *     "light straight on" choice, u_light_dir = (0,0,-1)) V is exactly (0,0,-1)
 *     there and H IS NaN. Choosing L = (0,1,0) makes (L+V).z strictly
 *     negative for every pixel, so no P of the triangle can degenerate.
 *
 * Because spec is zero by construction and not by a zero multiplier,
 * u_light_color is deliberately left NON-ZERO at (1,1,1). If the specular
 * term were ever reachable here the colour would shift and the test would go
 * red; the same for a mis-resolved u_light_dir.
 *
 * Push-constant sizing: this pipeline's root signature spends one DWORD on
 * the t0 SRV descriptor table, and the D3D12 root-signature budget is 64
 * DWORDs total (rhi_d3d12.c:2559-2562), so the constants param is clamped to
 * 63 DWORDs = 252 bytes — four short of the 256-byte graphics contract. Every
 * uniform here is therefore written with the 12-byte vec3 / 64-byte mat4
 * setters, never a padded 16-byte copy: a 16-byte write at offset 240 would
 * end at 256, fail rhi_push_helper_range_ok, and be dropped with a warning
 * while the shader still read whatever was left in the staging buffer.
 * u_camera_pos + 12 = 252 lands exactly on that boundary. */
TEST(blinn_phong_sidecar_resolves_offsets_and_shades_red) {
    /* pos3, normal3, uv2 = 32B stride, matching RHIPipelineDesc's mesh
     * layout. An oversized NDC triangle so all 64 pixels are covered; the
     * oversized UVs are harmless on a uniformly-coloured 2x2 texture with the
     * engine's static WRAP sampler. */
    static const float verts[3 * 8] = {
        /*  pos                 normal          uv     */
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         3.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
        -1.0f,  3.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f
    };
    static const unsigned char red[2 * 2 * 4] = {
        255, 0, 0, 255,   255, 0, 0, 255,
        255, 0, 0, 255,   255, 0, 0, 255
    };
    static const unsigned char white[2 * 2 * 4] = {
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255
    };
    /* Colume-major, matching HLSL's default float4x4 packing: index = col*4 + row. */
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tex_desc;
    RHITexture red_tex, white_tex;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    /* The contract: the engine resolves these names for blinn_phong on every
     * backend, and the Vulkan twin test pins the same numbers. R600:
     * u_camera_pos is NO LONGER one of them — it moved into the temporal
     * CBV at b1, so it must resolve -1. Pinning -1 (rather than dropping
     * the name) is the point: a stale 240 here is how the camera would
     * silently vanish from the push block again. */
    static const char *const names[7] = {
        "u_model", "u_view", "u_proj", "u_light_dir",
        "u_light_color", "u_ambient", "u_camera_pos"
    };
    static const i32 expected[7] = { 0, 64, 128, 192, 208, 224, -1 };
    i32 loc[7];
    RHIBuffer temporal_ubo;
    int i;

    /* Form A only: the GLSL paths the engine itself passes, mapped onto the
     * sidecars. The self-referential "_hlsl" form is already covered for blit
     * by shader_paths_resolve_to_blit_sidecars_and_render_red. */
    vs = rhi_shader_create_path(g_dev, "shaders/blinn_phong.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/blinn_phong.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

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
    red_tex = rhi_texture_create(g_dev, &tex_desc);
    ASSERT_TRUE(rhi_handle_valid(red_tex));
    tex_desc.data = white;
    white_tex = rhi_texture_create(g_dev, &tex_desc);
    ASSERT_TRUE(rhi_handle_valid(white_tex));

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 32u;    /* pos3 + normal3 + uv2 */
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;   /* also disables the depth test */
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 7; ++i) {
        loc[i] = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (loc[i] != expected[i]) {
            printf("FAIL: %s resolved to %d, expected %d\n",
                   names[i], (int)loc[i], (int)expected[i]);
        }
        ASSERT_EQ(loc[i], expected[i]);
    }

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));
    temporal_ubo = warp_forward_temporal_create(g_dev, 0.0f, 0.0f, -10.0f);
    ASSERT_TRUE(rhi_handle_valid(temporal_ubo));

    /* Draw 1: red albedo, white ambient -> every pixel is exactly the albedo. */
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, loc[0], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[1], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[2], identity);
    rhi_cmd_set_uniform_vec3(cmd, loc[3],  0.0f, -1.0f, 0.0f); /* u_light_dir */
    rhi_cmd_set_uniform_vec3(cmd, loc[4],  1.0f,  1.0f, 1.0f); /* u_light_color */
    rhi_cmd_set_uniform_vec3(cmd, loc[5],  1.0f,  1.0f, 1.0f); /* u_ambient */
    rhi_cmd_bind_uniform_buffer(cmd, temporal_ubo, 1u);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_bind_texture(cmd, red_tex, (RHISampler){0}, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    /* A fresh bind cleared the target, so every pixel must come from the
     * shader. Exact equality, not a tolerance: the whole expression is
     * (1,0,0) * ((1,1,1) + 0) + 0, so any deviation is a real defect. */
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        ASSERT_EQ(px[i + 0], 255);
        ASSERT_EQ(px[i + 1], 0);
        ASSERT_EQ(px[i + 2], 0);
        ASSERT_EQ(px[i + 3], 255);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    /* Draw 2: the offset markers could resolve to the right numbers while the
     * struct behind them disagrees, in which case the write would land on the
     * wrong member. A white albedo makes u_ambient the only contributor, so
     * u_ambient = (0,1,0) must come out green — proof that the value written
     * at byte 224 is the value the fragment shader reads. */
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, loc[0], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[1], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[2], identity);
    rhi_cmd_set_uniform_vec3(cmd, loc[3],  0.0f, -1.0f, 0.0f);
    rhi_cmd_set_uniform_vec3(cmd, loc[4],  1.0f,  1.0f,  1.0f);
    rhi_cmd_set_uniform_vec3(cmd, loc[5],  0.0f,  1.0f,  0.0f); /* green ambient */
    rhi_cmd_bind_uniform_buffer(cmd, temporal_ubo, 1u);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_bind_texture(cmd, white_tex, (RHISampler){0}, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        ASSERT_EQ(px[i + 0], 0);
        ASSERT_EQ(px[i + 1], 255);
        ASSERT_EQ(px[i + 2], 0);
        ASSERT_EQ(px[i + 3], 255);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, red_tex);
    rhi_texture_destroy(g_dev, white_tex);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, temporal_ubo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* Material binder Task 1+2: the REAL binder path, not a hand-placed
 * rhi_cmd_bind_texture. Three draws, three claims:
 *
 *  1. rhi_cmd_bind_material_textures puts albedo on texture unit 0, which is
 *     what lands on register t0 — the register the blinn_phong sidecar's
 *     `Texture2D g_albedo : register(t0)` reads. The five invalid handles
 *     travel the same call and take the fallback path, so this is the exact
 *     call the engine's forward pass makes.
 *  2. The fallback is not a no-op: a D3D12 root descriptor table left unwritten
 *     still samples whatever the last draw put in that descriptor slot, so the
 *     binder substitutes a 1x1 white texture for an invalid handle. Draw 2
 *     inverts the argument to prove the substitution happens: an INVALID
 *     albedo must come out exactly white, never the clear colour and never
 *     the previous frame's descriptor.
 *  3. Draw 3 drives the same frame through rhi_cmd_bind_material_textures_ibl,
 *     the entry point the engine actually calls, with a red albedo and four
 *     INVALID point-shadow cubes. The cubes are gated on being live cubes and
 *     must be skipped outright (a 2D descriptor on a samplerCube register is
 *     a type mismatch), and the draw must still come out exactly red: neither
 *     the gating nor the other eleven IBL slots may disturb t0.
 *
 * PROVEN BOUNDARY — read this before quoting the coverage. Only unit 0 is
 * observable in these pixels. The blinn_phong sidecar declares t0 and nothing
 * else, and rhi_cmd_bind_texture skips a register the pipeline does not
 * declare, so units 1-15 are structurally invisible here: this test proves the
 * unit map's ALBEDO entry (and the fallback rule, through albedo) and proves
 * that the other entries do not disturb it. It does NOT prove that shadow is
 * on 1, mr on 2, or ssao on 14 — those rest on the map mirroring the GL
 * binder and on review, not on a pixel. Proving them needs sidecars that
 * declare those registers.
 *
 * The colours are exact, not approximate: with the degenerate lighting used
 * by the sibling blinn_phong test (diff = 0 and spec = 0 by construction, see
 * that test's header), the shader reduces to albedo * u_ambient with
 * u_ambient = (1,1,1). Any other value can only come from a different
 * descriptor having been sampled. */
TEST(material_binder_puts_albedo_on_t0_and_falls_back_to_white) {
    static const float verts[3 * 8] = {
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         3.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
        -1.0f,  3.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f
    };
    static const unsigned char red[2 * 2 * 4] = {
        255, 0, 0, 255,   255, 0, 0, 255,
        255, 0, 0, 255,   255, 0, 0, 255
    };
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tex_desc;
    RHITexture red_tex;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    static const char *const names[7] = {
        "u_model", "u_view", "u_proj", "u_light_dir",
        "u_light_color", "u_ambient", "u_camera_pos"
    };
    /* Four invalid handles standing in for u_point_shadow_cubes[4]: the IBL
     * binder must skip those slots rather than substitute a 2D texture,
     * because the shaders declare samplerCube. */
    RHITexture cubes[4] = { RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                            RHI_HANDLE_NULL, RHI_HANDLE_NULL };
    i32 loc[7];
    RHIBuffer temporal_ubo;
    int i;

    vs = rhi_shader_create_path(g_dev, "shaders/blinn_phong.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/blinn_phong.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

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
    red_tex = rhi_texture_create(g_dev, &tex_desc);
    ASSERT_TRUE(rhi_handle_valid(red_tex));

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 32u;    /* pos3 + normal3 + uv2 */
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    /* R600: u_camera_pos is the one name that must NOT resolve — it lives
     * in the temporal CBV now. Asserting -1 is what keeps the push block
     * from quietly growing a camera back into the 248-byte tail. */
    for (i = 0; i < 7; ++i) {
        loc[i] = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (strcmp(names[i], "u_camera_pos") == 0) {
            ASSERT_EQ(loc[i], -1);
        } else {
            ASSERT_TRUE(loc[i] >= 0);
        }
    }

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));
    temporal_ubo = warp_forward_temporal_create(g_dev, 0.0f, 0.0f, -10.0f);
    ASSERT_TRUE(rhi_handle_valid(temporal_ubo));

    /* Draw 1: red albedo on unit 0, every other material map invalid. */
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, loc[0], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[1], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[2], identity);
    rhi_cmd_set_uniform_vec3(cmd, loc[3],  0.0f, -1.0f, 0.0f);
    rhi_cmd_set_uniform_vec3(cmd, loc[4],  1.0f,  1.0f, 1.0f);
    rhi_cmd_set_uniform_vec3(cmd, loc[5],  1.0f,  1.0f, 1.0f);
    rhi_cmd_bind_uniform_buffer(cmd, temporal_ubo, 1u);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_bind_material_textures(cmd, red_tex,
                                   RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                   RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                   RHI_HANDLE_NULL, (RHISampler){0});
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        ASSERT_EQ(px[i + 0], 255);
        ASSERT_EQ(px[i + 1], 0);
        ASSERT_EQ(px[i + 2], 0);
        ASSERT_EQ(px[i + 3], 255);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    /* Draw 2: invalid albedo. Unit 0 must now resolve to the shared 1x1
     * white fallback, so the same shader with the same uniforms comes out
     * exactly white — proof the descriptor was written rather than left
     * holding draw 1's red SRV. */
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, loc[0], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[1], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[2], identity);
    rhi_cmd_set_uniform_vec3(cmd, loc[3],  0.0f, -1.0f, 0.0f);
    rhi_cmd_set_uniform_vec3(cmd, loc[4],  1.0f,  1.0f, 1.0f);
    rhi_cmd_set_uniform_vec3(cmd, loc[5],  1.0f,  1.0f, 1.0f);
    rhi_cmd_bind_uniform_buffer(cmd, temporal_ubo, 1u);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_bind_material_textures(cmd, RHI_HANDLE_NULL,
                                   RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                   RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                   RHI_HANDLE_NULL, (RHISampler){0});
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        ASSERT_EQ(px[i + 0], 255);
        ASSERT_EQ(px[i + 1], 255);
        ASSERT_EQ(px[i + 2], 255);
        ASSERT_EQ(px[i + 3], 255);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    /* Draw 3: the IBL entry point the engine actually calls. A red albedo
     * must still reach t0 through it, and the four invalid point-shadow
     * cubes (units 10-13) must be skipped rather than handed a 2D
     * descriptor — they declare samplerCube, and there is no cube on D3D12
     * yet for the binder to bind. */
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, loc[0], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[1], identity);
    rhi_cmd_set_uniform_mat4(cmd, loc[2], identity);
    rhi_cmd_set_uniform_vec3(cmd, loc[3],  0.0f, -1.0f, 0.0f);
    rhi_cmd_set_uniform_vec3(cmd, loc[4],  1.0f,  1.0f, 1.0f);
    rhi_cmd_set_uniform_vec3(cmd, loc[5],  1.0f,  1.0f, 1.0f);
    rhi_cmd_bind_uniform_buffer(cmd, temporal_ubo, 1u);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_bind_material_textures_ibl(cmd, red_tex,
                                       RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                       RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                       RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                       (RHISampler){0}, RHI_HANDLE_NULL,
                                       RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                       cubes, 4u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        ASSERT_EQ(px[i + 0], 255);
        ASSERT_EQ(px[i + 1], 0);
        ASSERT_EQ(px[i + 2], 0);
        ASSERT_EQ(px[i + 3], 255);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, red_tex);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, temporal_ubo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* R605 / plan step 5: does the MRT sidecar actually put the motion vector in
 * RT1, and is it the value the matrices imply?
 *
 * The velocity is not a constant, so "every pixel equals X" does not apply.
 * With identity model/view/proj the vertex stage computes
 *
 *     curr = (x, y, 0, 1)                    so curr_ndc = (x, y)
 *     prev = u_prev_vp * u_prev_model * pos   so prev_ndc = (sx, ty)
 *     velocity = ((1 - sx) * x, (1 - ty) * y)
 *
 * for a diagonal u_prev_vp of scale (sx, ty) and identity u_prev_model.
 *
 * Every assertion below is INDEPENDENT of which way the target is stored,
 * which is deliberate: a test that had to know the pixel->NDC mapping would
 * be asserting the viewport transform instead of the velocity, and would
 * pass for the wrong reason.
 *
 *   Draw A (sx=sy=1)  velocity is exactly (0, 0) -- asserted on the RAW
 *                      16-bit patterns, so "approximately zero" cannot pass.
 *   Draw B (sx=2, sy=1) velocity.y is exactly 0 on every pixel while
 *                      velocity.x varies and takes both signs. One channel
 *                      pinned to a hard zero while the other is live is what
 *                      a correct per-channel read looks like.
 *
 * RT0 is checked on every draw: the camera rides the b1 temporal CBV now,
 * and RT0 must still come out exactly red, which is the regression guard on
 * that move.
 *
 * This test is also the one that could not exist before R605: reading
 * u_prev_vp / u_prev_model in the vertex stage used to resolve to a root
 * parameter that was never bound, so the velocity was garbage (NaN) no
 * matter what the matrices said. */




/* IEEE-754 binary16 -> float, for reading back the R16G16_SFLOAT velocity
 * attachment. Never shift by a negative count: most of a screen's NDC values
 * sit below 1.0 and land on exp < 15, which is where 1u << (exp - 15) is
 * undefined behaviour and silently produced garbage that read exactly like a
 * broken shader. */
static float warp_half_to_float(unsigned short h)
{
    unsigned int sign = (unsigned int)(h >> 15) & 1u;
    int exp = (int)((h >> 10) & 0x1fu);
    unsigned int frac = (unsigned int)(h & 0x3ffu);
    float mag;
    float scale = 1.0f;
    if (exp == 0) {
        mag = (float)frac * (1.0f / 16777216.0f);          /* subnormal */
    } else if (exp == 31) {
        mag = frac ? (0.0f / 0.0f) : (1.0f / 0.0f);       /* inf / NaN */
    } else {
        if (exp > 15) scale = (float)(1u << (unsigned int)(exp - 15));
        else if (exp < 15) scale = 1.0f / (float)(1u << (unsigned int)(15 - exp));
        mag = scale * (1.0f + (float)frac / 1024.0f);
    }
    return sign ? -mag : mag;
}

TEST(blinn_phong_mrt_sidecar_writes_velocity_to_rt1)
{
    /* Oversized triangle covering the whole 8x8 target; normals all (0,0,1)
     * and the sibling blinn test's degenerate lighting zeroes diff and spec,
     * so RT0 is the albedo regardless. */
    static const float verts[3 * 8] = {
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         3.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
        -1.0f,  3.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f
    };
    static const unsigned char red[2 * 2 * 4] = {
        255, 0, 0, 255,   255, 0, 0, 255,
        255, 0, 0, 255,   255, 0, 0, 255
    };
    /* Column-major: index = col*4 + row. Diagonal scale (sx, sy, 1, 1). */
    static const float identity[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    static const float scale_x2[16]   = {2,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    const RHIFormat formats[2] = {RHI_FORMAT_R8G8B8A8_UNORM, RHI_FORMAT_R16G16_SFLOAT};
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHITextureDesc tex_desc;
    RHITexture red_tex;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHIBuffer temporal_ubo;
    RHICmdBuffer *cmd;
    unsigned char rt0[8 * 8 * 4];
    unsigned short rt1[8 * 8 * 2];
    float min_x, max_x;
    int draw, i;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));
    ASSERT_EQ(fbo.attachment_count, 2u);
    ASSERT_TRUE(rhi_handle_valid(fbo.color_tex[1]));

    vs = rhi_shader_create_path(g_dev, "shaders/blinn_phong_mrt.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/blinn_phong_mrt.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&tex_desc, 0, sizeof(tex_desc));
    tex_desc.width = 2u; tex_desc.height = 2u;
    tex_desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tex_desc.mip_levels = 1u;
    tex_desc.data = red;
    red_tex = rhi_texture_create(g_dev, &tex_desc);
    ASSERT_TRUE(rhi_handle_valid(red_tex));

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 32u;    /* pos3 + normal3 + uv2 */
    pdesc.uses_textures = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_attachment_count = 2u;
    pdesc.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    /* R600: u_camera_pos is NOT a push member any more. Pin -1 rather than
     * dropping the name -- a stale 240 is how the camera would slip back
     * into the 248-byte tail. */
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_ambient"), 224);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_camera_pos"), -1);

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));
    temporal_ubo = warp_forward_temporal_create(g_dev, 0.0f, 0.0f, -10.0f);
    ASSERT_TRUE(rhi_handle_valid(temporal_ubo));

    for (draw = 0; draw < 2; ++draw) {
        const float *prev_vp = (draw == 0) ? identity : scale_x2;
        WARPForwardTemporal temporal;
        RHIBufferDesc ubo_desc;
        memset(&temporal, 0, sizeof(temporal));
        temporal.cam_pos[2] = -10.0f;
        memcpy(temporal.prev_vp, prev_vp, sizeof(temporal.prev_vp));
        temporal.prev_model[0] = 1.0f; temporal.prev_model[5] = 1.0f;
        temporal.prev_model[10] = 1.0f; temporal.prev_model[15] = 1.0f;
        memset(&ubo_desc, 0, sizeof(ubo_desc));
        (void)ubo_desc;
        rhi_buffer_update(g_dev, temporal_ubo, &temporal, sizeof(temporal));

        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_mrt_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_set_uniform_mat4(cmd, 128, identity);
        rhi_cmd_set_uniform_vec3(cmd, 192, 0.0f, -1.0f, 0.0f);
        rhi_cmd_set_uniform_vec3(cmd, 208, 1.0f, 1.0f, 1.0f);
        rhi_cmd_set_uniform_vec3(cmd, 224, 1.0f, 1.0f, 1.0f);
        rhi_cmd_bind_uniform_buffer(cmd, temporal_ubo, 1u);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_bind_texture(cmd, red_tex, (RHISampler){0}, 0u);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_mrt_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        /* RT0 must be exactly the albedo on every draw -- the temporal CBV
         * move must not have disturbed the colour path. */
        memset(rt0, 0, sizeof(rt0));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], rt0, sizeof(rt0)));
        for (i = 0; i < (int)sizeof(rt0); i += 4) {
            ASSERT_EQ(rt0[i + 0], 255);
            ASSERT_EQ(rt0[i + 1], 0);
            ASSERT_EQ(rt0[i + 2], 0);
            ASSERT_EQ(rt0[i + 3], 255);
        }

        memset(rt1, 0, sizeof(rt1));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], rt1, sizeof(rt1)));
        min_x = 1e30f; max_x = -1e30f;
        for (i = 0; i < 64; ++i) {
            float vx = warp_half_to_float(rt1[i * 2 + 0]);
            float vy = warp_half_to_float(rt1[i * 2 + 1]);
            if (draw == 0) {
                /* Exactly +0.0 in both channels, on the raw bits. */
                ASSERT_EQ(rt1[i * 2 + 0], 0u);
                ASSERT_EQ(rt1[i * 2 + 1], 0u);
            } else {
                ASSERT_EQ(rt1[i * 2 + 1], 0u);
            }
            if (vx < min_x) min_x = vx;
            if (vx > max_x) max_x = vx;
            (void)vy;
        }
        if (draw == 1) {
            /* curr_ndc lives in [-1, 1]; anything outside means the divide by
             * w or the perspective mapping is wrong. */
            ASSERT_TRUE(min_x < 0.0f);
            ASSERT_TRUE(max_x > 0.0f);
            ASSERT_TRUE(min_x >= -1.01f);
            ASSERT_TRUE(max_x <= 1.01f);
        }
    }

    rhi_mrt_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, red_tex);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, temporal_ubo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}


/* R441 on D3D12: does the material-array sidecar actually carry the draw's
 * instance index all the way into the sampled texel?
 *
 * "The picture is not black" would prove nothing here: a sampler2DArray bound
 * to layer 0 renders fine whether or not SV_InstanceID was forwarded at all.
 * So the array is built so that the layer INDEX is the only thing that decides
 * the colour, and every pixel is asserted against the colour its own layer
 * must produce.
 *
 *   layer 0 -> RGBA (255,   0,   0, 255)   pure red
 *   layer 1 -> RGBA (  0, 255,   0, 255)   pure green
 *   layer 2 -> RGBA (  0,   0, 255, 255)   pure blue
 *
 * Three layers, not two, because "0 vs non-zero" is exactly what a dropped
 * SV_InstanceID degrades to, and a two-layer test cannot tell a correct index
 * from a hard-wired 1. Frame 0 puts layers 1 and 2 side by side in ONE image;
 * frame 1 pins layer 0 on its own. A shader that forwarded anything other than
 * the exact index fails one of the two.
 *
 * Geometry — two triangles that tile the whole 8x8 target along the seam
 *
 *     L(x) = -0.075 - 0.9375 * x
 *
 * vertices 0..2 = (-1.2,-1.2) (1.2,-1.2) (-1.2, 1.05)   covers y <  L(x)
 * vertices 3..5 = ( 1.2,-1.2) ( 1.2,1.05) (-1.2, 1.05)   covers y >= L(x)
 *
 * The seam was picked so that NO pixel centre lands on it: the 8x8 target's
 * centres are +-0.125, +-0.375, +-0.625, +-0.875, and L evaluated at those x
 * takes no centre value for a centre y. The closest approach is at x = 0,
 * where L = -0.075 sits 0.175 NDC = 0.7 px from the nearest centre row. Both
 * triangles therefore yield an unambiguous expected layer per pixel, which is
 * what lets the assertions be exact rather than "one of the two".
 *
 * Shading is the sibling blinn_phong_sidecar test's degenerate-lighting setup,
 * reused verbatim: every normal is (0,0,1) and every vertex is on the z = 0
 * plane, so with u_light_dir = (0,-1,0) -> L = (0,1,0), diff = max(dot(N,L),0)
 * = 0; and with the camera at (0,0,-10) on the b1 temporal CBV, V.z < 0 at
 * every pixel, so H.z < 0 and spec = 0. The GLSL reduces to
 * albedo * (u_ambient + 0) + 0, and u_ambient is (1,1,1), so RT0 is EXACTLY
 * the layer's texel. A mis-resolved u_ambient or u_light_dir would shift the
 * colour, not merely darken it, and turn this red.
 *
 * WHY THE INSTANCE INDEX AND NOT THE INDIRECT first_instance.
 * blinn_phong_arr.vert reads gl_BaseInstanceARB, and the sidecar reads
 * SV_InstanceID, whose D3D12 source is the draw's StartInstanceLocation. On
 * this host that path is NOT observable: a single ExecuteIndirect record
 * {VertexCount=6, InstanceCount=1, StartVertexLocation=0,
 * StartInstanceLocation=1} against this very pipeline and this very shader
 * renders layer 0, while the same record with InstanceCount = 3 renders layer
 * 2 — i.e. WARP takes SV_InstanceID from InstanceCount and drops
 * StartInstanceLocation. (The args buffer was read back with
 * rhi_buffer_read to rule out a stale upload, and ExecuteIndirect now
 * transitions its argument buffer into D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT
 * as the API requires; neither changes the outcome.) So the pixel proof drives
 * SV_InstanceID through InstanceCount, which is the register the sidecar
 * actually reads, and leaves the first_instance route — the one production
 * uses — asserted at the ABI level instead. The DXIL for this vertex stage
 * disassembles to a single dx.op.loadInput on inputSigId 4 (SV_InstanceID),
 * which is the same instruction gl_BaseInstance lowers to.
 *
 * RT1 is checked on every frame as raw 16-bit patterns: identity model, view,
 * proj AND identity prev_vp / prev_model make the motion vector exactly
 * (+0.0, +0.0), so "approximately zero" cannot pass, and a layer read that
 * corrupted the interpolants would show up here too. */
TEST(blinn_phong_arr_sidecar_forwards_the_layer_into_pixels)
{
    static const float verts[6 * 8] = {
        /*  pos                    normal        uv  */
        -1.2f, -1.2f,  0.00f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         1.2f, -1.2f,  0.00f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
        -1.2f,  1.05f, 0.00f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f,
         1.2f, -1.2f,  0.00f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
         1.2f,  1.05f, 0.00f,   0.0f, 0.0f, 1.0f,   2.0f, 2.0f,
        -1.2f,  1.05f, 0.00f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f
    };
    /* 2x2 is enough: each layer is one flat colour and the oversized UVs only
     * need the WRAP sampler the root signature's static sampler already is. */
    static const unsigned char layer_red[2 * 2 * 4] = {
        255, 0, 0, 255,   255, 0, 0, 255,
        255, 0, 0, 255,   255, 0, 0, 255
    };
    static const unsigned char layer_green[2 * 2 * 4] = {
        0, 255, 0, 255,   0, 255, 0, 255,
        0, 255, 0, 255,   0, 255, 0, 255
    };
    static const unsigned char layer_blue[2 * 2 * 4] = {
        0, 0, 255, 255,   0, 0, 255, 255,
        0, 0, 255, 255,   0, 0, 255, 255
    };
    /* Column-major: index = col*4 + row. */
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    static const unsigned char expect[3][4] = {
        { 255,   0,   0, 255 },
        {   0, 255,   0, 255 },
        {   0,   0, 255, 255 }
    };
    const RHIFormat formats[2] = {
        RHI_FORMAT_R8G8B8A8_UNORM, RHI_FORMAT_R16G16_SFLOAT
    };
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHITexture albedo_array;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHIBuffer temporal_ubo;
    RHICmdBuffer *cmd;
    unsigned char rt0[8 * 8 * 4];
    unsigned short rt1[8 * 8 * 2];
    int frame;
    int row, col, i;
    int layer0_px = 0, layer1_px = 0, layer2_px = 0;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));
    ASSERT_EQ(fbo.attachment_count, 2u);

    /* Form A: the GLSL paths main.c passes on the D3D12 sidecar route. */
    vs = rhi_shader_create_path(g_dev, "shaders/blinn_phong_arr.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/blinn_phong_arr.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    /* R441 + R600: the array contract and the shortened push layout R600
     * bought. u_camera_pos must resolve -1 here exactly as it does on the
     * non-array pair — pinning it is what keeps the camera from creeping back
     * into the push block's 248-byte tail. */
    albedo_array = rhi_texture_array_create(g_dev, 2u, 2u, 3u,
                                            RHI_FORMAT_R8G8B8A8_UNORM);
    ASSERT_TRUE(rhi_handle_valid(albedo_array));
    rhi_texture_array_upload_layer(g_dev, albedo_array, 0u, layer_red,
                                   sizeof(layer_red));
    rhi_texture_array_upload_layer(g_dev, albedo_array, 1u, layer_green,
                                   sizeof(layer_green));
    rhi_texture_array_upload_layer(g_dev, albedo_array, 2u, layer_blue,
                                   sizeof(layer_blue));

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 32u;    /* pos3 + normal3 + uv2 -- no instance slot */
    pdesc.uses_textures = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_attachment_count = 2u;
    pdesc.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_model"), 0);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_view"), 64);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_proj"), 128);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_light_dir"), 192);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_light_color"), 208);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_ambient"), 224);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_camera_pos"), -1);

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));
    temporal_ubo = warp_forward_temporal_create(g_dev, 0.0f, 0.0f, -10.0f);
    ASSERT_TRUE(rhi_handle_valid(temporal_ubo));

    for (frame = 0; frame < 2; ++frame) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_mrt_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_set_uniform_mat4(cmd, 128, identity);
        rhi_cmd_set_uniform_vec3(cmd, 192, 0.0f, -1.0f, 0.0f);
        rhi_cmd_set_uniform_vec3(cmd, 208, 1.0f, 1.0f, 1.0f);
        rhi_cmd_set_uniform_vec3(cmd, 224, 1.0f, 1.0f, 1.0f);
        rhi_cmd_bind_uniform_buffer(cmd, temporal_ubo, 1u);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_bind_texture(cmd, albedo_array, (RHISampler){0}, 0u);
        if (frame == 0) {
            /* Two layers in one image. Each draw is instanced 0..N-1 and the
             * LAST instance rasterises last, so the top instance is the one
             * whose colour survives: instance 1 -> layer 1 (green) on the
             * lower side of the seam, instance 2 -> layer 2 (blue) above it. */
            rhi_cmd_draw_base(cmd, 3u, 2u, 0u);
            rhi_cmd_draw_base(cmd, 3u, 3u, 3u);
        } else {
            /* Layer 0 alone, whole target: 6 vertices cover both triangles. */
            rhi_cmd_draw_base(cmd, 6u, 1u, 0u);
        }
        rhi_mrt_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(rt0, 0, sizeof(rt0));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], rt0,
                                            sizeof(rt0)));
        for (row = 0; row < 8; ++row) {
            for (col = 0; col < 8; ++col) {
                float x = ((float)col + 0.5f) * 0.25f - 1.0f;
                float y = ((float)row + 0.5f) * 0.25f - 1.0f;
                /* Below the seam -> frame 0 drew layer 1, above -> layer 2;
                 * frame 1 drew layer 0 over the whole target. */
                int below = (y < -0.075f - 0.9375f * x);
                int layer = (frame == 0) ? (below ? 1 : 2) : 0;
                i = (row * 8 + col) * 4;
                if (rt0[i + 0] != expect[layer][0] ||
                    rt0[i + 1] != expect[layer][1] ||
                    rt0[i + 2] != expect[layer][2] ||
                    rt0[i + 3] != expect[layer][3]) {
                    printf("FAIL: frame %d pixel (col=%d,row=%d) got "
                           "(%u,%u,%u,%u), expected layer %d = "
                           "(%u,%u,%u,%u)\n", frame, col, row,
                           (unsigned)rt0[i + 0], (unsigned)rt0[i + 1],
                           (unsigned)rt0[i + 2], (unsigned)rt0[i + 3],
                           layer, (unsigned)expect[layer][0],
                           (unsigned)expect[layer][1],
                           (unsigned)expect[layer][2],
                           (unsigned)expect[layer][3]);
                }
                ASSERT_EQ(rt0[i + 0], expect[layer][0]);
                ASSERT_EQ(rt0[i + 1], expect[layer][1]);
                ASSERT_EQ(rt0[i + 2], expect[layer][2]);
                ASSERT_EQ(rt0[i + 3], expect[layer][3]);
                if (layer == 0) layer0_px++;
                else if (layer == 1) layer1_px++;
                else layer2_px++;
            }
        }

        /* Identity everywhere, so the motion vector is exactly +0.0 in both
         * channels on the raw bits. */
        memset(rt1, 0, sizeof(rt1));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], rt1,
                                            sizeof(rt1)));
        for (i = 0; i < 64; ++i) {
            ASSERT_EQ(rt1[i * 2 + 0], 0u);
            ASSERT_EQ(rt1[i * 2 + 1], 0u);
        }
    }

    /* Every layer must actually have contributed pixels, or "the colour is
     * right" would be vacuous. These are the exact areas the seam carves out
     * of the 8x8 target (28 below, 36 above) plus layer 0's full frame. */
    ASSERT_EQ(layer0_px, 64);
    ASSERT_EQ(layer1_px, 28);
    ASSERT_EQ(layer2_px, 36);

    rhi_mrt_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, albedo_array);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, temporal_ubo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* D3D12_DRAW_ARGUMENTS, spelled out because rhi.h deliberately does not leak
 * the SDK type: ExecuteIndirect reads exactly these four DWORDs, and the
 * backend's command signature declares ByteStride == sizeof(D3D12_DRAW_ARGUMENTS)
 * (rhi_d3d12.c), which rhi_d3d12_indirect_args_valid also enforces. */
typedef struct {
    u32 vertex_count_per_instance;
    u32 instance_count;
    u32 start_vertex_location;
    u32 start_instance_location;
} WarpDrawArgs;

static int warp_adapter_is_warp(RHIDevice *dev)
{
    RHIDeviceInfo info;
    if (!rhi_device_get_info(dev, &info)) return 0;
    return strstr(info.device_name, "Basic Render") != NULL ||
           strstr(info.device_name, "WARP") != NULL;
}

/* R609: the layer route production uses -- and why the array path is dead on
 * D3D12 today.
 *
 * mega_mat_arrays_draw encodes the material-array layer in the indirect
 * record's first_instance (main.c:3947) with instance_count = 1
 * (main.c:3779), and the GLSL twin reads it back as
 * uint(gl_BaseInstanceARB) in blinn_phong_arr.vert. The D3D12 sidecar reads
 * SV_InstanceID instead, and D3D12's SV_InstanceID does NOT include
 * StartInstanceLocation -- it is gl_InstanceID, i.e. base + instance index,
 * and here the base never arrives.
 *
 * This was recorded as a WARP limitation for several rounds and that was
 * wrong. Measured on the RTX 4060:
 *
 *   {InstanceCount = 1, StartInstanceLocation = 1} -> layer 0
 *   {InstanceCount = 1, StartInstanceLocation = 2} -> layer 0
 *   {InstanceCount = 2, StartInstanceLocation = 2} -> last instance is 1
 *
 * The third record is the discriminating one. InstanceCount IS honoured (two
 * instances rasterise and the second wins), so the argument buffer is being
 * read; only StartInstanceLocation is dropped. Without it the first two rows
 * would be indistinguishable from "the upload never happened".
 *
 * It does not corrupt rendering today, and "it is broken" would be the wrong
 * headline. rhi_d3d12.c never sets caps.indirect_draw_supported, so
 * indirect_draw_init fail-closes with "backend reports no indirect draw
 * support", mb->array_system_ready stays false, and mega_mat_arrays_draw
 * returns 0 before it reaches the pipeline this test drives directly. The
 * array pipeline is created and never drawn. So this is a trapdoor under a
 * disabled subsystem: it becomes a live bug the moment indirect draw is
 * enabled on D3D12, and it will not announce itself, because every mesh
 * still shades correctly -- with layer 0.
 *
 * Every row is asserted anyway. The test pins the measured behaviour so the
 * day the path is enabled the suite goes red and whoever fixes it updates
 * the expectations deliberately, instead of the layer silently becoming 0
 * inside a passing test. The per-draw argument buffer is read back and
 * asserted too, so "the record on the CPU was right" is part of the recorded
 * evidence rather than an assumption.
 *
 * The fix is a command signature with a second D3D12_INDIRECT_ARGUMENT_TYPE_
 * CONSTANT argument, copying the layer out of the record into a root
 * constant. There is room: this pipeline's push block ends at 240 and two
 * descriptor tables clamp 32BIT_CONSTANTS at 62 DWORDs = 248 bytes. See the
 * note in blinn_phong_arr_hlsl.frag. */
TEST(indirect_start_instance_does_not_reach_sv_instance_id)
{
    static const float verts[6 * 8] = {
        /*  pos                    normal        uv  */
        -1.2f, -1.2f,  0.00f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         1.2f, -1.2f,  0.00f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
        -1.2f,  1.05f, 0.00f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f,
         1.2f, -1.2f,  0.00f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
         1.2f,  1.05f, 0.00f,   0.0f, 0.0f, 1.0f,   2.0f, 2.0f,
        -1.2f,  1.05f, 0.00f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f
    };
    static const unsigned char layer_red[2 * 2 * 4] = {
        255, 0, 0, 255,   255, 0, 0, 255,
        255, 0, 0, 255,   255, 0, 0, 255
    };
    static const unsigned char layer_green[2 * 2 * 4] = {
        0, 255, 0, 255,   0, 255, 0, 255,
        0, 255, 0, 255,   0, 255, 0, 255
    };
    static const unsigned char layer_blue[2 * 2 * 4] = {
        0, 0, 255, 255,   0, 0, 255, 255,
        0, 0, 255, 255,   0, 0, 255, 255
    };
    /* Column-major: index = col*4 + row. */
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    static const unsigned char expect[3][4] = {
        { 255,   0,   0, 255 },
        {   0, 255,   0, 255 },
        {   0,   0, 255, 255 }
    };
    /* The three measured records from the header comment. The third is the
     * discriminating one: InstanceCount = 2 proves the argument buffer is
     * read at all, so a layer of 0 in the first two rows is the base being
     * dropped rather than an upload that never landed. */
    static const struct { u32 instances; u32 start; int layer; } cases[3] = {
        { 1u, 1u, 0 },
        { 1u, 2u, 0 },
        { 2u, 2u, 1 }
    };
    const RHIFormat formats[2] = {
        RHI_FORMAT_R8G8B8A8_UNORM, RHI_FORMAT_R16G16_SFLOAT
    };
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHITexture albedo_array;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo, args, temporal_ubo;
    RHICmdBuffer *cmd;
    unsigned char rt0[8 * 8 * 4];
    unsigned short rt1[8 * 8 * 2];
    WarpDrawArgs record, readback;
    const int on_warp = warp_adapter_is_warp(g_dev);
    int c, pixel, i;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create_path(g_dev, "shaders/blinn_phong_arr.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/blinn_phong_arr.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    albedo_array = rhi_texture_array_create(g_dev, 2u, 2u, 3u,
                                            RHI_FORMAT_R8G8B8A8_UNORM);
    ASSERT_TRUE(rhi_handle_valid(albedo_array));
    rhi_texture_array_upload_layer(g_dev, albedo_array, 0u, layer_red,
                                   sizeof(layer_red));
    rhi_texture_array_upload_layer(g_dev, albedo_array, 1u, layer_green,
                                   sizeof(layer_green));
    rhi_texture_array_upload_layer(g_dev, albedo_array, 2u, layer_blue,
                                   sizeof(layer_blue));

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 32u;
    pdesc.uses_textures = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_attachment_count = 2u;
    pdesc.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    /* INDIRECT, not STORAGE: the backend gives this one the UPLOAD heap, which
     * is the CPU-writable / GPU-readable shape ExecuteIndirect needs. */
    memset(&record, 0, sizeof(record));
    record.vertex_count_per_instance = 6u;
    record.instance_count = 2u;
    record.start_vertex_location = 0u;
    record.start_instance_location = 1u;
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(record);
    bdesc.usage = RHI_BUFFER_USAGE_INDIRECT;
    bdesc.initial_data = &record;
    args = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(args));

    temporal_ubo = warp_forward_temporal_create(g_dev, 0.0f, 0.0f, -10.0f);
    ASSERT_TRUE(rhi_handle_valid(temporal_ubo));

    /* The three measured records from the header comment. The third is the
     * discriminating one: InstanceCount = 2 proves the argument buffer is
     * read at all, so a layer of 0 in the first two rows is the base being
     * dropped rather than an upload that never landed. */
    for (c = 0; c < 3; ++c) {
        const int layer = cases[c].layer;
        record.instance_count = cases[c].instances;
        record.start_instance_location = cases[c].start;
        rhi_buffer_update(g_dev, args, &record, sizeof(record));
        memset(&readback, 0, sizeof(readback));
        ASSERT_TRUE(rhi_buffer_read(g_dev, args, &readback, 0u,
                                    sizeof(readback)));
        ASSERT_EQ(readback.vertex_count_per_instance, 6u);
        ASSERT_EQ(readback.instance_count, cases[c].instances);
        ASSERT_EQ(readback.start_vertex_location, 0u);
        ASSERT_EQ(readback.start_instance_location, cases[c].start);

        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_mrt_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_set_uniform_mat4(cmd, 128, identity);
        rhi_cmd_set_uniform_vec3(cmd, 192, 0.0f, -1.0f, 0.0f);
        rhi_cmd_set_uniform_vec3(cmd, 208, 1.0f, 1.0f, 1.0f);
        rhi_cmd_set_uniform_vec3(cmd, 224, 1.0f, 1.0f, 1.0f);
        rhi_cmd_bind_uniform_buffer(cmd, temporal_ubo, 1u);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_bind_texture(cmd, albedo_array, (RHISampler){0}, 0u);
        rhi_cmd_draw_indirect(g_dev, args, 0u, 1u, (u32)sizeof(record));
        rhi_mrt_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(rt0, 0, sizeof(rt0));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], rt0,
                                            sizeof(rt0)));
        for (pixel = 0; pixel < 64; ++pixel) {
            i = pixel * 4;
            if (rt0[i + 0] != expect[layer][0] ||
                rt0[i + 1] != expect[layer][1] ||
                rt0[i + 2] != expect[layer][2] ||
                rt0[i + 3] != expect[layer][3]) {
                printf("FAIL: {InstanceCount=%u, StartInstanceLocation=%u} on "
                       "%s adapter rendered layer %d at pixel %d as "
                       "(%u,%u,%u,%u), expected (%u,%u,%u,%u)\n",
                       (unsigned)cases[c].instances,
                       (unsigned)cases[c].start,
                       on_warp ? "WARP" : "hardware", layer, pixel,
                       (unsigned)rt0[i + 0], (unsigned)rt0[i + 1],
                       (unsigned)rt0[i + 2], (unsigned)rt0[i + 3],
                       (unsigned)expect[layer][0], (unsigned)expect[layer][1],
                       (unsigned)expect[layer][2], (unsigned)expect[layer][3]);
            }
            ASSERT_EQ(rt0[i + 0], expect[layer][0]);
            ASSERT_EQ(rt0[i + 1], expect[layer][1]);
            ASSERT_EQ(rt0[i + 2], expect[layer][2]);
            ASSERT_EQ(rt0[i + 3], expect[layer][3]);
        }

        memset(rt1, 0, sizeof(rt1));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], rt1,
                                            sizeof(rt1)));
        for (i = 0; i < 64 * 2; ++i) {
            ASSERT_EQ(rt1[i], 0u);
        }
    }

    printf("  note: %s agrees -- StartInstanceLocation does not reach "
           "SV_InstanceID on either adapter. Latent today only because "
           "caps.indirect_draw_supported is false on D3D12, so the array path "
           "is disabled; see the header comment.\n",
           on_warp ? "WARP" : "hardware");

    rhi_mrt_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, albedo_array);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, args);
    rhi_buffer_destroy(g_dev, temporal_ubo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(mrt_fbo_clears_and_reads_independent_attachments) {
    const RHIFormat formats[2] = {
        RHI_FORMAT_R8G8B8A8_UNORM,
        RHI_FORMAT_R8G8B8A8_UNORM
    };
    const unsigned char red[4] = {255u, 0u, 0u, 255u};
    const unsigned char blue[4] = {0u, 0u, 255u, 255u};
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHICmdBuffer *cmd;
    unsigned char pixels[2][8 * 8 * 4];
    int attachment;
    int pixel;
    int channel;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));
    ASSERT_EQ(fbo.attachment_count, 2u);
    ASSERT_TRUE(rhi_handle_valid(fbo.color_tex[0]));
    ASSERT_TRUE(rhi_handle_valid(fbo.color_tex[1]));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_mrt_fbo_bind(cmd, &fbo);
    rhi_cmd_clear_color_attachment(cmd, 0u, 1.0f, 0.0f, 0.0f, 1.0f);
    rhi_cmd_clear_color_attachment(cmd, 1u, 0.0f, 0.0f, 1.0f, 1.0f);
    rhi_mrt_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    memset(pixels, 0, sizeof(pixels));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0],
                                        pixels[0], sizeof(pixels[0])));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1],
                                        pixels[1], sizeof(pixels[1])));
    for (attachment = 0; attachment < 2; ++attachment) {
        const unsigned char *expected = attachment == 0 ? red : blue;
        for (pixel = 0; pixel < 8 * 8; ++pixel) {
            for (channel = 0; channel < 4; ++channel)
                ASSERT_EQ(pixels[attachment][pixel * 4 + channel],
                          expected[channel]);
        }
    }

    rhi_mrt_fbo_destroy(g_dev, &fbo);
}

/* ---- shadow atlas ---- */
/* R618: an atlas is published only if it names a real target. The create
 * contract is the R358 gate seen from the other side — a zero-sized or
 * otherwise invalid request must produce NO handles, because binding a handle
 * that resolves to nothing is exactly the case that used to clear whatever
 * depth was still bound. Destroy must be idempotent so a double teardown is a
 * no-op rather than a double free. */
TEST(shadow_map_create_publishes_a_depth_target_and_destroy_is_idempotent) {
    RHIShadowMap sm;
    RHIShadowMap bad;
    bad = rhi_shadow_map_create(g_dev, 0u, 0u);
    ASSERT_FALSE(rhi_handle_valid(bad.depth_tex));
    ASSERT_FALSE(rhi_handle_valid(bad.fbo));

    sm = rhi_shadow_map_create(g_dev, 8u, 8u);
    ASSERT_TRUE(rhi_handle_valid(sm.depth_tex));
    ASSERT_TRUE(rhi_handle_valid(sm.fbo));
    ASSERT_EQ(sm.width, 8u);
    ASSERT_EQ(sm.height, 8u);

    rhi_shadow_map_destroy(g_dev, &sm);
    ASSERT_FALSE(rhi_handle_valid(sm.depth_tex));
    ASSERT_FALSE(rhi_handle_valid(sm.fbo));
    /* Second destroy on an already-cleared handle must not fault. */
    rhi_shadow_map_destroy(g_dev, &sm);
    ASSERT_FALSE(rhi_handle_valid(sm.fbo));
}

/* The pixel proof that the shadow atlas and the lighting pass see the SAME
 * bytes.
 *
 * The one D3D12-specific thing under test is that a shadow atlas has to be two
 * views over one allocation. DXGI_FORMAT_D32_FLOAT cannot back a shader
 * resource view at all, so the atlas is created through the depth_samplable
 * path: the resource is the canonical typeless DXGI_FORMAT_R32_TYPELESS, the
 * shadow pass gets a D32_FLOAT depth-stencil view of it, and the lighting pass
 * gets an R32_FLOAT SRV of it.
 *
 * WHAT THESE PIXELS PIN, AND WHAT THEY DO NOT. Reverse-verified: reverting the
 * SRV's format to D32_FLOAT turns this test red (the invalid SRV takes the
 * device down, and the readback one-shot fails), and so does reverting the
 * shadow bind's unit to 0, its OMSetRenderTargets, the clear value, or the
 * barrier into the read state. What they do NOT pin is the typeless
 * ALLOCATION itself: allocating plain D32_FLOAT and still aliasing the SRV to
 * R32_FLOAT was tried as a break and stayed GREEN on WARP, because the two
 * formats have the same 4-byte texel and WARP tolerates the reinterpretation.
 * The typeless allocation is what the D3D12 spec requires for the SRV alias to
 * be legal on hardware drivers, so the implementation keeps it — but no WARP
 * pixel here proves it, and this comment must not be read as saying otherwise.
 *
 * What the pixels say:
 *   1. The bind clears the whole atlas to 1.0 (R618 "bind == fresh"). With a
 *      receiver depth of 0.5 and the stored depth still 1.0, the hand-rolled
 *      compare in shadow_sample_hlsl.frag gives lit => every pixel white.
 *   2. A depth-only pass then draws a quad covering the centre 4x4 at depth
 *      0.25. Re-reading the atlas, those 16 texels now compare 0.5 <= 0.25 as
 *      false => black (in shadow), and the other 48 stay white (lit). That
 *      single frame proves the clear, the DSV alias, the SRV alias, the
 *      non-flipped shadow viewport and the unit-1 binding all at once — the
 *      centre square is also what pins the viewport: a Y-flipped or mis-sized
 *      viewport would put the square somewhere other than rows/cols 2..5.
 *
 * The compare is done by hand on the sampled .r, exactly as the production
 * clustered shaders do, so this test also pins that D3D12's lack of comparison
 * sampling is irrelevant to the shadow pass. */
/* R613: depth_only_hlsl.vert has to convert clip z, and this is the test that
 * says so.
 *
 * depth_only.vert is one GLSL file shared by two backends behind #ifdef
 * VULKAN, and the arms differ: the GL arm leaves clip.z alone because
 * OpenGL's NDC is [-1,1] and fixed-function maps it to [0,1], while the
 * Vulkan arm does gl_Position.z = (z + w) * 0.5 because Vulkan's NDC is
 * [0,1]. D3D12's NDC is [0,1] too, so the sidecar follows the Vulkan arm --
 * and the CPU settles it independently, because mat4_ortho() writes
 * m.e[2][2] = -2/(far-near), the OpenGL form, so u_light_vp hands every
 * backend a z in [-1,1].
 *
 * "Mirror the GL variant" is the wrong rule here and would be easy to apply
 * by reflex, so the test is built to make the two conventions disagree by as
 * much as possible rather than by a rounding hair:
 *
 *   flat = identity with e[2][2] and e[2][3] zeroed, so clip.z = 0 and
 *   clip.w = 1 at every vertex of the quad.
 *     converted   -> window depth (0 + 1) * 0.5 = 0.5
 *     unconverted -> window depth 0.0
 *
 * The oracle is shadow_sample_hlsl.frag, which is the engine's real compare
 * (receiver.z > stored depth -> shadowed). Sampling it at receiver depth
 * 0.25 splits the two cases cleanly:
 *
 *     stored 0.5 -> 0.25 > 0.5 is false -> LIT      -> 255
 *     stored 0.0 -> 0.25 > 0.0 is true  -> SHADOWED -> 0
 *
 * So a single exact byte decides it, and the unconverted variant fails by
 * 255 rather than by one. The quad covers the whole 8x8 target, so there is
 * no partially-shaded corner for the assertion to hide in. */
/* R615: rhi_cmd_bind_texel_buffers reaches the shader.
 *
 * It was (void)cmd; (void)buf0; (void)buf1;, which is what made instanced and
 * skinned unwritable on D3D12 however correct a sidecar was -- both read
 * layout(binding = 5) samplerBuffer, and this is the call that fills unit 5.
 *
 * One buffer, two 16-byte rows, one full-target triangle:
 *
 *   row 0 = (255, 0, 0)   red
 *   row 1 = (0, 255, 0)   green
 *
 * Frame 0 draws with InstanceCount 1, so SV_InstanceID is 0 and the whole
 * target must be row 0. Frame 1 draws with InstanceCount 2; the pipeline has
 * depth writing off and no depth test, so both instances cover the same
 * pixels and the second rasterises last -- the whole target must be row 1.
 *
 * Two frames of one flat colour each is what makes this decisive. A binder
 * that did nothing leaves the descriptor table unwritten, both instances
 * read row 0, and frame 1 comes back red -- a wrong colour, not a wrong
 * shade. A wrong StructureByteStride (say 4 instead of 16) turns row 1's
 * green into whatever the bytes at offset 4 happen to be, which the exact
 * comparison also catches. */
/* R617: color_grade on D3D12, and post_hlsl.vert with it.
 *
 * color_grade is the cheapest member of the post family and the most
 * instructive, because all five of its uniforms fit in 20 bytes of push block
 * -- the opposite of instanced, whose six do not (R616). post_hlsl.vert is the
 * other half of the value here: 21 subsystems in src/renderer/ request
 * shaders/post.vert, so this file is the common prerequisite for the whole
 * family and it carries no uniforms at all.
 *
 * The colour maths is closed-form, so the expected bytes are derived rather
 * than recorded. Two configurations, each chosen so the result is an exact
 * byte and each isolating a different stage:
 *
 *   case A  grey in (200,200,200), saturation 1, contrast 1, brightness 1,
 *           temperature 0, tint 0.
 *             adjust_saturation(c, 1)  -> lerp(luma, c, 1) = c   (identity)
 *             adjust_contrast(c, 1)    -> (c-0.5)+0.5 = c        (identity)
 *             brightness 1             -> c                      (identity)
 *             temperature 0 -> t = mix(cool, warm, 0.5)
 *                           = ((0.7+1)/2, 0.85, (1+0.7)/2) = (0.85,0.85,0.85)
 *             grey in, grey multiplier -> 200 * 0.85 = 170 exactly.
 *           So case A proves the three identity stages really are identity and
 *           the white-balance vector is the neutral grey, not a per-channel
 *           one.
 *
 *   case B  pure red in (255,0,0), saturation 0, everything else as above.
 *             luma = dot(red, Rec.709) = 0.2126, and saturation 0 collapses the
 *             colour to exactly luma -- the strongest possible statement that
 *             the saturation term reads u_cg_saturation and not a constant.
 *             0.2126 * 0.85 = 0.18071, *255 = 46.08 -> 46.
 *
 * The source is a solid colour per configuration, so "one flat output" is the
 * assertion rather than a shortcut: a missing texture descriptor, a wrong
 * uniform offset, or a mis-typed multiplier each make it a different flat
 * colour, and the clear colour is set to a loud green that is never an answer. */
/* R617: lens_effects on D3D12.
 *
 * Chromatic aberration is disabled and grain is disabled, which leaves the
 * vignette as the only term, and that is deliberate: on a flat source the CA
 * offsets re-sample the same colour and grain is a hash that would have to be
 * reproduced in the test. The vignette is a pure function of pixel position,
 * so every expected byte is derivable:
 *
 *   vignette = 1 - smoothstep(u_vignette_softness, 0.8, dist * u_vignette_strength)
 *
 * with softness 0 and strength 1, dist = length(uv - 0.5), and uv = ((c+0.5)/8,
 * (r+0.5)/8) from post_hlsl.vert. Two values are hand-derived in the comment
 * below and the other 62 come from the same closed form; if the formula were
 * wrong the two anchors would not agree with the table.
 *
 * Asserting all 64 rather than one flat colour is what gives this teeth
 * despite the source being flat: a wrong vUV mapping, a wrong vertex shader,
 * a missing t0 descriptor or a mis-ordered u_vignette_strength each produce a
 * different radial table, and the corners and centre are the two ends of it.
 * The clear colour is a loud green that is never an answer. */
/* R619: fxaa on D3D12.
 *
 * FXAA cannot be asserted as a whole derived table the way the vignette
 * could, for two reasons that are recorded here rather than worked around
 * silently:
 *
 *  1. The GLSL reference divides 0 by 0 on some edge pixels. When the
 *     neighbourhood straddles an edge but both end-of-edge probes land on
 *     the local average exactly, distA + distB == 0 and blend becomes NaN,
 *     which is then used as a texture coordinate. What a GPU returns for a
 *     NaN UV is undefined, so those pixels are adapter-dependent. The HLSL
 *     sidecar is a line-for-line port and inherits this on purpose -- fixing
 *     it would make D3D12 diverge from GL -- so the test does not look at
 *     them. A Python model of the shader found six such pixels for the
 *     pattern below; they all sit on the box's outline.
 *  2. The blend direction depends on the texture's row order relative to the
 *     readback, so a test that pinned exact row positions would be asserting
 *     an orientation convention, not FXAA.
 *
 * So the assertions are the parts that are well defined and orientation-free,
 * on an 8x8 black target with a white 2x2 box at columns 3..4, rows 3..4:
 *
 *   - every pixel outside the 4x4 window (columns/rows 2..5) is exactly 0:
 *     flat regions pass through the early-out unchanged (48 pixels);
 *   - inside the window, exactly two pixels are blended to 191 +- 1
 *     (= 255 * 0.75, the model's value) and they are in columns 3 and 4 of the
 *     same row -- i.e. FXAA actually ran and moved the edge;
 *   - the box's own two fully-white pixels survive at 255.
 *
 * A pass-through shader leaves no 191 pixels; a wrong u_fxaa_sw/sh changes
 * the texel step and moves or removes the blend; a missing t0 descriptor
 * blacks out the box. */
/* R620: dof on D3D12, and rhi_cmd_bind_textures_multi with it.
 *
 * rhi_cmd_bind_textures_multi was a no-op stub on D3D12, and nine post passes
 * use it -- dof, motion_blur, taa, ssr, ssgi, contact_shadow, lens_flare and
 * both arms of combined_post_process. DOF is a good first proof of it because
 * it needs BOTH units to be right at once: t1 (depth) decides which branch the
 * shader takes, and t0 (colour) supplies the pixels in either branch.
 *
 * Source: an 8x8 colour image, columns 0..3 red and 4..7 blue, every row
 * identical; and an 8x8 R32_FLOAT depth image that is 0.5 everywhere, which
 * linearizes to 0.1998 at near 0.1 / far 100.
 *
 *   frame 0: u_dof_focus = 0.1998 (the depth itself) -> coc 0 -> early-out,
 *            the stripes pass through exactly: (255,0,0) | (0,0,255).
 *   frame 1: u_dof_focus = 100.1998, range 5 -> coc saturates at 1 -> the
 *            hex-disk gather (radius 10 texels) blurs the edge. A Python
 *            model of the shader gives the red table below, blue = 255 - red,
 *            green exactly 0.
 *
 * The first draft of this test only modelled row 3 and asserted every row
 * equal to row 0 because the SOURCE is row-invariant. That was wrong, and
 * both adapters said so on the first run (row 0, column 1 read 170, not 128):
 * the shader skips gather taps whose UV leaves [0,1], and at radius 10 on an
 * 8-pixel target most taps leave it, so which taps survive depends on the
 * row. The full table is what the model gives once all 64 pixels are
 * evaluated. It is symmetric under row r <-> 7 - r, so it does not depend on
 * whether readback row 0 is the top or the bottom of the image.
 *
 * Frame 1 is asserted with a +-2 tolerance and frame 0 exactly. Several model
 * values sit exactly on .5 (127.5), so exact bytes would be asserting the
 * hardware's round-half rule; the bound covers that and bilinear-weight
 * ULPs. Green is exactly 0 and red + blue is 255 +- 2 on every pixel.
 *
 * What each fault looks like: a stub multi-binder leaves t0/t1 unbound and
 * frame 0 is not the stripes; swapped units sample depth as colour and red is
 * a flat 127; a wrong u_dof_focus offset keeps frame 1 in the early-out and
 * it still shows hard stripes. */
/* R621: the forward sidecars convert clip z, and this is what it buys.
 *
 * mat4_perspective is the OpenGL form, so ndc_z is negative for near
 * geometry. At the demo's near 0.1 / far 100 the boundary is at eye distance
 * 0.2:
 *
 *   dist 0.15 -> ndc_z -0.3327   (D3D12 rasteriser clips this)
 *   dist 0.20 -> ndc_z +0.0010
 *   dist 0.30 -> ndc_z +0.3347
 *   dist 1.00 -> ndc_z +0.8018
 *   dist 5.00 -> ndc_z +0.9620
 *
 * D3D12's NDC z is [0,1] with no fixed-function mapping, so before R621 every
 * vertex closer than ~0.2 was clipped away. A quad spanning 0.15 to 1.0 under
 * a real perspective therefore rendered only its far half.
 *
 * depth_clip_hlsl.vert is a probe with the blinn_phong push block and the same
 * one-line conversion; it writes red where the un-converted ndc_z was
 * negative. The quad's near edge sits at 0.15, so without the conversion the
 * red band is missing (clipped); with it, the band is present. Both the vertex
 * count and the colour are asserted, so the test fails either way -- on colour
 * if the conversion is there but wrong, on missing pixels if it is absent.
 *
 * This is a probe rather than a blinn_phong test on purpose: blinn_phong's
 * pixel proofs assert exact colours with degenerate lighting, and moving the
 * projection under them would change what they are testing. The probe isolates
 * the one thing R621 changed. */
/* R622: ssr on D3D12 -- offsets, both early-outs, and an honest gap.
 *
 * SSR's pixel proof is much weaker than its siblings', and it is worth being
 * precise about why rather than shipping a test that looks thorough:
 *
 *   - `u_ssr_thickness` is a GLSL const, pinned at -1 like fxaa's threshold.
 *   - Frame 0: depth is 1.0 everywhere, so the first early-out
 *     (`if (depth >= 1.0)`) returns the scene colour untouched. Exact.
 *   - Frame 1: depth is a constant 0.5, so every pixel reconstructs to the
 *     same plane; the normal from the screen-space derivatives is that plane's
 *     normal, perpendicular to the view, which makes refl_dir.z > 0 and takes
 *     the second early-out. Also the scene colour. Exact.
 *   - The RAY MARCH is not asserted. Pinning it would mean modelling 32
 *     marching steps plus a 4-iteration bisection in Python and hoping the
 *     model's bilinear weights land in the same byte as the GPU's -- which is
 *     precisely what went wrong trying to assert fxaa's blend table, and
 *     fxaa also divides 0/0 on some edges, so some march inputs are undefined.
 *     A synthetic reflection would have to be built from a depth step, and the
 *     expected result would then be a number this test computed with a second
 *     implementation rather than a value derived from the contract.
 *
 * ⚠️ AND the two early-outs are NOT separately observable here, which the
 * reverse check proved rather than assumed: disabling the first one
 * (if (depth >= 1.0) -> if (false)) leaves this test GREEN, because the
 * second early-out then catches the same pixels, and with a flat depth field
 * the march finds nothing either so fade stays 0. All three paths return the
 * scene colour. So this test does NOT pin "the early-out fired"; it pins the
 * wiring. Anything that moves a uniform, a texture or the projection turns it
 * red; anything that merely changes which branch runs does not.
 *
 * What this pins is the wiring, which is where the real risk was: seven
 * uniform offsets at 0/64/128/192/196/200/204, the const at -1, and both
 * textures reaching the shader through rhi_cmd_bind_textures_multi (SSR is
 * the second consumer of the binder R620 implemented). A missing t0 or t1
 * blacks the frame out; a mis-offset uniform moves the scene colour, because
 * u_ssr_proj / u_ssr_inv_proj are what decode the depth that decides the
 * early-out. */
/* R626: lens_flare on D3D12 -- and the first post pass whose test really does
 * derive its pixels rather than only pinning the wiring.
 *
 * lens_flare is a closed-form function of uv: a radial star, two streaks, a
 * ghost gated on depth > 0.99 and a halo, added to the scene colour. No
 * march, no early-outs, no feedback. So all 64 pixels are computable:
 *
 *   scene  = (col * 31, 0, 0)          vertical stripes, column-dependent so a
 *                                         readback row flip cannot change it
 *   depth  = 1.0 everywhere             so the ghost always qualifies
 *   light  = (0.5, 0.5), colour (1,1,1), intensity 0.375
 *   out    = (scene_r + flare, flare, flare)
 *
 * Intensity 0.375 was searched for rather than picked: the closest any pixel
 * came to a byte rounding boundary is 0.007 there, and 0.001 at intensity 1.0.
 * Both are too tight to assert exact bytes, so the comparison is +-1 -- the
 * same treatment DOF's blur needed. ±1 still catches anything structural,
 * because the table spans 29..254 across the frame.
 *
 * The table is symmetric under r <-> 7-r, so readback orientation cannot
 * change it. And unlike ssr, motion_blur and contact_shadow, this test pins
 * the actual output rather than only the wiring: swapping t0 and t1, or
 * dropping the ghost, or changing the intensity all move specific pixels.
 */
/* R627: SSGI on D3D12 -- both passes.
 *
 * SSGI is the one post pass with two pipelines, so this exercises two
 * sidecars: ssgi_hlsl.frag (the 16-tap hemisphere gather) and
 * ssgi_blur_hlsl.frag (the 9-tap Gaussian that self-composites). Both share
 * post_hlsl.vert.
 *
 * Both are asserted exactly, and each for a different reason:
 *
 *  - gather pass, depth >= 1.0: the shader returns (0,0,0,1) with no
 *    dependency on anything else. That pins the branch and both texture
 *    registers without touching the 16-tap loop, which -- like ssr's march and
 *    motion_blur's blur -- is not asserted.
 *  - blur pass with a solid GI buffer: the nine weights sum to exactly
 *    0.0162*2 + 0.0540*2 + 0.1218*2 + 0.1960*2 + 0.2240 = 1.0000, and every
 *    tap lands on an exact texel centre (integer multiples of the texel step),
 *    so the 9-tap sum of a constant is that constant and the output is
 *    scene + gi exactly. That proves the blur runs, that u_direction reaches
 *    the shader, and that both textures are bound -- without the answer
 *    depending on how the taps were placed.
 *
 * The gather's u_ssgi_proj is declared in the GLSL and written by
 * ssgi_apply, but never read by the shader body. It is published as a marker
 * at offset 64 anyway so the engine's write is not silently dropped; the test
 * pins that.
 */
TEST(ssgi_gather_early_out_and_blur_pass_through_are_exact) {
    static unsigned char scene[8 * 8 * 4];
    static unsigned char gi[8 * 8 * 4];
    static float depth[8 * 8];
    static float sky[8 * 8];
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture dtex, skytex, ctex, gtex;
    RHITexture pair[2];
    RHIShader vs, fs_g, fs_b;
    RHIPipeline pg, pb;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    static const char *const gnames[6] = {
        "u_ssgi_inv_proj", "u_ssgi_proj", "u_ssgi_radius",
        "u_ssgi_intensity", "u_ssgi_sw", "u_ssgi_sh"
    };
    static const i32 gwant[6] = { 0, 64, 128, 132, 136, 140 };
    int i;

    for (i = 0; i < 64; ++i) {
        scene[i * 4 + 0] = (unsigned char)((i & 7) * 31u);
        scene[i * 4 + 1] = 40u;
        scene[i * 4 + 2] = 70u;
        scene[i * 4 + 3] = 255u;
        gi[i * 4 + 0] = 20u;
        gi[i * 4 + 1] = 110u;
        gi[i * 4 + 2] = 5u;
        gi[i * 4 + 3] = 255u;
        depth[i] = 0.5f;
        sky[i] = 1.0f;
    }

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs_g = rhi_shader_create(g_dev, "ssgi_hlsl.frag", 0, true);
    fs_b = rhi_shader_create(g_dev, "ssgi_blur_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs_g));
    ASSERT_TRUE(rhi_handle_valid(fs_b));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs_g;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pg = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pg));
    for (i = 0; i < 6; ++i) {
        i32 got = rhi_pipeline_get_uniform_location(g_dev, pg, gnames[i]);
        if (got != gwant[i])
            printf("FAIL: %s resolved to %d, expected %d\n", gnames[i],
                   (int)got, (int)gwant[i]);
        ASSERT_EQ(got, gwant[i]);
    }

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs_b;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pb = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pb));
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pb, "u_direction"), 0);

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 8u; tdesc.height = 8u;
    tdesc.mip_levels = 1u;
    tdesc.format = RHI_FORMAT_R32_FLOAT;
    tdesc.data = depth;  dtex   = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(dtex));
    tdesc.data = sky;    skytex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(skytex));
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.data = scene;  ctex   = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(ctex));
    tdesc.data = gi;     gtex   = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(gtex));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    /* Gather pass: depth 1.0 everywhere -> (0,0,0,1), exactly. */
    pair[0] = skytex; pair[1] = ctex;
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_clear_color(cmd, 1.0f, 1.0f, 0.0f, 1.0f);   /* never an answer */
    rhi_cmd_bind_pipeline(cmd, pg);
    rhi_cmd_bind_textures_multi(cmd, pair, 2, sampler);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < 64; ++i) {
        if (px[i * 4] || px[i * 4 + 1] || px[i * 4 + 2]) {
            printf("FAIL: ssgi gather pixel %d = (%u,%u,%u), expected "
                   "(0,0,0) from the depth >= 1.0 early-out\n", i,
                   (unsigned)px[i * 4], (unsigned)px[i * 4 + 1],
                   (unsigned)px[i * 4 + 2]);
            break;
        }
    }
    for (i = 0; i < 64; ++i) {
        ASSERT_EQ(px[i * 4], 0u);
        ASSERT_EQ(px[i * 4 + 1], 0u);
        ASSERT_EQ(px[i * 4 + 2], 0u);
        ASSERT_EQ(px[i * 4 + 3], 255u);
    }

    /* Blur pass: solid GI, so the nine weights sum to 1 and the output is
     * scene + gi. */
    pair[0] = gtex; pair[1] = ctex;
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_clear_color(cmd, 1.0f, 1.0f, 0.0f, 1.0f);   /* never an answer */
    rhi_cmd_bind_pipeline(cmd, pb);
    rhi_cmd_bind_textures_multi(cmd, pair, 2, sampler);
    rhi_cmd_set_uniform_vec2(cmd, 0, 1.0f, 0.0f);   /* u_direction */
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < 64; ++i) {
        int ch;
        for (ch = 0; ch < 3; ++ch) {
            int exp = (int)scene[i * 4 + ch] + (int)gi[i * 4 + ch];
            int got = px[i * 4 + ch];
            int d = got - exp;
            if (d < 0) d = -d;
            if (d > 1) {
                printf("FAIL: ssgi blur pixel %d ch%d = %d, expected %d "
                       "(scene + gi) +- 1\n", i, ch, got, exp);
            }
            ASSERT_TRUE(d <= 1);
        }
        ASSERT_EQ(px[i * 4 + 3], 255u);
    }

    rhi_texture_destroy(g_dev, dtex);
    rhi_texture_destroy(g_dev, skytex);
    rhi_texture_destroy(g_dev, ctex);
    rhi_texture_destroy(g_dev, gtex);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pg);
    rhi_pipeline_destroy(g_dev, pb);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs_g);
    rhi_shader_destroy(g_dev, fs_b);
}

TEST(lens_flare_sidecar_matches_the_derived_64_pixel_table) {
    static const unsigned char want[8][8][4] = {
        {{ 29, 29, 29,255}, { 63, 32, 32,255}, { 97, 35, 35,255}, {130, 37, 37,255}, {161, 37, 37,255}, {190, 35, 35,255}, {218, 32, 32,255}, {246, 29, 29,255}},
        {{ 32, 32, 32,255}, { 67, 36, 36,255}, {104, 42, 42,255}, {139, 46, 46,255}, {170, 46, 46,255}, {197, 42, 42,255}, {222, 36, 36,255}, {249, 32, 32,255}},
        {{ 35, 35, 35,255}, { 73, 42, 42,255}, {114, 52, 52,255}, {155, 62, 62,255}, {186, 62, 62,255}, {207, 52, 52,255}, {228, 42, 42,255}, {252, 35, 35,255}},
        {{ 37, 37, 37,255}, { 77, 46, 46,255}, {124, 62, 62,255}, {183, 90, 90,255}, {214, 90, 90,255}, {217, 62, 62,255}, {232, 46, 46,255}, {254, 37, 37,255}},
        {{ 37, 37, 37,255}, { 77, 46, 46,255}, {124, 62, 62,255}, {183, 90, 90,255}, {214, 90, 90,255}, {217, 62, 62,255}, {232, 46, 46,255}, {254, 37, 37,255}},
        {{ 35, 35, 35,255}, { 73, 42, 42,255}, {114, 52, 52,255}, {155, 62, 62,255}, {186, 62, 62,255}, {207, 52, 52,255}, {228, 42, 42,255}, {252, 35, 35,255}},
        {{ 32, 32, 32,255}, { 67, 36, 36,255}, {104, 42, 42,255}, {139, 46, 46,255}, {170, 46, 46,255}, {197, 42, 42,255}, {222, 36, 36,255}, {249, 32, 32,255}},
        {{ 29, 29, 29,255}, { 63, 32, 32,255}, { 97, 35, 35,255}, {130, 37, 37,255}, {161, 37, 37,255}, {190, 35, 35,255}, {218, 32, 32,255}, {246, 29, 29,255}}
    };
    static unsigned char scene[8 * 8 * 4];
    static float depth[8 * 8];
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture dtex, stex;
    RHITexture pair[2];
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    static const char *const names[8] = {
        "u_lf_light_x", "u_lf_light_y", "u_lf_intensity", "u_lf_sw",
        "u_lf_sh", "u_lf_lc_r", "u_lf_lc_g", "u_lf_lc_b"
    };
    static const i32 want_off[8] = { 0, 4, 8, 12, 16, 20, 24, 28 };
    int frame, i, ch;

    for (i = 0; i < 64; ++i) {
        scene[i * 4 + 0] = (unsigned char)((i & 7) * 31u);
        scene[i * 4 + 1] = 0u;
        scene[i * 4 + 2] = 0u;
        scene[i * 4 + 3] = 255u;
        depth[i] = 1.0f;
    }

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "lens_flare_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 8; ++i) {
        i32 got = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (got != want_off[i])
            printf("FAIL: %s resolved to %d, expected %d\n", names[i], (int)got,
                   (int)want_off[i]);
        ASSERT_EQ(got, want_off[i]);
    }

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 8u; tdesc.height = 8u;
    tdesc.mip_levels = 1u;
    tdesc.format = RHI_FORMAT_R32_FLOAT;
    tdesc.data = depth; dtex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(dtex));
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.data = scene; stex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(stex));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});
    pair[0] = dtex; pair[1] = stex;

    for (frame = 0; frame < 2; ++frame) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_clear_color(cmd, 1.0f, 0.0f, 1.0f, 1.0f);   /* never an answer */
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_textures_multi(cmd, pair, 2, sampler);
        rhi_cmd_set_uniform_f32(cmd, 0, 0.5f);    /* light x */
        rhi_cmd_set_uniform_f32(cmd, 4, 0.5f);    /* light y */
        rhi_cmd_set_uniform_f32(cmd, 8, frame == 0 ? 0.0f : 0.375f);
        rhi_cmd_set_uniform_f32(cmd, 12, 8.0f);
        rhi_cmd_set_uniform_f32(cmd, 16, 8.0f);
        rhi_cmd_set_uniform_f32(cmd, 20, 1.0f);
        rhi_cmd_set_uniform_f32(cmd, 24, 1.0f);
        rhi_cmd_set_uniform_f32(cmd, 28, 1.0f);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (i = 0; i < 64; ++i) {
            ASSERT_EQ(px[i * 4 + 3], 255u);
            for (ch = 0; ch < 3; ++ch) {
                int got = px[i * 4 + ch];
                /* Frame 0 zeroes the flare, so the scene stripe passes through
                 * exactly and is asserted exactly. */
                int exp = (frame == 0) ? (int)scene[i * 4 + ch]
                                       : (int)want[i >> 3][i & 7][ch];
                int tol = (frame == 0) ? 0 : 1;
                int d = got - exp;
                if (d < 0) d = -d;
                if (d > tol)
                    printf("FAIL: lens flare frame %d pixel %d ch%d = %d, "
                           "expected %d +- %d\n", frame, i, ch, got, exp, tol);
                ASSERT_TRUE(d <= tol);
            }
        }
    }

    rhi_texture_destroy(g_dev, dtex);
    rhi_texture_destroy(g_dev, stex);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(contact_shadow_sidecar_passes_offsets_and_runs_a_clean_march) {
    static unsigned char scene[8 * 8 * 4];
    static float depth[8 * 8];
    static float sky[8 * 8];
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture dtex, stex, skytex;
    RHITexture pair[2];
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    static const char *const names[6] = {
        "u_cs_inv_proj", "u_cs_light_x", "u_cs_light_y", "u_cs_light_z",
        "u_cs_sw", "u_cs_sh"
    };
    /* The sidecar leads with the mat4 so the five floats avoid a 12-byte hole
     * before the 16-byte alignment boundary. */
    static const i32 want[6] = { 0, 64, 68, 72, 76, 80 };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    int frame, i;

    /* Vertical stripes again: the value depends on the column only, so a
     * readback row flip cannot change the answer, and the stripe centres land
     * on texel centres. */
    for (i = 0; i < 64; ++i) {
        scene[i * 4 + 0] = (unsigned char)((i & 7) * 31u);
        scene[i * 4 + 1] = 160u;
        scene[i * 4 + 2] = 45u;
        scene[i * 4 + 3] = 255u;
        depth[i] = 0.5f;
        sky[i] = 1.0f;
    }

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "contact_shadow_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 6; ++i) {
        i32 got = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (got != want[i])
            printf("FAIL: %s resolved to %d, expected %d\n", names[i], (int)got,
                   (int)want[i]);
        ASSERT_EQ(got, want[i]);
    }

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 8u; tdesc.height = 8u;
    tdesc.mip_levels = 1u;
    tdesc.format = RHI_FORMAT_R32_FLOAT;
    tdesc.data = depth; dtex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(dtex));
    tdesc.data = sky; skytex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(skytex));
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.data = scene; stex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(stex));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    /* frame 0: depth 1.0 -> the first early-out, stripes pass through.
     * frame 1: depth 0.5 with the light straight down +Z. screen_step is
     *   light_dir.xy * 5 / res = 0, so all 12 taps sample vUV and never leave
     *   [0,1]; with an identity inv_proj the reconstructed depth of every tap
     *   is the same, and ray_pos.z grows with the offset while
     *   sampled_view.z stays put, so diff = sampled_view.z - ray_pos.z is
     *   negative at every step. No hit, shadow stays 1, and the output is the
     *   scene exactly -- with the march having run all 12 iterations.
     *
     * ⚠️ Neither branch is separately observable, and the reverse check
     * proved it rather than assuming it: disabling the depth early-out leaves
     * this test GREEN, because with the straight-on light the march also finds
     * no occluder; and flattening ray_pos so every step DOES report a hit also
     * leaves it green, because diff is 0 and the test is strict > 0. The reverse
     * check that fires is swapping t0 and t1: frame 0 then reads the depth
     * texture as colour and pixel 0 comes back (255,0,0). So this pins the
     * wiring -- six offsets, both textures through rhi_cmd_bind_textures_multi
     * (order depth-then-scene, R550-A) -- and not which branch runs. */
    for (frame = 0; frame < 2; ++frame) {
        pair[0] = (frame == 0) ? skytex : dtex;
        pair[1] = stex;
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_clear_color(cmd, 1.0f, 0.0f, 1.0f, 1.0f);   /* never an answer */
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_textures_multi(cmd, pair, 2, sampler);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_f32(cmd, 64, 0.0f);   /* light x */
        rhi_cmd_set_uniform_f32(cmd, 68, 0.0f);   /* light y */
        rhi_cmd_set_uniform_f32(cmd, 72, 1.0f);   /* light z */
        rhi_cmd_set_uniform_f32(cmd, 76, 8.0f);   /* sw */
        rhi_cmd_set_uniform_f32(cmd, 80, 8.0f);   /* sh */
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (i = 0; i < 64; ++i) {
            if (px[i * 4 + 0] != scene[i * 4 + 0] ||
                px[i * 4 + 1] != scene[i * 4 + 1] ||
                px[i * 4 + 2] != scene[i * 4 + 2] ||
                px[i * 4 + 3] != 255u) {
                printf("FAIL: contact shadow frame %d pixel %d = "
                       "(%u,%u,%u,%u), expected (%u,%u,%u,255)\n", frame, i,
                       (unsigned)px[i * 4 + 0], (unsigned)px[i * 4 + 1],
                       (unsigned)px[i * 4 + 2], (unsigned)px[i * 4 + 3],
                       (unsigned)scene[i * 4 + 0], (unsigned)scene[i * 4 + 1],
                       (unsigned)scene[i * 4 + 2]);
                break;
            }
        }
        for (i = 0; i < 64; ++i) {
            ASSERT_EQ(px[i * 4 + 0], scene[i * 4 + 0]);
            ASSERT_EQ(px[i * 4 + 1], scene[i * 4 + 1]);
            ASSERT_EQ(px[i * 4 + 2], scene[i * 4 + 2]);
            ASSERT_EQ(px[i * 4 + 3], 255u);
        }
    }

    rhi_texture_destroy(g_dev, dtex);
    rhi_texture_destroy(g_dev, skytex);
    rhi_texture_destroy(g_dev, stex);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(motion_blur_sidecar_reads_depth_and_velocity_and_blurs) {
    static unsigned char grad[8 * 8 * 4];
    static unsigned char solid[8 * 8 * 4];
    static float depth[8 * 8];
    static float far[8 * 8];
    static const unsigned short zero_vel[8 * 8 * 4] = { 0 };
    static const unsigned short vel_x[8 * 8 * 4] = {
        /* 8.0 in R for every texel: half-float 0x4100 = 8.0. Doubled by the
         * shader's 0.5 * res with res = (8,8), so velocity.x = 32 px. */
        0x4100, 0x0000, 0x0000, 0x0000
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture gtex, stex, dtex, ftex, ztex, vtex;
    RHITexture triple[3];
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    static const char *const names[6] = {
        "u_mb_strength", "u_mb_sw", "u_mb_sh", "u_mb_use_velocity",
        "u_mb_inv_proj", "u_mb_prev_vp"
    };
    /* u_mb_use_velocity shares the 12-byte tail, so the mat4 starts at 16 to
     * stay 16B-aligned rather than at 12. A float4x4 is 64 bytes, so the
     * second matrix starts at 80 -- R636, the old marker said 32 and
     * overlapped u_mb_inv_proj. */
    static const i32 want[6] = { 0, 4, 8, 12, 16, 80 };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    int frame, i;

    for (i = 0; i < 64; ++i) {
        /* Vertical stripes: the value depends on the column only, so every row
         * is identical and the pattern survives a readback row flip. A
         * per-texel-index ramp does not -- an earlier draft of this test used
         * one and the row order decided whether it matched. Stripe centres
         * land exactly on texel centres (uv = (col+0.5)/8), so the fetch is
         * exact and the early-out can be asserted byte for byte. */
        grad[i * 4 + 0] = (unsigned char)((i & 7) * 31u);
        grad[i * 4 + 1] = 200u;
        grad[i * 4 + 2] = 30u;
        grad[i * 4 + 3] = 255u;
        solid[i * 4 + 0] = 90u;
        solid[i * 4 + 1] = 140u;
        solid[i * 4 + 2] = 210u;
        solid[i * 4 + 3] = 255u;
        depth[i] = 0.5f;     /* < 1: past the first early-out */
        far[i] = 1.0f;       /* >= 1: takes the first early-out */
    }

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "motion_blur_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 6; ++i) {
        i32 got = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (got != want[i])
            printf("FAIL: %s resolved to %d, expected %d\n", names[i], (int)got,
                   (int)want[i]);
        ASSERT_EQ(got, want[i]);
    }

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 8u; tdesc.height = 8u;
    tdesc.mip_levels = 1u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.data = grad;   gtex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(gtex));
    tdesc.data = solid;  stex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(stex));
    tdesc.format = RHI_FORMAT_R32_FLOAT;
    tdesc.data = depth;  dtex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(dtex));
    tdesc.data = far;    ftex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(ftex));
    tdesc.format = RHI_FORMAT_R16G16_SFLOAT;
    tdesc.data = zero_vel; ztex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(ztex));
    tdesc.data = vel_x;     vtex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(vtex));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    /* frame 0  depth 1.0        -> first early-out, gradient passes through
     * frame 1  depth 0.5, no vel -> vel_len < 0.5 early-out, gradient through
     * frame 2  depth 0.5, use_velocity = 0 -> the RECONSTRUCTION branch:
     *          the shader rebuilds the previous clip position from
     *          u_mb_inv_proj / u_mb_prev_vp. Both are the identity here, so
     *          prev_uv collapses to uv, the velocity is exactly zero and the
     *          vel_len early-out hands back the gradient untouched. This is
     *          the LAYOUT GUARD: with a matrix at the wrong offset the read
     *          is garbage, the velocity is not zero, the blur loop runs and
     *          the stripes come back averaged instead of exact.
     * frame 3  depth 0.5, vel 32px -> the blur loop RUNS. The colour is solid,
     *          so every tap returns the same value and the weighted average is
     *          that value -- which proves t2 and u_mb_use_velocity reached the
     *          shader (a zero velocity would have taken the frame-1 path) while
     *          keeping the assertion exact.
     *          +-1 because the weighted sum is not bit-exact in fp32. */
    for (frame = 0; frame < 4; ++frame) {
        const unsigned char *want_src = (frame == 3) ? solid : grad;
        triple[0] = (frame == 3) ? stex : gtex;
        triple[1] = (frame == 0) ? ftex : dtex;
        triple[2] = (frame == 3) ? vtex : ztex;
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_clear_color(cmd, 1.0f, 0.0f, 1.0f, 1.0f);   /* never an answer */
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_textures_multi(cmd, triple, 3, sampler);
        rhi_cmd_set_uniform_f32(cmd, 0, 0.5f);    /* u_mb_strength */
        rhi_cmd_set_uniform_f32(cmd, 4, 8.0f);    /* u_mb_sw */
        rhi_cmd_set_uniform_f32(cmd, 8, 8.0f);    /* u_mb_sh */
        rhi_cmd_set_uniform_f32(cmd, 12, (frame == 0 || frame == 2) ? 0.0f : 1.0f);
        rhi_cmd_set_uniform_mat4(cmd, 16, identity);
        rhi_cmd_set_uniform_mat4(cmd, 80, identity);
        /* The vel_len early-out is NOT separately observable
         * either -- the reverse check proved it: disabling it leaves
         * this test GREEN, because at zero velocity sample_count is 0,
         * the loop degenerates to a single tap at uv with weight 1, and
         * step_size is 0. Both routes return the same colour. The
         * reverse check that DOES fire is swapping t0 and t1: frame 0
         * then reads the depth texture as colour and pixel 0 comes
         * back 255 instead of 0. And frame 3 only proves the loop
         * executes -- on a solid source every tap is equal, so the
         * blur GEOMETRY (span, jitter, weights) is not asserted here.
         */
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (i = 0; i < 64; ++i) {
            int ch;
            ASSERT_EQ(px[i * 4 + 3], 255u);
            for (ch = 0; ch < 3; ++ch) {
                int got = px[i * 4 + ch];
                int exp = want_src[i * 4 + ch];
                int d = got - exp;
                if (d < 0) d = -d;
                if (d > (frame == 3 ? 1 : 0)) {
                    printf("FAIL: motion blur frame %d pixel %d ch%d = %d, "
                           "expected %d +- %d\n", frame, i, ch, got, exp,
                           frame == 3 ? 1 : 0);
                }
                ASSERT_TRUE(d <= (frame == 3 ? 1 : 0));
            }
        }
    }

    rhi_texture_destroy(g_dev, gtex);
    rhi_texture_destroy(g_dev, stex);
    rhi_texture_destroy(g_dev, dtex);
    rhi_texture_destroy(g_dev, ftex);
    rhi_texture_destroy(g_dev, ztex);
    rhi_texture_destroy(g_dev, vtex);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(taa_sidecar_blends_history_through_the_neighbourhood_aabb) {
    static unsigned char curr[8 * 8 * 4];
    static unsigned char hist[8 * 8 * 4];
    static float depth[8 * 8];
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture ctex, htex, dtex, vtex;
    RHITexture quad[4];
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    static const char *const names[7] = {
        "u_taa_curr_vp", "u_taa_prev_vp", "u_taa_inv_proj", "u_taa_sw",
        "u_taa_sh", "u_taa_first_frame", "u_taa_use_velocity"
    };
    static const i32 want[7] = { 0, 64, 128, 192, 196, 200, 204 };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    int frame, r, c, i;

    /* An 8x8 checkerboard of 0 and 255 is chosen so that EVERY pixel's 3x3
     * neighbourhood spans the full [0,255] in each channel. That matters:
     * clip_aabb() pulls anything outside the neighbourhood box back to it, so
     * with a flat or ramped source the history colour would be clamped onto
     * the centre pixel and the blend would be invisible. With a checkerboard
     * a solid history of 128 survives unclipped, and the result is exactly
     * derivable:
     *
     *   mix(128, curr, 0.1) = 128 + (curr - 128) * 0.1
     *     curr =   0 -> 115.2000 -> byte 115
     *     curr = 255 -> 140.7000 -> byte 141
     *
     * Neither lands on .5, so exact bytes are safe here (unlike the DOF blur,
     * which needed a +-2 bound for exactly that reason). An 8x8 checkerboard
     * is also symmetric under a row flip, so readback orientation cannot
     * matter.
     *
     * With identity matrices and use_velocity = 0, prev_uv collapses back to
     * uv: ndc = uv*2-1, the identity inv_proj and prev_vp leave x and y
     * untouched, so prev_uv = (uv*2-1)*0.5 + 0.5 = uv. The history is
     * therefore sampled from the same place as the current colour, which is
     * what makes a solid history texture a valid input. */
    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            unsigned char v = ((r + c) & 1) ? 255u : 0u;
            i = (r * 8 + c) * 4;
            curr[i + 0] = v; curr[i + 1] = v; curr[i + 2] = v; curr[i + 3] = 255u;
            hist[i + 0] = 128u; hist[i + 1] = 128u; hist[i + 2] = 128u;
            hist[i + 3] = 255u;
            depth[r * 8 + c] = 0.5f;     /* < 1, so the temporal block runs */
        }
    }

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "taa_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 7; ++i) {
        i32 got = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (got != want[i])
            printf("FAIL: %s resolved to %d, expected %d\n", names[i], (int)got,
                   (int)want[i]);
        ASSERT_EQ(got, want[i]);
    }
    /* GLSL const (0.1) in the twin, so taa_apply's write is a no-op on GL. */
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_taa_blend"), -1);

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 8u; tdesc.height = 8u;
    tdesc.mip_levels = 1u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.data = curr; ctex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(ctex));
    tdesc.data = hist; htex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(htex));
    tdesc.format = RHI_FORMAT_R32_FLOAT;
    tdesc.data = depth; dtex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(dtex));
    tdesc.format = RHI_FORMAT_R16G16_SFLOAT;
    {
        static const unsigned short zero[8 * 8 * 4] = { 0 };
        tdesc.data = zero;
    }
    vtex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(vtex));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});
    quad[0] = ctex; quad[1] = htex; quad[2] = dtex; quad[3] = vtex;

    /* frame 0: first_frame = 1 -> the temporal block is skipped and the
     * checkerboard must come through untouched, which is the control that says
     * the 115/141 in frame 1 really is the blend. */
    for (frame = 0; frame < 2; ++frame) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_clear_color(cmd, 1.0f, 0.0f, 1.0f, 1.0f);   /* never an answer */
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_textures_multi(cmd, quad, 4, sampler);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_set_uniform_mat4(cmd, 128, identity);
        rhi_cmd_set_uniform_f32(cmd, 192, 8.0f);
        rhi_cmd_set_uniform_f32(cmd, 196, 8.0f);
        rhi_cmd_set_uniform_f32(cmd, 200, frame == 0 ? 1.0f : 0.0f);
        rhi_cmd_set_uniform_f32(cmd, 204, 0.0f);   /* use_velocity off */
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (r = 0; r < 8; ++r) {
            for (c = 0; c < 8; ++c) {
                unsigned char want_px = frame == 0
                    ? (unsigned char)(((r + c) & 1) ? 255u : 0u)
                    : (unsigned char)(((r + c) & 1) ? 141u : 115u);
                i = (r * 8 + c) * 4;
                if (px[i + 0] != want_px || px[i + 1] != want_px ||
                    px[i + 2] != want_px || px[i + 3] != 255u) {
                    printf("FAIL: taa frame %d pixel (c=%d,r=%d) = "
                           "(%u,%u,%u,%u), expected (%u,%u,%u,255)\n", frame,
                           c, r, (unsigned)px[i + 0], (unsigned)px[i + 1],
                           (unsigned)px[i + 2], (unsigned)px[i + 3],
                           (unsigned)want_px, (unsigned)want_px,
                           (unsigned)want_px);
                }
                ASSERT_EQ(px[i + 0], want_px);
                ASSERT_EQ(px[i + 1], want_px);
                ASSERT_EQ(px[i + 2], want_px);
                ASSERT_EQ(px[i + 3], 255u);
            }
        }
    }

    rhi_texture_destroy(g_dev, ctex);
    rhi_texture_destroy(g_dev, htex);
    rhi_texture_destroy(g_dev, dtex);
    rhi_texture_destroy(g_dev, vtex);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(ssr_sidecar_pins_offsets_and_both_early_outs) {
    static unsigned char colour[8 * 8 * 4];
    static float sky[8 * 8];
    static float flat[8 * 8];
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture ctex, skytex, flttex;
    RHITexture pair[2];
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    RHICapabilities caps;
    static const char *const names[7] = {
        "u_ssr_proj", "u_ssr_inv_proj", "u_ssr_view", "u_ssr_sw",
        "u_ssr_sh", "u_ssr_max_steps", "u_ssr_stride"
    };
    static const i32 want[7] = { 0, 64, 128, 192, 196, 200, 204 };
    const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    int frame, i;

    for (i = 0; i < 64; ++i) {
        colour[i * 4 + 0] = (unsigned char)(40 + (i & 7) * 20u);
        colour[i * 4 + 1] = 90u;
        colour[i * 4 + 2] = 200u;
        colour[i * 4 + 3] = 255u;
        sky[i] = 1.0f;    /* depth >= 1 -> first early-out */
        flat[i] = 0.5f;   /* constant depth -> plane normal -> second early-out */
    }

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "ssr_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 7; ++i) {
        i32 got = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (got != want[i])
            printf("FAIL: %s resolved to %d, expected %d\n", names[i], (int)got,
                   (int)want[i]);
        ASSERT_EQ(got, want[i]);
    }
    /* GLSL const (R89-2), so ssr_apply's write is a no-op on GL too. */
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_ssr_thickness"), -1);

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 8u; tdesc.height = 8u;
    tdesc.mip_levels = 1u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.data = colour;
    ctex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(ctex));
    tdesc.format = RHI_FORMAT_R32_FLOAT;
    tdesc.data = sky;
    skytex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(skytex));
    tdesc.data = flat;
    flttex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(flttex));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    ASSERT_TRUE(rhi_device_get_capabilities(g_dev, &caps));
    for (frame = 0; frame < 2; ++frame) {
        pair[0] = ctex;
        pair[1] = frame == 0 ? skytex : flttex;
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 0.0f);   /* never an answer */
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_textures_multi(cmd, pair, 2, sampler);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_set_uniform_mat4(cmd, 128, identity);
        rhi_cmd_set_uniform_f32(cmd, 192, 8.0f);
        rhi_cmd_set_uniform_f32(cmd, 196, 8.0f);
        rhi_cmd_set_uniform_f32(cmd, 200, 32.0f);
        rhi_cmd_set_uniform_f32(cmd, 204, 2.0f);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (i = 0; i < 64; ++i) {
            if (px[i * 4 + 0] != colour[i * 4 + 0] ||
                px[i * 4 + 1] != colour[i * 4 + 1] ||
                px[i * 4 + 2] != colour[i * 4 + 2] ||
                px[i * 4 + 3] != 255u) {
                printf("FAIL: ssr frame %d pixel %d = (%u,%u,%u,%u), expected "
                       "(%u,%u,%u,255) -- the early-out must return the scene "
                       "colour untouched\n", frame, i,
                       (unsigned)px[i * 4 + 0], (unsigned)px[i * 4 + 1],
                       (unsigned)px[i * 4 + 2], (unsigned)px[i * 4 + 3],
                       (unsigned)colour[i * 4 + 0], (unsigned)colour[i * 4 + 1],
                       (unsigned)colour[i * 4 + 2]);
                break;
            }
        }
        for (i = 0; i < 64; ++i) {
            ASSERT_EQ(px[i * 4 + 0], colour[i * 4 + 0]);
            ASSERT_EQ(px[i * 4 + 1], colour[i * 4 + 1]);
            ASSERT_EQ(px[i * 4 + 2], colour[i * 4 + 2]);
            ASSERT_EQ(px[i * 4 + 3], 255u);
        }
    }

    rhi_texture_destroy(g_dev, ctex);
    rhi_texture_destroy(g_dev, skytex);
    rhi_texture_destroy(g_dev, flttex);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(forward_clip_z_conversion_keeps_near_geometry_unclipped) {
    /* ONE quad at eye distance 0.15, y = +-0.6, facing the camera in view
     * space (looking down -Z).
     *
     * Its vertical extent is +-6.93 in NDC, so it covers the whole 8x8 target
     * at eye distance 0.15. The rasteriser's z clip is per pixel: a pixel
     * survives when (z + w) / 2 is inside [0, w], which is eye distance 0.15
     * to about 0.2 -- three of the eight rows. Where ndc_z < 0 the quad is
     * gone and the clear colour shows.
     *
     * There is deliberately no far quad here. One would cover the same pixels
     * and paint over the near quad, and the earlier draft of this test made
     * exactly that mistake: geometry rendered (64 green pixels) but the near
     * band never showed. Only the near geometry can demonstrate clipping.
     *
     * x is +-0.6 because a quad at x = 0 is degenerate and covers nothing. */
    static const float verts[6 * 3] = {
        -0.6f,  0.6f, -0.15f,   0.6f,  0.6f, -0.15f,   0.6f, -0.6f, -0.15f,
        -0.6f,  0.6f, -0.15f,   0.6f, -0.6f, -0.15f,  -0.6f, -0.6f, -0.15f
    };
    /* mat4_perspective(60 deg vertical, aspect 1, near 0.1, far 100),
     * column-major, from mat4_perspective in src/math/math.c:
     *   e[0][0] = f/a = 1/tan(30)   =  1.7320508
     *   e[1][1] = f                 =  1.7320508
     *   e[2][2] = -(far+near)/(f-n) = -1.0020020
     *   e[2][3] = -1                -> the implicit last row, w = -z_view
     *   e[3][2] = -2*far*near/(f-n) = -0.2002002
     */
    static const float proj[16] = {
        1.7320508f, 0.0f,  0.0f,        0.0f,
        0.0f,       1.7320508f, 0.0f,   0.0f,
        0.0f,       0.0f,      -1.0020020f, 0.0f,
        0.0f,       0.0f,      -0.2002002f, 1.0f
    };
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    int i;

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "depth_clip_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "depth_clip_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.vertex_stride = 12u;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 1.0f, 1.0f);   /* never an answer */
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, 0, identity);
    rhi_cmd_set_uniform_mat4(cmd, 64, identity);
    rhi_cmd_set_uniform_mat4(cmd, 128, proj);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    /* With the conversion the quad survives everywhere, so all 64 pixels are
     * red -- which is the point: red is what ndc_z < 0 means, and on D3D12
     * that band is clipped unless the vertex stage converts. A blue clear
     * means the near geometry disappeared, i.e. exactly the pre-R621 bug.
     * (The first draft of this probe also drew a far quad at 1.0 and expected
     * both colours; it covered the same pixels and painted over the near one,
     * so the assertion was wrong twice over -- geometry rendered but the near
     * band never showed.) */
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < 64; ++i) {
        if (px[i * 4 + 0] != 255u || px[i * 4 + 1] != 0u) {
            printf("FAIL: clip.z probe pixel %d = (%u,%u,%u), expected "
                   "(255,0,0) red = survives the conversion, blue = clipped\n",
                   i, (unsigned)px[i * 4 + 0], (unsigned)px[i * 4 + 1],
                   (unsigned)px[i * 4 + 2]);
            break;
        }
    }
    for (i = 0; i < 64; ++i) {
        ASSERT_EQ(px[i * 4 + 0], 255u);
        ASSERT_EQ(px[i * 4 + 1], 0u);
        ASSERT_EQ(px[i * 4 + 2], 0u);
        ASSERT_EQ(px[i * 4 + 3], 255u);
    }

    rhi_buffer_destroy(g_dev, vbo);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(dof_sidecar_passes_focus_and_blurs_out_of_focus_via_multi_bind) {
    static unsigned char colour[8 * 8 * 4];
    static float depth[8 * 8];
    static const unsigned char model_red[8 * 8] = {
        170, 170, 170, 170,  85,  85,  85,  85,
        170, 170, 170, 170,  85,  85,  85,  85,
        170, 128, 128, 142, 113, 128, 128,  85,
        170, 128, 128, 142, 113, 128, 128,  85,
        170, 128, 128, 142, 113, 128, 128,  85,
        170, 128, 128, 142, 113, 128, 128,  85,
        170, 170, 170, 170,  85,  85,  85,  85,
        170, 170, 170, 170,  85,  85,  85,  85
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture ctex, dtex;
    RHITexture pair[2];
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc_focus, loc_range, loc_sw, loc_sh;
    int frame, r, c, i;

    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            i = (r * 8 + c) * 4;
            colour[i + 0] = c < 4 ? 255u : 0u;
            colour[i + 1] = 0u;
            colour[i + 2] = c < 4 ? 0u : 255u;
            colour[i + 3] = 255u;
            depth[r * 8 + c] = 0.5f;
        }
    }

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "dof_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    loc_focus = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_dof_focus");
    loc_range = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_dof_range");
    loc_sw    = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_dof_sw");
    loc_sh    = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_dof_sh");
    ASSERT_EQ(loc_focus, 0);
    ASSERT_EQ(loc_range, 4);
    ASSERT_EQ(loc_sw, 8);
    ASSERT_EQ(loc_sh, 12);
    /* GLSL consts in the twin (R89-2), so dof_apply's writes are no-ops on
     * GL too. */
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_dof_near"), -1);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_dof_far"), -1);

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 8u; tdesc.height = 8u;
    tdesc.mip_levels = 1u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.data = colour;
    ctex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(ctex));
    tdesc.format = RHI_FORMAT_R32_FLOAT;
    tdesc.data = depth;
    dtex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(dtex));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});
    pair[0] = ctex;
    pair[1] = dtex;

    for (frame = 0; frame < 2; ++frame) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_clear_color(cmd, 0.0f, 1.0f, 0.0f, 1.0f);   /* never an answer */
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_textures_multi(cmd, pair, 2, sampler);
        rhi_cmd_set_uniform_f32(cmd, loc_focus, frame == 0 ? 0.1998f : 100.1998f);
        rhi_cmd_set_uniform_f32(cmd, loc_range, 5.0f);
        rhi_cmd_set_uniform_f32(cmd, loc_sw, 8.0f);
        rhi_cmd_set_uniform_f32(cmd, loc_sh, 8.0f);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (r = 0; r < 8; ++r) {
            for (c = 0; c < 8; ++c) {
                int red, blue, want_red;
                i = (r * 8 + c) * 4;
                red = px[i + 0];
                blue = px[i + 2];
                ASSERT_EQ(px[i + 1], 0u);
                ASSERT_EQ(px[i + 3], 255u);
                if (frame == 0) {
                    want_red = c < 4 ? 255 : 0;
                    if (red != want_red || blue != 255 - want_red)
                        printf("FAIL: dof in-focus pixel (c=%d,r=%d) = (%d,0,%d), "
                               "expected (%d,0,%d)\n", c, r, red, blue,
                               want_red, 255 - want_red);
                    ASSERT_EQ(red, want_red);
                    ASSERT_EQ(blue, 255 - want_red);
                } else {
                    want_red = (int)model_red[r * 8 + c];
                    if (red < want_red - 2 || red > want_red + 2 ||
                        red + blue < 253 || red + blue > 257)
                        printf("FAIL: dof blurred pixel (c=%d,r=%d) = (%d,0,%d), "
                               "expected red %d+-2 and red+blue 255+-2\n",
                               c, r, red, blue, want_red);
                    ASSERT_TRUE(red >= want_red - 2 && red <= want_red + 2);
                    ASSERT_TRUE(red + blue >= 253 && red + blue <= 257);
                }
            }
        }
    }

    rhi_texture_destroy(g_dev, ctex);
    rhi_texture_destroy(g_dev, dtex);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* R632: the instanced sidecar pair, and the pixel proof R632 shipped without.
 *
 * R632 moved the instanced pass's four lighting uniforms out of the push
 * block and into the temporal CBV, because six push words plus two mat4 is
 * 320 bytes and D3D12's rhi_cmd_set_uniform_* only reaches root constants.
 * That left the sidecar's CBV layout hand-aligned against the engine's
 * ForwardTemporalUbo with nothing asserting the two agree, so this test
 * pins the shader's own reading of it: each frame writes known values at
 * known byte offsets and asserts the colour that only comes out if the
 * shader read them from exactly those offsets.
 *
 * Lighting is made degenerate the way the blinn_phong tests do it, so the
 * expected colour is analytic rather than modelled:
 *   vertices are on the z = 0 plane with N = (0,0,1)
 *   frame A  light_dir = (0,-1,0)  -> L = (0,1,0), diff = 0, and with the
 *            camera at (0,0,-10) H.z < 0 so spec = 0. Output is
 *            ambient * albedo exactly, which pins the AMBIENT offset and
 *            proves the CBV is bound at all.
 *   frame B  light_dir = (0,0,-1)  -> L = (0,0,1) = N, so diff = 1 and the
 *            output is (ambient + light_color) * albedo. With ambient zeroed
 *            this pins LIGHT_DIR's z (the 1.0 in diff) and LIGHT_COLOR's
 *            three components together.
 *
 * u_camera_pos cannot be pinned by colour here -- with the degenerate setup
 * the view vector only reaches spec, which is zero either way -- so it is
 * pinned structurally instead: the vertex stage's SV_InstanceID must come
 * through, which is what makes the camera-position member worth carrying.
 *
 * The albedo choices avoid .5 exactly: 255 * (0.4, 0.2, 0.08) = (102, 51,
 * 20.4), so the assertions are byte-exact rather than tolerance-based --
 * unlike most of the other post proofs. */
TEST(instanced_sidecar_reads_lighting_from_the_temporal_cbv) {
    static const float verts[6 * 8] = {
        /*  aPos                 aNormal              aUV   */
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f
    };
    /* One instance row set: identity model (rows 0..3) and identity
     * prev_model (rows 4..7), so world_pos == a_pos and the velocity is
     * driven purely by u_prev_vp. */
    static const float rows[8 * 4] = {
        1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1,
        1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1
    };
    static const unsigned char white[4 * 4 * 4] = {
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255
    };
    /* Byte-identical to ForwardTemporalUbo in main.c. Writing the members by
     * offset rather than through a struct copy is deliberate: it is the
     * offsets that have to agree, and doing it this way keeps the test
     * independent of the engine's own layout. */
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    typedef struct { f32 cam[3]; f32 cam_pad; f32 prev_vp[16];
                     f32 prev_model[16];
                     f32 dir[3]; f32 dir_pad;
                     f32 col[3]; f32 col_pad;
                     f32 amb[3]; f32 amb_pad; } Temporal;
    const RHIFormat formats[2] = {RHI_FORMAT_R8G8B8A8_UNORM, RHI_FORMAT_R16G16_SFLOAT};
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHITextureDesc tdesc;
    RHITexture albedo, inst;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bdesc;
    RHIBuffer vbo, ubo;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char rt0[8 * 8 * 4];
    unsigned short rt1[8 * 8 * 2];
    Temporal t;
    int frame, i;
    static const unsigned char want[2][3] = {
        { 102, 51, 20 },   /* ambient only */
        { 102, 51, 20 }    /* ambient 0 + light_color, diff = 1 */
    };

    memset(&t, 0, sizeof(t));
    t.cam[0] = 0.0f; t.cam[1] = 0.0f; t.cam[2] = -10.0f;
    memcpy(t.prev_vp, identity, sizeof(identity));
    memcpy(t.prev_model, identity, sizeof(identity));
    t.amb[0] = 0.4f; t.amb[1] = 0.2f; t.amb[2] = 0.08f;
    t.col[0] = 0.4f; t.col[1] = 0.2f; t.col[2] = 0.08f;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 4u; tdesc.height = 4u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.mip_levels = 1u;
    tdesc.data = white;
    albedo = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(albedo));

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));
    bdesc.size = sizeof(rows);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;   /* keeps it off the UAV path */
    bdesc.initial_data = rows;
    inst = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(inst));

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(t);
    bdesc.usage = RHI_BUFFER_USAGE_UNIFORM;
    bdesc.initial_data = &t;
    ubo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(ubo));

    vs = rhi_shader_create(g_dev, "instanced_mrt_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "instanced_mrt_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.vertex_stride = 32u;                 /* aPos3 + aNormal3 + aUV2 */
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.mrt_attachment_count = 2u;
    pd.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    /* Only u_view / u_proj are push members now; the four lighting uniforms
     * must NOT resolve, or the port has silently reverted to the old shape. */
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_view"), 0);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_proj"), 64);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_light_dir"), -1);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_light_color"), -1);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_ambient"), -1);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_camera_pos"), -1);

    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    for (frame = 0; frame < 2; ++frame) {
        if (frame == 0) {
            t.dir[0] = 0.0f; t.dir[1] = -1.0f; t.dir[2] = 0.0f;
            t.amb[0] = 0.4f;  t.amb[1] = 0.2f;  t.amb[2] = 0.08f;
        } else {
            t.dir[0] = 0.0f; t.dir[1] = 0.0f;  t.dir[2] = -1.0f;
            t.amb[0] = 0.0f;  t.amb[1] = 0.0f;  t.amb[2] = 0.0f;
        }
        rhi_buffer_update(g_dev, ubo, &t, sizeof(t));
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_mrt_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_texture(cmd, albedo, sampler, 0u);
        rhi_cmd_bind_texel_buffers(cmd, inst, RHI_HANDLE_NULL);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_bind_uniform_buffer(cmd, ubo, 1u);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_draw(cmd, 6u, 1u);
        rhi_mrt_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(rt0, 0, sizeof(rt0));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], rt0, sizeof(rt0)));
        for (i = 0; i < 64; ++i) {
            if (rt0[i * 4 + 0] != want[frame][0] ||
                rt0[i * 4 + 1] != want[frame][1] ||
                rt0[i * 4 + 2] != want[frame][2] ||
                rt0[i * 4 + 3] != 255u) {
                printf("FAIL: instanced frame %d pixel %d = (%u,%u,%u,%u), "
                       "expected (%u,%u,%u,255)\n", frame, i,
                       (unsigned)rt0[i*4+0], (unsigned)rt0[i*4+1],
                       (unsigned)rt0[i*4+2], (unsigned)rt0[i*4+3],
                       (unsigned)want[frame][0], (unsigned)want[frame][1],
                       (unsigned)want[frame][2]);
                break;
            }
        }
        for (i = 0; i < 64; ++i) {
            ASSERT_EQ(rt0[i * 4 + 0], want[frame][0]);
            ASSERT_EQ(rt0[i * 4 + 1], want[frame][1]);
            ASSERT_EQ(rt0[i * 4 + 2], want[frame][2]);
            ASSERT_EQ(rt0[i * 4 + 3], 255u);
        }
        /* Identity prev_vp and prev_model make the motion vector exactly
         * +0.0 on the raw bits, so RT1 also proves the temporal block was
         * read rather than left unbound. */
        memset(rt1, 0, sizeof(rt1));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], rt1, sizeof(rt1)));
        for (i = 0; i < 64 * 2; ++i)
            ASSERT_EQ(rt1[i], 0u);
    }

    rhi_texture_destroy(g_dev, albedo);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, inst);
    rhi_buffer_destroy(g_dev, ubo);
    rhi_mrt_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* R636: the skinned twin of the instanced guard above. R634 ported the
 * skinned pass but left its temporal CBV layout unproven: the sidecar
 * hand-writes the ForwardTemporal member offsets, and a drift there reads
 * the wrong lighting with no error. The instanced guard does not cover it
 * -- the two sidecars declare the struct separately, so the skinned one
 * can drift on its own. */
TEST(skinned_sidecar_reads_lighting_from_the_temporal_cbv) {
    typedef struct { f32 pos[3]; f32 nrm[3]; f32 uv[2]; u32 joints[4];
                     f32 weights[4]; } SkinVert;
    /* The skinned input layout is 64 bytes: POSITION 3, NORMAL 3, TEXCOORD 2,
     * BLENDINDICES 4, BLENDWEIGHT 4. Joint 0 is the identity and the single
     * weight is 1, so skin == identity and world == aPos. */
    static const SkinVert verts[6] = {
        { { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f },
          { 0u, 0u, 0u, 0u }, { 1.0f, 0.0f, 0.0f, 0.0f } },
        { {  1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f },
          { 0u, 0u, 0u, 0u }, { 1.0f, 0.0f, 0.0f, 0.0f } },
        { {  1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f },
          { 0u, 0u, 0u, 0u }, { 1.0f, 0.0f, 0.0f, 0.0f } },
        { { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f },
          { 0u, 0u, 0u, 0u }, { 1.0f, 0.0f, 0.0f, 0.0f } },
        { {  1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f },
          { 0u, 0u, 0u, 0u }, { 1.0f, 0.0f, 0.0f, 0.0f } },
        { { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f },
          { 0u, 0u, 0u, 0u }, { 1.0f, 0.0f, 0.0f, 0.0f } }
    };
    static unsigned char white[4 * 4 * 4] = {
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255
    };
    /* Byte-identical to ForwardTemporalUbo in main.c. Writing the members by
     * offset rather than through a struct copy is deliberate: it is the
     * offsets that have to agree, and doing it this way keeps the test
     * independent of the engine's own layout. */
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    typedef struct { f32 cam[3]; f32 cam_pad; f32 prev_vp[16];
                     f32 prev_model[16];
                     f32 dir[3]; f32 dir_pad;
                     f32 col[3]; f32 col_pad;
                     f32 amb[3]; f32 amb_pad; } Temporal;
    /* The joint matrices are a raw buffer of float4: joint 0 is four column
     * float4s, and the PREVIOUS joint matrices sit 512 elements further in
     * (the offset the sidecar indexes). */
    static float joints[516 * 4];
    const RHIFormat formats[2] = {RHI_FORMAT_R8G8B8A8_UNORM, RHI_FORMAT_R16G16_SFLOAT};
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHITextureDesc tdesc;
    RHITexture albedo;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bdesc;
    RHIBuffer vbo, ubo, jbo;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char rt0[8 * 8 * 4];
    unsigned short rt1[8 * 8 * 2];
    Temporal t;
    int frame, i;
    static const unsigned char want[2][3] = {
        { 102, 51, 20 },   /* ambient only */
        { 102, 51, 20 }    /* ambient 0 + light_color, diff = 1 */
    };

    memset(joints, 0, sizeof(joints));
    joints[0] = 1.0f; joints[5] = 1.0f; joints[10] = 1.0f; joints[15] = 1.0f;
    joints[512 * 4 + 0]  = 1.0f;
    joints[512 * 4 + 5]  = 1.0f;
    joints[512 * 4 + 10] = 1.0f;
    joints[512 * 4 + 15] = 1.0f;

    memset(&t, 0, sizeof(t));
    t.cam[0] = 0.0f; t.cam[1] = 0.0f; t.cam[2] = -10.0f;
    memcpy(t.prev_vp, identity, sizeof(identity));
    memcpy(t.prev_model, identity, sizeof(identity));
    t.amb[0] = 0.4f; t.amb[1] = 0.2f; t.amb[2] = 0.08f;
    t.col[0] = 0.4f; t.col[1] = 0.2f; t.col[2] = 0.08f;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 4u; tdesc.height = 4u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.mip_levels = 1u;
    tdesc.data = white;
    albedo = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(albedo));

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));
    bdesc.size = sizeof(joints);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;   /* keeps it off the UAV path */
    bdesc.initial_data = joints;
    jbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(jbo));

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(t);
    bdesc.usage = RHI_BUFFER_USAGE_UNIFORM;
    bdesc.initial_data = &t;
    ubo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(ubo));

    vs = rhi_shader_create(g_dev, "skinned_mrt_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "skinned_mrt_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.skinned_vertex = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.mrt_attachment_count = 2u;
    pd.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    /* Only u_view / u_proj are push members now; the four lighting uniforms
     * must NOT resolve, or the port has silently reverted to the old shape. */
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_view"), 0);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_proj"), 64);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "light_dir"), -1);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "light_color"), -1);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "ambient"), -1);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_camera_pos"), -1);

    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    for (frame = 0; frame < 2; ++frame) {
        if (frame == 0) {
            t.dir[0] = 0.0f; t.dir[1] = -1.0f; t.dir[2] = 0.0f;
            t.amb[0] = 0.4f;  t.amb[1] = 0.2f;  t.amb[2] = 0.08f;
        } else {
            t.dir[0] = 0.0f; t.dir[1] = 0.0f;  t.dir[2] = -1.0f;
            t.amb[0] = 0.0f;  t.amb[1] = 0.0f;  t.amb[2] = 0.0f;
        }
        rhi_buffer_update(g_dev, ubo, &t, sizeof(t));
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_mrt_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_texture(cmd, albedo, sampler, 0u);
        rhi_cmd_bind_texel_buffers(cmd, jbo, RHI_HANDLE_NULL);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_bind_uniform_buffer(cmd, ubo, 1u);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_draw(cmd, 6u, 1u);
        rhi_mrt_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(rt0, 0, sizeof(rt0));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], rt0, sizeof(rt0)));
        for (i = 0; i < 64; ++i) {
            if (rt0[i * 4 + 0] != want[frame][0] ||
                rt0[i * 4 + 1] != want[frame][1] ||
                rt0[i * 4 + 2] != want[frame][2] ||
                rt0[i * 4 + 3] != 255u) {
                printf("FAIL: skinned frame %d pixel %d = (%u,%u,%u,%u), "
                       "expected (%u,%u,%u,255)\n", frame, i,
                       (unsigned)rt0[i*4+0], (unsigned)rt0[i*4+1],
                       (unsigned)rt0[i*4+2], (unsigned)rt0[i*4+3],
                       (unsigned)want[frame][0], (unsigned)want[frame][1],
                       (unsigned)want[frame][2]);
                break;
            }
        }
        for (i = 0; i < 64; ++i) {
            ASSERT_EQ(rt0[i * 4 + 0], want[frame][0]);
            ASSERT_EQ(rt0[i * 4 + 1], want[frame][1]);
            ASSERT_EQ(rt0[i * 4 + 2], want[frame][2]);
            ASSERT_EQ(rt0[i * 4 + 3], 255u);
        }
        /* Identity prev_vp and an identity joint matrix make the motion
         * vector exactly +0.0 on the raw bits, so RT1 also proves the
         * temporal block was read rather than left unbound. */
        memset(rt1, 0, sizeof(rt1));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], rt1, sizeof(rt1)));
        for (i = 0; i < 64 * 2; ++i)
            ASSERT_EQ(rt1[i], 0u);
    }

    rhi_texture_destroy(g_dev, albedo);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, jbo);
    rhi_buffer_destroy(g_dev, ubo);
    rhi_mrt_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(fxaa_sidecar_blends_the_box_edge_and_passes_flat_regions) {
    static unsigned char box_tex[8 * 8 * 4];
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture src;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc_sw, loc_sh;
    int r, c, i;
    int blended = 0, blend_row = -1, blend_c3 = 0, blend_c4 = 0, white = 0;

    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            unsigned char v = (c >= 3 && c <= 4 && r >= 3 && r <= 4) ? 255u : 0u;
            i = (r * 8 + c) * 4;
            box_tex[i + 0] = v; box_tex[i + 1] = v; box_tex[i + 2] = v;
            box_tex[i + 3] = 255u;
        }
    }

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "fxaa_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    loc_sw = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_fxaa_sw");
    loc_sh = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_fxaa_sh");
    ASSERT_EQ(loc_sw, 0);
    ASSERT_EQ(loc_sh, 4);
    /* A GLSL const in the twin, so fxaa_apply's write is a no-op on GL too. */
    ASSERT_EQ(rhi_pipeline_get_uniform_location(g_dev, pipe, "u_fxaa_threshold"), -1);

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 8u; tdesc.height = 8u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.mip_levels = 1u;
    tdesc.data = box_tex;
    src = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(src));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_clear_color(cmd, 0.0f, 1.0f, 0.0f, 1.0f);   /* never an answer */
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_texture(cmd, src, sampler, 0u);
    rhi_cmd_set_uniform_f32(cmd, loc_sw, 8.0f);
    rhi_cmd_set_uniform_f32(cmd, loc_sh, 8.0f);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (r = 0; r < 8; ++r) {
        for (c = 0; c < 8; ++c) {
            int in_window = (c >= 2 && c <= 5 && r >= 2 && r <= 5);
            unsigned v;
            i = (r * 8 + c) * 4;
            v = px[i + 0];
            /* FXAA keeps grey grey; any channel split means a wrong tap. */
            ASSERT_EQ(px[i + 1], px[i + 0]);
            ASSERT_EQ(px[i + 2], px[i + 0]);
            ASSERT_EQ(px[i + 3], 255u);
            if (!in_window) {
                if (v != 0u)
                    printf("FAIL: fxaa flat pixel (c=%d,r=%d) = %u, expected 0\n",
                           c, r, v);
                ASSERT_EQ(v, 0u);
                continue;
            }
            if (v == 255u) white++;
            if (v >= 190u && v <= 192u) {
                blended++;
                if (blend_row < 0) blend_row = r;
                if (r == blend_row && c == 3) blend_c3 = 1;
                if (r == blend_row && c == 4) blend_c4 = 1;
            }
        }
    }
    if (blended != 2 || !blend_c3 || !blend_c4)
        printf("FAIL: fxaa blended=%d (row %d, c3=%d c4=%d), expected exactly "
               "two 191+-1 pixels at columns 3 and 4 of one row\n",
               blended, blend_row, blend_c3, blend_c4);
    ASSERT_EQ(blended, 2);
    ASSERT_TRUE(blend_c3 && blend_c4);
    ASSERT_TRUE(white >= 2);

    rhi_texture_destroy(g_dev, src);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(lens_effects_sidecar_produces_the_exact_vignette_ramp) {
    /* Hand-derived anchors:
     *   centre-ish (col 3, row 3): uv = (0.4375, 0.4375), centre = -0.0625 both
     *     axes, dist = 0.08839, t = 0.11048, smoothstep = 0.03392,
     *     vignette = 0.96608, 200 * 0.96608 = 193.2 -> 193
     *   corner (col 7, row 7): uv = (0.9375, 0.9375), centre = 0.4375 both
     *     axes, dist = 0.61872, t = 0.77340, smoothstep = 0.86932,
     *     vignette = 0.13068, 200 * 0.13068 = 26.1 -> 26
     * Both agree with the table below, which is how the closed form was
     * checked before the table was written down. */
    static const unsigned char want[8 * 8] = {
         26,  50,  72,  84,  84,  72,  50,  26,
         50,  84, 113, 130, 130, 113,  84,  50,
         72, 113, 149, 169, 169, 149, 113,  72,
         84, 130, 169, 193, 193, 169, 130,  84,
         84, 130, 169, 193, 193, 169, 130,  84,
         72, 113, 149, 169, 169, 149, 113,  72,
         50,  84, 113, 130, 130, 113,  84,  50,
         26,  50,  72,  84,  84,  72,  50,  26
    };
    static const unsigned char grey_tex[4 * 4 * 4] = {
        200,200,200,255, 200,200,200,255, 200,200,200,255, 200,200,200,255,
        200,200,200,255, 200,200,200,255, 200,200,200,255, 200,200,200,255,
        200,200,200,255, 200,200,200,255, 200,200,200,255, 200,200,200,255,
        200,200,200,255, 200,200,200,255, 200,200,200,255, 200,200,200,255
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture src;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc[4];
    static const char *const names[4] = {
        "u_ca_strength", "u_vignette_strength", "u_vignette_softness",
        "u_grain_strength"
    };
    static const i32 expect_off[4] = { 0, 4, 8, 12 };
    int i, pixel;

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "lens_effects_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 4; ++i) {
        loc[i] = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (loc[i] != expect_off[i])
            printf("FAIL: %s resolved to %d, expected %d\n", names[i],
                   (int)loc[i], (int)expect_off[i]);
        ASSERT_EQ(loc[i], expect_off[i]);
    }

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 4u; tdesc.height = 4u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.mip_levels = 1u;
    tdesc.data = grey_tex;
    src = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(src));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_clear_color(cmd, 0.0f, 1.0f, 0.0f, 1.0f);   /* never an answer */
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_texture(cmd, src, sampler, 0u);
    rhi_cmd_set_uniform_f32(cmd, loc[0], 0.0f);   /* CA off  */
    rhi_cmd_set_uniform_f32(cmd, loc[1], 1.0f);   /* vignette strength */
    rhi_cmd_set_uniform_f32(cmd, loc[2], 0.0f);   /* vignette softness */
    rhi_cmd_set_uniform_f32(cmd, loc[3], 0.0f);   /* grain off */
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (pixel = 0; pixel < 64; ++pixel) {
        i = pixel * 4;
        if (px[i + 0] != want[pixel] || px[i + 1] != want[pixel] ||
            px[i + 2] != want[pixel] || px[i + 3] != 255u) {
            printf("FAIL: lens vignette pixel %d = (%u,%u,%u,%u), expected "
                   "(%u,%u,%u,255)\n", pixel, (unsigned)px[i + 0],
                   (unsigned)px[i + 1], (unsigned)px[i + 2],
                   (unsigned)px[i + 3], (unsigned)want[pixel],
                   (unsigned)want[pixel], (unsigned)want[pixel]);
        }
        ASSERT_EQ(px[i + 0], want[pixel]);
        ASSERT_EQ(px[i + 1], want[pixel]);
        ASSERT_EQ(px[i + 2], want[pixel]);
        ASSERT_EQ(px[i + 3], 255u);
    }

    rhi_texture_destroy(g_dev, src);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(color_grade_sidecar_applies_saturation_and_white_balance) {
    static const unsigned char grey_tex[4 * 4 * 4] = {
        200,200,200,255, 200,200,200,255, 200,200,200,255, 200,200,200,255,
        200,200,200,255, 200,200,200,255, 200,200,200,255, 200,200,200,255,
        200,200,200,255, 200,200,200,255, 200,200,200,255, 200,200,200,255,
        200,200,200,255, 200,200,200,255, 200,200,200,255, 200,200,200,255
    };
    static const unsigned char red_tex[4 * 4 * 4] = {
        255,0,0,255, 255,0,0,255, 255,0,0,255, 255,0,0,255,
        255,0,0,255, 255,0,0,255, 255,0,0,255, 255,0,0,255,
        255,0,0,255, 255,0,0,255, 255,0,0,255, 255,0,0,255,
        255,0,0,255, 255,0,0,255, 255,0,0,255, 255,0,0,255
    };
    static const struct { const unsigned char *src; float sat;
                         unsigned char want; const char *what; } cases[2] = {
        { grey_tex, 1.0f, 170u, "grey in, saturation 1" },
        { red_tex,  0.0f,  46u, "red in, saturation 0" }
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHITextureDesc tdesc;
    RHITexture src;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHISampler sampler;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc[5];
    static const char *const names[5] = {
        "u_cg_saturation", "u_cg_contrast", "u_cg_brightness",
        "u_cg_temperature", "u_cg_tint"
    };
    /* Declared offsets, in declaration order, so a reordering of the struct
     * that silently moves one uniform cannot pass. */
    static const i32 expect_off[5] = { 0, 4, 8, 12, 16 };
    int c, pixel, i;

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "color_grade_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.uses_textures = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 5; ++i) {
        loc[i] = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (loc[i] != expect_off[i])
            printf("FAIL: %s resolved to %d, expected %d\n", names[i],
                   (int)loc[i], (int)expect_off[i]);
        ASSERT_EQ(loc[i], expect_off[i]);
    }

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = 4u; tdesc.height = 4u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.mip_levels = 1u;
    tdesc.data = cases[0].src;
    src = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(src));
    sampler = rhi_sampler_create(g_dev, &(RHISamplerDesc){0});

    for (c = 0; c < 2; ++c) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_clear_color(cmd, 0.0f, 1.0f, 0.0f, 1.0f);   /* never an answer */
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_texture(cmd, src, sampler, 0u);
        rhi_cmd_set_uniform_f32(cmd, loc[0], cases[c].sat);
        rhi_cmd_set_uniform_f32(cmd, loc[1], 1.0f);
        rhi_cmd_set_uniform_f32(cmd, loc[2], 1.0f);
        rhi_cmd_set_uniform_f32(cmd, loc[3], 0.0f);
        rhi_cmd_set_uniform_f32(cmd, loc[4], 0.0f);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (pixel = 0; pixel < 64; ++pixel) {
            i = pixel * 4;
            if (px[i + 0] != cases[c].want || px[i + 1] != cases[c].want ||
                px[i + 2] != cases[c].want || px[i + 3] != 255u) {
                printf("FAIL: %s pixel %d = (%u,%u,%u,%u), expected "
                       "(%u,%u,%u,255)\n", cases[c].what, pixel,
                       (unsigned)px[i + 0], (unsigned)px[i + 1],
                       (unsigned)px[i + 2], (unsigned)px[i + 3],
                       (unsigned)cases[c].want, (unsigned)cases[c].want,
                       (unsigned)cases[c].want);
            }
            ASSERT_EQ(px[i + 0], cases[c].want);
            ASSERT_EQ(px[i + 1], cases[c].want);
            ASSERT_EQ(px[i + 2], cases[c].want);
            ASSERT_EQ(px[i + 3], 255u);
        }

        /* Swap the source for the second case: same pipeline, same uniforms
         * except saturation. */
        tdesc.data = cases[c + 1 < 2 ? c + 1 : c].src;
        rhi_texture_destroy(g_dev, src);
        src = rhi_texture_create(g_dev, &tdesc);
        ASSERT_TRUE(rhi_handle_valid(src));
    }

    rhi_texture_destroy(g_dev, src);
    rhi_sampler_destroy(g_dev, sampler);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(texel_buffer_binding_delivers_instance_rows_to_the_shader) {
    static const float verts[3 * 3] = {
        -1.0f, -1.0f, 0.0f,   3.0f, -1.0f, 0.0f,   -1.0f,  3.0f, 0.0f
    };
    static const float rows[2 * 4] = {
        1.0f, 0.0f, 0.0f, 1.0f,        /* row 0 -> red   */
        0.0f, 1.0f, 0.0f, 1.0f         /* row 1 -> green */
    };
    static const unsigned char expect[2][4] = {
        { 255,   0,   0, 255 },
        {   0, 255,   0, 255 }
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bdesc;
    RHIBuffer vbo, inst;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    int frame, pixel, i;

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    vs = rhi_shader_create(g_dev, "texel_buffer_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "texel_buffer_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.vertex_stride = 12u;               /* POSITION only */
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(rows);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = rows;
    inst = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(inst));

    for (frame = 0; frame < 2; ++frame) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_clear_color(cmd, 0.0f, 1.0f, 0.0f, 1.0f);   /* loud: never the answer */
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_texel_buffers(cmd, inst, RHI_HANDLE_NULL);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_draw(cmd, 3u, frame == 0 ? 1u : 2u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        for (pixel = 0; pixel < 64; ++pixel) {
            i = pixel * 4;
            if (px[i + 0] != (unsigned char)expect[frame][0] ||
                px[i + 1] != (unsigned char)expect[frame][1] ||
                px[i + 2] != (unsigned char)expect[frame][2] ||
                px[i + 3] != (unsigned char)expect[frame][3]) {
                printf("FAIL: frame %d (InstanceCount %u) pixel %d = "
                       "(%u,%u,%u,%u), expected (%u,%u,%u,%u)\n", frame,
                       frame == 0 ? 1u : 2u, pixel,
                       (unsigned)px[i + 0], (unsigned)px[i + 1],
                       (unsigned)px[i + 2], (unsigned)px[i + 3],
                       (unsigned)expect[frame][0], (unsigned)expect[frame][1],
                       (unsigned)expect[frame][2], (unsigned)expect[frame][3]);
            }
            ASSERT_EQ(px[i + 0], (unsigned char)expect[frame][0]);
            ASSERT_EQ(px[i + 1], (unsigned char)expect[frame][1]);
            ASSERT_EQ(px[i + 2], (unsigned char)expect[frame][2]);
            ASSERT_EQ(px[i + 3], (unsigned char)expect[frame][3]);
        }
    }

    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, inst);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

TEST(depth_only_sidecar_converts_clip_z_to_window_depth) {
    static const float flat[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,   /* e[2][2] = 0 -> clip.z = 0 */
        0.0f, 0.0f, 0.0f, 1.0f    /* e[2][3] = 0 -> clip.w stays 1 */
    };
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    static const float quad[6 * 3] = {
        -1.0f, -1.0f, 0.0f,   1.0f, -1.0f, 0.0f,   1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,   1.0f,  1.0f, 0.0f,  -1.0f,  1.0f, 0.0f
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShadowMap sm;
    RHIShader depth_vs, sample_vs, sample_fs;
    RHIPipeline depth_pipe, sample_pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc_model, loc_lvp, loc_compare;
    int i;

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    sm = rhi_shadow_map_create(g_dev, 8u, 8u);
    ASSERT_TRUE(rhi_handle_valid(sm.fbo));

    /* The real depth_only sidecar, not the test-only shadow_depth_hlsl --
     * this is the shader main.c now binds for the cascades. */
    depth_vs = rhi_shader_create(g_dev, "depth_only_hlsl.vert", 0, false);
    sample_vs = rhi_shader_create(g_dev, "shadow_sample_hlsl.vert", 0, false);
    sample_fs = rhi_shader_create(g_dev, "shadow_sample_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(depth_vs));
    ASSERT_TRUE(rhi_handle_valid(sample_vs));
    ASSERT_TRUE(rhi_handle_valid(sample_fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = depth_vs;
    pd.frag = RHI_HANDLE_NULL;
    pd.vertex_stride = 12u;
    pd.is_shadow_depth = true;
    pd.disable_culling = true;
    depth_pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(depth_pipe));

    /* main.c resolves exactly these two names on the cascade pipeline, so the
     * offsets are part of the contract the sidecar has to keep. */
    loc_model = rhi_pipeline_get_uniform_location(g_dev, depth_pipe, "u_model");
    loc_lvp   = rhi_pipeline_get_uniform_location(g_dev, depth_pipe, "u_light_vp");
    ASSERT_EQ(loc_model, 0);
    ASSERT_EQ(loc_lvp, 64);

    memset(&pd, 0, sizeof(pd));
    pd.vert = sample_vs; pd.frag = sample_fs;
    pd.no_vertex_input = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.depth_write_disable = true;
    sample_pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(sample_pipe));
    loc_compare = rhi_pipeline_get_uniform_location(g_dev, sample_pipe,
                                                    "u_compare");
    ASSERT_EQ(loc_compare, 64);

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(quad);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = quad;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_cmd_bind_shadow_map(cmd, &sm);
    rhi_cmd_bind_pipeline(cmd, depth_pipe);
    rhi_cmd_set_uniform_mat4(cmd, loc_model, identity);
    rhi_cmd_set_uniform_mat4(cmd, loc_lvp, flat);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    rhi_cmd_unbind_shadow_map(cmd, 64u, 64u);

    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, sample_pipe);
    rhi_cmd_set_uniform_mat4(cmd,
        rhi_pipeline_get_uniform_location(g_dev, sample_pipe, "u_transform"),
        identity);
    rhi_cmd_set_uniform_vec4(cmd, loc_compare, 0.0f, 0.0f, 0.25f, 0.0f);
    rhi_cmd_bind_shadow_texture(cmd, sm.depth_tex, (RHISampler){0});
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);

    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < 8 * 8; ++i) {
        if (px[i * 4] != 255u)
            printf("FAIL: pixel %d = %u, expected 255 (lit); 0 would mean the "
                   "sidecar stored window depth 0.0 and skipped the "
                   "GL->[0,1] clip.z conversion\n", i, (unsigned)px[i * 4]);
        ASSERT_EQ(px[i * 4], 255u);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, depth_pipe);
    rhi_pipeline_destroy(g_dev, sample_pipe);
    rhi_shader_destroy(g_dev, depth_vs);
    rhi_shader_destroy(g_dev, sample_vs);
    rhi_shader_destroy(g_dev, sample_fs);
    rhi_shadow_map_destroy(g_dev, &sm);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
}

TEST(shadow_atlas_depth_round_trips_through_the_sampling_path) {
    /* Centre half of NDC: on an 8x8 atlas that is the centre 4x4. */
    static const float half[16] = {
        0.5f, 0,   0,   0,
        0,   0.5f, 0,   0,
        0,   0,   1.0f, 0,
        0,   0,   0,   1.0f
    };
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    static const float quad[6 * 3] = {
        -1.0f, -1.0f, 0.25f,   1.0f, -1.0f, 0.25f,   1.0f,  1.0f, 0.25f,
        -1.0f, -1.0f, 0.25f,   1.0f,  1.0f, 0.25f,  -1.0f,  1.0f, 0.25f
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShadowMap sm;
    RHIShader depth_vs, sample_vs, sample_fs;
    RHIPipeline depth_pipe, sample_pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc_compare;
    int x, y;

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    sm = rhi_shadow_map_create(g_dev, 8u, 8u);
    ASSERT_TRUE(rhi_handle_valid(sm.fbo));

    depth_vs = rhi_shader_create(g_dev, "shadow_depth_hlsl.vert", 0, false);
    sample_vs = rhi_shader_create(g_dev, "shadow_sample_hlsl.vert", 0, false);
    sample_fs = rhi_shader_create(g_dev, "shadow_sample_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(depth_vs));
    ASSERT_TRUE(rhi_handle_valid(sample_vs));
    ASSERT_TRUE(rhi_handle_valid(sample_fs));

    /* Depth-only pipeline: no fragment stage, no render targets. */
    memset(&pd, 0, sizeof(pd));
    pd.vert = depth_vs;
    pd.frag = RHI_HANDLE_NULL;
    pd.vertex_stride = 12u;              /* POSITION only */
    pd.is_shadow_depth = true;
    pd.disable_culling = true;
    depth_pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(depth_pipe));

    memset(&pd, 0, sizeof(pd));
    pd.vert = sample_vs; pd.frag = sample_fs;
    pd.no_vertex_input = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.depth_write_disable = true;
    sample_pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(sample_pipe));
    loc_compare = rhi_pipeline_get_uniform_location(g_dev, sample_pipe,
                                                    "u_compare");
    ASSERT_EQ(loc_compare, 64);

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(quad);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = quad;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);

    /* Pass 1: bind clears the atlas to 1.0, then the depth pass writes 0.25
     * over the centre 4x4. */
    rhi_cmd_bind_shadow_map(cmd, &sm);
    rhi_cmd_bind_pipeline(cmd, depth_pipe);
    rhi_cmd_set_uniform_mat4(cmd,
        rhi_pipeline_get_uniform_location(g_dev, depth_pipe, "u_transform"),
        half);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    rhi_cmd_unbind_shadow_map(cmd, 64u, 64u);

    /* Pass 2: the lighting pass reads the atlas back through unit 1 at a
     * receiver depth of 0.5. */
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, sample_pipe);
    rhi_cmd_set_uniform_mat4(cmd,
        rhi_pipeline_get_uniform_location(g_dev, sample_pipe, "u_transform"),
        identity);
    rhi_cmd_set_uniform_vec4(cmd, loc_compare, 0.0f, 0.0f, 0.5f, 0.0f);
    rhi_cmd_bind_shadow_texture(cmd, sm.depth_tex, (RHISampler){0});
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);

    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            int centre = (x >= 2 && x < 6 && y >= 2 && y < 6);
            const unsigned char want = centre ? 0u : 255u;
            int i = (y * 8 + x) * 4;
            ASSERT_EQ(px[i + 0], want);
            ASSERT_EQ(px[i + 1], want);
            ASSERT_EQ(px[i + 2], want);
        }
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, depth_pipe);
    rhi_pipeline_destroy(g_dev, sample_pipe);
    rhi_shader_destroy(g_dev, depth_vs);
    rhi_shader_destroy(g_dev, sample_vs);
    rhi_shader_destroy(g_dev, sample_fs);
    rhi_shadow_map_destroy(g_dev, &sm);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
}

/* R618's clear and the unbind's target restore, as two separate observable
 * facts.
 *
 * (a) Every bind starts the atlas fresh: the second frame draws nothing into
 *     the atlas at all, so a reader must see all-white again. A bind that
 *     skipped its clear would leave the previous frame's 0.25 square behind
 *     and go black in the centre.
 * (b) The unbind has to leave the SCREEN target bound, not the atlas — the
 *     R230 rule. If it did not, the sampling draw that follows would rasterise
 *     into the depth-only atlas and the readback would come back as the
 *     previous frame's contents (or nothing at all) instead of this frame's
 *     compare result. */
TEST(shadow_bind_clears_each_frame_and_unbind_restores_the_screen) {
    static const float half[16] = {
        0.5f, 0,   0,   0,
        0,   0.5f, 0,   0,
        0,   0,   1.0f, 0,
        0,   0,   0,   1.0f
    };
    static const float identity[16] = {
        1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1
    };
    static const float quad[6 * 3] = {
        -1.0f, -1.0f, 0.25f,   1.0f, -1.0f, 0.25f,   1.0f,  1.0f, 0.25f,
        -1.0f, -1.0f, 0.25f,   1.0f,  1.0f, 0.25f,  -1.0f,  1.0f, 0.25f
    };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShadowMap sm;
    RHIShader depth_vs, sample_vs, sample_fs;
    RHIPipeline depth_pipe, sample_pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc_compare, loc_depth_tf, loc_sample_tf;
    int frame, x, y;

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));
    sm = rhi_shadow_map_create(g_dev, 8u, 8u);
    ASSERT_TRUE(rhi_handle_valid(sm.fbo));

    depth_vs = rhi_shader_create(g_dev, "shadow_depth_hlsl.vert", 0, false);
    sample_vs = rhi_shader_create(g_dev, "shadow_sample_hlsl.vert", 0, false);
    sample_fs = rhi_shader_create(g_dev, "shadow_sample_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(depth_vs));
    ASSERT_TRUE(rhi_handle_valid(sample_vs));
    ASSERT_TRUE(rhi_handle_valid(sample_fs));

    memset(&pd, 0, sizeof(pd));
    pd.vert = depth_vs; pd.frag = RHI_HANDLE_NULL;
    pd.vertex_stride = 12u;
    pd.is_shadow_depth = true;
    pd.disable_culling = true;
    depth_pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(depth_pipe));

    memset(&pd, 0, sizeof(pd));
    pd.vert = sample_vs; pd.frag = sample_fs;
    pd.no_vertex_input = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.depth_write_disable = true;
    sample_pipe = rhi_pipeline_create(g_dev, &pd);
    ASSERT_TRUE(rhi_handle_valid(sample_pipe));

    loc_depth_tf = rhi_pipeline_get_uniform_location(g_dev, depth_pipe,
                                                    "u_transform");
    loc_sample_tf = rhi_pipeline_get_uniform_location(g_dev, sample_pipe,
                                                      "u_transform");
    loc_compare = rhi_pipeline_get_uniform_location(g_dev, sample_pipe,
                                                    "u_compare");
    ASSERT_EQ(loc_depth_tf, 0);
    ASSERT_EQ(loc_sample_tf, 0);
    ASSERT_EQ(loc_compare, 64);

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(quad);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = quad;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    for (frame = 0; frame < 2; ++frame) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_cmd_bind_shadow_map(cmd, &sm);
        /* Frame 0 fills the centre square; frame 1 draws nothing, so only the
         * bind's clear can make frame 1 read as fully lit. */
        if (frame == 0) {
            rhi_cmd_bind_pipeline(cmd, depth_pipe);
            rhi_cmd_set_uniform_mat4(cmd, loc_depth_tf, half);
            rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
            rhi_cmd_draw(cmd, 6u, 1u);
        }
        rhi_cmd_unbind_shadow_map(cmd, 64u, 64u);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, sample_pipe);
        rhi_cmd_set_uniform_mat4(cmd, loc_sample_tf, identity);
        rhi_cmd_set_uniform_vec4(cmd, loc_compare, 0.0f, 0.0f, 0.5f, 0.0f);
        rhi_cmd_bind_shadow_texture(cmd, sm.depth_tex, (RHISampler){0});
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px,
                                            sizeof(px)));
        for (y = 0; y < 8; ++y) {
            for (x = 0; x < 8; ++x) {
                int centre = (x >= 2 && x < 6 && y >= 2 && y < 6);
                /* Frame 0 drew the square; frame 1 drew nothing and must be
                 * clean everywhere because the bind cleared the atlas. */
                const unsigned char want = (frame == 0 && centre) ? 0u : 255u;
                int i = (y * 8 + x) * 4;
                ASSERT_EQ(px[i + 0], want);
                ASSERT_EQ(px[i + 1], want);
                ASSERT_EQ(px[i + 2], want);
            }
        }
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    }

    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, depth_pipe);
    rhi_pipeline_destroy(g_dev, sample_pipe);
    rhi_shader_destroy(g_dev, depth_vs);
    rhi_shader_destroy(g_dev, sample_vs);
    rhi_shader_destroy(g_dev, sample_fs);
    rhi_shadow_map_destroy(g_dev, &sm);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
}

/* ---- environment sidecars: skybox, water, terrain ----
 *
 * These three follow blinn_phong into the sidecar path API, so each test
 * drives the SHAPE OF PIPELINE the demo actually builds (forward_mrt = true
 * in main.c) and asserts an exact RGBA byte, never "not black". The rig that
 * makes an exact byte possible is the same trick in all three:
 *
 *  - a projection that swaps world (x, z) into NDC (x, y) while leaving depth
 *    alone, so a single oversized triangle covers the whole target and the
 *    geometry is fully controlled by the vertex buffer;
 *  - uniforms chosen so every position-dependent term is either constant over
 *    the covered area or pinned to a branch whose value is known by
 *    construction.
 *
 * RT1 is read back on every draw as RAW 16-bit patterns. Both environment
 * sidecars document a zero motion vector (neither terrain_render nor
 * water_render ever binds a temporal UBO, so a b1 CBV would be an unbound
 * descriptor table), which is also what the attachment is cleared to -- so
 * "+0.0 exactly" is the assertion, not "approximately zero".
 */

/* Column-major (index = col*4 + row), matching HLSL's float4x4 packing.
 * m00 = m12 = 1/1.5 maps world x -> NDC x and world z -> NDC y; the m22 = 0
 * entry puts the whole plane at depth 0, which the depth-disabled test
 * pipeline never looks at. */
static const float WARP_XZ_TO_NDC[16] = {
    0.66666667f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.66666667f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
static const float WARP_IDENTITY[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

/* Prints the byte actually read next to the one expected; ASSERT_EQ reports
 * only the expressions, which is useless for an 8-bit value.
 *
 * `tol` is a per-channel LSB tolerance, and it is 1 for every colour
 * assertion below. That is not slack for its own sake: each of these
 * expected triples was chosen so the pipeline collapses to one colour, and
 * every one of them lands at least one channel within 0.08 of a byte
 * rounding boundary -- terrain 18.52 and 60.57, water 16.575, skybox
 * 52.44. WARP and the RTX 4060 therefore disagree by one LSB on terrain's
 * shadowed blue (19 vs 18) while agreeing everywhere else, and that is fp32
 * `sin`/`exp` argument reduction, not a defect. Pinning one adapter's
 * transcendental result as the contract would make this suite fail on
 * hardware; a +-1 per-channel bound still catches any mutation worth
 * catching -- flipping terrain's shadow factor 0.4 -> 0.5 moves red by 4 and
 * green by 9. The velocity assertions below stay exact: 0.0 is a literal,
 * so it has no boundary to fall across. */
static int warp_expect_rgba(const unsigned char *px, int count,
                            int r, int g, int b, int a, int tol,
                            const char *what)
{
    int i, ch;
    const int want[4] = { r, g, b, a };
    for (i = 0; i < count * 4; i += 4) {
        int bad = 0;
        for (ch = 0; ch < 4; ++ch) {
            int d = (int)px[i + ch] - want[ch];
            if (d < 0) d = -d;
            if (d > tol) bad = 1;
        }
        if (!bad) continue;
        printf("FAIL: %s pixel %d = (%u,%u,%u,%u), expected (%d,%d,%d,%d) +-%d\n",
               what, i / 4, px[i], px[i+1], px[i+2], px[i+3],
               r, g, b, a, tol);
        return 0;
    }
    return 1;
}

static int warp_expect_vel_zero(const unsigned short *rt1, const char *what)
{
    int i;
    for (i = 0; i < 64 * 2; ++i) {
        if (rt1[i] == 0u) continue;
        printf("FAIL: %s RT1 halfword %d = 0x%04x, expected 0x0000\n",
               what, i, (unsigned)rt1[i]);
        return 0;
    }
    return 1;
}

/* R608: the skybox sidecar pair. "The sky is blue" proves nothing, so the
 * uniforms are chosen to make the closed-form half of skybox.frag -- ray.y
 * below 0.01, so the 24-step cloud march is skipped and no fbm/hash is in the
 * pixel -- evaluate to one constant colour:
 *
 *   u_view     = identity
 *   u_inv_proj = the matrix with m03 = +1 and m13 = -1, so
 *                ray_eye.xy = (1, -1) at EVERY vertex and the whole screen
 *                shades one ray: normalize(1,-1,-1) = (0.5774,-0.5774,-0.5774)
 *   u_sun_dir  = (0,0,-1)   -> cos_sun = 0.57735, no sun disc, no halo
 *                                (smoothstep(0.9995,...) = 0); the horizon
 *                                term stays live at (1-|ray.y|)^3 = 0.0755
 *   u_sun_color= (20,10,5)  -> a linear HDR triple, not a clamped white
 *
 *   density    = exp(-zenith*6371/8400) + exp(-zenith*6371/1250) = 0.190499
 *   scattering = (RAYLEIGH_COEFF * phase_rayleigh * density) * 30000
 *                + mie_scat * 1000
 *   extinction = exp(-(RAYLEIGH_COEFF + 0.1*MIE_COEFF) * density*0.5 * 6371 * 0.01)
 *   sky        = u_sun_color * (scattering + 0.1 * horizon_fog) * extinction
 *
 * giving (0.20565, 0.13692, 0.08983) = bytes (52, 35, 23). The three
 * channels are the RAYLEIGH_COEFF ratio 5.5 : 13 : 22.4, so an error in the
 * per-channel coefficient, the phase function, or u_sun_color's byte offset
 * turns this red instead of merely darkening it. */
TEST(skybox_sidecar_scatters_an_exact_constant_sky) {
    /* m03 = 1 (column 3, row 0) and m13 = -1 (column 3, row 1): column 3 is
     * the last group of four floats, and its first two entries are rows 0/1. */
    static const float inv_proj[16] = {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f
    };
    const RHIFormat formats[2] = {RHI_FORMAT_R8G8B8A8_UNORM, RHI_FORMAT_R16G16_SFLOAT};
    static const char *const names[4] = {"u_inv_proj", "u_view", "u_sun_dir", "u_sun_color"};
    static const i32 expected[4] = {0, 64, 128, 144};
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHIShader vs, fs, vs1, fs1;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    i32 loc[4];
    RHICmdBuffer *cmd;
    unsigned char rt0[8 * 8 * 4];
    unsigned short rt1[8 * 8 * 2];
    int i;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    /* The GLSL paths the engine itself passes, plus the _mrt fragment name it
     * passes on D3D12 -- the backend appends _hlsl to whatever it is given. */
    vs = rhi_shader_create_path(g_dev, "shaders/skybox.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/skybox_mrt.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    vs1 = rhi_shader_create_path(g_dev, "shaders/skybox.vert", false);
    fs1 = rhi_shader_create_path(g_dev, "shaders/skybox.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs1));
    ASSERT_TRUE(rhi_handle_valid(fs1));
    rhi_shader_destroy(g_dev, vs1);
    rhi_shader_destroy(g_dev, fs1);

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.no_vertex_input = true;   /* SV_VertexID only: zero input elements */
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_attachment_count = 2u;
    pdesc.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 4; ++i) {
        loc[i] = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (loc[i] != expected[i])
            printf("FAIL: skybox %s resolved to %d, expected %d\n",
                   names[i], (int)loc[i], (int)expected[i]);
        ASSERT_EQ(loc[i], expected[i]);
    }

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_mrt_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_set_uniform_mat4(cmd, loc[0], inv_proj);
    rhi_cmd_set_uniform_mat4(cmd, loc[1], WARP_IDENTITY);
    rhi_cmd_set_uniform_vec3(cmd, loc[2], 0.0f, 0.0f, -1.0f);  /* u_sun_dir */
    rhi_cmd_set_uniform_vec3(cmd, loc[3], 20.0f, 10.0f, 5.0f);  /* u_sun_color */
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_mrt_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    memset(rt0, 0, sizeof(rt0));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], rt0, sizeof(rt0)));
    ASSERT_TRUE(warp_expect_rgba(rt0, 64, 52, 35, 23, 255, 1, "skybox RT0"));

    memset(rt1, 0, sizeof(rt1));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], rt1, sizeof(rt1)));
    ASSERT_TRUE(warp_expect_vel_zero(rt1, "skybox"));

    rhi_mrt_fbo_destroy(g_dev, &fbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* R608: the water sidecar pair. The GLSL modulates the colour by
 * dist / wave / fresnel, all of which vary across a lit water quad, so the
 * test plane is placed OUT of the 10..50 fade ramp instead:
 *
 *   fade = 1 - smoothstep(10, 50, dist) = 0   (camera.xz is (60,60), the
 *                                             quad is at the origin)
 *   -> wave *= 0, specular *= 0, and mix(deep, surface, fresnel*fade)
 *      collapses to deep = u_water_color * 0.5 exactly, with alpha = 0.
 *
 * Draw A: camera above the plane -> colour = u_water_color * 0.5.
 * Draw B: camera BELOW u_water_y -> depth_darken = 1 - 0.4*0.15 = 0.94,
 *         so colour = u_water_color * 0.47. Two different exact triples from
 *         one pipeline, and they can only both hold if u_camera_pos, u_water_y
 *         and u_water_color each land on their own byte offset. */
TEST(water_sidecar_deep_colour_and_underwater_darkening_are_exact) {
    static const float verts[3 * 3] = {
        -1.5f, 0.0f, -1.5f,
         4.5f, 0.0f, -1.5f,
        -1.5f, 0.0f,  4.5f
    };
    const RHIFormat formats[2] = {RHI_FORMAT_R8G8B8A8_UNORM, RHI_FORMAT_R16G16_SFLOAT};
    /* u_view, u_proj, u_light_vp, u_camera_pos, u_time, u_water_color,
     * u_shadow_bias, u_water_y, and the deliberately absent u_model. */
    static const char *const names[9] = {
        "u_view", "u_proj", "u_light_vp", "u_camera_pos", "u_time",
        "u_water_color", "u_shadow_bias", "u_water_y", "u_model"
    };
    static const i32 expected[9] = {0, 64, 128, 192, 204, 208, 220, 224, -1};
    static const unsigned char white_tex[4 * 4 * 4] = {
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255
    };
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHITextureDesc tex_desc;
    RHITexture shadow_tex;
    RHIShader vs, fs, vs1, fs1;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    i32 loc[9];
    RHICmdBuffer *cmd;
    unsigned char rt0[8 * 8 * 4];
    unsigned short rt1[8 * 8 * 2];
    int draw, i;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    memset(&tex_desc, 0, sizeof(tex_desc));
    tex_desc.width = 4u; tex_desc.height = 4u;
    tex_desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tex_desc.mip_levels = 1u;
    tex_desc.data = white_tex;
    shadow_tex = rhi_texture_create(g_dev, &tex_desc);
    ASSERT_TRUE(rhi_handle_valid(shadow_tex));

    vs = rhi_shader_create_path(g_dev, "shaders/water.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/water_mrt.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    vs1 = rhi_shader_create_path(g_dev, "shaders/water.vert", false);
    fs1 = rhi_shader_create_path(g_dev, "shaders/water.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs1));
    ASSERT_TRUE(rhi_handle_valid(fs1));
    rhi_shader_destroy(g_dev, vs1);
    rhi_shader_destroy(g_dev, fs1);

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 12u;   /* packed vec3: rhi_d3d12_input_layout's stride==12 arm */
    pdesc.uses_textures = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_attachment_count = 2u;
    pdesc.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 9; ++i) {
        loc[i] = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (loc[i] != expected[i])
            printf("FAIL: water %s resolved to %d, expected %d\n",
                   names[i], (int)loc[i], (int)expected[i]);
        ASSERT_EQ(loc[i], expected[i]);
    }

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    for (draw = 0; draw < 2; ++draw) {
        const float cam_y = (draw == 0) ? 1.0f : -0.4f;
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_mrt_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_set_uniform_mat4(cmd, loc[0], WARP_IDENTITY);      /* u_view */
        rhi_cmd_set_uniform_mat4(cmd, loc[1], WARP_XZ_TO_NDC);     /* u_proj */
        rhi_cmd_set_uniform_mat4(cmd, loc[2], WARP_IDENTITY);      /* u_light_vp */
        rhi_cmd_set_uniform_vec3(cmd, loc[3], 60.0f, cam_y, 60.0f);/* u_camera_pos */
        rhi_cmd_set_uniform_f32(cmd, loc[4], 0.0f);               /* u_time */
        rhi_cmd_set_uniform_vec3(cmd, loc[5], 0.13f, 0.94f, 0.90f);/* u_water_color */
        rhi_cmd_set_uniform_f32(cmd, loc[6], 1.0f);                /* u_shadow_bias */
        rhi_cmd_set_uniform_f32(cmd, loc[7], 0.0f);                /* u_water_y */
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_bind_texture(cmd, shadow_tex, (RHISampler){0}, 1u);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_mrt_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(rt0, 0, sizeof(rt0));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], rt0, sizeof(rt0)));
        /* deep = u_water_color * 0.5  ->  x255 = wc * 127.5
         * submerged adds depth_darken 0.94 -> x255 = wc * 119.85 */
        ASSERT_TRUE(warp_expect_rgba(rt0, 64,
                                     draw == 0 ? 17 : 16,
                                     draw == 0 ? 120 : 113,
                                     draw == 0 ? 115 : 108,
                                     0, 1,
                                     draw == 0 ? "water RT0 above" : "water RT0 below"));

        memset(rt1, 0, sizeof(rt1));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], rt1, sizeof(rt1)));
        ASSERT_TRUE(warp_expect_vel_zero(rt1, "water"));
    }

    rhi_mrt_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, shadow_tex);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* R608: the terrain sidecar pair. terrain.frag hard-codes u_light_dir /
 * u_light_color / u_ambient as GLSL consts, so the only shading knobs the
 * test has are the geometry and the push block. The geometry is chosen so
 * exactly one surface colour survives:
 *
 *   normal (0,1,0) -> slope 0 -> grass_w 1, rock_w 0, sand_w 0 (height 2 is
 *                     above the smoothstep(1.5, 0, h) cut), snow_w 0 (below
 *                     3.5), total 1
 *   uv (0.125, 0.25) -> pattern = sin(10)*sin(20)*0.03 = -0.01490, so
 *                     grass_color = (0.20510, 0.42020, 0.10510)
 *   u_water_y = -100 -> foam 0 and no caustics; fog_dist < 40 -> fog 0
 *   diff = dot((0,1,0), -u_light_dir) = 0.808122, spec 0 (rock_w = 0)
 *
 *   lit      = albedo * (ambient + light_color * 0.808122)
 *              -> (60.57, 119.76, 30.21) -> bytes (61,120,30)
 *   shadowed = albedo * (ambient + light_color * 0.808122*0.4)
 *              -> (35.21, 70.41, 18.52) -> bytes (35,70,19)
 *
 * Those are the bytes WARP produces. The hardware adapter produces 18 for
 * the shadowed blue: 18.52 is 0.02 above the rounding boundary and
 * sin(10)*sin(20) is the one transcendental in the chain, so this is fp32
 * argument reduction and not a defect. Hence the +-1 tolerance in
 * warp_expect_rgba, which is also why the lit red (60.57) is not treated as
 * special -- it is 0.07 from its boundary and just happens to agree.
 *
 * The shadowed triple comes from the SAME uniforms with a black 4x4 shadow
 * atlas instead of a white one, which is the only thing that changes: the
 * sidecar's terrain_shadow() returns 1.0 or 0.4 off .r and the sampled texel.
 * That makes it a real test of register t1 rather than of arithmetic alone. */
TEST(terrain_sidecar_lights_grass_and_reads_the_shadow_atlas) {
    static const float verts[3 * 8] = {
        /*  pos                     normal        uv  */
        -1.5f, 2.0f, -1.5f,        0.0f, 1.0f, 0.0f,   0.125f, 0.25f,
         4.5f, 2.0f, -1.5f,        0.0f, 1.0f, 0.0f,   0.125f, 0.25f,
        -1.5f, 2.0f,  4.5f,        0.0f, 1.0f, 0.0f,   0.125f, 0.25f
    };
    /* 0.25 on the xyz rows so the whole quad lands inside the atlas quadrant
     * and ndc.z stays in [-0.375, 0.375]: window depth 0.5 never passes the
     * 0.4-shadow comparison against a white texel and always passes against a
     * black one, on every pixel. */
    static const float light_vp[16] = {
        0.25f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.25f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.25f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    static const unsigned char white_tex[4 * 4 * 4] = {
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255,
        255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255
    };
    static const unsigned char black_tex[4 * 4 * 4] = {
        0,0,0,255, 0,0,0,255, 0,0,0,255, 0,0,0,255,
        0,0,0,255, 0,0,0,255, 0,0,0,255, 0,0,0,255,
        0,0,0,255, 0,0,0,255, 0,0,0,255, 0,0,0,255,
        0,0,0,255, 0,0,0,255, 0,0,0,255, 0,0,0,255
    };
    const RHIFormat formats[2] = {RHI_FORMAT_R8G8B8A8_UNORM, RHI_FORMAT_R16G16_SFLOAT};
    /* The sidecar keeps no u_model (identity), no u_albedo (the GL twin never
     * samples it) and no u_light_* (GL consts). Pinning -1 for those is the
     * point: a stale offset there is how a silently-zeroed uniform returns. */
    static const char *const names[12] = {
        "u_view", "u_proj", "u_light_vp", "u_camera_pos", "u_time",
        "u_water_y", "u_shadow_bias", "u_fog_strength", "u_model",
        "u_albedo", "u_light_dir", "u_ambient"
    };
    static const i32 expected[12] = {
        0, 64, 128, 192, 204, 208, 212, 216, -1, -1, -1, -1
    };
    RHIMRTFBO fbo = rhi_mrt_fbo_create(g_dev, 8u, 8u, formats, 2u);
    RHITextureDesc tex_desc;
    RHITexture albedo_tex, shadow_tex;
    RHIShader vs, fs, vs1, fs1;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    i32 loc[12];
    RHICmdBuffer *cmd;
    unsigned char rt0[8 * 8 * 4];
    unsigned short rt1[8 * 8 * 2];
    int draw, i;

    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    memset(&tex_desc, 0, sizeof(tex_desc));
    tex_desc.width = 4u; tex_desc.height = 4u;
    tex_desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tex_desc.mip_levels = 1u;
    tex_desc.data = white_tex;
    albedo_tex = rhi_texture_create(g_dev, &tex_desc);
    ASSERT_TRUE(rhi_handle_valid(albedo_tex));
    shadow_tex = albedo_tex;

    vs = rhi_shader_create_path(g_dev, "shaders/terrain.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/terrain_mrt.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    vs1 = rhi_shader_create_path(g_dev, "shaders/terrain.vert", false);
    fs1 = rhi_shader_create_path(g_dev, "shaders/terrain.frag", true);
    ASSERT_TRUE(rhi_handle_valid(vs1));
    ASSERT_TRUE(rhi_handle_valid(fs1));
    rhi_shader_destroy(g_dev, vs1);
    rhi_shader_destroy(g_dev, fs1);

    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 32u;   /* pos3 + normal3 + uv2 */
    pdesc.uses_textures = true;
    pdesc.terrain_layout = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_attachment_count = 2u;
    pdesc.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
    pdesc.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    pdesc.disable_culling = true;
    pdesc.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    for (i = 0; i < 12; ++i) {
        loc[i] = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        if (loc[i] != expected[i])
            printf("FAIL: terrain %s resolved to %d, expected %d\n",
                   names[i], (int)loc[i], (int)expected[i]);
        ASSERT_EQ(loc[i], expected[i]);
    }

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

    for (draw = 1; draw < 3; ++draw) {
        if (draw == 2) {
            /* Black atlas: terrain_shadow() now takes the 0.4 branch. */
            tex_desc.data = black_tex;
            shadow_tex = rhi_texture_create(g_dev, &tex_desc);
            ASSERT_TRUE(rhi_handle_valid(shadow_tex));
        }
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_mrt_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_set_uniform_mat4(cmd, loc[0], WARP_IDENTITY);        /* u_view */
        rhi_cmd_set_uniform_mat4(cmd, loc[1], WARP_XZ_TO_NDC);       /* u_proj */
        rhi_cmd_set_uniform_mat4(cmd, loc[2], light_vp);             /* u_light_vp */
        rhi_cmd_set_uniform_vec3(cmd, loc[3], 0.0f, 2.0f, 12.0f);    /* u_camera_pos */
        rhi_cmd_set_uniform_f32(cmd, loc[4], 0.0f);                  /* u_time */
        rhi_cmd_set_uniform_f32(cmd, loc[5], -100.0f);               /* u_water_y */
        rhi_cmd_set_uniform_f32(cmd, loc[6], 0.0f);                  /* u_shadow_bias */
        rhi_cmd_set_uniform_f32(cmd, loc[7], 0.0f);                  /* u_fog_strength */
        /* The REAL binder terrain_render calls: albedo on unit 0 (which this
         * sidecar does not declare, so the call is skipped), shadow atlas on
         * unit 1 -> register t1. */
        rhi_cmd_bind_material_textures(cmd, albedo_tex, albedo_tex, albedo_tex,
                                       albedo_tex, shadow_tex, albedo_tex,
                                       (RHISampler){0});
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_mrt_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        memset(rt0, 0, sizeof(rt0));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[0], rt0, sizeof(rt0)));
        ASSERT_TRUE(warp_expect_rgba(rt0, 64,
                                     draw == 1 ? 61 : 35,
                                     draw == 1 ? 120 : 70,
                                     draw == 1 ? 30 : 19,
                                     255, 1,
                                     draw == 1 ? "terrain RT0 lit" : "terrain RT0 shadowed"));

        memset(rt1, 0, sizeof(rt1));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex[1], rt1, sizeof(rt1)));
        ASSERT_TRUE(warp_expect_vel_zero(rt1, "terrain"));
    }
    if (draw == 2) rhi_texture_destroy(g_dev, shadow_tex);

    rhi_mrt_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, albedo_tex);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* R637: the storage binder end to end. One dispatch writes a raw UAV (u0)
 * and a structured UAV (u1), seeded by a root constant; both buffers are
 * read back and checked word for word. Before R637 this binder was a stub,
 * on the belief that any UAV view removed the device on this host -- which
 * was the probes' own incomplete descriptor. A UPLOAD-heap STORAGE buffer
 * (no initial_data) has no UAV access and must be refused, not bound. */
TEST(storage_buffers_receive_raw_and_structured_compute_writes) {
    enum { RAW_WORDS = 64, ROWS = 16 };
    static u32 raw_init[RAW_WORDS];
    static u32 rows_init[ROWS * 4];
    u32 raw_out[RAW_WORDS];
    u32 rows_out[ROWS * 4];
    const u32 seed = 1000u;
    RHIBufferDesc bd;
    RHIBuffer raw, rows, upload_only;
    RHIShader cs;
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    RHICmdBuffer *cmd;
    i32 loc;
    int i;
    memset(raw_init, 0xAB, sizeof(raw_init));
    memset(rows_init, 0xCD, sizeof(rows_init));
    memset(&bd, 0, sizeof(bd));
    bd.usage = RHI_BUFFER_USAGE_STORAGE;
    bd.size = sizeof(raw_init);
    bd.initial_data = raw_init;
    raw = rhi_buffer_create(g_dev, &bd);
    bd.size = sizeof(rows_init);
    bd.initial_data = rows_init;
    rows = rhi_buffer_create(g_dev, &bd);
    bd.initial_data = NULL;
    upload_only = rhi_buffer_create(g_dev, &bd);
    ASSERT_TRUE(rhi_handle_valid(raw));
    ASSERT_TRUE(rhi_handle_valid(rows));
    ASSERT_TRUE(rhi_handle_valid(upload_only));

    cs = rhi_shader_create_compute_path(g_dev, "shaders/probe_storage.comp");
    ASSERT_TRUE(rhi_handle_valid(cs));
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.is_compute = true;
    pdesc.frag = cs;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));
    loc = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_seed");
    ASSERT_EQ(loc, 0);

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, (u32)loc, &seed, sizeof(seed));
    /* Refused first: if it were bound, the real bind below would still
     * overwrite it, so this only proves the refusal does not kill the
     * device or the list. */
    rhi_cmd_bind_storage_buffer(cmd, upload_only, 1u);
    rhi_cmd_bind_storage_buffer(cmd, raw, 0u);
    rhi_cmd_bind_storage_buffer(cmd, rows, 1u);
    rhi_cmd_dispatch(cmd, 1u, 1u, 1u);
    rhi_cmd_memory_barrier(cmd);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);

    memset(raw_out, 0, sizeof(raw_out));
    memset(rows_out, 0, sizeof(rows_out));
    ASSERT_TRUE(rhi_buffer_read(g_dev, raw, raw_out, 0u, sizeof(raw_out)));
    ASSERT_TRUE(rhi_buffer_read(g_dev, rows, rows_out, 0u, sizeof(rows_out)));
    for (i = 0; i < RAW_WORDS; ++i)
        ASSERT_EQ(raw_out[i], seed + (u32)i);
    for (i = 0; i < ROWS; ++i) {
        ASSERT_EQ(rows_out[i * 4 + 0], (u32)i);
        ASSERT_EQ(rows_out[i * 4 + 1], (u32)i * 2u);
        ASSERT_EQ(rows_out[i * 4 + 2], (u32)i * 3u);
        ASSERT_EQ(rows_out[i * 4 + 3], seed);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, cs);
    rhi_buffer_destroy(g_dev, upload_only);
    rhi_buffer_destroy(g_dev, rows);
    rhi_buffer_destroy(g_dev, raw);
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
    RUN_TEST(shader_paths_resolve_to_blit_sidecars_and_render_red);
    RUN_TEST(blinn_phong_sidecar_resolves_offsets_and_shades_red);
    RUN_TEST(material_binder_puts_albedo_on_t0_and_falls_back_to_white);
    RUN_TEST(mrt_fbo_clears_and_reads_independent_attachments);
    RUN_TEST(blinn_phong_mrt_sidecar_writes_velocity_to_rt1);
    RUN_TEST(blinn_phong_arr_sidecar_forwards_the_layer_into_pixels);
    RUN_TEST(indirect_start_instance_does_not_reach_sv_instance_id);
    RUN_TEST(shadow_map_create_publishes_a_depth_target_and_destroy_is_idempotent);
    RUN_TEST(ssgi_gather_early_out_and_blur_pass_through_are_exact);
    RUN_TEST(lens_flare_sidecar_matches_the_derived_64_pixel_table);
    RUN_TEST(contact_shadow_sidecar_passes_offsets_and_runs_a_clean_march);
    RUN_TEST(motion_blur_sidecar_reads_depth_and_velocity_and_blurs);
    RUN_TEST(taa_sidecar_blends_history_through_the_neighbourhood_aabb);
    RUN_TEST(ssr_sidecar_pins_offsets_and_both_early_outs);
    RUN_TEST(forward_clip_z_conversion_keeps_near_geometry_unclipped);
    RUN_TEST(dof_sidecar_passes_focus_and_blurs_out_of_focus_via_multi_bind);
    RUN_TEST(instanced_sidecar_reads_lighting_from_the_temporal_cbv);
    RUN_TEST(skinned_sidecar_reads_lighting_from_the_temporal_cbv);
    RUN_TEST(fxaa_sidecar_blends_the_box_edge_and_passes_flat_regions);
    RUN_TEST(lens_effects_sidecar_produces_the_exact_vignette_ramp);
    RUN_TEST(color_grade_sidecar_applies_saturation_and_white_balance);
    RUN_TEST(texel_buffer_binding_delivers_instance_rows_to_the_shader);
    RUN_TEST(depth_only_sidecar_converts_clip_z_to_window_depth);
    RUN_TEST(shadow_atlas_depth_round_trips_through_the_sampling_path);
    RUN_TEST(shadow_bind_clears_each_frame_and_unbind_restores_the_screen);
    RUN_TEST(terrain_sidecar_lights_grass_and_reads_the_shadow_atlas);
    RUN_TEST(water_sidecar_deep_colour_and_underwater_darkening_are_exact);
    RUN_TEST(skybox_sidecar_scatters_an_exact_constant_sky);
    RUN_TEST(storage_buffers_receive_raw_and_structured_compute_writes);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
