#include "upscale.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ups_read_file(const char *path, usize *out_len) {
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

static RHIPipeline ups_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = ups_read_file(vert_path, &vs_len);
    char *fs_src = ups_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("Upscale: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Upscale: shader compile failed");
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

bool upscale_init(UpscaleSystem *s, RHIDevice *dev,
                  u32 render_w, u32 render_h,
                  u32 display_w, u32 display_h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

#ifdef ENGINE_VULKAN
    s->pipe = ups_create_pipe(dev, "shaders/post_vk.vert", "shaders/upscale_vk.frag");
#else
    s->pipe = ups_create_pipe(dev, "shaders/post.vert", "shaders/upscale.frag");
#endif

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("Upscale: pipeline creation failed");
        return false;
    }

    s->fbo = rhi_offscreen_fbo_create_fmt(dev, display_w, display_h, RHI_FORMAT_R8G8B8A8_UNORM);
    s->history[0] = rhi_offscreen_fbo_create_fmt(dev, display_w, display_h, RHI_FORMAT_R8G8B8A8_UNORM);
    s->history[1] = rhi_offscreen_fbo_create_fmt(dev, display_w, display_h, RHI_FORMAT_R8G8B8A8_UNORM);
    s->history_idx = 0;

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    /* R348: align R347 — present path uses upscale when ready; reject empty FBOs. */
    if (!rhi_handle_valid(s->fbo.fb) || !rhi_handle_valid(s->history[0].fb) ||
        !rhi_handle_valid(s->history[1].fb) || !rhi_handle_valid(s->sampler)) {
        LOG_WARN("Upscale: FBO/sampler creation failed");
        upscale_shutdown(s);
        return false;
    }

    s->loc_rw       = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_ups_rw");
    s->loc_rh       = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_ups_rh");
    s->loc_dw       = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_ups_dw");
    s->loc_dh       = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_ups_dh");
    s->loc_sharp     = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_ups_sharp");
    s->loc_copy_only = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_ups_copy_only");
    s->loc_inv_proj  = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_ups_inv_proj");
    s->loc_prev_vp   = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_ups_prev_vp");

    s->ready = true;
    LOG_INFO("Upscale: TSR initialized (%ux%u → %ux%u)", render_w, render_h, display_w, display_h);
    return true;
}

void upscale_shutdown(UpscaleSystem *s) {
    if (!s->dev) return;
    if (rhi_handle_valid(s->fbo.fb))         rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->history[0].fb))   rhi_offscreen_fbo_destroy(s->dev, &s->history[0]);
    if (rhi_handle_valid(s->history[1].fb))   rhi_offscreen_fbo_destroy(s->dev, &s->history[1]);
    if (rhi_handle_valid(s->sampler))         rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->pipe))            rhi_pipeline_destroy(s->dev, s->pipe);
    s->ready = false;
}

void upscale_apply(UpscaleSystem *s, RHICmdBuffer *cmd,
                   RHITexture input_tex, RHITexture depth_tex,
                   const f32 *inv_proj, const f32 *prev_vp,
                   f32 sharpness,
                   u32 render_w, u32 render_h,
                   u32 display_w, u32 display_h) {
    if (!s->ready) return;

    i32 read_idx  = s->history_idx;
    i32 write_idx = 1 - s->history_idx;

    /* Pass 1: temporal upscale into output FBO */
    rhi_offscreen_fbo_bind(cmd, &s->fbo);
    rhi_cmd_bind_pipeline(cmd, s->pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures instead of three rhi_cmd_bind_texture
     * calls. In the VK path, rhi_cmd_bind_texture ignores the unit parameter and
     * binds all 9 descriptor slots to the same texture — each subsequent call
     * overwrites the previous, so only the last texture (history) would be visible.
     * rhi_cmd_bind_material_textures correctly assigns albedo->binding 0 (u_ups_src),
     * shadow->binding 1 (u_ups_depth), mr->binding 2 (u_ups_history) in one call. */
    rhi_cmd_bind_material_textures(cmd, input_tex, s->history[read_idx].color_tex,
                                   input_tex, input_tex, depth_tex, input_tex, s->sampler);

    if (s->loc_rw >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_rw, (f32)render_w);
    if (s->loc_rh >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_rh, (f32)render_h);
    if (s->loc_dw >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_dw, (f32)display_w);
    if (s->loc_dh >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_dh, (f32)display_h);
    if (s->loc_sharp >= 0)     rhi_cmd_set_uniform_f32(cmd, s->loc_sharp, sharpness);
    if (s->loc_copy_only >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_copy_only, 0.0f);
    if (s->loc_inv_proj >= 0)  rhi_cmd_set_uniform_mat4(cmd, s->loc_inv_proj, inv_proj);
    if (s->loc_prev_vp >= 0)   rhi_cmd_set_uniform_mat4(cmd, s->loc_prev_vp, prev_vp);

    rhi_cmd_draw(cmd, 3, 1);

    /* Pass 2: blit Pass 1 result into history (no second TSR mix). */
    rhi_offscreen_fbo_bind(cmd, &s->history[write_idx]);
    rhi_cmd_bind_pipeline(cmd, s->pipe);
    /* R197-A: history/depth unused when copy_only; bind fbo.color_tex for all slots. */
    rhi_cmd_bind_material_textures(cmd, s->fbo.color_tex, s->fbo.color_tex,
                                   s->fbo.color_tex, s->fbo.color_tex, s->fbo.color_tex,
                                   s->fbo.color_tex, s->sampler);

    if (s->loc_rw >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_rw, (f32)render_w);
    if (s->loc_rh >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_rh, (f32)render_h);
    if (s->loc_dw >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_dw, (f32)display_w);
    if (s->loc_dh >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_dh, (f32)display_h);
    if (s->loc_sharp >= 0)     rhi_cmd_set_uniform_f32(cmd, s->loc_sharp, 0.0f);
    if (s->loc_copy_only >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_copy_only, 1.0f);
    if (s->loc_inv_proj >= 0)  rhi_cmd_set_uniform_mat4(cmd, s->loc_inv_proj, inv_proj);
    if (s->loc_prev_vp >= 0)   rhi_cmd_set_uniform_mat4(cmd, s->loc_prev_vp, prev_vp);

    rhi_cmd_draw(cmd, 3, 1);

    s->history_idx = write_idx;
}
