#include "tonemap.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *tm_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
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
    memset(tm, 0, sizeof(*tm));
    tm->device = dev;
    tm->exposure = 1.5f;
    tm->gamma = 2.2f;
    tm->mode = 0;
    tm->min_exposure = 0.5f;
    tm->max_exposure = 4.0f;
    tm->adaptation_speed = 3.0f;
    tm->current_luma = 0.5f;
    tm->auto_exposure = true;
    tm->lum_idx      = 0;

#ifdef ENGINE_VULKAN
    tm->tm_pipe = tm_create_pipe(dev, "shaders/post_vk.vert", "shaders/tonemap_vk.frag");
    tm->lum_pipe = tm_create_pipe(dev, "shaders/post_vk.vert", "shaders/luminance_vk.frag");
#else
    tm->tm_pipe = tm_create_pipe(dev, "shaders/post.vert", "shaders/tonemap.frag");
    tm->lum_pipe = tm_create_pipe(dev, "shaders/post.vert", "shaders/luminance.frag");
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
    tm->loc_mode       = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_mode");
    tm->loc_tm_lum      = rhi_pipeline_get_uniform_location(dev, tm->tm_pipe, "u_tm_lum");

    if (rhi_handle_valid(tm->lum_pipe)) {
        tm->lum_fbo[0] = rhi_offscreen_fbo_create_fmt(dev, 1, 1, RHI_FORMAT_R16G16B16A16_SFLOAT);
        tm->lum_fbo[1] = rhi_offscreen_fbo_create_fmt(dev, 1, 1, RHI_FORMAT_R16G16B16A16_SFLOAT);
        tm->loc_lum_w     = rhi_pipeline_get_uniform_location(dev, tm->lum_pipe, "u_lum_w");
        tm->loc_lum_h     = rhi_pipeline_get_uniform_location(dev, tm->lum_pipe, "u_lum_h");
        tm->loc_lum_speed = rhi_pipeline_get_uniform_location(dev, tm->lum_pipe, "u_lum_speed");
        tm->loc_lum_dt    = rhi_pipeline_get_uniform_location(dev, tm->lum_pipe, "u_lum_dt");
        tm->loc_lum_tex   = rhi_pipeline_get_uniform_location(dev, tm->lum_pipe, "u_lum_hdr");
        tm->loc_lum_prev  = rhi_pipeline_get_uniform_location(dev, tm->lum_pipe, "u_lum_prev");
    }

    /* R349: align R348 — sampler required; lum FBOs required when lum_pipe exists. */
    if (!rhi_handle_valid(tm->sampler) ||
        (rhi_handle_valid(tm->lum_pipe) &&
         (!rhi_handle_valid(tm->lum_fbo[0].fb) || !rhi_handle_valid(tm->lum_fbo[1].fb)))) {
        LOG_WARN("Tonemap: sampler/lum FBO creation failed");
        tonemap_shutdown(tm);
        return false;
    }

    tm->ready = true;
    LOG_INFO("Tonemap: initialized (ACES + auto-exposure, exposure=%.2f, gamma=%.2f)", tm->exposure, tm->gamma);
    return true;
}

void tonemap_shutdown(TonemapSystem *tm) {
    if (!tm->device) return;
    if (rhi_handle_valid(tm->lum_fbo[0].fb)) rhi_offscreen_fbo_destroy(tm->device, &tm->lum_fbo[0]);
    if (rhi_handle_valid(tm->lum_fbo[1].fb)) rhi_offscreen_fbo_destroy(tm->device, &tm->lum_fbo[1]);
    if (rhi_handle_valid(tm->sampler))     rhi_sampler_destroy(tm->device, tm->sampler);
    if (rhi_handle_valid(tm->tm_pipe))     rhi_pipeline_destroy(tm->device, tm->tm_pipe);
    if (rhi_handle_valid(tm->lum_pipe))    rhi_pipeline_destroy(tm->device, tm->lum_pipe);
    tm->ready = false;
}

void tonemap_update_auto_exposure(TonemapSystem *tm, RHICmdBuffer *cmd,
                                   RHITexture hdr_tex, u32 screen_w, u32 screen_h, f32 dt) {
    if (!tm->ready || !tm->auto_exposure) return;
    if (!rhi_handle_valid(tm->lum_pipe)) return;

    i32 read_idx  = tm->lum_idx;
    i32 write_idx = 1 - tm->lum_idx;

    rhi_offscreen_fbo_bind(cmd, &tm->lum_fbo[write_idx]);
    rhi_cmd_bind_pipeline(cmd, tm->lum_pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures instead of two rhi_cmd_bind_texture
     * calls. In the VK path, rhi_cmd_bind_texture ignores the unit parameter and
     * binds all 9 descriptor slots to the same texture — the second call would
     * overwrite the first, making the shader see lum_prev on binding 0 (u_lum_hdr)
     * instead of hdr_tex. */
    rhi_cmd_bind_material_textures(cmd, hdr_tex, hdr_tex, hdr_tex,
                                   hdr_tex, tm->lum_fbo[read_idx].color_tex, hdr_tex, tm->sampler);

    if (tm->loc_lum_w >= 0)     rhi_cmd_set_uniform_f32(cmd, tm->loc_lum_w, (f32)screen_w);
    if (tm->loc_lum_h >= 0)     rhi_cmd_set_uniform_f32(cmd, tm->loc_lum_h, (f32)screen_h);
    if (tm->loc_lum_speed >= 0) rhi_cmd_set_uniform_f32(cmd, tm->loc_lum_speed, tm->adaptation_speed);
    if (tm->loc_lum_dt >= 0)    rhi_cmd_set_uniform_f32(cmd, tm->loc_lum_dt, dt > 0.0f ? dt : 0.016f);

    rhi_cmd_draw(cmd, 3, 1);

    tm->lum_idx = write_idx;
}

void tonemap_apply(TonemapSystem *tm, RHICmdBuffer *cmd,
                   RHITexture hdr_tex, u32 screen_w, u32 screen_h) {
    if (!tm->ready) return;
    (void)screen_w; (void)screen_h;

    rhi_cmd_bind_pipeline(cmd, tm->tm_pipe);

    if (tm->auto_exposure && rhi_handle_valid(tm->lum_pipe)) {
        /* R99-2: Use rhi_cmd_bind_material_textures to avoid VK texture binding
         * overwrite bug when binding two textures. */
        rhi_cmd_bind_material_textures(cmd, hdr_tex, hdr_tex, hdr_tex,
                                       hdr_tex, tm->lum_fbo[tm->lum_idx].color_tex, hdr_tex, tm->sampler);
    } else {
        rhi_cmd_bind_texture(cmd, hdr_tex, tm->sampler, 0);
    }

    if (tm->loc_exposure >= 0)   rhi_cmd_set_uniform_f32(cmd, tm->loc_exposure, tm->exposure);
    if (tm->loc_gamma >= 0)      rhi_cmd_set_uniform_f32(cmd, tm->loc_gamma, tm->gamma);
    if (tm->loc_mode >= 0)       rhi_cmd_set_uniform_i32(cmd, tm->loc_mode, tm->mode);

    rhi_cmd_draw(cmd, 3, 1);
}
