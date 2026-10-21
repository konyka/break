#include <rhi/rhi.h>
#include <renderer/indirect_draw.h>
#include <renderer/post_process.h>
#include <renderer/tonemap.h>
#include <renderer/sss.h>
#include <renderer/cinematic.h>
#include <renderer/upscale.h>
#include <renderer/volumetric.h>
#include <renderer/ssao.h>
#include <renderer/sharpen.h>
#include <renderer/god_rays.h>
#include <renderer/debug_viz.h>
#include <renderer/combined_post_process.h>
#include <renderer/fxaa.h>
#include <renderer/deferred.h>
#include <renderer/lighting.h>
#include <renderer/point_shadow.h>
#include <stdlib.h>
#include <math/math.h>
#include <math.h>
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
 * It does not corrupt rendering. R637 enabled indirect draw on D3D12, and
 * this was the trapdoor under it: every mesh would still shade correctly --
 * with layer 0 -- and nothing would announce it. So D3D12 reports
 * caps.indirect_first_instance_supported = false, and main.c keeps the R437
 * per-group path (one material bind + one execute per group) instead of the
 * array path whenever that cap is false. The test asserts both caps below.
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
           "SV_InstanceID on either adapter. D3D12 therefore reports "
           "caps.indirect_first_instance_supported = false and the demo keeps "
           "the per-group path; see the header comment.\n",
           on_warp ? "WARP" : "hardware");
    {
        RHICapabilities caps;
        ASSERT_TRUE(rhi_device_get_capabilities(g_dev, &caps));
        ASSERT_TRUE(caps.indirect_draw_supported);
        ASSERT_FALSE(caps.indirect_first_instance_supported);
    }

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

    /* R638: a TRANSLATED instance. Identity is its own transpose, so the two
     * frames above could not tell a row-major from a column-major read of
     * the instance rows -- and the sidecar did read them as rows, which in
     * the demo stretched every entity across the screen. Here the model is
     * scale 0.5 plus translation (+0.5, +0.5) in the engine's column-major
     * layout (translation in the 4th column = rows 12..14 of the upload), so
     * the full-screen quad must shrink into the +x/+y quadrant only. */
    {
        static const float moved[8 * 4] = {
            0.5f,0,0,0,  0,0.5f,0,0,  0,0,1,0,  0.5f,0.5f,0,1,
            0.5f,0,0,0,  0,0.5f,0,0,  0,0,1,0,  0.5f,0.5f,0,1
        };
        RHIBuffer moved_buf;
        int x, y;
        memset(&bdesc, 0, sizeof(bdesc));
        bdesc.size = sizeof(moved);
        bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
        bdesc.initial_data = moved;
        moved_buf = rhi_buffer_create(g_dev, &bdesc);
        ASSERT_TRUE(rhi_handle_valid(moved_buf));
        t.dir[0] = 0.0f; t.dir[1] = -1.0f; t.dir[2] = 0.0f;
        t.amb[0] = 0.4f;  t.amb[1] = 0.2f;  t.amb[2] = 0.08f;
        rhi_buffer_update(g_dev, ubo, &t, sizeof(t));
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_mrt_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_texture(cmd, albedo, sampler, 0u);
        rhi_cmd_bind_texel_buffers(cmd, moved_buf, RHI_HANDLE_NULL);
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
        /* Offscreen targets keep GL row order: NDC y > 0 is rows 4..7. */
        for (y = 0; y < 8; ++y) {
            for (x = 0; x < 8; ++x) {
                int lit = rt0[(y * 8 + x) * 4 + 0] == want[0][0];
                int inside = x >= 4 && y >= 4;
                if (lit != inside)
                    printf("  translated instance: px (%d,%d) lit=%d want %d\n",
                           x, y, lit, inside);
                ASSERT_EQ(lit, inside);
            }
        }
        rhi_buffer_destroy(g_dev, moved_buf);
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

/* R637: the real IndirectDrawSystem on D3D12, end to end. Four quads, one
 * per screen quadrant, in two material groups (0,1 | 2,3). Visibility culls
 * quad 1 and quad 2. The grouped compact runs on the GPU (compact_draws_
 * hlsl.comp), and each group then draws through ExecuteIndirect with its GPU
 * count. Exactly quadrants 0 and 3 may turn green.
 *
 * After the draw the same frame compacts again with everything visible and
 * draws nothing from it. That pins C-BUF-3 for the per-cascade shadow
 * pattern: a recorded visibility write has to land at its place in the list,
 * not be collapsed into the last host write of the frame. */
TEST(indirect_draw_system_compacts_and_draws_on_the_gpu) {
    static const float quads[4][6 * 3] = {
        { -1,-1,0,  0,-1,0,  0, 0,0,  -1,-1,0,  0, 0,0, -1, 0,0 },
        {  0,-1,0,  1,-1,0,  1, 0,0,   0,-1,0,  1, 0,0,  0, 0,0 },
        { -1, 0,0,  0, 0,0,  0, 1,0,  -1, 0,0,  0, 1,0, -1, 1,0 },
        {  0, 0,0,  1, 0,0,  1, 1,0,   0, 0,0,  1, 1,0,  0, 1,0 },
    };
    static const u16 indices[24] = {
        0,1,2,3,4,5,  6,7,8,9,10,11,  12,13,14,15,16,17,  18,19,20,21,22,23
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    const u32 all_visible[4] = { 1u, 1u, 1u, 1u };
    const u32 culled[4] = { 1u, 0u, 0u, 1u };
    const u32 group_sizes[2] = { 2u, 2u };
    DrawIndexedIndirectCmd cmds[4];
    IndirectDrawSystem sys;
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pdesc;
    RHIBufferDesc bdesc;
    RHIBuffer vbo, ibo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    u32 counts[2] = { 99u, 99u };
    u32 total = 99u;
    i32 loc;
    int q, x, y;

    for (q = 0; q < 4; ++q) {
        cmds[q].index_count = 6u;
        cmds[q].instance_count = 1u;
        cmds[q].first_index = (u32)q * 6u;
        cmds[q].vertex_offset = 0;
        cmds[q].first_instance = 0u;
    }
    memset(&sys, 0, sizeof(sys));
    ASSERT_TRUE(indirect_draw_init_grouped(&sys, g_dev, 4u, 2u));
    indirect_draw_upload_grouped(&sys, g_dev, cmds, group_sizes, 2u);

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));
    vs = rhi_shader_create(g_dev, "probe_vb_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "probe_vb_hlsl.frag", 0, true);
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 12u;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe));
    loc = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_transform");
    ASSERT_TRUE(loc >= 0);
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = sizeof(quads);
    bdesc.initial_data = quads;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    bdesc.usage = RHI_BUFFER_USAGE_INDEX;
    bdesc.size = sizeof(indices);
    bdesc.initial_data = indices;
    ibo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(vbo));
    ASSERT_TRUE(rhi_handle_valid(ibo));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    indirect_draw_upload_visibility_cmd(&sys, g_dev, cmd, culled, 4u);
    indirect_draw_compact(&sys, g_dev, cmd);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, (u32)loc, identity, sizeof(identity));
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_bind_index_buffer(cmd, ibo, 0u, false);
    indirect_draw_execute_group(&sys, g_dev, 0u);
    indirect_draw_execute_group(&sys, g_dev, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    /* A second pass in the same frame with everything visible, compacted but
     * never drawn. If recorded writes collapsed into host writes, the draw
     * above would see these flags and light all four quadrants. */
    indirect_draw_upload_visibility_cmd(&sys, g_dev, cmd, all_visible, 4u);
    indirect_draw_compact(&sys, g_dev, cmd);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);

    /* The counters hold the LAST compact: all four visible, two per group. */
    ASSERT_TRUE(rhi_buffer_read(g_dev, sys.group_counts_buf, counts, 0u, sizeof(counts)));
    ASSERT_TRUE(rhi_buffer_read(g_dev, sys.draw_count_buf, &total, 0u, sizeof(total)));
    ASSERT_EQ(counts[0], 2u);
    ASSERT_EQ(counts[1], 2u);
    ASSERT_EQ(total, 4u);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    /* The backend's viewport is bottom-left origin (TopLeftY = h, negative
     * height, rhi_d3d12_set_full_target_viewport), so NDC y = -1 is memory
     * row 0 of the render target, as on GL. Quad 0 (x<0, y<0) is therefore
     * rows 0..3, columns 0..3; quad 3 rows 4..7, columns 4..7. The two lit
     * quadrants are on a diagonal, so a wrong cull and a wrong orientation
     * cannot cancel out. */
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            int quad = (x >= 4 ? 1 : 0) + (y >= 4 ? 2 : 0);
            int green = px[(y * 8 + x) * 4 + 1] > 200;
            if (green != (quad == 0 || quad == 3))
                printf("  pixel (%d,%d) quad %d green=%d\n", x, y, quad, green);
            ASSERT_EQ(green, (quad == 0 || quad == 3));
        }
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    indirect_draw_destroy(&sys, g_dev);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_buffer_destroy(g_dev, ibo);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* R638: the demo's whole D3D12 frame was black because PostProcess never
 * initialised: post_process.c handed inline GLSL to rhi_shader_create, which
 * this backend refuses, so postfx.ready stayed false and main.c skipped the
 * final tex_pipe blit onto the swapchain -- the back buffer was never
 * written. This drives the real PostProcess: init must succeed, tex_pipe
 * must copy a texture exactly, and the full bloom chain (extract, 4 blurs,
 * composite) must run. The grey input is below the 1.0 threshold, so bloom
 * contributes nothing and the composite must equal the input. */
TEST(post_process_initialises_and_blits_on_d3d12) {
    static unsigned char grey[4 * 4 * 4];
    PostProcess pp;
    RHITextureDesc td;
    RHITexture src;
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    u16 comp[8 * 8 * 4];
    int i;
    memset(grey, 128, sizeof(grey));
    for (i = 3; i < (int)sizeof(grey); i += 4) grey[i] = 255;
    memset(&td, 0, sizeof(td));
    td.width = 4u; td.height = 4u;
    td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
    td.data = grey;
    src = rhi_texture_create(g_dev, &td);
    ASSERT_TRUE(rhi_handle_valid(src));

    ASSERT_TRUE(post_process_init(&pp, g_dev, 8u, 8u));
    ASSERT_TRUE(pp.ready);
    ASSERT_TRUE(rhi_handle_valid(pp.tex_pipe));
    ASSERT_TRUE(pp.loc_threshold >= 0);
    ASSERT_TRUE(pp.loc_direction >= 0);
    ASSERT_TRUE(pp.loc_bloom_strength >= 0);

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    post_process_apply(&pp, cmd, src, 8u, 8u);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pp.tex_pipe);
    rhi_cmd_bind_texture(cmd, src, pp.sampler, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        ASSERT_EQ(px[i + 0], 128);
        ASSERT_EQ(px[i + 1], 128);
        ASSERT_EQ(px[i + 2], 128);
    }
    memset(comp, 0, sizeof(comp));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, pp.fbo_composite.color_tex,
                                        comp, sizeof(comp)));
    for (i = 0; i < 8 * 8 * 4; i += 4) {
        float r = warp_half_to_float(comp[i + 0]);
        float g = warp_half_to_float(comp[i + 1]);
        float b = warp_half_to_float(comp[i + 2]);
        ASSERT_TRUE(r > 0.495f && r < 0.51f);
        ASSERT_TRUE(g > 0.495f && g < 0.51f);
        ASSERT_TRUE(b > 0.495f && b < 0.51f);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    post_process_shutdown(&pp);
    rhi_texture_destroy(g_dev, src);
}

static double warp_aces(double x) {
    double v = (x * (2.51 * x + 0.03)) / (x * (2.43 * x + 0.59) + 0.14);
    return v < 0.0 ? 0.0 : (v > 1.0 ? 1.0 : v);
}

/* R638: tonemap and luminance on D3D12, through the real TonemapSystem.
 * Before the sidecars, tonemap_init failed exactly like PostProcess did
 * (inline GLSL refused), so the D3D12 frame went out untonemapped.
 *
 * Constant HDR input (2.0, 0.25, 0.25) in RGBA16F. The luminance pass
 * log-averages a constant, so current = its Rec.709 luma L; dt is large
 * enough that adaptation saturates (1 - exp(-speed*dt) == 1 in float), so
 * adapted = L. Tonemap then uses exposure = mix(1.5, 1 / (L + 0.5), 0.8) and
 * each channel is aces(c * exposure) ^ (1 / 2.2), computed below from the
 * same formula rather than hard-coded. The luminance target is read back
 * too, so a wrong t1 binding cannot hide behind a lucky exposure. */
TEST(tonemap_and_luminance_sidecars_match_the_aces_formula) {
    static u16 hdr[4 * 4 * 4];
    TonemapSystem tm;
    RHITextureDesc td;
    RHITexture src;
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    u16 lum[4];
    /* Non-grey on purpose: luminance (0.62205) differs from every channel,
     * so sampling the scene where the luminance belongs changes the result. */
    static const double in_rgb[3] = { 2.0, 0.25, 0.25 };
    const double luma = 0.2126 * 2.0 + 0.7152 * 0.25 + 0.0722 * 0.25;
    const double exposure = 0.2 * 1.5 + 0.8 * (1.0 / (luma + 0.5));
    int want[3];
    int i;
    for (i = 0; i < 3; ++i)
        want[i] = (int)floor(pow(warp_aces(in_rgb[i] * exposure), 1.0 / 2.2) * 255.0 + 0.5);
    for (i = 0; i < 4 * 4 * 4; i += 4) {
        hdr[i + 0] = 0x4000u; hdr[i + 1] = 0x3400u;   /* 2.0, 0.25 */
        hdr[i + 2] = 0x3400u; hdr[i + 3] = 0x3C00u;   /* 0.25, 1.0 */
    }
    memset(&td, 0, sizeof(td));
    td.width = 4u; td.height = 4u;
    td.format = RHI_FORMAT_R16G16B16A16_SFLOAT; td.mip_levels = 1u;
    td.data = hdr;
    src = rhi_texture_create(g_dev, &td);
    ASSERT_TRUE(rhi_handle_valid(src));

    ASSERT_TRUE(tonemap_init(&tm, g_dev));
    ASSERT_TRUE(rhi_handle_valid(tm.lum_pipe));
    ASSERT_TRUE(tm.loc_exposure >= 0 && tm.loc_gamma >= 0 && tm.loc_mode >= 0);
    ASSERT_TRUE(tm.loc_lum_speed >= 0 && tm.loc_lum_dt >= 0);
    tm.mode = 0;

    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    tonemap_update_auto_exposure(&tm, cmd, src, 8u, 8u, 100.0f);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    tonemap_apply(&tm, cmd, src, 8u, 8u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);

    memset(lum, 0, sizeof(lum));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, tm.lum_fbo[tm.lum_idx].color_tex,
                                        lum, sizeof(lum)));
    {
        float adapted = warp_half_to_float(lum[0]);
        ASSERT_TRUE(fabs(adapted - luma) < 0.005);
    }
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < (int)sizeof(px); i += 4) {
        int c;
        for (c = 0; c < 3; ++c) {
            int d = (int)px[i + c] - want[c];
            if (d < -1 || d > 1)
                printf("  px %d ch %d = %d, want %d\n", i / 4, c, (int)px[i + c], want[c]);
            ASSERT_TRUE(d >= -1 && d <= 1);
        }
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    tonemap_shutdown(&tm);
    rhi_texture_destroy(g_dev, src);
}

/* R638: every offscreen FBO takes one RTV and one DSV. The DSV heap used to
 * hold 16, so the demo's 17th FBO failed and about a dozen post subsystems
 * (TAA, FXAA, motion blur, lens effects, the second tonemap, ...) disabled
 * themselves at init. 64 live FBOs is comfortably above what the demo
 * creates; all of them must come back valid. */
TEST(offscreen_fbo_budget_covers_the_demo_post_chain) {
    enum { N = 64 };
    static RHIOffscreenFBO fbos[N];
    RHIOffscreenFBODesc desc;
    int i;
    memset(&desc, 0, sizeof(desc));
    desc.width = 4u; desc.height = 4u;
    desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    desc.sample_count = 1u;
    for (i = 0; i < N; ++i) {
        fbos[i] = rhi_offscreen_fbo_create_desc(g_dev, &desc);
        if (!rhi_handle_valid(fbos[i].fb)) printf("  fbo %d refused\n", i);
        ASSERT_TRUE(rhi_handle_valid(fbos[i].fb));
    }
    for (i = 0; i < N; ++i) rhi_offscreen_fbo_destroy(g_dev, &fbos[i]);
}

/* Swapchain orientation probe: a quad covering NDC y > 0 drawn straight to
 * the back buffer must land in the TOP half of the presented image, which is
 * what rhi_screenshot returns first (top-down rows, rhi.h contract). Drawn
 * twice: once under the viewport rhi_frame_begin installs, once after an
 * explicit rhi_cmd_set_viewport -- the call the UI canvas makes. */
static int warp_swapchain_top_half_green(int explicit_viewport) {
    static const float quad[6 * 3] = {
        -1, 0,0,  1, 0,0,  1, 1,0,  -1, 0,0,  1, 1,0,  -1, 1,0
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    RHIShader vs, fs;
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    static unsigned char px[64 * 64 * 4];
    int ok = 1, y;
    vs = rhi_shader_create(g_dev, "probe_vb_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "probe_vb_hlsl.frag", 0, true);
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 12u;
    /* A viewport flip also flips screen-space winding; this probe measures
     * orientation only, so facing must not decide whether it draws. */
    pdesc.disable_culling = true;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = sizeof(quad);
    bdesc.initial_data = quad;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    cmd = rhi_frame_begin(g_dev);
    if (cmd == NULL || !rhi_handle_valid(pipe)) return -1;
    rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 1.0f);
    if (explicit_viewport)
        rhi_cmd_set_viewport(cmd, 0.0f, 0.0f, 64.0f, 64.0f, 0.0f, 1.0f);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, 0u, identity, sizeof(identity));
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    if (rhi_frame_end_ex(g_dev) != RHI_RESULT_OK) return -1;
    memset(px, 0, sizeof(px));
    if (!rhi_screenshot(g_dev, 0u, 0u, 64u, 64u, px, sizeof(px))) return -1;
    /* 1 = exactly the top half green, 0 = exactly the bottom half, -1 =
     * anything else (nothing drawn, or a partial cover). */
    {
        int top = 1, bottom = 1;
        for (y = 0; y < 64; ++y) {
            int green = px[(y * 64 + 32) * 4 + 1] > 200;
            if (green != (y < 32)) top = 0;
            if (green != (y >= 32)) bottom = 0;
        }
        ok = top ? 1 : (bottom ? 0 : -1);
    }
    printf("  swapchain probe (%s viewport): row 0 green=%d, row 63 green=%d\n",
           explicit_viewport ? "explicit" : "frame_begin",
           px[(0 * 64 + 32) * 4 + 1] > 200, px[(63 * 64 + 32) * 4 + 1] > 200);
    (void)rhi_present_ex(g_dev);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
    return ok;
}

/* R638: the two viewport conventions, pinned on the presented image.
 * rhi_cmd_set_viewport is the RHI's +Y-up viewport (the UI canvas relies on
 * it, R715) and must put NDC y > 0 in the top half. The frame's default
 * viewport is the twin of VK's positive {0, 0, w, h}, which puts NDC +Y at
 * the bottom; that is what keeps offscreen targets in GL row order for the
 * post chain, and it is asserted as such so the two can never silently
 * collapse into one again -- which is exactly the bug this pins. */
TEST(swapchain_draws_put_ndc_up_at_the_top_of_the_screen) {
    int frame_default = warp_swapchain_top_half_green(0);
    int explicit_vp = warp_swapchain_top_half_green(1);
    ASSERT_EQ(frame_default, 0);
    ASSERT_EQ(explicit_vp, 1);
}

/* R638: the demo's whole route for scene orientation. A quad over NDC
 * y > 0 is drawn into an offscreen FBO (as the forward pass does, under the
 * FBO's default viewport), then copied to the back buffer with
 * PostProcess.tex_pipe after rhi_offscreen_fbo_unbind -- the exact last two
 * steps of main.c's frame. "Up in NDC" must come out as the top half of the
 * presented image, which is what the user sees. */
TEST(scene_through_offscreen_and_final_blit_keeps_ndc_up_on_top) {
    static const float quad[6 * 3] = {
        -1, 0,0,  1, 0,0,  1, 1,0,  -1, 0,0,  1, 1,0,  -1, 1,0
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    static unsigned char px[64 * 64 * 4];
    PostProcess pp;
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    int y, top = 1;
    ASSERT_TRUE(post_process_init(&pp, g_dev, 64u, 64u));
    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 64u; fbo_desc.height = 64u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    vs = rhi_shader_create(g_dev, "probe_vb_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "probe_vb_hlsl.frag", 0, true);
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 12u;
    pdesc.disable_culling = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = sizeof(quad);
    bdesc.initial_data = quad;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb) && rhi_handle_valid(pipe) && rhi_handle_valid(vbo));

    rhi_offscreen_fbo_set_clear_color(g_dev, &fbo, 0.0f, 0.0f, 0.0f, 1.0f);
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, 0u, identity, sizeof(identity));
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    rhi_cmd_bind_pipeline(cmd, pp.tex_pipe);
    rhi_cmd_bind_texture(cmd, fbo.color_tex, pp.sampler, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_screenshot(g_dev, 0u, 0u, 64u, 64u, px, sizeof(px)));
    for (y = 0; y < 64; ++y)
        if ((px[(y * 64 + 32) * 4 + 1] > 200) != (y < 32)) top = 0;
    printf("  scene route: screen row 0 green=%d, row 63 green=%d\n",
           px[(0 * 64 + 32) * 4 + 1] > 200, px[(63 * 64 + 32) * 4 + 1] > 200);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(top);

    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    post_process_shutdown(&pp);
}

/* R638: the engine's own camera matrices, end to end. A camera at the origin
 * looking down -Z (mat4_lookat) with mat4_perspective, and a quad 5 units
 * ahead spanning world y in [0.5, 2]: it is above the eye, so it must come
 * out in the TOP half of the presented image after the offscreen pass and
 * the final blit. Unlike the NDC probes above this goes through P * V built
 * by src/math, so a matrix-packing or handedness mismatch shows up here. */
