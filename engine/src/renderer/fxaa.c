#include "fxaa.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline fxaa_create_pipe_path(RHIDevice *dev, const char *vert_path,
                                         const char *frag_path) {
    RHIShader vs = rhi_shader_create_path(dev, vert_path, false);
    RHIShader fs = rhi_shader_create_path(dev, frag_path, true);
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("FXAA: sidecar shader unavailable (%s, %s)", vert_path,
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

static RHIPipeline fxaa_create_pipe(RHIDevice *dev,
                                     const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
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

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps)) {
        LOG_WARN("FXAA: capability query failed");
        return false;
    }
    if (caps.shader_sidecar_paths) {
        /* R619: D3D12 never compiles HLSL in-process, so the GLSL branch
         * below cannot build there; the backend resolves these two names to
         * post_hlsl.vert / fxaa_hlsl.frag. */
        fxaa->fxaa_pipe = fxaa_create_pipe_path(dev, "shaders/post.vert",
                                                "shaders/fxaa.frag");
    } else {
        if (!shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
            !shader_variant_path("shaders/fxaa.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
            LOG_WARN("FXAA: shader variant path failed");
            return false;
        }
        fxaa->fxaa_pipe = fxaa_create_pipe(dev, vs_path, fs_path);
    }

    if (!rhi_handle_valid(fxaa->fxaa_pipe)) {
        LOG_WARN("FXAA: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_fxaa_ 前缀名是
     * fxaa(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    fxaa->bind_pipe = rhi_pipeline_bindings_create(dev, fxaa->fxaa_pipe);
    if (!fxaa->bind_pipe)
        LOG_WARN("FXAA: bindings create failed; uniform locations resolve -1");

    fxaa->fxaa_fbo = rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    fxaa->sampler = rhi_sampler_create(dev, &sdesc);

    /* R348: align R347 — do not mark ready with empty FBO/sampler handles. */
    if (!rhi_handle_valid(fxaa->fxaa_fbo.fb) || !rhi_handle_valid(fxaa->sampler)) {
        LOG_WARN("FXAA: FBO/sampler creation failed");
        fxaa_shutdown(fxaa);
        return false;
    }

    fxaa->loc_screen_w = rhi_pipeline_bindings_resolve(fxaa->bind_pipe, "u_fxaa_sw");
    fxaa->loc_screen_h = rhi_pipeline_bindings_resolve(fxaa->bind_pipe, "u_fxaa_sh");
    fxaa->loc_threshold = rhi_pipeline_bindings_resolve(fxaa->bind_pipe, "u_fxaa_threshold");
    fxaa->threshold = 0.0312f;

    fxaa->ready = true;
    LOG_INFO("FXAA: initialized (%ux%u)", width, height);
    return true;
}

void fxaa_shutdown(FXAASystem *fxaa) {
    if (!fxaa->device) return;
    if (fxaa->bind_pipe) { rhi_pipeline_bindings_destroy(fxaa->device, fxaa->bind_pipe); fxaa->bind_pipe = NULL; }
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
