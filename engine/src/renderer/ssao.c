#include <renderer/ssao.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ssao_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

static RHIPipeline ssao_create_pipe(RHIDevice *dev,
                                      const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = ssao_read_file(vert_path, &vs_len);
    char *fs_src = ssao_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("SSAO: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("SSAO: shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }

    RHIPipelineDesc pdesc = {
        .vert = vs, .frag = fs,
        .no_vertex_input = true,
        .uses_textures = true,
        .depth_write_disable = true,
        .disable_culling = true,
    };
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

bool ssao_init(SSAOSystem *ssao, RHIDevice *dev, u32 width, u32 height) {
    memset(ssao, 0, sizeof(*ssao));
    ssao->device = dev;
    ssao->radius = 0.5f;
    ssao->bias = 0.025f;

#ifdef ENGINE_VULKAN
    ssao->ssao_pipe = ssao_create_pipe(dev, "shaders/post_vk.vert", "shaders/ssao_vk.frag");
    ssao->blur_pipe = ssao_create_pipe(dev, "shaders/post_vk.vert", "shaders/ssao_blur_vk.frag");
#else
    ssao->ssao_pipe = ssao_create_pipe(dev, "shaders/post.vert", "shaders/ssao.frag");
    ssao->blur_pipe = ssao_create_pipe(dev, "shaders/post.vert", "shaders/ssao_blur.frag");
#endif

    if (!rhi_handle_valid(ssao->ssao_pipe) || !rhi_handle_valid(ssao->blur_pipe)) {
        LOG_WARN("SSAO: pipeline creation failed");
        return false;
    }

    ssao->ssao_fbo = rhi_offscreen_fbo_create(dev, width / 2, height / 2);
    ssao->blur_fbo = rhi_offscreen_fbo_create(dev, width / 2, height / 2);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    ssao->sampler = rhi_sampler_create(dev, &sdesc);

    ssao->loc_proj = rhi_pipeline_get_uniform_location(dev, ssao->ssao_pipe, "u_ssao_proj");
    ssao->loc_inv_proj = rhi_pipeline_get_uniform_location(dev, ssao->ssao_pipe, "u_ssao_inv_proj");
    ssao->loc_screen_w = rhi_pipeline_get_uniform_location(dev, ssao->ssao_pipe, "u_ssao_sw");
    ssao->loc_screen_h = rhi_pipeline_get_uniform_location(dev, ssao->ssao_pipe, "u_ssao_sh");
    ssao->loc_radius = rhi_pipeline_get_uniform_location(dev, ssao->ssao_pipe, "u_ssao_radius");
    ssao->loc_bias = rhi_pipeline_get_uniform_location(dev, ssao->ssao_pipe, "u_ssao_bias");

    ssao->ready = true;
    LOG_INFO("SSAO: initialized (%ux%u, radius=%.2f)", width / 2, height / 2, ssao->radius);
    return true;
}

void ssao_shutdown(SSAOSystem *ssao) {
    if (!ssao->device) return;
    if (rhi_handle_valid(ssao->blur_fbo.fb)) rhi_offscreen_fbo_destroy(ssao->device, &ssao->blur_fbo);
    if (rhi_handle_valid(ssao->ssao_fbo.fb)) rhi_offscreen_fbo_destroy(ssao->device, &ssao->ssao_fbo);
    if (rhi_handle_valid(ssao->sampler)) rhi_sampler_destroy(ssao->device, ssao->sampler);
    if (rhi_handle_valid(ssao->blur_pipe)) rhi_pipeline_destroy(ssao->device, ssao->blur_pipe);
    if (rhi_handle_valid(ssao->ssao_pipe)) rhi_pipeline_destroy(ssao->device, ssao->ssao_pipe);
    ssao->ready = false;
}

void ssao_apply(SSAOSystem *ssao, RHICmdBuffer *cmd, RHITexture depth_tex,
                const f32 *proj, const f32 *inv_proj, u32 screen_w, u32 screen_h) {
    if (!ssao->ready) return;

    rhi_cmd_end_render_pass(cmd);
    rhi_cmd_transition_depth_to_read(cmd, depth_tex);

    /* ---- SSAO pass ---- */
    rhi_offscreen_fbo_bind(cmd, &ssao->ssao_fbo);

    rhi_cmd_bind_pipeline(cmd, ssao->ssao_pipe);
    rhi_cmd_bind_texture(cmd, depth_tex, ssao->sampler, 0);

    if (ssao->loc_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, ssao->loc_proj, proj);
    if (ssao->loc_inv_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, ssao->loc_inv_proj, inv_proj);
    if (ssao->loc_screen_w >= 0) rhi_cmd_set_uniform_f32(cmd, ssao->loc_screen_w, (f32)screen_w);
    if (ssao->loc_screen_h >= 0) rhi_cmd_set_uniform_f32(cmd, ssao->loc_screen_h, (f32)screen_h);
    if (ssao->loc_radius >= 0) rhi_cmd_set_uniform_f32(cmd, ssao->loc_radius, ssao->radius);
    if (ssao->loc_bias >= 0) rhi_cmd_set_uniform_f32(cmd, ssao->loc_bias, ssao->bias);

    rhi_cmd_draw(cmd, 3, 1);

    /* ---- Blur pass ---- */
    rhi_offscreen_fbo_bind(cmd, &ssao->blur_fbo);

    rhi_cmd_bind_pipeline(cmd, ssao->blur_pipe);
    rhi_cmd_bind_texture(cmd, ssao->ssao_fbo.color_tex, ssao->sampler, 0);

    rhi_cmd_draw(cmd, 3, 1);

    rhi_offscreen_fbo_unbind(cmd, screen_w, screen_h);
}

RHITexture ssao_get_texture(SSAOSystem *ssao) {
    return ssao->ready ? ssao->blur_fbo.color_tex : RHI_HANDLE_NULL;
}
