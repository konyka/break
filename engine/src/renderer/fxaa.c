#include "fxaa.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>

static char *fxaa_read_file(const char *path, usize *out_len) {
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

static RHIPipeline fxaa_create_pipe(RHIDevice *dev,
                                     const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = fxaa_read_file(vert_path, &vs_len);
    char *fs_src = fxaa_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("FXAA: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("FXAA: shader compile failed");
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

bool fxaa_init(FXAASystem *fxaa, RHIDevice *dev, u32 width, u32 height) {
    if (!fxaa || !dev) return false;
    fxaa->device = dev;

#ifdef ENGINE_VULKAN
    fxaa->fxaa_pipe = fxaa_create_pipe(dev, "shaders/post_vk.vert", "shaders/fxaa_vk.frag");
#else
    fxaa->fxaa_pipe = fxaa_create_pipe(dev, "shaders/post.vert", "shaders/fxaa.frag");
#endif

    if (!rhi_handle_valid(fxaa->fxaa_pipe)) {
        LOG_WARN("FXAA: pipeline creation failed");
        return false;
    }

    fxaa->fxaa_fbo = rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    fxaa->sampler = rhi_sampler_create(dev, &sdesc);

    fxaa->loc_screen_w = rhi_pipeline_get_uniform_location(dev, fxaa->fxaa_pipe, "u_fxaa_sw");
    fxaa->loc_screen_h = rhi_pipeline_get_uniform_location(dev, fxaa->fxaa_pipe, "u_fxaa_sh");
    fxaa->loc_threshold = rhi_pipeline_get_uniform_location(dev, fxaa->fxaa_pipe, "u_fxaa_threshold");
    fxaa->threshold = 0.0312f;

    fxaa->ready = true;
    LOG_INFO("FXAA: initialized (%ux%u)", width, height);
    return true;
}

void fxaa_shutdown(FXAASystem *fxaa) {
    if (!fxaa->device) return;
    if (rhi_handle_valid(fxaa->fxaa_fbo.fb)) rhi_offscreen_fbo_destroy(fxaa->device, &fxaa->fxaa_fbo);
    if (rhi_handle_valid(fxaa->sampler))     rhi_sampler_destroy(fxaa->device, fxaa->sampler);
    if (rhi_handle_valid(fxaa->fxaa_pipe))   rhi_pipeline_destroy(fxaa->device, fxaa->fxaa_pipe);
    fxaa->ready = false;
}

void fxaa_apply(FXAASystem *fxaa, RHICmdBuffer *cmd,
                RHITexture input_tex, u32 screen_w, u32 screen_h) {
    if (!fxaa->ready) return;

    rhi_offscreen_fbo_bind(cmd, &fxaa->fxaa_fbo);

    rhi_cmd_bind_pipeline(cmd, fxaa->fxaa_pipe);
    rhi_cmd_bind_texture(cmd, input_tex, fxaa->sampler, 0);

    if (fxaa->loc_screen_w >= 0) rhi_cmd_set_uniform_f32(cmd, fxaa->loc_screen_w, (f32)screen_w);
    if (fxaa->loc_screen_h >= 0) rhi_cmd_set_uniform_f32(cmd, fxaa->loc_screen_h, (f32)screen_h);
    if (fxaa->loc_threshold >= 0) rhi_cmd_set_uniform_f32(cmd, fxaa->loc_threshold, fxaa->threshold);

    rhi_cmd_draw(cmd, 3, 1);
}

RHITexture fxaa_get_texture(FXAASystem *fxaa) {
    if (!fxaa->ready) return RHI_HANDLE_NULL;
    return fxaa->fxaa_fbo.color_tex;
}
