#include "sss.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *sss_read_file(const char *path, usize *out_len) {
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

static RHIPipeline sss_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = sss_read_file(vert_path, &vs_len);
    char *fs_src = sss_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("SSS: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("SSS: shader compile failed");
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

bool sss_init(SSSSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

#ifdef ENGINE_VULKAN
    s->h_pipe = sss_create_pipe(dev, "shaders/post_vk.vert", "shaders/sss_vk.frag");
    s->v_pipe = sss_create_pipe(dev, "shaders/post_vk.vert", "shaders/sss_vertical_vk.frag");
#else
    s->h_pipe = sss_create_pipe(dev, "shaders/post.vert", "shaders/sss.frag");
    s->v_pipe = sss_create_pipe(dev, "shaders/post.vert", "shaders/sss_vertical.frag");
#endif

    if (!rhi_handle_valid(s->h_pipe) || !rhi_handle_valid(s->v_pipe)) {
        LOG_WARN("SSS: pipeline creation failed");
        return false;
    }

    s->fbo = rhi_offscreen_fbo_create_fmt(dev, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT);
    s->blur_fbo = rhi_offscreen_fbo_create_fmt(dev, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    /* R348: align R347 — do not mark ready with empty FBO/sampler handles. */
    if (!rhi_handle_valid(s->fbo.fb) || !rhi_handle_valid(s->blur_fbo.fb) ||
        !rhi_handle_valid(s->sampler)) {
        LOG_WARN("SSS: FBO/sampler creation failed");
        sss_shutdown(s);
        return false;
    }

    s->loc_strength  = rhi_pipeline_get_uniform_location(dev, s->h_pipe, "u_sss_strength");
    s->loc_sw        = rhi_pipeline_get_uniform_location(dev, s->h_pipe, "u_sss_sw");
    s->loc_sh        = rhi_pipeline_get_uniform_location(dev, s->h_pipe, "u_sss_sh");
    s->loc_max_dist  = rhi_pipeline_get_uniform_location(dev, s->h_pipe, "u_sss_max_dist");

    s->v_loc_strength = rhi_pipeline_get_uniform_location(dev, s->v_pipe, "u_sssv_strength");
    s->v_loc_sw       = rhi_pipeline_get_uniform_location(dev, s->v_pipe, "u_sssv_sw");
    s->v_loc_sh       = rhi_pipeline_get_uniform_location(dev, s->v_pipe, "u_sssv_sh");
    s->v_loc_max_dist = rhi_pipeline_get_uniform_location(dev, s->v_pipe, "u_sssv_max_dist");

    s->ready = true;
    LOG_INFO("SSS: initialized (%ux%u)", w, h);
    return true;
}

void sss_shutdown(SSSSystem *s) {
    if (!s->dev) return;
    if (rhi_handle_valid(s->fbo.fb))      rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->blur_fbo.fb)) rhi_offscreen_fbo_destroy(s->dev, &s->blur_fbo);
    if (rhi_handle_valid(s->sampler))     rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->h_pipe))      rhi_pipeline_destroy(s->dev, s->h_pipe);
    if (rhi_handle_valid(s->v_pipe))      rhi_pipeline_destroy(s->dev, s->v_pipe);
    s->ready = false;
}

void sss_apply(SSSSystem *s, RHICmdBuffer *cmd,
               RHITexture color_tex, RHITexture depth_tex,
               f32 strength, f32 max_dist, u32 w, u32 h) {
    if (!s->ready) return;

    /* Pass 1: Horizontal blur → blur_fbo */
    rhi_offscreen_fbo_bind(cmd, &s->blur_fbo);
    rhi_cmd_bind_pipeline(cmd, s->h_pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures — rhi_cmd_bind_texture ignores
     * the unit parameter in VK and binds all 9 slots to one texture. */
    rhi_cmd_bind_material_textures(cmd, color_tex, color_tex, color_tex,
                                   color_tex, depth_tex, color_tex, s->sampler);

    if (s->loc_strength >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_strength, strength);
    if (s->loc_sw >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sw, (f32)w);
    if (s->loc_sh >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sh, (f32)h);
    if (s->loc_max_dist >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_max_dist, max_dist);

    rhi_cmd_draw(cmd, 3, 1);

    /* Pass 2: Vertical blur → fbo (reads blur_fbo + depth + original) */
    rhi_offscreen_fbo_bind(cmd, &s->fbo);
    rhi_cmd_bind_pipeline(cmd, s->v_pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures for multi-texture binding. */
    rhi_cmd_bind_material_textures(cmd, s->blur_fbo.color_tex, color_tex,
                                   s->blur_fbo.color_tex, s->blur_fbo.color_tex,
                                   depth_tex, s->blur_fbo.color_tex, s->sampler);

    if (s->v_loc_strength >= 0) rhi_cmd_set_uniform_f32(cmd, s->v_loc_strength, strength);
    if (s->v_loc_sw >= 0)       rhi_cmd_set_uniform_f32(cmd, s->v_loc_sw, (f32)w);
    if (s->v_loc_sh >= 0)       rhi_cmd_set_uniform_f32(cmd, s->v_loc_sh, (f32)h);
    if (s->v_loc_max_dist >= 0) rhi_cmd_set_uniform_f32(cmd, s->v_loc_max_dist, max_dist);

    rhi_cmd_draw(cmd, 3, 1);
}
