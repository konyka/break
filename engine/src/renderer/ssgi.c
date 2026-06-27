#include "ssgi.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ssgi_read_file(const char *path, usize *out_len) {
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

static RHIPipeline ssgi_create_pipe(RHIDevice *dev,
                                     const char *vert_path, const char *frag_path,
                                     bool alpha_blend) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = ssgi_read_file(vert_path, &vs_len);
    char *fs_src = ssgi_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("SSGI: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("SSGI: shader compile failed");
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
        .alpha_blend = alpha_blend,
    };
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

bool ssgi_init(SSGISystem *ssgi, RHIDevice *dev, u32 width, u32 height) {
    if (!ssgi || !dev) return false;
    memset(ssgi, 0, sizeof(*ssgi));
    ssgi->device = dev;
    ssgi->radius = 0.5f;
    ssgi->intensity = 0.3f;

    u32 pw = width / 2;
    u32 ph = height / 2;
    if (pw < 1) pw = 1;
    if (ph < 1) ph = 1;

#ifdef ENGINE_VULKAN
    ssgi->ssgi_pipe = ssgi_create_pipe(dev, "shaders/post_vk.vert", "shaders/ssgi_vk.frag", false);
    ssgi->ssgi_blur_pipe = ssgi_create_pipe(dev, "shaders/post_vk.vert", "shaders/bloom_blur_vk.frag", false);
#else
    ssgi->ssgi_pipe = ssgi_create_pipe(dev, "shaders/post.vert", "shaders/ssgi.frag", false);
    ssgi->ssgi_blur_pipe = ssgi_create_pipe(dev, "shaders/post.vert", "shaders/bloom_blur.frag", false);
#endif

    if (!rhi_handle_valid(ssgi->ssgi_pipe) || !rhi_handle_valid(ssgi->ssgi_blur_pipe)) {
        LOG_WARN("SSGI: pipeline creation failed");
        return false;
    }

    ssgi->ssgi_fbo = rhi_offscreen_fbo_create_fmt(dev, pw, ph, RHI_FORMAT_R16G16B16A16_SFLOAT);
    ssgi->ssgi_blur_fbo = rhi_offscreen_fbo_create_fmt(dev, pw, ph, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    ssgi->sampler = rhi_sampler_create(dev, &sdesc);

    ssgi->loc_inv_proj = rhi_pipeline_get_uniform_location(dev, ssgi->ssgi_pipe, "u_ssgi_inv_proj");
    ssgi->loc_proj     = rhi_pipeline_get_uniform_location(dev, ssgi->ssgi_pipe, "u_ssgi_proj");
    ssgi->loc_radius   = rhi_pipeline_get_uniform_location(dev, ssgi->ssgi_pipe, "u_ssgi_radius");
    ssgi->loc_intensity= rhi_pipeline_get_uniform_location(dev, ssgi->ssgi_pipe, "u_ssgi_intensity");
    ssgi->loc_screen_w = rhi_pipeline_get_uniform_location(dev, ssgi->ssgi_pipe, "u_ssgi_sw");
    ssgi->loc_screen_h = rhi_pipeline_get_uniform_location(dev, ssgi->ssgi_pipe, "u_ssgi_sh");

    /* R113-1: Query the blur direction uniform location from the pipeline
     * instead of hardcoding 0.  In GL the linker assigns locations and they
     * are not guaranteed to be 0 — the hardcoded value was overwriting the
     * wrong uniform, corrupting the SSGI blur pass. */
    ssgi->loc_blur_dir_x = rhi_pipeline_get_uniform_location(dev, ssgi->ssgi_blur_pipe, "u_direction");
    ssgi->loc_blur_dir_y = -1;  /* unused — kept for ABI compatibility */

    ssgi->ready = true;
    LOG_INFO("SSGI: initialized (%ux%u, radius=%.2f, intensity=%.2f)", pw, ph, ssgi->radius, ssgi->intensity);
    return true;
}

void ssgi_shutdown(SSGISystem *ssgi) {
    if (!ssgi->device) return;
    if (rhi_handle_valid(ssgi->ssgi_fbo.fb))      rhi_offscreen_fbo_destroy(ssgi->device, &ssgi->ssgi_fbo);
    if (rhi_handle_valid(ssgi->ssgi_blur_fbo.fb))  rhi_offscreen_fbo_destroy(ssgi->device, &ssgi->ssgi_blur_fbo);
    if (rhi_handle_valid(ssgi->sampler))           rhi_sampler_destroy(ssgi->device, ssgi->sampler);
    if (rhi_handle_valid(ssgi->ssgi_pipe))         rhi_pipeline_destroy(ssgi->device, ssgi->ssgi_pipe);
    if (rhi_handle_valid(ssgi->ssgi_blur_pipe))    rhi_pipeline_destroy(ssgi->device, ssgi->ssgi_blur_pipe);
    ssgi->ready = false;
}

void ssgi_apply(SSGISystem *ssgi, RHICmdBuffer *cmd,
                RHITexture depth_tex, RHITexture color_tex,
                const f32 *inv_proj, const f32 *proj,
                u32 screen_w, u32 screen_h) {
    if (!ssgi->ready) return;

    rhi_offscreen_fbo_bind(cmd, &ssgi->ssgi_fbo);

    rhi_cmd_bind_pipeline(cmd, ssgi->ssgi_pipe);
    RHITexture ssgi_texs[] = { depth_tex, color_tex };
    rhi_cmd_bind_textures_multi(cmd, ssgi_texs, 2, ssgi->sampler);

    if (ssgi->loc_inv_proj >= 0)  rhi_cmd_set_uniform_mat4(cmd, ssgi->loc_inv_proj, inv_proj);
    if (ssgi->loc_proj >= 0)      rhi_cmd_set_uniform_mat4(cmd, ssgi->loc_proj, proj);
    if (ssgi->loc_radius >= 0)    rhi_cmd_set_uniform_f32(cmd, ssgi->loc_radius, ssgi->radius);
    if (ssgi->loc_intensity >= 0) rhi_cmd_set_uniform_f32(cmd, ssgi->loc_intensity, ssgi->intensity);
    if (ssgi->loc_screen_w >= 0)  rhi_cmd_set_uniform_f32(cmd, ssgi->loc_screen_w, (f32)screen_w);
    if (ssgi->loc_screen_h >= 0)  rhi_cmd_set_uniform_f32(cmd, ssgi->loc_screen_h, (f32)screen_h);

    rhi_cmd_draw(cmd, 3, 1);

    rhi_offscreen_fbo_bind(cmd, &ssgi->ssgi_blur_fbo);
    rhi_cmd_bind_pipeline(cmd, ssgi->ssgi_blur_pipe);
    rhi_cmd_bind_texture(cmd, ssgi->ssgi_fbo.color_tex, ssgi->sampler, 0);
    if (ssgi->loc_blur_dir_x >= 0) rhi_cmd_set_uniform_vec2(cmd, ssgi->loc_blur_dir_x, 1.0f, 0.0f);
    rhi_cmd_draw(cmd, 3, 1);
}

RHITexture ssgi_get_texture(SSGISystem *ssgi) {
    if (!ssgi->ready) return RHI_HANDLE_NULL;
    return ssgi->ssgi_blur_fbo.color_tex;
}
