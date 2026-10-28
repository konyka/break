#include "color_grade.h"
#include <renderer/post_targets.h>
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline cg_create_pipe_path(RHIDevice *dev, const char *vert_path,
                                       const char *frag_path) {
    RHIShader vs = rhi_shader_create_path(dev, vert_path, false);
    RHIShader fs = rhi_shader_create_path(dev, frag_path, true);
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("ColorGrade: sidecar shader unavailable (%s, %s)", vert_path,
                 frag_path);
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs;
    pdesc.frag = fs;
    pdesc.no_vertex_input = true;
    pdesc.uses_textures = true;
    pdesc.depth_write_disable = true;
    pdesc.disable_culling = true;
    pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

static RHIPipeline cg_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
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

static bool color_grade_targets_create(ColorGradeSystem *s, RHIDevice *dev, u32 w, u32 h) {
    const PostTargetSpec t[1] = {
        { &s->fbo, w, h, RHI_FORMAT_UNDEFINED },
    };
    return post_targets_replace(dev, t, 1u);
}

bool color_grade_init(ColorGradeSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps)) {
        LOG_WARN("ColorGrade: capability query failed");
        return false;
    }

    if (caps.shader_sidecar_paths) {
        /* R617: on D3D12 the GLSL branch below is a dead end -- this backend
         * never compiles HLSL in-process, so rhi_shader_create refuses the
         * source (see rhi_d3d12_shader_alloc) and the pipeline never built.
         * The two paths the caller names are the ones to hand to
         * rhi_shader_create_path: the backend appends _hlsl itself. */
        s->pipe = cg_create_pipe_path(dev, "shaders/post.vert",
                                      "shaders/color_grade.frag");
    } else {
        if (!shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
            !shader_variant_path("shaders/color_grade.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
            LOG_WARN("ColorGrade: shader variant path failed");
            return false;
        }
        s->pipe = cg_create_pipe(dev, vs_path, fs_path);
    }

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("ColorGrade: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_cg_ 前缀名是
     * color_grade(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    s->bind_pipe = rhi_pipeline_bindings_create(dev, s->pipe);
    if (!s->bind_pipe)
        LOG_WARN("ColorGrade: bindings create failed; uniform locations resolve -1");

    (void)color_grade_targets_create(s, dev, w, h);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    /* R348: align R347 — do not mark ready with empty FBO/sampler handles. */
    if (!rhi_handle_valid(s->fbo.fb) || !rhi_handle_valid(s->sampler)) {
        LOG_WARN("ColorGrade: FBO/sampler creation failed");
        color_grade_shutdown(s);
        return false;
    }

    s->loc_saturation  = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cg_saturation");
    s->loc_contrast    = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cg_contrast");
    s->loc_brightness  = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cg_brightness");
    s->loc_temperature = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cg_temperature");
    s->loc_tint        = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cg_tint");

    s->ready = true;
    LOG_INFO("ColorGrade: initialized (%ux%u)", w, h);
    return true;
}

bool color_grade_resize(ColorGradeSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev || !s->ready || s->dev != dev) return false;
    if (!color_grade_targets_create(s, dev, w, h)) {
        LOG_WARN("ColorGrade: resize to %ux%u failed; keeping previous targets", w, h);
        return false;
    }
    return true;
}

void color_grade_shutdown(ColorGradeSystem *s) {
    if (!s->dev) return;
    if (s->bind_pipe) { rhi_pipeline_bindings_destroy(s->dev, s->bind_pipe); s->bind_pipe = NULL; }
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
