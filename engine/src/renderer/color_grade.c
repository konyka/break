#include "color_grade.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *cg_read_file(const char *path, usize *out_len) {
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

static RHIPipeline cg_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = cg_read_file(vert_path, &vs_len);
    char *fs_src = cg_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("ColorGrade: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("ColorGrade: shader compile failed");
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

bool color_grade_init(ColorGradeSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

#ifdef ENGINE_VULKAN
    s->pipe = cg_create_pipe(dev, "shaders/post_vk.vert", "shaders/color_grade_vk.frag");
#else
    s->pipe = cg_create_pipe(dev, "shaders/post.vert", "shaders/color_grade.frag");
#endif

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("ColorGrade: pipeline creation failed");
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

    s->loc_saturation  = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cg_saturation");
    s->loc_contrast    = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cg_contrast");
    s->loc_brightness  = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cg_brightness");
    s->loc_temperature = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cg_temperature");
    s->loc_tint        = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cg_tint");

    s->ready = true;
    LOG_INFO("ColorGrade: initialized (%ux%u)", w, h);
    return true;
}

void color_grade_shutdown(ColorGradeSystem *s) {
    if (!s->dev) return;
    if (rhi_handle_valid(s->fbo.fb))   rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->sampler))  rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->pipe))     rhi_pipeline_destroy(s->dev, s->pipe);
    s->ready = false;
}

void color_grade_apply(ColorGradeSystem *s, RHICmdBuffer *cmd,
                       RHITexture input_tex, f32 saturation, f32 contrast,
                       f32 brightness, f32 temperature, f32 tint,
                       u32 w, u32 h) {
    if (!s->ready) return;
    (void)w; (void)h;

    rhi_offscreen_fbo_bind(cmd, &s->fbo);

    rhi_cmd_bind_pipeline(cmd, s->pipe);
    rhi_cmd_bind_texture(cmd, input_tex, s->sampler, 0);

    if (s->loc_saturation >= 0)  rhi_cmd_set_uniform_f32(cmd, s->loc_saturation, saturation);
    if (s->loc_contrast >= 0)    rhi_cmd_set_uniform_f32(cmd, s->loc_contrast, contrast);
    if (s->loc_brightness >= 0)  rhi_cmd_set_uniform_f32(cmd, s->loc_brightness, brightness);
    if (s->loc_temperature >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_temperature, temperature);
    if (s->loc_tint >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_tint, tint);

    rhi_cmd_draw(cmd, 3, 1);
}
