#include "tonemap.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>

static char *tm_read_file(const char *path, usize *out_len) {
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

static RHIPipeline tm_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = tm_read_file(vert_path, &vs_len);
    char *fs_src = tm_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("Tonemap: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Tonemap: shader compile failed");
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

bool tonemap_init(TonemapSystem *tm, RHIDevice *dev) {
    if (!tm || !dev) return false;
    tm->device = dev;
    tm->exposure = 1.5f;
    tm->gamma = 2.2f;
    tm->aberration = 0.003f;
    tm->vignette = 0.4f;
    tm->grain = 0.03f;
    tm->min_exposure = 0.5f;
    tm->max_exposure = 4.0f;
    tm->adaptation_speed = 3.0f;
    tm->current_luma = 0.5f;
    tm->auto_exposure = false;
    tm->saturation   = 1.1f;
    tm->contrast     = 1.05f;
    tm->brightness   = 1.0f;
    tm->temperature  = 0.0f;
    tm->tint         = 0.0f;

#ifdef ENGINE_VULKAN
    tm->tm_pipe = tm_create_pipe(dev, "shaders/post_vk.vert", "shaders/tonemap_vk.frag");
#else
    tm->tm_pipe = tm_create_pipe(dev, "shaders/post.vert", "shaders/tonemap.frag");
#endif

    if (!rhi_handle_valid(tm->tm_pipe)) {
        LOG_WARN("Tonemap: pipeline creation failed");
        return false;
    }

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    tm->sampler = rhi_sampler_create(dev, &sdesc);

    tm->loc_exposure   = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_exposure");
    tm->loc_gamma      = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_gamma");
    tm->loc_aberration = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_aberration");
    tm->loc_vignette   = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_vignette");
    tm->loc_grain      = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_grain");
    tm->loc_time       = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_time");
    tm->loc_screen_w   = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_screen_w");
    tm->loc_screen_h   = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_screen_h");
    tm->loc_saturation  = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_saturation");
    tm->loc_contrast    = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_contrast");
    tm->loc_brightness  = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_brightness");
    tm->loc_temperature = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_temperature");
    tm->loc_tint        = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_tint");

    tm->ready = true;
    LOG_INFO("Tonemap: initialized (ACES + cinematic, exposure=%.2f, gamma=%.2f)", tm->exposure, tm->gamma);
    return true;
}

void tonemap_shutdown(TonemapSystem *tm) {
    if (!tm->device) return;
    if (rhi_handle_valid(tm->lum_fbo.fb))  rhi_offscreen_fbo_destroy(tm->device, &tm->lum_fbo);
    if (rhi_handle_valid(tm->sampler))     rhi_sampler_destroy(tm->device, tm->sampler);
    if (rhi_handle_valid(tm->tm_pipe))     rhi_pipeline_destroy(tm->device, tm->tm_pipe);
    if (rhi_handle_valid(tm->lum_pipe))    rhi_pipeline_destroy(tm->device, tm->lum_pipe);
    tm->ready = false;
}

void tonemap_update_auto_exposure(TonemapSystem *tm, RHICmdBuffer *cmd,
                                   RHITexture hdr_tex, f32 dt) {
    if (!tm->ready || !tm->auto_exposure) return;
    (void)cmd;
    (void)hdr_tex;
    (void)dt;
}

void tonemap_apply(TonemapSystem *tm, RHICmdBuffer *cmd,
                   RHITexture hdr_tex, u32 screen_w, u32 screen_h, f32 time, f32 dt) {
    if (!tm->ready) return;
    (void)dt;

    rhi_cmd_bind_pipeline(cmd, tm->tm_pipe);
    rhi_cmd_bind_texture(cmd, hdr_tex, tm->sampler, 0);

    if (tm->loc_exposure >= 0)   rhi_cmd_set_uniform_f32(cmd, tm->loc_exposure, tm->exposure);
    if (tm->loc_gamma >= 0)      rhi_cmd_set_uniform_f32(cmd, tm->loc_gamma, tm->gamma);
    if (tm->loc_aberration >= 0) rhi_cmd_set_uniform_f32(cmd, tm->loc_aberration, tm->aberration);
    if (tm->loc_vignette >= 0)   rhi_cmd_set_uniform_f32(cmd, tm->loc_vignette, tm->vignette);
    if (tm->loc_grain >= 0)      rhi_cmd_set_uniform_f32(cmd, tm->loc_grain, tm->grain);
    if (tm->loc_time >= 0)       rhi_cmd_set_uniform_f32(cmd, tm->loc_time, time);
    if (tm->loc_screen_w >= 0)   rhi_cmd_set_uniform_f32(cmd, tm->loc_screen_w, (f32)screen_w);
    if (tm->loc_screen_h >= 0)   rhi_cmd_set_uniform_f32(cmd, tm->loc_screen_h, (f32)screen_h);
    if (tm->loc_saturation >= 0)  rhi_cmd_set_uniform_f32(cmd, tm->loc_saturation, tm->saturation);
    if (tm->loc_contrast >= 0)    rhi_cmd_set_uniform_f32(cmd, tm->loc_contrast, tm->contrast);
    if (tm->loc_brightness >= 0)  rhi_cmd_set_uniform_f32(cmd, tm->loc_brightness, tm->brightness);
    if (tm->loc_temperature >= 0) rhi_cmd_set_uniform_f32(cmd, tm->loc_temperature, tm->temperature);
    if (tm->loc_tint >= 0)        rhi_cmd_set_uniform_f32(cmd, tm->loc_tint, tm->tint);

    rhi_cmd_draw(cmd, 3, 1);
}