TEST(engine_camera_puts_world_up_at_the_top_of_the_screen) {
    static const float quad[6 * 3] = {
        -1.0f, 0.5f, -5.0f,   1.0f, 0.5f, -5.0f,   1.0f, 2.0f, -5.0f,
        -1.0f, 0.5f, -5.0f,   1.0f, 2.0f, -5.0f,  -1.0f, 2.0f, -5.0f
    };
    static unsigned char px[64 * 64 * 4];
    Mat4 proj = mat4_perspective(1.0471976f, 1.0f, 0.1f, 100.0f);
    Mat4 view = mat4_lookat(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f),
                            vec3(0.0f, 1.0f, 0.0f));
    Mat4 vp = mat4_mul(proj, view);
    PostProcess pp;
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    RHIBufferDesc bdesc;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    int y, first = -1, last = -1;
    ASSERT_TRUE(post_process_init(&pp, g_dev, 64u, 64u));
    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 64u; fbo_desc.height = 64u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    vs = rhi_shader_create(g_dev, "probe_vb_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "probe_vb_hlsl.frag", 0, true);
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 12u;
    pdesc.disable_culling = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = sizeof(quad);
    bdesc.initial_data = quad;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb) && rhi_handle_valid(pipe) && rhi_handle_valid(vbo));

    rhi_offscreen_fbo_set_clear_color(g_dev, &fbo, 0.0f, 0.0f, 0.0f, 1.0f);
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, 0u, &vp.e[0][0], 64u);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    rhi_cmd_bind_pipeline(cmd, pp.tex_pipe);
    rhi_cmd_bind_texture(cmd, fbo.color_tex, pp.sampler, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_screenshot(g_dev, 0u, 0u, 64u, 64u, px, sizeof(px)));
    for (y = 0; y < 64; ++y) {
        if (px[(y * 64 + 32) * 4 + 1] > 200) {
            if (first < 0) first = y;
            last = y;
        }
    }
    printf("  camera route: green rows %d..%d of 64\n", first, last);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    /* y in [0.5, 2] at distance 5 with a 60 deg fov: NDC y in [0.17, 0.69],
     * i.e. screen rows ~10..26 from the top. */
    ASSERT_TRUE(first >= 0);
    ASSERT_TRUE(last < 32);

    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    post_process_shutdown(&pp);
}

/* R638: main.c sets the forward pass's view/proj once, runs the indirect
 * compact (a compute dispatch), rebinds the graphics pipeline (R234-A) and
 * then draws. Vulkan keeps the graphics push constants across that; this
 * pins the same on D3D12. The quad only covers the centre if the pushed
 * 0.5-scale transform is still in effect at the draw; a lost transform
 * (zeroed root constants) degenerates every vertex onto the origin. */
TEST(graphics_push_constants_survive_a_compute_pass_and_rebind) {
    static const float quad[6 * 3] = {
        -1,-1,0,  1,-1,0,  1,1,0,  -1,-1,0,  1,1,0,  -1,1,0
    };
    static const float half[16] = { 0.5f,0,0,0, 0,0.5f,0,0, 0,0,1,0, 0,0,0,1 };
    static u32 raw_init[64];
    static u32 rows_init[64];
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs, cs;
    RHIPipelineDesc pdesc;
    RHIPipeline pipe, cpipe;
    RHIBufferDesc bdesc;
    RHIBuffer vbo, raw, rows;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    const u32 seed = 7u;
    int x, y;
    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    vs = rhi_shader_create(g_dev, "probe_vb_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "probe_vb_hlsl.frag", 0, true);
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs; pdesc.frag = fs;
    pdesc.vertex_stride = 12u;
    pdesc.disable_culling = true;
    pdesc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pipe = rhi_pipeline_create(g_dev, &pdesc);
    cs = rhi_shader_create_compute_path(g_dev, "shaders/probe_storage.comp");
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.is_compute = true;
    pdesc.frag = cs;
    cpipe = rhi_pipeline_create(g_dev, &pdesc);
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = sizeof(quad);
    bdesc.initial_data = quad;
    vbo = rhi_buffer_create(g_dev, &bdesc);
    bdesc.usage = RHI_BUFFER_USAGE_STORAGE;
    bdesc.size = sizeof(raw_init);
    bdesc.initial_data = raw_init;
    raw = rhi_buffer_create(g_dev, &bdesc);
    bdesc.size = sizeof(rows_init);
    bdesc.initial_data = rows_init;
    rows = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe) && rhi_handle_valid(cpipe));

    rhi_offscreen_fbo_set_clear_color(g_dev, &fbo, 0.0f, 0.0f, 0.0f, 1.0f);
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_push_constants(cmd, 0u, half, sizeof(half));
    rhi_cmd_bind_pipeline(cmd, cpipe);
    rhi_cmd_push_constants(cmd, 0u, &seed, sizeof(seed));
    rhi_cmd_bind_storage_buffer(cmd, raw, 0u);
    rhi_cmd_bind_storage_buffer(cmd, rows, 1u);
    rhi_cmd_dispatch(cmd, 1u, 1u, 1u);
    rhi_cmd_memory_barrier(cmd);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            int inside = x >= 2 && x < 6 && y >= 2 && y < 6;
            int green = px[(y * 8 + x) * 4 + 1] > 200;
            if (green != inside) printf("  px (%d,%d) green=%d want %d\n", x, y, green, inside);
            ASSERT_EQ(green, inside);
        }
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    rhi_buffer_destroy(g_dev, rows);
    rhi_buffer_destroy(g_dev, raw);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, cpipe);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, cs);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
}

/* R638: the demo's instanced pattern. main.c owns ONE host-visible instance
 * buffer per frame slot, rewrites it with rhi_cmd_update_buffer for every
 * mesh and binds it with rhi_cmd_bind_texel_buffers before that mesh's draw.
 * The texel binder used to view the buffer itself, which after recording
 * already holds the frame's LAST write, so every draw got the last mesh's
 * rows -- the large wrong triangles in the D3D12 demo. Here two draws in
 * one frame write different rows (red, then green) into the same buffer and
 * cover the left and right halves; each half must keep its own colour. */
TEST(texel_buffer_rewritten_per_draw_feeds_each_draw_its_own_rows) {
    static const float left[3 * 3]  = { -1,-1,0,  0,-1,0,  -1, 3,0 };
    static const float left2[3 * 3] = { 0,-1,0,  0, 3,0,  -1, 3,0 };
    static const float right[3 * 3] = { 0,-1,0,  3,-1,0,   0, 3,0 };
    static const float red[4]   = { 1.0f, 0.0f, 0.0f, 1.0f };
    static const float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    RHIOffscreenFBODesc fbo_desc;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bdesc;
    RHIBuffer vl, vl2, vr, inst;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    int x, y;
    memset(&fbo_desc, 0, sizeof(fbo_desc));
    fbo_desc.width = 8u; fbo_desc.height = 8u;
    fbo_desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo_desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fbo_desc);
    vs = rhi_shader_create(g_dev, "texel_buffer_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "texel_buffer_hlsl.frag", 0, true);
    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.vertex_stride = 12u;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.disable_culling = true;
    pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = sizeof(left);
    bdesc.initial_data = left;  vl  = rhi_buffer_create(g_dev, &bdesc);
    bdesc.initial_data = left2; vl2 = rhi_buffer_create(g_dev, &bdesc);
    bdesc.initial_data = right; vr  = rhi_buffer_create(g_dev, &bdesc);
    /* Same shape as main.c's instance_buf: TEXEL | STORAGE, no initial
     * data, so it lives on the UPLOAD heap. */
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_TEXEL | RHI_BUFFER_USAGE_STORAGE;
    bdesc.size = 256u;
    inst = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(pipe) && rhi_handle_valid(inst));

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 1.0f, 1.0f);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_update_buffer(cmd, inst, 0u, red, sizeof(red));
    rhi_cmd_bind_texel_buffers(cmd, inst, inst);
    rhi_cmd_bind_vertex_buffer(cmd, vl, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_cmd_bind_vertex_buffer(cmd, vl2, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_cmd_update_buffer(cmd, inst, 0u, green, sizeof(green));
    rhi_cmd_bind_texel_buffers(cmd, inst, inst);
    rhi_cmd_bind_vertex_buffer(cmd, vr, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            const unsigned char *p = &px[(y * 8 + x) * 4];
            int want_red = x < 4;
            if ((p[0] > 200) != want_red || (p[1] > 200) == want_red)
                printf("  px (%d,%d) = %u,%u,%u want %s\n", x, y, p[0], p[1], p[2],
                       want_red ? "red" : "green");
            ASSERT_EQ(p[0] > 200, want_red);
            ASSERT_EQ(p[1] > 200, !want_red);
        }
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    rhi_buffer_destroy(g_dev, inst);
    rhi_buffer_destroy(g_dev, vr);
    rhi_buffer_destroy(g_dev, vl2);
    rhi_buffer_destroy(g_dev, vl);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
}

/* R640: SSAO on D3D12, through the real SSAOSystem. Before ssao_hlsl.frag /
 * ssao_blur_hlsl.frag, ssao_init failed at "shader compile failed" (inline
 * GLSL refused), so the demo ran with no AO on this backend.
 *
 * Scene: one plane perpendicular to the view axis at z = -3, written as a
 * constant window depth d = ndc_z * 0.5 + 0.5 into an R32F texture. The
 * projection is off-centre (e[2][0] = 0.3, e[2][1] = -0.15, the slots TAA
 * jitter uses), which makes inv_proj asymmetric: an upload that transposes
 * it, or reads it from the wrong offset, reconstructs a different plane.
 * Constant depth means every tap reads the same texel value, so filtering
 * cannot move the answer; the reconstructed position is linear in uv, so
 * the fine derivatives give the exact plane normal (0,0,1).
 *
 * Expected values come from warp_ssao_ref, a line-for-line double-precision
 * port of ssao.frag fed with the same f32 inv_proj and depth the GPU sees,
 * at the pixel centre (c + 0.5, r + 0.5) -- SV_Position on an offscreen
 * target, whose memory row 0 is NDC y = -1. bias 0.9 rather than the
 * default 0.025: on a bare plane every horizon sits at the view's grazing
 * angle and the default bias saturates the whole frame to AO = 0, which
 * would pass with almost any wrong input; 0.9 spreads the 8x8 frame across
 * the whole 0..1 range (checked below: the test refuses to run on a
 * degenerate expectation). Tolerance is 3/255 for GPU acos/sin/cos.
 *
 * The blur pass is then checked against the raw AO actually read back:
 * constant depth makes every bilateral weight exp(0) = 1, so the result is
 * the plain 5x5 Gaussian exp(-(x^2+y^2)/4) of the raw values. Only the 4x4
 * interior is asserted -- there all 25 taps are in range, so the D3D12
 * static WRAP sampler and GL's CLAMP_TO_EDGE agree. A second frame with
 * depth 1.0 must hit both early-outs and come back exactly white. */
static double warp_ssao_ref(const Mat4 *inv, float depth, int c, int r,
                            int w, int h, double sw, double sh,
                            double radius, double bias)
{
    double u = (c + 0.5) / w, v = (r + 0.5) / h;
    double pos[3], px[3], py[3], dx[3], dy[3], n[3], view[3];
    double noise, ao = 0.0, len;
    int d, s, k;
#define WARP_SSAO_REC(out, uu, vv) do { \
        double ndc_[4], vh_[4]; int i_, j_; \
        ndc_[0] = (uu) * 2.0 - 1.0; ndc_[1] = (vv) * 2.0 - 1.0; \
        ndc_[2] = (double)depth * 2.0 - 1.0; ndc_[3] = 1.0; \
        for (i_ = 0; i_ < 4; ++i_) { \
            vh_[i_] = 0.0; \
            for (j_ = 0; j_ < 4; ++j_) vh_[i_] += (double)inv->e[j_][i_] * ndc_[j_]; \
        } \
        for (i_ = 0; i_ < 3; ++i_) (out)[i_] = vh_[i_] / vh_[3]; \
    } while (0)
    WARP_SSAO_REC(pos, u, v);
    WARP_SSAO_REC(px, (c + 1.5) / w, v);
    WARP_SSAO_REC(py, u, (r + 1.5) / h);
    for (k = 0; k < 3; ++k) { dx[k] = px[k] - pos[k]; dy[k] = py[k] - pos[k]; }
    n[0] = dx[1] * dy[2] - dx[2] * dy[1];
    n[1] = dx[2] * dy[0] - dx[0] * dy[2];
    n[2] = dx[0] * dy[1] - dx[1] * dy[0];
    len = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    for (k = 0; k < 3; ++k) n[k] /= len;
    {
        double t = 0.06711056 * (c + 0.5) + 0.00583715 * (r + 0.5);
        t = 52.9829189 * (t - floor(t));
        noise = t - floor(t);
    }
    len = sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]);
    for (k = 0; k < 3; ++k) view[k] = -pos[k] / len;
    for (d = 0; d < 4; ++d) {
        double angle = (d + noise) * 3.14159265 / 4.0;
        double dirx = cos(angle), diry = sin(angle);
        double hpos = -1.0, bt[3], np[3], cos_n, h2, a1, a2, contrib, ndb;
        for (s = 0; s < 6; ++s) {
            double t = (s + 0.5) / 6.0 * radius;
            double su = u + dirx * t / sw, sv = v + diry * t / sh;
            double sp[3], diff[3], dist, cos_h;
            if (su < 0.0 || su > 1.0 || sv < 0.0 || sv > 1.0) continue;
            WARP_SSAO_REC(sp, su, sv);
            for (k = 0; k < 3; ++k) diff[k] = sp[k] - pos[k];
            dist = sqrt(diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2]);
            if (dist < 0.001) dist = 0.001;
            cos_h = (view[0] * diff[0] + view[1] * diff[1] + view[2] * diff[2]) / dist;
            if (cos_h > hpos) hpos = cos_h;
        }
        /* bitangent = normalize(cross(view, (dir, 0))) */
        bt[0] = view[1] * 0.0 - view[2] * diry;
        bt[1] = view[2] * dirx - view[0] * 0.0;
        bt[2] = view[0] * diry - view[1] * dirx;
        len = sqrt(bt[0] * bt[0] + bt[1] * bt[1] + bt[2] * bt[2]);
        for (k = 0; k < 3; ++k) bt[k] /= len;
        ndb = n[0] * bt[0] + n[1] * bt[1] + n[2] * bt[2];
        for (k = 0; k < 3; ++k) np[k] = n[k] - bt[k] * ndb;
        len = sqrt(np[0] * np[0] + np[1] * np[1] + np[2] * np[2]);
        cos_n = len > 0.001
            ? (np[0] * view[0] + np[1] * view[1] + np[2] * view[2]) / len : 0.0;
        h2 = hpos + bias;
        if (h2 < -1.0) h2 = -1.0;
        if (h2 > 1.0) h2 = 1.0;
        a1 = acos(cos_n < -1.0 ? -1.0 : (cos_n > 1.0 ? 1.0 : cos_n));
        a2 = acos(h2);
        contrib = (sin(a2) - sin(a1)) * 0.5 + (a2 - a1) * cos_n;
        if (contrib > 0.0) ao += contrib;
    }
#undef WARP_SSAO_REC
    ao = 1.0 - ao / 4.0 * 2.0;
    return ao < 0.0 ? 0.0 : (ao > 1.0 ? 1.0 : ao);
}

TEST(ssao_sidecars_occlude_a_jittered_plane_and_blur_it) {
    enum { SW = 16, SH = 16, AW = 8, AH = 8 };
    static float depth[SW * SH];
    SSAOSystem ssao;
    Mat4 proj, inv;
    RHITextureDesc td;
    RHITexture dtex;
    RHICmdBuffer *cmd;
    unsigned char raw[AW * AH * 4], blur[AW * AH * 4];
    float plane_depth;
    int want[AW * AH];
    int frame, i, r, c, lo = 0, hi = 0, mid = 0;

    proj = mat4_perspective(1.04719755f, 1.0f, 0.5f, 20.0f);
    proj.e[2][0] = 0.3f;
    proj.e[2][1] = -0.15f;
    inv = mat4_inverse(proj);
    {
        float zc = proj.e[2][2] * -3.0f + proj.e[3][2];
        float wc = proj.e[2][3] * -3.0f;
        plane_depth = (zc / wc) * 0.5f + 0.5f;
    }
    for (i = 0; i < AW * AH; ++i) {
        double ao = warp_ssao_ref(&inv, plane_depth, i % AW, i / AW, AW, AH,
                                  (double)SW, (double)SH, 2.0, 0.9);
        want[i] = (int)floor(ao * 255.0 + 0.5);
        if (want[i] <= 3) ++lo;
        else if (want[i] >= 252) ++hi;
        else ++mid;
    }
    /* A degenerate expectation would prove nothing about the inputs. */
    ASSERT_TRUE(lo >= 4 && hi >= 2 && mid >= 24);

    memset(&td, 0, sizeof(td));
    td.width = SW; td.height = SH;
    td.format = RHI_FORMAT_R32_FLOAT; td.mip_levels = 1u;
    td.data = depth;

    ASSERT_TRUE(ssao_init(&ssao, g_dev, SW, SH));
    ASSERT_TRUE(ssao.ready);
    ASSERT_EQ(ssao.loc_inv_proj, 0);
    ASSERT_EQ(ssao.loc_screen_w, 64);
    ASSERT_EQ(ssao.loc_screen_h, 68);
    ASSERT_EQ(ssao.loc_radius, 72);
    ASSERT_EQ(ssao.loc_bias, 76);
    /* Declared but never read by ssao.frag, so GL drops it too. */
    ASSERT_EQ(ssao.loc_proj, -1);
    ssao.radius = 2.0f;
    ssao.bias = 0.9f;

    for (frame = 0; frame < 2; ++frame) {
        for (i = 0; i < SW * SH; ++i) depth[i] = frame == 0 ? plane_depth : 1.0f;
        dtex = rhi_texture_create(g_dev, &td);
        ASSERT_TRUE(rhi_handle_valid(dtex));

        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        ssao_apply(&ssao, cmd, dtex, &proj.e[0][0], &inv.e[0][0], SW, SH);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);

        memset(raw, 0, sizeof(raw));
        memset(blur, 0, sizeof(blur));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ssao.ssao_fbo.color_tex, raw, sizeof(raw)));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ssao_get_texture(&ssao), blur, sizeof(blur)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        for (i = 0; i < AW * AH; ++i) {
            if (frame == 1) {
                ASSERT_EQ(raw[i * 4 + 0], 255u);
                ASSERT_EQ(blur[i * 4 + 0], 255u);
                ASSERT_EQ(blur[i * 4 + 1], 255u);
                continue;
            }
            {
                int dv = (int)raw[i * 4 + 0] - want[i];
                if (dv < -3 || dv > 3)
                    printf("  ssao raw px (%d,%d) = %d, want %d\n",
                           i % AW, i / AW, (int)raw[i * 4 + 0], want[i]);
                ASSERT_TRUE(dv >= -3 && dv <= 3);
                ASSERT_EQ(raw[i * 4 + 1], 0u);
                ASSERT_EQ(raw[i * 4 + 3], 255u);
            }
        }
        if (frame == 0) {
            for (r = 2; r < AH - 2; ++r) {
                for (c = 2; c < AW - 2; ++c) {
                    double sum = 0.0, wsum = 0.0;
                    int x, y, wb, got;
                    for (y = -2; y <= 2; ++y) {
                        for (x = -2; x <= 2; ++x) {
                            double wgt = exp(-(double)(x * x + y * y) / 4.0);
                            sum += wgt * raw[((r + y) * AW + (c + x)) * 4] / 255.0;
                            wsum += wgt;
                        }
                    }
                    wb = (int)floor(sum / wsum * 255.0 + 0.5);
                    got = blur[(r * AW + c) * 4];
                    if (got < wb - 1 || got > wb + 1)
                        printf("  ssao blur px (%d,%d) = %d, want %d\n", c, r, got, wb);
                    ASSERT_TRUE(got >= wb - 1 && got <= wb + 1);
                    ASSERT_EQ(blur[(r * AW + c) * 4 + 1], (unsigned char)got);
                }
            }
        }
        rhi_texture_destroy(g_dev, dtex);
    }
    ssao_shutdown(&ssao);
}

/* R640: sharpen on D3D12, through the real SharpenSystem (same init failure
 * as SSAO before sharpen_hlsl.frag).
 *
 * Input: an 8x8 RGBA8 pattern with a vertical red edge (col < 4: 51, else
 * 204), a horizontal green edge (memory row < 4: 77, else 153) and one blue
 * spot (230 at col 2, row 5, else 26). sharpen_apply is called with the
 * input's own size, so the eight neighbour taps land exactly on texel
 * centres and the static sampler's filtering cannot change them. Expected
 * values are the shader formula computed per channel below:
 *   peak = -1 / (8 * strength + 1),  w = 1 + 4 * peak
 *   out  = max(e*w + 4*peak*(a+c+g+i) + peak*(b+d+f+h), 0) / max(w, 1e-5)
 *   out  = clamp(out, mn - rng/8, mx + rng/8), then max(out, 0)
 * with mn/mx/rng over the eight neighbours. strength 5.0 (peak = -1/41,
 * w = 37/41) on purpose: at the default-ish 0.6 the kernel overshoots so
 * far that the ringing clamp decides every edge pixel and strength never
 * reaches the output (reverse-verified: a sidecar that ignored strength
 * passed). At 5.0 the red edge's right column lands inside the clamp
 * window at 0.514, and the test also asserts that at least 12 samples are
 * changed by the unclamped kernel, so strength stays observable. Only the
 * 6x6 interior is asserted: border
 * taps go through D3D12's static WRAP sampler, not CLAMP_TO_EDGE (known
 * sampler limit), so the border legitimately differs from GL. The target is
 * RGBA16F; tolerance 0.004. */
static double warp_sharpen_in(int c, int r, int ch)
{
    if (ch == 0) return (c < 4 ? 51 : 204) / 255.0;
    if (ch == 1) return (r < 4 ? 77 : 153) / 255.0;
    return (c == 2 && r == 5 ? 230 : 26) / 255.0;
}

