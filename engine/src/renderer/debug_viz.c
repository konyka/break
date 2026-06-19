#include "debug_viz.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *dv_read_file(const char *path, usize *out_len) {
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

static RHIPipeline dv_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = dv_read_file(vert_path, &vs_len);
    char *fs_src = dv_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("DebugViz: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("DebugViz: shader compile failed");
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

bool debug_viz_init(DebugVizSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

#ifdef ENGINE_VULKAN
    s->pipe = dv_create_pipe(dev, "shaders/post_vk.vert", "shaders/debug_viz_vk.frag");
#else
    s->pipe = dv_create_pipe(dev, "shaders/post.vert", "shaders/debug_viz.frag");
#endif

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("DebugViz: pipeline creation failed");
        return false;
    }

    s->fbo = rhi_offscreen_fbo_create(dev, w, h);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    s->loc_mode = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_dv_mode");
    s->loc_near = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_dv_near");
    s->loc_far  = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_dv_far");
    s->loc_split0 = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_dv_split0");
    s->loc_split1 = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_dv_split1");
    s->loc_split2 = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_dv_split2");
    s->loc_split3 = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_dv_split3");

    s->ready = true;
    return true;
}

void debug_viz_shutdown(DebugVizSystem *s) {
    if (!s || !s->dev) return;
    if (rhi_handle_valid(s->pipe)) rhi_pipeline_destroy(s->dev, s->pipe);
    if (rhi_handle_valid(s->fbo.fb)) rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->sampler)) rhi_sampler_destroy(s->dev, s->sampler);
    memset(s, 0, sizeof(*s));
}

void debug_viz_apply(DebugVizSystem *s, RHICmdBuffer *cmd,
                     RHITexture input_tex, RHITexture depth_tex,
                     i32 mode, f32 near_plane, f32 far_plane,
                     const f32 *cascade_splits, u32 w, u32 h) {
    if (!s || !s->ready) return;
    (void)w; (void)h;

    rhi_offscreen_fbo_bind(cmd, &s->fbo);

    rhi_cmd_bind_pipeline(cmd, s->pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures — rhi_cmd_bind_texture ignores
     * the unit parameter in VK and binds all 9 slots to one texture. */
    rhi_cmd_bind_material_textures(cmd, input_tex, input_tex, input_tex,
                                   input_tex, depth_tex, input_tex, s->sampler);

    if (s->loc_mode >= 0) rhi_cmd_set_uniform_i32(cmd, s->loc_mode, mode);
    if (s->loc_near >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_near, near_plane);
    if (s->loc_far  >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_far, far_plane);
    if (cascade_splits) {
        if (s->loc_split0 >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_split0, cascade_splits[1]);
        if (s->loc_split1 >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_split1, cascade_splits[2]);
        if (s->loc_split2 >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_split2, cascade_splits[3]);
        if (s->loc_split3 >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_split3, cascade_splits[4]);
    }

    rhi_cmd_draw(cmd, 3, 1);
    rhi_offscreen_fbo_unbind(cmd, w, h);
}
