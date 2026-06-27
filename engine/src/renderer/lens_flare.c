#include "lens_flare.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static char *lf_read_file(const char *path, usize *out_len) {
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

static RHIPipeline lf_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = lf_read_file(vert_path, &vs_len);
    char *fs_src = lf_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("LensFlare: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("LensFlare: shader compile failed");
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
        .alpha_blend = true,
    };
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

bool lens_flare_init(LensFlareSystem *lf, RHIDevice *dev, u32 width, u32 height) {
    if (!lf || !dev) return false;
    memset(lf, 0, sizeof(*lf));
    lf->device = dev;
    lf->intensity = 0.5f;

#ifdef ENGINE_VULKAN
    lf->lf_pipe = lf_create_pipe(dev, "shaders/post_vk.vert", "shaders/lens_flare_vk.frag");
#else
    lf->lf_pipe = lf_create_pipe(dev, "shaders/post.vert", "shaders/lens_flare.frag");
#endif

    if (!rhi_handle_valid(lf->lf_pipe)) {
        LOG_WARN("LensFlare: pipeline creation failed");
        return false;
    }

    u32 pw = width / 2;
    u32 ph = height / 2;
    if (pw < 1) pw = 1;
    if (ph < 1) ph = 1;
    lf->lf_fbo = rhi_offscreen_fbo_create_fmt(dev, pw, ph, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    lf->sampler = rhi_sampler_create(dev, &sdesc);

    lf->loc_light_x  = rhi_pipeline_get_uniform_location(dev, lf->lf_pipe, "u_lf_light_x");
    lf->loc_light_y  = rhi_pipeline_get_uniform_location(dev, lf->lf_pipe, "u_lf_light_y");
    lf->loc_intensity = rhi_pipeline_get_uniform_location(dev, lf->lf_pipe, "u_lf_intensity");
    lf->loc_screen_w  = rhi_pipeline_get_uniform_location(dev, lf->lf_pipe, "u_lf_sw");
    lf->loc_screen_h  = rhi_pipeline_get_uniform_location(dev, lf->lf_pipe, "u_lf_sh");
    lf->loc_lc_r      = rhi_pipeline_get_uniform_location(dev, lf->lf_pipe, "u_lf_lc_r");
    lf->loc_lc_g      = rhi_pipeline_get_uniform_location(dev, lf->lf_pipe, "u_lf_lc_g");
    lf->loc_lc_b      = rhi_pipeline_get_uniform_location(dev, lf->lf_pipe, "u_lf_lc_b");

    lf->ready = true;
    LOG_INFO("LensFlare: initialized (%ux%u, intensity=%.2f)", pw, ph, lf->intensity);
    return true;
}

void lens_flare_shutdown(LensFlareSystem *lf) {
    if (!lf->device) return;
    if (rhi_handle_valid(lf->lf_fbo.fb))  rhi_offscreen_fbo_destroy(lf->device, &lf->lf_fbo);
    if (rhi_handle_valid(lf->sampler))    rhi_sampler_destroy(lf->device, lf->sampler);
    if (rhi_handle_valid(lf->lf_pipe))    rhi_pipeline_destroy(lf->device, lf->lf_pipe);
    lf->ready = false;
}

void lens_flare_apply(LensFlareSystem *lf, RHICmdBuffer *cmd,
                      RHITexture depth_tex,
                      const f32 *view, const f32 *proj,
                      const f32 *light_dir,
                      f32 lc_r, f32 lc_g, f32 lc_b,
                      u32 screen_w, u32 screen_h) {
    if (!lf->ready) return;

    f32 lx = light_dir[0], ly = light_dir[1], lz = light_dir[2];
    f32 light_view_z = view[2] * lx + view[6] * ly + view[10] * lz;

    if (light_view_z > 0.0f) {
        rhi_offscreen_fbo_bind(cmd, &lf->lf_fbo);
        rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 0.0f);
        return;
    }

    f32 vx = view[0] * lx + view[4] * ly + view[8]  * lz;
    f32 vy = view[1] * lx + view[5] * ly + view[9]  * lz;
    f32 vz = view[2] * lx + view[6] * ly + view[10] * lz;

    f32 clip_x = proj[0] * vx + proj[4] * vy + proj[8]  * vz;
    f32 clip_y = proj[1] * vx + proj[5] * vy + proj[9]  * vz;
    f32 clip_w = proj[3] * vx + proj[7] * vy + proj[11] * vz;

    if (clip_w <= 0.001f) {
        rhi_offscreen_fbo_bind(cmd, &lf->lf_fbo);
        rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 0.0f);
        return;
    }

    f32 ndc_x = clip_x / clip_w;
    f32 ndc_y = clip_y / clip_w;
    f32 screen_x = ndc_x * 0.5f + 0.5f;
    f32 screen_y = ndc_y * 0.5f + 0.5f;

    rhi_offscreen_fbo_bind(cmd, &lf->lf_fbo);

    rhi_cmd_bind_pipeline(cmd, lf->lf_pipe);
    rhi_cmd_bind_texture(cmd, depth_tex, lf->sampler, 0);

    if (lf->loc_light_x >= 0)  rhi_cmd_set_uniform_f32(cmd, lf->loc_light_x, screen_x);
    if (lf->loc_light_y >= 0)  rhi_cmd_set_uniform_f32(cmd, lf->loc_light_y, screen_y);
    if (lf->loc_intensity >= 0) rhi_cmd_set_uniform_f32(cmd, lf->loc_intensity, lf->intensity);
    if (lf->loc_screen_w >= 0)  rhi_cmd_set_uniform_f32(cmd, lf->loc_screen_w, (f32)screen_w);
    if (lf->loc_screen_h >= 0)  rhi_cmd_set_uniform_f32(cmd, lf->loc_screen_h, (f32)screen_h);
    if (lf->loc_lc_r >= 0)      rhi_cmd_set_uniform_f32(cmd, lf->loc_lc_r, lc_r);
    if (lf->loc_lc_g >= 0)      rhi_cmd_set_uniform_f32(cmd, lf->loc_lc_g, lc_g);
    if (lf->loc_lc_b >= 0)      rhi_cmd_set_uniform_f32(cmd, lf->loc_lc_b, lc_b);

    rhi_cmd_draw(cmd, 3, 1);
}

RHITexture lens_flare_get_texture(LensFlareSystem *lf) {
    if (!lf->ready) return RHI_HANDLE_NULL;
    return lf->lf_fbo.color_tex;
}