TEST(sharpen_sidecar_matches_the_cas_formula_on_interior_pixels) {
    enum { W = 8, H = 8 };
    static unsigned char img[W * H * 4];
    SharpenSystem sh;
    RHITextureDesc td;
    RHITexture src;
    RHICmdBuffer *cmd;
    u16 out[W * H * 4];
    const double strength = 5.0;
    int r, c, ch, changed = 0, unclamped = 0;

    for (r = 0; r < H; ++r)
        for (c = 0; c < W; ++c) {
            for (ch = 0; ch < 3; ++ch)
                img[(r * W + c) * 4 + ch] =
                    (unsigned char)floor(warp_sharpen_in(c, r, ch) * 255.0 + 0.5);
            img[(r * W + c) * 4 + 3] = 255u;
        }
    memset(&td, 0, sizeof(td));
    td.width = W; td.height = H;
    td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
    td.data = img;
    src = rhi_texture_create(g_dev, &td);
    ASSERT_TRUE(rhi_handle_valid(src));

    ASSERT_TRUE(sharpen_init(&sh, g_dev, W, H));
    ASSERT_TRUE(sh.ready);
    ASSERT_EQ(sh.loc_strength, 0);
    ASSERT_EQ(sh.loc_sw, 4);
    ASSERT_EQ(sh.loc_sh, 8);

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    sharpen_apply(&sh, cmd, src, (f32)strength, W, H);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, sh.fbo.color_tex, out, sizeof(out)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    for (r = 1; r < H - 1; ++r) {
        for (c = 1; c < W - 1; ++c) {
            for (ch = 0; ch < 3; ++ch) {
                double peak = -1.0 / (strength * 8.0 + 1.0);
                double w = 1.0 + 4.0 * peak;
                double nb[8], mn, mx, rng, corners, cross, e, v;
                float got;
                int k;
                nb[0] = warp_sharpen_in(c - 1, r - 1, ch);
                nb[1] = warp_sharpen_in(c,     r - 1, ch);
                nb[2] = warp_sharpen_in(c + 1, r - 1, ch);
                nb[3] = warp_sharpen_in(c - 1, r,     ch);
                nb[4] = warp_sharpen_in(c + 1, r,     ch);
                nb[5] = warp_sharpen_in(c - 1, r + 1, ch);
                nb[6] = warp_sharpen_in(c,     r + 1, ch);
                nb[7] = warp_sharpen_in(c + 1, r + 1, ch);
                e = warp_sharpen_in(c, r, ch);
                mn = mx = nb[0];
                for (k = 1; k < 8; ++k) {
                    if (nb[k] < mn) mn = nb[k];
                    if (nb[k] > mx) mx = nb[k];
                }
                rng = mx - mn;
                corners = nb[0] + nb[2] + nb[5] + nb[7];
                cross = nb[1] + nb[3] + nb[4] + nb[6];
                v = e * w + corners * 4.0 * peak + cross * peak;
                if (v < 0.0) v = 0.0;
                v /= (w > 1e-5 ? w : 1e-5);
                if (v >= mn - rng * 0.125 && v <= mx + rng * 0.125 &&
                    fabs(v - e) > 0.02) ++unclamped;
                if (v < mn - rng * 0.125) v = mn - rng * 0.125;
                if (v > mx + rng * 0.125) v = mx + rng * 0.125;
                if (v < 0.0) v = 0.0;
                if (fabs(v - e) > 0.02) ++changed;
                got = warp_half_to_float(out[(r * W + c) * 4 + ch]);
                if (fabs(got - v) > 0.004)
                    printf("  sharpen px (%d,%d) ch %d = %f, want %f\n", c, r, ch, got, v);
                ASSERT_TRUE(fabs(got - v) <= 0.004);
            }
        }
    }
    /* The pattern must exercise the kernel, not pass through, and enough of
     * it must escape the ringing clamp for strength to be observable. */
    ASSERT_TRUE(changed >= 20);
    ASSERT_TRUE(unclamped >= 12);

    sharpen_shutdown(&sh);
    rhi_texture_destroy(g_dev, src);
}

/* R640: god rays on D3D12, through the real GodRaysSystem (same init failure
 * as SSAO before god_rays_hlsl.frag).
 *
 * Scene: constant RGBA8 (51, 102, 153). Sun at uv (0.25, 0.7), intensity
 * 0.8. Two frames, each with a constant R32F depth, so no tap depends on
 * filtering:
 *   depth 1.0 (all sky): the sun is inside the frame, so the 32-step march
 *     never leaves [0,1] and every step counts:
 *       illum = 0.8 / 32 * sum_{i=0..31} (1 - i/32)^2
 *             = 0.8 / 32 * (32*33*65/6) / 1024 = 0.8 * 11440 / 32768
 *     and each pixel is scene * (1 + 2 * illum * mask) with
 *     mask = 1 - smoothstep(0, 0.8, |uv - sun|) at the pixel centre
 *     (memory row 0 = NDC y = -1, so uv.y = (row + 0.5) / 8). The sun is
 *     off-centre in both axes, so a sun_x/sun_y swap or a flipped uv moves
 *     the bright spot; the 153 channel peaks at 0.935, below the clamp.
 *   depth 0.5 (all occluded): illum = 0, output must equal the scene
 *     exactly. With t0/t1 swapped the scene would come from the R32F
 *     texture, (1.0, 0, 0) or (0.5, 0, 0), and fail both frames. */
TEST(god_rays_sidecar_scatters_sky_and_passes_occluded_scene) {
    enum { W = 8, H = 8 };
    static unsigned char scene[W * H * 4];
    static float depth[W * H];
    static const int base[3] = { 51, 102, 153 };
    GodRaysSystem gr;
    RHITextureDesc td;
    RHITexture stex, dtex;
    RHICmdBuffer *cmd;
    unsigned char px[W * H * 4];
    const double sun_x = 0.25, sun_y = 0.7, inten = 0.8;
    const double illum = inten * 11440.0 / 32768.0;
    int frame, i, ch, distinct_lo = 255, distinct_hi = 0;

    for (i = 0; i < W * H; ++i) {
        scene[i * 4 + 0] = (unsigned char)base[0];
        scene[i * 4 + 1] = (unsigned char)base[1];
        scene[i * 4 + 2] = (unsigned char)base[2];
        scene[i * 4 + 3] = 255u;
    }
    memset(&td, 0, sizeof(td));
    td.width = W; td.height = H;
    td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
    td.data = scene;
    stex = rhi_texture_create(g_dev, &td);
    ASSERT_TRUE(rhi_handle_valid(stex));

    ASSERT_TRUE(god_rays_init(&gr, g_dev, W, H));
    ASSERT_TRUE(gr.ready);
    ASSERT_EQ(gr.loc_sun_x, 0);
    ASSERT_EQ(gr.loc_sun_y, 4);
    ASSERT_EQ(gr.loc_intensity, 8);
    /* Declared but never read by god_rays.frag, so GL drops them too. */
    ASSERT_EQ(gr.loc_sw, -1);
    ASSERT_EQ(gr.loc_sh, -1);

    td.format = RHI_FORMAT_R32_FLOAT;
    td.data = depth;
    for (frame = 0; frame < 2; ++frame) {
        for (i = 0; i < W * H; ++i) depth[i] = frame == 0 ? 1.0f : 0.5f;
        dtex = rhi_texture_create(g_dev, &td);
        ASSERT_TRUE(rhi_handle_valid(dtex));

        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        god_rays_apply(&gr, cmd, stex, dtex, (f32)sun_x, (f32)sun_y, (f32)inten, W, H);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);
        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, gr.fbo.color_tex, px, sizeof(px)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

        for (i = 0; i < W * H; ++i) {
            double u = (i % W + 0.5) / W, v = (i / W + 0.5) / H;
            double dist = sqrt((u - sun_x) * (u - sun_x) + (v - sun_y) * (v - sun_y));
            double t = dist / 0.8, mask;
            if (t > 1.0) t = 1.0;
            mask = 1.0 - t * t * (3.0 - 2.0 * t);
            for (ch = 0; ch < 3; ++ch) {
                double c0 = base[ch] / 255.0;
                double val = frame == 0 ? c0 * (1.0 + 2.0 * illum * mask) : c0;
                int want = (int)floor((val > 1.0 ? 1.0 : val) * 255.0 + 0.5);
                int got = px[i * 4 + ch];
                if (got < want - 1 || got > want + 1)
                    printf("  god rays frame %d px (%d,%d) ch %d = %d, want %d\n",
                           frame, i % W, i / W, ch, got, want);
                ASSERT_TRUE(got >= want - 1 && got <= want + 1);
                if (frame == 0 && ch == 2) {
                    if (want < distinct_lo) distinct_lo = want;
                    if (want > distinct_hi) distinct_hi = want;
                }
            }
            ASSERT_EQ(px[i * 4 + 3], 255u);
        }
        rhi_texture_destroy(g_dev, dtex);
    }
    /* The sky frame must be a real gradient, not a near-constant boost. */
    ASSERT_TRUE(distinct_hi - distinct_lo >= 40);

    god_rays_shutdown(&gr);
    rhi_texture_destroy(g_dev, stex);
}

/* R641 helpers: an RGBA8 texture of one flat colour, and an R32F depth
 * texture whose left half is one value and right half another. */
static RHITexture r641_flat_rgba8(u32 w, u32 h, u8 r, u8 g, u8 b) {
    static u8 px[16 * 16 * 4];
    RHITextureDesc td;
    u32 i;
    for (i = 0; i < w * h; ++i) {
        px[i * 4 + 0] = r; px[i * 4 + 1] = g; px[i * 4 + 2] = b; px[i * 4 + 3] = 255;
    }
    memset(&td, 0, sizeof(td));
    td.width = w; td.height = h;
    td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
    td.data = px;
    return rhi_texture_create(g_dev, &td);
}
static RHITexture r641_depth_split(u32 w, u32 h, f32 left, f32 right) {
    static f32 d[16 * 16];
    RHITextureDesc td;
    u32 x, y;
    for (y = 0; y < h; ++y)
        for (x = 0; x < w; ++x) d[y * w + x] = x < w / 2 ? left : right;
    memset(&td, 0, sizeof(td));
    td.width = w; td.height = h;
    td.format = RHI_FORMAT_R32_FLOAT; td.mip_levels = 1u;
    td.data = d;
    return rhi_texture_create(g_dev, &td);
}

/* R641: cinematic on D3D12. Flat grey 128 input, aberration and grain 0, so
 * only the vignette acts: out = 128/255 * max(1 - |uv - 0.5|^2 * v, 0) with
 * uv the pixel centre. With v = 2 the corner pixel of an 8x8 target (uv =
 * 1/16) gets 1 - 2*(0.4375^2*2) = 0.234375 and the centre ring 0.984375, so
 * a vignette read from the wrong push slot, or a uv that is not the pixel
 * centre, moves every pixel by far more than the +-1 tolerance. */
TEST(cinematic_sidecar_applies_the_exact_vignette_without_grain) {
    CinematicSystem cine;
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO fbo;
    RHITexture src;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    int x, y;
    memset(&cine, 0, sizeof(cine));
    ASSERT_TRUE(cinematic_init(&cine, g_dev));
    ASSERT_EQ(cine.loc_aberration, 0);
    ASSERT_EQ(cine.loc_vignette, 4);
    ASSERT_EQ(cine.loc_grain, 8);
    ASSERT_EQ(cine.loc_screen_w, 16);
    cine.aberration = 0.0f; cine.vignette = 2.0f; cine.grain = 0.0f;
    src = r641_flat_rgba8(8u, 8u, 128, 128, 128);
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u;
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM; fd.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    ASSERT_TRUE(rhi_handle_valid(src) && rhi_handle_valid(fbo.fb));
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    cinematic_apply(&cine, cmd, src, 8u, 8u, 0.0f);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            double u = (x + 0.5) / 8.0 - 0.5, v = (y + 0.5) / 8.0 - 0.5;
            double vig = 1.0 - (u * u + v * v) * 2.0;
            int want = (int)floor(128.0 / 255.0 * (vig > 0 ? vig : 0) * 255.0 + 0.5);
            int got = px[(y * 8 + x) * 4 + 0];
            if (abs(got - want) > 1)
                printf("  cinematic px (%d,%d) = %d, want %d\n", x, y, got, want);
            ASSERT_TRUE(abs(got - want) <= 1);
            ASSERT_EQ(px[(y * 8 + x) * 4 + 0], px[(y * 8 + x) * 4 + 2]);
        }
    }
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_texture_destroy(g_dev, src);
    cinematic_shutdown(&cine);
}

/* R641: SSS on D3D12. Two passes (horizontal into blur_fbo, vertical into
 * fbo, mixed with the original by strength). First a flat 200 grey: any
 * blur of it is 200 again, so this pins the value path end to end. Then
 * vertical stripes, where the blur genuinely changes the value and the
 * depth split (left sky, right surface) decides which branch each pixel
 * takes; the expected image is the two passes replayed in double. */
