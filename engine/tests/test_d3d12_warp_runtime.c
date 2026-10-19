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
    RUN_TEST(depth_only_sidecar_converts_clip_z_to_window_depth);
    RUN_TEST(shadow_atlas_depth_round_trips_through_the_sampling_path);
    RUN_TEST(shadow_bind_clears_each_frame_and_unbind_restores_the_screen);
    RUN_TEST(terrain_sidecar_lights_grass_and_reads_the_shadow_atlas);
    RUN_TEST(water_sidecar_deep_colour_and_underwater_darkening_are_exact);
    RUN_TEST(skybox_sidecar_scatters_an_exact_constant_sky);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
