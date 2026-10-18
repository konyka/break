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
     * backend, and the Vulkan twin test pins the same seven numbers. */
    static const char *const names[7] = {
        "u_model", "u_view", "u_proj", "u_light_dir",
        "u_light_color", "u_ambient", "u_camera_pos"
    };
    static const i32 expected[7] = { 0, 64, 128, 192, 208, 224, 240 };
    i32 loc[7];
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
    rhi_cmd_set_uniform_vec3(cmd, loc[6],  0.0f,  0.0f, -10.0f);
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
    rhi_cmd_set_uniform_vec3(cmd, loc[6],  0.0f,  0.0f, -10.0f);
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

    for (i = 0; i < 7; ++i) {
        loc[i] = rhi_pipeline_get_uniform_location(g_dev, pipe, names[i]);
        ASSERT_TRUE(loc[i] >= 0);
    }

    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.size = sizeof(verts);
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));

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
    rhi_cmd_set_uniform_vec3(cmd, loc[6],  0.0f,  0.0f, -10.0f);
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
    rhi_cmd_set_uniform_vec3(cmd, loc[6],  0.0f,  0.0f, -10.0f);
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
    rhi_cmd_set_uniform_vec3(cmd, loc[6],  0.0f,  0.0f, -10.0f);
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
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