TEST(sss_sidecars_blur_only_where_depth_is_continuous) {
    SSSSystem sss;
    RHITexture col, depth;
    RHICmdBuffer *cmd;
    u16 out[8 * 8 * 4];
    const f32 strength = 0.5f;
    int x, y;
    memset(&sss, 0, sizeof(sss));
    ASSERT_TRUE(sss_init(&sss, g_dev, 8u, 8u));
    ASSERT_EQ(sss.loc_strength, 0);
    ASSERT_EQ(sss.loc_max_dist, 12);
    ASSERT_EQ(sss.v_loc_strength, 0);
    col = r641_flat_rgba8(8u, 8u, 200, 200, 200);
    depth = r641_depth_split(8u, 8u, 1.0f, 0.5f);
    ASSERT_TRUE(rhi_handle_valid(col) && rhi_handle_valid(depth));
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    sss_apply(&sss, cmd, col, depth, strength, 0.05f, 8u, 8u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, sss.fbo.color_tex, out, sizeof(out)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    /* The colour and the original are the same flat 200 here, so both
     * branches give 200/255; this pins the value path, the next frame pins
     * the branch split. */
    for (y = 0; y < 8; ++y)
        for (x = 0; x < 8; ++x) {
            f32 r = warp_half_to_float(out[(y * 8 + x) * 4 + 0]);
            if (fabsf(r - 200.0f / 255.0f) > 0.004f)
                printf("  sss flat px (%d,%d) = %f\n", x, y, r);
            ASSERT_TRUE(fabsf(r - 200.0f / 255.0f) <= 0.004f);
        }
    rhi_texture_destroy(g_dev, col);

    /* Branch split. Vertical stripes (column x is 255 if x odd, else 40) so
     * a horizontal blur changes the value, and strength 1/12 so the kernel
     * radius is exactly one texel: every tap lands on a texel centre and the
     * linear sampler returns that texel. Both passes are replicated in
     * double precision below. Left half is sky (depth 1.0) -> the pixel is
     * the ORIGINAL; right half is surface (0.5) -> lerp(original, blurred,
     * strength), with taps across the sky boundary rejected by the depth
     * falloff. A swapped depth/colour unit, a vertical pass that reads the
     * wrong input, or a dropped falloff all move the surface pixels. */
    {
        static const double k[9][3] = {
            {0.020,0.020,0.020},{0.050,0.040,0.030},{0.100,0.070,0.050},
            {0.150,0.130,0.080},{0.160,0.160,0.120},{0.150,0.130,0.080},
            {0.100,0.070,0.050},{0.050,0.040,0.030},{0.020,0.020,0.020}
        };
        static u8 stripes[8 * 8 * 4];
        const double s2 = 1.0 / 12.0, maxd = 0.05;
        double colv[8], dep[8], h[8][3];
        RHITextureDesc td;
        RHITexture stex;
        int c, i, moved = 0;
        /* Surface columns 4..7 alternate 255/40; sky columns 0..3 are all
         * 255. So a surface pixel's taps that reach across into the sky only
         * stay out of the average because the depth falloff rejects them --
         * dropping the falloff pulls column 4 and 6 toward 255. */
        for (x = 0; x < 8; ++x) {
            colv[x] = ((x < 4 || (x & 1)) ? 255.0 : 40.0) / 255.0;
            dep[x] = x < 4 ? 1.0 : 0.5;
        }
        for (y = 0; y < 8; ++y)
            for (x = 0; x < 8; ++x) {
                u8 v = (x < 4 || (x & 1)) ? 255 : 40;
                stripes[(y * 8 + x) * 4 + 0] = v; stripes[(y * 8 + x) * 4 + 1] = v;
                stripes[(y * 8 + x) * 4 + 2] = v; stripes[(y * 8 + x) * 4 + 3] = 255;
            }
        memset(&td, 0, sizeof(td));
        td.width = 8u; td.height = 8u;
        td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
        td.data = stripes;
        stex = rhi_texture_create(g_dev, &td);
        ASSERT_TRUE(rhi_handle_valid(stex));
        for (x = 0; x < 8; ++x) {
            for (c = 0; c < 3; ++c) {
                double sum = 0.0, tw = 0.0;
                if (dep[x] >= 1.0) { h[x][c] = colv[x]; continue; }
                for (i = -4; i <= 4; ++i) {
                    int sx = x + i;
                    double dd, t, fall, w;
                    if (sx < 0 || sx > 7) continue;
                    dd = fabs(dep[sx] - dep[x]);
                    t = dd / maxd; if (t > 1) t = 1;
                    fall = 1.0 - t * t * (3.0 - 2.0 * t);
                    w = k[i + 4][c] * fall;
                    sum += colv[sx] * w; tw += w;
                }
                h[x][c] = sum / (tw > 0.001 ? tw : 0.001);
            }
        }
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        sss_apply(&sss, cmd, stex, depth, (f32)s2, (f32)maxd, 8u, 8u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        memset(out, 0, sizeof(out));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, sss.fbo.color_tex, out, sizeof(out)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
        for (y = 0; y < 8; ++y)
            for (x = 0; x < 8; ++x)
                for (c = 0; c < 3; ++c) {
                    /* Vertical pass over a column that is constant in y
                     * returns h[x] (its weights normalise), so the result
                     * is lerp(original, h, strength). */
                    double want = dep[x] >= 1.0 ? colv[x]
                                  : colv[x] + (h[x][c] - colv[x]) * s2;
                    double got = warp_half_to_float(out[(y * 8 + x) * 4 + c]);
                    if (fabs(got - want) > 0.004)
                        printf("  sss stripes px (%d,%d) ch %d = %f, want %f\n",
                               x, y, c, got, want);
                    ASSERT_TRUE(fabs(got - want) <= 0.004);
                    if (fabs(want - colv[x]) > 0.01) moved++;
                }
        /* The surface half must actually be blurred, or this proves nothing. */
        ASSERT_TRUE(moved >= 8 * 2 * 3);
        rhi_texture_destroy(g_dev, stex);
    }
    rhi_texture_destroy(g_dev, depth);
    sss_shutdown(&sss);
}

/* R641: upscale (TSR) on D3D12: the first frame with no history, then a
 * second frame whose output is a known mix of history and current input.
 * Also pins the push layout the sidecar declares. */
TEST(upscale_sidecar_copies_flat_input_and_clips_history) {
    UpscaleSystem ups;
    RHITexture src, depth;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    int i;
    memset(&ups, 0, sizeof(ups));
    ASSERT_TRUE(upscale_init(&ups, g_dev, 8u, 8u, 8u, 8u));
    ASSERT_EQ(ups.loc_inv_proj, 0);
    ASSERT_EQ(ups.loc_prev_vp, 64);
    ASSERT_EQ(ups.loc_rw, 128);
    ASSERT_EQ(ups.loc_copy_only, 140);
    ASSERT_EQ(ups.loc_first_frame, 144);
    ASSERT_EQ(ups.loc_dw, -1);   /* declared, never read by upscale.frag */
    src = r641_flat_rgba8(8u, 8u, 90, 140, 210);
    depth = r641_depth_split(8u, 8u, 0.5f, 0.5f);
    ASSERT_TRUE(rhi_handle_valid(src) && rhi_handle_valid(depth));
    /* Frame 0: first frame, flat input. Catmull-Rom at a texel centre with
     * render == display size has weights (0,1,0,0) per axis, and the 5-tap
     * sharpener on a flat field adds 4c - 4c = 0, so the output is the
     * input. Before the R641 weight fix this was 255 in every channel. */
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    upscale_apply(&ups, cmd, src, depth, identity, identity, 0.3f, 8u, 8u, 8u, 8u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ups.fbo.color_tex, px, sizeof(px)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    for (i = 0; i < 64; ++i) {
        if (abs(px[i * 4 + 0] - 90) > 1 || abs(px[i * 4 + 1] - 140) > 1 ||
            abs(px[i * 4 + 2] - 210) > 1)
            printf("  upscale frame 0 px %d = %u,%u,%u\n", i,
                   px[i * 4 + 0], px[i * 4 + 1], px[i * 4 + 2]);
        ASSERT_TRUE(abs(px[i * 4 + 0] - 90) <= 1);
        ASSERT_TRUE(abs(px[i * 4 + 1] - 140) <= 1);
        ASSERT_TRUE(abs(px[i * 4 + 2] - 210) <= 1);
    }
    ASSERT_FALSE(ups.first_frame);

    /* Frame 1: history on. Identity inv_proj / prev_vp reproject every pixel
     * onto itself, so history is frame 0's (90,140,210). The input becomes
     * vertical grey stripes 40 / 220 with sharpness 0, so the upscaled value
     * is the stripe itself, and each pixel's 4-neighbourhood spans both
     * stripes (left/right differ, up/down match) -- the history value lies
     * inside that AABB in every channel and survives clip_aabb unchanged.
     * The output is therefore 0.85 * history + 0.15 * stripe, which is
     * nowhere near the input: a wrong history unit, a broken copy-only
     * pass 0 -> history, or a reprojection that falls outside [0,1] (no
     * history mix at all) each give a different value. */
    {
        static u8 stripes[8 * 8 * 4];
        static const int hist[3] = { 90, 140, 210 };
        RHITextureDesc td;
        RHITexture stex;
        int x, y, c;
        for (y = 0; y < 8; ++y)
            for (x = 0; x < 8; ++x) {
                u8 v = (x & 1) ? 220 : 40;
                stripes[(y * 8 + x) * 4 + 0] = v; stripes[(y * 8 + x) * 4 + 1] = v;
                stripes[(y * 8 + x) * 4 + 2] = v; stripes[(y * 8 + x) * 4 + 3] = 255;
            }
        memset(&td, 0, sizeof(td));
        td.width = 8u; td.height = 8u;
        td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
        td.data = stripes;
        stex = rhi_texture_create(g_dev, &td);
        ASSERT_TRUE(rhi_handle_valid(stex));
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        upscale_apply(&ups, cmd, stex, depth, identity, identity, 0.0f, 8u, 8u, 8u, 8u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ups.fbo.color_tex, px, sizeof(px)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
        for (y = 0; y < 8; ++y)
            for (x = 0; x < 8; ++x)
                for (c = 0; c < 3; ++c) {
                    int stripe = (x & 1) ? 220 : 40;
                    int want = (int)floor(0.85 * hist[c] + 0.15 * stripe + 0.5);
                    int got = px[(y * 8 + x) * 4 + c];
                    if (abs(got - want) > 1)
                        printf("  upscale frame 1 px (%d,%d) ch %d = %d, want %d\n",
                               x, y, c, got, want);
                    ASSERT_TRUE(abs(got - want) <= 1);
                }
        rhi_texture_destroy(g_dev, stex);
    }
    rhi_texture_destroy(g_dev, depth);
    rhi_texture_destroy(g_dev, src);
    upscale_shutdown(&ups);
}

/* R641: volumetric on D3D12, checked against the shader's own march done in
 * double precision. Identity matrices make view space == clip space, so for
 * a window depth d the ray end is (ndc.x, ndc.y, 2d - 1) and world_y is the
 * view y. The light direction (0,0,1) points straight at the camera, so
 * light_amount = max(dot(-ray_dir, (0,0,1)), 0) depends on the per-pixel ray.
 * Shadow is 1 (lit). Every quantity in the march -- ray length, height
 * falloff, transmittance, in-scatter -- is reproduced below, so a transposed
 * inv_view (world_y from the wrong row), a wrong depth decode, a swapped
 * texture unit or a mis-offset push member all land outside +-1. */
TEST(volumetric_sidecar_extincts_the_scene_by_the_marched_fog) {
    VolumetricSystem vol;
    RHITexture depth, shadow, scene;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    /* Camera 2 units up: view = translate(0,-2,0), column-major, so the CPU
     * inverse handed to the shader as u_vol_inv_view translates by +2 and
     * world_y = view_y + 2. Rotation-free, so light_dir in view space is
     * unchanged. With an identity view a transposed inv_view read would be
     * invisible; here it moves the +2 out of the y row. */
    static const float cam_up_view[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,-2,0,1 };
    const f32 ldir[3] = { 0.0f, 0.0f, 1.0f };
    const f32 lcol[3] = { 1.0f, 0.5f, 0.25f };
    const double fog[3] = { 0.2, 0.3, 0.4 };
    const double sc[3] = { 200.0 / 255.0, 100.0 / 255.0, 50.0 / 255.0 };
    const double dval = 0.2;
    int x, y, c;
    memset(&vol, 0, sizeof(vol));
    ASSERT_TRUE(volumetric_init(&vol, g_dev, 8u, 8u));
    ASSERT_EQ(vol.loc_inv_proj, 0);
    ASSERT_EQ(vol.loc_view, 64);
    ASSERT_EQ(vol.loc_inv_view, 128);
    ASSERT_EQ(vol.loc_ldx, 192);
    ASSERT_EQ(vol.loc_fog_density, 216);
    ASSERT_EQ(vol.loc_fog_color_b, 228);
    vol.fog_density = 0.3f;
    vol.fog_color[0] = (f32)fog[0]; vol.fog_color[1] = (f32)fog[1];
    vol.fog_color[2] = (f32)fog[2];
    depth = r641_depth_split(8u, 8u, (f32)dval, (f32)dval);
    shadow = r641_depth_split(8u, 8u, 1.0f, 1.0f);
    scene = r641_flat_rgba8(8u, 8u, 200, 100, 50);
    ASSERT_TRUE(rhi_handle_valid(depth) && rhi_handle_valid(shadow) &&
                rhi_handle_valid(scene));
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    volumetric_apply(&vol, cmd, depth, shadow, scene, identity, cam_up_view,
                     ldir, lcol, 8u, 8u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, volumetric_get_texture(&vol), px, sizeof(px)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            /* GL row order offscreen: memory row 0 is uv.y = 1/16. */
            double u = (x + 0.5) / 8.0, v = (y + 0.5) / 8.0;
            double ex = u * 2 - 1, ey = v * 2 - 1, ez = dval * 2 - 1;
            double len = sqrt(ex * ex + ey * ey + ez * ez);
            double dz = ez / len;
            double light_amount = -dz > 0 ? -dz : 0;
            double step = len / 16.0, trans = 1.0, accum[3] = { 0, 0, 0 };
            double lighting[3];
            int i;
            for (c = 0; c < 3; ++c)
                lighting[c] = fog[c] * 0.3 + lcol[c] * light_amount * 1.0;
            for (i = 0; i < 16; ++i) {
                double t = (i + 0.5) * step;
                double wy = (ey / len) * t + 2.0;
                double dens = 0.3 * exp(-wy * 0.3);
                double amt;
                if (dens < 0.0001) continue;
                amt = dens * step;
                for (c = 0; c < 3; ++c) accum[c] += lighting[c] * trans * amt;
                trans *= 1.0 - amt;
                if (trans < 0) trans = 0;
            }
            for (c = 0; c < 3; ++c) {
                double o = sc[c] * trans + accum[c];
                int want = (int)floor((o > 1 ? 1 : o) * 255.0 + 0.5);
                int got = px[(y * 8 + x) * 4 + c];
                if (abs(got - want) > 1)
                    printf("  volumetric px (%d,%d) ch %d = %d, want %d\n", x, y, c, got, want);
                ASSERT_TRUE(abs(got - want) <= 1);
            }
        }
    }
    rhi_texture_destroy(g_dev, scene);
    rhi_texture_destroy(g_dev, shadow);
    rhi_texture_destroy(g_dev, depth);
    volumetric_shutdown(&vol);
}

/* R642: debug_viz on D3D12, all five modes. The colour input is a flat
 * (200,100,50) and the depth a ramp in both axes, so every mode has an
 * exact closed form: 0 passes the colour, 3 its red channel, 1 the
 * linearised depth as a blue->red ramp, 4 the cascade colour picked by the
 * splits, 2 the depth-derived normal. Taps are whole texels from the pixel
 * centre (texture and target are both 8x8), so the linear sampler returns
 * texel values; mode 2 reads the +x / +y neighbour and is only checked
 * where that neighbour exists (the static WRAP sampler would wrap the last
 * row/column, GL's CLAMP would not). */
static double r642_dv_depth(int c, int r) { return 0.1 + 0.08 * c + 0.03 * r; }

TEST(debug_viz_sidecar_renders_every_mode_from_the_shader_formulas) {
    DebugVizSystem dv;
    RHITexture col, depth;
    RHITextureDesc td;
    RHICmdBuffer *cmd;
    static f32 dpx[8 * 8];
    unsigned char px[8 * 8 * 4];
    static const f32 splits[5] = { 0.0f, 0.8f, 1.2f, 1.8f, 100.0f };
    static const double casc[4][3] = {
        { 1.0, 0.2, 0.2 }, { 0.2, 1.0, 0.2 }, { 0.2, 0.4, 1.0 }, { 1.0, 1.0, 0.2 }
    };
    const double n = 0.5, f = 10.0;
    int mode, x, y, c, seen[4] = { 0, 0, 0, 0 };
    memset(&dv, 0, sizeof(dv));
    ASSERT_TRUE(debug_viz_init(&dv, g_dev, 8u, 8u));
    ASSERT_EQ(dv.loc_mode, 0);
    ASSERT_EQ(dv.loc_near, 4);
    ASSERT_EQ(dv.loc_far, 8);
    ASSERT_EQ(dv.loc_split0, 12);
    ASSERT_EQ(dv.loc_split3, 24);
    for (y = 0; y < 8; ++y)
        for (x = 0; x < 8; ++x) dpx[y * 8 + x] = (f32)r642_dv_depth(x, y);
    memset(&td, 0, sizeof(td));
    td.width = 8u; td.height = 8u;
    td.format = RHI_FORMAT_R32_FLOAT; td.mip_levels = 1u;
    td.data = dpx;
    depth = rhi_texture_create(g_dev, &td);
    col = r641_flat_rgba8(8u, 8u, 200, 100, 50);
    ASSERT_TRUE(rhi_handle_valid(col) && rhi_handle_valid(depth));
    for (mode = 0; mode < 5; ++mode) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        debug_viz_apply(&dv, cmd, col, depth, mode, (f32)n, (f32)f, splits, 8u, 8u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, dv.fbo.color_tex, px, sizeof(px)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
        for (y = 0; y < 8; ++y) {
            for (x = 0; x < 8; ++x) {
                double want[3];
                double d = r642_dv_depth(x, y);
                double lin = n * f / (f - d * (f - n));
                if (mode == 2 && (x == 7 || y == 7)) continue;
                if (mode == 0) {
                    want[0] = 200 / 255.0; want[1] = 100 / 255.0; want[2] = 50 / 255.0;
                } else if (mode == 3) {
                    want[0] = want[1] = want[2] = 200 / 255.0;
                } else if (mode == 1) {
                    double v = lin / f;
                    v = v < 0 ? 0 : (v > 1 ? 1 : v);
                    want[0] = v; want[1] = 0; want[2] = 1 - v;
                } else if (mode == 4) {
                    int k = 3, i;
                    for (i = 0; i < 4; ++i)
                        if (lin < splits[i + 1]) { k = i; break; }
                    seen[k]++;
                    for (c = 0; c < 3; ++c) want[c] = casc[k][c];
                } else {
                    double a = 2.0 / 8.0, bx = 2.0 * (r642_dv_depth(x + 1, y) - d);
                    double by = 2.0 * (r642_dv_depth(x, y + 1) - d);
                    /* cross((a,0,bx), (0,a,by)) */
                    double nx = 0.0 * by - bx * a, ny = bx * 0.0 - a * by, nz = a * a;
                    double len = sqrt(nx * nx + ny * ny + nz * nz);
                    want[0] = nx / len * 0.5 + 0.5;
                    want[1] = ny / len * 0.5 + 0.5;
                    want[2] = nz / len * 0.5 + 0.5;
                }
                for (c = 0; c < 3; ++c) {
                    int w = (int)floor(want[c] * 255.0 + 0.5);
                    int got = px[(y * 8 + x) * 4 + c];
                    if (abs(got - w) > 1)
                        printf("  debug viz mode %d px (%d,%d) ch %d = %d, want %d\n",
                               mode, x, y, c, got, w);
                    ASSERT_TRUE(abs(got - w) <= 1);
                }
            }
        }
    }
    /* The depth ramp must reach all four cascades, or mode 4 proved little. */
    for (c = 0; c < 4; ++c) ASSERT_TRUE(seen[c] > 0);
    rhi_texture_destroy(g_dev, col);
    rhi_texture_destroy(g_dev, depth);
    debug_viz_shutdown(&dv);
}

/* R642: CombinedColor (tonemap + grade + cinematic in one pass) on D3D12,
 * against a double-precision replay of combined_color.frag. Flat input, so
 * the aberration taps all read the same texel; grain 0 (the hash is chaotic
 * in float and not reproducible in double). One frame per tonemap mode:
 * ACES and AgX with a 0.75 adapted luminance (auto exposure 0.8, blended
 * 0.8 into the manual 1.5 -> 0.94), Khronos-neutral with 0.005 (< 0.01, so
 * the manual exposure is used as is). The first two go through the
 * auto-exposure material binder, the third through the multi-bind arm, so
 * both of combined_color_apply's bind paths have to put the luminance on
 * t1. The vignette varies per pixel, so a wrong uv moves the result too. */
static double r642_cl(double v) { return v < 0 ? 0 : (v > 1 ? 1 : v); }

static void r642_mat3_cols(const double a[9], const double v[3], double o[3]) {
    int j;
    for (j = 0; j < 3; ++j)
        o[j] = v[0] * a[3 * j] + v[1] * a[3 * j + 1] + v[2] * a[3 * j + 2];
}

static void r642_tonemap(int mode, const double in[3], double out[3]) {
    static const double inset[9] = {
        0.84247906, 0.04232824, 0.04237565,
        0.07843371, 0.87846855, 0.07843397,
        0.07922376, 0.07916613, 0.87923044 };
    static const double outset[9] = {
        1.1968790, -0.0525374, -0.0525374,
        -0.0920852, 1.1515179, -0.0920852,
        -0.0398265, -0.0398265, 1.1637448 };
    int c;
    if (mode == 1) {
        double v[3], t[3];
        for (c = 0; c < 3; ++c) v[c] = in[c] > 0 ? in[c] : 0;
        r642_mat3_cols(inset, v, t);
        for (c = 0; c < 3; ++c) {
            double s = r642_cl(t[c]);
            s = log(s + 0.0001) / log(2.0);
            s = r642_cl((s * 1.7 + 6.5) / 11.7);
            v[c] = s * s * (3.0 - 2.0 * s);
        }
        r642_mat3_cols(outset, v, t);
        for (c = 0; c < 3; ++c) out[c] = r642_cl(t[c]);
    } else {
        for (c = 0; c < 3; ++c) {
            double x = mode == 2 ? (in[c] > 0 ? in[c] : 0) : in[c];
            out[c] = r642_cl(x * (2.51 * x + 0.03) / (x * (2.43 * x + 0.59) + 0.14));
        }
    }
}

TEST(combined_color_sidecar_matches_the_fused_tonemap_grade_vignette) {
    CombinedColor cc;
    RHITexture hdr, lum_hi, lum_lo;
    RHICmdBuffer *cmd;
    u16 out[8 * 8 * 4];
    const double src[3] = { 200 / 255.0, 100 / 255.0, 50 / 255.0 };
    const double e = 1.5, gam = 2.2, sat = 1.3, con = 1.1, bri = 0.95;
    const double temp = 0.4, tint = 0.6, vig = 1.5;
    int mode, x, y, c;
    memset(&cc, 0, sizeof(cc));
    ASSERT_TRUE(combined_color_init(&cc, g_dev, 8u, 8u));
    ASSERT_TRUE(cc.use_combined);
    ASSERT_EQ(cc.loc_exposure, 0);
    ASSERT_EQ(cc.loc_mode, 8);
    ASSERT_EQ(cc.loc_saturation, 12);
    ASSERT_EQ(cc.loc_tint, 28);
    ASSERT_EQ(cc.loc_aberration, 32);
    ASSERT_EQ(cc.loc_grain, 40);
    ASSERT_EQ(cc.loc_screen_h, 52);
    hdr = r641_flat_rgba8(8u, 8u, 200, 100, 50);
    lum_hi = r641_depth_split(1u, 1u, 0.75f, 0.75f);
    lum_lo = r641_depth_split(1u, 1u, 0.005f, 0.005f);
    ASSERT_TRUE(rhi_handle_valid(hdr) && rhi_handle_valid(lum_hi) &&
                rhi_handle_valid(lum_lo));
    for (mode = 0; mode < 3; ++mode) {
        double exposure, ldr[3], h[3], luma;
        double scene_luma = mode == 2 ? 0.005 : 0.75;
        double auto_exp = scene_luma > 0.01 ? 1.0 / (scene_luma + 0.5) : e;
        exposure = e + (auto_exp - e) * 0.8;
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        combined_color_apply(&cc, cmd, hdr, mode == 2 ? lum_lo : lum_hi,
                             mode != 2, (f32)e, (f32)gam, mode,
                             (f32)sat, (f32)con, (f32)bri, (f32)temp, (f32)tint,
                             2.0f, (f32)vig, 0.0f, 0.0f, 8u, 8u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        memset(out, 0, sizeof(out));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, cc.output_fbo.color_tex,
                                            out, sizeof(out)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
        for (c = 0; c < 3; ++c) h[c] = src[c] * exposure;
        r642_tonemap(mode, h, ldr);
        for (c = 0; c < 3; ++c) ldr[c] = ldr[c] > 0 ? pow(ldr[c], 1.0 / gam) : 0;
        luma = ldr[0] * 0.2126 + ldr[1] * 0.7152 + ldr[2] * 0.0722;
        {
            const double warm[3] = { 1.0, 0.85, 0.7 }, cool[3] = { 0.7, 0.85, 1.0 };
            double k = temp * 0.5 + 0.5;
            for (c = 0; c < 3; ++c) {
                ldr[c] = luma + (ldr[c] - luma) * sat;
                ldr[c] = (ldr[c] - 0.5) * con + 0.5;
                ldr[c] *= bri;
                ldr[c] *= cool[c] + (warm[c] - cool[c]) * k;
            }
            ldr[1] += tint * 0.05;
        }
        for (y = 0; y < 8; ++y) {
            for (x = 0; x < 8; ++x) {
                double du = (x + 0.5) / 8.0 - 0.5, dvv = (y + 0.5) / 8.0 - 0.5;
                double v = 1.0 - (du * du + dvv * dvv) * vig;
                if (v < 0) v = 0;
                for (c = 0; c < 3; ++c) {
                    double want = r642_cl(ldr[c] * v);
                    float got = warp_half_to_float(out[(y * 8 + x) * 4 + c]);
                    if (fabs(got - want) > 0.004)
                        printf("  combined colour mode %d px (%d,%d) ch %d = %f, want %f\n",
                               mode, x, y, c, got, want);
                    ASSERT_TRUE(fabs(got - want) <= 0.004);
                }
            }
        }
    }
    rhi_texture_destroy(g_dev, hdr);
    rhi_texture_destroy(g_dev, lum_hi);
    rhi_texture_destroy(g_dev, lum_lo);
    combined_color_shutdown(&cc);
}

/* R642: CombinedAA (TAA resolve + FXAA in one pass) on D3D12. Four frames
 * through the real history ping-pong:
 *   F0  first frame, flat (90,140,210): FXAA early-outs (no contrast), no
 *       history -> the input comes back.
 *   F1  checkerboard 0/255. FXAA's contrast test looks only at the centre and
 *       the diagonals, which on a checkerboard are all the same colour, so
 *       aa_color is the centre; the 3x3 box spans [0,1], so F0's flat
 *       history survives clip_aabb and out = 0.9*hist + 0.1*curr.
 *   F2  same input, prev_vp = translate(+0.5 NDC x): prev_uv = uv + 2 texels,
 *       so columns 0..5 blend with F1's output two columns to the right and
 *       columns 6..7 fall off the history (out = curr). A transposed
 *       prev_vp read moves the shift into w and breaks both.
 *   F3  first_frame forced again with a horizontal edge whose bright side is
 *       a ramp 64..255 (starting at 64, not 0, so no pixel hits FXAA's
 *       0/0 distA+distB on the wrapped border): out must match a double replay of the FXAA math (bilinear,
 *       WRAP) and the standalone FXAA sidecar. A plain box is not enough
 *       here: none of its blended pixels reaches the end-search branch, so
 *       a broken posB tap passed; on the ramp edge it moves 15 pixels. */
/* R642: double replay of the FXAA half of combined_taa_fxaa.frag on an 8x8
 * grey image, bilinear with WRAP addressing (the D3D12 static sampler), so
 * the half-texel end-search taps (posA / posB) are reproduced exactly. */
static const u8 *r642_img;
static double r642_tex(int x, int y) {
    x = ((x % 8) + 8) % 8; y = ((y % 8) + 8) % 8;
    return r642_img[(y * 8 + x) * 4] / 255.0;
}
static double r642_bilin(double u, double v) {
    double fx = u * 8.0 - 0.5, fy = v * 8.0 - 0.5;
    int x0 = (int)floor(fx), y0 = (int)floor(fy);
    double ax = fx - x0, ay = fy - y0;
    return (r642_tex(x0, y0) * (1 - ax) + r642_tex(x0 + 1, y0) * ax) * (1 - ay) +
           (r642_tex(x0, y0 + 1) * (1 - ax) + r642_tex(x0 + 1, y0 + 1) * ax) * ay;
}
static double r642_fxaa(double u, double v) {
    const double t = 1.0 / 8.0;
    double M = r642_bilin(u, v), N = r642_bilin(u, v - t), S = r642_bilin(u, v + t);
    double W = r642_bilin(u - t, v), E = r642_bilin(u + t, v);
    double NW = r642_bilin(u - t, v - t), NE = r642_bilin(u + t, v - t);
    double SW = r642_bilin(u - t, v + t), SE = r642_bilin(u + t, v + t);
    double mn = fmin(M, fmin(fmin(NW, NE), fmin(SW, SE)));
    double mx = fmax(M, fmax(fmax(NW, NE), fmax(SW, SE)));
    double ev, eh, p1, p2, l1, l2, g1, g2, gs, avg, pos, ua, va, ub, vb, da, db, blend;
    int horiz, is1;
    /* Grey input: dot(c, LUMA) = c because LUMA sums to 1. */
    if (mx - mn < fmax(0.0312, mx * 0.125)) return M;
    ev = fabs(N + S - 2 * M) * 2 + fabs(NW + SW - 2 * N) + fabs(NE + SE - 2 * S);
    eh = fabs(W + E - 2 * M) * 2 + fabs(NW + NE - 2 * W) + fabs(SW + SE - 2 * E);
    horiz = eh >= ev;
    p1 = t; p2 = t;
    l1 = horiz ? N : W; l2 = horiz ? S : E;
    g1 = fabs(l1 - M); g2 = fabs(l2 - M);
    is1 = g1 >= g2;
    gs = fmax(g1, g2) * 0.25;
    avg = is1 ? (l1 + M) * 0.5 : (l2 + M) * 0.5;
    pos = is1 ? -p1 : p1;
    ua = ub = u; va = vb = v;
    if (horiz) { va += pos; vb += pos; ua -= p2 * 0.5; ub += p2 * 0.5; }
    else       { ua += pos; ub += pos; va -= p2 * 0.5; vb += p2 * 0.5; }
    da = fabs(r642_bilin(ua, va) - avg);
    db = fabs(r642_bilin(ub, vb) - avg);
    if (da < gs && db < gs) blend = 0.5 - 0.5 * (pos / p1);
    else blend = da < db ? -0.5 + 0.5 * (da / (da + db)) : 0.5 - 0.5 * (db / (da + db));
    if (horiz) v += blend * p1; else u += blend * p1;
    return r642_bilin(u, v);
}

static RHITexture r642_rgba8(const u8 *px) {
    RHITextureDesc td;
    memset(&td, 0, sizeof(td));
    td.width = 8u; td.height = 8u;
    td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
    td.data = px;
    return rhi_texture_create(g_dev, &td);
}

TEST(combined_aa_sidecar_reprojects_history_and_matches_fxaa) {
    CombinedAA caa;
    FXAASystem fx;
    RHITexture flat, checker, box, depth, fx_out;
    RHICmdBuffer *cmd;
    static u8 chk[8 * 8 * 4], bx[8 * 8 * 4];
    static u16 f1[8 * 8 * 4], out[8 * 8 * 4], ref[8 * 8 * 4];
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    static const float shift[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0.5f,0,0,1 };
    const double fl[3] = { 90 / 255.0, 140 / 255.0, 210 / 255.0 };
    int frame, x, y, c, i, blended = 0;
    for (y = 0; y < 8; ++y)
        for (x = 0; x < 8; ++x) {
            u8 v = ((x + y) & 1) ? 255u : 0u;
            u8 b = y >= 4 ? (u8)floor(64.0 + 191.0 * x / 7.0 + 0.5) : 0u;
            i = (y * 8 + x) * 4;
            chk[i] = chk[i + 1] = chk[i + 2] = v; chk[i + 3] = 255u;
            bx[i] = bx[i + 1] = bx[i + 2] = b; bx[i + 3] = 255u;
        }
    memset(&caa, 0, sizeof(caa));
    ASSERT_TRUE(combined_aa_init(&caa, g_dev, 8u, 8u));
    ASSERT_TRUE(caa.use_combined);
    ASSERT_EQ(caa.loc_curr_vp, -1);
    ASSERT_EQ(caa.loc_prev_vp, 0);
    ASSERT_EQ(caa.loc_inv_proj, 64);
    ASSERT_EQ(caa.loc_screen_w, 128);
    ASSERT_EQ(caa.loc_taa_first_frame, 136);
    ASSERT_EQ(caa.loc_use_velocity, 140);
    ASSERT_EQ(caa.loc_taa_blend, -1);
    ASSERT_EQ(caa.loc_fxaa_threshold, -1);
    flat = r641_flat_rgba8(8u, 8u, 90, 140, 210);
    checker = r642_rgba8(chk);
    box = r642_rgba8(bx);
    depth = r641_depth_split(8u, 8u, 0.5f, 0.5f);
    ASSERT_TRUE(rhi_handle_valid(flat) && rhi_handle_valid(checker) &&
                rhi_handle_valid(box) && rhi_handle_valid(depth));
    for (frame = 0; frame < 4; ++frame) {
        RHITexture in = frame == 0 ? flat : (frame == 3 ? box : checker);
        if (frame == 3) caa.first_frame = true;
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        combined_aa_apply(&caa, cmd, in, depth, RHI_HANDLE_NULL, identity,
                          frame == 2 ? shift : identity, identity, 8u, 8u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        memset(out, 0, sizeof(out));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, combined_aa_get_output(&caa),
                                            out, sizeof(out)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
        if (frame == 3) break;
        for (y = 0; y < 8; ++y) {
            for (x = 0; x < 8; ++x) {
                double cur = ((x + y) & 1) ? 1.0 : 0.0;
                for (c = 0; c < 3; ++c) {
                    double want;
                    float got = warp_half_to_float(out[(y * 8 + x) * 4 + c]);
                    if (frame == 0) want = fl[c];
                    else if (frame == 1) want = 0.9 * fl[c] + 0.1 * cur;
                    else if (x >= 6) want = cur;
                    else want = 0.9 * warp_half_to_float(f1[(y * 8 + x + 2) * 4 + c]) +
                                0.1 * cur;
                    if (fabs(got - want) > 0.003)
                        printf("  combined aa frame %d px (%d,%d) ch %d = %f, want %f\n",
                               frame, x, y, c, got, want);
                    ASSERT_TRUE(fabs(got - want) <= 0.003);
                }
            }
        }
        if (frame == 1) memcpy(f1, out, sizeof(f1));
    }

    memset(&fx, 0, sizeof(fx));
    ASSERT_TRUE(fxaa_init(&fx, g_dev, 8u, 8u));
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    fxaa_apply(&fx, cmd, box, 8u, 8u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    fx_out = fxaa_get_texture(&fx);
    memset(ref, 0, sizeof(ref));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fx_out, ref, sizeof(ref)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    r642_img = bx;
    for (i = 0; i < 8 * 8; ++i) {
        float got = warp_half_to_float(out[i * 4]);
        float want = warp_half_to_float(ref[i * 4]);
        double model = r642_fxaa((i % 8 + 0.5) / 8.0, (i / 8 + 0.5) / 8.0);
        if (fabsf(got - want) > 0.002f || fabs(got - model) > 0.006)
            printf("  combined aa fxaa px %d = %f, fxaa sidecar %f, model %f\n",
                   i, got, want, model);
        ASSERT_TRUE(fabsf(got - want) <= 0.002f);
        ASSERT_TRUE(fabs(got - model) <= 0.006);
        if (fabsf(got - bx[i * 4] / 255.0f) > 0.02f) blended++;
    }
    if (blended < 8) printf("  combined aa fxaa blended only %d pixels\n", blended);
    ASSERT_TRUE(blended >= 8);
    fxaa_shutdown(&fx);
    rhi_texture_destroy(g_dev, flat);
    rhi_texture_destroy(g_dev, checker);
    rhi_texture_destroy(g_dev, box);
    rhi_texture_destroy(g_dev, depth);
    combined_aa_shutdown(&caa);
}

/* ---- R644: deferred path on D3D12 ---- */

/* G-Buffer pass through the real DeferredSystem: one oversized triangle at
 * z = -0.5 (identity model / view-proj, so NDC z = -0.5), normal +Z, flat
 * textures, known factors. Every attachment is checked against
 * gbuffer.frag's arithmetic:
 *   RT0 = (albedo, clamp(mr.b * mfac))        RT1 = (oct(N), 0, 1)
 *   RT2 = (clamp(mr.g * rfac, .04, 1), mix(1, occ, aostr), flag, 1)
 *   RT3 = (curr_ndc - prev_ndc, 0, 1)          RT4 = (emissive * efac, 1)
 * The flat normal map (0.5, 0.5, 1) leaves N = +Z through the derivative
 * TBN, so oct(N) = (0.5, 0.5). u_prev_mvp translates by (+0.25, -0.125), so
 * the velocity is (-0.25, +0.125) on every pixel -- a transposed matrix read
 * moves that translation into w and the velocity changes. Depth is the
 * D3D12 window depth of NDC z = -0.5, i.e. 0.25. */
static RHITexture r644_tex(u8 r, u8 g, u8 b, u8 a) {
    static u8 px[2 * 2 * 4];
    RHITextureDesc td;
    int i;
    for (i = 0; i < 4; ++i) { px[i * 4] = r; px[i * 4 + 1] = g; px[i * 4 + 2] = b; px[i * 4 + 3] = a; }
    memset(&td, 0, sizeof(td));
    td.width = 2u; td.height = 2u;
    td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
    td.data = px;
    return rhi_texture_create(g_dev, &td);
}

static void r644_gbuffer_frame_ex(DeferredSystem *ds, RHICmdBuffer *cmd, RHIBuffer vbo,
                                  const float *vp, const float *prev_mvp, RHITexture *t,
                                  u32 nverts, int round_trip) {
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    deferred_begin_gbuffer(ds, g_dev, cmd);
    rhi_cmd_set_uniform_mat4(cmd, ds->_loc_gbuf_model, identity);
    rhi_cmd_set_uniform_mat4(cmd, ds->_loc_gbuf_vp, vp);
    rhi_cmd_set_uniform_mat4(cmd, ds->_loc_gbuf_prev_mvp, prev_mvp);
    if (round_trip) {
        /* main.c uploads the matrices once, then other pipelines run (skinned
         * G-Buffer, indirect compact) and the G-Buffer pipeline is bound
         * again WITHOUT re-uploading. On D3D12 a root-signature change drops
         * root constants, but the staging block is only flushed at a draw,
         * so values staged since the last draw still reach this one; the
         * demo's terrain / mesh draws depend on exactly that. */
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        /* An off-screen draw flushes the staged uniforms, as the skinned
         * draws do in the demo; only then does the root signature change
         * drop them. */
        rhi_cmd_draw(cmd, 1u, 1u);
        rhi_cmd_bind_pipeline(cmd, ds->lighting_pipeline);
        rhi_cmd_bind_pipeline(cmd, ds->gbuffer_pipeline);
    }
    /* bind_material's unit map: albedo 0, mr 2, normal 3, emissive 4,
     * occlusion 15. */
    rhi_cmd_bind_material_textures_ibl(cmd, t[0], t[1], t[2], t[3], t[4],
                                        RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                        (RHISampler){0}, RHI_HANDLE_NULL,
                                        RHI_HANDLE_NULL, RHI_HANDLE_NULL, NULL, 0u);
    deferred_bind_gbuffer_factors(ds, g_dev, cmd, 0.5f, 0.75f, 0.5f, 1.0f,
                                  2.0f, 1.0f, 0.5f);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, nverts, 1u);
    deferred_end_gbuffer(ds, g_dev, cmd);
}
static void r644_gbuffer_frame_n(DeferredSystem *ds, RHICmdBuffer *cmd, RHIBuffer vbo,
                                 const float *prev_mvp, RHITexture *t, u32 nverts) {
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    r644_gbuffer_frame_ex(ds, cmd, vbo, identity, prev_mvp, t, nverts, 0);
}
static void r644_gbuffer_frame(DeferredSystem *ds, RHICmdBuffer *cmd, RHIBuffer vbo,
                               const float *prev_mvp, RHITexture *t) {
    r644_gbuffer_frame_n(ds, cmd, vbo, prev_mvp, t, 3u);
}

TEST(deferred_gbuffer_sidecar_writes_all_five_targets) {
    static const float verts[3 * 8] = {
        -1.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         3.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
        -1.0f,  3.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f
    };
    static const float prev_mvp[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0.25f,-0.125f,0,1 };
    DeferredSystem ds;
    RHIBufferDesc bd;
    RHIBuffer vbo;
    RHITexture t[5];
    RHICmdBuffer *cmd;
    static u8 rt0[8 * 8 * 4], rt2[8 * 8 * 4];
    static u16 rt1[8 * 8 * 4], rt3[8 * 8 * 4], rt4[8 * 8 * 4];
    static float dep[8 * 8];
    int i;
    deferred_init(&ds, g_dev, 8u, 8u);
    ASSERT_TRUE(ds.initialized);
    ASSERT_EQ(ds._loc_gbuf_model, 0);
    ASSERT_EQ(ds._loc_gbuf_vp, 64);
    ASSERT_EQ(ds._loc_gbuf_prev_mvp, 128);
    ASSERT_EQ(ds._loc_gbuf_view, -1);
    ASSERT_EQ(ds._loc_gbuf_proj, -1);
    t[0] = r644_tex(200, 100, 50, 255);   /* albedo */
    t[1] = r644_tex(0, 204, 153, 255);    /* mr: g = roughness, b = metallic */
    t[2] = r644_tex(128, 128, 255, 255);  /* flat tangent-space normal */
    t[3] = r644_tex(51, 102, 153, 255);   /* emissive */
    t[4] = r644_tex(102, 0, 0, 255);      /* occlusion r */
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    ASSERT_TRUE(rhi_handle_valid(vbo));
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    r644_gbuffer_frame(&ds, cmd, vbo, prev_mvp, t);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_albedo_metallic, rt0, sizeof(rt0)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_normal, rt1, sizeof(rt1)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_roughness_ao, rt2, sizeof(rt2)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_velocity, rt3, sizeof(rt3)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_emissive, rt4, sizeof(rt4)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_depth, dep, sizeof(dep)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    for (i = 0; i < 8 * 8; ++i) {
        double metal = 153 / 255.0 * 0.5, rough = 204 / 255.0 * 0.75;
        double ao = 1.0 + (102 / 255.0 - 1.0) * 0.5;
        if (i == 0)
            printf("  gbuf px0 rt0 %u %u %u %u | rt1 %f %f | rt2 %u %u %u | rt3 %f %f | "
                   "rt4 %f %f %f | depth %f\n", rt0[0], rt0[1], rt0[2], rt0[3],
                   warp_half_to_float(rt1[0]), warp_half_to_float(rt1[1]),
                   rt2[0], rt2[1], rt2[2], warp_half_to_float(rt3[0]),
                   warp_half_to_float(rt3[1]), warp_half_to_float(rt4[0]),
                   warp_half_to_float(rt4[1]), warp_half_to_float(rt4[2]), dep[0]);
        ASSERT_EQ(rt0[i * 4 + 0], 200);
        ASSERT_EQ(rt0[i * 4 + 1], 100);
        ASSERT_EQ(rt0[i * 4 + 2], 50);
        ASSERT_TRUE(abs(rt0[i * 4 + 3] - (int)floor(metal * 255.0 + 0.5)) <= 1);
        ASSERT_TRUE(fabsf(warp_half_to_float(rt1[i * 4 + 0]) - 0.5f) < 0.002f);
        ASSERT_TRUE(fabsf(warp_half_to_float(rt1[i * 4 + 1]) - 0.5f) < 0.002f);
        ASSERT_TRUE(abs(rt2[i * 4 + 0] - (int)floor(rough * 255.0 + 0.5)) <= 1);
        ASSERT_TRUE(abs(rt2[i * 4 + 1] - (int)floor(ao * 255.0 + 0.5)) <= 1);
        ASSERT_EQ(rt2[i * 4 + 2], 255);
        ASSERT_TRUE(fabsf(warp_half_to_float(rt3[i * 4 + 0]) + 0.25f) < 0.002f);
        ASSERT_TRUE(fabsf(warp_half_to_float(rt3[i * 4 + 1]) - 0.125f) < 0.002f);
        ASSERT_TRUE(fabsf(warp_half_to_float(rt4[i * 4 + 0]) - 51 / 255.0f * 2.0f) < 0.004f);
        ASSERT_TRUE(fabsf(warp_half_to_float(rt4[i * 4 + 1]) - 102 / 255.0f) < 0.003f);
        ASSERT_TRUE(fabsf(warp_half_to_float(rt4[i * 4 + 2]) - 153 / 255.0f * 0.5f) < 0.003f);
        ASSERT_TRUE(fabsf(dep[i] - 0.25f) < 1e-5f);
    }
    /* Frame 2: the normal map points along tangent-space +X (255,128,128),
     * the uv is SWAPPED against screen space (u follows NDC y, v follows NDC
     * x) and the matrices go through a pipeline round trip before the draw.
     * Per pixel ddx(world) = (0.25, 0, 0), ddy(world) = (0, 0.25, 0) (row
     * index grows with NDC y on both backends' offscreen targets), ddx(uv) =
     * (0, 0.125), ddy(uv) = (0.125, 0). gbuffer.frag's
     * t = normalize(q1 * st2.t - q2 * st1.t) = normalize(0 - q2 * 0.125)
     * = -Y, so the perturbed normal is mostly -Y: oct = (0.5 +- small,
     * ~0.004). Only ddy reaches t here, so a flipped ddy turns it into +Y
     * (oct y ~0.996). */
    rhi_texture_destroy(g_dev, t[2]);
    t[2] = r644_tex(255, 128, 128, 255);
    {
        static const float sw[3 * 8] = {
            -1.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
             3.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f,
            -1.0f,  3.0f, -0.5f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f
        };
        rhi_buffer_update(g_dev, vbo, sw, sizeof(sw));
    }
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    {
        static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
        r644_gbuffer_frame_ex(&ds, cmd, vbo, identity, prev_mvp, t, 3u, 1);
    }
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_normal, rt1, sizeof(rt1)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_velocity, rt3, sizeof(rt3)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    for (i = 0; i < 8 * 8; ++i) {
        float ox = warp_half_to_float(rt1[i * 4 + 0]), oy = warp_half_to_float(rt1[i * 4 + 1]);
        if (fabsf(ox - 0.5f) > 0.01f || oy > 0.01f)
            printf("  gbuf tilted px %d oct = %f %f, want ~0.5 ~0.004\n", i, ox, oy);
        ASSERT_TRUE(fabsf(ox - 0.5f) < 0.01f);
        ASSERT_TRUE(oy < 0.01f);
        /* The round trip kept u_prev_mvp: velocity unchanged. */
        ASSERT_TRUE(fabsf(warp_half_to_float(rt3[i * 4 + 0]) + 0.25f) < 0.002f);
    }
    for (i = 0; i < 5; ++i) rhi_texture_destroy(g_dev, t[i]);
    rhi_buffer_destroy(g_dev, vbo);
    deferred_destroy(&ds, g_dev);
}

/* Deferred lighting through the real DeferredSystem + LightSystem, against
 * a double replay of deferred_light.frag (no IBL, no point-shadow cubes --
 * see deferred_light_hlsl.frag). The G-Buffer comes from the test above's
 * draw: albedo (200,100,50)/255, metallic 0.3, roughness 0.6, AO 0.75,
 * emissive (0.4, 0.4, 0.3), N = +Z, depth 0.25 everywhere.
 *
 * Camera: identity view/proj, so inv_vp = identity and the world position of
 * pixel (x, y) is (ndc_x, ndc_y, depth*2-1 = -0.5) with ndc from the pixel
 * centre. camera_pos (0, 0, 3). One directional light straight down -Z and
 * one point light. The cascade matrices map world into the atlas so that
 * cascade 0's NDC z = 0.5 ndc... (see below) for a shadowed / lit split.
 *
 * Frame A: no shadow atlas (white fallback = depth 1, so no blocker) and the
 * point light at (0.5, 0.5, 0) r=2 binned by light_system_cull -- every
 * pixel lit by the dir light, the point light only where the grid says.
 * Frame B: point_count = 0, a 2x2 shadow atlas with depth 0 (everything is a
 * blocker), cascade 0 = identity: z_win = 0.25, blocker = 0, filter radius
 * clamps to 5 -> samples = 5, every tap shadowed -> dir_shadow = 0.3. */
static void r644_cook(const double alb[3], double metal, double rough,
                      const double N[3], const double V[3], const double L[3],
                      const double lc[3], double out[3]) {
    double H[3], hl, ndh, ndv, ndl, hdv, a, a2, d, ndf, k, g, F0[3], c;
    int i;
    for (i = 0; i < 3; ++i) H[i] = V[i] + L[i];
    hl = sqrt(H[0] * H[0] + H[1] * H[1] + H[2] * H[2]);
    for (i = 0; i < 3; ++i) H[i] /= hl;
    ndh = fmax(N[0] * H[0] + N[1] * H[1] + N[2] * H[2], 0.0);
    ndv = fmax(N[0] * V[0] + N[1] * V[1] + N[2] * V[2], 0.0);
    ndl = fmax(N[0] * L[0] + N[1] * L[1] + N[2] * L[2], 0.0);
    hdv = fmax(H[0] * V[0] + H[1] * V[1] + H[2] * V[2], 0.0);
    a = rough * rough; a2 = a * a;
    d = ndh * ndh * (a2 - 1.0) + 1.0;
    ndf = a2 / (3.14159265359 * d * d);
    k = (rough + 1.0) * (rough + 1.0) / 8.0;
    g = (ndv / (ndv * (1.0 - k) + k)) * (ndl / (ndl * (1.0 - k) + k));
    c = 1.0 - hdv; c = c * c * c * c * c;
    for (i = 0; i < 3; ++i) {
        double F, spec, kD;
        F0[i] = 0.04 + (alb[i] - 0.04) * metal;
        F = F0[i] + (1.0 - F0[i]) * c;
        spec = ndf * g * F / (4.0 * ndv * ndl + 0.001);
        kD = (1.0 - F) * (1.0 - metal);
        out[i] = (kD * alb[i] / 3.14159265359 + spec) * lc[i] * ndl;
    }
}

TEST(deferred_lighting_sidecar_matches_the_brdf_and_csm_and_clusters) {
    static const float verts[3 * 8] = {
        -1.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         3.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
        -1.0f,  3.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    static Mat4 cascades[4];
    static LightSystem ls;
    DeferredSystem ds;
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO out;
    RHIBufferDesc bd;
    RHIBuffer vbo;
    RHITexture t[5], atlas;
    RHICmdBuffer *cmd;
    static u16 px[8 * 8 * 4];
    float cam[19];
    Mat4 view_m, proj_m;
    const double alb[3] = { 200 / 255.0, 100 / 255.0, 50 / 255.0 };
    const double N[3] = { 0, 0, 1 };
    const double dirc[3] = { 0.9, 0.8, 0.7 }, ptc[3] = { 3.0, 2.0, 1.0 };
    const double ptp[3] = { 0.5, 0.5, 0.0 }, ptr = 1.5;
    int frame, x, y, c, i, pt_lit = 0, pt_dark = 0;
    memset(&ds, 0, sizeof(ds));
    deferred_init(&ds, g_dev, 8u, 8u);
    ASSERT_TRUE(ds.initialized);
    ASSERT_EQ(ds._loc_inv_vp, 0);
    ASSERT_EQ(ds._loc_view, 64);
    ASSERT_EQ(ds._loc_camera_pos, 128);
    ASSERT_EQ(ds._loc_screen_w, 140);
    ASSERT_EQ(ds._loc_shadow_bias, 156);
    ASSERT_EQ(ds._loc_point_count, 160);
    ASSERT_EQ(ds._loc_dir_count, 164);
    ASSERT_EQ(ds._loc_point_shadow_far_planes, 176);
    t[0] = r644_tex(200, 100, 50, 255);
    t[1] = r644_tex(0, 204, 153, 255);
    t[2] = r644_tex(128, 128, 255, 255);
    t[3] = r644_tex(51, 102, 153, 255);
    t[4] = r644_tex(102, 0, 0, 255);
    {
        static float zero[2 * 2];
        RHITextureDesc td;
        memset(&td, 0, sizeof(td));
        td.width = 2u; td.height = 2u;
        td.format = RHI_FORMAT_R32_FLOAT; td.mip_levels = 1u;
        td.data = zero;
        atlas = rhi_texture_create(g_dev, &td);
    }
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u; fd.sample_count = 1u;
    fd.color_format = RHI_FORMAT_R16G16B16A16_SFLOAT;
    out = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    ASSERT_TRUE(rhi_handle_valid(vbo) && rhi_handle_valid(out.fb) &&
                rhi_handle_valid(atlas));
    memset(&ls, 0, sizeof(ls));
    light_system_init(&ls, g_dev);
    for (i = 0; i < 4; ++i) memcpy(cascades[i].e, identity, sizeof(identity));
    light_system_set_cascade_vp(&ls, cascades);
    memcpy(view_m.e, identity, sizeof(identity));
    memcpy(proj_m.e, identity, sizeof(identity));
    memcpy(cam, identity, sizeof(identity));
    cam[16] = 0.0f; cam[17] = 0.0f; cam[18] = 3.0f;
    for (frame = 0; frame < 2; ++frame) {
        double dir_shadow = frame == 0 ? 1.0 : 0.3;
        light_system_clear(&ls);
        light_system_add_dir(&ls, 0.0f, 0.0f, -1.0f, (f32)dirc[0], (f32)dirc[1], (f32)dirc[2]);
        if (frame == 0)
            light_system_add_point(&ls, (f32)ptp[0], (f32)ptp[1], (f32)ptp[2], (f32)ptr,
                                   (f32)ptc[0], (f32)ptc[1], (f32)ptc[2]);
        light_system_set_depth_range(&ls, 0.1f, 100.0f);
        light_system_cull(&ls, &view_m, &proj_m, 8u, 8u);
        light_system_upload(&ls);
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        r644_gbuffer_frame(&ds, cmd, vbo, identity, t);
        rhi_offscreen_fbo_bind(cmd, &out);
        deferred_lighting_pass(&ds, g_dev, cmd, light_system_data_slot(&ls),
                               light_system_grid_slot(&ls), ls.point_count, ls.dir_count,
                               frame == 0 ? RHI_HANDLE_NULL : atlas,
                               RHI_HANDLE_NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                               0u, NULL, NULL, 0.1f, 100.0f, 0.002f, identity, cam,
                               RHI_HANDLE_NULL);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, out.color_tex, px, sizeof(px)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
        for (y = 0; y < 8; ++y) {
            for (x = 0; x < 8; ++x) {
                double w[3], V[3], vl, col[3], add[3], L[3];
                double metal = 153 / 255.0 * 0.5, rough = 204 / 255.0 * 0.75;
                const double emis[3] = { 51 / 255.0 * 2.0, 102 / 255.0, 153 / 255.0 * 0.5 };
                w[0] = (x + 0.5) / 4.0 - 1.0; w[1] = (y + 0.5) / 4.0 - 1.0; w[2] = -0.5;
                V[0] = -w[0]; V[1] = -w[1]; V[2] = 3.0 - w[2];
                vl = sqrt(V[0] * V[0] + V[1] * V[1] + V[2] * V[2]);
                for (c = 0; c < 3; ++c) V[c] /= vl;
                metal = floor(metal * 255.0 + 0.5) / 255.0;   /* RGBA8 round trip */
                rough = floor(rough * 255.0 + 0.5) / 255.0;
                for (c = 0; c < 3; ++c) col[c] = emis[c];      /* ao * (no IBL) = 0 */
                L[0] = 0; L[1] = 0; L[2] = 1;
                {
                    double lc[3];
                    for (c = 0; c < 3; ++c) lc[c] = dirc[c] * dir_shadow;
                    r644_cook(alb, metal, rough, N, V, L, lc, add);
                    for (c = 0; c < 3; ++c) col[c] += add[c];
                }
                if (frame == 0) {
                    double toL[3], dist, att, lc[3];
                    for (c = 0; c < 3; ++c) toL[c] = ptp[c] - w[c];
                    dist = sqrt(toL[0] * toL[0] + toL[1] * toL[1] + toL[2] * toL[2]);
                    if (dist <= ptr) {
                        for (c = 0; c < 3; ++c) L[c] = toL[c] / fmax(dist, 1e-3);
                        att = 1.0 - dist / ptr; att *= att;
                        for (c = 0; c < 3; ++c) lc[c] = ptc[c] * att;
                        r644_cook(alb, metal, rough, N, V, L, lc, add);
                        for (c = 0; c < 3; ++c) col[c] += add[c];
                        if (att > 0.05) pt_lit++;
                    } else {
                        pt_dark++;
                    }
                }
                for (c = 0; c < 3; ++c) {
                    double want = col[c] / (col[c] + 1.0);
                    float got = warp_half_to_float(px[(y * 8 + x) * 4 + c]);
                    if (fabs(got - want) > 0.004)
                        printf("  deferred light frame %d px (%d,%d) ch %d = %f, want %f\n",
                               frame, x, y, c, got, want);
                    ASSERT_TRUE(fabs(got - want) <= 0.004);
                }
            }
        }
    }
    /* The point light must light some pixels strongly and miss others, or the
     * cluster lookup was not exercised. */
    ASSERT_TRUE(pt_lit >= 4 && pt_dark >= 8);
    light_system_shutdown(&ls);
    for (i = 0; i < 5; ++i) rhi_texture_destroy(g_dev, t[i]);
    rhi_texture_destroy(g_dev, atlas);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_offscreen_fbo_destroy(g_dev, &out);
    deferred_destroy(&ds, g_dev);
}

/* The demo allocates the G-Buffer at the WINDOW size (deferred_init(w, h)) but
 * lights into the half-resolution scene FBO, so the lighting pass must address
 * the G-Buffer by uv, not by SV_Position (the first port used Load(SV_Position)
 * and lit the whole frame from the top-left quarter of the G-Buffer). Here the
 * G-Buffer is 16x16 with the left half covered by a triangle at depth 0.25 and
 * the right half empty (depth 1 -> the sky early-out, black), lit into an 8x8
 * target: output pixel x must follow G-Buffer texel 2x+1, so columns 0..3 are
 * lit and 4..7 are black. Addressing by SV_Position would read texels 0..7 --
 * all inside the covered half -- and light every column. */
TEST(deferred_lighting_reads_a_larger_gbuffer_by_uv) {
    /* Left half of NDC as two triangles (clockwise on screen like the
     * engine's meshes, which the default back-face culling keeps). */
    static const float verts[6 * 8] = {
        -1.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         0.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         0.0f,  1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         0.0f,  1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    static LightSystem ls;
    DeferredSystem ds;
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO out;
    RHIBufferDesc bd;
    RHIBuffer vbo;
    RHITexture t[5];
    RHICmdBuffer *cmd;
    static u16 px[8 * 8 * 4];
    float cam[19];
    Mat4 view_m;
    int x, y, i, lit = 0, dark = 0;
    memset(&ds, 0, sizeof(ds));
    deferred_init(&ds, g_dev, 16u, 16u);
    ASSERT_TRUE(ds.initialized);
    t[0] = r644_tex(200, 100, 50, 255);
    t[1] = r644_tex(0, 204, 153, 255);
    t[2] = r644_tex(128, 128, 255, 255);
    t[3] = r644_tex(0, 0, 0, 255);
    t[4] = r644_tex(255, 0, 0, 255);
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u; fd.sample_count = 1u;
    fd.color_format = RHI_FORMAT_R16G16B16A16_SFLOAT;
    out = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    ASSERT_TRUE(rhi_handle_valid(vbo) && rhi_handle_valid(out.fb));
    memset(&ls, 0, sizeof(ls));
    light_system_init(&ls, g_dev);
    light_system_clear(&ls);
    light_system_add_dir(&ls, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f);
    memcpy(view_m.e, identity, sizeof(identity));
    light_system_cull(&ls, &view_m, &view_m, 8u, 8u);
    light_system_upload(&ls);
    memcpy(cam, identity, sizeof(identity));
    cam[16] = 0.0f; cam[17] = 0.0f; cam[18] = 3.0f;
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    r644_gbuffer_frame_n(&ds, cmd, vbo, identity, t, 6u);
    rhi_offscreen_fbo_bind(cmd, &out);
    deferred_lighting_pass(&ds, g_dev, cmd, light_system_data_slot(&ls),
                           light_system_grid_slot(&ls), ls.point_count, ls.dir_count,
                           RHI_HANDLE_NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                           RHI_HANDLE_NULL, 0u, NULL, NULL, 0.1f, 100.0f, 0.002f,
                           identity, cam, RHI_HANDLE_NULL);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, out.color_tex, px, sizeof(px)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            float r = warp_half_to_float(px[(y * 8 + x) * 4]);
            int want_lit = x < 4;
            if ((r > 0.05f) != want_lit)
                printf("  larger gbuffer px (%d,%d) r = %f, want %s\n", x, y, r,
                       want_lit ? "lit" : "black");
            ASSERT_TRUE((r > 0.05f) == want_lit);
            if (want_lit) lit++; else dark++;
        }
    }
    ASSERT_TRUE(lit == 32 && dark == 32);
    light_system_shutdown(&ls);
    for (i = 0; i < 5; ++i) rhi_texture_destroy(g_dev, t[i]);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_offscreen_fbo_destroy(g_dev, &out);
    deferred_destroy(&ds, g_dev);
}

/* A real camera through the whole deferred path, against a double replay.
 * The scene is a floor quad at y = 0 seen by a perspective camera at
 * (0, 3, 6) looking down at the origin (camera_view-style matrices built here
 * with mat4_lookat / mat4_perspective, the engine's own). With
 * non-identity view / proj / inv_vp a transposed product on any of them
 * moves the reconstructed world position, and the G-Buffer texel each output
 * pixel reads is found by uv because the G-Buffer (16x16) is twice the
 * lighting target (8x8), as in the demo.
 *
 * Lights: a directional light with cascade 0 = a top-down orthographic light
 * VP whose atlas quadrant is fully shadowed on the left half of the floor
 * (x < 0) and empty on the right; and one point light near the floor's +x/-z
 * corner whose radius only reaches part of the screen, binned by the real
 * light_system_cull with this camera -- a flipped cluster row or column puts
 * it in the wrong tiles. The expected image is replayed per pixel: depth from
 * the replayed G-Buffer projection, world from inv_vp, PCSS-free shadow
 * (blocker = 0 -> full 11x11 PCF of 0.3) or 1, and the cluster lookup's
 * light list replayed from ls.grid_* exactly as the shader indexes it. */
static const u8 *r644_chk;
static double r644_dot3(const double *a, const double *b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/* deferred_light.frag's shadow_test, replayed in double over a 64x64 atlas
 * read NEAREST + CLAMP (what deferred_light_hlsl.frag's nearest() does). */
static const float *r644_atlas;
static double r644_atlas_tap(int cascade, double u, double v, double ox, double oy) {
    double qx = cascade & 1, qy = cascade >> 1, ts = 1.0 / 64.0;
    double ax = (qx + u) * 0.5 + ox, ay = (qy + v) * 0.5 + oy;
    double lo_x = qx * 0.5 + ts, hi_x = (qx + 1.0) * 0.5 - ts;
    double lo_y = qy * 0.5 + ts, hi_y = (qy + 1.0) * 0.5 - ts;
    int tx, ty;
    ax = ax < lo_x ? lo_x : (ax > hi_x ? hi_x : ax);
    ay = ay < lo_y ? lo_y : (ay > hi_y ? hi_y : ay);
    tx = (int)floor(ax * 64.0); ty = (int)floor(ay * 64.0);
    if (tx > 63) tx = 63;
    if (ty > 63) ty = 63;
    return r644_atlas[ty * 64 + tx];
}
static double r644_shadow(const Mat4 *casc, const double wp[3], double bias) {
    double clip[4], n[3], u, v, z, ls_, sw, bsum = 0, blocker, pen, fr, s = 0;
    int r, k, x, y, bcount = 0, samples;
    for (r = 0; r < 4; ++r) {
        clip[r] = casc[0].e[3][r];
        for (k = 0; k < 3; ++k) clip[r] += casc[0].e[k][r] * wp[k];
    }
    for (k = 0; k < 3; ++k) n[k] = clip[k] / clip[3];
    u = n[0] * 0.5 + 0.5; v = n[1] * 0.5 + 0.5;
    if (u < 0 || u > 1 || v < 0 || v > 1) return 1.0;
    z = n[2] * 0.5 + 0.5;
    ls_ = 0.02;
    sw = ls_ / fmax(z, 1e-3);
    for (x = -2; x <= 2; ++x)
        for (y = -2; y <= 2; ++y) {
            double d = r644_atlas_tap(0, u, v, x / 64.0 * sw, y / 64.0 * sw);
            if (d < z - 0.002) { bsum += d; bcount++; }
        }
    if (bcount == 0) return 1.0;
    blocker = bsum / bcount;
    pen = (z - blocker) / fmax(blocker, 1e-3);
    fr = pen * ls_ * 40.0;
    fr = fr < 1.0 ? 1.0 : (fr > 5.0 ? 5.0 : fr);
    samples = (int)ceil(fr * 2.0);
    samples = samples < 1 ? 1 : (samples > 5 ? 5 : samples);
    for (x = -samples; x <= samples; ++x)
        for (y = -samples; y <= samples; ++y) {
            double d = r644_atlas_tap(0, u, v, x / 64.0 * fr, y / 64.0 * fr);
            s += (z - bias) > d ? 0.3 : 1.0;
        }
    return s / ((2 * samples + 1) * (2 * samples + 1));
}

TEST(deferred_path_with_a_perspective_camera_matches_a_replay) {
    static float verts[6 * 8];
    static LightSystem ls;
    static Mat4 cascades[4];
    static float atlas_px[64 * 64];
    DeferredSystem ds;
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO out;
    RHIBufferDesc bd;
    RHIBuffer vbo;
    RHITexture t[5], atlas;
    RHITextureDesc td;
    RHICmdBuffer *cmd;
    static u16 px[8 * 8 * 4];
    static float gdep[16 * 16];
    float cam[19];
    Mat4 view, proj, vp, inv_vp, lview, lproj;
    const double ptp[3] = { 0.5, 0.3, 3.0 }, ptc[3] = { 4.0, 3.0, 2.0 }, ptr = 1.5;
    const double dirc[3] = { 0.8, 0.8, 0.8 };
    int x, y, c, i, sh = 0, unsh = 0, pt_on = 0, pt_off = 0, sky = 0;
    const float q[4][2] = { {-4, -4}, {4, -4}, {4, 4}, {-4, 4} };
    const int tri[6] = { 0, 2, 1, 0, 3, 2 };
    for (i = 0; i < 6; ++i) {
        float *v = &verts[i * 8];
        v[0] = q[tri[i]][0]; v[1] = 0.0f; v[2] = q[tri[i]][1];
        v[3] = 0.0f; v[4] = 1.0f; v[5] = 0.0f;
        v[6] = (q[tri[i]][0] + 4.0f) / 8.0f; v[7] = (q[tri[i]][1] + 4.0f) / 8.0f;
    }
    view = mat4_lookat(vec3(0.0f, 3.0f, 6.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    proj = mat4_perspective(1.0f, 1.0f, 0.5f, 30.0f);
    vp = mat4_mul(proj, view);
    inv_vp = mat4_inverse(vp);
    /* Light: straight down, ortho over [-4,4]^2, y from 10 to -10. */
    lview = mat4_lookat(vec3(0.0f, 10.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    lproj = mat4_ortho(-4.0f, 4.0f, -4.0f, 4.0f, 0.1f, 20.0f);
    cascades[0] = mat4_mul(lproj, lview);
    for (i = 1; i < 4; ++i) cascades[i] = cascades[0];
    /* Atlas 64x64, quadrant 0 = texels [0,32)^2. Light-space uv.x = world x
     * mapped [-4,4] -> [0,1]; the caster (depth 0) covers world x < 0. */
    /* Caster at depth 0.4 (a blocker between light and floor, z_win ~0.5)
     * over world x < -1: a moderate penumbra, so both fully lit, fully
     * shadowed and partial pixels appear. */
    for (y = 0; y < 64; ++y)
        for (x = 0; x < 64; ++x)
            atlas_px[y * 64 + x] = (x < 32 && y < 32 && x < 12) ? 0.4f : 1.0f;
    r644_atlas = atlas_px;
    memset(&td, 0, sizeof(td));
    td.width = 64u; td.height = 64u; td.format = RHI_FORMAT_R32_FLOAT; td.mip_levels = 1u;
    td.data = atlas_px;
    atlas = rhi_texture_create(g_dev, &td);
    memset(&ds, 0, sizeof(ds));
    deferred_init(&ds, g_dev, 16u, 16u);
    ASSERT_TRUE(ds.initialized);
    /* Albedo: a 16x16 checker of two colours over the floor's uv, so every
     * G-Buffer texel the lighting pass might read by mistake (SV_Position
     * instead of uv, a swapped register) has a distinct colour. The
     * metallic-roughness texture is a different flat colour from albedo, so
     * reading one through the other's register changes the result. */
    {
        static u8 chk[16 * 16 * 4];
        RHITextureDesc ctd;
        for (y = 0; y < 16; ++y)
            for (x = 0; x < 16; ++x) {
                u8 *p = &chk[(y * 16 + x) * 4];
                int on = (x + y) & 1;
                p[0] = on ? 200 : 60; p[1] = on ? 100 : 180; p[2] = on ? 50 : 120; p[3] = 255;
            }
        memset(&ctd, 0, sizeof(ctd));
        ctd.width = 16u; ctd.height = 16u;
        ctd.format = RHI_FORMAT_R8G8B8A8_UNORM; ctd.mip_levels = 1u;
        ctd.data = chk;
        t[0] = rhi_texture_create(g_dev, &ctd);
        r644_chk = chk;
    }
    t[1] = r644_tex(0, 204, 153, 255);
    t[2] = r644_tex(128, 128, 255, 255);
    t[3] = r644_tex(0, 0, 0, 255);
    t[4] = r644_tex(255, 0, 0, 255);
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u; fd.sample_count = 1u;
    fd.color_format = RHI_FORMAT_R16G16B16A16_SFLOAT;
    out = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    ASSERT_TRUE(rhi_handle_valid(vbo) && rhi_handle_valid(out.fb) && rhi_handle_valid(atlas));
    ASSERT_TRUE(rhi_handle_valid(t[0]));
    memset(&ls, 0, sizeof(ls));
    light_system_init(&ls, g_dev);
    light_system_clear(&ls);
    light_system_add_dir(&ls, 0.0f, -1.0f, 0.0f, (f32)dirc[0], (f32)dirc[1], (f32)dirc[2]);
    light_system_add_point(&ls, (f32)ptp[0], (f32)ptp[1], (f32)ptp[2], (f32)ptr,
                           (f32)ptc[0], (f32)ptc[1], (f32)ptc[2]);
    light_system_set_cascade_vp(&ls, cascades);
    light_system_set_depth_range(&ls, 0.5f, 30.0f);
    light_system_cull(&ls, &view, &proj, 8u, 8u);
    light_system_upload(&ls);
    memcpy(cam, inv_vp.e, sizeof(inv_vp.e));
    cam[16] = 0.0f; cam[17] = 3.0f; cam[18] = 6.0f;
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    r644_gbuffer_frame_ex(&ds, cmd, vbo, &vp.e[0][0], &vp.e[0][0], t, 6u, 0);
    rhi_offscreen_fbo_bind(cmd, &out);
    deferred_set_lighting_target_size(&ds, 8u, 8u);   /* = the cull size */
    deferred_lighting_pass(&ds, g_dev, cmd, light_system_data_slot(&ls),
                           light_system_grid_slot(&ls), ls.point_count, ls.dir_count,
                           atlas, RHI_HANDLE_NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                           0u, NULL, NULL, 0.5f, 30.0f, 0.002f, &view.e[0][0], cam,
                           RHI_HANDLE_NULL);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, out.color_tex, px, sizeof(px)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_depth, gdep, sizeof(gdep)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            /* uv of this output pixel -> the G-Buffer texel nearest() reads. */
            double u = (x + 0.5) / 8.0, v = (y + 0.5) / 8.0;
            int gx = (int)floor(u * 16.0), gy = (int)floor(v * 16.0);
            double d = gdep[gy * 16 + gx];
            double clip[4], w[4], wp[3], V[3], vl, N[3] = { 0, 1, 0 }, col[3], add[3], L[3];
            double metal = floor(153 / 255.0 * 0.5 * 255.0 + 0.5) / 255.0;
            double rough = floor(204 / 255.0 * 0.75 * 255.0 + 0.5) / 255.0;
            double shadow = 1.0, alb[3];
            int k, r;
            if (d >= 1.0) {
                for (c = 0; c < 3; ++c)
                    ASSERT_TRUE(warp_half_to_float(px[(y * 8 + x) * 4 + c]) == 0.0f);
                sky++;
                continue;
            }
            clip[0] = u * 2 - 1; clip[1] = v * 2 - 1; clip[2] = d * 2 - 1; clip[3] = 1;
            for (r = 0; r < 4; ++r) {
                w[r] = 0;
                for (k = 0; k < 4; ++k) w[r] += inv_vp.e[k][r] * clip[k];
            }
            for (c = 0; c < 3; ++c) wp[c] = w[c] / w[3];
            {
                /* The G-Buffer texel's own centre is what was rasterised:
                 * its world position on the floor gives the uv the albedo
                 * texture was sampled at, replayed with the D3D12 static
                 * sampler (bilinear, WRAP). */
                double gc_clip[4], gw[4], fu, fv;
                gc_clip[0] = (gx + 0.5) / 16.0 * 2 - 1; gc_clip[1] = (gy + 0.5) / 16.0 * 2 - 1;
                gc_clip[2] = d * 2 - 1; gc_clip[3] = 1;
                for (r = 0; r < 4; ++r) {
                    gw[r] = 0;
                    for (k = 0; k < 4; ++k) gw[r] += inv_vp.e[k][r] * gc_clip[k];
                }
                fu = (gw[0] / gw[3] + 4.0) / 8.0 * 16.0 - 0.5;
                fv = (gw[2] / gw[3] + 4.0) / 8.0 * 16.0 - 0.5;
                {
                    int x0 = (int)floor(fu), y0 = (int)floor(fv), sx, sy;
                    double ax = fu - x0, ay = fv - y0;
                    for (c = 0; c < 3; ++c) alb[c] = 0.0;
                    for (sy = 0; sy < 2; ++sy)
                        for (sx = 0; sx < 2; ++sx) {
                            int tx = (((x0 + sx) % 16) + 16) % 16;
                            int ty = (((y0 + sy) % 16) + 16) % 16;
                            double wgt = (sx ? ax : 1 - ax) * (sy ? ay : 1 - ay);
                            for (c = 0; c < 3; ++c)
                                alb[c] += wgt * r644_chk[(ty * 16 + tx) * 4 + c] / 255.0;
                        }
                    /* RT0 is RGBA8: the stored albedo is rounded. */
                    for (c = 0; c < 3; ++c) alb[c] = floor(alb[c] * 255.0 + 0.5) / 255.0;
                }
            }
            V[0] = 0 - wp[0]; V[1] = 3 - wp[1]; V[2] = 6 - wp[2];
            vl = sqrt(r644_dot3(V, V));
            for (c = 0; c < 3; ++c) V[c] /= vl;
            shadow = r644_shadow(cascades, wp, 0.002);
            if (shadow < 0.999) sh++; else unsh++;
            for (c = 0; c < 3; ++c) col[c] = 0.0;   /* no emissive, no IBL */
            L[0] = 0; L[1] = 1; L[2] = 0;
            {
                double lc[3];
                for (c = 0; c < 3; ++c) lc[c] = dirc[c] * shadow;
                r644_cook(alb, metal, rough, N, V, L, lc, add);
                for (c = 0; c < 3; ++c) col[c] += add[c];
            }
            {
                /* Cluster lookup exactly as the shader does it. */
                double vpos[4], ld;
                /* SV_Position is the pixel centre: cx = floor((x + .5) / (8/16)). */
                int cx = (int)floor((x + 0.5) / (8.0 / 16.0));
                int cy = (int)floor((y + 0.5) / (8.0 / 8.0)), cz, ci, go, gc, gi;
                for (r = 0; r < 4; ++r) {
                    vpos[r] = view.e[3][r];
                    for (k = 0; k < 3; ++k) vpos[r] += view.e[k][r] * wp[k];
                }
                ld = -vpos[2];
                if (cx > 15) cx = 15;
                if (cy > 7) cy = 7;
                cz = (int)floor(24.0 * log2(fmax(ld / 0.5, 1.0)) / log2(30.0 / 0.5));
                if (cz > 23) cz = 23;
                ci = cx + cy * 16 + cz * 128;
                go = (int)ls.grid_offsets_counts[ci * 2];
                gc = (int)ls.grid_offsets_counts[ci * 2 + 1];
                for (gi = 0; gi < gc; ++gi) {
                    int li = (int)ls.grid_indices[go + gi];
                    double toL[3], dist, att, lc[3];
                    (void)li;
                    for (c = 0; c < 3; ++c) toL[c] = ptp[c] - wp[c];
                    dist = sqrt(r644_dot3(toL, toL));
                    if (dist > ptr) continue;
                    for (c = 0; c < 3; ++c) L[c] = toL[c] / fmax(dist, 1e-3);
                    att = 1.0 - dist / ptr; att *= att;
                    for (c = 0; c < 3; ++c) lc[c] = ptc[c] * att;
                    r644_cook(alb, metal, rough, N, V, L, lc, add);
                    for (c = 0; c < 3; ++c) col[c] += add[c];
                    if (att > 0.02) pt_on++;
                }
                if (gc == 0) pt_off++;
            }
            for (c = 0; c < 3; ++c) {
                double want = col[c] / (col[c] + 1.0);
                float got = warp_half_to_float(px[(y * 8 + x) * 4 + c]);
                if (fabs(got - want) > 0.006)
                    printf("  perspective px (%d,%d) ch %d = %f, want %f (world %.2f %.2f %.2f)\n",
                           x, y, c, got, want, wp[0], wp[1], wp[2]);
                ASSERT_TRUE(fabs(got - want) <= 0.006);
            }
        }
    }
    printf("  (perspective: %d shadowed, %d lit, %d sky, point on %d / off %d) ",
           sh, unsh, sky, pt_on, pt_off);
    ASSERT_TRUE(sh >= 3 && unsh >= 3 && sky >= 4 && pt_on >= 2 && pt_off >= 4);
    light_system_shutdown(&ls);
    for (i = 0; i < 5; ++i) rhi_texture_destroy(g_dev, t[i]);
    rhi_texture_destroy(g_dev, atlas);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_offscreen_fbo_destroy(g_dev, &out);
    deferred_destroy(&ds, g_dev);
}

/* ---- R643: D3D12 validation fixes ----
 * The debug layer's messages used to go to OutputDebugString only, so a
 * console run never saw them; R643 drains them into the log and counts them
 * (rhi_d3d12_debug_layer_counts). The tests below drive each pattern the
 * demo hit and assert both the pixels and that the layer stayed silent. On
 * a non-debug build the counts are not available and only the pixels are
 * checked. */
/* Declared here rather than through rhi/rhi_d3d12.h: that header pulls in
 * <windows.h>, whose `near` / `far` macros break this file. */
typedef unsigned long long UINT64;
int rhi_d3d12_debug_layer_counts(RHIDevice *dev, UINT64 *errors,
                                 UINT64 *warnings, UINT64 *rt_srv_aliases);
static UINT64 r643_err0, r643_warn0, r643_alias0;
static int r643_layer;

static void r643_mark(void) {
    r643_layer = rhi_d3d12_debug_layer_counts(g_dev, &r643_err0, &r643_warn0,
                                              &r643_alias0);
}

static int r643_clean(const char *what) {
    UINT64 e = 0, w = 0, a = 0;
    (void)rhi_d3d12_debug_layer_counts(g_dev, &e, &w, &a);
    if (a != r643_alias0)
        printf("  %s: %llu RT/SRV alias warnings\n", what,
               (unsigned long long)(a - r643_alias0));
    if (!r643_layer) return a == r643_alias0;
    if (e != r643_err0 || w != r643_warn0)
        printf("  %s: debug layer logged %llu errors, %llu warnings\n", what,
               (unsigned long long)(e - r643_err0),
               (unsigned long long)(w - r643_warn0));
    return e == r643_err0 && w == r643_warn0 && a == r643_alias0;
}

/* A uniform buffer bound once stays bound across a pipeline change on GL and
 * Vulkan, and main.c depends on it (the forward temporal block is published
 * once, then only the pipeline is rebound after other passes). D3D12 drops
 * every root argument when the root signature changes; R643 re-applies the
 * frame's CBVs on bind. The blinn_phong draw reads u_camera_pos from b1; a
 * lost b1 reads zeros, V = normalize(-world) and the specular term moves.
 * Draw A binds the CBV after the pipeline (the reference), draw B binds it,
 * then a different pipeline, then blinn_phong again without rebinding -- the
 * two images must match exactly, and the 52-byte UBO (not a multiple of 256)
 * must not trip the CBV range check ([649]). */
TEST(uniform_buffer_survives_a_pipeline_change) {
    static const float verts[3 * 8] = {
        -1.0f, -1.0f, 0.0f,   0.3f, 0.2f, 0.93f,   0.0f, 0.0f,
         3.0f, -1.0f, 0.0f,   0.3f, 0.2f, 0.93f,   2.0f, 0.0f,
        -1.0f,  3.0f, 0.0f,   0.3f, 0.2f, 0.93f,   0.0f, 2.0f
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs, bvs, bfs;
    RHIPipeline pipe, other;
    RHIPipelineDesc pd;
    RHIBufferDesc bd;
    RHIBuffer vbo, ubo;
    RHITexture white;
    RHICmdBuffer *cmd;
    unsigned char ref[8 * 8 * 4], got[8 * 8 * 4];
    int pass, i, lit = 0;
    vs = rhi_shader_create_path(g_dev, "shaders/blinn_phong.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/blinn_phong.frag", true);
    bvs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    bfs = rhi_shader_create(g_dev, "blit_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs) && rhi_handle_valid(fs) &&
                rhi_handle_valid(bvs) && rhi_handle_valid(bfs));
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u;
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM; fd.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.vertex_stride = 32u;
    pd.disable_culling = true; pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    memset(&pd, 0, sizeof(pd));
    pd.vert = bvs; pd.frag = bfs;
    pd.no_vertex_input = true; pd.uses_textures = true;
    pd.disable_culling = true; pd.depth_write_disable = true;
    other = rhi_pipeline_create(g_dev, &pd);
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    ubo = warp_forward_temporal_create(g_dev, 0.5f, 0.8f, 2.0f);
    white = r641_flat_rgba8(2u, 2u, 255, 255, 255);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb) && rhi_handle_valid(pipe) &&
                rhi_handle_valid(other) && rhi_handle_valid(vbo) &&
                rhi_handle_valid(ubo) && rhi_handle_valid(white));
    r643_mark();
    for (pass = 0; pass < 2; ++pass) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        if (pass == 1) {
            /* Published while ANOTHER pipeline is bound... */
            rhi_cmd_bind_pipeline(cmd, pipe);
            rhi_cmd_bind_uniform_buffer(cmd, ubo, 1u);
            rhi_cmd_bind_pipeline(cmd, other);
            rhi_cmd_bind_texture(cmd, white, (RHISampler){0}, 0u);
        }
        rhi_cmd_bind_pipeline(cmd, pipe);
        if (pass == 0) rhi_cmd_bind_uniform_buffer(cmd, ubo, 1u);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_set_uniform_mat4(cmd, 128, identity);
        rhi_cmd_set_uniform_vec3(cmd, 192, -0.2f, -0.3f, -0.93f);
        rhi_cmd_set_uniform_vec3(cmd, 208, 0.6f, 0.6f, 0.6f);
        rhi_cmd_set_uniform_vec3(cmd, 224, 0.1f, 0.1f, 0.1f);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        rhi_cmd_bind_texture(cmd, white, (RHISampler){0}, 0u);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex,
                                            pass == 0 ? ref : got, sizeof(ref)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    }
    for (i = 0; i < 8 * 8 * 4; ++i) {
        if (got[i] != ref[i])
            printf("  ubo rebind byte %d = %u, reference %u\n", i, got[i], ref[i]);
        ASSERT_EQ(got[i], ref[i]);
    }
    /* The reference itself must depend on the camera, or the comparison
     * proves nothing: the specular highlight puts some pixels well above the
     * diffuse level (0.1 + 0.6*0.98 = 0.69 -> 175). */
    for (i = 0; i < 8 * 8; ++i) if (ref[i * 4] > 185) lit++;
    ASSERT_TRUE(lit > 0);
    ASSERT_TRUE(r643_clean("uniform_buffer_survives_a_pipeline_change"));
    rhi_texture_destroy(g_dev, white);
    rhi_buffer_destroy(g_dev, ubo);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, other);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_shader_destroy(g_dev, vs); rhi_shader_destroy(g_dev, fs);
    rhi_shader_destroy(g_dev, bvs); rhi_shader_destroy(g_dev, bfs);
}

/* [1001]: a CBV bound in a frame must keep its descriptor until that frame's
 * list has executed. rhi_cmd_bind_uniform_buffer used to give the slot back
 * at once with ctx->next_fence as its retire point; any one-shot submit later
 * in the same frame (here: creating a texture with initial data) signals and
 * waits on exactly that value, so the slot looked retired while the frame was
 * still recording, and a later descriptor_take could hand it out again.
 * The blinn_phong output must equal the frame without the mid-frame upload.
 *
 * Limit, stated plainly: descriptor_take scans the free list from the
 * oldest entry, so with a mostly empty heap the stale slot is not the one
 * handed out next and this test also passes against the old code (verified).
 * The demo hit [1001] because its heap churns; the guard that actually
 * catches a regression is the debug-layer gate at the end of the suite plus
 * the demo run. The test stays as the scenario's pixel check. */
TEST(cbv_descriptor_survives_a_mid_frame_upload) {
    static const float verts[3 * 8] = {
        -1.0f, -1.0f, 0.0f,   0.3f, 0.2f, 0.93f,   0.0f, 0.0f,
         3.0f, -1.0f, 0.0f,   0.3f, 0.2f, 0.93f,   2.0f, 0.0f,
        -1.0f,  3.0f, 0.0f,   0.3f, 0.2f, 0.93f,   0.0f, 2.0f
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHIBufferDesc bd;
    RHIBuffer vbo, ubo;
    RHITexture white, extra = RHI_HANDLE_NULL;
    RHICmdBuffer *cmd;
    unsigned char ref[8 * 8 * 4], got[8 * 8 * 4];
    int pass, i;
    vs = rhi_shader_create_path(g_dev, "shaders/blinn_phong.vert", false);
    fs = rhi_shader_create_path(g_dev, "shaders/blinn_phong.frag", true);
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u;
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM; fd.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.vertex_stride = 32u;
    pd.disable_culling = true; pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    ubo = warp_forward_temporal_create(g_dev, 0.5f, 0.8f, 2.0f);
    white = r641_flat_rgba8(2u, 2u, 255, 255, 255);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb) && rhi_handle_valid(pipe) &&
                rhi_handle_valid(vbo) && rhi_handle_valid(ubo) &&
                rhi_handle_valid(white));
    r643_mark();
    for (pass = 0; pass < 2; ++pass) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, pipe);
        rhi_cmd_bind_uniform_buffer(cmd, ubo, 1u);
        if (pass == 1) {
            /* One-shot upload while this frame is recording... */
            extra = r641_flat_rgba8(2u, 2u, 0, 0, 0);
            ASSERT_TRUE(rhi_handle_valid(extra));
        }
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_mat4(cmd, 64, identity);
        rhi_cmd_set_uniform_mat4(cmd, 128, identity);
        rhi_cmd_set_uniform_vec3(cmd, 192, -0.2f, -0.3f, -0.93f);
        rhi_cmd_set_uniform_vec3(cmd, 208, 0.6f, 0.6f, 0.6f);
        rhi_cmd_set_uniform_vec3(cmd, 224, 0.1f, 0.1f, 0.1f);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
        /* ...then an SRV bind, which takes the next free descriptor slot. */
        rhi_cmd_bind_texture(cmd, white, (RHISampler){0}, 0u);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex,
                                            pass == 0 ? ref : got, sizeof(ref)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    }
    for (i = 0; i < 8 * 8 * 4; ++i) {
        if (got[i] != ref[i])
            printf("  mid-frame upload byte %d = %u, reference %u\n", i, got[i], ref[i]);
        ASSERT_EQ(got[i], ref[i]);
    }
    ASSERT_TRUE(r643_clean("cbv_descriptor_survives_a_mid_frame_upload"));
    rhi_texture_destroy(g_dev, extra);
    rhi_texture_destroy(g_dev, white);
    rhi_buffer_destroy(g_dev, ubo);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* One pipeline, declared with the default RGBA8 colour format, drawing into
 * an RGBA16F FBO, an RGBA8 FBO and the BGRA8 swapchain -- the demo's post
 * chain and UI do exactly this. The PSO bakes its RTV formats, so before
 * R643 two of the three draws ran with a mismatched PSO ([613]) and the
 * swapchain draw also with a D32 depth slot while no DSV was bound ([615]).
 * Each target must hold the blitted colour and the layer must stay silent. */
TEST(one_pipeline_draws_into_rgba16f_rgba8_and_the_swapchain) {
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO hdr, ldr;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHITexture src;
    RHICmdBuffer *cmd;
    u16 h[8 * 8 * 4];
    unsigned char l[8 * 8 * 4];
    static unsigned char sc[64 * 64 * 4];
    int i;
    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "blit_hlsl.frag", 0, true);
    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true; pd.uses_textures = true;
    pd.disable_culling = true; pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u; fd.sample_count = 1u;
    fd.color_format = RHI_FORMAT_R16G16B16A16_SFLOAT;
    hdr = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    ldr = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    src = r641_flat_rgba8(8u, 8u, 51, 102, 204);
    ASSERT_TRUE(rhi_handle_valid(pipe) && rhi_handle_valid(hdr.fb) &&
                rhi_handle_valid(ldr.fb) && rhi_handle_valid(src));
    r643_mark();
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &hdr);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_texture(cmd, src, (RHISampler){0}, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_bind(cmd, &ldr);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_texture(cmd, src, (RHISampler){0}, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_texture(cmd, src, (RHISampler){0}, 0u);
    rhi_cmd_draw(cmd, 3u, 1u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(rhi_screenshot(g_dev, 0u, 0u, 64u, 64u, sc, sizeof(sc)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, hdr.color_tex, h, sizeof(h)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ldr.color_tex, l, sizeof(l)));
    for (i = 0; i < 8 * 8; ++i) {
        if (fabsf(warp_half_to_float(h[i * 4 + 0]) - 0.2f) >= 0.003f ||
            fabsf(warp_half_to_float(h[i * 4 + 2]) - 0.8f) >= 0.003f)
            printf("  rgba16f px %d = %04x %04x %04x %04x | ldr %u %u %u\n", i,
                   h[i * 4], h[i * 4 + 1], h[i * 4 + 2], h[i * 4 + 3],
                   l[i * 4], l[i * 4 + 1], l[i * 4 + 2]);
        ASSERT_TRUE(fabsf(warp_half_to_float(h[i * 4 + 0]) - 0.2f) < 0.003f);
        ASSERT_TRUE(fabsf(warp_half_to_float(h[i * 4 + 2]) - 0.8f) < 0.003f);
        ASSERT_EQ(l[i * 4 + 0], 51);
        ASSERT_EQ(l[i * 4 + 2], 204);
    }
    for (i = 0; i < 64 * 64; ++i) {
        if (sc[i * 4 + 0] != 51 || sc[i * 4 + 1] != 102 || sc[i * 4 + 2] != 204) {
            printf("  swapchain px %d = %u,%u,%u\n", i, sc[i * 4], sc[i * 4 + 1],
                   sc[i * 4 + 2]);
            ASSERT_TRUE(0);
        }
    }
    ASSERT_TRUE(r643_clean("one_pipeline_draws_into_rgba16f_rgba8_and_the_swapchain"));
    rhi_texture_destroy(g_dev, src);
    rhi_offscreen_fbo_destroy(g_dev, &hdr);
    rhi_offscreen_fbo_destroy(g_dev, &ldr);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* The bloom pattern: read A -> write B, read B -> write A, inside one frame.
 * Legal (each bind barriers the resource), but R629's same-frame diagnostic
 * flagged every iteration -- 33 false warnings per 12 demo frames. The R643
 * diagnostic only fires while the texture is still bound to the CURRENT
 * pipeline: the ping-pong stays silent, and binding A's own FBO while A is
 * still in the bound tables does fire. */
TEST(rt_srv_alias_diagnostic_ignores_ping_pong_and_catches_a_live_alias) {
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO a, b;
    RHIShader vs, fs;
    RHIPipeline pipe;
    RHIPipelineDesc pd;
    RHICmdBuffer *cmd;
    UINT64 a0 = 0, a1 = 0;
    int k;
    vs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "blit_hlsl.frag", 0, true);
    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true; pd.uses_textures = true;
    pd.disable_culling = true; pd.depth_write_disable = true;
    pipe = rhi_pipeline_create(g_dev, &pd);
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u; fd.sample_count = 1u;
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    a = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    b = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    ASSERT_TRUE(rhi_handle_valid(pipe) && rhi_handle_valid(a.fb) &&
                rhi_handle_valid(b.fb));
    r643_mark();
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &a);
    rhi_cmd_bind_pipeline(cmd, pipe);
    /* post_process_apply's blur order: ONE pipeline bind, then per pass
     * bind_texture(src) -> fbo_bind(dst) -> draw. Iteration k+1 makes the
     * texture that iteration k read (still in the table) the new source, so
     * it is rebound before its own FBO is bound -- not an alias. */
    for (k = 0; k < 4; ++k) {
        RHIOffscreenFBO *src = (k & 1) ? &b : &a, *dst = (k & 1) ? &a : &b;
        rhi_cmd_bind_texture(cmd, src->color_tex, (RHISampler){0}, 0u);
        rhi_offscreen_fbo_bind(cmd, dst);
        rhi_cmd_draw(cmd, 3u, 1u);
    }
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(r643_clean("ping-pong"));
    /* A texture bound under the PREVIOUS pipeline is not bound any more once
     * the pipeline changes (the root signature drops its tables), so making
     * it a render target afterwards is legal and must stay silent too. */
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_texture(cmd, a.color_tex, (RHISampler){0}, 0u);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_offscreen_fbo_bind(cmd, &a);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(r643_clean("rebind drops the table"));
    /* Now the real alias, without drawing (the draw itself would be the
     * undefined read/write): A stays in the tables while A's FBO is bound. */
    (void)rhi_d3d12_debug_layer_counts(g_dev, NULL, NULL, &a0);
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_cmd_bind_pipeline(cmd, pipe);
    rhi_cmd_bind_texture(cmd, a.color_tex, (RHISampler){0}, 0u);
    rhi_offscreen_fbo_bind(cmd, &a);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    (void)rhi_d3d12_debug_layer_counts(g_dev, NULL, NULL, &a1);
    ASSERT_EQ(a1 - a0, 1u);
    /* Nothing above read back, so the GPU may still be running these frames;
     * D3D12 destroy releases at once (the other tests drain through
     * rhi_texture_read_pixels). Without this the release raced the GPU
     * ([921], and an intermittent crash). */
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);
    rhi_offscreen_fbo_destroy(g_dev, &a);
    rhi_offscreen_fbo_destroy(g_dev, &b);
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* ---- R645: deferred release of resources still referenced by the GPU ----
 * The UI canvas grows its vertex buffers mid-frame: ensure_vbo destroys the
 * buffers the frame has already drawn from and creates bigger ones. D3D12
 * released the old resource at once, while the recorded command list (and
 * the previous, possibly still running submission) referenced it -- debug
 * layer [921], and the demo intermittently hung or crashed. Here a frame
 * draws from a buffer, destroys it (and a texture and a pipeline it used)
 * before the frame is submitted, then draws again with fresh objects. The
 * pixels must be those of the second draw and the debug layer must stay
 * silent; before R645 this reported [921] on every run. */
TEST(destroying_objects_mid_frame_is_deferred_until_the_gpu_is_done) {
    static const float quad[6 * 3] = {
        -1,-1,0,  1,-1,0,  1,1,0,  -1,-1,0,  1,1,0,  -1,1,0
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs, bvs, bfs;
    RHIPipelineDesc pd;
    RHIPipeline pipe, blit;
    RHIBufferDesc bd;
    RHIBuffer vbo;
    RHITexture tex;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    int pass, i;
    r643_mark();
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u;
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM; fd.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    vs = rhi_shader_create(g_dev, "probe_vb_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "probe_vb_hlsl.frag", 0, true);
    bvs = rhi_shader_create(g_dev, "post_hlsl.vert", 0, false);
    bfs = rhi_shader_create(g_dev, "blit_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb) && rhi_handle_valid(vs) && rhi_handle_valid(fs) &&
                rhi_handle_valid(bvs) && rhi_handle_valid(bfs));
    for (pass = 0; pass < 3; ++pass) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        for (i = 0; i < 2; ++i) {
            /* Fresh objects for each draw, destroyed right after it while the
             * frame is still recording. */
            memset(&pd, 0, sizeof(pd));
            pd.vert = vs; pd.frag = fs;
            pd.vertex_stride = 12u;
            pd.disable_culling = true; pd.depth_write_disable = true;
            pipe = rhi_pipeline_create(g_dev, &pd);
            memset(&bd, 0, sizeof(bd));
            bd.size = sizeof(quad); bd.usage = RHI_BUFFER_USAGE_VERTEX;
            bd.initial_data = quad;
            vbo = rhi_buffer_create(g_dev, &bd);
            ASSERT_TRUE(rhi_handle_valid(pipe) && rhi_handle_valid(vbo));
            rhi_cmd_bind_pipeline(cmd, pipe);
            rhi_cmd_push_constants(cmd, 0u, identity, sizeof(identity));
            rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
            rhi_cmd_draw(cmd, 6u, 1u);
            rhi_buffer_destroy(g_dev, vbo);
            rhi_pipeline_destroy(g_dev, pipe);
        }
        /* A texture sampled by this frame, destroyed before submission. */
        tex = r641_flat_rgba8(2u, 2u, 30, 60, 90);
        memset(&pd, 0, sizeof(pd));
        pd.vert = bvs; pd.frag = bfs;
        pd.no_vertex_input = true; pd.uses_textures = true;
        pd.disable_culling = true; pd.depth_write_disable = true;
        blit = rhi_pipeline_create(g_dev, &pd);
        ASSERT_TRUE(rhi_handle_valid(tex) && rhi_handle_valid(blit));
        rhi_cmd_bind_pipeline(cmd, blit);
        rhi_cmd_bind_texture(cmd, tex, (RHISampler){0}, 0u);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_texture_destroy(g_dev, tex);
        rhi_pipeline_destroy(g_dev, blit);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    }
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (i = 0; i < 8 * 8; ++i) {
        ASSERT_EQ(px[i * 4 + 0], 30);
        ASSERT_EQ(px[i * 4 + 1], 60);
        ASSERT_EQ(px[i * 4 + 2], 90);
    }
    ASSERT_TRUE(r643_clean("destroying_objects_mid_frame"));
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    rhi_shader_destroy(g_dev, vs); rhi_shader_destroy(g_dev, fs);
    rhi_shader_destroy(g_dev, bvs); rhi_shader_destroy(g_dev, bfs);
}

/* R647: the point-shadow cube, end to end on the real PointShadowSystem.
 * Every face gets an occluder that covers only its face-space quadrant
 * s < 0.5, t < 0.5, at plane distance 2 from the light. cube_probe_hlsl
 * then reads each face back BY DIRECTION through a TextureCube view, the
 * way the lighting pass does. A face rendered rotated or mirrored puts the
 * occluder in another quadrant; a missing SRV/DSV path reads 1.0 or junk;
 * the shader writing rasterised depth instead of distance / far gets the
 * value wrong. Expected texel = 2 |d| / far for the probe direction d. */
static void r647_dir(int f, float a, float b, float d[3]) {
    switch (f) {
    case 0:  d[0] =  1.0f; d[1] = -b;    d[2] = -a;    break;
    case 1:  d[0] = -1.0f; d[1] = -b;    d[2] =  a;    break;
    case 2:  d[0] =  a;    d[1] =  1.0f; d[2] =  b;    break;
    case 3:  d[0] =  a;    d[1] = -1.0f; d[2] = -b;    break;
    case 4:  d[0] =  a;    d[1] = -b;    d[2] =  1.0f; break;
    default: d[0] = -a;    d[1] = -b;    d[2] = -1.0f; break;
    }
}
TEST(point_shadow_cube_faces_read_back_by_direction) {
    static const float corner[6][2] = {
        {-1,-1}, {0,-1}, {0,0},  {-1,-1}, {0,0}, {-1,0}
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    static PointShadowSystem ps;
    static float verts[6 * 12 * 8];
    const float light[3] = { 0.5f, -0.25f, 1.0f };
    const float far_plane = 10.0f;
    Vec3 lp;
    f32 radius = far_plane;
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO fbo;
    RHIShader vs, fs;
    RHIPipelineDesc pd;
    RHIPipeline probe;
    RHIBufferDesc bd;
    RHIBuffer vbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    i32 loc_face;
    int f, k, x, y, dark = 0;
    r643_mark();
    for (f = 0; f < 6; ++f) {
        for (k = 0; k < 12; ++k) {
            /* Both windings, so back-face culling cannot hide the quad. */
            int c = k < 6 ? k : 5 - (k - 6);
            float d[3];
            float *v = &verts[((size_t)f * 12u + (size_t)k) * 8u];
            r647_dir(f, corner[c][0], corner[c][1], d);
            v[0] = light[0] + 2.0f * d[0];
            v[1] = light[1] + 2.0f * d[1];
            v[2] = light[2] + 2.0f * d[2];
        }
    }
    memset(&ps, 0, sizeof(ps));
    point_shadow_init(&ps, g_dev, 8u);
    ASSERT_TRUE(ps.ready);
    ASSERT_EQ(ps.loc_model, 0);
    ASSERT_EQ(ps.loc_mvp, 64);
    ASSERT_EQ(ps.loc_light_pos, 128);
    ASSERT_EQ(ps.loc_far_plane, 144);
    lp.e[0] = light[0]; lp.e[1] = light[1]; lp.e[2] = light[2];
    point_shadow_update(&ps, &lp, &radius, 1u, lp);
    ASSERT_EQ(ps.active_count, 1u);

    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u; fd.sample_count = 1u;
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    vs = rhi_shader_create(g_dev, "shadow_sample_hlsl.vert", 0, false);
    fs = rhi_shader_create(g_dev, "cube_probe_hlsl.frag", 0, true);
    memset(&pd, 0, sizeof(pd));
    pd.vert = vs; pd.frag = fs;
    pd.no_vertex_input = true;
    pd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    pd.depth_write_disable = true;
    probe = rhi_pipeline_create(g_dev, &pd);
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb) && rhi_handle_valid(probe) &&
                rhi_handle_valid(vbo));
    loc_face = rhi_pipeline_get_uniform_location(g_dev, probe, "u_face");
    ASSERT_EQ(loc_face, 64);

    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    for (f = 0; f < 6; ++f) {
        point_shadow_render_begin(&ps, cmd, 0u, (u32)f);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, (usize)f * 12u * 8u * sizeof(float));
        rhi_cmd_draw(cmd, 12u, 1u);
    }
    point_shadow_render_end(&ps, cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);

    for (f = 0; f < 6; ++f) {
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        rhi_cmd_bind_pipeline(cmd, probe);
        rhi_cmd_set_uniform_mat4(cmd, 0, identity);
        rhi_cmd_set_uniform_vec4(cmd, loc_face, (float)f, 0.0f, 0.0f, 0.0f);
        rhi_cmd_bind_texture(cmd, ps.cubemap_fbos[0].depth_tex, ps.sampler, 10u);
        rhi_cmd_draw(cmd, 3u, 1u);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        memset(px, 0, sizeof(px));
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
        for (y = 0; y < 8; ++y) {
            for (x = 0; x < 8; ++x) {
                const unsigned char got = px[(y * 8 + x) * 4];
                int want = 255;
                if (x < 4 && y < 4) {
                    float d[3];
                    r647_dir(f, (x + 0.5f) / 4.0f - 1.0f,
                             (y + 0.5f) / 4.0f - 1.0f, d);
                    want = (int)(2.0f * sqrtf(d[0] * d[0] + d[1] * d[1] +
                                              d[2] * d[2]) / far_plane *
                                 255.0f + 0.5f);
                    ++dark;
                }
                if (abs((int)got - want) > 2)
                    printf("FAIL: face %d texel (%d,%d) = %u, expected %d\n",
                           f, x, y, (unsigned)got, want);
                ASSERT_TRUE(abs((int)got - want) <= 2);
            }
        }
    }
    ASSERT_EQ(dark, 6 * 16);
    ASSERT_TRUE(r643_clean("point_shadow_cube"));
    rhi_buffer_destroy(g_dev, vbo);
    rhi_pipeline_destroy(g_dev, probe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    point_shadow_destroy(&ps, g_dev);
}

/* R647: the deferred lighting pass samples the point-shadow cube. Same
 * G-Buffer plane as the BRDF test (world == NDC, z = -0.5) and its point
 * light at (0.5, 0.5, 0) with radius 1.5. An occluder plane at z = -0.25,
 * x < 0.5, is drawn into the light's cube; the ray from the light to a
 * surface point crosses z = -0.25 halfway, at x = 0.5 + (w.x - 0.5) / 2, so
 * exactly the columns with w.x < 0.5 (x <= 5) are shadowed.
 *
 * Four frames: A no point light, B an empty cube, C the occluder, D no cube
 * at all (psc_count 0, so t10 gets the 1.0 fallback). In linear space (the
 * pass ends with c / (c + 1)) the point light's share is B - A; the shadow
 * multiplies it by 0.15 (C - A), the lit columns keep it (C == B), and the
 * fallback must read as unshadowed (D == B). */
static double r647_lin(u16 h) {
    double t = warp_half_to_float(h);
    return t / (1.0 - t);
}
TEST(deferred_lighting_samples_the_point_shadow_cube) {
    static const float verts[3 * 8] = {
        -1.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         3.0f, -1.0f, -0.5f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f,
        -1.0f,  3.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f
    };
    static const float occ[12 * 8] = {
        -3.0f, -3.0f, -0.25f,0,0,0,0,0,  0.5f, -3.0f, -0.25f,0,0,0,0,0,
         0.5f,  3.0f, -0.25f,0,0,0,0,0, -3.0f, -3.0f, -0.25f,0,0,0,0,0,
         0.5f,  3.0f, -0.25f,0,0,0,0,0, -3.0f,  3.0f, -0.25f,0,0,0,0,0,
        -3.0f,  3.0f, -0.25f,0,0,0,0,0,  0.5f,  3.0f, -0.25f,0,0,0,0,0,
        -3.0f, -3.0f, -0.25f,0,0,0,0,0,  0.5f,  3.0f, -0.25f,0,0,0,0,0,
         0.5f, -3.0f, -0.25f,0,0,0,0,0, -3.0f, -3.0f, -0.25f,0,0,0,0,0
    };
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    static Mat4 cascades[4];
    static LightSystem ls;
    static PointShadowSystem ps;
    static u16 px[4][8 * 8 * 4];
    DeferredSystem ds;
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO out;
    RHIBufferDesc bd;
    RHIBuffer vbo, ovbo;
    RHITexture t[5];
    RHICmdBuffer *cmd;
    Mat4 view_m, proj_m;
    Vec3 lp = {{0.5f, 0.5f, 0.0f}};
    f32 radius = 1.5f;
    float cam[19];
    int frame, x, y, c, i, shadowed = 0, lit = 0;
    r643_mark();
    memset(&ds, 0, sizeof(ds));
    deferred_init(&ds, g_dev, 8u, 8u);
    ASSERT_TRUE(ds.initialized);
    memset(&ps, 0, sizeof(ps));
    point_shadow_init(&ps, g_dev, 64u);
    ASSERT_TRUE(ps.ready);
    point_shadow_update(&ps, &lp, &radius, 1u, lp);
    ASSERT_EQ(ps.active_count, 1u);
    t[0] = r644_tex(200, 100, 50, 255);
    t[1] = r644_tex(0, 204, 153, 255);
    t[2] = r644_tex(128, 128, 255, 255);
    t[3] = r644_tex(51, 102, 153, 255);
    t[4] = r644_tex(102, 0, 0, 255);
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    bd.size = sizeof(occ); bd.initial_data = occ;
    ovbo = rhi_buffer_create(g_dev, &bd);
    memset(&fd, 0, sizeof(fd));
    fd.width = 8u; fd.height = 8u; fd.sample_count = 1u;
    fd.color_format = RHI_FORMAT_R16G16B16A16_SFLOAT;
    out = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    ASSERT_TRUE(rhi_handle_valid(vbo) && rhi_handle_valid(ovbo) &&
                rhi_handle_valid(out.fb));
    memset(&ls, 0, sizeof(ls));
    light_system_init(&ls, g_dev);
    for (i = 0; i < 4; ++i) memcpy(cascades[i].e, identity, sizeof(identity));
    light_system_set_cascade_vp(&ls, cascades);
    memcpy(view_m.e, identity, sizeof(identity));
    memcpy(proj_m.e, identity, sizeof(identity));
    memcpy(cam, identity, sizeof(identity));
    cam[16] = 0.0f; cam[17] = 0.0f; cam[18] = 3.0f;
    for (frame = 0; frame < 4; ++frame) {
        light_system_clear(&ls);
        light_system_add_dir(&ls, 0.0f, 0.0f, -1.0f, 0.9f, 0.8f, 0.7f);
        if (frame != 0)
            light_system_add_point(&ls, 0.5f, 0.5f, 0.0f, 1.5f, 3.0f, 2.0f, 1.0f);
        light_system_set_point_shadow_indices(&ls, &ps);
        light_system_set_depth_range(&ls, 0.1f, 100.0f);
        light_system_cull(&ls, &view_m, &proj_m, 8u, 8u);
        light_system_upload(&ls);
        cmd = rhi_frame_begin(g_dev);
        ASSERT_TRUE(cmd != NULL);
        for (i = 0; i < 6; ++i) {
            point_shadow_render_begin(&ps, cmd, 0u, (u32)i);
            if (frame == 2) {
                rhi_cmd_bind_vertex_buffer(cmd, ovbo, 0u);
                rhi_cmd_draw(cmd, 12u, 1u);
            }
        }
        point_shadow_render_end(&ps, cmd, 64u, 64u);
        r644_gbuffer_frame(&ds, cmd, vbo, identity, t);
        rhi_offscreen_fbo_bind(cmd, &out);
        deferred_lighting_pass(&ds, g_dev, cmd, light_system_data_slot(&ls),
                               light_system_grid_slot(&ls), ls.point_count, ls.dir_count,
                               RHI_HANDLE_NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                               RHI_HANDLE_NULL,
                               frame == 3 ? 0u : 1u,
                               frame == 3 ? NULL : &ps.cubemap_fbos[0].depth_tex,
                               ps.far_planes, 0.1f, 100.0f, 0.002f, identity, cam,
                               RHI_HANDLE_NULL);
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_TRUE(rhi_texture_read_pixels(g_dev, out.color_tex, px[frame],
                                            sizeof(px[frame])));
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    }
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            int idx = (y * 8 + x) * 4;
            double share = r647_lin(px[1][idx]) - r647_lin(px[0][idx]);
            for (c = 0; c < 3; ++c) {
                double a = r647_lin(px[0][idx + c]);
                double b = r647_lin(px[1][idx + c]);
                double cc = r647_lin(px[2][idx + c]);
                double d = r647_lin(px[3][idx + c]);
                double want = x <= 5 ? a + 0.15 * (b - a) : b;
                double tol = 0.01 + 0.02 * fabs(want);
                if (fabs(d - b) > tol || fabs(cc - want) > tol)
                    printf("  point shadow px (%d,%d) ch %d: A %f B %f C %f "
                           "(want %f) D %f\n", x, y, c, a, b, cc, want, d);
                ASSERT_TRUE(fabs(d - b) <= tol);
                ASSERT_TRUE(fabs(cc - want) <= tol);
            }
            if (share > 0.05) {
                if (x <= 5) ++shadowed; else ++lit;
            }
        }
    }
    /* Both sides of the occluder edge carry real point light, or the test
     * proves nothing about where the shadow falls. */
    ASSERT_TRUE(shadowed >= 6 && lit >= 4);
    ASSERT_TRUE(r643_clean("deferred_point_shadow"));
    light_system_shutdown(&ls);
    for (i = 0; i < 5; ++i) rhi_texture_destroy(g_dev, t[i]);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, ovbo);
    rhi_offscreen_fbo_destroy(g_dev, &out);
    point_shadow_destroy(&ps, g_dev);
    deferred_destroy(&ds, g_dev);
}

