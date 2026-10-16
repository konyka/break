#include "motion_blur.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline mb_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("MotionBlur: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("MotionBlur: shader compile failed");
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

bool motion_blur_init(MotionBlurSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
        !shader_variant_path("shaders/motion_blur.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
        LOG_WARN("MotionBlur: capability query or shader variant path failed");
        return false;
    }
    s->pipe = mb_create_pipe(dev, vs_path, fs_path);

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("MotionBlur: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_mb_* 是
     * motion_blur(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    s->bind_pipe = rhi_pipeline_bindings_create(dev, s->pipe);
    if (!s->bind_pipe)
        LOG_WARN("MotionBlur: bindings create failed; uniform locations resolve -1");

    s->fbo = rhi_offscreen_fbo_create_fmt(dev, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT);

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
        LOG_WARN("MotionBlur: FBO/sampler creation failed");
        motion_blur_shutdown(s);
        return false;
    }

    s->loc_strength = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_mb_strength");
    s->loc_sw       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_mb_sw");
    s->loc_sh       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_mb_sh");
    s->loc_inv_proj = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_mb_inv_proj");
    s->loc_prev_vp  = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_mb_prev_vp");
    s->loc_use_velocity = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_mb_use_velocity");

    s->ready = true;
    LOG_INFO("MotionBlur: initialized (%ux%u)", w, h);
    return true;
}

void motion_blur_shutdown(MotionBlurSystem *s) {
    if (!s->dev) return;
    if (s->bind_pipe) { rhi_pipeline_bindings_destroy(s->dev, s->bind_pipe); s->bind_pipe = NULL; }
    if (rhi_handle_valid(s->fbo.fb))   rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->sampler))  rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->pipe))     rhi_pipeline_destroy(s->dev, s->pipe);
    s->ready = false;
}

void motion_blur_apply(MotionBlurSystem *s, RHICmdBuffer *cmd,
                       RHITexture color_tex, RHITexture depth_tex,
                       RHITexture velocity_tex,
                       const f32 *inv_proj, const f32 *prev_vp,
                       f32 strength, u32 w, u32 h) {
    if (!s->ready) return;

    rhi_offscreen_fbo_bind(cmd, &s->fbo);

    rhi_cmd_bind_pipeline(cmd, s->pipe);
    bool use_velocity = rhi_handle_valid(velocity_tex);
    /* Keep the third descriptor valid even when only the depth reconstruction
     * fallback is available; Vulkan requires all statically declared samplers
     * to be updated before the fullscreen draw. */
    RHITexture tex[3] = { color_tex, depth_tex,
                          use_velocity ? velocity_tex : color_tex };
    rhi_cmd_bind_textures_multi(cmd, tex, 3, s->sampler);

    if (s->loc_strength >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_strength, strength);
    if (s->loc_sw >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sw, (f32)w);
    if (s->loc_sh >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sh, (f32)h);
    if (s->loc_inv_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, s->loc_inv_proj, inv_proj);
    if (s->loc_prev_vp >= 0)  rhi_cmd_set_uniform_mat4(cmd, s->loc_prev_vp, prev_vp);
    if (s->loc_use_velocity >= 0)
        rhi_cmd_set_uniform_f32(cmd, s->loc_use_velocity, use_velocity ? 1.0f : 0.0f);

    rhi_cmd_draw(cmd, 3, 1);
}