/* R649: the skinned G-Buffer sidecar. A half-screen quad (NDC x in [-1, 0])
 * weighted 0.5 / 0.5 on joints 1 and 2. Joint 1 translates +1.0 in x and
 * joint 2 is the identity, so the blended skin moves the quad +0.5: it must
 * cover x in [-0.5, 0.5], i.e. columns 2..5 of an 8-wide target. Both
 * previous poses are the identity and u_prev_mvp is identity, so the
 * velocity is exactly +0.5 in x and 0 in y. u_model scales y by 1 (but
 * offsets nothing) and u_vp is identity; the albedo is the material binder's
 * t0 texture. What this pins: the joint fetch (indices and transpose), the
 * weight blend, the 512-texel previous-pose offset, and the u_vp fold. */
TEST(deferred_gbuffer_skinned_sidecar_skins_and_writes_velocity) {
    typedef struct { f32 pos[3]; f32 nrm[3]; f32 uv[2]; u32 joints[4];
                     f32 weights[4]; } SkinVert;
#define R649_V(x, y) { { x, y, -0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, \
                       { 1u, 2u, 0u, 0u }, { 0.5f, 0.5f, 0.0f, 0.0f } }
    static const SkinVert verts[6] = {
        R649_V(-1.0f, -1.0f), R649_V(0.0f, -1.0f), R649_V(0.0f, 1.0f),
        R649_V(-1.0f, -1.0f), R649_V(0.0f, 1.0f), R649_V(-1.0f, 1.0f)
    };
#undef R649_V
    static const float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    static float joints[(512 + 12) * 4];
    static u8 rt0[8 * 8 * 4];
    static u16 rt3[8 * 8 * 4];
    DeferredSystem ds;
    RHIBufferDesc bd;
    RHIBuffer vbo, jbo;
    RHITexture t[5];
    RHICmdBuffer *cmd;
    int x, y, j, i;
    r643_mark();
    memset(joints, 0, sizeof(joints));
    for (j = 0; j < 3; ++j) {
        float *cur = &joints[j * 16];
        float *prev = &joints[(512 + j * 4) * 4];
        cur[0] = cur[5] = cur[10] = cur[15] = 1.0f;
        prev[0] = prev[5] = prev[10] = prev[15] = 1.0f;
    }
    joints[1 * 16 + 12] = 1.0f;   /* joint 1: column 3 = translation (+1, 0, 0) */
    memset(&ds, 0, sizeof(ds));
    deferred_init(&ds, g_dev, 8u, 8u);
    ASSERT_TRUE(ds.initialized);
    ASSERT_TRUE(rhi_handle_valid(ds.gbuffer_skinned_pipeline));
    ASSERT_EQ(ds._loc_gbuf_skinned_model, 0);
    ASSERT_EQ(ds._loc_gbuf_skinned_vp, 64);
    ASSERT_EQ(ds._loc_gbuf_skinned_prev_mvp, 128);
    ASSERT_EQ(ds._loc_gbuf_skinned_view, -1);
    ASSERT_EQ(ds._loc_gbuf_skinned_proj, -1);
    t[0] = r644_tex(200, 100, 50, 255);
    t[1] = r644_tex(0, 204, 153, 255);
    t[2] = r644_tex(128, 128, 255, 255);
    t[3] = r644_tex(0, 0, 0, 255);
    t[4] = r644_tex(255, 0, 0, 255);
    memset(&bd, 0, sizeof(bd));
    bd.size = sizeof(verts); bd.usage = RHI_BUFFER_USAGE_VERTEX;
    bd.initial_data = verts;
    vbo = rhi_buffer_create(g_dev, &bd);
    bd.size = sizeof(joints); bd.initial_data = joints;
    jbo = rhi_buffer_create(g_dev, &bd);
    ASSERT_TRUE(rhi_handle_valid(vbo) && rhi_handle_valid(jbo));
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    deferred_begin_gbuffer(&ds, g_dev, cmd);
    rhi_cmd_bind_pipeline(cmd, ds.gbuffer_skinned_pipeline);
    rhi_cmd_set_uniform_mat4(cmd, ds._loc_gbuf_skinned_model, identity);
    rhi_cmd_set_uniform_mat4(cmd, ds._loc_gbuf_skinned_vp, identity);
    rhi_cmd_set_uniform_mat4(cmd, ds._loc_gbuf_skinned_prev_mvp, identity);
    rhi_cmd_bind_material_textures_ibl(cmd, t[0], t[1], t[2], t[3], t[4],
                                        RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                                        (RHISampler){0}, RHI_HANDLE_NULL,
                                        RHI_HANDLE_NULL, RHI_HANDLE_NULL, NULL, 0u);
    deferred_bind_gbuffer_factors(&ds, g_dev, cmd, 1.0f, 1.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f);
    rhi_cmd_bind_texel_buffers(cmd, jbo, jbo);
    rhi_cmd_bind_vertex_buffer(cmd, vbo, 0u);
    rhi_cmd_draw(cmd, 6u, 1u);
    deferred_end_gbuffer(&ds, g_dev, cmd);
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_albedo_metallic, rt0, sizeof(rt0)));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, ds.gbuf_velocity, rt3, sizeof(rt3)));
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    for (y = 0; y < 8; ++y) {
        for (x = 0; x < 8; ++x) {
            int in = x >= 2 && x <= 5;
            i = (y * 8 + x) * 4;
            if ((rt0[i] == 200) != in)
                printf("  skinned gbuf px (%d,%d) albedo r = %u, covered %d\n",
                       x, y, (unsigned)rt0[i], in);
            ASSERT_TRUE((rt0[i] == 200) == in);
            if (in) {
                ASSERT_EQ(rt0[i + 1], 100);
                ASSERT_EQ(rt0[i + 2], 50);
                ASSERT_TRUE(fabsf(warp_half_to_float(rt3[i + 0]) - 0.5f) < 0.002f);
                ASSERT_TRUE(fabsf(warp_half_to_float(rt3[i + 1])) < 0.002f);
            }
        }
    }
    ASSERT_TRUE(r643_clean("gbuffer_skinned"));
    for (i = 0; i < 5; ++i) rhi_texture_destroy(g_dev, t[i]);
    rhi_buffer_destroy(g_dev, vbo);
    rhi_buffer_destroy(g_dev, jbo);
    deferred_destroy(&ds, g_dev);
}

/* The whole post chain this suite exercises must have run clean under the
 * debug layer (when it is compiled in). Placed last, it covers every test
 * above: a regression anywhere in the backend's state tracking shows up here
 * even if the pixels happen to survive it. */
TEST(debug_layer_reported_nothing_for_the_whole_suite) {
    UINT64 e = 0, w = 0, a = 0;
    int on = rhi_d3d12_debug_layer_counts(g_dev, &e, &w, &a);
    printf("  (debug layer %s: %llu errors, %llu warnings, %llu aliases) ",
           on ? "on" : "off", (unsigned long long)e, (unsigned long long)w,
           (unsigned long long)a);
    ASSERT_EQ(e, 0u);
    ASSERT_EQ(w, 0u);
    /* Exactly the one deliberate alias above. */
    ASSERT_EQ(a, 1u);
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
    RUN_TEST(indirect_draw_system_compacts_and_draws_on_the_gpu);
    RUN_TEST(post_process_initialises_and_blits_on_d3d12);
    RUN_TEST(tonemap_and_luminance_sidecars_match_the_aces_formula);
    RUN_TEST(offscreen_fbo_budget_covers_the_demo_post_chain);
    RUN_TEST(swapchain_draws_put_ndc_up_at_the_top_of_the_screen);
    RUN_TEST(scene_through_offscreen_and_final_blit_keeps_ndc_up_on_top);
    RUN_TEST(engine_camera_puts_world_up_at_the_top_of_the_screen);
    RUN_TEST(graphics_push_constants_survive_a_compute_pass_and_rebind);
    RUN_TEST(texel_buffer_rewritten_per_draw_feeds_each_draw_its_own_rows);
    RUN_TEST(ssao_sidecars_occlude_a_jittered_plane_and_blur_it);
    RUN_TEST(sharpen_sidecar_matches_the_cas_formula_on_interior_pixels);
    RUN_TEST(god_rays_sidecar_scatters_sky_and_passes_occluded_scene);
    RUN_TEST(cinematic_sidecar_applies_the_exact_vignette_without_grain);
    RUN_TEST(sss_sidecars_blur_only_where_depth_is_continuous);
    RUN_TEST(upscale_sidecar_copies_flat_input_and_clips_history);
    RUN_TEST(volumetric_sidecar_extincts_the_scene_by_the_marched_fog);
    RUN_TEST(debug_viz_sidecar_renders_every_mode_from_the_shader_formulas);
    RUN_TEST(combined_color_sidecar_matches_the_fused_tonemap_grade_vignette);
    RUN_TEST(combined_aa_sidecar_reprojects_history_and_matches_fxaa);
    RUN_TEST(deferred_gbuffer_sidecar_writes_all_five_targets);
    RUN_TEST(deferred_lighting_sidecar_matches_the_brdf_and_csm_and_clusters);
    RUN_TEST(deferred_lighting_reads_a_larger_gbuffer_by_uv);
    RUN_TEST(deferred_path_with_a_perspective_camera_matches_a_replay);
    RUN_TEST(uniform_buffer_survives_a_pipeline_change);
    RUN_TEST(cbv_descriptor_survives_a_mid_frame_upload);
    RUN_TEST(one_pipeline_draws_into_rgba16f_rgba8_and_the_swapchain);
    RUN_TEST(rt_srv_alias_diagnostic_ignores_ping_pong_and_catches_a_live_alias);
    RUN_TEST(destroying_objects_mid_frame_is_deferred_until_the_gpu_is_done);
    RUN_TEST(point_shadow_cube_faces_read_back_by_direction);
    RUN_TEST(deferred_lighting_samples_the_point_shadow_cube);
    RUN_TEST(deferred_gbuffer_skinned_sidecar_skins_and_writes_velocity);
    RUN_TEST(debug_layer_reported_nothing_for_the_whole_suite);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
